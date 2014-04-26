/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/15/2013
 *	File: Earth.hpp
 */


#include "Planet.hpp"
#include "Shape.hpp"
#include <GL/glut.h>
#ifndef EARTH_HPP_
#define EARTH_HPP_

class Earth: public Shape{
	public:
		Planet earth;
		Planet moon;
		void draw();
		Earth();
		~Earth();
};
#endif /* EARTH_HPP_ */
