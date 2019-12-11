#include "options.h"
#include <fstream>

using namespace sf;

Options::Options()
	:cntr{},Background{},Volbar{},Volbox{},returnButton{},pbutton{},mbutton{},p1buttons{},p2buttons{},texts{},waitForKeyTexts{},waitForKey{false},player1{false},selectedKey{},lookupKey{}
{
	//Fyller lookupKey map för att kunna konvertera keys till strings för utritning längre ner
	std::ifstream ifs{"src/KeyboardKeys.txt"};
	sf::Keyboard::Key k{sf::Keyboard::Key::A};
	while(ifs)
	{
		std::string s;
		int i{k};
		std::getline(ifs,s);
		if(s == "KeyCount")
			break;
		lookupKey[k] = s;
		i++;
		k = static_cast<sf::Keyboard::Key>(i);
	}
	ifs.close();

	//Skapar alla knappar och texter som ska ritas ut
	//createText(string text, Vector2i pos)
	//button(string text,Vector2i pos,int textsize = 30)

	//Middle Column
	int posx{300};
	texts.push_back(createText(std::string("Settings"),Vector2i(posx,50))); texts.at(0).setStyle(Text::Underlined);
	texts.push_back(createText("Player 1",Vector2i(posx,100)));
	p1buttons[cntr.p1.key_enum::UP] = Button(lookupKey[cntr.p1.getKey(cntr.p1.key_enum::UP)],Vector2i(posx,150));
	p1buttons[cntr.p1.key_enum::DOWN] = Button(lookupKey[cntr.p1.getKey(cntr.p1.key_enum::DOWN)],Vector2i(posx,200));
	p1buttons[cntr.p1.key_enum::LEFT] = Button(lookupKey[cntr.p1.getKey(cntr.p1.key_enum::LEFT)],Vector2i(posx,250));
	p1buttons[cntr.p1.key_enum::RIGHT] = Button(lookupKey[cntr.p1.getKey(cntr.p1.key_enum::RIGHT)],Vector2i(posx,300));
	p1buttons[cntr.p1.key_enum::PUNCH] = Button(lookupKey[cntr.p1.getKey(cntr.p1.key_enum::PUNCH)],Vector2i(posx,350));
	p1buttons[cntr.p1.key_enum::KICK] = Button(lookupKey[cntr.p1.getKey(cntr.p1.key_enum::KICK)],Vector2i(posx,400));
	p1buttons[cntr.p1.key_enum::SPECIAL] = Button(lookupKey[cntr.p1.getKey(cntr.p1.key_enum::SPECIAL)],Vector2i(posx,450));
	//Right column
	posx = 500;
	texts.push_back(createText("Player 2",Vector2i(posx,100)));
	p2buttons[cntr.p2.key_enum::UP] = Button(lookupKey[cntr.p2.getKey(cntr.p2.key_enum::UP)],Vector2i(posx,150));
	p2buttons[cntr.p2.key_enum::DOWN] = Button(lookupKey[cntr.p2.getKey(cntr.p2.key_enum::DOWN)],Vector2i(posx,200));
	p2buttons[cntr.p2.key_enum::LEFT] = Button(lookupKey[cntr.p2.getKey(cntr.p2.key_enum::LEFT)],Vector2i(posx,250));
	p2buttons[cntr.p2.key_enum::RIGHT] = Button(lookupKey[cntr.p2.getKey(cntr.p2.key_enum::RIGHT)],Vector2i(posx,300));
	p2buttons[cntr.p2.key_enum::PUNCH] = Button(lookupKey[cntr.p2.getKey(cntr.p2.key_enum::PUNCH)],Vector2i(posx,350));
	p2buttons[cntr.p2.key_enum::KICK] = Button(lookupKey[cntr.p2.getKey(cntr.p2.key_enum::KICK)],Vector2i(posx,400));
	p2buttons[cntr.p2.key_enum::SPECIAL] = Button(lookupKey[cntr.p2.getKey(cntr.p2.key_enum::SPECIAL)],Vector2i(posx,450));
	//Left Column
	posx = 100;
	texts.push_back(createText("MoveUp",Vector2i(posx,150)));
	texts.push_back(createText("MoveDown",Vector2i(posx,200)));
	texts.push_back(createText("MoveLeft",Vector2i(posx,250)));
	texts.push_back(createText("MoveRight",Vector2i(posx,300)));
	texts.push_back(createText("Punch",Vector2i(posx,350)));
	texts.push_back(createText("Kick",Vector2i(posx,400)));
	texts.push_back(createText("Special",Vector2i(posx,450)));
	texts.push_back(createText("Vol",Vector2i(posx,550)));
	returnButton = Button("return",Vector2i(posx,700),30,"back.wav");
		
	//Other
	waitForKeyTexts.push_back(createText("Press Key To Bind",Vector2i(500,200)));
	Background.setPosition(Vector2f(0,0));
	Background.setFillColor(Color(128,128,128,255));
	Volbar.setPosition(Vector2f(200,550));
	Volbar.setFillColor(Color::Red);
	Volbar.setSize(Vector2f(getVolume()*3,40));
	Volbox.setPosition(Vector2f(200,550));
	Volbox.setFillColor(Color::Transparent);
	Volbox.setOutlineColor(Color::Red);
	Volbox.setOutlineThickness(3);
	Volbox.setSize(Vector2f(300,40));
	pbutton = Button("+",Vector2i(530,560));
	mbutton = Button("-",Vector2i(180,560));
}

Text Options::createText(std::string text, Vector2i pos)
{
	Text t(text,The_font::getFont());
	t.setPosition(pos.x - t.getGlobalBounds().width/2,pos.y - t.getGlobalBounds().height/2);
	t.setFillColor(Color::Red);
	return t;
}

void Options::update(sf::RenderWindow* win_ptr,std::vector<sf::Event>& events)
{
	
	if(!waitForKey)//Look for mouse input
	{
		if(returnButton.isPressed(win_ptr))
			changeState(state::menu);
		
		if(pbutton.isPressed(win_ptr) && getVolume() < 100)
		{
			setVolume(getVolume()+1);
			Volbar.setSize(Vector2f(getVolume()*3,40));
		}
		else if(mbutton.isPressed(win_ptr) && getVolume() > 0)
		{
			setVolume(getVolume()-1);
			Volbar.setSize(Vector2f(getVolume()*3,40));
		}

		for(auto it = p1buttons.begin(); it != p1buttons.end(); it++)
		{
			if(it->second.isPressed(win_ptr))
			{
				waitForKey = true;
				player1 = true;
				selectedKey = it->first;
				break;
			}
		}
		for(auto it = p2buttons.begin(); it != p2buttons.end(); it++)
		{
			if(it->second.isPressed(win_ptr))
			{
				waitForKey = true;
				player1 = false;
				selectedKey = it->first;
				break;
			}
		}
	}
	else //Look for user input
	{
		for(sf::Event & e : events)//Check events for keyboard inputs
		{
			if(e.type == sf::Event::KeyPressed)
			{
				if(e.key.code == sf::Keyboard::Escape || e.key.code == sf::Keyboard::Unknown)//abort if escape or unknown
				{
					waitForKey = false;
				}
				else
				{
					if(player1)
					{
						cntr.p1.setKey(selectedKey,e.key.code);
						p1buttons[selectedKey].setText(lookupKey[e.key.code]);
					}
					else
					{
						cntr.p2.setKey(selectedKey,e.key.code);
						p2buttons[selectedKey].setText(lookupKey[e.key.code]);
					}
					waitForKey = false;
				}
				break;
			}
		}
		for(int i{0};i<sf::Joystick::Count;i++)//Check all joystick axis and buttons
		{
			if(sf::Joystick::isConnected(i))
			{
			    waitForKeyTexts.push_back(createText("Joystick " + std::to_string(i) + " detected",Vector2i(500,250 + (i*50))));
				if(!assignJoystickButtons(i))
					assignJoystickAxis(i);     //If no buttons pressed check axis
			}
		}
	}
}

bool Options::assignJoystickButtons(int i)
{
	for(unsigned int j{0};j<sf::Joystick::getButtonCount(i);j++)//Check buttons
	{
		if(sf::Joystick::isButtonPressed(i,j))
		{
			if(player1)
			{
				cntr.p1.setKey(selectedKey,i,j);
				p1buttons[selectedKey].setText("J" + std::to_string(i) + " B" + std::to_string(j));
			}
			else
			{
				cntr.p2.setKey(selectedKey,i,j);
				p2buttons[selectedKey].setText("J" + std::to_string(i) + " B" + std::to_string(j));
			}
			waitForKey = false;
			return true;
		}
	}
	return false;
}

void Options::assignJoystickAxis(int i)
{
	for(int j{sf::Joystick::Axis::X};j != sf::Joystick::Axis::PovY;j++)
	{
		sf::Joystick::Axis jp = static_cast<sf::Joystick::Axis>(j);
		if(sf::Joystick::hasAxis(i,jp) && j != 5 && j != 4)
		{
                  auto axi = sf::Joystick::getAxisPosition(i,jp);
                  if(axi > 75 && axi < 90)
			{
				if(player1)
				{
                                  cntr.p1.setKey(selectedKey,i,true,jp);
					p1buttons[selectedKey].setText("JoyAxis+ " + std::to_string(j));
				}
				else
				{
                                  cntr.p2.setKey(selectedKey,i,true,jp);
					p2buttons[selectedKey].setText("JoyAxis+ " + std::to_string(j));
				}
				waitForKey = false;
			}
                  else if(axi < -75 && axi > -90)
			{
				if(player1)
				{
                                  cntr.p1.setKey(selectedKey,i,false,jp);
					p1buttons[selectedKey].setText("JoyAxis- " + std::to_string(j));
				}
				else
				{
                                  cntr.p2.setKey(selectedKey,i,false,jp);
					p2buttons[selectedKey].setText("JoyAxis- " + std::to_string(j));
				}
				waitForKey = false;
			}
		}
	}
}

Controllers& Options::get_controller()
{
    return cntr;
}

void Options::draw(RenderWindow* win_ptr)
{
	Background.setSize(Vector2f(2000,1000));
	win_ptr->draw(Background);
	win_ptr->draw(Volbox);
	win_ptr->draw(Volbar);
	pbutton.draw(win_ptr);
	mbutton.draw(win_ptr);
	returnButton.draw(win_ptr);
	for(sf::Text & t : texts)
	{
		win_ptr->draw(t);
	}
	for(auto it = p1buttons.begin(); it != p1buttons.end(); it++)
	{
		it->second.draw(win_ptr);
	}
	for(auto it = p2buttons.begin(); it != p2buttons.end(); it++)
	{
		it->second.draw(win_ptr);
	}

	if(waitForKey)
	{
		win_ptr->draw(Background);
		for(sf::Text & t : waitForKeyTexts)
		{
			win_ptr->draw(t);
		}
	}
}
