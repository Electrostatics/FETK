/* ./src_f77/zlatzm.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static doublecomplex c_b1 = {1.,0.};
static integer c__1 = 1;

/* Subroutine */ int zlatzm_(char *side, integer *m, integer *n, 
	doublecomplex *v, integer *incv, doublecomplex *tau, doublecomplex *
	c1, doublecomplex *c2, integer *ldc, doublecomplex *work, ftnlen 
	side_len)
{
    /* System generated locals */
    integer c1_dim1, c1_offset, c2_dim1, c2_offset, i__1;
    doublecomplex z__1;

    /* Local variables */
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    extern /* Subroutine */ int zgerc_(integer *, integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zgemv_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, ftnlen), 
	    zgeru_(integer *, integer *, doublecomplex *, doublecomplex *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, integer *)
	    , zcopy_(integer *, doublecomplex *, integer *, doublecomplex *, 
	    integer *), zaxpy_(integer *, doublecomplex *, doublecomplex *, 
	    integer *, doublecomplex *, integer *), zlacgv_(integer *, 
	    doublecomplex *, integer *);


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

/*  This routine is deprecated and has been replaced by routine ZUNMRZ. */

/*  ZLATZM applies a Householder matrix generated by ZTZRQF to a matrix. */

/*  Let P = I - tau*u*u',   u = ( 1 ), */
/*                              ( v ) */
/*  where v is an (m-1) vector if SIDE = 'L', or a (n-1) vector if */
/*  SIDE = 'R'. */

/*  If SIDE equals 'L', let */
/*         C = [ C1 ] 1 */
/*             [ C2 ] m-1 */
/*               n */
/*  Then C is overwritten by P*C. */

/*  If SIDE equals 'R', let */
/*         C = [ C1, C2 ] m */
/*                1  n-1 */
/*  Then C is overwritten by C*P. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': form P * C */
/*          = 'R': form C * P */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. */

/*  V       (input) COMPLEX*16 array, dimension */
/*                  (1 + (M-1)*abs(INCV)) if SIDE = 'L' */
/*                  (1 + (N-1)*abs(INCV)) if SIDE = 'R' */
/*          The vector v in the representation of P. V is not used */
/*          if TAU = 0. */

/*  INCV    (input) INTEGER */
/*          The increment between elements of v. INCV <> 0 */

/*  TAU     (input) COMPLEX*16 */
/*          The value tau in the representation of P. */

/*  C1      (input/output) COMPLEX*16 array, dimension */
/*                         (LDC,N) if SIDE = 'L' */
/*                         (M,1)   if SIDE = 'R' */
/*          On entry, the n-vector C1 if SIDE = 'L', or the m-vector C1 */
/*          if SIDE = 'R'. */

/*          On exit, the first row of P*C if SIDE = 'L', or the first */
/*          column of C*P if SIDE = 'R'. */

/*  C2      (input/output) COMPLEX*16 array, dimension */
/*                         (LDC, N)   if SIDE = 'L' */
/*                         (LDC, N-1) if SIDE = 'R' */
/*          On entry, the (m - 1) x n matrix C2 if SIDE = 'L', or the */
/*          m x (n - 1) matrix C2 if SIDE = 'R'. */

/*          On exit, rows 2:m of P*C if SIDE = 'L', or columns 2:m of C*P */
/*          if SIDE = 'R'. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the arrays C1 and C2. */
/*          LDC >= max(1,M). */

/*  WORK    (workspace) COMPLEX*16 array, dimension */
/*                      (N) if SIDE = 'L' */
/*                      (M) if SIDE = 'R' */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --v;
    c2_dim1 = *ldc;
    c2_offset = 1 + c2_dim1;
    c2 -= c2_offset;
    c1_dim1 = *ldc;
    c1_offset = 1 + c1_dim1;
    c1 -= c1_offset;
    --work;

    /* Function Body */
    if (min(*m,*n) == 0 || tau->r == 0. && tau->i == 0.) {
	return 0;
    }

    if (lsame_(side, "L", (ftnlen)1, (ftnlen)1)) {

/*        w :=  conjg( C1 + v' * C2 ) */

	zcopy_(n, &c1[c1_offset], ldc, &work[1], &c__1);
	zlacgv_(n, &work[1], &c__1);
	i__1 = *m - 1;
	zgemv_("Conjugate transpose", &i__1, n, &c_b1, &c2[c2_offset], ldc, &
		v[1], incv, &c_b1, &work[1], &c__1, (ftnlen)19);

/*        [ C1 ] := [ C1 ] - tau* [ 1 ] * w' */
/*        [ C2 ]    [ C2 ]        [ v ] */

	zlacgv_(n, &work[1], &c__1);
	z__1.r = -tau->r, z__1.i = -tau->i;
	zaxpy_(n, &z__1, &work[1], &c__1, &c1[c1_offset], ldc);
	i__1 = *m - 1;
	z__1.r = -tau->r, z__1.i = -tau->i;
	zgeru_(&i__1, n, &z__1, &v[1], incv, &work[1], &c__1, &c2[c2_offset], 
		ldc);

    } else if (lsame_(side, "R", (ftnlen)1, (ftnlen)1)) {

/*        w := C1 + C2 * v */

	zcopy_(m, &c1[c1_offset], &c__1, &work[1], &c__1);
	i__1 = *n - 1;
	zgemv_("No transpose", m, &i__1, &c_b1, &c2[c2_offset], ldc, &v[1], 
		incv, &c_b1, &work[1], &c__1, (ftnlen)12);

/*        [ C1, C2 ] := [ C1, C2 ] - tau* w * [ 1 , v'] */

	z__1.r = -tau->r, z__1.i = -tau->i;
	zaxpy_(m, &z__1, &work[1], &c__1, &c1[c1_offset], &c__1);
	i__1 = *n - 1;
	z__1.r = -tau->r, z__1.i = -tau->i;
	zgerc_(m, &i__1, &z__1, &work[1], &c__1, &v[1], incv, &c2[c2_offset], 
		ldc);
    }

    return 0;

/*     End of ZLATZM */

} /* zlatzm_ */

