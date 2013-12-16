#include <SDL/SDL.h>
#include <ode/ode.h>

#include "mainloop.h"
#include "gl.h"
#include "ode.h"

const char version[] = "1.0";

char readParams(const int argc, char ** argv)
{
  if(argc>1)
    {
      if(!strncmp(argv[argc-1],"--help",6))
	{
	  printf("\nno help.\n");
	  return 1;
	} else
      if(!strncmp(argv[argc-1],"--version",9))
	{
	  printf("\nversion: %s.\n",version);
	  return 1;
	}
    }
  return 0;
}

int main(int argc, char ** argv)
{
  SDL_Surface *screen;

  if(readParams(argc,argv))
    {
      return 0;
    }

  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
      printf("Error: SDL_Init(SDL_INIT_EVERYTHING) < 0\n");
      return -1;
    }

  screen=SDL_SetVideoMode(800,600,32,SDL_SWSURFACE|SDL_OPENGL);
  if(screen == 0)
    {
      printf("error: SDL_SetVideoMode() == 0\n");
      return -1;
    }

  mousey=mousex=0;

  initODE();

  initGL();

  mainLoop();

  closeODE();

  SDL_Quit();

  return 0;
}
