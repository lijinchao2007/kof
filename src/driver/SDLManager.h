/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef _SDL_MANAGER_H_
#define _SDL_MANAGER_H_
#include "VideoSystem.h"
#include "AudioSystem.h"
class CSDLManager
{
public:
	CSDLManager();
	~CSDLManager();
    bool Init();
    void CleanSDL();
	CVideoSystem* GetVideoSystem(){return m_VideoSystem;}
	CAudioSystem* GetAudioSystem(){return m_AudioSystem;}
    
public:
	CVideoSystem* m_VideoSystem;
	CAudioSystem* m_AudioSystem;

public:
	static CSDLManager *GetInstance();
};

static CSDLManager* g_pSDLManager;

#endif