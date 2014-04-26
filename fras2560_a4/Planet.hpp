/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Planet.hpp
 */

#ifndef CPlanet_H
#define CPlanet_H

#include <GL/glut.h>
#include "Shape.hpp"

class Planet: public Shape{
	protected:
		GLfloat radius, r ,g, b; //radius, red, green, blue
		GLint splices, stacks;
		GLuint texture;

	public:
		GLUquadricObj *sphere = NULL;
		Planet();
		Planet(GLint);
		~Planet();
		void draw();
		void set_colour(GLfloat, GLfloat, GLfloat);
		void set_texture(GLuint);

};
#endif
