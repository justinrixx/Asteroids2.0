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

/***********************************************
 * Main has to initialize the objects to be used
 * and then passes control to the Interface class.
 **********************************************/
int main(int argc, char ** argv)
{
    srand(clock());
    // instantiate the game object
    Game * pGame = new Game();

    vector<int> topology;
    topology.push_back(20);

    Network net(31, 4, topology);

    if (argc > 1)
        net.fromFile(argv[1]);
    else
    {
        cout << -1;
        return 0;
    }

    // instantiate an AI
    NNAI ai(pGame, net);

    // the game needs a reference to the AI
    pGame->setAI(&ai);

    while (!pGame->isGameOver())
        pGame->update(NULL);

    cout << pGame->getScore();

    return 0;
}
