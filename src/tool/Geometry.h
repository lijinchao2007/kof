/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __CGEMETRY_H__
#define __CGEMETRY_H__

#include <math.h>
#include <float.h>

#ifndef FLT_EPSILON
#define FLT_EPSILON __FLT_EPSILON__
#endif

class CSize;

class CPoint
{
public:
    float x;
    float y;

public:
    CPoint();
    CPoint(float x, float y);
    CPoint(const CPoint& other);
    CPoint(const CSize& size);
    /**
     * @lua NA
     */
    CPoint& operator= (const CPoint& other);
    /**
     * @lua NA
     */
    CPoint& operator= (const CSize& size);
    /**
     * @lua NA
     */
    CPoint operator+(const CPoint& right) const;
    /**
     * @lua NA
     */
    CPoint operator-(const CPoint& right) const;
    /**
     * @lua NA
     */
    CPoint operator-() const;
    /**
     * @lua NA
     */
    CPoint operator*(float a) const;
    /**
     * @lua NA
     */
    CPoint operator/(float a) const;
    /**
     * @lua NA
     */
    void setPoint(float x, float y);
    bool equals(const CPoint& target) const;
    
    /** @returns if points have fuzzy equality which means equal with some degree of variance.
     * @since v2.1.4
     * @lua NA
     */
    bool fuzzyEquals(const CPoint& target, float variance) const;

    /** Calculates distance between point an origin
     * @return float
     * @since v2.1.4
     * @lua NA
     */
    inline float getLength() const {
        return sqrtf(x*x + y*y);
    };

    /** Calculates the square length of a CPoint (not calling sqrt() )
     * @return float
     * @since v2.1.4
     * @lua NA
     */
    inline float getLengthSq() const {
        return dot(*this); //x*x + y*y;
    };

    /** Calculates the square distance between two points (not calling sqrt() )
     @return float
     @since v2.1.4
    */
    inline float getDistanceSq(const CPoint& other) const {
        return (*this - other).getLengthSq();
    };

    /** Calculates the distance between two points
     @return float
     @since v2.1.4
     */
    inline float getDistance(const CPoint& other) const {
        return (*this - other).getLength();
    };

    /** @returns the angle in radians between this vector and the x axis
     @since v2.1.4
    */
    inline float getAngle() const {
        return atan2f(y, x);
    };

    /** @returns the angle in radians between two vector directions
     @since v2.1.4
    */
    float getAngle(const CPoint& other) const;

    /** Calculates dot product of two points.
     @return float
     @since v2.1.4
     */
    inline float dot(const CPoint& other) const {
        return x*other.x + y*other.y;
    };

    /** Calculates cross product of two points.
     @return float
     @since v2.1.4
     */
    inline float cross(const CPoint& other) const {
        return x*other.y - y*other.x;
    };

    /** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
     @return CPoint
     @since v2.1.4
     */
    inline CPoint getPerp() const {
        return CPoint(-y, x);
    };

    /** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
     @return CPoint
     @since v2.1.4
     */
    inline CPoint getRPerp() const {
        return CPoint(y, -x);
    };

    /** Calculates the projection of this over other.
     @return CPoint
     @since v2.1.4
     */
    inline CPoint project(const CPoint& other) const {
        return other * (dot(other)/other.dot(other));
    };

    /** Complex multiplication of two points ("rotates" two points).
     @return CPoint vector with an angle of this.getAngle() + other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     */
    inline CPoint rotate(const CPoint& other) const {
        return CPoint(x*other.x - y*other.y, x*other.y + y*other.x);
    };

    /** Unrotates two points.
     @return CPoint vector with an angle of this.getAngle() - other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     */
    inline CPoint unrotate(const CPoint& other) const {
        return CPoint(x*other.x + y*other.y, y*other.x - x*other.y);
    };

    /** Returns point multiplied to a length of 1.
     * If the point is 0, it returns (1, 0)
     @return CPoint
     @since v2.1.4
     */
    inline CPoint normalize() const {
        float length = getLength();
        if(length == 0.) return CPoint(1.f, 0);
        return *this / getLength();
    };

    /** Linear Interpolation between two points a and b
     @returns
        alpha == 0 ? a
        alpha == 1 ? b
        otherwise a value between a..b
     @since v2.1.4
     */
    inline CPoint lerp(const CPoint& other, float alpha) const {
        return *this * (1.f - alpha) + other * alpha;
    };

    /** Rotates a point counter clockwise by the angle around a pivot
     @param pivot is the pivot, naturally
     @param angle is the angle of rotation ccw in radians
     @returns the rotated point
     @since v2.1.4
     */
    CPoint rotateByAngle(const CPoint& pivot, float angle) const;

    static inline CPoint forAngle(const float a)
    {
    	return CPoint(cosf(a), sinf(a));
    }
};

class CSize
{
public:
    float width;
    float height;

public:
    CSize();
    CSize(float width, float height);
    /**
     * @lua NA
     */
    CSize(const CSize& other);
    /**
     * @lua NA
     */
    CSize(const CPoint& point);
    /**
     * @lua NA
     */
    CSize& operator= (const CSize& other);
    /**
     * @lua NA
     */
    CSize& operator= (const CPoint& point);
    /**
     * @lua NA
     */
    CSize operator+(const CSize& right) const;
    /**
     * @lua NA
     */
    CSize operator-(const CSize& right) const;
    /**
     * @lua NA
     */
    CSize operator*(float a) const;
    /**
     * @lua NA
     */
    CSize operator/(float a) const;
    /**
     * @lua NA
     */
    void setSize(float width, float height);
    /**
     * @lua NA
     */
    bool equals(const CSize& target) const;
};

/**
 * @js NA
 */
class CRect
{
public:
    CPoint origin;
    CSize  size;

public:
    CRect();
    CRect(float x, float y, float width, float height);
    /**
     * @lua NA
     */
    CRect(const CRect& other);
    /**
     * @lua NA
     */
    CRect& operator= (const CRect& other);
    void setRect(float x, float y, float width, float height);
    float getMinX() const; /// return the leftmost x-value of current rect
    float getMidX() const; /// return the midpoint x-value of current rect
    float getMaxX() const; /// return the rightmost x-value of current rect
    float getMinY() const; /// return the bottommost y-value of current rect
    float getMidY() const; /// return the midpoint y-value of current rect
    float getMaxY() const; /// return the topmost y-value of current rect
    bool equals(const CRect& rect) const;   
    bool containsPoint(const CPoint& point) const;
    bool intersectsRect(const CRect& rect) const;
};


#define CPointMake(x, y) CPoint((float)(x), (float)(y))
#define CSizeMake(width, height) CSize((float)(width), (float)(height))
#define CRectMake(x, y, width, height) CRect((float)(x), (float)(y), (float)(width), (float)(height))


const CPoint CPointZero = CPointMake(0,0);

/* The "zero" size -- equivalent to CSizeMake(0, 0). */ 
const CSize CSizeZero = CSizeMake(0,0);

/* The "zero" rectangle -- equivalent to CRectMake(0, 0, 0, 0). */ 
const CRect CRectZero = CRectMake(0,0,0,0);

// end of data_structure group
/// @}




#endif // __CCGEMETRY_H__
