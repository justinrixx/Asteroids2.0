#include "ship.h"
#include "uiDraw.h"
#include "uiInteract.h"

using namespace std;

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
	// cast the ship back to the correct type
    Ship *pShip = (Ship *)p;

    // update it
    pShip->update(pUI);

   	// Draw the ship
   	pShip->draw();
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my pointer type and call the display engine.
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "SHIP TEST!");
   Ship ship;
   ui.run(callBack, &ship);

   return 0;
}