#ifndef PATH_HPP_INCLUDED
#define PATH_HPP_INCLUDED

#include "../MadEngine/stdafx.hpp"

class path
{
public:
    std::vector<b2Vec2*> m_nodes;
    path(b2Vec2* node, int count);
    path(sf::Vector2f* node, int count);
    ~path();
};

#endif // PATH_HPP_INCLUDED
