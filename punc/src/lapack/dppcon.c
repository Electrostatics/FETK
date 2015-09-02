/* ./src_f77/dppcon.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int dppcon_(char *uplo, integer *n, doublereal *ap, 
	doublereal *anorm, doublereal *rcond, doublereal *work, integer *
	iwork, integer *info, ftnlen uplo_len)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    static integer ix, kase;
    static doublereal scale;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    extern /* Subroutine */ int drscl_(integer *, doublereal *, doublereal *, 
	    integer *);
    static logical upper;
    extern doublereal dlamch_(char *, ftnlen);
    extern /* Subroutine */ int dlacon_(integer *, doublereal *, doublereal *,
	     integer *, doublereal *, integer *);
    static doublereal scalel;
    extern integer idamax_(integer *, doublereal *, integer *);
    static doublereal scaleu;
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen), dlatps_(
	    char *, char *, char *, char *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, ftnlen, 
	    ftnlen, ftnlen, ftnlen);
    static doublereal ainvnm;
    static char normin[1];
    static doublereal smlnum;


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

/*  DPPCON estimates the reciprocal of the condition number (in the */
/*  1-norm) of a real symmetric positive definite packed matrix using */
/*  the Cholesky factorization A = U**T*U or A = L*L**T computed by */
/*  DPPTRF. */

/*  An estimate is obtained for norm(inv(A)), and the reciprocal of the */
/*  condition number is computed as RCOND = 1 / (ANORM * norm(inv(A))). */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          = 'U':  Upper triangle of A is stored; */
/*          = 'L':  Lower triangle of A is stored. */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  AP      (input) DOUBLE PRECISION array, dimension (N*(N+1)/2) */
/*          The triangular factor U or L from the Cholesky factorization */
/*          A = U**T*U or A = L*L**T, packed columnwise in a linear */
/*          array.  The j-th column of U or L is stored in the array AP */
/*          as follows: */
/*          if UPLO = 'U', AP(i + (j-1)*j/2) = U(i,j) for 1<=i<=j; */
/*          if UPLO = 'L', AP(i + (j-1)*(2n-j)/2) = L(i,j) for j<=i<=n. */

/*  ANORM   (input) DOUBLE PRECISION */
/*          The 1-norm (or infinity-norm) of the symmetric matrix A. */

/*  RCOND   (output) DOUBLE PRECISION */
/*          The reciprocal of the condition number of the matrix A, */
/*          computed as RCOND = 1/(ANORM * AINVNM), where AINVNM is an */
/*          estimate of the 1-norm of inv(A) computed in this routine. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (3*N) */

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
    } else if (*anorm < 0.) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DPPCON", &i__1, (ftnlen)6);
	return 0;
    }

/*     Quick return if possible */

    *rcond = 0.;
    if (*n == 0) {
	*rcond = 1.;
	return 0;
    } else if (*anorm == 0.) {
	return 0;
    }

    smlnum = dlamch_("Safe minimum", (ftnlen)12);

/*     Estimate the 1-norm of the inverse. */

    kase = 0;
    *(unsigned char *)normin = 'N';
L10:
    dlacon_(n, &work[*n + 1], &work[1], &iwork[1], &ainvnm, &kase);
    if (kase != 0) {
	if (upper) {

/*           Multiply by inv(U'). */

	    dlatps_("Upper", "Transpose", "Non-unit", normin, n, &ap[1], &
		    work[1], &scalel, &work[(*n << 1) + 1], info, (ftnlen)5, (
		    ftnlen)9, (ftnlen)8, (ftnlen)1);
	    *(unsigned char *)normin = 'Y';

/*           Multiply by inv(U). */

	    dlatps_("Upper", "No transpose", "Non-unit", normin, n, &ap[1], &
		    work[1], &scaleu, &work[(*n << 1) + 1], info, (ftnlen)5, (
		    ftnlen)12, (ftnlen)8, (ftnlen)1);
	} else {

/*           Multiply by inv(L). */

	    dlatps_("Lower", "No transpose", "Non-unit", normin, n, &ap[1], &
		    work[1], &scalel, &work[(*n << 1) + 1], info, (ftnlen)5, (
		    ftnlen)12, (ftnlen)8, (ftnlen)1);
	    *(unsigned char *)normin = 'Y';

/*           Multiply by inv(L'). */

	    dlatps_("Lower", "Transpose", "Non-unit", normin, n, &ap[1], &
		    work[1], &scaleu, &work[(*n << 1) + 1], info, (ftnlen)5, (
		    ftnlen)9, (ftnlen)8, (ftnlen)1);
	}

/*        Multiply by 1/SCALE if doing so will not cause overflow. */

	scale = scalel * scaleu;
	if (scale != 1.) {
	    ix = idamax_(n, &work[1], &c__1);
	    if (scale < (d__1 = work[ix], abs(d__1)) * smlnum || scale == 0.) 
		    {
		goto L20;
	    }
	    drscl_(n, &scale, &work[1], &c__1);
	}
	goto L10;
    }

/*     Compute the estimate of the reciprocal condition number. */

    if (ainvnm != 0.) {
	*rcond = 1. / ainvnm / *anorm;
    }

L20:
    return 0;

/*     End of DPPCON */

} /* dppcon_ */

