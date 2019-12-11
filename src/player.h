#ifndef PLAYER_H
#define PLAYER_H
//=================================  
// Constants
#define LSTARTX 240
#define LSTARTY 540
#define RSTARTX 1100
#define RSTARTY 540

//=================================  
// forward declared dependencies 
class Controller;

//=================================  
// included dependencies
#include "character.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <memory>

class Player
{
public:
    Player(Character* charact,int playerNumber);
    Player(std::unique_ptr<Character> &charact,int playerNumber);
    void draw(sf::RenderWindow* window);
    void reset(bool);
    void update(Controller & controller);
    void collision(Player* p);
    void setSide(bool left);
    float get_hp();
    void set_tourHead(sf::Vector2f const & position);
    sf::RectangleShape& get_tourHead();
    void move_tourHead(float x, float y);
    sf::CircleShape& get_triangle();
    int get_playerNumber();
    std::string& get_name() { return character->get_name(); }
private:
    std::unique_ptr<Character> character;
    sf::CircleShape triangle;
    int playernbr;
};
#endif
