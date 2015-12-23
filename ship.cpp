/*************************************************
* All the ship's interesting stuff happens here
*************************************************/
#include "ship.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "point.h"

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
	// double point_max
	float dpm = POINT_MAX * 2.0;

	// draw where you are
	Point temp = mVector.getPoint();
	drawShip(temp, rotation, isThrusting);

	// to the right
	temp.setX(temp.getX() + dpm);
	drawShip(temp, rotation, isThrusting);
	temp.setX(temp.getX() - dpm);

	// to the left
	temp.setX(temp.getX() - dpm);
	drawShip(temp, rotation, isThrusting);
	temp.setX(temp.getX() + dpm);

	// above
	temp.setY(temp.getY() + dpm);
	drawShip(temp, rotation, isThrusting);
	temp.setY(temp.getY() - dpm);

	// below
	temp.setY(temp.getY() - dpm);
	drawShip(temp, rotation, isThrusting);
}
