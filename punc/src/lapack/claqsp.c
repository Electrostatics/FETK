/* ./src_f77/claqsp.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Subroutine */ int claqsp_(char *uplo, integer *n, realcomplex *ap, real *s, 
	real *scond, real *amax, char *equed, ftnlen uplo_len, ftnlen 
	equed_len)
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    real r__1;
    realcomplex q__1;

    /* Local variables */
    static integer i__, j, jc;
    static real cj, large;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    static real small;
    extern doublereal slamch_(char *, ftnlen);


/*  -- LAPACK auxiliary routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     February 29, 1992 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  CLAQSP equilibrates a symmetric matrix A using the scaling factors */
/*  in the vector S. */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          Specifies whether the upper or lower triangular part of the */
/*          symmetric matrix A is stored. */
/*          = 'U':  Upper triangular */
/*          = 'L':  Lower triangular */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  AP      (input/output) COMPLEX array, dimension (N*(N+1)/2) */
/*          On entry, the upper or lower triangle of the symmetric matrix */
/*          A, packed columnwise in a linear array.  The j-th column of A */
/*          is stored in the array AP as follows: */
/*          if UPLO = 'U', AP(i + (j-1)*j/2) = A(i,j) for 1<=i<=j; */
/*          if UPLO = 'L', AP(i + (j-1)*(2n-j)/2) = A(i,j) for j<=i<=n. */

/*          On exit, the equilibrated matrix:  diag(S) * A * diag(S), in */
/*          the same storage format as A. */

/*  S       (input) REAL array, dimension (N) */
/*          The scale factors for A. */

/*  SCOND   (input) REAL */
/*          Ratio of the smallest S(i) to the largest S(i). */

/*  AMAX    (input) REAL */
/*          Absolute value of largest matrix entry. */

/*  EQUED   (output) CHARACTER*1 */
/*          Specifies whether or not equilibration was done. */
/*          = 'N':  No equilibration. */
/*          = 'Y':  Equilibration was done, i.e., A has been replaced by */
/*                  diag(S) * A * diag(S). */

/*  Internal Parameters */
/*  =================== */

/*  THRESH is a threshold value used to decide if scaling should be done */
/*  based on the ratio of the scaling factors.  If SCOND < THRESH, */
/*  scaling is done. */

/*  LARGE and SMALL are threshold values used to decide if scaling should */
/*  be done based on the absolute size of the largest matrix element. */
/*  If AMAX > LARGE or AMAX < SMALL, scaling is done. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Quick return if possible */

    /* Parameter adjustments */
    --s;
    --ap;

    /* Function Body */
    if (*n <= 0) {
	*(unsigned char *)equed = 'N';
	return 0;
    }

/*     Initialize LARGE and SMALL. */

    small = slamch_("Safe minimum", (ftnlen)12) / slamch_("Precision", (
	    ftnlen)9);
    large = 1.f / small;

    if (*scond >= .1f && *amax >= small && *amax <= large) {

/*        No equilibration */

	*(unsigned char *)equed = 'N';
    } else {

/*        Replace A by diag(S) * A * diag(S). */

	if (lsame_(uplo, "U", (ftnlen)1, (ftnlen)1)) {

/*           Upper triangle of A is stored. */

	    jc = 1;
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		cj = s[j];
		i__2 = j;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    i__3 = jc + i__ - 1;
		    r__1 = cj * s[i__];
		    i__4 = jc + i__ - 1;
		    q__1.r = r__1 * ap[i__4].r, q__1.i = r__1 * ap[i__4].i;
		    ap[i__3].r = q__1.r, ap[i__3].i = q__1.i;
/* L10: */
		}
		jc += j;
/* L20: */
	    }
	} else {

/*           Lower triangle of A is stored. */

	    jc = 1;
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		cj = s[j];
		i__2 = *n;
		for (i__ = j; i__ <= i__2; ++i__) {
		    i__3 = jc + i__ - j;
		    r__1 = cj * s[i__];
		    i__4 = jc + i__ - j;
		    q__1.r = r__1 * ap[i__4].r, q__1.i = r__1 * ap[i__4].i;
		    ap[i__3].r = q__1.r, ap[i__3].i = q__1.i;
/* L30: */
		}
		jc = jc + *n - j + 1;
/* L40: */
	    }
	}
	*(unsigned char *)equed = 'Y';
    }

    return 0;

/*     End of CLAQSP */

} /* claqsp_ */

