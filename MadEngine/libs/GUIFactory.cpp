#include "../stdafx.hpp"
#include "GUIFactory.hpp"
#include "GameStates.hpp"

GUIFactory::GUIFactory(sf::RenderWindow* window)
{
    m_Window    = window;
    GUIWindow   = NULL;
}

bool GUIFactory::initialize()
{
    if(!m_GUI.initialize())
        return false;

	try
	{
	    GUIWindow                       = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("GUI.layout");
	    CEGUI::System::getSingleton().setGUISheet(GUIWindow);

	    CEGUI::PushButton* Button       = (CEGUI::PushButton*)GUIWindow->getChild("DefaultWindow/Menu")->getChild("DefaultWindow/Menu/Start");
	    Button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIFactory::Handle_StartButtonClicked, this));

	    Button                          = (CEGUI::PushButton*)GUIWindow->getChild("DefaultWindow/Menu")->getChild("DefaultWindow/Menu/Quit");
	    Button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIFactory::Handle_QuitButtonClicked, this));

	    Button                          = (CEGUI::PushButton*)GUIWindow->getChild("DefaultWindow/Menu")->getChild("DefaultWindow/Menu/Options");
	    Button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIFactory::Handle_OptionsButtonClicked, this));

	    //Pause Menu
	    Button                          = (CEGUI::PushButton*)GUIWindow->getChild("DefaultWindow/Pause")->getChild("DefaultWindow/Pause/Resume");
	    Button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIFactory::Handle_ResumeButtonClicked, this));

	    Button                          = (CEGUI::PushButton*)GUIWindow->getChild("DefaultWindow/Pause")->getChild("DefaultWindow/Pause/Quit");
	    Button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIFactory::Handle_QuitButtonClicked, this));

	    //Options Menu
	    Button                          = (CEGUI::PushButton*)GUIWindow->getChild("DefaultWindow/Options")->getChild("DefaultWindow/Options/Back");
	    Button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIFactory::Handle_OptionsBackButtonClicked, this));

	}
	catch(CEGUI::Exception& e)
	{
	    std::cout << "CEGUI Error: " << e.getMessage().c_str() << std::endl;
		return false;
	}

	prevState       = GameStates::CurrentState();

	return true;
}

void GUIFactory::update(sf::Event& event)
{
    m_GUI.handleEvent(event);
}

void GUIFactory::updateState()
{
    if (prevState == GameStates::CurrentState())
        return;
    switch(GameStates::CurrentState())
    {
        case GameStates::Menu_Main:
        {
            GUIWindow->getChild("DefaultWindow/Menu")->activate();
            GUIWindow->getChild("DefaultWindow/Menu")->show();

            GUIWindow->getChild("DefaultWindow/Options")->deactivate();
            GUIWindow->getChild("DefaultWindow/Options")->hide();

            GUIWindow->getChild("DefaultWindow/Loading")->deactivate();
            GUIWindow->getChild("DefaultWindow/Loading")->hide();

            GUIWindow->getChild("DefaultWindow/Pause")->deactivate();
            GUIWindow->getChild("DefaultWindow/Pause")->hide();

            m_GUI.enableCursor();
            break;
        }

        case GameStates::Menu_Options:
        {
            GUIWindow->getChild("DefaultWindow/Menu")->deactivate();
            GUIWindow->getChild("DefaultWindow/Menu")->hide();

            GUIWindow->getChild("DefaultWindow/Options")->activate();
            GUIWindow->getChild("DefaultWindow/Options")->show();

            GUIWindow->getChild("DefaultWindow/Loading")->deactivate();
            GUIWindow->getChild("DefaultWindow/Loading")->hide();

            GUIWindow->getChild("DefaultWindow/Pause")->deactivate();
            GUIWindow->getChild("DefaultWindow/Pause")->hide();

            m_GUI.enableCursor();
            break;
        }

        case GameStates::Load:
        {
            GUIWindow->getChild("DefaultWindow/Loading")->activate();
            GUIWindow->getChild("DefaultWindow/Loading")->show();

            GUIWindow->getChild("DefaultWindow/Menu")->deactivate();
            GUIWindow->getChild("DefaultWindow/Menu")->hide();

            GUIWindow->getChild("DefaultWindow/Options")->deactivate();
            GUIWindow->getChild("DefaultWindow/Options")->hide();

            GUIWindow->getChild("DefaultWindow/Pause")->deactivate();
            GUIWindow->getChild("DefaultWindow/Pause")->hide();

            m_GUI.enableCursor();
            break;
        }

        case GameStates::Play:
        {
            GUIWindow->getChild("DefaultWindow/Menu")->deactivate();
            GUIWindow->getChild("DefaultWindow/Menu")->hide();

            GUIWindow->getChild("DefaultWindow/Options")->deactivate();
            GUIWindow->getChild("DefaultWindow/Options")->hide();

            GUIWindow->getChild("DefaultWindow/Loading")->deactivate();
            GUIWindow->getChild("DefaultWindow/Loading")->hide();

            GUIWindow->getChild("DefaultWindow/Pause")->deactivate();
            GUIWindow->getChild("DefaultWindow/Pause")->hide();

            m_GUI.disableCursor();
            break;
        }

        case GameStates::Pause:
        {
            GUIWindow->getChild("DefaultWindow/Pause")->activate();
            GUIWindow->getChild("DefaultWindow/Pause")->show();

            GUIWindow->getChild("DefaultWindow/Menu")->deactivate();
            GUIWindow->getChild("DefaultWindow/Menu")->hide();

            GUIWindow->getChild("DefaultWindow/Options")->deactivate();
            GUIWindow->getChild("DefaultWindow/Options")->hide();

            GUIWindow->getChild("DefaultWindow/Loading")->deactivate();
            GUIWindow->getChild("DefaultWindow/Loading")->hide();

            m_GUI.enableCursor();
            break;
        }
    }
    prevState   = GameStates::CurrentState();
}

void GUIFactory::draw()
{
    updateState();
    m_GUI.draw();
}

bool GUIFactory::Handle_StartButtonClicked(const CEGUI::EventArgs& e)
{
    GameStates::ChangeState(GameStates::Load);
    return true;
}

bool GUIFactory::Handle_OptionsButtonClicked(const CEGUI::EventArgs& e)
{
    GameStates::ChangeState(GameStates::Menu_Options);
    return true;
}

bool GUIFactory::Handle_QuitButtonClicked( const CEGUI::EventArgs& e)
{
    GameStates::ChangeState(GameStates::Exit);
    return true;
}

bool GUIFactory::Handle_ResumeButtonClicked( const CEGUI::EventArgs& e)
{
    GameStates::ChangeState(GameStates::Resume);
    return true;
}

bool GUIFactory::Handle_OptionsBackButtonClicked( const CEGUI::EventArgs& e)
{
    GameStates::ChangeState(GameStates::Menu_Main);
    return true;
}
