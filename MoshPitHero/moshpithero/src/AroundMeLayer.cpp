#include "AroundMeLayer.h"
#include "CocosEventHandler.h"
#include "VisibleRect.h"
#include "PhysicsNode.h"
#include "CirclePhysicsNode.h"
#include "SquarePhysicsNode.h"
#include "StarPhysicsNode.h"
#include "TweetPhysicsNode.h"

enum {
    kTagParentNode = 1,
};

AroundMeLayer::AroundMeLayer(int bg)
        : m_world(NULL),
          m_stageWall(NULL) {
    setTouchEnabled(true);
    setAccelerometerEnabled(true);
    // init physics
    this->initPhysics();

    m_bgColor = bg;
    char* s;
    switch (bg) {
        case PhysicsNode::RED:
            s = "app/native/assets/images/Backgrounds/red.png";
            break;
        case PhysicsNode::GREEN:
            s = "app/native/assets/images/Backgrounds/green.png";
            break;
        default:
        case PhysicsNode::BLUE:
            s = "app/native/assets/images/Backgrounds/blue.png";
            break;
    }
    CCSprite* bgSprite = CCSprite::create(s);
    bgSprite->setPosition(ccp(768 / 2, 1138 / 2));
    addChild(bgSprite, -2, 100);

    CCNode *parent = CCNode::create();
    addChild(parent, 0, kTagParentNode);

    srand (time(NULL));

    m_objlist << QString(
            "app/native/assets/images/friends/friend"
                    + (bg == PhysicsNode::BLUE ? QString::number(rand() % 11) : "_Vivek") + ".png");

    addPhysicsNode    (
            new CirclePhysicsNode(
                    m_objlist.last().toStdString().c_str(),
                    CCPoint(50, VisibleRect::top().y - 400), this));

    m_objlist << "app/native/assets/images/info/info_drinks.png";

    addPhysicsNode(
            new SquarePhysicsNode(m_objlist.last().toStdString().c_str(),
                    CCPoint(600, VisibleRect::top().y - 800), this));

    this->scheduleOnce(schedule_selector(AroundMeLayer::addRedStage), 5);
    this->schedule(schedule_selector(AroundMeLayer::addPeeps), 20);

    m_objlist << QString("app/native/assets/images/stars/star" + QString::number(rand() % 9) + ".png");

    addPhysicsNode(
            new StarPhysicsNode(
                    m_objlist.last().toStdString().c_str(),
                    CCPoint(300, VisibleRect::top().y - 400), this));

    for (int i = 0; i < 3; i++) {
        int randNum = rand() % 19;
        addPhysicsNode(new TweetPhysicsNode(CCPoint(300, VisibleRect::top().y), this, randNum));
    }
    scheduleUpdate();
}

AroundMeLayer::~AroundMeLayer() {
   // CC_SAFE_DELETE(m_world);
}

void AroundMeLayer::addRedStage(){
    m_objlist << "app/native/assets/images/stages/stage2_red.png";
    addPhysicsNode(
                new SquarePhysicsNode(m_objlist.last().toStdString().c_str(),
                        CCPoint(600, VisibleRect::top().y - 400), this));
}

void AroundMeLayer::addPeeps(){
    QString s = QString(
                    "app/native/assets/images/friends/friend"
                            + (QString::number(rand() % 11)) + ".png");
    if(m_objlist.contains(s))
        return;
    else
        m_objlist << s;
    addPhysicsNode    (
                new CirclePhysicsNode(
                        m_objlist.last().toStdString().c_str(),
                        CCPoint(100 + rand() % 500, VisibleRect::top().y - 475), this));
}

void AroundMeLayer::initPhysics() {
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    m_world = new b2World(gravity);

    // Do we want to let bodies sleep?
    m_world->SetAllowSleeping(false);

    m_world->SetContinuousPhysics(true);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

    b2EdgeShape groundBox;

    m_t = (VisibleRect::leftTop().y + 200) / PTM_RATIO;
    m_l = VisibleRect::leftTop().x / PTM_RATIO;
    m_b = VisibleRect::rightBottom().y / PTM_RATIO;
    m_r = VisibleRect::rightBottom().x / PTM_RATIO;

    m_stageHeight = VisibleRect::leftTop().y - 400;

    // bottom
    groundBox.Set(b2Vec2(m_l, m_b), b2Vec2(m_r, m_b));
    groundBody->CreateFixture(&groundBox, 0);

    // top
    groundBox.Set(b2Vec2(m_l, m_t), b2Vec2(m_r, m_t));
    groundBody->CreateFixture(&groundBox, 0);

    // left
    groundBox.Set(b2Vec2(m_l, m_b), b2Vec2(m_l, m_stageHeight / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);

    //StageLeft
    {
        groundBox.Set(b2Vec2(m_l, m_stageHeight / PTM_RATIO), b2Vec2(m_l, m_t));
        b2Fixture* f = groundBody->CreateFixture(&groundBox, 0);
        b2Filter filter = f->GetFilterData();
        filter.groupIndex = -1;
        f->SetFilterData(filter);
    }

    // right
    groundBox.Set(b2Vec2(m_r, m_b), b2Vec2(m_r, m_stageHeight / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);

    //StageRight
    {
        groundBox.Set(b2Vec2(m_r, m_stageHeight / PTM_RATIO), b2Vec2(m_r, m_t));
        b2Fixture* f = groundBody->CreateFixture(&groundBox, 0);
        b2Filter filter = f->GetFilterData();
        filter.groupIndex = -1;
        f->SetFilterData(filter);
    }

    {
        b2EdgeShape stage;
        stage.Set(b2Vec2(VisibleRect::leftTop().x / PTM_RATIO, m_stageHeight / PTM_RATIO),
                b2Vec2(VisibleRect::rightTop().x / PTM_RATIO, m_stageHeight / PTM_RATIO));
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &stage;
        fixtureDef.density = 1.0f;
        fixtureDef.restitution = 0.5;
        fixtureDef.friction = 0.3f;
        fixtureDef.filter.categoryBits = STAGE_WALL;
        fixtureDef.filter.maskBits = BOUNDARY | TWEET_BOX;
        b2BodyDef bd;
        m_stageWall = groundBody->CreateFixture(&fixtureDef);
    }
}

void AroundMeLayer::createResetButton() {
    CCMenuItemImage *reset = CCMenuItemImage::create("app/native/assets/images/r1.png",
            "app/native/assets/images/r2.png", this, menu_selector(AroundMeLayer::reset));

    CCMenu *menu = CCMenu::create(reset, NULL);

    menu->setPosition(ccp(VisibleRect::bottom().x, VisibleRect::bottom().y + 30));
    this->addChild(menu, -1);
}

void AroundMeLayer::reset(CCObject* sender) {
    CCScene* s = new CCScene();
    CCLayer* pLayer = new AroundMeLayer(PhysicsNode::RED);
    s->addChild(pLayer);

    CCScene* pScene = CCTransitionSlideInR::create(1, s);
    s->release();
    pLayer->release();
    if (pScene) {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void AroundMeLayer::draw() {
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    CCLayer::draw();
}

void AroundMeLayer::addPhysicsNode(PhysicsNode* p) {
    CCNode *parent = this->getChildByTag(kTagParentNode);
    parent->addChild(p);
}

void AroundMeLayer::removePhysicsNode(PhysicsNode* p) {
    m_objlist.removeOne(p->getImage());
    CCNode *parent = this->getChildByTag(kTagParentNode);
    parent->removeChild(p);
}

void AroundMeLayer::update(float dt) {
    int velocityIterations = 8;
    int positionIterations = 3;

    m_world->Step(dt, velocityIterations, positionIterations);

    for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
        if (b->GetUserData() != NULL) {
            PhysicsNode* myActor = (PhysicsNode*) b->GetUserData();
            if (b->GetPosition().x < m_l - 100 / PTM_RATIO || b->GetPosition().x > m_r + 100 / PTM_RATIO)
            {
                CocosEventHandler::getInstance()->resetControls();
                removePhysicsNode(myActor);
            }
            else {
                myActor->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
                myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
            }
        }
    }
}

void AroundMeLayer::ccTouchesBegan(CCSet* touches, CCEvent* event) {
    CCTouch* touch = (CCTouch*) (*touches->begin());
    m_touchDownPoint = touch->getLocation();
}

void AroundMeLayer::ccTouchesMoved(CCSet* touches, CCEvent* event) {
    CCTouch* touch = (CCTouch*) (*touches->begin());
    CCPoint touchPoint = touch->getLocation();
    if(m_bgColor > PhysicsNode::GREEN && touchPoint.x > m_touchDownPoint.x + 200)
    {
        CCScene* s = new CCScene();
        CCLayer* pLayer = new AroundMeLayer(m_bgColor-1);
        s->addChild(pLayer);

        CCScene* pScene = CCTransitionSlideInL::create(1, s);
        s->release();
        pLayer->release();
        if (pScene) {
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
    }
    else if(m_bgColor < PhysicsNode::RED && touchPoint.x < m_touchDownPoint.x - 200)
    {
        CCScene* s = new CCScene();
        CCLayer* pLayer = new AroundMeLayer(m_bgColor+1);
        s->addChild(pLayer);

        CCScene* pScene = CCTransitionSlideInR::create(1, s);
        s->release();
        pLayer->release();
        if (pScene) {
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
    }
}

void AroundMeLayer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
    CCSetIterator it;
    CCTouch* touch;

    for (it = touches->begin(); it != touches->end(); it++) {
        touch = (CCTouch*) (*it);

        if (!touch)
            break;

        CCPoint location = touch->getLocation();
      //  addPhysicsNode(new CirclePhysicsNode("app/native/assets/images/friends/friend0.png", location, this));
    }
}

void AroundMeLayer::didAccelerate(CCAcceleration* acceleration) {
    static float prevX = 0, prevY = 0;

#define kFilterFactor 1.0f
    float accelX = (float) acceleration->x * kFilterFactor + (1 - kFilterFactor) * prevX;
    float accelY = (float) acceleration->y * kFilterFactor + (1 - kFilterFactor) * prevY;

    prevX = accelX;
    prevY = accelY;

    b2Vec2 gravity(accelX, accelY);

    m_world->SetGravity(gravity);
}

void AroundMeLayer::activateStageWall(bool v) {
    b2Filter filter = m_stageWall->GetFilterData();
    if (v) {
        if (filter.maskBits != 0xFFFF) {
            filter.maskBits = 0xFFFF;
            m_stageWall->SetFilterData(filter);
        }
    }
    else {
        if (filter.maskBits == 0xFFFF) {
            filter.maskBits = BOUNDARY | TWEET_BOX;
            m_stageWall->SetFilterData(filter);
        }
    }
}

b2World* AroundMeLayer::getWorld() {
    return m_world;
}
float AroundMeLayer::getStageHeight() {
    return m_stageHeight;
}
int AroundMeLayer::getBGColor() {
    return m_bgColor;
}
