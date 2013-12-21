#include <GL/glew.h>
/*#include <GL/gl.h>*/
#include <GL/glu.h>
#include <ode/ode.h>

#include "defines.h"

#include "genobject.h"
#include "ode.h"
#include "mainloop.h"
#include "shaders.h"

const char * oglVersion;

GLuint sphere, tfloor;

float xd, yd;
float x_position;
float y_position;

typedef struct vec3{
  float x;
  float y;
  float z;
}vec3;

struct vec3 vtest[3];

GLuint VBO;

void resetCam()
{
  glLoadIdentity();
  glRotatef(yd, 1.0, 0.0, 0.0);
  glRotatef(xd, 0.0, 1.0, 0.0);
  glTranslatef(0.0, 0.0,-10.0);
  
  if(move_flags&JUMP) {
    glTranslatef(0.0,-5.0-(2.0),0.0);
  } else glTranslatef(0.0,-5.0,0.0);
  
  glTranslatef(x_position, 0.0, y_position);
}

void display(void)
{
  float speed;

  speed=1.0;

  /*do some movement calculations, based on what buttons are pressed down*/

  if(mousex!=0 || mousey!=0) {
    xd-=mousex*MOUSEX_SPEED;
    yd-=mousey*MOUSEY_SPEED; /*not inverted, + for inverted*/
    mousex=0;
    mousey=0;
  }
  /*xor, didn't work*/
  /*if((((move_flags&FORWARD)) ^ ((move_flags&BACK))) & 1) {*/

  if(move_flags&FORWARD)  {
    y_position+=cos((xd/360.0)*2.0*3.14)*WALK_SPEED; /*forward*/
    x_position-=sin((xd/360.0)*2.0*3.14)*WALK_SPEED; /*strafe*/
  }
  if(move_flags&BACK) {
    y_position+=-cos((xd/360.0)*2.0*3.14)*WALK_SPEED; /*forward*/
    x_position-=-sin((xd/360.0)*2.0*3.14)*WALK_SPEED; /*strafe*/
  }
  
  /*xor, didn't work*/
  /*if((((move_flags&LEFT)) ^ ((move_flags&RIGHT))) & 1) {*/

  if(move_flags&RIGHT) {

    if((move_flags&FORWARD) || (move_flags&BACK)) {
      speed=0.5; /*if moving diagonal*/
    }

    y_position+=speed*cos(((xd+90.0)/360.0)*2.0*3.14)*WALK_SPEED;
    x_position-=speed*sin(((xd+90.0)/360.0)*2.0*3.14)*WALK_SPEED;
  }
  if(move_flags&LEFT) {

    if((move_flags&FORWARD) || (move_flags&BACK)) {
      speed=0.5; /*if moving diagonal*/
    }

    y_position+=-speed*cos(((xd+90.0)/360.0)*2.0*3.14)*WALK_SPEED;
    x_position-=-speed*sin(((xd+90.0)/360.0)*2.0*3.14)*WALK_SPEED;
  }

  /*
  printf ("xv: %.4f, yv: %.4f, xpos: %.4f, ypos: %.4f\n",xd,yd,x_position,y_position);
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

void getGLVersion()
{
  /*const GLubyte* sGLVersion;*/
  oglVersion =  (char*)glGetString(GL_VERSION);
  printf("OpenGL Version %s\n",oglVersion);
}

int addShader(const GLuint ShaderProgram, const char * pShaderSource, const GLenum ShaderType)
{
  GLuint ShaderObj;
  const GLchar* p[1];
  GLint length[1];
  GLint success;
  GLchar infolog[1024];

  ShaderObj = glCreateShader(ShaderType);

  if(ShaderObj==0)
    {
      printf("Error: glCreateShader() == 0");
      return -1;
    }

  p[0] = pShaderSource;
  length[0]=strlen(pShaderSource);

  glShaderSource(ShaderObj, 1, p, length);
  glCompileShader(ShaderObj);
  glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
  if(!success)
    {
      glGetShaderInfoLog(ShaderObj, 1024, NULL, infolog);
      printf("Error glCompileShader(): %s\n",infolog);
      return -1;
    }

  glAttachShader(ShaderProgram, ShaderObj);
 
  return 0;
}

int compileShaders()
{
  GLuint shaderProgram;
  GLint success;
  GLchar infolog[1024];

  shaderProgram = glCreateProgram();

  if(shaderProgram == 0)
    {
      printf("Error: glCreateProgram() == 0");
      return -1;
    }

  if(addShader(shaderProgram, pVS, GL_VERTEX_SHADER) < 0)
    {
      printf("Error: addShader(shaderProgram, pVS, GL_VERTEX_SHADER)\n");
      return -1;
    }
  if(addShader(shaderProgram, pFS, GL_FRAGMENT_SHADER) < 0)
    {
      printf("Error: addShader(shaderProgram, pFS, GL_FRAGMENT_SHADER)\n");
      return -1;
    }
  
  success = 0;

  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if(success == 0)
    {
      glGetProgramInfoLog(shaderProgram, sizeof(infolog), NULL, infolog);
      printf("Error glLinkProgram(): %s\n",infolog);
      return -1;
    }

  success = 0;

  glValidateProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
  if(success == 0)
    {
      glGetProgramInfoLog(shaderProgram, sizeof(infolog), NULL, infolog);
      printf("Error glValidateProgram(): %s\n",infolog);
      return -1;
    }

  glUseProgram(shaderProgram);

  return 0;

}

int initGL(void)
{
  float aspect_ratio;
  GLenum res;

  x_position=y_position=0.0;
  yd=xd=0.0;

  /*Init GLEW*/
  res = glewInit();
  if(res != GLEW_OK)
    {
      printf("Error: glewInit() '%s'\n",glewGetErrorString(res));
      return -1;
    }

  /*Print Version string*/
  getGLVersion();
  /*
  compileShaders();
  */ 
  

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

  /*VBO Test*/
  vtest[0].x = 0.1;
  vtest[0].y = 0.2;
  vtest[0].z = 0.3;

  vtest[1].x = 0.1;
  vtest[1].y = 0.2;
  vtest[1].z = 0.3;

  vtest[2].x = 0.1;
  vtest[2].y = 0.2;
  vtest[2].z = 0.3;

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vtest), vtest, GL_STATIC_DRAW);

  return 0;
}
