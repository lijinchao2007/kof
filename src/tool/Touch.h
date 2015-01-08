/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __C_TOUCH_H__
#define __C_TOUCH_H__
#include "tool.h"

class CTouch
{
public:
    CTouch();
	~CTouch();

    CPoint getLocation() const;
    CPoint getPreviousLocation() const;
    CPoint getStartLocation() const;
    CPoint getDelta() const;
    CPoint getLocationInView() const;
    CPoint getPreviousLocationInView() const;
    CPoint getStartLocationInView() const;
    
    void setTouchInfo(int id, float x, float y)
    {
        m_nId = id;
        m_prevPoint = m_point;

		float posx = x - Common_GetStartPosX();
		float posy = y - Common_GetStartPosY();
		posx = posx / Common_GetScaleX();
		posy = posy / Common_GetScaleY();
        m_point.x   = posx;
        m_point.y   = posy;
		// change to design pos
        if (!m_startPointCaptured)
        {
            m_startPoint = m_point;
            m_startPointCaptured = true;
        }
    }

    int getID() const
    {
        return m_nId;
    }

private:
    int m_nId;
    bool m_startPointCaptured;
    CPoint m_startPoint;
    CPoint m_point;
    CPoint m_prevPoint;
};


#endif  // __PLATFORM_TOUCH_H__
