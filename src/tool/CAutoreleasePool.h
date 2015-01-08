/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __AUTORELEASEPOOL_H__
#define __AUTORELEASEPOOL_H__

#include "CObject.h"
#include "CArray.h"
#include <vector>

class CAutoreleasePool : public CObject
{
    CArray*    m_pManagedObjectArray;    
public:
    CAutoreleasePool(void);
    ~CAutoreleasePool(void);

    void addObject(CObject *pObject);
    void removeObject(CObject *pObject);

    void clear();
};

class CPoolManager
{
	CArray*    m_pReleasePoolStack;    
    CAutoreleasePool*                    m_pCurReleasePool;
    CAutoreleasePool* getCurReleasePool();
public:
    CPoolManager();
    ~CPoolManager();
    void finalize();
    void push();
    void pop();

    void removeObject(CObject* pObject);
    void addObject(CObject* pObject);

    static CPoolManager* sharedPoolManager();
    static void purgePoolManager();

    friend class CAutoreleasePool;
};


class CObjCountManager
{
	std::vector<CObject*>    m_ObjCountList;    
public:
	CObjCountManager(){};
	~CObjCountManager(){};

	// count obj
	bool removeObjForCount(CObject* pObj);
	void addObjForCount(CObject* pObject);
	void printInfo();
	static CObjCountManager* sharedManager();
};

#endif //__AUTORELEASEPOOL_H__
