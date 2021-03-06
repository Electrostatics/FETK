/* ./src_f77/dggglm.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;
static integer c_n1 = -1;
static doublereal c_b32 = -1.;
static doublereal c_b34 = 1.;

/* Subroutine */ int dggglm_(integer *n, integer *m, integer *p, doublereal *
	a, integer *lda, doublereal *b, integer *ldb, doublereal *d__, 
	doublereal *x, doublereal *y, doublereal *work, integer *lwork, 
	integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
    static integer i__, nb, np, nb1, nb2, nb3, nb4, lopt;
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, ftnlen), dcopy_(integer *, 
	    doublereal *, integer *, doublereal *, integer *), dtrsv_(char *, 
	    char *, char *, integer *, doublereal *, integer *, doublereal *, 
	    integer *, ftnlen, ftnlen, ftnlen), dggqrf_(integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *, integer *), 
	    xerbla_(char *, integer *, ftnlen);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int dormqr_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *, integer *, ftnlen, ftnlen), 
	    dormrq_(char *, char *, integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *, integer *, integer *, ftnlen, ftnlen);
    static integer lwkopt;
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

/*  DGGGLM solves a general Gauss-Markov linear model (GLM) problem: */

/*          minimize || y ||_2   subject to   d = A*x + B*y */
/*              x */

/*  where A is an N-by-M matrix, B is an N-by-P matrix, and d is a */
/*  given N-vector. It is assumed that M <= N <= M+P, and */

/*             rank(A) = M    and    rank( A B ) = N. */

/*  Under these assumptions, the constrained equation is always */
/*  consistent, and there is a unique solution x and a minimal 2-norm */
/*  solution y, which is obtained using a generalized QR factorization */
/*  of A and B. */

/*  In particular, if matrix B is square nonsingular, then the problem */
/*  GLM is equivalent to the following weighted linear least squares */
/*  problem */

/*               minimize || inv(B)*(d-A*x) ||_2 */
/*                   x */

/*  where inv(B) denotes the inverse of B. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The number of rows of the matrices A and B.  N >= 0. */

/*  M       (input) INTEGER */
/*          The number of columns of the matrix A.  0 <= M <= N. */

/*  P       (input) INTEGER */
/*          The number of columns of the matrix B.  P >= N-M. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,M) */
/*          On entry, the N-by-M matrix A. */
/*          On exit, A is destroyed. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,N). */

/*  B       (input/output) DOUBLE PRECISION array, dimension (LDB,P) */
/*          On entry, the N-by-P matrix B. */
/*          On exit, B is destroyed. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B. LDB >= max(1,N). */

/*  D       (input/output) DOUBLE PRECISION array, dimension (N) */
/*          On entry, D is the left hand side of the GLM equation. */
/*          On exit, D is destroyed. */

/*  X       (output) DOUBLE PRECISION array, dimension (M) */
/*  Y       (output) DOUBLE PRECISION array, dimension (P) */
/*          On exit, X and Y are the solutions of the GLM problem. */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. LWORK >= max(1,N+M+P). */
/*          For optimum performance, LWORK >= M+min(N,P)+max(N,P)*NB, */
/*          where NB is an upper bound for the optimal blocksizes for */
/*          DGEQRF, SGERQF, DORMQR and SORMRQ. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit. */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value. */

/*  =================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    --d__;
    --x;
    --y;
    --work;

    /* Function Body */
    *info = 0;
    np = min(*n,*p);
    nb1 = ilaenv_(&c__1, "DGEQRF", " ", n, m, &c_n1, &c_n1, (ftnlen)6, (
	    ftnlen)1);
    nb2 = ilaenv_(&c__1, "DGERQF", " ", n, m, &c_n1, &c_n1, (ftnlen)6, (
	    ftnlen)1);
    nb3 = ilaenv_(&c__1, "DORMQR", " ", n, m, p, &c_n1, (ftnlen)6, (ftnlen)1);
    nb4 = ilaenv_(&c__1, "DORMRQ", " ", n, m, p, &c_n1, (ftnlen)6, (ftnlen)1);
/* Computing MAX */
    i__1 = max(nb1,nb2), i__1 = max(i__1,nb3);
    nb = max(i__1,nb4);
    lwkopt = *m + np + max(*n,*p) * nb;
    work[1] = (doublereal) lwkopt;
    lquery = *lwork == -1;
    if (*n < 0) {
	*info = -1;
    } else if (*m < 0 || *m > *n) {
	*info = -2;
    } else if (*p < 0 || *p < *n - *m) {
	*info = -3;
    } else if (*lda < max(1,*n)) {
	*info = -5;
    } else if (*ldb < max(1,*n)) {
	*info = -7;
    } else /* if(complicated condition) */ {
/* Computing MAX */
	i__1 = 1, i__2 = *n + *m + *p;
	if (*lwork < max(i__1,i__2) && ! lquery) {
	    *info = -12;
	}
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGGGLM", &i__1, (ftnlen)6);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

/*     Compute the GQR factorization of matrices A and B: */

/*            Q'*A = ( R11 ) M,    Q'*B*Z' = ( T11   T12 ) M */
/*                   (  0  ) N-M             (  0    T22 ) N-M */
/*                      M                     M+P-N  N-M */

/*     where R11 and T22 are upper triangular, and Q and Z are */
/*     orthogonal. */

    i__1 = *lwork - *m - np;
    dggqrf_(n, m, p, &a[a_offset], lda, &work[1], &b[b_offset], ldb, &work[*m 
	    + 1], &work[*m + np + 1], &i__1, info);
    lopt = (integer) work[*m + np + 1];

/*     Update left-hand-side vector d = Q'*d = ( d1 ) M */
/*                                             ( d2 ) N-M */

    i__1 = max(1,*n);
    i__2 = *lwork - *m - np;
    dormqr_("Left", "Transpose", n, &c__1, m, &a[a_offset], lda, &work[1], &
	    d__[1], &i__1, &work[*m + np + 1], &i__2, info, (ftnlen)4, (
	    ftnlen)9);
/* Computing MAX */
    i__1 = lopt, i__2 = (integer) work[*m + np + 1];
    lopt = max(i__1,i__2);

/*     Solve T22*y2 = d2 for y2 */

    i__1 = *n - *m;
    dtrsv_("Upper", "No transpose", "Non unit", &i__1, &b[*m + 1 + (*m + *p - 
	    *n + 1) * b_dim1], ldb, &d__[*m + 1], &c__1, (ftnlen)5, (ftnlen)
	    12, (ftnlen)8);
    i__1 = *n - *m;
    dcopy_(&i__1, &d__[*m + 1], &c__1, &y[*m + *p - *n + 1], &c__1);

/*     Set y1 = 0 */

    i__1 = *m + *p - *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	y[i__] = 0.;
/* L10: */
    }

/*     Update d1 = d1 - T12*y2 */

    i__1 = *n - *m;
    dgemv_("No transpose", m, &i__1, &c_b32, &b[(*m + *p - *n + 1) * b_dim1 + 
	    1], ldb, &y[*m + *p - *n + 1], &c__1, &c_b34, &d__[1], &c__1, (
	    ftnlen)12);

/*     Solve triangular system: R11*x = d1 */

    dtrsv_("Upper", "No Transpose", "Non unit", m, &a[a_offset], lda, &d__[1],
	     &c__1, (ftnlen)5, (ftnlen)12, (ftnlen)8);

/*     Copy D to X */

    dcopy_(m, &d__[1], &c__1, &x[1], &c__1);

/*     Backward transformation y = Z'*y */

/* Computing MAX */
    i__1 = 1, i__2 = *n - *p + 1;
    i__3 = max(1,*p);
    i__4 = *lwork - *m - np;
    dormrq_("Left", "Transpose", p, &c__1, &np, &b[max(i__1,i__2) + b_dim1], 
	    ldb, &work[*m + 1], &y[1], &i__3, &work[*m + np + 1], &i__4, info,
	     (ftnlen)4, (ftnlen)9);
/* Computing MAX */
    i__1 = lopt, i__2 = (integer) work[*m + np + 1];
    work[1] = (doublereal) (*m + np + max(i__1,i__2));

    return 0;

/*     End of DGGGLM */

} /* dggglm_ */

