/******************************************************************************* 
author : ljc
version : <1.0> 
------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __SYSTEM_CONFIG__H
#define __SYSTEM_CONFIG__H

#include "structs.h"
#include "BaseConfig.h"
#include "tokenizer.h"
#include "SffManager.h"
#include "SndConfig.h"
#include "FightConfig.h"
#include "SceneAirConfig.h"
#include "SelectConfig.h"

class CSystemConfig:public CBaseConfig
{

public:
	CSystemConfig();
	~CSystemConfig();

	bool ParseCfg(const char* file);
	SFFSPRITE*  GetRoleSpr(const char* name);

	CSceneAirConfig*		m_airConfig;
	CSceneAirConfig* GetAirConfig(){return m_airConfig;};

	CSffManager*		m_SffManager;
	CSffManager* GetSff(){return m_SffManager;};

	CSndConfig*			m_sndConfig;
	CSndConfig* GetSnd(){return m_sndConfig;};

	CFightConfig*			m_fightConfig;
	CFightConfig* GetFightConfig(){return m_fightConfig;};

	CSelectConfig*			m_selectConfig;
	CSelectConfig* GetSelectConfig(){return m_selectConfig;};

};

#endif