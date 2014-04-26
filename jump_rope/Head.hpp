/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: Head.hpp
 */

#ifndef HEAD_HPP_
#define HEAD_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include "Image.hpp"
class Head: public Shape{
	protected:
		GLfloat radius, r ,g, b; //radius, red, green, blue
		GLint splices, stacks;
		Image face;
		GLuint texture;
	public:
		GLUquadricObj *sphere = NULL;
		Head();
		~Head();
		void draw();
		void set_colour(GLfloat, GLfloat, GLfloat);
		void set_texture(GLuint);
		void reset_head();
		void draw_solid();

};
#endif /* HEAD_HPP_ */
