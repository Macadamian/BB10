#include "CocosEventHandler.h"
#include "PhysicsNode.h"
#include "VisibleRect.h"
#include "AroundMeLayer.h"
#include "StarPhysicsNode.h"
#include <QSet>

namespace{
// convert the timespec into milliseconds
long time2millis(struct timespec *times)
{
    return times->tv_sec*1000 + times->tv_nsec/1000000;
}
}

PhysicsNode::PhysicsNode(AroundMeLayer* layer)
        : m_pB2Body(NULL),
          m_mouseJoint(NULL),
          m_world(layer->getWorld()),
          m_parentLayer(layer) {
    m_state = kPhysicsNodeStateUngrabbed;
    scheduleOnce(schedule_selector(PhysicsNode::tintObj), 120);
    this->autorelease();
}

PhysicsNode::~PhysicsNode(void) {
    m_world->DestroyBody(m_pB2Body);
}

void PhysicsNode::onEnter() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCNode::onEnter();
}

void PhysicsNode::onExit() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

CCRect PhysicsNode::rect() {
    CCSize s = getContentSize();
    return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool PhysicsNode::containsTouchLocation(CCTouch* touch) {
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

b2Body* PhysicsNode::getEmptyBody(b2World* w) {
    static b2Body* s_groundBody = NULL;
    static b2World* s_world = w;
    if (!s_groundBody || s_world != w) {
        s_world = w;
        b2BodyDef bodyDef;
        s_groundBody = s_world->CreateBody(&bodyDef);
    }
    return s_groundBody;
}

void PhysicsNode::touchBeganActions(CCPoint touchPoint) {
    clock_gettime(CLOCK_REALTIME, &m_time_struct);
    m_touchDownTime = time2millis(&m_time_struct);
    m_touchDownOnStage = false;
    m_parentLayer->activateStageWall(false);
    if (touchPoint.y > m_parentLayer->getStageHeight()) {
        m_touchDownOnStage = true;
    }
}

void PhysicsNode::touchMovedActions(CCPoint touchPoint) {

    if(m_images.isEmpty())
    {
        clock_gettime(CLOCK_REALTIME, &m_time_struct);
        long curTime = time2millis(&m_time_struct);
        if(curTime - m_touchDownTime > 2000)
        {
            QStringList sl  = QStringList() << "app/native/assets/images/stars/star0.png";
            int s = rand() % 3 + 1;
            for(int i=1; i < s; i++)
            {
                sl << "app/native/assets/images/stars/star"+QString::number(rand()%8+1)+".png";
            }
            sl = sl.toSet().toList();
            addOrbitingObjs(sl);
        }
    }

    float stagePos = m_parentLayer->getStageHeight() / PTM_RATIO;
    if (m_touchDownOnStage && m_pB2Body->GetWorldCenter().y > stagePos) {
        openStageExits();
    }
}

void PhysicsNode::touchEndedActions(CCPoint touchPoint) {
    if (m_pB2Body->GetWorldCenter().y > m_parentLayer->getStageHeight() / PTM_RATIO) {
        m_parentLayer->activateStageWall(true);
        removeChild(m_orbitingObjs);
        for (int i = 0; i < m_images.size(); i++) {
            m_parentLayer->addPhysicsNode(
                    new StarPhysicsNode(m_images[i].toStdString().c_str(), CCPoint(i * 150 + 100, VisibleRect::top().y - 550), m_parentLayer));
        }
        m_images.clear();
        if(m_parentLayer->getBGColor() == PhysicsNode::RED)
        {
            CCSprite* coupon = CCSprite::create("app/native/assets/images/coupon.png");
            m_parentLayer->addChild(coupon,10);
            coupon->setPosition(ccp(400, VisibleRect::top().y - 600));
            CCFiniteTimeAction* wave = CCShaky3D::create(1,CCSizeMake(15,10), 5, false);
            CCFiniteTimeAction* shrink = CCScaleTo::create(1,0.1f);
            CCFiniteTimeAction* fadeOut = CCFadeOut::create(0.0);
            coupon->runAction(CCSequence::create(CCDelayTime::create(10),shrink,NULL));
            coupon->runAction(CCSequence::create(CCDelayTime::create(10),wave,fadeOut,NULL));
        }
        else
            triggerCascadesControl();

    }
    if (m_touchDownOnStage)
        this->scheduleOnce(schedule_selector(PhysicsNode::closeStageExits), 0.5);
    if(!m_images.isEmpty())
    {
        m_images.clear();
        removeChild(m_orbitingObjs);
    }
}

void PhysicsNode::openStageExits() {
    for (b2Fixture* f = m_pB2Body->GetFixtureList(); f; f = f->GetNext()) {
        b2Filter filter = f->GetFilterData();
        if (filter.groupIndex == -1)
            return;
        filter.groupIndex = -1;
        f->SetFilterData(filter);
    }
}

void PhysicsNode::closeStageExits() {
    for (b2Fixture* f = m_pB2Body->GetFixtureList(); f; f = f->GetNext()) {
        b2Filter filter = f->GetFilterData();
        if (filter.groupIndex != -1)
            return;
        filter.groupIndex = 0;
        f->SetFilterData(filter);
    }
}

bool PhysicsNode::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    if (m_state != kPhysicsNodeStateUngrabbed)
        return false;
    if (!containsTouchLocation(touch))
        return false;

    CCPoint touchPoint = touch->getLocation();

    touchBeganActions(touchPoint);

    m_mouseWorld = b2Vec2(touchPoint.x / PTM_RATIO, touchPoint.y / PTM_RATIO);

    if (m_mouseJoint != NULL)
        return false;

    // Make a small box.
    b2AABB aabb;
    b2Vec2 d;
    d.Set(0.001f, 0.001f);
    aabb.lowerBound = m_mouseWorld - d;
    aabb.upperBound = m_mouseWorld + d;

    // Query the world for overlapping shapes.
    QueryCallback callback(m_mouseWorld);
    m_world->QueryAABB(&callback, aabb);

    if (callback.m_fixture) {
        b2Body* body = callback.m_fixture->GetBody();
        b2MouseJointDef md;
        md.bodyA = getEmptyBody(m_world);
        md.bodyB = body;
        md.target = m_mouseWorld;
        md.maxForce = 1000.0f * body->GetMass();
        m_mouseJoint = (b2MouseJoint*) m_world->CreateJoint(&md);
        body->SetAwake(true);
        m_state = kPhysicsNodeStateGrabbed;
        return true;
    }

    return false;
}

void PhysicsNode::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    CCAssert(m_state == kPhysicsNodeStateGrabbed, "PhysicsNode - Unexpected state!");

    CCPoint touchPoint = touch->getLocation();

    touchMovedActions(touchPoint);

    m_mouseWorld = b2Vec2(touchPoint.x / PTM_RATIO, touchPoint.y / PTM_RATIO);
    if (m_mouseJoint) {
        m_mouseJoint->SetTarget(m_mouseWorld);
    }
}

CCObject* PhysicsNode::copyWithZone(CCZone *pZone) {
    this->retain();
    return this;
}

void PhysicsNode::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    CCAssert(m_state == kPhysicsNodeStateGrabbed, "PhysicsNode - Unexpected state!");

    CCPoint touchPoint = touch->getLocation();

    if (m_mouseJoint) {
        touchEndedActions(touchPoint);
        m_world->DestroyJoint(m_mouseJoint);
        m_mouseJoint = NULL;
    }
    m_state = kPhysicsNodeStateUngrabbed;
}

void PhysicsNode::touchDelegateRetain() {
    this->retain();
}

void PhysicsNode::touchDelegateRelease() {
    this->release();
}

b2Body* PhysicsNode::getB2Body() const {
    return m_pB2Body;
}

void PhysicsNode::setB2Body(b2Body *pBody) {
    m_pB2Body = pBody;
}
void PhysicsNode::addOrbitingObjs(QStringList images) {
    CCActionInterval* rot = CCRotateBy::create(10, 360);
    CCAction* seq = CCRepeatForever::create(rot);

    m_images = images;
    int orbitRadius = 200;

    CCNode* parentNode = CCNode::create();
    parentNode->setPosition(ccp(0, 0));
    parentNode->runAction(seq);

    for (int i = 0; i < images.size(); i++) {
        if (i < 2) {
            if (i % 2 == 0) {
                CCSprite* rotObj = CCSprite::create(images[i].toStdString().c_str());
                parentNode->addChild(rotObj);
                rotObj->setPosition(ccp(parentNode->getContentSize().width + (orbitRadius), 0.0f));
                rotObj->setScale(0.5);
            }
            else {
                CCSprite* rotObj = CCSprite::create(images[i].toStdString().c_str());
                parentNode->addChild(rotObj);
                rotObj->setPosition(ccp(parentNode->getContentSize().width - (orbitRadius), 0.0f));
                rotObj->setScale(0.5);
            }
        }
        else {
            if (i % 2 == 0) {
                CCSprite* rotObj = CCSprite::create(images[i].toStdString().c_str());
                parentNode->addChild(rotObj);
                rotObj->setPosition(ccp(0.0f, parentNode->getContentSize().height + (orbitRadius)));
                rotObj->setScale(0.5);
            }
            else {
                CCSprite* rotObj = CCSprite::create(images[i].toStdString().c_str());
                parentNode->addChild(rotObj);
                rotObj->setPosition(ccp(0.0f, parentNode->getContentSize().width - (orbitRadius)));
                rotObj->setScale(0.5);
            }
        }
    }

    addChild(parentNode);
    m_orbitingObjs = parentNode;
}

void PhysicsNode::tintSpriteWithColor(CCSprite* s, bool clear) {
    CCActionInterval* tintRed = CCTintBy::create(10, -100, -120, -120);
    CCActionInterval* tintGreen = CCTintBy::create(10, -120, -100, -120);
    CCActionInterval* tintBlue = CCTintBy::create(10, -120, -120, -100);

    CCActionInterval *tint;

    switch (m_parentLayer->getBGColor()) {
        case 0: {
            tint = tintRed;
            break;
        }
        case 1: {
            tint = tintGreen;
            break;
        }
        default:
        case 2: {
            tint = tintBlue;
            break;
        }
    }

    s->runAction(clear ? tint->reverse() : tint);
}

QString PhysicsNode::getImage()
{
    return m_image;
}
