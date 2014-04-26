/*
 *	Name: Dallas Fraser
 *	ID: 110242560
 *	Class: CP411
 *	Assignment: 4
 *	Date: 11/7/2013
 *	File: Image.hpp
 *	Description: implementation of Image class
 */
#ifndef CIMAGE_HPP
#define CIMAGE_HPP
#include <windows.h>
#include <mmsystem.h>

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

class Image{
	public:
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
	Image();
	~Image();
	GLint load_image(char *);

};

#endif
