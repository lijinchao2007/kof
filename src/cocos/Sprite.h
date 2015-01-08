/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __SPRITE_H_
#define __SPRITE_H_

#include "CCNode.h"
#include "tool.h"
#include "CCTexture2D.h"

class CSprite:public CCNode
{
protected:
	char m_String[MAX_PATH];
	SFFSPRITE* m_spr;
	CCTexture2D* m_image;
	CCTexture2D* m_stringImage;
public:
	CSprite();
	virtual ~CSprite();

	bool init(const char* png);
	bool init(SFFSPRITE* spr);
	static CSprite* create(const char* png);
	static CSprite* create(SFFSPRITE* spr);

	void SetString(const char* str);

	const char* GetString(){return m_String;};
	void draw();
};

#endif