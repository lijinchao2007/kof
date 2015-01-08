/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "CCProgressTimer.h"
#include "driver/SDLManager.h"

CCProgressTimer::CCProgressTimer()
	:m_frontPercentage(1.0f)
	,m_midPercentage(1.0f)
	,m_pbg(NULL)
	,m_pmid(NULL)
	,m_pfront(NULL)
	,m_bReverseDirection(false)
{}

CCProgressTimer* CCProgressTimer::create(SFFSPRITE* bg, SFFSPRITE* mid, SFFSPRITE* front)
{
    CCProgressTimer *pProgressTimer = new CCProgressTimer();
    if (pProgressTimer->initWithSpr(bg, mid, front))
    {
        pProgressTimer->autorelease();
    }
    else
    {
        delete pProgressTimer;
        pProgressTimer = NULL;
    }        

    return pProgressTimer;
}

bool CCProgressTimer::initWithSpr(SFFSPRITE* bg, SFFSPRITE* mid, SFFSPRITE* front)
{
    m_bReverseDirection = false;

	m_pbg =  bg;
	m_pmid = mid;
	m_pfront = front;
    return true;
}

CCProgressTimer::~CCProgressTimer(void)
{
}

void CCProgressTimer::setMidPercentage(float fPercentage)
{
	m_midPercentage = fPercentage;
}

void CCProgressTimer::setFrontPercentage(float fPercentage)
{
	m_frontPercentage = fPercentage;
}


void CCProgressTimer::setReverseProgress(bool reverse)
{
    if( m_bReverseDirection != reverse ) {
        m_bReverseDirection = reverse;
    }
}


void CCProgressTimer::updateProgress(void)
{
}


void CCProgressTimer::draw(void)
{
	if (m_bVisible)
	{
		CCNode::draw();
		CPoint scPos = convertToWorldSpace(CPointZero);
		if (m_pbg!=NULL)
		{
			DrawInfo info;
			info.spr = m_pbg;
			info.nScreenPosX = scPos.x;
			info.nScreenPosY = scPos.y;
			info.transMode = eTransTypeNone;
			info.nScaleX = m_fScaleX;
			info.nScaleY = m_fScaleY;
			if (m_bReverseDirection)
			{
				info.nScaleX = -m_fScaleX;
			}
			CSDLManager::GetInstance()->GetVideoSystem()->RerderSpr(info, NULL);
			CSDLManager::GetInstance()->GetVideoSystem()->RenderDrawRect(222,222,222, info.nScreenPosX, info.nScreenPosY, \
				5, 5, eDRAW_RECT_TYPE_FILLED);
		}
		if (m_pmid!=NULL)
		{
			DrawInfo info;
			info.spr = m_pmid;
			info.nScreenPosX = scPos.x;
			info.nScreenPosY = scPos.y;
			info.transMode = eTransTypeNone;
			info.nScaleX = m_fScaleX;
			info.nScaleY = m_fScaleY;
			if (m_bReverseDirection)
			{
				info.nScaleX = -m_fScaleX;
			}
			info.percentx = m_midPercentage;
			CSDLManager::GetInstance()->GetVideoSystem()->RerderSpr(info, NULL);
			CSDLManager::GetInstance()->GetVideoSystem()->RenderDrawRect(222,222,222, info.nScreenPosX, info.nScreenPosY, \
				5, 5, eDRAW_RECT_TYPE_FILLED);
		}
		if (m_pfront!=NULL)
		{
			DrawInfo info;
			info.spr = m_pfront;
			info.nScreenPosX = scPos.x;
			info.nScreenPosY = scPos.y;
			info.transMode = eTransTypeNone;
			info.nScaleX = m_fScaleX;
			info.nScaleY = m_fScaleY;
			if (m_bReverseDirection)
			{
				info.nScaleX = -m_fScaleX;
			}
			info.percentx = m_frontPercentage;
			CSDLManager::GetInstance()->GetVideoSystem()->RerderSpr(info, NULL);
			CSDLManager::GetInstance()->GetVideoSystem()->RenderDrawRect(222,222,222, info.nScreenPosX, info.nScreenPosY, \
				5, 5, eDRAW_RECT_TYPE_FILLED);
		}
	}
}

