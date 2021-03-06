//
// Created by justin on 5/3/16.
//

#ifndef MLP_NETWORK_H
#define MLP_NETWORK_H

#include <vector>
#include <fstream>
#include <string>
#include "uiDraw.h"

class Network {

public:
    // copy constructor
    Network(const Network & rhs);

    // randomly weighted network
    Network(int numInputs, int numOutputs, const std::vector<int> & topology)
        { init(numInputs, numOutputs, topology); }

    // TODO network from file
    //Network(std::string filename);

    void init(int numInputs, int numOutputs, const std::vector<int> & topology);

    // get the outputs of the network
    void getOutputs(std::vector<double> & outputs, const std::vector<double> & inputs);

    // write the network to a file
    void toFile(const std::string & filename);

    // read from a file
    void fromFile(const std::string & filename);

    // single point crossover
    std::vector<Network *> * spCrossover(const Network & rhs);

    // uniform crossover
    std::vector<Network *> * uCrossover(const Network & rhs);

    // mutate the dna to something slightly different
    void mutate();

    // for debugging
    void outputNetwork();

    void topologySize() { std::cerr << "topology.size() " << topology.size() << std::endl; };

private:
    void makeLayer(std::vector<std::vector<double> > &layer, int numInputs, int numNodes);
    void makeNode(std::vector<double> &node, int numInputs);
    void getOutputs(const std::vector<std::vector<double> > & layer, std::vector<double> & outputs, const std::vector<double> & inputs);

    std::vector<std::vector<std::vector<double> > > layers;
    int numInputs;
    int numOutputs;
    std::vector<int> topology;
};


#endif //MLP_NETWORK_H
