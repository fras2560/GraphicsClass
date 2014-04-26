/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
*	Assignment: 3
 *	Date: 10/24/2013
  *	File: Matrix.cpp
 *	Description: implementation of Matrix class
 */

#include "Matrix.hpp"
#include <stdio.h>
#include <cmath>
using namespace std;
// construct an identity matrix as mat
Matrix::Matrix() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				this->mat[i][j] = 1;
			else
				this->mat[i][j] = 0;
		}
	}
}

// multiplication  mat <- m * mat
/*
 * matrix_pre_multiply
 * 	Parameters:
 * 		m: the matrix to pre-multiply
 * 	Returns:
 * 		none
 */
void Matrix::matrix_pre_multiply(Matrix* m) {
	Matrix* temp = new Matrix();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GLfloat sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += m->mat[i][k] * this->mat[k][j];
			}
			temp->mat[i][j] = sum;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->mat[i][j] = temp->mat[i][j];
		}
	}
	delete temp;
}

// translate the origin of MC
/*
 * translate
 * 	Parameters:
 * 		tx: the translation in the x
 * 		ty: the translation in the y
 * 		tz: the translation in the z
 * 	Returns:
 * 		none
 */
void Matrix::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	this->mat[0][3] += tx;
	this->mat[1][3] += ty;
	this->mat[2][3] += tz;
	this->mat[3][3] = 1;
}

/*
 * transpose
 * 	a method that transposes the matrix
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Matrix::transpose() {
	GLint row, column;
	GLint temp;
	for(row=0;row<3;row++){
		for(column=row;column<4;column++){
			temp = this->mat[row][column];
			this->mat[row][column] = this->mat[column][row];
			this->mat[column][row] = temp;
		}
	}

}

// normalize MC
/*
 * normalize
 * 	a function to normalize the matrix
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Matrix::normalize() {
	GLfloat norm;

	norm = sqrt(this->mat[0][0]*this->mat[0][0] + this->mat[1][0]*this->mat[1][0]+this->mat[2][0]*this->mat[2][0]);

	this->mat[0][0] = this->mat[0][0]/norm;
	this->mat[1][0] = this->mat[1][0]/norm;
	this->mat[2][0] = this->mat[2][0]/norm;

	this->mat[0][2] = this->mat[1][0]*this->mat[2][1]-this->mat[2][0]*this->mat[1][1];
	this->mat[1][2] = this->mat[2][0]*this->mat[0][1]-this->mat[0][0]*this->mat[2][1];
	this->mat[2][2] = this->mat[0][0]*this->mat[1][1]-this->mat[1][0]*this->mat[0][1];

	norm = sqrt(this->mat[0][2]*this->mat[0][2] + this->mat[1][2]*this->mat[1][2]+this->mat[2][2]*this->mat[2][2]);

	this->mat[0][2] = this->mat[0][2]/norm;
	this->mat[1][2] = this->mat[1][2]/norm;
	this->mat[2][2] = this->mat[2][2]/norm;

	this->mat[0][1] = this->mat[1][2]*this->mat[2][0]-this->mat[1][0]*this->mat[2][2];
	this->mat[1][1] = this->mat[2][2]*this->mat[0][0]-this->mat[2][0]*this->mat[0][2];
	this->mat[2][1] = this->mat[0][2]*this->mat[1][0]-this->mat[0][0]*this->mat[1][2];

	this->mat[3][0] = 0;
	this->mat[3][1] = 0;
	this->mat[3][2] = 0;
	this->mat[3][3] = 1;
}

// v  <- mat * v
//this function was not working propery so was updated
/*
 * multiply_vector
 * 	a method to the matrix by a vector
 * 	Parameters:
 * 		v : the vector multiply
 * 	Returns:
 * 		none
 */
void Matrix::multiply_vector(GLfloat v[]) {
	GLint row;
	GLfloat sum=0;
	GLint vect;
	GLfloat vector [4];
	for (vect=0;vect<4;vect++){
		for(row=0;row<4;row++){
			sum +=  v[row] * this->mat[vect][row];
		}
		vector[vect] = sum;
		sum = 0;
	}
	for(vect=0;vect<4;vect++){
		v[vect] = vector[vect];
	}
}

/*
 * print_matrix
 * 	a method to print out the matrix
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Matrix:: print_matrix(){
	printf("Matrix:\n");
	printf("%f, %f,%f,%f\n",this->mat[0][0],this->mat[0][1],this->mat[0][2],this->mat[0][3]);
	printf("%f, %f,%f,%f\n",this->mat[1][0],this->mat[1][1],this->mat[1][2],this->mat[1][3]);
	printf("%f, %f,%f,%f\n",this->mat[2][0],this->mat[2][1],this->mat[2][2],this->mat[2][3]);
	printf("%f, %f,%f,%f\n",this->mat[3][0],this->mat[3][1],this->mat[3][2],this->mat[3][3]);
	printf("------------------\n");
}

// MC <= rotation matrix * MC, i.e., rotate coordinate vectors and the origin
/*
 * rotate
 * 	a method to rotate the matrix
 * 	Parameters:
 * 		x: the x co-ordinate
 * 		y: the y co-ordinate
 * 		z: the z co-ordinate
 * 		angle: the angle at which to rotate
 */
void Matrix::rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
	angle = angle * 3.1415926/180;
	float oneC = 1 - cos(angle);
	float COS = cos(angle);
	float SIN = sin(angle);
	Matrix* m = new Matrix();
	m->mat[0][0] = x * x * oneC + cos( angle );
	m->mat[0][1] = y * x * oneC + z * sin( angle );
	m->mat[0][2] = x * z * oneC - y * SIN;
	m->mat[0][3] = 0;
	m->mat[1][0] = x * y * oneC - z * SIN;
	m->mat[1][1] = y * y * oneC + COS;
	m->mat[1][2] = y * z * oneC + x * SIN;
	m->mat[1][3] = 0;
	m->mat[2][0] = x * z * oneC + y * SIN;
	m->mat[2][1] = y * z * oneC - x * SIN;
	m->mat[2][2] = z * z * oneC + COS;
	m->mat[2][3] = 0;
	m->mat[3][0] = 0;
	m->mat[3][1] = 0;
	m->mat[3][2] = 0;
	m->mat[3][3] = 1;
	this->matrix_pre_multiply(m);
	delete m;
}

