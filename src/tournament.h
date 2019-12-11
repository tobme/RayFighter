#ifndef TOURNAMENT_H
#define TOURNAMENT_H

//=================================  
// forward declared dependencies  
struct Controllers;
class Match;
class Character_Menu;
class Player;
//=================================  
// included dependencies 
#include "button.h"
#include "game_state.h"
#include "player.h"
#include "library.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

class Tournament : public Game_State, protected Sound_lib
{
public:
    Tournament();
    Tournament(Tournament const &) = delete;
    Tournament& operator=(Tournament const &) = delete;
    void start(int pcount);
    void update(Controllers & controller, sf::RenderWindow* window);
    void draw(sf::RenderWindow* window);
    bool done();
    void next_match();
    const sf::Texture get_head();
    std::string get_name() { return players.front().get_name(); }
private:
    void createbracket();
    void helpcreate(int tempPlayers, int counter);
    void setbracketPos();
    void player_initializtion(sf::RenderWindow* win_ptr,Controllers & controller);
    void setcurrentmatch();
    void setWinner();
    void reset();

    std::vector<Player> players;
    Character_Menu* charMenu;
    std::unique_ptr<Match> match;
    bool inMatch;
    bool selChar;
    bool midle;
    Button startbutton;
    sf::RectangleShape winnerLine;
    sf::Clock blank;
    sf::Clock testclock;
    int bracketcounter;
    int playerleft;
    bool finish;

    class bracketMatch
    {
    public:
	bracketMatch(int _stage,int _number, int playercount, std::vector<bracketMatch> & bracket);
	sf::Vector2f pos1, pos2, winner;
	sf::Vector2f victoryPos;
	int stage;
	int number;
	std::vector<sf::RectangleShape> lines;
	std::vector<bracketMatch> tempbracket;
	bool ground1, ground2;

	bool ground(bool ps1);
    };
    int playercount;
    int currentmatch;
    std::vector<bracketMatch> bracket;
    struct drawText : protected The_font
    {  
        sf::Text Tex;
        drawText()=delete;
        drawText(std::string const & tex,sf::RenderWindow* win_ptr);
        void draw(sf::RenderWindow* win_ptr){win_ptr->draw(Tex);}
    };
	sf::Music menuMusic,matchMusic;
};
#endif
