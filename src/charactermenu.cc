#include "charactermenu.h"
#include "controller.h"

//sf::RenderWindow winptr

Character_Menu::Character_Menu():chars{},it_sel{},selected{nullptr},keyClk{},background{getTexture("background.png")}
{
int const Xofs{OFFSET+PORTSIZE} ;
    int Xpos{OFFSET};
    int Ypos{OFFSET};
    int const Yofs{OFFSET+PORTSIZE};
    keyClk.restart();
    chars.push_back(CharPortrait("Nanders",new Nanders() ,sf::Vector2f(Xpos+Xofs*0,Ypos+Yofs*0)));
    chars.push_back(CharPortrait("Pikadorf",new Pikadorf() ,sf::Vector2f(Xpos+Xofs*1,Ypos+Yofs*0)));
    chars.push_back(CharPortrait("Conan",new Conan() ,sf::Vector2f(Xpos+Xofs*2,Ypos+Yofs*0)));
    chars.push_back(CharPortrait("It",new It() ,sf::Vector2f(Xpos+Xofs*3,Ypos+Yofs*0)));
    chars.push_back(CharPortrait("Saitama",new Saitama() ,sf::Vector2f(Xpos+Xofs*0,Ypos+Yofs*1)));
    chars.push_back(CharPortrait("Default",new Default() ,sf::Vector2f(Xpos+Xofs*1,Ypos+Yofs*1)));
    it_sel= begin(chars);

	for (auto it{begin(chars)};it != end(chars);it++)
	{
            it -> charact_ptr -> setPosition(sf::Vector2f((1400/2+1400/4),(800/2)),false);
	}

}

void Character_Menu::draw(sf::RenderWindow* win_ptr)
{
    win_ptr -> draw(background);
    for(auto it{begin(chars)};it!= end(chars);it++)
    {  
        if (it!=it_sel)
        {           
            it-> rect.setOutlineThickness(2.0f);
            it->drawPort(win_ptr);
        }
    }
    
    it_sel-> rect.setOutlineThickness(10.0f);
    it_sel -> drawPort(win_ptr);
    it_sel->drawText(win_ptr);
    it_sel->charact_ptr->draw(win_ptr);
    
}

void Character_Menu::update(sf::RenderWindow* win_ptr,Controllers & controller)
{
    for(auto it{begin(chars)};it!= end(chars);it++)
    {    
        if(it->isPointed(win_ptr) && it_sel !=it)
	{
            it_sel=it;
	    playSound("Sound_effects/hover.wav",30);
	}
        
        if(it->isClicked(win_ptr))
		{
		    selected= &(*it);
			if(it_sel->charact_ptr->get_pickedSound() != "null")
			{
				playSound(it_sel->charact_ptr->get_pickedSound() + "picked.wav");
				playSound(it_sel->charact_ptr->get_pickedSound() + "an_picked.wav");
			}
		}
    }
    
    controller.p1.update();
    if ((keyClk.getElapsedTime() > sf::milliseconds(KEYTIME) ))
        {
            if (controller.p1.right())
            {
                if (it_sel!= end(chars))
		{
                    it_sel++;
		    playSound("Sound_effects/hover.wav",30);
		}
            }
            else if(controller.p1.left())
            {
                if (it_sel!=begin(chars))
		{
                    it_sel--;
		    playSound("Sound_effects/hover.wav",30);
		}
            }
            else if(controller.p1.up())
            {
                if (it_sel!= begin(chars))
                {
                    for(int i{0}; i!= ROWSIZE; i++)
                    {
                        it_sel--;
                        if(it_sel==begin(chars))
                            break;
                    }
		    playSound("Sound_effects/hover.wav",30);
                }
            }
            else if(controller.p1.down())
            {
                if (it_sel!= end(chars))
                {
                    for(int i{0}; i!= ROWSIZE; i++)
                    {
                        it_sel++;
                        if(it_sel==end(chars))
                            break;
                    }
		    playSound("Sound_effects/hover.wav",30);
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                selected= &(*it_sel);
				if(it_sel->charact_ptr->get_pickedSound() != "null")
				{
					playSound(it_sel->charact_ptr->get_pickedSound() + "picked.wav");
					playSound(it_sel->charact_ptr->get_pickedSound() + "an_picked.wav");
				}
            }
            keyClk.restart();
        }
    if(it_sel==end(chars))
        it_sel--;

}

bool Character_Menu::done()
{
    return (selected != nullptr);
}

std::unique_ptr<Character>& Character_Menu::assigneHero()
{
    if(selected != nullptr)
    {
        auto temp{selected};
        selected = nullptr;
        return (temp->charact_ptr);
    }
    else 
        throw std::invalid_argument("trying to assigne null Hero");
}

// =======================Character Portrait Functions=================================================

Character_Menu::CharPortrait::CharPortrait(std::string _name,Character* _charact_ptr,sf::Vector2f pos)
    :name{},charact_ptr{_charact_ptr},rect{(sf::Vector2f(PORTSIZE,PORTSIZE))}
        {
            name.setFont(getFont());
            name.setString(_name);
            name.setFillColor(sf::Color::Red);
            name.setCharacterSize(80);
            name.setOutlineThickness(2);
            name.setOutlineColor(sf::Color::Black);
            auto tmp = name.getGlobalBounds();
            name.setPosition(NAMEPOS_X-tmp.width/2,NAMEPOS_Y-tmp.height/2);
            rect.setPosition(pos);
            std::string temp{_name};
            std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            rect.setTexture(&getTexture(temp+"/Head.png"));
			rect.setOutlineColor(sf::Color::Black);
        }

bool Character_Menu::CharPortrait::isPointed(sf::RenderWindow* win_ptr)
{
    auto mousepos = sf::Mouse::getPosition(*win_ptr);
    sf::Rect<int> temp{rect.getGlobalBounds()};
    if (temp.contains(mousepos))
        return true;
    
    
    return false;
}
        
bool Character_Menu::CharPortrait::isClicked(sf::RenderWindow* win_ptr)
{
    auto mousepos = sf::Mouse::getPosition(*win_ptr);
    sf::Rect<int> temp{rect.getGlobalBounds()};
    return temp.contains(mousepos) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
