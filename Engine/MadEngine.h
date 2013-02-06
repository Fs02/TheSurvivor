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

#ifndef MADENGINE_H_INCLUDED
#define MADENGINE_H_INCLUDED

#include "stdafx.h"
#include "../Vehicle/CarPhysic.h"
#include "DebugDraw.h"

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

private:
    enum gameState {gs_Uninitialized, gs_ShowingSplash, gs_Paused, gs_ShowingMenu, gs_Loading, gs_Playing, gs_Exiting};
    static b2World _mainWorld;

    static sf::RenderWindow _mainWindow;
    static sf::View _mainCamera;
    static DebugDraw newDebugDraw;

    static gameState _gameState;

    static CarBody* Car;

    static sf::Texture dummyLevelTexture;
    static sf::Sprite dummyLevelSprite;
};

#endif // MADENGINE_H_INCLUDED
