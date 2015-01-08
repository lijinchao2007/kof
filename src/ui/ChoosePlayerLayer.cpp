/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "ChoosePlayerLayer.h"
#include "GameLayer.h"
#include "MenuLayer.h"
#include "cocos.h"
#include "config/ConfigManager.h"
#include "logic/engine.h"
#include "logic/SystemManager.h"

ChoosePlayerLayer::ChoosePlayerLayer()
	:m_state(0)
{
}

ChoosePlayerLayer::~ChoosePlayerLayer()
{
}

ChoosePlayerLayer *ChoosePlayerLayer::create()
{
	ChoosePlayerLayer *pRet = new ChoosePlayerLayer();
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

bool ChoosePlayerLayer::init()
{
	bool bRet = true;
	/*int playerCount = CConfigManager::GetInstance()->GetInt("PlayerList.PlayerCount");
	for (int i= 1;i<=playerCount;i++)
	{
		char playerKey[MAX_PATH];
		SDL_snprintf(playerKey, MAX_PATH, "PlayerList.Player%d", i);
		const char* playerName = CConfigManager::GetInstance()->GetChar(playerKey);

		CUIBotton* btn1 = CUIBotton::create(CConfigManager::GetInstance()->GetChar("PlayerList.selectBack"));
		SDL_snprintf(playerKey, MAX_PATH, "PlayerList.PlayerPos%d.x", i);
		float posx = CConfigManager::GetInstance()->GetFloat(playerKey);
		SDL_snprintf(playerKey, MAX_PATH, "PlayerList.PlayerPos%d.y", i);
		float posy = CConfigManager::GetInstance()->GetFloat(playerKey);
		btn1->setPosition(ccp(posx, posy));
		btn1->SetTouchBeganCB(this, (SEL_CallFunc)&ChoosePlayerLayer::ChooseCB);
		btn1->setTag(i-1+BtnTypeMinPlayer);
		btn1->SetString(playerName);
		this->addChild(btn1);
	}


	m_start = CUIBotton::create(CConfigManager::GetInstance()->GetChar("InputUI.JumpIcon"));
	m_start->setPosition(ccp(400, 500));
	m_start->SetTouchBeganCB(this, (SEL_CallFunc)&ChoosePlayerLayer::ChooseCB);
	m_start->setTag(BtnTypeStart);
	m_start->SetString("start");
	this->addChild(m_start);*/

   /* CUIBotton* btn = CUIBotton::create(CConfigManager::GetInstance()->GetChar("InputUI.JumpIcon"));
	btn->setPosition(ccp(0, 500));
	btn->SetTouchBeganCB(this, (SEL_CallFunc)&ChoosePlayerLayer::ChooseCB);
	btn->setTag(BtnTypeMenu);
	btn->SetString("menu");
	this->addChild(btn);*/

	CSystemConfig* sysconfig = CConfigManager::GetInstance()->GetSystemConfig();
	CSelectConfig* selectconfig = sysconfig->GetSelectConfig();

	float ChooseSceneScale = CConfigManager::GetInstance()->GetFloat("Rules.ChooseSceneScale");

	int rows = sysconfig->GetInt("SelectInfo.rows");
	int columns = sysconfig->GetInt("SelectInfo.columns");
	float posx = sysconfig->GetFloat("SelectInfo.pos.x")*ChooseSceneScale;
	float posy = sysconfig->GetFloat("SelectInfo.pos.y")*ChooseSceneScale;
	float sizex = sysconfig->GetFloat("SelectInfo.cell.size.x")*ChooseSceneScale;
	float sizey = sysconfig->GetFloat("SelectInfo.cell.size.y")*ChooseSceneScale;
	float space = sysconfig->GetFloat("SelectInfo.cell.spacing")*ChooseSceneScale;
	int bggroup = sysconfig->GetInt("SelectInfo.cell.bg.spr.x");
	int bgimage = sysconfig->GetInt("SelectInfo.cell.bg.spr.y");
	int ranomgoup = sysconfig->GetInt("SelectInfo.cell.random.spr.x");
	int ranomdimage = sysconfig->GetInt("SelectInfo.cell.random.spr.y");

	SFFSPRITE* backspr = sysconfig->GetSff()->FindSprite(bggroup, bgimage);
	SFFSPRITE* randomspr = sysconfig->GetSff()->FindSprite(ranomgoup, ranomdimage);
	CAssert(backspr!=NULL&&randomspr!=NULL, "bg and random spr shoud existed");

	float p1namex = sysconfig->GetFloat("SelectInfo.p1.name.offset.x")*ChooseSceneScale;
	float p1namey = sysconfig->GetFloat("SelectInfo.p1.name.offset.y")*ChooseSceneScale;
	float p2namex = sysconfig->GetFloat("SelectInfo.p2.name.offset.x")*ChooseSceneScale;
	float p2namey = sysconfig->GetFloat("SelectInfo.p2.name.offset.y")*ChooseSceneScale;
	SFFSPRITE* nullspr = NULL;
	m_playerOne = CSprite::create(backspr);
	m_playerOne->setPosition(ccp(p1namex, p1namey));
	this->addChild(m_playerOne);
	m_playerTwo = CSprite::create(backspr);
	m_playerTwo->setPosition(ccp(p2namex, p2namey));
	this->addChild(m_playerTwo);

	selectconfig->LoadHeadSpr();
	for (int r=0;r<rows;r++)
	{
		for (int c=0;c<columns;c++)
		{
			int index = c+r*columns;
			SelectRoleInfo* curRoleInfo = selectconfig->m_selectList.rolelist+index;
			char* name = curRoleInfo->name;
			SFFSPRITE* spr = NULL;
			if (SDL_strcasecmp("randomselect", name) == 0)
			{
				spr = randomspr;
			}else{
				
				if (curRoleInfo->isPhotoLoaded)
				{
					spr = &curRoleInfo->headphoto;
				}
			}
			if (spr == NULL)
			{
				continue;
			}

			// back
			CSprite* sprite = CSprite::create(backspr);
			sprite->setPosition(ccp(posx+c*sizex+c*space, posy+r*sizey+r*space));
			CSize size = sprite->getContentSize();
			sprite->setScaleX(sizex/size.width);
			sprite->setScaleY(sizey/size.height);
			sprite->setZOrder(0);
			this->addChild(sprite);
			float box = 6.0;
			CUIBotton* btn = CUIBotton::create(spr);
			btn->setPosition(ccp(posx+c*sizex+c*space, posy+r*sizey+r*space));
			size = btn->getContentSize();
			btn->setScaleX((sizex-box)/size.width);
			btn->setScaleY((sizey-box)/size.height);
			btn->SetTouchBeganCB(this, (SEL_CallFunc)&ChoosePlayerLayer::ChooseCB);
			btn->setTag(BtnTypeMinPlayer+index);
			btn->SetString(name);
			btn->setZOrder(1);
			this->addChild(btn);
		}
	}
	
	return bRet;
}

void ChoosePlayerLayer::onEnter()
{
	CSysManager::GetInstance()->InitSelect();
	CMemManager::GetInstance()->GetMemUsage();
	CCLayer::onEnter();
}
void ChoosePlayerLayer::onExit()
{
	CCLayer::onExit();
}

void ChoosePlayerLayer::visit()
{
	CSysManager::GetInstance()->RunSelect();
	CCLayer::visit();
}
void ChoosePlayerLayer::draw()
{
	CCLayer::draw();
}

void ChoosePlayerLayer::ChooseCB(CUIBotton* btn, CTouch* ptouchs)
{
	int tag = btn->getTag();
    if (tag == BtnTypeMenu) {
        CCScene* scene = CCScene::create();
		scene->addChild(CMenuLayer::create());
		CCDirector::sharedDirector()->replaceScene(scene);
        return;
    }
	if (m_state == 0)
	{
		if (tag<BtnTypeMinPlayer)
		{
			return;
		}
		
		m_state ++;
		m_playerOne->SetString(btn->GetString());
		m_playerOne->setTag(tag);
	}else if (m_state == 1)
	{
		if (tag==m_playerOne->getTag())
		{
			m_state ++;
		}else{
			m_playerOne->SetString(btn->GetString());
			m_playerOne->setTag(tag);
		}
	}else if (m_state == 2)
	{
		if (tag<BtnTypeMinPlayer)
		{
			return;
		}
		m_state ++;
		m_playerTwo->SetString(btn->GetString());
	}else if (m_state == 3)
	{
		if (tag!=m_playerTwo->getTag())
		{
			m_playerTwo->SetString(btn->GetString());
			m_playerTwo->setTag(tag);
			return;
		}
		m_state++;
		PrintMessage("start");
		const char* str1 = m_playerOne->GetString();
		const char* str2 = m_playerTwo->GetString();
		CEngine::GetInstance()->SetPlayerName(str1,str2);
		CCScene* scene = CCScene::create();
		scene->addChild(GameLayer::create());
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	
	
}