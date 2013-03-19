#include "Level.hpp"

//Level::Level()
//{}

//Level::~Level()
//{
//    for (unsigned int i = 0; i < m_ObjectList.size(); i++)
//        delete m_ObjectList[i];
//
//    m_ObjectList.clear();
//}

void Level::loadLevel(const std::string& xml_map)
{
    m_SpriteFactory->newSprite("asphalt", "Level\\Asphalt.png");
 //   Level::setLevelSprite(m_SpriteFactory->getSprite("LEVEL1"));

    std::ifstream mapFile(xml_map.c_str());
    std::vector<char> buffer((std::istreambuf_iterator<char>(mapFile)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    rapidxml::xml_document<> map;
    map.parse<rapidxml::parse_declaration_node|rapidxml::parse_no_data_nodes>(&buffer[0]);

    rapidxml::xml_node<>* root_node = map.first_node("level");
    rapidxml::xml_node<>* cur_node = NULL;
    rapidxml::xml_node<>* map_node = NULL;

    name    = root_node->first_attribute("name")->value();
    std::cout<<"Level "<<name<<" loaded"<<std::endl;

    map_node = root_node->first_node("map");
    while (map_node != NULL)
    {
        if (strcmp(map_node->first_attribute("type")->value(),"terrain") == 0)
        {
            cur_node = map_node->first_node("sprite");
            while (cur_node != NULL)
            {
                sf::Sprite* terrain = new sf::Sprite;
                terrain->setTexture(*m_SpriteFactory->getSprite(cur_node->first_attribute("id")->value())->getTexture());
                terrain->setPosition(atof(cur_node->first_attribute("pos-x")->value()), atof(cur_node->first_attribute("pos-y")->value()));

                m_terrainSprite.push_back(terrain);
                cur_node = cur_node->next_sibling();
            }
        }
        else if (strcmp(map_node->first_attribute("type")->value(), "edges") == 0)
        {
            int count = atoi(map_node->first_attribute("count")->value());
            b2Vec2 vs[count];
            cur_node = map_node->first_node("edge");
            int x = 0;
            while (cur_node != NULL)
            {
                vs[x].Set(atof(cur_node->first_attribute("pos-x")->value()) * UNRATIO, atof(cur_node->first_attribute("pos-y")->value()) * UNRATIO);
                x++;
                cur_node = cur_node->next_sibling();
            }
            b2ChainShape chain;
            chain.CreateChain(vs, count);

            b2Body* edgeBody;
            b2BodyDef def;
            def.type = b2_staticBody;
            edgeBody = m_World->CreateBody(&def);

            edgeBody->CreateFixture(&chain, 1.f);
        }

        else if (strcmp(map_node->first_attribute("type")->value(),"building") == 0)
        {
            cur_node = map_node->first_node("building");
            while (cur_node != NULL)
            {
                b2Vec2 pos = b2Vec2(atof(cur_node->first_attribute("pos-x")->value()), atof(cur_node->first_attribute("pos-y")->value()));
                float rot  = atof(cur_node->first_attribute("rot")->value()) * DEGTORAD;
                StaticObject* building = new StaticObject(m_World, cur_node->first_attribute("model")->value());
                building->createSquareFixture(2.f, 2.f, b2Vec2_zero, 0);
                building->setPosition(atof(cur_node->first_attribute("pos-x")->value()), atof(cur_node->first_attribute("pos-y")->value()));
                building->setRotation(rot);

                Object* object = building;
                m_ObjectList.push_back(object);

                cur_node = cur_node->next_sibling();
            }
        }
        else {}
        map_node = map_node->next_sibling();
    }
    /*
    //terrain wrapper
    cur_node = root_node->first_node("terrain")->first_node("sprite");
    while (cur_node != NULL)
    {
        sf::Sprite* terrain = new sf::Sprite;
        terrain->setTexture(*m_SpriteFactory->getSprite(cur_node->first_attribute("id")->value())->getTexture());
        terrain->setPosition(atof(cur_node->first_attribute("pos-x")->value()), atof(cur_node->first_attribute("pos-y")->value()));

        m_terrainSprite.push_back(terrain);
        cur_node = cur_node->next_sibling();
    }

    //object wrapper
    cur_node = root_node->first_node("map")->first_node("building");
    while (cur_node != NULL)
    {
        b2Vec2 pos = b2Vec2(atof(cur_node->first_attribute("pos-x")->value()), atof(cur_node->first_attribute("pos-y")->value()));
        float rot  = atof(cur_node->first_attribute("rot")->value()) * DEGTORAD;
        StaticObject* building = new StaticObject(m_World, cur_node->first_attribute("model")->value());
        building->createSquareFixture(2.f, 2.f, b2Vec2_zero, 0);
        building->setPosition(atof(cur_node->first_attribute("pos-x")->value()), atof(cur_node->first_attribute("pos-y")->value()));
        building->setRotation(rot);

        Object* object = building;
        m_ObjectList.push_back(object);

        cur_node = cur_node->next_sibling();
    }
    */
}

void Level::setRenderWindow(sf::RenderWindow* Window)
{
    m_Window    = Window;
}

void Level::setPhysicWorld(b2World* World)
{
    m_World     = World;
}

void Level::setSpriteFactory(SpriteFactory* spriteFactory)
{
    m_SpriteFactory = spriteFactory;
}

void Level::AddObject(StaticObject* newStaticObject)
{
    m_ObjectList.push_back(newStaticObject);
}

void Level::DrawLevel()
{
    for (unsigned int i = 0; i < m_terrainSprite.size(); i++)
        m_Window->draw(*m_terrainSprite[i]);

    for (unsigned int i = 0; i < m_ObjectList.size(); i++)
        m_ObjectList[i]->Draw(m_Window);
}
