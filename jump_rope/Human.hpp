/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: Human.hpp
 */

#ifndef HUMAN_HPP_
#define HUMAN_HPP_

#include <GL/glut.h>
#include "LowerBody.hpp"
#include "UpperBody.hpp"
#include "Head.hpp"
#include "Image.hpp"

class Human: public Shape{
	protected:
		GLint max_bend;
		GLint bends;
		GLfloat v;
		GLfloat a;
		GLint bent;
		GLint rotations;
	public:
		GLboolean can_jump;
		GLint stage;
		GLboolean jumping;
		GLboolean bending;
		GLboolean falling;
		GLfloat up;
		GLfloat down;
		GLboolean solid;
		UpperBody * top;
		LowerBody * bottom;
		Head * head;
		Human();
		~Human();
		void draw();
		void jump();
		void bend();
		void unbend();
		void reset_human();
		void fall();
		void map_textures();
		GLfloat get_up();
		GLfloat get_down();


};
#endif /* HUMAN_HPP_ */
