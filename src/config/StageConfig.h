/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __STAGEMANAGER__H
#define __STAGEMANAGER__H

#include "structs.h"
#include "tokenizer.h"
#include "BaseConfig.h"
#include "SffManager.h"
#include "SceneAirConfig.h"

class CStageConfig: public CBaseConfig
{

public:
	CStageConfig();
	~CStageConfig();

	void ParseConfig(const char* path);

	CSffManager*		m_SffManager;
	CSffManager* GetSff(){return m_SffManager;};

	CSceneAirConfig*		m_airConfig;
	CSceneAirConfig* GetAirConfig(){return m_airConfig;};
};

#endif