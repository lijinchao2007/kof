/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef INPUT_H
#define INPUT_H
#include <set>
#include "structs.h"
#include "TouchDelegateProtocol.h"
#include "tool.h"

class CInput
{

	Sint32 m_nhistoryKey;

public:
    CInput();
    ~CInput();

	Prop_Get_Set(CTouchDelegate*, TouchDelegate);
	Vector_Get_Set(bool, KEY_COUNT, KeyData);

	void CheckSDL();
	void Dispatch();
	virtual void handleTouchesBegin(int id, float x, float ys);
	virtual void handleTouchesMove(int id, float x, float y);
	CTouch* getTouchesEndOrCancel(int id, float x, float y);
	void handleTouchesEnd(int id, float x, float y);
	void handleTouchesCancel(int id, float x, float y);

	void ProcessInput(KEYBOARDDATA *lpKeyBoard);
	void ProcessTouch(KEYBOARDDATA *lpKeyBoard);

public:
	static CInput* GetInstance();
	static void Destroy();
};

static CInput* pInputInstance = NULL;

#endif
