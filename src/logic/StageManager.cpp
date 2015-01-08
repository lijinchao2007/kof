/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "StageManager.h"
#include "GameTimer.h"
#include "config/ConfigManager.h"
#include "config/StageConfig.h"
#include "driver/SDLManager.h"

CStageManager* CStageManager::GetInstance()
{
	if (g_pStageManager == NULL)
	{
		g_pStageManager = new CStageManager();
	}
	return g_pStageManager;
}

CStageManager::CStageManager()
{

}

CStageManager::~CStageManager()
{
}

void CStageManager::LoadStage(const char* stageDef)
{
	m_stageConfig = CConfigManager::GetInstance()->GetStageConfig(stageDef);
	m_propCameraPosX = (float)m_stageConfig->GetInt("Camera.startx");
	m_propCameraPosY = (float)m_stageConfig->GetInt("Camera.starty");
	m_propCameraPosYDelta = 0;

	// player music 
	const char* music = m_stageConfig->GetChar("Music.bgmusic");
	CSDLManager::GetInstance()->GetAudioSystem()->PlayMusic(music);
	int volume = m_stageConfig->GetInt("Music.bgvolume");
	float v = volume/255.0;
	Mix_VolumeMusic(MIX_MAX_VOLUME * v);
}


//updates all interlal stuff of the player
void CStageManager::UpdateStage()
{
	Sint32 halfWidth = Common_GetDesiginHalfWidth();
	BG_DEF* bgDef = m_stageConfig->GetAirConfig()->m_BgDef;
	BG_ELEMENT* curElement = bgDef->elements;
	int i=0;
	while (i<bgDef->elementSize)
	{
		if (curElement->type == BG_TYPE_NORMAL)
		{
			Uint32 nGroupNumber = curElement->GroubNumber;
			Uint32 nImageNumber = curElement->ImageNumber;
			SFFSPRITE *spr =m_stageConfig->GetSff()->FindSprite(nGroupNumber,nImageNumber);
			if(spr==NULL)
				continue;
			Sint32 scX = curElement->nStartX + halfWidth;
			Sint32 scY = curElement->nStartY;
			Sint32 scPosX = GetScreenPosX(scX, curElement->fDeltaX);
			Sint32 scPosY = GetScreenPosY(scY, curElement->fDeltaY);
			DrawInfo info;
			info.spr = spr;
			info.pal = NULL;
			info.nScreenPosX = scPosX;
			info.nScreenPosY = scPosY;
			info.bDrawBack = curElement->bMask;

			int sprProi = 0;
			if (curElement->nLayerNo == 0)
			{
				sprProi = SPR_PRIORITY_STAGE_BOTTOM;
			}else{
				sprProi = SPR_PRIORITY_STAGE_TOP;
			}
			CSDLManager::GetInstance()->GetVideoSystem()->NormalBlt(info, NULL, sprProi);
		}

		i++;
		curElement++;
	}

}


float CStageManager::GetLeft()
{
	return  m_propCameraPosX - Common_GetDesiginWidth()*0.5;
}

float CStageManager::GetRight()
{
	return m_propCameraPosX+Common_GetDesiginWidth()*0.5 ;
}

//updates all interlal stuff of the player
Sint32 CStageManager::GetScreenPosX(Sint32 scX, float deltaX)
{
	return (Sint32)(scX - (this->m_propCameraPosX)*deltaX);
}

//updates all interlal stuff of the player
Sint32 CStageManager::GetScreenPosY(Sint32 scY, float deltaY)
{
	return (Sint32)(scY- (this->m_propCameraPosY+this->m_propCameraPosYDelta)*deltaY);
}

void CStageManager::UpdateCameraByPlayerY(float y)
{
	Sint32 floortension = this->GetInt("Camera.floortension");
	if (y >= floortension)
	{
		float verticalfollow = this->GetFloat("Camera.verticalfollow");
		float deltaY = (floortension- y) * verticalfollow;
		Sint32 boundhigh = this->GetInt("Camera.boundhigh");
		if (deltaY < boundhigh)
		{
			deltaY = boundhigh;
		}
		this->m_propCameraPosYDelta += deltaY;
	}
}