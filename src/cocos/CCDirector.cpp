/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "CCDirector.h"
#include "logic/GameTimer.h"

// singleton stuff
static CCDirector *s_SharedDirector = NULL;
CCDirector* CCDirector::sharedDirector(void)
{
	if (!s_SharedDirector)
	{
		s_SharedDirector = new CCDirector();
		s_SharedDirector->init();
	}

	return s_SharedDirector;
}

CCDirector::CCDirector(void)
{

}

bool CCDirector::init(void)
{

	// purge ?
	m_bPurgeDirecotorInNextLoop = false;
	// scenes
	m_pRunningScene = NULL;
	m_pNextScene = NULL;
	m_pobScenesStack = new CArray();
	m_pobScenesStack->init();
	// create autorelease pool
	CPoolManager::sharedPoolManager()->push();
	return true;
}

CCDirector::~CCDirector(void)
{
	CC_SAFE_RELEASE(m_pobScenesStack);
	// pop the autorelease pool
	CPoolManager::sharedPoolManager()->pop();
	CPoolManager::purgePoolManager();
	s_SharedDirector = NULL;
}


// scene management

void CCDirector::runWithScene(CCScene *pScene)
{
	CAssert(pScene != NULL, "This command can only be used to start the CCDirector. There is already a scene present.");
	CAssert(m_pRunningScene == NULL, "m_pRunningScene should be null");

	pushScene(pScene);
}

void CCDirector::replaceScene(CCScene *pScene)
{
	CAssert(m_pRunningScene, "Use runWithScene: instead to start the director");
	CAssert(pScene != NULL, "the scene should not be null");

	unsigned int index = m_pobScenesStack->count();

	m_pobScenesStack->replaceObjectAtIndex(index - 1, pScene);

	m_pNextScene = pScene;
}

void CCDirector::pushScene(CCScene *pScene)
{
	CAssert(pScene, "the scene should not null");

	m_pobScenesStack->addObject(pScene);
	m_pNextScene = pScene;
}

void CCDirector::popScene(void)
{
	CAssert(m_pRunningScene != NULL, "running scene should not null");

	m_pobScenesStack->removeLastObject();
	unsigned int c = m_pobScenesStack->count();

	if (c == 0)
	{
		end();
	}
	else
	{
		m_pNextScene = (CCScene*)m_pobScenesStack->objectAtIndex(c - 1);
	}
}

void CCDirector::end()
{
	m_bPurgeDirecotorInNextLoop = true;
}

void CCDirector::purgeDirector()
{
	PrintMessage("--purgeDirector");
	if (m_pRunningScene)
	{
		m_pRunningScene->onExit();
		m_pRunningScene->cleanup();
		m_pRunningScene->release();
	}

	// remove all objects, but don't release it.
	// runWithScene might be executed after 'end'.
	m_pobScenesStack->removeAllObjects();

	// delete CCDirector
	release();
}

void CCDirector::mainLoop(void)
{
	if (m_bPurgeDirecotorInNextLoop)
	{
		m_bPurgeDirecotorInNextLoop = false;
		purgeDirector();
	}
	else 
	{
		DEBUGBEGIN(drawScene);
		drawScene();
		DEBUGEND(drawScene);
		// release the objects
		DEBUGBEGIN(releaseobj);
		CPoolManager::sharedPoolManager()->pop();     
		DEBUGEND(releaseobj);
	}
}


// Draw the Scene
void CCDirector::drawScene(void)
{
	if (m_pNextScene)
	{
		setNextScene();
	}

	// draw the scene
	if (m_pRunningScene)
	{
		m_pRunningScene->visit();
	}

}

void CCDirector::setNextScene(void)
{
	if (m_pRunningScene)
	{
		m_pRunningScene->onExitTransitionDidStart();
		m_pRunningScene->onExit();
		m_pRunningScene->cleanup();
		m_pRunningScene->release();
	}

	m_pRunningScene = m_pNextScene;
	m_pNextScene->retain();
	m_pNextScene = NULL;

	if (m_pRunningScene)
	{
		m_pRunningScene->onEnter();
		m_pRunningScene->onEnterTransitionDidFinish();
	}
}
