/* ./src_f77/chetrs.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static realcomplex c_b1 = {1.f,0.f};
static integer c__1 = 1;

/* Subroutine */ int chetrs_(char *uplo, integer *n, integer *nrhs, realcomplex *
	a, integer *lda, integer *ipiv, realcomplex *b, integer *ldb, integer *
	info, ftnlen uplo_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2;
    realcomplex q__1, q__2, q__3;

    /* Builtin functions */
    void c_div(realcomplex *, realcomplex *, realcomplex *), r_cnjg(realcomplex *, realcomplex *);

    /* Local variables */
    static integer j, k;
    static real s;
    static realcomplex ak, bk;
    static integer kp;
    static realcomplex akm1, bkm1, akm1k;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    static realcomplex denom;
    extern /* Subroutine */ int cgemv_(char *, integer *, integer *, realcomplex *
	    , realcomplex *, integer *, realcomplex *, integer *, realcomplex *, realcomplex *
	    , integer *, ftnlen), cgeru_(integer *, integer *, realcomplex *, 
	    realcomplex *, integer *, realcomplex *, integer *, realcomplex *, integer *),
	     cswap_(integer *, realcomplex *, integer *, realcomplex *, integer *);
    static logical upper;
    extern /* Subroutine */ int clacgv_(integer *, realcomplex *, integer *), 
	    csscal_(integer *, real *, realcomplex *, integer *), xerbla_(char *, 
	    integer *, ftnlen);


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

/*  CHETRS solves a system of linear equations A*X = B with a realcomplex */
/*  Hermitian matrix A using the factorization A = U*D*U**H or */
/*  A = L*D*L**H computed by CHETRF. */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          Specifies whether the details of the factorization are stored */
/*          as an upper or lower triangular matrix. */
/*          = 'U':  Upper triangular, form is A = U*D*U**H; */
/*          = 'L':  Lower triangular, form is A = L*D*L**H. */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  NRHS    (input) INTEGER */
/*          The number of right hand sides, i.e., the number of columns */
/*          of the matrix B.  NRHS >= 0. */

/*  A       (input) COMPLEX array, dimension (LDA,N) */
/*          The block diagonal matrix D and the multipliers used to */
/*          obtain the factor U or L as computed by CHETRF. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,N). */

/*  IPIV    (input) INTEGER array, dimension (N) */
/*          Details of the interchanges and the block structure of D */
/*          as determined by CHETRF. */

/*  B       (input/output) COMPLEX array, dimension (LDB,NRHS) */
/*          On entry, the right hand side matrix B. */
/*          On exit, the solution matrix X. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B.  LDB >= max(1,N). */

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

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;
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
    } else if (*nrhs < 0) {
	*info = -3;
    } else if (*lda < max(1,*n)) {
	*info = -5;
    } else if (*ldb < max(1,*n)) {
	*info = -8;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CHETRS", &i__1, (ftnlen)6);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *nrhs == 0) {
	return 0;
    }

    if (upper) {

/*        Solve A*X = B, where A = U*D*U'. */

/*        First solve U*D*X = B, overwriting B with X. */

/*        K is the main loop index, decreasing from N to 1 in steps of */
/*        1 or 2, depending on the size of the diagonal blocks. */

	k = *n;
L10:

/*        If K < 1, exit from loop. */

	if (k < 1) {
	    goto L30;
	}

	if (ipiv[k] > 0) {

/*           1 x 1 diagonal block */

/*           Interchange rows K and IPIV(K). */

	    kp = ipiv[k];
	    if (kp != k) {
		cswap_(nrhs, &b[k + b_dim1], ldb, &b[kp + b_dim1], ldb);
	    }

/*           Multiply by inv(U(K)), where U(K) is the transformation */
/*           stored in column K of A. */

	    i__1 = k - 1;
	    q__1.r = -1.f, q__1.i = -0.f;
	    cgeru_(&i__1, nrhs, &q__1, &a[k * a_dim1 + 1], &c__1, &b[k + 
		    b_dim1], ldb, &b[b_dim1 + 1], ldb);

/*           Multiply by the inverse of the diagonal block. */

	    i__1 = k + k * a_dim1;
	    s = 1.f / a[i__1].r;
	    csscal_(nrhs, &s, &b[k + b_dim1], ldb);
	    --k;
	} else {

/*           2 x 2 diagonal block */

/*           Interchange rows K-1 and -IPIV(K). */

	    kp = -ipiv[k];
	    if (kp != k - 1) {
		cswap_(nrhs, &b[k - 1 + b_dim1], ldb, &b[kp + b_dim1], ldb);
	    }

/*           Multiply by inv(U(K)), where U(K) is the transformation */
/*           stored in columns K-1 and K of A. */

	    i__1 = k - 2;
	    q__1.r = -1.f, q__1.i = -0.f;
	    cgeru_(&i__1, nrhs, &q__1, &a[k * a_dim1 + 1], &c__1, &b[k + 
		    b_dim1], ldb, &b[b_dim1 + 1], ldb);
	    i__1 = k - 2;
	    q__1.r = -1.f, q__1.i = -0.f;
	    cgeru_(&i__1, nrhs, &q__1, &a[(k - 1) * a_dim1 + 1], &c__1, &b[k 
		    - 1 + b_dim1], ldb, &b[b_dim1 + 1], ldb);

/*           Multiply by the inverse of the diagonal block. */

	    i__1 = k - 1 + k * a_dim1;
	    akm1k.r = a[i__1].r, akm1k.i = a[i__1].i;
	    c_div(&q__1, &a[k - 1 + (k - 1) * a_dim1], &akm1k);
	    akm1.r = q__1.r, akm1.i = q__1.i;
	    r_cnjg(&q__2, &akm1k);
	    c_div(&q__1, &a[k + k * a_dim1], &q__2);
	    ak.r = q__1.r, ak.i = q__1.i;
	    q__2.r = akm1.r * ak.r - akm1.i * ak.i, q__2.i = akm1.r * ak.i + 
		    akm1.i * ak.r;
	    q__1.r = q__2.r - 1.f, q__1.i = q__2.i - 0.f;
	    denom.r = q__1.r, denom.i = q__1.i;
	    i__1 = *nrhs;
	    for (j = 1; j <= i__1; ++j) {
		c_div(&q__1, &b[k - 1 + j * b_dim1], &akm1k);
		bkm1.r = q__1.r, bkm1.i = q__1.i;
		r_cnjg(&q__2, &akm1k);
		c_div(&q__1, &b[k + j * b_dim1], &q__2);
		bk.r = q__1.r, bk.i = q__1.i;
		i__2 = k - 1 + j * b_dim1;
		q__3.r = ak.r * bkm1.r - ak.i * bkm1.i, q__3.i = ak.r * 
			bkm1.i + ak.i * bkm1.r;
		q__2.r = q__3.r - bk.r, q__2.i = q__3.i - bk.i;
		c_div(&q__1, &q__2, &denom);
		b[i__2].r = q__1.r, b[i__2].i = q__1.i;
		i__2 = k + j * b_dim1;
		q__3.r = akm1.r * bk.r - akm1.i * bk.i, q__3.i = akm1.r * 
			bk.i + akm1.i * bk.r;
		q__2.r = q__3.r - bkm1.r, q__2.i = q__3.i - bkm1.i;
		c_div(&q__1, &q__2, &denom);
		b[i__2].r = q__1.r, b[i__2].i = q__1.i;
/* L20: */
	    }
	    k += -2;
	}

	goto L10;
L30:

/*        Next solve U'*X = B, overwriting B with X. */

/*        K is the main loop index, increasing from 1 to N in steps of */
/*        1 or 2, depending on the size of the diagonal blocks. */

	k = 1;
L40:

/*        If K > N, exit from loop. */

	if (k > *n) {
	    goto L50;
	}

	if (ipiv[k] > 0) {

/*           1 x 1 diagonal block */

/*           Multiply by inv(U'(K)), where U(K) is the transformation */
/*           stored in column K of A. */

	    if (k > 1) {
		clacgv_(nrhs, &b[k + b_dim1], ldb);
		i__1 = k - 1;
		q__1.r = -1.f, q__1.i = -0.f;
		cgemv_("Conjugate transpose", &i__1, nrhs, &q__1, &b[b_offset]
			, ldb, &a[k * a_dim1 + 1], &c__1, &c_b1, &b[k + 
			b_dim1], ldb, (ftnlen)19);
		clacgv_(nrhs, &b[k + b_dim1], ldb);
	    }

/*           Interchange rows K and IPIV(K). */

	    kp = ipiv[k];
	    if (kp != k) {
		cswap_(nrhs, &b[k + b_dim1], ldb, &b[kp + b_dim1], ldb);
	    }
	    ++k;
	} else {

/*           2 x 2 diagonal block */

/*           Multiply by inv(U'(K+1)), where U(K+1) is the transformation */
/*           stored in columns K and K+1 of A. */

	    if (k > 1) {
		clacgv_(nrhs, &b[k + b_dim1], ldb);
		i__1 = k - 1;
		q__1.r = -1.f, q__1.i = -0.f;
		cgemv_("Conjugate transpose", &i__1, nrhs, &q__1, &b[b_offset]
			, ldb, &a[k * a_dim1 + 1], &c__1, &c_b1, &b[k + 
			b_dim1], ldb, (ftnlen)19);
		clacgv_(nrhs, &b[k + b_dim1], ldb);

		clacgv_(nrhs, &b[k + 1 + b_dim1], ldb);
		i__1 = k - 1;
		q__1.r = -1.f, q__1.i = -0.f;
		cgemv_("Conjugate transpose", &i__1, nrhs, &q__1, &b[b_offset]
			, ldb, &a[(k + 1) * a_dim1 + 1], &c__1, &c_b1, &b[k + 
			1 + b_dim1], ldb, (ftnlen)19);
		clacgv_(nrhs, &b[k + 1 + b_dim1], ldb);
	    }

/*           Interchange rows K and -IPIV(K). */

	    kp = -ipiv[k];
	    if (kp != k) {
		cswap_(nrhs, &b[k + b_dim1], ldb, &b[kp + b_dim1], ldb);
	    }
	    k += 2;
	}

	goto L40;
L50:

	;
    } else {

/*        Solve A*X = B, where A = L*D*L'. */

/*        First solve L*D*X = B, overwriting B with X. */

/*        K is the main loop index, increasing from 1 to N in steps of */
/*        1 or 2, depending on the size of the diagonal blocks. */

	k = 1;
L60:

/*        If K > N, exit from loop. */

	if (k > *n) {
	    goto L80;
	}

	if (ipiv[k] > 0) {

/*           1 x 1 diagonal block */

/*           Interchange rows K and IPIV(K). */

	    kp = ipiv[k];
	    if (kp != k) {
		cswap_(nrhs, &b[k + b_dim1], ldb, &b[kp + b_dim1], ldb);
	    }

/*           Multiply by inv(L(K)), where L(K) is the transformation */
/*           stored in column K of A. */

	    if (k < *n) {
		i__1 = *n - k;
		q__1.r = -1.f, q__1.i = -0.f;
		cgeru_(&i__1, nrhs, &q__1, &a[k + 1 + k * a_dim1], &c__1, &b[
			k + b_dim1], ldb, &b[k + 1 + b_dim1], ldb);
	    }

/*           Multiply by the inverse of the diagonal block. */

	    i__1 = k + k * a_dim1;
	    s = 1.f / a[i__1].r;
	    csscal_(nrhs, &s, &b[k + b_dim1], ldb);
	    ++k;
	} else {

/*           2 x 2 diagonal block */

/*           Interchange rows K+1 and -IPIV(K). */

	    kp = -ipiv[k];
	    if (kp != k + 1) {
		cswap_(nrhs, &b[k + 1 + b_dim1], ldb, &b[kp + b_dim1], ldb);
	    }

/*           Multiply by inv(L(K)), where L(K) is the transformation */
/*           stored in columns K and K+1 of A. */

	    if (k < *n - 1) {
		i__1 = *n - k - 1;
		q__1.r = -1.f, q__1.i = -0.f;
		cgeru_(&i__1, nrhs, &q__1, &a[k + 2 + k * a_dim1], &c__1, &b[
			k + b_dim1], ldb, &b[k + 2 + b_dim1], ldb);
		i__1 = *n - k - 1;
		q__1.r = -1.f, q__1.i = -0.f;
		cgeru_(&i__1, nrhs, &q__1, &a[k + 2 + (k + 1) * a_dim1], &
			c__1, &b[k + 1 + b_dim1], ldb, &b[k + 2 + b_dim1], 
			ldb);
	    }

/*           Multiply by the inverse of the diagonal block. */

	    i__1 = k + 1 + k * a_dim1;
	    akm1k.r = a[i__1].r, akm1k.i = a[i__1].i;
	    r_cnjg(&q__2, &akm1k);
	    c_div(&q__1, &a[k + k * a_dim1], &q__2);
	    akm1.r = q__1.r, akm1.i = q__1.i;
	    c_div(&q__1, &a[k + 1 + (k + 1) * a_dim1], &akm1k);
	    ak.r = q__1.r, ak.i = q__1.i;
	    q__2.r = akm1.r * ak.r - akm1.i * ak.i, q__2.i = akm1.r * ak.i + 
		    akm1.i * ak.r;
	    q__1.r = q__2.r - 1.f, q__1.i = q__2.i - 0.f;
	    denom.r = q__1.r, denom.i = q__1.i;
	    i__1 = *nrhs;
	    for (j = 1; j <= i__1; ++j) {
		r_cnjg(&q__2, &akm1k);
		c_div(&q__1, &b[k + j * b_dim1], &q__2);
		bkm1.r = q__1.r, bkm1.i = q__1.i;
		c_div(&q__1, &b[k + 1 + j * b_dim1], &akm1k);
		bk.r = q__1.r, bk.i = q__1.i;
		i__2 = k + j * b_dim1;
		q__3.r = ak.r * bkm1.r - ak.i * bkm1.i, q__3.i = ak.r * 
			bkm1.i + ak.i * bkm1.r;
		q__2.r = q__3.r - bk.r, q__2.i = q__3.i - bk.i;
		c_div(&q__1, &q__2, &denom);
		b[i__2].r = q__1.r, b[i__2].i = q__1.i;
		i__2 = k + 1 + j * b_dim1;
		q__3.r = akm1.r * bk.r - akm1.i * bk.i, q__3.i = akm1.r * 
			bk.i + akm1.i * bk.r;
		q__2.r = q__3.r - bkm1.r, q__2.i = q__3.i - bkm1.i;
		c_div(&q__1, &q__2, &denom);
		b[i__2].r = q__1.r, b[i__2].i = q__1.i;
/* L70: */
	    }
	    k += 2;
	}

	goto L60;
L80:

/*        Next solve L'*X = B, overwriting B with X. */

/*        K is the main loop index, decreasing from N to 1 in steps of */
/*        1 or 2, depending on the size of the diagonal blocks. */

	k = *n;
L90:

/*        If K < 1, exit from loop. */

	if (k < 1) {
	    goto L100;
	}

	if (ipiv[k] > 0) {

/*           1 x 1 diagonal block */

/*           Multiply by inv(L'(K)), where L(K) is the transformation */
/*           stored in column K of A. */

	    if (k < *n) {
		clacgv_(nrhs, &b[k + b_dim1], ldb);
		i__1 = *n - k;
		q__1.r = -1.f, q__1.i = -0.f;
		cgemv_("Conjugate transpose", &i__1, nrhs, &q__1, &b[k + 1 + 
			b_dim1], ldb, &a[k + 1 + k * a_dim1], &c__1, &c_b1, &
			b[k + b_dim1], ldb, (ftnlen)19);
		clacgv_(nrhs, &b[k + b_dim1], ldb);
	    }

/*           Interchange rows K and IPIV(K). */

	    kp = ipiv[k];
	    if (kp != k) {
		cswap_(nrhs, &b[k + b_dim1], ldb, &b[kp + b_dim1], ldb);
	    }
	    --k;
	} else {

/*           2 x 2 diagonal block */

/*           Multiply by inv(L'(K-1)), where L(K-1) is the transformation */
/*           stored in columns K-1 and K of A. */

	    if (k < *n) {
		clacgv_(nrhs, &b[k + b_dim1], ldb);
		i__1 = *n - k;
		q__1.r = -1.f, q__1.i = -0.f;
		cgemv_("Conjugate transpose", &i__1, nrhs, &q__1, &b[k + 1 + 
			b_dim1], ldb, &a[k + 1 + k * a_dim1], &c__1, &c_b1, &
			b[k + b_dim1], ldb, (ftnlen)19);
		clacgv_(nrhs, &b[k + b_dim1], ldb);

		clacgv_(nrhs, &b[k - 1 + b_dim1], ldb);
		i__1 = *n - k;
		q__1.r = -1.f, q__1.i = -0.f;
		cgemv_("Conjugate transpose", &i__1, nrhs, &q__1, &b[k + 1 + 
			b_dim1], ldb, &a[k + 1 + (k - 1) * a_dim1], &c__1, &
			c_b1, &b[k - 1 + b_dim1], ldb, (ftnlen)19);
		clacgv_(nrhs, &b[k - 1 + b_dim1], ldb);
	    }

/*           Interchange rows K and -IPIV(K). */

	    kp = -ipiv[k];
	    if (kp != k) {
		cswap_(nrhs, &b[k + b_dim1], ldb, &b[kp + b_dim1], ldb);
	    }
	    k += -2;
	}

	goto L90;
L100:
	;
    }

    return 0;

/*     End of CHETRS */

} /* chetrs_ */

