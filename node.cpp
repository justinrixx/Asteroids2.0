//
// Created by justin on 4/27/16.
//

#include <stdlib.h>
#include <cmath>
#include "node.h"

/*********************************************************************
 * Node constructor. Must have the number of inputs. The constructor
 * initializes the weights to small random numbers (-.5, .5).
 *********************************************************************/
Node::Node(int numInputs)
{
    for (int i = 0; i < numInputs + 1; i++)
    {
        weights.push_back((rand()) / static_cast <float> (RAND_MAX) - .5);
    }
}

/**********************************************************
 * Get the output value of the node
 *********************************************************/
double Node::getOutput(const std::vector<double> &inputs)
{

    double total = 0.0;

    // multiply the inputs by the weights
    for (int i = 0; i < inputs.size(); i++)
    {
        total += inputs[i] * weights[i];
    }

    // bias
    total += -1 * weights[inputs.size() - 1];

    return 1.0 / (1.0 + exp(-total));
}

/**
 * Write the weights of a node to a file, given the stream
 */
void Node::toFile(std::ostream &os)
{
    for (int i = 0; i < weights.size(); i++)
        os << weights[i] << " ";
}
