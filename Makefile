#
# Makefile 
#

CCC      = g++
FLAGS += -std=c++17 -pedantic -Wall -Wextra -Weffc++
SFML_FLAGS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDE_SFML += -I${SFML_ROOT}/include -L${SFML_ROOT}/lib

OBJECTS = controller.o button.o bodypart.o character.o menu.o game_state.o player.o library.o options.o round.o match.o tournament.o characters.o charactermenu.o helper.o chMap.o winscreen.o



main: bin ${OBJECTS} Makefile src/main.cc
	${CCC} ${FLAGS} src/main.cc ${OBJECTS} -o bin/game ${INCLUDE_SFML} ${SFML_FLAGS}

test: bin ${OBJECTS} Makefile src/test.cc
	${CCC} ${FLAGS} src/test.cc ${OBJECTS} -o bin/test ${INCLUDE_SFML} ${SFML_FLAGS}	

menu.o: src/menu.h src/menu.cc button.o game_state.o options.o tournament.o winscreen.o library.o match.o player.o characters.o
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/menu.cc 

button.o: src/button.h src/button.cc library.o
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/button.cc

controller.o: src/controller.cc src/controller.h
	${CCC} ${FLAGS} ${SFML_FLAGS} ${INCLUDE_SFML} -c src/controller.cc

bodypart.o: src/bodypart.h src/bodypart.cc 
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/bodypart.cc

character.o: src/character.h src/character.cc bodypart.o library.o helper.o chMap.o
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/character.cc

player.o: src/player.h src/player.cc controller.o character.o
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/player.cc

game_state.o: src/game_state.h src/game_state.cc
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/game_state.cc

library.o: src/library.h src/library.cc
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/library.cc

options.o: src/options.h src/options.cc controller.o button.o
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/options.cc

round.o: src/round.h src/round.cc controller.o player.o game_state.o characters.o
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/round.cc

match.o: src/match.h src/match.cc round.o controller.o player.o round.o library.o
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/match.cc

charactermenu.o: src/charactermenu.h src/charactermenu.cc character.o characters.o controller.o
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/charactermenu.cc

tournament.o: src/tournament.h src/tournament.cc game_state.o match.o player.o character.o controller.o charactermenu.o characters.o button.o
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/tournament.cc

characters.o: src/characters.h src/characters.cc chMap.o character.o
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/characters.cc

chMap.o: src/chMap.h src/chMap.cc bodypart.o helper.o
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/chMap.cc

helper.o: src/helper.h src/helper.cc
	${CCC} ${FLAGS} -fPIC -c src/helper.cc

winscreen.o: src/winscreen.h src/winscreen.cc game_state.o button.o library.o
	${CCC} ${FLAGS} ${INCLUDE_SFML} -c src/winscreen.cc

directories: 
	@ \mkdir -p bin

bin:
	@ \mkdir -p bin
clean:
	@ \rm -f *.o *.gch
	@ \rm -r -f bin
zap:
	@ \rm -f -v *.~
	@ \rm -f -v *.~*
	@ \rm -f -v src/*.~
	@ \rm -f -v src/*.~*
	@ \rm -f -v src/*#
	@ \rm -f -v src/#*	

