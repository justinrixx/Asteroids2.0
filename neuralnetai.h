/*****************************************************
 * Neural Net AI Class
 * Do what the neural net says to
 *****************************************************/
#include <cassert>
#include "game.h"
#include "network.h"

#define NETWORK_INPUTS 5 + (5 * NUM_CLOSEST_ROCKS)
#define NETWORK_OUTPUTS 4

#ifndef _NNAI_H
#define _NNAI_H

class NNAI : public AI
{
public:
    // Call the AI's constructor, and also initialize the neural network
    NNAI(Game * game, std::vector<int> & topology)
            : AI(game), mNetwork(NETWORK_INPUTS, NETWORK_OUTPUTS, topology) { };

protected:
    virtual void move(const Ship & playerShip)
    {
        // reset the vectors if there is anything in them
        if (!inputs.empty())
        {
            inputs.clear();
        }
        if (!outputs.empty())
        {
            outputs.clear();
        }

        // set the ship values
        inputs.push_back(playerShip.getX());
        inputs.push_back(playerShip.getY());
        inputs.push_back(playerShip.getDx());
        inputs.push_back(playerShip.getDy());
        inputs.push_back(playerShip.getRotation());

        // set the rock values
        for (int i = 0; i < NUM_CLOSEST_ROCKS; i++)
        {
            if (closestRocks[i] == NULL)
            {
                for (int j = 0; j < 5; j++)
                {
                    inputs.push_back(0);
                }
            }
            else
            {
                inputs.push_back(closestRocks[i]->getX());
                inputs.push_back(closestRocks[i]->getY());
                inputs.push_back(closestRocks[i]->getDx());
                inputs.push_back(closestRocks[i]->getDy());
                inputs.push_back(closestRocks[i]->getSize());
            }
        }

        // feed forward into the neural net
        mNetwork.getOutputs(outputs, inputs);

        // set the variables based on the outputs
        assert(outputs.size() > 3);
        isLeftPressed = outputs[0] > 0;
        isRightPressed = outputs[1] > 0;
        isUpPressed = outputs[2] > 0;
        isSpacePressed = outputs[3] > 0;
    }

private:
    Network mNetwork;
    std::vector<double> outputs;
    std::vector<double> inputs;
};

#endif // _NNAI_H