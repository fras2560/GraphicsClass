/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 3
 *	Date: 10/24/2013
 *	File: a2.cpp
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <time.h>
#include "World.hpp"
#include "Camera.hpp"
#include "Point.hpp"
#include "Cube.hpp"
#include "Light.hpp"

//prototypes
void move(void);
void modelTransforms(GLint);
void worldTransforms(GLint);
void viewTransforms(GLint);
void lightTransforms(GLint);

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
GLint shading = 0; //whether shading is on or off
GLint solar = 0, animate=0;
//Declare a world containing all objects to draw.
World myWorld;
//my camera object
Camera myCam;
//my light Object
Light myLight;

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
		myLight.draw();
		glFlush();
		glutSwapBuffers();
	}
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
		}else if (coordinate == 4){
			//light transformation
			lightTransforms(x);
		}
		glutPostRedisplay();
	}
}

/*
 * lightTransforms
 * a function that deals with all the light transformations
 * Parameters:
 * 	x: x position of the mouse
 * Returns:
 * 	none
 */
void lightTransforms(GLint x){
	GLfloat theta;
	theta = (xBegin - x > 0) ? 1 : -1;
	if (type == 1) {
		//light rotate x
		myLight.rotate(1.0, 0.0, 0.0, theta*0.5);
	}else if (type == 2) {
		//light rotate y
		myLight.rotate(0.0, 1.0, 0.0, theta*0.5);
	}else if(type == 3){
		//light rotate z
		myLight.rotate(0.0, 0.0, 1.0, theta*0.5);
	}else if (type == 4) {
		//light translate x
		myLight.translate(theta*.1, 0.0, 0.0);
	}else if(type == 5){
		//light translate y
		myLight.translate(0.0, theta*.1, 0.0);
	}else if(type == 6){
		//light translate z
		myLight.translate(0.0, 0.0, theta*.1);
	}else if(type == 7){
		//Ambient Ka
		theta *= -1;
		myLight.Increment(0,0,theta*.1,0);
	}else if(type == 8){
		//Ambient B
		theta *= -1;
		myLight.Increment(0,theta*.1,0,0);
	}else if(type == 9){
		//Point Light Kd
		theta *= -1;
		myLight.Increment(0,0,0,theta*.1);
	}
	else if(type == 10){
		// Point Intensity P
		theta *= -1;
		myLight.Increment(theta*.1,0,0,0);
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
	//Enable openGL depth buffer algorithm
	glEnable(GL_DEPTH_TEST);
}

/*
 * move
 * that function that moves the cube
 */
void move(void){
	GLfloat rx,ry,rz;
	if (moving == 0){
		if(solar == 0){
			rx = myWorld.list[selected]->getMC().mat[0][0];
			ry = myWorld.list[selected]->getMC().mat[1][0];
			rz = myWorld.list[selected]->getMC().mat[2][0];
			myWorld.list[selected]->rotate_mc(0, -1, 0, 0.5);
		}else{
			rx = 0;
			ry = 1;
			rz = 0;
			myWorld.list[2]->rotate_origin(rx,ry,rz, 0.5);
			rx = myWorld.list[1]->getMC().mat[0][1];
			ry = myWorld.list[1]->getMC().mat[1][1];
			rz = myWorld.list[1]->getMC().mat[2][1];
			myWorld.list[1]->rotate_mc(rx,ry,rz, 0.5);
		}
		glutPostRedisplay();
	}


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
			myLight.Reset();
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
 * LightMenu
 * a function the deals with the Light menu
 * Parameters:
 * 	lightOption: the light menu option selected
 * Returns:
 * 	none
 */
void LightMenu(GLint lightOption){
	/*
	 * Rotate x - 1
	 * Rotate y - 2
	 * Rotate z - 3
	 * Translate x - 4
	 * Translate y - 5
	 * Translate z - 6
	 * Ambient Ka - 7
	 * Ambient B - 8
	 * Point Light Kd - 9
	 * Point Intensity P - 10
	 */
	coordinate = 4;
	type = lightOption;
}

/*
 * ViewMenu
 * a function that deals with all the view options
 * Parameters:
 * 	viewOption: the view option selected
 * Returns:
 * 	none
 */
void ViewMenu(GLint viewOption){
	//view menu
	if(viewOption == 1){
		//show light
		myLight.On = true;
	}else if(viewOption == 2){
		//turn light of
		myLight.On = false;
	}

}

/*
 * AMenu
 * a function the deals with all the a3 menu options
 * Parameters:
 * 	menuOption: the menu option selected
 * Returns:
 * 	none
 */
void AMenu(GLint menuOption){
	//View menu
	glutIdleFunc(NULL);
	solar = 0;
	if(menuOption == 1){
		//hidden face removal
		shading = 0;
		myLight.On = false;
	}else if(menuOption == 2){
		//shading
		myLight.On = true;
		shading = 1;
	}else if(menuOption == 3){
		//cube animation
		myLight.On = true;
		shading = 1;
		glutIdleFunc(move);
	}else if(menuOption == 4){
		//solar system
		solar = 1;
		myLight.On = false;
		glutIdleFunc(move);
	}
	glutPostRedisplay();
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
	GLint WCTrans_Menu, VCTrans_Menu, MCTrans_Menu, Light_Menu, A_Menu, View_Menu;
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

	//view options
	Light_Menu = glutCreateMenu(LightMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	glutAddMenuEntry(" Ambient Ka", 7);
	glutAddMenuEntry(" Ambient B", 8);
	glutAddMenuEntry(" Point Light Kd", 9);
	glutAddMenuEntry(" Point Intensity P", 10);

	//A_3 menu
	A_Menu = glutCreateMenu(AMenu);
	glutAddMenuEntry(" Hidden Face Removal ", 1);
	glutAddMenuEntry(" Color Shading ", 2);
	glutAddMenuEntry(" P3 Cube Animation ", 3);
	glutAddMenuEntry(" P3 Solar System", 4);

	//view menu
	View_Menu = glutCreateMenu(ViewMenu);
	glutAddMenuEntry(" Show Point Light ", 1);
	glutAddMenuEntry(" Hide Point Light ", 2);

	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	glutAddMenuEntry(" Reset ", 1);
	glutAddSubMenu(" Model Transformations ", MCTrans_Menu);
	glutAddSubMenu(" WC Transformations ", WCTrans_Menu);
	glutAddSubMenu(" View Transformations ", VCTrans_Menu);
	glutAddSubMenu(" Light Transformations", Light_Menu);
	glutAddSubMenu(" View", View_Menu);
	glutAddSubMenu(" A3 Menu", A_Menu);
	glutAddMenuEntry(" Quit", 2);
}

// the main function
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("A3 (Written by Dallas Fraser)");
	init();
	menu();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
