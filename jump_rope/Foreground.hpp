/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/24/2013
 *	File: Foreground.hpp
 */

#ifndef FOREGROUND_HPP_
#define FOREGROUND_HPP_
#include <GL/glut.h>
#include "Shape.hpp"
#include "Image.hpp"
class Foreground: public Shape{
	protected:
		GLuint texture;
	public:
		Foreground();
		void set_texture(GLuint);
		void draw();
		void map_texture();
};



#endif /* FOREGROUND_HPP_ */
