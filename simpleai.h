/*****************************************************
 * Simple AI Class
 * Just run away from the closest asteroid
 *****************************************************/
 #include "ai.h"

 #ifndef _SIMPLEAI_H
 #define _SIMPLEAI_H

class SimpleAI : public AI
{
public:
	SimpleAI(Game * pGame) { AI(pGame); };

protected:
	/* Really simple. Just run away from the closest
	 * asteroid, and fire constantly
	 */
	virtual void move()
	{
		isSpacePressed = true; // always fire

		// TODO the moving part
	}

};

 #endif // _SIMPLEAI_H
