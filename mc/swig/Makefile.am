## ###########################################################################
## File:    Makefile.am
##
## Purpose: Automatically generate Makefile.in for autoconf using automake.
##
## Notes:   The final makefile produced by autoconf will use the following:
##
##     COMPILE = $(CC) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
##     LINK = $(CC) $(CFLAGS) $(LDFLAGS) -o $@
##
## Author:  Michael Holst
## ###########################################################################

AUTOMAKE_OPTIONS = no-dependencies
ACLOCAL_AMFLAGS  = -I m4
SUFFIXES = .y .l .H .h .m .C .cc .c .f .java .o
always_built_SUBDIRS =
SUBDIRS = $(always_built_SUBDIRS) .

INCLUDES               = @mc_inc@ @maloc_inc@ 
AM_CFLAGS              = @profile@ @wall_pedantic_ansi@ 

BUILT_SOURCES          = cmc_wrap.cc
SWIG_SOURCES           = mc.i maloc.i am_stripped.i aprx_stripped.i gem_stripped.i mc_typemaps.i pde_stripped.i post.i pre.i vio_stripped.i

pkgpython_PYTHON       = cmc.py ${top_srcdir}/src/__init__.py
pkgpyexec_LTLIBRARIES  = _cmc.la
_cmc_la_SOURCES        = cmc_wrap.cc ${SWIG_SOURCES}
_cmc_la_CPPFLAGS       = ${SWIG_PYTHON_CPPFLAGS} -I. -I${FETK_PYTHON_INCLUDE} -I${FETK_NUMPY_INCLUDE}
_cmc_la_LDFLAGS        = -module
_cmc_la_LIBADD         = @fetk_lib@/libmc.la @fetk_lib@/libpunc.la @fetk_lib@/libmaloc.la @fetk_lib@/libsuperlu.la @fetk_lib@/libumfpack.la @fetk_lib@/libamd.la @fetk_lib@/libblas.la @fetk_lib@/libvf2c.la

cmc_wrap.cc : ${top_srcdir}/src/mc.i
	${SWIG} ${SWIG_PYTHON_OPT} -I. ${maloc_inc} ${mc_inc} -o cmc_wrap.cc -oh cmc_wrap.h ${top_srcdir}/src/mc.i

clean-local :
	rm -f cmc.py cmc_wrap.cc

