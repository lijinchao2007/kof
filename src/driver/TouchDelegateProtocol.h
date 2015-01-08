/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __TOUCH_DISPATHCHER_CTouch_DELEGATE_PROTOCOL_H__
#define __TOUCH_DISPATHCHER_CTouch_DELEGATE_PROTOCOL_H__
#include "tool/Touch.h"

class CTouchDelegate
{

public:
	bool m_touchEnabled;
    CTouchDelegate() {
		m_touchEnabled = false;
	}

    virtual ~CTouchDelegate()
    {
    }

    virtual bool CTouchBegan(CTouch* pTouch) { return false;};
    virtual void CTouchMoved(CTouch* pTouch) {}
    virtual void CTouchEnded(CTouch* pTouch) {}
    virtual void CTouchCancelled(CTouch* pTouch) {}
};

#endif // __TOUCH_DISPATHCHER_CTouch_DELEGATE_PROTOCOL_H__
