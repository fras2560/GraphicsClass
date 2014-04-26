/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: a2.cpp
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include <windows.h>
#include "Rectangle.hpp"
#include "Human.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Rope.hpp"

//prototypes
void move(void);
void modelTransforms(GLint);
void worldTransforms(GLint);
void viewTransforms(GLint);
void lightTransforms(GLint);
void draw_axis();

GLint winWidth = 800, winHeight = 800;

/*  Set coordinate limits for the clipping window:  */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;
/*  Set positions for near and far clipping planes:  */
GLfloat vangle = 40.0, dnear = 1.0, dfar = 100.0;
GLint moving = 0, xBegin = 0, coordinate = 1, type = 4, selected=0, stereo=0, light=0, shading=0;

Rect r;

Human * h;
Rope * rope;
//Declare a world containing all objects to draw.
World myWorld;
//my camera object
Camera myCam;
//my light Object
Light myLight;

//Rectangle myRect;

//Lighting substitute lx, ly, lz
GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };

GLfloat ambient[] = { 0.1, 0.1, 0.3, 1.0 };
GLfloat diffuse[] = { 0.6, 0.6, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

//Material
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 1, 1, 1, 1 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 1, 1, 1, 1 };

GLuint programObject; // GLSL object
GLuint phongVS, phongFS; //phong Vector shader and phong fragment shader

Image image;
Image image2;
Image image3;

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(vangle, 1.0, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(myCam.Eye.x, myCam.Eye.y, myCam.Eye.z, myCam.Rotate.x, myCam.Rotate.y, myCam.Rotate.z, myCam.ViewNorm.x, myCam.ViewNorm.y, myCam.ViewNorm.z);
	glPushMatrix();
	//draw_axis();
	myLight.draw();
	h->draw();
	rope->draw_solid();
	//myWorld.draw_world();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

/*
 * draw_axis
 * 	a function to display the axis
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void draw_axis(){
	glDisable(GL_LIGHTING);
	glLineWidth(3);
	glBegin(GL_LINES);
	//x-axis
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(2, 0, 0);
	glVertex3f(0, 0, 0);
	//y-axis
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 2, 0);
	glVertex3f(0, 0, 0);
	//z-axis
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, 0);
	glEnd();
	glLineWidth(1);
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
		glutPostRedisplay();
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
	}else if (type == 7) {
		// Adjust Ka
		theta = (xBegin - x < 0) ? 0.05 : -0.05;
		ambient[0] += theta;
		ambient[1] += theta;
		ambient[2] += theta;
	}
	else if (type == 8) {
		// Adjust B
		theta = (xBegin - x < 0) ? 0.02 : -0.02;
		ambient[0] += theta;
		ambient[1] += theta;
		ambient[2] += theta;
	}
	else if (type == 9) {
		// Adjust Kd
		theta = (xBegin - x < 0) ? 0.05 : -0.05;
		diffuse[0] += theta;
		diffuse[1] += theta;
		diffuse[2] += theta;
	}
	else if (type == 10) {
		// Adjust P
		theta = (xBegin - x < 0) ? 0.05 : -0.05;
		if (myLight.P + theta < 1 && myLight.P + theta > 0) {
			myLight.P += theta;
			diffuse[0] += theta;
			diffuse[1] += theta;
			diffuse[2] += theta;
		}
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
	//Shape* s = myWorld.get_selected(selected);
	if (type == 1) {
		//WC rotate x
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = 1;
		ry = 0;
		rz = 0;
		h->rotate_origin(rx, ry, rz, theta * 0.5);
	}else if (type == 2) {
		//WC rotate y
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = 0;
		ry = 1;
		rz = 0;
		h->rotate_origin(rx, ry, rz, theta * 0.5);
	}else if(type == 3){
		//WC rotate z
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = 0;
		ry = 0;
		rz = 1;
		h->rotate_origin(rx, ry, rz, theta * 0.5);
	}else if (type == 4) {
		//WC translate x
		theta = (xBegin - x < 0) ? 1 : -1;
		h->translate(theta * 0.02, 0, 0);
	}else if(type == 5){
		//WC translate y
		theta = (xBegin - x < 0) ? 1 : -1;
		h->translate(0,theta * 0.02, 0);
	}else if(type == 6){
		//WC translate z
		theta = (xBegin - x < 0) ? 1 : -1;
		h->translate(0, 0, theta * 0.02);
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
	//Shape* s = myWorld.get_selected(selected);
	if (type == 1) {
		//model rotate x
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = h->getMC().mat[0][0];
		ry = h->getMC().mat[1][0];
		rz = h->getMC().mat[2][0];
		h->rotate_mc(rx, ry, rz, theta * 0.5);
	}
	else if (type == 2) {
		//model rotate y
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = h->getMC().mat[0][1];
		ry = h->getMC().mat[1][1];
		rz = h->getMC().mat[2][1];
		h->rotate_mc(rx, ry, rz, theta * 0.5);
	}else if (type == 3){
		//model rotate z
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = h->getMC().mat[0][2];
		ry = h->getMC().mat[1][2];
		rz = h->getMC().mat[2][2];
		h->rotate_mc(rx,ry,rz, theta * 0.5);
	}
	else if (type == 4) {
		//model scale
		theta = (xBegin - x < 0) ? 1 : -1;
		h->scale_change(theta * 0.02);
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
	glDepthFunc(GL_LESS);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	//initiall all texture maps
	h = new Human();
	h->map_textures();

	rope = new Rope();
	rope->translate(0,.4,0);
	glutIdleFunc(move);

	//initial rope texture map
	GLuint text[3];
	glGenTextures(3, text);
	//bind the third texture
	glBindTexture(GL_TEXTURE_2D, text[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name3[] = "fire.bmp";
	image3.load_image(name3);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image3.sizeX, image3.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image3.data);
	rope->set_texture(text[2]);





}

/*
 * move
 * that function that moves the cube
 */
void move(void){
	if (moving == 0){
		h->jump();
		rope->spin();
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
			h->reset_human();
			if(stereo == 0){
				myCam.CameraReset(1);
			}else{
				myCam.CameraReset(0);
			}
		}
			break;
		case 2:{
			//quit option
			h->falling = true;
			printf("Bend\n");
		}
			break;
		case 3:{
			h->solid = true;
		}
			break;
		case 4:{
			h->solid = false;
		}
			break;
		case 5:{
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
 * menu
 *	a function the creates the menus
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void menu() {
	GLint WCTrans_Menu, VCTrans_Menu, MCTrans_Menu, Light_Menu, View_Menu;
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
	glutAddMenuEntry(" Fall Animation", 2);
	glutAddMenuEntry(" Solid", 3);
	glutAddMenuEntry(" Wire", 4);
	glutAddMenuEntry(" Quit", 5);

}


/*
 * keyUp
 * 	a function that deals with keys up
 * 	Parameters:
 * 		char: the character that was released
 * 		x: the x coordinate of the mouse on key release
 * 		y: the y coordinate of the mouse on key release
 * 	Returns:
 * 		none
 */
void keyUp (unsigned char key, int x, int y) {
	switch( key ){
	case 'j':case'J':
    	h->jumping = true;
    	break;
	}
}

/*
 * keyboard
 * 	a function that deals with keys presses
 * 	Parameters:
 * 		char: the character that was pressed
 * 		x: the x coordinate of the mouse on key release
 * 		y: the y coordinate of the mouse on key release
 * 	Returns:
 * 		none
 */
void keyboard( unsigned char key, int x, int y ) {
    switch( key ) {
	case 033: // Escape Key
	case 'q': case 'Q':
	    h->bend();
		break;
    case 'w':case'W':
    	h->unbend();
    	break;
    case 'j':case'J':
    	if(h->jumping == false){
        	h->bending = true;
    	}else{
    		printf("Could not change bending\n");
    	}
    	break;
    case 'r':case'R':
    	h->top->rotate_arms();

    	break;
    }
    glutPostRedisplay();
}

// the main function
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("A4 (Written by Dallas Fraser)");
	glewInit();
	init();
	menu();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc( keyboard );
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
