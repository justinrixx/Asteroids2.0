//
// Created by justin on 4/27/16.
//

#include "layer.h"

/**
 * Layer constructor. Needs to know the number of nodes in the layer,
 * and also the number of inputs to each node. Initializes a layer of
 * hidden nodes with random weights.
 */
Layer::Layer(int numInputs, int numNodes)
{
    // add the correct number of nodes to the layer
    for (int i = 0; i < numNodes; i++)
    {
        nodes.push_back(Node(numInputs));
    }
}

/**
 * Get the output vector of the layer. The first parameter should be an empty
 * vector. The output vector will be put inside this vector. This function
 * doesn't actually return anything.
 */
void Layer::getOutputs(std::vector<double> &outputs, const std::vector<double> & inputs)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        outputs.push_back(nodes[i].getOutput(inputs));
    }
}

int Layer::getNumOutputs() const
{
    return nodes.size();
}

void Layer::toFile(std::ostream &os)
{
    for (int i = 0; i < nodes.size(); i++)
        nodes[i].toFile(os);
}
