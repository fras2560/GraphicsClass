/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: ForeArm.hpp
 */

#ifndef FOREARM_HPP_
#define FOREARM_HPP_


#include <GL/glut.h>
#include "Shape.hpp"
#include "Rectangle.hpp"
class ForeArm: public Shape{
	protected:
	public:
		Rect * hand;
		Rect * forearm;
		ForeArm();
		~ForeArm();
		void draw();
		void draw_solid();
		void reset_forearm();
};

#endif /* FOREARM_HPP_ */
