/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/


#include "Stack.h"
#include <memory.h>
#include "tool.h"

CStack::CStack()
{   
    m_CurPos = 0;
	m_BottomPos = 0;
	m_stackLevel = 0;
    memset(m_Stack,0,sizeof(m_Stack));
}


CStack::~CStack()
{

}

void CStack::PrepairStackForState()
{
	//if (m_BottomPos != m_CurPos)
	//{
	//	PrintMessage("Player %d I assume one stack should not Execute in another", m_propplayerID);
	//}
	//m_BottomPos = 0;
	//m_CurPos = 0;
	//m_SavedCurPos = 0;
	//m_SavedBottomPos = 0;
	////memset(m_Stack+m_BottomPos,0,sizeof(m_Stack));
}

void CStack::ResetStackForState()
{
	//CAssert(m_SavedCurPos==m_SavedCurPos, "ResetStackForState error");
	//// like OP_NumHelper which is not supported, whill push too much arg,so when reset the stack, top not equal bottom
	////CAssert(m_CurPos==m_BottomPos, "ResetStack error");
	//m_CurPos=m_SavedCurPos;
	//m_BottomPos=m_SavedBottomPos;
	////memset(m_Stack+m_BottomPos,0,sizeof(Stacktype)*(STACKSIZE-m_BottomPos));
}

void CStack::PrepairStack()
{
	/*if (m_stackLevel > 0 && m_propplayerID == 1)
	{
		PrintMessage("PrepairStack %d, level:%d | curpos:%d | bottom:%d | savedPos:%d | savedBottom:%d ", m_propplayerID, m_stackLevel, m_CurPos, m_BottomPos, m_SavedCurPos[m_stackLevel], m_SavedBottomPos[m_stackLevel]);
	}*/
	m_SavedCurPos[m_stackLevel] = m_CurPos;
	m_SavedBottomPos[m_stackLevel] = m_BottomPos;
	m_stackLevel ++;
	m_BottomPos = m_CurPos;
	CAssert(m_stackLevel < MAXSTACKLOOP, "stack loop is too much");
	//memset(m_Stack+m_BottomPos,0,sizeof(Stacktype)*(STACKSIZE-m_BottomPos));
}

void CStack::ResetStack()
{
	// like OP_NumHelper which is not supported, whill push too much arg,so when reset the stack, top not equal bottom
	//CAssert(m_CurPos==m_BottomPos, "ResetStack error");
	m_stackLevel --;
	/*if (m_stackLevel > 0 && m_propplayerID == 1)
	{
	PrintMessage("ResetStack %d, level:%d | curpos:%d | bottom:%d | savedPos:%d | savedBottom:%d ", m_propplayerID, m_stackLevel, m_CurPos, m_BottomPos, m_SavedCurPos[m_stackLevel], m_SavedBottomPos[m_stackLevel]);
	}*/
	m_CurPos = m_SavedCurPos[m_stackLevel];
	m_BottomPos = m_SavedBottomPos[m_stackLevel];
    //memset(m_Stack+m_BottomPos,0,sizeof(Stacktype)*(STACKSIZE-m_BottomPos));
}


void CStack::Push(float nValue,const char* strValue)
{
	CAssert(m_CurPos<STACKSIZE, "CStack::Push Stack overflow");
	/*if(m_CurPos>=STACKSIZE)
	{
		PrintWaring("CStack::Push Stack overflow");
		return;
	}*/
      
	if(strValue!=NULL)
		SDL_strlcpy(m_Stack[m_CurPos].string,strValue, MAX_PATH);
	m_Stack[m_CurPos].Value=nValue;
    m_CurPos++;      
}

Stacktype CStack::Pop()
{
	// don't pop other's stack
    if(m_CurPos<=m_BottomPos)
	{
        PrintWaring("Player %d stack::Pop Stack underflow", m_propplayerID);
		return m_Stack[m_CurPos];
	}
    return m_Stack[--m_CurPos];


}
