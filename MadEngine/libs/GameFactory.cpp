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
}

GameFactory::~GameFactory()
{
    for (unsigned int i = 0; i < m_VehicleList.size(); i++)
        delete m_VehicleList[i];
    m_VehicleList.clear();
}

void GameFactory::Update()
{
    currentLevel->DrawLevel();

    Player->updateFriction();
    Player->controller();

    for (unsigned int i = 0;i < m_VehicleList.size(); i++)
    {
        m_VehicleList[i]->update();
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
