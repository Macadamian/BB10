#ifndef _Star_Physics_Node_H_
#define _Star_Physics_Node_H_

#include "PhysicsNode.h"

class StarPhysicsNode: public PhysicsNode {
    CCSprite* m_sprite;
public:
    StarPhysicsNode(const char* f, CCPoint p, AroundMeLayer* layer);
    virtual ~StarPhysicsNode(void);
    void tintObj();
    void clearTint();
    void triggerCascadesControl();
};

#endif
