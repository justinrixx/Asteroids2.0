#include "point.h"
#include "uiDraw.h"
#include "uiInteract.h"

#define SIZE 50

using namespace std;

// GLOBAL!!
int rotation = 0;

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
  Point * pPoint = (Point *)p;

  drawAsteroid(*pPoint, rotation, SIZE, (rotation / 300));

  //drawCircle(*pPoint, SIZE);
  rotation++;
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my pointer type and call the display engine.
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Asteroid Types");

   // just use the default constructor
   Point pt;

   ui.run(callBack, &pt);

   return 0;
}