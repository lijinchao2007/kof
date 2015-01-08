/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef ___STATEPARSER__H
#define ___STATEPARSER__H

#include "define.h"
#include "tokenizer.h"
#include "StateManager.h"
#include "CharsConfig.h"

class CCharsConfig;

class CStateParser
{
	int m_nPrimaryArgc;
	CCharsConfig* m_CharMgr;
	CStateManager* m_StateMgr;

public:
	CStateParser(CCharsConfig* charMgr, CStateManager* stateMgr);
	~CStateParser();
	void ParseStateFile(const char * strFileName);

	void ParseStateDef(CTokenizer &tok);
	void PareseState(CTokenizer &tok);
	void ParseTrigger(CTokenizer &tok);
	//Expression parser
	void EvaluateExpression(CTokenizer &tok);
	void Term(CTokenizer &tok);
	void Primary(CTokenizer &tok);
	//helper functions   
	void PrimarySpecialOP(CTokenizer &tok, Uint32 i);
	int  GetControllerType(const char * strType,CTokenizer &tok);
	int GetOPArgc(int op, CTokenizer &Tok);
	int  GetTriggerType(const char * strTrigger,CTokenizer &tok);
	void Error(const char * strErrorMsg,CTokenizer &tok);

	//controller parser
	void ParserController(CTokenizer &tok, u16 nControllerType);
	bool ParseStateBaseParm(CTokenizer &tok);
	void ParseNormalAction(CTokenizer &tok);

	void ParseVarSet(CTokenizer &tok);
	void ParseWidth(CTokenizer &tok);
	void ParseStateTypeSet(CTokenizer &tok);
	void ParseTargetBind(CTokenizer &tok);
	void ParseAssertSpecial(CTokenizer &tok);
	void ParseAfterImage(CTokenizer &tok);
	void ParsePalFX(CTokenizer &tok);
	void ParseHelper(CTokenizer &tok);
	void ParseSuperPause(CTokenizer &tok);
	void ParsePlaySnd(CTokenizer &tok);
	void DisplayToClipboard(CTokenizer &tok);
	void ParseProj(CTokenizer &tok);
	void ParseExplod(CTokenizer &tok);
	void ParseNotHitBy(CTokenizer &tok);
	void ParseAddCommandInput(CTokenizer &tok);
	void ParseChangeState(CTokenizer &tok);
	void ParseTargetState(CTokenizer &tok);
	void ParseChangeAnim(CTokenizer &tok);
	Sint32 GetHitDefAttr(CTokenizer &tok);
	void ParseEnvShake(CTokenizer &tok);
	void ParseEnvColor(CTokenizer &tok);
	void ParseHitDef(CTokenizer &tok);

};

#define PRECEDENCE_OP(op) while(m_StateMgr->PrecedenceOp(op)<0)m_StateMgr->PopOp();\
	m_StateMgr->PushOp(op, #op);\
	Term(tok);

#endif
