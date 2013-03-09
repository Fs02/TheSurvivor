#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include "../stdafx.hpp"
class Object
{
public:
    virtual b2Vec2* getPosition() = 0;
    virtual float getRotation() = 0;
    virtual void update() = 0;
    virtual void Draw(sf::RenderWindow* Window) = 0;
};

#endif // OBJECT_HPP_INCLUDED
