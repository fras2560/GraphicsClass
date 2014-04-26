/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Pyramid.hpp
 */

#ifndef PYRAMID_HPP_
#define PYRAMID_HPP_

#include <GL/glut.h>

#include "Shape.hpp"

class Pyramid: public Shape {
protected:
	GLfloat vertex[5][3];
	GLint face[5][4];

public:
	Pyramid();
	void draw_face(int);
	void draw();
	void draw_simple();
};



#endif /* PYRAMID_HPP_ */
