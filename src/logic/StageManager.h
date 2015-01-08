/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __STAGE_MANAGER_H__
#define __STAGE_MANAGER_H__
#include "define.h"
#include "config/StageConfig.h"

class CStageManager
{
public:
	void LoadStage(const char* stageDef);
	//updates all interlal stuff of the player
	void UpdateStage();

	float GetLeft();
	float GetRight();

	Sint32 GetScreenPosX(Sint32 posX, float deltaX=1);
	Sint32 GetScreenPosY(Sint32 posY, float deltaY=1);
	void UpdateCameraByPlayerY(float y);
public:
	Prop_Get_Set(float, CameraPosX);
	Prop_Get_Set(float, CameraPosY);
	Prop_Get_Set(float, CameraPosYDelta);

	int GetInt(const char* name){return m_stageConfig->GetInt(name);};
	float GetFloat(const char* name){return m_stageConfig->GetFloat(name);};
	const char* GetChar(const char* name){return m_stageConfig->GetChar(name);};

private:
	CStageManager();
	~CStageManager();
	CStageConfig* m_stageConfig;


public:
	static CStageManager* GetInstance();
};
static CStageManager* g_pStageManager = NULL;

#endif // !__STAGE_MANAGER_H__
