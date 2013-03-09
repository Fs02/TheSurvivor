#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include "../stdafx.hpp"
#include "SpriteFactory.hpp"
#include "StaticObject.hpp"

class Level
{
private:
    std::vector<sf::Sprite*> m_terrainSprite;
    std::vector<Object*> m_ObjectList;

    b2World* m_World;
    SpriteFactory* m_SpriteFactory;

    sf::RenderWindow* m_Window;

public:
    std::string name;

//    Level();
 //   ~Level();

    void loadLevel(const std::string& xml_map);

    void setRenderWindow(sf::RenderWindow* Window);
    void setPhysicWorld(b2World* World);
    void setSpriteFactory(SpriteFactory* spriteFactory);

//    void setLevelSprite(sf::Sprite* sprite);

    void AddObject(StaticObject* newStaticObject);
    void DrawLevel();

//    virtual void Create();
};

#endif // LEVEL_HPP_INCLUDED
