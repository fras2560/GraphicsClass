/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: LowerBody.hpp
 */

#ifndef LOWERBODY_HPP_
#define LOWERBODY_HPP_

#include <GL/glut.h>
#include "Rectangle.hpp"
#include "Leg.hpp"
#include "Shape.hpp"
class LowerBody: public Shape {
protected:
	GLint bends; //how many degrees of bending have occurred
	GLint max_bend;

public:
	Rect * ham1;
	Rect * ham2;
	Leg * leg1;
	Leg * leg2;
	LowerBody(); //default constructor is a cube
	void draw();
	void bend_legs();
	void unbend_legs();
	void reset_lowerbody();
	void draw_solid();
};

#endif /* LOWERBODY_HPP_ */
