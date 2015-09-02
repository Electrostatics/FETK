/* ./src_f77/mgdrvd.f -- translated by f2c (version 20030320).
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
/* * @file    mgdrvd.f */
/* * @author  Michael Holst */
/* * @brief   Driver for the multigrid routines. */
/* * @version $Id: mgdrvd.c,v 1.3 2010/08/12 05:45:22 fetk Exp $ */
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
/* Subroutine */ int mgdriv_(integer *iparm, doublereal *rparm, integer *
	iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *
	yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *
	gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, 
	doublereal *ccf, doublereal *fcf, doublereal *tcf)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer nc, nf, nx, ny, nz, nxc, nyc, nzc, k_ac__, k_cc__, k_fc__, 
	    k_pc__, k_iz__, n_iz__, narr, nlev, niwk;
    extern /* Subroutine */ int mgsz_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *);
    static integer nrwk, mxlv, k_ipc__, n_ipc__, k_rpc__, n_rpc__, narrc, 
	    mgdisc, mgcoar;
    extern integer maxlev_(integer *, integer *, integer *);
    static integer ierror, iretot, iintot, mgsolv;
    extern /* Subroutine */ int mgdriv2_(integer *, doublereal *, integer *, 
	    integer *, integer *, doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 6, 0, 0, 0 };
    static cilist io___10 = { 0, 6, 0, 0, 0 };
    static cilist io___26 = { 0, 6, 0, 0, 0 };
    static cilist io___27 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    multilevel solver driver. */
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
	do_lio(&c__9, &c__1, "% MGDRIV:  nx,ny,nz, and nlev must be positive"
		"...", (ftnlen)49);
	e_wsle();
	ierror = -1;
	iparm[51] = ierror;
	return 0;
    }
    mxlv = maxlev_(&nx, &ny, &nz);
    if (nlev > mxlv) {
	s_wsle(&io___10);
	do_lio(&c__9, &c__1, "% MGDRIV:  max levels for your grid size is: ", 
		(ftnlen)45);
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
/* *    *** some more checks on input *** */
    if (nrwk < iretot || niwk < iintot) {
	s_wsle(&io___26);
	do_lio(&c__9, &c__1, "% MGDRIV: real    work space must be: ", (
		ftnlen)38);
	do_lio(&c__3, &c__1, (char *)&iretot, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___27);
	do_lio(&c__9, &c__1, "% MGDRIV: integer work space must be: ", (
		ftnlen)38);
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
    k_pc__ = k_fc__ + narr;
    k_ac__ = k_pc__ + narrc * 27;
/* * ***k_ac_after =  4*nf +  4*narrc */
/* * ***k_ac_after =  4*nf + 14*narrc */
/* * ***k_ac_after = 14*nf + 14*narrc */
/* * */
/* *    *** call the multigrid driver *** */
    mgdriv2_(&iparm[1], &rparm[1], &nx, &ny, &nz, &u[1], &iwork[k_iz__], &
	    iwork[k_ipc__], &rwork[k_rpc__], &rwork[k_pc__], &rwork[k_ac__], &
	    rwork[k_cc__], &rwork[k_fc__], &xf[1], &yf[1], &zf[1], &gxcf[1], &
	    gycf[1], &gzcf[1], &a1cf[1], &a2cf[1], &a3cf[1], &ccf[1], &fcf[1],
	     &tcf[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* mgdriv_ */

/* Subroutine */ int mgdriv2_(integer *iparm, doublereal *rparm, integer *nx, 
	integer *ny, integer *nz, doublereal *u, integer *iz, integer *ipc, 
	doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, 
	doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, 
	doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *
	a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal 
	*fcf, doublereal *tcf)
{
    /* Format strings */
    static char fmt_200[] = "(a,\002 [\002,i3,\002,\002,i3,\002,\002,i3,\002"
	    "] \002)";
    static char fmt_100[] = "(\002 ];\002,4(\002 \002,a7,\002=\002,1pe9.3"
	    ",\002;\002))";

    /* System generated locals */
    integer i__1;
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
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal errtol_p__;
    extern /* Subroutine */ int buildstr_(integer *, integer *, integer *, 
	    integer *, integer *);
    static integer nlev_real__;
    static doublereal bf, oh;
    static integer nu1, nu2, ido, iok, nxc, nyc, nzc, nxf, nyf, nzf;
    static doublereal rho_min_mod__, rho_max_mod__;
    static integer mode, ilev, nlev;
    extern /* Subroutine */ int mvcs_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static integer iok_p__, iinfo, iperf;
    static doublereal rho_p__;
    static integer level, nlevd, mgkey;
    extern /* Subroutine */ int mvfas_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), fmvcs_(
	    integer *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *, integer *, integer *, integer *, integer *,
	     integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer itmax, ipkey, iters;
    extern /* Subroutine */ int power_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *);
    static integer istop;
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
    extern /* Subroutine */ int fmvfas_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal epsiln;
    extern /* Subroutine */ int mkcors_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *);
    static integer mgprol, mgsmoo, ierror;
    extern /* Subroutine */ int azeros_(integer *, integer *, integer *, 
	    doublereal *), ipower_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, integer 
	    *, integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static integer mgsolv;
    static doublereal errtol;
    extern /* Subroutine */ int mpower_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , integer *, integer *, integer *, integer *, integer *, integer *
	    , integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal tsolve;
    extern /* Subroutine */ int tstart_(doublereal *, doublereal *), prtstp_(
	    integer *, integer *, doublereal *, doublereal *, doublereal *), 
	    fbound00_(integer *, integer *, integer *, doublereal *);
    static integer iinfo_p__;
    static doublereal rho_min__, rho_max__;
    static integer itmax_p__, iters_p__;
    static doublereal tsetupc, tsetupf;

    /* Fortran I/O blocks */
    static cilist io___57 = { 0, 6, 0, 0, 0 };
    static cilist io___59 = { 0, 6, 0, 0, 0 };
    static cilist io___72 = { 0, 6, 0, 0, 0 };
    static cilist io___73 = { 0, 6, 0, fmt_200, 0 };
    static cilist io___74 = { 0, 6, 0, 0, 0 };
    static cilist io___80 = { 0, 6, 0, 0, 0 };
    static cilist io___81 = { 0, 6, 0, 0, 0 };
    static cilist io___82 = { 0, 6, 0, 0, 0 };
    static cilist io___83 = { 0, 6, 0, 0, 0 };
    static cilist io___86 = { 0, 6, 0, 0, 0 };
    static cilist io___87 = { 0, 6, 0, 0, 0 };
    static cilist io___88 = { 0, 6, 0, 0, 0 };
    static cilist io___89 = { 0, 6, 0, 0, 0 };
    static cilist io___90 = { 0, 6, 0, 0, 0 };
    static cilist io___91 = { 0, 6, 0, 0, 0 };
    static cilist io___93 = { 0, 6, 0, 0, 0 };
    static cilist io___94 = { 0, 6, 0, 0, 0 };
    static cilist io___95 = { 0, 6, 0, 0, 0 };
    static cilist io___96 = { 0, 6, 0, 0, 0 };
    static cilist io___97 = { 0, 6, 0, 0, 0 };
    static cilist io___98 = { 0, 6, 0, 0, 0 };
    static cilist io___103 = { 0, 6, 0, 0, 0 };
    static cilist io___104 = { 0, 6, 0, 0, 0 };
    static cilist io___105 = { 0, 6, 0, 0, 0 };
    static cilist io___107 = { 0, 6, 0, 0, 0 };
    static cilist io___108 = { 0, 6, 0, fmt_100, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    this routine uses a multigrid method to solve the following */
/* *    three-dimensional, 2nd order elliptic partial differential */
/* *    equation: */
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
/* *    *** more misc variables *** */
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
    iz -= 51;
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
    mode = iparm[16];
    mgprol = iparm[17];
    mgcoar = iparm[18];
    mgdisc = iparm[19];
    mgsmoo = iparm[20];
    mgsolv = iparm[21];
    iperf = iparm[22];
    errtol = rparm[1];
    omegal = rparm[9];
    omegan = rparm[10];
/* * */
/* *    *** intitialize the iteration timer *** */
    prtstp_(&c__0, &c_n99, &c_b23, &c_b23, &c_b23);
/* * */
/* *    *** build the multigrid data structure in iz *** */
    buildstr_(nx, ny, nz, &nlev, &iz[51]);
/* * */
/* *    *** start timer *** */
    tstart_(&bf, &oh);
/* * */
/* *    *** build op and rhs on fine grid *** */
    ido = 0;
    buildops_(nx, ny, nz, &nlev, &ipkey, &iinfo, &ido, &iz[51], &mgprol, &
	    mgcoar, &mgsolv, &mgdisc, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1]
	    , &fc[1], &xf[1], &yf[1], &zf[1], &gxcf[1], &gycf[1], &gzcf[1], &
	    a1cf[1], &a2cf[1], &a3cf[1], &ccf[1], &fcf[1], &tcf[1]);
/* * */
/* *    *** stop timer *** */
    tstop_(&bf, &oh, &tsetupf);
    s_wsle(&io___57);
    do_lio(&c__9, &c__1, "% MGDRIV2: fine problem setup time: ", (ftnlen)36);
    do_lio(&c__5, &c__1, (char *)&tsetupf, (ftnlen)sizeof(doublereal));
    e_wsle();
/* * */
/* *    *** start timer *** */
    tstart_(&bf, &oh);
/* * */
/* *    *** build op and rhs on all coarse grids *** */
    ido = 1;
    buildops_(nx, ny, nz, &nlev, &ipkey, &iinfo, &ido, &iz[51], &mgprol, &
	    mgcoar, &mgsolv, &mgdisc, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1]
	    , &fc[1], &xf[1], &yf[1], &zf[1], &gxcf[1], &gycf[1], &gzcf[1], &
	    a1cf[1], &a2cf[1], &a3cf[1], &ccf[1], &fcf[1], &tcf[1]);
/* * */
/* *    *** stop timer *** */
    tstop_(&bf, &oh, &tsetupc);
    s_wsle(&io___59);
    do_lio(&c__9, &c__1, "% MGDRIV2: coarse problem setup time: ", (ftnlen)38)
	    ;
    do_lio(&c__5, &c__1, (char *)&tsetupc, (ftnlen)sizeof(doublereal));
    e_wsle();
/* * */
/* *    *** determine machine epsilon *** */
    epsiln = epsmac_(&c__0);
/* * */
/* * ****************************************************************** */
/* * *** analysis *** */
/* * *** note: we destroy the rhs function "fc" here in "mpower" *** */
/* * ****************************************************************** */
/* * */
/* *    *** errtol and itmax *** */
    itmax_p__ = 1000;
    iok_p__ = 0;
    nlev_real__ = nlev;
    nlevd = nlev_real__;
/* * */
/* *    *** finest level initialization *** */
    nxf = *nx;
    nyf = *ny;
    nzf = *nz;
/* * */
/* *    *** go down grids: compute max/min eigenvalues of all operators *** */
    i__1 = nlev_real__;
    for (level = 1; level <= i__1; ++level) {
	nlevd = nlev_real__ - level + 1;
/* * */
/* *       *** move down the grids *** */
	if (level != 1) {
/* * */
/* *          *** find new grid size *** */
	    mkcors_(&c__1, &nxf, &nyf, &nzf, &nxc, &nyc, &nzc);
/* * */
/* *          *** new grid size *** */
	    nxf = nxc;
	    nyf = nyc;
	    nzf = nzc;
	}
	s_wsle(&io___72);
	do_lio(&c__9, &c__1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
		 (ftnlen)46);
	do_lio(&c__9, &c__1, "%%%%%%%%%%", (ftnlen)10);
	e_wsle();
	s_wsfe(&io___73);
	do_fio(&c__1, "% MGDRIV2: ANALYSIS==>", (ftnlen)22);
	do_fio(&c__1, (char *)&nxf, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nyf, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nzf, (ftnlen)sizeof(integer));
	e_wsfe();
/* * */
/* *       *** largest eigenvalue of the system matrix A *** */
	if (iperf == 1 || iperf == 3) {
	    s_wsle(&io___74);
	    do_lio(&c__9, &c__1, "% MGDRIV2: power calculating rho(A)...", (
		    ftnlen)38);
	    e_wsle();
	    iters_p__ = 0;
	    iinfo_p__ = iinfo;
	    errtol_p__ = 1e-4f;
	    power_(&nxf, &nyf, &nzf, &iz[51], &level, &ipc[1], &rpc[1], &ac[1]
		    , &cc[1], &a1cf[1], &a2cf[1], &a3cf[1], &ccf[1], &
		    rho_max__, &rho_max_mod__, &errtol_p__, &itmax_p__, &
		    iters_p__, &iinfo_p__);
	    s_wsle(&io___80);
	    do_lio(&c__9, &c__1, "% MGDRIV2: power iters   = ", (ftnlen)27);
	    do_lio(&c__3, &c__1, (char *)&iters_p__, (ftnlen)sizeof(integer));
	    e_wsle();
	    s_wsle(&io___81);
	    do_lio(&c__9, &c__1, "% MGDRIV2: power eigmax  = ", (ftnlen)27);
	    do_lio(&c__5, &c__1, (char *)&rho_max__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___82);
	    do_lio(&c__9, &c__1, "% MGDRIV2: power (MODEL) = ", (ftnlen)27);
	    do_lio(&c__5, &c__1, (char *)&rho_max_mod__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
/* * */
/* *          *** smallest eigenvalue of the system matrix A *** */
	    s_wsle(&io___83);
	    do_lio(&c__9, &c__1, "% MGDRIV2: ipower calculating lambda_min(A"
		    ")...", (ftnlen)46);
	    e_wsle();
	    iters_p__ = 0;
	    iinfo_p__ = iinfo;
	    errtol_p__ = 1e-4f;
	    azeros_(&nxf, &nyf, &nzf, &u[1]);
	    ipower_(&nxf, &nyf, &nzf, &u[1], &iz[51], &a1cf[1], &a2cf[1], &
		    a3cf[1], &ccf[1], &fcf[1], &rho_min__, &rho_min_mod__, &
		    errtol_p__, &itmax_p__, &iters_p__, &nlevd, &level, &
		    nlev_real__, &mgsolv, &iok_p__, &iinfo_p__, &epsiln, &
		    errtol, &omegal, &nu1, &nu2, &mgsmoo, &ipc[1], &rpc[1], &
		    pc[1], &ac[1], &cc[1], &tcf[1]);
	    s_wsle(&io___86);
	    do_lio(&c__9, &c__1, "% MGDRIV2: ipower iters   = ", (ftnlen)28);
	    do_lio(&c__3, &c__1, (char *)&iters_p__, (ftnlen)sizeof(integer));
	    e_wsle();
	    s_wsle(&io___87);
	    do_lio(&c__9, &c__1, "% MGDRIV2: ipower eigmin  = ", (ftnlen)28);
	    do_lio(&c__5, &c__1, (char *)&rho_min__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___88);
	    do_lio(&c__9, &c__1, "% MGDRIV2: ipower (MODEL) = ", (ftnlen)28);
	    do_lio(&c__5, &c__1, (char *)&rho_min_mod__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
/* * */
/* *          *** condition number estimate *** */
	    s_wsle(&io___89);
	    do_lio(&c__9, &c__1, "% MGDRIV2: condition number  = ", (ftnlen)
		    31);
	    d__1 = rho_max__ / rho_min__;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___90);
	    do_lio(&c__9, &c__1, "% MGDRIV2: condition (MODEL) = ", (ftnlen)
		    31);
	    d__1 = rho_max_mod__ / rho_min_mod__;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	}
/* * */
/* *       *** spectral radius of the multigrid operator M *** */
/* *       *** NOTE: due to lack of vectors, we destroy "fc" in mpower... *** */
	if (iperf == 2 || iperf == 3) {
	    s_wsle(&io___91);
	    do_lio(&c__9, &c__1, "% MGDRIV2: mpower calculating rho(M)...", (
		    ftnlen)39);
	    e_wsle();
	    iters_p__ = 0;
	    iinfo_p__ = iinfo;
	    errtol_p__ = epsiln;
	    azeros_(&nxf, &nyf, &nzf, &u[iz[level * 50 + 1]]);
	    mpower_(&nxf, &nyf, &nzf, &u[1], &iz[51], &a1cf[1], &a2cf[1], &
		    a3cf[1], &ccf[1], &fcf[1], &rho_p__, &errtol_p__, &
		    itmax_p__, &iters_p__, &nlevd, &level, &nlev_real__, &
		    mgsolv, &iok_p__, &iinfo_p__, &epsiln, &errtol, &omegal, &
		    nu1, &nu2, &mgsmoo, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[
		    1], &fc[1], &tcf[1]);
	    s_wsle(&io___93);
	    do_lio(&c__9, &c__1, "% MGDRIV2: mpower iters  = ", (ftnlen)27);
	    do_lio(&c__3, &c__1, (char *)&iters_p__, (ftnlen)sizeof(integer));
	    e_wsle();
	    s_wsle(&io___94);
	    do_lio(&c__9, &c__1, "% MGDRIV2: mpower rho(M) = ", (ftnlen)27);
	    do_lio(&c__5, &c__1, (char *)&rho_p__, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsle();
	}
/* * */
/* *       *** reinitialize the solution function *** */
	azeros_(&nxf, &nyf, &nzf, &u[iz[level * 50 + 1]]);
/* * */
/* *    *** next grid *** */
/* L40: */
    }
    s_wsle(&io___95);
    do_lio(&c__9, &c__1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
	    "%%%%%%", (ftnlen)56);
    e_wsle();
/* * */
/* *    *** reinitialize the solution function *** */
    azeros_(nx, ny, nz, &u[1]);
/* * */
/* * ****************************************************************** */
/* * *** this overwrites the rhs array provided by pde specification */
/* * ****** compute an algebraically produced rhs for the given tcf *** */
    if (istop == 4 || istop == 5 || iperf != 0) {
	s_wsle(&io___96);
	do_lio(&c__9, &c__1, "% MGDRIV2: generating algebraic RHS from your "
		"soln...", (ftnlen)53);
	e_wsle();
	buildalg_(nx, ny, nz, &mode, &nlev, &iz[51], &ipc[1], &rpc[1], &ac[1],
		 &cc[1], &ccf[1], &tcf[1], &fc[1], &fcf[1]);
    }
/* * ****************************************************************** */
/* * */
/* *    *** impose zero dirichlet boundary conditions (now in source fcn) *** */
    fbound00_(nx, ny, nz, &u[1]);
/* * */
/* *    *** MATLAB *** */
    s_wsle(&io___97);
    do_lio(&c__9, &c__1, " mg = [ ", (ftnlen)8);
    e_wsle();
/* * */
/* *    *** start timer *** */
    tstart_(&bf, &oh);
/* * */
/* *    *** call specified multigrid method *** */
    if (mode == 0 || mode == 2) {
	s_wsle(&io___98);
	do_lio(&c__9, &c__1, "% MGDRIV2: linear mode...", (ftnlen)25);
	e_wsle();
	nlev_real__ = nlev;
	iok = 1;
	ilev = 1;
	if (mgkey == 0) {
	    mvcs_(nx, ny, nz, &u[1], &iz[51], &a1cf[1], &a2cf[1], &a3cf[1], &
		    ccf[1], &istop, &itmax, &iters, &ierror, &nlev, &ilev, &
		    nlev_real__, &mgsolv, &iok, &iinfo, &epsiln, &errtol, &
		    omegal, &nu1, &nu2, &mgsmoo, &ipc[1], &rpc[1], &pc[1], &
		    ac[1], &cc[1], &fc[1], &tcf[1]);
	} else if (mgkey == 1) {
	    fmvcs_(nx, ny, nz, &u[1], &iz[51], &a1cf[1], &a2cf[1], &a3cf[1], &
		    ccf[1], &istop, &itmax, &iters, &ierror, &nlev, &ilev, &
		    nlev_real__, &mgsolv, &iok, &iinfo, &epsiln, &errtol, &
		    omegal, &nu1, &nu2, &mgsmoo, &ipc[1], &rpc[1], &pc[1], &
		    ac[1], &cc[1], &fc[1], &tcf[1]);
	} else {
	    s_wsle(&io___103);
	    do_lio(&c__9, &c__1, "% MGDRIV2: bad mgkey given... ", (ftnlen)30)
		    ;
	    e_wsle();
	}
    }
    if (mode == 1 || mode == 2) {
	s_wsle(&io___104);
	do_lio(&c__9, &c__1, "% MGDRIV2: nonlinear mode...", (ftnlen)28);
	e_wsle();
	nlev_real__ = nlev;
	iok = 1;
	ilev = 1;
	if (mgkey == 0) {
	    mvfas_(nx, ny, nz, &u[1], &iz[51], &a1cf[1], &a2cf[1], &a3cf[1], &
		    ccf[1], &fcf[1], &istop, &itmax, &iters, &ierror, &nlev, &
		    ilev, &nlev_real__, &mgsolv, &iok, &iinfo, &epsiln, &
		    errtol, &omegan, &nu1, &nu2, &mgsmoo, &ipc[1], &rpc[1], &
		    pc[1], &ac[1], &cc[1], &fc[1], &tcf[1]);
	} else if (mgkey == 1) {
	    fmvfas_(nx, ny, nz, &u[1], &iz[51], &a1cf[1], &a2cf[1], &a3cf[1], 
		    &ccf[1], &fcf[1], &istop, &itmax, &iters, &ierror, &nlev, 
		    &ilev, &nlev_real__, &mgsolv, &iok, &iinfo, &epsiln, &
		    errtol, &omegan, &nu1, &nu2, &mgsmoo, &ipc[1], &rpc[1], &
		    pc[1], &ac[1], &cc[1], &fc[1], &tcf[1]);
	} else {
	    s_wsle(&io___105);
	    do_lio(&c__9, &c__1, "% MGDRIV2: bad mgkey given... ", (ftnlen)30)
		    ;
	    e_wsle();
	}
    }
/* * */
/* *    *** stop timer *** */
    tstop_(&bf, &oh, &tsolve);
    s_wsle(&io___107);
    do_lio(&c__9, &c__1, "% MGDRIV2: solve time: ", (ftnlen)23);
    do_lio(&c__5, &c__1, (char *)&tsolve, (ftnlen)sizeof(doublereal));
    e_wsle();
/* * */
/* *    *** MATLAB *** */
    s_wsfe(&io___108);
    do_fio(&c__1, "mg_sf", (ftnlen)5);
    do_fio(&c__1, (char *)&tsetupf, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, "mg_sc", (ftnlen)5);
    do_fio(&c__1, (char *)&tsetupc, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, "mg_st", (ftnlen)5);
    d__1 = tsetupf + tsetupc;
    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, "mg_so", (ftnlen)5);
    do_fio(&c__1, (char *)&tsolve, (ftnlen)sizeof(doublereal));
    e_wsfe();
/* * */
/* *    *** restore boundary conditions *** */
    ibound = 1;
    fbound_(&ibound, nx, ny, nz, &u[1], &gxcf[1], &gycf[1], &gzcf[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* mgdriv2_ */

/* Subroutine */ int mgsz_(integer *mgcoar, integer *mgdisc, integer *mgsolv, 
	integer *nx, integer *ny, integer *nz, integer *nlev, integer *nxc, 
	integer *nyc, integer *nzc, integer *nf, integer *nc, integer *narr, 
	integer *narrc, integer *n_rpc__, integer *n_iz__, integer *n_ipc__, 
	integer *iretot, integer *iintot)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer num_band__, nxf, nyf, nzf, num_nf_oper__, level, n_band__;
    extern /* Subroutine */ int mkcors_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *);
    static integer num_narrc_oper__, nc_band__;

    /* Fortran I/O blocks */
    static cilist io___115 = { 0, 6, 0, 0, 0 };
    static cilist io___117 = { 0, 6, 0, 0, 0 };
    static cilist io___121 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *   this routine computes the required sizes of the real and integer */
/* *   work arrays for the multigrid code.  these two sizes are a */
/* *   (complicated) function of input parameters. */
/* * */
/* *   the work arrays must have been declared in the calling program as: */
/* * */
/* *       double precision rwork(iretot) */
/* *       integer          iwork(iintot) */
/* * */
/* *   where: */
/* * */
/* *       iretot   = function_of(mgcoar,mgdisc,mgsolv,nx,ny,nz,nlev) */
/* *       iintot   = function_of(mgcoar,mgdisc,mgsolv,nx,ny,nz,nlev) */
/* * */
/* *       mgcoar   = coarsening technique: */
/* *                  0=standard discretization */
/* *                  1=averaged coefficient + standard discretization */
/* *                  2=algebraic galerkin coarsening */
/* * */
/* *       mgdisc   = discretization technique: */
/* *                  0=box method */
/* *                  1=fem method */
/* * */
/* *       mgsolv   = coarse grid solver: */
/* *                  0=conjugate gradients */
/* *                  1=symmetric banded linpack solver */
/* * */
/* *       nx,ny,nz = grid dimensions in each direction, */
/* *                  including boundary points */
/* * */
/* *       nlev     = the number of multigrid levels desired for the */
/* *                  method. */
/* * */
/* *   other parameters: */
/* * */
/* *       nf       = number of unknowns on the finest mesh */
/* *                = nx * ny * nz */
/* * */
/* *       nc       = number of unknowns on the coarsest mesh */
/* * */
/* *       narr     = storage for one vector on all the meshes */
/* * */
/* *       narrc    = storage for one vector on all the meshes but the finest */
/* * */
/* *   the work arrays rwork and iwork will be chopped into smaller */
/* *   pieces according to: */
/* * */
/* *       double precision ac(STORE)         (system operators on all levels) */
/* *       double precision pc(27*narrc)      (prol. opers for coarse levels) */
/* *       double precision cc(narr),fc(narr) (helmholtz term, rhs -- all levels) */
/* *       double precision rpc(100*(nlev+1)) (real info for all levels) */
/* *       integer          ipc(100*(nlev+1)) (integer info for all levels) */
/* *       integer          iz(50,nlev+1),    (pointers into ac,pc,cc,fc,etc.) */
/* * */
/* *   where STORE depends on the discretization, coarsening, and coarse */
/* *   grid solver: */
/* * */
/* *       STORE =  4*nf +  4*narrc + NBAND*nc (mgdisc=box, mgcoar=stan/harm) */
/* *          or =  4*nf + 14*narrc + NBAND*nc (mgdisc=box, mgcoar=gal) */
/* *          or = 14*nf + 14*narrc + NBAND*nc (mgdisc=fem, mgcoar=stan/harm/gal) */
/* * */
/* *       NBAND = 0                           (mgsolv=iterative) */
/* *          or = 1+(nxc-2)*(nyc-2)           (mgsolv=7-pt banded linpack) */
/* *          or = 1+(nxc-2)*(nyc-2)+(nxc-2)+1 (mgsolv=27-pt banded linpack) */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** input parameters *** */
/* * */
/* *    *** parameters: num of different types of arrays in mg code *** */
/* * */
/* *    *** variables returned from mgsz *** */
/* * */
/* *    *** misc variables *** */
/* * */
/* *    *** go down grids: compute max/min eigenvalues of all operators *** */
    *nf = *nx * *ny * *nz;
    *narr = *nf;
    nxf = *nx;
    nyf = *ny;
    nzf = *nz;
    *nxc = *nx;
    *nyc = *ny;
    *nzc = *nz;
    i__1 = *nlev;
    for (level = 2; level <= i__1; ++level) {
/* * */
/* *       *** find new grid size *** */
	mkcors_(&c__1, &nxf, &nyf, &nzf, nxc, nyc, nzc);
/* * */
/* *       *** new grid size *** */
	nxf = *nxc;
	nyf = *nyc;
	nzf = *nzc;
/* * */
/* *       *** add the unknowns on this level to the total *** */
	*narr += nxf * nyf * nzf;
/* L10: */
    }
    *nc = *nxc * *nyc * *nzc;
    *narrc = *narr - *nf;
/* * */
/* *    *** box or fem on fine grid? *** */
    if (*mgdisc == 0) {
	num_nf_oper__ = 4;
    } else if (*mgdisc == 1) {
	num_nf_oper__ = 14;
    } else {
	s_wsle(&io___115);
	do_lio(&c__9, &c__1, "% MGSZ: invalid mgdisc parameter...", (ftnlen)
		35);
	e_wsle();
    }
/* * */
/* *    *** galerkin or standard coarsening? *** */
    if ((*mgcoar == 0 || *mgcoar == 1) && *mgdisc == 0) {
	num_narrc_oper__ = 4;
    } else if (*mgcoar == 2) {
	num_narrc_oper__ = 14;
    } else {
	s_wsle(&io___117);
	do_lio(&c__9, &c__1, "% MGSZ: invalid mgcoar parameter...", (ftnlen)
		35);
	e_wsle();
    }
/* * */
/* *    *** symmetric banded linpack storage on coarse grid *** */
    if (*mgsolv == 0) {
	n_band__ = 0;
    } else if (*mgsolv == 1) {
	if ((*mgcoar == 0 || *mgcoar == 1) && *mgdisc == 0) {
	    num_band__ = (*nxc - 2) * (*nyc - 2) + 1;
	} else {
	    num_band__ = (*nxc - 2) * (*nyc - 2) + 1 + (*nxc - 2) + 1;
	}
	nc_band__ = (*nxc - 2) * (*nyc - 2) * (*nzc - 2);
	n_band__ = nc_band__ * num_band__;
    } else {
	s_wsle(&io___121);
	do_lio(&c__9, &c__1, "% MGSZ: invalid mgsolv parameter...", (ftnlen)
		35);
	e_wsle();
    }
/* * */
/* *    *** info work array required storage *** */
    *n_rpc__ = (*nlev + 1) * 100;
/* * */
/* *    *** resulting total required real storage for method *** */
    *iretot = (*narr << 1) + num_nf_oper__ * *nf + (num_narrc_oper__ + 27) * *
	    narrc + n_band__ + *n_rpc__;
/* * */
/* *    *** the integer storage parameters *** */
    *n_iz__ = (*nlev + 1) * 50;
    *n_ipc__ = (*nlev + 1) * 100;
/* * */
/* *    *** resulting total required integer storage for method *** */
    *iintot = *n_iz__ + *n_ipc__;
/* * */
/* *    *** return and end *** */
    return 0;
} /* mgsz_ */

/* Subroutine */ int mgsize_(integer *mgcoar, integer *mgdisc, integer *
	mgsolv, integer *nx, integer *ny, integer *nz, integer *nlev)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer nc, nf, nxc, nyc, nzc, n_iz__, narr;
    extern /* Subroutine */ int mgsz_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *);
    static integer n_ipc__, n_rpc__, narrc, iretot, iintot;

    /* Fortran I/O blocks */
    static cilist io___134 = { 0, 6, 0, 0, 0 };
    static cilist io___135 = { 0, 6, 0, 0, 0 };
    static cilist io___136 = { 0, 6, 0, 0, 0 };
    static cilist io___137 = { 0, 6, 0, 0, 0 };
    static cilist io___138 = { 0, 6, 0, 0, 0 };
    static cilist io___139 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *   this routine prints out the required sizes of the real and integer */
/* *   work arrays for the multigrid code.  these two sizes are a */
/* *   (complicated) function of the four input parameters: */
/* * */
/* *        nx,ny,nz ==> number of grid points in each grid direction. */
/* *        nlev     ==> number of multigrid levels to employ. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** input parameters *** */
/* * */
/* *    *** variables returned from mgsz *** */
/* * */
/* *    *** basic grid sizes, etc. *** */
    mgsz_(mgcoar, mgdisc, mgsolv, nx, ny, nz, nlev, &nxc, &nyc, &nzc, &nf, &
	    nc, &narr, &narrc, &n_rpc__, &n_iz__, &n_ipc__, &iretot, &iintot);
/* * */
/* *    *** resulting total required for real/integer storage *** */
    s_wsle(&io___134);
    do_lio(&c__9, &c__1, "% MGSIZE: number of unknowns on finest level:    ", 
	    (ftnlen)49);
    do_lio(&c__3, &c__1, (char *)&nf, (ftnlen)sizeof(integer));
    e_wsle();
    s_wsle(&io___135);
    do_lio(&c__9, &c__1, "% MGSIZE: number of unknowns on coarsest level:  ", 
	    (ftnlen)49);
    do_lio(&c__3, &c__1, (char *)&nc, (ftnlen)sizeof(integer));
    e_wsle();
    s_wsle(&io___136);
    do_lio(&c__9, &c__1, "% MGSIZE: storage for a vector on all levels:    ", 
	    (ftnlen)49);
    do_lio(&c__3, &c__1, (char *)&narr, (ftnlen)sizeof(integer));
    e_wsle();
    s_wsle(&io___137);
    do_lio(&c__9, &c__1, "% MGSIZE: storage for a vector on coarse levels: ", 
	    (ftnlen)49);
    do_lio(&c__3, &c__1, (char *)&narrc, (ftnlen)sizeof(integer));
    e_wsle();
    s_wsle(&io___138);
    do_lio(&c__9, &c__1, "% MGSIZE: REQUIRED floating point array size:    ", 
	    (ftnlen)49);
    do_lio(&c__3, &c__1, (char *)&iretot, (ftnlen)sizeof(integer));
    e_wsle();
    s_wsle(&io___139);
    do_lio(&c__9, &c__1, "% MGSIZE: REQUIRED integer array size:           ", 
	    (ftnlen)49);
    do_lio(&c__3, &c__1, (char *)&iintot, (ftnlen)sizeof(integer));
    e_wsle();
/* * */
/* *    *** return and end *** */
    return 0;
} /* mgsize_ */

