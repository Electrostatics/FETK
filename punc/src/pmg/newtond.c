/* ./src_f77/newtond.f -- translated by f2c (version 20030320).
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
static integer c__5 = 5;
static doublereal c_b61 = -1.;
static integer c__3 = 3;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    newtond.f */
/* * @author  Michael Holst */
/* * @brief   The main Newton iteration. */
/* * @version $Id: newtond.c,v 1.3 2010/08/12 05:45:25 fetk Exp $ */
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
/* Subroutine */ int fnewton_(integer *nx, integer *ny, integer *nz, 
	doublereal *x, integer *iz, doublereal *w0, doublereal *w1, 
	doublereal *w2, doublereal *w3, integer *istop, integer *itmax, 
	integer *iters, integer *ierror, integer *nlev, integer *ilev, 
	integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, 
	doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *
	nu1, integer *nu2, integer *mgsmoo, doublereal *cprime, doublereal *
	rhs, doublereal *xtmp, integer *ipc, doublereal *rpc, doublereal *pc, 
	doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru)
{
    /* Format strings */
    static char fmt_100[] = "(a,2(2x,\002 [\002,i3,\002,\002,i3,\002,\002,"
	    "i3,\002] \002))";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer nxc, nyc, nzc, nxf, nyf, nzf, iokd;
    static doublereal errd;
    static integer level, nlevd, iterd, istpd, itmxd;
    extern /* Subroutine */ int mkfine_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *), mkcors_(integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *),
	     interp_(integer *, integer *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *), newton_(
	    integer *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *, integer *, integer *, integer *, integer *,
	     integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 6, 0, fmt_100, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    nested iteration for an inexact-newton-multilevel method. */
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
    --xtmp;
    --rhs;
    --cprime;
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
/* *    *** move up grids: interpolate solution to finer, do newton *** */
    if (*iinfo != 0) {
	s_wsfe(&io___7);
	do_fio(&c__1, "% FNEWTON: starting:", (ftnlen)20);
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
	errd = *errtol;
	itmxd = 1000;
	nlevd = *nlev_real__ - level + 1;
	iterd = 0;
	iokd = *iok;
	istpd = *istop;
	newton_(&nxc, &nyc, &nzc, &x[1], &iz[51], &w0[1], &w1[1], &w2[1], &w3[
		1], &istpd, &itmxd, &iterd, ierror, &nlevd, &level, 
		nlev_real__, mgsolv, &iokd, iinfo, epsiln, &errd, omega, nu1, 
		nu2, mgsmoo, &cprime[1], &rhs[1], &xtmp[1], &ipc[1], &rpc[1], 
		&pc[1], &ac[1], &cc[1], &fc[1], &tru[1]);
/* * */
/* *       *** find new grid size *** */
	mkfine_(&c__1, &nxc, &nyc, &nzc, &nxf, &nyf, &nzf);
/* * */
/* *       *** interpolate to next finer grid (use correct bc's) *** */
	interp_(&nxc, &nyc, &nzc, &nxf, &nyf, &nzf, &x[iz[level * 50 + 1]], &
		x[iz[(level - 1) * 50 + 1]], &pc[iz[(level - 1) * 50 + 11]]);
/* ZZZ     call ninterp(nxc,nyc,nzc,nxf,nyf,nzf, */
/* ZZZ 2      x(iz(1,level)),x(iz(1,level-1)),pc(iz(11,level-1)), */
/* ZZZ 3      ipc(iz(5,level-1)),rpc(iz(6,level-1)), */
/* ZZZ 4      ac(iz(7,level-1)),cc(iz(1,level-1)),fc(iz(1,level-1))) */
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
    newton_(nx, ny, nz, &x[1], &iz[51], &w0[1], &w1[1], &w2[1], &w3[1], istop,
	     itmax, iters, ierror, nlev, &level, nlev_real__, mgsolv, iok, 
	    iinfo, epsiln, errtol, omega, nu1, nu2, mgsmoo, &cprime[1], &rhs[
	    1], &xtmp[1], &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1], &fc[1], &
	    tru[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* fnewton_ */

/* Subroutine */ int newton_(integer *nx, integer *ny, integer *nz, 
	doublereal *x, integer *iz, doublereal *w0, doublereal *w1, 
	doublereal *w2, doublereal *w3, integer *istop, integer *itmax, 
	integer *iters, integer *ierror, integer *nlev, integer *ilev, 
	integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, 
	doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *
	nu1, integer *nu2, integer *mgsmoo, doublereal *cprime, doublereal *
	rhs, doublereal *xtmp, integer *ipc, doublereal *rpc, doublereal *pc, 
	doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru)
{
    /* Format strings */
    static char fmt_100[] = "(a,(2x,\002 [\002,i3,\002,\002,i3,\002,\002,i3"
	    ",\002] \002))";
    static char fmt_110[] = "(\002% \002,a,i5,1pe10.2)";
    static char fmt_200[] = "(a,\002 [\002,i3,\002,\002,i3,\002,\002,i3,\002"
	    "] \002)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double sqrt(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer ierror_s__;
    static doublereal errtol_p__, errtol_s__, xnorm_med__, xnorm_den__, 
	    xnorm_old__, xnorm_new__, ord;
    static integer lev;
    static doublereal rho_min_mod__, rho_max_mod__, bigc, damp;
    static integer mode;
    extern /* Subroutine */ int mvcs_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    extern doublereal xdot_(integer *, integer *, integer *, doublereal *, 
	    doublereal *), xnrm1_(integer *, integer *, integer *, doublereal 
	    *), xnrm2_(integer *, integer *, integer *, doublereal *);
    static integer idamp, iok_p__, iok_s__, level;
    static doublereal rsden;
    static integer ipkey;
    extern /* Subroutine */ int power_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *);
    static doublereal rsnrm;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *), xaxpy_(integer *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *), getjac_(integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer iter_d__;
    extern /* Subroutine */ int azeros_(integer *, integer *, integer *, 
	    doublereal *), prtini_(integer *), ipower_(integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *);
    static doublereal orsnrm;
    extern /* Subroutine */ int prtstp_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *);
    static integer iinfo_p__, itmax_d__, iinfo_s__;
    static doublereal rho_min__, rho_max__;
    extern /* Subroutine */ int nmatvec_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *);
    static integer itmax_p__;
    extern /* Subroutine */ int nmresid_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *);
    static integer itmax_s__, iters_p__, iters_s__, istop_s__;

    /* Fortran I/O blocks */
    static cilist io___17 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___19 = { 0, 6, 0, 0, 0 };
    static cilist io___20 = { 0, 6, 0, 0, 0 };
    static cilist io___25 = { 0, 6, 0, 0, 0 };
    static cilist io___31 = { 0, 6, 0, 0, 0 };
    static cilist io___43 = { 0, 6, 0, fmt_110, 0 };
    static cilist io___45 = { 0, 6, 0, fmt_110, 0 };
    static cilist io___46 = { 0, 6, 0, fmt_110, 0 };
    static cilist io___47 = { 0, 6, 0, 0, 0 };
    static cilist io___48 = { 0, 6, 0, 0, 0 };
    static cilist io___49 = { 0, 6, 0, 0, 0 };
    static cilist io___50 = { 0, 6, 0, fmt_200, 0 };
    static cilist io___51 = { 0, 6, 0, 0, 0 };
    static cilist io___58 = { 0, 6, 0, 0, 0 };
    static cilist io___59 = { 0, 6, 0, 0, 0 };
    static cilist io___60 = { 0, 6, 0, 0, 0 };
    static cilist io___61 = { 0, 6, 0, 0, 0 };
    static cilist io___65 = { 0, 6, 0, 0, 0 };
    static cilist io___66 = { 0, 6, 0, 0, 0 };
    static cilist io___67 = { 0, 6, 0, 0, 0 };
    static cilist io___68 = { 0, 6, 0, 0, 0 };
    static cilist io___69 = { 0, 6, 0, 0, 0 };
    static cilist io___70 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    inexact-newton-multilevel method. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** other declarations *** */
/* * */
/* *    *** local variables *** */
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
    --xtmp;
    --rhs;
    --cprime;
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
	do_fio(&c__1, "% NEWTON: starting: ", (ftnlen)20);
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
/* *       *** compute initial residual with zero initial guess *** */
/* *       *** this is analogous to the linear case where one can *** */
/* *       *** simply take norm of rhs for a zero initial guess *** */
	azeros_(nx, ny, nz, &w1[1]);
	nmresid_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &
		ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev * 50 
		+ 1]], &w1[1], &w2[1], &w3[1]);
	rsden = xnrm1_(nx, ny, nz, &w2[1]);
    } else if (*istop == 2) {
	rsden = sqrt((doublereal) (*nx * *ny * *nz));
    } else if (*istop == 3) {
	rsden = xnrm2_(nx, ny, nz, &tru[iz[lev * 50 + 1]]);
    } else if (*istop == 4) {
	rsden = xnrm2_(nx, ny, nz, &tru[iz[lev * 50 + 1]]);
    } else if (*istop == 5) {
	nmatvec_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &
		ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &tru[iz[lev * 50 
		+ 1]], &w1[1], &w2[1]);
	rsden = sqrt(xdot_(nx, ny, nz, &tru[iz[lev * 50 + 1]], &w1[1]));
    } else {
	s_wsle(&io___19);
	do_lio(&c__9, &c__1, "% NEWTON: bad istop value... ", (ftnlen)29);
	e_wsle();
    }
    if (rsden == 0.) {
	rsden = 1.;
	s_wsle(&io___20);
	do_lio(&c__9, &c__1, "% NEWTON: rhs is zero...", (ftnlen)24);
	e_wsle();
    }
    rsnrm = rsden;
    orsnrm = rsnrm;
    if (*iok != 0) {
	prtstp_(iok, &c__0, &rsnrm, &rsden, &orsnrm);
    }
/* * */
/* * ********************************************************************* */
/* * *** begin newton iteration */
/* * ********************************************************************* */
/* * */
/* *    *** now compute residual with the initial guess *** */
    nmresid_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &ac[
	    iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev * 50 + 1]], &
	    x[iz[lev * 50 + 1]], &w0[1], &w2[1]);
    xnorm_old__ = xnrm1_(nx, ny, nz, &w0[1]);
    if (*iok != 0) {
	xnorm_den__ = rsden;
    } else {
	xnorm_den__ = xnorm_old__;
    }
/* * */
/* * ********************************************************************* */
/* * *** begin the loop */
/* * ********************************************************************* */
/* * */
/* *    *** setup for the looping *** */
    s_wsle(&io___25);
    do_lio(&c__9, &c__1, "% NEWTON: damping enabled...", (ftnlen)28);
    e_wsle();
    idamp = 1;
    *iters = 0;
L30:
    ++(*iters);
/* * */
/* *       *** save iterate if stop test will use it on next iter *** */
    if (*istop == 2) {
	xcopy_(nx, ny, nz, &x[iz[lev * 50 + 1]], &tru[iz[lev * 50 + 1]]);
    }
/* * */
/* *       *** compute the current jacobian system and rhs *** */
    ipkey = ipc[10];
    getjac_(nx, ny, nz, nlev_real__, &iz[51], ilev, &ipkey, &x[1], &w0[1], &
	    cprime[1], &rhs[1], &cc[1], &pc[1]);
/* * */
/* * ***** *** determine number of correct digits in current residual *** */
/* * ***** if (lev .eq. 1) then */
/* * *****    itmax_s = -idnint(dlog10(xnorm_old/xnorm_den)) */
/* * *****    itmax_s = max0(itmax_s,1) */
/* * ***** else */
/* * *****    itmax_s = 10 */
/* * ***** endif */
/* * ***** itmax_s = 1000 */
/* * ***** print*,'% NEWTON: using itmax_s: ',itmax_s */
/* * */
/* *       *** algorithm 5.3 in the thesis, test version (1') *** */
/* *       *** global-superlinear convergence *** */
    bigc = 1.;
    ord = 2.;
/* Computing MIN */
    d__1 = xnorm_old__ * .9f, d__2 = bigc * pow_dd(&xnorm_old__, &ord);
    errtol_s__ = min(d__1,d__2);
    s_wsle(&io___31);
    do_lio(&c__9, &c__1, "% NEWTON: using errtol_s: ", (ftnlen)26);
    do_lio(&c__5, &c__1, (char *)&errtol_s__, (ftnlen)sizeof(doublereal));
    e_wsle();
/* * */
/* *       *** do a linear multigrid solve of the newton equations *** */
    azeros_(nx, ny, nz, &xtmp[iz[lev * 50 + 1]]);
    itmax_s__ = 1000;
    istop_s__ = 0;
    iters_s__ = 0;
    ierror_s__ = 0;
    iok_s__ = 0;
    iinfo_s__ = 0;
    if (*iinfo >= 2 && *ilev == 1) {
	iok_s__ = 2;
    }
    mvcs_(nx, ny, nz, &xtmp[1], &iz[51], &w0[1], &w1[1], &w2[1], &w3[1], &
	    istop_s__, &itmax_s__, &iters_s__, &ierror_s__, nlev, ilev, 
	    nlev_real__, mgsolv, &iok_s__, &iinfo_s__, epsiln, &errtol_s__, 
	    omega, nu1, nu2, mgsmoo, &ipc[1], &rpc[1], &pc[1], &ac[1], &
	    cprime[1], &rhs[1], &tru[1]);
/* * */
/* *       ************************************************************** */
/* *       *** note: rhs and cprime are now available as temp vectors *** */
/* *       ************************************************************** */
/* * */
/* *       *** if damping is still enabled -- doit *** */
    if (idamp == 1) {
/* * */
/* *          *** try the correction *** */
	xcopy_(nx, ny, nz, &x[iz[lev * 50 + 1]], &w1[1]);
	damp = 1.;
	xaxpy_(nx, ny, nz, &damp, &xtmp[iz[lev * 50 + 1]], &w1[1]);
	nmresid_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &
		ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev * 50 
		+ 1]], &w1[1], &w0[1], &rhs[iz[lev * 50 + 1]]);
	xnorm_new__ = xnrm1_(nx, ny, nz, &w0[1]);
/* * */
/* *          *** damping is still enabled -- doit *** */
	damp = 1.;
	iter_d__ = 0;
	itmax_d__ = 10;
	mode = 0;
	s_wsfe(&io___43);
	do_fio(&c__1, "NEWTON: attempting damping: iter_d, relres = ", (
		ftnlen)45);
	do_fio(&c__1, (char *)&iter_d__, (ftnlen)sizeof(integer));
	d__1 = xnorm_new__ / xnorm_den__;
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
L11:
	if (iter_d__ >= itmax_d__) {
	    goto L12;
	}
	if (mode == 0) {
	    if (xnorm_new__ < xnorm_old__) {
		mode = 1;
	    }
	} else {
	    if (xnorm_new__ > xnorm_med__) {
		goto L12;
	    }
	}
/* * */
/* *             *** keep old soln and residual around, and its norm *** */
	xcopy_(nx, ny, nz, &w1[1], &w2[1]);
	xcopy_(nx, ny, nz, &w0[1], &w3[1]);
	xnorm_med__ = xnorm_new__;
/* * */
/* *             *** new damped correction, residual, and its norm *** */
	xcopy_(nx, ny, nz, &x[iz[lev * 50 + 1]], &w1[1]);
	damp /= 2.;
	xaxpy_(nx, ny, nz, &damp, &xtmp[iz[lev * 50 + 1]], &w1[1]);
	nmresid_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &
		ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev * 50 
		+ 1]], &w1[1], &w0[1], &rhs[iz[lev * 50 + 1]]);
	xnorm_new__ = xnrm1_(nx, ny, nz, &w0[1]);
/* * */
/* *             *** next iter... *** */
	++iter_d__;
	s_wsfe(&io___45);
	do_fio(&c__1, "NEWTON: attempting damping: iter_d, relres = ", (
		ftnlen)45);
	do_fio(&c__1, (char *)&iter_d__, (ftnlen)sizeof(integer));
	d__1 = xnorm_new__ / xnorm_den__;
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
	goto L11;
/* * */
/* *          *** accept the previous newton step *** */
L12:
	xcopy_(nx, ny, nz, &w2[1], &x[iz[lev * 50 + 1]]);
	xcopy_(nx, ny, nz, &w3[1], &w0[1]);
	xnorm_new__ = xnorm_med__;
	xnorm_old__ = xnorm_new__;
	s_wsfe(&io___46);
	do_fio(&c__1, "NEWTON: damping accepted:   iter_d, relres = ", (
		ftnlen)45);
	i__1 = iter_d__ - 1;
	do_fio(&c__1, (char *)&i__1, (ftnlen)sizeof(integer));
	d__1 = xnorm_new__ / xnorm_den__;
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
/* * */
/* *          *** determine whether or not to disable damping *** */
	if (iter_d__ - 1 == 0) {
	    s_wsle(&io___47);
	    do_lio(&c__9, &c__1, "% NEWTON: damping disabled...", (ftnlen)29);
	    e_wsle();
	    idamp = 0;
	}
    } else {
/* * */
/* *          *** damping is disabled -- accept the newton step *** */
	damp = 1.;
	xaxpy_(nx, ny, nz, &damp, &xtmp[iz[lev * 50 + 1]], &x[iz[lev * 50 + 1]
		]);
	nmresid_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]], &
		ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev * 50 
		+ 1]], &x[iz[lev * 50 + 1]], &w0[1], &rhs[iz[lev * 50 + 1]]);
	xnorm_new__ = xnrm1_(nx, ny, nz, &w0[1]);
	xnorm_old__ = xnorm_new__;
    }
/* * */
/* *       *** compute/check the current stopping test *** */
    if (*iok != 0) {
	orsnrm = rsnrm;
	if (*istop == 0) {
	    rsnrm = xnorm_new__;
	} else if (*istop == 1) {
	    rsnrm = xnorm_new__;
	} else if (*istop == 2) {
	    xcopy_(nx, ny, nz, &tru[iz[lev * 50 + 1]], &w1[1]);
	    xaxpy_(nx, ny, nz, &c_b61, &x[iz[lev * 50 + 1]], &w1[1]);
	    rsnrm = xnrm1_(nx, ny, nz, &w1[1]);
	} else if (*istop == 3) {
	    xcopy_(nx, ny, nz, &tru[iz[lev * 50 + 1]], &w1[1]);
	    xaxpy_(nx, ny, nz, &c_b61, &x[iz[lev * 50 + 1]], &w1[1]);
	    rsnrm = xnrm2_(nx, ny, nz, &w1[1]);
	} else if (*istop == 4) {
	    xcopy_(nx, ny, nz, &tru[iz[lev * 50 + 1]], &w1[1]);
	    xaxpy_(nx, ny, nz, &c_b61, &x[iz[lev * 50 + 1]], &w1[1]);
	    rsnrm = xnrm2_(nx, ny, nz, &w1[1]);
	} else if (*istop == 5) {
	    xcopy_(nx, ny, nz, &tru[iz[lev * 50 + 1]], &w1[1]);
	    xaxpy_(nx, ny, nz, &c_b61, &x[iz[lev * 50 + 1]], &w1[1]);
	    nmatvec_(nx, ny, nz, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]
		    ], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &w1[1], &
		    w2[1], &w3[1]);
	    rsnrm = sqrt(xdot_(nx, ny, nz, &w1[1], &w2[1]));
	} else {
	    s_wsle(&io___48);
	    do_lio(&c__9, &c__1, "% NEWTON: bad istop value... ", (ftnlen)29);
	    e_wsle();
	}
	prtstp_(iok, iters, &rsnrm, &rsden, &orsnrm);
	if (rsnrm / rsden <= *errtol) {
	    goto L99;
	}
    }
/* * */
/* *       *** check iteration count *** */
    if (*iters >= *itmax) {
	goto L99;
    }
/* * */
/* *    *** main loop *** */
    goto L30;
/* * */
/* *    *** a few things *** */
L99:
/* * */
/* *    *** condition estimate of final jacobian *** */
    if (*iinfo > 2) {
	s_wsle(&io___49);
	do_lio(&c__9, &c__1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
		 (ftnlen)46);
	do_lio(&c__9, &c__1, "%%%%%%%%%%", (ftnlen)10);
	e_wsle();
	s_wsfe(&io___50);
	do_fio(&c__1, "% NEWTON: JACOBIAN ANALYSIS==>", (ftnlen)30);
	do_fio(&c__1, (char *)&(*nx), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*ny), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*nz), (ftnlen)sizeof(integer));
	e_wsfe();
/* * */
/* *       *** largest eigenvalue of the jacobian matrix *** */
	s_wsle(&io___51);
	do_lio(&c__9, &c__1, "% NEWTON: power calculating rho(JAC)...", (
		ftnlen)39);
	e_wsle();
	itmax_p__ = 1000;
	errtol_p__ = 1e-4f;
	iters_p__ = 0;
	iinfo_p__ = *iinfo;
	power_(nx, ny, nz, &iz[51], ilev, &ipc[1], &rpc[1], &ac[1], &cprime[1]
		, &w0[1], &w1[1], &w2[1], &w3[1], &rho_max__, &rho_max_mod__, 
		&errtol_p__, &itmax_p__, &iters_p__, &iinfo_p__);
	s_wsle(&io___58);
	do_lio(&c__9, &c__1, "% NEWTON: power iters   = ", (ftnlen)26);
	do_lio(&c__3, &c__1, (char *)&iters_p__, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___59);
	do_lio(&c__9, &c__1, "% NEWTON: power eigmax  = ", (ftnlen)26);
	do_lio(&c__5, &c__1, (char *)&rho_max__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___60);
	do_lio(&c__9, &c__1, "% NEWTON: power (MODEL) = ", (ftnlen)26);
	do_lio(&c__5, &c__1, (char *)&rho_max_mod__, (ftnlen)sizeof(
		doublereal));
	e_wsle();
/* * */
/* *       *** smallest eigenvalue of the system matrix A *** */
	s_wsle(&io___61);
	do_lio(&c__9, &c__1, "% NEWTON: ipower calculating lambda_min(JAC)..."
		, (ftnlen)47);
	e_wsle();
	itmax_p__ = 1000;
	errtol_p__ = 1e-4f;
	iters_p__ = 0;
	iinfo_p__ = *iinfo;
	azeros_(nx, ny, nz, &xtmp[1]);
	ipower_(nx, ny, nz, &xtmp[1], &iz[51], &w0[1], &w1[1], &w2[1], &w3[1],
		 &rhs[1], &rho_min__, &rho_min_mod__, &errtol_p__, &itmax_p__,
		 &iters_p__, nlev, ilev, nlev_real__, mgsolv, &iok_p__, &
		iinfo_p__, epsiln, errtol, omega, nu1, nu2, mgsmoo, &ipc[1], &
		rpc[1], &pc[1], &ac[1], &cprime[1], &tru[1]);
	s_wsle(&io___65);
	do_lio(&c__9, &c__1, "% NEWTON: ipower iters   = ", (ftnlen)27);
	do_lio(&c__3, &c__1, (char *)&iters_p__, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___66);
	do_lio(&c__9, &c__1, "% NEWTON: ipower eigmin  = ", (ftnlen)27);
	do_lio(&c__5, &c__1, (char *)&rho_min__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___67);
	do_lio(&c__9, &c__1, "% NEWTON: ipower (MODEL) = ", (ftnlen)27);
	do_lio(&c__5, &c__1, (char *)&rho_min_mod__, (ftnlen)sizeof(
		doublereal));
	e_wsle();
/* * */
/* *       *** condition number estimate *** */
	s_wsle(&io___68);
	do_lio(&c__9, &c__1, "% NEWTON: condition number  = ", (ftnlen)30);
	d__1 = rho_max__ / rho_min__;
	do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___69);
	do_lio(&c__9, &c__1, "% NEWTON: condition (MODEL) = ", (ftnlen)30);
	d__1 = rho_max_mod__ / rho_min_mod__;
	do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___70);
	do_lio(&c__9, &c__1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
		 (ftnlen)46);
	do_lio(&c__9, &c__1, "%%%%%%%%%%", (ftnlen)10);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* newton_ */

/* Subroutine */ int getjac_(integer *nx, integer *ny, integer *nz, integer *
	nlev_real__, integer *iz, integer *lev, integer *ipkey, doublereal *x,
	 doublereal *r__, doublereal *cprime, doublereal *rhs, doublereal *cc,
	 doublereal *pc)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer nxx, nyy, nzz, level, nxold, nyold, nzold;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *), dc_vec__(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *), 
	    mkcors_(integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *), restrc_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    form the jacobian system. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** setup *** */
    /* Parameter adjustments */
    --pc;
    --cc;
    --rhs;
    --cprime;
    --r__;
    --x;
    iz -= 51;

    /* Function Body */
    nxx = *nx;
    nyy = *ny;
    nzz = *nz;
/* * */
/* *    *** form the rhs of the newton system -- just current residual *** */
    xcopy_(nx, ny, nz, &r__[1], &rhs[iz[*lev * 50 + 1]]);
/* * */
/* *    *** get nonlinear part of the jacobian operator *** */
    dc_vec__(&cc[iz[*lev * 50 + 1]], &x[iz[*lev * 50 + 1]], &cprime[iz[*lev * 
	    50 + 1]], nx, ny, nz, ipkey);
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
	restrc_(&nxold, &nyold, &nzold, &nxx, &nyy, &nzz, &rhs[iz[(level - 1) 
		* 50 + 1]], &rhs[iz[level * 50 + 1]], &pc[iz[(level - 1) * 50 
		+ 11]]);
/* * */
/* *       *** make the coarse grid helmholtz terms *** */
	restrc_(&nxold, &nyold, &nzold, &nxx, &nyy, &nzz, &cprime[iz[(level - 
		1) * 50 + 1]], &cprime[iz[level * 50 + 1]], &pc[iz[(level - 1)
		 * 50 + 11]]);
/* L10: */
    }
/* * */
/* *    *** end it *** */
    return 0;
} /* getjac_ */

