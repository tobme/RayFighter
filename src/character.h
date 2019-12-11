#ifndef CHARACTER_H
#define CHARACTER_H

//=================================  
// forward declared dependencies  

//=================================  
// included dependencies
#include "chMap.h"
#include "library.h"
#include <string>
#include <SFML/Graphics.hpp>

  
class Character : protected Texture_lib, protected Sound_lib
{
public: 
   Character(std::vector<std::string> textureNames);
   virtual ~Character();

   void draw(sf::RenderWindow* window);
   void update();
   void reset() { hp = 100; };
   float get_hp() const { return hp; };
   void check_collision(Character& opponent); 

   void move(bool const _right);
   void duck();
   void jump();
   void kick();
   void punch(); 
   virtual void special_attack() = 0;
   
   void move_tourHead(float x,float y);
   void set_tourHead(sf::Vector2f const & position);
   sf::RectangleShape& get_tourHead();
   std::string get_pickedSound();

   std::string& get_name() { return name; }
   void setSide(bool left);
   void setPosition(sf::Vector2f const &,bool);
  
protected:
   virtual void specialMotion() = 0;
   chMap::parts ActiveHand() {return cMap.getActiveHand(); };
   chMap::parts ActiveFoot() {return cMap.getActiveFoot(); };
   std::string attackSound,pickedSound;
   chMap cMap;
private:
   
  float hp;
  float acceleration;
  int counter;
  std::string name;
  sf::RectangleShape tourHead; 

  void moveBody(sf::Vector2f);
  void moveHead(sf::Vector2f);
  void moveFeets(sf::Vector2f);
  void moveHands(sf::Vector2f);
  void moveAll(sf::Vector2f);
   
  void checkWithAbility(Character& opponent, chMap::abilities, chMap::parts);
  void setDirection(bool le);
  bool checkWithAbilityCaseHandler(chMap::parts, chMap::abilities, Character&, chMap::parts);
};

#endif
