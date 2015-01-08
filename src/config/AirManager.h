/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef _AIRMANAGER_H_
#define _AIRMANAGER_H_

#include "AirBaseConfig.h"

class CAirManager:public CAirBaseConfig
{

public:
	CAirManager();
	~CAirManager();

public:
	void SetAlloc(const char *alloName);
	void ParseFile(const char *strFileName);
};
#endif
