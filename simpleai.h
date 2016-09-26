/*****************************************************
 * Simple AI Class
 * Just shoot
 *****************************************************/
 #include "game.h"

 #ifndef _SIMPLEAI_H
 #define _SIMPLEAI_H

class SimpleAI : public AI
{
public:
	SimpleAI(Game *game) : AI(game) {};

protected:
	/* Really simple. Just run away from the closest
	 * asteroid, and fire constantly
	 */
	virtual void move(const Ship & notUsed)
	{
		// spin in a circle and shoot
		isRightPressed = true;
		isSpacePressed = !isSpacePressed;
	}

};

 #endif // _SIMPLEAI_H
