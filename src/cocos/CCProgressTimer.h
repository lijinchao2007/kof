/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __CCPROGRESS_TIMER_H__
#define __CCPROGRESS_TIMER_H__

#include "CCNode.h"
#include "tool.h"
#include "CCTextureCache.h"

class CCProgressTimer : public CCNode
{
public:
    CCProgressTimer();
    ~CCProgressTimer(void);

    /** Initializes a progress timer with the sprite as the shape the timer goes through */
    bool initWithSpr(SFFSPRITE* bg, SFFSPRITE* mid, SFFSPRITE* front);

	void setMidPercentage(float fPercentage);
	void setFrontPercentage(float fPercentage);
    void setReverseProgress(bool reverse);

    virtual void draw(void);
    inline bool isReverseDirection() { return m_bReverseDirection; };

public:
    /** Creates a progress timer with the sprite as the shape the timer goes through */
    static CCProgressTimer* create(SFFSPRITE* bg, SFFSPRITE* mid, SFFSPRITE* front);
protected:
    void updateProgress(void);

protected:
	float m_frontPercentage;
	float m_midPercentage;
	SFFSPRITE *m_pbg;
	SFFSPRITE *m_pmid;
	SFFSPRITE *m_pfront;
    bool m_bReverseDirection;
};


#endif //__MISC_NODE_CCPROGRESS_TIMER_H__
