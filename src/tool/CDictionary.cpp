/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "CDictionary.h"
#include "CInteger.h"

using namespace std;


CDictElement::CDictElement(const char* pszKey, CObject* pObject)
{
    CAssert(pszKey && strlen(pszKey) > 0, "Invalid key value.");
    m_iKey = 0;
    const char* pStart = pszKey;
    
    int len = strlen(pszKey);
    if (len > MAX_KEY_LEN )
    {
        char* pEnd = (char*)&pszKey[len-1];
        pStart = pEnd - (MAX_KEY_LEN-1);
    }
    
    strcpy(m_szKey, pStart);
    
    m_pObject = pObject;
    memset(&hh, 0, sizeof(hh));
}

CDictElement::CDictElement(intptr_t iKey, CObject* pObject)
{
    m_szKey[0] = '\0';
    m_iKey = iKey;
    m_pObject = pObject;
    memset(&hh, 0, sizeof(hh));
}

CDictElement::~CDictElement()
{

}

// -----------------------------------------------------------------------
// CDictionary

CDictionary::CDictionary()
: m_pElements(NULL)
, m_eDictType(kCCDictUnknown)
{

}

CDictionary::~CDictionary()
{
    removeAllObjects();
}

unsigned int CDictionary::count()
{
    return HASH_COUNT(m_pElements);
}

CArray* CDictionary::allKeys()
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;

    CArray* pArray = CArray::createWithCapacity(iKeyCount);

    CDictElement *pElement, *tmp;
    if (m_eDictType == kCCDictStr)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            CString* pOneKey = new CString(pElement->m_szKey);
            pArray->addObject(pOneKey);
            CC_SAFE_RELEASE(pOneKey);
        }
    }
    else if (m_eDictType == kCCDictInt)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            CInteger* pOneKey = new CInteger(pElement->m_iKey);
            pArray->addObject(pOneKey);
            CC_SAFE_RELEASE(pOneKey);
        }
    }
    
    return pArray;
}

CArray* CDictionary::allKeysForObject(CObject* object)
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;
    CArray* pArray = CArray::create();

    CDictElement *pElement, *tmp;

    if (m_eDictType == kCCDictStr)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            if (object == pElement->m_pObject)
            {
                CString* pOneKey = new CString(pElement->m_szKey);
                pArray->addObject(pOneKey);
                CC_SAFE_RELEASE(pOneKey);
            }
        }
    }
    else if (m_eDictType == kCCDictInt)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            if (object == pElement->m_pObject)
            {
                CInteger* pOneKey = new CInteger(pElement->m_iKey);
                pArray->addObject(pOneKey);
                CC_SAFE_RELEASE(pOneKey);
            }
        }
    }
    return pArray;
}

CObject* CDictionary::objectForKey(const std::string& key)
{
    // if dictionary wasn't initialized, return NULL directly.
    if (m_eDictType == kCCDictUnknown) return NULL;
    // CDictionary only supports one kind of key, string or integer.
    // This method uses string as key, therefore we should make sure that the key type of this CDictionary is string.
    CAssert(m_eDictType == kCCDictStr, "this dictionary does not use string as key.");

    CObject* pRetObject = NULL;
    CDictElement *pElement = NULL;
    HASH_FIND_STR(m_pElements, key.c_str(), pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->m_pObject;
    }
    return pRetObject;
}

CObject* CDictionary::objectForKey(intptr_t key)
{
    // if dictionary wasn't initialized, return NULL directly.
    if (m_eDictType == kCCDictUnknown) return NULL;
    // CDictionary only supports one kind of key, string or integer.
    // This method uses integer as key, therefore we should make sure that the key type of this CDictionary is integer.
    CAssert(m_eDictType == kCCDictInt, "this dictionary does not use integer as key.");

    CObject* pRetObject = NULL;
    CDictElement *pElement = NULL;
    HASH_FIND_PTR(m_pElements, &key, pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->m_pObject;
    }
    return pRetObject;
}

const CString* CDictionary::valueForKey(const std::string& key)
{
    CString* pStr = dynamic_cast<CString*>(objectForKey(key));
    if (pStr == NULL)
    {
        pStr = CString::create("");
    }
    return pStr;
}

const CString* CDictionary::valueForKey(intptr_t key)
{
    CString* pStr = dynamic_cast<CString*>(objectForKey(key));
    if (pStr == NULL)
    {
        pStr = CString::create("");
    }
    return pStr;
}

void CDictionary::setObject(CObject* pObject, const std::string& key)
{
    CAssert(key.length() > 0 && pObject != NULL, "Invalid Argument!");
    if (m_eDictType == kCCDictUnknown)
    {
        m_eDictType = kCCDictStr;
    }

    CAssert(m_eDictType == kCCDictStr, "this dictionary doesn't use string as key.");

    CDictElement *pElement = NULL;
    HASH_FIND_STR(m_pElements, key.c_str(), pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->m_pObject != pObject)
    {
        CObject* pTmpObj = pElement->m_pObject;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }
}

void CDictionary::setObject(CObject* pObject, intptr_t key)
{
    CAssert(pObject != NULL, "Invalid Argument!");
    if (m_eDictType == kCCDictUnknown)
    {
        m_eDictType = kCCDictInt;
    }

    CAssert(m_eDictType == kCCDictInt, "this dictionary doesn't use integer as key.");

    CDictElement *pElement = NULL;
    HASH_FIND_PTR(m_pElements, &key, pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->m_pObject != pObject)
    {
        CObject* pTmpObj = pElement->m_pObject;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }

}

void CDictionary::removeObjectForKey(const std::string& key)
{
    if (m_eDictType == kCCDictUnknown)
    {
        return;
    }
    
    CAssert(m_eDictType == kCCDictStr, "this dictionary doesn't use string as its key");
    CAssert(key.length() > 0, "Invalid Argument!");
    CDictElement *pElement = NULL;
    HASH_FIND_STR(m_pElements, key.c_str(), pElement);
    removeObjectForElememt(pElement);
}

void CDictionary::removeObjectForKey(intptr_t key)
{
    if (m_eDictType == kCCDictUnknown)
    {
        return;
    }
    
    CAssert(m_eDictType == kCCDictInt, "this dictionary doesn't use integer as its key");
    CDictElement *pElement = NULL;
    HASH_FIND_PTR(m_pElements, &key, pElement);
    removeObjectForElememt(pElement);
}

void CDictionary::setObjectUnSafe(CObject* pObject, const std::string& key)
{
    pObject->retain();
    CDictElement* pElement = new CDictElement(key.c_str(), pObject);
    HASH_ADD_STR(m_pElements, m_szKey, pElement);
}

void CDictionary::setObjectUnSafe(CObject* pObject, const intptr_t key)
{
    pObject->retain();
    CDictElement* pElement = new CDictElement(key, pObject);
    HASH_ADD_PTR(m_pElements, m_iKey, pElement);
}

void CDictionary::removeObjectsForKeys(CArray* pKeyArray)
{
    CObject* pObj = NULL;
    CARRAY_FOREACH(pKeyArray, pObj)
    {
        CString* pStr = (CString*)pObj;
        removeObjectForKey(pStr->getCString());
    }
}

void CDictionary::removeObjectForElememt(CDictElement* pElement)
{
    if (pElement != NULL)
    {
        HASH_DEL(m_pElements, pElement);
        pElement->m_pObject->release();
        CC_SAFE_DELETE(pElement);
    }
}

void CDictionary::removeAllObjects()
{
    CDictElement *pElement, *tmp;
    HASH_ITER(hh, m_pElements, pElement, tmp) 
    {
        HASH_DEL(m_pElements, pElement);
        pElement->m_pObject->release();
        CC_SAFE_DELETE(pElement);

    }
}

CObject* CDictionary::randomObject()
{
    if (m_eDictType == kCCDictUnknown)
    {
        return NULL;
    }
    
    CObject* key = allKeys()->randomObject();
    
    if (m_eDictType == kCCDictInt)
    {
        return objectForKey(((CInteger*)key)->getValue());
    }
    else if (m_eDictType == kCCDictStr)
    {
        return objectForKey(((CString*)key)->getCString());
    }
    else
    {
        return NULL;
    }
}

CDictionary* CDictionary::create()
{
    CDictionary* pRet = new CDictionary();
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}
