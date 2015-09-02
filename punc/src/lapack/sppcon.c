/* ./src_f77/sppcon.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int sppcon_(char *uplo, integer *n, real *ap, real *anorm, 
	real *rcond, real *work, integer *iwork, integer *info, ftnlen 
	uplo_len)
{
    /* System generated locals */
    integer i__1;
    real r__1;

    /* Local variables */
    static integer ix, kase;
    static real scale;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    extern /* Subroutine */ int srscl_(integer *, real *, real *, integer *);
    static logical upper;
    static real scalel;
    extern doublereal slamch_(char *, ftnlen);
    static real scaleu;
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen), slacon_(
	    integer *, real *, real *, integer *, real *, integer *);
    extern integer isamax_(integer *, real *, integer *);
    static real ainvnm;
    static char normin[1];
    extern /* Subroutine */ int slatps_(char *, char *, char *, char *, 
	    integer *, real *, real *, real *, real *, integer *, ftnlen, 
	    ftnlen, ftnlen, ftnlen);
    static real smlnum;


/*  -- LAPACK routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     March 31, 1993 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  SPPCON estimates the reciprocal of the condition number (in the */
/*  1-norm) of a real symmetric positive definite packed matrix using */
/*  the Cholesky factorization A = U**T*U or A = L*L**T computed by */
/*  SPPTRF. */

/*  An estimate is obtained for norm(inv(A)), and the reciprocal of the */
/*  condition number is computed as RCOND = 1 / (ANORM * norm(inv(A))). */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          = 'U':  Upper triangle of A is stored; */
/*          = 'L':  Lower triangle of A is stored. */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  AP      (input) REAL array, dimension (N*(N+1)/2) */
/*          The triangular factor U or L from the Cholesky factorization */
/*          A = U**T*U or A = L*L**T, packed columnwise in a linear */
/*          array.  The j-th column of U or L is stored in the array AP */
/*          as follows: */
/*          if UPLO = 'U', AP(i + (j-1)*j/2) = U(i,j) for 1<=i<=j; */
/*          if UPLO = 'L', AP(i + (j-1)*(2n-j)/2) = L(i,j) for j<=i<=n. */

/*  ANORM   (input) REAL */
/*          The 1-norm (or infinity-norm) of the symmetric matrix A. */

/*  RCOND   (output) REAL */
/*          The reciprocal of the condition number of the matrix A, */
/*          computed as RCOND = 1/(ANORM * AINVNM), where AINVNM is an */
/*          estimate of the 1-norm of inv(A) computed in this routine. */

/*  WORK    (workspace) REAL array, dimension (3*N) */

/*  IWORK   (workspace) INTEGER array, dimension (N) */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

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

/*     Test the input parameters. */

    /* Parameter adjustments */
    --iwork;
    --work;
    --ap;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U", (ftnlen)1, (ftnlen)1);
    if (! upper && ! lsame_(uplo, "L", (ftnlen)1, (ftnlen)1)) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*anorm < 0.f) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("SPPCON", &i__1, (ftnlen)6);
	return 0;
    }

/*     Quick return if possible */

    *rcond = 0.f;
    if (*n == 0) {
	*rcond = 1.f;
	return 0;
    } else if (*anorm == 0.f) {
	return 0;
    }

    smlnum = slamch_("Safe minimum", (ftnlen)12);

/*     Estimate the 1-norm of the inverse. */

    kase = 0;
    *(unsigned char *)normin = 'N';
L10:
    slacon_(n, &work[*n + 1], &work[1], &iwork[1], &ainvnm, &kase);
    if (kase != 0) {
	if (upper) {

/*           Multiply by inv(U'). */

	    slatps_("Upper", "Transpose", "Non-unit", normin, n, &ap[1], &
		    work[1], &scalel, &work[(*n << 1) + 1], info, (ftnlen)5, (
		    ftnlen)9, (ftnlen)8, (ftnlen)1);
	    *(unsigned char *)normin = 'Y';

/*           Multiply by inv(U). */

	    slatps_("Upper", "No transpose", "Non-unit", normin, n, &ap[1], &
		    work[1], &scaleu, &work[(*n << 1) + 1], info, (ftnlen)5, (
		    ftnlen)12, (ftnlen)8, (ftnlen)1);
	} else {

/*           Multiply by inv(L). */

	    slatps_("Lower", "No transpose", "Non-unit", normin, n, &ap[1], &
		    work[1], &scalel, &work[(*n << 1) + 1], info, (ftnlen)5, (
		    ftnlen)12, (ftnlen)8, (ftnlen)1);
	    *(unsigned char *)normin = 'Y';

/*           Multiply by inv(L'). */

	    slatps_("Lower", "Transpose", "Non-unit", normin, n, &ap[1], &
		    work[1], &scaleu, &work[(*n << 1) + 1], info, (ftnlen)5, (
		    ftnlen)9, (ftnlen)8, (ftnlen)1);
	}

/*        Multiply by 1/SCALE if doing so will not cause overflow. */

	scale = scalel * scaleu;
	if (scale != 1.f) {
	    ix = isamax_(n, &work[1], &c__1);
	    if (scale < (r__1 = work[ix], dabs(r__1)) * smlnum || scale == 
		    0.f) {
		goto L20;
	    }
	    srscl_(n, &scale, &work[1], &c__1);
	}
	goto L10;
    }

/*     Compute the estimate of the reciprocal condition number. */

    if (ainvnm != 0.f) {
	*rcond = 1.f / ainvnm / *anorm;
    }

L20:
    return 0;

/*     End of SPPCON */

} /* sppcon_ */

