/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "SceneAirConfig.h"
#include "tool.h"

CSceneAirConfig::CSceneAirConfig()
{
	m_selectBG = NULL;
	m_BgDef = NULL;
	m_BgCtrlDefCon = NULL;
}

CSceneAirConfig::~CSceneAirConfig()
{
}

void CSceneAirConfig::ReAllocMem()
{
	CAirBaseConfig::ReAllocMem();
	if(m_selectBG!= NULL){
		m_selectBG->nMemSize = m_selectBG->elementSize;
		m_selectBG->elements = (BG_ELEMENT*)m_pAlloc->Realloc(m_selectBG->elements, sizeof(BG_ELEMENT)*m_selectBG->elementSize);
	}
	if(m_BgDef!= NULL){
		m_BgDef->nMemSize = m_BgDef->elementSize;
		m_BgDef->elements = (BG_ELEMENT*)m_pAlloc->Realloc(m_BgDef->elements, sizeof(BG_ELEMENT)*m_BgDef->elementSize);
	}
	if (m_BgCtrlDefCon!=NULL)
	{
		m_BgCtrlDefCon->nMemSize = m_BgCtrlDefCon->nCtrlDefSize;
		m_BgCtrlDefCon->elements = (BGCTRl_DEF*)m_pAlloc->Realloc(m_BgCtrlDefCon->elements, sizeof(BGCTRl_DEF)*m_BgCtrlDefCon->nMemSize);
		BGCTRl_DEF* defEle = m_BgCtrlDefCon->elements;
		int i = 0;
		while (i<m_BgCtrlDefCon->nCtrlDefSize)
		{
			defEle->nMemSize = defEle->nCtrlSize;
			defEle->elements = (BGCTRl_ELEMENT*)m_pAlloc->Realloc(defEle->elements, sizeof(BGCTRl_ELEMENT)* defEle->nMemSize);
			defEle++;
			i++;
		}
	}
}
void CSceneAirConfig::ParseFile(const char* file)
{
	PrintMessage("CSceneAirConfig::ParseFile  %s ", file);
	m_pAlloc=CMemManager::GetInstance()->GetAllocater(file);

	CAirBaseConfig::Reset();

	CTokenizer tok;
	if( !tok.OpenFile(file) )
		throw(CError("CConfigParse::GetStageConfig: File %s not found",file));

	tok.SetIsCaseSensitive(false);
	tok.SetReturnNegativeSeperatelyFromNumber(false);

	while( !tok.AtEndOfFile() )
	{
		bool bFoundSection = false;
		if(tok.CheckToken("[") )
		{
			if( tok.CheckToken("TitleBGdef") )
			{
				bFoundSection=true;
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}

			}else if (tok.CheckToken("TitleBG"))
			{
				bFoundSection=true;
				GET_ALL_LINE_TOKEN(tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}

			}else if (tok.CheckToken("SelectBGdef"))
			{
				bFoundSection=true;
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				m_selectBG = (BG_DEF*)m_pAlloc->Alloc(sizeof(BG_DEF));
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					if(tok.CheckToken("spr"))
					{
						if(!tok.CheckToken("="))
							Error("need = ", tok);
						tok.GetToken(m_selectBG->spr, MAX_STRING_LENGTH);

					}else if(tok.CheckToken("debugbg"))
					{
						if(!tok.CheckToken("="))
							Error("need = ", tok);
						tok.GetToken();
					}else
					{
						GET_ALL_LINE_TOKEN(tok);
					}
				}


			}else if (tok.CheckToken("SelectBG"))
			{
				bFoundSection=true;
				ParseBG(tok, m_selectBG);
			}else if (tok.CheckToken("VersusBGdef"))
			{
				bFoundSection=true;
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}

			}else if (tok.CheckToken("VersusBG"))
			{
				bFoundSection=true;
				GET_ALL_LINE_TOKEN(tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}
			}else if (tok.CheckToken("OptionBGdef"))
			{
				bFoundSection=true;
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}

			}else if (tok.CheckToken("OptionBG"))
			{
				bFoundSection=true;
				GET_ALL_LINE_TOKEN(tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}
			}else if( tok.CheckToken("BGdef") )
			{
				bFoundSection=true;
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				m_BgDef = (BG_DEF*)m_pAlloc->Alloc(sizeof(BG_DEF));
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					if(tok.CheckToken("spr"))
					{
						if(!tok.CheckToken("="))
							Error("need = ", tok);
						tok.GetToken(m_BgDef->spr, MAX_STRING_LENGTH);

					}else if(tok.CheckToken("debugbg"))
					{
						if(!tok.CheckToken("="))
							Error("need = ", tok);
						tok.GetToken();
					}else
					{
						GET_ALL_LINE_TOKEN(tok);
					}
				}

			}else if (tok.CheckToken("BG"))
			{
				bFoundSection=true;
				ParseBG(tok, m_BgDef);

			}else if (tok.CheckToken("BGCtrlDef"))
			{
				bFoundSection=true;
				ParseBGCtrlDef(tok);

			}else if (tok.CheckToken("BGCtrl"))
			{
				bFoundSection=true;
				ParseBGCtrl(tok);
			}else if (tok.CheckToken("Begin"))
			{
				bFoundSection=true;
				ParseAction(tok);
			}else{
				bFoundSection=true;
				tok.GetToken();
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}
			}
			
		}

		//skip useless stuff
		if(!bFoundSection)
			GET_ALL_LINE_TOKEN(tok);
	}
	// realloc

	ReAllocMem();
	tok.CloseFile();
}

void CSceneAirConfig::InitBG(BG_ELEMENT* tmpBG)
{
	tmpBG->nLayerNo = 0;
	tmpBG->nStartX = 0;
	tmpBG->nStartY = 0;
	tmpBG->fDeltaX = 1;
	tmpBG->fDeltaY = 1;
	tmpBG->bMask = 0;
}

void CSceneAirConfig::ParseBG(CTokenizer& tok, BG_DEF* bgdef)
{
	if(bgdef == NULL)Error("BGdef shoud defined!", tok);
	char bgName[MAX_PATH];
	tok.GetToken(bgName, MAX_PATH);
	if (!tok.CheckToken("]"))
	{
		Error("expect ]", tok);
	}

	if (bgdef->elements == NULL)
	{
		bgdef->nMemSize = 50;
		bgdef->elementSize = 0;
		bgdef->elements = (BG_ELEMENT*)m_pAlloc->Alloc(sizeof(BG_ELEMENT)*bgdef->nMemSize);
	}
	bgdef->elementSize++;
	if (bgdef->elementSize > bgdef->nMemSize)
	{
		bgdef->nMemSize += 50;
		bgdef->elements = (BG_ELEMENT*)m_pAlloc->Realloc(bgdef->elements, sizeof(BG_ELEMENT)*bgdef->nMemSize);
	}

	BG_ELEMENT* tmpElement = bgdef->elements+bgdef->elementSize-1;
	InitBG(tmpElement);
	while (!tok.CheckToken("[", false)&&!tok.AtEndOfFile())
	{
		if(tok.CheckToken("type"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);

			if (tok.CheckToken("normal"))
			{
				tmpElement->type = BG_TYPE_NORMAL;
			}else if (tok.CheckToken("anim"))
			{
				tmpElement->type = BG_TYPE_ANIM;
			}else{
				ParseWarning(tok, "ParseBG not support type");
				GET_ALL_LINE_TOKEN(tok);
			}

		}else if(tok.CheckToken("spriteno"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			
			tmpElement->GroubNumber = tok.GetInt();
			if(!tok.CheckToken(","))
				Error("need , ", tok);
			tmpElement->ImageNumber = tok.GetInt();

		}else if(tok.CheckToken("id"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);

			tmpElement->nID = tok.GetInt();
		}else if(tok.CheckToken("layerno"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);

			tmpElement->nLayerNo = tok.GetInt();
		}else if(tok.CheckToken("start"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);

			tmpElement->nStartX = tok.GetInt();
			if(!tok.CheckToken(","))
				Error("need , ", tok);
			tmpElement->nStartY = tok.GetInt();

		}else if(tok.CheckToken("delta"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);

			tmpElement->fDeltaX = tok.GetFloat();
			if(!tok.CheckToken(","))
				Error("need , ", tok);
			tmpElement->fDeltaY = tok.GetFloat();
		}else if(tok.CheckToken("trans"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			ParseWarning(tok, "trans not supported");
		}else if(tok.CheckToken("mask"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			tmpElement->bMask = tok.GetInt();
		}else if(tok.CheckToken("tile"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);

			tmpElement->nTileX = tok.GetInt();
			if(!tok.CheckToken(","))
				Error("need , ", tok);
			tmpElement->nTileY = tok.GetInt();

		}else if(tok.CheckToken("tilespacing"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);

			tmpElement->nTileSpacingX = tok.GetInt();
			if(!tok.CheckToken(","))
				Error("need , ", tok);
			tmpElement->nTileSpacingY = tok.GetInt();

		}else if(tok.CheckToken("window"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);

			tmpElement->nWindowX = tok.GetInt();
			if(!tok.CheckToken(","))
				Error("need , ", tok);
			tmpElement->nWindowY = tok.GetInt();
			if(!tok.CheckToken(","))
				Error("need , ", tok);
			tmpElement->nWindowW = tok.GetInt();
			if(!tok.CheckToken(","))
				Error("need , ", tok);
			tmpElement->nWindowH = tok.GetInt();

		}else if(tok.CheckToken("windowdelta"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			ParseWarning(tok, "windowdelta not supported");
		}else if(tok.CheckToken("actionno"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			tmpElement->nAnimNo = tok.GetInt();
		}else
		{
			GET_ALL_LINE_TOKEN(tok);
		}
	}
}

void CSceneAirConfig::ParseBGCtrlDef(CTokenizer& tok)
{
	if (m_BgCtrlDefCon == NULL)
	{
		m_BgCtrlDefCon = (BGCTRl_DEF_CONTAINER*)m_pAlloc->Alloc(sizeof(BGCTRl_DEF_CONTAINER));
	}

	if (m_BgCtrlDefCon->elements == NULL)
	{
		m_BgCtrlDefCon->nMemSize = 50;
		m_BgCtrlDefCon->nCtrlDefSize = 0;
		m_BgCtrlDefCon->elements = (BGCTRl_DEF*)m_pAlloc->Alloc(sizeof(BGCTRl_DEF)*m_BgCtrlDefCon->nMemSize);
	}
	m_BgCtrlDefCon->nCtrlDefSize++;
	if (m_BgCtrlDefCon->nCtrlDefSize > m_BgCtrlDefCon->nMemSize)
	{
		m_BgCtrlDefCon->nMemSize += 50;
		m_BgCtrlDefCon->elements = (BGCTRl_DEF*)m_pAlloc->Realloc(m_BgCtrlDefCon->elements, sizeof(BGCTRl_DEF)*m_BgCtrlDefCon->nMemSize);
	}

	BGCTRl_DEF* tmpCtrlDef = m_BgCtrlDefCon->elements+m_BgCtrlDefCon->nCtrlDefSize-1;

	tok.GetToken(tmpCtrlDef->name, MAX_PATH);
	if(!tok.CheckToken("]"))
		Error("need ] ", tok);

	while (!tok.CheckToken("[", false)&&!tok.AtEnd())
	{
		if(tok.CheckToken("looptime"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);

			tmpCtrlDef->nLoopTime = tok.GetInt();

		}else if(tok.CheckToken("CtrlID"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			int i=0;
			while (!tok.CheckToken("[", false)&&!tok.AtEnd())
			{
				tmpCtrlDef->CtrlID[i++] = tok.GetInt();
				if(!tok.CheckToken(",")||i>=10)
					break;
			}
		}else
		{
			GET_ALL_LINE_TOKEN(tok);
		}
	}

}

void CSceneAirConfig::ParseBGCtrl(CTokenizer& tok)
{
	SDL_assert(m_BgCtrlDefCon != NULL);
	BGCTRl_DEF* ctrlDef = m_BgCtrlDefCon->elements+m_BgCtrlDefCon->nCtrlDefSize-1;

	if (ctrlDef->elements == NULL)
	{
		ctrlDef->nMemSize = 50;
		ctrlDef->nCtrlSize = 0;
		ctrlDef->elements = (BGCTRl_ELEMENT*)m_pAlloc->Alloc(sizeof(BGCTRl_ELEMENT)*ctrlDef->nMemSize);
	}
	ctrlDef->nCtrlSize++;
	if (ctrlDef->nCtrlSize > ctrlDef->nMemSize)
	{
		ctrlDef->nMemSize += 50;
		ctrlDef->elements = (BGCTRl_ELEMENT*)m_pAlloc->Realloc(ctrlDef->elements, sizeof(BGCTRl_ELEMENT)*ctrlDef->nMemSize);
	}

	BGCTRl_ELEMENT* tmpCtrl = ctrlDef->elements+ctrlDef->nCtrlSize-1;

	char name[MAX_PATH];
	tok.GetToken(name, MAX_PATH);
	if(!tok.CheckToken("]"))
		Error("need ] ", tok);

	while (!tok.CheckToken("[", false)&&!tok.AtEnd())
	{
		if(tok.CheckToken("type"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			if (tok.CheckToken("null"))
			{
				tmpCtrl->type = BGCTRL_TYPE_null;
			}else if (tok.CheckToken("Visible"))
			{
				tmpCtrl->type = BGCTRL_TYPE_Visible;
			}else if (tok.CheckToken("Visible"))
			{
				tmpCtrl->type = BGCTRL_TYPE_Visible;
			}else if (tok.CheckToken("Enabled"))
			{
				tmpCtrl->type = BGCTRL_TYPE_Enabled;
			}else if (tok.CheckToken("Visible"))
			{
				tmpCtrl->type = BGCTRL_TYPE_Visible;
			}else if (tok.CheckToken("VelSet"))
			{
				tmpCtrl->type = BGCTRL_TYPE_VelSet;
			}else if (tok.CheckToken("VelAdd"))
			{
				tmpCtrl->type = BGCTRL_TYPE_VelAdd;
			}else if (tok.CheckToken("PosSet"))
			{
				tmpCtrl->type = BGCTRL_TYPE_PosSet;
			}else if (tok.CheckToken("PosAdd"))
			{
				tmpCtrl->type = BGCTRL_TYPE_PosAdd;
			}else if (tok.CheckToken("Anim"))
			{
				tmpCtrl->type = BGCTRL_TYPE_Anim;
			}else if (tok.CheckToken("SinX"))
			{
				tmpCtrl->type = BGCTRL_TYPE_SinX;
			}else if (tok.CheckToken("SinY"))
			{
				tmpCtrl->type = BGCTRL_TYPE_SinY;
			}
		}else if(tok.CheckToken("time"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			tmpCtrl->startTime = tok.GetInt();
			if (tok.CheckToken(","))
			{
				tmpCtrl->endTime = tok.GetInt();
				if (tok.CheckToken(","))
				{
					tmpCtrl->loopTime = tok.GetInt();
				}
			}

		}else if(tok.CheckToken("ctrlID"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			int i=0;
			while (!tok.CheckToken("[", false)&&!tok.AtEnd())
			{
				tmpCtrl->CtrlID[i++] = tok.GetInt();
				if(!tok.CheckToken(",")||i>=10)
					break;
			}

		}else if(tok.CheckToken("x"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			tmpCtrl->x = tok.GetInt();
		}else if(tok.CheckToken("y"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			tmpCtrl->y = tok.GetInt();
		}else if(tok.CheckToken("value"))
		{
			if(!tok.CheckToken("="))
				Error("need = ", tok);
			tmpCtrl->value = tok.GetInt();
		}else
		{
			GET_ALL_LINE_TOKEN(tok);
		}
	}
}


void CSceneAirConfig::ParseAction(CTokenizer& tok)
{
	int actionNum = -1;

	if( !tok.CheckToken( "Action" ) )
	{
	}                    

	if( !tok.CheckTokenIsNumber() )
	{
	}

	actionNum = tok.GetInt();

	if( !tok.CheckToken( "]" ) )
	{
	}

	PrintMessage("CSceneAirConfig::ParseAction actionNum %d", actionNum);
	AddAction(actionNum);   

	while (!tok.CheckToken("[", false)&&!tok.AtEndOfFile())
	{
		if( tok.CheckToken( "Loopstart" ) )
		{
			SetLoop();
		}
		else if( tok.CheckTokenIsNumber() )
		{
			int values[5];
			for( int v = 0; v < 5; v++ )
			{
				if( !tok.CheckTokenIsNumber() )
				{
				}

				values[ v ] = tok.GetInt();

				if( v < 4 )
				{
					if( !tok.CheckToken( "," ) )
					{
					}
				}
			}

			SDL_RendererFlip flipFlag = SDL_FLIP_NONE;

			if( tok.CheckToken( "," ) )
			{
				if( tok.CheckToken( "H" ) )
				{
					flipFlag = SDL_FLIP_HORIZONTAL;
				}
				else if( tok.CheckToken( "V" ) )
				{
					flipFlag = SDL_FLIP_VERTICAL;
				}
				else if( tok.CheckToken( "VH" ) || tok.CheckToken( "HV" ) )
				{
					flipFlag = (SDL_RendererFlip)(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL);
				}
				else if( !tok.CheckToken( ",", false ) )
				{
				}
			}

			const char* TransType = NULL;
			if( tok.CheckToken( "," )&&!tok.AtEndOfLine() )
			{
				TransType = tok.GetToken(); // alpha param
			}

			AddElement( values[0], values[1], values[2], values[3], values[4], flipFlag, TransType);
		}
	}

}
