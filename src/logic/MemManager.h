/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __MEMMANAGER__H
#define __MEMMANAGER__H
#include <map>
#include <string>
#include "define.h"
#include "structs.h"

class CAllocater
{

   char strAllocName[255];
   size_t  nAllocSize;
   size_t  nAllocNumber;
   size_t  nMemListSize;
   MEMLIST *lpMemList;
   bool bFree;
   
enum { FREE=0x00,
       ALLOC=0xff

      };
      void SetMemListFree(MEMLIST* lpList); 
public:
      //Constructor & Desctructor 
      CAllocater(const char *strName);
      ~CAllocater();
      
      void ShowMemUsage();
      void* Alloc(size_t nSize,int nMemInit = 0);
      void* Realloc(void *CurMem,size_t nSize);
      void  Free(void *CurMem);
      void  FreeAllocater();
      void ResetAllocater();
	  size_t   GetMemUsage(){return nAllocSize;}
	  size_t   GetAllNum(){return nAllocNumber;}
      char *GetName(){return strAllocName;}        
      
};

class CMemManager
{
	std::map<std::string, CAllocater*> m_AllocMap;
public:
      //Constructor & Desctructor  
      CMemManager();
      ~CMemManager();
      
      void InitManager();
      CAllocater *GetAllocater(const char* alloName);
	  bool DestroyAllocater(const char* alloName);
      void FreeManager();
      size_t GetMemUsage();
	  void Test();
public:
	static CMemManager *GetInstance();
	static void Destroy();

private:

};

static CMemManager* g_pMemInstance = NULL;

  
#endif
