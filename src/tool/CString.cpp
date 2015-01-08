/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "CString.h"
#include "ccMacros.h"
#include <stdlib.h>
#include <stdio.h>


#define kMaxStringLen (1024*100)

CString::CString()
    :m_sString("")
{}

CString::CString(const char * str)
    :m_sString(str)
{}

CString::CString(const std::string& str)
    :m_sString(str)
{}

CString::CString(const CString& str)
    :m_sString(str.getCString())
{}

CString::~CString()
{ 
    m_sString.clear();
}

CString& CString::operator= (const CString& other)
{
    m_sString = other.m_sString;
    return *this;
}

bool CString::initWithFormatAndValist(const char* format, va_list ap)
{
    bool bRet = false;
    char* pBuf = (char*)malloc(kMaxStringLen);
    if (pBuf != NULL)
    {
        vsnprintf(pBuf, kMaxStringLen, format, ap);
        m_sString = pBuf;
        free(pBuf);
        bRet = true;
    }
    return bRet;
}

bool CString::initWithFormat(const char* format, ...)
{
    bool bRet = false;
    m_sString.clear();

    va_list ap;
    va_start(ap, format);

    bRet = initWithFormatAndValist(format, ap);

    va_end(ap);

    return bRet;
}

int CString::intValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return atoi(m_sString.c_str());
}

unsigned int CString::uintValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return (unsigned int)atoi(m_sString.c_str());
}

float CString::floatValue() const
{
    if (length() == 0)
    {
        return 0.0f;
    }
    return (float)atof(m_sString.c_str());
}

double CString::doubleValue() const
{
    if (length() == 0)
    {
        return 0.0;
    }
    return atof(m_sString.c_str());
}

bool CString::boolValue() const
{
    if (length() == 0)
    {
        return false;
    }

    if (0 == strcmp(m_sString.c_str(), "0") || 0 == strcmp(m_sString.c_str(), "false"))
    {
        return false;
    }
    return true;
}

const char* CString::getCString() const
{
    return m_sString.c_str();
}

unsigned int CString::length() const
{
    return m_sString.length();
}

int CString::compare(const char * pStr) const
{
    return strcmp(getCString(), pStr);
}


bool CString::isEqual(const CObject* pObject)
{
    bool bRet = false;
    const CString* pStr = dynamic_cast<const CString*>(pObject);
    if (pStr != NULL)
    {
        if (0 == m_sString.compare(pStr->m_sString))
        {
            bRet = true;
        }
    }
    return bRet;
}

CString* CString::create(const std::string& str)
{
    CString* pRet = new CString(str);
    pRet->autorelease();
    return pRet;
}

CString* CString::createWithFormat(const char* format, ...)
{
    CString* pRet = CString::create("");
    va_list ap;
    va_start(ap, format);
    pRet->initWithFormatAndValist(format, ap);
    va_end(ap);

    return pRet;
}
