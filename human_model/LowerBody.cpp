/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: LowerBody.cpp
 */
#include "LowerBody.hpp"

LowerBody::LowerBody(){
	leg1 = new Leg();
	leg2 = new Leg();
	leg1->translate(-.2,-.3,0);
	leg2->translate(.2,-.3,0);
	ham1 = new Rect(6,2,2,1);
	ham2 = new Rect(6,2,2,1);
	ham1->scale_change(-.95);
	ham1->translate(-.2,0.0,0.0);
	ham2->scale_change(-.95);
	ham2->translate(.2,0.0,0.0);
	bends= 0;
	max_bend = 25;
}

/*
 * bend_legs
 * 	a method to bend the legs of the lowerbody
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void LowerBody::bend_legs(){
	if(bends < max_bend){
		bends++;
		GLfloat rx,ry,rz;
		rx = ham1->getMC().mat[0][0];
		ry = ham1->getMC().mat[1][0];
		rz = ham1->getMC().mat[2][0];
		ham1->rotate_mc(rx, ry, rz, 0.5);
		rx = ham2->getMC().mat[0][0];
		ry = ham2->getMC().mat[1][0];
		rz = ham2->getMC().mat[2][0];
		ham2->rotate_mc(rx, ry, rz, 0.5);
		rx = leg1->getMC().mat[0][0];
		ry = leg1->getMC().mat[1][0];
		rz = leg1->getMC().mat[2][0];
		leg1->rotate_mc(rx, ry, rz, -0.5);
		rx = leg2->getMC().mat[0][0];
		ry = leg2->getMC().mat[1][0];
		rz = leg2->getMC().mat[2][0];
		leg2->rotate_mc(rx, ry, rz, -0.5);
	}
}

/*
 * unbend_legs
 * 	a method to unbend legs of the lower body
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void LowerBody::unbend_legs(){
	if(bends > 0){
		bends--;
		GLfloat rx,ry,rz;
		rx = ham1->getMC().mat[0][0];
		ry = ham1->getMC().mat[1][0];
		rz = ham1->getMC().mat[2][0];
		ham1->rotate_mc(rx, ry, rz, -0.5);
		rx = ham2->getMC().mat[0][0];
		ry = ham2->getMC().mat[1][0];
		rz = ham2->getMC().mat[2][0];
		ham2->rotate_mc(rx, ry, rz, -0.5);
		rx = leg1->getMC().mat[0][0];
		ry = leg1->getMC().mat[1][0];
		rz = leg1->getMC().mat[2][0];
		leg1->rotate_mc(rx, ry, rz, 0.5);
		rx = leg2->getMC().mat[0][0];
		ry = leg2->getMC().mat[1][0];
		rz = leg2->getMC().mat[2][0];
		leg2->rotate_mc(rx, ry, rz, 0.5);
	}
}

/*
 * draw
 * 	a method to draw the lower body
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void LowerBody::draw(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    leg1->draw();
    leg2->draw();
    ham1->draw();
    ham2->draw();
    glPopMatrix();
}

/*
 * draw_solid
 * 	a mehtod to draw the lower body solid
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void LowerBody::draw_solid(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    leg1->draw_solid();
    leg2->draw_solid();
    ham1->draw_solid();
    ham2->draw_solid();
    glPopMatrix();
}

/*
 * reset
 * 	a method to reset the lower body position
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void LowerBody::reset_lowerbody(){
	leg1->reset_leg();
	leg2->reset_leg();
	leg1->translate(-.2,-.3,0);
	leg2->translate(.2,-.3,0);
	ham1->reset();
	ham2->reset();
	ham1->translate(-.2,0.0,0.0);
	ham2->translate(.2,0.0,0.0);
	bends= 0;
	max_bend = 25;
}
