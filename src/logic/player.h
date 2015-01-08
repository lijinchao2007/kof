/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __PLAYER__H
#define __PLAYER__H
#include <vector>
#include "structs.h"
#include "VirtualMachine.h"
#include "ControllerExecuter.h"
#include "MemManager.h"
#include "config/CharsConfig.h"
#include "tool.h"
#include "cocos/CCTexture2D.h"

class CControllerExecuter;
class CCharsConfig;
class CVirtualMachine;


class CPlayer:public CObject
{
	static Uint32 playerCount;
public:
	// prop
	Uint32 m_playerUid;
	PLAYER_TYPE m_type;
	Prop_Get_Set(Sint32, ID);
	Prop_Get_Set(Sint32, Pal);
	Prop_Get_Set(Sint32, MaxPower);
	Prop_Get_Set(Sint32, Power);
	Prop_Get_Set(Sint32, MaxLife);
	Prop_Get_Set(Sint32, Life);
	Prop_Get_Set(Sint32, AILevel);
	Prop_Get_Set(Sint32, WidthBack);
	Prop_Get_Set(Sint32, ScreenBack);
	Prop_Get_Set(Sint32, WidthFront);
	Prop_Get_Set(Sint32, ScreenFront);

	Prop_Get_Set(Sint32, HitByFlag);
	Prop_Get_Set(Sint32, HitByTime);
	Prop_Get_Set(Sint32, NotHitByFlag);
	Prop_Get_Set(Sint32, NotHitByTime);

	Prop_Get_Set(bool, IsSuperPause);

	Vector_Get_Set(Sint32, 60, Var);
	Vector_Get_Set(float, 40, FVar);
	Vector_Get_Set(Sint32, 4, SysVar);
	Vector_Get_Set(float, 4, SysFVar);
	Vector_Get_Set(bool, DEFAULT_TrgCount_PerState, TrigRet);

	CArray* m_Children;
	CPlayer* m_Parent;
public:
	CAllocater         *m_pAlloc;
	CVirtualMachine    *m_pVMachine;
	CControllerExecuter* m_ControllerExec;
	CPlayer				*m_p2;
	CCharsConfig			*m_Config;
	// 当前状态 
	PLSTATEDEF         *lpCurrStatedef;
	// 攻打信息
	HITDEFINFO			m_HitInfo;
	// 攻打信息
	PROJHITDEFINFO			m_projHitInfo;
	// 被打信息
	GETHITINFO			m_GetHitInfo;
	// 残影
	AfterImageStack    m_AfterImageStack;
	// 变色
	PalFXInfo*			m_PalFXinfo;

	CCTexture2D*		m_ComboTexture;
	int					m_ComboShowTicks;
public:
	bool		m_IsLogCommand;
	float              x,y;
	float              xVel,yVel;
	float              nGround;
	Sint32                nStateTime;
	Uint8                 nStateType;
	Uint8                 nPhysic;
	Uint8                 nMoveType;
	Sint8                 nSprPrio;
	bool               bHitDefPresit;
	bool               bHitCounterPresit;
	bool               bMoveHitPresit;        
	bool               bCtrl;
	bool               bRightFaced;
	bool				m_bIsDrawBack;
	bool				m_autoGuard;
	ENUM_DRAW_RECT_TYPE				m_bDrawClsn;
	bool               bAlive;
	bool				bPush;
	bool				bAssertNoAutoTurn;
	bool				bAssertNoWalk;
	Uint32				nLastStateNo;
	bool				bIsInP2Anim;
	bool				bIsInP2State;

	Sint32				nTargetBindTime;
	Sint32				nBindTargetID;
	CPoint				mBindPos;
	char				m_playerName[MAX_PATH];
	EvnColorStuct		m_Evn_color;
	EvnShakeStuct		m_shake;

public:
	CPlayer();
	virtual ~CPlayer();
	virtual void Init(Uint32 id, CPlayer* enimy);
	void Destroy();

public:
	void ChangeAutoGuard(){m_autoGuard = !m_autoGuard;};
	void ChangeDrawType(){m_bIsDrawBack = !m_bIsDrawBack;};
	void SetClsn(){m_bDrawClsn = (ENUM_DRAW_RECT_TYPE)((m_bDrawClsn+1)%3);};
	void SetP2(CPlayer *p){m_p2=p;}
	void SetPos(float xAxis,float yAxis){x=xAxis;y=yAxis;}
	void VelSetX(float xvel){xVel=xvel;}
	void VelSetY(float yvel){yVel=yvel;}
	void FaceLeft(){bRightFaced=false;}
	void FaceRight(){bRightFaced=true;}
	void SetGroundValue(float yLimit){nGround=yLimit;} 
	bool IsPlayerAlive(){return bAlive;}
	ActionElement *GetCurrAnim(){return m_Anim->Anim;}
	Sint32  GetAnim(){return m_Anim->Anim->nActionNumber;}
	bool IsCtrl(){return bCtrl;}
	void SetCtrl(bool value){bCtrl = value;}
	void SetPush(bool isPush){bPush=isPush;}
	void SetAssertNoAutoTurn(bool value){bAssertNoAutoTurn=value;}
	void SetAssetNoWalk(bool value){bAssertNoWalk=value;}
	CCharsConfig* GetConfig(){return m_Config;}

// act
public:
	DrawInfo m_curDrawInfo;
	ActionForPlay* m_Anim;
	ActionForPlay* m_Spark;
	ActionForPlay* m_SuperAnim;
	std::vector<ActionForPlay*> m_Explod;

	ExplodInfo* m_Projhitanim;
	std::vector<ActionForPlay*> m_Proj;

	
	void UpdatePlayerAnimInfo();
	void DrawPlayerAct(Sint32 priority=MAX_INT32);
	void StoreForAfterImage(DrawInfo& info);

	void UpdateProjMove(ActionForPlay* act);
	void UpdateExplodMove(ActionForPlay* act);
	void UpdateAnim(ActionForPlay* act);
	void DrawAct(ActionForPlay* act);

	void DrawPlayer();

	void BlitClsn(ActionForPlay *act, Sint32 x, Sint32 y);
	bool IsPause();
	bool IsShake();

// command
public:
	PLCOMMAND* m_Commands;
	Uint32 m_CommandCount;  
	COMMAND_RECORD_STATUS m_recordStatus;
	Uint16* m_RecordList;
	Uint32 m_RecordCount;
	Uint32 m_RecordPlayIndex;

	//this is the Keyboard buffer
	PLCOMMANDFRAMEINPUT* m_KeyBuffer;
	Uint32 m_KeyBufferSize;
	Uint32 m_KeyIndex;
	// command
	char m_CurrCommandName[MAX_ALLOWED_COMMAND][MAX_ALLOWED_COMMANDSTR_COUNT];
	Sint32 m_InputCommandCount;
	inline int AdjustKeyIndex( int keyIndex, int increment )
	{ return ( keyIndex + increment + m_KeyBufferSize ) % m_KeyBufferSize; }
	bool IsCommandInput(const char* name);
	void AddCommand(const char* name);
	void RecordCommand();
	void RecordCommandEnd();
	void RecordPlay();
	void SaveRecord();
	void LoadRecord();
	const char *GetCommand();

// call by engine
public:
	void BeforeUpDatePlayer();

	virtual void UpdateCommand();
	virtual void HandleSYSFSM();
	void HandleFSM();
	virtual void HandleSYSStateNo();
	void UpDatePlayerFirst();
	
	bool IsClsn(ActionForPlay* act, CONTROLHITDEF* hitDefInfo, float clsnX, float clsnY);
	void DoActionAfterHited(CONTROLHITDEF* hitDefInfo, bool isProj=false);
	void ChangeHitStateEnd();

	void HandleGetHit();
	void HandleHit();
	void HandleProj();
	void HandlePhysic();
	virtual void UpDateFacing();
	virtual void UpdateCamera();
	void UpDatePlayerSecond();

	void AfterUpDatePlayer();

public:
	float GetConfigFloat(const char*);
	const char* GetPlayerName();
	Sint32 GetScreenBack();
	Sint32 GetScreenFront();
	Sint32 GetPlayerBack();
	Sint32 GetPlayerFront();


public:
	bool LoadPlayer(const char* strPlayer, Uint32 pal);
	void DebugInfoToBack();
	void Debug();
	void MoveForward(Sint32 dis);
	void ChangeMoveType(Sint32 dis);
	void ChangeLife(Sint32 value);
	void ChangePower(Sint32 value);
	void ShowCombo(Sint32 value);

	int AnimTime();
	bool isGuardDist();
	bool isGuarded(CONTROLHITDEF* hitinfo);
	void EndGetHited();
	void ChangeState(Sint32 nSateNumber, bool changeByHit = false, bool isP2State= false);
	void ChangePlayerState(CPlayer* curPlayer, Sint32 nStateNumber, bool changeByHit = false);
	void PrepareSpark(CONTROLHITDEF* hitdef, bool isGuard);
	void PrepareSuperAnim(Uint32 nAnim, EnumAnimType type, int x, int y);
	void PrepareProj(ProjectileInfo* info, CONTROLHITDEF* hitdef);
	void PrepareExplod(ExplodInfo* explodinfo);
	void PrepareAnim(Uint32 nAnim, bool isChangeP2Anim=false);
	void PreparePlayerAnim(CPlayer* curPlayer, Uint32 nAnim);
	void PreParePalFX(PalFXInfo* palinfo);
	void PrepareEnvColor(float time, Sint32 r, Sint32 g, Sint32 b, bool isUnder);
	void PrepareShake(float time, float freq, float ampl, float phase);
	bool IsAnimAviable(Sint32 nAnim);
	void PrepareAudio(Sint32 nSndGroupNo, Sint32 nSndNo, SndType type);
	bool CheckState(PLSTATE* tempState, int index);

	Uint32 GetExplodCount(Sint32 explodid);
	Uint32 GetProjCount(Sint32 projid);

	Uint32 GetChildCount();
	CPlayer* GetParent();
	CPlayer* GetRoot();
	bool AddChild(CPlayer* player);
	bool RemovePlayer(CPlayer* player);
	bool RemovePlayerByID(int id);
};

#endif
