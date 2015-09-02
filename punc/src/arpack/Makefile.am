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
### rcsid="$Id: Makefile.am,v 1.16 2010/08/12 05:52:14 fetk Exp $"
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
THISLIB = arpack

noinst_LTLIBRARIES = libarpack.la

SSRC  = sgetv0.c slaqrb.c sstqrb.c ssortc.c ssortr.c sstatn.c sstats.c snaitr.c snapps.c snaup2.c snaupd.c snconv.c sneigh.c sngets.c ssaitr.c ssapps.c ssaup2.c ssaupd.c ssconv.c sseigt.c ssgets.c sneupd.c sseupd.c ssesrt.c

DSRC  = dgetv0.c dlaqrb.c dstqrb.c dsortc.c dsortr.c dstatn.c dstats.c dnaitr.c dnapps.c dnaup2.c dnaupd.c dnconv.c dneigh.c dngets.c dsaitr.c dsapps.c dsaup2.c dsaupd.c dsconv.c dseigt.c dsgets.c dneupd.c dseupd.c dsesrt.c

CSRC  = cnaitr.c cnapps.c cnaup2.c cnaupd.c cneigh.c cneupd.c cngets.c cgetv0.c csortc.c cstatn.c

ZSRC  = znaitr.c znapps.c znaup2.c znaupd.c zneigh.c zneupd.c zngets.c zgetv0.c zsortc.c zstatn.c

UTIL  = cmout.c cvout.c dmout.c dvout.c icnteq.c icopy.c iset.c iswap.c ivout.c second.c smout.c svout.c zmout.c zvout.c

libarpack_la_SOURCES = ${SSRC} ${DSRC} ${CSRC} ${ZSRC} ${UTIL}
INCLUDES             = @maloc_inc@
AM_CFLAGS            = @profile@ @pedantic_ansi@

all-local:
#	-cp -p ${top_srcdir}/src/${THISLIB}/punc/*.h ../aaa_inc/punc/.

