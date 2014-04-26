/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Earth.cpp
 */

#include "Earth.hpp"

Earth::Earth(){
	moon.translate(0.2,0,0.2);
}

Earth::~Earth(){
}

/*
 * draw
 * the function that draws the planet (earth and moon)
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Earth::draw(){
	glPushMatrix();
	this->ctm_multiply();
	earth.draw();
	moon.draw();
	glPopMatrix();
	glEnd();
}



