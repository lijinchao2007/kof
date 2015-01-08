/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "tool.h"
#include "ControllerExecuter.h"
#include "GameTimer.h"
#include "logic/engine.h"
#include "logic/StageManager.h"
#include "Helper.h"

//Constructor
CControllerExecuter::CControllerExecuter()
{
    InitFuncTable();

}
//Destructor
CControllerExecuter::~CControllerExecuter()
{

}

//Inits the Function Table
void CControllerExecuter::InitFuncTable()
{
    for (int i=0;i<NUMFUNCT_CONTROL;i++)
	{
		pFuncTable[i] = NULL;
	}
	pFuncTable[Control_AfterImage]=&CControllerExecuter::AfterImage;
	//pFuncTable[Control_AfterImageTime]=&CControllerExecuter::AfterImageTime;
	pFuncTable[Control_AllPalFX]=&CControllerExecuter::AllPalFX;
	//pFuncTable[Control_AngleAdd]=&CControllerExecuter::AngleAdd;
	//pFuncTable[Control_AngleDraw]=&CControllerExecuter::AngleDraw;
	//pFuncTable[Control_AngleMul]=&CControllerExecuter::AngleMul;
	//pFuncTable[Control_AngleSet]=&CControllerExecuter::AngleSet;
	//pFuncTable[Control_AppendToClipboard]=&CControllerExecuter::AppendToClipboard;
	pFuncTable[Control_AssertSpecial]=&CControllerExecuter::AssertSpecial;
	//pFuncTable[Control_AttackDist]=&CControllerExecuter::AttackDist;
	//pFuncTable[Control_AttackMulSet]=&CControllerExecuter::AttackMulSet;
	//pFuncTable[Control_BGPalFX]=&CControllerExecuter::BGPalFX;
	//pFuncTable[Control_BindToParent]=&CControllerExecuter::BindToParent;
	//pFuncTable[Control_BindToRoot]=&CControllerExecuter::BindToRoot;
	//pFuncTable[Control_BindToTarget]=&CControllerExecuter::BindToTarget;
	pFuncTable[Control_ChangeAnim]=&CControllerExecuter::ChangeAnim;
	pFuncTable[Control_ChangeAnim2]=&CControllerExecuter::ChangeAnim2;
	pFuncTable[Control_ChangeState]=&CControllerExecuter::ChangeState;
	//pFuncTable[Control_ClearClipboard]=&CPlayer::Control_ClearClipboard;
	pFuncTable[Control_CtrlSet]=&CControllerExecuter::CtrlSet;
	//pFuncTable[Control_DefenceMulSet]=&CPlayer::Control_DefenceMulSet;
	pFuncTable[Control_DestroySelf]=&CControllerExecuter::DestroySelf;
	pFuncTable[Control_DisplayToClipboard]=&CControllerExecuter::DisplayToClipboard;
	pFuncTable[Control_EnvColor]=&CControllerExecuter::EnvColor;
	pFuncTable[Control_EnvShake]=&CControllerExecuter::EnvShake;
	pFuncTable[Control_Explod]=&CControllerExecuter::Explod;
	//pFuncTable[Control_ExplodBindTime]=&CPlayer::Control_ExplodBindTime;
	//pFuncTable[Control_ForceFeedback]=&CPlayer::Control_ForceFeedback;
	//pFuncTable[Control_FallEnvShake]=&CPlayer::Control_FallEnvShake;
	//pFuncTable[Control_GameMakeAnim]=&CPlayer::Control_GameMakeAnim;
	pFuncTable[Control_Gravity]=&CControllerExecuter::Gravity;
	pFuncTable[Control_Helper]=&CControllerExecuter::Helper;
	//pFuncTable[Control_HitAdd]=&CPlayer::Control_HitAdd;
	pFuncTable[Control_HitBy]=&CControllerExecuter::HitBy;
	pFuncTable[Control_HitDef]=&CControllerExecuter::HitDef;
	pFuncTable[Control_HitFallDamage]=&CControllerExecuter::HitFallDamage;
	pFuncTable[Control_HitFallSet]=&CControllerExecuter::HitFallSet;
	pFuncTable[Control_HitFallVel]=&CControllerExecuter::HitFallVel;
	//pFuncTable[Control_HitOverride]=&CControllerExecuter::HitOverride;
	pFuncTable[Control_HitVelSet]=&CControllerExecuter::HitVelSet;
	//pFuncTable[Control_LifeAdd]=&CControllerExecuter::LifeAdd;
	//pFuncTable[Control_LifeSet]=&CControllerExecuter::LifeSet;
	//pFuncTable[Control_MakeDust]=&CControllerExecuter::MakeDust;
	//pFuncTable[Control_ModifyExplod]=&CControllerExecuter::ModifyExplod;
	//pFuncTable[Control_MoveHitReset]=&CControllerExecuter::MoveHitReset;
	pFuncTable[Control_NotHitBy]=&CControllerExecuter::NotHitBy;
	pFuncTable[Control_Null]=&CControllerExecuter::Null;
	//pFuncTable[Control_Offset]=&CControllerExecuter::Offset;
	pFuncTable[Control_PalFX]=&CControllerExecuter::PalFX;
	//pFuncTable[Control_ParentVarAdd]=&CControllerExecuter::ParentVarAdd;
	//pFuncTable[Control_ParentVarSet]=&CControllerExecuter::ParentVarSet;
	//pFuncTable[Control_Pause]=&CControllerExecuter::Pause;
	pFuncTable[Control_PlayerPush]=&CControllerExecuter::PlayerPush;
	pFuncTable[Control_PlaySnd]=&CControllerExecuter::PlaySnd;
	pFuncTable[Control_PosAdd]=&CControllerExecuter::PosAdd;
	//pFuncTable[Control_PosFreeze]=&CControllerExecuter::HitFallSet;
	pFuncTable[Control_PosSet]=&CControllerExecuter::PosSet;
	//pFuncTable[Control_PowerAdd]=&CControllerExecuter::HitFallSet;
	//pFuncTable[Control_PowerSet]=&CControllerExecuter::HitFallSet;
	pFuncTable[Control_Projectile]=&CControllerExecuter::Projectile;
	//pFuncTable[Control_RemoveExplod]=&CControllerExecuter::HitFallSet;
	//pFuncTable[Control_ReversalDef]=&CControllerExecuter::HitFallSet;
	//pFuncTable[Control_ScreenBound]=&CControllerExecuter::HitFallSet;
	pFuncTable[Control_SelfState]=&CControllerExecuter::SelfState;
	//pFuncTable[Control_SprPriority]=&CControllerExecuter::HitFallSet;
	pFuncTable[Control_StateTypeSet]=&CControllerExecuter::StateTypeSet;
	//pFuncTable[Control_SndPan]=&CControllerExecuter::HitFallSet;
	//pFuncTable[Control_StopSnd]=&CControllerExecuter::HitFallSet;
	pFuncTable[Control_SuperPause]=&CControllerExecuter::SuperPause;
	pFuncTable[Control_TargetBind]=&CControllerExecuter::TargetBind;
	//pFuncTable[Control_TargetDrop]=&CControllerExecuter::HitFallSet;
	//pFuncTable[Control_TargetFacing]=&CControllerExecuter::HitFallSet;
	//pFuncTable[Control_TargetLifeAdd]=&CControllerExecuter::HitFallSet;
	//pFuncTable[Control_TargetPowerAdd]=&CControllerExecuter::HitFallSet;
	pFuncTable[Control_TargetState]=&CControllerExecuter::targetState;
	//pFuncTable[Control_TargetVelAdd]=&CControllerExecuter::HitFallSet;
	//pFuncTable[Control_TargetVelSet]=&CControllerExecuter::HitFallSet;
	//pFuncTable[Control_Trans]=&CControllerExecuter::HitFallSet;
	pFuncTable[Control_Turn]=&CControllerExecuter::Turn;
	pFuncTable[Control_VarAdd]=&CControllerExecuter::VarAdd;
	//pFuncTable[Control_VarRandom]=&CControllerExecuter::HitFallSet;
	//pFuncTable[Control_VarRangeSet]=&CControllerExecuter::HitFallSet;
	pFuncTable[Control_VarSet]=&CControllerExecuter::VarSet;
	pFuncTable[Control_VelAdd]=&CControllerExecuter::VelAdd;
	pFuncTable[Control_VelMul]=&CControllerExecuter::VelMul;
	pFuncTable[Control_VelSet]=&CControllerExecuter::VelSet;
	pFuncTable[Control_Width]=&CControllerExecuter::Width;
	pFuncTable[Control_AddCommandInput]=&CControllerExecuter::AddCommandInput;
	pFuncTable[Control_Print]=&CControllerExecuter::Print;

}


void CControllerExecuter::ExecuteController(PLSTATE* tempState)
{
	//PrintMessage("ID %d|%4d: exec %d|%s",m_pPlayer1->GetPropID(), CGameTimer::GetInstance()->GetGameTime(), tempState->nType, strControllerTypes[tempState->nType]);
	if (this->pFuncTable[tempState->nType] == NULL)
	{
		if (OPEN_ERROR)
		{
			PrintMessage("ID %d|%4d: error %s  not existed", m_pPlayer1->GetPropID(), CGameTimer::GetInstance()->GetGameTime(), strControllerTypes[tempState->nType]);
		}
		return;
	}
	//Execute the function
	(this->*pFuncTable[tempState->nType])(tempState);
}

char* CControllerExecuter::ExecuteGetStr(OpElement *pInst)
{
	/*OpElement tmp[100];
	SDL_memcpy(tmp, pInst, sizeof(OpElement)*100);*/
	return m_pPlayer1->m_pVMachine->ExecuteGetStr(pInst);
}

float CControllerExecuter::Execute(OpElement *pInst)
{
	/*OpElement tmp[100];
	SDL_memcpy(tmp, pInst, sizeof(OpElement)*100);*/
	return m_pPlayer1->m_pVMachine->Execute(pInst);
}

void CControllerExecuter::AfterImage(PLSTATE* state)
{
	m_pPlayer1->m_AfterImageStack.config = state->pAfterImage;
	m_pPlayer1->m_AfterImageStack.duringTime = state->pAfterImage->time;
	m_pPlayer1->m_AfterImageStack.bottom = 0;
	m_pPlayer1->m_AfterImageStack.top = 0;
	m_pPlayer1->m_AfterImageStack.EndTime = 0;
}

void CControllerExecuter::AllPalFX(PLSTATE* state)
{
	PalFX(state);
}

void CControllerExecuter::AssertSpecial(PLSTATE* state)
{
	for (int i =0;i<state->nParamCount;i++)
	{
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_flag)
		{
			char* flag = ExecuteGetStr(param.pInts);
			if (SDL_strcasecmp("NoAutoTurn", flag) == 0)
			{
				m_pPlayer1->SetAssertNoAutoTurn(true);
			}
			if (SDL_strcasecmp("nowalk", flag) == 0)
			{
				m_pPlayer1->SetAssetNoWalk(true);
			}
			break;
		}
	}
	
}
void CControllerExecuter::ChangeAnim(PLSTATE* state)
{
	float value =0;
	for (int i =0;i<state->nParamCount;i++)
	{
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_value)
		{
			value = Execute(param.pInts);
			break;
		}
	}
	m_pPlayer1->PrepareAnim((int)value);
}

void CControllerExecuter::ChangeAnim2(PLSTATE* state)
{
	float value =0;
	for (int i =0;i<state->nParamCount;i++)
	{
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_value)
		{
			value = Execute(param.pInts);
			break;
		}
	}
	if (m_pPlayer1->bIsInP2State)
	{
		m_pPlayer2->PrepareAnim((int)value, true);
	}
	
}

void CControllerExecuter::CtrlSet(PLSTATE* state)
{
	float value =0;
	for (int i =0;i<state->nParamCount;i++)
	{
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_value)
		{
			value = Execute(param.pInts);
		}
	}
	m_pPlayer1->bCtrl = (bool)value;
}
void CControllerExecuter::ChangeState(PLSTATE* state)
{
	int stateNo =0;
	for (int i =0;i<state->nParamCount;i++)
	{
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_ctrl)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->SetCtrl((bool)(value));
		}
		if (param.nParam == CPN_value)
		{
			stateNo = Execute(param.pInts);
		}
	}
	if (m_pPlayer1->bIsInP2State)
	{
		m_pPlayer2->ChangeState(stateNo, false, true);
	}else{
		m_pPlayer1->ChangeState(stateNo);
	}
}

void CControllerExecuter::DestroySelf(PLSTATE* state)
{
	if (m_pPlayer1->m_type!=PLAYER_HELPER)
	{
		return;
	}
	PrintMessage("time<%d>:DestroySelf helperid %d helpercount %d ", CGameTimer::GetInstance()->GetGameTime() ,m_pPlayer1->GetPropID(), m_pPlayer1->GetParent()->GetChildCount());
	m_pPlayer1->GetParent()->RemovePlayer(m_pPlayer1);
}

void CControllerExecuter::DisplayToClipboard(PLSTATE* state)
{
#ifdef __WIN32__
	int valueList[10];
	va_list ap = reinterpret_cast<va_list>((char*)valueList);
	int parCount = 0;

	char format[MAX_PATH];
	for (int i =0;i<state->nParamCount;i++)
	{
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_text)
		{
			SDL_strlcpy(format, ExecuteGetStr(param.pInts), MAX_PATH);
		}
		else if (param.nParam == CPN_Param)
		{
			valueList[parCount++] = Execute(param.pInts);
		}
	}
	char logstr[MAX_PATH];
	SDL_vsnprintf(logstr, MAX_PATH, format, ap);
#endif
}

void CControllerExecuter::EnvColor(PLSTATE *state)
{
	float time=0, color_r=255,color_g=255,color_b=255;
	bool isUnder = false;
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_time)
		{
			time = Execute(param.pInts);
		}else if (param.nParam == CPN_color_r)
		{
			color_r = Execute(param.pInts);
		}else if (param.nParam == CPN_color_g)
		{
			color_g = Execute(param.pInts);
		}else if (param.nParam == CPN_color_b)
		{
			color_b = Execute(param.pInts);
		}else if (param.nParam == CPN_under)
		{
			isUnder = Execute(param.pInts);
		}
	}
	m_pPlayer1->PrepareEnvColor(time, color_r, color_g, color_b, isUnder);
}

void CControllerExecuter::EnvShake(PLSTATE* state)
{
	float time=0, freq=60,ampl=-10,phase=0;

	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_time)
		{
			time = Execute(param.pInts);
		}else if (param.nParam == CPN_freq)
		{
			freq = Execute(param.pInts);
		}else if (param.nParam == CPN_ampl)
		{
			ampl = Execute(param.pInts);
		}else{
			phase = Execute(param.pInts);
		}
	}
	m_pPlayer1->PrepareShake(time, freq, ampl, phase);
}

void CControllerExecuter::Explod(PLSTATE* state)
{
	m_pPlayer1->PrepareExplod(state->pExplod);
}

void CControllerExecuter::Gravity(PLSTATE* state)
{
	float yaccel = m_pPlayer1->GetConfigFloat("Movement.yaccel");
	m_pPlayer1->yVel += yaccel;
}

void CControllerExecuter::Helper(PLSTATE* state)
{
	EnumHelperType helptype = eHelperType_Normal;
	char name[MAX_PATH];
	int id=-1; 
	float posx=0, posy=0;
	EnumPosType postype = eEnumPosType_P1;
	int facing = 1;
	int stateno=-1;
	bool keyctrl=false;
	bool ownpal =false;
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if(param.nParam == CPN_helpertype){
			char *str = ExecuteGetStr(param.pInts);
			if (SDL_strcasecmp("normal", str)==0)
			{
				helptype = eHelperType_Normal;
			}else if (SDL_strcasecmp("player", str)==0)
			{
				helptype = eHelperType_Player;
			}
		}else if (param.nParam == CPN_name)
		{
			char *str = ExecuteGetStr(param.pInts);
			SDL_strlcpy(name, str, MAX_PATH);
		}else if (param.nParam == CPN_id)
		{
			id = Execute(param.pInts);
		}else if (param.nParam == CPN_x)
		{
			posx = Execute(param.pInts);
		}else if (param.nParam == CPN_y)
		{
			posy = Execute(param.pInts);
		}else if(param.nParam == CPN_postype){
			char *str = ExecuteGetStr(param.pInts);
			if (SDL_strcasecmp("p1", str)==0)
			{
				postype = eEnumPosType_P1;
			}else if (SDL_strcasecmp("p2", str)==0)
			{
				postype = eEnumPosType_P2;
			}else if (SDL_strcasecmp("front", str)==0)
			{
				postype = eEnumPosType_Front;
			}else if (SDL_strcasecmp("back", str)==0)
			{
				postype = eEnumPosType_Back;
			}else if (SDL_strcasecmp("left", str)==0)
			{
				postype = eEnumPosType_Left;
			}else if (SDL_strcasecmp("right", str)==0)
			{
				postype = eEnumPosType_Right;
			}
		}else if(param.nParam == CPN_facing){
			facing = Execute(param.pInts);
		}else if(param.nParam == CPN_stateno){
			stateno = Execute(param.pInts);
		}else if(param.nParam == CPN_keyctrl){
			keyctrl = Execute(param.pInts);
		}else if(param.nParam == CPN_ownpal){
			ownpal = Execute(param.pInts);
		}
	} 
	//get the virtual machines
	//Set players to the VM
	CAssert(id>P4||id==-1, "helper id shoud greater than p4");
	PrintMessage("time<%d>:Helper helperid %d helpercount %d ", CGameTimer::GetInstance()->GetGameTime(), id, m_pPlayer1->GetChildCount());
	CHelper* helper = new CHelper;
	//now set the VM to the player
	helper->InitWithParent(id, m_pPlayer1);
	helper->LoadPlayer(m_pPlayer1->GetPlayerName(), m_pPlayer1->GetPropPal());
	bool bfacingRight;
	if (facing == 1)
	{
		switch (postype)
		{
		case eEnumPosType_P2:
			bfacingRight = m_pPlayer2->bRightFaced;
			break;
		case eEnumPosType_Left:
		case eEnumPosType_Right:
			bfacingRight = true;
			break;
		default:
			bfacingRight = m_pPlayer1->bRightFaced;
			break;
		}
	}else{
		switch (postype)
		{
		case eEnumPosType_P2:
			bfacingRight = !m_pPlayer2->bRightFaced;
			break;
		case eEnumPosType_Left:
		case eEnumPosType_Right:
			bfacingRight = false;
			break;
		default:
			bfacingRight = !m_pPlayer1->bRightFaced;
			break;
		}
	}
	float realPosX, realPosY;
	if (bfacingRight)
	{
		helper->FaceRight();
		switch (postype)
		{
		case eEnumPosType_P1:
			realPosX = m_pPlayer1->x+ posx;
			realPosY = m_pPlayer1->y+ posy;
			break;
		case eEnumPosType_P2:
			realPosX = m_pPlayer2->x+ posx;
			realPosY = m_pPlayer2->y+ posy;
			break;
		case eEnumPosType_Front:
			realPosX = CStageManager::GetInstance()->GetRight()+posx;
			realPosY = posy;
			break;
		case eEnumPosType_Back:
			realPosX = CStageManager::GetInstance()->GetLeft()+posx;
			realPosY = posy;
			break;
		case eEnumPosType_Left:
			realPosX = CStageManager::GetInstance()->GetLeft()+posx;
			realPosY = posy;
			break;
		case eEnumPosType_Right:
			realPosX = CStageManager::GetInstance()->GetRight()+posx;
			realPosY = posy;
			break;
		default:
			realPosX = posx;
			realPosY = posy;
			break;
		}
	}// end bfaced
	else
	{
		helper->FaceLeft();
		switch (postype)
		{
		case eEnumPosType_P1:
			realPosX = m_pPlayer1->x- posx;
			realPosY = m_pPlayer1->y+ posy;
			break;
		case eEnumPosType_P2:
			realPosX = m_pPlayer2->x- posx;
			realPosY = m_pPlayer2->y+ posy;
			break;
		case eEnumPosType_Front:
			realPosX = CStageManager::GetInstance()->GetLeft()-posx;
			realPosY = posy;
			break;
		case eEnumPosType_Back:
			realPosX = CStageManager::GetInstance()->GetRight()-posx;
			realPosY = posy;
			break;
		case eEnumPosType_Left:
			realPosX = CStageManager::GetInstance()->GetLeft()-posx;
			realPosY = posy;
			break;
		case eEnumPosType_Right:
			realPosX = CStageManager::GetInstance()->GetRight()-posx;
			realPosY = posy;
			break;
		default:
			realPosX = -posx;
			realPosY = posy;
			break;
		}
	}
	helper->SetPos(realPosX, realPosY);
	helper->SetKeyCtrl(helptype);
	helper->SetKeyCtrl(keyctrl);
	helper->SetOwnPal(ownpal);
	helper->ChangeState(stateno, false, false);
}

void CControllerExecuter::HitBy(PLSTATE* state)
{
	m_pPlayer1->SetPropHitByTime(1);
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_value)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->SetPropHitByFlag(value);
		}
		if (param.nParam == CPN_time)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->SetPropHitByTime(value);
		}
	}

}
void CControllerExecuter::HitDef(PLSTATE* state)
{
	//���hitdefpersist  ��p1��hitdef�滻Ϊ��ǰhitdef
	m_pPlayer1->m_HitInfo.bIsHitDefConfSet = true;
	m_pPlayer1->m_HitInfo.CtrlHitDefConf = state->pConHDdef;
	m_pPlayer1->m_HitInfo.bIsHited = false;
	m_pPlayer1->m_HitInfo.nMoveContact = 0;
	m_pPlayer1->m_HitInfo.nMoveGuarded = 0;
	m_pPlayer1->m_HitInfo.nMoveHit = 0;

}

void CControllerExecuter::HitFallDamage(PLSTATE* state)
{
	Sint32 fall_damage = m_pPlayer1->m_GetHitInfo.bIsHitDefConfSet?m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->fall_damage:0;
	m_pPlayer1->ChangeLife(fall_damage);
}

void CControllerExecuter::HitFallSet(PLSTATE* state)
{

}

void CControllerExecuter::HitFallVel(PLSTATE* state)
{
	float fall_xvelocity = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->fall_xvelocity;
	float fall_yvelocity = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->fall_yvelocity;

	if (fall_xvelocity != -1.0f)
	{
		m_pPlayer1->xVel = fall_xvelocity;
	}
	m_pPlayer1->yVel = fall_yvelocity;
}
void CControllerExecuter::HitVelSet(PLSTATE* state)
{
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_x)
		{
			float value = Execute(param.pInts);
			if (value)
			{
				velocity groudV = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->ground_velocity;
				velocity guardV = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->guard_velocity.x == UNSET_VELOCITY? groudV: m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->guard_velocity;

				velocity airV = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->air_velocity;
				velocity airGuardV = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->airguard_velocity.x == UNSET_VELOCITY? airV:m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->airguard_velocity;

				velocity downV = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->down_velocity.x == UNSET_VELOCITY? airV:m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->down_velocity;
				if (m_pPlayer1->m_GetHitInfo.nGetHitedState == s_air)
				{
					if (m_pPlayer1->m_GetHitInfo.bIsGuarded){
						m_pPlayer1->xVel = airGuardV.x;
					}else{
						m_pPlayer1->xVel = airV.x;
					}
				}else if (m_pPlayer1->m_GetHitInfo.nGetHitedState == s_liedown)
				{
					m_pPlayer1->xVel = downV.x;
				}else{
					if (m_pPlayer1->m_GetHitInfo.bIsGuarded){
						m_pPlayer1->xVel = guardV.x;
					}else{
						m_pPlayer1->xVel = groudV.x;
					}
				}
			}
		}
		if (param.nParam == CPN_y)
		{
			float value = Execute(param.pInts);
			if (value)
			{
				velocity groudV = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->ground_velocity;
				velocity guardV = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->guard_velocity.x == UNSET_VELOCITY? groudV: m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->guard_velocity;

				velocity airV = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->air_velocity;
				velocity airGuardV = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->airguard_velocity.x == UNSET_VELOCITY? airV:m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->airguard_velocity;

				velocity downV = m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->down_velocity.x == UNSET_VELOCITY? airV:m_pPlayer1->m_GetHitInfo.CtrlHitDefConf->down_velocity;
				if (m_pPlayer1->m_GetHitInfo.nGetHitedState == s_air)
				{
					if (m_pPlayer1->m_GetHitInfo.bIsGuarded){
						m_pPlayer1->yVel = airGuardV.y;
					}else{
						m_pPlayer1->yVel = airV.y;
					}
				}else if (m_pPlayer1->m_GetHitInfo.nGetHitedState == s_liedown)
				{
					m_pPlayer1->yVel = downV.y;
				}else{
					if (m_pPlayer1->m_GetHitInfo.bIsGuarded){
						m_pPlayer1->yVel = guardV.y;
					}else{
						m_pPlayer1->yVel = groudV.y;
					}
				}
			}
		}
	}
}

void CControllerExecuter::PalFX(PLSTATE* state)
{
	m_pPlayer1->PreParePalFX(state->pPalFXinfo);
}

void CControllerExecuter::PlayerPush(PLSTATE* state)
{
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_value)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->SetPush(value);
		}
	}
}

void CControllerExecuter::PlaySnd(PLSTATE* state)
{
	int sndGroupno = 0, sndNo = 0;
	SndType type = SndPlayer;
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_SndGroupNo)
		{
			sndGroupno = Execute(param.pInts);
		}else if (param.nParam == CPN_SndNo)
		{
			sndNo = Execute(param.pInts);
		}else if (param.nParam == CPN_sndType)
		{
			type = (SndType)(int)Execute(param.pInts);
		}
	}
	m_pPlayer1->PrepareAudio(sndGroupno, sndNo, type);
}

void CControllerExecuter::PosAdd(PLSTATE* state)
{
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_x)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->MoveForward(value);
		}
		if (param.nParam == CPN_y)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->y = m_pPlayer1->y+value;
		}
	}
}

void CControllerExecuter::PosSet(PLSTATE* state)
{
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_x)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->x = value;
		}
		if (param.nParam == CPN_y)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->y = value;
		}
	}
}

void CControllerExecuter::Projectile(PLSTATE* state)
{
	m_pPlayer1->PrepareProj(state->pProjInfo, state->pConHDdef);
}

void CControllerExecuter::SelfState(PLSTATE* state)
{
	int stateNo =0;
	for (int i =0;i<state->nParamCount;i++)
	{
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_ctrl)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->SetCtrl((bool)(value));
		}
		if (param.nParam == CPN_value)
		{
			stateNo = Execute(param.pInts);
		}
	}
	m_pPlayer1->ChangeState(stateNo);
}

void CControllerExecuter::StateTypeSet(PLSTATE* state)
{
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_statetype)
		{
			char* value = ExecuteGetStr(param.pInts);
			if (value[0]=='a'||value[0]=='A')
			{
				m_pPlayer1->nStateType = s_air;
			}
			else if (value[0]=='c'||value[0]=='C')
			{
				m_pPlayer1->nStateType = s_crouch;
			}
			else if (value[0]=='s'||value[0]=='S')
			{
				m_pPlayer1->nStateType = s_stand;
			}
			else if (value[0]=='l'||value[0]=='L')
			{
				m_pPlayer1->nStateType = s_liedown;
			}else
			{
				SDL_assert(false);
			}
		}
		if (param.nParam == CPN_movetype)
		{
			char* value = ExecuteGetStr(param.pInts);
			if (value[0]=='i'||value[0]=='I')
			{
				m_pPlayer1->ChangeMoveType(m_idle);
			}
			else if (value[0]=='a'||value[0]=='A')
			{
				m_pPlayer1->ChangeMoveType(m_attack);
			}
			else if (value[0]=='h'||value[0]=='H')
			{
				m_pPlayer1->ChangeMoveType(m_hit);
			}
			else
			{
				SDL_assert(false);
			}
		}
		if (param.nParam == CPN_physics)
		{
			char* value = ExecuteGetStr(param.pInts);
			if (value[0]=='a'||value[0]=='A')
			{
				m_pPlayer1->nPhysic = p_air;
			}
			else if (value[0]=='c'||value[0]=='C')
			{
				m_pPlayer1->nPhysic = p_crouch;
			}
			else if (value[0]=='s'||value[0]=='S')
			{
				m_pPlayer1->nPhysic = p_stand;
			}
			else if (value[0]=='n'||value[0]=='N')
			{
				m_pPlayer1->nPhysic = p_none;
			}
			else
			{
				SDL_assert(false);
			}
		}
	}

}

void CControllerExecuter::NotHitBy(PLSTATE* state)
{
	m_pPlayer1->SetPropNotHitByTime(1);

	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_value)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->SetPropNotHitByFlag(value);
		}
		if (param.nParam == CPN_time)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->SetPropNotHitByTime(value);
		}
	}
}

void CControllerExecuter::Null(PLSTATE* state)
{
	//PrintMessage("time:%5d|ID %d: Null", CGameTimer::GetInstance()->GetGameTime(), m_pPlayer1->m_propID);
}

void CControllerExecuter::SuperPause(PLSTATE* state)
{
	PrintMessage("time:%5d|ID %d: SuperPause", CGameTimer::GetInstance()->GetGameTime(), m_pPlayer1->m_propID);
	int time  = 30;
	EnumAnimType animtype = AnimFightFX;
	int anim = -1;
	SndType sndtype = SndCommon;
	int sndg=-1, sndno=-1;
	int posx=0,posy=0;
	bool darken=1;
	float p2defmul = 0;
	int poweradd  = 0;
	bool unhittable = 1;

	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		switch (param.nParam)
		{
		case CPN_x:
			posx = Execute(param.pInts);
			break;
		case CPN_y:
			posy = Execute(param.pInts);
			break;
		case CPN_time:
			time = Execute(param.pInts);
			break;
		case CPN_animtype:
			animtype = (EnumAnimType)(int)Execute(param.pInts);
			break;
		case CPN_anim:
			anim = Execute(param.pInts);
			break;
		case CPN_sndType:
			sndtype = (SndType)(int)Execute(param.pInts);
			break;
		case CPN_SndGroupNo:
			sndg = Execute(param.pInts);
			break;
		case CPN_SndNo:
			sndno = Execute(param.pInts);
			break;
		case CPN_darken:
			darken = Execute(param.pInts);
			break;
		case CPN_p2defmul:
			p2defmul = Execute(param.pInts);
			break;
		case CPN_poweradd:
			poweradd = Execute(param.pInts);
			break;
		case CPN_unhittable:
			unhittable = Execute(param.pInts);
			break;
		default:
			continue;
		}
	}

	CEngine::GetInstance()->SetPropSuperPauseTime(time);
	CEngine::GetInstance()->SetPropSuperPauseDarken(darken);
	m_pPlayer1->SetPropIsSuperPause(true);
	m_pPlayer2->SetPropIsSuperPause(false);
	if (anim != -1)
	{
		m_pPlayer1->PrepareSuperAnim(anim, animtype, posx, posy);
	}
	if (sndg != -1 && sndno != -1)
	{
		m_pPlayer1->PrepareAudio(sndg, sndno, sndtype);
	}
	m_pPlayer1->ChangePower(poweradd);
}

void CControllerExecuter::TargetBind(PLSTATE* state)
{
	int bindTime = 1;
	int bindPosx=0, bindPosy=0;
	int bindID = -1;
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		switch (param.nParam)
		{
		case CPN_x:
			bindPosx = Execute(param.pInts);
			break;
		case CPN_y:
			bindPosy = Execute(param.pInts);
			break;
		case CPN_time:
			bindTime = Execute(param.pInts);
			break;
		case CPN_sysfv:
			bindID = Execute(param.pInts);
			break;
		default:
			continue;
		}
	}
	m_pPlayer1->nBindTargetID = bindID;
	m_pPlayer1->nTargetBindTime = bindTime;
	m_pPlayer1->mBindPos = ccp(bindPosx, bindPosy);
}

void CControllerExecuter::targetState(PLSTATE* state)
{
	int stateNo =0, id=-1;
	for (int i =0;i<state->nParamCount;i++)
	{
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_value)
		{
			stateNo = Execute(param.pInts);
		}else if (param.nParam == CPN_id)
		{
			id = Execute(param.pInts);
		}
	}
	m_pPlayer1->ChangeState(stateNo, false, true);
}

void CControllerExecuter::Turn(PLSTATE* state)
{
	m_pPlayer1->bRightFaced = !m_pPlayer1->bRightFaced;
}
void CControllerExecuter::VarAdd(PLSTATE* state)
{
	float value = 0;
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_value)
		{
			value = Execute(param.pInts);
			break;
		}
	}

	Sint32 valueIndex = 0;
	int curValue = 0;
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		valueIndex = Execute(param.pInts);
		
		switch (param.nParam)
		{
		case CPN_v:
			curValue = m_pPlayer1->GetVectorVar(valueIndex);
			m_pPlayer1->SetVectorVar(valueIndex, curValue+value);
			break;
		case CPN_fv:
			curValue = m_pPlayer1->GetVectorFVar(valueIndex);
			m_pPlayer1->SetVectorFVar(valueIndex, curValue+value);
			break;
		case CPN_sysv:
			curValue = m_pPlayer1->GetVectorSysVar(valueIndex);
			m_pPlayer1->SetVectorSysVar(valueIndex, curValue+value);
			break;
		case CPN_sysfv:
			curValue = m_pPlayer1->GetVectorSysFVar(valueIndex);
			m_pPlayer1->SetVectorSysFVar(valueIndex, curValue+value);
			break;

		default:
			continue;
		}
	}
}

void CControllerExecuter::VarSet(PLSTATE* state)
{
	float value = 0;
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_value)
		{
			value = Execute(param.pInts);
			break;
		}
	}

	Sint32 valueIndex = 0;
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		switch (param.nParam)
		{
		case CPN_v:
			valueIndex = Execute(param.pInts);
			m_pPlayer1->SetVectorVar(valueIndex, value);
			break;
		case CPN_fv:
			valueIndex = Execute(param.pInts);
			m_pPlayer1->SetVectorFVar(valueIndex, value);
			break;
		case CPN_sysv:
			valueIndex = Execute(param.pInts);
			m_pPlayer1->SetVectorSysVar(valueIndex, value);
			break;
		case CPN_sysfv:
			valueIndex = Execute(param.pInts);
			m_pPlayer1->SetVectorSysFVar(valueIndex, value);
			break;

		default:
			continue;
		}
	}
}

void CControllerExecuter::VelAdd(PLSTATE* state)
{
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_x)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->xVel = m_pPlayer1->xVel+value;
		}
		if (param.nParam == CPN_y)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->yVel = m_pPlayer1->yVel+value;
		}
	}
}

void CControllerExecuter::VelMul(PLSTATE* state)
{
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_x)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->xVel = m_pPlayer1->xVel*value;
		}
		if (param.nParam == CPN_y)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->yVel = m_pPlayer1->yVel*value;
		}
	}
}

void CControllerExecuter::VelSet(PLSTATE* state)
{
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_x)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->xVel = value;
		}
		if (param.nParam == CPN_y)
		{
			float value = Execute(param.pInts);
			m_pPlayer1->yVel = value;
		}
	}

}

void CControllerExecuter::Width(PLSTATE* state)
{
	int screenLeft=0, screenRight=0, playerback=0, playerFront=0;
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_screenBack)
		{
			screenLeft = Execute(param.pInts);
		}
		if (param.nParam == CPN_screenFront)
		{
			screenRight = Execute(param.pInts);
		}
		if (param.nParam == CPN_front)
		{
			playerFront = Execute(param.pInts);
		}
		if (param.nParam == CPN_back)
		{
			playerback = Execute(param.pInts);
		}
	}
	m_pPlayer1->SetPropScreenBack(screenLeft);
	m_pPlayer1->SetPropScreenFront(screenRight);
	m_pPlayer1->SetPropWidthBack(playerback);
	m_pPlayer1->SetPropWidthFront(playerFront);
}

void CControllerExecuter::AddCommandInput(PLSTATE* state)
{
	for(int i = 0;i<state->nParamCount;i++){
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_Command)
		{
			const char* command = ExecuteGetStr(param.pInts);
			m_pPlayer1->AddCommand(command);
		}
	}
}

void CControllerExecuter::Print(PLSTATE* state)
{
#ifdef __WIN32__
	int valueList[10];
	va_list ap = reinterpret_cast<va_list>((char*)valueList);
	int parCount = 0;

	char format[MAX_PATH];
	for (int i =0;i<state->nParamCount;i++)
	{
		CtrlParamStruct param = state->pContrlParma[i];
		if (param.nParam == CPN_text)
		{
			SDL_strlcpy(format, ExecuteGetStr(param.pInts), MAX_PATH);
		}
		else if (param.nParam == CPN_Param)
		{
			valueList[parCount++] = Execute(param.pInts);
		}
	}
	char logstr[MAX_PATH];
	SDL_vsnprintf(logstr, MAX_PATH, format, ap);
	char retvalue[MAX_PATH];
	SDL_snprintf(retvalue, MAX_PATH, "time:%d|id %d:<print>%s", CGameTimer::GetInstance()->GetGameTime(), m_pPlayer1->GetPropID(), logstr);
	PrintMessage(retvalue);
#endif
}
