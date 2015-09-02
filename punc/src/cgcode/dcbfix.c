/* ./src_f77/dcbfix.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;

/* Subroutine */ int dcbfix_(S_fp matvec, S_fp pcondl, doublereal *a, integer 
	*ia, doublereal *c__, integer *ic, integer *ipc, doublereal *aa, 
	doublereal *bb, integer *nsteps, doublereal *b, doublereal *x, 
	doublereal *r__, doublereal *dx, doublereal *work, integer *n)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static doublereal d__;
    static integer i__;
    static doublereal c2, p1, p2;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    static integer istep;
    static doublereal recipd, wdummy;

/* ***BEGIN PROLOGUE  DCBFIX */
/* ***REFER TO  DPPCG,DCGCHB */
/* ***ROUTINES CALLED  DAXPY,DCOPY,DSCAL */
/* ***REVISION DATE  870501   (YYMMDD) */
/* ***END PROLOGUE  DCBFIX */

/*     THIS SUBROUTINE PERFORMS NSTEPS STEPS OF THE CHEBYSHEV ITERATION */
/*     (BASED ON THE INTERVAL [AA,BB]) ON THE LINEAR SYSTEM AX=B.  THE */
/*     INITIAL GUESS X0 IS ASSUMED TO BE THE ZERO VECTOR.  R AND DX ARE */
/*     WORK ARRAYS OF LENGTH .GE. N.  IF PRECONDITIONING IS REQUESTED */
/*     (IPC .NE. 0), AN ADDITIONAL WORK ARRAY, WORK, MUST BE PASSED. */
/*     IN THIS CASE THE PROBLEM SOLVED IS C*AX = B. */

/*     *** DECLARATIONS *** */

/* ***FIRST EXECUTABLE STATEMENT  DCBFIX */
    /* Parameter adjustments */
    --work;
    --dx;
    --r__;
    --x;
    --b;

    /* Function Body */
/* L1: */

/*     *** CHECK FOR NSTEPS .LE. 0 *** */
    if (*nsteps <= 0) {
/*        *** RETURN X=B *** */
	dcopy_(n, &b[1], &c__1, &x[1], &c__1);
	return 0;
    }

/*     *** INITIALIZE ITERATION PARAMETERS *** */
    d__ = (*bb + *aa) * .5;
    c2 = (*bb - *aa) * .25 * (*bb - *aa);
    p1 = 2. / d__;
    p2 = 0.;

/*     *** EXECUTE STEP ONE OF THE ITERATION *** */
    recipd = 1. / d__;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dx[i__] = recipd * b[i__];
	x[i__] = dx[i__];
/* L10: */
    }

/*     *** MAIN LOOP OF THE CHEBYSHEV ITERATION *** */
    i__1 = *nsteps;
    for (istep = 2; istep <= i__1; ++istep) {

/*        *** COMPUTE MATRIX TIMES X *** */
	if (*ipc == 0) {
	    (*matvec)(&c__0, a, ia, &wdummy, &x[1], &r__[1], n);
	} else {
	    (*matvec)(&c__0, a, ia, &wdummy, &x[1], &work[1], n);
	    (*pcondl)(&c__0, c__, ic, &wdummy, &work[1], &r__[1], n);
	}

/*        *** COMPUTE NEW DX AND X *** */
	p2 = c2 * p1 / (d__ * 4. - c2 * p1);
	p1 = (p2 + 1.) / d__;
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    dx[i__] = p2 * dx[i__] + p1 * (b[i__] - r__[i__]);
	    x[i__] += dx[i__];
/* L30: */
	}

/* L40: */
    }

    return 0;
} /* dcbfix_ */

