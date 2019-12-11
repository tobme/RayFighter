#include "bodypart.h"
#include "helper.h"
#include "chMap.h"
#include <math.h>
#include <iostream>



Bodypart::Bodypart(sf::CircleShape box, sf::Sprite sprit) 
   : in_use{false}, offset{}, timer{}, hitbox{box}, sprite{sprit}, counter{182}, direction{}
{}

void Bodypart::move(sf::Vector2f const & dir)
{
   hitbox.move(dir);
   auto spriteS = sprite.getGlobalBounds();
   if ( sprite.getScale().x > 0 )
       sprite.setPosition(getCenter() - sf::Vector2f(spriteS.width/2, spriteS.height/2));
   else
       sprite.setPosition(sf::Vector2f( spriteS.width/2 + getCenter().x, getCenter().y - spriteS.height/2 ));
}

void Bodypart::draw(sf::RenderWindow* window)
{
   window->draw(sprite);
   //window->draw(hitbox);
}

sf::Vector2f Bodypart::getCenter() 
{return sf::Vector2f(hitbox.getPosition().x + hitbox.getRadius(),hitbox.getPosition().y + hitbox.getRadius());}

void Bodypart::moveTowards(sf::Vector2f const & pos, float max)
{
   sf::Vector2f diff = (pos - getCenter());
   float speed = sqrt(powf(diff.x,2) + powf(diff.y,2));
   if ( max != 0 ) {
      diff = diff / max;
   }
   else {
      if ( speed >= 2 ){
         diff = diff / 7.f; //(speed > 0.1) ? diff / 4.f : diff / 8.f;
      }else if (speed >= 1.5) 
         diff = diff / 6.f;
      else if (speed >= 1)
         diff = diff / 5.f;
      else if (speed >= 0.6)
         diff = diff / 4.f;
      else if (speed >= 0.4)
         diff = diff / 3.f;
      else 
         diff = diff / 2.f;
   }

   move(diff); 
}

// Move distance pos from center of *this
void Bodypart::moveTo(sf::Vector2f const & pos)
{ move((pos - sf::Vector2f(hitbox.getRadius(), hitbox.getRadius()) - getCenter())); }

 void Bodypart::flip()
{
	sprite.scale(-1,1);
	offset.x = offset.x * -1;
}

void Bodypart::setPosition(sf::Vector2f const & position)
{
    hitbox.setPosition(position);
    if ( sprite.getScale().x > 0 )
        sprite.setPosition(getCenter() - sf::Vector2f(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2));
    else
        sprite.setPosition( sf::Vector2f(sprite.getGlobalBounds().width/2 + getCenter().x, getCenter().y - sprite.getGlobalBounds().height/2));
}

void Bodypart::update(int idle_counter, float idle_range)
{
////////////////////////////////////
// Speed & range of pushback effect
   float range = 15;
   float speed = 8; 
////////////////////////////////////
   if ( ! (90 < counter && counter < 270 ) ) {
      float degrees = counter;
      float x = (range*cos(degrees*PI/180)/(1+powf(sin(degrees*PI/180), 2)));
      float y = (range*sin(degrees*PI/180)*cos(degrees*PI/180)) / (1+powf(sin(degrees*PI/180),2));
      //Set direction of pushback
      x = (direction.x > 0) ? -x : x;
      y = (direction.y > 0) ?  y :-y;
      hitbox.setOrigin(x,y);
      sprite.setOrigin(x,y);
      counter = (counter % 360) + speed;
   } 
   else if (!in_use && idle_counter != 0) {
      idle_counter = (idle_counter % 360);
      float degrees = idle_counter;
/*
      float x = (idle_range*cos(degrees*PI/180)/(1+powf(sin(degrees*PI/180), 2)));
      float y = (idle_range*sin(x*PI/180)*cos(x*PI/180)) / (1+powf(sin(x*PI/180),2));*/
      float x = idle_range*sin(2*degrees*PI/180);
      float y = idle_range*sin(3*x*PI/180);
      hitbox.setOrigin(x,y);
      sprite.setOrigin(x,y);
   }  
}

void Bodypart::givePushbackEffect(const sf::Vector2f& dir )
{
   direction = dir;
   counter = 270;
}
