/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __ERROR__H
#define __ERROR__H

#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <string.h>

class CError
{
	char strMessage[MAX_PATH];      
public:
	CError(const char* strError,...)
	{
		char string[MAX_PATH];                  // Temporary string
		va_list ap;                // Pointer To List Of Arguments
		va_start(ap, strError);         // Parses The String For Variables
		vsprintf(string, strError, ap); // Converts Symbols To Actual Numbers
		va_end(ap);      
		strcpy(strMessage,string);
	}
	const char *GetError(){return strMessage;}     
};

#endif