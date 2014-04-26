/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: Arm.cpp
 */
#include "Arm.hpp"

Arm::Arm(){
	lowerArm = new ForeArm();
	//lowerArm->scale_change(-.96);
	lowerArm->translate(0,-.4,0);
	upperArm = new Rect(8,2,2,3);
	upperArm->scale_change(-.96);
	upperArm->translate(0,0,0);
}

Arm::~Arm(){

}

/*
 * reset
 * 	a method to reset the arm to its initial position
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Arm::reset_arm(){
	this->reset();
	lowerArm->reset_forearm();
	lowerArm->translate(0,-0.4,0);
	upperArm->reset();
	upperArm->translate(0,0,0);
}

/*
 * draw
 * a method to draw the arm
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Arm::draw(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    lowerArm->draw();
    upperArm->draw();
    glPopMatrix();
}

/*
 * draw_solid
 * 	a method that will draw a solid arm
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Arm::draw_solid(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    lowerArm->draw_solid();
    upperArm->draw_solid();
    glPopMatrix();
}
/*
 * bend_arm
 * 	a method to bend the arm
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Arm::bend_arm(){
	GLfloat rx,ry,rz;
	rx = lowerArm->getMC().mat[0][0];
	ry = lowerArm->getMC().mat[1][0];
	rz = lowerArm->getMC().mat[2][0];
	lowerArm->rotate_mc(rx, ry, rz, 0.7);
	rx = upperArm->getMC().mat[0][0];
	ry = upperArm->getMC().mat[1][0];
	rz = upperArm->getMC().mat[2][0];
	upperArm->rotate_mc(rx, ry, rz, -0.7);
}

/*
 * unbend_arm
 * 	a method to bend the arm
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Arm::unbend_arm(){
	GLfloat rx,ry,rz;
	rx = lowerArm->getMC().mat[0][0];
	ry = lowerArm->getMC().mat[1][0];
	rz = lowerArm->getMC().mat[2][0];
	lowerArm->rotate_mc(rx, ry, rz, -0.7);
	rx = upperArm->getMC().mat[0][0];
	ry = upperArm->getMC().mat[1][0];
	rz = upperArm->getMC().mat[2][0];
	upperArm->rotate_mc(rx, ry, rz, 0.7);
}
