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
### rcsid="$Id: Makefile,v 1.12 2010/12/08 16:43:01 fetk Exp $"
### ##########################################################################

## ###########################################################################
## File:    Makefile.simple
##
## Purpose: Simple makefile for building FEtk tools without using autoconf.
##
## Notes:   Edit as needed and then invoke via "make -f Makefile.simple"
##
## Author:  Michael Holst
## ###########################################################################

ARCH     = x86_64-apple-darwin10.5.0
#ARCH    = x86_64-unknown-linux-gnu

include ../../../build/${ARCH}/fetk-env

DMAL     =
#DMAL    = -ldmalloc

SYSLIB   = -L/usr/X11R6/lib -L/sw/lib -lreadline -lncurses -lm ${DMAL}
#SYSLIB  = -L/usr/lib64 -lreadline -lncurses -lm ${DMAL}

FETK_INC  = -I${FETK_INCLUDE}
FETK_LIB  = -L${FETK_LIBRARY} -lmc -lpunc -lmaloc -lsuperlu -lumfpack -lamd ${DMAL}
#FETK_LIB = -L${FETK_LIBRARY} -lmc -lpunc -lmaloc -ltriangle -ltetgen -lcgcode -larpack -lsuperlu -lumfpack -lamd -llapack -lblas -lvf2c ${DMAL}

default : mcsh

main.o : main.c
	gcc -c -g -O2 -I. ${FETK_INC} main.c

mypde.o : mypde.c
	gcc -c -g -O2 -I. ${FETK_INC} mypde.c

myelm.o : myelm.c
	gcc -c -g -O2 -I. ${FETK_INC} myelm.c

mcsh : main.o mypde.o myelm.o
	gcc -g -O2 -o mcsh main.o mypde.o myelm.o ${FETK_LIB} ${SYSLIB}

setdmal :
	dmalloc -l logfile -i 100 high

clean :
	-rm -f *.o mcsh io.mc hist.mcsh logfile .gdb_history

