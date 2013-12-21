#define FORWARD 1
#define BACK    2
#define LEFT    4
#define RIGHT   8
#define JUMP    16
#define MOUSE   32

#define MOVTIME 1

void mainLoop(void);

extern int mousex;
extern int mousey;
extern int move_flags;
extern int ticks_flags;
