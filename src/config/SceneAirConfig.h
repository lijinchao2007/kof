/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __SCENEAIR_CONFIG__H
#define __SCENEAIR_CONFIG__H

#include "structs.h"
#include "AirBaseConfig.h"
#include "tokenizer.h"

class CSceneAirConfig:public CAirBaseConfig
{

public:

	CSceneAirConfig();
	~CSceneAirConfig();

	BG_DEF* m_BgDef;
	BG_DEF* m_selectBG;
	BGCTRl_DEF_CONTAINER* m_BgCtrlDefCon;

	void ParseFile(const char* path);
	void InitBG(BG_ELEMENT* tmpBG);
	void ParseBG(CTokenizer& tok,  BG_DEF* bgdef);

	void ParseBGCtrlDef(CTokenizer& tok);
	void ParseBGCtrl(CTokenizer& tok);
	void ParseAction(CTokenizer& tok);

	virtual void ReAllocMem();

};

#endif