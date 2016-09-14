/*****************************************************
 * Neural Net AI Class
 * Do what the neural net says to
 *****************************************************/
#include "game.h"

#ifndef _NNAI_H
#define _NNAI_H

class NNAI : public AI
{
public:
    NNAI(Game *game /* neural net weights */) : AI(game) { /* init NN */ };

protected:
    virtual void move()
    {
        // feed forward into the neural net

        // set the variables based on the outputs
    }

};

#endif // _NNAI_H