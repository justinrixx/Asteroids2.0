#########################################################
# Asteroids 2.0
#########################################################

#########################################################
# The real deal
#########################################################
gameDriver: game.o gameDriver.cpp point.h bullet.h uiInteract.o uiDraw.o player.o ship.o network.o rock.h bullet.h vector.h simpleai.h randomai.h network.h neuralnetai.h
	g++ -o gameDriver gameDriver.cpp game.o uiDraw.o uiInteract.o player.o ship.o network.o -lglut -lGL -lGLU


#########################################################
# Component drivers
#########################################################
networkDriver: network.h network.o uiDraw.o networkTest.cpp
	g++ -o networkDriver networkTest.cpp network.o uiDraw.o -lglut -lGL -lGLU
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
game.o: game.h game.cpp uiDraw.o uiInteract.o player.o ship.o rock.h bullet.h point.h vector.h debris.h
	g++ -c game.cpp
player.o: player.h player.cpp uiDraw.o uiInteract.o ship.h game.h
	g++ -c player.cpp
ship.o: ship.h ship.cpp uiDraw.o uiInteract.o bullet.h
	g++ -c ship.cpp
network.o: network.h network.cpp
	g++ -c network.cpp
uiDraw.o: uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp
uiInteract.o: uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp