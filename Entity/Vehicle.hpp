/*
    Copyright (C) 2013 Muhammad Surya (Fs02)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VEHICLE_HPP_INCLUDED
#define VEHICLE_HPP_INCLUDED

#include "../MadEngine/stdafx.hpp"

class Tire
{
private:
    b2Body* m_Body;
    sf::Sprite* m_Sprite;

    float m_MaxFowardSpeed;
    float m_MaxBackwardSpeed;
    float m_MaxDriveForce;

    bool enableMotor;

public:
    Tire(b2World* World, sf::Sprite* sprite, bool EnableMotor = false);
    ~Tire();

    b2Vec2 getLateralVelocity();
    b2Vec2 getFowardVelocity();

    b2Body* getBody() const;

    void updateFriction();
    void updateDrive(int throttleState);
    void updateTurn();

    void render(sf::RenderWindow* Window);
};

class Vehicle
{
private:
    b2Body* m_Body;
    b2RevoluteJoint *frJoint, *flJoint;
    std::vector<Tire*> m_Tires;

    sf::Sprite* m_Sprite;

    bool m_Controlled;

public:
    Vehicle(b2World* World, sf::Sprite* carSprite, sf::Sprite* tireSprite, b2Vec2 dimension = b2Vec2(1.f , 2.5f));
    ~Vehicle();

    virtual void update();
    virtual void controller(int throttleState, int steerState);

    void acquireControl();
    void releaseControl();

    virtual void render(sf::RenderWindow* Window);

    sf::Vector2f getPosition();
    b2Body* getBody();
    float getAngle();
    int getCurrentSpeed();
};

#endif // CARPHYSIC_HPP_INCLUDED
