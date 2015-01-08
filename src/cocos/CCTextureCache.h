/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __CCTEXTURE_CACHE_H__
#define __CCTEXTURE_CACHE_H__

#include "tool.h"
#include "CCTexture2D.h"
#include <string>

class  CCTextureCache : public CObject
{
protected:
	CDictionary* m_pTextures;
	CDictionary* m_pUITextures;

public:
    CCTextureCache();
    virtual ~CCTextureCache();
    static CCTextureCache * sharedTextureCache();
    static void purgeSharedTextureCache();

	void ClearTexture();
	void ClearUITexture();
	void ClearAfterTexture();

    CCTexture2D* addImage(const char* fileimage);
	Uint8* ConvertIndexToRGBA(Uint8* data,  int length, PaletteFormat* sharePallet);
	Uint8* DecodePcx(Uint8* PcxByte,PCXHEADER header);
	CCTexture2D* addSffImage(SFFSPRITE *lpSprite,PaletteFormat* sharePallet);
	CCTexture2D* GetAfterImage(SFFSPRITE *lpSprite,PaletteFormat* sharePallet);
	CCTexture2D* GetPngImage(const char* name);

};

#endif //__CCTEXTURE_CACHE_H__

