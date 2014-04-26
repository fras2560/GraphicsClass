/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: Leg.cpp
 */
#include "Leg.hpp"

Leg::Leg(){
	calves = new Rect(8,2,2,1);
	calves->scale_change(-.95);
	foot = new Rect(2,2,4,2);
	foot->scale_change(-.95);
	foot->translate(0,-.25,.05);
}

/*
 * draw
 * 	a method to draw the Leg
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Leg::draw(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    foot->draw();
    calves->draw();
    glPopMatrix();
}

/*
 * draw_solid()
 * 	a method to draw a solid leg
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Leg::draw_solid(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    foot->draw_solid();
    calves->draw_solid();
    glPopMatrix();
}
/*
 * reset
 * 	a method to reset the leg to initial position
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Leg::reset_leg(){
	this->reset();
	foot->reset();
	calves->reset();
	foot->translate(0,-.2,.05);
}
