#ifndef MENU_H 
#define MENU_H
//=================================  
// Constants

//=================================  
// forward declared dependencies  

//=================================  
// included dependencies
#include "game_state.h"
#include "button.h"
#include "options.h"
#include "library.h"
#include "tournament.h"
#include "match.h"
#include "player.h"
#include "characters.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "winscreen.h"

class Menu : protected Game_State, protected Texture_lib, protected The_font, protected Sound_lib
{
public:
    Menu(sf::RenderWindow*);
   ~Menu();
    Menu(const Menu&)= delete;
    Menu operator=(const Menu&)=delete;
    void update(std::vector<sf::Event>&);
    void draw();
private:
    void Animation();
    sf::Clock aniClock;
    std::vector<Button*> buttons;
    Options options;
    Tournament game;
    sf::RenderWindow* window;
    sf::Text title;
    sf::Sprite backG;
    sf::RectangleShape blackscreen,line;
    int playercount;
    Button playerbutton;
    Button returnbutton;
    Button startbutton;
    sf::Clock antispammer;
    sf::Music backS;
    std::string vsS,tourS,setS;
    std::unique_ptr<WinScreen> winscreen;
};

#endif
