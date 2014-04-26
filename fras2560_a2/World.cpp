/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 2
 *	Date: 10/10/2013
 *	File: World.cpp
 *	Description: implementation of World class
 */
#include "World.hpp"
#include "Pyramid.hpp"
#include "House.hpp"

World::World() {
	list[0] = new Cube();
	list[1] = new Pyramid();
	list[2] = new House();

}

World::~World(){
    delete list[0];
    delete list[1];
    delete list[2];
}

/*
 * draw_world
 * 		a method that draws every object in the world
 * 	Parameters:
 * 		none
 * 	Returns:
 * 		none
 */
void World::draw_world() {
	list[0]->draw();
	list[1]->draw();
	list[2]->draw();
}

/*
 * reset_world
 * a method that resets the objects to original position
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void World::reset_world(){
	list[0]->reset();
	list[1]->reset();
	list[2]->reset();
}

