
#ifndef MATCH_H
#define MATCH_H

//=================================  
// Constants

//=================================  
// forward declared dependencies  
class Player;
struct Controllers;
//=================================  
// included dependencies
#include <SFML/Graphics.hpp>
#include "round.h"
#include "library.h"

class Match : public The_font, public Texture_lib
{
public:
    Match(Player* _p1,Player* _p2);
    Match(const Match&) = delete;
    Match& operator=(const Match&) = default;
    Player* looser();
    void update(Controllers & controller);
    void draw(sf::RenderWindow* window);
    void new_round();
    bool done();
private:
    std::pair<int,int> score_board;
    Player* p1;
    Player* p2;
    Round round;
    sf::Text textScore;
    sf::Sprite background;
};
#endif
