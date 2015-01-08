/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "JoyStickButton.h"
#include "driver/Input.h"
#include "logic/engine.h"
#include "driver/SDLManager.h"


CJoyStickButton::CJoyStickButton()
	:m_JoyImage(NULL)
	,m_lastDir(DIR_COUNT)
	,m_JoyChangeRange(1)
{
	setAnchorPoint(ccp(0.5, 0.5));
}

CJoyStickButton::~CJoyStickButton()
{
	//CC_SAFE_RELEASE_NULL(m_JoyImage);
}

void CJoyStickButton::setJoyChangeRange(float joyChangeRange)
{
	m_JoyChangeRange = joyChangeRange;
}

bool CJoyStickButton::InitJoy(const char* joyicon)
{
	m_JoyImage = CSprite::create(joyicon);
	if (m_JoyImage == NULL)
	{
		PrintWaring("InitJoy %s error", joyicon);
		return false;
	}
	m_JoyImage->setAnchorPoint(ccp(0.5, 0.5));
	m_JoyImage->setPosition(getScaledContentSize().width/2, getScaledContentSize().height/2);
	this->addChild(m_JoyImage);
	return true;
}

CJoyStickButton *CJoyStickButton::create(const char* path, const char* joyicon)
{
	CJoyStickButton *pRet = new CJoyStickButton();
	if (pRet && pRet->init(path))
	{
		pRet->InitJoy(joyicon);
		pRet->autorelease();
#ifdef __ANDROID__
		pRet->setContentSize(CSize(512, 512));
#endif
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

void CJoyStickButton::setScale(float scale)
{
	this->setScaleX(scale);
	this->setScaleY(scale);
}
void CJoyStickButton::setScaleX(float fScaleX)
{
	CUIBotton::setScaleX(fScaleX);
	m_JoyImage->setScaleX(fScaleX);
	m_JoyImage->setPosition(getScaledContentSize().width/2, getScaledContentSize().height/2);
}
void CJoyStickButton::setScaleY(float fScaleY)
{
	CUIBotton::setScaleY(fScaleY);
	m_JoyImage->setScaleY(fScaleY);
	m_JoyImage->setPosition(getScaledContentSize().width/2, getScaledContentSize().height/2);
}

void CJoyStickButton::setAnchorPoint(const CPoint& point)
{
	if( ! point.equals(m_obAnchorPoint))
	{
		m_obAnchorPoint = point;
		m_obAnchorPointInPoints = ccp(m_obContentSize.width * m_obAnchorPoint.x, m_obContentSize.height * m_obAnchorPoint.y );
	}
}

DIRECTION CJoyStickButton::GetDirection(CPoint pos)
{
	CRect rect = boundingBox();
	CPoint center = ccp(rect.getMidX(), rect.getMidY());
	/*if (ccpSub(pos, center).getLength()<30)
	{
		return DIR_COUNT;
	}*/
	
	m_lastNormalize = ccpSub(pos, center).normalize();
	float radians = ccpToAngle(ccpSub(pos, center));
	float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);

	if (degrees <= 22.5 && degrees >= -22.5) 
	{
		return DIR_RIGHT;
	}
	else if (degrees > 22.5 && degrees < 67.5)
	{
		return DIR_UP_RIGHT;
	}
	else if (degrees >= 67.5 && degrees <= 112.5)
	{
		return DIR_UP;
	}
	else if (degrees > 112.5 && degrees < 157.5)
	{
		return DIR_UP_LEFT;
	}
	else if (degrees >= 157.5 || degrees <= -157.5)
	{
		return DIR_LEFT;
	}
	else if (degrees < -22.5 && degrees > -67.5)
	{
		return DIR_DOWN_RIGHT;
	}
	else if (degrees <= -67.5 && degrees >= -112.5)
	{
		return DIR_DOWN;
	}
	else if (degrees < -112.5 && degrees > -157.5)
	{
		return DIR_DOWN_LEFT;
	}
	
	return DIR_COUNT;
}

void CJoyStickButton::SetDirection(DIRECTION dir, bool isSet)
{
	m_lastDir = dir;
	CPoint anchor;
	if (isSet)
	{
		CPoint anchor = ccp(0.5-m_lastNormalize.x*m_JoyChangeRange, 0.5-m_lastNormalize.y*m_JoyChangeRange);
		m_JoyImage->setAnchorPoint(anchor);
	}
	
	switch (dir)
	{
	case DIR_UP:
		CInput::GetInstance()->SetVectorKeyData(KEY_UP, isSet);
		anchor.x = 0.5;
		anchor.y = 0.5+m_JoyChangeRange;
		break;
	case DIR_DOWN:
		CInput::GetInstance()->SetVectorKeyData(KEY_DOWN, isSet);
		anchor.x = 0.5;
		anchor.y = 0.5-m_JoyChangeRange;
		break;
	case DIR_LEFT:
		CInput::GetInstance()->SetVectorKeyData(KEY_LEFT, isSet);
		anchor.x = 0.5+m_JoyChangeRange;
		anchor.y = 0.5;
		break;
	case DIR_RIGHT:
		CInput::GetInstance()->SetVectorKeyData(KEY_RIGHT, isSet);
		anchor.x = 0.5-m_JoyChangeRange;
		anchor.y = 0.5;
		break;
	case DIR_UP_LEFT:
		CInput::GetInstance()->SetVectorKeyData(KEY_UP, isSet);
		CInput::GetInstance()->SetVectorKeyData(KEY_LEFT, isSet);
		anchor.x = 0.5+m_JoyChangeRange;
		anchor.y = 0.5+m_JoyChangeRange;
		break;
	case DIR_UP_RIGHT:
		CInput::GetInstance()->SetVectorKeyData(KEY_UP, isSet);
		CInput::GetInstance()->SetVectorKeyData(KEY_RIGHT, isSet);
		anchor.x = 0.5-m_JoyChangeRange;
		anchor.y = 0.5+m_JoyChangeRange;
		break;
	case DIR_DOWN_LEFT:
		CInput::GetInstance()->SetVectorKeyData(KEY_DOWN, isSet);
		CInput::GetInstance()->SetVectorKeyData(KEY_LEFT, isSet);
		anchor.x = 0.5+m_JoyChangeRange;
		anchor.y = 0.5-m_JoyChangeRange;
		break;
	case DIR_DOWN_RIGHT:
		CInput::GetInstance()->SetVectorKeyData(KEY_DOWN, isSet);
		CInput::GetInstance()->SetVectorKeyData(KEY_RIGHT, isSet);
		anchor.x = 0.5-m_JoyChangeRange;
		anchor.y = 0.5-m_JoyChangeRange;
		break;
	case DIR_COUNT:
		anchor.x = 0.5;
		anchor.y = 0.5;
		break;
	default:
		break;
	}
	//m_JoyImage->setAnchorPoint(anchor);
}

bool CJoyStickButton::CTouchBegan(CTouch* pTouch)
{
	bool ret = CUIBotton::CTouchBegan(pTouch);
	if (ret)
	{
		SetDirection(GetDirection(pTouch->getLocation()), true);
	}
	return ret;
}

void CJoyStickButton::CTouchMoved(CTouch* pTouch)
{
	SetDirection(m_lastDir, false);
	SetDirection(GetDirection(pTouch->getLocation()), true);
}

void CJoyStickButton::CTouchEnded(CTouch* pTouch)
{
	SetDirection(m_lastDir, false);
	m_JoyImage->setAnchorPoint(ccp(0.5, 0.5));
}

void CJoyStickButton::CTouchCancelled(CTouch* pTouch)
{
	SetDirection(m_lastDir, false);
	m_JoyImage->setAnchorPoint(ccp(0.5, 0.5));
}

