/*****************************************************
 * Ship Class
 *****************************************************/
 #include "vector.h"
 #include "uiDraw.h"
 #include "uiInteract.h"

 #ifndef _SHIP_H
 #define _SHIP_H

class Ship
{
public:
	Ship() : mVector(), rotation(0), isThrusting(false), dead(false) {};

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
	void setThrusting(bool thrust) { isThrusting = thrust; };
	void kill()      { dead = true;  };
	void resurrect() { dead = false; };

	// update yourself
	virtual void update(const Interface * pUI);

	// update the vector
	void updateVector() { mVector.update(); };

	// draw yourself
	virtual void draw();

private:
	Vector mVector;
	int rotation;
	bool isThrusting;
	bool dead;
};

 #endif // _SHIP_H