/* ./src_f77/csrscl.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Subroutine */ int csrscl_(integer *n, real *sa, realcomplex *sx, integer *incx)
{
    static real mul, cden;
    static logical done;
    static real cnum, cden1, cnum1;
    extern /* Subroutine */ int slabad_(real *, real *);
    extern doublereal slamch_(char *, ftnlen);
    extern /* Subroutine */ int csscal_(integer *, real *, realcomplex *, integer 
	    *);
    static real bignum, smlnum;


/*  -- LAPACK auxiliary routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     September 30, 1994 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  CSRSCL multiplies an n-element complex vector x by the real scalar */
/*  1/a.  This is done without overflow or underflow as long as */
/*  the final result x/a does not overflow or underflow. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The number of components of the vector x. */

/*  SA      (input) REAL */
/*          The scalar a which is used to divide each component of x. */
/*          SA must be >= 0, or the subroutine will divide by zero. */

/*  SX      (input/output) COMPLEX array, dimension */
/*                         (1+(N-1)*abs(INCX)) */
/*          The n-element vector x. */

/*  INCX    (input) INTEGER */
/*          The increment between successive values of the vector SX. */
/*          > 0:  SX(1) = X(1) and SX(1+(i-1)*INCX) = x(i),     1< i<= n */

/* ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Quick return if possible */

    /* Parameter adjustments */
    --sx;

    /* Function Body */
    if (*n <= 0) {
	return 0;
    }

/*     Get machine parameters */

    smlnum = slamch_("S", (ftnlen)1);
    bignum = 1.f / smlnum;
    slabad_(&smlnum, &bignum);

/*     Initialize the denominator to SA and the numerator to 1. */

    cden = *sa;
    cnum = 1.f;

L10:
    cden1 = cden * smlnum;
    cnum1 = cnum / bignum;
    if (dabs(cden1) > dabs(cnum) && cnum != 0.f) {

/*        Pre-multiply X by SMLNUM if CDEN is large compared to CNUM. */

	mul = smlnum;
	done = FALSE_;
	cden = cden1;
    } else if (dabs(cnum1) > dabs(cden)) {

/*        Pre-multiply X by BIGNUM if CDEN is small compared to CNUM. */

	mul = bignum;
	done = FALSE_;
	cnum = cnum1;
    } else {

/*        Multiply X by CNUM / CDEN and return. */

	mul = cnum / cden;
	done = TRUE_;
    }

/*     Scale the vector X by MUL */

    csscal_(n, &mul, &sx[1], incx);

    if (! done) {
	goto L10;
    }

    return 0;

/*     End of CSRSCL */

} /* csrscl_ */

