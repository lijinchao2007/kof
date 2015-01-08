/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "FightConfig.h"
#include "tool.h"

//Constructor
CFightConfig::CFightConfig()
{
	m_Sfffight = new CSffManager;
	m_sndfight = new CSndConfig;

	m_SffFX = new CSffManager;
	m_AirFX = new CAirManager;

	m_sndCommon = new CSndConfig;
}

//Destructor
CFightConfig::~CFightConfig()
{
	CC_SAFE_DELETE(m_Sfffight);
	CC_SAFE_DELETE(m_sndfight);

	CC_SAFE_DELETE(m_SffFX);
	CC_SAFE_DELETE(m_AirFX);

	CC_SAFE_DELETE(m_sndCommon);
}


bool CFightConfig::ParseCfg(const char* file)
{

	PrintMessage("  CFightConfig::ParseCfg %s ", file);
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
			if (tok.CheckToken("Begin"))
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
	const char* sprName = GetChar("Files.sff");
	if (sprName)
	{
		SDL_snprintf(filePath, MAX_PATH, "data/%s", sprName);
		m_Sfffight->SetAlloc(filePath);
		m_Sfffight->Reset();
		m_Sfffight->ParseFile(filePath);
	}
	const char* sndName = GetChar("Files.snd");
	if (sndName)
	{
		SDL_snprintf(filePath, MAX_PATH, "data/%s", sndName);
		m_sndfight->SetAlloc(filePath);
		m_sndfight->Reset();
		m_sndfight->ParseFile(filePath);
	}

	const char* fxSffName = GetChar("Files.fightfx.sff");
	if (fxSffName)
	{
		SDL_snprintf(filePath, MAX_PATH, "data/%s", fxSffName);
		m_SffFX->SetAlloc(filePath);
		m_SffFX->Reset();
		m_SffFX->ParseFile(filePath);
	}

	const char* fxAirName = GetChar("Files.fightfx.air");
	if (fxAirName)
	{
		SDL_snprintf(filePath, MAX_PATH, "data/%s", fxAirName);
		m_AirFX->ParseFile(filePath);
	}

	const char* sndCommonName = GetChar("Files.common.snd");
	if (sndName)
	{
		SDL_snprintf(filePath, MAX_PATH, "data/%s", sndCommonName);
		m_sndCommon->SetAlloc(filePath);
		m_sndCommon->Reset();
		m_sndCommon->ParseFile(filePath);
	}

	return true;
}
