#ifndef BODYPART_H
#define BODYPART_H


//=================================  
// forward declared dependencies  

//=================================  
// included dependencies
#include <SFML/Graphics.hpp>

class Bodypart
{
public:
    Bodypart(sf::CircleShape, sf::Sprite);
    void move(sf::Vector2f const & dir);
    void draw(sf::RenderWindow* window);
    sf::Vector2f getCenter(); //returns centrum of hitbox
    void moveTowards(sf::Vector2f const & pos, float max=0);
    void moveTo(sf::Vector2f const & pos);
    void flip();
    float radius() {return hitbox.getRadius(); };
    void setPosition(sf::Vector2f const &);
   void update(int, float);
   void givePushbackEffect(const sf::Vector2f&);
    bool in_use;
    sf::Vector2f offset;
    sf::Clock timer;
   operator bool(){
      return in_use;
   }
   Bodypart* operator ->() {
      return this;
   }
   Bodypart& operator=(const bool& rhs){
      this->in_use = rhs;
      return *this;
   }
  
   
   
private: 
   sf::CircleShape hitbox;
   sf::Sprite sprite;
   int counter;
   sf::Vector2f direction;

   
};

#endif
/*Bodypart& operator=(Bodypart lhs, bool const& rhs){
      lhs.in_use = rhs;
      return lhs;
      }

 auto operator==( Bodypart lhs, bool const& rhs )
        -> bool
    {
    lhs.in_use = rhs;
    return rhs;        // Whatever.
    }
   friend
    auto operator==( const Bodypart& lhs, bool const& rhs )
        -> bool
    {
       // lhs.in_use = rhs;
    return rhs;        // Whatever.
    }
   friend bool& operator = ( bool& i, const Bodypart& foo )
      {
         i = foo.x + foo.y;
         return i;
      }
   //Bodypart& operator=(Bodypart& lhs, bool& rhs);

*/
