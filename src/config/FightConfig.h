/******************************************************************************* 
author : ljc
version : <1.0> 
------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __FIGHT_CONFIG__H
#define __FIGHT_CONFIG__H

#include "structs.h"
#include "BaseConfig.h"
#include "AirManager.h"
#include "tokenizer.h"
#include "SffManager.h"
#include "SndConfig.h"

class CFightConfig:public CBaseConfig
{

public:
	CFightConfig();
	~CFightConfig();


	bool ParseCfg(const char* file);

	CSffManager*		m_Sfffight;
	CSffManager* GetFightSff(){return m_Sfffight;};

	CSndConfig*			m_sndfight;
	CSndConfig* GetFightSnd(){return m_sndfight;};

	CSffManager*		m_SffFX;
	CSffManager* GetFXSff(){return m_SffFX;};

	CAirManager*		m_AirFX;
	CAirManager* GetFXAir(){return m_AirFX;};

	CSndConfig*			m_sndCommon;
	CSndConfig* GetCommonSnd(){return m_sndCommon;};

};

#endif