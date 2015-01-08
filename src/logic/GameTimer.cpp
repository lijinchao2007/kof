/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "GameTimer.h"
#include "tool.h"

CGameTimer::CGameTimer()
{
	bPause = false;
	nGameTime = 0;
	nLayer = -1;
	m_propIsDebugTime = false;
	m_MSPerCount = 1000.0/SDL_GetPerformanceFrequency();
}

CGameTimer::~CGameTimer()
{

}

void CGameTimer::InitTimer()
{
	nGameTime=0;
	bPause=false;
}

void CGameTimer::UpdateTimer()
{
	if(!bPause)nGameTime++;
}

Uint32  CGameTimer::GetGameTime()
{
	return nGameTime;
}

void CGameTimer::DebugTimeBegin(const char* name)
{
	if (!m_propIsDebugTime)
	{
		return;
	}
	if (nLayer == -1)
	{
		m_logStr = "---------------------------------------------------------------\n";
	}
	nLayer ++;
	double tick = SDL_GetPerformanceCounter()*m_MSPerCount;
	m_MapDebugTime.insert(std::pair<const char*, double>(name, tick));
}

void CGameTimer::DebugTimeEnd(const char* name)
{
	
	std::map<const char*, double>::iterator iter = m_MapDebugTime.find(name);
	if (iter == m_MapDebugTime.end())
	{
		return;
	}
	double starttick = (iter->second);
	double endtick = SDL_GetPerformanceCounter()*m_MSPerCount;
	double cost = endtick - starttick;
	
	m_MapDebugTime.erase(iter);
	char blank[MAX_PATH] = {0};
	for (int i=0; i<nLayer*2&&i<MAX_PATH;i++)
	{
		blank[i] = ' ';
	}
	char temp[MAX_PATH];
	SDL_snprintf(temp, MAX_PATH, "%s%s:cost=%10.2f\n", blank, name, cost);
	m_logStr+=temp;
	nLayer --;
	if (nLayer == -1)
	{
		PrintMessage(m_logStr.c_str());
	}
}
void CGameTimer::DebugTimeClear()
{
	m_MapDebugTime.clear();
}

CGameTimer* CGameTimer::GetInstance()
{
	if ( g_pGameTimer == NULL )  //判断是否第一次调用
		g_pGameTimer = new CGameTimer();
	return g_pGameTimer;
}
void CGameTimer::Destroy()
{
	CC_SAFE_DELETE(g_pGameTimer);
}