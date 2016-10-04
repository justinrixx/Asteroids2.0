/******************************************************
* The Game Class
* This class puts all the individual pieces together.
******************************************************/

#ifndef _GAME_H
#define _GAME_H

#include <list>
#include <iostream> // for null
#include "uiDraw.h"
#include "uiInteract.h"
#include "ship.h"
#include "rock.h"
#include "player.h"
#include "bullet.h"
#include "debris.h"

#define NUM_DEBRIS 4
#define DEBRIS_RANDOM 2.0
#define INFIN 999999.9
#define NUM_CLOSEST_ROCKS 5

#define GAME_OVER_OFFSET -45

class AI;

class Game
{
public:

	Game() : mPlayer(), score(0), numSmallKilled(0), pAI(NULL) { addRock(new LRock()); addRock(new LRock()); };

	// add a bullet
	void addBullet(Bullet * pBullet)
	{
		if (bullets.size() < 6)
			bullets.push_back(pBullet);
		else
			delete pBullet;
	}

	// add a rock
	void addRock(Rock * pRock) { rocks.push_back(pRock); };

	// add debris
	void addDebris(Debris * pDebris) { debris.push_back(pDebris); };

	// update everything
	void update(const Interface * pUI);

	// draw everything
	void draw();

	// set up the AI
	void setAI(AI * ai) { pAI = ai; };

	// reset the game state
	void reset();

	bool isGameOver() { return mPlayer.isGameOver(); };

	// get the rocks. used by the AI
	std::list<Rock *> & getRocks() { return rocks; };

	int getScore() { return score; };
	int getNumBullets() { return bullets.size(); };

	void setSeed(int s) { this->seed = s; };

private:
	AI * pAI;
	Player mPlayer;
	std::list<Rock *> rocks;
	std::list<Bullet *> bullets;
	std::list<Debris *> debris;
	int score;
	int numSmallKilled;
	int seed;
};


/******************************************************************
* The AI class lives here as well
******************************************************************/
class AI
{
public:
	AI(Game * game) : isUpPressed(false), isLeftPressed(false), isRightPressed(false),
		isSpacePressed(false), pGame(game) {};

	/* Update the AI. Don't touch this. Your hook-in point is the move method */
	void update(Ship & playerShip) { getClosestRocks(playerShip); move(playerShip); moveShip(playerShip); };

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
	virtual void move(const Ship & playerShip) = 0;

	/* Don't touch these */
	void getClosestRocks(Ship & playerShip)
	{
		double distances[NUM_CLOSEST_ROCKS];

		std::list<Rock *> rocks = pGame->getRocks();

		// set the distances to infinity
		for (int i = 0; i < NUM_CLOSEST_ROCKS; i++)
		{
			distances[i] = INFIN;
		}

		// get all the distances
		std::list<Rock *>::iterator itr;
		for (itr = rocks.begin(); itr != rocks.end(); ++itr)
		{
			for (int i = 0; i < NUM_CLOSEST_ROCKS; i++)
			{
				closestRocks[i] = NULL;
			}

			double distance = getDistance((*itr)->getX(), (*itr)->getY(), playerShip.getX(), playerShip.getY());

			for (int i = NUM_CLOSEST_ROCKS - 1; i > 0; i--)
			{
				if (distance < distances[i])
				{
					// copy over unless at the end
					if (i < NUM_CLOSEST_ROCKS - 1)
					{
						distances[i + 1] = distances[i];
						closestRocks[i + 1] = closestRocks[i];
					}

					if (distance >= distances[i - 1])
					{
						distances[i] = distance;
						closestRocks[i] = *itr;
					}
					else
					{
						if (i == 1)
						{
							distances[1] = distances[0];
							closestRocks[1] = closestRocks[0];

							distances[0] = distance;
							closestRocks[0] = *itr;
						}
					}
				}
				else
					break;
			}
		}
	}
	/* Not real distance, but we're just using it to see what's closest */
	double getDistance(float x1, float y1, float x2, float y2)
	{
		return pow((x1 - x2), 2) + pow((y1 - y2), 2);
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
		{
			playerShip.setThrusting(false);
		}

		if (isSpacePressed)
		{
			Bullet * p = new Bullet();
			p->setX(playerShip.getX() - playerShip.getSize() * sin(deg2rad(playerShip.getRotation())));
			p->setY(playerShip.getY() + playerShip.getSize() * cos(deg2rad(playerShip.getRotation())));
			p->setDx(playerShip.getDx() - BULLET_SPEED * sin(deg2rad(playerShip.getRotation())));
			p->setDy(playerShip.getDy() + BULLET_SPEED * cos(deg2rad(playerShip.getRotation())));

			pGame->addBullet(p);
		}

		// now update the location
		playerShip.updateVector();

		playerShip.setRotation(playerShip.getRotation() % 360);
	}

	// The AI has an eye on where the enemy rocks are
	Rock * closestRocks[NUM_CLOSEST_ROCKS];

	// the AI needs a pointer to the game
	Game * pGame;

	// a boolean to keep track of what buttons to push at each frame
	bool isUpPressed;
	bool isLeftPressed;
	bool isRightPressed;
	bool isSpacePressed;
};

#endif // _GAME_H
