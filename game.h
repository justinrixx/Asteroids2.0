/******************************************************
* The Game Class
* This class puts all the individual pieces together.
******************************************************/

#ifndef _GAME_H
#define _GAME_H

#include <list>
#include "uiDraw.h"
#include "uiInteract.h"
#include "ship.h"
#include "rock.h"
#include "player.h"
#include "bullet.h"

class AI;

class Game
{
public:

	Game() : mPlayer(), score(0) {};

	// update everything
	void update(Interface * pUI);

	// draw everything
	void draw();

	// set up the AI
	void setAI(AI * ai) { pAI = ai; };

	// get the rocks. used by the AI
	std::list<Rock *> & getRocks() { return rocks; };

	int getScore() { return score; };

private:
	AI * pAI;
	Player mPlayer;
	std::list<Rock *> rocks;
	std::list<Bullet *> bullets;
	std::list<Bullet *> debris;
	int score;
};


/******************************************************************
* The AI class lives here as well
******************************************************************/
class AI
{
public:
	AI(Game * pGame) : isUpPressed(false), isLeftPressed(false), isRightPressed(false),
		isSpacePressed(false), pGame(pGame) {};

	/* Update the AI. Don't touch this. Your hook-in point is the move method */
	void update(Ship & playerShip) { getClosestRocks(); move(); moveShip(playerShip); };

protected:
	/****************************************************
	 * OVERRIDE THIS
	 * The update method will provide you with an array
	 * of rocks. The 0th rock is the closest, the 1st is
	 * next closest, and so on. If there are fewer than
	 * 5 rocks, the rock(s) will be null. SO YES! CHECK
	 * FOR NULLS!
	 * 
	 * The job of your move method is to set some boolean
	 * values that control the player. These are
	 *
	 * 1. isSpacePressed
	 * 2. isLeftPressed
	 * 3. isRightPressed
	 * 4. isUpPressed
	 *
	 * After you have had the chance to set these flags,
	 * the moveShip method will be invoked. It simply
	 * reads the flags set by this function and translates
	 * that into updating the ship's position on the
	 * screen. You only need to implement the move()
	 * method in your AI class.
	 ***************************************************/
	virtual void move() = 0;

	/* Don't touch these */
	void getClosestRocks()
	{
		std::list<Rock *> rocks = pGame->getRocks();

		
		for (int i = 0; i < 5; i++)
			closestRocks[i] = NULL;
	}
	void moveShip(Ship & playerShip)
	{
		if (isRightPressed)
			playerShip.setRotation(playerShip.getRotation() - 7);
		if (isLeftPressed)
    		playerShip.setRotation(playerShip.getRotation() + 7);

    	if (isUpPressed)
		{
			playerShip.setDx(playerShip.getDx() - (.2 * sin(deg2rad(playerShip.getRotation()))));
	    	playerShip.setDy(playerShip.getDy() + (.2 * cos(deg2rad(playerShip.getRotation()))));
    		playerShip.setThrusting(true);
		}
		else
		playerShip.setThrusting(false);

		// now update the location
		playerShip.updateVector();

		playerShip.setRotation(playerShip.getRotation() % 360);
	}

	// The AI has an eye on where the enemy rocks are
	Rock * closestRocks[5];

	// the AI needs a pointer to the game
	Game * pGame;

	// a boolean to keep track of what buttons to push at each frame
	bool isUpPressed;
	bool isLeftPressed;
	bool isRightPressed;
	bool isSpacePressed;
};

#endif // _GAME_H
