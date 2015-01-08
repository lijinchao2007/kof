/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "ConfigManager.h"
#include "tool.h"

CConfigManager* CConfigManager::GetInstance()
{
	if (g_pConfigManager == NULL)
	{
		g_pConfigManager = new CConfigManager();
	}
	return g_pConfigManager;
}

void CConfigManager::Destroy()
{
	CC_SAFE_DELETE(g_pConfigManager);
}

//Constructor
CConfigManager::CConfigManager()
{
	m_CharsConfig.clear();
	m_StageConfig.clear();
	m_sysconfig = NULL;
}

//Destructor
CConfigManager::~CConfigManager()
{
	FreeAllCharConfig();
	FreeAllStageConfig();
	CC_SAFE_DELETE(m_sysconfig);
}



bool CConfigManager::InitManager()
{
	ParseCfg("data/mugen.cfg");
	InitKeyBoard();
	return true;
}

bool CConfigManager::InitKeyBoard()
{

	m_keyDataP1.bKeyBoard = true;
	m_keyDataP1.keyInfo[KEY_UP].sdlKeycode = this->GetInt("P1_Keys.Jump");
	m_keyDataP1.keyInfo[KEY_DOWN].sdlKeycode = this->GetInt("P1_Keys.Crouch");
	m_keyDataP1.keyInfo[KEY_LEFT].sdlKeycode = this->GetInt("P1_Keys.Left");
	m_keyDataP1.keyInfo[KEY_RIGHT].sdlKeycode = this->GetInt("P1_Keys.Right");
	m_keyDataP1.keyInfo[KEY_BUTTON_A].sdlKeycode = this->GetInt("P1_Keys.A");
	m_keyDataP1.keyInfo[KEY_BUTTON_B].sdlKeycode = this->GetInt("P1_Keys.B");
	m_keyDataP1.keyInfo[KEY_BUTTON_C].sdlKeycode = this->GetInt("P1_Keys.C");
	m_keyDataP1.keyInfo[KEY_BUTTON_X].sdlKeycode = this->GetInt("P1_Keys.X");
	m_keyDataP1.keyInfo[KEY_BUTTON_Y].sdlKeycode = this->GetInt("P1_Keys.Y");
	m_keyDataP1.keyInfo[KEY_BUTTON_Z].sdlKeycode = this->GetInt("P1_Keys.Z");
	m_keyDataP1.keyInfo[KEY_BUTTON_START].sdlKeycode = this->GetInt("P1_Keys.Start");

	m_keyDataP2.bKeyBoard = true;
	m_keyDataP2.keyInfo[KEY_UP].sdlKeycode = this->GetInt("P2_Keys.Jump");
	m_keyDataP2.keyInfo[KEY_DOWN].sdlKeycode = this->GetInt("P2_Keys.Crouch");
	m_keyDataP2.keyInfo[KEY_LEFT].sdlKeycode = this->GetInt("P2_Keys.Left");
	m_keyDataP2.keyInfo[KEY_RIGHT].sdlKeycode = this->GetInt("P2_Keys.Right");
	m_keyDataP2.keyInfo[KEY_BUTTON_A].sdlKeycode = this->GetInt("P2_Keys.A");
	m_keyDataP2.keyInfo[KEY_BUTTON_B].sdlKeycode = this->GetInt("P2_Keys.B");
	m_keyDataP2.keyInfo[KEY_BUTTON_C].sdlKeycode = this->GetInt("P2_Keys.C");
	m_keyDataP2.keyInfo[KEY_BUTTON_X].sdlKeycode = this->GetInt("P2_Keys.X");
	m_keyDataP2.keyInfo[KEY_BUTTON_Y].sdlKeycode = this->GetInt("P2_Keys.Y");
	m_keyDataP2.keyInfo[KEY_BUTTON_Z].sdlKeycode = this->GetInt("P2_Keys.Z");
	m_keyDataP2.keyInfo[KEY_BUTTON_START].sdlKeycode = this->GetInt("P2_Keys.Start");

	return true;
}

KEYBOARDDATA* CConfigManager::GetKeyBoard(int playerid)
{
	if (playerid ==P1)
	{
		return &m_keyDataP1;
	}
	if (playerid ==P2)
	{
		return &m_keyDataP2;
	}
	return NULL;
}

//Destructor
bool CConfigManager::ParseCfg(const char* file)
{
	CTokenizer tok;

	if( !tok.OpenFile(file) )
		throw(CError("CConfigParse::ParseConfig: File %s not found",file));

	tok.SetIsCaseSensitive(false);
	while( !tok.AtEndOfFile() )
	{
		bool bFoundSection = false;
		if( tok.CheckToken("[") )
		{
			bFoundSection = Common_ParseSection(tok, m_KeyValueMap);
		}
		//skip useless stuff
		if(!bFoundSection)
			tok.GetToken(); 
	}
	tok.CloseFile();
	PrintMessage("config's count %d", m_KeyValueMap.size());
	return true;
}

/*
================================================================================
char config
================================================================================
*/
void CConfigManager::FreeAllCharConfig()
{
	std::map<std::string, CCharsConfig*>::iterator cIter;
	for (cIter=m_CharsConfig.begin();cIter!=m_CharsConfig.end();cIter++)
	{
		delete (cIter->second);
	}
	m_CharsConfig.clear();
}


void CConfigManager::FreeCharConfig(const char* keyName)
{

	char tmp[MAX_PATH] = {0};
	SDL_strlcpy(tmp, keyName, MAX_PATH);
	std::map<std::string, CCharsConfig*>::iterator cIter = m_CharsConfig.find(SDL_strlwr(tmp));
	if (cIter != m_CharsConfig.end())  //没找到就是指向END了
	{
		SDL_assert(cIter->second!=0);
		delete (cIter->second);
	}
}

CCharsConfig* CConfigManager::GetCharConfig(const char* keyName)
{

	char tmp[MAX_PATH] = {0};
	SDL_strlcpy(tmp, keyName, MAX_PATH);
	std::map<std::string, CCharsConfig*>::iterator cIter = m_CharsConfig.find(tmp);
	if (cIter != m_CharsConfig.end())  //没找到就是指向END了
	{
		return (CCharsConfig*)(cIter->second);
	}
	CCharsConfig* charMgr = new CCharsConfig;
	charMgr->ParseCharConfig(tmp);
	m_CharsConfig[tmp] = charMgr;
	return charMgr;
}

/*
================================================================================
sys config
================================================================================
*/

CSystemConfig* CConfigManager::GetSystemConfig()
{

	if (m_sysconfig == NULL)
	{
		m_sysconfig = new CSystemConfig;
		const char* sysfile = GetChar("Options.motif");
		m_sysconfig->ParseCfg(sysfile);
	}
	return m_sysconfig;;
}

void CConfigManager::FreeSysConfig()
{
	if (m_sysconfig)
	{
		CC_SAFE_DELETE(m_sysconfig);
	}
}
/*
================================================================================
stage config
================================================================================
*/
void CConfigManager::FreeAllStageConfig()
{
	std::map<std::string, CStageConfig*>::iterator cIter;
	for (cIter=m_StageConfig.begin();cIter!=m_StageConfig.end();cIter++)
	{
		delete (cIter->second);
	}
	m_StageConfig.clear();
}

void CConfigManager::FreeStageConfig(const char* keyName)
{

	char tmp[MAX_PATH] = {0};
	SDL_strlcpy(tmp, keyName, MAX_PATH);
	std::map<std::string, CStageConfig*>::iterator cIter = m_StageConfig.find(SDL_strlwr(tmp));
	if (cIter != m_StageConfig.end())  //没找到就是指向END了
	{
		SDL_assert(cIter->second!=0);
		delete (CCharsConfig*)(cIter->second);
	}
}

CStageConfig* CConfigManager::GetStageConfig(const char* keyName)
{

	char tmp[MAX_PATH] = {0};
	SDL_strlcpy(tmp, keyName, MAX_PATH);
	std::map<std::string, CStageConfig*>::iterator cIter = m_StageConfig.find(SDL_strlwr(tmp));
	if (cIter != m_StageConfig.end())  //没找到就是指向END了
	{
		return (CStageConfig*)(cIter->second);
	}
	CStageConfig* charMgr = new CStageConfig;
	charMgr->ParseConfig(keyName);
	m_StageConfig[keyName] = charMgr;
	return charMgr;

}
