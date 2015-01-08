/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __FIGHTER__H
#define __FIGHTER__H
#include "structs.h"
#include "tool.h"
#include "player.h"

class CFighter:public CPlayer
{
public:
	CFighter();
	virtual  ~CFighter();

	virtual  void Init(Uint32 id, CFighter* enimy);
};

#endif
