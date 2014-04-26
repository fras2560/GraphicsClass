/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
*	Assignment: 4
 *	Date: 11/7/2013
  *	File: Rope.hpp
 */

#include "Shape.hpp"
#include "Bezier.hpp"
#include "Rectangle.hpp"
#include "Human.hpp"
#include "Image.hpp"

#ifndef ROPE_HPP_
#define ROPE_HPP_
class Rope: public Shape {
 public:
	Bezier * rope;
	Rect * end1;
	Rect * end2;
	GLint spins;
	GLfloat speed;
	GLfloat rotations;
	GLfloat increment;
	Rope();
	void draw();
	void draw_solid();
	void set_texture(GLuint);
	void spin();
	void reset_rope();
	GLboolean collision_precheck();
	GLboolean collision_check(Human *);
	GLboolean check_top(Human *);
	GLboolean check_bottom(Human *);
	void map_texture();
};
#endif /* ROPE_HPP_ */
