/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "SystemConfig.h"
#include "tool.h"

//Constructor
CSystemConfig::CSystemConfig()
{
	m_SffManager = new CSffManager;
	m_sndConfig = new CSndConfig;
	m_fightConfig = new CFightConfig;
	m_airConfig = new CSceneAirConfig;
	m_selectConfig = new CSelectConfig;

}

//Destructor
CSystemConfig::~CSystemConfig()
{
	CC_SAFE_DELETE(m_SffManager);
	CC_SAFE_DELETE(m_sndConfig);
	CC_SAFE_DELETE(m_fightConfig);
	CC_SAFE_DELETE(m_airConfig);
	CC_SAFE_DELETE(m_selectConfig);
}

SFFSPRITE*  CSystemConfig::GetRoleSpr(const char* name)
{
	if (SDL_strlen(name)>2)
	{
		return m_SffManager->FindSprite(9000, 0);
	}else{
		return NULL;
	}
	

}

bool CSystemConfig::ParseCfg(const char* file)
{

	PrintMessage(" CSystemConfig::ParseCfg %s ", file);
	CTokenizer tok;
	if( !tok.OpenFile(file) )
		throw(CError("CSystemConfig::ParseCfg: File %s not found",file));

	tok.SetIsCaseSensitive(false);
	tok.SetReturnNegativeSeperatelyFromNumber(false);

	while(!tok.AtEndOfFile())
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
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}

			}else if (tok.CheckToken("SelectBG"))
			{
				bFoundSection=true;
				GET_ALL_LINE_TOKEN(tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}
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
			}else if (tok.CheckToken("Begin"))
			{
				bFoundSection=true;
				GET_ALL_LINE_TOKEN(tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEnd())
				{
					GET_ALL_LINE_TOKEN(tok);
				}
			}else{
				bFoundSection = Common_ParseSection(tok, m_KeyValueMap);
			}
		}
		if(!bFoundSection)
		{
			GET_ALL_LINE_TOKEN(tok);
		}
	}

	tok.CloseFile();

	char filePath[MAX_PATH];
	const char* sprName = GetChar("Files.spr");
	if (sprName)
	{
		SDL_snprintf(filePath, MAX_PATH, "data/%s", sprName);
		m_SffManager->ParseFile(filePath);
	}
	const char* sndName = GetChar("Files.snd");
	if (sndName)
	{
		SDL_snprintf(filePath, MAX_PATH, "data/%s", sndName);
		m_sndConfig->ParseFile(filePath);
	}

	const char* fightName = GetChar("Files.fight");
	if (fightName)
	{
		SDL_snprintf(filePath, MAX_PATH, "data/%s", fightName);
		m_fightConfig->ParseCfg(filePath);
	}

	const char* selectName = GetChar("Files.select");
	if (selectName)
	{
		SDL_snprintf(filePath, MAX_PATH, "data/%s", selectName);
		m_selectConfig->ParseCfg(filePath);
	}

	m_airConfig->ParseFile(file);
	return true;
}
