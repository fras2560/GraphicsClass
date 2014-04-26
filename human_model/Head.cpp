/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: Head.hpp
 */

#include "Head.hpp"
#include <stdio.h>
using namespace std;

Head::Head(){
	radius = 1.0;
	stacks = 20;
	splices = 20;
	r = 1.0;
	b = 1.0;
	g = 1.0;
	sphere =gluNewQuadric();
	this->scale_change(0.-0.88);
	texture = 0;
	this->rotate_mc(1,0,0, -220);

}

Head::~Head(){

}

/*
 * set_texture
 *	a method to set the Head's texture
 *  Parameters:
 *  	t: the tecture to be set
 *  Returns:
 *  	none
 */
void Head::set_texture(GLuint t){
	texture = t;
}

/*
 * draw_solid
 * the function that draws the Head solid
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Head::draw_solid(){
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	this->ctm_multiply();
	glBindTexture(GL_TEXTURE_2D, texture);
	glScalef(s, s, s);
	gluSphere(sphere,radius, splices, stacks);
	glPopMatrix();
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/*
 * draw
 * the function that draws the Head
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Head::draw(){
	glPushMatrix();
	this->ctm_multiply();
	glScalef(s, s, s);
	gluSphere(sphere,radius, splices, stacks);
	glPopMatrix();
	glEnd();
}


/*
 * reset
 * 	a method to reset the Head
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Head::reset_head(){
	this->reset();
}
