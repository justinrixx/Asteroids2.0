//
// Created by justin on 4/27/16.
//

#ifndef MLP_NODE_H
#define MLP_NODE_H

#include <vector>
#include <fstream>

/**********************************************************
 * Node class
 * This class is an implementation of a neural network node
 * It's pretty simple, but simplifies building a neural net
 **********************************************************/
class Node {

public:
    // constructor to randomly set weights
    Node(int numInputs);

    // get the node's output value
    double getOutput(const std::vector<double> & inputs);

    // write the weights to a file
    void toFile(std::ostream & os);

private:
    std::vector<double> weights;
};

#endif //MLP_NODE_H
