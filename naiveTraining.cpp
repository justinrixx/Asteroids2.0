/**
 * This is the file program that is used to train a naive genetic algorithm
 */

#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <sstream>
#include <algorithm>
#include "game.h"
#include "neuralnetai.h"

#define SEED 12345
#define NULL_SCORE -1

using namespace std;

void usage(char * name)
{
    cout << "Usage: " << name << " i p t1 t2 ... tn" << endl
         << "\ti:  The number of iterations desired" << endl
         << "\tp:  The desired population size" << endl
         << "\ttn: The number of nodes in the nth hidden layer" << endl;
}

/**
 * Simple comparison function to be used by the sort function
 * This function puts the bigger ones at the front of the vector.
 */
bool pairComparison(const pair<int, Network *> * a,const pair<int, Network *> * b)
{
    return a->first > b->first;
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
    float survivalPercentage = .3;
    int cutoffPoint;
    vector<int> topology;

    string dirName = "generation";

    numIterations = atoi(argv[1]);
    populationSize = atoi(argv[2]);

    cutoffPoint = int(survivalPercentage * populationSize);

    for (int i = 3; i < argc; i++)
    {
        topology.push_back(atoi(argv[i]));
    }

    // init the randomness!
    srand(clock());

    // <fitness, brain>
    vector<pair<int, Network * > * > brains;

    // instantiate the game object
    Game *pGame = new Game();
    pGame->setSeed(SEED);

    // randomize the brains
    for (int i = 0; i < populationSize; i++)
    {
        int fitness = NULL_SCORE;
        Network * brain = new Network(NETWORK_INPUTS, NETWORK_OUTPUTS, topology);

        pair<int, Network *> * p = new pair<int, Network *> (fitness, brain);
        brains.push_back(p);
    }

    // open the csv file
    ofstream points("points.csv");

    stringstream ss;

    for (int iteration = 0; iteration < numIterations; iteration++)
    {
        cerr << "Generation " << iteration << endl;

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

        for (int organism = 0; organism < brains.size(); organism++)
        {
            ss << dirName << iteration << "/" << organism << ".net";
            string organismFileName = ss.str();

            ss.str("");
            ss.clear();

            if (brains[organism]->first == NULL_SCORE) {
                // set the brains
                ai.setNetwork(*(brains[organism]->second));

                pGame->reset();

                // run the simulation
                while (!pGame->isGameOver()) {
                    pGame->update(NULL);
                }

                // set the score and clean up
                int score = pGame->getScore();
                brains[organism]->first = score;
            }

            // save the score
            ai.toFile(organismFileName);

            index << brains[organism]->first << ","
                  // just weird stuff to only get the filename, not the directory names
                  << organismFileName.substr(organismFileName.find_last_of("/") + 1, organismFileName.size() - 1)
                  << endl;

            points << iteration << "," << brains[organism]->first << endl;

            /*
            if (organism != 0)
            {
                points << "," << score;
            }
            else
            {
                points << endl << score;
            }
            */
        }

        index.close();

        // best ones at the beginning, worst at the end
        sort(brains.begin(), brains.end(), pairComparison);

        // kill the ones that don't deserve to live
        for (int i = brains.size() - 1; i  > cutoffPoint; i--)
        {
            delete brains[i]->second;
            brains.pop_back();
        }

        // make new babies
        vector<Network *> hopefulParents;

        for (int i = 0; i < brains.size(); i++)
        {
            // put the parent in as many times as its fitness
            for (int j = 0; j < brains[i]->first; j++)
            {
                hopefulParents.push_back(brains[i]->second);
            }
        }

        while (brains.size() < populationSize)
        {
            srand(clock());

            // pick to parents
            int p1 = random(0, (int)(hopefulParents.size()));
            int p2 = random(0, (int)(hopefulParents.size()));

            vector<Network *> * babies = hopefulParents[p1]->spCrossover(*hopefulParents[p2]);

            // mutate the babies
            (*babies)[0]->mutate();
            (*babies)[1]->mutate();

            // check the fitness of the babies
            int babyFitness = 0;

            ai.setNetwork(*(*babies)[0]);
            pGame->reset();
            while (!pGame->isGameOver())
            {
                pGame->update(NULL);
            }

            babyFitness = pGame->getScore();

            ai.setNetwork(*(*babies)[1]);
            pGame->reset();
            while (!pGame->isGameOver())
            {
                pGame->update(NULL);
            }

            // pick the stronger one
            if (babyFitness > pGame->getScore())
            {
                delete (*babies)[1];
                pair<int, Network *> * baby = new pair<int, Network *> (babyFitness, (*babies)[0]);
                brains.push_back(baby);
            }
            else
            {
                delete (*babies)[0];
                pair<int, Network *> * baby = new pair<int, Network *> (babyFitness, (*babies)[1]);
                brains.push_back(baby);
            }
        }
    }

    points.close();

    // clean up
    delete pGame;

    return 0;
}


