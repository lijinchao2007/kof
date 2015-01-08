/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __CCTEXTURE2D_H__
#define __CCTEXTURE2D_H__

#include <string>
#include "define.h"
#include "tool.h"
#include "ccTypes.h"
#include "shader/CCGLProgram.h"

class CCTexture2D : public CObject
{
public:
    CCTexture2D();
    virtual ~CCTexture2D();
	void setDefaultProgram();
	bool initWithSurface(SDL_Surface* surf, bool isFreeSurface);
    bool initWithData(const void* data, unsigned int pixelsWide, unsigned int pixelsHigh, const CSize& contentSize);

	void SetBackColor(SDL_Color c);
	void SetAlpha(Uint8 alpha);
	void SetDrawInfo(DrawInfo& info);
    void drawTexture();

	Prop_Get_Set(DrawInfo, info);

	
private:
    
	Uint8 m_backColor_r;
	Uint8 m_backColor_g;
	Uint8 m_backColor_b;
	Uint8 m_backColor_a;
	Uint8 m_alpha;
    /** width in pixels */
    CC_PROPERTY_READONLY(unsigned int, m_uPixelsWide, PixelsWide)
    /** height in pixels */
    CC_PROPERTY_READONLY(unsigned int, m_uPixelsHigh, PixelsHigh)

    /** texture name */
    CC_PROPERTY_READONLY(GLuint, m_uName, Name)

    /** texture max S */
    CC_PROPERTY(GLfloat, m_fMaxS, MaxS)
    /** texture max T */
    CC_PROPERTY(GLfloat, m_fMaxT, MaxT)
    /** content size */
    CC_PROPERTY_READONLY(CSize, m_tContentSize, ContentSize)

    CC_PROPERTY(CCGLProgram*, m_pShaderProgram, ShaderProgram);
};



#endif //__CCTEXTURE2D_H__

