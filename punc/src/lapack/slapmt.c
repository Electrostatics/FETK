/* ./src_f77/slapmt.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Subroutine */ int slapmt_(logical *forwrd, integer *m, integer *n, real *x,
	 integer *ldx, integer *k)
{
    /* System generated locals */
    integer x_dim1, x_offset, i__1, i__2;

    /* Local variables */
    static integer i__, j, ii, in;
    static real temp;


/*  -- LAPACK auxiliary routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     March 31, 1993 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  SLAPMT rearranges the columns of the M by N matrix X as specified */
/*  by the permutation K(1),K(2),...,K(N) of the integers 1,...,N. */
/*  If FORWRD = .TRUE.,  forward permutation: */

/*       X(*,K(J)) is moved X(*,J) for J = 1,2,...,N. */

/*  If FORWRD = .FALSE., backward permutation: */

/*       X(*,J) is moved to X(*,K(J)) for J = 1,2,...,N. */

/*  Arguments */
/*  ========= */

/*  FORWRD  (input) LOGICAL */
/*          = .TRUE., forward permutation */
/*          = .FALSE., backward permutation */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix X. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix X. N >= 0. */

/*  X       (input/output) REAL array, dimension (LDX,N) */
/*          On entry, the M by N matrix X. */
/*          On exit, X contains the permuted matrix X. */

/*  LDX     (input) INTEGER */
/*          The leading dimension of the array X, LDX >= MAX(1,M). */

/*  K       (input) INTEGER array, dimension (N) */
/*          On entry, K contains the permutation vector. */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    x_dim1 = *ldx;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --k;

    /* Function Body */
    if (*n <= 1) {
	return 0;
    }

    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	k[i__] = -k[i__];
/* L10: */
    }

    if (*forwrd) {

/*        Forward permutation */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {

	    if (k[i__] > 0) {
		goto L40;
	    }

	    j = i__;
	    k[j] = -k[j];
	    in = k[j];

L20:
	    if (k[in] > 0) {
		goto L40;
	    }

	    i__2 = *m;
	    for (ii = 1; ii <= i__2; ++ii) {
		temp = x[ii + j * x_dim1];
		x[ii + j * x_dim1] = x[ii + in * x_dim1];
		x[ii + in * x_dim1] = temp;
/* L30: */
	    }

	    k[in] = -k[in];
	    j = in;
	    in = k[in];
	    goto L20;

L40:

/* L60: */
	    ;
	}

    } else {

/*        Backward permutation */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {

	    if (k[i__] > 0) {
		goto L100;
	    }

	    k[i__] = -k[i__];
	    j = k[i__];
L80:
	    if (j == i__) {
		goto L100;
	    }

	    i__2 = *m;
	    for (ii = 1; ii <= i__2; ++ii) {
		temp = x[ii + i__ * x_dim1];
		x[ii + i__ * x_dim1] = x[ii + j * x_dim1];
		x[ii + j * x_dim1] = temp;
/* L90: */
	    }

	    k[j] = -k[j];
	    j = k[j];
	    goto L80;

L100:
/* L110: */
	    ;
	}

    }

    return 0;

/*     End of SLAPMT */

} /* slapmt_ */

