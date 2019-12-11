#include "player.h"
#include <iostream>
#include "controller.h"


Player::Player(Character* charact,int playerNumber) : character{charact}, triangle{10,3}, playernbr{playerNumber}
{
    switch (playerNumber)
    {
    case 0:
	triangle.setFillColor(sf::Color::Red);
	break;
    case 1:
	triangle.setFillColor(sf::Color::Blue);
	break;
    case 2:
	triangle.setFillColor(sf::Color::Cyan);
	break;
    case 3:
	triangle.setFillColor(sf::Color::Magenta);
	break;
    case 4:
	triangle.setFillColor(sf::Color(128,128,128));
	break;
    case 5:
	triangle.setFillColor(sf::Color::Yellow);
	break;
    case 6:
	triangle.setFillColor(sf::Color(255,140,0));
	break;
    default:
	triangle.setFillColor(sf::Color::Green);
	break;
    }
    triangle.setOrigin(5,5);
    triangle.rotate(180);
    //triangle.setOrigin(0,0);
}

Player::Player(std::unique_ptr<Character> &charact,int playerNumber) : character{std::move(charact)}, triangle{10,3}, playernbr{playerNumber}
{  
    switch (playerNumber)
    {
    case 0:
	triangle.setFillColor(sf::Color::Red);
	break;
    case 1:
	triangle.setFillColor(sf::Color::Blue);
	break;
    case 2:
	triangle.setFillColor(sf::Color::Cyan);
	break;
    case 3:
	triangle.setFillColor(sf::Color::Magenta);
	break;
    case 4:
	triangle.setFillColor(sf::Color(128,128,128));
	break;
    case 5:
	triangle.setFillColor(sf::Color::Yellow);
	break;
    case 6:
	triangle.setFillColor(sf::Color(255,140,0));
	break;
    default:
	triangle.setFillColor(sf::Color::Green);
	break;
    }
    triangle.setOrigin(5,5);
    triangle.rotate(180);
    //triangle.setOrigin(0,0);
}

void Player::draw(sf::RenderWindow* window)
{
    character->draw(window);
}

void Player::reset(bool left)
{
    character->reset();
    if(left)
        character-> setPosition(sf::Vector2f(LSTARTX,LSTARTY),left);
    else 
        character-> setPosition(sf::Vector2f(RSTARTX,RSTARTY),left);   
}

void Player::update(Controller & controller)
{
    if (controller.isKeyPressed(controller.key_enum::RIGHT))
    {
	character->move(true);
    }
    else if (controller.isKeyPressed(controller.key_enum::LEFT))
    {
	character->move(false);
    }
    if (controller.isKeyPressed(controller.key_enum::UP))
    {
	character->jump();
    }
    else if (controller.isKeyPressed(controller.key_enum::DOWN))
    {
	character->duck();
    }
    if (controller.isKeyPressed(controller.key_enum::KICK))
    {
	character->kick();
    }
    else if (controller.isKeyPressed(controller.key_enum::PUNCH))
    {
	character->punch();
    }
    else if (controller.isKeyPressed(controller.key_enum::SPECIAL))
    {
	character->special_attack();
    }
    character->update();
}
void Player::collision(Player* p)
{
	character->check_collision(*(p->character));
}
void Player::setSide(bool left)
{
	character->setSide(left);
}
float Player::get_hp()
{
    return (character->get_hp() > 0 ) ? character->get_hp() : 0.f;
}
void Player::set_tourHead(sf::Vector2f const & position)
{
    character->set_tourHead(position);
}
sf::RectangleShape& Player::get_tourHead()
{
    return character->get_tourHead();
}
void Player::move_tourHead(float x, float y)
{
    character->move_tourHead(x,y);
}
sf::CircleShape& Player::get_triangle()
{
    return triangle;
}
int Player::get_playerNumber()
{
    return playernbr;
}
