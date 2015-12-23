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
 #define SMALL_SIZE 8
 #define MED_SIZE 12
 #define LARGE_SIZE 16

class Rock
{
public:
	//                                             random type
	Rock() : mVector(), rotation(0), dead(false) { type = random(0, 2); };

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
	virtual void draw() { drawAsteroid(mVector.getPoint(), rotation, SMALL_SIZE, type); };

	// what size are you?
	virtual int getSize() { return SMALL_SIZE; };

protected:
	Vector mVector;
	int rotation;
	bool dead;
	int type;
};

/**************************************************
* Very small differences between the Rock and its
* subclasses.
**************************************************/
class SRock : public Rock
{
public:

	virtual void draw() { drawAsteroid(mVector.getPoint(), rotation, SMALL_SIZE, type); };

	virtual int getSize() { return SMALL_SIZE; };
};

class MRock : public Rock
{
public:

	virtual void draw() { drawAsteroid(mVector.getPoint(), rotation, MED_SIZE, type); };

	virtual int getSize() { return MED_SIZE; };
};

class LRock : public Rock
{
public:

	virtual void draw() { drawAsteroid(mVector.getPoint(), rotation, LARGE_SIZE, type); };

	virtual int getSize() { return LARGE_SIZE; };
};

 #endif // _SHIP_H