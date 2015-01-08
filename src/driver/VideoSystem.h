/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef VIDEO_H
#define VIDEO_H
#include "define.h"
#include "structs.h"
#include "tool.h"
#include "logic/MemManager.h"
#include "cocos/CCTexture2D.h"
#include "glesext.h"


class CVideoSystem
{
	SDL_Window *sdlWindow;
	SDL_Texture* m_fontTexture;
	CAllocater* m_pAlloc;
public:
	Sint32 m_renderInfoMemSize;
	Sint32 m_renderInfoSize;
	ccCArray* m_renderPoolArray;
	ccCArray* m_array;
public:
	CVideoSystem();
	~CVideoSystem();

	bool InitSystem();
	void CleanUp();
	void Draw();
	void Clear();

	//normal Blt
	void UnusedAllRenderInfo();
	RenderInfo* GetUnusedRenderInfo();
	void AddRenderInfo(RenderInfo* info);

	void DrawRect(Uint8 R, Uint8 G, Uint8 B,int x,int y,int width,int heigth, ENUM_DRAW_RECT_TYPE drawType, float srcAlpha=1, float desAlpha=0, Sint32 priority=SPR_PRIORITY_DEBUG);
	void DrawText(int x,int y,const char *strText,...);
	void DrawTexture(DrawInfo& info, CCTexture2D* texture, Sint32 priority);
	void NormalBlt(DrawInfo& drawInfo, PalFXInfo* palFXinfo, Sint32 sprpriority=0);
	void BltAfterImage(AfterImageStack& afterimageStack, int curPos, int effectCount);

	void RerderSpr(DrawInfo& drawInfo, PalFXInfo* palFXinfo);
	void PalFX(CCTexture2D* img, PalFXInfo* palFXinfo);
	void RenderAfterImage(DrawInfo& drawInfo, int effectCount, AfterImage* config);
	//primitiv functions
	void RenderDrawLines(Uint8 R, Uint8 G, Uint8 B,Uint8 pointSize,GLfloat* vertices, int verCount);
	void RenderDrawRect(Uint8 R, Uint8 G, Uint8 B,int x,int y,int width,int heigth, ENUM_DRAW_RECT_TYPE drawType, float srcAlpha=1, float desAlpha=0);
	void Render();

public:
	SDL_Renderer  *m_sdlRenderer;
	Uint8* deltaPtr;

	//Vector_Get_Set(CImage*, MaxAfterImageSize, AfterImageVector);

};


#endif
