#include "winscreen.h"
#include <iostream>

WinScreen::WinScreen(sf::Texture const winnerText,std::string n) : texture{winnerText}, shapes{}, speed{}, clock{},finishClock{},returnButton{"Return",sf::Vector2i(80,50)}, text{"Congratulations!",getFont(),50}, finish{},name{n}, counter{10},currentLetter{},letters{},charname{},anders{},albin{},tobias{},chris{},_and{},stage{0}
{
    if (name == "nanders")
    {
	name.erase(name.begin());
	name[0] = std::toupper(name[0]);
    }
    else
	name[0] = std::toupper(name[0]);

    for (int i{}; i < 20; i++)
	loadRect();
    load();
}
void WinScreen::loadPlayername()
{
    float xpos{static_cast<float>(1400/name.size()-170)};
    float ypos{500};
    int index{};
    for (char s : name)
    {
	charname.push_back(Letter{std::string(1,s),sf::Vector2f{xpos,ypos},&texture});
	if (charname.at(index).getInitPos().y < 0)
	{
	    ypos += abs(charname.at(index).getInitPos().y);
	    charname.at(index).setStartPos(sf::Vector2f{xpos, ypos});
	}

	if (charname.at(index).getInitPos().x < 0)
	{
	    xpos += abs(charname.at(index).getInitPos().x);
	    charname.at(index).setStartPos(sf::Vector2f{xpos, ypos});
	}
	else
	{
	    charname.at(index).setStartPos(sf::Vector2f{xpos, ypos});
	    xpos += abs(charname.at(index).getInitPos().x);
	}
	ypos = 500;
	xpos +=  100;


	index++;
    }
}
void WinScreen::load()
{
    anders.clear();
    albin.clear();
    tobias.clear();
    chris.clear();
    charname.clear();
    text.setPosition(500,100);
    text.setFillColor(sf::Color::Black);
    text.setString("Congratulations!");
    currentLetter = stage = 0;
    counter = 10;

    letters.emplace_back("W",sf::Vector2f{5,200},&texture);
    letters.emplace_back("i",sf::Vector2f{325,175},&texture);
    letters.push_back(Letter{"n",sf::Vector2f{400,175},&texture});
    letters.push_back(Letter{"n",sf::Vector2f{600,175},&texture});
    letters.push_back(Letter{"e",sf::Vector2f{800,300},&texture});
    letters.push_back(Letter{"r",sf::Vector2f{1100,200},&texture});

    if (name == "Anders")
    {
	loadPlayername();
	charname.push_back(Letter{"not",sf::Vector2f{50,450},&texture});
    }
    else
	loadPlayername();

    anders.push_back(Letter{"A",sf::Vector2f{10,700},&getTexture("nanders/Head.png")});
    anders.push_back(Letter{"n",sf::Vector2f{300,500},&getTexture("nanders/Head.png")});
    anders.push_back(Letter{"d",sf::Vector2f{600,500},&getTexture("nanders/Head.png")});
    anders.push_back(Letter{"e",sf::Vector2f{700,600},&getTexture("nanders/Head.png")});
    anders.push_back(Letter{"r",sf::Vector2f{1000,500},&getTexture("nanders/Head.png")});
    anders.push_back(Letter{"s",sf::Vector2f{1300,500},&getTexture("nanders/Head.png")});
    for (Letter &l : anders)
	l.setLeadPos(l.getStartPos().x,0);

    albin.push_back(Letter{"n",sf::Vector2f{1100,200},&getTexture("it/Head.png")});
    albin.push_back(Letter{"i",sf::Vector2f{1000,175},&getTexture("it/Head.png")});
    albin.push_back(Letter{"b",sf::Vector2f{850,200},&getTexture("it/Head.png")});
    albin.push_back(Letter{"t",sf::Vector2f{700,200},&getTexture("it/Head.png")});
    albin.push_back(Letter{"l",sf::Vector2f{550,200},&getTexture("it/Head.png")});
    albin.push_back(Letter{"A",sf::Vector2f{250,400},&getTexture("it/Head.png")});
    albin.push_back(Letter{"s",sf::Vector2f{150,200},&getTexture("it/Head.png")});

    tobias.push_back(Letter{"T",sf::Vector2f{1400,200},&getTexture("conan/Head.png")});
    tobias.push_back(Letter{"o",sf::Vector2f{1400,300},&getTexture("conan/Head.png")});
    tobias.push_back(Letter{"b",sf::Vector2f{1400,200},&getTexture("conan/Head.png")});
    tobias.push_back(Letter{"i",sf::Vector2f{1400,175},&getTexture("conan/Head.png")});
    tobias.push_back(Letter{"a",sf::Vector2f{1400,200},&getTexture("conan/Head.png")});
    tobias.push_back(Letter{"s",sf::Vector2f{1400,200},&getTexture("conan/Head.png")});

    chris.push_back(Letter{"C",sf::Vector2f{155,500},&getTexture("pikadorf/Head.png")});
    chris.push_back(Letter{"h",sf::Vector2f{250,500},&getTexture("pikadorf/Head.png")});
    chris.push_back(Letter{"r",sf::Vector2f{500,500},&getTexture("pikadorf/Head.png")});
    chris.push_back(Letter{"i",sf::Vector2f{700,475},&getTexture("pikadorf/Head.png")});
    chris.push_back(Letter{"dash",sf::Vector2f{1250,200},&getTexture("pikadorf/Head.png")});
    chris.push_back(Letter{"o",sf::Vector2f{200,550},&getTexture("pikadorf/Head.png")});
    chris.push_back(Letter{"f",sf::Vector2f{400,450},&getTexture("pikadorf/Head.png")});
    chris.push_back(Letter{"f",sf::Vector2f{600,450},&getTexture("pikadorf/Head.png")});
    chris.push_back(Letter{"e",sf::Vector2f{700,550},&getTexture("pikadorf/Head.png")});
    chris.push_back(Letter{"r",sf::Vector2f{1000,450},&getTexture("pikadorf/Head.png")});

    _and.push_back(Letter{"A",sf::Vector2f{300,400},&getTexture("nanders/Head.png")});
    _and.push_back(Letter{"n",sf::Vector2f{600,200},&getTexture("nanders/Head.png")});
    _and.push_back(Letter{"d",sf::Vector2f{900,200},&getTexture("nanders/Head.png")});
}

void WinScreen::update(sf::RenderWindow* window)
{
    if (clock.getElapsedTime().asMilliseconds() >= 200 && !finish)
    {

	clock.restart();
	loadRect();
	if (finishClock.getElapsedTime().asSeconds() >= 3)
	{
	    finish = true;
	    shapes.clear();
	}
    }
    else if (finish)
    {
	switch (stage)
	{
	case 0:
	    if (makefromStart(letters))
	    {
		stage++;
	    }
	    break;
	case 1:
	    erasefromEnd(letters);


	    if (makeAll(charname))
	    {
		if (makefromStart(albin))
		    stage++;
	    }
	    break;
	case 2:
	    text.setString("Made by");
	    if (albin.at(5).getPosition().x <= 500)
	    {
	      	albin.at(5).move(sf::Vector2f{5,0});
	      	albin.at(4).move(sf::Vector2f{5,0});
	      	albin.back().move(sf::Vector2f{20,7.5});
	      	albin.at(3).move(sf::Vector2f{10,7.5});		
	    }
	    if (eraseAll(charname))
		stage++;
	    break;
	case 3:
	    if (albin.size() != 2)
	    {
	     	for (unsigned int i{}; i<albin.size(); i++)
	     	{
	     	    if (i != 3 && i != 6)
	     	    {
	     		if (albin.at(0).erased())
	     		{
	     		    albin.erase(albin.begin());
	     		    albin.erase(albin.begin());
	     		    albin.erase(albin.begin());
	     		    albin.erase(albin.begin()+1);
	     		    albin.erase(albin.begin()+1);
	     		    break;
	     		}
	     		else if (!albin.at(i).erased())
	     		{
	     		    albin.at(i).eraseLetter();
	     		}
	     	    }
	     	}
	    }
	    else
	    {
		for (int i{}; i<4; i++)
		{
		    if (!chris.at(i).finished())
			chris.at(i).makeLetter();
		}

		if (static_cast<unsigned>(currentLetter) != tobias.size() && !tobias.empty())
		{		    
		    if (tobias.at(currentLetter).getPosition().x >= 100 + currentLetter * 200)
			tobias.at(currentLetter).move(sf::Vector2f{-5,0});
		   
		    if (tobias.at(currentLetter).finished() && tobias.at(currentLetter).getPosition().x <= 100 + currentLetter * 200)
			currentLetter++;
		    else if (static_cast<unsigned>(currentLetter) < tobias.size())
			tobias.at(currentLetter).makeLetter();

		}
		else if (chris.at(0).getPosition().y >= 300)
		{
		    for (int i{}; i<4; i++)
		    {
			chris.at(i).move(sf::Vector2f{0,-5});
			
		    }
		    albin.at(0).move(sf::Vector2f{0,-5});
		    albin.at(1).move(sf::Vector2f{0,-5});
		    for (Letter &l : tobias)
		    {
			l.move(sf::Vector2f{0,-5});
			l.eraseLetter();
		    }
		    
		}
		else
		{
		    tobias.clear();
		    for (unsigned int i{4}; i<chris.size(); i++)
		    {
			chris.at(i).makeLetter();
		    }
		    if (chris.back().finished())
			stage++;
		}
		break;
	    case 4:
		if (eraseAll(chris) & eraseAll(albin))
		    stage++;
		break;
	    case 5:
		for (Letter &l : anders)
		{
		    if (l.getPosition().y <= l.getStartPos().y)
			l.placeonMove(0,5);
		}
		if (anders.at(0).getPosition().y >= anders.front().getStartPos().y)
		    {
			stage++;
			break;
		    }
		break;
	    case 6:

		if (makeAll(anders) & makeAll(_and))
		    stage++;
		break;
	    default:

		if (eraseAll(anders) & eraseAll(_and))		
		     load();
		break;

	    }
	}

    }
    else
    {
	for (unsigned int i{}; i < shapes.size(); i++)
	{
	    shapes.at(i).move(speed.at(i).first,speed.at(i).second);
	}
    }

    if (returnButton.isPressed(window))
    {
	changeState(menu);
    }
}
WinScreen::Letter::Letter(std::string letter,sf::Vector2f pos, sf::Texture* text) : lead{sf::Vector2f{100,100}},startpos{pos},positions{},fileName{letter},currentPos{},speed{},traveldistance{80},texture{text},shapes{},jump{555}
{
    readFile();
    lead.setTexture(text);
    lead.setPosition(-100,700);
}
bool WinScreen::Letter::finished()
{
    if (static_cast<unsigned>(currentPos) == positions.size() - 1)
    {
	traveldistance = 80;
	return true;
    }
    return false;
}
void WinScreen::Letter::setLeadPos(float x,float y)
{
    lead.setPosition(x,y);
}
const sf::Vector2f& WinScreen::Letter::getStartPos()
{
    return startpos;
}

bool WinScreen::Letter::erased()
{
    return currentPos == -1;
}
void WinScreen::Letter::readFile()
{
    std::ifstream inFile{"letters/"+fileName+".txt"};
    if (!inFile)
	std::cout << "Failed to load file" << std::endl;
    sf::Vector2f xy;
    char getjump;
    int index{};
    while (inFile >> xy.x)
    {
	inFile >> xy.y;
	inFile.get(getjump);
	if (getjump == '!')
	    jump = index;
	    
	positions.push_back(xy);
	index++;
    }
    inFile.close();
}
void WinScreen::Letter::draw(sf::RenderWindow* window)
{
    window->draw(lead);
    for (sf::RectangleShape& s : shapes)
    {
	window->draw(s);
    }

}
void WinScreen::Letter::placeonMove(float x,float y)
{
    lead.move(x,y);
    for (sf::Vector2f &f : positions)
    {
	if (lead.getPosition() == f+startpos)   
	{
	    traveldistance = 100;
	    loadFinish();
	}
    }

}
sf::Vector2f WinScreen::Letter::negPos(sf::Vector2f const & pos1,sf::Vector2f const & pos2)
{
    return sf::Vector2f{(pos2.x+startpos.x-pos1.x)/40,(pos2.y+startpos.y-pos1.y)/40};    
}
void WinScreen::Letter::setStartPos(sf::Vector2f const pos)
{
    startpos = pos;
}
sf::Vector2f& WinScreen::Letter::getInitPos()
{
    return positions.back();
}
void WinScreen::Letter::makeLetter()
{
    if (static_cast<unsigned>(currentPos) != positions.size() - 1)
    {
	if (currentPos == 0)
	{
	    lead.setPosition(positions.at(0)+startpos);
	    currentPos++;
	    speed = negPos(lead.getPosition(),positions.at(currentPos));
	}
	else if (lead.getPosition() != positions.at(currentPos)+startpos)
	{
	    if (currentPos != jump)
		lead.move(speed);
	    else
		lead.setPosition(positions.at(currentPos)+startpos);
	}
	else
	{
	    currentPos++;
	    speed = negPos(lead.getPosition(),positions.at(currentPos));
	}
    }
    else
	traveldistance = 60;
    traveldistance += 20;
    loadFinish();
}
bool WinScreen::makeAll(std::vector<WinScreen::Letter> & letter)
{
    bool temp{true};
    for (Letter &l : letter)
    {
	l.makeLetter();
	if (!l.finished())
	    temp = false;;
    }
    return temp;
}
bool WinScreen::makefromStart(std::vector<WinScreen::Letter> & letter)
{

    for (long unsigned int i{}; i < letter.size(); i++)
    {
	if (!letter.at(i).finished())
	{
	    letter.at(i).makeLetter();
	    return false;
	}
    }
    return true;
}
bool WinScreen::makefromEnd(std::vector<WinScreen::Letter> & letter)
{
    for (int i{static_cast<int>(letter.size() - 1)}; i > 0 ; i--)
    {
	if (!letter.at(i).finished())
	{
	    letter.at(i).makeLetter();
	    return false;
	}
    }
    return true;
}
void WinScreen::Letter::eraseLetter()
{
    if (currentPos >= 0)
    {
	if (static_cast<unsigned>(currentPos) == positions.size() -1)
	{
	    currentPos--;
	    lead.setPosition(positions.at(currentPos)+startpos);
	    currentPos--;
	    speed = negPos(lead.getPosition(),positions.at(currentPos));
	}
	else if (lead.getPosition() != positions.at(currentPos)+startpos)
	{
	    if (currentPos != jump - 1)
		lead.move(speed);
	    else
		lead.setPosition(positions.at(currentPos)+startpos);
	}
	else
	{
	    currentPos--;
	    if (currentPos >= 0)
	    {
		speed = negPos(lead.getPosition(),positions.at(currentPos));
	    }
	}
    }
    traveldistance += 20;
    eraseFinish();
}
bool WinScreen::eraseAll(std::vector<WinScreen::Letter> & letter)
{
    for (auto i = letter.begin(); i!=letter.end();)
    {
	if (i->erased())
	{
	    letter.erase(i);
	}
	else
	{
	    i->eraseLetter();
	    ++i;
	}
    }
    return letter.empty();
}
bool WinScreen::erasefromEnd(std::vector<WinScreen::Letter> & letter)
{
    if (!letter.empty())
    {
	for (int i{static_cast<int>(letter.size() - 1)}; i >= 0; i--)
	{
	    if (!letter.at(i).erased())
	    {
		letter.at(i).eraseLetter();
		return false;
	    }
	    else if (!letter.empty())
	    {
		letter.erase(letter.begin()+i);
		return false;
	    }
	}
    }
    return true;
}
void WinScreen::draw(sf::RenderWindow* window)
{

    for (sf::RectangleShape& shape : shapes)
    {
	window->draw(shape);
    }

    drawhelp(letters, window);
    drawhelp(anders, window);
    drawhelp(albin, window);
    drawhelp(tobias, window);
    drawhelp(chris, window);
    drawhelp(charname,window);
    drawhelp(_and,window);

    returnButton.draw(window);

    window->draw(text);
}
void WinScreen::drawhelp(std::vector<Letter> & l, sf::RenderWindow* window)
{
    for (Letter & i : l)
    {
	i.draw(window);
    }
}
void WinScreen::Letter::loadFinish()
{
    if (traveldistance == 100)
    {
	sf::RectangleShape temp{sf::Vector2f{50,50}};
	temp.setPosition(lead.getPosition());
	temp.setTexture(texture);
	shapes.push_back(temp);
	traveldistance = 0;
    }
}
const sf::Vector2f& WinScreen::Letter::getPosition()
{
    return lead.getPosition();
}
void WinScreen::Letter::eraseFinish()
{  
    if (traveldistance == 100 && !shapes.empty())
    {
	shapes.erase(shapes.end());
	traveldistance = 0;
    }
}
void WinScreen::Letter::move(sf::Vector2f const & direction)
{
    for (sf::RectangleShape &shape : shapes)
    {
	shape.move(direction);
    }
    lead.move(direction);
    startpos += direction;
}
void WinScreen::loadRect()
{
    int const x = random(0,1400);
    int const y = random(0,800);
    int const size = random(1,5);
    int const direction = random(1,3);
    int const rotation = random(0,360);
    std::pair<int,int> tempSpeed(random(1,6),random(1,6));

    
    sf::RectangleShape temp{sf::Vector2f{static_cast<float>(50*size),static_cast<float>(50*size)}};
    temp.setPosition(x,y);
    temp.setTexture(&texture);
    temp.rotate(rotation);
    shapes.push_back(temp);


    switch (direction)
    {
    case 1:
	tempSpeed.first *= -1;
	break;
    case 2:
	tempSpeed.second *= -1;
	break;
    default:
	tempSpeed.first *= -1;
	tempSpeed.second *= -1;
	break;
    }

    speed.push_back(tempSpeed);
}
int WinScreen::random(const int low,const int high)
{
    std::random_device rnd;
    return rnd() % (high - low + 1) + low;
}
