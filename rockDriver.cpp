#include <list>
#include "rock.h"
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
	// cast the list back to the correct type
  list<Rock *> * pRocks = (list<Rock *> *)p;

  list<Rock *>::iterator it = pRocks->begin();
  list<Rock *>::iterator end = pRocks->end();

  for (; it != end; ++it)
  {
    (*it)->update();
    (*it)->setRotation((*it)->getRotation() + 3);
    (*it)->draw();
  }
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my pointer type and call the display engine.
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Player Test");

   list<Rock *> rocks;
   
   Rock * tempRock = new LRock();
   rocks.push_back(tempRock);
   tempRock->setX(13);
   tempRock->setY(-2);
   tempRock->setDx(3);
   tempRock->setDy(1);

   tempRock = new MRock();
   rocks.push_back(tempRock);
   tempRock->setX(-11);
   tempRock->setY(-92);
   tempRock->setDx(-3);
   tempRock->setDy(5);

   tempRock = new SRock();
   rocks.push_back(tempRock);
   tempRock->setX(0);
   tempRock->setY(0);
   tempRock->setDx(1);
   tempRock->setDy(-3);

   ui.run(callBack, &rocks);

   return 0;
}