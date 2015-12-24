#include <iostream>
#include <list>
#include "uiDraw.h"
#include "uiInteract.h"
#include "bullet.h"

using namespace std;

void callBack(const Interface *pUI, void *p)
{
  list<Bullet *> * bullets;

  bullets = (list<Bullet *> *)p;

  list<Bullet *>::iterator it = bullets->begin();

  while (it != bullets->end())
  {
    Bullet * temp = *it;

    // if it's dead, get rid of it
    if (temp->isDead())
    {
      delete temp;
      it = bullets->erase(it);
      // don't increment
    }

    else
    {
      temp->update();
      temp->draw();
      ++it; // increment
    }

  }

}

/***********************************************
 * Main has to initialize the objects to be used
 * and then passes control to the Interface class.
 **********************************************/
int main(int argc, char ** argv)
{
  list<Bullet *> * bullets = new list<Bullet *>();
  Bullet * temp = new Bullet();
  temp->setDx(random(-3, 3));
  temp->setDy(random(-3, 3));

  bullets->push_back(temp);

  temp = new Bullet();
  temp->setDx(random(-3, 3));
  temp->setDy(random(-3, 3));

  bullets->push_back(temp);

  Interface ui(argc, argv, "Bullet Test");
  ui.run(callBack, bullets);

  return 0;
}