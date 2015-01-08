/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/


#include "VirtualMachine.h"
#include "game.h"
#include "config/ConfigManager.h"
#include "StageManager.h"
#include "GameTimer.h"
#include "tool.h"

//Contructor
CVirtualMachine::CVirtualMachine()
	:isError(false)
{

}
//Destructor
CVirtualMachine::~CVirtualMachine()
{

}
//Sets pointers for get access to Player internal
void CVirtualMachine::SetPlayers(CPlayer *p1,CPlayer *p2)
{
	srand(SDL_GetTicks());
	m_pPlayer1=p1;
	m_pPlayer2=p2;
	m_curPlayer = p1;

	m_Stack.SetPropplayerID(p1->GetPropID());
	InitFunctTable();
}
//Sets the pointer to the Functions int this class
void CVirtualMachine::InitFunctTable()
{
	pFuncTable[OP_PUSH]=&CVirtualMachine::PushValue;
	pFuncTable[OP_POP]=&CVirtualMachine::PopValue;
	pFuncTable[OP_ADD]=&CVirtualMachine::AddOP;
	pFuncTable[OP_SUB]=&CVirtualMachine::SubOP;
	pFuncTable[OP_MUL]=&CVirtualMachine::MulOP;
	pFuncTable[OP_DIV]=&CVirtualMachine::DivOP;
	pFuncTable[OP_EQUAL]=&CVirtualMachine::EqualOP;
	pFuncTable[OP_ASSIGN]=&CVirtualMachine::Assign;
	pFuncTable[OP_NOTEQUAL]=&CVirtualMachine::NotEqual;
	pFuncTable[OP_LESS]=&CVirtualMachine::Less;
	pFuncTable[OP_GREATER]=&CVirtualMachine::Greater;
	pFuncTable[OP_LESSEQUAL]=&CVirtualMachine::LessEqual;
	pFuncTable[OP_GRAETEREQUAL]=&CVirtualMachine::GreaterEqual;
	pFuncTable[OP_INTERVALOP1]=&CVirtualMachine::InterValOP1;
	pFuncTable[OP_INTERVALOP2]=&CVirtualMachine::InterValOP2;
	pFuncTable[OP_INTERVALOP3]=&CVirtualMachine::InterValOP3;
	pFuncTable[OP_INTERVALOP4]=&CVirtualMachine::InterValOP4;
	pFuncTable[OP_INTERVALOP5]=&CVirtualMachine::InterValOP5;
	pFuncTable[OP_INTERVALOP6]=&CVirtualMachine::InterValOP6;
	pFuncTable[OP_INTERVALOP7]=&CVirtualMachine::InterValOP7;
	pFuncTable[OP_INTERVALOP8]=&CVirtualMachine::InterValOP8;
	pFuncTable[OP_LOGNOT]=&CVirtualMachine::LogNot;
	pFuncTable[OP_LOGAND]=&CVirtualMachine::LogAnd;
	pFuncTable[OP_LOGOR]=&CVirtualMachine::LogOr;
	pFuncTable[OP_LOGXOR]=&CVirtualMachine::LogXor;
	pFuncTable[OP_NOT]=&CVirtualMachine::Not;
	pFuncTable[OP_AND]=&CVirtualMachine::And;
	pFuncTable[OP_OR]=&CVirtualMachine::Or;
	pFuncTable[OP_XOR]=&CVirtualMachine::Xor;
	pFuncTable[OP_SQUARE]=&CVirtualMachine::Square;
	pFuncTable[OP_NEG]=&CVirtualMachine::Neg;
	pFuncTable[OP_MOD]=&CVirtualMachine::MODOP;

	pFuncTable[OP_LEFT]=&CVirtualMachine::LEFT;
	pFuncTable[OP_RIGHT]=&CVirtualMachine::RIGHT;

	pFuncTable[OP_Abs]=&CVirtualMachine::Abs;
	pFuncTable[OP_Acos]=&CVirtualMachine::Acos;
	pFuncTable[OP_AILevel]=&CVirtualMachine::AILevel;
	pFuncTable[OP_Alive]=&CVirtualMachine::Alive;
	pFuncTable[OP_Anim]=&CVirtualMachine::Anim;
	pFuncTable[OP_AnimElem]=&CVirtualMachine::AnimElem;
	pFuncTable[OP_AnimElemNo]=&CVirtualMachine::AnimeElemNo;
	pFuncTable[OP_AnimElemTime]=&CVirtualMachine::AnimeElemTime;
	pFuncTable[OP_AnimExist]=&CVirtualMachine::AnimExist;
	pFuncTable[OP_AnimTime]=&CVirtualMachine::AnimTime;
	pFuncTable[OP_Asin]=&CVirtualMachine::Asin;
	pFuncTable[OP_Atan]=&CVirtualMachine::Atan;
	pFuncTable[OP_AuthorName]=&CVirtualMachine::AuthorName;
	pFuncTable[OP_BackEdgeBodyDist]=&CVirtualMachine::BackEdgeBodyDist;
	pFuncTable[OP_BackEdgeDist]=&CVirtualMachine::BackEdgeDist;
	pFuncTable[OP_CanRecover]=&CVirtualMachine::CanRecover;
	pFuncTable[OP_Ceil]=&CVirtualMachine::Ceil;
	pFuncTable[OP_Command]=&CVirtualMachine::Command;
	pFuncTable[OP_Cond]=&CVirtualMachine::Const;
	pFuncTable[OP_Const]=&CVirtualMachine::Const;
	pFuncTable[OP_Const240p]=&CVirtualMachine::Const240p;
	pFuncTable[OP_Const480p]=&CVirtualMachine::Const480p;
	pFuncTable[OP_Const720p]=&CVirtualMachine::Const720p;
	pFuncTable[OP_Cos]=&CVirtualMachine::Cos;
	pFuncTable[OP_Ctrl]=&CVirtualMachine::Ctrl;
	pFuncTable[OP_DrawGame]=&CVirtualMachine::DrawGame;
	pFuncTable[OP_E]=&CVirtualMachine::E;
	pFuncTable[OP_Exp]=&CVirtualMachine::Exp;
	pFuncTable[OP_Facing]=&CVirtualMachine::Facing;
	pFuncTable[OP_Floor]=&CVirtualMachine::Floor;
	pFuncTable[OP_FrontEdgeBodyDist]=&CVirtualMachine::FrontEdgeBodyDist;
	pFuncTable[OP_FrontEdgeDist]=&CVirtualMachine::FrontEdgeDist;
	pFuncTable[OP_FVar]=&CVirtualMachine::FVar;
	pFuncTable[OP_GameHeight]=&CVirtualMachine::GameHeight;
	pFuncTable[OP_GameTime]=&CVirtualMachine::GameTime;
	pFuncTable[OP_GameWidth]=&CVirtualMachine::GameWidth;
	pFuncTable[OP_GetHitVar]=&CVirtualMachine::GetHitVar;
	pFuncTable[OP_HitCount]=&CVirtualMachine::HitCount;
	pFuncTable[OP_HitDefAttr]=&CVirtualMachine::HitDefAttr;//HitDefAttr
	pFuncTable[OP_HitFall]=&CVirtualMachine::HitFall;
	pFuncTable[OP_HitOver]=&CVirtualMachine::HitOver;
	pFuncTable[OP_HitPauseTime]=&CVirtualMachine::HitPauseTime;
	pFuncTable[OP_HitShakeOver]=&CVirtualMachine::HitShakeOver;
	pFuncTable[OP_HitVel]=&CVirtualMachine::HitVel;
	pFuncTable[OP_ID]=&CVirtualMachine::ID;
	pFuncTable[OP_IfElse]=&CVirtualMachine::IfElse;
	pFuncTable[OP_InGuardDist]=&CVirtualMachine::InGuardDist;
	pFuncTable[OP_IsHelper]=&CVirtualMachine::IsHelper;
	pFuncTable[OP_IsHomeTeam]=&CVirtualMachine::IsHomeTeam;
	pFuncTable[OP_Life]=&CVirtualMachine::Life;
	pFuncTable[OP_LifeMax]=&CVirtualMachine::LifeMax;
	pFuncTable[OP_Ln]=&CVirtualMachine::Ln;
	pFuncTable[OP_Log]=&CVirtualMachine::Log;
	pFuncTable[OP_Lose]=&CVirtualMachine::Lose;
	pFuncTable[OP_LoseKO]=&CVirtualMachine::LoseKO;
	pFuncTable[OP_LoseTime]=&CVirtualMachine::LoseTime;
	pFuncTable[OP_MatchNo]=&CVirtualMachine::MatchNo;
	pFuncTable[OP_MatchOver]=&CVirtualMachine::MatchOver;
	pFuncTable[OP_MoveContact]=&CVirtualMachine::MoveContact;
	pFuncTable[OP_MoveGuarded]=&CVirtualMachine::MoveGuarded;
	pFuncTable[OP_MoveHit]=&CVirtualMachine::MoveHit;
	pFuncTable[OP_MoveType]=&CVirtualMachine::MoveType;
	pFuncTable[OP_MoveReversed]=&CVirtualMachine::MoveReversed;
	pFuncTable[OP_Name]=&CVirtualMachine::Name;
	pFuncTable[OP_NumEnemy]=&CVirtualMachine::NumEnemy;
	pFuncTable[OP_NumExplod]=&CVirtualMachine::NumExplod;
	pFuncTable[OP_NumHelper]=&CVirtualMachine::NumHelper;
	pFuncTable[OP_NumPartner]=&CVirtualMachine::NumPartner;
	pFuncTable[OP_NumProj]=&CVirtualMachine::NumProj;
	pFuncTable[OP_NumProjID]=&CVirtualMachine::NumProjID;
	pFuncTable[OP_NumTarget]=&CVirtualMachine::NumTarget;
	pFuncTable[OP_P1Name]=&CVirtualMachine::P1Name;
	pFuncTable[OP_P2BodyDist]=&CVirtualMachine::P2BodyDist;
	pFuncTable[OP_P2Dist]=&CVirtualMachine::P2Dist;
	pFuncTable[OP_P2Life]=&CVirtualMachine::P2Life;
	pFuncTable[OP_P2MoveType]=&CVirtualMachine::P2MoveType;
	pFuncTable[OP_P2Name]=&CVirtualMachine::P2Name;
	pFuncTable[OP_P2StateNo]=&CVirtualMachine::P2StateNo;
	pFuncTable[OP_P2StateType]=&CVirtualMachine::P2StateType;
	pFuncTable[OP_P3Name]=&CVirtualMachine::P3Name;
	pFuncTable[OP_P4Name]=&CVirtualMachine::P4Name;
	pFuncTable[OP_PalNo]=&CVirtualMachine::PalNo;
	pFuncTable[OP_ParentDist]=&CVirtualMachine::ParentDist;
	pFuncTable[OP_Pi]=&CVirtualMachine::Pi;
	pFuncTable[OP_Pos]=&CVirtualMachine::Pos;
	pFuncTable[OP_Power]=&CVirtualMachine::Power;
	pFuncTable[OP_PowerMax]=&CVirtualMachine::PowerMax;
	pFuncTable[OP_PlayerIDExist]=&CVirtualMachine::PlayerIDExist;
	pFuncTable[OP_PrevStateNo]=&CVirtualMachine::PrevStateNo;//PrevStateNo
	pFuncTable[OP_ProjCancelTime]=&CVirtualMachine::ProjCancelTime;
	pFuncTable[OP_ProjContact]=&CVirtualMachine::ProjContact;
	pFuncTable[OP_ProjContactTime]=&CVirtualMachine::ProjContactTime;
	pFuncTable[OP_ProjGuarded]=&CVirtualMachine::ProjGuarded;
	pFuncTable[OP_ProjGuardedTime]=&CVirtualMachine::ProjGuardedTime;
	pFuncTable[OP_ProjHit]=&CVirtualMachine::ProjHit;
	pFuncTable[OP_ProjHitTime]=&CVirtualMachine::ProjHitTime;
	pFuncTable[OP_Random]=&CVirtualMachine::Random;
	pFuncTable[OP_RootDist]=&CVirtualMachine::RootDist;
	pFuncTable[OP_RoundNo]=&CVirtualMachine::RoundNo;
	pFuncTable[OP_RoundsExisted]=&CVirtualMachine::RoundsExisted;
	pFuncTable[OP_RoundState]=&CVirtualMachine::RoundState;
	pFuncTable[OP_ScreenPos]=&CVirtualMachine::ScreenPos;
	pFuncTable[OP_SelfAnimExist]=&CVirtualMachine::SelfAnimExist;
	pFuncTable[OP_Sin]=&CVirtualMachine::Sin;
	pFuncTable[OP_StateNo]=&CVirtualMachine::StateNo;
	pFuncTable[OP_StateType]=&CVirtualMachine::StateType;
	pFuncTable[OP_SysFVar]=&CVirtualMachine::SysFVar;
	pFuncTable[OP_SysVar]=&CVirtualMachine::SysVar;
	pFuncTable[OP_Tan]=&CVirtualMachine::Tan;
	pFuncTable[OP_TeamMode]=&CVirtualMachine::TeamMode;
	pFuncTable[OP_TeamSide]=&CVirtualMachine::TeamSide;
	pFuncTable[OP_TicksPerSecond]=&CVirtualMachine::TicksPerSecond;
	pFuncTable[OP_Time]=&CVirtualMachine::Time;
	pFuncTable[OP_TimeMod]=&CVirtualMachine::TimeMod;//TimeMod;
	pFuncTable[OP_UniqHitCount]=&CVirtualMachine::UniqHitCount;
	pFuncTable[OP_Var]=&CVirtualMachine::Var;
	pFuncTable[OP_Vel]=&CVirtualMachine::Vel;
	pFuncTable[OP_Win]=&CVirtualMachine::Win;
	pFuncTable[OP_WinKO]=&CVirtualMachine::WinKO;
	pFuncTable[OP_WinTime]=&CVirtualMachine::WinTime;
	pFuncTable[OP_WinPerfect]=&CVirtualMachine::WinPerfect;
	pFuncTable[OP_parent]=&CVirtualMachine::Parent;
	pFuncTable[OP_root]=&CVirtualMachine::Root;
	pFuncTable[OP_helper]=&CVirtualMachine::Helper;
	pFuncTable[OP_target]=&CVirtualMachine::Target;
	pFuncTable[OP_partner]=&CVirtualMachine::Partner;
	pFuncTable[OP_enemy]=&CVirtualMachine::Enemy;
	pFuncTable[OP_enemynear]=&CVirtualMachine::EnemyNear;
	pFuncTable[OP_playerid]=&CVirtualMachine::PlayerID;

}

void CVirtualMachine::NativeExecute(OpElement *pInst)
{
	if (pInst == NULL)
	{
		m_Stack.Push(0, "#");
		return;
	}
	Uint32 nCurrentIns = 0;
	isError = false;
	m_curPlayer = m_pPlayer1;
	while(pInst[nCurrentIns].n_OpCode!=OP_STOP)
	{
		if (isError)
		{
			PrintWaring("virtual machine reach bottom!");
			break;
		}
		pCurrentIns=&pInst[nCurrentIns];
		//Execute the 
		SDL_assert(this->pFuncTable[pInst[nCurrentIns].n_OpCode] != NULL);
		(this->*pFuncTable[pInst[nCurrentIns].n_OpCode])();
		nCurrentIns++;
	}
}

//Executes one instruction line
char* CVirtualMachine::ExecuteGetStr(OpElement *pInst)
{
	m_Stack.PrepairStack();
	NativeExecute(pInst);
	PopAllValue();
	m_Stack.ResetStack();
	return m_pop.string;
}

//Executes one instruction line
float CVirtualMachine::Execute(OpElement *pInst)
{
	m_Stack.PrepairStack();
	NativeExecute(pInst);
	PopAllValue();
	m_Stack.ResetStack();
	return m_pop.Value;
}
//Executes one instruction line
float CVirtualMachine::ExecuteForState(OpElement *pInst)
{
	m_Stack.PrepairStack();
	NativeExecute(pInst);
	PopAllValue();
	m_Stack.ResetStack();
	return m_pop.Value;
}

void CVirtualMachine::PopAllValue()
{
	int i = 0;
	while (m_Stack.m_BottomPos!= m_Stack.m_CurPos)
	{
		i++;
		if (i>1)
		{
			PrintWaring("PopAllValue to bottom!");
		}
		m_pop=m_Stack.Pop();
	}
}

//Pops a value from the stack
void CVirtualMachine::PopValue()
{
	m_pop=m_Stack.Pop();
}

void CVirtualMachine::PushValue()
{
	m_Stack.Push(pCurrentIns->Value,pCurrentIns->strValue);
}
//x+y
void CVirtualMachine::AddOP()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;

	m_pop.Value=temp1+temp2;
	//  PrintMessage("%f + %f = %f",temp1,temp2,m_pop.Value);
	m_Stack.Push(m_pop.Value,"#");

}
//x-y
void CVirtualMachine::SubOP()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;

	m_pop.Value=temp1-temp2;
	m_Stack.Push(m_pop.Value,"#");

}
//x*y
void CVirtualMachine::MulOP()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;

	m_pop.Value=temp1*temp2;
	m_Stack.Push(m_pop.Value,"#");

}
//x/y
void CVirtualMachine::DivOP()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;

	if (temp2 == 0)
	{
		m_Stack.Push(0,"#");
		isError = true;
	}else{
		m_pop.Value=temp1/temp2;
		m_Stack.Push(m_pop.Value,"#");
	}
}
//x==Y
void CVirtualMachine::EqualOP()
{
	char strTemp[MAX_PATH],strTemp1[MAX_PATH];

	PopValue();
	temp2=m_pop.Value;
	SDL_strlcpy(strTemp,m_pop.string, MAX_PATH);

	PopValue();
	temp1=m_pop.Value;
	SDL_strlcpy(strTemp1,m_pop.string, MAX_PATH);

	// command 比较特殊
	if(strTemp[0] == '@')
	{
		PrintWaring("op should be first");
		if(OPEN_ERROR)SDL_assert(false);
	}else if(strTemp1[0] == '@')
	{
		if (SDL_strcasecmp("@command", strTemp1)==0)
		{
			m_Stack.Push(m_curPlayer->IsCommandInput(strTemp),"#");
		}else if (SDL_strcasecmp("@hitdefatttr", strTemp1)==0)
		{
			Sint32 needhitattr = (Sint32)temp2;
			Sint32 attr = (Sint32)temp1;
			Sint32 self = (needhitattr&attr&HitDef_Attr_STATE_MASK);
			Sint32 atk = (needhitattr&attr&HitDef_Attr_ATK_MASK);
			m_Stack.Push(self&&atk,"#");
		}else{
			m_Stack.Push(0,"#");
		}
		
	}else if(strTemp[0] != '#' && strTemp1[0] != '#')
	{
		// 字符串
		if( SDL_strcasecmp(strTemp,strTemp1)==0)
		{
			m_Stack.Push(1,"#");
		}
		else
			m_Stack.Push(0,"#");
	}else{
		if(temp1==temp2)
			m_pop.Value=1;
		else
			m_pop.Value=0;
		m_Stack.Push(m_pop.Value,"#");
	}

}

void CVirtualMachine::Assign()
{
	PopValue();
	float value = m_pop.Value;
	PopValue();
	OpElement* curIns = this->pCurrentIns;
	OpElement* varOpType = curIns - 2;
	OpElement* varValue = curIns - 3;
	int valueIndex = varValue->Value;
	switch (varOpType->n_OpCode)
	{
	case OP_Var:
		m_curPlayer->SetVectorVar(valueIndex, value);
		break;
	case OP_FVar:
		m_curPlayer->SetVectorFVar(valueIndex, value);
		break;
	case OP_SysVar:
		m_curPlayer->SetVectorSysVar(valueIndex, value);
		break;
	case OP_SysFVar:
		m_curPlayer->SetVectorSysFVar(valueIndex, value);
		break;
	default:
		break;
	}
	m_Stack.Push(value, "#");
}
//x!=y
void CVirtualMachine::NotEqual()
{
	char strTemp[MAX_PATH],strTemp1[MAX_PATH];

	PopValue();
	temp2=m_pop.Value;
	SDL_strlcpy(strTemp,m_pop.string, MAX_PATH);

	PopValue();
	temp1=m_pop.Value;
	SDL_strlcpy(strTemp1,m_pop.string, MAX_PATH);

	// command 比较特殊
	if(strTemp[0] == '@')
	{
		PrintWaring("op should be first");
		if(OPEN_ERROR)SDL_assert(false);
	}else if(strTemp1[0] == '@')
	{
		if (SDL_strcasecmp("@command", strTemp1)==0)
		{
			/*if (SDL_strcasecmp(strTemp, "holdfwd")==0)
			{
			PrintMessage("");
			}*/
			m_Stack.Push(!m_curPlayer->IsCommandInput(strTemp),"#");
		}
		if (SDL_strcasecmp("@hitdefatttr", strTemp1)==0)
		{
			// not hit by
			Uint32 selfStateNeed = ~((Sint32)temp2 & HitDef_Attr_STATE_MASK);
			bool stateMatch = (Sint32)temp1&HitDef_Attr_STATE_MASK&selfStateNeed;
			if (!stateMatch)
			{
				m_Stack.Push(0,"#");
			}else{
				Uint32 atkNeed = ~((Sint32)temp2 & HitDef_Attr_ATK_MASK);
				bool atkMatch = (Sint32)temp1&HitDef_Attr_ATK_MASK&atkNeed;
				m_Stack.Push(stateMatch&&atkMatch,"#");
			}
		}

	}else if(strTemp[0] != '#' && strTemp1[0] != '#')
	{
		// 字符串
		if( strcmp(strTemp,strTemp1)==0)
		{
			m_Stack.Push(0,"#");
		}
		else
			m_Stack.Push(1,"#");
	}else{
		if(temp1==temp2)
			m_pop.Value=0;
		else
			m_pop.Value=1;
		m_Stack.Push(m_pop.Value,"#");
	}
}
//x<y
void CVirtualMachine::Less()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	if(temp1<temp2)
		m_pop.Value=1;
	else
		m_pop.Value=0;
	m_Stack.Push(m_pop.Value,"#");
}
//x>y
void CVirtualMachine::Greater()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	if(temp1>temp2)
		m_pop.Value=1;
	else
		m_pop.Value=0;
	m_Stack.Push(m_pop.Value,"#");

}
//x<=y
void CVirtualMachine::LessEqual()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	if(temp1<=temp2)
		m_pop.Value=1;
	else
		m_pop.Value=0;
	m_Stack.Push(m_pop.Value,"#");
}

void CVirtualMachine::GreaterEqual()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	if(temp1>=temp2)
		m_pop.Value=1;
	else
		m_pop.Value=0;
	m_Stack.Push(m_pop.Value,"#");
}

//x=[y,z]
void CVirtualMachine::InterValOP1()
{
	//Get Values from stack
	PopValue();
	temp3=m_pop.Value;
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	m_pop.Value=0;
	if( (temp1 >= temp2) && (temp1 <= temp3) )
		m_pop.Value=1;
	m_Stack.Push(m_pop.Value,"#");
}

//x=[y,z)
void CVirtualMachine::InterValOP2()
{
	PopValue();
	temp3=m_pop.Value;
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	m_pop.Value=0;
	if( (temp1 >= temp2) && (temp1 < temp3) )
		m_pop.Value=1;
	m_Stack.Push(m_pop.Value,"#");
}

//x=(y,z]
void CVirtualMachine::InterValOP3()
{
	PopValue();
	temp3=m_pop.Value;
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	m_pop.Value=0;
	if( (temp1 > temp2) && (temp1 <= temp3) )
		m_pop.Value=1;
	m_Stack.Push(m_pop.Value,"#");
}

//x=(y,z)
void CVirtualMachine::InterValOP4()
{
	PopValue();
	temp3=m_pop.Value;
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	m_pop.Value=0;
	if( (temp1 > temp2) && (temp1 < temp3) )
		m_pop.Value=1;
	m_Stack.Push(m_pop.Value,"#");
}

//x!=[y,z]
void CVirtualMachine::InterValOP5()
{
	//Get Values from stack
	PopValue();
	temp3=m_pop.Value;
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	m_pop.Value=0;
	//(x < y) || (x > z)
	if( (temp1 < temp2) || (temp1 > temp3) )
		m_pop.Value=1;
	m_Stack.Push(m_pop.Value,"#");
}

//x!=[y,z)
void CVirtualMachine::InterValOP6()
{
	PopValue();
	temp3=m_pop.Value;
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	m_pop.Value=0;
	if( (temp1 < temp2) || (temp1 >= temp3) )
		m_pop.Value=1;
	m_Stack.Push(m_pop.Value,"#");
}

//x!=(y,z]
void CVirtualMachine::InterValOP7()
{
	PopValue();
	temp3=m_pop.Value;
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	m_pop.Value=0;
	if( (temp1 <= temp2) || (temp1 > temp3) )
		m_pop.Value=1;
	m_Stack.Push(m_pop.Value,"#");
}

//x!=(y,z)
void CVirtualMachine::InterValOP8()
{
	PopValue();
	temp3=m_pop.Value;
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	m_pop.Value=0;
	if( (temp1 >= temp2) && (temp1 <= temp3) )
		m_pop.Value=1;
	m_Stack.Push(m_pop.Value,"#");
}


void CVirtualMachine::LogNot()
{
	PopValue();
	temp1=m_pop.Value;
	if(temp1==0)
		m_Stack.Push(1,"#");
	else
		m_Stack.Push(0,"#");
}

void CVirtualMachine::LogAnd()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	if( temp1>0 && temp2>0)
		m_Stack.Push(1,"#");
	else
		m_Stack.Push(0,"#"); 
}

void CVirtualMachine::LogOr()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	if( temp1>0 || temp2>0)
		m_Stack.Push(1,"#");
	else
		m_Stack.Push(0,"#"); 
}

void CVirtualMachine::LogXor()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	if( temp1>0  && temp2==0)
		m_Stack.Push(1,"#");
	else if ( temp1==0  && temp2>0)
		m_Stack.Push(1,"#"); 
	else
		m_Stack.Push(0,"#"); 
}

void CVirtualMachine::Not()
{
	PopValue();
	temp1=m_pop.Value;
	temp1=~(int)temp1;
	m_Stack.Push(temp1,"#");
}

void CVirtualMachine::And()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	temp1=(int)temp1 & (int)temp2;
	m_Stack.Push(temp1,"#");
}

void CVirtualMachine::Or()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	temp1=(int)temp1 | (int)temp2;
	m_Stack.Push(temp1,"#");
}

void CVirtualMachine::Xor()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	temp1=(float)((int)temp1 ^ (int)temp2);
	m_Stack.Push(temp1,"#");

}

//Square x^y
void CVirtualMachine::Square()
{
	PopValue();
	temp2=m_pop.Value;
	PopValue();
	temp1=m_pop.Value;
	temp1=pow(temp1,temp2);
	m_Stack.Push(temp1,"#");
}
//ABS
void CVirtualMachine::Abs()
{
	PopValue();
	temp1=m_pop.Value;
	temp1=fabs(temp1);
	m_Stack.Push(temp1,"#");

}
//Negate
void CVirtualMachine::Neg()
{
	PopValue();
	temp1=m_pop.Value;
	temp1=-temp1;
	m_Stack.Push(temp1,"#");
}
void CVirtualMachine::MODOP()
{
	int nDividend,nDivisor;
	PopValue();
	nDivisor=(int)m_pop.Value;
	PopValue();
	nDividend=(int)m_pop.Value;
	if (nDivisor==0)
	{
		m_Stack.Push(0,"#");
		isError = true;
	}else{
		nDividend=nDividend % nDivisor;
		m_Stack.Push(nDividend,"#");
	}
}

void CVirtualMachine::LEFT()
{
	PrintWaring("LEFT should not in trigger");
}
void CVirtualMachine::RIGHT()
{
	PrintWaring("RIGHT should not in trigger");
}

void CVirtualMachine::Acos()
{
	PopValue();
	temp1=m_pop.Value;
	temp1=acos(temp1);
	m_Stack.Push(temp1,"#");
}

void CVirtualMachine::AILevel()
{
	m_Stack.Push((float)m_curPlayer->GetPropAILevel(),"#");
}

//Alive
void CVirtualMachine::Alive()
{
	if(m_curPlayer->IsPlayerAlive())
		m_Stack.Push(1.0f,"#");
	else
		m_Stack.Push(0.0f,"#");
}

//Anime
void CVirtualMachine::Anim()
{
	m_Stack.Push((float)m_curPlayer->GetAnim(),"#");
}

//Anime Elem
void CVirtualMachine::AnimElem()
{
	//throw CError("AnimElem is replace by AnimElemTime");
}
//AnimElemNo(exprs)
void CVirtualMachine::AnimeElemNo()
{   
	ActionElement* tActionElement;
	tActionElement=m_curPlayer->GetCurrAnim();

	int nTimeOffset=0;
	int nTimeCheck=0;
	int nTimeToElement=0;

	PopValue();
	nTimeOffset=(int)m_pop.Value;

	nTimeCheck=nTimeOffset+m_curPlayer->m_Anim->nCurrTime;

	if(nTimeCheck > tActionElement->nCompletAnimTime)
	{
		m_Stack.Push(0,"#");
		return;
	}

	//now check on which elemt the time offset is  
	for (int i=0;i<tActionElement->nNumberOfElements;i++)
	{
		nTimeToElement+=tActionElement->AnimationElement[i].nDuringTime;
		if(nTimeToElement >= nTimeCheck)
		{
			//Now we had found wich elemt it would be on this time
			m_Stack.Push((float)i+1,"#");
			return;
		}
	}
	m_Stack.Push(0,"#");
}

//AnimElemTime(exprs)
void CVirtualMachine::AnimeElemTime()
{
	int nElementToCheck;
	PopValue();
	nElementToCheck=(int)m_pop.Value;

	ActionElement* tActionElement;
	tActionElement=m_curPlayer->GetCurrAnim();
	Sint32 nTimeToElement=0;
	//now check on which elemt the time offset is  
	for (int i=0;i<tActionElement->nNumberOfElements;i++)
	{
		if(i + 1 == nElementToCheck)
		{
			break;
		}
		nTimeToElement+=tActionElement->AnimationElement[i].nDuringTime;
	}
	
	Sint32 curTime = m_curPlayer->m_Anim->nCurrTime;
	m_Stack.Push(curTime-nTimeToElement,"#");
}

//AnimExist(exprs)
void CVirtualMachine::AnimExist()
{
	s32 nAnim;
	PopValue();
	nAnim=(s32)m_pop.Value;
	//If != NULL psuh true else push false
	if(m_curPlayer->IsAnimAviable(nAnim))
		m_Stack.Push(1.0,"#");
	else
		m_Stack.Push(0.0,"#");

}

//AnimeTime
void CVirtualMachine::AnimTime()
{
	Sint32 nAnimTime = m_curPlayer->AnimTime();
	m_Stack.Push((float)nAnimTime,"#");
}

//Asin(expr)
void CVirtualMachine::Asin()
{
	PopValue();
	temp1=m_pop.Value;
	temp1=asin(temp1);
	m_Stack.Push(temp1,"#");

}

//Atan (expr)
void CVirtualMachine::Atan()
{
	PopValue();
	temp1=m_pop.Value;
	temp1=atan(temp1);
	m_Stack.Push(temp1,"#");
}

//Author Name
void CVirtualMachine::AuthorName()
{
	m_Stack.Push(0,m_curPlayer->m_Config->GetChar("Info.author"));
}

//BackEdgeBodyDist
void CVirtualMachine::BackEdgeBodyDist()
{
	Sint32 back = m_curPlayer->GetPlayerBack();
	float cameraX = CStageManager::GetInstance()->GetPropCameraPosX();
	Sint32 GameWidth = Common_GetDesiginWidth();
	float dist;
	if (m_curPlayer->bRightFaced)
	{
		dist = m_curPlayer->x - back - (cameraX - GameWidth*0.5);
	}else
	{
		dist = (cameraX + GameWidth*0.5) - (m_curPlayer->x + back);
	}
	m_Stack.Push(dist,"#");

}
//BackEdgeDist
void CVirtualMachine::BackEdgeDist()
{
	float cameraX = CStageManager::GetInstance()->GetPropCameraPosX();
	Sint32 GameWidth =  Common_GetDesiginWidth();
	float dist;
	if (m_curPlayer->bRightFaced)
	{
		dist = m_curPlayer->x - (cameraX - GameWidth*0.5);
	}else
	{
		dist = (cameraX + GameWidth*0.5) - (m_curPlayer->x);
	}
	m_Stack.Push(dist,"#");
}
//CanRecover
void CVirtualMachine::CanRecover()
{
	//Push false for the moment
	m_Stack.Push(0,"#");    

}

//Ceil
void CVirtualMachine::Ceil()
{
	PopValue();
	temp1=m_pop.Value;
	temp1=ceil(temp1);
	m_Stack.Push(temp1,"#");
}

//Command
void CVirtualMachine::Command()
{
	m_Stack.Push(0,"@command");
}

//Const
void CVirtualMachine::Const()
{
	PopValue();
	const char* temp1=m_pop.string;
	float value = m_curPlayer->GetConfigFloat(temp1);
	m_Stack.Push(value,"#");
}

//Const
void CVirtualMachine::Const240p()
{
	PopValue();
	float value = m_pop.Value;
	float GameHeight = Common_GetDesiginHeight();
	float ret = value * 240 / GameHeight;
	m_Stack.Push(ret,"#");
}

//Const
void CVirtualMachine::Const480p()
{
	PopValue();
	float value = m_pop.Value;
	float GameHeight = Common_GetDesiginHeight();;
	float ret = value * 480 / GameHeight;
	m_Stack.Push(ret,"#");
}

//Const
void CVirtualMachine::Const720p()
{
	PopValue();
	float value = m_pop.Value;
	float GameHeight = Common_GetDesiginHeight();
	float ret = value * 720 / GameHeight;
	m_Stack.Push(ret,"#");
}

//cosinus
void CVirtualMachine::Cos()
{
	PopValue();
	temp1=m_pop.Value;
	temp1=cos(temp1);
	m_Stack.Push(temp1,"#");
}

//Check control of player
void CVirtualMachine::Ctrl()
{
	if(m_curPlayer->IsCtrl())
		m_Stack.Push(1.0,"#");
	else
		m_Stack.Push(0.0,"#");
}

//DrawGame TODO:Complete this
void CVirtualMachine::DrawGame()
{
	m_Stack.Push(0.0,"#");
}

void CVirtualMachine::E()
{
	m_Stack.Push(2.71828182845904523536f,"#");
}
//Exp to e
void CVirtualMachine::Exp()
{
	PopValue();
	temp1=m_pop.Value;
	temp1=pow(2.71828182f,temp1);
	m_Stack.Push(temp1,"#");
}

//retunr the facing direction
void CVirtualMachine::Facing()
{
	if(m_curPlayer->bRightFaced)
		m_Stack.Push(1.0f,"#");
	else
		m_Stack.Push(-1.0f,"#");
}

//Floor
void CVirtualMachine::Floor()
{
	PopValue();
	temp1=m_pop.Value;
	temp1=floor(temp1);
	m_Stack.Push(temp1,"#");
}

//FrontEdgeBodyDist
void CVirtualMachine::FrontEdgeBodyDist()
{
	Sint32 front;
	if (m_curPlayer->nStateType == s_air)
	{
		front = m_curPlayer->m_Config->GetInt("Size.air.front");
	}else
	{
		front = m_curPlayer->m_Config->GetInt("Size.ground.front");
	}
	float cameraX = CStageManager::GetInstance()->GetPropCameraPosX();
	Sint32 GameWidth =  Common_GetDesiginWidth();
	float dist;
	if (m_curPlayer->bRightFaced)
	{
		dist = (cameraX + GameWidth*0.5) - (m_curPlayer->x + front);
	}else
	{
		dist = m_curPlayer->x - front - (cameraX - GameWidth*0.5);
	}
	m_Stack.Push(dist,"#");
}

//FrontEdgeDist
void CVirtualMachine::FrontEdgeDist()
{
	float cameraX = CStageManager::GetInstance()->GetPropCameraPosX();
	Sint32 GameWidth =  Common_GetDesiginWidth();
	float dist;
	if (m_curPlayer->bRightFaced)
	{
		dist = (cameraX + GameWidth*0.5) - (m_curPlayer->x);
	}else
	{
		dist = m_curPlayer->x - (cameraX - GameWidth*0.5);
	}
	m_Stack.Push(dist,"#");
}

void CVirtualMachine::FVar()
{
	PopValue();
	float value = m_curPlayer->GetVectorFVar((Uint32)m_pop.Value);
	m_Stack.Push(value,"#");
}

void CVirtualMachine::GameHeight()
{
	Sint32 GameHeight = Common_GetDesiginHeight();
	m_Stack.Push(GameHeight,"#");
}

//GameTime
void CVirtualMachine::GameTime()
{
	Uint32 tick = CGameTimer::GetInstance()->GetGameTime();
	m_Stack.Push(tick,"#");
}

void CVirtualMachine::GameWidth()
{
	Sint32 gameWidth =  Common_GetDesiginWidth();
	m_Stack.Push(gameWidth,"#");
}

//GetHitVar
void CVirtualMachine::GetHitVar()
{
	char strTemp[MAX_PATH];
	PopValue();
	temp1=m_pop.Value;
	SDL_strlcpy(strTemp,m_pop.string, MAX_PATH);
	if (!m_curPlayer->m_GetHitInfo.bIsHitDefConfSet)
	{
		m_Stack.Push(0,"#");
		return;
	}

	if ( (SDL_strcasecmp("xveladd", strTemp)== 0) || (SDL_strcasecmp("yveladd", strTemp) == 0) )
	{
		if(OPEN_ERROR)SDL_assert(false);
	}
	else if (SDL_strcasecmp("type", strTemp) == 0)
	{
		if (m_curPlayer->m_GetHitInfo.nGetHitedState == s_air)
		{
			Sint32 ground_type = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->ground_type;
			Sint32 airtype = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->air_type == -1?ground_type:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->air_type;
			m_Stack.Push(airtype,"#");
		}
		else{
			Sint32 ground_type = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->ground_type;
			m_Stack.Push(ground_type,"#");
		}
	}
	else if (SDL_strcasecmp("animtype", strTemp) == 0)
	{
		Sint32 groundAnim = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->animtype;
		Sint32 airAnim = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->air_animtype == -1 ?groundAnim:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->air_animtype;
		Sint32 fallAnim = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->fall_animtype == -1 ?airAnim:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->fall_animtype;
		Sint32 anim;
		if (m_curPlayer->m_GetHitInfo.nGetHitedState == s_air)
		{
			anim = airAnim;
		}
		else if (m_curPlayer->m_GetHitInfo.nGetHitedState == s_liedown)
		{
			anim = fallAnim;
		}
		else{
			anim = groundAnim;
		}
		m_Stack.Push(anim,"#");
	}
	else if (SDL_strcasecmp("airtype", strTemp) == 0)
	{
		Sint32 ground_type = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->ground_type;
		Sint32 airtype = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->air_type == -1?ground_type:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->air_type;
		m_Stack.Push(airtype,"#");
	}
	else if (SDL_strcasecmp("groundtype", strTemp) == 0)
	{
		Sint32 ground_type = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->ground_type;
		m_Stack.Push(ground_type,"#");
	}
	else if (SDL_strcasecmp("damage", strTemp) == 0)
	{
		if (m_curPlayer->m_GetHitInfo.bIsGuarded){
			//m_Stack.Push(m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_damage,"#");
			m_Stack.Push(0,"#");
		}else{
			//m_Stack.Push(m_curPlayer->m_GetHitInfo.CtrlHitDefConf->hit_damage,"#");
			m_Stack.Push(0,"#");
		}
	}
	else if (SDL_strcasecmp("hitcount", strTemp) == 0 ||SDL_strcasecmp("#hitcount", strTemp) == 0)
	{
		m_Stack.Push(m_curPlayer->m_GetHitInfo.nCombo,"#");
	}
	else if (SDL_strcasecmp("fallcount", strTemp) == 0)
	{
		m_Stack.Push(m_curPlayer->m_GetHitInfo.nFallCount,"#");
	}
	else if (SDL_strcasecmp("hitshaketime", strTemp) == 0)
	{
		m_Stack.Push(m_curPlayer->m_GetHitInfo.nShakeTime,"#");
	}
	else if (SDL_strcasecmp("hittime", strTemp) == 0)
	{
		m_Stack.Push(m_curPlayer->m_GetHitInfo.nGetHitTime,"#");
	}
	else if (SDL_strcasecmp("slidetime", strTemp) == 0)
	{
		OpElement* ground = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->ground_slidetime;
		OpElement* guard = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_slidetime == NULL ?ground:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_slidetime;
		if (m_curPlayer->m_GetHitInfo.bIsGuarded){
			float vlaue = Execute(guard);
			float shaketime = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_shake_time;
			m_Stack.Push(vlaue-shaketime,"#");
		}else{
			float vlaue = Execute(ground);
			float shaketime = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->shake_time;
			m_Stack.Push(vlaue-shaketime,"#");
		}
	}
	else if (SDL_strcasecmp("ctrltime", strTemp) == 0)
	{
		OpElement* ground = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->ground_slidetime;
		OpElement* guard = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_slidetime == NULL ?ground:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_slidetime;

		OpElement* guard_ctrltime = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_ctrltime == NULL ?ground:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_ctrltime;;
		OpElement* airguard_ctrltime = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->airguard_ctrltime == NULL ?guard_ctrltime:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->airguard_ctrltime;
		if (m_curPlayer->m_GetHitInfo.bIsGuarded){
			if (m_curPlayer->m_GetHitInfo.nGetHitedState == s_air)
			{
				float vlaue = Execute(airguard_ctrltime);
				m_Stack.Push(vlaue,"#");
			}else
			{
				float vlaue = Execute(guard_ctrltime);
				m_Stack.Push(vlaue,"#");
			}
			
		}else{
			m_Stack.Push(0,"#");
		}
	}
	else if (SDL_strcasecmp("xvel", strTemp) == 0)
	{
		velocity groudV = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->ground_velocity;
		velocity guardV = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_velocity.x == UNSET_VELOCITY? groudV: m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_velocity;

		velocity airV = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->air_velocity;
		velocity airGuardV = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->airguard_velocity.x == UNSET_VELOCITY? airV:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->airguard_velocity;

		velocity downV = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->down_velocity.x == UNSET_VELOCITY? airV:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->down_velocity;
		if (m_curPlayer->m_GetHitInfo.nGetHitedState == s_air)
		{
			if (m_curPlayer->m_GetHitInfo.bIsGuarded){
				m_Stack.Push(airGuardV.x,"#");
			}else{
				m_Stack.Push(airV.x,"#");
			}

		}else if (m_curPlayer->m_GetHitInfo.nGetHitedState == s_liedown)
		{
			m_Stack.Push(downV.x,"#");
		}else{
			if (m_curPlayer->m_GetHitInfo.bIsGuarded){
				m_Stack.Push(guardV.x,"#");
			}else{
				m_Stack.Push(groudV.x,"#");
			}
		}
	}
	else if (SDL_strcasecmp("yvel", strTemp) == 0)
	{
		velocity groudV = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->ground_velocity;
		velocity guardV = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_velocity.x == UNSET_VELOCITY? groudV: m_curPlayer->m_GetHitInfo.CtrlHitDefConf->guard_velocity;

		velocity airV = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->air_velocity;
		velocity airGuardV = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->airguard_velocity.x == UNSET_VELOCITY? airV:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->airguard_velocity;
		velocity downV = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->down_velocity.x == UNSET_VELOCITY? airV:m_curPlayer->m_GetHitInfo.CtrlHitDefConf->down_velocity;
		if (m_curPlayer->m_GetHitInfo.nGetHitedState == s_air)
		{
			if (m_curPlayer->m_GetHitInfo.bIsGuarded){
				m_Stack.Push(airGuardV.y,"#");
			}else{
				m_Stack.Push(airV.y,"#");
			}

		}else if (m_curPlayer->m_GetHitInfo.nGetHitedState == s_liedown)
		{
			m_Stack.Push(downV.y,"#");
		}else{
			if (m_curPlayer->m_GetHitInfo.bIsGuarded){
				m_Stack.Push(guardV.y,"#");
			}else{
				m_Stack.Push(groudV.y,"#");
			}
		}
	}
	else if (SDL_strcasecmp("yaccel", strTemp) == 0)
	{
		float yaccel = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->yaccel;
		m_Stack.Push(yaccel,"#");
	}
	else if (SDL_strcasecmp("fall", strTemp) == 0)
	{
		Sint32 fall = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->fall;
		m_Stack.Push(fall,"#");
	}
	else if (SDL_strcasecmp("fall.damage", strTemp) == 0)
	{
		Sint32 value = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->fall_damage;
		m_Stack.Push(value,"#");
	}
	else if (SDL_strcasecmp("fall.xvel", strTemp) == 0)
	{
		float value = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->fall_xvelocity;
		m_Stack.Push(value,"#");
	}
	else if (SDL_strcasecmp("fall.yvel", strTemp) == 0)
	{
		float value = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->fall_yvelocity;
		m_Stack.Push(value,"#");
	}
	else
	{
		PrintMessage(" GetHitVar not deal %s", strTemp);
		PrintMessage("ID %d|%4d: GetHitVar not deal %s", m_pPlayer1->GetPropID(), CGameTimer::GetInstance()->GetGameTime(), strTemp);
		m_Stack.Push(0,"#");
	}
	
}

void CVirtualMachine::HitCount()
{
	//TODO:Push the correct value on stack
	// is the same name with gethitvar(hitcount)
	m_Stack.Push(0,"#hitcount");

}

void CVirtualMachine::HitDefAttr()
{

	Uint32 hitattr = 0;
	if (m_curPlayer->m_HitInfo.bIsHitDefConfSet)
	{
		hitattr = m_curPlayer->m_HitInfo.CtrlHitDefConf->attr;
	}
	m_Stack.Push(hitattr,"@hitdefatttr");
}


void CVirtualMachine::HitFall() 
{
	if (m_curPlayer->m_GetHitInfo.bIsHitDefConfSet)
	{
		bool hitfall = m_curPlayer->m_GetHitInfo.CtrlHitDefConf->fall;
		m_Stack.Push(hitfall,"#");
	}else{
		m_Stack.Push(0,"#");
	}
}

void CVirtualMachine::HitOver()
{
	if (m_curPlayer->m_GetHitInfo.bIsHitDefConfSet)
	{
		if(m_curPlayer->m_GetHitInfo.nGetHitTime >= 0)
		{
			m_Stack.Push(0,"#");
		}else{
			m_Stack.Push(1,"#");
		}
	}else{
		m_Stack.Push(1,"#");
	}
}

void CVirtualMachine::HitPauseTime()
{
	if (m_curPlayer->m_HitInfo.bIsHited)
	{
		m_Stack.Push(m_curPlayer->m_HitInfo.nPauseTime,"#");
	}else
	{
		m_Stack.Push(0,"#");
	}
}

void CVirtualMachine::HitShakeOver()
{

	if (m_curPlayer->m_GetHitInfo.bIsHitDefConfSet)
	{
		// because first tick, we should run once the state,so shake p2 after run fsm,but we also think it's shake begin
		// so when time=0,IsShake return false,but HitShakeOver also false
		/*bool isShake = m_curPlayer->IsShake();
		m_Stack.Push(!isShake,"#");*/
		bool isShakeBegin = m_curPlayer->m_GetHitInfo.nShakeTime >0;
		m_Stack.Push(!isShakeBegin,"#");

	}else{
		m_Stack.Push(1,"#");
	}
}

//HitVel [component]
void CVirtualMachine::HitVel()
{
	PopValue();
	temp1=m_pop.Value;

	//Pop the component value
	//1==X 2==y
	m_Stack.Push(0,"#");
}

//ID return the ID number of the player
void CVirtualMachine::ID()
{
	m_Stack.Push((float)m_curPlayer->m_propID,"#");
}

//IfElse(exp_cond,exp_true,exp_false)#
void CVirtualMachine::IfElse()
{
	PopValue();
	temp3=m_pop.Value;
	//exp_true
	PopValue();
	temp2=m_pop.Value;
	//exp_cond
	PopValue();
	temp1=m_pop.Value;

	if(temp1==1.0f)
		m_Stack.Push(temp2,"#");
	else
		m_Stack.Push(temp3,"#");
}

/*        InGuardDist 
Returns 1 if the player is within guarding distance of an opponent's physicalor projectile attack.
The guarding distance is the value of the guard.dist parameter of the
opponent's HitDef. Returns 0 if out of guard distance, or the opponent is not attacking.
*/
void CVirtualMachine::InGuardDist()
{
	int isindis = m_curPlayer->isGuardDist();
	m_Stack.Push(isindis,"#");
}

//Is helper
void CVirtualMachine::IsHelper()
{
	PopValue();
	int helperid = m_pop.Value;
	if (helperid == -1)
	{
		m_Stack.Push(m_curPlayer->m_type == PLAYER_HELPER, "#");
	}else{
		if(m_curPlayer->GetPropID() == helperid && m_curPlayer->m_type == PLAYER_HELPER)
		{
			m_Stack.Push(1,"#");
		}else{
			m_Stack.Push(0,"#");
		}
	}
}

//IsHomeTeam
void CVirtualMachine::IsHomeTeam()
{
	m_Stack.Push(0,"#");
}
//return the life of the player
void CVirtualMachine::Life()
{
	m_Stack.Push((float)m_curPlayer->GetPropLife(),"#");
}

//return the max life
void CVirtualMachine::LifeMax()
{
	Sint32 maxLife = m_curPlayer->m_Config->GetInt("Data.life");
	m_Stack.Push((float)maxLife,"#");
}

void CVirtualMachine::Ln()
{
	PopValue();
	float value = m_pop.Value;

	m_Stack.Push(log(value),"#");

}

void CVirtualMachine::Log()
{
	//Push  the 2 arguments
	PopValue();
	float value1 = m_pop.Value;
	PopValue();
	float value2 = m_pop.Value;
	float ret = log(value1)/log(value2);
	m_Stack.Push(ret,"#");
}

void CVirtualMachine::Lose()
{
	m_Stack.Push(0,"#");
}
void CVirtualMachine::LoseKO()
{
	m_Stack.Push(0,"#");
}
void CVirtualMachine::LoseTime()
{
	m_Stack.Push(0,"#");
}

//Returns the current match number.
void CVirtualMachine::MatchNo()
{
	m_Stack.Push(1,"#");
}

void CVirtualMachine::MatchOver()
{
	m_Stack.Push(0,"#");
}

void CVirtualMachine::MoveContact()
{
	if (m_curPlayer->m_HitInfo.bIsHitDefConfSet)
	{
		m_Stack.Push(m_curPlayer->m_HitInfo.nMoveContact,"#");
	}else
	{
		m_Stack.Push(0,"#");
	}
}

void CVirtualMachine::MoveGuarded()
{
	if (m_curPlayer->m_HitInfo.bIsHitDefConfSet)
	{
		m_Stack.Push(m_curPlayer->m_HitInfo.nMoveGuarded,"#");
	}else
	{
		m_Stack.Push(0,"#");
	}
}

void CVirtualMachine::MoveHit()
{
	if (m_curPlayer->m_HitInfo.bIsHitDefConfSet)
	{
		m_Stack.Push(m_curPlayer->m_HitInfo.nMoveHit,"#");
	}else
	{
		m_Stack.Push(0,"#");
	}
}

/*MoveType gives the player's move-type. Refer to the section
on StateDef in the CNS documentation for more details on MoveType.
Useful for "move interrupts" in the CMD file.
*/
void CVirtualMachine::MoveType()
{   
	//Types are A(ttack),I(dle),H(it)
	if (m_curPlayer->nMoveType == m_attack)
	{
		m_Stack.Push(0,"A");
	}else if(m_curPlayer->nMoveType == m_idle)
	{
		m_Stack.Push(0,"I");
	}else if(m_curPlayer->nMoveType == m_hit)
	{
		m_Stack.Push(0,"H");
	}else{
		if(OPEN_ERROR)SDL_assert(false);
	}
}

void CVirtualMachine::MoveReversed()
{
	//for now push False on the stack
	m_Stack.Push(0,"#");
}

void CVirtualMachine::Name()
{
	m_Stack.Push(0,m_curPlayer->m_Config->GetChar("Info.name"));
}

void CVirtualMachine::NumEnemy()
{
	//for now only one enemy is supported
	m_Stack.Push(1,"#");

}

void CVirtualMachine::NumExplod()
{
	PopValue();
	int explodid = m_pop.Value;
	int numExplodid = m_curPlayer->GetExplodCount(explodid);
	m_Stack.Push(numExplodid,"#");

}

//Return the Number of helpers
void CVirtualMachine::NumHelper()
{
	PopValue();
	int helperid = m_pop.Value;
	int HelperCount = 0;
	if (helperid == -1)
	{
		HelperCount = m_curPlayer->GetChildCount();
	}else{
		CObject* obj;
		CARRAY_FOREACH(m_curPlayer->m_Children, obj)
		{
			CPlayer* child = (CPlayer*)obj;
			if (child->m_type == PLAYER_HELPER && child->GetPropID() == helperid)
			{
				HelperCount ++;
			}
		}
	}
	m_Stack.Push(HelperCount,"#");
}

void CVirtualMachine::NumPartner()
{
	m_Stack.Push(0,"#");
}

void CVirtualMachine::NumProj()
{
	// don't pause when hit pause
	int numproj = m_curPlayer->GetProjCount(-1);
	m_Stack.Push(numproj,"#");
}

void CVirtualMachine::NumProjID()
{
	PopValue();
	int projid = m_pop.Value;
	Uint32 numproj = m_curPlayer->GetProjCount(projid);
	m_Stack.Push(numproj,"#");
}

void CVirtualMachine::NumTarget()
{
	PopValue();
	m_Stack.Push(0,"#");
}

void  CVirtualMachine::P1Name()
{
	Name();
}
void  CVirtualMachine::P2BodyDist()
{
	PopValue();
	const char* temp1=m_pop.string;
	float dis = 0;
	if (temp1[0] == 'x'||temp1[0]=='X')
	{
		Sint32 front1;
		Sint32 front2;
		if (m_curPlayer->nStateType == s_air)
		{
			front1 = m_curPlayer->m_Config->GetInt("Size.air.front");
		}else
		{
			front1 = m_curPlayer->m_Config->GetInt("Size.ground.front");
		}

		if (m_pPlayer2->nStateType == s_air)
		{
			front2 = m_pPlayer2->m_Config->GetInt("Size.air.front");
		}else
		{
			front2 = m_pPlayer2->m_Config->GetInt("Size.ground.front");
		}
		float dist = 0;
		if (m_curPlayer->x < m_pPlayer2->x)
		{
			dist = m_pPlayer2->x - m_curPlayer->x - front2 - front1;
		}else{
			dist = m_curPlayer->x - m_pPlayer2->x - front2 - front1;
		}
		
		m_Stack.Push(dist,"#");

	}else
	{
		float dist = 0;
		if (m_pPlayer2->y > m_curPlayer->y)
		{
			dist = m_pPlayer2->y - m_curPlayer->y;
		}else{
			dist =  m_curPlayer->y - m_pPlayer2->y;
		}
		m_Stack.Push(dist,"#");
	}

}

void CVirtualMachine::P2Dist()
{
	PopValue();
	const char* temp1=m_pop.string;
	float dis = 0;
	if (temp1[0] == 'x'||temp1[0]=='X')
	{
		float dist = 0;
		if (m_curPlayer->x < m_pPlayer2->x)
		{
			dist = m_pPlayer2->x - m_curPlayer->x;
		}else{
			dist = m_curPlayer->x - m_pPlayer2->x;
		}
		m_Stack.Push(dist,"#");

	}else
	{
		float dist = 0;
		if (m_pPlayer2->y > m_curPlayer->y)
		{
			dist = m_pPlayer2->y - m_curPlayer->y;
		}else{
			dist =  m_curPlayer->y - m_pPlayer2->y;
		}
		m_Stack.Push(dist,"#");
	}
}
void CVirtualMachine::P2Life()
{
	m_Stack.Push((float)m_pPlayer2->GetPropLife(),"#");
}

void CVirtualMachine::P2MoveType()
{
	//Types are A(ttack),I(dle),H(it)
	if (m_pPlayer2->nMoveType == m_attack)
	{
		m_Stack.Push(0,"A");
	}else if(m_pPlayer2->nMoveType == m_idle)
	{
		m_Stack.Push(0,"I");
	}else if(m_pPlayer2->nMoveType == m_hit)
	{
		m_Stack.Push(0,"H");
	}else{
		if(OPEN_ERROR)SDL_assert(false);
	}
}

void CVirtualMachine::P2Name()
{
	m_Stack.Push(0,m_pPlayer2->m_Config->GetChar("Info.name"));
}

void CVirtualMachine::P2StateNo()
{
	m_Stack.Push((float)m_pPlayer2->lpCurrStatedef->StateNumber,"#");
}

void CVirtualMachine::P2StateType()
{
	//SCAL
	if (m_pPlayer2->nStateType == s_stand)
	{
		m_Stack.Push(0,"S");
	}else if(m_pPlayer2->nStateType == s_crouch)
	{
		m_Stack.Push(0,"C");
	}else if(m_pPlayer2->nStateType == s_air)
	{
		m_Stack.Push(0,"A");
	}else if(m_pPlayer2->nStateType == s_liedown)
	{
		m_Stack.Push(0,"L");
	}else{
		if(OPEN_ERROR)SDL_assert(false);
	}

}

void CVirtualMachine::P3Name()
{
	m_Stack.Push(0,"P3Name");
}

void CVirtualMachine::P4Name()
{
	m_Stack.Push(0,"P4Name");
}

void CVirtualMachine::PalNo()
{
	m_Stack.Push(m_curPlayer->m_propPal,"#");
}

void CVirtualMachine::ParentDist()
{
	PopValue();
	const char* temp1=m_pop.string;
	float dis = 0;
	if (temp1[0] == 'x'||temp1[0]=='X')
	{
		m_Stack.Push(0,"#");
	}else
	{
		m_Stack.Push(0,"#");
	}

}

void CVirtualMachine::Pi()
{
	m_Stack.Push(3.141592653589f,"#");
}


void CVirtualMachine::Pos()
{
	PopValue();
	const char* temp1=m_pop.string;
	float dis = 0;
	if (temp1[0] == 'x'||temp1[0]=='X')
	{
		m_Stack.Push(m_curPlayer->x,"#");
	}else
	{
		m_Stack.Push(m_curPlayer->y,"#");
	}
}

void CVirtualMachine::Power()
{
	 m_Stack.Push((float)m_curPlayer->m_propPower,"#");
}

void CVirtualMachine::PowerMax()
{
	m_Stack.Push((float)m_curPlayer->m_propMaxPower,"#");
}

void CVirtualMachine::PlayerIDExist()
{
	PopValue();
	Uint32 id = (Uint32)m_pop.Value;
	bool ret = (id==P1)||(id==P2)||(id=P3)||(id==P4);
	m_Stack.Push(ret,"#");
}

void CVirtualMachine::PrevStateNo()
{
	m_Stack.Push(m_curPlayer->nLastStateNo,"#");
}

void CVirtualMachine::ProjCancelTime()
{
	if(OPEN_ERROR)SDL_assert(false);
	//throw CError("ProjCancelTime");
}


void CVirtualMachine::ProjContact()
{
	throw CError("ProjContact not supported, please use ProjContacttime");
}

void CVirtualMachine::ProjContactTime()
{
	PopValue();
	int projid = m_pop.Value;
	if (m_curPlayer->m_projHitInfo.bIsHited)
	{
		if (projid == m_curPlayer->m_projHitInfo.nProjID || projid == 0)
		{
			m_Stack.Push(m_curPlayer->m_projHitInfo.nProjContact,"#");
		}else{
			m_Stack.Push(-1,"#");
		}

	}else
	{
		m_Stack.Push(-1,"#");
	}
}

void CVirtualMachine::ProjGuarded()
{
	throw CError("ProjGuarded not supported, please use ProjGuardedTime");
}

void CVirtualMachine::ProjGuardedTime()
{
	PopValue();
	int projid = m_pop.Value;
	if (m_curPlayer->m_projHitInfo.bIsHited)
	{
		if (projid == m_curPlayer->m_projHitInfo.nProjID || projid == 0)
		{
			m_Stack.Push(m_curPlayer->m_projHitInfo.nProjGuarded,"#");
		}else{
			m_Stack.Push(-1,"#");
		}

	}else
	{
		m_Stack.Push(-1,"#");
	}
}

void CVirtualMachine::ProjHit()
{
	throw CError("ProjHit not supported, please use ProjHitTime");
}

void CVirtualMachine::ProjHitTime()
{
	PopValue();
	int projid = m_pop.Value;
	if (m_curPlayer->m_projHitInfo.bIsHited)
	{
		if (projid == m_curPlayer->m_projHitInfo.nProjID || projid == 0)
		{
			m_Stack.Push(m_curPlayer->m_projHitInfo.nProjHit,"#");
		}else{
			m_Stack.Push(-1,"#");
		}
		
	}else
	{
		m_Stack.Push(-1,"#");
	}
}

void CVirtualMachine::Random()
{
	Sint32 value = rand()%1000;
	m_Stack.Push((float)(value),"#"); 
}

void CVirtualMachine::RootDist()
{
	if(OPEN_ERROR)SDL_assert(false);
}

void CVirtualMachine::RoundNo()
{
	m_Stack.Push(1,"#");
}

void CVirtualMachine::RoundsExisted()
{
	m_Stack.Push(0,"#");
}

void CVirtualMachine::RoundState()
{
	//2= do battle
	m_Stack.Push(2,"#");

}
void CVirtualMachine::ScreenPos()
{
	PopValue();
	const char* temp1=m_pop.string;
	float dis = 0;
	if (temp1[0] == 'x'||temp1[0]=='X')
	{
		float x = CStageManager::GetInstance()->GetScreenPosX(m_curPlayer->x);
		Sint32 width =  Common_GetDesiginWidth();
		m_Stack.Push(x + width * 0.5,"#");
	}else
	{
		float y = CStageManager::GetInstance()->GetScreenPosX(m_curPlayer->y);
		Sint32 height = Common_GetDesiginHeight();
		m_Stack.Push(y + height * 0.5,"#");
	}

}

void CVirtualMachine::SelfAnimExist()
{
	PopValue();
	Sint32 nAnim=(Sint32)m_pop.Value;
	if(m_curPlayer->IsAnimAviable(nAnim))
		m_Stack.Push(1,"#");
	else
		m_Stack.Push(0,"#");
}


void CVirtualMachine::Sin()
{
	m_Stack.Push(sin(m_Stack.Pop().Value),"#");
}

void CVirtualMachine::StateNo()
{
	SDL_assert(m_curPlayer->lpCurrStatedef);
	m_Stack.Push((float)m_curPlayer->lpCurrStatedef->StateNumber,"#");
}

void CVirtualMachine::StateType()
{
	//SCAL
	if (m_curPlayer->nStateType == s_stand)
	{
		m_Stack.Push(0,"S");
	}else if(m_curPlayer->nStateType == s_crouch)
	{
		m_Stack.Push(0,"C");
	}else if(m_curPlayer->nStateType == s_air)
	{
		m_Stack.Push(0,"A");
	}else if(m_curPlayer->nStateType == s_liedown)
	{
		m_Stack.Push(0,"L");
	}else{
		if(OPEN_ERROR)SDL_assert(false);
	}

}

void CVirtualMachine::SysFVar()
{
	PopValue();
	float value = m_curPlayer->GetVectorSysFVar((Uint32)m_pop.Value);
	m_Stack.Push(value,"#");

}

void CVirtualMachine::SysVar()
{
	PopValue();
	Sint32 value = m_curPlayer->GetVectorSysVar((Uint32)m_pop.Value);
	m_Stack.Push(value,"#");
}

void CVirtualMachine::Tan()
{
	m_Stack.Push(tan(m_Stack.Pop().Value),"#");
}

void CVirtualMachine::TeamMode()
{
	if(OPEN_ERROR)SDL_assert(false);
}

void CVirtualMachine::TeamSide()
{
	m_Stack.Push(-1,"#");
	//if(OPEN_ERROR)SDL_assert(false);
}

void CVirtualMachine::TicksPerSecond()
{
	float fps = CGame::GetInstance()->GetPropFps();
	m_Stack.Push(fps,"#");
}

void CVirtualMachine::Time()
{
	m_Stack.Push(m_curPlayer->nStateTime,"#");
}

void CVirtualMachine::TimeMod()
{
	PopValue();
	int v1=m_pop.Value;

	PopValue();
	int v2=m_pop.Value;

	if (v2 == 0)
	{

	}
	CAssert(v2!=0, "time mod should not be 0");
	if ((m_curPlayer->nStateTime - v1) % v2 == 0)
	{
		m_Stack.Push(1, "#");
	}else{
		m_Stack.Push(0, "#");
	}

}
void CVirtualMachine::UniqHitCount()
{
	m_Stack.Push(1,"#");
}

void CVirtualMachine::Var()
{
	PopValue();
	Sint32 value = m_curPlayer->GetVectorVar((Uint32)m_pop.Value);
	m_Stack.Push(value,"#");
}

void CVirtualMachine::Vel()
{
	PopValue();
	const char* temp1=m_pop.string;
	float vel = 0;
	if (temp1[0] == 'x'||temp1[0] == 'X')
	{
		vel = m_curPlayer->xVel;
	}else
	{
		vel = m_curPlayer->yVel;
	}
	m_Stack.Push(vel,"#");
}

void CVirtualMachine::Win()
{
	m_Stack.Push(0, "#");
}
void CVirtualMachine::WinKO()
{
	m_Stack.Push(0, "#");
}
void CVirtualMachine::WinTime()
{
	m_Stack.Push(0, "#");
}
void CVirtualMachine::WinPerfect()
{
	m_Stack.Push(0, "#");
}

void CVirtualMachine::Parent()
{
	m_curPlayer = m_pPlayer1->GetParent();
}

void CVirtualMachine::Root()
{
	m_curPlayer = m_pPlayer1->GetRoot();
}


void CVirtualMachine::Helper()
{
	PopValue();
	m_curPlayer = m_pPlayer1;
}

void CVirtualMachine::Target()
{
	PopValue();
	m_curPlayer = m_pPlayer2;
}

void CVirtualMachine::Partner()
{
	m_curPlayer = m_pPlayer1;
}

void CVirtualMachine::Enemy()
{
	PopValue();
	m_curPlayer = m_pPlayer2;
}

void CVirtualMachine::EnemyNear()
{
	PopValue();
	m_curPlayer = m_pPlayer2;
}

void CVirtualMachine::PlayerID()
{
	PopValue();
	m_curPlayer = m_pPlayer1;
}

//Save one Value from stack for tempory 
void CVirtualMachine::Save()
{
	nSave=m_Stack.Pop().Value;
}

//Restore the tempory Value to stack
void CVirtualMachine::Restore()
{
	m_Stack.Push(nSave,"#");
}


