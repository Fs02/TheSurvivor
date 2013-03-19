#include "GameFactory.hpp"

GameFactory::GameFactory(b2World* World, sf::RenderWindow* Window)
{
    std::cout<<"Please Wait while loading !"<<std::endl;

    m_World     = World;
    m_Window    = Window;

    m_SpriteFactory.loadSprite("data//Map1texture.xml");

    currentLevel        = new Level;
    currentLevel->setPhysicWorld(m_World);
    currentLevel->setRenderWindow(m_Window);
    currentLevel->setSpriteFactory(&m_SpriteFactory);
    currentLevel->loadLevel("data//level.xml");

    Vehicle* newVehicle = new Vehicle(World, m_SpriteFactory.getSprite("DEATHCAR"), m_SpriteFactory.getSprite("TIRE"));
    m_VehicleList.push_back(newVehicle);

    newVehicle          = new Vehicle(World, m_SpriteFactory.getSprite("HUMMER"), m_SpriteFactory.getSprite("TIRE"), b2Vec2(1.f, 2.3f));
    m_VehicleList.push_back(newVehicle);

    Player              = new Character(World, Window, m_SpriteFactory.getSprite("EXAMPLECHAR"));
    AICharacter* newAI  = new AICharacter(World, Window, m_SpriteFactory.getSprite("EXAMPLECHAR"));
    //newAI->setTransform(5,-3,0);
    m_AICharacter.push_back(newAI);

    newAI  = new AICharacter(World, Window, m_SpriteFactory.getSprite("EXAMPLECHAR"));
    //newAI->setTransform(3,-2,0);
    m_AICharacter.push_back(newAI);
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
