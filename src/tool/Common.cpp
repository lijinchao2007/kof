/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include <math.h>
#include "Common.h"
#include "ccMacros.h"

static Sint32 g_DesiginWidth;
static Sint32 g_DesiginHalfWidth;
static Sint32 g_DesiginHeight;
static Sint32 g_ScreenWidth;
static Sint32 g_ScreenHeight;
static Sint32 g_StartPosX;
static Sint32 g_StartPosY;
static float g_ScaleX;
static float g_ScaleY;
void Common_SetDesiginWidth(Sint32 value)
{
	g_DesiginHalfWidth = value*0.5;
	g_DesiginWidth = value;
	
}
void Common_SetDesiginHeight(Sint32 value)
{
	g_DesiginHeight = value;
}

void Common_SetScreenWidth(Sint32 value)
{
	g_ScreenWidth = value;
}
void Common_SetScreenHeight(Sint32 value)
{
	g_ScreenHeight = value;
}
void Common_SetStartPosX(Sint32 value)
{
	g_StartPosX = value;
}
void Common_SetStartPosY(Sint32 value)
{
	g_StartPosY = value;
}

Sint32 Common_GetDesiginWidth()
{
	return g_DesiginWidth;
}
Sint32 Common_GetDesiginHalfWidth()
{
	return g_DesiginHalfWidth;
}
Sint32 Common_GetDesiginHeight()
{
	return g_DesiginHeight;
}

Sint32 Common_GetScreenWidth()
{
	return g_ScreenWidth;
}
Sint32 Common_GetScreenHeight()
{
	return g_ScreenHeight;
}

Sint32 Common_GetStartPosX()
{
	return g_StartPosX;
}
Sint32 Common_GetStartPosY()
{
	return g_StartPosY;
}

void Common_SetScaleX(float value)
{
	g_ScaleX = value;
}
void Common_SetScaleY(float value)
{
	g_ScaleY = value;
}


float Common_GetScaleX()
{
	return g_ScaleX;
}
float Common_GetScaleY()
{
	return g_ScaleY;
}


void Common_LogToFile(const char *fmt, ...)
{
#ifdef __WIN32__
	if (fileHander == NULL)
	{
		fileHander  = fopen("debug.log", "wt"); 
	}

	va_list ap;
	va_start(ap, fmt);
	char *message;
	message = SDL_stack_alloc(char, SDL_MAX_LOG_MESSAGE);
	if (!message) {
		return;
	}
	SDL_vsnprintf(message, SDL_MAX_LOG_MESSAGE, fmt, ap);
	va_end(ap);
	fwrite(message, SDL_strlen(message), 1, fileHander);
	SDL_stack_free(message);
	fwrite("\n", 1, 1, fileHander);
	fflush(fileHander);
#endif // __WIN32__
}

void Common_CloseLogFile()
{
#ifdef __WIN32__
	if (fileHander != NULL)
	{
		fclose(fileHander);
	}
#endif // __WIN32__
}

bool Common_rectIntersectsRect(ClsnRECT rectA, ClsnRECT rectB)
{
	bool ret = ! (  rectA.x > rectB.x + rectB.w ||
		rectA.x + rectA.w < rectB.x ||
		rectA.y > rectB.y +rectB.h ||
		rectA.y + rectA.h < rectB.y );
	return ret;
};
// absolute rect
ClsnRECT Common_MoveRect(s16 x, s16 y, ClsnRECT& r)
{
	ClsnRECT rect;
	rect.x = r.x+x;
	rect.y = r.y+y;
	rect.w = r.w;
	rect.h = r.h;
	return rect;
};

// mugen rect to screen rect
ClsnRECT Common_GetTransClsn(s16 x1, s16 y1, s16 w1, s16 h1)
{
	s16 x = Min(x1, w1);
	s16 y = Min(y1, h1);
	s16 w = abs(w1 - x1);
	s16 h = abs(h1 - y1);
	ClsnRECT rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
};

// mugen rect to screen rect
ClsnRECT Common_GetRevertClsn(ClsnRECT &r)
{
	ClsnRECT rect;
	rect.x = -r.x-r.w;
	rect.y = r.y;
	rect.w = r.w;
	rect.h = r.h;
	return rect;
};


