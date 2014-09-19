# additional include paths necessary to compile the C library
AM_CFLAGS = -I$(top_srcdir)/include @AM_CFLAGS@

###############################################################################
# THE LIBRARIES TO BUILD
###############################################################################

include_HEADERS = matrix2svg_types.h

# the library names to build (note we are building static libs only)
lib_LIBRARIES = libm2s.a

# where to install the headers on the system
libm2s_adir = $(includedir)/m2s

# the list of header files that belong to the library (to be installed later)
libm2s_a_HEADERS =	\
			../../include/matrix2svg_data.h \
			../../include/matrix2svg_heap.h \
			../../include/matrix2svg_print.h \
			../../include/matrix2svg_types.h 

# the sources to add to the library and to add to the source distribution
libm2s_a_SOURCES =	\
			$(libm2s_a_HEADERS) \
			matrix2svg_data.c \
			matrix2svg_heap.c \
			matrix2svg_print.c \
			matrix2svg_types.c  

CLEANFILES = $(top_srcdir)/include/matrix2svg_types.h
EXTRA_DIST = matrix2svg_types.h.in
HDR = $(top_srcdir)/include/matrix2svg_types.h.in
BUILT_SOURCES = matrix2svg_types.h
matrix2svg_types.h: ${HDR}
	sed -e "s/X.YY/$$(echo @VERSION@)/" < ${HDR} > $(top_srcdir)/include/$@
###############################################################################
