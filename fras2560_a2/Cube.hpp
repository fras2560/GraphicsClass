/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 2
 *	Date: 10/10/2013
 *	File: Cube.hpp
 */

#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>

#include "Shape.hpp"

class Cube: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];

public:
	Cube();
	void draw_face(int);
	void draw();
	void draw_simple();
};

#endif
