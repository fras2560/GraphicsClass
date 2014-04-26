/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: UpperBody.cpp
 */
#include "UpperBody.hpp"
#include <stdio.h>
using namespace std;
UpperBody::UpperBody(){
	arm1 = new Arm();
	arm1->translate(-.29,.3,0);
	arm2 = new Arm();
	arm2->translate(.29,.3,0);
	body = new Bezier();
	body->add_control_point(-1,0.1);
	body->add_control_point(-.5,1);
	body->add_control_point(0.5,1);
	body->add_control_point(1,0.15);
	body->R=360;
	body->S = 20;
	body->generate_bezier(1000);
	abdomen = new Rect(2,8,2,1);
	abdomen->scale_change(-.94);
	body->scale_change(30.0);
	GLint rx,rz,ry;
	rx = body->getMC().mat[0][2];
	ry = body->getMC().mat[1][2];
	rz = body->getMC().mat[2][2];
	body->rotate_mc(rx,ry,rz,-90);
	body->translate(0,.25,0);
	arm1->scale_change(-.2);
	arm2->scale_change(-.2);
	rx = arm1->getMC().mat[0][2];
	ry = arm1->getMC().mat[1][2];
	rz = arm1->getMC().mat[2][2];
	arm1->rotate_mc(rx,rz,rz, 25);
	rx = arm2->getMC().mat[0][2];
	ry = arm2->getMC().mat[1][2];
	rz = arm2->getMC().mat[2][2];
	arm2->rotate_mc(rx,rz,rz, -25);
	max_bend = 25;
	bends = 0;

}


UpperBody::~UpperBody(){

}

/*
 * draw
 * 	a method to draw the upper body
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void UpperBody::draw(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    arm1->draw();
    arm2->draw();
    body->solid = false;
    abdomen->draw();
    body->draw();
    glPopMatrix();
}

/*
 * draw_solid
 * 	a method to draw the upper body solid
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void UpperBody::draw_solid(){
	glPushMatrix();
    this->ctm_multiply();
    glScalef(s, s, s);
    arm1->draw_solid();
    arm2->draw_solid();
    abdomen->draw_solid();
    body->solid = true;
    body->draw();
    glPopMatrix();
}

/*
 * bend_arms
 * 	a method to bend the arms of the upper body
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void UpperBody::bend_arms(){
	if(bends < max_bend){
		bends++;
		arm1->bend_arm();
		arm2->bend_arm();
	}
}

/*
 * unbend_arms
 * 	a method to unbend the arms of the upper body
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void UpperBody::unbend_arms(){
	if(bends > 0){
		bends--;
		arm1->unbend_arm();
		arm2->unbend_arm();
	}
}

/*
 * reset
 * 	a method to reset the upper body to initial position
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void UpperBody::reset_upperbody(){
	this->reset();
	arm1->reset_arm();
	arm1->translate(-.29,.3,0);
	arm2->reset_arm();
	arm2->translate(.29,.3,0);
	abdomen->reset();
	GLfloat rx,rz,ry;
	rx = arm1->getMC().mat[0][2];
	ry = arm1->getMC().mat[1][2];
	rz = arm1->getMC().mat[2][2];
	arm1->rotate_mc(rx,ry,rz, 25);
	rx = arm2->getMC().mat[0][2];
	ry = arm2->getMC().mat[1][2];
	rz = arm2->getMC().mat[2][2];
	arm2->rotate_mc(rx,ry,rz, -25);
	max_bend = 25;
	bends = 0;
}

/*
 * set_body_texture
 * 	a method to set the body texture
 * 	Parameters:
 * 		t: the texture to set
 * 	Returns:
 * 		none
 */
void UpperBody::set_body_texture(GLuint t){
	body->set_texture(t);
}

/*
 * rotate_arms
 * 	a method to rotate the arms
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void UpperBody::rotate_arms(){
	GLfloat rx,rz,ry;
	//rotate in x
	rx = arm1->getMC().mat[0][0];
	ry = arm1->getMC().mat[1][0];
	rz = arm1->getMC().mat[2][0];
	arm1->rotate_mc(rx,ry,rz, 1);
	rx = arm2->getMC().mat[0][0];
	ry = arm2->getMC().mat[1][0];
	rz = arm2->getMC().mat[2][0];
	arm2->rotate_mc(rx,ry,rz, .5);
}
