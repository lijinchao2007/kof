/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __GAMETIMER__H
#define __GAMETIMER__H
#include <map>
#include <string>
#include "define.h"

class CGameTimer
{
	CGameTimer();
	~CGameTimer();
      
public:
	double m_MSPerCount;
	std::string m_logStr;
	Uint32   nGameTime;
	bool  bPause;
	Sint32 nLayer;
	std::map<const char*, double> m_MapDebugTime;

	void Pause(){bPause=true;}
	void Resume(){bPause=false;}

	Prop_Get_Set(bool, IsDebugTime);
public:
    void InitTimer();
    void UpdateTimer();
    Uint32  GetGameTime();
	void DebugTimeBegin(const char* name);
	void DebugTimeEnd(const char* name);
	void DebugTimeClear();

	static CGameTimer* GetInstance();
	static void Destroy();
};

static CGameTimer* g_pGameTimer = NULL;

#endif
