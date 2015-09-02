/* ./util_f77/second.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Subroutine */ int second_(real *t)
{
    static real t1;
    extern doublereal etime_(real *);
    static real tarray[2];



/*  -- LAPACK auxiliary routine (preliminary version) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     July 26, 1991 */

/*  Purpose */
/*  ======= */

/*  SECOND returns the user time for a process in seconds. */
/*  This version gets the time from the system function ETIME. */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    t1 = etime_(tarray);
    *t = tarray[0];
    return 0;

/*     End of SECOND */

} /* second_ */

