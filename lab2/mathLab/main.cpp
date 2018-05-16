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
using namespace std;

#include "stdlib.h"

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation

int piece = 0;
int frames = 0;


class Piece {
  float xPan, yPan, angle, goalX, goalY, goalAngle;
public:
  void setGoal (float, float, float);
  void setPos (float, float, float);
  // Piece(int, int, int);
  float getGoalX(){
    return goalX;
  }
  float getGoalY(){
    return goalY;
  }
  float getGoalAngle(){
    return goalAngle;
  }
  float getX(){
    return xPan;
  }
  float getY(){
    return yPan;
  }
  float getAngle(){
    return angle;
  }
};

void Piece::setPos(float new_xPan, float new_yPan, float new_angle){
  xPan += new_xPan;
  yPan += new_yPan;
  angle += new_angle;
}

void Piece::setGoal(float new_goalX, float new_goalY, float new_goalAngle){
  goalX = new_goalX;
  goalY = new_goalY;
  goalAngle = new_goalAngle;
}

Piece piece1;
Piece piece2;

Piece pieces[] = {piece1, piece2};
// piece1.setPos(1.0f, 1.0f, 1.0f);

void draw_square (void)
{
  // a simple function to draw a square with the current markers
  // orientation and position on screen

  glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, 0.0);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.5, 0.5, 0.0);
  glEnd();

  // std::cout << "Square created " + '\n';
}

// void rotateCClock(void){
//   angle += 5.0;
// }

// void rotateClock(void){
//   angle -= 5.0;
// }
//
// void translateLeft(void){
//   panHor -= 0.2;
// }
//
// void translateRight(void){
//   panHor += 0.2;
// }
//
// void translateUp(void){
//   panVer += 0.2;
// }
//
// void translateDown(void){
//   panVer -= 0.2;
// }

//our main routine
int main(int argc, char *argv[])
{

  // piece1.setPos(-1.0f, 0.0f, 0.0f);
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

  //request a window size of 800 x 800
  glutInitWindowSize(800,800);
  glutReshapeWindow(800,800);

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
  frames += 1;


  // std::cout << piece1.getX(); + '\n';
  // angle += 5.0;
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
    // glDisable(GL_LINE_STIPPLE);
    // glLineWidth(2.0);
  	// glColor3f(1.0,1.0,0.0);
  	// glColor3f(0.0,1.0,0.0);
    // DrawVector(p1,v1);

    //draw a red horizontal line, one unit long
    glLineWidth(1.0);
    glColor3f(0.5,0.5,0.5);
    glPushMatrix();
  	   glTranslatef(-9.55, -9.55, 0.0);
  	  glBegin(GL_LINES);
  		glVertex2f(0.0,0.0);
  		glVertex2f(12.0,0.0);
  	  glEnd();
    glPopMatrix();

    //draw a green vertical line, one unit high
    glLineWidth(1.0);
    glColor3f(0.5,0.5,0.5);
    glPushMatrix();
    glTranslatef(-9.55, -9.55, 0.0);
  	  glBegin(GL_LINES);
  		glVertex2f(0.0,0.0);
  		glVertex2f(0.0,12.0);
  	  glEnd();
    glPopMatrix();




    //draw a white point at the origin
    // glPointSize(2.0);
    // glColor3f(1.0,1.0,1.0);
    // glPushMatrix();
  	//   glTranslatef(0.0, 0.0, 0.0);
  	//   glBegin(GL_POINTS);
  	// 	glVertex2f(0.0,0.0);
  	//   glEnd();
    // glPopMatrix();

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

  // 2.2.2


  if (frames == 1) {
    pieces[0].setPos(1.0f, 1.0f, 0.0f);
    pieces[0].setGoal(-1.0f, 1.0f, 0.0f);

    pieces[1].setPos(-1.0f, 1.0f, 0.0f);
  }

// for (int iteration = 0; iteration < pieces.length(); ++iteration){
//
// }
  if (round(pieces[0].getX()*100)/100 == round(pieces[0].getGoalX()*100)/100){
    std::cout << pieces[0].getX();
    // pieces[0] = 0;
  }

  // std::cout << piece1.getAngle(); + '\n';

  glLoadIdentity();

  glPushMatrix();
    glRotatef(pieces[0].getAngle(), 0.0f, 0.0f, 1.0f);
    glTranslatef(pieces[0].getX(), pieces[0].getY(), -5.0f);
    draw_square();
  glPopMatrix();

  glPushMatrix();
    glRotatef(pieces[1].getAngle(), 0.0f, 0.0f, 1.0f);
    glTranslatef(pieces[1].getX(), pieces[1].getY(), -5.0f);
    draw_square();
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

    case 113: //Q - rotate counter-clockwise
      // angle += 5.0;
      // rotateCClock();
      // piece1.setPos(0.0f, 0.0f, 5.0f);
      pieces[piece].setPos(0.0f, 0.0f, 5.0f);
      // std::cout << piece1.getAngle(); + '\n';
      // std::cout << pieces[piece].getAngle(); + '\n';
      draw();
      break;

    case 101: //E - rotate clockwise
      // angle -= 5.0;
      // rotateClock();
      pieces[piece].setPos(0.0f, 0.0f, -5.0f);
      draw();
      break;

    case 119: //W - translate up
      // panVer += 0.2;
      // translateUp();
      pieces[piece].setPos(0.0f, 0.2f, 0.0f);
      draw();
      break;

    case 97: //A - translate left
      // panHor -= 0.2;
      // translateLeft();
      pieces[piece].setPos(-0.2f, 0.0f, 0.0f);
      draw();
      break;

    case 115: //S - translate down
      // panVer -= 0.2;
      // translateDown();
      pieces[piece].setPos(0.0f, -0.2f, 0.0f);
      draw();
      break;

    case 100: //D - translate right
      // panHor += 0.2;
      // translateRight();
      pieces[piece].setPos(0.2f, 0.0f, 0.0f);
      draw();
      break;

    case 120: //X - next piece
      piece += 1;
      if (piece == 2){
        piece = 0;
      }
      draw();
      break;

    case 122: //Z- last piece
      piece -=1;
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
