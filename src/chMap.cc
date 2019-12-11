#include "chMap.h"
#include "helper.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace HELP_FUNC;

chMap::chMap()
  :dir{1,1}, keep_down{false}, right_punch{true}, right_kick{false},
   old_kick_dir{},old_punch_dir{},old_special_dir{}, ability{},part{}, constants{}, counter{}
{
// std::cout << "chMap() har skapats \n";
}

chMap::chMap(std::vector<std::string> textureNames)
  :dir{1,1}, keep_down{false}, right_punch{true}, right_kick{false},
   old_kick_dir{},old_punch_dir{},old_special_dir{},ability{},part{}, constants{}, counter{}
{
   textureNames.clear();
   //std::cout << "chMap(std::vector<std::string> textureNames) har skapats \n";
} 

chMap::~chMap(){
  clear();
}
void chMap::clear()
{
  ability.clear();
  part.clear();
  constants.clear();
}
void chMap::update()
{ 
   keepActive(LH, PUNCH);
   keepActive(RH, PUNCH); 
   keepActive(LF, KICK); 
   keepActive(RF, KICK);

   part[HEAD]->update(fabs(counter/2 - 278), 10);
   part[BODY]->update(counter, 5);
   part[LF]->update(fabs(counter -99)  ,  10);
   part[RF]->update(fabs(counter -163) ,  10);
   part[LH]->update(fabs(counter -37)  , 20);
   part[RH]->update(fabs(counter -257) , 20);
   update_constants();
   counter = (counter % 3600) +1;
}
sf::Vector2f chMap::jumpMotion()
{
   float elapsed = ability[JUMP].timer.getElapsedTime().asSeconds(); 
   float x = (elapsed - constants["JUMP_TIME"]/2)/(constants["JUMP_TIME"]/2); 
   float y = -powf(x,2) +1;
   sf::Vector2f start = ability[JUMP].startingPoint;

   if (elapsed > constants["JUMP_TIME"] )
   { 
      ability[JUMP].process = STOPP;
      part[BODY]->in_use  = false;
      y = 0;
   }
   
   return start + sf::Vector2f(0, -sigmoid(y))* constants["JUMP_RANGE"];
   
}

sf::Vector2f chMap::duckMotion()
{
   float elapsed = ability[DUCK].timer.getElapsedTime().asMilliseconds()/(constants["DUCK_TIME"]*1000); 
   elapsed = sigmoid(elapsed);
   part[RF]->in_use = part[LF]->in_use = true;

   if (elapsed >= 1 && !keep_down)
   {
      ability[DUCK].process = STOPP; 
      part[BODY]->in_use = part[HEAD]->in_use = false;
   }
   bool down = keep_down;
   keep_down = false;
   return (down) ? 
      sf::Vector2f(ability[DUCK].startingPoint.x,ability[JUMP].startingPoint.y)
      - sf::Vector2f(constants["DUCK_RANGE_X"], constants["DUCK_RANGE_Y"])*dir 
      :
      sf::Vector2f(ability[DUCK].startingPoint.x,ability[JUMP].startingPoint.y)
      - sf::Vector2f(elapsed*constants["DUCK_RANGE_X"], elapsed*constants["DUCK_RANGE_Y"])*dir;
}

sf::Vector2f chMap::kickMotion()
{
   float elapsed = ability[KICK].timer.getElapsedTime().asMilliseconds()/(constants["KICK_TIME"]*1000); 
   float x = sigmoid(elapsed+elapsed); // in range -1 to 1 
   float y = elapsed;//sigmoid(log10(10*elapsed + 1));//elapsed+elapsed);//log10(x*x +1));

   sf::Vector2f const start = ability[KICK].startingPoint;
   sf::Vector2f const finish{constants["KICK_RANGE_X"], constants["KICK_RANGE_Y"]};

   if ( elapsed >= 1 )
   {
      ability[KICK].process = STOPP;
      part[getActiveFoot()]->timer.restart();
   }
   
   
   return start + sf::Vector2f(x, y) * finish * old_kick_dir;
}

sf::Vector2f chMap::punchMotion()
{
   float elapsed = ability[PUNCH].timer.getElapsedTime().asMilliseconds()/(constants["PUNCH_TIME"]*1000); 
   sf::Vector2f const start = ability[PUNCH].startingPoint;
   sf::Vector2f const finish{constants["PUNCH_RANGE_X"], constants["PUNCH_RANGE_Y"]};  

   float x = elapsed+elapsed;
   float y = 0.25*elapsed*(elapsed+0.5);
   if(elapsed < constants["PUNCH_TIME"]/2 )
   { }
   else if (elapsed >= 1 )
   {
      ability[PUNCH].process = STOPP;
      part[getActiveHand()]->timer.restart();
   }
   else
   { } 
   return start + sf::Vector2f(x, y) * finish * old_punch_dir;
}
 
void chMap::swap(parts left, parts right)
{
   std::unique_ptr<Bodypart> tmp = std::move(part[left]);
   part[left] = std::move(part[right]);
   part[right] = std::move(tmp);
}

chMap::parts chMap::getActiveHand()
{
   return (right_punch) ? RH : LH;
}
chMap::parts chMap::getActiveFoot()
{
   return (right_kick) ? RF : LF;
}


void chMap::keepActive(parts p, abilities a)
{
   // Disable active hands when they are back at offset from body
   if((!ability[a] && part[p] ) && 
      ( HELP_FUNC::distance(part[p]->getCenter(), part[BODY]->getCenter() + part[p]->offset) <= 15 
        ||  part[p]->timer.getElapsedTime().asSeconds() > constants["PART_RETURN_TIME"]  ) )
   { 
      part[p]->in_use = false;
   }  
}

void chMap::setPosition(parts p, sf::Vector2f const & position)
{
    part[p]->setPosition(position);
}

void chMap::moveToBody(parts p, float divider)
{
    if ( !part[p]->in_use || part[p]->timer.getElapsedTime().asSeconds() < constants["PART_RETURN_TIME"] )
    {
       part[p]->moveTowards(part[BODY]->getCenter() + part[p]->offset, divider);
   } 
}

void chMap::moveTo(parts p, sf::Vector2f v) 
{
    part[p]->moveTo(v);
}

void chMap::moveTowards(parts p, sf::Vector2f v) 
{
    part[p]->moveTowards(v);
}


chMap::s1& chMap::operator[](abilities key)& { return ability[key];  }
Bodypart& chMap::operator[](parts p)&  { return *part[p].get(); }
//  Bodypart& chMap::operator[](parts p)&  { return part[p].get(); }
float& chMap::operator[](std::string s)& { return constants[s];  }
chMap::s1& chMap::insert(abilities key) { return ability[key]; }
std::unique_ptr<Bodypart>& chMap::insert(parts key) & { return part[key]; }



// -------------------------------------------------------------------
// ------------------- COLLISION CONTROL -----------------------------


bool chMap::check_collision(Bodypart* attack)
{
   for(int i{0};i<6;i++)
   {
      parts p = static_cast<parts>(i);
      if ( distance(attack->getCenter(), part[p]->getCenter()) < attack->radius()+attack->radius()/6 )
         return true;
   } 
   return false;
} 
 
  
chMap::parts chMap::get_collision(Bodypart* attack)
{
   for(int i{0};i<6;i++)
   {
      parts p = static_cast<parts>(i);
      if ( distance(attack->getCenter(), part[p]->getCenter()) < attack->radius()+attack->radius()/6 )
         return p;
   } 
   std::cout << "[ERROR] chMap::get_collision(Bodypart*): No collision detected\n";
   return HEAD;
}

// -------------------------------------------------------------------
// -------------------   Get CONSTANTS   -----------------------------

void chMap::update_constants()
{
  const char* const FileName = "setup.txt";
  std::ifstream file( FileName );
  if( !file  ) {
    std::cerr << "Can't open file " << FileName << std::endl;
    std::exit( -1 );
  }
  std::string key;
  while( std::getline( file, key )) {
    std::istringstream buff(key);
    float value;
    buff >> key;
    buff >> value;
    if (!( 0 < value && value < 1000 ))
      value = 1;
    constants[key] = value;
  }
  file.close();
}
