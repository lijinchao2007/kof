/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "CObject.h"
#include "CAutoreleasePool.h"
#include "ccMacros.h"

CObject::CObject(void)
	: m_uReference(1) // when the object is created, the reference count of it is 1
	, m_uAutoReleaseCount(0)
{
	static Uint32 uObjectCount = 0;
	m_uID = ++uObjectCount;
	CObjCountManager::sharedManager()->addObjForCount(this);
}

CObject::~CObject(void)
{
	// if the object is managed, we should remove it
	// from pool manager
	if (m_uAutoReleaseCount > 0)
	{
		CPoolManager::sharedPoolManager()->removeObject(this);
	}
	if (!CObjCountManager::sharedManager()->removeObjForCount(this))
	{
		CAssert(false, "removeObjForCount fail");
	}
}


void CObject::release(void)
{
	CAssert(m_uReference > 0, "reference count should greater than 0");
	--m_uReference;

	if (m_uReference == 0)
	{
		delete this;
	}
}

void CObject::retain(void)
{
	CAssert(m_uReference > 0, "reference count should greater than 0");

	++m_uReference;
}

CObject* CObject::autorelease(void)
{
	CPoolManager::sharedPoolManager()->addObject(this);
	return this;
}

bool CObject::isSingleReference(void) const
{
	return m_uReference == 1;
}

unsigned int CObject::retainCount(void) const
{
	return m_uReference;
}

bool CObject::isEqual(const CObject *pObject)
{
	return this == pObject;
}
