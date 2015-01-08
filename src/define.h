/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __DEFINE__H
#define __DEFINE__H
#include "SDL_test_common.h"

#ifdef WIN32
#include "windows.h"

//#define  HAVE_OPENGLES2

#ifdef HAVE_OPENGLES2
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "SDL_opengles2.h"
#else
#include "GL/glew.h"
#include "SDL_opengl.h"
#endif // HAVE_OPENGLES2

#else
#define  HAVE_OPENGLES2
#include "SDL_opengles2.h"
#endif 


//Version
#define VER     "Alpha 1"
#define OMTITLE "kof"

#define MAX_INT32 2147483647
#define MIN_INT32 -2147483648

#define CUR_TIME_START 0
#define CUR_IMAGE_TIME_START 0
#define CUR_IMAGE_INDEX_START 0

#define  CC_MAX_TOUCHES 5
#define MAX_ALLOWED_COMMAND 15
#define MAX_ALLOWED_COMMANDSTR_COUNT 40
#define MAX_COMMAND_RECORD_COUNT 10000
//#define TEXTURE_FORMAT SDL_PIXELFORMAT_RGB565
#define TEXTURE_FORMAT SDL_PIXELFORMAT_RGBA8888
#define BACK_COLOR_ALPHA 128

#define OPEN_ERROR false

#define  SPR_PRIORITY_DEBUGINFO 500
#define  SPR_PRIORITY_STAGE_TOP 400
#define  SPR_PRIORITY_DEBUG 300
#define  SPR_PRIORITY_ENV_TOP 270
#define  SPR_PRIORITY_SUPER_TOP 260
#define  SPR_PRIORITY_TOP 255
#define  SPR_PRIORITY_BOTTOM -255
#define  SPR_PRIORITY_ENV_BOTTOM -270
#define  SPR_PRIORITY_STAGE_BOTTOM -400


#ifndef MAX_PATH
#define  MAX_PATH 256
#endif
#define MAX_STRING_LENGTH          40

#define PLAYR_LAYER_COUNT 5
#define MAX_CLSN_COUNT 10

#define NUMFUNCT_CONTROL 140
#define MAX_STACK_CHAR_LENGTH 10000
#define MAXCOMMAND 30
#define  PALLET_SIZE 256
#define PALLET_MAX_NUM 12

#define DEFAULT_ParmCount_PerState 100
#define DEFAULT_TrgCount_PerState  100
#define  MAX_STATE_NUM 400
#define  INVALID_STATE_NUM -11
#define INVALID_SPR_PRIORITY 100
#define UNSET_STATEDEF_FLAG -3333
#define UNSET_VELOCITY -3333.0f
#define UNSET_HIT_TIIME -1
#define UNSET_HIT_TIME -1
#define DEFAULT_KEY_BUF_MAX 120

// 设计尺寸，和屏幕左右的坐标

#define DEFAULT_STAND_STATE 0
#define DEFAULT_CROUCH_STATE  10
#define DEFAULT_CROUCHING_STATE  11
#define DEFAULT_CROUCH_TOSTAND_STATE  12
#define DEFAULT_WALK_STATE  20

#define DEFAULT_UP_STATE  40
#define DEFAULT_UP_DOWN_STATE  51
#define DEFAULT_LAND_STATE 52

#define DEFAULT_GUARD_START_STATE 120
#define DEFAULT_GUARD_END_STATE 140

#define DEFAULT_LIEDOWN_STATE 5110
#define DEFAULT_GETUP_STATE 5120

enum ENUM_DRAW_RECT_TYPE{
	eDRAW_RECT_TYPE_NONE,
	eDRAW_RECT_TYPE_LINE,
	eDRAW_RECT_TYPE_FILLED,
};


enum COMMAND_RECORD_STATUS{
	COMMAND_RECORD_READY,
	COMMAND_RECORD_START,
	COMMAND_RECORD_PLAY,
};

enum PLAYER_TYPE{
	PLAYER_FIGHTER,
	PLAYER_HELPER,
};

enum DEBUG_STATUS{
	DEBUG_NONE,
	DEBUG_PLAYER1,
	DEBUG_PLAYER2,
	DEBUG_PLAYER3,
	DEBUG_PLAYER4,
};

enum {
    BtnTypeStart = -10,
    BtnTypeMenu = -9,
	BtnTypeChoose = -8,
	BtnTypeDebug = -7,
	BtnTypeDebugClsn = -6,
    BtnTypeMinPlayer = 1
};
enum Jungle
{
	JungleNotSet = -3333,
	JungleMinNum = -1,
};
enum OPCODES
{
	OP_PUSH=0,
	OP_POP,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_EQUAL,
	OP_ASSIGN,
	OP_NOTEQUAL,
	OP_LESS,
	OP_GREATER,
	OP_LESSEQUAL,
	OP_GRAETEREQUAL,
	OP_INTERVALOP1,
	OP_INTERVALOP2,
	OP_INTERVALOP3,
	OP_INTERVALOP4,
	OP_INTERVALOP5,
	OP_INTERVALOP6,
	OP_INTERVALOP7,
	OP_INTERVALOP8,
	OP_LOGNOT,
	OP_LOGAND,
	OP_LOGOR,
	OP_LOGXOR,
	OP_NOT,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_SQUARE,
	OP_NEG,
	OP_MOD,
	OP_LEFT,
	OP_RIGHT,
		OP_STOP,
	OP_Abs,
	OP_Acos,
	OP_AILevel,
	OP_Alive,
	OP_Anim,
	OP_AnimElem,
	OP_AnimElemNo,
	OP_AnimElemTime,
	OP_AnimExist,
	OP_AnimTime,
	OP_Asin,
	OP_Atan,
	OP_AuthorName,
	OP_BackEdgeBodyDist,
	OP_BackEdgeDist,
	OP_CanRecover,
	OP_Ceil,
	OP_Command,
	OP_Cond,
	OP_Const,
	OP_Const240p,
	OP_Const480p,
	OP_Const720p,
	OP_Cos,
	OP_Ctrl,
	OP_DrawGame,
	OP_E,
	OP_Exp,
	OP_Facing,
	OP_Floor,
	OP_FrontEdgeBodyDist,
	OP_FrontEdgeDist,
	OP_FVar,
	OP_GameHeight,
	OP_GameTime,
	OP_GameWidth,
	OP_GetHitVar,
	OP_HitCount,
	OP_HitDefAttr,
	OP_HitFall,
	OP_HitOver,
	OP_HitPauseTime,
	OP_HitShakeOver,
	OP_HitVel,
	OP_ID,
	OP_IfElse,
	OP_InGuardDist,
	OP_IsHelper,
	OP_IsHomeTeam,
	OP_Life,
	OP_LifeMax,
	OP_Log,
	OP_Ln,
	OP_Lose,
	OP_LoseKO,
	OP_LoseTime,
	OP_MatchNo,
	OP_MatchOver,
	OP_MoveContact,
	OP_MoveGuarded,
	OP_MoveHit,
	OP_MoveType,
	OP_MoveReversed,
	OP_Name,
	OP_NumEnemy,
	OP_NumExplod,
	OP_NumHelper,
	OP_NumPartner,
	OP_NumProj,
	OP_NumProjID,
	OP_NumTarget,
	OP_P1Name,
	OP_P2BodyDist,
	OP_P2Dist,
	OP_P2Life,
	OP_P2MoveType,
	OP_P2Name,
	OP_P2StateNo,
	OP_P2StateType,
	OP_P3Name,
	OP_P4Name,
	OP_PalNo,
	OP_ParentDist,
	OP_Pi,
	OP_Pos,
	OP_Power,
	OP_PowerMax,
	OP_PlayerIDExist,
	OP_PrevStateNo,
	OP_ProjCancelTime,
	OP_ProjContact,
	OP_ProjContactTime,
	OP_ProjGuarded,
	OP_ProjGuardedTime,
	OP_ProjHit,
	OP_ProjHitTime,
	OP_Random,
	OP_RootDist,
	OP_RoundNo,
	OP_RoundsExisted,
	OP_RoundState,
	OP_ScreenPos,
	OP_SelfAnimExist,
	OP_Sin,
	OP_StateNo,
	OP_StateType,
	OP_SysFVar,
	OP_SysVar,
	OP_Tan,
	OP_TeamMode,
	OP_TeamSide,
	OP_TicksPerSecond,
	OP_Time,
	OP_TimeMod,
	OP_UniqHitCount,
	OP_Var,
	OP_Vel,
	OP_Win,
	OP_WinKO,
	OP_WinTime,
	OP_WinPerfect,
	OP_parent,
	OP_root,
	OP_helper,
	OP_target,
	OP_partner,
	OP_enemy,
	OP_enemynear,
	OP_playerid,
	OP_END,
};






//All triggers       
static const char STR_TriggerType[][20] = {
	"OP_PUSH",
	"OP_POP",
	"OP_ADD",
	"OP_SUB",
	"OP_MUL",
	"OP_DIV",
	"OP_EQUAL",
	"OP_ASSIGN",
	"OP_NOTEQUAL",
	"OP_LESS",
	"OP_GREATER",
	"OP_LESSEQUAL",
	"OP_GRAETEREQUAL",
	"OP_INTERVALOP1",
	"OP_INTERVALOP2",
	"OP_INTERVALOP3",
	"OP_INTERVALOP4",
	"OP_INTERVALOP5",
	"OP_INTERVALOP6",
	"OP_INTERVALOP7",
	"OP_INTERVALOP8",
	"OP_LOGNOT",
	"OP_LOGAND",
	"OP_LOGOR",
	"OP_LOGXOR",
	"OP_NOT",
	"OP_AND",
	"OP_OR",
	"OP_XOR",
	"OP_SQUARE",
	"OP_NEG",
	"OP_MOD",
	"OP_LEFT",
	"OP_RIGHT",
		"OP_STOP",
	"Abs",
	"Acos",
	"AILevel",
	"Alive",
	"Anim",
	"AnimElem",
	"AnimElemNo",
	"AnimElemTime",
	"AnimExist",
	"AnimTime",
	"Asin",
	"Atan",
	"AuthorName",
	"BackEdgeBodyDist",
	"BackEdgeDist",
	"CanRecover",
	"Ceil",
	"Command",
	"Cond",
	"Const",
	"Const240p",
	"Const480p",
	"Const720p",
	"Cos",
	"Ctrl",
	"DrawGame",
	"E",
	"Exp",
	"Facing",
	"Floor",
	"FrontEdgeBodyDist",
	"FrontEdgeDist",
	"FVar",
	"GameHeight",
	"GameTime",
	"GameWidth",
	"GetHitVar",
	"HitCount",
	"HitDefAttr",
	"HitFall",
	"HitOver",
	"HitPauseTime",
	"HitShakeOver",
	"HitVel",
	"ID",
	"IfElse",
	"InGuardDist",
	"IsHelper",
	"IsHomeTeam",
	"Life",
	"LifeMax",
	"Log",
	"Ln",
	"Lose",
	"LoseKO",
	"LoseTime",
	"MatchNo",
	"MatchOver",
	"MoveContact",
	"MoveGuarded",
	"MoveHit",
	"MoveType",
	"MoveReversed",
	"Name",
	"NumEnemy",
	"NumExplod",
	"NumHelper",
	"NumPartner",
	"NumProj",
	"NumProjID",
	"NumTarget",
	"P1Name",
	"P2BodyDist",
	"P2Dist",
	"P2Life",
	"P2MoveType",
	"P2Name",
	"P2StateNo",
	"P2StateType",
	"P3Name",
	"P4Name",
	"PalNo",
	"ParentDist",
	"Pi",
	"Pos",
	"Power",
	"PowerMax",
	"PlayerIDExist",
	"PrevStateNo",
	"ProjCancelTime",
	"ProjContact",
	"ProjContactTime",
	"ProjGuarded",
	"ProjGuardedTime",
	"ProjHit",
	"ProjHitTime",
	"Random",
	"RootDist",
	"RoundNo",
	"RoundsExisted",
	"RoundState",
	"ScreenPos",
	"SelfAnimExist",
	"Sin",
	"StateNo",
	"StateType",
	"SysFVar",
	"SysVar",
	"Tan",
	"TeamMode",
	"TeamSide",
	"TicksPerSecond",
	"Time",
	"TimeMod",
	"UniqHitCount",
	"Var",
	"Vel",
	"Win",
	"WinKO",
	"WinTime",
	"WinPerfect",
	"parent",
	"root",
	"helper",
	"target",
	"partner",
	"enemy",
	"enemyNear",
	"playerID",
	0,
};










// 参数个数 0 1 2, 3， -1代表特殊
// 11 代表存在组件的
#define COMPONENT_ARGCS 1
#define SPECIAL_ARGCS -1
#define ERROR_ARGCS 12
//All triggers       
static int strTriggerArgcs[] = {
	ERROR_ARGCS,//"OP_PUSH",
	ERROR_ARGCS,//"OP_POP",
	ERROR_ARGCS,//"OP_ADD",
	ERROR_ARGCS,//"OP_SUB",
	ERROR_ARGCS,//"OP_MUL",
	ERROR_ARGCS,//"OP_DIV",
	ERROR_ARGCS,//"OP_EQUAL",
	ERROR_ARGCS,//"OP_ASSIGN",
	ERROR_ARGCS,//"OP_NOTEQUAL",
	ERROR_ARGCS,//"OP_LESS",
	ERROR_ARGCS,//,"OP_GREATER",
	ERROR_ARGCS,//,"OP_LESSEQUAL",
	ERROR_ARGCS,//,"OP_GRAETEREQUAL",
	ERROR_ARGCS,//,"OP_INTERVALOP1",
	ERROR_ARGCS,//,"OP_INTERVALOP2",
	ERROR_ARGCS,//,"OP_INTERVALOP3",
	ERROR_ARGCS,//,"OP_INTERVALOP4",
	ERROR_ARGCS,//,"OP_INTERVALOP5",
	ERROR_ARGCS,//,"OP_INTERVALOP6",
	ERROR_ARGCS,//,"OP_INTERVALOP7",
	ERROR_ARGCS,//,"OP_INTERVALOP8",
	ERROR_ARGCS,//,//,"OP_LOGNOT",
	ERROR_ARGCS,//,"OP_LOGAND",
	ERROR_ARGCS,//,"OP_LOGOR",
	ERROR_ARGCS,//"OP_LOGXOR",
	ERROR_ARGCS,//"OP_NOT",
	ERROR_ARGCS,//"OP_AND",
	ERROR_ARGCS,//"OP_OR",
	ERROR_ARGCS,//"OP_XOR",
	ERROR_ARGCS,//"OP_SQUARE",
	ERROR_ARGCS,//"OP_NEG",
	ERROR_ARGCS,//	OP_MOD,
	ERROR_ARGCS, //OP_LEFT
	ERROR_ARGCS, //RIGHT
	ERROR_ARGCS,//stop
	1,//"Abs",
	1,//"Acos",
	0,//"AILevel"
	0,//"Alive",
	0,//"Anim",
	SPECIAL_ARGCS,//"AnimElem",
	1,//"AnimElemNo",
	1,//"AnimElemTime",
	1,//"AnimExist",
	0,//"AnimTime",
	1,//"Asin",
	1,//"Atan",
	0,//"AuthorName",
	0,//"BackEdgeBodyDist",
	0,//"BackEdgeDist",
	0,//"CanRecover",
	1,//"Ceil",
	0,//"Command",
	SPECIAL_ARGCS,//"Cond",
	1,//"Const",
	1,//"Const240p",
	1,//"Const480p",
	1,//"Const720p",
	1,//"Cos",
	0,//"Ctrl",
	0,//"DrawGame",
	0,//"E",
	SPECIAL_ARGCS,//"Exp",
	0,//"Facing",
	1,//"Floor",
	0,//"FrontEdgeBodyDist",
	0,//"FrontEdgeDist",
	1,//"FVar",
	0,//"GameHeight",
	0,//"GameTime",
	0,//"GameWidth",
	1,//"GetHitVar",
	0,//"HitCount",
	SPECIAL_ARGCS,//"HitDefAttr",
	0,//"HitFall",
	0,//"HitOver",
	0,//"HitPauseTime",
	0,//"HitShakeOver",
	COMPONENT_ARGCS,//"HitVel",
	0,//"ID",
	SPECIAL_ARGCS,//"IfElse",
	0,//"InGuardDist",
	SPECIAL_ARGCS,//"IsHelper",
	0,//"IsHomeTeam",
	0,//"Life",
	0,//"LifeMax",
	SPECIAL_ARGCS,//"Log",
	1,//"Ln",
	0,//"Lose",
	0,//"LoseKO",
	0,//"LoseTime",
	0,//"MatchNo",
	0,//"MatchOver",
	0,//"MoveContact",
	0,//"MoveGuarded",
	0,//"MoveHit",
	0,//"MoveType",
	0,//"MoveReversed",
	0,//"Name",
	0,//"NumEnemy",
	SPECIAL_ARGCS,//"NumExplod",
	SPECIAL_ARGCS,//"NumHelper",
	0,//"NumPartner",
	0,//"NumProj",
	1,//"NumProjID",
	SPECIAL_ARGCS,//"NumTarget",
	0,//"P1Name",
	COMPONENT_ARGCS,//"P2BodyDist",
	COMPONENT_ARGCS,//"P2Dist",
	0,//"P2Life",
	0,//"P2MoveType",
	0,//"P2Name",
	0,//"P2StateNo",
	0,//"P2StateType",
	0,//"P3Name",
	0,//"P4Name",
	0,//"PalNo",
	COMPONENT_ARGCS,//"ParentDist",
	0,//"Pi",
	COMPONENT_ARGCS,//"Pos",
	0,//"Power",
	0,//"PowerMax",
	1,//"PlayerIDExist",
	0,//"PrevStateNo",
	1,//"ProjCancelTime",
	SPECIAL_ARGCS,//"ProjContact",
	1,//"ProjContactTime",
	SPECIAL_ARGCS,//"ProjGuarded",
	1,//"ProjGuardedTime",
	SPECIAL_ARGCS,//"ProjHit",
	1,//"ProjHitTime",
	0,//"Random",
	COMPONENT_ARGCS,//"RootDist",
	0,//"RoundNo",
	0,//"RoundsExisted",
	0,//"RoundState",
	COMPONENT_ARGCS,//"ScreenPos",
	1,//"SelfAnimExist",
	1,//"Sin",
	0,//"StateNo",
	0,//"StateType",
	1,//"SysFVar",
	1,//"SysVar",
	1,//"Tan",
	SPECIAL_ARGCS,//"TeamMode",
	0,//"TeamSide",
	0,//"TicksPerSecond",
	0,//"Time",
	SPECIAL_ARGCS,//"TimeMod",
	0,//"UniqHitCount",
	1,//"Var",
	COMPONENT_ARGCS,//"Vel",
	0,//"Win",
	0,//"WinKO",
	0,//"WinTime",
	0,//"WinPerfect",
	SPECIAL_ARGCS,//"parent",
	SPECIAL_ARGCS,//"root",
	SPECIAL_ARGCS,//"helper",
	SPECIAL_ARGCS,//"target",
	SPECIAL_ARGCS,//"partner",
	SPECIAL_ARGCS,//"enemy",
	SPECIAL_ARGCS,//"enemyNear",
	SPECIAL_ARGCS,//"playerID",
};





//! ~ -					13
//**					12
//* / %					11
//+ -					10
//> >= < <=				9
//= != intervals		8
//:=					7 
//&						6
//^						5
//|						4
//&&					3
//^^					2
//||					1

// 一级开始
static int OP_Precedence[] = {
	14,//"OP_PUSH",
	14,//"OP_POP",
	10,//"OP_ADD",
	10,//"OP_SUB",
	11,//"OP_MUL",
	11,//"OP_DIV",
	8,//"OP_EQUAL",
	7,//"OP_ASSGIN",
	8,//"OP_NOTEQUAL",
	9,//"OP_LESS",
	9,//,"OP_GREATER",
	9,//,"OP_LESSEQUAL",
	9,//,"OP_GRAETEREQUAL",
	8,//,"OP_INTERVALOP1",
	8,//,"OP_INTERVALOP2",
	8,//,"OP_INTERVALOP3",
	8,//,"OP_INTERVALOP4",
	8,//,"OP_INTERVALOP5",
	8,//,"OP_INTERVALOP6",
	8,//,"OP_INTERVALOP7",
	8,//,"OP_INTERVALOP8",
	13,//,//,"OP_LOGNOT",
	3,//,"OP_LOGAND",
	1,//,"OP_LOGOR",
	2,//"OP_LOGXOR",
	13,//"OP_NOT",
	6,//"OP_AND",
	4,//"OP_OR",
	5,//"OP_XOR",
	12,//"OP_SQUARE",
	13,//"OP_NEG",
	11,//	OP_MOD,
	0,//left
	0,//RIGHT
	0,//stop
};

enum {
	MAINMENU=0,
	P1,
	P2,
	P3,
	P4,
	STAGE,
	ENGINE,
	CONFIG,
	MEM_EUUN_END,
};


enum DIRECTION
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP_LEFT,
	DIR_UP_RIGHT,
	DIR_DOWN_LEFT,
	DIR_DOWN_RIGHT,
	DIR_COUNT
};
//Define  Controller buttoms
enum KEY_NAMES
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
    KEY_BUTTON_A,
	KEY_BUTTON_B,
	KEY_BUTTON_C,
	KEY_BUTTON_X,
	KEY_BUTTON_Y,
	KEY_BUTTON_Z,
	KEY_BUTTON_START,
	KEY_COUNT
};




//This are all documented Controllers
//TODO: find the undocumented controllers
static const char* strControllerTypes[] = {
	"AfterImage",
	"AfterImageTime",
	"AllPalFX",
	"AngleAdd",
	"AngleDraw",
	"AngleMul",
	"AngleSet",
	"AppendToClipboard",
	"AssertSpecial",
	"AttackDist",
	"AttackMulSet",
	"BGPalFX",
	"BindToParent",
	"BindToRoot",
	"BindToTarget",
	"ChangeAnim",
	"ChangeAnim2",
	"ChangeState",
	"ClearClipboard",
	"CtrlSet",
	"DefenceMulSet",
	"DestroySelf",
	"DisplayToClipboard",
	"EnvColor",
	"EnvShake",
	"Explod",
	"ExplodBindTime",
	"ForceFeedback",
	"FallEnvShake",
	"GameMakeAnim",
	"Gravity",
	"Helper",
	"HitAdd",
	"HitBy",
	"HitDef",
	"HitFallDamage",
	"HitFallSet",
	"HitFallVel",
	"HitOverride",
	"HitVelSet",
	"LifeAdd",
	"LifeSet",
	"MakeDust",
	"ModifyExplod",
	"MoveHitReset",
	"NotHitBy",
	"Null",
	"Offset",
	"PalFX",
	"ParentVarAdd",
	"ParentVarSet",
	"Pause",
	"PlayerPush",
	"PlaySnd",
	"PosAdd",
	"PosFreeze",
	"PosSet",
	"PowerAdd",
	"PowerSet",
	"Projectile",
	"RemoveExplod",
	"ReversalDef",
	"ScreenBound",
	"SelfState",
	"SprPriority",
	"StateTypeSet",
	"SndPan",
	"StopSnd",
	"SuperPause",
	"TargetBind",
	"TargetDrop",
	"TargetFacing",
	"TargetLifeAdd",
	"TargetPowerAdd",
	"TargetState",
	"TargetVelAdd",
	"TargetVelSet",
	"Trans",
	"Turn",
	"VarAdd",
	"VarRandom",
	"VarRangeSet",
	"VarSet",
	"VelAdd",
	"VelMul",
	"VelSet",
	"Width",
	"AddCommandInput",
	"Print",
	0,
};






enum{
	Control_AfterImage =0,
	Control_AfterImageTime,
	Control_AllPalFX,
	Control_AngleAdd,
	Control_AngleDraw,
	Control_AngleMul,
	Control_AngleSet,
	Control_AppendToClipboard,
	Control_AssertSpecial,
	Control_AttackDist,
	Control_AttackMulSet,
	Control_BGPalFX,
	Control_BindToParent,
	Control_BindToRoot,
	Control_BindToTarget,
	Control_ChangeAnim,
	Control_ChangeAnim2,
	Control_ChangeState,
	Control_ClearClipboard,
	Control_CtrlSet,
	Control_DefenceMulSet,
	Control_DestroySelf,
	Control_DisplayToClipboard,
	Control_EnvColor,
	Control_EnvShake,
	Control_Explod,
	Control_ExplodBindTime,
	Control_ForceFeedback,
	Control_FallEnvShake,
	Control_GameMakeAnim,
	Control_Gravity,
	Control_Helper,
	Control_HitAdd,
	Control_HitBy,
	Control_HitDef,
	Control_HitFallDamage,
	Control_HitFallSet,
	Control_HitFallVel,
	Control_HitOverride,
	Control_HitVelSet,
	Control_LifeAdd,
	Control_LifeSet,
	Control_MakeDust,
	Control_ModifyExplod,
	Control_MoveHitReset,
	Control_NotHitBy,
	Control_Null,
	Control_Offset,
	Control_PalFX,
	Control_ParentVarAdd,
	Control_ParentVarSet,
	Control_Pause,
	Control_PlayerPush,
	Control_PlaySnd,
	Control_PosAdd,
	Control_PosFreeze,
	Control_PosSet,
	Control_PowerAdd,
	Control_PowerSet,
	Control_Projectile,
	Control_RemoveExplod,
	Control_ReversalDef,
	Control_ScreenBound,
	Control_SelfState,
	Control_SprPriority,
	Control_StateTypeSet,
	Control_SndPan,
	Control_StopSnd,
	Control_SuperPause,
	Control_TargetBind,
	Control_TargetDrop,
	Control_TargetFacing,
	Control_TargetLifeAdd,
	Control_TargetPowerAdd,
	Control_TargetState,
	Control_TargetVelAdd,
	Control_TargetVelSet,
	Control_Trans,
	Control_Turn,
	Control_VarAdd,
	Control_VarRandom,
	Control_VarRangeSet,
	Control_VarSet,
	Control_VelAdd,
	Control_VelMul,
	Control_VelSet,
	Control_Width,
	Control_AddCommandInput,
	Control_Print,

};



enum ConParmName
{
	CPN_value = 1,
	CPN_emem,
	CPN_animtype,
	CPN_anim,
	CPN_ctrl,
	CPN_x,
	CPN_y,
	CPN_v,
	CPN_fv,
	CPN_sysv,
	CPN_sysfv,
	CPN_back,
	CPN_screenBack,
	CPN_front,
	CPN_screenFront,
	CPN_statetype,
	CPN_movetype,
	CPN_physics,
	CPN_flag,

	CPN_darken,
	CPN_p2defmul,
	CPN_poweradd,
	CPN_unhittable,

	CPN_time,
	CPN_id,
	CPN_length,
	CPN_timegap,
	CPN_framegap,

	CPN_sndType,
	CPN_SndGroupNo,
	CPN_SndNo,

	CPN_text,
	CPN_Param,

	CPN_helpertype,
	CPN_name,
	CPN_facing,
	CPN_stateno,
	CPN_postype,
	CPN_keyctrl,
	CPN_ownpal,

	CPN_freq,
	CPN_ampl,
	CPN_phase,

	CPN_under,
	CPN_color_r,
	CPN_color_g,
	CPN_color_b,

	CPN_Command,

};

enum CONTROLHITDEFParmName
{
	CHD_attr = 1,
	CHD_hitflag,
	CHD_guardflag,
	CHD_affectteam,
	CHD_animtype,
	CHD_air_animtype,
	CHD_fall_animtype,
	CHD_priority,
	CHD_damage,
	CHD_pausetime,
	CHD_guard_pausetime,
	CHD_sparkno,
	CHD_guard_sparkno,
	CHD_sparkxy,
	CHD_hitsound,
	CHD_guardsound,
	CHD_ground_type,
	CHD_air_type,
	CHD_ground_slidetime,
	CHD_guard_slidetime,
	CHD_ground_hittime,
	CHD_guard_hittime,
	CHD_air_hittime ,
	CHD_guard_ctrltime,
	CHD_guard_dist,
	CHD_yaccel,
	CHD_ground_velocity,
	CHD_guard_velocity ,
	CHD_air_velocity,
	CHD_airguard_velocity,
	CHD_ground_cornerpush_veloff,
	CHD_air_cornerpush_veloff,
	CHD_down_cornerpush_veloff,
	CHD_guard_cornerpush_veloff,
	CHD_airguard_cornerpush_veloff,
	CHD_airguard_ctrltime,
	CHD_air_juggle,
	CHD_mindist,
	CHD_maxdist,
	CHD_snap,
	CHD_p1sprpriority,
	CHD_p2sprpriority,
	CHD_p1facing,
	CHD_p1getp2facing,
	CHD_p2facing,
	CHD_p1stateno,
	CHD_p2stateno,
	CHD_p2getp1state,
	CHD_forcestand,
	CHD_fall,
	CHD_fall_xvelocity,
	CHD_fall_yvelocity,
	CHD_fall_recover,
	CHD_fall_recovertime,
	CHD_fall_damage,
	CHD_air_fall,
	CHD_forcenofall,
	CHD_down_velocity,
	CHD_down_hittime,
	CHD_down_bounce,
	CHD_id,
	CHD_chainID,
	CHD_nochainID,
	CHD_hitonce,
	CHD_kill,
	CHD_guard_kill,
	CHD_fall_kill,
	CHD_numhits,
	CHD_getpower,
	CHD_givepower,
	CHD_palfx_time,
	CHD_palfx_mul,
	CHD_palfx_add,
	CHD_envshake_time,
	CHD_envshake_freq,
	CHD_envshake_ampl,
	CHD_envshake_phase,
	CHD_fall_envshake_time,
	CHD_fall_envshake_freq,
	CHD_fall_envshake_ampl,
	CHD_fall_envshake_phase,
};


//is for debug output
static const char *s_StateStr[]={
	"0",
	"stand",
	"crouch",
	"air",
	"liedown",
	"unchange"
}; 

//StateTypes
enum StateTypes
{
	s_stand=1,
	s_crouch,
	s_air,
	s_liedown,
	s_untouch
};

//is for debug output
static const char *m_StateStr[]={
	"idle",
	"attack",
	"hit",
	"unchange"
}; 
enum MoveTypes
{
	m_idle=0,
	m_attack,
	m_hit,
	m_untouch,
};

//is for debug output
static const char *p_StateStr[]={
	"stand",
	"crouch",
	"air",
	"none",
	"unchange"
};
enum Physics
{
	p_stand=0,
	p_crouch,
	p_air,
	p_none,
	p_untouch
};

// hitdef
enum HitDef_animtype
{
	HitDef_animtype_light=0,
	HitDef_animtype_medium,
	HitDef_animtype_hard,
	HitDef_animtype_back,
	HitDef_animtype_up,
	HitDef_animtype_diagup,
};

// hitdef
enum HitDef_atk_type
{
	HitDef_atk_type_None=0,
	HitDef_atk_type_High,
	HitDef_atk_type_Low,
	HitDef_atk_type_Trip,
};


enum HitDef_Attr_Enum
{
	HitDef_Attr_Stand=1<<0,
	HitDef_Attr_Crouch=1<<1,
	HitDef_Attr_Aerial=1<<2,

	HitDef_Attr_NA=1<<3,
	HitDef_Attr_SA=1<<4,
	HitDef_Attr_HA=1<<5,

	HitDef_Attr_NT=1<<6,
	HitDef_Attr_ST=1<<7,
	HitDef_Attr_HT=1<<8,

	HitDef_Attr_NP = 1<<9,
	HitDef_Attr_SP = 1<<10,
	HitDef_Attr_HP = 1<<11,

	HitDef_Attr_AA = HitDef_Attr_NA|HitDef_Attr_SA|HitDef_Attr_HA,
	HitDef_Attr_AT = HitDef_Attr_NT|HitDef_Attr_ST|HitDef_Attr_HT,
	HitDef_Attr_AP = HitDef_Attr_NP|HitDef_Attr_SP|HitDef_Attr_HP,
};
#define HitDef_Attr_STATE_MASK ~(-1<<3)
#define HitDef_Attr_ATK_MASK -1<<3


static char HitDef_Attr_SelfType[] = {'S','C','A'};
static char HitDef_Attr_LevelType[] = {'N','S','H'};
static const char HitDef_Attr_AtkType[] = {'A','T','P'};

enum EnumAnimType
{
	AnimPlayer=0,
	AnimFightFX,
	AnimBack,
};    

enum ActType
{
	ActAnim=0,
	ActSuperAnim,
	ActSpark,
	ActExplod,
	ActProj,
	ActBack,
};  

enum SndType
{
	SndPlayer=0,
	SndFight,
	SndCommon,
	SndSystem,
};    


#define Prop_Get_Set(type, name) type m_prop##name;\
	void SetProp##name(type value){m_prop##name=value;}\
	type GetProp##name(){return m_prop##name;}



#define Vector_Get_Set(type,length, name) type m_vector##name[length];\
	void SetVector##name(Uint32 index, type value){ if (index>=length){return;}	m_vector##name[index]=value;}\
	type GetVector##name(Uint32 index){if (index>=length){return 0;} return m_vector##name[index];}

#define GET_ALL_LINE_TOKEN(token) do{token.GetToken();}while (!token.AtEnd());
#define GET_ALL_LINE(token) while (!token.AtEnd()){token.GetToken();}

#if 1
#define DEBUGBEGIN(name) CGameTimer::GetInstance()->DebugTimeBegin(#name)
#define DEBUGEND(name) CGameTimer::GetInstance()->DebugTimeEnd(#name)
#else
#define DEBUGBEGIN(name) 
#define DEBUGEND(name) 
#endif

#endif
