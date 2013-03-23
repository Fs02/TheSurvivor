#include "GameFactory.hpp"

GameFactory::GameFactory(b2World* World, sf::RenderWindow* Window)
{
    std::cout<<"Please Wait while loading !"<<std::endl;

    m_World     = World;
    m_Window    = Window;

    m_SpriteFactory.loadSprite("data//TheHospital.MadTexturePack");
    m_SpriteFactory.newSprite("SOLDIER","Character//soldiersheet.png");

    currentLevel        = new Level;
    currentLevel->setPhysicWorld(m_World);
currentLevel->setRenderWindow(m_Window);
    currentLevel->setSpriteFactory(&m_SpriteFactory);
    currentLevel->loadLevel("data//TheHospital.MadMap");

    Player              = new Character(World, Window, m_SpriteFactory.getSprite("SOLDIER"),128,128);
}

GameFactory::~GameFactory()
{
    for (unsigned int i = 0; i<m_AICharacter.size(); i++)
        delete m_AICharacter[i];
        m_AICharacter.clear();

    for (unsigned int i = 0; i < m_VehicleList.size(); i++)
        delete m_VehicleList[i];
    m_VehicleList.clear();
}

void GameFactory::Update()
{
    Player->updateAll();

    for (unsigned int i = 0;i < m_AICharacter.size(); i++)
    {
        m_AICharacter[i]->updateAll();
    }

    for (unsigned int i = 0;i < m_VehicleList.size(); i++)
    {
        m_VehicleList[i]->update();
    }
}

void GameFactory::Draw()
{
    currentLevel->DrawLevel();

    Player->draw();

    for (unsigned int i = 0;i < m_AICharacter.size(); i++)
    {
        m_AICharacter[i]->draw();
    }

    for (unsigned int i = 0;i < m_VehicleList.size(); i++)
    {
        m_VehicleList[i]->render(m_Window);
    }
}

Character* GameFactory::getCharacter()
{
    return Player;
}

sf::Vector2f GameFactory::getPlayerPosition()
{
    return Player->getPosition();
}

float GameFactory::getPlayerRotation()
{
    return Player->getRotation();
}
