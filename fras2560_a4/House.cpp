/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: House.hpp
 */


#include "House.hpp"
#include <stdio.h>
House::House()
{
	cube =  Cube();
	pyramid = Pyramid();
}

/*
 * draw
 * 	a method that draws the house
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void House::draw()
{
    glPushMatrix();
    this->ctm_multiply();
	glScalef(s, s, s);
	cube.draw_simple();
	glPopMatrix();

	glPushMatrix();
	this->ctm_multiply();
	glScalef(s, s, s);
	glTranslatef(0,1,0);
	pyramid.draw_simple();
	glPopMatrix();
}
