
#pragma once
#include "GL/glut.h"
#include <string>


/* - these are simple convenience functions to draw primitives
     in openGL
   - feel free to understand and modify them
*/

/* after calling this, the line is set to this width until you call it again with a different value */
void setLineWidth(float width)
{
	glLineWidth(width);
}

/* sets the current color to use when drawing anything afterwards */
void setColor(float red, float green, float blue)
{
	glColor3f(red,green,blue);
}

/* draws a line between two points in screen pixel values (startX,startY) to (endX,endY) */
void drawLine(float startX,float startY, float endX, float endY)
{
	glBegin(GL_LINES);
	glVertex3f(startX,startY,0);
	glVertex3f(endX,endY,0);
	glEnd();
}

/* draw a rectangle
 * - filled specifies if we color it completely or just show the edges 
 * - cornerX/cornerY is the bottom left corner coordinates
 * - width/height is the width and height of the rectangle
 * - theta is the angle (counter clockwise) of the rectangle
 */
void drawRectangle(bool filled, float cornerX, float cornerY, int width, int height, float theta)
{
	if(filled) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glPushMatrix();
	glTranslatef(cornerX,cornerY,0);
	glRotatef(theta, 0,0,1);
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(0,height,0);
	glVertex3f(width,height,0);
	glVertex3f(width,0,0);
	glEnd();
	glPopMatrix();
}

/*
 * draw a circle
 * - subdivisions will change how smooth of a circle it will be
 * - radius is the radius in screen pixels
 * - centerX/centerY is the centroid of the circle
 */
void drawCircle(int subdivisions, float radius, float centerX, float centerY)
{
	float x,y;
	float step = 2.f*M_PI/(float) subdivisions;
	glPushMatrix();
	glTranslatef(centerX,centerY,0);
	glBegin(GL_LINE_LOOP);
	for(float theta=0;theta<=2.f*M_PI;theta+=step)
	{
		x = radius*cos(theta);
		y = radius*sin(theta);
		glVertex3f(x,y,0);
	}
	glEnd();
	glPopMatrix();
}
// draws a filled circle
void drawFilledCircle(int subdivisions, float radius, float centerX, float centerY)
{
	float x,y;
	float step = 2.f*M_PI/(float) subdivisions;
	glPushMatrix();
	glTranslatef(centerX,centerY,0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0,0);
	for(float theta=0;theta<=2.f*M_PI;theta+=step)
	{
		x = radius*cos(theta);
		y = radius*sin(theta);
		glVertex3f(x,y,0);
	}
	glVertex3f(radius,0,0);
	glEnd();

	glPopMatrix();
}

// draw a triangle between three specified points
// it draws from p0-p1-p2 in this order
void drawTriangle(bool filled, float p0x, float p0y, float p1x, float p1y, float p2x, float p2y)
{
	if(filled) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glBegin(GL_TRIANGLES);
	glVertex3f(p0x,p0y,0);
	glVertex3f(p1x,p1y,0);
	glVertex3f(p2x,p2y,0);
	glEnd();
}

/* this draws a string to the screen coordinates specified */
void drawText(std::string s, float posX, float posY)
{
	glPushMatrix();
	glRasterPos2f(posX,posY);
	const char *text = s.c_str();
	for(int i=0;i<s.length();i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glPopMatrix();
}