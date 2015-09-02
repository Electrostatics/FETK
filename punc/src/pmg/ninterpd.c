/* ./src_f77/ninterpd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__3 = 3;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    ninterpd.f */
/* * @author  Michael Holst */
/* * @brief   Nonlinear version of operator-based interpolation. */
/* * @version $Id: ninterpd.c,v 1.3 2010/08/12 05:45:26 fetk Exp $ */
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
/* Subroutine */ int ninterp_(integer *nxc, integer *nyc, integer *nzc, 
	integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal 
	*xout, doublereal *pc, integer *ipc, doublereal *rpc, doublereal *ac, 
	doublereal *cc, doublereal *fc)
{
    /* System generated locals */
    integer pc_dim1, pc_offset, ac_dim1, ac_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int ninterp7_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), ninterp27_(integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static integer numdia;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    driver for nonlinear operator-based interpolation. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** doit *** */
    /* Parameter adjustments */
    pc_dim1 = *nxc * *nyc * *nzc;
    pc_offset = 1 + pc_dim1;
    pc -= pc_offset;
    ac_dim1 = *nxf * *nyf * *nzf;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --xin;
    --xout;
    --ipc;
    --rpc;
    --cc;
    --fc;

    /* Function Body */
    numdia = ipc[11];
    if (numdia == 7) {
	ninterp7_(nxc, nyc, nzc, nxf, nyf, nzf, &xin[1], &xout[1], &pc[
		pc_dim1 + 1], &pc[(pc_dim1 << 1) + 1], &pc[pc_dim1 * 3 + 1], &
		pc[(pc_dim1 << 2) + 1], &pc[pc_dim1 * 5 + 1], &pc[pc_dim1 * 6 
		+ 1], &pc[pc_dim1 * 7 + 1], &pc[(pc_dim1 << 3) + 1], &pc[
		pc_dim1 * 9 + 1], &pc[pc_dim1 * 10 + 1], &pc[pc_dim1 * 11 + 1]
		, &pc[pc_dim1 * 12 + 1], &pc[pc_dim1 * 13 + 1], &pc[pc_dim1 * 
		14 + 1], &pc[pc_dim1 * 15 + 1], &pc[(pc_dim1 << 4) + 1], &pc[
		pc_dim1 * 17 + 1], &pc[pc_dim1 * 18 + 1], &pc[pc_dim1 * 19 + 
		1], &pc[pc_dim1 * 20 + 1], &pc[pc_dim1 * 21 + 1], &pc[pc_dim1 
		* 22 + 1], &pc[pc_dim1 * 23 + 1], &pc[pc_dim1 * 24 + 1], &pc[
		pc_dim1 * 25 + 1], &pc[pc_dim1 * 26 + 1], &pc[pc_dim1 * 27 + 
		1], &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &ac[(ac_dim1 << 1) + 
		1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) + 1], &cc[1], &
		fc[1]);
    } else if (numdia == 27) {
	ninterp27_(nxc, nyc, nzc, nxf, nyf, nzf, &xin[1], &xout[1], &pc[
		pc_dim1 + 1], &pc[(pc_dim1 << 1) + 1], &pc[pc_dim1 * 3 + 1], &
		pc[(pc_dim1 << 2) + 1], &pc[pc_dim1 * 5 + 1], &pc[pc_dim1 * 6 
		+ 1], &pc[pc_dim1 * 7 + 1], &pc[(pc_dim1 << 3) + 1], &pc[
		pc_dim1 * 9 + 1], &pc[pc_dim1 * 10 + 1], &pc[pc_dim1 * 11 + 1]
		, &pc[pc_dim1 * 12 + 1], &pc[pc_dim1 * 13 + 1], &pc[pc_dim1 * 
		14 + 1], &pc[pc_dim1 * 15 + 1], &pc[(pc_dim1 << 4) + 1], &pc[
		pc_dim1 * 17 + 1], &pc[pc_dim1 * 18 + 1], &pc[pc_dim1 * 19 + 
		1], &pc[pc_dim1 * 20 + 1], &pc[pc_dim1 * 21 + 1], &pc[pc_dim1 
		* 22 + 1], &pc[pc_dim1 * 23 + 1], &pc[pc_dim1 * 24 + 1], &pc[
		pc_dim1 * 25 + 1], &pc[pc_dim1 * 26 + 1], &pc[pc_dim1 * 27 + 
		1], &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &ac[(ac_dim1 << 1) + 
		1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) + 1], &ac[
		ac_dim1 * 5 + 1], &ac[ac_dim1 * 6 + 1], &ac[ac_dim1 * 7 + 1], 
		&ac[(ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1], &ac[ac_dim1 * 
		10 + 1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 + 1], &ac[
		ac_dim1 * 13 + 1], &ac[ac_dim1 * 14 + 1], &cc[1], &fc[1]);
    } else {
	s_wsle(&io___2);
	do_lio(&c__9, &c__1, "% NINTERP: invalid stencil type given...", (
		ftnlen)40);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* ninterp_ */

/* Subroutine */ int ninterp7_(integer *nxc, integer *nyc, integer *nzc, 
	integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal 
	*xout, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *
	ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *
	opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *
	ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *
	upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal 
	*dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *
	dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw, integer *
	ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, 
	doublereal *uc, doublereal *cc, doublereal *fc)
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
	    dpse_offset, dpsw_dim1, dpsw_dim2, dpsw_offset, cc_dim1, cc_dim2, 
	    cc_offset, fc_dim1, fc_dim2, fc_offset, oc_dim1, oc_dim2, 
	    oc_offset, oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, 
	    on_offset, uc_dim1, uc_dim2, uc_offset, i__1, i__2, i__3, i__4, 
	    i__5, i__6, i__7, i__8, i__9, i__10, i__11;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j, k, ifail_tol__, i1, j1, k1;
    static doublereal aa, bb, dd, ff;
    static integer ii, jj, kk;
    static doublereal uu;
    static integer key;
    static doublereal znn, dznn;
    static integer ipkey;
    static doublereal zntol;
    extern doublereal c_scal__(doublereal *, doublereal *, integer *);
    static doublereal change;
    static integer nitmax, niters;
    extern doublereal dc_scal__(doublereal *, doublereal *, integer *);
    extern /* Subroutine */ int fbound00_(integer *, integer *, integer *, 
	    doublereal *);
    static doublereal zndenom, znerror;

    /* Fortran I/O blocks */
    static cilist io___28 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    7-diagonal nonlinear operator-based interpolation. */
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
/* *    *** nonlinear iteration tolerance and itmax *** */
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
    fc_dim1 = *nxf;
    fc_dim2 = *nyf;
    fc_offset = 1 + fc_dim1 * (1 + fc_dim2);
    fc -= fc_offset;
    cc_dim1 = *nxf;
    cc_dim2 = *nyf;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
    cc -= cc_offset;
    uc_dim1 = *nxf;
    uc_dim2 = *nyf;
    uc_offset = 1 + uc_dim1 * (1 + uc_dim2);
    uc -= uc_offset;
    on_dim1 = *nxf;
    on_dim2 = *nyf;
    on_offset = 1 + on_dim1 * (1 + on_dim2);
    on -= on_offset;
    oe_dim1 = *nxf;
    oe_dim2 = *nyf;
    oe_offset = 1 + oe_dim1 * (1 + oe_dim2);
    oe -= oe_offset;
    oc_dim1 = *nxf;
    oc_dim2 = *nyf;
    oc_offset = 1 + oc_dim1 * (1 + oc_dim2);
    oc -= oc_offset;
    xout_dim1 = *nxf;
    xout_dim2 = *nyf;
    xout_offset = 1 + xout_dim1 * (1 + xout_dim2);
    xout -= xout_offset;
    --ipc;
    --rpc;

    /* Function Body */
    nitmax = 10;
    zntol = 1e-5f;
    ifail_tol__ = 0;
    ipkey = ipc[10];
    key = 0;
/* * */
/* *    *** verify correctness of the input boundary points *** */
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
/* * ********************************************************************* */
/* *             *** fine grid pts common only to y-z planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on x-row) *** */
		xout[i__ + 1 + (j + k * xout_dim2) * xout_dim1] = ope[ii + (
			jj + kk * ope_dim2) * ope_dim1] * xin[ii + (jj + kk * 
			xin_dim2) * xin_dim1] + opw[ii + 1 + (jj + kk * 
			opw_dim2) * opw_dim1] * xin[ii + 1 + (jj + kk * 
			xin_dim2) * xin_dim1];
		i1 = i__ + 1;
		j1 = j;
		k1 = k;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = k1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = k1 - 1;
/* Computing MAX */
		i__8 = 1, i__9 = j1 - 1;
/* Computing MIN */
		i__10 = 1, i__11 = j1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - uc[i1 + (j1 + 
			k1 * uc_dim2) * uc_dim1] - uc[i1 + (j1 + max(i__4,
			i__5) * uc_dim2) * uc_dim1] * (doublereal) min(i__6,
			i__7) - on[i1 + (j1 + k1 * on_dim2) * on_dim1] - on[
			i1 + (max(i__8,i__9) + k1 * on_dim2) * on_dim1] * (
			doublereal) min(i__10,i__11);
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L23;
		}
		if (niters > nitmax) {
		    goto L22;
		}
L21:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L23;
		}
		if (niters > nitmax) {
		    goto L22;
		}
/* * */
/* *             *** loop *** */
		goto L21;
/* * */
/* *             *** tolerance not reached *** */
L22:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L23:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* * ********************************************************************* */
/* *             *** fine grid pts common only to x-z planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on a y-row) *** */
		xout[i__ + (j + 1 + k * xout_dim2) * xout_dim1] = opn[ii + (
			jj + kk * opn_dim2) * opn_dim1] * xin[ii + (jj + kk * 
			xin_dim2) * xin_dim1] + ops[ii + (jj + 1 + kk * 
			ops_dim2) * ops_dim1] * xin[ii + (jj + 1 + kk * 
			xin_dim2) * xin_dim1];
		i1 = i__;
		j1 = j + 1;
		k1 = k;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = i1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = i1 - 1;
/* Computing MAX */
		i__8 = 1, i__9 = k1 - 1;
/* Computing MIN */
		i__10 = 1, i__11 = k1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - oe[i1 + (j1 + 
			k1 * oe_dim2) * oe_dim1] - oe[max(i__4,i__5) + (j1 + 
			k1 * oe_dim2) * oe_dim1] * (doublereal) min(i__6,i__7)
			 - uc[i1 + (j1 + k1 * uc_dim2) * uc_dim1] - uc[i1 + (
			j1 + max(i__8,i__9) * uc_dim2) * uc_dim1] * (
			doublereal) min(i__10,i__11);
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L33;
		}
		if (niters > nitmax) {
		    goto L32;
		}
L31:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L33;
		}
		if (niters > nitmax) {
		    goto L32;
		}
/* * */
/* *             *** loop *** */
		goto L31;
/* * */
/* *             *** tolerance not reached *** */
L32:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L33:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* * ********************************************************************* */
/* *             *** fine grid pts common only to x-y planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on a z-row) *** */
		xout[i__ + (j + (k + 1) * xout_dim2) * xout_dim1] = upc[ii + (
			jj + kk * upc_dim2) * upc_dim1] * xin[ii + (jj + kk * 
			xin_dim2) * xin_dim1] + dpc[ii + (jj + (kk + 1) * 
			dpc_dim2) * dpc_dim1] * xin[ii + (jj + (kk + 1) * 
			xin_dim2) * xin_dim1];
		i1 = i__;
		j1 = j;
		k1 = k + 1;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = i1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = i1 - 1;
/* Computing MAX */
		i__8 = 1, i__9 = j1 - 1;
/* Computing MIN */
		i__10 = 1, i__11 = j1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - oe[i1 + (j1 + 
			k1 * oe_dim2) * oe_dim1] - oe[max(i__4,i__5) + (j1 + 
			k1 * oe_dim2) * oe_dim1] * (doublereal) min(i__6,i__7)
			 - on[i1 + (j1 + k1 * on_dim2) * on_dim1] - on[i1 + (
			max(i__8,i__9) + k1 * on_dim2) * on_dim1] * (
			doublereal) min(i__10,i__11);
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L43;
		}
		if (niters > nitmax) {
		    goto L42;
		}
L41:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L43;
		}
		if (niters > nitmax) {
		    goto L42;
		}
/* * */
/* *             *** loop *** */
		goto L41;
/* * */
/* *             *** tolerance not reached *** */
L42:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L43:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* * ********************************************************************* */
/* * type 3 -- fine grid points common to a coarse grid line */
/* * ********************************************************************* */
/* * */
/* * ********************************************************************* */
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
		i1 = i__ + 1;
		j1 = j + 1;
		k1 = k;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = k1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = k1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - uc[i1 + (j1 + 
			k1 * uc_dim2) * uc_dim1] - uc[i1 + (j1 + max(i__4,
			i__5) * uc_dim2) * uc_dim1] * (doublereal) min(i__6,
			i__7);
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L53;
		}
		if (niters > nitmax) {
		    goto L52;
		}
L51:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L53;
		}
		if (niters > nitmax) {
		    goto L52;
		}
/* * */
/* *             *** loop *** */
		goto L51;
/* * */
/* *             *** tolerance not reached *** */
L52:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L53:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* * ********************************************************************* */
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
		i1 = i__ + 1;
		j1 = j;
		k1 = k + 1;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = j1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = j1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - on[i1 + (j1 + 
			k1 * on_dim2) * on_dim1] - on[i1 + (max(i__4,i__5) + 
			k1 * on_dim2) * on_dim1] * (doublereal) min(i__6,i__7)
			;
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L63;
		}
		if (niters > nitmax) {
		    goto L62;
		}
L61:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L63;
		}
		if (niters > nitmax) {
		    goto L62;
		}
/* * */
/* *             *** loop *** */
		goto L61;
/* * */
/* *             *** tolerance not reached *** */
L62:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L63:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* * ********************************************************************* */
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
		i1 = i__;
		j1 = j + 1;
		k1 = k + 1;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = i1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = i1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - oe[i1 + (j1 + 
			k1 * oe_dim2) * oe_dim1] - oe[max(i__4,i__5) + (j1 + 
			k1 * oe_dim2) * oe_dim1] * (doublereal) min(i__6,i__7)
			;
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L73;
		}
		if (niters > nitmax) {
		    goto L72;
		}
L71:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L73;
		}
		if (niters > nitmax) {
		    goto L72;
		}
/* * */
/* *             *** loop *** */
		goto L71;
/* * */
/* *             *** tolerance not reached *** */
L72:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L73:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
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
		i1 = i__ + 1;
		j1 = j + 1;
		k1 = k + 1;
/* * */
/* *             *** setup the 1d equation *** */
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1];
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L83;
		}
		if (niters > nitmax) {
		    goto L82;
		}
L81:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L83;
		}
		if (niters > nitmax) {
		    goto L82;
		}
/* * */
/* *             *** loop *** */
		goto L81;
/* * */
/* *             *** tolerance not reached *** */
L82:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L83:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* *             *** main loop *** */
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
/* *    *** messages *** */
    if (ifail_tol__ > 0) {
	s_wsle(&io___28);
	do_lio(&c__9, &c__1, "% NINTERP7: 1d newton tolerance failures: ", (
		ftnlen)42);
	do_lio(&c__3, &c__1, (char *)&ifail_tol__, (ftnlen)sizeof(integer));
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* ninterp7_ */

/* Subroutine */ int ninterp27_(integer *nxc, integer *nyc, integer *nzc, 
	integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal 
	*xout, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *
	ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *
	opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *
	ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *
	upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal 
	*dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *
	dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw, integer *
	ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, 
	doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, 
	doublereal *uw, doublereal *un, doublereal *us, doublereal *une, 
	doublereal *unw, doublereal *use, doublereal *usw, doublereal *cc, 
	doublereal *fc)
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
	    dpse_offset, dpsw_dim1, dpsw_dim2, dpsw_offset, cc_dim1, cc_dim2, 
	    cc_offset, fc_dim1, fc_dim2, fc_offset, oc_dim1, oc_dim2, 
	    oc_offset, oe_dim1, oe_dim2, oe_offset, on_dim1, on_dim2, 
	    on_offset, uc_dim1, uc_dim2, uc_offset, one_dim1, one_dim2, 
	    one_offset, onw_dim1, onw_dim2, onw_offset, ue_dim1, ue_dim2, 
	    ue_offset, uw_dim1, uw_dim2, uw_offset, un_dim1, un_dim2, 
	    un_offset, us_dim1, us_dim2, us_offset, une_dim1, une_dim2, 
	    une_offset, unw_dim1, unw_dim2, unw_offset, use_dim1, use_dim2, 
	    use_offset, usw_dim1, usw_dim2, usw_offset, i__1, i__2, i__3, 
	    i__4, i__5, i__6, i__7, i__8, i__9, i__10, i__11, i__12, i__13, 
	    i__14, i__15, i__16, i__17, i__18, i__19;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j, k, ifail_tol__, i1, j1, k1;
    static doublereal aa, bb, dd, ff;
    static integer ii, jj, kk;
    static doublereal uu;
    static integer key;
    static doublereal znn, dznn;
    static integer ipkey;
    static doublereal zntol;
    extern doublereal c_scal__(doublereal *, doublereal *, integer *);
    static doublereal change;
    static integer nitmax, niters;
    extern doublereal dc_scal__(doublereal *, doublereal *, integer *);
    extern /* Subroutine */ int fbound00_(integer *, integer *, integer *, 
	    doublereal *);
    static doublereal zndenom, znerror;

    /* Fortran I/O blocks */
    static cilist io___54 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    27-diagonal nonlinear operator-based interpolation. */
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
/* *    *** nonlinear iteration tolerance and itmax *** */
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
    fc_dim1 = *nxf;
    fc_dim2 = *nyf;
    fc_offset = 1 + fc_dim1 * (1 + fc_dim2);
    fc -= fc_offset;
    cc_dim1 = *nxf;
    cc_dim2 = *nyf;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
    cc -= cc_offset;
    usw_dim1 = *nxf;
    usw_dim2 = *nyf;
    usw_offset = 1 + usw_dim1 * (1 + usw_dim2);
    usw -= usw_offset;
    use_dim1 = *nxf;
    use_dim2 = *nyf;
    use_offset = 1 + use_dim1 * (1 + use_dim2);
    use -= use_offset;
    unw_dim1 = *nxf;
    unw_dim2 = *nyf;
    unw_offset = 1 + unw_dim1 * (1 + unw_dim2);
    unw -= unw_offset;
    une_dim1 = *nxf;
    une_dim2 = *nyf;
    une_offset = 1 + une_dim1 * (1 + une_dim2);
    une -= une_offset;
    us_dim1 = *nxf;
    us_dim2 = *nyf;
    us_offset = 1 + us_dim1 * (1 + us_dim2);
    us -= us_offset;
    un_dim1 = *nxf;
    un_dim2 = *nyf;
    un_offset = 1 + un_dim1 * (1 + un_dim2);
    un -= un_offset;
    uw_dim1 = *nxf;
    uw_dim2 = *nyf;
    uw_offset = 1 + uw_dim1 * (1 + uw_dim2);
    uw -= uw_offset;
    ue_dim1 = *nxf;
    ue_dim2 = *nyf;
    ue_offset = 1 + ue_dim1 * (1 + ue_dim2);
    ue -= ue_offset;
    onw_dim1 = *nxf;
    onw_dim2 = *nyf;
    onw_offset = 1 + onw_dim1 * (1 + onw_dim2);
    onw -= onw_offset;
    one_dim1 = *nxf;
    one_dim2 = *nyf;
    one_offset = 1 + one_dim1 * (1 + one_dim2);
    one -= one_offset;
    uc_dim1 = *nxf;
    uc_dim2 = *nyf;
    uc_offset = 1 + uc_dim1 * (1 + uc_dim2);
    uc -= uc_offset;
    on_dim1 = *nxf;
    on_dim2 = *nyf;
    on_offset = 1 + on_dim1 * (1 + on_dim2);
    on -= on_offset;
    oe_dim1 = *nxf;
    oe_dim2 = *nyf;
    oe_offset = 1 + oe_dim1 * (1 + oe_dim2);
    oe -= oe_offset;
    oc_dim1 = *nxf;
    oc_dim2 = *nyf;
    oc_offset = 1 + oc_dim1 * (1 + oc_dim2);
    oc -= oc_offset;
    xout_dim1 = *nxf;
    xout_dim2 = *nyf;
    xout_offset = 1 + xout_dim1 * (1 + xout_dim2);
    xout -= xout_offset;
    --ipc;
    --rpc;

    /* Function Body */
    nitmax = 10;
    zntol = 1e-5f;
    ifail_tol__ = 0;
    ipkey = ipc[10];
    key = 0;
/* * */
/* *    *** verify correctness of the input boundary points *** */
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
/* * ********************************************************************* */
/* *             *** fine grid pts common only to y-z planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on x-row) *** */
		xout[i__ + 1 + (j + k * xout_dim2) * xout_dim1] = ope[ii + (
			jj + kk * ope_dim2) * ope_dim1] * xin[ii + (jj + kk * 
			xin_dim2) * xin_dim1] + opw[ii + 1 + (jj + kk * 
			opw_dim2) * opw_dim1] * xin[ii + 1 + (jj + kk * 
			xin_dim2) * xin_dim1];
		i1 = i__ + 1;
		j1 = j;
		k1 = k;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = k1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = k1 - 1;
/* Computing MAX */
		i__8 = 1, i__9 = j1 - 1;
/* Computing MIN */
		i__10 = 1, i__11 = j1 - 1;
/* Computing MAX */
		i__12 = 1, i__13 = k1 - 1;
/* Computing MIN */
		i__14 = 1, i__15 = k1 - 1;
/* Computing MAX */
		i__16 = 1, i__17 = k1 - 1;
/* Computing MIN */
		i__18 = 1, i__19 = k1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - uc[i1 + (j1 + 
			k1 * uc_dim2) * uc_dim1] - uc[i1 + (j1 + max(i__4,
			i__5) * uc_dim2) * uc_dim1] * (doublereal) min(i__6,
			i__7) - on[i1 + (j1 + k1 * on_dim2) * on_dim1] - on[
			i1 + (max(i__8,i__9) + k1 * on_dim2) * on_dim1] * (
			doublereal) min(i__10,i__11) - un[i1 + (j1 + k1 * 
			un_dim2) * un_dim1] - us[i1 + (j1 + k1 * us_dim2) * 
			us_dim1] - un[i1 + (j1 + max(i__12,i__13) * un_dim2) *
			 un_dim1] * (doublereal) min(i__14,i__15) - us[i1 + (
			j1 + max(i__16,i__17) * us_dim2) * us_dim1] * (
			doublereal) min(i__18,i__19);
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L23;
		}
		if (niters > nitmax) {
		    goto L22;
		}
L21:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L23;
		}
		if (niters > nitmax) {
		    goto L22;
		}
/* * */
/* *             *** loop *** */
		goto L21;
/* * */
/* *             *** tolerance not reached *** */
L22:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L23:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* * ********************************************************************* */
/* *             *** fine grid pts common only to x-z planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on a y-row) *** */
		xout[i__ + (j + 1 + k * xout_dim2) * xout_dim1] = opn[ii + (
			jj + kk * opn_dim2) * opn_dim1] * xin[ii + (jj + kk * 
			xin_dim2) * xin_dim1] + ops[ii + (jj + 1 + kk * 
			ops_dim2) * ops_dim1] * xin[ii + (jj + 1 + kk * 
			xin_dim2) * xin_dim1];
		i1 = i__;
		j1 = j + 1;
		k1 = k;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = i1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = i1 - 1;
/* Computing MAX */
		i__8 = 1, i__9 = k1 - 1;
/* Computing MIN */
		i__10 = 1, i__11 = k1 - 1;
/* Computing MAX */
		i__12 = 1, i__13 = k1 - 1;
/* Computing MIN */
		i__14 = 1, i__15 = k1 - 1;
/* Computing MAX */
		i__16 = 1, i__17 = k1 - 1;
/* Computing MIN */
		i__18 = 1, i__19 = k1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - oe[i1 + (j1 + 
			k1 * oe_dim2) * oe_dim1] - oe[max(i__4,i__5) + (j1 + 
			k1 * oe_dim2) * oe_dim1] * (doublereal) min(i__6,i__7)
			 - uc[i1 + (j1 + k1 * uc_dim2) * uc_dim1] - uc[i1 + (
			j1 + max(i__8,i__9) * uc_dim2) * uc_dim1] * (
			doublereal) min(i__10,i__11) - ue[i1 + (j1 + k1 * 
			ue_dim2) * ue_dim1] - uw[i1 + (j1 + k1 * uw_dim2) * 
			uw_dim1] - ue[i1 + (j1 + max(i__12,i__13) * ue_dim2) *
			 ue_dim1] * (doublereal) min(i__14,i__15) - uw[i1 + (
			j1 + max(i__16,i__17) * uw_dim2) * uw_dim1] * (
			doublereal) min(i__18,i__19);
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L33;
		}
		if (niters > nitmax) {
		    goto L32;
		}
L31:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L33;
		}
		if (niters > nitmax) {
		    goto L32;
		}
/* * */
/* *             *** loop *** */
		goto L31;
/* * */
/* *             *** tolerance not reached *** */
L32:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L33:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* * ********************************************************************* */
/* *             *** fine grid pts common only to x-y planes on coarse grid *** */
/* *             *** (intermediate pts between 2 grid points on a z-row) *** */
		xout[i__ + (j + (k + 1) * xout_dim2) * xout_dim1] = upc[ii + (
			jj + kk * upc_dim2) * upc_dim1] * xin[ii + (jj + kk * 
			xin_dim2) * xin_dim1] + dpc[ii + (jj + (kk + 1) * 
			dpc_dim2) * dpc_dim1] * xin[ii + (jj + (kk + 1) * 
			xin_dim2) * xin_dim1];
		i1 = i__;
		j1 = j;
		k1 = k + 1;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = i1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = i1 - 1;
/* Computing MAX */
		i__8 = 1, i__9 = j1 - 1;
/* Computing MIN */
		i__10 = 1, i__11 = j1 - 1;
/* Computing MIN */
		i__12 = 1, i__13 = i1 - 1;
/* Computing MIN */
		i__14 = 1, i__15 = j1 - 1;
/* Computing MIN */
		i__16 = 1, i__17 = j1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - oe[i1 + (j1 + 
			k1 * oe_dim2) * oe_dim1] - oe[max(i__4,i__5) + (j1 + 
			k1 * oe_dim2) * oe_dim1] * (doublereal) min(i__6,i__7)
			 - on[i1 + (j1 + k1 * on_dim2) * on_dim1] - on[i1 + (
			max(i__8,i__9) + k1 * on_dim2) * on_dim1] * (
			doublereal) min(i__10,i__11) - one[i1 + (j1 + k1 * 
			one_dim2) * one_dim1] - onw[i1 + (j1 + k1 * onw_dim2) 
			* onw_dim1] - one[i1 - 1 + (j1 - 1 + k1 * one_dim2) * 
			one_dim1] * (doublereal) min(i__12,i__13) * (
			doublereal) min(i__14,i__15) - onw[i1 + 1 + (j1 - 1 + 
			k1 * onw_dim2) * onw_dim1] * (doublereal) min(i__16,
			i__17);
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L43;
		}
		if (niters > nitmax) {
		    goto L42;
		}
L41:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L43;
		}
		if (niters > nitmax) {
		    goto L42;
		}
/* * */
/* *             *** loop *** */
		goto L41;
/* * */
/* *             *** tolerance not reached *** */
L42:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L43:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* * ********************************************************************* */
/* * type 3 -- fine grid points common to a coarse grid line */
/* * ********************************************************************* */
/* * */
/* * ********************************************************************* */
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
		i1 = i__ + 1;
		j1 = j + 1;
		k1 = k;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = k1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = k1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - uc[i1 + (j1 + 
			k1 * uc_dim2) * uc_dim1] - uc[i1 + (j1 + max(i__4,
			i__5) * uc_dim2) * uc_dim1] * (doublereal) min(i__6,
			i__7);
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L53;
		}
		if (niters > nitmax) {
		    goto L52;
		}
L51:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L53;
		}
		if (niters > nitmax) {
		    goto L52;
		}
/* * */
/* *             *** loop *** */
		goto L51;
/* * */
/* *             *** tolerance not reached *** */
L52:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L53:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* * ********************************************************************* */
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
		i1 = i__ + 1;
		j1 = j;
		k1 = k + 1;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = j1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = j1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - on[i1 + (j1 + 
			k1 * on_dim2) * on_dim1] - on[i1 + (max(i__4,i__5) + 
			k1 * on_dim2) * on_dim1] * (doublereal) min(i__6,i__7)
			;
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L63;
		}
		if (niters > nitmax) {
		    goto L62;
		}
L61:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L63;
		}
		if (niters > nitmax) {
		    goto L62;
		}
/* * */
/* *             *** loop *** */
		goto L61;
/* * */
/* *             *** tolerance not reached *** */
L62:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L63:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* * ********************************************************************* */
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
		i1 = i__;
		j1 = j + 1;
		k1 = k + 1;
/* * */
/* *             *** setup the 1d equation *** */
/* Computing MAX */
		i__4 = 1, i__5 = i1 - 1;
/* Computing MIN */
		i__6 = 1, i__7 = i1 - 1;
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1] - oe[i1 + (j1 + 
			k1 * oe_dim2) * oe_dim1] - oe[max(i__4,i__5) + (j1 + 
			k1 * oe_dim2) * oe_dim1] * (doublereal) min(i__6,i__7)
			;
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L73;
		}
		if (niters > nitmax) {
		    goto L72;
		}
L71:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L73;
		}
		if (niters > nitmax) {
		    goto L72;
		}
/* * */
/* *             *** loop *** */
		goto L71;
/* * */
/* *             *** tolerance not reached *** */
L72:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L73:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
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
		i1 = i__ + 1;
		j1 = j + 1;
		k1 = k + 1;
/* * */
/* *             *** setup the 1d equation *** */
		dd = oc[i1 + (j1 + k1 * oc_dim2) * oc_dim1];
		if (dd == 0.) {
		    dd = 1.;
		} else {
		    dd = 1. / dd;
		}
		uu = xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1];
		aa = 1.;
		bb = cc[i1 + (j1 + k1 * cc_dim2) * cc_dim1];
		ff = key * fc[i1 + (j1 + k1 * fc_dim2) * fc_dim1] + xout[i1 + 
			(j1 + k1 * xout_dim2) * xout_dim1];
/* * */
/* *             *** evaluate residual of 1d system */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *             *** setup for newton's method */
		niters = 0;
		zndenom = znn;
		if (zndenom == 0.) {
		    zndenom = 1.;
		}
		znerror = znn / zndenom;
/* * */
/* *             *** the 1d newton's method *** */
		if (znerror < zntol) {
		    goto L83;
		}
		if (niters > nitmax) {
		    goto L82;
		}
L81:
		++niters;
/* * */
/* *                *** construct jacobian matrix of NN *** */
		dznn = aa + dd * dc_scal__(&bb, &uu, &ipkey);
/* * */
/* *                *** solve the linear system *** */
		change = -znn / dznn;
/* * */
/* *                *** update the solution *** */
		uu += change;
/* * */
/* *                *** evaluate residual of 1d system *** */
		znn = aa * uu + dd * c_scal__(&bb, &uu, &ipkey) - ff;
/* * */
/* *                *** compute error *** */
		znerror = znn / zndenom;
/* * */
/* *                *** tolerance and itmax check *** */
		if (znerror < zntol) {
		    goto L83;
		}
		if (niters > nitmax) {
		    goto L82;
		}
/* * */
/* *             *** loop *** */
		goto L81;
/* * */
/* *             *** tolerance not reached *** */
L82:
		++ifail_tol__;
/* * */
/* *             *** tolerance reached *** */
L83:
/* * */
/* *             *** newton's method complete -- update solution value *** */
		xout[i1 + (j1 + k1 * xout_dim2) * xout_dim1] = uu;
/* * */
/* *             *** main loop *** */
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
/* *    *** messages *** */
    if (ifail_tol__ > 0) {
	s_wsle(&io___54);
	do_lio(&c__9, &c__1, "% NINTERP27: 1d newton tolerance failures: ", (
		ftnlen)43);
	do_lio(&c__3, &c__1, (char *)&ifail_tol__, (ftnlen)sizeof(integer));
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* ninterp27_ */

