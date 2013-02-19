#include "EntityFactory.hpp"

EntityFactory::EntityFactory(b2World* World, sf::RenderWindow* Window)
{
    m_World     = World;
    m_Window    = Window;

    Vehicle* newVehicle = new Vehicle(World, m_SpriteFactory.getSprite("DEATHCAR"), m_SpriteFactory.getSprite("TIRE"));
    m_VehicleList.push_back(newVehicle);

    newVehicle          = new Vehicle(World, m_SpriteFactory.getSprite("HUMMER"), m_SpriteFactory.getSprite("TIRE"), b2Vec2(1.f, 2.3f));
    m_VehicleList.push_back(newVehicle);

    Player              = new Character(World, Window, m_SpriteFactory.getSprite("EXAMPLECHAR"));

    currentLevel        = new Level1;
    currentLevel->setPhysicWorld(m_World);
    currentLevel->setRenderWindow(m_Window);
    currentLevel->setSpriteFactory(&m_SpriteFactory);
    currentLevel->Create();
}

EntityFactory::~EntityFactory()
{
    for (unsigned int i = 0; i < m_VehicleList.size(); i++)
        delete m_VehicleList[i];
    m_VehicleList.clear();
}

void EntityFactory::Update()
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

Character* EntityFactory::getCharacter()
{
    return Player;
}

sf::Vector2f EntityFactory::getPlayerPosition()
{
    return Player->getPosition();
}

float EntityFactory::getPlayerRotation()
{
    return Player->getRotation();
}
