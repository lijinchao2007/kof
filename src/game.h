/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/


#ifndef GAME_H
#define GAME_H

#include "define.h"
#include "driver/SDL_framerate.h"

//This is the main game class 
class CGame
{
public:
	//Contructor Destructor
	CGame();
	~CGame();
	void InitGame();
	void RunLogic();
	void RunGame();
	void StopGame(){bGame = false;};
	void PauseGame(){bPause = true;};
	void ContinueGame(){bPause = false;};
	bool IsPause(){return bPause == true;};
	void Quit();
	float GetPropFps(){return m_FPSmanager.realFPS;};

public:
	Prop_Get_Set(bool, IsDebugTime);

	Uint32 nowTime,lastTime;
	Uint32 nFpsCount;
	FPSmanager m_FPSmanager;
private:

	bool bError;
	bool bPause;
	bool bGame;

public:
	static CGame* GetInstance();
};
static CGame* pGameInstance=NULL;




#endif
