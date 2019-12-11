#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "character.h"

class Nanders : public Character
{
public:
   Nanders();
   ~Nanders();
   void special_attack() override;
   void specialMotion() override;
};

class Conan : public Character
{
public:
   Conan();
   ~Conan();
   void special_attack() override;
   void specialMotion() override;
};

class Pikadorf : public Character
{
public:
   Pikadorf();
   ~Pikadorf();
   void special_attack() override;
   void specialMotion() override;
};

class Default : public Character
{
public:
   Default();
   ~Default();
   void special_attack() override;
   void specialMotion() override;
};

class Saitama : public Character
{
public:
   Saitama();
   ~Saitama();
   void special_attack() override;
   void specialMotion() override;
};

class It : public Character
{
public:
   It();
   ~It();
   void special_attack() override;
   void specialMotion() override;
};
#endif
