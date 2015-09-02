/* ./src_f77/powerd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b10 = -1.;
static real c_b19 = 2.f;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    powerd.f */
/* * @author  Michael Holst */
/* * @brief   Power and Inverse Power Methods for doing spectral diagnostics. */
/* * @version $Id: powerd.c,v 1.3 2010/08/12 05:45:28 fetk Exp $ */
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
/* Subroutine */ int power_(integer *nx, integer *ny, integer *nz, integer *
	iz, integer *ilev, integer *ipc, doublereal *rpc, doublereal *ac, 
	doublereal *cc, doublereal *w1, doublereal *w2, doublereal *w3, 
	doublereal *w4, doublereal *eigmax, doublereal *eigmax_model__, 
	doublereal *tol, integer *itmax, integer *iters, integer *iinfo)
{
    /* Format strings */
    static char fmt_510[] = "(\002% \002,a,i5,1pe11.4)";
    static char fmt_500[] = "(\002% \002,a,i5,2(1pe9.2),1pe11.4)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double atan(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double pow_ri(real *, integer *), cos(doublereal);

    /* Local variables */
    static doublereal pi, fac;
    static integer lev;
    static doublereal rho;
    extern doublereal xdot_(integer *, integer *, integer *, doublereal *, 
	    doublereal *), xnrm2_(integer *, integer *, integer *, doublereal 
	    *);
    static doublereal denom;
    static integer level;
    extern /* Subroutine */ int xscal_(integer *, integer *, integer *, 
	    doublereal *, doublereal *);
    static doublereal error;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *), xaxpy_(integer *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *), axrand_(integer *, 
	    integer *, integer *, doublereal *), matvec_(integer *, integer *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal oldrho, relerr;
    extern /* Subroutine */ int azeros_(integer *, integer *, integer *, 
	    doublereal *);

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 6, 0, fmt_510, 0 };
    static cilist io___11 = { 0, 6, 0, fmt_500, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    standard power method for maximum eigenvalue estimation */
/* *    of the system matrix A. */
/* * */
/* * notes: */
/* * */
/* *    to test, note that the 3d laplacean has min/max eigenvalues: */
/* * */
/* *       lambda_min = 6 - 2*dcos(pi/(nx-1)) */
/* *                      - 2*dcos(pi/(ny-1)) */
/* *                      - 2*dcos(pi/(nz-1)) */
/* * */
/* *       lambda_max = 6 - 2*dcos((nx-2)*pi/(nx-1)) */
/* *                      - 2*dcos((ny-2)*pi/(ny-1)) */
/* *                      - 2*dcos((nz-2)*pi/(nz-1)) */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** some parameters *** */
    /* Parameter adjustments */
    --w4;
    --w3;
    --w2;
    --w1;
    --cc;
    --ac;
    --rpc;
    --ipc;
    iz -= 51;

    /* Function Body */
    pi = atan(1.) * 4.;
/* * */
/* *    *** recover level information *** */
    level = 1;
    lev = *ilev - 1 + level;
/* * */
/* *    *** seed vector: random to contain all components *** */
    axrand_(nx, ny, nz, &w1[1]);
    azeros_(nx, ny, nz, &w2[1]);
    azeros_(nx, ny, nz, &w3[1]);
    azeros_(nx, ny, nz, &w4[1]);
/* * */
/* *    *** compute raleigh quotient with the seed vector *** */
    denom = xnrm2_(nx, ny, nz, &w1[1]);
    fac = 1.f / denom;
    xscal_(nx, ny, nz, &fac, &w1[1]);
    matvec_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &ac[
	    iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &w1[1], &w2[1]);
    oldrho = xdot_(nx, ny, nz, &w1[1], &w2[1]);
/* * */
/* *    *** i/o *** */
    if (oldrho == 0.f) {
	if (*iinfo > 3) {
	    s_wsfe(&io___7);
	    do_fio(&c__1, "POWER: iter; estimate = ", (ftnlen)24);
	    do_fio(&c__1, (char *)&(*iters), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&oldrho, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	rho = oldrho;
	goto L99;
    }
/* * */
/* *    *** main iteration *** */
    *iters = 0;
L20:
    ++(*iters);
/* * */
/* *       *** apply the matrix A *** */
    matvec_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &ac[
	    iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &w1[1], &w2[1]);
    xcopy_(nx, ny, nz, &w2[1], &w1[1]);
/* * */
/* *       *** normalize the new vector *** */
    denom = xnrm2_(nx, ny, nz, &w1[1]);
    fac = 1.f / denom;
    xscal_(nx, ny, nz, &fac, &w1[1]);
/* * */
/* *       *** compute the new raleigh quotient *** */
    matvec_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &ac[
	    iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &w1[1], &w2[1]);
    rho = xdot_(nx, ny, nz, &w1[1], &w2[1]);
/* * */
/* *       *** stopping test *** */
/* *       *** w2=A*x, w1=x, stop = 2-norm(A*x-lamda*x) *** */
    xcopy_(nx, ny, nz, &w1[1], &w3[1]);
    xcopy_(nx, ny, nz, &w2[1], &w4[1]);
    xscal_(nx, ny, nz, &rho, &w3[1]);
    xaxpy_(nx, ny, nz, &c_b10, &w3[1], &w4[1]);
    error = xnrm2_(nx, ny, nz, &w4[1]);
    relerr = (d__1 = rho - oldrho, abs(d__1)) / abs(rho);
/* * */
/* *       *** i/o *** */
    if (*iinfo > 3) {
	s_wsfe(&io___11);
	do_fio(&c__1, "POWER:  iter; error; relerr; estimate = ", (ftnlen)40);
	do_fio(&c__1, (char *)&(*iters), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&error, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&relerr, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rho, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (relerr < *tol || *iters == *itmax) {
	goto L99;
    }
    oldrho = rho;
    goto L20;
/* * */
/* *    *** return some stuff *** */
L99:
    *eigmax = rho;
    i__1 = *ilev - 1;
    fac = pow_ri(&c_b19, &i__1);
    *eigmax_model__ = fac * (6. - cos((doublereal) (*nx - 2) * pi / (
	    doublereal) (*nx - 1)) * 2. - cos((doublereal) (*ny - 2) * pi / (
	    doublereal) (*ny - 1)) * 2. - cos((doublereal) (*nz - 2) * pi / (
	    doublereal) (*nz - 1)) * 2.);
/* * */
/* *    *** return and end *** */
    return 0;
} /* power_ */

/* Subroutine */ int ipower_(integer *nx, integer *ny, integer *nz, 
	doublereal *u, integer *iz, doublereal *w0, doublereal *w1, 
	doublereal *w2, doublereal *w3, doublereal *w4, doublereal *eigmin, 
	doublereal *eigmin_model__, doublereal *tol, integer *itmax, integer *
	iters, integer *nlev, integer *ilev, integer *nlev_real__, integer *
	mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *
	errtol, doublereal *omega, integer *nu1, integer *nu2, integer *
	mgsmoo, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac,
	 doublereal *cc, doublereal *tru)
{
    /* Format strings */
    static char fmt_510[] = "(\002% \002,a,i5,1pe11.4)";
    static char fmt_500[] = "(\002% \002,a,i5,2(1pe9.2),1pe11.4)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double atan(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double pow_ri(real *, integer *), cos(doublereal);

    /* Local variables */
    static integer mgsmoo_s__, ierror_s__;
    static doublereal errtol_s__, pi, fac;
    static integer lev;
    static doublereal rho;
    extern /* Subroutine */ int mvcs_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    extern doublereal xdot_(integer *, integer *, integer *, doublereal *, 
	    doublereal *);
    static integer nu1_s__, nu2_s__;
    extern doublereal xnrm2_(integer *, integer *, integer *, doublereal *);
    static doublereal denom;
    static integer iok_s__, level;
    extern /* Subroutine */ int xscal_(integer *, integer *, integer *, 
	    doublereal *, doublereal *);
    static doublereal error;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *), xaxpy_(integer *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *), axrand_(integer *, 
	    integer *, integer *, doublereal *), matvec_(integer *, integer *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal oldrho, relerr;
    extern /* Subroutine */ int azeros_(integer *, integer *, integer *, 
	    doublereal *);
    static integer iinfo_s__, itmax_s__, iters_s__, istop_s__;

    /* Fortran I/O blocks */
    static cilist io___18 = { 0, 6, 0, fmt_510, 0 };
    static cilist io___32 = { 0, 6, 0, fmt_500, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    standard inverse power method for minimum eigenvalue estimation */
/* *    of the system matrix A. */
/* * */
/* * notes: */
/* * */
/* *    to test, note that the 3d laplacean has min/max eigenvalues: */
/* * */
/* *       lambda_min = 6 - 2*dcos(pi/(nx-1)) */
/* *                      - 2*dcos(pi/(ny-1)) */
/* *                      - 2*dcos(pi/(nz-1)) */
/* * */
/* *       lambda_max = 6 - 2*dcos((nx-2)*pi/(nx-1)) */
/* *                      - 2*dcos((ny-2)*pi/(ny-1)) */
/* *                      - 2*dcos((nz-2)*pi/(nz-1)) */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** other declarations *** */
/* * */
/* *    *** some more *** */
/* * */
/* *    *** some parameters *** */
    /* Parameter adjustments */
    --tru;
    --cc;
    --ac;
    --pc;
    --rpc;
    --ipc;
    --w4;
    --w3;
    --w2;
    --w1;
    --w0;
    iz -= 51;
    --u;

    /* Function Body */
    pi = atan(1.) * 4.;
/* * */
/* *    *** recover level information *** */
    level = 1;
    lev = *ilev - 1 + level;
/* * */
/* *    *** seed vector: random to contain all components *** */
    axrand_(nx, ny, nz, &w1[1]);
    azeros_(nx, ny, nz, &w2[1]);
    azeros_(nx, ny, nz, &w3[1]);
    azeros_(nx, ny, nz, &w4[1]);
    azeros_(nx, ny, nz, &w0[iz[lev * 50 + 1]]);
    azeros_(nx, ny, nz, &u[iz[lev * 50 + 1]]);
/* * */
/* *    *** compute raleigh quotient with the seed vector *** */
    denom = xnrm2_(nx, ny, nz, &w1[1]);
    fac = 1.f / denom;
    xscal_(nx, ny, nz, &fac, &w1[1]);
    matvec_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &ac[
	    iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &w1[1], &w2[1]);
    oldrho = xdot_(nx, ny, nz, &w1[1], &w2[1]);
/* * */
/* *    *** i/o *** */
    if (oldrho == 0.f) {
	if (*iinfo > 3) {
	    s_wsfe(&io___18);
	    do_fio(&c__1, "IPOWER: iter; estimate = ", (ftnlen)25);
	    do_fio(&c__1, (char *)&(*iters), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&oldrho, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	rho = oldrho;
	goto L99;
    }
/* * */
/* *    *** main iteration *** */
    *iters = 0;
L20:
    ++(*iters);
/* * */
/* *       *** apply the matrix A^{-1} (using MG solver) *** */
    itmax_s__ = 100;
    iters_s__ = 0;
    ierror_s__ = 0;
    iok_s__ = 0;
    iinfo_s__ = 0;
    istop_s__ = 0;
    mgsmoo_s__ = 1;
    nu1_s__ = 1;
    nu2_s__ = 1;
    errtol_s__ = *epsiln;
    xcopy_(nx, ny, nz, &w1[1], &w0[iz[lev * 50 + 1]]);
    mvcs_(nx, ny, nz, &u[1], &iz[51], &w1[1], &w2[1], &w3[1], &w4[1], &
	    istop_s__, &itmax_s__, &iters_s__, &ierror_s__, nlev, ilev, 
	    nlev_real__, mgsolv, &iok_s__, &iinfo_s__, epsiln, &errtol_s__, 
	    omega, &nu1_s__, &nu2_s__, &mgsmoo_s__, &ipc[1], &rpc[1], &pc[1], 
	    &ac[1], &cc[1], &w0[1], &tru[1]);
    xcopy_(nx, ny, nz, &u[iz[lev * 50 + 1]], &w1[1]);
/* * */
/* *       *** normalize the new vector *** */
    denom = xnrm2_(nx, ny, nz, &w1[1]);
    fac = 1.f / denom;
    xscal_(nx, ny, nz, &fac, &w1[1]);
/* * */
/* *       *** compute the new raleigh quotient *** */
    matvec_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &ac[
	    iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &w1[1], &w2[1]);
    rho = xdot_(nx, ny, nz, &w1[1], &w2[1]);
/* * */
/* *       *** stopping test *** */
/* *       *** w2=A*x, w1=x, stop = 2-norm(A*x-lamda*x) *** */
    xcopy_(nx, ny, nz, &w1[1], &w3[1]);
    xcopy_(nx, ny, nz, &w2[1], &w4[1]);
    xscal_(nx, ny, nz, &rho, &w3[1]);
    xaxpy_(nx, ny, nz, &c_b10, &w3[1], &w4[1]);
    error = xnrm2_(nx, ny, nz, &w4[1]);
    relerr = (d__1 = rho - oldrho, abs(d__1)) / abs(rho);
/* * */
/* *       *** i/o *** */
    if (*iinfo > 3) {
	s_wsfe(&io___32);
	do_fio(&c__1, "IPOWER: iter; error; relerr; estimate = ", (ftnlen)40);
	do_fio(&c__1, (char *)&(*iters), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&error, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&relerr, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rho, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (relerr < *tol || *iters == *itmax) {
	goto L99;
    }
    oldrho = rho;
    goto L20;
/* * */
/* *    *** return some stuff *** */
L99:
    *eigmin = rho;
    i__1 = *ilev - 1;
    fac = pow_ri(&c_b19, &i__1);
    *eigmin_model__ = fac * (6. - cos(pi / (doublereal) (*nx - 1)) * 2. - cos(
	    pi / (doublereal) (*ny - 1)) * 2. - cos(pi / (doublereal) (*nz - 
	    1)) * 2.);
/* * */
/* *    *** return and end *** */
    return 0;
} /* ipower_ */

/* Subroutine */ int mpower_(integer *nx, integer *ny, integer *nz, 
	doublereal *u, integer *iz, doublereal *w0, doublereal *w1, 
	doublereal *w2, doublereal *w3, doublereal *w4, doublereal *eigmax, 
	doublereal *tol, integer *itmax, integer *iters, integer *nlev, 
	integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, 
	integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *
	omega, integer *nu1, integer *nu2, integer *mgsmoo, integer *ipc, 
	doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, 
	doublereal *fc, doublereal *tru)
{
    /* Format strings */
    static char fmt_510[] = "(\002% \002,a,i5,1pe11.4)";
    static char fmt_500[] = "(\002% \002,a,i5,2(1pe9.2),1pe11.4)";

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer ierror_s__;
    static doublereal fac;
    static integer lev;
    static doublereal rho;
    extern /* Subroutine */ int mvcs_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    extern doublereal xdot_(integer *, integer *, integer *, doublereal *, 
	    doublereal *), xnrm2_(integer *, integer *, integer *, doublereal 
	    *);
    static doublereal denom;
    static integer iok_s__, level;
    extern /* Subroutine */ int xscal_(integer *, integer *, integer *, 
	    doublereal *, doublereal *);
    static doublereal error;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *), xaxpy_(integer *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *), axrand_(integer *, 
	    integer *, integer *, doublereal *);
    static doublereal oldrho, relerr;
    extern /* Subroutine */ int azeros_(integer *, integer *, integer *, 
	    doublereal *);
    static integer iinfo_s__, itmax_s__, iters_s__, istop_s__;

    /* Fortran I/O blocks */
    static cilist io___44 = { 0, 6, 0, fmt_510, 0 };
    static cilist io___48 = { 0, 6, 0, fmt_500, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    standard power method for maximimum eigenvalue estimation */
/* *    of the multigrid operator M. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** other declarations *** */
/* * */
/* *    *** some more *** */
/* * */
/* *    *** recover level information *** */
    /* Parameter adjustments */
    --tru;
    --fc;
    --cc;
    --ac;
    --pc;
    --rpc;
    --ipc;
    --w4;
    --w3;
    --w2;
    --w1;
    --w0;
    iz -= 51;
    --u;

    /* Function Body */
    level = 1;
    lev = *ilev - 1 + level;
/* * */
/* *    *** seed vector: random to contain all components *** */
    axrand_(nx, ny, nz, &w1[1]);
    azeros_(nx, ny, nz, &w2[1]);
    azeros_(nx, ny, nz, &w3[1]);
    azeros_(nx, ny, nz, &w4[1]);
    azeros_(nx, ny, nz, &u[iz[lev * 50 + 1]]);
/* * */
/* *    *** NOTE: we destroy "fc" on this level due to lack of vectors... *** */
    azeros_(nx, ny, nz, &fc[iz[lev * 50 + 1]]);
/* * */
/* *    *** normalize the seed vector *** */
    denom = xnrm2_(nx, ny, nz, &w1[1]);
    fac = 1.f / denom;
    xscal_(nx, ny, nz, &fac, &w1[1]);
/* * */
/* *    *** compute raleigh quotient with the seed vector *** */
    xcopy_(nx, ny, nz, &w1[1], &u[iz[lev * 50 + 1]]);
    itmax_s__ = 1;
    iters_s__ = 0;
    ierror_s__ = 0;
    iok_s__ = 0;
    iinfo_s__ = 0;
    istop_s__ = 1;
    mvcs_(nx, ny, nz, &u[1], &iz[51], &w0[1], &w2[1], &w3[1], &w4[1], &
	    istop_s__, &itmax_s__, &iters_s__, &ierror_s__, nlev, ilev, 
	    nlev_real__, mgsolv, &iok_s__, &iinfo_s__, epsiln, errtol, omega, 
	    nu1, nu2, mgsmoo, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1], &fc[1]
	    , &tru[1]);
    oldrho = xdot_(nx, ny, nz, &w1[1], &u[iz[lev * 50 + 1]]);
/* * */
/* *    *** i/o *** */
    if (oldrho == 0.f) {
	if (*iinfo > 3) {
	    s_wsfe(&io___44);
	    do_fio(&c__1, "MPOWER: iter; estimate = ", (ftnlen)25);
	    do_fio(&c__1, (char *)&(*iters), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&oldrho, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	rho = oldrho;
	goto L99;
    }
/* * */
/* *    *** main iteration *** */
    *iters = 0;
L20:
    ++(*iters);
/* * */
/* *       *** apply the matrix M *** */
    xcopy_(nx, ny, nz, &w1[1], &u[iz[lev * 50 + 1]]);
    itmax_s__ = 1;
    iters_s__ = 0;
    ierror_s__ = 0;
    iok_s__ = 0;
    iinfo_s__ = 0;
    istop_s__ = 1;
    mvcs_(nx, ny, nz, &u[1], &iz[51], &w1[1], &w2[1], &w3[1], &w4[1], &
	    istop_s__, &itmax_s__, &iters_s__, &ierror_s__, nlev, ilev, 
	    nlev_real__, mgsolv, &iok_s__, &iinfo_s__, epsiln, errtol, omega, 
	    nu1, nu2, mgsmoo, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1], &fc[1]
	    , &tru[1]);
    xcopy_(nx, ny, nz, &u[iz[lev * 50 + 1]], &w1[1]);
/* * */
/* *       *** normalize the new vector *** */
    denom = xnrm2_(nx, ny, nz, &w1[1]);
    fac = 1.f / denom;
    xscal_(nx, ny, nz, &fac, &w1[1]);
/* * */
/* *       *** compute the new raleigh quotient *** */
    xcopy_(nx, ny, nz, &w1[1], &u[iz[lev * 50 + 1]]);
    itmax_s__ = 1;
    iters_s__ = 0;
    ierror_s__ = 0;
    iok_s__ = 0;
    iinfo_s__ = 0;
    istop_s__ = 1;
    mvcs_(nx, ny, nz, &u[1], &iz[51], &w0[1], &w2[1], &w3[1], &w4[1], &
	    istop_s__, &itmax_s__, &iters_s__, &ierror_s__, nlev, ilev, 
	    nlev_real__, mgsolv, &iok_s__, &iinfo_s__, epsiln, errtol, omega, 
	    nu1, nu2, mgsmoo, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1], &fc[1]
	    , &tru[1]);
    xcopy_(nx, ny, nz, &u[iz[lev * 50 + 1]], &w2[1]);
    rho = xdot_(nx, ny, nz, &w1[1], &w2[1]);
/* * */
/* *       *** stopping test *** */
/* *       *** w2=A*x, w1=x, stop = 2-norm(A*x-lamda*x) *** */
    xcopy_(nx, ny, nz, &w1[1], &w3[1]);
    xcopy_(nx, ny, nz, &w2[1], &w4[1]);
    xscal_(nx, ny, nz, &rho, &w3[1]);
    xaxpy_(nx, ny, nz, &c_b10, &w3[1], &w4[1]);
    error = xnrm2_(nx, ny, nz, &w4[1]);
    relerr = (d__1 = rho - oldrho, abs(d__1)) / abs(rho);
/* * */
/* *       *** i/o *** */
    if (*iinfo > 3) {
	s_wsfe(&io___48);
	do_fio(&c__1, "MPOWER: iter; error; relerr; estimate = ", (ftnlen)40);
	do_fio(&c__1, (char *)&(*iters), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&error, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&relerr, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rho, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (relerr < *tol || *iters == *itmax) {
	goto L99;
    }
    oldrho = rho;
    goto L20;
/* * */
/* *    *** return some stuff *** */
L99:
    *eigmax = rho;
/* * */
/* *    *** return and end *** */
    return 0;
} /* mpower_ */

