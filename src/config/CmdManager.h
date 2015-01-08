/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __COMMAND_MANAGER__CMDMANAGER_H__
#define __COMMAND_MANAGER__CMDMANAGER_H__

#include "structs.h"
//Tokenizer by Nate Pendelton
class CCmdManager
{
// To Get the Game time
public:
    CCmdManager();
    ~CCmdManager();

	PLCOMMAND* m_Commands;
	Sint32 m_CommandCount;  
	PLCOMMAND* GetConfigCmd(){return m_Commands;};
	Sint32 GetCmdCount(){return m_CommandCount;};
    bool LoadCMDFile( const char* file );  // returns false upon load failure

};

#endif

