/**************************************************************
* Game class method implementations go here
**************************************************************/
#include <list>
#include "game.h"
#include "uiDraw.h"
#include "point.h"

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
void Game :: update()
{
	// TODO collision detection

	// update the player
	mPlayer.update();

	// update the rocks
	list<Rock *>::iterator itr;
	for (itr = rocks.begin(); itr != rocks.end(); ++itr)
		(*itr)->update();

	// update the bullets
	list<Bullet *>::iterator itb;
	for (itb = bullets.begin(); itb != bullets.end(); ++itb)
		(*itb)->update();

	// update the debris
	list<Bullet *>::iterator itd;
	for (itd = debris.begin(); itd != debris.end(); ++itd)
		(*itd)->update();
}
