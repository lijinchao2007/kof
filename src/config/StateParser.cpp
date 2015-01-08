/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "StateParser.h"
#include "tool.h"

CStateParser::CStateParser(CCharsConfig* charMgr, CStateManager* stateMgr)
{
	m_nPrimaryArgc = 0;
	m_StateMgr = stateMgr;
	m_CharMgr = charMgr;
}

CStateParser::~CStateParser()
{
}

void CStateParser::Error(const char * strErrorMsg,CTokenizer &tok)
{
	CError error("Parser error:\nin file %s at line %d:token:%s error:%s",tok.GetFileName()
		,tok.GetLineNumber()
		,tok.GetPartToken()
		,strErrorMsg);
	throw(error);                  
}

void CStateParser::ParseStateFile(const char* strFileName)
{
	PrintMessage("ParseStateFile strFileName %s ", strFileName);
	CTokenizer tok;
	bool foundState=false;

	if( !tok.OpenFile(strFileName) )
		throw(CError("CStateParser::ParseState: File %s not found",strFileName));

	tok.SetIsCaseSensitive(false);
	tok.SetReturnNegativeSeperatelyFromNumber(false);


	while( !tok.AtEndOfFile() )
	{
		foundState=false;

		if( tok.CheckToken("[") )
		{

			if( tok.CheckToken("statedef") )
			{
				foundState=true;
				if(!tok.CheckTokenIsNumber())
					Error("Expected a number in statedef block",tok);
				int stateNum = tok.GetInt();
				/*if (stateNum ==10499)
				{
				PrintMessage("");
				}*/
				m_StateMgr->AddStateDef(stateNum);
				PrintMessage("AddStateDef %i",stateNum);
				if (stateNum == 230)
				{
					PrintMessage("");
				}
				GET_ALL_LINE_TOKEN(tok);
				ParseStateDef(tok);        

			}else if( tok.CheckToken("state") )
			{
				foundState=true;  
				char stNum[MAX_PATH]={0},strStateInfo[MAX_PATH]={0}; 
				tok.GetToken(stNum, MAX_PATH);
				if(tok.CheckToken(",", true))
				{
					if (!tok.CheckToken("]", false))
					{
						tok.GetToken(strStateInfo, MAX_PATH);
						// controllerflag
						if (SDL_strcasecmp("testintervalop", strStateInfo) ==0)
						{
							PrintMessage("");
						}
					}
				}
				while( !tok.CheckToken("]") )
					tok.GetToken();  

				// 加入状态
				m_StateMgr->AddState(stNum,strStateInfo);

				PareseState(tok);
			}
		}

		//skip useless stuff
		if(!foundState)
			GET_ALL_LINE_TOKEN(tok);

	}

	tok.CloseFile();
}

void CStateParser::ParseStateDef(CTokenizer &tok)
{
	while( !tok.CheckToken("[",false) && !tok.AtEndOfFile() )
	{
		//parse state type
		if( tok.CheckToken("type") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			//to get a single char   
			char c=tok.GetToken()[0];
			//make sure we use uperchars
			if(c >= 97)
				c-=32;


			switch(c)
			{
			case 'S':
				m_StateMgr->SetStateDefType(s_stand); 
				break;

			case 'C':
				m_StateMgr->SetStateDefType(s_crouch);     
				break;

			case 'A':
				m_StateMgr->SetStateDefType(s_air); 
				break;

			case 'L':
				m_StateMgr->SetStateDefType(s_liedown);     
				break;

			case 'U':
				m_StateMgr->SetStateDefType(s_untouch);    
				break;

			default:
				Error("Unknown statetype",tok);
				break;


			}

		} else if( tok.CheckToken("movetype") )
		{
			if( !tok.CheckToken("=") )
				Error("expected '=' in line ",tok);

			//to get a single char   
			char c=tok.GetToken()[0];
			//make sure we use uperchars
			if(c >= 97)
				c-=32;

			switch(c)
			{
			case 'A':
				m_StateMgr->SetStateMoveType(m_attack);
				break;

			case 'I':
				m_StateMgr->SetStateMoveType(m_idle);
				break;

			case 'H':
				m_StateMgr->SetStateMoveType(m_hit);
				break;

			case 'U':
				m_StateMgr->SetStateMoveType(m_untouch);
				break;

			default:
				Error("Unknown movetype",tok);
				break;



			}      



		} else if( tok.CheckToken("physics") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			//to get a single char   
			char c=tok.GetToken()[0];
			//make sure we use uperchars
			if(c >= 97)
				c-=32;


			switch(c)
			{
			case 'S':
				m_StateMgr->SetStatePhysicType(p_stand); 
				break;

			case 'C':
				m_StateMgr->SetStatePhysicType(p_crouch);     
				break;

			case 'A':
				m_StateMgr->SetStatePhysicType(p_air); 
				break;

			case 'N':
				m_StateMgr->SetStatePhysicType(p_none);     
				break;

			case 'U':
				m_StateMgr->SetStatePhysicType(p_untouch);    
				break;

			default:
				Error("Unknown physic type",tok);
				break;


			}



		} else if( tok.CheckToken("anim") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			EvaluateExpression(tok);
			m_StateMgr->SetStateAnim();  


		} else if( tok.CheckToken("velset") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			float x=tok.GetFloat();
			float y = x;
			if( tok.CheckToken(",") )
				y=tok.GetFloat();
			m_StateMgr->SetVelSet(x,y);     

		} else if( tok.CheckToken("ctrl") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			if(!tok.CheckTokenIsNumber())
				Error("Expected a number for ctrl",tok);

			m_StateMgr->SetStateCtrl(tok.GetInt());    

		} else if( tok.CheckToken("poweradd") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			if(!tok.CheckTokenIsNumber())
				Error("Expected a number for poweradd",tok);      

			m_StateMgr->SetStatePowerAdd(tok.GetInt());  

		} else if( tok.CheckToken("juggle") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			if(!tok.CheckTokenIsNumber())
				Error("Expected a number for juggle",tok);

			m_StateMgr->SetStateJuggle(tok.GetInt());              

		} else if( tok.CheckToken("facep2") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			if( !tok.CheckTokenIsNumber() )
				Error("Expected a number for facep2",tok);

			m_StateMgr->SetStateFaceP2((bool)tok.GetInt());   

		} else if( tok.CheckToken("hitdefpersist") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			if( !tok.CheckTokenIsNumber() )
				Error("Expected a number for hitdefpersist",tok); 

			m_StateMgr->SetStateHitDefPresit((bool)tok.GetInt());   

		} else if( tok.CheckToken("movehitpersist") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			if( !tok.CheckTokenIsNumber() )
				Error("Expected a number for movehitpersist",tok);

			m_StateMgr->SetMoveHitPresit((bool)tok.GetInt());  

		} else if( tok.CheckToken("hitcountpersist") )
		{ 
			if( !tok.CheckToken("=") )
				Error("expected =",tok);

			if( !tok.CheckTokenIsNumber() )
				Error("Expected a number for hitcountpersist",tok);

			m_StateMgr->SetStateHitCounterPresit((bool)tok.GetInt());  


		} else if( tok.CheckToken("sprpriority") )
		{
			if( !tok.CheckToken("=") )
				Error("expected =",tok); 

			if( !tok.CheckTokenIsNumber() )
				Error("Expected a number for sprpriority",tok);

			m_StateMgr->SetSprPriority(tok.GetInt()); 

		}else //faile in statedef
		{
			ParseWarning(tok, "Unknown token for ParseStateDef");
			GET_ALL_LINE_TOKEN(tok);
		}


	}

}

void CStateParser::PareseState(CTokenizer &tok)
{
	Sint32 nController = -10;
	// 暂时支持三条tirgger，不支持triggerall 
	while( !tok.CheckToken("[",false) && !tok.AtEndOfFile() )
	{
		if (tok.CheckToken("type"))
		{
			if( !tok.CheckToken("=") )
				throw(CError("expected ="));
			const char* type = tok.GetToken();
			//PrintMessage("PareseState state control type :%s", type);
			nController=GetControllerType(type,tok);
			m_StateMgr->AddTypeToState(nController);
		}else if (tok.CheckToken("triggerall"))
		{
			ParseTrigger(tok);
			m_StateMgr->AddTriggerToState(0);
		}else if (tok.CheckToken("trigger", false, 7))
		{
			const char* triggerName = tok.GetToken();
			int triggerIndex = SDL_atoi(triggerName+7);
			ParseTrigger(tok);
			m_StateMgr->AddTriggerToState(triggerIndex);
		}else
		{
			if (nController == -10)
			{
				PrintWaring("PareseState type is unknow!");
				GET_ALL_LINE_TOKEN(tok);
			}else{
				ParserController(tok,nController); 
			}
			
		}
	}

}

void CStateParser::ParseTrigger(CTokenizer &tok)
{
	if (!tok.CheckToken("="))
	{
		Error("ParseTrigger error, expect =", tok);
	}
	EvaluateExpression(tok);
}


//Generates the Opcode sequenz for the trigger statement
//evaluates and + and - expression
void CStateParser::EvaluateExpression(CTokenizer &tok)
{
	m_StateMgr->NewInst();
	tok.SetReturnNegativeSeperatelyFromNumber(true);
	// 加入OP_STOP
	m_StateMgr->PushOp(OP_STOP,"OP_STOP");
	Term(tok);
	while(!m_StateMgr->OpStackEnd())  
	{  
		m_StateMgr->PopOp();
	}  
	tok.SetReturnNegativeSeperatelyFromNumber(false);
}

void CStateParser::Term(CTokenizer &tok)
{
	Primary(tok);
	//search for operators 
	while( tok.CheckToken("*",false) || tok.CheckToken("/",false)  || 
		tok.CheckToken("=",false) || tok.CheckToken("!=",false) || tok.CheckToken(":=",false) ||
		tok.CheckToken("<",false) || tok.CheckToken("<=",false) ||
		tok.CheckToken(">",false) || tok.CheckToken(">=",false) ||
		tok.CheckToken("|",false) ||  tok.CheckToken("&&",false) || 
		tok.CheckToken("||",false)|| tok.CheckToken("^^",false) ||
		tok.CheckToken("&",false) || tok.CheckToken("~",false)  ||
		tok.CheckToken("+",false) || tok.CheckToken("-",false)  || 
		tok.CheckToken("%",false) || (tok.CheckToken("(",false) && !tok.AtEndOfLine()) )
	{  

		if( tok.CheckToken("*") )
		{
			PRECEDENCE_OP(OP_MUL);
		}

		//Have we a ** operator?
		if( tok.CheckToken("**") )
		{
			PRECEDENCE_OP(OP_SQUARE);
		}

		if( tok.CheckToken("/") )
		{
			PRECEDENCE_OP(OP_DIV);
		}
		if( tok.CheckToken("+") )
		{
			PRECEDENCE_OP(OP_ADD);
		}
		if( tok.CheckToken("-") )
		{
			PRECEDENCE_OP(OP_SUB);
		}

		if( tok.CheckToken("=") )
		{    
			//check for intervall operator
			if( tok.CheckToken("(") )
			{
				while(m_StateMgr->PrecedenceOp(OP_INTERVALOP1)<0)  
				{  
					m_StateMgr->PopOp();
				} 
				//evaluate first expression                   
				Term(tok);
				if( !tok.CheckToken(",") )
					Error("Expectetd a , in intervall operator",tok);

				//evaluate second expression 
				Term(tok);

				//intervall op =(,)
				if( tok.CheckToken(")") )
				{
					m_StateMgr->AddInstruction(OP_INTERVALOP4,0,"OP_INTERVALOP4");
				}else if( tok.CheckToken("]") )
				{
					m_StateMgr->AddInstruction(OP_INTERVALOP3,0,"OP_INTERVALOP3");
				}

			}else if (tok.CheckToken("[") )
			{
				while(m_StateMgr->PrecedenceOp(OP_INTERVALOP1)<0)  
				{  
					m_StateMgr->PopOp();
				} 
				//evaluate first expression                   
				Term(tok);
				if( !tok.CheckToken(",") )
					Error("Expectetd a , in intervall operator",tok);

				//evaluate second expression 
				Term(tok);

				//intervall op =[,)
				if( tok.CheckToken(")") )
				{
					m_StateMgr->AddInstruction(OP_INTERVALOP2,0,"OP_INTERVALOP2");
				}else if( tok.CheckToken("]") )
				{
					m_StateMgr->AddInstruction(OP_INTERVALOP1,0,"OP_INTERVALOP1");
				}

			}
			else // is the = op
			{          
				PRECEDENCE_OP(OP_EQUAL);
			}
		}

		if( tok.CheckToken("!=") )
		{    //evalute the right side of the operator
			//check for intervall operator
			if( tok.CheckToken("(") )
			{
				while(m_StateMgr->PrecedenceOp(OP_INTERVALOP1)<0)  
				{  
					m_StateMgr->PopOp();
				} 
				//evaluate first expression                   
				Term(tok);
				if( !tok.CheckToken(",") )
					Error("Expectetd a , in intervall operator",tok);

				//evaluate second expression 
				Term(tok);

				//intervall op !=(,)
				if( tok.CheckToken(")") )
				{
					m_StateMgr->AddInstruction(OP_INTERVALOP8,0,"OP_INTERVALOP8");
				}else if( tok.CheckToken("]") )
				{
					m_StateMgr->AddInstruction(OP_INTERVALOP7,0,"OP_INTERVALOP7");
				}

			}else if (tok.CheckToken("[") )
			{
				while(m_StateMgr->PrecedenceOp(OP_INTERVALOP1)<0)  
				{  
					m_StateMgr->PopOp();
				} 
				//evaluate first expression                   
				Term(tok);
				if( !tok.CheckToken(",") )
					Error("Expectetd a , in intervall operator",tok);

				//evaluate second expression 
				Term(tok);

				//intervall op !=[,)
				if( tok.CheckToken(")") )
				{
					m_StateMgr->AddInstruction(OP_INTERVALOP6,0,"OP_INTERVALOP6");
				}else if( tok.CheckToken("]") )
				{
					m_StateMgr->AddInstruction(OP_INTERVALOP5,0,"OP_INTERVALOP5");
				}

			}
			else // is the != op
			{                
				PRECEDENCE_OP(OP_NOTEQUAL);
			}
		}

		if( tok.CheckToken(":=") )
		{    //evalute the right side of the operator
			PRECEDENCE_OP(OP_ASSIGN);
		}

		if( tok.CheckToken("<") )
		{    //evalute the right side of the operator
			PRECEDENCE_OP(OP_LESS);
		}

		if( tok.CheckToken("<=") )
		{    //evalute the right side of the operator
			PRECEDENCE_OP(OP_LESSEQUAL);
		}

		if( tok.CheckToken(">") )
		{    
			while(m_StateMgr->PrecedenceOp(OP_GREATER)<0)  
			{  
				m_StateMgr->PopOp();
			}  
			m_StateMgr->PushOp(OP_GREATER, "OP_GREATER");
			Term(tok);
		}

		if( tok.CheckToken(">=") )
		{    //evalute the right side of the operator
			PRECEDENCE_OP(OP_GRAETEREQUAL);
		}

		if( tok.CheckToken("&&") )
		{   
			while(m_StateMgr->PrecedenceOp(OP_LOGAND)<0)  
			{  
				m_StateMgr->PopOp();
			}  
			m_StateMgr->PushOp(OP_LOGAND, "OP_LOGAND");
			Term(tok);

		}

		if( tok.CheckToken("(") )
		{
			m_StateMgr->PushOp(OP_LEFT, "OP_LEFT");
			Term(tok);
			if( !tok.CheckToken(")") )
			{
				ParseWarning(tok, "Missing )");
				GET_ALL_LINE_TOKEN(tok);
			}
			while(m_StateMgr->PopOp() != OP_LEFT)
				// 将左括号删掉
					m_StateMgr->DelpInstTop();
		}

		if( tok.CheckToken("||") )
		{    //evalute the right side of the operator
			PRECEDENCE_OP(OP_LOGOR);
		}

		if( tok.CheckToken("^^") ) // is this realy needed?
		{    //evalute the right side of the operator
			PRECEDENCE_OP(OP_LOGXOR);
		}

		if( tok.CheckToken("&") ) 
		{    //evalute the right side of the operator
			PRECEDENCE_OP(OP_AND);
		}


		if( tok.CheckToken("|") ) 
		{    //evalute the right side of the operator
			PRECEDENCE_OP(OP_OR);
		}

		if( tok.CheckToken("^") ) 
		{    //evalute the right side of the operator
			PRECEDENCE_OP(OP_XOR);
		}

		if( tok.CheckToken("%") ) 
		{    //evalute the right side of the operator
			PRECEDENCE_OP(OP_MOD);
		}

	}

}

//evaluates a primary
void CStateParser::Primary(CTokenizer &tok)
{
	//a negate operator
	if( tok.CheckToken("-") )
	{
		Primary(tok);
		m_StateMgr->AddInstruction(OP_NEG,0,"OP_NEG");  
	}

	else if( tok.CheckToken("!") )
	{
		Primary(tok);
		m_StateMgr->AddInstruction(OP_LOGNOT,0,"OP_LOGNOT");

	} 

	else if( tok.CheckToken("~") ) 
	{    //evalute the right side of the operator
		Primary(tok);
		m_StateMgr->AddInstruction(OP_NOT,0,"OP_NOT");
	}

	else if( tok.CheckTokenIsNumber() )
	{
		m_StateMgr->AddInstruction(OP_PUSH,tok.GetFloat(),"OP_PUSH");
	}

	else if( tok.CheckTokenIsQuotedString() )
	{
		m_StateMgr->AddInstruction(OP_PUSH,0,tok.GetToken());  
	}
	else if( tok.CheckToken("(") )
	{
		m_StateMgr->PushOp(OP_LEFT, "OP_LEFT");
		Term(tok);
		while(m_StateMgr->PopOp() != OP_LEFT);
		m_StateMgr->DelpInstTop();
		if( !tok.CheckToken(")") )
		{
			ParseWarning(tok, "Missing )");
			GET_ALL_LINE_TOKEN(tok);
		}
	}
	else //check for a trigger name
	{
		const char *tokStr = tok.GetToken();
		int i=GetTriggerType(tokStr,tok);
		if (i != -1)
		{
			if (!(m_nPrimaryArgc == 0 || m_nPrimaryArgc == -1))
			{
				ParseWarning(tok, "m_nPrimaryArgc should be zero");
				m_nPrimaryArgc =0;
			}
			m_nPrimaryArgc =GetOPArgc(i,tok);

			if (ERROR_ARGCS == m_nPrimaryArgc)
			{			
				Error("m_nPrimaryArgc error", tok);
			}
			else if(SPECIAL_ARGCS == m_nPrimaryArgc)
			{
				PrimarySpecialOP(tok, i);
			}
			else
			{
				char strOpToken[MAX_PATH] = {0};
				SDL_strlcpy(strOpToken, tokStr, MAX_PATH);
				while (m_nPrimaryArgc>0)
				{
					m_nPrimaryArgc --;
					//m_StateMgr->PushInt(m_nPrimaryArgc);
					Primary(tok);
					//m_nPrimaryArgc = m_StateMgr->PopInt();
				}
				m_StateMgr->AddInstruction(i,0,strOpToken);
			}
		}
		else
		{
			// 处理x，y，或者其他特殊参数
			if (SDL_strncasecmp("ProjHit", tokStr, 7)==0)
			{
				//Error("please use ProjHitTime", tok);
				int id = SDL_atoi(tokStr+7);
				m_StateMgr->AddInstruction(OP_PUSH,id,"#");
				m_StateMgr->AddInstruction(OP_ProjHitTime,0,"#");
			}
			if (SDL_strncasecmp("ProjGuarded", tokStr, 11)==0)
			{
				//Error("please use ProjGuardedTime", tok);
				int id = SDL_atoi(tokStr+11);
				m_StateMgr->AddInstruction(OP_PUSH,id,"#");
				m_StateMgr->AddInstruction(OP_ProjGuardedTime,0,"#");
			}
			if (SDL_strncasecmp("ProjContact", tokStr, 11)==0)
			{
				//Error("please use ProjContactTime", tok);
				int id = SDL_atoi(tokStr+11);
				m_StateMgr->AddInstruction(OP_PUSH,id,"#");
				m_StateMgr->AddInstruction(OP_ProjContactTime,0,"#");
			}

			m_StateMgr->AddInstruction(OP_PUSH,0,tokStr);
		}

	}

}


void CStateParser::PrimarySpecialOP(CTokenizer &tok, Uint32 i)
{
	if(i==OP_AnimElem)
	{
		// change to AnimElemTime
		Uint32 animNo = 0;
		Uint32 secondOp = OP_EQUAL;
		Sint32 passTime = 0;
		if(!tok.CheckToken("=")){
			Error("OP_HitDefAttr error",tok);
		}
		animNo = tok.GetInt();
		tok.SetReturnNegativeSeperatelyFromNumber(false);
		if (tok.CheckToken(","))
		{
			if (tok.CheckToken("!")&&tok.CheckToken("="))
			{
				secondOp = OP_NOTEQUAL;
			}else if(tok.CheckToken("=")){
				secondOp = OP_EQUAL;
			}else if(tok.CheckToken("<")){
				secondOp = OP_LESS;
			}else if(tok.CheckToken(">")){
				secondOp = OP_GREATER;
			}else if (tok.CheckToken("<="))
			{
				secondOp = OP_LESSEQUAL;
			}else if (tok.CheckToken(">="))
			{
				secondOp = OP_GRAETEREQUAL;
			}else
			{
				secondOp = OP_EQUAL;
			}
			passTime = tok.GetInt();
		}
		tok.SetReturnNegativeSeperatelyFromNumber(true);

		m_StateMgr->AddInstruction(OP_PUSH,(float)animNo,"#");
		m_StateMgr->AddInstruction(OP_AnimElemTime,0,"OP_AnimElem");
		m_StateMgr->AddInstruction(OP_PUSH,passTime,"#");
		m_StateMgr->AddInstruction(secondOp,0,"Compaire_OP");

	}
	else if (i == OP_Cond || i == OP_Exp)
	{
		CAssert(false, "not support");
		m_StateMgr->PushOp(OP_LEFT, "ifelse");
		tok.CheckToken("(");
		Term(tok);
		while(m_StateMgr->PopOp() != OP_LEFT);
		m_StateMgr->DelpInstTop();
		m_StateMgr->PushOp(OP_LEFT, "ifelse");
		tok.CheckToken(",");
		Term(tok);
		while(m_StateMgr->PopOp() != OP_LEFT);
		m_StateMgr->DelpInstTop();
		m_StateMgr->PushOp(OP_LEFT, "ifelse");
		tok.CheckToken(",");
		Term(tok);
		while(m_StateMgr->PopOp() != OP_LEFT);
		m_StateMgr->DelpInstTop();
		tok.CheckToken(")");
		m_StateMgr->AddInstruction(OP_IfElse,0,"ifElse");
	}
	else if(i==OP_HitDefAttr)
	{
		Uint32 equalOP = 0;
		Uint32 needFlag = 0;
		if (tok.CheckToken("!")&&tok.CheckToken("=")||tok.CheckToken("!="))
		{
			equalOP = OP_NOTEQUAL;
		}else if(tok.CheckToken("=")){
			equalOP = OP_EQUAL;
		}else{
			Error("OP_HitDefAttr error",tok);
		}
		Uint32 param = GetHitDefAttr(tok);

		m_StateMgr->AddInstruction(i,0,"OP_HitDefAttr");
		m_StateMgr->AddInstruction(OP_PUSH,(float)param,"#");
		m_StateMgr->AddInstruction(equalOP,0,"Compaire_OP");

	}
	else if (i == OP_IfElse)
	{
		m_StateMgr->PushOp(OP_LEFT, "ifelse");
		tok.CheckToken("(");
		Term(tok);
		while(m_StateMgr->PopOp() != OP_LEFT);
		m_StateMgr->DelpInstTop();
		m_StateMgr->PushOp(OP_LEFT, "ifelse");
		tok.CheckToken(",");
		Term(tok);
		while(m_StateMgr->PopOp() != OP_LEFT);
		m_StateMgr->DelpInstTop();
		m_StateMgr->PushOp(OP_LEFT, "ifelse");
		tok.CheckToken(",");
		Term(tok);
		while(m_StateMgr->PopOp() != OP_LEFT);
		m_StateMgr->DelpInstTop();
		tok.CheckToken(")");
		m_StateMgr->AddInstruction(OP_IfElse,0,"ifElse");
	}
	else if (i == OP_IsHelper)
	{
		//m_StateMgr->AddInstruction(OP_TeamMode,0,"OP_TeamMode");
		int helpId = -1;
		if (tok.CheckToken("("))
		{
			helpId = tok.GetInt();
			if (!tok.CheckToken(")"))
			{
				Error("OP_IsHelper expect )", tok);
			}
		}
		m_StateMgr->AddInstruction(OP_PUSH, helpId,"#");
		m_StateMgr->AddInstruction(OP_IsHelper, 0,"#");
	}
	else if(i==OP_Log)
	{
		if (!tok.CheckToken("("))
		{
			Error("OP_Log need (", tok);
		}
		tok.SetReturnNegativeSeperatelyFromNumber(false);
		Sint32 value1 = tok.GetInt();
		if (!tok.CheckToken(","))
		{
			Error("OP_Log need ,", tok);
		}
		Sint32 value2 = tok.GetInt();
		if (!tok.CheckToken(")"))
		{
			Error("OP_Log need )",tok);
		}
		tok.SetReturnNegativeSeperatelyFromNumber(true);

		m_StateMgr->AddInstruction(OP_PUSH,value1,"#");
		m_StateMgr->AddInstruction(OP_PUSH,value2,"#");
		m_StateMgr->AddInstruction(OP_Log,0,"OP_Log");

	}
	else if (i == OP_NumExplod || i==OP_NumHelper || i==OP_NumTarget)
	{
		Sint32 id = -1;
		if (tok.CheckToken("("))
		{
			id = tok.GetInt();
			if (!tok.CheckToken(")"))
			{
				Error("OP_Numxxx need )", tok);
			}
		}
		m_StateMgr->AddInstruction(OP_PUSH, id,"#");
		m_StateMgr->AddInstruction(i,0,"OP_Numxxx");
	}
	else if (i == OP_TeamMode)
	{
		//m_StateMgr->AddInstruction(OP_TeamMode,0,"OP_TeamMode");
		if (!tok.CheckToken("="))
		{
			Error("OP_enemynear expect =", tok);
		}
		tok.GetToken();
		m_StateMgr->AddInstruction(OP_PUSH, 0,"#");
	}
	else if (i == OP_TimeMod)
	{
		//m_StateMgr->AddInstruction(OP_TeamMode,0,"OP_TeamMode");
		if (!tok.CheckToken("="))
		{
			Error("OP_TimeMod expect =", tok);
		}
		int vlaue1 = tok.GetInt();
		if (!tok.CheckToken(","))
		{
			Error("OP_TimeMod expect ,", tok);
		}
		int value2 = tok.GetInt();
		m_StateMgr->AddInstruction(OP_PUSH, vlaue1,"#");
		m_StateMgr->AddInstruction(OP_PUSH, value2,"#");
		m_StateMgr->AddInstruction(OP_TimeMod, 0,"#");
	}
	else if (i == OP_parent)
	{
		m_StateMgr->AddInstruction(OP_parent,0,"OP_parent");
		if (!tok.CheckToken(","))
		{
			Error("OP_parent expect ,", tok);
		}
		Primary(tok);
	}
	else if (i == OP_root)
	{
		m_StateMgr->AddInstruction(OP_root,0,"OP_root");
		if (!tok.CheckToken(","))
		{
			Error("OP_root expect ,", tok);
		}
		Primary(tok);
	}
	else if (i == OP_helper)
	{
		int helperid = -1;
		if (tok.CheckToken("("))
		{
			helperid = tok.GetInt();
			if (!tok.CheckToken(")"))
			{
				Error("OP_helper expect )", tok);
			}
		}
		if (!tok.CheckToken(","))
		{
			Error("OP_helper expect ,", tok);
		}
		m_StateMgr->AddInstruction(OP_PUSH, helperid,"#");
		m_StateMgr->AddInstruction(OP_helper,0,"OP_helper");
		Primary(tok);
	}
	else if (i == OP_target)
	{
		int id = -1;
		if (tok.CheckToken("("))
		{
			id = tok.GetInt();
			if (!tok.CheckToken(")"))
			{
				Error("OP_target expect )", tok);
			}
		}
		if (!tok.CheckToken(","))
		{
			Error("OP_target expect ,", tok);
		}
		m_StateMgr->AddInstruction(OP_PUSH, id,"#");
		m_StateMgr->AddInstruction(OP_target,0,"OP_target");
		Primary(tok);
	}
	else if (i == OP_partner)
	{
		m_StateMgr->AddInstruction(OP_partner,0,"OP_partner");
		if (!tok.CheckToken(","))
		{
			Error("OP_partner expect ,", tok);
		}
		Primary(tok);
	}
	else if (i == OP_enemy)
	{
		int id = -1;
		if (tok.CheckToken("("))
		{
			id = tok.GetInt();
			if (!tok.CheckToken(")"))
			{
				Error("OP_enemy expect )", tok);
			}
		}
		if (!tok.CheckToken(","))
		{
			Error("OP_enemy expect ,", tok);
		}
		m_StateMgr->AddInstruction(OP_PUSH, id,"#");
		m_StateMgr->AddInstruction(OP_enemy,0,"OP_enemy");
		Primary(tok);
	}
	else if (i == OP_enemynear)
	{
		int id = -1;
		if (tok.CheckToken("("))
		{
			id = tok.GetInt();
			if (!tok.CheckToken(")"))
			{
				Error("OP_enemynear expect )", tok);
			}
		}
		if (!tok.CheckToken(","))
		{
			Error("OP_enemynear expect ,", tok);
		}
		m_StateMgr->AddInstruction(OP_PUSH, id,"#");
		m_StateMgr->AddInstruction(OP_enemynear,0,"OP_enemynear");
		Primary(tok);
	}
	else if (i == OP_playerid)
	{
		int id = -1;
		if (tok.CheckToken("("))
		{
			id = tok.GetInt();
			if (!tok.CheckToken(")"))
			{
				Error("OP_playerid expect )", tok);
			}
		}
		if (!tok.CheckToken(","))
		{
			Error("OP_playerid expect ,", tok);
		}
		m_StateMgr->AddInstruction(OP_PUSH, id,"#");
		m_StateMgr->AddInstruction(OP_playerid,0,"OP_playerid");
		Primary(tok);
	}
	else
	{
		if (OPEN_ERROR)
		{
			SDL_assert(false);
		}
		ParseWarning(tok, "undeal op");
		m_StateMgr->AddInstruction(OP_PUSH, 0,"#");
	}
}

int CStateParser::GetControllerType(const char * strType,CTokenizer &tok)
{
	int i=0;
	while(strControllerTypes[i])
	{
		if(SDL_strcasecmp(strType,strControllerTypes[i]) == 0)
			return i;       

		i++;

	}
	Error(strType,tok);

	return -1;   
}

int CStateParser::GetOPArgc(int op,CTokenizer &tok)
{
	if (op >= OP_END || op == -1)
	{
		Error("GetOPArgc error",tok);
		return 0;
	}
	return strTriggerArgcs[op];
}
int CStateParser::GetTriggerType(const char * strTrigger,CTokenizer &tok)
{
	int i=0;
	while(STR_TriggerType[i][0])
	{
		/*if (i == 144)
		{
		PrintMessage("");
		}*/
		if(SDL_strcasecmp(strTrigger,STR_TriggerType[i]) == 0)
			return i;


		i++;   

	}
	//Error(strTrigger,tok);
	return -1;

}
