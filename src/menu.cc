#include "menu.h"
#include "button.h"
#include <iterator>
#include <string>
#include <stdexcept>
//#include <SFML/Rect.hpp>


Menu::Menu(sf::RenderWindow* _window) :
    aniClock{},buttons{},options{},game{},window{_window},title{"Ray Fighters",getFont(),100},backG{},blackscreen{sf::Vector2f(1400,800)},line{}, playercount{3}, playerbutton{"Players: 3", sf::Vector2i(_window->getView().getSize().x / 2 , 280)}, returnbutton{"Return",sf::Vector2i(200,700)},startbutton{"Start", sf::Vector2i(_window->getView().getSize().x / 2 , 350),50}, antispammer{},backS{}, vsS{"Sound_effects/versus.wav"},tourS{"Sound_effects/tournament.wav"},setS{"Sound_effects/settings.wav"}, winscreen{}

{
    int xpos = _window->getView().getSize().x / 2;
    int ypos = 280;
    int yinc = 110;

    title.setFillColor(sf::Color::Red);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(6);
    title.setPosition(xpos-title.getGlobalBounds().width/2,60);

    line.setSize(sf::Vector2f(title.getGlobalBounds().width,10));
    line.setPosition(title.getPosition().x,title.getPosition().y+title.getGlobalBounds().height/2 + 10);
    line.setFillColor(sf::Color::Black);

    backG.setTexture(getTexture("b1.png"));
    aniClock.restart();
    sf::Rect<float> size(backG.getLocalBounds());
    backG.setScale(sf::Vector2f(1400/size.width,800/size.height));
    size = backG.getLocalBounds();

    // initiering av knapparna //
    buttons.push_back(new Button("..vs..",sf::Vector2i(xpos,ypos),100,"front.wav"));
    buttons.push_back(new Button("Tournament",sf::Vector2i(xpos,ypos+yinc),100,"front.wav"));
    buttons.push_back(new Button("Settings",sf::Vector2i(xpos,ypos+yinc*2),100,"front.wav"));
    buttons.push_back(new Button("Quit",sf::Vector2i(xpos,ypos+yinc*3),100));

    blackscreen.setFillColor(sf::Color(0,0,0,125));
	backS.openFromFile("audio/Music/meny.wav");
	backS.setVolume(50);
	backS.setLoop(true);
}

Menu::~Menu() {
   for ( Button* b : buttons ) 
      delete b;
   buttons.clear();
}


void Menu::update(std::vector<sf::Event>& events)
{

    switch (getState())

    {
    case opt:
		backS.setVolume(0.5*getVolume());
        options.update(window,events);
        break;
    case tour:
        game.update(options.cntr,window);
	if (game.done())
	{
	    winscreen = std::make_unique<WinScreen>(game.get_head(),game.get_name());
	    changeState(win_screen);
	}
        break;
    case menu:
		if(backS.getStatus() != sf::Sound::Status::Playing)backS.play();
        Animation();	
        if(buttons.at(0) -> isPressed(window))
        {
			backS.stop();
			playSound(vsS,100);
            changeState(tour);
            game.start(2);
        } 
        else if(buttons.at(1) -> isPressed(window))
        {
			playSound(tourS,100);
            changeState(tour_init);
            sf::Vector2f lastpos = title.getPosition();
            lastpos.x = lastpos.x - title.getGlobalBounds().width/2;
            title.setString("Tournament Mode");
            title.setPosition(lastpos);
            title.move(title.getGlobalBounds().width/4,0);
        }
        else if(buttons.at(2) -> isPressed(window))
        {
			playSound(setS,100);
            changeState(opt);
        }
        else if(buttons.at(3) -> isPressed(window))
        {
            changeState(quit);
        }
        break;
    case win_screen:
	winscreen->update(window);
	break;
    default:
		Animation();
		if (playerbutton.isPressed(window) && antispammer.getElapsedTime().asMilliseconds() >= 500)
		{
			if (playercount < 8)
                playercount++;
			else
				playercount = 3;	    
			playerbutton = Button{"Players: " + std::to_string(playercount),sf::Vector2i(window->getView().getSize().x / 2 , 280)};

			antispammer.restart();
		}
		else if (returnbutton.isPressed(window))
		{
			changeState(menu);
			sf::Vector2f lastpos = title.getPosition();
			lastpos.x = lastpos.x - title.getGlobalBounds().width/4;
			title.setString("Ray Fighters");
			title.setPosition(lastpos);
			title.move(title.getGlobalBounds().width/2,0);
		}
		else if (startbutton.isPressed(window))
		{
			backS.stop();
			game.start(playercount);
			changeState(tour);
		}
		break;
    }
}


void Menu::draw()
{
    switch (getState())
    {
    case opt:
        options.draw(window);
        break;
    case tour:
        game.draw(window);
        break;
    case menu:
        window -> draw(backG);
        window -> draw(title);
        window -> draw(line);
        for (auto n: buttons) 
            n -> draw(window);
        break;
    case quit:
        window -> close();
        break;
    case win_screen:
	winscreen->draw(window);
	break;
    default:
        window -> draw(backG);
        window -> draw(blackscreen);
        window -> draw(title);
        playerbutton.draw(window);
        returnbutton.draw(window);
        startbutton.draw(window);
        break;
    }
}

void Menu::Animation()
{

    int cmp = 128;
    //  std::cout << "Animation::";
    if ( aniClock.getElapsedTime() < sf::milliseconds(cmp) )
    {
        backG.setTexture(getTexture("b1.png"));
    } 
    else if  (aniClock.getElapsedTime() < sf::milliseconds(cmp*2) )
    {
        backG.setTexture(getTexture("b2.png"));
    }
    else  if (aniClock.getElapsedTime() < sf::milliseconds(cmp*3) )
    {
        backG.setTexture(getTexture("b3.png"));
    }
    else  if (aniClock.getElapsedTime() < sf::milliseconds(cmp*4))
    {
        backG.setTexture(getTexture("b4.png"));
    }
    else  if (aniClock.getElapsedTime() < sf::milliseconds(cmp*5))
    {
        backG.setTexture(getTexture("b5.png"));
    }
    else  if (aniClock.getElapsedTime() < sf::milliseconds(cmp*6))
    {
        backG.setTexture(getTexture("b6.png"));
    }
    else//(aniClock.getElapsedTime() < sf::milliseconds(cmp*7))
        {
                aniClock.restart();
        }

}

