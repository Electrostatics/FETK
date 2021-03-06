/* ./src_f77/rchd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    rchd.f */
/* * @author  Michael Holst */
/* * @brief   Richardson iteration. */
/* * @version $Id: rchd.c,v 1.3 2010/08/12 05:45:28 fetk Exp $ */
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
/* Subroutine */ int rich_(integer *nx, integer *ny, integer *nz, integer *
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
    extern /* Subroutine */ int rich7_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, integer *), rich27_(
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
	rich7_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[cc_offset],
		 &fc[fc_offset], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1]
		, &ac[(ac_dim1 << 2) + 1], &x[x_offset], &w1[w1_offset], &w2[
		w2_offset], &r__[r_offset], itmax, iters, errtol, omega, 
		iresid, iadjoint);
    } else if (numdia == 27) {
	rich27_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[cc_offset]
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
	do_lio(&c__9, &c__1, "% RICH: invalid stencil type given...", (ftnlen)
		37);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* rich_ */

/* Subroutine */ int rich7_(integer *nx, integer *ny, integer *nz, integer *
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

    /* Local variables */
    static integer i__, j, k;
    extern /* Subroutine */ int mresid7_1s__(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *   linear richardson's iteration (hackbusch, page 185) */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do the richardson's iteration itmax times *** */
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
    i__1 = *itmax;
    for (*iters = 1; *iters <= i__1; ++(*iters)) {
/* * */
/* *       *** first get the residual *** */
	mresid7_1s__(nx, ny, nz, &ipc[1], &rpc[1], &oc[oc_offset], &cc[
		cc_offset], &fc[fc_offset], &oe[oe_offset], &on[on_offset], &
		uc[uc_offset], &x[x_offset], &r__[r_offset]);
/* * */
/* *       *** do it *** */
/* mdir 3 1 */
	i__2 = *nz - 1;
	for (k = 2; k <= i__2; ++k) {
/* mdir 3 2 */
	    i__3 = *ny - 1;
	    for (j = 2; j <= i__3; ++j) {
/* mdir 3 3 */
		i__4 = *nx - 1;
		for (i__ = 2; i__ <= i__4; ++i__) {
		    x[i__ + (j + k * x_dim2) * x_dim1] += *omega * r__[i__ + (
			    j + k * r_dim2) * r_dim1];
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
	mresid7_1s__(nx, ny, nz, &ipc[1], &rpc[1], &oc[oc_offset], &cc[
		cc_offset], &fc[fc_offset], &oe[oe_offset], &on[on_offset], &
		uc[uc_offset], &x[x_offset], &r__[r_offset]);
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* rich7_ */

/* Subroutine */ int rich27_(integer *nx, integer *ny, integer *nz, integer *
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

    /* Local variables */
    static integer i__, j, k;
    extern /* Subroutine */ int mresid27_1s__(integer *, integer *, integer *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *   linear richardson's iteration (hackbusch, page 185) */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do the richardson's iteration itmax times *** */
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
    i__1 = *itmax;
    for (*iters = 1; *iters <= i__1; ++(*iters)) {
/* * */
/* *       *** first get the residual *** */
	mresid27_1s__(nx, ny, nz, &ipc[1], &rpc[1], &oc[oc_offset], &cc[
		cc_offset], &fc[fc_offset], &oe[oe_offset], &on[on_offset], &
		uc[uc_offset], &one[one_offset], &onw[onw_offset], &ue[
		ue_offset], &uw[uw_offset], &un[un_offset], &us[us_offset], &
		une[une_offset], &unw[unw_offset], &use[use_offset], &usw[
		usw_offset], &x[x_offset], &r__[r_offset]);
/* * */
/* *       *** do it *** */
/* mdir 3 1 */
	i__2 = *nz - 1;
	for (k = 2; k <= i__2; ++k) {
/* mdir 3 2 */
	    i__3 = *ny - 1;
	    for (j = 2; j <= i__3; ++j) {
/* mdir 3 3 */
		i__4 = *nx - 1;
		for (i__ = 2; i__ <= i__4; ++i__) {
		    x[i__ + (j + k * x_dim2) * x_dim1] += *omega * r__[i__ + (
			    j + k * r_dim2) * r_dim1];
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
	mresid27_1s__(nx, ny, nz, &ipc[1], &rpc[1], &oc[oc_offset], &cc[
		cc_offset], &fc[fc_offset], &oe[oe_offset], &on[on_offset], &
		uc[uc_offset], &one[one_offset], &onw[onw_offset], &ue[
		ue_offset], &uw[uw_offset], &un[un_offset], &us[us_offset], &
		une[une_offset], &unw[unw_offset], &use[use_offset], &usw[
		usw_offset], &x[x_offset], &r__[r_offset]);
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* rich27_ */

