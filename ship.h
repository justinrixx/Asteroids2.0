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
	Ship() : mVector(), rotation(0), isThrusting(false) {};

	// getters
	float getX()  { return mVector.getX();  };
	float getY()  { return mVector.getY();  };
	float getDx() { return mVector.getDx(); };
	float getDy() { return mVector.getDy(); };
	int getRotation() { return rotation; };

	// setters
	void setX(float x) { mVector.setX(x);   };
	void setY(float y) { mVector.setY(y);   };
	void setRotation(int r) { rotation = r; };

	// update yourself
	void update(const Interface * pUI);

	// draw yourself
	void draw();

private:
	Vector mVector;
	int rotation;
	bool isThrusting;
};

 #endif // _SHIP_H