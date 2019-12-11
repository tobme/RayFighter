#include <SFML/Graphics.hpp>
#include <vector>
#include "library.h"
#include "player.h"
#include "match.h"
#include <exception>
#include <iostream>
#include <memory>
#include "characters.h"
#include "controller.h"

int main()
{

   sf::RenderWindow window(sf::VideoMode(1400, 800), "Ray Fighters");
   // window.setFramerateLimit(60);
   sf::Clock gameClock{};

   {
      //Game has its own bracket to make sure it deconstruct before static stuff
      Player p1{new Conan{},0};
      Player p2{new Nanders{},1};
      Match m{&p1,&p2};
      Controllers cont;
      while (window.isOpen())
      {
         if(gameClock.getElapsedTime().asMilliseconds() >= 16.66)
         {
            gameClock.restart();
            std::vector<sf::Event> events;
            sf::Event event;
            while (window.pollEvent(event))
            {
               if (event.type == sf::Event::Closed) 
                  window.close();
               events.push_back(event);
            }

            window.clear(sf::Color::White);
            // update game events
            try{
               m.update(cont);
               m.draw(&window);
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
