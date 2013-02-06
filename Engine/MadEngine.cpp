/*
    Copyright (C) 2013 Muhammad Surya (Fs02)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MadEngine.h"


void MadEngine::Start()
{
    if (_gameState != gs_Uninitialized)
        return;

    _mainWindow.create(sf::VideoMode(1024,800,32),"The Survivor");
    _mainWindow.setFramerateLimit(60);
    _mainWindow.setVerticalSyncEnabled(true);

    _gameState = gs_Loading;

    while (_gameState != gs_Exiting)
    {
        MainLoop();
    }

    _mainWindow.close();
}

void MadEngine::GameLoading()
{
    Car         = new CarBody(&_mainWorld);

    dummyLevelTexture.loadFromFile("Assets\\Level\\Asphalt.png");
    dummyLevelSprite.setTexture(dummyLevelTexture);

    _gameState  = gs_Playing;
}

void MadEngine::MainLoop()
{
    newDebugDraw.setRenderWindow(_mainWindow);
    _mainWorld.SetDebugDraw(&newDebugDraw);
    sf::Event CurrentEvent;
    while (_mainWindow.isOpen())
    {
        switch (_gameState)
        {

            case gs_Loading:
            {
                GameLoading();
                break;
            }
            case gs_Playing:
            {
                _mainWindow.clear(sf::Color::White);
                _mainWorld.Step(1/60.f,6,2);

                for (float x = 0; x <= 2560; x+=256)
                {
                    for (float y=0; y<=2560; y+=256)
                    {
                        dummyLevelSprite.setPosition(x,y);
                        _mainWindow.draw(dummyLevelSprite);
                    }
                }

                Car->update();
                Car->getControl();
                Car->render(&_mainWindow);


                //--------------------------------------------------------------------------------------------------------------------------------
                //Uncoment For debug render mode
                //DebugRender();
                //--------------------------------------------------------------------------------------------------------------------------------
                _mainCamera.reset(sf::FloatRect(Car->getPosition().x - _mainCamera.getSize().x/2, Car->getPosition().y - _mainCamera.getSize().y/2, 800, 600));
                _mainCamera.rotate(Car->getAngle());
                _mainWindow.setView(_mainCamera);

                //_mainWindow.draw(text);
                _mainWindow.display();
                break;
            }
        }

        _mainWindow.pollEvent(CurrentEvent);
        if (CurrentEvent.type == sf::Event::Closed)
        {
            _mainWindow.close();
        }
    }
}

void MadEngine::DebugRender()
{
    for (b2Body* b = _mainWorld.GetBodyList(); b; b = b->GetNext())
    {
        const b2Transform& xf = b->GetTransform();
        for (b2Fixture* fixture = b->GetFixtureList(); fixture; fixture = fixture->GetNext())
        {
            b2Color color = b2Color(0.5f, 0.5f, 0.3f);

            switch (fixture->GetType())
            {
                case b2Shape::e_circle:
                {
                    b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();

                    b2Vec2 center = b2Mul(xf, circle->m_p);
                    float32 radius = circle->m_radius;
                    b2Vec2 axis = b2Mul(xf.q, b2Vec2(1.0f, 0.0f));

                    newDebugDraw.DrawSolidCircle(center, radius, axis, color);
                }
                break;

                case b2Shape::e_edge:
                {
                    b2EdgeShape* edge = (b2EdgeShape*)fixture->GetShape();
                    b2Vec2 v1 = b2Mul(xf, edge->m_vertex1);
                    b2Vec2 v2 = b2Mul(xf, edge->m_vertex2);
                    newDebugDraw.DrawSegment(v1, v2, color);
                }
                break;

                case b2Shape::e_chain:
                {
                    b2ChainShape* chain = (b2ChainShape*)fixture->GetShape();
                    int32 count = chain->m_count;
                    const b2Vec2* vertices = chain->m_vertices;

                    b2Vec2 v1 = b2Mul(xf, vertices[0]);
                    for (int32 i = 1; i < count; ++i)
                    {
                        b2Vec2 v2 = b2Mul(xf, vertices[i]);
                        newDebugDraw.DrawSegment(v1, v2, color);
                        newDebugDraw.DrawCircle(v1, 0.05f, color);
                        v1 = v2;
                    }
                }
                break;

                case b2Shape::e_polygon:
                {
                    b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
                    int32 vertexCount = poly->m_vertexCount;
                    b2Assert(vertexCount <= b2_maxPolygonVertices);
                    b2Vec2 vertices[b2_maxPolygonVertices];

                    for (int32 i = 0; i < vertexCount; ++i)
                    {
                        vertices[i] = b2Mul(xf, poly->m_vertices[i]);
                    }

                    newDebugDraw.DrawSolidPolygon(vertices, vertexCount, color);
                }
                break;

                default:
                break;
            }
        }
    }
}

MadEngine::gameState MadEngine::_gameState = MadEngine::gs_Uninitialized;

sf::RenderWindow MadEngine::_mainWindow;
sf::View MadEngine::_mainCamera;

b2Vec2 Gravity(0.f,0.f);
b2World MadEngine::_mainWorld(Gravity);
DebugDraw MadEngine::newDebugDraw;

CarBody* MadEngine::Car;

sf::Texture MadEngine::dummyLevelTexture;
sf::Sprite MadEngine::dummyLevelSprite;
