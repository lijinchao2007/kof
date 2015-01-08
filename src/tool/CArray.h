/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __CArray_H__
#define __CArray_H__

#include "ccCArray.h"

/**
 * @addtogroup data_structures
 * @{
 */

/** @def CARRAY_FOREACH
A convenience macro to iterate over a CArray using. It is faster than the "fast enumeration" interface.
@since v0.99.4
*/

/*
In cocos2d-iphone 1.0.0, This macro have been update to like this:

#define CARRAY_FOREACH(__array__, __object__)                                                \
if (__array__ && __array__->data->num > 0)                                                    \
for(id *__arr__ = __array__->data->arr, *end = __array__->data->arr + __array__->data->num-1;    \
__arr__ <= end && ((__object__ = *__arr__) != nil || true);                                        \
__arr__++)

I found that it's not work in C++. So it keep what it's look like in version 1.0.0-rc3. ---By Bin
*/
#define CARRAY_FOREACH(__array__, __object__)                                                                         \
    if ((__array__) && (__array__)->data->num > 0)                                                                     \
    for(CObject** __arr__ = (__array__)->data->arr, **__end__ = (__array__)->data->arr + (__array__)->data->num-1;    \
    __arr__ <= __end__ && (((__object__) = *__arr__) != NULL/* || true*/);                                             \
    __arr__++)

#define CARRAY_FOREACH_REVERSE(__array__, __object__)                                                                  \
    if ((__array__) && (__array__)->data->num > 0)                                                                      \
    for(CObject** __arr__ = (__array__)->data->arr + (__array__)->data->num-1, **__end__ = (__array__)->data->arr;     \
    __arr__ >= __end__ && (((__object__) = *__arr__) != NULL/* || true*/);                                              \
    __arr__--)

#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
#define CArray_VERIFY_TYPE(__array__, __type__)                                                                 \
    do {                                                                                                         \
        if ((__array__) && (__array__)->data->num > 0)                                                           \
            for(CObject** __arr__ = (__array__)->data->arr,                                                     \
                **__end__ = (__array__)->data->arr + (__array__)->data->num-1; __arr__ <= __end__; __arr__++)    \
                CCAssert(dynamic_cast<__type__>(*__arr__), "element type is wrong!");                            \
    } while(false)
#else
#define CArray_VERIFY_TYPE(__array__, __type__) void(0)
#endif

#define arrayMakeObjectsPerformSelector(pArray, func, elementType)    \
do {                                                                  \
    if(pArray && pArray->count() > 0)                                 \
    {                                                                 \
        CObject* child;                                              \
        CARRAY_FOREACH(pArray, child)                                \
        {                                                             \
            elementType pNode = (elementType) child;                  \
            if(pNode)                                                 \
            {                                                         \
                pNode->func();                                        \
            }                                                         \
        }                                                             \
    }                                                                 \
}                                                                     \
while(false)

#define arrayMakeObjectsPerformSelectorWithObject(pArray, func, pObject, elementType)   \
do {                                                                  \
    if(pArray && pArray->count() > 0)                                 \
    {                                                                 \
        CObject* child = NULL;                                       \
        CARRAY_FOREACH(pArray, child)                                \
        {                                                             \
            elementType pNode = (elementType) child;                  \
            if(pNode)                                                 \
            {                                                         \
                pNode->func(pObject);                                 \
            }                                                         \
        }                                                             \
    }                                                                 \
}                                                                     \
while(false)

#include "CObject.h"
class CArray : public CObject
{
public:
    ~CArray();

    static CArray* create();
    static CArray* create(CObject* pObject, ...);
    static CArray* createWithObject(CObject* pObject);
    static CArray* createWithCapacity(unsigned int capacity);

	/** Initializes an array 
     *  @lua NA
     */
    bool init();
    /** Initializes an array with one object
     *  @lua NA
     */
    bool initWithObject(CObject* pObject);
    /** Initializes an array with some objects 
     *  @lua NA
     */
    bool initWithObjects(CObject* pObject, ...);
    /** Initializes an array with capacity 
     *  @lua NA
     */
    bool initWithCapacity(unsigned int capacity);
    /** Initializes an array with an existing array 
     *  @lua NA
     */
    bool initWithArray(CArray* otherArray);

    // Querying an Array

    /** Returns element count of the array */
    unsigned int count() const;
    /** Returns capacity of the array */
    unsigned int capacity() const;
    /** Returns index of a certain object, return UINT_MAX if doesn't contain the object */
    unsigned int indexOfObject(CObject* object) const;
    /** Returns an element with a certain index */
    CObject* objectAtIndex(unsigned int index);
    /** Returns last element */
    CObject* lastObject();
    /** Returns a random element */
    CObject* randomObject();
    /** Returns a Boolean value that indicates whether object is present in array. */
    bool containsObject(CObject* object) const;
    /** @since 1.1 */
    bool isEqualToArray(CArray* pOtherArray);
    // Adding Objects

    /** Add a certain object */
    void addObject(CObject* object);
    /** Add all elements of an existing array */
    void addObjectsFromArray(CArray* otherArray);
    /** Insert a certain object at a certain index */
    void insertObject(CObject* object, unsigned int index);

    // Removing Objects

    /** Remove last object */
    void removeLastObject(bool bReleaseObj = true);
    /** Remove a certain object */
    void removeObject(CObject* object, bool bReleaseObj = true);
    /** Remove an element with a certain index */
    void removeObjectAtIndex(unsigned int index, bool bReleaseObj = true);
    /** Remove all elements */
    void removeObjectsInArray(CArray* otherArray);
    /** Remove all objects */
    void removeAllObjects();
    /** Fast way to remove a certain object */
    void fastRemoveObject(CObject* object);
    /** Fast way to remove an element with a certain index */
    void fastRemoveObjectAtIndex(unsigned int index);

    // Rearranging Content

    /** Swap two elements */
    void exchangeObject(CObject* object1, CObject* object2);
    /** Swap two elements with certain indexes */
    void exchangeObjectAtIndex(unsigned int index1, unsigned int index2);

    /** Replace object at index with another object. */
    void replaceObjectAtIndex(unsigned int uIndex, CObject* pObject, bool bReleaseObject = true);

    /** Revers the array */
    void reverseObjects();
    /* Shrinks the array so the memory footprint corresponds with the number of items */
    void reduceMemoryFootprint();
  

public:
    ccArray* data;
    /**
     *  @lua NA
     */
    CArray();
    /**
     *  @lua NA
     */
    CArray(unsigned int capacity);
};



#endif // __CArray_H__
