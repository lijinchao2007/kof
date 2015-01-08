/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __MYAUDIO_H__
#define __MYAUDIO_H__
#include "define.h"
#include "structs.h"
#include "SDL_mixer.h"

class CAudioSystem
{

public:
	Mix_Music *m_music;
	Prop_Get_Set(int, audio_rate);
	Prop_Get_Set(Uint16, audio_format);
	Prop_Get_Set(int, audio_channels);
	Prop_Get_Set(int, audio_buffers);

public:
	CAudioSystem();
	~CAudioSystem();

	bool InitSystem();
	void CleanUp();
	void PlayMusic(const char* music);
	void PlaySound(SNDELEMENT* curElement);
};


#endif
