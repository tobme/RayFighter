#ifndef OPTIONS_H
#define OPTIONS_H

//=================================  
// Constants

//=================================  
// forward declared dependencies  

//=================================  
// included dependencies
#include <SFML/Window.hpp>
#include <vector>
#include <map>
#include "button.h"
#include "game_state.h"
#include "library.h"
#include "controller.h"

class Options : protected The_font, protected Game_State, protected Sound_lib
{
public:
	Options();
      ~Options() {
      texts.clear();
      waitForKeyTexts.clear();
      lookupKey.clear();
      p1buttons.clear();
      p2buttons.clear();
   }
    void update(sf::RenderWindow*,std::vector<sf::Event>&);
    void draw(sf::RenderWindow*);
    Controllers& get_controller();

	//Hidden variables
	Controllers cntr;
private:
	sf::RectangleShape Background,Volbar,Volbox;
	Button returnButton,pbutton,mbutton;
	std::map<Controller::key_enum,Button> p1buttons,p2buttons;
	std::vector<sf::Text> texts;
	std::vector<sf::Text> waitForKeyTexts;
	bool waitForKey,player1;
	Controller::key_enum selectedKey;
	std::map<sf::Keyboard::Key,std::string> lookupKey;

	sf::Text createText(std::string,sf::Vector2i);
	bool assignJoystickButtons(int);
	void assignJoystickAxis(int);
};


#endif
