/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#include "CCNode.h"

CCNode::CCNode(void):
	 m_fScaleX(1.0f)
	, m_fScaleY(1.0f)
	, m_obPosition(CPointZero)
	, m_obAnchorPointInPoints(CPointZero)
	, m_obAnchorPoint(CPointZero)
	, m_obContentSize(CSizeZero)
	, m_nZOrder(0)
	, m_bRunning(false)
	, m_pChildren(NULL)
	, m_pParent(NULL)
	, m_bReorderChildDirty(false)
	, m_nTag(kCCNodeTagInvalid)
	, m_pUserData(NULL)
	, m_pUserObject(NULL)
	, m_bVisible(true)
	, m_alpha(255)
{

}

CCNode::~CCNode(void)
{
    CC_SAFE_RELEASE(m_pUserObject);

    if(m_pChildren && m_pChildren->count() > 0)
    {
        CObject* child;
        CARRAY_FOREACH(m_pChildren, child)
        {
            CCNode* pChild = (CCNode*) child;
            if (pChild)
            {
                pChild->m_pParent = NULL;
            }
        }
    }

    // children
    CC_SAFE_RELEASE(m_pChildren);
}

bool CCNode::init()
{
    return true;
}


/// zOrder getter
int CCNode::getZOrder()
{
    return m_nZOrder;
}

/// zOrder setter : private method
/// used internally to alter the zOrder variable. DON'T call this method manually 
void CCNode::_setZOrder(int z)
{
    m_nZOrder = z;
}

void CCNode::setZOrder(int z)
{
    _setZOrder(z);
    if (m_pParent)
    {
        m_pParent->reorderChild(this, z);
    }
}


/// scale getter
float CCNode::getScale(void)
{
    CAssert( m_fScaleX == m_fScaleY, "CCNode#scale. ScaleX != ScaleY. Don't know which one to return");
    return m_fScaleX;
}

/// scale setter
void CCNode::setScale(float scale)
{
    m_fScaleX = m_fScaleY = scale;
}

/// scale setter
void CCNode::setScale(float fScaleX,float fScaleY)
{
    m_fScaleX = fScaleX;
    m_fScaleY = fScaleY;
}

/// scaleX getter
float CCNode::getScaleX()
{
    return m_fScaleX;
}

/// scaleX setter
void CCNode::setScaleX(float newScaleX)
{
    m_fScaleX = newScaleX;
}

/// scaleY getter
float CCNode::getScaleY()
{
    return m_fScaleY;
}

/// scaleY setter
void CCNode::setScaleY(float newScaleY)
{
    m_fScaleY = newScaleY;
}

void CCNode::SetAlpha(unsigned int alpha)
{
	m_alpha = alpha;
}

// left-right corner pos
const CPoint CCNode::nodeToParentTransform(void)
{
	float x = m_obPosition.x;
	float y = m_obPosition.y;
	x -= m_obAnchorPointInPoints.x* m_fScaleX;
	y -= m_obAnchorPointInPoints.y* m_fScaleY;
	return ccp(x,y);
}

const CPoint CCNode::nodeToWorldTransform()
{
	CPoint t = this->nodeToParentTransform();

	for (CCNode *p = m_pParent; p != NULL; p = p->getParent())
		t = ccpAdd(t, p->nodeToParentTransform());

	return t;
}

const CPoint CCNode::worldToNodeTransform(void)
{
	return ccpSub(CPointZero, this->nodeToWorldTransform());
}


CPoint CCNode::convertToNodeSpace(const CPoint& worldPoint)
{
	CPoint ret = ccpAdd(worldPoint, worldToNodeTransform());
	return ret;
}

CPoint CCNode::convertToWorldSpace(const CPoint& nodePoint)
{
	CPoint ret = ccpAdd(nodePoint, nodeToWorldTransform());
	return ret;
}


// convenience methods which take a CCTouch instead of CPoint
CPoint CCNode::convertTouchToNodeSpace(CTouch *touch)
{
	CPoint point = touch->getLocation();
	return this->convertToNodeSpace(point);
}

//CPoint CCNode::convertToWindowSpace(const CPoint& nodePoint)
//{
//	CPoint worldPoint = this->convertToWorldSpace(nodePoint);
//	return CCDirector::sharedDirector()->convertToUI(worldPoint);
//}

/// left-up pos
const CPoint CCNode::getLPPosition()
{
	CPoint p = ccp(m_obAnchorPointInPoints.x*m_fScaleX, m_obAnchorPointInPoints.y*m_fScaleY);
	return ccpSub(CPointZero, p);
}

/// position getter
const CPoint CCNode::getPosition()
{
    return m_obPosition;
}

/// position setter
void CCNode::setPosition(const CPoint& newPosition)
{
    m_obPosition = newPosition;
}

void CCNode::getPosition(float* x, float* y)
{
    *x = m_obPosition.x;
    *y = m_obPosition.y;
}

void CCNode::setPosition(float x, float y)
{
    setPosition(ccp(x, y));
}

float CCNode::getPositionX(void)
{
    return m_obPosition.x;
}

float CCNode::getPositionY(void)
{
    return  m_obPosition.y;
}

void CCNode::setPositionX(float x)
{
    setPosition(ccp(x, m_obPosition.y));
}

void CCNode::setPositionY(float y)
{
    setPosition(ccp(m_obPosition.x, y));
}

/// children getter
CArray* CCNode::getChildren()
{
    return m_pChildren;
}

unsigned int CCNode::getChildrenCount(void) const
{
    return m_pChildren ? m_pChildren->count() : 0;
}


/// isVisible getter
bool CCNode::isVisible()
{
    return m_bVisible;
}

/// isVisible setter
void CCNode::setVisible(bool var)
{
    m_bVisible = var;
}

const CPoint& CCNode::getAnchorPointInPoints()
{
    return m_obAnchorPointInPoints;
}

/// anchorPoint getter
const CPoint& CCNode::getAnchorPoint()
{
    return m_obAnchorPoint;
}

void CCNode::setAnchorPoint(const CPoint& point)
{
    if( ! point.equals(m_obAnchorPoint))
    {
        m_obAnchorPoint = point;
        m_obAnchorPointInPoints = ccp(m_obContentSize.width * m_obAnchorPoint.x, m_obContentSize.height * m_obAnchorPoint.y );
    }
}

/// contentSize getter
const CSize& CCNode::getContentSize() const
{
    return m_obContentSize;
}

/// contentSize getter
const CSize CCNode::getScaledContentSize() const
{
	return CSizeMake(m_obContentSize.width*m_fScaleX, m_obContentSize.height*m_fScaleY);
}

void CCNode::setContentSize(const CSize & size)
{
    if ( ! size.equals(m_obContentSize))
    {
        m_obContentSize = size;

        m_obAnchorPointInPoints = ccp(m_obContentSize.width * m_obAnchorPoint.x, m_obContentSize.height * m_obAnchorPoint.y );
    }
}

/// parent getter
CCNode * CCNode::getParent()
{
    return m_pParent;
}
/// parent setter
void CCNode::setParent(CCNode * var)
{
    m_pParent = var;
}


/// tag getter
int CCNode::getTag() const
{
    return m_nTag;
}

/// tag setter
void CCNode::setTag(int var)
{
    m_nTag = var;
}

/// userData getter
void * CCNode::getUserData()
{
    return m_pUserData;
}

/// userData setter
void CCNode::setUserData(void *var)
{
    m_pUserData = var;
}

CObject* CCNode::getUserObject()
{
    return m_pUserObject;
}


void CCNode::setUserObject(CObject *pUserObject)
{
    CC_SAFE_RETAIN(pUserObject);
    CC_SAFE_RELEASE(m_pUserObject);
    m_pUserObject = pUserObject;
}


CRect CCNode::boundingBox()
{
	CPoint scPos = convertToWorldSpace(CPointZero);
    CRect rect = CRectMake(scPos.x, scPos.y, m_obContentSize.width*m_fScaleX, m_obContentSize.height*m_fScaleY);
	return rect;
}

CCNode * CCNode::create(void)
{
	CCNode * pRet = new CCNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void CCNode::cleanup()
{
    // timers
    arrayMakeObjectsPerformSelector(m_pChildren, cleanup, CCNode*);
}


// lazy allocs
void CCNode::childrenAlloc(void)
{
    m_pChildren = CArray::createWithCapacity(4);
    m_pChildren->retain();
}

CCNode* CCNode::getChildByTag(int aTag)
{
    CAssert( aTag != kCCNodeTagInvalid, "Invalid tag");

    if(m_pChildren && m_pChildren->count() > 0)
    {
        CObject* child;
        CARRAY_FOREACH(m_pChildren, child)
        {
            CCNode* pNode = (CCNode*) child;
            if(pNode && pNode->m_nTag == aTag)
                return pNode;
        }
    }
    return NULL;
}

/* "add" logic MUST only be on this method
* If a class want's to extend the 'addChild' behavior it only needs
* to override this method
*/
void CCNode::addChild(CCNode *child, int zOrder, int tag)
{    
    CAssert( child != NULL, "Argument must be non-nil");
    CAssert( child->m_pParent == NULL, "child already added. It can't be added again");

    if( ! m_pChildren )
    {
        this->childrenAlloc();
    }

    this->insertChild(child, zOrder);

    child->m_nTag = tag;

    child->setParent(this);

}

void CCNode::addChild(CCNode *child, int zOrder)
{
    CAssert( child != NULL, "Argument must be non-nil");
    this->addChild(child, zOrder, child->m_nTag);
}

void CCNode::addChild(CCNode *child)
{
    CAssert( child != NULL, "Argument must be non-nil");
    this->addChild(child, child->m_nZOrder, child->m_nTag);
}

void CCNode::removeFromParent()
{
    this->removeFromParentAndCleanup(true);
}

void CCNode::removeFromParentAndCleanup(bool cleanup)
{
    if (m_pParent != NULL)
    {
        m_pParent->removeChild(this,cleanup);
    } 
}

void CCNode::removeChild(CCNode* child)
{
    this->removeChild(child, true);
}

/* "remove" logic MUST only be on this method
* If a class want's to extend the 'removeChild' behavior it only needs
* to override this method
*/
void CCNode::removeChild(CCNode* child, bool cleanup)
{
    // explicit nil handling
    if (m_pChildren == NULL)
    {
        return;
    }

    if ( m_pChildren->containsObject(child) )
    {
        this->detachChild(child,cleanup);
    }
}

void CCNode::removeChildByTag(int tag)
{
    this->removeChildByTag(tag, true);
}

void CCNode::removeChildByTag(int tag, bool cleanup)
{
    CAssert( tag != kCCNodeTagInvalid, "Invalid tag");

    CCNode *child = this->getChildByTag(tag);

    if (child == NULL)
    {
        PrintWaring("cocos2d: removeChildByTag(tag = %d): child not found!", tag);
    }
    else
    {
        this->removeChild(child, cleanup);
    }
}

void CCNode::removeAllChildren()
{
    this->removeAllChildrenWithCleanup(true);
}

void CCNode::removeAllChildrenWithCleanup(bool cleanup)
{
    // not using detachChild improves speed here
    if ( m_pChildren && m_pChildren->count() > 0 )
    {
        CObject* child;
        CARRAY_FOREACH(m_pChildren, child)
        {
            CCNode* pNode = (CCNode*) child;
            if (pNode)
            {
                if (cleanup)
                {
                    pNode->cleanup();
                }
                // set parent nil at the end
                pNode->setParent(NULL);
            }
        }
        
        m_pChildren->removeAllObjects();
    }
}

void CCNode::detachChild(CCNode *child, bool doCleanup)
{

    // If you don't do cleanup, the child's actions will not get removed and the
    // its scheduledSelectors_ dict will not get released!
    if (doCleanup)
    {
        child->cleanup();
    }

    // set parent nil at the end
    child->setParent(NULL);

    m_pChildren->removeObject(child);
}


// helper used by reorderChild & add
void CCNode::insertChild(CCNode* child, int z)
{
	m_bReorderChildDirty = true;
    m_pChildren->addObject(child);
    child->_setZOrder(z);
}

void CCNode::reorderChild(CCNode *child, int zOrder)
{
    CAssert( child != NULL, "Child must be non-nil");
	m_bReorderChildDirty = true;
    child->_setZOrder(zOrder);
}

void CCNode::sortAllChildren()
{
    if (m_bReorderChildDirty)
    {
        int i,j,length = m_pChildren->data->num;
        CCNode ** x = (CCNode**)m_pChildren->data->arr;
        CCNode *tempItem;

        // insertion sort
        for(i=1; i<length; i++)
        {
            tempItem = x[i];
            j = i-1;

            //continue moving element downwards while zOrder is smaller or when zOrder is the same but mutatedIndex is smaller
            while(j>=0 && ( tempItem->m_nZOrder < x[j]->m_nZOrder || ( tempItem->m_nZOrder== x[j]->m_nZOrder) ) )
            {
                x[j+1] = x[j];
                j = j-1;
            }
            x[j+1] = tempItem;
        }

        //don't need to check children recursively, that's done in visit of each child

        m_bReorderChildDirty = false;
    }
}

// isRunning getter
bool CCNode::isRunning()
{
	return m_bRunning;
}

void CCNode::onEnter()
{
	//fix setTouchEnabled not take effect when called the function in onEnter in JSBinding.
	m_bRunning = true;

	//Judge the running state for prevent called onEnter method more than once,it's possible that this function called by addChild  
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CObject* child;
		CCNode* node;
		CARRAY_FOREACH(m_pChildren, child)
		{
			node = (CCNode*)child;
			if (!node->isRunning())
			{
				node->onEnter();
			}            
		}
	}
}

void CCNode::onEnterTransitionDidFinish()
{
	arrayMakeObjectsPerformSelector(m_pChildren, onEnterTransitionDidFinish, CCNode*);
}

void CCNode::onExitTransitionDidStart()
{
	arrayMakeObjectsPerformSelector(m_pChildren, onExitTransitionDidStart, CCNode*);
}

void CCNode::onExit()
{
	m_bRunning = false;
	arrayMakeObjectsPerformSelector(m_pChildren, onExit, CCNode*);
}


 void CCNode::draw()
 {
     //CCAssert(0);
     // override me
     // Only use- this function to draw your stuff.
     // DON'T draw your stuff outside this method
 }

void CCNode::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!m_bVisible)
    {
        return;
    }
    CCNode* pNode = NULL;
    unsigned int i = 0;

    if(m_pChildren && m_pChildren->count() > 0)
    {
        sortAllChildren();
        // draw children zOrder < 0
        ccArray *arrayData = m_pChildren->data;
        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];

            if ( pNode && pNode->m_nZOrder < 0 ) 
            {
                pNode->visit();
            }
            else
            {
                break;
            }
        }
        // self draw
        this->draw();

        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];
            if (pNode)
            {
                pNode->visit();
            }
        }        
    }
    else
    {
        this->draw();
    }

}


