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
	/**********************
	* Collision Detection
	***********************/
	// bullets and rocks
	list<Rock *>::iterator itr;
	list<Bullet *>::iterator itb;

	for (itr = rocks.begin(); itr != rocks.end(); ++itr)
	{
		// make sure the rock isn't dead
		if (!(*itr)->isDead())
		{
			for (itb = bullets.begin(); itb != bullets.end(); ++itb)
			{
				// make sure the bullet isn't dead
				if (!(*itb)->isDead())
				{
					if ((*itr)->getVector().minDistance((*itb)->getVector()) <= (*itr)->getSize())
					{
						Rock * src = *itr;
						// large rock, add two medium ones
						if ((*itr)->getSize() == LARGE_SIZE)
						{
							for (int i = 0; i < 2; i++)
							{
								Rock * p = new MRock();
								p->setX(src->getX());
								p->setY(src->getY());
								p->setDx(src->getDx() + random(-MED_RANDOM, MED_RANDOM));
								p->setDy(src->getDy() + random(-MED_RANDOM, MED_RANDOM));

								addRock(p);
							}
						}
						// medium rock, add three small ones
						else if ((*itr)->getSize() == MED_SIZE)
						{
							for (int i = 0; i < 3; i++)
							{
								Rock * p = new SRock();
								p->setX(src->getX());
								p->setY(src->getY());
								p->setDx(src->getDx() + random(-SMALL_RANDOM, SMALL_RANDOM));
								p->setDy(src->getDy() + random(-SMALL_RANDOM, SMALL_RANDOM));

								addRock(p);
							}
						}

						// some debris for eye candy
						for (int i = 0; i < NUM_DEBRIS; i++)
						{
							Bullet * p = new Bullet();
							p->setX(src->getX());
							p->setY(src->getY());
							p->setDx(src->getDx() + random(-DEBRIS_RANDOM, DEBRIS_RANDOM));
							p->setDy(src->getDy() + random(-DEBRIS_RANDOM, DEBRIS_RANDOM));

							addDebris(p);
						}

						// kill them both
						(*itr)->kill();
						(*itb)->kill();
					}
				}
			}
		}
	}

	// rocks and ship
	if (!mPlayer.isDead())
	{
		for (itr = rocks.begin(); itr != rocks.end(); ++itr)
		{
			// make sure the rock isn't dead
			if (!(*itr)->isDead())
			{
				if ((*itr)->getVector().minDistance(mPlayer.getVector()) <= (*itr)->getSize())
				{
					Rock * src = *itr;
					// large rock, add two medium ones
					if ((*itr)->getSize() == LARGE_SIZE)
					{
						for (int i = 0; i < 2; i++)
						{
							Rock * p = new MRock();
							p->setX(src->getX());
							p->setY(src->getY());
							p->setDx(src->getDx() + random(-MED_RANDOM, MED_RANDOM));
							p->setDy(src->getDy() + random(-MED_RANDOM, MED_RANDOM));

							addRock(p);
						}
					}
					// medium rock, add three small ones
					else if ((*itr)->getSize() == MED_SIZE)
					{
						for (int i = 0; i < 3; i++)
						{
							Rock * p = new SRock();
							p->setX(src->getX());
							p->setY(src->getY());
							p->setDx(src->getDx() + random(-SMALL_RANDOM, SMALL_RANDOM));
							p->setDy(src->getDy() + random(-SMALL_RANDOM, SMALL_RANDOM));

							addRock(p);
						}
					}

					// some debris for eye candy
					for (int i = 0; i < NUM_DEBRIS; i++)
					{
						Bullet * p = new Bullet();
						p->setX(src->getX());
						p->setY(src->getY());
						p->setDx(src->getDx() + random(-DEBRIS_RANDOM, DEBRIS_RANDOM));
						p->setDy(src->getDy() + random(-DEBRIS_RANDOM, DEBRIS_RANDOM));

						addDebris(p);
					}

					// kill the rock and the ship
					(*itr)->kill();
					mPlayer.kill();
				}
			}
		}
	}

	/**********************
	* Update Locations
	***********************/
	// update the player
	mPlayer.update(pUI, pAI, this);

	// update the rocks
	itr = rocks.begin();
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
	itb = bullets.begin();
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
