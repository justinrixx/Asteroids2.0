//
// Created by justin on 5/3/16.
//

#include "network.h"

/**
 * Constructor create a randomly weighted network
 */
void Network::init(int numInputs, int numOutputs, const std::vector<int> & topology)
{
    // copy these for later
    this->numInputs = numInputs;
    this->numOutputs = numOutputs;

    // input layer
    layers.push_back(Layer(numInputs, topology[0]));

    this->topology.push_back(topology[0]);

    // hidden layers
    for (int i = 1; i < topology.size(); i++)
    {
        // make the layer
        layers.push_back(Layer(layers[i - 1].getNumOutputs(), topology[i]));

        // save the topology
        this->topology.push_back(topology[i]);
    }

    // output layer
    layers.push_back(Layer(layers[layers.size() - 1].getNumOutputs(), numOutputs));
}

/**
 * Get the outputs of the network.
 * This function feeds the inputs all the way through the network and returns the outputs
 * of the network inside the outputs vector. The outputs vector is assumed to be empty.
 */
void Network::getOutputs(std::vector<double> &outputs, const std::vector<double> &inputs)
{
    std::vector<double> out;

    // first layer
    layers[0].getOutputs(out, inputs);

    // hidden and output layers
    for (int i = 1; i < layers.size(); i++)
    {
        // evens
        if (i % 2 == 0)
        {
            out.clear();
            layers[i].getOutputs(out, outputs);
        }
        // odds
        else
        {
            outputs.clear();
            layers[i].getOutputs(outputs, out);
        }
    }

    // copy the values if ended on even
    if (layers.size() % 2 == 0)
    {
        outputs.clear();
        for (int i = 0; i < out.size(); i++)
        {
            outputs.push_back(out[i]);
        }
    }
}

/**
 * Write the entire network to a file
 */
void Network::toFile(std::string filename)
{
    // open a file stream
    std::ofstream fout(filename.c_str());

    // write the topology
    fout << numInputs << " ";
    for (int i = 0; i < topology.size(); i++)
    {
        fout << topology[i] << " ";
    }
    fout << numOutputs << " 0";

    // write all the layers
    for (int i = 0; i < layers.size(); i++)
    {
        layers[i].toFile(fout);
        fout << std::endl;
    }

    fout.close();
}

/**
 * Read the entire network from a file
 */
void Network::fromFile(std::string filename) {
    
}
