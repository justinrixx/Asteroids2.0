/*****************************************************
 * Player Class
 *****************************************************/
 #include <iostream> // for null
 #include "ship.h"
 #include "uiInteract.h"

 #ifndef _PLAYER_H
 #define _PLAYER_H

 #define NULL_TICK -1

class AI;

class Player
{
public:
	// default constructor
	Player() : numLives(3) { init(); };

	/* Update yourself. This requires the interface (to get user input)
	*    and an AI object as well, in order to get input from the AI.
	*    If no AI is used, pass a null reference.
	*/
	void update(const Interface * pUI, AI * pAI);

	// draw yourself
	void draw();

	/* The game goes until there are no more lives */
	bool isGameOver() { return !numLives; };

private:
	void init() { mShip.init(); nextTick = NULL_TICK; };

	Ship mShip;
	int numLives; // the number of lives
	int nextTick; // the proper time to resurrect
};

 #endif // _PLAYER_H