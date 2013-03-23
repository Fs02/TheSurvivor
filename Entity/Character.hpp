#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include "../MadEngine/stdafx.hpp"
#include "Vehicle.hpp"
#include "Bullet.hpp"
#include "../MadEngine/libs/AniSprite.hpp"

//AnimState enum
class Character
{
protected:
    enum PlayerState {STAND, STEADY, STAND_SHOOT, WALK, WALK_SHOOT, THROW};

    PlayerState CurrentState;
    PlayerState prevState;

    b2Body* m_Body;
    AniSprite* m_AniSprite;
    int Health;
    int keyTemp;

    sf::RenderWindow* m_Window;
    sf::SoundBuffer footStepsBuffer;
    sf::Sound footStepsFX;

    bool isAttacking;

public:
    Vehicle* m_Vehicle;
    bool isDrive;

    Character(b2World* World, sf::RenderWindow* Window, sf::Sprite* spriteSheet, int fwidth = 50, int fheight = 50);
    ~Character();

    virtual void updateAll();
    void updateFriction();
    void controller(int walkState, int turnState);
    void runState(PlayerState State);
    void draw();

    b2Vec2 getNormal();

    void setVehicle(Vehicle* vehicle);
    void unsetCat();
    void driveHandler(bool control = true);

    void setTransform(float _x, float _y, float _deg);
    sf::Vector2f getPosition();
    b2Vec2 b2_getPositon();
    float getRotation();

    std::vector<Vehicle*>VehicleCache;
};

#endif // CHARACTER_HPP_INCLUDED
