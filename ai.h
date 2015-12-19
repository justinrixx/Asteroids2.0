/*****************************************************
 * AI Class
 * This class is essentially just an interface. To make
 * a concrete AI, extend this class and implement the
 * move() method.
 *****************************************************/
 #include "ship.h"

 #ifndef _AI_H
 #define _AI_H

class AI
{
public:
	AI() : isUpPressed(false), isLeftPressed(false), isRightPressed(false),
		isSpacePressed(false) {};

	/* Update the AI. Don't touch this. Your hook-in point is the move method */
	void update(Ship & playerShip) { getClosestRocks(); move(playerShip); };

protected:
	/* OVERRIDE THIS */
	virtual void move(Ship & playerShip) = 0;

	/* Don't touch this */
	void getClosestRocks();

	// TODO The AI needs a notion of enemy rocks
	// Rock[5] closestRocks;
	// TODO the AI needs a pointer to the game

	// a boolean to keep track of what buttons to push at each frame
	bool isUpPressed;
	bool isLeftPressed;
	bool isRightPressed;
	bool isSpacePressed;
};

 #endif // _AI_H