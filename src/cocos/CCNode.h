/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __PLATFORM_CCNODE_H__
#define __PLATFORM_CCNODE_H__

#include "tool.h"

enum {
	kCCNodeTagInvalid = -1,
};

class CCNode : public CObject
{
public:
    CCNode(void);
    virtual ~CCNode(void);
    virtual bool init();
    static CCNode * create(void);

	virtual void setZOrder(int zOrder);
    virtual void _setZOrder(int z);
    virtual int getZOrder();

	virtual void setScaleX(float fScaleX);
    virtual float getScaleX();
    virtual void setScaleY(float fScaleY);
    virtual float getScaleY();
    virtual void setScale(float scale);
    virtual float getScale();
    virtual void setScale(float fScaleX,float fScaleY);
    
	virtual const CPoint nodeToParentTransform(void);
    virtual const CPoint  nodeToWorldTransform(void);
    virtual const CPoint  worldToNodeTransform(void);
    CPoint convertToNodeSpace(const CPoint& worldPoint);
	// if you want get self's pos in screen, please use CPointZero
    CPoint convertToWorldSpace(const CPoint& nodePoint);
    CPoint convertTouchToNodeSpace(CTouch * touch);
 //   CPoint convertToWindowSpace(const CPoint& nodePoint);
    virtual void setPosition(const CPoint &position);
	virtual const CPoint getLPPosition();
    virtual const CPoint getPosition();
    virtual void setPosition(float x, float y);
    virtual void getPosition(float* x, float* y);
    virtual void  setPositionX(float x);
    virtual float getPositionX(void);
    virtual void  setPositionY(float y);
    virtual float getPositionY(void);
    
    virtual void setAnchorPoint(const CPoint& anchorPoint);
    virtual const CPoint& getAnchorPoint();
    virtual const CPoint& getAnchorPointInPoints();
    
    virtual void setContentSize(const CSize& contentSize);
	virtual const CSize& getContentSize() const;
	virtual const CSize getScaledContentSize() const;

    virtual void setVisible(bool visible);
    virtual bool isVisible();

    
    
    virtual void addChild(CCNode * child);
    virtual void addChild(CCNode * child, int zOrder);
    virtual void addChild(CCNode* child, int zOrder, int tag);
    virtual CCNode * getChildByTag(int tag);
    virtual CArray* getChildren();
    virtual unsigned int getChildrenCount(void) const;
    virtual void setParent(CCNode* parent);
    virtual CCNode* getParent();
    ////// REMOVES //////
    virtual void removeFromParent();
    virtual void removeFromParentAndCleanup(bool cleanup);
    virtual void removeChild(CCNode* child);
    virtual void removeChild(CCNode* child, bool cleanup);
    virtual void removeChildByTag(int tag);
    virtual void removeChildByTag(int tag, bool cleanup);
    virtual void removeAllChildren();
    virtual void removeAllChildrenWithCleanup(bool cleanup);

    virtual void reorderChild(CCNode * child, int zOrder);
    virtual void sortAllChildren();

    virtual int getTag() const;
    virtual void setTag(int nTag);
    virtual void* getUserData();
    virtual void setUserData(void *pUserData);
    virtual CObject* getUserObject();
    virtual void setUserObject(CObject *pUserObject);

    virtual void cleanup(void);
    virtual void draw(void);
    virtual void visit(void);

    CRect boundingBox(void);


	bool m_bRunning;
	virtual bool isRunning();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
	virtual void SetAlpha(unsigned int alpha);

private:
    /// lazy allocs
    void childrenAlloc(void);
    
    /// helper that reorder a child
    void insertChild(CCNode* child, int z);
    
    /// Removes a child, call child->onExit(), do cleanup, remove it from children array.
    void detachChild(CCNode *child, bool doCleanup);

protected:
    float m_fScaleX;                    ///< scaling factor on x-axis
    float m_fScaleY;                    ///< scaling factor on y-axis
    
    CPoint m_obPosition;               ///< position of the node
    CPoint m_obAnchorPointInPoints;    ///< anchor point in points
    CPoint m_obAnchorPoint;            ///< anchor point normalized (NOT in points)
    CSize m_obContentSize;             ///< untransformed size of the node
    
    int m_nZOrder;                      ///< z-order value that affects the draw order
    
    CArray *m_pChildren;               ///< array of children nodes
    CCNode *m_pParent;                  ///< weak reference to parent node
    
	bool m_bReorderChildDirty;
    int m_nTag;                         ///< a tag. Can be any number you assigned just to identify this node
    void *m_pUserData;                  ///< A user assingned void pointer, Can be point to any cpp object
    CObject *m_pUserObject;            ///< A user assigned CCObject
    
    
    
    bool m_bVisible;                    ///< is this node visible

	unsigned int m_alpha;

};
#endif // __PLATFORM_CCNODE_H__
