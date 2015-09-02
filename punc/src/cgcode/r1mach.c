/* ./src_f77/r1mach.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

doublereal r1mach_(integer *idum)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static real u, comp;

/* ----------------------------------------------------------------------- */
/* this routine computes the unit roundoff of the machine in double */
/* precision.  this is defined as the smallest positive machine number */
/* u such that  1.0e0 + u .ne. 1.0e0 (in single precision). */
/* ----------------------------------------------------------------------- */
    u = 1.f;
L10:
    u *= .5f;
    comp = u + 1.f;
    if (comp != 1.f) {
	goto L10;
    }
    ret_val = u * 2.f;
    return ret_val;
/* ----------------------- end of function R1MACH ------------------------ */
} /* r1mach_ */

