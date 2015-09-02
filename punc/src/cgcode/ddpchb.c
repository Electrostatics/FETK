/* ./src_f77/ddpchb.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__4 = 4;
static integer c__1 = 1;

/* Subroutine */ int ddpchb_(integer *iounit, doublereal *aa, doublereal *bb, 
	integer *n, doublereal *cl, doublereal *cu, doublereal *cond, 
	doublereal *ereps, integer *iadapt)
{
    /* Format strings */
    static char fmt_30[] = "(\002 THESE CA EIGENVALUES YIELD NO NEW AA OR B"
	    "B\002,/,\002 REFINED CF = \002,d12.5,\002 AND CONDCA = \002,d12."
	    "5,/)";
    static char fmt_40[] = "(\002 NEW AA = \002,d12.5,\002 AND NEW BB = \002"
	    ",d12.5,/,\002 CURRENT POLYNOMIAL IS SUPERIOR; RESUME CG\002,/"
	    ",\002 CURRENT CL = \002,d12.5,\002 AND CURRENT CU = \002,d12.5,/,"
	    "\002 CURRENT CF = \002,d12.5,\002 AND CONDCA     = \002,d12.5,/)";
    static char fmt_50[] = "(\002 NEW AA = \002,d12.5,\002 AND NEW BB = \002"
	    ",d12.5,/,\002 NEW POLYNOMIAL IS SUPERIOR; RESTART CG \002,/,\002"
	    " NEW CL = \002,d12.5,\002 AND NEW CU = \002,d12.5,/,\002 NEW CF "
	    "= \002,d12.5,\002 AND CONDCA = \002,d12.5,/)";

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal), pow_di(doublereal *, integer *), pow_dd(
	    doublereal *, doublereal *), log(doublereal), cosh(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal c__, d__, g, cf, an, bn, gn, cfn, cfo, eta, tau, epz, 
	    taun, test, condn, condo;
    extern doublereal d1mach_(integer *);
    static doublereal recipn, cshinv, sqtmep;

    /* Fortran I/O blocks */
    static cilist io___12 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___21 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_50, 0 };


/* ***BEGIN PROLOGUE  DDPCHB */
/* ***REFER TO  DPPCG,DCGCHB */
/* ***ROUTINES CALLED  D1MACH */
/* ***REVISION DATE  860715   (YYMMDD) */
/* ***END PROLOGUE  DDPCHB */

/*     THIS SUBROUTINE DYNAMICALLY DETERMINES THE NEW PRECONDITIONING */
/*     POLYNOMIAL, C(A).  THIS IS DONE BY DETERMINING THE NEW INTERVAL */
/*     [AA,BB] OVER WHICH TO DEFINE THE SCALED AND TRANSLATED CHEBYSHEV */
/*     POLYNOMIAL, P(A).  ONCE WE HAVE P(A), WE DEFINE C(A)A = I-P(A). */
/*     AA AND BB ARE UPDATED VIA INFORMATION OBTAINED BY DONEST, WHICH */
/*     RETURNS EGVAL ESTIMATES FOR THE CURRENT PRECONDITIONED SYSTEM, */
/*     C(A)A.  THESE ESTIMATES ARE MAPPED TO EGVAL ESTIMATES FOR A, AND */
/*     THEN [AA,BB] IS EXPANDED IF NECESSARY.  IF THE NEW CG CONVERGENCE */
/*     FACTOR (CF) IS LARGER THAN THE CURRENT CF, THEN THE OLD POLY IS */
/*     RETAINED AND THE ITERATION RESUMED.  OTHERWISE, THE CG ITERATION */
/*     IS RESTARTED WITH THE NEW PRECONDITIONER.  (NOTE: N, THE DEGREE */
/*     OF THE CHEBYSHEV POLY, MUST BE ODD FOR THE ADAPTIVE PROCEDURE TO */
/*     WORK CORRECTLY.  IF N IS EVEN, THE ROUTINE RETURNS IMMEDIATELY.) */


/* ***FIRST EXECUTABLE STATEMENT  DDPCHB */
/* L1: */

/*     *** CHECK THAT N IS POSITIVE AND ODD *** */
    if (*n <= 0 || *n % 2 == 0) {
	*iadapt = -1;
	return 0;
    }

/*     *** COMPUTE D, C, RECIPN, SQTMEP *** */
    d__ = (*bb + *aa) * .5;
    c__ = (*bb - *aa) * .5;
    recipn = 1. / (doublereal) (*n);
    sqtmep = sqrt(d1mach_(&c__4));

/*     *** CHECK FOR SMALL C (RELATIVE TO D) *** */
    if (c__ <= d__ * sqtmep) {
/*        *** C IS SMALL *** */
	tau = pow_di(&d__, n);
	if (*cl > 1.) {
	    *cl = 1.;
	}
	if (*cu < 1.) {
	    *cu = 1.;
	}
	d__1 = (1. - *cl) * tau;
	an = d__ - pow_dd(&d__1, &recipn);
	d__1 = (*cu - 1.) * tau;
	bn = d__ + pow_dd(&d__1, &recipn);
	goto L20;
    }

/*     *** COMPUTE POLY DEVIATION FROM 1 OVER (AA,BB) *** */
    g = d__ / c__;
    tau = cosh(*n * log(g + sqrt(g * g - 1.)));

/*     *** DETERMINE NEW LEFT ENDPOINT AN *** */
    eta = (1. - *cl) * tau;
    if (eta > 1.) {
/*        *** COMPUTE NEW AA *** */
	cshinv = log(eta + sqrt(eta * eta - 1.));
	an = d__ - c__ * cosh(recipn * cshinv);
    } else {
/*        *** USE OLD AA *** */
	an = *aa;
	*cl = (tau - 1.) / tau;
    }

/*     *** DETERMINE NEW RIGHT ENDPOINT BN *** */
    eta = (*cu - 1.) * tau;
    if (eta > 1.) {
/*        *** COMPUTE NEW BB *** */
	cshinv = log(eta + sqrt(eta * eta - 1.));
	bn = d__ + c__ * cosh(recipn * cshinv);
    } else {
/*        *** USE OLD BB *** */
	bn = *bb;
	*cu = (tau + 1.) / tau;
    }

/*     *** CHECK FOR NO CHANGE IN ENDPOINTS *** */
L20:
    if (an == *aa && bn == *bb) {
/*        *** NO NEW ENDPOINTS; SET IADAPT *** */
	*iadapt = 0;
	*cond = *cu / *cl;
	cf = (sqrt(*cond) - 1.) / (sqrt(*cond) + 1.);
	if (*iounit > 0) {
	    io___12.ciunit = *iounit;
	    s_wsfe(&io___12);
	    do_fio(&c__1, (char *)&cf, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*cond), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	return 0;
    }

/*     *** NEW ENDPOINTS: COMPARE CONVERGENCE FACTORS *** */
    condo = *cu / *cl;
    gn = (bn + an) / (bn - an);
    taun = cosh(*n * log(gn + sqrt(gn * gn - 1.)));
    condn = (taun + 1.) / (taun - 1.);
    cfo = (sqrt(condo) - 1.) / (sqrt(condo) + 1.);
    cfn = (sqrt(condn) - 1.) / (sqrt(condn) + 1.);
    epz = max(*ereps,sqtmep);
    test = log(epz) * (1. / log(cfo) - 1. / log(cfn));
    if (test < 1.) {
/*        *** RESUME ITERATION WITH OLD AA,BB *** */
	*iadapt = 1;
	*cond = condo;
	cf = cfo;
	if (*iounit > 0) {
	    io___21.ciunit = *iounit;
	    s_wsfe(&io___21);
	    do_fio(&c__1, (char *)&an, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&bn, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*cl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*cu), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cf, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*cond), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    } else {
/*        *** RESTART ITERATION WITH NEW AA,BB *** */
	*iadapt = 2;
	*aa = an;
	*bb = bn;
	*cl = (taun - 1.) / taun;
	*cu = (taun + 1.) / taun;
	*cond = condn;
	cf = cfn;
	if (*iounit > 0) {
	    io___22.ciunit = *iounit;
	    s_wsfe(&io___22);
	    do_fio(&c__1, (char *)&an, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&bn, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*cl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*cu), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cf, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*cond), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }

    return 0;
} /* ddpchb_ */

