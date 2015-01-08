/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "cocos/CCLayer.h"
#include "cocos/UIBotton.h"

class CMenuLayer:public CCLayer
{
public:
	CMenuLayer();
	virtual ~CMenuLayer();

	/** create one layer */
	static CMenuLayer *create(void);
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();
	virtual void visit();
	virtual void draw();
    
    void OnBtnClicked(CUIBotton* btn, CTouch* ptouch);
private:

};

