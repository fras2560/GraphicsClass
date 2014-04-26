/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 3
 *	Date: 10/24/2013
 *	File: Shape.cpp
 *	Description: implementation of Shape class
 */

#include "Shape.hpp"
#include <stdio.h>
using namespace std;
Shape::Shape() {
	MC.mat[0][0] = 1.0; MC.mat[0][1] = 0.0; MC.mat[0][2] = 0.0; MC.mat[0][3] = 0.0;
	MC.mat[1][0] = 0.0; MC.mat[1][1] = 1.0; MC.mat[1][2] = 0.0; MC.mat[1][3] = 0.0;
	MC.mat[2][0] = 0.0;	MC.mat[2][1] = 0.0;	MC.mat[2][2] = 1.0;	MC.mat[2][3] = 0.0;
	MC.mat[3][0] = 0.0;	MC.mat[3][1] = 0.0;	MC.mat[3][2] = 0.0;	MC.mat[3][3] = 1.0;
	s = 1;
}


Shape::~Shape() { };

Matrix Shape::getMC() {
	return  MC;
};

/*
 * reset
 * a method that resets the object
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Shape::reset(){
	GLint row,column;
	for(row=0;row<4;row++){
		for(column=0;column<4;column++){
			MC.mat[row][column] = 0.0;
		}
	}
	MC.mat[0][0] = 1.0;
	MC.mat[1][1] = 1.0;
	MC.mat[2][2] = 1.0;
	MC.mat[3][3] = 1.0;

}

/*
 * translate
 * 	a method that translates the shape
 * 	Parameters:
 * 		tx: the x translation
 * 		ty: the y translation
 * 		tz: the z translation
 * 	Returns:
 * 		none
 */
void Shape::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	MC.translate(tx, ty, tz);
	MC.normalize();
}

/*
 * rotate
 *a function that rotates (just rotates the shape)
 * Parameters:
 * 	rx: the rotation in the x space
 * 	ry: the rotation in the y space
 * 	rz the rotation in the z space
 * 	angle: the angle in which to rotate
 * Returns:
 * 	none
 */
void Shape::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	MC.rotate(rx, ry, rz, angle);
}

/*
 * rotate_mc
 * a method the rotates in the model co-ordinate system
 * Parameters:
 * 	rx: the rotation in the x space
 * 	ry: the rotation in the y space
 * 	rz: the rotation in the z space
 * 	angle: the angle in which to rotate
 * Returns:
 * 	none
 */
void Shape::rotate_mc(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	GLfloat x0,y0,z0;
	x0 = MC.mat[0][3];
	y0 = MC.mat[1][3];
	z0 = MC.mat[2][3];
	MC.rotate(rx, ry, rz, angle);
	MC.mat[0][3] = x0;
	MC.mat[1][3] = y0;
	MC.mat[2][3] = z0;
	MC.normalize();
}

/*
 * rotate_origin
 * 	a functions that adds the rotation to the matrix
 * 	Parameters:
 * 		rx:
 * 		ry:
 * 		rz:
 * 		angle:
 * 	Returns:
 * 		none
 */
void Shape::rotate_origin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix* m = new Matrix();
	m->rotate(rx, ry, rz, angle);
	GLfloat v[4];
	v[0] = MC.mat[0][3];
	v[1] = MC.mat[1][3];
	v[2] = MC.mat[2][3];
	v[3] = MC.mat[3][3];
	m->multiply_vector(v);
	MC.mat[0][3] = v[0];
	MC.mat[1][3] = v[1];
	MC.mat[2][3] = v[2];
	MC.mat[3][3] = v[3];
	MC.normalize();
	delete m;
}

/*
 * scale_change
 * 		a method to change the scale of the object
 * 	Parameters:
 * 		x: the amount to change the scale
 * 	Returns:
 * 		none
 *
 */
void Shape::scale_change(GLfloat x) {
	s += x;
}

/**
 * ctm_multiply
 * 		a method that multiply this matrix to openGL current matrix
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Shape::ctm_multiply() {
	GLfloat M[16];
	M[0] = MC.mat[0][0];
	M[1] = MC.mat[1][0];
	M[2] = MC.mat[2][0];
	M[3] = 0;
	M[4] = MC.mat[0][1];
	M[5] = MC.mat[1][1];
	M[6] = MC.mat[2][1];
	M[7] = 0;
	M[8] = MC.mat[0][2];
	M[9] = MC.mat[1][2];
	M[10] = MC.mat[2][2];
	M[11] = 0;
	M[12] = MC.mat[0][3];
	M[13] = MC.mat[1][3];
	M[14] = MC.mat[2][3];
	M[15] = 1;
	glMultMatrixf(M);
}
