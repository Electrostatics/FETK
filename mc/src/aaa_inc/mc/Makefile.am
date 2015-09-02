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
### rcsid="$Id: Makefile.am,v 1.30 2010/08/12 05:18:12 fetk Exp $"
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

BAM_HEADS    = bam.h   bmat.h bvec.h mat.h mtool.h vec.h vec3.h slu.h
WHB_HEADS    = whb.h
APRX_HEADS   = aprx.h  bnode.h node.h re.h
GEM_HEADS    = gem.h   vel.h ves.h 
MCSH_HEADS   = mcsh.h
NAM_HEADS    = nam.h   am.h
DYN_HEADS    = dyn.h
PDE_HEADS    = pde.h

MC_HEADS     = mc.h mc_base.h
OTHER_HEADS  = ${BAM_HEADS} ${WHB_HEADS} ${APRX_HEADS} ${GEM_HEADS} ${MCSH_HEADS} ${NAM_HEADS} ${DYN_HEADS} ${PDE_HEADS}

includedir = ${prefix}/include/mc
include_HEADERS = ${MC_HEADS} ${OTHER_HEADS}

distclean-local: clean-local

clean-local:
	-rm -f ${OTHER_HEADS}

