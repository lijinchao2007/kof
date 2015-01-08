/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "SelectConfig.h"
#include "tool.h"


//Constructor
CSelectConfig::CSelectConfig()
{
	m_selectList.roleCount = m_selectList.roleMemSize = 0;
	m_stageCount =0;
	m_selectList.rolelist = NULL;
}

//Destructor
CSelectConfig::~CSelectConfig()
{
}


bool CSelectConfig::ParseCfg(const char* file)
{
	PrintMessage(" CSelectConfig::ParseCfg %s ", file);
	m_pAlloc = CMemManager::GetInstance()->GetAllocater(file);
	CToken tok;
	if( !tok.OpenFile(file) )
		throw(CError("CSelectConfig::ParseCfg: File %s not found",file));

	tok.SetIsCaseSensitive(false);

	while(!tok.AtEndOfFile())
	{
		bool bFoundSection = false;
		if(tok.CheckToken("[") )
		{
			if( tok.CheckToken("Characters") )
			{
				PrintMessage("deal Characters");
				bFoundSection=true;
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);
				while (!tok.CheckToken("[", false)&&!tok.AtEndOfFile())
				{
					ParseSelectLine(tok);
				}

			}else if( tok.CheckToken("ExtraStages") )
			{
				PrintMessage("deal ExtraStages");
				bFoundSection=true;
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);

				while (!tok.CheckToken("[", false)&&!tok.AtEndOfFile())
				{
					tok.GetToken(m_stageList[Min(19, m_stageCount)], MAX_STRING_LENGTH);
					m_stageCount++;
					GET_ALL_LINE(tok);
				}
			}else if( tok.CheckToken("Options") )
			{
				PrintMessage("deal Options");
				bFoundSection=true;
				if(!tok.CheckToken("]"))
					Error("need ] ", tok);

				while (!tok.CheckToken("[", false)&&!tok.AtEndOfFile())
				{
					if (tok.CheckToken("arcade.maxmatches"))
					{
						tok.CheckToken("=");
						int index = 0;
						do 
						{
							m_arcade[index++] = tok.GetInt();
						} while (tok.CheckToken(","));
					}else if (tok.CheckToken("team.maxmatches"))
					{
						tok.CheckToken("=");
						int index = 0;
						do 
						{
							m_team[index++] = tok.GetInt();
						} while (tok.CheckToken(","));
					}else{
						while (!tok.AtEnd()){
							tok.GetToken();
						}
					}
				}
			}
		}
		if(!bFoundSection)
		{
			PrintMessage("not deal %s", tok.GetToken());
		}
	}
	tok.CloseFile();
	return true;
}

void CSelectConfig::ParseSelectLine(CToken &tok)
{
	if (m_selectList.rolelist== NULL)
	{
		m_selectList.roleMemSize = 100;
		m_selectList.rolelist = (SelectRoleInfo*)m_pAlloc->Alloc(m_selectList.roleMemSize*sizeof(SelectRoleInfo));
	}
	if (m_selectList.roleCount>=m_selectList.roleMemSize)
	{
		m_selectList.roleMemSize += 100;
		m_selectList.rolelist = (SelectRoleInfo*)m_pAlloc->Realloc(m_selectList.rolelist, m_selectList.roleMemSize*sizeof(SelectRoleInfo));
	}
	SelectRoleInfo* curInfo = m_selectList.rolelist + m_selectList.roleCount;
	tok.GetToken(curInfo->name, MAX_STRING_LENGTH);
	PrintMessage("ParseSelectLine %s ", curInfo->name);
	if (tok.CheckToken(","))
	{
		if (tok.CheckToken(","))
		{
		}else{
			tok.GetToken(curInfo->stagename, MAX_STRING_LENGTH);
		}

		// parse params
		do
		{
			if (tok.CheckToken("includestage"))
			{
				if (!tok.CheckToken("="))
					Error("need =", tok);
				curInfo->includestage = tok.GetInt();
			}else if (tok.CheckToken("music"))
			{
				if (!tok.CheckToken("="))
					Error("need =", tok);
				tok.GetToken(curInfo->musicName, MAX_STRING_LENGTH);
			}else if (tok.CheckToken("order"))
			{
				if (!tok.CheckToken("="))
					Error("need =", tok);
				curInfo->order = tok.GetInt();
			}
		}while (tok.CheckToken(","));

	}
	curInfo->isPhotoLoaded = false;
	m_selectList.roleCount ++;
	GET_ALL_LINE(tok);
} 

bool CSelectConfig::LoadHeadSpr()
{
	for (int i=0;i<m_selectList.roleCount;i++)
	{
		SelectRoleInfo* curRoleInfo = m_selectList.rolelist+i;
		char* name = curRoleInfo->name;
		if (SDL_strcasecmp("randomselect", name) != 0)
		{
			LoadOneHeadSpr(i);
		}
	}
	return true;
}


bool CSelectConfig::LoadOneHeadSpr(int index)
{
	char configPath[MAX_PATH] = {0};
	SelectRoleInfo* curInfo = m_selectList.rolelist + index;
	char* name = curInfo->name;
	SDL_snprintf(configPath, MAX_PATH, "chars/%s/%s.def", name, name);

	CToken tok;
	if( !tok.OpenFile(configPath) )
		return false;

	tok.SetIsCaseSensitive(false);
	bool isfound = false;
	while( !tok.AtEndOfFile()&&!isfound )
	{
		if( tok.CheckToken("[") )
		{
			if (tok.CheckToken("Files"))
			{
				if(!tok.CheckToken("]"))
					Error("need ]", tok);
				while (!tok.CheckToken("[")&&!tok.AtEndOfFile()&&!isfound)
				{
					if (tok.CheckToken("sprite"))
					{
						if(!tok.CheckToken("="))
							Error("need =", tok);
						isfound = true;
						tok.GetToken(configPath, MAX_PATH);
					}
					tok.GetToken();
				}
			}

		}
		tok.GetToken();
	}
	tok.CloseFile();
	PrintMessage("GetRoleSpr %s", configPath);


	char strSffFile[MAX_PATH];
	SDL_snprintf(strSffFile, MAX_PATH, "chars/%s/%s", name, configPath);
	SFFHEADER header;   
	SDL_RWops* lpSffFile=SDL_RWFromFile(strSffFile,"rb");
	if(lpSffFile==0)
	{
		return false;
	}
	//read the header of the file
	SDL_RWread(lpSffFile, &header, 1, sizeof(header));
	//check file signatur
	if(strcmp((char*)header.signature,"ElecbyteSpr")!=0)
	{
		SDL_RWclose(lpSffFile);
		PrintMessage("CSffManager::%s is not an SFF file",strSffFile);
		return false;                                           
	}
	//move the file to the first subheader
	SDL_RWseek(lpSffFile,header.SubHeaderFileOffset,RW_SEEK_SET);


	SFFSUBHEADER subheader;
	Uint8 *tempByte;
	//read the first subheader
	SDL_RWread(lpSffFile, &subheader,1,sizeof(SFFSUBHEADER));
	Sint64 size = SDL_RWsize(lpSffFile);
	SFFSPRITE* ret = NULL;
	bool is1seted =false, is0seted = false;
	while(SDL_RWtell(lpSffFile) < size)
	{
		if (subheader.GroubNumber==9000&&(subheader.ImageNumber == 0||subheader.ImageNumber==1))
		{
			if (subheader.ImageNumber==0)
			{
				is0seted = true;
				ret = &curInfo->headphoto;
			}
			if (subheader.ImageNumber==1)
			{
				is1seted = true;
				ret = &curInfo->photo;
			}
			ret->GroupNumber=subheader.GroubNumber;
			ret->ImageNumber=subheader.ImageNumber;
			ret->x=subheader.x;
			ret->y=subheader.y;

			//is it a linked sprite??
			CAssert(subheader.LenghtOfSubheader!=0, "is a linked sprite");
			//read the pcx header
			SDL_RWread(lpSffFile, &ret->PcxHeader, 1, sizeof(PCXHEADER));
			ret->PcxHeader.widht=ret->PcxHeader.widht - ret->PcxHeader.x + 1;
			ret->PcxHeader.height=ret->PcxHeader.height - ret->PcxHeader.y +1;

			Uint32 dataLength = subheader.LenghtOfSubheader-sizeof(PCXHEADER);
			tempByte=(Uint8*)m_pAlloc->Alloc(dataLength);
			SDL_RWread(lpSffFile, tempByte, 1, dataLength);
			ret->byPcxFile=tempByte;

			// pal size + 1 = 769
			Uint8 flag = tempByte[dataLength - 769];
			PaletteFormat* selfColorPallet = (PaletteFormat*)m_pAlloc->Alloc(sizeof(PaletteFormat));
			Uint8* palData = tempByte + dataLength - 768;
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
			ret->bSharePallet = false;
			ret->ColorPallet = (PaletteFormat*)selfColorPallet;

			
			if (is1seted&&is0seted)
			{
				SDL_RWclose(lpSffFile);
				curInfo->isPhotoLoaded = true;
				return true;
			}
		}

		SDL_RWseek(lpSffFile,subheader.NextSubheaderFileOffset,RW_SEEK_SET);
		//read the next subheader
		SDL_RWread(lpSffFile, &subheader, 1, sizeof(SFFSUBHEADER));
	}

	SDL_RWclose(lpSffFile);
	return false;
}
