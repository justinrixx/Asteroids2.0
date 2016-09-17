/*****************************************************
 * Debris class
 *****************************************************/
#include "bullet.h"

#ifndef _DEBRIS_H
#define _DEBRIS_H

#define DEBRIS_SIZE 4

class Debris : public Bullet
{
public:
    Debris() : Bullet(), rotation(random(0, 359)), dr(random(-20, 20)) {};

    // update yourself
    void update()
    {
        Bullet::update();

        rotation += dr;
        rotation = rotation % 360;
    }

    // draw yourself
    void draw() { drawRect(mVector.getPoint(), DEBRIS_SIZE, DEBRIS_SIZE, rotation); };

protected:
    int rotation;
    int dr;
};

#endif // _DEBRIS_H