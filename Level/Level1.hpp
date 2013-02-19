#ifndef LEVEL1_HPP_INCLUDED
#define LEVEL1_HPP_INCLUDED

#include "../MadEngine/stdafx.hpp"
#include "../MadEngine/libs/Level.hpp"

class Level1 :
    public Level
{
    void Create()
    {
        m_SpriteFactory->newSprite("LEVEL1", "Level\\Asphalt.png");
        Level::setLevelSprite(m_SpriteFactory->getSprite("LEVEL1"));

        StaticObject* newObj    = new StaticObject(m_World);
        newObj->createSquareFixture(2.f, 2.f, b2Vec2(5,5), 0);
        Level::AddObject(newObj);
    }
};

#endif // LEVEL1_HPP_INCLUDED

