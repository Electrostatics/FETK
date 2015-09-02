/* ./src_f77/buildAd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    buildAd.f */
/* * @author  Michael Holst */
/* * @brief   PDE Discretization routines. */
/* * @version $Id: buildAd.c,v 1.3 2010/08/12 05:45:18 fetk Exp $ */
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
/* Subroutine */ int builda_(integer *nx, integer *ny, integer *nz, integer *
	ipkey, integer *mgdisc, integer *numdia, integer *ipc, doublereal *
	rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, 
	doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, 
	doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *
	a3cf, doublereal *ccf, doublereal *fcf)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int builda_fe__(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), builda_fv__(integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, 0, 0 };
    static cilist io___2 = { 0, 6, 0, 0, 0 };
    static cilist io___3 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    break the matrix data-structure into diagonals */
/* *    and then call the matrix build routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the build routine *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;
    --cc;
    --fc;
    --xf;
    --yf;
    --zf;
    --gxcf;
    --gycf;
    --gzcf;
    --a1cf;
    --a2cf;
    --a3cf;
    --ccf;
    --fcf;

    /* Function Body */
    if (*mgdisc == 0) {
	s_wsle(&io___1);
	do_lio(&c__9, &c__1, "% BUILDA:   (BOX) performing discretization...",
		 (ftnlen)46);
	e_wsle();
	builda_fv__(nx, ny, nz, ipkey, numdia, &ipc[1], &rpc[1], &ac[ac_dim1 
		+ 1], &cc[1], &fc[1], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 
		3 + 1], &ac[(ac_dim1 << 2) + 1], &xf[1], &yf[1], &zf[1], &
		gxcf[1], &gycf[1], &gzcf[1], &a1cf[1], &a2cf[1], &a3cf[1], &
		ccf[1], &fcf[1]);
    } else if (*mgdisc == 1) {
	s_wsle(&io___2);
	do_lio(&c__9, &c__1, "% BUILDA:   (FEM) performing discretization...",
		 (ftnlen)46);
	e_wsle();
	builda_fe__(nx, ny, nz, ipkey, numdia, &ipc[1], &rpc[1], &ac[ac_dim1 
		+ 1], &cc[1], &fc[1], &ac[(ac_dim1 << 1) + 1], &ac[ac_dim1 * 
		3 + 1], &ac[(ac_dim1 << 2) + 1], &ac[ac_dim1 * 5 + 1], &ac[
		ac_dim1 * 6 + 1], &ac[ac_dim1 * 7 + 1], &ac[(ac_dim1 << 3) + 
		1], &ac[ac_dim1 * 9 + 1], &ac[ac_dim1 * 10 + 1], &ac[ac_dim1 *
		 11 + 1], &ac[ac_dim1 * 12 + 1], &ac[ac_dim1 * 13 + 1], &ac[
		ac_dim1 * 14 + 1], &xf[1], &yf[1], &zf[1], &gxcf[1], &gycf[1],
		 &gzcf[1], &a1cf[1], &a2cf[1], &a3cf[1], &ccf[1], &fcf[1]);
    } else {
	s_wsle(&io___3);
	do_lio(&c__9, &c__1, "% BUILDA: invalid discretization requested...", 
		(ftnlen)45);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* builda_ */

/* Subroutine */ int builda_fv__(integer *nx, integer *ny, integer *nz, 
	integer *ipkey, integer *numdia, integer *ipc, doublereal *rpc, 
	doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, 
	doublereal *on, doublereal *uc, doublereal *xf, doublereal *yf, 
	doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, 
	doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf,
	 doublereal *fcf)
{
    /* System generated locals */
    integer a1cf_dim1, a1cf_dim2, a1cf_offset, a2cf_dim1, a2cf_dim2, 
	    a2cf_offset, a3cf_dim1, a3cf_dim2, a3cf_offset, ccf_dim1, 
	    ccf_dim2, ccf_offset, fcf_dim1, fcf_dim2, fcf_offset, oe_dim1, 
	    oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1, uc_dim2,
	     uc_offset, cc_dim1, cc_dim2, cc_offset, fc_dim1, fc_dim2, 
	    fc_offset, oc_dim1, oc_dim2, oc_offset, gxcf_dim1, gxcf_dim2, 
	    gxcf_offset, gycf_dim1, gycf_dim2, gycf_offset, gzcf_dim1, 
	    gzcf_dim2, gzcf_offset, i__1, i__2, i__3, i__4, i__5, i__6;

    /* Local variables */
    static doublereal coef_oem1__, coef_ucm1__, coef_onm1__;
    static integer i__, j, k;
    static doublereal bc_cond_e__, bc_cond_d__, bc_cond_n__, bc_cond_s__, 
	    bc_cond_u__, bc_cond_w__, hx, hy, hz;
    static integer ike, jke, kke;
    static doublereal hxm1, hym1, hzm1;
    static integer nxm1, nym1, nzm1;
    static doublereal diag, coef_fc__, coef_oe__, coef_uc__, coef_on__;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    box method (finite volume) discretization of a 3d pde on a */
/* *    tensor product (axi-parallel) three-dimensional mesh. */
/* * */
/* *    this subroutine discretizes the elliptic boundary value problem: */
/* * */
/* *          lu = f, u in omega */
/* *           u = g, u on boundary of omega */
/* * */
/* *    the multigrid code requires the operator in the form: */
/* * */
/* *         - \nabla \cdot (a \nabla u) + b \cdot u + c u = f */
/* * */
/* *    or: */
/* * */
/* *        lu = (a11 u_x)_x + (a22 u_y)_y + (a33 u_z)_z */
/* *             + b1 u_x + b2 u_y + b3 u_z + c u */
/* * */
/* *    here, we consider only the case: b=b1=b2=b3=0. */
/* *    then we assume: */
/* * */
/* *    the tensor a=diag(a11,a22,a33) has components which are */
/* *    then scalar functions, a11(x,y,z),a22(x,y,z),a33(x,y,z) */
/* *    and the functions c(x,y,z) and f(x,y,z) are also scalar. */
/* *    functions.  All are allowed to be possibly discontinuous on */
/* *    omega (the discontinuities must be along grid lines on fine grid). */
/* *    the boundary function g(x,y,z) is smooth on boundary of omega. */
/* * */
/* *    we will take the following conventions: */
/* *    (north,south,east,west refers to x-y plane. */
/* *    up/down refers to the z-axis) */
/* *      (u(x+h_x,y,z) = u^+   (east neighbor of u(x,y,z)) */
/* *      (u(x-h_x,y,z) = u^-   (west neighbor of u(x,y,z)) */
/* *      (u(x,y+h_y,z) = u_+   (north neighbor of u(x,y,z)) */
/* *      (u(x,y-h_y,z) = u_-   (south neighbor of u(x,y,z)) */
/* *      (u(x,y,z+h_z) = u.+   (up neighbor of u(x,y,z)) */
/* *      (u(x,y,z-h_z) = u.-   (down neighbor u(x,y,z)) */
/* * */
/* *    below, we will denote: */
/* *          u(x+h_x,y,z)       as u^+ */
/* *          u(x+(1/2)h_x,y,z)  as u^++ */
/* *          u(x-h_x,y,z)       as u^+ */
/* *          u(x-(1/2)h_x,y,z)  as u^-- */
/* *    and similarly for u_-,u_--,u_+,u_++,u.-,u.--,u.+,u.++. */
/* * */
/* *    we use the 3d analogue of the box method (see varga, pg. 191) */
/* *    which results in the following difference scheme: */
/* * */
/* *    u            : [ + (a11^++ + a11^--) * (h_y*h_z/h_x) */
/* *                     + (a22_++ + a22_--) * (h_x*h_z/h_y) */
/* *                     + (a33.++ + a33.--) * (h_x*h_y/h_z) */
/* *                     + c * (h_x*h_y*h_z) ] u */
/* *    u^+ (e nbr)  : [ - (a11^++) * (h_y*h_z/h_x) ] */
/* *    u^_ (w nbr)  : [ - (a11^--) * (h_y*h_z/h_x) ] */
/* *    u_+ (n nbr)  : [ - (a22_++) * (h_x*h_z/h_y) ] */
/* *    u_- (s nbr)  : [ - (a22_--) * (h_x*h_z/h_y) ] */
/* *    u.+ (u nbr)  : [ - (a33.++) * (h_x*h_y/h_z) ] */
/* *    u.- (d nbr)  : [ - (a33.--) * (h_x*h_y/h_z) ] */
/* *    f            : [ h_x*h_y*h_z ] f */
/* * */
/* *    note: fast way to do a conditional: we wish to set (a=coef), */
/* *          unless we are on the (z=0)-boundary, which occurs with k=1: */
/* * */
/* *             coef = ...etc... */
/* *             ike  = min0(1,iabs(k-1)) */
/* *             a (index1) = (ike)*coef */
/* *             b(index2) = b(index2) - (1-ike)*coef*bnd_data */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** save the problem key with this operator *** */
    /* Parameter adjustments */
    gzcf_dim1 = *nx;
    gzcf_dim2 = *ny;
    gzcf_offset = 1 + gzcf_dim1 * (1 + gzcf_dim2);
    gzcf -= gzcf_offset;
    fcf_dim1 = *nx;
    fcf_dim2 = *ny;
    fcf_offset = 1 + fcf_dim1 * (1 + fcf_dim2);
    fcf -= fcf_offset;
    ccf_dim1 = *nx;
    ccf_dim2 = *ny;
    ccf_offset = 1 + ccf_dim1 * (1 + ccf_dim2);
    ccf -= ccf_offset;
    a3cf_dim1 = *nx;
    a3cf_dim2 = *ny;
    a3cf_offset = 1 + a3cf_dim1 * (1 + a3cf_dim2);
    a3cf -= a3cf_offset;
    a2cf_dim1 = *nx;
    a2cf_dim2 = *ny;
    a2cf_offset = 1 + a2cf_dim1 * (1 + a2cf_dim2);
    a2cf -= a2cf_offset;
    a1cf_dim1 = *nx;
    a1cf_dim2 = *ny;
    a1cf_offset = 1 + a1cf_dim1 * (1 + a1cf_dim2);
    a1cf -= a1cf_offset;
    gycf_dim1 = *nx;
    gycf_dim2 = *nz;
    gycf_offset = 1 + gycf_dim1 * (1 + gycf_dim2);
    gycf -= gycf_offset;
    gxcf_dim1 = *ny;
    gxcf_dim2 = *nz;
    gxcf_offset = 1 + gxcf_dim1 * (1 + gxcf_dim2);
    gxcf -= gxcf_offset;
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
    --xf;
    --yf;
    --zf;

    /* Function Body */
    ipc[10] = *ipkey;
/* * */
/* *    *** note how many nonzeros in this discretization stencil */
    ipc[11] = 7;
    ipc[12] = 1;
    *numdia = 4;
/* * */
/* *    *** define n and determine number of mesh points *** */
    nxm1 = *nx - 1;
    nym1 = *ny - 1;
    nzm1 = *nz - 1;
/* * */
/* *    *** determine diag scale factor *** */
/* *    *** (would like something close to ones on the main diagonal) *** */
    diag = 1.;
/* * */
/* * ********************************************************************* */
/* * *** interior points *** */
/* * ********************************************************************* */
/* * */
/* *    *** build the operator *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
	hzm1 = zf[k] - zf[k - 1];
	hz = zf[k + 1] - zf[k];
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
	    hym1 = yf[j] - yf[j - 1];
	    hy = yf[j + 1] - yf[j];
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		hxm1 = xf[i__] - xf[i__ - 1];
		hx = xf[i__ + 1] - xf[i__];
/* * */
/* *             *** some coefficients *** */
		coef_oe__ = diag * (hym1 + hy) * (hzm1 + hz) / (hx * 4.f);
		coef_oem1__ = diag * (hym1 + hy) * (hzm1 + hz) / (hxm1 * 4.f);
		coef_on__ = diag * (hxm1 + hx) * (hzm1 + hz) / (hy * 4.f);
		coef_onm1__ = diag * (hxm1 + hx) * (hzm1 + hz) / (hym1 * 4.f);
		coef_uc__ = diag * (hxm1 + hx) * (hym1 + hy) / (hz * 4.f);
		coef_ucm1__ = diag * (hxm1 + hx) * (hym1 + hy) / (hzm1 * 4.f);
		coef_fc__ = diag * (hxm1 + hx) * (hym1 + hy) * (hzm1 + hz) / 
			8.f;
/* * */
/* *             *** the coefficient and source function *** */
		fc[i__ + (j + k * fc_dim2) * fc_dim1] = coef_fc__ * fcf[i__ + 
			(j + k * fcf_dim2) * fcf_dim1];
		cc[i__ + (j + k * cc_dim2) * cc_dim1] = coef_fc__ * ccf[i__ + 
			(j + k * ccf_dim2) * ccf_dim1];
/* * */
/* *             *** the diagonal for matvecs and smoothings *** */
		oc[i__ + (j + k * oc_dim2) * oc_dim1] = coef_oe__ * a1cf[i__ 
			+ (j + k * a1cf_dim2) * a1cf_dim1] + coef_oem1__ * 
			a1cf[i__ - 1 + (j + k * a1cf_dim2) * a1cf_dim1] + 
			coef_on__ * a2cf[i__ + (j + k * a2cf_dim2) * 
			a2cf_dim1] + coef_onm1__ * a2cf[i__ + (j - 1 + k * 
			a2cf_dim2) * a2cf_dim1] + coef_uc__ * a3cf[i__ + (j + 
			k * a3cf_dim2) * a3cf_dim1] + coef_ucm1__ * a3cf[i__ 
			+ (j + (k - 1) * a3cf_dim2) * a3cf_dim1];
/* * */
/* *             *** east neighbor *** */
/* Computing MIN */
		i__5 = 1, i__6 = (i__4 = i__ - nxm1, abs(i__4));
		ike = min(i__5,i__6);
		oe[i__ + (j + k * oe_dim2) * oe_dim1] = ike * coef_oe__ * 
			a1cf[i__ + (j + k * a1cf_dim2) * a1cf_dim1];
		bc_cond_e__ = (1 - ike) * coef_oe__ * a1cf[i__ + (j + k * 
			a1cf_dim2) * a1cf_dim1] * gxcf[j + (k + (gxcf_dim2 << 
			1)) * gxcf_dim1];
		fc[i__ + (j + k * fc_dim2) * fc_dim1] += bc_cond_e__;
/* * */
/* *             *** north neighbor *** */
/* Computing MIN */
		i__5 = 1, i__6 = (i__4 = j - nym1, abs(i__4));
		jke = min(i__5,i__6);
		on[i__ + (j + k * on_dim2) * on_dim1] = jke * coef_on__ * 
			a2cf[i__ + (j + k * a2cf_dim2) * a2cf_dim1];
		bc_cond_n__ = (1 - jke) * coef_on__ * a2cf[i__ + (j + k * 
			a2cf_dim2) * a2cf_dim1] * gycf[i__ + (k + (gycf_dim2 
			<< 1)) * gycf_dim1];
		fc[i__ + (j + k * fc_dim2) * fc_dim1] += bc_cond_n__;
/* * */
/* *             *** up neighbor *** */
/* Computing MIN */
		i__5 = 1, i__6 = (i__4 = k - nzm1, abs(i__4));
		kke = min(i__5,i__6);
		uc[i__ + (j + k * uc_dim2) * uc_dim1] = kke * coef_uc__ * 
			a3cf[i__ + (j + k * a3cf_dim2) * a3cf_dim1];
		bc_cond_u__ = (1 - kke) * coef_uc__ * a3cf[i__ + (j + k * 
			a3cf_dim2) * a3cf_dim1] * gzcf[i__ + (j + (gzcf_dim2 
			<< 1)) * gzcf_dim1];
		fc[i__ + (j + k * fc_dim2) * fc_dim1] += bc_cond_u__;
/* * */
/* *             *** west neighbor (just handle b.c.) *** */
/* Computing MIN */
		i__5 = 1, i__6 = (i__4 = i__ - 2, abs(i__4));
		ike = min(i__5,i__6);
		bc_cond_w__ = (1 - ike) * coef_oem1__ * a1cf[i__ - 1 + (j + k 
			* a1cf_dim2) * a1cf_dim1] * gxcf[j + (k + gxcf_dim2) *
			 gxcf_dim1];
		fc[i__ + (j + k * fc_dim2) * fc_dim1] += bc_cond_w__;
/* * */
/* *             *** south neighbor (just handle b.c.) *** */
/* Computing MIN */
		i__5 = 1, i__6 = (i__4 = j - 2, abs(i__4));
		jke = min(i__5,i__6);
		bc_cond_s__ = (1 - jke) * coef_onm1__ * a2cf[i__ + (j - 1 + k 
			* a2cf_dim2) * a2cf_dim1] * gycf[i__ + (k + gycf_dim2)
			 * gycf_dim1];
		fc[i__ + (j + k * fc_dim2) * fc_dim1] += bc_cond_s__;
/* * */
/* *             *** down neighbor (just handle b.c.) *** */
/* Computing MIN */
		i__5 = 1, i__6 = (i__4 = k - 2, abs(i__4));
		kke = min(i__5,i__6);
		bc_cond_d__ = (1 - kke) * coef_ucm1__ * a3cf[i__ + (j + (k - 
			1) * a3cf_dim2) * a3cf_dim1] * gzcf[i__ + (j + 
			gzcf_dim2) * gzcf_dim1];
		fc[i__ + (j + k * fc_dim2) * fc_dim1] += bc_cond_d__;
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* builda_fv__ */

/* Subroutine */ int builda_fe__(integer *nx, integer *ny, integer *nz, 
	integer *ipkey, integer *numdia, integer *ipc, doublereal *rpc, 
	doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, 
	doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, 
	doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, 
	doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, 
	doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, 
	doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *
	a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf)
{
    /* System generated locals */
    integer a1cf_dim1, a1cf_dim2, a1cf_offset, a2cf_dim1, a2cf_dim2, 
	    a2cf_offset, a3cf_dim1, a3cf_dim2, a3cf_offset, ccf_dim1, 
	    ccf_dim2, ccf_offset, fcf_dim1, fcf_dim2, fcf_offset, oe_dim1, 
	    oe_dim2, oe_offset, on_dim1, on_dim2, on_offset, uc_dim1, uc_dim2,
	     uc_offset, one_dim1, one_dim2, one_offset, onw_dim1, onw_dim2, 
	    onw_offset, ue_dim1, ue_dim2, ue_offset, uw_dim1, uw_dim2, 
	    uw_offset, un_dim1, un_dim2, un_offset, us_dim1, us_dim2, 
	    us_offset, une_dim1, une_dim2, une_offset, unw_dim1, unw_dim2, 
	    unw_offset, use_dim1, use_dim2, use_offset, usw_dim1, usw_dim2, 
	    usw_offset, cc_dim1, cc_dim2, cc_offset, fc_dim1, fc_dim2, 
	    fc_offset, oc_dim1, oc_dim2, oc_offset, gxcf_dim1, gxcf_dim2, 
	    gxcf_offset, gycf_dim1, gycf_dim2, gycf_offset, gzcf_dim1, 
	    gzcf_dim2, gzcf_offset, i__1, i__2, i__3, i__4, i__5, i__6, i__7, 
	    i__8, i__9, i__10, i__11, i__12;

    /* Local variables */
    static integer i__, j, k;
    static doublereal hx, hy, hz;
    static integer ike, jke, kke;
    static doublereal hxm1, hym1, hzm1;
    static integer nxm1, nym1, nzm1;
    static doublereal diag, coef_fc__, coef_uc__;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    finite element method discretization of a 3d pde on a */
/* *    tensor product (axi-parallel) three-dimensional mesh. */
/* * */
/* *    KEY RESTRICTION: the coefficients in the pde below must */
/* *                     be piecewise constant in the elements */
/* *                     for this discretization to be formally */
/* *                     correct. */
/* * */
/* *    this subroutine discretizes the elliptic boundary value problem: */
/* * */
/* *          lu = f, u in omega */
/* *           u = g, u on boundary of omega */
/* * */
/* *    the multigrid code requires the operator in the form: */
/* * */
/* *         - \nabla \cdot (a \nabla u) + b \cdot u + c u = f */
/* * */
/* *    or: */
/* * */
/* *        lu = (a11 u_x)_x + (a22 u_y)_y + (a33 u_z)_z */
/* *             + b1 u_x + b2 u_y + b3 u_z + c u */
/* * */
/* *    here, we consider only the case: b=b1=b2=b3=0. */
/* *    then we assume: */
/* * */
/* *    the tensor a=diag(a11,a22,a33) has components which are */
/* *    then scalar functions, a11(x,y,z),a22(x,y,z),a33(x,y,z) */
/* *    and the functions c(x,y,z) and f(x,y,z) are also scalar. */
/* *    functions.  All are allowed to be possibly discontinuous on */
/* *    omega (the discontinuities must be along grid lines on fine grid). */
/* *    the boundary function g(x,y,z) is smooth on boundary of omega. */
/* * */
/* *    we will take the following conventions: */
/* *    (north,south,east,west refers to x-y plane. */
/* *    up/down refers to the z-axis) */
/* *      (u(x+h_x,y,z) = u^+   (east neighbor of u(x,y,z)) */
/* *      (u(x-h_x,y,z) = u^-   (west neighbor of u(x,y,z)) */
/* *      (u(x,y+h_y,z) = u_+   (north neighbor of u(x,y,z)) */
/* *      (u(x,y-h_y,z) = u_-   (south neighbor of u(x,y,z)) */
/* *      (u(x,y,z+h_z) = u.+   (up neighbor of u(x,y,z)) */
/* *      (u(x,y,z-h_z) = u.-   (down neighbor u(x,y,z)) */
/* * */
/* *    below, we will denote: */
/* *          u(x+h_x,y,z)       as u^+ */
/* *          u(x+(1/2)h_x,y,z)  as u^++ */
/* *          u(x-h_x,y,z)       as u^+ */
/* *          u(x-(1/2)h_x,y,z)  as u^-- */
/* *    and similarly for u_-,u_--,u_+,u_++,u.-,u.--,u.+,u.++. */
/* * */
/* *    we use trilinear basis functions and hexahedral elements */
/* *    to perform this standard finite element discretization, */
/* *    which results in the following difference scheme: */
/* * */
/* *    u            : [ + (a11^++ + a11^--) * (h_y*h_z/h_x) */
/* *                     + (a22_++ + a22_--) * (h_x*h_z/h_y) */
/* *                     + (a33.++ + a33.--) * (h_x*h_y/h_z) */
/* *                     + c * (h_x*h_y*h_z) ] u */
/* *    u^+ (e nbr)  : [ - (a11^++) * (h_y*h_z/h_x) ] */
/* *    u^_ (w nbr)  : [ - (a11^--) * (h_y*h_z/h_x) ] */
/* *    u_+ (n nbr)  : [ - (a22_++) * (h_x*h_z/h_y) ] */
/* *    u_- (s nbr)  : [ - (a22_--) * (h_x*h_z/h_y) ] */
/* *    u.+ (u nbr)  : [ - (a33.++) * (h_x*h_y/h_z) ] */
/* *    u.- (d nbr)  : [ - (a33.--) * (h_x*h_y/h_z) ] */
/* *    f            : [ h_x*h_y*h_z ] f */
/* * */
/* *    note: fast way to do a conditional: we wish to set (a=coef), */
/* *          unless we are on the (z=0)-boundary, which occurs with k=1: */
/* * */
/* *             coef = ...etc... */
/* *             ike  = min0(1,iabs(k-1)) */
/* *             a (index1) = (ike)*coef */
/* *             b(index2) = b(index2) - (1-ike)*coef*bnd_data */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** save the problem key with this operator *** */
    /* Parameter adjustments */
    gzcf_dim1 = *nx;
    gzcf_dim2 = *ny;
    gzcf_offset = 1 + gzcf_dim1 * (1 + gzcf_dim2);
    gzcf -= gzcf_offset;
    fcf_dim1 = *nx;
    fcf_dim2 = *ny;
    fcf_offset = 1 + fcf_dim1 * (1 + fcf_dim2);
    fcf -= fcf_offset;
    ccf_dim1 = *nx;
    ccf_dim2 = *ny;
    ccf_offset = 1 + ccf_dim1 * (1 + ccf_dim2);
    ccf -= ccf_offset;
    a3cf_dim1 = *nx;
    a3cf_dim2 = *ny;
    a3cf_offset = 1 + a3cf_dim1 * (1 + a3cf_dim2);
    a3cf -= a3cf_offset;
    a2cf_dim1 = *nx;
    a2cf_dim2 = *ny;
    a2cf_offset = 1 + a2cf_dim1 * (1 + a2cf_dim2);
    a2cf -= a2cf_offset;
    a1cf_dim1 = *nx;
    a1cf_dim2 = *ny;
    a1cf_offset = 1 + a1cf_dim1 * (1 + a1cf_dim2);
    a1cf -= a1cf_offset;
    gycf_dim1 = *nx;
    gycf_dim2 = *nz;
    gycf_offset = 1 + gycf_dim1 * (1 + gycf_dim2);
    gycf -= gycf_offset;
    gxcf_dim1 = *ny;
    gxcf_dim2 = *nz;
    gxcf_offset = 1 + gxcf_dim1 * (1 + gxcf_dim2);
    gxcf -= gxcf_offset;
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
    --xf;
    --yf;
    --zf;

    /* Function Body */
    ipc[10] = *ipkey;
/* * */
/* *    *** note how many nonzeros in this discretization stencil */
    ipc[11] = 27;
    ipc[12] = 1;
    *numdia = 14;
/* * */
/* *    *** define n and determine number of mesh points *** */
    nxm1 = *nx - 1;
    nym1 = *ny - 1;
    nzm1 = *nz - 1;
/* * */
/* *    *** determine diag scale factor *** */
/* *    *** (would like something close to ones on the main diagonal) *** */
    diag = 1.;
/* * */
/* * ********************************************************************* */
/* * *** interior points *** */
/* * ********************************************************************* */
/* * */
/* *    *** build the operator *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
	hzm1 = zf[k] - zf[k - 1];
	hz = zf[k + 1] - zf[k];
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
	    hym1 = yf[j] - yf[j - 1];
	    hy = yf[j + 1] - yf[j];
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		hxm1 = xf[i__] - xf[i__ - 1];
		hx = xf[i__ + 1] - xf[i__];
/* * */
/* *             *** some coefficients *** */
		coef_uc__ = hx * hy / (hz * 2.);
		coef_fc__ = hx * hy * hz;
/* * */
/* *             *** the coefficient and source function *** */
		fc[i__ + (j + k * fc_dim2) * fc_dim1] = coef_fc__ * fcf[i__ + 
			(j + k * fcf_dim2) * fcf_dim1];
		cc[i__ + (j + k * cc_dim2) * cc_dim1] = coef_fc__ * ccf[i__ + 
			(j + k * ccf_dim2) * ccf_dim1];
/* * */
/* *             *** the diagonal for matvecs and smoothings *** */
		oc[i__ + (j + k * oc_dim2) * oc_dim1] = coef_uc__ * 32. / 6.;
/* * */
/* *             *** east neighbor *** */
/* Computing MIN */
		i__5 = 1, i__6 = (i__4 = i__ - nxm1, abs(i__4));
		ike = min(i__5,i__6);
		oe[i__ + (j + k * oe_dim2) * oe_dim1] = 0.;
/* * */
/* *             *** north neighbor *** */
/* Computing MIN */
		i__5 = 1, i__6 = (i__4 = j - nym1, abs(i__4));
		jke = min(i__5,i__6);
		on[i__ + (j + k * on_dim2) * on_dim1] = 0.;
/* * */
/* *             *** up neighbor *** */
/* Computing MIN */
		i__5 = 1, i__6 = (i__4 = k - nzm1, abs(i__4));
		kke = min(i__5,i__6);
		uc[i__ + (j + k * uc_dim2) * uc_dim1] = 0.;
/* * */
/* *             *** north-east neighbor *** */
/* Computing MIN */
		i__6 = 1, i__7 = (i__4 = i__ - nxm1, abs(i__4));
/* Computing MIN */
		i__8 = 1, i__9 = (i__5 = j - nym1, abs(i__5));
		ike = min(i__6,i__7) * min(i__8,i__9);
		one[i__ + (j + k * one_dim2) * one_dim1] = ike * coef_uc__ * 
			2. / 6.;
/* * */
/* *             *** north-west neighbor *** */
/* Computing MIN */
		i__6 = 1, i__7 = (i__4 = i__ - 2, abs(i__4));
/* Computing MIN */
		i__8 = 1, i__9 = (i__5 = j - nym1, abs(i__5));
		ike = min(i__6,i__7) * min(i__8,i__9);
		onw[i__ + (j + k * onw_dim2) * onw_dim1] = ike * coef_uc__ * 
			2. / 6.;
/* * */
/* *             *** up-east neighbor *** */
/* Computing MIN */
		i__6 = 1, i__7 = (i__4 = i__ - nxm1, abs(i__4));
/* Computing MIN */
		i__8 = 1, i__9 = (i__5 = k - nzm1, abs(i__5));
		ike = min(i__6,i__7) * min(i__8,i__9);
		ue[i__ + (j + k * ue_dim2) * ue_dim1] = ike * coef_uc__ * 2. /
			 6.;
/* * */
/* *             *** up-west neighbor *** */
/* Computing MIN */
		i__6 = 1, i__7 = (i__4 = i__ - 2, abs(i__4));
/* Computing MIN */
		i__8 = 1, i__9 = (i__5 = k - nzm1, abs(i__5));
		ike = min(i__6,i__7) * min(i__8,i__9);
		uw[i__ + (j + k * uw_dim2) * uw_dim1] = ike * coef_uc__ * 2. /
			 6.;
/* * */
/* *             *** up-north neighbor *** */
/* Computing MIN */
		i__6 = 1, i__7 = (i__4 = j - nym1, abs(i__4));
/* Computing MIN */
		i__8 = 1, i__9 = (i__5 = k - nzm1, abs(i__5));
		ike = min(i__6,i__7) * min(i__8,i__9);
		un[i__ + (j + k * un_dim2) * un_dim1] = ike * coef_uc__ * 2. /
			 6.;
/* * */
/* *             *** up-south neighbor *** */
/* Computing MIN */
		i__6 = 1, i__7 = (i__4 = j - 2, abs(i__4));
/* Computing MIN */
		i__8 = 1, i__9 = (i__5 = k - nzm1, abs(i__5));
		ike = min(i__6,i__7) * min(i__8,i__9);
		us[i__ + (j + k * us_dim2) * us_dim1] = ike * coef_uc__ * 2. /
			 6.;
/* * */
/* *             *** up-north-east neighbor *** */
/* Computing MIN */
		i__7 = 1, i__8 = (i__4 = i__ - nxm1, abs(i__4));
/* Computing MIN */
		i__9 = 1, i__10 = (i__5 = j - nym1, abs(i__5));
/* Computing MIN */
		i__11 = 1, i__12 = (i__6 = k - nzm1, abs(i__6));
		ike = min(i__7,i__8) * min(i__9,i__10) * min(i__11,i__12);
		une[i__ + (j + k * une_dim2) * une_dim1] = ike * coef_uc__ * 
			1. / 6.;
/* * */
/* *             *** up-north-west neighbor *** */
/* Computing MIN */
		i__7 = 1, i__8 = (i__4 = i__ - 2, abs(i__4));
/* Computing MIN */
		i__9 = 1, i__10 = (i__5 = j - nym1, abs(i__5));
/* Computing MIN */
		i__11 = 1, i__12 = (i__6 = k - nzm1, abs(i__6));
		ike = min(i__7,i__8) * min(i__9,i__10) * min(i__11,i__12);
		unw[i__ + (j + k * unw_dim2) * unw_dim1] = ike * coef_uc__ * 
			1. / 6.;
/* * */
/* *             *** up-south-east neighbor *** */
/* Computing MIN */
		i__7 = 1, i__8 = (i__4 = i__ - nxm1, abs(i__4));
/* Computing MIN */
		i__9 = 1, i__10 = (i__5 = j - 2, abs(i__5));
/* Computing MIN */
		i__11 = 1, i__12 = (i__6 = k - nzm1, abs(i__6));
		ike = min(i__7,i__8) * min(i__9,i__10) * min(i__11,i__12);
		use[i__ + (j + k * use_dim2) * use_dim1] = ike * coef_uc__ * 
			1. / 6.;
/* * */
/* *             *** up-south-west neighbor *** */
/* Computing MIN */
		i__7 = 1, i__8 = (i__4 = i__ - 2, abs(i__4));
/* Computing MIN */
		i__9 = 1, i__10 = (i__5 = j - 2, abs(i__5));
/* Computing MIN */
		i__11 = 1, i__12 = (i__6 = k - nzm1, abs(i__6));
		ike = min(i__7,i__8) * min(i__9,i__10) * min(i__11,i__12);
		usw[i__ + (j + k * usw_dim2) * usw_dim1] = ike * coef_uc__ * 
			1. / 6.;
/* * */
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* builda_fe__ */

