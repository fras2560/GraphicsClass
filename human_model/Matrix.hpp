/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Matrix.hpp
 *	Description: implementation of Matrix class
 */

#ifndef CMATRIX_H
#define CMATRIX_H

#include <iostream>
#include <GL/gl.h>
#include <math.h>

using namespace std;

class Matrix {
public:
	GLfloat mat[4][4];   	// this matrix is for MC
	Matrix();  				// constructor
	void matrix_pre_multiply(Matrix* m);  	// m*mat
	void transpose();  						// mat'
	void translate(GLfloat x, GLfloat y, GLfloat z);  // translate MC =  T(x, y, z)
	void rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle); //rotate w.r.p.t. vector (x, y, z) by angle
	void multiply_vector(GLfloat* v); // mat*v
	void normalize();  // this function is to normalize MC
	void  print_matrix(); // a function to print matrixes
};

#endif
