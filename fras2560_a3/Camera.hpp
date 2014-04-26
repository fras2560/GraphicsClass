/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
*	Assignment: 3
 *	Date: 10/24/2013
  *	File: Camera.hpp
 */

#ifndef CCAMERA_H
#define CCAMERA_H

#include <GL/glut.h>
#include "Point.hpp"

class Camera {
 public:
	Point Eye; //view position vp
	Point ViewVector; //view direction vector vd
	Point ViewNorm; // view up direction vu
	Point Rotate; //point to rotate about pr
	GLint screenWidth, screenHeight; //screen dimensions
	GLfloat focalLength, aperture, eyesep; //other values needed for three d
	Camera();
	void rotate(GLfloat rx, GLfloat rz, GLfloat ry, GLfloat angle);
	void translate(GLfloat tx, GLfloat ty, GLfloat tz);
	void zoomIn(GLfloat zoom);
	void zoomOut(GLfloat zoom);
	void CameraReset(GLint);

};
#endif


