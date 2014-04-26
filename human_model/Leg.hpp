/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: Leg.hpp
 */

#ifndef LEG_HPP_
#define LEG_HPP_
#include <GL/glut.h>
#include "Rectangle.hpp"
#include "Shape.hpp"
class Leg: public Shape {
protected:
public:
	Rect * calves;
	Rect * foot;
	Leg(); //default constructor is a cube
	void draw();
	void reset_leg();
	void draw_solid();
};
#endif /* LEG_HPP_ */
