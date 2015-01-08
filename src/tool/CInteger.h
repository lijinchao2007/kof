/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __CINTEGER_H__
#define __CINTEGER_H__

#include "CObject.h"

class CInteger:public CObject
{

public:
    CInteger(int v)
        : m_nValue(v) {}
    int getValue() const {return m_nValue;}

    static CInteger* create(int v)
    {
        CInteger* pRet = new CInteger(v);
        return pRet;
    }

private:
    int m_nValue;
};


#endif /* __CInteger_H__ */
