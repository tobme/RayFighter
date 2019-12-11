#ifndef BUTTON_H
#define BUTTON_H

//=================================  
// Constants

//=================================  
// forward declared dependencies  

//=================================  
// included dependencies
#include <string>
#include "library.h"
#include <SFML/Graphics.hpp>

class Button : protected The_font, protected Sound_lib
{
public:
  Button();
  Button(std::string texts, sf::Vector2i pos, int textsize = 30, std::string clickeffect = "");
  void setText(std::string);
  bool isPressed(sf::RenderWindow* window);
  void draw(sf::RenderWindow* window);
private:
  int size;
  sf::Vector2i mousepos;
  sf::Text text;
  sf::Vector2f pos;
  std::string clickSound;
  bool hover;
};
#endif
