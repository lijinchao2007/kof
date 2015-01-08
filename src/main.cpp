/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "define.h"
#include "tool.h"
#include "game.h"

//only for VC compiler 
#ifdef WIN32
//only include this when compiling for windows
#ifdef HAVE_OPENGLES2
#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#else
#pragma comment(lib, "glew32.lib")
#endif // HAVE_OPENGLES2
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2test.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#endif


char globalStr[1024];
int main(int argc, char **argv)
{
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);
//	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
	try
	{
		CGame::GetInstance()->InitGame();
		CGame::GetInstance()->RunGame();
	}
	catch(CError e)
	{
		SDL_ShowSimpleMessageBox(0, "error", e.GetError(), NULL);
		PrintMessage("get some erro %s ", e.GetError());
	}
	catch(...)
	{
		PrintMessage("unknown error");
	}
	CGame::GetInstance()->Quit();
	CObjCountManager::sharedManager()->printInfo();
	Common_CloseLogFile();
	return 0;
}
