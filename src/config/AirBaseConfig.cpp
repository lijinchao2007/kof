/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "AirBaseConfig.h"
#include "tool.h"

CAirBaseConfig::CAirBaseConfig()
	:nDefaultTotalCns1(0)
	,nDefaultTotalCns2(0)
	,nTotalCns1(0)
	,nTotalCns2(0)
	,bIsClsn1(false)
	,bDefaultClsn(false)
{
	lpActionContainer = NULL;
}

CAirBaseConfig::~CAirBaseConfig()
{
	m_pAlloc->FreeAllocater();
}

void CAirBaseConfig::SetAlloc(CAllocater* alloc)
{
	m_pAlloc = alloc;
}

void CAirBaseConfig::Reset()
{
	if(lpActionContainer != NULL)
	{
		m_pAlloc->Free(lpActionContainer);
	}
	lpActionContainer = (ActionContainer*)m_pAlloc->Alloc(sizeof(ActionContainer));

	nTotalCns1 = 0;
	nTotalCns2 = 0;
	nDefaultTotalCns1 = 0;
	nDefaultTotalCns2 = 0;
}


void CAirBaseConfig::ReAllocMem()
{
	if(lpActionContainer==NULL)return;
	lpActionContainer->nMemSize = lpActionContainer->nNumberOfAct;
	lpActionContainer->AnimationElement =(ActionElement*)m_pAlloc->Realloc(lpActionContainer->AnimationElement, sizeof(ActionElement)* lpActionContainer->nMemSize);

	ActionElement* curAct = lpActionContainer->AnimationElement;
	int i = 0;
	while (i<lpActionContainer->nNumberOfAct)
	{
		curAct->nMemSize = curAct->nNumberOfElements;
		curAct->AnimationElement = (Element*)m_pAlloc->Realloc(curAct->AnimationElement, sizeof(Element)* curAct->nMemSize);
		curAct++;
		i++;
	}
}

//add one action block int the list
void CAirBaseConfig::AddAction(Sint32 nActionNumber)
{
	// init
	if (lpActionContainer->AnimationElement == NULL)
	{
		lpActionContainer->nNumberOfAct = 0;
		lpActionContainer ->nMemSize = 100;
		lpActionContainer->AnimationElement =(ActionElement*)m_pAlloc->Alloc(sizeof(ActionElement)*lpActionContainer->nMemSize); 
	}
	lpActionContainer->nNumberOfAct++;
	// realloc
	if (lpActionContainer->nNumberOfAct>lpActionContainer->nMemSize)
	{
		lpActionContainer->nMemSize += 100;
		lpActionContainer->AnimationElement =(ActionElement*)m_pAlloc->Realloc(lpActionContainer->AnimationElement, sizeof(ActionElement)*lpActionContainer->nMemSize); 
		// init new memory
		ActionElement* curAct = lpActionContainer->AnimationElement+lpActionContainer->nNumberOfAct-1;
		SDL_memset(curAct, 0, sizeof(ActionElement)*100);
	}

	ActionElement* curAct = lpActionContainer->AnimationElement+lpActionContainer->nNumberOfAct-1;
	curAct->loopStart = -1;
	curAct->nNumberOfElements = 0;
	curAct->nActionNumber = nActionNumber;
	curAct->nCompletAnimTime = 0;

	// reset all clsn info
	nDefaultTotalCns1 = 0;
	nDefaultTotalCns2 = 0;
	nTotalCns1 = 0;
	nTotalCns2 = 0;
}

void CAirBaseConfig::AddElement(Sint32 nGroupNumber,Sint32 nImageNumber,Sint32 x,Sint32 y, Sint32 nDuringTime,SDL_RendererFlip nFlip,const char* colorStr)
{
	//PrintMessage("AddElement nGroupNumber %d, nImageNumber %d", nGroupNumber, nImageNumber);
	//if (nDuringTime == -1)
	//{
	//	PrintMessage("");
	//}
	SDL_assert(lpActionContainer!=NULL);
	SDL_assert(lpActionContainer->AnimationElement!=NULL);
	ActionElement* curAct = lpActionContainer->AnimationElement+lpActionContainer->nNumberOfAct-1;
	// init
	if (curAct->AnimationElement == NULL)
	{
		curAct->nNumberOfElements = 0;
		curAct ->nMemSize = 100;
		curAct->AnimationElement =(Element*)m_pAlloc->Alloc(sizeof(Element)*curAct->nMemSize); 
	}
	curAct->nNumberOfElements++;
	// realloc
	if (curAct->nNumberOfElements>curAct->nMemSize)
	{
		curAct->nMemSize += 100;
		curAct->AnimationElement =(Element*)m_pAlloc->Realloc(curAct->AnimationElement, sizeof(Element)*curAct->nMemSize); 
	}
	
	Element* curElement = curAct->AnimationElement + curAct->nNumberOfElements - 1;
	
	curElement->nGroupNumber=nGroupNumber;
	curElement->nImageNumber=nImageNumber;
	curElement->x=x;
	curElement->y=y;
	curElement->nDuringTime=nDuringTime;
	curElement->FlipFlags=nFlip;
	TransType nTransType = eTransTypeNone;
	if (colorStr != NULL)
	{
		if (colorStr[0] == 'S' || colorStr[0] == 's')
		{
			nTransType = eTransTypeSub;
		}else if (colorStr[0] == 'A'||colorStr[0] == 'a')
		{
			if (colorStr[1] == '1')
			{
				nTransType = eTransTypeAdd1;
			}else{
				char* srcStart = SDL_strchr(colorStr, 'S');
				char* desStart = SDL_strchr(colorStr, 'D');
				if (srcStart != NULL)
				{
					nTransType = eTransTypeAddAlpha;
					char srcStr[10], desStr[10];
					SDL_strlcpy(srcStr, srcStart+1, desStart - srcStart);
					SDL_strlcpy(desStr, desStart+1, 10);
					curElement->srcAlpha = SDL_atoi(srcStr);
					curElement->desAlpha = SDL_atoi(desStr) ;
				}else
				{
					nTransType = eTransTypeAdd;
					curElement->srcAlpha = 256;
					curElement->desAlpha = 256;
				}
				
			}

		}
	}
	curElement->TransTypes=nTransType;
	if (nDuringTime == -1)
	{
	}else{
		curAct->nCompletAnimTime+=nDuringTime;
	}
}

void CAirBaseConfig::SetLoop()
{
	SDL_assert(lpActionContainer!=NULL);
	SDL_assert(lpActionContainer->AnimationElement!=NULL);
	ActionElement* curAct = lpActionContainer->AnimationElement+lpActionContainer->nNumberOfAct-1;
	curAct->loopStart=curAct->nNumberOfElements-1;
}

void CAirBaseConfig::AddClsnToElement()
{
	SDL_assert(lpActionContainer!=NULL);
	SDL_assert(lpActionContainer->AnimationElement!=NULL);
	ActionElement* curAct = lpActionContainer->AnimationElement+lpActionContainer->nNumberOfAct-1;
	SDL_assert(curAct!=NULL);
	SDL_assert(curAct->AnimationElement!=NULL);
	Element* curElement = curAct->AnimationElement + curAct->nNumberOfElements - 1;

	/*if( curAct->nActionNumber == 20){
		PrintMessage("");
	}*/

	if(nTotalCns1==0){
		curElement->nNumberOfClsn1 = nDefaultTotalCns1;
		if (curElement->nNumberOfClsn1>0)
		{
			curElement->pClns1Data=(ClsnRECT*)m_pAlloc->Alloc(sizeof(ClsnRECT)*curElement->nNumberOfClsn1);   
			memcpy(curElement->pClns1Data, pDefaultClsn1, sizeof(ClsnRECT)*curElement->nNumberOfClsn1); 
		}
	}else{
		curElement->nNumberOfClsn1 = nTotalCns1;
		if (curElement->nNumberOfClsn1>0)
		{
			curElement->pClns1Data=(ClsnRECT*)m_pAlloc->Alloc(sizeof(ClsnRECT)*curElement->nNumberOfClsn1);  
			memcpy(curElement->pClns1Data, pClsn1, sizeof(ClsnRECT)* curElement->nNumberOfClsn1); 
		}
	}
	nTotalCns1=0;

	if(nTotalCns2==0){
		curElement->nNumberOfClsn2 = nDefaultTotalCns2;
		if (curElement->nNumberOfClsn2)
		{
			curElement->pClns2Data=(ClsnRECT*)m_pAlloc->Alloc(sizeof(ClsnRECT)*curElement->nNumberOfClsn2);   
			memcpy(curElement->pClns2Data, pDefaultClsn2, sizeof(ClsnRECT)*curElement->nNumberOfClsn2); 
		}
	}else{
		curElement->nNumberOfClsn2 = nTotalCns2;
		if (curElement->nNumberOfClsn2>0)
		{
			curElement->pClns2Data=(ClsnRECT*)m_pAlloc->Alloc(sizeof(ClsnRECT)*curElement->nNumberOfClsn2);  
			memcpy(curElement->pClns2Data, pClsn2, sizeof(ClsnRECT)* curElement->nNumberOfClsn2); 
		}
	}
	nTotalCns2=0;
}

//to add a Clsn box 
void CAirBaseConfig::AddClsnBox(s16 x,s16 y,s16 w,s16 h,int nNumberOfClsn)
{
	if (bIsClsn1&&bDefaultClsn)
	{
		pDefaultClsn1[nDefaultTotalCns1] = Common_GetTransClsn(x,y,w,h);
		nDefaultTotalCns1++;
	}
	if (bIsClsn1&&!bDefaultClsn)
	{
		pClsn1[nTotalCns1] = Common_GetTransClsn(x,y,w,h);
		nTotalCns1++;
	}

	if (!bIsClsn1&&bDefaultClsn)
	{
		pDefaultClsn2[nDefaultTotalCns2] = Common_GetTransClsn(x,y,w,h);
		nDefaultTotalCns2++;
	}
	if (!bIsClsn1&&!bDefaultClsn)
	{
		pClsn2[nTotalCns2] = Common_GetTransClsn(x,y,w,h);
		nTotalCns2++;
	}

}

void CAirBaseConfig::CreateClsnBox(u16 nNumberOfClsn,bool bClsn1,bool bDefault)
{
	SDL_assert(lpActionContainer!=NULL);
	SDL_assert(lpActionContainer->AnimationElement!=NULL);
	ActionElement* curAct = lpActionContainer->AnimationElement+lpActionContainer->nNumberOfAct-1;

	bDefaultClsn=bDefault;
	bIsClsn1=bClsn1;
	if (bDefaultClsn)
	{
		// if new default append, reset the default clsn num
		if (bIsClsn1)
		{
			nDefaultTotalCns1 = 0;
		}else{
			nDefaultTotalCns2 = 0;
		}
	}
}

ActionElement* CAirBaseConfig::GetAction(s32 nActionNumber)
{
	SDL_assert(lpActionContainer!=NULL);
	for(u16 i=0;i<lpActionContainer->nNumberOfAct;i++)
	{
		if(lpActionContainer->AnimationElement[i].nActionNumber==nActionNumber)
			return lpActionContainer->AnimationElement+i;
	}
	return NULL;
}

void CAirBaseConfig::Error(const char * strErrorMsg,CTokenizer &tok)
{
	throw(CError("Parser error:\nin file %s at line %i:\ntoken:%s\nerror:%s",tok.GetFileName()
		,tok.GetLineNumber()
		,tok.GetPartToken()
		,strErrorMsg));                  
}