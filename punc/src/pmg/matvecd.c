/* ./src_f77/matvecd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    matvecd.f */
/* * @author  Michael Holst */
/* * @brief   Matrix-vector operations. */
/* * @version $Id: matvecd.c,v 1.3 2010/08/12 05:45:21 fetk Exp $ */
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
/* Subroutine */ int matvec_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, 
	doublereal *y)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer numdia;
    extern /* Subroutine */ int matvec7_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *), matvec27_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *);

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the matrix-vector routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --x;
    --y;

    /* Function Body */
    numdia = ipc[11];
    if (numdia == 7) {
	matvec7_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[1], &x[1], 
		&y[1]);
    } else if (numdia == 27) {
	matvec27_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[1], &x[1],
		 &y[1]);
    } else {
	s_wsle(&io___2);
	do_lio(&c__9, &c__1, "% MATVEC: invalid stencil type given...", (
		ftnlen)39);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* matvec_ */

/* Subroutine */ int matvec7_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, 
	doublereal *y)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Local variables */
    extern /* Subroutine */ int matvec7_1s__(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the matrix-vector routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --x;
    --y;

    /* Function Body */
    matvec7_1s__(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[1], &ac[(
	    ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) + 1],
	     &x[1], &y[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* matvec7_ */

/* Subroutine */ int matvec7_1s__(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, 
	doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, 
	doublereal *y)
{
    /* System generated locals */
    integer oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1,
	     uc_dim2, uc_offset, cc_dim1, cc_dim2, cc_offset, oc_dim1, 
	    oc_dim2, oc_offset, x_dim1, x_dim2, x_offset, y_dim1, y_dim2, 
	    y_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the operator times a vector. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    y_dim1 = *nx;
    y_dim2 = *ny;
    y_offset = 1 + y_dim1 * (1 + y_dim2);
    y -= y_offset;
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
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		y[i__ + (j + k * y_dim2) * y_dim1] = -on[i__ + (j + k * 
			on_dim2) * on_dim1] * x[i__ + (j + 1 + k * x_dim2) * 
			x_dim1] - on[i__ + (j - 1 + k * on_dim2) * on_dim1] * 
			x[i__ + (j - 1 + k * x_dim2) * x_dim1] - oe[i__ + (j 
			+ k * oe_dim2) * oe_dim1] * x[i__ + 1 + (j + k * 
			x_dim2) * x_dim1] - oe[i__ - 1 + (j + k * oe_dim2) * 
			oe_dim1] * x[i__ - 1 + (j + k * x_dim2) * x_dim1] - 
			uc[i__ + (j + (k - 1) * uc_dim2) * uc_dim1] * x[i__ + 
			(j + (k - 1) * x_dim2) * x_dim1] - uc[i__ + (j + k * 
			uc_dim2) * uc_dim1] * x[i__ + (j + (k + 1) * x_dim2) *
			 x_dim1] + (oc[i__ + (j + k * oc_dim2) * oc_dim1] + 
			cc[i__ + (j + k * cc_dim2) * cc_dim1]) * x[i__ + (j + 
			k * x_dim2) * x_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* matvec7_1s__ */

/* Subroutine */ int matvec27_(integer *nx, integer *ny, integer *nz, integer 
	*ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, 
	doublereal *y)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Local variables */
    extern /* Subroutine */ int matvec27_1s__(integer *, integer *, integer *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the matrix-vector routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --x;
    --y;

    /* Function Body */
    matvec27_1s__(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[1], &ac[
	    (ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) + 1]
	    , &ac[ac_dim1 * 5 + 1], &ac[ac_dim1 * 6 + 1], &ac[ac_dim1 * 7 + 1]
	    , &ac[(ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1], &ac[ac_dim1 * 10 
	    + 1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 + 1], &ac[ac_dim1 * 
	    13 + 1], &ac[ac_dim1 * 14 + 1], &x[1], &y[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* matvec27_ */

/* Subroutine */ int matvec27_1s__(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, 
	doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, 
	doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, 
	doublereal *us, doublereal *une, doublereal *unw, doublereal *use, 
	doublereal *usw, doublereal *x, doublereal *y)
{
    /* System generated locals */
    integer oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1,
	     uc_dim2, uc_offset, one_dim1, one_dim2, one_offset, onw_dim1, 
	    onw_dim2, onw_offset, ue_dim1, ue_dim2, ue_offset, uw_dim1, 
	    uw_dim2, uw_offset, un_dim1, un_dim2, un_offset, us_dim1, us_dim2,
	     us_offset, une_dim1, une_dim2, une_offset, unw_dim1, unw_dim2, 
	    unw_offset, use_dim1, use_dim2, use_offset, usw_dim1, usw_dim2, 
	    usw_offset, cc_dim1, cc_dim2, cc_offset, oc_dim1, oc_dim2, 
	    oc_offset, x_dim1, x_dim2, x_offset, y_dim1, y_dim2, y_offset, 
	    i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;
    static doublereal tmpd, tmpo, tmpu;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the operator times a vector. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    y_dim1 = *nx;
    y_dim2 = *ny;
    y_offset = 1 + y_dim1 * (1 + y_dim2);
    y -= y_offset;
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
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		tmpo = -on[i__ + (j + k * on_dim2) * on_dim1] * x[i__ + (j + 
			1 + k * x_dim2) * x_dim1] - on[i__ + (j - 1 + k * 
			on_dim2) * on_dim1] * x[i__ + (j - 1 + k * x_dim2) * 
			x_dim1] - oe[i__ + (j + k * oe_dim2) * oe_dim1] * x[
			i__ + 1 + (j + k * x_dim2) * x_dim1] - oe[i__ - 1 + (
			j + k * oe_dim2) * oe_dim1] * x[i__ - 1 + (j + k * 
			x_dim2) * x_dim1] - one[i__ + (j + k * one_dim2) * 
			one_dim1] * x[i__ + 1 + (j + 1 + k * x_dim2) * x_dim1]
			 - onw[i__ + (j + k * onw_dim2) * onw_dim1] * x[i__ - 
			1 + (j + 1 + k * x_dim2) * x_dim1] - onw[i__ + 1 + (j 
			- 1 + k * onw_dim2) * onw_dim1] * x[i__ + 1 + (j - 1 
			+ k * x_dim2) * x_dim1] - one[i__ - 1 + (j - 1 + k * 
			one_dim2) * one_dim1] * x[i__ - 1 + (j - 1 + k * 
			x_dim2) * x_dim1];
		tmpu = -uc[i__ + (j + k * uc_dim2) * uc_dim1] * x[i__ + (j + (
			k + 1) * x_dim2) * x_dim1] - un[i__ + (j + k * 
			un_dim2) * un_dim1] * x[i__ + (j + 1 + (k + 1) * 
			x_dim2) * x_dim1] - us[i__ + (j + k * us_dim2) * 
			us_dim1] * x[i__ + (j - 1 + (k + 1) * x_dim2) * 
			x_dim1] - ue[i__ + (j + k * ue_dim2) * ue_dim1] * x[
			i__ + 1 + (j + (k + 1) * x_dim2) * x_dim1] - uw[i__ + 
			(j + k * uw_dim2) * uw_dim1] * x[i__ - 1 + (j + (k + 
			1) * x_dim2) * x_dim1] - une[i__ + (j + k * une_dim2) 
			* une_dim1] * x[i__ + 1 + (j + 1 + (k + 1) * x_dim2) *
			 x_dim1] - unw[i__ + (j + k * unw_dim2) * unw_dim1] * 
			x[i__ - 1 + (j + 1 + (k + 1) * x_dim2) * x_dim1] - 
			use[i__ + (j + k * use_dim2) * use_dim1] * x[i__ + 1 
			+ (j - 1 + (k + 1) * x_dim2) * x_dim1] - usw[i__ + (j 
			+ k * usw_dim2) * usw_dim1] * x[i__ - 1 + (j - 1 + (k 
			+ 1) * x_dim2) * x_dim1];
		tmpd = -uc[i__ + (j + (k - 1) * uc_dim2) * uc_dim1] * x[i__ + 
			(j + (k - 1) * x_dim2) * x_dim1] - us[i__ + (j + 1 + (
			k - 1) * us_dim2) * us_dim1] * x[i__ + (j + 1 + (k - 
			1) * x_dim2) * x_dim1] - un[i__ + (j - 1 + (k - 1) * 
			un_dim2) * un_dim1] * x[i__ + (j - 1 + (k - 1) * 
			x_dim2) * x_dim1] - uw[i__ + 1 + (j + (k - 1) * 
			uw_dim2) * uw_dim1] * x[i__ + 1 + (j + (k - 1) * 
			x_dim2) * x_dim1] - ue[i__ - 1 + (j + (k - 1) * 
			ue_dim2) * ue_dim1] * x[i__ - 1 + (j + (k - 1) * 
			x_dim2) * x_dim1] - usw[i__ + 1 + (j + 1 + (k - 1) * 
			usw_dim2) * usw_dim1] * x[i__ + 1 + (j + 1 + (k - 1) *
			 x_dim2) * x_dim1] - use[i__ - 1 + (j + 1 + (k - 1) * 
			use_dim2) * use_dim1] * x[i__ - 1 + (j + 1 + (k - 1) *
			 x_dim2) * x_dim1] - unw[i__ + 1 + (j - 1 + (k - 1) * 
			unw_dim2) * unw_dim1] * x[i__ + 1 + (j - 1 + (k - 1) *
			 x_dim2) * x_dim1] - une[i__ - 1 + (j - 1 + (k - 1) * 
			une_dim2) * une_dim1] * x[i__ - 1 + (j - 1 + (k - 1) *
			 x_dim2) * x_dim1];
		y[i__ + (j + k * y_dim2) * y_dim1] = tmpo + tmpu + tmpd + (oc[
			i__ + (j + k * oc_dim2) * oc_dim1] + cc[i__ + (j + k *
			 cc_dim2) * cc_dim1]) * x[i__ + (j + k * x_dim2) * 
			x_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* matvec27_1s__ */

/* Subroutine */ int mresid_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, 
	doublereal *x, doublereal *r__)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer numdia;
    extern /* Subroutine */ int mresid7_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *), mresid27_(integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___13 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the residual routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --fc;
    --x;
    --r__;

    /* Function Body */
    numdia = ipc[11];
    if (numdia == 7) {
	mresid7_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[1], &fc[1],
		 &x[1], &r__[1]);
    } else if (numdia == 27) {
	mresid27_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[1], &fc[1]
		, &x[1], &r__[1]);
    } else {
	s_wsle(&io___13);
	do_lio(&c__9, &c__1, "% MRESID: invalid stencil type given...", (
		ftnlen)39);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* mresid_ */

/* Subroutine */ int mresid7_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, 
	doublereal *x, doublereal *r__)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Local variables */
    extern /* Subroutine */ int mresid7_1s__(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the residual routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --fc;
    --x;
    --r__;

    /* Function Body */
    mresid7_1s__(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[1], &fc[
	    1], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 <<
	     2) + 1], &x[1], &r__[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* mresid7_ */

/* Subroutine */ int mresid7_1s__(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, 
	doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, 
	doublereal *x, doublereal *r__)
{
    /* System generated locals */
    integer oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1,
	     uc_dim2, uc_offset, cc_dim1, cc_dim2, cc_offset, fc_dim1, 
	    fc_dim2, fc_offset, oc_dim1, oc_dim2, oc_offset, x_dim1, x_dim2, 
	    x_offset, r_dim1, r_dim2, r_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the residual. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    r_dim1 = *nx;
    r_dim2 = *ny;
    r_offset = 1 + r_dim1 * (1 + r_dim2);
    r__ -= r_offset;
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
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		r__[i__ + (j + k * r_dim2) * r_dim1] = fc[i__ + (j + k * 
			fc_dim2) * fc_dim1] + on[i__ + (j + k * on_dim2) * 
			on_dim1] * x[i__ + (j + 1 + k * x_dim2) * x_dim1] + 
			on[i__ + (j - 1 + k * on_dim2) * on_dim1] * x[i__ + (
			j - 1 + k * x_dim2) * x_dim1] + oe[i__ + (j + k * 
			oe_dim2) * oe_dim1] * x[i__ + 1 + (j + k * x_dim2) * 
			x_dim1] + oe[i__ - 1 + (j + k * oe_dim2) * oe_dim1] * 
			x[i__ - 1 + (j + k * x_dim2) * x_dim1] + uc[i__ + (j 
			+ (k - 1) * uc_dim2) * uc_dim1] * x[i__ + (j + (k - 1)
			 * x_dim2) * x_dim1] + uc[i__ + (j + k * uc_dim2) * 
			uc_dim1] * x[i__ + (j + (k + 1) * x_dim2) * x_dim1] - 
			(oc[i__ + (j + k * oc_dim2) * oc_dim1] + cc[i__ + (j 
			+ k * cc_dim2) * cc_dim1]) * x[i__ + (j + k * x_dim2) 
			* x_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* mresid7_1s__ */

/* Subroutine */ int mresid27_(integer *nx, integer *ny, integer *nz, integer 
	*ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc,
	 doublereal *x, doublereal *r__)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Local variables */
    extern /* Subroutine */ int mresid27_1s__(integer *, integer *, integer *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the residual routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --fc;
    --x;
    --r__;

    /* Function Body */
    mresid27_1s__(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[1], &fc[
	    1], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 <<
	     2) + 1], &ac[ac_dim1 * 5 + 1], &ac[ac_dim1 * 6 + 1], &ac[ac_dim1 
	    * 7 + 1], &ac[(ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1], &ac[
	    ac_dim1 * 10 + 1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 + 1], &
	    ac[ac_dim1 * 13 + 1], &ac[ac_dim1 * 14 + 1], &x[1], &r__[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* mresid27_ */

/* Subroutine */ int mresid27_1s__(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, 
	doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, 
	doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, 
	doublereal *un, doublereal *us, doublereal *une, doublereal *unw, 
	doublereal *use, doublereal *usw, doublereal *x, doublereal *r__)
{
    /* System generated locals */
    integer oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1,
	     uc_dim2, uc_offset, one_dim1, one_dim2, one_offset, onw_dim1, 
	    onw_dim2, onw_offset, ue_dim1, ue_dim2, ue_offset, uw_dim1, 
	    uw_dim2, uw_offset, un_dim1, un_dim2, un_offset, us_dim1, us_dim2,
	     us_offset, une_dim1, une_dim2, une_offset, unw_dim1, unw_dim2, 
	    unw_offset, use_dim1, use_dim2, use_offset, usw_dim1, usw_dim2, 
	    usw_offset, cc_dim1, cc_dim2, cc_offset, fc_dim1, fc_dim2, 
	    fc_offset, oc_dim1, oc_dim2, oc_offset, x_dim1, x_dim2, x_offset, 
	    r_dim1, r_dim2, r_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;
    static doublereal tmpd, tmpo, tmpu;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the residual. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    r_dim1 = *nx;
    r_dim2 = *ny;
    r_offset = 1 + r_dim1 * (1 + r_dim2);
    r__ -= r_offset;
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
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		tmpo = on[i__ + (j + k * on_dim2) * on_dim1] * x[i__ + (j + 1 
			+ k * x_dim2) * x_dim1] + on[i__ + (j - 1 + k * 
			on_dim2) * on_dim1] * x[i__ + (j - 1 + k * x_dim2) * 
			x_dim1] + oe[i__ + (j + k * oe_dim2) * oe_dim1] * x[
			i__ + 1 + (j + k * x_dim2) * x_dim1] + oe[i__ - 1 + (
			j + k * oe_dim2) * oe_dim1] * x[i__ - 1 + (j + k * 
			x_dim2) * x_dim1] + one[i__ + (j + k * one_dim2) * 
			one_dim1] * x[i__ + 1 + (j + 1 + k * x_dim2) * x_dim1]
			 + onw[i__ + (j + k * onw_dim2) * onw_dim1] * x[i__ - 
			1 + (j + 1 + k * x_dim2) * x_dim1] + onw[i__ + 1 + (j 
			- 1 + k * onw_dim2) * onw_dim1] * x[i__ + 1 + (j - 1 
			+ k * x_dim2) * x_dim1] + one[i__ - 1 + (j - 1 + k * 
			one_dim2) * one_dim1] * x[i__ - 1 + (j - 1 + k * 
			x_dim2) * x_dim1];
		tmpu = uc[i__ + (j + k * uc_dim2) * uc_dim1] * x[i__ + (j + (
			k + 1) * x_dim2) * x_dim1] + un[i__ + (j + k * 
			un_dim2) * un_dim1] * x[i__ + (j + 1 + (k + 1) * 
			x_dim2) * x_dim1] + us[i__ + (j + k * us_dim2) * 
			us_dim1] * x[i__ + (j - 1 + (k + 1) * x_dim2) * 
			x_dim1] + ue[i__ + (j + k * ue_dim2) * ue_dim1] * x[
			i__ + 1 + (j + (k + 1) * x_dim2) * x_dim1] + uw[i__ + 
			(j + k * uw_dim2) * uw_dim1] * x[i__ - 1 + (j + (k + 
			1) * x_dim2) * x_dim1] + une[i__ + (j + k * une_dim2) 
			* une_dim1] * x[i__ + 1 + (j + 1 + (k + 1) * x_dim2) *
			 x_dim1] + unw[i__ + (j + k * unw_dim2) * unw_dim1] * 
			x[i__ - 1 + (j + 1 + (k + 1) * x_dim2) * x_dim1] + 
			use[i__ + (j + k * use_dim2) * use_dim1] * x[i__ + 1 
			+ (j - 1 + (k + 1) * x_dim2) * x_dim1] + usw[i__ + (j 
			+ k * usw_dim2) * usw_dim1] * x[i__ - 1 + (j - 1 + (k 
			+ 1) * x_dim2) * x_dim1];
		tmpd = uc[i__ + (j + (k - 1) * uc_dim2) * uc_dim1] * x[i__ + (
			j + (k - 1) * x_dim2) * x_dim1] + us[i__ + (j + 1 + (
			k - 1) * us_dim2) * us_dim1] * x[i__ + (j + 1 + (k - 
			1) * x_dim2) * x_dim1] + un[i__ + (j - 1 + (k - 1) * 
			un_dim2) * un_dim1] * x[i__ + (j - 1 + (k - 1) * 
			x_dim2) * x_dim1] + uw[i__ + 1 + (j + (k - 1) * 
			uw_dim2) * uw_dim1] * x[i__ + 1 + (j + (k - 1) * 
			x_dim2) * x_dim1] + ue[i__ - 1 + (j + (k - 1) * 
			ue_dim2) * ue_dim1] * x[i__ - 1 + (j + (k - 1) * 
			x_dim2) * x_dim1] + usw[i__ + 1 + (j + 1 + (k - 1) * 
			usw_dim2) * usw_dim1] * x[i__ + 1 + (j + 1 + (k - 1) *
			 x_dim2) * x_dim1] + use[i__ - 1 + (j + 1 + (k - 1) * 
			use_dim2) * use_dim1] * x[i__ - 1 + (j + 1 + (k - 1) *
			 x_dim2) * x_dim1] + unw[i__ + 1 + (j - 1 + (k - 1) * 
			unw_dim2) * unw_dim1] * x[i__ + 1 + (j - 1 + (k - 1) *
			 x_dim2) * x_dim1] + une[i__ - 1 + (j - 1 + (k - 1) * 
			une_dim2) * une_dim1] * x[i__ - 1 + (j - 1 + (k - 1) *
			 x_dim2) * x_dim1];
		r__[i__ + (j + k * r_dim2) * r_dim1] = fc[i__ + (j + k * 
			fc_dim2) * fc_dim1] + tmpo + tmpu + tmpd - (oc[i__ + (
			j + k * oc_dim2) * oc_dim1] + cc[i__ + (j + k * 
			cc_dim2) * cc_dim1]) * x[i__ + (j + k * x_dim2) * 
			x_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* mresid27_1s__ */

/* Subroutine */ int nmatvec_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, 
	doublereal *y, doublereal *w1)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int nmatvec7_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *), nmatvec27_(integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static integer numdia;

    /* Fortran I/O blocks */
    static cilist io___24 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the matrix-vector routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --x;
    --y;
    --w1;

    /* Function Body */
    numdia = ipc[11];
    if (numdia == 7) {
	nmatvec7_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[1], &x[1],
		 &y[1], &w1[1]);
    } else if (numdia == 27) {
	nmatvec27_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[1], &x[1]
		, &y[1], &w1[1]);
    } else {
	s_wsle(&io___24);
	do_lio(&c__9, &c__1, "% NMATVEC: invalid stencil type given...", (
		ftnlen)40);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* nmatvec_ */

/* Subroutine */ int nmatvec7_(integer *nx, integer *ny, integer *nz, integer 
	*ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, 
	doublereal *y, doublereal *w1)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Local variables */
    extern /* Subroutine */ int nmatvecd7_1s__(integer *, integer *, integer *
	    , integer *, doublereal *, doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the matrix-vector routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --x;
    --y;
    --w1;

    /* Function Body */
    nmatvecd7_1s__(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[1], &
	    ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) 
	    + 1], &x[1], &y[1], &w1[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* nmatvec7_ */

/* Subroutine */ int nmatvecd7_1s__(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, 
	doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, 
	doublereal *y, doublereal *w1)
{
    /* System generated locals */
    integer oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1,
	     uc_dim2, uc_offset, cc_dim1, cc_dim2, cc_offset, oc_dim1, 
	    oc_dim2, oc_offset, x_dim1, x_dim2, x_offset, y_dim1, y_dim2, 
	    y_offset, w1_dim1, w1_dim2, w1_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;
    extern /* Subroutine */ int c_vec__(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *);
    static integer ipkey;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the operator times a vector. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** first get vector noNlinear term to avoid subroutine calls *** */
    /* Parameter adjustments */
    w1_dim1 = *nx;
    w1_dim2 = *ny;
    w1_offset = 1 + w1_dim1 * (1 + w1_dim2);
    w1 -= w1_offset;
    y_dim1 = *nx;
    y_dim2 = *ny;
    y_offset = 1 + y_dim1 * (1 + y_dim2);
    y -= y_offset;
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
    ipkey = ipc[10];
    c_vec__(&cc[cc_offset], &x[x_offset], &w1[w1_offset], nx, ny, nz, &ipkey);
/* * */
/* *    *** the operator *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		y[i__ + (j + k * y_dim2) * y_dim1] = -on[i__ + (j + k * 
			on_dim2) * on_dim1] * x[i__ + (j + 1 + k * x_dim2) * 
			x_dim1] - on[i__ + (j - 1 + k * on_dim2) * on_dim1] * 
			x[i__ + (j - 1 + k * x_dim2) * x_dim1] - oe[i__ + (j 
			+ k * oe_dim2) * oe_dim1] * x[i__ + 1 + (j + k * 
			x_dim2) * x_dim1] - oe[i__ - 1 + (j + k * oe_dim2) * 
			oe_dim1] * x[i__ - 1 + (j + k * x_dim2) * x_dim1] - 
			uc[i__ + (j + (k - 1) * uc_dim2) * uc_dim1] * x[i__ + 
			(j + (k - 1) * x_dim2) * x_dim1] - uc[i__ + (j + k * 
			uc_dim2) * uc_dim1] * x[i__ + (j + (k + 1) * x_dim2) *
			 x_dim1] + oc[i__ + (j + k * oc_dim2) * oc_dim1] * x[
			i__ + (j + k * x_dim2) * x_dim1] + w1[i__ + (j + k * 
			w1_dim2) * w1_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* nmatvecd7_1s__ */

/* Subroutine */ int nmatvec27_(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, 
	doublereal *x, doublereal *y, doublereal *w1)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Local variables */
    extern /* Subroutine */ int nmatvecd27_1s__(integer *, integer *, integer 
	    *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the matrix-vector routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --x;
    --y;
    --w1;

    /* Function Body */
    nmatvecd27_1s__(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[1], &
	    ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) 
	    + 1], &ac[ac_dim1 * 5 + 1], &ac[ac_dim1 * 6 + 1], &ac[ac_dim1 * 7 
	    + 1], &ac[(ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1], &ac[ac_dim1 *
	     10 + 1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 + 1], &ac[
	    ac_dim1 * 13 + 1], &ac[ac_dim1 * 14 + 1], &x[1], &y[1], &w1[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* nmatvec27_ */

/* Subroutine */ int nmatvecd27_1s__(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, 
	doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, 
	doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, 
	doublereal *us, doublereal *une, doublereal *unw, doublereal *use, 
	doublereal *usw, doublereal *x, doublereal *y, doublereal *w1)
{
    /* System generated locals */
    integer oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1,
	     uc_dim2, uc_offset, one_dim1, one_dim2, one_offset, onw_dim1, 
	    onw_dim2, onw_offset, ue_dim1, ue_dim2, ue_offset, uw_dim1, 
	    uw_dim2, uw_offset, un_dim1, un_dim2, un_offset, us_dim1, us_dim2,
	     us_offset, une_dim1, une_dim2, une_offset, unw_dim1, unw_dim2, 
	    unw_offset, use_dim1, use_dim2, use_offset, usw_dim1, usw_dim2, 
	    usw_offset, cc_dim1, cc_dim2, cc_offset, oc_dim1, oc_dim2, 
	    oc_offset, x_dim1, x_dim2, x_offset, y_dim1, y_dim2, y_offset, 
	    w1_dim1, w1_dim2, w1_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;
    static doublereal tmpd, tmpo, tmpu;
    extern /* Subroutine */ int c_vec__(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *);
    static integer ipkey;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the operator times a vector. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** first get vector noNlinear term to avoid subroutine calls *** */
    /* Parameter adjustments */
    w1_dim1 = *nx;
    w1_dim2 = *ny;
    w1_offset = 1 + w1_dim1 * (1 + w1_dim2);
    w1 -= w1_offset;
    y_dim1 = *nx;
    y_dim2 = *ny;
    y_offset = 1 + y_dim1 * (1 + y_dim2);
    y -= y_offset;
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
    ipkey = ipc[10];
    c_vec__(&cc[cc_offset], &x[x_offset], &w1[w1_offset], nx, ny, nz, &ipkey);
/* * */
/* *    *** the operator *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		tmpo = -on[i__ + (j + k * on_dim2) * on_dim1] * x[i__ + (j + 
			1 + k * x_dim2) * x_dim1] - on[i__ + (j - 1 + k * 
			on_dim2) * on_dim1] * x[i__ + (j - 1 + k * x_dim2) * 
			x_dim1] - oe[i__ + (j + k * oe_dim2) * oe_dim1] * x[
			i__ + 1 + (j + k * x_dim2) * x_dim1] - oe[i__ - 1 + (
			j + k * oe_dim2) * oe_dim1] * x[i__ - 1 + (j + k * 
			x_dim2) * x_dim1] - one[i__ + (j + k * one_dim2) * 
			one_dim1] * x[i__ + 1 + (j + 1 + k * x_dim2) * x_dim1]
			 - onw[i__ + (j + k * onw_dim2) * onw_dim1] * x[i__ - 
			1 + (j + 1 + k * x_dim2) * x_dim1] - onw[i__ + 1 + (j 
			- 1 + k * onw_dim2) * onw_dim1] * x[i__ + 1 + (j - 1 
			+ k * x_dim2) * x_dim1] - one[i__ - 1 + (j - 1 + k * 
			one_dim2) * one_dim1] * x[i__ - 1 + (j - 1 + k * 
			x_dim2) * x_dim1];
		tmpu = -uc[i__ + (j + k * uc_dim2) * uc_dim1] * x[i__ + (j + (
			k + 1) * x_dim2) * x_dim1] - un[i__ + (j + k * 
			un_dim2) * un_dim1] * x[i__ + (j + 1 + (k + 1) * 
			x_dim2) * x_dim1] - us[i__ + (j + k * us_dim2) * 
			us_dim1] * x[i__ + (j - 1 + (k + 1) * x_dim2) * 
			x_dim1] - ue[i__ + (j + k * ue_dim2) * ue_dim1] * x[
			i__ + 1 + (j + (k + 1) * x_dim2) * x_dim1] - uw[i__ + 
			(j + k * uw_dim2) * uw_dim1] * x[i__ - 1 + (j + (k + 
			1) * x_dim2) * x_dim1] - une[i__ + (j + k * une_dim2) 
			* une_dim1] * x[i__ + 1 + (j + 1 + (k + 1) * x_dim2) *
			 x_dim1] - unw[i__ + (j + k * unw_dim2) * unw_dim1] * 
			x[i__ - 1 + (j + 1 + (k + 1) * x_dim2) * x_dim1] - 
			use[i__ + (j + k * use_dim2) * use_dim1] * x[i__ + 1 
			+ (j - 1 + (k + 1) * x_dim2) * x_dim1] - usw[i__ + (j 
			+ k * usw_dim2) * usw_dim1] * x[i__ - 1 + (j - 1 + (k 
			+ 1) * x_dim2) * x_dim1];
		tmpd = -uc[i__ + (j + (k - 1) * uc_dim2) * uc_dim1] * x[i__ + 
			(j + (k - 1) * x_dim2) * x_dim1] - us[i__ + (j + 1 + (
			k - 1) * us_dim2) * us_dim1] * x[i__ + (j + 1 + (k - 
			1) * x_dim2) * x_dim1] - un[i__ + (j - 1 + (k - 1) * 
			un_dim2) * un_dim1] * x[i__ + (j - 1 + (k - 1) * 
			x_dim2) * x_dim1] - uw[i__ + 1 + (j + (k - 1) * 
			uw_dim2) * uw_dim1] * x[i__ + 1 + (j + (k - 1) * 
			x_dim2) * x_dim1] - ue[i__ - 1 + (j + (k - 1) * 
			ue_dim2) * ue_dim1] * x[i__ - 1 + (j + (k - 1) * 
			x_dim2) * x_dim1] - usw[i__ + 1 + (j + 1 + (k - 1) * 
			usw_dim2) * usw_dim1] * x[i__ + 1 + (j + 1 + (k - 1) *
			 x_dim2) * x_dim1] - use[i__ - 1 + (j + 1 + (k - 1) * 
			use_dim2) * use_dim1] * x[i__ - 1 + (j + 1 + (k - 1) *
			 x_dim2) * x_dim1] - unw[i__ + 1 + (j - 1 + (k - 1) * 
			unw_dim2) * unw_dim1] * x[i__ + 1 + (j - 1 + (k - 1) *
			 x_dim2) * x_dim1] - une[i__ - 1 + (j - 1 + (k - 1) * 
			une_dim2) * une_dim1] * x[i__ - 1 + (j - 1 + (k - 1) *
			 x_dim2) * x_dim1];
		y[i__ + (j + k * y_dim2) * y_dim1] = tmpo + tmpu + tmpd + oc[
			i__ + (j + k * oc_dim2) * oc_dim1] * x[i__ + (j + k * 
			x_dim2) * x_dim1] + w1[i__ + (j + k * w1_dim2) * 
			w1_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* nmatvecd27_1s__ */

/* Subroutine */ int nmresid_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, 
	doublereal *x, doublereal *r__, doublereal *w1)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int nmresid7_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *), nmresid27_(integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static integer numdia;

    /* Fortran I/O blocks */
    static cilist io___37 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the residual routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --fc;
    --x;
    --r__;
    --w1;

    /* Function Body */
    numdia = ipc[11];
    if (numdia == 7) {
	nmresid7_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[1], &fc[1]
		, &x[1], &r__[1], &w1[1]);
    } else if (numdia == 27) {
	nmresid27_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[1], &fc[
		1], &x[1], &r__[1], &w1[1]);
    } else {
	s_wsle(&io___37);
	do_lio(&c__9, &c__1, "% NMRESID: invalid stencil type given...", (
		ftnlen)40);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* nmresid_ */

/* Subroutine */ int nmresid7_(integer *nx, integer *ny, integer *nz, integer 
	*ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc,
	 doublereal *x, doublereal *r__, doublereal *w1)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Local variables */
    extern /* Subroutine */ int nmresid7_1s__(integer *, integer *, integer *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the residual routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --fc;
    --x;
    --r__;
    --w1;

    /* Function Body */
    nmresid7_1s__(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[1], &fc[
	    1], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 <<
	     2) + 1], &x[1], &r__[1], &w1[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* nmresid7_ */

/* Subroutine */ int nmresid7_1s__(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, 
	doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, 
	doublereal *x, doublereal *r__, doublereal *w1)
{
    /* System generated locals */
    integer oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1,
	     uc_dim2, uc_offset, cc_dim1, cc_dim2, cc_offset, fc_dim1, 
	    fc_dim2, fc_offset, oc_dim1, oc_dim2, oc_offset, x_dim1, x_dim2, 
	    x_offset, r_dim1, r_dim2, r_offset, w1_dim1, w1_dim2, w1_offset, 
	    i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;
    extern /* Subroutine */ int c_vec__(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *);
    static integer ipkey;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the residual. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** first get vector noNlinear term to avoid subroutine calls *** */
    /* Parameter adjustments */
    w1_dim1 = *nx;
    w1_dim2 = *ny;
    w1_offset = 1 + w1_dim1 * (1 + w1_dim2);
    w1 -= w1_offset;
    r_dim1 = *nx;
    r_dim2 = *ny;
    r_offset = 1 + r_dim1 * (1 + r_dim2);
    r__ -= r_offset;
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
    ipkey = ipc[10];
    c_vec__(&cc[cc_offset], &x[x_offset], &w1[w1_offset], nx, ny, nz, &ipkey);
/* * */
/* *    *** the residual *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		r__[i__ + (j + k * r_dim2) * r_dim1] = fc[i__ + (j + k * 
			fc_dim2) * fc_dim1] + on[i__ + (j + k * on_dim2) * 
			on_dim1] * x[i__ + (j + 1 + k * x_dim2) * x_dim1] + 
			on[i__ + (j - 1 + k * on_dim2) * on_dim1] * x[i__ + (
			j - 1 + k * x_dim2) * x_dim1] + oe[i__ + (j + k * 
			oe_dim2) * oe_dim1] * x[i__ + 1 + (j + k * x_dim2) * 
			x_dim1] + oe[i__ - 1 + (j + k * oe_dim2) * oe_dim1] * 
			x[i__ - 1 + (j + k * x_dim2) * x_dim1] + uc[i__ + (j 
			+ (k - 1) * uc_dim2) * uc_dim1] * x[i__ + (j + (k - 1)
			 * x_dim2) * x_dim1] + uc[i__ + (j + k * uc_dim2) * 
			uc_dim1] * x[i__ + (j + (k + 1) * x_dim2) * x_dim1] - 
			oc[i__ + (j + k * oc_dim2) * oc_dim1] * x[i__ + (j + 
			k * x_dim2) * x_dim1] - w1[i__ + (j + k * w1_dim2) * 
			w1_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* nmresid7_1s__ */

/* Subroutine */ int nmresid27_(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, 
	doublereal *fc, doublereal *x, doublereal *r__, doublereal *w1)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Local variables */
    extern /* Subroutine */ int nmresid27_1s__(integer *, integer *, integer *
	    , integer *, doublereal *, doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-struCture into diagoNals */
/* *    and then call the residual routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in oNe step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --fc;
    --x;
    --r__;
    --w1;

    /* Function Body */
    nmresid27_1s__(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &cc[1], &
	    fc[1], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(
	    ac_dim1 << 2) + 1], &ac[ac_dim1 * 5 + 1], &ac[ac_dim1 * 6 + 1], &
	    ac[ac_dim1 * 7 + 1], &ac[(ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1]
	    , &ac[ac_dim1 * 10 + 1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 
	    + 1], &ac[ac_dim1 * 13 + 1], &ac[ac_dim1 * 14 + 1], &x[1], &r__[1]
	    , &w1[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* nmresid27_ */

/* Subroutine */ int nmresid27_1s__(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, 
	doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, 
	doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, 
	doublereal *un, doublereal *us, doublereal *une, doublereal *unw, 
	doublereal *use, doublereal *usw, doublereal *x, doublereal *r__, 
	doublereal *w1)
{
    /* System generated locals */
    integer oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1,
	     uc_dim2, uc_offset, one_dim1, one_dim2, one_offset, onw_dim1, 
	    onw_dim2, onw_offset, ue_dim1, ue_dim2, ue_offset, uw_dim1, 
	    uw_dim2, uw_offset, un_dim1, un_dim2, un_offset, us_dim1, us_dim2,
	     us_offset, une_dim1, une_dim2, une_offset, unw_dim1, unw_dim2, 
	    unw_offset, use_dim1, use_dim2, use_offset, usw_dim1, usw_dim2, 
	    usw_offset, cc_dim1, cc_dim2, cc_offset, fc_dim1, fc_dim2, 
	    fc_offset, oc_dim1, oc_dim2, oc_offset, x_dim1, x_dim2, x_offset, 
	    r_dim1, r_dim2, r_offset, w1_dim1, w1_dim2, w1_offset, i__1, i__2,
	     i__3;

    /* Local variables */
    static integer i__, j, k;
    static doublereal tmpd, tmpo, tmpu;
    extern /* Subroutine */ int c_vec__(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *);
    static integer ipkey;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    compute the residual. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** first get vector noNlinear term to avoid subroutine calls *** */
    /* Parameter adjustments */
    w1_dim1 = *nx;
    w1_dim2 = *ny;
    w1_offset = 1 + w1_dim1 * (1 + w1_dim2);
    w1 -= w1_offset;
    r_dim1 = *nx;
    r_dim2 = *ny;
    r_offset = 1 + r_dim1 * (1 + r_dim2);
    r__ -= r_offset;
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
    ipkey = ipc[10];
    c_vec__(&cc[cc_offset], &x[x_offset], &w1[w1_offset], nx, ny, nz, &ipkey);
/* * */
/* *    *** the residual *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		tmpo = on[i__ + (j + k * on_dim2) * on_dim1] * x[i__ + (j + 1 
			+ k * x_dim2) * x_dim1] + on[i__ + (j - 1 + k * 
			on_dim2) * on_dim1] * x[i__ + (j - 1 + k * x_dim2) * 
			x_dim1] + oe[i__ + (j + k * oe_dim2) * oe_dim1] * x[
			i__ + 1 + (j + k * x_dim2) * x_dim1] + oe[i__ - 1 + (
			j + k * oe_dim2) * oe_dim1] * x[i__ - 1 + (j + k * 
			x_dim2) * x_dim1] + one[i__ + (j + k * one_dim2) * 
			one_dim1] * x[i__ + 1 + (j + 1 + k * x_dim2) * x_dim1]
			 + onw[i__ + (j + k * onw_dim2) * onw_dim1] * x[i__ - 
			1 + (j + 1 + k * x_dim2) * x_dim1] + onw[i__ + 1 + (j 
			- 1 + k * onw_dim2) * onw_dim1] * x[i__ + 1 + (j - 1 
			+ k * x_dim2) * x_dim1] + one[i__ - 1 + (j - 1 + k * 
			one_dim2) * one_dim1] * x[i__ - 1 + (j - 1 + k * 
			x_dim2) * x_dim1];
		tmpu = uc[i__ + (j + k * uc_dim2) * uc_dim1] * x[i__ + (j + (
			k + 1) * x_dim2) * x_dim1] + un[i__ + (j + k * 
			un_dim2) * un_dim1] * x[i__ + (j + 1 + (k + 1) * 
			x_dim2) * x_dim1] + us[i__ + (j + k * us_dim2) * 
			us_dim1] * x[i__ + (j - 1 + (k + 1) * x_dim2) * 
			x_dim1] + ue[i__ + (j + k * ue_dim2) * ue_dim1] * x[
			i__ + 1 + (j + (k + 1) * x_dim2) * x_dim1] + uw[i__ + 
			(j + k * uw_dim2) * uw_dim1] * x[i__ - 1 + (j + (k + 
			1) * x_dim2) * x_dim1] + une[i__ + (j + k * une_dim2) 
			* une_dim1] * x[i__ + 1 + (j + 1 + (k + 1) * x_dim2) *
			 x_dim1] + unw[i__ + (j + k * unw_dim2) * unw_dim1] * 
			x[i__ - 1 + (j + 1 + (k + 1) * x_dim2) * x_dim1] + 
			use[i__ + (j + k * use_dim2) * use_dim1] * x[i__ + 1 
			+ (j - 1 + (k + 1) * x_dim2) * x_dim1] + usw[i__ + (j 
			+ k * usw_dim2) * usw_dim1] * x[i__ - 1 + (j - 1 + (k 
			+ 1) * x_dim2) * x_dim1];
		tmpd = uc[i__ + (j + (k - 1) * uc_dim2) * uc_dim1] * x[i__ + (
			j + (k - 1) * x_dim2) * x_dim1] + us[i__ + (j + 1 + (
			k - 1) * us_dim2) * us_dim1] * x[i__ + (j + 1 + (k - 
			1) * x_dim2) * x_dim1] + un[i__ + (j - 1 + (k - 1) * 
			un_dim2) * un_dim1] * x[i__ + (j - 1 + (k - 1) * 
			x_dim2) * x_dim1] + uw[i__ + 1 + (j + (k - 1) * 
			uw_dim2) * uw_dim1] * x[i__ + 1 + (j + (k - 1) * 
			x_dim2) * x_dim1] + ue[i__ - 1 + (j + (k - 1) * 
			ue_dim2) * ue_dim1] * x[i__ - 1 + (j + (k - 1) * 
			x_dim2) * x_dim1] + usw[i__ + 1 + (j + 1 + (k - 1) * 
			usw_dim2) * usw_dim1] * x[i__ + 1 + (j + 1 + (k - 1) *
			 x_dim2) * x_dim1] + use[i__ - 1 + (j + 1 + (k - 1) * 
			use_dim2) * use_dim1] * x[i__ - 1 + (j + 1 + (k - 1) *
			 x_dim2) * x_dim1] + unw[i__ + 1 + (j - 1 + (k - 1) * 
			unw_dim2) * unw_dim1] * x[i__ + 1 + (j - 1 + (k - 1) *
			 x_dim2) * x_dim1] + une[i__ - 1 + (j - 1 + (k - 1) * 
			une_dim2) * une_dim1] * x[i__ - 1 + (j - 1 + (k - 1) *
			 x_dim2) * x_dim1];
		r__[i__ + (j + k * r_dim2) * r_dim1] = fc[i__ + (j + k * 
			fc_dim2) * fc_dim1] + tmpo + tmpu + tmpd - oc[i__ + (
			j + k * oc_dim2) * oc_dim1] * x[i__ + (j + k * x_dim2)
			 * x_dim1] - w1[i__ + (j + k * w1_dim2) * w1_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* nmresid27_1s__ */

/* Subroutine */ int interp_(integer *nxc, integer *nyc, integer *nzc, 
	integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal 
	*xout, doublereal *pc)
{
    /* System generated locals */
    integer pc_dim1, pc_offset;

    /* Local variables */
    extern /* Subroutine */ int interp2_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    apply the prolongation operator. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** doit *** */
/* ZZZZ call interpZ(nxc,nyc,nzc,nxf,nyf,nzf,xin,xout) */
    /* Parameter adjustments */
    pc_dim1 = *nxc * *nyc * *nzc;
    pc_offset = 1 + pc_dim1;
    pc -= pc_offset;
    --xin;
    --xout;

    /* Function Body */
    interp2_(nxc, nyc, nzc, nxf, nyf, nzf, &xin[1], &xout[1], &pc[pc_dim1 + 1]
	    , &pc[(pc_dim1 << 1) + 1], &pc[pc_dim1 * 3 + 1], &pc[(pc_dim1 << 
	    2) + 1], &pc[pc_dim1 * 5 + 1], &pc[pc_dim1 * 6 + 1], &pc[pc_dim1 *
	     7 + 1], &pc[(pc_dim1 << 3) + 1], &pc[pc_dim1 * 9 + 1], &pc[
	    pc_dim1 * 10 + 1], &pc[pc_dim1 * 11 + 1], &pc[pc_dim1 * 12 + 1], &
	    pc[pc_dim1 * 13 + 1], &pc[pc_dim1 * 14 + 1], &pc[pc_dim1 * 15 + 1]
	    , &pc[(pc_dim1 << 4) + 1], &pc[pc_dim1 * 17 + 1], &pc[pc_dim1 * 
	    18 + 1], &pc[pc_dim1 * 19 + 1], &pc[pc_dim1 * 20 + 1], &pc[
	    pc_dim1 * 21 + 1], &pc[pc_dim1 * 22 + 1], &pc[pc_dim1 * 23 + 1], &
	    pc[pc_dim1 * 24 + 1], &pc[pc_dim1 * 25 + 1], &pc[pc_dim1 * 26 + 1]
	    , &pc[pc_dim1 * 27 + 1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* interp_ */

/* Subroutine */ int interp2_(integer *nxc, integer *nyc, integer *nzc, 
	integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal 
	*xout, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *
	ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *
	opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *
	ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *
	upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal 
	*dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *
	dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw)
{
    /* System generated locals */
    integer xin_dim1, xin_dim2, xin_offset, xout_dim1, xout_dim2, xout_offset,
	     opc_dim1, opc_dim2, opc_offset, opn_dim1, opn_dim2, opn_offset, 
	    ops_dim1, ops_dim2, ops_offset, ope_dim1, ope_dim2, ope_offset, 
	    opw_dim1, opw_dim2, opw_offset, opne_dim1, opne_dim2, opne_offset,
	     opnw_dim1, opnw_dim2, opnw_offset, opse_dim1, opse_dim2, 
	    opse_offset, opsw_dim1, opsw_dim2, opsw_offset, upc_dim1, 
	    upc_dim2, upc_offset, upn_dim1, upn_dim2, upn_offset, ups_dim1, 
	    ups_dim2, ups_offset, upe_dim1, upe_dim2, upe_offset, upw_dim1, 
	    upw_dim2, upw_offset, upne_dim1, upne_dim2, upne_offset, 
	    upnw_dim1, upnw_dim2, upnw_offset, upse_dim1, upse_dim2, 
	    upse_offset, upsw_dim1, upsw_dim2, upsw_offset, dpc_dim1, 
	    dpc_dim2, dpc_offset, dpn_dim1, dpn_dim2, dpn_offset, dps_dim1, 
	    dps_dim2, dps_offset, dpe_dim1, dpe_dim2, dpe_offset, dpw_dim1, 
	    dpw_dim2, dpw_offset, dpne_dim1, dpne_dim2, dpne_offset, 
	    dpnw_dim1, dpnw_dim2, dpnw_offset, dpse_dim1, dpse_dim2, 
	    dpse_offset, dpsw_dim1, dpsw_dim2, dpsw_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, ii, jj, kk;
    extern /* Subroutine */ int fbound00_(integer *, integer *, integer *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    apply the prolongation operator. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* * ********************************************************************* */
/* * setup */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** verify correctness of the input boundary points *** */
    /* Parameter adjustments */
    dpsw_dim1 = *nxc;
    dpsw_dim2 = *nyc;
    dpsw_offset = 1 + dpsw_dim1 * (1 + dpsw_dim2);
    dpsw -= dpsw_offset;
    dpse_dim1 = *nxc;
    dpse_dim2 = *nyc;
    dpse_offset = 1 + dpse_dim1 * (1 + dpse_dim2);
    dpse -= dpse_offset;
    dpnw_dim1 = *nxc;
    dpnw_dim2 = *nyc;
    dpnw_offset = 1 + dpnw_dim1 * (1 + dpnw_dim2);
    dpnw -= dpnw_offset;
    dpne_dim1 = *nxc;
    dpne_dim2 = *nyc;
    dpne_offset = 1 + dpne_dim1 * (1 + dpne_dim2);
    dpne -= dpne_offset;
    dpw_dim1 = *nxc;
    dpw_dim2 = *nyc;
    dpw_offset = 1 + dpw_dim1 * (1 + dpw_dim2);
    dpw -= dpw_offset;
    dpe_dim1 = *nxc;
    dpe_dim2 = *nyc;
    dpe_offset = 1 + dpe_dim1 * (1 + dpe_dim2);
    dpe -= dpe_offset;
    dps_dim1 = *nxc;
    dps_dim2 = *nyc;
    dps_offset = 1 + dps_dim1 * (1 + dps_dim2);
    dps -= dps_offset;
    dpn_dim1 = *nxc;
    dpn_dim2 = *nyc;
    dpn_offset = 1 + dpn_dim1 * (1 + dpn_dim2);
    dpn -= dpn_offset;
    dpc_dim1 = *nxc;
    dpc_dim2 = *nyc;
    dpc_offset = 1 + dpc_dim1 * (1 + dpc_dim2);
    dpc -= dpc_offset;
    upsw_dim1 = *nxc;
    upsw_dim2 = *nyc;
    upsw_offset = 1 + upsw_dim1 * (1 + upsw_dim2);
    upsw -= upsw_offset;
    upse_dim1 = *nxc;
    upse_dim2 = *nyc;
    upse_offset = 1 + upse_dim1 * (1 + upse_dim2);
    upse -= upse_offset;
    upnw_dim1 = *nxc;
    upnw_dim2 = *nyc;
    upnw_offset = 1 + upnw_dim1 * (1 + upnw_dim2);
    upnw -= upnw_offset;
    upne_dim1 = *nxc;
    upne_dim2 = *nyc;
    upne_offset = 1 + upne_dim1 * (1 + upne_dim2);
    upne -= upne_offset;
    upw_dim1 = *nxc;
    upw_dim2 = *nyc;
    upw_offset = 1 + upw_dim1 * (1 + upw_dim2);
    upw -= upw_offset;
    upe_dim1 = *nxc;
    upe_dim2 = *nyc;
    upe_offset = 1 + upe_dim1 * (1 + upe_dim2);
    upe -= upe_offset;
    ups_dim1 = *nxc;
    ups_dim2 = *nyc;
    ups_offset = 1 + ups_dim1 * (1 + ups_dim2);
    ups -= ups_offset;
    upn_dim1 = *nxc;
    upn_dim2 = *nyc;
    upn_offset = 1 + upn_dim1 * (1 + upn_dim2);
    upn -= upn_offset;
    upc_dim1 = *nxc;
    upc_dim2 = *nyc;
    upc_offset = 1 + upc_dim1 * (1 + upc_dim2);
    upc -= upc_offset;
    opsw_dim1 = *nxc;
    opsw_dim2 = *nyc;
    opsw_offset = 1 + opsw_dim1 * (1 + opsw_dim2);
    opsw -= opsw_offset;
    opse_dim1 = *nxc;
    opse_dim2 = *nyc;
    opse_offset = 1 + opse_dim1 * (1 + opse_dim2);
    opse -= opse_offset;
    opnw_dim1 = *nxc;
    opnw_dim2 = *nyc;
    opnw_offset = 1 + opnw_dim1 * (1 + opnw_dim2);
    opnw -= opnw_offset;
    opne_dim1 = *nxc;
    opne_dim2 = *nyc;
    opne_offset = 1 + opne_dim1 * (1 + opne_dim2);
    opne -= opne_offset;
    opw_dim1 = *nxc;
    opw_dim2 = *nyc;
    opw_offset = 1 + opw_dim1 * (1 + opw_dim2);
    opw -= opw_offset;
    ope_dim1 = *nxc;
    ope_dim2 = *nyc;
    ope_offset = 1 + ope_dim1 * (1 + ope_dim2);
    ope -= ope_offset;
    ops_dim1 = *nxc;
    ops_dim2 = *nyc;
    ops_offset = 1 + ops_dim1 * (1 + ops_dim2);
    ops -= ops_offset;
    opn_dim1 = *nxc;
    opn_dim2 = *nyc;
    opn_offset = 1 + opn_dim1 * (1 + opn_dim2);
    opn -= opn_offset;
    opc_dim1 = *nxc;
    opc_dim2 = *nyc;
    opc_offset = 1 + opc_dim1 * (1 + opc_dim2);
    opc -= opc_offset;
    xin_dim1 = *nxc;
    xin_dim2 = *nyc;
    xin_offset = 1 + xin_dim1 * (1 + xin_dim2);
    xin -= xin_offset;
    xout_dim1 = *nxf;
    xout_dim2 = *nyf;
    xout_offset = 1 + xout_dim1 * (1 + xout_dim2);
    xout -= xout_offset;

    /* Function Body */
    fbound00_(nxc, nyc, nzc, &xin[xin_offset]);
/* * */
/* *    *** doit *** */
/* mdir 3 1 */
    i__1 = *nzf - 2;
    for (k = 1; k <= i__1; k += 2) {
	kk = (k - 1) / 2 + 1;
/* mdir 3 2 */
	i__2 = *nyf - 2;
	for (j = 1; j <= i__2; j += 2) {
	    jj = (j - 1) / 2 + 1;
/* mdir 3 3 */
	    i__3 = *nxf - 2;
	    for (i__ = 1; i__ <= i__3; i__ += 2) {
		ii = (i__ - 1) / 2 + 1;
/* * */
/* * ********************************************************************* */
/* * type 1 -- fine grid points common to a coarse grid point */
/* * ********************************************************************* */
/* * */
/* *             *** copy coinciding points from coarse grid to fine grid *** */
		xout[i__ + (j + k * xout_dim2) * xout_dim1] = xin[ii + (jj + 
			kk * xin_dim2) * xin_dim1];
/* * */
/* * ********************************************************************* */
/* * type 2 -- fine grid points common to a coarse grid plane */
/* * ********************************************************************* */
/* * */
/* *             *** fine grid pts common only to y-z planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on x-row) *** */
		xout[i__ + 1 + (j + k * xout_dim2) * xout_dim1] = ope[ii + (
			jj + kk * ope_dim2) * ope_dim1] * xin[ii + (jj + kk * 
			xin_dim2) * xin_dim1] + opw[ii + 1 + (jj + kk * 
			opw_dim2) * opw_dim1] * xin[ii + 1 + (jj + kk * 
			xin_dim2) * xin_dim1];
/* * */
/* *             *** fine grid pts common only to x-z planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on a y-row) *** */
		xout[i__ + (j + 1 + k * xout_dim2) * xout_dim1] = opn[ii + (
			jj + kk * opn_dim2) * opn_dim1] * xin[ii + (jj + kk * 
			xin_dim2) * xin_dim1] + ops[ii + (jj + 1 + kk * 
			ops_dim2) * ops_dim1] * xin[ii + (jj + 1 + kk * 
			xin_dim2) * xin_dim1];
/* * */
/* *             *** fine grid pts common only to x-y planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on a z-row) *** */
		xout[i__ + (j + (k + 1) * xout_dim2) * xout_dim1] = upc[ii + (
			jj + kk * upc_dim2) * upc_dim1] * xin[ii + (jj + kk * 
			xin_dim2) * xin_dim1] + dpc[ii + (jj + (kk + 1) * 
			dpc_dim2) * dpc_dim1] * xin[ii + (jj + (kk + 1) * 
			xin_dim2) * xin_dim1];
/* * */
/* * ********************************************************************* */
/* * type 3 -- fine grid points common to a coarse grid line */
/* * ********************************************************************* */
/* * */
/* *             *** fine grid pts common only to z planes on coarse grid *** */
/* *             *** (intermediate pts between 4 grid pts on the xy-plane*** */
		xout[i__ + 1 + (j + 1 + k * xout_dim2) * xout_dim1] = opne[ii 
			+ (jj + kk * opne_dim2) * opne_dim1] * xin[ii + (jj + 
			kk * xin_dim2) * xin_dim1] + opnw[ii + 1 + (jj + kk * 
			opnw_dim2) * opnw_dim1] * xin[ii + 1 + (jj + kk * 
			xin_dim2) * xin_dim1] + opse[ii + (jj + 1 + kk * 
			opse_dim2) * opse_dim1] * xin[ii + (jj + 1 + kk * 
			xin_dim2) * xin_dim1] + opsw[ii + 1 + (jj + 1 + kk * 
			opsw_dim2) * opsw_dim1] * xin[ii + 1 + (jj + 1 + kk * 
			xin_dim2) * xin_dim1];
/* * */
/* *             *** fine grid pts common only to y planes on coarse grid *** */
/* *             *** (intermediate pts between 4 grid pts on the xz-plane*** */
		xout[i__ + 1 + (j + (k + 1) * xout_dim2) * xout_dim1] = upe[
			ii + (jj + kk * upe_dim2) * upe_dim1] * xin[ii + (jj 
			+ kk * xin_dim2) * xin_dim1] + upw[ii + 1 + (jj + kk *
			 upw_dim2) * upw_dim1] * xin[ii + 1 + (jj + kk * 
			xin_dim2) * xin_dim1] + dpe[ii + (jj + (kk + 1) * 
			dpe_dim2) * dpe_dim1] * xin[ii + (jj + (kk + 1) * 
			xin_dim2) * xin_dim1] + dpw[ii + 1 + (jj + (kk + 1) * 
			dpw_dim2) * dpw_dim1] * xin[ii + 1 + (jj + (kk + 1) * 
			xin_dim2) * xin_dim1];
/* * */
/* *             *** fine grid pts common only to x planes on coarse grid *** */
/* *             *** (intermediate pts between 4 grid pts on the yz-plane*** */
		xout[i__ + (j + 1 + (k + 1) * xout_dim2) * xout_dim1] = upn[
			ii + (jj + kk * upn_dim2) * upn_dim1] * xin[ii + (jj 
			+ kk * xin_dim2) * xin_dim1] + ups[ii + (jj + 1 + kk *
			 ups_dim2) * ups_dim1] * xin[ii + (jj + 1 + kk * 
			xin_dim2) * xin_dim1] + dpn[ii + (jj + (kk + 1) * 
			dpn_dim2) * dpn_dim1] * xin[ii + (jj + (kk + 1) * 
			xin_dim2) * xin_dim1] + dps[ii + (jj + 1 + (kk + 1) * 
			dps_dim2) * dps_dim1] * xin[ii + (jj + 1 + (kk + 1) * 
			xin_dim2) * xin_dim1];
/* * */
/* * ********************************************************************* */
/* * type 4 -- fine grid points not common to coarse grid pts/lines/planes */
/* * ********************************************************************* */
/* * */
/* *             *** completely interior points *** */
		xout[i__ + 1 + (j + 1 + (k + 1) * xout_dim2) * xout_dim1] = 
			upne[ii + (jj + kk * upne_dim2) * upne_dim1] * xin[ii 
			+ (jj + kk * xin_dim2) * xin_dim1] + upnw[ii + 1 + (
			jj + kk * upnw_dim2) * upnw_dim1] * xin[ii + 1 + (jj 
			+ kk * xin_dim2) * xin_dim1] + upse[ii + (jj + 1 + kk 
			* upse_dim2) * upse_dim1] * xin[ii + (jj + 1 + kk * 
			xin_dim2) * xin_dim1] + upsw[ii + 1 + (jj + 1 + kk * 
			upsw_dim2) * upsw_dim1] * xin[ii + 1 + (jj + 1 + kk * 
			xin_dim2) * xin_dim1] + dpne[ii + (jj + (kk + 1) * 
			dpne_dim2) * dpne_dim1] * xin[ii + (jj + (kk + 1) * 
			xin_dim2) * xin_dim1] + dpnw[ii + 1 + (jj + (kk + 1) *
			 dpnw_dim2) * dpnw_dim1] * xin[ii + 1 + (jj + (kk + 1)
			 * xin_dim2) * xin_dim1] + dpse[ii + (jj + 1 + (kk + 
			1) * dpse_dim2) * dpse_dim1] * xin[ii + (jj + 1 + (kk 
			+ 1) * xin_dim2) * xin_dim1] + dpsw[ii + 1 + (jj + 1 
			+ (kk + 1) * dpsw_dim2) * dpsw_dim1] * xin[ii + 1 + (
			jj + 1 + (kk + 1) * xin_dim2) * xin_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** verify correctness of the output boundary points *** */
    fbound00_(nxf, nyf, nzf, &xout[xout_offset]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* interp2_ */

/* Subroutine */ int restrc_(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, doublereal *xin, doublereal 
	*xout, doublereal *pc)
{
    /* System generated locals */
    integer pc_dim1, pc_offset;

    /* Local variables */
    extern /* Subroutine */ int restrc2_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    apply the restriction operator. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** doit *** */
/* ZZZ  call restrcZ(nxf,nyf,nzf,nxc,nyc,nzc,xin,xout) */
    /* Parameter adjustments */
    pc_dim1 = *nxc * *nyc * *nzc;
    pc_offset = 1 + pc_dim1;
    pc -= pc_offset;
    --xin;
    --xout;

    /* Function Body */
    restrc2_(nxf, nyf, nzf, nxc, nyc, nzc, &xin[1], &xout[1], &pc[pc_dim1 + 1]
	    , &pc[(pc_dim1 << 1) + 1], &pc[pc_dim1 * 3 + 1], &pc[(pc_dim1 << 
	    2) + 1], &pc[pc_dim1 * 5 + 1], &pc[pc_dim1 * 6 + 1], &pc[pc_dim1 *
	     7 + 1], &pc[(pc_dim1 << 3) + 1], &pc[pc_dim1 * 9 + 1], &pc[
	    pc_dim1 * 10 + 1], &pc[pc_dim1 * 11 + 1], &pc[pc_dim1 * 12 + 1], &
	    pc[pc_dim1 * 13 + 1], &pc[pc_dim1 * 14 + 1], &pc[pc_dim1 * 15 + 1]
	    , &pc[(pc_dim1 << 4) + 1], &pc[pc_dim1 * 17 + 1], &pc[pc_dim1 * 
	    18 + 1], &pc[pc_dim1 * 19 + 1], &pc[pc_dim1 * 20 + 1], &pc[
	    pc_dim1 * 21 + 1], &pc[pc_dim1 * 22 + 1], &pc[pc_dim1 * 23 + 1], &
	    pc[pc_dim1 * 24 + 1], &pc[pc_dim1 * 25 + 1], &pc[pc_dim1 * 26 + 1]
	    , &pc[pc_dim1 * 27 + 1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* restrc_ */

/* Subroutine */ int restrc2_(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, doublereal *xin, doublereal 
	*xout, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *
	ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *
	opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *
	ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *
	upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal 
	*dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *
	dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw)
{
    /* System generated locals */
    integer xin_dim1, xin_dim2, xin_offset, xout_dim1, xout_dim2, xout_offset,
	     opc_dim1, opc_dim2, opc_offset, opn_dim1, opn_dim2, opn_offset, 
	    ops_dim1, ops_dim2, ops_offset, ope_dim1, ope_dim2, ope_offset, 
	    opw_dim1, opw_dim2, opw_offset, opne_dim1, opne_dim2, opne_offset,
	     opnw_dim1, opnw_dim2, opnw_offset, opse_dim1, opse_dim2, 
	    opse_offset, opsw_dim1, opsw_dim2, opsw_offset, upc_dim1, 
	    upc_dim2, upc_offset, upn_dim1, upn_dim2, upn_offset, ups_dim1, 
	    ups_dim2, ups_offset, upe_dim1, upe_dim2, upe_offset, upw_dim1, 
	    upw_dim2, upw_offset, upne_dim1, upne_dim2, upne_offset, 
	    upnw_dim1, upnw_dim2, upnw_offset, upse_dim1, upse_dim2, 
	    upse_offset, upsw_dim1, upsw_dim2, upsw_offset, dpc_dim1, 
	    dpc_dim2, dpc_offset, dpn_dim1, dpn_dim2, dpn_offset, dps_dim1, 
	    dps_dim2, dps_offset, dpe_dim1, dpe_dim2, dpe_offset, dpw_dim1, 
	    dpw_dim2, dpw_offset, dpne_dim1, dpne_dim2, dpne_offset, 
	    dpnw_dim1, dpnw_dim2, dpnw_offset, dpse_dim1, dpse_dim2, 
	    dpse_offset, dpsw_dim1, dpsw_dim2, dpsw_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, ii, jj, kk;
    static doublereal tmpd, tmpo, tmpu, dimfac;
    extern /* Subroutine */ int fbound00_(integer *, integer *, integer *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    generic restriction of a fine grid function to coarse grid. */
/* *    this is the adjoint of some prolongation: */
/* * */
/* *         R = 2**dim P^T, */
/* * */
/* *    where dim=3 is the number of spatial dimensions, and P is the */
/* *    prolongation operator. */
/* * */
/* *    with the inner-product weighed by 2**dim, where here dim=3, */
/* *    this operator is the adjoint of P. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** verify correctness of the input boundary points *** */
    /* Parameter adjustments */
    xin_dim1 = *nxf;
    xin_dim2 = *nyf;
    xin_offset = 1 + xin_dim1 * (1 + xin_dim2);
    xin -= xin_offset;
    dpsw_dim1 = *nxc;
    dpsw_dim2 = *nyc;
    dpsw_offset = 1 + dpsw_dim1 * (1 + dpsw_dim2);
    dpsw -= dpsw_offset;
    dpse_dim1 = *nxc;
    dpse_dim2 = *nyc;
    dpse_offset = 1 + dpse_dim1 * (1 + dpse_dim2);
    dpse -= dpse_offset;
    dpnw_dim1 = *nxc;
    dpnw_dim2 = *nyc;
    dpnw_offset = 1 + dpnw_dim1 * (1 + dpnw_dim2);
    dpnw -= dpnw_offset;
    dpne_dim1 = *nxc;
    dpne_dim2 = *nyc;
    dpne_offset = 1 + dpne_dim1 * (1 + dpne_dim2);
    dpne -= dpne_offset;
    dpw_dim1 = *nxc;
    dpw_dim2 = *nyc;
    dpw_offset = 1 + dpw_dim1 * (1 + dpw_dim2);
    dpw -= dpw_offset;
    dpe_dim1 = *nxc;
    dpe_dim2 = *nyc;
    dpe_offset = 1 + dpe_dim1 * (1 + dpe_dim2);
    dpe -= dpe_offset;
    dps_dim1 = *nxc;
    dps_dim2 = *nyc;
    dps_offset = 1 + dps_dim1 * (1 + dps_dim2);
    dps -= dps_offset;
    dpn_dim1 = *nxc;
    dpn_dim2 = *nyc;
    dpn_offset = 1 + dpn_dim1 * (1 + dpn_dim2);
    dpn -= dpn_offset;
    dpc_dim1 = *nxc;
    dpc_dim2 = *nyc;
    dpc_offset = 1 + dpc_dim1 * (1 + dpc_dim2);
    dpc -= dpc_offset;
    upsw_dim1 = *nxc;
    upsw_dim2 = *nyc;
    upsw_offset = 1 + upsw_dim1 * (1 + upsw_dim2);
    upsw -= upsw_offset;
    upse_dim1 = *nxc;
    upse_dim2 = *nyc;
    upse_offset = 1 + upse_dim1 * (1 + upse_dim2);
    upse -= upse_offset;
    upnw_dim1 = *nxc;
    upnw_dim2 = *nyc;
    upnw_offset = 1 + upnw_dim1 * (1 + upnw_dim2);
    upnw -= upnw_offset;
    upne_dim1 = *nxc;
    upne_dim2 = *nyc;
    upne_offset = 1 + upne_dim1 * (1 + upne_dim2);
    upne -= upne_offset;
    upw_dim1 = *nxc;
    upw_dim2 = *nyc;
    upw_offset = 1 + upw_dim1 * (1 + upw_dim2);
    upw -= upw_offset;
    upe_dim1 = *nxc;
    upe_dim2 = *nyc;
    upe_offset = 1 + upe_dim1 * (1 + upe_dim2);
    upe -= upe_offset;
    ups_dim1 = *nxc;
    ups_dim2 = *nyc;
    ups_offset = 1 + ups_dim1 * (1 + ups_dim2);
    ups -= ups_offset;
    upn_dim1 = *nxc;
    upn_dim2 = *nyc;
    upn_offset = 1 + upn_dim1 * (1 + upn_dim2);
    upn -= upn_offset;
    upc_dim1 = *nxc;
    upc_dim2 = *nyc;
    upc_offset = 1 + upc_dim1 * (1 + upc_dim2);
    upc -= upc_offset;
    opsw_dim1 = *nxc;
    opsw_dim2 = *nyc;
    opsw_offset = 1 + opsw_dim1 * (1 + opsw_dim2);
    opsw -= opsw_offset;
    opse_dim1 = *nxc;
    opse_dim2 = *nyc;
    opse_offset = 1 + opse_dim1 * (1 + opse_dim2);
    opse -= opse_offset;
    opnw_dim1 = *nxc;
    opnw_dim2 = *nyc;
    opnw_offset = 1 + opnw_dim1 * (1 + opnw_dim2);
    opnw -= opnw_offset;
    opne_dim1 = *nxc;
    opne_dim2 = *nyc;
    opne_offset = 1 + opne_dim1 * (1 + opne_dim2);
    opne -= opne_offset;
    opw_dim1 = *nxc;
    opw_dim2 = *nyc;
    opw_offset = 1 + opw_dim1 * (1 + opw_dim2);
    opw -= opw_offset;
    ope_dim1 = *nxc;
    ope_dim2 = *nyc;
    ope_offset = 1 + ope_dim1 * (1 + ope_dim2);
    ope -= ope_offset;
    ops_dim1 = *nxc;
    ops_dim2 = *nyc;
    ops_offset = 1 + ops_dim1 * (1 + ops_dim2);
    ops -= ops_offset;
    opn_dim1 = *nxc;
    opn_dim2 = *nyc;
    opn_offset = 1 + opn_dim1 * (1 + opn_dim2);
    opn -= opn_offset;
    opc_dim1 = *nxc;
    opc_dim2 = *nyc;
    opc_offset = 1 + opc_dim1 * (1 + opc_dim2);
    opc -= opc_offset;
    xout_dim1 = *nxc;
    xout_dim2 = *nyc;
    xout_offset = 1 + xout_dim1 * (1 + xout_dim2);
    xout -= xout_offset;

    /* Function Body */
    fbound00_(nxf, nyf, nzf, &xin[xin_offset]);
/* * */
/* *    *** determine dimension factor *** */
    dimfac = 8.f;
/* * */
/* *    *** handle the interior points as average of 5 finer grid pts *** */
/* mdir 3 1 */
    i__1 = *nzc - 1;
    for (k = 2; k <= i__1; ++k) {
	kk = (k - 1 << 1) + 1;
/* mdir 3 2 */
	i__2 = *nyc - 1;
	for (j = 2; j <= i__2; ++j) {
	    jj = (j - 1 << 1) + 1;
/* mdir 3 3 */
	    i__3 = *nxc - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		ii = (i__ - 1 << 1) + 1;
/* * */
/* *             *** compute the restriction *** */
		tmpo = opc[i__ + (j + k * opc_dim2) * opc_dim1] * xin[ii + (
			jj + kk * xin_dim2) * xin_dim1] + opn[i__ + (j + k * 
			opn_dim2) * opn_dim1] * xin[ii + (jj + 1 + kk * 
			xin_dim2) * xin_dim1] + ops[i__ + (j + k * ops_dim2) *
			 ops_dim1] * xin[ii + (jj - 1 + kk * xin_dim2) * 
			xin_dim1] + ope[i__ + (j + k * ope_dim2) * ope_dim1] *
			 xin[ii + 1 + (jj + kk * xin_dim2) * xin_dim1] + opw[
			i__ + (j + k * opw_dim2) * opw_dim1] * xin[ii - 1 + (
			jj + kk * xin_dim2) * xin_dim1] + opne[i__ + (j + k * 
			opne_dim2) * opne_dim1] * xin[ii + 1 + (jj + 1 + kk * 
			xin_dim2) * xin_dim1] + opnw[i__ + (j + k * opnw_dim2)
			 * opnw_dim1] * xin[ii - 1 + (jj + 1 + kk * xin_dim2) 
			* xin_dim1] + opse[i__ + (j + k * opse_dim2) * 
			opse_dim1] * xin[ii + 1 + (jj - 1 + kk * xin_dim2) * 
			xin_dim1] + opsw[i__ + (j + k * opsw_dim2) * 
			opsw_dim1] * xin[ii - 1 + (jj - 1 + kk * xin_dim2) * 
			xin_dim1];
		tmpu = upc[i__ + (j + k * upc_dim2) * upc_dim1] * xin[ii + (
			jj + (kk + 1) * xin_dim2) * xin_dim1] + upn[i__ + (j 
			+ k * upn_dim2) * upn_dim1] * xin[ii + (jj + 1 + (kk 
			+ 1) * xin_dim2) * xin_dim1] + ups[i__ + (j + k * 
			ups_dim2) * ups_dim1] * xin[ii + (jj - 1 + (kk + 1) * 
			xin_dim2) * xin_dim1] + upe[i__ + (j + k * upe_dim2) *
			 upe_dim1] * xin[ii + 1 + (jj + (kk + 1) * xin_dim2) *
			 xin_dim1] + upw[i__ + (j + k * upw_dim2) * upw_dim1] 
			* xin[ii - 1 + (jj + (kk + 1) * xin_dim2) * xin_dim1] 
			+ upne[i__ + (j + k * upne_dim2) * upne_dim1] * xin[
			ii + 1 + (jj + 1 + (kk + 1) * xin_dim2) * xin_dim1] + 
			upnw[i__ + (j + k * upnw_dim2) * upnw_dim1] * xin[ii 
			- 1 + (jj + 1 + (kk + 1) * xin_dim2) * xin_dim1] + 
			upse[i__ + (j + k * upse_dim2) * upse_dim1] * xin[ii 
			+ 1 + (jj - 1 + (kk + 1) * xin_dim2) * xin_dim1] + 
			upsw[i__ + (j + k * upsw_dim2) * upsw_dim1] * xin[ii 
			- 1 + (jj - 1 + (kk + 1) * xin_dim2) * xin_dim1];
		tmpd = dpc[i__ + (j + k * dpc_dim2) * dpc_dim1] * xin[ii + (
			jj + (kk - 1) * xin_dim2) * xin_dim1] + dpn[i__ + (j 
			+ k * dpn_dim2) * dpn_dim1] * xin[ii + (jj + 1 + (kk 
			- 1) * xin_dim2) * xin_dim1] + dps[i__ + (j + k * 
			dps_dim2) * dps_dim1] * xin[ii + (jj - 1 + (kk - 1) * 
			xin_dim2) * xin_dim1] + dpe[i__ + (j + k * dpe_dim2) *
			 dpe_dim1] * xin[ii + 1 + (jj + (kk - 1) * xin_dim2) *
			 xin_dim1] + dpw[i__ + (j + k * dpw_dim2) * dpw_dim1] 
			* xin[ii - 1 + (jj + (kk - 1) * xin_dim2) * xin_dim1] 
			+ dpne[i__ + (j + k * dpne_dim2) * dpne_dim1] * xin[
			ii + 1 + (jj + 1 + (kk - 1) * xin_dim2) * xin_dim1] + 
			dpnw[i__ + (j + k * dpnw_dim2) * dpnw_dim1] * xin[ii 
			- 1 + (jj + 1 + (kk - 1) * xin_dim2) * xin_dim1] + 
			dpse[i__ + (j + k * dpse_dim2) * dpse_dim1] * xin[ii 
			+ 1 + (jj - 1 + (kk - 1) * xin_dim2) * xin_dim1] + 
			dpsw[i__ + (j + k * dpsw_dim2) * dpsw_dim1] * xin[ii 
			- 1 + (jj - 1 + (kk - 1) * xin_dim2) * xin_dim1];
		xout[i__ + (j + k * xout_dim2) * xout_dim1] = tmpo + tmpu + 
			tmpd;
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** verify correctness of the output boundary points *** */
    fbound00_(nxc, nyc, nzc, &xout[xout_offset]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* restrc2_ */

/* Subroutine */ int extrac_(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, doublereal *xin, doublereal 
	*xout)
{
    /* System generated locals */
    integer xin_dim1, xin_dim2, xin_offset, xout_dim1, xout_dim2, xout_offset,
	     i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, ii, jj, kk;
    extern /* Subroutine */ int fbound00_(integer *, integer *, integer *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    simple injection of a fine grid function into coarse grid. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** verify correctness of the input boundary points *** */
    /* Parameter adjustments */
    xin_dim1 = *nxf;
    xin_dim2 = *nyf;
    xin_offset = 1 + xin_dim1 * (1 + xin_dim2);
    xin -= xin_offset;
    xout_dim1 = *nxc;
    xout_dim2 = *nyc;
    xout_offset = 1 + xout_dim1 * (1 + xout_dim2);
    xout -= xout_offset;

    /* Function Body */
    fbound00_(nxf, nyf, nzf, &xin[xin_offset]);
/* * */
/* *    *** doit *** */
/* mdir 3 1 */
    i__1 = *nzc - 1;
    for (k = 2; k <= i__1; ++k) {
	kk = (k - 1 << 1) + 1;
/* mdir 3 2 */
	i__2 = *nyc - 1;
	for (j = 2; j <= i__2; ++j) {
	    jj = (j - 1 << 1) + 1;
/* mdir 3 3 */
	    i__3 = *nxc - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		ii = (i__ - 1 << 1) + 1;
/* * */
/* *             *** compute the restriction *** */
		xout[i__ + (j + k * xout_dim2) * xout_dim1] = xin[ii + (jj + 
			kk * xin_dim2) * xin_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** verify correctness of the output boundary points *** */
    fbound00_(nxc, nyc, nzc, &xout[xout_offset]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* extrac_ */

/* Subroutine */ int interpz_(integer *nxc, integer *nyc, integer *nzc, 
	integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal 
	*xout)
{
    /* System generated locals */
    integer xin_dim1, xin_dim2, xin_offset, xout_dim1, xout_dim2, xout_offset,
	     i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;
    static doublereal c0, c1, c2, c3;
    static integer ii, jj, kk;
    extern /* Subroutine */ int fbound00_(integer *, integer *, integer *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    fast trilinear interpolation. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* * ********************************************************************* */
/* * setup */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** verify correctness of the input boundary points *** */
    /* Parameter adjustments */
    xin_dim1 = *nxc;
    xin_dim2 = *nyc;
    xin_offset = 1 + xin_dim1 * (1 + xin_dim2);
    xin -= xin_offset;
    xout_dim1 = *nxf;
    xout_dim2 = *nyf;
    xout_offset = 1 + xout_dim1 * (1 + xout_dim2);
    xout -= xout_offset;

    /* Function Body */
    fbound00_(nxc, nyc, nzc, &xin[xin_offset]);
/* * */
/* *    *** set interpolation weights *** */
    c0 = 1.;
    c1 = .5f;
    c2 = .25f;
    c3 = .125f;
/* * */
/* *    *** doit *** */
/* mdir 3 1 */
    i__1 = *nzf - 2;
    for (k = 1; k <= i__1; k += 2) {
	kk = (k - 1) / 2 + 1;
/* mdir 3 2 */
	i__2 = *nyf - 2;
	for (j = 1; j <= i__2; j += 2) {
	    jj = (j - 1) / 2 + 1;
/* mdir 3 3 */
	    i__3 = *nxf - 2;
	    for (i__ = 1; i__ <= i__3; i__ += 2) {
		ii = (i__ - 1) / 2 + 1;
/* * */
/* * ********************************************************************* */
/* * type 1 -- fine grid points common to a coarse grid point */
/* * ********************************************************************* */
/* * */
/* *             *** copy coinciding points from coarse grid to fine grid *** */
		xout[i__ + (j + k * xout_dim2) * xout_dim1] = xin[ii + (jj + 
			kk * xin_dim2) * xin_dim1];
/* * */
/* * ********************************************************************* */
/* * type 2 -- fine grid points common to a coarse grid plane */
/* * ********************************************************************* */
/* * */
/* *             *** fine grid pts common only to y-z planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on x-row) *** */
		xout[i__ + 1 + (j + k * xout_dim2) * xout_dim1] = c1 * (xin[
			ii + (jj + kk * xin_dim2) * xin_dim1] + xin[ii + 1 + (
			jj + kk * xin_dim2) * xin_dim1]);
/* * */
/* *             *** fine grid pts common only to x-z planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on a y-row) *** */
		xout[i__ + (j + 1 + k * xout_dim2) * xout_dim1] = c1 * (xin[
			ii + (jj + kk * xin_dim2) * xin_dim1] + xin[ii + (jj 
			+ 1 + kk * xin_dim2) * xin_dim1]);
/* * */
/* *             *** fine grid pts common only to x-y planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on a z-row) *** */
		xout[i__ + (j + (k + 1) * xout_dim2) * xout_dim1] = c1 * (xin[
			ii + (jj + kk * xin_dim2) * xin_dim1] + xin[ii + (jj 
			+ (kk + 1) * xin_dim2) * xin_dim1]);
/* * */
/* * ********************************************************************* */
/* * type 3 -- fine grid points common to a coarse grid line */
/* * ********************************************************************* */
/* * */
/* *             *** fine grid pts common only to z planes on coarse grid *** */
/* *             *** (intermediate pts between 4 grid pts on the xy-plane*** */
		xout[i__ + 1 + (j + 1 + k * xout_dim2) * xout_dim1] = c2 * (
			xin[ii + (jj + kk * xin_dim2) * xin_dim1] + xin[ii + 
			1 + (jj + kk * xin_dim2) * xin_dim1] + xin[ii + (jj + 
			1 + kk * xin_dim2) * xin_dim1] + xin[ii + 1 + (jj + 1 
			+ kk * xin_dim2) * xin_dim1]);
/* * */
/* *             *** fine grid pts common only to y planes on coarse grid *** */
/* *             *** (intermediate pts between 4 grid pts on the xz-plane*** */
		xout[i__ + 1 + (j + (k + 1) * xout_dim2) * xout_dim1] = c2 * (
			xin[ii + (jj + kk * xin_dim2) * xin_dim1] + xin[ii + 
			1 + (jj + kk * xin_dim2) * xin_dim1] + xin[ii + (jj + 
			(kk + 1) * xin_dim2) * xin_dim1] + xin[ii + 1 + (jj + 
			(kk + 1) * xin_dim2) * xin_dim1]);
/* * */
/* *             *** fine grid pts common only to x planes on coarse grid *** */
/* *             *** (intermediate pts between 4 grid pts on the yz-plane*** */
		xout[i__ + (j + 1 + (k + 1) * xout_dim2) * xout_dim1] = c2 * (
			xin[ii + (jj + kk * xin_dim2) * xin_dim1] + xin[ii + (
			jj + 1 + kk * xin_dim2) * xin_dim1] + xin[ii + (jj + (
			kk + 1) * xin_dim2) * xin_dim1] + xin[ii + (jj + 1 + (
			kk + 1) * xin_dim2) * xin_dim1]);
/* * */
/* * ********************************************************************* */
/* * type 4 -- fine grid points not common to coarse grid pts/lines/planes */
/* * ********************************************************************* */
/* * */
/* *             *** completely interior points *** */
		xout[i__ + 1 + (j + 1 + (k + 1) * xout_dim2) * xout_dim1] = 
			c3 * (xin[ii + (jj + kk * xin_dim2) * xin_dim1] + xin[
			ii + 1 + (jj + kk * xin_dim2) * xin_dim1] + xin[ii + (
			jj + 1 + kk * xin_dim2) * xin_dim1] + xin[ii + 1 + (
			jj + 1 + kk * xin_dim2) * xin_dim1] + xin[ii + (jj + (
			kk + 1) * xin_dim2) * xin_dim1] + xin[ii + 1 + (jj + (
			kk + 1) * xin_dim2) * xin_dim1] + xin[ii + (jj + 1 + (
			kk + 1) * xin_dim2) * xin_dim1] + xin[ii + 1 + (jj + 
			1 + (kk + 1) * xin_dim2) * xin_dim1]);
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** verify correctness of the output boundary points *** */
    fbound00_(nxf, nyf, nzf, &xout[xout_offset]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* interpz_ */

/* Subroutine */ int restrcz_(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, doublereal *xin, doublereal 
	*xout)
{
    /* System generated locals */
    integer xin_dim1, xin_dim2, xin_offset, xout_dim1, xout_dim2, xout_offset,
	     i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;
    static doublereal c0, c1, c2, c3;
    static integer ii, jj, kk;
    static doublereal dimfac;
    extern /* Subroutine */ int fbound00_(integer *, integer *, integer *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    fast full-weighting restriction. */
/* * */
/* *    trilinear restriction of a fine grid function to coarse grid. */
/* *    this is the adjoint of trilinear prolongation: */
/* * */
/* *         R = 2**dim P^T, */
/* * */
/* *    where dim=3 is the number of spatial dimensions, and P is the */
/* *    prolongation operator. */
/* * */
/* *    with the inner-product weighed by 2**dim, where here dim=3, */
/* *    this operator is the adjoint of P. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** verify correctness of the input boundary points *** */
    /* Parameter adjustments */
    xin_dim1 = *nxf;
    xin_dim2 = *nyf;
    xin_offset = 1 + xin_dim1 * (1 + xin_dim2);
    xin -= xin_offset;
    xout_dim1 = *nxc;
    xout_dim2 = *nyc;
    xout_offset = 1 + xout_dim1 * (1 + xout_dim2);
    xout -= xout_offset;

    /* Function Body */
    fbound00_(nxf, nyf, nzf, &xin[xin_offset]);
/* * */
/* *    *** determine dimension factor *** */
    dimfac = 8.f;
/* * */
/* *    *** set restriction weights *** */
    c0 = 1.;
    c1 = .5f;
    c2 = .25f;
    c3 = .125f;
/* * */
/* *    *** handle the interior points as average of 5 finer grid pts *** */
/* mdir 3 1 */
    i__1 = *nzc - 1;
    for (k = 2; k <= i__1; ++k) {
	kk = (k - 1 << 1) + 1;
/* mdir 3 2 */
	i__2 = *nyc - 1;
	for (j = 2; j <= i__2; ++j) {
	    jj = (j - 1 << 1) + 1;
/* mdir 3 3 */
	    i__3 = *nxc - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		ii = (i__ - 1 << 1) + 1;
/* * */
/* *             *** compute the restriction *** */
		xout[i__ + (j + k * xout_dim2) * xout_dim1] = c0 * xin[ii + (
			jj + kk * xin_dim2) * xin_dim1] + c1 * (xin[ii - 1 + (
			jj + kk * xin_dim2) * xin_dim1] + xin[ii + 1 + (jj + 
			kk * xin_dim2) * xin_dim1] + xin[ii + (jj - 1 + kk * 
			xin_dim2) * xin_dim1] + xin[ii + (jj + 1 + kk * 
			xin_dim2) * xin_dim1] + xin[ii + (jj + (kk - 1) * 
			xin_dim2) * xin_dim1] + xin[ii + (jj + (kk + 1) * 
			xin_dim2) * xin_dim1]) + c2 * (xin[ii - 1 + (jj - 1 + 
			kk * xin_dim2) * xin_dim1] + xin[ii + 1 + (jj - 1 + 
			kk * xin_dim2) * xin_dim1] + xin[ii - 1 + (jj + 1 + 
			kk * xin_dim2) * xin_dim1] + xin[ii + 1 + (jj + 1 + 
			kk * xin_dim2) * xin_dim1] + xin[ii - 1 + (jj + (kk - 
			1) * xin_dim2) * xin_dim1] + xin[ii + 1 + (jj + (kk - 
			1) * xin_dim2) * xin_dim1] + xin[ii - 1 + (jj + (kk + 
			1) * xin_dim2) * xin_dim1] + xin[ii + 1 + (jj + (kk + 
			1) * xin_dim2) * xin_dim1] + xin[ii + (jj - 1 + (kk - 
			1) * xin_dim2) * xin_dim1] + xin[ii + (jj + 1 + (kk - 
			1) * xin_dim2) * xin_dim1] + xin[ii + (jj - 1 + (kk + 
			1) * xin_dim2) * xin_dim1] + xin[ii + (jj + 1 + (kk + 
			1) * xin_dim2) * xin_dim1]) + c3 * (xin[ii - 1 + (jj 
			- 1 + (kk - 1) * xin_dim2) * xin_dim1] + xin[ii + 1 + 
			(jj - 1 + (kk - 1) * xin_dim2) * xin_dim1] + xin[ii - 
			1 + (jj + 1 + (kk - 1) * xin_dim2) * xin_dim1] + xin[
			ii + 1 + (jj + 1 + (kk - 1) * xin_dim2) * xin_dim1] + 
			xin[ii - 1 + (jj - 1 + (kk + 1) * xin_dim2) * 
			xin_dim1] + xin[ii + 1 + (jj - 1 + (kk + 1) * 
			xin_dim2) * xin_dim1] + xin[ii - 1 + (jj + 1 + (kk + 
			1) * xin_dim2) * xin_dim1] + xin[ii + 1 + (jj + 1 + (
			kk + 1) * xin_dim2) * xin_dim1]);
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** verify correctness of the output boundary points *** */
    fbound00_(nxc, nyc, nzc, &xout[xout_offset]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* restrcz_ */

