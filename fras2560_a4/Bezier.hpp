/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Bezier.hpp
 */

#ifndef CBEZIER_H
#define CBEZIER_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Point.hpp"

class Bezier: public Shape{
public:
	GLint control_points; // the number of control points
	GLint R,S,T; //rotation points
	GLint PTgen, BCgen, BCrotation;
	Point points[10];
	Point mesh_points[73][26];
	Point mesh_normals[73][26];
	GLfloat CR,CG,CB;// the colours
	Bezier();
	void display_control_points();
	void binomial_coefficients(GLint, GLint *);
	void compute_bezier_point(GLfloat, Point *, Point *, GLint *);
	void draw(GLint);
	void draw_wire_rbc();
	void rotate_bezier(GLint);
	void draw_solid_rbc();
	void set_pixel(GLfloat, GLfloat);
	void add_control_point(GLfloat, GLfloat);
	void add_control_point(GLfloat, GLfloat, GLfloat);
	void draw();
	void draw2DFrame();
	void setPixel (GLfloat, GLfloat);
	void reset();
	void display_controls();
};


#endif
