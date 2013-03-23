#ifndef ZOMBIE_HPP_INCLUDED
#define ZOMBIE_HPP_INCLUDED

#include "../MadEngine/stdafx.hpp"
#include "Character.hpp"

class Zombie:
    public Character
{
private:
    std::vector<Character*> m_EnemyOnSight;
public:
    void updateAll();

    void EnemySighted(Character* character);
    void EnemyUnSighted(Character* Character);

    b2Vec2* getTarget();
};

#endif // ZOMBIE_HPP_INCLUDED
