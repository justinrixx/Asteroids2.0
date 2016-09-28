/**
* Created by justin on 5/3/16.
*/

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

    for (int i = 0; i < topology.size(); i++)
    {
        this->topology.push_back(topology[i]);
    }

    // input layer
    std::vector<std::vector<double> > inputLayer;
    makeLayer(inputLayer, numInputs, topology[0]);
    layers.push_back(inputLayer);

    // hidden layers
    for (int i = 1; i < topology.size(); i++)
    {
        // make the layer
        std::vector<std::vector<double> > layer;
        makeLayer(layer, layers[i - 1].size(), topology[i]);
        layers.push_back(layer);
    }

    // output layer
    std::vector<std::vector<double> > outputLayer;
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
    fout << numInputs << " " << numOutputs << " " << topology.size() << " ";
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
    layers.clear();
    topology.clear();
    numInputs = 0;
    numOutputs = 0;

    int topologySize = 0;
    std::ifstream fin(filename.c_str());

    fin >> numInputs >> numOutputs >> topologySize;

    assert(numInputs != 0 || numOutputs != 0 || topologySize != 0);

    // read in the topology
    int temp = 0;
    for (int i = 0; i < topologySize; i++)
    {
        fin >> temp;
        topology.push_back(temp);
    }

    assert(topologySize == topology.size());

    // input layer
    std::vector<std::vector<double> > inputLayer;

    for (int i = 0; i < topology[0]; i++)
    {
        double weight = 0;
        std::vector<double> node;

        // +1 for the bias
        for (int j = 0; j < numInputs + 1; j++)
        {
            fin >> weight;
            node.push_back(weight);
        }

        inputLayer.push_back(node);
    }

    layers.push_back(inputLayer);

    for (int i = 1; i < topologySize; i++)
    {
        std::vector<std::vector<double> > layer;

        for (int j = 0; j < topology[i]; j++)
        {
            double weight = 0;
            std::vector<double> node;

            for (int k = 0; k < layers[i - 1].size() + 1; k++)
            {
                fin >> weight;
                node.push_back(weight);
            }

            layer.push_back(node);
        }

        layers.push_back(layer);
    }

    // output layer
    std::vector<std::vector<double> > outputLayer;

    for (int i = 0; i < numOutputs; i++)
    {
        double weight = 0;
        std::vector<double> node;

        // +1 for the bias
        for (int j = 0; j < topology[topology.size() - 1] + 1; j++)
        {
            fin >> weight;
            node.push_back(weight);
        }

        outputLayer.push_back(node);
    }

    layers.push_back(outputLayer);
}

/**
 * A helper function to build a layer in the neural net
 */
void Network::makeLayer(std::vector<std::vector<double> > &layer, int numInputs, int numNodes)
{
    for (int i = 0; i < numNodes; i++)
    {
        std::vector<double> node;
        makeNode(node, numInputs);

        layer.push_back(node);
    }
}

/**
 * A helper function to build a node in the neural net
 */
void Network::makeNode(std::vector<double> &node, int numInputs)
{
    // numInputs + 1 for the bias
    for (int i = 0; i < numInputs + 1; i++)
    {
        node.push_back(random(-1.0, 1.0));
    }
}

/**
 * A helper function to get the output of a layer
 */
void Network::getOutputs(const std::vector<std::vector<double> > & layer, std::vector<double> & outputs,
                         const std::vector<double> & inputs)
{
    for (int i = 0; i < layer.size(); i++)
    {
        assert(layer[i].size() == inputs.size() + 1);

        double total = 0;
        for (int j = 0; j < layer[i].size() - 1; j++)
        {
            total += inputs[j] * layer[i][j];
        }

        // bias node
        total += layer[i][layer[i].size() - 1] * -1;

        outputs.push_back(tanh(total));
    }
}

/**
 * Copy constructor
 */
Network::Network(const Network & rhs)
{

    this->numInputs = rhs.numInputs;
    this->numOutputs = rhs.numOutputs;
    this->topology = rhs.topology;

    for (int i = 0; i < rhs.layers.size(); i++)
    {
        std::vector<std::vector<double> > layer;
        for (int j = 0; j < rhs.layers[i].size(); j++)
        {
            std::vector<double> node;
            for (int k = 0; k < rhs.layers[i][j].size(); k++)
            {
                node.push_back(rhs.layers[i][j][k]);
            }
            layer.push_back(node);
        }
        this->layers.push_back(layer);
    }
}

void Network::outputNetwork()
{
    for (int i = 0; i < layers.size(); i++)
    {
        for (int j = 0; j < layers[i].size(); j++)
        {
            for (int k = 0; k < layers[i][j].size(); k++)
            {
                std::cerr << layers[i][j][k] << " ";
            }
        }
    }
    std::cerr << std::endl << std::endl;
}
