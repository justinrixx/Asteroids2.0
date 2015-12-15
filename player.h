/*****************************************************
 * Player Class
 *****************************************************/
 #include <iostream> // for null
 #include "ship.h"
 #include "uiInteract.h"
 #include "ai.h"

 #ifndef _PLAYER_H
 #define _PLAYER_H

class Player
{
public:
	// default constructor
	Player() : mShip(), numLives(3), nextTick(-1) {};

	/* Update yourself. This requires the interface (to get user input)
	*    and an AI object as well, in order to get input from the AI.
	*    If no AI is used, pass a null reference.
	*/
	void update(const Interface * pUI, AI * pAI);

	// draw yourself
	void draw();

private:
	Ship mShip;
	int numLives; // the number of lives
	int nextTick; // the proper time to resurrect
};

 #endif // _PLAYER_H