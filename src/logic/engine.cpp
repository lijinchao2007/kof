/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "engine.h"
#include "GameTimer.h"
#include "config/ConfigManager.h"
#include "StageManager.h"
#include "tool.h"
#include "driver/SDLManager.h"
#include "game.h"
#include "cocos/CCTextureCache.h"
#include "driver/FontManager.h"


CEngine* CEngine::GetInstance()
{
	if ( pInstance == NULL )  //判断是否第一次调用
		pInstance = new CEngine();
	return pInstance;
}
CEngine::CEngine()
	:m_inited(false)
	,m_propSuperPauseTime(0)
	,m_propSuperPauseDarken(false)
	, m_gamelayer(NULL)
{
#ifdef __WIN32__
	m_uDebug = DEBUG_PLAYER1;  
#else
	m_uDebug = DEBUG_NONE;
#endif
}

void CEngine::Destroy()
{
	PrintMessage("Destroy CEngine");
	CC_SAFE_DELETE(pInstance);
}
CEngine::~CEngine()
{ 
	CC_SAFE_RELEASE(m_gamelayer);
	Mix_HaltChannel(-1);
	// release mem 
	// in player will release the allocate mem,delete exector
	m_player1->Destroy();
	CC_SAFE_DELETE(m_player1);
	m_player2->Destroy();
	CC_SAFE_DELETE(m_player2);

	// delete virtualMachine
	// release char config, in char config release, sff,air,statemgr will release.
	CConfigManager::GetInstance()->FreeAllCharConfig();
	// release stage config, release sff and statemgr;
	CConfigManager::GetInstance()->FreeAllStageConfig();
	// free sysconfig
	CCTextureCache::sharedTextureCache()->ClearTexture();
	CCTextureCache::sharedTextureCache()->ClearUITexture();
	CFontManager::GetInstance()->ReleaseUnusedObj();
}


/*
================================================================================
Init the engine clall the function once at the start
of OpenMugen
================================================================================
*/
void CEngine::InitEngine(GameLayer* layer)
{
	m_gamelayer = layer;
	m_gamelayer->retain();
	//init stage
	const char* stagePath = CConfigManager::GetInstance()->GetChar("Debug.StartStage");
	CStageManager::GetInstance()->LoadStage(stagePath);
	// also load systemconfig
	CConfigManager::GetInstance()->GetSystemConfig();

	//Set players to the VM
	m_player1 = new CFighter;
	m_player2 = new CFighter;
	//now set the VM to the player
	m_player1->Init(P1, m_player2);
	Sint32 p1startx = CStageManager::GetInstance()->GetInt("PlayerInfo.p1startx");
	Sint32 p1starty = CStageManager::GetInstance()->GetInt("PlayerInfo.p1starty");
	m_player1->SetPos(p1startx,p1starty);
	Sint32 p1facing = CStageManager::GetInstance()->GetInt("PlayerInfo.p1facing");
	if (p1facing == -1)
	{
		m_player1->FaceLeft();
	}

	m_player2->Init(P2, m_player1);
	Sint32 p2startx = CStageManager::GetInstance()->GetInt("PlayerInfo.p2startx");
	Sint32 p2starty = CStageManager::GetInstance()->GetInt("PlayerInfo.p2starty");
	m_player2->SetPos(p2startx,p2starty);
	Sint32 p2facing = CStageManager::GetInstance()->GetInt("PlayerInfo.p2facing");
	if (p2facing == -1)
	{
		m_player2->FaceLeft();
	}
	m_player1->LoadPlayer(m_PlayerName1, 1);
	m_player2->LoadPlayer(m_PlayerName2, 7);
	
	m_inited = true;
}

void CEngine::DrawEngine()
{
	if (!m_inited)
	{
		return;
	}

	// start draw
	CStageManager::GetInstance()->UpdateStage();

	arrayMakeObjectsPerformSelector(m_player1->m_Children, DrawPlayer, CPlayer*);
	arrayMakeObjectsPerformSelector(m_player2->m_Children, DrawPlayer, CPlayer*);
	m_player1->DrawPlayer();
	m_player2->DrawPlayer();

	if (m_uDebug == DEBUG_NONE)
	{
	}else if (m_uDebug == DEBUG_PLAYER1)
	{
		m_player1->Debug();
	}else if (m_uDebug == DEBUG_PLAYER2)
	{
		m_player2->Debug();
	}
	CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,0,"FPS:%5.2f",CGame::GetInstance()->GetPropFps());
	CSDLManager::GetInstance()->GetVideoSystem()->Render();
}

void CEngine::RunEngine()
{
	if (!m_inited)
	{
		return;
	}
	if (m_propSuperPauseTime>0)
	{
		m_propSuperPauseTime --;
		int w = Common_GetDesiginWidth();
		int h = Common_GetDesiginHeight();
		if (m_propSuperPauseDarken)
		{
			CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(0, 0, 0, 0, 0, w, h, eDRAW_RECT_TYPE_FILLED, 1, 0.3, SPR_PRIORITY_SUPER_TOP);
		}
		// draw front for super pause
		if (m_propSuperPauseTime == 0)
		{
			m_player1->SetPropIsSuperPause(false);
			m_player2->SetPropIsSuperPause(false);
		}
		// when superpause, only draw not run logic
		DrawEngine();
		return;
	}
	CGameTimer::GetInstance()->UpdateTimer();
	
	DEBUGBEGIN(BeforeUpDatePlayer);
	arrayMakeObjectsPerformSelector(m_player1->m_Children, BeforeUpDatePlayer, CPlayer*);
	arrayMakeObjectsPerformSelector(m_player2->m_Children, BeforeUpDatePlayer, CPlayer*);
	m_player1->BeforeUpDatePlayer();
	m_player2->BeforeUpDatePlayer();
    DEBUGEND(BeforeUpDatePlayer);

	DEBUGBEGIN(UpDatePlayerFirst);
	arrayMakeObjectsPerformSelector(m_player1->m_Children, UpDatePlayerFirst, CPlayer*);
	arrayMakeObjectsPerformSelector(m_player2->m_Children, UpDatePlayerFirst, CPlayer*);
	m_player1->UpDatePlayerFirst();
	m_player2->UpDatePlayerFirst();
    DEBUGEND(UpDatePlayerFirst);

	DEBUGBEGIN(UpDatePlayerSecond);
	arrayMakeObjectsPerformSelector(m_player1->m_Children, UpDatePlayerSecond, CPlayer*);
	arrayMakeObjectsPerformSelector(m_player2->m_Children, UpDatePlayerSecond, CPlayer*);
	m_player1->UpDatePlayerSecond();
	m_player2->UpDatePlayerSecond();
    DEBUGEND(UpDatePlayerSecond);

	DEBUGBEGIN(AfterUpDatePlayer);
	arrayMakeObjectsPerformSelector(m_player1->m_Children, AfterUpDatePlayer, CPlayer*);
	arrayMakeObjectsPerformSelector(m_player2->m_Children, AfterUpDatePlayer, CPlayer*);
	m_player1->AfterUpDatePlayer();
	m_player2->AfterUpDatePlayer();
	DEBUGEND(AfterUpDatePlayer);

	DEBUGBEGIN(DrawEngine);
	DrawEngine();
	DEBUGEND(DrawEngine);
}

/*
================================================================================
================================================================================
*/

void CEngine::ChangeAutoGuard()
{
	if (!m_inited)
	{
		return;
	}
	m_player1->ChangeAutoGuard();
	m_player2->ChangeAutoGuard();

	CSDLManager::GetInstance()->GetVideoSystem()->Clear();
	DrawEngine();
	CSDLManager::GetInstance()->GetVideoSystem()->Draw();
}
void CEngine::ChangeDrawType()
{
	if (!m_inited)
	{
		return;
	}
	m_player1->ChangeDrawType();
	m_player2->ChangeDrawType();

	CSDLManager::GetInstance()->GetVideoSystem()->Clear();
	DrawEngine();
	CSDLManager::GetInstance()->GetVideoSystem()->Draw();
}
void CEngine::ChangeDebug()
{
	if (!m_inited)
	{
		return;
	}
	m_uDebug = (m_uDebug+1)%DEBUG_PLAYER3;
	CSDLManager::GetInstance()->GetVideoSystem()->Clear();
	DrawEngine();
	CSDLManager::GetInstance()->GetVideoSystem()->Draw();
}
void CEngine::SetClsn()
{
	if (!m_inited)
	{
		return;
	}
	m_player1->SetClsn();
	m_player2->SetClsn();
	CSDLManager::GetInstance()->GetVideoSystem()->Clear();
	DrawEngine();
	CSDLManager::GetInstance()->GetVideoSystem()->Draw();
}

void CEngine::SetPlayer1AI(Uint8 aiLV)
{
	if (!m_inited)
	{
		return;
	}
	if (m_player1->GetPropAILevel() == 0)
	{
		m_player1->SetPropAILevel(aiLV);
	}else{
		m_player1->SetPropAILevel(0);
	}
}

void CEngine::SetPlayer2AI(Uint8 aiLV)
{
	if (!m_inited)
	{
		return;
	}
	if (m_player2->GetPropAILevel() == 0)
	{
		m_player2->SetPropAILevel(aiLV);
	}else{
		m_player2->SetPropAILevel(0);
	}
}

SFFSPRITE* CEngine::GetPLayerSpr(Sint32 id, Uint32 g, Uint32 i)
{
	if (id = P1)
	{
		return m_player1->GetConfig()->GetSff()->FindSprite(g,i);
	}
	if (id = P2)
	{
		return m_player2->GetConfig()->GetSff()->FindSprite(g,i);
	}
	return NULL;
}