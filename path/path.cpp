#include "path.hpp"

path::path(b2Vec2* node, int count)
{
    if (!m_nodes.empty())
        m_nodes.clear();

    m_nodes.reserve(count);
    for (int i=0; i<count; i++)
    {
        m_nodes.push_back(&node[i]);
    }
}

path::path(sf::Vector2f* node, int count)
{
    if (!m_nodes.empty())
        m_nodes.clear();

    m_nodes.reserve(count);
    for (int i=0; i<count; i++)
    {
        m_nodes.push_back(new b2Vec2(node[i].x * UNRATIO, node[i].y * UNRATIO));
    }
}

path::~path()
{
    m_nodes.clear();
}
