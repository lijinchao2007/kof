/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "FightButton.h"
#include "driver/Input.h"
#include "logic/engine.h"
#include "logic/GameTimer.h"
#include "game.h"

CFightButton::CFightButton()
{
}

CFightButton::~CFightButton()
{

}
CFightButton *CFightButton::create(const char* path)
{
	CFightButton *pRet = new CFightButton();
	if (pRet && pRet->init(path))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}


bool CFightButton::CTouchBegan(CTouch* pTouch)
{
	bool ret = CUIBotton::CTouchBegan(pTouch);
	if (ret)
	{
		PrintMessage("CTouchBegan butontag %d", getTag());
		CInput::GetInstance()->SetVectorKeyData(getTag(), true);
        if (getTag() == KEY_BUTTON_START) {
            CMemManager::GetInstance()->GetMemUsage();
            CEngine::GetInstance()->m_player1->DebugInfoToBack();
            CEngine::GetInstance()->m_player2->DebugInfoToBack();
            CGame::GetInstance()->SetPropIsDebugTime(true);
			int aiLv = CEngine::GetInstance()->m_player2->GetPropAILevel();
			CEngine::GetInstance()->m_player2->SetPropAILevel(!aiLv);
        }
	}
	return ret;
}
void CFightButton::CTouchMoved(CTouch* pTouch)
{
	CUIBotton::CTouchMoved(pTouch);
}
void CFightButton::CTouchEnded(CTouch* pTouch)
{
	PrintMessage("CTouchEnded butontag: %d", getTag());
	CInput::GetInstance()->SetVectorKeyData(getTag(), false);
	CUIBotton::CTouchEnded(pTouch);
}
void CFightButton::CTouchCancelled(CTouch* pTouch)
{
	CInput::GetInstance()->SetVectorKeyData(getTag(), false);
	CUIBotton::CTouchCancelled(pTouch);
}