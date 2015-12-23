/*****************************************************
 * Vector Class
 * A vector is just a point, plus direction.
 *****************************************************/
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
	float getX()  { return pt.getX(); };
	float getY()  { return pt.getY(); };
	float getDx() { return dx; };
	float getDy() { return dy; };
	const Point & getPoint() { return pt; };

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

	// TODO minDistance
	float minDistance(const Vector & rhs)
	{
		return 0.0;
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
};

 #endif // _VECTOR_H