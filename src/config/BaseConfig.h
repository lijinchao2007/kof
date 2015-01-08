/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef _BASECONFIG_H_
#define _BASECONFIG_H_

#include <map>
#include "tokenizer.h"
#include "token.h"
#include "logic/MemManager.h"

class CBaseConfig
{
public:
	CBaseConfig();
	~CBaseConfig();
	virtual int GetInt(const char* keyName);
	virtual bool SetInt(const char* keyName, int value);
	virtual float GetFloat(const char* keyName);
	virtual const char* GetChar(const char* keyName);
	virtual void Error(const char * strErrorMsg,CTokenizer &tok);
	virtual void Error(const char * strErrorMsg,CToken &tok);

	std::map<std::string, std::string> m_KeyValueMap;
};


#endif