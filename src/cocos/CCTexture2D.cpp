/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "CCTexture2D.h"
#include "CCTextureCache.h"
#include "shader/ccGLStateCache.h"
#include "shader/CCShaderCache.h"
#include "driver/glesext.h"

CCTexture2D::CCTexture2D()
	: m_uPixelsWide(0)
	, m_uPixelsHigh(0)
	, m_uName(0)
	, m_fMaxS(0.0)
	, m_fMaxT(0.0)
	, m_pShaderProgram(NULL)
	, m_backColor_r(0)
	, m_backColor_b(0)
	, m_backColor_g(0)
	, m_backColor_a(0)
	, m_alpha(255)
{
}

CCTexture2D::~CCTexture2D()
{
    CC_SAFE_RELEASE(m_pShaderProgram);
    if(m_uName)
    {
        ccGLDeleteTexture(m_uName);
    }
}


unsigned int CCTexture2D::getPixelsWide()
{
    return m_uPixelsWide;
}

unsigned int CCTexture2D::getPixelsHigh()
{
    return m_uPixelsHigh;
}

GLuint CCTexture2D::getName()
{
	return m_uName;
}

CSize CCTexture2D::getContentSize()
{
    return m_tContentSize;
}


GLfloat CCTexture2D::getMaxS()
{
    return m_fMaxS;
}

void CCTexture2D::setMaxS(GLfloat maxS)
{
    m_fMaxS = maxS;
}

GLfloat CCTexture2D::getMaxT()
{
    return m_fMaxT;
}

void CCTexture2D::setMaxT(GLfloat maxT)
{
    m_fMaxT = maxT;
}

CCGLProgram* CCTexture2D::getShaderProgram(void)
{
    return m_pShaderProgram;
}

void CCTexture2D::setDefaultProgram()
{
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));
}

void CCTexture2D::setShaderProgram(CCGLProgram* pShaderProgram)
{
    CC_SAFE_RETAIN(pShaderProgram);
    CC_SAFE_RELEASE(m_pShaderProgram);
    m_pShaderProgram = pShaderProgram;
}

Uint8* ConvertSurfaceToRGBA(SDL_Surface* surf)
{
	int length = surf->w*surf->h;
	Uint8* retData = (Uint8*)malloc((length)*4);

	CAssert(surf->w*surf->format->BytesPerPixel == surf->pitch, "ConvertSurfaceToRGBA only support for width == pitch");
	if (surf->format->format == SDL_PIXELFORMAT_INDEX8)
	{
		Uint8* data = (Uint8*)surf->pixels;
		for (int i=surf->pitch;i<length;i++)
		{
			int posOfPal = data[i];
			retData[i*4] = surf->format->palette->colors[posOfPal].r;
			retData[i*4+1] = surf->format->palette->colors[posOfPal].g;
			retData[i*4+2] =surf->format->palette->colors[posOfPal].b;
			retData[i*4+3] = surf->format->palette->colors[posOfPal].a;
		}
	}else if(surf->format->format == SDL_PIXELFORMAT_ABGR8888)
	{
		Uint32* data = (Uint32*)surf->pixels;
		for (int i=0;i<length;i++)
		{
			retData[i*4] = (data[i]&surf->format->Rmask)>>surf->format->Rshift;
			retData[i*4+1] = (data[i]&surf->format->Gmask)>>surf->format->Gshift;
			retData[i*4+2] =(data[i]&surf->format->Bmask)>>surf->format->Bshift;
			retData[i*4+3] = (data[i]&surf->format->Amask)>>surf->format->Ashift;
		}
	}else if(surf->format->format == SDL_PIXELFORMAT_ARGB8888)
	{
		Uint32* data = (Uint32*)surf->pixels;
		for (int i=0;i<length;i++)
		{
			retData[i*4] = (data[i]&surf->format->Rmask)>>surf->format->Rshift;
			retData[i*4+1] = (data[i]&surf->format->Gmask)>>surf->format->Gshift;
			retData[i*4+2] =(data[i]&surf->format->Bmask)>>surf->format->Bshift;
			retData[i*4+3] = (data[i]&surf->format->Amask)>>surf->format->Ashift;
		}
	}else if(surf->format->format == SDL_PIXELFORMAT_RGBA8888)
	{
		SDL_memcpy(retData, surf->pixels, (length)*4);
	}else{
		const char* format = SDL_GetPixelFormatName(surf->format->format);
		PrintWaring("%s not supported for ConvertSurfaceToRGBA", format);
		CAssert(false," not supported for ConvertSurfaceToRGBA");
	}
	return retData;
}
bool CCTexture2D::initWithSurface(SDL_Surface* surf, bool isFreeSurface)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (m_uName==0)
	{
		glGenTextures(1, &m_uName);
	}
	ccGLBindTexture2D(m_uName);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	Uint8* data = ConvertSurfaceToRGBA(surf);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);

	m_tContentSize = CSize(surf->w, surf->h);
	m_uPixelsWide = surf->w;
	m_uPixelsHigh = surf->h;
	m_fMaxS = m_tContentSize.width / (float)(m_uPixelsWide);
	m_fMaxT = m_tContentSize.height / (float)(m_uPixelsHigh);

	if (isFreeSurface)
	{
		SDL_FreeSurface(surf);
	}
	
	setDefaultProgram();

	return true;
}

bool CCTexture2D::initWithData(const void *data, unsigned int pixelsWide, unsigned int pixelsHigh, const CSize& contentSize)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (m_uName==0)
	{
		glGenTextures(1, &m_uName);
	}
    ccGLBindTexture2D(m_uName);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    // Specify OpenGL texture image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixelsWide, pixelsHigh, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    m_tContentSize = contentSize;
    m_uPixelsWide = pixelsWide;
    m_uPixelsHigh = pixelsHigh;
    m_fMaxS = contentSize.width / (float)(pixelsWide);
    m_fMaxT = contentSize.height / (float)(pixelsHigh);

    setDefaultProgram();

    return true;
}

void CCTexture2D::SetBackColor(SDL_Color c)
{
	m_backColor_r = c.r;
	m_backColor_g = c.g;
	m_backColor_b = c.b;
	m_backColor_a = c.a;
}

void CCTexture2D::SetAlpha(Uint8 alpha)
{
	m_alpha = alpha;
}

void CCTexture2D::SetDrawInfo(DrawInfo& info)
{
	m_propinfo = info;
}

void CCTexture2D::drawTexture()
{
	CPoint point = ccp(m_propinfo.nScreenPosX, m_propinfo.nScreenPosY);

	if (m_propinfo.transMode == eTransTypeNone)
	{
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	}
	else if (m_propinfo.transMode == eTransTypeSub)
	{
		glBlendEquationSeparate(GL_FUNC_SUBTRACT, GL_FUNC_SUBTRACT);
	}
	else if (m_propinfo.transMode == eTransTypeAdd1)
	{
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendColor(1.0,1.0, 1.0, 0.5);
		glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
	}
	else if (m_propinfo.transMode == eTransTypeAdd)
	{
		glBlendColor(1,1, 1, 1);
		glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	}
	else if (m_propinfo.transMode == eTransTypeAddAlpha)
	{
		glBlendColor(m_propinfo.srcAlpha/256.0,m_propinfo.srcAlpha/256.0,m_propinfo.srcAlpha/256.0,m_propinfo.desAlpha/256.0);
		glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	}
    
	GLfloat    coordinates[] = {    
		0.0f,    0.0,
		m_fMaxS*m_propinfo.percentx,   0.0f,
		0.0f, m_fMaxT*m_propinfo.percenty,
		m_fMaxS*m_propinfo.percentx,m_fMaxT*m_propinfo.percenty };

    CHECK_GL_ERROR_DEBUG();
    GLfloat    width = (GLfloat)m_uPixelsWide * m_fMaxS*m_propinfo.nScaleX*m_propinfo.percentx,
        height = (GLfloat)m_uPixelsHigh * m_fMaxT*m_propinfo.nScaleY*m_propinfo.percenty;

    GLfloat        vertices[] = {    
        point.x,            point.y,
        width + point.x,    point.y,
        point.x,            height  + point.y,
        width + point.x,    height  + point.y};

	GLfloat tmp;
	if (m_propinfo.flip & SDL_FLIP_HORIZONTAL) {
		tmp = vertices[0];
		vertices[0] = vertices[4] = vertices[2];
		vertices[2] = vertices[6] = tmp;
	}
	if (m_propinfo.flip & SDL_FLIP_VERTICAL) {
		tmp = vertices[1];
		vertices[1] = vertices[3] = vertices[5];
		vertices[5] = vertices[7] = tmp;
	}
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords );
    CHECK_GL_ERROR_DEBUG();
    m_pShaderProgram->use();
	m_pShaderProgram->setUniformsForBuiltins();
	GLint u_isDrawBack = m_pShaderProgram->getUniformLocationForName(kCCUniformIsDrawBack_s);
	m_pShaderProgram->setUniformLocationWith1i(u_isDrawBack, (int)m_propinfo.bDrawBack);
	GLint u_BackColor = m_pShaderProgram->getUniformLocationForName(kCCUniformBackColor_s);
	m_pShaderProgram->setUniformLocationWith4f(u_BackColor, m_backColor_r/255.0, m_backColor_g/255.0, m_backColor_b/255.0, m_backColor_a/255.0);
	GLint u_alpha= m_pShaderProgram->getUniformLocationForName(kCCUniformAlpha_s);
	m_pShaderProgram->setUniformLocationWith1f(u_alpha, m_alpha/255.0);

    CHECK_GL_ERROR_DEBUG();
    ccGLBindTexture2D( m_uName );
    CHECK_GL_ERROR_DEBUG();
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
    CHECK_GL_ERROR_DEBUG();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	GLenum __error = glGetError(); 
	if(__error) { 
		PrintWaring("OpenGL error 0x%04X %04d in %s %s %d\n", __error,__error, __FILE__, __FUNCTION__, __LINE__); 
	} 
}
