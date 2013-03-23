#ifndef GAMESTATES_HPP_INCLUDED
#define GAMESTATES_HPP_INCLUDED

class GameStates
{
public:
    enum States{Uninitialized, Splash, Pause, Resume, Menu_Main, Menu_Options, Load, Play, Exit};

    static void ChangeState(States state);
    static States CurrentState();

private:
    static States _State;
};

#endif // GAMESTATES_H_INCLUDED
