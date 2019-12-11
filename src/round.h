#ifndef ROUND_H
#define ROUND_H

//=================================  
// Constants
//////////QuickiStart///////////
#define START_TIME1 2 // was 2 before
#define START_TIME2 0.1 // was 6 before
#define END_TIME 0.1    // was 2 before
////////////////////////////////
#define ROUND_TIME 60
#define BAR_x1 20
#define BAR_y1 10
#define BAR_x2 1380
#define BAR_y2 10
#define BAR_SIZE_X 400
#define BAR_SIZE_Y 80

//=================================  
// forward declared dependencies  
class Player;
class Controller;
struct Controllers;

//=================================  
// included dependencies
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include "library.h"


class Round : public The_font
{
public:
    Round(Player* P1, Player* P2, int roundnmbr);
    Round(const Round&) = delete;
    Round& operator=(const Round&) = default;
    Player* winner();
    bool done(); 
    bool MatchTime(){ return (startTimer.getElapsedTime().asSeconds() <= START_TIME1); }
    void update(Controllers& input); 
    void draw(sf::RenderWindow* win_ptr);
   
private:
    sf::Time time;
    Player* p1;
    Player* p2;
    sf::RectangleShape hp_bar1, hp_bar2; //Health-bar
    sf::RectangleShape bar1, bar2;      // Health-bar background
    sf::Clock endTimer;
    sf::Clock startTimer;
    sf::Clock roundTimer;
    sf::Text clockTimer;
	sf::Text infoText;
    int roundNumber;
    bool end;
}; 

#endif
