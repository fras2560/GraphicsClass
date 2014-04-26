/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Bezier.cpp
 */

#include "Cube.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Bezier.hpp"
#include <math.h>
#include <stdio.h>

using namespace std;
extern GLint winHeight, winWidth;
extern GLint curve_gen , generated, solid, rotated;
#define Pi 3.141592653589793238462643
Bezier::Bezier(){
	control_points = 0;
	R = 45, S = 5, T = 5;
	PTgen = 1, BCgen = 0, BCrotation = 0;
	CR = 1.0, CB = 0.0, CG = 0.0;
}

/*
 * reset
 * 	reset the bezier point curve
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Bezier::reset(){
	control_points = 0;
	R = 45, S = 5, T = 5;
	PTgen = 1, BCgen = 0, BCrotation = 0;
	CR = 1.0, CB = 0.0, CG = 0.0;
}

/*
 * display_controls
 *   a function that displays the controls
 *   Parameters:
 *   	none
 *   Returns:
 *   	none
 */
void Bezier::display_controls(){
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set display-window color to black
	draw2DFrame();
	display_control_points();
}

/*
 * add_control_points
 *  add a control point to the bezier curve
 * Parameters:
 * 	x: the x position
 * 	y: the y position
 * Returns:
 * 	none
 *
 */
void Bezier::add_control_point(GLfloat x, GLfloat y){
	points[control_points].x = x;
	points[control_points].y = y;
	points[control_points].z = 0.0;
	control_points ++;
}

/*
 * add_control_points
 *  add a control point to the bezier curve
 * Parameters:
 * 	x: the x position
 * 	y: the y position
 * Returns:
 * 	none
 *
 */
void Bezier::add_control_point(GLfloat x, GLfloat y, GLfloat z){
	points[control_points].x = x;
	points[control_points].y = y;
	points[control_points].z = z;
	control_points ++;
}

/*
 * display_control_points
 * 	a method to display all the control points in 2d
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Bezier::display_control_points(){
	glPointSize(3.0);
	glColor3f(CR,CG,CB);
	GLint pos;
	for (pos=0;pos<control_points;pos++){
		set_pixel(points[pos].x, points[pos].y);
	}
}

/*
 * draw2DFrame
 * 	a method that draws the x and y axis
 * 	Parameters:
 * 		none
 *	Returns:
 *		none
 */
void Bezier::draw2DFrame(){
	glLineWidth(3);
	glBegin (GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f (-winWidth/4, 0.0);
	glVertex2f (winWidth/4, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f (0.0, -winHeight/4);
	glVertex2f (0.0, winHeight/4);
	glEnd();
	//printf("Drew the frame frame\n ");
}

/*
 * binomial_coefficients
 *	a method that determines the binomial coefficients and stores them in the given array
 * Parameters:
 * 	n: n value
 * 	c: a point to the array to hold the coefficients
 * Returns:
 * 	none
 */
void Bezier::binomial_coefficients(GLint n, GLint *C){
	GLint k, j;
	for(k=0; k<=n; k++){
		/* Compute n!/(k!(n - k)!). */
		C [k] = 1;
		for (j = n; j >= k + 1; j--){
			C [k] *= j;
		}
		for (j = n - k; j >= 2; j--){
			C [k] /= j;
		}
	}
}

/*
 * compute_bezier_point
 * 	a method to computer the bezier point
 * Parameters:
 * 	u: the value of u for blending function
 * 	bezer_point: a pointer to bezier point we are calculating (stores result)
 * 	bezier_tan: stores the bezier tan (stores result)
 * 	C: the binomial coefficients
 * Returns:
 * 	none
 */
void Bezier::compute_bezier_point(GLfloat u, Point *bezier_point, Point *bezier_tan, GLint *C){
	GLint k,n = control_points - 1;
	GLfloat blend_function, factor = 1.0;
	bezier_point->x = bezier_point->y = bezier_point->z = 0.0;
	bezier_tan->x = bezier_tan->y = bezier_tan->z = 0.0;
	/*
	 * Compute the blending function and blend control points
	 */
	for(k=0 ; k < control_points ; k++){
		blend_function = C[k] * pow(u, k) * pow(1-u, n-k);
		bezier_point -> x += points[k].x * blend_function;
		bezier_point -> y += points[k].y * blend_function;
		bezier_point -> z += points[k].z * blend_function;
		if(u < 0.001){
			bezier_tan->x = points[1].x - points[0].x;
			bezier_tan->y = points[1].y - points[0].y;
			bezier_tan->z = points[1].z - points[0].z;
		}else if((1-u) < 0.001){
			bezier_tan->x = points[n+1].x - points[n].x;
			bezier_tan->y = points[n+1].y - points[n].y;
			bezier_tan->z = points[n+1].z - points[n].z;
		}else{
			factor = (k/u) - (n-k) / (1-u);
			bezier_tan->x += points[k].x * blend_function * factor;
			bezier_tan->y += points[k].y * blend_function * factor;
			bezier_tan->z += points[k].z * blend_function * factor;
		}
	}
}

/*
 * set_pixel
 * 	a method that display a pixel at (x,y)
 * 	Parameters:
 * 		x: the x position
 * 		y: the y position
 * 	Returns:
 * 		none
 */
void Bezier::set_pixel(GLfloat x, GLfloat y){
	glBegin (GL_POINTS);
	glVertex2f (x, y);
	glEnd ( );
}

/*
 * draw
 * 	a method to draw the bezier curve
 * 	Parameters:
 * 		bezier_curve_points: the number of bezier curve points
 * 	Returns:
 * 		none
 */
void Bezier::draw(GLint bezier_curve_points){
	Point bezier_curve_point, bezier_curve_tangent;
	GLfloat u;
	GLint *C;
	GLint k;
	C = new GLint[control_points];
	binomial_coefficients(control_points - 1, C);
	glColor3f(CR,CG,CB);
	for(k=0; k<=bezier_curve_points; k++){
		u = GLfloat (k) / GLfloat (bezier_curve_points);
		compute_bezier_point(u, &bezier_curve_point, &bezier_curve_tangent, C);
		set_pixel(bezier_curve_point.x, bezier_curve_point.y);
	}
	delete []C;
}

/*
 * draw
 * a method to display the control points
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Bezier::draw(){
	//printf("S:%i, T:%i R:%i\n", S,T,R);
	glPushMatrix();
	this->ctm_multiply();
	glScalef(s * 0.01, s * 0.01, s * 0.01);

	if(curve_gen == 1){
		display_controls();
		if(generated == 1){
			draw(1000);
		}
	}
	if(rotated == 1){
		rotate_bezier(1000);
		if(solid == 0){
			draw_wire_rbc();
		}else{
			draw_solid_rbc();
		}
	}
	glPopMatrix();
}

/*
 * setPixel
 * 	a function that sets the pixel in x,y
 * 	Parameters:
 * 		x: the x coordinate
 * 		y: the y coordinate
 * 	Returns:
 * 		none
 */
void Bezier::setPixel (GLfloat x, GLfloat y)
{
	glBegin (GL_POINTS);
	glVertex2f (x, y);
	glEnd ( );
}

/*
 * rotate_bezier
 * 	a method to rotate the bezier curve
 * 	it calculates all the mesh points and curves
 * 	Parameters:
 * 		bezier_curve_points: the number of bezier curve points
 * 	Returns:
 * 		none
 */
void Bezier::rotate_bezier(GLint bezier_curve_points){
	Point bezier_curve_point, bezier_curve_tangent;
	GLfloat u, temp, x, y;
	GLint *C;
	GLint k,i;
	C = new GLint[control_points];
	binomial_coefficients( control_points-1, C);
	for(k=0; k<= T; k++){
		u = GLfloat (k) / GLfloat (T);
		compute_bezier_point(u, &bezier_curve_point, &bezier_curve_tangent, C);
		for(i=0;i<= int(R/S);i++){
			//get the mesh points
			mesh_points[i][k].x = bezier_curve_point.x;
			mesh_points[i][k].y = bezier_curve_point.y*cos((Pi/180)*S*i);
			mesh_points[i][k].z = bezier_curve_point.y*sin((Pi/180)*S*i);
			//get the mesh normals
			// compute the normal at the each mesh point
			x = bezier_curve_tangent.x;
			y = bezier_curve_tangent.y;

			temp = x;
			x = -y;
			y = temp;

			//printf("Mesh Point %i, %i = (%f,%f,%f)\n", i,k ,mesh_points[i][k].x ,mesh_points[i][k].y,mesh_points[i][k].z );
			mesh_normals[i][k].x = x;
			mesh_normals[i][k].y = y*cos((Pi/180)*S*i);
			mesh_normals[i][k].z = y*sin((Pi/180)*S*i);
		}
	}
	delete []C;
}

/*
 * draw_wire_rbc
 * 	a method that draws the wire bezier curve
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Bezier::draw_wire_rbc(){
	int i, j;
	glColor3f(CR, CG, CB);
	for (i=0; i<int(R/S); i++){
		for(j=0;j<T;j++){
			glBegin(GL_LINE_LOOP);
			glVertex3f(mesh_points[i][j].x, mesh_points[i][j].y, mesh_points[i][j].z);
			glVertex3f(mesh_points[i+1][j].x, mesh_points[i+1][j].y, mesh_points[i+1][j].z);
			glVertex3f(mesh_points[i+1][j+1].x, mesh_points[i+1][j+1].y, mesh_points[i+1][j+1].z);
			glVertex3f(mesh_points[i][j+1].x, mesh_points[i][j+1].y, mesh_points[i][j+1].z);
			printf("(%i,%i), (%f,%f,%f)\n",i,j+1,mesh_points[i][j+1].x, mesh_points[i][j+1].y,mesh_points[i][j+1].z);
			printf("(%i,%i), (%f,%f,%f)\n",i+1,j+1,mesh_points[i+1][j+1].x, mesh_points[i+1][j+1].y,mesh_points[i+1][j+1].z);
			glEnd ( );
		}
	}
	if( R == 360){
		i = (GLint)(R/S - 1);
		for (j = 0; j< T; j++)
		{
		glBegin (GL_LINE_LOOP);
		glVertex3f(mesh_points[i][j].x, mesh_points[i][j].y, mesh_points[i][j].z);
		glVertex3f(mesh_points[0][j].x, mesh_points[0][j].y, mesh_points[0][j].z);
		glVertex3f(mesh_points[0][j+1].x, mesh_points[0][j+1].y, mesh_points[0][j+1].z);
		glVertex3f(mesh_points[i][j+1].x, mesh_points[i][j+1].y, mesh_points[i][j+1].z);
		glEnd();
		}
	}
}

/*
 * draw_wire_rbc
 * 	a method that draws the solid bezier curve
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Bezier::draw_solid_rbc(){
	GLint i,j;
	GLint loop = (R/S);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
	for(i=0;i<loop;i++){
		for(j=0;j<T;j++){
			glBegin (GL_POLYGON);
			glColor3f(CR, CG, CB);
			glNormal3f(mesh_normals[i][j].x, mesh_normals[i][j].y, mesh_normals[i][j].z);
			glVertex3f(mesh_points[i][j].x, mesh_points[i][j].y,mesh_points[i][j].z);
			glVertex3f(mesh_points[i+1][j].x, mesh_points[i+1][j].y,mesh_points[i+1][j].z);
			glVertex3f(mesh_points[i+1][j+1].x, mesh_points[i+1][j+1].y,mesh_points[i+1][j+1].z);
			glVertex3f(mesh_points[i][j+1].x, mesh_points[i][j+1].y,mesh_points[i][j+1].z);
			glEnd();
		}
		for (j = 0; j< T; j++){
			glBegin (GL_POLYGON);
			glColor3f(CR, CG, CB);
			glNormal3f(-mesh_normals[i][j].x, -mesh_normals[i][j].y, -mesh_normals[i][j].z);
			glVertex3f(mesh_points[i][j].x, mesh_points[i][j].y,mesh_points[i][j].z);
			glVertex3f(mesh_points[i][j+1].x, mesh_points[i][j+1].y,mesh_points[i][j+1].z);
			glVertex3f(mesh_points[i+1][j+1].x, mesh_points[i+1][j+1].y,mesh_points[i+1][j+1].z);
			glVertex3f(mesh_points[i+1][j].x, mesh_points[i+1][j].y,mesh_points[i+1][j].z);
			glEnd();
		}
	}
	if (R == 360)
	{
		i = (R/S-1) ;
		for (j = 0; j< T; j++)
		{
			glColor3f(CR, CG, CB);
			glNormal3f(mesh_normals[i][j].x, mesh_normals[i][j].y, mesh_normals[i][j].z);
			glBegin (GL_POLYGON);
			glVertex3f(mesh_points[i][j].x, mesh_points[i][j].y,mesh_points[i][j].z);
			glVertex3f(mesh_points[0][j].x, mesh_points[0][j].y,mesh_points[0][j].z);
			glVertex3f(mesh_points[0][j+1].x, mesh_points[0][j+1].y,mesh_points[0][j+1].z);
			glVertex3f(mesh_points[i][j+1].x, mesh_points[i][j+1].y,mesh_points[i][j+1].z);
			glEnd();
			glColor3f(CR, CG, CB);
			glNormal3f(-mesh_normals[i][j].x, -mesh_normals[i][j].y, -mesh_normals[i][j].z);
			glBegin (GL_POLYGON);
			glVertex3f(mesh_points[i][j].x, mesh_points[i][j].y,mesh_points[i][j].z);
			glVertex3f(mesh_points[0][j].x, mesh_points[0][j].y,mesh_points[0][j].z);
			glVertex3f(mesh_points[0][j+1].x, mesh_points[0][j+1].y,mesh_points[0][j+1].z);
			glVertex3f(mesh_points[i][j+1].x, mesh_points[i][j+1].y,mesh_points[i][j+1].z);
			glEnd();
		}
	}
}
