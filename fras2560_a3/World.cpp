/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 3
 *	Date: 10/24/2013
 *	File: World.cpp
 *	Description: implementation of World class
 */
#include "World.hpp"
#include "Pyramid.hpp"
#include "House.hpp"
#include "Planet.hpp"
extern GLint solar;
World::World() {
	list[0] = new Cube();
	list[1] = new Planet(1); //sun
	list[2] = new Planet(2);//earth


}

World::~World(){
    delete list[0];
    delete list[1];
    delete list [2];
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
	if (solar == 0){
		list[0]->draw();
	}else{
		list[1]->draw();
		list[2]->draw();
	}

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
}

