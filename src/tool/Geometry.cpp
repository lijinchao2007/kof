/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "define.h"
#include "Geometry.h"

CPoint::CPoint(void) : x(0), y(0)
{
}

CPoint::CPoint(float x, float y) : x(x), y(y)
{
}

CPoint::CPoint(const CPoint& other) : x(other.x), y(other.y)
{
}

CPoint::CPoint(const CSize& size) : x(size.width), y(size.height)
{
}

CPoint& CPoint::operator= (const CPoint& other)
{
    setPoint(other.x, other.y);
    return *this;
}

CPoint& CPoint::operator= (const CSize& size)
{
    setPoint(size.width, size.height);
    return *this;
}

CPoint CPoint::operator+(const CPoint& right) const
{
    return CPoint(this->x + right.x, this->y + right.y);
}

CPoint CPoint::operator-(const CPoint& right) const
{
    return CPoint(this->x - right.x, this->y - right.y);
}

CPoint CPoint::operator-() const
{
	return CPoint(-x, -y);
}

CPoint CPoint::operator*(float a) const
{
    return CPoint(this->x * a, this->y * a);
}

CPoint CPoint::operator/(float a) const
{
	SDL_assert(a);
    return CPoint(this->x / a, this->y / a);
}

void CPoint::setPoint(float x, float y)
{
    this->x = x;
    this->y = y;
}

bool CPoint::equals(const CPoint& target) const
{
    return (fabs(this->x - target.x) < FLT_EPSILON)
        && (fabs(this->y - target.y) < FLT_EPSILON);
}

bool CPoint::fuzzyEquals(const CPoint& b, float var) const
{
    if(x - var <= b.x && b.x <= x + var)
        if(y - var <= b.y && b.y <= y + var)
            return true;
    return false;
}

float CPoint::getAngle(const CPoint& other) const
{
    CPoint a2 = normalize();
    CPoint b2 = other.normalize();
    float angle = atan2f(a2.cross(b2), a2.dot(b2));
    if( fabs(angle) < FLT_EPSILON ) return 0.f;
    return angle;
}

CPoint CPoint::rotateByAngle(const CPoint& pivot, float angle) const
{
    return pivot + (*this - pivot).rotate(CPoint::forAngle(angle));
}

// implementation of CSize

CSize::CSize(void) : width(0), height(0)
{
}

CSize::CSize(float width, float height) : width(width), height(height)
{
}

CSize::CSize(const CSize& other) : width(other.width), height(other.height)
{
}

CSize::CSize(const CPoint& point) : width(point.x), height(point.y)
{
}

CSize& CSize::operator= (const CSize& other)
{
    setSize(other.width, other.height);
    return *this;
}

CSize& CSize::operator= (const CPoint& point)
{
    setSize(point.x, point.y);
    return *this;
}

CSize CSize::operator+(const CSize& right) const
{
    return CSize(this->width + right.width, this->height + right.height);
}

CSize CSize::operator-(const CSize& right) const
{
    return CSize(this->width - right.width, this->height - right.height);
}

CSize CSize::operator*(float a) const
{
    return CSize(this->width * a, this->height * a);
}

CSize CSize::operator/(float a) const
{
	SDL_assert(a);
    return CSize(this->width / a, this->height / a);
}

void CSize::setSize(float width, float height)
{
    this->width = width;
    this->height = height;
}

bool CSize::equals(const CSize& target) const
{
    return (fabs(this->width  - target.width)  < FLT_EPSILON)
        && (fabs(this->height - target.height) < FLT_EPSILON);
}

// implementation of CRect

CRect::CRect(void)
{
    setRect(0.0f, 0.0f, 0.0f, 0.0f);
}

CRect::CRect(float x, float y, float width, float height)
{
    setRect(x, y, width, height);
}

CRect::CRect(const CRect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
}

CRect& CRect::operator= (const CRect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
    return *this;
}

void CRect::setRect(float x, float y, float width, float height)
{
    // CGRect can support width<0 or height<0
    // CCAssert(width >= 0.0f && height >= 0.0f, "width and height of Rect must not less than 0.");

    origin.x = x;
    origin.y = y;

    size.width = width;
    size.height = height;
}

bool CRect::equals(const CRect& rect) const
{
    return (origin.equals(rect.origin) && 
            size.equals(rect.size));
}

float CRect::getMaxX() const
{
    return (float)(origin.x + size.width);
}

float CRect::getMidX() const
{
    return (float)(origin.x + size.width / 2.0);
}

float CRect::getMinX() const
{
    return origin.x;
}

float CRect::getMaxY() const
{
    return origin.y + size.height;
}

float CRect::getMidY() const
{
    return (float)(origin.y + size.height / 2.0);
}

float CRect::getMinY() const
{
    return origin.y;
}

bool CRect::containsPoint(const CPoint& point) const
{
    bool bRet = false;

    if (point.x >= getMinX() && point.x <= getMaxX()
        && point.y >= getMinY() && point.y <= getMaxY())
    {
        bRet = true;
    }

    return bRet;
}

bool CRect::intersectsRect(const CRect& rect) const
{
    return !(     getMaxX() < rect.getMinX() ||
             rect.getMaxX() <      getMinX() ||
                  getMaxY() < rect.getMinY() ||
             rect.getMaxY() <      getMinY());
}

