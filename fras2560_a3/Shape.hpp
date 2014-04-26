/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 3
 *	Date: 10/24/2013
 *	File: Matrix.cpp
 *	Description: implementation of Shape class
 */

#ifndef CSHAPE_H
#define CSHAPE_H

#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <GL/glut.h>

#include "Matrix.hpp"

using namespace std;

/**
 * Shape class the common class that will be inherited model object class
 */
class Shape {
protected:
	Matrix MC; //the Model coordinate system in (X, Y, Z, 0)
	GLfloat s; // scale factor

public:
	Shape();  // constructor
	virtual ~Shape();  // destructor

	Matrix getMC();
	void ctm_multiply(); // function to do the CTM * MC
	// to change the scale factor
	void scale_change(GLfloat x);
	// to translate the MC origin
	void translate(GLfloat tx, GLfloat ty, GLfloat tz);
	// to rotate the MC with respect to a local axis.
	void rotate_mc(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);
	// to rotate the MC including both vectors and origin
	void rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);
	// to rotate the origin of MC and keep the vector changed
	void rotate_origin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle);
	// a function that resets the shape transformation matrix
	void reset();
	// draw function must be overwritten
	virtual void draw() = 0;
};

#endif
