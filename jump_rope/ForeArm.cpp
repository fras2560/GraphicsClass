/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: UpperBody.cpp
 */

#include "ForeArm.hpp"

ForeArm::ForeArm(){
	hand = new Rect();
	hand->scale_change(-.95);
	forearm = new Rect(8,2,2,3);
	forearm->scale_change(-.96);
	forearm->translate(0,.2,0);
}

ForeArm::~ForeArm(){

}

/*
 * reset_forearm
 * 	a method to reset the ForeArm to initial position
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void ForeArm::reset_forearm(){
	this->reset();
	hand->reset();
	forearm->reset();
	forearm->translate(0,.2,0);
}

/*
 * draw
 * 	a method to draw the forearm
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void ForeArm::draw(){
	glPushMatrix();
	this->ctm_multiply();
	glScalef(s, s, s);
	hand->draw();
	forearm->draw();
	glPopMatrix();
}

/*
 * draw_solid
 * 	a method for drawing a solid forearm
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void ForeArm::draw_solid(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    hand->draw_solid();
    forearm->draw_solid();
    glPopMatrix();
}
