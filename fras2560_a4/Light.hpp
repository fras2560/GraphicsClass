/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Light.hpp
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_
#include <GL/glut.h>
#include "Shape.hpp"
class Light{
	public:
		//light and shading
		GLfloat P, B, Ka, Kd;
		//point light position variable
		GLfloat Position[3];
		GLboolean On;
		GLfloat Size;
		Light();
		void Reset();
		void draw();
		void LightReset();
		void rotate(GLfloat rx, GLfloat rz, GLfloat ry, GLfloat angle);
		void translate(GLfloat tx, GLfloat ty, GLfloat tz);
		void Increment(GLfloat,GLfloat, GLfloat, GLfloat);

};
#endif /* LIGHT_HPP_ */
