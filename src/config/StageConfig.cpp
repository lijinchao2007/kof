/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "StageConfig.h"
#include "tool.h"

CStageConfig::CStageConfig()
{
	m_SffManager = new CSffManager;
	m_airConfig = new CSceneAirConfig;
}

CStageConfig::~CStageConfig()
{
	CC_SAFE_DELETE(m_SffManager);
	CC_SAFE_DELETE(m_airConfig);
}

void CStageConfig::ParseConfig(const char* file)
{
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
			if( tok.CheckToken("BGdef") )
			{
				bFoundSection=true;
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}

			}else if (tok.CheckToken("BG"))
			{
				bFoundSection=true;
				tok.GetToken();
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}

			}else if (tok.CheckToken("BGCtrlDef"))
			{
				bFoundSection=true;
				tok.GetToken();
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}

			}else if (tok.CheckToken("BGCtrl"))
			{
				bFoundSection=true;
				tok.GetToken();
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}
			}else if (tok.CheckToken("Begin"))
			{
				bFoundSection=true;
				tok.GetToken();
				tok.GetToken();
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}
			}else{
				bFoundSection = Common_ParseSection(tok, m_KeyValueMap);
			}
		}
		if(!bFoundSection)
			GET_ALL_LINE_TOKEN(tok);
	}

	tok.CloseFile();

	m_airConfig->ParseFile(file);

	const char* sprName = m_airConfig->m_BgDef->spr;
	CAssert(sprName!=NULL, "");
	m_SffManager->ParseFile(sprName);
}
