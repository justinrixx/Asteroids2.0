/*****************************************************
 * Rock Class
 * Asteroids are rocks
 *****************************************************/
 #include "vector.h"
 #include "uiDraw.h"
 #include "uiInteract.h"
 #include "point.h"

 #ifndef _ROCK_H
 #define _ROCK_H

/* Differentiate between sizes */
 #define SMALL_SIZE 8
 #define MED_SIZE 14
 #define LARGE_SIZE 22

#define LARGE_RANDOM 2.0
#define MED_RANDOM 2.5
#define SMALL_RANDOM 3.0
#define SMALL_POINTS 2
#define MED_POINTS 4
#define LARGE_POINTS 7

class Rock
{
public:
	Rock() : mVector(), dead(false)
	{
		rotation = random(0, 360);
		dr = random(-8, 8);
		type = random(0, 2);
		mVector.setX(POINT_MAX);
		mVector.setY(random(-POINT_MAX, POINT_MAX));
		mVector.setDx(random(-LARGE_RANDOM, LARGE_RANDOM));
		mVector.setDy(random(-LARGE_RANDOM, LARGE_RANDOM));
	}

	// getters
	float getX()               const { return mVector.getX();  };
	float getY()               const { return mVector.getY();  };
	float getDx()              const { return mVector.getDx(); };
	float getDy()              const { return mVector.getDy(); };
	const Vector & getVector() const { return mVector; }
	bool  isDead()             const { return dead; };
	int getRotation()          const { return rotation; };

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
		rotation += dr;
		rotation = rotation % 360;
	}

	// draw yourself
	void draw()
	{
		// double point_max
		float dpm = POINT_MAX * 2.0;

		// draw where you are
		Point temp = mVector.getPoint();
		drawAsteroid(temp, rotation, getSize(), type);

		// to the right
		temp.setX(temp.getX() + dpm);
		drawAsteroid(temp, rotation, getSize(), type);
		temp.setX(temp.getX() - dpm);

		// to the left
		temp.setX(temp.getX() - dpm);
		drawAsteroid(temp, rotation, getSize(), type);
		temp.setX(temp.getX() + dpm);

		// above	
		temp.setY(temp.getY() + dpm);
		drawAsteroid(temp, rotation, getSize(), type);
		temp.setY(temp.getY() - dpm);

		// below
		temp.setY(temp.getY() - dpm);
		drawAsteroid(temp, rotation, getSize(), type);
	}

	// what size are you?
	virtual float getSize() { return SMALL_SIZE; };

protected:
	Vector mVector;
	int rotation;
	int dr;
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

	SRock() { Rock(); };

	virtual float getSize() { return SMALL_SIZE; };
};

class MRock : public Rock
{
public:

	MRock() { Rock(); };

	virtual float getSize() { return MED_SIZE; };
};

class LRock : public Rock
{
public:

	LRock() { Rock(); };

	virtual float getSize() { return LARGE_SIZE; };
};

 #endif // _ROCK_H