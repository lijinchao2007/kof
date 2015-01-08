/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include <SDL.h>
#include "VideoSystem.h"
#include "tool.h"
#include "config/ConfigManager.h"
#include "logic/GameTimer.h"
#include "FontManager.h"
#include "cocos/CCTextureCache.h"
#include "shader/CCShaderCache.h"
#include "shader/ccGLStateCache.h"

//Konstructor
CVideoSystem::CVideoSystem()
	:m_renderPoolArray(NULL)
	,m_array(NULL)
{

}
//Destructor
CVideoSystem::~CVideoSystem()
{
	PrintMessage("CVideoSystem::~CVideoSystem() Cleaning Up");
	CleanUp();
}

void CVideoSystem::CleanUp()
{
	if (m_array)
	{ 
		ccCArrayFree(m_array);
		m_array = NULL;
	}
	if (m_renderPoolArray)
	{ 
		ccCArrayFree(m_renderPoolArray);
		m_renderPoolArray = NULL;
	}
	m_pAlloc->FreeAllocater();
	SDL_VideoQuit();
}


bool CVideoSystem::InitSystem()
{
	PrintMessage("CVideoSystem::InitSystem()");
	m_pAlloc = CMemManager::GetInstance()->GetAllocater("CVideoSystem");
	m_renderInfoMemSize = 0;
	m_renderInfoSize = 0;
	//m_renderInfoPool = (RenderInfo*)m_pAlloc->Alloc(m_renderInfoMemSize*sizeof(RenderInfo));
	m_renderPoolArray = ccCArrayNew(0);
	m_array = ccCArrayNew(0);

	bool isStretch = CConfigManager::GetInstance()->GetInt("Video.IsStretch");
	Sint32 screenw = CConfigManager::GetInstance()->GetInt("Video.Width");
	Sint32 screenh = CConfigManager::GetInstance()->GetInt("Video.Height");
	Sint32 designW = CConfigManager::GetInstance()->GetInt("Config.GameWidth");
	Sint32 designH = CConfigManager::GetInstance()->GetInt("Config.GameHeight");
	SetUpGLES(screenw, screenh);

#ifdef __WIN32__
#else
	SDL_DisplayMode current;
	int should_be_zero = SDL_GetCurrentDisplayMode(0, &current);
	CAssert(should_be_zero == 0, "error for get mode");
	screenw = current.w;
	screenh = current.h;
#endif

	float scalex = screenw*1.0/designW;
	float scaley = screenh*1.0/designH;

	Sint32 startx, starty;
	float w,h;
	if (isStretch)
	{
		w = screenw;
		h = screenh;
		startx = starty = 0;
	}else{
		float scale = Min(scalex, scaley);
		w = scale*designW;
		h = scale*designH;
		if (scalex>scaley)
		{
			startx = (screenw - w)*0.5;
			starty = 0;
		}else{
			startx = 0;
			starty = (screenh - h)*0.5;
		}
		scaley = scalex = scale;
	}
	Common_SetScreenWidth(screenw);
	Common_SetScreenHeight(screenh);
	Common_SetDesiginHeight(designH);
	Common_SetDesiginWidth(designW);
	Common_SetStartPosX(startx);
	Common_SetStartPosY(starty);
	Common_SetScaleX(scalex);
	Common_SetScaleY(scaley);
	glViewport(startx, starty, w, h);


	return true;
}


//To clear the screen
void CVideoSystem::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//Copy the work surface to screen backbuffer and then flip
void CVideoSystem::Draw()
{
	SwapWindow();
}


void CVideoSystem::UnusedAllRenderInfo()
{
	m_renderInfoSize = 0;
}
RenderInfo* CVideoSystem::GetUnusedRenderInfo()
{
	if (m_renderInfoSize>=m_renderInfoMemSize)
	{
		/*PrintWaring("too much spr");
		return NULL;*/
		m_renderInfoMemSize += 30;
		RenderInfo* data = (RenderInfo*)m_pAlloc->Alloc(sizeof(RenderInfo)*30);
		for (int i=0;i<30;i++)
		{ 
			ccCArrayAppendValue(m_renderPoolArray, data+i);
		}
	}
	RenderInfo* retInfo = (RenderInfo*)m_renderPoolArray->arr[m_renderInfoSize];
	m_renderInfoSize++;
	return retInfo;
}
void CVideoSystem::AddRenderInfo(RenderInfo* info)
{
	void* obj;
	int index = 0;
	CCARRAYDATA_FOREACH(m_array, obj)
	{
		RenderInfo* curRenderInfo = (RenderInfo*)obj;
		if (curRenderInfo->sprpriority>info->sprpriority)
		{
			break;
		}
		index ++;
	}
	ccCArrayInsertValueAtIndex(m_array, info, index);
}


void CVideoSystem::DrawRect(Uint8 R, Uint8 G, Uint8 B,int x,int y,int width,int height, ENUM_DRAW_RECT_TYPE drawType, float srcAlpha, float desAlpha, Sint32 priority)
{ 
	RenderInfo* renderinfo = GetUnusedRenderInfo();
	if (renderinfo == NULL)
	{
		return;
	}
	renderinfo->sprpriority = priority;
	renderinfo->type = eEnumRenderRect;
	renderinfo->rectinfo.R = R;
	renderinfo->rectinfo.G = G;
	renderinfo->rectinfo.B = B;
	renderinfo->rectinfo.x = x;
	renderinfo->rectinfo.y = y;
	renderinfo->rectinfo.width = width;
	renderinfo->rectinfo.height = height;
	renderinfo->rectinfo.drawType = drawType;
	renderinfo->rectinfo.srcAlpha = srcAlpha;
	renderinfo->rectinfo.desAlpha = desAlpha;
	AddRenderInfo(renderinfo);
}

//Draw a string to video
void CVideoSystem::DrawText(int x,int y,const char *strText,...)
{

	char string[255];                  // Temporary string

	va_list ap;                // Pointer To List Of Arguments
	va_start(ap, strText);     // Parses The String For Variables
	vsprintf(string, strText, ap); // Converts Symbols To Actual Numbers
	va_end(ap);

	CFontManager::GetInstance()->SetFontStyle(TTF_STYLE_BOLD);
	CFontManager::GetInstance()->SetFontColor(255, 255, 0, 255);
	CCTexture2D* fonttext = CFontManager::GetInstance()->GetFontTextureFormat(string);
	DrawInfo info;
	info.nScreenPosX = x;
	info.nScreenPosY = y;
	this->DrawTexture(info, fonttext, SPR_PRIORITY_DEBUGINFO);
}

//Draw a string to video
void CVideoSystem::DrawTexture(DrawInfo& info, CCTexture2D* texture, Sint32 priority)
{
	RenderInfo* renderinfo = GetUnusedRenderInfo();
	if (renderinfo == NULL)
	{
		return;
	}
	renderinfo->sprpriority = priority;
	renderinfo->type = eEnumRenderTexture;
	renderinfo->drawinfo = info;
	renderinfo->texture = texture;
	AddRenderInfo(renderinfo);
}

void CVideoSystem::NormalBlt(DrawInfo& drawInfo, PalFXInfo* palFXinfo, Sint32 sprpriority)
{
	if (drawInfo.spr == NULL)
	{
		return;
	}
    RenderInfo* renderinfo = GetUnusedRenderInfo();
	if (renderinfo == NULL)
	{
		return;
	}
	renderinfo->sprpriority = sprpriority;
	renderinfo->type = eEnumRenderNormal;
	renderinfo->drawinfo = drawInfo;
	renderinfo->palfxInfo = palFXinfo;
	AddRenderInfo(renderinfo);
}


void CVideoSystem::BltAfterImage(AfterImageStack& afterimageStack, int curPos, int effectCount)
{
	DrawInfo drawInfo = afterimageStack.stack[curPos];
	if (drawInfo.spr == NULL)
	{
		return;
	}
	RenderInfo* renderinfo = GetUnusedRenderInfo();
	if (renderinfo == NULL)
	{
		return;
	}
	renderinfo->sprpriority = -6;
	renderinfo->type = eEnumRenderAfterImage;
	renderinfo->drawinfo = drawInfo;
	renderinfo->afterimagecofig = afterimageStack.config;
	renderinfo->afterImageEffectCount = effectCount;
	AddRenderInfo(renderinfo);
}



void CVideoSystem::RerderSpr(DrawInfo& drawInfo, PalFXInfo* palFXinfo)
{
    
	DrawInfo info = drawInfo;
	SFFSPRITE* lpSprite = info.spr;
	CAssert(lpSprite != NULL, "RerderSpr spr should existed");
	//calculate x and y value 
	// image's xy is the anchor,so the result is the position of the up-left point.it change to(airx-anchorx, airx-anchory)
	// 图片的起始点是左上，一般就把锚点设置在下面居中
	PaletteFormat *ColorTable=NULL;
	if (lpSprite->bSharePallet)
	{
		ColorTable  = drawInfo.pal;
	}else
	{
		ColorTable = lpSprite->ColorPallet;
	}
	SDL_assert(ColorTable!=NULL);
	CCTexture2D* img = CCTextureCache::sharedTextureCache()->addSffImage(lpSprite, ColorTable);

	CSize size = img->getContentSize();
	bool IsPosChangedByScale = CConfigManager::GetInstance()->GetInt("Rules.IsPosChangedByScale");
	if (IsPosChangedByScale)
	{
		if (info.flip&SDL_FLIP_HORIZONTAL)
		{
			info.nScreenPosX=drawInfo.nScreenPosX + lpSprite->x * info.nScaleX - size.width * info.nScaleX;
		}else{
			info.nScreenPosX=drawInfo.nScreenPosX - lpSprite->x * info.nScaleX ;
		}
		if (info.flip&SDL_FLIP_VERTICAL)
		{
			info.nScreenPosY=drawInfo.nScreenPosY + lpSprite->y* info.nScaleY - size.height * info.nScaleY;
		}else{
			info.nScreenPosY=drawInfo.nScreenPosY - lpSprite->y* info.nScaleY;
		}
	}else{
		if (info.flip&SDL_FLIP_HORIZONTAL)
		{
			info.nScreenPosX=drawInfo.nScreenPosX + lpSprite->x - size.width * info.nScaleX;
		}else{
			info.nScreenPosX=drawInfo.nScreenPosX - lpSprite->x ;
		}
		if (info.flip&SDL_FLIP_VERTICAL)
		{
			info.nScreenPosY=drawInfo.nScreenPosY + lpSprite->y - size.height * info.nScaleY;
		}else{
			info.nScreenPosY=drawInfo.nScreenPosY - lpSprite->y;
		}
	}

	
	img->SetDrawInfo(info);

	if (palFXinfo)
	{
		this->PalFX(img, palFXinfo);
	}else{
		img->drawTexture();
	}
	
}

void CVideoSystem::PalFX(CCTexture2D* img, PalFXInfo* palFXinfo)
{
	CCGLProgram* program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture_afterimage);
	img->setShaderProgram(program);
	program->use();

	GLint u_palinvertall = glGetUniformLocation(program->getProgram(), "u_palinvertall");
	float palinvertall = palFXinfo->palinvertall;
	program->setUniformLocationWith1f(u_palinvertall, palinvertall);
	CHECK_GL_ERROR_DEBUG();

	GLint u_palcolor = glGetUniformLocation(program->getProgram(), "u_palcolor");
	float palcolor = palFXinfo->palcolor;
	program->setUniformLocationWith1f(u_palcolor, palcolor);
	CHECK_GL_ERROR_DEBUG();

	GLint u_palbright = glGetUniformLocation(program->getProgram(), "u_palbright");
	float sinr=0,sing=0,sinb=0;
	if (palFXinfo->sinperiod !=0)
	{
		double value = sin(2 * M_PI * palFXinfo->nowtime / palFXinfo->sinperiod);
		sinr = palFXinfo->sinadd.r * value;
		sing = palFXinfo->sinadd.g * value;
		sinb = palFXinfo->sinadd.b * value;
	}
	
	program->setUniformLocationWith3f(u_palbright, palFXinfo->palbright.r+sinr, palFXinfo->palbright.g+sing, palFXinfo->palbright.b+sinb);

	GLint u_palcontrast = glGetUniformLocation(program->getProgram(), "u_palcontrast");
	program->setUniformLocationWith3f(u_palcontrast, palFXinfo->palcontrast.r, palFXinfo->palcontrast.g, palFXinfo->palcontrast.b);
	// use for afterimage
	GLint u_palpostbright = glGetUniformLocation(program->getProgram(), "u_palpostbright");
	program->setUniformLocationWith3f(u_palpostbright, 0.0, 0.0, 0.0);
	CHECK_GL_ERROR_DEBUG();

	// use for afterimage
	GLint u_effectCount = glGetUniformLocation(program->getProgram(), "u_effectCount");
	program->setUniformLocationWith1i(u_effectCount, 0);
	/*GLint u_paladd = glGetUniformLocation(program->getProgram(), "u_paladd");
	program->setUniformLocationWith3f(u_paladd, palFXinfo->paladd.r, palFXinfo->paladd.g, palFXinfo->paladd.b);
	GLint u_palmul = glGetUniformLocation(program->getProgram(), "u_palmul");
	program->setUniformLocationWith3f(u_palmul, palFXinfo->palmul.r, palFXinfo->palmul.g, palFXinfo->palmul.b);*/
	CHECK_GL_ERROR_DEBUG();

	img->drawTexture();
	img->setDefaultProgram();
}


void CVideoSystem::RenderAfterImage(DrawInfo& drawInfo, int effectCount, AfterImage* config)
{
	SFFSPRITE *lpSprite = drawInfo.spr;
	PaletteFormat *ColorTable=NULL;
	if (lpSprite->bSharePallet)
	{
		ColorTable  = drawInfo.pal;
	}else
	{
		ColorTable = lpSprite->ColorPallet;
	}

	CCTexture2D* img =  CCTextureCache::sharedTextureCache()->addSffImage(lpSprite, ColorTable);
	CSize size = img->getContentSize();
	DrawInfo info = drawInfo;

	if (info.flip&SDL_FLIP_HORIZONTAL)
	{
		info.nScreenPosX=drawInfo.nScreenPosX + lpSprite->x - size.width * info.nScaleX;
	}else{
		info.nScreenPosX=drawInfo.nScreenPosX - lpSprite->x;
	}
	if (info.flip&SDL_FLIP_VERTICAL)
	{
		info.nScreenPosY=drawInfo.nScreenPosY + lpSprite->y - size.height * info.nScaleY;
	}else{
		info.nScreenPosY=drawInfo.nScreenPosY - lpSprite->y;
	}

	info.transMode = config->trans;
	img->SetDrawInfo(info);
	CCGLProgram* program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture_afterimage);
	img->setShaderProgram(program);
	program->use();

	GLint u_palinvertall = glGetUniformLocation(program->getProgram(), "u_palinvertall");
	float palinvertall = config->palinvertall;
	program->setUniformLocationWith1f(u_palinvertall, palinvertall);
	CHECK_GL_ERROR_DEBUG();

	GLint u_palcolor = glGetUniformLocation(program->getProgram(), "u_palcolor");
	float palcolor = config->palcolor;
	program->setUniformLocationWith1f(u_palcolor, palcolor);
	CHECK_GL_ERROR_DEBUG();

	GLint u_palbright = glGetUniformLocation(program->getProgram(), "u_palbright");
	program->setUniformLocationWith3f(u_palbright, config->palbright.r, config->palbright.g, config->palbright.b);
	GLint u_palcontrast = glGetUniformLocation(program->getProgram(), "u_palcontrast");
	program->setUniformLocationWith3f(u_palcontrast, config->palcontrast.r, config->palcontrast.g, config->palcontrast.b);
	GLint u_palpostbright = glGetUniformLocation(program->getProgram(), "u_palpostbright");
	program->setUniformLocationWith3f(u_palpostbright, config->palpostbright.r, config->palpostbright.g, config->palpostbright.b);
	CHECK_GL_ERROR_DEBUG();

	GLint u_effectCount = glGetUniformLocation(program->getProgram(), "u_effectCount");
	program->setUniformLocationWith1i(u_effectCount, effectCount);
	GLint u_paladd = glGetUniformLocation(program->getProgram(), "u_paladd");
	program->setUniformLocationWith3f(u_paladd, config->paladd.r, config->paladd.g, config->paladd.b);
	GLint u_palmul = glGetUniformLocation(program->getProgram(), "u_palmul");
	program->setUniformLocationWith3f(u_palmul, config->palmul.r, config->palmul.g, config->palmul.b);
	CHECK_GL_ERROR_DEBUG();

	img->drawTexture();
	img->setDefaultProgram();
}




void CVideoSystem::RenderDrawLines(Uint8 R, Uint8 G, Uint8 B,Uint8 pointSize, GLfloat* vertices, int verCount)
{
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position);
	CHECK_GL_ERROR_DEBUG();
	CCGLProgram* program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor);
	program->use();
	program->setUniformsForBuiltins();
	CHECK_GL_ERROR_DEBUG();

	int nUniformColor = glGetUniformLocation(program->getProgram(), "u_color");
	GLfloat colors[4] = {R / 255.0f, G / 255.0f, B / 255.0f, 0.5f};
	program->setUniformLocationWith4fv(nUniformColor, colors, 1);
	int nUniformPointSize = glGetUniformLocation(program->getProgram(), "u_pointSize");
	program->setUniformLocationWith1f(nUniformPointSize, pointSize);

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
	CHECK_GL_ERROR_DEBUG();
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_LINES, 0, verCount);
}

void CVideoSystem::RenderDrawRect(Uint8 R, Uint8 G, Uint8 B,int x,int y,int width,int height, ENUM_DRAW_RECT_TYPE drawType, float srcAlpha, float desAlpha)
{ 
	if (drawType ==eDRAW_RECT_TYPE_FILLED)
	{
		ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position);
		CHECK_GL_ERROR_DEBUG();
		CCGLProgram* program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor);
		program->use();
		program->setUniformsForBuiltins();
		CHECK_GL_ERROR_DEBUG();

		int nUniformColor = glGetUniformLocation(program->getProgram(), "u_color");
		GLfloat colors[4] = {R / 255.0f, G / 255.0f, B / 255.0f, 1.0f};
		program->setUniformLocationWith4fv(nUniformColor, colors, 1);
		int nUniformPointSize = glGetUniformLocation(program->getProgram(), "u_pointSize");
		program->setUniformLocationWith1f(nUniformPointSize, 1.0);

		ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
		CHECK_GL_ERROR_DEBUG();

		GLfloat        vertices[] = {    
			x,            y,
			width + x,    y,
			x,            height  + y,
			width + x,    height  + y};

		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);

		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendColor(srcAlpha,srcAlpha, srcAlpha, desAlpha);
		glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	}else if (drawType == eDRAW_RECT_TYPE_LINE)
	{
		GLfloat        vertices[] = {    
			x,            y,
			width + x,    y,

			width + x,    y,
			width + x,            height  + y,

			width + x,    height  + y,
			x,            height  + y,

			x,            height  + y,
			x,    y
		};

		this->RenderDrawLines(R, G, B,1, vertices, 8);
	}
}

void CVideoSystem::Render()
{
	void* obj;
	CCARRAYDATA_FOREACH(m_array, obj)
	{
		RenderInfo* curRenderInfo = (RenderInfo*)obj;
		if (curRenderInfo->type == eEnumRenderAfterImage)
		{
			RenderAfterImage(curRenderInfo->drawinfo, curRenderInfo->afterImageEffectCount, curRenderInfo->afterimagecofig);
		}else if (curRenderInfo->type == eEnumRenderNormal)
		{
			RerderSpr(curRenderInfo->drawinfo, curRenderInfo->palfxInfo);
		}else if (curRenderInfo->type == eEnumRenderTexture)
		{
			curRenderInfo->texture->SetDrawInfo(curRenderInfo->drawinfo);
			curRenderInfo->texture->drawTexture();
		}else if (curRenderInfo->type == eEnumRenderRect)
		{
			RenderDrawRect(curRenderInfo->rectinfo.R, curRenderInfo->rectinfo.G, curRenderInfo->rectinfo.G, 
				curRenderInfo->rectinfo.x, curRenderInfo->rectinfo.y, curRenderInfo->rectinfo.width, curRenderInfo->rectinfo.height, 
				curRenderInfo->rectinfo.drawType, curRenderInfo->rectinfo.srcAlpha, curRenderInfo->rectinfo.desAlpha);
		}
	}
	UnusedAllRenderInfo();
	ccCArrayRemoveAllValues(m_array);
}