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

#include "Angel.h"
#include "World.hpp"
#include "Camera.hpp"
#include "Point.hpp"
#include "Cube.hpp"
#include "Light.hpp"
#include "Bezier.hpp"
#include "Image.hpp"
#include "Planet.hpp"
#include "Earth.hpp"

//prototypes
void move(void);
void modelTransforms(GLint);
void worldTransforms(GLint);
void CurvemodelTransforms(GLint);
void CurveworldTransforms(GLint);
void viewTransforms(GLint);
void lightTransforms(GLint);
void solar_display();
void draw_axis();

GLint winWidth = 800, winHeight = 800;

/*  Set coordinate limits for the clipping window:  */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;
/*  Set positions for near and far clipping planes:  */
GLfloat vangle = 40.0, dnear = 1.0, dfar = 100.0;

GLfloat red = 1.0, green = 1.0, blue = 1.0;  //color
GLint moving = 0, xBegin = 0, coordinate = 1, type = 4, selected=2, stereo=0, light=0;
GLint shading = 0; //whether shading is on or off
GLint solar = 0, animate=0, bezier = 0, curve_gen = 0, generated = 0, solid=0, rotated = 0;

//Declare a world containing all objects to draw.
World myWorld;
//my camera object
Camera myCam;
//my light Object
Light myLight;
//my bezier surface
Bezier myCurve;
//textures
GLuint texture[3];
 //images
Image image1;
Image image2;
Image image3;

//Lighting substitute lx, ly, lz
GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };
GLfloat positionSolar[] = { 0.0, 0.0, 0.0, 1.0 };

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

Earth m_e; //moon and earth
Planet sun;

#define DTOR 0.0174532925

/*
 * solar_display
 * 	a function that display all of the solar system
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void solar_display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(vangle, 1.0, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(myCam.Eye.x, myCam.Eye.y, myCam.Eye.z, myCam.Rotate.x, myCam.Rotate.y, myCam.Rotate.z, myCam.ViewNorm.x, myCam.ViewNorm.y, myCam.ViewNorm.z);
	glPushMatrix();
	m_e.draw(); //draw the moon and the earth
	sun.draw(); // draw the sun
	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

/*
 * display
 *  a function to display the model
 *  Parameters:
 *  	none
 *  Returns:
 *  	none
 */
void display(void) {
	if(solar == 1){
		solar_display();
	}else{
		if (curve_gen == 0){
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(vangle, 1.0, dnear, dfar);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(myCam.Eye.x, myCam.Eye.y, myCam.Eye.z, myCam.Rotate.x, myCam.Rotate.y, myCam.Rotate.z, myCam.ViewNorm.x, myCam.ViewNorm.y, myCam.ViewNorm.z);
			glColor3f(red, green, blue);

			draw_axis();
			if(light == 0){
				glDisable(GL_LIGHTING);
			}else{
				glEnable(GL_LIGHTING);
			}
			if(selected == 1){
				myWorld.draw_world(); // draw all objects in the world
				myLight.draw();
			}else if(selected == 2){
				myCurve.draw(); //draw bezier curve
				myLight.draw();
			}
			if (solid == 1 && light == 1) {
				glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
				position[0] = myLight.Position[0];
				position[1] = myLight.Position[1];
				position[2] = myLight.Position[2];
				glLightfv(GL_LIGHT0, GL_POSITION, position);
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient);
				glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			}
			glFlush();
			glutSwapBuffers();
		}else{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			myCurve.draw();
			glFlush();
			glutSwapBuffers();
		}
	}
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
	if(curve_gen == 0){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			moving = 1;
			xBegin = x;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			moving = 0;
		}
	}else{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && myCurve.control_points <10)
		{
		myCurve.add_control_point((x - winWidth/2 ),(winHeight/2 - y), 0.0);
		}
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
		if(selected == 1){
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
		}else if(selected == 2){
			if (coordinate == 1){
				//model transformations
				CurvemodelTransforms(x);
			}else if (coordinate == 2){
				//WC transformations
				CurveworldTransforms(x);
			}else if(coordinate == 3){
				//view transformations
				viewTransforms(x);
			}else if (coordinate == 4){
				//light transformation
				lightTransforms(x);
			}
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
 * CurvemodelTransforms
 * 	a function that deals with all the curve model transformations
 * 	Parameteres:
 * 		x: the movement in the x mouse co-ordinate
 * 	Returns:
 * 		none
 */
void CurvemodelTransforms(GLint x){
	GLfloat rx, ry, rz, theta;
	if (type == 1) {
		//model rotate x
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = myCurve.getMC().mat[0][0];
		ry = myCurve.getMC().mat[1][0];
		rz = myCurve.getMC().mat[2][0];
		myCurve.rotate_mc(rx, ry, rz, theta * 0.5);
	}
	else if (type == 2) {
		//model rotate y
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = myCurve.getMC().mat[0][1];
		ry = myCurve.getMC().mat[1][1];
		rz = myCurve.getMC().mat[2][1];
		myCurve.rotate_mc(rx, ry, rz, theta * 0.5);
	}else if (type == 3){
		//model rotate z
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = myCurve.getMC().mat[0][2];
		ry = myCurve.getMC().mat[1][2];
		rz = myCurve.getMC().mat[2][2];
		myCurve.rotate_mc(rx,ry,rz, theta * 0.5);
	}
	else if (type == 4) {
		//model scale
		theta = (xBegin - x < 0) ? 1 : -1;
		myCurve.scale_change(theta * 0.02);
	}
}

/*
 * CurveworldTransforms
 * 	a function the transform the curve on the world system
 * 	Parameters:
 * 		x: the x movement
 * 	Returns:
 * 		none
 */
void CurveworldTransforms(GLint x){
	GLfloat rx, ry, rz, theta;
	if (type == 1) {
		//WC rotate x
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = 1;
		ry = 0;
		rz = 0;
		myCurve.rotate_origin(rx, ry, rz, theta * 0.5);
	}else if (type == 2) {
		//WC rotate y
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = 0;
		ry = 1;
		rz = 0;
		myCurve.rotate_origin(rx, ry, rz, theta * 0.5);
	}else if(type == 3){
		//WC rotate z
		theta = (xBegin - x > 0) ? 1 : -1;
		rx = 0;
		ry = 0;
		rz = 1;
		myCurve.rotate_origin(rx, ry, rz, theta * 0.5);
	}else if (type == 4) {
		//WC translate x
		theta = (xBegin - x < 0) ? 1 : -1;
		myCurve.translate(theta * 0.02, 0, 0);
	}else if(type == 5){
		//WC translate y
		theta = (xBegin - x < 0) ? 1 : -1;
		myCurve.translate(0,theta * 0.02, 0);
	}else if(type == 6){
		//WC translate z
		theta = (xBegin - x < 0) ? 1 : -1;
		myCurve.translate(0, 0, theta * 0.02);
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
	glDepthFunc(GL_LESS);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	//Load Shaders and use the resulting shader program
	printf("Starting\n");
	programObject = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(0);

	printf("Done\n");
	//create three different textures texture
	glGenTextures(3, texture);

	//first texture to earth
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name[] = "earth.bmp";
	image1.load_image(name);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1.sizeX, image1.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image1.data);
	m_e.earth.set_texture(texture[0]);
	glEnable(GL_TEXTURE_2D);
	m_e.earth.sphere = gluNewQuadric();
	m_e.earth.scale_change(-.85);
	m_e.translate(2.0,0.0,2.0);
	gluQuadricDrawStyle(m_e.earth.sphere, GLU_FILL);
	gluQuadricTexture(m_e.earth.sphere, GL_TRUE);
	gluQuadricNormals(m_e.earth.sphere, GLU_SMOOTH);

	//second texture sun
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name2[] = "sun.bmp";
	image2.load_image(name2);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image2.sizeX, image2.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image2.data);
	sun.set_texture(texture[1]);
	glEnable(GL_TEXTURE_2D);
	sun.sphere = gluNewQuadric();
	sun.scale_change(-.3);
	gluQuadricDrawStyle(sun.sphere, GLU_FILL);
	gluQuadricTexture(sun.sphere, GL_TRUE);
	gluQuadricNormals(sun.sphere, GLU_SMOOTH);

	//third texture to moon
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name3[] = "moon.bmp";
	image3.load_image(name3);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image3.sizeX, image3.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image3.data);
	m_e.moon.set_texture(texture[2]);
	glEnable(GL_TEXTURE_2D);
	m_e.moon.sphere = gluNewQuadric();
	m_e.moon.scale_change(-.96);
	gluQuadricDrawStyle(m_e.moon.sphere, GLU_FILL);
	gluQuadricTexture(m_e.moon.sphere, GL_TRUE);
	gluQuadricNormals(m_e.moon.sphere, GLU_SMOOTH);
	glShadeModel(GL_FLAT);
	myCurve.S = 5;
	//disable since not texture at the start
	glDisable(GL_TEXTURE_2D);

	//testing adding a new cube
	//Shape *add = new Cube();
	//myWorld.add_object(1, add);

}

/*
 * move
 * that function that moves the cube
 */
void move(void){
	GLfloat rx,ry,rz;
	GLfloat sunx,suny,sunz;
	GLfloat earthx,earthy,earthz;
	GLfloat systemx,systemy,systemz;
	GLfloat moonx, moony, moonz;
	if (moving == 0){
		if(solar == 0){
			rx = myWorld.list[selected]->getMC().mat[0][0];
			ry = myWorld.list[selected]->getMC().mat[1][0];
			rz = myWorld.list[selected]->getMC().mat[2][0];
			myWorld.list[selected]->rotate_mc(0, -1, 0, 0.5);
		}else{
			//28 days for moon to spin around earth
			//35 days for one rotation of sun
			//365 days for sun to fully rotate around sun
			//1 day for earth to rotate
			//to change the speed just change the earth values
			earthx = 0, earthy = 5, earthz = 0; //earth rotation
			systemx = earthx/365, systemy = earthy/365, systemz = earthz/365; //earth + moon rotation around the sun
			moonx = earthx/28, moony = earthy/28, moonz = earthz/28; //moon rotation around earth
			sunx = earthx/35, suny = earthy/35, sunz = earthz/35; //sun rotation
			m_e.earth.rotate_mc(earthx,earthy,earthz, 0.5); //rotate the earth
			m_e.rotate_origin(systemx,systemy,systemz, 0.5); //rotate earth + moon around the sun
			sun.rotate_mc(sunx,suny,sunz,0.5); //rotate sun
			m_e.rotate_mc(moonx,moony,moonz,0.5); //rotate the moon around the earth
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
			myCurve.reset();
			generated = 0;
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
 * RotateMenu
 * 	a function that deals with Rotation options
 * 	Parameters:
 * 		rotateOption: the rotate option
 * 	Returns:
 * 		none
 */
void RotateMenu(GLint rotateOption){
	//Rotate Menu
	switch (rotateOption) {
	case 1:
		myCurve.R = 45;
		break;
	case 2:
		myCurve.R = 90;
		break;
	case 3:
		myCurve.R = 135;
		break;
	case 4:
		myCurve.R = 180;
		break;
	case 5:
		myCurve.R = 225;
		break;
	case 6:
		myCurve.R = 270;
		break;
	case 7:
		myCurve.R = 315;
		break;
	case 8:
		myCurve.R = 360;
		break;
	case 9:
		myCurve.S = 5;
		break;
	case 10:
		myCurve.S = 10;
		break;
	case 11:
		myCurve.S = 15;
		break;
	case 12:
		myCurve.T = 5;
		break;
	case 13:
		myCurve.T = 10;
		break;
	case 14:
		myCurve.T = 15;
		break;
	case 15:
		myCurve.T = 20;
		break;
	case 16:
		myCurve.T = 25;
		break;
	default:
		break;
	}
	glutPostRedisplay();
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
	/*
	 * Control Point Selection - 1
	 * Bezier Curve Generation - 2
	 * X Axis Rotate - 3
	 * Mesh Without Lighting - 4
	 * Solid With Lighting - 5
	 * Improved Solar System - 6
	 */
	glutIdleFunc(NULL);
	solar = 0;
	glDisable(GL_TEXTURE_2D);
	if(menuOption == 1){
		curve_gen = 1;
		rotated = 0;
	}else if(menuOption == 2){
		generated = 1;
		curve_gen = 1;
		rotated = 0;
	}else if(menuOption == 3){
		curve_gen = 0;
		selected = 2;
		rotated = 1;
	}else if(menuOption == 4){
		solid = 0;
		light = 0;
		rotated = 1;
		curve_gen = 0;
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glDisable( GL_NORMALIZE);
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_LIGHT0);
	}else if(menuOption == 5){
		solid = 1;
		light = 1;
		glEnable(GL_DEPTH_TEST); // enable OpenGL depth buffer algorithm for hidden surface removal
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable( GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHT0);
		glCullFace(GL_BACK);
	}else if(menuOption == 6){
		solar = 1;
		curve_gen = 0;
		generated = 0;
		glutIdleFunc(move);
		glClearColor(0.0, 0.0, 0.0, 1.0); // Set display-window color to black
		glEnable(GL_TEXTURE_2D);

		glMatrixMode(GL_PROJECTION);
		gluPerspective(vangle, 1.0, dnear, dfar);

		glMatrixMode(GL_MODELVIEW);

		gluLookAt(myCam.Eye.x, myCam.Eye.y, myCam.Eye.z, myCam.Rotate.x, myCam.Rotate.y, myCam.Rotate.z, myCam.ViewNorm.x, myCam.ViewNorm.y, myCam.ViewNorm.z);

		glEnable(GL_DEPTH_TEST);

		glEnable( GL_NORMALIZE);

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

		// Set up simple lighting model
		glEnable( GL_LIGHTING);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, positionSolar);
		glEnable( GL_LIGHT0);

		// Enable material properties for lighting
		glEnable( GL_COLOR_MATERIAL);
		glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1);

		glEnable( GL_CULL_FACE);
		glEnable( GL_TEXTURE_2D);
		// disable GLSL shader
		glUseProgram(0);

	}
	glutPostRedisplay();
}

/*
 * glslSubMenu
 * 	a function to deals with glsl on and off
 * 	Parameters:
 * 		glslOption: the option selected
 * 	Returns:
 * 		none
 */
void glslSubMenu(GLint glslOption){
	switch (glslOption) {
	case 1:
		// use GLSL shader
		if(solar == 0){
			glUseProgram(programObject);
		}
		break;
	case 2:
		// disable GLSL shader
		glUseProgram(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

/*
 * ObjectMenu
 * a function the deals with all the object menu options
 * Parameters:
 * 	ObjectOption: the object selected
 * Returns:
 * 	none
 */
void ObjectMenu(GLint ObjectOption){
	//Object menu
	/*
	 * Cube - 1
	 * Curve - 2
	 */
	if(ObjectOption == 1){
		 //cube
		selected = 1;
	}else if(ObjectOption == 2){
		// bezier curve
		selected = 2;
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
	GLint WCTrans_Menu, VCTrans_Menu, MCTrans_Menu, Light_Menu, A_Menu, View_Menu, Rotate_Menu, Object_Menu, glsl_shad;
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

	//Rotate_Menu
	Rotate_Menu = glutCreateMenu(RotateMenu);
	glutAddMenuEntry(" R_45 ", 1);
	glutAddMenuEntry(" R_90 ", 2);
	glutAddMenuEntry(" R_135 ", 3);
	glutAddMenuEntry(" R_180 ", 4);
	glutAddMenuEntry(" R_225 ", 5);
	glutAddMenuEntry(" R_270 ", 6);
	glutAddMenuEntry(" R_315 ", 7);
	glutAddMenuEntry(" R_360 ", 8);
	glutAddMenuEntry(" S_5 ", 9);
	glutAddMenuEntry(" S_10 ", 10);
	glutAddMenuEntry(" S_15 ", 11);
	glutAddMenuEntry(" T_5 ", 12);
	glutAddMenuEntry(" T_10 ", 13);
	glutAddMenuEntry(" T_15 ", 14);
	glutAddMenuEntry(" T_20 ", 15);
	glutAddMenuEntry(" T_25 ", 16);


	//Object menu
	Object_Menu = glutCreateMenu(ObjectMenu);
	glutAddMenuEntry(" Cube ", 1);
	glutAddMenuEntry(" Bezier Curve ", 2);

	//shadding off or on
	glsl_shad = glutCreateMenu(glslSubMenu);
	glutAddMenuEntry(" On ", 1);
	glutAddMenuEntry(" Off ", 2);

	//A_3 menu
	A_Menu = glutCreateMenu(AMenu);
	glutAddMenuEntry(" Control Point Selection ", 1);
	glutAddMenuEntry(" Bezier Curve Generation ", 2);
	glutAddSubMenu(" Rotation Options", Rotate_Menu);
	glutAddMenuEntry(" X Axis Rotate", 3);
	glutAddMenuEntry(" Mesh Without Lighting", 4);
	glutAddMenuEntry(" Solid With Lighting", 5);
	glutAddMenuEntry(" Improved Solar System", 6);
	glutAddSubMenu(" GLSL", glsl_shad);


	//view menu
	View_Menu = glutCreateMenu(ViewMenu);
	glutAddMenuEntry(" Show Point Light ", 1);
	glutAddMenuEntry(" Hide Point Light ", 2);

	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	glutAddMenuEntry(" Reset ", 1);
	glutAddSubMenu(" A4 Menu", A_Menu);
	glutAddSubMenu(" Select Object ", Object_Menu);
	glutAddSubMenu(" Model Transformations ", MCTrans_Menu);
	glutAddSubMenu(" WC Transformations ", WCTrans_Menu);
	glutAddSubMenu(" View Transformations ", VCTrans_Menu);
	glutAddSubMenu(" Light Transformations", Light_Menu);
	glutAddSubMenu(" View", View_Menu);
	glutAddMenuEntry(" Quit", 2);
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
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
