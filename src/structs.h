/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __STRUCTS__H
#define __STRUCTS__H
#include "define.h"
#include <SDL.h>

//typedefs
typedef Uint8   u8;
typedef Sint8   s8;
typedef Uint16 u16;
typedef Sint16  s16;
typedef Uint32   u32;
typedef Sint32   s32;


enum TransType
{
	eTransTypeNone,
	eTransTypeAdd,
	eTransTypeSub,
	eTransTypeAdd1,
	eTransTypeAddAlpha,
};

struct PaletteFormat
{
#ifdef __KOF_EDITOR
	Uint8 paldata[768];
#endif // __KOF_EDITOR
	SDL_Color color[PALLET_SIZE];
	char palName[MAX_PATH];
};
struct SFFSPRITE;
struct DrawInfo
{
	DrawInfo()
	{
		spr = NULL;
		transMode= eTransTypeNone;
		desAlpha = 0;
		srcAlpha = 0xff;
		pal = NULL;
		nPosX=nPosY=0;
		nScaleX=nScaleY=1;
		percentx=percenty = 1.0;
		bDrawBack = false;
		flip = SDL_FLIP_NONE;
	}
	//for video draw
	SFFSPRITE* spr;
	PaletteFormat* pal;

	//for texture2d draw
	// pos in screen (differed by faced)
	Sint32 nScreenPosX,nScreenPosY;
	// real pos
	Sint32 nPosX,nPosY;
	// actanim's change pos
	float nScaleX,nScaleY;
	float percentx, percenty;
	bool bDrawBack;
	TransType transMode;
	Uint16 srcAlpha;
	Uint16 desAlpha;
	SDL_RendererFlip flip;
};

typedef struct velocity 
{
	float x;
	float y;
}velocity; 

struct KEYELEMENT
{
	KEYELEMENT()  { isPressed = false; sdlKeycode = 0; }
	Uint16 isPressed, sdlKeycode;
};


//now lets define a command

#define PLC_KEYMOD_MUST_BE_HELD    ( 1 << 0 )
#define PLC_KEYMOD_DETECT_AS_4WAY  ( 1 << 1 )
#define PLC_KEYMOD_BAN_OTHER_INPUT ( 1 << 2 )
#define PLC_KEYMOD_ON_RELEASE      ( 1 << 3 )
#define PLC_KEYCODE(x)             ( 1 << x )
#define IsKeyInPLCKeyCode( k, c )  (( PLC_KEYCODE( k ) & c ) > 0 )

#define PLC_ALL_DIRECTIONS_BITFIELD ( PLC_KEYCODE( KEY_UP ) + PLC_KEYCODE( KEY_DOWN ) + PLC_KEYCODE( KEY_LEFT ) + PLC_KEYCODE( KEY_RIGHT ) )
#define PLC_ALL_KEYS ~PLC_ALL_DIRECTIONS_BITFIELD

struct PLCOMMANDELEMENT
{
	PLCOMMANDELEMENT() { keyCode = 0; keyModifier = 0; gameTicksForHold = 0; }
	int keyCode;
	Uint16 keyModifier;
	Uint16 gameTicksForHold;
};

struct PLCOMMANDFRAMEINPUT
{
	PLCOMMANDFRAMEINPUT()  { keyBitfield = gameTicks = 0; }
	Uint16 keyBitfield;
	Uint32 gameTicks;
};

struct PLCOMMAND
{
	PLCOMMANDELEMENT nCommand[MAXCOMMAND];
	Uint8 nHowManyCommand;
	Uint8 nCommandTime, nBufferTime;
	char strCommand[255];

};


//Movedata Struct for Saving the current Button States
struct KEYBOARDDATA
{
	KEYELEMENT keyInfo[ KEY_COUNT ];
	bool bKeyBoard;
};


//memlist for Allocater class
struct MEMLIST
{
	u8    nType;
	size_t   nSize;
	void *adrress;    

};


struct SFFHEADER
{
	Uint8 signature[11];
	Uint8 verhi;
	Uint8 verlo;
	Uint8 verhi2;
	Uint8 verlo2;
	Uint32		  NumberOfGroups;
	Uint32		  NumberOfImage;
	Uint32		  SubHeaderFileOffset;
	Uint32		  SizeOfSubheader;
	Uint8 PaletteType;
	Uint8 BLANK[476];
};
//Sff Subheader
struct SFFSUBHEADER
{
	Uint32 NextSubheaderFileOffset;
	Uint32 LenghtOfSubheader;
	Sint16 x;
	Sint16 y;
	Sint16 GroubNumber;
	Sint16 ImageNumber;
	Sint16 IndexOfPrevious;
	bool  PalletSame;
	Uint8 BALNK[13];
};
struct PCXHEADER
{
	Uint8 Manufacturer;
	Uint8 Version;
	Uint8 Encoding;
	Uint8 BPP;
	Uint16 x,y,widht,height;
	Uint16 HRES;
	Uint16 VRES;
	Uint8 ColorMap[48];
	Uint8 reserved;
	Uint8 NPlanes;
	Uint16 bytesPerLine;
	Uint16 palletInfo;
	Uint16 screenX;
	Uint16 screenY;
	Uint8 Filler[54];
};

struct FNTHEADER
{
	Uint8 signature[11];
	Uint8 verhi;
	Uint8 verlo;
	Uint8 verhi2;
	Uint8 verlo2;
	Uint32		  NextSubheaderFileOffset;
	Uint32		  NumberOfImage;
	Uint32		  SubHeaderFileOffset;
	Uint32		  SizeOfSubheader;
};

//Sound  header
struct SNDHEADER
{
	Uint8 strSignatur[12];
	Sint16 verhi;
	Sint16 verlo;
	Uint32 nNumberOfSounds;
	Uint32 SubHeaderFileOffset;
	Uint8 strBlank[488];

};

//Sound SubHeader
struct SNDSUBHEADER
{
	Uint32  NextSubHeaderFileOffset;
	Uint32  SubFileLenght;
	Sint32  nGroupNumber;
	Sint32  nSoundNumber;

};

//Sound SubHeader
struct SNDELEMENT
{
	Sint32  nGroupNumber;
	Sint32  nSoundNumber;

	Uint8 *sound;               /* Pointer to wave data */
	Uint32 soundlen;            /* Length of wave data */
};

struct SFFSPRITE
{
	Sint16 x;
	Sint16 y;
#ifdef __KOF_EDITOR
	SFFSUBHEADER subhead;
#endif // _KOF_EDITOR
	PCXHEADER PcxHeader;
	Sint16 GroupNumber;
	Sint16 ImageNumber;
	bool bSharePallet;
	PaletteFormat *ColorPallet;
#ifdef __KOF_EDITOR
	Uint32 byPcxFileLength;
#endif // _KOF_EDITOR
	Uint8 *byPcxFile;
};

struct SFFFile
{
	SFFHEADER head;
	Sint32	nTotalImages;
	Sint32 nImageListSize;
	SFFSPRITE* pSffList;
};

struct V3_FLOAT
{
	V3_FLOAT(){
		r=g=b=0.0;
	}
	V3_FLOAT(float a,float b,float c)
	{
		r=a;
		g=b;
		b=c;
	}
	float r,g,b;
};

struct V3_SINT16
{
	V3_SINT16(Sint16 a1,Sint16 b1,Sint16 c1)
	{
		r=a1;
		g=b1;
		b=c1;
	}
	Sint16 r,g,b;
};


struct Stacktype
{
	float Value;
	char string[MAX_STRING_LENGTH]; 
};


struct XYVALUE
{
	float x; 
	float y;          
};

// 操作堆栈的元素
struct OpElement
{   
	Uint16 n_OpCode;
	float Value;
	char strValue[MAX_STRING_LENGTH];

};
// 触发器，一个触发器就是一个表达式
struct TriggerStruct
{
	Uint8 nTriggerIndex;
	OpElement* pInts;
	Uint8 nIntCount;

};

// 触发器执行需要的值，用表达式保存，
struct CtrlParamStruct
{
	ConParmName nParam;
	//TODO:动态生成内存
	OpElement* pInts;
};

struct EvnColorStuct
{
	float time;
	float passedtime;
	Uint8 color_r;
	Uint8 color_g;
	Uint8 color_b;
	Sint32 priority;
};


struct EvnShakeStuct
{
	EvnShakeStuct(){
		time =0;
		passedtime = 0;
		freq = 60;
		ampl = 10;
		phase = 0;
	}
	float time;
	float passedtime;
	float freq;
	float ampl;
	float phase;
};

enum EnumHelperType
{
	eHelperType_Normal,
	eHelperType_Player
};

enum EnumPosType
{
	eEnumPosType_P1,
	eEnumPosType_P2,
	eEnumPosType_Front,
	eEnumPosType_Back,
	eEnumPosType_Left,
	eEnumPosType_Right,
};
struct ExplodInfo
{
	ExplodInfo()
	{
		nAnim = 0;
		AnimType = AnimPlayer;
		nExplodID = 0;
		posx = posy = NULL;
		postype =eEnumPosType_P1;
		bFaceing = bVFaceing = true;
		nBindtime = 0;
		velx=vely=0;
		accelx = accely =0;
		nRandomX = nRandomY = 0;
		nRemovetime = -2;
		bSuperMove = false;
		nSuperMoveTime = nPauseMoveTime = 0;
		scalex=scaley = 1.0;
		nSprpriority = 0;
		bOnTop = 0;
		ShadowB = ShadowG = ShadowR = 0;
		bOwnPal = 0;
		bRemoveongethit = false;
		bignorehitpause = true;
		trans = eTransTypeNone;
		desalpha = srcalpha = 0xff;
	}
	Sint32 nAnim;
	EnumAnimType AnimType;
	Sint32 nExplodID;
	OpElement* posx, *posy;
	EnumPosType postype;
	Sint8 bFaceing;
	Sint8 bVFaceing;
	Sint32 nBindtime;
	float velx, vely;
	float accelx, accely;
	Sint32 nRandomX, nRandomY;
	Sint32 nRemovetime;
	bool bSuperMove;
	Sint32 nSuperMoveTime;
	Sint32 nPauseMoveTime;
	float scalex, scaley;
	Sint32 nSprpriority;
	bool bOnTop;
	Sint32 ShadowR, ShadowG, ShadowB;
	bool bOwnPal;
	bool bRemoveongethit;
	//seted when exec
	bool bignorehitpause;
	TransType trans;
	Sint16 srcalpha, desalpha;
};

struct ProjectileInfo
{
	ProjectileInfo()
	{
		nAnim = -1;
		nProjID = 0;
		nProjhitanim = -1;
		nProjremanim = -1;
		nProjcancelanim = -1;
		scalex = scaley = 1;
		bProjremove = 1;
		nRemovetime = -1;
		velx = vely = 0;
		remvelocityx = remvelocityy = 0;
		accelx = accely = 0;
		velmulx = velmuly = 1;
		nProjhits = 1;
		nProjmisstime = 0;
		nProjpriority = 1;
		nSprpriority = 3;

		nProjedgebound = 120;
		nProjstagebound = 120;
		nProjheightbound = 4;

		posx=posy=0;
		postype = eEnumPosType_P1;

		ShadowR=ShadowG= ShadowB = 0;
		nSuperMoveTime = 0;
		nPauseMoveTime = 0;
	}
	Sint32 nAnim;
	Sint32 nProjID;
	Sint32 nProjhitanim;
	Sint32 nProjremanim;
	Sint32 nProjcancelanim;
	float scalex, scaley;
	bool bProjremove;
	Sint32 nRemovetime;
	float velx, vely;
	float remvelocityx, remvelocityy;
	float accelx, accely;
	float velmulx, velmuly;
	Sint32 nProjhits;
	Sint32 nProjmisstime;
	Sint32 nProjpriority;
	Sint32 nSprpriority;

	Sint32 nProjedgebound;
	Sint32 nProjstagebound;
	Sint32 nProjheightbound;

	float posx,posy;
	EnumPosType postype;

	Sint32 ShadowR, ShadowG, ShadowB;
	Sint32 nSuperMoveTime;
	Sint32 nPauseMoveTime;
	// after image not supported
};

struct PalFXInfo
{
	PalFXInfo()
	{
		nowtime = 0;
		time=0;
		palcolor = 1.0;
		palinvertall = 0.0;
		palbright.r = palbright.g = palbright.b = 0.0;
		palcontrast.r = palcontrast.g = palcontrast.b = 1.0;
		sinadd.r = sinadd.g = sinadd.b = 0.0;
		sinperiod = 0.0;
	}
	Sint16 time;
	Sint16 nowtime;
	float palcolor;
	bool palinvertall;
	V3_FLOAT palbright;
	V3_FLOAT palcontrast;
	V3_FLOAT sinadd;
	float sinperiod ;
};

struct  AfterImage
{
	AfterImage()
	{
		palbright.r = palbright.g = palbright.b = 30.0/256.0;
		palcontrast.r = palcontrast.g = palcontrast.b = 120.0/256.0;
		palpostbright.r = palpostbright.g = palpostbright.b = 0.0;
		paladd.r = paladd.g = 10.0/256.0;
		paladd.b = 25.0/256.0;
		palmul.r = palmul.g = 0.65;
		palmul.b = 0.75;
		time = 1;
		length = 20;
		palcolor = 1;
		palinvertall = false;
		timegap=3;
		framegap = 4;
		trans = eTransTypeNone;
	}
	Sint16 time;
	Sint16 length;
	float palcolor;
	bool palinvertall;
	V3_FLOAT palbright;
	V3_FLOAT palcontrast;
	V3_FLOAT palpostbright;
	V3_FLOAT paladd;
	V3_FLOAT palmul;
	Sint16 timegap;
	Sint16 framegap;
	TransType trans;
};

#define MaxAfterImageSize 60
struct AfterImageStack
{
	AfterImageStack()
		:config(NULL)
	{
	}
	AfterImage* config;
	DrawInfo stack[MaxAfterImageSize];
	Sint16 bottom, top;
	Sint16 duringTime;
	Uint32 EndTime;
};

enum EnumRenderSprType{
	eEnumRenderNormal,
	eEnumRenderAfterImage,
	eEnumRenderTexture,
	eEnumRenderRect,
};

class CCTexture2D;
struct RenderRectInfo
{
	Uint8 R, G, B;
	int x, y, width, height;
	ENUM_DRAW_RECT_TYPE drawType;
	float srcAlpha, desAlpha;
};
struct RenderInfo
{
	Sint16 sprpriority;
	EnumRenderSprType type;
	DrawInfo drawinfo;
	RenderRectInfo rectinfo;
	PalFXInfo* palfxInfo;
	CCTexture2D* texture;

	AfterImage* afterimagecofig;
	Sint16 afterImageEffectCount;
};

#ifdef CONTROL_HIT_DEF_DEFINE
#undef CONTROL_HIT_DEF_DEFINE
#endif // CONTROL_HIT_DEF_DEFINE
#define CONTROL_HIT_DEF_DEFINE(type, name) type name

#ifdef CONTROL_HIT_DEF_DEFINE_INSTRUCTION
#undef CONTROL_HIT_DEF_DEFINE_INSTRUCTION
#endif // CONTROL_HIT_DEF_DEFINE
#define CONTROL_HIT_DEF_DEFINE_INSTRUCTION(name) OpElement* name


#define CONTROL_HIT_DEF_ATTRS \
	CONTROL_HIT_DEF_DEFINE(Uint32, attr);\
	CONTROL_HIT_DEF_DEFINE(Sint16, hitflag);\
	CONTROL_HIT_DEF_DEFINE(Sint16, guardflag);\
	CONTROL_HIT_DEF_DEFINE(Sint16, animtype);\
	CONTROL_HIT_DEF_DEFINE(Sint16, air_animtype);\
	CONTROL_HIT_DEF_DEFINE(Sint16, fall_animtype);\
	CONTROL_HIT_DEF_DEFINE(Sint16, priority);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(hit_damage);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(guard_damage);\
	CONTROL_HIT_DEF_DEFINE(Sint16, pause_time);\
	CONTROL_HIT_DEF_DEFINE(Sint16, shake_time);\
	CONTROL_HIT_DEF_DEFINE(Sint16, guard_pause_time);\
	CONTROL_HIT_DEF_DEFINE(Sint16, guard_shake_time);\
	CONTROL_HIT_DEF_DEFINE(Sint16, sparkno);\
	CONTROL_HIT_DEF_DEFINE(Sint16, guard_sparkno);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(sparkno_x);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(sparkno_y);\
	CONTROL_HIT_DEF_DEFINE(Sint16, ground_type);\
	CONTROL_HIT_DEF_DEFINE(Sint16, air_type);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(ground_slidetime);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(guard_slidetime);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(ground_hittime);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(guard_hittime);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(air_hittime);\
	CONTROL_HIT_DEF_DEFINE(Sint16, air_juggle);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(guard_ctrltime);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(airguard_ctrltime);\
	CONTROL_HIT_DEF_DEFINE(float, yaccel);\
	CONTROL_HIT_DEF_DEFINE(velocity, ground_velocity);\
	CONTROL_HIT_DEF_DEFINE(velocity, guard_velocity);\
	CONTROL_HIT_DEF_DEFINE(velocity, air_velocity);\
	CONTROL_HIT_DEF_DEFINE(velocity, airguard_velocity);\
	CONTROL_HIT_DEF_DEFINE(velocity, down_velocity);\
	CONTROL_HIT_DEF_DEFINE(Sint16, p1stateno);\
	CONTROL_HIT_DEF_DEFINE(Sint16, p2stateno);\
	CONTROL_HIT_DEF_DEFINE(Sint16, fall);\
	CONTROL_HIT_DEF_DEFINE(float, fall_xvelocity);\
	CONTROL_HIT_DEF_DEFINE(float, fall_yvelocity);\
	CONTROL_HIT_DEF_DEFINE(Sint16, fall_damage);\
	CONTROL_HIT_DEF_DEFINE(Sint16, getpower);\
	CONTROL_HIT_DEF_DEFINE(Sint16, guard_getpower);\
	CONTROL_HIT_DEF_DEFINE(Sint16, givepower );\
	CONTROL_HIT_DEF_DEFINE(Sint16, guard_givepower);\
	CONTROL_HIT_DEF_DEFINE(Sint16, guard_dist);\
	CONTROL_HIT_DEF_DEFINE(Sint16, p1sprpriority);\
	CONTROL_HIT_DEF_DEFINE(Sint16, p2sprpriority);\
	CONTROL_HIT_DEF_DEFINE_INSTRUCTION(palfx_time);\
	CONTROL_HIT_DEF_DEFINE(Sint16, numhits);



// HitDef 保存的值
struct CONTROLHITDEF
{
	CONTROL_HIT_DEF_ATTRS
	PalFXInfo palfxinfo;
};


struct PROJHITDEFINFO
{
	PROJHITDEFINFO()
	{
		bIsHited= false;
		nProjContact = 0;
		nProjGuarded = 0;
		nProjHit = 0;
		nProjID = 0;
	}
	// movehitpersist decide to reset these value
	bool bIsHited;
	Sint16 nProjContact;
	Sint16 nProjGuarded;
	Sint16 nProjHit;
	Sint32 nProjID;
};

struct HITDEFINFO
{
	HITDEFINFO()
	{
		bIsHitDefConfSet= false;
		CtrlHitDefConf = NULL;
		bIsHited= false;
		nPauseTime = 0;
		nMoveContact = 0;
		nMoveGuarded = 0;
		nMoveHit = 0;
		nHitCount = 0;
	}
	// hitdefpersist decide to reset hitinfo,it's meaning if last state's hitfinfo not hit somebody,next state still work
	bool bIsHitDefConfSet;
	CONTROLHITDEF* CtrlHitDefConf;

	// movehitpersist decide to reset these value
	bool bIsHited;
	Sint16 nPauseTime;
	Sint16 nMoveContact;
	Sint16 nMoveGuarded;
	Sint16 nMoveHit;
	Sint16 nHitCount;
};

struct GETHITINFO
{
	bool bIsHitDefConfSet;
	bool bIsProjHitSet;
	CONTROLHITDEF* CtrlHitDefConf;

	bool bIsShakedState;
	Sint16 nShakeTime;
	Sint16 nLieDownTime;
	Uint16 nGetHitedState;
	bool bIsGuarded;
	Sint16 nGetHitTime;
	Sint16 nFallCount;
	Sint16 nCombo;
	Sint16 nJuggle;
};


struct PLSTATE
{
	// control所属的state num
	char stNumber[MAX_STRING_LENGTH];
	char stInfo[MAX_STRING_LENGTH];
	Uint32 nType;
	TriggerStruct *triggers;
	Uint32 nHowManyTriggers;
	Uint32 nTriggersMemSize;

	Sint32 nPersistent;
	Sint32 nRunCount;
	bool bIgnorPause;

	// http://elecbyte.com/wiki/index.php/Category:State_Controllers
	// 里面有说明persistent和ignorehitpause是必须的字段，其他非必须，用map映射存储
	CtrlParamStruct* pContrlParma;
	Uint32 nParamCount;
	Uint32 nParamMemSize;

	// HitDef参数比较多，单独解析
	CONTROLHITDEF* pConHDdef;
	ProjectileInfo* pProjInfo;
	// AfterImage 
	AfterImage* pAfterImage;
	PalFXInfo* pPalFXinfo;
	ExplodInfo* pExplod;
	
};



struct PLSTATEDEF
{
	//recommend parameters
	Sint32 StateNumber;
	Uint8 type;
	Uint8 movetype;
	Uint8 physics;
	OpElement * nAnim;
	//optional param
	XYVALUE Velset;
	Sint16 bCtrl;
	Sint32 nPoweradd;
	Sint32 nJuggle;
	bool bFacep2;
	///Some  flags
	bool bHitdefpersist;
	bool bMovehitpersist;
	bool bHitcountpersist;
	//////////////////////
	Sint8 nSprpriority;
	Uint16 nHowManyState;
	PLSTATE* lpState;

};


typedef struct ClsnRECT
{
	Sint32 x,y;
	Sint32 w, h;

}ClsnRECT;

//Element Strcut to save one Elment of an Action Block
struct Element
{
	Sint16 nGroupNumber;
	Sint16 nImageNumber;
	Sint16 x;
	Sint16 y;
	// take -1 as forever
	Sint16 nDuringTime;
	SDL_RendererFlip FlipFlags;
	TransType TransTypes;
	Uint16 srcAlpha;
	Uint16 desAlpha;
	ClsnRECT *pClns1Data;
	Sint16 nNumberOfClsn1;
	ClsnRECT *pClns2Data;
	Sint16 nNumberOfClsn2;
};

//Action Element to hold one Action Block with its Elements
struct ActionElement
{
	Sint16 nActionNumber;
	// 当前帧数据
	Element* AnimationElement;
	// 总帧
	Sint16 nNumberOfElements;
	Sint16 nMemSize;
	Sint16 loopStart;
	// 动画完成时间
	Sint16 nCompletAnimTime;
};


//Action Element to hold one Action Block with its Elements
struct ActionContainer
{
	ActionElement* AnimationElement;
	// 总帧
	Sint16 nNumberOfAct;
	Sint16 nMemSize;
};

struct ActionMoveInfo
{
	// use for all except normal anim
	bool isPosSeted;
	bool bRightFacing;
	// use for proj
	bool bVRightFacing;
	Sint32 nBindtime;
	float ScreenPosX, ScreenPosY;
	float nPosX, nPosY;
	float velX, velY;
};

struct ProjHitInfo
{
	CONTROLHITDEF* pHitDefInfo;
	bool isHited;
};


enum BG_TYPE
{
	BG_TYPE_NORMAL = 0,
	BG_TYPE_ANIM,
	BG_TYPE_PARALLAX,
	BG_END,
};
// BG
struct BG_ELEMENT 
{
	BG_TYPE type;
	Uint32 GroubNumber;
	Uint32 ImageNumber;
	Uint32 nAnimNo;
	Uint16 nID;
	Uint16 nLayerNo;
	Sint16 nStartX;
	Sint16 nStartY;
	float fDeltaX;
	float fDeltaY;
	Uint16 trans;
	bool bMask;
	Uint16 nTileX;
	Uint16 nTileY;
	Uint16 nTileSpacingX;
	Uint16 nTileSpacingY;
	Sint16 nWindowX;
	Sint16 nWindowY;
	Sint16 nWindowW;
	Sint16 nWindowH;
	Sint16 nWindowDeltaX;
	Sint16 nWindowDeltaY;
};

struct BG_DEF
{
	char spr[MAX_PATH];
	BG_ELEMENT* elements;
	Uint16 elementSize;
	Uint16 nMemSize;
};

enum BGCTRL_TYPE
{
	BGCTRL_TYPE_null = 0,
	BGCTRL_TYPE_Visible,
	BGCTRL_TYPE_Enabled,
	BGCTRL_TYPE_VelSet,
	BGCTRL_TYPE_VelAdd,
	BGCTRL_TYPE_PosSet,
	BGCTRL_TYPE_PosAdd,
	BGCTRL_TYPE_Anim,
	BGCTRL_TYPE_SinX,
	BGCTRL_TYPE_SinY,
	BGCTRL_TYPE_End,
};
struct BGCTRl_ELEMENT
{
	Uint8 type;
	Sint16 startTime;
	Sint16 endTime;
	Sint16 loopTime;
	Sint16 CtrlID[10];
	Sint16 value;
	Sint16 x;
	Sint16 y;
};
struct BGCTRl_DEF
{
	char name[MAX_PATH];
	Sint16 nLoopTime;
	Sint16 CtrlID[10];
	BGCTRl_ELEMENT* elements;
	Uint16 nCtrlSize;
	Uint16 nMemSize;
};
struct BGCTRl_DEF_CONTAINER
{
	BGCTRl_DEF *elements;
	Uint16 nCtrlDefSize;
	Uint16 nMemSize;
};

struct ActionForPlay
{
	ActionForPlay()
	{
		Anim = NULL;
		nAnim = -1;
	}
	ActionElement *Anim;    
	Sint32 nCurrentImage;
	Sint32 nCurrentImageTime;
	Sint32 nCurrTime;
	Sint32 nCurrTimeInAnim;
	Sint32 nAnim;

	EnumAnimType type;
	ActType acttype;
	// pal is effected by palFX
	bool bOwnpal;
	Sint32 nRemovetime;

	void* actData;
	ActionMoveInfo* moveinfo;
	ProjHitInfo* projinfo;
	BG_ELEMENT* bgInfo;
};


struct SelectRoleInfo
{
	char name[MAX_STRING_LENGTH];
	char stagename[MAX_STRING_LENGTH];
	bool includestage;
	char musicName[MAX_STRING_LENGTH];
	Uint32 order;

	bool isPhotoLoaded;
	SFFSPRITE headphoto;
	SFFSPRITE photo;
};
struct SelectRoleList
{
	SelectRoleInfo* rolelist;
	Uint32 roleCount;
	Uint32 roleMemSize;
};
#endif
