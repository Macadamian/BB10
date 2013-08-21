#include "CirclePhysicsNode.h"
#include  "CocosEventHandler.h"

CirclePhysicsNode::CirclePhysicsNode(const char* f, CCPoint p, AroundMeLayer* layer)
        : PhysicsNode(layer) {
    m_image = QString(f);
    float radius = 3;

    b2CircleShape shape;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.5;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = CHEERIOS;

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    shape.m_radius = radius;
    bd.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);
    bd.userData = this;
    b2Body *body = m_world->CreateBody(&bd);
    body->CreateFixture(&fixtureDef);

    setContentSize(CCSize(WORLD_TO_SCREEN(radius*2), WORLD_TO_SCREEN(radius*2)));
    setScale(WORLD_TO_SCREEN(radius) / 99);
    setPosition(ccp(p.x, p.y));
    setB2Body(body);

    m_sprite = CCSprite::create(f);

    addChild(m_sprite);
}

CirclePhysicsNode::~CirclePhysicsNode(void) {
}

void CirclePhysicsNode::tintObj() {
    tintSpriteWithColor(m_sprite);
}

void CirclePhysicsNode::clearTint() {
    tintSpriteWithColor(m_sprite, true);
}

void CirclePhysicsNode::triggerCascadesControl()
{
    CocosEventHandler::getInstance()->onFriendStaged(m_image);
}
