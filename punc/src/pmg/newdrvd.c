/* ./src_f77/newdrvd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__3 = 3;
static integer c__0 = 0;
static integer c_n99 = -99;
static doublereal c_b23 = 0.;
static integer c__5 = 5;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    newdrvd.f */
/* * @author  Michael Holst */
/* * @brief   Driver for the Newton solver. */
/* * @version $Id: newdrvd.c,v 1.3 2010/08/12 05:45:24 fetk Exp $ */
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
/* Subroutine */ int newdriv_(integer *iparm, doublereal *rparm, integer *
	iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *
	yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *
	gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, 
	doublereal *ccf, doublereal *fcf, doublereal *tcf)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int newdriv2_(integer *, doublereal *, integer *, 
	    integer *, integer *, doublereal *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer nc, nf, nx, ny, nz, nxc, nyc, nzc, k_w1__, k_w2__, k_ac__, 
	    k_cc__, k_fc__, k_pc__, k_iz__, n_iz__, narr, nlev, niwk;
    extern /* Subroutine */ int mgsz_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *);
    static integer nrwk, mxlv, k_ipc__, n_ipc__, k_rpc__, n_rpc__, narrc, 
	    mgdisc, mgcoar;
    extern integer maxlev_(integer *, integer *, integer *);
    static integer ierror, iretot, iintot, mgsolv;

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 6, 0, 0, 0 };
    static cilist io___10 = { 0, 6, 0, 0, 0 };
    static cilist io___26 = { 0, 6, 0, 0, 0 };
    static cilist io___27 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    driver for a screaming inexact-newton-multilevel solver. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** input parameters *** */
/* * */
/* *    *** variables returned from mgsz *** */
/* * */
/* *    *** misc variables *** */
/* * */
/* *    *** decode some parameters *** */
    /* Parameter adjustments */
    --tcf;
    --fcf;
    --ccf;
    --a3cf;
    --a2cf;
    --a1cf;
    --gzcf;
    --gycf;
    --gxcf;
    --zf;
    --yf;
    --xf;
    --u;
    --rwork;
    --iwork;
    --rparm;
    --iparm;

    /* Function Body */
    nrwk = iparm[1];
    niwk = iparm[2];
    nx = iparm[3];
    ny = iparm[4];
    nz = iparm[5];
    nlev = iparm[6];
/* * */
/* *    *** some checks on input *** */
    if (nlev <= 0 || nx <= 0 || ny <= 0 || nz <= 0) {
	s_wsle(&io___7);
	do_lio(&c__9, &c__1, "% NEWDRIV:  nx,ny,nz, and nlev must be positiv"
		"e...", (ftnlen)50);
	e_wsle();
	ierror = -1;
	iparm[51] = ierror;
	return 0;
    }
    mxlv = maxlev_(&nx, &ny, &nz);
    if (nlev > mxlv) {
	s_wsle(&io___10);
	do_lio(&c__9, &c__1, "% NEWDRIV:  max levels for your grid size is: ",
		 (ftnlen)46);
	do_lio(&c__3, &c__1, (char *)&mxlv, (ftnlen)sizeof(integer));
	e_wsle();
	ierror = -2;
	iparm[51] = ierror;
	return 0;
    }
/* * */
/* *    *** basic grid sizes, etc. *** */
    mgcoar = iparm[18];
    mgdisc = iparm[19];
    mgsolv = iparm[21];
    mgsz_(&mgcoar, &mgdisc, &mgsolv, &nx, &ny, &nz, &nlev, &nxc, &nyc, &nzc, &
	    nf, &nc, &narr, &narrc, &n_rpc__, &n_iz__, &n_ipc__, &iretot, &
	    iintot);
/* * */
/* *    *** allocate space for two additional work vectors *** */
    iretot += nf << 1;
/* * */
/* *    *** some more checks on input *** */
    if (nrwk < iretot || niwk < iintot) {
	s_wsle(&io___26);
	do_lio(&c__9, &c__1, "% NEWDRIV: real    work space must be: ", (
		ftnlen)39);
	do_lio(&c__3, &c__1, (char *)&iretot, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___27);
	do_lio(&c__9, &c__1, "% NEWDRIV: integer work space must be: ", (
		ftnlen)39);
	do_lio(&c__3, &c__1, (char *)&iintot, (ftnlen)sizeof(integer));
	e_wsle();
	ierror = -3;
	iparm[51] = ierror;
	return 0;
    }
/* * */
/* *    *** split up the integer work array *** */
    k_iz__ = 1;
    k_ipc__ = k_iz__ + n_iz__;
/* * */
/* *    *** split up the real work array *** */
    k_rpc__ = 1;
    k_cc__ = k_rpc__ + n_rpc__;
    k_fc__ = k_cc__ + narr;
    k_w1__ = k_fc__ + narr;
    k_w2__ = k_w1__ + nf;
    k_pc__ = k_w2__ + nf;
    k_ac__ = k_pc__ + narrc * 27;
/* * ***k_ac_after = 4*nf + 14*narrc */
/* * */
/* *    *** call the multigrid driver *** */
    newdriv2_(&iparm[1], &rparm[1], &nx, &ny, &nz, &u[1], &iwork[k_iz__], &
	    rwork[k_w1__], &rwork[k_w2__], &iwork[k_ipc__], &rwork[k_rpc__], &
	    rwork[k_pc__], &rwork[k_ac__], &rwork[k_cc__], &rwork[k_fc__], &
	    xf[1], &yf[1], &zf[1], &gxcf[1], &gycf[1], &gzcf[1], &a1cf[1], &
	    a2cf[1], &a3cf[1], &ccf[1], &fcf[1], &tcf[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* newdriv_ */

/* Subroutine */ int newdriv2_(integer *iparm, doublereal *rparm, integer *nx,
	 integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *w1,
	 doublereal *w2, integer *ipc, doublereal *rpc, doublereal *pc, 
	doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, 
	doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, 
	doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *
	a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf)
{
    /* Format strings */
    static char fmt_100[] = "(\002 ];\002,4(\002 \002,a7,\002=\002,1pe9.3"
	    ",\002;\002))";

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void), s_wsfe(cilist *), do_fio(integer *, char *, ftnlen),
	     e_wsfe(void);

    /* Local variables */
    extern /* Subroutine */ int buildalg_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), buildops_(integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), 
	    buildstr_(integer *, integer *, integer *, integer *, integer *);
    static integer nlev_real__;
    static doublereal bf, oh;
    static integer nu1, nu2, ido, iok, mode, ilev, nlev, iinfo, mgkey, itmax, 
	    ipkey, iters, istop;
    extern /* Subroutine */ int tstop_(doublereal *, doublereal *, doublereal 
	    *);
    static doublereal omegal;
    static integer mgdisc;
    static doublereal omegan;
    static integer mgcoar;
    extern doublereal epsmac_(integer *);
    extern /* Subroutine */ int fbound_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *)
	    ;
    static integer ibound;
    static doublereal epsiln;
    static integer mgprol, mgsmoo, ierror, mgsolv;
    static doublereal errtol;
    extern /* Subroutine */ int newton_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal tsolve;
    extern /* Subroutine */ int tstart_(doublereal *, doublereal *), prtstp_(
	    integer *, integer *, doublereal *, doublereal *, doublereal *), 
	    fbound00_(integer *, integer *, integer *, doublereal *), 
	    fnewton_(integer *, integer *, integer *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , integer *, integer *, integer *, integer *, integer *, integer *
	    , integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal tsetupc, tsetupf;

    /* Fortran I/O blocks */
    static cilist io___57 = { 0, 6, 0, 0, 0 };
    static cilist io___59 = { 0, 6, 0, 0, 0 };
    static cilist io___62 = { 0, 6, 0, 0, 0 };
    static cilist io___68 = { 0, 6, 0, 0, 0 };
    static cilist io___70 = { 0, 6, 0, 0, 0 };
    static cilist io___71 = { 0, 6, 0, fmt_100, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    this routine uses a newton's method, combined with a linear */
/* *    multigrid iteration, to solve the following three-dimensional, */
/* *    2nd order elliptic partial differential equation: */
/* * */
/* *         lu = f, u in omega */
/* *          u = g, u on boundary of omega */
/* *    where */
/* * */
/* *         omega = [xmin,xmax]x[ymin,ymax]x[zmin,zmax] */
/* * */
/* *    the multigrid code requires the operator in the form: */
/* * */
/* *         - \nabla \cdot (a \nabla u) + c(u) = f */
/* * */
/* *    with */
/* * */
/* *        a(x,y,z),f(x,y,z), scalar functions (possibly discontinuous) */
/* *        on omega.  (discontinuities must be along fine grid lines). */
/* *        boundary function g(x,y,z) is smooth on boundary of omega. */
/* * */
/* *        the function c(u) is a possibly nonlinear function of the */
/* *        unknown u, and varies (possibly discontinuously) with the */
/* *        spatial position also. */
/* * */
/* * user inputs: */
/* * */
/* *    the user must provide the coefficients of the differential */
/* *    operator, some initial parameter settings in an integer and a */
/* *    real parameter array, and various work arrays. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** input parameters *** */
/* * */
/* *    *** misc variables *** */
/* * */
/* *    *** decode the iparm array *** */
    /* Parameter adjustments */
    --tcf;
    --fcf;
    --ccf;
    --a3cf;
    --a2cf;
    --a1cf;
    --gzcf;
    --gycf;
    --gxcf;
    --zf;
    --yf;
    --xf;
    --fc;
    --cc;
    --ac;
    --pc;
    --rpc;
    --ipc;
    --w2;
    --w1;
    --iz;
    --u;
    --rparm;
    --iparm;

    /* Function Body */
    nlev = iparm[6];
    nu1 = iparm[7];
    nu2 = iparm[8];
    mgkey = iparm[9];
    itmax = iparm[10];
    istop = iparm[11];
    iinfo = iparm[12];
    ipkey = iparm[14];
    mgprol = iparm[17];
    mgcoar = iparm[18];
    mgdisc = iparm[19];
    mgsmoo = iparm[20];
    mgsolv = iparm[21];
    errtol = rparm[1];
    omegal = rparm[9];
    omegan = rparm[10];
/* * */
/* *    *** intitialize the iteration timer *** */
    prtstp_(&c__0, &c_n99, &c_b23, &c_b23, &c_b23);
/* * */
/* *    *** build the multigrid data structure in iz *** */
    buildstr_(nx, ny, nz, &nlev, &iz[1]);
/* * */
/* *    *** start timer *** */
    tstart_(&bf, &oh);
/* * */
/* *    *** build op and rhs on fine grid *** */
    ido = 0;
    buildops_(nx, ny, nz, &nlev, &ipkey, &iinfo, &ido, &iz[1], &mgprol, &
	    mgcoar, &mgsolv, &mgdisc, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1]
	    , &fc[1], &xf[1], &yf[1], &zf[1], &gxcf[1], &gycf[1], &gzcf[1], &
	    a1cf[1], &a2cf[1], &a3cf[1], &ccf[1], &fcf[1], &tcf[1]);
/* * */
/* *    *** stop timer *** */
    tstop_(&bf, &oh, &tsetupf);
    s_wsle(&io___57);
    do_lio(&c__9, &c__1, "% NEWDRIV2: fine problem setup time: ", (ftnlen)37);
    do_lio(&c__5, &c__1, (char *)&tsetupf, (ftnlen)sizeof(doublereal));
    e_wsle();
/* * */
/* *    *** start timer *** */
    tstart_(&bf, &oh);
/* * */
/* *    *** build op and rhs on all coarse grids *** */
    ido = 1;
    buildops_(nx, ny, nz, &nlev, &ipkey, &iinfo, &ido, &iz[1], &mgprol, &
	    mgcoar, &mgsolv, &mgdisc, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1]
	    , &fc[1], &xf[1], &yf[1], &zf[1], &gxcf[1], &gycf[1], &gzcf[1], &
	    a1cf[1], &a2cf[1], &a3cf[1], &ccf[1], &fcf[1], &tcf[1]);
/* * */
/* *    *** stop timer *** */
    tstop_(&bf, &oh, &tsetupc);
    s_wsle(&io___59);
    do_lio(&c__9, &c__1, "% NEWDRIV2: coarse problem setup time: ", (ftnlen)
	    39);
    do_lio(&c__5, &c__1, (char *)&tsetupc, (ftnlen)sizeof(doublereal));
    e_wsle();
/* * */
/* * ****************************************************************** */
/* * *** this overwrites the rhs array provided by pde specification */
/* * ****** compute an algebraically produced rhs for the given tcf *** */
    mode = 1;
    if (istop == 4 || istop == 5) {
	buildalg_(nx, ny, nz, &mode, &nlev, &iz[1], &ipc[1], &rpc[1], &ac[1], 
		&cc[1], &ccf[1], &tcf[1], &fc[1], &fcf[1]);
    }
/* * ****************************************************************** */
/* * */
/* *    *** determine machine epsilon *** */
    epsiln = epsmac_(&c__0);
/* * */
/* *    *** impose zero dirichlet boundary conditions (now in source fcn) *** */
    fbound00_(nx, ny, nz, &u[1]);
/* * */
/* *    *** MATLAB *** */
    s_wsle(&io___62);
    do_lio(&c__9, &c__1, " new = [ ", (ftnlen)9);
    e_wsle();
/* * */
/* *    *** start timer *** */
    tstart_(&bf, &oh);
/* * */
/* *    *** call specified multigrid method *** */
    nlev_real__ = nlev;
    iok = 1;
    ilev = 1;
    if (mgkey == 0) {
	newton_(nx, ny, nz, &u[1], &iz[1], &ccf[1], &fcf[1], &w1[1], &w2[1], &
		istop, &itmax, &iters, &ierror, &nlev, &ilev, &nlev_real__, &
		mgsolv, &iok, &iinfo, &epsiln, &errtol, &omegan, &nu1, &nu2, &
		mgsmoo, &a1cf[1], &a2cf[1], &a3cf[1], &ipc[1], &rpc[1], &pc[1]
		, &ac[1], &cc[1], &fc[1], &tcf[1]);
    } else if (mgkey == 1) {
	fnewton_(nx, ny, nz, &u[1], &iz[1], &ccf[1], &fcf[1], &w1[1], &w2[1], 
		&istop, &itmax, &iters, &ierror, &nlev, &ilev, &nlev_real__, &
		mgsolv, &iok, &iinfo, &epsiln, &errtol, &omegan, &nu1, &nu2, &
		mgsmoo, &a1cf[1], &a2cf[1], &a3cf[1], &ipc[1], &rpc[1], &pc[1]
		, &ac[1], &cc[1], &fc[1], &tcf[1]);
    } else {
	s_wsle(&io___68);
	do_lio(&c__9, &c__1, "% NEWDRIV2: bad mgkey given ", (ftnlen)28);
	e_wsle();
    }
/* * */
/* *    *** stop timer *** */
    tstop_(&bf, &oh, &tsolve);
    s_wsle(&io___70);
    do_lio(&c__9, &c__1, "% NEWDRIV2: solve time: ", (ftnlen)24);
    do_lio(&c__5, &c__1, (char *)&tsolve, (ftnlen)sizeof(doublereal));
    e_wsle();
/* * */
/* *    *** MATLAB *** */
    s_wsfe(&io___71);
    do_fio(&c__1, "new_sf", (ftnlen)6);
    do_fio(&c__1, (char *)&tsetupf, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, "new_sc", (ftnlen)6);
    do_fio(&c__1, (char *)&tsetupc, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, "new_st", (ftnlen)6);
    d__1 = tsetupf + tsetupc;
    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, "new_so", (ftnlen)6);
    do_fio(&c__1, (char *)&tsolve, (ftnlen)sizeof(doublereal));
    e_wsfe();
/* * */
/* *    *** restore boundary conditions *** */
    ibound = 1;
    fbound_(&ibound, nx, ny, nz, &u[1], &gxcf[1], &gycf[1], &gzcf[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* newdriv2_ */

