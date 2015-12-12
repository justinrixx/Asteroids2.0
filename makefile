#########################################################
# Asteroids 2.0
#########################################################

shipDriver: ship.o uiDraw.o uiInteract.o shipDriver.cpp
	g++ -o shipDriver shipDriver.cpp ship.o uiDraw.o uiInteract.o -lglut -lGL -lGLU

#########################################################
# Individual components
#########################################################
ship.o: ship.h ship.cpp uiDraw.o uiInteract.o
	g++ -c ship.cpp
uiDraw.o: uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp
uiInteract.o: uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp