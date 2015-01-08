/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __COMMON__H
#define __COMMON__H
#include "structs.h"
#include <stdio.h>

void Common_SetDesiginWidth(Sint32 value);
void Common_SetDesiginHeight(Sint32 value);
void Common_SetScreenWidth(Sint32 value);
void Common_SetScreenHeight(Sint32 value);
void Common_SetStartPosX(Sint32 value);
void Common_SetStartPosY(Sint32 value);

Sint32 Common_GetDesiginWidth();
Sint32 Common_GetDesiginHalfWidth();
Sint32 Common_GetDesiginHeight();
Sint32 Common_GetScreenWidth();
Sint32 Common_GetScreenHeight();
Sint32 Common_GetStartPosX();
Sint32 Common_GetStartPosY();

void Common_SetScaleX(float value);
void Common_SetScaleY(float value);
float Common_GetScaleX();
float Common_GetScaleY();

static FILE* fileHander;
void Common_LogToFile(const char *fmt, ...);
void Common_CloseLogFile();

ClsnRECT Common_MoveRect(s16 x1, s16 y1, ClsnRECT& r);
bool Common_rectIntersectsRect(ClsnRECT r1, ClsnRECT r2);
ClsnRECT Common_GetTransClsn(s16 x, s16 y, s16 w, s16 h);
// revert rect
ClsnRECT Common_GetRevertClsn(ClsnRECT &r);

#endif
