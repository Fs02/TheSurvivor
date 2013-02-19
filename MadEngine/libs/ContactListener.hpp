#ifndef CONTACTLISTENER_HPP_INCLUDED
#define CONTACTLISTENER_HPP_INCLUDED

#include "../stdafx.hpp"

#include "../../Entity/Character.hpp"
#include "../../Entity/Vehicle.hpp"

class ContactListener
    : public b2ContactListener
{
public:
    void BeginContact(b2Contact* Contact);
    void EndContact(b2Contact* Contact);
};

#endif // COLLOSIONLISTENER_HPP_INCLUDED
