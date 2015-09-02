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
### rcsid="$Id: Makefile.am,v 1.29 2010/12/09 21:02:07 fetk Exp $"
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

noinst_PROGRAMS  = go goSlu goSmooth
go_SOURCES       = main.c
goSlu_SOURCES    = mainSlu.c
goSmooth_SOURCES = mainSmooth.c
go_LDADD         = @mc_lib@ @punc_lib@ @maloc_lib@ @umfpack_lib@ @amd_lib@ @superlu_lib@ @blas_lib@ @vf2c_lib@ @mpi_lib@ @rl_lib@ @liberty_lib@ @socket_lib@ @nsl_lib@ @thread_lib@ @math_lib@ @zfence_lib@ @profile_lib@
goSlu_LDADD      = @mc_lib@ @punc_lib@ @maloc_lib@ @umfpack_lib@ @amd_lib@ @superlu_lib@ @blas_lib@ @vf2c_lib@ @mpi_lib@ @rl_lib@ @liberty_lib@ @socket_lib@ @nsl_lib@ @thread_lib@ @math_lib@ @zfence_lib@ @profile_lib@
goSmooth_LDADD   = @mc_lib@ @punc_lib@ @maloc_lib@ @umfpack_lib@ @amd_lib@ @superlu_lib@ @blas_lib@ @vf2c_lib@ @mpi_lib@ @rl_lib@ @liberty_lib@ @socket_lib@ @nsl_lib@ @thread_lib@ @math_lib@ @zfence_lib@ @profile_lib@
INCLUDES         = @mc_inc@ @punc_inc@ @maloc_inc@
AM_CFLAGS        = @profile@ @wall_pedantic_ansi@

