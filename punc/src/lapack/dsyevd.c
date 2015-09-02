/* ./src_f77/dsyevd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__0 = 0;
static doublereal c_b12 = 1.;
static integer c__1 = 1;

/* Subroutine */ int dsyevd_(char *jobz, char *uplo, integer *n, doublereal *
	a, integer *lda, doublereal *w, doublereal *work, integer *lwork, 
	integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, 
	ftnlen uplo_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal eps;
    static integer inde;
    static doublereal anrm, rmin, rmax;
    static integer lopt;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static doublereal sigma;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    static integer iinfo, lwmin, liopt;
    static logical lower, wantz;
    static integer indwk2, llwrk2;
    extern doublereal dlamch_(char *, ftnlen);
    static integer iscale;
    extern /* Subroutine */ int dlascl_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    integer *, integer *, ftnlen), dstedc_(char *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     integer *, integer *, integer *, integer *, ftnlen), dlacpy_(
	    char *, integer *, integer *, doublereal *, integer *, doublereal 
	    *, integer *, ftnlen);
    static doublereal safmin;
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen);
    static doublereal bignum;
    static integer indtau;
    extern /* Subroutine */ int dsterf_(integer *, doublereal *, doublereal *,
	     integer *);
    extern doublereal dlansy_(char *, char *, integer *, doublereal *, 
	    integer *, doublereal *, ftnlen, ftnlen);
    static integer indwrk, liwmin;
    extern /* Subroutine */ int dormtr_(char *, char *, char *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *, integer *, ftnlen, ftnlen, 
	    ftnlen), dsytrd_(char *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, ftnlen);
    static integer llwork;
    static doublereal smlnum;
    static logical lquery;


/*  -- LAPACK driver routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     June 30, 1999 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DSYEVD computes all eigenvalues and, optionally, eigenvectors of a */
/*  real symmetric matrix A. If eigenvectors are desired, it uses a */
/*  divide and conquer algorithm. */

/*  The divide and conquer algorithm makes very mild assumptions about */
/*  floating point arithmetic. It will work on machines with a guard */
/*  digit in add/subtract, or on those binary machines without guard */
/*  digits which subtract like the Cray X-MP, Cray Y-MP, Cray C-90, or */
/*  Cray-2. It could conceivably fail on hexadecimal or decimal machines */
/*  without guard digits, but we know of none. */

/*  Because of large use of BLAS of level 3, DSYEVD needs N**2 more */
/*  workspace than DSYEVX. */

/*  Arguments */
/*  ========= */

/*  JOBZ    (input) CHARACTER*1 */
/*          = 'N':  Compute eigenvalues only; */
/*          = 'V':  Compute eigenvalues and eigenvectors. */

/*  UPLO    (input) CHARACTER*1 */
/*          = 'U':  Upper triangle of A is stored; */
/*          = 'L':  Lower triangle of A is stored. */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA, N) */
/*          On entry, the symmetric matrix A.  If UPLO = 'U', the */
/*          leading N-by-N upper triangular part of A contains the */
/*          upper triangular part of the matrix A.  If UPLO = 'L', */
/*          the leading N-by-N lower triangular part of A contains */
/*          the lower triangular part of the matrix A. */
/*          On exit, if JOBZ = 'V', then if INFO = 0, A contains the */
/*          orthonormal eigenvectors of the matrix A. */
/*          If JOBZ = 'N', then on exit the lower triangle (if UPLO='L') */
/*          or the upper triangle (if UPLO='U') of A, including the */
/*          diagonal, is destroyed. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,N). */

/*  W       (output) DOUBLE PRECISION array, dimension (N) */
/*          If INFO = 0, the eigenvalues in ascending order. */

/*  WORK    (workspace/output) DOUBLE PRECISION array, */
/*                                         dimension (LWORK) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. */
/*          If N <= 1,               LWORK must be at least 1. */
/*          If JOBZ = 'N' and N > 1, LWORK must be at least 2*N+1. */
/*          If JOBZ = 'V' and N > 1, LWORK must be at least */
/*                                                1 + 6*N + 2*N**2. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  IWORK   (workspace/output) INTEGER array, dimension (LIWORK) */
/*          On exit, if INFO = 0, IWORK(1) returns the optimal LIWORK. */

/*  LIWORK  (input) INTEGER */
/*          The dimension of the array IWORK. */
/*          If N <= 1,                LIWORK must be at least 1. */
/*          If JOBZ  = 'N' and N > 1, LIWORK must be at least 1. */
/*          If JOBZ  = 'V' and N > 1, LIWORK must be at least 3 + 5*N. */

/*          If LIWORK = -1, then a workspace query is assumed; the */
/*          routine only calculates the optimal size of the IWORK array, */
/*          returns this value as the first entry of the IWORK array, and */
/*          no error message related to LIWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */
/*          > 0:  if INFO = i, the algorithm failed to converge; i */
/*                off-diagonal elements of an intermediate tridiagonal */
/*                form did not converge to zero. */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*     Jeff Rutter, Computer Science Division, University of California */
/*     at Berkeley, USA */
/*  Modified by Francoise Tisseur, University of Tennessee. */

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
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --w;
    --work;
    --iwork;

    /* Function Body */
    wantz = lsame_(jobz, "V", (ftnlen)1, (ftnlen)1);
    lower = lsame_(uplo, "L", (ftnlen)1, (ftnlen)1);
    lquery = *lwork == -1 || *liwork == -1;

    *info = 0;
    if (*n <= 1) {
	liwmin = 1;
	lwmin = 1;
	lopt = lwmin;
	liopt = liwmin;
    } else {
	if (wantz) {
	    liwmin = *n * 5 + 3;
/* Computing 2nd power */
	    i__1 = *n;
	    lwmin = *n * 6 + 1 + (i__1 * i__1 << 1);
	} else {
	    liwmin = 1;
	    lwmin = (*n << 1) + 1;
	}
	lopt = lwmin;
	liopt = liwmin;
    }
    if (! (wantz || lsame_(jobz, "N", (ftnlen)1, (ftnlen)1))) {
	*info = -1;
    } else if (! (lower || lsame_(uplo, "U", (ftnlen)1, (ftnlen)1))) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*lda < max(1,*n)) {
	*info = -5;
    } else if (*lwork < lwmin && ! lquery) {
	*info = -8;
    } else if (*liwork < liwmin && ! lquery) {
	*info = -10;
    }

    if (*info == 0) {
	work[1] = (doublereal) lopt;
	iwork[1] = liopt;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DSYEVD", &i__1, (ftnlen)6);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

    if (*n == 1) {
	w[1] = a[a_dim1 + 1];
	if (wantz) {
	    a[a_dim1 + 1] = 1.;
	}
	return 0;
    }

/*     Get machine constants. */

    safmin = dlamch_("Safe minimum", (ftnlen)12);
    eps = dlamch_("Precision", (ftnlen)9);
    smlnum = safmin / eps;
    bignum = 1. / smlnum;
    rmin = sqrt(smlnum);
    rmax = sqrt(bignum);

/*     Scale matrix to allowable range, if necessary. */

    anrm = dlansy_("M", uplo, n, &a[a_offset], lda, &work[1], (ftnlen)1, (
	    ftnlen)1);
    iscale = 0;
    if (anrm > 0. && anrm < rmin) {
	iscale = 1;
	sigma = rmin / anrm;
    } else if (anrm > rmax) {
	iscale = 1;
	sigma = rmax / anrm;
    }
    if (iscale == 1) {
	dlascl_(uplo, &c__0, &c__0, &c_b12, &sigma, n, n, &a[a_offset], lda, 
		info, (ftnlen)1);
    }

/*     Call DSYTRD to reduce symmetric matrix to tridiagonal form. */

    inde = 1;
    indtau = inde + *n;
    indwrk = indtau + *n;
    llwork = *lwork - indwrk + 1;
    indwk2 = indwrk + *n * *n;
    llwrk2 = *lwork - indwk2 + 1;

    dsytrd_(uplo, n, &a[a_offset], lda, &w[1], &work[inde], &work[indtau], &
	    work[indwrk], &llwork, &iinfo, (ftnlen)1);
    lopt = (integer) ((*n << 1) + work[indwrk]);

/*     For eigenvalues only, call DSTERF.  For eigenvectors, first call */
/*     DSTEDC to generate the eigenvector matrix, WORK(INDWRK), of the */
/*     tridiagonal matrix, then call DORMTR to multiply it by the */
/*     Householder transformations stored in A. */

    if (! wantz) {
	dsterf_(n, &w[1], &work[inde], info);
    } else {
	dstedc_("I", n, &w[1], &work[inde], &work[indwrk], n, &work[indwk2], &
		llwrk2, &iwork[1], liwork, info, (ftnlen)1);
	dormtr_("L", uplo, "N", n, n, &a[a_offset], lda, &work[indtau], &work[
		indwrk], n, &work[indwk2], &llwrk2, &iinfo, (ftnlen)1, (
		ftnlen)1, (ftnlen)1);
	dlacpy_("A", n, n, &work[indwrk], n, &a[a_offset], lda, (ftnlen)1);
/* Computing MAX */
/* Computing 2nd power */
	i__3 = *n;
	i__1 = lopt, i__2 = *n * 6 + 1 + (i__3 * i__3 << 1);
	lopt = max(i__1,i__2);
    }

/*     If matrix was scaled, then rescale eigenvalues appropriately. */

    if (iscale == 1) {
	d__1 = 1. / sigma;
	dscal_(n, &d__1, &w[1], &c__1);
    }

    work[1] = (doublereal) lopt;
    iwork[1] = liopt;

    return 0;

/*     End of DSYEVD */

} /* dsyevd_ */

