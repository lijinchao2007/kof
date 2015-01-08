/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "Sprite.h"
#include "driver/SDLManager.h"
#include "driver/FontManager.h"
#include "CCTextureCache.h"

CSprite::CSprite()
	:m_image(NULL)
	,m_stringImage(NULL)
	,m_spr(NULL)
{
}

CSprite::~CSprite()
{
	if (m_image)
	{
		CC_SAFE_RELEASE_NULL(m_image);
	}
	if (m_stringImage)
	{
		CC_SAFE_RELEASE_NULL(m_stringImage);
	}
}

bool CSprite::init(const char* path)
{
	CCNode::init();
	m_image = CCTextureCache::sharedTextureCache()->GetPngImage(path);
	if (m_image == NULL)
	{
		PrintWaring("CSprite init %s error", path);
		return false;
	}
	m_image->retain();
	setContentSize(m_image->getContentSize());
	return true;
}

bool CSprite::init(SFFSPRITE* spr)
{
	CCNode::init();
	CAssert(spr->bSharePallet==false, "spr should be private colorPallet ");
	m_spr = spr;
	if (m_spr == NULL)
	{
		PrintWaring("CSprite init with SFFSPRITE error");
		return false;
	}
	setContentSize(CSize(spr->PcxHeader.widht, spr->PcxHeader.height));
	return true;
}

CSprite* CSprite::create(const char* png)
{
	CSprite *pRet = new CSprite();
	if (pRet && pRet->init(png))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

CSprite* CSprite::create(SFFSPRITE* spr)
{
	CSprite *pRet = new CSprite();
	if (pRet && pRet->init(spr))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

void CSprite::SetString(const char* str)
{
	if (str ==NULL)
	{
		return;
	}
	SDL_strlcpy(m_String, str, MAX_PATH);
	CFontManager::GetInstance()->SetFontColor(255, 255, 255,255);
	m_stringImage = CFontManager::GetInstance()->GetFontTextureFormat(str);
	m_stringImage->retain();
}


void CSprite::draw()
{
	if (m_bVisible)
	{
		CCNode::draw();
		CPoint scPos = convertToWorldSpace(CPointZero);
		if (m_image!=NULL)
		{
			DrawInfo info;
			info.nScreenPosX = scPos.x;
			info.nScreenPosY = scPos.y;
			info.transMode = eTransTypeNone;
			info.nScaleX = m_fScaleX;
			info.nScaleY = m_fScaleY;
			m_image->SetPropinfo(info);
			m_image->SetAlpha(m_alpha);
			m_image->drawTexture();
		}
		if (m_spr!=NULL)
		{
			
			DrawInfo info;
			info.spr = m_spr;
			info.nScreenPosX = scPos.x;
			info.nScreenPosY = scPos.y;
			info.transMode = eTransTypeNone;
			info.nScaleX = m_fScaleX;
			info.nScaleY = m_fScaleY;
			CSDLManager::GetInstance()->GetVideoSystem()->RerderSpr(info, NULL);
		}
		/*CSDLManager::GetInstance()->GetVideoSystem()->RenderDrawRect(222,0,0, info.nScreenPosX, info.nScreenPosY, \
			m_obContentSize.width*m_fScaleX, m_obContentSize.height*m_fScaleY, eDRAW_RECT_TYPE_LINE);*/

		if (m_stringImage)
		{
			DrawInfo strInfo;
			strInfo.nScreenPosX = scPos.x + m_obContentSize.width*0.5;
			strInfo.nScreenPosY = scPos.y+m_obContentSize.height*0.5;
			strInfo.nScaleX = m_fScaleX;
			strInfo.nScaleY = m_fScaleY;
			m_stringImage->SetPropinfo(strInfo);
			m_stringImage->SetAlpha(m_alpha);
			m_stringImage->drawTexture();
		}
	}
}