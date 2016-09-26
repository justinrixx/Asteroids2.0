//
// Created by justin on 5/3/16.
//

#include <cassert>
#include <cmath>
#include <iostream>
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
    std::vector<std::vector<float> > inputLayer;
    makeLayer(inputLayer, numInputs, topology[0]); // - 1 because we don't want a bias on the inputs
    layers.push_back(inputLayer);

    this->topology.push_back(topology[0]);

    // hidden layers
    for (int i = 1; i < topology.size(); i++)
    {
        // make the layer
        std::vector<std::vector<float> > layer;
        makeLayer(layer, layers[i - 1].size(), topology[i]);
        layers.push_back(layer);

        // save the topology
        this->topology.push_back(topology[i]);
    }

    // output layer
    std::vector<std::vector<float> > outputLayer;
    makeLayer(outputLayer, layers[layers.size() - 1].size(), numOutputs);
    layers.push_back(outputLayer);
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
    getOutputs(layers[0], out, inputs);

    // hidden and output layers
    for (int i = 1; i < layers.size(); i++)
    {
        // evens
        if (i % 2 == 0)
        {
            out.clear();
            getOutputs(layers[i], out, outputs);
        }
        // odds
        else
        {
            outputs.clear();
            getOutputs(layers[i], outputs, out);
        }
    }

    // copy the values if ended on even
    if (layers.size() % 2 == 1)
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
    fout << numInputs << " " << numOutputs << " ";
    for (int i = 0; i < topology.size(); i++)
    {
        fout << topology[i] << " ";
    }

    // write all the layers
    for (int i = 0; i < layers.size(); i++)
    {
        for (int j = 0; j < layers[i].size(); j++)
        {
            for (int k = 0; k < layers[i][j].size(); k++)
            {
                fout << layers[i][j][k] << " ";
            }
        }
    }

    fout.close();
}

/**
 * Read the entire network from a file
 */
void Network::fromFile(std::string filename)
{

}

/**
 * A helper function to build a layer in the neural net
 */
void Network::makeLayer(std::vector<std::vector<float> > &layer, int numInputs, int numNodes)
{
    for (int i = 0; i < numNodes; i++)
    {
        std::vector<float> node;
        makeNode(node, numInputs);

        layer.push_back(node);
    }
}

/**
 * A helper function to build a node in the neural net
 */
void Network::makeNode(std::vector<float> &node, int numInputs)
{
    // numInputs + 1 for the bias
    for (int i = 0; i < numInputs + 1; i++)
    {
        node.push_back(random(-1, 1));
    }
}

/**
 * A helper function to get the output of a layer
 */
void Network::getOutputs(const std::vector<std::vector<float> > & layer, std::vector<double> & outputs,
                         const std::vector<double> & inputs)
{
    for (int i = 0; i < layer.size(); i++)
    {
        assert(layer[i].size() == inputs.size() + 1);

        float total = 0;
        for (int j = 0; j < layer[i].size(); j++)
        {
            total += inputs[j] * layer[i][j];
        }

        // bias node
        total += layer[i][layer[i].size() - 1] * -1;

        outputs.push_back(tanh(total));
    }
}
