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
		GLint stage;
		GLfloat v;
		GLfloat a;
		GLint bent;
		GLfloat up;
		GLfloat down;
		GLint rotations;
		GLboolean can_jump;
	public:
		GLboolean jumping;
		GLboolean bending;
		GLboolean falling;

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

};
#endif /* HUMAN_HPP_ */
