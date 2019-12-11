#include "characters.h"
#include <string>
#include "helper.h"
#include <iostream>
#include <math.h>
#include <complex>
#include <stdio.h>
using namespace HELP_FUNC;

Nanders::Nanders()
    :Character(std::vector<std::string>
			   {std::string("nanders/Foot.png"),
                std::string("nanders/Hand.png"),
                std::string("nanders/Body.png"),
                std::string("nanders/Head.png")})
{
   cMap["SPECIAL_DMG"] = 20;
   pickedSound = "Sound_effects/nanders/";
   attackSound = "Sound_effects/nanders/attack2.wav";
}

Nanders::~Nanders()
{}
void Nanders::special_attack()
{
   if( cMap[chMap::PUNCH].process || cMap[chMap::SPECIAL].process  ||
       cMap[chMap::SPECIAL].timer.getElapsedTime().asSeconds() < (cMap["SPECIAL_TIME"] + cMap["CD"]) ||
       (cMap[chMap::LH]->in_use && cMap[chMap::RH]->in_use )) 
      return;
   cMap[chMap::LH]->in_use = true;
   cMap[chMap::RH]->in_use = true;
   cMap[chMap::SPECIAL].start(chMap::HEAD, cMap[chMap::BODY]->getCenter() + cMap.dir*sf::Vector2f(35,-5));  
   cMap.old_punch_dir = cMap.dir;
}
void Nanders::specialMotion()
{
   float elapsed = cMap[chMap::SPECIAL].timer.getElapsedTime().asMilliseconds()/(cMap["SPECIAL_TIME"]*1000); 
   sf::Vector2f const start = cMap[chMap::SPECIAL].startingPoint;
   sf::Vector2f const finish{ cMap["NAND_RANGE_X"], cMap["NAND_RANGE_Y"]};  
   //1) Move ActiveHand() in spiral
   float deg = elapsed * 1080;
   float radie = (elapsed < 0.9) ? elapsed*elapsed : elapsed;
   float x = radie *cos(exp(tan(deg*PI/180)));
   float y = radie *sin(deg*PI/180);
   cMap[chMap::LH]->moveTo(start + sf::Vector2f(x, y)* finish * cMap.old_punch_dir);
    cMap[chMap::RH]->moveTo(start + sf::Vector2f(x, -y)* finish * cMap.old_punch_dir);
   if ( elapsed > 1 ) {
      cMap[chMap::SPECIAL].process = STOPP;
      cMap[ActiveHand()]->timer.restart();
   }
}
//-------------------------------------------------------------------

Conan::Conan()
   :Character(std::vector<std::string>
              {std::string("conan/Foot.png"),
                    std::string("conan/Hand.png"),
                    std::string("conan/Body.png"),
                    std::string("conan/Head.png")})
{
   cMap["SPECIAL_DMG"] = 20;
   pickedSound = "Sound_effects/conan/";
   attackSound = "Sound_effects/conan/attack2.wav";
}

Conan::~Conan()
{}
void Conan::special_attack()
{
   if( cMap[chMap::PUNCH].process || cMap[chMap::SPECIAL].process  ||
       cMap[chMap::SPECIAL].timer.getElapsedTime().asSeconds() < (cMap["SPECIAL_TIME"] + cMap["CD"]) ||
       (cMap[chMap::LH]->in_use && cMap[chMap::RH]->in_use )) 
      return;
   cMap.right_punch = !cMap.right_punch;
   cMap[ActiveHand()]->in_use = true;
   cMap[chMap::SPECIAL].start(chMap::HEAD, cMap[ActiveHand()]->getCenter());
   cMap.old_punch_dir = cMap.dir;
}
void Conan::specialMotion()
{
   float elapsed = cMap[chMap::SPECIAL].timer.getElapsedTime().asMilliseconds()/(cMap["SPECIAL_TIME"]*1000); 
   sf::Vector2f const start = cMap[chMap::SPECIAL].startingPoint;
   sf::Vector2f const finish{ cMap["CONAN_RANGE_X"], cMap["CONAN_RANGE_Y"]};  
   //1) Move ActiveHand() in spiral
   float deg = elapsed * 1080;
   float radie = (elapsed < 0.9) ? elapsed*elapsed*elapsed*elapsed : elapsed;
   float x = radie *cos(deg*PI/180);
   float y = radie *sin(deg*PI/180);
   cMap[ActiveHand()]->moveTo(start + sf::Vector2f(x, y)* finish * cMap.old_punch_dir);
   
   if ( elapsed > 1 ) {
      cMap[chMap::SPECIAL].process = STOPP;
      cMap[ActiveHand()]->timer.restart();
   }
}

//--------------------------------------------------------------
//  Pikadorf::Pikadorf()
Pikadorf::Pikadorf()
    :Character(std::vector<std::string>
			   {std::string("pikadorf/Foot.png"),
                std::string("pikadorf/Hand.png"),
                std::string("pikadorf/Body.png"),
                std::string("pikadorf/Head.png")})
{
   cMap["SPECIAL_DMG"] = 20;
   pickedSound = "Sound_effects/pikadorf/";
   attackSound = "Sound_effects/pikadorf/attack2.wav";
}

Pikadorf::~Pikadorf()
{}

void Pikadorf::special_attack() 
{
   if( cMap[chMap::PUNCH].process || cMap[chMap::SPECIAL].process  ||
       cMap[chMap::SPECIAL].timer.getElapsedTime().asSeconds() < (cMap["SPECIAL_TIME"] + cMap["CD"]) ||
       (cMap[chMap::LH]->in_use && cMap[chMap::RH]->in_use )) 
      return;
   cMap[chMap::LH]->in_use = true;
   cMap[chMap::RH]->in_use = true;
   cMap[chMap::SPECIAL].start(chMap::HEAD, cMap[chMap::BODY]->getCenter() + cMap.dir*sf::Vector2f(35,-5));  
   cMap.old_punch_dir = cMap.dir;
}

void Pikadorf::specialMotion()
{
   float elapsed = cMap[chMap::SPECIAL].timer.getElapsedTime().asMilliseconds()/(cMap["SPECIAL_TIME"]*1000); 
   sf::Vector2f const start = cMap[chMap::SPECIAL].startingPoint;
   sf::Vector2f const finish{ cMap["PIKA_RANGE_X"], cMap["PIKA_RANGE_Y"]};  
   //1) Move LH & RH to Bodycenter 
   if (elapsed < 0.8)
   {
      float x = sin(elapsed/0.6*180*PI/160);
      float y = sin(elapsed/0.6*180*PI/160);
      cMap[chMap::LH]->moveTo(start + sf::Vector2f(x, y) * cMap[chMap::LH]->offset * cMap.old_punch_dir);
      cMap[chMap::RH]->moveTo(start + sf::Vector2f(x,-y) * cMap[chMap::LH]->offset * cMap.old_punch_dir);
   }
   else {
      float x = elapsed;
      float y = sigmoid(elapsed*elapsed);
      cMap[chMap::LH]->moveTo(start + sf::Vector2f(x, y)* finish * cMap.old_punch_dir);
      cMap[chMap::RH]->moveTo(start + sf::Vector2f(x,-y)* finish * cMap.old_punch_dir);
   }
   //2) Move: LH forward and up, RH forward and down
   if ( elapsed > 1 ) {
      cMap[chMap::SPECIAL].process = STOPP;
      cMap[chMap::LH]->timer.restart();
      cMap[chMap::RH]->timer.restart();
   }

   //3) DO something extra jah
}
//--------------------------------------------------------------

Default::Default()
    :Character(std::vector<std::string>
			   {std::string("default/Foot.png"),
                std::string("default/Hand.png"),
                std::string("default/Body.png"),
                std::string("default/Head.png")})
{
   cMap["SPECIAL_DMG"] = 20;
   pickedSound = "Sound_effects/default/";
   attackSound = "Sound_effects/default/attack1.wav";
}

Default::~Default()
{}

void Default::special_attack()
{
 if( cMap[chMap::PUNCH].process || cMap[chMap::SPECIAL].process  ||
       cMap[chMap::SPECIAL].timer.getElapsedTime().asSeconds() < (cMap["SPECIAL_TIME"] + cMap["CD"]) ||
       (cMap[chMap::LH]->in_use && cMap[chMap::RH]->in_use )) 
      return;
   cMap.right_punch = !cMap.right_punch;
   cMap[ActiveHand()]->in_use = true;
   cMap[chMap::SPECIAL].start(chMap::HEAD, cMap[ActiveHand()]->getCenter());
   cMap.old_punch_dir = cMap.dir;
}
void Default::specialMotion()
{
 float elapsed = cMap[chMap::SPECIAL].timer.getElapsedTime().asMilliseconds()/(cMap["SPECIAL_TIME"]*1000); 
   sf::Vector2f const start = cMap[chMap::SPECIAL].startingPoint;
   sf::Vector2f const finish{ cMap["DEFAULT_RANGE_X"], cMap["DEFAULT_RANGE_Y"]};  
   //1) Move ActiveHand() in spiral
   float deg = elapsed * 1080;
   float radie = (elapsed < 0.9) ? elapsed*elapsed*elapsed*elapsed : elapsed;
   float x = radie *cos(deg*PI/180);
   float y = radie *sin(deg*PI/180);
   cMap[ActiveHand()]->moveTo(start + sf::Vector2f(x, y)* finish * cMap.old_punch_dir);
   
   if ( elapsed > 1 ) {
      cMap[chMap::SPECIAL].process = STOPP;
      cMap[ActiveHand()]->timer.restart();
   }
}
//--------------------------------------------------------------

It::It()
    :Character(std::vector<std::string>
			   {std::string("it/it.png"),
                std::string("it/it.png"),
                std::string("it/it.png"),
                std::string("it/it.png")})
{
	cMap["SPECIAL_DMG"] = 20;
   pickedSound = "Sound_effects/it/";
   attackSound = "Sound_effects/it/attack1.wav";
}

It::~It()
{}

void It::special_attack()
{
  if( cMap[chMap::PUNCH].process || cMap[chMap::SPECIAL].process  ||
       cMap[chMap::SPECIAL].timer.getElapsedTime().asSeconds() < (cMap["SPECIAL_TIME"] + cMap["CD"]) ||
       (cMap[chMap::LH]->in_use && cMap[chMap::RH]->in_use )) 
      return;
   cMap.right_punch = !cMap.right_punch;
   cMap[ActiveHand()]->in_use = true;
   cMap[chMap::SPECIAL].start(chMap::HEAD, cMap[ActiveHand()]->getCenter()+sf::Vector2f(40,0)*cMap.dir);
   cMap.old_punch_dir = cMap.dir;
}
void It::specialMotion()
{
   float elapsed = cMap[chMap::SPECIAL].timer.getElapsedTime().asMilliseconds()/(cMap["SPECIAL_TIME"]*1000); 
   sf::Vector2f const start = cMap[chMap::SPECIAL].startingPoint;
   sf::Vector2f const finish{ cMap["IT_RANGE_X"], cMap["IT_RANGE_Y"]};  
   //1) Move ActiveHand() in spiral
   float deg = elapsed * 1080;
   float radie = elapsed;
   float x = radie *cos(deg*PI/180);
   float y = radie *sin(deg*PI/180);
   cMap[ActiveHand()]->moveTo(start + sf::Vector2f(x, y)* finish * cMap.old_punch_dir);
   
   if ( elapsed > 1 ) {
      cMap[chMap::SPECIAL].process = STOPP;
      cMap[ActiveHand()]->timer.restart();
   }
}
//--------------------------------------------------------------

Saitama::Saitama()
    :Character(std::vector<std::string>
			   {std::string("saitama/Foot.png"),
                std::string("saitama/Hand.png"),
                std::string("saitama/Body.png"),
                std::string("saitama/Head.png")})
{
    cMap["SPECIAL_DMG"] = 100;
   pickedSound = "Sound_effects/saitama/";
   attackSound = "Sound_effects/saitama/attack1.wav";
}

Saitama::~Saitama()
{}

void Saitama::special_attack()
{
   if( cMap[chMap::PUNCH].process || cMap[chMap::SPECIAL].process  ||
       cMap[chMap::SPECIAL].timer.getElapsedTime().asSeconds() < (cMap["SPECIAL_TIME"] + cMap["CD"]) ||
       (cMap[chMap::LH]->in_use && cMap[chMap::RH]->in_use )) 
      return;
   cMap.right_punch = !cMap.right_punch;
   cMap[ActiveHand()]->in_use = true;
   cMap[chMap::SPECIAL].start(chMap::HEAD, cMap[ActiveHand()]->getCenter());
   cMap.old_punch_dir = cMap.dir;
}
void Saitama::specialMotion()
{
 float elapsed = cMap[chMap::SPECIAL].timer.getElapsedTime().asMilliseconds()/(cMap["SPECIAL_TIME"]*1000); 
   sf::Vector2f const start = cMap[chMap::SPECIAL].startingPoint;
   sf::Vector2f const finish{ cMap["SAITIMA_RANGE_X"], cMap["SAITIMA_RANGE_Y"]};  
   //1) Move ActiveHand() in spiral
   float deg = elapsed * 1080;
   float radie = (elapsed < 0.9) ? elapsed*elapsed*elapsed*elapsed : elapsed;
   float x = radie *cos(deg*PI/180);
   float y = radie *sin(deg*PI/180);
   cMap[ActiveHand()]->moveTo(start + sf::Vector2f(x, y)* finish * cMap.old_punch_dir);
   
   if ( elapsed > 1 ) {
      cMap[chMap::SPECIAL].process = STOPP;
      cMap[ActiveHand()]->timer.restart();
   }
}
