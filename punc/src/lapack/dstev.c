/* ./src_f77/dstev.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int dstev_(char *jobz, integer *n, doublereal *d__, 
	doublereal *e, doublereal *z__, integer *ldz, doublereal *work, 
	integer *info, ftnlen jobz_len)
{
    /* System generated locals */
    integer z_dim1, z_offset, i__1;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal eps;
    static integer imax;
    static doublereal rmin, rmax, tnrm;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static doublereal sigma;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    static logical wantz;
    extern doublereal dlamch_(char *, ftnlen);
    static integer iscale;
    static doublereal safmin;
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen);
    static doublereal bignum;
    extern doublereal dlanst_(char *, integer *, doublereal *, doublereal *, 
	    ftnlen);
    extern /* Subroutine */ int dsterf_(integer *, doublereal *, doublereal *,
	     integer *), dsteqr_(char *, integer *, doublereal *, doublereal *
	    , doublereal *, integer *, doublereal *, integer *, ftnlen);
    static doublereal smlnum;


/*  -- LAPACK driver routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     September 30, 1994 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DSTEV computes all eigenvalues and, optionally, eigenvectors of a */
/*  real symmetric tridiagonal matrix A. */

/*  Arguments */
/*  ========= */

/*  JOBZ    (input) CHARACTER*1 */
/*          = 'N':  Compute eigenvalues only; */
/*          = 'V':  Compute eigenvalues and eigenvectors. */

/*  N       (input) INTEGER */
/*          The order of the matrix.  N >= 0. */

/*  D       (input/output) DOUBLE PRECISION array, dimension (N) */
/*          On entry, the n diagonal elements of the tridiagonal matrix */
/*          A. */
/*          On exit, if INFO = 0, the eigenvalues in ascending order. */

/*  E       (input/output) DOUBLE PRECISION array, dimension (N) */
/*          On entry, the (n-1) subdiagonal elements of the tridiagonal */
/*          matrix A, stored in elements 1 to N-1 of E; E(N) need not */
/*          be set, but is used by the routine. */
/*          On exit, the contents of E are destroyed. */

/*  Z       (output) DOUBLE PRECISION array, dimension (LDZ, N) */
/*          If JOBZ = 'V', then if INFO = 0, Z contains the orthonormal */
/*          eigenvectors of the matrix A, with the i-th column of Z */
/*          holding the eigenvector associated with D(i). */
/*          If JOBZ = 'N', then Z is not referenced. */

/*  LDZ     (input) INTEGER */
/*          The leading dimension of the array Z.  LDZ >= 1, and if */
/*          JOBZ = 'V', LDZ >= max(1,N). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (max(1,2*N-2)) */
/*          If JOBZ = 'N', WORK is not referenced. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */
/*          > 0:  if INFO = i, the algorithm failed to converge; i */
/*                off-diagonal elements of E did not converge to zero. */

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
    --d__;
    --e;
    z_dim1 = *ldz;
    z_offset = 1 + z_dim1;
    z__ -= z_offset;
    --work;

    /* Function Body */
    wantz = lsame_(jobz, "V", (ftnlen)1, (ftnlen)1);

    *info = 0;
    if (! (wantz || lsame_(jobz, "N", (ftnlen)1, (ftnlen)1))) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*ldz < 1 || wantz && *ldz < *n) {
	*info = -6;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DSTEV ", &i__1, (ftnlen)6);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

    if (*n == 1) {
	if (wantz) {
	    z__[z_dim1 + 1] = 1.;
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

    iscale = 0;
    tnrm = dlanst_("M", n, &d__[1], &e[1], (ftnlen)1);
    if (tnrm > 0. && tnrm < rmin) {
	iscale = 1;
	sigma = rmin / tnrm;
    } else if (tnrm > rmax) {
	iscale = 1;
	sigma = rmax / tnrm;
    }
    if (iscale == 1) {
	dscal_(n, &sigma, &d__[1], &c__1);
	i__1 = *n - 1;
	dscal_(&i__1, &sigma, &e[1], &c__1);
    }

/*     For eigenvalues only, call DSTERF.  For eigenvalues and */
/*     eigenvectors, call DSTEQR. */

    if (! wantz) {
	dsterf_(n, &d__[1], &e[1], info);
    } else {
	dsteqr_("I", n, &d__[1], &e[1], &z__[z_offset], ldz, &work[1], info, (
		ftnlen)1);
    }

/*     If matrix was scaled, then rescale eigenvalues appropriately. */

    if (iscale == 1) {
	if (*info == 0) {
	    imax = *n;
	} else {
	    imax = *info - 1;
	}
	d__1 = 1. / sigma;
	dscal_(&imax, &d__1, &d__[1], &c__1);
    }

    return 0;

/*     End of DSTEV */

} /* dstev_ */

