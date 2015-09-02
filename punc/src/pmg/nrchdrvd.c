/* ./src_f77/nrchdrvd.f -- translated by f2c (version 20030320).
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
static doublereal c_b15 = 0.;
static integer c__5 = 5;
static integer c_n1 = -1;
static doublereal c_b72 = -1.;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    nrchdrvd.f */
/* * @author  Michael Holst */
/* * @brief   Driver for nonlinear Richardson iteration. */
/* * @version $Id: nrchdrvd.c,v 1.3 2010/08/12 05:45:26 fetk Exp $ */
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
/* Subroutine */ int nrichdriv_(integer *iparm, doublereal *rparm, integer *
	iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *
	yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *
	gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, 
	doublereal *ccf, doublereal *fcf, doublereal *tcf)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer n;
    extern /* Subroutine */ int nrichdriv2_(integer *, doublereal *, integer *
	    , integer *, integer *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static integer nx, ny, nz, k_w0__, k_ac__, k_cc__, k_fc__, k_iz__, n_iz__,
	     nlev, niwk, nrwk, k_ipc__, n_ipc__, k_rpc__, n_rpc__, ierror, 
	    iretot, iintot;

    /* Fortran I/O blocks */
    static cilist io___13 = { 0, 6, 0, 0, 0 };
    static cilist io___14 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    driver for linear/nonlinear richardson's iteration. */
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
    n = nx * ny * nz;
    n_iz__ = (nlev + 1) * 10;
    n_ipc__ = (nlev + 1) * 100;
    n_rpc__ = (nlev + 1) * 100;
/* * */
/* *    *** compute required work array sizes *** */
    iintot = n_iz__ + n_ipc__;
    iretot = n_rpc__ + n * 3 + (n << 2);
/* * */
/* *    *** some more checks on input *** */
    if (nrwk < iretot || niwk < iintot) {
	s_wsle(&io___13);
	do_lio(&c__9, &c__1, "% NRICHDRIV: real    work space must be: ", (
		ftnlen)41);
	do_lio(&c__3, &c__1, (char *)&iretot, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___14);
	do_lio(&c__9, &c__1, "% NRICHDRIV: integer work space must be: ", (
		ftnlen)41);
	do_lio(&c__3, &c__1, (char *)&iintot, (ftnlen)sizeof(integer));
	e_wsle();
	ierror = -3;
	iparm[51] = ierror;
	return 0;
    }
/* * */
/* *    *** iwork offsets *** */
    k_iz__ = 1;
    k_ipc__ = k_iz__ + n_iz__;
/* * */
/* *    *** rwork offsets *** */
    k_rpc__ = 1;
    k_cc__ = k_rpc__ + n_rpc__;
    k_fc__ = k_cc__ + n;
    k_w0__ = k_fc__ + n;
    k_ac__ = k_w0__ + n;
/* * ***k_ac_after  = k_ac + 4*n */
/* * */
/* *    *** call the multigrid driver *** */
    nrichdriv2_(&iparm[1], &rparm[1], &nx, &ny, &nz, &u[1], &iwork[k_iz__], &
	    rwork[k_w0__], &iwork[k_ipc__], &rwork[k_rpc__], &rwork[k_ac__], &
	    rwork[k_cc__], &rwork[k_fc__], &xf[1], &yf[1], &zf[1], &gxcf[1], &
	    gycf[1], &gzcf[1], &a1cf[1], &a2cf[1], &a3cf[1], &ccf[1], &fcf[1],
	     &tcf[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* nrichdriv_ */

/* Subroutine */ int nrichdriv2_(integer *iparm, doublereal *rparm, integer *
	nx, integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *
	w0, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, 
	doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, 
	doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *
	a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal 
	*fcf, doublereal *tcf)
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
    extern /* Subroutine */ int buildops_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), 
	    buildstr_(integer *, integer *, integer *, integer *, integer *);
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
    extern /* Subroutine */ int richgo_(integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *), fbound_(
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), matvec_(integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static integer ibound;
    static doublereal epsiln;
    static integer mgprol, ierror, mgsolv;
    static doublereal errtol, tsolve;
    extern /* Subroutine */ int tstart_(doublereal *, doublereal *), prtstp_(
	    integer *, integer *, doublereal *, doublereal *, doublereal *), 
	    fbound00_(integer *, integer *, integer *, doublereal *);
    static doublereal pc_dumm__;
    extern /* Subroutine */ int nrichgo_(integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *), 
	    nmatvec_(integer *, integer *, integer *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal tsetupc, tsetupf;

    /* Fortran I/O blocks */
    static cilist io___44 = { 0, 6, 0, 0, 0 };
    static cilist io___47 = { 0, 6, 0, 0, 0 };
    static cilist io___48 = { 0, 6, 0, 0, 0 };
    static cilist io___53 = { 0, 6, 0, 0, 0 };
    static cilist io___55 = { 0, 6, 0, 0, 0 };
    static cilist io___56 = { 0, 6, 0, fmt_100, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    driver for linear/nonlinear richardson's iteration. */
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
    --rpc;
    --ipc;
    --w0;
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
    mode = iparm[16];
    mgprol = iparm[17];
    mgcoar = iparm[18];
    mgdisc = iparm[19];
    mgsolv = iparm[21];
    errtol = rparm[1];
    omegal = rparm[9];
    omegan = rparm[10];
/* * */
/* *    *** intitialize the iteration timer *** */
    prtstp_(&c__0, &c_n99, &c_b15, &c_b15, &c_b15);
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
	    mgcoar, &mgsolv, &mgdisc, &ipc[1], &rpc[1], &pc_dumm__, &ac[1], &
	    cc[1], &fc[1], &xf[1], &yf[1], &zf[1], &gxcf[1], &gycf[1], &gzcf[
	    1], &a1cf[1], &a2cf[1], &a3cf[1], &ccf[1], &fcf[1], &tcf[1]);
/* * */
/* *    *** stop timer *** */
    tstop_(&bf, &oh, &tsetupf);
    s_wsle(&io___44);
    do_lio(&c__9, &c__1, "% NRICHDRIV2: fine problem setup time: ", (ftnlen)
	    39);
    do_lio(&c__5, &c__1, (char *)&tsetupf, (ftnlen)sizeof(doublereal));
    e_wsle();
    tsetupc = 0.;
/* * */
/* * ****************************************************************** */
/* * *** this overwrites the rhs array provided by pde specification */
/* * ****** compute an algebraically produced rhs for the given tcf *** */
    if (istop == 4 || istop == 5) {
	if (mode == 1 || mode == 2) {
	    nmatvec_(nx, ny, nz, &ipc[1], &rpc[1], &ac[1], &cc[1], &tcf[1], &
		    fc[1], &w0[1]);
	} else {
	    matvec_(nx, ny, nz, &ipc[1], &rpc[1], &ac[1], &cc[1], &tcf[1], &
		    fc[1]);
	}
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
    s_wsle(&io___47);
    do_lio(&c__9, &c__1, " rich = [ ", (ftnlen)10);
    e_wsle();
/* * */
/* *    *** start timer *** */
    tstart_(&bf, &oh);
/* * */
/* *    *** call specified multigrid method *** */
    if (mode == 0 || mode == 2) {
	s_wsle(&io___48);
	do_lio(&c__9, &c__1, "% NRICHDRIV2: linear mode...", (ftnlen)28);
	e_wsle();
	iok = 1;
	ilev = 1;
	richgo_(nx, ny, nz, &u[1], &w0[1], &a1cf[1], &a2cf[1], &istop, &itmax,
		 &iters, &ierror, &iok, &iinfo, &epsiln, &errtol, &omegal, &
		ipc[1], &rpc[1], &ac[1], &cc[1], &fc[1], &tcf[1]);
    }
    if (mode == 1 || mode == 2) {
	s_wsle(&io___53);
	do_lio(&c__9, &c__1, "% NRICHDRIV2: nonlinear mode...", (ftnlen)31);
	e_wsle();
	iok = 1;
	ilev = 1;
	nrichgo_(nx, ny, nz, &u[1], &w0[1], &a1cf[1], &a2cf[1], &istop, &
		itmax, &iters, &ierror, &iok, &iinfo, &epsiln, &errtol, &
		omegan, &ipc[1], &rpc[1], &ac[1], &cc[1], &fc[1], &tcf[1]);
    }
/* * */
/* *    *** stop timer *** */
    tstop_(&bf, &oh, &tsolve);
    s_wsle(&io___55);
    do_lio(&c__9, &c__1, "% NRICHDRIV2: solve time: ", (ftnlen)26);
    do_lio(&c__5, &c__1, (char *)&tsolve, (ftnlen)sizeof(doublereal));
    e_wsle();
/* * */
/* *    *** MATLAB *** */
    s_wsfe(&io___56);
    do_fio(&c__1, "rich_sf", (ftnlen)7);
    do_fio(&c__1, (char *)&tsetupf, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, "rich_sc", (ftnlen)7);
    do_fio(&c__1, (char *)&tsetupc, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, "rich_st", (ftnlen)7);
    d__1 = tsetupf + tsetupc;
    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, "rich_so", (ftnlen)7);
    do_fio(&c__1, (char *)&tsolve, (ftnlen)sizeof(doublereal));
    e_wsfe();
/* * */
/* *    *** restore boundary conditions *** */
    ibound = 1;
    fbound_(&ibound, nx, ny, nz, &u[1], &gxcf[1], &gycf[1], &gzcf[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* nrichdriv2_ */

/* Subroutine */ int nrichgo_(integer *nx, integer *ny, integer *nz, 
	doublereal *x, doublereal *r__, doublereal *w1, doublereal *w2, 
	integer *istop, integer *itmax, integer *iters, integer *ierror, 
	integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, 
	doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, 
	doublereal *cc, doublereal *fc, doublereal *tru)
{
    /* Format strings */
    static char fmt_100[] = "(a,(2x,\002 [\002,i3,\002,\002,i3,\002,\002,i3"
	    ",\002] \002))";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double sqrt(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer iadjoint;
    static doublereal errtol_s__;
    extern doublereal xdot_(integer *, integer *, integer *, doublereal *, 
	    doublereal *), xnrm1_(integer *, integer *, integer *, doublereal 
	    *), xnrm2_(integer *, integer *, integer *, doublereal *);
    extern /* Subroutine */ int nrich_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , integer *, doublereal *, doublereal *, integer *, integer *);
    static doublereal rsden, rsnrm;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *), xaxpy_(integer *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *);
    static integer iresid;
    extern /* Subroutine */ int azeros_(integer *, integer *, integer *, 
	    doublereal *), prtini_(integer *);
    static doublereal orsnrm;
    extern /* Subroutine */ int prtstp_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal omega_s__;
    extern /* Subroutine */ int nmatvec_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *), nmresid_(integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static integer itmax_s__, iters_s__;

    /* Fortran I/O blocks */
    static cilist io___58 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___60 = { 0, 6, 0, 0, 0 };
    static cilist io___61 = { 0, 6, 0, 0, 0 };
    static cilist io___70 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    nonlinear richardson's iteration. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** other declarations *** */
/* * */
/* *    *** do some i/o if requested *** */
    /* Parameter adjustments */
    --tru;
    --fc;
    --cc;
    --ac;
    --rpc;
    --ipc;
    --w2;
    --w1;
    --r__;
    --x;

    /* Function Body */
    if (*iinfo != 0) {
	s_wsfe(&io___58);
	do_fio(&c__1, "% NRICHGO: starting:", (ftnlen)20);
	do_fio(&c__1, (char *)&(*nx), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*ny), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*nz), (ftnlen)sizeof(integer));
	e_wsfe();
    }
/* * */
/* *    *** initial wall clock *** */
    prtini_(istop);
    prtstp_(iok, &c_n1, &c_b15, &c_b15, &c_b15);
/* * */
/* *    ************************************************************** */
/* *    *** note: if (iok.ne.0) then:  use a stopping test.        *** */
/* *    ***       else:  use just the itmax to stop iteration.     *** */
/* *    ************************************************************** */
/* *    *** istop=0 most efficient (whatever it is)                *** */
/* *    *** istop=1 relative residual                              *** */
/* *    *** istop=2 rms difference of successive iterates          *** */
/* *    *** istop=3 relative true error (provided for testing)     *** */
/* *    ************************************************************** */
/* * */
/* *    *** compute denominator for stopping criterion *** */
    if (*istop == 0) {
	rsden = 1.;
    } else if (*istop == 1) {
/* *       *** compute initial residual with zero initial guess *** */
/* *       *** this is analogous to the linear case where one can *** */
/* *       *** simply take norm of rhs for a zero initial guess *** */
	azeros_(nx, ny, nz, &w1[1]);
	nmresid_(nx, ny, nz, &ipc[1], &rpc[1], &ac[1], &cc[1], &fc[1], &w1[1],
		 &r__[1], &w2[1]);
	rsden = xnrm1_(nx, ny, nz, &r__[1]);
    } else if (*istop == 2) {
	rsden = sqrt((doublereal) (*nx * *ny * *nz));
    } else if (*istop == 3) {
	rsden = xnrm2_(nx, ny, nz, &tru[1]);
    } else if (*istop == 4) {
	rsden = xnrm2_(nx, ny, nz, &tru[1]);
    } else if (*istop == 5) {
	nmatvec_(nx, ny, nz, &ipc[1], &rpc[1], &ac[1], &cc[1], &tru[1], &w1[1]
		, &w2[1]);
	rsden = sqrt(xdot_(nx, ny, nz, &tru[1], &w1[1]));
    } else {
	s_wsle(&io___60);
	do_lio(&c__9, &c__1, "% NRICHGO: bad istop value... ", (ftnlen)30);
	e_wsle();
    }
    if (rsden == 0.) {
	rsden = 1.;
	s_wsle(&io___61);
	do_lio(&c__9, &c__1, "% NRICHGO: rhs is zero ", (ftnlen)23);
	e_wsle();
    }
    rsnrm = rsden;
    orsnrm = rsnrm;
    prtstp_(iok, &c__0, &rsnrm, &rsden, &orsnrm);
/* * */
/* *    *** setup for the looping *** */
    *iters = 0;
L30:
    *iters += 10;
/* * */
/* *       *** save iterate if stop test will use it on next iter *** */
    if (*istop == 2) {
	xcopy_(nx, ny, nz, &x[1], &tru[1]);
    }
/* * */
/* *       *** do 10 iterations *** */
    iresid = 1;
    iadjoint = 0;
    errtol_s__ = 0.;
    itmax_s__ = 10;
    omega_s__ = *omega;
    nrich_(nx, ny, nz, &ipc[1], &rpc[1], &ac[1], &cc[1], &fc[1], &x[1], &w1[1]
	    , &w2[1], &r__[1], &itmax_s__, &iters_s__, &errtol_s__, &
	    omega_s__, &iresid, &iadjoint);
/* * */
/* *       *** compute/check the current stopping test *** */
    orsnrm = rsnrm;
    if (*istop == 0) {
	rsnrm = xnrm1_(nx, ny, nz, &r__[1]);
    } else if (*istop == 1) {
	rsnrm = xnrm1_(nx, ny, nz, &r__[1]);
    } else if (*istop == 2) {
	xcopy_(nx, ny, nz, &tru[1], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b72, &x[1], &w1[1]);
	rsnrm = xnrm1_(nx, ny, nz, &w1[1]);
    } else if (*istop == 3) {
	xcopy_(nx, ny, nz, &tru[1], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b72, &x[1], &w1[1]);
	rsnrm = xnrm2_(nx, ny, nz, &w1[1]);
    } else if (*istop == 4) {
	xcopy_(nx, ny, nz, &tru[1], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b72, &x[1], &w1[1]);
	rsnrm = xnrm2_(nx, ny, nz, &w1[1]);
    } else if (*istop == 5) {
	xcopy_(nx, ny, nz, &tru[1], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b72, &x[1], &w1[1]);
	nmatvec_(nx, ny, nz, &ipc[1], &rpc[1], &ac[1], &cc[1], &w1[1], &w2[1],
		 &r__[1]);
	rsnrm = sqrt(xdot_(nx, ny, nz, &w1[1], &w2[1]));
    } else {
	s_wsle(&io___70);
	do_lio(&c__9, &c__1, "% NRICHGO: bad istop value... ", (ftnlen)30);
	e_wsle();
    }
    prtstp_(iok, iters, &rsnrm, &rsden, &orsnrm);
    if (rsnrm / rsden <= *errtol) {
	goto L99;
    }
    if (*iters >= *itmax) {
	goto L99;
    }
    goto L30;
/* * */
/* *    *** return and end *** */
L99:
    return 0;
} /* nrichgo_ */

/* Subroutine */ int richgo_(integer *nx, integer *ny, integer *nz, 
	doublereal *x, doublereal *r__, doublereal *w1, doublereal *w2, 
	integer *istop, integer *itmax, integer *iters, integer *ierror, 
	integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, 
	doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, 
	doublereal *cc, doublereal *fc, doublereal *tru)
{
    /* Format strings */
    static char fmt_100[] = "(a,(2x,\002 [\002,i3,\002,\002,i3,\002,\002,i3"
	    ",\002] \002))";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double sqrt(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer iadjoint;
    static doublereal errtol_s__;
    extern /* Subroutine */ int rich_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , integer *, doublereal *, doublereal *, integer *, integer *);
    extern doublereal xdot_(integer *, integer *, integer *, doublereal *, 
	    doublereal *), xnrm1_(integer *, integer *, integer *, doublereal 
	    *), xnrm2_(integer *, integer *, integer *, doublereal *);
    static doublereal rsden, rsnrm;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *), xaxpy_(integer *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *);
    static integer iresid;
    extern /* Subroutine */ int matvec_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *), prtini_(integer *);
    static doublereal orsnrm;
    extern /* Subroutine */ int prtstp_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal omega_s__;
    static integer itmax_s__, iters_s__;

    /* Fortran I/O blocks */
    static cilist io___71 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___73 = { 0, 6, 0, 0, 0 };
    static cilist io___74 = { 0, 6, 0, 0, 0 };
    static cilist io___83 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    linear richardson's iteration. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** other declarations *** */
/* * */
/* *    *** do some i/o if requested *** */
    /* Parameter adjustments */
    --tru;
    --fc;
    --cc;
    --ac;
    --rpc;
    --ipc;
    --w2;
    --w1;
    --r__;
    --x;

    /* Function Body */
    if (*iinfo != 0) {
	s_wsfe(&io___71);
	do_fio(&c__1, "% RICHGO: starting: ", (ftnlen)20);
	do_fio(&c__1, (char *)&(*nx), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*ny), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*nz), (ftnlen)sizeof(integer));
	e_wsfe();
    }
/* * */
/* *    *** initial wall clock *** */
    prtini_(istop);
    prtstp_(iok, &c_n1, &c_b15, &c_b15, &c_b15);
/* * */
/* *    ************************************************************** */
/* *    *** note: if (iok.ne.0) then:  use a stopping test.        *** */
/* *    ***       else:  use just the itmax to stop iteration.     *** */
/* *    ************************************************************** */
/* *    *** istop=0 most efficient (whatever it is)                *** */
/* *    *** istop=1 relative residual                              *** */
/* *    *** istop=2 rms difference of successive iterates          *** */
/* *    *** istop=3 relative true error (provided for testing)     *** */
/* *    ************************************************************** */
/* * */
/* *    *** compute denominator for stopping criterion *** */
    if (*istop == 0) {
	rsden = 1.;
    } else if (*istop == 1) {
	rsden = xnrm1_(nx, ny, nz, &fc[1]);
    } else if (*istop == 2) {
	rsden = sqrt((doublereal) (*nx * *ny * *nz));
    } else if (*istop == 3) {
	rsden = xnrm2_(nx, ny, nz, &tru[1]);
    } else if (*istop == 4) {
	rsden = xnrm2_(nx, ny, nz, &tru[1]);
    } else if (*istop == 5) {
	matvec_(nx, ny, nz, &ipc[1], &rpc[1], &ac[1], &cc[1], &tru[1], &w1[1])
		;
	rsden = sqrt(xdot_(nx, ny, nz, &tru[1], &w1[1]));
    } else {
	s_wsle(&io___73);
	do_lio(&c__9, &c__1, "% RICHGO: bad istop value... ", (ftnlen)29);
	e_wsle();
    }
    if (rsden == 0.) {
	rsden = 1.;
	s_wsle(&io___74);
	do_lio(&c__9, &c__1, "% RICHGO: rhs is zero ", (ftnlen)22);
	e_wsle();
    }
    rsnrm = rsden;
    orsnrm = rsnrm;
    prtstp_(iok, &c__0, &rsnrm, &rsden, &orsnrm);
/* * */
/* *    *** setup for the looping *** */
    *iters = 0;
L30:
    *iters += 10;
/* * */
/* *       *** save iterate if stop test will use it on next iter *** */
    if (*istop == 2) {
	xcopy_(nx, ny, nz, &x[1], &tru[1]);
    }
/* * */
/* *       *** do 10 iterations *** */
    iresid = 1;
    iadjoint = 0;
    errtol_s__ = 0.;
    itmax_s__ = 10;
    omega_s__ = *omega;
    rich_(nx, ny, nz, &ipc[1], &rpc[1], &ac[1], &cc[1], &fc[1], &x[1], &w1[1],
	     &w2[1], &r__[1], &itmax_s__, &iters_s__, &errtol_s__, &omega_s__,
	     &iresid, &iadjoint);
/* * */
/* *       *** compute/check the current stopping test *** */
    orsnrm = rsnrm;
    if (*istop == 0) {
	rsnrm = xnrm1_(nx, ny, nz, &r__[1]);
    } else if (*istop == 1) {
	rsnrm = xnrm1_(nx, ny, nz, &r__[1]);
    } else if (*istop == 2) {
	xcopy_(nx, ny, nz, &tru[1], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b72, &x[1], &w1[1]);
	rsnrm = xnrm1_(nx, ny, nz, &w1[1]);
    } else if (*istop == 3) {
	xcopy_(nx, ny, nz, &tru[1], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b72, &x[1], &w1[1]);
	rsnrm = xnrm2_(nx, ny, nz, &w1[1]);
    } else if (*istop == 4) {
	xcopy_(nx, ny, nz, &tru[1], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b72, &x[1], &w1[1]);
	rsnrm = xnrm2_(nx, ny, nz, &w1[1]);
    } else if (*istop == 5) {
	xcopy_(nx, ny, nz, &tru[1], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b72, &x[1], &w1[1]);
	matvec_(nx, ny, nz, &ipc[1], &rpc[1], &ac[1], &cc[1], &w1[1], &w2[1]);
	rsnrm = sqrt(xdot_(nx, ny, nz, &w1[1], &w2[1]));
    } else {
	s_wsle(&io___83);
	do_lio(&c__9, &c__1, "% RICHGO: bad istop value... ", (ftnlen)29);
	e_wsle();
    }
    prtstp_(iok, iters, &rsnrm, &rsden, &orsnrm);
    if (rsnrm / rsden <= *errtol) {
	goto L99;
    }
    if (*iters >= *itmax) {
	goto L99;
    }
    goto L30;
/* * */
/* *    *** return and end *** */
L99:
    return 0;
} /* richgo_ */

