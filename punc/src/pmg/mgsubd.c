/* ./src_f77/mgsubd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__2 = 2;
static integer c__9 = 9;
static integer c__1 = 1;
static integer c_n1 = -1;
static doublereal c_b75 = 0.;
static integer c__3 = 3;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    mgsubd.f */
/* * @author  Michael Holst */
/* * @brief   Supporting routines for CS and FAS multigrid algorithms. */
/* * @version $Id: mgsubd.c,v 1.3 2010/08/12 05:45:23 fetk Exp $ */
/* * @attention */
/* * @verbatim */
/* * */
/* * PMG -- Parallel algebraic MultiGrid */
/* * Copyright (C) 1994-- Michael Holst. */
/* * */
/* * Michael Holst <mholst@math.ucsd.edu> */
/* * University of California, San Diego */
/* * Department of Mathematics, 5739 AP&M */
/* * 9500 Gilman Drive, Dept. 0112 */
/* * La Jolla, CA 92093-0112 USA */
/* * http://math.ucsd.edu/~mholst */
/* * */
/* * This file is part of PMG. */
/* * */
/* * PMG is free software; you can redistribute it and/or modify */
/* * it under the terms of the GNU General Public License as published by */
/* * the Free Software Foundation; either version 2 of the License, or */
/* * (at your option) any later version. */
/* * */
/* * PMG is distributed in the hope that it will be useful, */
/* * but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* * GNU General Public License for more details. */
/* * */
/* * You should have received a copy of the GNU General Public License */
/* * along with PMG; if not, write to the Free Software */
/* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA */
/* * */
/* * Linking PMG statically or dynamically with other modules is making a */
/* * combined work based on PMG. Thus, the terms and conditions of the GNU */
/* * General Public License cover the whole combination. */
/* * */
/* * SPECIAL GPL EXCEPTION */
/* * In addition, as a special exception, the copyright holders of PMG */
/* * give you permission to combine the PMG program with free software */
/* * programs and libraries that are released under the GNU LGPL or with */
/* * code included in releases of ISIM, PMV, PyMOL, SMOL, VMD, and Vision. */
/* * Such combined software may be linked with PMG and redistributed together */
/* * in original or modified form as mere aggregation without requirement that */
/* * the entire work be under the scope of the GNU General Public License. */
/* * This special exception permission is also extended to any software listed */
/* * in the SPECIAL GPL EXCEPTION clauses by the FEtk and APBS libraries. */
/* * */
/* * Note that people who make modified versions of PMG are not obligated */
/* * to grant this special exception for their modified versions; it is */
/* * their choice whether to do so. The GNU General Public License gives */
/* * permission to release a modified version without this exception; this */
/* * exception also makes it possible to release a modified version which */
/* * carries forward this exception. */
/* * */
/* * @endverbatim */
/* * /////////////////////////////////////////////////////////////////////////// */
integer maxlev_(integer *n1, integer *n2, integer *n3)
{
    /* System generated locals */
    integer ret_val, i__1;

    /* Builtin functions */
    integer pow_ii(integer *, integer *);

    /* Local variables */
    static integer n1c, n2c, n3c, lev, iden, idone;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    find maximum multigrid possible coarsenning common to three grid */
/* *    sizes:  n1,n2,n3. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** fine the common level *** */
    idone = 0;
    lev = 0;
L10:
    ++lev;
    i__1 = lev - 1;
    iden = pow_ii(&c__2, &i__1);
    n1c = (*n1 - 1) / iden + 1;
    n2c = (*n2 - 1) / iden + 1;
    n3c = (*n3 - 1) / iden + 1;
    if ((n1c - 1) * iden != *n1 - 1 || n1c <= 2) {
	idone = 1;
    }
    if ((n2c - 1) * iden != *n2 - 1 || n2c <= 2) {
	idone = 1;
    }
    if ((n3c - 1) * iden != *n3 - 1 || n3c <= 2) {
	idone = 1;
    }
    if (idone != 1) {
	goto L10;
    }
    ret_val = lev - 1;
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* maxlev_ */

/* Subroutine */ int mkcors_(integer *numlev, integer *nxold, integer *nyold, 
	integer *nzold, integer *nxnew, integer *nynew, integer *nznew)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    extern /* Subroutine */ int corsr_(integer *, integer *);
    static integer nxtmp, nytmp, nztmp;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the number of grid points in the coarser grid, given the */
/* *    number of grid points in a finger grid in each direction. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** determine the coarser grid *** */
    *nxnew = *nxold;
    *nynew = *nyold;
    *nznew = *nzold;
    i__1 = *numlev;
    for (i__ = 1; i__ <= i__1; ++i__) {
	nxtmp = *nxnew;
	nytmp = *nynew;
	nztmp = *nznew;
	corsr_(&nxtmp, nxnew);
	corsr_(&nytmp, nynew);
	corsr_(&nztmp, nznew);
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* mkcors_ */

/* Subroutine */ int corsr_(integer *nold, integer *nnew)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Fortran I/O blocks */
    static cilist io___11 = { 0, 6, 0, 0, 0 };
    static cilist io___12 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the number of grid points in the coarser grid, given the */
/* *    number of grid points in a finer grid. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** find the coarser grid size *** */
    *nnew = (*nold - 1) / 2 + 1;
/* * */
/* *    *** check a few things *** */
    if (*nnew - 1 << 1 != *nold - 1) {
	s_wsle(&io___11);
	do_lio(&c__9, &c__1, "% CORSR:  may not corsen grid this far... ", (
		ftnlen)42);
	e_wsle();
    }
    if (*nnew < 1) {
	s_wsle(&io___12);
	do_lio(&c__9, &c__1, "% CORSR:  have corsenned grid below zero... ", (
		ftnlen)44);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* corsr_ */

/* Subroutine */ int mkfine_(integer *numlev, integer *nxold, integer *nyold, 
	integer *nzold, integer *nxnew, integer *nynew, integer *nznew)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    extern /* Subroutine */ int finer_(integer *, integer *);
    static integer nxtmp, nytmp, nztmp;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the number of grid points in the finer grid, given the */
/* *    number of grid points in a coarser grid in each direction. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** determine the finer grid *** */
    *nxnew = *nxold;
    *nynew = *nyold;
    *nznew = *nzold;
    i__1 = *numlev;
    for (i__ = 1; i__ <= i__1; ++i__) {
	nxtmp = *nxnew;
	nytmp = *nynew;
	nztmp = *nznew;
	finer_(&nxtmp, nxnew);
	finer_(&nytmp, nynew);
	finer_(&nztmp, nznew);
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* mkfine_ */

/* Subroutine */ int finer_(integer *nold, integer *nnew)
{
/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the number of grid points in the finer grid, given the */
/* *    number of grid points in a coarser grid. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** find the finer grid size *** */
    *nnew = (*nold - 1 << 1) + 1;
/* * */
/* *    *** return and end *** */
    return 0;
} /* finer_ */

integer ivariv_(integer *nu, integer *level)
{
    /* System generated locals */
    integer ret_val;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    this routine defines the number of smoothings for a particular */
/* *    level in a variable-v-cycle method. */
/* * */
/* *    possible definitions: */
/* *       ivariv = nu * 2**(level - 1) */
/* *       ivariv = nu * level */
/* *       ivariv = nu + (level - 1) */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* * ** *** variable V-cycle *** */
/* * ** ivariv = nu * 2**(level - 1) */
/* * */
/* * ** *** standard V-cycle *** */
    ret_val = *nu;
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* ivariv_ */

/* Subroutine */ int prtini_(integer *istop)
{
    /* Format strings */
    static char fmt_100[] = "(\002% \002,a12,1x,a12,3x,a12,3x,a12)";

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void), s_wsfe(cilist *), do_fio(integer *, char *, ftnlen),
	     e_wsfe(void);

    /* Local variables */
    static char str0a[20], str1a[20], str2a[20], str3a[20], str0b[20], str1b[
	    20], str2b[20], str3b[20], str0c[20], str1c[20], str2c[20], str3c[
	    20];

    /* Fortran I/O blocks */
    static cilist io___23 = { 0, 6, 0, 0, 0 };
    static cilist io___30 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___31 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___32 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___33 = { 0, 6, 0, fmt_100, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    this routine prints out some info and such from inside multigrid. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** do some i/o *** */
    s_copy(str0a, "iteration  ", (ftnlen)20, (ftnlen)11);
    s_copy(str0b, "count      ", (ftnlen)20, (ftnlen)11);
    s_copy(str0c, "---------  ", (ftnlen)20, (ftnlen)11);
    if (*istop == 0) {
	s_copy(str1a, "absol resid", (ftnlen)20, (ftnlen)11);
	s_copy(str1b, "discr(1-nm)", (ftnlen)20, (ftnlen)11);
	s_copy(str1c, "-----------", (ftnlen)20, (ftnlen)11);
    } else if (*istop == 1) {
	s_copy(str1a, "relat resid", (ftnlen)20, (ftnlen)11);
	s_copy(str1b, "discr(1-nm)", (ftnlen)20, (ftnlen)11);
	s_copy(str1c, "-----------", (ftnlen)20, (ftnlen)11);
    } else if (*istop == 2) {
	s_copy(str1a, "rms change ", (ftnlen)20, (ftnlen)11);
	s_copy(str1b, "discr(1-nm)", (ftnlen)20, (ftnlen)11);
	s_copy(str1c, "---------- ", (ftnlen)20, (ftnlen)11);
    } else if (*istop == 3) {
	s_copy(str1a, "relat error", (ftnlen)20, (ftnlen)11);
	s_copy(str1b, "conti(2-nm)", (ftnlen)20, (ftnlen)11);
	s_copy(str1c, "-----------", (ftnlen)20, (ftnlen)11);
    } else if (*istop == 4) {
	s_copy(str1a, "relat error", (ftnlen)20, (ftnlen)11);
	s_copy(str1b, "discr(2-nm)", (ftnlen)20, (ftnlen)11);
	s_copy(str1c, "-----------", (ftnlen)20, (ftnlen)11);
    } else if (*istop == 5) {
	s_copy(str1a, "relat error", (ftnlen)20, (ftnlen)11);
	s_copy(str1b, "discr(A-nm)", (ftnlen)20, (ftnlen)11);
	s_copy(str1c, "-----------", (ftnlen)20, (ftnlen)11);
    } else {
	s_wsle(&io___23);
	do_lio(&c__9, &c__1, "% PRTINI: bad istop value... ", (ftnlen)29);
	e_wsle();
    }
    s_copy(str2a, "contraction", (ftnlen)20, (ftnlen)11);
    s_copy(str2b, "number     ", (ftnlen)20, (ftnlen)11);
    s_copy(str2c, "-----------", (ftnlen)20, (ftnlen)11);
    s_copy(str3a, "wall ", (ftnlen)20, (ftnlen)5);
    s_copy(str3b, "clock", (ftnlen)20, (ftnlen)5);
    s_copy(str3c, "-----", (ftnlen)20, (ftnlen)5);
    s_wsfe(&io___30);
    do_fio(&c__1, str0c, (ftnlen)20);
    do_fio(&c__1, str1c, (ftnlen)20);
    do_fio(&c__1, str2c, (ftnlen)20);
    do_fio(&c__1, str3c, (ftnlen)20);
    e_wsfe();
    s_wsfe(&io___31);
    do_fio(&c__1, str0a, (ftnlen)20);
    do_fio(&c__1, str1a, (ftnlen)20);
    do_fio(&c__1, str2a, (ftnlen)20);
    do_fio(&c__1, str3a, (ftnlen)20);
    e_wsfe();
    s_wsfe(&io___32);
    do_fio(&c__1, str0b, (ftnlen)20);
    do_fio(&c__1, str1b, (ftnlen)20);
    do_fio(&c__1, str2b, (ftnlen)20);
    do_fio(&c__1, str3b, (ftnlen)20);
    e_wsfe();
    s_wsfe(&io___33);
    do_fio(&c__1, str0c, (ftnlen)20);
    do_fio(&c__1, str1c, (ftnlen)20);
    do_fio(&c__1, str2c, (ftnlen)20);
    do_fio(&c__1, str3c, (ftnlen)20);
    e_wsfe();
/* * */
/* *    *** format statements *** */
/* * */
/* *    *** return and end *** */
    return 0;
} /* prtini_ */

/* Subroutine */ int prtstp_(integer *iok, integer *iters, doublereal *rsnrm, 
	doublereal *rsden, doublereal *orsnrm)
{
    /* Format strings */
    static char fmt_100[] = "(2x,i5,8x,1pe11.5,4x,1pe11.5,4x,1pe8.2,20x,\002"
	    "%%%\002)";
    static char fmt_110[] = "(\002% \002,i5,8x,1pe11.5,4x,1pe11.5,4x,1pe8.2)";

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void), s_wsfe(cilist *), do_fio(integer *, char *, ftnlen),
	     e_wsfe(void);

    /* Local variables */
    static doublereal bf, oh;
    extern /* Subroutine */ int tstop_(doublereal *, doublereal *, doublereal 
	    *);
    static doublereal relres, cputme;
    extern /* Subroutine */ int tstart_(doublereal *, doublereal *);
    static doublereal contrac;

    /* Fortran I/O blocks */
    static cilist io___34 = { 0, 6, 0, 0, 0 };
    static cilist io___38 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___39 = { 0, 6, 0, fmt_110, 0 };
    static cilist io___41 = { 0, 6, 0, 0, 0 };
    static cilist io___43 = { 0, 6, 0, 0, 0 };
    static cilist io___44 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___45 = { 0, 6, 0, fmt_110, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    this routine prints out some info and such from inside multigrid. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** initializing timer *** */
    if (*iters == -99) {
	s_wsle(&io___34);
	do_lio(&c__9, &c__1, "% PRTSTP: initializing timer...", (ftnlen)31);
	e_wsle();
	tstart_(&bf, &oh);
	cputme = 0.;
	goto L99;
/* * */
/* *    *** setup for the iteration *** */
    } else if (*iters == -1) {
	tstop_(&bf, &oh, &cputme);
	if (*iok == 1) {
	    s_wsfe(&io___38);
	    do_fio(&c__1, (char *)&c_n1, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&c_b75, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&c_b75, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cputme, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	} else if (*iok == 2) {
	    s_wsfe(&io___39);
	    do_fio(&c__1, (char *)&c_n1, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&c_b75, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&c_b75, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cputme, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	goto L99;
/* * */
/* *    *** during the iteration *** */
    } else {
/* * */
/* *       *** stop the timer *** */
	tstop_(&bf, &oh, &cputme);
/* * */
/* *       *** relative residual *** */
	if (*rsden == 0.) {
	    relres = 1e6f;
	    s_wsle(&io___41);
	    do_lio(&c__9, &c__1, "% PRTSTP: avoided division by zero", (
		    ftnlen)34);
	    e_wsle();
	} else {
	    relres = *rsnrm / *rsden;
	}
/* * */
/* *       *** contraction number *** */
	if (*orsnrm == 0.) {
	    contrac = 1e6f;
	    s_wsle(&io___43);
	    do_lio(&c__9, &c__1, "% PRTSTP: avoided division by zero", (
		    ftnlen)34);
	    e_wsle();
	} else {
	    contrac = *rsnrm / *orsnrm;
	}
/* * */
/* *       *** the i/o *** */
	if (*iok == 1) {
	    s_wsfe(&io___44);
	    do_fio(&c__1, (char *)&(*iters), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&relres, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&contrac, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cputme, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	} else if (*iok == 2) {
	    s_wsfe(&io___45);
	    do_fio(&c__1, (char *)&(*iters), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&relres, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&contrac, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cputme, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }
/* * */
/* *    *** format statements *** */
/* * */
/* *    *** return and end *** */
L99:
    return 0;
} /* prtstp_ */

/* Subroutine */ int buildstr_(integer *nx, integer *ny, integer *nz, integer 
	*nlev, integer *iz)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer n, lev, nxold, nyold, nzold, nxnew, nynew, nznew;
    extern /* Subroutine */ int mkcors_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    build the nested operator framework in the array iz */
/* * */
/* *    note: iz(50,i) indexes into the gridfcn arrays */
/* *       for each level i=(1,...,nlev+1) as follows: */
/* * */
/* *          fun(i)    = fun (iz(1,i)) */
/* *          bndx(i)   = bndx(iz(2,i)) */
/* *          bndy(i)   = bndy(iz(3,i)) */
/* *          bndz(i)   = bndz(iz(4,i)) */
/* *          ipc(i)    = ipc(iz(5,i)) */
/* *          rpc(i)    = rpc(iz(6,i)) */
/* *          oper(i)   = oper(iz(7,i)) */
/* *          grdx(i)   = brdx(iz(8,i)) */
/* *          grdy(i)   = brdy(iz(9,i)) */
/* *          grdz(i)   = brdz(iz(10,i)) */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** setup *** */
    /* Parameter adjustments */
    iz -= 51;

    /* Function Body */
    nxnew = *nx;
    nynew = *ny;
    nznew = *nz;
    n = nxnew * nynew * nznew;
/* * */
/* *    *** start with level 1 *** */
    lev = 1;
/* * */
/* *    *** mark beginning of everything at level 1 *** */
    iz[lev * 50 + 1] = 1;
    iz[lev * 50 + 2] = 1;
    iz[lev * 50 + 3] = 1;
    iz[lev * 50 + 4] = 1;
    iz[lev * 50 + 5] = 1;
    iz[lev * 50 + 6] = 1;
    iz[lev * 50 + 7] = 1;
    iz[lev * 50 + 8] = 1;
    iz[lev * 50 + 9] = 1;
    iz[lev * 50 + 10] = 1;
    iz[lev * 50 + 11] = 1;
/* * */
/* *    *** mark beginning of everything at level 2 *** */
    iz[(lev + 1) * 50 + 1] = iz[lev * 50 + 1] + n;
    iz[(lev + 1) * 50 + 2] = iz[lev * 50 + 2] + (nynew << 2) * nznew;
    iz[(lev + 1) * 50 + 3] = iz[lev * 50 + 3] + (nxnew << 2) * nznew;
    iz[(lev + 1) * 50 + 4] = iz[lev * 50 + 4] + (nxnew << 2) * nynew;
    iz[(lev + 1) * 50 + 5] = iz[lev * 50 + 5] + 100;
    iz[(lev + 1) * 50 + 6] = iz[lev * 50 + 6] + 100;
    iz[(lev + 1) * 50 + 8] = iz[lev * 50 + 8] + nxnew;
    iz[(lev + 1) * 50 + 9] = iz[lev * 50 + 9] + nynew;
    iz[(lev + 1) * 50 + 10] = iz[lev * 50 + 10] + nznew;
/* * ********************************************************************* */
/* * ***NOTE: we mark operator offsets as we build the operators *** */
/* * ***iz(7,lev+1)  = iz(7,lev)  + 4*n */
/* * ********************************************************************* */
/* * ***NOTE: we mark prolongation operator offsets lagging a level *** */
/* * ***iz(11,lev)   = iz(11,lev-1) + 27*nsmall */
/* * ********************************************************************* */
/* * */
/* *    *** mark the beginning of everything at (nlev-1) more *** */
    i__1 = *nlev;
    for (lev = 2; lev <= i__1; ++lev) {
	nxold = nxnew;
	nyold = nynew;
	nzold = nznew;
	mkcors_(&c__1, &nxold, &nyold, &nzold, &nxnew, &nynew, &nznew);
	n = nxnew * nynew * nznew;
/* * */
/* *       *** mark the beginning of everything at level (lev+1) *** */
	iz[(lev + 1) * 50 + 1] = iz[lev * 50 + 1] + n;
	iz[(lev + 1) * 50 + 2] = iz[lev * 50 + 2] + (nynew << 2) * nznew;
	iz[(lev + 1) * 50 + 3] = iz[lev * 50 + 3] + (nxnew << 2) * nznew;
	iz[(lev + 1) * 50 + 4] = iz[lev * 50 + 4] + (nxnew << 2) * nynew;
	iz[(lev + 1) * 50 + 5] = iz[lev * 50 + 5] + 100;
	iz[(lev + 1) * 50 + 6] = iz[lev * 50 + 6] + 100;
	iz[(lev + 1) * 50 + 7] = iz[lev * 50 + 7] + (n << 2);
	iz[(lev + 1) * 50 + 8] = iz[lev * 50 + 8] + nxnew;
	iz[(lev + 1) * 50 + 9] = iz[lev * 50 + 9] + nynew;
	iz[(lev + 1) * 50 + 10] = iz[lev * 50 + 10] + nznew;
/* *       *** mark prolongation operator storage for previous level *** */
	iz[lev * 50 + 11] = iz[(lev - 1) * 50 + 11] + n * 27;
/* *       *************************************************************** */
/* *       ***NOTE: we mark operator offsets as we build the operators *** */
/* *       *** iz(7,lev+1)  = iz(7,lev)  + 4*n */
/* *       *************************************************************** */
/* L10: */
    }
/* * */
/* *    *** end it *** */
    return 0;
} /* buildstr_ */

/* Subroutine */ int buildops_(integer *nx, integer *ny, integer *nz, integer 
	*nlev, integer *ipkey, integer *iinfo, integer *ido, integer *iz, 
	integer *mgprol, integer *mgcoar, integer *mgsolv, integer *mgdisc, 
	integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, 
	doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, 
	doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, 
	doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf,
	 doublereal *fcf, doublereal *tcf)
{
    /* Format strings */
    static char fmt_100[] = "(a,(2x,\002 [\002,i3,\002,\002,i3,\002,\002,i3"
	    ",\002] \002))";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void),
	     s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int buildband_(integer *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *), buildharm0_(integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), buildcopy0_(integer *, 
	    integer *, integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), buildgaler0_(integer *,
	     integer *, integer *, integer *, integer *, integer *, integer *,
	     integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *);
    static integer lev, key, nxx, nyy, nzz, nxold, nyold, nzold;
    extern /* Subroutine */ int builda_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer numdia;
    extern /* Subroutine */ int buildp_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), extrac_(integer *, integer *, integer *, integer *,
	     integer *, integer *, doublereal *, doublereal *), mkcors_(
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *), prtmatd_(integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___58 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___60 = { 0, 6, 0, 0, 0 };
    static cilist io___64 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___65 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___66 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___67 = { 0, 6, 0, 0, 0 };
    static cilist io___68 = { 0, 6, 0, 0, 0 };
    static cilist io___70 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    build operators, boundary arrays, modify affine vectors. */
/* *    if (ido=0) do only fine level */
/* *    if (ido=1) do only coarse levels (including a second op at coarsest) */
/* *    if (ido=2) do all levels */
/* *    if (ido=3) rebuild the second operator at the coarsest level */
/* * */
/* *    note:  the fine level must be build before any coarse levels. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** setup *** */
    /* Parameter adjustments */
    --tcf;
    --fcf;
    --ccf;
    --a3cf;
    --a2cf;
    --a1cf;
    --gzcf;
    --gycf;
    --gxcf;
    --zf;
    --yf;
    --xf;
    --fc;
    --cc;
    --ac;
    --pc;
    --rpc;
    --ipc;
    iz -= 51;

    /* Function Body */
    nxx = *nx;
    nyy = *ny;
    nzz = *nz;
/* * */
/* *    *** build the operator a on the finest level *** */
    if (*ido == 0 || *ido == 2) {
	lev = 1;
/* * */
/* *       *** some i/o *** */
	if (*iinfo != 0) {
	    s_wsfe(&io___58);
	    do_fio(&c__1, "% BUILDOPS: (FINE) :", (ftnlen)20);
	    do_fio(&c__1, (char *)&nxx, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&nyy, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&nzz, (ftnlen)sizeof(integer));
	    e_wsfe();
	}
/* * */
/* *       *** finest level discretization *** */
	builda_(&nxx, &nyy, &nzz, ipkey, mgdisc, &numdia, &ipc[iz[lev * 50 + 
		5]], &rpc[iz[lev * 50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[
		lev * 50 + 1]], &fc[iz[lev * 50 + 1]], &xf[iz[lev * 50 + 8]], 
		&yf[iz[lev * 50 + 9]], &zf[iz[lev * 50 + 10]], &gxcf[iz[lev * 
		50 + 2]], &gycf[iz[lev * 50 + 3]], &gzcf[iz[lev * 50 + 4]], &
		a1cf[iz[lev * 50 + 1]], &a2cf[iz[lev * 50 + 1]], &a3cf[iz[lev 
		* 50 + 1]], &ccf[iz[lev * 50 + 1]], &fcf[iz[lev * 50 + 1]]);
/* * */
/* *       *** now initialize the differential operator offset *** */
	s_wsle(&io___60);
	do_lio(&c__9, &c__1, "% BUILDOPS: operator stencil (lev,numdia) = ", (
		ftnlen)44);
	do_lio(&c__3, &c__1, (char *)&lev, (ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&numdia, (ftnlen)sizeof(integer));
	e_wsle();
	iz[(lev + 1) * 50 + 7] = iz[lev * 50 + 7] + numdia * nxx * nyy * nzz;
/* * */
/* *       *** debug *** */
	if (*iinfo > 7) {
	    prtmatd_(&nxx, &nyy, &nzz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 
		    50 + 6]], &ac[iz[lev * 50 + 7]]);
	}
    }
/* * */
/* *    *** build the (nlev-1) level operators *** */
    if (*ido == 1 || *ido == 2 || *ido == 3) {
	i__1 = *nlev;
	for (lev = 2; lev <= i__1; ++lev) {
	    nxold = nxx;
	    nyold = nyy;
	    nzold = nzz;
	    mkcors_(&c__1, &nxold, &nyold, &nzold, &nxx, &nyy, &nzz);
	    if (*ido != 3) {
/* * */
/* *             *** build the interpolation operator on this level *** */
		buildp_(&nxold, &nyold, &nzold, &nxx, &nyy, &nzz, mgprol, &
			ipc[iz[(lev - 1) * 50 + 5]], &rpc[iz[(lev - 1) * 50 + 
			6]], &pc[iz[(lev - 1) * 50 + 11]], &ac[iz[(lev - 1) * 
			50 + 7]], &xf[iz[(lev - 1) * 50 + 8]], &yf[iz[(lev - 
			1) * 50 + 9]], &zf[iz[(lev - 1) * 50 + 10]]);
/* * */
/* *             *** differential operator this level with standard disc. *** */
		if (*mgcoar == 0) {
		    if (*iinfo != 0) {
			s_wsfe(&io___64);
			do_fio(&c__1, "% BUILDOPS: (STAND) ", (ftnlen)20);
			do_fio(&c__1, (char *)&nxx, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&nyy, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&nzz, (ftnlen)sizeof(integer));
			e_wsfe();
		    }
		    buildcopy0_(&nxx, &nyy, &nzz, &nxold, &nyold, &nzold, &xf[
			    iz[lev * 50 + 8]], &yf[iz[lev * 50 + 9]], &zf[iz[
			    lev * 50 + 10]], &gxcf[iz[lev * 50 + 2]], &gycf[
			    iz[lev * 50 + 3]], &gzcf[iz[lev * 50 + 4]], &a1cf[
			    iz[lev * 50 + 1]], &a2cf[iz[lev * 50 + 1]], &a3cf[
			    iz[lev * 50 + 1]], &ccf[iz[lev * 50 + 1]], &fcf[
			    iz[lev * 50 + 1]], &tcf[iz[lev * 50 + 1]], &xf[iz[
			    (lev - 1) * 50 + 8]], &yf[iz[(lev - 1) * 50 + 9]],
			     &zf[iz[(lev - 1) * 50 + 10]], &gxcf[iz[(lev - 1) 
			    * 50 + 2]], &gycf[iz[(lev - 1) * 50 + 3]], &gzcf[
			    iz[(lev - 1) * 50 + 4]], &a1cf[iz[(lev - 1) * 50 
			    + 1]], &a2cf[iz[(lev - 1) * 50 + 1]], &a3cf[iz[(
			    lev - 1) * 50 + 1]], &ccf[iz[(lev - 1) * 50 + 1]],
			     &fcf[iz[(lev - 1) * 50 + 1]], &tcf[iz[(lev - 1) *
			     50 + 1]]);
		    builda_(&nxx, &nyy, &nzz, ipkey, mgdisc, &numdia, &ipc[iz[
			    lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &ac[iz[
			    lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev 
			    * 50 + 1]], &xf[iz[lev * 50 + 8]], &yf[iz[lev * 
			    50 + 9]], &zf[iz[lev * 50 + 10]], &gxcf[iz[lev * 
			    50 + 2]], &gycf[iz[lev * 50 + 3]], &gzcf[iz[lev * 
			    50 + 4]], &a1cf[iz[lev * 50 + 1]], &a2cf[iz[lev * 
			    50 + 1]], &a3cf[iz[lev * 50 + 1]], &ccf[iz[lev * 
			    50 + 1]], &fcf[iz[lev * 50 + 1]]);
/* * */
/* *             *** differential operator this level with harmonic disc. *** */
		} else if (*mgcoar == 1) {
		    if (*iinfo != 0) {
			s_wsfe(&io___65);
			do_fio(&c__1, "% BUILDOPS: (HARMO) ", (ftnlen)20);
			do_fio(&c__1, (char *)&nxx, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&nyy, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&nzz, (ftnlen)sizeof(integer));
			e_wsfe();
		    }
		    buildharm0_(&nxx, &nyy, &nzz, &nxold, &nyold, &nzold, &xf[
			    iz[lev * 50 + 8]], &yf[iz[lev * 50 + 9]], &zf[iz[
			    lev * 50 + 10]], &gxcf[iz[lev * 50 + 2]], &gycf[
			    iz[lev * 50 + 3]], &gzcf[iz[lev * 50 + 4]], &a1cf[
			    iz[lev * 50 + 1]], &a2cf[iz[lev * 50 + 1]], &a3cf[
			    iz[lev * 50 + 1]], &ccf[iz[lev * 50 + 1]], &fcf[
			    iz[lev * 50 + 1]], &tcf[iz[lev * 50 + 1]], &xf[iz[
			    (lev - 1) * 50 + 8]], &yf[iz[(lev - 1) * 50 + 9]],
			     &zf[iz[(lev - 1) * 50 + 10]], &gxcf[iz[(lev - 1) 
			    * 50 + 2]], &gycf[iz[(lev - 1) * 50 + 3]], &gzcf[
			    iz[(lev - 1) * 50 + 4]], &a1cf[iz[(lev - 1) * 50 
			    + 1]], &a2cf[iz[(lev - 1) * 50 + 1]], &a3cf[iz[(
			    lev - 1) * 50 + 1]], &ccf[iz[(lev - 1) * 50 + 1]],
			     &fcf[iz[(lev - 1) * 50 + 1]], &tcf[iz[(lev - 1) *
			     50 + 1]]);
		    builda_(&nxx, &nyy, &nzz, ipkey, mgdisc, &numdia, &ipc[iz[
			    lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &ac[iz[
			    lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev 
			    * 50 + 1]], &xf[iz[lev * 50 + 8]], &yf[iz[lev * 
			    50 + 9]], &zf[iz[lev * 50 + 10]], &gxcf[iz[lev * 
			    50 + 2]], &gycf[iz[lev * 50 + 3]], &gzcf[iz[lev * 
			    50 + 4]], &a1cf[iz[lev * 50 + 1]], &a2cf[iz[lev * 
			    50 + 1]], &a3cf[iz[lev * 50 + 1]], &ccf[iz[lev * 
			    50 + 1]], &fcf[iz[lev * 50 + 1]]);
/* * */
/* *             *** differential operator with galerkin formulation *** */
		} else if (*mgcoar == 2) {
		    if (*iinfo != 0) {
			s_wsfe(&io___66);
			do_fio(&c__1, "% BUILDOPS: (GALER) ", (ftnlen)20);
			do_fio(&c__1, (char *)&nxx, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&nyy, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&nzz, (ftnlen)sizeof(integer));
			e_wsfe();
		    }
		    buildgaler0_(&nxold, &nyold, &nzold, &nxx, &nyy, &nzz, 
			    ipkey, &numdia, &pc[iz[(lev - 1) * 50 + 11]], &
			    ipc[iz[(lev - 1) * 50 + 5]], &rpc[iz[(lev - 1) * 
			    50 + 6]], &ac[iz[(lev - 1) * 50 + 7]], &cc[iz[(
			    lev - 1) * 50 + 1]], &fc[iz[(lev - 1) * 50 + 1]], 
			    &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &
			    ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[
			    iz[lev * 50 + 1]]);
		    extrac_(&nxold, &nyold, &nzold, &nxx, &nyy, &nzz, &tcf[iz[
			    (lev - 1) * 50 + 1]], &tcf[iz[lev * 50 + 1]]);
		} else {
		    s_wsle(&io___67);
		    do_lio(&c__9, &c__1, "% BUILDOPS: bad mgcoar key given..."
			    , (ftnlen)35);
		    e_wsle();
		}
/* * */
/* *             *** now initialize the differential operator offset *** */
		s_wsle(&io___68);
		do_lio(&c__9, &c__1, "% BUILDOPS: operator stencil (lev,numd"
			"ia) = ", (ftnlen)44);
		do_lio(&c__3, &c__1, (char *)&lev, (ftnlen)sizeof(integer));
		do_lio(&c__3, &c__1, (char *)&numdia, (ftnlen)sizeof(integer))
			;
		e_wsle();
		iz[(lev + 1) * 50 + 7] = iz[lev * 50 + 7] + numdia * nxx * 
			nyy * nzz;
/* * */
/* *             *** debug *** */
		if (*iinfo > 8) {
		    prtmatd_(&nxx, &nyy, &nzz, &ipc[iz[lev * 50 + 5]], &rpc[
			    iz[lev * 50 + 6]], &ac[iz[lev * 50 + 7]]);
		}
	    }
/* L10: */
	}
/* * */
/* *       *** build a sparse format coarse grid operator *** */
	if (*mgsolv == 1) {
	    lev = *nlev;
	    buildband_(&key, &nxx, &nyy, &nzz, &ipc[iz[lev * 50 + 5]], &rpc[
		    iz[lev * 50 + 6]], &ac[iz[lev * 50 + 7]], &ipc[iz[(lev + 
		    1) * 50 + 5]], &rpc[iz[(lev + 1) * 50 + 6]], &ac[iz[(lev 
		    + 1) * 50 + 7]]);
	    if (key == 1) {
		s_wsle(&io___70);
		do_lio(&c__9, &c__1, "% BUILDOPS: changing your MGSOLV to it"
			"erative...", (ftnlen)48);
		e_wsle();
		*mgsolv = 0;
	    }
	}
    }
/* * */
/* *    *** end it *** */
    return 0;
} /* buildops_ */

/* Subroutine */ int buildcopy0_(integer *nx, integer *ny, integer *nz, 
	integer *nxf, integer *nyf, integer *nzf, doublereal *xc, doublereal *
	yc, doublereal *zc, doublereal *gxc, doublereal *gyc, doublereal *gzc,
	 doublereal *a1c, doublereal *a2c, doublereal *a3c, doublereal *cc, 
	doublereal *fc, doublereal *tc, doublereal *xf, doublereal *yf, 
	doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, 
	doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf,
	 doublereal *fcf, doublereal *tcf)
{
    /* System generated locals */
    integer gxc_dim1, gxc_dim2, gxc_offset, gyc_dim1, gyc_dim2, gyc_offset, 
	    gzc_dim1, gzc_dim2, gzc_offset, a1c_dim1, a1c_dim2, a1c_offset, 
	    a2c_dim1, a2c_dim2, a2c_offset, a3c_dim1, a3c_dim2, a3c_offset, 
	    cc_dim1, cc_dim2, cc_offset, fc_dim1, fc_dim2, fc_offset, tc_dim1,
	     tc_dim2, tc_offset, gxcf_dim1, gxcf_dim2, gxcf_offset, gycf_dim1,
	     gycf_dim2, gycf_offset, gzcf_dim1, gzcf_dim2, gzcf_offset, 
	    a1cf_dim1, a1cf_dim2, a1cf_offset, a2cf_dim1, a2cf_dim2, 
	    a2cf_offset, a3cf_dim1, a3cf_dim2, a3cf_offset, tcf_dim1, 
	    tcf_dim2, tcf_offset, ccf_dim1, ccf_dim2, ccf_offset, fcf_dim1, 
	    fcf_dim2, fcf_offset, i__1, i__2, i__3;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j, k, ii, jj, kk, iadd, jadd, kadd;

    /* Fortran I/O blocks */
    static cilist io___74 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    produce information for a coarser grid. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** how far to step into the coefficient arrays *** */
    /* Parameter adjustments */
    --xc;
    gzc_dim1 = *nx;
    gzc_dim2 = *ny;
    gzc_offset = 1 + gzc_dim1 * (1 + gzc_dim2);
    gzc -= gzc_offset;
    --yc;
    tc_dim1 = *nx;
    tc_dim2 = *ny;
    tc_offset = 1 + tc_dim1 * (1 + tc_dim2);
    tc -= tc_offset;
    fc_dim1 = *nx;
    fc_dim2 = *ny;
    fc_offset = 1 + fc_dim1 * (1 + fc_dim2);
    fc -= fc_offset;
    cc_dim1 = *nx;
    cc_dim2 = *ny;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
    cc -= cc_offset;
    a3c_dim1 = *nx;
    a3c_dim2 = *ny;
    a3c_offset = 1 + a3c_dim1 * (1 + a3c_dim2);
    a3c -= a3c_offset;
    a2c_dim1 = *nx;
    a2c_dim2 = *ny;
    a2c_offset = 1 + a2c_dim1 * (1 + a2c_dim2);
    a2c -= a2c_offset;
    a1c_dim1 = *nx;
    a1c_dim2 = *ny;
    a1c_offset = 1 + a1c_dim1 * (1 + a1c_dim2);
    a1c -= a1c_offset;
    gyc_dim1 = *nx;
    gyc_dim2 = *nz;
    gyc_offset = 1 + gyc_dim1 * (1 + gyc_dim2);
    gyc -= gyc_offset;
    gxc_dim1 = *ny;
    gxc_dim2 = *nz;
    gxc_offset = 1 + gxc_dim1 * (1 + gxc_dim2);
    gxc -= gxc_offset;
    --zc;
    --xf;
    gzcf_dim1 = *nxf;
    gzcf_dim2 = *nyf;
    gzcf_offset = 1 + gzcf_dim1 * (1 + gzcf_dim2);
    gzcf -= gzcf_offset;
    --yf;
    tcf_dim1 = *nxf;
    tcf_dim2 = *nyf;
    tcf_offset = 1 + tcf_dim1 * (1 + tcf_dim2);
    tcf -= tcf_offset;
    fcf_dim1 = *nxf;
    fcf_dim2 = *nyf;
    fcf_offset = 1 + fcf_dim1 * (1 + fcf_dim2);
    fcf -= fcf_offset;
    ccf_dim1 = *nxf;
    ccf_dim2 = *nyf;
    ccf_offset = 1 + ccf_dim1 * (1 + ccf_dim2);
    ccf -= ccf_offset;
    a3cf_dim1 = *nxf;
    a3cf_dim2 = *nyf;
    a3cf_offset = 1 + a3cf_dim1 * (1 + a3cf_dim2);
    a3cf -= a3cf_offset;
    a2cf_dim1 = *nxf;
    a2cf_dim2 = *nyf;
    a2cf_offset = 1 + a2cf_dim1 * (1 + a2cf_dim2);
    a2cf -= a2cf_offset;
    a1cf_dim1 = *nxf;
    a1cf_dim2 = *nyf;
    a1cf_offset = 1 + a1cf_dim1 * (1 + a1cf_dim2);
    a1cf -= a1cf_offset;
    gycf_dim1 = *nxf;
    gycf_dim2 = *nzf;
    gycf_offset = 1 + gycf_dim1 * (1 + gycf_dim2);
    gycf -= gycf_offset;
    gxcf_dim1 = *nyf;
    gxcf_dim2 = *nzf;
    gxcf_offset = 1 + gxcf_dim1 * (1 + gxcf_dim2);
    gxcf -= gxcf_offset;
    --zf;

    /* Function Body */
    iadd = (*nxf - 1) / (*nx - 1);
    jadd = (*nyf - 1) / (*ny - 1);
    kadd = (*nzf - 1) / (*nz - 1);
    if (iadd != 2 || jadd != 2 || kadd != 2) {
	s_wsle(&io___74);
	do_lio(&c__9, &c__1, "% BUILDCOPY0: problem with grid dimensions...", 
		(ftnlen)45);
	e_wsle();
    }
/* * */
/* *    *** compute the coarse grid pde coefficients *** */
/* mdir 3 1 */
    i__1 = *nz;
    for (k = 1; k <= i__1; ++k) {
	kk = (k << 1) - 1;
	zc[k] = zf[kk];
/* mdir 3 2 */
	i__2 = *ny;
	for (j = 1; j <= i__2; ++j) {
	    jj = (j << 1) - 1;
	    yc[j] = yf[jj];
/* mdir 3 3 */
	    i__3 = *nx;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		ii = (i__ << 1) - 1;
		xc[i__] = xf[ii];
/* * */
/* *             *** true solution *** */
		tc[i__ + (j + k * tc_dim2) * tc_dim1] = tcf[ii + (jj + kk * 
			tcf_dim2) * tcf_dim1];
/* * */
/* *             *** helmholtz coefficient *** */
		cc[i__ + (j + k * cc_dim2) * cc_dim1] = ccf[ii + (jj + kk * 
			ccf_dim2) * ccf_dim1];
/* * */
/* *             *** source function *** */
		fc[i__ + (j + k * fc_dim2) * fc_dim1] = fcf[ii + (jj + kk * 
			fcf_dim2) * fcf_dim1];
/* * */
/* *             *** east/west neighbor *** */
		a1c[i__ + (j + k * a1c_dim2) * a1c_dim1] = a1cf[ii + (jj + kk 
			* a1cf_dim2) * a1cf_dim1];
/* * */
/* *             *** north/south neighbor *** */
		a2c[i__ + (j + k * a2c_dim2) * a2c_dim1] = a2cf[ii + (jj + kk 
			* a2cf_dim2) * a2cf_dim1];
/* * */
/* *             *** up/down neighbor *** */
		a3c[i__ + (j + k * a3c_dim2) * a3c_dim1] = a3cf[ii + (jj + kk 
			* a3cf_dim2) * a3cf_dim1];
/* L32: */
	    }
/* L31: */
	}
/* L30: */
    }
/* * */
/* *    *** the (i=1) and (i=nx) boundaries *** */
/* mdir 2 1 */
    i__1 = *nz;
    for (k = 1; k <= i__1; ++k) {
	kk = (k << 1) - 1;
/* mdir 2 2 */
	i__2 = *ny;
	for (j = 1; j <= i__2; ++j) {
	    jj = (j << 1) - 1;
	    gxc[j + (k + gxc_dim2) * gxc_dim1] = gxcf[jj + (kk + gxcf_dim2) * 
		    gxcf_dim1];
	    gxc[j + (k + (gxc_dim2 << 1)) * gxc_dim1] = gxcf[jj + (kk + (
		    gxcf_dim2 << 1)) * gxcf_dim1];
	    gxc[j + (k + gxc_dim2 * 3) * gxc_dim1] = gxcf[jj + (kk + 
		    gxcf_dim2 * 3) * gxcf_dim1];
	    gxc[j + (k + (gxc_dim2 << 2)) * gxc_dim1] = gxcf[jj + (kk + (
		    gxcf_dim2 << 2)) * gxcf_dim1];
/* L51: */
	}
/* L50: */
    }
/* * */
/* *    *** the (j=1) and (j=ny) boundaries *** */
/* mdir 2 1 */
    i__1 = *nz;
    for (k = 1; k <= i__1; ++k) {
	kk = (k << 1) - 1;
/* mdir 2 2 */
	i__2 = *nx;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ii = (i__ << 1) - 1;
	    gyc[i__ + (k + gyc_dim2) * gyc_dim1] = gycf[ii + (kk + gycf_dim2) 
		    * gycf_dim1];
	    gyc[i__ + (k + (gyc_dim2 << 1)) * gyc_dim1] = gycf[ii + (kk + (
		    gycf_dim2 << 1)) * gycf_dim1];
	    gyc[i__ + (k + gyc_dim2 * 3) * gyc_dim1] = gycf[ii + (kk + 
		    gycf_dim2 * 3) * gycf_dim1];
	    gyc[i__ + (k + (gyc_dim2 << 2)) * gyc_dim1] = gycf[ii + (kk + (
		    gycf_dim2 << 2)) * gycf_dim1];
/* L61: */
	}
/* L60: */
    }
/* * */
/* *    *** the (k=1) and (k=nz) boundaries *** */
/* mdir 2 1 */
    i__1 = *ny;
    for (j = 1; j <= i__1; ++j) {
	jj = (j << 1) - 1;
/* mdir 2 2 */
	i__2 = *nx;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ii = (i__ << 1) - 1;
	    gzc[i__ + (j + gzc_dim2) * gzc_dim1] = gzcf[ii + (jj + gzcf_dim2) 
		    * gzcf_dim1];
	    gzc[i__ + (j + (gzc_dim2 << 1)) * gzc_dim1] = gzcf[ii + (jj + (
		    gzcf_dim2 << 1)) * gzcf_dim1];
	    gzc[i__ + (j + gzc_dim2 * 3) * gzc_dim1] = gzcf[ii + (jj + 
		    gzcf_dim2 * 3) * gzcf_dim1];
	    gzc[i__ + (j + (gzc_dim2 << 2)) * gzc_dim1] = gzcf[ii + (jj + (
		    gzcf_dim2 << 2)) * gzcf_dim1];
/* L71: */
	}
/* L70: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildcopy0_ */

/* Subroutine */ int buildharm0_(integer *nx, integer *ny, integer *nz, 
	integer *nxf, integer *nyf, integer *nzf, doublereal *xc, doublereal *
	yc, doublereal *zc, doublereal *gxc, doublereal *gyc, doublereal *gzc,
	 doublereal *a1c, doublereal *a2c, doublereal *a3c, doublereal *cc, 
	doublereal *fc, doublereal *tc, doublereal *xf, doublereal *yf, 
	doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, 
	doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf,
	 doublereal *fcf, doublereal *tcf)
{
    /* System generated locals */
    integer gxc_dim1, gxc_dim2, gxc_offset, gyc_dim1, gyc_dim2, gyc_offset, 
	    gzc_dim1, gzc_dim2, gzc_offset, a1c_dim1, a1c_dim2, a1c_offset, 
	    a2c_dim1, a2c_dim2, a2c_offset, a3c_dim1, a3c_dim2, a3c_offset, 
	    cc_dim1, cc_dim2, cc_offset, fc_dim1, fc_dim2, fc_offset, tc_dim1,
	     tc_dim2, tc_offset, gxcf_dim1, gxcf_dim2, gxcf_offset, gycf_dim1,
	     gycf_dim2, gycf_offset, gzcf_dim1, gzcf_dim2, gzcf_offset, 
	    a1cf_dim1, a1cf_dim2, a1cf_offset, a2cf_dim1, a2cf_dim2, 
	    a2cf_offset, a3cf_dim1, a3cf_dim2, a3cf_offset, tcf_dim1, 
	    tcf_dim2, tcf_offset, ccf_dim1, ccf_dim2, ccf_offset, fcf_dim1, 
	    fcf_dim2, fcf_offset, i__1, i__2, i__3, i__4, i__5, i__6, i__7, 
	    i__8, i__9, i__10, i__11, i__12, i__13, i__14, i__15, i__16, 
	    i__17, i__18, i__19, i__20, i__21, i__22, i__23, i__24, i__25, 
	    i__26, i__27, i__28, i__29, i__30, i__31, i__32, i__33, i__34, 
	    i__35, i__36, i__37, i__38, i__39, i__40, i__41, i__42, i__43, 
	    i__44, i__45, i__46, i__47, i__48, i__49, i__50, i__51, i__52, 
	    i__53, i__54, i__55;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j, k, ii, jj, kk, iadd, jadd, kadd;

    /* Fortran I/O blocks */
    static cilist io___84 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    produce information for a coarser grid. */
/* *    but also harmonically average the problem coefficients. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** statement functions *** */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** how far to step into the coefficient arrays *** */
    /* Parameter adjustments */
    --xc;
    gzc_dim1 = *nx;
    gzc_dim2 = *ny;
    gzc_offset = 1 + gzc_dim1 * (1 + gzc_dim2);
    gzc -= gzc_offset;
    --yc;
    tc_dim1 = *nx;
    tc_dim2 = *ny;
    tc_offset = 1 + tc_dim1 * (1 + tc_dim2);
    tc -= tc_offset;
    fc_dim1 = *nx;
    fc_dim2 = *ny;
    fc_offset = 1 + fc_dim1 * (1 + fc_dim2);
    fc -= fc_offset;
    cc_dim1 = *nx;
    cc_dim2 = *ny;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
    cc -= cc_offset;
    a3c_dim1 = *nx;
    a3c_dim2 = *ny;
    a3c_offset = 1 + a3c_dim1 * (1 + a3c_dim2);
    a3c -= a3c_offset;
    a2c_dim1 = *nx;
    a2c_dim2 = *ny;
    a2c_offset = 1 + a2c_dim1 * (1 + a2c_dim2);
    a2c -= a2c_offset;
    a1c_dim1 = *nx;
    a1c_dim2 = *ny;
    a1c_offset = 1 + a1c_dim1 * (1 + a1c_dim2);
    a1c -= a1c_offset;
    gyc_dim1 = *nx;
    gyc_dim2 = *nz;
    gyc_offset = 1 + gyc_dim1 * (1 + gyc_dim2);
    gyc -= gyc_offset;
    gxc_dim1 = *ny;
    gxc_dim2 = *nz;
    gxc_offset = 1 + gxc_dim1 * (1 + gxc_dim2);
    gxc -= gxc_offset;
    --zc;
    --xf;
    gzcf_dim1 = *nxf;
    gzcf_dim2 = *nyf;
    gzcf_offset = 1 + gzcf_dim1 * (1 + gzcf_dim2);
    gzcf -= gzcf_offset;
    --yf;
    tcf_dim1 = *nxf;
    tcf_dim2 = *nyf;
    tcf_offset = 1 + tcf_dim1 * (1 + tcf_dim2);
    tcf -= tcf_offset;
    fcf_dim1 = *nxf;
    fcf_dim2 = *nyf;
    fcf_offset = 1 + fcf_dim1 * (1 + fcf_dim2);
    fcf -= fcf_offset;
    ccf_dim1 = *nxf;
    ccf_dim2 = *nyf;
    ccf_offset = 1 + ccf_dim1 * (1 + ccf_dim2);
    ccf -= ccf_offset;
    a3cf_dim1 = *nxf;
    a3cf_dim2 = *nyf;
    a3cf_offset = 1 + a3cf_dim1 * (1 + a3cf_dim2);
    a3cf -= a3cf_offset;
    a2cf_dim1 = *nxf;
    a2cf_dim2 = *nyf;
    a2cf_offset = 1 + a2cf_dim1 * (1 + a2cf_dim2);
    a2cf -= a2cf_offset;
    a1cf_dim1 = *nxf;
    a1cf_dim2 = *nyf;
    a1cf_offset = 1 + a1cf_dim1 * (1 + a1cf_dim2);
    a1cf -= a1cf_offset;
    gycf_dim1 = *nxf;
    gycf_dim2 = *nzf;
    gycf_offset = 1 + gycf_dim1 * (1 + gycf_dim2);
    gycf -= gycf_offset;
    gxcf_dim1 = *nyf;
    gxcf_dim2 = *nzf;
    gxcf_offset = 1 + gxcf_dim1 * (1 + gxcf_dim2);
    gxcf -= gxcf_offset;
    --zf;

    /* Function Body */
    iadd = (*nxf - 1) / (*nx - 1);
    jadd = (*nyf - 1) / (*ny - 1);
    kadd = (*nzf - 1) / (*nz - 1);
    if (iadd != 2 || jadd != 2 || kadd != 2) {
	s_wsle(&io___84);
	do_lio(&c__9, &c__1, "% BUILDHARM0: problem with grid dimensions...", 
		(ftnlen)45);
	e_wsle();
    }
/* * */
/* *    *** compute the coarse grid pde coefficients *** */
/* mdir 3 1 */
    i__1 = *nz;
    for (k = 1; k <= i__1; ++k) {
	kk = (k << 1) - 1;
	zc[k] = zf[kk];
/* mdir 3 2 */
	i__2 = *ny;
	for (j = 1; j <= i__2; ++j) {
	    jj = (j << 1) - 1;
	    yc[j] = yf[jj];
/* mdir 3 3 */
	    i__3 = *nx;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		ii = (i__ << 1) - 1;
		xc[i__] = xf[ii];
/* * */
/* *             *** true solution *** */
		tc[i__ + (j + k * tc_dim2) * tc_dim1] = tcf[ii + (jj + kk * 
			tcf_dim2) * tcf_dim1];
/* * */
/* *             *** helmholtz coefficient *** */
		cc[i__ + (j + k * cc_dim2) * cc_dim1] = ccf[ii + (jj + kk * 
			ccf_dim2) * ccf_dim1];
/* ZZZ           cc(i,j,k) = ( */
/* ZZZ 2            +0.5e0 * ccf(ii,jj,kk) */
/* ZZZ 3            +0.5e0 * arith6( ccf(max0(1,ii-1),jj,kk), */
/* ZZZ 4                             ccf(min0(nxf,ii+1),jj,kk), */
/* ZZZ 5                             ccf(ii,max0(1,jj-1),kk), */
/* ZZZ 6                             ccf(ii,min0(nyf,jj+1),kk), */
/* ZZZ 7                             ccf(ii,jj,max0(nzf,kk-1)), */
/* ZZZ 8                             ccf(ii,jj,min0(nzf,kk+1)) ) */
/* ZZZ 9            ) */
/* * */
/* *             *** source function *** */
		fc[i__ + (j + k * fc_dim2) * fc_dim1] = fcf[ii + (jj + kk * 
			fcf_dim2) * fcf_dim1];
/* ZZZ           fc(i,j,k) = ( */
/* ZZZ 2            +0.5e0 * fcf(ii,jj,kk) */
/* ZZZ 3            +0.5e0 * arith6( fcf(max0(1,ii-1),jj,kk), */
/* ZZZ 4                             fcf(min0(nxf,ii+1),jj,kk), */
/* ZZZ 5                             fcf(ii,max0(1,jj-1),kk), */
/* ZZZ 6                             fcf(ii,min0(nyf,jj+1),kk), */
/* ZZZ 7                             fcf(ii,jj,max0(nzf,kk-1)), */
/* ZZZ 8                             fcf(ii,jj,min0(nzf,kk+1)) ) */
/* ZZZ 9            ) */
/* * */
/* *             *** east/west neighbor *** */
/* Computing MIN */
		i__4 = *nxf, i__5 = ii + 1;
/* Computing MIN */
		i__6 = *nxf, i__7 = ii + 1;
/* Computing MAX */
		i__8 = 1, i__9 = kk - 1;
/* Computing MIN */
		i__10 = *nxf, i__11 = ii + 1;
/* Computing MAX */
		i__12 = 1, i__13 = kk - 1;
/* Computing MAX */
		i__14 = 1, i__15 = kk - 1;
/* Computing MIN */
		i__16 = *nxf, i__17 = ii + 1;
/* Computing MAX */
		i__18 = 1, i__19 = kk - 1;
/* Computing MIN */
		i__20 = *nzf, i__21 = kk + 1;
/* Computing MIN */
		i__22 = *nxf, i__23 = ii + 1;
/* Computing MIN */
		i__24 = *nzf, i__25 = kk + 1;
/* Computing MIN */
		i__26 = *nzf, i__27 = kk + 1;
/* Computing MIN */
		i__28 = *nxf, i__29 = ii + 1;
/* Computing MIN */
		i__30 = *nzf, i__31 = kk + 1;
/* Computing MAX */
		i__32 = 1, i__33 = jj - 1;
/* Computing MIN */
		i__34 = *nxf, i__35 = ii + 1;
/* Computing MAX */
		i__36 = 1, i__37 = jj - 1;
/* Computing MAX */
		i__38 = 1, i__39 = jj - 1;
/* Computing MIN */
		i__40 = *nxf, i__41 = ii + 1;
/* Computing MAX */
		i__42 = 1, i__43 = jj - 1;
/* Computing MIN */
		i__44 = *nyf, i__45 = jj + 1;
/* Computing MIN */
		i__46 = *nxf, i__47 = ii + 1;
/* Computing MIN */
		i__48 = *nyf, i__49 = jj + 1;
/* Computing MIN */
		i__50 = *nyf, i__51 = jj + 1;
/* Computing MIN */
		i__52 = *nxf, i__53 = ii + 1;
/* Computing MIN */
		i__54 = *nyf, i__55 = jj + 1;
		a1c[i__ + (j + k * a1c_dim2) * a1c_dim1] = 2.f * a1cf[ii + (
			jj + kk * a1cf_dim2) * a1cf_dim1] * a1cf[min(i__4,
			i__5) + (jj + kk * a1cf_dim2) * a1cf_dim1] / (a1cf[ii 
			+ (jj + kk * a1cf_dim2) * a1cf_dim1] + a1cf[min(i__6,
			i__7) + (jj + kk * a1cf_dim2) * a1cf_dim1]) * .5f + 
			2.f * a1cf[ii + (jj + max(i__8,i__9) * a1cf_dim2) * 
			a1cf_dim1] * a1cf[min(i__10,i__11) + (jj + max(i__12,
			i__13) * a1cf_dim2) * a1cf_dim1] / (a1cf[ii + (jj + 
			max(i__14,i__15) * a1cf_dim2) * a1cf_dim1] + a1cf[min(
			i__16,i__17) + (jj + max(i__18,i__19) * a1cf_dim2) * 
			a1cf_dim1]) * .125f + 2.f * a1cf[ii + (jj + min(i__20,
			i__21) * a1cf_dim2) * a1cf_dim1] * a1cf[min(i__22,
			i__23) + (jj + min(i__24,i__25) * a1cf_dim2) * 
			a1cf_dim1] / (a1cf[ii + (jj + min(i__26,i__27) * 
			a1cf_dim2) * a1cf_dim1] + a1cf[min(i__28,i__29) + (jj 
			+ min(i__30,i__31) * a1cf_dim2) * a1cf_dim1]) * .125f 
			+ 2.f * a1cf[ii + (max(i__32,i__33) + kk * a1cf_dim2) 
			* a1cf_dim1] * a1cf[min(i__34,i__35) + (max(i__36,
			i__37) + kk * a1cf_dim2) * a1cf_dim1] / (a1cf[ii + (
			max(i__38,i__39) + kk * a1cf_dim2) * a1cf_dim1] + 
			a1cf[min(i__40,i__41) + (max(i__42,i__43) + kk * 
			a1cf_dim2) * a1cf_dim1]) * .125f + 2.f * a1cf[ii + (
			min(i__44,i__45) + kk * a1cf_dim2) * a1cf_dim1] * 
			a1cf[min(i__46,i__47) + (min(i__48,i__49) + kk * 
			a1cf_dim2) * a1cf_dim1] / (a1cf[ii + (min(i__50,i__51)
			 + kk * a1cf_dim2) * a1cf_dim1] + a1cf[min(i__52,
			i__53) + (min(i__54,i__55) + kk * a1cf_dim2) * 
			a1cf_dim1]) * .125f;
/* * */
/* *             *** north/south neighbor *** */
/* Computing MIN */
		i__4 = *nyf, i__5 = jj + 1;
/* Computing MIN */
		i__6 = *nyf, i__7 = jj + 1;
/* Computing MAX */
		i__8 = 1, i__9 = kk - 1;
/* Computing MIN */
		i__10 = *nyf, i__11 = jj + 1;
/* Computing MAX */
		i__12 = 1, i__13 = kk - 1;
/* Computing MAX */
		i__14 = 1, i__15 = kk - 1;
/* Computing MIN */
		i__16 = *nyf, i__17 = jj + 1;
/* Computing MAX */
		i__18 = 1, i__19 = kk - 1;
/* Computing MIN */
		i__20 = *nzf, i__21 = kk + 1;
/* Computing MIN */
		i__22 = *nyf, i__23 = jj + 1;
/* Computing MIN */
		i__24 = *nzf, i__25 = kk + 1;
/* Computing MIN */
		i__26 = *nzf, i__27 = kk + 1;
/* Computing MIN */
		i__28 = *nyf, i__29 = jj + 1;
/* Computing MIN */
		i__30 = *nzf, i__31 = kk + 1;
/* Computing MAX */
		i__32 = 1, i__33 = ii - 1;
/* Computing MAX */
		i__34 = 1, i__35 = ii - 1;
/* Computing MIN */
		i__36 = *nyf, i__37 = jj + 1;
/* Computing MAX */
		i__38 = 1, i__39 = ii - 1;
/* Computing MAX */
		i__40 = 1, i__41 = ii - 1;
/* Computing MIN */
		i__42 = *nyf, i__43 = jj + 1;
/* Computing MIN */
		i__44 = *nxf, i__45 = ii + 1;
/* Computing MIN */
		i__46 = *nxf, i__47 = ii + 1;
/* Computing MIN */
		i__48 = *nyf, i__49 = jj + 1;
/* Computing MIN */
		i__50 = *nxf, i__51 = ii + 1;
/* Computing MIN */
		i__52 = *nxf, i__53 = ii + 1;
/* Computing MIN */
		i__54 = *nyf, i__55 = jj + 1;
		a2c[i__ + (j + k * a2c_dim2) * a2c_dim1] = 2.f * a2cf[ii + (
			jj + kk * a2cf_dim2) * a2cf_dim1] * a2cf[ii + (min(
			i__4,i__5) + kk * a2cf_dim2) * a2cf_dim1] / (a2cf[ii 
			+ (jj + kk * a2cf_dim2) * a2cf_dim1] + a2cf[ii + (min(
			i__6,i__7) + kk * a2cf_dim2) * a2cf_dim1]) * .5f + 
			2.f * a2cf[ii + (jj + max(i__8,i__9) * a2cf_dim2) * 
			a2cf_dim1] * a2cf[ii + (min(i__10,i__11) + max(i__12,
			i__13) * a2cf_dim2) * a2cf_dim1] / (a2cf[ii + (jj + 
			max(i__14,i__15) * a2cf_dim2) * a2cf_dim1] + a2cf[ii 
			+ (min(i__16,i__17) + max(i__18,i__19) * a2cf_dim2) * 
			a2cf_dim1]) * .125f + 2.f * a2cf[ii + (jj + min(i__20,
			i__21) * a2cf_dim2) * a2cf_dim1] * a2cf[ii + (min(
			i__22,i__23) + min(i__24,i__25) * a2cf_dim2) * 
			a2cf_dim1] / (a2cf[ii + (jj + min(i__26,i__27) * 
			a2cf_dim2) * a2cf_dim1] + a2cf[ii + (min(i__28,i__29) 
			+ min(i__30,i__31) * a2cf_dim2) * a2cf_dim1]) * .125f 
			+ 2.f * a2cf[max(i__32,i__33) + (jj + kk * a2cf_dim2) 
			* a2cf_dim1] * a2cf[max(i__34,i__35) + (min(i__36,
			i__37) + kk * a2cf_dim2) * a2cf_dim1] / (a2cf[max(
			i__38,i__39) + (jj + kk * a2cf_dim2) * a2cf_dim1] + 
			a2cf[max(i__40,i__41) + (min(i__42,i__43) + kk * 
			a2cf_dim2) * a2cf_dim1]) * .125f + 2.f * a2cf[min(
			i__44,i__45) + (jj + kk * a2cf_dim2) * a2cf_dim1] * 
			a2cf[min(i__46,i__47) + (min(i__48,i__49) + kk * 
			a2cf_dim2) * a2cf_dim1] / (a2cf[min(i__50,i__51) + (
			jj + kk * a2cf_dim2) * a2cf_dim1] + a2cf[min(i__52,
			i__53) + (min(i__54,i__55) + kk * a2cf_dim2) * 
			a2cf_dim1]) * .125f;
/* * */
/* *             *** up/down neighbor *** */
/* Computing MIN */
		i__4 = *nzf, i__5 = kk + 1;
/* Computing MIN */
		i__6 = *nzf, i__7 = kk + 1;
/* Computing MAX */
		i__8 = 1, i__9 = jj - 1;
/* Computing MAX */
		i__10 = 1, i__11 = jj - 1;
/* Computing MIN */
		i__12 = *nzf, i__13 = kk + 1;
/* Computing MAX */
		i__14 = 1, i__15 = jj - 1;
/* Computing MAX */
		i__16 = 1, i__17 = jj - 1;
/* Computing MIN */
		i__18 = *nzf, i__19 = kk + 1;
/* Computing MIN */
		i__20 = *nyf, i__21 = jj + 1;
/* Computing MIN */
		i__22 = *nyf, i__23 = jj + 1;
/* Computing MIN */
		i__24 = *nzf, i__25 = kk + 1;
/* Computing MIN */
		i__26 = *nyf, i__27 = jj + 1;
/* Computing MIN */
		i__28 = *nyf, i__29 = jj + 1;
/* Computing MIN */
		i__30 = *nzf, i__31 = kk + 1;
/* Computing MAX */
		i__32 = 1, i__33 = ii - 1;
/* Computing MAX */
		i__34 = 1, i__35 = ii - 1;
/* Computing MIN */
		i__36 = *nzf, i__37 = kk + 1;
/* Computing MAX */
		i__38 = 1, i__39 = ii - 1;
/* Computing MAX */
		i__40 = 1, i__41 = ii - 1;
/* Computing MIN */
		i__42 = *nzf, i__43 = kk + 1;
/* Computing MIN */
		i__44 = *nxf, i__45 = ii + 1;
/* Computing MIN */
		i__46 = *nxf, i__47 = ii + 1;
/* Computing MIN */
		i__48 = *nzf, i__49 = kk + 1;
/* Computing MIN */
		i__50 = *nxf, i__51 = ii + 1;
/* Computing MIN */
		i__52 = *nxf, i__53 = ii + 1;
/* Computing MIN */
		i__54 = *nzf, i__55 = kk + 1;
		a3c[i__ + (j + k * a3c_dim2) * a3c_dim1] = 2.f * a3cf[ii + (
			jj + kk * a3cf_dim2) * a3cf_dim1] * a3cf[ii + (jj + 
			min(i__4,i__5) * a3cf_dim2) * a3cf_dim1] / (a3cf[ii + 
			(jj + kk * a3cf_dim2) * a3cf_dim1] + a3cf[ii + (jj + 
			min(i__6,i__7) * a3cf_dim2) * a3cf_dim1]) * .5f + 2.f 
			* a3cf[ii + (max(i__8,i__9) + kk * a3cf_dim2) * 
			a3cf_dim1] * a3cf[ii + (max(i__10,i__11) + min(i__12,
			i__13) * a3cf_dim2) * a3cf_dim1] / (a3cf[ii + (max(
			i__14,i__15) + kk * a3cf_dim2) * a3cf_dim1] + a3cf[ii 
			+ (max(i__16,i__17) + min(i__18,i__19) * a3cf_dim2) * 
			a3cf_dim1]) * .125f + 2.f * a3cf[ii + (min(i__20,
			i__21) + kk * a3cf_dim2) * a3cf_dim1] * a3cf[ii + (
			min(i__22,i__23) + min(i__24,i__25) * a3cf_dim2) * 
			a3cf_dim1] / (a3cf[ii + (min(i__26,i__27) + kk * 
			a3cf_dim2) * a3cf_dim1] + a3cf[ii + (min(i__28,i__29) 
			+ min(i__30,i__31) * a3cf_dim2) * a3cf_dim1]) * .125f 
			+ 2.f * a3cf[max(i__32,i__33) + (jj + kk * a3cf_dim2) 
			* a3cf_dim1] * a3cf[max(i__34,i__35) + (jj + min(
			i__36,i__37) * a3cf_dim2) * a3cf_dim1] / (a3cf[max(
			i__38,i__39) + (jj + kk * a3cf_dim2) * a3cf_dim1] + 
			a3cf[max(i__40,i__41) + (jj + min(i__42,i__43) * 
			a3cf_dim2) * a3cf_dim1]) * .125f + 2.f * a3cf[min(
			i__44,i__45) + (jj + kk * a3cf_dim2) * a3cf_dim1] * 
			a3cf[min(i__46,i__47) + (jj + min(i__48,i__49) * 
			a3cf_dim2) * a3cf_dim1] / (a3cf[min(i__50,i__51) + (
			jj + kk * a3cf_dim2) * a3cf_dim1] + a3cf[min(i__52,
			i__53) + (jj + min(i__54,i__55) * a3cf_dim2) * 
			a3cf_dim1]) * .125f;
/* L32: */
	    }
/* L31: */
	}
/* L30: */
    }
/* * */
/* *    *** the (i=1) and (i=nx) boundaries *** */
/* mdir 2 1 */
    i__1 = *nz;
    for (k = 1; k <= i__1; ++k) {
	kk = (k << 1) - 1;
/* mdir 2 2 */
	i__2 = *ny;
	for (j = 1; j <= i__2; ++j) {
	    jj = (j << 1) - 1;
	    gxc[j + (k + gxc_dim2) * gxc_dim1] = gxcf[jj + (kk + gxcf_dim2) * 
		    gxcf_dim1];
	    gxc[j + (k + (gxc_dim2 << 1)) * gxc_dim1] = gxcf[jj + (kk + (
		    gxcf_dim2 << 1)) * gxcf_dim1];
	    gxc[j + (k + gxc_dim2 * 3) * gxc_dim1] = gxcf[jj + (kk + 
		    gxcf_dim2 * 3) * gxcf_dim1];
	    gxc[j + (k + (gxc_dim2 << 2)) * gxc_dim1] = gxcf[jj + (kk + (
		    gxcf_dim2 << 2)) * gxcf_dim1];
/* L51: */
	}
/* L50: */
    }
/* * */
/* *    *** the (j=1) and (j=ny) boundaries *** */
/* mdir 2 1 */
    i__1 = *nz;
    for (k = 1; k <= i__1; ++k) {
	kk = (k << 1) - 1;
/* mdir 2 2 */
	i__2 = *nx;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ii = (i__ << 1) - 1;
	    gyc[i__ + (k + gyc_dim2) * gyc_dim1] = gycf[ii + (kk + gycf_dim2) 
		    * gycf_dim1];
	    gyc[i__ + (k + (gyc_dim2 << 1)) * gyc_dim1] = gycf[ii + (kk + (
		    gycf_dim2 << 1)) * gycf_dim1];
	    gyc[i__ + (k + gyc_dim2 * 3) * gyc_dim1] = gycf[ii + (kk + 
		    gycf_dim2 * 3) * gycf_dim1];
	    gyc[i__ + (k + (gyc_dim2 << 2)) * gyc_dim1] = gycf[ii + (kk + (
		    gycf_dim2 << 2)) * gycf_dim1];
/* L61: */
	}
/* L60: */
    }
/* * */
/* *    *** the (k=1) and (k=nz) boundaries *** */
/* mdir 2 1 */
    i__1 = *ny;
    for (j = 1; j <= i__1; ++j) {
	jj = (j << 1) - 1;
/* mdir 2 2 */
	i__2 = *nx;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ii = (i__ << 1) - 1;
	    gzc[i__ + (j + gzc_dim2) * gzc_dim1] = gzcf[ii + (jj + gzcf_dim2) 
		    * gzcf_dim1];
	    gzc[i__ + (j + (gzc_dim2 << 1)) * gzc_dim1] = gzcf[ii + (jj + (
		    gzcf_dim2 << 1)) * gzcf_dim1];
	    gzc[i__ + (j + gzc_dim2 * 3) * gzc_dim1] = gzcf[ii + (jj + 
		    gzcf_dim2 * 3) * gzcf_dim1];
	    gzc[i__ + (j + (gzc_dim2 << 2)) * gzc_dim1] = gzcf[ii + (jj + (
		    gzcf_dim2 << 2)) * gzcf_dim1];
/* L71: */
	}
/* L70: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildharm0_ */

/* Subroutine */ int buildgaler0_(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, integer *ipkey, integer *
	numdia, doublereal *pcff, integer *ipcff, doublereal *rpcff, 
	doublereal *acff, doublereal *ccff, doublereal *fcff, integer *ipc, 
	doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc)
{
    static integer numdia_loc__;
    extern /* Subroutine */ int buildg_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *), restrc_(integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    form the galerkin coarse grid system. */
/* * */
/* *    notes: although the fine grid matrix may be 7 or 27 diagonal, */
/* *           the coarse grid matrix is always 27 diagonal. */
/* *           (only 14 stored due to symmetry.) */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the algebraic galerkin routine *** */
    /* Parameter adjustments */
    --fc;
    --cc;
    --ac;
    --rpc;
    --ipc;
    --fcff;
    --ccff;
    --acff;
    --rpcff;
    --ipcff;
    --pcff;

    /* Function Body */
    numdia_loc__ = ipcff[11];
    buildg_(nxf, nyf, nzf, nxc, nyc, nzc, &numdia_loc__, &pcff[1], &acff[1], &
	    ac[1]);
/* * */
/* *    *** note how many nonzeros in this new discretization stencil *** */
    ipc[11] = 27;
    *numdia = 14;
/* * */
/* *    *** save the problem key with this new operator *** */
    ipc[10] = *ipkey;
/* * */
/* *    *** restrict the helmholtz term and source function *** */
    restrc_(nxf, nyf, nzf, nxc, nyc, nzc, &ccff[1], &cc[1], &pcff[1]);
    restrc_(nxf, nyf, nzf, nxc, nyc, nzc, &fcff[1], &fc[1], &pcff[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildgaler0_ */

/* Subroutine */ int buildgaler1_(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, integer *numdia, doublereal 
	*pcff, integer *ipcff, doublereal *rpcff, doublereal *ccff, integer *
	ipc, doublereal *rpc, doublereal *cc)
{
    static integer numdia_loc__;
    extern /* Subroutine */ int buildg_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    form the helmholtz term of a galerkin coarse grid system. */
/* * */
/* *    notes: although the fine grid matrix may be 1 or 27 diagonal, */
/* *           the coarse grid matrix is always 27 diagonal. */
/* *           (only 14 stored due to symmetry.) */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the algebraic galerkin routine *** */
    /* Parameter adjustments */
    --cc;
    --rpc;
    --ipc;
    --ccff;
    --rpcff;
    --ipcff;
    --pcff;

    /* Function Body */
    numdia_loc__ = ipcff[12];
    buildg_(nxf, nyf, nzf, nxc, nyc, nzc, &numdia_loc__, &pcff[1], &ccff[1], &
	    cc[1]);
/* * */
/* *    *** note how many nonzeros in this new discretization stencil *** */
    ipc[12] = 27;
    *numdia = 14;
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildgaler1_ */

/* Subroutine */ int buildalg_(integer *nx, integer *ny, integer *nz, integer 
	*mode, integer *nlev, integer *iz, integer *ipc, doublereal *rpc, 
	doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, 
	doublereal *y, doublereal *tmp)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer lev, nxx, nyy, nzz, nxold, nyold, nzold;
    extern /* Subroutine */ int matvec_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *), mkcors_(integer *, integer *, integer *, integer *
	    , integer *, integer *, integer *), nmatvec_(integer *, integer *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    build rhs algebraically for analysis purposes. */
/* * */
/* *    note:  the fine level must be build before any coarse levels. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** setup *** */
    /* Parameter adjustments */
    --tmp;
    --y;
    --x;
    --fc;
    --cc;
    --ac;
    --rpc;
    --ipc;
    iz -= 51;

    /* Function Body */
    nxx = *nx;
    nyy = *ny;
    nzz = *nz;
/* * */
/* *    *** build the rhs the finest level *** */
    lev = 1;
    if (*mode == 1 || *mode == 2) {
	nmatvec_(&nxx, &nyy, &nzz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 
		6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev 
		* 50 + 1]], &x[iz[lev * 50 + 1]], &y[iz[lev * 50 + 1]], &tmp[
		1]);
    } else {
	matvec_(&nxx, &nyy, &nzz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 
		6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &x[iz[lev *
		 50 + 1]], &y[iz[lev * 50 + 1]]);
    }
/* * */
/* *    *** build the (nlev-1) level rhs function *** */
    i__1 = *nlev;
    for (lev = 2; lev <= i__1; ++lev) {
	nxold = nxx;
	nyold = nyy;
	nzold = nzz;
	mkcors_(&c__1, &nxold, &nyold, &nzold, &nxx, &nyy, &nzz);
/* * */
/* *       *** build the rhs on this level *** */
	if (*mode == 1 || *mode == 2) {
	    nmatvec_(&nxx, &nyy, &nzz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 
		    50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &
		    fc[iz[lev * 50 + 1]], &x[iz[lev * 50 + 1]], &y[iz[lev * 
		    50 + 1]], &tmp[1]);
	} else {
	    matvec_(&nxx, &nyy, &nzz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 
		    50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &
		    x[iz[lev * 50 + 1]], &y[iz[lev * 50 + 1]]);
	}
/* L10: */
    }
/* * */
/* *    *** end it *** */
    return 0;
} /* buildalg_ */

