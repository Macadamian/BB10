#ifndef _Physics_Node_H_
#define _Physics_Node_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <QStringList>

USING_NS_CC;

#define PTM_RATIO 32.0f
#define SCREEN_TO_WORLD(n) ((n) / PTM_RATIO)
#define WORLD_TO_SCREEN(n) ((n) * PTM_RATIO)
#define B2_ANGLE_TO_COCOS_ROTATION(n) (-1 * CC_RADIANS_TO_DEGREES(n))
#define COCOS_ROTATION_TO_B2_ANGLE(n) (CC_DEGREES_TO_RADIANS(-1 * n))

typedef enum tagPhysicsNodeState {
    kPhysicsNodeStateGrabbed, kPhysicsNodeStateUngrabbed
} PhysicsNodeState;

enum _entityCategory {
    BOUNDARY = 0x0001, CHEERIOS = 0x0002, TWEET_BOX = 0x0004, STAGE_WALL = 0x0008
};

class b2Body;
class b2World;
class AroundMeLayer;

class PhysicsNode: public CCNode, public CCTargetedTouchDelegate {
    b2Body *m_pB2Body;
    b2Vec2 m_mouseWorld;
    b2MouseJoint* m_mouseJoint;
    AroundMeLayer* m_parentLayer;
    bool m_touchDownOnStage;
    QStringList m_images;
    CCNode* m_orbitingObjs;

protected:
    PhysicsNodeState m_state;
    b2World* m_world;
    struct timespec m_time_struct;
    long m_touchDownTime;
    QString m_image;

public:
    enum {
       GREEN, BLUE, RED, CLEAR
    };
    PhysicsNode(AroundMeLayer* layer);
    virtual ~PhysicsNode(void);

    virtual CCRect rect();
    virtual void onEnter();
    virtual void onExit();
    bool containsTouchLocation(CCTouch* touch);
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();
    virtual void touchBeganActions(CCPoint touchPoint);
    virtual void touchMovedActions(CCPoint touchPoint);
    virtual void touchEndedActions(CCPoint touchPoint);

    b2Body* getB2Body() const;
    void setB2Body(b2Body *pBody);
    static b2Body* getEmptyBody(b2World* w);
    void closeStageExits();
    void openStageExits();
    virtual void addOrbitingObjs(QStringList images);
    virtual void tintSpriteWithColor(CCSprite* s, bool clear = false);
    virtual void tintObj() = 0;
    virtual void clearTint() = 0;
    virtual void triggerCascadesControl() = 0;
    QString getImage();
};

class QueryCallback: public b2QueryCallback {
public:
    QueryCallback(const b2Vec2& point) {
        m_point = point;
        m_fixture = NULL;
    }

    bool ReportFixture(b2Fixture* fixture) {
        b2Body* body = fixture->GetBody();
        if (body->GetType() == b2_dynamicBody) {
            bool inside = fixture->TestPoint(m_point);
            if (inside) {
                m_fixture = fixture;

                // We are done, terminate the query.
                return false;
            }
        }

        // Continue the query.
        return true;
    }

    b2Vec2 m_point;
    b2Fixture* m_fixture;
};

#endif
