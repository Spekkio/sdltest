AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
# -I m4
#-std=c99

include aminclude.am

MOSTLYCLEANFILES = $(DX_CLEANFILES)

AM_CFLAGS = -pedantic -Wall -Wextra -Werror

AM_CPPFLAGS=$(DEPS_CFLAGS)

bin_PROGRAMS = sdltest
sdltest_SOURCES = src/ode.c src/main.c src/mainloop.c src/shaders.c src/genobject.c src/gl.c src/defines.h src/gl.h src/ode.h src/genobject.h src/shaders.h src/mainloop.h src/lua.c src/lua.h config.h

sdltest_LDADD = $(DEPS_LIBS)

EXTRA_DIST = autogen.sh $(DX_CONFIG) doc/html
#dist_noinst_SCRIPTS = autogen.sh
