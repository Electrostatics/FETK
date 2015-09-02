### ##########################################################################
### PUNC = < Portable Understructure for Numerical Computing >
### Copyright (C) 1994-- Michael Holst
### 
### This library is free software; you can redistribute it and/or
### modify it under the terms of the GNU Lesser General Public
### License as published by the Free Software Foundation; either
### version 2.1 of the License, or (at your option) any later version.
### 
### This library is distributed in the hope that it will be useful,
### but WITHOUT ANY WARRANTY; without even the implied warranty of
### MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
### Lesser General Public License for more details.
### 
### You should have received a copy of the GNU Lesser General Public
### License along with this library; if not, write to the Free Software
### Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
### 
### rcsid="$Id: Makefile.am,v 1.67 2010/08/12 05:52:12 fetk Exp $"
### ##########################################################################

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
SUFFIXES = .y .l .H .h .m .C .cc .c .f .java .o
always_built_SUBDIRS =
SUBDIRS = $(always_built_SUBDIRS) .

BASE_LIBS  = ../base/libbase.la

VF2C_LIBS  = ../vf2c/libvf2c.la
if BUILD_VF2C
LIBVF2C    = libvf2c.la
else
LIBVF2C    = 
endif

BLAS_LIBS  = ../blas/libblas.la
if BUILD_BLAS
LIBBLAS    = libblas.la
else
LIBBLAS    = 
endif

LAPACK_LIBS  = ../lapack/liblapack.la
if BUILD_LAPACK
LIBLAPACK    = liblapack.la
else
LIBLAPACK    = 
endif

AMD_LIBS = ../amd/libamd.la
if BUILD_AMD
LIBAMD = libamd.la
else
LIBAMD = 
endif

UMFPACK_LIBS = ../umfpack/libumfpack.la
if BUILD_UMFPACK
LIBUMFPACK   = libumfpack.la
else
LIBUMFPACK   = 
endif

SUPERLU_LIBS = ../superlu/libsuperlu.la
if BUILD_SUPERLU
LIBSUPERLU   = libsuperlu.la
else
LIBSUPERLU   = 
endif

ARPACK_LIBS  = ../arpack/libarpack.la
if BUILD_ARPACK
LIBARPACK    = libarpack.la
else
LIBARPACK    = 
endif

CGCODE_LIBS  = ../cgcode/libcgcode.la
if BUILD_CGCODE
LIBCGCODE    = libcgcode.la
else
LIBCGCODE    = 
endif

PMG_LIBS  = ../pmg/libpmg.la
if BUILD_PMG
LIBPMG    = libpmg.la
else
LIBPMG    = 
endif

libdir = ${prefix}/lib
lib_LTLIBRARIES = libpunc.la ${LIBVF2C} ${LIBBLAS} ${LIBLAPACK} ${LIBAMD} ${LIBUMFPACK} ${LIBSUPERLU} ${LIBARPACK} ${LIBCGCODE} ${LIBPMG}

libpunc_la_SOURCES =
libpunc_la_LIBADD  = ${BASE_LIBS}
libpunc_la_LDFLAGS = -version-info ${FETK_VERSION}

libvf2c_la_SOURCES =
libvf2c_la_LIBADD  = ${VF2C_LIBS}
libvf2c_la_LDFLAGS = -version-info ${FETK_VERSION}

libblas_la_SOURCES =
libblas_la_LIBADD  = ${BLAS_LIBS}
libblas_la_LDFLAGS = -version-info ${FETK_VERSION}

liblapack_la_SOURCES =
liblapack_la_LIBADD  = ${LAPACK_LIBS}
liblapack_la_LDFLAGS = -version-info ${FETK_VERSION}

libamd_la_SOURCES =
libamd_la_LIBADD  = ${AMD_LIBS}
libamd_la_LDFLAGS = -version-info ${FETK_VERSION}

libumfpack_la_SOURCES =
libumfpack_la_LIBADD  = ${UMFPACK_LIBS}
libumfpack_la_LDFLAGS = -version-info ${FETK_VERSION}

libsuperlu_la_SOURCES =
libsuperlu_la_LIBADD  = ${SUPERLU_LIBS}
libsuperlu_la_LDFLAGS = -version-info ${FETK_VERSION}

libarpack_la_SOURCES =
libarpack_la_LIBADD  = ${ARPACK_LIBS}
libarpack_la_LDFLAGS = -version-info ${FETK_VERSION}

libcgcode_la_SOURCES =
libcgcode_la_LIBADD  = ${CGCODE_LIBS}
libcgcode_la_LDFLAGS = -version-info ${FETK_VERSION}

libpmg_la_SOURCES =
libpmg_la_LIBADD  = ${PMG_LIBS}
libpmg_la_LDFLAGS = -version-info ${FETK_VERSION}

