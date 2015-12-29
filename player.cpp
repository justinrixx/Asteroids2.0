/*****************************************************
 * Player Class method definitions
 *****************************************************/
 #include <iostream> // for null
 #include <ctime>    // for clock()
 #include "player.h"
 #include "ship.h"
 #include "uiInteract.h"
 #include "uiDraw.h"
 #include "game.h"
 #include "point.h"

/* Update yourself. This requires the interface (to get user input)
*    and an AI object as well, in order to get input from the AI.
*    If no AI is used, pass a null reference.
*/
void Player :: update(const Interface * pUI, AI * pAI, void * pGame)
{
	// First of all, make sure you're not dead
	if (!mShip.isDead())
	{
		// If no AI, use the keyboard
		if (pAI == NULL)
			mShip.update(pUI, pGame);
		
		// handle the AI case
		else
		{
			pAI->update(mShip);
		}
	}
	// otherwise, the ship is dead
	else
	{
		// if we just died
		if (nextTick == NULL_TICK)
		{
			nextTick = (clock() / 1000) + 2;
		}
		
		// if it's time to resurrect
		else if ((clock() / 1000) >= nextTick && numLives > 0)
		{
			--numLives;
			init();
		}
		// otherwise, do nothing
	}
}

/*******************************************************************
* Draw
* This requires drawing the ship where it is, plus ships in the corner
* for the number of lives that remain.
*******************************************************************/
void Player :: draw()
{
	if (!mShip.isDead())
		mShip.draw();

	// draw the extra lives
	for (int i = 0; i < numLives; i++)
		drawShip(Point((POINT_MAX - (i + 1) * 20.0), -POINT_MAX + 20.0), 0, false);
}
