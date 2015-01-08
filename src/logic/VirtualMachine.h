/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef VM_H
#define VM_H

#include "player.h"
#include "Stack.h"
class CPlayer;
#define NUMFUNCT 170

class CVirtualMachine
{
	typedef void (CVirtualMachine::*pt2Member)();
	pt2Member pFuncTable[NUMFUNCT];

	CPlayer *m_pPlayer1,*m_pPlayer2;
	CPlayer* m_curPlayer;

	CStack m_Stack;
	OpElement *pCurrentIns;
	Stacktype m_pop;
	float temp1,temp2,temp3;
	float nSave;
	bool isError;

public:
	CVirtualMachine();
	~CVirtualMachine();

	void PushValue();
	void PopAllValue();
	void PopValue();
	void AddOP();
	void SubOP();
	void DivOP();
	void MulOP();
	void EqualOP();
	void Assign();
	void NotEqual();
	void Less();
	void Greater();
	void LessEqual();
	void GreaterEqual();
	void InterValOP1();
	void InterValOP2();
	void InterValOP3();
	void InterValOP4();
	void InterValOP5();
	void InterValOP6();
	void InterValOP7();
	void InterValOP8();
	void LogNot();
	void LogAnd();
	void LogOr();
	void LogXor();
	void Not();
	void And();
	void Or();
	void Xor();
	void Square();
	void Abs();
	void Neg();
	void MODOP();
	void LEFT();
	void RIGHT();

	void Acos();
	void AILevel();
	void Alive();
	void Anim();
	void AnimElem();
	void AnimeElemNo();
	void AnimeElemTime();
	void AnimExist();
	void AnimTime();
	void Asin();
	void Atan();
	void AuthorName();
	void BackEdgeBodyDist();
	void BackEdgeDist();
	void CanRecover();
	void Ceil();
	void Command();
	void Const();
	void Const240p();
	void Const480p();
	void Const720p();
	void Cos();
	void Ctrl();
	void DrawGame();
	void E();
	void Exp();
	void Facing();
	void Floor();
	void FrontEdgeBodyDist();
	void FrontEdgeDist();
	void FVar();
	void GameHeight();
	void GameTime();
	void GameWidth();
	void GetHitVar();
	void HitCount();
	void HitDefAttr();
	void HitFall();
	void HitOver();
	void HitPauseTime();
	void HitShakeOver();
	void HitVel();
	void ID();
	void IfElse();
	void InGuardDist();
	void IsHelper();
	void IsHomeTeam();
	void Life();
	void LifeMax();
	void Ln();
	void Log();
	void Lose();
	void LoseKO();
	void LoseTime();
	void MatchNo();
	void MatchOver();
	void MoveContact();
	void MoveGuarded();
	void MoveHit();
	void MoveType();
	void MoveReversed();
	void Name();
	void NumEnemy();
	void NumExplod();
	void NumHelper();
	void NumPartner();
	void NumProj();
	void NumProjID();
	void NumTarget();
	void P1Name();
	void P2BodyDist();
	void P2Dist();
	void P2Life();
	void P2MoveType();
	void P2Name();
	void P2StateNo();
	void P2StateType();
	void P3Name();
	void P4Name();
	void PalNo();
	void ParentDist();
	void Pi();
	void Pos();
	void Power();
	void PowerMax();
	void PlayerIDExist();
	void PrevStateNo();
	void ProjCancelTime();
	void ProjContact();
	void ProjContactTime();
	void ProjGuarded();
	void ProjGuardedTime();
	void ProjHit();
	void ProjHitTime();
	void Random();
	void RootDist();
	void RoundNo();
	void RoundsExisted();
	void RoundState();
	void ScreenPos();
	void SelfAnimExist();
	void Sin();
	void StateNo();
	void StateType();
	void SysFVar();
	void SysVar();
	void Tan();
	void TeamMode();
	void TeamSide();
	void TicksPerSecond();
	void Time();
	void TimeMod();
	void UniqHitCount();
	void Var();
	void Vel();
	void Win();
	void WinKO();
	void WinTime();
	void WinPerfect();
	void Parent();
	void Root();
	void Helper();
	void Target();
	void Partner();
	void Enemy();
	void EnemyNear();
	void PlayerID();


	//helper functions
	void Save();
	void Restore();

	char* ExecuteGetStr(OpElement *pInst);
	float Execute(OpElement *pInst);
	float ExecuteForState(OpElement *pInst);
	void InitFunctTable();
	void SetPlayers(CPlayer *p1,CPlayer *p2);

private:
	void NativeExecute(OpElement *pInst);
};


#endif
