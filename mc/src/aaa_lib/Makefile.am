### ##########################################################################
### MC = < Manifold Code >
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
### rcsid="$Id: Makefile.am,v 1.38 2010/08/12 05:18:13 fetk Exp $"
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

BASE_LIBS = ../base/libbase.la
BAM_LIBS  = ../bam/libbam.la
WHB_LIBS  = ../whb/libwhb.la
APRX_LIBS = ../aprx/libaprx.la
GEM_LIBS  = ../gem/libgem.la
MCSH_LIBS = ../mcsh/libmcsh.la
NAM_LIBS  = ../nam/libnam.la
DYN_LIBS  = ../dyn/libdyn.la
PDE_LIBS  = ../pde/libpde.la

libdir = ${prefix}/lib
lib_LTLIBRARIES = libmc.la

libmc_la_SOURCES = 
libmc_la_LIBADD  = ${BASE_LIBS} ${BAM_LIBS} ${WHB_LIBS} ${APRX_LIBS} ${GEM_LIBS} ${MCSH_LIBS} ${NAM_LIBS} ${DYN_LIBS} ${PDE_LIBS}
libmc_la_LDFLAGS = -version-info ${FETK_VERSION}

