#include "SpriteFactory.hpp"

SpriteFactory::SpriteFactory()
{
    assetsDir           = "Assets\\";

    newSprite("TIRE", "Vehicle\\tire.png");
    newSprite("HUMMER", "Vehicle\\Hummer.png");
    newSprite("DEATHCAR", "Vehicle\\deathCar.png");
    newSprite("EXAMPLECHAR", "Character\\example.png");
}

SpriteFactory::~SpriteFactory()
{
    std::map<std::string, sf::Sprite*>::iterator it_s;
    for (it_s = m_SpriteList.begin(); it_s != m_SpriteList.end(); it_s++)
        delete it_s->second;
    m_SpriteList.clear();

    std::vector<sf::Texture*>::iterator it_tex;
    for (it_tex = m_TextureList.begin(); it_tex != m_TextureList.end(); it_tex++)
        delete *it_tex;
    m_TextureList.clear();
    m_TextureList.clear();
}

void SpriteFactory::newSprite(std::string id, std::string fileName)
{
    sf::Texture *pTexture   = new sf::Texture;
    pTexture->loadFromFile(assetsDir+fileName);
    m_TextureList.push_back(pTexture);

    sf::Sprite *pSprite     = new sf::Sprite;
    pSprite->setTexture(*pTexture);
    pSprite->setOrigin(pSprite->getLocalBounds().width/2, pSprite->getLocalBounds().height/2);
    m_SpriteList.insert(std::pair<std::string, sf::Sprite*>(id, pSprite));
}

sf::Sprite* SpriteFactory::getSprite(std::string id)
{
    std::map<std::string, sf::Sprite*>::iterator it = m_SpriteList.find(id);
    if (it != m_SpriteList.end())
        return it->second;

    return NULL;
}
