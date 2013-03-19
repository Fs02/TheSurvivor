#ifndef GUIFACTORY_HPP_INCLUDED
#define GUIFACTORY_HPP_INCLUDED

#include "../stdafx.hpp"
#include "GUI.hpp"
#include "GameStates.hpp"

class GUIFactory
{
public:
    GUIFactory(sf::RenderWindow* window);

    bool initialize();
    void update(sf::Event& event);
    void updateState();
    void stop();
    void draw();

    bool Handle_StartButtonClicked( const CEGUI::EventArgs& e);
    bool Handle_QuitButtonClicked( const CEGUI::EventArgs& e);
    bool Handle_ResumeButtonClicked( const CEGUI::EventArgs& e);

private:
    sf::RenderWindow* m_Window;
    CEGUI::Window* GUIWindow;
    GUI m_GUI;

    GameStates::States prevState;
};

#endif // GUIFACTORY_HPP_INCLUDED
