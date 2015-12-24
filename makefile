#########################################################
# Asteroids 2.0
#########################################################

#########################################################
# Component drivers
#########################################################
bulletDriver: point.h bullet.h uiInteract.o uiDraw.o bulletDriver.cpp
	g++ -o bulletDriver bulletDriver.cpp uiDraw.o uiInteract.o -lglut -lGL -lGLU
drawTest: point.h uiDraw.o uiInteract.o drawTest.cpp
	g++ -o drawTest drawTest.cpp uiDraw.o uiInteract.o -lglut -lGL -lGLU
rockDriver: rock.h uiDraw.o uiInteract.o rockDriver.cpp
	g++ -o rockDriver rockDriver.cpp uiDraw.o uiInteract.o -lglut -lGL -lGLU
playerDriver: player.o ship.o uiDraw.o uiInteract.o game.h playerDriver.cpp
	g++ -o playerDriver playerDriver.cpp player.o ship.o uiDraw.o uiInteract.o -lglut -lGL -lGLU
shipDriver: ship.o uiDraw.o uiInteract.o shipDriver.cpp
	g++ -o shipDriver shipDriver.cpp ship.o uiDraw.o uiInteract.o -lglut -lGL -lGLU

#########################################################
# Individual components
#########################################################
player.o: player.h player.cpp uiDraw.o uiInteract.o ship.h game.h
	g++ -c player.cpp
ship.o: ship.h ship.cpp uiDraw.o uiInteract.o
	g++ -c ship.cpp
uiDraw.o: uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp
uiInteract.o: uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp