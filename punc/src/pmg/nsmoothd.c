/* ./src_f77/nsmoothd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    nsmoothd.f */
/* * @author  Michael Holst */
/* * @brief   Generic nonlinear smoothing iteration. */
/* * @version $Id: nsmoothd.c,v 1.3 2010/08/12 05:45:27 fetk Exp $ */
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
/* Subroutine */ int nsmooth_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, 
	doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, 
	integer *itmax, integer *iters, doublereal *errtol, doublereal *omega,
	 integer *iresid, integer *iadjoint, integer *meth)
{
    /* System generated locals */
    integer ac_dim1, ac_offset, cc_dim1, cc_dim2, cc_offset, fc_dim1, fc_dim2,
	     fc_offset, x_dim1, x_dim2, x_offset, w1_dim1, w1_dim2, w1_offset,
	     w2_dim1, w2_dim2, w2_offset, r_dim1, r_dim2, r_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int nsor_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , integer *, doublereal *, doublereal *, integer *, integer *), 
	    nwjac_(integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, integer *), nrich_(integer 
	    *, integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, integer *, integer *), ngsrb_(integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, doublereal *, doublereal *, 
	    integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    call the appropriate nonlinear smoothing routine. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do in one step *** */
    /* Parameter adjustments */
    r_dim1 = *nx;
    r_dim2 = *ny;
    r_offset = 1 + r_dim1 * (1 + r_dim2);
    r__ -= r_offset;
    w2_dim1 = *nx;
    w2_dim2 = *ny;
    w2_offset = 1 + w2_dim1 * (1 + w2_dim2);
    w2 -= w2_offset;
    w1_dim1 = *nx;
    w1_dim2 = *ny;
    w1_offset = 1 + w1_dim1 * (1 + w1_dim2);
    w1 -= w1_offset;
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;
    fc_dim1 = *nx;
    fc_dim2 = *ny;
    fc_offset = 1 + fc_dim1 * (1 + fc_dim2);
    fc -= fc_offset;
    cc_dim1 = *nx;
    cc_dim2 = *ny;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
    cc -= cc_offset;
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;

    /* Function Body */
    if (*meth == 0) {
	nwjac_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[cc_offset], &
		fc[fc_offset], &x[x_offset], &w1[w1_offset], &w2[w2_offset], &
		r__[r_offset], itmax, iters, errtol, omega, iresid, iadjoint);
    } else if (*meth == 1) {
	ngsrb_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[cc_offset], &
		fc[fc_offset], &x[x_offset], &w1[w1_offset], &w2[w2_offset], &
		r__[r_offset], itmax, iters, errtol, omega, iresid, iadjoint);
    } else if (*meth == 2) {
	nsor_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[cc_offset], &
		fc[fc_offset], &x[x_offset], &w1[w1_offset], &w2[w2_offset], &
		r__[r_offset], itmax, iters, errtol, omega, iresid, iadjoint);
    } else if (*meth == 3) {
	nrich_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_offset], &cc[cc_offset], &
		fc[fc_offset], &x[x_offset], &w1[w1_offset], &w2[w2_offset], &
		r__[r_offset], itmax, iters, errtol, omega, iresid, iadjoint);
    } else {
	s_wsle(&io___1);
	do_lio(&c__9, &c__1, "% NSMOOTH: bad smoothing routine specified...", 
		(ftnlen)45);
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* nsmooth_ */

