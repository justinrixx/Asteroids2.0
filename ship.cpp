/*************************************************
* All the ship's interesting stuff happens here
*************************************************/
#include "ship.h"
#include "uiInteract.h"
#include "uiDraw.h"

/*****************************************
* Handle user input and update the position
*****************************************/
void Ship :: update(const Interface * pUI)
{
	if (pUI->isRight())
		rotation -= 7;
	if (pUI->isLeft())
    	rotation += 7;

	if (pUI->isUp())
	{
    	mVector.setDx(mVector.getDx() - (.2 * sin(deg2rad(rotation))));
    	mVector.setDy(mVector.getDy() + (.2 * cos(deg2rad(rotation))));
    	isThrusting = true;
	}

	else
		isThrusting = false;

	// now update the location
	mVector.update();

	rotation = rotation % 360;
}

/**********************************************
* Delegate the drawing to the library function
**********************************************/
void Ship :: draw()
{ 
	drawShip(mVector.getPoint(), rotation, isThrusting);
}
