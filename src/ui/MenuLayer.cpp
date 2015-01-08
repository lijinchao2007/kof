/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "MenuLayer.h"
#include "ChoosePlayerLayer.h"
#include "cocos.h"
#include "config/ConfigManager.h"

CMenuLayer::CMenuLayer()
{
}

CMenuLayer::~CMenuLayer()
{
}

CMenuLayer *CMenuLayer::create()
{
	CMenuLayer *pRet = new CMenuLayer();
	if (pRet && pRet->init())
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

bool CMenuLayer::init()
{
	bool bRet = true;
	CUIBotton* btn2 = CUIBotton::create(CConfigManager::GetInstance()->GetChar("InputUI.ZIcon"));
	btn2->setPosition(ccp(200,0));
    btn2->SetString("choose player");
    btn2->SetTouchBeganCB(this, (SEL_CallFunc)&CMenuLayer::OnBtnClicked);
	this->addChild(btn2);
	return bRet;
}

void CMenuLayer::onEnter()
{
	CCLayer::onEnter();
}
void CMenuLayer::onExit()
{
	CCLayer::onExit();
}

void CMenuLayer::visit()
{
	CCLayer::visit();
}
void CMenuLayer::draw()
{
	CCLayer::draw();
}

void CMenuLayer::OnBtnClicked(CUIBotton* btn, CTouch* ptouch)
{
	CCScene* scene = CCScene::create();
    scene->addChild(ChoosePlayerLayer::create());
    CCDirector::sharedDirector()->replaceScene(scene);
}

