#include "../MadEngine/stdafx.hpp"
#include "AICharacter.hpp"

AICharacter::AICharacter(b2World* World, sf::RenderWindow* Window, sf::Sprite* Sprite) :
        Character(World, Window, Sprite)
{ }

void AICharacter::updateAll()
{
    updateFriction();
    driveHandler(false);
}
