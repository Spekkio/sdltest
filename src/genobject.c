/*! \file genobject.c */

#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void makeFloor(const float size)
{
  const float alpha = 0.3;
  const float num = 100.0;
  float ix, iy;

  srand(10);

  iy=-num;
  ix=-num;
  glBegin(GL_QUADS);
  while(iy<num) {
    while(ix<num) {

      glColor4f((float)(rand())/RAND_MAX, (float)(rand())/RAND_MAX, (float)(rand())/RAND_MAX ,alpha);
      glVertex3f(size*ix, 0.0, size*iy);

      glColor4f((float)(rand())/RAND_MAX, (float)(rand())/RAND_MAX, (float)(rand())/RAND_MAX ,alpha);
      glVertex3f( size+size*ix, 0.0, size*iy);

      glColor4f((float)(rand())/RAND_MAX, (float)(rand())/RAND_MAX, (float)(rand())/RAND_MAX ,alpha);
      glVertex3f( size+size*ix, 0.0, size+size*iy);

      glColor4f((float)(rand())/RAND_MAX, (float)(rand())/RAND_MAX, (float)(rand())/RAND_MAX ,alpha);
      glVertex3f(size*ix, 0.0, size+size*iy);

      ix+=1.0;
    }
    ix=-num;
    iy+=1.0;
  }
  glEnd();

}

void makeSphere(const double rad)
{
  const float it = 100.0;
  float i,a;

  glBegin(GL_QUADS);

  for(a=0;a<it;a+=1.0)
  for(i=0;i<it;i+=1.0)
    {
      glColor3f(sin(a/(it*3))*2*M_PI,0.5,sin((i/(it/10))*2*M_PI));

      glVertex3f(rad*sin((a/(it*2))*2*M_PI)*cos(((i)/it)*2*M_PI)      , rad*sin((a/(it*2))*2*M_PI)*sin(((i)/it)*2*M_PI)      , rad*cos((a/(it*2))*2*M_PI));
      glVertex3f(rad*sin((a/(it*2))*2*M_PI)*cos(((i+1)/it)*2*M_PI)    , rad*sin((a/(it*2))*2*M_PI)*sin(((i+1)/it)*2*M_PI)    , rad*cos((a/(it*2))*2*M_PI));
      glVertex3f(rad*sin(((a+1)/(it*2))*2*M_PI)*cos(((i+1)/it)*2*M_PI), rad*sin(((a+1)/(it*2))*2*M_PI)*sin(((i+1)/it)*2*M_PI), rad*cos(((a+1)/(it*2))*2*M_PI));
      glVertex3f(rad*sin(((a+1)/(it*2))*2*M_PI)*cos(((i)/it)*2*M_PI)  , rad*sin(((a+1)/(it*2))*2*M_PI)*sin(((i)/it)*2*M_PI)  , rad*cos(((a+1)/(it*2))*2*M_PI));
    }

  glEnd();
}

void makeCube(const float size)
{
  glBegin(GL_QUADS);

  glColor3f(0.7, 0.0, 0.2);
  glTexCoord2f(0.0, 0.0); glVertex3f(-size, -size, -size);
  glTexCoord2f(1.0, 0.0); glVertex3f( size, -size, -size);
  glTexCoord2f(1.0, 1.0); glVertex3f( size,  size, -size);
  glTexCoord2f(0.0, 1.0); glVertex3f(-size,  size, -size);

  glColor3f(0.7, 0.0, 0.6);
  glTexCoord2f(0.0, 0.0); glVertex3f(-size, -size,  size);
  glTexCoord2f(1.0, 0.0); glVertex3f( size, -size,  size);
  glTexCoord2f(1.0, 1.0); glVertex3f( size,  size,  size);
  glTexCoord2f(0.0, 1.0); glVertex3f(-size,  size,  size);

  glColor3f(0.7, 0.23, 0.2);
  glTexCoord2f(0.0, 0.0); glVertex3f(-size, -size, -size);
  glTexCoord2f(1.0, 0.0); glVertex3f(-size, -size,  size);
  glTexCoord2f(1.0, 1.0); glVertex3f(-size,  size,  size);
  glTexCoord2f(0.0, 1.0); glVertex3f(-size,  size, -size);

  glColor3f(0.1, 0.4, 0.2);
  glTexCoord2f(0.0, 0.0); glVertex3f( size, -size, -size);
  glTexCoord2f(1.0, 0.0); glVertex3f( size, -size,  size);
  glTexCoord2f(1.0, 1.0); glVertex3f( size,  size,  size);
  glTexCoord2f(0.0, 1.0); glVertex3f( size,  size, -size);
 
  glColor3f(0.7, 0.5, 1.0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-size, -size, -size);
  glTexCoord2f(1.0, 0.0); glVertex3f(-size, -size,  size);
  glTexCoord2f(1.0, 1.0); glVertex3f( size, -size,  size);
  glTexCoord2f(0.0, 1.0); glVertex3f( size, -size, -size);
  
  glColor3f(0.1, 0.0, 0.2);
  glTexCoord2f(0.0, 0.0); glVertex3f(-size, size, -size);
  glTexCoord2f(1.0, 0.0); glVertex3f(-size, size,  size);
  glTexCoord2f(1.0, 1.0); glVertex3f( size, size,  size);
  glTexCoord2f(0.0, 1.0); glVertex3f( size, size, -size);

  glEnd();
}

