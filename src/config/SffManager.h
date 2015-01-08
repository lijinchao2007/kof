/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __SFFMANAGER__H
#define __SFFMANAGER__H

#include "define.h"
#include <map>
#include "logic/MemManager.h"

class CSffManager
{
private:
	SDL_RWops           *lpSffFile;
	//need pointer to classes
	CAllocater     *m_pAlloc;
	char m_allocName[MAX_PATH];
	//global color pallet    
	std::map<Uint32, PaletteFormat*>   m_ColorPalletMap;
	Uint16            nTotalImages;
	Uint16            nImageListSize;
	//Sprite list 
	SFFSPRITE*      lpSpriteList;
	//decode the PCX file by run lenght 
	void DecodeSffFile();
public:
	CSffManager();
	~CSffManager();
	void SetAlloc(const char* alloName);

	//returns the current animation
	SFFSPRITE*  FindSprite(Sint32 nGroupNumber,Sint32 nImageNumber);
	bool ParseFile(const char *strSffFile);

	PaletteFormat* GetPallet(Uint32 palNum);
	bool LoadActToSff(Uint32 actNum, const char *strActFile);

	void Reset();

};

#endif
