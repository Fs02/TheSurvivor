#include "StaticObject.hpp"

StaticObject::StaticObject(b2World* World, std::string Name)
{
    name = name;
    b2BodyDef def;
    def.type    = b2_kinematicBody;
    m_Body      = World->CreateBody(&def);

    m_Sprite    = NULL;
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

void StaticObject::createNodeFixture(b2Vec2 &vertices, int count)
{
    b2PolygonShape shape;
    shape.Set(&vertices, count);

    m_Body->CreateFixture(&shape, 1.f);
}

void StaticObject::setSprite(sf::Sprite* sprite)
{
    m_Sprite    = sprite;
    m_Sprite->setOrigin(m_Sprite->getLocalBounds().width/2, m_Sprite->getLocalBounds().height/2);
}

void StaticObject::setPosition(float x, float y)
{
    m_Body->SetTransform(b2Vec2(x, y), m_Body->GetAngle());
}

void StaticObject::setRotation(float angle)
{
    m_Body->SetTransform(m_Body->GetPosition(), angle);
}

b2Vec2* StaticObject::getPosition()
{
    //return m_Body->GetPosition();
}

float StaticObject::getRotation()
{
    return m_Body->GetAngle();
}

void StaticObject::update()
{

}

void StaticObject::Draw(sf::RenderWindow* Window)
{
    if (m_Sprite != NULL){
    m_Sprite->setPosition(m_Body->GetPosition().x * RATIO, m_Body->GetPosition().y * RATIO);
    m_Sprite->setRotation(m_Body->GetAngle() * RADTODEG);
    Window->draw(*m_Sprite);
    }
}
