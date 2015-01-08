/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "SDLManager.h"
#include "tool.h"
#include "config/ConfigManager.h"
#include "FontManager.h"


CSDLManager *CSDLManager::GetInstance()
{
	if (g_pSDLManager == NULL)
	{
		g_pSDLManager = new CSDLManager;
	}
	return g_pSDLManager;
}

CSDLManager::CSDLManager()
{

}

CSDLManager::~CSDLManager()
{
	CC_SAFE_DELETE(m_VideoSystem);
	CC_SAFE_DELETE(m_AudioSystem);
}

//Init the SDL SUB systems
bool CSDLManager::Init()
{
    PrintMessage("CSDLManager:: Init()");
	m_VideoSystem = new CVideoSystem;
    if(!m_VideoSystem->InitSystem())
    {
        PrintMessage("CSDLManager:: VideoSystem Init Failed");
        return false;
    }
    PrintMessage("CSDLManager::VideoSystem Init OK");
	m_AudioSystem = new CAudioSystem;
	if(!m_AudioSystem->InitSystem())
	{
		PrintMessage("CSDLManager:: m_AudioSystem Init Failed");
		return false;
	}
	PrintMessage("CSDLManager::m_AudioSystem Init OK");
	return true;
}

void CSDLManager::CleanSDL()
{
    PrintMessage("CSDLManager:: Cleaning SDL");
	CC_SAFE_DELETE(g_pSDLManager);
    SDL_Quit();
}
