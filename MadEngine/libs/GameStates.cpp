#include "GameStates.hpp"

void GameStates::ChangeState(GameStates::States state)
{
    _State      = state;
}

GameStates::States GameStates::CurrentState()
{
    return _State;
}

GameStates::States GameStates::_State   = GameStates::Uninitialized;
