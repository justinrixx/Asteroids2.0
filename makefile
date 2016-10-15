#########################################################
# Asteroids 2.0
#########################################################

#########################################################
# The game
#########################################################
gameDriver.out: game.o gameDriver.cpp point.h bullet.h uiInteract.o uiDraw.o player.o ship.o network.o rock.h vector.h simpleai.h randomai.h network.h neuralnetai.h
	g++ -o gameDriver.out gameDriver.cpp game.o uiDraw.o uiInteract.o player.o ship.o network.o -lglut -lGL -lGLU
naiveTrainer.out: game.o naiveTraining.cpp point.h bullet.h uiInteract.o uiDraw.o player.o ship.o network.o rock.h vector.h network.h neuralnetai.h organism.h
	g++ -o naiveTrainer.out -g naiveTraining.cpp game.o uiDraw.o uiInteract.o player.o ship.o network.o -lglut -lGL -lGLU
gameNNRunner.out: game.o gameNNRunner.cpp point.h bullet.h uiInteract.o uiDraw.o player.o ship.o network.o rock.h vector.h network.h neuralnetai.h
	g++ -o gameNNRunner.out gameNNRunner.cpp game.o uiDraw.o uiInteract.o player.o ship.o network.o -lglut -lGL -lGLU

#########################################################
# Component drivers
#########################################################
networkDriver.out: network.h network.o uiDraw.o networkTest.cpp
	g++ -o networkDriver.out networkTest.cpp network.o uiDraw.o -lglut -lGL -lGLU
bulletDriver.out: point.h bullet.h uiInteract.o uiDraw.o bulletDriver.cpp
	g++ -o bulletDriver.out bulletDriver.cpp uiDraw.o uiInteract.o -lglut -lGL -lGLU
drawTest.out: point.h uiDraw.o uiInteract.o drawTest.cpp
	g++ -o drawTest.out drawTest.cpp uiDraw.o uiInteract.o -lglut -lGL -lGLU
rockDriver.out: rock.h uiDraw.o uiInteract.o rockDriver.cpp
	g++ -o rockDriver.out rockDriver.cpp uiDraw.o uiInteract.o -lglut -lGL -lGLU
playerDriver.out: player.o ship.o uiDraw.o uiInteract.o game.h playerDriver.cpp
	g++ -o playerDriver.out playerDriver.cpp player.o ship.o uiDraw.o uiInteract.o -lglut -lGL -lGLU
shipDriver.out: ship.o uiDraw.o uiInteract.o shipDriver.cpp
	g++ -o shipDriver.out shipDriver.cpp ship.o uiDraw.o uiInteract.o -lglut -lGL -lGLU

#########################################################
# Individual components
#########################################################
game.o: game.h game.cpp uiDraw.o uiInteract.o player.o ship.o rock.h bullet.h point.h vector.h debris.h
	g++ -c game.cpp -g
player.o: player.h player.cpp uiDraw.o uiInteract.o ship.h game.h
	g++ -c player.cpp -g
ship.o: ship.h ship.cpp uiDraw.o uiInteract.o bullet.h
	g++ -c ship.cpp -g
network.o: network.h network.cpp
	g++ -c network.cpp -g
uiDraw.o: uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp -g
uiInteract.o: uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp -g

########################################################
# Clean up
########################################################
clean:
	rm -rf generation* points.csv