/* ./src_f77/second.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

doublereal second_(void)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static real t1;
    extern doublereal etime_(real *);
    static real tarray[2];


/*  -- LAPACK auxiliary routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     September 30, 1994 */

/*  Purpose */
/*  ======= */

/*  SECOND returns the user time for a process in seconds. */
/*  This version gets the time from the system function ETIME. */

/* ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    t1 = etime_(tarray);
    ret_val = tarray[0];
    return ret_val;

/*     End of SECOND */

} /* second_ */

