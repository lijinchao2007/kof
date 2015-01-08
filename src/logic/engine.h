/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __ENGINE__H
#define __ENGINE__H
#include "define.h"
#include "Fighter.h"
#include "ui/GameLayer.h"

class CEngine
{
public:
	GameLayer* m_gamelayer;
	bool m_inited;
	char m_PlayerName1[MAX_PATH], m_PlayerName2[MAX_PATH];
	CFighter *m_player1,*m_player2;
	Uint32 m_uDebug;

	Prop_Get_Set(int, SuperPauseTime);
	Prop_Get_Set(bool, SuperPauseDarken);
public:
	void ResetEngine();
	void InitEngine(GameLayer* layer);   
	void RunEngine();

	void DrawEngine();

	void ChangeAutoGuard();
	void ChangeDrawType();
	void ChangeDebug();
	void SetClsn();
	void SetPlayer1AI(Uint8 aiLV);
	void SetPlayer2AI(Uint8 aiLV);
	SFFSPRITE* GetPLayerSpr(Sint32 id, Uint32 g, Uint32 i);

	void SetPlayerName(const char* str1, const char* str2)
	{
		SDL_strlcpy(m_PlayerName1, str1, MAX_PATH);
		SDL_strlcpy(m_PlayerName2, str2, MAX_PATH);
	}
	GameLayer* GetGameLayer()
	{
		return m_gamelayer;
	}

	
private:
	CEngine();
	~CEngine();
public:
	static void Destroy();
	static CEngine* GetInstance();
};
static CEngine* pInstance=NULL;
#endif
