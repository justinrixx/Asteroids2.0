#include <iostream>
#include <vector>
#include "game.h"
#include "neuralnetai.h"

using namespace std;

/*************************************
 * Super simple callback function. Just
 * update the game, then draw it.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
    // cast the pointer back to the correct type
    Game * pGame = (Game *)p;

    // update the game
    pGame->update(pUI);

    // draw the game
    pGame->draw();
}

/***********************************************
 * Main has to initialize the objects to be used
 * and then passes control to the Interface class.
 **********************************************/
int main(int argc, char ** argv)
{
    srand(clock());
    // instantiate the game object
    bool fromFile = false;
    Game * pGame = new Game();

    vector<int> topology;
    topology.push_back(10);
    topology.push_back(10);
    topology.push_back(10);

    Network net(21, 5, topology);

    if (argc > 1)
    {
        net.fromFile(argv[1]);
        fromFile = true;
    }

    // instantiate an AI
    //SimpleAI ai(pGame);
    //RandomAI ai(pGame);
    NNAI ai(pGame, net);

    // the game needs a reference to the AI
    if (fromFile)
        pGame->setAI(&ai);
    else
        pGame->setAI(NULL);

    Interface ui(argc, argv, "Asteroids");
    ui.run(callBack, pGame);

    return 0;
}
