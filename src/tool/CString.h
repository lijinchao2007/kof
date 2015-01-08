/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __CString_H__
#define __CString_H__

#include <stdarg.h>
#include <string>
#include <functional>
#include "CObject.h"


/**
 * @addtogroup data_structures
 * @{
 * @ js NA
 */

class CString : public CObject
{
public:
    /**
     * @lua NA
     */
    CString();
    /**
     * @lua NA
     */
    CString(const char* str);
    /**
     * @lua NA
     */
    CString(const std::string& str);
    /**
     * @lua NA
     */
    CString(const CString& str);
    /**
     * @lua NA
     */
    virtual ~CString();
    
    /* override assignment operator
     * @lua NA
     */
    CString& operator= (const CString& other);

    /** init a string with format, it's similar with the c function 'sprintf' 
     * @lua NA
     */
    bool initWithFormat(const char* format, ...);

    /** convert to int value */
    int intValue() const;

    /** convert to unsigned int value */
    unsigned int uintValue() const;

    /** convert to float value */
    float floatValue() const;

    /** convert to double value */
    double doubleValue() const;

    /** convert to bool value */
    bool boolValue() const;

    /** get the C string */
    const char* getCString() const;

    /** get the length of string */
    unsigned int length() const;

    /** compare to a c string */
    int compare(const char *) const;

    /* override functions 
     * @lua NA
     * @js  NA
     */
    virtual bool isEqual(const CObject* pObject);

    /** create a string with std string, you can also pass a c string pointer because the default constructor of std::string can access a c string pointer. 
     *  @return A CString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     */
    static CString* create(const std::string& str);

    /** create a string with format, it's similar with the c function 'sprintf', the default buffer size is (1024*100) bytes,
     *  if you want to change it, you should modify the kMaxStringLen macro in CString.cpp file.
     *  @return A CString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     *  @lua NA
     */ 
    static CString* createWithFormat(const char* format, ...);


private:

    /** only for internal use */
    bool initWithFormatAndValist(const char* format, va_list ap);

public:
    std::string m_sString;
};

struct CStringCompare : public std::binary_function<CString *, CString *, bool> {
    public:
        bool operator() (CString * a, CString * b) const {
            return strcmp(a->getCString(), b->getCString()) < 0;
        }
};

#define CStringMake(str) CString::create(str)
#define ccs               CStringMake

// end of data_structure group
/// @}


#endif //__CString_H__
