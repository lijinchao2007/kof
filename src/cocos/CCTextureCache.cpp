/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "CCTextureCache.h"
#include "CCTexture2D.h"
#include <list>
#include <SDL_image.h>
static CCTextureCache *g_sharedTextureCache = NULL;

CCTextureCache * CCTextureCache::sharedTextureCache()
{
    if (!g_sharedTextureCache)
    {
        g_sharedTextureCache = new CCTextureCache();
    }
    return g_sharedTextureCache;
}

CCTextureCache::CCTextureCache()
{
    CAssert(g_sharedTextureCache == NULL, "Attempted to allocate a second instance of a singleton.");
    
	glEnable(GL_BLEND);
	m_pTextures = new CDictionary();
	m_pUITextures = new CDictionary();
}

CCTextureCache::~CCTextureCache()
{
	CC_SAFE_RELEASE(m_pTextures);
	CC_SAFE_RELEASE(m_pUITextures);
}

void CCTextureCache::purgeSharedTextureCache()
{
    CC_SAFE_RELEASE_NULL(g_sharedTextureCache);
}

void CCTextureCache::ClearTexture()
{
	CDictElement* ele;
	CCDICT_FOREACH(m_pTextures, ele)
	{
		CObject* obj = ele->getObject();
		if (obj->isSingleReference())
		{
			m_pTextures->removeObjectForElememt(ele);
		}
	}
}
void CCTextureCache::ClearUITexture()
{
	CDictElement* ele;
	CCDICT_FOREACH(m_pUITextures, ele)
	{
		CObject* obj = ele->getObject();
		if (obj->isSingleReference())
		{
			m_pUITextures->removeObjectForElememt(ele);
		}
	}
}

CCTexture2D* CCTextureCache::GetPngImage(const char* name)
{
	PrintMessage("GetPngImage %s", name);
	std::string key(name);
	CCTexture2D *texture = (CCTexture2D*)m_pTextures->objectForKey(key);
	if (texture)
	{
		return texture;
	}
	SDL_ClearError();
	SDL_Surface* surface = IMG_LoadTyped_RW(SDL_RWFromFile(name,"rb"), 1, "png");
	if (surface == NULL)
	{
		PrintMessage("IMG_LoadTyped_RW error: %s", SDL_GetError());
		return NULL;
	}
	texture = new CCTexture2D;
	texture->initWithSurface(surface, true);
	m_pTextures->setObject(texture, key);
	texture->autorelease();
	return texture;
}

CCTexture2D* CCTextureCache::addSffImage(SFFSPRITE *lpSprite,PaletteFormat* sharePallet)
{
	//TODO:use other key, number is not right
	char keyStr[MAX_PATH];
	SDL_snprintf(keyStr, MAX_PATH, "%d_%d", lpSprite, sharePallet);
	std::string key(keyStr);
	CCTexture2D *texture = (CCTexture2D*)m_pTextures->objectForKey(key);
	if (texture)
	{
		return texture;
	}
	Uint32 width = lpSprite->PcxHeader.widht;
	Uint32 height = lpSprite->PcxHeader.height;
	Uint32 NPlane = lpSprite->PcxHeader.NPlanes;
	Uint8* pcxData  = DecodePcx(lpSprite->byPcxFile, lpSprite->PcxHeader);
	Uint8* rgbaData = ConvertIndexToRGBA(pcxData, width*NPlane*height, sharePallet);
	texture = new CCTexture2D;
	CSize contentSize = CSize(width, height);
	texture->initWithData(rgbaData, width, height, contentSize);
	SDL_Color back = sharePallet->color[0];
	texture->SetBackColor(back);
	m_pTextures->setObject(texture, key);
	free(pcxData);
	free(rgbaData);
	texture->autorelease();
	return texture;
}

Uint8* CCTextureCache::ConvertIndexToRGBA(Uint8* data, int length,  PaletteFormat* sharePallet)
{
	Uint8* retData = (Uint8*)malloc(sizeof(Uint8)*(length+1)*4);
	sharePallet->color[0].a = BACK_COLOR_ALPHA;
	for (int i=0;i<length;i++)
	{
		int posOfPal = data[i];
		retData[i*4] = sharePallet->color[posOfPal].r;
		retData[i*4+1] = sharePallet->color[posOfPal].g;
		retData[i*4+2] = sharePallet->color[posOfPal].b;
		retData[i*4+3] = sharePallet->color[posOfPal].a;
	}
	return retData;
}
//decodes one PCX file
Uint8* CCTextureCache::DecodePcx(Uint8* PcxByte,PCXHEADER header)
{
	Uint8* byImageBuffer=0;
	Uint8 BPP,byData;  
	u16 size;
	s16 x,y,widht;
	u32 Pos=0;

	u32 nCountByte,nTotalyByte,
		nHowManyBytes,nHowManyBlank;

	nTotalyByte=header.bytesPerLine*header.NPlanes;

	nHowManyBytes=0;
	nHowManyBlank=0;
	nCountByte=0;

	BPP=header.NPlanes*8; 

	//allocate memory
	byImageBuffer=(Uint8*)malloc(sizeof(Uint8)*(header.widht*header.NPlanes*header.height+1));
	widht=header.widht;

	if(widht<header.bytesPerLine * header.NPlanes)
		widht=header.bytesPerLine*header.NPlanes;

	//we do not support 24bit pcx images
	if(BPP>8)
	{

		PrintMessage("24Bit pcx file is not supproted");       
		return byImageBuffer;
	}

	size=0;
	y=0;
	x=0;
	for(y=0;y<header.height;y++)
	{
		x=0;
		while(x < widht)
		{

			byData=PcxByte[Pos++];

			if( (byData & 0xC0) == 0xC0 )
			{
				size = byData & 0x3F;
				byData=PcxByte[Pos++];

			}
			else
			{
				size=1;
			}

			while(size-- > 0)
			{
				if(x <= header.widht)
				{
					byImageBuffer[x + (y * header.widht)]=byData;

				}
				//this it to Skip blank data on PCX image wich are on the right side
				//TODO:OK? Skip two bytes
				if(x == widht && widht != header.widht)
				{
					nHowManyBlank=widht-header.widht;
					for(u32 i=0;i<nHowManyBlank;i++)
						Pos+=2;
				}
				x++;

			}

		} 

	}

	return byImageBuffer;    
}
