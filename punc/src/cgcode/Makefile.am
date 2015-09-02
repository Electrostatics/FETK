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
### rcsid="$Id: Makefile.am,v 1.8 2010/08/12 05:52:22 fetk Exp $"
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
THISLIB = cgcode

noinst_LTLIBRARIES = libcgcode.la

SSRCLIB = scgdrv.c scg.c scr.c scrind.c spcg.c scgnr.c scgne.c spcgnr.c spcgne.c sppcg.c spcgca.c sdpchb.c scbfix.c sckchb.c scgchk.c sonest.c msstop.c
SAUXLIB = r1mach.c sratqr.c

DSRCLIB = dcgdrv.c dcg.c dcr.c dcrind.c dpcg.c dcgnr.c dcgne.c dpcgnr.c dpcgne.c dppcg.c dpcgca.c ddpchb.c dcbfix.c dckchb.c dcgchk.c donest.c mdstop.c
DAUXLIB = d1mach.c dratqr.c depsln.c

libcgcode_la_SOURCES = ${SSRCLIB} ${SAUXLIB} ${DSRCLIB} ${DAUXLIB}
INCLUDES  = @maloc_inc@
AM_CFLAGS = @profile@ @pedantic_ansi@

all-local:
#	-cp -p ${top_srcdir}/src/${THISLIB}/punc/*.h ../aaa_inc/punc/.

