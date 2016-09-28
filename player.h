/*****************************************************
 * Player Class
 * The player ship is encapsulated within the player
 * class
 *****************************************************/
 #ifndef _PLAYER_H
 #define _PLAYER_H

 #include <iostream> // for null
 #include "ship.h"
 #include "uiInteract.h"

 #define NULL_TICK -1
 #define TICK_DELAY 20

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
	void update(const Interface * pUI, AI * pAI, void * pGame);

	// draw yourself
	void draw();

	// are you dead?
	bool isDead() { return mShip.isDead(); };

	// send the kill signal
	void kill() { mShip.kill(); };

	/* The game goes until there are no more lives */
	bool isGameOver() { return !numLives; };

	const Vector & getVector() const { return mShip.getVector(); };

	void init(int numLives) { this->numLives = numLives; init(); };

private:
	void init() { mShip.init(); nextTick = NULL_TICK; };

	Ship mShip;
	int numLives; // the number of lives
	int nextTick; // the proper time to resurrect
};

 #endif // _PLAYER_H