/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "CPointExtension.h"
#include "ccMacros.h" // FLT_EPSILON
#include <stdio.h>


float
ccpLength(const CPoint& v)
{
    return v.getLength();
}

float
ccpDistance(const CPoint& v1, const CPoint& v2)
{
    return (v1 - v2).getLength();
}

CPoint
ccpNormalize(const CPoint& v)
{
    return v.normalize();
}

CPoint
ccpForAngle(const float a)
{
    return CPoint::forAngle(a);
}

float
ccpToAngle(const CPoint& v)
{
    return v.getAngle();
}

CPoint ccpLerp(const CPoint& a, const CPoint& b, float alpha)
{
    return a.lerp(b, alpha);
}



CPoint ccpFromSize(const CSize& s)
{
    return CPoint(s);
}

CPoint ccpCompOp(const CPoint& p, float (*opFunc)(float))
{
    return ccp(opFunc(p.x), opFunc(p.y));
}

bool ccpFuzzyEqual(const CPoint& a, const CPoint& b, float var)
{
	return a.fuzzyEquals(b, var);
}

CPoint ccpCompMult(const CPoint& a, const CPoint& b)
{
    return ccp(a.x * b.x, a.y * b.y);
}

float ccpAngleSigned(const CPoint& a, const CPoint& b)
{
	return a.getAngle(b);
}

CPoint ccpRotateByAngle(const CPoint& v, const CPoint& pivot, float angle)
{
	return v.rotateByAngle(pivot, angle);
}


bool ccpSegmentIntersect(const CPoint& A, const CPoint& B, const CPoint& C, const CPoint& D)
{
    float S, T;

    if( ccpLineIntersect(A, B, C, D, &S, &T )
        && (S >= 0.0f && S <= 1.0f && T >= 0.0f && T <= 1.0f) )
        return true;

    return false;
}

CPoint ccpIntersectPoint(const CPoint& A, const CPoint& B, const CPoint& C, const CPoint& D)
{
    float S, T;

    if( ccpLineIntersect(A, B, C, D, &S, &T) )
    {
        // Point of intersection
        CPoint P;
        P.x = A.x + S * (B.x - A.x);
        P.y = A.y + S * (B.y - A.y);
        return P;
    }

    return CPointZero;
}

bool ccpLineIntersect(const CPoint& A, const CPoint& B, 
                      const CPoint& C, const CPoint& D,
                      float *S, float *T)
{
    // FAIL: Line undefined
    if ( (A.x==B.x && A.y==B.y) || (C.x==D.x && C.y==D.y) )
    {
        return false;
    }
    const float BAx = B.x - A.x;
    const float BAy = B.y - A.y;
    const float DCx = D.x - C.x;
    const float DCy = D.y - C.y;
    const float ACx = A.x - C.x;
    const float ACy = A.y - C.y;

    const float denom = DCy*BAx - DCx*BAy;

    *S = DCx*ACy - DCy*ACx;
    *T = BAx*ACy - BAy*ACx;

    if (denom == 0)
    {
        if (*S == 0 || *T == 0)
        { 
            // Lines incident
            return true;   
        }
        // Lines parallel and not incident
        return false;
    }

    *S = *S / denom;
    *T = *T / denom;

    // Point of intersection
    // CGPoint P;
    // P.x = A.x + *S * (B.x - A.x);
    // P.y = A.y + *S * (B.y - A.y);

    return true;
}

float ccpAngle(const CPoint& a, const CPoint& b)
{
    float angle = acosf(ccpDot(ccpNormalize(a), ccpNormalize(b)));
    if( fabs(angle) < FLT_EPSILON ) return 0.f;
    return angle;
}

