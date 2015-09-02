/* ./src_f77/mikpckd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__3 = 3;
static doublereal c_b170 = -1.;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    mikpckd.f */
/* * @author  Michael Holst */
/* * @brief   A collection of useful low-level routines (timing, etc). */
/* * @version $Id: mikpckd.c,v 1.3 2010/08/12 05:45:23 fetk Exp $ */
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
doublereal epsmac_(integer *idum)
{
    /* System generated locals */
    doublereal ret_val;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    this routine computes the unit roundoff of the machine in single */
/* *    precision.  this is defined as the smallest positive machine */
/* *    number u such that  1.0d0 + u .ne. 1.0d0 (in single precision). */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * ***double precision u, comp */
/* * */
/* * ****** determine the machine epsilon *** */
/* * ***u = 1.0d0 */
/* * ***10 continue */
/* * ***   u = u*0.50d0 */
/* * ***   comp = 1.0d0 + u */
/* * ***if (comp .ne. 1.0d0) goto 10 */
/* * ***epsmac = u*2.0d0 */
/* * */
/* *    *** hardcoded *** */
    ret_val = 1e-9;
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* epsmac_ */

/* Subroutine */ int tstart_(doublereal *before, doublereal *overhd)
{
    static doublereal t0, t1, garbge;
    extern doublereal tsecnd_(void);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    this routine starts the timer on the particular machine. */
/* * */
/* *    the routine uses my own "c" routine timer, which works for most */
/* *    unix systems, including (atleast): */
/* * */
/* *       convex c240 */
/* *       sun 4 */
/* *       sun 3 */
/* *       alliant fx/80 */
/* * */
/* *    this routine is also correct for the native "tsecnd" (which is */
/* *    for multitasked programs, rather than "second" for single task */
/* *    programs) routine on the following machines: */
/* * */
/* *       cray ymp */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** compute overhead and mark timer *** */
    garbge = tsecnd_();
    t0 = tsecnd_();
    t1 = tsecnd_();
    *overhd = t1 - t0;
    *before = tsecnd_();
/* * */
/* *    *** return and end *** */
    return 0;
} /* tstart_ */

/* Subroutine */ int tstop_(doublereal *before, doublereal *overhd, 
	doublereal *cputme)
{
    static doublereal after;
    extern doublereal tsecnd_(void);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    this routine stops the timer on the particular machine. */
/* * */
/* *    the routine uses my own "c" routine timer, which works for most */
/* *    unix systems, including (atleast): */
/* * */
/* *       convex c240 */
/* *       sun 4 */
/* *       sun 3 */
/* *       alliant fx/80 */
/* * */
/* *    this routine is also correct for the native "tsecnd" (which is */
/* *    for multitasked programs, rather than "second" for single task */
/* *    programs) routine on the following machines: */
/* * */
/* *       cray ymp */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** stop timer, compute elapsed time, add to time counter *** */
    after = tsecnd_();
    *cputme = after - *before - *overhd;
/* * */
/* *    *** return and end *** */
    return 0;
} /* tstop_ */

/* Subroutine */ int xaxpy_(integer *nx, integer *ny, integer *nz, doublereal 
	*alpha, doublereal *x, doublereal *y)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, y_dim1, y_dim2, y_offset, i__1, i__2, 
	    i__3;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    saxpy operation for a grid function with boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    y_dim1 = *nx;
    y_dim2 = *ny;
    y_offset = 1 + y_dim1 * (1 + y_dim2);
    y -= y_offset;
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		y[i__ + (j + k * y_dim2) * y_dim1] += *alpha * x[i__ + (j + k 
			* x_dim2) * x_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* xaxpy_ */

/* Subroutine */ int xcopy_(integer *nx, integer *ny, integer *nz, doublereal 
	*x, doublereal *y)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, y_dim1, y_dim2, y_offset, i__1, i__2, 
	    i__3;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    copy operation for a grid function with boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    y_dim1 = *nx;
    y_dim2 = *ny;
    y_offset = 1 + y_dim1 * (1 + y_dim2);
    y -= y_offset;
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		y[i__ + (j + k * y_dim2) * y_dim1] = x[i__ + (j + k * x_dim2) 
			* x_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* xcopy_ */

doublereal xnrm1_(integer *nx, integer *ny, integer *nz, doublereal *x)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, i__1, i__2, i__3;
    doublereal ret_val, d__1;

    /* Local variables */
    static integer i__, j, k;
    static doublereal tmp;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    norm operation for a grid function with boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** initialize *** */
    /* Parameter adjustments */
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    tmp = 0.;
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		tmp += (d__1 = x[i__ + (j + k * x_dim2) * x_dim1], abs(d__1));
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** finish up *** */
    ret_val = tmp;
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* xnrm1_ */

doublereal xnrm2_(integer *nx, integer *ny, integer *nz, doublereal *x)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, i__1, i__2, i__3;
    doublereal ret_val;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, j, k;
    static doublereal tmp;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    norm operation for a grid function with boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** initialize *** */
    /* Parameter adjustments */
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    tmp = 0.;
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		tmp += x[i__ + (j + k * x_dim2) * x_dim1] * x[i__ + (j + k * 
			x_dim2) * x_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** finish up *** */
    ret_val = sqrt(tmp);
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* xnrm2_ */

doublereal xnrm8_(integer *nx, integer *ny, integer *nz, doublereal *x)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, i__1, i__2, i__3;
    doublereal ret_val, d__1, d__2, d__3;

    /* Local variables */
    static integer i__, j, k;
    static doublereal tmp;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    norm operation for a grid function with boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** initialize *** */
    /* Parameter adjustments */
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    tmp = 0.;
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
/* Computing MAX */
		d__2 = tmp, d__3 = (d__1 = x[i__ + (j + k * x_dim2) * x_dim1],
			 abs(d__1));
		tmp = max(d__2,d__3);
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** finish up *** */
    ret_val = tmp;
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* xnrm8_ */

/* Subroutine */ int xscal_(integer *nx, integer *ny, integer *nz, doublereal 
	*fac, doublereal *x)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    scale operation for a grid function with boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		x[i__ + (j + k * x_dim2) * x_dim1] = *fac * x[i__ + (j + k * 
			x_dim2) * x_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* xscal_ */

doublereal xdot_(integer *nx, integer *ny, integer *nz, doublereal *x, 
	doublereal *y)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, y_dim1, y_dim2, y_offset, i__1, i__2, 
	    i__3;
    doublereal ret_val;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    inner product operation for a grid function with boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** initialize *** */
    /* Parameter adjustments */
    y_dim1 = *nx;
    y_dim2 = *ny;
    y_offset = 1 + y_dim1 * (1 + y_dim2);
    y -= y_offset;
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    ret_val = 0.;
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		ret_val += x[i__ + (j + k * x_dim2) * x_dim1] * y[i__ + (j + 
			k * y_dim2) * y_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* xdot_ */

doublereal xdot3_(integer *nx, integer *ny, integer *nz, doublereal *x, 
	doublereal *y)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, y_dim1, y_dim2, y_offset, i__1, i__2, 
	    i__3;
    doublereal ret_val;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    necessary mess. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** initialize *** */
    /* Parameter adjustments */
    y_dim1 = *nx;
    y_dim2 = *ny;
    y_offset = 1 + y_dim1 * (1 + y_dim2);
    y -= y_offset;
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    ret_val = 0.;
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		ret_val += x[i__ + (j + k * x_dim2) * x_dim1] * y[i__ + (j + 
			k * y_dim2) * y_dim1] * y[i__ + (j + k * y_dim2) * 
			y_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* xdot3_ */

/* Subroutine */ int zeros_(integer *nx, integer *ny, integer *nz, doublereal 
	*x)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    zero out operation for a grid function with boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		x[i__ + (j + k * x_dim2) * x_dim1] = 0.;
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* zeros_ */

/* Subroutine */ int xrand_(integer *nx, integer *ny, integer *nz, doublereal 
	*x)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;
    extern doublereal rand_(integer *);
    static doublereal xdum;
    static integer iflag;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    fill grid function with random values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
    /* Parameter adjustments */
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    iflag = 1;
    xdum = (doublereal) rand_(&iflag);
/* mdir 3 1 */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		x[i__ + (j + k * x_dim2) * x_dim1] = (doublereal) rand_(&
			iflag);
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* xrand_ */

/* Subroutine */ int cinit_(integer *nx, integer *ny, integer *nz, doublereal 
	*x, doublereal *value)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    initialize a grid function to a specific constant, without */
/* *    changing the boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		x[i__ + (j + k * x_dim2) * x_dim1] = *value;
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* cinit_ */

/* Subroutine */ int azeros_(integer *nx, integer *ny, integer *nz, 
	doublereal *x)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, n, ii, ipara, ivect;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    zero out operation for a grid function, including boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** find parallel loops (ipara), remainder (ivect) *** */
    /* Parameter adjustments */
    --x;

    /* Function Body */
    n = *nx * *ny * *nz;
    ipara = n;
    ivect = n % 1;
/* * */
/* *    *** do parallel loops *** */
/* mdir 2 1 */
    for (ii = 1; ii <= 1; ++ii) {
/* mdir 2 2 */
	i__1 = ipara * ii;
	for (i__ = ipara * (ii - 1) + 1; i__ <= i__1; ++i__) {
	    x[i__] = 0.;
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** do vector loops *** */
/* mdir 1 1 */
    i__1 = n;
    for (i__ = ipara + 1; i__ <= i__1; ++i__) {
	x[i__] = 0.;
/* L20: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* azeros_ */

/* Subroutine */ int axrand_(integer *nx, integer *ny, integer *nz, 
	doublereal *x)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, n, ii;
    extern doublereal rand_(integer *);
    static doublereal xdum;
    static integer iflag, ipara, ivect;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    fill grid function with random values, including boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** find parallel loops (ipara), remainder (ivect) *** */
    /* Parameter adjustments */
    --x;

    /* Function Body */
    n = *nx * *ny * *nz;
    ipara = n;
    ivect = n % 1;
    iflag = 1;
    xdum = (doublereal) rand_(&iflag);
/* * */
/* *    *** do parallel loops *** */
/* mdir 2 1 */
    for (ii = 1; ii <= 1; ++ii) {
/* mdir 2 2 */
	i__1 = ipara * ii;
	for (i__ = ipara * (ii - 1) + 1; i__ <= i__1; ++i__) {
	    x[i__] = (doublereal) rand_(&iflag);
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** do vector loops *** */
/* mdir 1 1 */
    i__1 = n;
    for (i__ = ipara + 1; i__ <= i__1; ++i__) {
	x[i__] = (doublereal) rand_(&iflag);
/* L20: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* axrand_ */

/* Subroutine */ int xcopy_small__(integer *nx, integer *ny, integer *nz, 
	doublereal *x, doublereal *y)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, y_dim1, y_dim2, y_offset, i__1, i__2, 
	    i__3;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    copy operation for a grid function with boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    y_dim1 = *nx - 2;
    y_dim2 = *ny - 2;
    y_offset = 1 + y_dim1 * (1 + y_dim2);
    y -= y_offset;
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		y[i__ - 1 + (j - 1 + (k - 1) * y_dim2) * y_dim1] = x[i__ + (j 
			+ k * x_dim2) * x_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* xcopy_small__ */

/* Subroutine */ int xcopy_large__(integer *nx, integer *ny, integer *nz, 
	doublereal *x, doublereal *y)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, y_dim1, y_dim2, y_offset, i__1, i__2, 
	    i__3;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    copy operation for a grid function with boundary values. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** do it *** */
/* mdir 3 1 */
    /* Parameter adjustments */
    y_dim1 = *nx;
    y_dim2 = *ny;
    y_offset = 1 + y_dim1 * (1 + y_dim2);
    y -= y_offset;
    x_dim1 = *nx - 2;
    x_dim2 = *ny - 2;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
/* mdir 3 2 */
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
/* mdir 3 3 */
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		y[i__ + (j + k * y_dim2) * y_dim1] = x[i__ - 1 + (j - 1 + (k 
			- 1) * x_dim2) * x_dim1];
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* xcopy_large__ */

/* Subroutine */ int fbound_(integer *ibound, integer *nx, integer *ny, 
	integer *nz, doublereal *x, doublereal *gxc, doublereal *gyc, 
	doublereal *gzc)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, gxc_dim1, gxc_dim2, gxc_offset, 
	    gyc_dim1, gyc_dim2, gyc_offset, gzc_dim1, gzc_dim2, gzc_offset, 
	    i__1, i__2;

    /* Local variables */
    static integer i__, j, k;
    extern /* Subroutine */ int fbound00_(integer *, integer *, integer *, 
	    doublereal *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    initialize a grid function to have a certain boundary value, */
/* *    given in the arrays gxc,gyc,gzc */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** zero dirichlet? *** */
    /* Parameter adjustments */
    gzc_dim1 = *nx;
    gzc_dim2 = *ny;
    gzc_offset = 1 + gzc_dim1 * (1 + gzc_dim2);
    gzc -= gzc_offset;
    gyc_dim1 = *nx;
    gyc_dim2 = *nz;
    gyc_offset = 1 + gyc_dim1 * (1 + gyc_dim2);
    gyc -= gyc_offset;
    gxc_dim1 = *ny;
    gxc_dim2 = *nz;
    gxc_offset = 1 + gxc_dim1 * (1 + gxc_dim2);
    gxc -= gxc_offset;
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    if (*ibound == 0) {
	fbound00_(nx, ny, nz, &x[x_offset]);
/* * */
/* *    *** nonzero dirichlet *** */
    } else {
/* *       *** the (i=1) and (i=nx) boundaries *** */
/* mdir 2 1 */
	i__1 = *nz;
	for (k = 1; k <= i__1; ++k) {
/* mdir 2 2 */
	    i__2 = *ny;
	    for (j = 1; j <= i__2; ++j) {
		x[(j + k * x_dim2) * x_dim1 + 1] = gxc[j + (k + gxc_dim2) * 
			gxc_dim1];
		x[*nx + (j + k * x_dim2) * x_dim1] = gxc[j + (k + (gxc_dim2 <<
			 1)) * gxc_dim1];
/* L11: */
	    }
/* L10: */
	}
/* * */
/* *       *** the (j=1) and (j=ny) boundaries *** */
/* mdir 2 1 */
	i__1 = *nz;
	for (k = 1; k <= i__1; ++k) {
/* mdir 2 2 */
	    i__2 = *nx;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		x[i__ + (k * x_dim2 + 1) * x_dim1] = gyc[i__ + (k + gyc_dim2) 
			* gyc_dim1];
		x[i__ + (*ny + k * x_dim2) * x_dim1] = gyc[i__ + (k + (
			gyc_dim2 << 1)) * gyc_dim1];
/* L21: */
	    }
/* L20: */
	}
/* * */
/* *       *** the (k=1) and (k=nz) boundaries *** */
/* mdir 2 1 */
	i__1 = *ny;
	for (j = 1; j <= i__1; ++j) {
/* mdir 2 2 */
	    i__2 = *nx;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		x[i__ + (j + x_dim2) * x_dim1] = gzc[i__ + (j + gzc_dim2) * 
			gzc_dim1];
		x[i__ + (j + *nz * x_dim2) * x_dim1] = gzc[i__ + (j + (
			gzc_dim2 << 1)) * gzc_dim1];
/* L31: */
	    }
/* L30: */
	}
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* fbound_ */

/* Subroutine */ int fbound00_(integer *nx, integer *ny, integer *nz, 
	doublereal *x)
{
    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, i__1, i__2;

    /* Local variables */
    static integer i__, j, k;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    initialize a grid function to have a zero boundary value, */
/* *    given in the arrays gxc,gyc,gzc */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** the (i=1) and (i=nx) boundaries *** */
/* mdir 2 1 */
    /* Parameter adjustments */
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    i__1 = *nz;
    for (k = 1; k <= i__1; ++k) {
/* mdir 2 2 */
	i__2 = *ny;
	for (j = 1; j <= i__2; ++j) {
	    x[(j + k * x_dim2) * x_dim1 + 1] = 0.;
	    x[*nx + (j + k * x_dim2) * x_dim1] = 0.;
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** the (j=1) and (j=ny) boundaries *** */
/* mdir 2 1 */
    i__1 = *nz;
    for (k = 1; k <= i__1; ++k) {
/* mdir 2 2 */
	i__2 = *nx;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    x[i__ + (k * x_dim2 + 1) * x_dim1] = 0.;
	    x[i__ + (*ny + k * x_dim2) * x_dim1] = 0.;
/* L21: */
	}
/* L20: */
    }
/* * */
/* *    *** the (k=1) and (k=nz) boundaries *** */
/* mdir 2 1 */
    i__1 = *ny;
    for (j = 1; j <= i__1; ++j) {
/* mdir 2 2 */
	i__2 = *nx;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    x[i__ + (j + x_dim2) * x_dim1] = 0.;
	    x[i__ + (j + *nz * x_dim2) * x_dim1] = 0.;
/* L31: */
	}
/* L30: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* fbound00_ */

/* Subroutine */ int xprint_(integer *nx, integer *ny, integer *nz, 
	doublereal *x)
{
    /* Format strings */
    static char fmt_100[] = "(100(1x,1pe8.1))";

    /* System generated locals */
    integer x_dim1, x_dim2, x_offset, i__1, i__2, i__3;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void), s_wsfe(cilist *), do_fio(integer *, char *, ftnlen),
	     e_wsfe(void);

    /* Local variables */
    static integer i__, j, k;
    static char title[10];

    /* Fortran I/O blocks */
    static cilist io___67 = { 0, 6, 0, 0, 0 };
    static cilist io___71 = { 0, 6, 0, fmt_100, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    this routine prints a grid function. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** doit *** */
    /* Parameter adjustments */
    x_dim1 = *nx;
    x_dim2 = *ny;
    x_offset = 1 + x_dim1 * (1 + x_dim2);
    x -= x_offset;

    /* Function Body */
    s_wsle(&io___67);
    do_lio(&c__9, &c__1, title, (ftnlen)10);
    e_wsle();
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
	    s_wsfe(&io___71);
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		do_fio(&c__1, (char *)&x[i__ + (j + k * x_dim2) * x_dim1], (
			ftnlen)sizeof(doublereal));
	    }
	    e_wsfe();
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* xprint_ */

/* Subroutine */ int prtmatd_(integer *nx, integer *ny, integer *nz, integer *
	ipc, doublereal *rpc, doublereal *ac)
{
    /* System generated locals */
    integer ac_dim1, ac_offset;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern /* Subroutine */ int prtmatd7_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *), prtmatd27_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static integer numdia;

    /* Fortran I/O blocks */
    static cilist io___74 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    interface to routine to print sparse diagonal-format matrix. */
/* * */
/* * note: */
/* * */
/* *    the matrix is symmetric, therefore we print only the main and */
/* *    upper diagonals. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** do the printing *** */
    /* Parameter adjustments */
    ac_dim1 = *nx * *ny * *nz;
    ac_offset = 1 + ac_dim1;
    ac -= ac_offset;
    --ipc;
    --rpc;

    /* Function Body */
    numdia = ipc[11];
    if (numdia == 7) {
	prtmatd7_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &ac[(
		ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) 
		+ 1]);
    } else if (numdia == 27) {
	prtmatd27_(nx, ny, nz, &ipc[1], &rpc[1], &ac[ac_dim1 + 1], &ac[(
		ac_dim1 << 1) + 1], &ac[ac_dim1 * 3 + 1], &ac[(ac_dim1 << 2) 
		+ 1], &ac[ac_dim1 * 5 + 1], &ac[ac_dim1 * 6 + 1], &ac[ac_dim1 
		* 7 + 1], &ac[(ac_dim1 << 3) + 1], &ac[ac_dim1 * 9 + 1], &ac[
		ac_dim1 * 10 + 1], &ac[ac_dim1 * 11 + 1], &ac[ac_dim1 * 12 + 
		1], &ac[ac_dim1 * 13 + 1], &ac[ac_dim1 * 14 + 1]);
    } else {
	s_wsle(&io___74);
	do_lio(&c__9, &c__1, "% PRTMATD: invalid stencil type given...", (
		ftnlen)40);
	e_wsle();
    }
/* * */
/* *    *** go home *** */
    return 0;
} /* prtmatd_ */

/* Subroutine */ int prtmatd7_(integer *nx, integer *ny, integer *nz, integer 
	*ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on,
	 doublereal *uc)
{
    /* Format strings */
    static char fmt_104[] = "(4(1pe8.1,1x))";

    /* System generated locals */
    integer oc_dim1, oc_dim2, oc_offset, oe_dim1, oe_dim2, oe_offset, on_dim1,
	     on_dim2, on_offset, uc_dim1, uc_dim2, uc_offset, i__1, i__2, 
	    i__3;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void), s_wsfe(cilist *), do_fio(integer *, char *, ftnlen),
	     e_wsfe(void);

    /* Local variables */
    static integer i__, j, k, n;

    /* Fortran I/O blocks */
    static cilist io___76 = { 0, 6, 0, 0, 0 };
    static cilist io___77 = { 0, 6, 0, 0, 0 };
    static cilist io___78 = { 0, 6, 0, 0, 0 };
    static cilist io___82 = { 0, 6, 0, fmt_104, 0 };
    static cilist io___83 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    routine to print sparse 7-diagonal-format matrix. */
/* * */
/* * note: */
/* * */
/* *    the matrix is symmetric, therefore we print only the main and */
/* *    upper diagonals. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** recover matrix dimension *** */
    /* Parameter adjustments */
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
    oc_dim1 = *nx;
    oc_dim2 = *ny;
    oc_offset = 1 + oc_dim1 * (1 + oc_dim2);
    oc -= oc_offset;
    --ipc;
    --rpc;

    /* Function Body */
    n = (*nx - 2) * (*ny - 2) * (*nz - 2);
    s_wsle(&io___76);
    do_lio(&c__9, &c__1, "% ", (ftnlen)2);
    e_wsle();
    s_wsle(&io___77);
    do_lio(&c__9, &c__1, "% dimension of matrix = ", (ftnlen)24);
    do_lio(&c__3, &c__1, (char *)&n, (ftnlen)sizeof(integer));
    e_wsle();
    s_wsle(&io___78);
    do_lio(&c__9, &c__1, "% *begin diagonal matrix* ", (ftnlen)26);
    e_wsle();
/* * */
/* *    *** handle first block *** */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		s_wsfe(&io___82);
		do_fio(&c__1, (char *)&oc[i__ + (j + k * oc_dim2) * oc_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&oe[i__ + (j + k * oe_dim2) * oe_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&on[i__ + (j + k * on_dim2) * on_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&uc[i__ + (j + k * uc_dim2) * uc_dim1], 
			(ftnlen)sizeof(doublereal));
		e_wsfe();
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** finish up *** */
    s_wsle(&io___83);
    do_lio(&c__9, &c__1, "% *end diagonal matrix* ", (ftnlen)24);
    e_wsle();
/* * */
/* *    *** format statements *** */
/* * */
/* *    *** return and end *** */
    return 0;
} /* prtmatd7_ */

/* Subroutine */ int prtmatd27_(integer *nx, integer *ny, integer *nz, 
	integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, 
	doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, 
	doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, 
	doublereal *une, doublereal *unw, doublereal *use, doublereal *usw)
{
    /* Format strings */
    static char fmt_114[] = "(14(1pe8.1,1x))";

    /* System generated locals */
    integer oc_dim1, oc_dim2, oc_offset, oe_dim1, oe_dim2, oe_offset, on_dim1,
	     on_dim2, on_offset, uc_dim1, uc_dim2, uc_offset, one_dim1, 
	    one_dim2, one_offset, onw_dim1, onw_dim2, onw_offset, ue_dim1, 
	    ue_dim2, ue_offset, uw_dim1, uw_dim2, uw_offset, un_dim1, un_dim2,
	     un_offset, us_dim1, us_dim2, us_offset, une_dim1, une_dim2, 
	    une_offset, unw_dim1, unw_dim2, unw_offset, use_dim1, use_dim2, 
	    use_offset, usw_dim1, usw_dim2, usw_offset, i__1, i__2, i__3;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void), s_wsfe(cilist *), do_fio(integer *, char *, ftnlen),
	     e_wsfe(void);

    /* Local variables */
    static integer i__, j, k, n;

    /* Fortran I/O blocks */
    static cilist io___85 = { 0, 6, 0, 0, 0 };
    static cilist io___86 = { 0, 6, 0, 0, 0 };
    static cilist io___87 = { 0, 6, 0, 0, 0 };
    static cilist io___91 = { 0, 6, 0, fmt_114, 0 };
    static cilist io___92 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    routine to print sparse 27-diagonal-format matrix. */
/* * */
/* * note: */
/* * */
/* *    the matrix is symmetric, therefore we print only the main and */
/* *    upper diagonals. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** recover matrix dimension *** */
    /* Parameter adjustments */
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
    oc_dim1 = *nx;
    oc_dim2 = *ny;
    oc_offset = 1 + oc_dim1 * (1 + oc_dim2);
    oc -= oc_offset;
    --ipc;
    --rpc;

    /* Function Body */
    n = (*nx - 2) * (*ny - 2) * (*nz - 2);
    s_wsle(&io___85);
    do_lio(&c__9, &c__1, "% ", (ftnlen)2);
    e_wsle();
    s_wsle(&io___86);
    do_lio(&c__9, &c__1, "% dimension of matrix = ", (ftnlen)24);
    do_lio(&c__3, &c__1, (char *)&n, (ftnlen)sizeof(integer));
    e_wsle();
    s_wsle(&io___87);
    do_lio(&c__9, &c__1, "% *begin diagonal matrix* ", (ftnlen)26);
    e_wsle();
/* * */
/* *    *** handle first block *** */
    i__1 = *nz - 1;
    for (k = 2; k <= i__1; ++k) {
	i__2 = *ny - 1;
	for (j = 2; j <= i__2; ++j) {
	    i__3 = *nx - 1;
	    for (i__ = 2; i__ <= i__3; ++i__) {
		s_wsfe(&io___91);
		do_fio(&c__1, (char *)&oc[i__ + (j + k * oc_dim2) * oc_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&oe[i__ + (j + k * oe_dim2) * oe_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&onw[i__ + (j + k * onw_dim2) * 
			onw_dim1], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&on[i__ + (j + k * on_dim2) * on_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&one[i__ + (j + k * one_dim2) * 
			one_dim1], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&usw[i__ + (j + k * usw_dim2) * 
			usw_dim1], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&us[i__ + (j + k * us_dim2) * us_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&use[i__ + (j + k * use_dim2) * 
			use_dim1], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&uw[i__ + (j + k * uw_dim2) * uw_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&uc[i__ + (j + k * uc_dim2) * uc_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ue[i__ + (j + k * ue_dim2) * ue_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&unw[i__ + (j + k * unw_dim2) * 
			unw_dim1], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&un[i__ + (j + k * un_dim2) * un_dim1], 
			(ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&une[i__ + (j + k * une_dim2) * 
			une_dim1], (ftnlen)sizeof(doublereal));
		e_wsfe();
/* L12: */
	    }
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** finish up *** */
    s_wsle(&io___92);
    do_lio(&c__9, &c__1, "% *end diagonal matrix* ", (ftnlen)24);
    e_wsle();
/* * */
/* *    *** format statements *** */
/* * */
/* *    *** return and end *** */
    return 0;
} /* prtmatd27_ */

/* Subroutine */ int prtmatb_(doublereal *a, integer *n, integer *m, integer *
	lda)
{
    /* Format strings */
    static char fmt_100[] = "(30(1x,1pe8.1))";

    /* System generated locals */
    integer a_dim1, a_offset, i__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void), s_wsfe(cilist *), do_fio(integer *, char *, ftnlen),
	     e_wsfe(void);

    /* Local variables */
    static integer i__, j;

    /* Fortran I/O blocks */
    static cilist io___93 = { 0, 6, 0, 0, 0 };
    static cilist io___94 = { 0, 6, 0, 0, 0 };
    static cilist io___95 = { 0, 6, 0, 0, 0 };
    static cilist io___97 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___99 = { 0, 6, 0, 0, 0 };


/* *********************************************************************** */
/* * purpose: */
/* * */
/* *    routine to print sparse banded-format matrix. */
/* * */
/* * note: */
/* * */
/* *    the matrix is symmetric, therefore we print only the main and */
/* *    upper diagonal bands. */
/* * */
/* *********************************************************************** */

/*     *** recover matrix dimension *** */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    s_wsle(&io___93);
    do_lio(&c__9, &c__1, " ", (ftnlen)1);
    e_wsle();
    s_wsle(&io___94);
    do_lio(&c__9, &c__1, " dimension of matrix = ", (ftnlen)23);
    do_lio(&c__3, &c__1, (char *)&(*n), (ftnlen)sizeof(integer));
    e_wsle();
    s_wsle(&io___95);
    do_lio(&c__9, &c__1, " *begin banded matrix* ", (ftnlen)23);
    e_wsle();

/*     *** do the printing *** */
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	s_wsfe(&io___97);
	for (i__ = *lda; i__ >= 1; --i__) {
	    do_fio(&c__1, (char *)&a[i__ + j * a_dim1], (ftnlen)sizeof(
		    doublereal));
	}
	e_wsfe();
/* L10: */
    }

/*     *** finish up *** */
    s_wsle(&io___99);
    do_lio(&c__9, &c__1, " *end banded matrix* ", (ftnlen)21);
    e_wsle();

/*     *** format statements *** */

/*     *** go home *** */
    return 0;
} /* prtmatb_ */

/* Subroutine */ int linesearch_(integer *nx, integer *ny, integer *nz, 
	doublereal *alpha, integer *ipc, doublereal *rpc, doublereal *ac, 
	doublereal *cc, doublereal *fc, doublereal *p, doublereal *x, 
	doublereal *r__, doublereal *ap, doublereal *zk, doublereal *zkp1)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer ifail_tol__;
    static doublereal pr, alp, pap, val, znn, dznn;
    extern doublereal xdot_(integer *, integer *, integer *, doublereal *, 
	    doublereal *), xdot3_(integer *, integer *, integer *, doublereal 
	    *, doublereal *);
    extern /* Subroutine */ int c_vec__(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *);
    static integer ipkey;
    extern /* Subroutine */ int xcopy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *);
    static doublereal zntol;
    extern /* Subroutine */ int xaxpy_(integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *), dc_vec__(doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *), matvec_(integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static integer nitmax, niters;
    static doublereal alp_old__;

    /* Fortran I/O blocks */
    static cilist io___112 = { 0, 6, 0, 0, 0 };


/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    line search for a minimizing steplength given a descent direction. */
/* * */
/* * input: */
/* * */
/* *    nx,ny,nz = mesh dimensions */
/* *    ipc,rpc  = operator/level information */
/* *    ac,cc,fc = operator/level entries */
/* *    p        = the direction */
/* *    x        = the previous solution */
/* *    r        = the previous nonlinear residual, r=r(x) */
/* * */
/* * temporary vectors: */
/* * */
/* *    ap,zk,zkp1 = used as temp vectors, passed back as needed for the */
/* *                 nonlinear fletcher-reeves conjugate gradient algorithm */
/* *                 (can be ignored otherwise) */
/* *    r          = is definitely overwritten */
/* * */
/* * output: */
/* * */
/* *    alpha = steplength for minimizing the 1d problem in direction p. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* *    *** other declarations *** */
/* * */
/* *    *** nonlinear iteration tolerance and itmax *** */
    /* Parameter adjustments */
    --zkp1;
    --zk;
    --ap;
    --r__;
    --x;
    --p;
    --fc;
    --cc;
    --ac;
    --rpc;
    --ipc;

    /* Function Body */
    nitmax = 20;
    zntol = 1e-5f;
    ifail_tol__ = 0;
    ipkey = ipc[10];
/* * */
/* * ********************************************************************* */
/* * *** begin linear case for choosing alpha */
/* * ********************************************************************* */
/* * */
/* *    *** compute the hackbusch/reusken damping parameter *** */
/* *    *** which is equivalent to the standard linear cg steplength *** */
    matvec_(nx, ny, nz, &ipc[1], &rpc[1], &ac[1], &cc[1], &p[1], &ap[1]);
    pr = xdot_(nx, ny, nz, &p[1], &r__[1]);
    pap = xdot_(nx, ny, nz, &p[1], &ap[1]);
    *alpha = pr / pap;
/* * */
/* * ********************************************************************* */
/* * *** begin nonlinear case for choosing alpha */
/* * ********************************************************************* */
/* * */
/* *    *** initialize ALP (use linear approx) and zkp1 *** */
    alp = *alpha;
    xcopy_(nx, ny, nz, &x[1], &r__[1]);
    xaxpy_(nx, ny, nz, &alp, &p[1], &r__[1]);
    c_vec__(&cc[1], &x[1], &zk[1], nx, ny, nz, &ipkey);
    c_vec__(&cc[1], &r__[1], &zkp1[1], nx, ny, nz, &ipkey);
/* * */
/* *    *** evaluate residual of 1d system */
    xcopy_(nx, ny, nz, &zkp1[1], &r__[1]);
    xaxpy_(nx, ny, nz, &c_b170, &zk[1], &r__[1]);
    val = xdot_(nx, ny, nz, &p[1], &r__[1]);
    znn = alp * pap - pr + val;
/* * */
/* *    *** setup for newton's method */
    niters = 0;
/* * */
/* *    *** the 1d newton's method *** */
    if (niters > nitmax) {
	goto L16;
    }
    ifail_tol__ = 0;
    alp_old__ = alp;
L15:
    ++niters;
/* * */
/* *       *** some i/o *** */
/* * **    write(6,110) */
/* * **2      'LINESEARCH: 1d newton iterations: niters, alpha = ', */
/* * **3      niters,alpha */
/* * **       format('% ',a,i5,1pe10.2) */
/* * */
/* *       *** construct jacobian matrix of NN *** */
    dc_vec__(&cc[1], &r__[1], &zkp1[1], nx, ny, nz, &ipkey);
    val = xdot3_(nx, ny, nz, &zkp1[1], &p[1]);
    dznn = pap + val;
/* * */
/* *       *** update the solution *** */
    alp_old__ = alp;
    alp -= znn / dznn;
/* * */
/* *       *** evaluate residual of 1d system *** */
    xcopy_(nx, ny, nz, &x[1], &r__[1]);
    xaxpy_(nx, ny, nz, &alp, &p[1], &r__[1]);
    c_vec__(&cc[1], &r__[1], &zkp1[1], nx, ny, nz, &ipkey);
    xcopy_(nx, ny, nz, &zkp1[1], &r__[1]);
    xaxpy_(nx, ny, nz, &c_b170, &zk[1], &r__[1]);
    val = xdot_(nx, ny, nz, &p[1], &r__[1]);
    znn = alp * pap - pr + val;
/* * */
/* *       *** tolerance and itmax check *** */
    if (abs(znn) < zntol && (d__1 = (alp - alp_old__) / alp, abs(d__1)) < 
	    zntol) {
	goto L17;
    }
    if (niters > nitmax) {
	goto L16;
    }
/* * */
/* *    *** loop *** */
    goto L15;
/* * */
/* *    *** tolerance not reached *** */
L16:
    ++ifail_tol__;
/* * */
/* *    *** tolerance reached *** */
L17:
/* * */
/* *    *** newton's method complete -- update solution value *** */
    *alpha = alp;
/* * */
/* *    *** messages *** */
    if (ifail_tol__ > 0) {
	s_wsle(&io___112);
	do_lio(&c__9, &c__1, "% LINESEARCH: exceeded 1d newton itmax: = ", (
		ftnlen)42);
	do_lio(&c__3, &c__1, (char *)&nitmax, (ftnlen)sizeof(integer));
	e_wsle();
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* linesearch_ */

