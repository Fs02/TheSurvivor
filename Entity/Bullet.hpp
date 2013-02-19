#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "../MadEngine/stdafx.hpp"
#include "../MadEngine/libs/SpriteFactory.hpp"

class Bullet
{
private:
    b2Body *Body;
public:
    Bullet(b2World* World, b2Vec2 pos, b2Vec2 normal);
    ~Bullet();
};

#endif // BULLET_HPP_INCLUDED
