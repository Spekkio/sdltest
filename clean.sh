#!/bin/bash
rm -rf COPYING INSTALL Makefile.in aclocal.m4 autom4te.cache/ config.h.in configure depcomp install-sh missing Makefile config.h config.log config.status main src/.deps/ src/.dirstamp stamp-h1 *~ \#*\# *.o mdate-sh texinfo.tex

find . -regex "^.*\.o$" -delete
find . -regex "^.*\.~$" -delete
