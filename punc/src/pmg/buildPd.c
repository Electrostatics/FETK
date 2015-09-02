/* ./src_f77/buildPd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    buildPd.f */
/* * @author  Michael Holst */
/* * @brief   Routines to build the normal and opertor-based prolongations. */
/* * @version $Id: buildPd.c,v 1.3 2010/08/12 05:45:20 fetk Exp $ */
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
/* Subroutine */ int buildp_(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, integer *mgprol, integer *
	ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *xf, 
	doublereal *yf, doublereal *zf)
{
    /* System generated locals */
    integer pc_dim1, pc_offset, ac_dim1, ac_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int buildp_op7__(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *), buildp_op27__(integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *), buildp_modop7__(integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *), buildp_modop27__(
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *), 
	    buildp_trilin__(integer *, integer *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static integer numdia;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, 0, 0 };
    static cilist io___3 = { 0, 6, 0, 0, 0 };
    static cilist io___4 = { 0, 6, 0, 0, 0 };
    static cilist io___5 = { 0, 6, 0, 0, 0 };
    static cilist io___6 = { 0, 6, 0, 0, 0 };
    static cilist io___7 = { 0, 6, 0, 0, 0 };
    static cilist io___8 = { 0, 6, 0, 0, 0 };
    static cilist io___9 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    form the prolongation operator, which is one of: */
/* * */
/* *       (1) trilinear interpolation */
/* *       (2) standard operator-based prolongation */
/* *       (3) a modified operator-based prolongation */
/* * */
/* *    we differentiate between 7 and 27 point fine grid matrix in */
/* *    each case for efficiency in building the prolongation operator. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the build routine *** */
    /* Parameter adjustments */
    ac_dim1 = *nxf * *nyf * *nzf;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    pc_dim1 = *nxc * *nyc * *nzc;
    pc_offset = 1 + pc_dim1;
    pc -= pc_offset;
    --ipc;
    --rpc;
    --xf;
    --yf;
    --zf;

    /* Function Body */
    if (*mgprol == 0) {
	s_wsle(&io___1);
	do_lio(&c__9, &c__1, "% BUILDP:   (TRILINEAR) building prolongation."
		"..", (ftnlen)48);
	e_wsle();
	buildp_trilin__(nxf, nyf, nzf, nxc, nyc, nzc, &pc[pc_dim1 + 1], &xf[1]
		, &yf[1], &zf[1]);
    } else if (*mgprol == 1) {
	numdia = ipc[11];
	if (numdia == 7) {
	    s_wsle(&io___3);
	    do_lio(&c__9, &c__1, "% BUILDP:   (OPERATOR-7) building prolonga"
		    "tion...", (ftnlen)49);
	    e_wsle();
	    buildp_op7__(nxf, nyf, nzf, nxc, nyc, nzc, &ipc[1], &rpc[1], &ac[
		    ac_dim1 + 1], &pc[pc_dim1 + 1]);
	} else if (numdia == 27) {
	    s_wsle(&io___4);
	    do_lio(&c__9, &c__1, "% BUILDP:   (OPERATOR-27) building prolong"
		    "ation...", (ftnlen)50);
	    e_wsle();
	    buildp_op27__(nxf, nyf, nzf, nxc, nyc, nzc, &ipc[1], &rpc[1], &ac[
		    ac_dim1 + 1], &pc[pc_dim1 + 1]);
	} else {
	    s_wsle(&io___5);
	    do_lio(&c__9, &c__1, "% BUILDP: invalid stencil type give...", (
		    ftnlen)38);
	    e_wsle();
	}
    } else if (*mgprol == 2) {
	numdia = ipc[11];
	if (numdia == 7) {
	    s_wsle(&io___6);
	    do_lio(&c__9, &c__1, "% BUILDP: (MODIFY-OP-7) building prolongat"
		    "ion...", (ftnlen)48);
	    e_wsle();
	    buildp_modop7__(nxf, nyf, nzf, nxc, nyc, nzc, &ipc[1], &rpc[1], &
		    ac[ac_dim1 + 1], &pc[pc_dim1 + 1]);
	} else if (numdia == 27) {
	    s_wsle(&io___7);
	    do_lio(&c__9, &c__1, "% BUILDP: (MODIFY-OP-27) building prolonga"
		    "tion...", (ftnlen)49);
	    e_wsle();
	    buildp_modop27__(nxf, nyf, nzf, nxc, nyc, nzc, &ipc[1], &rpc[1], &
		    ac[ac_dim1 + 1], &pc[pc_dim1 + 1]);
	} else {
	    s_wsle(&io___8);
	    do_lio(&c__9, &c__1, "% BUILDP: invalid stencil type give...", (
		    ftnlen)38);
	    e_wsle();
	}
    } else {
	s_wsle(&io___9);
	do_lio(&c__9, &c__1, "% BUILDP: invalid prolongation requested...", (
		ftnlen)43);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildp_ */

/* Subroutine */ int buildp_trilin__(integer *nxf, integer *nyf, integer *nzf,
	 integer *nxc, integer *nyc, integer *nzc, doublereal *pc, doublereal 
	*xf, doublereal *yf, doublereal *zf)
{
    /* System generated locals */
    integer pc_dim1, pc_offset;

    /* Local variables */
    extern /* Subroutine */ int buildpb_trilin__(integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    call the routine to form the trilinear prolongation operator. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the build routine *** */
    /* Parameter adjustments */
    pc_dim1 = *nxc * *nyc * *nzc;
    pc_offset = 1 + pc_dim1;
    pc -= pc_offset;
    --xf;
    --yf;
    --zf;

    /* Function Body */
    buildpb_trilin__(nxf, nyf, nzf, nxc, nyc, nzc, &pc[pc_dim1 + 1], &pc[(
	    pc_dim1 << 1) + 1], &pc[pc_dim1 * 3 + 1], &pc[(pc_dim1 << 2) + 1],
	     &pc[pc_dim1 * 5 + 1], &pc[pc_dim1 * 6 + 1], &pc[pc_dim1 * 7 + 1],
	     &pc[(pc_dim1 << 3) + 1], &pc[pc_dim1 * 9 + 1], &pc[pc_dim1 * 10 
	    + 1], &pc[pc_dim1 * 11 + 1], &pc[pc_dim1 * 12 + 1], &pc[pc_dim1 * 
	    13 + 1], &pc[pc_dim1 * 14 + 1], &pc[pc_dim1 * 15 + 1], &pc[(
	    pc_dim1 << 4) + 1], &pc[pc_dim1 * 17 + 1], &pc[pc_dim1 * 18 + 1], 
	    &pc[pc_dim1 * 19 + 1], &pc[pc_dim1 * 20 + 1], &pc[pc_dim1 * 21 + 
	    1], &pc[pc_dim1 * 22 + 1], &pc[pc_dim1 * 23 + 1], &pc[pc_dim1 * 
	    24 + 1], &pc[pc_dim1 * 25 + 1], &pc[pc_dim1 * 26 + 1], &pc[
	    pc_dim1 * 27 + 1], &xf[1], &yf[1], &zf[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildp_trilin__ */

/* Subroutine */ int buildpb_trilin__(integer *nxf, integer *nyf, integer *
	nzf, integer *nxc, integer *nyc, integer *nzc, doublereal *opc, 
	doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, 
	doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *
	opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *
	upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *
	upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *
	dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *
	dpnw, doublereal *dpse, doublereal *dpsw, doublereal *xf, doublereal *
	yf, doublereal *zf)
{
    /* System generated locals */
    integer opc_dim1, opc_dim2, opc_offset, opn_dim1, opn_dim2, opn_offset, 
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
    static integer i__, j, k;
    static doublereal won, half, eighth, quarter;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    form the trilinear prolongation operator. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** interpolation stencil *** */
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
    --xf;
    --yf;
    --zf;

    /* Function Body */
    won = 1.;
    half = .5;
    quarter = .25;
    eighth = .125;
/* mdir 3 1 */
    i__1 = *nzc - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *nyc - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nxc - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		opc[i__ + (j + k * opc_dim2) * opc_dim1] = won;
		opn[i__ + (j + k * opn_dim2) * opn_dim1] = half;
		ops[i__ + (j + k * ops_dim2) * ops_dim1] = half;
		ope[i__ + (j + k * ope_dim2) * ope_dim1] = half;
		opw[i__ + (j + k * opw_dim2) * opw_dim1] = half;
		upc[i__ + (j + k * upc_dim2) * upc_dim1] = half;
		dpc[i__ + (j + k * dpc_dim2) * dpc_dim1] = half;
		opne[i__ + (j + k * opne_dim2) * opne_dim1] = quarter;
		opnw[i__ + (j + k * opnw_dim2) * opnw_dim1] = quarter;
		opse[i__ + (j + k * opse_dim2) * opse_dim1] = quarter;
		opsw[i__ + (j + k * opsw_dim2) * opsw_dim1] = quarter;
		dpn[i__ + (j + k * dpn_dim2) * dpn_dim1] = quarter;
		dps[i__ + (j + k * dps_dim2) * dps_dim1] = quarter;
		dpe[i__ + (j + k * dpe_dim2) * dpe_dim1] = quarter;
		dpw[i__ + (j + k * dpw_dim2) * dpw_dim1] = quarter;
		upn[i__ + (j + k * upn_dim2) * upn_dim1] = quarter;
		ups[i__ + (j + k * ups_dim2) * ups_dim1] = quarter;
		upe[i__ + (j + k * upe_dim2) * upe_dim1] = quarter;
		upw[i__ + (j + k * upw_dim2) * upw_dim1] = quarter;
		dpne[i__ + (j + k * dpne_dim2) * dpne_dim1] = eighth;
		dpnw[i__ + (j + k * dpnw_dim2) * dpnw_dim1] = eighth;
		dpse[i__ + (j + k * dpse_dim2) * dpse_dim1] = eighth;
		dpsw[i__ + (j + k * dpsw_dim2) * dpsw_dim1] = eighth;
		upne[i__ + (j + k * upne_dim2) * upne_dim1] = eighth;
		upnw[i__ + (j + k * upnw_dim2) * upnw_dim1] = eighth;
		upse[i__ + (j + k * upse_dim2) * upse_dim1] = eighth;
		upsw[i__ + (j + k * upsw_dim2) * upsw_dim1] = eighth;
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildpb_trilin__ */

/* Subroutine */ int buildp_op7__(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *
	rpc, doublereal *ac, doublereal *pc)
{
    /* System generated locals */
    integer ac_dim1, ac_offset, pc_dim1, pc_offset;

    /* Local variables */
    extern /* Subroutine */ int buildpb_op7__(integer *, integer *, integer *,
	     integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
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
/* *    standard 7-pt operator-based prologation. */
/* * */
/* *    call the routine to form the prolongation operator from a */
/* *    7 diagonal fine grid matrix. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the build routine *** */
    /* Parameter adjustments */
    ac_dim1 = *nxf * *nyf * *nzf;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    pc_dim1 = *nxc * *nyc * *nzc;
    pc_offset = 1 + pc_dim1;
    pc -= pc_offset;
    --ipc;
    --rpc;

    /* Function Body */
    buildpb_op7__(nxf, nyf, nzf, nxc, nyc, nzc, &ipc[1], &rpc[1], &ac[ac_dim1 
	    + 1], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 
	    << 2) + 1], &pc[pc_dim1 + 1], &pc[(pc_dim1 << 1) + 1], &pc[
	    pc_dim1 * 3 + 1], &pc[(pc_dim1 << 2) + 1], &pc[pc_dim1 * 5 + 1], &
	    pc[pc_dim1 * 6 + 1], &pc[pc_dim1 * 7 + 1], &pc[(pc_dim1 << 3) + 1]
	    , &pc[pc_dim1 * 9 + 1], &pc[pc_dim1 * 10 + 1], &pc[pc_dim1 * 11 + 
	    1], &pc[pc_dim1 * 12 + 1], &pc[pc_dim1 * 13 + 1], &pc[pc_dim1 * 
	    14 + 1], &pc[pc_dim1 * 15 + 1], &pc[(pc_dim1 << 4) + 1], &pc[
	    pc_dim1 * 17 + 1], &pc[pc_dim1 * 18 + 1], &pc[pc_dim1 * 19 + 1], &
	    pc[pc_dim1 * 20 + 1], &pc[pc_dim1 * 21 + 1], &pc[pc_dim1 * 22 + 1]
	    , &pc[pc_dim1 * 23 + 1], &pc[pc_dim1 * 24 + 1], &pc[pc_dim1 * 25 
	    + 1], &pc[pc_dim1 * 26 + 1], &pc[pc_dim1 * 27 + 1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildp_op7__ */

/* Subroutine */ int buildpb_op7__(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *
	rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, 
	doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, 
	doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse,
	 doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, 
	doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, 
	doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, 
	doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, 
	doublereal *dpnw, doublereal *dpse, doublereal *dpsw)
{
    /* System generated locals */
    integer oc_dim1, oc_dim2, oc_offset, oe_dim1, oe_dim2, oe_offset, on_dim1,
	     on_dim2, on_offset, uc_dim1, uc_dim2, uc_offset, opc_dim1, 
	    opc_dim2, opc_offset, opn_dim1, opn_dim2, opn_offset, ops_dim1, 
	    ops_dim2, ops_offset, ope_dim1, ope_dim2, ope_offset, opw_dim1, 
	    opw_dim2, opw_offset, opne_dim1, opne_dim2, opne_offset, 
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
    static integer i__, j, k, ii, jj, kk, im1, im2, jm1, ip1, ip2, jp1, jm2, 
	    jp2, km1, kp1, km2, kp2;
    static doublereal won;
    static integer iim1, jjm1, iip1, kkm1, jjp1, kkp1;
    static doublereal half, eighth, quarter;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    standard 7-pt operator-based prologation. */
/* * */
/* *    form the prolongation operator from a 7 diagonal fine grid matrix. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** interpolation stencil *** */
    /* Parameter adjustments */
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
    --ipc;
    --rpc;

    /* Function Body */
    won = 1.;
    half = .5;
    quarter = .25;
    eighth = .125;
    i__1 = *nzc - 1;
    for (kk = 2; kk <= i__1; ++kk) {
	k = (kk << 1) - 1;
	i__2 = *nyc - 1;
	for (jj = 2; jj <= i__2; ++jj) {
	    j = (jj << 1) - 1;
	    i__3 = *nxc - 1;
	    for (ii = 2; ii <= i__3; ++ii) {
		i__ = (ii << 1) - 1;
/* * */
/* *             *** index computations *** */
		im1 = i__ - 1;
		ip1 = i__ + 1;
		im2 = i__ - 2;
		ip2 = i__ + 2;
		jm1 = j - 1;
		jp1 = j + 1;
		jm2 = j - 2;
		jp2 = j + 2;
		km1 = k - 1;
		kp1 = k + 1;
		km2 = k - 2;
		kp2 = k + 2;
		iim1 = ii - 1;
		iip1 = ii + 1;
		jjm1 = jj - 1;
		jjp1 = jj + 1;
		kkm1 = kk - 1;
		kkp1 = kk + 1;
/* * */
/* * ******************************************************************** */
/* * *** > oPC; */
/* * ******************************************************************** */
		opc[ii + (jj + kk * opc_dim2) * opc_dim1] = won;
/* * ******************************************************************** */
/* * *** > oPN; */
/* * ******************************************************************** */
		opn[ii + (jj + kk * opn_dim2) * opn_dim1] = on[i__ + (j + k * 
			on_dim2) * on_dim1] / (oc[i__ + (jp1 + k * oc_dim2) * 
			oc_dim1] - oe[im1 + (jp1 + k * oe_dim2) * oe_dim1] - 
			oe[i__ + (jp1 + k * oe_dim2) * oe_dim1] - uc[i__ + (
			jp1 + km1 * uc_dim2) * uc_dim1] - uc[i__ + (jp1 + k * 
			uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPS; */
/* * ******************************************************************** */
		ops[ii + (jj + kk * ops_dim2) * ops_dim1] = on[i__ + (jm1 + k 
			* on_dim2) * on_dim1] / (oc[i__ + (jm1 + k * oc_dim2) 
			* oc_dim1] - oe[im1 + (jm1 + k * oe_dim2) * oe_dim1] 
			- oe[i__ + (jm1 + k * oe_dim2) * oe_dim1] - uc[i__ + (
			jm1 + km1 * uc_dim2) * uc_dim1] - uc[i__ + (jm1 + k * 
			uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPE; */
/* * ******************************************************************** */
		ope[ii + (jj + kk * ope_dim2) * ope_dim1] = oe[i__ + (j + k * 
			oe_dim2) * oe_dim1] / (oc[ip1 + (j + k * oc_dim2) * 
			oc_dim1] - uc[ip1 + (j + km1 * uc_dim2) * uc_dim1] - 
			uc[ip1 + (j + k * uc_dim2) * uc_dim1] - on[ip1 + (j + 
			k * on_dim2) * on_dim1] - on[ip1 + (jm1 + k * on_dim2)
			 * on_dim1]);
/* * ******************************************************************** */
/* * *** > oPW; */
/* * ******************************************************************** */
		opw[ii + (jj + kk * opw_dim2) * opw_dim1] = oe[im1 + (j + k * 
			oe_dim2) * oe_dim1] / (oc[im1 + (j + k * oc_dim2) * 
			oc_dim1] - uc[im1 + (j + km1 * uc_dim2) * uc_dim1] - 
			uc[im1 + (j + k * uc_dim2) * uc_dim1] - on[im1 + (j + 
			k * on_dim2) * on_dim1] - on[im1 + (jm1 + k * on_dim2)
			 * on_dim1]);
/* * ******************************************************************** */
/* * *** > oPNE; */
/* * ******************************************************************** */
		opne[ii + (jj + kk * opne_dim2) * opne_dim1] = (on[ip1 + (j + 
			k * on_dim2) * on_dim1] * ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] + oe[i__ + (jp1 + k * oe_dim2) *
			 oe_dim1] * opn[ii + (jj + kk * opn_dim2) * opn_dim1])
			 / (oc[ip1 + (jp1 + k * oc_dim2) * oc_dim1] - uc[ip1 
			+ (jp1 + km1 * uc_dim2) * uc_dim1] - uc[ip1 + (jp1 + 
			k * uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPNW; */
/* * ******************************************************************** */
		opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] = (on[im1 + (j + 
			k * on_dim2) * on_dim1] * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] + oe[im1 + (jp1 + k * oe_dim2) *
			 oe_dim1] * opn[ii + (jj + kk * opn_dim2) * opn_dim1])
			 / (oc[im1 + (jp1 + k * oc_dim2) * oc_dim1] - uc[im1 
			+ (jp1 + km1 * uc_dim2) * uc_dim1] - uc[im1 + (jp1 + 
			k * uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPSE; */
/* * ******************************************************************** */
		opse[ii + (jj + kk * opse_dim2) * opse_dim1] = (on[ip1 + (jm1 
			+ k * on_dim2) * on_dim1] * ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] + oe[i__ + (jm1 + k * oe_dim2) *
			 oe_dim1] * ops[ii + (jj + kk * ops_dim2) * ops_dim1])
			 / (oc[ip1 + (jm1 + k * oc_dim2) * oc_dim1] - uc[ip1 
			+ (jm1 + km1 * uc_dim2) * uc_dim1] - uc[ip1 + (jm1 + 
			k * uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPSW; */
/* * ******************************************************************** */
		opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] = (on[im1 + (jm1 
			+ k * on_dim2) * on_dim1] * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] + oe[im1 + (jm1 + k * oe_dim2) *
			 oe_dim1] * ops[ii + (jj + kk * ops_dim2) * ops_dim1])
			 / (oc[im1 + (jm1 + k * oc_dim2) * oc_dim1] - uc[im1 
			+ (jm1 + km1 * uc_dim2) * uc_dim1] - uc[im1 + (jm1 + 
			k * uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > dPC; */
/* * ******************************************************************** */
		dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] = uc[i__ + (j + km1 
			* uc_dim2) * uc_dim1] / (oc[i__ + (j + km1 * oc_dim2) 
			* oc_dim1] - on[i__ + (j + km1 * on_dim2) * on_dim1] 
			- on[i__ + (jm1 + km1 * on_dim2) * on_dim1] - oe[im1 
			+ (j + km1 * oe_dim2) * oe_dim1] - oe[i__ + (j + km1 *
			 oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > dPN; */
/* * ******************************************************************** */
		dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] = (on[i__ + (j + 
			km1 * on_dim2) * on_dim1] * dpc[ii + (jj + kk * 
			dpc_dim2) * dpc_dim1] + uc[i__ + (jp1 + km1 * uc_dim2)
			 * uc_dim1] * opn[ii + (jj + kk * opn_dim2) * 
			opn_dim1]) / (oc[i__ + (jp1 + km1 * oc_dim2) * 
			oc_dim1] - oe[im1 + (jp1 + km1 * oe_dim2) * oe_dim1] 
			- oe[i__ + (jp1 + km1 * oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > dPS; */
/* * ******************************************************************** */
		dps[ii + (jj + kk * dps_dim2) * dps_dim1] = (on[i__ + (jm1 + 
			km1 * on_dim2) * on_dim1] * dpc[ii + (jj + kk * 
			dpc_dim2) * dpc_dim1] + uc[i__ + (jm1 + km1 * uc_dim2)
			 * uc_dim1] * ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1]) / (oc[i__ + (jm1 + km1 * oc_dim2) * 
			oc_dim1] - oe[im1 + (jm1 + km1 * oe_dim2) * oe_dim1] 
			- oe[i__ + (jm1 + km1 * oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > dPE; */
/* * ******************************************************************** */
		dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] = (uc[ip1 + (j + 
			km1 * uc_dim2) * uc_dim1] * ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] + oe[i__ + (j + km1 * oe_dim2) *
			 oe_dim1] * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1])
			 / (oc[ip1 + (j + km1 * oc_dim2) * oc_dim1] - on[ip1 
			+ (j + km1 * on_dim2) * on_dim1] - on[ip1 + (jm1 + 
			km1 * on_dim2) * on_dim1]);
/* * ******************************************************************** */
/* * *** > dPW; */
/* * ******************************************************************** */
		dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] = (uc[im1 + (j + 
			km1 * uc_dim2) * uc_dim1] * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] + oe[im1 + (j + km1 * oe_dim2) *
			 oe_dim1] * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1])
			 / (oc[im1 + (j + km1 * oc_dim2) * oc_dim1] - on[im1 
			+ (j + km1 * on_dim2) * on_dim1] - on[im1 + (jm1 + 
			km1 * on_dim2) * on_dim1]);
/* * ******************************************************************** */
/* * *** > dPNE; */
/* * ******************************************************************** */
		dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] = (uc[ip1 + (jp1 
			+ km1 * uc_dim2) * uc_dim1] * opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1] + oe[i__ + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpn[ii + (jj + kk * dpn_dim2) * 
			dpn_dim1] + on[ip1 + (j + km1 * on_dim2) * on_dim1] * 
			dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1]) / oc[ip1 + 
			(jp1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > dPNW; */
/* * ******************************************************************** */
		dpnw[ii + (jj + kk * dpnw_dim2) * dpnw_dim1] = (uc[im1 + (jp1 
			+ km1 * uc_dim2) * uc_dim1] * opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] + oe[im1 + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpn[ii + (jj + kk * dpn_dim2) * 
			dpn_dim1] + on[im1 + (j + km1 * on_dim2) * on_dim1] * 
			dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1]) / oc[im1 + 
			(jp1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > dPSE; */
/* * ******************************************************************** */
		dpse[ii + (jj + kk * dpse_dim2) * dpse_dim1] = (uc[ip1 + (jm1 
			+ km1 * uc_dim2) * uc_dim1] * opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] + oe[i__ + (jm1 + km1 * 
			oe_dim2) * oe_dim1] * dps[ii + (jj + kk * dps_dim2) * 
			dps_dim1] + on[ip1 + (jm1 + km1 * on_dim2) * on_dim1] 
			* dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1]) / oc[ip1 
			+ (jm1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > dPSW; */
/* * ******************************************************************** */
		dpsw[ii + (jj + kk * dpsw_dim2) * dpsw_dim1] = (uc[im1 + (jm1 
			+ km1 * uc_dim2) * uc_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] + oe[im1 + (jm1 + km1 * 
			oe_dim2) * oe_dim1] * dps[ii + (jj + kk * dps_dim2) * 
			dps_dim1] + on[im1 + (jm1 + km1 * on_dim2) * on_dim1] 
			* dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1]) / oc[im1 
			+ (jm1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPC; */
/* * ******************************************************************** */
		upc[ii + (jj + kk * upc_dim2) * upc_dim1] = uc[i__ + (j + k * 
			uc_dim2) * uc_dim1] / (oc[i__ + (j + kp1 * oc_dim2) * 
			oc_dim1] - on[i__ + (j + kp1 * on_dim2) * on_dim1] - 
			on[i__ + (jm1 + kp1 * on_dim2) * on_dim1] - oe[im1 + (
			j + kp1 * oe_dim2) * oe_dim1] - oe[i__ + (j + kp1 * 
			oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > uPN; */
/* * ******************************************************************** */
		upn[ii + (jj + kk * upn_dim2) * upn_dim1] = (on[i__ + (j + 
			kp1 * on_dim2) * on_dim1] * upc[ii + (jj + kk * 
			upc_dim2) * upc_dim1] + uc[i__ + (jp1 + k * uc_dim2) *
			 uc_dim1] * opn[ii + (jj + kk * opn_dim2) * opn_dim1])
			 / (oc[i__ + (jp1 + kp1 * oc_dim2) * oc_dim1] - oe[
			im1 + (jp1 + kp1 * oe_dim2) * oe_dim1] - oe[i__ + (
			jp1 + kp1 * oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > uPS; */
/* * ******************************************************************** */
		ups[ii + (jj + kk * ups_dim2) * ups_dim1] = (on[i__ + (jm1 + 
			kp1 * on_dim2) * on_dim1] * upc[ii + (jj + kk * 
			upc_dim2) * upc_dim1] + uc[i__ + (jm1 + k * uc_dim2) *
			 uc_dim1] * ops[ii + (jj + kk * ops_dim2) * ops_dim1])
			 / (oc[i__ + (jm1 + kp1 * oc_dim2) * oc_dim1] - oe[
			im1 + (jm1 + kp1 * oe_dim2) * oe_dim1] - oe[i__ + (
			jm1 + kp1 * oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > uPE; */
/* * ******************************************************************** */
		upe[ii + (jj + kk * upe_dim2) * upe_dim1] = (uc[ip1 + (j + k *
			 uc_dim2) * uc_dim1] * ope[ii + (jj + kk * ope_dim2) *
			 ope_dim1] + oe[i__ + (j + kp1 * oe_dim2) * oe_dim1] *
			 upc[ii + (jj + kk * upc_dim2) * upc_dim1]) / (oc[ip1 
			+ (j + kp1 * oc_dim2) * oc_dim1] - on[ip1 + (j + kp1 *
			 on_dim2) * on_dim1] - on[ip1 + (jm1 + kp1 * on_dim2) 
			* on_dim1]);
/* * ******************************************************************** */
/* * *** > uPW; */
/* * ******************************************************************** */
		upw[ii + (jj + kk * upw_dim2) * upw_dim1] = (uc[im1 + (j + k *
			 uc_dim2) * uc_dim1] * opw[ii + (jj + kk * opw_dim2) *
			 opw_dim1] + oe[im1 + (j + kp1 * oe_dim2) * oe_dim1] *
			 upc[ii + (jj + kk * upc_dim2) * upc_dim1]) / (oc[im1 
			+ (j + kp1 * oc_dim2) * oc_dim1] - on[im1 + (j + kp1 *
			 on_dim2) * on_dim1] - on[im1 + (jm1 + kp1 * on_dim2) 
			* on_dim1]);
/* * ******************************************************************** */
/* * *** > uPNE; */
/* * ******************************************************************** */
		upne[ii + (jj + kk * upne_dim2) * upne_dim1] = (uc[ip1 + (jp1 
			+ k * uc_dim2) * uc_dim1] * opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1] + oe[i__ + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * upn[ii + (jj + kk * upn_dim2) * 
			upn_dim1] + on[ip1 + (j + kp1 * on_dim2) * on_dim1] * 
			upe[ii + (jj + kk * upe_dim2) * upe_dim1]) / oc[ip1 + 
			(jp1 + kp1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPNW; */
/* * ******************************************************************** */
		upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] = (uc[im1 + (jp1 
			+ k * uc_dim2) * uc_dim1] * opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] + oe[im1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * upn[ii + (jj + kk * upn_dim2) * 
			upn_dim1] + on[im1 + (j + kp1 * on_dim2) * on_dim1] * 
			upw[ii + (jj + kk * upw_dim2) * upw_dim1]) / oc[im1 + 
			(jp1 + kp1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPSE; */
/* * ******************************************************************** */
		upse[ii + (jj + kk * upse_dim2) * upse_dim1] = (uc[ip1 + (jm1 
			+ k * uc_dim2) * uc_dim1] * opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] + oe[i__ + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * ups[ii + (jj + kk * ups_dim2) * 
			ups_dim1] + on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1] 
			* upe[ii + (jj + kk * upe_dim2) * upe_dim1]) / oc[ip1 
			+ (jm1 + kp1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPSW; */
/* * ******************************************************************** */
		upsw[ii + (jj + kk * upsw_dim2) * upsw_dim1] = (uc[im1 + (jm1 
			+ k * uc_dim2) * uc_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] + oe[im1 + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * ups[ii + (jj + kk * ups_dim2) * 
			ups_dim1] + on[im1 + (jm1 + kp1 * on_dim2) * on_dim1] 
			* upw[ii + (jj + kk * upw_dim2) * upw_dim1]) / oc[im1 
			+ (jm1 + kp1 * oc_dim2) * oc_dim1];
/* *             *** main loop *** */
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildpb_op7__ */

/* Subroutine */ int buildp_op27__(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *
	rpc, doublereal *ac, doublereal *pc)
{
    /* System generated locals */
    integer ac_dim1, ac_offset, pc_dim1, pc_offset;

    /* Local variables */
    extern /* Subroutine */ int buildpb_op27__(integer *, integer *, integer *
	    , integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    standard 27-pt operator-based prologation. */
/* * */
/* *    call the routine to form the prolongation operator from a */
/* *    27 diagonal fine grid matrix. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the build routine *** */
    /* Parameter adjustments */
    ac_dim1 = *nxf * *nyf * *nzf;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    pc_dim1 = *nxc * *nyc * *nzc;
    pc_offset = 1 + pc_dim1;
    pc -= pc_offset;
    --ipc;
    --rpc;

    /* Function Body */
    buildpb_op27__(nxf, nyf, nzf, nxc, nyc, nzc, &ipc[1], &rpc[1], &ac[
	    ac_dim1 + 1], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(
	    ac_dim1 << 2) + 1], &ac[ac_dim1 * 5 + 1], &ac[ac_dim1 * 6 + 1], &
	    ac[ac_dim1 * 7 + 1], &ac[(ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1]
	    , &ac[ac_dim1 * 10 + 1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 
	    + 1], &ac[ac_dim1 * 13 + 1], &ac[ac_dim1 * 14 + 1], &pc[pc_dim1 + 
	    1], &pc[(pc_dim1 << 1) + 1], &pc[pc_dim1 * 3 + 1], &pc[(pc_dim1 <<
	     2) + 1], &pc[pc_dim1 * 5 + 1], &pc[pc_dim1 * 6 + 1], &pc[pc_dim1 
	    * 7 + 1], &pc[(pc_dim1 << 3) + 1], &pc[pc_dim1 * 9 + 1], &pc[
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
} /* buildp_op27__ */

/* Subroutine */ int buildpb_op27__(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *
	rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, 
	doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, 
	doublereal *un, doublereal *us, doublereal *une, doublereal *unw, 
	doublereal *use, doublereal *usw, doublereal *opc, doublereal *opn, 
	doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, 
	doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc,
	 doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, 
	doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *
	upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *
	dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *
	dpse, doublereal *dpsw)
{
    /* System generated locals */
    integer oc_dim1, oc_dim2, oc_offset, oe_dim1, oe_dim2, oe_offset, on_dim1,
	     on_dim2, on_offset, uc_dim1, uc_dim2, uc_offset, one_dim1, 
	    one_dim2, one_offset, onw_dim1, onw_dim2, onw_offset, ue_dim1, 
	    ue_dim2, ue_offset, uw_dim1, uw_dim2, uw_offset, un_dim1, un_dim2,
	     un_offset, us_dim1, us_dim2, us_offset, une_dim1, une_dim2, 
	    une_offset, unw_dim1, unw_dim2, unw_offset, use_dim1, use_dim2, 
	    use_offset, usw_dim1, usw_dim2, usw_offset, opc_dim1, opc_dim2, 
	    opc_offset, opn_dim1, opn_dim2, opn_offset, ops_dim1, ops_dim2, 
	    ops_offset, ope_dim1, ope_dim2, ope_offset, opw_dim1, opw_dim2, 
	    opw_offset, opne_dim1, opne_dim2, opne_offset, opnw_dim1, 
	    opnw_dim2, opnw_offset, opse_dim1, opse_dim2, opse_offset, 
	    opsw_dim1, opsw_dim2, opsw_offset, upc_dim1, upc_dim2, upc_offset,
	     upn_dim1, upn_dim2, upn_offset, ups_dim1, ups_dim2, ups_offset, 
	    upe_dim1, upe_dim2, upe_offset, upw_dim1, upw_dim2, upw_offset, 
	    upne_dim1, upne_dim2, upne_offset, upnw_dim1, upnw_dim2, 
	    upnw_offset, upse_dim1, upse_dim2, upse_offset, upsw_dim1, 
	    upsw_dim2, upsw_offset, dpc_dim1, dpc_dim2, dpc_offset, dpn_dim1, 
	    dpn_dim2, dpn_offset, dps_dim1, dps_dim2, dps_offset, dpe_dim1, 
	    dpe_dim2, dpe_offset, dpw_dim1, dpw_dim2, dpw_offset, dpne_dim1, 
	    dpne_dim2, dpne_offset, dpnw_dim1, dpnw_dim2, dpnw_offset, 
	    dpse_dim1, dpse_dim2, dpse_offset, dpsw_dim1, dpsw_dim2, 
	    dpsw_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, ii, jj, kk, im1, im2, jm1, ip1, ip2, jp1, jm2, 
	    jp2, km1, kp1, km2, kp2;
    static doublereal won;
    static integer iim1, jjm1, iip1, kkm1, jjp1, kkp1;
    static doublereal half, eighth, quarter;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    standard 27-pt operator-based prologation. */
/* * */
/* *    form the prolongation operator from a 27 diagonal fine grid matrix. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** interpolation stencil *** */
    /* Parameter adjustments */
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
    --ipc;
    --rpc;

    /* Function Body */
    won = 1.;
    half = .5;
    quarter = .25;
    eighth = .125;
    i__1 = *nzc - 1;
    for (kk = 2; kk <= i__1; ++kk) {
	k = (kk << 1) - 1;
	i__2 = *nyc - 1;
	for (jj = 2; jj <= i__2; ++jj) {
	    j = (jj << 1) - 1;
	    i__3 = *nxc - 1;
	    for (ii = 2; ii <= i__3; ++ii) {
		i__ = (ii << 1) - 1;
/* * */
/* *             *** index computations *** */
		im1 = i__ - 1;
		ip1 = i__ + 1;
		im2 = i__ - 2;
		ip2 = i__ + 2;
		jm1 = j - 1;
		jp1 = j + 1;
		jm2 = j - 2;
		jp2 = j + 2;
		km1 = k - 1;
		kp1 = k + 1;
		km2 = k - 2;
		kp2 = k + 2;
		iim1 = ii - 1;
		iip1 = ii + 1;
		jjm1 = jj - 1;
		jjp1 = jj + 1;
		kkm1 = kk - 1;
		kkp1 = kk + 1;
/* * */
/* * ******************************************************************** */
/* * *** > oPC; */
/* * ******************************************************************** */
		opc[ii + (jj + kk * opc_dim2) * opc_dim1] = won;
/* * ******************************************************************** */
/* * *** > oPN; */
/* * ******************************************************************** */
		opn[ii + (jj + kk * opn_dim2) * opn_dim1] = (une[im1 + (j + 
			km1 * une_dim2) * une_dim1] + un[i__ + (j + km1 * 
			un_dim2) * un_dim1] + unw[ip1 + (j + km1 * unw_dim2) *
			 unw_dim1] + one[im1 + (j + k * one_dim2) * one_dim1] 
			+ on[i__ + (j + k * on_dim2) * on_dim1] + onw[ip1 + (
			j + k * onw_dim2) * onw_dim1] + usw[i__ + (jp1 + k * 
			usw_dim2) * usw_dim1] + us[i__ + (jp1 + k * us_dim2) *
			 us_dim1] + use[i__ + (jp1 + k * use_dim2) * use_dim1]
			) / (oc[i__ + (jp1 + k * oc_dim2) * oc_dim1] - oe[im1 
			+ (jp1 + k * oe_dim2) * oe_dim1] - oe[i__ + (jp1 + k *
			 oe_dim2) * oe_dim1] - uc[i__ + (jp1 + km1 * uc_dim2) 
			* uc_dim1] - ue[im1 + (jp1 + km1 * ue_dim2) * ue_dim1]
			 - uw[ip1 + (jp1 + km1 * uw_dim2) * uw_dim1] - uc[i__ 
			+ (jp1 + k * uc_dim2) * uc_dim1] - uw[i__ + (jp1 + k *
			 uw_dim2) * uw_dim1] - ue[i__ + (jp1 + k * ue_dim2) * 
			ue_dim1]);
/* * ******************************************************************** */
/* * *** > oPS; */
/* * ******************************************************************** */
		ops[ii + (jj + kk * ops_dim2) * ops_dim1] = (use[im1 + (j + 
			km1 * use_dim2) * use_dim1] + us[i__ + (j + km1 * 
			us_dim2) * us_dim1] + usw[ip1 + (j + km1 * usw_dim2) *
			 usw_dim1] + onw[i__ + (jm1 + k * onw_dim2) * 
			onw_dim1] + on[i__ + (jm1 + k * on_dim2) * on_dim1] + 
			one[i__ + (jm1 + k * one_dim2) * one_dim1] + unw[i__ 
			+ (jm1 + k * unw_dim2) * unw_dim1] + un[i__ + (jm1 + 
			k * un_dim2) * un_dim1] + une[i__ + (jm1 + k * 
			une_dim2) * une_dim1]) / (oc[i__ + (jm1 + k * oc_dim2)
			 * oc_dim1] - oe[im1 + (jm1 + k * oe_dim2) * oe_dim1] 
			- oe[i__ + (jm1 + k * oe_dim2) * oe_dim1] - uc[i__ + (
			jm1 + km1 * uc_dim2) * uc_dim1] - ue[im1 + (jm1 + km1 
			* ue_dim2) * ue_dim1] - uw[ip1 + (jm1 + km1 * uw_dim2)
			 * uw_dim1] - uc[i__ + (jm1 + k * uc_dim2) * uc_dim1] 
			- uw[i__ + (jm1 + k * uw_dim2) * uw_dim1] - ue[i__ + (
			jm1 + k * ue_dim2) * ue_dim1]);
/* * ******************************************************************** */
/* * *** > oPE; */
/* * ******************************************************************** */
		ope[ii + (jj + kk * ope_dim2) * ope_dim1] = (use[i__ + (jp1 + 
			km1 * use_dim2) * use_dim1] + onw[ip1 + (j + k * 
			onw_dim2) * onw_dim1] + unw[ip1 + (j + k * unw_dim2) *
			 unw_dim1] + ue[i__ + (j + km1 * ue_dim2) * ue_dim1] 
			+ oe[i__ + (j + k * oe_dim2) * oe_dim1] + uw[ip1 + (j 
			+ k * uw_dim2) * uw_dim1] + une[i__ + (jm1 + km1 * 
			une_dim2) * une_dim1] + one[i__ + (jm1 + k * one_dim2)
			 * one_dim1] + usw[ip1 + (j + k * usw_dim2) * 
			usw_dim1]) / (oc[ip1 + (j + k * oc_dim2) * oc_dim1] - 
			uc[ip1 + (j + km1 * uc_dim2) * uc_dim1] - uc[ip1 + (j 
			+ k * uc_dim2) * uc_dim1] - on[ip1 + (j + k * on_dim2)
			 * on_dim1] - us[ip1 + (jp1 + km1 * us_dim2) * 
			us_dim1] - un[ip1 + (j + k * un_dim2) * un_dim1] - on[
			ip1 + (jm1 + k * on_dim2) * on_dim1] - un[ip1 + (jm1 
			+ km1 * un_dim2) * un_dim1] - us[ip1 + (j + k * 
			us_dim2) * us_dim1]);
/* * ******************************************************************** */
/* * *** > oPW; */
/* * ******************************************************************** */
		opw[ii + (jj + kk * opw_dim2) * opw_dim1] = (usw[i__ + (jp1 + 
			km1 * usw_dim2) * usw_dim1] + one[im1 + (j + k * 
			one_dim2) * one_dim1] + une[im1 + (j + k * une_dim2) *
			 une_dim1] + uw[i__ + (j + km1 * uw_dim2) * uw_dim1] 
			+ oe[im1 + (j + k * oe_dim2) * oe_dim1] + ue[im1 + (j 
			+ k * ue_dim2) * ue_dim1] + unw[i__ + (jm1 + km1 * 
			unw_dim2) * unw_dim1] + onw[i__ + (jm1 + k * onw_dim2)
			 * onw_dim1] + use[im1 + (j + k * use_dim2) * 
			use_dim1]) / (oc[im1 + (j + k * oc_dim2) * oc_dim1] - 
			uc[im1 + (j + km1 * uc_dim2) * uc_dim1] - uc[im1 + (j 
			+ k * uc_dim2) * uc_dim1] - on[im1 + (j + k * on_dim2)
			 * on_dim1] - us[im1 + (jp1 + km1 * us_dim2) * 
			us_dim1] - un[im1 + (j + k * un_dim2) * un_dim1] - on[
			im1 + (jm1 + k * on_dim2) * on_dim1] - un[im1 + (jm1 
			+ km1 * un_dim2) * un_dim1] - us[im1 + (j + k * 
			us_dim2) * us_dim1]);
/* * ******************************************************************** */
/* * *** > oPNE; */
/* * ******************************************************************** */
		opne[ii + (jj + kk * opne_dim2) * opne_dim1] = (une[i__ + (j 
			+ km1 * une_dim2) * une_dim1] + one[i__ + (j + k * 
			one_dim2) * one_dim1] + usw[ip1 + (jp1 + k * usw_dim2)
			 * usw_dim1] + (un[ip1 + (j + km1 * un_dim2) * 
			un_dim1] + on[ip1 + (j + k * on_dim2) * on_dim1] + us[
			ip1 + (jp1 + k * us_dim2) * us_dim1]) * ope[ii + (jj 
			+ kk * ope_dim2) * ope_dim1] + (ue[i__ + (jp1 + km1 * 
			ue_dim2) * ue_dim1] + oe[i__ + (jp1 + k * oe_dim2) * 
			oe_dim1] + uw[ip1 + (jp1 + k * uw_dim2) * uw_dim1]) * 
			opn[ii + (jj + kk * opn_dim2) * opn_dim1]) / (oc[ip1 
			+ (jp1 + k * oc_dim2) * oc_dim1] - uc[ip1 + (jp1 + 
			km1 * uc_dim2) * uc_dim1] - uc[ip1 + (jp1 + k * 
			uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPNW; */
/* * ******************************************************************** */
		opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] = (unw[i__ + (j 
			+ km1 * unw_dim2) * unw_dim1] + onw[i__ + (j + k * 
			onw_dim2) * onw_dim1] + use[im1 + (jp1 + k * use_dim2)
			 * use_dim1] + (un[im1 + (j + km1 * un_dim2) * 
			un_dim1] + on[im1 + (j + k * on_dim2) * on_dim1] + us[
			im1 + (jp1 + k * us_dim2) * us_dim1]) * opw[ii + (jj 
			+ kk * opw_dim2) * opw_dim1] + (uw[i__ + (jp1 + km1 * 
			uw_dim2) * uw_dim1] + oe[im1 + (jp1 + k * oe_dim2) * 
			oe_dim1] + ue[im1 + (jp1 + k * ue_dim2) * ue_dim1]) * 
			opn[ii + (jj + kk * opn_dim2) * opn_dim1]) / (oc[im1 
			+ (jp1 + k * oc_dim2) * oc_dim1] - uc[im1 + (jp1 + 
			km1 * uc_dim2) * uc_dim1] - uc[im1 + (jp1 + k * 
			uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPSE; */
/* * ******************************************************************** */
		opse[ii + (jj + kk * opse_dim2) * opse_dim1] = (use[i__ + (j 
			+ km1 * use_dim2) * use_dim1] + onw[ip1 + (jm1 + k * 
			onw_dim2) * onw_dim1] + unw[ip1 + (jm1 + k * unw_dim2)
			 * unw_dim1] + (us[ip1 + (j + km1 * us_dim2) * 
			us_dim1] + on[ip1 + (jm1 + k * on_dim2) * on_dim1] + 
			un[ip1 + (jm1 + k * un_dim2) * un_dim1]) * ope[ii + (
			jj + kk * ope_dim2) * ope_dim1] + (ue[i__ + (jm1 + 
			km1 * ue_dim2) * ue_dim1] + oe[i__ + (jm1 + k * 
			oe_dim2) * oe_dim1] + uw[ip1 + (jm1 + k * uw_dim2) * 
			uw_dim1]) * ops[ii + (jj + kk * ops_dim2) * ops_dim1])
			 / (oc[ip1 + (jm1 + k * oc_dim2) * oc_dim1] - uc[ip1 
			+ (jm1 + km1 * uc_dim2) * uc_dim1] - uc[ip1 + (jm1 + 
			k * uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPSW; */
/* * ******************************************************************** */
		opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] = (usw[i__ + (j 
			+ km1 * usw_dim2) * usw_dim1] + one[im1 + (jm1 + k * 
			one_dim2) * one_dim1] + une[im1 + (jm1 + k * une_dim2)
			 * une_dim1] + (us[im1 + (j + km1 * us_dim2) * 
			us_dim1] + on[im1 + (jm1 + k * on_dim2) * on_dim1] + 
			un[im1 + (jm1 + k * un_dim2) * un_dim1]) * opw[ii + (
			jj + kk * opw_dim2) * opw_dim1] + (uw[i__ + (jm1 + 
			km1 * uw_dim2) * uw_dim1] + oe[im1 + (jm1 + k * 
			oe_dim2) * oe_dim1] + ue[im1 + (jm1 + k * ue_dim2) * 
			ue_dim1]) * ops[ii + (jj + kk * ops_dim2) * ops_dim1])
			 / (oc[im1 + (jm1 + k * oc_dim2) * oc_dim1] - uc[im1 
			+ (jm1 + km1 * uc_dim2) * uc_dim1] - uc[im1 + (jm1 + 
			k * uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > dPC; */
/* * ******************************************************************** */
		dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] = (unw[i__ + (j + 
			km1 * unw_dim2) * unw_dim1] + uw[i__ + (j + km1 * 
			uw_dim2) * uw_dim1] + usw[i__ + (j + km1 * usw_dim2) *
			 usw_dim1] + un[i__ + (j + km1 * un_dim2) * un_dim1] 
			+ uc[i__ + (j + km1 * uc_dim2) * uc_dim1] + us[i__ + (
			j + km1 * us_dim2) * us_dim1] + une[i__ + (j + km1 * 
			une_dim2) * une_dim1] + ue[i__ + (j + km1 * ue_dim2) *
			 ue_dim1] + use[i__ + (j + km1 * use_dim2) * use_dim1]
			) / (oc[i__ + (j + km1 * oc_dim2) * oc_dim1] - on[i__ 
			+ (j + km1 * on_dim2) * on_dim1] - on[i__ + (jm1 + 
			km1 * on_dim2) * on_dim1] - onw[i__ + (j + km1 * 
			onw_dim2) * onw_dim1] - oe[im1 + (j + km1 * oe_dim2) *
			 oe_dim1] - one[im1 + (jm1 + km1 * one_dim2) * 
			one_dim1] - one[i__ + (j + km1 * one_dim2) * one_dim1]
			 - oe[i__ + (j + km1 * oe_dim2) * oe_dim1] - onw[ip1 
			+ (jm1 + km1 * onw_dim2) * onw_dim1]);
/* * ******************************************************************** */
/* * *** > dPN; */
/* * ******************************************************************** */
		dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] = (usw[i__ + (jp1 + 
			km1 * usw_dim2) * usw_dim1] + us[i__ + (jp1 + km1 * 
			us_dim2) * us_dim1] + use[i__ + (jp1 + km1 * use_dim2)
			 * use_dim1] + (one[im1 + (j + km1 * one_dim2) * 
			one_dim1] + on[i__ + (j + km1 * on_dim2) * on_dim1] + 
			onw[ip1 + (j + km1 * onw_dim2) * onw_dim1]) * dpc[ii 
			+ (jj + kk * dpc_dim2) * dpc_dim1] + (uw[i__ + (jp1 + 
			km1 * uw_dim2) * uw_dim1] + uc[i__ + (jp1 + km1 * 
			uc_dim2) * uc_dim1] + ue[i__ + (jp1 + km1 * ue_dim2) *
			 ue_dim1]) * opn[ii + (jj + kk * opn_dim2) * opn_dim1]
			) / (oc[i__ + (jp1 + km1 * oc_dim2) * oc_dim1] - oe[
			im1 + (jp1 + km1 * oe_dim2) * oe_dim1] - oe[i__ + (
			jp1 + km1 * oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > dPS; */
/* * ******************************************************************** */
		dps[ii + (jj + kk * dps_dim2) * dps_dim1] = (unw[i__ + (jm1 + 
			km1 * unw_dim2) * unw_dim1] + un[i__ + (jm1 + km1 * 
			un_dim2) * un_dim1] + une[i__ + (jm1 + km1 * une_dim2)
			 * une_dim1] + (onw[i__ + (jm1 + km1 * onw_dim2) * 
			onw_dim1] + on[i__ + (jm1 + km1 * on_dim2) * on_dim1] 
			+ one[i__ + (jm1 + km1 * one_dim2) * one_dim1]) * dpc[
			ii + (jj + kk * dpc_dim2) * dpc_dim1] + (uw[i__ + (
			jm1 + km1 * uw_dim2) * uw_dim1] + uc[i__ + (jm1 + km1 
			* uc_dim2) * uc_dim1] + ue[i__ + (jm1 + km1 * ue_dim2)
			 * ue_dim1]) * ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1]) / (oc[i__ + (jm1 + km1 * oc_dim2) * 
			oc_dim1] - oe[im1 + (jm1 + km1 * oe_dim2) * oe_dim1] 
			- oe[i__ + (jm1 + km1 * oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > dPE; */
/* * ******************************************************************** */
		dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] = (unw[ip1 + (j + 
			km1 * unw_dim2) * unw_dim1] + uw[ip1 + (j + km1 * 
			uw_dim2) * uw_dim1] + usw[ip1 + (j + km1 * usw_dim2) *
			 usw_dim1] + (un[ip1 + (j + km1 * un_dim2) * un_dim1] 
			+ uc[ip1 + (j + km1 * uc_dim2) * uc_dim1] + us[ip1 + (
			j + km1 * us_dim2) * us_dim1]) * ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] + (onw[ip1 + (j + km1 * 
			onw_dim2) * onw_dim1] + oe[i__ + (j + km1 * oe_dim2) *
			 oe_dim1] + one[i__ + (jm1 + km1 * one_dim2) * 
			one_dim1]) * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1]
			) / (oc[ip1 + (j + km1 * oc_dim2) * oc_dim1] - on[ip1 
			+ (j + km1 * on_dim2) * on_dim1] - on[ip1 + (jm1 + 
			km1 * on_dim2) * on_dim1]);
/* * ******************************************************************** */
/* * *** > dPW; */
/* * ******************************************************************** */
		dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] = (une[im1 + (j + 
			km1 * une_dim2) * une_dim1] + ue[im1 + (j + km1 * 
			ue_dim2) * ue_dim1] + use[im1 + (j + km1 * use_dim2) *
			 use_dim1] + (un[im1 + (j + km1 * un_dim2) * un_dim1] 
			+ uc[im1 + (j + km1 * uc_dim2) * uc_dim1] + us[im1 + (
			j + km1 * us_dim2) * us_dim1]) * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] + (one[im1 + (j + km1 * 
			one_dim2) * one_dim1] + oe[im1 + (j + km1 * oe_dim2) *
			 oe_dim1] + onw[i__ + (jm1 + km1 * onw_dim2) * 
			onw_dim1]) * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1]
			) / (oc[im1 + (j + km1 * oc_dim2) * oc_dim1] - on[im1 
			+ (j + km1 * on_dim2) * on_dim1] - on[im1 + (jm1 + 
			km1 * on_dim2) * on_dim1]);
/* * ******************************************************************** */
/* * *** > dPNE; */
/* * ******************************************************************** */
		dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] = (usw[ip1 + (
			jp1 + km1 * usw_dim2) * usw_dim1] + uw[ip1 + (jp1 + 
			km1 * uw_dim2) * uw_dim1] * opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] + us[ip1 + (jp1 + km1 * us_dim2)
			 * us_dim1] * ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1] + uc[ip1 + (jp1 + km1 * uc_dim2) * uc_dim1] 
			* opne[ii + (jj + kk * opne_dim2) * opne_dim1] + one[
			i__ + (j + km1 * one_dim2) * one_dim1] * dpc[ii + (jj 
			+ kk * dpc_dim2) * dpc_dim1] + oe[i__ + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpn[ii + (jj + kk * dpn_dim2) * 
			dpn_dim1] + on[ip1 + (j + km1 * on_dim2) * on_dim1] * 
			dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1]) / oc[ip1 + 
			(jp1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > dPNW; */
/* * ******************************************************************** */
		dpnw[ii + (jj + kk * dpnw_dim2) * dpnw_dim1] = (use[im1 + (
			jp1 + km1 * use_dim2) * use_dim1] + ue[im1 + (jp1 + 
			km1 * ue_dim2) * ue_dim1] * opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] + us[im1 + (jp1 + km1 * us_dim2)
			 * us_dim1] * opw[ii + (jj + kk * opw_dim2) * 
			opw_dim1] + uc[im1 + (jp1 + km1 * uc_dim2) * uc_dim1] 
			* opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] + onw[
			i__ + (j + km1 * onw_dim2) * onw_dim1] * dpc[ii + (jj 
			+ kk * dpc_dim2) * dpc_dim1] + oe[im1 + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpn[ii + (jj + kk * dpn_dim2) * 
			dpn_dim1] + on[im1 + (j + km1 * on_dim2) * on_dim1] * 
			dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1]) / oc[im1 + 
			(jp1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > dPSE; */
/* * ******************************************************************** */
		dpse[ii + (jj + kk * dpse_dim2) * dpse_dim1] = (unw[ip1 + (
			jm1 + km1 * unw_dim2) * unw_dim1] + uw[ip1 + (jm1 + 
			km1 * uw_dim2) * uw_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] + un[ip1 + (jm1 + km1 * un_dim2)
			 * un_dim1] * ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1] + uc[ip1 + (jm1 + km1 * uc_dim2) * uc_dim1] 
			* opse[ii + (jj + kk * opse_dim2) * opse_dim1] + onw[
			ip1 + (jm1 + km1 * onw_dim2) * onw_dim1] * dpc[ii + (
			jj + kk * dpc_dim2) * dpc_dim1] + oe[i__ + (jm1 + km1 
			* oe_dim2) * oe_dim1] * dps[ii + (jj + kk * dps_dim2) 
			* dps_dim1] + on[ip1 + (jm1 + km1 * on_dim2) * 
			on_dim1] * dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1]) 
			/ oc[ip1 + (jm1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > dPSW; */
/* * ******************************************************************** */
		dpsw[ii + (jj + kk * dpsw_dim2) * dpsw_dim1] = (une[im1 + (
			jm1 + km1 * une_dim2) * une_dim1] + ue[im1 + (jm1 + 
			km1 * ue_dim2) * ue_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] + un[im1 + (jm1 + km1 * un_dim2)
			 * un_dim1] * opw[ii + (jj + kk * opw_dim2) * 
			opw_dim1] + uc[im1 + (jm1 + km1 * uc_dim2) * uc_dim1] 
			* opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] + one[
			im1 + (jm1 + km1 * one_dim2) * one_dim1] * dpc[ii + (
			jj + kk * dpc_dim2) * dpc_dim1] + oe[im1 + (jm1 + km1 
			* oe_dim2) * oe_dim1] * dps[ii + (jj + kk * dps_dim2) 
			* dps_dim1] + on[im1 + (jm1 + km1 * on_dim2) * 
			on_dim1] * dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1]) 
			/ oc[im1 + (jm1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPC; */
/* * ******************************************************************** */
		upc[ii + (jj + kk * upc_dim2) * upc_dim1] = (use[im1 + (jp1 + 
			k * use_dim2) * use_dim1] + ue[im1 + (j + k * ue_dim2)
			 * ue_dim1] + une[im1 + (jm1 + k * une_dim2) * 
			une_dim1] + us[i__ + (jp1 + k * us_dim2) * us_dim1] + 
			uc[i__ + (j + k * uc_dim2) * uc_dim1] + un[i__ + (jm1 
			+ k * un_dim2) * un_dim1] + usw[ip1 + (jp1 + k * 
			usw_dim2) * usw_dim1] + uw[ip1 + (j + k * uw_dim2) * 
			uw_dim1] + unw[ip1 + (jm1 + k * unw_dim2) * unw_dim1])
			 / (oc[i__ + (j + kp1 * oc_dim2) * oc_dim1] - on[i__ 
			+ (j + kp1 * on_dim2) * on_dim1] - on[i__ + (jm1 + 
			kp1 * on_dim2) * on_dim1] - onw[i__ + (j + kp1 * 
			onw_dim2) * onw_dim1] - oe[im1 + (j + kp1 * oe_dim2) *
			 oe_dim1] - one[im1 + (jm1 + kp1 * one_dim2) * 
			one_dim1] - one[i__ + (j + kp1 * one_dim2) * one_dim1]
			 - oe[i__ + (j + kp1 * oe_dim2) * oe_dim1] - onw[ip1 
			+ (jm1 + kp1 * onw_dim2) * onw_dim1]);
/* * ******************************************************************** */
/* * *** > uPN; */
/* * ******************************************************************** */
		upn[ii + (jj + kk * upn_dim2) * upn_dim1] = (une[im1 + (j + k 
			* une_dim2) * une_dim1] + un[i__ + (j + k * un_dim2) *
			 un_dim1] + unw[ip1 + (j + k * unw_dim2) * unw_dim1] 
			+ (one[im1 + (j + kp1 * one_dim2) * one_dim1] + on[
			i__ + (j + kp1 * on_dim2) * on_dim1] + onw[ip1 + (j + 
			kp1 * onw_dim2) * onw_dim1]) * upc[ii + (jj + kk * 
			upc_dim2) * upc_dim1] + (ue[im1 + (jp1 + k * ue_dim2) 
			* ue_dim1] + uc[i__ + (jp1 + k * uc_dim2) * uc_dim1] 
			+ uw[ip1 + (jp1 + k * uw_dim2) * uw_dim1]) * opn[ii + 
			(jj + kk * opn_dim2) * opn_dim1]) / (oc[i__ + (jp1 + 
			kp1 * oc_dim2) * oc_dim1] - oe[im1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] - oe[i__ + (jp1 + kp1 * oe_dim2) *
			 oe_dim1]);
/* * ******************************************************************** */
/* * *** > uPS; */
/* * ******************************************************************** */
		ups[ii + (jj + kk * ups_dim2) * ups_dim1] = (use[im1 + (j + k 
			* use_dim2) * use_dim1] + us[i__ + (j + k * us_dim2) *
			 us_dim1] + usw[ip1 + (j + k * usw_dim2) * usw_dim1] 
			+ (onw[i__ + (jm1 + kp1 * onw_dim2) * onw_dim1] + on[
			i__ + (jm1 + kp1 * on_dim2) * on_dim1] + one[i__ + (
			jm1 + kp1 * one_dim2) * one_dim1]) * upc[ii + (jj + 
			kk * upc_dim2) * upc_dim1] + (ue[im1 + (jm1 + k * 
			ue_dim2) * ue_dim1] + uc[i__ + (jm1 + k * uc_dim2) * 
			uc_dim1] + uw[ip1 + (jm1 + k * uw_dim2) * uw_dim1]) * 
			ops[ii + (jj + kk * ops_dim2) * ops_dim1]) / (oc[i__ 
			+ (jm1 + kp1 * oc_dim2) * oc_dim1] - oe[im1 + (jm1 + 
			kp1 * oe_dim2) * oe_dim1] - oe[i__ + (jm1 + kp1 * 
			oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > uPE; */
/* * ******************************************************************** */
		upe[ii + (jj + kk * upe_dim2) * upe_dim1] = (use[i__ + (jp1 + 
			k * use_dim2) * use_dim1] + us[ip1 + (jp1 + k * 
			us_dim2) * us_dim1] + une[i__ + (jm1 + k * une_dim2) *
			 une_dim1] + (us[ip1 + (jp1 + k * us_dim2) * us_dim1] 
			+ uc[ip1 + (j + k * uc_dim2) * uc_dim1] + un[ip1 + (
			jm1 + k * un_dim2) * un_dim1]) * ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] + (onw[ip1 + (j + kp1 * 
			onw_dim2) * onw_dim1] + oe[i__ + (j + kp1 * oe_dim2) *
			 oe_dim1] + one[i__ + (jm1 + kp1 * one_dim2) * 
			one_dim1]) * upc[ii + (jj + kk * upc_dim2) * upc_dim1]
			) / (oc[ip1 + (j + kp1 * oc_dim2) * oc_dim1] - on[ip1 
			+ (j + kp1 * on_dim2) * on_dim1] - on[ip1 + (jm1 + 
			kp1 * on_dim2) * on_dim1]);
/* * ******************************************************************** */
/* * *** > uPW; */
/* * ******************************************************************** */
		upw[ii + (jj + kk * upw_dim2) * upw_dim1] = (usw[i__ + (jp1 + 
			k * usw_dim2) * usw_dim1] + uw[i__ + (j + k * uw_dim2)
			 * uw_dim1] + unw[i__ + (jm1 + k * unw_dim2) * 
			unw_dim1] + (us[im1 + (jp1 + k * us_dim2) * us_dim1] 
			+ uc[im1 + (j + k * uc_dim2) * uc_dim1] + un[im1 + (
			jm1 + k * un_dim2) * un_dim1]) * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] + (one[im1 + (j + kp1 * 
			one_dim2) * one_dim1] + oe[im1 + (j + kp1 * oe_dim2) *
			 oe_dim1] + onw[i__ + (jm1 + kp1 * onw_dim2) * 
			onw_dim1]) * upc[ii + (jj + kk * upc_dim2) * upc_dim1]
			) / (oc[im1 + (j + kp1 * oc_dim2) * oc_dim1] - on[im1 
			+ (j + kp1 * on_dim2) * on_dim1] - on[im1 + (jm1 + 
			kp1 * on_dim2) * on_dim1]);
/* * ******************************************************************** */
/* * *** > uPNE; */
/* * ******************************************************************** */
		upne[ii + (jj + kk * upne_dim2) * upne_dim1] = (une[i__ + (j 
			+ k * une_dim2) * une_dim1] + ue[i__ + (jp1 + k * 
			ue_dim2) * ue_dim1] * opn[ii + (jj + kk * opn_dim2) * 
			opn_dim1] + un[ip1 + (j + k * un_dim2) * un_dim1] * 
			ope[ii + (jj + kk * ope_dim2) * ope_dim1] + uc[ip1 + (
			jp1 + k * uc_dim2) * uc_dim1] * opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1] + one[i__ + (j + kp1 * 
			one_dim2) * one_dim1] * upc[ii + (jj + kk * upc_dim2) 
			* upc_dim1] + oe[i__ + (jp1 + kp1 * oe_dim2) * 
			oe_dim1] * upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			+ on[ip1 + (j + kp1 * on_dim2) * on_dim1] * upe[ii + (
			jj + kk * upe_dim2) * upe_dim1]) / oc[ip1 + (jp1 + 
			kp1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPNW; */
/* * ******************************************************************** */
		upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] = (unw[i__ + (j 
			+ k * unw_dim2) * unw_dim1] + uw[i__ + (jp1 + k * 
			uw_dim2) * uw_dim1] * opn[ii + (jj + kk * opn_dim2) * 
			opn_dim1] + un[im1 + (j + k * un_dim2) * un_dim1] * 
			opw[ii + (jj + kk * opw_dim2) * opw_dim1] + uc[im1 + (
			jp1 + k * uc_dim2) * uc_dim1] * opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] + onw[i__ + (j + kp1 * 
			onw_dim2) * onw_dim1] * upc[ii + (jj + kk * upc_dim2) 
			* upc_dim1] + oe[im1 + (jp1 + kp1 * oe_dim2) * 
			oe_dim1] * upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			+ on[im1 + (j + kp1 * on_dim2) * on_dim1] * upw[ii + (
			jj + kk * upw_dim2) * upw_dim1]) / oc[im1 + (jp1 + 
			kp1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPSE; */
/* * ******************************************************************** */
		upse[ii + (jj + kk * upse_dim2) * upse_dim1] = (use[i__ + (j 
			+ k * use_dim2) * use_dim1] + ue[i__ + (jm1 + k * 
			ue_dim2) * ue_dim1] * ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1] + us[ip1 + (j + k * us_dim2) * us_dim1] * 
			ope[ii + (jj + kk * ope_dim2) * ope_dim1] + uc[ip1 + (
			jm1 + k * uc_dim2) * uc_dim1] * opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] + onw[ip1 + (jm1 + kp1 * 
			onw_dim2) * onw_dim1] * upc[ii + (jj + kk * upc_dim2) 
			* upc_dim1] + oe[i__ + (jm1 + kp1 * oe_dim2) * 
			oe_dim1] * ups[ii + (jj + kk * ups_dim2) * ups_dim1] 
			+ on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1] * upe[ii 
			+ (jj + kk * upe_dim2) * upe_dim1]) / oc[ip1 + (jm1 + 
			kp1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPSW; */
/* * ******************************************************************** */
		upsw[ii + (jj + kk * upsw_dim2) * upsw_dim1] = (usw[i__ + (j 
			+ k * usw_dim2) * usw_dim1] + uw[i__ + (jm1 + k * 
			uw_dim2) * uw_dim1] * ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1] + us[im1 + (j + k * us_dim2) * us_dim1] * 
			opw[ii + (jj + kk * opw_dim2) * opw_dim1] + uc[im1 + (
			jm1 + k * uc_dim2) * uc_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] + one[im1 + (jm1 + kp1 * 
			one_dim2) * one_dim1] * upc[ii + (jj + kk * upc_dim2) 
			* upc_dim1] + oe[im1 + (jm1 + kp1 * oe_dim2) * 
			oe_dim1] * ups[ii + (jj + kk * ups_dim2) * ups_dim1] 
			+ on[im1 + (jm1 + kp1 * on_dim2) * on_dim1] * upw[ii 
			+ (jj + kk * upw_dim2) * upw_dim1]) / oc[im1 + (jm1 + 
			kp1 * oc_dim2) * oc_dim1];
/* *             *** main loop *** */
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildpb_op27__ */

/* Subroutine */ int buildp_modop7__(integer *nxf, integer *nyf, integer *nzf,
	 integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *
	rpc, doublereal *ac, doublereal *pc)
{
    /* System generated locals */
    integer ac_dim1, ac_offset, pc_dim1, pc_offset;

    /* Local variables */
    extern /* Subroutine */ int buildpb_modop7__(integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
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
/* *    a modified 7-pt operator-based prologation. */
/* * */
/* *    call the routine to form the prolongation operator from a */
/* *    7 diagonal fine grid matrix. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the build routine *** */
    /* Parameter adjustments */
    ac_dim1 = *nxf * *nyf * *nzf;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    pc_dim1 = *nxc * *nyc * *nzc;
    pc_offset = 1 + pc_dim1;
    pc -= pc_offset;
    --ipc;
    --rpc;

    /* Function Body */
    buildpb_modop7__(nxf, nyf, nzf, nxc, nyc, nzc, &ipc[1], &rpc[1], &ac[
	    ac_dim1 + 1], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(
	    ac_dim1 << 2) + 1], &pc[pc_dim1 + 1], &pc[(pc_dim1 << 1) + 1], &
	    pc[pc_dim1 * 3 + 1], &pc[(pc_dim1 << 2) + 1], &pc[pc_dim1 * 5 + 1]
	    , &pc[pc_dim1 * 6 + 1], &pc[pc_dim1 * 7 + 1], &pc[(pc_dim1 << 3) 
	    + 1], &pc[pc_dim1 * 9 + 1], &pc[pc_dim1 * 10 + 1], &pc[pc_dim1 * 
	    11 + 1], &pc[pc_dim1 * 12 + 1], &pc[pc_dim1 * 13 + 1], &pc[
	    pc_dim1 * 14 + 1], &pc[pc_dim1 * 15 + 1], &pc[(pc_dim1 << 4) + 1],
	     &pc[pc_dim1 * 17 + 1], &pc[pc_dim1 * 18 + 1], &pc[pc_dim1 * 19 + 
	    1], &pc[pc_dim1 * 20 + 1], &pc[pc_dim1 * 21 + 1], &pc[pc_dim1 * 
	    22 + 1], &pc[pc_dim1 * 23 + 1], &pc[pc_dim1 * 24 + 1], &pc[
	    pc_dim1 * 25 + 1], &pc[pc_dim1 * 26 + 1], &pc[pc_dim1 * 27 + 1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildp_modop7__ */

/* Subroutine */ int buildpb_modop7__(integer *nxf, integer *nyf, integer *
	nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, 
	doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, 
	doublereal *uc, doublereal *opc, doublereal *opn, doublereal *ops, 
	doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, 
	doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, 
	doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, 
	doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc,
	 doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, 
	doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *
	dpsw)
{
    /* System generated locals */
    integer oc_dim1, oc_dim2, oc_offset, oe_dim1, oe_dim2, oe_offset, on_dim1,
	     on_dim2, on_offset, uc_dim1, uc_dim2, uc_offset, opc_dim1, 
	    opc_dim2, opc_offset, opn_dim1, opn_dim2, opn_offset, ops_dim1, 
	    ops_dim2, ops_offset, ope_dim1, ope_dim2, ope_offset, opw_dim1, 
	    opw_dim2, opw_offset, opne_dim1, opne_dim2, opne_offset, 
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
    doublereal d__1, d__2, d__3, d__4, d__5, d__6;

    /* Local variables */
    static doublereal ocim1jm1k, ocim1jkm1, ocijm1km1, ocip1jm1k, ocim1jp1k, 
	    ocip1jkm1, ocip1jp1k, ocijp1km1, ocim1jkp1, ocip1jkp1, ocijm1kp1, 
	    ocijp1kp1;
    static integer i__, j, k;
    static doublereal ocim1jm1km1, ocip1jm1km1, ocim1jp1km1, ocim1jm1kp1, 
	    ocip1jp1km1, ocip1jm1kp1, ocim1jp1kp1, ocip1jp1kp1;
    static integer ii, jj, kk, im1, im2, jm1, ip1, ip2, jp1, jm2, jp2, km1, 
	    kp1, km2, kp2;
    static doublereal won;
    static integer iim1, jjm1, iip1, kkm1, jjp1, kkp1;
    static doublereal half, ocijk, eighth, ocim1jk, ocijm1k, ocijkm1, ocip1jk,
	     ocijp1k, ocijkp1, quarter;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    a modified 7-pt operator-based prologation. */
/* * */
/* *    form the prolongation operator from a 7 diagonal fine grid matrix. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** interpolation stencil *** */
    /* Parameter adjustments */
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
    --ipc;
    --rpc;

    /* Function Body */
    won = 1.;
    half = .5;
    quarter = .25;
    eighth = .125;
    i__1 = *nzc - 1;
    for (kk = 2; kk <= i__1; ++kk) {
	k = (kk << 1) - 1;
	i__2 = *nyc - 1;
	for (jj = 2; jj <= i__2; ++jj) {
	    j = (jj << 1) - 1;
	    i__3 = *nxc - 1;
	    for (ii = 2; ii <= i__3; ++ii) {
		i__ = (ii << 1) - 1;
/* * */
/* *             *** index computations *** */
		im1 = i__ - 1;
		ip1 = i__ + 1;
		im2 = i__ - 2;
		ip2 = i__ + 2;
		jm1 = j - 1;
		jp1 = j + 1;
		jm2 = j - 2;
		jp2 = j + 2;
		km1 = k - 1;
		kp1 = k + 1;
		km2 = k - 2;
		kp2 = k + 2;
		iim1 = ii - 1;
		iip1 = ii + 1;
		jjm1 = jj - 1;
		jjp1 = jj + 1;
		kkm1 = kk - 1;
		kkp1 = kk + 1;
/* * */
/* *             *** fix the operator *** */
		ocijk = (d__1 = oe[im1 + (j + k * oe_dim2) * oe_dim1], abs(
			d__1)) + (d__2 = oe[i__ + (j + k * oe_dim2) * oe_dim1]
			, abs(d__2)) + (d__3 = on[i__ + (jm1 + k * on_dim2) * 
			on_dim1], abs(d__3)) + (d__4 = on[i__ + (j + k * 
			on_dim2) * on_dim1], abs(d__4)) + (d__5 = uc[i__ + (j 
			+ km1 * uc_dim2) * uc_dim1], abs(d__5)) + (d__6 = uc[
			i__ + (j + k * uc_dim2) * uc_dim1], abs(d__6));
		ocijp1k = (d__1 = oe[im1 + (jp1 + k * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[i__ + (jp1 + k * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[i__ + (j + k * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[i__ + (
			jp1 + k * on_dim2) * on_dim1], abs(d__4)) + (d__5 = 
			uc[i__ + (jp1 + km1 * uc_dim2) * uc_dim1], abs(d__5)) 
			+ (d__6 = uc[i__ + (jp1 + k * uc_dim2) * uc_dim1], 
			abs(d__6));
		ocijm1k = (d__1 = oe[im1 + (jm1 + k * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[i__ + (jm1 + k * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[i__ + (jm2 + k * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[i__ + (
			jm1 + k * on_dim2) * on_dim1], abs(d__4)) + (d__5 = 
			uc[i__ + (jm1 + km1 * uc_dim2) * uc_dim1], abs(d__5)) 
			+ (d__6 = uc[i__ + (jm1 + k * uc_dim2) * uc_dim1], 
			abs(d__6));
		ocip1jk = (d__1 = oe[i__ + (j + k * oe_dim2) * oe_dim1], abs(
			d__1)) + (d__2 = oe[ip1 + (j + k * oe_dim2) * oe_dim1]
			, abs(d__2)) + (d__3 = on[ip1 + (jm1 + k * on_dim2) * 
			on_dim1], abs(d__3)) + (d__4 = on[ip1 + (j + k * 
			on_dim2) * on_dim1], abs(d__4)) + (d__5 = uc[ip1 + (j 
			+ km1 * uc_dim2) * uc_dim1], abs(d__5)) + (d__6 = uc[
			ip1 + (j + k * uc_dim2) * uc_dim1], abs(d__6));
		ocim1jk = (d__1 = oe[im2 + (j + k * oe_dim2) * oe_dim1], abs(
			d__1)) + (d__2 = oe[im1 + (j + k * oe_dim2) * oe_dim1]
			, abs(d__2)) + (d__3 = on[im1 + (jm1 + k * on_dim2) * 
			on_dim1], abs(d__3)) + (d__4 = on[im1 + (j + k * 
			on_dim2) * on_dim1], abs(d__4)) + (d__5 = uc[im1 + (j 
			+ km1 * uc_dim2) * uc_dim1], abs(d__5)) + (d__6 = uc[
			im1 + (j + k * uc_dim2) * uc_dim1], abs(d__6));
		ocip1jp1k = (d__1 = oe[i__ + (jp1 + k * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[ip1 + (jp1 + k * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[ip1 + (j + k * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[ip1 + (
			jp1 + k * on_dim2) * on_dim1], abs(d__4)) + (d__5 = 
			uc[ip1 + (jp1 + km1 * uc_dim2) * uc_dim1], abs(d__5)) 
			+ (d__6 = uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1], 
			abs(d__6));
		ocim1jp1k = (d__1 = oe[im1 + (jp1 + k * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[i__ + (jp1 + k * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[i__ + (j + k * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[i__ + (
			jp1 + k * on_dim2) * on_dim1], abs(d__4)) + (d__5 = 
			uc[i__ + (jp1 + km1 * uc_dim2) * uc_dim1], abs(d__5)) 
			+ (d__6 = uc[i__ + (jp1 + k * uc_dim2) * uc_dim1], 
			abs(d__6));
		ocip1jm1k = (d__1 = oe[i__ + (jm1 + k * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[ip1 + (jm1 + k * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[ip1 + (jm2 + k * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[ip1 + (
			jm1 + k * on_dim2) * on_dim1], abs(d__4)) + (d__5 = 
			uc[ip1 + (jm1 + km1 * uc_dim2) * uc_dim1], abs(d__5)) 
			+ (d__6 = uc[ip1 + (jm1 + k * uc_dim2) * uc_dim1], 
			abs(d__6));
		ocim1jm1k = (d__1 = oe[im1 + (jm1 + k * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[i__ + (jm1 + k * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[i__ + (jm2 + k * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[i__ + (
			jm1 + k * on_dim2) * on_dim1], abs(d__4)) + (d__5 = 
			uc[i__ + (jm1 + km1 * uc_dim2) * uc_dim1], abs(d__5)) 
			+ (d__6 = uc[i__ + (jm1 + k * uc_dim2) * uc_dim1], 
			abs(d__6));
/* * ******************************************************************** */
		ocijkm1 = (d__1 = oe[im1 + (j + km1 * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[i__ + (j + km1 * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[i__ + (jm1 + km1 * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[i__ + (j 
			+ km1 * on_dim2) * on_dim1], abs(d__4)) + (d__5 = uc[
			i__ + (j + km2 * uc_dim2) * uc_dim1], abs(d__5)) + (
			d__6 = uc[i__ + (j + km1 * uc_dim2) * uc_dim1], abs(
			d__6));
		ocijp1km1 = (d__1 = oe[im1 + (jp1 + km1 * oe_dim2) * oe_dim1],
			 abs(d__1)) + (d__2 = oe[i__ + (jp1 + km1 * oe_dim2) *
			 oe_dim1], abs(d__2)) + (d__3 = on[i__ + (j + km1 * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[i__ + (
			jp1 + km1 * on_dim2) * on_dim1], abs(d__4)) + (d__5 = 
			uc[i__ + (jp1 + km2 * uc_dim2) * uc_dim1], abs(d__5)) 
			+ (d__6 = uc[i__ + (jp1 + km1 * uc_dim2) * uc_dim1], 
			abs(d__6));
		ocijm1km1 = (d__1 = oe[im1 + (jm1 + km1 * oe_dim2) * oe_dim1],
			 abs(d__1)) + (d__2 = oe[i__ + (jm1 + km1 * oe_dim2) *
			 oe_dim1], abs(d__2)) + (d__3 = on[i__ + (jm2 + km1 * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[i__ + (
			jm1 + km1 * on_dim2) * on_dim1], abs(d__4)) + (d__5 = 
			uc[i__ + (jm1 + km2 * uc_dim2) * uc_dim1], abs(d__5)) 
			+ (d__6 = uc[i__ + (jm1 + km1 * uc_dim2) * uc_dim1], 
			abs(d__6));
		ocip1jkm1 = (d__1 = oe[i__ + (j + km1 * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[ip1 + (j + km1 * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[ip1 + (jm1 + km1 * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[ip1 + (j 
			+ km1 * on_dim2) * on_dim1], abs(d__4)) + (d__5 = uc[
			ip1 + (j + km2 * uc_dim2) * uc_dim1], abs(d__5)) + (
			d__6 = uc[ip1 + (j + km1 * uc_dim2) * uc_dim1], abs(
			d__6));
		ocim1jkm1 = (d__1 = oe[im2 + (j + km1 * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[im1 + (j + km1 * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[im1 + (jm1 + km1 * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[im1 + (j 
			+ km1 * on_dim2) * on_dim1], abs(d__4)) + (d__5 = uc[
			im1 + (j + km2 * uc_dim2) * uc_dim1], abs(d__5)) + (
			d__6 = uc[im1 + (j + km1 * uc_dim2) * uc_dim1], abs(
			d__6));
		ocip1jp1km1 = (d__1 = oe[i__ + (jp1 + km1 * oe_dim2) * 
			oe_dim1], abs(d__1)) + (d__2 = oe[ip1 + (jp1 + km1 * 
			oe_dim2) * oe_dim1], abs(d__2)) + (d__3 = on[ip1 + (j 
			+ km1 * on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[
			ip1 + (jp1 + km1 * on_dim2) * on_dim1], abs(d__4)) + (
			d__5 = uc[ip1 + (jp1 + km2 * uc_dim2) * uc_dim1], abs(
			d__5)) + (d__6 = uc[ip1 + (jp1 + km1 * uc_dim2) * 
			uc_dim1], abs(d__6));
		ocim1jp1km1 = (d__1 = oe[im1 + (jp1 + km1 * oe_dim2) * 
			oe_dim1], abs(d__1)) + (d__2 = oe[i__ + (jp1 + km1 * 
			oe_dim2) * oe_dim1], abs(d__2)) + (d__3 = on[i__ + (j 
			+ km1 * on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[
			i__ + (jp1 + km1 * on_dim2) * on_dim1], abs(d__4)) + (
			d__5 = uc[i__ + (jp1 + km2 * uc_dim2) * uc_dim1], abs(
			d__5)) + (d__6 = uc[i__ + (jp1 + km1 * uc_dim2) * 
			uc_dim1], abs(d__6));
		ocip1jm1km1 = (d__1 = oe[i__ + (jm1 + km1 * oe_dim2) * 
			oe_dim1], abs(d__1)) + (d__2 = oe[ip1 + (jm1 + km1 * 
			oe_dim2) * oe_dim1], abs(d__2)) + (d__3 = on[ip1 + (
			jm2 + km1 * on_dim2) * on_dim1], abs(d__3)) + (d__4 = 
			on[ip1 + (jm1 + km1 * on_dim2) * on_dim1], abs(d__4)) 
			+ (d__5 = uc[ip1 + (jm1 + km2 * uc_dim2) * uc_dim1], 
			abs(d__5)) + (d__6 = uc[ip1 + (jm1 + km1 * uc_dim2) * 
			uc_dim1], abs(d__6));
		ocim1jm1km1 = (d__1 = oe[im1 + (jm1 + km1 * oe_dim2) * 
			oe_dim1], abs(d__1)) + (d__2 = oe[i__ + (jm1 + km1 * 
			oe_dim2) * oe_dim1], abs(d__2)) + (d__3 = on[i__ + (
			jm2 + km1 * on_dim2) * on_dim1], abs(d__3)) + (d__4 = 
			on[i__ + (jm1 + km1 * on_dim2) * on_dim1], abs(d__4)) 
			+ (d__5 = uc[i__ + (jm1 + km2 * uc_dim2) * uc_dim1], 
			abs(d__5)) + (d__6 = uc[i__ + (jm1 + km1 * uc_dim2) * 
			uc_dim1], abs(d__6));
/* * ******************************************************************** */
		ocijkp1 = (d__1 = oe[im1 + (j + kp1 * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[i__ + (j + kp1 * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[i__ + (jm1 + kp1 * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[i__ + (j 
			+ kp1 * on_dim2) * on_dim1], abs(d__4)) + (d__5 = uc[
			i__ + (j + k * uc_dim2) * uc_dim1], abs(d__5)) + (
			d__6 = uc[i__ + (j + kp1 * uc_dim2) * uc_dim1], abs(
			d__6));
		ocijp1kp1 = (d__1 = oe[im1 + (jp1 + kp1 * oe_dim2) * oe_dim1],
			 abs(d__1)) + (d__2 = oe[i__ + (jp1 + kp1 * oe_dim2) *
			 oe_dim1], abs(d__2)) + (d__3 = on[i__ + (j + kp1 * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[i__ + (
			jp1 + kp1 * on_dim2) * on_dim1], abs(d__4)) + (d__5 = 
			uc[i__ + (jp1 + k * uc_dim2) * uc_dim1], abs(d__5)) + 
			(d__6 = uc[i__ + (jp1 + kp1 * uc_dim2) * uc_dim1], 
			abs(d__6));
		ocijm1kp1 = (d__1 = oe[im1 + (jm1 + kp1 * oe_dim2) * oe_dim1],
			 abs(d__1)) + (d__2 = oe[i__ + (jm1 + kp1 * oe_dim2) *
			 oe_dim1], abs(d__2)) + (d__3 = on[i__ + (jm2 + kp1 * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[i__ + (
			jm1 + kp1 * on_dim2) * on_dim1], abs(d__4)) + (d__5 = 
			uc[i__ + (jm1 + k * uc_dim2) * uc_dim1], abs(d__5)) + 
			(d__6 = uc[i__ + (jm1 + kp1 * uc_dim2) * uc_dim1], 
			abs(d__6));
		ocip1jkp1 = (d__1 = oe[i__ + (j + kp1 * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[ip1 + (j + kp1 * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[ip1 + (jm1 + kp1 * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[ip1 + (j 
			+ kp1 * on_dim2) * on_dim1], abs(d__4)) + (d__5 = uc[
			ip1 + (j + k * uc_dim2) * uc_dim1], abs(d__5)) + (
			d__6 = uc[ip1 + (j + kp1 * uc_dim2) * uc_dim1], abs(
			d__6));
		ocim1jkp1 = (d__1 = oe[im2 + (j + kp1 * oe_dim2) * oe_dim1], 
			abs(d__1)) + (d__2 = oe[im1 + (j + kp1 * oe_dim2) * 
			oe_dim1], abs(d__2)) + (d__3 = on[im1 + (jm1 + kp1 * 
			on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[im1 + (j 
			+ kp1 * on_dim2) * on_dim1], abs(d__4)) + (d__5 = uc[
			im1 + (j + k * uc_dim2) * uc_dim1], abs(d__5)) + (
			d__6 = uc[im1 + (j + kp1 * uc_dim2) * uc_dim1], abs(
			d__6));
		ocip1jp1kp1 = (d__1 = oe[i__ + (jp1 + kp1 * oe_dim2) * 
			oe_dim1], abs(d__1)) + (d__2 = oe[ip1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1], abs(d__2)) + (d__3 = on[ip1 + (j 
			+ kp1 * on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[
			ip1 + (jp1 + kp1 * on_dim2) * on_dim1], abs(d__4)) + (
			d__5 = uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1], abs(
			d__5)) + (d__6 = uc[ip1 + (jp1 + kp1 * uc_dim2) * 
			uc_dim1], abs(d__6));
		ocim1jp1kp1 = (d__1 = oe[im1 + (jp1 + kp1 * oe_dim2) * 
			oe_dim1], abs(d__1)) + (d__2 = oe[i__ + (jp1 + kp1 * 
			oe_dim2) * oe_dim1], abs(d__2)) + (d__3 = on[i__ + (j 
			+ kp1 * on_dim2) * on_dim1], abs(d__3)) + (d__4 = on[
			i__ + (jp1 + kp1 * on_dim2) * on_dim1], abs(d__4)) + (
			d__5 = uc[i__ + (jp1 + k * uc_dim2) * uc_dim1], abs(
			d__5)) + (d__6 = uc[i__ + (jp1 + kp1 * uc_dim2) * 
			uc_dim1], abs(d__6));
		ocip1jm1kp1 = (d__1 = oe[i__ + (jm1 + kp1 * oe_dim2) * 
			oe_dim1], abs(d__1)) + (d__2 = oe[ip1 + (jm1 + kp1 * 
			oe_dim2) * oe_dim1], abs(d__2)) + (d__3 = on[ip1 + (
			jm2 + kp1 * on_dim2) * on_dim1], abs(d__3)) + (d__4 = 
			on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1], abs(d__4)) 
			+ (d__5 = uc[ip1 + (jm1 + k * uc_dim2) * uc_dim1], 
			abs(d__5)) + (d__6 = uc[ip1 + (jm1 + kp1 * uc_dim2) * 
			uc_dim1], abs(d__6));
		ocim1jm1kp1 = (d__1 = oe[im1 + (jm1 + kp1 * oe_dim2) * 
			oe_dim1], abs(d__1)) + (d__2 = oe[i__ + (jm1 + kp1 * 
			oe_dim2) * oe_dim1], abs(d__2)) + (d__3 = on[i__ + (
			jm2 + kp1 * on_dim2) * on_dim1], abs(d__3)) + (d__4 = 
			on[i__ + (jm1 + kp1 * on_dim2) * on_dim1], abs(d__4)) 
			+ (d__5 = uc[i__ + (jm1 + k * uc_dim2) * uc_dim1], 
			abs(d__5)) + (d__6 = uc[i__ + (jm1 + kp1 * uc_dim2) * 
			uc_dim1], abs(d__6));
/* * ******************************************************************** */
/* * *** > oPC; */
/* * ******************************************************************** */
		opc[ii + (jj + kk * opc_dim2) * opc_dim1] = won;
/* * ******************************************************************** */
/* * *** > oPN; */
/* * ******************************************************************** */
		opn[ii + (jj + kk * opn_dim2) * opn_dim1] = (d__5 = on[i__ + (
			j + k * on_dim2) * on_dim1], abs(d__5)) / (ocijp1k - (
			d__1 = oe[im1 + (jp1 + k * oe_dim2) * oe_dim1], abs(
			d__1)) - (d__2 = oe[i__ + (jp1 + k * oe_dim2) * 
			oe_dim1], abs(d__2)) - (d__3 = uc[i__ + (jp1 + km1 * 
			uc_dim2) * uc_dim1], abs(d__3)) - (d__4 = uc[i__ + (
			jp1 + k * uc_dim2) * uc_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > oPS; */
/* * ******************************************************************** */
		ops[ii + (jj + kk * ops_dim2) * ops_dim1] = (d__5 = on[i__ + (
			jm1 + k * on_dim2) * on_dim1], abs(d__5)) / (ocijm1k 
			- (d__1 = oe[im1 + (jm1 + k * oe_dim2) * oe_dim1], 
			abs(d__1)) - (d__2 = oe[i__ + (jm1 + k * oe_dim2) * 
			oe_dim1], abs(d__2)) - (d__3 = uc[i__ + (jm1 + km1 * 
			uc_dim2) * uc_dim1], abs(d__3)) - (d__4 = uc[i__ + (
			jm1 + k * uc_dim2) * uc_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > oPE; */
/* * ******************************************************************** */
		ope[ii + (jj + kk * ope_dim2) * ope_dim1] = (d__5 = oe[i__ + (
			j + k * oe_dim2) * oe_dim1], abs(d__5)) / (ocip1jk - (
			d__1 = uc[ip1 + (j + km1 * uc_dim2) * uc_dim1], abs(
			d__1)) - (d__2 = uc[ip1 + (j + k * uc_dim2) * uc_dim1]
			, abs(d__2)) - (d__3 = on[ip1 + (j + k * on_dim2) * 
			on_dim1], abs(d__3)) - (d__4 = on[ip1 + (jm1 + k * 
			on_dim2) * on_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > oPW; */
/* * ******************************************************************** */
		opw[ii + (jj + kk * opw_dim2) * opw_dim1] = (d__5 = oe[im1 + (
			j + k * oe_dim2) * oe_dim1], abs(d__5)) / (ocim1jk - (
			d__1 = uc[im1 + (j + km1 * uc_dim2) * uc_dim1], abs(
			d__1)) - (d__2 = uc[im1 + (j + k * uc_dim2) * uc_dim1]
			, abs(d__2)) - (d__3 = on[im1 + (j + k * on_dim2) * 
			on_dim1], abs(d__3)) - (d__4 = on[im1 + (jm1 + k * 
			on_dim2) * on_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > oPNE; */
/* * ******************************************************************** */
		opne[ii + (jj + kk * opne_dim2) * opne_dim1] = ((d__1 = on[
			ip1 + (j + k * on_dim2) * on_dim1], abs(d__1)) * ope[
			ii + (jj + kk * ope_dim2) * ope_dim1] + (d__2 = oe[
			i__ + (jp1 + k * oe_dim2) * oe_dim1], abs(d__2)) * 
			opn[ii + (jj + kk * opn_dim2) * opn_dim1]) / (
			ocip1jp1k - (d__3 = uc[ip1 + (jp1 + km1 * uc_dim2) * 
			uc_dim1], abs(d__3)) - (d__4 = uc[ip1 + (jp1 + k * 
			uc_dim2) * uc_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > oPNW; */
/* * ******************************************************************** */
		opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] = ((d__1 = on[
			im1 + (j + k * on_dim2) * on_dim1], abs(d__1)) * opw[
			ii + (jj + kk * opw_dim2) * opw_dim1] + (d__2 = oe[
			im1 + (jp1 + k * oe_dim2) * oe_dim1], abs(d__2)) * 
			opn[ii + (jj + kk * opn_dim2) * opn_dim1]) / (
			ocim1jp1k - (d__3 = uc[im1 + (jp1 + km1 * uc_dim2) * 
			uc_dim1], abs(d__3)) - (d__4 = uc[im1 + (jp1 + k * 
			uc_dim2) * uc_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > oPSE; */
/* * ******************************************************************** */
		opse[ii + (jj + kk * opse_dim2) * opse_dim1] = ((d__1 = on[
			ip1 + (jm1 + k * on_dim2) * on_dim1], abs(d__1)) * 
			ope[ii + (jj + kk * ope_dim2) * ope_dim1] + (d__2 = 
			oe[i__ + (jm1 + k * oe_dim2) * oe_dim1], abs(d__2)) * 
			ops[ii + (jj + kk * ops_dim2) * ops_dim1]) / (
			ocip1jm1k - (d__3 = uc[ip1 + (jm1 + km1 * uc_dim2) * 
			uc_dim1], abs(d__3)) - (d__4 = uc[ip1 + (jm1 + k * 
			uc_dim2) * uc_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > oPSW; */
/* * ******************************************************************** */
		opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] = ((d__1 = on[
			im1 + (jm1 + k * on_dim2) * on_dim1], abs(d__1)) * 
			opw[ii + (jj + kk * opw_dim2) * opw_dim1] + (d__2 = 
			oe[im1 + (jm1 + k * oe_dim2) * oe_dim1], abs(d__2)) * 
			ops[ii + (jj + kk * ops_dim2) * ops_dim1]) / (
			ocim1jm1k - (d__3 = uc[im1 + (jm1 + km1 * uc_dim2) * 
			uc_dim1], abs(d__3)) - (d__4 = uc[im1 + (jm1 + k * 
			uc_dim2) * uc_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > dPC; */
/* * ******************************************************************** */
		dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] = (d__5 = uc[i__ + (
			j + km1 * uc_dim2) * uc_dim1], abs(d__5)) / (ocijkm1 
			- (d__1 = on[i__ + (j + km1 * on_dim2) * on_dim1], 
			abs(d__1)) - (d__2 = on[i__ + (jm1 + km1 * on_dim2) * 
			on_dim1], abs(d__2)) - (d__3 = oe[im1 + (j + km1 * 
			oe_dim2) * oe_dim1], abs(d__3)) - (d__4 = oe[i__ + (j 
			+ km1 * oe_dim2) * oe_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > dPN; */
/* * ******************************************************************** */
		dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] = ((d__1 = on[i__ + 
			(j + km1 * on_dim2) * on_dim1], abs(d__1)) * dpc[ii + 
			(jj + kk * dpc_dim2) * dpc_dim1] + (d__2 = uc[i__ + (
			jp1 + km1 * uc_dim2) * uc_dim1], abs(d__2)) * opn[ii 
			+ (jj + kk * opn_dim2) * opn_dim1]) / (ocijp1km1 - (
			d__3 = oe[im1 + (jp1 + km1 * oe_dim2) * oe_dim1], abs(
			d__3)) - (d__4 = oe[i__ + (jp1 + km1 * oe_dim2) * 
			oe_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > dPS; */
/* * ******************************************************************** */
		dps[ii + (jj + kk * dps_dim2) * dps_dim1] = ((d__1 = on[i__ + 
			(jm1 + km1 * on_dim2) * on_dim1], abs(d__1)) * dpc[ii 
			+ (jj + kk * dpc_dim2) * dpc_dim1] + (d__2 = uc[i__ + 
			(jm1 + km1 * uc_dim2) * uc_dim1], abs(d__2)) * ops[ii 
			+ (jj + kk * ops_dim2) * ops_dim1]) / (ocijm1km1 - (
			d__3 = oe[im1 + (jm1 + km1 * oe_dim2) * oe_dim1], abs(
			d__3)) - (d__4 = oe[i__ + (jm1 + km1 * oe_dim2) * 
			oe_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > dPE; */
/* * ******************************************************************** */
		dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] = ((d__1 = uc[ip1 + 
			(j + km1 * uc_dim2) * uc_dim1], abs(d__1)) * ope[ii + 
			(jj + kk * ope_dim2) * ope_dim1] + (d__2 = oe[i__ + (
			j + km1 * oe_dim2) * oe_dim1], abs(d__2)) * dpc[ii + (
			jj + kk * dpc_dim2) * dpc_dim1]) / (ocip1jkm1 - (d__3 
			= on[ip1 + (j + km1 * on_dim2) * on_dim1], abs(d__3)) 
			- (d__4 = on[ip1 + (jm1 + km1 * on_dim2) * on_dim1], 
			abs(d__4)));
/* * ******************************************************************** */
/* * *** > dPW; */
/* * ******************************************************************** */
		dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] = ((d__1 = uc[im1 + 
			(j + km1 * uc_dim2) * uc_dim1], abs(d__1)) * opw[ii + 
			(jj + kk * opw_dim2) * opw_dim1] + (d__2 = oe[im1 + (
			j + km1 * oe_dim2) * oe_dim1], abs(d__2)) * dpc[ii + (
			jj + kk * dpc_dim2) * dpc_dim1]) / (ocim1jkm1 - (d__3 
			= on[im1 + (j + km1 * on_dim2) * on_dim1], abs(d__3)) 
			- (d__4 = on[im1 + (jm1 + km1 * on_dim2) * on_dim1], 
			abs(d__4)));
/* * ******************************************************************** */
/* * *** > dPNE; */
/* * ******************************************************************** */
		dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] = ((d__1 = uc[
			ip1 + (jp1 + km1 * uc_dim2) * uc_dim1], abs(d__1)) * 
			opne[ii + (jj + kk * opne_dim2) * opne_dim1] + (d__2 =
			 oe[i__ + (jp1 + km1 * oe_dim2) * oe_dim1], abs(d__2))
			 * dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] + (d__3 =
			 on[ip1 + (j + km1 * on_dim2) * on_dim1], abs(d__3)) *
			 dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1]) / 
			ocip1jp1km1;
/* * ******************************************************************** */
/* * *** > dPNW; */
/* * ******************************************************************** */
		dpnw[ii + (jj + kk * dpnw_dim2) * dpnw_dim1] = ((d__1 = uc[
			im1 + (jp1 + km1 * uc_dim2) * uc_dim1], abs(d__1)) * 
			opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] + (d__2 =
			 oe[im1 + (jp1 + km1 * oe_dim2) * oe_dim1], abs(d__2))
			 * dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] + (d__3 =
			 on[im1 + (j + km1 * on_dim2) * on_dim1], abs(d__3)) *
			 dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1]) / 
			ocim1jp1km1;
/* * ******************************************************************** */
/* * *** > dPSE; */
/* * ******************************************************************** */
		dpse[ii + (jj + kk * dpse_dim2) * dpse_dim1] = ((d__1 = uc[
			ip1 + (jm1 + km1 * uc_dim2) * uc_dim1], abs(d__1)) * 
			opse[ii + (jj + kk * opse_dim2) * opse_dim1] + (d__2 =
			 oe[i__ + (jm1 + km1 * oe_dim2) * oe_dim1], abs(d__2))
			 * dps[ii + (jj + kk * dps_dim2) * dps_dim1] + (d__3 =
			 on[ip1 + (jm1 + km1 * on_dim2) * on_dim1], abs(d__3))
			 * dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1]) / 
			ocip1jm1km1;
/* * ******************************************************************** */
/* * *** > dPSW; */
/* * ******************************************************************** */
		dpsw[ii + (jj + kk * dpsw_dim2) * dpsw_dim1] = ((d__1 = uc[
			im1 + (jm1 + km1 * uc_dim2) * uc_dim1], abs(d__1)) * 
			opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] + (d__2 =
			 oe[im1 + (jm1 + km1 * oe_dim2) * oe_dim1], abs(d__2))
			 * dps[ii + (jj + kk * dps_dim2) * dps_dim1] + (d__3 =
			 on[im1 + (jm1 + km1 * on_dim2) * on_dim1], abs(d__3))
			 * dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1]) / 
			ocim1jm1km1;
/* * ******************************************************************** */
/* * *** > uPC; */
/* * ******************************************************************** */
		upc[ii + (jj + kk * upc_dim2) * upc_dim1] = (d__5 = uc[i__ + (
			j + k * uc_dim2) * uc_dim1], abs(d__5)) / (ocijkp1 - (
			d__1 = on[i__ + (j + kp1 * on_dim2) * on_dim1], abs(
			d__1)) - (d__2 = on[i__ + (jm1 + kp1 * on_dim2) * 
			on_dim1], abs(d__2)) - (d__3 = oe[im1 + (j + kp1 * 
			oe_dim2) * oe_dim1], abs(d__3)) - (d__4 = oe[i__ + (j 
			+ kp1 * oe_dim2) * oe_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > uPN; */
/* * ******************************************************************** */
		upn[ii + (jj + kk * upn_dim2) * upn_dim1] = ((d__1 = on[i__ + 
			(j + kp1 * on_dim2) * on_dim1], abs(d__1)) * upc[ii + 
			(jj + kk * upc_dim2) * upc_dim1] + (d__2 = uc[i__ + (
			jp1 + k * uc_dim2) * uc_dim1], abs(d__2)) * opn[ii + (
			jj + kk * opn_dim2) * opn_dim1]) / (ocijp1kp1 - (d__3 
			= oe[im1 + (jp1 + kp1 * oe_dim2) * oe_dim1], abs(d__3)
			) - (d__4 = oe[i__ + (jp1 + kp1 * oe_dim2) * oe_dim1],
			 abs(d__4)));
/* * ******************************************************************** */
/* * *** > uPS; */
/* * ******************************************************************** */
		ups[ii + (jj + kk * ups_dim2) * ups_dim1] = ((d__1 = on[i__ + 
			(jm1 + kp1 * on_dim2) * on_dim1], abs(d__1)) * upc[ii 
			+ (jj + kk * upc_dim2) * upc_dim1] + (d__2 = uc[i__ + 
			(jm1 + k * uc_dim2) * uc_dim1], abs(d__2)) * ops[ii + 
			(jj + kk * ops_dim2) * ops_dim1]) / (ocijm1kp1 - (
			d__3 = oe[im1 + (jm1 + kp1 * oe_dim2) * oe_dim1], abs(
			d__3)) - (d__4 = oe[i__ + (jm1 + kp1 * oe_dim2) * 
			oe_dim1], abs(d__4)));
/* * ******************************************************************** */
/* * *** > uPE; */
/* * ******************************************************************** */
		upe[ii + (jj + kk * upe_dim2) * upe_dim1] = ((d__1 = uc[ip1 + 
			(j + k * uc_dim2) * uc_dim1], abs(d__1)) * ope[ii + (
			jj + kk * ope_dim2) * ope_dim1] + (d__2 = oe[i__ + (j 
			+ kp1 * oe_dim2) * oe_dim1], abs(d__2)) * upc[ii + (
			jj + kk * upc_dim2) * upc_dim1]) / (ocip1jkp1 - (d__3 
			= on[ip1 + (j + kp1 * on_dim2) * on_dim1], abs(d__3)) 
			- (d__4 = on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1], 
			abs(d__4)));
/* * ******************************************************************** */
/* * *** > uPW; */
/* * ******************************************************************** */
		upw[ii + (jj + kk * upw_dim2) * upw_dim1] = ((d__1 = uc[im1 + 
			(j + k * uc_dim2) * uc_dim1], abs(d__1)) * opw[ii + (
			jj + kk * opw_dim2) * opw_dim1] + (d__2 = oe[im1 + (j 
			+ kp1 * oe_dim2) * oe_dim1], abs(d__2)) * upc[ii + (
			jj + kk * upc_dim2) * upc_dim1]) / (ocim1jkp1 - (d__3 
			= on[im1 + (j + kp1 * on_dim2) * on_dim1], abs(d__3)) 
			- (d__4 = on[im1 + (jm1 + kp1 * on_dim2) * on_dim1], 
			abs(d__4)));
/* * ******************************************************************** */
/* * *** > uPNE; */
/* * ******************************************************************** */
		upne[ii + (jj + kk * upne_dim2) * upne_dim1] = ((d__1 = uc[
			ip1 + (jp1 + k * uc_dim2) * uc_dim1], abs(d__1)) * 
			opne[ii + (jj + kk * opne_dim2) * opne_dim1] + (d__2 =
			 oe[i__ + (jp1 + kp1 * oe_dim2) * oe_dim1], abs(d__2))
			 * upn[ii + (jj + kk * upn_dim2) * upn_dim1] + (d__3 =
			 on[ip1 + (j + kp1 * on_dim2) * on_dim1], abs(d__3)) *
			 upe[ii + (jj + kk * upe_dim2) * upe_dim1]) / 
			ocip1jp1kp1;
/* * ******************************************************************** */
/* * *** > uPNW; */
/* * ******************************************************************** */
		upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] = ((d__1 = uc[
			im1 + (jp1 + k * uc_dim2) * uc_dim1], abs(d__1)) * 
			opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] + (d__2 =
			 oe[im1 + (jp1 + kp1 * oe_dim2) * oe_dim1], abs(d__2))
			 * upn[ii + (jj + kk * upn_dim2) * upn_dim1] + (d__3 =
			 on[im1 + (j + kp1 * on_dim2) * on_dim1], abs(d__3)) *
			 upw[ii + (jj + kk * upw_dim2) * upw_dim1]) / 
			ocim1jp1kp1;
/* * ******************************************************************** */
/* * *** > uPSE; */
/* * ******************************************************************** */
		upse[ii + (jj + kk * upse_dim2) * upse_dim1] = ((d__1 = uc[
			ip1 + (jm1 + k * uc_dim2) * uc_dim1], abs(d__1)) * 
			opse[ii + (jj + kk * opse_dim2) * opse_dim1] + (d__2 =
			 oe[i__ + (jm1 + kp1 * oe_dim2) * oe_dim1], abs(d__2))
			 * ups[ii + (jj + kk * ups_dim2) * ups_dim1] + (d__3 =
			 on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1], abs(d__3))
			 * upe[ii + (jj + kk * upe_dim2) * upe_dim1]) / 
			ocip1jm1kp1;
/* * ******************************************************************** */
/* * *** > uPSW; */
/* * ******************************************************************** */
		upsw[ii + (jj + kk * upsw_dim2) * upsw_dim1] = ((d__1 = uc[
			im1 + (jm1 + k * uc_dim2) * uc_dim1], abs(d__1)) * 
			opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] + (d__2 =
			 oe[im1 + (jm1 + kp1 * oe_dim2) * oe_dim1], abs(d__2))
			 * ups[ii + (jj + kk * ups_dim2) * ups_dim1] + (d__3 =
			 on[im1 + (jm1 + kp1 * on_dim2) * on_dim1], abs(d__3))
			 * upw[ii + (jj + kk * upw_dim2) * upw_dim1]) / 
			ocim1jm1kp1;
/* *             *** main loop *** */
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildpb_modop7__ */

/* Subroutine */ int buildp_modop27__(integer *nxf, integer *nyf, integer *
	nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, 
	doublereal *rpc, doublereal *ac, doublereal *pc)
{
    /* System generated locals */
    integer ac_dim1, ac_offset, pc_dim1, pc_offset;

    /* Local variables */
    extern /* Subroutine */ int buildpb_modop27__(integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    a modified 27-pt operator-based prologation. */
/* * */
/* *    call the routine to form the prolongation operator from a */
/* *    27 diagonal fine grid matrix. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the build routine *** */
    /* Parameter adjustments */
    ac_dim1 = *nxf * *nyf * *nzf;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    pc_dim1 = *nxc * *nyc * *nzc;
    pc_offset = 1 + pc_dim1;
    pc -= pc_offset;
    --ipc;
    --rpc;

    /* Function Body */
    buildpb_modop27__(nxf, nyf, nzf, nxc, nyc, nzc, &ipc[1], &rpc[1], &ac[
	    ac_dim1 + 1], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(
	    ac_dim1 << 2) + 1], &ac[ac_dim1 * 5 + 1], &ac[ac_dim1 * 6 + 1], &
	    ac[ac_dim1 * 7 + 1], &ac[(ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1]
	    , &ac[ac_dim1 * 10 + 1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 
	    + 1], &ac[ac_dim1 * 13 + 1], &ac[ac_dim1 * 14 + 1], &pc[pc_dim1 + 
	    1], &pc[(pc_dim1 << 1) + 1], &pc[pc_dim1 * 3 + 1], &pc[(pc_dim1 <<
	     2) + 1], &pc[pc_dim1 * 5 + 1], &pc[pc_dim1 * 6 + 1], &pc[pc_dim1 
	    * 7 + 1], &pc[(pc_dim1 << 3) + 1], &pc[pc_dim1 * 9 + 1], &pc[
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
} /* buildp_modop27__ */

/* Subroutine */ int buildpb_modop27__(integer *nxf, integer *nyf, integer *
	nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, 
	doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, 
	doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, 
	doublereal *uw, doublereal *un, doublereal *us, doublereal *une, 
	doublereal *unw, doublereal *use, doublereal *usw, doublereal *opc, 
	doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, 
	doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *
	opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *
	upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *
	upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *
	dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *
	dpnw, doublereal *dpse, doublereal *dpsw)
{
    /* System generated locals */
    integer oc_dim1, oc_dim2, oc_offset, oe_dim1, oe_dim2, oe_offset, on_dim1,
	     on_dim2, on_offset, uc_dim1, uc_dim2, uc_offset, one_dim1, 
	    one_dim2, one_offset, onw_dim1, onw_dim2, onw_offset, ue_dim1, 
	    ue_dim2, ue_offset, uw_dim1, uw_dim2, uw_offset, un_dim1, un_dim2,
	     un_offset, us_dim1, us_dim2, us_offset, une_dim1, une_dim2, 
	    une_offset, unw_dim1, unw_dim2, unw_offset, use_dim1, use_dim2, 
	    use_offset, usw_dim1, usw_dim2, usw_offset, opc_dim1, opc_dim2, 
	    opc_offset, opn_dim1, opn_dim2, opn_offset, ops_dim1, ops_dim2, 
	    ops_offset, ope_dim1, ope_dim2, ope_offset, opw_dim1, opw_dim2, 
	    opw_offset, opne_dim1, opne_dim2, opne_offset, opnw_dim1, 
	    opnw_dim2, opnw_offset, opse_dim1, opse_dim2, opse_offset, 
	    opsw_dim1, opsw_dim2, opsw_offset, upc_dim1, upc_dim2, upc_offset,
	     upn_dim1, upn_dim2, upn_offset, ups_dim1, ups_dim2, ups_offset, 
	    upe_dim1, upe_dim2, upe_offset, upw_dim1, upw_dim2, upw_offset, 
	    upne_dim1, upne_dim2, upne_offset, upnw_dim1, upnw_dim2, 
	    upnw_offset, upse_dim1, upse_dim2, upse_offset, upsw_dim1, 
	    upsw_dim2, upsw_offset, dpc_dim1, dpc_dim2, dpc_offset, dpn_dim1, 
	    dpn_dim2, dpn_offset, dps_dim1, dps_dim2, dps_offset, dpe_dim1, 
	    dpe_dim2, dpe_offset, dpw_dim1, dpw_dim2, dpw_offset, dpne_dim1, 
	    dpne_dim2, dpne_offset, dpnw_dim1, dpnw_dim2, dpnw_offset, 
	    dpse_dim1, dpse_dim2, dpse_offset, dpsw_dim1, dpsw_dim2, 
	    dpsw_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, ii, jj, kk, im1, im2, jm1, ip1, ip2, jp1, jm2, 
	    jp2, km1, kp1, km2, kp2;
    static doublereal won;
    static integer iim1, jjm1, iip1, kkm1, jjp1, kkp1;
    static doublereal half, eighth, quarter;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    a modified 27-pt operator-based prologation. */
/* * */
/* *    form the prolongation operator from a 27 diagonal fine grid matrix. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** interpolation stencil *** */
    /* Parameter adjustments */
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
    --ipc;
    --rpc;

    /* Function Body */
    won = 1.;
    half = .5;
    quarter = .25;
    eighth = .125;
    i__1 = *nzc - 1;
    for (kk = 2; kk <= i__1; ++kk) {
	k = (kk << 1) - 1;
	i__2 = *nyc - 1;
	for (jj = 2; jj <= i__2; ++jj) {
	    j = (jj << 1) - 1;
	    i__3 = *nxc - 1;
	    for (ii = 2; ii <= i__3; ++ii) {
		i__ = (ii << 1) - 1;
/* * */
/* *             *** index computations *** */
		im1 = i__ - 1;
		ip1 = i__ + 1;
		im2 = i__ - 2;
		ip2 = i__ + 2;
		jm1 = j - 1;
		jp1 = j + 1;
		jm2 = j - 2;
		jp2 = j + 2;
		km1 = k - 1;
		kp1 = k + 1;
		km2 = k - 2;
		kp2 = k + 2;
		iim1 = ii - 1;
		iip1 = ii + 1;
		jjm1 = jj - 1;
		jjp1 = jj + 1;
		kkm1 = kk - 1;
		kkp1 = kk + 1;
/* * */
/* * ******************************************************************** */
/* * *** > oPC; */
/* * ******************************************************************** */
		opc[ii + (jj + kk * opc_dim2) * opc_dim1] = won;
/* * ******************************************************************** */
/* * *** > oPN; */
/* * ******************************************************************** */
		opn[ii + (jj + kk * opn_dim2) * opn_dim1] = (une[im1 + (j + 
			km1 * une_dim2) * une_dim1] + un[i__ + (j + km1 * 
			un_dim2) * un_dim1] + unw[ip1 + (j + km1 * unw_dim2) *
			 unw_dim1] + one[im1 + (j + k * one_dim2) * one_dim1] 
			+ on[i__ + (j + k * on_dim2) * on_dim1] + onw[ip1 + (
			j + k * onw_dim2) * onw_dim1] + usw[i__ + (jp1 + k * 
			usw_dim2) * usw_dim1] + us[i__ + (jp1 + k * us_dim2) *
			 us_dim1] + use[i__ + (jp1 + k * use_dim2) * use_dim1]
			) / (oc[i__ + (jp1 + k * oc_dim2) * oc_dim1] - oe[im1 
			+ (jp1 + k * oe_dim2) * oe_dim1] - oe[i__ + (jp1 + k *
			 oe_dim2) * oe_dim1] - uc[i__ + (jp1 + km1 * uc_dim2) 
			* uc_dim1] - ue[im1 + (jp1 + km1 * ue_dim2) * ue_dim1]
			 - uw[ip1 + (jp1 + km1 * uw_dim2) * uw_dim1] - uc[i__ 
			+ (jp1 + k * uc_dim2) * uc_dim1] - uw[i__ + (jp1 + k *
			 uw_dim2) * uw_dim1] - ue[i__ + (jp1 + k * ue_dim2) * 
			ue_dim1]);
/* * ******************************************************************** */
/* * *** > oPS; */
/* * ******************************************************************** */
		ops[ii + (jj + kk * ops_dim2) * ops_dim1] = (use[im1 + (j + 
			km1 * use_dim2) * use_dim1] + us[i__ + (j + km1 * 
			us_dim2) * us_dim1] + usw[ip1 + (j + km1 * usw_dim2) *
			 usw_dim1] + onw[i__ + (jm1 + k * onw_dim2) * 
			onw_dim1] + on[i__ + (jm1 + k * on_dim2) * on_dim1] + 
			one[i__ + (jm1 + k * one_dim2) * one_dim1] + unw[i__ 
			+ (jm1 + k * unw_dim2) * unw_dim1] + un[i__ + (jm1 + 
			k * un_dim2) * un_dim1] + une[i__ + (jm1 + k * 
			une_dim2) * une_dim1]) / (oc[i__ + (jm1 + k * oc_dim2)
			 * oc_dim1] - oe[im1 + (jm1 + k * oe_dim2) * oe_dim1] 
			- oe[i__ + (jm1 + k * oe_dim2) * oe_dim1] - uc[i__ + (
			jm1 + km1 * uc_dim2) * uc_dim1] - ue[im1 + (jm1 + km1 
			* ue_dim2) * ue_dim1] - uw[ip1 + (jm1 + km1 * uw_dim2)
			 * uw_dim1] - uc[i__ + (jm1 + k * uc_dim2) * uc_dim1] 
			- uw[i__ + (jm1 + k * uw_dim2) * uw_dim1] - ue[i__ + (
			jm1 + k * ue_dim2) * ue_dim1]);
/* * ******************************************************************** */
/* * *** > oPE; */
/* * ******************************************************************** */
		ope[ii + (jj + kk * ope_dim2) * ope_dim1] = (use[i__ + (jp1 + 
			km1 * use_dim2) * use_dim1] + onw[ip1 + (j + k * 
			onw_dim2) * onw_dim1] + unw[ip1 + (j + k * unw_dim2) *
			 unw_dim1] + ue[i__ + (j + km1 * ue_dim2) * ue_dim1] 
			+ oe[i__ + (j + k * oe_dim2) * oe_dim1] + uw[ip1 + (j 
			+ k * uw_dim2) * uw_dim1] + une[i__ + (jm1 + km1 * 
			une_dim2) * une_dim1] + one[i__ + (jm1 + k * one_dim2)
			 * one_dim1] + usw[ip1 + (j + k * usw_dim2) * 
			usw_dim1]) / (oc[ip1 + (j + k * oc_dim2) * oc_dim1] - 
			uc[ip1 + (j + km1 * uc_dim2) * uc_dim1] - uc[ip1 + (j 
			+ k * uc_dim2) * uc_dim1] - on[ip1 + (j + k * on_dim2)
			 * on_dim1] - us[ip1 + (jp1 + km1 * us_dim2) * 
			us_dim1] - un[ip1 + (j + k * un_dim2) * un_dim1] - on[
			ip1 + (jm1 + k * on_dim2) * on_dim1] - un[ip1 + (jm1 
			+ km1 * un_dim2) * un_dim1] - us[ip1 + (j + k * 
			us_dim2) * us_dim1]);
/* * ******************************************************************** */
/* * *** > oPW; */
/* * ******************************************************************** */
		opw[ii + (jj + kk * opw_dim2) * opw_dim1] = (usw[i__ + (jp1 + 
			km1 * usw_dim2) * usw_dim1] + one[im1 + (j + k * 
			one_dim2) * one_dim1] + une[im1 + (j + k * une_dim2) *
			 une_dim1] + uw[i__ + (j + km1 * uw_dim2) * uw_dim1] 
			+ oe[im1 + (j + k * oe_dim2) * oe_dim1] + ue[im1 + (j 
			+ k * ue_dim2) * ue_dim1] + unw[i__ + (jm1 + km1 * 
			unw_dim2) * unw_dim1] + onw[i__ + (jm1 + k * onw_dim2)
			 * onw_dim1] + use[im1 + (j + k * use_dim2) * 
			use_dim1]) / (oc[im1 + (j + k * oc_dim2) * oc_dim1] - 
			uc[im1 + (j + km1 * uc_dim2) * uc_dim1] - uc[im1 + (j 
			+ k * uc_dim2) * uc_dim1] - on[im1 + (j + k * on_dim2)
			 * on_dim1] - us[im1 + (jp1 + km1 * us_dim2) * 
			us_dim1] - un[im1 + (j + k * un_dim2) * un_dim1] - on[
			im1 + (jm1 + k * on_dim2) * on_dim1] - un[im1 + (jm1 
			+ km1 * un_dim2) * un_dim1] - us[im1 + (j + k * 
			us_dim2) * us_dim1]);
/* * ******************************************************************** */
/* * *** > oPNE; */
/* * ******************************************************************** */
		opne[ii + (jj + kk * opne_dim2) * opne_dim1] = (une[i__ + (j 
			+ km1 * une_dim2) * une_dim1] + one[i__ + (j + k * 
			one_dim2) * one_dim1] + usw[ip1 + (jp1 + k * usw_dim2)
			 * usw_dim1] + (un[ip1 + (j + km1 * un_dim2) * 
			un_dim1] + on[ip1 + (j + k * on_dim2) * on_dim1] + us[
			ip1 + (jp1 + k * us_dim2) * us_dim1]) * ope[ii + (jj 
			+ kk * ope_dim2) * ope_dim1] + (ue[i__ + (jp1 + km1 * 
			ue_dim2) * ue_dim1] + oe[i__ + (jp1 + k * oe_dim2) * 
			oe_dim1] + uw[ip1 + (jp1 + k * uw_dim2) * uw_dim1]) * 
			opn[ii + (jj + kk * opn_dim2) * opn_dim1]) / (oc[ip1 
			+ (jp1 + k * oc_dim2) * oc_dim1] - uc[ip1 + (jp1 + 
			km1 * uc_dim2) * uc_dim1] - uc[ip1 + (jp1 + k * 
			uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPNW; */
/* * ******************************************************************** */
		opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] = (unw[i__ + (j 
			+ km1 * unw_dim2) * unw_dim1] + onw[i__ + (j + k * 
			onw_dim2) * onw_dim1] + use[im1 + (jp1 + k * use_dim2)
			 * use_dim1] + (un[im1 + (j + km1 * un_dim2) * 
			un_dim1] + on[im1 + (j + k * on_dim2) * on_dim1] + us[
			im1 + (jp1 + k * us_dim2) * us_dim1]) * opw[ii + (jj 
			+ kk * opw_dim2) * opw_dim1] + (uw[i__ + (jp1 + km1 * 
			uw_dim2) * uw_dim1] + oe[im1 + (jp1 + k * oe_dim2) * 
			oe_dim1] + ue[im1 + (jp1 + k * ue_dim2) * ue_dim1]) * 
			opn[ii + (jj + kk * opn_dim2) * opn_dim1]) / (oc[im1 
			+ (jp1 + k * oc_dim2) * oc_dim1] - uc[im1 + (jp1 + 
			km1 * uc_dim2) * uc_dim1] - uc[im1 + (jp1 + k * 
			uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPSE; */
/* * ******************************************************************** */
		opse[ii + (jj + kk * opse_dim2) * opse_dim1] = (use[i__ + (j 
			+ km1 * use_dim2) * use_dim1] + onw[ip1 + (jm1 + k * 
			onw_dim2) * onw_dim1] + unw[ip1 + (jm1 + k * unw_dim2)
			 * unw_dim1] + (us[ip1 + (j + km1 * us_dim2) * 
			us_dim1] + on[ip1 + (jm1 + k * on_dim2) * on_dim1] + 
			un[ip1 + (jm1 + k * un_dim2) * un_dim1]) * ope[ii + (
			jj + kk * ope_dim2) * ope_dim1] + (ue[i__ + (jm1 + 
			km1 * ue_dim2) * ue_dim1] + oe[i__ + (jm1 + k * 
			oe_dim2) * oe_dim1] + uw[ip1 + (jm1 + k * uw_dim2) * 
			uw_dim1]) * ops[ii + (jj + kk * ops_dim2) * ops_dim1])
			 / (oc[ip1 + (jm1 + k * oc_dim2) * oc_dim1] - uc[ip1 
			+ (jm1 + km1 * uc_dim2) * uc_dim1] - uc[ip1 + (jm1 + 
			k * uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > oPSW; */
/* * ******************************************************************** */
		opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] = (usw[i__ + (j 
			+ km1 * usw_dim2) * usw_dim1] + one[im1 + (jm1 + k * 
			one_dim2) * one_dim1] + une[im1 + (jm1 + k * une_dim2)
			 * une_dim1] + (us[im1 + (j + km1 * us_dim2) * 
			us_dim1] + on[im1 + (jm1 + k * on_dim2) * on_dim1] + 
			un[im1 + (jm1 + k * un_dim2) * un_dim1]) * opw[ii + (
			jj + kk * opw_dim2) * opw_dim1] + (uw[i__ + (jm1 + 
			km1 * uw_dim2) * uw_dim1] + oe[im1 + (jm1 + k * 
			oe_dim2) * oe_dim1] + ue[im1 + (jm1 + k * ue_dim2) * 
			ue_dim1]) * ops[ii + (jj + kk * ops_dim2) * ops_dim1])
			 / (oc[im1 + (jm1 + k * oc_dim2) * oc_dim1] - uc[im1 
			+ (jm1 + km1 * uc_dim2) * uc_dim1] - uc[im1 + (jm1 + 
			k * uc_dim2) * uc_dim1]);
/* * ******************************************************************** */
/* * *** > dPC; */
/* * ******************************************************************** */
		dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] = (unw[i__ + (j + 
			km1 * unw_dim2) * unw_dim1] + uw[i__ + (j + km1 * 
			uw_dim2) * uw_dim1] + usw[i__ + (j + km1 * usw_dim2) *
			 usw_dim1] + un[i__ + (j + km1 * un_dim2) * un_dim1] 
			+ uc[i__ + (j + km1 * uc_dim2) * uc_dim1] + us[i__ + (
			j + km1 * us_dim2) * us_dim1] + une[i__ + (j + km1 * 
			une_dim2) * une_dim1] + ue[i__ + (j + km1 * ue_dim2) *
			 ue_dim1] + use[i__ + (j + km1 * use_dim2) * use_dim1]
			) / (oc[i__ + (j + km1 * oc_dim2) * oc_dim1] - on[i__ 
			+ (j + km1 * on_dim2) * on_dim1] - on[i__ + (jm1 + 
			km1 * on_dim2) * on_dim1] - onw[i__ + (j + km1 * 
			onw_dim2) * onw_dim1] - oe[im1 + (j + km1 * oe_dim2) *
			 oe_dim1] - one[im1 + (jm1 + km1 * one_dim2) * 
			one_dim1] - one[i__ + (j + km1 * one_dim2) * one_dim1]
			 - oe[i__ + (j + km1 * oe_dim2) * oe_dim1] - onw[ip1 
			+ (jm1 + km1 * onw_dim2) * onw_dim1]);
/* * ******************************************************************** */
/* * *** > dPN; */
/* * ******************************************************************** */
		dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] = (usw[i__ + (jp1 + 
			km1 * usw_dim2) * usw_dim1] + us[i__ + (jp1 + km1 * 
			us_dim2) * us_dim1] + use[i__ + (jp1 + km1 * use_dim2)
			 * use_dim1] + (one[im1 + (j + km1 * one_dim2) * 
			one_dim1] + on[i__ + (j + km1 * on_dim2) * on_dim1] + 
			onw[ip1 + (j + km1 * onw_dim2) * onw_dim1]) * dpc[ii 
			+ (jj + kk * dpc_dim2) * dpc_dim1] + (uw[i__ + (jp1 + 
			km1 * uw_dim2) * uw_dim1] + uc[i__ + (jp1 + km1 * 
			uc_dim2) * uc_dim1] + ue[i__ + (jp1 + km1 * ue_dim2) *
			 ue_dim1]) * opn[ii + (jj + kk * opn_dim2) * opn_dim1]
			) / (oc[i__ + (jp1 + km1 * oc_dim2) * oc_dim1] - oe[
			im1 + (jp1 + km1 * oe_dim2) * oe_dim1] - oe[i__ + (
			jp1 + km1 * oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > dPS; */
/* * ******************************************************************** */
		dps[ii + (jj + kk * dps_dim2) * dps_dim1] = (unw[i__ + (jm1 + 
			km1 * unw_dim2) * unw_dim1] + un[i__ + (jm1 + km1 * 
			un_dim2) * un_dim1] + une[i__ + (jm1 + km1 * une_dim2)
			 * une_dim1] + (onw[i__ + (jm1 + km1 * onw_dim2) * 
			onw_dim1] + on[i__ + (jm1 + km1 * on_dim2) * on_dim1] 
			+ one[i__ + (jm1 + km1 * one_dim2) * one_dim1]) * dpc[
			ii + (jj + kk * dpc_dim2) * dpc_dim1] + (uw[i__ + (
			jm1 + km1 * uw_dim2) * uw_dim1] + uc[i__ + (jm1 + km1 
			* uc_dim2) * uc_dim1] + ue[i__ + (jm1 + km1 * ue_dim2)
			 * ue_dim1]) * ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1]) / (oc[i__ + (jm1 + km1 * oc_dim2) * 
			oc_dim1] - oe[im1 + (jm1 + km1 * oe_dim2) * oe_dim1] 
			- oe[i__ + (jm1 + km1 * oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > dPE; */
/* * ******************************************************************** */
		dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] = (unw[ip1 + (j + 
			km1 * unw_dim2) * unw_dim1] + uw[ip1 + (j + km1 * 
			uw_dim2) * uw_dim1] + usw[ip1 + (j + km1 * usw_dim2) *
			 usw_dim1] + (un[ip1 + (j + km1 * un_dim2) * un_dim1] 
			+ uc[ip1 + (j + km1 * uc_dim2) * uc_dim1] + us[ip1 + (
			j + km1 * us_dim2) * us_dim1]) * ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] + (onw[ip1 + (j + km1 * 
			onw_dim2) * onw_dim1] + oe[i__ + (j + km1 * oe_dim2) *
			 oe_dim1] + one[i__ + (jm1 + km1 * one_dim2) * 
			one_dim1]) * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1]
			) / (oc[ip1 + (j + km1 * oc_dim2) * oc_dim1] - on[ip1 
			+ (j + km1 * on_dim2) * on_dim1] - on[ip1 + (jm1 + 
			km1 * on_dim2) * on_dim1]);
/* * ******************************************************************** */
/* * *** > dPW; */
/* * ******************************************************************** */
		dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] = (une[im1 + (j + 
			km1 * une_dim2) * une_dim1] + ue[im1 + (j + km1 * 
			ue_dim2) * ue_dim1] + use[im1 + (j + km1 * use_dim2) *
			 use_dim1] + (un[im1 + (j + km1 * un_dim2) * un_dim1] 
			+ uc[im1 + (j + km1 * uc_dim2) * uc_dim1] + us[im1 + (
			j + km1 * us_dim2) * us_dim1]) * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] + (one[im1 + (j + km1 * 
			one_dim2) * one_dim1] + oe[im1 + (j + km1 * oe_dim2) *
			 oe_dim1] + onw[i__ + (jm1 + km1 * onw_dim2) * 
			onw_dim1]) * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1]
			) / (oc[im1 + (j + km1 * oc_dim2) * oc_dim1] - on[im1 
			+ (j + km1 * on_dim2) * on_dim1] - on[im1 + (jm1 + 
			km1 * on_dim2) * on_dim1]);
/* * ******************************************************************** */
/* * *** > dPNE; */
/* * ******************************************************************** */
		dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] = (usw[ip1 + (
			jp1 + km1 * usw_dim2) * usw_dim1] + uw[ip1 + (jp1 + 
			km1 * uw_dim2) * uw_dim1] * opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] + us[ip1 + (jp1 + km1 * us_dim2)
			 * us_dim1] * ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1] + uc[ip1 + (jp1 + km1 * uc_dim2) * uc_dim1] 
			* opne[ii + (jj + kk * opne_dim2) * opne_dim1] + one[
			i__ + (j + km1 * one_dim2) * one_dim1] * dpc[ii + (jj 
			+ kk * dpc_dim2) * dpc_dim1] + oe[i__ + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpn[ii + (jj + kk * dpn_dim2) * 
			dpn_dim1] + on[ip1 + (j + km1 * on_dim2) * on_dim1] * 
			dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1]) / oc[ip1 + 
			(jp1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > dPNW; */
/* * ******************************************************************** */
		dpnw[ii + (jj + kk * dpnw_dim2) * dpnw_dim1] = (use[im1 + (
			jp1 + km1 * use_dim2) * use_dim1] + ue[im1 + (jp1 + 
			km1 * ue_dim2) * ue_dim1] * opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] + us[im1 + (jp1 + km1 * us_dim2)
			 * us_dim1] * opw[ii + (jj + kk * opw_dim2) * 
			opw_dim1] + uc[im1 + (jp1 + km1 * uc_dim2) * uc_dim1] 
			* opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] + onw[
			i__ + (j + km1 * onw_dim2) * onw_dim1] * dpc[ii + (jj 
			+ kk * dpc_dim2) * dpc_dim1] + oe[im1 + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpn[ii + (jj + kk * dpn_dim2) * 
			dpn_dim1] + on[im1 + (j + km1 * on_dim2) * on_dim1] * 
			dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1]) / oc[im1 + 
			(jp1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > dPSE; */
/* * ******************************************************************** */
		dpse[ii + (jj + kk * dpse_dim2) * dpse_dim1] = (unw[ip1 + (
			jm1 + km1 * unw_dim2) * unw_dim1] + uw[ip1 + (jm1 + 
			km1 * uw_dim2) * uw_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] + un[ip1 + (jm1 + km1 * un_dim2)
			 * un_dim1] * ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1] + uc[ip1 + (jm1 + km1 * uc_dim2) * uc_dim1] 
			* opse[ii + (jj + kk * opse_dim2) * opse_dim1] + onw[
			ip1 + (jm1 + km1 * onw_dim2) * onw_dim1] * dpc[ii + (
			jj + kk * dpc_dim2) * dpc_dim1] + oe[i__ + (jm1 + km1 
			* oe_dim2) * oe_dim1] * dps[ii + (jj + kk * dps_dim2) 
			* dps_dim1] + on[ip1 + (jm1 + km1 * on_dim2) * 
			on_dim1] * dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1]) 
			/ oc[ip1 + (jm1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > dPSW; */
/* * ******************************************************************** */
		dpsw[ii + (jj + kk * dpsw_dim2) * dpsw_dim1] = (une[im1 + (
			jm1 + km1 * une_dim2) * une_dim1] + ue[im1 + (jm1 + 
			km1 * ue_dim2) * ue_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] + un[im1 + (jm1 + km1 * un_dim2)
			 * un_dim1] * opw[ii + (jj + kk * opw_dim2) * 
			opw_dim1] + uc[im1 + (jm1 + km1 * uc_dim2) * uc_dim1] 
			* opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] + one[
			im1 + (jm1 + km1 * one_dim2) * one_dim1] * dpc[ii + (
			jj + kk * dpc_dim2) * dpc_dim1] + oe[im1 + (jm1 + km1 
			* oe_dim2) * oe_dim1] * dps[ii + (jj + kk * dps_dim2) 
			* dps_dim1] + on[im1 + (jm1 + km1 * on_dim2) * 
			on_dim1] * dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1]) 
			/ oc[im1 + (jm1 + km1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPC; */
/* * ******************************************************************** */
		upc[ii + (jj + kk * upc_dim2) * upc_dim1] = (use[im1 + (jp1 + 
			k * use_dim2) * use_dim1] + ue[im1 + (j + k * ue_dim2)
			 * ue_dim1] + une[im1 + (jm1 + k * une_dim2) * 
			une_dim1] + us[i__ + (jp1 + k * us_dim2) * us_dim1] + 
			uc[i__ + (j + k * uc_dim2) * uc_dim1] + un[i__ + (jm1 
			+ k * un_dim2) * un_dim1] + usw[ip1 + (jp1 + k * 
			usw_dim2) * usw_dim1] + uw[ip1 + (j + k * uw_dim2) * 
			uw_dim1] + unw[ip1 + (jm1 + k * unw_dim2) * unw_dim1])
			 / (oc[i__ + (j + kp1 * oc_dim2) * oc_dim1] - on[i__ 
			+ (j + kp1 * on_dim2) * on_dim1] - on[i__ + (jm1 + 
			kp1 * on_dim2) * on_dim1] - onw[i__ + (j + kp1 * 
			onw_dim2) * onw_dim1] - oe[im1 + (j + kp1 * oe_dim2) *
			 oe_dim1] - one[im1 + (jm1 + kp1 * one_dim2) * 
			one_dim1] - one[i__ + (j + kp1 * one_dim2) * one_dim1]
			 - oe[i__ + (j + kp1 * oe_dim2) * oe_dim1] - onw[ip1 
			+ (jm1 + kp1 * onw_dim2) * onw_dim1]);
/* * ******************************************************************** */
/* * *** > uPN; */
/* * ******************************************************************** */
		upn[ii + (jj + kk * upn_dim2) * upn_dim1] = (une[im1 + (j + k 
			* une_dim2) * une_dim1] + un[i__ + (j + k * un_dim2) *
			 un_dim1] + unw[ip1 + (j + k * unw_dim2) * unw_dim1] 
			+ (one[im1 + (j + kp1 * one_dim2) * one_dim1] + on[
			i__ + (j + kp1 * on_dim2) * on_dim1] + onw[ip1 + (j + 
			kp1 * onw_dim2) * onw_dim1]) * upc[ii + (jj + kk * 
			upc_dim2) * upc_dim1] + (ue[im1 + (jp1 + k * ue_dim2) 
			* ue_dim1] + uc[i__ + (jp1 + k * uc_dim2) * uc_dim1] 
			+ uw[ip1 + (jp1 + k * uw_dim2) * uw_dim1]) * opn[ii + 
			(jj + kk * opn_dim2) * opn_dim1]) / (oc[i__ + (jp1 + 
			kp1 * oc_dim2) * oc_dim1] - oe[im1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] - oe[i__ + (jp1 + kp1 * oe_dim2) *
			 oe_dim1]);
/* * ******************************************************************** */
/* * *** > uPS; */
/* * ******************************************************************** */
		ups[ii + (jj + kk * ups_dim2) * ups_dim1] = (use[im1 + (j + k 
			* use_dim2) * use_dim1] + us[i__ + (j + k * us_dim2) *
			 us_dim1] + usw[ip1 + (j + k * usw_dim2) * usw_dim1] 
			+ (onw[i__ + (jm1 + kp1 * onw_dim2) * onw_dim1] + on[
			i__ + (jm1 + kp1 * on_dim2) * on_dim1] + one[i__ + (
			jm1 + kp1 * one_dim2) * one_dim1]) * upc[ii + (jj + 
			kk * upc_dim2) * upc_dim1] + (ue[im1 + (jm1 + k * 
			ue_dim2) * ue_dim1] + uc[i__ + (jm1 + k * uc_dim2) * 
			uc_dim1] + uw[ip1 + (jm1 + k * uw_dim2) * uw_dim1]) * 
			ops[ii + (jj + kk * ops_dim2) * ops_dim1]) / (oc[i__ 
			+ (jm1 + kp1 * oc_dim2) * oc_dim1] - oe[im1 + (jm1 + 
			kp1 * oe_dim2) * oe_dim1] - oe[i__ + (jm1 + kp1 * 
			oe_dim2) * oe_dim1]);
/* * ******************************************************************** */
/* * *** > uPE; */
/* * ******************************************************************** */
		upe[ii + (jj + kk * upe_dim2) * upe_dim1] = (use[i__ + (jp1 + 
			k * use_dim2) * use_dim1] + us[ip1 + (jp1 + k * 
			us_dim2) * us_dim1] + une[i__ + (jm1 + k * une_dim2) *
			 une_dim1] + (us[ip1 + (jp1 + k * us_dim2) * us_dim1] 
			+ uc[ip1 + (j + k * uc_dim2) * uc_dim1] + un[ip1 + (
			jm1 + k * un_dim2) * un_dim1]) * ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] + (onw[ip1 + (j + kp1 * 
			onw_dim2) * onw_dim1] + oe[i__ + (j + kp1 * oe_dim2) *
			 oe_dim1] + one[i__ + (jm1 + kp1 * one_dim2) * 
			one_dim1]) * upc[ii + (jj + kk * upc_dim2) * upc_dim1]
			) / (oc[ip1 + (j + kp1 * oc_dim2) * oc_dim1] - on[ip1 
			+ (j + kp1 * on_dim2) * on_dim1] - on[ip1 + (jm1 + 
			kp1 * on_dim2) * on_dim1]);
/* * ******************************************************************** */
/* * *** > uPW; */
/* * ******************************************************************** */
		upw[ii + (jj + kk * upw_dim2) * upw_dim1] = (usw[i__ + (jp1 + 
			k * usw_dim2) * usw_dim1] + uw[i__ + (j + k * uw_dim2)
			 * uw_dim1] + unw[i__ + (jm1 + k * unw_dim2) * 
			unw_dim1] + (us[im1 + (jp1 + k * us_dim2) * us_dim1] 
			+ uc[im1 + (j + k * uc_dim2) * uc_dim1] + un[im1 + (
			jm1 + k * un_dim2) * un_dim1]) * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] + (one[im1 + (j + kp1 * 
			one_dim2) * one_dim1] + oe[im1 + (j + kp1 * oe_dim2) *
			 oe_dim1] + onw[i__ + (jm1 + kp1 * onw_dim2) * 
			onw_dim1]) * upc[ii + (jj + kk * upc_dim2) * upc_dim1]
			) / (oc[im1 + (j + kp1 * oc_dim2) * oc_dim1] - on[im1 
			+ (j + kp1 * on_dim2) * on_dim1] - on[im1 + (jm1 + 
			kp1 * on_dim2) * on_dim1]);
/* * ******************************************************************** */
/* * *** > uPNE; */
/* * ******************************************************************** */
		upne[ii + (jj + kk * upne_dim2) * upne_dim1] = (une[i__ + (j 
			+ k * une_dim2) * une_dim1] + ue[i__ + (jp1 + k * 
			ue_dim2) * ue_dim1] * opn[ii + (jj + kk * opn_dim2) * 
			opn_dim1] + un[ip1 + (j + k * un_dim2) * un_dim1] * 
			ope[ii + (jj + kk * ope_dim2) * ope_dim1] + uc[ip1 + (
			jp1 + k * uc_dim2) * uc_dim1] * opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1] + one[i__ + (j + kp1 * 
			one_dim2) * one_dim1] * upc[ii + (jj + kk * upc_dim2) 
			* upc_dim1] + oe[i__ + (jp1 + kp1 * oe_dim2) * 
			oe_dim1] * upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			+ on[ip1 + (j + kp1 * on_dim2) * on_dim1] * upe[ii + (
			jj + kk * upe_dim2) * upe_dim1]) / oc[ip1 + (jp1 + 
			kp1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPNW; */
/* * ******************************************************************** */
		upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] = (unw[i__ + (j 
			+ k * unw_dim2) * unw_dim1] + uw[i__ + (jp1 + k * 
			uw_dim2) * uw_dim1] * opn[ii + (jj + kk * opn_dim2) * 
			opn_dim1] + un[im1 + (j + k * un_dim2) * un_dim1] * 
			opw[ii + (jj + kk * opw_dim2) * opw_dim1] + uc[im1 + (
			jp1 + k * uc_dim2) * uc_dim1] * opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] + onw[i__ + (j + kp1 * 
			onw_dim2) * onw_dim1] * upc[ii + (jj + kk * upc_dim2) 
			* upc_dim1] + oe[im1 + (jp1 + kp1 * oe_dim2) * 
			oe_dim1] * upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			+ on[im1 + (j + kp1 * on_dim2) * on_dim1] * upw[ii + (
			jj + kk * upw_dim2) * upw_dim1]) / oc[im1 + (jp1 + 
			kp1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPSE; */
/* * ******************************************************************** */
		upse[ii + (jj + kk * upse_dim2) * upse_dim1] = (use[i__ + (j 
			+ k * use_dim2) * use_dim1] + ue[i__ + (jm1 + k * 
			ue_dim2) * ue_dim1] * ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1] + us[ip1 + (j + k * us_dim2) * us_dim1] * 
			ope[ii + (jj + kk * ope_dim2) * ope_dim1] + uc[ip1 + (
			jm1 + k * uc_dim2) * uc_dim1] * opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] + onw[ip1 + (jm1 + kp1 * 
			onw_dim2) * onw_dim1] * upc[ii + (jj + kk * upc_dim2) 
			* upc_dim1] + oe[i__ + (jm1 + kp1 * oe_dim2) * 
			oe_dim1] * ups[ii + (jj + kk * ups_dim2) * ups_dim1] 
			+ on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1] * upe[ii 
			+ (jj + kk * upe_dim2) * upe_dim1]) / oc[ip1 + (jm1 + 
			kp1 * oc_dim2) * oc_dim1];
/* * ******************************************************************** */
/* * *** > uPSW; */
/* * ******************************************************************** */
		upsw[ii + (jj + kk * upsw_dim2) * upsw_dim1] = (usw[i__ + (j 
			+ k * usw_dim2) * usw_dim1] + uw[i__ + (jm1 + k * 
			uw_dim2) * uw_dim1] * ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1] + us[im1 + (j + k * us_dim2) * us_dim1] * 
			opw[ii + (jj + kk * opw_dim2) * opw_dim1] + uc[im1 + (
			jm1 + k * uc_dim2) * uc_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] + one[im1 + (jm1 + kp1 * 
			one_dim2) * one_dim1] * upc[ii + (jj + kk * upc_dim2) 
			* upc_dim1] + oe[im1 + (jm1 + kp1 * oe_dim2) * 
			oe_dim1] * ups[ii + (jj + kk * ups_dim2) * ups_dim1] 
			+ on[im1 + (jm1 + kp1 * on_dim2) * on_dim1] * upw[ii 
			+ (jj + kk * upw_dim2) * upw_dim1]) / oc[im1 + (jm1 + 
			kp1 * oc_dim2) * oc_dim1];
/* *             *** main loop *** */
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildpb_modop27__ */

