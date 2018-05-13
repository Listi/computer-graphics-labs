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
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <string>
#include <iostream>
#include <stdio.h>

#include "myVector.h"
#include "myMatrix.h"

// #include "vector.h"
using namespace MyMathLab;

#include "stdlib.h"

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation
float angle = -10.0;

void draw_square (void)
{
  // a simple function to draw a square with the current markers
  // orientation and position on screen

  glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, 1.0, 0.0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, -1.0, 0.0);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0);
  glEnd();
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
  glutDisplayFunc(draw);

  //request a window size of 600 x 600
  glutInitWindowSize(600,600);
  glutReshapeWindow(600,600);

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
  angle += 5.0;
  //clear the current window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //make changes to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  //initialise the modelview matrix to the identity matrix
  glLoadIdentity();

  //***DO ALL YOUR DRAWING HERE****//

  glTranslatef(0.0, 0.0, -25.0);

    /*glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
  	glVertex3f(0.0,0.0,-5.0);
    glEnd();*/


    //draw the vector at position
    glDisable(GL_LINE_STIPPLE);
    glLineWidth(2.0);
  	glColor3f(1.0,1.0,0.0);
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

  glEnd();

  // 2.1.1

  // glLoadIdentity();
  //
  // glTranslatef(-1.5f, 0.0f, -6.0f);
  // glBegin(GL_TRIANGLES);
  //   glVertex3f(0.0f, 0.0f, 0.0f);
  //   glVertex3f(1.0f, 0.0f, 0.0f);
  //   glVertex3f(0.0f, 1.0f, 0.0f);
  // glEnd();
  //
  // glLoadIdentity();
  // glRotatef(45, 0.0f, 0.0f, 1.0f);
  // glTranslatef(0.0f, 0.0f, -6.0f);
  // glBegin(GL_TRIANGLES);
  //   glVertex3f(0.0f, 0.0f, 0.0f);
  //   glVertex3f(1.0f, 0.0f, 0.0f);
  //   glVertex3f(0.0f, 1.0f, 0.0f);
  // glEnd();

  // 2.2.1

  // glLoadIdentity();
  //
  // glPushMatrix();
  //   glTranslatef(1.0f, 1.0f, -5.0f);
  //   draw_square();
  // glPopMatrix();
  //
  // glPushMatrix();
  //   glTranslatef(-1.0f, 1.0f, -5.0f);
  //   draw_square();
  // glPopMatrix();

  // 2.2.2 - The squares rotate around their center

  // glLoadIdentity();
  //
  // glPushMatrix();
  // glTranslatef(1.0f, 1.0f, -5.0f);
  // glRotatef(angle, 0.0f, 0.0f, 1.0f);
  // draw_square();
  // glPopMatrix();
  //
  // glPushMatrix();
  // glTranslatef(-1.0f, 1.0f, -5.0f);
  // glRotatef(angle, 0.0f, 0.0f, 1.0f);
  // draw_square();
  // glPopMatrix();


  // 2.2.3 - The squares rotate around the origin

  glLoadIdentity();

  glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 1.0f, -5.0f);
    draw_square();
  glPopMatrix();

  glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0f, 1.0f, -5.0f);
    draw_square();
  glPopMatrix();


  // 2.2.4

  // GLfloat myIdentityMatrix[16] = 	{
  // 		1.0,0.0,0.0,0.0,
  // 		0.0,1.0,0.0,0.0,
  // 		0.0,0.0,1.0,0.0,
  // 		0.0,0.0,0.0,1.0
  // 	};
  // glMatrixMode(GL_MODELVIEW); // Applies subsequent matrix operations to the modelview matrix stack.
  // glLoadMatrixf(myIdentityMatrix); // Replace the current matrix with the specified matrix
  // MyMatrix matrix = getGLModelviewMatrix();

  // myIdentityMatrix.glMultMatrixf(draw_square());



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

    case 114:
      draw();
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
