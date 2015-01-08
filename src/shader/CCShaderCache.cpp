/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "CCShaderCache.h"
#include "CCGLProgram.h"
#include "shader/ccShaders.h"

static CCShaderCache *_sharedShaderCache = 0;

CCShaderCache* CCShaderCache::sharedShaderCache()
{
    if (!_sharedShaderCache) {
        _sharedShaderCache = new CCShaderCache();
        if (!_sharedShaderCache->init())
        {
            CC_SAFE_DELETE(_sharedShaderCache);
        }
    }
    return _sharedShaderCache;
}

void CCShaderCache::purgeSharedShaderCache()
{
    CC_SAFE_RELEASE_NULL(_sharedShaderCache);
}

CCShaderCache::CCShaderCache()
: m_pPrograms(0)
{

}

CCShaderCache::~CCShaderCache()
{
    m_pPrograms->release();
}



bool CCShaderCache::init()
{
    m_pPrograms = new CDictionary();
    loadDefaultShaders();
    return true;
}

void CCShaderCache::loadDefaultShaders()
{
	CCGLProgram* p = new CCGLProgram(kCCShader_Position_uColor);
	loadDefaultShader(p, kCCShaderType_Position_uColor);
	m_pPrograms->setObject(p, kCCShader_Position_uColor);
	p->release();

	p = new CCGLProgram(kCCShader_PositionTexture_afterimage);
	loadDefaultShader(p, kCCShaderType_PositionTexture_afterimage);
	m_pPrograms->setObject(p, kCCShader_PositionTexture_afterimage);
	p->release();

	p = new CCGLProgram(kCCShader_PositionTexture);
	loadDefaultShader(p, kCCShaderType_PositionTexture);
	m_pPrograms->setObject(p, kCCShader_PositionTexture);
	p->release();

}



void CCShaderCache::loadDefaultShader(CCGLProgram *p, int type)
{
	switch (type) {

	case kCCShaderType_Position_uColor:
		p->initWithVertexShaderByteArray(ccPosition_uColor_vert, ccPosition_uColor_frag);    
		p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		break;

	case kCCShaderType_PositionTexture_afterimage:
		p->initWithVertexShaderByteArray(ccPositionTexture_afterimage_vert ,ccPositionTexture_afterimage_frag);
		p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		break;

	case kCCShaderType_PositionTexture:
		p->initWithVertexShaderByteArray(ccPositionTexture_vert ,ccPositionTexture_frag);
		p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		break;
	
	default:
		PrintWaring("cocos2d: %s:%d, error shader type", __FUNCTION__, __LINE__);
		return;
	}

	p->link();
	p->updateUniforms();

	CHECK_GL_ERROR_DEBUG();
}

CCGLProgram* CCShaderCache::programForKey(const char* key)
{
    return (CCGLProgram*)m_pPrograms->objectForKey(key);
}

void CCShaderCache::addProgram(CCGLProgram* program, const char* key)
{
    m_pPrograms->setObject(program, key);
}

