/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "Fighter.h"
/*
================================================================================
================================================================================
*/
CFighter::CFighter()
{ 

}

CFighter::~CFighter()
{
}


void CFighter::Init(Uint32 id, CFighter* enimy)
{
	CPlayer::Init(id, enimy);
	m_type = PLAYER_FIGHTER;
}

