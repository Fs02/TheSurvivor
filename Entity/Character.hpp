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
    int m_AnimState;
    int keyTemp;

    sf::RenderWindow* m_Window;

public:
    Vehicle* m_Vehicle;
    bool isDrive;

    Character(b2World* World, sf::RenderWindow* Window, sf::Sprite* spriteSheet, int fwidth = 50, int fheight = 50);
    ~Character();

    virtual void updateAll();
    void updateFriction();
    void controller(int walkState, int turnState);
    void playAnim(int animState);
    void draw();

    b2Vec2 getNormal();

    void setVehicle(Vehicle* vehicle);
    void unsetCat();
    void driveHandler(bool control = true);

    void setTransform(float _x, float _y, float _deg);
    sf::Vector2f getPosition();
    float getRotation();

    std::vector<Vehicle*>VehicleCache;

};

#endif // CHARACTER_HPP_INCLUDED
