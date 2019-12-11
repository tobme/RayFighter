<p >
  <img src="Design/Loga.png" width="180"/>
</p>

# Ray Fighters<br />
Ray Fighters is a multiplayer fighting game made in c++, try it out!  
This is a project in the course TDDI02<br />

## Requirements
* linux
* g++  version 5.4.1 or higher
* SFML build 2.4.2

## Installation

A. Clone the repository: `git clone git@gitlab.ida.liu.se:TDDI02-2017/c4.git`.

B. Open: `<repo>/`

C. Build and execute:
```
> make 
> bin/game
```
To clean:
```
> make clean
```

## Information

More info about the project and how to play on our [promopage](http://www-und.ida.liu.se/~albsj371/)
<br /><br />

## Supports
* Plug and play device
* Keyboard and mouse controll 
* Audio output

### Memory leaks 
SFML has a problem with memory leaks with the functions  
setOutlineThickness(param) and setOutlineColor(param).  
[More info](https://github.com/SFML/SFML/issues/1233)
