#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <glm/glm.hpp>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
#endif

#include <string>
#include <iostream>
#include <stdio.h>

#include "myVector.h"
#include "myMatrix.h"

// #include "vector.h"
using namespace MyMathLab;
using namespace std;

#include "stdlib.h"

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation

int piece = 0;      // Keeps track of the current selected piece
int frames = 0;     // Counts the number of frames since starting the app
int noOfPieces = 9; // The number of pieces we are going to create

					// Class Piece:
					//    members: * current position and angle in space,
					//                * goal position and angle,
					//                * flag for when the piece is at its
					//                 goal position and when it's not
					//    functions:  * setGoal() sets the goal x, y and angle
					//                  value for when the piece should be
					//                  concidered being in the right place,
					//                * setPos() sets the new position of the
					//                  piece.
					//                * toggleInPlace() toggles the flag for
					//                  when the piece is considered being in
					//                  the right place and not.
					//                * functions to access the members.
class Piece {
	float xPan, yPan, angle, goalX, goalY, goalAngle, inPlace;
public:
	void setGoal(float, float, float);
	void setPos(float, float, float);
	void toggleInPlace(bool);
	float getGoalX() {
		return goalX;
	}
	float getGoalY() {
		return goalY;
	}
	float getGoalAngle() {
		return goalAngle;
	}
	float getX() {
		return xPan;
	}
	float getY() {
		return yPan;
	}
	float getAngle() {
		return angle;
	}
	bool getInPlace() {
		return inPlace;
	}
};

// Sets the new position and angle of the object
void Piece::setPos(float new_xPan, float new_yPan, float new_angle) {
	xPan += new_xPan;
	yPan += new_yPan;
	angle += new_angle;
}

//Sets the goal position and angle of the object
void Piece::setGoal(float new_goalX, float new_goalY, float new_goalAngle) {
	goalX = new_goalX;
	goalY = new_goalY;
	goalAngle = new_goalAngle;
}

// Toggles the inPlace-member
void Piece::toggleInPlace(bool flag) {
	inPlace = flag;
}

//Create the pieces and put them in an array:
Piece piece1;
Piece piece2;
Piece piece3;
Piece piece4;
Piece piece5;
Piece piece6;
Piece piece7;
Piece piece8;
Piece piece9;

Piece pieces[] = { piece1, piece2, piece3, piece4, piece5, piece6, piece7, piece8, piece9 };


//TEXT
void drawBitmapText(char *string, float x, float y, float z) //3D font in case we want to add depth
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void drawStrokeText(char*string, int x, int y, int z) //Itterates over all the characters and draws them
{
	char *c;
	glPushMatrix();
	glTranslatef(x, y + 8, z);
	glScalef(0.15f, -0.15f, z); //Scaling for text

	for (c = string; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c); //displays each character
	}
	glPopMatrix();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void reshapeText(int w, int h)
{

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1, 1, 1);
	drawStrokeText((char*)"Move and rotate the squares in the right configuration (\n) configurationconfigurationconfigurationconfiguration", 0, 10, 0);
	drawStrokeText((char*)"Move the squares with wasd, rotate them with q & e.", 0, 35, 0);
	drawStrokeText((char*)"Change the square being controlled with z & x.", 0, 60, 0);
	drawStrokeText((char*)"The squares turn green when in the correct position.", 0, 85, 0);

	glutSwapBuffers();
}



//TEXT




void draw_square(int iteration)
{
	// a simple function to draw a square with the current markers
	// orientation and position on screen
	float centerColor = 1.0;
	bool isInPlace = pieces[iteration].getInPlace();

	if (isInPlace) {
		centerColor = 0.0;
	}
	else if (iteration == piece) {
		centerColor = 0.8;
	}
	// 3:1
	if (iteration == 0) {
		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);

		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, 0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.5, -0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(0.5, 0.5, 0.0);
		glEnd();
	}

	// 3:2
	else if (iteration == 1) {
		glBegin(GL_POLYGON);
		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(-0.5, 0.5, 0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-0.5, -0.5, 0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.5, -0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(0.5, 0.5, 0.0);
		glEnd();
	}

	// 3:3
	else if (iteration == 2) {
		glBegin(GL_POLYGON);
		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(-0.5, 0.5, 0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-0.5, -0.5, 0.0);

		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.5, -0.5, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glEnd();
	}

	// 2:1
	else if (iteration == 3) {
		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(0.5, -0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(0.5, 0.5, 0.0);
		glEnd();
	}

	// 2:2
	else if (iteration == 4) {
		glBegin(GL_POLYGON);
		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(-0.5, 0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(-0.5, -0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(0.5, -0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(0.5, 0.5, 0.0);
		glEnd();
	}

	// 2:3
	else if (iteration == 5) {
		glBegin(GL_POLYGON);
		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(-0.5, 0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(-0.5, -0.5, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.5, -0.5, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glEnd();
	}

	// 1:1
	else if (iteration == 6) {
		glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(0.5, -0.5, 0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.5, 0.5, 0.0);
		glEnd();
	}

	// 1:2
	else if (iteration == 7) {
		glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-0.5, 0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(-0.5, -0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(0.5, -0.5, 0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.5, 0.5, 0.0);
		glEnd();
	}

	// 1:3
	else if (iteration == 8) {
		glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-0.5, 0.5, 0.0);

		glColor3f(centerColor, 1.0, centerColor);
		glVertex3f(-0.5, -0.5, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.5, -0.5, 0.0);

		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glEnd();
	}
}

//our main routine
//our main routine
int main(int argc, char *argv[])
{
	//Initialise Glut and create a window
	glutInit(&argc, argv);

	//Window 2
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//create a window and pass through the windows title
	glutCreateWindow("Instruction"); //Instruction window



									 //run our own drawing initialisation routine


									 //tell glut the names of our callback functions point to our
									 //functions that we defined at the start of this file

	glutIdleFunc(render);
	glutReshapeFunc(reshapeText);
	glutDisplayFunc(render);


	//request a window size of 800 x 400 for the instructions
	glutInitWindowSize(800, 400);
	//glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 680) / 2); //Moves the window to the start position
	glutReshapeWindow(800, 400);
	glutInitWindowPosition(830, 10);//Sets the puzzlewindows startposition

									//sets up our display mode
									//here we've selected an RGBA display with depth testing
									//and double buffering enabled
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	//create a window and pass through the windows title
	glutCreateWindow("Puzzle"); //Puzzle window

								//run our own drawing initialisation routine
	init_drawing();

	//tell glut the names of our callback functions point to our
	//functions that we defined at the start of this file
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutDisplayFunc(draw);

	//request a window size of 800 x 800 for the puzzle
	glutInitWindowSize(800, 800);
	//glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 680) / 2); //Moves the window to the start position
	glutReshapeWindow(800, 800);







	//go into the main loop
	//this loop won't terminate until the user exits the
	//application
	glutMainLoop();

	return 0;

}

//draw callback function - this is called by glut whenever the
//window needs to be redrawn
void draw(void)
{
	// Counter of each time a new frame is rendered through draw()
	frames += 1;

	//clear the current window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//make changes to the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	//initialise the modelview matrix to the identity matrix
	glLoadIdentity();

	// Initialize the pieces on the first frame;
	// set their start and goal position
	if (frames == 1) {
		// 3:1
		pieces[0].setPos(1.4f, 1.4f, 4.0f);
		pieces[0].setGoal(-0.8f, -1.2f, 10.0f);

		// 3:2
		pieces[1].setPos(-1.2f, 1.0f, -12.0f);
		pieces[1].setGoal(0.2f, -1.2f, 10.0f);

		// 3:3
		pieces[2].setPos(0.4f, 1.6f, -30.0f);
		pieces[2].setGoal(1.2f, -1.2f, 10.0f);

		// 2:1
		pieces[3].setPos(0.2f, 0.6f, 20.0f);
		pieces[3].setGoal(-0.8f, -0.2f, 10.0f);

		// 2:2
		pieces[4].setPos(1.2f, 1.0f, -18.0f);
		pieces[4].setGoal(0.2f, -0.2f, 10.0f);

		// 2:3
		pieces[5].setPos(0.6f, 1.2f, 60.0f);
		pieces[5].setGoal(1.2f, -0.2f, 10.0f);

		// 1:1
		pieces[6].setPos(0.8f, 1.4f, 20.0f);
		pieces[6].setGoal(-0.8f, 0.8f, 10.0f);

		// 1:2
		pieces[7].setPos(1.0f, 1.0f, -12.0f);
		pieces[7].setGoal(0.2f, 0.8f, 10.0f);

		// 1:3
		pieces[8].setPos(-0.6f, 1.6f, -2.0f);
		pieces[8].setGoal(1.2f, 0.8f, 10.0f);

	}

	// Check if each piece is on the right place every frame,
	// if not; set their inPlace-attribute to false.
	for (int iteration = 0; iteration < noOfPieces; ++iteration) {
		// Rounding because of problem with the floating numbers
		if (round(pieces[iteration].getX() * 100) / 100 == round(pieces[iteration].getGoalX() * 100) / 100 && round(pieces[iteration].getY() * 100) / 100 == round(pieces[iteration].getGoalY() * 100) / 100 && round(pieces[iteration].getAngle() * 100) / 100 == round(pieces[iteration].getGoalAngle() * 100) / 100) {
			pieces[iteration].toggleInPlace(true);
			// std::cout << pieces[iteration].getInPlace();
		}
		else {
			// If a piece once was in the right place but then was
			// moved again, it should toggle back to false:
			pieces[iteration].toggleInPlace(false);
			// std::cout << pieces[iteration].getInPlace();
		}
	}

	// Initialize a frame for the puzzle pieces in order to
	// give a hint of where the puzzle should be put
	glTranslatef(0.0, 0.0, -25.0);

	// Axis
	glLineWidth(1.0);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(-4.95, -9.55, 0.0);
	glRotatef(10.0, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(12.0, 0.0);
	glEnd();
	glPopMatrix();

	glLineWidth(1.0);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(-4.95, -9.55, 0.0);
	glRotatef(10.0, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 12.0);
	glEnd();
	glPopMatrix();


	// Instruction axis
	glLineWidth(1.0);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(-9.6, 7.9, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(2.0, 0.0);
	glEnd();
	glPopMatrix();

	glLineWidth(1.0);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(-9.6, 7.9, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 2.0);
	glEnd();
	glPopMatrix();

	//   glLineWidth(1.0);
	//   glColor3f(0.5,0.5,0.5);
	//   glPushMatrix();
	//   glRotatef(45.0, 0.0f, 0.0f, 1.0f);
	//      glTranslatef(-7, 9, 0.0);
	//     glBegin(GL_LINES);
	//     glVertex2f(0.0,0.0);
	//     glVertex2f(0.5,0.0);
	//     glEnd();
	//   glPopMatrix();
	//
	//   glLineWidth(1.0);
	//   glColor3f(0.5,0.5,0.5);
	//   glPushMatrix();
	//   glTranslatef(-7, 9, 0.0);
	//   glRotatef(90.0, 0.0f, 0.0f, 1.0f);
	//     glBegin(GL_LINES);
	//     glVertex2f(0.0,0.0);
	//     glVertex2f(0.0,0.5);
	//     glEnd();
	//   glPopMatrix();


	// Semi-interactive, instructive square
	int square = -2;
	for (int i = 0; i < 3; ++i) {
		square += 2;
		for (int k = 0; k < 3; ++k) {
			//   if (k == 1 && i == 0){
			//     glPushMatrix();
			//       glTranslatef(k-11, i+10, -5.0f);
			//       glRotatef(0.0, 0.0f, 0.0f, 1.0f);
			//       draw_square(3);
			//     glPopMatrix();
			//   }
			//   else{
			//   glPushMatrix();
			//     glTranslatef(k-11, i+10, -5.0f);
			//     glRotatef(0.0, 0.0f, 0.0f, 1.0f);
			//     draw_square(i+k);
			//   glPopMatrix();
			// }
			// if (i == 1){
			//     glPushMatrix();
			//       glTranslatef(k-11, i+10, -5.0f);
			//       glRotatef(0.0, 0.0f, 0.0f, 1.0f);
			//       draw_square(i+k);
			//     glPopMatrix();
			// }
			glPushMatrix();
			glTranslatef(k - 11, i + 10, -5.0f);
			glRotatef(0.0, 0.0f, 0.0f, 1.0f);
			draw_square(i + k + square);
			glPopMatrix();
		}
	}

	// for (int i = 0; i < 2; ++i){
	//   for (int k = 0; k < 2; ++k){
	//     if (k == 1 && i == 0){
	//       glPushMatrix();
	//         glTranslatef(k-9, i+8, -5.0f);
	//         glRotatef(0.0, 0.0f, 0.0f, 1.0f);
	//         draw_square(3);
	//       glPopMatrix();
	//     }
	//     else{
	//     glPushMatrix();
	//       glTranslatef(k-11, i+10, -5.0f);
	//       glRotatef(0.0, 0.0f, 0.0f, 1.0f);
	//       draw_square(i+k);
	//     glPopMatrix();
	//   }
	//   }
	//   }

	glEnd();

	glLoadIdentity();

	// For each Piece object; draw it with it's current
	// position and angle.
	for (int iteration = 0; iteration < noOfPieces; ++iteration) {
		glPushMatrix();
		glRotatef(pieces[iteration].getAngle(), 0.0f, 0.0f, 1.0f);
		glTranslatef(pieces[iteration].getX(), pieces[iteration].getY(), -5.0f);
		draw_square(iteration);
		glPopMatrix();
	}

	//flush what we've drawn to the buffer

	glFlush();
	//swap the back buffer with the front buffer
	glutSwapBuffers();
}

//idle callback function - this is called when there is nothing
//else to do
void idle(void) {}

//key callback function - called whenever the user presses a
//key
void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27: //esc - quit the application
		exit(0);
		break;

	case 113: //Q - rotate counter-clockwise
		pieces[piece].setPos(0.0f, 0.0f, 2.0f);
		draw();
		break;

	case 101: //E - rotate clockwise
		pieces[piece].setPos(0.0f, 0.0f, -2.0f);
		draw();
		break;

	case 119: //W - translate up
		pieces[piece].setPos(0.0f, 0.2f, 0.0f);
		draw();
		break;

	case 97: //A - translate left
		pieces[piece].setPos(-0.2f, 0.0f, 0.0f);
		draw();
		break;

	case 115: //S - translate down
		pieces[piece].setPos(0.0f, -0.2f, 0.0f);
		draw();
		break;

	case 100: //D - translate right
		pieces[piece].setPos(0.2f, 0.0f, 0.0f);
		draw();
		break;

	case 120: //X - next piece
		piece += 1;
		if (piece == noOfPieces) {
			piece = 0;
		}
		draw();
		break;

	case 122: //Z - last piece
		piece -= 1;
		if (piece < 0) {
			piece = noOfPieces - 1;
		}
		draw();
		break;

	}
}

//reshape callback function - called when the window size changed
void reshape(int width, int height)
{
	//set the viewport to be the same width and height as the window
	glViewport(0, 0, width, height);
	//make changes to the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set up our projection type
	//we'll be using a perspective projection, with a 90 degree
	//field of view
	gluPerspective(45.0, (float)width / (float)height, 1.0, 100.0);
	//redraw the view during resizing
	draw();
}

//set up OpenGL before we do any drawing
//this function is only called once at the start of the program
void init_drawing(void)
{
	//blend colours across the surface of the polygons
	//another mode to try is GL_FLAT which is flat shading
	glShadeModel(GL_SMOOTH);
	//turn lighting off
	glDisable(GL_LIGHTING);
	//enable OpenGL hidden surface removal
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
}
