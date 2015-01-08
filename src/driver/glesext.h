/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __GLEXEXT_H_
#define __GLEXEXT_H_

#ifdef __cplusplus
extern "C" {
#endif
	/*
	typedef struct GLES2_Context
	{
	#define SDL_PROC(ret,func,params) ret (APIENTRY *func) params;
	#include "../src/render/opengles2/SDL_gles2funcs.h"
	#undef SDL_PROC
	} GLES2_Context;

	#define GL_CHECK(x) \
	x; \
	{ \
	GLenum glError = glGetError(); \
	if(glError != GL_NO_ERROR) { \
	SDL_Log("OpenGL error 0x%04X %04d in %s %s %d\n", glError,glError, __FILE__, __FUNCTION__, __LINE__); \
	quit(1); \
	} \
	}*/

extern void SwapWindow();
extern void quit(int);

//extern int LoadContext();
extern int SetUpGLES(Sint32 screenW, Sint32 screenH);
//extern GLES2_Context* GetglesCtx();

#ifdef __cplusplus
}
#endif




#endif
