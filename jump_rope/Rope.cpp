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
	this->translate(0,.4,0);
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

/*
 * collision_precheck
 * 	is a method that returns true if the rope is in a position where may be
 * 	colliding with the human model
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		true: if collision is possible
 * 		false: otherwise
 */
GLboolean Rope::collision_precheck(){
	GLint position = ((GLint) rotations) % 360; //get the the number of rotations from top
	GLboolean result = false;
	if(position < 5 or position > 355){
		//top position
		result = true;
	}else if( position > 175 and position < 185){
		//bottom position
		result = true;
	}
	return result;
}

/*
 * collision_check
 * 	a method to check whether there is collision between rope and human
 * 	Parameters:
 * 		model: a pointer to the human
 * 	Returns:
 * 		true: if there is collision
 * 		false: otherwise
 */
GLboolean Rope::collision_check(Human * model){
	GLboolean result = false;
	GLint position = ((GLint) rotations) % 360; //get the the number of rotations from top
	if(position < 5 or position > 355){
		//top position
		result = check_top(model);
	}else if( position > 175 and position < 188){
		//bottom position
		result = check_bottom(model);
	}
	return result;
}

/*
 * check_top
 * 	a method that checks whether the rope collided with the human top
 * 	Parameters:
 * 		model: the human model to check
 * 	Returns:
 * 		true: if collision
 * 		false: otherwise
 */
GLboolean Rope::check_top(Human * model){
	GLboolean result = false;
	GLfloat up = model->get_up(), down = model->get_down();
	GLfloat jumped  = up + down;
	if(jumped > 200){
		result = true;
	}

	return result;
}

/*
 * check_bottom
 * 	a method that checks whether the rope collided witht he human bottom
 * 	Parameters:
 * 		model: the human model to check
 * 	Returns:
 * 		true: if collision
 * 		false: otherwise
 */
GLboolean Rope::check_bottom(Human * model){
	GLboolean result = false;
	GLfloat jumped  = model->up + model->down;
	if(jumped < 5){
		result = true;
	}
	return result;
}

/*
 * reset_rope
 * 	a method that reset the rope position
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Rope::reset_rope(){
	this->reset();
	this->translate(0,.4,0);
	rope->reset();
	speed = 1.0;
	rotations = 0;
	spins = 0;
	increment = 0.001;
}

/*
 * map_texture
 * 	a method that maps the rope texture
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Rope::map_texture(){
	//initial rope texture map
	GLuint text[3];
	glGenTextures(3, text);
	//bind the rope texture
	glBindTexture(GL_TEXTURE_2D, text[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name[] = "fire.bmp";
	Image i;
	i.load_image(name);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, i.sizeX, i.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, i.data);
	set_texture(text[0]);
}
