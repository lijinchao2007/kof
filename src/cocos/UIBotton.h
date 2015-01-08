/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __UIBOTTON_H_
#define __UIBOTTON_H_
#include "tool.h"
#include "Sprite.h"
#include "driver/TouchDelegateProtocol.h"

class CUIBotton;
typedef void (CObject::*SEL_CallFunc)(CUIBotton* btn, CTouch* pTouch);
//typedef void (CCObject::*SEL_SCHEDULE)(float);
//typedef void (CCObject::*SEL_CallFunc)();
//typedef void (CCObject::*SEL_CallFuncN)(CCNode*);
//typedef void (CCObject::*SEL_CallFuncND)(CCNode*, void*);
//typedef void (CCObject::*SEL_CallFuncO)(CCObject*);
//typedef void (CCObject::*SEL_MenuHandler)(CCObject*);
//typedef void (CCObject::*SEL_EventHandler)(CCEvent*);
//typedef int (CCObject::*SEL_Compare)(CCObject*);
//
//#define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(&_SELECTOR)
//#define callfunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)


class CUIBotton:public CSprite, public CTouchDelegate
{
public:
	CUIBotton();
	virtual ~CUIBotton();
	static CUIBotton *create(const char* path);
	static CUIBotton *create(SFFSPRITE* spr);

	virtual bool CTouchBegan(CTouch* pTouch);
	virtual void CTouchMoved(CTouch* pTouch);
	virtual void CTouchEnded(CTouch* pTouch);
	virtual void CTouchCancelled(CTouch* pTouch);

	void SetTouchBeganCB(CObject* obj, SEL_CallFunc cb){m_Ojb1 = obj;m_TouchBeganCB = cb;};
	void SetTouchMovedCB(CObject* obj, SEL_CallFunc cb){m_Ojb2 = obj;m_TouchMovedCB = cb;};
	void SetTouchEndCB(CObject* obj, SEL_CallFunc cb){m_Ojb3 = obj;m_TouchEndCB = cb;};
protected:
	bool m_Touched;
	CObject* m_Ojb1;
	CObject* m_Ojb2;
	CObject* m_Ojb3;
	SEL_CallFunc m_TouchBeganCB;
	SEL_CallFunc m_TouchMovedCB;
	SEL_CallFunc m_TouchEndCB;
};
#endif