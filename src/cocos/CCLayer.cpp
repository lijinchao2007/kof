/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "CCLayer.h"
#include "CCDirector.h"
#include "driver/TouchDispatcher.h"

// CCLayer
CCLayer::CCLayer()
{
    //setAnchorPoint(ccp(0, 0));
	SDL_memset(m_SwallowTouchs, 0, sizeof(intptr_t)*(CC_MAX_TOUCHES+1));
}

CCLayer::~CCLayer()
{
}

bool CCLayer::init()
{
    bool bRet = true;
    return bRet;
}

CCLayer *CCLayer::create()
{
    CCLayer *pRet = new CCLayer();
    if (pRet && pRet->init())
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


/// Callbacks
void CCLayer::onEnter()
{
	CTouchDispatcher::GetInstance()->addDelegate(this);
    CCNode::onEnter();
}

void CCLayer::onExit()
{
	CTouchDispatcher::GetInstance()->removeDelegate(this);
    CCNode::onExit();
}

void CCLayer::onEnterTransitionDidFinish()
{
    CCNode::onEnterTransitionDidFinish();
}



bool CCLayer::CTouchBegan(CTouch* pTouch)
{
	//PrintMessage("CTouchBegan");
	if (!m_bVisible)
	{
		return false;
	}
	CTouchDelegate* pHandler = NULL;
	unsigned int i = 0;
	bool bSwallow = false;
	if(m_pChildren && m_pChildren->count() > 0)
	{
		sortAllChildren();
		ccArray *arrayData = m_pChildren->data;
		for( ; i < arrayData->num; i++ )
		{
			pHandler = dynamic_cast<CTouchDelegate*>(arrayData->arr[i]);
			if ( pHandler != NULL ) 
			{
				bSwallow = pHandler->CTouchBegan(pTouch);
				if (bSwallow)
				{
					m_SwallowTouchs[pTouch->getID()] = pHandler;
					return  true;
				}
			}
		}
	}
	return false;
}
void CCLayer::CTouchMoved(CTouch* pTouch)
{
	CTouchDelegate* pHandler = m_SwallowTouchs[pTouch->getID()];
	if (pHandler != NULL)
	{
		pHandler->CTouchMoved(pTouch);
	}
}
void CCLayer::CTouchEnded(CTouch* pTouch)
{
	CTouchDelegate* pHandler = m_SwallowTouchs[pTouch->getID()];
	if (pHandler != NULL)
	{
		pHandler->CTouchEnded(pTouch);
		m_SwallowTouchs[pTouch->getID()] = NULL;
	}
}
void CCLayer::CTouchCancelled(CTouch* pTouch)
{
	CTouchDelegate* pHandler = m_SwallowTouchs[pTouch->getID()];
	if (pHandler != NULL)
	{
		pHandler->CTouchCancelled(pTouch);
		m_SwallowTouchs[pTouch->getID()] = NULL;
	}
}