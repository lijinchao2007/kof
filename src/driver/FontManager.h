/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __FONTMANAGER_H_
#define __FONTMANAGER_H_

#include <SDL_ttf.h>
#include "tool.h"
class CCTexture2D;


class CFontManager
{
	TTF_Font *m_font;
	SDL_Color m_fontColor;

	CArray* m_texturePool;
	
public:
	CFontManager();
	~CFontManager();
    
	void OpenFont(const char* ttf, int fontSize);

	void SetFontStyle(int style);
	void SetFontOutline(int outsize);
	void SetFontColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A);

	CCTexture2D* GetUnusedTexture();
	void ReleaseUnusedObj();
	CCTexture2D* GetFontTextureFormat(const char *strText,...);
	SDL_Surface* GetFontSurFormat(const char *strText,...);
public:
	static CFontManager *GetInstance();
	static void Destroy();
};

static CFontManager* g_pFontManager;

#endif