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

#ifndef CARPHYSIC_H_INCLUDED
#define CARPHYSIC_H_INCLUDED

#include "../Engine/stdafx.h"

enum { IDLE, FOWARD, BACKWARD, TURNLEFT, TURNRIGHT};

class Tire
{
private:
    b2Body* m_Body;

    sf::Texture texture;
    sf::Sprite m_Sprite;

    float m_MaxFowardSpeed;
    float m_MaxBackwardSpeed;
    float m_MaxDriveForce;

    bool enableMotor;

public:
    Tire(b2World* World, bool EnableMotor = false);
    ~Tire();

    b2Vec2 getLateralVelocity();
    b2Vec2 getFowardVelocity();

    b2Body* getBody() const;

    void updateFriction();
    void updateDrive(int throttleState);
    void updateTurn();

    void render(sf::RenderWindow* Window);
};

class CarBody
{
private:
    b2Body* m_Body;
    b2RevoluteJoint *frJoint, *flJoint;
    std::vector<Tire*> m_Tires;

    sf::Texture texture;
    sf::Sprite m_Sprite;
    std::string spriteFile;

public:
    CarBody(b2World* World, std::string spriteFileName = "default.png", b2Vec2 dimension = b2Vec2(1.f , 2.5f));
    ~CarBody();

    void update();
    void getControl();

    void render(sf::RenderWindow* Window);

    sf::Vector2f getPosition();
    float getAngle();
    int getCurrentSpeed();
};

#endif // CARPHYSIC_H_INCLUDED
