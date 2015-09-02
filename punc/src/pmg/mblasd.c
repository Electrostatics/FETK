/* ./src_f77/mblasd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    mblasd.f */
/* * @author  Michael Holst */
/* * @brief   Micro version of the BLAS needed for low-level PMG support. */
/* * @version $Id: mblasd.c,v 1.3 2010/08/12 05:45:22 fetk Exp $ */
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
/* Subroutine */ int daxpy_(integer *n, doublereal *alpha, doublereal *x, 
	integer *istep, doublereal *y, integer *jstep)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, ii, ipara, ivect;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    parallel/vector vector saxpy. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** find parallel loops (ipara), remainder (ivect) *** */
    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
    ipara = *n;
    ivect = *n % 1;
/* * */
/* *    *** do parallel loops *** */
/* mdir 2 1 */
    for (ii = 1; ii <= 1; ++ii) {
/* mdir 2 2 */
	i__1 = ipara * ii;
	for (i__ = ipara * (ii - 1) + 1; i__ <= i__1; ++i__) {
	    y[i__] += *alpha * x[i__];
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** do vector loops *** */
/* mdir 1 1 */
    i__1 = *n;
    for (i__ = ipara + 1; i__ <= i__1; ++i__) {
	y[i__] += *alpha * x[i__];
/* L20: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* daxpy_ */

/* Subroutine */ int dcopy_(integer *n, doublereal *x, integer *istep, 
	doublereal *y, integer *jstep)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, ii, ipara, ivect;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    parallel/vector vector copy. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** find parallel loops (ipara), remainder (ivect) *** */
    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
    ipara = *n;
    ivect = *n % 1;
/* * */
/* *    *** do parallel loops *** */
/* mdir 2 1 */
    for (ii = 1; ii <= 1; ++ii) {
/* mdir 2 2 */
	i__1 = ipara * ii;
	for (i__ = ipara * (ii - 1) + 1; i__ <= i__1; ++i__) {
	    y[i__] = x[i__];
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** do vector loops *** */
/* mdir 1 1 */
    i__1 = *n;
    for (i__ = ipara + 1; i__ <= i__1; ++i__) {
	y[i__] = x[i__];
/* L20: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* dcopy_ */

doublereal dasum_(integer *n, doublereal *x, integer *istep)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal dnrm1_(integer *, doublereal *, integer *);

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    parallel/vector sum of vector components. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** call the max-norm function *** */
    /* Parameter adjustments */
    --x;

    /* Function Body */
    ret_val = dnrm1_(n, &x[1], istep);
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* dasum_ */

doublereal dnrm1_(integer *n, doublereal *x, integer *istep)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1;

    /* Local variables */
    static integer i__, ii;
    static doublereal tmp;
    static integer ipara, ivect;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    parallel/vector vector norm. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** initialize *** */
    /* Parameter adjustments */
    --x;

    /* Function Body */
    tmp = 0.;
/* * */
/* *    *** find parallel loops (ipara), remainder (ivect) *** */
    ipara = *n;
    ivect = *n % 1;
/* * */
/* *    *** do parallel loops *** */
/* mdir 2 1 */
    for (ii = 1; ii <= 1; ++ii) {
/* mdir 2 2 */
	i__1 = ipara * ii;
	for (i__ = ipara * (ii - 1) + 1; i__ <= i__1; ++i__) {
	    tmp += (d__1 = x[i__], abs(d__1));
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** do vector loops *** */
/* mdir 1 1 */
    i__1 = *n;
    for (i__ = ipara + 1; i__ <= i__1; ++i__) {
	tmp += (d__1 = x[i__], abs(d__1));
/* L20: */
    }
/* * */
/* *    *** finish up *** */
    ret_val = tmp;
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* dnrm1_ */

doublereal dnrm2_(integer *n, doublereal *x, integer *istep)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, ii;
    static doublereal tmp;
    static integer ipara, ivect;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    parallel/vector vector norm. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** initialize *** */
    /* Parameter adjustments */
    --x;

    /* Function Body */
    tmp = 0.;
/* * */
/* *    *** find parallel loops (ipara), remainder (ivect) *** */
    ipara = *n;
    ivect = *n % 1;
/* * */
/* *    *** do parallel loops *** */
/* mdir 2 1 */
    for (ii = 1; ii <= 1; ++ii) {
/* mdir 2 2 */
	i__1 = ipara * ii;
	for (i__ = ipara * (ii - 1) + 1; i__ <= i__1; ++i__) {
	    tmp += x[i__] * x[i__];
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** do vector loops *** */
/* mdir 1 1 */
    i__1 = *n;
    for (i__ = ipara + 1; i__ <= i__1; ++i__) {
	tmp += x[i__] * x[i__];
/* L20: */
    }
/* * */
/* *    *** finish up *** */
    ret_val = sqrt(tmp);
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* dnrm2_ */

doublereal dnrm8_(integer *n, doublereal *x, integer *istep)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1, d__2, d__3;

    /* Local variables */
    static integer i__, ii;
    static doublereal tmp;
    static integer ipara, ivect;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    parallel/vector vector norm. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** initialize *** */
    /* Parameter adjustments */
    --x;

    /* Function Body */
    tmp = 0.;
/* * */
/* *    *** find parallel loops (ipara), remainder (ivect) *** */
    ipara = *n;
    ivect = *n % 1;
/* * */
/* *    *** do parallel loops *** */
/* mdir 2 1 */
    for (ii = 1; ii <= 1; ++ii) {
/* mdir 2 2 */
	i__1 = ipara * ii;
	for (i__ = ipara * (ii - 1) + 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	    d__2 = tmp, d__3 = (d__1 = x[i__], abs(d__1));
	    tmp = max(d__2,d__3);
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** do vector loops *** */
/* mdir 1 1 */
    i__1 = *n;
    for (i__ = ipara + 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__2 = tmp, d__3 = (d__1 = x[i__], abs(d__1));
	tmp = max(d__2,d__3);
/* L20: */
    }
/* * */
/* *    *** finish up *** */
    ret_val = tmp;
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* dnrm8_ */

/* Subroutine */ int dscal_(integer *n, doublereal *fac, doublereal *x, 
	integer *istep)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, ii, ipara, ivect;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    parallel/vector vector scale. */
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
    ipara = *n;
    ivect = *n % 1;
/* * */
/* *    *** do parallel loops *** */
/* mdir 2 1 */
    for (ii = 1; ii <= 1; ++ii) {
/* mdir 2 2 */
	i__1 = ipara * ii;
	for (i__ = ipara * (ii - 1) + 1; i__ <= i__1; ++i__) {
	    x[i__] = *fac * x[i__];
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** do vector loops *** */
/* mdir 1 1 */
    i__1 = *n;
    for (i__ = ipara + 1; i__ <= i__1; ++i__) {
	x[i__] = *fac * x[i__];
/* L20: */
    }
/* * */
/* *    *** return and end *** */
    return 0;
} /* dscal_ */

doublereal ddot_(integer *n, doublereal *x, integer *istep, doublereal *y, 
	integer *jstep)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Local variables */
    static integer i__, ii, ipara, ivect;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    parallel/vector dot product. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
/* *    *** initialize *** */
    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
    ret_val = 0.;
/* * */
/* *    *** find parallel loops (ipara), remainder (ivect) *** */
    ipara = *n;
    ivect = *n % 1;
/* * */
/* *    *** do parallel loops *** */
/* mdir 2 1 */
    for (ii = 1; ii <= 1; ++ii) {
/* mdir 2 2 */
	i__1 = ipara * ii;
	for (i__ = ipara * (ii - 1) + 1; i__ <= i__1; ++i__) {
	    ret_val += x[i__] * y[i__];
/* L11: */
	}
/* L10: */
    }
/* * */
/* *    *** do vector loops *** */
/* mdir 1 1 */
    i__1 = *n;
    for (i__ = ipara + 1; i__ <= i__1; ++i__) {
	ret_val += x[i__] * y[i__];
/* L20: */
    }
/* * */
/* *    *** return and end *** */
    return ret_val;
} /* ddot_ */

integer idamax_(integer *n, doublereal *sx, integer *incx)
{
    /* System generated locals */
    integer ret_val, i__1, i__2;
    doublereal d__1;

    /* Local variables */
    static integer i__, ii, ns;
    static doublereal xmag, smax;

/* * ********************************************************************* */
/* * purpose: */
/* * */
/* *    parallel/vector icamax. */
/* * */
/* * author:  michael holst */
/* * ********************************************************************* */
/* * */
/* mdir 0 0 */
/* * */
    /* Parameter adjustments */
    --sx;

    /* Function Body */
    ret_val = 0;
    if (*n <= 0) {
	return ret_val;
    }
    ret_val = 1;
    if (*n <= 1) {
	return ret_val;
    }
    if (*incx == 1) {
	goto L20;
    }
/* * */
/* *       code for increments not equal to 1. */
/* * */
    smax = abs(sx[1]);
    ns = *n * *incx;
    ii = 1;
    i__1 = ns;
    i__2 = *incx;
    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
	xmag = (d__1 = sx[i__], abs(d__1));
	if (xmag <= smax) {
	    goto L40;
	}
	ret_val = ii;
	smax = xmag;
L40:
	++ii;
/* L10: */
    }
    return ret_val;
/* * */
/* *    code for increments equal to 1. */
/* * */
L20:
    smax = abs(sx[1]);
    i__2 = *n;
    for (i__ = 2; i__ <= i__2; ++i__) {
	xmag = (d__1 = sx[i__], abs(d__1));
	if (xmag <= smax) {
	    goto L30;
	}
	ret_val = i__;
	smax = xmag;
L30:
	;
    }
    return ret_val;
} /* idamax_ */

