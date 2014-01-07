AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS=$(DEPS_CFLAGS)

bin_PROGRAMS = sdltest
sdltest_SOURCES = src/defines.h src/genobject.h src/gl.h src/mainloop.c src/ode.c src/shaders.c src/genobject.c src/gl.c src/main.c src/mainloop.h src/ode.h src/shaders.h

sdltest_LDADD = $(DEPS_LIBS)

dist_noinst_SCRIPTS = autogen.sh