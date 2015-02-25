#ifndef CAMERA_H
#define CAMERA_H

#include "GL\glut.h"
#include <GL\GL.h>
#include <GL\GLU.h>

class Camera
{
public:
	Camera() { x = y = 0; }
	void MoveTo(float _x, float _y) { x = _x; y = _y; glTranslatef(x, y, 0); }
	void MoveY(float deltaY) { y += deltaY; glTranslatef(x, y, 0); }
	void MoveX(float deltaX) { x += deltaX; glTranslatef(x, y, 0); }
	float getX() { return x; }
	float getY() { return y; }
private:
	float x, y;
};

#endif