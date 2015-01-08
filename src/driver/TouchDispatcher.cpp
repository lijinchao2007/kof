/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "TouchDispatcher.h"
#include "Input.h"

CTouchDispatcher* CTouchDispatcher::GetInstance()
{
	if ( pTouchDispatcherInstance == NULL )  
	{
		pTouchDispatcherInstance = new CTouchDispatcher();
	}
	return pTouchDispatcherInstance;
}

void CTouchDispatcher::Destroy()
{
	CC_SAFE_DELETE(pTouchDispatcherInstance);
}

bool CTouchDispatcher::init(void)
{
	CInput::GetInstance()->SetPropTouchDelegate(this);
	m_pHandlers = CArray::createWithCapacity(4);
	m_pHandlers->retain();
    return true;
}

CTouchDispatcher::~CTouchDispatcher(void)
{
	CInput::GetInstance()->SetPropTouchDelegate(NULL);
	CC_SAFE_RELEASE(m_pHandlers);
}

void CTouchDispatcher::addDelegate(CObject *pDelegate)
{   
	m_pHandlers->addObject((CObject*)pDelegate);
}

void CTouchDispatcher::removeDelegate(CObject *pDelegate)
{
	CObject* handler = (CObject*) pDelegate;
	if (m_pHandlers->containsObject(handler))
	{
		m_pHandlers->removeObject(handler);
	}
}

void CTouchDispatcher::removeAllDelegates()
{
	m_pHandlers->removeAllObjects();
}



bool CTouchDispatcher::CTouchBegan(CTouch* pTouch)
{
	CObject* pObj = NULL;
	CTouchDelegate* pHander = NULL;
	CARRAY_FOREACH(m_pHandlers, pObj)
	{
		pHander =  dynamic_cast<CTouchDelegate*>(pObj);
		if (pHander == NULL)
		{
			PrintWaring("pHander is not CTouchDelegate type");
		}
		pHander->CTouchBegan(pTouch);
	}
	return false;
}
void CTouchDispatcher::CTouchMoved(CTouch* pTouch)
{
	CObject* pObj = NULL;
	CTouchDelegate* pHander = NULL;
	CARRAY_FOREACH(m_pHandlers, pObj)
	{
		pHander =  dynamic_cast<CTouchDelegate*>(pObj);
		if (pHander == NULL)
		{
			PrintWaring("pHander is not CTouchMoved type");
		}
		pHander->CTouchMoved(pTouch);
	}
}
void CTouchDispatcher::CTouchEnded(CTouch* pTouch)
{
	CObject* pObj = NULL;
	CTouchDelegate* pHander = NULL;
	CARRAY_FOREACH(m_pHandlers, pObj)
	{
		pHander =  dynamic_cast<CTouchDelegate*>(pObj);
		if (pHander == NULL)
		{
			PrintWaring("pHander is not CTouchEnded type");
		}
		pHander->CTouchEnded(pTouch);
	}
}
void CTouchDispatcher::CTouchCancelled(CTouch* pTouch)
{
	CObject* pObj = NULL;
	CTouchDelegate* pHander = NULL;
	CARRAY_FOREACH(m_pHandlers, pObj)
	{
		pHander =  dynamic_cast<CTouchDelegate*>(pObj);
		if (pHander == NULL)
		{
			PrintWaring("pHander is not CTouchCancelled type");
		}
		pHander->CTouchCancelled(pTouch);
	}
}