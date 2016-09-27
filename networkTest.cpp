/**
* This is just a test file to make sure that the network is working correctly
*/

#include <iostream>
#include <vector>
#include "network.h"

using namespace std;

int main()
{
    vector<double> outputs;

    vector<int> topology;
    topology.push_back(2);
    topology.push_back(2);
    topology.push_back(3);

    Network net(3, 3, topology);

    vector<double> inputs;
    inputs.push_back(1);
    inputs.push_back(2);
    inputs.push_back(3);

    net.getOutputs(outputs, inputs);

    for (int i = 0; i < outputs.size(); i++)
    {
        cout << outputs[i] << " ";
    }
    cout << endl << endl;

    net.outputNetwork();

    // now write to a file, then read it in again
    net.toFile(string("test.net"));
    net.fromFile(string("test.net"));

    outputs.clear();

    net.getOutputs(outputs, inputs);

    for (int i = 0; i < outputs.size(); i++)
    {
        cout << outputs[i] << " ";
    }
    cout << endl << endl;

    net.outputNetwork();

    return 0;
}
