/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: Arm.hpp
 */

#ifndef ARM_HPP_
#define ARM_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Rectangle.hpp"
#include "ForeArm.hpp"

class Arm: public Shape{
	protected:
	public:
		ForeArm * lowerArm;
		Rect * upperArm;
		Arm();
		~Arm();
		void draw();
		void bend_arm();
		void unbend_arm();
		void reset_arm();
		void draw_solid();

};
#endif /* ARM_HPP_ */
