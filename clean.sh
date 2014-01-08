#!/bin/bash
rm -rf COPYING INSTALL Makefile.in aclocal.m4 autom4te.cache/ config.h.in configure depcomp install-sh missing Makefile config.h config.log config.status main src/.deps/ src/.dirstamp stamp-h1 *~ \#*\# *.o mdate-sh texinfo.tex doc/*.info doc/stamp-vti doc/version.texi config.guess config.sub ltmain.sh m4/* compile

find . -regex "^.*\.o$" -delete
find . -regex "^.*~$" -delete
#find . -regex "^.*\.deps$" -delete
#find . -regex "^.*\.dirstamp$" -delete