
#pragma once
#ifndef PRIM_H
#define PRIM_H
#include <stdlib.h>
#include "GL/glut.h"
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* - these are simple convenience functions to draw primitives
     in openGL
   - feel free to understand and modify them
*/

/* after calling this, the line is set to this width until you call it again with a different value */
void setLineWidth(float width);

/* sets the current color to use when drawing anything afterwards */
void setColor(float red, float green, float blue);
/* draws a line between two points in screen pixel values (startX,startY) to (endX,endY) */
void drawLine(float startX, float startY, float endX, float endY);

/* draw a rectangle
 * - filled specifies if we color it completely or just show the edges 
 * - cornerX/cornerY is the bottom left corner coordinates
 * - width/height is the width and height of the rectangle
 * - theta is the angle (counter clockwise) of the rectangle
 */
void drawRectangle(bool filled, float cornerX, float cornerY, int width, int height, float theta);

/*
 * draw a circle
 * - subdivisions will change how smooth of a circle it will be
 * - radius is the radius in screen pixels
 * - centerX/centerY is the centroid of the circle
 */
void drawCircle(int subdivisions, float radius, float centerX, float centerY);
// draws a filled circle
void drawFilledCircle(int subdivisions, float radius, float centerX, float centerY);
// draw a triangle between three specified points
// it draws from p0-p1-p2 in this order
void drawTriangle(bool filled, float p0x, float p0y, float p1x, float p1y, float p2x, float p2y);

/* this draws a string to the screen coordinates specified */
void drawText(std::string s, float posX, float posY);
void drawText(std::string s, float posX, float posY, int numChars);

#endif