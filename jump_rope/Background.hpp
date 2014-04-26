/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/24/2013
 *	File: Background.hpp
 */

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_
#include <GL/glut.h>
#include "Shape.hpp"
#include "Cube.hpp"
#include "Image.hpp"

class Background: public Shape{
	protected:
		GLuint texture;
		GLfloat vertex[7][3];
		GLint faces[4][4];
	public:
		Background();
		void set_texture(GLuint);
		void draw();
		void map_texture();
};


#endif /* BACKGROUND_HPP_ */
