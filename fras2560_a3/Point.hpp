/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 3
 *	Date: 10/24/2013
 *	File: Point.hpp
 */
#ifndef CPOINT_H
#define CPOINT_H

#include <GL/glut.h>

class Point {
 public:
	GLfloat x,y,z; //the coordinates
	Point();
	void Normalize();
	Point CalcNormal(Point, Point);
	void CrossProduct(Point, Point);
	void printPoint();
};

#endif
