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

/**
 * This is everything about an organism
 */
struct Tuple
{
    // the actual brain
    Network * pNet;

    // its fitness average
    int fitness;

    // how many generations it has lasted
    int generation;

    // a name so tracking across generations is possible
    string name;
};

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
 * It only compares the fitness, so that's all that matters.
 */
bool pairComparison(const Tuple * a,const Tuple * b)
{
    return a->fitness > b->fitness;
}

void generateBrains(vector<Tuple * > & brains, Game * pGame, int p, const vector<int> & topology, NNAI & ai);
void killStuff(vector<Tuple * > & brains, int cutoff);
void repopulate(vector<Tuple * > & brains, Game * pGame, int p, int generation, NNAI & ai);

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

    vector<Tuple * > brains;

    // instantiate the game object
    Game *pGame = new Game();
    Network net(NETWORK_INPUTS, NETWORK_OUTPUTS, topology);
    NNAI ai(pGame, net);
    pGame->setAI(&ai);

    generateBrains(brains, pGame, populationSize, topology, ai);

    // open the csv file
    ofstream points("points.csv");

    stringstream ss;

    for (int iteration = 0; iteration < numIterations; iteration++)
    {
        cerr << "Generation " << iteration + 1 << endl;

        // make the directory for the generation
        ss << dirName << iteration;
        string dir = ss.str();
        mkdir(dir.c_str(), 0755);

        ss.str("");
        ss.clear();

        ofstream index((dir + "/index.csv").c_str());

        // replenish the earth
        killStuff(brains, cutoffPoint);

        cerr << "BRAINS ================================= " << brains.size() << endl;
        for (int i = 0; i < brains.size(); i++)
        {
            cerr << brains[i]->name << endl;
            brains[i]->pNet->outputNetwork();
            cerr << "--------------------" << endl;
        }

        repopulate(brains, pGame, populationSize, iteration, ai);
        cerr << "After repopulation" << endl;
        cerr << "BRAINS ================================= " << brains.size() << endl;
        for (int i = 0; i < brains.size(); i++)
        {
            cerr << brains[i]->name << endl;
            brains[i]->pNet->outputNetwork();
            cerr << "--------------------" << endl;
        }

        for (int organism = 0; organism < brains.size(); organism++)
        {
            ss << dirName << iteration << "/" << brains[organism]->name;
            string organismFileName = ss.str();

            ss.str("");
            ss.clear();

            // set the brains
            ai.setNetwork(*(brains[organism]->pNet));

            pGame->reset();

            // run the simulation
            while (!pGame->isGameOver())
            {
                pGame->update(NULL);
            }

            // set the score and clean up
            int score = pGame->getScore();

            // this maintains an unweighted average across generations
            brains[organism]->fitness =
                    (int)((((float)(brains[organism]->generation - 1) / brains[organism]->generation) * brains[organism]->fitness)
                    + ((1.0 / brains[organism]->generation) * score));

            brains[organism]->generation += 1;

            // save the score
            ai.toFile(organismFileName);

            index << brains[organism]->fitness << ","
                  // just weird stuff to only get the filename, not the directory names
                  << organismFileName.substr(organismFileName.find_last_of("/") + 1, organismFileName.size() - 1)
                  << endl;

            points << iteration << "," << brains[organism]->name << endl;
        }

        index.close();
    }

    points.close();

    // clean up
    delete pGame;

    return 0;
}

/**
 * This is where the initial population is generated. The brains are random,
 * and they are pre-evaluated.
 */
void generateBrains(vector<Tuple * > & brains, Game * pGame, int p, const vector<int> & topology, NNAI & ai)
{
    ostringstream ss;

    for (int i = 0; i < p; i++)
    {
        ss << 0 << "-" << i << ".net";

        Tuple * organism = new Tuple;
        cerr << "Topology size: " << topology.size() << endl;
        organism->pNet = new Network(NETWORK_INPUTS, NETWORK_OUTPUTS, topology);
        organism->name = ss.str();
        organism->generation = 2;

        // evaluate it
        ai.setNetwork(*organism->pNet);
        pGame->reset();
        while (!pGame->isGameOver())
            pGame->update(NULL);

        organism->fitness = pGame->getScore();

        ss.str("");
        ss.clear();

        brains.push_back(organism);
    }
}

/**
 * This function simulates the harsh reality of life, by killing off
 * all but the top performers up to the cutoff point. The cutoff point
 * is measured from the beginning of the list up to where the organisms
 * stop living and start dying.
 */
void killStuff(vector<Tuple * > & brains, int cutoff)
{
    // best ones at the beginning, worst at the end
    sort(brains.begin(), brains.end(), pairComparison);

    // kill the ones that don't deserve to live
    for (int i = brains.size() - 1; i  > cutoff; i--)
    {
        delete brains[i]->pNet;
        brains.pop_back();
    }
}

/**
 * The population is replenished here. The list of brains should be already pared
 * down to the survivors, and the population will be replenished until it is size
 * p. The generation is passed in so that the babies can be named correctly.
 */
void repopulate(vector<Tuple * > & brains, Game * pGame, int p, int generation, NNAI & ai)
{
    int orgNum = 0;

    ostringstream ss;

    // make new babies
    vector<Network *> hopefulParents;

    for (int i = 0; i < brains.size(); i++)
    {
        // put the parent in as many times as its fitness
        for (int j = 0; j < brains[i]->fitness; j++)
        {
            hopefulParents.push_back(brains[i]->pNet);
        }
    }

    while (brains.size() < p)
    {
        // pick two parents
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

        // Two babies will fight for one name . . .
        ss << generation + 1 << "-" << orgNum << ".net";

        // pick the stronger one
        if (babyFitness > pGame->getScore())
        {
            delete (*babies)[1];
            Tuple * baby = new Tuple;
            baby->pNet = (*babies)[0];
            baby->fitness = babyFitness;
            baby->generation = 2;
            baby->name = ss.str();
            brains.push_back(baby);

            cerr << "baby generated: " << baby->name << endl;
            (*babies)[0]->outputNetwork();
            cerr << endl << endl;
        }
        else
        {
            delete (*babies)[0];
            Tuple * baby = new Tuple;
            baby->pNet = (*babies)[0];
            baby->fitness = pGame->getScore();
            baby->generation = 2;
            baby->name = ss.str();
            brains.push_back(baby);

            cerr << "baby generated: " << baby->name << endl;
            (*babies)[1]->outputNetwork();
            cerr << endl << endl;
        }

        ss.str("");
        ss.clear();

        orgNum++;
    }
}
