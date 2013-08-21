#ifndef _AROUND_ME_LAYER_H_
#define _AROUND_ME_LAYER_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <QList>
#include <QStringList>

USING_NS_CC;

class PhysicsNode;

class AroundMeLayer: public CCLayer {
    b2World* m_world;
    b2Fixture* m_stageWall;
    float m_stageHeight, m_t, m_l, m_b, m_r;
    int m_bgColor;
    CCPoint m_touchDownPoint;
    QList<PhysicsNode *> m_delList;
    QStringList m_objlist;

public:
    AroundMeLayer(int);
    ~AroundMeLayer();

    void initPhysics();
    void createResetButton();
    void reset(CCObject* sender);
    virtual void draw();

    void addPhysicsNode(PhysicsNode* p);
    void removePhysicsNode(PhysicsNode* p);

    void update(float dt);
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual void didAccelerate(CCAcceleration* acceleration);
    b2World* getWorld();
    float getStageHeight();
    void activateStageWall(bool v);
    int getBGColor();
    void addRedStage();
    void addPeeps();
};
#endif
