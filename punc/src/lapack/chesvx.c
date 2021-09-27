/* ./src_f77/chesvx.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;
static integer c_n1 = -1;

/* Subroutine */ int chesvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, realcomplex *a, integer *lda, realcomplex *af, integer *ldaf, integer *
	ipiv, realcomplex *b, integer *ldb, realcomplex *x, integer *ldx, real *rcond,
	 real *ferr, real *berr, realcomplex *work, integer *lwork, real *rwork, 
	integer *info, ftnlen fact_len, ftnlen uplo_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, af_dim1, af_offset, b_dim1, b_offset, x_dim1, 
	    x_offset, i__1, i__2;

    /* Local variables */
    static integer nb;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    static real anorm;
    extern doublereal clanhe_(char *, char *, integer *, realcomplex *, integer *,
	     real *, ftnlen, ftnlen);
    extern /* Subroutine */ int checon_(char *, integer *, realcomplex *, integer 
	    *, integer *, real *, real *, realcomplex *, integer *, ftnlen);
    extern doublereal slamch_(char *, ftnlen);
    static logical nofact;
    extern /* Subroutine */ int cherfs_(char *, integer *, integer *, realcomplex 
	    *, integer *, realcomplex *, integer *, integer *, realcomplex *, integer 
	    *, realcomplex *, integer *, real *, real *, realcomplex *, real *, 
	    integer *, ftnlen), chetrf_(char *, integer *, realcomplex *, integer 
	    *, integer *, realcomplex *, integer *, integer *, ftnlen), clacpy_(
	    char *, integer *, integer *, realcomplex *, integer *, realcomplex *, 
	    integer *, ftnlen);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int xerbla_(char *, integer *, ftnlen), chetrs_(
	    char *, integer *, integer *, realcomplex *, integer *, integer *, 
	    realcomplex *, integer *, integer *, ftnlen);
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

/*  CHESVX uses the diagonal pivoting factorization to compute the */
/*  solution to a complex system of linear equations A * X = B, */
/*  where A is an N-by-N Hermitian matrix and X and B are N-by-NRHS */
/*  matrices. */

/*  Error bounds on the solution and a condition estimate are also */
/*  provided. */

/*  Description */
/*  =========== */

/*  The following steps are performed: */

/*  1. If FACT = 'N', the diagonal pivoting method is used to factor A. */
/*     The form of the factorization is */
/*        A = U * D * U**H,  if UPLO = 'U', or */
/*        A = L * D * L**H,  if UPLO = 'L', */
/*     where U (or L) is a product of permutation and unit upper (lower) */
/*     triangular matrices, and D is Hermitian and block diagonal with */
/*     1-by-1 and 2-by-2 diagonal blocks. */

/*  2. If some D(i,i)=0, so that D is exactly singular, then the routine */
/*     returns with INFO = i. Otherwise, the factored form of A is used */
/*     to estimate the condition number of the matrix A.  If the */
/*     reciprocal of the condition number is less than machine precision, */
/*     INFO = N+1 is returned as a warning, but the routine still goes on */
/*     to solve for X and compute error bounds as described below. */

/*  3. The system of equations is solved for X using the factored form */
/*     of A. */

/*  4. Iterative refinement is applied to improve the computed solution */
/*     matrix and calculate error bounds and backward error estimates */
/*     for it. */

/*  Arguments */
/*  ========= */

/*  FACT    (input) CHARACTER*1 */
/*          Specifies whether or not the factored form of A has been */
/*          supplied on entry. */
/*          = 'F':  On entry, AF and IPIV contain the factored form */
/*                  of A.  A, AF and IPIV will not be modified. */
/*          = 'N':  The matrix A will be copied to AF and factored. */

/*  UPLO    (input) CHARACTER*1 */
/*          = 'U':  Upper triangle of A is stored; */
/*          = 'L':  Lower triangle of A is stored. */

/*  N       (input) INTEGER */
/*          The number of linear equations, i.e., the order of the */
/*          matrix A.  N >= 0. */

/*  NRHS    (input) INTEGER */
/*          The number of right hand sides, i.e., the number of columns */
/*          of the matrices B and X.  NRHS >= 0. */

/*  A       (input) COMPLEX array, dimension (LDA,N) */
/*          The Hermitian matrix A.  If UPLO = 'U', the leading N-by-N */
/*          upper triangular part of A contains the upper triangular part */
/*          of the matrix A, and the strictly lower triangular part of A */
/*          is not referenced.  If UPLO = 'L', the leading N-by-N lower */
/*          triangular part of A contains the lower triangular part of */
/*          the matrix A, and the strictly upper triangular part of A is */
/*          not referenced. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,N). */

/*  AF      (input or output) COMPLEX array, dimension (LDAF,N) */
/*          If FACT = 'F', then AF is an input argument and on entry */
/*          contains the block diagonal matrix D and the multipliers used */
/*          to obtain the factor U or L from the factorization */
/*          A = U*D*U**H or A = L*D*L**H as computed by CHETRF. */

/*          If FACT = 'N', then AF is an output argument and on exit */
/*          returns the block diagonal matrix D and the multipliers used */
/*          to obtain the factor U or L from the factorization */
/*          A = U*D*U**H or A = L*D*L**H. */

/*  LDAF    (input) INTEGER */
/*          The leading dimension of the array AF.  LDAF >= max(1,N). */

/*  IPIV    (input or output) INTEGER array, dimension (N) */
/*          If FACT = 'F', then IPIV is an input argument and on entry */
/*          contains details of the interchanges and the block structure */
/*          of D, as determined by CHETRF. */
/*          If IPIV(k) > 0, then rows and columns k and IPIV(k) were */
/*          interchanged and D(k,k) is a 1-by-1 diagonal block. */
/*          If UPLO = 'U' and IPIV(k) = IPIV(k-1) < 0, then rows and */
/*          columns k-1 and -IPIV(k) were interchanged and D(k-1:k,k-1:k) */
/*          is a 2-by-2 diagonal block.  If UPLO = 'L' and IPIV(k) = */
/*          IPIV(k+1) < 0, then rows and columns k+1 and -IPIV(k) were */
/*          interchanged and D(k:k+1,k:k+1) is a 2-by-2 diagonal block. */

/*          If FACT = 'N', then IPIV is an output argument and on exit */
/*          contains details of the interchanges and the block structure */
/*          of D, as determined by CHETRF. */

/*  B       (input) COMPLEX array, dimension (LDB,NRHS) */
/*          The N-by-NRHS right hand side matrix B. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B.  LDB >= max(1,N). */

/*  X       (output) COMPLEX array, dimension (LDX,NRHS) */
/*          If INFO = 0 or INFO = N+1, the N-by-NRHS solution matrix X. */

/*  LDX     (input) INTEGER */
/*          The leading dimension of the array X.  LDX >= max(1,N). */

/*  RCOND   (output) REAL */
/*          The estimate of the reciprocal condition number of the matrix */
/*          A.  If RCOND is less than the machine precision (in */
/*          particular, if RCOND = 0), the matrix is singular to working */
/*          precision.  This condition is indicated by a return code of */
/*          INFO > 0. */

/*  FERR    (output) REAL array, dimension (NRHS) */
/*          The estimated forward error bound for each solution vector */
/*          X(j) (the j-th column of the solution matrix X). */
/*          If XTRUE is the true solution corresponding to X(j), FERR(j) */
/*          is an estimated upper bound for the magnitude of the largest */
/*          element in (X(j) - XTRUE) divided by the magnitude of the */
/*          largest element in X(j).  The estimate is as reliable as */
/*          the estimate for RCOND, and is almost always a slight */
/*          overestimate of the true error. */

/*  BERR    (output) REAL array, dimension (NRHS) */
/*          The componentwise relative backward error of each solution */
/*          vector X(j) (i.e., the smallest relative change in */
/*          any element of A or B that makes X(j) an exact solution). */

/*  WORK    (workspace/output) COMPLEX array, dimension (LWORK) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The length of WORK.  LWORK >= 2*N, and for best performance */
/*          LWORK >= N*NB, where NB is the optimal blocksize for */
/*          CHETRF. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  RWORK   (workspace) REAL array, dimension (N) */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument had an illegal value */
/*          > 0: if INFO = i, and i is */
/*                <= N:  D(i,i) is exactly zero.  The factorization */
/*                       has been completed but the factor D is exactly */
/*                       singular, so the solution and error bounds could */
/*                       not be computed. RCOND = 0 is returned. */
/*                = N+1: D is nonsingular, but RCOND is less than machine */
/*                       precision, meaning that the matrix is singular */
/*                       to working precision.  Nevertheless, the */
/*                       solution and error bounds are computed because */
/*                       there are a number of situations where the */
/*                       computed solution can be more accurate than the */
/*                       value of RCOND would suggest. */

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
    af_dim1 = *ldaf;
    af_offset = 1 + af_dim1;
    af -= af_offset;
    --ipiv;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    x_dim1 = *ldx;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --ferr;
    --berr;
    --work;
    --rwork;

    /* Function Body */
    *info = 0;
    nofact = lsame_(fact, "N", (ftnlen)1, (ftnlen)1);
    lquery = *lwork == -1;
    if (! nofact && ! lsame_(fact, "F", (ftnlen)1, (ftnlen)1)) {
	*info = -1;
    } else if (! lsame_(uplo, "U", (ftnlen)1, (ftnlen)1) && ! lsame_(uplo, 
	    "L", (ftnlen)1, (ftnlen)1)) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*nrhs < 0) {
	*info = -4;
    } else if (*lda < max(1,*n)) {
	*info = -6;
    } else if (*ldaf < max(1,*n)) {
	*info = -8;
    } else if (*ldb < max(1,*n)) {
	*info = -11;
    } else if (*ldx < max(1,*n)) {
	*info = -13;
    } else /* if(complicated condition) */ {
/* Computing MAX */
	i__1 = 1, i__2 = *n << 1;
	if (*lwork < max(i__1,i__2) && ! lquery) {
	    *info = -18;
	}
    }

    if (*info == 0) {
	nb = ilaenv_(&c__1, "CHETRF", uplo, n, &c_n1, &c_n1, &c_n1, (ftnlen)6,
		 (ftnlen)1);
	lwkopt = *n * nb;
	work[1].r = (real) lwkopt, work[1].i = 0.f;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CHESVX", &i__1, (ftnlen)6);
	return 0;
    } else if (lquery) {
	return 0;
    }

    if (nofact) {

/*        Compute the factorization A = U*D*U' or A = L*D*L'. */

	clacpy_(uplo, n, n, &a[a_offset], lda, &af[af_offset], ldaf, (ftnlen)
		1);
	chetrf_(uplo, n, &af[af_offset], ldaf, &ipiv[1], &work[1], lwork, 
		info, (ftnlen)1);

/*        Return if INFO is non-zero. */

	if (*info != 0) {
	    if (*info > 0) {
		*rcond = 0.f;
	    }
	    return 0;
	}
    }

/*     Compute the norm of the matrix A. */

    anorm = clanhe_("I", uplo, n, &a[a_offset], lda, &rwork[1], (ftnlen)1, (
	    ftnlen)1);

/*     Compute the reciprocal of the condition number of A. */

    checon_(uplo, n, &af[af_offset], ldaf, &ipiv[1], &anorm, rcond, &work[1], 
	    info, (ftnlen)1);

/*     Set INFO = N+1 if the matrix is singular to working precision. */

    if (*rcond < slamch_("Epsilon", (ftnlen)7)) {
	*info = *n + 1;
    }

/*     Compute the solution vectors X. */

    clacpy_("Full", n, nrhs, &b[b_offset], ldb, &x[x_offset], ldx, (ftnlen)4);
    chetrs_(uplo, n, nrhs, &af[af_offset], ldaf, &ipiv[1], &x[x_offset], ldx, 
	    info, (ftnlen)1);

/*     Use iterative refinement to improve the computed solutions and */
/*     compute error bounds and backward error estimates for them. */

    cherfs_(uplo, n, nrhs, &a[a_offset], lda, &af[af_offset], ldaf, &ipiv[1], 
	    &b[b_offset], ldb, &x[x_offset], ldx, &ferr[1], &berr[1], &work[1]
	    , &rwork[1], info, (ftnlen)1);

    work[1].r = (real) lwkopt, work[1].i = 0.f;

    return 0;

/*     End of CHESVX */

} /* chesvx_ */

