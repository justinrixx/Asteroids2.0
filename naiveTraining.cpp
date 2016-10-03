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

    // randomize the brains
    for (int i = 0; i < populationSize; i++)
    {
        int fitness = 0;
        Network * brain = new Network(NETWORK_INPUTS, NETWORK_OUTPUTS, topology);

        pair<int, Network *> * p = new pair<int, Network *> (fitness, brain);
        brains.push_back(p);
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

        for (int organism = 0; organism < brains.size(); organism++)
        {
            ss << dirName << iteration << "/" << organism << ".net";
            string organismFileName = ss.str();

            ss.str("");
            ss.clear();

            cerr << "Changing to organism " << organism << endl;
            // set the brains
            ai.setNetwork(*(brains[organism]->second));

            // run the simulation
            while (!pGame->isGameOver())
            {
                pGame->update(NULL);
            }

            // set the score and clean up
            int score = pGame->getScore();
            pGame->reset();

            cerr << "Game done" << endl;

            // save the score
            ai.toFile(organismFileName);
            brains[organism]->first = score;
            index << score << ","
                  // just weird stuff to only get the filename, not the directory names
                  << organismFileName.substr(organismFileName.find_last_of("/") + 1, organismFileName.size() - 1)
                  << endl;

            points << iteration << "," << score << endl;

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
            cerr << "About to delete an organism" << endl;
            delete brains[i]->second;
            brains.pop_back();
        }

        cerr << "About to make babies" << endl;
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

        cerr << "Parents selected" << endl;

        while (brains.size() < populationSize)
        {
            // pick to parents
            int p1 = random(0, (int)(hopefulParents.size()));
            int p2 = random(0, (int)(hopefulParents.size()));

            vector<Network *> * babies = hopefulParents[p1]->spCrossover(*hopefulParents[p2]);

            // mutate the babies
            (*babies)[0]->mutate();
            (*babies)[1]->mutate();

            cerr << "Got babies" << endl;

            // check the fitness of the babies
            int babyFitness = 0;

            ai.setNetwork(*(*babies)[0]);
            while (!pGame->isGameOver())
            {
                pGame->update(NULL);
            }

            cerr << "Got baby 1 fitness" << endl;

            babyFitness = pGame->getScore();
            pGame->reset();

            ai.setNetwork(*(*babies)[1]);
            while (!pGame->isGameOver())
            {
                pGame->update(NULL);
            }

            cerr << "Got baby 2 fitness" << endl;

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

            pGame->reset();
        }
    }

    points.close();

    // clean up
    delete pGame;

    return 0;
}


