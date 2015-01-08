/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef _AIRBASECONFIG_H_
#define _AIRBASECONFIG_H_

#include "logic/MemManager.h"
#include "tokenizer.h"

class CAirBaseConfig
{
public:
	CAllocater         *m_pAlloc;
	ActionContainer *lpActionContainer;

	bool          bDefaultClsn;
	bool          bIsClsn1;
	ClsnRECT          pClsn1[MAX_CLSN_COUNT];
	Sint16           nTotalCns1;
	ClsnRECT          pClsn2[MAX_CLSN_COUNT];
	Sint16           nTotalCns2;
	ClsnRECT          pDefaultClsn1[MAX_CLSN_COUNT];
	Sint16           nDefaultTotalCns1;
	ClsnRECT          pDefaultClsn2[MAX_CLSN_COUNT];
	Sint16           nDefaultTotalCns2;

public:
	CAirBaseConfig();
	~CAirBaseConfig();

public:
	virtual void SetAlloc(CAllocater* alloc);
	virtual void AddAction(Sint32 nActionNumber);
	virtual void AddElement(Sint32 nGroupNumber,Sint32 nImageNumber,Sint32 x,Sint32 y, Sint32 nDuringTime,SDL_RendererFlip nFlip,const char* TransType);
	virtual void AddClsnToElement();
	virtual void SetLoop();
	virtual void AddClsnBox(s16 x,s16 y,s16 w,s16 h,int nNumberOfClsn);
	virtual void CreateClsnBox(u16 nNumberOfClsn,bool bClsn1,bool bDefault);

	virtual ActionElement* GetAction(s32 nActionNumber);
	virtual void ReAllocMem();
	virtual void Reset();

	virtual void Error(const char * strErrorMsg,CTokenizer &tok);
};
#endif
