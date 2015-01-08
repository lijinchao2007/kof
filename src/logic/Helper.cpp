/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "Helper.h"
/*
================================================================================
================================================================================
*/
CHelper::CHelper()
	:m_bKeyCtrl(false)
	,m_bOwnPal(false)
	,m_helpertype(eHelperType_Normal)
{ 

}

CHelper::~CHelper()
{
}


void CHelper::InitWithParent(Uint32 id, CPlayer *parent)
{
	CPlayer::Init(id, parent->m_p2);
	m_type = PLAYER_HELPER;
	m_Parent = parent;
	parent->AddChild(this);
}


//first
 void CHelper::UpdateCommand()
 {
	 return;
 }

void CHelper::HandleSYSFSM()
{
	return;
	//TODO:击中pause的时候，是否执行？
	// default state 
	for (Sint32 stateIndex =-3;stateIndex<=-1;stateIndex++)
	{
		PLSTATEDEF *specialState = m_Config->GetState()->GetStateDef(stateIndex);
		if (specialState != NULL)
		{
			//check every state in this statedef
			for(Uint16 i=0;i < specialState->nHowManyState; i++)
			{
				if( CheckState(&specialState->lpState[i], i))
					m_ControllerExec->ExecuteController(&specialState->lpState[i]);

			}
		}
	}
}
void CHelper::HandleSYSStateNo()
{

}


//second
void CHelper::UpDateFacing()
{

}
void CHelper::UpdateCamera()
{

}