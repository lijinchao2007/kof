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
#include "config/SystemConfig.h"
#include <vector>

class CSysManager
{
	std::vector<ActionForPlay*> m_AnimVector;
	CAllocater* m_pAlloc;
public:
	//updates all interlal stuff of the player
	void ChangeToFight();
	void InitSelect();
	void RunSelect();

	void PrepareBackAnim(BG_ELEMENT* curElement);
	void UpdateBackAnim(ActionForPlay* act);
	void DrawBackAct(ActionForPlay* act);


public:
	int GetInt(const char* name){return m_sysConfig->GetInt(name);};
	float GetFloat(const char* name){return m_sysConfig->GetFloat(name);};
	const char* GetChar(const char* name){return m_sysConfig->GetChar(name);};

	CSysManager();
	~CSysManager();
	CSystemConfig* m_sysConfig;


public:
	static void Destroy();
	static CSysManager* GetInstance();
};
static CSysManager* g_pSysManager = NULL;

#endif // !__STAGE_MANAGER_H__
