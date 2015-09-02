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
### rcsid="$Id: Makefile.am,v 1.66 2010/12/08 09:24:31 fetk Exp $"
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

if BUILD_VF2C
VF2C_HEADS   = vf2c.h   vblas.h vlapack.h varpack.h vcgcode.h vpmg.h
else
VF2C_HEADS   = 
endif

if BUILD_BLAS
BLAS_HEADS   = 
else
BLAS_HEADS   = 
endif

if BUILD_LAPACK
LAPACK_HEADS   = 
else
LAPACK_HEADS   = 
endif

if BUILD_AMD
AMD_HEADS = amd.h UFconfig.h
else
AMD_HEADS = 
endif

if BUILD_UMFPACK
UMFPACK_HEADS  = vumfpack.h umfpack.h umfpack_col_to_triplet.h umfpack_defaults.h umfpack_free_numeric.h umfpack_free_symbolic.h umfpack_get_determinant.h umfpack_get_lunz.h umfpack_get_numeric.h umfpack_get_symbolic.h umfpack_global.h umfpack_load_numeric.h umfpack_load_symbolic.h umfpack_numeric.h umfpack_qsymbolic.h umfpack_report_control.h umfpack_report_info.h umfpack_report_matrix.h umfpack_report_numeric.h umfpack_report_perm.h umfpack_report_status.h umfpack_report_symbolic.h umfpack_report_triplet.h umfpack_report_vector.h umfpack_save_numeric.h umfpack_save_symbolic.h umfpack_scale.h umfpack_solve.h umfpack_symbolic.h umfpack_tictoc.h umfpack_timer.h umfpack_transpose.h umfpack_triplet_to_col.h umfpack_wsolve.h
else
UMFPACK_HEADS  = 
endif

if BUILD_SUPERLU
SUPERLU_HEADS   = vsuperlu.h colamd.h slu_cdefs.h slu_scomplex.h slu_zdefs.h slu_dcomplex.h slu_sdefs.h supermatrix.h slu_Cnames.h slu_ddefs.h slu_util.h
else
SUPERLU_HEADS   = 
endif

if BUILD_ARPACK
ARPACK_HEADS   = 
else
ARPACK_HEADS   = 
endif

if BUILD_CGCODE
CGCODE_HEADS   = 
else
CGCODE_HEADS   = 
endif

if BUILD_PMG
PMG_HEADS   = 
else
PMG_HEADS   = 
endif

PUNC_HEADS = punc.h punc_base.h
OTHER_HEADS  = ${VF2C_HEADS} ${BLAS_HEADS} ${LAPACK_HEADS} ${AMD_HEADS} ${UMFPACK_HEADS} ${SUPERLU_HEADS} ${ARPACK_HEADS} ${CGCODE_HEADS} ${PMG_HEADS}

includedir = ${prefix}/include/punc
include_HEADERS = ${PUNC_HEADS} ${OTHER_HEADS}

distclean-local: clean-local

clean-local:
	-rm -f ${OTHER_HEADS}

