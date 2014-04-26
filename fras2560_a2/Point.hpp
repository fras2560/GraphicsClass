/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 2
 *	Date: 10/10/2013
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
