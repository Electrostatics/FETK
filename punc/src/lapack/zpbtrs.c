/* ./src_f77/zpbtrs.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int zpbtrs_(char *uplo, integer *n, integer *kd, integer *
	nrhs, doublecomplex *ab, integer *ldab, doublecomplex *b, integer *
	ldb, integer *info, ftnlen uplo_len)
{
    /* System generated locals */
    integer ab_dim1, ab_offset, b_dim1, b_offset, i__1;

    /* Local variables */
    static integer j;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    static logical upper;
    extern /* Subroutine */ int ztbsv_(char *, char *, char *, integer *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, integer *,
	     ftnlen, ftnlen, ftnlen), xerbla_(char *, integer *, ftnlen);


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

/*  ZPBTRS solves a system of linear equations A*X = B with a Hermitian */
/*  positive definite band matrix A using the Cholesky factorization */
/*  A = U**H*U or A = L*L**H computed by ZPBTRF. */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          = 'U':  Upper triangular factor stored in AB; */
/*          = 'L':  Lower triangular factor stored in AB. */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  KD      (input) INTEGER */
/*          The number of superdiagonals of the matrix A if UPLO = 'U', */
/*          or the number of subdiagonals if UPLO = 'L'.  KD >= 0. */

/*  NRHS    (input) INTEGER */
/*          The number of right hand sides, i.e., the number of columns */
/*          of the matrix B.  NRHS >= 0. */

/*  AB      (input) COMPLEX*16 array, dimension (LDAB,N) */
/*          The triangular factor U or L from the Cholesky factorization */
/*          A = U**H*U or A = L*L**H of the band matrix A, stored in the */
/*          first KD+1 rows of the array.  The j-th column of U or L is */
/*          stored in the j-th column of the array AB as follows: */
/*          if UPLO ='U', AB(kd+1+i-j,j) = U(i,j) for max(1,j-kd)<=i<=j; */
/*          if UPLO ='L', AB(1+i-j,j)    = L(i,j) for j<=i<=min(n,j+kd). */

/*  LDAB    (input) INTEGER */
/*          The leading dimension of the array AB.  LDAB >= KD+1. */

/*  B       (input/output) COMPLEX*16 array, dimension (LDB,NRHS) */
/*          On entry, the right hand side matrix B. */
/*          On exit, the solution matrix X. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B.  LDB >= max(1,N). */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    ab_dim1 = *ldab;
    ab_offset = 1 + ab_dim1;
    ab -= ab_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U", (ftnlen)1, (ftnlen)1);
    if (! upper && ! lsame_(uplo, "L", (ftnlen)1, (ftnlen)1)) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*kd < 0) {
	*info = -3;
    } else if (*nrhs < 0) {
	*info = -4;
    } else if (*ldab < *kd + 1) {
	*info = -6;
    } else if (*ldb < max(1,*n)) {
	*info = -8;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("ZPBTRS", &i__1, (ftnlen)6);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *nrhs == 0) {
	return 0;
    }

    if (upper) {

/*        Solve A*X = B where A = U'*U. */

	i__1 = *nrhs;
	for (j = 1; j <= i__1; ++j) {

/*           Solve U'*X = B, overwriting B with X. */

	    ztbsv_("Upper", "Conjugate transpose", "Non-unit", n, kd, &ab[
		    ab_offset], ldab, &b[j * b_dim1 + 1], &c__1, (ftnlen)5, (
		    ftnlen)19, (ftnlen)8);

/*           Solve U*X = B, overwriting B with X. */

	    ztbsv_("Upper", "No transpose", "Non-unit", n, kd, &ab[ab_offset],
		     ldab, &b[j * b_dim1 + 1], &c__1, (ftnlen)5, (ftnlen)12, (
		    ftnlen)8);
/* L10: */
	}
    } else {

/*        Solve A*X = B where A = L*L'. */

	i__1 = *nrhs;
	for (j = 1; j <= i__1; ++j) {

/*           Solve L*X = B, overwriting B with X. */

	    ztbsv_("Lower", "No transpose", "Non-unit", n, kd, &ab[ab_offset],
		     ldab, &b[j * b_dim1 + 1], &c__1, (ftnlen)5, (ftnlen)12, (
		    ftnlen)8);

/*           Solve L'*X = B, overwriting B with X. */

	    ztbsv_("Lower", "Conjugate transpose", "Non-unit", n, kd, &ab[
		    ab_offset], ldab, &b[j * b_dim1 + 1], &c__1, (ftnlen)5, (
		    ftnlen)19, (ftnlen)8);
/* L20: */
	}
    }

    return 0;

/*     End of ZPBTRS */

} /* zpbtrs_ */

