#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")


#include <iostream>
#include <stdio.h>
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>


#include "vector.h"
// #include "glut.h"             // OpenGL utilties

using namespace MyOGLProg;

#include "stdlib.h"

//prototypes for our callback functions
void DisplayScene(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation


void DrawVector(Position& startPos, Vector& v1)
{
	//draw the vector v1 starting from position startPos
	//this function will only work as long as the z coordinate for both positions is zero
	float length = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	Vector v;
	if (length > 0.0){ v.x = v1.x/length; v.y = v1.y/length; v.z = v1.z/length; }
	else return;
	float d = (v.x * 0.0) + (v.y * 1.0) + (v.z * 0.0);
	float a = RAD2DEG(acos(d));
	if (v.x > 0.0) a = -a;

	glPushMatrix();
	glTranslatef(startPos.x, startPos.y, startPos.z);
	glRotatef(a,0.0,0.0,1.0);
	float space = 0.25;
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, length, 0.0);

		glVertex3f(0.0, length, 0.0);
		glVertex3f(-space, length - (space * 1.5), 0.0);

		glVertex3f(0.0, length, 0.0);
		glVertex3f(space, length - (space * 1.5), 0.0);
	glEnd();
	glPopMatrix();
}

void Answer1(void)
{
	Position position;
	position.x = 1.0; position.y = 2.0; position.z = 0.0;
	Vector vector(4.0, 2.0, 0.0);
	DrawVector(position, vector);
}

void Answer2(void)
{
	Position position;
	position.x = 0.0; position.y = 0.0; position.z = 0.0;
	Vector vector1(4.0, 2.0, 0.0);
	Vector vector2(-2.0, 3.0, 0.0);
	Vector vector3 = vector1.addTo(vector2);
	DrawVector(position, vector3);
}

void Answer3(void)
{
	Position position;
	position.x = 0.0; position.y = 0.0; position.z = 0.0;

	Vector vector1(0.0, 1.0, 0.0);
	Vector vector2(0.707, 0.707, 0.0);

	DrawVector(position, vector1);
	DrawVector(position, vector2);

	float dotProduct = vector1.getDotProduct(vector2);

	vector1.normalise();
	vector2.normalise();
	float normDotProduct = vector1.getDotProduct(vector2);

	float cosangle = dotProduct/normDotProduct;

	float angle = RAD2DEG(acos(cosangle));

	std::cout << angle << '\n';
}

void Answer4(void)
{
	Position position;
	position.x = 0.0; position.y = 0.0; position.z = 0.0;

	Vector vector1(4.0, 4.0, 0.0);
	Vector vector2(-2.0, 3.0, 0.0);

	DrawVector(position, vector1);
	DrawVector(position, vector2);

	float dotProduct = vector1.getDotProduct(vector2);

	// vector1.normalise();
	// vector2.normalise();

	float magVec1 = vector1.getMagnitude();
	float magVec2 = vector2.getMagnitude();

	float cosangle = ((int)((100.0*dotProduct)/(magVec1*magVec2))/100.0);

	std::cout << cosangle << '\n';

	if (cosangle == 1.0){
		std::cout << "Same angle" << '\n';
	}
	else{
		std::cout << "Different angle" << '\n';
	}
}

void Answer5(void)
{
	Position position;
	position.x = 0.0; position.y = 0.0; position.z = 0.0;

	Vector vector1(5.0, 4.0, 0.0);
	Vector vector2(3.0, 9.0, 0.0);

	DrawVector(position, vector1);
	DrawVector(position, vector2);

	float mag2 = vector2.getMagnitude();
	float dotProduct = vector1.getDotProduct(vector2);

	float scalar = (dotProduct/(pow(mag2, 2)));

	Vector proj1on2;

	proj1on2.x = vector2.x*scalar;
	proj1on2.y = vector2.y*scalar;
	proj1on2.z = vector2.z*scalar;

	Vector vector3 = vector1.subtractFrom(proj1on2);

	position.x = 5.0; position.y = 4.0; position.z = 0.0;

	DrawVector(position, vector3);
}

void Answer6(void)
{
	Vector firstPointOne(1.0, 8.0, 0.0);
	Vector firstPointTwo(5.0, 4.0, 0.0);

	Vector secondPointOne(3.0, 0.0, 0.0);
	Vector secondPointTwo(-6.0, 0.0, 0.0);

	Vector vector1 = firstPointOne.subtractFrom(firstPointTwo);
	Vector vector2 = secondPointOne.subtractFrom(secondPointTwo);

	float dotProduct = vector1.getDotProduct(vector2);

	float magVec1 = vector1.getMagnitude();
	float magVec2 = vector2.getMagnitude();

	float cosangle = ((int)((100.0*dotProduct)/(magVec1*magVec2))/100.0);

	float angle = RAD2DEG(acos(cosangle));

	std::cout << angle << '\n';
}

void Answer7(void)
{
	Position position;

	position.x = 0.0; position.y = 0.0; position.z = 0.0;

	Vector firstPointOne(-2.5, -2.0, 0.0);
	Vector firstPointTwo(5.0, -2.0, 0.0);

	Vector vector1 = firstPointOne.subtractFrom(firstPointTwo);

	Vector secondPointOne(-2.5, -2.0, 0.0);
	Vector secondPointTwo(8.0, 3.0, 0.0);

	Vector vector2 = secondPointOne.subtractFrom(secondPointTwo);


	vector1.normalise();
	std::cout << "Coordinates of the point:" << '\n';

	float length = vector2.getDotProduct(vector1);
	Vector result;
	result.x = (length+firstPointOne.x)*vector1.x;
	result.y = (length+firstPointOne.y)*vector1.y;
	result.z = (length+firstPointOne.z)*vector1.z;

	std::cout << result.x << '\n';
	std::cout << result.y << '\n';
	std::cout << result.z << '\n';

	// DrawVector(position, refVector);

}


//our main routine
int main(int argc, char *argv[])
{
  //Initialise Glut and create a window
  glutInit(&argc, argv);
  //sets up our display mode
  //here we've selected an RGBA display with depth testing
  //and double buffering enabled
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  //create a window and pass through the windows title
  glutCreateWindow("Basic Glut Application");

  //run our own drawing initialisation routine
  init_drawing();

  //tell glut the names of our callback functions point to our
  //functions that we defined at the start of this file
  glutReshapeFunc(reshape);
  glutKeyboardFunc(key);
  glutIdleFunc(idle);
  glutDisplayFunc(DisplayScene);

  //request a window size of 600 x 600
  glutInitWindowSize(600,600);
  glutReshapeWindow(600,600);

  //go into the main loop
  //this loop won't terminate until the user exits the
  //application
  glutMainLoop();

  return 0;
}



/*****************************************************************************
 DisplayScene()

 The work of the application is done here. This is called by glut whenever the
//window needs to be redrawn
*****************************************************************************/

void DisplayScene(void)
{
  //clear the current window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //make changes to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  //initialise the modelview matrix to the identity matrix
  glLoadIdentity();

  glTranslatef(-10.0,-10.0,-25.0);

  /*glColor3f(1.0,0.0,0.0);
  glBegin(GL_POINTS);
	glVertex3f(0.0,0.0,-5.0);
  glEnd();*/

  GLfloat yellow[4] = { 1.0f, 1.0f, 0.2f, 1.0f };
  GLfloat blue[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
  GLfloat green[4] = { 0.2f, 1.0f, 0.2f, 1.0f };
Position origin;
origin.x = origin.y = origin.z = 0.0;

  //define a position and a vector
  Position p1;
  p1.x = 1.0; p1.y = 1.0; p1.z = 0.0;
  Vector v1(4.0, 4.0, 0.0);

  //draw the vector at position
  glDisable(GL_LINE_STIPPLE);
  glLineWidth(2.0);
	glColor3f(1.0,1.0,0.0);
	Answer7();
	glColor3f(0.0,1.0,0.0);
  // DrawVector(p1,v1);

  //draw a red horizontal line, one unit long
  glLineWidth(1.0);
  glColor3f(3.0,0.0,0.0);
  glPushMatrix();
	  glTranslatef(0.0, 0.0, 0.0);
	  glBegin(GL_LINES);
		glVertex2f(0.0,0.0);
		glVertex2f(1.0,0.0);
	  glEnd();
  glPopMatrix();

  //draw a green vertical line, one unit high
  glLineWidth(1.0);
  glColor3f(0.0,0.0,1.0);
  glPushMatrix();
	  glBegin(GL_LINES);
		glVertex2f(0.0,0.0);
		glVertex2f(0.0,1.0);
	  glEnd();
  glPopMatrix();

  //draw a white point at the origin
  glPointSize(2.0);
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
	  glTranslatef(0.0, 0.0, 0.0);
	  glBegin(GL_POINTS);
		glVertex2f(0.0,0.0);
	  glEnd();
  glPopMatrix();

  //flush what we've drawn to the buffer
  glFlush();
  //swap the back buffer with the front buffer
  glutSwapBuffers();
}

//idle callback function - this is called when there is nothing
//else to do
void idle(void)
{
  //this is a good place to do animation
  //since there are no animations in this test, we can leave
  //idle() empty
}

//key callback function - called whenever the user presses a
//key
void key(unsigned char k, int x, int y)
{
  switch(k)
  {
    case 27: //27 is the ASCII code for the ESCAPE key
     exit(0);
      break;
  }
}

//reshape callback function - called when the window size changed
void reshape(int width, int height)
{
  //set the viewport to be the same width and height as the window
  glViewport(0,0,width, height);
  //make changes to the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //set up our projection type
  //we'll be using a perspective projection, with a 90 degree
  //field of view
  gluPerspective(45.0, (float) width / (float) height, 1.0, 100.0);
  //redraw the view during resizing
  DisplayScene();
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
  //glDepthFunc(GL_LEQUAL);
  //glEnable(GL_DEPTH_TEST);

  //glClearColor(1.0,0.0,0.0,0.0);
}
