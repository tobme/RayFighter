#include "round.h"
#include "player.h"
#include "controller.h"
#include <iostream>

Round::Round(Player* P1, Player* P2, int roundnmbr)
    :time{sf::seconds(ROUND_TIME)}, p1{P1}, p2{P2}, hp_bar1{}, hp_bar2{}, bar1{}, bar2{}, endTimer{}, startTimer{},roundTimer{}, clockTimer{"0",getFont(),100}, infoText{}, roundNumber{roundnmbr},end{false}
{
   // Jooohooo, det tror jag faktiskt! Tro inte. Vet
   p1->reset(true);
   p2->reset(false);

   clockTimer.setPosition(650,-10);
   clockTimer.setFillColor(sf::Color::Red);
   clockTimer.setOutlineThickness(2);
   clockTimer.setOutlineColor(sf::Color::Black);
            
   hp_bar1.setPosition(sf::Vector2f(BAR_x1, BAR_y1));
   hp_bar1.setFillColor(sf::Color::Green);
   hp_bar1.setSize(sf::Vector2f(p1->get_hp()/100*BAR_SIZE_X, BAR_SIZE_Y));
   bar1 = hp_bar1;
   bar1.setFillColor(sf::Color::Red);
   bar1.setOutlineColor(sf::Color::Black);
   bar1.setOutlineThickness(2);

   hp_bar2.setPosition(sf::Vector2f(BAR_x2, BAR_y2));
   hp_bar2.setFillColor(sf::Color::Green);
   hp_bar2.setSize(sf::Vector2f(p2->get_hp()/-100*BAR_SIZE_X, BAR_SIZE_Y));
   bar2 = hp_bar2;
   bar2.setFillColor(sf::Color::Red);
   bar2.setOutlineColor(sf::Color::Black);
   bar2.setOutlineThickness(2);

   infoText.setPosition(500,100);
   infoText.setFont(getFont());
   infoText.setCharacterSize(100);
   infoText.setFillColor(sf::Color::Red);
   infoText.setOutlineColor(sf::Color::Black);
   infoText.setOutlineThickness(2);
}

Player* Round::winner()
{
    if(ROUND_TIME - roundTimer.getElapsedTime().asSeconds() <= 0)
        return nullptr;
    else
        return (p1->get_hp() <= p2->get_hp()) ? p2 : p1 ;
}

bool Round::done()
{
    return end;
}

void Round::update(Controllers& input)
{
    if (startTimer.getElapsedTime().asSeconds() <= START_TIME1)
    {
		infoText.setString("ROUND " + std::to_string(roundNumber));
    }
    else if (startTimer.getElapsedTime().asSeconds() <= START_TIME2)
    {
		clockTimer.setOutlineThickness(0);
		clockTimer.setPosition(650,150);
		clockTimer.setString(std::to_string(static_cast<int>(6 - startTimer.getElapsedTime().asSeconds())));
		roundTimer.restart();
    }
    else if (p1->get_hp() <= 0 || p2->get_hp() <= 0)
    {
       if (endTimer.getElapsedTime().asSeconds() <= END_TIME)
        {
            hp_bar1.setSize(sf::Vector2f((p1->get_hp()/100)*BAR_SIZE_X, BAR_SIZE_Y));
            hp_bar2.setSize(sf::Vector2f((p2->get_hp()/-100)*BAR_SIZE_X, BAR_SIZE_Y));
            infoText.setString("K.O");
        }
        else 
            end = true;
    }
    else if( ROUND_TIME - roundTimer.getElapsedTime().asSeconds() <= 0)
    {
        if (roundTimer.getElapsedTime().asSeconds() <= 61)
        {
            hp_bar1.setSize(sf::Vector2f((p1->get_hp()/100)*BAR_SIZE_X, BAR_SIZE_Y));
            hp_bar2.setSize(sf::Vector2f((p2->get_hp()/-100)*BAR_SIZE_X, BAR_SIZE_Y));
            infoText.setString(" Draw ");
        }
        else 
            end = true;
    }
    else
    {
		clockTimer.setString(std::to_string(static_cast<int>(ROUND_TIME - roundTimer.getElapsedTime().asSeconds())));
        //Update controller
        input.p1.update();
        input.p2.update();

        //Update healthbar
        hp_bar1.setSize(sf::Vector2f((p1->get_hp()/100)*BAR_SIZE_X, BAR_SIZE_Y));
        hp_bar2.setSize(sf::Vector2f((p2->get_hp()/-100)*BAR_SIZE_X, BAR_SIZE_Y));

        //Update animation?

        //Update player input and characters 
        p1->update(input.p1); 
        p2->update(input.p2);

        //Update collision control 
        p1->collision(p2);
        p2->collision(p1);
        if (p1->get_hp() <= 0 || p2->get_hp() <= 0)
            endTimer.restart();
    }
}
   
void Round::draw(sf::RenderWindow* win_ptr)
{ 
	if(startTimer.getElapsedTime().asSeconds() <= END_TIME || startTimer.getElapsedTime().asSeconds() <= START_TIME1)
	{
		win_ptr->draw(infoText);
	}

	p1->draw(win_ptr);
	p2->draw(win_ptr);
	//Draw healthbar 
	win_ptr->draw(bar1);
	win_ptr->draw(bar2);
	win_ptr->draw(hp_bar1);
	win_ptr->draw(hp_bar2);
	win_ptr->draw(clockTimer);

    // Draw animations?
} 


