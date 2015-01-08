/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "player.h"
#include "GameTimer.h"
#include "game.h"
#include "StageManager.h"
#include "config/ConfigManager.h"
#include "driver/SDLManager.h"
#include "driver/Input.h"
#include "tool.h"
#include "driver/FontManager.h"
#include "engine.h"

/*
================================================================================
================================================================================
*/

Uint32 CPlayer::playerCount = 0;
CPlayer::CPlayer()
	:lpCurrStatedef(NULL)
	,m_pAlloc(NULL)
	,m_ControllerExec(NULL)
	,m_IsLogCommand(false)
{ 
	playerCount++;
	m_playerUid = playerCount;
}

CPlayer::~CPlayer()
{
	CC_SAFE_DELETE(m_pVMachine);
	CC_SAFE_DELETE(m_ControllerExec);
	if (m_pAlloc)
	{
		m_pAlloc->FreeAllocater();
	}
	m_Children->removeAllObjects();
	CC_SAFE_DELETE(m_Children);
}

void CPlayer::Destroy()
{
}


void CPlayer::Init(Uint32 id, CPlayer* enimy)
{
	m_pVMachine= new CVirtualMachine;
	m_pVMachine->SetPlayers(this, enimy);

	m_Parent = NULL;
	Sint32 groundPosY = CConfigManager::GetInstance()->GetInt("PlayerList.PlayerGoundPosY");
	this->SetGroundValue(groundPosY);

	m_Evn_color.time = 0;

	m_propIsSuperPause = false;
	m_PalFXinfo = NULL;
	m_recordStatus = COMMAND_RECORD_READY;
	m_RecordList = NULL;
	m_RecordCount = 0;

	m_AfterImageStack.config = NULL;
	SDL_memset(&m_AfterImageStack, 0, sizeof(m_AfterImageStack));
	nTargetBindTime = 0;
	nBindTargetID = -1;
	bIsInP2Anim = false;
	bIsInP2State = false;
	nLastStateNo = 0;
	m_propID = id;
	m_p2 = enimy;
	m_ControllerExec = new CControllerExecuter;
	m_ControllerExec->SetPlayer(this, m_p2);
	m_Children = new CArray;
	bCtrl = 1;
	m_KeyIndex = 0;

	m_bDrawClsn = eDRAW_RECT_TYPE_NONE;
	bRightFaced=true;
	bAlive=true;
	bHitDefPresit=false;
	bHitCounterPresit=false;
	bMoveHitPresit=false;
	nStateTime=-1;
	nStateType=0;
	nPhysic=0;
	nMoveType=0;
	nSprPrio = 0;
	x=y=0;
	xVel=0;
	yVel=0;
	m_bIsDrawBack = false;
	m_autoGuard = false;
	m_Config = NULL;
	bPush = true;
	bAssertNoWalk = false;

	m_propMaxPower = 3000;
	m_propPower = m_propMaxPower;
	m_propAILevel = 0;
	m_propLife = 0;
	m_propWidthBack = 0;
	m_propWidthFront = 0;
	m_propNotHitByTime = -1;
	m_propHitByTime = -1;

	m_SuperAnim = NULL;
	m_Spark = NULL;
	m_Anim = NULL;
	m_Explod.clear();
	m_Projhitanim = NULL;
	m_Proj.clear();

	m_ComboTexture = NULL;
	//init var
	for (int i =0;i<60;i++)
	{
		m_vectorVar[i] = 0;
	}
	for (int i =0;i<40;i++)
	{
		m_vectorFVar[i] = 0;
	}
	for (int i =0;i<4;i++)
	{
		m_vectorSysVar[i] = 0;
	}
	for (int i =0;i<4;i++)
	{
		m_vectorSysFVar[i] = 0;
	}
}

/*
================================================================================
================================================================================
*/

void CPlayer::UpdatePlayerAnimInfo()
{
	ActionForPlay* act = m_Anim;
	CAssert(act->Anim!=NULL, "act's anim is null");

	Sint32 nGroupNumber =act->Anim->AnimationElement[act->nCurrentImage].nGroupNumber;
	Sint32 nImageNumber = act->Anim->AnimationElement[act->nCurrentImage].nImageNumber;
	SDL_RendererFlip FlipFlags = act->Anim->AnimationElement[act->nCurrentImage].FlipFlags;
	TransType sprTransType = act->Anim->AnimationElement[act->nCurrentImage].TransTypes;
	Uint16 srcAlpha = act->Anim->AnimationElement[act->nCurrentImage].srcAlpha;
	Uint16 desAlpha = act->Anim->AnimationElement[act->nCurrentImage].desAlpha;
	// spr delta pos
	Sint32 DeltaX = act->Anim->AnimationElement[act->nCurrentImage].x;
	Sint32 DeltaY = act->Anim->AnimationElement[act->nCurrentImage].y;

	SFFSPRITE *spr = NULL;
	if (act->type == AnimPlayer)
	{
		spr =m_Config->GetSff()->FindSprite(nGroupNumber,nImageNumber);
	}else if(act->type == AnimFightFX)
	{
		spr =CConfigManager::GetInstance()->GetSystemConfig()->GetFightConfig()->GetFXSff()->FindSprite(nGroupNumber,nImageNumber);
	}
	// continue but not draw player
	/*if(spr==NULL)
		return;*/

	PaletteFormat* sharePallet = NULL;
	if (act->acttype == ActAnim)
	{
		sharePallet = m_Config->GetSff()->GetPallet(this->m_propPal);
	}else{
		sharePallet = m_Config->GetSff()->GetPallet(3);
	}

	Sint32 GameWidth =Common_GetDesiginWidth();
	Sint32 GameHeight = Common_GetDesiginHeight();
	// deal with camera
	float verticalfollow = CStageManager::GetInstance()->GetFloat("Camera.verticalfollow");
	Sint32 screenPosX = CStageManager::GetInstance()->GetScreenPosX(x + 0.5*GameWidth, 1);
	Sint32 screenPosY = CStageManager::GetInstance()->GetScreenPosY(y + nGround, verticalfollow);
	if (bRightFaced)
	{
		m_curDrawInfo.nScreenPosX = screenPosX+DeltaX;
		m_curDrawInfo.nScreenPosY = screenPosY+DeltaY;
	}else{
		m_curDrawInfo.nScreenPosX = screenPosX-DeltaX;
		m_curDrawInfo.nScreenPosY = screenPosY+DeltaY;
	}

	m_curDrawInfo.spr = spr;
	m_curDrawInfo.nPosX = screenPosX;
	m_curDrawInfo.nPosY = screenPosY;
	m_curDrawInfo.pal = sharePallet;
	m_curDrawInfo.bDrawBack = m_bIsDrawBack;
	m_curDrawInfo.transMode = sprTransType;
	m_curDrawInfo.srcAlpha = srcAlpha;
	m_curDrawInfo.desAlpha = desAlpha;
	if (bRightFaced)
	{
		// flip
		m_curDrawInfo.flip = FlipFlags;
	}
	else
	{
		m_curDrawInfo.flip = (SDL_RendererFlip)(FlipFlags ^ SDL_FLIP_HORIZONTAL);
	}
}

void CPlayer::DrawPlayerAct(Sint32 priority)
{
	ActionForPlay* act = m_Anim;
	CAssert(act->Anim!=NULL, "act's anim is null");
	Sint32 pri = priority;
	if (pri == MAX_INT32)
	{
		pri = this->nSprPrio;
	}
	CSDLManager::GetInstance()->GetVideoSystem()->NormalBlt(m_curDrawInfo, m_PalFXinfo, pri);
	StoreForAfterImage(m_curDrawInfo);

	Sint32 back = this->GetPlayerBack();
	Sint32 front = this->GetPlayerFront();
	Sint32 playerHeight = m_Config->GetInt("size.height");
	if (m_bDrawClsn == eDRAW_RECT_TYPE_NONE)
	{
		return;
	}
	BlitClsn(m_Anim, m_curDrawInfo.nPosX,m_curDrawInfo.nPosY);
	if (bRightFaced)
	{
		CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(255,0, 0, m_curDrawInfo.nPosX, m_curDrawInfo.nPosY,  front, 2, this->m_bDrawClsn);//画矩形 
		CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(255,0, 0, m_curDrawInfo.nPosX-back, m_curDrawInfo.nPosY,  back, 2, this->m_bDrawClsn);//画矩形
		CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(0, 255, 0, m_curDrawInfo.nPosX, m_curDrawInfo.nPosY-playerHeight,  2, playerHeight, this->m_bDrawClsn);//画矩形
	}
	else
	{
		CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(255,0, 0, m_curDrawInfo.nPosX-front, m_curDrawInfo.nPosY,  front, 2, this->m_bDrawClsn);//画矩形 
		CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(255,0, 0, m_curDrawInfo.nPosX, m_curDrawInfo.nPosY,  back, 2, this->m_bDrawClsn);//画矩形 
		CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(0, 255, 0, m_curDrawInfo.nPosX, m_curDrawInfo.nPosY-playerHeight,  2, playerHeight, this->m_bDrawClsn);//画矩形
	}
}


void CPlayer::UpdateProjMove(ActionForPlay* act)
{
	if (act->Anim ==NULL)
	{
		return;
	}
	ProjectileInfo* actdata = (ProjectileInfo*)act->actData;
	if (act->moveinfo->isPosSeted)
	{
		if (!m_propIsSuperPause)
		{
			act->moveinfo->ScreenPosX += act->moveinfo->velX;
			act->moveinfo->ScreenPosY += act->moveinfo->velY;
			act->moveinfo->nPosX += act->moveinfo->velX;
			act->moveinfo->nPosY += act->moveinfo->velY;
			act->moveinfo->velX += actdata->accelx;
			act->moveinfo->velY += actdata->accely;
		}
		int h = Common_GetDesiginHeight();
		int w = Common_GetDesiginWidth();
		if (act->moveinfo->ScreenPosX < - actdata->nProjedgebound || act->moveinfo->ScreenPosX - w > actdata->nProjedgebound)
		{
			act->Anim = NULL;
		}else if (act->moveinfo->ScreenPosY < - actdata->nProjheightbound || act->moveinfo->ScreenPosY - h > actdata->nProjheightbound)
		{
			act->Anim = NULL;
		}
		return;
	}
	// set pos
	// spr delta pos
	Sint32 DeltaX = act->Anim->AnimationElement[act->nCurrentImage].x;
	Sint32 DeltaY = act->Anim->AnimationElement[act->nCurrentImage].y;
	if (act->moveinfo->bRightFacing)
	{
		switch (actdata->postype)
		{
		case eEnumPosType_P1:
			act->moveinfo->nPosX = m_curDrawInfo.nPosX + actdata->posx;
			act->moveinfo->nPosY =  m_curDrawInfo.nPosY + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_P2:
			act->moveinfo->nPosX = m_p2->m_curDrawInfo.nPosX + actdata->posx;
			act->moveinfo->nPosY =  m_p2->m_curDrawInfo.nPosY + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Front:
			act->moveinfo->nPosX = Common_GetDesiginWidth()*0.5 + actdata->posx;
			act->moveinfo->nPosY =  0 + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Left:
			act->moveinfo->nPosX = 0 + actdata->posx;
			act->moveinfo->nPosY =  0 + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Back:
			act->moveinfo->nPosX = Common_GetDesiginWidth()*0.5 - actdata->posx;
			act->moveinfo->nPosY = 0 + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Right:
			act->moveinfo->nPosX = Common_GetDesiginWidth() - actdata->posx;
			act->moveinfo->nPosY = 0 + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		default:
			break;
		}
	}// end bfaced
	else
	{
		// same dir left
		switch (actdata->postype)
		{
		case eEnumPosType_P1:
			// face right
			act->moveinfo->nPosX = m_curDrawInfo.nPosX - actdata->posx;
			act->moveinfo->nPosY =  m_curDrawInfo.nPosY + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_P2:
			// face left
			act->moveinfo->nPosX = m_p2->m_curDrawInfo.nPosX - actdata->posx;
			act->moveinfo->nPosY =  m_p2->m_curDrawInfo.nPosY + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Front:
			// face left
			act->moveinfo->nPosX = Common_GetDesiginWidth()*0.5 - actdata->posx;
			act->moveinfo->nPosY =  0 + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Left:
			// face left
			act->moveinfo->nPosX = 0 + actdata->posx;
			act->moveinfo->nPosY =  0 + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Back:
			// face left
			act->moveinfo->nPosX = Common_GetDesiginWidth()*0.5 + actdata->posx;
			act->moveinfo->nPosY = 0 + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;// face left
			break;
		case eEnumPosType_Right:
			// face left
			act->moveinfo->nPosX = Common_GetDesiginWidth() - actdata->posx;
			act->moveinfo->nPosY = 0 + actdata->posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		default:
			break;
		}
	}

	act->moveinfo->isPosSeted = true;
	// set speed
	act->moveinfo->velY = actdata->vely;
	if (act->moveinfo->bVRightFacing)
	{
		act->moveinfo->velX = actdata->velx;
	}
	else
	{
		act->moveinfo->velX = -actdata->velx;
	}// end set vel
}
void CPlayer::UpdateExplodMove(ActionForPlay* act)
{
	if (act->Anim ==NULL)
	{
		return;
	}
	ExplodInfo* actdata = (ExplodInfo*)act->actData;
	// spr delta pos
	Sint32 DeltaX = act->Anim->AnimationElement[act->nCurrentImage].x;
	Sint32 DeltaY = act->Anim->AnimationElement[act->nCurrentImage].y;
	if (act->moveinfo->isPosSeted)
	{
		if (!m_propIsSuperPause&&(actdata->bignorehitpause||!IsShake()&&!IsPause()))
		{
			act->moveinfo->ScreenPosX += act->moveinfo->velX;
			act->moveinfo->ScreenPosY += act->moveinfo->velY;
			act->moveinfo->nPosX += act->moveinfo->velX;
			act->moveinfo->nPosY += act->moveinfo->velY;
			act->moveinfo->velX += actdata->accelx;
			act->moveinfo->velY += actdata->accely;
		}
		return;
	}

	float posx = m_pVMachine->Execute(actdata->posx);
	float posy = m_pVMachine->Execute(actdata->posy);
	if (act->moveinfo->bRightFacing)
	{
		// same dir
		switch (actdata->postype)
		{
		case eEnumPosType_P1:
			act->moveinfo->nPosX = m_curDrawInfo.nPosX + posx;
			act->moveinfo->nPosY =  m_curDrawInfo.nPosY + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_P2:
			act->moveinfo->nPosX = m_p2->m_curDrawInfo.nPosX + posx;
			act->moveinfo->nPosY =  m_p2->m_curDrawInfo.nPosY + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Front:
			act->moveinfo->nPosX = Common_GetDesiginWidth()*0.5 + posx;
			act->moveinfo->nPosY =  0 + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Left:
			act->moveinfo->nPosX = 0 + posx;
			act->moveinfo->nPosY =  0 + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Back:
			act->moveinfo->nPosX = Common_GetDesiginWidth()*0.5 + posx;
			act->moveinfo->nPosY = 0 + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Right:
			act->moveinfo->nPosX = Common_GetDesiginWidth() + posx;
			act->moveinfo->nPosY = 0 + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX + DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		default:
			break;
		}
	}else{
		// diff dir left
		switch (actdata->postype)
		{
		case eEnumPosType_P1:
			// face right
			act->moveinfo->nPosX = m_curDrawInfo.nPosX - posx;
			act->moveinfo->nPosY =  m_curDrawInfo.nPosY + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_P2:
			// face left
			act->moveinfo->nPosX = m_p2->m_curDrawInfo.nPosX - posx;
			act->moveinfo->nPosY =  m_p2->m_curDrawInfo.nPosY + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Front:
			// face left
			act->moveinfo->nPosX = Common_GetDesiginWidth()*0.5 - posx;
			act->moveinfo->nPosY =  0 + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Left:
			// face left
			act->moveinfo->nPosX = 0 - posx;
			act->moveinfo->nPosY =  0 + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		case eEnumPosType_Back:
			// face left
			act->moveinfo->nPosX = Common_GetDesiginWidth()*0.5 - posx;
			act->moveinfo->nPosY = 0 + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;// face left
			break;
		case eEnumPosType_Right:
			// face left
			act->moveinfo->nPosX = Common_GetDesiginWidth() - posx;
			act->moveinfo->nPosY = 0 + posy;
			act->moveinfo->ScreenPosX = act->moveinfo->nPosX - DeltaX;
			act->moveinfo->ScreenPosY = act->moveinfo->nPosY + DeltaY;
			break;
		default:
			break;
		}
	}// end bFaceing

	if (actdata->nRandomX&&actdata->nRandomY)
	{
		float rx = CCRANDOM_MINUS1_1()*0.5*actdata->nRandomX;
		float ry = CCRANDOM_MINUS1_1()*0.5*actdata->nRandomY;
		act->moveinfo->nPosX += rx;
		act->moveinfo->ScreenPosX+= rx;
		act->moveinfo->nPosY += ry;
		act->moveinfo->ScreenPosY += ry;
	}
	if(m_propIsSuperPause||(!actdata->bignorehitpause && (IsShake()||IsPause()) ) )
	{
		return;
	}
	if (act->moveinfo->nBindtime>0)
	{
		act->moveinfo->nBindtime --;
	}else if (act->moveinfo->nBindtime == 0 )
	{
		act->moveinfo->isPosSeted = true;
		act->moveinfo->velY = actdata->vely;
		if (act->moveinfo->bVRightFacing)
		{
			act->moveinfo->velX = actdata->velx;
		}
		else
		{
			act->moveinfo->velX = -actdata->velx;
		}
	}else{
		//forever
	}
}

void CPlayer::DrawAct(ActionForPlay* act)
{
	if (act==NULL || act->Anim ==NULL)
	{
		return;
	}
	CAssert(act->acttype != ActAnim, "please use DrawPlayerAct");
	Sint32 nGroupNumber =act->Anim->AnimationElement[act->nCurrentImage].nGroupNumber;
	Sint32 nImageNumber = act->Anim->AnimationElement[act->nCurrentImage].nImageNumber;
	SDL_RendererFlip FlipFlags = act->Anim->AnimationElement[act->nCurrentImage].FlipFlags;
	TransType sprTransType = act->Anim->AnimationElement[act->nCurrentImage].TransTypes;
	Uint16 srcAlpha = act->Anim->AnimationElement[act->nCurrentImage].srcAlpha;
	Uint16 desAlpha = act->Anim->AnimationElement[act->nCurrentImage].desAlpha;
	// spr delta pos
	Sint32 DeltaX = act->Anim->AnimationElement[act->nCurrentImage].x;
	Sint32 DeltaY = act->Anim->AnimationElement[act->nCurrentImage].y;
	
	SFFSPRITE *spr = NULL;
	if (act->type == AnimPlayer)
	{
		spr =m_Config->GetSff()->FindSprite(nGroupNumber,nImageNumber);
	}else if(act->type == AnimFightFX)
	{
		spr =CConfigManager::GetInstance()->GetSystemConfig()->GetFightConfig()->GetFXSff()->FindSprite(nGroupNumber,nImageNumber);
	}
	if(spr==NULL)
		return;

	PaletteFormat* sharePallet = NULL;
	sharePallet = m_Config->GetSff()->GetPallet(3);

	DrawInfo info;
	info.spr = spr;
	info.pal = sharePallet;
	info.bDrawBack = m_bIsDrawBack;
	info.transMode = sprTransType;
	info.srcAlpha = srcAlpha;
	info.desAlpha = desAlpha;
	info.nScaleX = m_Config->GetFloat("Size.effect.xscale");
	info.nScaleY = m_Config->GetFloat("Size.effect.yscale");

	PalFXInfo* curFX = NULL;
	if (!act->bOwnpal)
	{
		curFX = m_PalFXinfo;
	}

	if (act->moveinfo->bRightFacing)
	{
		info.flip = FlipFlags;
	}
	else
	{
		info.flip = (SDL_RendererFlip)(FlipFlags ^ SDL_FLIP_HORIZONTAL);
	}

	Sint32 sprpriority = 0;
	// set pos
	if (act->acttype == ActExplod)
	{
		ExplodInfo* actdata = (ExplodInfo*)act->actData;
		info.nScaleX *= actdata->scalex;
		info.nScaleY *= actdata->scaley;
		if (actdata->trans!=eTransTypeNone)
		{
			info.transMode = actdata->trans;
			info.srcAlpha = actdata->srcalpha;
			info.desAlpha = actdata->desalpha;
		}
		info.nScreenPosX = act->moveinfo->ScreenPosX;
		info.nScreenPosY = act->moveinfo->ScreenPosY;
		info.nPosX = act->moveinfo->nPosX;
		info.nPosY = act->moveinfo->nPosY;
		sprpriority = actdata->nSprpriority;
		if (actdata->bOnTop)
		{
			sprpriority = SPR_PRIORITY_TOP;
		}
	}else if (act->acttype == ActProj)
	{
		ProjectileInfo* actdata = (ProjectileInfo*)act->actData;
		info.nScaleX *= actdata->scalex;
		info.nScaleY *= actdata->scaley;
		info.nPosX = act->moveinfo->nPosX;
		info.nPosY = act->moveinfo->nPosY;
		info.nScreenPosX = act->moveinfo->ScreenPosX;
		info.nScreenPosY = act->moveinfo->ScreenPosY;
		sprpriority = actdata->nSprpriority;
	}else if (act->acttype == ActSuperAnim)
	{
		info.nPosX = act->moveinfo->nPosX;
		info.nPosY = act->moveinfo->nPosY;
		if (act->moveinfo->bRightFacing)
		{
			info.nScreenPosX = info.nPosX + DeltaX;
			info.nScreenPosY = info.nPosY + DeltaY;
		}
		else
		{
			info.nScreenPosX = info.nPosX-DeltaX;
			info.nScreenPosY = info.nPosY+DeltaY;
		}
		sprpriority = SPR_PRIORITY_SUPER_TOP+2;
	}else{// end spark
		info.nPosX = act->moveinfo->nPosX;
		info.nPosY = act->moveinfo->nPosY;
		if (act->moveinfo->bRightFacing)
		{
			info.nScreenPosX = info.nPosX + DeltaX;
			info.nScreenPosY = info.nPosY + DeltaY;
		}
		else
		{
			info.nScreenPosX = info.nPosX-DeltaX;
			info.nScreenPosY = info.nPosY+DeltaY;
		}
		sprpriority = SPR_PRIORITY_TOP;
	}// end set pos

	CSDLManager::GetInstance()->GetVideoSystem()->NormalBlt(info, curFX, sprpriority);

	CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(0,0, 255, act->moveinfo->nPosX-4, act->moveinfo->nPosY-4,  8, 8, this->m_bDrawClsn, 1.0, 0);//画矩形
}

void CPlayer::StoreForAfterImage(DrawInfo& info)
{
	// afterimage
	if (m_AfterImageStack.config != NULL)
	{
		// if timegap is zero, pass
		if (m_AfterImageStack.duringTime>=0&&m_AfterImageStack.config->timegap&&(m_AfterImageStack.duringTime%m_AfterImageStack.config->timegap == 0))
		{
			// still in during time, push after image
			m_AfterImageStack.stack[m_AfterImageStack.top] = info;
			m_AfterImageStack.top++;
			if (m_AfterImageStack.top<=m_AfterImageStack.bottom)
			{
				m_AfterImageStack.bottom++;
			}else{
				if (m_AfterImageStack.top - m_AfterImageStack.bottom >= m_AfterImageStack.config->length)
				{
					m_AfterImageStack.bottom ++;
				}
			}
		}
		m_AfterImageStack.top = m_AfterImageStack.top % MaxAfterImageSize;
		m_AfterImageStack.bottom = m_AfterImageStack.bottom % MaxAfterImageSize;
		m_AfterImageStack.duringTime --;
		if (m_AfterImageStack.duringTime==0)
		{
			// record the end of during time
			m_AfterImageStack.EndTime = CGameTimer::GetInstance()->GetGameTime();
		}
	}
}

void CPlayer::DrawPlayer()
{
	if (m_Evn_color.time>0)
	{
		int w = Common_GetDesiginWidth();
		int h = Common_GetDesiginHeight();
		CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(m_Evn_color.color_b, m_Evn_color.color_g, m_Evn_color.color_b, 0, 0, w, h, eDRAW_RECT_TYPE_FILLED, 1, 0, m_Evn_color.priority);
	}
	if (m_propIsSuperPause)
	{
		DrawPlayerAct(SPR_PRIORITY_SUPER_TOP+1);
		UpdateAnim(m_SuperAnim);
		DrawAct(m_SuperAnim);
	}else{
		DrawPlayerAct();
	}

	for(std::vector<ActionForPlay*>::iterator it=m_Explod.begin(); it!=m_Explod.end(); it++)  
	{ 
		DrawAct(*it);
	}

	// don't pause when hit pause
	for(std::vector<ActionForPlay*>::iterator it=m_Proj.begin(); it!=m_Proj.end(); it++)  
	{ 
		ActionForPlay* act = *it;
		DrawAct(*it);
		// draw clsn
		BlitClsn(*it, act->moveinfo->nPosX, act->moveinfo->nPosY);
	}

	DrawAct(m_Spark);

	if (m_ComboTexture)
	{
		m_ComboShowTicks ++;
		if (m_ComboShowTicks >60)
		{
			CC_SAFE_RELEASE_NULL(m_ComboTexture);
			return;
		}
		DrawInfo info;
		info.nScreenPosX = 560;
		info.nScreenPosY = 300;
		info.nScaleX = 2;
		info.nScaleY = 2;
		CSDLManager::GetInstance()->GetVideoSystem()->DrawTexture(info, m_ComboTexture, SPR_PRIORITY_TOP);
	}

	// draw afterimge in back
	// how many buffer should be draw!
	if (m_AfterImageStack.config !=NULL)
	{
		Sint32 bufferCount = 0;
		if (m_AfterImageStack.duringTime<0)
		{
			bufferCount = m_AfterImageStack.config->time - CGameTimer::GetInstance()->GetGameTime() + m_AfterImageStack.EndTime;
		}else{
			bufferCount = m_AfterImageStack.config->time;
		}

		if (bufferCount <= 0)
		{
			// end the after image
			m_AfterImageStack.config = NULL;
		}else{

			int tmpBottom = m_AfterImageStack.bottom;
			if (m_AfterImageStack.top < tmpBottom)
			{
				tmpBottom = tmpBottom - MaxAfterImageSize;
			}
			int startPos = Max(m_AfterImageStack.top - bufferCount, tmpBottom);

			int effectcount = m_AfterImageStack.top - startPos -1;
			while (startPos < m_AfterImageStack.top)
			{
				// draw first 1+framegap, 1+2*framegap
				if (startPos % m_AfterImageStack.config->framegap == 0)
				{
					int curDrawPos = (startPos + MaxAfterImageSize)%MaxAfterImageSize;
					CSDLManager::GetInstance()->GetVideoSystem()->BltAfterImage(m_AfterImageStack, curDrawPos, effectcount);
				}
				startPos++;
				effectcount--;
			}
		}
	}
}



void CPlayer::BlitClsn(ActionForPlay* act, Sint32 x, Sint32 y)
{
	if (this->m_bDrawClsn == eDRAW_RECT_TYPE_NONE)
	{
		return;
	}
	if (act->Anim == NULL)
	{
		return;
	}
	int w,h;
	u16 clsn2Count = act->Anim->AnimationElement[act->nCurrentImage].nNumberOfClsn2;
	ClsnRECT* clsn2 = act->Anim->AnimationElement[act->nCurrentImage].pClns2Data;
	for (int i=0;i<clsn2Count;i++)
	{
		w = clsn2[i].w ;
		h = clsn2[i].h ;
		ClsnRECT rect =  clsn2[i];
		if (!bRightFaced)
		{
			rect = Common_GetRevertClsn(clsn2[i]);
		}
		CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(255,255, 255, x + rect.x, y+rect.y,  w, h, this->m_bDrawClsn, 0.5, 0.5);//画矩形 
	}
	// 绘制碰撞矩形
	u16 clsn1Count = act->Anim->AnimationElement[act->nCurrentImage].nNumberOfClsn1;
	ClsnRECT* clsn1 = act->Anim->AnimationElement[act->nCurrentImage].pClns1Data;
	for (int i=0;i<clsn1Count;i++)
	{
		w = clsn1[i].w;
		h = clsn1[i].h;
		ClsnRECT rect =  clsn1[i];
		if (!bRightFaced)
		{
			rect = Common_GetRevertClsn(clsn1[i]);
		}
		CSDLManager::GetInstance()->GetVideoSystem()->DrawRect(255,0, 0, x + rect.x, y+rect.y,  w, h, this->m_bDrawClsn, 0.5, 0.5);//画矩形 
	}
}

void CPlayer::UpdateAnim(ActionForPlay* act)
{
	if (act == NULL || act->Anim ==NULL)
	{
		return;
	}
	//is the current image in time? && do not check if during time of the current image is -1
	Sint32 duringTime = act->Anim->AnimationElement[act->nCurrentImage].nDuringTime;
	act->nCurrentImageTime++;
	act->nCurrTime++;
	act->nCurrTimeInAnim++;
	if (act->nRemovetime>0)
	{
		act->nRemovetime --;
	}
	if(duringTime==-1)
	{
		// loop forever
		return;
	}
	if (act->nCurrentImageTime>duringTime)
	{
		act->nCurrentImage++;
		// record curtime when first enter the image
		act->nCurrentImageTime = CUR_IMAGE_TIME_START+1;
		if(act->nCurrentImage >= act->Anim->nNumberOfElements)
		{
			act->nCurrTime=CUR_TIME_START + 1;
			act->nCurrentImage=CUR_IMAGE_INDEX_START;
			if (act->nRemovetime == -1)
			{
				//if we have a loop start go to it
				if(act->Anim->loopStart!=-1) 
				{
					//now check on which elemt the time offset is  
					for (int i=0;i<act->Anim->loopStart;i++)
					{
						act->nCurrTime+=act->Anim->AnimationElement[i].nDuringTime;
					}
					act->nCurrentImage=act->Anim->loopStart;
				}
			}else if (act->nRemovetime == -2||act->nRemovetime == 0){ 
				act->Anim = NULL;
				act->nAnim = -1;
				/*if (act->acttype == ActExplod)
				{
					PrintMessage("%p", act);
				}*/
			}
		}
	}
	//PrintMessage("%d, %d %d", Anim->nActionNumber,Anim->nCurrentImage+1, Anim->nCurrTime);
}

bool CPlayer::IsPause()
{
	if (m_HitInfo.bIsHited)
	{
		return m_HitInfo.nPauseTime >0;
	}else
	{
		return false;
	}
}

bool CPlayer::IsShake()
{
	if (m_GetHitInfo.bIsShakedState)
	{
		return m_GetHitInfo.nShakeTime >0;
	}else
	{
		return false;
	}
}


/*
================================================================================
================================================================================
*/

bool CPlayer::IsCommandInput(const char* name)
{
	for (Uint16 i=0;i<m_InputCommandCount;i++)
	{
		if(SDL_strcmp(name, m_CurrCommandName[i]) == 0) return true;
	}
	return false;
}

void CPlayer::AddCommand(const char* name)
{
	SDL_strlcpy((char*)m_CurrCommandName[m_InputCommandCount], name, MAX_ALLOWED_COMMANDSTR_COUNT);
	m_InputCommandCount++;
	PrintMessage("<AddCommand>time:%5d, %s, commandcount %d ",CGameTimer::GetInstance()->GetGameTime(), name, m_InputCommandCount);
}
void CPlayer::RecordCommand()
{
	m_recordStatus = COMMAND_RECORD_START;
	if (m_RecordList == NULL)
	{
		m_RecordList = (Uint16*)m_pAlloc->Alloc(MAX_COMMAND_RECORD_COUNT*sizeof(Uint16));
	}
	m_RecordCount = 0;
}
void CPlayer::RecordCommandEnd()
{
	m_recordStatus = COMMAND_RECORD_READY;
}
void CPlayer::SaveRecord()
{
	if (m_RecordList == NULL)
	{
		return;
	}
	int i,j;
	char str[MAX_PATH];
	SDL_RWops* file = SDL_RWFromFile("record.txt", "wb");
	SDL_itoa(m_RecordCount, str, 10);
	int len = SDL_strlen(str);
	str[len] = '\r';
	str[len+1] = '\n';
	SDL_RWwrite(file, str, sizeof(Uint8), len+2);
	const char* commandKey = "UDLRABCXYZS";
	for (i=0;i<m_RecordCount;i++)
	{
		for (j=KEY_UP;j<KEY_COUNT;j++)
		{
			if(IsKeyInPLCKeyCode(j, m_RecordList[i]))
			{
				str[j+1] = commandKey[j];
			}else{
				str[j+1] = '-';
			}
		}
		str[0] = '"';
		str[j] = '"';
		str[j+1] = '\r';
		str[j+2] = '\n';
		SDL_RWwrite(file, str, sizeof(Uint8), KEY_COUNT+3);
	}
	SDL_RWclose(file);
}
void CPlayer::LoadRecord()
{
	if (m_RecordList == NULL)
	{
		m_RecordList = (Uint16*)m_pAlloc->Alloc(MAX_COMMAND_RECORD_COUNT*sizeof(Uint16));
	}

	CTokenizer* tok = new CTokenizer();
	tok->OpenFile("record.txt");
	const char* commandKey = "UDLRABCXYZS";
	m_RecordCount = tok->GetInt();
	for (int i=0;i<m_RecordCount;i++)
	{
		const char* comand = tok->GetToken();
		int value = 0;
		for (int j=KEY_UP;j<KEY_COUNT;j++)
		{
			if(commandKey[j] == comand[j])
			{
				value = value|1 << j;
			}
		}
		m_RecordList[i] = value;
	}
	tok->CloseFile();
}
void CPlayer::RecordPlay()
{
	m_recordStatus = COMMAND_RECORD_PLAY;
	m_RecordPlayIndex = 0;
}
void CPlayer::UpdateCommand()
{
	if (m_propAILevel > 0)
	{
		return;
	}
	KEYBOARDDATA* keys = CConfigManager::GetInstance()->GetKeyBoard(m_propID);
	for( int k = 0; k < KEY_COUNT; k++ )
	{
		keys->keyInfo[ k ].isPressed = false;
	}
	CInput::GetInstance()->ProcessInput(keys);
	if (m_propID == P1)
	{
		CInput::GetInstance()->ProcessTouch(keys);
	}

	
	m_InputCommandCount = 0;
	bool facingRight = bRightFaced;
	m_KeyBuffer[m_KeyIndex].keyBitfield = 0; // buffer是用来存储上次的键值
	Sint32 curTime = CGameTimer::GetInstance()->GetGameTime();
	m_KeyBuffer[m_KeyIndex].gameTicks = curTime;
	// add current keystrokes to input buffer
	for( int k = 0; k < KEY_COUNT; k++ )
	{
		if( keys->keyInfo[ k ].isPressed )
		{
			if( ( k == KEY_LEFT ) && !facingRight )
			{
				m_KeyBuffer[m_KeyIndex].keyBitfield += PLC_KEYCODE(KEY_RIGHT);
			}
			else if( ( k == KEY_RIGHT ) && !facingRight )
			{
				m_KeyBuffer[m_KeyIndex].keyBitfield += PLC_KEYCODE( KEY_LEFT );
			}
			else
			{
				m_KeyBuffer[m_KeyIndex].keyBitfield += PLC_KEYCODE( k );
			}
		}    
	}

	// record
	if (m_recordStatus == COMMAND_RECORD_START)
	{
		if (m_RecordCount<MAX_COMMAND_RECORD_COUNT)
		{
			m_RecordList[m_RecordCount++] = m_KeyBuffer[m_KeyIndex].keyBitfield;
		}
	}else if(m_recordStatus == COMMAND_RECORD_PLAY)
	{
		if (m_RecordPlayIndex>=m_RecordCount)
		{
			m_RecordPlayIndex = 0;
		}
		m_KeyBuffer[m_KeyIndex].keyBitfield = m_RecordList[m_RecordPlayIndex++];
	}

	// 分三次，先遍历command，再遍历单个指令的按键，每个按键又要遍历历史buff
	PLCOMMAND* currCommand = m_Commands;
	for( int a = 0; a < m_CommandCount; a++ )// 遍历所有命令
	{           
		Sint32 nFirstTime = -1, nLastTime = -1;
		Sint32 currKeyIndex = 0;
		bool onRelease, onHold,use4Way,banOtherInput;
		Sint32 gameTicksToHold;
		Sint32 keyCode;

		PLCOMMANDFRAMEINPUT* frameInput;
		bool keyDown;
		Sint32 keyCodeDirs,frameInputDirs;
		PLCOMMANDFRAMEINPUT* frameInput2;
		bool keyDown2;
		Sint32 keyCodeDirs2,frameInputDirs2;

		Sint32 gameTicksHeld;

		// 使用例子command = ~D, DF, F, x讲解
		// 最初从x判定，按下，且与要求一致，将记录最后的时间，然后currKeyIndex++，将buffer判定向前推进
		// F，DF，一致的时候向前走，直到~D一致，记录第一时间，判定是否超出。
		for( int b = currCommand->nHowManyCommand - 1; b >= 0; b-- )// 遍历
		{
			bool bCommand = false;
			onRelease = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_ON_RELEASE ) != 0 );// 按键是否需要放开
			onHold = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_MUST_BE_HELD ) != 0 );// 是否要求按住
			use4Way = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_DETECT_AS_4WAY ) != 0 );// 是否是四个方向
			banOtherInput = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_BAN_OTHER_INPUT ) != 0 );// 是否禁止有其他按键按下
			gameTicksToHold = currCommand->nCommand[ b ].gameTicksForHold; // 按键按下的时间
			keyCode = currCommand->nCommand[ b ].keyCode;// 按键转码

			int allKeyCount = 0;
			for( ; currKeyIndex < m_KeyBufferSize; currKeyIndex++ )// 单个建向前buff匹配
			{
				frameInput = &m_KeyBuffer[ AdjustKeyIndex( m_KeyIndex, -currKeyIndex ) ];
				if (frameInput->keyBitfield&PLC_ALL_KEYS)
				{
					if (allKeyCount>=1)
					{
						break;
					}
					allKeyCount ++;
				}
				keyDown = (( frameInput->keyBitfield & keyCode ) == keyCode );
				if( keyDown && !use4Way )// 过滤方向键，比较纯粹的按键是否一致
				{
					keyCodeDirs = ( keyCode & PLC_ALL_DIRECTIONS_BITFIELD );
					frameInputDirs = ( frameInput->keyBitfield & PLC_ALL_DIRECTIONS_BITFIELD );
					keyDown = !keyCodeDirs || ( keyCodeDirs == frameInputDirs );
				}


				bool buttonConditionsMet = false;
				if( onRelease != keyDown)// 如果松开的类型，key按下，或者不是松开的类型，key不按下，都跳过，向下个buff匹配
				{
					gameTicksHeld = 0;
					for( int k = currKeyIndex + 1; k < m_KeyBufferSize; k++ )
					{
						frameInput2 = &m_KeyBuffer[ AdjustKeyIndex( m_KeyIndex, -k ) ];// 从当前的输入键值，向前遍历
						keyDown2 = (( frameInput2->keyBitfield & keyCode ) == keyCode );
						if( keyDown2 && !use4Way )// 按键按下，不是四个方向
						{
							keyCodeDirs2 = ( keyCode & PLC_ALL_DIRECTIONS_BITFIELD );
							frameInputDirs2 = ( frameInput2->keyBitfield & PLC_ALL_DIRECTIONS_BITFIELD );
							keyDown2 = !keyCodeDirs2 || (keyCodeDirs2 == frameInputDirs2);
						}  
						if( keyDown2 )
						{
							gameTicksHeld++;
							if( onHold )
							{
								buttonConditionsMet = keyDown;
								break;
							}
							else if( onRelease )
							{
								if( gameTicksHeld >= gameTicksToHold )
								{
									buttonConditionsMet = true;
									break;
								}
							}
							else
							{
								buttonConditionsMet = ( b < currCommand->nHowManyCommand - 1 );
								break;
							}
						}
						else
						{
							buttonConditionsMet = !( onHold || onRelease );    
							break;
						}                        
					}
				}
				// 如果单键过关了，就记录开始结束时间，继续下一个按键，
				if( buttonConditionsMet )
				{
					//if its the first element store the time of it
					if( b == 0 )
					{
						nFirstTime = frameInput->gameTicks;
						//PrintMessage("%d", frameInput->gameTicks);
					}

					if( b == ( currCommand->nHowManyCommand - 1 ))
					{
						nLastTime = frameInput->gameTicks;   
					}

					bCommand = true;
					currKeyIndex++;
					break;                    
				}
			}
			if( !bCommand )
				break;            
		}
		//PrintMessage(" nFirstTime %d nLastTime %d", nFirstTime, nLastTime);
		if( ( nFirstTime >= 0 ) && ( nLastTime > 0 ) )
		{
			// the last button of the sequenz must be pressed int the Current game tick to
			// be valid and then it must be check for how long it has taken to do the input
			// int gameTicks = GetGameTicks();
			// bufer时间，即时命令有效的tick时间
			Sint32 curTime = CGameTimer::GetInstance()->GetGameTime();
			if( (currCommand->nBufferTime > curTime - nLastTime) && ( nLastTime - nFirstTime  <= currCommand->nCommandTime ))
			{
				if (m_InputCommandCount<MAX_ALLOWED_COMMAND)
				{
					SDL_strlcpy((char*)m_CurrCommandName[m_InputCommandCount], currCommand->strCommand, MAX_ALLOWED_COMMANDSTR_COUNT);
					m_InputCommandCount++;
					if (m_IsLogCommand)
					{
						PrintMessage("<command>time:%5d, %s, commandcount %d ",CGameTimer::GetInstance()->GetGameTime(), currCommand->strCommand, m_InputCommandCount);
					}
				}else{
					break;
				}
				//break;

				//if (SDL_strcmp("holdfwd", currCommand->strCommand) == 0)//down_b
				//{
				//	PrintMessage("");
				//}
				//if (SDL_strcmp("holddown", m_CurrCommandName) == 0)//down_b
				//{
				//	PrintMessage("");
				//}

			}
		}
		currCommand++;
	}

	if( ++m_KeyIndex >= m_KeyBufferSize )
		m_KeyIndex = 0;
}

/*
================================================================================
================================================================================
*/

float CPlayer::GetConfigFloat(const char* key)
{
	SDL_assert(m_Config!=NULL);
	return m_Config->GetFloat(key);
}

const char * CPlayer::GetPlayerName()
{
	return m_playerName;
}

Sint32 CPlayer::GetScreenBack()
{
	Sint32 screenleft;
	if (m_propScreenBack == -1)
	{
		screenleft = CStageManager::GetInstance()->GetInt("Bound.screenleft");
		return screenleft;
	}else{
		return m_propScreenBack;
	}
}

Sint32 CPlayer::GetScreenFront()
{
	Sint32 screenright;
	if (m_propScreenFront == -1)
	{
		screenright = CStageManager::GetInstance()->GetInt("Bound.screenright");
		return screenright;
	}else{
		return m_propScreenFront;
	}
}
Sint32 CPlayer::GetPlayerBack()
{
	Sint32 back = 0;
	if (m_propWidthBack == -1)
	{
		if (this->nStateType == s_air)
		{
			back = m_Config->GetInt("Size.air.back");
		}else
		{
			back = m_Config->GetInt("Size.ground.back");
		}
		return back;
	}else
	{
		return m_propWidthBack;
	}
	
}

Sint32 CPlayer::GetPlayerFront()
{
	Sint32 front;
	if (m_propWidthFront == -1)
	{
		if (this->nStateType == s_air)
		{
			front = this->m_Config->GetInt("Size.air.front");
		}else
		{
			front = this->m_Config->GetInt("Size.ground.front");
		}
		return front;
	}else{
		return m_propWidthFront;
	}
	
}
/*
================================================================================
================================================================================
*/

void CPlayer::BeforeUpDatePlayer()
{
	//when pause not increase statetime
	if (!IsShake()&&!IsPause())
	{
		nStateTime ++;
	}
	// all this value will be seted by fsm or others
	this->SetPropScreenBack(-1);
	this->SetPropScreenFront(-1);
	this->SetPropWidthBack(-1);
	this->SetPropWidthFront(-1);
	this->SetPush(true);
	this->SetAssertNoAutoTurn(false);
	this->SetAssetNoWalk(false);
	CStageManager::GetInstance()->SetPropCameraPosYDelta(0);
	// update palPx after palpx seted,increase the paltime and end palpx
	if (m_PalFXinfo!=NULL)
	{
		m_PalFXinfo->nowtime ++;
		if (m_PalFXinfo->nowtime>=m_PalFXinfo->time)
		{
			// end palfx
			m_PalFXinfo = NULL;
		}
	}

	if (this->nPhysic == p_air)
	{
		float yaccel = this->GetConfigFloat("Movement.yaccel");
		yVel += yaccel;
	}

	// deal friction
	if (this->nPhysic == p_stand)
	{
		xVel *= this->GetConfigFloat("Movement.stand.friction");
		if (fabs(xVel) < this->GetConfigFloat("Movement.stand.friction.threshold"))
		{
			xVel = 0;
		}
	}else if(this->nPhysic == p_crouch){
		xVel *= this->GetConfigFloat("Movement.crouch.friction");
		if (fabs(xVel) < this->GetConfigFloat("Movement.crouch.friction.threshold"))
		{
			xVel = 0;
		}
	}
}

void CPlayer::HandleSYSStateNo()
{
	if (IsShake()||IsPause())
	{
		return;
	}
	bool isStand = this->nStateType == s_stand;
	bool isCrouch = this->nStateType == s_crouch;
	bool isIdle = this->nMoveType == m_idle;

	int stateNo = this->lpCurrStatedef->StateNumber;
	bool isWalk = stateNo == DEFAULT_WALK_STATE;
	bool isInState0 = stateNo == 0;

	//into ground
	if (y>0 && yVel>=0 && this->nPhysic == p_air)
	{
		yVel = 0;
		y = 0;
		this->ChangeState(DEFAULT_LAND_STATE);
		return;
	}

	if (bCtrl&&(IsCommandInput("holdback")||m_autoGuard))
	{
		if (isGuardDist()&&isIdle)
		{
			if (stateNo<120||stateNo>160)
			{
				this->ChangeState(DEFAULT_GUARD_START_STATE);
				return;
			}
		}
	}
	if (stateNo == DEFAULT_GUARD_END_STATE)
	{
		if (AnimTime()>=0)
		{
			if (this->nStateType == s_crouch)
			{
				ChangeState(DEFAULT_CROUCHING_STATE);
			}else if (this->nStateType == s_air)
			{
				ChangeState(DEFAULT_UP_DOWN_STATE);
			}else{
				ChangeState(DEFAULT_STAND_STATE);
			}
		}
		return;
	}

	if (isIdle&&bCtrl)
	{
		if (isStand&&IsCommandInput("holdup"))
		{
			this->ChangeState(DEFAULT_UP_STATE);
			return;

		}
		if (isStand&&IsCommandInput("holddown"))
		{
			this->ChangeState(DEFAULT_CROUCH_STATE);
			return;
		}

		if(isCrouch&&!IsCommandInput("holddown"))
		{
			this->ChangeState(DEFAULT_CROUCH_TOSTAND_STATE);
			return;
		}
		if(isStand)
		{
			if (isWalk&&!IsCommandInput("holdfwd")&&!IsCommandInput("holdback"))
			{
				this->ChangeState(DEFAULT_STAND_STATE);
			}

			if (isInState0 && (IsCommandInput("holdfwd")||IsCommandInput("holdback")))
			{
				if (!this->bAssertNoWalk)
				{
					this->ChangeState(DEFAULT_WALK_STATE);
				}
			}
		}
	}
}

/*
================================================================================
Handles the FSM of the player
-checks all trigger 
-and activate controllers  
================================================================================
*/
void CPlayer::HandleSYSFSM()
{
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

void CPlayer::HandleFSM()
{
	//check every state in this statedef
	/*if (lpCurrStatedef->StateNumber == 40)
	{
	PrintMessage("");
	}*/
	int stateNo = lpCurrStatedef->StateNumber;
	for(u16 i=0;i < lpCurrStatedef->nHowManyState; i++)
	{
		if (stateNo!=lpCurrStatedef->StateNumber)
		{
			return;
		}
		if( CheckState(&lpCurrStatedef->lpState[i], i))
			m_ControllerExec->ExecuteController(&lpCurrStatedef->lpState[i]);
	}
}


void CPlayer::HandleGetHit()
{
	if (m_propNotHitByTime >0)
	{
		m_propNotHitByTime -- ;
	}
	if (m_propHitByTime >0)
	{
		m_propHitByTime -- ;
	}
	if (m_GetHitInfo.bIsHitDefConfSet)
	{
		if (IsShake())
		{
			m_GetHitInfo.nShakeTime --;
		}
		else
		{
			m_GetHitInfo.nGetHitTime --;
		}

		if (this->lpCurrStatedef->StateNumber == DEFAULT_LIEDOWN_STATE)
		{
			m_GetHitInfo.nLieDownTime ++;
			Sint32 maxLieDownTime = m_Config->GetInt("Data.liedown.time");
			if (m_GetHitInfo.nLieDownTime >= maxLieDownTime)
			{
				this->ChangeState(DEFAULT_GETUP_STATE);
			}
		}else{
			m_GetHitInfo.nLieDownTime = 0;
		}
	}
}

bool CPlayer::IsClsn(ActionForPlay* act, CONTROLHITDEF* hitDefInfo, float clsnX, float clsnY)
{
	if (act->Anim == NULL)
	{
		return false;
	}

	if (m_p2->m_propNotHitByTime >0)
	{
		// not hit by
		Uint32 selfStateNeed = ~(m_p2->m_propNotHitByFlag & HitDef_Attr_STATE_MASK);
		bool stateMatch = hitDefInfo->attr&HitDef_Attr_STATE_MASK&selfStateNeed;
		if (!stateMatch)
		{
			return false;
		}
		Uint32 atkNeed = ~(m_p2->m_propNotHitByFlag & HitDef_Attr_ATK_MASK);
		bool atkMatch = hitDefInfo->attr&HitDef_Attr_ATK_MASK&atkNeed;
		if (!atkMatch)
		{
			return false;
		}
	}
	if (m_p2->m_propHitByTime >0)
	{
		// not hit by
		Uint32 selfStateNeed = m_p2->m_propHitByFlag;
		bool stateMatch = hitDefInfo->attr&HitDef_Attr_STATE_MASK&selfStateNeed;
		if (!stateMatch)
		{
			return false;
		}
		Uint32 atkNeed = m_p2->m_propHitByFlag & HitDef_Attr_ATK_MASK;
		bool atkMatch = hitDefInfo->attr&HitDef_Attr_ATK_MASK&atkNeed;
		if (!atkMatch)
		{
			return false;
		}
	}
	// hit flag
	u16 p2HitState = 1<<(m_p2->nStateType);

	u16 mask = ~(-1<<(s_liedown+1));
	u16 needhitflag = hitDefInfo->hitflag&mask; 
	if (!(needhitflag&p2HitState))
	{
		return false;
	}
	// p2 is in right move type
	mask = -1<<(s_liedown+1);
	needhitflag = hitDefInfo->hitflag&mask; 
	if (m_p2->nMoveType == m_hit)//+
	{
		p2HitState = 1<<(s_liedown+1);
	}
	if (m_p2->nMoveType != m_hit) //-
	{
		p2HitState = 1<<(s_liedown+2);
	}
	if (!(needhitflag&p2HitState))
	{
		return false;
	}

	// collision
	ActionElement* tActionElement1 = act->Anim;
	u16 p1_clsnCount = tActionElement1->AnimationElement[act->nCurrentImage].nNumberOfClsn1;
	ClsnRECT* p1_clsn = tActionElement1->AnimationElement[act->nCurrentImage].pClns1Data;
	ActionElement* tActionElement2 = m_p2->GetCurrAnim();
	u16 p2_clsnCount = tActionElement2->AnimationElement[m_p2->m_Anim->nCurrentImage].nNumberOfClsn2;
	ClsnRECT* p2_clsn = tActionElement2->AnimationElement[m_p2->m_Anim->nCurrentImage].pClns2Data;
	bool isClsn = false;
	ClsnRECT r1,r2;
	for (int i=0;i<p1_clsnCount;i++)
	{
		if (isClsn)
		{
			break;
		}

		if (this->bRightFaced)
		{
			r1 = Common_MoveRect(clsnX, clsnY, p1_clsn[i]);
		}else
		{
			ClsnRECT tmpRect = Common_GetRevertClsn(p1_clsn[i]);
			r1 = Common_MoveRect(clsnX, clsnY, tmpRect);
		}

		for (int j=0;j<p2_clsnCount;j++)
		{
			if (m_p2->bRightFaced)
			{
				r2 = Common_MoveRect(m_p2->m_curDrawInfo.nPosX, m_p2->m_curDrawInfo.nPosY, p2_clsn[j]);
			}else
			{
				ClsnRECT tmpRect = Common_GetRevertClsn(p2_clsn[j]);
				r2 = Common_MoveRect(m_p2->m_curDrawInfo.nPosX, m_p2->m_curDrawInfo.nPosY, tmpRect);
			}

			if (Common_rectIntersectsRect(r1, r2))
			{
				isClsn = true;
				break;
			}
		}
	}
	return isClsn;
}

void CPlayer::DoActionAfterHited(CONTROLHITDEF* hitDefInfo, bool isProj)
{

	this->nSprPrio = hitDefInfo->p1sprpriority;
	m_p2->nSprPrio = hitDefInfo->p2sprpriority;

	m_p2->m_GetHitInfo.bIsHitDefConfSet = true;
	m_p2->m_GetHitInfo.CtrlHitDefConf = hitDefInfo;
	m_p2->m_GetHitInfo.bIsShakedState = false;
	m_p2->m_GetHitInfo.nGetHitedState = m_p2->nStateType;

	if(hitDefInfo->fall && m_p2->m_GetHitInfo.nJuggle == JungleNotSet)
	{
		m_p2->m_GetHitInfo.nJuggle = m_p2->m_Config->GetInt("Data.airjuggle");
	}
	if(m_p2->m_GetHitInfo.nJuggle != JungleNotSet)
	{
		m_p2->m_GetHitInfo.nJuggle -= lpCurrStatedef->nJuggle;
		m_p2->m_GetHitInfo.nJuggle = Max(m_p2->m_GetHitInfo.nJuggle, JungleMinNum);
	}

	// power
	if (m_p2->m_GetHitInfo.bIsGuarded)
	{
		//damage
		float damage = 0;
		if (hitDefInfo->guard_damage != NULL){
			damage = m_pVMachine->Execute(hitDefInfo->guard_damage);
		}
		m_p2->ChangeLife(damage);
		int get = hitDefInfo->getpower;
		if (get == -1)
		{
			int param = CConfigManager::GetInstance()->GetFloat("Rules.Default.Attack.LifeToPowerMul");
			get = damage * param;
		}
		ChangePower(get);

		int give = hitDefInfo->givepower;
		if (give == -1)
		{
			int param = CConfigManager::GetInstance()->GetFloat("Rules.Default.GetHit.LifeToPowerMul");
			give = damage * param;
		}
		m_p2->ChangePower(give);
	}else{
		// palfx
		float time = m_pVMachine->Execute(hitDefInfo->palfx_time);
		if (time > 0)
		{
			hitDefInfo->palfxinfo.time = time;
			m_p2->PreParePalFX(&hitDefInfo->palfxinfo);
		}

		//damage
		float damage = 0;
		if (hitDefInfo->hit_damage != NULL){
			damage = m_pVMachine->Execute(hitDefInfo->hit_damage);
		}
		m_p2->ChangeLife(damage);
		int get = hitDefInfo->guard_getpower;
		if (get == -1)
		{
			int param = CConfigManager::GetInstance()->GetFloat("Rules.Default.Attack.LifeToPowerMul");
			get = damage * param * 0.5;
		}
		ChangePower(get);

		int give = hitDefInfo->guard_givepower;
		if (give == -1)
		{ 
			int param = CConfigManager::GetInstance()->GetFloat("Rules.Default.GetHit.LifeToPowerMul");
			give = damage * param * 0.5;
		}
		m_p2->ChangePower(give);
	}
	// comba
	if (m_p2->m_GetHitInfo.nCombo!=0)
	{
		m_p2->m_GetHitInfo.nCombo += m_p2->m_GetHitInfo.CtrlHitDefConf->numhits;
		m_p2->ShowCombo(m_p2->m_GetHitInfo.nCombo);
	}else{
		m_p2->m_GetHitInfo.nCombo = m_p2->m_GetHitInfo.CtrlHitDefConf->numhits;
	}

	if (m_p2->m_GetHitInfo.CtrlHitDefConf->fall)
	{
		m_p2->m_GetHitInfo.nFallCount++;
	}

	// set spark
	this->PrepareSpark(hitDefInfo, m_p2->m_GetHitInfo.bIsGuarded);

	// set get hit time
	OpElement* expiredTime;
	if (m_p2->m_GetHitInfo.bIsGuarded)
	{
		expiredTime =  m_p2->m_GetHitInfo.CtrlHitDefConf->guard_hittime == NULL ? 
		m_p2->m_GetHitInfo.CtrlHitDefConf->ground_hittime:m_p2->m_GetHitInfo.CtrlHitDefConf->guard_hittime; 
	}else if (m_p2->m_GetHitInfo.nGetHitedState == s_air)
	{
		expiredTime =  m_p2->m_GetHitInfo.CtrlHitDefConf->air_hittime; 
	}else{
		expiredTime = m_p2->m_GetHitInfo.CtrlHitDefConf->ground_hittime;
	}
	int exprTime = m_pVMachine->Execute(expiredTime);
	m_p2->m_GetHitInfo.nGetHitTime = exprTime;

	ChangeHitStateEnd();
}

void CPlayer::HandleHit()
{
	// proj time crease
	if (m_projHitInfo.bIsHited)
	{
		m_projHitInfo.nProjContact ++;
		if (m_projHitInfo.nProjHit != 0)
		{
			m_projHitInfo.nProjHit ++;
		}
		if (m_projHitInfo.nProjGuarded != 0)
		{
			m_projHitInfo.nProjGuarded ++;
		}
	}

	if (!m_HitInfo.bIsHitDefConfSet)
	{
		// no hitinfo
		return;
	}
	if (m_HitInfo.bIsHited)
	{
		if (IsPause())
		{
			m_HitInfo.nPauseTime --;
		}
		else
		{
			m_HitInfo.nMoveContact ++;
			if (m_HitInfo.nMoveHit != 0)
			{
				m_HitInfo.nMoveHit ++;
			}
			if (m_HitInfo.nMoveGuarded != 0)
			{
				m_HitInfo.nMoveGuarded ++;
			}
		}
		return;
	}

	// not atk type
	if (nMoveType!=m_attack)
	{
		return;
	}

	bool isClsn = IsClsn(m_Anim, m_HitInfo.CtrlHitDefConf, m_curDrawInfo.nPosX, m_curDrawInfo.nPosY);
	// 处理防御
	if (isClsn)
	{
		//if p2's juggle is seted ,  p1's needed juggle should begin than p2 owned;
		if (m_p2->m_GetHitInfo.bIsHitDefConfSet && m_p2->m_GetHitInfo.nJuggle != JungleNotSet)
		{
			int needJuggle = m_HitInfo.CtrlHitDefConf->air_juggle;
			int p2Juggle = m_p2->m_GetHitInfo.nJuggle;
			if ((m_p2->nStateType == s_air||m_p2->nStateType==s_liedown) &&needJuggle > p2Juggle)
			{
				PrintMessage("juggle is not enought");
				return;
			}
		}
		// set hited
		m_HitInfo.bIsHited = true;
		bool isGuarded = m_p2->isGuarded(m_HitInfo.CtrlHitDefConf);
		if (isGuarded)
		{
			m_HitInfo.nMoveGuarded = 1;
			m_HitInfo.nMoveContact = 1;
			m_HitInfo.nPauseTime = m_HitInfo.CtrlHitDefConf->guard_pause_time;
			m_p2->m_GetHitInfo.bIsGuarded = true;
			m_p2->m_GetHitInfo.nShakeTime = m_HitInfo.CtrlHitDefConf->guard_shake_time;
		}else{
			m_HitInfo.nMoveHit = 1;
			m_HitInfo.nMoveContact = 1;
			m_HitInfo.nPauseTime = m_HitInfo.CtrlHitDefConf->pause_time;
			m_p2->m_GetHitInfo.bIsGuarded = false;
			m_p2->m_GetHitInfo.nShakeTime =  m_HitInfo.CtrlHitDefConf->shake_time;
		}
		DoActionAfterHited(m_HitInfo.CtrlHitDefConf);
	}
}


void CPlayer::HandleProj()
{
	for(std::vector<ActionForPlay*>::iterator it=m_Proj.begin(); it!=m_Proj.end(); it++)  
	{ 
		ActionForPlay* act = *it;
		ProjectileInfo* projInfo = (ProjectileInfo*)(act->actData);
		CONTROLHITDEF* hitdefinfo = act->projinfo->pHitDefInfo;
		if (!act->moveinfo->isPosSeted)
		{
			continue;
		}
		if (act->projinfo->isHited)
		{
			continue;
		}
		bool isClsn = IsClsn(act, hitdefinfo, act->moveinfo->nPosX, act->moveinfo->nPosY);
		// 处理防御
		if (isClsn)
		{
			act->projinfo->isHited = true;
			act->Anim = NULL;

			m_projHitInfo.bIsHited = true;
			bool isGuarded = m_p2->isGuarded(hitdefinfo);
			m_projHitInfo.nProjID = projInfo->nProjID;
			if (isGuarded)
			{
				m_projHitInfo.nProjGuarded = 1;
				m_projHitInfo.nProjHit = 0;
				m_projHitInfo.nProjContact = 1;
				m_p2->m_GetHitInfo.bIsGuarded = true;
				m_p2->m_GetHitInfo.nShakeTime =hitdefinfo->guard_shake_time;
			}else{
				m_projHitInfo.nProjGuarded = 0;
				m_projHitInfo.nProjHit = 1;
				m_projHitInfo.nProjContact = 1;
				m_p2->m_GetHitInfo.bIsGuarded = false;
				m_p2->m_GetHitInfo.nShakeTime =  hitdefinfo->shake_time;
			}

			DoActionAfterHited(hitdefinfo, true);

			// m_Projhitanim
			if (projInfo->nProjhitanim!=-1)
			{
				if (m_Projhitanim == NULL)
				{
					m_Projhitanim = (ExplodInfo*)m_pAlloc->Alloc(sizeof(ExplodInfo));
					ExplodInfo tempinfo;
					SDL_memcpy(m_Projhitanim, &tempinfo, sizeof(ExplodInfo));
				}
				m_Projhitanim->nAnim = projInfo->nProjhitanim;
				m_Projhitanim->AnimType = AnimPlayer;
				m_Projhitanim->bOwnPal = true;
				m_Projhitanim->nRemovetime = -2;
				m_Projhitanim->nBindtime = 0;
				m_Projhitanim->postype = eEnumPosType_P2;
				m_Projhitanim->bFaceing = -1;
				m_Projhitanim->bVFaceing = -1;
				this->PrepareExplod(m_Projhitanim);
			}
		}
	}
}

//updates all interlal stuff of the player
void CPlayer::ChangeHitStateEnd()
{
	// set change state
	Sint32 attack_type;
	if (m_p2->m_GetHitInfo.nGetHitedState == s_air)
	{
		Sint32 ground_type = m_p2->m_GetHitInfo.CtrlHitDefConf->ground_type;
		attack_type = m_p2->m_GetHitInfo.CtrlHitDefConf->air_type == -1?ground_type:m_p2->m_GetHitInfo.CtrlHitDefConf->air_type;
	}
	else{
		attack_type = m_p2->m_GetHitInfo.CtrlHitDefConf->ground_type;
	}
	if (attack_type == HitDef_atk_type_Trip && m_p2->nStateType!=s_liedown)
	{
		m_p2->ChangeState(5070, true, false);
		return;
	}
	// 处理被打状态
	if (m_p2->m_GetHitInfo.bIsGuarded)
	{
		switch (m_p2->nStateType)
		{
		case s_stand:
			// dealwith groundType if trip
			m_p2->ChangeState(150, true, false);
			break;
		case s_crouch:
			m_p2->ChangeState(152, true, false);
			break;
		case s_air:
			// dealwith airType if trip
			m_p2->ChangeState(154, true, false);
			break;
		case s_liedown:
			m_p2->ChangeState(5080, true, false);
			break;

		default:
			break;
		}
	}else{
		if (m_p2->m_GetHitInfo.CtrlHitDefConf->p1stateno!=-1)
		{
			ChangeState(m_p2->m_GetHitInfo.CtrlHitDefConf->p1stateno, true, false);
		}
		if (m_p2->m_GetHitInfo.CtrlHitDefConf->p2stateno!=-1)
		{
			ChangeState(m_p2->m_GetHitInfo.CtrlHitDefConf->p2stateno, true, true);
			// not change again
			return;
		}
		switch (m_p2->nStateType)
		{
		case s_stand:
			// dealwith groundType if trip
			m_p2->ChangeState(5000, true, false);
			break;
		case s_crouch:
			m_p2->ChangeState(5010, true, false);
			break;
		case s_air:
			// dealwith airType if trip
			m_p2->ChangeState(5020, true, false);
			break;
		case s_liedown:
			m_p2->ChangeState(5080, true, false);
			break;

		default:
			break;
		}
	}
}
/*
================================================================================
Handles the players Physic 
================================================================================
*/
void CPlayer::HandlePhysic()
{

	if (this->IsPause()||this->IsShake())
	{
		return;
	}

	y+=yVel;

	if (bRightFaced)
	{
		x+=xVel;
	}else
	{
		x-=xVel;
	}

	Sint32 leftbound = CStageManager::GetInstance()->GetInt("PlayerInfo.leftbound");
	Sint32 rightbound = CStageManager::GetInstance()->GetInt("PlayerInfo.rightbound");
	//ow close the player can get to the edge of the screen.
	Sint32 screenleft = GetScreenBack();
	Sint32 screenright = GetScreenFront();
	Sint32 cameraLeft = CStageManager::GetInstance()->GetInt("Camera.boundleft");
	Sint32 cameraRight = CStageManager::GetInstance()->GetInt("Camera.boundright");

	Sint32 GameWidth = Common_GetDesiginWidth();
	Sint32 front1 = this->GetPlayerFront();
	Sint32 back1 = this->GetPlayerBack();
	Sint32 front2 = m_p2->GetPlayerFront();
	Sint32 back2 = m_p2->GetPlayerBack();

	// collision
	ActionElement* tActionElement1 = this->GetCurrAnim();
	u16 p1_clsnCount = tActionElement1->AnimationElement[m_Anim->nCurrentImage].nNumberOfClsn2;
	ClsnRECT* p1_clsn = tActionElement1->AnimationElement[m_Anim->nCurrentImage].pClns2Data;
	ActionElement* tActionElement2 = m_p2->GetCurrAnim();
	u16 p2_clsnCount = tActionElement2->AnimationElement[m_p2->m_Anim->nCurrentImage].nNumberOfClsn2;
	ClsnRECT* p2_clsn = tActionElement2->AnimationElement[m_p2->m_Anim->nCurrentImage].pClns2Data;
	bool isClsn = false;
	ClsnRECT r1,r2;
	for (int i=0;i<p1_clsnCount;i++)
	{
		if (isClsn)
		{
			break;
		}

		if (this->bRightFaced)
		{
			r1 = Common_MoveRect(this->x, this->y, p1_clsn[i]);
		}else
		{
			ClsnRECT tmpRect = Common_GetRevertClsn(p1_clsn[i]);
			r1 = Common_MoveRect(this->x, this->y, tmpRect);
		}

		for (int j=0;j<p2_clsnCount;j++)
		{
			if (m_p2->bRightFaced)
			{
				r2 = Common_MoveRect(m_p2->x, m_p2->y, p2_clsn[j]);
			}else
			{
				ClsnRECT tmpRect = Common_GetRevertClsn(p2_clsn[j]);
				r2 = Common_MoveRect(m_p2->x, m_p2->y, tmpRect);
			}

			if (Common_rectIntersectsRect(r1, r2))
			{
				isClsn = true;
				break;
			}
		}
	}
	bool bTmpPush = isClsn;
	Sint32 minScreenX = leftbound + screenleft;
	Sint32 maxScreenX = rightbound - screenright;
	Sint32 minCameraX = cameraLeft - GameWidth/2 + screenleft;
	Sint32 maxCameraX = cameraRight + GameWidth/2 - screenright;
	Sint32 minX = Max(minScreenX, minCameraX);
	Sint32 maxX = Min(maxScreenX, maxCameraX);

	if (this->x > maxX)
	{
		this->x = maxX;
	}
	if (this->x < minX)
	{
		this->x = minX;
	}

	// p1 to p2 's dis should less than gamewidth
	if(m_p2->x > this->x)
	{
		if (m_p2->x - this->x +  screenright + screenleft > GameWidth)
		{
			this->x -= xVel;
		}
	}else
	{
		if (this->x  - m_p2->x +  screenright + screenleft > GameWidth)
		{
			this->x += xVel;
		}
	}

	float SpeedFrictionWhenPush = CConfigManager::GetInstance()->GetFloat("Rules.SpeedFrictionWhenPush");
	// push each other
	if (bPush &&m_p2->bPush&& bTmpPush)
	{
		if(m_p2->x > this->x)
		{
			if ((m_p2->x - this->x) < front1 + front2)
			{
				float newX = this->x + front2 + front1;
				// beyond screen or camera
				if (newX > maxX)
				{
					this->x -= xVel;
				}else
				{
					// push
					this->x -= xVel*(1-SpeedFrictionWhenPush);
					m_p2->x = newX - xVel*(1-SpeedFrictionWhenPush);
				}
			}

		}else{
			if ((this->x - m_p2->x) < front1 + front2)
			{
				Sint32 newX = this->x - front2 - front1;
				// end
				if (newX < minX)
				{
					this->x -= xVel;
				}else
				{
					// push
					this->x += xVel*(1-SpeedFrictionWhenPush);
					m_p2->x = newX + xVel*(1-SpeedFrictionWhenPush);
				}
			}

		}

	}

}
//handles the facing of the player
void CPlayer::UpDateFacing()
{
	if (bAssertNoAutoTurn)
	{
		return;
	}
	if (!CStageManager::GetInstance()->GetInt("StageInfo.autoturn"))
	{
		return;
	}
	if (this->bCtrl&&this->nStateType == s_stand && this->nMoveType == m_idle)
	{
		if (this->x <= m_p2->x && bRightFaced != true)
		{
			// change speed
			this->xVel = -this->xVel;
			bRightFaced = true;
		}
		else if (this->x > m_p2->x &&  bRightFaced != false)
		{
			// change speed
			this->xVel = -this->xVel;
			bRightFaced = false;
		}
	}
	
}

void CPlayer::UpdateCamera()
{
	if (m_shake.time >0)
	{
		float deltaY = m_shake.ampl*sin(m_shake.passedtime*24*M_PI/(180.001-m_shake.freq) + M_PI*0.5 + m_shake.phase);
		CStageManager::GetInstance()->SetPropCameraPosYDelta(deltaY);
		m_shake.time --;
		m_shake.passedtime ++;
	}
	if (this->y <= m_p2->y)
	{
		CStageManager::GetInstance()->UpdateCameraByPlayerY(fabs(this->y));
	}
	
	Sint32 GameWidth = Common_GetDesiginWidth();
	Sint32 tension = CStageManager::GetInstance()->GetInt("Camera.tension");
	float cameraX = CStageManager::GetInstance()->GetPropCameraPosX();

	Sint32 screenleft = GetScreenBack();
	Sint32 screenright = GetScreenFront();

	Sint32 boundleft = CStageManager::GetInstance()->GetInt("Camera.boundleft");
	Sint32 boundright = CStageManager::GetInstance()->GetInt("Camera.boundright");

	if (this->x<m_p2->x)
	{
		if(2*tension + m_p2->x - this->x > GameWidth)
		{
			cameraX = this->x + (m_p2->x - this->x)/2;
		}else if(cameraX > this->x + GameWidth/2 - screenleft)
		{
			cameraX = this->x + GameWidth/2 - screenleft;
		}else if(cameraX > this->x + GameWidth/2 - tension)
		{
			cameraX = this->x + GameWidth/2 - tension;
		}else if(cameraX  < m_p2->x - GameWidth/2 + screenright)
		{
			cameraX = m_p2->x - GameWidth/2 + screenright;
		}else if (cameraX  < m_p2->x - GameWidth/2 + tension)
		{
			cameraX = m_p2->x - GameWidth/2 + tension;
		}
		if (cameraX < boundleft)
		{
			cameraX = boundleft;
		}
		if (cameraX > boundright)
		{
			cameraX = boundright;
		}
		CStageManager::GetInstance()->SetPropCameraPosX(cameraX);
	}
}




//updates all interlal stuff of the player
void CPlayer::UpDatePlayerFirst()
{
	UpdateCommand();
	// when end state,first enter 0 state, then next tick,change to other state
	// if first to handledirect
	HandleSYSStateNo();
	HandleSYSFSM();
	HandleFSM();
}

void CPlayer::UpDatePlayerSecond()
{
	// p2 is hited,will update the hited state in change state when time = 0(it's different from mugen, which time start from -1)
	// HandleGetHit because isshakedstate not set, the shake time will update next tick after the isshakedstate is seted in firstupdate
	// so is's real shake in next time
	HandleGetHit();
	HandleHit();
	HandleProj();
	HandlePhysic();
	UpDateFacing();
	UpdateCamera();
}

void CPlayer::AfterUpDatePlayer()
{
	// update state when get hit
	//deal with bind
	if (nTargetBindTime>0)
	{
		nTargetBindTime--;
		if (true)//nBindTargetID == -1
		{
			// avoid zero to change face
			if (bRightFaced)
			{
				m_p2->x = x + mBindPos.x+0.1;
				m_p2->m_curDrawInfo.nPosX = m_curDrawInfo.nPosX + mBindPos.x+0.1;
				m_p2->m_curDrawInfo.nScreenPosX = m_curDrawInfo.nScreenPosX + mBindPos.x+0.1;
			}else{
				m_p2->x = x - mBindPos.x-0.1;
				m_p2->m_curDrawInfo.nPosX = m_curDrawInfo.nPosX - mBindPos.x-0.1;
				m_p2->m_curDrawInfo.nScreenPosX = m_curDrawInfo.nScreenPosX - mBindPos.x-0.1;
			}
			m_p2->y = y + mBindPos.y;
			m_p2->m_curDrawInfo.nPosY = m_curDrawInfo.nPosY + mBindPos.y;
			m_p2->m_curDrawInfo.nScreenPosY = m_curDrawInfo.nScreenPosY + mBindPos.y;
		}
		if (nTargetBindTime <= 0)
		{
			nBindTargetID = -1;
			mBindPos = ccp(0,0);
		}
	}

	if (m_GetHitInfo.bIsHitDefConfSet&&nStateTime>=0)
	{
		// second tick, begin shake
		m_GetHitInfo.bIsShakedState = true;
	}

	if (!IsShake()&&!IsPause())
	{
		UpdateAnim(m_Anim);
	}
	UpdatePlayerAnimInfo();
	// update player's draw info in this gametick
	for(std::vector<ActionForPlay*>::iterator it=m_Explod.begin(); it!=m_Explod.end(); it++)  
	{ 
		if ((*it)->Anim == NULL)
		{
			continue;
		}
		ExplodInfo* actData = (ExplodInfo*)((*it)->actData);
		if (actData->bignorehitpause||!IsShake()&&!IsPause())
		{
			UpdateAnim(*it);
			UpdateExplodMove(*it);
		}
	}
	// don't pause when hit pause
	UpdateAnim(m_Spark);
	for(std::vector<ActionForPlay*>::iterator it=m_Proj.begin(); it!=m_Proj.end(); it++)  
	{ 
		UpdateAnim(*it);
		UpdateProjMove(*it);
	}
	if (m_Evn_color.time>0)
	{
		m_Evn_color.passedtime ++;
		if (m_Evn_color.passedtime > m_Evn_color.time)
		{
			m_Evn_color.time = 0;
		}
	}
	
}
/*
================================================================================
================================================================================
*/

//Load the player by his given .def filename
//ToDo: the .def file loading
bool CPlayer::LoadPlayer(const char* strPlayer, Uint32 pal)
{
	SDL_strlcpy(m_playerName, strPlayer, MAX_PATH);
	m_Config = CConfigManager::GetInstance()->GetCharConfig(strPlayer);
	m_IsLogCommand = CConfigManager::GetInstance()->GetInt("Rules.IsLogCommand");
	m_propMaxLife = m_propLife = m_Config->GetInt("Data.life");
	PLCOMMAND* playerCommand = m_Config->GetCmd()->GetConfigCmd();
	m_CommandCount = m_Config->GetCmd()->GetCmdCount();
	char alloName[MAX_PATH];
	SDL_snprintf(alloName, MAX_PATH, "%s_%d_%d",strPlayer, m_propID, m_playerUid);
	m_pAlloc = CMemManager::GetInstance()->GetAllocater(alloName);
	m_Commands = (PLCOMMAND*)m_pAlloc->Alloc(sizeof(PLCOMMAND)*m_CommandCount);
	SDL_memcpy(m_Commands, playerCommand, sizeof(PLCOMMAND)*m_CommandCount);

	m_KeyBuffer = (PLCOMMANDFRAMEINPUT*)m_pAlloc->Alloc(sizeof(PLCOMMANDFRAMEINPUT)*DEFAULT_KEY_BUF_MAX); 
	m_KeyBufferSize = DEFAULT_KEY_BUF_MAX;

	this->m_propPal = pal;
	PrepareAnim(0);
	ChangeState(0);    
	return true;
}


//draw debug info of the player
void CPlayer::DebugInfoToBack()
{
	float cameraX = CStageManager::GetInstance()->GetPropCameraPosX();
	float cameraY = CStageManager::GetInstance()->GetPropCameraPosY() + CStageManager::GetInstance()->GetPropCameraPosYDelta();
	PrintMessage("FPS:%5.2f",CGame::GetInstance()->GetPropFps());
	PrintMessage("name=%s, pos(%6.1f,%6.1f),vel(%4.1f,%4.1f),camera(%6.1f,%6.1f)",
		this->GetPlayerName(),x,y, xVel, yVel, cameraX, cameraY);
	PrintMessage("id=%d |Power=%4d |Life=%4d |AILevel=%d |Pal=%d |hitset=%d |MoveConctact=%d |MoveHit=%d |MoveGuard=%d",
		m_propID, m_propPower, m_propLife, m_propAILevel, m_propPal, m_HitInfo.bIsHitDefConfSet, m_HitInfo.nMoveContact, m_HitInfo.nMoveHit, m_HitInfo.nMoveGuarded);
	PrintMessage("sparkNo=%5d |nSprPrio=%d |juggle %5d |var(39) %d | RecordStatus %d/%d ",
		m_Spark==NULL?-1:m_Spark->nAnim, nSprPrio, m_GetHitInfo.nJuggle, GetVectorVar(39),
		m_recordStatus, m_recordStatus == COMMAND_RECORD_PLAY?m_RecordPlayIndex:m_RecordCount);
	PrintMessage("back=%3d |front=%3d |combo=%2d |fallcount=%2d |nGetHitTime=%2d | m_autoGuard=%2d ",
		this->GetPlayerBack(), this->GetPlayerFront(), this->m_GetHitInfo.nCombo, this->m_GetHitInfo.nFallCount, this->m_GetHitInfo.nGetHitTime, m_autoGuard);
	PrintMessage("nProjID=%d | MoveConctact=%d |MoveHit=%d |MoveGuard=%d |helper=%d |proj=%d |explod=%d ",
		m_projHitInfo.nProjID, m_projHitInfo.nProjContact, m_projHitInfo.nProjHit, m_projHitInfo.nProjGuarded, GetChildCount(),GetProjCount(-1), GetExplodCount(-1));

	PrintMessage("State=%8s | Move=%8s | Physic=%8s",
		s_StateStr[nStateType],m_StateStr[nMoveType],p_StateStr[nPhysic]);
	PrintMessage("Act %3i |bIsInP2Anim %d |%3i/%3i |ElemNo %3i/%3i |Time %3i/%3i ",
		m_Anim->Anim->nActionNumber,
		bIsInP2Anim,
		m_Anim->nCurrentImageTime, m_Anim->Anim->AnimationElement[m_Anim->nCurrentImage].nDuringTime,
		m_Anim->nCurrentImage+1,m_Anim->Anim->nNumberOfElements,
		m_Anim->nCurrTime,m_Anim->Anim->nCompletAnimTime);
	PrintMessage("State No %3i | bIsInP2State %d | Time %3i | ctrl %i |GameTick %5i",
		lpCurrStatedef->StateNumber,bIsInP2State, this->nStateTime, this->bCtrl,  CGameTimer::GetInstance()->GetGameTime());

}

//draw debug info of the player
void CPlayer::Debug()
{
	float cameraX = CStageManager::GetInstance()->GetPropCameraPosX();
	float cameraY = CStageManager::GetInstance()->GetPropCameraPosY() + CStageManager::GetInstance()->GetPropCameraPosYDelta();
	//CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,0,"FPS:%5.2f",CGame::GetInstance()->GetPropFps());
	CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,15,"name=%s, pos(%6.1f,%6.1f),vel(%4.1f,%4.1f),camera(%6.1f,%6.1f)",
		this->GetPlayerName(),x,y, xVel, yVel, cameraX, cameraY);
	CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,30,"id=%d |Power=%4d |Life=%4d |AILevel=%d |Pal=%d |hitset=%d |MoveConctact=%d |MoveHit=%d |MoveGuard=%d",
		m_propID, m_propPower, m_propLife, m_propAILevel, m_propPal, m_HitInfo.bIsHitDefConfSet, m_HitInfo.nMoveContact, m_HitInfo.nMoveHit, m_HitInfo.nMoveGuarded);
	CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,45,"sparkNo=%5d |nSprPrio=%d |juggle %5d |var(39) %d | RecordStatus %d/%d",
		m_Spark==NULL?-1:m_Spark->nAnim, nSprPrio, m_GetHitInfo.nJuggle, GetVectorVar(39),
		m_recordStatus, m_recordStatus == COMMAND_RECORD_PLAY?m_RecordPlayIndex:m_RecordCount);
	CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,60,"back=%3d |front=%3d |combo=%2d |fallcount=%2d |nGetHitTime=%2d | m_autoGuard=%2d",
		this->GetPlayerBack(), this->GetPlayerFront(), this->m_GetHitInfo.nCombo, this->m_GetHitInfo.nFallCount, this->m_GetHitInfo.nGetHitTime, m_autoGuard);
	CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,75, "nProjID=%d | MoveConctact=%d |MoveHit=%d |MoveGuard=%d |helper=%d |proj=%d |explod=%d ",
		m_projHitInfo.nProjID, m_projHitInfo.nProjContact, m_projHitInfo.nProjHit, m_projHitInfo.nProjGuarded, GetChildCount(),GetProjCount(-1), GetExplodCount(-1));

	CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,90,"State=%8s | Move=%8s | Physic=%8s",
		s_StateStr[nStateType],m_StateStr[nMoveType],p_StateStr[nPhysic]);
	CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,105,"Act %3i |bIsInP2Anim %d |%3i/%3i |ElemNo %3i/%3i |Time %3i/%3i ",
		m_Anim->Anim->nActionNumber,
		bIsInP2Anim,
		m_Anim->nCurrentImageTime, m_Anim->Anim->AnimationElement[m_Anim->nCurrentImage].nDuringTime,
		m_Anim->nCurrentImage+1,m_Anim->Anim->nNumberOfElements,
		m_Anim->nCurrTime,m_Anim->Anim->nCompletAnimTime);
	CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,120,"State No %3i | bIsInP2State %d |Time %3i | ctrl %i |GameTick %5i",
		lpCurrStatedef->StateNumber, bIsInP2State, this->nStateTime, this->bCtrl,  CGameTimer::GetInstance()->GetGameTime());

}


void CPlayer::MoveForward(Sint32 dis)
{
	if (bRightFaced)
	{
		this->x += dis;
	}else{
		this->x -= dis;
	}
}
void CPlayer::ChangeMoveType(Sint32 mtype)
{
	//[State 5040, 4]
	//type = StateTypeSet
	//	trigger1 = HitOver
	//	movetype = I

	//	[State 5040, 5]
	//type = VelAdd
	//	trigger1 = 1
	//	y = GetHitVar(yaccel)
	// as config like this, will can't get the yaccel,so only endhiedstate, when change state;
	/*if (this->nMoveType == m_hit && mtype != m_hit)
	{
	this->EndGetHited();
	}*/
	this->nMoveType = mtype;
}
void CPlayer::ChangeLife(Sint32 value)
{
	CEngine::GetInstance()->GetGameLayer()->OnLifeChanged(this->m_propID, this->m_propMaxLife, this->m_propLife, -value);
	m_propLife -= value;
	if (m_propLife<=0)
	{
		bAlive = false;
	}
}
void CPlayer::ChangePower(Sint32 value)
{
	CEngine::GetInstance()->GetGameLayer()->OnPowerChanged(this->m_propID, this->m_propMaxPower, this->m_propPower, value);
	m_propPower += value;
	m_propPower = Min(m_propPower, m_propMaxPower);
	m_propPower = Max(m_propPower, 0);
}

void CPlayer::ShowCombo(Sint32 value)
{
	m_ComboShowTicks = 0;
	if (m_ComboTexture)
	{
		CC_SAFE_RELEASE_NULL(m_ComboTexture);
	}
	CFontManager::GetInstance()->SetFontColor(255, 255, 255,255);
	m_ComboTexture = CFontManager::GetInstance()->GetFontTextureFormat("+%d COMBO!", value);
	m_ComboTexture->retain();
}

bool CPlayer::CheckState(PLSTATE* tempState, int index)
{
	/*if (SDL_strcasecmp("StandLightKick", tempState->stInfo)==0&&IsCommandInput("a"))
	{
	if (m_proptmp == 3)
	{
	PrintMessage("");
	}
	m_proptmp = 3;

	}*/
	CAssert(index<MAX_STATE_NUM, "state should less than MAX_STATE_NUM");
	if (tempState->bIgnorPause == false)
	{
		if (this->IsPause())
		{
			return false;
		}
		if (this->IsShake())
		{
			return false;
		}
	}
	// default all trigger is true
	for (int i=0;i<tempState->nHowManyTriggers;i++)
	{
		TriggerStruct trigger = tempState->triggers[i];
		this->SetVectorTrigRet(trigger.nTriggerIndex, true);
	}
	// exec
	for (int i=0;i<tempState->nHowManyTriggers;i++)
	{
		TriggerStruct trigger = tempState->triggers[i];
		/*if (SDL_strcasecmp("test11", tempState->stInfo) == 0)
		{
			PrintMessage("");
		}*/
		bool trig = (bool)m_pVMachine->ExecuteForState(trigger.pInts);
		if (trigger.nTriggerIndex == 0&&!trig)
		{
			return false;
		}
		bool blastTrig = this->GetVectorTrigRet(trigger.nTriggerIndex);
		this->SetVectorTrigRet(trigger.nTriggerIndex, trig&&blastTrig);
	}
	// ret
	bool bTriggerAll=true;
	bool bTrigger=false;
	for (int i=0;i<tempState->nHowManyTriggers;i++)
	{
		TriggerStruct trigger = tempState->triggers[i];
		bool tmpTrig = this->GetVectorTrigRet(trigger.nTriggerIndex);
		if (trigger.nTriggerIndex == 0)
		{
			// triggerall
			bTriggerAll = bTriggerAll&&tmpTrig;
			if (!bTriggerAll)
			{
				break;
			}
		}else{
			bTrigger = bTrigger || tmpTrig;
			/*if (!bTrigger)
			{
				break;
			}*/
		}
	}

	bool ret = bTriggerAll&&bTrigger;
	if (ret)
	{
		/*if (tempState->nPersistent<0)
		{
			throw CError("bPersistent is invalid");
		}*/
		// -1 is the flag to be valided only once.
		if (tempState->nRunCount == -1)
		{
			return false;
		}else if (tempState->nPersistent == 0){
			tempState->nRunCount = -1;
			return true;
		}else{
			tempState->nRunCount += 1;
			if (tempState->nRunCount%tempState->nPersistent == 0)
			{
				return true;
			}else
			{
				return false;
			}
		}

	}else
	{
		return false;
	}
}

int CPlayer::AnimTime()
{
	return m_Anim->nCurrTimeInAnim - m_Anim->Anim->nCompletAnimTime;
}

bool CPlayer::isGuardDist()
{
	int playerdist = fabs(this->x - m_p2->x);
	if(m_p2->nMoveType == m_attack)
	{
		int guarddist = 0;
		if (m_p2->m_HitInfo.bIsHitDefConfSet)
		{
			guarddist = m_p2->m_HitInfo.CtrlHitDefConf->guard_dist;
			if (guarddist == -1)
			{
				guarddist = m_Config->GetInt("Size.attack.dist");
			}
			
		}else{
			guarddist = m_Config->GetInt("Size.attack.dist");
		}
		if (playerdist < guarddist)
		{
			return true;
		}
	}
	
	for(std::vector<ActionForPlay*>::iterator it=m_p2->m_Proj.begin(); it!=m_p2->m_Proj.end(); it++)  
	{ 
		if (*it != NULL && (*it)->Anim!=NULL)
		{
			CONTROLHITDEF* hitinfo = (*it)->projinfo->pHitDefInfo;
			int guarddist = hitinfo->guard_dist;
			if (guarddist == -1)
			{
				guarddist = m_Config->GetInt("Size.proj.attack.dist");
			}
			int projdis = fabs((*it)->moveinfo->nPosX - m_curDrawInfo.nPosX);
			if (projdis < guarddist)
			{
				return true;
			}
		}
	}
	return false;
}

bool CPlayer::isGuarded(CONTROLHITDEF* hitinfo)
{
	if (!bCtrl)
	{
		return false;
	}
	if (!m_autoGuard)
	{
		if (!IsCommandInput("holdback"))
		{
			return false;
		}
	}
	
	// hit flag
	u16 p2HitState = 1<<(m_p2->nStateType);

	u16 mask = ~(-1<<(s_liedown+1));
	u16 needhitflag = hitinfo->hitflag&mask; 
	if (!(needhitflag&p2HitState))
	{
		return false;
	}
	return true;
}

// when movetype change to not hit, restet all get hit info
void CPlayer::EndGetHited()
{
	m_GetHitInfo.bIsHitDefConfSet = false;

	m_GetHitInfo.bIsShakedState = false;
	m_GetHitInfo.nGetHitTime = 0;
	m_GetHitInfo.nFallCount = 0;
	m_GetHitInfo.nCombo = 0;
	m_GetHitInfo.nJuggle = JungleNotSet;
}

void CPlayer::ChangeState(Sint32 nStateNumber, bool changeByHit, bool isChangeP2State)
{
	/*if (nStateNumber == 2220)
	{
	PrintMessage("");
	}*/
	if (isChangeP2State)
	{
		m_p2->bIsInP2State = true;
		m_p2->bCtrl = false;
		ChangePlayerState(m_p2, nStateNumber, changeByHit);
	}else{
		this->bIsInP2State = false;
		ChangePlayerState(this, nStateNumber, changeByHit);
	}
}

void CPlayer::ChangePlayerState(CPlayer* curPlayer, Sint32 nStateNumber, bool changeByHit)
{
	bool isChangeP2State = this->GetPropID() != curPlayer->GetPropID();
	PrintMessage("time:%5d|ID %d:<<ChangeP2State %d>> changeState %d ", CGameTimer::GetInstance()->GetGameTime(), curPlayer->GetPropID(), isChangeP2State, nStateNumber);
	//get the statedef
	PLSTATEDEF* curDef = m_Config->GetState()->GetStateDef(nStateNumber);
	if (!curDef)
	{
		return;
	}

	if (curPlayer->lpCurrStatedef)
	{
		curPlayer->nLastStateNo = curPlayer->lpCurrStatedef->StateNumber;
	}
	curPlayer->lpCurrStatedef=curDef;
	//Set StateType
	if(curDef->type!=s_untouch)
		curPlayer->nStateType=curDef->type;
	//Set Physic    
	if(curDef->physics!=p_untouch)
		curPlayer->nPhysic=curDef->physics;

	if(curDef->movetype!=m_untouch)
		curPlayer->nMoveType=curDef->movetype;
	if (curPlayer->nMoveType != m_hit)
	{
		curPlayer->EndGetHited();
	}
	//Set the Ctrl flag  
	if(curDef->bCtrl != -1)
		curPlayer->bCtrl=curDef->bCtrl;

	curPlayer->bHitDefPresit                  =curDef->bHitdefpersist;
	curPlayer->bHitCounterPresit              =curDef->bHitcountpersist;
	curPlayer->bMoveHitPresit                 =curDef->bMovehitpersist;
	if (!curPlayer->bHitDefPresit)
	{
		curPlayer->m_HitInfo.bIsHitDefConfSet = false;

	}
	if(!curPlayer->bMoveHitPresit){
		// 计算+1，当pause结束的时候不加1
		curPlayer->m_HitInfo.bIsHited = false;
		curPlayer->m_HitInfo.nMoveContact = 0;
		curPlayer->m_HitInfo.nMoveGuarded = 0;
		curPlayer->m_HitInfo.nMoveHit = 0;
	}
	// 是否重置打中人数
	if (!curPlayer->bHitCounterPresit)
	{
		curPlayer->m_HitInfo.nHitCount = 0;
	}

	if(curDef->nAnim != NULL)
	{
		int ani = curPlayer->m_pVMachine->Execute(curDef->nAnim);
		curPlayer->PrepareAnim(ani, this->bIsInP2State);
	}

	if(curDef->Velset.x != UNSET_STATEDEF_FLAG)
		curPlayer->xVel=curDef->Velset.x;

	if(curDef->Velset.y != UNSET_STATEDEF_FLAG)
		curPlayer->yVel=curDef->Velset.y;

	if(curDef->nSprpriority != INVALID_SPR_PRIORITY)
		curPlayer->nSprPrio=curDef->nSprpriority;

	if(curDef->nPoweradd != UNSET_STATEDEF_FLAG)
		curPlayer->ChangePower(curDef->nPoweradd);

	// init state run count
	CAssert(curDef->nHowManyState<=MAX_STATE_NUM, "state num should less than MAX_STATE_NUM");
	for (Uint32 i=0;i<curDef->nHowManyState;i++)
	{
		//TODO:bug if two same player in state statedef
		PLSTATE *curState = curDef->lpState + i;
		curState->nRunCount = 0;
	}

	//restet StateTime next time run it
	
	// don't run fsm when change by others
	if (!changeByHit)
	{
		// shake end,because when p2state,some state can't evelate
		curPlayer->m_GetHitInfo.nShakeTime = 0;
		curPlayer->nStateTime=0;
		int stateNo = curDef->StateNumber;
		for(u16 i=0;i < curDef->nHowManyState; i++)
		{
			if (curDef->StateNumber!= stateNo)
			{
				// change state in loop
				break;
			}
			if( curPlayer->CheckState(&curDef->lpState[i], i))
				curPlayer->m_ControllerExec->ExecuteController(&curDef->lpState[i]);
		}
	}else{
		curPlayer->nStateTime=-1;
	}
}

void CPlayer::PrepareSpark(CONTROLHITDEF* hitdef, bool isGuard)
{
	Sint32 sparkNo = -1;
	if (isGuard)
	{
		sparkNo = hitdef->guard_sparkno;
		if (sparkNo == -1)
		{
			sparkNo = hitdef->sparkno;
		}
		if (sparkNo == -1)
		{
			sparkNo = m_Config->GetInt("Data.guard.sparkno");
		}
	}else
	{
		sparkNo = hitdef->sparkno;
		if (sparkNo == -1)
		{
			sparkNo = m_Config->GetInt("Data.sparkno");
		}
	}
	//CAssert(sparkNo!=-1, "spark no should config");
	SDL_assert(m_Config!=NULL);
	ActionElement* tmp = m_Config->GetAir()->GetAction(sparkNo);
	if (tmp== NULL ){
		return;
	}
	if (m_Spark == NULL)
	{
		m_Spark = (ActionForPlay*)m_pAlloc->Alloc(sizeof(ActionForPlay));
		m_Spark->moveinfo = (ActionMoveInfo*)m_pAlloc->Alloc(sizeof(ActionMoveInfo));
	}

	m_Spark->Anim = tmp;
	m_Spark->nAnim = sparkNo;
	m_Spark->nCurrentImage=CUR_IMAGE_INDEX_START;
	m_Spark->nCurrentImageTime=CUR_IMAGE_TIME_START;
	m_Spark->nCurrTime=CUR_TIME_START;
	m_Spark->nCurrTimeInAnim=CUR_TIME_START;

	m_Spark->type = AnimPlayer;
	m_Spark->acttype = ActSpark;
	m_Spark->bOwnpal = true;
	m_Spark->nRemovetime = -2;

	m_Spark->actData = NULL;
	//curPlayer->m_Anim->moveinfo = NULL;
	/*if (m_Spark->moveinfo == NULL)
	{
	m_Spark->moveinfo = (ActionMoveInfo*)m_pAlloc->Alloc(sizeof(ActionMoveInfo));
	}*/
	m_Spark->moveinfo->isPosSeted = true;
	m_Spark->moveinfo->bRightFacing = bRightFaced;
	m_Spark->moveinfo->bVRightFacing = bRightFaced;
	float offsetx, offsety;
	if (hitdef->sparkno_x)
	{
		offsetx = m_pVMachine->Execute(hitdef->sparkno_x);
		offsety = m_pVMachine->Execute(hitdef->sparkno_y);
	}else{
		offsetx = 0;
		offsety = 0;
	}
	// set pos
	Sint32 P2Front = m_p2->GetPlayerFront();
	if (bRightFaced)
	{
		m_Spark->moveinfo->nPosX = m_p2->m_curDrawInfo.nPosX - P2Front - offsetx;
		m_Spark->moveinfo->nPosY =  m_curDrawInfo.nPosY + offsety;
	}
	else
	{
		m_Spark->moveinfo->nPosX = m_p2->m_curDrawInfo.nPosX + P2Front + offsetx;
		m_Spark->moveinfo->nPosY =  m_curDrawInfo.nPosY + offsety;
	}
	//curPlayer->m_Anim->projinfo = NULL;
}

void CPlayer::PrepareSuperAnim(Uint32 nAnim, EnumAnimType type, int offsetx, int offsety)
{
	ActionElement* tmp = NULL;
	if (type == AnimPlayer)
	{
		tmp = m_Config->GetAir()->GetAction(nAnim);
	}else if (type == AnimFightFX){
		tmp = CConfigManager::GetInstance()->GetSystemConfig()->GetFightConfig()->GetFXAir()->GetAction(nAnim);
	}
	if (tmp== NULL ){
		return;
	}
	
	if (m_SuperAnim == NULL)
	{
		m_SuperAnim = (ActionForPlay*)m_pAlloc->Alloc(sizeof(ActionForPlay));
		m_SuperAnim->moveinfo = (ActionMoveInfo*)m_pAlloc->Alloc(sizeof(ActionMoveInfo));
	}
	m_SuperAnim->Anim = tmp;
	m_SuperAnim->nAnim = nAnim;
	m_SuperAnim->nCurrentImage=CUR_IMAGE_INDEX_START;
	m_SuperAnim->nCurrentImageTime=CUR_IMAGE_TIME_START;
	m_SuperAnim->nCurrTime=CUR_TIME_START;
	m_SuperAnim->nCurrTimeInAnim=CUR_TIME_START;

	m_SuperAnim->type = type;
	m_SuperAnim->acttype = ActSuperAnim;
	m_SuperAnim->bOwnpal = true;
	m_SuperAnim->nRemovetime = -2;

	m_SuperAnim->actData = NULL;
	//curPlayer->m_Anim->moveinfo = NULL;
	/*if (m_SuperAnim->moveinfo == NULL)
	{
	m_SuperAnim->moveinfo = (ActionMoveInfo*)m_pAlloc->Alloc(sizeof(ActionMoveInfo));
	}*/
	m_SuperAnim->moveinfo->isPosSeted = true;
	m_SuperAnim->moveinfo->bRightFacing = bRightFaced;
	m_SuperAnim->moveinfo->bVRightFacing = bRightFaced;
	if (bRightFaced)
	{
		m_SuperAnim->moveinfo->nPosX = m_curDrawInfo.nPosX + offsetx;
		m_SuperAnim->moveinfo->nPosY =  m_curDrawInfo.nPosY + offsety;
	}
	else
	{
		m_SuperAnim->moveinfo->nPosX = m_curDrawInfo.nPosX - offsetx;
		m_SuperAnim->moveinfo->nPosY =  m_curDrawInfo.nPosY + offsety;
	}
	//curPlayer->m_Anim->projinfo = NULL;
}


void CPlayer::PrepareProj(ProjectileInfo* projInfo, CONTROLHITDEF* hitdefInfo)
{
	ActionForPlay* curAct = NULL;
	for(std::vector<ActionForPlay*>::iterator it=m_Proj.begin(); it!=m_Proj.end(); it++)  
	{ 
		if (*it != NULL && (*it)->Anim==NULL)
		{
			curAct = *it;
			break;
		}
	}
	if (curAct == NULL)
	{
		curAct = (ActionForPlay*)m_pAlloc->Alloc(sizeof(ActionForPlay));
		curAct->Anim = NULL;
		curAct->moveinfo = (ActionMoveInfo*)m_pAlloc->Alloc(sizeof(ActionMoveInfo));
		curAct->projinfo = (ProjHitInfo*)m_pAlloc->Alloc(sizeof(ProjHitInfo));
		m_Proj.push_back(curAct);
	}

	ActionElement* tmp;
	tmp = m_Config->GetAir()->GetAction(projInfo->nAnim);
	PrintMessage("PrepareProj anim %d, isanimExisted %d ", projInfo->nAnim, int(tmp!= NULL));
	if (tmp== NULL){
		return;
	}
	curAct->Anim = tmp;
	curAct->nAnim = projInfo->nAnim;
	curAct->nCurrentImage=CUR_IMAGE_INDEX_START;
	curAct->nCurrentImageTime=CUR_IMAGE_TIME_START;
	curAct->nCurrTime=CUR_TIME_START;
	curAct->nCurrTimeInAnim=CUR_TIME_START;

	curAct->type = AnimPlayer;
	curAct->acttype = ActProj;
	curAct->bOwnpal = true;
	curAct->nRemovetime = projInfo->nRemovetime;

	curAct->actData = projInfo;
	//curPlayer->m_Anim->moveinfo = NULL;
	curAct->moveinfo->isPosSeted = false;
	curAct->moveinfo->bRightFacing = bRightFaced;
	curAct->moveinfo->bVRightFacing = bRightFaced;
	curAct->moveinfo->nBindtime = 0;
	//curPlayer->m_Anim->projinfo = NULL;
	curAct->projinfo->isHited = false;
	curAct->projinfo->pHitDefInfo = hitdefInfo;

}

//prepares the animation
void CPlayer::PrepareExplod(ExplodInfo* explodinfo)
{
	ActionForPlay* curAct = NULL;
	for(std::vector<ActionForPlay*>::iterator it=m_Explod.begin(); it!=m_Explod.end(); it++)  
	{ 
		if (*it != NULL && (*it)->Anim==NULL)
		{
			curAct = *it;
			break;
		}
	}
	if (curAct == NULL)
	{
		curAct = (ActionForPlay*)m_pAlloc->Alloc(sizeof(ActionForPlay));
		curAct->Anim = NULL;
		curAct->moveinfo = (ActionMoveInfo*)m_pAlloc->Alloc(sizeof(ActionMoveInfo));
		m_Explod.push_back(curAct);
	}

	ActionElement* tmp;
	Sint32 nAnim = explodinfo->nAnim;
	if (explodinfo->AnimType == AnimPlayer)
	{
		tmp = m_Config->GetAir()->GetAction(nAnim);
	}else if (explodinfo->AnimType == AnimFightFX){
		tmp = CConfigManager::GetInstance()->GetSystemConfig()->GetFightConfig()->GetFXAir()->GetAction(nAnim);
	}
	if (tmp== NULL ){
		// can't find act
		return;
	}
	PrintMessage("PrepareExplod nAnim %d isAnimExised %d ",nAnim, int(tmp!=NULL));
	curAct->Anim = tmp;
	curAct->nAnim = nAnim;
	curAct->nCurrentImage=CUR_IMAGE_INDEX_START;
	curAct->nCurrentImageTime=CUR_IMAGE_TIME_START;
	curAct->nCurrTime=CUR_TIME_START;
	curAct->nCurrTimeInAnim=CUR_TIME_START;

	curAct->type = explodinfo->AnimType;
	curAct->acttype = ActExplod;
	curAct->bOwnpal = explodinfo->bOwnPal;
	curAct->nRemovetime = explodinfo->nRemovetime;

	curAct->actData = explodinfo;
	//curPlayer->m_Anim->moveinfo = NULL;
	curAct->moveinfo->isPosSeted = false;
	if (explodinfo->bFaceing == 1)
	{
		switch (explodinfo->postype)
		{
		case eEnumPosType_P2:
			curAct->moveinfo->bRightFacing = m_p2->bRightFaced;
			break;
		default:
			curAct->moveinfo->bRightFacing = bRightFaced;
			break;
		}
	}else{
		switch (explodinfo->postype)
		{
		case eEnumPosType_P2:
			curAct->moveinfo->bRightFacing = !m_p2->bRightFaced;
			break;
		default:
			curAct->moveinfo->bRightFacing = !bRightFaced;
			break;
		}
	}
	if (explodinfo->bVFaceing == explodinfo->bFaceing)
	{
		curAct->moveinfo->bVRightFacing = curAct->moveinfo->bRightFacing;
	}else{
		curAct->moveinfo->bVRightFacing = !curAct->moveinfo->bRightFacing;
	}
	curAct->moveinfo->nBindtime = explodinfo->nBindtime;
	//curPlayer->m_Anim->projinfo = NULL;
}

//prepares the animation
void CPlayer::PrepareAnim(Uint32 nAnim, bool isChangeP2Anim)
{
	if (isChangeP2Anim)
	{
		m_p2->bIsInP2Anim = true;
		PreparePlayerAnim(m_p2, nAnim);
	}else
	{
		this->bIsInP2Anim = false;
		PreparePlayerAnim(this, nAnim);
	}
}

//prepares the animation
void CPlayer::PreparePlayerAnim(CPlayer* curPlayer, Uint32 nAnim)
{
	bool isChangeP2Anim = this->GetPropID() != curPlayer->GetPropID();
	PrintMessage("time:%5d|ID %d:ChangeP2Anim %d PrepareAnim %d ", CGameTimer::GetInstance()->GetGameTime(), curPlayer->GetPropID(), isChangeP2Anim, nAnim);
	SDL_assert(m_Config!=NULL);

	ActionElement* tmp = m_Config->GetAir()->GetAction(nAnim);
	if (tmp== NULL ){
		return;
	}
	if (curPlayer->m_Anim == NULL)
	{
		curPlayer->m_Anim = (ActionForPlay*)m_pAlloc->Alloc(sizeof(ActionForPlay));
	}
	curPlayer->m_Anim->Anim = tmp;
	curPlayer->m_Anim->nAnim = nAnim;
	curPlayer->m_Anim->nCurrentImage=CUR_IMAGE_INDEX_START;
	curPlayer->m_Anim->nCurrentImageTime=CUR_IMAGE_TIME_START;
	curPlayer->m_Anim->nCurrTime=CUR_TIME_START;
	curPlayer->m_Anim->nCurrTimeInAnim=CUR_TIME_START;

	curPlayer->m_Anim->type = AnimPlayer;
	curPlayer->m_Anim->acttype = ActAnim;
	curPlayer->m_Anim->bOwnpal = false;
	curPlayer->m_Anim->nRemovetime = -1;

	curPlayer->m_Anim->actData = NULL;
	//curPlayer->m_Anim->moveinfo = NULL;
	//curPlayer->m_Anim->projinfo = NULL;
}

void CPlayer::PreParePalFX(PalFXInfo* palinfo)
{
	m_PalFXinfo = palinfo;
	m_PalFXinfo->nowtime = 0;
}

void CPlayer::PrepareEnvColor(float time, Sint32 r, Sint32 g, Sint32 b, bool isUnder)
{
	m_Evn_color.time = time;
	m_Evn_color.passedtime = 0;
	m_Evn_color.color_r = r;
	m_Evn_color.color_g = g;
	m_Evn_color.color_b = b;
	if (isUnder)
	{
		m_Evn_color.priority = SPR_PRIORITY_ENV_BOTTOM;
	}else{
		m_Evn_color.priority = SPR_PRIORITY_ENV_TOP;
	}
}

void CPlayer::PrepareShake(float time, float freq, float ampl, float phase)
{
	m_shake.time = time;
	m_shake.freq = freq;
	m_shake.ampl = ampl;
	m_shake.phase = phase;
	m_shake.passedtime = 0;
}

bool CPlayer::IsAnimAviable(Sint32 nAnim)
{
	SDL_assert(m_Config!=NULL);
	if(m_Config->GetAir()->GetAction(nAnim) == NULL)
		return false;
	else
		return true;
}

void CPlayer::PrepareAudio(Sint32 nSndGroupNo, Sint32 nSndNo, SndType type)
{
	PrintMessage("time:%5d|ID %d:PrepareAudio %d %d ", CGameTimer::GetInstance()->GetGameTime(), GetPropID(), nSndGroupNo, nSndNo);
	SNDELEMENT* curElement = NULL;
	if (type == SndPlayer)
	{
		curElement = m_Config->GetSnd()->FindSnd(nSndGroupNo, nSndNo);
	}else if (type == SndFight)
	{
		curElement = CConfigManager::GetInstance()->GetSystemConfig()->GetFightConfig()->GetFightSnd()->FindSnd(nSndGroupNo, nSndNo);
	}else if (type == SndCommon)
	{
		curElement = CConfigManager::GetInstance()->GetSystemConfig()->GetFightConfig()->GetCommonSnd()->FindSnd(nSndGroupNo, nSndNo);
	}else if (type == SndSystem)
	{
		curElement = CConfigManager::GetInstance()->GetSystemConfig()->GetSnd()->FindSnd(nSndGroupNo, nSndNo);
	}
	if (curElement == NULL)
	{
		PrintWaring("PrepareAudio fail find %d %d", nSndGroupNo, nSndNo);
		return;
	}
	CSDLManager::GetInstance()->GetAudioSystem()->PlaySound(curElement);
}


Uint32 CPlayer::GetExplodCount(Sint32 explodid)
{
	Uint32 numExplod = 0;
	for(std::vector<ActionForPlay*>::iterator it=m_Explod.begin(); it!=m_Explod.end(); it++)  
	{ 
		ExplodInfo* actData = (ExplodInfo*)((*it)->actData);
		if ((*it)->Anim == NULL)
		{
			continue;
		}
		if (explodid == actData->nExplodID || explodid == -1)
		{
			numExplod ++;
		}
	}
	return numExplod;
}

Uint32 CPlayer::GetProjCount(Sint32 projid)
{
	int numproj = 0;
	for(std::vector<ActionForPlay*>::iterator it=m_Proj.begin(); it!=m_Proj.end(); it++)  
	{ 
		ActionForPlay* act = *it;
		if (act->Anim!=NULL && !act->projinfo->isHited)
		{
			ProjectileInfo* info = (ProjectileInfo*)act->actData;
			if (info->nProjID == projid || projid == -1)
			{
				numproj ++;
			}
		}
	}
	return numproj;
}


Uint32 CPlayer::GetChildCount()
{
	return m_Children->count();
}
CPlayer* CPlayer::GetParent()
{
	if (m_Parent == NULL)
	{
		return this;
	}
	return m_Parent;
}
CPlayer* CPlayer::GetRoot()
{
	if (m_Parent==NULL)
	{
		return this;
	}
	return m_Parent->GetRoot();
}

bool CPlayer::AddChild(CPlayer* player)
{
	player->m_Parent = this;
	m_Children->addObject(player);
	return true;
}

bool CPlayer::RemovePlayer(CPlayer* player)
{
	player->autorelease();
	m_Children->removeObject(player);
	return true;
}

bool CPlayer::RemovePlayerByID(int id)
{
	return true;
}