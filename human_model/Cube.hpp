/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Cube.hpp
 */

#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>

#include "Shape.hpp"

class Cube: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat cube_face_norm_mc[6][3]; // normal face in mc
	GLfloat cube_face_norm_wc[6][4]; //normal face in wc
	GLfloat faceColor[6][3]; //colour for each face
	GLfloat cubeWC[8][4]; //cube vertices in WC
	GLfloat backFaceTest[6];
	GLfloat cubeShade[6]; //light shading for each face
	GLfloat cube_face_center_mc[6][3]; //in mc
	GLfloat cube_face_center_wc[6][4]; //in WC


public:
	Cube();
	void draw_face(GLint);
	void draw_solid_face(GLint);
	void draw();
	void draw_simple();
	void update_cube();
	GLfloat calculate_z(GLint);
	void update_normal_vectors();
	void update_cube_face_center();
	void update_back_face(GLint);
	void print_array(GLint*, GLint);
	void print_array(GLfloat*, GLint);
	void update_shade(GLint);
	void calculate_normal(GLint);
};

#endif
