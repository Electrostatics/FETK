/* ./src_f77/clarzb.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static realcomplex c_b1 = {1.f,0.f};
static integer c__1 = 1;

/* Subroutine */ int clarzb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, integer *l, realcomplex *v, 
	integer *ldv, realcomplex *t, integer *ldt, realcomplex *c__, integer *ldc, 
	realcomplex *work, integer *ldwork, ftnlen side_len, ftnlen trans_len, 
	ftnlen direct_len, ftnlen storev_len)
{
    /* System generated locals */
    integer c_dim1, c_offset, t_dim1, t_offset, v_dim1, v_offset, work_dim1, 
	    work_offset, i__1, i__2, i__3, i__4, i__5;
    realcomplex q__1;

    /* Local variables */
    static integer i__, j, info;
    extern /* Subroutine */ int cgemm_(char *, char *, integer *, integer *, 
	    integer *, realcomplex *, realcomplex *, integer *, realcomplex *, integer *, 
	    realcomplex *, realcomplex *, integer *, ftnlen, ftnlen);
    extern logical lsame_(char *, char *, ftnlen, ftnlen);
    extern /* Subroutine */ int ccopy_(integer *, realcomplex *, integer *, 
	    realcomplex *, integer *), ctrmm_(char *, char *, char *, char *, 
	    integer *, integer *, realcomplex *, realcomplex *, integer *, realcomplex *, 
	    integer *, ftnlen, ftnlen, ftnlen, ftnlen), clacgv_(integer *, 
	    realcomplex *, integer *), xerbla_(char *, integer *, ftnlen);
    static char transt[1];


/*  -- LAPACK routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     December 1, 1999 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  CLARZB applies a complex block reflector H or its transpose H**H */
/*  to a complex distributed M-by-N  C from the left or the right. */

/*  Currently, only STOREV = 'R' and DIRECT = 'B' are supported. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': apply H or H' from the Left */
/*          = 'R': apply H or H' from the Right */

/*  TRANS   (input) CHARACTER*1 */
/*          = 'N': apply H (No transpose) */
/*          = 'C': apply H' (Conjugate transpose) */

/*  DIRECT  (input) CHARACTER*1 */
/*          Indicates how H is formed from a product of elementary */
/*          reflectors */
/*          = 'F': H = H(1) H(2) . . . H(k) (Forward, not supported yet) */
/*          = 'B': H = H(k) . . . H(2) H(1) (Backward) */

/*  STOREV  (input) CHARACTER*1 */
/*          Indicates how the vectors which define the elementary */
/*          reflectors are stored: */
/*          = 'C': Columnwise                        (not supported yet) */
/*          = 'R': Rowwise */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. */

/*  K       (input) INTEGER */
/*          The order of the matrix T (= the number of elementary */
/*          reflectors whose product defines the block reflector). */

/*  L       (input) INTEGER */
/*          The number of columns of the matrix V containing the */
/*          meaningful part of the Householder reflectors. */
/*          If SIDE = 'L', M >= L >= 0, if SIDE = 'R', N >= L >= 0. */

/*  V       (input) COMPLEX array, dimension (LDV,NV). */
/*          If STOREV = 'C', NV = K; if STOREV = 'R', NV = L. */

/*  LDV     (input) INTEGER */
/*          The leading dimension of the array V. */
/*          If STOREV = 'C', LDV >= L; if STOREV = 'R', LDV >= K. */

/*  T       (input) COMPLEX array, dimension (LDT,K) */
/*          The triangular K-by-K matrix T in the representation of the */
/*          block reflector. */

/*  LDT     (input) INTEGER */
/*          The leading dimension of the array T. LDT >= K. */

/*  C       (input/output) COMPLEX array, dimension (LDC,N) */
/*          On entry, the M-by-N matrix C. */
/*          On exit, C is overwritten by H*C or H'*C or C*H or C*H'. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace) COMPLEX array, dimension (LDWORK,K) */

/*  LDWORK  (input) INTEGER */
/*          The leading dimension of the array WORK. */
/*          If SIDE = 'L', LDWORK >= max(1,N); */
/*          if SIDE = 'R', LDWORK >= max(1,M). */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA */

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

/*     Quick return if possible */

    /* Parameter adjustments */
    v_dim1 = *ldv;
    v_offset = 1 + v_dim1;
    v -= v_offset;
    t_dim1 = *ldt;
    t_offset = 1 + t_dim1;
    t -= t_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    work_dim1 = *ldwork;
    work_offset = 1 + work_dim1;
    work -= work_offset;

    /* Function Body */
    if (*m <= 0 || *n <= 0) {
	return 0;
    }

/*     Check for currently supported options */

    info = 0;
    if (! lsame_(direct, "B", (ftnlen)1, (ftnlen)1)) {
	info = -3;
    } else if (! lsame_(storev, "R", (ftnlen)1, (ftnlen)1)) {
	info = -4;
    }
    if (info != 0) {
	i__1 = -info;
	xerbla_("CLARZB", &i__1, (ftnlen)6);
	return 0;
    }

    if (lsame_(trans, "N", (ftnlen)1, (ftnlen)1)) {
	*(unsigned char *)transt = 'C';
    } else {
	*(unsigned char *)transt = 'N';
    }

    if (lsame_(side, "L", (ftnlen)1, (ftnlen)1)) {

/*        Form  H * C  or  H' * C */

/*        W( 1:n, 1:k ) = conjg( C( 1:k, 1:n )' ) */

	i__1 = *k;
	for (j = 1; j <= i__1; ++j) {
	    ccopy_(n, &c__[j + c_dim1], ldc, &work[j * work_dim1 + 1], &c__1);
/* L10: */
	}

/*        W( 1:n, 1:k ) = W( 1:n, 1:k ) + ... */
/*                        conjg( C( m-l+1:m, 1:n )' ) * V( 1:k, 1:l )' */

	if (*l > 0) {
	    cgemm_("Transpose", "Conjugate transpose", n, k, l, &c_b1, &c__[*
		    m - *l + 1 + c_dim1], ldc, &v[v_offset], ldv, &c_b1, &
		    work[work_offset], ldwork, (ftnlen)9, (ftnlen)19);
	}

/*        W( 1:n, 1:k ) = W( 1:n, 1:k ) * T'  or  W( 1:m, 1:k ) * T */

	ctrmm_("Right", "Lower", transt, "Non-unit", n, k, &c_b1, &t[t_offset]
		, ldt, &work[work_offset], ldwork, (ftnlen)5, (ftnlen)5, (
		ftnlen)1, (ftnlen)8);

/*        C( 1:k, 1:n ) = C( 1:k, 1:n ) - conjg( W( 1:n, 1:k )' ) */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *k;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = i__ + j * c_dim1;
		i__4 = i__ + j * c_dim1;
		i__5 = j + i__ * work_dim1;
		q__1.r = c__[i__4].r - work[i__5].r, q__1.i = c__[i__4].i - 
			work[i__5].i;
		c__[i__3].r = q__1.r, c__[i__3].i = q__1.i;
/* L20: */
	    }
/* L30: */
	}

/*        C( m-l+1:m, 1:n ) = C( m-l+1:m, 1:n ) - ... */
/*                    conjg( V( 1:k, 1:l )' ) * conjg( W( 1:n, 1:k )' ) */

	if (*l > 0) {
	    q__1.r = -1.f, q__1.i = -0.f;
	    cgemm_("Transpose", "Transpose", l, n, k, &q__1, &v[v_offset], 
		    ldv, &work[work_offset], ldwork, &c_b1, &c__[*m - *l + 1 
		    + c_dim1], ldc, (ftnlen)9, (ftnlen)9);
	}

    } else if (lsame_(side, "R", (ftnlen)1, (ftnlen)1)) {

/*        Form  C * H  or  C * H' */

/*        W( 1:m, 1:k ) = C( 1:m, 1:k ) */

	i__1 = *k;
	for (j = 1; j <= i__1; ++j) {
	    ccopy_(m, &c__[j * c_dim1 + 1], &c__1, &work[j * work_dim1 + 1], &
		    c__1);
/* L40: */
	}

/*        W( 1:m, 1:k ) = W( 1:m, 1:k ) + ... */
/*                        C( 1:m, n-l+1:n ) * conjg( V( 1:k, 1:l )' ) */

	if (*l > 0) {
	    cgemm_("No transpose", "Transpose", m, k, l, &c_b1, &c__[(*n - *l 
		    + 1) * c_dim1 + 1], ldc, &v[v_offset], ldv, &c_b1, &work[
		    work_offset], ldwork, (ftnlen)12, (ftnlen)9);
	}

/*        W( 1:m, 1:k ) = W( 1:m, 1:k ) * conjg( T )  or */
/*                        W( 1:m, 1:k ) * conjg( T' ) */

	i__1 = *k;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *k - j + 1;
	    clacgv_(&i__2, &t[j + j * t_dim1], &c__1);
/* L50: */
	}
	ctrmm_("Right", "Lower", trans, "Non-unit", m, k, &c_b1, &t[t_offset],
		 ldt, &work[work_offset], ldwork, (ftnlen)5, (ftnlen)5, (
		ftnlen)1, (ftnlen)8);
	i__1 = *k;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *k - j + 1;
	    clacgv_(&i__2, &t[j + j * t_dim1], &c__1);
/* L60: */
	}

/*        C( 1:m, 1:k ) = C( 1:m, 1:k ) - W( 1:m, 1:k ) */

	i__1 = *k;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = i__ + j * c_dim1;
		i__4 = i__ + j * c_dim1;
		i__5 = i__ + j * work_dim1;
		q__1.r = c__[i__4].r - work[i__5].r, q__1.i = c__[i__4].i - 
			work[i__5].i;
		c__[i__3].r = q__1.r, c__[i__3].i = q__1.i;
/* L70: */
	    }
/* L80: */
	}

/*        C( 1:m, n-l+1:n ) = C( 1:m, n-l+1:n ) - ... */
/*                            W( 1:m, 1:k ) * conjg( V( 1:k, 1:l ) ) */

	i__1 = *l;
	for (j = 1; j <= i__1; ++j) {
	    clacgv_(k, &v[j * v_dim1 + 1], &c__1);
/* L90: */
	}
	if (*l > 0) {
	    q__1.r = -1.f, q__1.i = -0.f;
	    cgemm_("No transpose", "No transpose", m, l, k, &q__1, &work[
		    work_offset], ldwork, &v[v_offset], ldv, &c_b1, &c__[(*n 
		    - *l + 1) * c_dim1 + 1], ldc, (ftnlen)12, (ftnlen)12);
	}
	i__1 = *l;
	for (j = 1; j <= i__1; ++j) {
	    clacgv_(k, &v[j * v_dim1 + 1], &c__1);
/* L100: */
	}

    }

    return 0;

/*     End of CLARZB */

} /* clarzb_ */

