#include "match.h"
#include "player.h"
#include "controller.h"

Match::Match(Player* _p1,Player* _p2) : score_board{0,0}, p1{_p1}, p2{_p2}, round{p1,p2,1}, textScore{"0              0",getFont(), 100}, background{getTexture("background.png")}

{
    textScore.setPosition(475,-15);
    textScore.setFillColor(sf::Color::Red);
	textScore.setOutlineColor(sf::Color::Black);
	textScore.setOutlineThickness(2);
}

Player* Match::looser()
{
     if (score_board.first < 2)
     	return p1;
     else
     	return p2;
}

void Match::update(Controllers & controller)
{
    if (round.done())
		new_round();
    else
		round.update(controller);
}

void Match::draw(sf::RenderWindow* window)
{
    if (round.MatchTime())
        round.draw(window);
    else
    {
        //draw background + scoreboard
        window->draw(background);
        window->draw(textScore);
        round.draw(window);
    }
}

void Match::new_round()
{
    if (p1 == round.winner())
	score_board.first++;
    else if (p2 == round.winner())
	score_board.second++;

    textScore.setString(std::to_string(score_board.first) + "              " + std::to_string(score_board.second));

    round = Round{p1,p2, score_board.first + score_board.second + 1};
}

bool Match::done()
{
    return score_board.first == 2 || score_board.second == 2;
}
