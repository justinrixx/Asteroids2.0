/********************************************************
 * This is a simple C++ program that evaluates a neural
 * network by running it through a simulation of the game
 * without graphics. It can be called by any other program.
 ********************************************************/

#include <iostream>
#include <vector>
#include "game.h"
#include "neuralnetai.h"

using namespace std;

int run(string filename);

/***********************************************
 * Main has to initialize the objects to be used
 * and then passes control to the Interface class.
 **********************************************/
int main(int argc, char ** argv)
{
    if (argc > 1)
        cout << run(argv[1]);
    else
        cout << -1;

    return 0;
}

/**************************************************
 * This is the actual function that will be called
 *************************************************/
int run(string filename)
{
    srand(clock());
    Game * pGame = new Game();

    vector<int> topology;
    topology.push_back(20);

    Network net(31, 4, topology);

    net.fromFile(filename);

    NNAI ai(pGame, net);

    pGame->setAI(&ai);

    while (!pGame->isGameOver())
        pGame->update(NULL);

    return pGame->getScore();
}
