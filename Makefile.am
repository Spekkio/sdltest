AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror

AM_CPPFLAGS=$(DEPS_CFLAGS)

bin_PROGRAMS = sdltest
sdltest_SOURCES = src/ode.c src/main.c src/mainloop.c src/shaders.c src/genobject.c src/gl.c src/defines.h src/gl.h src/ode.h src/genobject.h src/shaders.h src/mainloop.h

sdltest_LDADD = $(DEPS_LIBS)

dist_noinst_SCRIPTS = autogen.sh