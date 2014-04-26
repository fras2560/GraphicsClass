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
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Rectangle.hpp"
#include "Background.hpp"
#include "Foreground.hpp"
#include "Human.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Rope.hpp"


//prototypes
void move(void);
void init(void);
void mainMenu(GLint);
void menu();
void controlMenu(GLint);
void display(void);
void speedMenu(GLint);
void mouseAction(int,int,int,int);
void mouseMotion(GLint, GLint);
void playSong();
void displayGameOver();
void displayScore();
void renderBitmapString(GLfloat, GLfloat, void *,const char *);
void gameOver();

//window width and height
GLint winWidth = 800, winHeight = 800;
/*  Set coordinate limits for the clipping window:  */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;
/*  Set positions for near and far clipping planes:  */
GLfloat vangle = 40.0, dnear = 1.0, dfar = 100.0;
GLint moving = 0, xBegin = 0, coordinate = 1, type = 4, selected=0, stereo=0, light=0, shading=0;
GLint gametime = 0, speed = 1000, song = 0, gameover=0, score=0;
Foreground foreground;
Background background;
Human * human;
Rope * rope;
//my camera object
Camera myCam;
//my light Object
Light myLight;


/*
 * keyboard
 * 	a method that deals with keys presses
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
    case 's':case'S':
    	//pre power up
    	human->bend();
    	break;
    case 'w':case'W':case' ':
    	//get ready to jump
    	if(human->jumping == false){
        	human->bending = true;
    	}
    	break;
    case 'a':case'A':
    	//rotate cam left
		myCam.rotate(0.0, 1.0, 0.0, 1*0.5);
		break;
    case 'd':case'D':
    	//rotate cam right
		myCam.rotate(0.0, 1.0, 0.0, -1*0.5);
		break;
    }
    glutPostRedisplay();
}

/*
 * keyUp
 * 	a method that deals with keys up
 * 	Parameters:
 * 		char: the character that was released
 * 		x: the x coordinate of the mouse on key release
 * 		y: the y coordinate of the mouse on key release
 * 	Returns:
 * 		none
 */
void keyUp (unsigned char key, int x, int y) {
	switch( key ){
	case 'w':case'W':case' ':
		human->jumping = true;
    	break;
	}
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
			myLight.Reset();
			human->reset_human();
			rope->reset_rope();
			myCam.CameraReset(1);
			gameover = 0;
		}
			break;
		case 2:{
			//draw a wire model
			human->solid = false;
		}
			break;
		case 3:{
			//full model
			human->solid = true;
		}
			break;
		case 4:{
			playSong();
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
 * controlMenu
 * a method that needs to be implemented for glut to display controls
 * Parameters:
 * 	option:the option selected
 * Returns:
 * 	none
 */
void controlMenu(GLint option){
	//nothing has to happen on click
}

/*
 * speedMenu
 * 	a method that adjusts the game speed depending on which option was selected
 * 	Parameters:
 * 		option: the selected option
 * 	Returns:
 * 		none
 */
void speedMenu(GLint option){
	//an increase in speed slows down the game
	if(option == 1){
		speed = 1;
	}else if(option == 2){
		speed = 10;
	}else if(option == 3){
		speed = 100;
	}else if(option == 4){
		speed = 1000;
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
	GLint Controls_Menu, Speed_Menu;
	//controls menu
	Controls_Menu = glutCreateMenu(controlMenu);
	glutAddMenuEntry(" Jump - w or W or spacebar ", 1);
	glutAddMenuEntry(" Bend: s or s ", 2);
	glutAddMenuEntry(" Rotate Camera left: a or A", 3);
	glutAddMenuEntry(" Rotate Camera right: d or D", 4);
	//speed menu
	Speed_Menu = glutCreateMenu(speedMenu);
	glutAddMenuEntry(" Speed - 1000x", 1);
	glutAddMenuEntry(" Speed - 100x ", 2);
	glutAddMenuEntry(" Speed - 10x", 3);
	glutAddMenuEntry(" Speed - 1x", 4);
	//main menu
	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	glutAddMenuEntry(" New Game", 1);
	glutAddSubMenu(" Controls", Controls_Menu);
	glutAddSubMenu(" Speed", Speed_Menu);
	glutAddMenuEntry(" Wire Model", 2);
	glutAddMenuEntry(" Model", 3);
	glutAddMenuEntry(" Play Song", 4);
	glutAddMenuEntry(" Quit", 5);
}

/*
 * move
 * that function that moves the cube
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void move(void){
	gametime += 1;
	if(human->can_jump == false){
		gameOver();
	}else{
		if (gametime % speed == 0){
			human->jump(); //call and see if variables are needed
			rope->spin();
			if (rope->collision_precheck() == true){
				if(rope->collision_check(human) == true){
					human->falling = true;
				}
			}
			score = rope->spins;
			glutPostRedisplay();
		}
	}
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
		glutPostRedisplay();
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	myCam.CameraReset(1);
	myCam.screenWidth = winWidth;
	myCam.screenHeight = winHeight;
	gluLookAt(myCam.Eye.x, myCam.Eye.y, myCam.Eye.z, myCam.Rotate.x, myCam.Rotate.y, myCam.Rotate.z, myCam.ViewNorm.x, myCam.ViewNorm.y, myCam.ViewNorm.z);
	//Enable openGL depth buffer algorithm
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	glutIdleFunc(move);
	//initiall all texture maps
	human = new Human();
	human->map_textures();
	rope = new Rope();
	rope->map_texture();
	background.map_texture();
	foreground.map_texture();
	playSong();
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
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(vangle, 1.0, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(myCam.Eye.x, myCam.Eye.y, myCam.Eye.z, myCam.Rotate.x, myCam.Rotate.y, myCam.Rotate.z, myCam.ViewNorm.x, myCam.ViewNorm.y, myCam.ViewNorm.z);

	//draw_axis();
	myLight.draw();
	human->draw();
	rope->draw_solid();
	background.draw();
	foreground.draw();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
	glRasterPos2i(10, 10);
	if(gameover == 0){
		displayScore();
	}else{
		displayGameOver();
	}
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
	glFlush();
	glutSwapBuffers();
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
	glutPostRedisplay();
}

/*
 * playSong
 * 	a method that plays a song
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void playSong(){
	if(song == 0){
		PlaySound((LPCSTR) "House of Pain - Jump Around.wav", NULL, SND_FILENAME | SND_ASYNC);
	}else if(song == 1){
		PlaySound((LPCSTR) "Space Jam Theme Song.wav", NULL, SND_FILENAME | SND_ASYNC);
	}else if(song == 2){
		PlaySound((LPCSTR) "Wake me up Before you Go Go- lyrics.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	song = (song + 1) % 3;
}

/*
 * gameOver a method that gets called on when game is over
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void gameOver(){
	if(gameover == 0){
		displayGameOver();
		gameover = 1;
		PlaySound((LPCSTR) "GAME OVER (Deep Voice) - Sound Effect.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	glutPostRedisplay();
}

/*
 * displayScore
 * 	a method to display the score
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void displayScore(){
	string name = "Score: ";
	ostringstream sstm;
	sstm << name << score;
	string result;
	result = sstm.str();
	renderBitmapString(winWidth/2, winHeight/4, GLUT_BITMAP_HELVETICA_18, result.c_str());
}

/*
 * displayGameOver
 * 	a method to display game over
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void displayGameOver(){
	renderBitmapString(winWidth/2, winHeight/4, GLUT_BITMAP_HELVETICA_18, "GAME OVER");
	string name = "Final Score: ";
	ostringstream sstm;
	sstm << name << score;
	string result;
	result = sstm.str();
	renderBitmapString(winWidth/2, winHeight/4-20, GLUT_BITMAP_HELVETICA_18, result.c_str());
}

/*
 * renderBitmapString
 * 		a function that prints the string at (x,y)
 * 	Parameters:
 * 		x: the x coordinate
 * 		y: the y coordinate
 * 		font: the glut bitmap font
 * 		string: the string to be printed
 */
void renderBitmapString(GLfloat x, GLfloat y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// the main function
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Jump Rope (Written by Dallas Fraser)");
	glewInit();
	init();
	menu();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
