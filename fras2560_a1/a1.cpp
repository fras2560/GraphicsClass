/*
 * Name: Dallas Fraser
 * Student Id: 110242560
 * Date:09/26/2013
 * Class: CP411
 * File: a1.cpp
 * References: a1.hpp
 *
 */

//openGL Header
#include "a1.hpp"
using namespace std;

//global variables
GLint windowId;
GLsizei winWidth = 640, winHeight = 480;
GLint tool = 0, type = 1, style = 1, selected = 0, selection = 0;
GLint move = 0, xbegin, ybegin, ptCtr = 0, numObj =0;
GLint drawing = 0;
GLfloat red = 1.0, green = 0.0, blue = 0.0;

//global structures
class modelObject {
public:
	GLint x1, y1, x2, y2, type, style;
	GLfloat red, green, blue;
} list[100];

/*
 * brintToFront
 * 		a function that takes an objects position and brings it to the front
 * Parameters:
 * 		object: the objects position in the array
 *
 */
void bringToFront(GLint object){
	GLint position;
	GLint x1, x2, y1, y2, type, style;
	GLfloat red, blue, green;
	//save the values
	x1 = list[object].x1;
	x2 = list[object].x2;
	y1 = list[object].y1;
	y2 = list[object].y2;
	type = list[object].type;
	style = list[object].style;
	red = list[object].red;
	blue = list[object].blue;
	green = list[object].green;
	//swap all objects in front of object
	for(position = object;position < numObj; position++){
		list[position].x1 = list[position + 1].x1;
		list[position].x2 = list[position + 1].x2;
		list[position].y1 = list[position + 1].y1;
		list[position].y2 = list[position + 1].y2;
		list[position].type = list[position + 1].type;
		list[position].style = list[position + 1].style;
		list[position].red = list[position + 1].red;
		list[position].blue = list[position + 1].blue;
		list[position].green = list[position + 1].green;
	}
	//place it at the end
	list[numObj].x1 = x1;
	list[numObj].x2 = x2;
	list[numObj].y1 = y1;
	list[numObj].y2 = y2;
	list[numObj].type = type;
	list[numObj].style = style;
	list[numObj].red = red;
	list[numObj].blue = blue;
	list[numObj].green = green;
}

/*
 * checkInRange
 * 		a functions that checks in (px,py) is in range of (x1,y2) tp (x2,y2)
 * 	Parameters:
 * 		px: the x coordinate to check
 * 		py: the y coordinate to check
 * 		x1: the first x coordinate of the range
 * 		y1: the first y coordinate of the range
 * 		x2: the second x coordinate of the range
 * 		y2: the seocnd y coordinate of the range
 * 	Returns:
 * 		GLboolean: true if inside the range false otherwise
 */
GLboolean checkInRange(GLint px, GLint py, GLint x1, GLint y1, GLint x2, GLint y2){
	GLboolean inRange = false;
	if(px > minPoint(x1,x2) and py > minPoint(y1,y2)){
		if(px < maxPoint(x1,x2) and py < maxPoint(y1, y2)){
			inRange = true;
		}
	}
	return inRange;
}

/*
 * circleFillPoints
 * 		a helper function that takes on point on the circle and lines for
 * 		all the connecting points on the circle
 * 	Parameters:
 * 		xc: the x center coordinate
 * 		yx: the y center coordinate
 * 		x: the distance to the x value on the circle
 * 		y: the distance to the y value on the circle
 *
 */
void circleFillPoints(GLint xc, GLint yc, GLint x, GLint y){
	glBegin (GL_LINES);
		glVertex2i(xc+x, yc+y);
		glVertex2i(xc-x, yc+y);
	glEnd();
	glBegin (GL_LINES);
		glVertex2i(xc+x, yc-y);
		glVertex2i(xc-x, yc-y);
	glEnd();
	glBegin (GL_LINES);
		glVertex2i(xc+y, yc+x);
		glVertex2i(xc-y, yc+x);
	glEnd();
	glBegin (GL_LINES);
		glVertex2i(xc+y, yc-x);
		glVertex2i(xc-y, yc-x);
	glEnd();
}

/*
 * circlePlotPoints
 * 		a helper function that takes on point on the circle and draws it and all
 * 		7 other points on that circle
 * 	Parameters:
 * 		xc: the x center coordinate
 * 		yx: the y center coordinate
 * 		x: the distance to the x value on the circle
 * 		y: the distance to the y value on the circle
 *
 */
void circlePlotPoints(GLint xc, GLint yc, GLint x, GLint y){
	glVertex2i(xc+x, yc+y);
	glVertex2i(xc-x, yc+y);
	glVertex2i(xc+x, yc-y);
	glVertex2i(xc-x, yc-y);
	glVertex2i(xc+y, yc+x);
	glVertex2i(xc-y, yc+x);
	glVertex2i(xc+y, yc-x);
	glVertex2i(xc-y, yc-x);
}

/*
 * colorMenu
 * 		the function that is used to determine color menu events and their resulting action
 * Parameters:
 * 		item: which item was clicked
 * 		(red=1 green=2 blue=3 black=4 white=5 yellow=6 cyan=7 magenta=8)
 */
void colorMenu(GLint item) {
	//red=1 green=2 blue=3 black=4 white=5 yellow=6 cyan=7 magenta=8
	if (item == 1) {
		red = 1.0;
		blue = 0.0;
		green = 0.0;
	} else if (item == 2) {
		red = 0.0;
		blue = 0.0;
		green = 1.0;
	} else if (item == 3) {
		red = 0.0;
		blue = 1.0;
		green = 0.0;
	} else if (item == 4) {
		red = 0.0;
		blue = 0.0;
		green = 0.0;
	}else if(item == 5){
		red = 1.0;
		blue = 1.0;
		green = 1.0;
	}else if(item == 6){
		red = 1.0;
		blue = 0.0;
		green = 1.0;
	}else if(item == 7){
		red = 0.0;
		blue = 1.0;
		green = 1.0;
	}else if (item == 8){
		red = 1.0;
		blue = 1.0;
		green = 0.0;
	}
	if(selection == 1){
		list[selected].red = red;
		list[selected].blue = blue;
		list[selected].green = green;
	}
}

/*
 * convertFromString
 * 		takes a string and converts it into an int
 * 	Parameters:
 * 		line: the string to be converted
 * 	Returns:
 * 		number: the converted number
 */
int convertFromString(string line){
	int number;
	istringstream(line) >> number; // convertFromString
	return number;
}

/*
 * deleteObject
 * 		a functions that takes an object positions and deletes it
 * Parameter:
 * 		object: the object position in the array
 *
 */
void deleteObject(GLint object){
	GLint position;
	for(position = object;position <numObj; position++){
		list[position].x1 = list[position + 1].x1;
		list[position].x2 = list[position + 1].x2;
		list[position].y1 = list[position + 1].y1;
		list[position].y2 = list[position + 1].y2;
		list[position].type = list[position + 1].type;
		list[position].style = list[position + 1].style;
		list[position].red = list[position + 1].red;
		list[position].blue = list[position + 1].blue;
		list[position].green = list[position + 1].green;
	}
	numObj -= 1;
	selection = 0;
}

/*
 * deselectObject
 * 		a function the de-selects the object and returns to drawing mode
 * Parameters:
 * 		none
 */
void deselectObject(){
	selected = 0;
	selection = 0;
	tool = 0;
}

/*
* drawCircle
* a functions that draws a  non-filled circle using mid point circle algorithm
* Parameters:
* 			  	x1: the first x coordinate
* 			  	y1: the first y coordinate
* 			  	x2: the second x coordinate
* 			  	y2: the second y coordiante
* 			  	red: The amount of red in rectangle
* 			  	blue: the amount of blue in rectangle
* 			  	green: the amount of green in rectangle
*/
void drawCircle(GLint x1, GLint y1, GLint x2, GLint y2, GLfloat red,
				GLfloat blue, GLfloat green)
{
	glPointSize(1.0);
	glColor3f(red, green, blue);
	GLint dx = x2 - x1, dy = y2 - y1;
	dx = dx * dx;
	dy = dy * dy;
	GLint radius;
	GLint p, x, y;
	radius = (GLint)(fabs(sqrt( dx + dy )));
	p = 1 - radius;
	x = 0;
	y = radius;
	glBegin(GL_POINTS);
	while(x < y){
		if (p < 0){
			p += x + x +1;
		}else{
			y -= 1;
			p += x +x - y - y +1;
		}
		circlePlotPoints(x1, y1, x, y);
		x += 1;
	}
	glEnd();
}

/*
 * drawLine
 * 		I attempted to implement Bresenham Line Drawing algorithm
 * 		STILL NEEDS WORK
 */
void drawLine(GLint x1, GLint y1, GLint x2, GLint y2, GLint style,
		   GLfloat red, GLfloat blue, GLfloat green)
{

	GLfloat slope;
	GLint dx = fabs(x2-x1);
	GLint dy = fabs(y2-y1);
	GLint ydirection = 1, xdirection = 1, xpdirection = 1, ypdirection = 1;
	GLint pgtzero, pltzero, p;
	GLint x,y, xEnd, yEnd;
	p = dy + dy - dx;
	pgtzero = dy + dy;
	pltzero = dy - dx + dy - dx;
	x = minPoint(x1,x2);
	xEnd = maxPoint(x1,x2);
	if (xEnd == x1){
		yEnd = y1;
		y = y2;
	}else{
		yEnd = y2;
		y = y1;
	}
	if(x1 != x2){
		slope = (GLfloat)(yEnd-y) / (GLfloat)(xEnd-x); //rise over run
		if(slope < 0.0){
			ydirection = -1;
			ypdirection = -1;
		}else if (slope > 0.0){
			ydirection = 1;
			ypdirection = 1;
		}else{
			ydirection = 0;
			ypdirection = 0;
		}

		if (fabs(slope) > 1.0){
			//favours y
			ypdirection = 0;
			xdirection = 0;
			pgtzero = dx + dx;
			pltzero = dx - dy + dx - dy;
		}else{
			//favours x
			xpdirection = 0;
			ydirection = 0;
		}
		glColor3f(red, green, blue);
		glPointSize(1.0);
		glBegin(GL_POINTS);
			glVertex2i(x,y);
			while (x != xEnd and y != yEnd){
				x += xdirection;
				y += ydirection;
				if(p < 0){
					p += pgtzero;
				}else{
					y += ypdirection;
					x += xpdirection;
					p += pltzero;
				}
				glVertex2i(x,y);
			}
		glEnd();
	}else{
		//vertical line
		y = minPoint(y1,y2);
		yEnd = maxPoint(y1,y2);
		glColor3f(red, green, blue);
		glPointSize(1.0);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		while(y < yEnd){
			y += 1;
			glVertex2i(x,y);
		}
		glEnd();
		printf("Vertical Line\n");
	}


}

/*
 * drawList
 * the drawing function that is called to display all the objects in list
 */
void drawList() {
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	if(numObj > 100){
		errorHandler();
	}
	for (int i = 1; i <= numObj; i++) {
		if (list[i].type == 1) {
			drawRectangle(list[i].x1, list[i].y1, list[i].x2, list[i].y2,
						  list[i].style, list[i].red, list[i].blue,
						  list[i].green);
			if (selection ==  1 and selected == i){
				if(red == 0.0  and blue == 0.0 and green == 0.0){
					drawRectangle(list[i].x1, list[i].y1, list[i].x2,
							list[i].y2, 0,1.0, 0.0, 0.0);
				}else{
					drawRectangle(list[i].x1, list[i].y1, list[i].x2,
							list[i].y2, 0,0.0, 0.0, 0.0);
				}

			}
		}else if(list[i].type == 2){
			if(list[i].style == 2){
				drawCircle(list[i].x1, list[i].y1, list[i].x2, list[i].y2,
						   list[i].red, list[i].blue, list[i].green);
			}else{
				fillCircle(list[i].x1, list[i].y1, list[i].x2, list[i].y2,
						   list[i].red, list[i].blue, list[i].green);
			}
			if (selection ==  1 and selected == i){
				if(red == 0.0  and blue == 0.0 and green == 0.0){
					drawCircle(list[i].x1, list[i].y1, list[i].x2,
							list[i].y2, 1.0, 0.0, 0.0);
				}else{
					drawCircle(list[i].x1, list[i].y1, list[i].x2,
							list[i].y2, 0.0, 0.0, 0.0);
				}
			}
		}else if (list[i].type == 3){
			drawLine(list[i].x1, list[i].y1, list[i].x2, list[i].y2,
						  list[i].style, list[i].red, list[i].blue,
						  list[i].green);
		}
	}
	glFlush();
}

/*
 * drawMenu
 * 		the function that is used to determine draw menu events and their resulting action
 * Parameters:
 * 		item: which item was clicked (1=Rectangle 2=Circle 3=Line)
 *
 */
void drawMenu(GLint item) {
	// Rectangle 1 Circle 2 Line 3
	tool = 0;
	if (item == 1){
		type = 1;
	}else if(item == 2){
		type = 2;
	}else if(item ==3){
		type = 3;
	}
}

/*
 * drawRectangle
 * a functions that draws a filled/outlined rectangle using GL_POLYGON
 * Parameters:
 * 			  	x1: the first x coordinate
 * 			  	y1: the first y coordinate
 * 			  	x2: the second x coordinate
 * 			  	y2: the second y coordiante
 * 			  	style: determines whether filled or outline (1 for filled, two for outline)
 * 			  	red: The amount of red in rectangle
 * 			  	blue: the amount of blue in rectangle
 * 			  	green: the amount of green in rectangle
 */
void drawRectangle(GLint x1, GLint y1, GLint x2, GLint y2, GLint style,
				   GLfloat red, GLfloat blue, GLfloat green)
{
	glColor3f(red, green, blue);
	if (style == 1) {
		glBegin(GL_POLYGON);
		glVertex2i(x1, y1);
		glVertex2i(x1, y2);
		glVertex2i(x2, y2);
		glVertex2i(x2, y1);
		glEnd();
	} else {
		glBegin(GL_LINES);
		glVertex2i(x1, y1);
		glVertex2i(x1, y2);
		glEnd();
		glBegin(GL_LINES);
		glVertex2i(x1, y2);
		glVertex2i(x2, y2);
		glEnd();
		glBegin(GL_LINES);
		glVertex2i(x2, y2);
		glVertex2i(x2, y1);
		glEnd();
		glBegin(GL_LINES);
		glVertex2i(x2, y1);
		glVertex2i(x1, y1);
		glEnd();
	}
}

/*
 * editMenu
 * 		the function that is used to determine edit menu events and their resulting action
 * Parameters:
 * 		item: which item was clicked
 * 		(1=select, 2=deselect 3=delete, 4=send to back, 5=bring to front 6=move)
 */
void editMenu(GLint item) {
	if(item == 1){
		//select
		tool = 1;
	}else if(item == 2){
		//Deselect
		deselectObject();
		tool = 0;
	}else if(item == 3){
		//Delete
		if (selection == 1){
			deleteObject(selected);
		}
		tool = 0;
	}else if(item == 4){
		//send to back
		if (selection == 1){
			sendToBack(selected);
		}
		tool = 0;
	}else if(item == 5){
		//bring to front
		if (selection == 1){
			bringToFront(selected);
		}
		tool = 5;
	}else if(item == 6){
		//move
		tool = 6;
	}
}

/*
 * errorHandler
 * 		a function that deals with error
 * 	Parameters:
 * 		none
 *
 */
void errorHandler(){
	renderBitmapString(100.0, 100.0, GLUT_BITMAP_8_BY_13, "Error:Over Capacity. Cannot store any more objects");
}


/*
* fillCircle
* a functions that draws a filled circle using mid point circle algorithm
* Parameters:
* 			  	x1: the first x coordinate
* 			  	y1: the first y coordinate
* 			  	x2: the second x coordinate
* 			  	y2: the second y coordiante
* 			  	red: The amount of red in rectangle
* 			  	blue: the amount of blue in rectangle
* 			  	green: the amount of green in rectangle
*/
void fillCircle(GLint x1, GLint y1, GLint x2, GLint y2, GLfloat red,
				GLfloat blue, GLfloat green)
{
	glPointSize(1.0);
	glColor3f(red, green, blue);
	GLint dx = x2 - x1, dy = y2 - y1;
	dx = dx * dx;
	dy = dy * dy;
	GLint radius;
	GLint p, x, y;
	radius = (GLint)(fabs(sqrt(dx + dy )));
	p = 1 - radius;
	x = 0;
	y = radius;
	while(x < y){
		if (p < 0){
			p += x + x + 1;
		}else{
			y -= 1;
			p += x + x - y - y + 1;
		}
		circleFillPoints(x1, y1, x, y);
		x += 1;
	}
}

/*
 * fileMenu
 * 		the function that is used to determine file menu events and their resulting action
 * Parameters:
 * 		item: which item was clicked (1=save to svg, 2=read from svg, 3=export to Bitmap)
 */
void fileMenu(GLint item) {
	if (item == 1){
		saveSVG();
	}else if(item == 2){
		readSVG();
	}else if (item == 3){
		saveBitmap("output.bmp", 0, 0, winWidth,winHeight);
	}
}

/*init
*this function it use to intialize the window
*Parameters: none
*Returns: none
*/
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, winHeight, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glFlush();
}

/*
 * maxPoint
 * 		a functions that finds the max value of the two
 * 	Parameters:
 * 		one: the first value to compare
 * 		two: the second value to compare
 * 	Returns:
 * 		GLint: the maximum value of the two
 */
GLint maxPoint(GLint one, GLint two){
	GLint result;
	if (one > two){
		result = one;
	}else{
		result = two;
	}
	return result;
}

/*
 * menu
 * 		the function that is used to determine main menu events and their resulting action
 * Parameters:
 * 		item: which item was clicked (2=exit, 1=delete)
 */
void menu(GLint item) {
	if (item == 2) {
		//exit
		exit(0);
	}else if(item == 1){
		//delete all items
		numObj = 0;
	}
}

/*
 * minPoint
 * 		a functions that finds the minimum value of the two
 * 	Parameters:
 * 		one: the first value to compare
 * 		two: the second value to compare
 * 	Returns:
 * 		GLint: the minimum value of the two
 */
GLint minPoint(GLint one, GLint two){
	GLint result;
	if (one < two){
		result = one;
	}else{
		result = two;
	}
	return result;
}

/*
 * Motion
 * 		a function that is called on mouse movement event
 * 	Parameters:
 * 		x: the x coordinate of the mouse
 * 		y: the y coordinate of the mouse
 */
void Motion(GLint x, GLint y) {
	if (drawing == 1 and tool == 0){
		//rubber band drawing effect
		list[numObj].x2 = x;
		list[numObj].y2 = y;
		//update display
		glutPostRedisplay();
	}else if(tool == 6){
		//moving event
		//figure out direction
		GLint dx = x - xbegin, dy = y - ybegin;
		//update object
		list[selected].x2 += dx;
		list[selected].y2 += dy;
		list[selected].x1 += dx;
		list[selected].y1 += dy;
		glutPostRedisplay();
		//update last click
		xbegin = x;
		ybegin = y;
	}
}

/*
 * mouseDraw
 * 		a function that gets called when on a mouse click event
 * 	Parameters:
 * 		button: which button was clicked
 * 		action: the action that caused the event
 * 		xMouse: the x coordinate of the mouse event
 * 		yMouse: the y coordinate of the mouse event
 */
void mouseDraw(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (action == GLUT_DOWN and button == GLUT_LEFT_BUTTON) {
		if(tool == 0){
			//drawing
			drawing = 1;
			numObj++;
			if (numObj > 100) {
				errorHandler();
			}else{
				setObject(numObj, xMouse, yMouse);
				glutPostRedisplay();
			}
		}else if(tool == 1){
			//selection
			selectObject(xMouse, yMouse);
			glutPostRedisplay();
		}else if(tool == 6){
			//moving
			xbegin = xMouse;
			ybegin = yMouse;
			selectObject(xMouse, yMouse);
			selection = 0;
		}
	}else if(action == GLUT_UP and button == GLUT_LEFT_BUTTON){
		if(tool == 0){
			drawing = 0;
			list[numObj].style = style;
			glutPostRedisplay();
		}
	}else if(action == GLUT_DOWN and button == GLUT_MIDDLE_BUTTON){
		if(selection ==1){
			deleteObject(selected);
		}
	}
	glFlush();
}

/*
 * readSVG
 * 		the function that is called to read an svg
 * 	Parameters:
 * 		none
 * 	Returns
 * 		0
 */
int readSVG(){
	//open File
	ifstream inFile("output.svg");
	string line;
	string value;
	GLint height, width;
	GLint start, end;
	//don't need first two lines
	getline(inFile,line);
	getline(inFile, line);
	//get height and width
	getline(inFile, line);
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of "
	value = line.substr(0, end);
	height = convertFromString(value);
	line = line.substr(end+1); //trim off more of the string
	start = line.find("\""); //find second occurrence of "
	value = line.substr(0,end);
	width = convertFromString(value);
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of "
	winWidth = width;
	winHeight = height;

	//read the rest of the characters
	while(getline(inFile, line)){
		if(line.find("rect") != -1){
			//rectangle
			numObj++;
			setRectangle(line);
		}else if(line.find("circle") != -1){
			//circle
			numObj++;
			setCircle(line);
		}else if(line.find("line") != -1){
			numObj++;
			setLine(line);
		}

	}
	//close file
	inFile.close();
	return 0;
}

/*
 * renderBitmapString
 * 		a function that prints the string at (x,y)
 * 	Parameters:
 * 		x: the x coordinate
 * 		y: the y coordinate
 * 		font: the glut bitmap font
 * 		string: the string to be printed
 */
void renderBitmapString(GLfloat x, GLfloat y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

/*
 * saveBitmap
 * 		a function that exports all the objects into a bitmap file called output
 * 	Parameters:
 * 		ptrcFileName: the file name string
 * 		nX: the starting x position
 * 		nY: the starting y position
 * 		nWidth: the width
 * 		nHeight: the height
 */
#define GL_BGR_EXT 0x80E0
int saveBitmap(const char *ptrcFileName, GLint nX, GLint nY, GLint nWidth, GLint nHeight)
{
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;

    unsigned char *ptrImage = (unsigned char*) malloc(sizeof(unsigned char)*nWidth*nHeight*3 + (4-(3*nWidth)%4)*nHeight);
    FILE *ptrFile = fopen(ptrcFileName, "wb");
    //read pixels from framebuffer
    glReadPixels(nX, nY, nWidth, nHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, ptrImage );
    // set memory buffer for bitmap header and informaiton header
    memset(&bf, 0, sizeof(bf));
    memset(&bi, 0, sizeof(bi));
    // configure the headers with the give parameters
    bf.bfType = 0x4d42;
        bf.bfSize = sizeof(bf) + sizeof(bi) + nWidth*nHeight*3 + (4-(3*nWidth)%4)*nHeight;
        bf.bfOffBits = sizeof(bf) + sizeof(bi);
        bi.biSize = sizeof(bi);
        bi.biWidth = nWidth + nWidth%4;
        bi.biHeight = nHeight;
        bi.biPlanes = 1;
        bi.biBitCount = 24;
        bi.biSizeImage = nWidth*nHeight*3 + (4-(3*nWidth)%4)*nHeight;
    // to files
    fwrite(&bf, sizeof(bf), 1, ptrFile);
	fwrite(&bi, sizeof(bi), 1, ptrFile);
	fwrite(ptrImage, sizeof(unsigned char), nWidth*nHeight*3 + (4-(3*nWidth)%4)*nHeight, ptrFile);
	fclose(ptrFile);
	free(ptrImage);
	return 0;
}

/*
 * saveSVG
 * 		a function that saves all the objects into an svg file called output
 * 	Parameters:
 * 		none
 *
 */
int saveSVG(){
	//open file
	FILE * outputFile;
	outputFile = fopen("output.svg", "w");
	//write header content
	fprintf(outputFile, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
	fprintf(outputFile, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	fprintf(outputFile, "<svg width=\"%i\" height=\"%i\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n", winWidth, winHeight);
	//variables
	GLint position;
	GLint r, b , g; //colours
	GLint height, width, radius; // things to calculate
	GLint x,y,x2,y2, dx, dy; // positions
	for(position=1;position <=numObj;position++){
		r = (int)(list[position].red * 256);
		b = (int)(list[position].blue * 256);
		g = (int)(list[position].green * 256);
		if(list[position].type == 1){
			//rectangle
			x = minPoint(list[position].x1,list[position].x2);
			y = minPoint(list[position].y1,list[position].y2);
			width = fabs(list[position].x1 - list[position].x2);
			height = fabs(list[position].y1 - list[position].y2);
			if (list[position].style == 2){ //outlined
				fprintf(outputFile, "<rect x=\"%i\" y=\"%i\" width=\"%i\" height=\"%i\" style=\"fill:none;stroke-width:1;stroke:rgb(%i,%i,%i)\" />\n",x,y,width, height,r,g,b);
			}else{
				fprintf(outputFile, "<rect x=\"%i\" y=\"%i\" width=\"%i\" height=\"%i\" style=\"fill:rgb(%i,%i,%i);stroke-width:1;stroke:rgb(%i,%i,%i)\" />\n",x,y,width, height,r,g,b,r,g,b);
			}
		}else if (list[position].type == 2){
			//circle
			x = list[position].x1;
			y = list[position].y1;
			dx = list[position].x2 - x;
			dy = list[position].y2 - y;
			dx = dx*dx;
			dy = dy*dy;
			radius = (GLint)(fabs(sqrt(dx + dy )));
			if(list[position].style == 1){ //filled
				fprintf(outputFile, "<circle cx=\"%i\" cy=\"%i\" r=\"%i\" style=\"fill:rgb(%i,%i,%i);stroke-width:1;stroke:rgb(%i,%i,%i)\" />\n",x,y,radius,r,g,b,r,g,b);
			}else{
				fprintf(outputFile, "<circle cx=\"%i\" cy=\"%i\" r=\"%i\" style=\"fill:none;stroke-width:1;stroke:rgb(%i,%i,%i)\" />\n",x,y,radius,r,g,b);
			}
		}else if(list[position].type == 3){
			x = list[position].x1;
			y = list[position].y1;
			x2 = list[position].x2;
			y2 = list[position].y2;
			fprintf(outputFile, "<line x1=\"%i\" y1=\"%i\" x2=\"%i\" y2=\"%i\" style=\"stroke:rgb(%i,%i,%i);stroke-width:1\" />\n",x,y,x2,y2,r,g,b);
		}
	}
	//print closing line
	fprintf(outputFile, "</svg>");
	//close file
	fclose(outputFile);
	return 0;
}

/*
 * selectObject
 * 		take mouse click co-ordinate and selects the top most object at that
 * 		position
 * Parameters:
 * 				x: the x spot that was clicked on
 * 				y: the y spot that was clicked on
 *
 */
void selectObject(GLint x, GLint y){
	GLboolean found = false;
	GLint position = numObj;
	GLint x1,y1,x2,y2;
	while(position > 0 and found == false){
		if(list[position].type == 2){
			// circle
			x1 = list[position].x1;
			y1 = list[position].y1;
			x2 = list[position].x2;
			y2 = list[position].y2;
			GLint dx = x2 - x1, dy = y2 - y1;
			dx = dx * dx;
			dy = dy * dy;
			GLfloat radius;
			GLfloat distance;
			distance = sqrt((x -x1)*(x-x1) + (y-y1) *(y-y1));
			radius = (GLfloat)(fabs(sqrt( dx + dy )));
			if(radius > distance){
				found = true;
			}else{
				position -= 1;
			}
		}else if(list[position].type == 1){
			//rectangle
			x1 = list[position].x1;
			y1 = list[position].y1;
			x2 = list[position].x2;
			y2 = list[position].y2;
			if (checkInRange(x, y, x1,y1 , x2, y2) == true)
			{
				found = true;
			}else{
					position -= 1;
			}
		}else{
			//line
			position -= 1;
		}

	}
	if (found == true){
		selected = position;
		selection = 1;
	}else{
		//allow for click away to deselect
		selected = 0;
		selection = 0;
	}
}

/*
 * sendToBack
 * 		a function that takes an objects position and sends it to the back
 * Parameters:
 * 		object: the objects position in the array
 *
 */
void sendToBack(GLint object){
	GLint position;
	GLint x1, x2, y1, y2, type, style;
	GLfloat red, blue, green;
	//save values
	x1 = list[object].x1;
	x2 = list[object].x2;
	y1 = list[object].y1;
	y2 = list[object].y2;
	type = list[object].type;
	style = list[object].style;
	red = list[object].red;
	blue = list[object].blue;
	green = list[object].green;
	//swap every item up one
	for(position = object;position > 1; position--){
		list[position].x1 = list[position - 1].x1;
		list[position].x2 = list[position - 1].x2;
		list[position].y1 = list[position - 1].y1;
		list[position].y2 = list[position - 1].y2;
		list[position].type = list[position - 1].type;
		list[position].style = list[position - 1].style;
		list[position].red = list[position - 1].red;
		list[position].blue = list[position - 1].blue;
		list[position].green = list[position - 1].green;
	}
	//set saved value to the first position
	list[1].x1 = x1;
	list[1].x2 = x2;
	list[1].y1 = y1;
	list[1].y2 = y2;
	list[1].type = type;
	list[1].style = style;
	list[1].red = red;
	list[1].blue = blue;
	list[1].green = green;
}

/*
 * setCircle
 * 		a function that takes a svg line for a circle and set the values for the circle into an object
 * 	Parameters:
 * 		line: the svg line
 * 	Returns:
 * 		0
 *
 *
 */
int setCircle(string line){
	GLint x1,x2,y1,y2, s, t=2, radius;
	GLfloat r,g,b;
	GLint start, end;
	string value;
	if(line.find("fill:none") == -1){
		s = 1;
	}else{
		s = 2;
	}

	//get x1
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end);//get sub string of the value
	x1 = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part
	//get y1
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end);//get sub string of the value
	y1 = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part
	//get radius
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end); //get sub string of the value
	radius = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part
	//get rgb
	start = line.find("rgb("); //find first occurrence of "
	line = line.substr(start+4); //substring it
	end = line.find(","); //find first occurrence of"
	value = line.substr(0,end); //get the float string
	istringstream(value) >> r; // convert to a float
	line = line.substr(end+1); //chop of the ,
	end = line.find(",");//find next comma
	value = line.substr(0,end); //get the float string
	istringstream(value) >> g; // convert to a float
	line = line.substr(end+1); //chop of the ,
	end = line.find(")");//find next comma
	value = line.substr(0,end); //get the float string
	istringstream(value) >> b; // convert to a float
	//set values
	x2 = x1 + radius;
	y2 = y1 + radius;
	list[numObj].x1 = x1;
	list[numObj].x2 = x2;
	list[numObj].y1 = y1;
	list[numObj].y2 = y2;
	list[numObj].style = s;
	list[numObj].type = t;
	list[numObj].red = r;
	list[numObj].blue = b;
	list[numObj].green = g;
	return 0;
}

/*
 *setLine
 *		a function thata takes a svg line for a line and set the values
 *	Parameters:
 *		line: the svg line
 *	Returns:
 *		0
 *
 */
int setLine(string line){
	GLint x1,x2,y1,y2, s, t=3;
	GLfloat r,g,b;
	GLint start, end;
	string value;
	if(line.find("fill:none") == -1){
		s = 1;
	}
	//get x1
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end);//get sub string of the value
	x1 = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part
	//get y1
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end);//get sub string of the value
	y1 = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part
	//get x2
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end);//get sub string of the value
	x2 = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part
	//get y2
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end);//get sub string of the value
	y2 = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part

	//get rgb
	start = line.find("rgb("); //find first occurrence of "
	line = line.substr(start+4); //substring it
	end = line.find(","); //find first occurrence of"
	value = line.substr(0,end); //get the float string
	istringstream(value) >> r; // convert to a float
	line = line.substr(end+1); //chop of the ,
	end = line.find(",");//find next comma
	value = line.substr(0,end); //get the float string
	istringstream(value) >> g; // convert to a float
	line = line.substr(end+1); //chop of the ,
	end = line.find(")");//find next comma
	value = line.substr(0,end); //get the float string
	istringstream(value) >> b; // convert to a float
	//set values
	list[numObj].x1 = x1;
	list[numObj].x2 = x2;
	list[numObj].y1 = y1;
	list[numObj].y2 = y2;
	list[numObj].style = s;
	list[numObj].type = t;
	list[numObj].red = r;
	list[numObj].blue = b;
	list[numObj].green = g;
	return 0;
	return 0;
}

/*
 * setObject
 * 		a helper functions to help set a new object
 * 	Parameters:
 * 		numObj: the object position in the array
 * 		x: the x coordinate of creation
 * 		y: the y coordinate of creation
 */
void setObject(GLint numObj, GLint x, GLint y) {
	list[numObj].x1 = x;
	list[numObj].y1 = y;
	list[numObj].x2 = x;
	list[numObj].y2 = y;
	list[numObj].type = type;
	list[numObj].style = 2;
	list[numObj].red = red;
	list[numObj].blue = blue;
	list[numObj].green = green;
}

/*
 * setRectangle
 * 		a function that takes a string of svg rect and sets the value to a rectangle object
 * 	Parameters:
 * 		line: a string representation in svg format for the rectangle
 * 	Returns:
 * 		0
 */
int setRectangle(string line){
	GLint x1,x2,y1,y2, s, t=1, width, height;
	GLfloat r,g,b;
	GLint start, end;
	string value;
	if(line.find("fill:none") == -1){
		s = 1;
	}else{
		s = 2;
	}
	printf("Style: %i\n", s);
	//get x1
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end);//get sub string of the value
	x1 = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part
	//get y1
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end);//get sub string of the value
	y1 = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part
	//get width
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end); //get sub string of the value
	width = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part
	//get height
	start = line.find("\""); //find first occurrence of "
	line = line.substr(start+1); //substring it
	end = line.find("\""); //find first occurrence of"
	value = line.substr(0,end); //get sub string of the value
	height = convertFromString(value); //convert it
	line = line.substr(end+1); //chop off the previous part
	//get rgb
	start = line.find("rgb("); //find first occurrence of "
	line = line.substr(start+4); //substring it
	end = line.find(","); //find first occurrence of"
	value = line.substr(0,end); //get the float string
	istringstream(value) >> r; // convert to a float
	line = line.substr(end+1); //chop of the ,
	end = line.find(",");//find next comma
	value = line.substr(0,end); //get the float string
	istringstream(value) >> g; // convert to a float
	line = line.substr(end+1); //chop of the ,
	end = line.find(")");//find next comma
	value = line.substr(0,end); //get the float string
	istringstream(value) >> b; // convert to a float

	//set values
	x2 = width + x1;
	y2 = height + y1;
	list[numObj].x1 = x1;
	list[numObj].x2 = x2;
	list[numObj].y1 = y1;
	list[numObj].y2 = y2;
	list[numObj].style = s;
	list[numObj].type = t;
	list[numObj].red = r;
	list[numObj].blue = b;
	list[numObj].green = g;
	return 0;
}

/*
 * styleMenu
 * 		the function that is used to determine style menu events and their resulting action
 * Parameters:
 * 		item: which item was clicked (1=filled, 2=outline)
 */
void styleMenu(GLint item) {
	if (item == 1) {
		style = 1; //filled
	} else {
		style = 2; //outline
	}
}

/*
 * winReshapeFcn
 * 		a functions that is called on window Resize
 * 	Parameters:
 * 		newWidth: the new window width
 * 		newHeight: the new window height
 */
void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), GLdouble(newHeight), 0.0);
	/* Reset display-window size parameters. */
	winWidth = newWidth;
	winHeight = newHeight;
	drawList();
	glFlush();
}

// main function
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	windowId = glutCreateWindow(
			"SimpleDraw Sample for Assignment 1 (by Dallas Fraser)");

	//draw menu
	GLint drawMenuId = glutCreateMenu(drawMenu);
	glutAddMenuEntry("Rectangle", 1);
	glutAddMenuEntry("Circle", 2);
	glutAddMenuEntry("Line", 3);

	//edit menu
	GLint editMenuId = glutCreateMenu(editMenu);
	glutAddMenuEntry("Select", 1);
	glutAddMenuEntry("Deselect", 2);
	glutAddMenuEntry("Delete", 3);
	glutAddMenuEntry("Send to Back", 4);
	glutAddMenuEntry("Bring to Front", 5);
	glutAddMenuEntry("Move", 6);

	//style menu
	GLint styleMenuId = glutCreateMenu(styleMenu);
	glutAddMenuEntry("Filled", 1);
	glutAddMenuEntry("Outlined", 2);

	//colours menu
	GLint colourMenuId = glutCreateMenu(colorMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);
	glutAddMenuEntry("Yellow", 6);
	glutAddMenuEntry("Cyan", 7);
	glutAddMenuEntry("Magenta", 8);

	//file menu
	GLint fileMenuId = glutCreateMenu(fileMenu);
	glutAddMenuEntry("Save SVG file", 1);
	glutAddMenuEntry("Open SVG file", 2);
	glutAddMenuEntry("Export to Bitmap", 3);

	//main menu
	glutCreateMenu(menu);
	glutAddMenuEntry("New", 1);
	glutAddSubMenu("Draw", drawMenuId);
	glutAddSubMenu("Edit", editMenuId);
	glutAddSubMenu("Styles", styleMenuId);
	glutAddSubMenu("Colours", colourMenuId);
	glutAddSubMenu("File", fileMenuId);
	glutAddMenuEntry("Quit", 2);

	//attach click to menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	// register call back funtions
	glutDisplayFunc(drawList);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouseDraw);
	glutMotionFunc(Motion);
	glutMainLoop();
}
