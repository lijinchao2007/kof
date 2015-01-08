/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "MemManager.h"
#include "tool.h"

CAllocater::CAllocater(const char *strName)
{
	//copy the name
	SDL_strlcpy(strAllocName,strName, MAX_PATH);
	nAllocSize=0;
	lpMemList=NULL;                
}

CAllocater::~CAllocater()
{

}

void CAllocater::SetMemListFree(MEMLIST* lpList)
{
	memset(lpList,0,sizeof(MEMLIST)*100);   
}


void CAllocater::ResetAllocater()
{
	nAllocSize=0;
	nAllocNumber=0;
	nMemListSize=0;
	bFree=true;
	lpMemList = NULL;
	/*lpMemList=(MEMLIST*)malloc(sizeof(MEMLIST)*nMemListSize);
	SetMemListFree(lpMemList);     */
}


void CAllocater::ShowMemUsage()
{
	PrintMessage("---Memory usage of %s allocater",strAllocName); 
	PrintMessage("---Allocated memory %i in bytes",nAllocSize);
	PrintMessage("---Allocated number of Memory %i",nAllocNumber);
	// PrintMessage("////////////////////////////////////");

}
//Allocate memory and save its address in a list
void* CAllocater::Alloc(size_t nSize,int nMemInit)
{
	if(bFree)
		bFree=false;

	if(lpMemList == NULL)
	{
		//grow the list by 100
		nMemListSize=100;
		lpMemList=(MEMLIST*)malloc(sizeof(MEMLIST)*nMemListSize);
		SetMemListFree(lpMemList); 
	}
	if(nAllocNumber > nMemListSize-1)
	{
		//grow the list by 100
		nMemListSize+=100;
		lpMemList=(MEMLIST*)realloc(lpMemList,sizeof(MEMLIST)*nMemListSize);
		//set memlist empty
		SetMemListFree(&lpMemList[nMemListSize-100]);
	}


	u32 i;
	//search the list for a free place to hold the address
	for (i=0;i<nMemListSize;i++)
		if(lpMemList[i].nType==FREE) break;

	CAssert(i < nMemListSize, "CAllocater::no free block found"); 

	/* if (i == 1414)
	{
	PrintMessage("special mem");
	}*/
	lpMemList[i].nType=ALLOC;
	lpMemList[i].adrress=malloc(nSize);

	CAssert(lpMemList[i].adrress!=0, "CAllocater::malloc failed");

	memset(lpMemList[i].adrress,0,nSize);
	lpMemList[i].nSize=nSize;

	nAllocNumber++;
	nAllocSize+=nSize;

	return lpMemList[i].adrress;


}
//reallocate the given memory block and save the new address in the list
void* CAllocater::Realloc(void *CurMem,size_t nSize)
{

	u32 i;
	bool bFound=false;

	for(i=0;i<nMemListSize;i++)
	{
		if(CurMem==lpMemList[i].adrress && lpMemList[i].nType == ALLOC )
		{
			bFound=true;
			break;
		}
	}
	CAssert(bFound, "Realloc failed  was never allocated");
	nAllocSize-=lpMemList[i].nSize;
	if (nSize == 0)
	{
		free(lpMemList[i].adrress);
		lpMemList[i].adrress = NULL;
		lpMemList[i].nSize=0;
		lpMemList[i].nType = FREE;
		return NULL;
	}

	void* addr = realloc(lpMemList[i].adrress,nSize);
	if (addr == NULL)
	{
		CAssert(addr!=NULL, "realloc failed");
	}
	lpMemList[i].adrress=addr;
	lpMemList[i].nSize=nSize;
	nAllocSize+=nSize;

	return lpMemList[i].adrress;

}

//seacrh the list for the allocated block and free it from memory
void CAllocater::Free(void *CurMem)
{

	u32 i;
	bool bFound=false;

	for(i=0;i<nMemListSize;i++)
	{
		if(CurMem==lpMemList[i].adrress && lpMemList[i].nType == ALLOC )
		{
			bFound=true;
			break;
		}
	}

	if(!bFound)
		PrintMessage("free failed %x was never allocated",CurMem);

	free(lpMemList[i].adrress);
	lpMemList[i].adrress=0;
	lpMemList[i].nType=FREE;
	nAllocSize-=lpMemList[i].nSize;

	nAllocNumber--;

}


//Free all allocated memory
void CAllocater::FreeAllocater()
{
	if(!bFree)
	{
		for(u32 i=0;i<nMemListSize;i++)
		{
			if(lpMemList[i].nType==ALLOC){
				free(lpMemList[i].adrress);   
				lpMemList[i].adrress = NULL;
				lpMemList[i].nType = FREE;
			}
		}
		nMemListSize = 0;
	} 
	// PrintMessage("CAllocater::%s unfreed %i bytes",strAllocName,nAllocSize);
	//clear ouer memlist  
	if(lpMemList!=NULL){
		CC_SAFE_FREE(lpMemList);
	}
	ResetAllocater();
}

/*
*	manager
*/
CMemManager::CMemManager()
{

}

CMemManager::~CMemManager()
{
	FreeManager();
}

void CMemManager::InitManager()
{
	m_AllocMap.clear();
}

CAllocater* CMemManager::GetAllocater(const char* alloName)
{
	CAllocater* tmpAlloc;
	std::map<std::string, CAllocater*>::iterator cIter = m_AllocMap.find(alloName);
	if (cIter == m_AllocMap.end())
	{
		tmpAlloc = new CAllocater(alloName);
		tmpAlloc->ResetAllocater();
		m_AllocMap[alloName] = tmpAlloc;
	}else
	{
		tmpAlloc = (CAllocater*)cIter->second;
	}
	return tmpAlloc;          
}

bool CMemManager::DestroyAllocater(const char* alloName)
{
	std::map<std::string, CAllocater*>::iterator cIter = m_AllocMap.find(alloName);
	if (cIter == m_AllocMap.end())
	{
		return false;
	}else
	{
		cIter->second->FreeAllocater();
		delete cIter->second;
		m_AllocMap.erase(cIter);
		return true;
	}
}

//free all the allocaters from mem
void CMemManager::FreeManager()
{

	for (std::map<std::string, CAllocater*>::iterator cIter=m_AllocMap.begin();cIter!=m_AllocMap.end(); cIter++)
	{
		CAllocater* alloc = cIter->second;
		alloc->FreeAllocater();
		delete alloc;
	}
	m_AllocMap.clear();
}
//show and return the memusage
size_t CMemManager::GetMemUsage()
{
	size_t nMem=0;

	PrintMessage("======================Memory Manager============================");
	//PrintMessage("sizeof(SFFSUBHEADER) %d", sizeof(SFFSUBHEADER));
	//PrintMessage("sizeof(SFFSPRITE) %d", sizeof(SFFSPRITE));
	//PrintMessage("sizeof(PCXHEADER) %d", sizeof(PCXHEADER));
	//PrintMessage("sizeof(SDL_Color) %d", sizeof(SDL_Color));
	PrintMessage("|Name:               |Alloc Num     |Allocated Kbytes          |"); 
	PrintMessage("----------------------------------------------------------------");

	for (std::map<std::string, CAllocater*>::iterator cIter=m_AllocMap.begin();cIter!=m_AllocMap.end(); cIter++)
	{
		CAllocater* alloc = (CAllocater*)cIter->second;
		PrintMessage("|%20s|%15d |%15.4f KB | ",alloc->GetName(), alloc->GetAllNum(), alloc->GetMemUsage()/1024.0);
		nMem ++;
	}
	PrintMessage("================================================================");  
	return nMem;

}

void CMemManager::Test()
{

	for (int j=0;j<10000;j++)
	{
		/*Uint8* tmpaddr[200];
		for (int i=0;i<200;i++)
		{
		tmpaddr[i] = (Uint8*)malloc(10000);
		}
		PrintMessage("reday");
		for (int i=0;i<200;i++)
		{
		free(tmpaddr[i]);
		}*/

		/*CAllocater* tmpAlloc;
		tmpAlloc = new CAllocater("test");
		tmpAlloc->ResetAllocater();
		for (int i =0;i<200;i++)
		{
		Uint8* t = (Uint8*)tmpAlloc->Alloc(1000);
		SDL_memset(t, 1, 1000);
		}
		tmpAlloc->ShowMemUsage();
		tmpAlloc->FreeAllocater();
		delete tmpAlloc;*/
		PrintMessage("sdjfisdfhasidfs");
	}

}

CMemManager* CMemManager::GetInstance()
{
	if ( g_pMemInstance == NULL )  //判断是否第一次调用
		g_pMemInstance = new CMemManager();
	return g_pMemInstance;
}

void CMemManager::Destroy()
{
	CC_SAFE_DELETE(g_pMemInstance);
}
