/* ./src_f77/stptri.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int stptri_(char *uplo, char *diag, integer *n, real *ap, 
	integer *info, ftnlen uplo_len, ftnlen diag_len)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer j, jc, jj;
    static real ajj;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    extern /* Subroutine */ int sscal_(integer *, real *, real *, integer *);
    static logical upper;
    extern /* Subroutine */ int stpmv_(char *, char *, char *, integer *, 
	    real *, real *, integer *, ftnlen, ftnlen, ftnlen), xerbla_(char *
	    , integer *, ftnlen);
    static integer jclast;
    static logical nounit;


/*  -- LAPACK routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     September 30, 1994 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  STPTRI computes the inverse of a real upper or lower triangular */
/*  matrix A stored in packed format. */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          = 'U':  A is upper triangular; */
/*          = 'L':  A is lower triangular. */

/*  DIAG    (input) CHARACTER*1 */
/*          = 'N':  A is non-unit triangular; */
/*          = 'U':  A is unit triangular. */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  AP      (input/output) REAL array, dimension (N*(N+1)/2) */
/*          On entry, the upper or lower triangular matrix A, stored */
/*          columnwise in a linear array.  The j-th column of A is stored */
/*          in the array AP as follows: */
/*          if UPLO = 'U', AP(i + (j-1)*j/2) = A(i,j) for 1<=i<=j; */
/*          if UPLO = 'L', AP(i + (j-1)*((2*n-j)/2) = A(i,j) for j<=i<=n. */
/*          See below for further details. */
/*          On exit, the (triangular) inverse of the original matrix, in */
/*          the same packed storage format. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */
/*          > 0:  if INFO = i, A(i,i) is exactly zero.  The triangular */
/*                matrix is singular and its inverse can not be computed. */

/*  Further Details */
/*  =============== */

/*  A triangular matrix A can be transferred to packed storage using one */
/*  of the following program segments: */

/*  UPLO = 'U':                      UPLO = 'L': */

/*        JC = 1                           JC = 1 */
/*        DO 2 J = 1, N                    DO 2 J = 1, N */
/*           DO 1 I = 1, J                    DO 1 I = J, N */
/*              AP(JC+I-1) = A(I,J)              AP(JC+I-J) = A(I,J) */
/*      1    CONTINUE                    1    CONTINUE */
/*           JC = JC + J                      JC = JC + N - J + 1 */
/*      2 CONTINUE                       2 CONTINUE */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    --ap;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U", (ftnlen)1, (ftnlen)1);
    nounit = lsame_(diag, "N", (ftnlen)1, (ftnlen)1);
    if (! upper && ! lsame_(uplo, "L", (ftnlen)1, (ftnlen)1)) {
	*info = -1;
    } else if (! nounit && ! lsame_(diag, "U", (ftnlen)1, (ftnlen)1)) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("STPTRI", &i__1, (ftnlen)6);
	return 0;
    }

/*     Check for singularity if non-unit. */

    if (nounit) {
	if (upper) {
	    jj = 0;
	    i__1 = *n;
	    for (*info = 1; *info <= i__1; ++(*info)) {
		jj += *info;
		if (ap[jj] == 0.f) {
		    return 0;
		}
/* L10: */
	    }
	} else {
	    jj = 1;
	    i__1 = *n;
	    for (*info = 1; *info <= i__1; ++(*info)) {
		if (ap[jj] == 0.f) {
		    return 0;
		}
		jj = jj + *n - *info + 1;
/* L20: */
	    }
	}
	*info = 0;
    }

    if (upper) {

/*        Compute inverse of upper triangular matrix. */

	jc = 1;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (nounit) {
		ap[jc + j - 1] = 1.f / ap[jc + j - 1];
		ajj = -ap[jc + j - 1];
	    } else {
		ajj = -1.f;
	    }

/*           Compute elements 1:j-1 of j-th column. */

	    i__2 = j - 1;
	    stpmv_("Upper", "No transpose", diag, &i__2, &ap[1], &ap[jc], &
		    c__1, (ftnlen)5, (ftnlen)12, (ftnlen)1);
	    i__2 = j - 1;
	    sscal_(&i__2, &ajj, &ap[jc], &c__1);
	    jc += j;
/* L30: */
	}

    } else {

/*        Compute inverse of lower triangular matrix. */

	jc = *n * (*n + 1) / 2;
	for (j = *n; j >= 1; --j) {
	    if (nounit) {
		ap[jc] = 1.f / ap[jc];
		ajj = -ap[jc];
	    } else {
		ajj = -1.f;
	    }
	    if (j < *n) {

/*              Compute elements j+1:n of j-th column. */

		i__1 = *n - j;
		stpmv_("Lower", "No transpose", diag, &i__1, &ap[jclast], &ap[
			jc + 1], &c__1, (ftnlen)5, (ftnlen)12, (ftnlen)1);
		i__1 = *n - j;
		sscal_(&i__1, &ajj, &ap[jc + 1], &c__1);
	    }
	    jclast = jc;
	    jc = jc - *n + j - 2;
/* L40: */
	}
    }

    return 0;

/*     End of STPTRI */

} /* stptri_ */

