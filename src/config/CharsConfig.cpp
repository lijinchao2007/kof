/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "CharsConfig.h"
#include "StateParser.h"
#include "tool.h"

//Constructor
CCharsConfig::CCharsConfig()
{
	m_SffManager = new CSffManager;
	m_AirManager = new CAirManager;
	m_StateManager = new CStateManager;  
	m_CmdManager = new CCmdManager;
	m_SndConfig = new CSndConfig;
}

//Destructor
CCharsConfig::~CCharsConfig()
{
	CC_SAFE_DELETE(m_SffManager);
	CC_SAFE_DELETE(m_AirManager);
	CC_SAFE_DELETE(m_StateManager);
	CC_SAFE_DELETE(m_CmdManager);
	CC_SAFE_DELETE(m_SndConfig);
}

void CCharsConfig::ModifyMap(const char* key, const char* value)
{
	std::map<std::string, std::string>::iterator it;
	it = m_KeyValueMap.find(key);
	if(it == m_KeyValueMap.end())
		m_KeyValueMap.insert(std::make_pair(key, value));
	/*else
	{
		it->second = value;
	}*/
}
void CCharsConfig::LoadDefaultValue()
{
	ModifyMap("size.effect.xscale", "1.0");
	ModifyMap("size.effect.yscale", "1.0");

	ModifyMap("movement.stand.friction.threshold", "2");
	ModifyMap("movement.crouch.friction.threshold", "0.05");
	ModifyMap("movement.air.gethit.groundlevel", "25");
	ModifyMap("movement.air.gethit.groundrecover.ground.threshold", "-20");
	ModifyMap("movement.air.gethit.groundrecover.groundlevel", "10");
	ModifyMap("movement.air.gethit.airrecover.threshold", "-1");
	ModifyMap("movement.air.gethit.airrecover.yaccel", "0.35");
	ModifyMap("movement.air.gethit.trip.groundlevel", "15");
	ModifyMap("movement.down.bounce.offset.x", "0");
	ModifyMap("movement.down.bounce.offset.y", "20");
	ModifyMap("movement.down.bounce.yaccel", "0.4");
	ModifyMap("movement.down.bounce.groundlevel", "12");
	ModifyMap("movement.down.friction.threshold", "0.05");
}

bool CCharsConfig::ParseCharConfig(const char* strPlayer)
{

	char configPath[MAX_PATH] = {0};
	char allcName[MAX_PATH] = {0};
	SDL_snprintf(configPath, MAX_PATH, "chars/%s/%s.def", strPlayer, strPlayer);

	SDL_snprintf(allcName, MAX_PATH, "%s.state", strPlayer);
	m_StateManager->SetAlloc(allcName);
	m_StateManager->Reset();
	
	this->ParseDef(configPath);

	CStateParser StateParser(this, m_StateManager);
	SDL_snprintf(configPath, MAX_PATH, "data/%s", this->GetChar("Files.stcommon"));
	StateParser.ParseStateFile(configPath);
	SDL_snprintf(configPath, MAX_PATH, "chars/%s/%s", strPlayer, this->GetChar("Files.cns"));
	this->ParseDef(configPath);
	this->LoadDefaultValue();

	if (this->GetChar("Files.st")!=NULL)
	{
		SDL_snprintf(configPath, MAX_PATH, "chars/%s/%s", strPlayer, this->GetChar("Files.st"));
		StateParser.ParseStateFile(configPath);
	}
	for (int i=0;i<11;i++)
	{
		char keyName[MAX_PATH];
		SDL_snprintf(keyName, MAX_PATH, "Files.st%d", i);
		if (this->GetChar(keyName)!=NULL)
		{
			SDL_snprintf(configPath, MAX_PATH, "chars/%s/%s", strPlayer, this->GetChar(keyName));
			StateParser.ParseStateFile(configPath);
		}
	}

	SDL_snprintf(configPath, MAX_PATH, "chars/%s/%s", strPlayer, this->GetChar("Files.cmd"));
	StateParser.ParseStateFile(configPath);
	m_CmdManager->LoadCMDFile(configPath);
	SDL_snprintf(configPath, MAX_PATH, "chars/%s/%s", strPlayer, this->GetChar("Files.anim"));
	m_AirManager->ParseFile(configPath);

	SDL_snprintf(configPath, MAX_PATH, "chars/%s/%s", strPlayer, this->GetChar("Files.sprite"));
	m_SffManager->ParseFile(configPath);
	char strPalKey[MAX_PATH];
	for (int i=1;i<=PALLET_MAX_NUM;i++)
	{
		SDL_snprintf(strPalKey, MAX_PATH, "Files.pal%d", i);
		const char* actName = this->GetChar(strPalKey);
		if (actName == NULL)
		{
			continue;
		}
		SDL_snprintf(configPath, MAX_PATH, "chars/%s/%s", strPlayer, actName);
		m_SffManager->LoadActToSff(i, configPath);
	}

	SDL_snprintf(configPath, MAX_PATH, "chars/%s/%s", strPlayer, this->GetChar("Files.Sound"));
	m_SndConfig->ParseFile(configPath);

	return true;

}


bool CCharsConfig::ParseDef(const char* file)
{
	PrintMessage("CCharsConfig::ParseDef %s ", file);
	CTokenizer tok;

	if( !tok.OpenFile(file) )
		throw(CError("CConfigParse::ParseConfig: File %s not found",file));

	tok.SetIsCaseSensitive(false);
	while( !tok.AtEndOfFile() )
	{
		bool bFoundSection = false;
		if( tok.CheckToken("[") )
		{
			if (tok.CheckToken("statedef")||tok.CheckToken("state"))
			{
				continue;
			}
			bFoundSection = Common_ParseSection(tok, m_KeyValueMap);

		}
		//skip useless stuff
		if(!bFoundSection)
			GET_ALL_LINE_TOKEN(tok);

	}
	tok.CloseFile();
	PrintMessage("config's count %d", m_KeyValueMap.size());
	return true;
}


