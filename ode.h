void simLoop(int pause, dReal step);
void initODE(void);
void closeODE(void);
void glODEMultMatrixd(const dReal pos[3], const dReal R[12]);

extern dReal *pos,*pos2, *R1, *R2;
extern dBodyID *bodies;
