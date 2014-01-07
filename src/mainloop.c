#include <SDL/SDL.h>
#include <ode/ode.h>

#include "defines.h"
#include "gl.h"
#include "ode.h"
#include "mainloop.h"

int mousex,mousey,forward,strafe;
int jump;

int move_flags;
int ticks_flags;

void mainLoop(void)
{
  SDL_Event event;
  Uint32 start;
  Uint32 ticks,gticks,frames,count;
  int running=1;
  float FPS,collect;

  ticks=0;
  frames=0;
  start=0;
  collect=0;

  ticks_flags=0;
  move_flags=0;

  while(running)
    {
      gticks= SDL_GetTicks();
      ticks = gticks-start;
      start = gticks;
      count+= ticks;

      if(count>1000.0)
	{
	  FPS=(frames)/*/(count/1000.0)*/;
	  FPS=FPS;
	  count=0;
	  frames=0;
	}

      while(SDL_PollEvent(&event))
	{
	  switch(event.type)
	    {

	    case SDL_QUIT:
	      running=0;
	      break;

	    case SDL_MOUSEMOTION:
	      /*
	      printf("%i %i %i\n",event.motion.x,event.motion.xrel,event.motion.yrel);
	      */
	      mousex = event.motion.xrel;
	      mousey = event.motion.yrel;
	      SDL_WarpMouse(400, 300);
	      move_flags|=MOUSE;
	      break;

	    case SDL_KEYDOWN:
	      switch(event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
		  running=0;
		  break;

		case SDLK_SPACE:
		  move_flags|=JUMP;
		  break;

		case SDLK_w:
		  move_flags|=FORWARD;
		  break;
		case SDLK_s:
		  move_flags|=BACK;
		  break;

		case SDLK_d:
		  move_flags|=RIGHT;
		  break;
		case SDLK_a:
		  move_flags|=LEFT;
		  break;

		default:break;
		}
	      break;

	    case SDL_KEYUP:
	      switch(event.key.keysym.sym)
		{
		case SDLK_SPACE:
		  move_flags&=0xFFFFFFFF^(JUMP);
		  break;
		case SDLK_s:
		  move_flags&=0xFFFFFFFF^(BACK);
		  break;
		case SDLK_w:
		  move_flags&=0xFFFFFFFF^(FORWARD);
		  break;
		case SDLK_a:
		  move_flags&=0xFFFFFFFF^(LEFT);
		  break;
		case SDLK_d:
		  move_flags&=0xFFFFFFFF^(RIGHT);
		  break;
		default:break;
		}
	      break;

	    case SDL_ACTIVEEVENT:
	      if(event.active.type==SDL_APPMOUSEFOCUS)
		{
		  if(event.active.gain)
		    {
		      SDL_WM_GrabInput( SDL_GRAB_ON );
		      /*
		      SDL_SetRelativeMouseMode(SDL_TRUE);
		      */
		    }
		}
	      break;

	    default:
	      break;
	    }
	}
      /*printf("%u\n",SDL_GetTicks());*/

      display();
      frames++;

      SDL_GL_SwapBuffers();
      /*
      for(i=0;i<0xFFFFFF;i++)
	{
	  i=i;
	}
      SDL_Delay(1);
      */

      collect+=ticks;
      if(collect>RDELAY) {

	move_calcs();

	simLoop(0,collect/1000.0f);
	collect=0;/*
		    printf("%u %u %f\n",ticks,frames,FPS);*/
      }
    }
}
