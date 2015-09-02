/* ./src_f77/nsord.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__3 = 3;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    nsord.f */
/* * @author  Michael Holst */
/* * @brief   Nonlinear SOR iteration. */
/* * @version $Id: nsord.c,v 1.3 2010/08/12 05:45:27 fetk Exp $ */
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
/* Subroutine */ int nsor_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, 
	doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, 
	integer *itmax, integer *iters, doublereal *errtol, doublereal *omega,
	 integer *iresid, integer *iadjoint)
{
    /* System generated locals */
    integer ac_dim1, ac_offset, cc_dim1, cc_dim2, cc_offset, fc_dim1, fc_dim2,
	     fc_offset, x_dim1, x_dim2, x_offset, w1_dim1, w1_dim2, w1_offset,
	     w2_dim1, w2_dim2, w2_offset, r_dim1, r_dim2, r_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int nsor7_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, integer *), nsor27_(
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, doublereal *, doublereal *, integer *, integer *);
    static integer numdia;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    call the fast diagonal iterative method. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in one step *** */
    /* Parameter adjustments */
    r_dim1 = *nx;
    r_dim2 = *ny;
    r_offset = 1 + r_dim1 * (1 + r_dim2);
    r__ -= r_offset;
    w2_dim1 = *nx;
    w2_dim2 = *ny;
    w2_offset = 1 + w2_dim1 * (1 + w2_dim2);
    w2 -= w2_offset;
    w1_dim1 = *nx;
    w1_dim2 = *ny;
    w1_offset = 1 + w1_dim1 * (1 + w1_dim2);
    w1 -= w1_offset;
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;
    fc_dim1 = *nx;
    fc_dim2 = *ny;
    fc_offset = 1 + fc_dim1 * (1 + fc_dim2);
    fc -= fc_offset;
    cc_dim1 = *nx;
    cc_dim2 = *ny;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
    cc -= cc_offset;
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;

    /* Function Body */
    numdia = ipc[11];
    if (numdia == 7) {
	nsor7_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[cc_offset],
		 &fc[fc_offset], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1]
		, &ac[(ac_dim1 << 2) + 1], &x[x_offset], &w1[w1_offset], &w2[
		w2_offset], &r__[r_offset], itmax, iters, errtol, omega, 
		iresid, iadjoint);
    } else if (numdia == 27) {
	nsor27_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[cc_offset]
		, &fc[fc_offset], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 
		1], &ac[(ac_dim1 << 2) + 1], &ac[ac_dim1 * 5 + 1], &ac[
		ac_dim1 * 6 + 1], &ac[ac_dim1 * 7 + 1], &ac[(ac_dim1 << 3) + 
		1], &ac[ac_dim1 * 9 + 1], &ac[ac_dim1 * 10 + 1], &ac[ac_dim1 *
		 11 + 1], &ac[ac_dim1 * 12 + 1], &ac[ac_dim1 * 13 + 1], &ac[
		ac_dim1 * 14 + 1], &x[x_offset], &w1[w1_offset], &w2[
		w2_offset], &r__[r_offset], itmax, iters, errtol, omega, 
		iresid, iadjoint);
    } else {
	s_wsle(&io___2);
	do_lio(&c__9, &c__1, "% NSOR: invalid stencil type given...", (ftnlen)
		37);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* nsor_ */

/* Subroutine */ int nsor7_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, 
	doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, 
	doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, 
	integer *iters, doublereal *errtol, doublereal *omega, integer *
	iresid, integer *iadjoint)
{
    /* System generated locals */
    integer oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1,
	     uc_dim2, uc_offset, fc_dim1, fc_dim2, fc_offset, oc_dim1, 
	    oc_dim2, oc_offset, cc_dim1, cc_dim2, cc_offset, x_dim1, x_dim2, 
	    x_offset, w1_dim1, w1_dim2, w1_offset, w2_dim1, w2_dim2, 
	    w2_offset, r_dim1, r_dim2, r_offset, i__1, i__2, i__3, i__4;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j, k, ifail_tol__;
    static doublereal aa, bb, ff, uu;
    extern /* Subroutine */ int nmresid7_1s__(integer *, integer *, integer *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal fac, znn;
    static integer ioff;
    static doublereal dznn;
    static integer ipkey;
    static doublereal zntol;
    extern doublereal c_scal__(doublereal *, doublereal *, integer *);
    static doublereal change;
    static integer nitmax, niters;
    extern doublereal dc_scal__(doublereal *, doublereal *, integer *);
    static doublereal zndenom, znerror;

    /* Fortran I/O blocks */
    static cilist io___22 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    fast 7 diagonal nonlinear red/black sor routine. */
/* * */
/* *    note that the interior grid points from 2,...,nx-1, etc. */
/* *    we then begin coloring with a red point, and do a point red/black */
/* *    coloring. */
/* * */
/* *    the red points are: */
/* * */
/* *       if ((j even) and (k even)) then */
/* *          begin row at first point, i=2 (i even), or ioff = 0 */
/* *       else if ((j odd) and (k even)) then */
/* *          begin row at second point, i=3 (i odd), or ioff = 1 */
/* *       else if ((j even) and (k odd)) then */
/* *          begin row at second point, i=3 (i odd), or ioff = 1 */
/* *       else if ((j odd) and (k odd)) then */
/* *          begin row at first point, i=2 (i even), or ioff = 0 */
/* *       endif */
/* *       then: begin row at:  i=2+ioff */
/* * */
/* *    the appropriate ioff function for the red points is then: */
/* *         ioff = dabs(mod(j,2)-mod(k,2)) */
/* * */
/* *    the appropriate ioff function for the black points is then: */
/* *         ioff = 1 - dabs(mod(j,2)-mod(k,2)) */
/* * */
/* * */
/* *    alternatively, the red points are: */
/* * */
/* *       those whose indices add up to an even number. */
/* *       to see this, consider that all surrounding points are */
/* *       only one index different, hence the sum will differ by one. */
/* *       thus, if a given point has an even sum, then the surrounding */
/* *       points will have an odd sum. */
/* * */
/* *    thus, the black points are: */
/* * */
/* *       therefore those whose indices add up to an odd number. */
/* * */
/* * algorithm parameters: */
/* * --------------------- */
/* * */
/* *    U0      = initial guess */
/* *    Llin    = matrix representing linear part of equations */
/* *    F       = vector representing rhs of equations */
/* *    nx      = number of unknowns */
/* *    itmax   = number of iterations to perform */
/* *    c_scal  = function representing nonlinear part of equations */
/* *    dc_scal = function representing derivative of nonlinear */
/* *              part of equations */
/* *    U       = final result */
/* * */
/* * algorithm idea: */
/* * --------------- */
/* * */
/* *    the ith nonlinear equation is represented as: */
/* * */
/* *       N(UU) = AA * UU + c_scal(UU) - FF */
/* * */
/* *    which is solved for UU using newton's method, where: */
/* * */
/* *       AA = ith diagonal entry of Llin */
/* *       FF = F(i), minus the nondiag of ith eqn of Llin times current U */
/* *       UU = the unknown, initialized to U(i) */
/* * */
/* * algorithm (matlab language): */
/* * ---------------------------- */
/* * */
/* * function [U,iterss,errors] = Zgs(U0,UTRUE,a,b,Llin,F,nx,tol,itmax,stp,plt); */
/* * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* * %%% nonlinear sor-newton iteration (ortega-rheinboldt, page 219) */
/* * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* * */
/* * %%% initial guess */
/* * iters = 0; */
/* * error = 1.0d0; */
/* * U     = U0; */
/* * Lnon  = c_vec(b,U,nx); */
/* * N     = Llin * U + Lnon - F ; */
/* * denom = 1.0d0; if (stp == 1) denom = norm(N); end; */
/* * */
/* * %%% loop */
/* * while ((error > tol) & (iters < itmax)) */
/* *    iters = iters + 1; */
/* * */
/* *    %%% save old guys */
/* *    Lnon_OLD = Lnon; */
/* *    U_OLD    = U; */
/* * */
/* *    %%% relax each unknown */
/* *    for i = 1:nx */
/* * */
/* *       %%% define the 1d rhs */
/* *       FF = F(i) - Llin(i,1:nx) * U + Llin(i,i) * U(i); */
/* *       AA = Llin(i,i); */
/* *       UU = U(i); */
/* *       BB = b(i); */
/* * */
/* *       %%% perform 1d newton's method */
/* *       %%% note that in the linear case, this is equivalent to:  FF/AA */
/* *       nitmax = 10; */
/* *       ntol   = 1.0e-7; */
/* *       niters = 0; */
/* *       N      = AA * UU + c_scal(BB,UU) - FF ; */
/* *       ndenom = N; */
/* *       if (ndenom == 0) */
/* *          ndenom = 1; */
/* *       end; */
/* *       nerror = N / ndenom; */
/* * */
/* *       while ((nerror > ntol) & (niters < nitmax)) */
/* *          niters = niters + 1; */
/* * */
/* *          %%% construct jacobian matrix of N */
/* *          DN = AA + dc_scal(BB,UU); */
/* * */
/* *          %%% solve linear system */
/* *          change = - N / DN; */
/* * */
/* *          %%% update solution */
/* *          UU = UU + change; */
/* * */
/* *          %%% construct nonlinear residual */
/* *          N = AA * UU + c_scal(BB,UU) - FF ; */
/* * */
/* *          %%% compute residual */
/* *          nerror = N / ndenom; */
/* *       end */
/* * */
/* *       %%% update the unknown */
/* *       U(i) = UU; */
/* *    end */
/* * */
/* *    %%% new residual %%% */
/* *    Lnon  = c_vec(b,U,nx); */
/* *    N     = Llin * U + Lnon - F ; */
/* *    delta = zeros(U); */
/* *    delta_s = zeros(U); */
/* * */
/* * end */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** nonlinear iteration tolerance and itmax *** */
    /* Parameter adjustments */
    r_dim1 = *nx;
    r_dim2 = *ny;
    r_offset = 1 + r_dim1 * (1 + r_dim2);
    r__ -= r_offset;
    w2_dim1 = *nx;
    w2_dim2 = *ny;
    w2_offset = 1 + w2_dim1 * (1 + w2_dim2);
    w2 -= w2_offset;
    w1_dim1 = *nx;
    w1_dim2 = *ny;
    w1_offset = 1 + w1_dim1 * (1 + w1_dim2);
    w1 -= w1_offset;
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;
    uc_dim1 = *nx;
    uc_dim2 = *ny;
    uc_offset = 1 + uc_dim1 * (1 + uc_dim2);
    uc -= uc_offset;
    on_dim1 = *nx;
    on_dim2 = *ny;
    on_offset = 1 + on_dim1 * (1 + on_dim2);
    on -= on_offset;
    oe_dim1 = *nx;
    oe_dim2 = *ny;
    oe_offset = 1 + oe_dim1 * (1 + oe_dim2);
    oe -= oe_offset;
    fc_dim1 = *nx;
    fc_dim2 = *ny;
    fc_offset = 1 + fc_dim1 * (1 + fc_dim2);
    fc -= fc_offset;
    cc_dim1 = *nx;
    cc_dim2 = *ny;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
    cc -= cc_offset;
    oc_dim1 = *nx;
    oc_dim2 = *ny;
    oc_offset = 1 + oc_dim1 * (1 + oc_dim2);
    oc -= oc_offset;
    --ipc;
    --rpc;

    /* Function Body */
    nitmax = 10;
    zntol = 1e-5f;
    ifail_tol__ = 0;
    ipkey = ipc[10];
/* * */
/* *    *** do the sor iteration itmax times *** */
    fac = 1. - *omega;
    i__1 = *itmax;
    for (*iters = 1; *iters <= i__1; ++(*iters)) {
/* * */
/* *       *** do the red points *** */
/* mdir 3 1 */
	i__2 = *nz - 1;
	for (k = 2; k <= i__2; ++k) {
/* mdir 3 2 */
	    i__3 = *ny - 1;
	    for (j = 2; j <= i__3; ++j) {
		ioff = (j + k + 2) % 2;
/* mdir 3 3 */
		i__4 = *nx - 1;
		for (i__ = ioff + 2; i__ <= i__4; i__ += 2) {
/* * */
/* *                *** for this unknown, do a 1d newton's method */
/* * */
/* *                *** determine the 1d equation */
		    uu = x[i__ + (j + k * x_dim2) * x_dim1];
		    aa = oc[i__ + (j + k * oc_dim2) * oc_dim1];
		    bb = cc[i__ + (j + k * cc_dim2) * cc_dim1];
		    ff = fc[i__ + (j + k * fc_dim2) * fc_dim1] + on[i__ + (j 
			    + k * on_dim2) * on_dim1] * x[i__ + (j + 1 + k * 
			    x_dim2) * x_dim1] + on[i__ + (j - 1 + k * on_dim2)
			     * on_dim1] * x[i__ + (j - 1 + k * x_dim2) * 
			    x_dim1] + oe[i__ + (j + k * oe_dim2) * oe_dim1] * 
			    x[i__ + 1 + (j + k * x_dim2) * x_dim1] + oe[i__ - 
			    1 + (j + k * oe_dim2) * oe_dim1] * x[i__ - 1 + (j 
			    + k * x_dim2) * x_dim1] + uc[i__ + (j + (k - 1) * 
			    uc_dim2) * uc_dim1] * x[i__ + (j + (k - 1) * 
			    x_dim2) * x_dim1] + uc[i__ + (j + k * uc_dim2) * 
			    uc_dim1] * x[i__ + (j + (k + 1) * x_dim2) * 
			    x_dim1];
/* * */
/* *                *** evaluate residual of 1d system */
		    znn = aa * uu + c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** setup for newton's method */
		    niters = 0;
		    zndenom = znn;
		    if (zndenom == 0.) {
			zndenom = 1.;
		    }
		    znerror = znn / zndenom;
/* * */
/* *                *** the 1d newton's method *** */
		    if (znerror < zntol) {
			goto L17;
		    }
		    if (niters > nitmax) {
			goto L16;
		    }
L15:
		    ++niters;
/* * */
/* *                   *** construct jacobian matrix of NN *** */
		    dznn = aa + dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                   *** solve the linear system *** */
		    change = -znn / dznn;
/* * */
/* *                   *** update the solution *** */
		    uu += change;
/* * */
/* *                   *** evaluate residual of 1d system *** */
		    znn = aa * uu + c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                   *** compute error *** */
		    znerror = znn / zndenom;
/* * */
/* *                   *** tolerance and itmax check *** */
		    if (znerror < zntol) {
			goto L17;
		    }
		    if (niters > nitmax) {
			goto L16;
		    }
/* * */
/* *                *** loop *** */
		    goto L15;
/* * */
/* *                *** tolerance not reached *** */
L16:
		    ++ifail_tol__;
/* * */
/* *                *** tolerance reached *** */
L17:
/* * */
/* *                *** newton's method complete -- update solution value *** */
		    x[i__ + (j + k * x_dim2) * x_dim1] = x[i__ + (j + k * 
			    x_dim2) * x_dim1] * fac + *omega * uu;
/* L12: */
		}
/* L11: */
	    }
/* L10: */
	}
/* * */
/* *       *** do the black points *** */
/* mdir 3 1 */
	i__2 = *nz - 1;
	for (k = 2; k <= i__2; ++k) {
/* mdir 3 2 */
	    i__3 = *ny - 1;
	    for (j = 2; j <= i__3; ++j) {
		ioff = 1 - (j + k + 2) % 2;
/* mdir 3 3 */
		i__4 = *nx - 1;
		for (i__ = ioff + 2; i__ <= i__4; i__ += 2) {
/* * */
/* *                *** for this unknown, do a 1d newton's method */
/* * */
/* *                *** determine the 1d equation */
		    uu = x[i__ + (j + k * x_dim2) * x_dim1];
		    aa = oc[i__ + (j + k * oc_dim2) * oc_dim1];
		    bb = cc[i__ + (j + k * cc_dim2) * cc_dim1];
		    ff = fc[i__ + (j + k * fc_dim2) * fc_dim1] + on[i__ + (j 
			    + k * on_dim2) * on_dim1] * x[i__ + (j + 1 + k * 
			    x_dim2) * x_dim1] + on[i__ + (j - 1 + k * on_dim2)
			     * on_dim1] * x[i__ + (j - 1 + k * x_dim2) * 
			    x_dim1] + oe[i__ + (j + k * oe_dim2) * oe_dim1] * 
			    x[i__ + 1 + (j + k * x_dim2) * x_dim1] + oe[i__ - 
			    1 + (j + k * oe_dim2) * oe_dim1] * x[i__ - 1 + (j 
			    + k * x_dim2) * x_dim1] + uc[i__ + (j + (k - 1) * 
			    uc_dim2) * uc_dim1] * x[i__ + (j + (k - 1) * 
			    x_dim2) * x_dim1] + uc[i__ + (j + k * uc_dim2) * 
			    uc_dim1] * x[i__ + (j + (k + 1) * x_dim2) * 
			    x_dim1];
/* * */
/* *                *** evaluate residual of 1d system */
		    znn = aa * uu + c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** setup for newton's method */
		    niters = 0;
		    zndenom = znn;
		    if (zndenom == 0.) {
			zndenom = 1.;
		    }
		    znerror = znn / zndenom;
/* * */
/* *                *** the 1d newton's method *** */
		    if (znerror < zntol) {
			goto L27;
		    }
		    if (niters > nitmax) {
			goto L26;
		    }
L25:
		    ++niters;
/* * */
/* *                   *** construct jacobian matrix of NN *** */
		    dznn = aa + dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                   *** solve the linear system *** */
		    change = -znn / dznn;
/* * */
/* *                   *** update the solution *** */
		    uu += change;
/* * */
/* *                   *** evaluate residual of 1d system *** */
		    znn = aa * uu + c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                   *** compute error *** */
		    znerror = znn / zndenom;
/* * */
/* *                   *** tolerance and itmax check *** */
		    if (znerror < zntol) {
			goto L27;
		    }
		    if (niters > nitmax) {
			goto L26;
		    }
/* * */
/* *                *** loop *** */
		    goto L25;
/* * */
/* *                *** tolerance not reached *** */
L26:
		    ++ifail_tol__;
/* * */
/* *                *** tolerance reached *** */
L27:
/* * */
/* *                *** newton's method complete -- update solution value *** */
		    x[i__ + (j + k * x_dim2) * x_dim1] = x[i__ + (j + k * 
			    x_dim2) * x_dim1] * fac + *omega * uu;
/* L22: */
		}
/* L21: */
	    }
/* L20: */
	}
/* * */
/* *       *** main loop *** */
/* L30: */
    }
/* * */
/* *    *** if specified, return the new residual as well *** */
    if (*iresid == 1) {
	nmresid7_1s__(nx, ny, nz, &ipc[1], &rpc[1], &oc[oc_offset], &cc[
		cc_offset], &fc[fc_offset], &oe[oe_offset], &on[on_offset], &
		uc[uc_offset], &x[x_offset], &r__[r_offset], &w1[w1_offset]);
    }
/* * */
/* *    *** messages *** */
    if (ifail_tol__ > 0) {
	s_wsle(&io___22);
	do_lio(&c__9, &c__1, "% NSOR: 1d newton tolerance failures:     ", (
		ftnlen)42);
	do_lio(&c__3, &c__1, (char *)&ifail_tol__, (ftnlen)sizeof(integer));
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* nsor7_ */

/* Subroutine */ int nsor27_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, 
	doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, 
	doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, 
	doublereal *us, doublereal *une, doublereal *unw, doublereal *use, 
	doublereal *usw, doublereal *x, doublereal *w1, doublereal *w2, 
	doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, 
	doublereal *omega, integer *iresid, integer *iadjoint)
{
    /* System generated locals */
    integer oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1,
	     uc_dim2, uc_offset, one_dim1, one_dim2, one_offset, onw_dim1, 
	    onw_dim2, onw_offset, ue_dim1, ue_dim2, ue_offset, uw_dim1, 
	    uw_dim2, uw_offset, un_dim1, un_dim2, un_offset, us_dim1, us_dim2,
	     us_offset, une_dim1, une_dim2, une_offset, unw_dim1, unw_dim2, 
	    unw_offset, use_dim1, use_dim2, use_offset, usw_dim1, usw_dim2, 
	    usw_offset, fc_dim1, fc_dim2, fc_offset, oc_dim1, oc_dim2, 
	    oc_offset, cc_dim1, cc_dim2, cc_offset, x_dim1, x_dim2, x_offset, 
	    w1_dim1, w1_dim2, w1_offset, w2_dim1, w2_dim2, w2_offset, r_dim1, 
	    r_dim2, r_offset, i__1, i__2, i__3, i__4;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j, k, ifail_tol__;
    static doublereal aa, bb, ff, uu, fac;
    extern /* Subroutine */ int nmresid27_1s__(integer *, integer *, integer *
	    , integer *, doublereal *, doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal znn, tmpd, dznn, tmpo, tmpu;
    static integer ipkey;
    static doublereal zntol;
    extern doublereal c_scal__(doublereal *, doublereal *, integer *);
    static doublereal change;
    static integer nitmax, niters;
    extern doublereal dc_scal__(doublereal *, doublereal *, integer *);
    static doublereal zndenom, znerror;

    /* Fortran I/O blocks */
    static cilist io___44 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    27 diagonal nonlinear sor routine. */
/* * */
/* * algorithm parameters: */
/* * --------------------- */
/* * */
/* *    U0      = initial guess */
/* *    Llin    = matrix representing linear part of equations */
/* *    F       = vector representing rhs of equations */
/* *    nx      = number of unknowns */
/* *    itmax   = number of iterations to perform */
/* *    c_scal  = function representing nonlinear part of equations */
/* *    dc_scal = function representing derivative of nonlinear */
/* *              part of equations */
/* *    U       = final result */
/* * */
/* * algorithm idea: */
/* * --------------- */
/* * */
/* *    the ith nonlinear equation is represented as: */
/* * */
/* *       N(UU) = AA * UU + c_scal(UU) - FF */
/* * */
/* *    which is solved for UU using newton's method, where: */
/* * */
/* *       AA = ith diagonal entry of Llin */
/* *       FF = F(i), minus the nondiag of ith eqn of Llin times current U */
/* *       UU = the unknown, initialized to U(i) */
/* * */
/* * algorithm (matlab language): */
/* * ---------------------------- */
/* * */
/* * function [U,iterss,errors] = Zgs(U0,UTRUE,a,b,Llin,F,nx,tol,itmax,stp,plt); */
/* * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* * %%% nonlinear sor-newton iteration (ortega-rheinboldt, page 219) */
/* * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* * */
/* * %%% initial guess */
/* * iters = 0; */
/* * error = 1.0d0; */
/* * U     = U0; */
/* * Lnon  = c_vec(b,U,nx); */
/* * N     = Llin * U + Lnon - F ; */
/* * denom = 1.0d0; if (stp == 1) denom = norm(N); end; */
/* * */
/* * %%% loop */
/* * while ((error > tol) & (iters < itmax)) */
/* *    iters = iters + 1; */
/* * */
/* *    %%% save old guys */
/* *    Lnon_OLD = Lnon; */
/* *    U_OLD    = U; */
/* * */
/* *    %%% relax each unknown */
/* *    for i = 1:nx */
/* * */
/* *       %%% define the 1d rhs */
/* *       FF = F(i) - Llin(i,1:nx) * U + Llin(i,i) * U(i); */
/* *       AA = Llin(i,i); */
/* *       UU = U(i); */
/* *       BB = b(i); */
/* * */
/* *       %%% perform 1d newton's method */
/* *       %%% note that in the linear case, this is equivalent to:  FF/AA */
/* *       nitmax = 10; */
/* *       ntol   = 1.0e-7; */
/* *       niters = 0; */
/* *       N      = AA * UU + c_scal(BB,UU) - FF ; */
/* *       ndenom = N; */
/* *       if (ndenom == 0) */
/* *          ndenom = 1; */
/* *       end; */
/* *       nerror = N / ndenom; */
/* * */
/* *       while ((nerror > ntol) & (niters < nitmax)) */
/* *          niters = niters + 1; */
/* * */
/* *          %%% construct jacobian matrix of N */
/* *          DN = AA + dc_scal(BB,UU); */
/* * */
/* *          %%% solve linear system */
/* *          change = - N / DN; */
/* * */
/* *          %%% update solution */
/* *          UU = UU + change; */
/* * */
/* *          %%% construct nonlinear residual */
/* *          N = AA * UU + c_scal(BB,UU) - FF ; */
/* * */
/* *          %%% compute residual */
/* *          nerror = N / ndenom; */
/* *       end */
/* * */
/* *       %%% update the unknown */
/* *       U(i) = UU; */
/* *    end */
/* * */
/* *    %%% new residual %%% */
/* *    Lnon  = c_vec(b,U,nx); */
/* *    N     = Llin * U + Lnon - F ; */
/* *    delta = zeros(U); */
/* *    delta_s = zeros(U); */
/* * */
/* * end */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** nonlinear iteration tolerance and itmax *** */
    /* Parameter adjustments */
    r_dim1 = *nx;
    r_dim2 = *ny;
    r_offset = 1 + r_dim1 * (1 + r_dim2);
    r__ -= r_offset;
    w2_dim1 = *nx;
    w2_dim2 = *ny;
    w2_offset = 1 + w2_dim1 * (1 + w2_dim2);
    w2 -= w2_offset;
    w1_dim1 = *nx;
    w1_dim2 = *ny;
    w1_offset = 1 + w1_dim1 * (1 + w1_dim2);
    w1 -= w1_offset;
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;
    usw_dim1 = *nx;
    usw_dim2 = *ny;
    usw_offset = 1 + usw_dim1 * (1 + usw_dim2);
    usw -= usw_offset;
    use_dim1 = *nx;
    use_dim2 = *ny;
    use_offset = 1 + use_dim1 * (1 + use_dim2);
    use -= use_offset;
    unw_dim1 = *nx;
    unw_dim2 = *ny;
    unw_offset = 1 + unw_dim1 * (1 + unw_dim2);
    unw -= unw_offset;
    une_dim1 = *nx;
    une_dim2 = *ny;
    une_offset = 1 + une_dim1 * (1 + une_dim2);
    une -= une_offset;
    us_dim1 = *nx;
    us_dim2 = *ny;
    us_offset = 1 + us_dim1 * (1 + us_dim2);
    us -= us_offset;
    un_dim1 = *nx;
    un_dim2 = *ny;
    un_offset = 1 + un_dim1 * (1 + un_dim2);
    un -= un_offset;
    uw_dim1 = *nx;
    uw_dim2 = *ny;
    uw_offset = 1 + uw_dim1 * (1 + uw_dim2);
    uw -= uw_offset;
    ue_dim1 = *nx;
    ue_dim2 = *ny;
    ue_offset = 1 + ue_dim1 * (1 + ue_dim2);
    ue -= ue_offset;
    onw_dim1 = *nx;
    onw_dim2 = *ny;
    onw_offset = 1 + onw_dim1 * (1 + onw_dim2);
    onw -= onw_offset;
    one_dim1 = *nx;
    one_dim2 = *ny;
    one_offset = 1 + one_dim1 * (1 + one_dim2);
    one -= one_offset;
    uc_dim1 = *nx;
    uc_dim2 = *ny;
    uc_offset = 1 + uc_dim1 * (1 + uc_dim2);
    uc -= uc_offset;
    on_dim1 = *nx;
    on_dim2 = *ny;
    on_offset = 1 + on_dim1 * (1 + on_dim2);
    on -= on_offset;
    oe_dim1 = *nx;
    oe_dim2 = *ny;
    oe_offset = 1 + oe_dim1 * (1 + oe_dim2);
    oe -= oe_offset;
    fc_dim1 = *nx;
    fc_dim2 = *ny;
    fc_offset = 1 + fc_dim1 * (1 + fc_dim2);
    fc -= fc_offset;
    cc_dim1 = *nx;
    cc_dim2 = *ny;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
    cc -= cc_offset;
    oc_dim1 = *nx;
    oc_dim2 = *ny;
    oc_offset = 1 + oc_dim1 * (1 + oc_dim2);
    oc -= oc_offset;
    --ipc;
    --rpc;

    /* Function Body */
    nitmax = 10;
    zntol = 1e-5f;
    ifail_tol__ = 0;
    ipkey = ipc[10];
/* * */
/* *    *** do the sor iteration itmax times *** */
    fac = 1. - *omega;
    i__1 = *itmax;
    for (*iters = 1; *iters <= i__1; ++(*iters)) {
/* * */
/* *       *** do all of the points *** */
/* mdir 3 1 */
	i__2 = *nz - 1;
	for (k = 2; k <= i__2; ++k) {
/* mdir 3 2 */
	    i__3 = *ny - 1;
	    for (j = 2; j <= i__3; ++j) {
/* mdir 3 3 */
		i__4 = *nx - 1;
		for (i__ = 2; i__ <= i__4; ++i__) {
/* * */
/* *                *** for this unknown, do a 1d newton's method */
/* * */
/* *                *** determine the 1d equation */
		    uu = x[i__ + (j + k * x_dim2) * x_dim1];
		    aa = oc[i__ + (j + k * oc_dim2) * oc_dim1];
		    bb = cc[i__ + (j + k * cc_dim2) * cc_dim1];
		    tmpo = on[i__ + (j + k * on_dim2) * on_dim1] * x[i__ + (j 
			    + 1 + k * x_dim2) * x_dim1] + on[i__ + (j - 1 + k 
			    * on_dim2) * on_dim1] * x[i__ + (j - 1 + k * 
			    x_dim2) * x_dim1] + oe[i__ + (j + k * oe_dim2) * 
			    oe_dim1] * x[i__ + 1 + (j + k * x_dim2) * x_dim1] 
			    + oe[i__ - 1 + (j + k * oe_dim2) * oe_dim1] * x[
			    i__ - 1 + (j + k * x_dim2) * x_dim1] + one[i__ + (
			    j + k * one_dim2) * one_dim1] * x[i__ + 1 + (j + 
			    1 + k * x_dim2) * x_dim1] + onw[i__ + (j + k * 
			    onw_dim2) * onw_dim1] * x[i__ - 1 + (j + 1 + k * 
			    x_dim2) * x_dim1] + onw[i__ + 1 + (j - 1 + k * 
			    onw_dim2) * onw_dim1] * x[i__ + 1 + (j - 1 + k * 
			    x_dim2) * x_dim1] + one[i__ - 1 + (j - 1 + k * 
			    one_dim2) * one_dim1] * x[i__ - 1 + (j - 1 + k * 
			    x_dim2) * x_dim1];
		    tmpu = uc[i__ + (j + k * uc_dim2) * uc_dim1] * x[i__ + (j 
			    + (k + 1) * x_dim2) * x_dim1] + un[i__ + (j + k * 
			    un_dim2) * un_dim1] * x[i__ + (j + 1 + (k + 1) * 
			    x_dim2) * x_dim1] + us[i__ + (j + k * us_dim2) * 
			    us_dim1] * x[i__ + (j - 1 + (k + 1) * x_dim2) * 
			    x_dim1] + ue[i__ + (j + k * ue_dim2) * ue_dim1] * 
			    x[i__ + 1 + (j + (k + 1) * x_dim2) * x_dim1] + uw[
			    i__ + (j + k * uw_dim2) * uw_dim1] * x[i__ - 1 + (
			    j + (k + 1) * x_dim2) * x_dim1] + une[i__ + (j + 
			    k * une_dim2) * une_dim1] * x[i__ + 1 + (j + 1 + (
			    k + 1) * x_dim2) * x_dim1] + unw[i__ + (j + k * 
			    unw_dim2) * unw_dim1] * x[i__ - 1 + (j + 1 + (k + 
			    1) * x_dim2) * x_dim1] + use[i__ + (j + k * 
			    use_dim2) * use_dim1] * x[i__ + 1 + (j - 1 + (k + 
			    1) * x_dim2) * x_dim1] + usw[i__ + (j + k * 
			    usw_dim2) * usw_dim1] * x[i__ - 1 + (j - 1 + (k + 
			    1) * x_dim2) * x_dim1];
		    tmpd = uc[i__ + (j + (k - 1) * uc_dim2) * uc_dim1] * x[
			    i__ + (j + (k - 1) * x_dim2) * x_dim1] + us[i__ + 
			    (j + 1 + (k - 1) * us_dim2) * us_dim1] * x[i__ + (
			    j + 1 + (k - 1) * x_dim2) * x_dim1] + un[i__ + (j 
			    - 1 + (k - 1) * un_dim2) * un_dim1] * x[i__ + (j 
			    - 1 + (k - 1) * x_dim2) * x_dim1] + uw[i__ + 1 + (
			    j + (k - 1) * uw_dim2) * uw_dim1] * x[i__ + 1 + (
			    j + (k - 1) * x_dim2) * x_dim1] + ue[i__ - 1 + (j 
			    + (k - 1) * ue_dim2) * ue_dim1] * x[i__ - 1 + (j 
			    + (k - 1) * x_dim2) * x_dim1] + usw[i__ + 1 + (j 
			    + 1 + (k - 1) * usw_dim2) * usw_dim1] * x[i__ + 1 
			    + (j + 1 + (k - 1) * x_dim2) * x_dim1] + use[i__ 
			    - 1 + (j + 1 + (k - 1) * use_dim2) * use_dim1] * 
			    x[i__ - 1 + (j + 1 + (k - 1) * x_dim2) * x_dim1] 
			    + unw[i__ + 1 + (j - 1 + (k - 1) * unw_dim2) * 
			    unw_dim1] * x[i__ + 1 + (j - 1 + (k - 1) * x_dim2)
			     * x_dim1] + une[i__ - 1 + (j - 1 + (k - 1) * 
			    une_dim2) * une_dim1] * x[i__ - 1 + (j - 1 + (k - 
			    1) * x_dim2) * x_dim1];
		    ff = fc[i__ + (j + k * fc_dim2) * fc_dim1] + tmpo + tmpu 
			    + tmpd;
/* * */
/* *                *** evaluate residual of 1d system */
		    znn = aa * uu + c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** setup for newton's method */
		    niters = 0;
		    zndenom = znn;
		    if (zndenom == 0.) {
			zndenom = 1.;
		    }
		    znerror = znn / zndenom;
/* * */
/* *                *** the 1d newton's method *** */
		    if (znerror < zntol) {
			goto L17;
		    }
		    if (niters > nitmax) {
			goto L16;
		    }
L15:
		    ++niters;
/* * */
/* *                   *** construct jacobian matrix of NN *** */
		    dznn = aa + dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                   *** solve the linear system *** */
		    change = -znn / dznn;
/* * */
/* *                   *** update the solution *** */
		    uu += change;
/* * */
/* *                   *** evaluate residual of 1d system *** */
		    znn = aa * uu + c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                   *** compute error *** */
		    znerror = znn / zndenom;
/* * */
/* *                   *** tolerance and itmax check *** */
		    if (znerror < zntol) {
			goto L17;
		    }
		    if (niters > nitmax) {
			goto L16;
		    }
/* * */
/* *                *** loop *** */
		    goto L15;
/* * */
/* *                *** tolerance not reached *** */
L16:
		    ++ifail_tol__;
/* * */
/* *                *** tolerance reached *** */
L17:
/* * */
/* *                *** newton's method complete -- update solution value *** */
		    x[i__ + (j + k * x_dim2) * x_dim1] = x[i__ + (j + k * 
			    x_dim2) * x_dim1] * fac + *omega * uu;
/* L12: */
		}
/* L11: */
	    }
/* L10: */
	}
/* * */
/* *       *** main loop *** */
/* L30: */
    }
/* * */
/* *    *** if specified, return the new residual as well *** */
    if (*iresid == 1) {
	nmresid27_1s__(nx, ny, nz, &ipc[1], &rpc[1], &oc[oc_offset], &cc[
		cc_offset], &fc[fc_offset], &oe[oe_offset], &on[on_offset], &
		uc[uc_offset], &one[one_offset], &onw[onw_offset], &ue[
		ue_offset], &uw[uw_offset], &un[un_offset], &us[us_offset], &
		une[une_offset], &unw[unw_offset], &use[use_offset], &usw[
		usw_offset], &x[x_offset], &r__[r_offset], &w1[w1_offset]);
    }
/* * */
/* *    *** messages *** */
    if (ifail_tol__ > 0) {
	s_wsle(&io___44);
	do_lio(&c__9, &c__1, "% NSOR: 1d newton tolerance failures:     ", (
		ftnlen)42);
	do_lio(&c__3, &c__1, (char *)&ifail_tol__, (ftnlen)sizeof(integer));
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* nsor27_ */

