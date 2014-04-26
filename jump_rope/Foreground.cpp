/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/24/2013
 *	File: Foreground.cpp
 */

#include "Foreground.hpp"
extern GLint winWidth, winHeight;

Foreground::Foreground(){
	texture = 0;
	this->scale_change(-.99);
	this->translate(0,-0.6,0);
}

/*
 * set_texture
 * 	a method to set the texture of the foreground
 * 	Parameters:
 * 		t: the texture to set to
 * 	Returns:
 * 		none
 */
void Foreground::set_texture(GLuint t){
	texture = t;
}

/*
 * draw
 * 	a method to draw the foreground
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Foreground::draw(){
	glPushMatrix();
	this->ctm_multiply();
	glScalef(0.3, .1, 0.1);
	GLfloat vertex[4][3];
	vertex[0][0]=-winWidth/2, vertex[0][1] = 0, vertex[0][2] = winHeight/4;
	vertex[1][0]=-winWidth/2, vertex[1][1] = 0, vertex[1][2] = -winHeight/4;
	vertex[2][0]=winWidth/2, vertex[2][1] = 0, vertex[2][2] = -winHeight/4;
	vertex[3][0]=winWidth/2, vertex[3][1] = 0, vertex[3][2] = winHeight/4;
	if(texture == 0){
		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
	    glVertex3fv(&vertex[0][0]);
	    glVertex3fv(&vertex[1][0]);
	    glVertex3fv(&vertex[2][0]);
	    glVertex3fv(&vertex[3][0]);
	    glEnd();
	}else{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_POLYGON);
		glTexCoord2f( -1, -1);
		glVertex3fv(&vertex[0][0]);
		glTexCoord2f( 0, 2);
		glVertex3fv(&vertex[1][0]);
		glTexCoord2f( 2,2);
		glVertex3fv(&vertex[2][0]);
		glTexCoord2f( 2,0);
		glVertex3fv(&vertex[3][0]);
	    glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	//printf("\n\n");
	glPopMatrix();
}

/*
 * map_texutre
 * 	a method that maps the texture of the foreground
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Foreground::map_texture(){
	//initial rope texture map
	GLuint text[3];
	glGenTextures(3, text);
	//bind the rope texture
	//bind the background texture
	glBindTexture(GL_TEXTURE_2D, text[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name[] = "foreground.bmp";
	Image i;
	i.load_image(name);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, i.sizeX, i.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, i.data);
	set_texture(text[1]);
}



