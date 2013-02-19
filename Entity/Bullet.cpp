#include "Bullet.hpp"

Bullet::Bullet(b2World* World, b2Vec2 pos, b2Vec2 normal)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.position = pos;
    Body = World->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = 0.05;
    b2FixtureDef fixDef;
    fixDef.density = 0.1;
    fixDef.shape = &shape;
    //fixDef.filter.categoryBits = BULLETOBJ;
    Body->CreateFixture(&fixDef);

    Body->ApplyLinearImpulse(Body->GetWorldVector(normal), Body->GetWorldCenter());
    Body->SetUserData(this);

}

Bullet::~Bullet()
{
    Body->GetWorld()->DestroyBody(Body);
}
