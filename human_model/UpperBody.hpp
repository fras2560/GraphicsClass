/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: UpperBody.hpp
 */

#ifndef UPPERBODY_HPP_
#define UPPERBODY_HPP_
#include <GL/glut.h>
#include "Shape.hpp"
#include "Rectangle.hpp"
#include "Bezier.hpp"
#include "Arm.hpp"

class UpperBody: public Shape{
	protected:

		GLint max_bend;
		GLint bends;
	public:
		Arm * arm1;
		Arm * arm2;
		Bezier * body;
		Rect * abdomen;
		UpperBody();
		~UpperBody();
		void reset_upperbody();
		void draw();
		void draw_solid();
		void bend_arms();
		void unbend_arms();
		void set_body_texture(GLuint);
		void rotate_arms();

};



#endif /* UPPERBODY_HPP_ */
