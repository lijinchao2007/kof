/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __CDictionary_H__
#define __CDictionary_H__

#include "uthash.h"
#include "CObject.h"
#include "CArray.h"
#include "CString.h"


class CDictionary;

/**
 * @addtogroup data_structures
 * @{
 */


/**
 *  CDictElement is used for traversing CDictionary.
 *
 *  A CDictElement is one element of CDictionary, it contains two properties, key and object.
 *  Its key has two different type (integer and string).
 *
 *  @note The key type is unique, all the elements in CDictionary has the same key type(integer or string).
 *  @code
 *  CDictElement* pElement;
 *  CCDICT_FOREACH(dict, pElement)
 *  {
 *      const char*key = pElement->getStrKey();
 *      // You certainly know the type of value, so we assume that it's a CCSprite.
 *      CCSprite* pSprite = (CCSprite*)pElement->getObject();
 *      // ......
 *  }
 *  @endcode
 *  @js NA
 *  @lua NA
 */
class CDictElement
{
private:
    /**
     *  Constructor of CDictElement. It's only for internal usage. CDictionary is its friend class.
     *  
     *  @param  pszKey    The string key of this element.
     *  @param  pObject   The object of this element.
     */
    CDictElement(const char* pszKey, CObject* pObject);

    /**
     *  Constructor of CDictElement. It's only for internal usage. CDictionary is its friend class.
     *
     *  @param  iKey    The integer key of this element.
     *  @param  pObject   The object of this element.
     */
    CDictElement(intptr_t iKey, CObject* pObject);
    
public:
    /**
     *  The destructor of CDictElement.
     */
    ~CDictElement();

    // Inline functions need to be implemented in header file on Android.
    
    /**
     * Get the string key of this element.
     * @note    This method assumes you know the key type in the element. 
     *          If the element's key type is integer, invoking this method will cause an assert.
     *
     * @return  The string key of this element.
     */
    inline const char* getStrKey() const
    {
        CAssert(m_szKey[0] != '\0', "Should not call this function for integer dictionary");
        return m_szKey;
    }

    /**
     * Get the integer key of this element.
     * @note    This method assumes you know the key type in the element.
     *          If the element's key type is string, invoking this method will cause an assert.
     *
     * @return  The integer key of this element.
     */
    inline intptr_t getIntKey() const
    {
        CAssert(m_szKey[0] == '\0', "Should not call this function for string dictionary");
        return m_iKey;
    }
    
    /**
     * Get the object of this element.
     *
     * @return  The object of this element.
     */
    inline CObject* getObject() const { return m_pObject; }

private:
    // The max length of string key.
    #define   MAX_KEY_LEN   256
    // char array is needed for HASH_ADD_STR in UT_HASH.
    // So it's a pain that all elements will allocate 256 bytes for this array.
    char      m_szKey[MAX_KEY_LEN];     // hash key of string type
    intptr_t  m_iKey;       // hash key of integer type
    CObject* m_pObject;    // hash value
public:
    UT_hash_handle hh;      // makes this class hashable
    friend class CDictionary; // declare CDictionary as friend class
};

/** The macro for traversing dictionary
 *  
 *  @note It's faster than getting all keys and traversing keys to get objects by objectForKey.
 *        It's also safe to remove elements while traversing.
 */
#define CCDICT_FOREACH(__dict__, __el__) \
    CDictElement* pTmp##__dict__##__el__ = NULL; \
    if (__dict__) \
    HASH_ITER(hh, (__dict__)->m_pElements, __el__, pTmp##__dict__##__el__)



/**
 *  CDictionary is a class like NSDictionary in Obj-C .
 *
 *  @note Only the pointer of CObject or its subclass can be inserted to CDictionary.
 *  @code
 *  // Create a dictionary, return an autorelease object.
 *  CDictionary* pDict = CDictionary::create();
 *
 *  // Insert objects to dictionary
 *  CString* pValue1 = CString::create("100");
 *  CString* pValue2 = CString::create("120");
 *  CCInteger* pValue3 = CCInteger::create(200);
 *  pDict->setObject(pValue1, "key1");
 *  pDict->setObject(pValue2, "key2");
 *  pDict->setObject(pValue3, "key3");
 *
 *  // Get the object for key
 *  CString* pStr1 = (CString*)pDict->objectForKey("key1");
 *  CCLog("{ key1: %s }", pStr1->getCString());
 *  CCInteger* pInteger = (CCInteger*)pDict->objectForKey("key3");
 *  CCLog("{ key3: %d }", pInteger->getValue());
 *  @endcode
 *  @js NA
 *
 */

class CDictionary : public CObject
{
public:
    /** 
     * The constructor of CDictionary.
     * @lua NA
     */
    CDictionary();

    /**
     * The destructor of CDictionary
     * @lua NA
     */
    ~CDictionary();

    /**
     *  Get the count of elements in CDictionary.
     *
     *  @return  The count of elements.
     */
    unsigned int count();

    /**
     *  Return all keys of elements.
     *
     *  @return  The array contains all keys of elements. It's an autorelease object yet.
     */
    CArray* allKeys();

    /** 
     *  Get all keys according to the specified object.
     *  @warning  We use '==' to compare two objects
     *  @return   The array contains all keys for the specified object. It's an autorelease object yet.
     */
    CArray* allKeysForObject(CObject* object);

    /**
     *  Get the object according to the specified string key.
     *
     *  @note The dictionary needs to use string as key. If integer is passed, an assert will appear.
     *  @param key  The string key for searching.
     *  @return The object matches the key. You need to force convert it to the type you know.
     *  @code
     *     // Assume that the elements are CString* pointers. Convert it by following code.
     *     CString* pStr = (CString*)pDict->objectForKey("key1");
     *     // Do something about pStr.
     *     // If you don't know the object type, properly you need to use dynamic_cast<SomeType*> to check it.
     *     CString* pStr2 = dynamic_cast<CString*>(pDict->objectForKey("key1"));
     *     if (pStr2 != NULL) {
     *          // Do something about pStr2
     *     }
     *  @endcode
     *  @see objectForKey(intptr_t)
     */
    CObject* objectForKey(const std::string& key);
    
    /**
     *  Get the object according to the specified integer key.
     *
     *  @note The dictionary needs to use integer as key. If string is passed, an assert will appear.
     *  @param key  The integer key for searching.
     *  @return The object matches the key.
     *  @see objectForKey(const std::string&)
     */
    CObject* objectForKey(intptr_t key);
    
    /** Get the value according to the specified string key.
     *
     *  @note Be careful to use this function since it assumes the objects in the dictionary are CString pointer.
     *  @param key  The string key for searching
     *  @return An instance of CString.
     *          It will return an empty string if the objects aren't CString pointer or the key wasn't found.
     *  @see valueForKey(intptr_t)
     */
    const CString* valueForKey(const std::string& key);
    
    /** Get the value according to the specified integer key.
     *
     *  @note Be careful to use this function since it assumes the objects in the dictionary are CString pointer.
     *  @param key  The string key for searching.
     *  @return An instance of CString.
     *          It will return an empty string if the objects aren't CString pointer or the key wasn't found.
     *  @see valueForKey(intptr_t)
     */
    const CString* valueForKey(intptr_t key);

    /** Insert an object to dictionary, and match it with the specified string key.
     *
     *  @note Whe the first time this method is invoked, the key type will be set to string.
     *        After that you can't setObject with an integer key.
     *        If the dictionary contains the key you passed, the object matching the key will be released and removed from dictionary.
     *        Then the new object will be inserted after that.
     *
     *  @param pObject  The Object to be inserted.
     *  @param key      The string key for searching.
     *  @see setObject(CObject*, intptr_t)
     */
    void setObject(CObject* pObject, const std::string& key);
    
    /** Insert an object to dictionary, and match it with the specified string key.
     *
     *  @note Then the first time this method is invoked, the key type will be set to string.
     *        After that you can't setObject with an integer key.
     *        If the dictionary contains the key you passed, the object matching the key will be released and removed from dictionary.
     *        Then the new object will be inserted after that.
     *  @param pObject  The Object to be inserted.
     *  @param key      The string key for searching.
     *  @see setObject(CObject*, const std::string&)
     */
    void setObject(CObject* pObject, intptr_t key);

    /** 
     *  Remove an object by the specified string key.
     *
     *  @param key  The string key for searching.
     *  @see removeObjectForKey(intptr_t), removeObjectsForKeys(CArray*),
     *       removeObjectForElememt(CDictElement*), removeAllObjects().
     */
    void removeObjectForKey(const std::string& key);
    
    /**
     *  Remove an object by the specified integer key.
     *
     *  @param key  The integer key for searching.
     *  @see removeObjectForKey(const std::string&), removeObjectsForKeys(CArray*),
     *       removeObjectForElememt(CDictElement*), removeAllObjects().
     */
    void removeObjectForKey(intptr_t key);
    
    /**
     *  Remove objects by an array of keys.
     *
     *  @param pKeyArray  The array contains keys to be removed.
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectForElememt(CDictElement*), removeAllObjects().
     */
    void removeObjectsForKeys(CArray* pKeyArray);
    
    /**
     *  Remove an object by an element.
     *
     *  @param pElement  The element need to be removed.
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectsForKeys(CArray*), removeAllObjects().
     *  @lua NA
     */
    void removeObjectForElememt(CDictElement* pElement);
    
    /**
     *  Remove all objects in the dictionary.
     *
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectsForKeys(CArray*), removeObjectForElememt(CDictElement*).
     */
    void removeAllObjects();

    
    /**
     *  Return a random object in the dictionary.
     *
     *  @return The random object. 
     *  @see objectForKey(intptr_t), objectForKey(const std::string&)
     *  @lua NA
     */
    CObject* randomObject();
    
    /**
     *  Create a dictionary.
     *  @return A dictionary which is an autorelease object.
     *  @see createWithDictionary(CDictionary*), createWithContentsOfFile(const char*), createWithContentsOfFileThreadSafe(const char*).
     */
    static CDictionary* create();
     

private:
    /** 
     *  For internal usage, invoked by setObject.
     */
    void setObjectUnSafe(CObject* pObject, const std::string& key);
    void setObjectUnSafe(CObject* pObject, const intptr_t key);
    
public:
    /**
     *  All the elements in dictionary.
     * 
     *  @note For internal usage, we need to declare this member variable as public since it's used in UT_HASH.
     */
    CDictElement* m_pElements;
private:
    
    /** The support type of dictionary, it's confirmed when setObject is invoked. */
    enum CCDictType
    {
        kCCDictUnknown = 0,
        kCCDictStr,
        kCCDictInt
    };
    
    /** 
     *  The type of dictionary, it's assigned to kCCDictUnknown by default.
     */
    CCDictType m_eDictType;
};


#endif /* __CDictionary_H__ */
