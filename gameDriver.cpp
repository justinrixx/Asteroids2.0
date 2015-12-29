#include <iostream>
#include "game.h"
#include "uiDraw.h"
#include "uiInteract.h"

using namespace std;

/*************************************
 * Super simple callback function. Just
 * update the game, then draw it.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
	// cast the pointer back to the correct type
  Game * pGame = (Game *)p;

  // update the game
  pGame->update(pUI);

  // draw the game
  pGame->draw();

}

/***********************************************
 * Main has to initialize the objects to be used
 * and then passes control to the Interface class.
 **********************************************/
int main(int argc, char ** argv)
{
  // instantiate the game object
  Game * pGame = new Game();

  // instantiate an AI
  // SimpleAI ai(pGame);

  // the game needs a reference to the AI
  pGame->setAI(NULL);
  pGame->addRock(new LRock());
  pGame->addRock(new LRock());

  Interface ui(argc, argv, "Game Test");
  ui.run(callBack, pGame);

  return 0;
}