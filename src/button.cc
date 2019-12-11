#include "button.h"

Button::Button() :size{},mousepos{},text{},pos{},clickSound{},hover{true}
{}

Button::Button(std::string texts,sf::Vector2i po, int textsize, std::string clickeffect) :size{},mousepos{},text{},pos{po},clickSound{},hover{true}
{
	if(clickeffect != "")
	{
		clickSound = "Sound_effects/"+clickeffect;
	}

    text.setFont(getFont());
    text.setString(texts);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(textsize);
    text.setStyle(sf::Text::Bold);
    text.setOutlineThickness(6);
    text.setOutlineColor(sf::Color::Black);
	auto tmp = text.getGlobalBounds();
    text.setPosition(pos.x - tmp.width/2,pos.y - tmp.height/2);
    size = textsize;
}

void Button::setText(std::string s)
{
	text.setString(s);
	auto tmp = text.getGlobalBounds();
	text.setPosition(pos.x - tmp.width/2,pos.y - tmp.height/2);
}

bool Button::isPressed(sf::RenderWindow* window)
{
    mousepos = sf::Mouse::getPosition(*window);
    sf::Rect<int> rect{window->mapCoordsToPixel(text.getPosition()).x,window->mapCoordsToPixel(text.getPosition()).y + size / 3,static_cast<int>(text.getGlobalBounds().width),static_cast<int>(text.getGlobalBounds().height)};
	if( rect.contains(mousepos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	    if(clickSound != "")playSound(clickSound,30);
		return true;
	}
	return false;
}

void Button::draw(sf::RenderWindow* window)
{
        mousepos = sf::Mouse::getPosition(*window);
	sf::Rect<int> rect{window->mapCoordsToPixel(text.getPosition()).x,window->mapCoordsToPixel(text.getPosition()).y + size / 3,static_cast<int>(text.getGlobalBounds().width),static_cast<int>(text.getGlobalBounds().height)};

    if (rect.contains(mousepos))
	{
	    if(hover)playSound("Sound_effects/hover.wav",30);
		text.setOutlineThickness(10.0f);
		hover = false;
	}
    else
	{
		hover = true;
		text.setOutlineThickness(6.0f);
	}

    window->draw(text);
}
