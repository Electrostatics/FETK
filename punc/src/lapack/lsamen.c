/* ./src_f77/lsamen.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

logical lsamen_(integer *n, char *ca, char *cb, ftnlen ca_len, ftnlen cb_len)
{
    /* System generated locals */
    integer i__1;
    logical ret_val;

    /* Builtin functions */
    integer i_len(char *, ftnlen);

    /* Local variables */
    static integer i__;
    extern logical lsame_(char *, char *, ftnlen, ftnlen);


/*  -- LAPACK auxiliary routine (version 3.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     September 30, 1994 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  LSAMEN  tests if the first N letters of CA are the same as the */
/*  first N letters of CB, regardless of case. */
/*  LSAMEN returns .TRUE. if CA and CB are equivalent except for case */
/*  and .FALSE. otherwise.  LSAMEN also returns .FALSE. if LEN( CA ) */
/*  or LEN( CB ) is less than N. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The number of characters in CA and CB to be compared. */

/*  CA      (input) CHARACTER*(*) */
/*  CB      (input) CHARACTER*(*) */
/*          CA and CB specify two character strings of length at least N. */
/*          Only the first N characters of each string will be accessed. */

/* ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    ret_val = FALSE_;
    if (i_len(ca, ca_len) < *n || i_len(cb, cb_len) < *n) {
	goto L20;
    }

/*     Do for each character in the two strings. */

    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {

/*        Test if the characters are equal using LSAME. */

	if (! lsame_(ca + (i__ - 1), cb + (i__ - 1), (ftnlen)1, (ftnlen)1)) {
	    goto L20;
	}

/* L10: */
    }
    ret_val = TRUE_;

L20:
    return ret_val;

/*     End of LSAMEN */

} /* lsamen_ */

