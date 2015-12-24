/*****************************************************
 * Ship Class
 *****************************************************/
 #include "vector.h"
 #include "uiDraw.h"
 #include "uiInteract.h"

 #ifndef _SHIP_H
 #define _SHIP_H

 #define SHIP_SIZE 8
 #define BULLET_SPEED 6

class Ship
{
public:
	Ship() { init(); };

	// getters
	float getX()   { return mVector.getX();  };
	float getY()   { return mVector.getY();  };
	float getDx()  { return mVector.getDx(); };
	float getDy()  { return mVector.getDy(); };
	bool  isDead() { return dead; };
	int getRotation() { return rotation; };
	int getSize()  { return SHIP_SIZE; };

	// setters
	void setX(float x)   { mVector.setX(x);   };
	void setY(float y)   { mVector.setY(y);   };
	void setDx(float dx) { mVector.setDx(dx); };
	void setDy(float dy) { mVector.setDy(dy); };  
	void setRotation(int r) { rotation = r; };
	void setThrusting(bool thrust) { isThrusting = thrust; };
	void kill()      { dead = true;  };
	void resurrect() { dead = false; };

	// update yourself
	virtual void update(const Interface * pUI, void * pGame);

	// update the vector
	void updateVector() { mVector.update(); };

	void init()
	{
		mVector.init();
		rotation = 0;
		isThrusting = false;
		dead = false;
	}

	// draw yourself
	virtual void draw();

private:
	Vector mVector;
	int rotation;
	bool isThrusting;
	bool dead;
};

 #endif // _SHIP_H