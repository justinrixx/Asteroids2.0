#########################################################
# Asteroids 2.0
#########################################################

#########################################################
# Component drivers
#########################################################
playerDriver: player.o ship.o uiDraw.o uiInteract.o ai.h playerDriver.cpp
	g++ -o playerDriver playerDriver.cpp player.o ship.o uiDraw.o uiInteract.o -lglut -lGL -lGLU
shipDriver: ship.o uiDraw.o uiInteract.o shipDriver.cpp
	g++ -o shipDriver shipDriver.cpp ship.o uiDraw.o uiInteract.o -lglut -lGL -lGLU

#########################################################
# Individual components
#########################################################
player.o: player.h player.cpp uiDraw.o uiInteract.o ship.h ai.h
	g++ -c player.cpp
ship.o: ship.h ship.cpp uiDraw.o uiInteract.o
	g++ -c ship.cpp
uiDraw.o: uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp
uiInteract.o: uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp