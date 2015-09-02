/* ./src_f77/buildBd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__3 = 3;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    buildBd.f */
/* * @author  Michael Holst */
/* * @brief   Routines to build/factor/store a banded coarse grid matrix. */
/* * @version $Id: buildBd.c,v 1.3 2010/08/12 05:45:19 fetk Exp $ */
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
/* Subroutine */ int buildband_(integer *key, integer *nx, integer *ny, 
	integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, integer *
	ipcb, doublereal *rpcb, doublereal *acb)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer m, n, lda;
    extern /* Subroutine */ int buildband1_7__(integer *, integer *, integer *
	    , integer *, doublereal *, doublereal *, doublereal *, doublereal 
	    *, doublereal *, integer *, doublereal *, doublereal *, integer *,
	     integer *, integer *), buildband1_27__(integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, integer *, integer *, integer *);
    static integer info;
    extern /* Subroutine */ int dpbfa_(doublereal *, integer *, integer *, 
	    integer *, integer *);
    static integer numdia;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, 0, 0 };
    static cilist io___6 = { 0, 6, 0, 0, 0 };
    static cilist io___7 = { 0, 6, 0, 0, 0 };
    static cilist io___9 = { 0, 6, 0, 0, 0 };
    static cilist io___10 = { 0, 6, 0, 0, 0 };
    static cilist io___11 = { 0, 6, 0, 0, 0 };
    static cilist io___12 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    build and factor a banded matrix given a matrix in diagonal form. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* ZZZZ double precision rcond */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in one step *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --ipcb;
    --rpcb;
    --acb;

    /* Function Body */
    numdia = ipc[11];
    if (numdia == 7) {
	s_wsle(&io___2);
	do_lio(&c__9, &c__1, "% BUILDBAND: building 7-pt banded coarse opera"
		"tor...", (ftnlen)52);
	e_wsle();
	n = (*nx - 2) * (*ny - 2) * (*nz - 2);
	m = (*nx - 2) * (*ny - 2);
	lda = m + 1;
	buildband1_7__(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &ac[(
		ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) 
		+ 1], &ipcb[1], &rpcb[1], &acb[1], &n, &m, &lda);
    } else if (numdia == 27) {
	s_wsle(&io___6);
	do_lio(&c__9, &c__1, "% BUILDBAND: building 27-pt banded coarse oper"
		"ator...", (ftnlen)53);
	e_wsle();
	n = (*nx - 2) * (*ny - 2) * (*nz - 2);
	m = (*nx - 2) * (*ny - 2) + (*nx - 2) + 1;
	lda = m + 1;
	buildband1_27__(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &ac[(
		ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) 
		+ 1], &ac[ac_dim1 * 5 + 1], &ac[ac_dim1 * 6 + 1], &ac[ac_dim1 
		* 7 + 1], &ac[(ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1], &ac[
		ac_dim1 * 10 + 1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 + 
		1], &ac[ac_dim1 * 13 + 1], &ac[ac_dim1 * 14 + 1], &ipcb[1], &
		rpcb[1], &acb[1], &n, &m, &lda);
    } else {
	s_wsle(&io___7);
	do_lio(&c__9, &c__1, "% BUILDBAND: invalid stencil type given...", (
		ftnlen)42);
	e_wsle();
    }
/* * */
/* *    *** print matrices *** */
/* ZZZZ call prtmatd(nx,ny,nz,ipc,rpc,ac) */
/* ZZZZ call prtmatb(acB,n,m,lda) */
/* * */
/* *    *** factor the system *** */
    *key = 0;
    info = 0;
    s_wsle(&io___9);
    do_lio(&c__9, &c__1, "% BUILDBAND: dpbfa factoring banded coarse system."
	    "..", (ftnlen)52);
    e_wsle();
    dpbfa_(&acb[1], &lda, &n, &m, &info);
/* ZZZZ call dpbco(acB,lda,n,m,rcond,w1,info) */
    ipcb[4] = 1;
    if (info != 0) {
/* ZZZZ    print*,'% BUILDBAND: dpbco rcond:   ',rcond */
	s_wsle(&io___10);
	do_lio(&c__9, &c__1, "% BUILDBAND: dpbfa problem: ", (ftnlen)28);
	do_lio(&c__3, &c__1, (char *)&info, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___11);
	do_lio(&c__9, &c__1, "% BUILDBAND: leading principle minor not PD...",
		 (ftnlen)46);
	e_wsle();
	*key = 1;
    }
    s_wsle(&io___12);
    do_lio(&c__9, &c__1, "% BUILDBAND: dpbfa banded factorization complete.", 
	    (ftnlen)49);
    e_wsle();
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildband_ */

/* Subroutine */ int buildband1_7__(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, 
	doublereal *on, doublereal *uc, integer *ipcb, doublereal *rpcb, 
	doublereal *acb, integer *n, integer *m, integer *lda)
{
    /* System generated locals */
    integer acb_dim1, acb_offset, oc_dim1, oc_dim2, oc_offset, oe_dim1, 
	    oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1, uc_dim2,
	     uc_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, ii, jj, kk;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    build the operator in banded form given the 7-diagonal form. */
/* * */
/* * notes: */
/* * */
/* *    pseudo-code from the banded linpack routines: */
/* * */
/* *    jj = 0 */
/* *    do 10 k = 2, nz-1 */
/* *       do 10 j = 2, ny-1 */
/* *          do 10 i = 2, nx-1 */
/* *             jj = jj + 1 */
/* *             i1 = max0(1, jj-m) */
/* *             do 20 ii = i1, jj */
/* *                kk = ii - jj + m + 1 */
/* *                acB(kk,jj) = 0.0e0 */
/* *                if ((jj-ii).eq.0) acB(kk,jj)=oC(i,j,k) */
/* *                if ((jj-ii).eq.1) acB(kk,jj)=-oE(i-1,j,k) */
/* *                if ((jj-ii).eq.(nx-2)) acB(kk,jj)=-oN(i,j-1,k) */
/* *                if ((jj-ii).eq.(nx-2)*(ny-2)) acB(kk,jj)=-uC(i,j,k-1) */
/* * 20          continue */
/* * 10   continue */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** doit *** */
    /* Parameter adjustments */
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
    oc_dim1 = *nx;
    oc_dim2 = *ny;
    oc_offset = 1 + oc_dim1 * (1 + oc_dim2);
    oc -= oc_offset;
    --ipc;
    --rpc;
    --ipcb;
    --rpcb;
    acb_dim1 = *lda;
    acb_offset = 1 + acb_dim1;
    acb -= acb_offset;

    /* Function Body */
    ipcb[1] = *n;
    ipcb[2] = *m;
    ipcb[3] = *lda;
    ipcb[4] = 0;
    jj = 0;
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		++jj;
/* * */
/* *             *** diagonal term *** */
		ii = jj;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = oc[i__ + (j + k * oc_dim2) * 
			oc_dim1];
/* * */
/* *             *** east neighbor *** */
		ii = jj - 1;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -oe[i__ - 1 + (j + k * oe_dim2) * 
			oe_dim1];
/* * */
/* *             *** north neighbor *** */
		ii = jj - (*nx - 2);
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -on[i__ + (j - 1 + k * on_dim2) * 
			on_dim1];
/* * */
/* *             *** up neighbor *** */
		ii = jj - (*nx - 2) * (*ny - 2);
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -uc[i__ + (j + (k - 1) * uc_dim2) * 
			uc_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildband1_7__ */

/* Subroutine */ int buildband1_27__(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, 
	doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, 
	doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, 
	doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, 
	integer *ipcb, doublereal *rpcb, doublereal *acb, integer *n, integer 
	*m, integer *lda)
{
    /* System generated locals */
    integer acb_dim1, acb_offset, oc_dim1, oc_dim2, oc_offset, oe_dim1, 
	    oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1, uc_dim2,
	     uc_offset, one_dim1, one_dim2, one_offset, onw_dim1, onw_dim2, 
	    onw_offset, ue_dim1, ue_dim2, ue_offset, uw_dim1, uw_dim2, 
	    uw_offset, un_dim1, un_dim2, un_offset, us_dim1, us_dim2, 
	    us_offset, une_dim1, une_dim2, une_offset, unw_dim1, unw_dim2, 
	    unw_offset, use_dim1, use_dim2, use_offset, usw_dim1, usw_dim2, 
	    usw_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, ii, jj, kk;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    build the operator in banded form given the 27-diagonal form. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** doit *** */
    /* Parameter adjustments */
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
    oc_dim1 = *nx;
    oc_dim2 = *ny;
    oc_offset = 1 + oc_dim1 * (1 + oc_dim2);
    oc -= oc_offset;
    --ipc;
    --rpc;
    --ipcb;
    --rpcb;
    acb_dim1 = *lda;
    acb_offset = 1 + acb_dim1;
    acb -= acb_offset;

    /* Function Body */
    ipcb[1] = *n;
    ipcb[2] = *m;
    ipcb[3] = *lda;
    ipcb[4] = 0;
    jj = 0;
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		++jj;
/* * */
/* *             *** diagonal term *** */
		ii = jj;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = oc[i__ + (j + k * oc_dim2) * 
			oc_dim1];
/* * */
/* *             *** east neighbor *** */
		ii = jj - 1;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -oe[i__ - 1 + (j + k * oe_dim2) * 
			oe_dim1];
/* * */
/* *             *** north neighbor *** */
		ii = jj - (*nx - 2);
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -on[i__ + (j - 1 + k * on_dim2) * 
			on_dim1];
/* * */
/* *             *** north-east neighbor *** */
		ii = jj - (*nx - 2) + 1;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -one[i__ + (j - 1 + k * one_dim2) * 
			one_dim1];
/* * */
/* *             *** north-west neighbor *** */
		ii = jj - (*nx - 2) - 1;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -onw[i__ + (j - 1 + k * onw_dim2) * 
			onw_dim1];
/* * */
/* *             *** up neighbor *** */
		ii = jj - (*nx - 2) * (*ny - 2);
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -uc[i__ + (j + (k - 1) * uc_dim2) * 
			uc_dim1];
/* * */
/* *             *** up-east neighbor *** */
		ii = jj - (*nx - 2) * (*ny - 2) + 1;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -ue[i__ + (j + (k - 1) * ue_dim2) * 
			ue_dim1];
/* * */
/* *             *** up-west neighbor *** */
		ii = jj - (*nx - 2) * (*ny - 2) - 1;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -uw[i__ + (j + (k - 1) * uw_dim2) * 
			uw_dim1];
/* * */
/* *             *** up-north neighbor *** */
		ii = jj - (*nx - 2) * (*ny - 2) + (*nx - 2);
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -un[i__ + (j + (k - 1) * un_dim2) * 
			un_dim1];
/* * */
/* *             *** up-south neighbor *** */
		ii = jj - (*nx - 2) * (*ny - 2) - (*nx - 2);
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -us[i__ + (j + (k - 1) * us_dim2) * 
			us_dim1];
/* * */
/* *             *** up-north-east neighbor *** */
		ii = jj - (*nx - 2) * (*ny - 2) + (*nx - 2) + 1;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -une[i__ + (j + (k - 1) * une_dim2) 
			* une_dim1];
/* * */
/* *             *** up-north-west neighbor *** */
		ii = jj - (*nx - 2) * (*ny - 2) + (*nx - 2) - 1;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -unw[i__ + (j + (k - 1) * unw_dim2) 
			* unw_dim1];
/* * */
/* *             *** up-south-east neighbor *** */
		ii = jj - (*nx - 2) * (*ny - 2) - (*nx - 2) + 1;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -use[i__ + (j + (k - 1) * use_dim2) 
			* use_dim1];
/* * */
/* *             *** up-south-west neighbor *** */
		ii = jj - (*nx - 2) * (*ny - 2) - (*nx - 2) - 1;
		kk = ii - jj + *m + 1;
		acb[kk + jj * acb_dim1] = -usw[i__ + (j + (k - 1) * usw_dim2) 
			* usw_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildband1_27__ */

