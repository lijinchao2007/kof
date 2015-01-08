/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "cocos/UIBotton.h"
#include "tool.h"

class CJoyStickButton:public CUIBotton
{
protected:
	CSprite* m_JoyImage;
	DIRECTION m_lastDir;
	CPoint m_lastNormalize;
	float m_JoyChangeRange;
public:
	CJoyStickButton();
	virtual ~CJoyStickButton();
	/** create one layer */
	bool InitJoy(const char* joyicon);
	void setJoyChangeRange(float joyChangeRange);
	static CJoyStickButton *create(const char* path, const char* joyicon);

	virtual void setScale(float scale);
	virtual void setScaleX(float fScaleX);
	virtual void setScaleY(float fScaleY);

	virtual void setAnchorPoint(const CPoint& point);
	DIRECTION GetDirection(CPoint pos);
	void SetDirection(DIRECTION dir, bool isSet);

	virtual bool CTouchBegan(CTouch* pTouch);
	virtual void CTouchMoved(CTouch* pTouch);
	virtual void CTouchEnded(CTouch* pTouch);
	virtual void CTouchCancelled(CTouch* pTouch);


};

