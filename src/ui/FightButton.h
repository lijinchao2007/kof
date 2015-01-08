/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "cocos/UIBotton.h"

class CFightButton:public CUIBotton
{
public:
	CFightButton();
	virtual ~CFightButton();
	//bool initWithPng(const char* path);
	/** create one layer */
	static CFightButton *create(const char* path);

	virtual bool CTouchBegan(CTouch* pTouch);
	virtual void CTouchMoved(CTouch* pTouch);
	virtual void CTouchEnded(CTouch* pTouch);
	virtual void CTouchCancelled(CTouch* pTouch);

};

