#include "Level.hpp"

Level::Level()
{}

Level::~Level()
{
    for (unsigned int i = 0; i < m_ObjectList.size(); i++)
        delete m_ObjectList[i];

    m_ObjectList.clear();
}

void Level::setRenderWindow(sf::RenderWindow* Window)
{
    m_Window    = Window;
}

void Level::setPhysicWorld(b2World* World)
{
    m_World     = World;
}

void Level::setSpriteFactory(SpriteFactory* spriteFactory)
{
    m_SpriteFactory = spriteFactory;
}

void Level::setLevelSprite(sf::Sprite* sprite)
{
    m_LevelSprite   = sprite;
}

void Level::AddObject(StaticObject* newStaticObject)
{
    m_ObjectList.push_back(newStaticObject);
}

void Level::DrawLevel()
{
    m_Window->draw(*m_LevelSprite);

    for (unsigned int i = 0; i < m_ObjectList.size(); i++)
        m_ObjectList[i]->Draw(m_Window);
}
