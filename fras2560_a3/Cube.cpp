/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
*	Assignment: 3
 *	Date: 10/24/2013
  *	File: Cube.hpp
 */

#include "Cube.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include <math.h>
#include <stdio.h>
using namespace std;
extern Camera myCam;
extern Light myLight;
extern GLint shading;
Cube::Cube()
{  
	cube_face_norm_mc[0][0] = 0.0,cube_face_norm_mc[0][1] = 0.0,cube_face_norm_mc[0][2] = -1.0,
	cube_face_norm_mc[1][0] = 1.0, cube_face_norm_mc[1][1] = 0.0, cube_face_norm_mc[1][2] = 0.0;
	cube_face_norm_mc[2][0] = 0.0, cube_face_norm_mc[2][1] = 0.0, cube_face_norm_mc[2][2] = 1.0;
	cube_face_norm_mc[3][0] = -1.0, cube_face_norm_mc[3][1] = 0.0, cube_face_norm_mc[3][2] = 0.0;
	cube_face_norm_mc[4][0] = 0.0, cube_face_norm_mc[4][1] = 1.0, cube_face_norm_mc[4][2] = 0.0;
	cube_face_norm_mc[5][0] = 0.0, cube_face_norm_mc[5][1] = -1.0, cube_face_norm_mc[5][2] = 0.0;

	cube_face_norm_wc[0][0] = 0.0, cube_face_norm_wc[0][1] = 0.0, cube_face_norm_wc[0][2] = -1.0, cube_face_norm_wc[0][3] = 0.0;
	cube_face_norm_wc[1][0] = 1.0, cube_face_norm_wc[1][1] = 0.0, cube_face_norm_wc[1][2] = 0.0, cube_face_norm_wc[1][3] = 0.0;
	cube_face_norm_wc[2][0] = 0.0, cube_face_norm_wc[2][1] = 0.0, cube_face_norm_wc[2][2] = 1.0, cube_face_norm_wc[2][3] = 0.0;
	cube_face_norm_wc[3][0] = -1.0, cube_face_norm_wc[3][1] = 0.0, cube_face_norm_wc[3][2] = 0.0, cube_face_norm_wc[3][3] = 0.0;
	cube_face_norm_wc[4][0] = 0.0, cube_face_norm_wc[4][1] = 1.0, cube_face_norm_wc[4][2] = 0.0, cube_face_norm_wc[4][3] = 0.0;
	cube_face_norm_wc[5][0] = 0.0, cube_face_norm_wc[5][1] = -1.0, cube_face_norm_wc[5][2] = 0.0, cube_face_norm_wc[5][3] = 0.0;

	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0; faceColor[0][2] = 0.0;
	faceColor[1][0] = 0.0, faceColor[1][1] = 1.0; faceColor[1][2] = 0.0;
	faceColor[2][0] = 0.0, faceColor[2][1] = 0.0; faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0, faceColor[3][1] = 1.0; faceColor[3][2] = 0.0;
	faceColor[4][0] = 1.0, faceColor[4][1] = 0.0; faceColor[4][2] = 1.0;
	faceColor[5][0] = 0.0, faceColor[5][1] = 1.0; faceColor[5][2] = 1.0;

	cubeShade[0] = 1, cubeShade[1] = 1, cubeShade[2] = 1, cubeShade[3] = 1;
	cubeShade[4] = 1, cubeShade[5] = 1;

	cube_face_center_mc [0][0] = 0.0, cube_face_center_mc [0][1] = 0.0, cube_face_center_mc [0][2] = -1.0;
	cube_face_center_mc [1][0] = 1.0, cube_face_center_mc [1][1] = 0.0, cube_face_center_mc [1][2] = 0.0;
	cube_face_center_mc [2][0] = 0.0, cube_face_center_mc [2][1] = 0.0, cube_face_center_mc [2][2] = 1.0;
	cube_face_center_mc [3][0] = -1.0, cube_face_center_mc [3][1] = 0.0, cube_face_center_mc [3][2] = 0.0;
	cube_face_center_mc [4][0] = 0.0, cube_face_center_mc [4][1] = 1.0, cube_face_center_mc [4][2] = 0.0;
	cube_face_center_mc [5][0] = 0.0, cube_face_center_mc [5][1] = -1.0, cube_face_center_mc [5][2] = 0.0;

	cube_face_center_wc[0][0] = 0.0, cube_face_center_wc[0][1] = 0.0, cube_face_center_wc[0][2] = -1.0,cube_face_center_wc[0][3] = 1.0;
	cube_face_center_wc[1][0] = 1.0, cube_face_center_wc[1][1] = 0.0, cube_face_center_wc[1][2] = 0.0,cube_face_center_wc[1][3] = 1.0;
	cube_face_center_wc[2][0] = 0.0, cube_face_center_wc[2][1] = 0.0, cube_face_center_wc[2][2] = 1.0,cube_face_center_wc[2][3] = 1.0;
	cube_face_center_wc[3][0] = -1.0, cube_face_center_wc[3][1] = 0.0, cube_face_center_wc[3][2] = 0.0,cube_face_center_wc[3][3] = 1.0;
	cube_face_center_wc[4][0] = 0.0, cube_face_center_wc[4][1] = 1.0, cube_face_center_wc[4][2] = 0.0,cube_face_center_wc[4][3] = 1.0;
	cube_face_center_wc[5][0] = 0.0, cube_face_center_wc[5][1] = -1.0, cube_face_center_wc[5][2] = 0.0,cube_face_center_wc[5][3] = 1.0;

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
}

/*
 * draw_face
 * a method that draws one of the cube's face
 * Parameters:
 * 	i: the face to draw
 * Returns:
 * 	none
 */
void Cube::draw_face(GLint i)
{
    glBegin(GL_LINE_LOOP);
    glVertex3fv(&vertex[face[i][0]][0]);
    glVertex3fv(&vertex[face[i][1]][0]);
    glVertex3fv(&vertex[face[i][2]][0]);
    glVertex3fv(&vertex[face[i][3]][0]);
    glEnd();
}

/*
 * draw_solid_face
 * a method that draws a solid face of the cube
 * Parameters:
 * 	i: the face to draw
 * Returns:
 * 	none
 */
void Cube::draw_solid_face(GLint i){
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
void Cube::draw()
{
	GLfloat r,g,b;
	glPushMatrix();
    this->ctm_multiply();
    update_cube();
	glScalef(s, s, s);
    for (int i = 0; i < 6; i++) {
    	if(backFaceTest[i] < 0){
    		printf("%i is not a back face %f\n", i, backFaceTest[i]);
    		printf("Normal (%f,%f,%f)\n",cube_face_norm_wc[i][0], cube_face_norm_wc[i][1],cube_face_norm_wc[i][2]);
    		if (shading == 1){
                r = faceColor[i][0]*cubeShade[i];
                g = faceColor[i][1]*cubeShade[i];
                b = faceColor[i][2]*cubeShade[i];
    		}else{
    			r = faceColor[i][0];
    			g = faceColor[i][1];
    			b = faceColor[i][2];
    		}
    		glColor3f(r, g, b);
            draw_solid_face(i);
    	}else{
    		printf("%i is a back face %f\n", i, backFaceTest[i]);
    		printf("Normal (%f,%f,%f)\n",cube_face_norm_wc[i][0], cube_face_norm_wc[i][1],cube_face_norm_wc[i][2]);
    	}
    }
    printf("\n\n");
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

/*
 * update_cube
 * a method that will update the cube after each transformations
 * to compute:
 * 	1.back face
 * 	2. the z-value of each face
 * 	3. the light intensity  of each face cubeShade
 * 	4. Need the faces of the cube in order of faceIndex
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Cube::update_cube(){
	GLint i;
	//update cube
	this->MC.print_matrix();
	for(i=0;i<6;i++){
		cubeWC[i][0] = vertex[i][0];
		cubeWC[i][1] = vertex[i][1];
		cubeWC[i][2] = vertex[i][2];
		cubeWC[i][3] = 1.0;
		this->MC.multiply_vector(cubeWC[i]);
	}

	//update cube face normal vectors
	update_normal_vectors();
	update_cube_face_center();
	// update backFaceTest
	for (i = 0;i<6;i++){
		update_back_face(i);
	}
	//update shading for each face and facenormal * (ref-eye)
	for (i = 0; i<6;i++){
		update_shade(i);
	}
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
void Cube::print_array(GLint a[], GLint length){
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
void Cube::print_array(GLfloat a[], GLint length){
	GLint position = 0;
	for (position=0;position < length;position++){
		printf("%f:%f  ",position,a[position]);
	}
	printf("\n");
}


/*
 * calculate_z
 * a method to calculate the z value of the given face
 * Parameters:
 * 	the face to calculate the z value
 * Returns:
 * 	none
 */
GLfloat Cube::calculate_z(GLint pos){
	GLfloat z_value , x,y,z, xeye, yeye, zeye;
	xeye = myCam.Rotate.x - myCam.Eye.x;
	yeye = myCam.Rotate.y - myCam.Eye.y;
	zeye = myCam.Rotate.z - myCam.Eye.z;
	x = (zeye)*(cube_face_center_wc[pos][0] - myCam.Eye.x);
	y = (yeye)*(cube_face_center_wc[pos][1] - myCam.Eye.y);
	z = (zeye)*(cube_face_center_wc[pos][2] - myCam.Eye.z);
	z_value = (x+y+z) / sqrt((xeye*xeye)+(yeye*yeye)+(zeye*zeye));
	return z_value;
}

/*
 * check_if_back_face
 * a method check if the face is a back face
 * Parameters:
 * 	face: the face to check (index)
 * Returns:
 * 	true if back face and false otherwise
 */
void Cube::update_back_face(GLint face){
	GLfloat x,y,z, result;
	//PeyePref
	x = myCam.Rotate.x- myCam.Eye.x;
	y = myCam.Rotate.y - myCam.Eye.y;
	z = myCam.Rotate.z - myCam.Eye.z;
	result = x * cube_face_norm_wc[face][0] + y * cube_face_norm_wc[face][1] + z * cube_face_norm_wc[face][2];
	backFaceTest[face] = result;
}

/*
 * calculate_normal
 * calculate the normal for the face
 * puts the result into normal
 * Parameters:
 * 	face: the index of the face
 * 	normal: the pointer to the noraml
 * Returns:
 * 	none
 */
void Cube::calculate_normal(GLint facenum){
	GLfloat nx,ny,nz, length;
	GLint p0,p1,p2;
	p0 = face[facenum][0];
	p1 = face[facenum][1];
	p2 = face[facenum][2];

	nx = (cubeWC[p1][1] -cubeWC[p0][1]) * (cubeWC[p2][2] - cubeWC[p1][2])  - (cubeWC[p2][1] - cubeWC[p1][1]) * (cubeWC[p1][2] - cubeWC[p0][2]);
	ny = (cubeWC[p1][2] -cubeWC[p0][2]) * (cubeWC[p2][0] - cubeWC[p1][0])  - (cubeWC[p2][2] - cubeWC[p1][2]) * (cubeWC[p1][0] - cubeWC[p0][0]);
	nz = (cubeWC[p1][0] -cubeWC[p0][0]) * (cubeWC[p2][1] - cubeWC[p1][1])  - (cubeWC[p2][0] - cubeWC[p1][0]) * (cubeWC[p1][1] - cubeWC[p0][1]);
	length = sqrt(nx * nx + ny * ny + nz * nz);
	//normalize
	if(length != 0){
		nx /= length;
		ny /= length;
		nz /= length;
	}else{
		nx = 0;
		ny = 0;
		nz = 0;
	}
	cube_face_norm_wc[facenum][0] = nx;
	cube_face_norm_wc[facenum][1] = ny;
	cube_face_norm_wc[facenum][2] = nz;

}

/*
 * update_normal_vectors
 * a method that updates all the face normal vectors in wc
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Cube::update_normal_vectors(){
	GLint face;
	for(face=0;face<6;face++){
		cube_face_norm_wc[face][0] = cube_face_norm_mc[face][0];
		cube_face_norm_wc[face][1] = cube_face_norm_mc[face][1];
		cube_face_norm_wc[face][2] = cube_face_norm_mc[face][2];
		cube_face_norm_wc[face][3] = 1.0;
		this->MC.multiply_vector(cube_face_norm_wc[face]);
		GLdouble length;
		//calculate_normal(face,cube_face_norm_wc[face]);
	}
}

/*
 * update_cube_face_center
 * a method that updates all the face center values
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Cube::update_cube_face_center(){
	GLint face;
	for(face=0;face<6;face++){
		cube_face_center_wc[face][0] = cube_face_center_mc[face][0];
		cube_face_center_wc[face][1] = cube_face_center_mc[face][1];
		cube_face_center_wc[face][2] = cube_face_center_mc[face][2];
		cube_face_center_wc[face][3] = 1.0;
		this->MC.multiply_vector(cube_face_center_wc[face]);
	}
}

/*
 * update_shade
 * updates the shade of the face
 * Parameters:
 * 	face: the face index
 * Returns:
 * 	none
 */
void Cube::update_shade(GLint face){
	GLfloat sx,sy,sz, norm, ns;
	sx = myLight.Position[0] - cube_face_center_wc[face][0];
	sy = myLight.Position[1] - cube_face_center_wc[face][1];
	sz = myLight.Position[2] - cube_face_center_wc[face][2];
	norm = sqrt(sx * sx + sy * sy+ sz * sz);
	ns = (cube_face_norm_wc[face][0] * sx + cube_face_norm_wc[face][1] * sy + cube_face_norm_wc[face][2] * sz)/norm;
	if(ns>0){
		if((myLight.B * myLight.Ka + myLight.P * myLight.Ka * ns) <=  1){
			cubeShade[face] = myLight.B * myLight.Ka + myLight.P * myLight.Kd * ns;
		}else{
			cubeShade[face] = 1.0;
		}
	}else{
		cubeShade[face] = myLight.B * myLight.Ka;
	}
}
