#include <SDL/SDL.h>
#include <ode/ode.h>
#include <config.h>

#include "mainloop.h"
#include "gl.h"
#include "ode.h"

const char version[] = "1.0";

char readParams(const int argc, char ** argv)
{
  if(argc>1)
    {
#ifdef HAVE_PRINTF
      if(!strncmp(argv[argc-1],"--help",6))
	{
	  printf("\n\t--version\tdisplay version.\n");
	  printf("\t--help   \tdisplay this help.\n");
	  printf("\t--about  \tabout this program.\n");
	  printf("\n");
	  return 1;
	} else
      if(!strncmp(argv[argc-1],"--version",9))
	{
	  printf("\n%s.\n",PACKAGE_STRING);
	  printf("\n");
	  return 1;
	} else
      if(!strncmp(argv[argc-1],"--about",7))
	{
	  printf("\nA simple program for testing some OpenGL in SDL\n");
	  printf("\nReport bugs to: %s.\n",PACKAGE_BUGREPORT);
	  printf("Package URL: %s\n",PACKAGE_URL);
	  printf("Also see http://www.spekkio.se/ for my Public PGP key.\n");
	  printf("\n");
	  return 1;
	}
#endif
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
