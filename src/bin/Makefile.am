# this is example-file: src/bin/Makefile.am

# additional include pathes necessary to compile the C++ programs
AM_CFLAGS = -I$(top_srcdir)/include @AM_CFLAGS@

###############################################################################
# THE PROGRAMS TO BUILD
###############################################################################

# the program to build (the names of the final binaries)
bin_PROGRAMS = matrix2svg

# list of sources for the 'helloWorld' binary
matrix2svg_SOURCES =	\
			matrix2svg.c

# the additional libraries needed to link helloWorld
matrix2svg_LDADD = 	$(top_builddir)/src/m2s/libm2s.a $(AM_LDFLAGS)

###############################################################################
