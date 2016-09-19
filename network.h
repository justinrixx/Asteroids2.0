//
// Created by justin on 5/3/16.
//

#ifndef MLP_NETWORK_H
#define MLP_NETWORK_H

#include <vector>
#include <fstream>
#include <string>
#include "layer.h"

class Network {

public:
    // randomly weighted network
    Network(int numInputs, int numOutputs, const std::vector<int> & topology)
        { init(numInputs, numOutputs, topology); }

    // TODO network from file
    //Network(std::string filename);

    void init(int numInputs, int numOutputs, const std::vector<int> & topology);

    // get the outputs of the network
    void getOutputs(std::vector<double> & outputs, const std::vector<double> & inputs);

    // write the network to a file
    void toFile(std::string filename);

    // read from a file
    void fromFile(std::string filename);

private:
    std::vector<Layer> layers;
    int numInputs;
    int numOutputs;
    std::vector<int> topology;
};


#endif //MLP_NETWORK_H
