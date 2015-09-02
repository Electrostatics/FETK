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
### rcsid="$Id: Makefile.am,v 1.13 2010/12/02 18:39:26 fetk Exp $"
### ##########################################################################

## ###########################################################################
## File:Makefile.am
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
THISLIB = blas

noinst_LTLIBRARIES = libblas.la

ALLBLAS = lsame.c xerbla.c

SBLAS1  = isamax.c sasum.c saxpy.c scopy.c sdot.c snrm2.c srot.c srotg.c sscal.c sswap.c
DBLAS1  = idamax.c dasum.c daxpy.c dcopy.c ddot.c dnrm2.c drot.c drotg.c dscal.c dswap.c
CBLAS1  = scasum.c scnrm2.c icamax.c caxpy.c ccopy.c cdotc.c cdotu.c csscal.c crotg.c cscal.c cswap.c
ZBLAS1  = dcabs1.c dzasum.c dznrm2.c izamax.c zaxpy.c zcopy.c zdotc.c zdotu.c zdscal.c zrotg.c zscal.c zswap.c
# CB1AUX  = isamax.c sasum.c saxpy.c scopy.c snrm2.c sscal.c
# ZB1AUX  = idamax.c dasum.c daxpy.c dcopy.c dnrm2.c dscal.c

SBLAS2  = sgemv.c sgbmv.c ssymv.c ssbmv.c sspmv.c strmv.c stbmv.c stpmv.c strsv.c stbsv.c stpsv.c sger.c ssyr.c sspr.c ssyr2.c sspr2.c
DBLAS2  = dgemv.c dgbmv.c dsymv.c dsbmv.c dspmv.c dtrmv.c dtbmv.c dtpmv.c dtrsv.c dtbsv.c dtpsv.c dger.c dsyr.c dspr.c dsyr2.c dspr2.c
CBLAS2  = cgemv.c cgbmv.c chemv.c chbmv.c chpmv.c ctrmv.c ctbmv.c ctpmv.c ctrsv.c ctbsv.c ctpsv.c cgerc.c cgeru.c cher.c chpr.c cher2.c chpr2.c
ZBLAS2  = zgemv.c zgbmv.c zhemv.c zhbmv.c zhpmv.c ztrmv.c ztbmv.c ztpmv.c ztrsv.c ztbsv.c ztpsv.c zgerc.c zgeru.c zher.c zhpr.c zher2.c zhpr2.c

SBLAS3  = sgemm.c ssymm.c ssyrk.c ssyr2k.c strmm.c strsm.c 
DBLAS3  = dgemm.c dsymm.c dsyrk.c dsyr2k.c dtrmm.c dtrsm.c
CBLAS3  = cgemm.c csymm.c csyrk.c csyr2k.c ctrmm.c ctrsm.c chemm.c cherk.c cher2k.c
ZBLAS3  = zgemm.c zsymm.c zsyrk.c zsyr2k.c ztrmm.c ztrsm.c zhemm.c zherk.c zher2k.c

EXTRA   = sdsdot.c dsdot.c srotm.c srotmg.c drotm.c drotmg.c csrot.c zdrot.c

libblas_la_SOURCES = ${ALLBLAS} ${SBLAS1} ${DBLAS1} ${CBLAS1} ${ZBLAS1} ${SBLAS2} ${DBLAS2} ${CBLAS2} ${ZBLAS2} ${SBLAS3} ${DBLAS3} ${CBLAS3} ${ZBLAS3} ${EXTRA}
INCLUDES  = @maloc_inc@
AM_CFLAGS = @profile@ @pedantic_ansi@

all-local:
#	-cp -p ${top_srcdir}/src/${THISLIB}/punc/*.h ../aaa_inc/punc/.

