/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "UIBotton.h"
#include "driver/SDLManager.h"

CUIBotton::CUIBotton()
	:m_Touched(false)
	,m_Ojb1(NULL)
	,m_Ojb2(NULL)
	,m_Ojb3(NULL)
{
}

CUIBotton::~CUIBotton()
{
}


CUIBotton *CUIBotton::create(const char* path)
{
	CUIBotton *pRet = new CUIBotton();
	if (pRet && pRet->init(path))
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
CUIBotton *CUIBotton::create(SFFSPRITE* spr)
{
	CUIBotton *pRet = new CUIBotton();
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

bool CUIBotton::CTouchBegan(CTouch* pTouch)
{
	CRect rect = this->boundingBox();
	if (rect.containsPoint(pTouch->getLocation()))
	{
		m_Touched = true;
		if (m_Ojb1)
		{
			(m_Ojb1->*m_TouchBeganCB)(this, pTouch);
		}
		return true;
	}
	return false;
}
void CUIBotton::CTouchMoved(CTouch* pTouch)
{
	if (m_Ojb2)
	{
		(m_Ojb2->*m_TouchMovedCB)(this, pTouch);
	}
}
void CUIBotton::CTouchEnded(CTouch* pTouch)
{
	if (m_Ojb3)
	{
		(m_Ojb3->*m_TouchEndCB)(this, pTouch);
	}
	m_Touched = false;
}
void CUIBotton::CTouchCancelled(CTouch* pTouch)
{
	if (m_Ojb3)
	{
		(m_Ojb3->*m_TouchEndCB)(this, pTouch);
	}
	m_Touched = false;
}