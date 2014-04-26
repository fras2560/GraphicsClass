/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: Rectangle.hpp
 */

#ifndef RECT_HPP_
#define RECT_HPP_

#include <GL/glut.h>

#include "Shape.hpp"

class Rect: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat norm_mc[6][3]; // normal face in mc
	GLfloat norm_wc[6][4]; //normal face in wc
	GLfloat faceColor[6][3]; //colour for each face
	GLfloat cubeWC[8][4]; //cube vertices in WC
	GLuint texture;
public:
	Rect(); //default constructor is a cube
	Rect(GLint, GLint, GLint, GLint); //constructor for custom width, height, depth, colour
	void draw_face(GLint);
	void draw_solid_face(GLint);
	void draw_solid_texture(GLint);
	void draw();
	void update_rect();
	void update_normal_vectors();
	void print_array(GLint*, GLint);
	void print_array(GLfloat*, GLint);
	void draw_solid();
	void set_texture(GLuint);
};
#endif /* RECTANGLE_HPP_ */
