/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "SffManager.h"
#include "driver/SDLManager.h"
#include "tool.h"

CSffManager::CSffManager()
{
	m_pAlloc=0;  
	m_ColorPalletMap.clear();
}

CSffManager::~CSffManager()
{
	m_pAlloc->FreeAllocater();
}

//Set the pointers to the class
void CSffManager::SetAlloc(const char* alloName)
{
	SDL_strlcpy(m_allocName, alloName, MAX_PATH);
	m_pAlloc=CMemManager::GetInstance()->GetAllocater(alloName);
}

//reste the class variables
void CSffManager::Reset()
{
	lpSffFile=0;
	nTotalImages=-1;
	nImageListSize=100;
	lpSpriteList=(SFFSPRITE*)m_pAlloc->Alloc(sizeof(SFFSPRITE)*nImageListSize);
}

//load and deccode the SFF sprite and store it in a array
bool CSffManager::ParseFile(const char *strSffFile)
{
	SetAlloc(strSffFile);
	Reset();

	SFFHEADER header;   
	PrintMessage("CSffManager::Loading %s",strSffFile);

	lpSffFile=SDL_RWFromFile(strSffFile,"rb");
	if(lpSffFile==0)
	{
		throw CError("CSffManager::Can't find %s",strSffFile);             
		return false;
	}

	//read the header of the file
	SDL_RWread(lpSffFile, &header, 1, sizeof(header));

	//check file signatur
	if(strcmp((char*)header.signature,"ElecbyteSpr")!=0)
	{
		PrintMessage("CSffManager::%s is not an SFF file",strSffFile);
		return false;                                           

	}
	PrintMessage("CSffManager::Sff file include %i images",header.NumberOfImage);

	//move the file to the first subheader
	SDL_RWseek(lpSffFile,header.SubHeaderFileOffset,RW_SEEK_SET);

	DecodeSffFile();

	SDL_RWclose(lpSffFile);

	//save memory
	//TODO:
	lpSpriteList=(SFFSPRITE*)m_pAlloc->Realloc(lpSpriteList,sizeof(SFFSPRITE)*nTotalImages);
	return true;
}

//Load an Colorpallet from file
PaletteFormat* CSffManager::GetPallet(Uint32 palNum)
{
	std::map<Uint32, PaletteFormat*>::iterator itor = m_ColorPalletMap.find(palNum);
	if (itor == m_ColorPalletMap.end())
	{
		itor = m_ColorPalletMap.begin();
	}
	return itor->second;

}
//Load an Colorpallet from file
bool CSffManager::LoadActToSff(Uint32 palNum, const char *strActFile)
{
	PrintMessage("LoadActToSff %s ", strActFile);
	SDL_RWops *Act=SDL_RWFromFile(strActFile,"rb");

	if(Act==NULL)
		PrintMessage("CSffSpriteManager %s File not found",strActFile);

	PaletteFormat* ColorPallet = (PaletteFormat*)m_pAlloc->Alloc(sizeof(PaletteFormat));
	for(int j=PALLET_SIZE-1;j>=0;j--)
	//for(int j=0;j<PALLET_SIZE;j++)
	{
		Uint8 r,g,b;    
		r=SDL_ReadU8(Act);
		g=SDL_ReadU8(Act);
		b=SDL_ReadU8(Act); 
		ColorPallet->color[j].r = r;
		ColorPallet->color[j].g = g;
		ColorPallet->color[j].b = b;
		ColorPallet->color[j].a = 0xFF;
	}
	m_ColorPalletMap.insert(std::make_pair(palNum, ColorPallet));
	SDL_RWclose(Act);
	return true;    
}


SFFSPRITE*  CSffManager::FindSprite(Sint32 nGroupNumber,Sint32 nImageNumber)
{
	if(nImageNumber == -1)return NULL;

	for(int i=0;i<nTotalImages;i++)
	{
		if(lpSpriteList[i].GroupNumber == nGroupNumber &&
			lpSpriteList[i].ImageNumber == nImageNumber)
		{    

			return &lpSpriteList[i];                                   
		}
	}

	//no image found
	return NULL;
}

void CSffManager::DecodeSffFile()
{

	SFFSUBHEADER subheader;

	Sint64 size = SDL_RWsize(lpSffFile);
	Uint8 *data = (Uint8*)m_pAlloc->Alloc(size);
	SDL_RWread(lpSffFile, data, 1, size);
	Uint8 *curdata = data;
	subheader = *(SFFSUBHEADER*)curdata;
	curdata += sizeof(SFFSUBHEADER);

	//int index = 0;
	while(curdata < data+size)
	{
		//index ++;
		//PrintMessage("1 index %d", index);
		//when we need more a bigger array to store the information that get an bigger array        
		nTotalImages++;
		if(nTotalImages > nImageListSize-1)
		{
			nImageListSize+=100;
			lpSpriteList=(SFFSPRITE*)m_pAlloc->Realloc(lpSpriteList,sizeof(SFFSPRITE)*nImageListSize);
		}

		//copy the information contained in the subheader
		/*if (subheader.GroubNumber == 5040)
		{
			PrintMessage("");
		}*/
		lpSpriteList[nTotalImages].GroupNumber=subheader.GroubNumber;
		lpSpriteList[nTotalImages].ImageNumber=subheader.ImageNumber;
		lpSpriteList[nTotalImages].x=subheader.x;
		lpSpriteList[nTotalImages].y=subheader.y;

		//is it a linked sprite??
		if(subheader.LenghtOfSubheader!=0)
		{
			//read the pcx header
			//SDL_RWread(lpSffFile, &lpSpriteList[nTotalImages].PcxHeader, 1, sizeof(PCXHEADER));
			lpSpriteList[nTotalImages].PcxHeader = *(PCXHEADER*)curdata;
			curdata += sizeof(PCXHEADER);
			//Correct the Image dimension 
			lpSpriteList[nTotalImages].PcxHeader.widht=lpSpriteList[nTotalImages].PcxHeader.widht - lpSpriteList[nTotalImages].PcxHeader.x + 1;
			lpSpriteList[nTotalImages].PcxHeader.height=lpSpriteList[nTotalImages].PcxHeader.height - lpSpriteList[nTotalImages].PcxHeader.y +1;

			//now read the pcx data 
			//TODO:check subheader.LenghtOfSubheader
			Uint32 dataLength = subheader.LenghtOfSubheader-sizeof(PCXHEADER);

			//TODO:解压逻辑放在绘制的时候处理成最终纹理
			lpSpriteList[nTotalImages].byPcxFile=curdata;
			
			//move the file pointer to Color pallet of the PCX file
			// it should be 768,but we want get the magic flag, so add 2 byte
			//fseek(lpSffFile,-770L,SEEK_CUR);
			//SDL_RWseek(lpSffFile, -770L, RW_SEEK_CUR);
			lpSpriteList[nTotalImages].bSharePallet = false;
			if(dataLength < 770){
				lpSpriteList[nTotalImages].bSharePallet = true;
			}else{
				// pal size + 1 = 769
				Uint8 flag = curdata[dataLength - 769];
				if (flag==0xC && !subheader.PalletSame && lpSpriteList[nTotalImages].PcxHeader.NPlanes<=1)
				{
					PaletteFormat* selfColorPallet = (PaletteFormat*)m_pAlloc->Alloc(sizeof(PaletteFormat));
					Uint8* palData = curdata + dataLength - 768;
					for(int j=0;j<PALLET_SIZE;j++)
					{
						Uint8 r,g,b;
						r=palData[j*3];
						g=palData[j*3+1];
						b=palData[j*3+2];
						selfColorPallet->color[j].r = r;
						selfColorPallet->color[j].g = g;
						selfColorPallet->color[j].b = b;
						selfColorPallet->color[j].a = 0xff;
					}
					//// set last pallet to be zero
					//selfColorPallet->color[0].r = 0xff;
					//selfColorPallet->color[0].g = 0xff;
					//selfColorPallet->color[0].b = 0xff;
					//selfColorPallet->color[0].a = 0;
					lpSpriteList[nTotalImages].bSharePallet = false;
					lpSpriteList[nTotalImages].ColorPallet = (PaletteFormat*)selfColorPallet;

				}else{
					lpSpriteList[nTotalImages].bSharePallet = true;
				}
			}
			curdata += dataLength;
		}
		else
		{
			//subheader.IndexOfPrevious-1 if the first ellement is 1 and not 0
			// we have a linked image here
			memcpy(&lpSpriteList[nTotalImages],
				&lpSpriteList[subheader.IndexOfPrevious],
				sizeof(SFFSPRITE));

			lpSpriteList[nTotalImages].GroupNumber=subheader.GroubNumber;
			lpSpriteList[nTotalImages].ImageNumber=subheader.ImageNumber;

		}
		
		//PrintMessage("2 index %d", index);
		if (subheader.NextSubheaderFileOffset == 0)
		{
			break;
		}
		curdata = data + subheader.NextSubheaderFileOffset - sizeof(SFFHEADER);
		subheader = *(SFFSUBHEADER*)curdata;
		curdata += sizeof(SFFSUBHEADER);
		//SDL_RWseek(lpSffFile,subheader.NextSubheaderFileOffset,RW_SEEK_SET);
		//read the next subheader
		//SDL_RWread(lpSffFile, &subheader, 1, sizeof(SFFSUBHEADER));
		//PrintMessage("3 index %d", index);
	}
	PrintMessage("CSffManager:: %i image are decoded",nTotalImages);
}

