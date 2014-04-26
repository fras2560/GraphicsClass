/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 2
 *	Date: 10/10/2013
 *	File: a2.cpp
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

#include "World.hpp"
#include "Camera.hpp"
#include "Point.hpp"
//prototypes
void modelTransforms(GLint);
void worldTransforms(GLint);
void viewTransforms(GLint);

GLint winWidth = 800, winHeight = 800;
//now in Camera Object
//GLfloat xeye = 3.0, yeye = 3.0, zeye = 7.0;  //  Viewing-coordinate origin.
//GLfloat xref = 0.0, yref = 0.0, zref = 0.0;  //  Look-at point.
//GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;        //  View up vector.
/*  Set coordinate limits for the clipping window:  */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;
/*  Set positions for near and far clipping planes:  */
GLfloat vangle = 40.0, dnear = 1.0, dfar = 10.0;
//GLfloat theta = 0.0, rx = 1.0, ry = 0.0, rz = 0.0, s=0.8;
GLfloat red = 1.0, green = 1.0, blue = 1.0;  //color
GLint moving = 0, xBegin = 0, coordinate = 1, type = 4, selected, stereo=0;

//Declare a world containing all objects to draw.
World myWorld;
//my camera object
Camera myCam;

#define DTOR 0.0174532925

/*
 * display
 *  a function to display the model
 *  Parameters:
 *  	none
 *  Returns:
 *  	none
 */
void display(void) {
	if (stereo == 0){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(vangle, 1.0, dnear, dfar);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(myCam.Eye.x, myCam.Eye.y, myCam.Eye.z, myCam.Rotate.x, myCam.Rotate.y, myCam.Rotate.z, myCam.ViewNorm.x, myCam.ViewNorm.y, myCam.ViewNorm.z);
		glColor3f(red, green, blue);
		myWorld.draw_world(); // draw all objects in the world


	}else{
		Point r;
		GLdouble ratio, radians, wd2, ndfl;
		GLdouble left1, right1,top1,bottom1,near1,far1;
		near1 = 0.1;
		far1 = 10000;
		near1 = myCam.focalLength / 5;

		/*Misc Stuff */
		ratio = myCam.screenWidth / (GLdouble)myCam.screenHeight;
		radians = DTOR * myCam.aperture / 2;
		wd2 = near1 * tan(radians);
		ndfl = near1 / myCam.focalLength;
		r.CrossProduct(myCam.ViewVector, myCam.ViewNorm);
		r.Normalize();
		/* Derive the two eye positions */
		r.x *= myCam.eyesep / 2.0;
		r.y *= myCam.eyesep / 2.0;
		r.z *= myCam.eyesep / 2.0;

		r.printPoint();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//left eye
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		left1 = - ratio * wd2 - 0.5 * myCam.eyesep * ndfl;
		right1 = ratio * wd2 - 0.5 * myCam.eyesep * ndfl;
		top1 = wd2;
		bottom1 = - wd2;
		glFrustum(left1,right1,bottom1,top1,near1,far1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(myCam.Eye.x + r.x, myCam.Eye.y + r.y,myCam.Eye.z + r.z,
				  myCam.Rotate.x + r.x,
				  myCam.Rotate.y + r.y,
				  myCam.Rotate.z + r.z,
				  myCam.ViewNorm.x,myCam.ViewNorm.y,myCam.ViewNorm.z);
		glColor3f(0.0, 0.0, 0.4);
		glLineWidth(3.0);
		glScalef(8.0, 8.0, 8.0);
		myWorld.draw_world();
		printf("LEft eye done\n");

		//right eye
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		left1 = - ratio * wd2 + 0.5 * myCam.eyesep * ndfl;
		right1 = ratio * wd2 + 0.5 * myCam.eyesep * ndfl;
		top1 = wd2;
		bottom1 = - wd2;
		glFrustum(left1,right1,bottom1,top1,near1,far1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(myCam.Eye.x - r.x,myCam.Eye.y - r.y,myCam.Eye.z - r.z,
				  myCam.Rotate.x - r.x,
				  myCam.Rotate.y - r.y,
				  myCam.Rotate.z - r.z,
				  myCam.ViewNorm.x,myCam.ViewNorm.y,myCam.ViewNorm.z);
		glColor3f(0.4, 0.0, 0.0);
		glScalef(8.0, 8.0, 8.0);
		myWorld.draw_world();
	}
	glFlush();
	glutSwapBuffers();
}

/*
 * winReshapeFcn
 * 	the functions that deals with window reshapes
 * 	Parameters:
 * 		newWidth: the new window width
 * 		newHeight: the new window height
 * 	Returns:
 * 		none
 *
 */
void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
	myCam.screenWidth = winWidth;
	myCam.screenHeight = winHeight;
}

/*
 * mouseAction
 * 	a function that deals with mouseAction
 * 	Parameters:
 * 		button: the button that was clicked
 * 		state: the state of the button
 * 		x: the x position of the event
 * 		y: the y position of the event
 */
void mouseAction(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		moving = 1;
		xBegin = x;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		moving = 0;
	}
}

/*
 * mouseMotion
 * 	a function that deals with mouse motion
 * 	Parameters:
 * 		x: the x position of the mouse
 * 		y: the y position of the mouse
 * 	Returns:
 * 		none
 */
void mouseMotion(GLint x, GLint y) {
	if (moving) {
		if (coordinate == 1){
			//model transformations
			modelTransforms(x);
		}else if (coordinate == 2){
			//WC transformations
			worldTransforms(x);
		}else if(coordinate == 3){
			//view transformations
			viewTransforms(x);
		}
		glutPostRedisplay();
	}
}

/*
 * worldTransforms
 * a function that deals with all the world transformations
 * Parameters:
 * 		x: x position of the mouse
 * 	Returns:
 * 		none
 */
void worldTransforms(GLint x){
	GLfloat rx, ry, rz, theta;
	if (type == 1) {
		//WC rotate x
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = 1;
		ry = 0;
		rz = 0;
		myWorld.list[selected]->rotate_origin(rx, ry, rz, theta * 0.5);
	}else if (type == 2) {
		//WC rotate y
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = 0;
		ry = 1;
		rz = 0;
		myWorld.list[selected]->rotate_origin(rx, ry, rz, theta * 0.5);
	}else if(type == 3){
		//WC rotate z
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = 0;
		ry = 0;
		rz = 1;
		myWorld.list[selected]->rotate_origin(rx, ry, rz, theta * 0.5);
	}else if (type == 4) {
		//WC translate x
		theta = (xBegin - x < 0) ? 1 : -1;
		myWorld.list[selected]->translate(theta * 0.02, 0, 0);
	}else if(type == 5){
		//WC translate y
		theta = (xBegin - x < 0) ? 1 : -1;
		myWorld.list[selected]->translate(0,theta * 0.02, 0);
	}else if(type == 6){
		//WC translate z
		theta = (xBegin - x < 0) ? 1 : -1;
		myWorld.list[selected]->translate(0, 0, theta * 0.02);
	}

}

/*
 * viewTransforms
 * a function that deals with all the view transformations
 * Parameters:
 * 	x: the position of the mouse
 * Returns:
 * 	none
 */
void viewTransforms(GLint x){
	GLfloat theta;
	if (type == 1) {
		//view rotate x
		theta = (xBegin - x > 0) ? 1 : -1;
		myCam.rotate(1.0, 0.0, 0.0, theta*0.5);
	}else if (type == 2) {
		//view rotate y
		theta = (xBegin - x > 0) ? 1 : -1;
		myCam.rotate(0.0, 1.0, 0.0, theta*0.5);
	}else if(type == 3){
		//view rotate z
		theta = (xBegin - x > 0) ? 1 : -1;
		myCam.rotate(0.0, 0.0, 1.0, theta*0.5);
	}else if (type == 4) {
		//view translate x
		theta = (xBegin - x < 0) ? 1 : -1;
		myCam.translate(theta, 0.0, 0.0);
	}else if(type == 5){
		//view translate y
		theta = (xBegin - x < 0) ? 1 : -1;
		myCam.translate(0.0, theta, 0.0);
	}else if(type == 6){
		//view translate z
		theta = (xBegin - x < 0) ? 1 : -1;
		myCam.translate(0.0, 0.0, theta);
	}else if(type == 7){
		//clipping near
		theta = (xBegin - x < 0) ? 1 : -1;
		dnear += theta * .1;
	}else if(type == 8){
		//clipping far
		theta = (xBegin - x < 0) ? 1 : -1;
		dfar += theta *.1;
	}else if(type == 9){
		//a function i made for fun
		theta = (xBegin - x < 0) ? 1 : -1;
		vangle += theta * .1;
	}
	else if(type == 10){
		// zoom
		theta = (xBegin - x > 0) ? 1 : -1;
		if (theta == 1){
			myCam.zoomIn(theta*.1);
		}else{
			myCam.zoomOut(theta*-.1);
		}
	}
}

/*
 * modelTransforms
 * 	a function that deals with all the model transformations
 * 	Parameters:
 * 		x: the position of the mouse
 * 	Returns:
 * 		none
 */
void modelTransforms(GLint x){
	GLfloat rx, ry, rz, theta;
	if (type == 1) {
		//model rotate x
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = myWorld.list[selected]->getMC().mat[0][0];
		ry = myWorld.list[selected]->getMC().mat[1][0];
		rz = myWorld.list[selected]->getMC().mat[2][0];
		myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 0.5);
	}
	else if (type == 2) {
		//model rotate y
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = myWorld.list[selected]->getMC().mat[0][1];
		ry = myWorld.list[selected]->getMC().mat[1][1];
		rz = myWorld.list[selected]->getMC().mat[2][1];
		myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 0.5);
	}else if (type == 3){
		//model rotate z
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = myWorld.list[selected]->getMC().mat[0][2];
		ry = myWorld.list[selected]->getMC().mat[1][2];
		rz = myWorld.list[selected]->getMC().mat[2][2];
		myWorld.list[selected]->rotate_mc(rx,ry,rz, theta * 0.5);
	}
	else if (type == 4) {
		//model scale
		theta = (xBegin - x < 0) ? 1 : -1;
		myWorld.list[selected]->scale_change(theta * 0.02);
	}

}

/*
 * init
 * 	a function that deals with initialization
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);  // Set display-window color to black
	glMatrixMode(GL_PROJECTION);
	gluPerspective(vangle, 1.0, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
	myCam.CameraReset(1);
	myCam.screenWidth = winWidth;
	myCam.screenHeight = winHeight;
	gluLookAt(myCam.Eye.x, myCam.Eye.y, myCam.Eye.z, myCam.Rotate.x, myCam.Rotate.y, myCam.Rotate.z, myCam.ViewNorm.x, myCam.ViewNorm.y, myCam.ViewNorm.z);

}

/*
 * MCTransMenu
 * 	the function that deals with the model Coordinate menu
 * 	Parameters:
 * 		transOption: the option selected
 * 	Returns:
 * 		none
 */
void MCTransMenu(GLint transOption) {
	switch (transOption) {
	case 1: {
		//rotate x
		coordinate = 1;
		type = 1;
	}
		break;
	case 2: {
		//rotate y
		coordinate = 1;
		type = 2;
	}
		break;
	case 3: {
		//rotate z
		coordinate = 1;
		type = 3;
	}
		break;
	case 4: {
		//scale
		coordinate = 1;
		type = 4;
	}
		break;
	}
	glutPostRedisplay();
}

/*
 * WCTransMenu
 * a function that deals with the world coordinate menu
 * 	Parameters:
 * 		transOption: the option selected
 * 	Returns:
 * 		none
 */
void WCTransMenu(GLint transOption) {
	coordinate = 2;
	switch (transOption) {
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	case 1: {
		// rotate x
		type = 1;
	}
		break;
	case 2: {
		// rotate y
		type = 2;
	}
		break;
	case 3:{
		//rotate z
		type = 3;
	}
		break;
	case 4: {
		// translate x
		type = 4;
	}
		break;
	case 5: {
		// translate y
		type = 5;
	}
		break;
	case 6: {
		// translate z
		type = 6;
	}
		break;
	}
	glutPostRedisplay();
}

/*
 * mainMenu
 * 	a function the deals with the main menu options
 * 	Parameters:
 * 		option: the option selected
 */
void mainMenu(GLint option) {
	switch (option){
		case 1:{
			//reset option
			myWorld.reset_world();
			if(stereo == 0){
				myCam.CameraReset(1);
			}else{
				myCam.CameraReset(0);
			}

		}
			break;
		case 2:{
			//quit option
			exit(0);
		}
			break;
	}
	glutPostRedisplay();
}

/*
 *VCTransMenu
 *a function that deals with view coordinate menu
 *Parameters:
 *		transOption: the option selected
 *Returns:
 *		none
 */
void VCTransMenu(GLint transOption) {
	coordinate = 3;
	switch (transOption){
		case 1:{
			//rotate x
			type = 1;
		}
			break;
		case 2:{
			//rotate y
			type = 2;
		}
			break;
		case 3:{
			//rotate z
			type = 3;
		}
			break;
		case 4:{
			//translate x
			type = 4;
		}
			break;
		case 5:{
			//translate y
			type = 5;
		}
			break;
		case 6:{
			//translate z
			type = 6;
		}
			break;
		case 7:{
			//clipping Near
			type = 7;
		}
			break;
		case 8:{
			//clipping far
			type = 8;
		}
			break;
		case 9:{
			//angle
			type = 9;
		}
			break;
		case 10:{
			//zoom in
			type = 10;
		}
			break;
	}
	glutPostRedisplay();
}

/*
 * colorSubMenu
 *	a function that deals the color menu
 * Parameters:
 * 	colorOption: the color option selected
 * Returns:
 * 	none
 */
void colorSubMenu(GLint colorOption) {
	red = 0.0;
	blue = 0.0;
	green = 0.0;
	switch(colorOption){
		case 1: {
			//red
			red = 1.0;
		}
			break;
		case 2: {
			//green
			green = 1.0;
		}
			break;
		case 3: {
			//blue
			blue = 1.0;
		}
			break;
		case 4: {
			//white
			red = 1.0;
			blue = 1.0;
			green = 1.0;
		}
			break;
	}
	glutPostRedisplay();
}

/*
 * ObjSubMenu
 * a function the deals with the object selection menu
 * Parameters:
 * 	objectOption: the object selected
 * Returns:
 * 	none
 */
void ObjSubMenu(GLint objectOption) {
	switch (objectOption) {
		case 1: {
			//square
			selected = 0;
			break;
		}
		case 2: {
			//pyramid
			selected = 1;
			break;
		}
		case 3: {
			//house
			selected = 2;
			break;
		}
	}
	glutPostRedisplay();
}

/*
 * threeDMenu
 * a function the deals with 3d menu
 * Parameters:
 * 	menu: the menu option selected
 * Returns:
 * 	none
 */
void threeDMenu(GLint menu){
	switch (menu){
		case 1:{
			stereo = 0;
			myCam.CameraReset(1);
			break;
		}
		case 2:{
			stereo = 1;
			myCam.CameraReset(0);
			break;
		}
	}
}

/*
 * menu
 *	a function the creates the menus
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void menu() {
	GLint WCTrans_Menu, VCTrans_Menu, MCTrans_Menu, subMenuColor, Object_Menu, threeD_Menu;
	MCTrans_Menu = glutCreateMenu(MCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Scale", 4);

	WCTrans_Menu = glutCreateMenu(WCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);

	VCTrans_Menu = glutCreateMenu(VCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	glutAddMenuEntry(" Clipping Near ", 7);
	glutAddMenuEntry(" Clipping Far ", 8);
	glutAddMenuEntry(" Angle ", 9);
	glutAddMenuEntry(" Camera Zoom", 10);

	subMenuColor = glutCreateMenu(colorSubMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("White", 4);


	Object_Menu = glutCreateMenu(ObjSubMenu);
	glutAddMenuEntry(" Cube ", 1);
	glutAddMenuEntry(" Pyramid", 2);
	glutAddMenuEntry(" House ", 3);

	threeD_Menu = glutCreateMenu(threeDMenu);
	glutAddMenuEntry(" Normal", 1);
	glutAddMenuEntry(" Stereoscopic 3D", 2);


	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	glutAddMenuEntry(" Reset ", 1);
	glutAddSubMenu(" Object Selection ", Object_Menu);
	glutAddSubMenu(" Model Transformations ", MCTrans_Menu);
	glutAddSubMenu(" WC Transformations ", WCTrans_Menu);
	glutAddSubMenu(" View Transformations ", VCTrans_Menu);
	glutAddSubMenu(" 3D", threeD_Menu);
	glutAddSubMenu(" Colors ", subMenuColor);
	glutAddMenuEntry(" Quit", 2);
}

// the main function
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("A2 (Written by Dallas Fraser)");
	init();
	menu();

	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
