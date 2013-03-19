/*
 * GUI.hpp
 *
 *  Created on: Feb 19, 2013
 *      Author: alienjon
 */
#ifndef GUI_HPP_
#define GUI_HPP_

#include <map>

#include "../stdafx.hpp"
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

class GUI
{
	public:
	GUI();
	~GUI();

	bool initialize();
	bool handleEvent(sf::Event& event);
	void draw();

	void disableCursor();
	void enableCursor();

	private:
	/**
	 * @brief Initialize the resource groups.
	 */
	void initializeResourceGroups();

	typedef std::map<sf::Keyboard::Key, CEGUI::Key::Scan> KeyMap;
	typedef std::map<sf::Mouse::Button, CEGUI::MouseButton> MouseButtonMap;

	KeyMap mKeyMap;
	MouseButtonMap mMouseButtonMap;

	void initializeMaps();
	CEGUI::Key::Scan toCEGUIKey(sf::Keyboard::Key key);
	CEGUI::MouseButton toCEGUIMouseButton(sf::Mouse::Button button);
};

#endif /* GUI_HPP_ */
