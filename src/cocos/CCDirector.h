/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

#include "define.h"
#include "tool.h"
#include "CCScene.h"

class CCDirector : public CObject
{
public:
    CCDirector(void);
    virtual ~CCDirector(void);
    virtual bool init(void);

	void mainLoop(void);

    /** Get current running Scene. Director can only run one Scene at the time */
    inline CCScene* getRunningScene(void) { return m_pRunningScene; }
    void runWithScene(CCScene *pScene);
    void pushScene(CCScene *pScene);
    void popScene(void);
    void popToRootScene(void);
    void replaceScene(CCScene *pScene);
    void drawScene(void);
	void setNextScene(void);

	void end(void);
public:
    static CCDirector* sharedDirector(void);
	void purgeDirector();

protected:
    CCScene *m_pRunningScene;
    CCScene *m_pNextScene;
    CArray* m_pobScenesStack;
	
	bool m_bPurgeDirecotorInNextLoop; // this flag will be set to true in end()
};

#endif // __CCDIRECTOR_H__
