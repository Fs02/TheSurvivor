#ifndef STATICOBJECT_HPP_INCLUDED
#define STATICOBJECT_HPP_INCLUDED

#include "../stdafx.hpp"
#include "Object.hpp"

class StaticObject
    : public Object
{
private:
    std::string name;
    sf::Sprite* m_Sprite;
    b2Body* m_Body;

public:
    StaticObject(b2World* World, std::string Name);
    ~StaticObject();

    void createSquareFixture(float width, float height, b2Vec2 center, int angle = 0);
    void createCircleFixture(float radius, b2Vec2 center);

    void setSprite(sf::Sprite* sprite);
    void setPosition(float x, float y);
    void setRotation(float angle);

    b2Vec2* getPosition();
    float getRotation();
    void update();
    void Draw(sf::RenderWindow* Window);
};

#endif // STATICOBJECT_HPP_INCLUDED
