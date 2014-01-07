#include <ode/ode.h>
#include <GL/gl.h>

#include "defines.h"

static dWorldID world;
static dSpaceID space;
static dBodyID body, body2;
static dGeomID geom, geom2;

static dMass m;
static dJointGroupID contactgroup;

const dReal *pos,*pos2, *R1, *R2;
static dGeomID box1, box2, box3, box4;

void glODEMultMatrixd(const dReal pos[3], const dReal R[12])
{
  GLdouble matrix[16];
  matrix[0]=R[0];
  matrix[1]=R[4];
  matrix[2]=R[8];
  matrix[3]=0;
  matrix[4]=R[1];
  matrix[5]=R[5];
  matrix[6]=R[9];
  matrix[7]=0;
  matrix[8]=R[2];
  matrix[9]=R[6];
  matrix[10]=R[10];
  matrix[11]=0;
  matrix[12]=pos[0];
  matrix[13]=pos[1];
  matrix[14]=pos[2];
  matrix[15]=1;
  /*glPushMatrix();*/
  glMultMatrixd (matrix);
}

static void nearCallback(void *data, dGeomID o1, dGeomID o2)
{
  dBodyID b1 = dGeomGetBody(o1);
  dBodyID b2 = dGeomGetBody(o2);
  dContact contact;
  int numc;

  data=data;

  contact.surface.mode = dContactBounce | dContactSoftCFM | dContactApprox1;
  /* friction parameter */
  contact.surface.mu = 9000.0;
  /* bounce is the amount of "bouncyness".*/
  contact.surface.bounce = 0.9;
  /*bounce_vel is the minimum incoming velocity to cause a bounce*/
  contact.surface.bounce_vel = 0.5;
  /*constraint force mixing parameter*/
  contact.surface.soft_cfm = 0.001;  

  numc = dCollide (o1,o2,1,&contact.geom,sizeof(dContact));

  if (numc) {
    dJointID c = dJointCreateContact (world,contactgroup,&contact);
    dJointAttach (c,b1,b2);
  }
}

void simLoop(int pause, dReal step)
{
  /*static double time=0.0;*/
  pause=pause;
  dSpaceCollide(space,0,&nearCallback);
  dWorldStep(world,step);
  dJointGroupEmpty(contactgroup);

  dBodyGetPosition(body);
  dBodyGetRotation(body);
  dBodyGetPosition(body2);
  dBodyGetRotation(body2);

  /*
  printf("%.10f %.10f %.10f %.10f %.10f %.10f %.10f %.10f %.10f %.10f\n",0.0,
	 pos[0], pos[1], pos[2],R1[0],R1[1],R1[2],
	 pos2[0], pos2[1], pos2[2]);
  */
  /*
  time+=0.01;
  */
}

void initODE(void)
{
  dInitODE();

  /*World*/
  world = dWorldCreate();
  space = dHashSpaceCreate (0);
  dWorldSetGravity (world,0,-9.82,0); /*Gravity is on Y*/
  dWorldSetCFM (world,1e-5);

  dCreatePlane(space,0,1,0,0); /*plane is on X and Z -*/

  /*Delimiters, invisible boxes*/
  box1 = dCreateBox(space, 100, 100, 1);
  dGeomSetPosition(box1,0.0,0.0,-5.0);
  box2 = dCreateBox(space, 100, 100, 1);
  dGeomSetPosition(box2,0.0,0.0,5.0);
  box3 = dCreateBox(space, 1, 100, 3.0);
  dGeomSetPosition(box3,5.0,0.0,0.0);
  box4 = dCreateBox(space, 1, 100, 3.0);
  dGeomSetPosition(box4,-5.0,0.0,0.0);

  contactgroup = dJointGroupCreate (0);

  body = dBodyCreate (world);
  body2 = dBodyCreate (world);

  geom = dCreateSphere (space,RADIUS);
  geom2 = dCreateSphere (space,RADIUS);

  /*set mass obj*/
  dMassSetSphere (&m,1.0,0.1);

  dBodySetMass (body,&m);
  dBodySetMass (body2,&m);

  dGeomSetBody (geom,body);
  dGeomSetBody (geom2,body2);
  
  /*set initial pos*/
  dBodySetPosition (body ,0   , 3, 0);
  dBodySetPosition (body2,0.01, 10, 0.01);

  pos = dBodyGetPosition(body);
  R1  = dBodyGetRotation(body);
  pos2 = dBodyGetPosition(body2);
  R2  = dBodyGetRotation(body2);
}

void closeODE(void)
{
  /*clean up*/
  dJointGroupDestroy (contactgroup);
  dSpaceDestroy (space);
  dWorldDestroy (world);
  dCloseODE();
}
