#ifndef ENTITYFACTORY_H_INCLUDED
#define ENTITYFACTORY_H_INCLUDED

#include "../stdafx.hpp"
#include "SpriteFactory.hpp"
#include "../../Entity/Vehicle.hpp"
#include "../../Entity/Character.hpp"
#include "AniSprite.hpp"
#include "Level.hpp"
#include "../../Level/Level1.hpp"

class GameFactory
{
private:
    b2World* m_World;
    sf::RenderWindow* m_Window;

    std::vector<Vehicle*> m_VehicleList;
    Character* Player;

    SpriteFactory m_SpriteFactory;

    Level* currentLevel;

public:
    GameFactory(b2World* World, sf::RenderWindow* Window);
    ~GameFactory();

    void Update();
    Character* getCharacter();
    sf::Vector2f getPlayerPosition();
    float getPlayerRotation();

};

#endif // ENTITYFACTORY_H_INCLUDED
