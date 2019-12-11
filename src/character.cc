#include "character.h"
#include "helper.h"
#include <iostream>
#include <sstream>
#include <exception>

using namespace HELP_FUNC;

Character::Character(std::vector<std::string> textureNames) 
    : attackSound{"null"},pickedSound{"null"},cMap(), hp{100}, acceleration{}, counter{}, name{textureNames.front()},tourHead{sf::Vector2f{50,50}}
{ 
    std::stringstream ss;
    ss << name;
    std::getline(ss,name,'/');

    tourHead.setTexture(&getTexture(textureNames.at(3)));
    tourHead.setOrigin(15,0);
   
   sf::Sprite foot{getTexture(textureNames.at(0))};
   sf::CircleShape footbox{30.0f};
   footbox.setFillColor(sf::Color::Magenta);
   sf::Sprite foot2{getTexture(textureNames.at(0))};
   sf::CircleShape footbox2{30.0f};
   footbox2.setFillColor(sf::Color::Magenta);
 
   sf::Sprite hand{getTexture(textureNames.at(1))};
   sf::CircleShape handbox{30.0f};
   handbox.setFillColor(sf::Color::Green);
   sf::Sprite hand2{getTexture(textureNames.at(1))};
   sf::CircleShape handbox2{30.0f};
   handbox2.setFillColor(sf::Color::Green);
    
   sf::Sprite torso{getTexture(textureNames.at(2))};
   sf::CircleShape torsobox{40.0f};
   torsobox.setFillColor(sf::Color::Red);  
   sf::Sprite head{getTexture(textureNames.at(3))};
   sf::CircleShape headbox{35.0f};
   headbox.setFillColor(sf::Color::Red);

   
   GoalSeekSize(hand , 40, 40);
   GoalSeekSize(hand2, 40, 40);
   GoalSeekSize(foot , 40, 45);
   GoalSeekSize(foot2, 40, 45);
   GoalSeekSize(torso, 70, 100);
   GoalSeekSize(head , 60, 70);
   
   
   //Skapa BodychMap::parts - Push_back order is important
   cMap.insert(chMap::LH) = {(std::make_unique<Bodypart>(handbox,hand))};
   cMap.insert(chMap::RH) = (std::make_unique<Bodypart>(handbox2,hand2));
   cMap.insert(chMap::LF) = (std::make_unique<Bodypart>(footbox,foot));
   cMap.insert(chMap::RF) = (std::make_unique<Bodypart>(footbox2,foot2));
   cMap.insert(chMap::BODY) = (std::make_unique<Bodypart>(torsobox,torso));
   cMap.insert(chMap::HEAD) = (std::make_unique<Bodypart>(headbox,head));
   
   // Assign BodychMap::parts
   sf::Vector2f startPos{400,580};
   for(int i{0};i<6;i++)
   {
      chMap::parts p = static_cast<chMap::parts>(i);
      cMap[p]->moveTo(startPos);
   }
   cMap[chMap::JUMP] = startPos;

   //Set bodyparts offset to center of body
   auto bodySize = torso.getGlobalBounds();
   cMap[chMap::LH]->offset = sf::Vector2f(-hand.getGlobalBounds().width,                 -bodySize.height/4);
   cMap[chMap::RH]->offset = sf::Vector2f(bodySize.width -hand.getGlobalBounds().width/2,                                 -bodySize.height/4);
   cMap[chMap::LF]->offset = sf::Vector2f(-foot.getGlobalBounds().width/2,                 bodySize.height/2 + foot.getGlobalBounds().height);
   cMap[chMap::RF]->offset = sf::Vector2f(foot.getGlobalBounds().width,                  bodySize.height/2 + foot.getGlobalBounds().height);
   cMap[chMap::BODY]->offset = sf::Vector2f(0,0);
   cMap[chMap::HEAD]->offset = sf::Vector2f(bodySize.width/8,                            -bodySize.height/4 - head.getGlobalBounds().height);

   cMap["RF_Y_OFFSET"] = cMap[chMap::RF]->offset.y;
   cMap["LF_Y_OFFSET"] = cMap[chMap::LF]->offset.y;
   

} 

Character::~Character() {
  cMap.clear();
}
void Character::draw(sf::RenderWindow* window)
{
   //Draw order is important
	if(cMap.dir.x > 0)
	{
		cMap[chMap::RH]->draw(window);
		cMap[chMap::RF]->draw(window); 
		cMap[chMap::BODY]->draw(window);
		cMap[chMap::HEAD]->draw(window);
		cMap[chMap::LF]->draw(window); 
		cMap[chMap::LH]->draw(window); 
	}
	else
	{
		cMap[chMap::LH]->draw(window); 
		cMap[chMap::LF]->draw(window); 
		cMap[chMap::BODY]->draw(window);
		cMap[chMap::HEAD]->draw(window);
		cMap[chMap::RF]->draw(window); 
		cMap[chMap::RH]->draw(window);
	}
}

// Only move Body, rest of the bodyparts will follow 
void Character::update()
{
   float speedx{};
   float speedy{};
   sf::Vector2f v = sf::Vector2f(0,0);
   cMap.update(); 
   
   // Jump, Duck or Slow
   if( cMap[chMap::JUMP] )
   {
      v = cMap.jumpMotion();
      v.x = cMap[chMap::BODY]->getCenter().x;
      cMap[chMap::BODY]->moveTowards(v); 
      cMap.dir.y = 1;
   } else if ( cMap[chMap::DUCK] )
   {
      v = cMap.duckMotion();
      if ( !cMap.keep_down )
         cMap.moveTowards(chMap::BODY, v);
      v.y -= 40;
      cMap.moveTowards(chMap::HEAD, v);
   } else 
   { //Move body to LINE 
      v = cMap[chMap::JUMP];
      v.x = cMap[chMap::BODY]->getCenter().x;
      cMap.moveTowards(chMap::BODY, v);
      cMap.dir.y = -1;
   }

   // Move right or left
   if ( cMap[chMap::MOVE] )
   { 
      speedx =  (acceleration*cMap["MAX_SPEED"]);
      cMap[chMap::MOVE].process = STOPP;
      cMap[chMap::RF]->offset.y =  cMap["RF_Y_OFFSET"] + (counter % 20) - 10;
      cMap[chMap::LF]->offset.y =  cMap["LF_Y_OFFSET"] + ((counter -45) % 20) -10;
   }
   else  { // apply friction/slow
      speedx = 0;
   } 

   // Kick and punch or special attack 
   if ( cMap[chMap::KICK] ) { 
       v = cMap.kickMotion();
       cMap[ActiveFoot()]->moveTo(v);
   }
   if ( cMap[chMap::PUNCH] ){
       v = cMap.punchMotion();
       cMap[ActiveHand()]->moveTo(v);
   }
   if ( cMap[chMap::SPECIAL] ) {
   //Special attack; Very gut jah
      specialMotion();
   }

      //Follow body position
   cMap.moveToBody(chMap::LH, 5); 
   cMap.moveToBody(chMap::RH, 5);
   cMap.moveToBody(chMap::LF, 3);
   cMap.moveToBody(chMap::RF, 3);
   cMap.moveToBody(chMap::HEAD, 6);
   moveBody(sf::Vector2f(speedx, speedy)*cMap["MAX_SPEED"]);

   counter++;
}


void Character::setSide(bool left)
{
    if(!left) { moveAll(sf::Vector2f(400,0));}
    setDirection(left);
}


void Character::setPosition(sf::Vector2f const & position,bool left)
{
    setDirection(left);
    cMap.setPosition(chMap::BODY,position);
    cMap.setPosition(chMap::LH,position);
    cMap.setPosition(chMap::RH,position);
    cMap.setPosition(chMap::LF,position);
    cMap.setPosition(chMap::RF,position);
    cMap.setPosition(chMap::HEAD,position);
    //update();
    for( int i{0};i!=15;i++)
    {
        cMap.moveToBody(chMap::LH); 
        cMap.moveToBody(chMap::RH);
        cMap.moveToBody(chMap::LF);
        cMap.moveToBody(chMap::RF);
        cMap.moveToBody(chMap::HEAD);
    }

}
//--------------------------------------------------------------------
//-------------------- functions 
void Character::move(bool const _right)
{
    if ( cMap[chMap::MOVE] ) return; 
    float x = acceleration;
    if (_right) 
        x = (x > 0.2) ? (x + cMap["ACC_STEP"]) : 0.2; 
    else
        x = (x < -0.2) ? (x - cMap["ACC_STEP"]) :-0.2;
    
    acceleration = sigmoid(x);
    cMap[chMap::MOVE].process = START;
}

void Character::duck() 
{ 
   if ( cMap[chMap::JUMP].secondsElapsed() < (cMap["JUMP_TIME"] + 0.15)) 
      return; //Prevents hanging feets after jump 
   if ( cMap[chMap::DUCK]) 
   {
      cMap.keep_down = true;
   }
   if(cMap[chMap::DUCK] || cMap[chMap::JUMP] || cMap[chMap::SPECIAL] ) return;
   cMap[chMap::DUCK].start(chMap::BODY, cMap[chMap::BODY]->getCenter() );
   cMap[chMap::BODY]->in_use = cMap[chMap::HEAD]->in_use = cMap[chMap::RF]->in_use = cMap[chMap::LF]->in_use = true;
} 
 
void Character::jump()
{
   if(cMap[chMap::DUCK] || cMap[chMap::JUMP] || cMap[chMap::SPECIAL] ) return;
   if( cMap[chMap::JUMP].secondsElapsed() < (cMap["JUMP_TIME"] + cMap["CD_JUMP"])) return;
   cMap[chMap::JUMP].start(chMap::BODY, cMap[chMap::JUMP].startingPoint);
   cMap[chMap::BODY]->in_use  = true;
}

void Character::kick()
{
   if( cMap[chMap::KICK] || cMap[chMap::DUCK] || cMap[chMap::SPECIAL] ) return;
   if( cMap[chMap::KICK].secondsElapsed() < (cMap["KICK_TIME"] + cMap["CD"])) return;
   if ( cMap.right_kick )
   {
       if( cMap[chMap::LF] ) return; 
       cMap[chMap::LF] = true;
   }
   else 
   {
       if ( cMap[chMap::RF] ) return;
       cMap[chMap::RF] = true;
   }
   if(attackSound != "null")playSoundRP(attackSound);
   cMap.right_kick = !cMap.right_kick;
   cMap[chMap::KICK].start(ActiveFoot(), cMap[ActiveFoot()]->getCenter() );
   cMap.old_kick_dir = cMap.dir;
} 

void Character::punch() 
{
    if( cMap[chMap::PUNCH] || cMap[chMap::SPECIAL] ) return;
    if( cMap[chMap::PUNCH].secondsElapsed() < (cMap["PUNCH_TIME"] + cMap["CD"])) return;
    if ( cMap.right_punch )
    {
        if( cMap[chMap::LH] ) return;
        cMap[chMap::LH] = true;
    }
    else
    {
        if ( cMap[chMap::RH] ) return;
        cMap[chMap::RH] = true;
    }
    if(attackSound != "null")playSoundRP(attackSound);
    cMap.right_punch = !cMap.right_punch;
    cMap[chMap::PUNCH].start(ActiveHand(), cMap[ActiveHand()]->getCenter() );  
    cMap.old_punch_dir = cMap.dir;
   
}


// -------------------------------------------------------------------
// ----------------------- PRIVATE -----------------------------------
void Character::moveBody(sf::Vector2f v)
{
    cMap[chMap::BODY]->move(v);
}

void Character::moveHead(sf::Vector2f v)
{
     cMap[chMap::HEAD]->move(v);
}

void Character::moveFeets(sf::Vector2f v)
{
    cMap[chMap::LF]->move(v);
    cMap[chMap::RF]->move(v);
}

void Character::moveHands(sf::Vector2f v)
{
    cMap[chMap::LH]->move(v);
    cMap[chMap::RH]->move(v);
}

void Character::moveAll(sf::Vector2f v)
{    // Move all bodychMap::parts 
   moveBody(v);
   moveHead(v);
   moveFeets(v);
   moveHands(v);
}

void Character::set_tourHead(sf::Vector2f const & position)
{
    tourHead.setPosition(position);
}
sf::RectangleShape& Character::get_tourHead()
{
    return tourHead;
}
std::string Character::get_pickedSound()
{
	return pickedSound;
}
void Character::move_tourHead(float x,float y)
{
    tourHead.move(x,y);
}


bool Character::checkWithAbilityCaseHandler( chMap::parts got_hit, chMap::abilities ability, Character& opponent , chMap::parts p)
{
   bool kill_AbilityProcess = true;
   chMap::parts activePart = ( ability == chMap::KICK ) ? ActiveFoot() : ActiveHand();
   //ability Hits ability
   if (activePart == got_hit && cMap[ability].process  ) {
      cMap[ability].process = STOPP;
      cMap[got_hit]->timer.restart();
   }
    // ability hits idle got_hit
   else if ( cMap[chMap::DUCK] ){
      kill_AbilityProcess = false;
   }
   // ability hits got_hit in defence 
   else{
      cMap[got_hit]->givePushbackEffect(cMap[got_hit]->getCenter() - opponent.cMap[p]->getCenter() );
   } 
   return kill_AbilityProcess;
}

// -------------------------------------------------------------------
// ------------------- COLLISION CONTROL -----------------------------

void Character::checkWithAbility(Character& opponent, chMap::abilities a, chMap::parts p)
{
   //Check if process [a] is running
   if ( opponent.cMap[a] )
   {  
      //Check if part [p] has collided 
      if ( cMap.check_collision( &opponent.cMap[p]) )
      {
		  playSoundRP("Sound_effects/hit.wav",100);
         chMap::parts got_hit = cMap.get_collision( &opponent.cMap[p] );
         /*
           Kanske starta en process som gradvis ändrar Origin för att ge en push back effekt
         */
         bool kill_AbilityProcess = true;
         switch (got_hit){ 
         case chMap::LF:
            kill_AbilityProcess = checkWithAbilityCaseHandler(got_hit, chMap::KICK, opponent,p);break;
         case chMap::RF:
            kill_AbilityProcess = checkWithAbilityCaseHandler(got_hit, chMap::KICK, opponent,p);break;
         case chMap::LH:
            kill_AbilityProcess = checkWithAbilityCaseHandler(got_hit, chMap::PUNCH, opponent,p);
            kill_AbilityProcess = checkWithAbilityCaseHandler(got_hit, chMap::SPECIAL, opponent,p);
            break;
         case chMap::RH:
            kill_AbilityProcess = checkWithAbilityCaseHandler(got_hit, chMap::PUNCH, opponent,p);
            kill_AbilityProcess = checkWithAbilityCaseHandler(got_hit, chMap::SPECIAL, opponent,p);
            break;

         case chMap::HEAD:
            if ( a == chMap::SPECIAL ) {
               switch(p){
               case chMap::LF: hp -=opponent.cMap["HEAD_KICK_DMG"];  break;
               case chMap::RF: hp -=opponent.cMap["HEAD_KICK_DMG"];  break;
               case chMap::LH: hp -=opponent.cMap["SPECIAL_DMG"];    break; 
               case chMap::RH: hp -=opponent.cMap["SPECIAL_DMG"];    break;
               default: throw std::logic_error( "[ERROR] Character::checkWithAbility code: 12");
               };

            }else{
               switch(p){
            case chMap::LF: hp -=opponent.cMap["HEAD_KICK_DMG"];  break;
            case chMap::RF: hp -=opponent.cMap["HEAD_KICK_DMG"];  break;
            case chMap::LH: hp -=opponent.cMap["HEAD_PUNCH_DMG"]; break; 
            case chMap::RH: hp -=opponent.cMap["HEAD_PUNCH_DMG"]; break;
            default: throw std::logic_error( "[ERROR] Character::checkWithAbility code: 13");
            };
            }
            
            cMap[got_hit]->givePushbackEffect(cMap[got_hit]->getCenter() - opponent.cMap[p]->getCenter() );
            break;

         case chMap::BODY:
            if ( a == chMap::SPECIAL ) {
               switch(p){
               case chMap::LF: hp -=opponent.cMap["BODY_KICK_DMG"];break;
               case chMap::RF: hp -=opponent.cMap["BODY_KICK_DMG"];break;
               case chMap::LH: hp -=opponent.cMap["SPECIAL_DMG"];  break; 
               case chMap::RH: hp -=opponent.cMap["SPECIAL_DMG"];  break;
               default: throw std::logic_error( "[ERROR] Character::checkWithAbility code: 14");
               };

            }else{
               switch(p){
               case chMap::LF: hp -=opponent.cMap["BODY_KICK_DMG"];  break;
               case chMap::RF: hp -=opponent.cMap["BODY_KICK_DMG"];  break;
               case chMap::LH: hp -=opponent.cMap["BODY_PUNCH_DMG"]; break; 
               case chMap::RH: hp -=opponent.cMap["BODY_PUNCH_DMG"]; break;
               default: throw std::logic_error( "[ERROR] Character::checkWithAbility code: 15");
               };
            }
            cMap[got_hit]->givePushbackEffect(cMap[got_hit]->getCenter() - opponent.cMap[p]->getCenter() );
            break;
         default:
            hp = hp;
         };

         if ( kill_AbilityProcess ) {
            opponent.cMap[p]->timer.restart();
            opponent.cMap[a].process = STOPP;
         }
      }
   }
 
}

void Character::check_collision(Character& opponent) 
{
   // Set direction in *this 
   setDirection(cMap[chMap::BODY]->getCenter().x - opponent.cMap[chMap::BODY]->getCenter().x < 0 );
//Check if opponents ability hits *this
    checkWithAbility(opponent, chMap::KICK, opponent.ActiveFoot()   );
    checkWithAbility(opponent, chMap::PUNCH, opponent.ActiveHand()  );
    checkWithAbility(opponent, chMap::SPECIAL, chMap::LH);
    checkWithAbility(opponent, chMap::SPECIAL, chMap::RH);
}

void Character::setDirection(bool left)
{
    if ( (cMap.dir.x == -1 && left ) || (cMap.dir.x == 1 && !left ) )
    {
        for(int i{0};i<6;i++)
        {
            chMap::parts p = static_cast<chMap::parts>(i);
            cMap[p]->flip();
        }
        cMap.swap( chMap::RH, chMap::LH );
        cMap.swap( chMap::RF, chMap::LF );
    }
    cMap.dir.x = (left) ? 1 : -1;
}
