//
// Created by justin on 10/11/16.
//

#ifndef ASTEROIDS2_0_ORGANISM_H
#define ASTEROIDS2_0_ORGANISM_H


#include "network.h"

/**
 * This is everything about an organism
 */
class Organism
{
public:

    /*
    // Default constructor. Do nothing.
    Organism() { };

    // copy constructor
    Organism(const Organism & rhs)
    {
        this->pNet = rhs.pNet;
        this->name = rhs.name;
        this->fitness = rhs.fitness;
        this->generation = rhs.generation;
    }*/

    // the actual brain
    Network * pNet;

    // its fitness average
    int fitness;

    // how many generations it has lasted
    int generation;

    // a name so tracking across generations is possible
    string name;
};


#endif //ASTEROIDS2_0_ORGANISM_H
