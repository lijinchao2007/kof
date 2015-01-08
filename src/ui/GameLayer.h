/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __GAMELAYER_H_
#define __GAMELAYER_H_

#include "cocos/CCLayer.h"
#include "cocos/UIBotton.h"
#include "cocos/CCProgressTimer.h"

class GameLayer:public CCLayer
{
public:
	CCProgressTimer*	m_Pro1;
	CCProgressTimer*	m_Pro2;
	CCProgressTimer*	m_ProPower1;
	CCProgressTimer*	m_ProPower2;
public:
	GameLayer();
	virtual ~GameLayer();

	/** create one layer */
	static GameLayer *create(void);
	virtual bool init();
	
	virtual void onEnter();
	virtual void onExit();
	virtual void visit();
	virtual void draw();
    
	void BtnClicked(CUIBotton* btn, CTouch* ptouch);
	void OnLifeChanged(Sint32 id, Sint32 maxlife, Sint32 startlife, Sint32 changedlife);
	void OnPowerChanged(Sint32 id, Sint32 max, Sint32 start, Sint32 changed);
private:

};

#endif