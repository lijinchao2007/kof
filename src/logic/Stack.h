/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef STACK_H
#define STACK_H

#define STACKSIZE 200
#define MAXSTACKLOOP 20
#include "structs.h"

class CStack
{
	
//Constructor & Destructor
public:
    CStack();
    ~CStack();
    
	Prop_Get_Set(int, playerID);
	void PrepairStackForState();
	void ResetStackForState();
	void PrepairStack();
    void ResetStack();
    void Push(float nValue,const char *strValue);
    Stacktype Pop();

public:
    int m_CurPos;
	int m_BottomPos;

	int m_SavedCurPos[MAXSTACKLOOP];
	int m_SavedBottomPos[MAXSTACKLOOP];
	int m_stackLevel;
    Stacktype m_Stack[STACKSIZE];

};

#endif
