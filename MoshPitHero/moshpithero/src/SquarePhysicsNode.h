#ifndef _Square_Physics_Node_H_
#define _Square_Physics_Node_H_

#include "PhysicsNode.h"

class SquarePhysicsNode: public PhysicsNode {
    CCSprite* m_sprite;
public:
    SquarePhysicsNode(const char* f, CCPoint p, AroundMeLayer* layer);
    virtual ~SquarePhysicsNode(void);
    void tintObj();
    void clearTint();
    void triggerCascadesControl();
};
#endif
