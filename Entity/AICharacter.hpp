#ifndef AICHARACTER_HPP_INCLUDED
#define AICHARACTER_HPP_INCLUDED

#include "Character.hpp"

class AICharacter :
    public Character
{
public:
    AICharacter(b2World* World, sf::RenderWindow* Window, sf::Sprite* Sprite);
    void updateAll();
};

#endif // AICHARACTER_HPP_INCLUDED
