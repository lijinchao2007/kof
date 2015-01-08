/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "Input.h"
#include "logic/GameTimer.h"
#include "logic/engine.h"
#include "config/ConfigManager.h"
#include "game.h"
#include "ui/GameLayer.h"
#include "ui/ChoosePlayerLayer.h"
#include "ui/MenuLayer.h"
#include "cocos.h"
#include "SDLManager.h"


static CTouch* s_pTouches[CC_MAX_TOUCHES] = { NULL };
static Uint32 s_indexBitsUsed = 0;
static std::map<int, int> s_TouchesIdToIndexDict;

static int getUnUsedIndex()
{
	int i;
	int temp = s_indexBitsUsed;

	for (i = 0; i < CC_MAX_TOUCHES; i++) {
		if (! (temp & 0x00000001)) {
			s_indexBitsUsed |= (1 <<  i);
			return i;
		}

		temp >>= 1;
	}

	// all bits are used
	return -1;
}

static void removeUsedIndexBit(int index)
{
	if (index < 0 || index >= CC_MAX_TOUCHES) 
	{
		return;
	}

	unsigned int temp = 1 << index;
	temp = ~temp;
	s_indexBitsUsed &= temp;
}


CInput* CInput::GetInstance()
{
	if ( pInputInstance == NULL )  
		pInputInstance = new CInput();
	return pInputInstance;
}

void CInput::Destroy()
{
	CC_SAFE_DELETE(pInputInstance);
}

static SDL_Event event;
static int watch(void* data, SDL_Event* e)
{
	event = *e;
	CInput::GetInstance()->Dispatch();
	return 1;
}

//Constructor
CInput::CInput()
{
	// restet m_KeyData
	for( int k = 0; k < KEY_COUNT; k++ )
	{
		m_vectorKeyData[k] = false;
	}
	m_propTouchDelegate = NULL;

	//SDL_AddEventWatch(watch, NULL);
}
//Destructor
CInput::~CInput()
{

}


//Checks the SDL event list
void CInput::CheckSDL()
{

	while (SDL_PollEvent(&event))
	{
		Dispatch();
	}
	//if(count)PrintMessage("CheckSDL get event count");
	/**/
}


void CInput::Dispatch()
{
	if(event.type==SDL_QUIT)
	{
		PrintMessage("SDL_QUIT");
		CGame::GetInstance()->StopGame();
	}

	if(event.type==SDL_KEYUP)
	{
		m_nhistoryKey = 0;
	}
	if(event.type==SDL_KEYDOWN&&m_nhistoryKey!=event.key.keysym.sym)
	{
		m_nhistoryKey = event.key.keysym.sym;
		//PrintMessage("SDL_KEYDOWN m_nhistoryKey %d", m_nhistoryKey);
		//通过不同的键标检测来选择表面
		switch(event.key.keysym.sym)
		{
		case 1073742094:
			CGame::GetInstance()->StopGame();
			break;
		case SDLK_ESCAPE:
			CGame::GetInstance()->StopGame();
			break;

		case SDLK_PAUSE:
			if(CGame::GetInstance()->IsPause())
			{
				CGame::GetInstance()->ContinueGame();
			}else{
				CGame::GetInstance()->PauseGame();
			}
			break;
		case SDLK_SCROLLLOCK:
			if(CGame::GetInstance()->IsPause())
			{
				CGame::GetInstance()->RunLogic();
			}
			PrintMessage("continue");
			break;
		case SDLK_d:
			if(event.key.keysym.mod & KMOD_CTRL){
				CEngine::GetInstance()->ChangeDebug();
			}
			break;
		case SDLK_x:
			if(event.key.keysym.mod & KMOD_CTRL){
				CEngine::GetInstance()->ChangeDrawType();
			}
			break;
		case SDLK_c:
			if(event.key.keysym.mod & KMOD_CTRL){
				// draw the fron and back dis
				CEngine::GetInstance()->SetClsn();
			}
			break;
		case SDLK_t:
			if(event.key.keysym.mod & KMOD_CTRL){
				// draw the fron and back dis
				CMemManager::GetInstance()->Test();
			}
			break;
		case SDLK_p:
			if(event.key.keysym.mod & KMOD_CTRL){
				CMemManager::GetInstance()->GetMemUsage();
				CGame::GetInstance()->SetPropIsDebugTime(true);
				CObjCountManager::sharedManager()->printInfo();
				//CEngine::GetInstance()->m_player1->DebugInfoToBack();
			}
			break;

		case SDLK_n:
			if(event.key.keysym.mod & KMOD_CTRL){
				PrintMessage("change to choose!");
				CCScene* scene = CCScene::create();
				scene->addChild(ChoosePlayerLayer::create());
				CCDirector::sharedDirector()->replaceScene(scene);
			}
			break;
		case SDLK_m:
			if(event.key.keysym.mod & KMOD_CTRL){
				PrintMessage("change to menu!");
				CCScene* scene = CCScene::create();
				scene->addChild(CMenuLayer::create());
				CCDirector::sharedDirector()->replaceScene(scene);
			}
			break;
		case SDLK_g:
			if(event.key.keysym.mod & KMOD_CTRL){
				PrintMessage("change auto guard!");
				CEngine::GetInstance()->ChangeAutoGuard();
			}
			break;

		case SDLK_0:
			if(event.key.keysym.mod & KMOD_CTRL){
				CEngine::GetInstance()->SetPlayer1AI(0);
			}
			if(event.key.keysym.mod & KMOD_ALT){
				CEngine::GetInstance()->SetPlayer2AI(0);
			}
			break;
		case SDLK_1:
			if(event.key.keysym.mod & KMOD_CTRL){
				CEngine::GetInstance()->SetPlayer1AI(1);
			}
			if(event.key.keysym.mod & KMOD_ALT){
				CEngine::GetInstance()->SetPlayer2AI(1);
			}
			break;
		case SDLK_2:
			if(event.key.keysym.mod & KMOD_CTRL){
				CEngine::GetInstance()->SetPlayer1AI(2);
			}
			if(event.key.keysym.mod & KMOD_ALT){
				CEngine::GetInstance()->SetPlayer2AI(2);
			}
			break;
		case SDLK_3:
			if(event.key.keysym.mod & KMOD_CTRL){
				CEngine::GetInstance()->SetPlayer1AI(3);
			}
			if(event.key.keysym.mod & KMOD_ALT){
				CEngine::GetInstance()->SetPlayer2AI(3);
			}
			break;
		case SDLK_4:
			if(event.key.keysym.mod & KMOD_CTRL){
				CEngine::GetInstance()->SetPlayer1AI(4);
			}
			if(event.key.keysym.mod & KMOD_ALT){
				CEngine::GetInstance()->SetPlayer2AI(4);
			}
			break;

		case SDLK_F1:
			CEngine::GetInstance()->m_player1->RecordCommandEnd();
			break;
		case SDLK_F2:
			CEngine::GetInstance()->m_player1->RecordCommand();
			break;
		case SDLK_F3:
			CEngine::GetInstance()->m_player1->RecordPlay();
			break;
		case SDLK_F4:
			CEngine::GetInstance()->m_player1->SaveRecord();
			break;
		case SDLK_F5:
			CEngine::GetInstance()->m_player1->LoadRecord();
			break;
		}
	}

	int width =Common_GetScreenWidth();
	int height = Common_GetScreenHeight();
	if (event.type == SDL_MOUSEBUTTONDOWN&&!event.button.which)
	{
		handleTouchesBegin(0, event.button.x, event.button.y);
	}
	if (event.type == SDL_MOUSEMOTION&&!event.button.which)
	{
		handleTouchesMove(0, event.button.x, event.button.y);
	}
	if (event.type == SDL_MOUSEBUTTONUP&&!event.button.which)
	{
		handleTouchesEnd(0, event.button.x, event.button.y);
	}


	if (event.type == SDL_FINGERDOWN)
	{
		int id = event.tfinger.fingerId;
		handleTouchesBegin(id, event.tfinger.x*width, event.tfinger.y*height);
	}
	if (event.type == SDL_FINGERMOTION)
	{
		int id = event.tfinger.fingerId;
		handleTouchesMove(id, event.tfinger.x*width, event.tfinger.y*height);
	}
	if (event.type == SDL_FINGERUP)
	{
		int id = event.tfinger.fingerId;
		handleTouchesEnd(id, event.tfinger.x*width, event.tfinger.y*height);
	}
}

void CInput::handleTouchesBegin(int id, float x, float y)
{
	CTouch* pTouch = NULL;
	std::map<int, int>::iterator iter;
	iter = s_TouchesIdToIndexDict.find(id);
	int nUnusedIndex = 0;
	// it is a new touch
	if (iter == s_TouchesIdToIndexDict.end())
	{
		nUnusedIndex = getUnUsedIndex();
		// The touches is more than MAX_TOUCHES ?
		if (nUnusedIndex == -1) {
			PrintMessage("The touches is more than MAX_TOUCHES, nUnusedIndex = %d", nUnusedIndex);
		}else{
			pTouch = new CTouch();
			s_pTouches[nUnusedIndex]  = pTouch;
			pTouch->setTouchInfo(nUnusedIndex, x, y);
			s_TouchesIdToIndexDict.insert(std::pair<int, int>(id, nUnusedIndex));
		}
	}

	if (pTouch == NULL)
	{
		//PrintMessage("no new touch for touch begin");
		return;
	}
	if(this->m_propTouchDelegate != NULL)
	{
		this->m_propTouchDelegate->CTouchBegan(pTouch);
	}
}

void CInput::handleTouchesMove(int id, float x, float y)
{
	CTouch* pTouch = NULL;
	std::map<int, int>::iterator iter;
	iter = s_TouchesIdToIndexDict.find(id);
	if (iter == s_TouchesIdToIndexDict.end())
	{
		//PrintWaring("if the index doesn't exist, it is an error");
		return;
	}

	//PrintMessage("Moving touches with id: %d, x=%f, y=%f", id, x, y);
	int pIndex = iter->second;
	pTouch = s_pTouches[pIndex];
	if (pTouch)
	{
		pTouch->setTouchInfo(pIndex, x, y);
	}
	else
	{
		// It is error, should return.
		PrintWaring("Moving touches with id: %d error", id);
		return;
	}

	if(this->m_propTouchDelegate != NULL)
	{
		this->m_propTouchDelegate->CTouchMoved(pTouch);
	}
}

CTouch* CInput::getTouchesEndOrCancel(int id, float x, float y)
{
	std::map<int, int>::iterator iter;
	iter = s_TouchesIdToIndexDict.find(id);
	if (iter == s_TouchesIdToIndexDict.end())
	{
		//PrintWaring("if the index doesn't exist, it is an error");
		return NULL;
	}
	/* Add to the set to send to the director */
	int pIndex = iter->second;
	CTouch* pTouch = s_pTouches[pIndex];        
	if (pTouch)
	{
		//PrintMessage("Ending touches with id: %d, x=%f, y=%f", id, x, y);
		pTouch->setTouchInfo(pIndex, x, y);
		// release the object
		s_pTouches[pIndex] = NULL;
		removeUsedIndexBit(pIndex);
		s_TouchesIdToIndexDict.erase(id);
	} 
	else
	{
		PrintWaring("Ending touches with id: %d error", id);
	} 
	return pTouch;
}

void CInput::handleTouchesEnd(int id, float x, float y)
{
	CTouch* ptouch = getTouchesEndOrCancel(id, x, y);
	if (ptouch)
	{
		if(this->m_propTouchDelegate != NULL)
		{
			this->m_propTouchDelegate->CTouchEnded(ptouch);
		}
		delete ptouch;
	}
}

void CInput::handleTouchesCancel(int id, float x, float y)
{
	CTouch* ptouch = getTouchesEndOrCancel(id, x, y);
	if (ptouch)
	{
		if(this->m_propTouchDelegate != NULL)
		{
			this->m_propTouchDelegate->CTouchCancelled(ptouch);
		}
		delete ptouch;
	}
}

//Process InputData
void CInput::ProcessInput(KEYBOARDDATA *lpKeyBoard)
{
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    
    if( lpKeyBoard->bKeyBoard )
    {
        for( int k = 0; k < KEY_COUNT; k++ )
        {
            lpKeyBoard->keyInfo[ k ].isPressed = keystate[ lpKeyBoard->keyInfo[ k ].sdlKeycode ];
        }
    }  
}

//Process InputData
void CInput::ProcessTouch(KEYBOARDDATA *lpKeyBoard)
{

	if( lpKeyBoard->bKeyBoard )
	{
		for( int k = 0; k < KEY_COUNT; k++ )
		{
			if (m_vectorKeyData[k])
			{
				lpKeyBoard->keyInfo[ k ].isPressed = m_vectorKeyData[k];
			}
		}
	}  
}