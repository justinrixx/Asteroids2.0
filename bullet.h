/*****************************************************
 * Bullet class
 *****************************************************/
 #include "vector.h"
 #include "uiDraw.h"

 #ifndef _BULLET_H
 #define _BULLET_H

/* Differentiate between sizes */
 #define BULLET_LIFE 70

class Bullet
{
public:
	Bullet() : mVector(), dead(false), life(BULLET_LIFE) {};

	// getters
	float getX()   { return mVector.getX();  };
	float getY()   { return mVector.getY();  };
	float getDx()  { return mVector.getDx(); };
	float getDy()  { return mVector.getDy(); };
	bool  isDead() { return dead; };

	// setters
	void setX(float x)   { mVector.setX(x);   };
	void setY(float y)   { mVector.setY(y);   };
	void setDx(float dx) { mVector.setDx(dx); };
	void setDy(float dy) { mVector.setDy(dy); };
	void kill()      { dead = true;  };
	void resurrect() { dead = false; life = BULLET_LIFE; };

	// update yourself
	void update()
	{
		if (life <= 0)
		{
			dead = true;
			return;
		}

		mVector.update();
		life--;
	}

	// draw yourself
	void draw() { drawDot(mVector.getPoint()); };

protected:
	Vector mVector;
	int life;
	bool dead;
};

 #endif // _BULLET_H