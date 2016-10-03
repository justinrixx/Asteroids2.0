/**
* This is just a test file to make sure that the network is working correctly
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include "network.h"

using namespace std;

void testCrossover()
{
    vector<int> topology;
    topology.push_back(2);
    topology.push_back(2);
    topology.push_back(2);

    Network mom(4, 4, topology);
    Network dad(4, 4, topology);

    vector<Network *> * pVector = mom.uCrossover(dad);

    cout << "Mom & Dad" << endl;
    mom.outputNetwork();
    dad.outputNetwork();

    cout << "Brother & Sister" << endl;
    (*pVector)[0]->outputNetwork();
    (*pVector)[1]->outputNetwork();
}

int main()
{
    srand(clock());

    testCrossover();
    return 0;

    vector<double> outputs;

    vector<int> topology;
    topology.push_back(2);
    topology.push_back(2);
    topology.push_back(3);
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

    outputs.clear();

    net.getOutputs(outputs, inputs);

    for (int i = 0; i < outputs.size(); i++)
    {
        cout << outputs[i] << " ";
    }
    cout << endl << endl;

    //net.outputNetwork();

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

    //net.outputNetwork();

    return 0;
}
