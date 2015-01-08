/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/


#ifndef CONTROLLEREXECUTER_H
#define CONTROLLEREXECUTER_H
#include "player.h"
class CPlayer;

class CControllerExecuter
{
	CPlayer *m_pPlayer1;
	CPlayer *m_pPlayer2;
public:
    CControllerExecuter();
    ~CControllerExecuter();
    void SetPlayer(CPlayer *p1, CPlayer *p2){m_pPlayer1=p1;m_pPlayer2=p2;};


public:// controlº¯Êý
	void InitFuncTable();
	typedef void (CControllerExecuter::*ptControlExe)(PLSTATE*);
	ptControlExe pFuncTable[NUMFUNCT_CONTROL];

	void ExecuteController(PLSTATE* tempState);
	char* ExecuteGetStr(OpElement *pInst);
	float Execute(OpElement *pInst);

	void AfterImage(PLSTATE* state);
	void AllPalFX(PLSTATE* state);
	void AssertSpecial(PLSTATE*);
	void ChangeAnim(PLSTATE* );
	void ChangeAnim2(PLSTATE* state);
	void CtrlSet(PLSTATE*);
	void ChangeState(PLSTATE* );
	void DestroySelf(PLSTATE* state);
	void DisplayToClipboard(PLSTATE* state);
	void EnvColor(PLSTATE *state);
	void EnvShake(PLSTATE* state);
	void Explod(PLSTATE* state);
	void Gravity(PLSTATE* state);
	void Helper(PLSTATE* state);
	void HitBy(PLSTATE* state);
	void HitDef(PLSTATE* );
	void HitFallDamage(PLSTATE* state);
	void HitFallSet(PLSTATE* state);
	void HitFallVel(PLSTATE* state);
	void HitVelSet(PLSTATE* state);
	void PalFX(PLSTATE* state);
	void PlayerPush(PLSTATE* state);
	void PlaySnd(PLSTATE* state);
	void PosAdd(PLSTATE* state);
	void PosSet(PLSTATE*);
	void Projectile(PLSTATE* state);
	void SelfState(PLSTATE* state);
	void StateTypeSet(PLSTATE* state);
	void NotHitBy(PLSTATE* state);
	void Null(PLSTATE*);
	void SuperPause(PLSTATE* state);
	void TargetBind(PLSTATE* state);
	void targetState(PLSTATE* state);
	void Turn(PLSTATE* state);
	void VarAdd(PLSTATE* state);
	void VarSet(PLSTATE* state);
	void VelAdd(PLSTATE* state);
	void VelMul(PLSTATE*);
	void VelSet(PLSTATE*);
	void Width(PLSTATE* state);
	void AddCommandInput(PLSTATE* state);
	void Print(PLSTATE* state);

};

#endif
