/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __CONFIGMANAGER_H__
#define __CONFIGMANAGER_H__

#include "structs.h"
#include "CharsConfig.h"
#include "StageConfig.h"
#include "SystemConfig.h"

class CCharsConfig;

//This is the main game class 
class CConfigManager:public CBaseConfig
{
public:
	//Contructor Destructor
	CConfigManager();
	~CConfigManager();

	bool ParseCfg(const char* file);

	bool InitManager();
	bool InitKeyBoard();
	KEYBOARDDATA* GetKeyBoard(int playerid);
	// ∂¡»°≈‰÷√£¨”≥…‰∞¥º¸
	KEYBOARDDATA		m_keyDataP1;
	KEYBOARDDATA		m_keyDataP2;

	void FreeAllCharConfig();
	void FreeCharConfig(const char* keyName);
	CCharsConfig* GetCharConfig(const char* charname);
	
	void FreeAllStageConfig();
	void FreeStageConfig(const char* keyName);
	CStageConfig* GetStageConfig(const char* keyName);


	CSystemConfig* m_sysconfig;
	CSystemConfig* GetSystemConfig();
	void FreeSysConfig();
private:
	std::map<std::string, CCharsConfig*> m_CharsConfig;
	std::map<std::string, CStageConfig*> m_StageConfig;

public:
	static CConfigManager* GetInstance();
	static void Destroy();
};
static CConfigManager* g_pConfigManager;


#endif
