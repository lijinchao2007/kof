/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __SNDCONFIG__H
#define __SNDCONFIG__H

#include "define.h"
#include <map>
#include "logic/MemManager.h"

class CSndConfig
{
private:
	//need pointer to classes
	CAllocater     *m_pAlloc;
	char m_allocName[MAX_PATH];

	Uint16 nTotalSnd;
	Uint16 nSndListSize;
	SNDELEMENT*      lpSndList;
	void DecodeSndFile(SDL_RWops* lpSndFile);
public:
	CSndConfig();
	~CSndConfig();
	void SetAlloc(const char* alloName);
	//reste the class variables
	void Reset();
	SNDELEMENT*  FindSnd(Sint32 nGroupNumber,Sint32 nImageNumber);
	bool ParseFile(const char *strFile);
};

#endif
