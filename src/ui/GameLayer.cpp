/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "GameLayer.h"
#include "logic/engine.h"
#include "logic/MemManager.h"
#include "FightButton.h"
#include "JoyStickButton.h"
#include "config/ConfigManager.h"

#include "cocos.h"
#include "ui/MenuLayer.h"
#include "ui/ChoosePlayerLayer.h"
#include "logic/GameTimer.h"
#include "cocos/CCProgressTimer.h"

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}

GameLayer *GameLayer::create()
{
	GameLayer *pRet = new GameLayer();
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

bool GameLayer::init()
{
	bool bRet = true;
	// create button
	CFightButton* button = NULL;
	/*KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_BUTTON_A,
	KEY_BUTTON_B,
	KEY_BUTTON_C,
	KEY_BUTTON_X,
	KEY_BUTTON_Y,
	KEY_BUTTON_Z,
	KEY_BUTTON_START,*/

	float normalScale = CConfigManager::GetInstance()->GetFloat("InputUI.NormalBtnScale");
	float anchorX = CConfigManager::GetInstance()->GetFloat("InputUI.NormalAnchor.x");
	float anchorY = CConfigManager::GetInstance()->GetFloat("InputUI.NormalAnchor.y");

	for (int i = KEY_BUTTON_A; i < KEY_COUNT; i++)
	{
		button = new CFightButton;
		button->setTag(i);
		button->setScale(normalScale);
		button->setAnchorPoint(ccp(anchorX, anchorY));
		switch (i)
		{
		/*case KEY_UP:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.JumpIcon"));
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.JumpPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.JumpPos.y"));
			break;
		case KEY_DOWN:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.CrouchIcon"));
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.CrouchPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.CrouchPos.y"));
			break;
		case KEY_LEFT:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.LeftIcon"));
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.LeftPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.LeftPos.y"));
			break;
		case KEY_RIGHT:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.RightIcon"));
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.RightPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.RightPos.y"));
			break;*/
		case KEY_BUTTON_A:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.AIcon"));
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.APos.x"), CConfigManager::GetInstance()->GetInt("InputUI.APos.y"));
			break;
		case KEY_BUTTON_B:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.BIcon"));
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.BPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.BPos.y"));
			break;
		case KEY_BUTTON_C:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.CIcon"));
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.CPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.CPos.y"));
			break;
		case KEY_BUTTON_X:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.XIcon"));
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.XPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.XPos.y"));
			break;
		case KEY_BUTTON_Y:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.YIcon"));
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.YPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.YPos.y"));
			break;
		case KEY_BUTTON_Z:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.ZIcon"));
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.ZPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.ZPos.y"));
			break;
		case KEY_BUTTON_START:
			button->init(CConfigManager::GetInstance()->GetChar("InputUI.StartIcon"));
            button->SetString("Start");
			button->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.StartPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.StartPos.y"));
			break;
		default:
			break;
		}
		button->autorelease();
		button->SetAlpha(0x80);
		this->addChild(button);
	}

    
    CUIBotton* btn = CUIBotton::create(CConfigManager::GetInstance()->GetChar("InputUI.JumpIcon"));
	btn->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.choose.x"), CConfigManager::GetInstance()->GetInt("InputUI.choose.y"));
	btn->SetTouchBeganCB(this, (SEL_CallFunc)&GameLayer::BtnClicked);
	btn->setTag(BtnTypeChoose);
	btn->SetString("choose");
	btn->SetAlpha(0x40);
	this->addChild(btn);

	btn = CUIBotton::create(CConfigManager::GetInstance()->GetChar("InputUI.JumpIcon"));
	btn->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.debug.x"), CConfigManager::GetInstance()->GetInt("InputUI.debug.y"));
	btn->SetTouchBeganCB(this, (SEL_CallFunc)&GameLayer::BtnClicked);
	btn->setTag(BtnTypeDebug);
	btn->SetString("debug");
	btn->SetAlpha(0x40);
	this->addChild(btn);
	btn = CUIBotton::create(CConfigManager::GetInstance()->GetChar("InputUI.JumpIcon"));
	btn->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.clsn.x"), CConfigManager::GetInstance()->GetInt("InputUI.clsn.y"));
	btn->SetTouchBeganCB(this, (SEL_CallFunc)&GameLayer::BtnClicked);
	btn->setTag(BtnTypeDebugClsn);
	btn->SetString("clsn");
	btn->SetAlpha(0x40);
	this->addChild(btn);
	// add joystick
	const char* back = CConfigManager::GetInstance()->GetChar("InputUI.JoystickBack");
	const char* joy = CConfigManager::GetInstance()->GetChar("InputUI.JoystickIcon");
	CJoyStickButton *joyBtn = CJoyStickButton::create(back, joy);
	joyBtn->setPosition(CConfigManager::GetInstance()->GetInt("InputUI.JoystickPos.x"), CConfigManager::GetInstance()->GetInt("InputUI.JoystickPos.y"));
	float JoystickScale = CConfigManager::GetInstance()->GetFloat("InputUI.JoystickScale");
	anchorX = CConfigManager::GetInstance()->GetFloat("InputUI.JoystickAnchor.x");
	anchorY = CConfigManager::GetInstance()->GetFloat("InputUI.JoystickAnchor.y");
	float JoystickChangeRange = CConfigManager::GetInstance()->GetFloat("InputUI.JoystickChangeRange");
	joyBtn->setScale(JoystickScale);
	joyBtn->setAnchorPoint(ccp(anchorX, anchorY));
	joyBtn->setJoyChangeRange(JoystickChangeRange);
	joyBtn->SetAlpha(0x80);
	this->addChild(joyBtn);
	
	
	/*
	 *	life
	 */
	CSystemConfig* sysconfig = CConfigManager::GetInstance()->GetSystemConfig();
	CFightConfig* fightconf = sysconfig->GetFightConfig();

	float FightScale = CConfigManager::GetInstance()->GetFloat("Rules.FightScale");
	int p1posx = fightconf->GetInt("Lifebar.p1.pos.x")*FightScale;
	int p1posy = fightconf->GetInt("Lifebar.p1.pos.y")*FightScale;
	int p1bg1group = fightconf->GetInt("Lifebar.p1.bg1.spr.x");
	int p1bg1image = fightconf->GetInt("Lifebar.p1.bg1.spr.y");
	int p1midgroup = fightconf->GetInt("Lifebar.p1.mid.spr.x");
	int p1midimage = fightconf->GetInt("Lifebar.p1.mid.spr.y");
	int p1frontgroup = fightconf->GetInt("Lifebar.p1.front.spr.x");
	int p1frontimage = fightconf->GetInt("Lifebar.p1.front.spr.y");
	int p1rangestart = fightconf->GetInt("Lifebar.p1.range.x.x");
	int p1rangeend = fightconf->GetInt("Lifebar.p1.range.x.y");
	SFFSPRITE* p1bg = fightconf->GetFightSff()->FindSprite(p1bg1group, p1bg1image);
	SFFSPRITE* p1mid = fightconf->GetFightSff()->FindSprite(p1midgroup, p1midimage);
	SFFSPRITE* p1front = fightconf->GetFightSff()->FindSprite(p1frontgroup, p1frontimage);
	m_Pro1 = CCProgressTimer::create(p1bg, p1mid, p1front);
	m_Pro1->setPosition(ccp(p1posx, p1posy));
	m_Pro1->setScale(FightScale);
	//pro->setFrontPercentage(0.5);
	this->addChild(m_Pro1); 

	int p2posx = fightconf->GetInt("Lifebar.p2.pos.x")*FightScale;
	int p2posy = fightconf->GetInt("Lifebar.p2.pos.y")*FightScale;
	int p2bg1group = fightconf->GetInt("Lifebar.p2.bg1.spr.x");
	int p2bg1image = fightconf->GetInt("Lifebar.p2.bg1.spr.y");
	int p2midgroup = fightconf->GetInt("Lifebar.p2.mid.spr.x");
	int p2midimage = fightconf->GetInt("Lifebar.p2.mid.spr.y");
	int p2frontgroup = fightconf->GetInt("Lifebar.p2.front.spr.x");
	int p2frontimage = fightconf->GetInt("Lifebar.p2.front.spr.y");
	int p2rangestart = fightconf->GetInt("Lifebar.p2.range.x.x");
	int p2rangeend = fightconf->GetInt("Lifebar.p2.range.x.y");
	SFFSPRITE* p2bg = fightconf->GetFightSff()->FindSprite(p2bg1group, p2bg1image);
	SFFSPRITE* p2mid = fightconf->GetFightSff()->FindSprite(p2midgroup, p2midimage);
	SFFSPRITE* p2front = fightconf->GetFightSff()->FindSprite(p2frontgroup, p2frontimage);
	m_Pro2 = CCProgressTimer::create(p2bg, p2mid, p2front);
	m_Pro2->setPosition(ccp(p2posx, p2posy));
	m_Pro2->setScale(FightScale); 
	m_Pro2->setReverseProgress(true);
	//pro->setFrontPercentage(0.5);
	this->addChild(m_Pro2);

	/*
	 *	power
	 */
	int p1powerposx = fightconf->GetInt("Powerbar.p1.pos.x")*FightScale;
	int p1powerposy = fightconf->GetInt("Powerbar.p1.pos.y")*FightScale;
	int p1powerbg1group = fightconf->GetInt("Powerbar.p1.bg1.spr.x");
	int p1powerbg1image = fightconf->GetInt("Powerbar.p1.bg1.spr.y");
	int p1powermidgroup = fightconf->GetInt("Powerbar.p1.mid.spr.x");
	int p1powermidimage = fightconf->GetInt("Powerbar.p1.mid.spr.y");
	int p1powerfrontgroup = fightconf->GetInt("Powerbar.p1.front.spr.x");
	int p1powerfrontimage = fightconf->GetInt("Powerbar.p1.front.spr.y");
	int p1powerrangestart = fightconf->GetInt("Powerbar.p1.range.x.x");
	int p1powerrangeend = fightconf->GetInt("Powerbar.p1.range.x.y");
	SFFSPRITE* p1powerbg = fightconf->GetFightSff()->FindSprite(p1powerbg1group, p1powerbg1image);
	SFFSPRITE* p1powermid = fightconf->GetFightSff()->FindSprite(p1powermidgroup, p1powermidimage);
	SFFSPRITE* p1powerfront = fightconf->GetFightSff()->FindSprite(p1powerfrontgroup, p1powerfrontimage);
	m_ProPower1 = CCProgressTimer::create(p1powerbg, p1powermid, p1powerfront);
	m_ProPower1->setPosition(ccp(p1powerposx, p1powerposy));
	m_ProPower1->setScale(FightScale);
	m_ProPower1->setFrontPercentage(0.0);
	this->addChild(m_ProPower1); 

	int p2Powerposx = fightconf->GetInt("Powerbar.p2.pos.x")*FightScale;
	int p2Powerposy = fightconf->GetInt("Powerbar.p2.pos.y")*FightScale;
	int p2Powerbg1group = fightconf->GetInt("Powerbar.p2.bg1.spr.x");
	int p2Powerbg1image = fightconf->GetInt("Powerbar.p2.bg1.spr.y");
	int p2Powermidgroup = fightconf->GetInt("Powerbar.p2.mid.spr.x");
	int p2Powermidimage = fightconf->GetInt("Powerbar.p2.mid.spr.y");
	int p2Powerfrontgroup = fightconf->GetInt("Powerbar.p2.front.spr.x");
	int p2Powerfrontimage = fightconf->GetInt("Powerbar.p2.front.spr.y");
	int p2Powerrangestart = fightconf->GetInt("Powerbar.p2.range.x.x");
	int p2Powerrangeend = fightconf->GetInt("Powerbar.p2.range.x.y");
	SFFSPRITE* p2Powerbg = fightconf->GetFightSff()->FindSprite(p2Powerbg1group, p2Powerbg1image);
	SFFSPRITE* p2Powermid = fightconf->GetFightSff()->FindSprite(p2Powermidgroup, p2Powermidimage);
	SFFSPRITE* p2Powerfront = fightconf->GetFightSff()->FindSprite(p2Powerfrontgroup, p2Powerfrontimage);
	m_ProPower2 = CCProgressTimer::create(p2Powerbg, p2Powermid, p2Powerfront);
	m_ProPower2->setPosition(ccp(p2Powerposx, p2Powerposy));
	m_ProPower2->setScale(FightScale); 
	m_ProPower2->setReverseProgress(true);
	m_ProPower2->setFrontPercentage(0.0);
	this->addChild(m_ProPower2);

	return bRet;
}

void GameLayer::onEnter()
{
	CCLayer::onEnter();
	CEngine::GetInstance()->InitEngine(this);
	CMemManager::GetInstance()->GetMemUsage();
	
	/*
	 *	face
	 */
	CSystemConfig* sysconfig = CConfigManager::GetInstance()->GetSystemConfig();
	CFightConfig* fightconf = sysconfig->GetFightConfig();
	float FightScale = CConfigManager::GetInstance()->GetFloat("Rules.FightScale");

	int p1faceposx = fightconf->GetInt("Face.p1.pos.x")*FightScale;
	int p1faceposy = fightconf->GetInt("Face.p1.pos.y")*FightScale;
	int p1facebggroup = fightconf->GetInt("Face.p1.bg.spr.x");
	int p1facebgimage = fightconf->GetInt("Face.p1.bg.spr.y");
	int p1facefrontgroup = fightconf->GetInt("Face.p1.face.spr.x");
	int p1facefrontimage = fightconf->GetInt("Face.p1.face.spr.y");
	SFFSPRITE* p1facbg = fightconf->GetFightSff()->FindSprite(p1facebggroup, p1facebgimage);
	CSprite* bg = CSprite::create(p1facbg);
	bg->setPosition(ccp(p1faceposx, p1faceposy));
	bg->setScaleX(FightScale);
	bg->setScaleY(FightScale);
	this->addChild(bg); 

	SFFSPRITE* p1facespr = CEngine::GetInstance()->GetPLayerSpr(P1, p1facefrontgroup, p1facefrontimage);
	CSprite* p1face = CSprite::create(p1facespr);
	int p1faceoffx = fightconf->GetInt("Face.p1.face.offset.x")*FightScale;
	int p1faceoffy = fightconf->GetInt("Face.p1.face.offset.y")*FightScale;
	p1face->setPosition(ccp(p1faceposx+p1faceoffx, p1faceposy+p1faceoffy));
	p1face->setScaleX(FightScale);
	p1face->setScaleY(FightScale);
	p1face->setZOrder(1);
	this->addChild(p1face); 

	int p2faceposx = fightconf->GetInt("Face.p2.pos.x")*FightScale;
	int p2faceposy = fightconf->GetInt("Face.p2.pos.y")*FightScale;
	int p2facebggroup = fightconf->GetInt("Face.p2.bg.spr.x");
	int p2facebgimage = fightconf->GetInt("Face.p2.bg.spr.y");
	int p2facefrontgroup = fightconf->GetInt("Face.p2.face.spr.x");
	int p2facefrontimage = fightconf->GetInt("Face.p2.face.spr.y");
	SFFSPRITE* p2facbg = fightconf->GetFightSff()->FindSprite(p2facebggroup, p2facebgimage);
	//SFFSPRITE* p2face = fightconf->GetFightSff()->FindSprite(p2powerfrontgroup, p2powerfrontimage);
	bg = CSprite::create(p2facbg);
	bg->setPosition(ccp(p2faceposx, p2faceposy));
	bg->setScaleX(-FightScale);
	bg->setScaleY(FightScale);
	this->addChild(bg); 

	SFFSPRITE* p2facespr = CEngine::GetInstance()->GetPLayerSpr(P2, p2facefrontgroup, p2facefrontimage);
	CSprite* p2face = CSprite::create(p2facespr);
	int p2faceoffx = fightconf->GetInt("Face.p2.face.offset.x")*FightScale;
	int p2faceoffy = fightconf->GetInt("Face.p2.face.offset.y")*FightScale;
	p2face->setPosition(ccp(p2faceposx+p2faceoffx, p2faceposy+p2faceoffy));
	p2face->setScaleX(-FightScale);
	p2face->setScaleY(FightScale);
	p2face->setZOrder(1);
	this->addChild(p2face); 
}
void GameLayer::onExit()
{
	CCLayer::onExit();
	CEngine::GetInstance()->Destroy();
}

void GameLayer::visit()
{
	DEBUGBEGIN(RunEngine);
	CEngine::GetInstance()->RunEngine();
	DEBUGEND(RunEngine);

	// update ui
	DEBUGBEGIN(CCNode::visit);
	CCNode::visit();
	DEBUGEND(CCNode::visit);

}
void GameLayer::draw()
{
	CCLayer::draw();
}

void GameLayer::BtnClicked(CUIBotton* btn, CTouch* ptouch)
{

    if (btn->getTag()==BtnTypeChoose) {
		CCScene* scene = CCScene::create();
		scene->addChild(ChoosePlayerLayer::create());
		CCDirector::sharedDirector()->replaceScene(scene);
    }
	if (btn->getTag()==BtnTypeDebug) {
		/*CMemManager::GetInstance()->GetMemUsage();
		CGameTimer::GetInstance()->SetPropIsDebugTime(true);
		CImgManager::GetInstance()->GetInfo();
		CObjCountManager::sharedManager()->printInfo();
		*/
		CEngine::GetInstance()->ChangeDebug();
	}
	if (btn->getTag()==BtnTypeDebugClsn) {
		CEngine::GetInstance()->SetClsn();
	}
}


void GameLayer::OnLifeChanged(Sint32 id, Sint32 maxlife, Sint32 startlife, Sint32 changedlife)
{
	float per = (startlife+changedlife)*1.0/maxlife;
	per = Min(Max(0.0, per), 1.0);
	if (id==P1)
	{
		m_Pro1->setMidPercentage(per);
		m_Pro1->setFrontPercentage(per);
	}
	if (id==P2)
	{
		m_Pro2->setMidPercentage(per);
		m_Pro2->setFrontPercentage(per);
	}
}

void GameLayer::OnPowerChanged(Sint32 id, Sint32 max, Sint32 start, Sint32 changed)
{
	float per = (start+changed)*1.0/max;
	per = Min(Max(0.0, per), 1.0);
	if (id==P1)
	{
		m_ProPower1->setMidPercentage(per);
		m_ProPower1->setFrontPercentage(per);
	}
	if (id==P2)
	{
		m_ProPower2->setMidPercentage(per);
		m_ProPower2->setFrontPercentage(per);
	}
}