/* ./src_f77/donest.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int donest_(integer *iounit, doublereal *d__, doublereal *e, 
	doublereal *w1, doublereal *w2, integer *ind, integer *nt, doublereal 
	*eigmin, doublereal *eigmax, doublereal *cond)
{
    /* Format strings */
    static char fmt_15[] = "(/,\002 WARNING IN DONEST: SRATQR RETURNED IERR "
	    "= \002,i5,/)";
    static char fmt_50[] = "(4x,\002 MIN, MAX EIGENVALUES = \002,d12.5,\002 "
	    "AND \002,d12.5,/,4x,\002 CONDITION NUMBER     = \002,d12.5,/)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__;
    static doublereal eps1;
    static integer ierr;
    static logical type__;
    extern /* Subroutine */ int sratqr_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, logical *, integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 0, 0, fmt_15, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_15, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_50, 0 };


/* ***BEGIN PROLOGUE  DONEST */
/* ***REFER TO  DPPCG,DPCGCA */
/* ***ROUTINES CALLED  SRATQR */
/* ***REVISION DATE  860901   (YYMMDD) */
/* ***END PROLOGUE  DONEST */

/*     THIS SUBROUTINE COMPUTES THE SMALLEST AND LARGEST EIGENVALUES OF */
/*     A SYMMETRIC POSITIVE DEFINITE TRIDIAGONAL MATRIX OF ORDER NT. THE */
/*     DIAGONAL IS STORED IN THE ARRAY D AND THE SUB-DIAG IS STORED IN */
/*     THE LAST NT-1 POSITIONS OF THE ARRAY E.  EIGMIN AND EIGMAX ARE */
/*     UPDATED WITH EACH CALL TO DONEST.  ONCE THESE ARE DETERMINED, AN */
/*     ESTIMATE FOR THE CONDITION NUMBER IS COMPUTED.  THE ARRAYS D AND */
/*     E ARE UNALTERED.  TWO DBLE WORK ARRAYS (W1, W2) AND ONE INTEGER */
/*     WORK ARRAY (IND) MUST BE PASSED. */

/*     *** DECLARATIONS *** */

/* ***FIRST EXECUTABLE STATEMENT  DONEST */
    /* Parameter adjustments */
    --ind;
    --w2;
    --w1;
    --e;
    --d__;

    /* Function Body */
/* L1: */

/*     *** FIND SMALLEST EIGENVALUE *** */
    eps1 = 0.;
    type__ = TRUE_;
    i__1 = *nt;
    for (i__ = 2; i__ <= i__1; ++i__) {
/* Computing 2nd power */
	d__1 = e[i__];
	w1[i__] = d__1 * d__1;
/* L10: */
    }
    sratqr_(nt, &eps1, &d__[1], &e[1], &w1[1], &c__1, &w2[1], &ind[1], &w1[1],
	     &type__, &c__1, &ierr);
    if (ierr != 0) {
	io___5.ciunit = *iounit;
	s_wsfe(&io___5);
	do_fio(&c__1, (char *)&ierr, (ftnlen)sizeof(integer));
	e_wsfe();
    } else {
	*eigmin = min(*eigmin,w2[1]);
    }

/*     *** FIND LARGEST EIGENVALUE *** */
    eps1 = 0.;
    type__ = FALSE_;
    i__1 = *nt;
    for (i__ = 2; i__ <= i__1; ++i__) {
/* Computing 2nd power */
	d__1 = e[i__];
	w1[i__] = d__1 * d__1;
/* L20: */
    }
    sratqr_(nt, &eps1, &d__[1], &e[1], &w1[1], &c__1, &w2[1], &ind[1], &w1[1],
	     &type__, &c__1, &ierr);
    if (ierr != 0) {
	io___6.ciunit = *iounit;
	s_wsfe(&io___6);
	do_fio(&c__1, (char *)&ierr, (ftnlen)sizeof(integer));
	e_wsfe();
    } else {
	*eigmax = max(*eigmax,w2[1]);
    }

/*     *** UPDATE CONDITION NUMBER ESTIMATE *** */
/* Computing MAX */
    d__1 = 1., d__2 = *eigmax / *eigmin, d__1 = max(d__1,d__2);
    *cond = max(d__1,*cond);
    if (*iounit > 0) {
	io___7.ciunit = *iounit;
	s_wsfe(&io___7);
	do_fio(&c__1, (char *)&(*eigmin), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*eigmax), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*cond), (ftnlen)sizeof(doublereal));
	e_wsfe();
    }

    return 0;
} /* donest_ */

