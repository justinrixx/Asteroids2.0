/*****************************************************
 * Vector Class
 * A vector is just a point, plus direction.
 *****************************************************/
 //#include <iostream>

 #include <cmath>
 #include <stdlib.h>
 #include "point.h"

 #ifndef _VECTOR_H
 #define _VECTOR_H

class Vector
{
public:
	// constructors
	Vector() : pt(), dx(0.0), dy(0.0) {};
	Vector(const Vector & v) : pt(v.pt), dx(v.dx), dy(v.dy) {};
	Vector(float x, float y, float dx, float dy) : dx(dx), dy(dy)
	 { pt.setX(x); pt.setY(y); };

	// getters
	float getX()  const { return pt.getX(); };
	float getY()  const { return pt.getY(); };
	float getDx() const { return dx; };
	float getDy() const { return dy; };
	const Point & getPoint() const { return pt; };

	// setters
	void setX( float x ) { pt.setX(x); };
	void setY( float y ) { pt.setY(y); };
	void setDx(float dx) { this->dx = dx; };
	void setDy(float dy) { this->dy = dy; };

	// update the position on the screen
	void update()
	{
		// handle screen wrapping
		if (pt.getX() < pt.getXMin())
			pt.setX(pt.getXMax());
		if (pt.getX() > pt.getXMax())
			pt.setX(pt.getXMin());
		if (pt.getY() < pt.getYMin())
			pt.setY(pt.getYMax());
		if (pt.getY() > pt.getYMax())
			pt.setY(pt.getYMin());

		
		setX(pt.getX() + dx);
		setY(pt.getY() + dy);
	}

	float minDistance(const Vector & rhs) const
	{
		float distance = 0;
   		float maxD = max(abs(dx), abs(dy), abs(rhs.dx), abs(rhs.dy));

   		//for the first pixel
		float minD = (((pt.getX() - rhs.getX()) * (pt.getX() - rhs.getX()))
			+ ((pt.getY() - rhs.getY()) * (pt.getY() - rhs.getY())));

		for (int i = 1; i < maxD; i++) //for every pixel after that
		{
			distance = ((((pt.getX() + dx * i / maxD) - (rhs.getX() + rhs.dx * i / maxD)) 
				* ((pt.getX() + dx * i / maxD) - (rhs.getX() + rhs.dx * i / maxD)))
                   + (((pt.getY() + dy * i / maxD) - (rhs.getY() + rhs.dy * i / maxD)) 
                   	* ((pt.getY() + dy * i / maxD) - (rhs.getY() + rhs.dy * i / maxD))));

      		minD = min(minD, distance);
   		}

   		//std::cerr << "minD: " << minD << "  sqrt(minD): " << sqrt(minD) << std::endl;
   		return sqrt(minD);
	}

	void init()
	{
		pt.init();
		dx = 0.0;
		dy = 0.0;
	}

private:
	Point pt;
	float dx;
	float dy;

	/*** Some utility methods used by minDistance ***/
	float min(const float a, const float b) const
	{
 		if (a < b)
 			return a;
 		return b;
	}

	float max(const float a, const float b) const
	{
 		if (a > b)
 			return a;
 		return b;
 	}

 	float max(const float a, const float b, const float c, const float d) const
 	{
 		float ab = max(a, b);
 		float cd = max(c, d);
 		if (ab > cd)
 			return ab;
 		return cd;
	}
};

 #endif // _VECTOR_H