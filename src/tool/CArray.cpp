/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "CArray.h"
#include <math.h>

CArray::CArray()
: data(NULL)
{
    init();
}

CArray::CArray(unsigned int capacity)
: data(NULL)
{
    initWithCapacity(capacity);
}

CArray* CArray::create()
{
    CArray* pArray = new CArray();

    if (pArray && pArray->init())
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }
    
    return pArray;
}

CArray* CArray::createWithObject(CObject* pObject)
{
    CArray* pArray = new CArray();

    if (pArray && pArray->initWithObject(pObject))
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }

    return pArray;
}

CArray* CArray::create(CObject* pObject, ...)
{
    va_list args;
    va_start(args,pObject);

    CArray* pArray = create();
    if (pArray && pObject)
    {
        pArray->addObject(pObject);
        CObject *i = va_arg(args, CObject*);
        while(i) 
        {
            pArray->addObject(i);
            i = va_arg(args, CObject*);
        }
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }

    va_end(args);

    return pArray;
}


CArray* CArray::createWithCapacity(unsigned int capacity)
{
    CArray* pArray = new CArray();
    
    if (pArray && pArray->initWithCapacity(capacity))
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }
    
    return pArray;
}


bool CArray::init()
{
    return initWithCapacity(1);
}

bool CArray::initWithObject(CObject* pObject)
{
    ccArrayFree(data);
    bool bRet = initWithCapacity(1);
    if (bRet)
    {
        addObject(pObject);
    }
    return bRet;
}

/** Initializes an array with some objects */
bool CArray::initWithObjects(CObject* pObject, ...)
{
    ccArrayFree(data);
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(pObject == NULL);

        va_list args;
        va_start(args, pObject);

        if (pObject)
        {
            this->addObject(pObject);
            CObject* i = va_arg(args, CObject*);
            while(i) 
            {
                this->addObject(i);
                i = va_arg(args, CObject*);
            }
            bRet = true;
        }
        va_end(args);

    } while (false);

    return bRet;
}

bool CArray::initWithCapacity(unsigned int capacity)
{
    ccArrayFree(data);
    data = ccArrayNew(capacity);
    return true;
}

bool CArray::initWithArray(CArray* otherArray)
{
    ccArrayFree(data);
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! initWithCapacity(otherArray->data->num));

        addObjectsFromArray(otherArray);
        bRet = true;
    } while (0);
    
    return bRet;
}

unsigned int CArray::count() const
{
    return data->num;
}

unsigned int CArray::capacity() const
{
    return data->max;
}

unsigned int CArray::indexOfObject(CObject* object) const
{
    return ccArrayGetIndexOfObject(data, object);
}

CObject* CArray::objectAtIndex(unsigned int index)
{
    CAssert(index < data->num, "index out of range in objectAtIndex()");

    return data->arr[index];
}

CObject* CArray::lastObject()
{
    if( data->num > 0 )
        return data->arr[data->num-1];

    return NULL;
}

CObject* CArray::randomObject()
{
    if (data->num==0)
    {
        return NULL;
    }

    float r = CCRANDOM_0_1();
    
    if (r == 1) // to prevent from accessing data-arr[data->num], out of range.
    {
        r = 0;
    }
    
    return data->arr[(int)(data->num * r)];
}

bool CArray::containsObject(CObject* object) const
{
    return ccArrayContainsObject(data, object);
}

bool CArray::isEqualToArray(CArray* otherArray)
{
    for (unsigned int i = 0; i< this->count(); i++)
    {
        if (!this->objectAtIndex(i)->isEqual(otherArray->objectAtIndex(i)))
        {
            return false;
        }
    }
    return true;
}

void CArray::addObject(CObject* object)
{
    ccArrayAppendObjectWithResize(data, object);
}

void CArray::addObjectsFromArray(CArray* otherArray)
{
    ccArrayAppendArrayWithResize(data, otherArray->data);
}

void CArray::insertObject(CObject* object, unsigned int index)
{
    ccArrayInsertObjectAtIndex(data, object, index);
}

void CArray::removeLastObject(bool bReleaseObj)
{
    CAssert(data->num, "no objects added");
    ccArrayRemoveObjectAtIndex(data, data->num-1, bReleaseObj);
}

void CArray::removeObject(CObject* object, bool bReleaseObj/* = true*/)
{
    ccArrayRemoveObject(data, object, bReleaseObj);
}

void CArray::removeObjectAtIndex(unsigned int index, bool bReleaseObj)
{
    ccArrayRemoveObjectAtIndex(data, index, bReleaseObj);
}

void CArray::removeObjectsInArray(CArray* otherArray)
{
    ccArrayRemoveArray(data, otherArray->data);
}

void CArray::removeAllObjects()
{
    ccArrayRemoveAllObjects(data);
}

void CArray::fastRemoveObjectAtIndex(unsigned int index)
{
    ccArrayFastRemoveObjectAtIndex(data, index);
}

void CArray::fastRemoveObject(CObject* object)
{
    ccArrayFastRemoveObject(data, object);
}

void CArray::exchangeObject(CObject* object1, CObject* object2)
{
    unsigned int index1 = ccArrayGetIndexOfObject(data, object1);
    if(index1 == CC_INVALID_INDEX)
    {
        return;
    }

    unsigned int index2 = ccArrayGetIndexOfObject(data, object2);
    if(index2 == CC_INVALID_INDEX)
    {
        return;
    }

    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void CArray::exchangeObjectAtIndex(unsigned int index1, unsigned int index2)
{
    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void CArray::replaceObjectAtIndex(unsigned int index, CObject* pObject, bool bReleaseObject/* = true*/)
{
    ccArrayInsertObjectAtIndex(data, pObject, index);
    ccArrayRemoveObjectAtIndex(data, index+1);
}

void CArray::reverseObjects()
{
    if (data->num > 1)
    {
        // floorf(), since in the case of an even number, the number of swaps stays the same
        int count = (int) floorf(data->num/2.f); 
        unsigned int maxIndex = data->num - 1;

        for (int i = 0; i < count ; i++)
        {
            ccArraySwapObjectsAtIndexes(data, i, maxIndex);
            maxIndex--;
        }
    }
}

void CArray::reduceMemoryFootprint()
{
    ccArrayShrink(data);
}

CArray::~CArray()
{
    ccArrayFree(data);
}



