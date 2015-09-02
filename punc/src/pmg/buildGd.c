/* ./src_f77/buildGd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    buildGd.f */
/* * @author  Michael Holst */
/* * @brief   The heart of PMG: MAPLE-generated Galerkin product expressions. */
/* * @version $Id: buildGd.c,v 1.3 2010/08/12 05:45:19 fetk Exp $ */
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
/* Subroutine */ int buildg_(integer *nxf, integer *nyf, integer *nzf, 
	integer *nxc, integer *nyc, integer *nzc, integer *numdia, doublereal 
	*pcff, doublereal *acff, doublereal *ac)
{
    /* System generated locals */
    integer pcff_dim1, pcff_offset, acff_dim1, acff_offset, ac_dim1, 
	    ac_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int buildg_27__(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
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
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), buildg_1__(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), 
	    buildg_7__(integer *, integer *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
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

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    form the galerkin coarse grid matrix from the fine grid */
/* *    matrix and the prolongation operator. */
/* * */
/* *    differentiate between 1, 7, and 27 diagonal fine grid matrices */
/* *    for efficiency. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the build routine *** */
    /* Parameter adjustments */
    acff_dim1 = *nxf * *nyf * *nzf;
    acff_offset = 1 + acff_dim1;
    acff -= acff_offset;
    ac_dim1 = *nxc * *nyc * *nzc;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    pcff_dim1 = *nxc * *nyc * *nzc;
    pcff_offset = 1 + pcff_dim1;
    pcff -= pcff_offset;

    /* Function Body */
    if (*numdia == 1) {
	buildg_1__(nxf, nyf, nzf, nxc, nyc, nzc, &pcff[pcff_dim1 + 1], &pcff[(
		pcff_dim1 << 1) + 1], &pcff[pcff_dim1 * 3 + 1], &pcff[(
		pcff_dim1 << 2) + 1], &pcff[pcff_dim1 * 5 + 1], &pcff[
		pcff_dim1 * 6 + 1], &pcff[pcff_dim1 * 7 + 1], &pcff[(
		pcff_dim1 << 3) + 1], &pcff[pcff_dim1 * 9 + 1], &pcff[
		pcff_dim1 * 10 + 1], &pcff[pcff_dim1 * 11 + 1], &pcff[
		pcff_dim1 * 12 + 1], &pcff[pcff_dim1 * 13 + 1], &pcff[
		pcff_dim1 * 14 + 1], &pcff[pcff_dim1 * 15 + 1], &pcff[(
		pcff_dim1 << 4) + 1], &pcff[pcff_dim1 * 17 + 1], &pcff[
		pcff_dim1 * 18 + 1], &pcff[pcff_dim1 * 19 + 1], &pcff[
		pcff_dim1 * 20 + 1], &pcff[pcff_dim1 * 21 + 1], &pcff[
		pcff_dim1 * 22 + 1], &pcff[pcff_dim1 * 23 + 1], &pcff[
		pcff_dim1 * 24 + 1], &pcff[pcff_dim1 * 25 + 1], &pcff[
		pcff_dim1 * 26 + 1], &pcff[pcff_dim1 * 27 + 1], &acff[
		acff_dim1 + 1], &ac[ac_dim1 + 1], &ac[(ac_dim1 << 1) + 1], &
		ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) + 1], &ac[ac_dim1 * 5 
		+ 1], &ac[ac_dim1 * 6 + 1], &ac[ac_dim1 * 7 + 1], &ac[(
		ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1], &ac[ac_dim1 * 10 + 
		1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 + 1], &ac[ac_dim1 
		* 13 + 1], &ac[ac_dim1 * 14 + 1]);
    } else if (*numdia == 7) {
	buildg_7__(nxf, nyf, nzf, nxc, nyc, nzc, &pcff[pcff_dim1 + 1], &pcff[(
		pcff_dim1 << 1) + 1], &pcff[pcff_dim1 * 3 + 1], &pcff[(
		pcff_dim1 << 2) + 1], &pcff[pcff_dim1 * 5 + 1], &pcff[
		pcff_dim1 * 6 + 1], &pcff[pcff_dim1 * 7 + 1], &pcff[(
		pcff_dim1 << 3) + 1], &pcff[pcff_dim1 * 9 + 1], &pcff[
		pcff_dim1 * 10 + 1], &pcff[pcff_dim1 * 11 + 1], &pcff[
		pcff_dim1 * 12 + 1], &pcff[pcff_dim1 * 13 + 1], &pcff[
		pcff_dim1 * 14 + 1], &pcff[pcff_dim1 * 15 + 1], &pcff[(
		pcff_dim1 << 4) + 1], &pcff[pcff_dim1 * 17 + 1], &pcff[
		pcff_dim1 * 18 + 1], &pcff[pcff_dim1 * 19 + 1], &pcff[
		pcff_dim1 * 20 + 1], &pcff[pcff_dim1 * 21 + 1], &pcff[
		pcff_dim1 * 22 + 1], &pcff[pcff_dim1 * 23 + 1], &pcff[
		pcff_dim1 * 24 + 1], &pcff[pcff_dim1 * 25 + 1], &pcff[
		pcff_dim1 * 26 + 1], &pcff[pcff_dim1 * 27 + 1], &acff[
		acff_dim1 + 1], &acff[(acff_dim1 << 1) + 1], &acff[acff_dim1 *
		 3 + 1], &acff[(acff_dim1 << 2) + 1], &ac[ac_dim1 + 1], &ac[(
		ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) 
		+ 1], &ac[ac_dim1 * 5 + 1], &ac[ac_dim1 * 6 + 1], &ac[ac_dim1 
		* 7 + 1], &ac[(ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1], &ac[
		ac_dim1 * 10 + 1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 + 
		1], &ac[ac_dim1 * 13 + 1], &ac[ac_dim1 * 14 + 1]);
    } else if (*numdia == 27) {
	buildg_27__(nxf, nyf, nzf, nxc, nyc, nzc, &pcff[pcff_dim1 + 1], &pcff[
		(pcff_dim1 << 1) + 1], &pcff[pcff_dim1 * 3 + 1], &pcff[(
		pcff_dim1 << 2) + 1], &pcff[pcff_dim1 * 5 + 1], &pcff[
		pcff_dim1 * 6 + 1], &pcff[pcff_dim1 * 7 + 1], &pcff[(
		pcff_dim1 << 3) + 1], &pcff[pcff_dim1 * 9 + 1], &pcff[
		pcff_dim1 * 10 + 1], &pcff[pcff_dim1 * 11 + 1], &pcff[
		pcff_dim1 * 12 + 1], &pcff[pcff_dim1 * 13 + 1], &pcff[
		pcff_dim1 * 14 + 1], &pcff[pcff_dim1 * 15 + 1], &pcff[(
		pcff_dim1 << 4) + 1], &pcff[pcff_dim1 * 17 + 1], &pcff[
		pcff_dim1 * 18 + 1], &pcff[pcff_dim1 * 19 + 1], &pcff[
		pcff_dim1 * 20 + 1], &pcff[pcff_dim1 * 21 + 1], &pcff[
		pcff_dim1 * 22 + 1], &pcff[pcff_dim1 * 23 + 1], &pcff[
		pcff_dim1 * 24 + 1], &pcff[pcff_dim1 * 25 + 1], &pcff[
		pcff_dim1 * 26 + 1], &pcff[pcff_dim1 * 27 + 1], &acff[
		acff_dim1 + 1], &acff[(acff_dim1 << 1) + 1], &acff[acff_dim1 *
		 3 + 1], &acff[(acff_dim1 << 2) + 1], &acff[acff_dim1 * 5 + 1]
		, &acff[acff_dim1 * 6 + 1], &acff[acff_dim1 * 7 + 1], &acff[(
		acff_dim1 << 3) + 1], &acff[acff_dim1 * 9 + 1], &acff[
		acff_dim1 * 10 + 1], &acff[acff_dim1 * 11 + 1], &acff[
		acff_dim1 * 12 + 1], &acff[acff_dim1 * 13 + 1], &acff[
		acff_dim1 * 14 + 1], &ac[ac_dim1 + 1], &ac[(ac_dim1 << 1) + 1]
		, &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) + 1], &ac[ac_dim1 *
		 5 + 1], &ac[ac_dim1 * 6 + 1], &ac[ac_dim1 * 7 + 1], &ac[(
		ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1], &ac[ac_dim1 * 10 + 
		1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 + 1], &ac[ac_dim1 
		* 13 + 1], &ac[ac_dim1 * 14 + 1]);
    } else {
	s_wsle(&io___1);
	do_lio(&c__9, &c__1, "% BUILDG: invalid stencil type give...", (
		ftnlen)38);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* buildg_ */

/* Subroutine */ int buildg_1__(integer *nxf, integer *nyf, integer *nzf, 
	integer *nx, integer *ny, integer *nz, doublereal *opc, doublereal *
	opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *
	opne, doublereal *opnw, doublereal *opse, doublereal *opsw, 
	doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, 
	doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse,
	 doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, 
	doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, 
	doublereal *dpse, doublereal *dpsw, doublereal *oc, doublereal *xoc, 
	doublereal *xoe, doublereal *xon, doublereal *xuc, doublereal *xone, 
	doublereal *xonw, doublereal *xue, doublereal *xuw, doublereal *xun, 
	doublereal *xus, doublereal *xune, doublereal *xunw, doublereal *xuse,
	 doublereal *xusw)
{
    /* System generated locals */
    integer oc_dim1, oc_dim2, oc_offset, xoc_dim1, xoc_dim2, xoc_offset, 
	    xoe_dim1, xoe_dim2, xoe_offset, xon_dim1, xon_dim2, xon_offset, 
	    xuc_dim1, xuc_dim2, xuc_offset, xone_dim1, xone_dim2, xone_offset,
	     xonw_dim1, xonw_dim2, xonw_offset, xue_dim1, xue_dim2, 
	    xue_offset, xuw_dim1, xuw_dim2, xuw_offset, xun_dim1, xun_dim2, 
	    xun_offset, xus_dim1, xus_dim2, xus_offset, xune_dim1, xune_dim2, 
	    xune_offset, xunw_dim1, xunw_dim2, xunw_offset, xuse_dim1, 
	    xuse_dim2, xuse_offset, xusw_dim1, xusw_dim2, xusw_offset, 
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
    static doublereal tmp1_xoc__, tmp2_xoc__, tmp3_xoc__;
    static integer i__, j, k, ii, jj, kk, im1, jm1, km1, ip1, jp1, kp1, iim1, 
	    jjm1, iip1, kkm1, jjp1, kkp1, nxm1, nym1, nzm1;

/* * ******************************************************************** */
/* * purpose: compute a 27-point galerkin coarse grid matrix from */
/* *          a 1-point (i.e., diagonal) fine grid matrix. */
/* * */
/* * expressions for the galerkin coarse grid stencil XA in terms of */
/* * the fine grid matrix stencil A and the interpolation operator */
/* * stencil P.  these stencils have the form: */
/* * */
/* *    XA := array([ */
/* * */
/* *      matrix([ */
/* *         [ -XdNW(i,j,k), -XdN(i,j,k), -XdNE(i,j,k) ], */
/* *         [ -XdW(i,j,k),  -XdC(i,j,k), -XdE(i,j,k)  ], */
/* *         [ -XdSW(i,j,k), -XdS(i,j,k), -XdSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ -XoNW(i,j,k), -XoN(i,j,k), -XoNE(i,j,k) ], */
/* *         [ -XoW(i,j,k),   XoC(i,j,k), -XoE(i,j,k)  ], */
/* *         [ -XoSW(i,j,k), -XoS(i,j,k), -XoSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ -XuNW(i,j,k), -XuN(i,j,k), -XuNE(i,j,k) ], */
/* *         [ -XuW(i,j,k),  -XuC(i,j,k), -XuE(i,j,k)  ], */
/* *         [ -XuSW(i,j,k), -XuS(i,j,k), -XuSE(i,j,k) ] */
/* *      ]) */
/* *    ]): */
/* * */
/* *    A := array([ */
/* * */
/* *      matrix([ */
/* *         [  0,           0,          0          ], */
/* *         [  0,           0,          0          ], */
/* *         [  0,           0,          0          ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [  0,           0,          0          ], */
/* *         [  0,           oC(i,j,k),  0          ], */
/* *         [  0,           0,          0          ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [  0,           0,          0          ], */
/* *         [  0,           0,          0          ], */
/* *         [  0,           0,          0          ] */
/* *      ]) */
/* * */
/* *   P := array([ */
/* * */
/* *      matrix([ */
/* *         [ dPNW(i,j,k), dPN(i,j,k), dPNE(i,j,k) ], */
/* *         [ dPW(i,j,k),  dPC(i,j,k), dPE(i,j,k)  ], */
/* *         [ dPSW(i,j,k), dPS(i,j,k), dPSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ oPNW(i,j,k), oPN(i,j,k), oPNE(i,j,k) ], */
/* *         [ oPW(i,j,k),  oPC(i,j,k), oPE(i,j,k)  ], */
/* *         [ oPSW(i,j,k), oPS(i,j,k), oPSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ uPNW(i,j,k), uPN(i,j,k), uPNE(i,j,k) ], */
/* *         [ uPW(i,j,k),  uPC(i,j,k), uPE(i,j,k)  ], */
/* *         [ uPSW(i,j,k), uPS(i,j,k), uPSE(i,j,k) ] */
/* *      ]) */
/* *    ]): */
/* * */
/* * author:  michael holst */
/* * ******************************************************************** */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** define n and determine number of mesh points *** */
    /* Parameter adjustments */
    oc_dim1 = *nxf;
    oc_dim2 = *nyf;
    oc_offset = 1 + oc_dim1 * (1 + oc_dim2);
    oc -= oc_offset;
    xusw_dim1 = *nx;
    xusw_dim2 = *ny;
    xusw_offset = 1 + xusw_dim1 * (1 + xusw_dim2);
    xusw -= xusw_offset;
    xuse_dim1 = *nx;
    xuse_dim2 = *ny;
    xuse_offset = 1 + xuse_dim1 * (1 + xuse_dim2);
    xuse -= xuse_offset;
    xunw_dim1 = *nx;
    xunw_dim2 = *ny;
    xunw_offset = 1 + xunw_dim1 * (1 + xunw_dim2);
    xunw -= xunw_offset;
    xune_dim1 = *nx;
    xune_dim2 = *ny;
    xune_offset = 1 + xune_dim1 * (1 + xune_dim2);
    xune -= xune_offset;
    xus_dim1 = *nx;
    xus_dim2 = *ny;
    xus_offset = 1 + xus_dim1 * (1 + xus_dim2);
    xus -= xus_offset;
    xun_dim1 = *nx;
    xun_dim2 = *ny;
    xun_offset = 1 + xun_dim1 * (1 + xun_dim2);
    xun -= xun_offset;
    xuw_dim1 = *nx;
    xuw_dim2 = *ny;
    xuw_offset = 1 + xuw_dim1 * (1 + xuw_dim2);
    xuw -= xuw_offset;
    xue_dim1 = *nx;
    xue_dim2 = *ny;
    xue_offset = 1 + xue_dim1 * (1 + xue_dim2);
    xue -= xue_offset;
    xonw_dim1 = *nx;
    xonw_dim2 = *ny;
    xonw_offset = 1 + xonw_dim1 * (1 + xonw_dim2);
    xonw -= xonw_offset;
    xone_dim1 = *nx;
    xone_dim2 = *ny;
    xone_offset = 1 + xone_dim1 * (1 + xone_dim2);
    xone -= xone_offset;
    xuc_dim1 = *nx;
    xuc_dim2 = *ny;
    xuc_offset = 1 + xuc_dim1 * (1 + xuc_dim2);
    xuc -= xuc_offset;
    xon_dim1 = *nx;
    xon_dim2 = *ny;
    xon_offset = 1 + xon_dim1 * (1 + xon_dim2);
    xon -= xon_offset;
    xoe_dim1 = *nx;
    xoe_dim2 = *ny;
    xoe_offset = 1 + xoe_dim1 * (1 + xoe_dim2);
    xoe -= xoe_offset;
    xoc_dim1 = *nx;
    xoc_dim2 = *ny;
    xoc_offset = 1 + xoc_dim1 * (1 + xoc_dim2);
    xoc -= xoc_offset;
    dpsw_dim1 = *nx;
    dpsw_dim2 = *ny;
    dpsw_offset = 1 + dpsw_dim1 * (1 + dpsw_dim2);
    dpsw -= dpsw_offset;
    dpse_dim1 = *nx;
    dpse_dim2 = *ny;
    dpse_offset = 1 + dpse_dim1 * (1 + dpse_dim2);
    dpse -= dpse_offset;
    dpnw_dim1 = *nx;
    dpnw_dim2 = *ny;
    dpnw_offset = 1 + dpnw_dim1 * (1 + dpnw_dim2);
    dpnw -= dpnw_offset;
    dpne_dim1 = *nx;
    dpne_dim2 = *ny;
    dpne_offset = 1 + dpne_dim1 * (1 + dpne_dim2);
    dpne -= dpne_offset;
    dpw_dim1 = *nx;
    dpw_dim2 = *ny;
    dpw_offset = 1 + dpw_dim1 * (1 + dpw_dim2);
    dpw -= dpw_offset;
    dpe_dim1 = *nx;
    dpe_dim2 = *ny;
    dpe_offset = 1 + dpe_dim1 * (1 + dpe_dim2);
    dpe -= dpe_offset;
    dps_dim1 = *nx;
    dps_dim2 = *ny;
    dps_offset = 1 + dps_dim1 * (1 + dps_dim2);
    dps -= dps_offset;
    dpn_dim1 = *nx;
    dpn_dim2 = *ny;
    dpn_offset = 1 + dpn_dim1 * (1 + dpn_dim2);
    dpn -= dpn_offset;
    dpc_dim1 = *nx;
    dpc_dim2 = *ny;
    dpc_offset = 1 + dpc_dim1 * (1 + dpc_dim2);
    dpc -= dpc_offset;
    upsw_dim1 = *nx;
    upsw_dim2 = *ny;
    upsw_offset = 1 + upsw_dim1 * (1 + upsw_dim2);
    upsw -= upsw_offset;
    upse_dim1 = *nx;
    upse_dim2 = *ny;
    upse_offset = 1 + upse_dim1 * (1 + upse_dim2);
    upse -= upse_offset;
    upnw_dim1 = *nx;
    upnw_dim2 = *ny;
    upnw_offset = 1 + upnw_dim1 * (1 + upnw_dim2);
    upnw -= upnw_offset;
    upne_dim1 = *nx;
    upne_dim2 = *ny;
    upne_offset = 1 + upne_dim1 * (1 + upne_dim2);
    upne -= upne_offset;
    upw_dim1 = *nx;
    upw_dim2 = *ny;
    upw_offset = 1 + upw_dim1 * (1 + upw_dim2);
    upw -= upw_offset;
    upe_dim1 = *nx;
    upe_dim2 = *ny;
    upe_offset = 1 + upe_dim1 * (1 + upe_dim2);
    upe -= upe_offset;
    ups_dim1 = *nx;
    ups_dim2 = *ny;
    ups_offset = 1 + ups_dim1 * (1 + ups_dim2);
    ups -= ups_offset;
    upn_dim1 = *nx;
    upn_dim2 = *ny;
    upn_offset = 1 + upn_dim1 * (1 + upn_dim2);
    upn -= upn_offset;
    upc_dim1 = *nx;
    upc_dim2 = *ny;
    upc_offset = 1 + upc_dim1 * (1 + upc_dim2);
    upc -= upc_offset;
    opsw_dim1 = *nx;
    opsw_dim2 = *ny;
    opsw_offset = 1 + opsw_dim1 * (1 + opsw_dim2);
    opsw -= opsw_offset;
    opse_dim1 = *nx;
    opse_dim2 = *ny;
    opse_offset = 1 + opse_dim1 * (1 + opse_dim2);
    opse -= opse_offset;
    opnw_dim1 = *nx;
    opnw_dim2 = *ny;
    opnw_offset = 1 + opnw_dim1 * (1 + opnw_dim2);
    opnw -= opnw_offset;
    opne_dim1 = *nx;
    opne_dim2 = *ny;
    opne_offset = 1 + opne_dim1 * (1 + opne_dim2);
    opne -= opne_offset;
    opw_dim1 = *nx;
    opw_dim2 = *ny;
    opw_offset = 1 + opw_dim1 * (1 + opw_dim2);
    opw -= opw_offset;
    ope_dim1 = *nx;
    ope_dim2 = *ny;
    ope_offset = 1 + ope_dim1 * (1 + ope_dim2);
    ope -= ope_offset;
    ops_dim1 = *nx;
    ops_dim2 = *ny;
    ops_offset = 1 + ops_dim1 * (1 + ops_dim2);
    ops -= ops_offset;
    opn_dim1 = *nx;
    opn_dim2 = *ny;
    opn_offset = 1 + opn_dim1 * (1 + opn_dim2);
    opn -= opn_offset;
    opc_dim1 = *nx;
    opc_dim2 = *ny;
    opc_offset = 1 + opc_dim1 * (1 + opc_dim2);
    opc -= opc_offset;

    /* Function Body */
    nxm1 = *nx - 1;
    nym1 = *ny - 1;
    nzm1 = *nz - 1;
/* * */
/* *    *** build the operator *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (kk = 2; kk <= i__1; ++kk) {
	k = (kk << 1) - 1;
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (jj = 2; jj <= i__2; ++jj) {
	    j = (jj << 1) - 1;
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (ii = 2; ii <= i__3; ++ii) {
		i__ = (ii << 1) - 1;
/* * */
/* *             *** index computations *** */
		im1 = i__ - 1;
		ip1 = i__ + 1;
		jm1 = j - 1;
		jp1 = j + 1;
		km1 = k - 1;
		kp1 = k + 1;
		iim1 = ii - 1;
		iip1 = ii + 1;
		jjm1 = jj - 1;
		jjp1 = jj + 1;
		kkm1 = kk - 1;
		kkp1 = kk + 1;
/* * */
/* * ******************************************************************** */
/* * *** > oC; */
/* * ******************************************************************** */
/* * ***XoC(ii,jj,kk) = */
		tmp1_xoc__ = ups[ii + (jj + kk * ups_dim2) * ups_dim1] * ups[
			ii + (jj + kk * ups_dim2) * ups_dim1] * oc[i__ + (jm1 
			+ kp1 * oc_dim2) * oc_dim1] + dpsw[ii + (jj + kk * 
			dpsw_dim2) * dpsw_dim1] * dpsw[ii + (jj + kk * 
			dpsw_dim2) * dpsw_dim1] * oc[im1 + (jm1 + km1 * 
			oc_dim2) * oc_dim1] + opsw[ii + (jj + kk * opsw_dim2) 
			* opsw_dim1] * opsw[ii + (jj + kk * opsw_dim2) * 
			opsw_dim1] * oc[im1 + (jm1 + k * oc_dim2) * oc_dim1] 
			+ upsw[ii + (jj + kk * upsw_dim2) * upsw_dim1] * upsw[
			ii + (jj + kk * upsw_dim2) * upsw_dim1] * oc[im1 + (
			jm1 + kp1 * oc_dim2) * oc_dim1] + dpw[ii + (jj + kk * 
			dpw_dim2) * dpw_dim1] * dpw[ii + (jj + kk * dpw_dim2) 
			* dpw_dim1] * oc[im1 + (j + km1 * oc_dim2) * oc_dim1] 
			+ opw[ii + (jj + kk * opw_dim2) * opw_dim1] * opw[ii 
			+ (jj + kk * opw_dim2) * opw_dim1] * oc[im1 + (j + k *
			 oc_dim2) * oc_dim1] + upnw[ii + (jj + kk * upnw_dim2)
			 * upnw_dim1] * upnw[ii + (jj + kk * upnw_dim2) * 
			upnw_dim1] * oc[im1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 + dps[ii + (jj + kk * dps_dim2) * dps_dim1] * dps[ii 
			+ (jj + kk * dps_dim2) * dps_dim1] * oc[i__ + (jm1 + 
			km1 * oc_dim2) * oc_dim1] + ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] * ops[ii + (jj + kk * ops_dim2) 
			* ops_dim1] * oc[i__ + (jm1 + k * oc_dim2) * oc_dim1];
		tmp2_xoc__ = dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] * dpc[
			ii + (jj + kk * dpc_dim2) * dpc_dim1] * oc[i__ + (j + 
			km1 * oc_dim2) * oc_dim1] + opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] * opc[ii + (jj + kk * opc_dim2) 
			* opc_dim1] * oc[i__ + (j + k * oc_dim2) * oc_dim1] + 
			upc[ii + (jj + kk * upc_dim2) * upc_dim1] * upc[ii + (
			jj + kk * upc_dim2) * upc_dim1] * oc[i__ + (j + kp1 * 
			oc_dim2) * oc_dim1] + dpn[ii + (jj + kk * dpn_dim2) * 
			dpn_dim1] * dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] 
			* oc[i__ + (jp1 + km1 * oc_dim2) * oc_dim1] + opn[ii 
			+ (jj + kk * opn_dim2) * opn_dim1] * opn[ii + (jj + 
			kk * opn_dim2) * opn_dim1] * oc[i__ + (jp1 + k * 
			oc_dim2) * oc_dim1] + upw[ii + (jj + kk * upw_dim2) * 
			upw_dim1] * upw[ii + (jj + kk * upw_dim2) * upw_dim1] 
			* oc[im1 + (j + kp1 * oc_dim2) * oc_dim1] + dpnw[ii + 
			(jj + kk * dpnw_dim2) * dpnw_dim1] * dpnw[ii + (jj + 
			kk * dpnw_dim2) * dpnw_dim1] * oc[im1 + (jp1 + km1 * 
			oc_dim2) * oc_dim1] + opnw[ii + (jj + kk * opnw_dim2) 
			* opnw_dim1] * opnw[ii + (jj + kk * opnw_dim2) * 
			opnw_dim1] * oc[im1 + (jp1 + k * oc_dim2) * oc_dim1] 
			+ ope[ii + (jj + kk * ope_dim2) * ope_dim1] * ope[ii 
			+ (jj + kk * ope_dim2) * ope_dim1] * oc[ip1 + (j + k *
			 oc_dim2) * oc_dim1];
		tmp3_xoc__ = upe[ii + (jj + kk * upe_dim2) * upe_dim1] * upe[
			ii + (jj + kk * upe_dim2) * upe_dim1] * oc[ip1 + (j + 
			kp1 * oc_dim2) * oc_dim1] + dpne[ii + (jj + kk * 
			dpne_dim2) * dpne_dim1] * dpne[ii + (jj + kk * 
			dpne_dim2) * dpne_dim1] * oc[ip1 + (jp1 + km1 * 
			oc_dim2) * oc_dim1] + opne[ii + (jj + kk * opne_dim2) 
			* opne_dim1] * opne[ii + (jj + kk * opne_dim2) * 
			opne_dim1] * oc[ip1 + (jp1 + k * oc_dim2) * oc_dim1] 
			+ upne[ii + (jj + kk * upne_dim2) * upne_dim1] * upne[
			ii + (jj + kk * upne_dim2) * upne_dim1] * oc[ip1 + (
			jp1 + kp1 * oc_dim2) * oc_dim1] + upn[ii + (jj + kk * 
			upn_dim2) * upn_dim1] * upn[ii + (jj + kk * upn_dim2) 
			* upn_dim1] * oc[i__ + (jp1 + kp1 * oc_dim2) * 
			oc_dim1] + dpse[ii + (jj + kk * dpse_dim2) * 
			dpse_dim1] * dpse[ii + (jj + kk * dpse_dim2) * 
			dpse_dim1] * oc[ip1 + (jm1 + km1 * oc_dim2) * oc_dim1]
			 + opse[ii + (jj + kk * opse_dim2) * opse_dim1] * 
			opse[ii + (jj + kk * opse_dim2) * opse_dim1] * oc[ip1 
			+ (jm1 + k * oc_dim2) * oc_dim1] + upse[ii + (jj + kk 
			* upse_dim2) * upse_dim1] * upse[ii + (jj + kk * 
			upse_dim2) * upse_dim1] * oc[ip1 + (jm1 + kp1 * 
			oc_dim2) * oc_dim1] + dpe[ii + (jj + kk * dpe_dim2) * 
			dpe_dim1] * dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] 
			* oc[ip1 + (j + km1 * oc_dim2) * oc_dim1];
		xoc[ii + (jj + kk * xoc_dim2) * xoc_dim1] = tmp1_xoc__ + 
			tmp2_xoc__ + tmp3_xoc__;
/* * ******************************************************************** */
/* * *** > oE; */
/* * ******************************************************************** */
		xoe[ii + (jj + kk * xoe_dim2) * xoe_dim1] = -dpse[ii + (jj + 
			kk * dpse_dim2) * dpse_dim1] * oc[ip1 + (jm1 + km1 * 
			oc_dim2) * oc_dim1] * dpsw[iip1 + (jj + kk * 
			dpsw_dim2) * dpsw_dim1] - opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] * oc[ip1 + (jm1 + k * oc_dim2)
			 * oc_dim1] * opsw[iip1 + (jj + kk * opsw_dim2) * 
			opsw_dim1] - upse[ii + (jj + kk * upse_dim2) * 
			upse_dim1] * oc[ip1 + (jm1 + kp1 * oc_dim2) * oc_dim1]
			 * upsw[iip1 + (jj + kk * upsw_dim2) * upsw_dim1] - 
			dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] * oc[ip1 + (
			j + km1 * oc_dim2) * oc_dim1] * dpw[iip1 + (jj + kk * 
			dpw_dim2) * dpw_dim1] - ope[ii + (jj + kk * ope_dim2) 
			* ope_dim1] * oc[ip1 + (j + k * oc_dim2) * oc_dim1] * 
			opw[iip1 + (jj + kk * opw_dim2) * opw_dim1] - upe[ii 
			+ (jj + kk * upe_dim2) * upe_dim1] * oc[ip1 + (j + 
			kp1 * oc_dim2) * oc_dim1] * upw[iip1 + (jj + kk * 
			upw_dim2) * upw_dim1] - dpne[ii + (jj + kk * 
			dpne_dim2) * dpne_dim1] * oc[ip1 + (jp1 + km1 * 
			oc_dim2) * oc_dim1] * dpnw[iip1 + (jj + kk * 
			dpnw_dim2) * dpnw_dim1] - opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1] * oc[ip1 + (jp1 + k * oc_dim2)
			 * oc_dim1] * opnw[iip1 + (jj + kk * opnw_dim2) * 
			opnw_dim1] - upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1] * oc[ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * upnw[iip1 + (jj + kk * upnw_dim2) * upnw_dim1];
/* * ******************************************************************** */
/* * *** > oN; */
/* * ******************************************************************** */
		xon[ii + (jj + kk * xon_dim2) * xon_dim1] = -dpnw[ii + (jj + 
			kk * dpnw_dim2) * dpnw_dim1] * oc[im1 + (jp1 + km1 * 
			oc_dim2) * oc_dim1] * dpsw[ii + (jjp1 + kk * 
			dpsw_dim2) * dpsw_dim1] - opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] * oc[im1 + (jp1 + k * oc_dim2)
			 * oc_dim1] * opsw[ii + (jjp1 + kk * opsw_dim2) * 
			opsw_dim1] - upnw[ii + (jj + kk * upnw_dim2) * 
			upnw_dim1] * oc[im1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * upsw[ii + (jjp1 + kk * upsw_dim2) * upsw_dim1] - 
			dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] * oc[i__ + (
			jp1 + km1 * oc_dim2) * oc_dim1] * dps[ii + (jjp1 + kk 
			* dps_dim2) * dps_dim1] - opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] * oc[i__ + (jp1 + k * oc_dim2) *
			 oc_dim1] * ops[ii + (jjp1 + kk * ops_dim2) * 
			ops_dim1] - upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			* oc[i__ + (jp1 + kp1 * oc_dim2) * oc_dim1] * ups[ii 
			+ (jjp1 + kk * ups_dim2) * ups_dim1] - dpne[ii + (jj 
			+ kk * dpne_dim2) * dpne_dim1] * oc[ip1 + (jp1 + km1 *
			 oc_dim2) * oc_dim1] * dpse[ii + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] - opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1] * oc[ip1 + (jp1 + k * oc_dim2)
			 * oc_dim1] * opse[ii + (jjp1 + kk * opse_dim2) * 
			opse_dim1] - upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1] * oc[ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * upse[ii + (jjp1 + kk * upse_dim2) * upse_dim1];
/* * ******************************************************************** */
/* * *** > uC; */
/* * ******************************************************************** */
		xuc[ii + (jj + kk * xuc_dim2) * xuc_dim1] = -dpsw[ii + (jj + 
			kkp1 * dpsw_dim2) * dpsw_dim1] * oc[im1 + (jm1 + kp1 *
			 oc_dim2) * oc_dim1] * upsw[ii + (jj + kk * upsw_dim2)
			 * upsw_dim1] - dpw[ii + (jj + kkp1 * dpw_dim2) * 
			dpw_dim1] * oc[im1 + (j + kp1 * oc_dim2) * oc_dim1] * 
			upw[ii + (jj + kk * upw_dim2) * upw_dim1] - dpnw[ii + 
			(jj + kkp1 * dpnw_dim2) * dpnw_dim1] * oc[im1 + (jp1 
			+ kp1 * oc_dim2) * oc_dim1] * upnw[ii + (jj + kk * 
			upnw_dim2) * upnw_dim1] - dps[ii + (jj + kkp1 * 
			dps_dim2) * dps_dim1] * oc[i__ + (jm1 + kp1 * oc_dim2)
			 * oc_dim1] * ups[ii + (jj + kk * ups_dim2) * 
			ups_dim1] - dpc[ii + (jj + kkp1 * dpc_dim2) * 
			dpc_dim1] * oc[i__ + (j + kp1 * oc_dim2) * oc_dim1] * 
			upc[ii + (jj + kk * upc_dim2) * upc_dim1] - dpn[ii + (
			jj + kkp1 * dpn_dim2) * dpn_dim1] * oc[i__ + (jp1 + 
			kp1 * oc_dim2) * oc_dim1] * upn[ii + (jj + kk * 
			upn_dim2) * upn_dim1] - dpse[ii + (jj + kkp1 * 
			dpse_dim2) * dpse_dim1] * oc[ip1 + (jm1 + kp1 * 
			oc_dim2) * oc_dim1] * upse[ii + (jj + kk * upse_dim2) 
			* upse_dim1] - dpe[ii + (jj + kkp1 * dpe_dim2) * 
			dpe_dim1] * oc[ip1 + (j + kp1 * oc_dim2) * oc_dim1] * 
			upe[ii + (jj + kk * upe_dim2) * upe_dim1] - dpne[ii + 
			(jj + kkp1 * dpne_dim2) * dpne_dim1] * oc[ip1 + (jp1 
			+ kp1 * oc_dim2) * oc_dim1] * upne[ii + (jj + kk * 
			upne_dim2) * upne_dim1];
/* * ******************************************************************** */
/* * *** > oNE; */
/* * ******************************************************************** */
		xone[ii + (jj + kk * xone_dim2) * xone_dim1] = -dpne[ii + (jj 
			+ kk * dpne_dim2) * dpne_dim1] * oc[ip1 + (jp1 + km1 *
			 oc_dim2) * oc_dim1] * dpsw[iip1 + (jjp1 + kk * 
			dpsw_dim2) * dpsw_dim1] - opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1] * oc[ip1 + (jp1 + k * oc_dim2)
			 * oc_dim1] * opsw[iip1 + (jjp1 + kk * opsw_dim2) * 
			opsw_dim1] - upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1] * oc[ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * upsw[iip1 + (jjp1 + kk * upsw_dim2) * upsw_dim1];
/* * ******************************************************************** */
/* * *** > oNW; */
/* * ******************************************************************** */
		xonw[ii + (jj + kk * xonw_dim2) * xonw_dim1] = -dpnw[ii + (jj 
			+ kk * dpnw_dim2) * dpnw_dim1] * oc[im1 + (jp1 + km1 *
			 oc_dim2) * oc_dim1] * dpse[iim1 + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] - opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] * oc[im1 + (jp1 + k * oc_dim2)
			 * oc_dim1] * opse[iim1 + (jjp1 + kk * opse_dim2) * 
			opse_dim1] - upnw[ii + (jj + kk * upnw_dim2) * 
			upnw_dim1] * oc[im1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * upse[iim1 + (jjp1 + kk * upse_dim2) * upse_dim1];
/* * ******************************************************************** */
/* * *** > uE; */
/* * ******************************************************************** */
		xue[ii + (jj + kk * xue_dim2) * xue_dim1] = -upse[ii + (jj + 
			kk * upse_dim2) * upse_dim1] * oc[ip1 + (jm1 + kp1 * 
			oc_dim2) * oc_dim1] * dpsw[iip1 + (jj + kkp1 * 
			dpsw_dim2) * dpsw_dim1] - upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1] * oc[ip1 + (j + kp1 * oc_dim2) *
			 oc_dim1] * dpw[iip1 + (jj + kkp1 * dpw_dim2) * 
			dpw_dim1] - upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1] * oc[ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * dpnw[iip1 + (jj + kkp1 * dpnw_dim2) * dpnw_dim1];
/* * ******************************************************************** */
/* * *** > uW; */
/* * ******************************************************************** */
		xuw[ii + (jj + kk * xuw_dim2) * xuw_dim1] = -upsw[ii + (jj + 
			kk * upsw_dim2) * upsw_dim1] * oc[im1 + (jm1 + kp1 * 
			oc_dim2) * oc_dim1] * dpse[iim1 + (jj + kkp1 * 
			dpse_dim2) * dpse_dim1] - upw[ii + (jj + kk * 
			upw_dim2) * upw_dim1] * oc[im1 + (j + kp1 * oc_dim2) *
			 oc_dim1] * dpe[iim1 + (jj + kkp1 * dpe_dim2) * 
			dpe_dim1] - upnw[ii + (jj + kk * upnw_dim2) * 
			upnw_dim1] * oc[im1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * dpne[iim1 + (jj + kkp1 * dpne_dim2) * dpne_dim1];
/* * ******************************************************************** */
/* * *** > uN; */
/* * ******************************************************************** */
		xun[ii + (jj + kk * xun_dim2) * xun_dim1] = -upnw[ii + (jj + 
			kk * upnw_dim2) * upnw_dim1] * oc[im1 + (jp1 + kp1 * 
			oc_dim2) * oc_dim1] * dpsw[ii + (jjp1 + kkp1 * 
			dpsw_dim2) * dpsw_dim1] - upn[ii + (jj + kk * 
			upn_dim2) * upn_dim1] * oc[i__ + (jp1 + kp1 * oc_dim2)
			 * oc_dim1] * dps[ii + (jjp1 + kkp1 * dps_dim2) * 
			dps_dim1] - upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1] * oc[ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * dpse[ii + (jjp1 + kkp1 * dpse_dim2) * dpse_dim1];
/* * ******************************************************************** */
/* * *** > uS; */
/* * ******************************************************************** */
		xus[ii + (jj + kk * xus_dim2) * xus_dim1] = -upsw[ii + (jj + 
			kk * upsw_dim2) * upsw_dim1] * oc[im1 + (jm1 + kp1 * 
			oc_dim2) * oc_dim1] * dpnw[ii + (jjm1 + kkp1 * 
			dpnw_dim2) * dpnw_dim1] - ups[ii + (jj + kk * 
			ups_dim2) * ups_dim1] * oc[i__ + (jm1 + kp1 * oc_dim2)
			 * oc_dim1] * dpn[ii + (jjm1 + kkp1 * dpn_dim2) * 
			dpn_dim1] - upse[ii + (jj + kk * upse_dim2) * 
			upse_dim1] * oc[ip1 + (jm1 + kp1 * oc_dim2) * oc_dim1]
			 * dpne[ii + (jjm1 + kkp1 * dpne_dim2) * dpne_dim1];
/* * ******************************************************************** */
/* * *** > uNE; */
/* * ******************************************************************** */
		xune[ii + (jj + kk * xune_dim2) * xune_dim1] = -upne[ii + (jj 
			+ kk * upne_dim2) * upne_dim1] * oc[ip1 + (jp1 + kp1 *
			 oc_dim2) * oc_dim1] * dpsw[iip1 + (jjp1 + kkp1 * 
			dpsw_dim2) * dpsw_dim1];
/* * ******************************************************************** */
/* * *** > uNW; */
/* * ******************************************************************** */
		xunw[ii + (jj + kk * xunw_dim2) * xunw_dim1] = -upnw[ii + (jj 
			+ kk * upnw_dim2) * upnw_dim1] * oc[im1 + (jp1 + kp1 *
			 oc_dim2) * oc_dim1] * dpse[iim1 + (jjp1 + kkp1 * 
			dpse_dim2) * dpse_dim1];
/* * ******************************************************************** */
/* * *** > uSE; */
/* * ******************************************************************** */
		xuse[ii + (jj + kk * xuse_dim2) * xuse_dim1] = -upse[ii + (jj 
			+ kk * upse_dim2) * upse_dim1] * oc[ip1 + (jm1 + kp1 *
			 oc_dim2) * oc_dim1] * dpnw[iip1 + (jjm1 + kkp1 * 
			dpnw_dim2) * dpnw_dim1];
/* * ******************************************************************** */
/* * *** > uSW; */
/* * ******************************************************************** */
		xusw[ii + (jj + kk * xusw_dim2) * xusw_dim1] = -upsw[ii + (jj 
			+ kk * upsw_dim2) * upsw_dim1] * oc[im1 + (jm1 + kp1 *
			 oc_dim2) * oc_dim1] * dpne[iim1 + (jjm1 + kkp1 * 
			dpne_dim2) * dpne_dim1];
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
} /* buildg_1__ */

/* Subroutine */ int buildg_7__(integer *nxf, integer *nyf, integer *nzf, 
	integer *nx, integer *ny, integer *nz, doublereal *opc, doublereal *
	opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *
	opne, doublereal *opnw, doublereal *opse, doublereal *opsw, 
	doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, 
	doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse,
	 doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, 
	doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, 
	doublereal *dpse, doublereal *dpsw, doublereal *oc, doublereal *oe, 
	doublereal *on, doublereal *uc, doublereal *xoc, doublereal *xoe, 
	doublereal *xon, doublereal *xuc, doublereal *xone, doublereal *xonw, 
	doublereal *xue, doublereal *xuw, doublereal *xun, doublereal *xus, 
	doublereal *xune, doublereal *xunw, doublereal *xuse, doublereal *
	xusw)
{
    /* System generated locals */
    integer oc_dim1, oc_dim2, oc_offset, oe_dim1, oe_dim2, oe_offset, on_dim1,
	     on_dim2, on_offset, uc_dim1, uc_dim2, uc_offset, xoc_dim1, 
	    xoc_dim2, xoc_offset, xoe_dim1, xoe_dim2, xoe_offset, xon_dim1, 
	    xon_dim2, xon_offset, xuc_dim1, xuc_dim2, xuc_offset, xone_dim1, 
	    xone_dim2, xone_offset, xonw_dim1, xonw_dim2, xonw_offset, 
	    xue_dim1, xue_dim2, xue_offset, xuw_dim1, xuw_dim2, xuw_offset, 
	    xun_dim1, xun_dim2, xun_offset, xus_dim1, xus_dim2, xus_offset, 
	    xune_dim1, xune_dim2, xune_offset, xunw_dim1, xunw_dim2, 
	    xunw_offset, xuse_dim1, xuse_dim2, xuse_offset, xusw_dim1, 
	    xusw_dim2, xusw_offset, opc_dim1, opc_dim2, opc_offset, opn_dim1, 
	    opn_dim2, opn_offset, ops_dim1, ops_dim2, ops_offset, ope_dim1, 
	    ope_dim2, ope_offset, opw_dim1, opw_dim2, opw_offset, opne_dim1, 
	    opne_dim2, opne_offset, opnw_dim1, opnw_dim2, opnw_offset, 
	    opse_dim1, opse_dim2, opse_offset, opsw_dim1, opsw_dim2, 
	    opsw_offset, upc_dim1, upc_dim2, upc_offset, upn_dim1, upn_dim2, 
	    upn_offset, ups_dim1, ups_dim2, ups_offset, upe_dim1, upe_dim2, 
	    upe_offset, upw_dim1, upw_dim2, upw_offset, upne_dim1, upne_dim2, 
	    upne_offset, upnw_dim1, upnw_dim2, upnw_offset, upse_dim1, 
	    upse_dim2, upse_offset, upsw_dim1, upsw_dim2, upsw_offset, 
	    dpc_dim1, dpc_dim2, dpc_offset, dpn_dim1, dpn_dim2, dpn_offset, 
	    dps_dim1, dps_dim2, dps_offset, dpe_dim1, dpe_dim2, dpe_offset, 
	    dpw_dim1, dpw_dim2, dpw_offset, dpne_dim1, dpne_dim2, dpne_offset,
	     dpnw_dim1, dpnw_dim2, dpnw_offset, dpse_dim1, dpse_dim2, 
	    dpse_offset, dpsw_dim1, dpsw_dim2, dpsw_offset, i__1, i__2, i__3;

    /* Local variables */
    static doublereal tmp1_xoc__, tmp2_xoc__, tmp3_xoc__, tmp4_xoc__, 
	    tmp5_xoc__, tmp6_xoc__, tmp7_xoc__, tmp8_xoc__, tmp9_xoc__, 
	    tmp1_xoe__, tmp2_xoe__, tmp3_xoe__, tmp4_xoe__, tmp1_xon__, 
	    tmp2_xon__, tmp3_xon__, tmp4_xon__, tmp1_xuc__, tmp2_xuc__, 
	    tmp3_xuc__, tmp4_xuc__;
    static integer i__, j, k, ii, jj, kk, im1, im2, jm1, ip1, ip2, jp1, jm2, 
	    jp2, km1, kp1, km2, kp2, iim1, jjm1, iip1, kkm1, jjp1, kkp1, nxm1,
	     nym1, nzm1;

/* * ******************************************************************** */
/* * purpose: compute a 27-point galerkin coarse grid matrix from */
/* *          a 7-point fine grid matrix. */
/* * */
/* * expressions for the galerkin coarse grid stencil XA in terms of */
/* * the fine grid matrix stencil A and the interpolation operator */
/* * stencil P.  these stencils have the form: */
/* * */
/* *    XA := array([ */
/* * */
/* *      matrix([ */
/* *         [ -XdNW(i,j,k), -XdN(i,j,k), -XdNE(i,j,k) ], */
/* *         [ -XdW(i,j,k),  -XdC(i,j,k), -XdE(i,j,k)  ], */
/* *         [ -XdSW(i,j,k), -XdS(i,j,k), -XdSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ -XoNW(i,j,k), -XoN(i,j,k), -XoNE(i,j,k) ], */
/* *         [ -XoW(i,j,k),   XoC(i,j,k), -XoE(i,j,k)  ], */
/* *         [ -XoSW(i,j,k), -XoS(i,j,k), -XoSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ -XuNW(i,j,k), -XuN(i,j,k), -XuNE(i,j,k) ], */
/* *         [ -XuW(i,j,k),  -XuC(i,j,k), -XuE(i,j,k)  ], */
/* *         [ -XuSW(i,j,k), -XuS(i,j,k), -XuSE(i,j,k) ] */
/* *      ]) */
/* *    ]): */
/* * */
/* *    A := array([ */
/* * */
/* *      matrix([ */
/* *         [  0,           0,          0          ], */
/* *         [  0,          -dC(i,j,k),  0          ], */
/* *         [  0,           0,          0          ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [  0,          -oN(i,j,k),  0          ], */
/* *         [ -oW(i,j,k),   oC(i,j,k), -oE(i,j,k)  ], */
/* *         [  0,          -oS(i,j,k),  0          ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [  0,           0,          0          ], */
/* *         [  0,          -uC(i,j,k),  0          ], */
/* *         [  0,           0,          0          ] */
/* *      ]) */
/* * */
/* *   P := array([ */
/* * */
/* *      matrix([ */
/* *         [ dPNW(i,j,k), dPN(i,j,k), dPNE(i,j,k) ], */
/* *         [ dPW(i,j,k),  dPC(i,j,k), dPE(i,j,k)  ], */
/* *         [ dPSW(i,j,k), dPS(i,j,k), dPSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ oPNW(i,j,k), oPN(i,j,k), oPNE(i,j,k) ], */
/* *         [ oPW(i,j,k),  oPC(i,j,k), oPE(i,j,k)  ], */
/* *         [ oPSW(i,j,k), oPS(i,j,k), oPSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ uPNW(i,j,k), uPN(i,j,k), uPNE(i,j,k) ], */
/* *         [ uPW(i,j,k),  uPC(i,j,k), uPE(i,j,k)  ], */
/* *         [ uPSW(i,j,k), uPS(i,j,k), uPSE(i,j,k) ] */
/* *      ]) */
/* *    ]): */
/* * */
/* * in addition, A is assumed to be symmetric so that: */
/* * */
/* *    oS  := proc(x,y,z) RETURN( oN(x,y-1,z) ): end: */
/* *    oW  := proc(x,y,z) RETURN( oE(x-1,y,z) ): end: */
/* *    dC  := proc(x,y,z) RETURN( uC(x,y,z-1) ): end: */
/* * */
/* * author:  michael holst */
/* * ******************************************************************** */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** define n and determine number of mesh points *** */
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
    xusw_dim1 = *nx;
    xusw_dim2 = *ny;
    xusw_offset = 1 + xusw_dim1 * (1 + xusw_dim2);
    xusw -= xusw_offset;
    xuse_dim1 = *nx;
    xuse_dim2 = *ny;
    xuse_offset = 1 + xuse_dim1 * (1 + xuse_dim2);
    xuse -= xuse_offset;
    xunw_dim1 = *nx;
    xunw_dim2 = *ny;
    xunw_offset = 1 + xunw_dim1 * (1 + xunw_dim2);
    xunw -= xunw_offset;
    xune_dim1 = *nx;
    xune_dim2 = *ny;
    xune_offset = 1 + xune_dim1 * (1 + xune_dim2);
    xune -= xune_offset;
    xus_dim1 = *nx;
    xus_dim2 = *ny;
    xus_offset = 1 + xus_dim1 * (1 + xus_dim2);
    xus -= xus_offset;
    xun_dim1 = *nx;
    xun_dim2 = *ny;
    xun_offset = 1 + xun_dim1 * (1 + xun_dim2);
    xun -= xun_offset;
    xuw_dim1 = *nx;
    xuw_dim2 = *ny;
    xuw_offset = 1 + xuw_dim1 * (1 + xuw_dim2);
    xuw -= xuw_offset;
    xue_dim1 = *nx;
    xue_dim2 = *ny;
    xue_offset = 1 + xue_dim1 * (1 + xue_dim2);
    xue -= xue_offset;
    xonw_dim1 = *nx;
    xonw_dim2 = *ny;
    xonw_offset = 1 + xonw_dim1 * (1 + xonw_dim2);
    xonw -= xonw_offset;
    xone_dim1 = *nx;
    xone_dim2 = *ny;
    xone_offset = 1 + xone_dim1 * (1 + xone_dim2);
    xone -= xone_offset;
    xuc_dim1 = *nx;
    xuc_dim2 = *ny;
    xuc_offset = 1 + xuc_dim1 * (1 + xuc_dim2);
    xuc -= xuc_offset;
    xon_dim1 = *nx;
    xon_dim2 = *ny;
    xon_offset = 1 + xon_dim1 * (1 + xon_dim2);
    xon -= xon_offset;
    xoe_dim1 = *nx;
    xoe_dim2 = *ny;
    xoe_offset = 1 + xoe_dim1 * (1 + xoe_dim2);
    xoe -= xoe_offset;
    xoc_dim1 = *nx;
    xoc_dim2 = *ny;
    xoc_offset = 1 + xoc_dim1 * (1 + xoc_dim2);
    xoc -= xoc_offset;
    dpsw_dim1 = *nx;
    dpsw_dim2 = *ny;
    dpsw_offset = 1 + dpsw_dim1 * (1 + dpsw_dim2);
    dpsw -= dpsw_offset;
    dpse_dim1 = *nx;
    dpse_dim2 = *ny;
    dpse_offset = 1 + dpse_dim1 * (1 + dpse_dim2);
    dpse -= dpse_offset;
    dpnw_dim1 = *nx;
    dpnw_dim2 = *ny;
    dpnw_offset = 1 + dpnw_dim1 * (1 + dpnw_dim2);
    dpnw -= dpnw_offset;
    dpne_dim1 = *nx;
    dpne_dim2 = *ny;
    dpne_offset = 1 + dpne_dim1 * (1 + dpne_dim2);
    dpne -= dpne_offset;
    dpw_dim1 = *nx;
    dpw_dim2 = *ny;
    dpw_offset = 1 + dpw_dim1 * (1 + dpw_dim2);
    dpw -= dpw_offset;
    dpe_dim1 = *nx;
    dpe_dim2 = *ny;
    dpe_offset = 1 + dpe_dim1 * (1 + dpe_dim2);
    dpe -= dpe_offset;
    dps_dim1 = *nx;
    dps_dim2 = *ny;
    dps_offset = 1 + dps_dim1 * (1 + dps_dim2);
    dps -= dps_offset;
    dpn_dim1 = *nx;
    dpn_dim2 = *ny;
    dpn_offset = 1 + dpn_dim1 * (1 + dpn_dim2);
    dpn -= dpn_offset;
    dpc_dim1 = *nx;
    dpc_dim2 = *ny;
    dpc_offset = 1 + dpc_dim1 * (1 + dpc_dim2);
    dpc -= dpc_offset;
    upsw_dim1 = *nx;
    upsw_dim2 = *ny;
    upsw_offset = 1 + upsw_dim1 * (1 + upsw_dim2);
    upsw -= upsw_offset;
    upse_dim1 = *nx;
    upse_dim2 = *ny;
    upse_offset = 1 + upse_dim1 * (1 + upse_dim2);
    upse -= upse_offset;
    upnw_dim1 = *nx;
    upnw_dim2 = *ny;
    upnw_offset = 1 + upnw_dim1 * (1 + upnw_dim2);
    upnw -= upnw_offset;
    upne_dim1 = *nx;
    upne_dim2 = *ny;
    upne_offset = 1 + upne_dim1 * (1 + upne_dim2);
    upne -= upne_offset;
    upw_dim1 = *nx;
    upw_dim2 = *ny;
    upw_offset = 1 + upw_dim1 * (1 + upw_dim2);
    upw -= upw_offset;
    upe_dim1 = *nx;
    upe_dim2 = *ny;
    upe_offset = 1 + upe_dim1 * (1 + upe_dim2);
    upe -= upe_offset;
    ups_dim1 = *nx;
    ups_dim2 = *ny;
    ups_offset = 1 + ups_dim1 * (1 + ups_dim2);
    ups -= ups_offset;
    upn_dim1 = *nx;
    upn_dim2 = *ny;
    upn_offset = 1 + upn_dim1 * (1 + upn_dim2);
    upn -= upn_offset;
    upc_dim1 = *nx;
    upc_dim2 = *ny;
    upc_offset = 1 + upc_dim1 * (1 + upc_dim2);
    upc -= upc_offset;
    opsw_dim1 = *nx;
    opsw_dim2 = *ny;
    opsw_offset = 1 + opsw_dim1 * (1 + opsw_dim2);
    opsw -= opsw_offset;
    opse_dim1 = *nx;
    opse_dim2 = *ny;
    opse_offset = 1 + opse_dim1 * (1 + opse_dim2);
    opse -= opse_offset;
    opnw_dim1 = *nx;
    opnw_dim2 = *ny;
    opnw_offset = 1 + opnw_dim1 * (1 + opnw_dim2);
    opnw -= opnw_offset;
    opne_dim1 = *nx;
    opne_dim2 = *ny;
    opne_offset = 1 + opne_dim1 * (1 + opne_dim2);
    opne -= opne_offset;
    opw_dim1 = *nx;
    opw_dim2 = *ny;
    opw_offset = 1 + opw_dim1 * (1 + opw_dim2);
    opw -= opw_offset;
    ope_dim1 = *nx;
    ope_dim2 = *ny;
    ope_offset = 1 + ope_dim1 * (1 + ope_dim2);
    ope -= ope_offset;
    ops_dim1 = *nx;
    ops_dim2 = *ny;
    ops_offset = 1 + ops_dim1 * (1 + ops_dim2);
    ops -= ops_offset;
    opn_dim1 = *nx;
    opn_dim2 = *ny;
    opn_offset = 1 + opn_dim1 * (1 + opn_dim2);
    opn -= opn_offset;
    opc_dim1 = *nx;
    opc_dim2 = *ny;
    opc_offset = 1 + opc_dim1 * (1 + opc_dim2);
    opc -= opc_offset;

    /* Function Body */
    nxm1 = *nx - 1;
    nym1 = *ny - 1;
    nzm1 = *nz - 1;
/* * */
/* *    *** build the operator *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (kk = 2; kk <= i__1; ++kk) {
	k = (kk << 1) - 1;
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (jj = 2; jj <= i__2; ++jj) {
	    j = (jj << 1) - 1;
/* mdir 3 3 */
	    i__3 = *nx - 1;
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
/* * *** > oC; */
/* * ******************************************************************** */
/* * ***XoC(ii,jj,kk) = */
		tmp1_xoc__ = dpsw[ii + (jj + kk * dpsw_dim2) * dpsw_dim1] * (
			oc[im1 + (jm1 + km1 * oc_dim2) * oc_dim1] * dpsw[ii + 
			(jj + kk * dpsw_dim2) * dpsw_dim1] - uc[im1 + (jm1 + 
			km1 * uc_dim2) * uc_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] - on[im1 + (jm1 + km1 * 
			on_dim2) * on_dim1] * dpw[ii + (jj + kk * dpw_dim2) * 
			dpw_dim1] - oe[im1 + (jm1 + km1 * oe_dim2) * oe_dim1] 
			* dps[ii + (jj + kk * dps_dim2) * dps_dim1]) + opne[
			ii + (jj + kk * opne_dim2) * opne_dim1] * (-oe[i__ + (
			jp1 + k * oe_dim2) * oe_dim1] * opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] - on[ip1 + (j + k * on_dim2) * 
			on_dim1] * ope[ii + (jj + kk * ope_dim2) * ope_dim1] 
			- uc[ip1 + (jp1 + km1 * uc_dim2) * uc_dim1] * dpne[ii 
			+ (jj + kk * dpne_dim2) * dpne_dim1] + oc[ip1 + (jp1 
			+ k * oc_dim2) * oc_dim1] * opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1] - uc[ip1 + (jp1 + k * uc_dim2)
			 * uc_dim1] * upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1]) + dpne[ii + (jj + kk * dpne_dim2) * 
			dpne_dim1] * (-oe[i__ + (jp1 + km1 * oe_dim2) * 
			oe_dim1] * dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] 
			- on[ip1 + (j + km1 * on_dim2) * on_dim1] * dpe[ii + (
			jj + kk * dpe_dim2) * dpe_dim1] + oc[ip1 + (jp1 + km1 
			* oc_dim2) * oc_dim1] * dpne[ii + (jj + kk * 
			dpne_dim2) * dpne_dim1] - uc[ip1 + (jp1 + km1 * 
			uc_dim2) * uc_dim1] * opne[ii + (jj + kk * opne_dim2) 
			* opne_dim1]);
		tmp2_xoc__ = dpse[ii + (jj + kk * dpse_dim2) * dpse_dim1] * (
			-oe[i__ + (jm1 + km1 * oe_dim2) * oe_dim1] * dps[ii + 
			(jj + kk * dps_dim2) * dps_dim1] + oc[ip1 + (jm1 + 
			km1 * oc_dim2) * oc_dim1] * dpse[ii + (jj + kk * 
			dpse_dim2) * dpse_dim1] - uc[ip1 + (jm1 + km1 * 
			uc_dim2) * uc_dim1] * opse[ii + (jj + kk * opse_dim2) 
			* opse_dim1] - on[ip1 + (jm1 + km1 * on_dim2) * 
			on_dim1] * dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1]) 
			+ upe[ii + (jj + kk * upe_dim2) * upe_dim1] * (-oe[
			i__ + (j + kp1 * oe_dim2) * oe_dim1] * upc[ii + (jj + 
			kk * upc_dim2) * upc_dim1] - on[ip1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * upse[ii + (jj + kk * upse_dim2) 
			* upse_dim1] - uc[ip1 + (j + k * uc_dim2) * uc_dim1] *
			 ope[ii + (jj + kk * ope_dim2) * ope_dim1] + oc[ip1 + 
			(j + kp1 * oc_dim2) * oc_dim1] * upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1] - on[ip1 + (j + kp1 * on_dim2) *
			 on_dim1] * upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1]) + ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1] * (-oe[i__ + (j + k * oe_dim2) * oe_dim1] * 
			opc[ii + (jj + kk * opc_dim2) * opc_dim1] - on[ip1 + (
			jm1 + k * on_dim2) * on_dim1] * opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] - uc[ip1 + (j + km1 * uc_dim2)
			 * uc_dim1] * dpe[ii + (jj + kk * dpe_dim2) * 
			dpe_dim1] + oc[ip1 + (j + k * oc_dim2) * oc_dim1] * 
			ope[ii + (jj + kk * ope_dim2) * ope_dim1] - uc[ip1 + (
			j + k * uc_dim2) * uc_dim1] * upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1] - on[ip1 + (j + k * on_dim2) * 
			on_dim1] * opne[ii + (jj + kk * opne_dim2) * 
			opne_dim1]);
		tmp3_xoc__ = dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] * (-oe[
			i__ + (j + km1 * oe_dim2) * oe_dim1] * dpc[ii + (jj + 
			kk * dpc_dim2) * dpc_dim1] - on[ip1 + (jm1 + km1 * 
			on_dim2) * on_dim1] * dpse[ii + (jj + kk * dpse_dim2) 
			* dpse_dim1] + oc[ip1 + (j + km1 * oc_dim2) * oc_dim1]
			 * dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] - uc[ip1 
			+ (j + km1 * uc_dim2) * uc_dim1] * ope[ii + (jj + kk *
			 ope_dim2) * ope_dim1] - on[ip1 + (j + km1 * on_dim2) 
			* on_dim1] * dpne[ii + (jj + kk * dpne_dim2) * 
			dpne_dim1]) + upse[ii + (jj + kk * upse_dim2) * 
			upse_dim1] * (-oe[i__ + (jm1 + kp1 * oe_dim2) * 
			oe_dim1] * ups[ii + (jj + kk * ups_dim2) * ups_dim1] 
			- uc[ip1 + (jm1 + k * uc_dim2) * uc_dim1] * opse[ii + 
			(jj + kk * opse_dim2) * opse_dim1] + oc[ip1 + (jm1 + 
			kp1 * oc_dim2) * oc_dim1] * upse[ii + (jj + kk * 
			upse_dim2) * upse_dim1] - on[ip1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * upe[ii + (jj + kk * upe_dim2) * 
			upe_dim1]) + upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1] * (-oe[i__ + (jp1 + kp1 * oe_dim2) * 
			oe_dim1] * upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			- on[ip1 + (j + kp1 * on_dim2) * on_dim1] * upe[ii + (
			jj + kk * upe_dim2) * upe_dim1] - uc[ip1 + (jp1 + k * 
			uc_dim2) * uc_dim1] * opne[ii + (jj + kk * opne_dim2) 
			* opne_dim1] + oc[ip1 + (jp1 + kp1 * oc_dim2) * 
			oc_dim1] * upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1]);
		tmp4_xoc__ = ops[ii + (jj + kk * ops_dim2) * ops_dim1] * (-oe[
			im1 + (jm1 + k * oe_dim2) * oe_dim1] * opsw[ii + (jj 
			+ kk * opsw_dim2) * opsw_dim1] - uc[i__ + (jm1 + km1 *
			 uc_dim2) * uc_dim1] * dps[ii + (jj + kk * dps_dim2) *
			 dps_dim1] + oc[i__ + (jm1 + k * oc_dim2) * oc_dim1] *
			 ops[ii + (jj + kk * ops_dim2) * ops_dim1] - uc[i__ + 
			(jm1 + k * uc_dim2) * uc_dim1] * ups[ii + (jj + kk * 
			ups_dim2) * ups_dim1] - on[i__ + (jm1 + k * on_dim2) *
			 on_dim1] * opc[ii + (jj + kk * opc_dim2) * opc_dim1] 
			- oe[i__ + (jm1 + k * oe_dim2) * oe_dim1] * opse[ii + 
			(jj + kk * opse_dim2) * opse_dim1]) + dps[ii + (jj + 
			kk * dps_dim2) * dps_dim1] * (-oe[im1 + (jm1 + km1 * 
			oe_dim2) * oe_dim1] * dpsw[ii + (jj + kk * dpsw_dim2) 
			* dpsw_dim1] + oc[i__ + (jm1 + km1 * oc_dim2) * 
			oc_dim1] * dps[ii + (jj + kk * dps_dim2) * dps_dim1] 
			- uc[i__ + (jm1 + km1 * uc_dim2) * uc_dim1] * ops[ii 
			+ (jj + kk * ops_dim2) * ops_dim1] - on[i__ + (jm1 + 
			km1 * on_dim2) * on_dim1] * dpc[ii + (jj + kk * 
			dpc_dim2) * dpc_dim1] - oe[i__ + (jm1 + km1 * oe_dim2)
			 * oe_dim1] * dpse[ii + (jj + kk * dpse_dim2) * 
			dpse_dim1]) + opse[ii + (jj + kk * opse_dim2) * 
			opse_dim1] * (-oe[i__ + (jm1 + k * oe_dim2) * oe_dim1]
			 * ops[ii + (jj + kk * ops_dim2) * ops_dim1] - uc[ip1 
			+ (jm1 + km1 * uc_dim2) * uc_dim1] * dpse[ii + (jj + 
			kk * dpse_dim2) * dpse_dim1] + oc[ip1 + (jm1 + k * 
			oc_dim2) * oc_dim1] * opse[ii + (jj + kk * opse_dim2) 
			* opse_dim1] - uc[ip1 + (jm1 + k * uc_dim2) * uc_dim1]
			 * upse[ii + (jj + kk * upse_dim2) * upse_dim1] - on[
			ip1 + (jm1 + k * on_dim2) * on_dim1] * ope[ii + (jj + 
			kk * ope_dim2) * ope_dim1]);
		tmp5_xoc__ = dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] * (-oe[
			im1 + (jp1 + km1 * oe_dim2) * oe_dim1] * dpnw[ii + (
			jj + kk * dpnw_dim2) * dpnw_dim1] - on[i__ + (j + km1 
			* on_dim2) * on_dim1] * dpc[ii + (jj + kk * dpc_dim2) 
			* dpc_dim1] + oc[i__ + (jp1 + km1 * oc_dim2) * 
			oc_dim1] * dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] 
			- uc[i__ + (jp1 + km1 * uc_dim2) * uc_dim1] * opn[ii 
			+ (jj + kk * opn_dim2) * opn_dim1] - oe[i__ + (jp1 + 
			km1 * oe_dim2) * oe_dim1] * dpne[ii + (jj + kk * 
			dpne_dim2) * dpne_dim1]) + upc[ii + (jj + kk * 
			upc_dim2) * upc_dim1] * (-oe[im1 + (j + kp1 * oe_dim2)
			 * oe_dim1] * upw[ii + (jj + kk * upw_dim2) * 
			upw_dim1] - on[i__ + (jm1 + kp1 * on_dim2) * on_dim1] 
			* ups[ii + (jj + kk * ups_dim2) * ups_dim1] - uc[i__ 
			+ (j + k * uc_dim2) * uc_dim1] * opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] + oc[i__ + (j + kp1 * oc_dim2) *
			 oc_dim1] * upc[ii + (jj + kk * upc_dim2) * upc_dim1] 
			- on[i__ + (j + kp1 * on_dim2) * on_dim1] * upn[ii + (
			jj + kk * upn_dim2) * upn_dim1] - oe[i__ + (j + kp1 * 
			oe_dim2) * oe_dim1] * upe[ii + (jj + kk * upe_dim2) * 
			upe_dim1]) + opc[ii + (jj + kk * opc_dim2) * opc_dim1]
			 * (-oe[im1 + (j + k * oe_dim2) * oe_dim1] * opw[ii + 
			(jj + kk * opw_dim2) * opw_dim1] - on[i__ + (jm1 + k *
			 on_dim2) * on_dim1] * ops[ii + (jj + kk * ops_dim2) *
			 ops_dim1] - uc[i__ + (j + km1 * uc_dim2) * uc_dim1] *
			 dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] + oc[i__ + 
			(j + k * oc_dim2) * oc_dim1] * opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] - uc[i__ + (j + k * uc_dim2) * 
			uc_dim1] * upc[ii + (jj + kk * upc_dim2) * upc_dim1] 
			- on[i__ + (j + k * on_dim2) * on_dim1] * opn[ii + (
			jj + kk * opn_dim2) * opn_dim1] - oe[i__ + (j + k * 
			oe_dim2) * oe_dim1] * ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1]);
		tmp6_xoc__ = dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] * (-oe[
			im1 + (j + km1 * oe_dim2) * oe_dim1] * dpw[ii + (jj + 
			kk * dpw_dim2) * dpw_dim1] - on[i__ + (jm1 + km1 * 
			on_dim2) * on_dim1] * dps[ii + (jj + kk * dps_dim2) * 
			dps_dim1] + oc[i__ + (j + km1 * oc_dim2) * oc_dim1] * 
			dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] - uc[i__ + (
			j + km1 * uc_dim2) * uc_dim1] * opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] - on[i__ + (j + km1 * on_dim2) *
			 on_dim1] * dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] 
			- oe[i__ + (j + km1 * oe_dim2) * oe_dim1] * dpe[ii + (
			jj + kk * dpe_dim2) * dpe_dim1]) + ups[ii + (jj + kk *
			 ups_dim2) * ups_dim1] * (-oe[im1 + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * upsw[ii + (jj + kk * upsw_dim2) 
			* upsw_dim1] - uc[i__ + (jm1 + k * uc_dim2) * uc_dim1]
			 * ops[ii + (jj + kk * ops_dim2) * ops_dim1] + oc[i__ 
			+ (jm1 + kp1 * oc_dim2) * oc_dim1] * ups[ii + (jj + 
			kk * ups_dim2) * ups_dim1] - on[i__ + (jm1 + kp1 * 
			on_dim2) * on_dim1] * upc[ii + (jj + kk * upc_dim2) * 
			upc_dim1] - oe[i__ + (jm1 + kp1 * oe_dim2) * oe_dim1] 
			* upse[ii + (jj + kk * upse_dim2) * upse_dim1]) + 
			upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * (-on[
			im1 + (j + kp1 * on_dim2) * on_dim1] * upw[ii + (jj + 
			kk * upw_dim2) * upw_dim1] - uc[im1 + (jp1 + k * 
			uc_dim2) * uc_dim1] * opnw[ii + (jj + kk * opnw_dim2) 
			* opnw_dim1] + oc[im1 + (jp1 + kp1 * oc_dim2) * 
			oc_dim1] * upnw[ii + (jj + kk * upnw_dim2) * 
			upnw_dim1] - oe[im1 + (jp1 + kp1 * oe_dim2) * oe_dim1]
			 * upn[ii + (jj + kk * upn_dim2) * upn_dim1]);
		tmp7_xoc__ = dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] * (-on[
			im1 + (jm1 + km1 * on_dim2) * on_dim1] * dpsw[ii + (
			jj + kk * dpsw_dim2) * dpsw_dim1] + oc[im1 + (j + km1 
			* oc_dim2) * oc_dim1] * dpw[ii + (jj + kk * dpw_dim2) 
			* dpw_dim1] - uc[im1 + (j + km1 * uc_dim2) * uc_dim1] 
			* opw[ii + (jj + kk * opw_dim2) * opw_dim1] - on[im1 
			+ (j + km1 * on_dim2) * on_dim1] * dpnw[ii + (jj + kk 
			* dpnw_dim2) * dpnw_dim1] - oe[im1 + (j + km1 * 
			oe_dim2) * oe_dim1] * dpc[ii + (jj + kk * dpc_dim2) * 
			dpc_dim1]) + upsw[ii + (jj + kk * upsw_dim2) * 
			upsw_dim1] * (-uc[im1 + (jm1 + k * uc_dim2) * uc_dim1]
			 * opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] + oc[
			im1 + (jm1 + kp1 * oc_dim2) * oc_dim1] * upsw[ii + (
			jj + kk * upsw_dim2) * upsw_dim1] - on[im1 + (jm1 + 
			kp1 * on_dim2) * on_dim1] * upw[ii + (jj + kk * 
			upw_dim2) * upw_dim1] - oe[im1 + (jm1 + kp1 * oe_dim2)
			 * oe_dim1] * ups[ii + (jj + kk * ups_dim2) * 
			ups_dim1]) + opsw[ii + (jj + kk * opsw_dim2) * 
			opsw_dim1] * (-uc[im1 + (jm1 + km1 * uc_dim2) * 
			uc_dim1] * dpsw[ii + (jj + kk * dpsw_dim2) * 
			dpsw_dim1] + oc[im1 + (jm1 + k * oc_dim2) * oc_dim1] *
			 opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] - uc[
			im1 + (jm1 + k * uc_dim2) * uc_dim1] * upsw[ii + (jj 
			+ kk * upsw_dim2) * upsw_dim1] - on[im1 + (jm1 + k * 
			on_dim2) * on_dim1] * opw[ii + (jj + kk * opw_dim2) * 
			opw_dim1] - oe[im1 + (jm1 + k * oe_dim2) * oe_dim1] * 
			ops[ii + (jj + kk * ops_dim2) * ops_dim1]);
		tmp8_xoc__ = opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] * (
			-on[im1 + (j + k * on_dim2) * on_dim1] * opw[ii + (jj 
			+ kk * opw_dim2) * opw_dim1] - uc[im1 + (jp1 + km1 * 
			uc_dim2) * uc_dim1] * dpnw[ii + (jj + kk * dpnw_dim2) 
			* dpnw_dim1] + oc[im1 + (jp1 + k * oc_dim2) * oc_dim1]
			 * opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] - uc[
			im1 + (jp1 + k * uc_dim2) * uc_dim1] * upnw[ii + (jj 
			+ kk * upnw_dim2) * upnw_dim1] - oe[im1 + (jp1 + k * 
			oe_dim2) * oe_dim1] * opn[ii + (jj + kk * opn_dim2) * 
			opn_dim1]) + dpnw[ii + (jj + kk * dpnw_dim2) * 
			dpnw_dim1] * (-on[im1 + (j + km1 * on_dim2) * on_dim1]
			 * dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] + oc[im1 
			+ (jp1 + km1 * oc_dim2) * oc_dim1] * dpnw[ii + (jj + 
			kk * dpnw_dim2) * dpnw_dim1] - uc[im1 + (jp1 + km1 * 
			uc_dim2) * uc_dim1] * opnw[ii + (jj + kk * opnw_dim2) 
			* opnw_dim1] - oe[im1 + (jp1 + km1 * oe_dim2) * 
			oe_dim1] * dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1]) 
			+ opw[ii + (jj + kk * opw_dim2) * opw_dim1] * (-on[
			im1 + (jm1 + k * on_dim2) * on_dim1] * opsw[ii + (jj 
			+ kk * opsw_dim2) * opsw_dim1] - uc[im1 + (j + km1 * 
			uc_dim2) * uc_dim1] * dpw[ii + (jj + kk * dpw_dim2) * 
			dpw_dim1] + oc[im1 + (j + k * oc_dim2) * oc_dim1] * 
			opw[ii + (jj + kk * opw_dim2) * opw_dim1] - uc[im1 + (
			j + k * uc_dim2) * uc_dim1] * upw[ii + (jj + kk * 
			upw_dim2) * upw_dim1] - on[im1 + (j + k * on_dim2) * 
			on_dim1] * opnw[ii + (jj + kk * opnw_dim2) * 
			opnw_dim1] - oe[im1 + (j + k * oe_dim2) * oe_dim1] * 
			opc[ii + (jj + kk * opc_dim2) * opc_dim1]);
		tmp9_xoc__ = upw[ii + (jj + kk * upw_dim2) * upw_dim1] * (-on[
			im1 + (jm1 + kp1 * on_dim2) * on_dim1] * upsw[ii + (
			jj + kk * upsw_dim2) * upsw_dim1] - uc[im1 + (j + k * 
			uc_dim2) * uc_dim1] * opw[ii + (jj + kk * opw_dim2) * 
			opw_dim1] + oc[im1 + (j + kp1 * oc_dim2) * oc_dim1] * 
			upw[ii + (jj + kk * upw_dim2) * upw_dim1] - on[im1 + (
			j + kp1 * on_dim2) * on_dim1] * upnw[ii + (jj + kk * 
			upnw_dim2) * upnw_dim1] - oe[im1 + (j + kp1 * oe_dim2)
			 * oe_dim1] * upc[ii + (jj + kk * upc_dim2) * 
			upc_dim1]) + upn[ii + (jj + kk * upn_dim2) * upn_dim1]
			 * (-oe[im1 + (jp1 + kp1 * oe_dim2) * oe_dim1] * upnw[
			ii + (jj + kk * upnw_dim2) * upnw_dim1] - on[i__ + (j 
			+ kp1 * on_dim2) * on_dim1] * upc[ii + (jj + kk * 
			upc_dim2) * upc_dim1] - uc[i__ + (jp1 + k * uc_dim2) *
			 uc_dim1] * opn[ii + (jj + kk * opn_dim2) * opn_dim1] 
			+ oc[i__ + (jp1 + kp1 * oc_dim2) * oc_dim1] * upn[ii 
			+ (jj + kk * upn_dim2) * upn_dim1] - oe[i__ + (jp1 + 
			kp1 * oe_dim2) * oe_dim1] * upne[ii + (jj + kk * 
			upne_dim2) * upne_dim1]) + opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] * (-oe[im1 + (jp1 + k * oe_dim2)
			 * oe_dim1] * opnw[ii + (jj + kk * opnw_dim2) * 
			opnw_dim1] - on[i__ + (j + k * on_dim2) * on_dim1] * 
			opc[ii + (jj + kk * opc_dim2) * opc_dim1] - uc[i__ + (
			jp1 + km1 * uc_dim2) * uc_dim1] * dpn[ii + (jj + kk * 
			dpn_dim2) * dpn_dim1] + oc[i__ + (jp1 + k * oc_dim2) *
			 oc_dim1] * opn[ii + (jj + kk * opn_dim2) * opn_dim1] 
			- uc[i__ + (jp1 + k * uc_dim2) * uc_dim1] * upn[ii + (
			jj + kk * upn_dim2) * upn_dim1] - oe[i__ + (jp1 + k * 
			oe_dim2) * oe_dim1] * opne[ii + (jj + kk * opne_dim2) 
			* opne_dim1]);
		xoc[ii + (jj + kk * xoc_dim2) * xoc_dim1] = tmp1_xoc__ + 
			tmp2_xoc__ + tmp3_xoc__ + tmp4_xoc__ + tmp5_xoc__ + 
			tmp6_xoc__ + tmp7_xoc__ + tmp8_xoc__ + tmp9_xoc__;
/* * ******************************************************************** */
/* * *** > oE; */
/* * ******************************************************************** */
/* * ***XoE(ii,jj,kk) = */
		tmp1_xoe__ = dps[ii + (jj + kk * dps_dim2) * dps_dim1] * oe[
			i__ + (jm1 + km1 * oe_dim2) * oe_dim1] * dpsw[iip1 + (
			jj + kk * dpsw_dim2) * dpsw_dim1] + ops[ii + (jj + kk 
			* ops_dim2) * ops_dim1] * oe[i__ + (jm1 + k * oe_dim2)
			 * oe_dim1] * opsw[iip1 + (jj + kk * opsw_dim2) * 
			opsw_dim1] + ups[ii + (jj + kk * ups_dim2) * ups_dim1]
			 * oe[i__ + (jm1 + kp1 * oe_dim2) * oe_dim1] * upsw[
			iip1 + (jj + kk * upsw_dim2) * upsw_dim1] + dpc[ii + (
			jj + kk * dpc_dim2) * dpc_dim1] * oe[i__ + (j + km1 * 
			oe_dim2) * oe_dim1] * dpw[iip1 + (jj + kk * dpw_dim2) 
			* dpw_dim1] + opc[ii + (jj + kk * opc_dim2) * 
			opc_dim1] * oe[i__ + (j + k * oe_dim2) * oe_dim1] * 
			opw[iip1 + (jj + kk * opw_dim2) * opw_dim1] + upc[ii 
			+ (jj + kk * upc_dim2) * upc_dim1] * oe[i__ + (j + 
			kp1 * oe_dim2) * oe_dim1] * upw[iip1 + (jj + kk * 
			upw_dim2) * upw_dim1] + dpn[ii + (jj + kk * dpn_dim2) 
			* dpn_dim1] * oe[i__ + (jp1 + km1 * oe_dim2) * 
			oe_dim1] * dpnw[iip1 + (jj + kk * dpnw_dim2) * 
			dpnw_dim1] + opn[ii + (jj + kk * opn_dim2) * opn_dim1]
			 * oe[i__ + (jp1 + k * oe_dim2) * oe_dim1] * opnw[
			iip1 + (jj + kk * opnw_dim2) * opnw_dim1] + upn[ii + (
			jj + kk * upn_dim2) * upn_dim1] * oe[i__ + (jp1 + kp1 
			* oe_dim2) * oe_dim1] * upnw[iip1 + (jj + kk * 
			upnw_dim2) * upnw_dim1] - dpse[ii + (jj + kk * 
			dpse_dim2) * dpse_dim1] * (oc[ip1 + (jm1 + km1 * 
			oc_dim2) * oc_dim1] * dpsw[iip1 + (jj + kk * 
			dpsw_dim2) * dpsw_dim1] - uc[ip1 + (jm1 + km1 * 
			uc_dim2) * uc_dim1] * opsw[iip1 + (jj + kk * 
			opsw_dim2) * opsw_dim1] - on[ip1 + (jm1 + km1 * 
			on_dim2) * on_dim1] * dpw[iip1 + (jj + kk * dpw_dim2) 
			* dpw_dim1] - oe[ip1 + (jm1 + km1 * oe_dim2) * 
			oe_dim1] * dps[iip1 + (jj + kk * dps_dim2) * dps_dim1]
			);
		tmp2_xoe__ = -opse[ii + (jj + kk * opse_dim2) * opse_dim1] * (
			-uc[ip1 + (jm1 + km1 * uc_dim2) * uc_dim1] * dpsw[
			iip1 + (jj + kk * dpsw_dim2) * dpsw_dim1] + oc[ip1 + (
			jm1 + k * oc_dim2) * oc_dim1] * opsw[iip1 + (jj + kk *
			 opsw_dim2) * opsw_dim1] - uc[ip1 + (jm1 + k * 
			uc_dim2) * uc_dim1] * upsw[iip1 + (jj + kk * 
			upsw_dim2) * upsw_dim1] - on[ip1 + (jm1 + k * on_dim2)
			 * on_dim1] * opw[iip1 + (jj + kk * opw_dim2) * 
			opw_dim1] - oe[ip1 + (jm1 + k * oe_dim2) * oe_dim1] * 
			ops[iip1 + (jj + kk * ops_dim2) * ops_dim1]) - upse[
			ii + (jj + kk * upse_dim2) * upse_dim1] * (-uc[ip1 + (
			jm1 + k * uc_dim2) * uc_dim1] * opsw[iip1 + (jj + kk *
			 opsw_dim2) * opsw_dim1] + oc[ip1 + (jm1 + kp1 * 
			oc_dim2) * oc_dim1] * upsw[iip1 + (jj + kk * 
			upsw_dim2) * upsw_dim1] - on[ip1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * upw[iip1 + (jj + kk * upw_dim2) 
			* upw_dim1] - oe[ip1 + (jm1 + kp1 * oe_dim2) * 
			oe_dim1] * ups[iip1 + (jj + kk * ups_dim2) * ups_dim1]
			) - dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] * (-on[
			ip1 + (jm1 + km1 * on_dim2) * on_dim1] * dpsw[iip1 + (
			jj + kk * dpsw_dim2) * dpsw_dim1] + oc[ip1 + (j + km1 
			* oc_dim2) * oc_dim1] * dpw[iip1 + (jj + kk * 
			dpw_dim2) * dpw_dim1] - uc[ip1 + (j + km1 * uc_dim2) *
			 uc_dim1] * opw[iip1 + (jj + kk * opw_dim2) * 
			opw_dim1] - on[ip1 + (j + km1 * on_dim2) * on_dim1] * 
			dpnw[iip1 + (jj + kk * dpnw_dim2) * dpnw_dim1] - oe[
			ip1 + (j + km1 * oe_dim2) * oe_dim1] * dpc[iip1 + (jj 
			+ kk * dpc_dim2) * dpc_dim1]);
		tmp3_xoe__ = -ope[ii + (jj + kk * ope_dim2) * ope_dim1] * (
			-on[ip1 + (jm1 + k * on_dim2) * on_dim1] * opsw[iip1 
			+ (jj + kk * opsw_dim2) * opsw_dim1] - uc[ip1 + (j + 
			km1 * uc_dim2) * uc_dim1] * dpw[iip1 + (jj + kk * 
			dpw_dim2) * dpw_dim1] + oc[ip1 + (j + k * oc_dim2) * 
			oc_dim1] * opw[iip1 + (jj + kk * opw_dim2) * opw_dim1]
			 - uc[ip1 + (j + k * uc_dim2) * uc_dim1] * upw[iip1 + 
			(jj + kk * upw_dim2) * upw_dim1] - on[ip1 + (j + k * 
			on_dim2) * on_dim1] * opnw[iip1 + (jj + kk * 
			opnw_dim2) * opnw_dim1] - oe[ip1 + (j + k * oe_dim2) *
			 oe_dim1] * opc[iip1 + (jj + kk * opc_dim2) * 
			opc_dim1]) - upe[ii + (jj + kk * upe_dim2) * upe_dim1]
			 * (-on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1] * upsw[
			iip1 + (jj + kk * upsw_dim2) * upsw_dim1] - uc[ip1 + (
			j + k * uc_dim2) * uc_dim1] * opw[iip1 + (jj + kk * 
			opw_dim2) * opw_dim1] + oc[ip1 + (j + kp1 * oc_dim2) *
			 oc_dim1] * upw[iip1 + (jj + kk * upw_dim2) * 
			upw_dim1] - on[ip1 + (j + kp1 * on_dim2) * on_dim1] * 
			upnw[iip1 + (jj + kk * upnw_dim2) * upnw_dim1] - oe[
			ip1 + (j + kp1 * oe_dim2) * oe_dim1] * upc[iip1 + (jj 
			+ kk * upc_dim2) * upc_dim1]) - dpne[ii + (jj + kk * 
			dpne_dim2) * dpne_dim1] * (-on[ip1 + (j + km1 * 
			on_dim2) * on_dim1] * dpw[iip1 + (jj + kk * dpw_dim2) 
			* dpw_dim1] + oc[ip1 + (jp1 + km1 * oc_dim2) * 
			oc_dim1] * dpnw[iip1 + (jj + kk * dpnw_dim2) * 
			dpnw_dim1] - uc[ip1 + (jp1 + km1 * uc_dim2) * uc_dim1]
			 * opnw[iip1 + (jj + kk * opnw_dim2) * opnw_dim1] - 
			oe[ip1 + (jp1 + km1 * oe_dim2) * oe_dim1] * dpn[iip1 
			+ (jj + kk * dpn_dim2) * dpn_dim1]);
		tmp4_xoe__ = -opne[ii + (jj + kk * opne_dim2) * opne_dim1] * (
			-on[ip1 + (j + k * on_dim2) * on_dim1] * opw[iip1 + (
			jj + kk * opw_dim2) * opw_dim1] - uc[ip1 + (jp1 + km1 
			* uc_dim2) * uc_dim1] * dpnw[iip1 + (jj + kk * 
			dpnw_dim2) * dpnw_dim1] + oc[ip1 + (jp1 + k * oc_dim2)
			 * oc_dim1] * opnw[iip1 + (jj + kk * opnw_dim2) * 
			opnw_dim1] - uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1] *
			 upnw[iip1 + (jj + kk * upnw_dim2) * upnw_dim1] - oe[
			ip1 + (jp1 + k * oe_dim2) * oe_dim1] * opn[iip1 + (jj 
			+ kk * opn_dim2) * opn_dim1]) - upne[ii + (jj + kk * 
			upne_dim2) * upne_dim1] * (-on[ip1 + (j + kp1 * 
			on_dim2) * on_dim1] * upw[iip1 + (jj + kk * upw_dim2) 
			* upw_dim1] - uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1] 
			* opnw[iip1 + (jj + kk * opnw_dim2) * opnw_dim1] + oc[
			ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1] * upnw[iip1 + (
			jj + kk * upnw_dim2) * upnw_dim1] - oe[ip1 + (jp1 + 
			kp1 * oe_dim2) * oe_dim1] * upn[iip1 + (jj + kk * 
			upn_dim2) * upn_dim1]);
		xoe[ii + (jj + kk * xoe_dim2) * xoe_dim1] = tmp1_xoe__ + 
			tmp2_xoe__ + tmp3_xoe__ + tmp4_xoe__;
/* * ******************************************************************** */
/* * *** > oN; */
/* * ******************************************************************** */
/* * ***XoN(ii,jj,kk) = */
		tmp1_xon__ = dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] * on[
			im1 + (j + km1 * on_dim2) * on_dim1] * dpsw[ii + (
			jjp1 + kk * dpsw_dim2) * dpsw_dim1] + opw[ii + (jj + 
			kk * opw_dim2) * opw_dim1] * on[im1 + (j + k * 
			on_dim2) * on_dim1] * opsw[ii + (jjp1 + kk * 
			opsw_dim2) * opsw_dim1] + upw[ii + (jj + kk * 
			upw_dim2) * upw_dim1] * on[im1 + (j + kp1 * on_dim2) *
			 on_dim1] * upsw[ii + (jjp1 + kk * upsw_dim2) * 
			upsw_dim1] - dpnw[ii + (jj + kk * dpnw_dim2) * 
			dpnw_dim1] * (oc[im1 + (jp1 + km1 * oc_dim2) * 
			oc_dim1] * dpsw[ii + (jjp1 + kk * dpsw_dim2) * 
			dpsw_dim1] - uc[im1 + (jp1 + km1 * uc_dim2) * uc_dim1]
			 * opsw[ii + (jjp1 + kk * opsw_dim2) * opsw_dim1] - 
			on[im1 + (jp1 + km1 * on_dim2) * on_dim1] * dpw[ii + (
			jjp1 + kk * dpw_dim2) * dpw_dim1] - oe[im1 + (jp1 + 
			km1 * oe_dim2) * oe_dim1] * dps[ii + (jjp1 + kk * 
			dps_dim2) * dps_dim1]) - opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] * (-uc[im1 + (jp1 + km1 * 
			uc_dim2) * uc_dim1] * dpsw[ii + (jjp1 + kk * 
			dpsw_dim2) * dpsw_dim1] + oc[im1 + (jp1 + k * oc_dim2)
			 * oc_dim1] * opsw[ii + (jjp1 + kk * opsw_dim2) * 
			opsw_dim1] - uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] *
			 upsw[ii + (jjp1 + kk * upsw_dim2) * upsw_dim1] - on[
			im1 + (jp1 + k * on_dim2) * on_dim1] * opw[ii + (jjp1 
			+ kk * opw_dim2) * opw_dim1] - oe[im1 + (jp1 + k * 
			oe_dim2) * oe_dim1] * ops[ii + (jjp1 + kk * ops_dim2) 
			* ops_dim1]);
		tmp2_xon__ = -upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * (
			-uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] * opsw[ii + (
			jjp1 + kk * opsw_dim2) * opsw_dim1] + oc[im1 + (jp1 + 
			kp1 * oc_dim2) * oc_dim1] * upsw[ii + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - on[im1 + (jp1 + kp1 * 
			on_dim2) * on_dim1] * upw[ii + (jjp1 + kk * upw_dim2) 
			* upw_dim1] - oe[im1 + (jp1 + kp1 * oe_dim2) * 
			oe_dim1] * ups[ii + (jjp1 + kk * ups_dim2) * ups_dim1]
			) + dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] * on[
			i__ + (j + km1 * on_dim2) * on_dim1] * dps[ii + (jjp1 
			+ kk * dps_dim2) * dps_dim1] + opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] * on[i__ + (j + k * on_dim2) * 
			on_dim1] * ops[ii + (jjp1 + kk * ops_dim2) * ops_dim1]
			 + upc[ii + (jj + kk * upc_dim2) * upc_dim1] * on[i__ 
			+ (j + kp1 * on_dim2) * on_dim1] * ups[ii + (jjp1 + 
			kk * ups_dim2) * ups_dim1] - dpn[ii + (jj + kk * 
			dpn_dim2) * dpn_dim1] * (-oe[im1 + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpsw[ii + (jjp1 + kk * 
			dpsw_dim2) * dpsw_dim1] + oc[i__ + (jp1 + km1 * 
			oc_dim2) * oc_dim1] * dps[ii + (jjp1 + kk * dps_dim2) 
			* dps_dim1] - uc[i__ + (jp1 + km1 * uc_dim2) * 
			uc_dim1] * ops[ii + (jjp1 + kk * ops_dim2) * ops_dim1]
			 - on[i__ + (jp1 + km1 * on_dim2) * on_dim1] * dpc[ii 
			+ (jjp1 + kk * dpc_dim2) * dpc_dim1] - oe[i__ + (jp1 
			+ km1 * oe_dim2) * oe_dim1] * dpse[ii + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1]);
		tmp3_xon__ = -opn[ii + (jj + kk * opn_dim2) * opn_dim1] * (
			-oe[im1 + (jp1 + k * oe_dim2) * oe_dim1] * opsw[ii + (
			jjp1 + kk * opsw_dim2) * opsw_dim1] - uc[i__ + (jp1 + 
			km1 * uc_dim2) * uc_dim1] * dps[ii + (jjp1 + kk * 
			dps_dim2) * dps_dim1] + oc[i__ + (jp1 + k * oc_dim2) *
			 oc_dim1] * ops[ii + (jjp1 + kk * ops_dim2) * 
			ops_dim1] - uc[i__ + (jp1 + k * uc_dim2) * uc_dim1] * 
			ups[ii + (jjp1 + kk * ups_dim2) * ups_dim1] - on[i__ 
			+ (jp1 + k * on_dim2) * on_dim1] * opc[ii + (jjp1 + 
			kk * opc_dim2) * opc_dim1] - oe[i__ + (jp1 + k * 
			oe_dim2) * oe_dim1] * opse[ii + (jjp1 + kk * 
			opse_dim2) * opse_dim1]) - upn[ii + (jj + kk * 
			upn_dim2) * upn_dim1] * (-oe[im1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * upsw[ii + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - uc[i__ + (jp1 + k * uc_dim2)
			 * uc_dim1] * ops[ii + (jjp1 + kk * ops_dim2) * 
			ops_dim1] + oc[i__ + (jp1 + kp1 * oc_dim2) * oc_dim1] 
			* ups[ii + (jjp1 + kk * ups_dim2) * ups_dim1] - on[
			i__ + (jp1 + kp1 * on_dim2) * on_dim1] * upc[ii + (
			jjp1 + kk * upc_dim2) * upc_dim1] - oe[i__ + (jp1 + 
			kp1 * oe_dim2) * oe_dim1] * upse[ii + (jjp1 + kk * 
			upse_dim2) * upse_dim1]) + dpe[ii + (jj + kk * 
			dpe_dim2) * dpe_dim1] * on[ip1 + (j + km1 * on_dim2) *
			 on_dim1] * dpse[ii + (jjp1 + kk * dpse_dim2) * 
			dpse_dim1] + ope[ii + (jj + kk * ope_dim2) * ope_dim1]
			 * on[ip1 + (j + k * on_dim2) * on_dim1] * opse[ii + (
			jjp1 + kk * opse_dim2) * opse_dim1] + upe[ii + (jj + 
			kk * upe_dim2) * upe_dim1] * on[ip1 + (j + kp1 * 
			on_dim2) * on_dim1] * upse[ii + (jjp1 + kk * 
			upse_dim2) * upse_dim1];
		tmp4_xon__ = -dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] * (
			-oe[i__ + (jp1 + km1 * oe_dim2) * oe_dim1] * dps[ii + 
			(jjp1 + kk * dps_dim2) * dps_dim1] + oc[ip1 + (jp1 + 
			km1 * oc_dim2) * oc_dim1] * dpse[ii + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] - uc[ip1 + (jp1 + km1 * 
			uc_dim2) * uc_dim1] * opse[ii + (jjp1 + kk * 
			opse_dim2) * opse_dim1] - on[ip1 + (jp1 + km1 * 
			on_dim2) * on_dim1] * dpe[ii + (jjp1 + kk * dpe_dim2) 
			* dpe_dim1]) - opne[ii + (jj + kk * opne_dim2) * 
			opne_dim1] * (-oe[i__ + (jp1 + k * oe_dim2) * oe_dim1]
			 * ops[ii + (jjp1 + kk * ops_dim2) * ops_dim1] - uc[
			ip1 + (jp1 + km1 * uc_dim2) * uc_dim1] * dpse[ii + (
			jjp1 + kk * dpse_dim2) * dpse_dim1] + oc[ip1 + (jp1 + 
			k * oc_dim2) * oc_dim1] * opse[ii + (jjp1 + kk * 
			opse_dim2) * opse_dim1] - uc[ip1 + (jp1 + k * uc_dim2)
			 * uc_dim1] * upse[ii + (jjp1 + kk * upse_dim2) * 
			upse_dim1] - on[ip1 + (jp1 + k * on_dim2) * on_dim1] *
			 ope[ii + (jjp1 + kk * ope_dim2) * ope_dim1]) - upne[
			ii + (jj + kk * upne_dim2) * upne_dim1] * (-oe[i__ + (
			jp1 + kp1 * oe_dim2) * oe_dim1] * ups[ii + (jjp1 + kk 
			* ups_dim2) * ups_dim1] - uc[ip1 + (jp1 + k * uc_dim2)
			 * uc_dim1] * opse[ii + (jjp1 + kk * opse_dim2) * 
			opse_dim1] + oc[ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * upse[ii + (jjp1 + kk * upse_dim2) * upse_dim1] - 
			on[ip1 + (jp1 + kp1 * on_dim2) * on_dim1] * upe[ii + (
			jjp1 + kk * upe_dim2) * upe_dim1]);
		xon[ii + (jj + kk * xon_dim2) * xon_dim1] = tmp1_xon__ + 
			tmp2_xon__ + tmp3_xon__ + tmp4_xon__;
/* * ******************************************************************** */
/* * *** > uC; */
/* * ******************************************************************** */
/* * ***XuC(ii,jj,kk) = */
		tmp1_xuc__ = opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] * 
			uc[im1 + (jm1 + k * uc_dim2) * uc_dim1] * dpsw[ii + (
			jj + kkp1 * dpsw_dim2) * dpsw_dim1] - upsw[ii + (jj + 
			kk * upsw_dim2) * upsw_dim1] * (oc[im1 + (jm1 + kp1 * 
			oc_dim2) * oc_dim1] * dpsw[ii + (jj + kkp1 * 
			dpsw_dim2) * dpsw_dim1] - uc[im1 + (jm1 + kp1 * 
			uc_dim2) * uc_dim1] * opsw[ii + (jj + kkp1 * 
			opsw_dim2) * opsw_dim1] - on[im1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * dpw[ii + (jj + kkp1 * dpw_dim2) 
			* dpw_dim1] - oe[im1 + (jm1 + kp1 * oe_dim2) * 
			oe_dim1] * dps[ii + (jj + kkp1 * dps_dim2) * dps_dim1]
			) + opw[ii + (jj + kk * opw_dim2) * opw_dim1] * uc[
			im1 + (j + k * uc_dim2) * uc_dim1] * dpw[ii + (jj + 
			kkp1 * dpw_dim2) * dpw_dim1] - upw[ii + (jj + kk * 
			upw_dim2) * upw_dim1] * (-on[im1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * dpsw[ii + (jj + kkp1 * 
			dpsw_dim2) * dpsw_dim1] + oc[im1 + (j + kp1 * oc_dim2)
			 * oc_dim1] * dpw[ii + (jj + kkp1 * dpw_dim2) * 
			dpw_dim1] - uc[im1 + (j + kp1 * uc_dim2) * uc_dim1] * 
			opw[ii + (jj + kkp1 * opw_dim2) * opw_dim1] - on[im1 
			+ (j + kp1 * on_dim2) * on_dim1] * dpnw[ii + (jj + 
			kkp1 * dpnw_dim2) * dpnw_dim1] - oe[im1 + (j + kp1 * 
			oe_dim2) * oe_dim1] * dpc[ii + (jj + kkp1 * dpc_dim2) 
			* dpc_dim1]) + opnw[ii + (jj + kk * opnw_dim2) * 
			opnw_dim1] * uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] *
			 dpnw[ii + (jj + kkp1 * dpnw_dim2) * dpnw_dim1];
		tmp2_xuc__ = -upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * (
			-on[im1 + (j + kp1 * on_dim2) * on_dim1] * dpw[ii + (
			jj + kkp1 * dpw_dim2) * dpw_dim1] + oc[im1 + (jp1 + 
			kp1 * oc_dim2) * oc_dim1] * dpnw[ii + (jj + kkp1 * 
			dpnw_dim2) * dpnw_dim1] - uc[im1 + (jp1 + kp1 * 
			uc_dim2) * uc_dim1] * opnw[ii + (jj + kkp1 * 
			opnw_dim2) * opnw_dim1] - oe[im1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * dpn[ii + (jj + kkp1 * dpn_dim2) 
			* dpn_dim1]) + ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1] * uc[i__ + (jm1 + k * uc_dim2) * uc_dim1] * 
			dps[ii + (jj + kkp1 * dps_dim2) * dps_dim1] - ups[ii 
			+ (jj + kk * ups_dim2) * ups_dim1] * (-oe[im1 + (jm1 
			+ kp1 * oe_dim2) * oe_dim1] * dpsw[ii + (jj + kkp1 * 
			dpsw_dim2) * dpsw_dim1] + oc[i__ + (jm1 + kp1 * 
			oc_dim2) * oc_dim1] * dps[ii + (jj + kkp1 * dps_dim2) 
			* dps_dim1] - uc[i__ + (jm1 + kp1 * uc_dim2) * 
			uc_dim1] * ops[ii + (jj + kkp1 * ops_dim2) * ops_dim1]
			 - on[i__ + (jm1 + kp1 * on_dim2) * on_dim1] * dpc[ii 
			+ (jj + kkp1 * dpc_dim2) * dpc_dim1] - oe[i__ + (jm1 
			+ kp1 * oe_dim2) * oe_dim1] * dpse[ii + (jj + kkp1 * 
			dpse_dim2) * dpse_dim1]) + opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] * uc[i__ + (j + k * uc_dim2) * 
			uc_dim1] * dpc[ii + (jj + kkp1 * dpc_dim2) * dpc_dim1]
			 - upc[ii + (jj + kk * upc_dim2) * upc_dim1] * (-oe[
			im1 + (j + kp1 * oe_dim2) * oe_dim1] * dpw[ii + (jj + 
			kkp1 * dpw_dim2) * dpw_dim1] - on[i__ + (jm1 + kp1 * 
			on_dim2) * on_dim1] * dps[ii + (jj + kkp1 * dps_dim2) 
			* dps_dim1] + oc[i__ + (j + kp1 * oc_dim2) * oc_dim1] 
			* dpc[ii + (jj + kkp1 * dpc_dim2) * dpc_dim1] - uc[
			i__ + (j + kp1 * uc_dim2) * uc_dim1] * opc[ii + (jj + 
			kkp1 * opc_dim2) * opc_dim1] - on[i__ + (j + kp1 * 
			on_dim2) * on_dim1] * dpn[ii + (jj + kkp1 * dpn_dim2) 
			* dpn_dim1] - oe[i__ + (j + kp1 * oe_dim2) * oe_dim1] 
			* dpe[ii + (jj + kkp1 * dpe_dim2) * dpe_dim1]);
		tmp3_xuc__ = opn[ii + (jj + kk * opn_dim2) * opn_dim1] * uc[
			i__ + (jp1 + k * uc_dim2) * uc_dim1] * dpn[ii + (jj + 
			kkp1 * dpn_dim2) * dpn_dim1] - upn[ii + (jj + kk * 
			upn_dim2) * upn_dim1] * (-oe[im1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * dpnw[ii + (jj + kkp1 * 
			dpnw_dim2) * dpnw_dim1] - on[i__ + (j + kp1 * on_dim2)
			 * on_dim1] * dpc[ii + (jj + kkp1 * dpc_dim2) * 
			dpc_dim1] + oc[i__ + (jp1 + kp1 * oc_dim2) * oc_dim1] 
			* dpn[ii + (jj + kkp1 * dpn_dim2) * dpn_dim1] - uc[
			i__ + (jp1 + kp1 * uc_dim2) * uc_dim1] * opn[ii + (jj 
			+ kkp1 * opn_dim2) * opn_dim1] - oe[i__ + (jp1 + kp1 *
			 oe_dim2) * oe_dim1] * dpne[ii + (jj + kkp1 * 
			dpne_dim2) * dpne_dim1]) + opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] * uc[ip1 + (jm1 + k * uc_dim2)
			 * uc_dim1] * dpse[ii + (jj + kkp1 * dpse_dim2) * 
			dpse_dim1] - upse[ii + (jj + kk * upse_dim2) * 
			upse_dim1] * (-oe[i__ + (jm1 + kp1 * oe_dim2) * 
			oe_dim1] * dps[ii + (jj + kkp1 * dps_dim2) * dps_dim1]
			 + oc[ip1 + (jm1 + kp1 * oc_dim2) * oc_dim1] * dpse[
			ii + (jj + kkp1 * dpse_dim2) * dpse_dim1] - uc[ip1 + (
			jm1 + kp1 * uc_dim2) * uc_dim1] * opse[ii + (jj + 
			kkp1 * opse_dim2) * opse_dim1] - on[ip1 + (jm1 + kp1 *
			 on_dim2) * on_dim1] * dpe[ii + (jj + kkp1 * dpe_dim2)
			 * dpe_dim1]);
		tmp4_xuc__ = ope[ii + (jj + kk * ope_dim2) * ope_dim1] * uc[
			ip1 + (j + k * uc_dim2) * uc_dim1] * dpe[ii + (jj + 
			kkp1 * dpe_dim2) * dpe_dim1] - upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1] * (-oe[i__ + (j + kp1 * oe_dim2)
			 * oe_dim1] * dpc[ii + (jj + kkp1 * dpc_dim2) * 
			dpc_dim1] - on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1] 
			* dpse[ii + (jj + kkp1 * dpse_dim2) * dpse_dim1] + oc[
			ip1 + (j + kp1 * oc_dim2) * oc_dim1] * dpe[ii + (jj + 
			kkp1 * dpe_dim2) * dpe_dim1] - uc[ip1 + (j + kp1 * 
			uc_dim2) * uc_dim1] * ope[ii + (jj + kkp1 * ope_dim2) 
			* ope_dim1] - on[ip1 + (j + kp1 * on_dim2) * on_dim1] 
			* dpne[ii + (jj + kkp1 * dpne_dim2) * dpne_dim1]) + 
			opne[ii + (jj + kk * opne_dim2) * opne_dim1] * uc[ip1 
			+ (jp1 + k * uc_dim2) * uc_dim1] * dpne[ii + (jj + 
			kkp1 * dpne_dim2) * dpne_dim1] - upne[ii + (jj + kk * 
			upne_dim2) * upne_dim1] * (-oe[i__ + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * dpn[ii + (jj + kkp1 * dpn_dim2) 
			* dpn_dim1] - on[ip1 + (j + kp1 * on_dim2) * on_dim1] 
			* dpe[ii + (jj + kkp1 * dpe_dim2) * dpe_dim1] + oc[
			ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1] * dpne[ii + (
			jj + kkp1 * dpne_dim2) * dpne_dim1] - uc[ip1 + (jp1 + 
			kp1 * uc_dim2) * uc_dim1] * opne[ii + (jj + kkp1 * 
			opne_dim2) * opne_dim1]);
		xuc[ii + (jj + kk * xuc_dim2) * xuc_dim1] = tmp1_xuc__ + 
			tmp2_xuc__ + tmp3_xuc__ + tmp4_xuc__;
/* * ******************************************************************** */
/* * *** > oNE; */
/* * ******************************************************************** */
		xone[ii + (jj + kk * xone_dim2) * xone_dim1] = dpn[ii + (jj + 
			kk * dpn_dim2) * dpn_dim1] * oe[i__ + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpsw[iip1 + (jjp1 + kk * 
			dpsw_dim2) * dpsw_dim1] + opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] * oe[i__ + (jp1 + k * oe_dim2) *
			 oe_dim1] * opsw[iip1 + (jjp1 + kk * opsw_dim2) * 
			opsw_dim1] + upn[ii + (jj + kk * upn_dim2) * upn_dim1]
			 * oe[i__ + (jp1 + kp1 * oe_dim2) * oe_dim1] * upsw[
			iip1 + (jjp1 + kk * upsw_dim2) * upsw_dim1] + dpe[ii 
			+ (jj + kk * dpe_dim2) * dpe_dim1] * on[ip1 + (j + 
			km1 * on_dim2) * on_dim1] * dpsw[iip1 + (jjp1 + kk * 
			dpsw_dim2) * dpsw_dim1] + ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] * on[ip1 + (j + k * on_dim2) * 
			on_dim1] * opsw[iip1 + (jjp1 + kk * opsw_dim2) * 
			opsw_dim1] + upe[ii + (jj + kk * upe_dim2) * upe_dim1]
			 * on[ip1 + (j + kp1 * on_dim2) * on_dim1] * upsw[
			iip1 + (jjp1 + kk * upsw_dim2) * upsw_dim1] - dpne[ii 
			+ (jj + kk * dpne_dim2) * dpne_dim1] * (oc[ip1 + (jp1 
			+ km1 * oc_dim2) * oc_dim1] * dpsw[iip1 + (jjp1 + kk *
			 dpsw_dim2) * dpsw_dim1] - uc[ip1 + (jp1 + km1 * 
			uc_dim2) * uc_dim1] * opsw[iip1 + (jjp1 + kk * 
			opsw_dim2) * opsw_dim1] - on[ip1 + (jp1 + km1 * 
			on_dim2) * on_dim1] * dpw[iip1 + (jjp1 + kk * 
			dpw_dim2) * dpw_dim1] - oe[ip1 + (jp1 + km1 * oe_dim2)
			 * oe_dim1] * dps[iip1 + (jjp1 + kk * dps_dim2) * 
			dps_dim1]) - opne[ii + (jj + kk * opne_dim2) * 
			opne_dim1] * (-uc[ip1 + (jp1 + km1 * uc_dim2) * 
			uc_dim1] * dpsw[iip1 + (jjp1 + kk * dpsw_dim2) * 
			dpsw_dim1] + oc[ip1 + (jp1 + k * oc_dim2) * oc_dim1] *
			 opsw[iip1 + (jjp1 + kk * opsw_dim2) * opsw_dim1] - 
			uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1] * upsw[iip1 + 
			(jjp1 + kk * upsw_dim2) * upsw_dim1] - on[ip1 + (jp1 
			+ k * on_dim2) * on_dim1] * opw[iip1 + (jjp1 + kk * 
			opw_dim2) * opw_dim1] - oe[ip1 + (jp1 + k * oe_dim2) *
			 oe_dim1] * ops[iip1 + (jjp1 + kk * ops_dim2) * 
			ops_dim1]) - upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1] * (-uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1]
			 * opsw[iip1 + (jjp1 + kk * opsw_dim2) * opsw_dim1] + 
			oc[ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1] * upsw[iip1 
			+ (jjp1 + kk * upsw_dim2) * upsw_dim1] - on[ip1 + (
			jp1 + kp1 * on_dim2) * on_dim1] * upw[iip1 + (jjp1 + 
			kk * upw_dim2) * upw_dim1] - oe[ip1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * ups[iip1 + (jjp1 + kk * 
			ups_dim2) * ups_dim1]);
/* * ******************************************************************** */
/* * *** > oNW; */
/* * ******************************************************************** */
		xonw[ii + (jj + kk * xonw_dim2) * xonw_dim1] = dpw[ii + (jj + 
			kk * dpw_dim2) * dpw_dim1] * on[im1 + (j + km1 * 
			on_dim2) * on_dim1] * dpse[iim1 + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] + opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] * on[im1 + (j + k * on_dim2) * 
			on_dim1] * opse[iim1 + (jjp1 + kk * opse_dim2) * 
			opse_dim1] + upw[ii + (jj + kk * upw_dim2) * upw_dim1]
			 * on[im1 + (j + kp1 * on_dim2) * on_dim1] * upse[
			iim1 + (jjp1 + kk * upse_dim2) * upse_dim1] - dpnw[ii 
			+ (jj + kk * dpnw_dim2) * dpnw_dim1] * (-oe[im2 + (
			jp1 + km1 * oe_dim2) * oe_dim1] * dps[iim1 + (jjp1 + 
			kk * dps_dim2) * dps_dim1] + oc[im1 + (jp1 + km1 * 
			oc_dim2) * oc_dim1] * dpse[iim1 + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] - uc[im1 + (jp1 + km1 * 
			uc_dim2) * uc_dim1] * opse[iim1 + (jjp1 + kk * 
			opse_dim2) * opse_dim1] - on[im1 + (jp1 + km1 * 
			on_dim2) * on_dim1] * dpe[iim1 + (jjp1 + kk * 
			dpe_dim2) * dpe_dim1]) - opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] * (-oe[im2 + (jp1 + k * 
			oe_dim2) * oe_dim1] * ops[iim1 + (jjp1 + kk * 
			ops_dim2) * ops_dim1] - uc[im1 + (jp1 + km1 * uc_dim2)
			 * uc_dim1] * dpse[iim1 + (jjp1 + kk * dpse_dim2) * 
			dpse_dim1] + oc[im1 + (jp1 + k * oc_dim2) * oc_dim1] *
			 opse[iim1 + (jjp1 + kk * opse_dim2) * opse_dim1] - 
			uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] * upse[iim1 + 
			(jjp1 + kk * upse_dim2) * upse_dim1] - on[im1 + (jp1 
			+ k * on_dim2) * on_dim1] * ope[iim1 + (jjp1 + kk * 
			ope_dim2) * ope_dim1]) - upnw[ii + (jj + kk * 
			upnw_dim2) * upnw_dim1] * (-oe[im2 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * ups[iim1 + (jjp1 + kk * 
			ups_dim2) * ups_dim1] - uc[im1 + (jp1 + k * uc_dim2) *
			 uc_dim1] * opse[iim1 + (jjp1 + kk * opse_dim2) * 
			opse_dim1] + oc[im1 + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * upse[iim1 + (jjp1 + kk * upse_dim2) * upse_dim1] - 
			on[im1 + (jp1 + kp1 * on_dim2) * on_dim1] * upe[iim1 
			+ (jjp1 + kk * upe_dim2) * upe_dim1]) + dpn[ii + (jj 
			+ kk * dpn_dim2) * dpn_dim1] * oe[im1 + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpse[iim1 + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] + opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] * oe[im1 + (jp1 + k * oe_dim2) *
			 oe_dim1] * opse[iim1 + (jjp1 + kk * opse_dim2) * 
			opse_dim1] + upn[ii + (jj + kk * upn_dim2) * upn_dim1]
			 * oe[im1 + (jp1 + kp1 * oe_dim2) * oe_dim1] * upse[
			iim1 + (jjp1 + kk * upse_dim2) * upse_dim1];
/* * ******************************************************************** */
/* * *** > uE; */
/* * ******************************************************************** */
		xue[ii + (jj + kk * xue_dim2) * xue_dim1] = ups[ii + (jj + kk 
			* ups_dim2) * ups_dim1] * oe[i__ + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * dpsw[iip1 + (jj + kkp1 * 
			dpsw_dim2) * dpsw_dim1] + upc[ii + (jj + kk * 
			upc_dim2) * upc_dim1] * oe[i__ + (j + kp1 * oe_dim2) *
			 oe_dim1] * dpw[iip1 + (jj + kkp1 * dpw_dim2) * 
			dpw_dim1] + upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			* oe[i__ + (jp1 + kp1 * oe_dim2) * oe_dim1] * dpnw[
			iip1 + (jj + kkp1 * dpnw_dim2) * dpnw_dim1] + opse[ii 
			+ (jj + kk * opse_dim2) * opse_dim1] * uc[ip1 + (jm1 
			+ k * uc_dim2) * uc_dim1] * dpsw[iip1 + (jj + kkp1 * 
			dpsw_dim2) * dpsw_dim1] - upse[ii + (jj + kk * 
			upse_dim2) * upse_dim1] * (oc[ip1 + (jm1 + kp1 * 
			oc_dim2) * oc_dim1] * dpsw[iip1 + (jj + kkp1 * 
			dpsw_dim2) * dpsw_dim1] - uc[ip1 + (jm1 + kp1 * 
			uc_dim2) * uc_dim1] * opsw[iip1 + (jj + kkp1 * 
			opsw_dim2) * opsw_dim1] - on[ip1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * dpw[iip1 + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - oe[ip1 + (jm1 + kp1 * oe_dim2)
			 * oe_dim1] * dps[iip1 + (jj + kkp1 * dps_dim2) * 
			dps_dim1]) + ope[ii + (jj + kk * ope_dim2) * ope_dim1]
			 * uc[ip1 + (j + k * uc_dim2) * uc_dim1] * dpw[iip1 + 
			(jj + kkp1 * dpw_dim2) * dpw_dim1] - upe[ii + (jj + 
			kk * upe_dim2) * upe_dim1] * (-on[ip1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * dpsw[iip1 + (jj + kkp1 * 
			dpsw_dim2) * dpsw_dim1] + oc[ip1 + (j + kp1 * oc_dim2)
			 * oc_dim1] * dpw[iip1 + (jj + kkp1 * dpw_dim2) * 
			dpw_dim1] - uc[ip1 + (j + kp1 * uc_dim2) * uc_dim1] * 
			opw[iip1 + (jj + kkp1 * opw_dim2) * opw_dim1] - on[
			ip1 + (j + kp1 * on_dim2) * on_dim1] * dpnw[iip1 + (
			jj + kkp1 * dpnw_dim2) * dpnw_dim1] - oe[ip1 + (j + 
			kp1 * oe_dim2) * oe_dim1] * dpc[iip1 + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1]) + opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1] * uc[ip1 + (jp1 + k * uc_dim2)
			 * uc_dim1] * dpnw[iip1 + (jj + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1] * (-on[ip1 + (j + kp1 * on_dim2) * on_dim1]
			 * dpw[iip1 + (jj + kkp1 * dpw_dim2) * dpw_dim1] + oc[
			ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1] * dpnw[iip1 + (
			jj + kkp1 * dpnw_dim2) * dpnw_dim1] - uc[ip1 + (jp1 + 
			kp1 * uc_dim2) * uc_dim1] * opnw[iip1 + (jj + kkp1 * 
			opnw_dim2) * opnw_dim1] - oe[ip1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * dpn[iip1 + (jj + kkp1 * 
			dpn_dim2) * dpn_dim1]);
/* * ******************************************************************** */
/* * *** > uW; */
/* * ******************************************************************** */
		xuw[ii + (jj + kk * xuw_dim2) * xuw_dim1] = opsw[ii + (jj + 
			kk * opsw_dim2) * opsw_dim1] * uc[im1 + (jm1 + k * 
			uc_dim2) * uc_dim1] * dpse[iim1 + (jj + kkp1 * 
			dpse_dim2) * dpse_dim1] - upsw[ii + (jj + kk * 
			upsw_dim2) * upsw_dim1] * (-oe[im2 + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * dps[iim1 + (jj + kkp1 * 
			dps_dim2) * dps_dim1] + oc[im1 + (jm1 + kp1 * oc_dim2)
			 * oc_dim1] * dpse[iim1 + (jj + kkp1 * dpse_dim2) * 
			dpse_dim1] - uc[im1 + (jm1 + kp1 * uc_dim2) * uc_dim1]
			 * opse[iim1 + (jj + kkp1 * opse_dim2) * opse_dim1] - 
			on[im1 + (jm1 + kp1 * on_dim2) * on_dim1] * dpe[iim1 
			+ (jj + kkp1 * dpe_dim2) * dpe_dim1]) + opw[ii + (jj 
			+ kk * opw_dim2) * opw_dim1] * uc[im1 + (j + k * 
			uc_dim2) * uc_dim1] * dpe[iim1 + (jj + kkp1 * 
			dpe_dim2) * dpe_dim1] - upw[ii + (jj + kk * upw_dim2) 
			* upw_dim1] * (-oe[im2 + (j + kp1 * oe_dim2) * 
			oe_dim1] * dpc[iim1 + (jj + kkp1 * dpc_dim2) * 
			dpc_dim1] - on[im1 + (jm1 + kp1 * on_dim2) * on_dim1] 
			* dpse[iim1 + (jj + kkp1 * dpse_dim2) * dpse_dim1] + 
			oc[im1 + (j + kp1 * oc_dim2) * oc_dim1] * dpe[iim1 + (
			jj + kkp1 * dpe_dim2) * dpe_dim1] - uc[im1 + (j + kp1 
			* uc_dim2) * uc_dim1] * ope[iim1 + (jj + kkp1 * 
			ope_dim2) * ope_dim1] - on[im1 + (j + kp1 * on_dim2) *
			 on_dim1] * dpne[iim1 + (jj + kkp1 * dpne_dim2) * 
			dpne_dim1]) + opnw[ii + (jj + kk * opnw_dim2) * 
			opnw_dim1] * uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] *
			 dpne[iim1 + (jj + kkp1 * dpne_dim2) * dpne_dim1] - 
			upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * (-oe[
			im2 + (jp1 + kp1 * oe_dim2) * oe_dim1] * dpn[iim1 + (
			jj + kkp1 * dpn_dim2) * dpn_dim1] - on[im1 + (j + kp1 
			* on_dim2) * on_dim1] * dpe[iim1 + (jj + kkp1 * 
			dpe_dim2) * dpe_dim1] + oc[im1 + (jp1 + kp1 * oc_dim2)
			 * oc_dim1] * dpne[iim1 + (jj + kkp1 * dpne_dim2) * 
			dpne_dim1] - uc[im1 + (jp1 + kp1 * uc_dim2) * uc_dim1]
			 * opne[iim1 + (jj + kkp1 * opne_dim2) * opne_dim1]) 
			+ ups[ii + (jj + kk * ups_dim2) * ups_dim1] * oe[im1 
			+ (jm1 + kp1 * oe_dim2) * oe_dim1] * dpse[iim1 + (jj 
			+ kkp1 * dpse_dim2) * dpse_dim1] + upc[ii + (jj + kk *
			 upc_dim2) * upc_dim1] * oe[im1 + (j + kp1 * oe_dim2) 
			* oe_dim1] * dpe[iim1 + (jj + kkp1 * dpe_dim2) * 
			dpe_dim1] + upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			* oe[im1 + (jp1 + kp1 * oe_dim2) * oe_dim1] * dpne[
			iim1 + (jj + kkp1 * dpne_dim2) * dpne_dim1];
/* * ******************************************************************** */
/* * *** > uN; */
/* * ******************************************************************** */
		xun[ii + (jj + kk * xun_dim2) * xun_dim1] = upw[ii + (jj + kk 
			* upw_dim2) * upw_dim1] * on[im1 + (j + kp1 * on_dim2)
			 * on_dim1] * dpsw[ii + (jjp1 + kkp1 * dpsw_dim2) * 
			dpsw_dim1] + opnw[ii + (jj + kk * opnw_dim2) * 
			opnw_dim1] * uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] *
			 dpsw[ii + (jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - 
			upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * (oc[
			im1 + (jp1 + kp1 * oc_dim2) * oc_dim1] * dpsw[ii + (
			jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - uc[im1 + (jp1 
			+ kp1 * uc_dim2) * uc_dim1] * opsw[ii + (jjp1 + kkp1 *
			 opsw_dim2) * opsw_dim1] - on[im1 + (jp1 + kp1 * 
			on_dim2) * on_dim1] * dpw[ii + (jjp1 + kkp1 * 
			dpw_dim2) * dpw_dim1] - oe[im1 + (jp1 + kp1 * oe_dim2)
			 * oe_dim1] * dps[ii + (jjp1 + kkp1 * dps_dim2) * 
			dps_dim1]) + upc[ii + (jj + kk * upc_dim2) * upc_dim1]
			 * on[i__ + (j + kp1 * on_dim2) * on_dim1] * dps[ii + 
			(jjp1 + kkp1 * dps_dim2) * dps_dim1] + opn[ii + (jj + 
			kk * opn_dim2) * opn_dim1] * uc[i__ + (jp1 + k * 
			uc_dim2) * uc_dim1] * dps[ii + (jjp1 + kkp1 * 
			dps_dim2) * dps_dim1] - upn[ii + (jj + kk * upn_dim2) 
			* upn_dim1] * (-oe[im1 + (jp1 + kp1 * oe_dim2) * 
			oe_dim1] * dpsw[ii + (jjp1 + kkp1 * dpsw_dim2) * 
			dpsw_dim1] + oc[i__ + (jp1 + kp1 * oc_dim2) * oc_dim1]
			 * dps[ii + (jjp1 + kkp1 * dps_dim2) * dps_dim1] - uc[
			i__ + (jp1 + kp1 * uc_dim2) * uc_dim1] * ops[ii + (
			jjp1 + kkp1 * ops_dim2) * ops_dim1] - on[i__ + (jp1 + 
			kp1 * on_dim2) * on_dim1] * dpc[ii + (jjp1 + kkp1 * 
			dpc_dim2) * dpc_dim1] - oe[i__ + (jp1 + kp1 * oe_dim2)
			 * oe_dim1] * dpse[ii + (jjp1 + kkp1 * dpse_dim2) * 
			dpse_dim1]) + upe[ii + (jj + kk * upe_dim2) * 
			upe_dim1] * on[ip1 + (j + kp1 * on_dim2) * on_dim1] * 
			dpse[ii + (jjp1 + kkp1 * dpse_dim2) * dpse_dim1] + 
			opne[ii + (jj + kk * opne_dim2) * opne_dim1] * uc[ip1 
			+ (jp1 + k * uc_dim2) * uc_dim1] * dpse[ii + (jjp1 + 
			kkp1 * dpse_dim2) * dpse_dim1] - upne[ii + (jj + kk * 
			upne_dim2) * upne_dim1] * (-oe[i__ + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * dps[ii + (jjp1 + kkp1 * 
			dps_dim2) * dps_dim1] + oc[ip1 + (jp1 + kp1 * oc_dim2)
			 * oc_dim1] * dpse[ii + (jjp1 + kkp1 * dpse_dim2) * 
			dpse_dim1] - uc[ip1 + (jp1 + kp1 * uc_dim2) * uc_dim1]
			 * opse[ii + (jjp1 + kkp1 * opse_dim2) * opse_dim1] - 
			on[ip1 + (jp1 + kp1 * on_dim2) * on_dim1] * dpe[ii + (
			jjp1 + kkp1 * dpe_dim2) * dpe_dim1]);
/* * ******************************************************************** */
/* * *** > uS; */
/* * ******************************************************************** */
		xus[ii + (jj + kk * xus_dim2) * xus_dim1] = opsw[ii + (jj + 
			kk * opsw_dim2) * opsw_dim1] * uc[im1 + (jm1 + k * 
			uc_dim2) * uc_dim1] * dpnw[ii + (jjm1 + kkp1 * 
			dpnw_dim2) * dpnw_dim1] - upsw[ii + (jj + kk * 
			upsw_dim2) * upsw_dim1] * (-on[im1 + (jm2 + kp1 * 
			on_dim2) * on_dim1] * dpw[ii + (jjm1 + kkp1 * 
			dpw_dim2) * dpw_dim1] + oc[im1 + (jm1 + kp1 * oc_dim2)
			 * oc_dim1] * dpnw[ii + (jjm1 + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - uc[im1 + (jm1 + kp1 * uc_dim2) * uc_dim1]
			 * opnw[ii + (jjm1 + kkp1 * opnw_dim2) * opnw_dim1] - 
			oe[im1 + (jm1 + kp1 * oe_dim2) * oe_dim1] * dpn[ii + (
			jjm1 + kkp1 * dpn_dim2) * dpn_dim1]) + upw[ii + (jj + 
			kk * upw_dim2) * upw_dim1] * on[im1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * dpnw[ii + (jjm1 + kkp1 * 
			dpnw_dim2) * dpnw_dim1] + ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] * uc[i__ + (jm1 + k * uc_dim2) *
			 uc_dim1] * dpn[ii + (jjm1 + kkp1 * dpn_dim2) * 
			dpn_dim1] - ups[ii + (jj + kk * ups_dim2) * ups_dim1] 
			* (-oe[im1 + (jm1 + kp1 * oe_dim2) * oe_dim1] * dpnw[
			ii + (jjm1 + kkp1 * dpnw_dim2) * dpnw_dim1] - on[i__ 
			+ (jm2 + kp1 * on_dim2) * on_dim1] * dpc[ii + (jjm1 + 
			kkp1 * dpc_dim2) * dpc_dim1] + oc[i__ + (jm1 + kp1 * 
			oc_dim2) * oc_dim1] * dpn[ii + (jjm1 + kkp1 * 
			dpn_dim2) * dpn_dim1] - uc[i__ + (jm1 + kp1 * uc_dim2)
			 * uc_dim1] * opn[ii + (jjm1 + kkp1 * opn_dim2) * 
			opn_dim1] - oe[i__ + (jm1 + kp1 * oe_dim2) * oe_dim1] 
			* dpne[ii + (jjm1 + kkp1 * dpne_dim2) * dpne_dim1]) + 
			upc[ii + (jj + kk * upc_dim2) * upc_dim1] * on[i__ + (
			jm1 + kp1 * on_dim2) * on_dim1] * dpn[ii + (jjm1 + 
			kkp1 * dpn_dim2) * dpn_dim1] + opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] * uc[ip1 + (jm1 + k * uc_dim2)
			 * uc_dim1] * dpne[ii + (jjm1 + kkp1 * dpne_dim2) * 
			dpne_dim1] - upse[ii + (jj + kk * upse_dim2) * 
			upse_dim1] * (-oe[i__ + (jm1 + kp1 * oe_dim2) * 
			oe_dim1] * dpn[ii + (jjm1 + kkp1 * dpn_dim2) * 
			dpn_dim1] - on[ip1 + (jm2 + kp1 * on_dim2) * on_dim1] 
			* dpe[ii + (jjm1 + kkp1 * dpe_dim2) * dpe_dim1] + oc[
			ip1 + (jm1 + kp1 * oc_dim2) * oc_dim1] * dpne[ii + (
			jjm1 + kkp1 * dpne_dim2) * dpne_dim1] - uc[ip1 + (jm1 
			+ kp1 * uc_dim2) * uc_dim1] * opne[ii + (jjm1 + kkp1 *
			 opne_dim2) * opne_dim1]) + upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1] * on[ip1 + (jm1 + kp1 * on_dim2)
			 * on_dim1] * dpne[ii + (jjm1 + kkp1 * dpne_dim2) * 
			dpne_dim1];
/* * ******************************************************************** */
/* * *** > uNE; */
/* * ******************************************************************** */
		xune[ii + (jj + kk * xune_dim2) * xune_dim1] = upn[ii + (jj + 
			kk * upn_dim2) * upn_dim1] * oe[i__ + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * dpsw[iip1 + (jjp1 + kkp1 * 
			dpsw_dim2) * dpsw_dim1] + upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1] * on[ip1 + (j + kp1 * on_dim2) *
			 on_dim1] * dpsw[iip1 + (jjp1 + kkp1 * dpsw_dim2) * 
			dpsw_dim1] + opne[ii + (jj + kk * opne_dim2) * 
			opne_dim1] * uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1] *
			 dpsw[iip1 + (jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - 
			upne[ii + (jj + kk * upne_dim2) * upne_dim1] * (oc[
			ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1] * dpsw[iip1 + (
			jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - uc[ip1 + (jp1 
			+ kp1 * uc_dim2) * uc_dim1] * opsw[iip1 + (jjp1 + 
			kkp1 * opsw_dim2) * opsw_dim1] - on[ip1 + (jp1 + kp1 *
			 on_dim2) * on_dim1] * dpw[iip1 + (jjp1 + kkp1 * 
			dpw_dim2) * dpw_dim1] - oe[ip1 + (jp1 + kp1 * oe_dim2)
			 * oe_dim1] * dps[iip1 + (jjp1 + kkp1 * dps_dim2) * 
			dps_dim1]);
/* * ******************************************************************** */
/* * *** > uNW; */
/* * ******************************************************************** */
		xunw[ii + (jj + kk * xunw_dim2) * xunw_dim1] = upw[ii + (jj + 
			kk * upw_dim2) * upw_dim1] * on[im1 + (j + kp1 * 
			on_dim2) * on_dim1] * dpse[iim1 + (jjp1 + kkp1 * 
			dpse_dim2) * dpse_dim1] + opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] * uc[im1 + (jp1 + k * uc_dim2)
			 * uc_dim1] * dpse[iim1 + (jjp1 + kkp1 * dpse_dim2) * 
			dpse_dim1] - upnw[ii + (jj + kk * upnw_dim2) * 
			upnw_dim1] * (-oe[im2 + (jp1 + kp1 * oe_dim2) * 
			oe_dim1] * dps[iim1 + (jjp1 + kkp1 * dps_dim2) * 
			dps_dim1] + oc[im1 + (jp1 + kp1 * oc_dim2) * oc_dim1] 
			* dpse[iim1 + (jjp1 + kkp1 * dpse_dim2) * dpse_dim1] 
			- uc[im1 + (jp1 + kp1 * uc_dim2) * uc_dim1] * opse[
			iim1 + (jjp1 + kkp1 * opse_dim2) * opse_dim1] - on[
			im1 + (jp1 + kp1 * on_dim2) * on_dim1] * dpe[iim1 + (
			jjp1 + kkp1 * dpe_dim2) * dpe_dim1]) + upn[ii + (jj + 
			kk * upn_dim2) * upn_dim1] * oe[im1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * dpse[iim1 + (jjp1 + kkp1 * 
			dpse_dim2) * dpse_dim1];
/* * ******************************************************************** */
/* * *** > uSE; */
/* * ******************************************************************** */
		xuse[ii + (jj + kk * xuse_dim2) * xuse_dim1] = ups[ii + (jj + 
			kk * ups_dim2) * ups_dim1] * oe[i__ + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * dpnw[iip1 + (jjm1 + kkp1 * 
			dpnw_dim2) * dpnw_dim1] + opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] * uc[ip1 + (jm1 + k * uc_dim2)
			 * uc_dim1] * dpnw[iip1 + (jjm1 + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - upse[ii + (jj + kk * upse_dim2) * 
			upse_dim1] * (-on[ip1 + (jm2 + kp1 * on_dim2) * 
			on_dim1] * dpw[iip1 + (jjm1 + kkp1 * dpw_dim2) * 
			dpw_dim1] + oc[ip1 + (jm1 + kp1 * oc_dim2) * oc_dim1] 
			* dpnw[iip1 + (jjm1 + kkp1 * dpnw_dim2) * dpnw_dim1] 
			- uc[ip1 + (jm1 + kp1 * uc_dim2) * uc_dim1] * opnw[
			iip1 + (jjm1 + kkp1 * opnw_dim2) * opnw_dim1] - oe[
			ip1 + (jm1 + kp1 * oe_dim2) * oe_dim1] * dpn[iip1 + (
			jjm1 + kkp1 * dpn_dim2) * dpn_dim1]) + upe[ii + (jj + 
			kk * upe_dim2) * upe_dim1] * on[ip1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * dpnw[iip1 + (jjm1 + kkp1 * 
			dpnw_dim2) * dpnw_dim1];
/* * ******************************************************************** */
/* * *** > uSW; */
/* * ******************************************************************** */
		xusw[ii + (jj + kk * xusw_dim2) * xusw_dim1] = opsw[ii + (jj 
			+ kk * opsw_dim2) * opsw_dim1] * uc[im1 + (jm1 + k * 
			uc_dim2) * uc_dim1] * dpne[iim1 + (jjm1 + kkp1 * 
			dpne_dim2) * dpne_dim1] - upsw[ii + (jj + kk * 
			upsw_dim2) * upsw_dim1] * (-oe[im2 + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * dpn[iim1 + (jjm1 + kkp1 * 
			dpn_dim2) * dpn_dim1] - on[im1 + (jm2 + kp1 * on_dim2)
			 * on_dim1] * dpe[iim1 + (jjm1 + kkp1 * dpe_dim2) * 
			dpe_dim1] + oc[im1 + (jm1 + kp1 * oc_dim2) * oc_dim1] 
			* dpne[iim1 + (jjm1 + kkp1 * dpne_dim2) * dpne_dim1] 
			- uc[im1 + (jm1 + kp1 * uc_dim2) * uc_dim1] * opne[
			iim1 + (jjm1 + kkp1 * opne_dim2) * opne_dim1]) + upw[
			ii + (jj + kk * upw_dim2) * upw_dim1] * on[im1 + (jm1 
			+ kp1 * on_dim2) * on_dim1] * dpne[iim1 + (jjm1 + 
			kkp1 * dpne_dim2) * dpne_dim1] + ups[ii + (jj + kk * 
			ups_dim2) * ups_dim1] * oe[im1 + (jm1 + kp1 * oe_dim2)
			 * oe_dim1] * dpne[iim1 + (jjm1 + kkp1 * dpne_dim2) * 
			dpne_dim1];
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
} /* buildg_7__ */

/* Subroutine */ int buildg_27__(integer *nxf, integer *nyf, integer *nzf, 
	integer *nx, integer *ny, integer *nz, doublereal *opc, doublereal *
	opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *
	opne, doublereal *opnw, doublereal *opse, doublereal *opsw, 
	doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, 
	doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse,
	 doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, 
	doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, 
	doublereal *dpse, doublereal *dpsw, doublereal *oc, doublereal *oe, 
	doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, 
	doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, 
	doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, 
	doublereal *xoc, doublereal *xoe, doublereal *xon, doublereal *xuc, 
	doublereal *xone, doublereal *xonw, doublereal *xue, doublereal *xuw, 
	doublereal *xun, doublereal *xus, doublereal *xune, doublereal *xunw, 
	doublereal *xuse, doublereal *xusw)
{
    /* System generated locals */
    integer oc_dim1, oc_dim2, oc_offset, oe_dim1, oe_dim2, oe_offset, on_dim1,
	     on_dim2, on_offset, uc_dim1, uc_dim2, uc_offset, one_dim1, 
	    one_dim2, one_offset, onw_dim1, onw_dim2, onw_offset, ue_dim1, 
	    ue_dim2, ue_offset, uw_dim1, uw_dim2, uw_offset, un_dim1, un_dim2,
	     un_offset, us_dim1, us_dim2, us_offset, une_dim1, une_dim2, 
	    une_offset, unw_dim1, unw_dim2, unw_offset, use_dim1, use_dim2, 
	    use_offset, usw_dim1, usw_dim2, usw_offset, xoc_dim1, xoc_dim2, 
	    xoc_offset, xoe_dim1, xoe_dim2, xoe_offset, xon_dim1, xon_dim2, 
	    xon_offset, xuc_dim1, xuc_dim2, xuc_offset, xone_dim1, xone_dim2, 
	    xone_offset, xonw_dim1, xonw_dim2, xonw_offset, xue_dim1, 
	    xue_dim2, xue_offset, xuw_dim1, xuw_dim2, xuw_offset, xun_dim1, 
	    xun_dim2, xun_offset, xus_dim1, xus_dim2, xus_offset, xune_dim1, 
	    xune_dim2, xune_offset, xunw_dim1, xunw_dim2, xunw_offset, 
	    xuse_dim1, xuse_dim2, xuse_offset, xusw_dim1, xusw_dim2, 
	    xusw_offset, opc_dim1, opc_dim2, opc_offset, opn_dim1, opn_dim2, 
	    opn_offset, ops_dim1, ops_dim2, ops_offset, ope_dim1, ope_dim2, 
	    ope_offset, opw_dim1, opw_dim2, opw_offset, opne_dim1, opne_dim2, 
	    opne_offset, opnw_dim1, opnw_dim2, opnw_offset, opse_dim1, 
	    opse_dim2, opse_offset, opsw_dim1, opsw_dim2, opsw_offset, 
	    upc_dim1, upc_dim2, upc_offset, upn_dim1, upn_dim2, upn_offset, 
	    ups_dim1, ups_dim2, ups_offset, upe_dim1, upe_dim2, upe_offset, 
	    upw_dim1, upw_dim2, upw_offset, upne_dim1, upne_dim2, upne_offset,
	     upnw_dim1, upnw_dim2, upnw_offset, upse_dim1, upse_dim2, 
	    upse_offset, upsw_dim1, upsw_dim2, upsw_offset, dpc_dim1, 
	    dpc_dim2, dpc_offset, dpn_dim1, dpn_dim2, dpn_offset, dps_dim1, 
	    dps_dim2, dps_offset, dpe_dim1, dpe_dim2, dpe_offset, dpw_dim1, 
	    dpw_dim2, dpw_offset, dpne_dim1, dpne_dim2, dpne_offset, 
	    dpnw_dim1, dpnw_dim2, dpnw_offset, dpse_dim1, dpse_dim2, 
	    dpse_offset, dpsw_dim1, dpsw_dim2, dpsw_offset, i__1, i__2, i__3;

    /* Local variables */
    static doublereal tmp1_xoc__, tmp2_xoc__, tmp3_xoc__, tmp4_xoc__, 
	    tmp5_xoc__, tmp6_xoc__, tmp7_xoc__, tmp8_xoc__, tmp9_xoc__, 
	    tmp1_xoe__, tmp2_xoe__, tmp3_xoe__, tmp4_xoe__, tmp5_xoe__, 
	    tmp6_xoe__, tmp7_xoe__, tmp8_xoe__, tmp9_xoe__, tmp1_xon__, 
	    tmp2_xon__, tmp3_xon__, tmp4_xon__, tmp5_xon__, tmp6_xon__, 
	    tmp7_xon__, tmp8_xon__, tmp9_xon__, tmp1_xuc__, tmp2_xuc__, 
	    tmp3_xuc__, tmp4_xuc__, tmp5_xuc__, tmp6_xuc__, tmp7_xuc__, 
	    tmp8_xuc__, tmp9_xuc__, tmp1_xue__, tmp2_xue__, tmp3_xue__, 
	    tmp4_xue__, tmp5_xue__, tmp6_xue__, tmp1_xuw__, tmp2_xuw__, 
	    tmp3_xuw__, tmp4_xuw__, tmp5_xuw__, tmp10_xoc__, tmp11_xoc__, 
	    tmp12_xoc__, tmp13_xoc__, tmp14_xoc__, tmp15_xoc__, tmp16_xoc__, 
	    tmp17_xoc__, tmp18_xoc__, tmp19_xoc__, tmp20_xoc__, tmp21_xoc__, 
	    tmp22_xoc__, tmp23_xoc__, tmp24_xoc__, tmp25_xoc__, tmp26_xoc__, 
	    tmp27_xoc__, tmp10_xoe__, tmp11_xoe__, tmp12_xoe__, tmp10_xon__, 
	    tmp11_xon__, tmp12_xon__, tmp10_xuc__, tmp11_xuc__, tmp12_xuc__, 
	    tmp6_xuw__, tmp1_xun__, tmp2_xun__, tmp3_xun__, tmp4_xun__, 
	    tmp5_xun__, tmp6_xun__, tmp1_xus__, tmp2_xus__, tmp3_xus__, 
	    tmp4_xus__, tmp5_xus__, tmp6_xus__;
    static integer i__, j, k;
    static doublereal tmp1_xone__, tmp2_xone__, tmp3_xone__, tmp4_xone__, 
	    tmp5_xone__, tmp6_xone__, tmp1_xune__, tmp2_xune__, tmp1_xuse__, 
	    tmp2_xuse__, tmp1_xonw__, tmp2_xonw__, tmp3_xonw__, tmp4_xonw__, 
	    tmp5_xonw__, tmp6_xonw__, tmp1_xunw__, tmp2_xunw__, tmp1_xusw__, 
	    tmp2_xusw__;
    static integer ii, jj, kk, im1, im2, jm1, ip1, ip2, jp1, jm2, jp2, km1, 
	    kp1, km2, kp2, iim1, jjm1, iip1, kkm1, jjp1, kkp1, nxm1, nym1, 
	    nzm1;

/* * ******************************************************************** */
/* * purpose: compute a 27-point galerkin coarse grid matrix from */
/* *          a 27-point fine grid matrix. */
/* * */
/* * expressions for the galerkin coarse grid stencil XA in terms of */
/* * the fine grid matrix stencil A and the interpolation operator */
/* * stencil P.  these stencils have the form: */
/* * */
/* *    XA := array([ */
/* * */
/* *      matrix([ */
/* *         [ -XdNW(i,j,k), -XdN(i,j,k), -XdNE(i,j,k) ], */
/* *         [ -XdW(i,j,k),  -XdC(i,j,k), -XdE(i,j,k)  ], */
/* *         [ -XdSW(i,j,k), -XdS(i,j,k), -XdSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ -XoNW(i,j,k), -XoN(i,j,k), -XoNE(i,j,k) ], */
/* *         [ -XoW(i,j,k),   XoC(i,j,k), -XoE(i,j,k)  ], */
/* *         [ -XoSW(i,j,k), -XoS(i,j,k), -XoSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ -XuNW(i,j,k), -XuN(i,j,k), -XuNE(i,j,k) ], */
/* *         [ -XuW(i,j,k),  -XuC(i,j,k), -XuE(i,j,k)  ], */
/* *         [ -XuSW(i,j,k), -XuS(i,j,k), -XuSE(i,j,k) ] */
/* *      ]) */
/* *    ]): */
/* * */
/* *    A := array([ */
/* * */
/* *      matrix([ */
/* *         [ -dNW(i,j,k), -dN(i,j,k), -dNE(i,j,k) ], */
/* *         [ -dW(i,j,k),  -dC(i,j,k), -dE(i,j,k)  ], */
/* *         [ -dSW(i,j,k), -dS(i,j,k), -dSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ -oNW(i,j,k), -oN(i,j,k), -oNE(i,j,k) ], */
/* *         [ -oW(i,j,k),   oC(i,j,k), -oE(i,j,k)  ], */
/* *         [ -oSW(i,j,k), -oS(i,j,k), -oSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ -uNW(i,j,k), -uN(i,j,k), -uNE(i,j,k) ], */
/* *         [ -uW(i,j,k),  -uC(i,j,k), -uE(i,j,k)  ], */
/* *         [ -uSW(i,j,k), -uS(i,j,k), -uSE(i,j,k) ] */
/* *      ]) */
/* *    ]): */
/* * */
/* *   P := array([ */
/* * */
/* *      matrix([ */
/* *         [ dPNW(i,j,k), dPN(i,j,k), dPNE(i,j,k) ], */
/* *         [ dPW(i,j,k),  dPC(i,j,k), dPE(i,j,k)  ], */
/* *         [ dPSW(i,j,k), dPS(i,j,k), dPSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ oPNW(i,j,k), oPN(i,j,k), oPNE(i,j,k) ], */
/* *         [ oPW(i,j,k),  oPC(i,j,k), oPE(i,j,k)  ], */
/* *         [ oPSW(i,j,k), oPS(i,j,k), oPSE(i,j,k) ] */
/* *      ]), */
/* * */
/* *      matrix([ */
/* *         [ uPNW(i,j,k), uPN(i,j,k), uPNE(i,j,k) ], */
/* *         [ uPW(i,j,k),  uPC(i,j,k), uPE(i,j,k)  ], */
/* *         [ uPSW(i,j,k), uPS(i,j,k), uPSE(i,j,k) ] */
/* *      ]) */
/* *    ]): */
/* * */
/* * in addition, A is assumed to be symmetric so that: */
/* * */
/* *    oS  := proc(x,y,z) RETURN( oN(x,y-1,z) ): end: */
/* *    oW  := proc(x,y,z) RETURN( oE(x-1,y,z) ): end: */
/* *    oSE := proc(x,y,z) RETURN( oNW(x+1,y-1,z) ): end: */
/* *    oSW := proc(x,y,z) RETURN( oNE(x-1,y-1,z) ): end: */
/* * */
/* *    dC  := proc(x,y,z) RETURN( uC(x,y,z-1) ): end: */
/* *    dW  := proc(x,y,z) RETURN( uE(x-1,y,z-1) ): end: */
/* *    dE  := proc(x,y,z) RETURN( uW(x+1,y,z-1) ): end: */
/* * */
/* *    dN  := proc(x,y,z) RETURN( uS(x,y+1,z-1) ): end: */
/* *    dNW := proc(x,y,z) RETURN( uSE(x-1,y+1,z-1) ): end: */
/* *    dNE := proc(x,y,z) RETURN( uSW(x+1,y+1,z-1) ): end: */
/* * */
/* *    dS  := proc(x,y,z) RETURN( uN(x,y-1,z-1) ): end: */
/* *    dSW := proc(x,y,z) RETURN( uNE(x-1,y-1,z-1) ): end: */
/* *    dSE := proc(x,y,z) RETURN( uNW(x+1,y-1,z-1) ): end: */
/* * */
/* * author:  michael holst */
/* * ******************************************************************** */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** define n and determine number of mesh points *** */
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
    xusw_dim1 = *nx;
    xusw_dim2 = *ny;
    xusw_offset = 1 + xusw_dim1 * (1 + xusw_dim2);
    xusw -= xusw_offset;
    xuse_dim1 = *nx;
    xuse_dim2 = *ny;
    xuse_offset = 1 + xuse_dim1 * (1 + xuse_dim2);
    xuse -= xuse_offset;
    xunw_dim1 = *nx;
    xunw_dim2 = *ny;
    xunw_offset = 1 + xunw_dim1 * (1 + xunw_dim2);
    xunw -= xunw_offset;
    xune_dim1 = *nx;
    xune_dim2 = *ny;
    xune_offset = 1 + xune_dim1 * (1 + xune_dim2);
    xune -= xune_offset;
    xus_dim1 = *nx;
    xus_dim2 = *ny;
    xus_offset = 1 + xus_dim1 * (1 + xus_dim2);
    xus -= xus_offset;
    xun_dim1 = *nx;
    xun_dim2 = *ny;
    xun_offset = 1 + xun_dim1 * (1 + xun_dim2);
    xun -= xun_offset;
    xuw_dim1 = *nx;
    xuw_dim2 = *ny;
    xuw_offset = 1 + xuw_dim1 * (1 + xuw_dim2);
    xuw -= xuw_offset;
    xue_dim1 = *nx;
    xue_dim2 = *ny;
    xue_offset = 1 + xue_dim1 * (1 + xue_dim2);
    xue -= xue_offset;
    xonw_dim1 = *nx;
    xonw_dim2 = *ny;
    xonw_offset = 1 + xonw_dim1 * (1 + xonw_dim2);
    xonw -= xonw_offset;
    xone_dim1 = *nx;
    xone_dim2 = *ny;
    xone_offset = 1 + xone_dim1 * (1 + xone_dim2);
    xone -= xone_offset;
    xuc_dim1 = *nx;
    xuc_dim2 = *ny;
    xuc_offset = 1 + xuc_dim1 * (1 + xuc_dim2);
    xuc -= xuc_offset;
    xon_dim1 = *nx;
    xon_dim2 = *ny;
    xon_offset = 1 + xon_dim1 * (1 + xon_dim2);
    xon -= xon_offset;
    xoe_dim1 = *nx;
    xoe_dim2 = *ny;
    xoe_offset = 1 + xoe_dim1 * (1 + xoe_dim2);
    xoe -= xoe_offset;
    xoc_dim1 = *nx;
    xoc_dim2 = *ny;
    xoc_offset = 1 + xoc_dim1 * (1 + xoc_dim2);
    xoc -= xoc_offset;
    dpsw_dim1 = *nx;
    dpsw_dim2 = *ny;
    dpsw_offset = 1 + dpsw_dim1 * (1 + dpsw_dim2);
    dpsw -= dpsw_offset;
    dpse_dim1 = *nx;
    dpse_dim2 = *ny;
    dpse_offset = 1 + dpse_dim1 * (1 + dpse_dim2);
    dpse -= dpse_offset;
    dpnw_dim1 = *nx;
    dpnw_dim2 = *ny;
    dpnw_offset = 1 + dpnw_dim1 * (1 + dpnw_dim2);
    dpnw -= dpnw_offset;
    dpne_dim1 = *nx;
    dpne_dim2 = *ny;
    dpne_offset = 1 + dpne_dim1 * (1 + dpne_dim2);
    dpne -= dpne_offset;
    dpw_dim1 = *nx;
    dpw_dim2 = *ny;
    dpw_offset = 1 + dpw_dim1 * (1 + dpw_dim2);
    dpw -= dpw_offset;
    dpe_dim1 = *nx;
    dpe_dim2 = *ny;
    dpe_offset = 1 + dpe_dim1 * (1 + dpe_dim2);
    dpe -= dpe_offset;
    dps_dim1 = *nx;
    dps_dim2 = *ny;
    dps_offset = 1 + dps_dim1 * (1 + dps_dim2);
    dps -= dps_offset;
    dpn_dim1 = *nx;
    dpn_dim2 = *ny;
    dpn_offset = 1 + dpn_dim1 * (1 + dpn_dim2);
    dpn -= dpn_offset;
    dpc_dim1 = *nx;
    dpc_dim2 = *ny;
    dpc_offset = 1 + dpc_dim1 * (1 + dpc_dim2);
    dpc -= dpc_offset;
    upsw_dim1 = *nx;
    upsw_dim2 = *ny;
    upsw_offset = 1 + upsw_dim1 * (1 + upsw_dim2);
    upsw -= upsw_offset;
    upse_dim1 = *nx;
    upse_dim2 = *ny;
    upse_offset = 1 + upse_dim1 * (1 + upse_dim2);
    upse -= upse_offset;
    upnw_dim1 = *nx;
    upnw_dim2 = *ny;
    upnw_offset = 1 + upnw_dim1 * (1 + upnw_dim2);
    upnw -= upnw_offset;
    upne_dim1 = *nx;
    upne_dim2 = *ny;
    upne_offset = 1 + upne_dim1 * (1 + upne_dim2);
    upne -= upne_offset;
    upw_dim1 = *nx;
    upw_dim2 = *ny;
    upw_offset = 1 + upw_dim1 * (1 + upw_dim2);
    upw -= upw_offset;
    upe_dim1 = *nx;
    upe_dim2 = *ny;
    upe_offset = 1 + upe_dim1 * (1 + upe_dim2);
    upe -= upe_offset;
    ups_dim1 = *nx;
    ups_dim2 = *ny;
    ups_offset = 1 + ups_dim1 * (1 + ups_dim2);
    ups -= ups_offset;
    upn_dim1 = *nx;
    upn_dim2 = *ny;
    upn_offset = 1 + upn_dim1 * (1 + upn_dim2);
    upn -= upn_offset;
    upc_dim1 = *nx;
    upc_dim2 = *ny;
    upc_offset = 1 + upc_dim1 * (1 + upc_dim2);
    upc -= upc_offset;
    opsw_dim1 = *nx;
    opsw_dim2 = *ny;
    opsw_offset = 1 + opsw_dim1 * (1 + opsw_dim2);
    opsw -= opsw_offset;
    opse_dim1 = *nx;
    opse_dim2 = *ny;
    opse_offset = 1 + opse_dim1 * (1 + opse_dim2);
    opse -= opse_offset;
    opnw_dim1 = *nx;
    opnw_dim2 = *ny;
    opnw_offset = 1 + opnw_dim1 * (1 + opnw_dim2);
    opnw -= opnw_offset;
    opne_dim1 = *nx;
    opne_dim2 = *ny;
    opne_offset = 1 + opne_dim1 * (1 + opne_dim2);
    opne -= opne_offset;
    opw_dim1 = *nx;
    opw_dim2 = *ny;
    opw_offset = 1 + opw_dim1 * (1 + opw_dim2);
    opw -= opw_offset;
    ope_dim1 = *nx;
    ope_dim2 = *ny;
    ope_offset = 1 + ope_dim1 * (1 + ope_dim2);
    ope -= ope_offset;
    ops_dim1 = *nx;
    ops_dim2 = *ny;
    ops_offset = 1 + ops_dim1 * (1 + ops_dim2);
    ops -= ops_offset;
    opn_dim1 = *nx;
    opn_dim2 = *ny;
    opn_offset = 1 + opn_dim1 * (1 + opn_dim2);
    opn -= opn_offset;
    opc_dim1 = *nx;
    opc_dim2 = *ny;
    opc_offset = 1 + opc_dim1 * (1 + opc_dim2);
    opc -= opc_offset;

    /* Function Body */
    nxm1 = *nx - 1;
    nym1 = *ny - 1;
    nzm1 = *nz - 1;
/* * */
/* *    *** build the operator *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (kk = 2; kk <= i__1; ++kk) {
	k = (kk << 1) - 1;
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (jj = 2; jj <= i__2; ++jj) {
	    j = (jj << 1) - 1;
/* mdir 3 3 */
	    i__3 = *nx - 1;
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
/* * *** > oC; */
/* * ******************************************************************** */
/* * ***XoC(ii,jj,kk) = */
		tmp1_xoc__ = opn[ii + (jj + kk * opn_dim2) * opn_dim1] * (
			-une[im1 + (j + km1 * une_dim2) * une_dim1] * dpw[ii 
			+ (jj + kk * dpw_dim2) * dpw_dim1] - one[im1 + (j + k 
			* one_dim2) * one_dim1] * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] - usw[i__ + (jp1 + k * usw_dim2)
			 * usw_dim1] * upw[ii + (jj + kk * upw_dim2) * 
			upw_dim1] - ue[im1 + (jp1 + km1 * ue_dim2) * ue_dim1] 
			* dpnw[ii + (jj + kk * dpnw_dim2) * dpnw_dim1] - oe[
			im1 + (jp1 + k * oe_dim2) * oe_dim1] * opnw[ii + (jj 
			+ kk * opnw_dim2) * opnw_dim1] - uw[i__ + (jp1 + k * 
			uw_dim2) * uw_dim1] * upnw[ii + (jj + kk * upnw_dim2) 
			* upnw_dim1] - un[i__ + (j + km1 * un_dim2) * un_dim1]
			 * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] - on[i__ 
			+ (j + k * on_dim2) * on_dim1] * opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] - us[i__ + (jp1 + k * us_dim2) *
			 us_dim1] * upc[ii + (jj + kk * upc_dim2) * upc_dim1] 
			- uc[i__ + (jp1 + km1 * uc_dim2) * uc_dim1] * dpn[ii 
			+ (jj + kk * dpn_dim2) * dpn_dim1] + oc[i__ + (jp1 + 
			k * oc_dim2) * oc_dim1] * opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] - uc[i__ + (jp1 + k * uc_dim2) *
			 uc_dim1] * upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			- unw[ip1 + (j + km1 * unw_dim2) * unw_dim1] * dpe[ii 
			+ (jj + kk * dpe_dim2) * dpe_dim1] - onw[ip1 + (j + k 
			* onw_dim2) * onw_dim1] * ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] - use[i__ + (jp1 + k * use_dim2)
			 * use_dim1] * upe[ii + (jj + kk * upe_dim2) * 
			upe_dim1] - uw[ip1 + (jp1 + km1 * uw_dim2) * uw_dim1] 
			* dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] - oe[
			i__ + (jp1 + k * oe_dim2) * oe_dim1] * opne[ii + (jj 
			+ kk * opne_dim2) * opne_dim1] - ue[i__ + (jp1 + k * 
			ue_dim2) * ue_dim1] * upne[ii + (jj + kk * upne_dim2) 
			* upne_dim1]);
		tmp2_xoc__ = dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] * (
			-one[im1 + (j + km1 * one_dim2) * one_dim1] * dpw[ii 
			+ (jj + kk * dpw_dim2) * dpw_dim1] - usw[i__ + (jp1 + 
			km1 * usw_dim2) * usw_dim1] * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] - oe[im1 + (jp1 + km1 * oe_dim2)
			 * oe_dim1] * dpnw[ii + (jj + kk * dpnw_dim2) * 
			dpnw_dim1] - uw[i__ + (jp1 + km1 * uw_dim2) * uw_dim1]
			 * opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] - on[
			i__ + (j + km1 * on_dim2) * on_dim1] * dpc[ii + (jj + 
			kk * dpc_dim2) * dpc_dim1] - us[i__ + (jp1 + km1 * 
			us_dim2) * us_dim1] * opc[ii + (jj + kk * opc_dim2) * 
			opc_dim1] + oc[i__ + (jp1 + km1 * oc_dim2) * oc_dim1] 
			* dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] - uc[i__ 
			+ (jp1 + km1 * uc_dim2) * uc_dim1] * opn[ii + (jj + 
			kk * opn_dim2) * opn_dim1] - onw[ip1 + (j + km1 * 
			onw_dim2) * onw_dim1] * dpe[ii + (jj + kk * dpe_dim2) 
			* dpe_dim1] - use[i__ + (jp1 + km1 * use_dim2) * 
			use_dim1] * ope[ii + (jj + kk * ope_dim2) * ope_dim1] 
			- oe[i__ + (jp1 + km1 * oe_dim2) * oe_dim1] * dpne[ii 
			+ (jj + kk * dpne_dim2) * dpne_dim1] - ue[i__ + (jp1 
			+ km1 * ue_dim2) * ue_dim1] * opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1]);
		tmp3_xoc__ = dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] * (
			-one[im1 + (jm1 + km1 * one_dim2) * one_dim1] * dpsw[
			ii + (jj + kk * dpsw_dim2) * dpsw_dim1] - usw[i__ + (
			j + km1 * usw_dim2) * usw_dim1] * opsw[ii + (jj + kk *
			 opsw_dim2) * opsw_dim1] - oe[im1 + (j + km1 * 
			oe_dim2) * oe_dim1] * dpw[ii + (jj + kk * dpw_dim2) * 
			dpw_dim1] - uw[i__ + (j + km1 * uw_dim2) * uw_dim1] * 
			opw[ii + (jj + kk * opw_dim2) * opw_dim1] - onw[i__ + 
			(j + km1 * onw_dim2) * onw_dim1] * dpnw[ii + (jj + kk 
			* dpnw_dim2) * dpnw_dim1] - unw[i__ + (j + km1 * 
			unw_dim2) * unw_dim1] * opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] - on[i__ + (jm1 + km1 * 
			on_dim2) * on_dim1] * dps[ii + (jj + kk * dps_dim2) * 
			dps_dim1] - us[i__ + (j + km1 * us_dim2) * us_dim1] * 
			ops[ii + (jj + kk * ops_dim2) * ops_dim1] + oc[i__ + (
			j + km1 * oc_dim2) * oc_dim1] * dpc[ii + (jj + kk * 
			dpc_dim2) * dpc_dim1] - uc[i__ + (j + km1 * uc_dim2) *
			 uc_dim1] * opc[ii + (jj + kk * opc_dim2) * opc_dim1] 
			- on[i__ + (j + km1 * on_dim2) * on_dim1] * dpn[ii + (
			jj + kk * dpn_dim2) * dpn_dim1] - un[i__ + (j + km1 * 
			un_dim2) * un_dim1] * opn[ii + (jj + kk * opn_dim2) * 
			opn_dim1] - onw[ip1 + (jm1 + km1 * onw_dim2) * 
			onw_dim1] * dpse[ii + (jj + kk * dpse_dim2) * 
			dpse_dim1] - use[i__ + (j + km1 * use_dim2) * 
			use_dim1] * opse[ii + (jj + kk * opse_dim2) * 
			opse_dim1] - oe[i__ + (j + km1 * oe_dim2) * oe_dim1] *
			 dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] - ue[i__ + 
			(j + km1 * ue_dim2) * ue_dim1] * ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] - one[i__ + (j + km1 * one_dim2)
			 * one_dim1] * dpne[ii + (jj + kk * dpne_dim2) * 
			dpne_dim1] - une[i__ + (j + km1 * une_dim2) * 
			une_dim1] * opne[ii + (jj + kk * opne_dim2) * 
			opne_dim1]);
		tmp4_xoc__ = upc[ii + (jj + kk * upc_dim2) * upc_dim1] * (
			-une[im1 + (jm1 + k * une_dim2) * une_dim1] * opsw[ii 
			+ (jj + kk * opsw_dim2) * opsw_dim1] - one[im1 + (jm1 
			+ kp1 * one_dim2) * one_dim1] * upsw[ii + (jj + kk * 
			upsw_dim2) * upsw_dim1] - ue[im1 + (j + k * ue_dim2) *
			 ue_dim1] * opw[ii + (jj + kk * opw_dim2) * opw_dim1] 
			- oe[im1 + (j + kp1 * oe_dim2) * oe_dim1] * upw[ii + (
			jj + kk * upw_dim2) * upw_dim1] - use[im1 + (jp1 + k *
			 use_dim2) * use_dim1] * opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] - onw[i__ + (j + kp1 * 
			onw_dim2) * onw_dim1] * upnw[ii + (jj + kk * 
			upnw_dim2) * upnw_dim1] - un[i__ + (jm1 + k * un_dim2)
			 * un_dim1] * ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1] - on[i__ + (jm1 + kp1 * on_dim2) * on_dim1] 
			* ups[ii + (jj + kk * ups_dim2) * ups_dim1] - uc[i__ 
			+ (j + k * uc_dim2) * uc_dim1] * opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] + oc[i__ + (j + kp1 * oc_dim2) *
			 oc_dim1] * upc[ii + (jj + kk * upc_dim2) * upc_dim1] 
			- us[i__ + (jp1 + k * us_dim2) * us_dim1] * opn[ii + (
			jj + kk * opn_dim2) * opn_dim1] - on[i__ + (j + kp1 * 
			on_dim2) * on_dim1] * upn[ii + (jj + kk * upn_dim2) * 
			upn_dim1] - unw[ip1 + (jm1 + k * unw_dim2) * unw_dim1]
			 * opse[ii + (jj + kk * opse_dim2) * opse_dim1] - onw[
			ip1 + (jm1 + kp1 * onw_dim2) * onw_dim1] * upse[ii + (
			jj + kk * upse_dim2) * upse_dim1] - uw[ip1 + (j + k * 
			uw_dim2) * uw_dim1] * ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1] - oe[i__ + (j + kp1 * oe_dim2) * oe_dim1] * 
			upe[ii + (jj + kk * upe_dim2) * upe_dim1] - usw[ip1 + 
			(jp1 + k * usw_dim2) * usw_dim1] * opne[ii + (jj + kk 
			* opne_dim2) * opne_dim1] - one[i__ + (j + kp1 * 
			one_dim2) * one_dim1] * upne[ii + (jj + kk * 
			upne_dim2) * upne_dim1]);
		tmp5_xoc__ = opc[ii + (jj + kk * opc_dim2) * opc_dim1] * (-uw[
			ip1 + (j + km1 * uw_dim2) * uw_dim1] * dpe[ii + (jj + 
			kk * dpe_dim2) * dpe_dim1] - oe[im1 + (j + k * 
			oe_dim2) * oe_dim1] * opw[ii + (jj + kk * opw_dim2) * 
			opw_dim1] - use[im1 + (jp1 + km1 * use_dim2) * 
			use_dim1] * dpnw[ii + (jj + kk * dpnw_dim2) * 
			dpnw_dim1] - une[im1 + (jm1 + km1 * une_dim2) * 
			une_dim1] * dpsw[ii + (jj + kk * dpsw_dim2) * 
			dpsw_dim1] - un[i__ + (jm1 + km1 * un_dim2) * un_dim1]
			 * dps[ii + (jj + kk * dps_dim2) * dps_dim1] - one[
			im1 + (jm1 + k * one_dim2) * one_dim1] * opsw[ii + (
			jj + kk * opsw_dim2) * opsw_dim1] - ue[im1 + (j + km1 
			* ue_dim2) * ue_dim1] * dpw[ii + (jj + kk * dpw_dim2) 
			* dpw_dim1] - onw[ip1 + (jm1 + k * onw_dim2) * 
			onw_dim1] * opse[ii + (jj + kk * opse_dim2) * 
			opse_dim1] - uc[i__ + (j + km1 * uc_dim2) * uc_dim1] *
			 dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] - unw[ip1 
			+ (jm1 + km1 * unw_dim2) * unw_dim1] * dpse[ii + (jj 
			+ kk * dpse_dim2) * dpse_dim1] - usw[ip1 + (jp1 + km1 
			* usw_dim2) * usw_dim1] * dpne[ii + (jj + kk * 
			dpne_dim2) * dpne_dim1] - us[i__ + (jp1 + km1 * 
			us_dim2) * us_dim1] * dpn[ii + (jj + kk * dpn_dim2) * 
			dpn_dim1] - on[i__ + (jm1 + k * on_dim2) * on_dim1] * 
			ops[ii + (jj + kk * ops_dim2) * ops_dim1] - une[i__ + 
			(j + k * une_dim2) * une_dim1] * upne[ii + (jj + kk * 
			upne_dim2) * upne_dim1] - one[i__ + (j + k * one_dim2)
			 * one_dim1] * opne[ii + (jj + kk * opne_dim2) * 
			opne_dim1] - ue[i__ + (j + k * ue_dim2) * ue_dim1] * 
			upe[ii + (jj + kk * upe_dim2) * upe_dim1] - use[i__ + 
			(j + k * use_dim2) * use_dim1] * upse[ii + (jj + kk * 
			upse_dim2) * upse_dim1] - on[i__ + (j + k * on_dim2) *
			 on_dim1] * opn[ii + (jj + kk * opn_dim2) * opn_dim1] 
			- oe[i__ + (j + k * oe_dim2) * oe_dim1] * ope[ii + (
			jj + kk * ope_dim2) * ope_dim1] - us[i__ + (j + k * 
			us_dim2) * us_dim1] * ups[ii + (jj + kk * ups_dim2) * 
			ups_dim1] + oc[i__ + (j + k * oc_dim2) * oc_dim1] * 
			opc[ii + (jj + kk * opc_dim2) * opc_dim1] - usw[i__ + 
			(j + k * usw_dim2) * usw_dim1] * upsw[ii + (jj + kk * 
			upsw_dim2) * upsw_dim1] - un[i__ + (j + k * un_dim2) *
			 un_dim1] * upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			- uc[i__ + (j + k * uc_dim2) * uc_dim1] * upc[ii + (
			jj + kk * upc_dim2) * upc_dim1] - uw[i__ + (j + k * 
			uw_dim2) * uw_dim1] * upw[ii + (jj + kk * upw_dim2) * 
			upw_dim1] - onw[i__ + (j + k * onw_dim2) * onw_dim1] *
			 opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] - unw[
			i__ + (j + k * unw_dim2) * unw_dim1] * upnw[ii + (jj 
			+ kk * upnw_dim2) * upnw_dim1]);
		tmp6_xoc__ = ups[ii + (jj + kk * ups_dim2) * ups_dim1] * (-ue[
			im1 + (jm1 + k * ue_dim2) * ue_dim1] * opsw[ii + (jj 
			+ kk * opsw_dim2) * opsw_dim1] - oe[im1 + (jm1 + kp1 *
			 oe_dim2) * oe_dim1] * upsw[ii + (jj + kk * upsw_dim2)
			 * upsw_dim1] - use[im1 + (j + k * use_dim2) * 
			use_dim1] * opw[ii + (jj + kk * opw_dim2) * opw_dim1] 
			- onw[i__ + (jm1 + kp1 * onw_dim2) * onw_dim1] * upw[
			ii + (jj + kk * upw_dim2) * upw_dim1] - uc[i__ + (jm1 
			+ k * uc_dim2) * uc_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] + oc[i__ + (jm1 + kp1 * oc_dim2)
			 * oc_dim1] * ups[ii + (jj + kk * ups_dim2) * 
			ups_dim1] - us[i__ + (j + k * us_dim2) * us_dim1] * 
			opc[ii + (jj + kk * opc_dim2) * opc_dim1] - on[i__ + (
			jm1 + kp1 * on_dim2) * on_dim1] * upc[ii + (jj + kk * 
			upc_dim2) * upc_dim1] - uw[ip1 + (jm1 + k * uw_dim2) *
			 uw_dim1] * opse[ii + (jj + kk * opse_dim2) * 
			opse_dim1] - oe[i__ + (jm1 + kp1 * oe_dim2) * oe_dim1]
			 * upse[ii + (jj + kk * upse_dim2) * upse_dim1] - usw[
			ip1 + (j + k * usw_dim2) * usw_dim1] * ope[ii + (jj + 
			kk * ope_dim2) * ope_dim1] - one[i__ + (jm1 + kp1 * 
			one_dim2) * one_dim1] * upe[ii + (jj + kk * upe_dim2) 
			* upe_dim1]);
		tmp7_xoc__ = ops[ii + (jj + kk * ops_dim2) * ops_dim1] * (-ue[
			im1 + (jm1 + km1 * ue_dim2) * ue_dim1] * dpsw[ii + (
			jj + kk * dpsw_dim2) * dpsw_dim1] - oe[im1 + (jm1 + k 
			* oe_dim2) * oe_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] - uw[i__ + (jm1 + k * uw_dim2)
			 * uw_dim1] * upsw[ii + (jj + kk * upsw_dim2) * 
			upsw_dim1] - use[im1 + (j + km1 * use_dim2) * 
			use_dim1] * dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] 
			- onw[i__ + (jm1 + k * onw_dim2) * onw_dim1] * opw[ii 
			+ (jj + kk * opw_dim2) * opw_dim1] - unw[i__ + (jm1 + 
			k * unw_dim2) * unw_dim1] * upw[ii + (jj + kk * 
			upw_dim2) * upw_dim1] - uc[i__ + (jm1 + km1 * uc_dim2)
			 * uc_dim1] * dps[ii + (jj + kk * dps_dim2) * 
			dps_dim1] + oc[i__ + (jm1 + k * oc_dim2) * oc_dim1] * 
			ops[ii + (jj + kk * ops_dim2) * ops_dim1] - uc[i__ + (
			jm1 + k * uc_dim2) * uc_dim1] * ups[ii + (jj + kk * 
			ups_dim2) * ups_dim1] - us[i__ + (j + km1 * us_dim2) *
			 us_dim1] * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] 
			- on[i__ + (jm1 + k * on_dim2) * on_dim1] * opc[ii + (
			jj + kk * opc_dim2) * opc_dim1] - un[i__ + (jm1 + k * 
			un_dim2) * un_dim1] * upc[ii + (jj + kk * upc_dim2) * 
			upc_dim1] - uw[ip1 + (jm1 + km1 * uw_dim2) * uw_dim1] 
			* dpse[ii + (jj + kk * dpse_dim2) * dpse_dim1] - oe[
			i__ + (jm1 + k * oe_dim2) * oe_dim1] * opse[ii + (jj 
			+ kk * opse_dim2) * opse_dim1] - ue[i__ + (jm1 + k * 
			ue_dim2) * ue_dim1] * upse[ii + (jj + kk * upse_dim2) 
			* upse_dim1] - usw[ip1 + (j + km1 * usw_dim2) * 
			usw_dim1] * dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] 
			- one[i__ + (jm1 + k * one_dim2) * one_dim1] * ope[ii 
			+ (jj + kk * ope_dim2) * ope_dim1] - une[i__ + (jm1 + 
			k * une_dim2) * une_dim1] * upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1]);
		tmp8_xoc__ = dps[ii + (jj + kk * dps_dim2) * dps_dim1] * (-oe[
			im1 + (jm1 + km1 * oe_dim2) * oe_dim1] * dpsw[ii + (
			jj + kk * dpsw_dim2) * dpsw_dim1] - uw[i__ + (jm1 + 
			km1 * uw_dim2) * uw_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] - onw[i__ + (jm1 + km1 * 
			onw_dim2) * onw_dim1] * dpw[ii + (jj + kk * dpw_dim2) 
			* dpw_dim1] - unw[i__ + (jm1 + km1 * unw_dim2) * 
			unw_dim1] * opw[ii + (jj + kk * opw_dim2) * opw_dim1] 
			+ oc[i__ + (jm1 + km1 * oc_dim2) * oc_dim1] * dps[ii 
			+ (jj + kk * dps_dim2) * dps_dim1] - uc[i__ + (jm1 + 
			km1 * uc_dim2) * uc_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] - on[i__ + (jm1 + km1 * on_dim2)
			 * on_dim1] * dpc[ii + (jj + kk * dpc_dim2) * 
			dpc_dim1] - un[i__ + (jm1 + km1 * un_dim2) * un_dim1] 
			* opc[ii + (jj + kk * opc_dim2) * opc_dim1] - oe[i__ 
			+ (jm1 + km1 * oe_dim2) * oe_dim1] * dpse[ii + (jj + 
			kk * dpse_dim2) * dpse_dim1] - ue[i__ + (jm1 + km1 * 
			ue_dim2) * ue_dim1] * opse[ii + (jj + kk * opse_dim2) 
			* opse_dim1] - one[i__ + (jm1 + km1 * one_dim2) * 
			one_dim1] * dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] 
			- une[i__ + (jm1 + km1 * une_dim2) * une_dim1] * ope[
			ii + (jj + kk * ope_dim2) * ope_dim1]);
		tmp9_xoc__ = upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * (
			-un[im1 + (j + k * un_dim2) * un_dim1] * opw[ii + (jj 
			+ kk * opw_dim2) * opw_dim1] - on[im1 + (j + kp1 * 
			on_dim2) * on_dim1] * upw[ii + (jj + kk * upw_dim2) * 
			upw_dim1] - uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] * 
			opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] + oc[im1 
			+ (jp1 + kp1 * oc_dim2) * oc_dim1] * upnw[ii + (jj + 
			kk * upnw_dim2) * upnw_dim1] - unw[i__ + (j + k * 
			unw_dim2) * unw_dim1] * opc[ii + (jj + kk * opc_dim2) 
			* opc_dim1] - onw[i__ + (j + kp1 * onw_dim2) * 
			onw_dim1] * upc[ii + (jj + kk * upc_dim2) * upc_dim1] 
			- uw[i__ + (jp1 + k * uw_dim2) * uw_dim1] * opn[ii + (
			jj + kk * opn_dim2) * opn_dim1] - oe[im1 + (jp1 + kp1 
			* oe_dim2) * oe_dim1] * upn[ii + (jj + kk * upn_dim2) 
			* upn_dim1]);
		tmp10_xoc__ = opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] * (
			-un[im1 + (j + km1 * un_dim2) * un_dim1] * dpw[ii + (
			jj + kk * dpw_dim2) * dpw_dim1] - on[im1 + (j + k * 
			on_dim2) * on_dim1] * opw[ii + (jj + kk * opw_dim2) * 
			opw_dim1] - us[im1 + (jp1 + k * us_dim2) * us_dim1] * 
			upw[ii + (jj + kk * upw_dim2) * upw_dim1] - uc[im1 + (
			jp1 + km1 * uc_dim2) * uc_dim1] * dpnw[ii + (jj + kk *
			 dpnw_dim2) * dpnw_dim1] + oc[im1 + (jp1 + k * 
			oc_dim2) * oc_dim1] * opnw[ii + (jj + kk * opnw_dim2) 
			* opnw_dim1] - uc[im1 + (jp1 + k * uc_dim2) * uc_dim1]
			 * upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] - unw[
			i__ + (j + km1 * unw_dim2) * unw_dim1] * dpc[ii + (jj 
			+ kk * dpc_dim2) * dpc_dim1] - onw[i__ + (j + k * 
			onw_dim2) * onw_dim1] * opc[ii + (jj + kk * opc_dim2) 
			* opc_dim1] - use[im1 + (jp1 + k * use_dim2) * 
			use_dim1] * upc[ii + (jj + kk * upc_dim2) * upc_dim1] 
			- uw[i__ + (jp1 + km1 * uw_dim2) * uw_dim1] * dpn[ii 
			+ (jj + kk * dpn_dim2) * dpn_dim1] - oe[im1 + (jp1 + 
			k * oe_dim2) * oe_dim1] * opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] - ue[im1 + (jp1 + k * ue_dim2) *
			 ue_dim1] * upn[ii + (jj + kk * upn_dim2) * upn_dim1])
			;
		tmp11_xoc__ = upw[ii + (jj + kk * upw_dim2) * upw_dim1] * (
			-un[im1 + (jm1 + k * un_dim2) * un_dim1] * opsw[ii + (
			jj + kk * opsw_dim2) * opsw_dim1] - on[im1 + (jm1 + 
			kp1 * on_dim2) * on_dim1] * upsw[ii + (jj + kk * 
			upsw_dim2) * upsw_dim1] - uc[im1 + (j + k * uc_dim2) *
			 uc_dim1] * opw[ii + (jj + kk * opw_dim2) * opw_dim1] 
			+ oc[im1 + (j + kp1 * oc_dim2) * oc_dim1] * upw[ii + (
			jj + kk * upw_dim2) * upw_dim1] - us[im1 + (jp1 + k * 
			us_dim2) * us_dim1] * opnw[ii + (jj + kk * opnw_dim2) 
			* opnw_dim1] - on[im1 + (j + kp1 * on_dim2) * on_dim1]
			 * upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] - unw[
			i__ + (jm1 + k * unw_dim2) * unw_dim1] * ops[ii + (jj 
			+ kk * ops_dim2) * ops_dim1] - onw[i__ + (jm1 + kp1 * 
			onw_dim2) * onw_dim1] * ups[ii + (jj + kk * ups_dim2) 
			* ups_dim1] - uw[i__ + (j + k * uw_dim2) * uw_dim1] * 
			opc[ii + (jj + kk * opc_dim2) * opc_dim1] - oe[im1 + (
			j + kp1 * oe_dim2) * oe_dim1] * upc[ii + (jj + kk * 
			upc_dim2) * upc_dim1] - usw[i__ + (jp1 + k * usw_dim2)
			 * usw_dim1] * opn[ii + (jj + kk * opn_dim2) * 
			opn_dim1] - one[im1 + (j + kp1 * one_dim2) * one_dim1]
			 * upn[ii + (jj + kk * upn_dim2) * upn_dim1]);
		tmp12_xoc__ = dpnw[ii + (jj + kk * dpnw_dim2) * dpnw_dim1] * (
			-on[im1 + (j + km1 * on_dim2) * on_dim1] * dpw[ii + (
			jj + kk * dpw_dim2) * dpw_dim1] - us[im1 + (jp1 + km1 
			* us_dim2) * us_dim1] * opw[ii + (jj + kk * opw_dim2) 
			* opw_dim1] + oc[im1 + (jp1 + km1 * oc_dim2) * 
			oc_dim1] * dpnw[ii + (jj + kk * dpnw_dim2) * 
			dpnw_dim1] - uc[im1 + (jp1 + km1 * uc_dim2) * uc_dim1]
			 * opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] - onw[
			i__ + (j + km1 * onw_dim2) * onw_dim1] * dpc[ii + (jj 
			+ kk * dpc_dim2) * dpc_dim1] - use[im1 + (jp1 + km1 * 
			use_dim2) * use_dim1] * opc[ii + (jj + kk * opc_dim2) 
			* opc_dim1] - oe[im1 + (jp1 + km1 * oe_dim2) * 
			oe_dim1] * dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] 
			- ue[im1 + (jp1 + km1 * ue_dim2) * ue_dim1] * opn[ii 
			+ (jj + kk * opn_dim2) * opn_dim1]);
		tmp13_xoc__ = opw[ii + (jj + kk * opw_dim2) * opw_dim1] * (
			-un[im1 + (jm1 + km1 * un_dim2) * un_dim1] * dpsw[ii 
			+ (jj + kk * dpsw_dim2) * dpsw_dim1] - on[im1 + (jm1 
			+ k * on_dim2) * on_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] - us[im1 + (j + k * us_dim2) *
			 us_dim1] * upsw[ii + (jj + kk * upsw_dim2) * 
			upsw_dim1] - uc[im1 + (j + km1 * uc_dim2) * uc_dim1] *
			 dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] + oc[im1 + 
			(j + k * oc_dim2) * oc_dim1] * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] - uc[im1 + (j + k * uc_dim2) * 
			uc_dim1] * upw[ii + (jj + kk * upw_dim2) * upw_dim1] 
			- us[im1 + (jp1 + km1 * us_dim2) * us_dim1] * dpnw[ii 
			+ (jj + kk * dpnw_dim2) * dpnw_dim1] - on[im1 + (j + 
			k * on_dim2) * on_dim1] * opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] - un[im1 + (j + k * un_dim2) *
			 un_dim1] * upnw[ii + (jj + kk * upnw_dim2) * 
			upnw_dim1] - unw[i__ + (jm1 + km1 * unw_dim2) * 
			unw_dim1] * dps[ii + (jj + kk * dps_dim2) * dps_dim1] 
			- onw[i__ + (jm1 + k * onw_dim2) * onw_dim1] * ops[ii 
			+ (jj + kk * ops_dim2) * ops_dim1] - use[im1 + (j + k 
			* use_dim2) * use_dim1] * ups[ii + (jj + kk * 
			ups_dim2) * ups_dim1] - uw[i__ + (j + km1 * uw_dim2) *
			 uw_dim1] * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] 
			- oe[im1 + (j + k * oe_dim2) * oe_dim1] * opc[ii + (
			jj + kk * opc_dim2) * opc_dim1] - ue[im1 + (j + k * 
			ue_dim2) * ue_dim1] * upc[ii + (jj + kk * upc_dim2) * 
			upc_dim1] - usw[i__ + (jp1 + km1 * usw_dim2) * 
			usw_dim1] * dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] 
			- one[im1 + (j + k * one_dim2) * one_dim1] * opn[ii + 
			(jj + kk * opn_dim2) * opn_dim1] - une[im1 + (j + k * 
			une_dim2) * une_dim1] * upn[ii + (jj + kk * upn_dim2) 
			* upn_dim1]);
		tmp14_xoc__ = upsw[ii + (jj + kk * upsw_dim2) * upsw_dim1] * (
			-uc[im1 + (jm1 + k * uc_dim2) * uc_dim1] * opsw[ii + (
			jj + kk * opsw_dim2) * opsw_dim1] + oc[im1 + (jm1 + 
			kp1 * oc_dim2) * oc_dim1] * upsw[ii + (jj + kk * 
			upsw_dim2) * upsw_dim1] - us[im1 + (j + k * us_dim2) *
			 us_dim1] * opw[ii + (jj + kk * opw_dim2) * opw_dim1] 
			- on[im1 + (jm1 + kp1 * on_dim2) * on_dim1] * upw[ii 
			+ (jj + kk * upw_dim2) * upw_dim1] - uw[i__ + (jm1 + 
			k * uw_dim2) * uw_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] - oe[im1 + (jm1 + kp1 * oe_dim2)
			 * oe_dim1] * ups[ii + (jj + kk * ups_dim2) * 
			ups_dim1] - usw[i__ + (j + k * usw_dim2) * usw_dim1] *
			 opc[ii + (jj + kk * opc_dim2) * opc_dim1] - one[im1 
			+ (jm1 + kp1 * one_dim2) * one_dim1] * upc[ii + (jj + 
			kk * upc_dim2) * upc_dim1]);
		tmp15_xoc__ = opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] * (
			-uc[im1 + (jm1 + km1 * uc_dim2) * uc_dim1] * dpsw[ii 
			+ (jj + kk * dpsw_dim2) * dpsw_dim1] + oc[im1 + (jm1 
			+ k * oc_dim2) * oc_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] - uc[im1 + (jm1 + k * uc_dim2)
			 * uc_dim1] * upsw[ii + (jj + kk * upsw_dim2) * 
			upsw_dim1] - us[im1 + (j + km1 * us_dim2) * us_dim1] *
			 dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] - on[im1 + 
			(jm1 + k * on_dim2) * on_dim1] * opw[ii + (jj + kk * 
			opw_dim2) * opw_dim1] - un[im1 + (jm1 + k * un_dim2) *
			 un_dim1] * upw[ii + (jj + kk * upw_dim2) * upw_dim1] 
			- uw[i__ + (jm1 + km1 * uw_dim2) * uw_dim1] * dps[ii 
			+ (jj + kk * dps_dim2) * dps_dim1] - oe[im1 + (jm1 + 
			k * oe_dim2) * oe_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] - ue[im1 + (jm1 + k * ue_dim2) *
			 ue_dim1] * ups[ii + (jj + kk * ups_dim2) * ups_dim1] 
			- usw[i__ + (j + km1 * usw_dim2) * usw_dim1] * dpc[ii 
			+ (jj + kk * dpc_dim2) * dpc_dim1] - one[im1 + (jm1 + 
			k * one_dim2) * one_dim1] * opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] - une[im1 + (jm1 + k * une_dim2)
			 * une_dim1] * upc[ii + (jj + kk * upc_dim2) * 
			upc_dim1]);
		tmp16_xoc__ = dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] * (
			-on[im1 + (jm1 + km1 * on_dim2) * on_dim1] * dpsw[ii 
			+ (jj + kk * dpsw_dim2) * dpsw_dim1] - us[im1 + (j + 
			km1 * us_dim2) * us_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] + oc[im1 + (j + km1 * oc_dim2)
			 * oc_dim1] * dpw[ii + (jj + kk * dpw_dim2) * 
			dpw_dim1] - uc[im1 + (j + km1 * uc_dim2) * uc_dim1] * 
			opw[ii + (jj + kk * opw_dim2) * opw_dim1] - on[im1 + (
			j + km1 * on_dim2) * on_dim1] * dpnw[ii + (jj + kk * 
			dpnw_dim2) * dpnw_dim1] - un[im1 + (j + km1 * un_dim2)
			 * un_dim1] * opnw[ii + (jj + kk * opnw_dim2) * 
			opnw_dim1] - onw[i__ + (jm1 + km1 * onw_dim2) * 
			onw_dim1] * dps[ii + (jj + kk * dps_dim2) * dps_dim1] 
			- use[im1 + (j + km1 * use_dim2) * use_dim1] * ops[ii 
			+ (jj + kk * ops_dim2) * ops_dim1] - oe[im1 + (j + 
			km1 * oe_dim2) * oe_dim1] * dpc[ii + (jj + kk * 
			dpc_dim2) * dpc_dim1] - ue[im1 + (j + km1 * ue_dim2) *
			 ue_dim1] * opc[ii + (jj + kk * opc_dim2) * opc_dim1] 
			- one[im1 + (j + km1 * one_dim2) * one_dim1] * dpn[ii 
			+ (jj + kk * dpn_dim2) * dpn_dim1] - une[im1 + (j + 
			km1 * une_dim2) * une_dim1] * opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1]);
		tmp17_xoc__ = upne[ii + (jj + kk * upne_dim2) * upne_dim1] * (
			-une[i__ + (j + k * une_dim2) * une_dim1] * opc[ii + (
			jj + kk * opc_dim2) * opc_dim1] - one[i__ + (j + kp1 *
			 one_dim2) * one_dim1] * upc[ii + (jj + kk * upc_dim2)
			 * upc_dim1] - ue[i__ + (jp1 + k * ue_dim2) * ue_dim1]
			 * opn[ii + (jj + kk * opn_dim2) * opn_dim1] - oe[i__ 
			+ (jp1 + kp1 * oe_dim2) * oe_dim1] * upn[ii + (jj + 
			kk * upn_dim2) * upn_dim1] - un[ip1 + (j + k * 
			un_dim2) * un_dim1] * ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1] - on[ip1 + (j + kp1 * on_dim2) * on_dim1] * 
			upe[ii + (jj + kk * upe_dim2) * upe_dim1] - uc[ip1 + (
			jp1 + k * uc_dim2) * uc_dim1] * opne[ii + (jj + kk * 
			opne_dim2) * opne_dim1] + oc[ip1 + (jp1 + kp1 * 
			oc_dim2) * oc_dim1] * upne[ii + (jj + kk * upne_dim2) 
			* upne_dim1]);
		tmp18_xoc__ = upe[ii + (jj + kk * upe_dim2) * upe_dim1] * (
			-une[i__ + (jm1 + k * une_dim2) * une_dim1] * ops[ii 
			+ (jj + kk * ops_dim2) * ops_dim1] - one[i__ + (jm1 + 
			kp1 * one_dim2) * one_dim1] * ups[ii + (jj + kk * 
			ups_dim2) * ups_dim1] - ue[i__ + (j + k * ue_dim2) * 
			ue_dim1] * opc[ii + (jj + kk * opc_dim2) * opc_dim1] 
			- oe[i__ + (j + kp1 * oe_dim2) * oe_dim1] * upc[ii + (
			jj + kk * upc_dim2) * upc_dim1] - use[i__ + (jp1 + k *
			 use_dim2) * use_dim1] * opn[ii + (jj + kk * opn_dim2)
			 * opn_dim1] - onw[ip1 + (j + kp1 * onw_dim2) * 
			onw_dim1] * upn[ii + (jj + kk * upn_dim2) * upn_dim1] 
			- un[ip1 + (jm1 + k * un_dim2) * un_dim1] * opse[ii + 
			(jj + kk * opse_dim2) * opse_dim1] - on[ip1 + (jm1 + 
			kp1 * on_dim2) * on_dim1] * upse[ii + (jj + kk * 
			upse_dim2) * upse_dim1] - uc[ip1 + (j + k * uc_dim2) *
			 uc_dim1] * ope[ii + (jj + kk * ope_dim2) * ope_dim1] 
			+ oc[ip1 + (j + kp1 * oc_dim2) * oc_dim1] * upe[ii + (
			jj + kk * upe_dim2) * upe_dim1] - us[ip1 + (jp1 + k * 
			us_dim2) * us_dim1] * opne[ii + (jj + kk * opne_dim2) 
			* opne_dim1] - on[ip1 + (j + kp1 * on_dim2) * on_dim1]
			 * upne[ii + (jj + kk * upne_dim2) * upne_dim1]);
		tmp19_xoc__ = dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] * (
			-one[i__ + (j + km1 * one_dim2) * one_dim1] * dpc[ii 
			+ (jj + kk * dpc_dim2) * dpc_dim1] - usw[ip1 + (jp1 + 
			km1 * usw_dim2) * usw_dim1] * opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] - oe[i__ + (jp1 + km1 * oe_dim2)
			 * oe_dim1] * dpn[ii + (jj + kk * dpn_dim2) * 
			dpn_dim1] - uw[ip1 + (jp1 + km1 * uw_dim2) * uw_dim1] 
			* opn[ii + (jj + kk * opn_dim2) * opn_dim1] - on[ip1 
			+ (j + km1 * on_dim2) * on_dim1] * dpe[ii + (jj + kk *
			 dpe_dim2) * dpe_dim1] - us[ip1 + (jp1 + km1 * 
			us_dim2) * us_dim1] * ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1] + oc[ip1 + (jp1 + km1 * oc_dim2) * oc_dim1] 
			* dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] - uc[
			ip1 + (jp1 + km1 * uc_dim2) * uc_dim1] * opne[ii + (
			jj + kk * opne_dim2) * opne_dim1]);
		tmp20_xoc__ = opne[ii + (jj + kk * opne_dim2) * opne_dim1] * (
			-une[i__ + (j + km1 * une_dim2) * une_dim1] * dpc[ii 
			+ (jj + kk * dpc_dim2) * dpc_dim1] - one[i__ + (j + k 
			* one_dim2) * one_dim1] * opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] - usw[ip1 + (jp1 + k * usw_dim2)
			 * usw_dim1] * upc[ii + (jj + kk * upc_dim2) * 
			upc_dim1] - ue[i__ + (jp1 + km1 * ue_dim2) * ue_dim1] 
			* dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] - oe[i__ 
			+ (jp1 + k * oe_dim2) * oe_dim1] * opn[ii + (jj + kk *
			 opn_dim2) * opn_dim1] - uw[ip1 + (jp1 + k * uw_dim2) 
			* uw_dim1] * upn[ii + (jj + kk * upn_dim2) * upn_dim1]
			 - un[ip1 + (j + km1 * un_dim2) * un_dim1] * dpe[ii + 
			(jj + kk * dpe_dim2) * dpe_dim1] - on[ip1 + (j + k * 
			on_dim2) * on_dim1] * ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1] - us[ip1 + (jp1 + k * us_dim2) * us_dim1] * 
			upe[ii + (jj + kk * upe_dim2) * upe_dim1] - uc[ip1 + (
			jp1 + km1 * uc_dim2) * uc_dim1] * dpne[ii + (jj + kk *
			 dpne_dim2) * dpne_dim1] + oc[ip1 + (jp1 + k * 
			oc_dim2) * oc_dim1] * opne[ii + (jj + kk * opne_dim2) 
			* opne_dim1] - uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1]
			 * upne[ii + (jj + kk * upne_dim2) * upne_dim1]);
		tmp21_xoc__ = opse[ii + (jj + kk * opse_dim2) * opse_dim1] * (
			-ue[i__ + (jm1 + km1 * ue_dim2) * ue_dim1] * dps[ii + 
			(jj + kk * dps_dim2) * dps_dim1] - oe[i__ + (jm1 + k *
			 oe_dim2) * oe_dim1] * ops[ii + (jj + kk * ops_dim2) *
			 ops_dim1] - uw[ip1 + (jm1 + k * uw_dim2) * uw_dim1] *
			 ups[ii + (jj + kk * ups_dim2) * ups_dim1] - use[i__ 
			+ (j + km1 * use_dim2) * use_dim1] * dpc[ii + (jj + 
			kk * dpc_dim2) * dpc_dim1] - onw[ip1 + (jm1 + k * 
			onw_dim2) * onw_dim1] * opc[ii + (jj + kk * opc_dim2) 
			* opc_dim1] - unw[ip1 + (jm1 + k * unw_dim2) * 
			unw_dim1] * upc[ii + (jj + kk * upc_dim2) * upc_dim1] 
			- uc[ip1 + (jm1 + km1 * uc_dim2) * uc_dim1] * dpse[ii 
			+ (jj + kk * dpse_dim2) * dpse_dim1] + oc[ip1 + (jm1 
			+ k * oc_dim2) * oc_dim1] * opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] - uc[ip1 + (jm1 + k * uc_dim2)
			 * uc_dim1] * upse[ii + (jj + kk * upse_dim2) * 
			upse_dim1] - us[ip1 + (j + km1 * us_dim2) * us_dim1] *
			 dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] - on[ip1 + 
			(jm1 + k * on_dim2) * on_dim1] * ope[ii + (jj + kk * 
			ope_dim2) * ope_dim1] - un[ip1 + (jm1 + k * un_dim2) *
			 un_dim1] * upe[ii + (jj + kk * upe_dim2) * upe_dim1])
			;
		tmp22_xoc__ = dpse[ii + (jj + kk * dpse_dim2) * dpse_dim1] * (
			-oe[i__ + (jm1 + km1 * oe_dim2) * oe_dim1] * dps[ii + 
			(jj + kk * dps_dim2) * dps_dim1] - uw[ip1 + (jm1 + 
			km1 * uw_dim2) * uw_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] - onw[ip1 + (jm1 + km1 * 
			onw_dim2) * onw_dim1] * dpc[ii + (jj + kk * dpc_dim2) 
			* dpc_dim1] - unw[ip1 + (jm1 + km1 * unw_dim2) * 
			unw_dim1] * opc[ii + (jj + kk * opc_dim2) * opc_dim1] 
			+ oc[ip1 + (jm1 + km1 * oc_dim2) * oc_dim1] * dpse[ii 
			+ (jj + kk * dpse_dim2) * dpse_dim1] - uc[ip1 + (jm1 
			+ km1 * uc_dim2) * uc_dim1] * opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] - on[ip1 + (jm1 + km1 * 
			on_dim2) * on_dim1] * dpe[ii + (jj + kk * dpe_dim2) * 
			dpe_dim1] - un[ip1 + (jm1 + km1 * un_dim2) * un_dim1] 
			* ope[ii + (jj + kk * ope_dim2) * ope_dim1]);
		tmp23_xoc__ = upse[ii + (jj + kk * upse_dim2) * upse_dim1] * (
			-ue[i__ + (jm1 + k * ue_dim2) * ue_dim1] * ops[ii + (
			jj + kk * ops_dim2) * ops_dim1] - oe[i__ + (jm1 + kp1 
			* oe_dim2) * oe_dim1] * ups[ii + (jj + kk * ups_dim2) 
			* ups_dim1] - use[i__ + (j + k * use_dim2) * use_dim1]
			 * opc[ii + (jj + kk * opc_dim2) * opc_dim1] - onw[
			ip1 + (jm1 + kp1 * onw_dim2) * onw_dim1] * upc[ii + (
			jj + kk * upc_dim2) * upc_dim1] - uc[ip1 + (jm1 + k * 
			uc_dim2) * uc_dim1] * opse[ii + (jj + kk * opse_dim2) 
			* opse_dim1] + oc[ip1 + (jm1 + kp1 * oc_dim2) * 
			oc_dim1] * upse[ii + (jj + kk * upse_dim2) * 
			upse_dim1] - us[ip1 + (j + k * us_dim2) * us_dim1] * 
			ope[ii + (jj + kk * ope_dim2) * ope_dim1] - on[ip1 + (
			jm1 + kp1 * on_dim2) * on_dim1] * upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1]);
		tmp24_xoc__ = ope[ii + (jj + kk * ope_dim2) * ope_dim1] * (
			-une[i__ + (jm1 + km1 * une_dim2) * une_dim1] * dps[
			ii + (jj + kk * dps_dim2) * dps_dim1] - one[i__ + (
			jm1 + k * one_dim2) * one_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] - usw[ip1 + (j + k * usw_dim2) *
			 usw_dim1] * ups[ii + (jj + kk * ups_dim2) * ups_dim1]
			 - ue[i__ + (j + km1 * ue_dim2) * ue_dim1] * dpc[ii + 
			(jj + kk * dpc_dim2) * dpc_dim1] - oe[i__ + (j + k * 
			oe_dim2) * oe_dim1] * opc[ii + (jj + kk * opc_dim2) * 
			opc_dim1] - uw[ip1 + (j + k * uw_dim2) * uw_dim1] * 
			upc[ii + (jj + kk * upc_dim2) * upc_dim1] - use[i__ + 
			(jp1 + km1 * use_dim2) * use_dim1] * dpn[ii + (jj + 
			kk * dpn_dim2) * dpn_dim1] - onw[ip1 + (j + k * 
			onw_dim2) * onw_dim1] * opn[ii + (jj + kk * opn_dim2) 
			* opn_dim1] - unw[ip1 + (j + k * unw_dim2) * unw_dim1]
			 * upn[ii + (jj + kk * upn_dim2) * upn_dim1] - un[ip1 
			+ (jm1 + km1 * un_dim2) * un_dim1] * dpse[ii + (jj + 
			kk * dpse_dim2) * dpse_dim1] - on[ip1 + (jm1 + k * 
			on_dim2) * on_dim1] * opse[ii + (jj + kk * opse_dim2) 
			* opse_dim1] - us[ip1 + (j + k * us_dim2) * us_dim1] *
			 upse[ii + (jj + kk * upse_dim2) * upse_dim1] - uc[
			ip1 + (j + km1 * uc_dim2) * uc_dim1] * dpe[ii + (jj + 
			kk * dpe_dim2) * dpe_dim1] + oc[ip1 + (j + k * 
			oc_dim2) * oc_dim1] * ope[ii + (jj + kk * ope_dim2) * 
			ope_dim1] - uc[ip1 + (j + k * uc_dim2) * uc_dim1] * 
			upe[ii + (jj + kk * upe_dim2) * upe_dim1] - us[ip1 + (
			jp1 + km1 * us_dim2) * us_dim1] * dpne[ii + (jj + kk *
			 dpne_dim2) * dpne_dim1] - on[ip1 + (j + k * on_dim2) 
			* on_dim1] * opne[ii + (jj + kk * opne_dim2) * 
			opne_dim1] - un[ip1 + (j + k * un_dim2) * un_dim1] * 
			upne[ii + (jj + kk * upne_dim2) * upne_dim1]);
		tmp25_xoc__ = dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] * (
			-one[i__ + (jm1 + km1 * one_dim2) * one_dim1] * dps[
			ii + (jj + kk * dps_dim2) * dps_dim1] - usw[ip1 + (j 
			+ km1 * usw_dim2) * usw_dim1] * ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] - oe[i__ + (j + km1 * oe_dim2) *
			 oe_dim1] * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] 
			- uw[ip1 + (j + km1 * uw_dim2) * uw_dim1] * opc[ii + (
			jj + kk * opc_dim2) * opc_dim1] - onw[ip1 + (j + km1 *
			 onw_dim2) * onw_dim1] * dpn[ii + (jj + kk * dpn_dim2)
			 * dpn_dim1] - unw[ip1 + (j + km1 * unw_dim2) * 
			unw_dim1] * opn[ii + (jj + kk * opn_dim2) * opn_dim1] 
			- on[ip1 + (jm1 + km1 * on_dim2) * on_dim1] * dpse[ii 
			+ (jj + kk * dpse_dim2) * dpse_dim1] - us[ip1 + (j + 
			km1 * us_dim2) * us_dim1] * opse[ii + (jj + kk * 
			opse_dim2) * opse_dim1] + oc[ip1 + (j + km1 * oc_dim2)
			 * oc_dim1] * dpe[ii + (jj + kk * dpe_dim2) * 
			dpe_dim1] - uc[ip1 + (j + km1 * uc_dim2) * uc_dim1] * 
			ope[ii + (jj + kk * ope_dim2) * ope_dim1] - on[ip1 + (
			j + km1 * on_dim2) * on_dim1] * dpne[ii + (jj + kk * 
			dpne_dim2) * dpne_dim1] - un[ip1 + (j + km1 * un_dim2)
			 * un_dim1] * opne[ii + (jj + kk * opne_dim2) * 
			opne_dim1]);
		tmp26_xoc__ = upn[ii + (jj + kk * upn_dim2) * upn_dim1] * (
			-une[im1 + (j + k * une_dim2) * une_dim1] * opw[ii + (
			jj + kk * opw_dim2) * opw_dim1] - one[im1 + (j + kp1 *
			 one_dim2) * one_dim1] * upw[ii + (jj + kk * upw_dim2)
			 * upw_dim1] - ue[im1 + (jp1 + k * ue_dim2) * ue_dim1]
			 * opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] - oe[
			im1 + (jp1 + kp1 * oe_dim2) * oe_dim1] * upnw[ii + (
			jj + kk * upnw_dim2) * upnw_dim1] - un[i__ + (j + k * 
			un_dim2) * un_dim1] * opc[ii + (jj + kk * opc_dim2) * 
			opc_dim1] - on[i__ + (j + kp1 * on_dim2) * on_dim1] * 
			upc[ii + (jj + kk * upc_dim2) * upc_dim1] - uc[i__ + (
			jp1 + k * uc_dim2) * uc_dim1] * opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] + oc[i__ + (jp1 + kp1 * oc_dim2)
			 * oc_dim1] * upn[ii + (jj + kk * upn_dim2) * 
			upn_dim1] - unw[ip1 + (j + k * unw_dim2) * unw_dim1] *
			 ope[ii + (jj + kk * ope_dim2) * ope_dim1] - onw[ip1 
			+ (j + kp1 * onw_dim2) * onw_dim1] * upe[ii + (jj + 
			kk * upe_dim2) * upe_dim1] - uw[ip1 + (jp1 + k * 
			uw_dim2) * uw_dim1] * opne[ii + (jj + kk * opne_dim2) 
			* opne_dim1] - oe[i__ + (jp1 + kp1 * oe_dim2) * 
			oe_dim1] * upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1]);
		tmp27_xoc__ = dpsw[ii + (jj + kk * dpsw_dim2) * dpsw_dim1] * (
			oc[im1 + (jm1 + km1 * oc_dim2) * oc_dim1] * dpsw[ii + 
			(jj + kk * dpsw_dim2) * dpsw_dim1] - uc[im1 + (jm1 + 
			km1 * uc_dim2) * uc_dim1] * opsw[ii + (jj + kk * 
			opsw_dim2) * opsw_dim1] - on[im1 + (jm1 + km1 * 
			on_dim2) * on_dim1] * dpw[ii + (jj + kk * dpw_dim2) * 
			dpw_dim1] - un[im1 + (jm1 + km1 * un_dim2) * un_dim1] 
			* opw[ii + (jj + kk * opw_dim2) * opw_dim1] - oe[im1 
			+ (jm1 + km1 * oe_dim2) * oe_dim1] * dps[ii + (jj + 
			kk * dps_dim2) * dps_dim1] - ue[im1 + (jm1 + km1 * 
			ue_dim2) * ue_dim1] * ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1] - one[im1 + (jm1 + km1 * one_dim2) * 
			one_dim1] * dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] 
			- une[im1 + (jm1 + km1 * une_dim2) * une_dim1] * opc[
			ii + (jj + kk * opc_dim2) * opc_dim1]);
		xoc[ii + (jj + kk * xoc_dim2) * xoc_dim1] = tmp1_xoc__ + 
			tmp2_xoc__ + tmp3_xoc__ + tmp4_xoc__ + tmp5_xoc__ + 
			tmp6_xoc__ + tmp7_xoc__ + tmp8_xoc__ + tmp9_xoc__ + 
			tmp10_xoc__ + tmp11_xoc__ + tmp12_xoc__ + tmp13_xoc__ 
			+ tmp14_xoc__ + tmp15_xoc__ + tmp16_xoc__ + 
			tmp17_xoc__ + tmp18_xoc__ + tmp19_xoc__ + tmp20_xoc__ 
			+ tmp21_xoc__ + tmp22_xoc__ + tmp23_xoc__ + 
			tmp24_xoc__ + tmp25_xoc__ + tmp26_xoc__ + tmp27_xoc__;
/* * ******************************************************************** */
/* * *** > oE; */
/* * ******************************************************************** */
/* * ***XoE(ii,jj,kk) = */
		tmp1_xoe__ = -dps[ii + (jj + kk * dps_dim2) * dps_dim1] * (
			-oe[i__ + (jm1 + km1 * oe_dim2) * oe_dim1] * dpsw[
			iip1 + (jj + kk * dpsw_dim2) * dpsw_dim1] - ue[i__ + (
			jm1 + km1 * ue_dim2) * ue_dim1] * opsw[iip1 + (jj + 
			kk * opsw_dim2) * opsw_dim1] - one[i__ + (jm1 + km1 * 
			one_dim2) * one_dim1] * dpw[iip1 + (jj + kk * 
			dpw_dim2) * dpw_dim1] - une[i__ + (jm1 + km1 * 
			une_dim2) * une_dim1] * opw[iip1 + (jj + kk * 
			opw_dim2) * opw_dim1]) - ops[ii + (jj + kk * ops_dim2)
			 * ops_dim1] * (-uw[ip1 + (jm1 + km1 * uw_dim2) * 
			uw_dim1] * dpsw[iip1 + (jj + kk * dpsw_dim2) * 
			dpsw_dim1] - oe[i__ + (jm1 + k * oe_dim2) * oe_dim1] *
			 opsw[iip1 + (jj + kk * opsw_dim2) * opsw_dim1] - ue[
			i__ + (jm1 + k * ue_dim2) * ue_dim1] * upsw[iip1 + (
			jj + kk * upsw_dim2) * upsw_dim1] - usw[ip1 + (j + 
			km1 * usw_dim2) * usw_dim1] * dpw[iip1 + (jj + kk * 
			dpw_dim2) * dpw_dim1] - one[i__ + (jm1 + k * one_dim2)
			 * one_dim1] * opw[iip1 + (jj + kk * opw_dim2) * 
			opw_dim1] - une[i__ + (jm1 + k * une_dim2) * une_dim1]
			 * upw[iip1 + (jj + kk * upw_dim2) * upw_dim1]) - ups[
			ii + (jj + kk * ups_dim2) * ups_dim1] * (-uw[ip1 + (
			jm1 + k * uw_dim2) * uw_dim1] * opsw[iip1 + (jj + kk *
			 opsw_dim2) * opsw_dim1] - oe[i__ + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * upsw[iip1 + (jj + kk * 
			upsw_dim2) * upsw_dim1] - usw[ip1 + (j + k * usw_dim2)
			 * usw_dim1] * opw[iip1 + (jj + kk * opw_dim2) * 
			opw_dim1] - one[i__ + (jm1 + kp1 * one_dim2) * 
			one_dim1] * upw[iip1 + (jj + kk * upw_dim2) * 
			upw_dim1]);
		tmp2_xoe__ = -dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] * (
			-onw[ip1 + (jm1 + km1 * onw_dim2) * onw_dim1] * dpsw[
			iip1 + (jj + kk * dpsw_dim2) * dpsw_dim1] - use[i__ + 
			(j + km1 * use_dim2) * use_dim1] * opsw[iip1 + (jj + 
			kk * opsw_dim2) * opsw_dim1] - oe[i__ + (j + km1 * 
			oe_dim2) * oe_dim1] * dpw[iip1 + (jj + kk * dpw_dim2) 
			* dpw_dim1] - ue[i__ + (j + km1 * ue_dim2) * ue_dim1] 
			* opw[iip1 + (jj + kk * opw_dim2) * opw_dim1] - one[
			i__ + (j + km1 * one_dim2) * one_dim1] * dpnw[iip1 + (
			jj + kk * dpnw_dim2) * dpnw_dim1] - une[i__ + (j + 
			km1 * une_dim2) * une_dim1] * opnw[iip1 + (jj + kk * 
			opnw_dim2) * opnw_dim1]) - opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] * (-unw[ip1 + (jm1 + km1 * 
			unw_dim2) * unw_dim1] * dpsw[iip1 + (jj + kk * 
			dpsw_dim2) * dpsw_dim1] - onw[ip1 + (jm1 + k * 
			onw_dim2) * onw_dim1] * opsw[iip1 + (jj + kk * 
			opsw_dim2) * opsw_dim1] - use[i__ + (j + k * use_dim2)
			 * use_dim1] * upsw[iip1 + (jj + kk * upsw_dim2) * 
			upsw_dim1] - uw[ip1 + (j + km1 * uw_dim2) * uw_dim1] *
			 dpw[iip1 + (jj + kk * dpw_dim2) * dpw_dim1] - oe[i__ 
			+ (j + k * oe_dim2) * oe_dim1] * opw[iip1 + (jj + kk *
			 opw_dim2) * opw_dim1] - ue[i__ + (j + k * ue_dim2) * 
			ue_dim1] * upw[iip1 + (jj + kk * upw_dim2) * upw_dim1]
			 - usw[ip1 + (jp1 + km1 * usw_dim2) * usw_dim1] * 
			dpnw[iip1 + (jj + kk * dpnw_dim2) * dpnw_dim1] - one[
			i__ + (j + k * one_dim2) * one_dim1] * opnw[iip1 + (
			jj + kk * opnw_dim2) * opnw_dim1] - une[i__ + (j + k *
			 une_dim2) * une_dim1] * upnw[iip1 + (jj + kk * 
			upnw_dim2) * upnw_dim1]);
		tmp3_xoe__ = -upc[ii + (jj + kk * upc_dim2) * upc_dim1] * (
			-unw[ip1 + (jm1 + k * unw_dim2) * unw_dim1] * opsw[
			iip1 + (jj + kk * opsw_dim2) * opsw_dim1] - onw[ip1 + 
			(jm1 + kp1 * onw_dim2) * onw_dim1] * upsw[iip1 + (jj 
			+ kk * upsw_dim2) * upsw_dim1] - uw[ip1 + (j + k * 
			uw_dim2) * uw_dim1] * opw[iip1 + (jj + kk * opw_dim2) 
			* opw_dim1] - oe[i__ + (j + kp1 * oe_dim2) * oe_dim1] 
			* upw[iip1 + (jj + kk * upw_dim2) * upw_dim1] - usw[
			ip1 + (jp1 + k * usw_dim2) * usw_dim1] * opnw[iip1 + (
			jj + kk * opnw_dim2) * opnw_dim1] - one[i__ + (j + 
			kp1 * one_dim2) * one_dim1] * upnw[iip1 + (jj + kk * 
			upnw_dim2) * upnw_dim1]) - dpn[ii + (jj + kk * 
			dpn_dim2) * dpn_dim1] * (-onw[ip1 + (j + km1 * 
			onw_dim2) * onw_dim1] * dpw[iip1 + (jj + kk * 
			dpw_dim2) * dpw_dim1] - use[i__ + (jp1 + km1 * 
			use_dim2) * use_dim1] * opw[iip1 + (jj + kk * 
			opw_dim2) * opw_dim1] - oe[i__ + (jp1 + km1 * oe_dim2)
			 * oe_dim1] * dpnw[iip1 + (jj + kk * dpnw_dim2) * 
			dpnw_dim1] - ue[i__ + (jp1 + km1 * ue_dim2) * ue_dim1]
			 * opnw[iip1 + (jj + kk * opnw_dim2) * opnw_dim1]) - 
			opn[ii + (jj + kk * opn_dim2) * opn_dim1] * (-unw[ip1 
			+ (j + km1 * unw_dim2) * unw_dim1] * dpw[iip1 + (jj + 
			kk * dpw_dim2) * dpw_dim1] - onw[ip1 + (j + k * 
			onw_dim2) * onw_dim1] * opw[iip1 + (jj + kk * 
			opw_dim2) * opw_dim1] - use[i__ + (jp1 + k * use_dim2)
			 * use_dim1] * upw[iip1 + (jj + kk * upw_dim2) * 
			upw_dim1] - uw[ip1 + (jp1 + km1 * uw_dim2) * uw_dim1] 
			* dpnw[iip1 + (jj + kk * dpnw_dim2) * dpnw_dim1] - oe[
			i__ + (jp1 + k * oe_dim2) * oe_dim1] * opnw[iip1 + (
			jj + kk * opnw_dim2) * opnw_dim1] - ue[i__ + (jp1 + k 
			* ue_dim2) * ue_dim1] * upnw[iip1 + (jj + kk * 
			upnw_dim2) * upnw_dim1]);
		tmp4_xoe__ = -upn[ii + (jj + kk * upn_dim2) * upn_dim1] * (
			-unw[ip1 + (j + k * unw_dim2) * unw_dim1] * opw[iip1 
			+ (jj + kk * opw_dim2) * opw_dim1] - onw[ip1 + (j + 
			kp1 * onw_dim2) * onw_dim1] * upw[iip1 + (jj + kk * 
			upw_dim2) * upw_dim1] - uw[ip1 + (jp1 + k * uw_dim2) *
			 uw_dim1] * opnw[iip1 + (jj + kk * opnw_dim2) * 
			opnw_dim1] - oe[i__ + (jp1 + kp1 * oe_dim2) * oe_dim1]
			 * upnw[iip1 + (jj + kk * upnw_dim2) * upnw_dim1]) - 
			dpse[ii + (jj + kk * dpse_dim2) * dpse_dim1] * (oc[
			ip1 + (jm1 + km1 * oc_dim2) * oc_dim1] * dpsw[iip1 + (
			jj + kk * dpsw_dim2) * dpsw_dim1] - uc[ip1 + (jm1 + 
			km1 * uc_dim2) * uc_dim1] * opsw[iip1 + (jj + kk * 
			opsw_dim2) * opsw_dim1] - on[ip1 + (jm1 + km1 * 
			on_dim2) * on_dim1] * dpw[iip1 + (jj + kk * dpw_dim2) 
			* dpw_dim1] - un[ip1 + (jm1 + km1 * un_dim2) * 
			un_dim1] * opw[iip1 + (jj + kk * opw_dim2) * opw_dim1]
			 - oe[ip1 + (jm1 + km1 * oe_dim2) * oe_dim1] * dps[
			iip1 + (jj + kk * dps_dim2) * dps_dim1] - ue[ip1 + (
			jm1 + km1 * ue_dim2) * ue_dim1] * ops[iip1 + (jj + kk 
			* ops_dim2) * ops_dim1] - one[ip1 + (jm1 + km1 * 
			one_dim2) * one_dim1] * dpc[iip1 + (jj + kk * 
			dpc_dim2) * dpc_dim1] - une[ip1 + (jm1 + km1 * 
			une_dim2) * une_dim1] * opc[iip1 + (jj + kk * 
			opc_dim2) * opc_dim1]);
		tmp5_xoe__ = -opse[ii + (jj + kk * opse_dim2) * opse_dim1] * (
			-uc[ip1 + (jm1 + km1 * uc_dim2) * uc_dim1] * dpsw[
			iip1 + (jj + kk * dpsw_dim2) * dpsw_dim1] + oc[ip1 + (
			jm1 + k * oc_dim2) * oc_dim1] * opsw[iip1 + (jj + kk *
			 opsw_dim2) * opsw_dim1] - uc[ip1 + (jm1 + k * 
			uc_dim2) * uc_dim1] * upsw[iip1 + (jj + kk * 
			upsw_dim2) * upsw_dim1] - us[ip1 + (j + km1 * us_dim2)
			 * us_dim1] * dpw[iip1 + (jj + kk * dpw_dim2) * 
			dpw_dim1] - on[ip1 + (jm1 + k * on_dim2) * on_dim1] * 
			opw[iip1 + (jj + kk * opw_dim2) * opw_dim1] - un[ip1 
			+ (jm1 + k * un_dim2) * un_dim1] * upw[iip1 + (jj + 
			kk * upw_dim2) * upw_dim1] - uw[ip2 + (jm1 + km1 * 
			uw_dim2) * uw_dim1] * dps[iip1 + (jj + kk * dps_dim2) 
			* dps_dim1] - oe[ip1 + (jm1 + k * oe_dim2) * oe_dim1] 
			* ops[iip1 + (jj + kk * ops_dim2) * ops_dim1] - ue[
			ip1 + (jm1 + k * ue_dim2) * ue_dim1] * ups[iip1 + (jj 
			+ kk * ups_dim2) * ups_dim1] - usw[ip2 + (j + km1 * 
			usw_dim2) * usw_dim1] * dpc[iip1 + (jj + kk * 
			dpc_dim2) * dpc_dim1] - one[ip1 + (jm1 + k * one_dim2)
			 * one_dim1] * opc[iip1 + (jj + kk * opc_dim2) * 
			opc_dim1] - une[ip1 + (jm1 + k * une_dim2) * une_dim1]
			 * upc[iip1 + (jj + kk * upc_dim2) * upc_dim1]);
		tmp6_xoe__ = -upse[ii + (jj + kk * upse_dim2) * upse_dim1] * (
			-uc[ip1 + (jm1 + k * uc_dim2) * uc_dim1] * opsw[iip1 
			+ (jj + kk * opsw_dim2) * opsw_dim1] + oc[ip1 + (jm1 
			+ kp1 * oc_dim2) * oc_dim1] * upsw[iip1 + (jj + kk * 
			upsw_dim2) * upsw_dim1] - us[ip1 + (j + k * us_dim2) *
			 us_dim1] * opw[iip1 + (jj + kk * opw_dim2) * 
			opw_dim1] - on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1] 
			* upw[iip1 + (jj + kk * upw_dim2) * upw_dim1] - uw[
			ip2 + (jm1 + k * uw_dim2) * uw_dim1] * ops[iip1 + (jj 
			+ kk * ops_dim2) * ops_dim1] - oe[ip1 + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * ups[iip1 + (jj + kk * ups_dim2) 
			* ups_dim1] - usw[ip2 + (j + k * usw_dim2) * usw_dim1]
			 * opc[iip1 + (jj + kk * opc_dim2) * opc_dim1] - one[
			ip1 + (jm1 + kp1 * one_dim2) * one_dim1] * upc[iip1 + 
			(jj + kk * upc_dim2) * upc_dim1]);
		tmp7_xoe__ = -dpe[ii + (jj + kk * dpe_dim2) * dpe_dim1] * (
			-on[ip1 + (jm1 + km1 * on_dim2) * on_dim1] * dpsw[
			iip1 + (jj + kk * dpsw_dim2) * dpsw_dim1] - us[ip1 + (
			j + km1 * us_dim2) * us_dim1] * opsw[iip1 + (jj + kk *
			 opsw_dim2) * opsw_dim1] + oc[ip1 + (j + km1 * 
			oc_dim2) * oc_dim1] * dpw[iip1 + (jj + kk * dpw_dim2) 
			* dpw_dim1] - uc[ip1 + (j + km1 * uc_dim2) * uc_dim1] 
			* opw[iip1 + (jj + kk * opw_dim2) * opw_dim1] - on[
			ip1 + (j + km1 * on_dim2) * on_dim1] * dpnw[iip1 + (
			jj + kk * dpnw_dim2) * dpnw_dim1] - un[ip1 + (j + km1 
			* un_dim2) * un_dim1] * opnw[iip1 + (jj + kk * 
			opnw_dim2) * opnw_dim1] - onw[ip2 + (jm1 + km1 * 
			onw_dim2) * onw_dim1] * dps[iip1 + (jj + kk * 
			dps_dim2) * dps_dim1] - use[ip1 + (j + km1 * use_dim2)
			 * use_dim1] * ops[iip1 + (jj + kk * ops_dim2) * 
			ops_dim1] - oe[ip1 + (j + km1 * oe_dim2) * oe_dim1] * 
			dpc[iip1 + (jj + kk * dpc_dim2) * dpc_dim1] - ue[ip1 
			+ (j + km1 * ue_dim2) * ue_dim1] * opc[iip1 + (jj + 
			kk * opc_dim2) * opc_dim1] - one[ip1 + (j + km1 * 
			one_dim2) * one_dim1] * dpn[iip1 + (jj + kk * 
			dpn_dim2) * dpn_dim1] - une[ip1 + (j + km1 * une_dim2)
			 * une_dim1] * opn[iip1 + (jj + kk * opn_dim2) * 
			opn_dim1]);
		tmp8_xoe__ = -ope[ii + (jj + kk * ope_dim2) * ope_dim1] * (
			-un[ip1 + (jm1 + km1 * un_dim2) * un_dim1] * dpsw[
			iip1 + (jj + kk * dpsw_dim2) * dpsw_dim1] - on[ip1 + (
			jm1 + k * on_dim2) * on_dim1] * opsw[iip1 + (jj + kk *
			 opsw_dim2) * opsw_dim1] - us[ip1 + (j + k * us_dim2) 
			* us_dim1] * upsw[iip1 + (jj + kk * upsw_dim2) * 
			upsw_dim1] - uc[ip1 + (j + km1 * uc_dim2) * uc_dim1] *
			 dpw[iip1 + (jj + kk * dpw_dim2) * dpw_dim1] + oc[ip1 
			+ (j + k * oc_dim2) * oc_dim1] * opw[iip1 + (jj + kk *
			 opw_dim2) * opw_dim1] - uc[ip1 + (j + k * uc_dim2) * 
			uc_dim1] * upw[iip1 + (jj + kk * upw_dim2) * upw_dim1]
			 - us[ip1 + (jp1 + km1 * us_dim2) * us_dim1] * dpnw[
			iip1 + (jj + kk * dpnw_dim2) * dpnw_dim1] - on[ip1 + (
			j + k * on_dim2) * on_dim1] * opnw[iip1 + (jj + kk * 
			opnw_dim2) * opnw_dim1] - un[ip1 + (j + k * un_dim2) *
			 un_dim1] * upnw[iip1 + (jj + kk * upnw_dim2) * 
			upnw_dim1] - unw[ip2 + (jm1 + km1 * unw_dim2) * 
			unw_dim1] * dps[iip1 + (jj + kk * dps_dim2) * 
			dps_dim1] - onw[ip2 + (jm1 + k * onw_dim2) * onw_dim1]
			 * ops[iip1 + (jj + kk * ops_dim2) * ops_dim1] - use[
			ip1 + (j + k * use_dim2) * use_dim1] * ups[iip1 + (jj 
			+ kk * ups_dim2) * ups_dim1] - uw[ip2 + (j + km1 * 
			uw_dim2) * uw_dim1] * dpc[iip1 + (jj + kk * dpc_dim2) 
			* dpc_dim1] - oe[ip1 + (j + k * oe_dim2) * oe_dim1] * 
			opc[iip1 + (jj + kk * opc_dim2) * opc_dim1] - ue[ip1 
			+ (j + k * ue_dim2) * ue_dim1] * upc[iip1 + (jj + kk *
			 upc_dim2) * upc_dim1] - usw[ip2 + (jp1 + km1 * 
			usw_dim2) * usw_dim1] * dpn[iip1 + (jj + kk * 
			dpn_dim2) * dpn_dim1] - one[ip1 + (j + k * one_dim2) *
			 one_dim1] * opn[iip1 + (jj + kk * opn_dim2) * 
			opn_dim1] - une[ip1 + (j + k * une_dim2) * une_dim1] *
			 upn[iip1 + (jj + kk * upn_dim2) * upn_dim1]);
		tmp9_xoe__ = -upe[ii + (jj + kk * upe_dim2) * upe_dim1] * (
			-un[ip1 + (jm1 + k * un_dim2) * un_dim1] * opsw[iip1 
			+ (jj + kk * opsw_dim2) * opsw_dim1] - on[ip1 + (jm1 
			+ kp1 * on_dim2) * on_dim1] * upsw[iip1 + (jj + kk * 
			upsw_dim2) * upsw_dim1] - uc[ip1 + (j + k * uc_dim2) *
			 uc_dim1] * opw[iip1 + (jj + kk * opw_dim2) * 
			opw_dim1] + oc[ip1 + (j + kp1 * oc_dim2) * oc_dim1] * 
			upw[iip1 + (jj + kk * upw_dim2) * upw_dim1] - us[ip1 
			+ (jp1 + k * us_dim2) * us_dim1] * opnw[iip1 + (jj + 
			kk * opnw_dim2) * opnw_dim1] - on[ip1 + (j + kp1 * 
			on_dim2) * on_dim1] * upnw[iip1 + (jj + kk * 
			upnw_dim2) * upnw_dim1] - unw[ip2 + (jm1 + k * 
			unw_dim2) * unw_dim1] * ops[iip1 + (jj + kk * 
			ops_dim2) * ops_dim1] - onw[ip2 + (jm1 + kp1 * 
			onw_dim2) * onw_dim1] * ups[iip1 + (jj + kk * 
			ups_dim2) * ups_dim1] - uw[ip2 + (j + k * uw_dim2) * 
			uw_dim1] * opc[iip1 + (jj + kk * opc_dim2) * opc_dim1]
			 - oe[ip1 + (j + kp1 * oe_dim2) * oe_dim1] * upc[iip1 
			+ (jj + kk * upc_dim2) * upc_dim1] - usw[ip2 + (jp1 + 
			k * usw_dim2) * usw_dim1] * opn[iip1 + (jj + kk * 
			opn_dim2) * opn_dim1] - one[ip1 + (j + kp1 * one_dim2)
			 * one_dim1] * upn[iip1 + (jj + kk * upn_dim2) * 
			upn_dim1]);
		tmp10_xoe__ = -dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] * 
			(-on[ip1 + (j + km1 * on_dim2) * on_dim1] * dpw[iip1 
			+ (jj + kk * dpw_dim2) * dpw_dim1] - us[ip1 + (jp1 + 
			km1 * us_dim2) * us_dim1] * opw[iip1 + (jj + kk * 
			opw_dim2) * opw_dim1] + oc[ip1 + (jp1 + km1 * oc_dim2)
			 * oc_dim1] * dpnw[iip1 + (jj + kk * dpnw_dim2) * 
			dpnw_dim1] - uc[ip1 + (jp1 + km1 * uc_dim2) * uc_dim1]
			 * opnw[iip1 + (jj + kk * opnw_dim2) * opnw_dim1] - 
			onw[ip2 + (j + km1 * onw_dim2) * onw_dim1] * dpc[iip1 
			+ (jj + kk * dpc_dim2) * dpc_dim1] - use[ip1 + (jp1 + 
			km1 * use_dim2) * use_dim1] * opc[iip1 + (jj + kk * 
			opc_dim2) * opc_dim1] - oe[ip1 + (jp1 + km1 * oe_dim2)
			 * oe_dim1] * dpn[iip1 + (jj + kk * dpn_dim2) * 
			dpn_dim1] - ue[ip1 + (jp1 + km1 * ue_dim2) * ue_dim1] 
			* opn[iip1 + (jj + kk * opn_dim2) * opn_dim1]);
		tmp11_xoe__ = -opne[ii + (jj + kk * opne_dim2) * opne_dim1] * 
			(-un[ip1 + (j + km1 * un_dim2) * un_dim1] * dpw[iip1 
			+ (jj + kk * dpw_dim2) * dpw_dim1] - on[ip1 + (j + k *
			 on_dim2) * on_dim1] * opw[iip1 + (jj + kk * opw_dim2)
			 * opw_dim1] - us[ip1 + (jp1 + k * us_dim2) * us_dim1]
			 * upw[iip1 + (jj + kk * upw_dim2) * upw_dim1] - uc[
			ip1 + (jp1 + km1 * uc_dim2) * uc_dim1] * dpnw[iip1 + (
			jj + kk * dpnw_dim2) * dpnw_dim1] + oc[ip1 + (jp1 + k 
			* oc_dim2) * oc_dim1] * opnw[iip1 + (jj + kk * 
			opnw_dim2) * opnw_dim1] - uc[ip1 + (jp1 + k * uc_dim2)
			 * uc_dim1] * upnw[iip1 + (jj + kk * upnw_dim2) * 
			upnw_dim1] - unw[ip2 + (j + km1 * unw_dim2) * 
			unw_dim1] * dpc[iip1 + (jj + kk * dpc_dim2) * 
			dpc_dim1] - onw[ip2 + (j + k * onw_dim2) * onw_dim1] *
			 opc[iip1 + (jj + kk * opc_dim2) * opc_dim1] - use[
			ip1 + (jp1 + k * use_dim2) * use_dim1] * upc[iip1 + (
			jj + kk * upc_dim2) * upc_dim1] - uw[ip2 + (jp1 + km1 
			* uw_dim2) * uw_dim1] * dpn[iip1 + (jj + kk * 
			dpn_dim2) * dpn_dim1] - oe[ip1 + (jp1 + k * oe_dim2) *
			 oe_dim1] * opn[iip1 + (jj + kk * opn_dim2) * 
			opn_dim1] - ue[ip1 + (jp1 + k * ue_dim2) * ue_dim1] * 
			upn[iip1 + (jj + kk * upn_dim2) * upn_dim1]);
		tmp12_xoe__ = -upne[ii + (jj + kk * upne_dim2) * upne_dim1] * 
			(-un[ip1 + (j + k * un_dim2) * un_dim1] * opw[iip1 + (
			jj + kk * opw_dim2) * opw_dim1] - on[ip1 + (j + kp1 * 
			on_dim2) * on_dim1] * upw[iip1 + (jj + kk * upw_dim2) 
			* upw_dim1] - uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1] 
			* opnw[iip1 + (jj + kk * opnw_dim2) * opnw_dim1] + oc[
			ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1] * upnw[iip1 + (
			jj + kk * upnw_dim2) * upnw_dim1] - unw[ip2 + (j + k *
			 unw_dim2) * unw_dim1] * opc[iip1 + (jj + kk * 
			opc_dim2) * opc_dim1] - onw[ip2 + (j + kp1 * onw_dim2)
			 * onw_dim1] * upc[iip1 + (jj + kk * upc_dim2) * 
			upc_dim1] - uw[ip2 + (jp1 + k * uw_dim2) * uw_dim1] * 
			opn[iip1 + (jj + kk * opn_dim2) * opn_dim1] - oe[ip1 
			+ (jp1 + kp1 * oe_dim2) * oe_dim1] * upn[iip1 + (jj + 
			kk * upn_dim2) * upn_dim1]);
		xoe[ii + (jj + kk * xoe_dim2) * xoe_dim1] = tmp1_xoe__ + 
			tmp2_xoe__ + tmp3_xoe__ + tmp4_xoe__ + tmp5_xoe__ + 
			tmp6_xoe__ + tmp7_xoe__ + tmp8_xoe__ + tmp9_xoe__ + 
			tmp10_xoe__ + tmp11_xoe__ + tmp12_xoe__;
/* * ******************************************************************** */
/* * *** > oN; */
/* * ******************************************************************** */
/* * ***XoN(ii,jj,kk) = */
		tmp1_xon__ = -dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] * (
			-on[im1 + (j + km1 * on_dim2) * on_dim1] * dpsw[ii + (
			jjp1 + kk * dpsw_dim2) * dpsw_dim1] - un[im1 + (j + 
			km1 * un_dim2) * un_dim1] * opsw[ii + (jjp1 + kk * 
			opsw_dim2) * opsw_dim1] - one[im1 + (j + km1 * 
			one_dim2) * one_dim1] * dps[ii + (jjp1 + kk * 
			dps_dim2) * dps_dim1] - une[im1 + (j + km1 * une_dim2)
			 * une_dim1] * ops[ii + (jjp1 + kk * ops_dim2) * 
			ops_dim1]) - opw[ii + (jj + kk * opw_dim2) * opw_dim1]
			 * (-us[im1 + (jp1 + km1 * us_dim2) * us_dim1] * dpsw[
			ii + (jjp1 + kk * dpsw_dim2) * dpsw_dim1] - on[im1 + (
			j + k * on_dim2) * on_dim1] * opsw[ii + (jjp1 + kk * 
			opsw_dim2) * opsw_dim1] - un[im1 + (j + k * un_dim2) *
			 un_dim1] * upsw[ii + (jjp1 + kk * upsw_dim2) * 
			upsw_dim1] - usw[i__ + (jp1 + km1 * usw_dim2) * 
			usw_dim1] * dps[ii + (jjp1 + kk * dps_dim2) * 
			dps_dim1] - one[im1 + (j + k * one_dim2) * one_dim1] *
			 ops[ii + (jjp1 + kk * ops_dim2) * ops_dim1] - une[
			im1 + (j + k * une_dim2) * une_dim1] * ups[ii + (jjp1 
			+ kk * ups_dim2) * ups_dim1]) - upw[ii + (jj + kk * 
			upw_dim2) * upw_dim1] * (-us[im1 + (jp1 + k * us_dim2)
			 * us_dim1] * opsw[ii + (jjp1 + kk * opsw_dim2) * 
			opsw_dim1] - on[im1 + (j + kp1 * on_dim2) * on_dim1] *
			 upsw[ii + (jjp1 + kk * upsw_dim2) * upsw_dim1] - usw[
			i__ + (jp1 + k * usw_dim2) * usw_dim1] * ops[ii + (
			jjp1 + kk * ops_dim2) * ops_dim1] - one[im1 + (j + 
			kp1 * one_dim2) * one_dim1] * ups[ii + (jjp1 + kk * 
			ups_dim2) * ups_dim1]);
		tmp2_xon__ = -dpnw[ii + (jj + kk * dpnw_dim2) * dpnw_dim1] * (
			oc[im1 + (jp1 + km1 * oc_dim2) * oc_dim1] * dpsw[ii + 
			(jjp1 + kk * dpsw_dim2) * dpsw_dim1] - uc[im1 + (jp1 
			+ km1 * uc_dim2) * uc_dim1] * opsw[ii + (jjp1 + kk * 
			opsw_dim2) * opsw_dim1] - on[im1 + (jp1 + km1 * 
			on_dim2) * on_dim1] * dpw[ii + (jjp1 + kk * dpw_dim2) 
			* dpw_dim1] - un[im1 + (jp1 + km1 * un_dim2) * 
			un_dim1] * opw[ii + (jjp1 + kk * opw_dim2) * opw_dim1]
			 - oe[im1 + (jp1 + km1 * oe_dim2) * oe_dim1] * dps[ii 
			+ (jjp1 + kk * dps_dim2) * dps_dim1] - ue[im1 + (jp1 
			+ km1 * ue_dim2) * ue_dim1] * ops[ii + (jjp1 + kk * 
			ops_dim2) * ops_dim1] - one[im1 + (jp1 + km1 * 
			one_dim2) * one_dim1] * dpc[ii + (jjp1 + kk * 
			dpc_dim2) * dpc_dim1] - une[im1 + (jp1 + km1 * 
			une_dim2) * une_dim1] * opc[ii + (jjp1 + kk * 
			opc_dim2) * opc_dim1]);
		tmp3_xon__ = -opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] * (
			-uc[im1 + (jp1 + km1 * uc_dim2) * uc_dim1] * dpsw[ii 
			+ (jjp1 + kk * dpsw_dim2) * dpsw_dim1] + oc[im1 + (
			jp1 + k * oc_dim2) * oc_dim1] * opsw[ii + (jjp1 + kk *
			 opsw_dim2) * opsw_dim1] - uc[im1 + (jp1 + k * 
			uc_dim2) * uc_dim1] * upsw[ii + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - us[im1 + (jp2 + km1 * 
			us_dim2) * us_dim1] * dpw[ii + (jjp1 + kk * dpw_dim2) 
			* dpw_dim1] - on[im1 + (jp1 + k * on_dim2) * on_dim1] 
			* opw[ii + (jjp1 + kk * opw_dim2) * opw_dim1] - un[
			im1 + (jp1 + k * un_dim2) * un_dim1] * upw[ii + (jjp1 
			+ kk * upw_dim2) * upw_dim1] - uw[i__ + (jp1 + km1 * 
			uw_dim2) * uw_dim1] * dps[ii + (jjp1 + kk * dps_dim2) 
			* dps_dim1] - oe[im1 + (jp1 + k * oe_dim2) * oe_dim1] 
			* ops[ii + (jjp1 + kk * ops_dim2) * ops_dim1] - ue[
			im1 + (jp1 + k * ue_dim2) * ue_dim1] * ups[ii + (jjp1 
			+ kk * ups_dim2) * ups_dim1] - usw[i__ + (jp2 + km1 * 
			usw_dim2) * usw_dim1] * dpc[ii + (jjp1 + kk * 
			dpc_dim2) * dpc_dim1] - one[im1 + (jp1 + k * one_dim2)
			 * one_dim1] * opc[ii + (jjp1 + kk * opc_dim2) * 
			opc_dim1] - une[im1 + (jp1 + k * une_dim2) * une_dim1]
			 * upc[ii + (jjp1 + kk * upc_dim2) * upc_dim1]);
		tmp4_xon__ = -upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * (
			-uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] * opsw[ii + (
			jjp1 + kk * opsw_dim2) * opsw_dim1] + oc[im1 + (jp1 + 
			kp1 * oc_dim2) * oc_dim1] * upsw[ii + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - us[im1 + (jp2 + k * us_dim2)
			 * us_dim1] * opw[ii + (jjp1 + kk * opw_dim2) * 
			opw_dim1] - on[im1 + (jp1 + kp1 * on_dim2) * on_dim1] 
			* upw[ii + (jjp1 + kk * upw_dim2) * upw_dim1] - uw[
			i__ + (jp1 + k * uw_dim2) * uw_dim1] * ops[ii + (jjp1 
			+ kk * ops_dim2) * ops_dim1] - oe[im1 + (jp1 + kp1 * 
			oe_dim2) * oe_dim1] * ups[ii + (jjp1 + kk * ups_dim2) 
			* ups_dim1] - usw[i__ + (jp2 + k * usw_dim2) * 
			usw_dim1] * opc[ii + (jjp1 + kk * opc_dim2) * 
			opc_dim1] - one[im1 + (jp1 + kp1 * one_dim2) * 
			one_dim1] * upc[ii + (jjp1 + kk * upc_dim2) * 
			upc_dim1]) - dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1]
			 * (-onw[i__ + (j + km1 * onw_dim2) * onw_dim1] * 
			dpsw[ii + (jjp1 + kk * dpsw_dim2) * dpsw_dim1] - unw[
			i__ + (j + km1 * unw_dim2) * unw_dim1] * opsw[ii + (
			jjp1 + kk * opsw_dim2) * opsw_dim1] - on[i__ + (j + 
			km1 * on_dim2) * on_dim1] * dps[ii + (jjp1 + kk * 
			dps_dim2) * dps_dim1] - un[i__ + (j + km1 * un_dim2) *
			 un_dim1] * ops[ii + (jjp1 + kk * ops_dim2) * 
			ops_dim1] - one[i__ + (j + km1 * one_dim2) * one_dim1]
			 * dpse[ii + (jjp1 + kk * dpse_dim2) * dpse_dim1] - 
			une[i__ + (j + km1 * une_dim2) * une_dim1] * opse[ii 
			+ (jjp1 + kk * opse_dim2) * opse_dim1]);
		tmp5_xon__ = -opc[ii + (jj + kk * opc_dim2) * opc_dim1] * (
			-use[im1 + (jp1 + km1 * use_dim2) * use_dim1] * dpsw[
			ii + (jjp1 + kk * dpsw_dim2) * dpsw_dim1] - onw[i__ + 
			(j + k * onw_dim2) * onw_dim1] * opsw[ii + (jjp1 + kk 
			* opsw_dim2) * opsw_dim1] - unw[i__ + (j + k * 
			unw_dim2) * unw_dim1] * upsw[ii + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - us[i__ + (jp1 + km1 * 
			us_dim2) * us_dim1] * dps[ii + (jjp1 + kk * dps_dim2) 
			* dps_dim1] - on[i__ + (j + k * on_dim2) * on_dim1] * 
			ops[ii + (jjp1 + kk * ops_dim2) * ops_dim1] - un[i__ 
			+ (j + k * un_dim2) * un_dim1] * ups[ii + (jjp1 + kk *
			 ups_dim2) * ups_dim1] - usw[ip1 + (jp1 + km1 * 
			usw_dim2) * usw_dim1] * dpse[ii + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] - one[i__ + (j + k * one_dim2)
			 * one_dim1] * opse[ii + (jjp1 + kk * opse_dim2) * 
			opse_dim1] - une[i__ + (j + k * une_dim2) * une_dim1] 
			* upse[ii + (jjp1 + kk * upse_dim2) * upse_dim1]) - 
			upc[ii + (jj + kk * upc_dim2) * upc_dim1] * (-use[im1 
			+ (jp1 + k * use_dim2) * use_dim1] * opsw[ii + (jjp1 
			+ kk * opsw_dim2) * opsw_dim1] - onw[i__ + (j + kp1 * 
			onw_dim2) * onw_dim1] * upsw[ii + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - us[i__ + (jp1 + k * us_dim2)
			 * us_dim1] * ops[ii + (jjp1 + kk * ops_dim2) * 
			ops_dim1] - on[i__ + (j + kp1 * on_dim2) * on_dim1] * 
			ups[ii + (jjp1 + kk * ups_dim2) * ups_dim1] - usw[ip1 
			+ (jp1 + k * usw_dim2) * usw_dim1] * opse[ii + (jjp1 
			+ kk * opse_dim2) * opse_dim1] - one[i__ + (j + kp1 * 
			one_dim2) * one_dim1] * upse[ii + (jjp1 + kk * 
			upse_dim2) * upse_dim1]);
		tmp6_xon__ = -dpn[ii + (jj + kk * dpn_dim2) * dpn_dim1] * (
			-oe[im1 + (jp1 + km1 * oe_dim2) * oe_dim1] * dpsw[ii 
			+ (jjp1 + kk * dpsw_dim2) * dpsw_dim1] - uw[i__ + (
			jp1 + km1 * uw_dim2) * uw_dim1] * opsw[ii + (jjp1 + 
			kk * opsw_dim2) * opsw_dim1] - onw[i__ + (jp1 + km1 * 
			onw_dim2) * onw_dim1] * dpw[ii + (jjp1 + kk * 
			dpw_dim2) * dpw_dim1] - unw[i__ + (jp1 + km1 * 
			unw_dim2) * unw_dim1] * opw[ii + (jjp1 + kk * 
			opw_dim2) * opw_dim1] + oc[i__ + (jp1 + km1 * oc_dim2)
			 * oc_dim1] * dps[ii + (jjp1 + kk * dps_dim2) * 
			dps_dim1] - uc[i__ + (jp1 + km1 * uc_dim2) * uc_dim1] 
			* ops[ii + (jjp1 + kk * ops_dim2) * ops_dim1] - on[
			i__ + (jp1 + km1 * on_dim2) * on_dim1] * dpc[ii + (
			jjp1 + kk * dpc_dim2) * dpc_dim1] - un[i__ + (jp1 + 
			km1 * un_dim2) * un_dim1] * opc[ii + (jjp1 + kk * 
			opc_dim2) * opc_dim1] - oe[i__ + (jp1 + km1 * oe_dim2)
			 * oe_dim1] * dpse[ii + (jjp1 + kk * dpse_dim2) * 
			dpse_dim1] - ue[i__ + (jp1 + km1 * ue_dim2) * ue_dim1]
			 * opse[ii + (jjp1 + kk * opse_dim2) * opse_dim1] - 
			one[i__ + (jp1 + km1 * one_dim2) * one_dim1] * dpe[ii 
			+ (jjp1 + kk * dpe_dim2) * dpe_dim1] - une[i__ + (jp1 
			+ km1 * une_dim2) * une_dim1] * ope[ii + (jjp1 + kk * 
			ope_dim2) * ope_dim1]);
		tmp7_xon__ = -opn[ii + (jj + kk * opn_dim2) * opn_dim1] * (
			-ue[im1 + (jp1 + km1 * ue_dim2) * ue_dim1] * dpsw[ii 
			+ (jjp1 + kk * dpsw_dim2) * dpsw_dim1] - oe[im1 + (
			jp1 + k * oe_dim2) * oe_dim1] * opsw[ii + (jjp1 + kk *
			 opsw_dim2) * opsw_dim1] - uw[i__ + (jp1 + k * 
			uw_dim2) * uw_dim1] * upsw[ii + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - use[im1 + (jp2 + km1 * 
			use_dim2) * use_dim1] * dpw[ii + (jjp1 + kk * 
			dpw_dim2) * dpw_dim1] - onw[i__ + (jp1 + k * onw_dim2)
			 * onw_dim1] * opw[ii + (jjp1 + kk * opw_dim2) * 
			opw_dim1] - unw[i__ + (jp1 + k * unw_dim2) * unw_dim1]
			 * upw[ii + (jjp1 + kk * upw_dim2) * upw_dim1] - uc[
			i__ + (jp1 + km1 * uc_dim2) * uc_dim1] * dps[ii + (
			jjp1 + kk * dps_dim2) * dps_dim1] + oc[i__ + (jp1 + k 
			* oc_dim2) * oc_dim1] * ops[ii + (jjp1 + kk * 
			ops_dim2) * ops_dim1] - uc[i__ + (jp1 + k * uc_dim2) *
			 uc_dim1] * ups[ii + (jjp1 + kk * ups_dim2) * 
			ups_dim1] - us[i__ + (jp2 + km1 * us_dim2) * us_dim1] 
			* dpc[ii + (jjp1 + kk * dpc_dim2) * dpc_dim1] - on[
			i__ + (jp1 + k * on_dim2) * on_dim1] * opc[ii + (jjp1 
			+ kk * opc_dim2) * opc_dim1] - un[i__ + (jp1 + k * 
			un_dim2) * un_dim1] * upc[ii + (jjp1 + kk * upc_dim2) 
			* upc_dim1] - uw[ip1 + (jp1 + km1 * uw_dim2) * 
			uw_dim1] * dpse[ii + (jjp1 + kk * dpse_dim2) * 
			dpse_dim1] - oe[i__ + (jp1 + k * oe_dim2) * oe_dim1] *
			 opse[ii + (jjp1 + kk * opse_dim2) * opse_dim1] - ue[
			i__ + (jp1 + k * ue_dim2) * ue_dim1] * upse[ii + (
			jjp1 + kk * upse_dim2) * upse_dim1] - usw[ip1 + (jp2 
			+ km1 * usw_dim2) * usw_dim1] * dpe[ii + (jjp1 + kk * 
			dpe_dim2) * dpe_dim1] - one[i__ + (jp1 + k * one_dim2)
			 * one_dim1] * ope[ii + (jjp1 + kk * ope_dim2) * 
			ope_dim1] - une[i__ + (jp1 + k * une_dim2) * une_dim1]
			 * upe[ii + (jjp1 + kk * upe_dim2) * upe_dim1]);
		tmp8_xon__ = -upn[ii + (jj + kk * upn_dim2) * upn_dim1] * (
			-ue[im1 + (jp1 + k * ue_dim2) * ue_dim1] * opsw[ii + (
			jjp1 + kk * opsw_dim2) * opsw_dim1] - oe[im1 + (jp1 + 
			kp1 * oe_dim2) * oe_dim1] * upsw[ii + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - use[im1 + (jp2 + k * 
			use_dim2) * use_dim1] * opw[ii + (jjp1 + kk * 
			opw_dim2) * opw_dim1] - onw[i__ + (jp1 + kp1 * 
			onw_dim2) * onw_dim1] * upw[ii + (jjp1 + kk * 
			upw_dim2) * upw_dim1] - uc[i__ + (jp1 + k * uc_dim2) *
			 uc_dim1] * ops[ii + (jjp1 + kk * ops_dim2) * 
			ops_dim1] + oc[i__ + (jp1 + kp1 * oc_dim2) * oc_dim1] 
			* ups[ii + (jjp1 + kk * ups_dim2) * ups_dim1] - us[
			i__ + (jp2 + k * us_dim2) * us_dim1] * opc[ii + (jjp1 
			+ kk * opc_dim2) * opc_dim1] - on[i__ + (jp1 + kp1 * 
			on_dim2) * on_dim1] * upc[ii + (jjp1 + kk * upc_dim2) 
			* upc_dim1] - uw[ip1 + (jp1 + k * uw_dim2) * uw_dim1] 
			* opse[ii + (jjp1 + kk * opse_dim2) * opse_dim1] - oe[
			i__ + (jp1 + kp1 * oe_dim2) * oe_dim1] * upse[ii + (
			jjp1 + kk * upse_dim2) * upse_dim1] - usw[ip1 + (jp2 
			+ k * usw_dim2) * usw_dim1] * ope[ii + (jjp1 + kk * 
			ope_dim2) * ope_dim1] - one[i__ + (jp1 + kp1 * 
			one_dim2) * one_dim1] * upe[ii + (jjp1 + kk * 
			upe_dim2) * upe_dim1]) - dpe[ii + (jj + kk * dpe_dim2)
			 * dpe_dim1] * (-onw[ip1 + (j + km1 * onw_dim2) * 
			onw_dim1] * dps[ii + (jjp1 + kk * dps_dim2) * 
			dps_dim1] - unw[ip1 + (j + km1 * unw_dim2) * unw_dim1]
			 * ops[ii + (jjp1 + kk * ops_dim2) * ops_dim1] - on[
			ip1 + (j + km1 * on_dim2) * on_dim1] * dpse[ii + (
			jjp1 + kk * dpse_dim2) * dpse_dim1] - un[ip1 + (j + 
			km1 * un_dim2) * un_dim1] * opse[ii + (jjp1 + kk * 
			opse_dim2) * opse_dim1]);
		tmp9_xon__ = -ope[ii + (jj + kk * ope_dim2) * ope_dim1] * (
			-use[i__ + (jp1 + km1 * use_dim2) * use_dim1] * dps[
			ii + (jjp1 + kk * dps_dim2) * dps_dim1] - onw[ip1 + (
			j + k * onw_dim2) * onw_dim1] * ops[ii + (jjp1 + kk * 
			ops_dim2) * ops_dim1] - unw[ip1 + (j + k * unw_dim2) *
			 unw_dim1] * ups[ii + (jjp1 + kk * ups_dim2) * 
			ups_dim1] - us[ip1 + (jp1 + km1 * us_dim2) * us_dim1] 
			* dpse[ii + (jjp1 + kk * dpse_dim2) * dpse_dim1] - on[
			ip1 + (j + k * on_dim2) * on_dim1] * opse[ii + (jjp1 
			+ kk * opse_dim2) * opse_dim1] - un[ip1 + (j + k * 
			un_dim2) * un_dim1] * upse[ii + (jjp1 + kk * 
			upse_dim2) * upse_dim1]) - upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1] * (-use[i__ + (jp1 + k * 
			use_dim2) * use_dim1] * ops[ii + (jjp1 + kk * 
			ops_dim2) * ops_dim1] - onw[ip1 + (j + kp1 * onw_dim2)
			 * onw_dim1] * ups[ii + (jjp1 + kk * ups_dim2) * 
			ups_dim1] - us[ip1 + (jp1 + k * us_dim2) * us_dim1] * 
			opse[ii + (jjp1 + kk * opse_dim2) * opse_dim1] - on[
			ip1 + (j + kp1 * on_dim2) * on_dim1] * upse[ii + (
			jjp1 + kk * upse_dim2) * upse_dim1]);
		tmp10_xon__ = -dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] * 
			(-oe[i__ + (jp1 + km1 * oe_dim2) * oe_dim1] * dps[ii 
			+ (jjp1 + kk * dps_dim2) * dps_dim1] - uw[ip1 + (jp1 
			+ km1 * uw_dim2) * uw_dim1] * ops[ii + (jjp1 + kk * 
			ops_dim2) * ops_dim1] - onw[ip1 + (jp1 + km1 * 
			onw_dim2) * onw_dim1] * dpc[ii + (jjp1 + kk * 
			dpc_dim2) * dpc_dim1] - unw[ip1 + (jp1 + km1 * 
			unw_dim2) * unw_dim1] * opc[ii + (jjp1 + kk * 
			opc_dim2) * opc_dim1] + oc[ip1 + (jp1 + km1 * oc_dim2)
			 * oc_dim1] * dpse[ii + (jjp1 + kk * dpse_dim2) * 
			dpse_dim1] - uc[ip1 + (jp1 + km1 * uc_dim2) * uc_dim1]
			 * opse[ii + (jjp1 + kk * opse_dim2) * opse_dim1] - 
			on[ip1 + (jp1 + km1 * on_dim2) * on_dim1] * dpe[ii + (
			jjp1 + kk * dpe_dim2) * dpe_dim1] - un[ip1 + (jp1 + 
			km1 * un_dim2) * un_dim1] * ope[ii + (jjp1 + kk * 
			ope_dim2) * ope_dim1]);
		tmp11_xon__ = -opne[ii + (jj + kk * opne_dim2) * opne_dim1] * 
			(-ue[i__ + (jp1 + km1 * ue_dim2) * ue_dim1] * dps[ii 
			+ (jjp1 + kk * dps_dim2) * dps_dim1] - oe[i__ + (jp1 
			+ k * oe_dim2) * oe_dim1] * ops[ii + (jjp1 + kk * 
			ops_dim2) * ops_dim1] - uw[ip1 + (jp1 + k * uw_dim2) *
			 uw_dim1] * ups[ii + (jjp1 + kk * ups_dim2) * 
			ups_dim1] - use[i__ + (jp2 + km1 * use_dim2) * 
			use_dim1] * dpc[ii + (jjp1 + kk * dpc_dim2) * 
			dpc_dim1] - onw[ip1 + (jp1 + k * onw_dim2) * onw_dim1]
			 * opc[ii + (jjp1 + kk * opc_dim2) * opc_dim1] - unw[
			ip1 + (jp1 + k * unw_dim2) * unw_dim1] * upc[ii + (
			jjp1 + kk * upc_dim2) * upc_dim1] - uc[ip1 + (jp1 + 
			km1 * uc_dim2) * uc_dim1] * dpse[ii + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] + oc[ip1 + (jp1 + k * oc_dim2)
			 * oc_dim1] * opse[ii + (jjp1 + kk * opse_dim2) * 
			opse_dim1] - uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1] *
			 upse[ii + (jjp1 + kk * upse_dim2) * upse_dim1] - us[
			ip1 + (jp2 + km1 * us_dim2) * us_dim1] * dpe[ii + (
			jjp1 + kk * dpe_dim2) * dpe_dim1] - on[ip1 + (jp1 + k 
			* on_dim2) * on_dim1] * ope[ii + (jjp1 + kk * 
			ope_dim2) * ope_dim1] - un[ip1 + (jp1 + k * un_dim2) *
			 un_dim1] * upe[ii + (jjp1 + kk * upe_dim2) * 
			upe_dim1]);
		tmp12_xon__ = -upne[ii + (jj + kk * upne_dim2) * upne_dim1] * 
			(-ue[i__ + (jp1 + k * ue_dim2) * ue_dim1] * ops[ii + (
			jjp1 + kk * ops_dim2) * ops_dim1] - oe[i__ + (jp1 + 
			kp1 * oe_dim2) * oe_dim1] * ups[ii + (jjp1 + kk * 
			ups_dim2) * ups_dim1] - use[i__ + (jp2 + k * use_dim2)
			 * use_dim1] * opc[ii + (jjp1 + kk * opc_dim2) * 
			opc_dim1] - onw[ip1 + (jp1 + kp1 * onw_dim2) * 
			onw_dim1] * upc[ii + (jjp1 + kk * upc_dim2) * 
			upc_dim1] - uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1] * 
			opse[ii + (jjp1 + kk * opse_dim2) * opse_dim1] + oc[
			ip1 + (jp1 + kp1 * oc_dim2) * oc_dim1] * upse[ii + (
			jjp1 + kk * upse_dim2) * upse_dim1] - us[ip1 + (jp2 + 
			k * us_dim2) * us_dim1] * ope[ii + (jjp1 + kk * 
			ope_dim2) * ope_dim1] - on[ip1 + (jp1 + kp1 * on_dim2)
			 * on_dim1] * upe[ii + (jjp1 + kk * upe_dim2) * 
			upe_dim1]);
		xon[ii + (jj + kk * xon_dim2) * xon_dim1] = tmp1_xon__ + 
			tmp2_xon__ + tmp3_xon__ + tmp4_xon__ + tmp5_xon__ + 
			tmp6_xon__ + tmp7_xon__ + tmp8_xon__ + tmp9_xon__ + 
			tmp10_xon__ + tmp11_xon__ + tmp12_xon__;
/* * ******************************************************************** */
/* * *** > uC; */
/* * ******************************************************************** */
/* * ***XuC(ii,jj,kk) = */
		tmp1_xuc__ = -opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] * (
			-uc[im1 + (jm1 + k * uc_dim2) * uc_dim1] * dpsw[ii + (
			jj + kkp1 * dpsw_dim2) * dpsw_dim1] - un[im1 + (jm1 + 
			k * un_dim2) * un_dim1] * dpw[ii + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - ue[im1 + (jm1 + k * ue_dim2) *
			 ue_dim1] * dps[ii + (jj + kkp1 * dps_dim2) * 
			dps_dim1] - une[im1 + (jm1 + k * une_dim2) * une_dim1]
			 * dpc[ii + (jj + kkp1 * dpc_dim2) * dpc_dim1]) - 
			upsw[ii + (jj + kk * upsw_dim2) * upsw_dim1] * (oc[
			im1 + (jm1 + kp1 * oc_dim2) * oc_dim1] * dpsw[ii + (
			jj + kkp1 * dpsw_dim2) * dpsw_dim1] - uc[im1 + (jm1 + 
			kp1 * uc_dim2) * uc_dim1] * opsw[ii + (jj + kkp1 * 
			opsw_dim2) * opsw_dim1] - on[im1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * dpw[ii + (jj + kkp1 * dpw_dim2) 
			* dpw_dim1] - un[im1 + (jm1 + kp1 * un_dim2) * 
			un_dim1] * opw[ii + (jj + kkp1 * opw_dim2) * opw_dim1]
			 - oe[im1 + (jm1 + kp1 * oe_dim2) * oe_dim1] * dps[ii 
			+ (jj + kkp1 * dps_dim2) * dps_dim1] - ue[im1 + (jm1 
			+ kp1 * ue_dim2) * ue_dim1] * ops[ii + (jj + kkp1 * 
			ops_dim2) * ops_dim1] - one[im1 + (jm1 + kp1 * 
			one_dim2) * one_dim1] * dpc[ii + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - une[im1 + (jm1 + kp1 * 
			une_dim2) * une_dim1] * opc[ii + (jj + kkp1 * 
			opc_dim2) * opc_dim1]);
		tmp2_xuc__ = -opw[ii + (jj + kk * opw_dim2) * opw_dim1] * (
			-us[im1 + (j + k * us_dim2) * us_dim1] * dpsw[ii + (
			jj + kkp1 * dpsw_dim2) * dpsw_dim1] - uc[im1 + (j + k 
			* uc_dim2) * uc_dim1] * dpw[ii + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - un[im1 + (j + k * un_dim2) * 
			un_dim1] * dpnw[ii + (jj + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - use[im1 + (j + k * use_dim2) * use_dim1] 
			* dps[ii + (jj + kkp1 * dps_dim2) * dps_dim1] - ue[
			im1 + (j + k * ue_dim2) * ue_dim1] * dpc[ii + (jj + 
			kkp1 * dpc_dim2) * dpc_dim1] - une[im1 + (j + k * 
			une_dim2) * une_dim1] * dpn[ii + (jj + kkp1 * 
			dpn_dim2) * dpn_dim1]);
		tmp3_xuc__ = -upw[ii + (jj + kk * upw_dim2) * upw_dim1] * (
			-on[im1 + (jm1 + kp1 * on_dim2) * on_dim1] * dpsw[ii 
			+ (jj + kkp1 * dpsw_dim2) * dpsw_dim1] - us[im1 + (j 
			+ kp1 * us_dim2) * us_dim1] * opsw[ii + (jj + kkp1 * 
			opsw_dim2) * opsw_dim1] + oc[im1 + (j + kp1 * oc_dim2)
			 * oc_dim1] * dpw[ii + (jj + kkp1 * dpw_dim2) * 
			dpw_dim1] - uc[im1 + (j + kp1 * uc_dim2) * uc_dim1] * 
			opw[ii + (jj + kkp1 * opw_dim2) * opw_dim1] - on[im1 
			+ (j + kp1 * on_dim2) * on_dim1] * dpnw[ii + (jj + 
			kkp1 * dpnw_dim2) * dpnw_dim1] - un[im1 + (j + kp1 * 
			un_dim2) * un_dim1] * opnw[ii + (jj + kkp1 * 
			opnw_dim2) * opnw_dim1] - onw[i__ + (jm1 + kp1 * 
			onw_dim2) * onw_dim1] * dps[ii + (jj + kkp1 * 
			dps_dim2) * dps_dim1] - use[im1 + (j + kp1 * use_dim2)
			 * use_dim1] * ops[ii + (jj + kkp1 * ops_dim2) * 
			ops_dim1] - oe[im1 + (j + kp1 * oe_dim2) * oe_dim1] * 
			dpc[ii + (jj + kkp1 * dpc_dim2) * dpc_dim1] - ue[im1 
			+ (j + kp1 * ue_dim2) * ue_dim1] * opc[ii + (jj + 
			kkp1 * opc_dim2) * opc_dim1] - one[im1 + (j + kp1 * 
			one_dim2) * one_dim1] * dpn[ii + (jj + kkp1 * 
			dpn_dim2) * dpn_dim1] - une[im1 + (j + kp1 * une_dim2)
			 * une_dim1] * opn[ii + (jj + kkp1 * opn_dim2) * 
			opn_dim1]) - opnw[ii + (jj + kk * opnw_dim2) * 
			opnw_dim1] * (-us[im1 + (jp1 + k * us_dim2) * us_dim1]
			 * dpw[ii + (jj + kkp1 * dpw_dim2) * dpw_dim1] - uc[
			im1 + (jp1 + k * uc_dim2) * uc_dim1] * dpnw[ii + (jj 
			+ kkp1 * dpnw_dim2) * dpnw_dim1] - use[im1 + (jp1 + k 
			* use_dim2) * use_dim1] * dpc[ii + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - ue[im1 + (jp1 + k * ue_dim2) *
			 ue_dim1] * dpn[ii + (jj + kkp1 * dpn_dim2) * 
			dpn_dim1]);
		tmp4_xuc__ = -upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * (
			-on[im1 + (j + kp1 * on_dim2) * on_dim1] * dpw[ii + (
			jj + kkp1 * dpw_dim2) * dpw_dim1] - us[im1 + (jp1 + 
			kp1 * us_dim2) * us_dim1] * opw[ii + (jj + kkp1 * 
			opw_dim2) * opw_dim1] + oc[im1 + (jp1 + kp1 * oc_dim2)
			 * oc_dim1] * dpnw[ii + (jj + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - uc[im1 + (jp1 + kp1 * uc_dim2) * uc_dim1]
			 * opnw[ii + (jj + kkp1 * opnw_dim2) * opnw_dim1] - 
			onw[i__ + (j + kp1 * onw_dim2) * onw_dim1] * dpc[ii + 
			(jj + kkp1 * dpc_dim2) * dpc_dim1] - use[im1 + (jp1 + 
			kp1 * use_dim2) * use_dim1] * opc[ii + (jj + kkp1 * 
			opc_dim2) * opc_dim1] - oe[im1 + (jp1 + kp1 * oe_dim2)
			 * oe_dim1] * dpn[ii + (jj + kkp1 * dpn_dim2) * 
			dpn_dim1] - ue[im1 + (jp1 + kp1 * ue_dim2) * ue_dim1] 
			* opn[ii + (jj + kkp1 * opn_dim2) * opn_dim1]) - ops[
			ii + (jj + kk * ops_dim2) * ops_dim1] * (-uw[i__ + (
			jm1 + k * uw_dim2) * uw_dim1] * dpsw[ii + (jj + kkp1 *
			 dpsw_dim2) * dpsw_dim1] - unw[i__ + (jm1 + k * 
			unw_dim2) * unw_dim1] * dpw[ii + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - uc[i__ + (jm1 + k * uc_dim2) *
			 uc_dim1] * dps[ii + (jj + kkp1 * dps_dim2) * 
			dps_dim1] - un[i__ + (jm1 + k * un_dim2) * un_dim1] * 
			dpc[ii + (jj + kkp1 * dpc_dim2) * dpc_dim1] - ue[i__ 
			+ (jm1 + k * ue_dim2) * ue_dim1] * dpse[ii + (jj + 
			kkp1 * dpse_dim2) * dpse_dim1] - une[i__ + (jm1 + k * 
			une_dim2) * une_dim1] * dpe[ii + (jj + kkp1 * 
			dpe_dim2) * dpe_dim1]);
		tmp5_xuc__ = -ups[ii + (jj + kk * ups_dim2) * ups_dim1] * (
			-oe[im1 + (jm1 + kp1 * oe_dim2) * oe_dim1] * dpsw[ii 
			+ (jj + kkp1 * dpsw_dim2) * dpsw_dim1] - uw[i__ + (
			jm1 + kp1 * uw_dim2) * uw_dim1] * opsw[ii + (jj + 
			kkp1 * opsw_dim2) * opsw_dim1] - onw[i__ + (jm1 + kp1 
			* onw_dim2) * onw_dim1] * dpw[ii + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - unw[i__ + (jm1 + kp1 * 
			unw_dim2) * unw_dim1] * opw[ii + (jj + kkp1 * 
			opw_dim2) * opw_dim1] + oc[i__ + (jm1 + kp1 * oc_dim2)
			 * oc_dim1] * dps[ii + (jj + kkp1 * dps_dim2) * 
			dps_dim1] - uc[i__ + (jm1 + kp1 * uc_dim2) * uc_dim1] 
			* ops[ii + (jj + kkp1 * ops_dim2) * ops_dim1] - on[
			i__ + (jm1 + kp1 * on_dim2) * on_dim1] * dpc[ii + (jj 
			+ kkp1 * dpc_dim2) * dpc_dim1] - un[i__ + (jm1 + kp1 *
			 un_dim2) * un_dim1] * opc[ii + (jj + kkp1 * opc_dim2)
			 * opc_dim1] - oe[i__ + (jm1 + kp1 * oe_dim2) * 
			oe_dim1] * dpse[ii + (jj + kkp1 * dpse_dim2) * 
			dpse_dim1] - ue[i__ + (jm1 + kp1 * ue_dim2) * ue_dim1]
			 * opse[ii + (jj + kkp1 * opse_dim2) * opse_dim1] - 
			one[i__ + (jm1 + kp1 * one_dim2) * one_dim1] * dpe[ii 
			+ (jj + kkp1 * dpe_dim2) * dpe_dim1] - une[i__ + (jm1 
			+ kp1 * une_dim2) * une_dim1] * ope[ii + (jj + kkp1 * 
			ope_dim2) * ope_dim1]);
		tmp6_xuc__ = -opc[ii + (jj + kk * opc_dim2) * opc_dim1] * (
			-usw[i__ + (j + k * usw_dim2) * usw_dim1] * dpsw[ii + 
			(jj + kkp1 * dpsw_dim2) * dpsw_dim1] - uw[i__ + (j + 
			k * uw_dim2) * uw_dim1] * dpw[ii + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - unw[i__ + (j + k * unw_dim2) *
			 unw_dim1] * dpnw[ii + (jj + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - us[i__ + (j + k * us_dim2) * us_dim1] * 
			dps[ii + (jj + kkp1 * dps_dim2) * dps_dim1] - uc[i__ 
			+ (j + k * uc_dim2) * uc_dim1] * dpc[ii + (jj + kkp1 *
			 dpc_dim2) * dpc_dim1] - un[i__ + (j + k * un_dim2) * 
			un_dim1] * dpn[ii + (jj + kkp1 * dpn_dim2) * dpn_dim1]
			 - use[i__ + (j + k * use_dim2) * use_dim1] * dpse[ii 
			+ (jj + kkp1 * dpse_dim2) * dpse_dim1] - ue[i__ + (j 
			+ k * ue_dim2) * ue_dim1] * dpe[ii + (jj + kkp1 * 
			dpe_dim2) * dpe_dim1] - une[i__ + (j + k * une_dim2) *
			 une_dim1] * dpne[ii + (jj + kkp1 * dpne_dim2) * 
			dpne_dim1]);
		tmp7_xuc__ = -upc[ii + (jj + kk * upc_dim2) * upc_dim1] * (
			-one[im1 + (jm1 + kp1 * one_dim2) * one_dim1] * dpsw[
			ii + (jj + kkp1 * dpsw_dim2) * dpsw_dim1] - usw[i__ + 
			(j + kp1 * usw_dim2) * usw_dim1] * opsw[ii + (jj + 
			kkp1 * opsw_dim2) * opsw_dim1] - oe[im1 + (j + kp1 * 
			oe_dim2) * oe_dim1] * dpw[ii + (jj + kkp1 * dpw_dim2) 
			* dpw_dim1] - uw[i__ + (j + kp1 * uw_dim2) * uw_dim1] 
			* opw[ii + (jj + kkp1 * opw_dim2) * opw_dim1] - onw[
			i__ + (j + kp1 * onw_dim2) * onw_dim1] * dpnw[ii + (
			jj + kkp1 * dpnw_dim2) * dpnw_dim1] - unw[i__ + (j + 
			kp1 * unw_dim2) * unw_dim1] * opnw[ii + (jj + kkp1 * 
			opnw_dim2) * opnw_dim1] - on[i__ + (jm1 + kp1 * 
			on_dim2) * on_dim1] * dps[ii + (jj + kkp1 * dps_dim2) 
			* dps_dim1] - us[i__ + (j + kp1 * us_dim2) * us_dim1] 
			* ops[ii + (jj + kkp1 * ops_dim2) * ops_dim1] + oc[
			i__ + (j + kp1 * oc_dim2) * oc_dim1] * dpc[ii + (jj + 
			kkp1 * dpc_dim2) * dpc_dim1] - uc[i__ + (j + kp1 * 
			uc_dim2) * uc_dim1] * opc[ii + (jj + kkp1 * opc_dim2) 
			* opc_dim1] - on[i__ + (j + kp1 * on_dim2) * on_dim1] 
			* dpn[ii + (jj + kkp1 * dpn_dim2) * dpn_dim1] - un[
			i__ + (j + kp1 * un_dim2) * un_dim1] * opn[ii + (jj + 
			kkp1 * opn_dim2) * opn_dim1] - onw[ip1 + (jm1 + kp1 * 
			onw_dim2) * onw_dim1] * dpse[ii + (jj + kkp1 * 
			dpse_dim2) * dpse_dim1] - use[i__ + (j + kp1 * 
			use_dim2) * use_dim1] * opse[ii + (jj + kkp1 * 
			opse_dim2) * opse_dim1] - oe[i__ + (j + kp1 * oe_dim2)
			 * oe_dim1] * dpe[ii + (jj + kkp1 * dpe_dim2) * 
			dpe_dim1] - ue[i__ + (j + kp1 * ue_dim2) * ue_dim1] * 
			ope[ii + (jj + kkp1 * ope_dim2) * ope_dim1] - one[i__ 
			+ (j + kp1 * one_dim2) * one_dim1] * dpne[ii + (jj + 
			kkp1 * dpne_dim2) * dpne_dim1] - une[i__ + (j + kp1 * 
			une_dim2) * une_dim1] * opne[ii + (jj + kkp1 * 
			opne_dim2) * opne_dim1]);
		tmp8_xuc__ = -opn[ii + (jj + kk * opn_dim2) * opn_dim1] * (
			-usw[i__ + (jp1 + k * usw_dim2) * usw_dim1] * dpw[ii 
			+ (jj + kkp1 * dpw_dim2) * dpw_dim1] - uw[i__ + (jp1 
			+ k * uw_dim2) * uw_dim1] * dpnw[ii + (jj + kkp1 * 
			dpnw_dim2) * dpnw_dim1] - us[i__ + (jp1 + k * us_dim2)
			 * us_dim1] * dpc[ii + (jj + kkp1 * dpc_dim2) * 
			dpc_dim1] - uc[i__ + (jp1 + k * uc_dim2) * uc_dim1] * 
			dpn[ii + (jj + kkp1 * dpn_dim2) * dpn_dim1] - use[i__ 
			+ (jp1 + k * use_dim2) * use_dim1] * dpe[ii + (jj + 
			kkp1 * dpe_dim2) * dpe_dim1] - ue[i__ + (jp1 + k * 
			ue_dim2) * ue_dim1] * dpne[ii + (jj + kkp1 * 
			dpne_dim2) * dpne_dim1]);
		tmp9_xuc__ = -upn[ii + (jj + kk * upn_dim2) * upn_dim1] * (
			-one[im1 + (j + kp1 * one_dim2) * one_dim1] * dpw[ii 
			+ (jj + kkp1 * dpw_dim2) * dpw_dim1] - usw[i__ + (jp1 
			+ kp1 * usw_dim2) * usw_dim1] * opw[ii + (jj + kkp1 * 
			opw_dim2) * opw_dim1] - oe[im1 + (jp1 + kp1 * oe_dim2)
			 * oe_dim1] * dpnw[ii + (jj + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - uw[i__ + (jp1 + kp1 * uw_dim2) * uw_dim1]
			 * opnw[ii + (jj + kkp1 * opnw_dim2) * opnw_dim1] - 
			on[i__ + (j + kp1 * on_dim2) * on_dim1] * dpc[ii + (
			jj + kkp1 * dpc_dim2) * dpc_dim1] - us[i__ + (jp1 + 
			kp1 * us_dim2) * us_dim1] * opc[ii + (jj + kkp1 * 
			opc_dim2) * opc_dim1] + oc[i__ + (jp1 + kp1 * oc_dim2)
			 * oc_dim1] * dpn[ii + (jj + kkp1 * dpn_dim2) * 
			dpn_dim1] - uc[i__ + (jp1 + kp1 * uc_dim2) * uc_dim1] 
			* opn[ii + (jj + kkp1 * opn_dim2) * opn_dim1] - onw[
			ip1 + (j + kp1 * onw_dim2) * onw_dim1] * dpe[ii + (jj 
			+ kkp1 * dpe_dim2) * dpe_dim1] - use[i__ + (jp1 + kp1 
			* use_dim2) * use_dim1] * ope[ii + (jj + kkp1 * 
			ope_dim2) * ope_dim1] - oe[i__ + (jp1 + kp1 * oe_dim2)
			 * oe_dim1] * dpne[ii + (jj + kkp1 * dpne_dim2) * 
			dpne_dim1] - ue[i__ + (jp1 + kp1 * ue_dim2) * ue_dim1]
			 * opne[ii + (jj + kkp1 * opne_dim2) * opne_dim1]) - 
			opse[ii + (jj + kk * opse_dim2) * opse_dim1] * (-uw[
			ip1 + (jm1 + k * uw_dim2) * uw_dim1] * dps[ii + (jj + 
			kkp1 * dps_dim2) * dps_dim1] - unw[ip1 + (jm1 + k * 
			unw_dim2) * unw_dim1] * dpc[ii + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - uc[ip1 + (jm1 + k * uc_dim2) *
			 uc_dim1] * dpse[ii + (jj + kkp1 * dpse_dim2) * 
			dpse_dim1] - un[ip1 + (jm1 + k * un_dim2) * un_dim1] *
			 dpe[ii + (jj + kkp1 * dpe_dim2) * dpe_dim1]);
		tmp10_xuc__ = -upse[ii + (jj + kk * upse_dim2) * upse_dim1] * 
			(-oe[i__ + (jm1 + kp1 * oe_dim2) * oe_dim1] * dps[ii 
			+ (jj + kkp1 * dps_dim2) * dps_dim1] - uw[ip1 + (jm1 
			+ kp1 * uw_dim2) * uw_dim1] * ops[ii + (jj + kkp1 * 
			ops_dim2) * ops_dim1] - onw[ip1 + (jm1 + kp1 * 
			onw_dim2) * onw_dim1] * dpc[ii + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - unw[ip1 + (jm1 + kp1 * 
			unw_dim2) * unw_dim1] * opc[ii + (jj + kkp1 * 
			opc_dim2) * opc_dim1] + oc[ip1 + (jm1 + kp1 * oc_dim2)
			 * oc_dim1] * dpse[ii + (jj + kkp1 * dpse_dim2) * 
			dpse_dim1] - uc[ip1 + (jm1 + kp1 * uc_dim2) * uc_dim1]
			 * opse[ii + (jj + kkp1 * opse_dim2) * opse_dim1] - 
			on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1] * dpe[ii + (
			jj + kkp1 * dpe_dim2) * dpe_dim1] - un[ip1 + (jm1 + 
			kp1 * un_dim2) * un_dim1] * ope[ii + (jj + kkp1 * 
			ope_dim2) * ope_dim1]) - ope[ii + (jj + kk * ope_dim2)
			 * ope_dim1] * (-usw[ip1 + (j + k * usw_dim2) * 
			usw_dim1] * dps[ii + (jj + kkp1 * dps_dim2) * 
			dps_dim1] - uw[ip1 + (j + k * uw_dim2) * uw_dim1] * 
			dpc[ii + (jj + kkp1 * dpc_dim2) * dpc_dim1] - unw[ip1 
			+ (j + k * unw_dim2) * unw_dim1] * dpn[ii + (jj + 
			kkp1 * dpn_dim2) * dpn_dim1] - us[ip1 + (j + k * 
			us_dim2) * us_dim1] * dpse[ii + (jj + kkp1 * 
			dpse_dim2) * dpse_dim1] - uc[ip1 + (j + k * uc_dim2) *
			 uc_dim1] * dpe[ii + (jj + kkp1 * dpe_dim2) * 
			dpe_dim1] - un[ip1 + (j + k * un_dim2) * un_dim1] * 
			dpne[ii + (jj + kkp1 * dpne_dim2) * dpne_dim1]);
		tmp11_xuc__ = -upe[ii + (jj + kk * upe_dim2) * upe_dim1] * (
			-one[i__ + (jm1 + kp1 * one_dim2) * one_dim1] * dps[
			ii + (jj + kkp1 * dps_dim2) * dps_dim1] - usw[ip1 + (
			j + kp1 * usw_dim2) * usw_dim1] * ops[ii + (jj + kkp1 
			* ops_dim2) * ops_dim1] - oe[i__ + (j + kp1 * oe_dim2)
			 * oe_dim1] * dpc[ii + (jj + kkp1 * dpc_dim2) * 
			dpc_dim1] - uw[ip1 + (j + kp1 * uw_dim2) * uw_dim1] * 
			opc[ii + (jj + kkp1 * opc_dim2) * opc_dim1] - onw[ip1 
			+ (j + kp1 * onw_dim2) * onw_dim1] * dpn[ii + (jj + 
			kkp1 * dpn_dim2) * dpn_dim1] - unw[ip1 + (j + kp1 * 
			unw_dim2) * unw_dim1] * opn[ii + (jj + kkp1 * 
			opn_dim2) * opn_dim1] - on[ip1 + (jm1 + kp1 * on_dim2)
			 * on_dim1] * dpse[ii + (jj + kkp1 * dpse_dim2) * 
			dpse_dim1] - us[ip1 + (j + kp1 * us_dim2) * us_dim1] *
			 opse[ii + (jj + kkp1 * opse_dim2) * opse_dim1] + oc[
			ip1 + (j + kp1 * oc_dim2) * oc_dim1] * dpe[ii + (jj + 
			kkp1 * dpe_dim2) * dpe_dim1] - uc[ip1 + (j + kp1 * 
			uc_dim2) * uc_dim1] * ope[ii + (jj + kkp1 * ope_dim2) 
			* ope_dim1] - on[ip1 + (j + kp1 * on_dim2) * on_dim1] 
			* dpne[ii + (jj + kkp1 * dpne_dim2) * dpne_dim1] - un[
			ip1 + (j + kp1 * un_dim2) * un_dim1] * opne[ii + (jj 
			+ kkp1 * opne_dim2) * opne_dim1]);
		tmp12_xuc__ = -opne[ii + (jj + kk * opne_dim2) * opne_dim1] * 
			(-usw[ip1 + (jp1 + k * usw_dim2) * usw_dim1] * dpc[ii 
			+ (jj + kkp1 * dpc_dim2) * dpc_dim1] - uw[ip1 + (jp1 
			+ k * uw_dim2) * uw_dim1] * dpn[ii + (jj + kkp1 * 
			dpn_dim2) * dpn_dim1] - us[ip1 + (jp1 + k * us_dim2) *
			 us_dim1] * dpe[ii + (jj + kkp1 * dpe_dim2) * 
			dpe_dim1] - uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1] * 
			dpne[ii + (jj + kkp1 * dpne_dim2) * dpne_dim1]) - 
			upne[ii + (jj + kk * upne_dim2) * upne_dim1] * (-one[
			i__ + (j + kp1 * one_dim2) * one_dim1] * dpc[ii + (jj 
			+ kkp1 * dpc_dim2) * dpc_dim1] - usw[ip1 + (jp1 + kp1 
			* usw_dim2) * usw_dim1] * opc[ii + (jj + kkp1 * 
			opc_dim2) * opc_dim1] - oe[i__ + (jp1 + kp1 * oe_dim2)
			 * oe_dim1] * dpn[ii + (jj + kkp1 * dpn_dim2) * 
			dpn_dim1] - uw[ip1 + (jp1 + kp1 * uw_dim2) * uw_dim1] 
			* opn[ii + (jj + kkp1 * opn_dim2) * opn_dim1] - on[
			ip1 + (j + kp1 * on_dim2) * on_dim1] * dpe[ii + (jj + 
			kkp1 * dpe_dim2) * dpe_dim1] - us[ip1 + (jp1 + kp1 * 
			us_dim2) * us_dim1] * ope[ii + (jj + kkp1 * ope_dim2) 
			* ope_dim1] + oc[ip1 + (jp1 + kp1 * oc_dim2) * 
			oc_dim1] * dpne[ii + (jj + kkp1 * dpne_dim2) * 
			dpne_dim1] - uc[ip1 + (jp1 + kp1 * uc_dim2) * uc_dim1]
			 * opne[ii + (jj + kkp1 * opne_dim2) * opne_dim1]);
		xuc[ii + (jj + kk * xuc_dim2) * xuc_dim1] = tmp1_xuc__ + 
			tmp2_xuc__ + tmp3_xuc__ + tmp4_xuc__ + tmp5_xuc__ + 
			tmp6_xuc__ + tmp7_xuc__ + tmp8_xuc__ + tmp9_xuc__ + 
			tmp10_xuc__ + tmp11_xuc__ + tmp12_xuc__;
/* * ******************************************************************** */
/* * *** > oNE; */
/* * ******************************************************************** */
/* * ***XoNE(ii,jj,kk) = */
		tmp1_xone__ = -dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1] * (
			-one[i__ + (j + km1 * one_dim2) * one_dim1] * dpsw[
			iip1 + (jjp1 + kk * dpsw_dim2) * dpsw_dim1] - une[i__ 
			+ (j + km1 * une_dim2) * une_dim1] * opsw[iip1 + (
			jjp1 + kk * opsw_dim2) * opsw_dim1]) - opc[ii + (jj + 
			kk * opc_dim2) * opc_dim1] * (-usw[ip1 + (jp1 + km1 * 
			usw_dim2) * usw_dim1] * dpsw[iip1 + (jjp1 + kk * 
			dpsw_dim2) * dpsw_dim1] - one[i__ + (j + k * one_dim2)
			 * one_dim1] * opsw[iip1 + (jjp1 + kk * opsw_dim2) * 
			opsw_dim1] - une[i__ + (j + k * une_dim2) * une_dim1] 
			* upsw[iip1 + (jjp1 + kk * upsw_dim2) * upsw_dim1]) - 
			upc[ii + (jj + kk * upc_dim2) * upc_dim1] * (-usw[ip1 
			+ (jp1 + k * usw_dim2) * usw_dim1] * opsw[iip1 + (
			jjp1 + kk * opsw_dim2) * opsw_dim1] - one[i__ + (j + 
			kp1 * one_dim2) * one_dim1] * upsw[iip1 + (jjp1 + kk *
			 upsw_dim2) * upsw_dim1]) - dpn[ii + (jj + kk * 
			dpn_dim2) * dpn_dim1] * (-oe[i__ + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpsw[iip1 + (jjp1 + kk * 
			dpsw_dim2) * dpsw_dim1] - ue[i__ + (jp1 + km1 * 
			ue_dim2) * ue_dim1] * opsw[iip1 + (jjp1 + kk * 
			opsw_dim2) * opsw_dim1] - one[i__ + (jp1 + km1 * 
			one_dim2) * one_dim1] * dpw[iip1 + (jjp1 + kk * 
			dpw_dim2) * dpw_dim1] - une[i__ + (jp1 + km1 * 
			une_dim2) * une_dim1] * opw[iip1 + (jjp1 + kk * 
			opw_dim2) * opw_dim1]);
		tmp2_xone__ = -opn[ii + (jj + kk * opn_dim2) * opn_dim1] * (
			-uw[ip1 + (jp1 + km1 * uw_dim2) * uw_dim1] * dpsw[
			iip1 + (jjp1 + kk * dpsw_dim2) * dpsw_dim1] - oe[i__ 
			+ (jp1 + k * oe_dim2) * oe_dim1] * opsw[iip1 + (jjp1 
			+ kk * opsw_dim2) * opsw_dim1] - ue[i__ + (jp1 + k * 
			ue_dim2) * ue_dim1] * upsw[iip1 + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - usw[ip1 + (jp2 + km1 * 
			usw_dim2) * usw_dim1] * dpw[iip1 + (jjp1 + kk * 
			dpw_dim2) * dpw_dim1] - one[i__ + (jp1 + k * one_dim2)
			 * one_dim1] * opw[iip1 + (jjp1 + kk * opw_dim2) * 
			opw_dim1] - une[i__ + (jp1 + k * une_dim2) * une_dim1]
			 * upw[iip1 + (jjp1 + kk * upw_dim2) * upw_dim1]) - 
			upn[ii + (jj + kk * upn_dim2) * upn_dim1] * (-uw[ip1 
			+ (jp1 + k * uw_dim2) * uw_dim1] * opsw[iip1 + (jjp1 
			+ kk * opsw_dim2) * opsw_dim1] - oe[i__ + (jp1 + kp1 *
			 oe_dim2) * oe_dim1] * upsw[iip1 + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - usw[ip1 + (jp2 + k * 
			usw_dim2) * usw_dim1] * opw[iip1 + (jjp1 + kk * 
			opw_dim2) * opw_dim1] - one[i__ + (jp1 + kp1 * 
			one_dim2) * one_dim1] * upw[iip1 + (jjp1 + kk * 
			upw_dim2) * upw_dim1]) - dpe[ii + (jj + kk * dpe_dim2)
			 * dpe_dim1] * (-on[ip1 + (j + km1 * on_dim2) * 
			on_dim1] * dpsw[iip1 + (jjp1 + kk * dpsw_dim2) * 
			dpsw_dim1] - un[ip1 + (j + km1 * un_dim2) * un_dim1] *
			 opsw[iip1 + (jjp1 + kk * opsw_dim2) * opsw_dim1] - 
			one[ip1 + (j + km1 * one_dim2) * one_dim1] * dps[iip1 
			+ (jjp1 + kk * dps_dim2) * dps_dim1] - une[ip1 + (j + 
			km1 * une_dim2) * une_dim1] * ops[iip1 + (jjp1 + kk * 
			ops_dim2) * ops_dim1]);
		tmp3_xone__ = -ope[ii + (jj + kk * ope_dim2) * ope_dim1] * (
			-us[ip1 + (jp1 + km1 * us_dim2) * us_dim1] * dpsw[
			iip1 + (jjp1 + kk * dpsw_dim2) * dpsw_dim1] - on[ip1 
			+ (j + k * on_dim2) * on_dim1] * opsw[iip1 + (jjp1 + 
			kk * opsw_dim2) * opsw_dim1] - un[ip1 + (j + k * 
			un_dim2) * un_dim1] * upsw[iip1 + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - usw[ip2 + (jp1 + km1 * 
			usw_dim2) * usw_dim1] * dps[iip1 + (jjp1 + kk * 
			dps_dim2) * dps_dim1] - one[ip1 + (j + k * one_dim2) *
			 one_dim1] * ops[iip1 + (jjp1 + kk * ops_dim2) * 
			ops_dim1] - une[ip1 + (j + k * une_dim2) * une_dim1] *
			 ups[iip1 + (jjp1 + kk * ups_dim2) * ups_dim1]) - upe[
			ii + (jj + kk * upe_dim2) * upe_dim1] * (-us[ip1 + (
			jp1 + k * us_dim2) * us_dim1] * opsw[iip1 + (jjp1 + 
			kk * opsw_dim2) * opsw_dim1] - on[ip1 + (j + kp1 * 
			on_dim2) * on_dim1] * upsw[iip1 + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - usw[ip2 + (jp1 + k * 
			usw_dim2) * usw_dim1] * ops[iip1 + (jjp1 + kk * 
			ops_dim2) * ops_dim1] - one[ip1 + (j + kp1 * one_dim2)
			 * one_dim1] * ups[iip1 + (jjp1 + kk * ups_dim2) * 
			ups_dim1]);
		tmp4_xone__ = -dpne[ii + (jj + kk * dpne_dim2) * dpne_dim1] * 
			(oc[ip1 + (jp1 + km1 * oc_dim2) * oc_dim1] * dpsw[
			iip1 + (jjp1 + kk * dpsw_dim2) * dpsw_dim1] - uc[ip1 
			+ (jp1 + km1 * uc_dim2) * uc_dim1] * opsw[iip1 + (
			jjp1 + kk * opsw_dim2) * opsw_dim1] - on[ip1 + (jp1 + 
			km1 * on_dim2) * on_dim1] * dpw[iip1 + (jjp1 + kk * 
			dpw_dim2) * dpw_dim1] - un[ip1 + (jp1 + km1 * un_dim2)
			 * un_dim1] * opw[iip1 + (jjp1 + kk * opw_dim2) * 
			opw_dim1] - oe[ip1 + (jp1 + km1 * oe_dim2) * oe_dim1] 
			* dps[iip1 + (jjp1 + kk * dps_dim2) * dps_dim1] - ue[
			ip1 + (jp1 + km1 * ue_dim2) * ue_dim1] * ops[iip1 + (
			jjp1 + kk * ops_dim2) * ops_dim1] - one[ip1 + (jp1 + 
			km1 * one_dim2) * one_dim1] * dpc[iip1 + (jjp1 + kk * 
			dpc_dim2) * dpc_dim1] - une[ip1 + (jp1 + km1 * 
			une_dim2) * une_dim1] * opc[iip1 + (jjp1 + kk * 
			opc_dim2) * opc_dim1]);
		tmp5_xone__ = -opne[ii + (jj + kk * opne_dim2) * opne_dim1] * 
			(-uc[ip1 + (jp1 + km1 * uc_dim2) * uc_dim1] * dpsw[
			iip1 + (jjp1 + kk * dpsw_dim2) * dpsw_dim1] + oc[ip1 
			+ (jp1 + k * oc_dim2) * oc_dim1] * opsw[iip1 + (jjp1 
			+ kk * opsw_dim2) * opsw_dim1] - uc[ip1 + (jp1 + k * 
			uc_dim2) * uc_dim1] * upsw[iip1 + (jjp1 + kk * 
			upsw_dim2) * upsw_dim1] - us[ip1 + (jp2 + km1 * 
			us_dim2) * us_dim1] * dpw[iip1 + (jjp1 + kk * 
			dpw_dim2) * dpw_dim1] - on[ip1 + (jp1 + k * on_dim2) *
			 on_dim1] * opw[iip1 + (jjp1 + kk * opw_dim2) * 
			opw_dim1] - un[ip1 + (jp1 + k * un_dim2) * un_dim1] * 
			upw[iip1 + (jjp1 + kk * upw_dim2) * upw_dim1] - uw[
			ip2 + (jp1 + km1 * uw_dim2) * uw_dim1] * dps[iip1 + (
			jjp1 + kk * dps_dim2) * dps_dim1] - oe[ip1 + (jp1 + k 
			* oe_dim2) * oe_dim1] * ops[iip1 + (jjp1 + kk * 
			ops_dim2) * ops_dim1] - ue[ip1 + (jp1 + k * ue_dim2) *
			 ue_dim1] * ups[iip1 + (jjp1 + kk * ups_dim2) * 
			ups_dim1] - usw[ip2 + (jp2 + km1 * usw_dim2) * 
			usw_dim1] * dpc[iip1 + (jjp1 + kk * dpc_dim2) * 
			dpc_dim1] - one[ip1 + (jp1 + k * one_dim2) * one_dim1]
			 * opc[iip1 + (jjp1 + kk * opc_dim2) * opc_dim1] - 
			une[ip1 + (jp1 + k * une_dim2) * une_dim1] * upc[iip1 
			+ (jjp1 + kk * upc_dim2) * upc_dim1]);
		tmp6_xone__ = -upne[ii + (jj + kk * upne_dim2) * upne_dim1] * 
			(-uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1] * opsw[iip1 
			+ (jjp1 + kk * opsw_dim2) * opsw_dim1] + oc[ip1 + (
			jp1 + kp1 * oc_dim2) * oc_dim1] * upsw[iip1 + (jjp1 + 
			kk * upsw_dim2) * upsw_dim1] - us[ip1 + (jp2 + k * 
			us_dim2) * us_dim1] * opw[iip1 + (jjp1 + kk * 
			opw_dim2) * opw_dim1] - on[ip1 + (jp1 + kp1 * on_dim2)
			 * on_dim1] * upw[iip1 + (jjp1 + kk * upw_dim2) * 
			upw_dim1] - uw[ip2 + (jp1 + k * uw_dim2) * uw_dim1] * 
			ops[iip1 + (jjp1 + kk * ops_dim2) * ops_dim1] - oe[
			ip1 + (jp1 + kp1 * oe_dim2) * oe_dim1] * ups[iip1 + (
			jjp1 + kk * ups_dim2) * ups_dim1] - usw[ip2 + (jp2 + 
			k * usw_dim2) * usw_dim1] * opc[iip1 + (jjp1 + kk * 
			opc_dim2) * opc_dim1] - one[ip1 + (jp1 + kp1 * 
			one_dim2) * one_dim1] * upc[iip1 + (jjp1 + kk * 
			upc_dim2) * upc_dim1]);
		xone[ii + (jj + kk * xone_dim2) * xone_dim1] = tmp1_xone__ + 
			tmp2_xone__ + tmp3_xone__ + tmp4_xone__ + tmp5_xone__ 
			+ tmp6_xone__;
/* * ******************************************************************** */
/* * *** > oNW; */
/* * ******************************************************************** */
/* * ***XoNW(ii,jj,kk) = */
		tmp1_xonw__ = -dpw[ii + (jj + kk * dpw_dim2) * dpw_dim1] * (
			-onw[im1 + (j + km1 * onw_dim2) * onw_dim1] * dps[
			iim1 + (jjp1 + kk * dps_dim2) * dps_dim1] - unw[im1 + 
			(j + km1 * unw_dim2) * unw_dim1] * ops[iim1 + (jjp1 + 
			kk * ops_dim2) * ops_dim1] - on[im1 + (j + km1 * 
			on_dim2) * on_dim1] * dpse[iim1 + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] - un[im1 + (j + km1 * un_dim2)
			 * un_dim1] * opse[iim1 + (jjp1 + kk * opse_dim2) * 
			opse_dim1]) - opw[ii + (jj + kk * opw_dim2) * 
			opw_dim1] * (-use[im2 + (jp1 + km1 * use_dim2) * 
			use_dim1] * dps[iim1 + (jjp1 + kk * dps_dim2) * 
			dps_dim1] - onw[im1 + (j + k * onw_dim2) * onw_dim1] *
			 ops[iim1 + (jjp1 + kk * ops_dim2) * ops_dim1] - unw[
			im1 + (j + k * unw_dim2) * unw_dim1] * ups[iim1 + (
			jjp1 + kk * ups_dim2) * ups_dim1] - us[im1 + (jp1 + 
			km1 * us_dim2) * us_dim1] * dpse[iim1 + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] - on[im1 + (j + k * on_dim2) *
			 on_dim1] * opse[iim1 + (jjp1 + kk * opse_dim2) * 
			opse_dim1] - un[im1 + (j + k * un_dim2) * un_dim1] * 
			upse[iim1 + (jjp1 + kk * upse_dim2) * upse_dim1]);
		tmp2_xonw__ = -upw[ii + (jj + kk * upw_dim2) * upw_dim1] * (
			-use[im2 + (jp1 + k * use_dim2) * use_dim1] * ops[
			iim1 + (jjp1 + kk * ops_dim2) * ops_dim1] - onw[im1 + 
			(j + kp1 * onw_dim2) * onw_dim1] * ups[iim1 + (jjp1 + 
			kk * ups_dim2) * ups_dim1] - us[im1 + (jp1 + k * 
			us_dim2) * us_dim1] * opse[iim1 + (jjp1 + kk * 
			opse_dim2) * opse_dim1] - on[im1 + (j + kp1 * on_dim2)
			 * on_dim1] * upse[iim1 + (jjp1 + kk * upse_dim2) * 
			upse_dim1]) - dpnw[ii + (jj + kk * dpnw_dim2) * 
			dpnw_dim1] * (-oe[im2 + (jp1 + km1 * oe_dim2) * 
			oe_dim1] * dps[iim1 + (jjp1 + kk * dps_dim2) * 
			dps_dim1] - uw[im1 + (jp1 + km1 * uw_dim2) * uw_dim1] 
			* ops[iim1 + (jjp1 + kk * ops_dim2) * ops_dim1] - onw[
			im1 + (jp1 + km1 * onw_dim2) * onw_dim1] * dpc[iim1 + 
			(jjp1 + kk * dpc_dim2) * dpc_dim1] - unw[im1 + (jp1 + 
			km1 * unw_dim2) * unw_dim1] * opc[iim1 + (jjp1 + kk * 
			opc_dim2) * opc_dim1] + oc[im1 + (jp1 + km1 * oc_dim2)
			 * oc_dim1] * dpse[iim1 + (jjp1 + kk * dpse_dim2) * 
			dpse_dim1] - uc[im1 + (jp1 + km1 * uc_dim2) * uc_dim1]
			 * opse[iim1 + (jjp1 + kk * opse_dim2) * opse_dim1] - 
			on[im1 + (jp1 + km1 * on_dim2) * on_dim1] * dpe[iim1 
			+ (jjp1 + kk * dpe_dim2) * dpe_dim1] - un[im1 + (jp1 
			+ km1 * un_dim2) * un_dim1] * ope[iim1 + (jjp1 + kk * 
			ope_dim2) * ope_dim1]);
		tmp3_xonw__ = -opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] * 
			(-ue[im2 + (jp1 + km1 * ue_dim2) * ue_dim1] * dps[
			iim1 + (jjp1 + kk * dps_dim2) * dps_dim1] - oe[im2 + (
			jp1 + k * oe_dim2) * oe_dim1] * ops[iim1 + (jjp1 + kk 
			* ops_dim2) * ops_dim1] - uw[im1 + (jp1 + k * uw_dim2)
			 * uw_dim1] * ups[iim1 + (jjp1 + kk * ups_dim2) * 
			ups_dim1] - use[im2 + (jp2 + km1 * use_dim2) * 
			use_dim1] * dpc[iim1 + (jjp1 + kk * dpc_dim2) * 
			dpc_dim1] - onw[im1 + (jp1 + k * onw_dim2) * onw_dim1]
			 * opc[iim1 + (jjp1 + kk * opc_dim2) * opc_dim1] - 
			unw[im1 + (jp1 + k * unw_dim2) * unw_dim1] * upc[iim1 
			+ (jjp1 + kk * upc_dim2) * upc_dim1] - uc[im1 + (jp1 
			+ km1 * uc_dim2) * uc_dim1] * dpse[iim1 + (jjp1 + kk *
			 dpse_dim2) * dpse_dim1] + oc[im1 + (jp1 + k * 
			oc_dim2) * oc_dim1] * opse[iim1 + (jjp1 + kk * 
			opse_dim2) * opse_dim1] - uc[im1 + (jp1 + k * uc_dim2)
			 * uc_dim1] * upse[iim1 + (jjp1 + kk * upse_dim2) * 
			upse_dim1] - us[im1 + (jp2 + km1 * us_dim2) * us_dim1]
			 * dpe[iim1 + (jjp1 + kk * dpe_dim2) * dpe_dim1] - on[
			im1 + (jp1 + k * on_dim2) * on_dim1] * ope[iim1 + (
			jjp1 + kk * ope_dim2) * ope_dim1] - un[im1 + (jp1 + k 
			* un_dim2) * un_dim1] * upe[iim1 + (jjp1 + kk * 
			upe_dim2) * upe_dim1]);
		tmp4_xonw__ = -upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * 
			(-ue[im2 + (jp1 + k * ue_dim2) * ue_dim1] * ops[iim1 
			+ (jjp1 + kk * ops_dim2) * ops_dim1] - oe[im2 + (jp1 
			+ kp1 * oe_dim2) * oe_dim1] * ups[iim1 + (jjp1 + kk * 
			ups_dim2) * ups_dim1] - use[im2 + (jp2 + k * use_dim2)
			 * use_dim1] * opc[iim1 + (jjp1 + kk * opc_dim2) * 
			opc_dim1] - onw[im1 + (jp1 + kp1 * onw_dim2) * 
			onw_dim1] * upc[iim1 + (jjp1 + kk * upc_dim2) * 
			upc_dim1] - uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] * 
			opse[iim1 + (jjp1 + kk * opse_dim2) * opse_dim1] + oc[
			im1 + (jp1 + kp1 * oc_dim2) * oc_dim1] * upse[iim1 + (
			jjp1 + kk * upse_dim2) * upse_dim1] - us[im1 + (jp2 + 
			k * us_dim2) * us_dim1] * ope[iim1 + (jjp1 + kk * 
			ope_dim2) * ope_dim1] - on[im1 + (jp1 + kp1 * on_dim2)
			 * on_dim1] * upe[iim1 + (jjp1 + kk * upe_dim2) * 
			upe_dim1]) - dpc[ii + (jj + kk * dpc_dim2) * dpc_dim1]
			 * (-onw[i__ + (j + km1 * onw_dim2) * onw_dim1] * 
			dpse[iim1 + (jjp1 + kk * dpse_dim2) * dpse_dim1] - 
			unw[i__ + (j + km1 * unw_dim2) * unw_dim1] * opse[
			iim1 + (jjp1 + kk * opse_dim2) * opse_dim1]);
		tmp5_xonw__ = -opc[ii + (jj + kk * opc_dim2) * opc_dim1] * (
			-use[im1 + (jp1 + km1 * use_dim2) * use_dim1] * dpse[
			iim1 + (jjp1 + kk * dpse_dim2) * dpse_dim1] - onw[i__ 
			+ (j + k * onw_dim2) * onw_dim1] * opse[iim1 + (jjp1 
			+ kk * opse_dim2) * opse_dim1] - unw[i__ + (j + k * 
			unw_dim2) * unw_dim1] * upse[iim1 + (jjp1 + kk * 
			upse_dim2) * upse_dim1]) - upc[ii + (jj + kk * 
			upc_dim2) * upc_dim1] * (-use[im1 + (jp1 + k * 
			use_dim2) * use_dim1] * opse[iim1 + (jjp1 + kk * 
			opse_dim2) * opse_dim1] - onw[i__ + (j + kp1 * 
			onw_dim2) * onw_dim1] * upse[iim1 + (jjp1 + kk * 
			upse_dim2) * upse_dim1]) - dpn[ii + (jj + kk * 
			dpn_dim2) * dpn_dim1] * (-oe[im1 + (jp1 + km1 * 
			oe_dim2) * oe_dim1] * dpse[iim1 + (jjp1 + kk * 
			dpse_dim2) * dpse_dim1] - uw[i__ + (jp1 + km1 * 
			uw_dim2) * uw_dim1] * opse[iim1 + (jjp1 + kk * 
			opse_dim2) * opse_dim1] - onw[i__ + (jp1 + km1 * 
			onw_dim2) * onw_dim1] * dpe[iim1 + (jjp1 + kk * 
			dpe_dim2) * dpe_dim1] - unw[i__ + (jp1 + km1 * 
			unw_dim2) * unw_dim1] * ope[iim1 + (jjp1 + kk * 
			ope_dim2) * ope_dim1]);
		tmp6_xonw__ = -opn[ii + (jj + kk * opn_dim2) * opn_dim1] * (
			-ue[im1 + (jp1 + km1 * ue_dim2) * ue_dim1] * dpse[
			iim1 + (jjp1 + kk * dpse_dim2) * dpse_dim1] - oe[im1 
			+ (jp1 + k * oe_dim2) * oe_dim1] * opse[iim1 + (jjp1 
			+ kk * opse_dim2) * opse_dim1] - uw[i__ + (jp1 + k * 
			uw_dim2) * uw_dim1] * upse[iim1 + (jjp1 + kk * 
			upse_dim2) * upse_dim1] - use[im1 + (jp2 + km1 * 
			use_dim2) * use_dim1] * dpe[iim1 + (jjp1 + kk * 
			dpe_dim2) * dpe_dim1] - onw[i__ + (jp1 + k * onw_dim2)
			 * onw_dim1] * ope[iim1 + (jjp1 + kk * ope_dim2) * 
			ope_dim1] - unw[i__ + (jp1 + k * unw_dim2) * unw_dim1]
			 * upe[iim1 + (jjp1 + kk * upe_dim2) * upe_dim1]) - 
			upn[ii + (jj + kk * upn_dim2) * upn_dim1] * (-ue[im1 
			+ (jp1 + k * ue_dim2) * ue_dim1] * opse[iim1 + (jjp1 
			+ kk * opse_dim2) * opse_dim1] - oe[im1 + (jp1 + kp1 *
			 oe_dim2) * oe_dim1] * upse[iim1 + (jjp1 + kk * 
			upse_dim2) * upse_dim1] - use[im1 + (jp2 + k * 
			use_dim2) * use_dim1] * ope[iim1 + (jjp1 + kk * 
			ope_dim2) * ope_dim1] - onw[i__ + (jp1 + kp1 * 
			onw_dim2) * onw_dim1] * upe[iim1 + (jjp1 + kk * 
			upe_dim2) * upe_dim1]);
		xonw[ii + (jj + kk * xonw_dim2) * xonw_dim1] = tmp1_xonw__ + 
			tmp2_xonw__ + tmp3_xonw__ + tmp4_xonw__ + tmp5_xonw__ 
			+ tmp6_xonw__;
/* * ******************************************************************** */
/* * *** > uE; */
/* * ******************************************************************** */
/* * ***XuE(ii,jj,kk) = */
		tmp1_xue__ = -ops[ii + (jj + kk * ops_dim2) * ops_dim1] * (
			-ue[i__ + (jm1 + k * ue_dim2) * ue_dim1] * dpsw[iip1 
			+ (jj + kkp1 * dpsw_dim2) * dpsw_dim1] - une[i__ + (
			jm1 + k * une_dim2) * une_dim1] * dpw[iip1 + (jj + 
			kkp1 * dpw_dim2) * dpw_dim1]) - ups[ii + (jj + kk * 
			ups_dim2) * ups_dim1] * (-oe[i__ + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * dpsw[iip1 + (jj + kkp1 * 
			dpsw_dim2) * dpsw_dim1] - ue[i__ + (jm1 + kp1 * 
			ue_dim2) * ue_dim1] * opsw[iip1 + (jj + kkp1 * 
			opsw_dim2) * opsw_dim1] - one[i__ + (jm1 + kp1 * 
			one_dim2) * one_dim1] * dpw[iip1 + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - une[i__ + (jm1 + kp1 * 
			une_dim2) * une_dim1] * opw[iip1 + (jj + kkp1 * 
			opw_dim2) * opw_dim1]) - opc[ii + (jj + kk * opc_dim2)
			 * opc_dim1] * (-use[i__ + (j + k * use_dim2) * 
			use_dim1] * dpsw[iip1 + (jj + kkp1 * dpsw_dim2) * 
			dpsw_dim1] - ue[i__ + (j + k * ue_dim2) * ue_dim1] * 
			dpw[iip1 + (jj + kkp1 * dpw_dim2) * dpw_dim1] - une[
			i__ + (j + k * une_dim2) * une_dim1] * dpnw[iip1 + (
			jj + kkp1 * dpnw_dim2) * dpnw_dim1]);
		tmp2_xue__ = -upc[ii + (jj + kk * upc_dim2) * upc_dim1] * (
			-onw[ip1 + (jm1 + kp1 * onw_dim2) * onw_dim1] * dpsw[
			iip1 + (jj + kkp1 * dpsw_dim2) * dpsw_dim1] - use[i__ 
			+ (j + kp1 * use_dim2) * use_dim1] * opsw[iip1 + (jj 
			+ kkp1 * opsw_dim2) * opsw_dim1] - oe[i__ + (j + kp1 *
			 oe_dim2) * oe_dim1] * dpw[iip1 + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - ue[i__ + (j + kp1 * ue_dim2) *
			 ue_dim1] * opw[iip1 + (jj + kkp1 * opw_dim2) * 
			opw_dim1] - one[i__ + (j + kp1 * one_dim2) * one_dim1]
			 * dpnw[iip1 + (jj + kkp1 * dpnw_dim2) * dpnw_dim1] - 
			une[i__ + (j + kp1 * une_dim2) * une_dim1] * opnw[
			iip1 + (jj + kkp1 * opnw_dim2) * opnw_dim1]) - opn[ii 
			+ (jj + kk * opn_dim2) * opn_dim1] * (-use[i__ + (jp1 
			+ k * use_dim2) * use_dim1] * dpw[iip1 + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - ue[i__ + (jp1 + k * ue_dim2) *
			 ue_dim1] * dpnw[iip1 + (jj + kkp1 * dpnw_dim2) * 
			dpnw_dim1]) - upn[ii + (jj + kk * upn_dim2) * 
			upn_dim1] * (-onw[ip1 + (j + kp1 * onw_dim2) * 
			onw_dim1] * dpw[iip1 + (jj + kkp1 * dpw_dim2) * 
			dpw_dim1] - use[i__ + (jp1 + kp1 * use_dim2) * 
			use_dim1] * opw[iip1 + (jj + kkp1 * opw_dim2) * 
			opw_dim1] - oe[i__ + (jp1 + kp1 * oe_dim2) * oe_dim1] 
			* dpnw[iip1 + (jj + kkp1 * dpnw_dim2) * dpnw_dim1] - 
			ue[i__ + (jp1 + kp1 * ue_dim2) * ue_dim1] * opnw[iip1 
			+ (jj + kkp1 * opnw_dim2) * opnw_dim1]);
		tmp3_xue__ = -opse[ii + (jj + kk * opse_dim2) * opse_dim1] * (
			-uc[ip1 + (jm1 + k * uc_dim2) * uc_dim1] * dpsw[iip1 
			+ (jj + kkp1 * dpsw_dim2) * dpsw_dim1] - un[ip1 + (
			jm1 + k * un_dim2) * un_dim1] * dpw[iip1 + (jj + kkp1 
			* dpw_dim2) * dpw_dim1] - ue[ip1 + (jm1 + k * ue_dim2)
			 * ue_dim1] * dps[iip1 + (jj + kkp1 * dps_dim2) * 
			dps_dim1] - une[ip1 + (jm1 + k * une_dim2) * une_dim1]
			 * dpc[iip1 + (jj + kkp1 * dpc_dim2) * dpc_dim1]) - 
			upse[ii + (jj + kk * upse_dim2) * upse_dim1] * (oc[
			ip1 + (jm1 + kp1 * oc_dim2) * oc_dim1] * dpsw[iip1 + (
			jj + kkp1 * dpsw_dim2) * dpsw_dim1] - uc[ip1 + (jm1 + 
			kp1 * uc_dim2) * uc_dim1] * opsw[iip1 + (jj + kkp1 * 
			opsw_dim2) * opsw_dim1] - on[ip1 + (jm1 + kp1 * 
			on_dim2) * on_dim1] * dpw[iip1 + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - un[ip1 + (jm1 + kp1 * un_dim2)
			 * un_dim1] * opw[iip1 + (jj + kkp1 * opw_dim2) * 
			opw_dim1] - oe[ip1 + (jm1 + kp1 * oe_dim2) * oe_dim1] 
			* dps[iip1 + (jj + kkp1 * dps_dim2) * dps_dim1] - ue[
			ip1 + (jm1 + kp1 * ue_dim2) * ue_dim1] * ops[iip1 + (
			jj + kkp1 * ops_dim2) * ops_dim1] - one[ip1 + (jm1 + 
			kp1 * one_dim2) * one_dim1] * dpc[iip1 + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - une[ip1 + (jm1 + kp1 * 
			une_dim2) * une_dim1] * opc[iip1 + (jj + kkp1 * 
			opc_dim2) * opc_dim1]);
		tmp4_xue__ = -ope[ii + (jj + kk * ope_dim2) * ope_dim1] * (
			-us[ip1 + (j + k * us_dim2) * us_dim1] * dpsw[iip1 + (
			jj + kkp1 * dpsw_dim2) * dpsw_dim1] - uc[ip1 + (j + k 
			* uc_dim2) * uc_dim1] * dpw[iip1 + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - un[ip1 + (j + k * un_dim2) * 
			un_dim1] * dpnw[iip1 + (jj + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - use[ip1 + (j + k * use_dim2) * use_dim1] 
			* dps[iip1 + (jj + kkp1 * dps_dim2) * dps_dim1] - ue[
			ip1 + (j + k * ue_dim2) * ue_dim1] * dpc[iip1 + (jj + 
			kkp1 * dpc_dim2) * dpc_dim1] - une[ip1 + (j + k * 
			une_dim2) * une_dim1] * dpn[iip1 + (jj + kkp1 * 
			dpn_dim2) * dpn_dim1]);
		tmp5_xue__ = -upe[ii + (jj + kk * upe_dim2) * upe_dim1] * (
			-on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1] * dpsw[
			iip1 + (jj + kkp1 * dpsw_dim2) * dpsw_dim1] - us[ip1 
			+ (j + kp1 * us_dim2) * us_dim1] * opsw[iip1 + (jj + 
			kkp1 * opsw_dim2) * opsw_dim1] + oc[ip1 + (j + kp1 * 
			oc_dim2) * oc_dim1] * dpw[iip1 + (jj + kkp1 * 
			dpw_dim2) * dpw_dim1] - uc[ip1 + (j + kp1 * uc_dim2) *
			 uc_dim1] * opw[iip1 + (jj + kkp1 * opw_dim2) * 
			opw_dim1] - on[ip1 + (j + kp1 * on_dim2) * on_dim1] * 
			dpnw[iip1 + (jj + kkp1 * dpnw_dim2) * dpnw_dim1] - un[
			ip1 + (j + kp1 * un_dim2) * un_dim1] * opnw[iip1 + (
			jj + kkp1 * opnw_dim2) * opnw_dim1] - onw[ip2 + (jm1 
			+ kp1 * onw_dim2) * onw_dim1] * dps[iip1 + (jj + kkp1 
			* dps_dim2) * dps_dim1] - use[ip1 + (j + kp1 * 
			use_dim2) * use_dim1] * ops[iip1 + (jj + kkp1 * 
			ops_dim2) * ops_dim1] - oe[ip1 + (j + kp1 * oe_dim2) *
			 oe_dim1] * dpc[iip1 + (jj + kkp1 * dpc_dim2) * 
			dpc_dim1] - ue[ip1 + (j + kp1 * ue_dim2) * ue_dim1] * 
			opc[iip1 + (jj + kkp1 * opc_dim2) * opc_dim1] - one[
			ip1 + (j + kp1 * one_dim2) * one_dim1] * dpn[iip1 + (
			jj + kkp1 * dpn_dim2) * dpn_dim1] - une[ip1 + (j + 
			kp1 * une_dim2) * une_dim1] * opn[iip1 + (jj + kkp1 * 
			opn_dim2) * opn_dim1]);
		tmp6_xue__ = -opne[ii + (jj + kk * opne_dim2) * opne_dim1] * (
			-us[ip1 + (jp1 + k * us_dim2) * us_dim1] * dpw[iip1 + 
			(jj + kkp1 * dpw_dim2) * dpw_dim1] - uc[ip1 + (jp1 + 
			k * uc_dim2) * uc_dim1] * dpnw[iip1 + (jj + kkp1 * 
			dpnw_dim2) * dpnw_dim1] - use[ip1 + (jp1 + k * 
			use_dim2) * use_dim1] * dpc[iip1 + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - ue[ip1 + (jp1 + k * ue_dim2) *
			 ue_dim1] * dpn[iip1 + (jj + kkp1 * dpn_dim2) * 
			dpn_dim1]) - upne[ii + (jj + kk * upne_dim2) * 
			upne_dim1] * (-on[ip1 + (j + kp1 * on_dim2) * on_dim1]
			 * dpw[iip1 + (jj + kkp1 * dpw_dim2) * dpw_dim1] - us[
			ip1 + (jp1 + kp1 * us_dim2) * us_dim1] * opw[iip1 + (
			jj + kkp1 * opw_dim2) * opw_dim1] + oc[ip1 + (jp1 + 
			kp1 * oc_dim2) * oc_dim1] * dpnw[iip1 + (jj + kkp1 * 
			dpnw_dim2) * dpnw_dim1] - uc[ip1 + (jp1 + kp1 * 
			uc_dim2) * uc_dim1] * opnw[iip1 + (jj + kkp1 * 
			opnw_dim2) * opnw_dim1] - onw[ip2 + (j + kp1 * 
			onw_dim2) * onw_dim1] * dpc[iip1 + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - use[ip1 + (jp1 + kp1 * 
			use_dim2) * use_dim1] * opc[iip1 + (jj + kkp1 * 
			opc_dim2) * opc_dim1] - oe[ip1 + (jp1 + kp1 * oe_dim2)
			 * oe_dim1] * dpn[iip1 + (jj + kkp1 * dpn_dim2) * 
			dpn_dim1] - ue[ip1 + (jp1 + kp1 * ue_dim2) * ue_dim1] 
			* opn[iip1 + (jj + kkp1 * opn_dim2) * opn_dim1]);
		xue[ii + (jj + kk * xue_dim2) * xue_dim1] = tmp1_xue__ + 
			tmp2_xue__ + tmp3_xue__ + tmp4_xue__ + tmp5_xue__ + 
			tmp6_xue__;
/* * ******************************************************************** */
/* * *** > uW; */
/* * ******************************************************************** */
/* * ***XuW(ii,jj,kk) = */
		tmp1_xuw__ = -opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] * (
			-uw[im1 + (jm1 + k * uw_dim2) * uw_dim1] * dps[iim1 + 
			(jj + kkp1 * dps_dim2) * dps_dim1] - unw[im1 + (jm1 + 
			k * unw_dim2) * unw_dim1] * dpc[iim1 + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - uc[im1 + (jm1 + k * uc_dim2) *
			 uc_dim1] * dpse[iim1 + (jj + kkp1 * dpse_dim2) * 
			dpse_dim1] - un[im1 + (jm1 + k * un_dim2) * un_dim1] *
			 dpe[iim1 + (jj + kkp1 * dpe_dim2) * dpe_dim1]) - 
			upsw[ii + (jj + kk * upsw_dim2) * upsw_dim1] * (-oe[
			im2 + (jm1 + kp1 * oe_dim2) * oe_dim1] * dps[iim1 + (
			jj + kkp1 * dps_dim2) * dps_dim1] - uw[im1 + (jm1 + 
			kp1 * uw_dim2) * uw_dim1] * ops[iim1 + (jj + kkp1 * 
			ops_dim2) * ops_dim1] - onw[im1 + (jm1 + kp1 * 
			onw_dim2) * onw_dim1] * dpc[iim1 + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - unw[im1 + (jm1 + kp1 * 
			unw_dim2) * unw_dim1] * opc[iim1 + (jj + kkp1 * 
			opc_dim2) * opc_dim1] + oc[im1 + (jm1 + kp1 * oc_dim2)
			 * oc_dim1] * dpse[iim1 + (jj + kkp1 * dpse_dim2) * 
			dpse_dim1] - uc[im1 + (jm1 + kp1 * uc_dim2) * uc_dim1]
			 * opse[iim1 + (jj + kkp1 * opse_dim2) * opse_dim1] - 
			on[im1 + (jm1 + kp1 * on_dim2) * on_dim1] * dpe[iim1 
			+ (jj + kkp1 * dpe_dim2) * dpe_dim1] - un[im1 + (jm1 
			+ kp1 * un_dim2) * un_dim1] * ope[iim1 + (jj + kkp1 * 
			ope_dim2) * ope_dim1]);
		tmp2_xuw__ = -opw[ii + (jj + kk * opw_dim2) * opw_dim1] * (
			-usw[im1 + (j + k * usw_dim2) * usw_dim1] * dps[iim1 
			+ (jj + kkp1 * dps_dim2) * dps_dim1] - uw[im1 + (j + 
			k * uw_dim2) * uw_dim1] * dpc[iim1 + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - unw[im1 + (j + k * unw_dim2) *
			 unw_dim1] * dpn[iim1 + (jj + kkp1 * dpn_dim2) * 
			dpn_dim1] - us[im1 + (j + k * us_dim2) * us_dim1] * 
			dpse[iim1 + (jj + kkp1 * dpse_dim2) * dpse_dim1] - uc[
			im1 + (j + k * uc_dim2) * uc_dim1] * dpe[iim1 + (jj + 
			kkp1 * dpe_dim2) * dpe_dim1] - un[im1 + (j + k * 
			un_dim2) * un_dim1] * dpne[iim1 + (jj + kkp1 * 
			dpne_dim2) * dpne_dim1]);
		tmp3_xuw__ = -upw[ii + (jj + kk * upw_dim2) * upw_dim1] * (
			-one[im2 + (jm1 + kp1 * one_dim2) * one_dim1] * dps[
			iim1 + (jj + kkp1 * dps_dim2) * dps_dim1] - usw[im1 + 
			(j + kp1 * usw_dim2) * usw_dim1] * ops[iim1 + (jj + 
			kkp1 * ops_dim2) * ops_dim1] - oe[im2 + (j + kp1 * 
			oe_dim2) * oe_dim1] * dpc[iim1 + (jj + kkp1 * 
			dpc_dim2) * dpc_dim1] - uw[im1 + (j + kp1 * uw_dim2) *
			 uw_dim1] * opc[iim1 + (jj + kkp1 * opc_dim2) * 
			opc_dim1] - onw[im1 + (j + kp1 * onw_dim2) * onw_dim1]
			 * dpn[iim1 + (jj + kkp1 * dpn_dim2) * dpn_dim1] - 
			unw[im1 + (j + kp1 * unw_dim2) * unw_dim1] * opn[iim1 
			+ (jj + kkp1 * opn_dim2) * opn_dim1] - on[im1 + (jm1 
			+ kp1 * on_dim2) * on_dim1] * dpse[iim1 + (jj + kkp1 *
			 dpse_dim2) * dpse_dim1] - us[im1 + (j + kp1 * 
			us_dim2) * us_dim1] * opse[iim1 + (jj + kkp1 * 
			opse_dim2) * opse_dim1] + oc[im1 + (j + kp1 * oc_dim2)
			 * oc_dim1] * dpe[iim1 + (jj + kkp1 * dpe_dim2) * 
			dpe_dim1] - uc[im1 + (j + kp1 * uc_dim2) * uc_dim1] * 
			ope[iim1 + (jj + kkp1 * ope_dim2) * ope_dim1] - on[
			im1 + (j + kp1 * on_dim2) * on_dim1] * dpne[iim1 + (
			jj + kkp1 * dpne_dim2) * dpne_dim1] - un[im1 + (j + 
			kp1 * un_dim2) * un_dim1] * opne[iim1 + (jj + kkp1 * 
			opne_dim2) * opne_dim1]);
		tmp4_xuw__ = -opnw[ii + (jj + kk * opnw_dim2) * opnw_dim1] * (
			-usw[im1 + (jp1 + k * usw_dim2) * usw_dim1] * dpc[
			iim1 + (jj + kkp1 * dpc_dim2) * dpc_dim1] - uw[im1 + (
			jp1 + k * uw_dim2) * uw_dim1] * dpn[iim1 + (jj + kkp1 
			* dpn_dim2) * dpn_dim1] - us[im1 + (jp1 + k * us_dim2)
			 * us_dim1] * dpe[iim1 + (jj + kkp1 * dpe_dim2) * 
			dpe_dim1] - uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] * 
			dpne[iim1 + (jj + kkp1 * dpne_dim2) * dpne_dim1]) - 
			upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * (-one[
			im2 + (j + kp1 * one_dim2) * one_dim1] * dpc[iim1 + (
			jj + kkp1 * dpc_dim2) * dpc_dim1] - usw[im1 + (jp1 + 
			kp1 * usw_dim2) * usw_dim1] * opc[iim1 + (jj + kkp1 * 
			opc_dim2) * opc_dim1] - oe[im2 + (jp1 + kp1 * oe_dim2)
			 * oe_dim1] * dpn[iim1 + (jj + kkp1 * dpn_dim2) * 
			dpn_dim1] - uw[im1 + (jp1 + kp1 * uw_dim2) * uw_dim1] 
			* opn[iim1 + (jj + kkp1 * opn_dim2) * opn_dim1] - on[
			im1 + (j + kp1 * on_dim2) * on_dim1] * dpe[iim1 + (jj 
			+ kkp1 * dpe_dim2) * dpe_dim1] - us[im1 + (jp1 + kp1 *
			 us_dim2) * us_dim1] * ope[iim1 + (jj + kkp1 * 
			ope_dim2) * ope_dim1] + oc[im1 + (jp1 + kp1 * oc_dim2)
			 * oc_dim1] * dpne[iim1 + (jj + kkp1 * dpne_dim2) * 
			dpne_dim1] - uc[im1 + (jp1 + kp1 * uc_dim2) * uc_dim1]
			 * opne[iim1 + (jj + kkp1 * opne_dim2) * opne_dim1]);
		tmp5_xuw__ = -ops[ii + (jj + kk * ops_dim2) * ops_dim1] * (
			-uw[i__ + (jm1 + k * uw_dim2) * uw_dim1] * dpse[iim1 
			+ (jj + kkp1 * dpse_dim2) * dpse_dim1] - unw[i__ + (
			jm1 + k * unw_dim2) * unw_dim1] * dpe[iim1 + (jj + 
			kkp1 * dpe_dim2) * dpe_dim1]) - ups[ii + (jj + kk * 
			ups_dim2) * ups_dim1] * (-oe[im1 + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * dpse[iim1 + (jj + kkp1 * 
			dpse_dim2) * dpse_dim1] - uw[i__ + (jm1 + kp1 * 
			uw_dim2) * uw_dim1] * opse[iim1 + (jj + kkp1 * 
			opse_dim2) * opse_dim1] - onw[i__ + (jm1 + kp1 * 
			onw_dim2) * onw_dim1] * dpe[iim1 + (jj + kkp1 * 
			dpe_dim2) * dpe_dim1] - unw[i__ + (jm1 + kp1 * 
			unw_dim2) * unw_dim1] * ope[iim1 + (jj + kkp1 * 
			ope_dim2) * ope_dim1]) - opc[ii + (jj + kk * opc_dim2)
			 * opc_dim1] * (-usw[i__ + (j + k * usw_dim2) * 
			usw_dim1] * dpse[iim1 + (jj + kkp1 * dpse_dim2) * 
			dpse_dim1] - uw[i__ + (j + k * uw_dim2) * uw_dim1] * 
			dpe[iim1 + (jj + kkp1 * dpe_dim2) * dpe_dim1] - unw[
			i__ + (j + k * unw_dim2) * unw_dim1] * dpne[iim1 + (
			jj + kkp1 * dpne_dim2) * dpne_dim1]);
		tmp6_xuw__ = -upc[ii + (jj + kk * upc_dim2) * upc_dim1] * (
			-one[im1 + (jm1 + kp1 * one_dim2) * one_dim1] * dpse[
			iim1 + (jj + kkp1 * dpse_dim2) * dpse_dim1] - usw[i__ 
			+ (j + kp1 * usw_dim2) * usw_dim1] * opse[iim1 + (jj 
			+ kkp1 * opse_dim2) * opse_dim1] - oe[im1 + (j + kp1 *
			 oe_dim2) * oe_dim1] * dpe[iim1 + (jj + kkp1 * 
			dpe_dim2) * dpe_dim1] - uw[i__ + (j + kp1 * uw_dim2) *
			 uw_dim1] * ope[iim1 + (jj + kkp1 * ope_dim2) * 
			ope_dim1] - onw[i__ + (j + kp1 * onw_dim2) * onw_dim1]
			 * dpne[iim1 + (jj + kkp1 * dpne_dim2) * dpne_dim1] - 
			unw[i__ + (j + kp1 * unw_dim2) * unw_dim1] * opne[
			iim1 + (jj + kkp1 * opne_dim2) * opne_dim1]) - opn[ii 
			+ (jj + kk * opn_dim2) * opn_dim1] * (-usw[i__ + (jp1 
			+ k * usw_dim2) * usw_dim1] * dpe[iim1 + (jj + kkp1 * 
			dpe_dim2) * dpe_dim1] - uw[i__ + (jp1 + k * uw_dim2) *
			 uw_dim1] * dpne[iim1 + (jj + kkp1 * dpne_dim2) * 
			dpne_dim1]) - upn[ii + (jj + kk * upn_dim2) * 
			upn_dim1] * (-one[im1 + (j + kp1 * one_dim2) * 
			one_dim1] * dpe[iim1 + (jj + kkp1 * dpe_dim2) * 
			dpe_dim1] - usw[i__ + (jp1 + kp1 * usw_dim2) * 
			usw_dim1] * ope[iim1 + (jj + kkp1 * ope_dim2) * 
			ope_dim1] - oe[im1 + (jp1 + kp1 * oe_dim2) * oe_dim1] 
			* dpne[iim1 + (jj + kkp1 * dpne_dim2) * dpne_dim1] - 
			uw[i__ + (jp1 + kp1 * uw_dim2) * uw_dim1] * opne[iim1 
			+ (jj + kkp1 * opne_dim2) * opne_dim1]);
		xuw[ii + (jj + kk * xuw_dim2) * xuw_dim1] = tmp1_xuw__ + 
			tmp2_xuw__ + tmp3_xuw__ + tmp4_xuw__ + tmp5_xuw__ + 
			tmp6_xuw__;
/* * ******************************************************************** */
/* * *** > uN; */
/* * ******************************************************************** */
/* * ***XuN(ii,jj,kk) = */
		tmp1_xun__ = -opw[ii + (jj + kk * opw_dim2) * opw_dim1] * (
			-un[im1 + (j + k * un_dim2) * un_dim1] * dpsw[ii + (
			jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - une[im1 + (j 
			+ k * une_dim2) * une_dim1] * dps[ii + (jjp1 + kkp1 * 
			dps_dim2) * dps_dim1]) - upw[ii + (jj + kk * upw_dim2)
			 * upw_dim1] * (-on[im1 + (j + kp1 * on_dim2) * 
			on_dim1] * dpsw[ii + (jjp1 + kkp1 * dpsw_dim2) * 
			dpsw_dim1] - un[im1 + (j + kp1 * un_dim2) * un_dim1] *
			 opsw[ii + (jjp1 + kkp1 * opsw_dim2) * opsw_dim1] - 
			one[im1 + (j + kp1 * one_dim2) * one_dim1] * dps[ii + 
			(jjp1 + kkp1 * dps_dim2) * dps_dim1] - une[im1 + (j + 
			kp1 * une_dim2) * une_dim1] * ops[ii + (jjp1 + kkp1 * 
			ops_dim2) * ops_dim1]) - opnw[ii + (jj + kk * 
			opnw_dim2) * opnw_dim1] * (-uc[im1 + (jp1 + k * 
			uc_dim2) * uc_dim1] * dpsw[ii + (jjp1 + kkp1 * 
			dpsw_dim2) * dpsw_dim1] - un[im1 + (jp1 + k * un_dim2)
			 * un_dim1] * dpw[ii + (jjp1 + kkp1 * dpw_dim2) * 
			dpw_dim1] - ue[im1 + (jp1 + k * ue_dim2) * ue_dim1] * 
			dps[ii + (jjp1 + kkp1 * dps_dim2) * dps_dim1] - une[
			im1 + (jp1 + k * une_dim2) * une_dim1] * dpc[ii + (
			jjp1 + kkp1 * dpc_dim2) * dpc_dim1]);
		tmp2_xun__ = -upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * (
			oc[im1 + (jp1 + kp1 * oc_dim2) * oc_dim1] * dpsw[ii + 
			(jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - uc[im1 + (
			jp1 + kp1 * uc_dim2) * uc_dim1] * opsw[ii + (jjp1 + 
			kkp1 * opsw_dim2) * opsw_dim1] - on[im1 + (jp1 + kp1 *
			 on_dim2) * on_dim1] * dpw[ii + (jjp1 + kkp1 * 
			dpw_dim2) * dpw_dim1] - un[im1 + (jp1 + kp1 * un_dim2)
			 * un_dim1] * opw[ii + (jjp1 + kkp1 * opw_dim2) * 
			opw_dim1] - oe[im1 + (jp1 + kp1 * oe_dim2) * oe_dim1] 
			* dps[ii + (jjp1 + kkp1 * dps_dim2) * dps_dim1] - ue[
			im1 + (jp1 + kp1 * ue_dim2) * ue_dim1] * ops[ii + (
			jjp1 + kkp1 * ops_dim2) * ops_dim1] - one[im1 + (jp1 
			+ kp1 * one_dim2) * one_dim1] * dpc[ii + (jjp1 + kkp1 
			* dpc_dim2) * dpc_dim1] - une[im1 + (jp1 + kp1 * 
			une_dim2) * une_dim1] * opc[ii + (jjp1 + kkp1 * 
			opc_dim2) * opc_dim1]) - opc[ii + (jj + kk * opc_dim2)
			 * opc_dim1] * (-unw[i__ + (j + k * unw_dim2) * 
			unw_dim1] * dpsw[ii + (jjp1 + kkp1 * dpsw_dim2) * 
			dpsw_dim1] - un[i__ + (j + k * un_dim2) * un_dim1] * 
			dps[ii + (jjp1 + kkp1 * dps_dim2) * dps_dim1] - une[
			i__ + (j + k * une_dim2) * une_dim1] * dpse[ii + (
			jjp1 + kkp1 * dpse_dim2) * dpse_dim1]);
		tmp3_xun__ = -upc[ii + (jj + kk * upc_dim2) * upc_dim1] * (
			-onw[i__ + (j + kp1 * onw_dim2) * onw_dim1] * dpsw[ii 
			+ (jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - unw[i__ + (
			j + kp1 * unw_dim2) * unw_dim1] * opsw[ii + (jjp1 + 
			kkp1 * opsw_dim2) * opsw_dim1] - on[i__ + (j + kp1 * 
			on_dim2) * on_dim1] * dps[ii + (jjp1 + kkp1 * 
			dps_dim2) * dps_dim1] - un[i__ + (j + kp1 * un_dim2) *
			 un_dim1] * ops[ii + (jjp1 + kkp1 * ops_dim2) * 
			ops_dim1] - one[i__ + (j + kp1 * one_dim2) * one_dim1]
			 * dpse[ii + (jjp1 + kkp1 * dpse_dim2) * dpse_dim1] - 
			une[i__ + (j + kp1 * une_dim2) * une_dim1] * opse[ii 
			+ (jjp1 + kkp1 * opse_dim2) * opse_dim1]) - opn[ii + (
			jj + kk * opn_dim2) * opn_dim1] * (-uw[i__ + (jp1 + k 
			* uw_dim2) * uw_dim1] * dpsw[ii + (jjp1 + kkp1 * 
			dpsw_dim2) * dpsw_dim1] - unw[i__ + (jp1 + k * 
			unw_dim2) * unw_dim1] * dpw[ii + (jjp1 + kkp1 * 
			dpw_dim2) * dpw_dim1] - uc[i__ + (jp1 + k * uc_dim2) *
			 uc_dim1] * dps[ii + (jjp1 + kkp1 * dps_dim2) * 
			dps_dim1] - un[i__ + (jp1 + k * un_dim2) * un_dim1] * 
			dpc[ii + (jjp1 + kkp1 * dpc_dim2) * dpc_dim1] - ue[
			i__ + (jp1 + k * ue_dim2) * ue_dim1] * dpse[ii + (
			jjp1 + kkp1 * dpse_dim2) * dpse_dim1] - une[i__ + (
			jp1 + k * une_dim2) * une_dim1] * dpe[ii + (jjp1 + 
			kkp1 * dpe_dim2) * dpe_dim1]);
		tmp4_xun__ = -upn[ii + (jj + kk * upn_dim2) * upn_dim1] * (
			-oe[im1 + (jp1 + kp1 * oe_dim2) * oe_dim1] * dpsw[ii 
			+ (jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - uw[i__ + (
			jp1 + kp1 * uw_dim2) * uw_dim1] * opsw[ii + (jjp1 + 
			kkp1 * opsw_dim2) * opsw_dim1] - onw[i__ + (jp1 + kp1 
			* onw_dim2) * onw_dim1] * dpw[ii + (jjp1 + kkp1 * 
			dpw_dim2) * dpw_dim1] - unw[i__ + (jp1 + kp1 * 
			unw_dim2) * unw_dim1] * opw[ii + (jjp1 + kkp1 * 
			opw_dim2) * opw_dim1] + oc[i__ + (jp1 + kp1 * oc_dim2)
			 * oc_dim1] * dps[ii + (jjp1 + kkp1 * dps_dim2) * 
			dps_dim1] - uc[i__ + (jp1 + kp1 * uc_dim2) * uc_dim1] 
			* ops[ii + (jjp1 + kkp1 * ops_dim2) * ops_dim1] - on[
			i__ + (jp1 + kp1 * on_dim2) * on_dim1] * dpc[ii + (
			jjp1 + kkp1 * dpc_dim2) * dpc_dim1] - un[i__ + (jp1 + 
			kp1 * un_dim2) * un_dim1] * opc[ii + (jjp1 + kkp1 * 
			opc_dim2) * opc_dim1] - oe[i__ + (jp1 + kp1 * oe_dim2)
			 * oe_dim1] * dpse[ii + (jjp1 + kkp1 * dpse_dim2) * 
			dpse_dim1] - ue[i__ + (jp1 + kp1 * ue_dim2) * ue_dim1]
			 * opse[ii + (jjp1 + kkp1 * opse_dim2) * opse_dim1] - 
			one[i__ + (jp1 + kp1 * one_dim2) * one_dim1] * dpe[ii 
			+ (jjp1 + kkp1 * dpe_dim2) * dpe_dim1] - une[i__ + (
			jp1 + kp1 * une_dim2) * une_dim1] * ope[ii + (jjp1 + 
			kkp1 * ope_dim2) * ope_dim1]);
		tmp5_xun__ = -ope[ii + (jj + kk * ope_dim2) * ope_dim1] * (
			-unw[ip1 + (j + k * unw_dim2) * unw_dim1] * dps[ii + (
			jjp1 + kkp1 * dps_dim2) * dps_dim1] - un[ip1 + (j + k 
			* un_dim2) * un_dim1] * dpse[ii + (jjp1 + kkp1 * 
			dpse_dim2) * dpse_dim1]) - upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1] * (-onw[ip1 + (j + kp1 * 
			onw_dim2) * onw_dim1] * dps[ii + (jjp1 + kkp1 * 
			dps_dim2) * dps_dim1] - unw[ip1 + (j + kp1 * unw_dim2)
			 * unw_dim1] * ops[ii + (jjp1 + kkp1 * ops_dim2) * 
			ops_dim1] - on[ip1 + (j + kp1 * on_dim2) * on_dim1] * 
			dpse[ii + (jjp1 + kkp1 * dpse_dim2) * dpse_dim1] - un[
			ip1 + (j + kp1 * un_dim2) * un_dim1] * opse[ii + (
			jjp1 + kkp1 * opse_dim2) * opse_dim1]) - opne[ii + (
			jj + kk * opne_dim2) * opne_dim1] * (-uw[ip1 + (jp1 + 
			k * uw_dim2) * uw_dim1] * dps[ii + (jjp1 + kkp1 * 
			dps_dim2) * dps_dim1] - unw[ip1 + (jp1 + k * unw_dim2)
			 * unw_dim1] * dpc[ii + (jjp1 + kkp1 * dpc_dim2) * 
			dpc_dim1] - uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1] * 
			dpse[ii + (jjp1 + kkp1 * dpse_dim2) * dpse_dim1] - un[
			ip1 + (jp1 + k * un_dim2) * un_dim1] * dpe[ii + (jjp1 
			+ kkp1 * dpe_dim2) * dpe_dim1]);
		tmp6_xun__ = -upne[ii + (jj + kk * upne_dim2) * upne_dim1] * (
			-oe[i__ + (jp1 + kp1 * oe_dim2) * oe_dim1] * dps[ii + 
			(jjp1 + kkp1 * dps_dim2) * dps_dim1] - uw[ip1 + (jp1 
			+ kp1 * uw_dim2) * uw_dim1] * ops[ii + (jjp1 + kkp1 * 
			ops_dim2) * ops_dim1] - onw[ip1 + (jp1 + kp1 * 
			onw_dim2) * onw_dim1] * dpc[ii + (jjp1 + kkp1 * 
			dpc_dim2) * dpc_dim1] - unw[ip1 + (jp1 + kp1 * 
			unw_dim2) * unw_dim1] * opc[ii + (jjp1 + kkp1 * 
			opc_dim2) * opc_dim1] + oc[ip1 + (jp1 + kp1 * oc_dim2)
			 * oc_dim1] * dpse[ii + (jjp1 + kkp1 * dpse_dim2) * 
			dpse_dim1] - uc[ip1 + (jp1 + kp1 * uc_dim2) * uc_dim1]
			 * opse[ii + (jjp1 + kkp1 * opse_dim2) * opse_dim1] - 
			on[ip1 + (jp1 + kp1 * on_dim2) * on_dim1] * dpe[ii + (
			jjp1 + kkp1 * dpe_dim2) * dpe_dim1] - un[ip1 + (jp1 + 
			kp1 * un_dim2) * un_dim1] * ope[ii + (jjp1 + kkp1 * 
			ope_dim2) * ope_dim1]);
		xun[ii + (jj + kk * xun_dim2) * xun_dim1] = tmp1_xun__ + 
			tmp2_xun__ + tmp3_xun__ + tmp4_xun__ + tmp5_xun__ + 
			tmp6_xun__;
/* * ******************************************************************** */
/* * *** > uS; */
/* * ******************************************************************** */
/* * ***XuS(ii,jj,kk) = */
		tmp1_xus__ = -opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] * (
			-us[im1 + (jm1 + k * us_dim2) * us_dim1] * dpw[ii + (
			jjm1 + kkp1 * dpw_dim2) * dpw_dim1] - uc[im1 + (jm1 + 
			k * uc_dim2) * uc_dim1] * dpnw[ii + (jjm1 + kkp1 * 
			dpnw_dim2) * dpnw_dim1] - use[im1 + (jm1 + k * 
			use_dim2) * use_dim1] * dpc[ii + (jjm1 + kkp1 * 
			dpc_dim2) * dpc_dim1] - ue[im1 + (jm1 + k * ue_dim2) *
			 ue_dim1] * dpn[ii + (jjm1 + kkp1 * dpn_dim2) * 
			dpn_dim1]) - upsw[ii + (jj + kk * upsw_dim2) * 
			upsw_dim1] * (-on[im1 + (jm2 + kp1 * on_dim2) * 
			on_dim1] * dpw[ii + (jjm1 + kkp1 * dpw_dim2) * 
			dpw_dim1] - us[im1 + (jm1 + kp1 * us_dim2) * us_dim1] 
			* opw[ii + (jjm1 + kkp1 * opw_dim2) * opw_dim1] + oc[
			im1 + (jm1 + kp1 * oc_dim2) * oc_dim1] * dpnw[ii + (
			jjm1 + kkp1 * dpnw_dim2) * dpnw_dim1] - uc[im1 + (jm1 
			+ kp1 * uc_dim2) * uc_dim1] * opnw[ii + (jjm1 + kkp1 *
			 opnw_dim2) * opnw_dim1] - onw[i__ + (jm2 + kp1 * 
			onw_dim2) * onw_dim1] * dpc[ii + (jjm1 + kkp1 * 
			dpc_dim2) * dpc_dim1] - use[im1 + (jm1 + kp1 * 
			use_dim2) * use_dim1] * opc[ii + (jjm1 + kkp1 * 
			opc_dim2) * opc_dim1] - oe[im1 + (jm1 + kp1 * oe_dim2)
			 * oe_dim1] * dpn[ii + (jjm1 + kkp1 * dpn_dim2) * 
			dpn_dim1] - ue[im1 + (jm1 + kp1 * ue_dim2) * ue_dim1] 
			* opn[ii + (jjm1 + kkp1 * opn_dim2) * opn_dim1]);
		tmp2_xus__ = -opw[ii + (jj + kk * opw_dim2) * opw_dim1] * (
			-us[im1 + (j + k * us_dim2) * us_dim1] * dpnw[ii + (
			jjm1 + kkp1 * dpnw_dim2) * dpnw_dim1] - use[im1 + (j 
			+ k * use_dim2) * use_dim1] * dpn[ii + (jjm1 + kkp1 * 
			dpn_dim2) * dpn_dim1]) - upw[ii + (jj + kk * upw_dim2)
			 * upw_dim1] * (-on[im1 + (jm1 + kp1 * on_dim2) * 
			on_dim1] * dpnw[ii + (jjm1 + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - us[im1 + (j + kp1 * us_dim2) * us_dim1] *
			 opnw[ii + (jjm1 + kkp1 * opnw_dim2) * opnw_dim1] - 
			onw[i__ + (jm1 + kp1 * onw_dim2) * onw_dim1] * dpn[ii 
			+ (jjm1 + kkp1 * dpn_dim2) * dpn_dim1] - use[im1 + (j 
			+ kp1 * use_dim2) * use_dim1] * opn[ii + (jjm1 + kkp1 
			* opn_dim2) * opn_dim1]) - ops[ii + (jj + kk * 
			ops_dim2) * ops_dim1] * (-usw[i__ + (jm1 + k * 
			usw_dim2) * usw_dim1] * dpw[ii + (jjm1 + kkp1 * 
			dpw_dim2) * dpw_dim1] - uw[i__ + (jm1 + k * uw_dim2) *
			 uw_dim1] * dpnw[ii + (jjm1 + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - us[i__ + (jm1 + k * us_dim2) * us_dim1] *
			 dpc[ii + (jjm1 + kkp1 * dpc_dim2) * dpc_dim1] - uc[
			i__ + (jm1 + k * uc_dim2) * uc_dim1] * dpn[ii + (jjm1 
			+ kkp1 * dpn_dim2) * dpn_dim1] - use[i__ + (jm1 + k * 
			use_dim2) * use_dim1] * dpe[ii + (jjm1 + kkp1 * 
			dpe_dim2) * dpe_dim1] - ue[i__ + (jm1 + k * ue_dim2) *
			 ue_dim1] * dpne[ii + (jjm1 + kkp1 * dpne_dim2) * 
			dpne_dim1]);
		tmp3_xus__ = -ups[ii + (jj + kk * ups_dim2) * ups_dim1] * (
			-one[im1 + (jm2 + kp1 * one_dim2) * one_dim1] * dpw[
			ii + (jjm1 + kkp1 * dpw_dim2) * dpw_dim1] - usw[i__ + 
			(jm1 + kp1 * usw_dim2) * usw_dim1] * opw[ii + (jjm1 + 
			kkp1 * opw_dim2) * opw_dim1] - oe[im1 + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * dpnw[ii + (jjm1 + kkp1 * 
			dpnw_dim2) * dpnw_dim1] - uw[i__ + (jm1 + kp1 * 
			uw_dim2) * uw_dim1] * opnw[ii + (jjm1 + kkp1 * 
			opnw_dim2) * opnw_dim1] - on[i__ + (jm2 + kp1 * 
			on_dim2) * on_dim1] * dpc[ii + (jjm1 + kkp1 * 
			dpc_dim2) * dpc_dim1] - us[i__ + (jm1 + kp1 * us_dim2)
			 * us_dim1] * opc[ii + (jjm1 + kkp1 * opc_dim2) * 
			opc_dim1] + oc[i__ + (jm1 + kp1 * oc_dim2) * oc_dim1] 
			* dpn[ii + (jjm1 + kkp1 * dpn_dim2) * dpn_dim1] - uc[
			i__ + (jm1 + kp1 * uc_dim2) * uc_dim1] * opn[ii + (
			jjm1 + kkp1 * opn_dim2) * opn_dim1] - onw[ip1 + (jm2 
			+ kp1 * onw_dim2) * onw_dim1] * dpe[ii + (jjm1 + kkp1 
			* dpe_dim2) * dpe_dim1] - use[i__ + (jm1 + kp1 * 
			use_dim2) * use_dim1] * ope[ii + (jjm1 + kkp1 * 
			ope_dim2) * ope_dim1] - oe[i__ + (jm1 + kp1 * oe_dim2)
			 * oe_dim1] * dpne[ii + (jjm1 + kkp1 * dpne_dim2) * 
			dpne_dim1] - ue[i__ + (jm1 + kp1 * ue_dim2) * ue_dim1]
			 * opne[ii + (jjm1 + kkp1 * opne_dim2) * opne_dim1]);
		tmp4_xus__ = -opc[ii + (jj + kk * opc_dim2) * opc_dim1] * (
			-usw[i__ + (j + k * usw_dim2) * usw_dim1] * dpnw[ii + 
			(jjm1 + kkp1 * dpnw_dim2) * dpnw_dim1] - us[i__ + (j 
			+ k * us_dim2) * us_dim1] * dpn[ii + (jjm1 + kkp1 * 
			dpn_dim2) * dpn_dim1] - use[i__ + (j + k * use_dim2) *
			 use_dim1] * dpne[ii + (jjm1 + kkp1 * dpne_dim2) * 
			dpne_dim1]) - upc[ii + (jj + kk * upc_dim2) * 
			upc_dim1] * (-one[im1 + (jm1 + kp1 * one_dim2) * 
			one_dim1] * dpnw[ii + (jjm1 + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - usw[i__ + (j + kp1 * usw_dim2) * 
			usw_dim1] * opnw[ii + (jjm1 + kkp1 * opnw_dim2) * 
			opnw_dim1] - on[i__ + (jm1 + kp1 * on_dim2) * on_dim1]
			 * dpn[ii + (jjm1 + kkp1 * dpn_dim2) * dpn_dim1] - us[
			i__ + (j + kp1 * us_dim2) * us_dim1] * opn[ii + (jjm1 
			+ kkp1 * opn_dim2) * opn_dim1] - onw[ip1 + (jm1 + kp1 
			* onw_dim2) * onw_dim1] * dpne[ii + (jjm1 + kkp1 * 
			dpne_dim2) * dpne_dim1] - use[i__ + (j + kp1 * 
			use_dim2) * use_dim1] * opne[ii + (jjm1 + kkp1 * 
			opne_dim2) * opne_dim1]);
		tmp5_xus__ = -opse[ii + (jj + kk * opse_dim2) * opse_dim1] * (
			-usw[ip1 + (jm1 + k * usw_dim2) * usw_dim1] * dpc[ii 
			+ (jjm1 + kkp1 * dpc_dim2) * dpc_dim1] - uw[ip1 + (
			jm1 + k * uw_dim2) * uw_dim1] * dpn[ii + (jjm1 + kkp1 
			* dpn_dim2) * dpn_dim1] - us[ip1 + (jm1 + k * us_dim2)
			 * us_dim1] * dpe[ii + (jjm1 + kkp1 * dpe_dim2) * 
			dpe_dim1] - uc[ip1 + (jm1 + k * uc_dim2) * uc_dim1] * 
			dpne[ii + (jjm1 + kkp1 * dpne_dim2) * dpne_dim1]) - 
			upse[ii + (jj + kk * upse_dim2) * upse_dim1] * (-one[
			i__ + (jm2 + kp1 * one_dim2) * one_dim1] * dpc[ii + (
			jjm1 + kkp1 * dpc_dim2) * dpc_dim1] - usw[ip1 + (jm1 
			+ kp1 * usw_dim2) * usw_dim1] * opc[ii + (jjm1 + kkp1 
			* opc_dim2) * opc_dim1] - oe[i__ + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * dpn[ii + (jjm1 + kkp1 * 
			dpn_dim2) * dpn_dim1] - uw[ip1 + (jm1 + kp1 * uw_dim2)
			 * uw_dim1] * opn[ii + (jjm1 + kkp1 * opn_dim2) * 
			opn_dim1] - on[ip1 + (jm2 + kp1 * on_dim2) * on_dim1] 
			* dpe[ii + (jjm1 + kkp1 * dpe_dim2) * dpe_dim1] - us[
			ip1 + (jm1 + kp1 * us_dim2) * us_dim1] * ope[ii + (
			jjm1 + kkp1 * ope_dim2) * ope_dim1] + oc[ip1 + (jm1 + 
			kp1 * oc_dim2) * oc_dim1] * dpne[ii + (jjm1 + kkp1 * 
			dpne_dim2) * dpne_dim1] - uc[ip1 + (jm1 + kp1 * 
			uc_dim2) * uc_dim1] * opne[ii + (jjm1 + kkp1 * 
			opne_dim2) * opne_dim1]);
		tmp6_xus__ = -ope[ii + (jj + kk * ope_dim2) * ope_dim1] * (
			-usw[ip1 + (j + k * usw_dim2) * usw_dim1] * dpn[ii + (
			jjm1 + kkp1 * dpn_dim2) * dpn_dim1] - us[ip1 + (j + k 
			* us_dim2) * us_dim1] * dpne[ii + (jjm1 + kkp1 * 
			dpne_dim2) * dpne_dim1]) - upe[ii + (jj + kk * 
			upe_dim2) * upe_dim1] * (-one[i__ + (jm1 + kp1 * 
			one_dim2) * one_dim1] * dpn[ii + (jjm1 + kkp1 * 
			dpn_dim2) * dpn_dim1] - usw[ip1 + (j + kp1 * usw_dim2)
			 * usw_dim1] * opn[ii + (jjm1 + kkp1 * opn_dim2) * 
			opn_dim1] - on[ip1 + (jm1 + kp1 * on_dim2) * on_dim1] 
			* dpne[ii + (jjm1 + kkp1 * dpne_dim2) * dpne_dim1] - 
			us[ip1 + (j + kp1 * us_dim2) * us_dim1] * opne[ii + (
			jjm1 + kkp1 * opne_dim2) * opne_dim1]);
		xus[ii + (jj + kk * xus_dim2) * xus_dim1] = tmp1_xus__ + 
			tmp2_xus__ + tmp3_xus__ + tmp4_xus__ + tmp5_xus__ + 
			tmp6_xus__;
/* * ******************************************************************** */
/* * *** > uNE; */
/* * ******************************************************************** */
/* * ***XuNE(ii,jj,kk) = */
		tmp1_xune__ = opc[ii + (jj + kk * opc_dim2) * opc_dim1] * une[
			i__ + (j + k * une_dim2) * une_dim1] * dpsw[iip1 + (
			jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - upc[ii + (jj 
			+ kk * upc_dim2) * upc_dim1] * (-one[i__ + (j + kp1 * 
			one_dim2) * one_dim1] * dpsw[iip1 + (jjp1 + kkp1 * 
			dpsw_dim2) * dpsw_dim1] - une[i__ + (j + kp1 * 
			une_dim2) * une_dim1] * opsw[iip1 + (jjp1 + kkp1 * 
			opsw_dim2) * opsw_dim1]) - opn[ii + (jj + kk * 
			opn_dim2) * opn_dim1] * (-ue[i__ + (jp1 + k * ue_dim2)
			 * ue_dim1] * dpsw[iip1 + (jjp1 + kkp1 * dpsw_dim2) * 
			dpsw_dim1] - une[i__ + (jp1 + k * une_dim2) * 
			une_dim1] * dpw[iip1 + (jjp1 + kkp1 * dpw_dim2) * 
			dpw_dim1]) - upn[ii + (jj + kk * upn_dim2) * upn_dim1]
			 * (-oe[i__ + (jp1 + kp1 * oe_dim2) * oe_dim1] * dpsw[
			iip1 + (jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - ue[
			i__ + (jp1 + kp1 * ue_dim2) * ue_dim1] * opsw[iip1 + (
			jjp1 + kkp1 * opsw_dim2) * opsw_dim1] - one[i__ + (
			jp1 + kp1 * one_dim2) * one_dim1] * dpw[iip1 + (jjp1 
			+ kkp1 * dpw_dim2) * dpw_dim1] - une[i__ + (jp1 + kp1 
			* une_dim2) * une_dim1] * opw[iip1 + (jjp1 + kkp1 * 
			opw_dim2) * opw_dim1]) - ope[ii + (jj + kk * ope_dim2)
			 * ope_dim1] * (-un[ip1 + (j + k * un_dim2) * un_dim1]
			 * dpsw[iip1 + (jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] 
			- une[ip1 + (j + k * une_dim2) * une_dim1] * dps[iip1 
			+ (jjp1 + kkp1 * dps_dim2) * dps_dim1]);
		tmp2_xune__ = -upe[ii + (jj + kk * upe_dim2) * upe_dim1] * (
			-on[ip1 + (j + kp1 * on_dim2) * on_dim1] * dpsw[iip1 
			+ (jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] - un[ip1 + (
			j + kp1 * un_dim2) * un_dim1] * opsw[iip1 + (jjp1 + 
			kkp1 * opsw_dim2) * opsw_dim1] - one[ip1 + (j + kp1 * 
			one_dim2) * one_dim1] * dps[iip1 + (jjp1 + kkp1 * 
			dps_dim2) * dps_dim1] - une[ip1 + (j + kp1 * une_dim2)
			 * une_dim1] * ops[iip1 + (jjp1 + kkp1 * ops_dim2) * 
			ops_dim1]) - opne[ii + (jj + kk * opne_dim2) * 
			opne_dim1] * (-uc[ip1 + (jp1 + k * uc_dim2) * uc_dim1]
			 * dpsw[iip1 + (jjp1 + kkp1 * dpsw_dim2) * dpsw_dim1] 
			- un[ip1 + (jp1 + k * un_dim2) * un_dim1] * dpw[iip1 
			+ (jjp1 + kkp1 * dpw_dim2) * dpw_dim1] - ue[ip1 + (
			jp1 + k * ue_dim2) * ue_dim1] * dps[iip1 + (jjp1 + 
			kkp1 * dps_dim2) * dps_dim1] - une[ip1 + (jp1 + k * 
			une_dim2) * une_dim1] * dpc[iip1 + (jjp1 + kkp1 * 
			dpc_dim2) * dpc_dim1]) - upne[ii + (jj + kk * 
			upne_dim2) * upne_dim1] * (oc[ip1 + (jp1 + kp1 * 
			oc_dim2) * oc_dim1] * dpsw[iip1 + (jjp1 + kkp1 * 
			dpsw_dim2) * dpsw_dim1] - uc[ip1 + (jp1 + kp1 * 
			uc_dim2) * uc_dim1] * opsw[iip1 + (jjp1 + kkp1 * 
			opsw_dim2) * opsw_dim1] - on[ip1 + (jp1 + kp1 * 
			on_dim2) * on_dim1] * dpw[iip1 + (jjp1 + kkp1 * 
			dpw_dim2) * dpw_dim1] - un[ip1 + (jp1 + kp1 * un_dim2)
			 * un_dim1] * opw[iip1 + (jjp1 + kkp1 * opw_dim2) * 
			opw_dim1] - oe[ip1 + (jp1 + kp1 * oe_dim2) * oe_dim1] 
			* dps[iip1 + (jjp1 + kkp1 * dps_dim2) * dps_dim1] - 
			ue[ip1 + (jp1 + kp1 * ue_dim2) * ue_dim1] * ops[iip1 
			+ (jjp1 + kkp1 * ops_dim2) * ops_dim1] - one[ip1 + (
			jp1 + kp1 * one_dim2) * one_dim1] * dpc[iip1 + (jjp1 
			+ kkp1 * dpc_dim2) * dpc_dim1] - une[ip1 + (jp1 + kp1 
			* une_dim2) * une_dim1] * opc[iip1 + (jjp1 + kkp1 * 
			opc_dim2) * opc_dim1]);
		xune[ii + (jj + kk * xune_dim2) * xune_dim1] = tmp1_xune__ + 
			tmp2_xune__;
/* * ******************************************************************** */
/* * *** > uNW; */
/* * ******************************************************************** */
/* * ***XuNW(ii,jj,kk) = */
		tmp1_xunw__ = -opw[ii + (jj + kk * opw_dim2) * opw_dim1] * (
			-unw[im1 + (j + k * unw_dim2) * unw_dim1] * dps[iim1 
			+ (jjp1 + kkp1 * dps_dim2) * dps_dim1] - un[im1 + (j 
			+ k * un_dim2) * un_dim1] * dpse[iim1 + (jjp1 + kkp1 *
			 dpse_dim2) * dpse_dim1]) - upw[ii + (jj + kk * 
			upw_dim2) * upw_dim1] * (-onw[im1 + (j + kp1 * 
			onw_dim2) * onw_dim1] * dps[iim1 + (jjp1 + kkp1 * 
			dps_dim2) * dps_dim1] - unw[im1 + (j + kp1 * unw_dim2)
			 * unw_dim1] * ops[iim1 + (jjp1 + kkp1 * ops_dim2) * 
			ops_dim1] - on[im1 + (j + kp1 * on_dim2) * on_dim1] * 
			dpse[iim1 + (jjp1 + kkp1 * dpse_dim2) * dpse_dim1] - 
			un[im1 + (j + kp1 * un_dim2) * un_dim1] * opse[iim1 + 
			(jjp1 + kkp1 * opse_dim2) * opse_dim1]) - opnw[ii + (
			jj + kk * opnw_dim2) * opnw_dim1] * (-uw[im1 + (jp1 + 
			k * uw_dim2) * uw_dim1] * dps[iim1 + (jjp1 + kkp1 * 
			dps_dim2) * dps_dim1] - unw[im1 + (jp1 + k * unw_dim2)
			 * unw_dim1] * dpc[iim1 + (jjp1 + kkp1 * dpc_dim2) * 
			dpc_dim1] - uc[im1 + (jp1 + k * uc_dim2) * uc_dim1] * 
			dpse[iim1 + (jjp1 + kkp1 * dpse_dim2) * dpse_dim1] - 
			un[im1 + (jp1 + k * un_dim2) * un_dim1] * dpe[iim1 + (
			jjp1 + kkp1 * dpe_dim2) * dpe_dim1]);
		tmp2_xunw__ = -upnw[ii + (jj + kk * upnw_dim2) * upnw_dim1] * 
			(-oe[im2 + (jp1 + kp1 * oe_dim2) * oe_dim1] * dps[
			iim1 + (jjp1 + kkp1 * dps_dim2) * dps_dim1] - uw[im1 
			+ (jp1 + kp1 * uw_dim2) * uw_dim1] * ops[iim1 + (jjp1 
			+ kkp1 * ops_dim2) * ops_dim1] - onw[im1 + (jp1 + kp1 
			* onw_dim2) * onw_dim1] * dpc[iim1 + (jjp1 + kkp1 * 
			dpc_dim2) * dpc_dim1] - unw[im1 + (jp1 + kp1 * 
			unw_dim2) * unw_dim1] * opc[iim1 + (jjp1 + kkp1 * 
			opc_dim2) * opc_dim1] + oc[im1 + (jp1 + kp1 * oc_dim2)
			 * oc_dim1] * dpse[iim1 + (jjp1 + kkp1 * dpse_dim2) * 
			dpse_dim1] - uc[im1 + (jp1 + kp1 * uc_dim2) * uc_dim1]
			 * opse[iim1 + (jjp1 + kkp1 * opse_dim2) * opse_dim1] 
			- on[im1 + (jp1 + kp1 * on_dim2) * on_dim1] * dpe[
			iim1 + (jjp1 + kkp1 * dpe_dim2) * dpe_dim1] - un[im1 
			+ (jp1 + kp1 * un_dim2) * un_dim1] * ope[iim1 + (jjp1 
			+ kkp1 * ope_dim2) * ope_dim1]) + opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] * unw[i__ + (j + k * unw_dim2) *
			 unw_dim1] * dpse[iim1 + (jjp1 + kkp1 * dpse_dim2) * 
			dpse_dim1] - upc[ii + (jj + kk * upc_dim2) * upc_dim1]
			 * (-onw[i__ + (j + kp1 * onw_dim2) * onw_dim1] * 
			dpse[iim1 + (jjp1 + kkp1 * dpse_dim2) * dpse_dim1] - 
			unw[i__ + (j + kp1 * unw_dim2) * unw_dim1] * opse[
			iim1 + (jjp1 + kkp1 * opse_dim2) * opse_dim1]) - opn[
			ii + (jj + kk * opn_dim2) * opn_dim1] * (-uw[i__ + (
			jp1 + k * uw_dim2) * uw_dim1] * dpse[iim1 + (jjp1 + 
			kkp1 * dpse_dim2) * dpse_dim1] - unw[i__ + (jp1 + k * 
			unw_dim2) * unw_dim1] * dpe[iim1 + (jjp1 + kkp1 * 
			dpe_dim2) * dpe_dim1]) - upn[ii + (jj + kk * upn_dim2)
			 * upn_dim1] * (-oe[im1 + (jp1 + kp1 * oe_dim2) * 
			oe_dim1] * dpse[iim1 + (jjp1 + kkp1 * dpse_dim2) * 
			dpse_dim1] - uw[i__ + (jp1 + kp1 * uw_dim2) * uw_dim1]
			 * opse[iim1 + (jjp1 + kkp1 * opse_dim2) * opse_dim1] 
			- onw[i__ + (jp1 + kp1 * onw_dim2) * onw_dim1] * dpe[
			iim1 + (jjp1 + kkp1 * dpe_dim2) * dpe_dim1] - unw[i__ 
			+ (jp1 + kp1 * unw_dim2) * unw_dim1] * ope[iim1 + (
			jjp1 + kkp1 * ope_dim2) * ope_dim1]);
		xunw[ii + (jj + kk * xunw_dim2) * xunw_dim1] = tmp1_xunw__ + 
			tmp2_xunw__;
/* * ******************************************************************** */
/* * *** > uSE; */
/* * ******************************************************************** */
/* * ***XuSE(ii,jj,kk) = */
		tmp1_xuse__ = -ops[ii + (jj + kk * ops_dim2) * ops_dim1] * (
			-use[i__ + (jm1 + k * use_dim2) * use_dim1] * dpw[
			iip1 + (jjm1 + kkp1 * dpw_dim2) * dpw_dim1] - ue[i__ 
			+ (jm1 + k * ue_dim2) * ue_dim1] * dpnw[iip1 + (jjm1 
			+ kkp1 * dpnw_dim2) * dpnw_dim1]) - ups[ii + (jj + kk 
			* ups_dim2) * ups_dim1] * (-onw[ip1 + (jm2 + kp1 * 
			onw_dim2) * onw_dim1] * dpw[iip1 + (jjm1 + kkp1 * 
			dpw_dim2) * dpw_dim1] - use[i__ + (jm1 + kp1 * 
			use_dim2) * use_dim1] * opw[iip1 + (jjm1 + kkp1 * 
			opw_dim2) * opw_dim1] - oe[i__ + (jm1 + kp1 * oe_dim2)
			 * oe_dim1] * dpnw[iip1 + (jjm1 + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - ue[i__ + (jm1 + kp1 * ue_dim2) * ue_dim1]
			 * opnw[iip1 + (jjm1 + kkp1 * opnw_dim2) * opnw_dim1])
			 + opc[ii + (jj + kk * opc_dim2) * opc_dim1] * use[
			i__ + (j + k * use_dim2) * use_dim1] * dpnw[iip1 + (
			jjm1 + kkp1 * dpnw_dim2) * dpnw_dim1] - upc[ii + (jj 
			+ kk * upc_dim2) * upc_dim1] * (-onw[ip1 + (jm1 + kp1 
			* onw_dim2) * onw_dim1] * dpnw[iip1 + (jjm1 + kkp1 * 
			dpnw_dim2) * dpnw_dim1] - use[i__ + (j + kp1 * 
			use_dim2) * use_dim1] * opnw[iip1 + (jjm1 + kkp1 * 
			opnw_dim2) * opnw_dim1]);
		tmp2_xuse__ = -opse[ii + (jj + kk * opse_dim2) * opse_dim1] * 
			(-us[ip1 + (jm1 + k * us_dim2) * us_dim1] * dpw[iip1 
			+ (jjm1 + kkp1 * dpw_dim2) * dpw_dim1] - uc[ip1 + (
			jm1 + k * uc_dim2) * uc_dim1] * dpnw[iip1 + (jjm1 + 
			kkp1 * dpnw_dim2) * dpnw_dim1] - use[ip1 + (jm1 + k * 
			use_dim2) * use_dim1] * dpc[iip1 + (jjm1 + kkp1 * 
			dpc_dim2) * dpc_dim1] - ue[ip1 + (jm1 + k * ue_dim2) *
			 ue_dim1] * dpn[iip1 + (jjm1 + kkp1 * dpn_dim2) * 
			dpn_dim1]) - upse[ii + (jj + kk * upse_dim2) * 
			upse_dim1] * (-on[ip1 + (jm2 + kp1 * on_dim2) * 
			on_dim1] * dpw[iip1 + (jjm1 + kkp1 * dpw_dim2) * 
			dpw_dim1] - us[ip1 + (jm1 + kp1 * us_dim2) * us_dim1] 
			* opw[iip1 + (jjm1 + kkp1 * opw_dim2) * opw_dim1] + 
			oc[ip1 + (jm1 + kp1 * oc_dim2) * oc_dim1] * dpnw[iip1 
			+ (jjm1 + kkp1 * dpnw_dim2) * dpnw_dim1] - uc[ip1 + (
			jm1 + kp1 * uc_dim2) * uc_dim1] * opnw[iip1 + (jjm1 + 
			kkp1 * opnw_dim2) * opnw_dim1] - onw[ip2 + (jm2 + kp1 
			* onw_dim2) * onw_dim1] * dpc[iip1 + (jjm1 + kkp1 * 
			dpc_dim2) * dpc_dim1] - use[ip1 + (jm1 + kp1 * 
			use_dim2) * use_dim1] * opc[iip1 + (jjm1 + kkp1 * 
			opc_dim2) * opc_dim1] - oe[ip1 + (jm1 + kp1 * oe_dim2)
			 * oe_dim1] * dpn[iip1 + (jjm1 + kkp1 * dpn_dim2) * 
			dpn_dim1] - ue[ip1 + (jm1 + kp1 * ue_dim2) * ue_dim1] 
			* opn[iip1 + (jjm1 + kkp1 * opn_dim2) * opn_dim1]) - 
			ope[ii + (jj + kk * ope_dim2) * ope_dim1] * (-us[ip1 
			+ (j + k * us_dim2) * us_dim1] * dpnw[iip1 + (jjm1 + 
			kkp1 * dpnw_dim2) * dpnw_dim1] - use[ip1 + (j + k * 
			use_dim2) * use_dim1] * dpn[iip1 + (jjm1 + kkp1 * 
			dpn_dim2) * dpn_dim1]) - upe[ii + (jj + kk * upe_dim2)
			 * upe_dim1] * (-on[ip1 + (jm1 + kp1 * on_dim2) * 
			on_dim1] * dpnw[iip1 + (jjm1 + kkp1 * dpnw_dim2) * 
			dpnw_dim1] - us[ip1 + (j + kp1 * us_dim2) * us_dim1] *
			 opnw[iip1 + (jjm1 + kkp1 * opnw_dim2) * opnw_dim1] - 
			onw[ip2 + (jm1 + kp1 * onw_dim2) * onw_dim1] * dpn[
			iip1 + (jjm1 + kkp1 * dpn_dim2) * dpn_dim1] - use[ip1 
			+ (j + kp1 * use_dim2) * use_dim1] * opn[iip1 + (jjm1 
			+ kkp1 * opn_dim2) * opn_dim1]);
		xuse[ii + (jj + kk * xuse_dim2) * xuse_dim1] = tmp1_xuse__ + 
			tmp2_xuse__;
/* * ******************************************************************** */
/* * *** > uSW; */
/* * ******************************************************************** */
/* * ***XuSW(ii,jj,kk) = */
		tmp1_xusw__ = -opsw[ii + (jj + kk * opsw_dim2) * opsw_dim1] * 
			(-usw[im1 + (jm1 + k * usw_dim2) * usw_dim1] * dpc[
			iim1 + (jjm1 + kkp1 * dpc_dim2) * dpc_dim1] - uw[im1 
			+ (jm1 + k * uw_dim2) * uw_dim1] * dpn[iim1 + (jjm1 + 
			kkp1 * dpn_dim2) * dpn_dim1] - us[im1 + (jm1 + k * 
			us_dim2) * us_dim1] * dpe[iim1 + (jjm1 + kkp1 * 
			dpe_dim2) * dpe_dim1] - uc[im1 + (jm1 + k * uc_dim2) *
			 uc_dim1] * dpne[iim1 + (jjm1 + kkp1 * dpne_dim2) * 
			dpne_dim1]) - upsw[ii + (jj + kk * upsw_dim2) * 
			upsw_dim1] * (-one[im2 + (jm2 + kp1 * one_dim2) * 
			one_dim1] * dpc[iim1 + (jjm1 + kkp1 * dpc_dim2) * 
			dpc_dim1] - usw[im1 + (jm1 + kp1 * usw_dim2) * 
			usw_dim1] * opc[iim1 + (jjm1 + kkp1 * opc_dim2) * 
			opc_dim1] - oe[im2 + (jm1 + kp1 * oe_dim2) * oe_dim1] 
			* dpn[iim1 + (jjm1 + kkp1 * dpn_dim2) * dpn_dim1] - 
			uw[im1 + (jm1 + kp1 * uw_dim2) * uw_dim1] * opn[iim1 
			+ (jjm1 + kkp1 * opn_dim2) * opn_dim1] - on[im1 + (
			jm2 + kp1 * on_dim2) * on_dim1] * dpe[iim1 + (jjm1 + 
			kkp1 * dpe_dim2) * dpe_dim1] - us[im1 + (jm1 + kp1 * 
			us_dim2) * us_dim1] * ope[iim1 + (jjm1 + kkp1 * 
			ope_dim2) * ope_dim1] + oc[im1 + (jm1 + kp1 * oc_dim2)
			 * oc_dim1] * dpne[iim1 + (jjm1 + kkp1 * dpne_dim2) * 
			dpne_dim1] - uc[im1 + (jm1 + kp1 * uc_dim2) * uc_dim1]
			 * opne[iim1 + (jjm1 + kkp1 * opne_dim2) * opne_dim1])
			 - opw[ii + (jj + kk * opw_dim2) * opw_dim1] * (-usw[
			im1 + (j + k * usw_dim2) * usw_dim1] * dpn[iim1 + (
			jjm1 + kkp1 * dpn_dim2) * dpn_dim1] - us[im1 + (j + k 
			* us_dim2) * us_dim1] * dpne[iim1 + (jjm1 + kkp1 * 
			dpne_dim2) * dpne_dim1]);
		tmp2_xusw__ = -upw[ii + (jj + kk * upw_dim2) * upw_dim1] * (
			-one[im2 + (jm1 + kp1 * one_dim2) * one_dim1] * dpn[
			iim1 + (jjm1 + kkp1 * dpn_dim2) * dpn_dim1] - usw[im1 
			+ (j + kp1 * usw_dim2) * usw_dim1] * opn[iim1 + (jjm1 
			+ kkp1 * opn_dim2) * opn_dim1] - on[im1 + (jm1 + kp1 *
			 on_dim2) * on_dim1] * dpne[iim1 + (jjm1 + kkp1 * 
			dpne_dim2) * dpne_dim1] - us[im1 + (j + kp1 * us_dim2)
			 * us_dim1] * opne[iim1 + (jjm1 + kkp1 * opne_dim2) * 
			opne_dim1]) - ops[ii + (jj + kk * ops_dim2) * 
			ops_dim1] * (-usw[i__ + (jm1 + k * usw_dim2) * 
			usw_dim1] * dpe[iim1 + (jjm1 + kkp1 * dpe_dim2) * 
			dpe_dim1] - uw[i__ + (jm1 + k * uw_dim2) * uw_dim1] * 
			dpne[iim1 + (jjm1 + kkp1 * dpne_dim2) * dpne_dim1]) - 
			ups[ii + (jj + kk * ups_dim2) * ups_dim1] * (-one[im1 
			+ (jm2 + kp1 * one_dim2) * one_dim1] * dpe[iim1 + (
			jjm1 + kkp1 * dpe_dim2) * dpe_dim1] - usw[i__ + (jm1 
			+ kp1 * usw_dim2) * usw_dim1] * ope[iim1 + (jjm1 + 
			kkp1 * ope_dim2) * ope_dim1] - oe[im1 + (jm1 + kp1 * 
			oe_dim2) * oe_dim1] * dpne[iim1 + (jjm1 + kkp1 * 
			dpne_dim2) * dpne_dim1] - uw[i__ + (jm1 + kp1 * 
			uw_dim2) * uw_dim1] * opne[iim1 + (jjm1 + kkp1 * 
			opne_dim2) * opne_dim1]) + opc[ii + (jj + kk * 
			opc_dim2) * opc_dim1] * usw[i__ + (j + k * usw_dim2) *
			 usw_dim1] * dpne[iim1 + (jjm1 + kkp1 * dpne_dim2) * 
			dpne_dim1] - upc[ii + (jj + kk * upc_dim2) * upc_dim1]
			 * (-one[im1 + (jm1 + kp1 * one_dim2) * one_dim1] * 
			dpne[iim1 + (jjm1 + kkp1 * dpne_dim2) * dpne_dim1] - 
			usw[i__ + (j + kp1 * usw_dim2) * usw_dim1] * opne[
			iim1 + (jjm1 + kkp1 * opne_dim2) * opne_dim1]);
		xusw[ii + (jj + kk * xusw_dim2) * xusw_dim1] = tmp1_xusw__ + 
			tmp2_xusw__;
/* * */
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
} /* buildg_27__ */

