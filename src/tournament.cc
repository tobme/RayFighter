#include "tournament.h"
#include "button.h"
#include "match.h"
#include "charactermenu.h"
#include <string>
#include <math.h>
#include <iostream>

Tournament::Tournament() : players{},charMenu{nullptr}, match{},inMatch{false},selChar{false},midle{false},startbutton{"Start",sf::Vector2i{1200,600}},winnerLine{sf::Vector2f{20,100}},blank{},testclock{},bracketcounter{},playerleft{},finish{},playercount{}, currentmatch{}, bracket{}, menuMusic{}, matchMusic{}
{
    winnerLine.setFillColor(sf::Color::Black);
	menuMusic.openFromFile("audio/Music/pick.wav");
	menuMusic.setLoop(true);
	matchMusic.openFromFile("audio/Music/fight.wav");
	matchMusic.setLoop(true);
}
void Tournament::start(int pcount)
{
    reset();

    selChar=true;
    midle=true;
    blank.restart();
    playercount = playerleft = pcount;
}
void Tournament::reset()
{
    players.clear();
    charMenu = nullptr;
    bracketcounter = 0;
    finish = false;
    currentmatch = 0;
    bracket.clear();
    
}

void Tournament::update(Controllers & controller, sf::RenderWindow* window)
{
    if (players.size() == 1 && !selChar)
    {
	if (players.front().get_tourHead().getPosition().y >= winnerLine.getPosition().y)
	{
	     players.front().move_tourHead(0,-1);
	     players.front().get_triangle().move(0,-1);
	}

	finish = players.front().get_tourHead().getPosition().y == winnerLine.getPosition().y || playercount == 2;
	
    }
    else if (!inMatch && !selChar)
    {
	if (startbutton.isPressed(window) && testclock.getElapsedTime().asMilliseconds() >= 500)
	{
	    testclock.restart();
	    inMatch = true;
	    next_match();
	}
	setcurrentmatch();
    }
    else if(selChar)
	{
		menuMusic.setVolume(0.1*getVolume());
		if(menuMusic.getStatus() == sf::Music::Status::Stopped)
			menuMusic.play();
		player_initializtion(window,controller);
	}
    else
    {
		menuMusic.stop();
		matchMusic.setVolume(0.01*getVolume());
		if(matchMusic.getStatus() == sf::Music::Status::Stopped)
			matchMusic.play();
		match->update(controller);
		setWinner();
    }
}

void Tournament::draw(sf::RenderWindow* window)
{
    if (!inMatch && !selChar)
    {
	for (unsigned int i{}; i<bracket.size(); i++)
	{
	    for (unsigned int j{}; j<bracket.at(i).lines.size(); j++)
	    {
		window->draw(bracket.at(i).lines.at(j));
	    }
	}
	window->draw(winnerLine);
	startbutton.draw(window);

	for (Player & p : players)
	{
	    window->draw(p.get_triangle());
	    window->draw(p.get_tourHead());
	}
    }
    else if (selChar)
    {

        if (midle)
        {
            std::string temp= std::string{"Player : "} + (std::to_string(static_cast<int>(players.size())+1));
            Tournament::drawText text(temp,window);
            text.draw(window);       
        }       
        else if (charMenu != nullptr)
        {
			charMenu->draw(window);
        }
    }
    else
	match->draw(window);
}
bool Tournament::done()
{
    return finish;
}

void Tournament::player_initializtion(sf::RenderWindow* win_ptr,Controllers & controller)
{  
    if (static_cast<int>(players.size())< playercount)
    {
        if (charMenu==nullptr)
        {
            charMenu=new Character_Menu;
        }
        else 
        {

            if (!(charMenu->done()) && !midle)
            {
                charMenu->update(win_ptr,controller);
            }
            else if (midle)
            {
                   if ((blank.getElapsedTime()).asMilliseconds() > 1562)
                       midle=false;
            }
            else if (charMenu->done()) 
            {
                players.push_back(Player{charMenu->assigneHero(),static_cast<int>(players.size())});
                blank.restart();
                delete charMenu;
                if(static_cast<int>(players.size()) != playercount)midle = true;
                if (charMenu != nullptr)
                    charMenu=nullptr;
            }
        }
    }
    else 
    {
        inMatch = playercount == 2;
	if (playercount == 2)
	    next_match();
	else
	{
	    std::random_shuffle(players.begin(),players.end());
	    createbracket();
	}
        selChar=false;
    }
}

void Tournament::next_match()
{
    players.at(currentmatch).setSide(true);
    players.at(currentmatch+1).setSide(false);
    match = std::make_unique<Match>((&players.at(currentmatch)),(&players.at(currentmatch+1)));

    currentmatch++;
}
void Tournament::setcurrentmatch()
{
    if (players.at(currentmatch).get_tourHead().getPosition().y >= bracket.at(bracketcounter).pos1.y)
    {
	players.at(currentmatch).move_tourHead(0,-1);
	players.at(currentmatch).get_triangle().move(0,-1);
	players.at(currentmatch+1).get_triangle().move(0,-1);
	players.at(currentmatch+1).move_tourHead(0,-1);
    }
}
void Tournament::setWinner()
{
    if (match->done())
    {
	if (match->looser() == &players.at(currentmatch-1))
	{
	    if (playercount != 2)
	    {
		players.at(currentmatch).set_tourHead(bracket.at(bracketcounter).victoryPos);
		players.at(currentmatch).get_triangle().setPosition(bracket.at(bracketcounter).victoryPos.x + 10,bracket.at(bracketcounter).victoryPos.y-20);
	    }
	    players.erase(players.begin()+currentmatch-1);
	}
	else
	{
	    if (playercount != 2)
	    {
		players.at(currentmatch-1).set_tourHead(bracket.at(bracketcounter).victoryPos);
		players.at(currentmatch-1).get_triangle().setPosition(bracket.at(bracketcounter).victoryPos.x + 10,bracket.at(bracketcounter).victoryPos.y-20);
	    }
	    players.erase(players.begin()+currentmatch);
	}

	if (playerleft - currentmatch * 2 <= 1)
	{
	    currentmatch = 0;
	    playerleft -= floor(playerleft / 2);
	}
	bracketcounter++;
	matchMusic.stop();
	inMatch = false;
    }
}

void Tournament::createbracket()
{
    int tempPlayers{playercount};
    int counter{};
    while (tempPlayers != 1)
    {
	helpcreate(tempPlayers, counter);
	if (playercount == 6 && counter == 0)
	    tempPlayers -= 2;
	else
	    tempPlayers -= floor(tempPlayers / 2);
	counter++;
    }
    winnerLine.setPosition(bracket.back().victoryPos.x,bracket.back().victoryPos.y-100);

    setbracketPos();
}
void Tournament::helpcreate(int tempPlayers, int counter)
{
    int number{};
    while (tempPlayers > 1 && !(playercount == 6 && number == 2 && counter == 0))
    {
	bracket.push_back(bracketMatch{counter,number,playercount,bracket});
	number++;
	tempPlayers -= 2;
    }
}
void Tournament::setbracketPos()
{
    int playerSet{};
    int currentBracket{};

    while (playerSet < playercount)
    {
	if (bracket.at(currentBracket).ground1)
	{
	    players.at(playerSet).set_tourHead(sf::Vector2f{bracket.at(currentBracket).pos1.x, bracket.at(currentBracket).pos1.y + 100});
	    players.at(playerSet).get_triangle().setPosition(sf::Vector2f{bracket.at(currentBracket).pos1.x + 10, bracket.at(currentBracket).pos1.y + 80});
	    playerSet++;
	}

	if (bracket.at(currentBracket).ground2)
	{
	    players.at(playerSet).set_tourHead(sf::Vector2f{bracket.at(currentBracket).pos2.x, bracket.at(currentBracket).pos2.y + 100});
	    players.at(playerSet).get_triangle().setPosition(sf::Vector2f{bracket.at(currentBracket).pos2.x + 10, bracket.at(currentBracket).pos2.y + 80});
	    playerSet++;
	}
	currentBracket++;
    }
}
bool Tournament::bracketMatch::ground(bool ps1)
{
    
    for (bracketMatch & m : tempbracket)
    {
	if (ps1)
	{
	    if (pos1.y + 100 == m.victoryPos.y && pos1.x == m.victoryPos.x)
		return false;
	}
	else
	{
	    if (pos2.y + 100 == m.victoryPos.y && pos2.x == m.victoryPos.x)
		return false;
	}
		
    }
    
    return true;
}
Tournament::bracketMatch::bracketMatch(int _stage, int _number, int playercount, std::vector<bracketMatch> & bracket) : pos1{0,0}, pos2{0,0},winner{0,0},victoryPos{0,0},stage{_stage}, number{_number}, lines{}, tempbracket{bracket}, ground1{false},ground2{false}
{
    int const bracketHeight = 100;
    int const bracketWidth = 200;
    std::pair<float,float> const startpos{650 - (playercount - 2) * 60,600};
    float const lineWidth{20};

    int xstage{0};
    int winnerstage{};
    for (int i{1}; i<=stage; i++)
    {
	xstage += bracketWidth / 4 * i;
	winnerstage += bracketWidth/2 * i;
    }
    
    float xpos{startpos.first + number * bracketWidth * (stage + 1) + xstage};
    float ypos{startpos.second - stage * bracketHeight};
    
    pos1 = sf::Vector2f{xpos,ypos};
    pos2 = sf::Vector2f{xpos+bracketWidth/2 + winnerstage,ypos};
    winner = sf::Vector2f{xpos,ypos};

    sf::RectangleShape line{sf::Vector2f{lineWidth,bracketHeight}};
    line.setPosition(pos1);
    line.setFillColor(sf::Color::Black);

    sf::RectangleShape line2{sf::Vector2f{lineWidth,bracketHeight}};
    line2.setPosition(pos2);
    line2.setFillColor(sf::Color::Black);

    sf::RectangleShape line3{sf::Vector2f{bracketWidth / 2 + float(winnerstage),lineWidth}};
    line3.setPosition(winner);
    line3.setFillColor(sf::Color::Black);

    lines.push_back(line);
    lines.push_back(line2);
    lines.push_back(line3);
    
    victoryPos = sf::Vector2f{xpos+(bracketWidth / 2 + float(winnerstage)) / 2,ypos};

    ground1 = ground(true);
    ground2 = ground(false);
}

Tournament::drawText::drawText(std::string const& tex,sf::RenderWindow* win_ptr)
    :Tex{}
{
	Tex.setFont(getFont());
	Tex.setString(tex);
	Tex.setFillColor(sf::Color::Red);
	Tex.setCharacterSize(100);
	Tex.setOutlineThickness(2);
	Tex.setOutlineColor(sf::Color::Black);
	auto temp2 = Tex.getGlobalBounds();
	sf::Vector2u bound{win_ptr->getSize()};
	Tex.setPosition(bound.x/2-temp2.width/2,bound.y/2-temp2.height);
}
const sf::Texture Tournament::get_head()
{
    return *players.front().get_tourHead().getTexture();
}
