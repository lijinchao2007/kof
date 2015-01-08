/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/


#include "StateManager.h"
#include "tool.h"
#include "ConfigManager.h"

//Constructor
CStateManager::CStateManager()
{
	nIntTop = 0;
	m_MugenScale = CConfigManager::GetInstance()->GetFloat("Rules.MugenScale");
}
//Destructor
CStateManager::~CStateManager()
{
	m_pAlloc->FreeAllocater();
}

void CStateManager::SetAlloc(const char* allocName)
{
	SDL_strlcpy(m_allocName, allocName, MAX_PATH);
	m_pAlloc = CMemManager::GetInstance()->GetAllocater(allocName);
}
//restet after clean up
void CStateManager::Reset()
{
	nTotalStateDef=0;
	nTotalStateDefSize=100;
	lpStateDefList=(PLSTATEDEF*)m_pAlloc->Alloc(sizeof(PLSTATEDEF)*nTotalStateDefSize);
	nCurrTrigger=0;
}

void CStateManager::ReallocStatedef(u16 index)
{
	lpStateDefList[index].lpState=(PLSTATE*)m_pAlloc->Realloc(lpStateDefList[index].lpState,sizeof(PLSTATE)*lpStateDefList[index].nHowManyState);

	for(int i=0;i<lpStateDefList[index].nHowManyState;i++)
	{
		PLSTATE* curState = lpStateDefList[index].lpState + i;
		curState->triggers=(TriggerStruct*)m_pAlloc->Realloc(curState->triggers, sizeof(TriggerStruct)*curState->nHowManyTriggers);
		curState->nParamMemSize = curState->nParamCount;
		curState->pContrlParma = (CtrlParamStruct*)m_pAlloc->Realloc(curState->pContrlParma, sizeof(CtrlParamStruct)*curState->nParamMemSize);
	}
}


bool CStateManager::IsStateDefAviable(s32 nStateDefNum)
{
	for(s32 i=0;i < nTotalStateDef;i++)
	{
		if(lpStateDefList[i].StateNumber==nStateDefNum)
		{
			//make this state invalide to overwrite it 
			lpStateDefList[i].StateNumber=INVALID_STATE_NUM;                                           
			return true;
		}   
	}
	return false;
}

//Add a new statedef in the list
void CStateManager::AddStateDef(s32 nStateDefNum)
{

	if( IsStateDefAviable(nStateDefNum) )
	{
		PrintWaring("Overwriting StateDef %i",nStateDefNum);
	}

	// 优化上一个内存
	if(nTotalStateDef!=0)
		ReallocStatedef(nTotalStateDef-1);                  

	if( nTotalStateDef > nTotalStateDefSize -1)
	{
		nTotalStateDefSize+=100;
		lpStateDefList=(PLSTATEDEF*)m_pAlloc->Realloc(lpStateDefList,sizeof(PLSTATEDEF)*nTotalStateDefSize);
	}

	lpStateDefList[nTotalStateDef].StateNumber=nStateDefNum;

	nTotalState=0;

	nTotalStateSize=100;
	lpStateDefList[nTotalStateDef].lpState=(PLSTATE*)m_pAlloc->Alloc(sizeof(PLSTATE)*nTotalStateSize);

	nTotalStateDef++;

	//Set default values
	SetDefaultStatedef();


}

void CStateManager::SetStateDefType(u8 nType)
{
	lpStateDefList[nTotalStateDef-1].type=nType;

}
void CStateManager::SetStateMoveType(u8 nType)
{
	lpStateDefList[nTotalStateDef-1].movetype=nType;
}

void CStateManager::SetStatePhysicType(u8 nType)
{
	lpStateDefList[nTotalStateDef-1].physics=nType;
}
//Sets default values to the Statedef
void CStateManager::SetDefaultStatedef()
{
	lpStateDefList[nTotalStateDef-1].type            =s_stand;
	lpStateDefList[nTotalStateDef-1].movetype        =m_idle;
	lpStateDefList[nTotalStateDef-1].physics         =p_none;
	lpStateDefList[nTotalStateDef-1].nAnim           =NULL;
	lpStateDefList[nTotalStateDef-1].Velset.x        =UNSET_STATEDEF_FLAG;
	lpStateDefList[nTotalStateDef-1].Velset.y        =UNSET_STATEDEF_FLAG;
	lpStateDefList[nTotalStateDef-1].bCtrl           =-1;
	lpStateDefList[nTotalStateDef-1].nPoweradd       =UNSET_STATEDEF_FLAG;
	lpStateDefList[nTotalStateDef-1].bFacep2         =false;
	lpStateDefList[nTotalStateDef-1].nJuggle         =0;
	lpStateDefList[nTotalStateDef-1].bHitdefpersist  =false;
	lpStateDefList[nTotalStateDef-1].bMovehitpersist=false;
	lpStateDefList[nTotalStateDef-1].bHitcountpersist=false;
	lpStateDefList[nTotalStateDef-1].nSprpriority    =INVALID_SPR_PRIORITY;       

}

void CStateManager::SetStateAnim()
{
	// PrintMessage("%i param",nParam);
	//this->AddInstruction(OP_STOP,0,"OP_STOP");
	PLSTATEDEF *curStateDef = &(lpStateDefList[nTotalStateDef-1]);
	curStateDef->nAnim = (OpElement*)m_pAlloc->Alloc(sizeof(OpElement)* nCurrInst);
	memcpy(curStateDef->nAnim, pInst,sizeof(OpElement)*nCurrInst);
}
void CStateManager::SetStateCtrl(s8 nCtrl)
{
	lpStateDefList[nTotalStateDef-1].bCtrl=nCtrl;
}
void CStateManager::SetStatePowerAdd(s16 nPowerAdd)
{
	lpStateDefList[nTotalStateDef-1].nPoweradd=nPowerAdd;
}
void CStateManager::SetStateJuggle(s16 nJuggle)
{
	lpStateDefList[nTotalStateDef-1].nJuggle=nJuggle;
}

void CStateManager::SetStateHitDefPresit(bool bHitDef)
{
	lpStateDefList[nTotalStateDef-1].bHitdefpersist=bHitDef;
}
void CStateManager::SetMoveHitPresit(bool bMoveHit)
{
	lpStateDefList[nTotalStateDef-1].bMovehitpersist=bMoveHit;
}

void CStateManager::SetStateHitCounterPresit(bool bHitCounter)
{
	lpStateDefList[nTotalStateDef-1].bHitcountpersist=bHitCounter;
}
void CStateManager::SetSprPriority(Sint8 nSprpriority)
{
	lpStateDefList[nTotalStateDef-1].nSprpriority=nSprpriority;
}

void CStateManager::SetStateFaceP2(bool bFaceP2)
{
	lpStateDefList[nTotalStateDef-1].bFacep2=bFaceP2;       
}

void CStateManager::SetVelSet(float x,float y)
{
	lpStateDefList[nTotalStateDef-1].Velset.x=x;
	lpStateDefList[nTotalStateDef-1].Velset.y=y;

}

//Add a State tothe current Statedef
void CStateManager::AddState(char* stNum,char* stInfo)
{
	PrintMessage("Add state %s, %s",stNum, stInfo);
	// expand the size fo state
	if(nTotalState > nTotalStateSize-1)
	{
		nTotalStateSize+=100;
		lpStateDefList[nTotalStateDef-1].lpState = (PLSTATE*)m_pAlloc->Realloc(lpStateDefList[nTotalStateDef-1].lpState,
			sizeof(PLSTATE)*nTotalStateSize);
	}

	//// realloc last state's trigger
	//if (nTotalState > 0)
	//{
	//	PLSTATE *lastState = lpStateDefList[nTotalStateDef-1].lpState+nTotalState - 1;
	//	lastState->triggers = (TriggerStruct*)m_pAlloc->Realloc(lastState->triggers, sizeof(TriggerStruct)*lastState->nHowManyTriggers);
	//}
	// init state
	PLSTATE *curState = lpStateDefList[nTotalStateDef-1].lpState+nTotalState;

	SDL_strlcpy(curState->stNumber, stNum, MAX_STRING_LENGTH);
	SDL_strlcpy(curState->stInfo, stInfo, MAX_STRING_LENGTH);
	// Control_AfterImage start from 0;
	curState->nType = -1;
	curState->triggers=(TriggerStruct*)m_pAlloc->Alloc(sizeof(TriggerStruct)*DEFAULT_TrgCount_PerState);
	curState->nTriggersMemSize = DEFAULT_TrgCount_PerState;
	curState->nHowManyTriggers = 0;
	curState->bIgnorPause = 0;
	curState->nPersistent = 1;
	curState->nParamCount = 0;

	curState->nParamMemSize = DEFAULT_ParmCount_PerState;
	curState->pContrlParma = (CtrlParamStruct*)m_pAlloc->Alloc(sizeof(CtrlParamStruct)*curState->nParamMemSize);
	curState->nParamCount = 0;
	curState->pConHDdef = NULL;
	curState->pProjInfo = NULL;
	curState->pAfterImage = NULL;
	curState->pPalFXinfo = NULL;
	curState->pExplod = NULL;

	nTotalState++;
	lpStateDefList[nTotalStateDef-1].nHowManyState=nTotalState;

	// init for state parse
	nCurrTrigger=0;
}
//Now save the controller type wich would be executeted
void CStateManager::AddTypeToState(u16 nType)
{
	lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1].nType=nType;
	if (nType == Control_HitDef)
	{
		// 添加数据结构
		this->AddHDHitDef();
	}else if (nType == Control_AfterImage)
	{
		// 添加数据结构
		this->AddAfterImage();
	}else if (nType == Control_PalFX||nType == Control_AllPalFX)
	{
		// 添加数据结构
		this->AddPalFXinfo();
	}else if (nType == Control_Explod)
	{
		// 添加数据结构
		this->AddExplod();
	}else if (nType == Control_Projectile)
	{
		// 添加数据结构
		this->AddHDHitDef();
		this->AddPorj();
	}
}

PLSTATEDEF* CStateManager::GetCurrStateDef()
{

	return &lpStateDefList[nTotalStateDef-1];        
}

PLSTATE* CStateManager::GetCurState()
{
	PLSTATE* curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);
	CAssert(curState!=NULL, "getcurstate return null error");
	return curState;
}

void* CStateManager::GetController()
{
	return NULL;
	//	return lpCurrent->lpController;
}

//Cleans up ;-)
void CStateManager::CleanUp()
{

}

bool CStateManager::OpStackEnd()
{
	if (nTop == 0)
	{
		return true;
	}
	return false;
}

void CStateManager::PushInt(Sint32 value)
{
	intStack[nIntTop] = value;
	nIntTop ++;
}
Sint32 CStateManager::PopInt()
{
	if (nIntTop==0)
	{
		return 0;
	}
	return intStack[--nIntTop];
}
void CStateManager::DelpInstTop()
{
	nCurrInst--;
}
Uint32 CStateManager::PopOp(bool isAddInst)
{
	
	Uint32 code = pStackInst[nTop-1].n_OpCode;

	if (isAddInst)
	{
		pInst[nCurrInst].n_OpCode = code;
		pInst[nCurrInst].Value=pStackInst[nTop-1].Value;
		SDL_strlcpy(pInst[nCurrInst].strValue, pStackInst[nTop-1].strValue, MAX_PATH);
		nCurrInst++;
	}

	nTop--;
	return code;
}
void CStateManager::PushOp(Uint32 code, const char* str)
{

	pStackInst[nTop].n_OpCode=code;
	pStackInst[nTop].Value=0;
	SDL_strlcpy(pStackInst[nTop].strValue, str, MAX_PATH);
	nTop++;
}
Sint32 CStateManager::PrecedenceOp(Uint32 op1)
{
	return this->PrecedenceOp(op1, pStackInst[nTop-1].n_OpCode);
}
Sint32 CStateManager::PrecedenceOp(Uint32 op1, Uint32 op2)
{
	if (op1<0 || op1 >OP_STOP || op2<0 || op2 > OP_STOP)
	{
		PrintMessage("precedence op error op1 %d op2 %d", op1, op2);
		return 0;
	}
	return OP_Precedence[op1] - OP_Precedence[op2];
}
//Add Instruction to currrent trigger
void CStateManager::AddInstruction(Uint16 nOpCode,float value,const char *strValue)
{
	const char* tmp = STR_TriggerType[nOpCode];
	//PrintMessage("AddInstruction = command:%s value:%f str:%s",tmp,value,strValue);

	pInst[nCurrInst].n_OpCode=nOpCode;
	pInst[nCurrInst].Value=value;
	pInst[nCurrInst].strValue[0]=0;

	//only add a string if we need one
	if(strValue[0]!='#')
	{
		SDL_strlcpy(pInst[nCurrInst].strValue,strValue, MAX_PATH);
	}

	nCurrInst++;


}
//Increase the index of the current trigger ref
void CStateManager::AddTriggerToState(Uint8 triggerIndex)
{   
	if (nTotalState <= 0)
	{
		throw CError("there is no state to add trigger");
	}
	PLSTATE *curState = lpStateDefList[nTotalStateDef-1].lpState + nTotalState-1;
	if(nCurrTrigger > curState->nTriggersMemSize)
	{
		curState->nTriggersMemSize += DEFAULT_TrgCount_PerState;
		curState->triggers = (TriggerStruct *)m_pAlloc->Realloc(curState->triggers, sizeof(TriggerStruct)*curState->nTriggersMemSize);
	}

	//bool bFound = false;
	//for (int i=0;i<nCurrTrigger;i++)
	//{
	//	if (curState->triggers[i].nTriggerIndex == triggerIndex)
	//	{
	//		bFound = true;
	//		// 已经存在
	//		AddInstruction(OP_AND, 0, "OP_AND");
	//		ExchangeIns();
	//		Sint32 oldCount = curState->triggers[i].nIntCount;
	//		curState->triggers[i].pInts=(OpElement*)m_pAlloc->Realloc(curState->triggers[i].pInts, sizeof(OpElement)* (oldCount + nCurrInst));
	//		// 覆盖最后一个stop
	//		memcpy(curState->triggers[i].pInts + oldCount - 1,	pInst, sizeof(OpElement)*(nCurrInst + 1));
	//		curState->triggers[i].nIntCount = oldCount + nCurrInst;
	//		break;

	//	}
	//}

	curState->triggers[nCurrTrigger].nTriggerIndex=triggerIndex;
	curState->triggers[nCurrTrigger].pInts=(OpElement*)m_pAlloc->Alloc(sizeof(OpElement)* nCurrInst);
	curState->triggers[nCurrTrigger].nIntCount = nCurrInst;
	memcpy(curState->triggers[nCurrTrigger].pInts,	pInst,sizeof(OpElement)*nCurrInst);
	nCurrTrigger++;

	curState->nHowManyTriggers = nCurrTrigger;
}


//set the param value
void CStateManager::SetParam(ConParmName nParam)
{
	// PrintMessage("%i param",nParam);
	//this->AddInstruction(OP_STOP,0,"OP_STOP");
	PLSTATE *curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);
	SDL_assert(curState->pContrlParma!=NULL);
	if (curState->nParamCount>=curState->nParamMemSize)
	{
		curState->nParamMemSize += DEFAULT_ParmCount_PerState;
		curState->pContrlParma = (CtrlParamStruct*)m_pAlloc->Alloc(sizeof(CtrlParamStruct)* curState->nParamMemSize);
	}
	curState->pContrlParma[curState->nParamCount].nParam = nParam;
	curState->pContrlParma[curState->nParamCount].pInts = (OpElement*)m_pAlloc->Alloc(sizeof(OpElement)* nCurrInst);
	memcpy(curState->pContrlParma[curState->nParamCount].pInts, pInst,sizeof(OpElement)*nCurrInst);
	curState->nParamCount++;
}


//set the param value
void CStateManager::SetOpList(OpElement** addr)
{
	// PrintMessage("%i param",nParam);
	//this->AddInstruction(OP_STOP,0,"OP_STOP");
	PLSTATE *curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);
	*addr = (OpElement*)m_pAlloc->Alloc(sizeof(OpElement)* nCurrInst);
	memcpy(*addr, pInst,sizeof(OpElement)*nCurrInst);
	curState->nParamCount++;
}

void CStateManager::AddPorj()
{
	PLSTATE *curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);
	if (curState->pProjInfo == NULL)
	{
		curState->pProjInfo = (ProjectileInfo*)m_pAlloc->Alloc(sizeof(ProjectileInfo));
		ProjectileInfo proj;
		SDL_memcpy(curState->pProjInfo, &proj, sizeof(ProjectileInfo));
	}
}
void CStateManager::AddExplod()
{
	PLSTATE *curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);
	if (curState->pExplod == NULL)
	{
		curState->pExplod = (ExplodInfo*)m_pAlloc->Alloc(sizeof(ExplodInfo));
		ExplodInfo explod;
		SDL_memcpy(curState->pExplod, &explod, sizeof(ExplodInfo));
	}
}

void CStateManager::AddPalFXinfo()
{
	PLSTATE *curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);
	if (curState->pPalFXinfo == NULL)
	{
		curState->pPalFXinfo = (PalFXInfo*)m_pAlloc->Alloc(sizeof(PalFXInfo));
		PalFXInfo Info;
		SDL_memcpy(curState->pPalFXinfo, &Info, sizeof(PalFXInfo));
	}
}


void CStateManager::AddAfterImage()
{
	PLSTATE *curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);
	if (curState->pAfterImage == NULL)
	{
		curState->pAfterImage = (AfterImage*)m_pAlloc->Alloc(sizeof(AfterImage));
		AfterImage afterimage;
		SDL_memcpy(curState->pAfterImage, &afterimage, sizeof(AfterImage));
	}
}
//set the HITDEF param value
void CStateManager::AddHDHitDef()
{
	PLSTATE *curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);
	if (curState->pConHDdef == NULL)
	{
		curState->pConHDdef = (CONTROLHITDEF*)m_pAlloc->Alloc(sizeof(CONTROLHITDEF));
	}
	// init hitdef
	curState->pConHDdef->hitflag = -1;
	curState->pConHDdef->guardflag = 0;

	curState->pConHDdef->ground_hittime = NULL;
	curState->pConHDdef->guard_hittime = NULL;
	curState->pConHDdef->air_hittime = NULL;

	curState->pConHDdef->ground_slidetime = NULL;
	curState->pConHDdef->guard_slidetime = NULL;
	curState->pConHDdef->guard_ctrltime = NULL;
	curState->pConHDdef->airguard_ctrltime = NULL;

	curState->pConHDdef->animtype = HitDef_animtype_light;
	curState->pConHDdef->air_animtype = -1;
	curState->pConHDdef->fall_animtype = -1;

	curState->pConHDdef->sparkno = -1;
	curState->pConHDdef->guard_sparkno = -1;
	curState->pConHDdef->sparkno_x = NULL;
	curState->pConHDdef->sparkno_y = NULL;

	curState->pConHDdef->ground_type = HitDef_atk_type_None;
	curState->pConHDdef->air_type = -1;

	curState->pConHDdef->numhits = 1;

	curState->pConHDdef->hit_damage = NULL;
	curState->pConHDdef->guard_damage = NULL;

	// vel
	curState->pConHDdef->ground_velocity.x = 0;
	curState->pConHDdef->ground_velocity.y = 0;
	curState->pConHDdef->guard_velocity.x = UNSET_VELOCITY;
	curState->pConHDdef->guard_velocity.y = UNSET_VELOCITY;

	curState->pConHDdef->air_velocity.x = 0;
	curState->pConHDdef->air_velocity.y = 0;
	curState->pConHDdef->airguard_velocity.x = UNSET_VELOCITY;
	curState->pConHDdef->airguard_velocity.y = UNSET_VELOCITY;
	curState->pConHDdef->down_velocity.x = UNSET_VELOCITY;
	curState->pConHDdef->down_velocity.y = UNSET_VELOCITY;

	curState->pConHDdef->yaccel = 0.35*m_MugenScale;

	curState->pConHDdef->p1stateno = -1;
	curState->pConHDdef->p2stateno = -1;

	curState->pConHDdef->fall = 0;
	curState->pConHDdef->fall_xvelocity = -1.0f;
	curState->pConHDdef->fall_yvelocity =  -4.5*m_MugenScale;


	curState->pConHDdef->getpower = -1;
	curState->pConHDdef->guard_getpower = -1;
	curState->pConHDdef->givepower = -1;
	curState->pConHDdef->guard_givepower = -1;

	curState->pConHDdef->pause_time = 0;
	curState->pConHDdef->guard_pause_time = 0;
	curState->pConHDdef->shake_time = 0;
	curState->pConHDdef->guard_shake_time = 0;

	curState->pConHDdef->palfx_time = NULL;
	PalFXInfo info;
	curState->pConHDdef->palfxinfo = info;

	curState->pConHDdef->guard_dist = -1;
	curState->pConHDdef->p1sprpriority = 1;
	curState->pConHDdef->p2sprpriority = 0;

}

void CStateManager::SetPersistent(Uint32 persistent)
{
	PLSTATE* curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);
	curState->nPersistent = persistent;
}
void CStateManager::SetIgnorehitpause(bool ignorePause)
{
	PLSTATE* curState = &(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1]);
	curState->bIgnorPause = ignorePause;
}

//search for the given state and return it
PLSTATEDEF* CStateManager::GetStateDef(int nStateNumber)
{
	for(u16 i=0;i<nTotalStateDef;i++)
	{
		if(lpStateDefList[i].StateNumber==nStateNumber)
			return &lpStateDefList[i];
	}
	if (nStateNumber != -3 && nStateNumber != -2 && nStateNumber!=-1)
	{
		PrintWaring("CStateManager::Statedef %i not found",nStateNumber);
	}
	return 0;    
}

void CStateManager::ExchangeIns()
{
	OpElement temp;

	memcpy(&temp,&pInst[nCurrInst-1],sizeof(temp));

	memcpy(&pInst[nCurrInst-1],&pInst[nCurrInst-2],sizeof(temp));
	memcpy(&pInst[nCurrInst-2],&temp,sizeof(temp));

}
