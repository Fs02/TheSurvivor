#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include "../MadEngine/stdafx.hpp"
#include "Vehicle.hpp"
#include "Bullet.hpp"
#include "../MadEngine/libs/AniSprite.hpp"

class Character
{
private:
    b2Body* m_Body;
    AniSprite* m_AniSprite;
    int Health;
    Vehicle* m_Vehicle;
    bool isDrive;
    int m_AnimState;
    int keyTemp;

    sf::RenderWindow* m_Window;

public:
    Character(b2World* World, sf::RenderWindow* Window, sf::Sprite* spriteSheet, int fwidth = 50, int fheight = 50);
    ~Character();

    void updateFriction();
    void controller();
    void playAnim(int animState);
    void draw();

    b2Vec2 getNormal();

    void setVehicle(Vehicle* vehicle);
    void unsetCat();
    void driveHandler();

    sf::Vector2f getPosition();
    float getRotation();

    std::vector<Vehicle*>VehicleCache;
};

#endif // CHARACTER_HPP_INCLUDED
