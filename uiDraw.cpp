/***********************************************************************        
 * Source File:                                                                 
 *    User Interface Draw : put pixels on the screen                            
 * Author:                                                                      
 *    Br. Helfrich                                                              
 * Summary:                                                                     
 *    This is the code necessary to draw on the screen. We have a collection    
 *    of procedural functions here because each draw function does not          
 *    retain state. In other words, they are verbs (functions), not nouns       
 *    (variables) or a mixture (objects)                                        
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock

#define LINUX
//#define MAC_XCODE
//#define WIN_VISUAL_STUDIO

#ifdef MAC_XCODE
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // MAC_XCODE

#ifdef LINUX
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // LINUX

#ifdef WIN_VISUAL_STUDIO
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#endif // WIN_VISUAL_STUDIO


#include "point.h"
#include "uiDraw.h"

using namespace std;

/*********************************************
 * NUMBER OUTLINES
 * We are drawing the text for score and things
 * like that by hand to make it look "old school."
 * These are how we render each individual charactger.
 * Note how -1 indicates "done".  These are paired
 * coordinates where the even are the x and the odd
 * are the y and every 2 pairs represents a point
 ********************************************/
const char NUMBER_OUTLINES[10][20] =
{
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   0,10,  0, 0,  -1,-1, -1,-1},//0
  {7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//1
  {0, 0,  7, 0,   7, 0,  7, 5,   7, 5,  0, 5,   0, 5,  0,10,   0,10,  7,10},//2
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   4, 5,  7, 5,  -1,-1, -1,-1},//3
  {0, 0,  0, 5,   0, 5,  7, 5,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1},//4
  {7, 0,  0, 0,   0, 0,  0, 5,   0, 5,  7, 5,   7, 5,  7,10,   7,10,  0,10},//5
  {7, 0,  0, 0,   0, 0,  0,10,   0,10,  7,10,   7,10,  7, 5,   7, 5,  0, 5},//6
  {0, 0,  7, 0,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//7
  {0, 0,  7, 0,   0, 5,  7, 5,   0,10,  7,10,   0, 0,  0,10,   7, 0,  7,10},//8
  {0, 0,  7, 0,   7, 0,  7,10,   0, 0,  0, 5,   0, 5,  7, 5,  -1,-1, -1,-1} //9
};

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawDigit(const Point & topLeft, char digit)
{
   // we better be only drawing digits
   assert(isdigit(digit));
   if (!isdigit(digit))
      return;

   // compute the row as specified by the digit
   int r = digit - '0';
   assert(r >= 0 && r <= 9);

   // go through each segment.
   for (int c = 0; c < 20 && NUMBER_OUTLINES[r][c] != -1; c += 4)
   {
      assert(NUMBER_OUTLINES[r][c    ] != -1 &&
             NUMBER_OUTLINES[r][c + 1] != -1 &&
             NUMBER_OUTLINES[r][c + 2] != -1 &&
             NUMBER_OUTLINES[r][c + 3] != -1);

      //Draw a line based off of the num structure for each number
      Point start;
      start.setX(topLeft.getX() + NUMBER_OUTLINES[r][c]);
      start.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 1]);
      Point end;
      end.setX(topLeft.getX() + NUMBER_OUTLINES[r][c + 2]);
      end.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 3]);
         
      drawLine(start, end);
   }
}

/*************************************************************************
 * DRAW NUMBER
 * Display an positive integer on the screen using the 7-segment method
 *   INPUT  topLeft   The top left corner of the character
 *          digit     The digit we are rendering: '0' .. '9'
 *************************************************************************/
void drawNumber(const Point & topLeft, int number)
{
   // our cursor, if you will. It will advance as we output digits
   Point point = topLeft;
   
   // is this negative
   bool isNegative = (number < 0);
   number *= (isNegative ? -1 : 1);
   
   // render the number as text
   ostringstream sout;
   sout << number;
   string text = sout.str();

   // handle the negative
   if (isNegative)
   {
      glBegin(GL_LINES);
      glVertex2f(point.getX() + 1, point.getY() - 5);
      glVertex2f(point.getX() + 5, point.getY() - 5);
      glEnd();
      point.addX(11);
   }
   
   // walk through the text one digit at a time
   for (const char *p = text.c_str(); *p; p++)
   {
      assert(isdigit(*p));
      drawDigit(point, *p);
      point.addX(11);
   }
}

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void drawText(const Point & topLeft, const char * text)
{
   // void *pFont = GLUT_BITMAP_HELVETICA_18;  // also try _18
   void *pFont = GLUT_BITMAP_9_BY_15;

   // prepare to draw the text from the top-left corner
   glRasterPos2f(topLeft.getX(), topLeft.getY());

   // loop through the text
   for (const char *p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  point    The point to be moved
 *           center   The center point we will rotate around
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
void rotate(Point & point, const Point & origin, int rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(deg2rad(rotation));
   double sinA = sin(deg2rad(rotation));

   // remember our original point
   Point tmp(false /*check*/);
   tmp.setX(point.getX() - origin.getX());
   tmp.setY(point.getY() - origin.getY());

   // find the new values
   point.setX( (tmp.getX() * cosA - 
                tmp.getY() * sinA) +
               origin.getX());
   point.setY((tmp.getX() * sinA +
               tmp.getY() * cosA) +
              origin.getY());
}

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 *  INPUT  center    Center of the rectangle
 *         width     Horizontal size
 *         height    Vertical size
 *         rotation  Orientation
 *************************************************************************/
void drawRect(const Point & center, int width, int height, int rotation)
{
   Point tl(false /*check*/); // top left
   Point tr(false /*check*/); // top right 
   Point bl(false /*check*/); // bottom left
   Point br(false /*check*/); // bottom right

   //Top Left point
   tl.setX(center.getX() - (width  / 2));
   tl.setY(center.getY() + (height / 2));

   //Top right point
   tr.setX(center.getX() + (width  / 2));
   tr.setY(center.getY() + (height / 2));

   //Bottom left point
   bl.setX(center.getX() - (width  / 2));
   bl.setY(center.getY() - (height / 2));

   //Bottom right point
   br.setX(center.getX() + (width  / 2));
   br.setY(center.getY() - (height / 2));

   //Rotate all points the given degrees
   rotate(tl, center, rotation);
   rotate(tr, center, rotation);
   rotate(bl, center, rotation);
   rotate(br, center, rotation);

   //Finally draw the rectangle
   glBegin(GL_LINE_STRIP);
   glVertex2f(tl.getX(), tl.getY());
   glVertex2f(tr.getX(), tr.getY());
   glVertex2f(br.getX(), br.getY());
   glVertex2f(bl.getX(), bl.getY());
   glVertex2f(tl.getX(), tl.getY());
   glEnd();
}

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *  INPUT   center   Center of the circle
 *          radius   Size of the circle
 *************************************************************************/
void drawCircle(const Point & center, int radius)
{
   assert(radius > 1.0);
   const double increment = 1.0 / (double)radius;

   // begin drawing
   glBegin(GL_LINE_LOOP);

   // go around the circle
   for (double radians = 0; radians < M_PI * 2.0; radians += increment)
      glVertex2f(center.getX() + (radius * cos(radians)),
                 center.getY() + (radius * sin(radians)));
   
   // complete drawing
   glEnd();
   
}

/************************************************************************
 * DRAW POLYGON
 * Draw a POLYGON from a given location (center) of a given size (radius).
 *  INPUT   center   Center of the polygon
 *          radius   Size of the polygon
 *          points   How many points will we draw it.  Larger the number,
 *                   the more line segments we will use
 *          rotation True circles are rotation independent.  However, if you
 *                   are drawing a 3-sided polygon (triangle), this matters!
 *************************************************************************/
void drawPolygon(const Point & center, int radius, int points, int rotation)
{
   // begin drawing
   glBegin(GL_LINE_LOOP);

   //loop around a circle the given number of times drawing a line from
   //one point to the next
   for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / points)
   {
      Point temp(false /*check*/);
      temp.setX(center.getX() + (radius * cos(i)));
      temp.setY(center.getY() + (radius * sin(i)));
      rotate(temp, center, rotation);
      glVertex2f(temp.getX(), temp.getY());
   }
   
   // complete drawing
   glEnd();

}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *   INPUT  begin     The position of the beginning of the line
 *          end       The position of the end of the line
 *************************************************************************/
void drawLine(const Point & begin, const Point & end)
{
   // Get ready...
   glBegin(GL_LINES);

   // Note how we scale the lines by a factor of two
   glVertex2f(begin.getX(), begin.getY());
   glVertex2f(  end.getX(),   end.getY());

   // complete drawing
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *  INPUT point   The position of the dow
 *************************************************************************/
void drawDot(const Point & point)
{
   // Get ready, get set...
   glBegin(GL_POINTS);

   // Go...
   glVertex2f(point.getX(),     point.getY()    );
   glVertex2f(point.getX() + 1, point.getY()    );
   glVertex2f(point.getX() + 1, point.getY() + 1);
   glVertex2f(point.getX(),     point.getY() + 1);

   // Done!  OK, that was a bit too dramatic
   glEnd();
}

/**********************************************************************
 * DRAW ASTEROID 
 * @author Justin Ricks
 * Draw an asteroid of a particular size and type. A type is an integer
 * starting at 0 and going up to the number of different types. If none
 * is passed in, the default will be drawn
 **********************************************************************/
void drawAsteroid(const Point & center, int rotation, float size, int type /*= 0*/)
{
   float sizex2 = size * 2;
   int typemod = type % 3;

   switch(type)
   {
      case 0:
         drawAsteroid0(center, rotation, sizex2);
         break;
      case 1:
         drawAsteroid1(center, rotation, sizex2);
         break;
      default:
         drawAsteroid2(center, rotation, sizex2);
         break;
   }
}

/*******************************************
* TYPE 0
*******************************************/
void drawAsteroid0(const Point & center, int rotation, float size)
{

   const PTF points[] = 
   {
      {-0.3, 0.4},  {-0.1, 0.4},   {0.3, 0.5},   
      {0.4, 0.4},   {0.5, 0.2},  {0.4, -0.3}, 
      {-0.2, -0.5}, {-0.5, -0.4}, {-0.3, -0.1},
      {-0.4, -0.1},  {-0.3, 0.4}
   };

   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PTF); i++)
   {
      Point pt(center.getX() + (points[i].x * size), 
               center.getY() + (points[i].y * size));
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glEnd();
}

/*******************************************
* TYPE 1
*******************************************/
void drawAsteroid1(const Point & center, int rotation, float size)
{

   const PTF points[] = 
   {
      {-0.1, 0.5},  {0.3, 0.4},   {0.3, 0.2},   
      {0.4, 0.1},   {0.5, -0.1},  {0.3, -0.4}, 
      {-0.2, -0.5}, {-0.5, -0.2}, {-0.4, 0.0},
      {-0.5, 0.3},  {-0.4, 0.4},  {-0.2, 0.4}, {-0.1, 0.5}
   };

   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PTF); i++)
   {
      Point pt(center.getX() + (points[i].x * size), 
               center.getY() + (points[i].y * size));
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glEnd();
}

/*******************************************
* TYPE 2
*******************************************/
void drawAsteroid2(const Point & center, int rotation, float size)
{

   const PTF points[] = 
   {
      {-0.3, 0.5},  {-0.1, 0.3},   {0.4, 0.4},   
      {0.5, 0.2},   {0.4, -0.2},  {0.1, -0.4}, 
      {-0.3, -0.5}, {-0.5, -0.1}, {-0.4, -0.1},
      {-0.4, 0.3},  {-0.3, 0.5}
   };

   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PTF); i++)
   {
      Point pt(center.getX() + (points[i].x * size), 
               center.getY() + (points[i].y * size));
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glEnd();
}

/**********************************************************************
 * DRAW SMALL ASTEROID
 **********************************************************************/
void drawSmallAsteroid( const Point & center, int rotation)
{
   PT points[] = 
   {
      {-5, 9},  {4, 8},   {8, 4},   
      {8, -5},  {-2, -8}, {-2, -3}, 
      {-8, -4}, {-8, 4},  {-5, 10}
   };
   
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glEnd();
}

/**********************************************************************
 * DRAW MEDIUM ASTEROID
 **********************************************************************/
void drawMediumAsteroid( const Point & center, int rotation)
{
   PT points[] = 
   {
      {2, 8},    {8, 15},    {12, 8}, 
      {6, 2},    {12, -6},   {2, -15},
      {-6, -15}, {-14, -10}, {-15, 0},
      {-4, 15},  {2, 8}
   };
   
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glEnd();
}

/**********************************************************************
 * DRAW LARGE ASTEROID
 **********************************************************************/
void drawLargeAsteroid( const Point & center, int rotation)
{
   PT points[] = 
   {
      {0, 12},    {8, 20}, {16, 14},
      {10, 12},   {20, 0}, {0, -20},
      {-18, -10}, {-20, -2}, {-20, 14},
      {-10, 20},  {0, 12}
   };
   
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(points)/sizeof(PT); i++)
   {
      Point pt(center.getX() + points[i].x, 
               center.getY() + points[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glEnd();
}


/************************************************************************       
 * DRAW Ship                                                                    
 * Draw a spaceship on the screen                                               
 *  INPUT point   The position of the ship                                      
 *        angle   Which direction it is ponted                                  
 *************************************************************************/
void drawShip(const Point & center, int rotation, bool thrust)
{
   
   // draw the ship                                                 
   const PT pointsShip[] = 
   { // top   r.wing   r.engine l.engine  l.wing    top
      {0, 6}, {6, -6}, {2, -3}, {-2, -3}, {-6, -6}, {0, 6}  
   };
   
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < sizeof(pointsShip)/sizeof(PT); i++)
   {
      Point pt(center.getX() + pointsShip[i].x, 
               center.getY() + pointsShip[i].y);
      rotate(pt, center, rotation);
      glVertex2f(pt.getX(), pt.getY());
   }
   glEnd();

   // draw the flame if necessary
   if (thrust)
   {
      const PT pointsFlame[3][5] =
      {
         { {-2, -3}, {-2, -13}, { 0, -6}, { 2, -13}, {2, -3} },
         { {-2, -3}, {-4,  -9}, {-1, -7}, { 1, -14}, {2, -3} },
         { {-2, -3}, {-1, -14}, { 1, -7}, { 4,  -9}, {2, -3} }
      };
      
      glBegin(GL_LINE_STRIP);
      glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
      int iFlame = random(0, 3);
      for (int i = 0; i < 5; i++)
      {
         Point pt(center.getX() + pointsFlame[iFlame][i].x, 
                  center.getY() + pointsFlame[iFlame][i].y);
         rotate(pt, center, rotation);
         glVertex2f(pt.getX(), pt.getY());
      }
      glColor3f(1.0, 1.0, 1.0); // reset to white                                  
      glEnd();
   }
}

/******************************************************************
 * RANDOM
 * This function generates a random number.  
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max)
{
   assert(min <= max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);

   return num;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.  
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the double
 ****************************************************************/
double random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   
   assert(min <= num && num <= max);

   return num;
}

