/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "BaseConfig.h"
#include "tool.h"

//Constructor
CBaseConfig::CBaseConfig()
{
	m_KeyValueMap.clear();
}

//Destructor
CBaseConfig::~CBaseConfig()
{
	m_KeyValueMap.clear();
}


float CBaseConfig::GetFloat(const char* keyName)
{
	char tmp[MAX_PATH] = {0};
	SDL_strlcpy(tmp, keyName, MAX_PATH);
	SDL_strlwr(tmp);
	std::map<std::string, std::string>::iterator cIter = m_KeyValueMap.find(tmp);
	if (cIter == m_KeyValueMap.end())  //没找到就是指向END了
	{
		// 如果是x y类型的
		int len = SDL_strlen(tmp);
		if (tmp[len-1] == 'x' || tmp[len-1] == 'y')
		{
			tmp[len-2] = '\0';
			cIter = m_KeyValueMap.find(tmp);
			if (cIter != m_KeyValueMap.end())
			{
				return SDL_atof(cIter->second.c_str());
			}
		}
		return 0.0;
	}
	const char* str = cIter->second.c_str();
	return SDL_atof(str);
}

int CBaseConfig::GetInt(const char* keyName)
{
	char tmp[MAX_PATH] = {0};
	SDL_strlcpy(tmp, keyName, MAX_PATH);
	std::map<std::string, std::string>::iterator cIter = m_KeyValueMap.find(SDL_strlwr(tmp));
	if (cIter == m_KeyValueMap.end())  //没找到就是指向END了
	{
		return 0;
	}
	const char* str = cIter->second.c_str();
	return SDL_atoi(str);
}
bool CBaseConfig::SetInt(const char* keyName, int value)
{
	char tmp[MAX_PATH] = {0};
	SDL_strlcpy(tmp, keyName, MAX_PATH);
	std::map<std::string, std::string>::iterator cIter = m_KeyValueMap.find(SDL_strlwr(tmp));
	if (cIter == m_KeyValueMap.end())  //没找到就是指向END了
	{
		return false;
	}
	SDL_itoa(value, tmp, 10);
	cIter->second = std::string(tmp);
	return true;
}

const char* CBaseConfig::GetChar(const char* keyName)
{
	char tmp[MAX_PATH] = {0};
	SDL_strlcpy(tmp, keyName, MAX_PATH);
	std::map<std::string, std::string>::iterator cIter = m_KeyValueMap.find(SDL_strlwr(tmp));
	if (cIter == m_KeyValueMap.end())  //没找到就是指向END了
	{
		return NULL;
	}
	const char* str = cIter->second.c_str();
	return str;
}

void CBaseConfig::Error(const char * strErrorMsg,CTokenizer &tok)
{
	throw(CError("Parser error:\nin file %s at line %i:\ntoken:%s\nerror:%s",tok.GetFileName()
		,tok.GetLineNumber()
		,tok.GetPartToken()
		,strErrorMsg));                  
}

void CBaseConfig::Error(const char * strErrorMsg,CToken &tok)
{
	throw(CError("Parser error:\nin file %s at line %i:\ntoken:%s\nerror:%s",tok.GetFileName()
		,tok.GetLineNumber()
		,tok.GetCurToken()
		,strErrorMsg));                  
}