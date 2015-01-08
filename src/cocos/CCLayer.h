/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __CCLAYER_H__
#define __CCLAYER_H__
#include <map>
#include "CCNode.h"
#include "driver/TouchDelegateProtocol.h"

class CCLayer : public CCNode, public CTouchDelegate
{
public:
    CCLayer();
    virtual ~CCLayer();
    virtual bool init();
    
    /** create one layer */
    static CCLayer *create(void);
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();


	virtual bool CTouchBegan(CTouch* pTouch);
	virtual void CTouchMoved(CTouch* pTouch);
	virtual void CTouchEnded(CTouch* pTouch);
	virtual void CTouchCancelled(CTouch* pTouch);

public:
	CTouchDelegate* m_SwallowTouchs[CC_MAX_TOUCHES+1];
};

#endif // __CCLAYER_H__

