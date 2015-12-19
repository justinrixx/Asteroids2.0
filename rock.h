/*****************************************************
 * Rock Class
 * Asteroids are rocks
 *****************************************************/
 #include "vector.h"
 #include "uiDraw.h"
 #include "uiInteract.h"

 #ifndef _ROCK_H
 #define _ROCK_H

/* Differentiate between sizes */
 #define SMALL_ROCK 0
 #define MED_ROCK 1
 #define LARGE_ROCK 2

class Rock
{
public:
	Rock() : mVector(), rotation(0), dead(false) {};

	// getters
	float getX()   { return mVector.getX();  };
	float getY()   { return mVector.getY();  };
	float getDx()  { return mVector.getDx(); };
	float getDy()  { return mVector.getDy(); };
	bool  isDead() { return dead; };
	int getRotation() { return rotation; };

	// setters
	void setX(float x)   { mVector.setX(x);   };
	void setY(float y)   { mVector.setY(y);   };
	void setDx(float dx) { mVector.setDx(dx); };
	void setDy(float dy) { mVector.setDy(dy); };
	void setRotation(int r) { rotation = r; };
	void kill()      { dead = true;  };
	void resurrect() { dead = false; };

	// update yourself
	void update()
	{
		mVector.update();
	}

	// draw yourself
	virtual void draw() { drawSmallAsteroid(mVector.getPoint(), rotation); };

	// what size are you?
	virtual int getSize() { return SMALL_ROCK; };

protected:
	Vector mVector;
	int rotation;
	bool dead;
};

/**************************************************
* Very small differences between the Rock and its
* subclasses.
**************************************************/
class SRock : public Rock
{
public:

	virtual void draw() { drawSmallAsteroid(mVector.getPoint(), rotation); };

	virtual int getSize() { return SMALL_ROCK; };
};

class MRock : public Rock
{
public:

	virtual void draw() { drawMediumAsteroid(mVector.getPoint(), rotation); };

	virtual int getSize() { return MED_ROCK; };
};

class LRock : public Rock
{
public:

	virtual void draw() { drawLargeAsteroid(mVector.getPoint(), rotation); };

	virtual int getSize() { return LARGE_ROCK; };
};

 #endif // _SHIP_H