/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "CCScene.h"
#include "CCDirector.h"


CCScene::CCScene()
{
    //setAnchorPoint(ccp(0.0f, 0.0f));
}

CCScene::~CCScene()
{
}

bool CCScene::init()
{
    bool bRet = false;
     do 
     {
         CCDirector * pDirector;
         CC_BREAK_IF( ! (pDirector = CCDirector::sharedDirector()) );
         bRet = true;
     } while (0);
     return bRet;
}

CCScene *CCScene::create()
{
    CCScene *pRet = new CCScene();
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

