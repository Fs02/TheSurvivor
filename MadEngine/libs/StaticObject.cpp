#include "StaticObject.hpp"

StaticObject::StaticObject(b2World* World)
{
    b2BodyDef def;
    def.type    = b2_kinematicBody;
    m_Body      = World->CreateBody(&def);
}

StaticObject::~StaticObject()
{
    m_Body->GetWorld()->DestroyBody(m_Body);
}

void StaticObject::createSquareFixture(float width, float height, b2Vec2 center, int angle)
{
    b2PolygonShape shape;
    shape.SetAsBox(width, height, center, angle);

    m_Body->CreateFixture(&shape, 1.f);
}

void StaticObject::createCircleFixture(float radius, b2Vec2 center)
{
    b2CircleShape shape;
    shape.m_radius  = radius;
    shape.m_p       = center;

    m_Body->CreateFixture(&shape, 1.f);
}

void StaticObject::setSprite(sf::Sprite* sprite)
{
    m_Sprite    = sprite;
}

void StaticObject::setPosition(float x, float y)
{
    m_Body->SetTransform(b2Vec2(x, y), 0);
}

void StaticObject::setRotation(float angle)
{
    m_Body->SetTransform(b2Vec2_zero, angle);
}

void StaticObject::Draw(sf::RenderWindow* Window)
{
    //m_Sprite->setPosition(m_Body->GetPosition().x * RATIO, m_Body->GetPosition().y * RATIO);
    //m_Sprite->setRotation(m_Body->GetAngle() * RADTODEG);
    //Window->draw(*m_Sprite);
}
