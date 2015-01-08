/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "FontManager.h"
#include "cocos.h"

CFontManager::CFontManager()
	:m_texturePool(NULL)
{
	if ( TTF_Init() < 0 ) {
		PrintWaring("Couldn't initialize TTF: %s\n",SDL_GetError());
		SDL_assert(false);
	}
	m_texturePool = new CArray;
	m_font = NULL;
}

CFontManager::~CFontManager()
{
	if (m_font)
	{
		TTF_CloseFont(m_font);
	}
	m_texturePool->removeAllObjects();
	CC_SAFE_DELETE(m_texturePool);
}

void CFontManager::Destroy()
{
	CC_SAFE_DELETE(g_pFontManager);
}

CFontManager *CFontManager::GetInstance()
{
	if (g_pFontManager == NULL)
	{
		g_pFontManager = new CFontManager;
		g_pFontManager->OpenFont("font/arial.ttf", 14);
		g_pFontManager->SetFontColor(255, 255, 255, 255);
	}
	return g_pFontManager;
}


void CFontManager::OpenFont(const char* ttf, int fontSize)
{
	  m_font = TTF_OpenFontRW(SDL_RWFromFile(ttf, "rb"), 1, fontSize);
	  TTF_SetFontStyle(m_font, TTF_STYLE_NORMAL);
	  TTF_SetFontOutline(m_font, 0);
	  TTF_SetFontKerning(m_font, 1);
	  TTF_SetFontHinting(m_font, TTF_HINTING_NONE);
}

void CFontManager::SetFontStyle(int style)
{
	TTF_SetFontStyle(m_font, style);
}

void CFontManager::SetFontOutline(int outsize)
{
	TTF_SetFontOutline(m_font, outsize);
}
void CFontManager::SetFontColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A)
{
	m_fontColor.r = R;
	m_fontColor.g = G;
	m_fontColor.b = B;
	m_fontColor.a = A;
}

CCTexture2D* CFontManager::GetUnusedTexture()
{
	CObject* obj;
	CARRAY_FOREACH(m_texturePool, obj)
	{
		if (obj->isSingleReference())
		{
			obj->retain();
			obj->autorelease();
			return (CCTexture2D*)obj;
		}
	}
	CCTexture2D* texture = new CCTexture2D;
	texture->autorelease();
	m_texturePool->addObject(texture);
	return texture;
}
void CFontManager::ReleaseUnusedObj()
{
	CObject* obj;
	CARRAY_FOREACH_REVERSE(m_texturePool, obj)
	{
		if (obj->isSingleReference())
		{
			m_texturePool->removeObject(obj);
		}
	}
}

CCTexture2D* CFontManager::GetFontTextureFormat(const char *strText,...)
{
	char string[MAX_PATH];                  // Temporary string
	va_list ap;                // Pointer To List Of Arguments
	va_start(ap, strText);     // Parses The String For Variables
	vsprintf(string, strText, ap); // Converts Symbols To Actual Numbers
	va_end(ap);
	string[MAX_PATH - 1] = 0;
	SDL_Surface* surf =  GetFontSurFormat(string);

	SDL_Surface* convertedSur;
	if (surf->format->format == SDL_PIXELFORMAT_INDEX8)
	{
		convertedSur = SDL_ConvertSurfaceFormat(surf, TEXTURE_FORMAT, 0);
		SDL_FreeSurface(surf);
	}else{
		convertedSur = surf;
	}

	CCTexture2D* texture = GetUnusedTexture();
	texture->initWithSurface(convertedSur, true);
	return texture;
}


SDL_Surface* CFontManager::GetFontSurFormat(const char *strText,...)
{
	char string[MAX_PATH];                  // Temporary string
	va_list ap;                // Pointer To List Of Arguments
	va_start(ap, strText);     // Parses The String For Variables
	vsprintf(string, strText, ap); // Converts Symbols To Actual Numbers
	va_end(ap);
	string[MAX_PATH - 1] = 0;

	CAssert(m_font!=NULL, "openfont first");
	SDL_Surface* fontSur = TTF_RenderText_Solid(m_font, string, m_fontColor);
	return fontSur;
}

