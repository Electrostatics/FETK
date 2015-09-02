/* ./src_f77/cgmgd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;
static integer c_n1 = -1;
static doublereal c_b23 = 0.;
static integer c__9 = 9;
static integer c__0 = 0;
static doublereal c_b35 = -1.;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    cgmgd.f */
/* * @author  Michael Holst */
/* * @brief   Multigrid-Preconditioned CG. */
/* * @version $Id: cgmgd.c,v 1.3 2010/08/12 05:45:20 fetk Exp $ */
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
/* Subroutine */ int fcgmg_(integer *nx, integer *ny, integer *nz, doublereal 
	*x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, 
	doublereal *w3, integer *istop, integer *itmax, integer *iters, 
	integer *ierror, integer *nlev, integer *ilev, integer *nlev_real__, 
	integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, 
	doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, 
	integer *mgsmoo, doublereal *w4, doublereal *w5, doublereal *w6, 
	integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, 
	doublereal *cc, doublereal *fc, doublereal *tru)
{
    /* Format strings */
    static char fmt_100[] = "(a,2(2x,\002 [\002,i3,\002,\002,i3,\002,\002,"
	    "i3,\002] \002))";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer nxc, nyc, nzc, nxf, nyf, nzf;
    extern /* Subroutine */ int cgmg_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer iokd;
    static doublereal errd;
    static integer level, nlevd, iterd, istpd, itmxd;
    extern /* Subroutine */ int mkfine_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *), mkcors_(integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *),
	     interp_(integer *, integer *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 6, 0, fmt_100, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    nested iteration for multilevel preconditioned cg */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** other declarations *** */
/* * */
/* *    *** recover gridsizes *** */
    /* Parameter adjustments */
    --tru;
    --fc;
    --cc;
    --ac;
    --pc;
    --rpc;
    --ipc;
    --w6;
    --w5;
    --w4;
    --w3;
    --w2;
    --w1;
    --w0;
    iz -= 51;
    --x;

    /* Function Body */
    nxf = *nx;
    nyf = *ny;
    nzf = *nz;
    i__1 = *nlev - 1;
    mkcors_(&i__1, &nxf, &nyf, &nzf, &nxc, &nyc, &nzc);
/* * */
/* *    *** move up grids: interpolate solution to finer, do cgmg *** */
    if (*iinfo != 0) {
	s_wsfe(&io___7);
	do_fio(&c__1, "% FCGMG: starting:  ", (ftnlen)20);
	do_fio(&c__1, (char *)&nxf, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nyf, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nzf, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nxc, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nyc, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nzc, (ftnlen)sizeof(integer));
	e_wsfe();
    }
    i__1 = *ilev + 1;
    for (level = *nlev_real__; level >= i__1; --level) {
/* * */
/* *       *** call mv cycle *** */
	errd = 1e-5f;
	itmxd = 1;
	nlevd = *nlev_real__ - level + 1;
	iterd = 0;
	iokd = 0;
	istpd = 1;
	if (*iinfo >= 2) {
	    iokd = 2;
	}
	cgmg_(&nxc, &nyc, &nzc, &x[1], &iz[51], &w0[1], &w1[1], &w2[1], &w3[1]
		, &istpd, &itmxd, &iterd, ierror, &nlevd, &level, nlev_real__,
		 mgsolv, &iokd, iinfo, epsiln, errtol, omega, nu1, nu2, 
		mgsmoo, &w4[1], &w5[1], &w6[1], &ipc[1], &rpc[1], &pc[1], &ac[
		1], &cc[1], &fc[1], &tru[1]);
/* * */
/* *       *** find new grid size *** */
	mkfine_(&c__1, &nxc, &nyc, &nzc, &nxf, &nyf, &nzf);
/* * */
/* *       *** interpolate to next finer grid (use correct bc's) *** */
	interp_(&nxc, &nyc, &nzc, &nxf, &nyf, &nzf, &x[iz[level * 50 + 1]], &
		x[iz[(level - 1) * 50 + 1]], &pc[iz[(level - 1) * 50 + 11]]);
/* * */
/* *       *** new grid size *** */
	nxc = nxf;
	nyc = nyf;
	nzc = nzf;
/* L10: */
    }
/* * */
/* *    *** call mv cycle *** */
    level = *ilev;
    cgmg_(&nxf, &nyf, &nzf, &x[1], &iz[51], &w0[1], &w1[1], &w2[1], &w3[1], 
	    istop, itmax, iters, ierror, nlev, &level, nlev_real__, mgsolv, 
	    iok, iinfo, epsiln, errtol, omega, nu1, nu2, mgsmoo, &w4[1], &w5[
	    1], &w6[1], &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1], &fc[1], &
	    tru[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* fcgmg_ */

/* Subroutine */ int cgmg_(integer *nx, integer *ny, integer *nz, doublereal *
	x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, 
	doublereal *w3, integer *istop, integer *itmax, integer *iters, 
	integer *ierror, integer *nlev, integer *ilev, integer *nlev_real__, 
	integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, 
	doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, 
	integer *mgsmoo, doublereal *rr, doublereal *zz, doublereal *pp, 
	integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, 
	doublereal *cc, doublereal *fc, doublereal *tru)
{
    /* Format strings */
    static char fmt_100[] = "(a,(2x,\002 [\002,i3,\002,\002,i3,\002,\002,i3"
	    ",\002] \002))";

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double sqrt(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer ierror_s__, lev;
    extern /* Subroutine */ int mvcs_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    extern doublereal xdot_(integer *, integer *, integer *, doublereal *, 
	    doublereal *);
    static doublereal ztmp, rhok1, rhok2;
    extern doublereal xnrm1_(integer *, integer *, integer *, doublereal *), 
	    xnrm2_(integer *, integer *, integer *, doublereal *);
    static integer iok_s__, level;
    extern /* Subroutine */ int xscal_(integer *, integer *, integer *, 
	    doublereal *, doublereal *);
    static doublereal rsden, rsnrm;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *), xaxpy_(integer *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *), matvec_(integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), mresid_(integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), getpre_(
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *), azeros_(integer *, integer *, 
	    integer *, doublereal *), prtini_(integer *);
    static doublereal orsnrm;
    extern /* Subroutine */ int prtstp_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *);
    static integer iinfo_s__, itmax_s__, iters_s__, istop_s__;

    /* Fortran I/O blocks */
    static cilist io___17 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___19 = { 0, 6, 0, 0, 0 };
    static cilist io___20 = { 0, 6, 0, 0, 0 };
    static cilist io___32 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    multilevel preconditioned cg */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** other declarations *** */
/* * */
/* *    *** recover level information *** */
    /* Parameter adjustments */
    --tru;
    --fc;
    --cc;
    --ac;
    --pc;
    --rpc;
    --ipc;
    --pp;
    --zz;
    --rr;
    --w3;
    --w2;
    --w1;
    --w0;
    iz -= 51;
    --x;

    /* Function Body */
    level = 1;
    lev = *ilev - 1 + level;
/* * */
/* *    *** do some i/o if requested *** */
    if (*iinfo != 0) {
	s_wsfe(&io___17);
	do_fio(&c__1, "% CGMG: starting:   ", (ftnlen)20);
	do_fio(&c__1, (char *)&(*nx), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*ny), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*nz), (ftnlen)sizeof(integer));
	e_wsfe();
    }
/* * */
/* *    *** initial wall clock *** */
    if (*iok != 0) {
	prtini_(istop);
	prtstp_(iok, &c_n1, &c_b23, &c_b23, &c_b23);
    }
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
	rsden = xnrm1_(nx, ny, nz, &fc[iz[lev * 50 + 1]]);
    } else if (*istop == 2) {
	rsden = sqrt((doublereal) (*nx * *ny * *nz));
    } else if (*istop == 3) {
	rsden = xnrm2_(nx, ny, nz, &tru[iz[lev * 50 + 1]]);
    } else if (*istop == 4) {
	rsden = xnrm2_(nx, ny, nz, &tru[iz[lev * 50 + 1]]);
    } else if (*istop == 5) {
	matvec_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &
		ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &tru[iz[lev * 50 
		+ 1]], &w1[1]);
	rsden = sqrt(xdot_(nx, ny, nz, &tru[iz[lev * 50 + 1]], &w1[1]));
    } else {
	s_wsle(&io___19);
	do_lio(&c__9, &c__1, "% CGMG: bad istop value... ", (ftnlen)27);
	e_wsle();
    }
    if (rsden == 0.) {
	rsden = 1.;
	s_wsle(&io___20);
	do_lio(&c__9, &c__1, "% CGMG: rhs is zero...", (ftnlen)22);
	e_wsle();
    }
    rsnrm = rsden;
    orsnrm = rsnrm;
    if (*iok != 0) {
	prtstp_(iok, &c__0, &rsnrm, &rsden, &orsnrm);
    }
/* * */
/* * ********************************************************************* */
/* * *** begin cg iteration */
/* * ********************************************************************* */
/* * */
/* *    *** compute the initial residual (always required) *** */
    mresid_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &ac[
	    iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev * 50 + 1]], &
	    x[iz[lev * 50 + 1]], &rr[iz[lev * 50 + 1]]);
/* * */
/* * ********************************************************************* */
/* * ** *** no preconditioning *** */
/* * ** call xcopy(nx,ny,nz,rr(iz(1,lev)),zz(iz(1,lev))) */
/* * ********************************************************************* */
/* *    *** multilevel preconditioning *** */
/* * */
/* *    *** restrict residual to form rhs of coarse grid systems *** */
    getpre_(nx, ny, nz, &iz[51], ilev, nlev_real__, &rr[1], &pc[1]);
/* * */
/* *    *** do a linear multigrid solve of the precond equations *** */
    azeros_(nx, ny, nz, &zz[iz[lev * 50 + 1]]);
    istop_s__ = 1;
    itmax_s__ = 1;
    iters_s__ = 0;
    ierror_s__ = 0;
    iinfo_s__ = 0;
    iok_s__ = 0;
/* * ***if ((iinfo .ge. 2) .and. (ilev .eq. 1)) iok_s = 2 */
    mvcs_(nx, ny, nz, &zz[1], &iz[51], &w0[1], &w1[1], &w2[1], &w3[1], &
	    istop_s__, &itmax_s__, &iters_s__, &ierror_s__, nlev, ilev, 
	    nlev_real__, mgsolv, &iok_s__, &iinfo_s__, epsiln, errtol, omega, 
	    nu1, nu2, mgsmoo, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1], &rr[1]
	    , &tru[1]);
/* * ********************************************************************* */
/* * */
/* *    *** setup *** */
    rhok1 = xdot_(nx, ny, nz, &zz[iz[lev * 50 + 1]], &rr[iz[lev * 50 + 1]]);
    if (rhok1 == 0.) {
	goto L99;
    }
/* * */
/* *    *** do the cg iteration *** */
    *iters = 0;
L30:
    ++(*iters);
/* * */
/* *       *** save iterate if stop test will use it on next iter *** */
    if (*istop == 2) {
	xcopy_(nx, ny, nz, &x[iz[lev * 50 + 1]], &tru[iz[lev * 50 + 1]]);
    }
/* * */
/* *       *** main computation *** */
    if (*iters == 1) {
	xcopy_(nx, ny, nz, &zz[iz[lev * 50 + 1]], &pp[1]);
    } else {
	d__1 = rhok2 / rhok1;
	xaxpy_(nx, ny, nz, &d__1, &zz[iz[lev * 50 + 1]], &pp[1]);
	d__1 = rhok1 / rhok2;
	xscal_(nx, ny, nz, &d__1, &pp[1]);
    }
    matvec_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &ac[
	    iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &pp[1], &w1[1]);
    ztmp = rhok1 / xdot_(nx, ny, nz, &pp[1], &w1[1]);
    xaxpy_(nx, ny, nz, &ztmp, &pp[1], &x[iz[lev * 50 + 1]]);
    d__1 = -ztmp;
    xaxpy_(nx, ny, nz, &d__1, &w1[1], &rr[iz[lev * 50 + 1]]);
/* * */
/* * ********************************************************************* */
/* * ***** *** no preconditioning *** */
/* * ***** call xcopy(nx,ny,nz,rr(iz(1,lev)),zz(iz(1,lev))) */
/* * ********************************************************************* */
/* *       *** multilevel preconditioning *** */
/* * */
/* *       *** restrict residual to form rhs of coarse grid systems *** */
    getpre_(nx, ny, nz, &iz[51], ilev, nlev_real__, &rr[1], &pc[1]);
/* * */
/* *       *** do a linear multigrid solve of the precond equations *** */
    azeros_(nx, ny, nz, &zz[iz[lev * 50 + 1]]);
    istop_s__ = 1;
    itmax_s__ = 1;
    iters_s__ = 0;
    ierror_s__ = 0;
    iinfo_s__ = 0;
    iok_s__ = 0;
/* * ******if ((iinfo .ge. 2) .and. (ilev .eq. 1)) iok_s = 2 */
    mvcs_(nx, ny, nz, &zz[1], &iz[51], &w0[1], &w1[1], &w2[1], &w3[1], &
	    istop_s__, &itmax_s__, &iters_s__, &ierror_s__, nlev, ilev, 
	    nlev_real__, mgsolv, &iok_s__, &iinfo_s__, epsiln, errtol, omega, 
	    nu1, nu2, mgsmoo, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1], &rr[1]
	    , &tru[1]);
/* * ********************************************************************* */
/* * */
/* *       *** new residual *** */
    rhok2 = rhok1;
    rhok1 = xdot_(nx, ny, nz, &zz[iz[lev * 50 + 1]], &rr[iz[lev * 50 + 1]]);
    if (rhok1 == 0.) {
	goto L99;
    }
/* * */
/* *       *** compute/check the current stopping test *** */
    orsnrm = rsnrm;
    if (*istop == 0) {
	rsnrm = xnrm1_(nx, ny, nz, &rr[iz[lev * 50 + 1]]);
    } else if (*istop == 1) {
	rsnrm = xnrm1_(nx, ny, nz, &rr[iz[lev * 50 + 1]]);
    } else if (*istop == 2) {
	xcopy_(nx, ny, nz, &tru[iz[lev * 50 + 1]], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b35, &x[iz[lev * 50 + 1]], &w1[1]);
	rsnrm = xnrm1_(nx, ny, nz, &w1[1]);
    } else if (*istop == 3) {
	xcopy_(nx, ny, nz, &tru[iz[lev * 50 + 1]], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b35, &x[iz[lev * 50 + 1]], &w1[1]);
	rsnrm = xnrm2_(nx, ny, nz, &w1[1]);
    } else if (*istop == 4) {
	xcopy_(nx, ny, nz, &tru[iz[lev * 50 + 1]], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b35, &x[iz[lev * 50 + 1]], &w1[1]);
	rsnrm = xnrm2_(nx, ny, nz, &w1[1]);
    } else if (*istop == 5) {
	xcopy_(nx, ny, nz, &tru[iz[lev * 50 + 1]], &w1[1]);
	xaxpy_(nx, ny, nz, &c_b35, &x[iz[lev * 50 + 1]], &w1[1]);
	matvec_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &
		ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &w1[1], &w2[1]);
	rsnrm = sqrt(xdot_(nx, ny, nz, &w1[1], &w2[1]));
    } else {
	s_wsle(&io___32);
	do_lio(&c__9, &c__1, "% MVCS: bad istop value... ", (ftnlen)27);
	e_wsle();
    }
    if (*iok != 0) {
	prtstp_(iok, iters, &rsnrm, &rsden, &orsnrm);
    }
/* * */
/* *       *** check iteration count and tolerance *** */
    if (rsnrm / rsden <= *errtol) {
	goto L99;
    }
    if (*iters >= *itmax) {
	goto L99;
    }
/* * */
/* *    *** main loop *** */
    goto L30;
/* * */
/* *    *** return and end *** */
L99:
    return 0;
} /* cgmg_ */

/* Subroutine */ int getpre_(integer *nx, integer *ny, integer *nz, integer *
	iz, integer *lev, integer *nlev_real__, doublereal *r__, doublereal *
	pc)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer nxx, nyy, nzz, level, nxold, nyold, nzold;
    extern /* Subroutine */ int mkcors_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *), restrc_(integer *, 
	    integer *, integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    form the residual on all levels to prepare for multilevel prec. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** setup *** */
    /* Parameter adjustments */
    --pc;
    --r__;
    iz -= 51;

    /* Function Body */
    nxx = *nx;
    nyy = *ny;
    nzz = *nz;
/* * */
/* *    *** build the (nlev-1) level operators *** */
    i__1 = *nlev_real__;
    for (level = *lev + 1; level <= i__1; ++level) {
	nxold = nxx;
	nyold = nyy;
	nzold = nzz;
	mkcors_(&c__1, &nxold, &nyold, &nzold, &nxx, &nyy, &nzz);
/* * */
/* *       *** make the coarse grid rhs functions *** */
	restrc_(&nxold, &nyold, &nzold, &nxx, &nyy, &nzz, &r__[iz[(level - 1) 
		* 50 + 1]], &r__[iz[level * 50 + 1]], &pc[iz[(level - 1) * 50 
		+ 11]]);
/* L10: */
    }
/* * */
/* *    *** end it *** */
    return 0;
} /* getpre_ */

