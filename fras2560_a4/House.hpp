/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
*	Assignment: 4
 *	Date: 11/7/2013
  *	File: House.hpp
 */

#ifndef HOUSE_HPP_
#define HOUSE_HPP_

#include <GL/glut.h>

#include "Cube.hpp"
#include "Pyramid.hpp"


class House: public Shape{
protected:
	Pyramid pyramid;
	Cube cube;

public:
	House();
	void draw();
};



#endif /* House_HPP_ */
