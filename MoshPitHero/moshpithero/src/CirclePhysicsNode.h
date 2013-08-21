#ifndef _Circle_Physics_Node_H_
#define _Circle_Physics_Node_H_

#include "PhysicsNode.h"

class CirclePhysicsNode: public PhysicsNode {
    CCSprite* m_sprite;
public:
    CirclePhysicsNode(const char* f, CCPoint p, AroundMeLayer* layer);
    virtual ~CirclePhysicsNode(void);
    void tintObj();
    void clearTint();
    void triggerCascadesControl();
};
#endif
