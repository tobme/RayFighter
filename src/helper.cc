#include "helper.h"
#include <math.h>
 
//--------------------------------------------------------------------------
//_-------------------------HELP FUNCTIONS

namespace HELP_FUNC {
   float sigmoid(float x)
   {
      if (x >= 1) 
         x = 1;
      else if (x <= -1) 
         x = -1;
      return x;
   }

   float distance(sf::Vector2f v, sf::Vector2f v2)
   {
      float x_distance = (v2.x - v.x);
      float y_distance = (v.y - v2.y);
      return fabs(sqrt(powf(x_distance, 2) + powf(y_distance, 2)));
   }

     sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
   }

void GoalSeekSize(sf::Sprite & s,int sizeX, int sizeY)
{
float x = 0.1;
s.setScale(x,1);
   while(s.getGlobalBounds().width < sizeX)
   {
       s.setScale(x,1);
       x += 0.1;
   }
   float y = 0.1;
   s.setScale(x,y);
   while(s.getGlobalBounds().height < sizeY)
   {
       s.setScale(x,y);
       y += 0.1;
   }
}
////////////////////////////////////////////////////////////
/// \brief Multiply 2 Vectors
///
/// \param left  Left operand (a vector) 
/// \param right Right operand (a vector)
///
/// \return (A Multiplied Vector)
///
////////////////////////////////////////////////////////////
   //  template <typename T>
   sf::Vector2f operator *(const sf::Vector2f& left, const sf::Vector2f& right)
   {
      float X = left.x * right.x;
      float Y = left.y * right.y;
      return sf::Vector2f(X,Y);
   }
////////////////////////////////////////////////////////////
/// \brief Divide 2 Vectors
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return (A Divided Vector)
///
////////////////////////////////////////////////////////////
//   template <typename T>
   sf::Vector2f operator /(const sf::Vector2f& left, const sf::Vector2f& right)
   {
      float X = left.x / right.x;
      float Y = left.y / right.y;
      return sf::Vector2f(X,Y);
   }

//FLoat 
   sf::Vector2<float> operator *(const sf::Vector2<float>& left, const float& right)
   {
      float X = left.x * right;
      float Y = left.y * right;
      return sf::Vector2<float>(X,Y);
   }

//Float
   sf::Vector2<float> operator /(const sf::Vector2<float>& left, const float& right)
   {
      float X = left.x / right;
      float Y = left.y / right;
      return sf::Vector2<float>(X,Y);
   }
}
//----------------------------END HELP FUNCTIONS -----------------------------

