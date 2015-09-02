/* ./src_f77/mgfasd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;
static integer c_n1 = -1;
static doublereal c_b26 = 0.;
static integer c__9 = 9;
static integer c__0 = 0;
static doublereal c_b36 = -1.;
static doublereal c_b47 = 1.;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    mgfasd.f */
/* * @author  Michael Holst */
/* * @brief   Core nonlinear (full approximation scheme) multigrid routines. */
/* * @version $Id: mgfasd.c,v 1.3 2010/08/12 05:45:23 fetk Exp $ */
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
/* Subroutine */ int fmvfas_(integer *nx, integer *ny, integer *nz, 
	doublereal *x, integer *iz, doublereal *w0, doublereal *w1, 
	doublereal *w2, doublereal *w3, doublereal *w4, integer *istop, 
	integer *itmax, integer *iters, integer *ierror, integer *nlev, 
	integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, 
	integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *
	omega, integer *nu1, integer *nu2, integer *mgsmoo, integer *ipc, 
	doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, 
	doublereal *fc, doublereal *tru)
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
    static integer level, nlevd, iterd;
    extern /* Subroutine */ int mvfas_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static integer istpd, itmxd, iinfod;
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
/* *    nested iteration for a nonlinear multilevel method. */
/* * */
/* *    algorithm:  nonlinear multigrid iteration (fas) */
/* * */
/* *    this routine is the full multigrid front-end for a multigrid */
/* *    v-cycle solver.  in other words, at repeatedly calls the v-cycle */
/* *    multigrid solver on successively finer and finer grids. */
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
/* *    *** move up grids: interpolate solution to finer, do v cycle *** */
    if (*iinfo != 0) {
	s_wsfe(&io___7);
	do_fio(&c__1, "% FMVFAS: starting: ", (ftnlen)20);
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
	iokd = 2;
	iinfod = *iinfo;
	istpd = *istop;
	if (*iinfo >= 2) {
	    iokd = 2;
	}
	mvfas_(&nxc, &nyc, &nzc, &x[1], &iz[51], &w0[1], &w1[1], &w2[1], &w3[
		1], &w4[1], &istpd, &itmxd, &iterd, ierror, &nlevd, &level, 
		nlev_real__, mgsolv, &iokd, &iinfod, epsiln, errtol, omega, 
		nu1, nu2, mgsmoo, &ipc[1], &rpc[1], &pc[1], &ac[1], &cc[1], &
		fc[1], &tru[1]);
/* * */
/* *       *** find new grid size *** */
	mkfine_(&c__1, &nxc, &nyc, &nzc, &nxf, &nyf, &nzf);
/* * */
/* *       *** interpolate to next finer grid *** */
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
    mvfas_(&nxf, &nyf, &nzf, &x[1], &iz[51], &w0[1], &w1[1], &w2[1], &w3[1], &
	    w4[1], istop, itmax, iters, ierror, nlev, &level, nlev_real__, 
	    mgsolv, iok, iinfo, epsiln, errtol, omega, nu1, nu2, mgsmoo, &ipc[
	    1], &rpc[1], &pc[1], &ac[1], &cc[1], &fc[1], &tru[1]);
/* * */
/* *    *** return and end *** */
    return 0;
} /* fmvfas_ */

/* Subroutine */ int mvfas_(integer *nx, integer *ny, integer *nz, doublereal 
	*x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, 
	doublereal *w3, doublereal *w4, integer *istop, integer *itmax, 
	integer *iters, integer *ierror, integer *nlev, integer *ilev, 
	integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, 
	doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *
	nu1, integer *nu2, integer *mgsmoo, integer *ipc, doublereal *rpc, 
	doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, 
	doublereal *tru)
{
    /* Format strings */
    static char fmt_100[] = "(a,2(2x,\002 [\002,i3,\002,\002,i3,\002,\002,"
	    "i3,\002] \002))";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double sqrt(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer iadjoint, mgsmoo_s__;
    static doublereal errtol_s__;
    extern /* Subroutine */ int linesearch_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static integer lev, nxc, nyc, nzc, nxf, nyf, nzf;
    extern doublereal xdot_(integer *, integer *, integer *, doublereal *, 
	    doublereal *);
    static integer nuuu;
    extern doublereal xnrm1_(integer *, integer *, integer *, doublereal *), 
	    xnrm2_(integer *, integer *, integer *, doublereal *);
    static integer level;
    static doublereal xdamp, rsden, rsnrm;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *), xaxpy_(integer *, integer *, integer 
	    *, doublereal *, doublereal *, doublereal *), mkfine_(integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *);
    static integer iresid;
    extern /* Subroutine */ int extrac_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *), 
	    mkcors_(integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *);
    extern integer ivariv_(integer *, integer *);
    extern /* Subroutine */ int azeros_(integer *, integer *, integer *, 
	    doublereal *), restrc_(integer *, integer *, integer *, integer *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *), 
	    prtini_(integer *), interp_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal orsnrm;
    extern /* Subroutine */ int prtstp_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *), nmatvec_(integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), nmresid_(integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static integer itmax_s__, iters_s__;
    extern /* Subroutine */ int nsmooth_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , integer *, doublereal *, doublereal *, integer *, integer *, 
	    integer *);

    /* Fortran I/O blocks */
    static cilist io___24 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___26 = { 0, 6, 0, 0, 0 };
    static cilist io___27 = { 0, 6, 0, 0, 0 };
    static cilist io___36 = { 0, 6, 0, 0, 0 };
    static cilist io___39 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    nonlinear multilevel method. */
/* * */
/* *    algorithm:  nonlinear multigrid iteration (fas) */
/* * */
/* *    multigrid v-cycle solver. */
/* * */
/* *    input: */
/* *       (1) fine and coarse grid discrete nonlinear operators: L_h, L_H */
/* *       (2) fine grid source function: f_h */
/* *       (3) fine grid approximate solution: u_h */
/* * */
/* *    output: */
/* *       (1) fine grid improved solution: u_h */
/* * */
/* *    the two-grid algorithm is: */
/* *       (1) pre-smooth:               u1_h = smooth(L_h,f_h,u_h) */
/* *       (2) restrict defect:          d_H  = r(L_h(u1_h) - f_h) */
/* *           restrict solution:        u_H  = r(u1_h) */
/* *       (3) form coarse grid rhs:     f_H  = L_H(u_H) - d_H */
/* *           solve for correction:     c_H  = L_H^{-1}(f_H) */
/* *       (4) prolongate and correct:   u2_h = u1_h - p(c_H - u_H) */
/* *       (5) post-smooth:              u_h  = smooth(L_h,f_h,u2_h) */
/* * */
/* *    (of course, c_H is determined with another two-grid algorithm) */
/* * */
/* *    implementation notes: */
/* *       (0) "u1_h" and "u_H" must be kept on each level until "c_H" is */
/* *           computed, and then all three are used to compute "u2_h". */
/* *       (1) "u_h" (and then "u1_h") on all levels is stored in the "x" array. */
/* *       (2) "u_H" on all levels is stored in the "e" array. */
/* *       (3) "c_h" is identically "u_h" for u_h on the next coarser grid. */
/* *       (4) "d_H" is stored in the "r" array. */
/* *       (5) "f_h" and "f_H" are stored in the "fc" array. */
/* *       (6) "L_h" on all levels is stored in the "ac" array. */
/* *       (7) signs may be reveresed; i.e., residual is used in place */
/* *           of the defect in places, etc. */
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
    --w4;
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
/* *    *** recover gridsizes *** */
    nxf = *nx;
    nyf = *ny;
    nzf = *nz;
    i__1 = *nlev - 1;
    mkcors_(&i__1, &nxf, &nyf, &nzf, &nxc, &nyc, &nzc);
/* * */
/* *    *** do some i/o if requested *** */
    if (*iinfo != 0) {
	s_wsfe(&io___24);
	do_fio(&c__1, "% MVFAS: starting:  ", (ftnlen)20);
	do_fio(&c__1, (char *)&nxf, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nyf, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nzf, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nxc, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nyc, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nzc, (ftnlen)sizeof(integer));
	e_wsfe();
    }
/* * */
/* *    *** initial wall clock *** */
    if (*iok != 0) {
	prtini_(istop);
	prtstp_(iok, &c_n1, &c_b26, &c_b26, &c_b26);
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
    if (*iok != 0) {
	if (*istop == 0) {
	    rsden = 1.;
	} else if (*istop == 1) {
/* *          *** compute initial residual with zero initial guess *** */
/* *          *** this is analogous to the linear case where one can *** */
/* *          *** simply take norm of rhs for a zero initial guess *** */
	    azeros_(&nxf, &nyf, &nzf, &w1[1]);
	    nmresid_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 
		    50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &
		    fc[iz[lev * 50 + 1]], &w1[1], &w2[1], &w3[1]);
	    rsden = xnrm1_(&nxf, &nyf, &nzf, &w2[1]);
	} else if (*istop == 2) {
	    rsden = sqrt((doublereal) (nxf * nyf * nzf));
	} else if (*istop == 3) {
	    rsden = xnrm2_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]]);
	} else if (*istop == 4) {
	    rsden = xnrm2_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]]);
	} else if (*istop == 5) {
	    nmatvec_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 
		    50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &
		    tru[iz[lev * 50 + 1]], &w1[1], &w2[1]);
	    rsden = sqrt(xdot_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]], &w1[
		    1]));
	} else {
	    s_wsle(&io___26);
	    do_lio(&c__9, &c__1, "% MVFAS: bad istop value... ", (ftnlen)28);
	    e_wsle();
	}
	if (rsden == 0.) {
	    rsden = 1.;
	    s_wsle(&io___27);
	    do_lio(&c__9, &c__1, "% MVFAS:  rhs is zero on finest level ", (
		    ftnlen)38);
	    e_wsle();
	}
	rsnrm = rsden;
	orsnrm = rsnrm;
	prtstp_(iok, &c__0, &rsnrm, &rsden, &orsnrm);
    }
/* * */
/* * ********************************************************************* */
/* * *** solve directly if nlev = 1 */
/* * ********************************************************************* */
/* * */
/* *    *** solve directly if on the coarse grid *** */
    if (*nlev == 1) {
/* * */
/* *       *** solve with ncghs, mgsmoo_s=4 (no residual) *** */
	iresid = 0;
	iadjoint = 0;
	itmax_s__ = 100;
	iters_s__ = 0;
	errtol_s__ = *epsiln;
	mgsmoo_s__ = *mgsmoo;
	azeros_(&nxf, &nyf, &nzf, &x[iz[lev * 50 + 1]]);
	nsmooth_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 
		6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev 
		* 50 + 1]], &x[iz[lev * 50 + 1]], &w1[1], &w2[1], &w3[1], &
		itmax_s__, &iters_s__, &errtol_s__, omega, &iresid, &iadjoint,
		 &mgsmoo_s__);
/* * */
/* * ***** *** check if trouble on the coarse grid *** */
/* * ***** if (iters_s .ge. itmax_s) then */
/* * *****    print*,'% MVFAS: smooth iters on coarse grid: ',iters_s */
/* * ***** endif */
/* * */
/* *       *** compute the stopping test *** */
	*iters = 1;
	if (*iok != 0) {
	    orsnrm = rsnrm;
	    if (*istop == 0) {
		nmresid_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[
			lev * 50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 
			50 + 1]], &fc[iz[lev * 50 + 1]], &x[iz[lev * 50 + 1]],
			 &w1[1], &w2[1]);
		rsnrm = xnrm1_(&nxf, &nyf, &nzf, &w1[1]);
	    } else if (*istop == 1) {
		nmresid_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[
			lev * 50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 
			50 + 1]], &fc[iz[lev * 50 + 1]], &x[iz[lev * 50 + 1]],
			 &w1[1], &w2[1]);
		rsnrm = xnrm1_(&nxf, &nyf, &nzf, &w1[1]);
	    } else if (*istop == 2) {
		xcopy_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]], &w1[1]);
		xaxpy_(&nxf, &nyf, &nzf, &c_b36, &x[iz[lev * 50 + 1]], &w1[1])
			;
		rsnrm = xnrm1_(&nxf, &nyf, &nzf, &w1[1]);
		xcopy_(&nxf, &nyf, &nzf, &x[iz[lev * 50 + 1]], &tru[iz[lev * 
			50 + 1]]);
	    } else if (*istop == 3) {
		xcopy_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]], &w1[1]);
		xaxpy_(&nxf, &nyf, &nzf, &c_b36, &x[iz[lev * 50 + 1]], &w1[1])
			;
		rsnrm = xnrm2_(&nxf, &nyf, &nzf, &w1[1]);
	    } else if (*istop == 4) {
		xcopy_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]], &w1[1]);
		xaxpy_(&nxf, &nyf, &nzf, &c_b36, &x[iz[lev * 50 + 1]], &w1[1])
			;
		rsnrm = xnrm2_(&nxf, &nyf, &nzf, &w1[1]);
	    } else if (*istop == 5) {
		xcopy_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]], &w1[1]);
		xaxpy_(&nxf, &nyf, &nzf, &c_b36, &x[iz[lev * 50 + 1]], &w1[1])
			;
		nmatvec_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[
			lev * 50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 
			50 + 1]], &w1[1], &w2[1], &w3[1]);
		rsnrm = sqrt(xdot_(&nxf, &nyf, &nzf, &w1[1], &w2[1]));
	    } else {
		s_wsle(&io___36);
		do_lio(&c__9, &c__1, "% MVCS: bad istop value... ", (ftnlen)
			27);
		e_wsle();
	    }
	    prtstp_(iok, iters, &rsnrm, &rsden, &orsnrm);
	}
/* * */
/* *       *** return now *** */
	goto L99;
    }
/* * */
/* * ********************************************************************* */
/* * *** begin mg iteration (note nxf,nyf,nzf changes during loop) */
/* * ********************************************************************* */
/* * */
/* *    *** setup for the v-cycle looping *** */
    *iters = 0;
L30:
/* * */
/* *       *** finest level initialization *** */
    level = 1;
    lev = *ilev - 1 + level;
/* * */
/* *       *** nu1 pre-smoothings on fine grid (with residual) *** */
    iresid = 1;
    iadjoint = 0;
    iters_s__ = 0;
    errtol_s__ = 0.;
    nuuu = ivariv_(nu1, &lev);
    nsmooth_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]],
	     &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev * 50 + 
	    1]], &x[iz[lev * 50 + 1]], &w2[1], &w3[1], &w1[1], &nuuu, &
	    iters_s__, &errtol_s__, omega, &iresid, &iadjoint, mgsmoo);
    xcopy_(&nxf, &nyf, &nzf, &w1[1], &w0[iz[lev * 50 + 1]]);
/* * */
/* * ********************************************************************* */
/* * begin cycling down to coarse grid */
/* * ********************************************************************* */
/* * */
/* *       *** go down grids: restrict resid to coarser and smooth *** */
    i__1 = *nlev;
    for (level = 2; level <= i__1; ++level) {
	lev = *ilev - 1 + level;
/* * */
/* *          *** find new grid size *** */
	mkcors_(&c__1, &nxf, &nyf, &nzf, &nxc, &nyc, &nzc);
/* * */
/* *          *** restrict residual to coarser grid *** */
	restrc_(&nxf, &nyf, &nzf, &nxc, &nyc, &nzc, &w1[1], &w0[iz[lev * 50 + 
		1]], &pc[iz[(lev - 1) * 50 + 11]]);
/* * */
/* *          *** restrict (extract) solution to coarser grid *** */
	extrac_(&nxf, &nyf, &nzf, &nxc, &nyc, &nzc, &x[iz[(lev - 1) * 50 + 1]]
		, &w4[iz[lev * 50 + 1]]);
/* * */
/* *          *** new grid size *** */
	nxf = nxc;
	nyf = nyc;
	nzf = nzc;
/* * */
/* *          *** apply coarse grid operator to coarse grid soln *** */
	nmatvec_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 
		6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &w4[iz[lev 
		* 50 + 1]], &fc[iz[lev * 50 + 1]], &w3[1]);
/* * */
/* *          *** build coarse grid right hand side *** */
	xaxpy_(&nxf, &nyf, &nzf, &c_b47, &w0[iz[lev * 50 + 1]], &fc[iz[lev * 
		50 + 1]]);
/* * */
/* *          *** if not on coarsest level yet... *** */
	if (level != *nlev) {
/* * */
/* *             *** nu1 pre-smoothings on this level (with residual) *** */
	    xcopy_(&nxf, &nyf, &nzf, &w4[iz[lev * 50 + 1]], &x[iz[lev * 50 + 
		    1]]);
	    iresid = 1;
	    iadjoint = 0;
	    iters_s__ = 0;
	    errtol_s__ = 0.;
	    nuuu = ivariv_(nu1, &lev);
	    nsmooth_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 
		    50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &
		    fc[iz[lev * 50 + 1]], &x[iz[lev * 50 + 1]], &w2[1], &w3[1]
		    , &w1[1], &nuuu, &iters_s__, &errtol_s__, omega, &iresid, 
		    &iadjoint, mgsmoo);
	}
/* * */
/* *       *** end of cycling down to coarse grid loop *** */
/* L40: */
    }
/* * */
/* * ********************************************************************* */
/* * begin coarse grid */
/* * ********************************************************************* */
/* * */
/* *       *** coarsest level *** */
    level = *nlev;
    lev = *ilev - 1 + level;
/* * */
/* *       *** solve on coarsest grid with ncghs, mgsmoo_s=4 (no residual) *** */
    iresid = 0;
    iadjoint = 0;
    itmax_s__ = 100;
    iters_s__ = 0;
    errtol_s__ = *epsiln;
    mgsmoo_s__ = *mgsmoo;
    azeros_(&nxf, &nyf, &nzf, &x[iz[lev * 50 + 1]]);
    nsmooth_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 6]],
	     &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev * 50 + 
	    1]], &x[iz[lev * 50 + 1]], &w1[1], &w2[1], &w3[1], &itmax_s__, &
	    iters_s__, &errtol_s__, omega, &iresid, &iadjoint, &mgsmoo_s__);
/* * */
/* * ***** *** check for trouble on the coarse grid *** */
/* * ***** if (iters_s .ge. itmax_s) then */
/* * *****    print*,'% MVFAS: smooth iters on coarse grid: ',iters_s */
/* * ***** endif */
/* * */
/* * ********************************************************************* */
/* * begin cycling back to fine grid */
/* * ********************************************************************* */
/* * */
/* *       *** move up grids: interpolate resid to finer and smooth *** */
    for (level = *nlev - 1; level >= 1; --level) {
	lev = *ilev - 1 + level;
/* * */
/* *          *** find new grid size *** */
	mkfine_(&c__1, &nxf, &nyf, &nzf, &nxc, &nyc, &nzc);
/* * */
/* *          *** form difference of new approx at the coarse grid *** */
	xaxpy_(&nxf, &nyf, &nzf, &c_b36, &w4[iz[(lev + 1) * 50 + 1]], &x[iz[(
		lev + 1) * 50 + 1]]);
/* * */
/* *          *** call the line search (on the coarser level) *** */
	linesearch_(&nxf, &nyf, &nzf, &xdamp, &ipc[iz[(lev + 1) * 50 + 5]], &
		rpc[iz[(lev + 1) * 50 + 6]], &ac[iz[(lev + 1) * 50 + 7]], &cc[
		iz[(lev + 1) * 50 + 1]], &fc[iz[(lev + 1) * 50 + 1]], &x[iz[(
		lev + 1) * 50 + 1]], &w4[iz[(lev + 1) * 50 + 1]], &w0[iz[(lev 
		+ 1) * 50 + 1]], &w1[1], &w2[1], &w3[1]);
/* * */
/* *          *** interpolate to next finer grid *** */
	interp_(&nxf, &nyf, &nzf, &nxc, &nyc, &nzc, &x[iz[(lev + 1) * 50 + 1]]
		, &w1[1], &pc[iz[lev * 50 + 11]]);
/* * */
/* *          *** new grid size *** */
	nxf = nxc;
	nyf = nyc;
	nzf = nzc;
/* * */
/* *          *** call the line search (on the finer level) *** */
/* ZZZ        call linesearch(nxf,nyf,nzf,xdamp, */
/* ZZZ 2         ipc(iz(5,lev)),rpc(iz(6,lev)), */
/* ZZZ 3         ac(iz(7,lev)),cc(iz(1,lev)),fc(iz(1,lev)), */
/* ZZZ 4         w1,x(iz(1,lev)),w0(iz(1,lev)), */
/* ZZZ 5         w2,w3,w4) */
/* * */
/* *          *** perform the coarse grid correction *** */
/* * ******** xdamp = 1.0d0 */
	xaxpy_(&nxf, &nyf, &nzf, &xdamp, &w1[1], &x[iz[lev * 50 + 1]]);
/* * */
/* *          *** nu2 post-smoothings for correction (no residual) *** */
	iresid = 0;
	iadjoint = 1;
	iters_s__ = 0;
	errtol_s__ = 0.;
	nuuu = ivariv_(nu2, &lev);
	nsmooth_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 50 + 
		6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &fc[iz[lev 
		* 50 + 1]], &x[iz[lev * 50 + 1]], &w1[1], &w2[1], &w3[1], &
		nuuu, &iters_s__, &errtol_s__, omega, &iresid, &iadjoint, 
		mgsmoo);
/* L70: */
    }
/* * */
/* * ********************************************************************* */
/* * iteration complete: do some i/o */
/* * ********************************************************************* */
/* * */
/* *       *** increment the iteration counter *** */
    ++(*iters);
/* * */
/* *       *** compute/check the current stopping test *** */
    if (*iok != 0) {
	orsnrm = rsnrm;
	if (*istop == 0) {
	    nmresid_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 
		    50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &
		    fc[iz[lev * 50 + 1]], &x[iz[lev * 50 + 1]], &w1[1], &w2[1]
		    );
	    rsnrm = xnrm1_(&nxf, &nyf, &nzf, &w1[1]);
	} else if (*istop == 1) {
	    nmresid_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 
		    50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &
		    fc[iz[lev * 50 + 1]], &x[iz[lev * 50 + 1]], &w1[1], &w2[1]
		    );
	    rsnrm = xnrm1_(&nxf, &nyf, &nzf, &w1[1]);
	} else if (*istop == 2) {
	    xcopy_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]], &w1[1]);
	    xaxpy_(&nxf, &nyf, &nzf, &c_b36, &x[iz[lev * 50 + 1]], &w1[1]);
	    rsnrm = xnrm1_(&nxf, &nyf, &nzf, &w1[1]);
	    xcopy_(&nxf, &nyf, &nzf, &x[iz[lev * 50 + 1]], &tru[iz[lev * 50 + 
		    1]]);
	} else if (*istop == 3) {
	    xcopy_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]], &w1[1]);
	    xaxpy_(&nxf, &nyf, &nzf, &c_b36, &x[iz[lev * 50 + 1]], &w1[1]);
	    rsnrm = xnrm2_(&nxf, &nyf, &nzf, &w1[1]);
	} else if (*istop == 4) {
	    xcopy_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]], &w1[1]);
	    xaxpy_(&nxf, &nyf, &nzf, &c_b36, &x[iz[lev * 50 + 1]], &w1[1]);
	    rsnrm = xnrm2_(&nxf, &nyf, &nzf, &w1[1]);
	} else if (*istop == 5) {
	    xcopy_(&nxf, &nyf, &nzf, &tru[iz[lev * 50 + 1]], &w1[1]);
	    xaxpy_(&nxf, &nyf, &nzf, &c_b36, &x[iz[lev * 50 + 1]], &w1[1]);
	    nmatvec_(&nxf, &nyf, &nzf, &ipc[iz[lev * 50 + 5]], &rpc[iz[lev * 
		    50 + 6]], &ac[iz[lev * 50 + 7]], &cc[iz[lev * 50 + 1]], &
		    w1[1], &w2[1], &w3[1]);
	    rsnrm = sqrt(xdot_(&nxf, &nyf, &nzf, &w1[1], &w2[1]));
	} else {
	    s_wsle(&io___39);
	    do_lio(&c__9, &c__1, "% MVFAS: bad istop value... ", (ftnlen)28);
	    e_wsle();
	}
	prtstp_(iok, iters, &rsnrm, &rsden, &orsnrm);
	if (rsnrm / rsden <= *errtol) {
	    goto L99;
	}
    }
    if (*iters >= *itmax) {
	goto L91;
    }
    goto L30;
/* * */
/* *    *** problems *** */
L91:
    *ierror = 1;
/* * */
/* *    *** return and end *** */
L99:
    return 0;
} /* mvfas_ */

