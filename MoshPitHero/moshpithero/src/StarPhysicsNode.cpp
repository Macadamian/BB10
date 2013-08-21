#include "StarPhysicsNode.h"
#include  "CocosEventHandler.h"

StarPhysicsNode::StarPhysicsNode(const char* f, CCPoint p, AroundMeLayer* layer)
        : PhysicsNode(layer) {
    m_image = QString(f);
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);
    bd.userData = this;
    b2Body *body = m_world->CreateBody(&bd);
    b2Vec2 vertices[3];

    {
        b2PolygonShape triangle;
        vertices[0] = b2Vec2(-3.0f, 0.78f);
        vertices[1] = b2Vec2(-1.98f, -0.84f);
        vertices[2] = b2Vec2(-1.2f, 1.56f);
        triangle.Set(vertices, 3);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &triangle;
        fixtureDef.density = 1.0f;
        fixtureDef.restitution = 0.5;
        fixtureDef.friction = 0.3f;
        fixtureDef.filter.categoryBits = CHEERIOS;
        body->CreateFixture(&fixtureDef);
    }
    {
        b2PolygonShape triangle;
        vertices[0] = b2Vec2(-1.2f, 1.56f);
        vertices[1] = b2Vec2(1.2f, 1.56f);
        vertices[2] = b2Vec2(0.0f, 3.0f);
        triangle.Set(vertices, 3);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &triangle;
        fixtureDef.density = 1.0f;
        fixtureDef.restitution = 0.5;
        fixtureDef.friction = 0.3f;
        fixtureDef.filter.categoryBits = CHEERIOS;
        body->CreateFixture(&fixtureDef);
    }
    {
        b2PolygonShape triangle;
        vertices[0] = b2Vec2(1.2f, 1.56f);
        vertices[1] = b2Vec2(1.98f, -0.84f);
        vertices[2] = b2Vec2(3.0f, 0.78f);
        triangle.Set(vertices, 3);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &triangle;
        fixtureDef.density = 1.0f;
        fixtureDef.restitution = 0.5;
        fixtureDef.friction = 0.3f;
        fixtureDef.filter.categoryBits = CHEERIOS;
        body->CreateFixture(&fixtureDef);
    }
    {
        b2PolygonShape triangle;
        vertices[0] = b2Vec2(1.98f, -0.84f);
        vertices[1] = b2Vec2(0.0f, -2.22f);
        vertices[2] = b2Vec2(1.8f, -3.0f);
        triangle.Set(vertices, 3);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &triangle;
        fixtureDef.density = 1.0f;
        fixtureDef.restitution = 0.5;
        fixtureDef.friction = 0.3f;
        fixtureDef.filter.categoryBits = CHEERIOS;
        body->CreateFixture(&fixtureDef);
    }
    {
        b2PolygonShape triangle;
        vertices[0] = b2Vec2(0.0f, -2.22f);
        vertices[1] = b2Vec2(-1.98f, -0.84f);
        vertices[2] = b2Vec2(-1.8f, -3.0f);
        triangle.Set(vertices, 3);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &triangle;
        fixtureDef.density = 1.0f;
        fixtureDef.restitution = 0.5;
        fixtureDef.friction = 0.3f;
        fixtureDef.filter.categoryBits = CHEERIOS;
        body->CreateFixture(&fixtureDef);
    }
    {
        b2Vec2 vertices[5];
        b2PolygonShape pentagon;
        vertices[0] = b2Vec2(-1.98f, -0.84f);
        vertices[1] = b2Vec2(0.0f, -2.22f);
        vertices[2] = b2Vec2(1.98f, -0.84f);
        vertices[3] = b2Vec2(1.2f, 1.56f);
        vertices[4] = b2Vec2(-1.2f, 1.56f);
        pentagon.Set(vertices, 5);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &pentagon;
        fixtureDef.density = 1.0f;
        fixtureDef.restitution = 0.5;
        fixtureDef.friction = 0.3f;
        fixtureDef.filter.categoryBits = CHEERIOS;
        body->CreateFixture(&fixtureDef);
    }

    setContentSize(CCSize(WORLD_TO_SCREEN(3*2), WORLD_TO_SCREEN(3*2)));
    setScale(WORLD_TO_SCREEN(3) / 100);
    setPosition(ccp(p.x, p.y));
    setB2Body(body);

    m_sprite = CCSprite::create(f);
    addChild(m_sprite);
}

StarPhysicsNode::~StarPhysicsNode(void) {
}

void StarPhysicsNode::tintObj() {
    tintSpriteWithColor(m_sprite);
}

void StarPhysicsNode::clearTint() {
    tintSpriteWithColor(m_sprite, true);
}

void StarPhysicsNode::triggerCascadesControl()
{
    CocosEventHandler::getInstance()->onStarStaged(m_image);
}
