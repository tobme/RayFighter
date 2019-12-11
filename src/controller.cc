#include "controller.h"
#include <iostream>

using namespace std;

Controller::Controller(bool p1)
    : truth_table{}, key_binds_table{}
{
	if(p1) //Default controller for player1 
	{
		key_binds_table[RIGHT]  = make_unique<Key>(sf::Keyboard::D);
		key_binds_table[DOWN]   = make_unique<Key>(sf::Keyboard::S);
		key_binds_table[LEFT]   = make_unique<Key>(sf::Keyboard::A);
		key_binds_table[UP]     = make_unique<Key>(sf::Keyboard::W);
		key_binds_table[KICK]   = make_unique<Key>(sf::Keyboard::F);
		key_binds_table[PUNCH]  = make_unique<Key>(sf::Keyboard::G);
		key_binds_table[SPECIAL]= make_unique<Key>(sf::Keyboard::H);
	}
	else
	{
		key_binds_table[RIGHT]  = make_unique<Key>(sf::Keyboard::Right);
		key_binds_table[DOWN]   = make_unique<Key>(sf::Keyboard::Down);
		key_binds_table[LEFT]   = make_unique<Key>(sf::Keyboard::Left);
		key_binds_table[UP]     = make_unique<Key>(sf::Keyboard::Up);
		key_binds_table[KICK]   = make_unique<Key>(sf::Keyboard::K);
		key_binds_table[PUNCH]  = make_unique<Key>(sf::Keyboard::L);
		key_binds_table[SPECIAL]= make_unique<Key>(sf::Keyboard::J);
	}
    truth_table[RIGHT]  = false;
    truth_table[DOWN]   = false;
    truth_table[LEFT]   = false;
    truth_table[UP]     = false;
    truth_table[KICK]   = false;
    truth_table[PUNCH]  = false;
    truth_table[SPECIAL]= false;
}

void Controller::update()
{
	for (pair<const key_enum, unique_ptr<Controller::Input>> & key_pair : key_binds_table )
   {
      if (key_pair.second->isPressed())
      {
         truth_table[key_pair.first] = true;
      }
      else 
      {
         truth_table[key_pair.first] = false;
      }
   }
   
}

// SETTERS

void Controller::setKey(key_enum action, sf::Keyboard::Key keyBind)
{
	key_binds_table[action] = make_unique<Key>(keyBind);
}

void Controller::setKey(key_enum action, int joystick, int button)
{
	key_binds_table[action] = make_unique<JoyButton>(joystick,button);
}

void Controller::setKey(key_enum action, int joystick,bool positive, sf::Joystick::Axis axis)
{
	key_binds_table[action] = make_unique<JoyAxis>(joystick, positive, axis);
}

// GETTERS

sf::Keyboard::Key Controller::getKey(key_enum action)
{
	return key_binds_table[action]->getKey();
}

bool Controller::isKeyPressed(key_enum action)
{
    return truth_table[action];
}

bool Controller::up()
{
   return truth_table[UP];
}

bool Controller::down()
{
   return truth_table[DOWN];
}

bool Controller::left()
{
   return truth_table[LEFT];
}

bool Controller::right()
{
   return truth_table[RIGHT];
}

bool Controller::kick()
{
   return truth_table[KICK];
}

bool Controller::punch()
{
   return truth_table[PUNCH];
}

bool Controller::special()
{
   return truth_table[SPECIAL];
}

//Hidden classes
Controller::Key::Key(sf::Keyboard::Key k):key{k}
{}

Controller::JoyButton::JoyButton(int joy,int butt):joystick{joy},button{butt}
{}

Controller::JoyAxis::JoyAxis(int joy,bool posi,sf::Joystick::Axis axi):joystick{joy},positive{posi},axis{axi}
{}

bool Controller::Key::isPressed()
{
	if(sf::Keyboard::isKeyPressed(key))
		return true;
	return false;
}

bool Controller::JoyButton::isPressed()
{
	if(sf::Joystick::isButtonPressed(joystick,button))
		return true;
	return false;
}

bool Controller::JoyAxis::isPressed()
{
	float pos{sf::Joystick::getAxisPosition(joystick,axis)};
	if(pos > 60 && positive)
          return true;
        else if(pos < -60 && !positive)
          return true;
	return false;
}

sf::Keyboard::Key Controller::Key::getKey()
{
	return key;
}

sf::Keyboard::Key Controller::JoyButton::getKey()
{
	return sf::Keyboard::Key::Unknown;
}

sf::Keyboard::Key Controller::JoyAxis::getKey()
{
	return sf::Keyboard::Key::Unknown;
}
