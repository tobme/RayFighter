
#ifndef WINSCREEN_H
#define WINSCREEN_H
#include "library.h"
#include "game_state.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "button.h"
#include <random>
#include <fstream>
#include <math.h>
#include <stdlib.h>

class WinScreen : public Game_State, public The_font, public Texture_lib
{
public:
    WinScreen(sf::Texture const winnerText, std::string n);
   ~WinScreen() {
      letters.clear();
      charname.clear();
      anders.clear();
      tobias.clear();
      chris.clear();
      _and.clear();
      shapes.clear();
      speed.clear();
   }
    void update(sf::RenderWindow* window);
    void draw(sf::RenderWindow* window);

private:
    void loadRect();
    void load();
    void loadPlayername();

    int random(const int low,const int high);
    sf::Texture texture;
    std::vector<sf::RectangleShape> shapes;
    std::vector<std::pair<int,int>> speed;
    sf::Clock clock;
    sf::Clock finishClock;
    Button returnButton;
    sf::Text text;
    bool finish;
    std::string name;
    int counter;
    class Letter
    {
    public:
	Letter(std::string letter,sf::Vector2f pos, sf::Texture* text);
       ~Letter() {
          shapes.clear();
       }
	Letter(Letter const &) = default;
	Letter& operator=(Letter const &) = default;
	void makeLetter();
	void eraseLetter();
	void readFile();
	void loadFinish();
	void eraseFinish();
	void setStartPos(sf::Vector2f const pos);
	void setLeadPos(float x,float y);
	const sf::Vector2f& getStartPos();
	void placeonMove(float x, float y);
	sf::Vector2f& getInitPos();


	sf::Vector2f negPos(sf::Vector2f const & pos1,sf::Vector2f const & pos2);
	void draw(sf::RenderWindow* window);
	bool finished();
	bool erased();
	void move(sf::Vector2f const & direction);
	const sf::Vector2f& getPosition();

	sf::RectangleShape lead;
	sf::Vector2f startpos;
	std::vector<sf::Vector2f> positions;
	std::string fileName;
	int currentPos;
	sf::Vector2f speed;
	int traveldistance;
	sf::Texture* texture;
	std::vector<sf::RectangleShape> shapes;
	int jump;
    };
    int currentLetter;
    std::vector<Letter> letters;
    std::vector<Letter> charname;
    std::vector<Letter> anders;
    std::vector<Letter> albin;
    std::vector<Letter> tobias;
    std::vector<Letter> chris;
    std::vector<Letter> _and;
    int stage;
    void drawhelp(std::vector<Letter> & l, sf::RenderWindow* window);
    bool makefromStart(std::vector<WinScreen::Letter> & letter);
    bool makefromEnd(std::vector<WinScreen::Letter> & letter);
    bool erasefromEnd(std::vector<WinScreen::Letter> & letter);
    bool makeAll(std::vector<WinScreen::Letter> & letter);
    bool eraseAll(std::vector<WinScreen::Letter> & letter);
};
#endif
