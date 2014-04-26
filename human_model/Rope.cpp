/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Rope.cpp
 */

#include "Rope.hpp"
#include <stdio.h>
using namespace std;

Rope::Rope(){
	rope = new Bezier();
	rope->add_control_point(-1,0,0);
	rope->add_control_point(0,2,0);
	rope->add_control_point(1,0,0);
	rope->R = 5;
	rope->generate_bezier(1000);
	rope->scale_change(100);
	speed = 1.0;
	rotations = 0;
	spins = 0;
	increment = 0.001;
	end1 = new Rect(2,4,2,1);
	end2 = new Rect(2,4,2,1);
	end1->scale_change(-.95);
	end2->scale_change(-.95);
	end1->translate(-1.1,0,0);
	end2->translate(1.1,0,0);
}

/*
 * draw
 * 	a method that draws a rope
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Rope::draw(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    rope->solid = false;
    rope->draw();
    end1->draw();
    end2->draw();
    glPopMatrix();
    printf("drew rope\n");
}

/*
 * draw_solid
 * 	a method that draws a solid rope
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Rope::draw_solid(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    rope->solid = true;
    rope->draw();
    end1->draw_solid();
    end2->draw_solid();
    glPopMatrix();
}

/*
 * spin
 * 	a method the rotates the rope
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Rope::spin(){
	GLfloat rx,ry,rz;
	//rotate in x axis
	rx = rope->getMC().mat[0][0];
	ry = rope->getMC().mat[1][0];
	rz = rope->getMC().mat[2][0];
	rope->rotate_mc(rx,ry,rz, speed);
	rotations += speed;
	speed += increment;
	if(rotations >= 360){
		spins += 1;
		rotations = 0;
	}
}

/*
 * set_texture
 * 	a method that sets the texture
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Rope::set_texture(GLuint t){
	this->rope->set_texture(t);
}

