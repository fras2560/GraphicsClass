/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 2
 *	Date: 10/10/2013
 *	File: Cube.hpp
 */

#include "Cube.hpp"

Cube::Cube()
{  
    vertex[0][0] = -1;vertex[0][1] = -1;vertex[0][2] = -1;
    vertex[1][0] = -1;vertex[1][1] = 1; vertex[1][2] = -1;
    vertex[2][0] = 1;vertex[2][1] = -1; vertex[2][2] = -1; 
    vertex[3][0] = 1;vertex[3][1] = 1;vertex[3][2] = -1;
    vertex[4][0] = -1;vertex[4][1] = -1;vertex[4][2] = 1;
    vertex[5][0] = -1;vertex[5][1] = 1; vertex[5][2] = 1; 
    vertex[6][0] = 1;vertex[6][1] = -1;vertex[6][2] = 1;
    vertex[7][0] = 1;vertex[7][1] = 1;vertex[7][2] = 1;
    
    face[0][0] = 0;face[0][1] = 1;face[0][2] = 3; face[0][3] = 2;
    face[1][0] = 3;face[1][1] = 7;face[1][2] = 6;face[1][3] = 2;
    face[2][0] = 7;face[2][1] = 5;face[2][2] = 4;face[2][3] = 6;
    face[3][0] = 4;face[3][1] = 5;face[3][2] = 1;face[3][3] = 0;
    face[4][0] = 5;face[4][1] = 7;face[4][2] = 3;face[4][3] = 1;
    face[5][0] = 6;face[5][1] = 4;face[5][2] = 0;face[5][3] = 2;
}

/*
 * draw_face
 * a method that draws one of the cube's face
 * Parameters:
 * 	i: the face to draw
 * Returns:
 * 	none
 */
void Cube::draw_face(int i)
{
    glBegin(GL_LINE_LOOP);
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
void Cube::draw()
{
    glPushMatrix();
    this->ctm_multiply();
	glScalef(s, s, s);
    for (int i = 0; i < 6; i++) {
        draw_face(i);
    }
    glPopMatrix();
}

/*
 * draw
 * a method that draw the cube but does not ctm_multiply
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Cube::draw_simple()
{
    for (int i = 0; i < 6; i++) {
        draw_face(i);
    }
}
