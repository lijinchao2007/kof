/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "SystemManager.h"
#include "GameTimer.h"
#include "config/ConfigManager.h"
#include "driver/SDLManager.h"
#include "engine.h"
#include "cocos.h"
#include "ui/GameLayer.h"
#include "game.h"


CSysManager* CSysManager::GetInstance()
{
	if (g_pSysManager == NULL)
	{
		g_pSysManager = new CSysManager();
	}
	return g_pSysManager;
}

void CSysManager::Destroy()
{
	PrintMessage("Destroy CSysManager");
	CC_SAFE_DELETE(g_pSysManager);
}

CSysManager::CSysManager()
{
	m_pAlloc = CMemManager::GetInstance()->GetAllocater("CSysManager");
	m_sysConfig = CConfigManager::GetInstance()->GetSystemConfig();
}

CSysManager::~CSysManager()
{
	m_pAlloc->FreeAllocater();
}


void CSysManager::ChangeToFight()
{
	const char* str1 = "kof";
	const char* str2 = "kof";
	CEngine::GetInstance()->SetPlayerName(str1,str2);
	CCScene* scene = CCScene::create();
	scene->addChild(GameLayer::create());
	CCDirector::sharedDirector()->replaceScene(scene);
}



void CSysManager::InitSelect()
{
	CSceneAirConfig* config = m_sysConfig->GetAirConfig();
	BG_DEF* bgDef = config->m_selectBG;
	BG_ELEMENT* curElement = bgDef->elements;
	for (int i=0;i<bgDef->elementSize;i++,curElement++)
	{
		if (curElement->type == BG_TYPE_ANIM)
		{
			PrepareBackAnim(curElement);
		}
	}

	//create spr

}

void CSysManager::RunSelect()
{
	CSceneAirConfig* config = m_sysConfig->GetAirConfig();
	CSffManager* sff = m_sysConfig->GetSff();

	Sint32 halfWidth = Common_GetDesiginHalfWidth();
	BG_DEF* bgDef = config->m_selectBG;
	BG_ELEMENT* curElement = bgDef->elements;
	for (int i=0;i<bgDef->elementSize;i++,curElement++)
	{
		if (curElement->type == BG_TYPE_NORMAL)
		{
			Uint32 nGroupNumber = curElement->GroubNumber;
			Uint32 nImageNumber = curElement->ImageNumber;
			SFFSPRITE *spr = sff->FindSprite(nGroupNumber,nImageNumber);
			if(spr==NULL)
				continue;
			Sint32 scX = curElement->nStartX + halfWidth;
			Sint32 scY = curElement->nStartY;
			DrawInfo info;
			float ChooseSceneScale = CConfigManager::GetInstance()->GetFloat("Rules.ChooseSceneScale");
			info.nScaleX = info.nScaleY = ChooseSceneScale;
			info.spr = spr;
			info.pal = NULL;
			info.nScreenPosX = scX;
			info.nScreenPosY = scY;
			info.bDrawBack = !curElement->bMask;

			int sprProi = 0;
			if (curElement->nLayerNo == 0)
			{
				sprProi = SPR_PRIORITY_STAGE_BOTTOM;
			}else{
				sprProi = SPR_PRIORITY_STAGE_TOP;
			}
			
			CSDLManager::GetInstance()->GetVideoSystem()->NormalBlt(info, NULL, sprProi);
		}
	}

	// run act
	for(std::vector<ActionForPlay*>::iterator it=m_AnimVector.begin(); it!=m_AnimVector.end(); it++)  
	{ 
		UpdateBackAnim(*it);
		DrawBackAct(*it);
	}

	CSDLManager::GetInstance()->GetVideoSystem()->DrawText(0,0,"FPS:%5.2f",CGame::GetInstance()->GetPropFps());
	CSDLManager::GetInstance()->GetVideoSystem()->Render();
}


//prepares the animation
void CSysManager::PrepareBackAnim(BG_ELEMENT* curElement)
{
	Uint32 nAnimNo = curElement->nAnimNo;
	CSceneAirConfig* config = m_sysConfig->GetAirConfig();
	ActionElement* tmp = config->GetAction(nAnimNo);
	if (tmp== NULL ){
		return;
	}

	ActionForPlay* curAct = NULL;
	for(std::vector<ActionForPlay*>::iterator it=m_AnimVector.begin(); it!=m_AnimVector.end(); it++)  
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
		m_AnimVector.push_back(curAct);
	}

	PrintMessage("PrepareSysAnim nAnim %d ",nAnimNo);
	curAct->Anim = tmp;
	curAct->nAnim = nAnimNo;
	curAct->nCurrentImage=CUR_IMAGE_INDEX_START;
	curAct->nCurrentImageTime=CUR_IMAGE_TIME_START;
	curAct->nCurrTime=CUR_TIME_START;
	curAct->nCurrTimeInAnim=CUR_TIME_START;

	curAct->type = AnimBack;
	curAct->acttype = ActBack;
	curAct->bgInfo = curElement;
	curAct->nRemovetime = -1;
}



void CSysManager::UpdateBackAnim(ActionForPlay* act)
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
			}
		}
	}
}

void CSysManager::DrawBackAct(ActionForPlay* act)
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

	SFFSPRITE *spr = m_sysConfig->GetSff()->FindSprite(nGroupNumber,nImageNumber);
	if(spr==NULL)
		return;

	Sint32 halfWidth = Common_GetDesiginHalfWidth();
	Sint32 scX = act->bgInfo->nStartX + halfWidth;
	Sint32 scY = act->bgInfo->nStartY;
	DrawInfo info;
	float ChooseSceneScale = CConfigManager::GetInstance()->GetFloat("Rules.ChooseSceneScale");
	info.nScaleX = info.nScaleY = ChooseSceneScale;
	info.spr = spr;
	info.pal = NULL;
	info.nScreenPosX = scX + DeltaX;
	info.nScreenPosY = scY + DeltaY;
	info.bDrawBack = 0;
	info.transMode = sprTransType;
	info.srcAlpha = srcAlpha;
	info.desAlpha = desAlpha;
	info.flip = FlipFlags;

	int sprProi = 0;
	if (act->bgInfo->nLayerNo == 0)
	{
		sprProi = SPR_PRIORITY_STAGE_BOTTOM;
	}else{
		sprProi = SPR_PRIORITY_STAGE_TOP;
	}


	CSDLManager::GetInstance()->GetVideoSystem()->NormalBlt(info, NULL, sprProi);
}