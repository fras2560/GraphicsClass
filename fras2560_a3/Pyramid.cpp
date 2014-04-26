/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 3
 *	Date: 10/24/2013
 *	File: Pyramid.hpp
 */

#include "Pyramid.hpp"

Pyramid::Pyramid()
{
    vertex[0][0] = -1;vertex[0][1] = 0;vertex[0][2] = -1;
    vertex[1][0] = 1;vertex[1][1] = 0; vertex[1][2] = -1;
    vertex[2][0] = 1;vertex[2][1] = 0; vertex[2][2] = 1;
    vertex[3][0] = -1;vertex[3][1] = 0;vertex[3][2] = 1;
    vertex[4][0] = 0;vertex[4][1] = 1;vertex[4][2] = 0;

    face[0][0] = 0;face[0][1] = 1;face[0][2] = 4; face[0][3] = -1;
    face[1][0] = 0;face[1][1] = 3;face[1][2] = 4;face[1][3] = -1;
    face[2][0] = 1;face[2][1] = 2;face[2][2] = 4;face[2][3] = -1;
    face[3][0] = 2;face[3][1] = 3;face[3][2] = 4;face[3][3] = -1;
    face[4][0] = 3;face[4][1] = 2;face[4][2] = 1;face[4][3] = 0;
}

/*
 * draw_face
 * 	a function that draws the face of the pyramid
 * 	Parameters:
 * 		i: the face i
 * 	Returns:
 * 		none
 */
void Pyramid::draw_face(int i)
{
    glBegin(GL_LINE_LOOP);
    glVertex3fv(&vertex[face[i][0]][0]);
    glVertex3fv(&vertex[face[i][1]][0]);
    glVertex3fv(&vertex[face[i][2]][0]);
    if(face[i][3] != -1){\
        glVertex3fv(&vertex[face[i][3]][0]);
    }
    glEnd();
}

/*
 * draw
 * 	a function that draws the pyramid
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Pyramid::draw()
{
    glPushMatrix();
    this->ctm_multiply();
	glScalef(s, s, s);
    for (int i = 0; i < 5; i++) {
        draw_face(i);
    }
    glPopMatrix();
}

/*
 * draw_simple
 * 	a function the draws the pyramid without matrix multiply
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Pyramid::draw_simple(){
    for (int i = 0; i < 5; i++) {
        draw_face(i);
    }
}
