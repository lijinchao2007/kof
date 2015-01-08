/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/


#ifndef __HELPER__H
#define __HELPER__H
#include "structs.h"
#include "tool.h"
#include "player.h"

class CHelper:public CPlayer
{
	bool m_bKeyCtrl;
	bool m_bOwnPal;
	EnumHelperType m_helpertype;
public:
	CHelper();
	virtual  ~CHelper();

	void InitWithParent(Uint32 id, CPlayer* parent);

public:
	void SetKeyCtrl(bool isctrl){m_bKeyCtrl = isctrl;};
	void SetOwnPal(bool ispal){m_bOwnPal = ispal;};
	void SetHelperType(EnumHelperType type){m_helpertype = type;};

public:
	virtual void UpdateCommand();
	virtual void HandleSYSFSM();
	virtual void HandleSYSStateNo();

	virtual void UpDateFacing();
	virtual void UpdateCamera();
};

#endif
