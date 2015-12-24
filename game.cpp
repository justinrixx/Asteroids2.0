/**************************************************************
* Game class method implementations go here
**************************************************************/
#include <list>
#include "game.h"
#include "uiDraw.h"
#include "point.h"

using namespace std;

/*************************************************************
* Game :: draw
* This method draws all the elements to the screen
*************************************************************/
void Game :: draw()
{
	// draw the player
	mPlayer.draw();

	// draw the rocks
	list<Rock *>::iterator itr;
	for (itr = rocks.begin(); itr != rocks.end(); ++itr)
		(*itr)->draw();

	// draw the bullets
	list<Bullet *>::iterator itb;
	for (itb = bullets.begin(); itb != bullets.end(); ++itb)
		(*itb)->draw();

	// draw the debris
	list<Bullet *>::iterator itd;
	for (itd = debris.begin(); itd != debris.end(); ++itd)
		(*itd)->draw();

	// draw the score
	drawNumber(Point(POINT_MAX - 45, POINT_MAX - 5), score);
}

/************************************************************
* Game :: update
* This method is called each frame, and ensures that all the
* components of the game are updated. It handles collisions
* as well.
************************************************************/
void Game :: update(const Interface * pUI)
{
	// TODO collision detection

	// update the player
	mPlayer.update(pUI, pAI, this);

	// update the rocks
	list<Rock *>::iterator itr = rocks.begin();
 	while (itr != rocks.end())
 	{
    	Rock * temp = *itr;

    	// if it's dead, get rid of it
    	if (temp->isDead())
    	{
     		delete temp;
    		itr = rocks.erase(itr);
    		// don't increment
   		}

		else
		{
    		temp->update();
    		temp->draw();
    		++itr; // increment
		}
	}

	// update the bullets
	list<Bullet *>::iterator itb = bullets.begin();
 	while (itb != bullets.end())
 	{
    	Bullet * temp = *itb;

    	// if it's dead, get rid of it
    	if (temp->isDead())
    	{
     		delete temp;
    		itb = bullets.erase(itb);
    		// don't increment
   		}

		else
		{
    		temp->update();
    		temp->draw();
    		++itb; // increment
		}
	}

	// update the debris
	list<Bullet *>::iterator itd = debris.begin();
 	while (itd != debris.end())
 	{
    	Bullet * temp = *itd;

    	// if it's dead, get rid of it
    	if (temp->isDead())
    	{
     		delete temp;
    		itd = debris.erase(itd);
    		// don't increment
   		}

		else
		{
    		temp->update();
    		temp->draw();
    		++itd; // increment
		}
	}
}
