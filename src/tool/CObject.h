/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __COBJECT_H__
#define __COBJECT_H__

#include "define.h"

class CAutoreleasePool;
class CObject
{
public:
    Uint32        m_uID;
protected:
    Uint32        m_uReference;
    Uint32        m_uAutoReleaseCount;
public:
	CObject(void);
    virtual ~CObject(void);
    
    void release(void);
    void retain(void);
    CObject* autorelease(void);
    bool isSingleReference(void) const;
    unsigned int retainCount(void) const;
    virtual bool isEqual(const CObject* pObject);

    virtual void update(float dt) {};
    friend class CAutoreleasePool;
};



#endif // __COBJECT_H__
