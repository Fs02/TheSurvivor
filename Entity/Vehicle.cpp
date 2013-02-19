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

#include "Vehicle.hpp"

//-----------------------------------------------------------------------------------------------------
//Tire's Physic Behavior
//-----------------------------------------------------------------------------------------------------

Tire::Tire(b2World* World, sf::Sprite* sprite, bool EnableMotor)
{
    //-------------------------------------------------------------------------------------------------
    // Constructing the Tire
    //-------------------------------------------------------------------------------------------------
    m_MaxFowardSpeed    = 160;
    m_MaxBackwardSpeed  = -40;
    m_MaxDriveForce     = 160;

    b2BodyDef def;
    def.type            = b2_dynamicBody;
    m_Body              = World->CreateBody(&def);

    b2PolygonShape shape;
    shape.SetAsBox(0.15f, 0.45f);

    b2FixtureDef fixDef;
    fixDef.shape        = &shape;
    m_Body->CreateFixture(&shape, 5.f);

    enableMotor = EnableMotor;
    //-------------------------------------------------------------------------------------------------
    //Set this Object as User Data
    //-------------------------------------------------------------------------------------------------
    m_Body->SetUserData(this);

    //-------------------------------------------------------------------------------------------------
    //Sprite
    //-------------------------------------------------------------------------------------------------
    m_Sprite = sprite;
}

Tire::~Tire()
{
    m_Body->GetWorld()->DestroyBody(m_Body);
    m_Body = NULL;
}

b2Vec2 Tire::getLateralVelocity()
{
    b2Vec2 currentRightNormal   = m_Body->GetWorldVector(b2Vec2(1,0));

    return b2Dot(currentRightNormal, m_Body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Tire::getFowardVelocity()
{
    b2Vec2 currentFowardNormal  = m_Body->GetWorldVector(b2Vec2(0,1));

    return b2Dot(currentFowardNormal, m_Body->GetLinearVelocity()) * currentFowardNormal;
}

b2Body* Tire::getBody() const
{
    return m_Body;
}

void Tire::updateFriction()
{
    //-------------------------------------------------------------------------------------------------
    //Killing the lateral Velocity
    //-------------------------------------------------------------------------------------------------
    b2Vec2 impulse = m_Body->GetMass() * -getLateralVelocity();
    m_Body->ApplyLinearImpulse(impulse, m_Body->GetWorldCenter());

    //-------------------------------------------------------------------------------------------------
    //Decreace angular velocity
    //-------------------------------------------------------------------------------------------------
    m_Body->ApplyAngularImpulse( 0.05 * m_Body->GetInertia() * - m_Body->GetAngularVelocity());

    //-------------------------------------------------------------------------------------------------
    //Apply Dragmagnitude
    //-------------------------------------------------------------------------------------------------
    float currentFowardSpeed    = getFowardVelocity().Normalize();
    float dragForceMagnitude    = -0.1 * currentFowardSpeed;

    m_Body->ApplyForce(dragForceMagnitude * getFowardVelocity(), m_Body->GetWorldCenter());
}

 void Tire::updateDrive(int throttleState)
{
    if (enableMotor){ //check wether the tire has motor enabled or no

    b2Vec2 currentFowardNormal  = m_Body->GetWorldVector(b2Vec2(0,1));
    float currentSpeed          = b2Dot(getFowardVelocity(),currentFowardNormal);
    float desiredSpeed          = 0;

    switch (throttleState)
    {
        case FOWARD     : desiredSpeed = m_MaxFowardSpeed;      break;
        case BACKWARD   : desiredSpeed = m_MaxBackwardSpeed;    break;
        case HANDBRAKE  : desiredSpeed = 0;                     break;
        default:return;
    }

    float force = 0;

    if (currentSpeed > desiredSpeed)
        force = - m_MaxDriveForce;
    else if (currentSpeed < desiredSpeed)
        force = m_MaxDriveForce;
    else return;

    //-------------------------------------------------------------------------------------------------
    // Applying the Drive Force
    //-------------------------------------------------------------------------------------------------
    m_Body->ApplyForce(force * currentFowardNormal, m_Body->GetWorldCenter());
    }
}

void Tire::updateTurn()
{
    float desiredTorque = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))    desiredTorque   = -5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))    desiredTorque   = 5;

    //-------------------------------------------------------------------------------------------------
    // Apllying the necessary Torque
    //-------------------------------------------------------------------------------------------------
    m_Body->ApplyTorque(desiredTorque);
}

void Tire::render(sf::RenderWindow* Window)
{
    m_Sprite->setPosition(m_Body->GetPosition().x * RATIO, m_Body->GetPosition().y * RATIO);
    m_Sprite->setRotation(m_Body->GetAngle() * RADTODEG);
    Window->draw(*m_Sprite);
}
//-----------------------------------------------------------------------------------------------------
//Car Physic
//-----------------------------------------------------------------------------------------------------


Vehicle::Vehicle(b2World* World, sf::Sprite* carSprite, sf::Sprite* tireSprite, b2Vec2 dimension)
{
    b2BodyDef def;
    def.type        = b2_dynamicBody;
    //def.position.Set(10.f,10.f);

    m_Body = World->CreateBody(&def);

    b2PolygonShape shape;
    shape.SetAsBox(dimension.x ,dimension.y);

    b2FixtureDef fixDef;
    fixDef.shape    = &shape;
    fixDef.density  = 0.5f;
    fixDef.filter.categoryBits  = VEHICLE;

    m_Body->CreateFixture(&fixDef);

    //-------------------------------------------------------------------------------------------------
    //The Tire Joints setting
    //-------------------------------------------------------------------------------------------------
    b2RevoluteJointDef jointDef;
    jointDef.bodyA          = m_Body;
    jointDef.lowerAngle     = 0;
    jointDef.upperAngle     = 0;
    jointDef.enableLimit    = true;
    jointDef.localAnchorA.SetZero();

    //-------------------------------------------------------------------------------------------------
    //Front Left Tire
    //-------------------------------------------------------------------------------------------------
    Tire* pTire             = new Tire(World, tireSprite);
    jointDef.bodyB          = pTire->getBody();
    jointDef.localAnchorA.Set( -(dimension.x - 0.25f), (dimension.y - 0.8));
    flJoint                 = (b2RevoluteJoint*)World->CreateJoint(&jointDef);
    m_Tires.push_back(pTire);

    //-------------------------------------------------------------------------------------------------
    //Front Right Tire
    //-------------------------------------------------------------------------------------------------
    pTire                   = new Tire(World, tireSprite);
    jointDef.bodyB          = pTire->getBody();
    jointDef.localAnchorA.Set( (dimension.x - 0.25f), (dimension.y - 0.8) );
    frJoint                 = (b2RevoluteJoint*)World->CreateJoint(&jointDef);
    m_Tires.push_back(pTire);

    //-------------------------------------------------------------------------------------------------
    //Back Tires
    //-------------------------------------------------------------------------------------------------
    pTire                   = new Tire(World, tireSprite, true);
    jointDef.bodyB          = pTire->getBody();
    jointDef.localAnchorA.Set( -(dimension.x - 0.25f), -(dimension.y - 0.8));
    World->CreateJoint(&jointDef);
    m_Tires.push_back(pTire);

    pTire                   = new Tire(World, tireSprite, true);
    jointDef.bodyB          = pTire->getBody();
    jointDef.localAnchorA.Set( (dimension.x - 0.25f), -(dimension.y - 0.8));
    World->CreateJoint(&jointDef);
    m_Tires.push_back(pTire);

    //-------------------------------------------------------------------------------------------------
    //Set this pointer as User Data
    //-------------------------------------------------------------------------------------------------
    m_Body->SetUserData(this);

    //-------------------------------------------------------------------------------------------------
    //Sprite
    //-------------------------------------------------------------------------------------------------
    m_Sprite                   = carSprite;

    m_Controlled               = false;
}

Vehicle::~Vehicle()
{
    for (unsigned int i = 0; i < m_Tires.size(); i++)
        delete m_Tires[i];
    m_Tires.clear();

    m_Body->GetWorld()->DestroyBody(m_Body);
    m_Body = NULL;
}

void Vehicle::update()
{
    //-------------------------------------------------------------------------------------------------
    //Control Car if it being controlled
    //-------------------------------------------------------------------------------------------------
    if (m_Controlled)
    {
        int throttleState   = 0;
        int steerDirection  = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))throttleState   = HANDBRAKE;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))    throttleState   = FOWARD;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))    throttleState   = BACKWARD;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))    steerDirection  = TURNLEFT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))    steerDirection  = TURNRIGHT;

        controller(throttleState, steerDirection);
    }
    //-------------------------------------------------------------------------------------------------
    //Update All Tires at once
    //-------------------------------------------------------------------------------------------------
    for (unsigned int i = 0; i < m_Tires.size(); i++)
        m_Tires[i]->updateFriction();
}

void Vehicle::controller(int throttleState, int steerState)
{
    //-------------------------------------------------------------------------------------------------
    //Control The Throtle and Brake
    //-------------------------------------------------------------------------------------------------
    for (unsigned int i = 0; i < m_Tires.size(); i++)
        m_Tires[i]->updateDrive(throttleState);

    //-------------------------------------------------------------------------------------------------
    //Control The Steering Wheel
    //-------------------------------------------------------------------------------------------------
    float turnPerSec    = 150 * DEGTORAD;
    float turnPerStep   = turnPerSec / 60.f;
    float lockAngle     = 40 * DEGTORAD;
    float linearSpeed   = m_Body->GetLinearVelocity().Normalize();
    lockAngle           = lockAngle - ((linearSpeed/100) * lockAngle);

    float desiredAngle;
    switch (steerState)
    {
        case TURNLEFT  : desiredAngle = -lockAngle;  break;
        case TURNRIGHT : desiredAngle = lockAngle;   break;
        default   : desiredAngle = 0;
    }

    float currentAngle  = frJoint->GetJointAngle();
    float angle2Turn    = desiredAngle - currentAngle;

    angle2Turn          = b2Clamp(angle2Turn, -turnPerStep, turnPerStep);
    float newAngle      = currentAngle + angle2Turn;

    flJoint->SetLimits(newAngle, newAngle);
    frJoint->SetLimits(newAngle, newAngle);
}

void Vehicle::acquireControl()
{
    m_Controlled    = true;
}

void Vehicle::releaseControl()
{
    m_Controlled    = false;
}

void Vehicle::render(sf::RenderWindow* Window)
{
    //-------------------------------------------------------------------------------------------------
    //Render four Tires
    //-------------------------------------------------------------------------------------------------
    for (unsigned int i = 0; i < m_Tires.size(); i++)
        m_Tires[i]->render(Window);

    //-------------------------------------------------------------------------------------------------
    //Render the Body
    //-------------------------------------------------------------------------------------------------
    m_Sprite->setPosition(m_Body->GetPosition().x * RATIO, m_Body->GetPosition().y * RATIO);
    m_Sprite->setRotation(m_Body->GetAngle() * RADTODEG);
    Window->draw(*m_Sprite);
}

sf::Vector2f Vehicle::getPosition()
{
    return sf::Vector2f(m_Body->GetPosition().x * RATIO, m_Body->GetPosition().y * RATIO);
}

b2Body* Vehicle::getBody()
{
    return m_Body;
}

float Vehicle::getAngle()
{
    return m_Body->GetAngle() * DEGTORAD;
}

int Vehicle::getCurrentSpeed()
{
    return (float)m_Tires[0]->getFowardVelocity().Normalize();
}

