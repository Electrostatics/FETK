/* ./src_f77/cgd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    cgd.f */
/* * @author  Michael Holst */
/* * @brief   Classical (Hestenes-Stiefel) Conjugate Gradient Method. */
/* * @version $Id: cgd.c,v 1.3 2010/08/12 05:45:20 fetk Exp $ */
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
/* Subroutine */ int cghs_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, 
	doublereal *x, doublereal *p, doublereal *ap, doublereal *r__, 
	integer *itmax, integer *iters, doublereal *errtol, doublereal *omega,
	 integer *iresid, integer *iadjoint)
{
    /* System generated locals */
    integer ac_dim1, ac_dim2, ac_dim3, ac_offset, fc_dim1, fc_dim2, fc_offset,
	     cc_dim1, cc_dim2, cc_offset, x_dim1, x_dim2, x_offset, r_dim1, 
	    r_dim2, r_offset, p_dim1, p_dim2, p_offset, ap_dim1, ap_dim2, 
	    ap_offset;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal pap, beta;
    extern doublereal xdot_(integer *, integer *, integer *, doublereal *, 
	    doublereal *);
    static doublereal rhok1, rhok2;
    extern doublereal xnrm2_(integer *, integer *, integer *, doublereal *);
    static doublereal alpha, denom;
    extern /* Subroutine */ int xscal_(integer *, integer *, integer *, 
	    doublereal *, doublereal *);
    static doublereal rsnrm;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *), xaxpy_(integer *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *), matvec_(integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), mresid_(integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    this routine solves the spd ax=b using conjugate gradients (cghs). */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** setup for the looping *** */
    /* Parameter adjustments */
    r_dim1 = *nx;
    r_dim2 = *ny;
    r_offset = 1 + r_dim1 * (1 + r_dim2);
    r__ -= r_offset;
    ap_dim1 = *nx;
    ap_dim2 = *ny;
    ap_offset = 1 + ap_dim1 * (1 + ap_dim2);
    ap -= ap_offset;
    p_dim1 = *nx;
    p_dim2 = *ny;
    p_offset = 1 + p_dim1 * (1 + p_dim2);
    p -= p_offset;
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
    ac_dim1 = *nx;
    ac_dim2 = *ny;
    ac_dim3 = *nz;
    ac_offset = 1 + ac_dim1 * (1 + ac_dim2 * (1 + ac_dim3));
    ac -= ac_offset;
    --ipc;
    --rpc;

    /* Function Body */
    *iters = 0;
    if (*iters >= *itmax && *iresid == 0) {
	goto L99;
    }
    mresid_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[cc_offset], &fc[
	    fc_offset], &x[x_offset], &r__[r_offset]);
    denom = xnrm2_(nx, ny, nz, &r__[r_offset]);
    if (denom == 0.f) {
	goto L99;
    }
    if (*iters >= *itmax) {
	goto L99;
    }
L30:
/* * */
/* *       *** compute/check the current stopping test *** */
    rhok2 = xdot_(nx, ny, nz, &r__[r_offset], &r__[r_offset]);
    rsnrm = sqrt(rhok2);
/* * ******print*,'% CGHS: iters, rsnrm = ',iters,rsnrm/denom */
    if (rsnrm / denom <= *errtol) {
	goto L99;
    }
    if (*iters >= *itmax) {
	goto L99;
    }
/* * */
/* *       *** form new direction vector from old one and residual *** */
    if (*iters == 0) {
	xcopy_(nx, ny, nz, &r__[r_offset], &p[p_offset]);
    } else {
	beta = rhok2 / rhok1;
	d__1 = 1. / beta;
	xaxpy_(nx, ny, nz, &d__1, &r__[r_offset], &p[p_offset]);
	xscal_(nx, ny, nz, &beta, &p[p_offset]);
    }
/* * */
/* *       *** linear case: alpha which minimizes energy norm of error *** */
    matvec_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[cc_offset], &p[
	    p_offset], &ap[ap_offset]);
    pap = xdot_(nx, ny, nz, &p[p_offset], &ap[ap_offset]);
    alpha = rhok2 / pap;
/* * */
/* *       *** save rhok2 for next iteration *** */
    rhok1 = rhok2;
/* * */
/* *       *** update solution in direction p of length alpha *** */
    xaxpy_(nx, ny, nz, &alpha, &p[p_offset], &x[x_offset]);
/* * */
/* *       *** update residual *** */
    d__1 = -alpha;
    xaxpy_(nx, ny, nz, &d__1, &ap[ap_offset], &r__[r_offset]);
/* * */
/* *       *** some bookkeeping *** */
    ++(*iters);
    goto L30;
/* * */
/* *    *** return and end *** */
L99:
    return 0;
} /* cghs_ */

