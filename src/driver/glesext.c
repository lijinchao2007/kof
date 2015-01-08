/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "define.h"
#include "glesext.h"
static SDLTest_CommonState *state;
//static GLES2_Context ctx;
//
//int LoadContext()
//{
//#if SDL_VIDEO_DRIVER_UIKIT
//#define __SDL_NOGETPROCADDR__
//#elif SDL_VIDEO_DRIVER_ANDROID
//#define __SDL_NOGETPROCADDR__
//#elif SDL_VIDEO_DRIVER_PANDORA
//#define __SDL_NOGETPROCADDR__
//#endif
//
//#if defined __SDL_NOGETPROCADDR__
//#define SDL_PROC(ret,func,params) ctx.func=func;
//#else
//#define SDL_PROC(ret,func,params) \
//	do { \
//	ctx.func = SDL_GL_GetProcAddress(#func); \
//	SDL_Log(#func);\
//	if ( ! ctx.func ) { \
//	return SDL_SetError("Couldn't load GLES2 function %s: %s\n", #func, SDL_GetError()); \
//	} \
//	} while ( 0 );
//#endif /* _SDL_NOGETPROCADDR_ */
//
//#include "../src/render/opengles2/SDL_gles2funcs.h"
//#undef SDL_PROC
//	return 0;
//}

//GLES2_Context* GetglesCtx()
//{
//	return &ctx;
//}


void
quit(int rc)
{
    exit(rc);
}


void SwapWindow()
{
	SDL_GL_SwapWindow(state->windows[0]);
}

 int SetUpGLES(Sint32 screenW, Sint32 screenH)
 {
	 SDL_DisplayMode mode;
	 SDL_GLContext* context;
	 int status;
	 /* Initialize test framework */
	 char* argv[1] = {"kof"};
	 int i;

	 state = SDLTest_CommonCreateState(argv, SDL_INIT_VIDEO);
	 if (!state) {
		 return 1;
	 }
	 /* Set OpenGL parameters */
	 state->window_flags |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	 state->gl_red_size = 5;
	 state->gl_green_size = 5;
	 state->gl_blue_size = 5;
	 state->gl_depth_size = 24;
	 state->gl_major_version = 2;
	 state->gl_minor_version = 0;
#ifdef HAVE_OPENGLES2
	 state->gl_profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#endif // WIN32


#ifdef WIN32
	 state->window_w = screenW;
	 state->window_h = screenH;
#else
	 state->window_x = 0;
	 state->window_y = 0;
#endif // WIN32

	 if (!SDLTest_CommonInit(state)) {
		 return 0;
	 }

	 context = (SDL_GLContext *)SDL_calloc(state->num_windows, sizeof(context));
	 if (context == NULL) {
		 return 0;
	 }
	 /* Create OpenGL ES contexts */
	 for (i = 0; i < state->num_windows; i++) {
		 context[i] = SDL_GL_CreateContext(state->windows[i]);
		 if (!context[i]) {
			 return 0;
		 }
	 }

	 if (state->render_flags & SDL_RENDERER_PRESENTVSYNC) {
		 SDL_GL_SetSwapInterval(1);
	 } else {
		 SDL_GL_SetSwapInterval(0);
	 }
	 SDL_GetCurrentDisplayMode(0, &mode);
	 SDL_Log("Screen bpp: %d\n", SDL_BITSPERPIXEL(mode.format));
	 SDL_Log("Vendor     : %s\n", glGetString(GL_VENDOR));
	 SDL_Log("Renderer   : %s\n", glGetString(GL_RENDERER));
	 SDL_Log("Version    : %s\n", glGetString(GL_VERSION));
	 SDL_Log("Extensions : %s\n", glGetString(GL_EXTENSIONS));

	 /* Set rendering settings for each context */
	 for (i = 0; i < state->num_windows; ++i) {

		 status = SDL_GL_MakeCurrent(state->windows[i], context[i]);
		 if (status) {
			 SDL_Log("SDL_GL_MakeCurrent(): %s\n", SDL_GetError());

			 /* Continue for next window */
			 continue;
		 }
		 glViewport(0, 0, state->window_w, state->window_h);
	 }
#ifndef HAVE_OPENGLES2
	 if (GLEW_OK != glewInit())
	 {
		 SDL_Log("OpenGL error");
		 return 0;
	 }
#endif // win
	 return 1;
 }