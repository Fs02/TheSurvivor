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

void SpriteFactory::loadSprite(const std::string& xmlfile)
{
    std::ifstream texturePack(xmlfile.c_str());
    std::vector<char> buffer((std::istreambuf_iterator<char>(texturePack)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    rapidxml::xml_document<> data;
    data.parse<rapidxml::parse_declaration_node|rapidxml::parse_no_data_nodes>(&buffer[0]);

    rapidxml::xml_node<>* root = data.first_node("texture_pack");
    std::string path = root->first_attribute("path")->value();

    rapidxml::xml_node<>* cur_node = root->first_node("texture");
    while (cur_node != NULL)
    {
        newSprite(cur_node->first_attribute("id")->value(), path + cur_node->first_attribute("filename")->value());

        cur_node = cur_node->next_sibling();
    }
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
