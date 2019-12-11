#include <SFML/Graphics.hpp>
#include <vector>
#include "library.h"
#include "menu.h"
#include <exception>
#include <iostream>

int main()
{

    sf::RenderWindow window(sf::VideoMode(1400, 800), "Ray Fighters");
   // window.setFramerateLimit(60);
    sf::Clock gameClock{};

	{
		//Game has its own bracket to make sure it deconstruct before static stuff
		Menu game{&window};
		while (window.isOpen())
		{
			if(gameClock.getElapsedTime().asMilliseconds() >= 16.66)
			{
				gameClock.restart();
				std::vector<sf::Event> events;
				sf::Event event;
				while (window.pollEvent(event))
				{
                                   if (event.type == sf::Event::Closed) {
						window.close();
                                                return 2;
                                   }
					events.push_back(event);
				}

				window.clear(sf::Color::White);
				// update game events
				try{
					game.update(events);
					game.draw();
				}
				catch (const std::exception& e )
				{
					std::cout << e.what() << std::endl;
					return 1;
				}
				// Draw stuff on screen 
				window.display();         
			}
		}
	}
	Sound_lib::Empty();
    return 0;
}
