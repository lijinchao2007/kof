/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __CCSCENE_H__
#define __CCSCENE_H__

#include "tool.h"
#include "CCNode.h"

class CCScene : public CCNode
{
public:
    /**
     *  @js ctor
     */
    CCScene();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCScene();
    bool init();

    static CCScene *create(void);
};


#endif // __CCSCENE_H__
