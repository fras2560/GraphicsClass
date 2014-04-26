/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final
 *	Date: 11/19/2013
 *	File: Human.hpp
 */
#include "Human.hpp"
#include <stdio.h>
using namespace std;

Human::Human(){
	// the lower body
	bottom = new LowerBody();
	//create upper body and put on top of lower body
	top = new UpperBody();
	top->translate(0,.2,0);
	//create head and put in right position
	head = new Head();
	head->translate(0,.85,0);
	head->scale_change(.05);
	bends = 0; // the number of knee bends
	max_bend = 20; // the max amount of knee bend
	jumping = false; //whether the human is jumping or not
	bending = false; //whether the human is bending or not
	stage = 0; // the stage of the animation
	a = -4.9; //the deceleration of gravity
	v = 0; //velocity of the jump
	bent = 0; //how many power has been build up (knee bends)
	up = 0; //how much has been travelled up in the jump
	down = 0; // how much has been travelled down in the jump
	solid = true; //whether to draw a solid human or a wire
	falling = false; //whether the huma is falling or not
	rotations = 0; //the number of rotations for falling
	can_jump = true;
}

Human::~Human(){

}

/*
 * draw
 * 	a method to draw the human
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Human::draw(){
	glPushMatrix();
	this->ctm_multiply();
	if(solid == true){
		bottom->draw_solid();
		top->draw_solid();
		head->draw_solid();
	}else{
		bottom->draw();
		top->draw();
		head->draw();
	}
	glPopMatrix();
	glEnd();
}

/*
 * bend
 * 	a method to bend the human
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Human::bend(){
	if(bends < max_bend){
		top->bend_arms();
		bottom->bend_legs();
		head->translate(0,-0.005,0);
		top->translate(0,-0.005,0);
		bends++;
	}
}

/*
 * unbend
 * 	a method to unbend the human
 * 	Pamameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Human::unbend(){
	if(bends > 0){
		top->unbend_arms();
		bottom->unbend_legs();
		head->translate(0,0.005,0);
		top->translate(0,0.005,0);
		bends--;
	}
}

/*
 * jump
 * 	a method that continually called will make the player jump depening on
 * 	how long the player builds up power based on bending of the knees
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Human::jump(){
	if(can_jump == true){
		if(falling == false){
			if (bending == true and jumping == false){
				//bending stage
				printf("Here bending\n");
				bend();
				bent = bends;
				v = 4.9 * bent; //building up power
				down = 0;
				up = 0;
			}
			if(jumping == true and bent > 0){
				//jumping stage
				if(stage == 0){
					//on the way up
					if(v <= 0){
						stage = 1;
					}else{
						printf("Way up v:%f\n", v);
						unbend();
						this->translate(0,v*.001,0);
						up += v;
						v += a;
					}
				}else if(stage == 1){
					//on the way down
					if(v <= (a * bent) ){
						printf("Difference between up - down: %f\n", (up+down));
						this->translate(0,-0.001*(up+down),0);
						up = 0;
						down = 0;
						stage = 2;
					}else{
						printf("Way down v:%f\n", v);
						this->translate(0,v*.001,0);
						down+=v;
						v += a;
					}
				}else if(stage == 2){
					//bending stage on land
					bend();
					if(bends == bent){
						stage = 3;
					}
				}else if(stage == 3){
					//unbending on land
					unbend();
					if(bends == 0){
						stage = 0;
						jumping = false;
						bent = 0;
						bending = false;
					}
				}
			}else{
				if(jumping == true and bent == 0){
					jumping = false;
					down = 0;
					up = 0;
				}
			}
		}else{
			fall();
		}
	}
}

void Human::fall(){
	if(rotations != 90){
		GLfloat rx,ry,rz;
		//top->bend_arms();
		top->rotate_arms();
		//rotate y
		rx = this->getMC().mat[0][1];
		ry = this->getMC().mat[1][1];
		rz = this->getMC().mat[2][1];
		this->rotate_mc(rx,ry,rz, -.55);
		//rotate x
		rx = this->getMC().mat[0][0];
		ry = this->getMC().mat[1][0];
		rz = this->getMC().mat[2][0];
		this->rotate_mc(rx,ry,rz, -.30);

		//rotate z
		rx = this->getMC().mat[0][2];
		ry = this->getMC().mat[1][2];
		rz = this->getMC().mat[2][2];
		this->rotate_mc(rx,ry,rz, 1);
		rotations ++;
	}else{
		falling = false;
		jumping = false;
		can_jump = false;
	}
}

/*
 * reset
 * 	a method to reset the human to its initial position
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Human::reset_human(){
	this->reset();
	this->top->reset_upperbody();
	top->translate(0,.2,0);
	while(bends != 0){
		unbend();
	}
	max_bend = 20; // the max amount of knee bend
	jumping = false; //whether the human is jumping or not
	bending = false; //whether the human is bending or not
	stage = 0; // the stage of the animation
	a = -4.9; //the deceleration of gravity
	v = 0; //velocity of the jump
	bent = 0; //how many power has been build up (knee bends)
	up = 0;
	down = 0;
	can_jump = true;
}

/*
 * map_textures
 * 	a method to map all the textures of the human parts
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Human::map_textures(){
	//create some textures
	Image i1;
	Image i2;
	Image i3;
	Image i4;
	Image i5;
	GLuint text[5];
	glGenTextures(5, text);

	//bind the head texture
	glBindTexture(GL_TEXTURE_2D, text[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name[] = "Mario_Face.bmp";
	i1.load_image(name);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, i1.sizeX, i1.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, i1.data);
	head->set_texture(text[0]);
	gluQuadricDrawStyle(head->sphere, GLU_FILL);
	gluQuadricTexture(head->sphere, GL_TRUE);
	gluQuadricNormals(head->sphere, GLU_SMOOTH);

	//bind the shirt texture
	glBindTexture(GL_TEXTURE_2D, text[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name2[] = "shirt_doe.bmp";
	i2.load_image(name2);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, i2.sizeX, i2.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, i2.data);
	top->set_body_texture(text[1]);
	top->arm1->upperArm->set_texture(text[1]);
	top->arm1->upperArm->set_texture(text[1]);
	top->arm1->lowerArm->forearm->set_texture(text[1]);
	top->arm2->upperArm->set_texture(text[1]);
	top->arm2->upperArm->set_texture(text[1]);
	top->arm2->lowerArm->forearm->set_texture(text[1]);


	//bind the shoe textures
	glBindTexture(GL_TEXTURE_2D, text[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name3[] = "shoe.bmp";
	i3.load_image(name3);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, i3.sizeX, i3.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, i3.data);
	bottom->leg1->foot->set_texture(text[2]);
	bottom->leg2->foot->set_texture(text[2]);

	//bind the shoe textures
	glBindTexture(GL_TEXTURE_2D, text[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name4[] = "pants.bmp";
	i4.load_image(name4);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, i4.sizeX, i4.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, i4.data);
	bottom->leg1->calves->set_texture(text[3]);
	bottom->leg2->calves->set_texture(text[3]);
	bottom->ham2->set_texture(text[3]);
	bottom->ham1->set_texture(text[3]);
	top->abdomen->set_texture(text[3]);

	//bind the glove
	glBindTexture(GL_TEXTURE_2D, text[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name5[] = "glove.bmp";
	i5.load_image(name5);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, i5.sizeX, i5.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, i5.data);
	top->arm2->lowerArm->hand->set_texture(text[4]);
	top->arm1->lowerArm->hand->set_texture(text[4]);
}
