#include "SquarePhysicsNode.h"
#include  "CocosEventHandler.h"

SquarePhysicsNode::SquarePhysicsNode(const char* f, CCPoint p, AroundMeLayer* layer)
        : PhysicsNode(layer) {
    m_image = QString(f);
    float side = 3;

    b2PolygonShape polygon;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.5;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = CHEERIOS;

    polygon.SetAsBox(side, side);

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);
    bd.userData = this;
    b2Body *body = m_world->CreateBody(&bd);
    body->CreateFixture(&fixtureDef);

    setContentSize(CCSize(WORLD_TO_SCREEN(side*2), WORLD_TO_SCREEN(side*2)));
    setScale(WORLD_TO_SCREEN(side) / 100);
    setPosition(ccp(p.x, p.y));
    setB2Body(body);

    m_sprite = CCSprite::create(f);

    addChild(m_sprite);
}

SquarePhysicsNode::~SquarePhysicsNode(void) {
}

void SquarePhysicsNode::tintObj() {
    tintSpriteWithColor(m_sprite);
}

void SquarePhysicsNode::clearTint() {
    tintSpriteWithColor(m_sprite, true);
}

void SquarePhysicsNode::triggerCascadesControl()
{
    CocosEventHandler::getInstance()->onStagePicked(m_image, "Red Stage");
}
