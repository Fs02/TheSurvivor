#include "Character.hpp"

Character::Character(b2World* World, sf::RenderWindow* Window, sf::Sprite* spriteSheet, int fwidth, int fheight)
{
    m_Window          = Window;

    b2BodyDef def;
    def.type        = b2_dynamicBody;

    m_Body          = World->CreateBody(&def);

    b2PolygonShape shape;
    shape.SetAsBox(0.25,0.2);

    b2FixtureDef fixDef;
    fixDef.shape    = &shape;
    fixDef.density  = 5.f;
    fixDef.filter.categoryBits = PLAYER;
    m_Body->CreateFixture(&fixDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 1.5f;
    fixDef.shape    = &circleShape;
    fixDef.isSensor = true;
    fixDef.filter.categoryBits = ENEMY_CENCOR;
    fixDef.density  = 1.f;
    m_Body->CreateFixture(&fixDef);
    m_Body->SetUserData(this);

    m_Vehicle       = NULL;
    isDrive         = false;

    m_AniSprite     = new AniSprite(spriteSheet, fwidth, fheight);
    m_AniSprite->SetLoopSpeed(10);
    m_AniSprite->setOrigin(64,76);
    m_AniSprite->SetInvert(true);

    keyTemp         = 0;

    footStepsBuffer.loadFromFile("Audio//SFX//footsteps.ogg");
    footStepsFX.setBuffer(footStepsBuffer);
    footStepsFX.setLoop(true);
}

Character::~Character()
{
    m_Body->GetWorld()->DestroyBody(m_Body);
}

void Character::updateAll()
{
    updateFriction();
    int walkState = 0;
    int turnState = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))           walkState = FOWARD;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))         walkState = BACKWARD;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))         turnState = TURNLEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))        turnState = TURNRIGHT;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))     isAttacking = true;
    else                                                        isAttacking = false;

    controller(walkState, turnState);
}

void Character::updateFriction()
{
    m_Body->ApplyForce(-2 * m_Body->GetLinearVelocity(), m_Body->GetWorldCenter());
    m_Body->ApplyTorque( m_Body->GetInertia() * -m_Body->GetAngularVelocity());
}

void Character::setVehicle(Vehicle* vehicle)
{
    if (!isDrive)   m_Vehicle       = vehicle;
}

void Character::unsetCat()
{
    if (!isDrive)   m_Vehicle       = NULL;
}

void Character::driveHandler(bool control)
{
    if ((!isDrive) && (m_Vehicle != NULL))
    {
        if (control)    m_Vehicle->acquireControl();
        m_Body->SetActive(false);
        isDrive     = true;
    }
    else if ((isDrive) && (m_Vehicle != NULL))
    {
        if (control)    m_Vehicle->releaseControl();
        m_Body->SetTransform(m_Vehicle->getBody()->GetWorldPoint(b2Vec2(1.5,1)), m_Vehicle->getAngle());
        m_Body->SetActive(true);
        isDrive     = false;
    }
    else return;
}

void Character::setTransform(float _x, float _y, float _deg)
{
    m_Body->SetTransform(b2Vec2(_x * RATIO, _y *RATIO), _deg * DEGTORAD);
}

void Character::controller(int walkState, int turnState)
{
    b2Vec2 desiredVelocity;
    b2Vec2 vel = m_Body->GetLinearVelocity();

    b2Vec2 direction ;
    PlayerState State = STEADY;
    float desiredAngle = m_Body->GetAngle();
    if (walkState == FOWARD)   { State = WALK; direction = m_Body->GetWorldVector(b2Vec2(0,1.f));  }
    if (walkState == BACKWARD) { State = WALK; direction = m_Body->GetWorldVector(b2Vec2(0,-1.f)); }
    if (turnState == TURNLEFT)  desiredAngle += -5.f * DEGTORAD;
    if (turnState == TURNRIGHT) desiredAngle += 5.f * DEGTORAD;

    runState(State);
    m_AniSprite->Update();
    draw();

    desiredVelocity = m_Body->GetWorldVector(direction);

    m_Body->ApplyLinearImpulse(direction , m_Body->GetWorldCenter());
    m_Body->ApplyLinearImpulse(-0.1 * m_Body->GetMass() * m_Body->GetLinearVelocity(), m_Body->GetWorldCenter());


    float nextAngle = m_Body->GetAngle() + m_Body->GetAngularVelocity()/ 60;
    //sf::Vector2i targetPos   = sf::Mouse::getPosition(*m_Window) - sf::Vector2i(m_Window->getSize().x/2, m_Window->getSize().y/2);
    //float desiredAngle             = atan2f(-targetPos.x, targetPos.y);
    float totalRotation = desiredAngle - nextAngle;
    while (totalRotation < -180 * DEGTORAD) totalRotation+=360 * DEGTORAD;
    while (totalRotation > 180 * DEGTORAD)  totalRotation-=360 * DEGTORAD;
    float desiredAngularVelocity = totalRotation * 60;
    m_Body->ApplyAngularImpulse(m_Body->GetInertia() * desiredAngularVelocity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        keyTemp++;
        if (keyTemp == 1)   driveHandler();     //Make Sure driveHandler() only called once
    }
    else
    {
        keyTemp = 0;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        new Bullet(m_Body->GetWorld(), m_Body->GetWorldPoint(b2Vec2(0,1)) , getNormal());
    }

    for (unsigned int i = 0; i < VehicleCache.size(); i++)
    {
        setVehicle(VehicleCache[i]);
    }
    VehicleCache.clear();
}

void Character::runState(PlayerState State)
{
    if (isAttacking)
    {
        if (State == WALK)   State   = WALK_SHOOT;
        if (State == STEADY) State   = STAND_SHOOT;
    }

    if (CurrentState != State)
    {
        CurrentState    = State;
        switch (State)
        {
            case STAND      : m_AniSprite->Play(0, 0);  break;
            case STEADY     : m_AniSprite->Play(1, 1);  break;
            case STAND_SHOOT: m_AniSprite->Play(2, 9);  break;
            case WALK       : m_AniSprite->Play(10,17); break;
            case WALK_SHOOT : m_AniSprite->Play(18,25); break;
            case THROW      : m_AniSprite->Play(26,30); break;
        }
        prevState   = CurrentState;
    }
}

void Character::draw()
{
    if (!isDrive)
    {
        m_AniSprite->setPosition(m_Body->GetPosition().x * RATIO, m_Body->GetPosition().y * RATIO);
        m_AniSprite->setRotation(m_Body->GetAngle() * RADTODEG);
        m_AniSprite->Draw(m_Window);
    }
}

b2Vec2 Character::getNormal()
{
    return m_Body->GetWorldVector(b2Vec2(0,1));
}

sf::Vector2f Character::getPosition()
{
    if (isDrive)    return sf::Vector2f(m_Vehicle->getPosition().x, m_Vehicle->getPosition().y);
    else            return sf::Vector2f(m_Body->GetPosition().x * RATIO, m_Body->GetPosition().y * RATIO);
}

float Character::getRotation()
{
    if (isDrive)    return m_Vehicle->getAngle();
    else            return m_Body->GetAngle() * RADTODEG;
}

b2Vec2 Character::b2_getPositon()
{
    //if (isDrive)    return m_Vehicle->getPosition();
    //else
    return m_Body->GetPosition();
}
