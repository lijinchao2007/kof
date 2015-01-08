/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "CAutoreleasePool.h"
#include "ccMacros.h"
#include <typeinfo>

static CPoolManager* s_pPoolManager = NULL;

CAutoreleasePool::CAutoreleasePool(void)
{
	m_pManagedObjectArray = new CArray();
	m_pManagedObjectArray->init();
}

CAutoreleasePool::~CAutoreleasePool(void)
{
	CC_SAFE_DELETE(m_pManagedObjectArray);
}

void CAutoreleasePool::addObject(CObject* pObject)
{
	m_pManagedObjectArray->addObject(pObject);

	CAssert(pObject->m_uReference > 1, "reference count should be greater than 1");
	++(pObject->m_uAutoReleaseCount);
	pObject->release(); // no ref count, in this case autorelease pool added.
}

void CAutoreleasePool::removeObject(CObject* pObject)
{
	for (unsigned int i = 0; i < pObject->m_uAutoReleaseCount; ++i)
	{
		m_pManagedObjectArray->removeObject(pObject, false);
	}
}

void CAutoreleasePool::clear()
{
	if(m_pManagedObjectArray->count() > 0)
	{
		CObject* pObj = NULL;
		CARRAY_FOREACH_REVERSE(m_pManagedObjectArray, pObj)
		{
			if(!pObj)
				break;

			--(pObj->m_uAutoReleaseCount);
		}

		m_pManagedObjectArray->removeAllObjects();
	}
}


//--------------------------------------------------------------------
//
// CPoolManager
//
//--------------------------------------------------------------------

CPoolManager* CPoolManager::sharedPoolManager()
{
	if (s_pPoolManager == NULL)
	{
		s_pPoolManager = new CPoolManager();
	}
	return s_pPoolManager;
}

void CPoolManager::purgePoolManager()
{
	CC_SAFE_DELETE(s_pPoolManager);
}

CPoolManager::CPoolManager()
{
	m_pReleasePoolStack = new CArray();    
	m_pReleasePoolStack->init();
	m_pCurReleasePool = 0;
}

CPoolManager::~CPoolManager()
{

	finalize();

	// we only release the last autorelease pool here 
	m_pCurReleasePool = 0;
	m_pReleasePoolStack->removeObjectAtIndex(0);

	CC_SAFE_DELETE(m_pReleasePoolStack);
	//TODO: also can clear again
}

void CPoolManager::finalize()
{
	if(m_pReleasePoolStack->count() > 0)
	{
		//CAutoreleasePool* pReleasePool;
		CObject* pObj = NULL;
		CARRAY_FOREACH(m_pReleasePoolStack, pObj)
		{
			if(!pObj)
				break;
			CAutoreleasePool* pPool = (CAutoreleasePool*)pObj;
			pPool->clear();
		}
	}
}

void CPoolManager::push()
{
	CAutoreleasePool* pPool = new CAutoreleasePool();       //ref = 1
	m_pCurReleasePool = pPool;

	m_pReleasePoolStack->addObject(pPool);                   //ref = 2

	pPool->release();                                       //ref = 1
}

void CPoolManager::pop()
{
	if (! m_pCurReleasePool)
	{
		return;
	}

	int nCount = m_pReleasePoolStack->count();

	m_pCurReleasePool->clear();

	if(nCount > 1)
	{
		m_pReleasePoolStack->removeObjectAtIndex(nCount-1);
		m_pCurReleasePool = (CAutoreleasePool*)m_pReleasePoolStack->objectAtIndex(nCount - 2);
	}

	/*m_pCurReleasePool = NULL;*/
}

void CPoolManager::removeObject(CObject* pObject)
{
	CAssert(m_pCurReleasePool, "current auto release pool should not be null");

	m_pCurReleasePool->removeObject(pObject);
}

void CPoolManager::addObject(CObject* pObject)
{
	getCurReleasePool()->addObject(pObject);
}


CAutoreleasePool* CPoolManager::getCurReleasePool()
{
	if(!m_pCurReleasePool)
	{
		push();
	}

	CAssert(m_pCurReleasePool, "current auto release pool should not be null");

	return m_pCurReleasePool;
}

//--------------------------------------------------------------------
//
// CObjCountManager
//
//--------------------------------------------------------------------
static CObjCountManager* s_pObjCountManager = NULL;
CObjCountManager* CObjCountManager::sharedManager()
{
	if (s_pObjCountManager == NULL)
	{
		s_pObjCountManager = new CObjCountManager();
	}
	return s_pObjCountManager;
}

bool CObjCountManager::removeObjForCount(CObject* pObj)
{
	std::vector<CObject*>::iterator iter;
	for (iter=m_ObjCountList.begin();iter!=m_ObjCountList.end();iter++)
	{
		if (pObj == *iter)
		{
			m_ObjCountList.erase(iter);
			return true;
		}
	}
	return false;

}
void CObjCountManager::addObjForCount(CObject* pObject)
{
	m_ObjCountList.push_back(pObject);

}
void CObjCountManager::printInfo()
{
	
	PrintMessage("==============================================");
	/*std::vector<CObject*>::iterator iter;
	for (iter=m_ObjCountList.begin();iter!=m_ObjCountList.end();iter++)
	{
		CObject* tmp = *iter;
		PrintMessage("id %d| classname :%s",tmp->m_uID, typeid(*tmp).name());
	}*/
	PrintMessage("CPoolManager obj %d ", m_ObjCountList.size());
	PrintMessage("==============================================");
}