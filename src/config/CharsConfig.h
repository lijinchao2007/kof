/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef _CHARSCONFIGMANAGER_H
#define _CHARSCONFIGMANAGER_H

#include "BaseConfig.h"
#include "CmdManager.h"
#include "StateManager.h"
#include "SffManager.h"
#include "AirManager.h"
#include "SndConfig.h"

class CCharsConfig:public CBaseConfig
{
public:
	CCharsConfig();
	~CCharsConfig();

	void ModifyMap(const char* key, const char* value);
	void LoadDefaultValue();
	bool ParseCharConfig(const char* charname);
	bool ParseDef(const char* file);

	CSffManager*		m_SffManager;
	CSffManager* GetSff(){return m_SffManager;};
	CSndConfig*			m_SndConfig;
	CSndConfig* GetSnd(){return m_SndConfig;};
	CAirManager*         m_AirManager;
	CAirManager* GetAir(){return m_AirManager;};
	CStateManager*       m_StateManager;  
	CStateManager*	GetState(){return m_StateManager;};
	CCmdManager*         m_CmdManager;
	CCmdManager*	GetCmd(){return m_CmdManager;};

};


#endif