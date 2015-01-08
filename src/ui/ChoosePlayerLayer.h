/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "cocos/CCLayer.h"
#include "cocos/UIBotton.h"



class ChoosePlayerLayer:public CCLayer
{
public:
	ChoosePlayerLayer();
	virtual ~ChoosePlayerLayer();

	/** create one layer */
	static ChoosePlayerLayer *create(void);
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();
	virtual void visit();
	virtual void draw();

	void ChooseCB(CUIBotton* btn, CTouch* ptouchs);
private:
	CUIBotton* m_start;
	CSprite* m_playerOne;
	CSprite* m_playerTwo;
	int m_state;
};

