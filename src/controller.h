#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <map>
#include <memory>

class Controller
{
public:
    enum key_enum{RIGHT , DOWN, LEFT, UP, KICK, PUNCH, SPECIAL};

    Controller(bool p1);
    void update();
   
//Setters
    void setKey(key_enum ,sf::Keyboard::Key);
	void setKey(key_enum ,int ,int);
	void setKey(key_enum ,int ,bool, sf::Joystick::Axis);
//Getters
    sf::Keyboard::Key getKey(key_enum );

    bool isKeyPressed(key_enum );
    bool up();
    bool down();
    bool left();
    bool right();
    bool kick();
    bool punch();
    bool special();

protected:
	class Input
	{
	public:
		virtual ~Input() = default;
		virtual bool isPressed() = 0;
		virtual sf::Keyboard::Key getKey() = 0;
	};
	class Key: public Input
	{
	public:
		Key(sf::Keyboard::Key);
		bool isPressed() override;
		sf::Keyboard::Key getKey() override;
	private:
		sf::Keyboard::Key key;
	};
	class JoyButton: public Input
	{
	public:
		JoyButton(int,int);
		bool isPressed() override;
		sf::Keyboard::Key getKey() override;
	private:
		int joystick,button;
	};
	class JoyAxis: public Input
	{
	public:
		JoyAxis(int,bool,sf::Joystick::Axis);
		bool isPressed() override;
		sf::Keyboard::Key getKey() override;
	private:
		int joystick;
		bool positive;
		sf::Joystick::Axis axis;
	};

private:
    std::map<key_enum, bool> truth_table;
    std::map<key_enum, std::unique_ptr<Input>> key_binds_table;
};

struct Controllers{
    Controller p1{true};
    Controller p2{false};
};
#endif
