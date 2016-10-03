/**
 * This is the file program that is used to train a naive genetic algorithm
 */

#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <sstream>
#include "game.h"
#include "neuralnetai.h"

using namespace std;

void usage(char * name)
{
    cout << "Usage: " << name << " i p t1 t2 ... tn" << endl
         << "\ti:  The number of iterations desired" << endl
         << "\tp:  The desired population size" << endl
         << "\ttn: The number of nodes in the nth hidden layer" << endl;
}

/***********************************************
 * Do the things!
 **********************************************/
int main(int argc, char ** argv)
{
    if (argc < 4)
    {
        usage(argv[0]);
        return 0;
    }

    int numIterations;
    int populationSize;
    vector<int> topology;

    string dirName = "generation";

    numIterations = atoi(argv[1]);
    populationSize = atoi(argv[2]);

    for (int i = 3; i < argc; i++)
    {
        topology.push_back(atoi(argv[i]));
    }

    // init the randomness!
    srand(clock());

    // <fitness, brain>
    vector<pair<int, Network * > > * brains = new vector<pair<int, Network * > >();
    vector<pair<int, Network * > > * nextGeneration = new vector<pair<int, Network * > >();

    // instantiate the game object
    Game *pGame = new Game();

    // randomize the brains
    for (int i = 0; i < populationSize; i++)
    {
        int fitness = 0;
        Network * brain = new Network(NETWORK_INPUTS, NETWORK_OUTPUTS, topology);

        pair<int, Network *> p(fitness, brain);
        brains->push_back(p);
    }

    // open the csv file
    ofstream points("points.csv");

    stringstream ss;

    for (int iteration = 0; iteration < numIterations; iteration++)
    {
        // make the directory for the generation
        ss << dirName << iteration;
        string dir = ss.str();
        mkdir(dir.c_str(), 0755);

        ss.str("");
        ss.clear();

        ofstream index((dir + "/index.csv").c_str());

        Network net(NETWORK_INPUTS, NETWORK_OUTPUTS, topology);
        NNAI ai(pGame, net);

        pGame->setAI(&ai);

        for (int organism = 0; organism < brains->size(); organism++)
        {
            ss << dirName << iteration << "/" << organism << ".net";
            string organismFileName = ss.str();

            ss.str("");
            ss.clear();

            // set the brains
            ai.setNetwork(*(*brains)[organism].second);

            // run the simulation
            while (!pGame->isGameOver())
            {
                pGame->update(NULL);
            }

            // set the score and clean up
            int score = pGame->getScore();
            pGame->reset();

            // save the score
            ai.toFile(organismFileName);
            (*brains)[organism].first = score;
            index << score << ","
                  // just weird stuff to only get the filename, not the directory names
                  << organismFileName.substr(organismFileName.find_last_of("/") + 1, organismFileName.size() - 1)
                  << endl;

            if (organism != 0)
            {
                points << "," << score;
            }
            else
            {
                points << endl << score;
            }
        }

        index.close();
    }

    points.close();

    // clean up
    delete brains;
    delete nextGeneration;
    delete pGame;

    return 0;
}


