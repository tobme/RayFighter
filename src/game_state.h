#ifndef GAME_STATE_H
#define GAME_STATE_H

class Game_State
{
protected:
    enum state{ menu, opt, tour, quit, tour_init, win_screen};
    void changeState(state const & new_state);
    state& getState();
private:
    static state current_state;
};

#endif
