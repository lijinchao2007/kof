/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "game.h"
#include "logic/MemManager.h"
#include "tool.h"
#include "logic/GameTimer.h"
#include "logic/SystemManager.h"
#include "config/ConfigManager.h"
#include "driver/SDLManager.h"
#include "logic/engine.h"
#include "driver/Input.h"
#include "cocos/CCDirector.h"
#include "ui/GameLayer.h"
#include "ui/ChoosePlayerLayer.h"
#include "driver/TouchDispatcher.h"
#include "shader/CCShaderCache.h"
#include "driver/FontManager.h"

CGame* CGame::GetInstance()
{
	if ( pGameInstance == NULL )  //判断是否第一次调用
		pGameInstance = new CGame();
	return pGameInstance;
}

//Constructor
CGame::CGame()
{
	bError=false;
	bGame=true;
	bPause = false;
	nowTime=lastTime=0;
		nFpsCount=0;
}

//Destructor
CGame::~CGame()
{

}

//Init the hole game 
void CGame::InitGame()
{
	PrintMessage("Welcome to kof Version %s",VER);
	PrintMessage("CGame:Init SDL system");
	
	CMemManager::GetInstance()->InitManager();
	CGameTimer::GetInstance()->InitTimer();
	CConfigManager::GetInstance()->InitManager();

	if(!CSDLManager::GetInstance()->Init())
	{
		PrintMessage("CGame:SDL init failed");
		throw CError("init failed");
		bError=true;
	}
	//init the main engine
	SDL_initFramerate(&m_FPSmanager);
	SDL_setFramerate(&m_FPSmanager,60);

	// set touch dispatch
	CTouchDispatcher::GetInstance()->init();
	// set first scene
	CEngine::GetInstance()->SetPlayerName("Iori","Iori");
	CCScene* scene = CCScene::create();
	scene->addChild(GameLayer::create());
	CCDirector::sharedDirector()->runWithScene(scene);
}

//The main game Loop
void CGame::RunLogic()
{
	DEBUGBEGIN(RunLogic);
	DEBUGBEGIN(Clear);
	CSDLManager::GetInstance()->GetVideoSystem()->Clear();
	DEBUGEND(Clear);
	DEBUGBEGIN(mainLoop);
	CCDirector::sharedDirector()->mainLoop();
	DEBUGEND(mainLoop);
	DEBUGBEGIN(Draw);
	CSDLManager::GetInstance()->GetVideoSystem()->Draw();
	DEBUGEND(Draw);
	DEBUGEND(RunLogic);
}

//The main game Loop
void CGame::RunGame()
{
	PrintMessage("RunGame %d", bGame);
	while(bGame)
	{
		
		if (m_propIsDebugTime)
		{
			CGameTimer::GetInstance()->DebugTimeClear();
			m_propIsDebugTime = false;
			CGameTimer::GetInstance()->SetPropIsDebugTime(true);
		}

		CInput::GetInstance()->CheckSDL();
		
		if (!bPause)
		{
			RunLogic();
		}
		SDL_framerateDelay(&m_FPSmanager);
		CGameTimer::GetInstance()->SetPropIsDebugTime(false);
	}
	PrintMessage("bGame %d", bGame);

}

//Exit the game and cleans the memory and SDL
void CGame::Quit()
{
	PrintMessage("Quit game");

	CCTextureCache::sharedTextureCache()->purgeSharedTextureCache();
	CCShaderCache::sharedShaderCache()->purgeSharedShaderCache();

	CCDirector::sharedDirector()->purgeDirector();
	CSDLManager::GetInstance()->CleanSDL();

	CFontManager::Destroy();
	CSysManager::Destroy();
	CConfigManager::Destroy();
	CMemManager::Destroy();
	CGameTimer::Destroy();
	CTouchDispatcher::Destroy();
	CInput::Destroy();
	CC_SAFE_DELETE(pGameInstance);
}

