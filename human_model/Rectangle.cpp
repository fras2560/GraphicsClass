/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: Final Assignment
 *	Date: 11/19/2013
 *	File: Rectangle.cpp
 */

#include <math.h>
#include <stdio.h>
#include "Rectangle.hpp"
Rect::Rect()
{
	norm_mc[0][0] = 0.0,norm_mc[0][1] = 0.0,norm_mc[0][2] = -1.0,
	norm_mc[1][0] = 1.0, norm_mc[1][1] = 0.0, norm_mc[1][2] = 0.0;
	norm_mc[2][0] = 0.0, norm_mc[2][1] = 0.0, norm_mc[2][2] = 1.0;
	norm_mc[3][0] = -1.0, norm_mc[3][1] = 0.0, norm_mc[3][2] = 0.0;
	norm_mc[4][0] = 0.0, norm_mc[4][1] = 1.0, norm_mc[4][2] = 0.0;
	norm_mc[5][0] = 0.0, norm_mc[5][1] = -1.0, norm_mc[5][2] = 0.0;

	norm_wc[0][0] = 0.0, norm_wc[0][1] = 0.0, norm_wc[0][2] = -1.0, norm_wc[0][3] = 0.0;
	norm_wc[1][0] = 1.0, norm_wc[1][1] = 0.0, norm_wc[1][2] = 0.0, norm_wc[1][3] = 0.0;
	norm_wc[2][0] = 0.0, norm_wc[2][1] = 0.0, norm_wc[2][2] = 1.0, norm_wc[2][3] = 0.0;
	norm_wc[3][0] = -1.0, norm_wc[3][1] = 0.0, norm_wc[3][2] = 0.0, norm_wc[3][3] = 0.0;
	norm_wc[4][0] = 0.0, norm_wc[4][1] = 1.0, norm_wc[4][2] = 0.0, norm_wc[4][3] = 0.0;
	norm_wc[5][0] = 0.0, norm_wc[5][1] = -1.0, norm_wc[5][2] = 0.0, norm_wc[5][3] = 0.0;

	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0; faceColor[0][2] = 1.0;
	faceColor[1][0] = 1.0, faceColor[1][1] = 0.0; faceColor[1][2] = 1.0;
	faceColor[2][0] = 1.0, faceColor[2][1] = 0.0; faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0, faceColor[3][1] = 0.0; faceColor[3][2] = 1.0;
	faceColor[4][0] = 1.0, faceColor[4][1] = 0.0; faceColor[4][2] = 1.0;
	faceColor[5][0] = 1.0, faceColor[5][1] = 0.0; faceColor[5][2] = 1.0;

    vertex[0][0] = -1;vertex[0][1] = -1;vertex[0][2] = -1;
    vertex[1][0] = -1;vertex[1][1] = 1; vertex[1][2] = -1;
    vertex[2][0] = 1;vertex[2][1] = -1; vertex[2][2] = -1;
    vertex[3][0] = 1;vertex[3][1] = 1;vertex[3][2] = -1;
    vertex[4][0] = -1;vertex[4][1] = -1;vertex[4][2] = 1;
    vertex[5][0] = -1;vertex[5][1] = 1; vertex[5][2] = 1;
    vertex[6][0] = 1;vertex[6][1] = -1;vertex[6][2] = 1;
    vertex[7][0] = 1;vertex[7][1] = 1;vertex[7][2] = 1;

	cubeWC[0][0] = -1, cubeWC[0][1] = -1, cubeWC[0][2] = -1, cubeWC[0][3] = 1;
	cubeWC[1][0] = -1, cubeWC[1][1] = 1, cubeWC[1][2] = -1, cubeWC[1][3] = 1;
	cubeWC[2][0] = 1, cubeWC[2][1] = -1, cubeWC[2][2] = -1, cubeWC[2][3] = 1;
	cubeWC[3][0] = 1, cubeWC[3][1] = 1, cubeWC[3][2] = -1, cubeWC[3][3] = 1;
	cubeWC[4][0] = -1, cubeWC[4][1] = -1, cubeWC[4][2] = 1, cubeWC[4][3] = 1;
	cubeWC[5][0] = -1, cubeWC[5][1] = 1, cubeWC[5][2] = 1, cubeWC[5][3] = 1;
	cubeWC[6][0] = 1, cubeWC[6][1] = -1, cubeWC[6][2] = 1, cubeWC[6][3] = 1;
	cubeWC[7][0] = 1, cubeWC[7][1] = 1, cubeWC[7][2] = 1, cubeWC[7][3] = 1;

    face[0][0] = 0;face[0][1] = 1;face[0][2] = 3; face[0][3] = 2;
    face[1][0] = 3;face[1][1] = 7;face[1][2] = 6;face[1][3] = 2;
    face[2][0] = 7;face[2][1] = 5;face[2][2] = 4;face[2][3] = 6;
    face[3][0] = 4;face[3][1] = 5;face[3][2] = 1;face[3][3] = 0;
    face[4][0] = 5;face[4][1] = 7;face[4][2] = 3;face[4][3] = 1;
    face[5][0] = 6;face[5][1] = 4;face[5][2] = 0;face[5][3] = 2;
    texture = 0;
}

Rect::Rect(GLint height, GLint width, GLint depth, GLint colour){
	norm_mc[0][0] = 0.0,norm_mc[0][1] = 0.0,norm_mc[0][2] = -1.0,
	norm_mc[1][0] = 1.0, norm_mc[1][1] = 0.0, norm_mc[1][2] = 0.0;
	norm_mc[2][0] = 0.0, norm_mc[2][1] = 0.0, norm_mc[2][2] = 1.0;
	norm_mc[3][0] = -1.0, norm_mc[3][1] = 0.0, norm_mc[3][2] = 0.0;
	norm_mc[4][0] = 0.0, norm_mc[4][1] = 1.0, norm_mc[4][2] = 0.0;
	norm_mc[5][0] = 0.0, norm_mc[5][1] = -1.0, norm_mc[5][2] = 0.0;

	norm_wc[0][0] = 0.0, norm_wc[0][1] = 0.0, norm_wc[0][2] = -1.0, norm_wc[0][3] = 0.0;
	norm_wc[1][0] = 1.0, norm_wc[1][1] = 0.0, norm_wc[1][2] = 0.0, norm_wc[1][3] = 0.0;
	norm_wc[2][0] = 0.0, norm_wc[2][1] = 0.0, norm_wc[2][2] = 1.0, norm_wc[2][3] = 0.0;
	norm_wc[3][0] = -1.0, norm_wc[3][1] = 0.0, norm_wc[3][2] = 0.0, norm_wc[3][3] = 0.0;
	norm_wc[4][0] = 0.0, norm_wc[4][1] = 1.0, norm_wc[4][2] = 0.0, norm_wc[4][3] = 0.0;
	norm_wc[5][0] = 0.0, norm_wc[5][1] = -1.0, norm_wc[5][2] = 0.0, norm_wc[5][3] = 0.0;
	GLfloat r,g,b;
	if (colour == 1){
		r = 1.0;
		g=0.0;
		b=0.0;
	}else if(colour == 2){
		r=0.0;
		g=1.0;
		b=0.0;
	}else{
		r=0.0;
		g=0.0;
		b=1.0;
	}
	faceColor[0][0] = r, faceColor[0][1] = g; faceColor[0][2] = b;
	faceColor[1][0] = r, faceColor[1][1] = g; faceColor[1][2] = b;
	faceColor[2][0] = r, faceColor[2][1] = g; faceColor[2][2] = b;
	faceColor[3][0] = r, faceColor[3][1] = g; faceColor[3][2] = b;
	faceColor[4][0] = r, faceColor[4][1] = g; faceColor[4][2] = b;
	faceColor[5][0] = r, faceColor[5][1] = g; faceColor[5][2] = b;
	GLfloat h = height / 2;
	GLfloat w = width / 2;
	GLfloat d = depth / 2;

    vertex[0][0] = -w;vertex[0][1] = -h;vertex[0][2] = -d;
    vertex[1][0] = -w;vertex[1][1] = h; vertex[1][2] = -d;
    vertex[2][0] = w;vertex[2][1] = -h; vertex[2][2] = -d;
    vertex[3][0] = w;vertex[3][1] = h;vertex[3][2] = -d;
    vertex[4][0] = -w;vertex[4][1] = -h;vertex[4][2] = d;
    vertex[5][0] = -w;vertex[5][1] = h; vertex[5][2] = d;
    vertex[6][0] = w;vertex[6][1] = -h;vertex[6][2] = d;
    vertex[7][0] = w;vertex[7][1] = h;vertex[7][2] = d;

	cubeWC[0][0] = -w, cubeWC[0][1] = -h, cubeWC[0][2] = -d, cubeWC[0][3] = 1;
	cubeWC[1][0] = -w, cubeWC[1][1] = h, cubeWC[1][2] = -d, cubeWC[1][3] = 1;
	cubeWC[2][0] = w, cubeWC[2][1] = -h, cubeWC[2][2] = -d, cubeWC[2][3] = 1;
	cubeWC[3][0] = w, cubeWC[3][1] = h, cubeWC[3][2] = -d, cubeWC[3][3] = 1;
	cubeWC[4][0] = -w, cubeWC[4][1] = -h, cubeWC[4][2] = d, cubeWC[4][3] = 1;
	cubeWC[5][0] = -w, cubeWC[5][1] = h, cubeWC[5][2] = d, cubeWC[5][3] = 1;
	cubeWC[6][0] = w, cubeWC[6][1] = -h, cubeWC[6][2] = d, cubeWC[6][3] = 1;
	cubeWC[7][0] = w, cubeWC[7][1] = h, cubeWC[7][2] = d, cubeWC[7][3] = 1;

    face[0][0] = 0;face[0][1] = 1;face[0][2] = 3; face[0][3] = 2;
    face[1][0] = 3;face[1][1] = 7;face[1][2] = 6;face[1][3] = 2;
    face[2][0] = 7;face[2][1] = 5;face[2][2] = 4;face[2][3] = 6;
    face[3][0] = 4;face[3][1] = 5;face[3][2] = 1;face[3][3] = 0;
    face[4][0] = 5;face[4][1] = 7;face[4][2] = 3;face[4][3] = 1;
    face[5][0] = 6;face[5][1] = 4;face[5][2] = 0;face[5][3] = 2;
    texture = 0;
}

/*
 * draw_face
 * a method that draws one of the cube's face
 * Parameters:
 * 	i: the face to draw
 * Returns:
 * 	none
 */
void Rect::draw_face(GLint i)
{
    glBegin(GL_LINE_LOOP);
    glVertex3fv(&vertex[face[i][0]][0]);
    glVertex3fv(&vertex[face[i][1]][0]);
    glVertex3fv(&vertex[face[i][2]][0]);
    glVertex3fv(&vertex[face[i][3]][0]);
    glEnd();
}

/*
 * draw_solid_texture
 * 	a method that draws the rectangle witl the texture
 * 	Parameters:
 * 		i
 * 	Returns:
 * 		none
 */
void Rect::draw_solid_texture(GLint i){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_POLYGON);
	glTexCoord2f( 1.0*i/6, 1);
	glVertex3fv(&vertex[face[i][0]][0]);
	glTexCoord2f( 1.0*i/6, 0);
	glVertex3fv(&vertex[face[i][1]][0]);
	glTexCoord2f( (1.0*i/6) + (1.0*1/6) , 0);
	glVertex3fv(&vertex[face[i][2]][0]);
	glTexCoord2f( (1.0*i/6) + (1.0*1/6), 1);
	glVertex3fv(&vertex[face[i][3]][0]);
    glEnd();
	glDisable(GL_TEXTURE_2D);
}

/*
 * draw_solid_face
 * a method that draws a solid face of the cube
 * Parameters:
 * 	i: the face to draw
 * Returns:
 * 	none
 */
void Rect::draw_solid_face(GLint i){
	glBegin(GL_POLYGON);
    glVertex3fv(&vertex[face[i][0]][0]);
    glVertex3fv(&vertex[face[i][1]][0]);
    glVertex3fv(&vertex[face[i][2]][0]);
    glVertex3fv(&vertex[face[i][3]][0]);
    glEnd();
}

/*
 * draw
 * a method that draw the cube
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Rect::draw()
{
	GLfloat r,g,b;
	glPushMatrix();
    this->ctm_multiply();
    update_rect();
	glScalef(s, s, s);
    for (GLint i = 0; i < 6; i++) {
		//printf("%i is not a back face %f\n", i, backFaceTest[i]);
		//printf("Normal (%f,%f,%f)\n",norm_wc[i][0], norm_wc[i][1],norm_wc[i][2]);
		r = faceColor[i][0];
		g = faceColor[i][1];
		b = faceColor[i][2];
		glColor3f(r, g, b);
		draw_face(i);
    }
    //printf("\n\n");
    glPopMatrix();
}

/*
 * draw
 * a method that draw the solid rectangle
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Rect::draw_solid()
{
	if(texture == 0){
		GLfloat r,g,b;
		glPushMatrix();
	    this->ctm_multiply();
	    update_rect();
		glScalef(s, s, s);
	    for (int i = 0; i < 6; i++) {
			//printf("%i is not a back face %f\n", i, backFaceTest[i]);
			//printf("Normal (%f,%f,%f)\n",norm_wc[i][0], norm_wc[i][1],norm_wc[i][2]);
			r = faceColor[i][0];
			g = faceColor[i][1];
			b = faceColor[i][2];
			glColor3f(r, g, b);
			draw_solid_face(i);
	    }
	    //printf("\n\n");
	    glPopMatrix();
	}else{
		GLfloat r,g,b;
		glPushMatrix();
	    this->ctm_multiply();
	    update_rect();
		glScalef(s, s, s);
	    for (GLint i = 0; i < 6; i++) {
			//printf("%i is not a back face %f\n", i, backFaceTest[i]);
			//printf("Normal (%f,%f,%f)\n",norm_wc[i][0], norm_wc[i][1],norm_wc[i][2]);
			r = faceColor[i][0];
			g = faceColor[i][1];
			b = faceColor[i][2];
			glColor3f(r, g, b);
			draw_solid_texture(i);
	    }
	    //printf("\n\n");
	    glPopMatrix();
	}

}

/*
 * update_Rect
 * a method that will update the Rect after each transformations
 * to compute:
 * 	1.back face
 * 	2. the z-value of each face
 * 	3. the light intensity  of each face cubeShade
 * 	4. Need the faces of the Rect in order of faceIndex
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Rect::update_rect(){
	GLint i;
	//update cube
	//this->MC.print_matrix();
	for(i=0;i<6;i++){
		cubeWC[i][0] = vertex[i][0];
		cubeWC[i][1] = vertex[i][1];
		cubeWC[i][2] = vertex[i][2];
		cubeWC[i][3] = 1.0;
		this->MC.multiply_vector(cubeWC[i]);
	}
	//update cube face normal vectors
	update_normal_vectors();
}

/*
 * print_array
 * a method for testing that prints out an array
 * Parameters:
 * 	a: the pointer to the array
 * 	length: the length of the array
 * Returns:
 * 	none
 */
void Rect::print_array(GLint a[], GLint length){
	GLint position = 0;
	for (position=0;position < length;position++){
		printf("%i:%i  ",position,a[position]);
	}
	printf("\n");
}

/*
 * print_array
 * a method for testing that prints out an array
 * Parameters:
 * 	a: the pointer to the array
 * 	length: the length of the array
 * Returns:
 * 	none
 */
void Rect::print_array(GLfloat a[], GLint length){
	GLint position = 0;
	for (position=0;position < length;position++){
		printf("%i:%f  ",position,a[position]);
	}
	printf("\n");
}

/*
 * update_normal_vectors
 * a method that updates all the face normal vectors in wc
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Rect::update_normal_vectors(){
	GLint face;
	for(face=0;face<6;face++){
		norm_wc[face][0] = norm_mc[face][0];
		norm_wc[face][1] = norm_mc[face][1];
		norm_wc[face][2] = norm_mc[face][2];
		norm_wc[face][3] = 1.0;
		this->MC.multiply_vector(norm_wc[face]);
	}
}

/*
 * set_texture
 * 	a method that sets the texture
 * 	Parameters:
 * 		t: the texture to set
 * 	Returns:
 * 		none
 */
void Rect::set_texture(GLuint t){
	texture = t;
}
