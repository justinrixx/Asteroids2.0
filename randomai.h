/*****************************************************
 * Random AI Class
 * Choose actions at random
 *****************************************************/
#include "game.h"

#ifndef _RANDOMAI_H
#define _RANDOMAI_H

#define SHOOT_FREQUENCY 30
#define THRUST_FREQUENCY 60

class RandomAI : public AI
{
public:
    RandomAI(Game *game) : AI(game) {};

protected:
    /* Really simple. Just run away from the closest
     * asteroid, and fire constantly
     */
    virtual void move()
    {
        int r = random(0, THRUST_FREQUENCY);
        isUpPressed = (r == 0);
        isSpacePressed = (r % SHOOT_FREQUENCY == 0);

        r = r % 4;
        isRightPressed = (r == 2);
        isLeftPressed = (r == 0);
    }

};

#endif // _RANDOMAI_H