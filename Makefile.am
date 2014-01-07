AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS=$(DEPS_CFLAGS)

bin_PROGRAMS = sdltest
sdltest_SOURCES = defines.h genobject.h gl.h mainloop.c ode.c shaders.c genobject.c gl.c main.c mainloop.h ode.h shaders.h

sdltest_LDADD = $(DEPS_LIBS)

dist_noinst_SCRIPTS = autogen.sh