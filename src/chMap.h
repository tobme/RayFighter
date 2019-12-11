#ifndef CHMAP_H
#define CHMAP_H

//=================================  
// Constants
#define START true
#define STOPP false

//=================================  
// forward declared dependencies  

//=================================  
// included dependencies
#include "bodypart.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

class chMap 
{
//friend class Character;

public:
   enum abilities{MOVE = 0, DUCK, JUMP, KICK, PUNCH, SPECIAL};
   enum parts    {  LH = 0,    RH,   LF,   RF,  BODY,    HEAD};
   struct  s1{
      s1()
         :timer{},process{false},startingPoint{sf::Vector2f(0,0)}, part{HEAD}
         {}
      void start(parts p, sf::Vector2f v)
         {
            timer.restart();
            process = START;
            part = p;
            startingPoint = v;
         }
      float secondsElapsed() {
         return timer.getElapsedTime().asMilliseconds()/1000; 
      }
      operator bool(){
         return process;
      }
      operator sf::Vector2f(){
         return startingPoint;
      }
      s1& operator=(sf::Vector2f rhs) {
         startingPoint = rhs;
         return *this;
      }
      sf::Clock timer;
      bool process;
      sf::Vector2f startingPoint;
      parts part;
   };

   chMap();
   chMap(std::vector<std::string> textureNames);
   ~chMap();
  void clear();
   chMap operator*(const chMap &) = delete;
   
   void update();
   sf::Vector2f jumpMotion();
   sf::Vector2f duckMotion();
   sf::Vector2f kickMotion();
   sf::Vector2f punchMotion();
  
   void swap(parts left, parts right);

   parts getActiveHand();
   void keepActive(parts part_enum, abilities move); 
   parts getActiveFoot();

   void setPosition(parts, sf::Vector2f const &);
   void moveToBody(parts, float =0);
   void moveTo(parts, sf::Vector2f);
   void moveTowards(parts, sf::Vector2f);

// Access to chMap::part/ability/constants
   s1& operator[](abilities key)&;
   Bodypart& operator[](parts p)&;
   //  Bodypart& operator[](parts p)&  { return part[p].get(); };
   float& operator[](std::string s)&;
   s1& insert(abilities key);
   std::unique_ptr<Bodypart>& insert(parts key) &;
   
   bool check_collision(Bodypart* attack);
   parts get_collision(Bodypart* attack);

   sf::Vector2f dir;
   bool keep_down;
   bool right_punch;
   bool right_kick;
   sf::Vector2f old_kick_dir;
   sf::Vector2f old_punch_dir;
   sf::Vector2f old_special_dir;

  
 
private:
  void update_constants();
   
   std::map<abilities, s1> ability;
   std::map<parts, std::unique_ptr<Bodypart>> part;
   std::map<std::string, float> constants;
   int counter;
};



#endif
 
