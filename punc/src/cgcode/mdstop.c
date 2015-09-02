/* ./src_f77/mdstop.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;

integer mdstop_(integer *istop, integer *iters, integer *itmax, doublereal *
	errtol, doublereal *stptst, integer *ierror, doublereal *r__, 
	doublereal *s, doublereal *z__, integer *n, doublereal *rnorm, 
	doublereal *snorm, doublereal *znorm, doublereal *denom, doublereal *
	conda, integer *ido)
{
    /* System generated locals */
    integer ret_val;

    /* Local variables */
    extern doublereal dnrm2_(integer *, doublereal *, integer *);

/* ***BEGIN PROLOGUE  MDSTOP */
/* ***REFER TO  DCGDRV */
/* ***ROUTINES CALLED */
/* ***REVISION DATE  900210   (YYMMDD) */
/* ***END PROLOGUE  MDSTOP */

/*     STOPPING CRITERION MENU */
/*        ISTOP = 0  ||E||/||E0||      <= ERRTOL  (DEFAULT) */
/*        ISTOP = 1  ||R||             <= ERRTOL */
/*        ISTOP = 2  ||R||/||B||       <= ERRTOL */
/*        ISTOP = 3  ||C*R||           <= ERRTOL */
/*        ISTOP = 4  ||C*R||/||C*B||   <= ERRTOL */
/*     WHERE E=ERROR, R=RESIDUAL, B=RIGHT HAND SIDE OF A*X=B, */
/*     AND C IS THE PRECONDITIONING MATRIX OR PRECONDITIONING */
/*     POLYNOMIAL (OR BOTH.) */
/*     NOTE: IF ISTOP=0 IS SELECTED BY THE USER, THEN ERRTOL */
/*     IS THE AMOUNT BY WHICH THE INITIAL ERROR IS TO BE */
/*     REDUCED.  BY ESTIMATING THE CONDITION NUMBER OF THE */
/*     ITERATION MATRIX, THE CODE ATTEMPTS TO GUARANTEE THAT */
/*     THE FINAL RELATIVE ERROR IS .LE. ERRTOL.  SEE THE LONG */
/*     DEDCRIPTION OF DCGDRV FOR DETAILS. */

/*     NOTE:  ISTOP,ITERS,ITMAX,ERRTOL,STPTST,IERROR ARE AS DEDCRIBED */
/*               IN THE DOCUMENTATION OF DCGDRV. */
/*            R,S,Z ARE RESIDUAL VECTORS. */
/*            N IS THE LENGTH OF R,S,Z. */
/*            RNORM,SNORM,ZNORM ARE THE NORMS OF R,S,Z IF THE ROUTINE */
/*               HAS HAD TO COMPUTE THEM IN ITS ALGORITHM ALREADY. */
/*            DENOM IS THE APPROPRIATE DENOMINATOR FOR THE STOPPING */
/*               CRITERION STPTST IF ISTOP=0,2,4 IS SELECTED. */
/*            CONDA IS THE CONDITION ESTIMATE IF ISTOP=0 IS SELECTED. */
/*            IDO IS A FLAG TO DETERMINE IF ONE OF RNORM,SNORM, OR */
/*               ZNORM HAS BEEN COMPUTED OR STILL NEEDS TO BE COMPUTED. */

/*     NOTE:  THE FLAG ISTOP IS INTERPRETED AS: */
/*            IF (ISTOP .EQ. 0) MDSTOP = DNRM2(N,Z,1)*CONDA/DENOM */
/*            IF (ISTOP .EQ. 1) MDSTOP = DNRM2(N,R,1) */
/*            IF (ISTOP .EQ. 2) MDSTOP = DNRM2(N,R,1)/DENOM */
/*            IF (ISTOP .EQ. 3) MDSTOP = DNRM2(N,S,1) */
/*            IF (ISTOP .EQ. 4) MDSTOP = DNRM2(N,S,1)/DENOM */

/*     NOTE:  THE FLAG IDO IS INTERPRETED AS: */
/*            IF (IDO .EQ. 1) THEN THE CALLING ROUTINE HAS ALREADY */
/*               COMPUTED THE APPROPRIATE NUMERATOR QUANTITY, AND IT'S */
/*               VALUE IS CONTAINED IN THE PARAMETER DETERMINED BY ISTOP; */
/*               EITHER RNORM,SNORM, OR ZNORM. */
/*            IF (IDO .EQ. 0) THEN THE CALLING ROUTINE REQUESTS THAT */
/*               ROUTINE MDSTOP COMPUTE THE APPROPRIATE QUANTITY, */
/*               FROM ONE OF R,S, OR Z. */

/*     *** DECLARATIONS *** */

/* ***FIRST EXECUTABLE STATEMENT  MDSTOP */
    /* Parameter adjustments */
    --z__;
    --s;
    --r__;

    /* Function Body */
/* L1: */

/*     *** COMPUTE STPTST *** */
    if (*ido == 0) {
	if (*istop == 0) {
	    *znorm = dnrm2_(n, &z__[1], &c__1);
	}
	if (*istop == 1 || *istop == 2) {
	    *rnorm = dnrm2_(n, &r__[1], &c__1);
	}
	if (*istop == 3 || *istop == 4) {
	    *snorm = dnrm2_(n, &s[1], &c__1);
	}
    }
    if (*istop == 0) {
	*stptst = *znorm * *conda / *denom;
    }
    if (*istop == 1) {
	*stptst = *rnorm;
    }
    if (*istop == 2) {
	*stptst = *rnorm / *denom;
    }
    if (*istop == 3) {
	*stptst = *snorm;
    }
    if (*istop == 4) {
	*stptst = *snorm / *denom;
    }

/*     *** CHECK THE STOPPING CRITERION *** */
    ret_val = 0;
    if (*stptst <= *errtol) {
	ret_val = 1;
	return ret_val;
    }
    if (*iters >= *itmax) {
	*ierror = -1000;
	ret_val = 1;
	return ret_val;
    }

    return ret_val;
} /* mdstop_ */

