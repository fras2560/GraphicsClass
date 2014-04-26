/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 2
 *	Date: 10/10/2013
 *	File: Point.cpp
 */
#include "Point.hpp"
#include <math.h>
#include <stdio.h>
using namespace std;
Point::Point(){
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

/*
 * Normalize
 * 	a method to normalize the point
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void Point::Normalize(){
	GLdouble length;
	length = sqrt(x * x + y * y + z * z);
	if (length != 0) {
		x /= length;
		y /= length;
		z /= length;
	} else {
		x = 0;
		y = 0;
		z = 0;
	}
}

/*
 * CalcNormal
 * 	a method the calculates the normal of the three points
 * 	Parameters:
 * 		p1: the first point
 * 		p2: the second point
 * 	Returns:
 * 		n: the normal point
 */
Point Point::CalcNormal(Point p1, Point p2){
	Point n,pa,pb;

	pa.x = p1.x - this->x;
	pa.y = p1.y - this->y;
	pa.z = p1.z - this->z;
	pb.x = p2.x - this->x;
	pb.y = p2.y - this->y;
	pb.z = p2.z - this->z;
	pa.Normalize();
	pb.Normalize();

	n.x = pa.y * pb.z - pa.z * pb.y;
	n.y = pa.z * pb.x - pa.x * pb.z;
	n.z = pa.x * pb.y - pa.y * pb.x;
	n.Normalize();

	return(n);
}

/*
 * CrossProduct
 * a method to calculate the normal of two points
 * Parameters:
 * 	p1: the first point
 * 	p2: the second point
 * Returns:
 * 	none
 */
void Point::CrossProduct(Point p1, Point p2){
	this->x = p1.y*p2.z - p1.z*p2.y;
	this->y = p1.z*p2.x - p1.x*p2.z;
	this->z = p1.x*p2.y - p1.y*p2.x;
}

/*
 * printPoint
 * 	a function the neatly print out the point
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Point::printPoint(){
	printf("(x:%f, y:%f, z:%f)\n",x,y,z);
}
