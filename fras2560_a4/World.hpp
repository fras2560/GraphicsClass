/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
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
#include "Bezier.hpp"

struct node{
	Shape* object;
	GLint key;
	node *next;
};
class World {

public:
	Shape* list[4];
	Bezier curve;
	node *objects;
	World();

	~World();

	void draw_world(); // draw all objects in the world
	void reset_world(); //resets all objects
	Bezier get_curve();
	void add_object(GLint, Shape*);
	void delete_object(GLint);
};

#endif
