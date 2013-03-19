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

#ifndef MADENGINE_HPP_INCLUDED
#define MADENGINE_HPP_INCLUDED

#include "stdafx.hpp"
#include "libs/GameFactory.hpp"
#include "libs/GUIFactory.hpp"
#include "libs/DebugDraw.hpp"
#include "libs/ContactListener.hpp"
#include "libs/GameStates.hpp"

enum {C_CAR,C_HUMMER};

class MadEngine
{
public:
    static void Start();
    static void GameLoader();
    static void GamePlayLogic();

    static void SplashScreen();
    static void MainMenuScreen();
    static void InGameMenuScreen();
    static void LoadScreen();
    static void GameHUD();
    static void GamePlay();

    static void MainLoop();

    static void DebugRender();

    static float str2float(std::string input);
private:
    static b2World _mainWorld;
    static ContactListener _ContactListener;

    static sf::RenderWindow _mainWindow;
    static sf::View _mainCamera;
    static sf::Event _EventListener;
    static DebugDraw newDebugDraw;

    static sf::Texture dummyLevelTexture;
    static sf::Sprite dummyLevelSprite;

    static int playerControl;

    static GameFactory* Game;
    static GUIFactory* _GUI;
};

#endif // MADENGINE_HPP_INCLUDED
