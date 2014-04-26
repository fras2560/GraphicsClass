/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 2
 *	Date: 10/10/2013
 *	File: Camera.cpp
 */

#include "Camera.hpp"
#include "Matrix.hpp"
#include <stdio.h>

Camera::Camera(){
	Eye.x = 3.0, Eye.y = 3.0, Eye.z = 7.0;  //  Viewing-coordinate origin.
	ViewNorm.x = 0.0,ViewNorm.y = 1.0,ViewNorm.z = 0.0; //view up vector
	Rotate.x = 0.0, Rotate.y = 0.0, Rotate.z = 0.0; //loot at point
	screenWidth = 800, screenHeight = 800; //screen dimensions
	focalLength = 70, aperture = 50, eyesep = focalLength / 20; //other values needed for three d
}

/*
 * rotate
 * a method to rotate the camera
 * Parameters:
 * 	rx: the rotation in the x axis
 * 	ry: the rotation in the y axis
 * 	rz: the rotation in the z axis
 * 	angle: the rotation angle
 * Returns:
 * 	none
 */
void Camera::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle){
	Matrix *m =  new Matrix();
	m->rotate(rx, ry, rz, angle);
	GLfloat vector[4];
	vector[0] = Eye.x;
	vector[1] = Eye.y;
	vector[2] = Eye.z;
	vector[3] = 1;
	m->multiply_vector(vector);
	m->print_matrix();
	Eye.x = vector[0];
	Eye.y = vector[1];
	Eye.z = vector[2];
}

/*
 * translate
 * 	a method to translate the camera position
 * Parameters:
 * 	tx:the translation in the x axis
 * 	ty:the translation in the y axis
 * 	tz:the translation in the z axis
 */
void Camera::translate(GLfloat tx, GLfloat ty, GLfloat tz){
	Eye.x += tx;
	Eye.y += ty;
	Eye.z += tz;
}

/*
 * zoomIn
 * a method for zooming into display point
 * Parameters:
 * 	zoom: the direction of the zoom
 * Returns:
 * 	none
 */
void Camera::zoomIn(GLfloat zoom){
	if(Eye.x - Rotate.x < 0){
		Eye.x += zoom;
	}else{
		Eye.x -= zoom;
	}
	if(Eye.y - Rotate.y < 0){
		Eye.y += zoom;
	}else{
		Eye.y -= zoom;
	}
	if(Eye.z - Rotate.z < 0){
		Eye.z += zoom;
	}else{
		Eye.z -= zoom;
	}
}

/*
 * zoomOut
 * a method for zooming out of display point
 * Parameters:
 * 	zoom: the direction of the zoom
 * Returns:
 * 	none
 */
void Camera::zoomOut(GLfloat zoom){
	if(Eye.x - Rotate.x < 0){
		Eye.x -= zoom;
	}else{
		Eye.x += zoom;
	}
	if(Eye.y - Rotate.y < 0){
		Eye.y -= zoom;
	}else{
		Eye.y += zoom;
	}
	if(Eye.z - Rotate.z < 0){
		Eye.z -= zoom;
	}else{
		Eye.z += zoom;
	}
}

/*
 * CameraReset
 * 	a method to reset the camera
 * Parameters:
 * 	mode: the mode of the camera
 * Returns:
 * 	none
 */
void Camera::CameraReset(GLint mode){
	printf("Called\n");
	if(mode == 1){
		aperture = 50;
		focalLength = 70;
		eyesep = focalLength / 20;

		Rotate.x = 0.0;
		Rotate.y = 0.0;
		Rotate.z = 0.0;

		/* Special camera position so the beam crosses the view */
		Eye.x = 3.0;
		Eye.y = 3.0;
		Eye.z = 7.0;

		ViewVector.x = -Eye.x;
		ViewVector.y = -Eye.y;
		ViewVector.z = -Eye.z;

		ViewNorm.x = 0.0;
		ViewNorm.y = 1.0;
		ViewNorm.z = 0.0;
	}else{
		aperture = 50;
		focalLength = 70;
		eyesep = focalLength / 20;

		Rotate.x = 0.0;
		Rotate.y = 0.0;
		Rotate.z = 0.0;

		/* Special camera position so the beam crosses the view */
		Eye.x = 30;
		Eye.y = 30;
		Eye.z = 70;

		ViewVector.x = -Eye.x;
		ViewVector.y = -Eye.y;
		ViewVector.z = -Eye.z;

		ViewNorm.x = 0;
		ViewNorm.y = 1;
		ViewNorm.z = 0;
	}

}
