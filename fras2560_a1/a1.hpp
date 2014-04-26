/*
 * a1.hpp
 *
 *  Created on: 2013 10 3
 *      Author: Student
 */

#ifndef A1_HPP_
#define A1_HPP_
#include <GL/glut.h>

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//function prototypes
void bringToFront(GLint);
GLboolean checkInRange(GLint, GLint, GLint, GLint, GLint, GLint);
void circleFillPoints(GLint, GLint, GLint, GLint);
void circlePlotPoints(GLint, GLint, GLint, GLint);
void colorMenu(GLint);
int convertFromString(std::string);
void deleteObject(GLint);
void deselectObject();
void drawCircle(GLint, GLint, GLint, GLint, GLfloat, GLfloat, GLfloat);
void drawLine(GLint, GLint, GLint, GLint, GLint, GLfloat, GLfloat, GLfloat);
void drawList();
void drawMenu(GLint);
void drawRectangle(GLint, GLint, GLint, GLint, GLint, GLfloat, GLfloat, GLfloat);
void editMenu(GLint);
void errorHandler();
void fileMenu(GLint);
void fillCircle(GLint, GLint, GLint, GLint, GLfloat, GLfloat, GLfloat);
void init();
GLint maxPoint(GLint, GLint);
void menu(GLint);
GLint minPoint(GLint, GLint);
void motion(GLint, GLint);
void mouseDraw(GLint, GLint, GLint, GLint);
int readSVG();
void renderBitmapString(GLfloat, GLfloat, void *,const char *);
int saveBitmap(const char*, GLint, GLint, GLint, GLint);
int saveSVG();
void selectObject(GLint, GLint);
void sendToBack(GLint);
int setCircle(std::string);
int setLine(std::string);
void setObject(GLint, GLint, GLint);
int setRectangle(std::string);
void styleMenu(GLint);
void winReshapeFcn(GLint, GLint);
#endif /* A1_HPP_ */
