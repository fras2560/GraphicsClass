/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Planet.cpp
 */

#include "Planet.hpp"
#include <stdio.h>
using namespace std;

Planet::Planet(){
	radius = 1.0;
	stacks = 20;
	splices = 20;
	r = 1.0;
	b = 1.0;
	g = 1.0;
	texture = 0;
	sphere = NULL;
}
Planet::~Planet(){

}

/*
 * Planet constructor
 * Parameters:
 * 	planet: the planet to create 1 for sun and 2 for earth
 */
Planet::Planet(GLint planet){
	radius = 1.0;
	stacks = 20;
	splices = 20;
	if(planet == 1){
		//sun
		r = 1.0;
		b = 0.0;
		g = 0.0;
		this->scale_change(-.7);
	}else if(planet == 2){
		//earth
		r = 0.0;
		b = 1.0;
		g = 0.0;
		this->scale_change(-.9);
		this->translate(1.0, 0.0, 1.0);
	}
	texture = 0;
	sphere = NULL;

}

void Planet::set_texture(GLuint text){
	texture = text;
}

/*
 * set_colour
 * a function to set the colour of the planet
 * Parameters:
 * 	red: the amount of red
 * 	green: the amount of green
 * 	blue: the amount of blue
 * Returns:
 * 	none
 */
void Planet::set_colour(GLfloat red, GLfloat green, GLfloat blue){
	r = red;
	g = green;
	b = blue;
}

/*
 * draw
 * the function that draws the planet
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Planet::draw(){
	glPushMatrix();
	this->ctm_multiply();
	glBindTexture(GL_TEXTURE_2D, texture);
	glScalef(s, s, s);
	gluSphere(sphere,radius, splices, stacks);
	glPopMatrix();
	glEnd();
}
