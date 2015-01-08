/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "SndConfig.h"
#include "tool.h"
#include "driver/SDLManager.h"

CSndConfig::CSndConfig()
{
	m_pAlloc=0;  
}

CSndConfig::~CSndConfig()
{
	m_pAlloc->FreeAllocater();
}


//Set the pointers to the class
void CSndConfig::SetAlloc(const char* alloName)
{
	SDL_strlcpy(m_allocName, alloName, MAX_PATH);
	m_pAlloc=CMemManager::GetInstance()->GetAllocater(alloName);
}

//reste the class variables
void CSndConfig::Reset()
{
	nTotalSnd=0;
	nSndListSize=100;
	lpSndList=(SNDELEMENT*)m_pAlloc->Alloc(sizeof(SNDELEMENT)*nSndListSize);
}

SNDELEMENT*  CSndConfig::FindSnd(Sint32 nGroupNumber,Sint32 nSoundNo)
{
	for (int i = 0;i<nTotalSnd;i++)
	{
		SNDELEMENT* curElement = lpSndList+i;
		if (curElement->nGroupNumber == nGroupNumber && curElement->nSoundNumber == nSoundNo)
		{
			return curElement;
		}
	}
	return NULL;
}
bool CSndConfig::ParseFile(const char *strFile)
{
	SetAlloc(strFile);
	Reset();

	SNDHEADER header;   
	PrintMessage("ParseFile::Loading %s",strFile);

	SDL_RWops* lpSndFile=SDL_RWFromFile(strFile,"rb");
	if(lpSndFile==0)
	{
		throw CError("CSndConfig::Can't find %s",strFile);             
		return false;
	}

	//read the header of the file
	SDL_RWread(lpSndFile, &header, 1, sizeof(header));

	//check file signatur
	if(strcmp((char*)header.strSignatur,"ElecbyteSnd")!=0)
	{
		PrintMessage("ParseFile::%s is not an Snd file",strFile);
		return false;                                           

	}
	PrintMessage("CSndConfig::snd file include %i snd",header.nNumberOfSounds);

	////move the file to the first subheader
	SDL_RWseek(lpSndFile,header.SubHeaderFileOffset,RW_SEEK_SET);
	DecodeSndFile(lpSndFile);
	SDL_RWclose(lpSndFile);

	nSndListSize = nTotalSnd;
	lpSndList=(SNDELEMENT*)m_pAlloc->Realloc(lpSndList,sizeof(SNDELEMENT)*nSndListSize);
	return true;
}


void CSndConfig::DecodeSndFile(SDL_RWops* lpSndFile)
{
	Uint16 audio_format = CSDLManager::GetInstance()->GetAudioSystem()->GetPropaudio_format();
	int audio_channels = CSDLManager::GetInstance()->GetAudioSystem()->GetPropaudio_channels();
	int audio_rate = CSDLManager::GetInstance()->GetAudioSystem()->GetPropaudio_rate();
	//set convert 
	SDL_AudioCVT  wav_cvt;
	SDL_AudioSpec wav_spec;
	Uint32 wav_len;
	Uint8 *wav_buf;
	int samplesize;

	SNDSUBHEADER subheader;
	//read the first subheader
	SDL_RWread(lpSndFile, &subheader,1,sizeof(SNDSUBHEADER));

	Sint64 size = SDL_RWsize(lpSndFile);
	while(SDL_RWtell(lpSndFile) < size)
	{
		//when we need more a bigger array to store the information that get an bigger array                    
		if(nTotalSnd > nSndListSize-1)
		{
			nSndListSize+=100;
			lpSndList=(SNDELEMENT*)m_pAlloc->Realloc(lpSndList,sizeof(SNDELEMENT)*nSndListSize);
		}

		SNDELEMENT* curSnd = lpSndList+nTotalSnd;
		curSnd->nGroupNumber = subheader.nGroupNumber;
		curSnd->nSoundNumber = subheader.nSoundNumber;
		if (curSnd->nGroupNumber == 220 && curSnd->nSoundNumber == 2)
		{
			PrintMessage("");
		}
		if(SDL_LoadWAV_RW(lpSndFile,0, &wav_spec, &wav_buf, &wav_len) == NULL)
		{
			CError("Could not open snd %d %d: %s\n", curSnd->nGroupNumber, curSnd->nSoundNumber, SDL_GetError());
		}

		if ( wav_spec.format != audio_format ||
			wav_spec.channels != audio_channels ||
			wav_spec.freq != audio_rate ) 
		{
			if ( SDL_BuildAudioCVT(&wav_cvt,
				wav_spec.format, wav_spec.channels, wav_spec.freq,
				audio_format, audio_channels, audio_rate) < 0 ) {
					throw CError("SDL_BuildAudioCVT failed!");
			}

			samplesize = ((wav_spec.format & 0xFF)/8)*wav_spec.channels;
			wav_cvt.len = wav_len & ~(samplesize-1);
			wav_cvt.buf=(Uint8 *)m_pAlloc->Alloc(wav_cvt.len*wav_cvt.len_mult);
			if ( wav_cvt.buf == NULL ) {
				throw CError("Out of memory");
			}
			SDL_memcpy(wav_cvt.buf, wav_buf, wav_len);
			SDL_FreeWAV(wav_buf);

			if ( SDL_ConvertAudio(&wav_cvt) < 0 ) {
				throw CError("SDL_ConvertAudio failed!");
			}
			wav_buf=(Uint8 *)m_pAlloc->Realloc(wav_cvt.buf, wav_cvt.len_cvt);
			/*wav_buf = wav_cvt.buf;*/
			wav_len = wav_cvt.len_cvt;
		}
		curSnd->soundlen = wav_len;
		curSnd->sound=wav_buf;

		/*ret = SDL_BuildAudioCVT(&wav_cvt, wav_spec.format, wav_spec.channels, wav_spec.freq,
			audio_format,  audio_channels, audio_rate);
		if(ret==-1){
			CError("Couldn't build converter!");
		}
		wav_cvt.buf=(Uint8 *)m_pAlloc->Alloc(wav_len*wav_cvt.len_mult);
		wav_cvt.len=wav_len;
		memcpy(wav_cvt.buf, wav_buf, wav_len);
		SDL_FreeWAV(wav_buf);
		SDL_ConvertAudio(&wav_cvt);
		curSnd->soundlen = wav_cvt.len_cvt;
		curSnd->sound=(Uint8 *)m_pAlloc->Realloc(wav_cvt.buf, curSnd->soundlen);*/


		nTotalSnd++;
		SDL_RWseek(lpSndFile,subheader.NextSubHeaderFileOffset,RW_SEEK_SET);
		//read the next subheader
		SDL_RWread(lpSndFile, &subheader, 1, sizeof(SNDSUBHEADER));
	}
	PrintMessage("CSndConfig:: %i sound are decoded",nTotalSnd);

}