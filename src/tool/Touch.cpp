/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "Touch.h"
static unsigned int uObjectCount = 0;

CTouch::CTouch()
{
	m_startPointCaptured = false;
	m_nId = ++uObjectCount;
}

CTouch::~CTouch()
{

}

// returns the current touch location in screen coordinates
CPoint CTouch::getLocationInView() const 
{ 
    return m_point; 
}

// returns the previous touch location in screen coordinates
CPoint CTouch::getPreviousLocationInView() const 
{ 
    return m_prevPoint; 
}

// returns the start touch location in screen coordinates
CPoint CTouch::getStartLocationInView() const 
{ 
    return m_startPoint; 
}

// returns the current touch location in OpenGL coordinates
CPoint CTouch::getLocation() const
{ 
    return (m_point); 
}

// returns the previous touch location in OpenGL coordinates
CPoint CTouch::getPreviousLocation() const
{ 
    return (m_prevPoint);  
}

// returns the start touch location in OpenGL coordinates
CPoint CTouch::getStartLocation() const
{ 
    return (m_startPoint);  
}

// returns the delta position between the current location and the previous location in OpenGL coordinates
CPoint CTouch::getDelta() const
{     
    return CPointMake(getLocation().x - getPreviousLocation().x, getLocation().y - getPreviousLocation().y); 
}
