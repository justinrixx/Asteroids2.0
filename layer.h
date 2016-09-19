//
// Created by justin on 4/27/16.
//

#ifndef MLP_LAYER_H
#define MLP_LAYER_H

#include <fstream>
#include "node.h"

class Layer {
public:
    Layer(int numInputs, int numNodes);

    int getNumOutputs() const;

    void getOutputs(std::vector<double> & outputs, const std::vector<double> & inputs);

    void toFile(std::ostream & os);

private:
    std::vector<Node> nodes;
};


#endif //MLP_LAYER_H
