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
### rcsid="$Id: Makefile.am,v 1.12 2010/12/09 20:43:32 fetk Exp $"
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

CCOMPILENOOPT = $(subst -O2, , $(COMPILE))
## LAPACK NO OPTIMIZE
slamch.o: slamch.c
	$(CCOMPILENOOPT) -c @srcdir@/slamch.c
dlamch.o: dlamch.c
	$(CCOMPILENOOPT) -c @srcdir@/dlamch.c
## SuperLU NO OPTIMIZE
superlu_timer.o: superlu_timer.c
	$(CCOMPILENOOPT) -c @srcdir@/superlu_timer.c

AUTOMAKE_OPTIONS = no-dependencies
SUFFIXES = .y .l .H .h .m .C .cc .c .f .java .o
always_built_SUBDIRS =
SUBDIRS = $(always_built_SUBDIRS) .
THISLIB = superlu

noinst_LTLIBRARIES = libsuperlu.la

### LAPACK 
LAAUX   = lsame.c xerbla.c
SLASRC  = slacon.c 
DLASRC  = dlacon.c
CLASRC  = clacon.c scsum1.c icmax1.c
ZLASRC  = zlacon.c dzsum1.c izmax1.c
NOPTSRC = slamch.c dlamch.c

### SuperLU 
ALLAUX = util.c memory.c get_perm_c.c mmd.c sp_coletree.c sp_preorder.c sp_ienv.c relax_snode.c heap_relax_snode.c colamd.c superlu_timer.c

SLUSRC = sgssv.c sgssvx.c ssp_blas2.c ssp_blas3.c sgscon.c slangs.c sgsequ.c slaqgs.c spivotgrowth.c sgsrfs.c sgstrf.c sgstrs.c scopy_to_ucol.c ssnode_dfs.c ssnode_bmod.c spanel_dfs.c spanel_bmod.c sreadhb.c scolumn_dfs.c scolumn_bmod.c spivotL.c spruneL.c smemory.c sutil.c smyblas2.c

DLUSRC = dgssv.c dgssvx.c dsp_blas2.c dsp_blas3.c dgscon.c dlangs.c dgsequ.c dlaqgs.c dpivotgrowth.c dgsrfs.c dgstrf.c dgstrs.c dcopy_to_ucol.c dsnode_dfs.c dsnode_bmod.c dpanel_dfs.c dpanel_bmod.c dreadhb.c dcolumn_dfs.c dcolumn_bmod.c dpivotL.c dpruneL.c dmemory.c dutil.c dmyblas2.c

CLUSRC = scomplex.c cgssv.c cgssvx.c csp_blas2.c csp_blas3.c cgscon.c clangs.c cgsequ.c claqgs.c cpivotgrowth.c cgsrfs.c cgstrf.c cgstrs.c ccopy_to_ucol.c csnode_dfs.c csnode_bmod.c cpanel_dfs.c cpanel_bmod.c creadhb.c ccolumn_dfs.c ccolumn_bmod.c cpivotL.c cpruneL.c cmemory.c cutil.c cmyblas2.c

ZLUSRC = dcomplex.c zgssv.c zgssvx.c zsp_blas2.c zsp_blas3.c zgscon.c zlangs.c zgsequ.c zlaqgs.c zpivotgrowth.c zgsrfs.c zgstrf.c zgstrs.c zcopy_to_ucol.c zsnode_dfs.c zsnode_bmod.c zpanel_dfs.c zpanel_bmod.c zreadhb.c zcolumn_dfs.c zcolumn_bmod.c zpivotL.c zpruneL.c zmemory.c zutil.c zmyblas2.c

libsuperlu_la_SOURCES = ${ALLAUX} ${LAAUX} ${SLUSRC} ${SLASRC} ${DLUSRC} ${DLASRC} ${CLUSRC} ${CLASRC} ${SCLAUX} ${ZLUSRC} ${ZLASRC} ${DZLAUX} ${NOPTSRC}
INCLUDES             = @maloc_inc@
AM_CFLAGS            = @profile@ @pedantic_ansi@

all-local:
	-cp -p ${top_srcdir}/src/${THISLIB}/punc/*.h ../aaa_inc/punc/.

