/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __STATEMANAGER_H_
#define __STATEMANAGER_H_

#include "define.h"
#include "logic/MemManager.h"


class CStateManager
{

private:
	float m_MugenScale;
	OpElement pInst[200];
	u16 nCurrInst;
	OpElement pStackInst[200];
	u16 nTop;
	int intStack[200];
	u16 nIntTop;
	PLSTATEDEF *lpStateDefList;
	u16        nTotalStateDef;
	u16        nTotalStateDefSize;
	u16        nTotalState;
	u16        nTotalStateSize;
	u16        nCurrTrigger;

	u16 nCurrParamInst;
	u16 nCurrParam;

	bool bParam;


    CAllocater     *m_pAlloc;
	char m_allocName[MAX_PATH];
public:
	//Konstructor and Destructor
	CStateManager();
	~CStateManager();
	void SetAlloc(const char *alloName);

	void AddStateDef(s32 nStateDefNum);
	void AddState(char* nStateNum,char *strSomeNumber);
	void AddTriggerToState(Uint8 triggerIndex);
	void AddTypeToState(u16 nType);
	void AddInstruction(Uint16 nOpCode,float value,const char *strValue);
	void ExchangeIns();
	void *GetController();
	void CleanUp();
	
	void PushInt(Sint32 value);
	Sint32 PopInt();

	bool OpStackEnd();
	void DelpInstTop();
	Uint32 PopOp(bool isAddInst=true);
	void PushOp(Uint32 code, const char* str);
	// 获取优先级
	Sint32 PrecedenceOp(Uint32 op1);
	Sint32 PrecedenceOp(Uint32 op1, Uint32 op2);
	OpElement *GetInst(){return pInst;}
	int         GetHowManyInst(){return nCurrInst;}
	//search a State
	PLSTATEDEF* GetStateDef(int nStateNumber);
	PLSTATEDEF* GetCurrStateDef();
	PLSTATE* GetCurState();

	void ReallocStatedef(u16 index);
	 
	//SetFuction
	void SetStateDefType(u8 nType);
	void SetStateMoveType(u8 nType);
	void SetStatePhysicType(u8 nType);
	void SetStateAnim();
	void SetStateCtrl(s8 nCtrl);
	void SetStatePowerAdd(s16 nPowerAdd);
	void SetStateJuggle(s16 nJuggle);
	void SetStateHitDefPresit(bool bHitDef);
	void SetMoveHitPresit(bool bMoveHit);
	void SetStateHitCounterPresit(bool bHitCounter);
	void SetSprPriority(Sint8 nSprpriority);
	void SetStateFaceP2(bool bFaceP2);
	
	void SetVelSet(float x,float y);
    void NewInst(){nCurrInst=0;nTop = 0;}
	void SetParam(ConParmName nParam);
	void SetOpList(OpElement** addr);


	void SetPersistent(Uint32 persistent);
	void SetIgnorehitpause(bool ignorePause);
	void SetDefaultStatedef();
	void Reset();
	bool IsStateDefAviable(s32 nStateDefNum);

	void AddPorj();
	void AddExplod();
	void AddPalFXinfo();
	void AddAfterImage();
	void AddHDHitDef();



#ifdef CONTROL_HIT_DEF_DEFINE
#undef CONTROL_HIT_DEF_DEFINE
#endif // CONTROL_HIT_DEF_DEFINE
#define CONTROL_HIT_DEF_DEFINE(type, name) void SetHitDef_##name(type value)\
	{\
	PLSTATE *curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);\
	curState->pConHDdef->name = value;\
	}

#ifdef CONTROL_HIT_DEF_DEFINE_INSTRUCTION
#undef CONTROL_HIT_DEF_DEFINE_INSTRUCTION
#endif // CONTROL_HIT_DEF_DEFINE

#define CONTROL_HIT_DEF_DEFINE_INSTRUCTION(name) void SetHitDef_##name()\
	{\
	PLSTATE *curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);\
	curState->pConHDdef->name = (OpElement*)m_pAlloc->Alloc(sizeof(OpElement)*nCurrInst);\
	memcpy(curState->pConHDdef->name, pInst,sizeof(OpElement)*nCurrInst);\
	}

	// use macros to set hit attr
	CONTROL_HIT_DEF_ATTRS

};

#endif
