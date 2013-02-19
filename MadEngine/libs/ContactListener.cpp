#include "ContactListener.hpp"

void ContactListener::BeginContact(b2Contact* Contact)
{
    void* objA      = Contact->GetFixtureA()->GetBody()->GetUserData();
    void* objB      = Contact->GetFixtureB()->GetBody()->GetUserData();

    int CatBitsA    = Contact->GetFixtureA()->GetFilterData().categoryBits;
    int CatBitsB    = Contact->GetFixtureB()->GetFilterData().categoryBits;

    if ((CatBitsA == H_VEHICLE_SENSOR) && (CatBitsB == VEHICLE))
    {
        static_cast<Character*>(objA)->VehicleCache.push_back(static_cast<Vehicle*>(objB));
    }
    else if ((CatBitsA == VEHICLE) && (CatBitsB == H_VEHICLE_SENSOR))
    {
        static_cast<Character*>(objB)->VehicleCache.push_back(static_cast<Vehicle*>(objA));
    }
    else return;

}

void ContactListener::EndContact(b2Contact* Contact)
{
    void* objA      = Contact->GetFixtureA()->GetBody()->GetUserData();
    void* objB      = Contact->GetFixtureB()->GetBody()->GetUserData();

    int CatBitsA    = Contact->GetFixtureA()->GetFilterData().categoryBits;
    int CatBitsB    = Contact->GetFixtureB()->GetFilterData().categoryBits;

    if ((CatBitsA == H_VEHICLE_SENSOR) && (CatBitsB == VEHICLE))
    {
        static_cast<Character*>(objA)->VehicleCache.push_back(NULL);
    }
    else if ((CatBitsA == VEHICLE) && (CatBitsB == H_VEHICLE_SENSOR))
    {
        static_cast<Character*>(objB)->VehicleCache.push_back(NULL);
    }
    else return;

}
