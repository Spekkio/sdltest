#include <GL/gl.h>
#include <GL/glu.h>
#include <ode/ode.h>

#include "defines.h"

#include "genobject.h"
#include "ode.h"
#include "mainloop.h"

GLuint sphere, tfloor;

float xd, yd;
float x_position;
float y_position;

void resetCam()
{
  glLoadIdentity();
  glRotatef(yd, 1.0, 0.0, 0.0);
  glRotatef(xd, 0.0, 1.0, 0.0);
  glTranslatef(0.0, 0.0,-10.0);
  glTranslatef(0.0,-5.0-(jump*2.0),0.0);
  glTranslatef(x_position, 0.0, y_position);
}

void display(void)
{

  if(mousex!=0 || mousey!=0) {
    xd-=mousex*MOUSEX_SPEED;
    yd-=mousey*MOUSEY_SPEED; /*not inverted, + for inverted*/
    mousex=0;
    mousey=0;
  }
  if(forward) {
    y_position+=forward*cos((xd/360.0)*2.0*3.14)*WALK_SPEED; /*forward*/
    x_position-=forward*sin((xd/360.0)*2.0*3.14)*WALK_SPEED; /*strafe*/
  }
  if(strafe) {
    y_position+=strafe*cos(((xd+90.0)/360.0)*2.0*3.14)*WALK_SPEED;
    x_position-=strafe*sin(((xd+90.0)/360.0)*2.0*3.14)*WALK_SPEED;
  }
  /*
  printf ("xd: %.4f, yd: %.4f, fw: %.4f, st: %.4f\n",xd,yd,y_position,x_position);
  */

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*Reset Camera*/
  resetCam();
  /*Rotate, move and display object*/
  glODEMultMatrixd(pos,R1);
  glCallList(sphere);

  /*Reset Camera*/
  resetCam();
  /*Rotate, move and display object*/
  glODEMultMatrixd(pos2,R2);
  glCallList(sphere);

  /*Reset Camera*/
  resetCam();
  /*Rotate, move and display object*/
  glCallList(tfloor);

}

void initGL(void)
{
  float aspect_ratio;

  x_position=y_position=0.0;
  yd=xd=0.0;

  /*Settings*/
  glShadeModel(GL_SMOOTH);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  /*Clear screen*/
  glClearColor(0.0, 0.0, 0.0, 1.0);
  /*
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);  
  */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  aspect_ratio = 800.0f/600.0f;
  gluPerspective(70.0, aspect_ratio, 1.0, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /*Generate a Sphere*/
  sphere = glGenLists(1);
  glNewList(sphere, GL_COMPILE);
  makeSphere(RADIUS);
  glEndList();

  /*Generate the floor*/
  tfloor = glGenLists(1);
  glNewList(tfloor, GL_COMPILE);
  makeFloor(2.0);
  glEndList();

}
