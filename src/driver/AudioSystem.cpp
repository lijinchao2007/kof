/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "AudioSystem.h"
#include "tool.h"


// a simple channel_finished function
void channelDone(int channel) {
	//PrintMessage("channel %d finished playback.\n",channel);
	Mix_FreeChunk(Mix_GetChunk(channel));
}

CAudioSystem::CAudioSystem()
	:m_music(NULL)
{
}

CAudioSystem::~CAudioSystem()
{
	
}


bool CAudioSystem::InitSystem()
{
	/*m_propaudio_rate = 22050;
	m_propaudio_format = AUDIO_S16LSB;
	m_propaudio_channels = 2;
	m_propaudio_buffers = 4096;*/

	m_propaudio_rate = 22050;
	//m_propaudio_format = AUDIO_U8;
	m_propaudio_format = AUDIO_S16LSB;
	m_propaudio_channels = 1;
	m_propaudio_buffers = 4096;
	if (Mix_OpenAudio(m_propaudio_rate, m_propaudio_format, m_propaudio_channels, m_propaudio_buffers) < 0) {
		PrintMessage("Couldn't open audio: %s\n", SDL_GetError());
		return false;
	} else {
		Mix_QuerySpec(&m_propaudio_rate, &m_propaudio_format, &m_propaudio_channels);
		PrintMessage("Opened audio at %d Hz %d bit %s (%s), %d bytes audio buffer\n", m_propaudio_rate,
			(m_propaudio_format&0xFF),
			(m_propaudio_channels > 2) ? "surround" : (m_propaudio_channels > 1) ? "stereo" : "mono",
			(m_propaudio_format&0x1000) ? "BE" : "LE",
			m_propaudio_buffers );
	}

	Mix_ChannelFinished(channelDone);
	/* Set the music volume */
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	return true;
}
void CAudioSystem::CleanUp()
{
	if (m_music)
	{
		Mix_FreeMusic(m_music);
	}
	Mix_CloseAudio();
}


void CAudioSystem::PlayMusic(const char* music)
{

	if (m_music)
	{
		Mix_FreeMusic(m_music);
	}
	m_music = Mix_LoadMUS_RW(SDL_RWFromFile(music, "rb"), SDL_TRUE);
	if ( m_music == NULL ) {
		printf("Couldn't load: error %s\n",SDL_GetError());
		return;
	}
	Mix_FadeInMusic(m_music,-1,2000);
}

void CAudioSystem::PlaySound(SNDELEMENT* curElement)
{

	/* Load the requested wave file */
	Mix_Chunk* wave = Mix_QuickLoad_RAW(curElement->sound, curElement->soundlen);
	if ( wave == NULL ) {
		PrintWaring("PlaySound Couldn't load: %s\n", SDL_GetError());
		return;
	}
	/* Play and then exit */
	Mix_PlayChannel(-1, wave, 0);



	//int soundP = soundPos - P1;
	//if (soundP > 0||m_CurSndElement[0].soundpos < m_CurSndElement[0].soundlen)
	//{
	//	return;
	//}
	//SDL_LockAudio();
	//m_CurSndElement[0] = *curElement;  
	//m_CurSndElement[0].soundpos =0;
	//SDL_UnlockAudio();
}