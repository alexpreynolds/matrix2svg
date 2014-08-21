# initial information about the project
AC_INIT([m2s],[1.0],[alexpreynolds@gmail.com])

# check if the source folder is correct
AC_CONFIG_SRCDIR([src/bin/matrix2svg.c])

# automake initialisation (mandatory) and check for minimal automake API version 1.9
AM_INIT_AUTOMAKE([1.9])

# Checks for programs

OLD_CFLAGS=$CFLAGS
# check for C compiler and the library compiler
AC_PROG_CC
AC_PROG_RANLIB
CFLAGS=$OLD_CFLAGS

# use the C++ compiler for the following checks
AC_LANG([C])

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdlib.h string.h stdint.h float.h math.h getopt.h errno.h])
AC_CHECK_LIB(m, log)
AC_CHECK_LIB(m, sqrt)

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# distribute additional compiler and linker flags
#DEBUGFLAGS="-DDEBUG=1"
COMMONFLAGS="-D__STDC_CONSTANT_MACROS -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE=1"
AC_MSG_CHECKING([whether to build with debug information])
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
        [enable debug data generation (def=no)])],
    [debugit="$enableval"],
    [debugit=no])
AC_MSG_RESULT([$debugit])
if test x"$debugit" = x"yes"; then
    AC_DEFINE([DEBUG],[],[Debug Mode])
    AM_CFLAGS="$AM_CFLAGS -g -Wall -Wextra -pedantic -std=c99 -Werror -Wno-uninitialized -O0 $DEBUGFLAGS $COMMONFLAGS"
else
    AC_DEFINE([NDEBUG],[],[No-debug Mode])
    AM_CFLAGS="$AM_CFLAGS -Wall -Wextra -pedantic -std=c99 -O3 $COMMONFLAGS"
fi

# --> set these variables instead of CFLAGS or LDFLAGS
AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_LDFLAGS])

# files to generate via autotools (.am or .in source files)
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/m2s/Makefile])
AC_CONFIG_FILES([src/bin/Makefile])

# generate the final Makefile etc.
AC_OUTPUT
