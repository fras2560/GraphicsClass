/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 3
 *	Date: 10/24/2013
 *	File: World.hpp
 *	Description: implementation of World class
 */

#ifndef CWORLD_HPP
#define CWORLD_HPP

#include "Cube.hpp"
//#include "Shape.hpp"
#include <iostream>
#include <list>
#include <vector>


class World {

public:

	Shape* list[3];

	World();

	~World();

	void draw_world(); // draw all objects in the world
	void reset_world(); //resets all objects
};

#endif
