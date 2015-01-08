/******************************************************************************* 
author : ljc
version : <1.0> 
------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __SELECT_CONFIG_H
#define __SELECT_CONFIG_H

#include "structs.h"
#include "BaseConfig.h"
#include "token.h"
#include "SffManager.h"
#include "SndConfig.h"
#include "FightConfig.h"
#include "SceneAirConfig.h"

class CSelectConfig:public CBaseConfig
{

public:
	CSelectConfig();
	~CSelectConfig();

	CAllocater* m_pAlloc;
	SelectRoleList m_selectList;
	char m_stageCount;
	char m_stageList[20][MAX_STRING_LENGTH];

	int m_arcade[11];
	int m_team[11];

	bool ParseCfg(const char* file);
	void ParseSelectLine(CToken &tok);

	bool LoadHeadSpr();
	bool LoadOneHeadSpr(int index);
};

#endif