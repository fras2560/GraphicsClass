/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/24/2013
 *	File: Background.cpp
 */

#include "Background.hpp"

Background::Background(){
	texture = 0;
    vertex[0][0] = -1;vertex[0][1] = -1;vertex[0][2] = -1;
    vertex[1][0] = -1;vertex[1][1] = 1; vertex[1][2] = -1;
    vertex[2][0] = 1;vertex[2][1] = -1; vertex[2][2] = -1;
    vertex[3][0] = 1;vertex[3][1] = 1;vertex[3][2] = -1;
    vertex[4][0] = -1;vertex[4][1] = -1;vertex[4][2] = 1;
    vertex[5][0] = -1;vertex[5][1] = 1; vertex[5][2] = 1;
    vertex[6][0] = 1;vertex[6][1] = -1;vertex[6][2] = 1;
    vertex[7][0] = 1;vertex[7][1] = 1;vertex[7][2] = 1;

//    faces[0][0] = 0;faces[0][1] = 1;faces[0][2] = 3; faces[0][3] = 2;
//    faces[1][0] = 2;faces[1][1] = 3;faces[1][2] = 7;faces[1][3] = 6;
//    faces[2][0] = 6;faces[2][1] = 7;faces[2][2] = 5;faces[2][3] = 4;
//    faces[3][0] = 4;faces[3][1] = 5;faces[3][2] = 1;faces[3][3] = 0;

    faces[0][0] = 0;faces[0][1] = 1;faces[0][2] = 3; faces[0][3] = 2;
    faces[1][0] = 3;faces[1][1] = 7;faces[1][2] = 6;faces[1][3] = 2;
    faces[2][0] = 7;faces[2][1] = 5;faces[2][2] = 4;faces[2][3] = 6;
    faces[3][0] = 4;faces[3][1] = 5;faces[3][2] = 1;faces[3][3] = 0;
    this->scale_change(18);
    this->translate(3,4,2);
}

/*
 * set_texture
 * 	a method to set the texture of the background
 * 	Parameters:
 * 		t: the texture to set to
 * 	Returns:
 * 		none
 */
void Background::set_texture(GLuint t){
	texture = t;
}

/*
 * draw
 * 	a method to draw the background
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Background::draw(){
	glPushMatrix();
	this->ctm_multiply();
	glScalef(s, s, s);
	for(GLint i = 0; i<4;i++){
		if(texture == 0){
			glColor3f(1, 1, 1);
			glBegin(GL_POLYGON);
		    glVertex3fv(&vertex[faces[i][0]][0]);
		    glVertex3fv(&vertex[faces[i][1]][0]);
		    glVertex3fv(&vertex[faces[i][2]][0]);
		    glVertex3fv(&vertex[faces[i][3]][0]);
		    glEnd();
		}else if(i == 0 or i == 3) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_POLYGON);
			glTexCoord2f( 0, 0);
		    glVertex3fv(&vertex[faces[i][0]][0]);
			glTexCoord2f( 0, 1);
			glVertex3fv(&vertex[faces[i][1]][0]);
			glTexCoord2f( 1,1);
			glVertex3fv(&vertex[faces[i][2]][0]);
			glTexCoord2f( 1,0);
			glVertex3fv(&vertex[faces[i][3]][0]);
		    glEnd();
			glDisable(GL_TEXTURE_2D);
		}else if (i == 1 or i == 2){
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_POLYGON);
			glColor3f(.8,1,1);
		    glVertex3fv(&vertex[faces[i][0]][0]);
			glVertex3fv(&vertex[faces[i][1]][0]);
			glVertex3fv(&vertex[faces[i][2]][0]);
			glVertex3fv(&vertex[faces[i][3]][0]);
		    glEnd();
		}
	}
	//printf("\n\n");
	glPopMatrix();
}


/*
 * map_texutre
 * 	a method that maps the texture of the background
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Background::map_texture(){
	GLuint text[3];
	glGenTextures(3, text);
	glBindTexture(GL_TEXTURE_2D, text[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char name[] = "background.bmp";
	Image i;
	i.load_image(name);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, i.sizeX, i.sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, i.data);
	set_texture(text[1]);
}
