#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include "../stdafx.hpp"
#include "SpriteFactory.hpp"
#include "StaticObject.hpp"

class Level
{
private:
    sf::Sprite* m_LevelSprite;
    std::vector<StaticObject*> m_ObjectList;

    sf::RenderWindow* m_Window;

public:
    b2World* m_World;
    SpriteFactory* m_SpriteFactory;


    Level();
    ~Level();

    void setRenderWindow(sf::RenderWindow* Window);
    void setPhysicWorld(b2World* World);
    void setSpriteFactory(SpriteFactory* spriteFactory);

    void setLevelSprite(sf::Sprite* sprite);

    void AddObject(StaticObject* newStaticObject);
    void DrawLevel();

    virtual void Create() = 0;
};

#endif // LEVEL_HPP_INCLUDED
