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
### rcsid="$Id: Makefile.am,v 1.3 2010/08/12 05:52:13 fetk Exp $"
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
## Author:  Michael Holst and Stephen Bond
## ###########################################################################

CPPINC = -I@srcdir@ -I@srcdir@/punc

# Preprocess for AMD Library
amd_i_aat.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_aat.c > amd_i_aat.c
amd_i_1.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_1.c > amd_i_1.c
amd_i_2.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_2.c > amd_i_2.c
amd_i_dump.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_dump.c > amd_i_dump.c
amd_i_postorder.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_postorder.c > amd_i_postorder.c
amd_i_post_tree.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_post_tree.c > amd_i_post_tree.c
amd_i_defaults.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_defaults.c > amd_i_defaults.c
amd_i_order.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_order.c > amd_i_order.c
amd_i_control.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_control.c > amd_i_control.c
amd_i_info.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_info.c > amd_i_info.c
amd_i_valid.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_valid.c > amd_i_valid.c
amd_i_preprocess.c:
	$(CPP) ${CPPINC} -DDINT @srcdir@/amd_preprocess.c > amd_i_preprocess.c
amd_l_aat.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_aat.c > amd_l_aat.c
amd_l_1.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_1.c > amd_l_1.c
amd_l_2.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_2.c > amd_l_2.c
amd_l_dump.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_dump.c > amd_l_dump.c
amd_l_postorder.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_postorder.c > amd_l_postorder.c
amd_l_post_tree.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_post_tree.c > amd_l_post_tree.c
amd_l_defaults.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_defaults.c > amd_l_defaults.c
amd_l_order.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_order.c > amd_l_order.c
amd_l_control.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_control.c > amd_l_control.c
amd_l_info.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_info.c > amd_l_info.c
amd_l_valid.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_valid.c > amd_l_valid.c
amd_l_preprocess.c:
	$(CPP) ${CPPINC} -DDLONG @srcdir@/amd_preprocess.c > amd_l_preprocess.c

AMD_I = amd_i_aat.c amd_i_1.c amd_i_2.c amd_i_dump.c \
      amd_i_postorder.c amd_i_post_tree.c amd_i_defaults.c amd_i_order.c \
      amd_i_control.c amd_i_info.c amd_i_valid.c amd_i_preprocess.c
AMD_L = amd_l_aat.c amd_l_1.c amd_l_2.c amd_l_dump.c \
      amd_l_postorder.c amd_l_post_tree.c amd_l_defaults.c amd_l_order.c \
      amd_l_control.c amd_l_info.c amd_l_valid.c amd_l_preprocess.c

AUTOMAKE_OPTIONS = no-dependencies
SUFFIXES = .y .l .H .h .m .C .cc .c .f .java .o
always_built_SUBDIRS =
SUBDIRS = $(always_built_SUBDIRS) .
THISLIB = amd

noinst_LTLIBRARIES = libamd.la

libamd_la_SOURCES  = ${AMD_I} ${AMD_L} amd_global.c

INCLUDES           = @maloc_inc@
AM_CFLAGS          = @profile@ @pedantic_ansi@

all-local:
	-cp -p ${top_srcdir}/src/${THISLIB}/punc/*.h ../aaa_inc/punc/.

clean-local:
	-rm -f ${AMD_I} ${AMD_L}

