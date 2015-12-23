/*****************************************************
 * Player Class method definitions
 *****************************************************/
 #include <iostream> // for null
 #include <ctime>    // for clock()
 #include "player.h"
 #include "ship.h"
 #include "uiInteract.h"
 #include "game.h"

/* Update yourself. This requires the interface (to get user input)
*    and an AI object as well, in order to get input from the AI.
*    If no AI is used, pass a null reference.
*/
void Player :: update(const Interface * pUI, AI * pAI)
{
	// First of all, make sure you're not dead
	if (!mShip.isDead())
	{
		// If no AI, use the keyboard
		if (pAI == NULL)
			mShip.update(pUI);
		
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
			nextTick = (clock() / 1000) + 4;
		
		// if it's time to resurrect
		else if ((clock() / 1000) >= nextTick)
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
	mShip.draw();

	// TODO draw the extra lives
}

