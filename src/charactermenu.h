#ifndef CHARACTERMENU_H
#define CHARACTERMENU_H
//=================================  
// Constants
#define NAMEPOS_X 600
#define NAMEPOS_Y  600
#define PORTSIZE 100
#define OFFSET 40
#define ROWSIZE 4 
#define KEYTIME 128
//=================================  
// forward declared dependencies  
struct Controllers;
//=================================  
// included dependencies
#include "character.h"
#include "characters.h"
#include <SFML/Graphics.hpp>
#include "library.h"
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <memory>
#include <string>


class Character_Menu : protected Texture_lib, protected Sound_lib
{
public:
    Character_Menu();
    Character_Menu(Character_Menu&)=delete;
    void draw(sf::RenderWindow* win_ptr);
    void update(sf::RenderWindow* win_ptr,Controllers & controller);
    bool done();
    std::unique_ptr<Character> & assigneHero();
//    sf::Texture* const setHead();
    Character_Menu operator=(const Character_Menu&)=delete;
protected:

    struct CharPortrait  : protected The_font,Texture_lib
    {
        sf::Text name;
        std::unique_ptr<Character> charact_ptr;
        sf::RectangleShape rect;
        CharPortrait(std::string _name,Character* _charact_ptr,sf::Vector2f pos); 
        void drawText(sf::RenderWindow* win_ptr) { win_ptr -> draw(name); }        
        void drawPort(sf::RenderWindow* win_ptr) { win_ptr -> draw(rect); }
        bool isPointed(sf::RenderWindow* win_pntr);
        bool isClicked(sf::RenderWindow* win_ptr);
    };
    
private:
    std::vector<Character_Menu::CharPortrait> chars;
    std::vector<CharPortrait>::iterator it_sel;
    CharPortrait* selected;
    sf::Clock keyClk;
	sf::Sprite background;
};


#endif
