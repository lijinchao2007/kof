/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __TOUCH_DISPATCHER_CCTOUCH_DISPATCHER_H__
#define __TOUCH_DISPATCHER_CCTOUCH_DISPATCHER_H__

#include "TouchDelegateProtocol.h"
#include "tool.h"

class CTouchDispatcher : public CObject, public CTouchDelegate
{
public:
    ~CTouchDispatcher();
    bool init(void);
    CTouchDispatcher()
    {}

public:

    void addDelegate(CObject *pDelegate);
    void removeDelegate(CObject *pDelegate);
    void removeAllDelegates(void);

	virtual bool CTouchBegan(CTouch* pTouch);
	virtual void CTouchMoved(CTouch* pTouch);
	virtual void CTouchEnded(CTouch* pTouch);
	virtual void CTouchCancelled(CTouch* pTouch);

protected:
     CArray* m_pHandlers;

public:
	static CTouchDispatcher* GetInstance();
	static void Destroy();
};

static CTouchDispatcher* pTouchDispatcherInstance = NULL;

#endif // __TOUCH_DISPATCHER_CCTOUCH_DISPATCHER_H__
