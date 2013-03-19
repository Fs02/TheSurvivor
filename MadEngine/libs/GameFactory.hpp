#ifndef ENTITYFACTORY_H_INCLUDED
#define ENTITYFACTORY_H_INCLUDED

#include "../stdafx.hpp"
#include "SpriteFactory.hpp"
#include "../../Entity/Vehicle.hpp"
#include "../../Entity/Character.hpp"
#include "../../Entity/AICharacter.hpp"
#include "AniSprite.hpp"
#include "Level.hpp"
#include "../../Level/Level1.hpp"

class GameFactory
{
private:
    b2World* m_World;
    sf::RenderWindow* m_Window;

    std::vector<Vehicle*> m_VehicleList;
    std::vector<AICharacter*> m_AICharacter;
    Character* Player;

    SpriteFactory m_SpriteFactory;

    Level* currentLevel;

public:
    GameFactory(b2World* World, sf::RenderWindow* Window);
    ~GameFactory();

    void Update();
    void Draw();

    Character* getCharacter();
    sf::Vector2f getPlayerPosition();
    float getPlayerRotation();

};

#endif // ENTITYFACTORY_H_INCLUDED
