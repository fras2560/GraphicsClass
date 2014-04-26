/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: World.cpp
 *	Description: implementation of World class
 */
#include "World.hpp"
#include "Pyramid.hpp"
#include "House.hpp"
#include "Planet.hpp"
#include "Bezier.hpp"
#include <stdio.h>

extern GLint selected;
World::World() {
	list[1] = new Cube();
	objects = NULL;
}

World::~World(){
    //delete list[0];
    //delete list[1];
    node *current = objects;
    node *next;
    for(;current!=NULL;current=next){
    	next = current->next;
    	free(current);
    }
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
		list[1]->draw();
		node *current = objects;
		for(; current!=NULL; current=current->next){
			current->object->draw();
		}
		printf("Done Drawing\n");
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
	//list[1]->reset();
	node *current = objects;
	for(; current!=NULL; current=current->next){
		current->object->reset();
	}
}

/*
 * add_object
 * 	a method to add an object
 * Parameters:
 * 	key: the key to identifying the object
 * 	object: the object to add
 * Returns:
 * 	none
 */
void World::add_object(GLint key , Shape* object){
	node *current =  objects;
	node *creation = (node*)malloc(sizeof(node));
	creation->object = object;
	creation->key = key;
	creation->next = NULL;
	if (objects == NULL){
		objects = creation;
	}else{
		for(; current->next!=NULL; current=current->next){
		}
		current->next = creation;
	}
}

/*
 * delete_object
 * 	a method to delete an object from the world
 * 	Parameters:
 * 		key: the key to identify the object
 * 	Returns:
 * 		none
 */
void World::delete_object(GLint key){
	node *current = objects;
	node *previous = NULL;
	for(; current!=NULL; current=current->next){
		previous = current;
	}
	if (previous == NULL){
		objects = current->next;
	}else{
		previous->next = current->next;
	}
	free(current);
}
