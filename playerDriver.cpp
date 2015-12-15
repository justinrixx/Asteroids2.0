#include <iostream> // for NULL
#include "player.h"
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
    Player * pPlay = (Player *)p;

    // update it
    pPlay->update(pUI, NULL);

   	// Draw the ship
   	pPlay->draw();
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my pointer type and call the display engine.
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Player Test");
   Player player;
   ui.run(callBack, &player);

   return 0;
}