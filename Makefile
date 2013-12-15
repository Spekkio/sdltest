target: sdltest

OPTS=-g -pedantic -Wall -Wextra -Werror
OBJS=obj/mainloop.o obj/gl.o obj/genobject.o obj/ode.o
LINK=`pkg-config --libs sdl` `pkg-config --libs ode` -lGL -lGLU 
#-lX11 -lpng
CFLAGS=`pkg-config --cflags sdl` `pkg-config --cflags ode`
NEED=defines.h

sdltest: main.c $(NEED) $(OBJS)
	gcc $(OPTS) $(CFLAGS) main.c -o sdltest $(OBJS) $(LINK)

obj/mainloop.o: mainloop.c mainloop.h $(NEED)
	mkdir -p obj/
	gcc $(OPTS) $(CFLAGS) -c mainloop.c
	mv mainloop.o obj/

obj/gl.o: gl.c gl.h $(NEED)
	mkdir -p obj/
	gcc $(OPTS) $(CFLAGS) -c gl.c
	mv gl.o obj/

obj/genobject.o: genobject.c genobject.h $(NEED)
	mkdir -p obj/
	gcc $(OPTS) -c genobject.c
	mv genobject.o obj/

obj/ode.o: ode.c ode.h $(NEED)
	mkdir -p obj/
	gcc $(OPTS) `pkg-config --cflags ode` -c ode.c
	mv ode.o obj/

clean:
	rm -rf *~ sdltest *.o obj/ \#*\#
