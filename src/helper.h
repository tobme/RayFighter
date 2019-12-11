#ifndef HELPER_H
#define HELPER_H

#ifdef _cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER

//=================================  
// Constants
#define PI 3.14159265

//=================================  
// forward declared dependencies  

//=================================  
// included dependencies
#include <SFML/Graphics.hpp>


//--------------------------------------------------------------------------
//_-------------------------HELP FUNCTIONS
  namespace HELP_FUNC {
    float sigmoid(float x);
    float distance(sf::Vector2f v, sf::Vector2f v2);
    sf::Vector2f normalize(const sf::Vector2f&);
    void GoalSeekSize(sf::Sprite & s,int sizeX, int sizeY);  

    sf::Vector2f operator *(const sf::Vector2f& left, const sf::Vector2f& right);
    sf::Vector2f operator /(const sf::Vector2f& left, const sf::Vector2f& right);
    sf::Vector2<float> operator *(const sf::Vector2<float>& left, const float& right);
    sf::Vector2<float> operator /(const sf::Vector2<float>& left, const float& right);
  }

#ifdef _cplusplus
}
#endif

#endif
