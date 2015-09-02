/* ./src_f77/sdpchb.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__4 = 4;
static integer c__1 = 1;

/* Subroutine */ int sdpchb_(integer *iounit, real *aa, real *bb, integer *n, 
	real *cl, real *cu, real *cond, real *ereps, integer *iadapt)
{
    /* Format strings */
    static char fmt_30[] = "(\002 THESE CA EIGENVALUES YIELD NO NEW AA OR B"
	    "B\002,/,\002 REFINED CF = \002,e12.5,\002 AND CONDCA = \002,e12."
	    "5,/)";
    static char fmt_40[] = "(\002 NEW AA = \002,e12.5,\002 AND NEW BB = \002"
	    ",e12.5,/,\002 CURRENT POLYNOMIAL IS SUPERIOR; RESUME CG\002,/"
	    ",\002 CURRENT CL = \002,e12.5,\002 AND CURRENT CU = \002,e12.5,/,"
	    "\002 CURRENT CF = \002,e12.5,\002 AND CONDCA     = \002,e12.5,/)";
    static char fmt_50[] = "(\002 NEW AA = \002,e12.5,\002 AND NEW BB = \002"
	    ",e12.5,/,\002 NEW POLYNOMIAL IS SUPERIOR; RESTART CG \002,/,\002"
	    " NEW CL = \002,e12.5,\002 AND NEW CU = \002,e12.5,/,\002 NEW CF "
	    "= \002,e12.5,\002 AND CONDCA = \002,e12.5,/)";

    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal), pow_ri(real *, integer *), pow_dd(doublereal *, 
	    doublereal *), log(doublereal), cosh(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static real c__, d__, g, cf, an, bn, gn, cfn, cfo, eta, tau, epz, taun, 
	    test, condn, condo;
    extern doublereal r1mach_(integer *);
    static real recipn, cshinv, sqtmep;

    /* Fortran I/O blocks */
    static cilist io___12 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___21 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_50, 0 };


/* ***BEGIN PROLOGUE  SDPCHB */
/* ***REFER TO  SPPCG,SCGCHB */
/* ***ROUTINES CALLED  R1MACH */
/* ***REVISION DATE  860715   (YYMMDD) */
/* ***END PROLOGUE  SDPCHB */

/*     THIS SUBROUTINE DYNAMICALLY DETERMINES THE NEW PRECONDITIONING */
/*     POLYNOMIAL, C(A).  THIS IS DONE BY DETERMINING THE NEW INTERVAL */
/*     [AA,BB] OVER WHICH TO DEFINE THE SCALED AND TRANSLATED CHEBYSHEV */
/*     POLYNOMIAL, P(A).  ONCE WE HAVE P(A), WE DEFINE C(A)A = I-P(A). */
/*     AA AND BB ARE UPDATED VIA INFORMATION OBTAINED BY SONEST, WHICH */
/*     RETURNS EGVAL ESTIMATES FOR THE CURRENT PRECONDITIONED SYSTEM, */
/*     C(A)A.  THESE ESTIMATES ARE MAPPED TO EGVAL ESTIMATES FOR A, AND */
/*     THEN [AA,BB] IS EXPANDED IF NECESSARY.  IF THE NEW CG CONVERGENCE */
/*     FACTOR (CF) IS LARGER THAN THE CURRENT CF, THEN THE OLD POLY IS */
/*     RETAINED AND THE ITERATION RESUMED.  OTHERWISE, THE CG ITERATION */
/*     IS RESTARTED WITH THE NEW PRECONDITIONER.  (NOTE: N, THE DEGREE */
/*     OF THE CHEBYSHEV POLY, MUST BE ODD FOR THE ADAPTIVE PROCEDURE TO */
/*     WORK CORRECTLY.  IF N IS EVEN, THE ROUTINE RETURNS IMMEDIATELY.) */

/* CCCCCIMPLICIT  DOUBLE PRECISION(A-H,O-Z) */

/* ***FIRST EXECUTABLE STATEMENT  SDPCHB */
/* L1: */

/*     *** CHECK THAT N IS POSITIVE AND ODD *** */
    if (*n <= 0 || *n % 2 == 0) {
	*iadapt = -1;
	return 0;
    }

/*     *** COMPUTE D, C, RECIPN, SQTMEP *** */
    d__ = (*bb + *aa) * .5;
    c__ = (*bb - *aa) * .5;
    recipn = 1.f / (real) (*n);
    sqtmep = sqrt(r1mach_(&c__4));

/*     *** CHECK FOR SMALL C (RELATIVE TO D) *** */
    if (c__ <= d__ * sqtmep) {
/*        *** C IS SMALL *** */
	tau = pow_ri(&d__, n);
	if (*cl > 1.f) {
	    *cl = 1.f;
	}
	if (*cu < 1.f) {
	    *cu = 1.f;
	}
	d__1 = (doublereal) ((1.f - *cl) * tau);
	d__2 = (doublereal) recipn;
	an = d__ - pow_dd(&d__1, &d__2);
	d__1 = (doublereal) ((*cu - 1.f) * tau);
	d__2 = (doublereal) recipn;
	bn = d__ + pow_dd(&d__1, &d__2);
	goto L20;
    }

/*     *** COMPUTE POLY DEVIATION FROM 1 OVER (AA,BB) *** */
    g = d__ / c__;
    tau = cosh(*n * log(g + sqrt(g * g - 1.f)));

/*     *** DETERMINE NEW LEFT ENDPOINT AN *** */
    eta = (1.f - *cl) * tau;
    if (eta > 1.f) {
/*        *** COMPUTE NEW AA *** */
	cshinv = log(eta + sqrt(eta * eta - 1.f));
	an = d__ - c__ * cosh(recipn * cshinv);
    } else {
/*        *** USE OLD AA *** */
	an = *aa;
	*cl = (tau - 1.f) / tau;
    }

/*     *** DETERMINE NEW RIGHT ENDPOINT BN *** */
    eta = (*cu - 1.f) * tau;
    if (eta > 1.f) {
/*        *** COMPUTE NEW BB *** */
	cshinv = log(eta + sqrt(eta * eta - 1.f));
	bn = d__ + c__ * cosh(recipn * cshinv);
    } else {
/*        *** USE OLD BB *** */
	bn = *bb;
	*cu = (tau + 1.f) / tau;
    }

/*     *** CHECK FOR NO CHANGE IN ENDPOINTS *** */
L20:
    if (an == *aa && bn == *bb) {
/*        *** NO NEW ENDPOINTS; SET IADAPT *** */
	*iadapt = 0;
	*cond = *cu / *cl;
	cf = (sqrt(*cond) - 1.f) / (sqrt(*cond) + 1.f);
	if (*iounit > 0) {
	    io___12.ciunit = *iounit;
	    s_wsfe(&io___12);
	    do_fio(&c__1, (char *)&cf, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*cond), (ftnlen)sizeof(real));
	    e_wsfe();
	}
	return 0;
    }

/*     *** NEW ENDPOINTS: COMPARE CONVERGENCE FACTORS *** */
    condo = *cu / *cl;
    gn = (bn + an) / (bn - an);
    taun = cosh(*n * log(gn + sqrt(gn * gn - 1.f)));
    condn = (taun + 1.f) / (taun - 1.f);
    cfo = (sqrt(condo) - 1.f) / (sqrt(condo) + 1.f);
    cfn = (sqrt(condn) - 1.f) / (sqrt(condn) + 1.f);
    epz = dmax(*ereps,sqtmep);
    test = log(epz) * (1.f / log(cfo) - 1.f / log(cfn));
    if (test < 1.f) {
/*        *** RESUME ITERATION WITH OLD AA,BB *** */
	*iadapt = 1;
	*cond = condo;
	cf = cfo;
	if (*iounit > 0) {
	    io___21.ciunit = *iounit;
	    s_wsfe(&io___21);
	    do_fio(&c__1, (char *)&an, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&bn, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*cl), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*cu), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&cf, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*cond), (ftnlen)sizeof(real));
	    e_wsfe();
	}
    } else {
/*        *** RESTART ITERATION WITH NEW AA,BB *** */
	*iadapt = 2;
	*aa = an;
	*bb = bn;
	*cl = (taun - 1.f) / taun;
	*cu = (taun + 1.f) / taun;
	*cond = condn;
	cf = cfn;
	if (*iounit > 0) {
	    io___22.ciunit = *iounit;
	    s_wsfe(&io___22);
	    do_fio(&c__1, (char *)&an, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&bn, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*cl), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*cu), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&cf, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*cond), (ftnlen)sizeof(real));
	    e_wsfe();
	}
    }

    return 0;
} /* sdpchb_ */

