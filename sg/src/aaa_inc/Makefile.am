### ##########################################################################
### SG = < Socket Graphics >
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
### rcsid="$Id: Makefile.am,v 1.8 2010/08/12 04:56:10 fetk Exp $"
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
always_built_SUBDIRS = sg GL
SUBDIRS = $(always_built_SUBDIRS) .

