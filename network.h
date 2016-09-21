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
    void makeLayer(std::vector<std::vector<float> > &layer, int numInputs, int numNodes);
    void makeNode(std::vector<float> &node, int numInputs);
    void getOutputs(const std::vector<std::vector<float> > & layer, std::vector<double> & outputs, const std::vector<double> & inputs);

    std::vector<std::vector<std::vector<float> > > layers;
    int numInputs;
    int numOutputs;
    std::vector<int> topology;
};


#endif //MLP_NETWORK_H
