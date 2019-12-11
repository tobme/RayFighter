#include "game_state.h"

void Game_State::changeState(state const & new_state)
{
	current_state = new_state;
}

Game_State::state& Game_State::getState()  
{
	return current_state;
}
Game_State::state Game_State::current_state{menu};

