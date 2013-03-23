#include "Zombie.hpp"

void Zombie::updateAll()
{

}

void Zombie::EnemySighted(Character* character)
{
    m_EnemyOnSight.push_back(character);
}

void Zombie::EnemyUnSighted(Character* character)
{
    if (!m_EnemyOnSight.empty())
        m_EnemyOnSight.erase(std::find(m_EnemyOnSight.begin(), m_EnemyOnSight.end(), character));
}

b2Vec2* Zombie::getTarget()
{
    if (m_EnemyOnSight.empty()){}
        //return m_Body->GetPosition();

    Character* nearestEnemy;
    float nearestDistance = 0;
    float Distance;

    for (int i=0; i < m_EnemyOnSight.size(); i++)
    {
        Distance    = m_Body->GetLocalVector(m_EnemyOnSight[i]->b2_getPositon()).Normalize();
        if ((Distance < nearestDistance) || (Distance == 0))
        {
            nearestDistance = Distance;
            nearestEnemy    = m_EnemyOnSight[i];
        }
    }
    //return nearestEnemy->b2_getPositon();
}
