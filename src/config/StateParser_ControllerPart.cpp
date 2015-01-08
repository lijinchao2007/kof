/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "StateParser.h"
#include "tool.h"

//Parse a controller
void CStateParser::ParserController(CTokenizer &tok, u16 nControllerType)
{
	if (ParseStateBaseParm(tok))
	{
		return;
	}
	switch(nControllerType)
	{
	case Control_ChangeAnim:
	case Control_ChangeAnim2:
		// parse is same as ParseChangeAnim
		ParseChangeAnim(tok);   
		break;
	case Control_SelfState:
	case Control_ChangeState:
		ParseChangeState(tok);   
		break;
	case Control_TargetState:
		ParseTargetState(tok);   
		break;
	case Control_EnvShake:
		ParseEnvShake(tok);   
		break;
	case Control_EnvColor:
		ParseEnvColor(tok);   
		break;
	case Control_HitDef:
		ParseHitDef(tok);   
		break;
	case Control_VarAdd:
	case Control_VarSet:
		ParseVarSet(tok); 
		break;
	case Control_Width:
		ParseWidth(tok); 
		break;
	case Control_StateTypeSet:
		ParseStateTypeSet(tok); 
		break;
	case Control_TargetBind:
		ParseTargetBind(tok);
		break;
	case Control_AssertSpecial:
		ParseAssertSpecial(tok);   
		break;
	case Control_AfterImage:
		ParseAfterImage(tok);   
		break;
	case Control_AllPalFX:
	case Control_PalFX:
		ParsePalFX(tok);   
		break;

	case Control_Helper:
		ParseHelper(tok);   
		break;
	case Control_SuperPause:
		ParseSuperPause(tok);   
		break;
	case Control_PlaySnd:
		ParsePlaySnd(tok);   
		break;
	case Control_DisplayToClipboard:
	case Control_Print:
		DisplayToClipboard(tok);   
		break;
	case Control_Projectile:
		ParseProj(tok);   
		break;
	case Control_Explod:
		ParseExplod(tok);   
		break;
	case Control_NotHitBy:
	case Control_HitBy:
		ParseNotHitBy(tok);   
		break;
	case Control_AddCommandInput:
		ParseAddCommandInput(tok);   
		break;
	default:
		ParseNormalAction(tok);
	}
}

#define CONTROL_PARAMS_PARSE_START(name) if( tok.CheckToken(#name) )\
{\
	if( !tok.CheckToken("=") )\
	Error("expected =",tok);\
	EvaluateExpression(tok);\
	m_StateMgr->SetParam(CPN_##name);\
}
#define CONTROL_PARAMS_PARSE(name) else if( tok.CheckToken(#name) )\
{\
	if( !tok.CheckToken("=") )\
	Error("expected =",tok);\
	EvaluateExpression(tok);\
	m_StateMgr->SetParam(CPN_##name);\
}


#define CONTROL_PARAMS_PARSE_END(func) else{\
	ParseWarning(tok, #func" param is not deal!");\
	GET_ALL_LINE_TOKEN(tok);\
}  

bool CStateParser::ParseStateBaseParm(CTokenizer &tok)
{
	// 基本的解析persistent" and "ignorehitpause"
	if( tok.CheckToken("persistent") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  

		int per = tok.GetInt();
		m_StateMgr->SetPersistent(per);
		return true;
		// 设置当前state的参数
	}else if( tok.CheckToken("ignorehitpause") )
	{
		Uint32 ignore = 1;
		if( tok.CheckToken("=") )
			ignore = tok.GetInt();
		m_StateMgr->SetIgnorehitpause((bool)ignore);
		if (m_StateMgr->GetCurState()->nType == Control_Explod)
		{
			m_StateMgr->GetCurState()->pExplod->bignorehitpause = ignore;
		}
		return true;
	}else
	{
		return false;
	}     
}

void CStateParser::ParseNormalAction(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(value)
		CONTROL_PARAMS_PARSE(ctrl)
		CONTROL_PARAMS_PARSE(anim)
		CONTROL_PARAMS_PARSE(x)
		CONTROL_PARAMS_PARSE(y)
		CONTROL_PARAMS_PARSE(time)
		CONTROL_PARAMS_PARSE_END(ParseNormalAction)
}

void CStateParser::ParseVarSet(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(v)
		CONTROL_PARAMS_PARSE(fv)
		CONTROL_PARAMS_PARSE(value)
	else if ( tok.CheckToken("var") )
	{
		if( !tok.CheckToken("(") )
			Error("expected (",tok); 
		EvaluateExpression(tok);
		// 设置当前state的参数
		m_StateMgr->SetParam(CPN_v);
		if( !tok.CheckToken(")") )
			Error("expected )",tok); 
		if( !tok.CheckToken("=") )
			Error("expected =",tok); 

		EvaluateExpression(tok); 
		m_StateMgr->SetParam(CPN_value);

	}else if ( tok.CheckToken("fvar") )
	{
		if( !tok.CheckToken("(") )
			Error("expected (",tok); 
		EvaluateExpression(tok);
		// 设置当前state的参数
		m_StateMgr->SetParam(CPN_v);
		if( !tok.CheckToken(")") )
			Error("expected )",tok); 
		if( !tok.CheckToken("=") )
			Error("expected =",tok); 

		EvaluateExpression(tok); 
		m_StateMgr->SetParam(CPN_value);
	}else if ( tok.CheckToken("sysvar") )
	{
		if( !tok.CheckToken("(") )
			Error("expected (",tok); 
		EvaluateExpression(tok);
		// 设置当前state的参数
		m_StateMgr->SetParam(CPN_sysv);
		if( !tok.CheckToken(")") )
			Error("expected )",tok); 
		if( !tok.CheckToken("=") )
			Error("expected =",tok); 

		EvaluateExpression(tok); 
		m_StateMgr->SetParam(CPN_value);
	}else if ( tok.CheckToken("sysfvar") )
	{
		if( !tok.CheckToken("(") )
			Error("expected (",tok); 
		EvaluateExpression(tok);
		// 设置当前state的参数
		m_StateMgr->SetParam(CPN_sysfv);
		if( !tok.CheckToken(")") )
			Error("expected )",tok); 
		if( !tok.CheckToken("=") )
			Error("expected =",tok); 

		EvaluateExpression(tok); 
		m_StateMgr->SetParam(CPN_value);
	}   

	CONTROL_PARAMS_PARSE_END(ParseVarSet)

}

void CStateParser::ParseWidth(CTokenizer &tok)
{
	if( tok.CheckToken("value") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  

		EvaluateExpression(tok);
		// 设置当前state的参数
		m_StateMgr->SetParam(CPN_front);
		m_StateMgr->SetParam(CPN_screenFront);
		if(tok.CheckToken(",") )
		{
			EvaluateExpression(tok);
			// 设置当前state的参数
			m_StateMgr->SetParam(CPN_back);
			m_StateMgr->SetParam(CPN_screenBack);
		}

	}else if( tok.CheckToken("edge") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  

		EvaluateExpression(tok);
		// 设置当前state的参数
		m_StateMgr->SetParam(CPN_screenFront);
		if(tok.CheckToken(",") )
		{
			EvaluateExpression(tok);
			// 设置当前state的参数
			m_StateMgr->SetParam(CPN_screenBack);
		}
	}else if( tok.CheckToken("player") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  

		EvaluateExpression(tok);
		// 设置当前state的参数
		m_StateMgr->SetParam(CPN_front);
		if(tok.CheckToken(",") )
		{
			EvaluateExpression(tok);
			// 设置当前state的参数
			m_StateMgr->SetParam(CPN_back);
		}
	}else
	{
		ParseWarning(tok, "ParseWidth not deal");
		GET_ALL_LINE_TOKEN(tok);
	}   
}


void CStateParser::ParseStateTypeSet(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(statetype)
		CONTROL_PARAMS_PARSE(movetype)
		CONTROL_PARAMS_PARSE(physics)
		CONTROL_PARAMS_PARSE_END(ParseStateTypeSet)
}

void CStateParser::ParseTargetBind(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(time)
		CONTROL_PARAMS_PARSE(id)
		else if( tok.CheckToken("pos") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);
		m_StateMgr->SetParam(CPN_x);

		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		EvaluateExpression(tok);
		m_StateMgr->SetParam(CPN_y);

	}
	CONTROL_PARAMS_PARSE_END(ParseAssertSpecial)
}

void CStateParser::ParseAssertSpecial(CTokenizer &tok)
{
	if( tok.CheckToken("flag") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  

		char flag[MAX_PATH];
		tok.GetToken(flag, MAX_PATH);
		m_StateMgr->NewInst();
		m_StateMgr->AddInstruction(OP_PUSH, 0, flag);
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_flag);

	}
		CONTROL_PARAMS_PARSE_END(ParseAssertSpecial)
}

void CStateParser::ParseAfterImage(CTokenizer &tok)
{
	if( tok.CheckToken("time") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val = tok.GetInt();
		m_StateMgr->GetCurState()->pAfterImage->time = val;
	}
	else if( tok.CheckToken("length") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val = tok.GetInt();
		m_StateMgr->GetCurState()->pAfterImage->length = val;
	}
	else if( tok.CheckToken("timegap") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val = tok.GetInt();
		m_StateMgr->GetCurState()->pAfterImage->timegap = val;
	}
	else if( tok.CheckToken("framegap") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val = tok.GetInt();
		m_StateMgr->GetCurState()->pAfterImage->framegap = val;
	}

	else if( tok.CheckToken("palcolor") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val = tok.GetInt();
		m_StateMgr->GetCurState()->pAfterImage->palcolor = val/256.0;
	}
	else if( tok.CheckToken("palinvertall") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val = tok.GetInt();
		m_StateMgr->GetCurState()->pAfterImage->palinvertall = val;
	}
	else if( tok.CheckToken("palbright") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val1 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val2 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val3 = tok.GetInt();
		m_StateMgr->GetCurState()->pAfterImage->palbright.r = val1/256.0;
		m_StateMgr->GetCurState()->pAfterImage->palbright.g = val2/256.0;
		m_StateMgr->GetCurState()->pAfterImage->palbright.b = val3/256.0;
	}
	else if( tok.CheckToken("palcontrast") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val1 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val2 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val3 = tok.GetInt();
		m_StateMgr->GetCurState()->pAfterImage->palcontrast.r = val1/256.0;
		m_StateMgr->GetCurState()->pAfterImage->palcontrast.g = val2/256.0;
		m_StateMgr->GetCurState()->pAfterImage->palcontrast.b = val3/256.0;
	}
	else if( tok.CheckToken("palpostbright") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val1 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val2 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val3 = tok.GetInt();
		m_StateMgr->GetCurState()->pAfterImage->palpostbright.r = val1/256.0;
		m_StateMgr->GetCurState()->pAfterImage->palpostbright.g = val2/256.0;
		m_StateMgr->GetCurState()->pAfterImage->palpostbright.b = val3/256.0;
	}
	else if( tok.CheckToken("paladd") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val1 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val2 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val3 = tok.GetInt();
		m_StateMgr->GetCurState()->pAfterImage->paladd.r = val1/256.0;
		m_StateMgr->GetCurState()->pAfterImage->paladd.g = val2/256.0;
		m_StateMgr->GetCurState()->pAfterImage->paladd.b = val3/256.0;
	}
	else if( tok.CheckToken("palmul") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float val1 = tok.GetFloat();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		float val2 = tok.GetFloat();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		float val3 = tok.GetFloat();
		m_StateMgr->GetCurState()->pAfterImage->palmul.r = val1/256.0;
		m_StateMgr->GetCurState()->pAfterImage->palmul.g = val2/256.0;
		m_StateMgr->GetCurState()->pAfterImage->palmul.b = val3/256.0;
	}
	else if( tok.CheckToken("trans") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		const char* val2 = tok.GetToken();
		if (SDL_strcasecmp(val2, "none") == 0)
		{
			m_StateMgr->GetCurState()->pAfterImage->trans = eTransTypeNone;
		}else if(SDL_strcasecmp(val2, "add") == 0)
		{
			m_StateMgr->GetCurState()->pAfterImage->trans = eTransTypeAdd;
		}else if(SDL_strcasecmp(val2, "add1") == 0)
		{
			m_StateMgr->GetCurState()->pAfterImage->trans = eTransTypeAdd1;
		}else if(SDL_strcasecmp(val2, "sub") == 0)
		{
			m_StateMgr->GetCurState()->pAfterImage->trans = eTransTypeSub;
		}
	}
		CONTROL_PARAMS_PARSE_END(ParseAfterImage)
}

void CStateParser::ParsePalFX(CTokenizer &tok)
{
	if( tok.CheckToken("time") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val = tok.GetInt();
		m_StateMgr->GetCurState()->pPalFXinfo->time = val;
	}
	else if( tok.CheckToken("color") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val = tok.GetInt();
		m_StateMgr->GetCurState()->pPalFXinfo->palcolor = val/256.0;
	}
	else if( tok.CheckToken("invertall") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val = tok.GetInt();
		m_StateMgr->GetCurState()->pPalFXinfo->palinvertall = val;
	}
	else if( tok.CheckToken("add") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val1 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val2 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val3 = tok.GetInt();
		m_StateMgr->GetCurState()->pPalFXinfo->palbright.r = val1/256.0;
		m_StateMgr->GetCurState()->pPalFXinfo->palbright.g = val2/256.0;
		m_StateMgr->GetCurState()->pPalFXinfo->palbright.b = val3/256.0;
	}
	else if( tok.CheckToken("mul") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val1 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val2 = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		int val3 = tok.GetInt();
		m_StateMgr->GetCurState()->pPalFXinfo->palcontrast.r = val1/256.0;
		m_StateMgr->GetCurState()->pPalFXinfo->palcontrast.g = val2/256.0;
		m_StateMgr->GetCurState()->pPalFXinfo->palcontrast.b = val3/256.0;
	}
	else if( tok.CheckToken("sinadd") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float val1 = tok.GetFloat();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		float val2 = tok.GetFloat();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok);  
		float val3 = tok.GetFloat();
		float val4 = 0;
		if(tok.CheckToken(","))
			val4 = tok.GetFloat();
		m_StateMgr->GetCurState()->pPalFXinfo->sinadd.r = val1/256.0;
		m_StateMgr->GetCurState()->pPalFXinfo->sinadd.g = val2/256.0;
		m_StateMgr->GetCurState()->pPalFXinfo->sinadd.b = val3/256.0;
		m_StateMgr->GetCurState()->pPalFXinfo->sinperiod = val4;
	}
	CONTROL_PARAMS_PARSE_END(ParsePalFX)
}

void CStateParser::ParseHelper(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(name)
		CONTROL_PARAMS_PARSE(id)
		CONTROL_PARAMS_PARSE(stateno)
		CONTROL_PARAMS_PARSE(postype)
		CONTROL_PARAMS_PARSE(helpertype)
		CONTROL_PARAMS_PARSE(keyctrl)
		CONTROL_PARAMS_PARSE(ownpal)
	else if( tok.CheckToken("pos") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);
		m_StateMgr->SetParam(CPN_x);

		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		EvaluateExpression(tok);
		m_StateMgr->SetParam(CPN_y);
	}
	CONTROL_PARAMS_PARSE_END(ParseHelper)
}

void CStateParser::ParseSuperPause(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(time)
		CONTROL_PARAMS_PARSE(darken)
		CONTROL_PARAMS_PARSE(p2defmul)
		CONTROL_PARAMS_PARSE(poweradd)
		CONTROL_PARAMS_PARSE(unhittable)
	else if( tok.CheckToken("anim") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		const char* anim = tok.GetToken();
		int animValue = -1;
		EnumAnimType type;
		if (anim[0] == 'S'||anim[0] == 's')
		{
			type = AnimPlayer;
			animValue = SDL_atoi(anim+1);
		}else{
			type = AnimFightFX;
			animValue = SDL_atoi(anim);
		}
		m_StateMgr->NewInst();
		m_StateMgr->AddInstruction(OP_PUSH, animValue, "#");
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_anim);

		m_StateMgr->NewInst();
		m_StateMgr->AddInstruction(OP_PUSH, type, "#");
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_animtype);
	}
	else if( tok.CheckToken("sound") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  

		char groupNo[MAX_PATH];
		int gNo = 0;
		int sNo = 0;
		SndType type;
		tok.GetToken(groupNo, MAX_PATH);
		if (groupNo[0] == 'S' || groupNo[0] == 's')
		{
			type = SndPlayer;
			gNo = SDL_atoi(groupNo+1);
			
		}else
		{
			type = SndCommon;
			gNo = SDL_atoi(groupNo);
		}

		m_StateMgr->NewInst();
		m_StateMgr->AddInstruction(OP_PUSH, type, "#");
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_sndType);

		m_StateMgr->NewInst();
		m_StateMgr->AddInstruction(OP_PUSH, gNo, "#");
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_SndGroupNo);

		if (gNo != -1)
		{
			if( !tok.CheckToken(",") )
				Error("expected ,",tok);
			m_StateMgr->NewInst();
			sNo = tok.GetInt();
			m_StateMgr->AddInstruction(OP_PUSH, sNo, "#");
			m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
			m_StateMgr->SetParam(CPN_SndNo);
		}
		
	}
	else if( tok.CheckToken("pos") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int x = tok.GetInt();
		m_StateMgr->NewInst();
		m_StateMgr->AddInstruction(OP_PUSH, x, "");
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_x);

		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		int y = tok.GetInt();
		m_StateMgr->AddInstruction(OP_PUSH, y, "");
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_y);

	}
		CONTROL_PARAMS_PARSE_END(ParseSuperPause)
}

void CStateParser::ParsePlaySnd(CTokenizer &tok)
{
	if( tok.CheckToken("value") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  

		int gNo = 0;
		int sNo = 0;
		SndType type;
		const char* groupNo = tok.GetToken();
		if (groupNo[0] == 'F' || groupNo[0] == 'f')
		{
			type = SndFight;
			gNo = SDL_atoi(groupNo+1);

		}else
		{
			type = SndPlayer;
			gNo = SDL_atoi(groupNo);
		}

		m_StateMgr->NewInst();
		m_StateMgr->AddInstruction(OP_PUSH, type, "#");
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_sndType);

		m_StateMgr->NewInst();
		m_StateMgr->AddInstruction(OP_PUSH, gNo, "#");
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_SndGroupNo);

		if (gNo != -1)
		{
			if( !tok.CheckToken(",") )
				Error("expected ,",tok);
			m_StateMgr->NewInst();
			sNo = tok.GetInt();
			m_StateMgr->AddInstruction(OP_PUSH, sNo, "#");
			m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
			m_StateMgr->SetParam(CPN_SndNo);
		}
		
	}
		CONTROL_PARAMS_PARSE_END(ParsePlaySnd)
}

void CStateParser::DisplayToClipboard(CTokenizer &tok)
{
	if( tok.CheckToken("text") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);
		m_StateMgr->SetParam(CPN_text);
	}
	else if( tok.CheckToken("params") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);
		m_StateMgr->SetParam(CPN_Param);
		while (tok.CheckToken(","))
		{
			EvaluateExpression(tok);
			m_StateMgr->SetParam(CPN_Param);
		}
	}
}
void CStateParser::ParseProj(CTokenizer &tok)
{
	if( tok.CheckToken("projanim") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int anim = tok.GetInt();
		m_StateMgr->GetCurState()->pProjInfo->nAnim = anim;
	}
	else if( tok.CheckToken("ProjID") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjID = tok.GetInt();
	}
	else if( tok.CheckToken("projhitanim") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjhitanim = tok.GetInt();
	}
	else if( tok.CheckToken("projremanim") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjremanim = tok.GetInt();
	}
	else if( tok.CheckToken("projcancelanim") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjcancelanim = tok.GetInt();
	}
	else if( tok.CheckToken("projscale") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float sx = 1, sy = 1;
		sx = tok.GetFloat();
		if(tok.CheckToken(",") )
		{
			sy = tok.GetFloat();
		}
		else
		{
			sy = sx;
		}
		m_StateMgr->GetCurState()->pProjInfo->scalex = sx;
		m_StateMgr->GetCurState()->pProjInfo->scaley = sy;
	}
	else if( tok.CheckToken("projremove") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->bProjremove = tok.GetInt();
	}
	else if( tok.CheckToken("projremovetime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nRemovetime = tok.GetInt();
	}
	else if( tok.CheckToken("velocity") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float vx = tok.GetFloat();
		float vy = 0;
		if(tok.CheckToken(",") )
			vy = tok.GetFloat();
		m_StateMgr->GetCurState()->pProjInfo->velx = vx;
		m_StateMgr->GetCurState()->pProjInfo->vely = vy;
	}
	else if( tok.CheckToken("remvelocity") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float vx = tok.GetFloat();
		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		float vy = tok.GetFloat();
		m_StateMgr->GetCurState()->pProjInfo->remvelocityx = vx;
		m_StateMgr->GetCurState()->pProjInfo->remvelocityy = vy;
	}
	else if( tok.CheckToken("accel") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float ax = tok.GetFloat();
		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		float ay = tok.GetFloat();
		m_StateMgr->GetCurState()->pProjInfo->accelx = ax;
		m_StateMgr->GetCurState()->pProjInfo->accely = ay;
	}
	else if( tok.CheckToken("velmul") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float ax = tok.GetFloat();
		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		float ay = tok.GetFloat();
		m_StateMgr->GetCurState()->pProjInfo->velmulx = ax;
		m_StateMgr->GetCurState()->pProjInfo->velmuly = ay;
	}
	else if( tok.CheckToken("projhits") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjhits = tok.GetInt();
	}
	else if( tok.CheckToken("projmisstime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjmisstime = tok.GetInt();
	}
	else if( tok.CheckToken("projpriority") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjpriority = tok.GetInt();
	}
	else if( tok.CheckToken("projhits") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjhits = tok.GetInt();
	}
	else if( tok.CheckToken("projsprpriority") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nSprpriority = tok.GetInt();
	}
	else if( tok.CheckToken("projedgebound") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjedgebound = tok.GetInt();
	}
	else if( tok.CheckToken("projstagebound") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjstagebound = tok.GetInt();
	}
	else if( tok.CheckToken("projheightbound") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nProjheightbound = tok.GetInt();
	}
	else if( tok.CheckToken("offset") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float x = tok.GetFloat();
		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		float y = tok.GetFloat();
		m_StateMgr->GetCurState()->pProjInfo->posx = x;
		m_StateMgr->GetCurState()->pProjInfo->posy = y;
	}
	else if( tok.CheckToken("postype") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EnumPosType type = eEnumPosType_P1;
		if (tok.CheckToken("p1"))
		{
			type = eEnumPosType_P1;
		}
		else if (tok.CheckToken("p2"))
		{
			type = eEnumPosType_P2;
		}
		else if (tok.CheckToken("front"))
		{
			type = eEnumPosType_Front;
		}
		else if (tok.CheckToken("back"))
		{
			type = eEnumPosType_Back;
		}
		else if (tok.CheckToken("left"))
		{
			type = eEnumPosType_Left;
		}
		else if (tok.CheckToken("right"))
		{
			type = eEnumPosType_Right;
		}
		m_StateMgr->GetCurState()->pProjInfo->postype = type;
	}
	else if( tok.CheckToken("projshadow") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->ShadowR = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->ShadowG = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->ShadowB = tok.GetInt();
	}
	else if( tok.CheckToken("supermovetime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nSuperMoveTime = tok.GetInt();
	}
	else if( tok.CheckToken("pausemovetime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pProjInfo->nPauseMoveTime  = tok.GetInt();
	}
	else{
		ParseHitDef(tok);
	}

}

void CStateParser::ParseExplod(CTokenizer &tok)
{
	if( tok.CheckToken("anim") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		const char* anim = tok.GetToken();
		int animValue = -1;
		EnumAnimType type;
		if (anim[0] == 'F'||anim[0] == 'f')
		{
			type = AnimFightFX;
			animValue = SDL_atoi(anim+1);
		}else{
			type = AnimPlayer;
			animValue = SDL_atoi(anim);
		}
		m_StateMgr->GetCurState()->pExplod->AnimType = type;
		m_StateMgr->GetCurState()->pExplod->nAnim = animValue;
	}
	else if( tok.CheckToken("ID") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->nExplodID = tok.GetInt();
	}
	else if( tok.CheckToken("pos") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);
		PLSTATE *curState = m_StateMgr->GetCurState();
		m_StateMgr->SetOpList(&curState->pExplod->posx);

		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		EvaluateExpression(tok);
		m_StateMgr->SetOpList(&curState->pExplod->posy);
	}
	else if( tok.CheckToken("postype") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EnumPosType type = eEnumPosType_P1;
		if (tok.CheckToken("p1"))
		{
			type = eEnumPosType_P1;
		}
		else if (tok.CheckToken("p2"))
		{
			type = eEnumPosType_P2;
		}
		else if (tok.CheckToken("front"))
		{
			type = eEnumPosType_Front;
		}
		else if (tok.CheckToken("back"))
		{
			type = eEnumPosType_Back;
		}
		else if (tok.CheckToken("left"))
		{
			type = eEnumPosType_Left;
		}
		else if (tok.CheckToken("right"))
		{
			type = eEnumPosType_Right;
		}
		m_StateMgr->GetCurState()->pExplod->postype = type;
	}
	else if( tok.CheckToken("facing") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->bFaceing = tok.GetInt();
	}
	else if( tok.CheckToken("vfacing") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->bVFaceing = tok.GetInt();
	}
	else if( tok.CheckToken("bindtime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->nBindtime = tok.GetInt();
	}
	else if( tok.CheckToken("vel") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float vx =0, vy = 0;
		vx = tok.GetFloat();
		if(tok.CheckToken(",") )
			vy = tok.GetFloat();
		m_StateMgr->GetCurState()->pExplod->velx = vx;
		m_StateMgr->GetCurState()->pExplod->vely = vy;
	}
	else if( tok.CheckToken("accel") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float ax = tok.GetFloat();
		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		float ay = tok.GetFloat();
		m_StateMgr->GetCurState()->pExplod->accelx = ax;
		m_StateMgr->GetCurState()->pExplod->accely = ay;
	}
	else if( tok.CheckToken("random") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float rx = tok.GetFloat();
		if( !tok.CheckToken(",") )
			Error("expected =",tok);  
		float ry = tok.GetFloat();
		m_StateMgr->GetCurState()->pExplod->nRandomX = rx;
		m_StateMgr->GetCurState()->pExplod->nRandomY = ry;
	}
	else if( tok.CheckToken("removetime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		Sint32 removetime = tok.GetInt();
		if(removetime==-2||removetime>0)
			PrintMessage("removetime is not right");
		m_StateMgr->GetCurState()->pExplod->nRemovetime = -2;
		
	}
	else if( tok.CheckToken("supermove") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->bSuperMove = tok.GetInt();
	}
	else if( tok.CheckToken("supermovetime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->nSuperMoveTime = tok.GetInt();
	}
	else if( tok.CheckToken("pausemovetime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->nPauseMoveTime  = tok.GetInt();
	}
	else if( tok.CheckToken("scale") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float sx = 1, sy = 1;
		sx = tok.GetFloat();
		if(tok.CheckToken(",") )
		{
			sy = tok.GetFloat();
		}
		else
		{
			sy = sx;
		}
		m_StateMgr->GetCurState()->pExplod->scalex = sx;
		m_StateMgr->GetCurState()->pExplod->scaley = sy;
	}
	else if( tok.CheckToken("sprpriority") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->nSprpriority = tok.GetInt();
	}
	else if( tok.CheckToken("ontop") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->bOnTop = tok.GetInt();
	}
	else if( tok.CheckToken("shadow") )
	{
		int r,g,b;
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		r =  tok.GetInt();
		g=b=r;
		if(tok.CheckToken(",") )
			g = tok.GetInt();
	
		if(tok.CheckToken(",") )
			b = tok.GetInt();

		m_StateMgr->GetCurState()->pExplod->ShadowR = r;
		m_StateMgr->GetCurState()->pExplod->ShadowG = g;
		m_StateMgr->GetCurState()->pExplod->ShadowB = b;
	}
	else if( tok.CheckToken("ownpal") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->bOwnPal = tok.GetInt();
	}
	else if( tok.CheckToken("removeongethit") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->bRemoveongethit = tok.GetInt();
	}
	else if( tok.CheckToken("ignorehitpause") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->bignorehitpause = tok.GetInt();
	}
	else if( tok.CheckToken("trans") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		const char* val2 = tok.GetToken();
		if (SDL_strcasecmp(val2, "none") == 0)
		{
			m_StateMgr->GetCurState()->pExplod->trans = eTransTypeNone;
		}else if(SDL_strcasecmp(val2, "add") == 0)
		{
			m_StateMgr->GetCurState()->pExplod->trans = eTransTypeAdd;
		}else if(SDL_strcasecmp(val2, "add1") == 0)
		{
			m_StateMgr->GetCurState()->pExplod->trans = eTransTypeAdd1;
		}else if(SDL_strcasecmp(val2, "sub") == 0)
		{
			m_StateMgr->GetCurState()->pExplod->trans = eTransTypeSub;
		}else if(SDL_strcasecmp(val2, "addalpha") == 0)
		{
			m_StateMgr->GetCurState()->pExplod->trans = eTransTypeAddAlpha;
		}
	}
	else if( tok.CheckToken("alpha") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		m_StateMgr->GetCurState()->pExplod->srcalpha = tok.GetInt();
		if( !tok.CheckToken(",") )
			Error("expected ,",tok); 
		m_StateMgr->GetCurState()->pExplod->desalpha = tok.GetInt();
	}
		CONTROL_PARAMS_PARSE_END(ParseExplod)
}

void CStateParser::ParseNotHitBy(CTokenizer &tok)
{
	if( tok.CheckToken("value") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  

		Sint32 param = GetHitDefAttr(tok);
		m_StateMgr->NewInst();
		m_StateMgr->AddInstruction(OP_PUSH, param, "#");
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_value);

	}
	CONTROL_PARAMS_PARSE(time)
		CONTROL_PARAMS_PARSE_END(ParseNotHitBy)
}

void CStateParser::ParseAddCommandInput(CTokenizer &tok)
{
	if( tok.CheckToken("command") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  

		const char* command = tok.GetToken();
		m_StateMgr->NewInst();
		m_StateMgr->AddInstruction(OP_PUSH, 0, command);
		m_StateMgr->AddInstruction(OP_STOP, 0, "OP_STOP");
		m_StateMgr->SetParam(CPN_Command);

	}
	CONTROL_PARAMS_PARSE(time)
		CONTROL_PARAMS_PARSE_END(ParseAddCommandInput)
}

void CStateParser::ParseChangeState(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(value)
		CONTROL_PARAMS_PARSE(ctrl)
		CONTROL_PARAMS_PARSE(anim)
		CONTROL_PARAMS_PARSE_END(ParseChangeState)
}
void CStateParser::ParseTargetState(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(value)
		CONTROL_PARAMS_PARSE(id)
		CONTROL_PARAMS_PARSE_END(ParseTargetState)
}

void CStateParser::ParseChangeAnim(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(value)
		CONTROL_PARAMS_PARSE(ctrl)
		CONTROL_PARAMS_PARSE(anim)
		CONTROL_PARAMS_PARSE_END(ParseChangeAnim)
}

void CStateParser::ParseEnvShake(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(time)
		CONTROL_PARAMS_PARSE(freq)
		CONTROL_PARAMS_PARSE(ampl)
		CONTROL_PARAMS_PARSE(phase)
		CONTROL_PARAMS_PARSE_END(ParseEnvShake);
}

void CStateParser::ParseEnvColor(CTokenizer &tok)
{
	CONTROL_PARAMS_PARSE_START(time)
		if( tok.CheckToken("value") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);  
			EvaluateExpression(tok);
			m_StateMgr->SetParam(CPN_color_r);

			if( !tok.CheckToken(",") )
				Error("expected =",tok);  
			EvaluateExpression(tok);
			m_StateMgr->SetParam(CPN_color_g);

			if( !tok.CheckToken(",") )
				Error("expected =",tok);  
			EvaluateExpression(tok);
			m_StateMgr->SetParam(CPN_color_b);
		}
		CONTROL_PARAMS_PARSE(under)
		CONTROL_PARAMS_PARSE_END(ParseEnvColor);
}

/*
 *	start parse the hit params
 */

#ifdef CONTROL_HIT_DEF_PARSE
#undef CONTROL_HIT_DEF_PARSE
#endif // CONTROL_HIT_DEF_DEFINE
#define CONTROL_HIT_DEF_PARSE_INT(name) else if( tok.CheckToken(#name) )\
{\
	if( !tok.CheckToken("=") )\
	Error("expected =",tok);  \
	Sint16 param = tok.GetInt();\
	m_StateMgr->SetHitDef_##name(param); \
}

#define PARSE_HITDEF_PARAM1(name) CONTROL_HIT_DEF_PARSE_INT(name)


#define PARSE_HITDEF_PARAM2(p1, p2) else if( tok.CheckToken(#p1"."#p2) )\
{\
	if( !tok.CheckToken("=") )\
	Error("expected =",tok); \
	while( !tok.AtEndOfLine() )\
	tok.GetToken();  \
}


#define PARSE_HITDEF_PARAM3(param1,param2, param3) else if( tok.CheckToken(#param1"."#param2"."#param3) )\
{\
	if( !tok.CheckToken("=") )\
	Error("expected =",tok); \
	while( !tok.AtEndOfLine() )\
	tok.GetToken();  \
}

#define PARSE_HITDEF_SKIP(param) else if( tok.CheckToken(#param) )\
{\
	if( !tok.CheckToken("=") )\
	Error("expected =",tok); \
	while( !tok.AtEndOfLine() )\
	tok.GetToken();  \
}

Sint32 CStateParser::GetHitDefAttr(CTokenizer &tok)
{
	Uint32 param = 0;
	char tmpTok[MAX_PATH];
	char first, second;
	if (!tok.CheckToken(",", false))
	{
		//to get a single char   
		tok.GetToken(tmpTok, MAX_PATH);
		for (int i= 0; i<SDL_strlen(tmpTok); i++)
		{
			first = tmpTok[i];
			//make sure we use uperchars
			if(first >= 97)
				first-=32;
			switch(first)
			{
			case 'S':
				param |= HitDef_Attr_Stand; 
				break;

			case 'C':
				param |= HitDef_Attr_Crouch;
				break;

			case 'A':
				param |=(HitDef_Attr_Aerial); 
				break;

			default:
				Error("Unknown Hit Attr",tok);
				break;
			}
		}
	}

	while (tok.CheckToken(","))
	{
		//to get a single char   
		const char* tokenStr=tok.GetToken();
		if (strlen(tokenStr)!=2)
		{
			Error("expected for hit attr =",tok);  
		}

		first=tokenStr[0];
		second=tokenStr[1];
		//make sure we use uperchars
		if(first >= 97)
			first-=32;
		if(second >= 97)
			second-=32;
		switch(first)
		{
		case 'N':
			switch(second)
			{
			case 'A':
				param |=(HitDef_Attr_NA); 
				break;

			case 'T':
				param |=(HitDef_Attr_NT);     
				break;

			case 'P':
				param |=(HitDef_Attr_NP); 
				break;
			default:
				Error("Unknown Hit Attr",tok);
				break;
			}
			break;

		case 'S':
			switch(second)
			{
			case 'A':
				param |=(HitDef_Attr_SA); 
				break;

			case 'T':
				param |=(HitDef_Attr_ST);     
				break;

			case 'P':
				param |=(HitDef_Attr_SP); 
				break;
			default:
				Error("Unknown Hit Attr",tok);
				break;
			}
			break;

		case 'H':
			switch(second)
			{
			case 'A':
				param |=(HitDef_Attr_HA); 
				break;

			case 'T':
				param |=(HitDef_Attr_HT);     
				break;

			case 'P':
				param |=(HitDef_Attr_HP); 
				break;
			default:
				Error("Unknown Hit Attr",tok);
				break;
			}
			break;

		case 'A':
			switch(second)
			{
			case 'A':
				param |=(HitDef_Attr_AA); 
				break;

			case 'T':
				param |=(HitDef_Attr_AT);     
				break;

			case 'P':
				param |=(HitDef_Attr_AP); 
				break;
			default:
				Error("Unknown Hit Attr",tok);
				break;
			}
			break;
		default:
			Error("Unknown Hit Attr",tok);
			break;
		}
	}
	return param;
}


void CStateParser::ParseHitDef(CTokenizer &tok)
{
	if( tok.CheckToken("attr") )
	{

		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		Uint32 param = GetHitDefAttr(tok);
		m_StateMgr->SetHitDef_attr(param); 
	}

	else if( tok.CheckToken("hitflag") )//HLAF ->SCAL
	{//以二进制形式保存

		if( !tok.CheckToken("=") )
			Error("expected =",tok);  

		//to get a single char   
		const char* tokenStr=tok.GetToken();
		int i = 0;
		u16 hitFlag = 0;
		while (tokenStr[i]!='\0')
		{
			char c = tokenStr[i];
			//make sure we use uperchars
			if(c >= 97)
				c-=32;
			switch (c)
			{
			case 'H':
				hitFlag |= 1<<s_stand;
				break;
			case 'L':
				hitFlag |= 1<<s_crouch;
				break;
			case 'M':
				hitFlag |= 1<<s_stand;
				hitFlag |= 1<<s_crouch;
				break;
			case 'A':
				hitFlag |= 1<<s_air;
				break;
			case 'F':
				hitFlag |= 1<<s_liedown;
				break;
			default:
				break;
			}
			i++;
		}
		if(tok.CheckToken("+") ){
			hitFlag |= 1<<(s_liedown+1);
		}
		else if(tok.CheckToken("-") ){
			hitFlag |= 1<<(s_liedown+2);
		}
		else
		{
			hitFlag |= 1<<(s_liedown+1);
			hitFlag |= 1<<(s_liedown+2);
		}
		m_StateMgr->SetHitDef_hitflag(hitFlag); 
	}

	else if( tok.CheckToken("guardflag") )//HLAF ->SCAL
	{//以二进制形式保存
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		//to get a single char   
		const char* tokenStr=tok.GetToken();
		int i = 0;
		u16 hitFlag = 0;
		while (tokenStr[i]!='\0')
		{
			char c = tokenStr[i];
			//make sure we use uperchars
			if(c >= 97)
				c-=32;
			switch (c)
			{
			case 'H':
				hitFlag |= 1<<s_stand;
				break;
			case 'L':
				hitFlag |= 1<<s_crouch;
				break;
			case 'M':
				hitFlag |= 1<<s_stand;
				hitFlag |= 1<<s_crouch;
				break;
			case 'A':
				hitFlag |= 1<<s_air;
				break;
			case 'F':
				hitFlag |= 1<<s_liedown;
				break;
			default:
				break;
			}
			i++;
		}
		m_StateMgr->SetHitDef_guardflag(hitFlag); 
	}		

	PARSE_HITDEF_SKIP(affectteam)

	else if( tok.CheckToken("animtype") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 aniType = HitDef_animtype_light;
		if(tok.CheckToken("light") )
			aniType = HitDef_animtype_light;
		if(tok.CheckToken("medium") || tok.CheckToken("med") )
			aniType = HitDef_animtype_medium;
		if(tok.CheckToken("hard") )
			aniType = HitDef_animtype_hard;
		if(tok.CheckToken("back") )
			aniType = HitDef_animtype_back;
		if(tok.CheckToken("up") )
			aniType = HitDef_animtype_up;
		if(tok.CheckToken("diagup") )
			aniType = HitDef_animtype_diagup;
		m_StateMgr->SetHitDef_animtype(aniType); 
	}
	else if( tok.CheckToken("air.animtype") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 aniType = HitDef_animtype_light;
		if(tok.CheckToken("light") )
			aniType = HitDef_animtype_light;
		if(tok.CheckToken("medium") || tok.CheckToken("med") )
			aniType = HitDef_animtype_medium;
		if(tok.CheckToken("hard") )
			aniType = HitDef_animtype_hard;
		if(tok.CheckToken("back") )
			aniType = HitDef_animtype_back;
		if(tok.CheckToken("up") )
			aniType = HitDef_animtype_up;
		if(tok.CheckToken("diagup") )
			aniType = HitDef_animtype_diagup;
		m_StateMgr->SetHitDef_air_animtype(aniType); 
	}		
	else if( tok.CheckToken("air.animtype") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 aniType = HitDef_animtype_light;
		if(tok.CheckToken("light") )
			aniType = HitDef_animtype_light;
		if(tok.CheckToken("medium") || tok.CheckToken("med") )
			aniType = HitDef_animtype_medium;
		if(tok.CheckToken("hard") )
			aniType = HitDef_animtype_hard;
		if(tok.CheckToken("back") )
			aniType = HitDef_animtype_back;
		if(tok.CheckToken("up") )
			aniType = HitDef_animtype_up;
		if(tok.CheckToken("diagup") )
			aniType = HitDef_animtype_diagup;
		m_StateMgr->SetHitDef_fall_animtype(aniType); 
	}	

	PARSE_HITDEF_PARAM1(priority)

	else if( tok.CheckToken("damage") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);  
		if(tok.CheckToken(","))
		{
			m_StateMgr->SetHitDef_hit_damage(); 
			EvaluateExpression(tok);  
			m_StateMgr->SetHitDef_guard_damage(); 
		}else{
			m_StateMgr->SetHitDef_hit_damage();
			m_StateMgr->SetHitDef_guard_damage(); 
		}

	}

	else if( tok.CheckToken("pausetime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 param1=0,param2=0;
		param1 = tok.GetInt();
		if(tok.CheckToken(",") )
			param2 = tok.GetInt();
		m_StateMgr->SetHitDef_pause_time(param1); 
		m_StateMgr->SetHitDef_shake_time(param2); 
	}

	else if( tok.CheckToken("guard.pausetime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 param1=0,param2=0;
		param1 = tok.GetInt();
		if(tok.CheckToken(",") )
			param2 = tok.GetInt();
		m_StateMgr->SetHitDef_guard_pause_time(param1); 
		m_StateMgr->SetHitDef_guard_shake_time(param2); 
	}
	else if( tok.CheckToken("sparkno") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		char param[MAX_PATH];
		Sint16 num = -1;
		tok.GetToken(param, MAX_PATH);
		if (param[0] == 's' || param[0]=='S')
		{
			num = SDL_atoi(param+1);
		}else{
			num = SDL_atoi(param);
		}
		m_StateMgr->SetHitDef_sparkno(num); 
	}
	else if( tok.CheckToken("guard.sparkno") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		char param[MAX_PATH];
		Sint16 num = -1;
		tok.GetToken(param, MAX_PATH);
		if (param[0] == 's' || param[0]=='S')
		{
			num = SDL_atoi(param+1);
		}else{
			num = SDL_atoi(param);
		}
		m_StateMgr->SetHitDef_guard_sparkno(num); 
	}
	else if( tok.CheckToken("sparkxy") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);  
		if(!tok.CheckToken(","))
		{
			Error("expected =",tok);  
		}
		m_StateMgr->SetHitDef_sparkno_x(); 
		EvaluateExpression(tok);  
		m_StateMgr->SetHitDef_sparkno_y(); 
	}
		PARSE_HITDEF_SKIP(hitsound)
		PARSE_HITDEF_SKIP(guardsound)

	else if( tok.CheckToken("ground.type") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 param = HitDef_atk_type_High;
		if(tok.CheckToken("High") )
			param = HitDef_atk_type_High;
		else if(tok.CheckToken("Low") )
			param = HitDef_atk_type_Low;
		else if(tok.CheckToken("Trip") )
			param = HitDef_atk_type_Trip;
		/*else
		{
		Error("ground.type is error", tok);

		}*/
		m_StateMgr->SetHitDef_ground_type(param); 
	}

	else if( tok.CheckToken("air.type") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 param = HitDef_atk_type_High;
		if(tok.CheckToken("High") )
			param = HitDef_atk_type_High;
		if(tok.CheckToken("Low") )
			param = HitDef_atk_type_Low;
		if(tok.CheckToken("Trip") )
			param = HitDef_atk_type_Trip;
		m_StateMgr->SetHitDef_air_type(param); 
	}
	else if( tok.CheckToken("ground.slidetime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);  
		m_StateMgr->SetHitDef_ground_slidetime(); 
	}
	else if( tok.CheckToken("guard.slidetime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);  
		m_StateMgr->SetHitDef_guard_slidetime(); 
	}
	else if( tok.CheckToken("ground.hittime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);  
		m_StateMgr->SetHitDef_ground_hittime(); 
	}
	else if( tok.CheckToken("guard.hittime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);  
		m_StateMgr->SetHitDef_guard_hittime(); 
	}
	else if( tok.CheckToken("air.hittime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);  
		m_StateMgr->SetHitDef_air_hittime(); 
	}
	else if( tok.CheckToken("guard.ctrltime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);  
		m_StateMgr->SetHitDef_guard_ctrltime(); 
	}
	else if( tok.CheckToken("airguard.ctrltime") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);  
		m_StateMgr->SetHitDef_airguard_ctrltime(); 
	}
	else if( tok.CheckToken("guard.dist"))
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int param = tok.GetInt();
		m_StateMgr->SetHitDef_guard_dist(param); 
	}
	else if( tok.CheckToken("yaccel") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float param = tok.GetFloat();
		m_StateMgr->SetHitDef_yaccel(param); 
	}
	else if( tok.CheckToken("ground.velocity") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		velocity param={0,0};
		param.x =  tok.GetFloat();
		if(tok.CheckToken(",") )
			param.y =  tok.GetFloat();
		m_StateMgr->SetHitDef_ground_velocity(param); 
	}
	else if( tok.CheckToken("guard.velocity") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		velocity param={0,0};
		param.x =  tok.GetFloat();
		if(tok.CheckToken(",") )
			param.y =  tok.GetFloat();
		m_StateMgr->SetHitDef_guard_velocity(param); 
	}
	else if( tok.CheckToken("air.velocity") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		velocity param={0,0};
		param.x =  tok.GetFloat();
		if(tok.CheckToken(",") )
			param.y =  tok.GetFloat();
		m_StateMgr->SetHitDef_air_velocity(param); 
	}
	else if( tok.CheckToken("airguard.velocity") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		velocity param={0,0};
		param.x =  tok.GetFloat();
		if(tok.CheckToken(",") )
			param.y =  tok.GetFloat();
		m_StateMgr->SetHitDef_airguard_velocity(param); 
	}
	else if( tok.CheckToken("down.velocity") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		velocity param={0,0};
		param.x =  tok.GetFloat();
		if(tok.CheckToken(",") )
			param.y =  tok.GetFloat();
		m_StateMgr->SetHitDef_airguard_velocity(param); 
	}
	PARSE_HITDEF_PARAM3(ground, cornerpush,veloff)
		PARSE_HITDEF_PARAM3(air, cornerpush,veloff)
		PARSE_HITDEF_PARAM3(down, cornerpush,veloff)
		PARSE_HITDEF_PARAM3(guard, cornerpush,veloff)
		PARSE_HITDEF_PARAM3(airguard, cornerpush,veloff)
	else if( tok.CheckToken("air.juggle") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int value =  tok.GetInt();
		m_StateMgr->SetHitDef_air_juggle(value); 
	}
		PARSE_HITDEF_SKIP(mindist)
		PARSE_HITDEF_SKIP(maxdist)
		PARSE_HITDEF_SKIP(snap)
	else if( tok.CheckToken("p1sprpriority") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);  
			int value =  tok.GetInt();
			m_StateMgr->SetHitDef_p1sprpriority(value); 
	}
	else if( tok.CheckToken("p2sprpriority") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int value =  tok.GetInt();
		m_StateMgr->SetHitDef_p2sprpriority(value); 
		}
		PARSE_HITDEF_SKIP(p1facing)
		PARSE_HITDEF_SKIP(p1getp2facing)
		PARSE_HITDEF_SKIP(p2facing)
	else if( tok.CheckToken("p1stateno") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int value =  tok.GetInt();
		m_StateMgr->SetHitDef_p1stateno(value); 
	}
	else if( tok.CheckToken("p2stateno") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int value =  tok.GetInt();
		m_StateMgr->SetHitDef_p2stateno(value); 
	}
		PARSE_HITDEF_SKIP(p2getp1state)
		PARSE_HITDEF_SKIP(forcestand)

	else if( tok.CheckToken("fall") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 param = tok.GetInt();
		m_StateMgr->SetHitDef_fall(param); 
	}
	else if( tok.CheckToken("fall.xvelocity") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float param = tok.GetFloat();
		m_StateMgr->SetHitDef_fall_xvelocity(param); 
	}		
	else if( tok.CheckToken("fall.yvelocity") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float param = tok.GetFloat();
		m_StateMgr->SetHitDef_fall_yvelocity(param); 
	}	
	PARSE_HITDEF_PARAM2(fall,recover)
		PARSE_HITDEF_PARAM2(fall,recovertime)
	else if( tok.CheckToken("fall.damage") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 param = tok.GetInt();
		m_StateMgr->SetHitDef_fall_damage(param); 
	}	
	PARSE_HITDEF_PARAM2(air,fall)
		PARSE_HITDEF_SKIP(forcenofall)
		PARSE_HITDEF_PARAM2(down,velocity)
		PARSE_HITDEF_PARAM2(down,hittime)
		PARSE_HITDEF_PARAM2(down,bounce)
		PARSE_HITDEF_SKIP(id)
		PARSE_HITDEF_SKIP(chainID)
		PARSE_HITDEF_SKIP(nochainID)
		PARSE_HITDEF_SKIP(hitonce)
		PARSE_HITDEF_SKIP(kill)
		PARSE_HITDEF_PARAM2(guard,kill)
		PARSE_HITDEF_PARAM2(fall,kill)
	else if( tok.CheckToken("numhits") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 param = tok.GetInt();
		m_StateMgr->SetHitDef_numhits(param); 
	}	
	else if( tok.CheckToken("getpower") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 param1=0,param2=0;
		param1 = tok.GetInt();
		if(tok.CheckToken(",") )
			param2 = tok.GetInt();
		else
		{
			param2 = param1/2;
		}
		m_StateMgr->SetHitDef_getpower(param1); 
		m_StateMgr->SetHitDef_guard_getpower(param2); 
	}
	else if( tok.CheckToken("givepower") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		u16 param1=0,param2=0;
		param1 = tok.GetInt();
		if(tok.CheckToken(",") )
			param2 = tok.GetInt();
		else
		{
			param2 = param1/2;
		}
		m_StateMgr->SetHitDef_givepower(param1); 
		m_StateMgr->SetHitDef_guard_givepower(param2); 
	}
	else if( tok.CheckToken("palfx.time") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		EvaluateExpression(tok);  
		m_StateMgr->SetHitDef_palfx_time(); 
	}
	else if( tok.CheckToken("palfx.color") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float val1 = tok.GetFloat()/256.0;
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.palcolor = val1; 
	}
	else if( tok.CheckToken("palfx.invertall") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		int val1 = tok.GetInt();
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.palinvertall = val1; 
	}
	else if( tok.CheckToken("palfx.add") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float val1 = tok.GetFloat()/256.0;
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.palbright.r = val1; 
		if( !tok.CheckToken(",") )
			Error("expected ,",tok); 
		float val2 = tok.GetFloat()/256.0;
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.palbright.g = val2; 
		if( !tok.CheckToken(",") )
			Error("expected ,",tok); 
		float val3 = tok.GetFloat()/256.0;
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.palbright.b = val3; 
	}
	else if( tok.CheckToken("palfx.mul") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float val1 = tok.GetFloat()/256.0;
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.palcontrast.r = val1; 
		if( !tok.CheckToken(",") )
			Error("expected ,",tok); 
		float val2 = tok.GetFloat()/256.0;
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.palcontrast.g = val2; 
		if( !tok.CheckToken(",") )
			Error("expected ,",tok); 
		float val3 = tok.GetFloat()/256.0;
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.palcontrast.b = val3; 
	}
	else if( tok.CheckToken("palfx.sinadd") )
	{
		if( !tok.CheckToken("=") )
			Error("expected =",tok);  
		float val1 = tok.GetFloat()/256.0;
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.sinadd.r = val1; 
		if( !tok.CheckToken(",") )
			Error("expected ,",tok); 
		float val2 = tok.GetFloat()/256.0;
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.sinadd.g = val2; 
		if( !tok.CheckToken(",") )
			Error("expected ,",tok); 
		float val3 = tok.GetFloat()/256.0;
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.sinadd.b = val3; 
		if( !tok.CheckToken(",") )
			Error("expected ,",tok); 
		float val4 = tok.GetFloat();
		m_StateMgr->GetCurState()->pConHDdef->palfxinfo.sinperiod = val4; 
	}
		PARSE_HITDEF_PARAM2(envshake,time)
		PARSE_HITDEF_PARAM2(envshake,freq)
		PARSE_HITDEF_PARAM2(envshake,ampl)
		PARSE_HITDEF_PARAM2(envshake,phase)
		PARSE_HITDEF_PARAM3(fall, envshake,time)
		PARSE_HITDEF_PARAM3(fall, envshake,freq)
		PARSE_HITDEF_PARAM3(fall, envshake,ampl)
		PARSE_HITDEF_PARAM3(fall, envshake,phase)
	CONTROL_PARAMS_PARSE_END(ParseHitDef);    

}
