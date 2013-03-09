#ifndef SPRITEFACTORY_HPP_INCLUDED
#define SPRITEFACTORY_HPP_INCLUDED

#include "../stdafx.hpp"

class SpriteFactory
{
private:
    std::vector<sf::Texture*> m_TextureList;
    std::map<std::string, sf::Sprite*>m_SpriteList;

    std::string assetsDir;
public:
    SpriteFactory();
    ~SpriteFactory();

    void loadSprite(const std::string& xmlfile);
    void newSprite(std::string id, std::string fileName);
    sf::Sprite* getSprite(std::string id);
};

#endif // SPRITEFACTORY_HPP_INCLUDED
