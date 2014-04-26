/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: House.hpp
 */
#include "Light.hpp"
#include "Matrix.hpp"
#include <stdio.h>

Light::Light(){
	P = 0.8, B = 0.3, Ka = 1.0, Kd = 1.0;
	Position[0] = 2.0;
	Position[1] = 2.0;
	Position[2] = 1.5;
	On = false;
	Size = 100000.0;
}

/*
 * Reset
 * 	a method to reset the light
 * Parameters:
 * 	none
 * Returns
 * 	none
 */
void Light::Reset(){
	P = 0.8, B = 0.3, Ka = 1.0, Kd = 1.0;
	Position[0] = 2.0;
	Position[1] = 2.0;
	Position[2] = 1.5;
}

/*
 * Increment
 * a function to increment the light source
 * Parameters:
 * 	p: the increment to point light intensity
 * 	b: the increment to background light intensity
 * 	ka: the increment to the background Ka
 * 	kd: the increment to the poinght light Kd
 * Returns:
 * 	none
 */
void Light::Increment(GLfloat p, GLfloat b, GLfloat ka, GLfloat kd){
	P += p;
	if (P < 0){
		P = 0;
	}
	B += b;
	if (B < 0){
		B = 0;
	}
	Ka += ka;
	if (Ka < 0){
		Ka = 0;
	}
	Kd += kd;
	if (Kd < 0){
		Kd = 0;
	}
}

/*
 * draw
 * 	a method that draws the light
 * Parameters:
 * 	none
 * Returns
 * 	none
 */
void Light::draw(){
	if(On == true){

		glPushMatrix();
		//this->ctm_multiply();
		GLfloat light;
		light =  (P);
		if (light < 0){
			light = 0.0;
		}else if(light > 1.0){
			light = 1.0;
		}
		printf("Light %f\n", light);
		glColor3f(light, light, light);
		glEnable(GL_POINT_SMOOTH);
		glPointSize(Size);
		glBegin(GL_POINTS);
			glVertex3fv(&Position[0]);
		glEnd();
		glPopMatrix();
	}
}


/*
 * translate
 * 	a method to translate the light position
 * Parameters:
 * 	tx:the translation in the x axis
 * 	ty:the translation in the y axis
 * 	tz:the translation in the z axis
 */
void Light::translate(GLfloat tx, GLfloat ty, GLfloat tz){
	Position[0] += tx;
	Position[1] += ty;
	Position[2] += tz;
}


/*
 * rotate
 * a method to rotate the light
 * Parameters:
 * 	rx: the rotation in the x axis
 * 	ry: the rotation in the y axis
 * 	rz: the rotation in the z axis
 * 	angle: the rotation angle
 * Returns:
 * 	none
 */
void Light::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle){
	Matrix *m =  new Matrix();
	m->rotate(rx, ry, rz, angle);
	GLfloat vector[4];
	vector[0] = Position[0];
	vector[1] = Position[1];
	vector[2] = Position[2];
	vector[3] = 1;
	m->multiply_vector(vector);
	m->print_matrix();
	Position[0] = vector[0];
	Position[1] = vector[1];
	Position[2] = vector[2];
}
