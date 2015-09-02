/* ./src_f77/dcrind.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__4 = 4;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__0 = 0;

/* Subroutine */ int dcrind_(S_fp matvec, doublereal *a, integer *ia, 
	doublereal *x, doublereal *b, integer *n, integer *iparam, doublereal 
	*rparam, integer *iwork, doublereal *r__, doublereal *aap, doublereal 
	*ap, doublereal *pold, doublereal *apold, doublereal *d__, doublereal 
	*e, doublereal *cndwk, integer *ierror)
{
    /* Format strings */
    static char fmt_6[] = "(\002 THE METHOD IS CONJUGATE RESIDUALS (CRIND"
	    ")\002,/)";
    static char fmt_8[] = "(4x,\002CONDA  = \002,d12.5,/)";
    static char fmt_10[] = "(\002 RESID  = 2-NORM OF R\002,/,\002 RELRSD = R"
	    "ESID / INITIAL RESID\002,/,\002 COND(A) USED IN STOPPING CRITERI"
	    "ON\002,/)";
    static char fmt_25[] = "(\002 INITIAL RESIDUAL = \002,d12.5,/)";
    static char fmt_35[] = "(\002 ITERS = \002,i5,4x,\002RESID = \002,d12.5,"
	    "4x,\002RELRSD = \002,d12.5)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static integer i__, nce, ido;
    static doublereal beta, coef;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static integer kmax;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    static doublereal gamma, conda, alpha, sigma, denom;
    static integer itmax;
    static doublereal rdumm, sdumm;
    static integer iters;
    static doublereal tempp, zdumm;
    static integer istop;
    extern doublereal d1mach_(integer *);
    static integer jstop;
    static doublereal rnorm, r0norm;
    extern /* Subroutine */ int dcgchk_(integer *, doublereal *, integer *);
    static doublereal alfold, denold;
    static integer icycle;
    static doublereal eigmin, eigmax, dennew, epslon;
    extern integer mdstop_(integer *, integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, integer *);
    static integer iounit;
    static doublereal errtol, wdummy, stptst;

    /* Fortran I/O blocks */
    static cilist io___10 = { 0, 0, 0, fmt_6, 0 };
    static cilist io___11 = { 0, 0, 0, fmt_8, 0 };
    static cilist io___12 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___21 = { 0, 0, 0, fmt_25, 0 };
    static cilist io___32 = { 0, 0, 0, fmt_35, 0 };


/* ***BEGIN PROLOGUE  DCRIND */
/* ***DATE WRITTEN   870715   (YYMMDD) */
/* ***REVISION DATE  900210   (YYMMDD) */
/* ***CATEGORY NO. D2B4 */
/* ***KEYWORDS  LINEAR SYSTEM,SPARSE,SYMMETRIC,INDEFINITE,ITERATIVE, */
/*             CONJUGATE GRADIENTS,CONJUGATE RESIDUALS,ODIR,OMIN */
/* ***AUTHOR  ASHBY,STEVEN F., (UIUC) */
/*             UNIV. OF ILLINOIS */
/*             DEPT. OF COMPUTER SCIENCE */
/*             URBANA, IL 61801 */
/* ***AUTHOR  HOLST,MICHAEL J., (UIUC) */
/*             UNIV. OF ILLINOIS */
/*             DEPT. OF COMPUTER SCIENCE */
/*             URBANA, IL 61801 */
/*           MANTEUFFEL,THOMAS A., (LANL) */
/*             LOS ALAMOS NATIONAL LABORATORY */
/*             MAIL STOP B265 */
/*             LOS ALAMOS, NM 87545 */
/* ***PURPOSE  THIS SUBROUTINE SOLVES THE SYMMETRIC (POSSIBLY INDEFINITE) */
/*            LINEAR SYSTEM AX=B.  THE METHOD OF CONJUGATE RESIDUALS IS */
/*            USED WITH A HYBRID ODIR/OMIN IMPLEMENTATION. */
/* ***DEDCRIPTION */

/* --- ON ENTRY --- */

/*    MATVEC   EXTERNAL SUBROUTINE MATVEC(JOB,A,IA,W,X,Y,N) */
/*             THE USER MUST PROVIDE A SUBROUTINE HAVING THE SPECIFED */
/*             PARAMETER LIST.  THE SUBROUTINE MUST RETURN THE PRODUCT */
/*             (OR A RELATED COMPUTATION; SEE BELOW) Y=A*X, WHERE A IS */
/*             THE COEFFICIENT MATRIX OF THE LINEAR SYSTEM.  THE MATRIX */
/*             A IS REPRESENTED BY THE WORK ARRAYS A AND IA, DEDCRIBED */
/*             BELOW.  THE INTEGER PARAMETER JOB SPECIFIES THE PRODUCT */
/*             TO BE COMPUTED: */
/*                  JOB=0    Y=A*X */
/*                  JOB=1    Y=AT*X */
/*                  JOB=2    Y=W - A*X */
/*                  JOB=3    Y=W - AT*X. */
/*             IN THE ABOVE, AT DENOTES A-TRANSPOSE.  NOTE THAT */
/*             ONLY THE VALUES OF JOB=0,1 ARE REQUIRED FOR CGCODE. */
/*             ALL OF THE ROUTINES IN CGCODE REQUIRE JOB=0; THE */
/*             ROUTINES DCGNR, DCGNE, DPCGNR, AND DPCGNE ALSO REQUIRE */
/*             THE VALUE OF JOB=1.  (THE VALUES OF JOB=2,3 ARE NOT */
/*             REQUIRED BY ANY OF THE ROUTINES IN CGCODE, BUT MAY BE */
/*             REQUIRED BY OTHER ITERATIVE PACKAGES CONFORMING TO THE */
/*             PROPOSED ITERATIVE STANDARD.)  THE PARAMETERS W,X,Y ARE */
/*             ALL VECTORS OF LENGTH N.  THE ONLY PARAMETER THAT MAY BE */
/*             CHANGED INSIDE THE ROUTINE IS Y.  MATVEC WILL USUALLY */
/*             SERVE AS AN INTERFACE TO THE USER'S OWN MATRIX-VECTOR */
/*             MULTIPLY SUBROUTINE. */
/*             NOTE: MATVEC MUST BE DECLARED IN AN EXTERNAL STATEMENT */
/*             IN THE CALLING PROGRAM. */

/*    A        DBLE ARRAY ADDRESS. */
/*             THE BASE ADDRESS OF THE USER'S DBLE WORK ARRAY, USUALLY */
/*             THE MATRIX A.  SINCE A IS ONLY ACCESSED BY CALLS TO SUBR */
/*             MATVEC, IT MAY BE A DUMMY ADDRESS. */

/*    IA       INTEGER ARRAY ADDRESS. */
/*             THE BASE ADDRESS OF THE USER'S INTEGER WORK ARRAY.  THIS */
/*             USUALLY CONTAINS ADDITIONAL INFORMATION ABOUT A NEEDED BY */
/*             MATVEC.  SINCE IA IS ONLY ACCESSED BY CALLS TO MATVEC, IT */
/*             MAY BE A DUMMY ADDRESS. */

/*    X        DBLE(N). */
/*             THE INITIAL GUESS VECTOR, X0. */
/*             (ON EXIT, X IS OVERWRITTEN WITH THE APPROXIMATE SOLUTION */
/*             OF A*X=B.) */

/*    B        DBLE(N). */
/*             THE RIGHT-HAND SIDE VECTOR OF THE LINEAR SYSTEM AX=B. */
/*             NOTE: B IS CHANGED BY THE SOLVER. */

/*    N        INTEGER. */
/*             THE ORDER OF THE MATRIX A IN THE LINEAR SYSTEM AX=B. */

/*    IPARAM   INTEGER(40). */
/*             AN ARRAY OF INTEGER INPUT PARAMETERS: */
/*                NOTE: IPARAM(1) THROUGH IPARAM(10) ARE MANDATED BY THE */
/*                PROPOSED STANDARD; IPARAM(11) THROUGH IPARAM(30) ARE */
/*                RESERVED FOR EXPANSION OF THE PROPOSED STANDARD; */
/*                IPARAM(31) THROUGH IPARAM(34) ARE ADDITIONAL */
/*                PARAMETERS, SPECIFIC TO CGCODE. */

/*             IPARAM(1) = NIPAR */
/*             LENGTH OF THE IPARAM ARRAY. */

/*             IPARAM(2) = NRPAR */
/*             LENGTH OF THE RPARAM ARRAY. */

/*             IPARAM(3) = NIWK */
/*             LENGTH OF THE IWORK ARRAY. */

/*             IPARAM(4) = NRWK */
/*             LENGTH OF THE RWORK ARRAY. */

/*             IPARAM(5) = IOUNIT */
/*             IF (IOUNIT > 0) THEN ITERATION INFORMATION (AS */
/*             SPECIFIED BY IOLEVL; SEE BELOW) IS SENT TO UNIT=IOUNIT, */
/*             WHICH MUST BE OPENED IN THE CALLING PROGRAM. */
/*             IF (IOUNIT <= 0) THEN THERE IS NO OUTPUT. */

/*             IPARAM(6) = IOLEVL */
/*             SPECIFIES THE AMOUNT AND TYPE OF INFORMATION TO BE */
/*             OUTPUT IF (IOUNIT > 0): */
/*                IOLEVL = 0   OUTPUT ERROR MESSAGES ONLY */
/*                IOLEVL = 1   OUTPUT INPUT PARAMETERS AND LEVEL 0 INFO */
/*                IOLEVL = 2   OUTPUT STPTST (SEE BELOW) AND LEVEL 1 INFO */
/*                IOLEVL = 3   OUTPUT LEVEL 2 INFO AND MORE DETAILS */

/*             IPARAM(8) = ISTOP */
/*             STOPPING CRITERION FLAG, INTERPRETED AS: */
/*                ISTOP = 0  ||E||/||E0||      <= ERRTOL  (DEFAULT) */
/*                ISTOP = 1  ||R||             <= ERRTOL */
/*                ISTOP = 2  ||R||/||B||       <= ERRTOL */
/*                ISTOP = 3  ||C*R||           <= ERRTOL */
/*                ISTOP = 4  ||C*R||/||C*B||   <= ERRTOL */
/*             WHERE E=ERROR, R=RESIDUAL, B=RIGHT HAND SIDE OF A*X=B, */
/*             AND C IS THE PRECONDITIONING MATRIX OR PRECONDITIONING */
/*             POLYNOMIAL (OR BOTH.) */
/*             NOTE: IF ISTOP=0 IS SELECTED BY THE USER, THEN ERRTOL */
/*             IS THE AMOUNT BY WHICH THE INITIAL ERROR IS TO BE */
/*             REDUCED.  BY ESTIMATING THE CONDITION NUMBER OF THE */
/*             ITERATION MATRIX, THE CODE ATTEMPTS TO GUARANTEE THAT */
/*             THE FINAL RELATIVE ERROR IS .LE. ERRTOL.  SEE THE LONG */
/*             DEDCRIPTION BELOW FOR DETAILS. */

/*             IPARAM(9) = ITMAX */
/*             THE MAXIMUM NUMBER OF ITERATIVE STEPS TO BE TAKEN. */
/*             IF SOLVER IS UNABLE TO SATISFY THE STOPPING CRITERION */
/*             WITHIN ITMAX ITERATIONS, IT RETURNS TO THE CALLING */
/*             PROGRAM WITH IERROR=-1000. */

/*             IPARAM(31) = ICYCLE */
/*             THE FREQUENCY WITH WHICH A CONDITION NUMBER ESTIMATE IS */
/*             COMPUTED; SEE THE LONG DEDCRIPTION BELOW. */

/*             IPARAM(32) = NCE */
/*             THE MAXIMUM NUMBER OF CONDITION NUMBER ESTIMATES TO BE */
/*             COMPUTED.  IF NCE = 0 NO ESTIMATES ARE COMPUTED.  SEE */
/*             THE LONG DEDCRIPTION BELOW. */

/*             NOTE:  KMAX = ICYCLE*NCE IS THE ORDER OF THE LARGEST */
/*             ORTHOGONAL SECTION OF C*A USED TO COMPUTE A CONDITION */
/*             NUMBER ESTIMATE.  THIS ESTIMATE IS ONLY USED IN THE */
/*             STOPPING CRITERION.  AS SUCH, KMAX SHOULD BE MUCH LESS */
/*             THAN N.  OTHERWISE THE CODE WILL HAVE EXCESSIVE STORAGE */
/*             AND WORK REQUIREMENTS. */

/*    RPARAM   DBLE(40). */
/*             AN ARRAY OF DBLE INPUT PARAMETERS: */
/*                NOTE: RPARAM(1) AND RPARAM(2) ARE MANDATED BY THE */
/*                PROPOSED STANDARD; RPARAM(3) THROUGH RPARAM(30) ARE */
/*                RESERVED FOR EXPANSION OF THE PROPOSED STANDARD; */
/*                RPARAM(31) THROUGH RPARAM(34) ARE ADDITIONAL */
/*                PARAMETERS, SPECIFIC TO CGCODE. */

/*             RPARAM(1) = ERRTOL */
/*             USER PROVIDED ERROR TOLERANCE; SEE ISTOP ABOVE, AND THE */
/*             LONG DEDCRIPTION BELOW. */

/*             RPARAM(31) = CONDES */
/*             AN INITIAL ESTIMATE FOR THE COND NUMBER OF THE ITERATION */
/*             MATRIX; SEE THE INDIVIDUAL SUBROUTINE'S PROLOGUE. AN */
/*             ACCEPTABLE INITIAL VALUE IS 1.0. */

/*    R        DBLE(N). */
/*             WORK ARRAY OF LENGTH .GE. N. */

/*    AAP      DBLE(N). */
/*             WORK ARRAY OF LENGTH .GE. N. */

/*    AP       DBLE(N). */
/*             WORK ARRAY OF LENGTH .GE. N. */

/*    POLD     DBLE(N). */
/*             WORK ARRAY OF LENGTH .GE. N. */

/*    APOLD    DBLE(N). */
/*             WORK ARRAY OF LENGTH .GE. N. */

/*    D,E      DBLE(ICYCLE*NCE + 1), DBLE(ICYCLE*NCE + 1). */
/*    CNDWK    DBLE(2*ICYCLE*NCE). */
/*    IWORK    INTEGER(ICYCLE*NCE). */
/*             WORK ARRAYS FOR COMPUTING CONDITION NUMBER ESTIMATES. */
/*             IF NCE = 0 THESE MAY BE DUMMY ADDRESSES. */

/* --- ON RETURN --- */

/*    IPARAM   THE FOLLOWING ITERATION INFO IS RETURNED VIA THIS ARRAY: */

/*             IPARAM(10) = ITERS */
/*             THE NUMBER OF ITERATIONS TAKEN.  IF IERROR=0, THEN X_ITERS */
/*             SATISFIES THE SPECIFIED STOPPING CRITERION.  IF */
/*             IERROR=-1000, CGCODE WAS UNABLE TO CONVERGE WITHIN ITMAX */
/*             ITERATIONS, AND X_ITERS IS CGCODE'S BEST APPROXIMATION TO */
/*             THE SOLUTION OF A*X=B. */

/*    RPARAM   THE FOLLOWING ITERATION INFO IS RETURNED VIA THIS ARRAY: */

/*             RPARAM(2) = STPTST */
/*             FINAL QUANTITY USED IN THE STOPPING CRITERION; SEE ISTOP */
/*             ABOVE, AND THE LONG DEDCRIPTION BELOW. */

/*             RPARAM(31) = CONDES */
/*             CONDITION NUMBER ESTIMATE; FINAL ESTIMATE USED IN THE */
/*             STOPPING CRITERION; SEE ISTOP ABOVE, AND THE LONG */
/*             DEDCRIPTION BELOW. */

/*             RPARAM(34) = DCRLRS */
/*             THE SCALED RELATIVE RESIDUAL USING THE LAST COMPUTED */
/*             RESIDUAL. */

/*    X        THE COMPUTED SOLUTION OF THE LINEAR SYSTEM AX=B. */

/*    IERROR   INTEGER. */
/*             ERROR FLAG (NEGATIVE ERRORS ARE FATAL): */
/*             (BELOW, A=SYSTEM MATRIX, Q=LEFT PRECONDITIONING MATRIX.) */
/*             IERROR =  0      NORMAL RETURN: ITERATION CONVERGED */
/*             IERROR =  -1000  METHOD FAILED TO CONVERGE IN ITMAX STEPS */
/*             IERROR = +-2000  ERROR IN USER INPUT */
/*             IERROR = +-3000  METHOD BREAKDOWN */
/*             IERROR =  -6000  A DOES NOT SATISTY ASSUMPTIONS OF METHOD */
/*             IERROR =  -7000  Q DOES NOT SATISTY ASSUMPTIONS OF METHOD */

/* ***LONG DEDCRIPTION */

/*    DCRIND IMPLEMENTS THE CONJUGATE RESIDUAL METHOD FOR SYMMETRIC */
/*    MATRICES, USING A HYBRID ODIR/OMIN ALGORITHM GIVEN BY: */

/*                   P0 = R0 */
/*                   ALPHA = <A*P,R>/<A*P,A*P> */
/*                   XNEW = X + ALPHA*P */
/*                   RNEW = R - ALPHA*(A*P) */
/*                   IF (ALPHA < EPSILON) THEN */
/*                      IF (ALPHA_OLD < EPSILON) THEN */
/*                         C = 1.0 */
/*                      ELSE */
/*                         C = -1.0 / ALPHA_OLD */
/*                      ENDIF */
/*                      SIGMA = C * <A*P,A*P>/<A*POLD,A*POLD> */
/*                      GAMMA = <A*A*P,A*P>/<A*P,A*P> */
/*                      PNEW = A*P - GAMMA*P - SIGMA*POLD */
/*                   ELSE */
/*                      BETA = <A*RNEW,A*P>/<A*P,A*P> */
/*                      PNEW = RNEW - BETA*P */
/*                   ENDIF */

/*    THIS ALGORITHM IS GUARANTEED TO CONVERGE FOR SYMMETRIC MATRICES. */
/*    MATHEMATICALLY, IF THE MATRIX HAS M DISTINCT EIGENVALUES, THE */
/*    ALGORITHM WILL CONVERGE IN AT MOST M STEPS.  AT EACH STEP THE */
/*    ALGORITHM MINIMIZES THE 2-NORM OF THE RESIDUAL. */

/*    WHEN THE USER SELECTS THE STOPPING CRITERION OPTION ISTOP=0, THEN */
/*    THE CODE STOPS WHEN  COND(A)*(RNORM/R0NORM) .LE. ERRTOL, THEREBY */
/*    ATTEMPTING TO GUARANTEE THAT (FINAL RELATIVE ERROR) .LE. ERRTOL. */
/*    A NEW ESTIMATE FOR COND(A) IS COMPUTED EVERY ICYCLE STEPS. THIS */
/*    IS DONE BY COMPUTING THE MIN AND MAX EIGENVALUES OF AN ORTHOGONAL */
/*    SECTION OF A.  THE LARGEST ORTHOG SECTION HAS ORDER ICYCLE*NCE, */
/*    WHERE NCE IS THE MAXIMUM NUMBER OF CONDITION ESTIMATES.  IF NCE=0, */
/*    NO CONDITION ESTIMATES ARE COMPUTED.  IN THIS CASE, THE CODE STOPS */
/*    WHEN RNORM/R0NORM .LE. ERRTOL.  (ALSO SEE THE PROLOGUE TO DCGDRV.) */

/*    THIS STOPPING CRITERION WAS IMPLEMENTED BY A.J. ROBERTSON, III */
/*    (DEPT. OF MATHEMATICS, UNIV. OF COLORADO AT DENVER).  QUESTIONS */
/*    MAY BE DIRECTED TO HIM OR TO ONE OF THE AUTHORS. */

/*    DCRIND IS ONE ROUTINE IN A PACKAGE OF CG CODES; THE OTHERS ARE: */

/*    DCGDRV : AN INTERFACE TO ANY ROUTINE IN THE PACKAGE */
/*    DCG    : CONJUGATE GRADIENTS ON A, A SPD (CGHS) */
/*    DCR    : CONJUGATE RESIDUALS ON A, A SPD (CR) */
/*    DCRIND : CR ON A, A SYMMETRIC (CRIND) */
/*    DPCG   : PRECONITIONED CG ON A, A AND C SPD (PCG) */
/*    DCGNR  : CGHS ON AT*A, A ARBITRARY (CGNR) */
/*    DCGNE  : CGHS ON A*AT, A ARBITRARY (CGNE) */
/*    DPCGNR : CGNR ON A*C, A AND C ARBITRARY (PCGNR) */
/*    DPCGNE : CGNE ON C*A, A AND C ARBITRARY (PCGNE) */
/*    DPPCG  : POLYNOMIAL PCG ON A, A AND C SPD (PPCG) */
/*    DPCGCA : CGHS ON C(A)*A, A AND C SPD (PCGCA) */

/* ***REFERENCES  HOWARD C. ELMAN, "ITERATIVE METHODS FOR LARGE, SPARSE, */
/*                 NONSYMMETRIC SYSTEMS OF LINEAR EQUATIONS", YALE UNIV. */
/*                 DCS RESEARCH REPORT NO. 229 (APRIL 1982). */
/*               VANCE FABER AND THOMAS MANTEUFFEL, "NECESSARY AND */
/*                 SUFFICIENT CONDITIONS FOR THE EXISTENCE OF A */
/*                 CONJUGATE GRADIENT METHODS", SIAM J. NUM ANAL 21(2), */
/*                 PP. 352-362, 1984. */
/*               S. ASHBY, T. MANTEUFFEL, AND P. SAYLOR, "A TAXONOMY FOR */
/*                 CONJUGATE GRADIENT METHODS", SIAM J. NUM ANAL 27(6), */
/*                 PP. 1542-1568, 1990. */
/*               S. ASHBY, M. HOLST, T. MANTEUFFEL, AND P. SAYLOR, */
/*                 THE ROLE OF THE INNER PRODUCT IN STOPPING CRITERIA */
/*                 FOR CONJUGATE GRADIENT ITERATIONS", BIT 41(1), */
/*                 PP. 26-53, 2001. */
/*               M. HOLST, "CGCODE: SOFTWARE FOR SOLVING LINEAR SYSTEMS */
/*                 WITH CONJUGATE GRADIENT METHODS", M.S. THESIS, UNIV. */
/*                 OF ILLINOIS DCS RESEARCH REPORT (MAY 1990). */
/*               S. ASHBY, "POLYNOMIAL PRECONDITIONG FOR CONJUGATE */
/*                 GRADIENT METHODS", PH.D. THESIS, UNIV. OF ILLINOIS */
/*                 DCS RESEARCH REPORT NO. R-87-1355 (DECEMBER 1987). */
/*               S. ASHBY, M. SEAGER, "A PROPOSED STANDARD FOR ITERATIVE */
/*                 LINEAR SOLVERS", LAWRENCE LIVERMORE NATIONAL */
/*                 LABORATORY REPORT (TO APPEAR). */

/* ***ROUTINES CALLED  MATVEC,MDSTOP,D1MACH,DCGCHK,DDOT,DNRM2 */
/* ***END PROLOGUE  DCRIND */

/*     TO SAVE VECTOR COPIES THE ITERATION IS UNROLLED */

/*     *** DECLARATIONS *** */

/* ***FIRST EXECUTABLE STATEMENT  DCRIND */
    /* Parameter adjustments */
    --apold;
    --pold;
    --ap;
    --aap;
    --r__;
    --b;
    --x;
    --iparam;
    --rparam;
    --iwork;
    --d__;
    --e;
    --cndwk;

    /* Function Body */
/* L1: */

/*     *** INITIALIZE INPUT PARAMETERS *** */
    iounit = iparam[5];
    istop = iparam[8];
    itmax = iparam[9];
    icycle = iparam[31];
    nce = iparam[32];
    kmax = icycle * nce;
    errtol = rparam[1];
    conda = max(1.,rparam[31]);
    epslon = sqrt(d1mach_(&c__4));

/*     *** CHECK THE INPUT PARAMETERS *** */
    if (iounit > 0) {
	io___10.ciunit = iounit;
	s_wsfe(&io___10);
	e_wsfe();
    }
    dcgchk_(&iparam[1], &rparam[1], n);
    if (iounit > 0) {
	io___11.ciunit = iounit;
	s_wsfe(&io___11);
	do_fio(&c__1, (char *)&conda, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (iounit > 0) {
	io___12.ciunit = iounit;
	s_wsfe(&io___12);
	e_wsfe();
    }

/*     *** INITIALIZE D(1), EIGMIN, EIGMAX, ITERS *** */
    d__[1] = 0.;
    eigmin = d1mach_(&c__2);
    eigmax = d1mach_(&c__1);
    iters = 0;

/*     *** COMPUTE STOPPING CRITERION DENOMINATOR *** */
    denom = 1.;
    if (istop == 0) {
	denom = dnrm2_(n, &b[1], &c__1);
    }
    if (istop == 2) {
	denom = dnrm2_(n, &b[1], &c__1);
    }
    if (istop == 4) {
	denom = dnrm2_(n, &b[1], &c__1);
    }

/*     *** TELL MDSTOP WHETHER OR NOT I AM SUPPLYING THE STOPPING QUANTITY *** */
    ido = 1;

/*     *** COMPUTE THE INITIAL RESIDUAL *** */
    (*matvec)(&c__0, a, ia, &wdummy, &x[1], &r__[1], n);
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	r__[i__] = b[i__] - r__[i__];
/* L20: */
    }
    r0norm = dnrm2_(n, &r__[1], &c__1);
    if (iounit > 0) {
	io___21.ciunit = iounit;
	s_wsfe(&io___21);
	do_fio(&c__1, (char *)&r0norm, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }

/*     *** CHECK THE INITIAL RESIDUAL *** */
    jstop = mdstop_(&istop, &iters, &itmax, &errtol, &stptst, ierror, &rdumm, 
	    &sdumm, &zdumm, n, &r0norm, &r0norm, &r0norm, &denom, &conda, &
	    ido);
    if (jstop == 1) {
	goto L90;
    }

/*     *** INITIALIZE P, POLD, AP, APOLD *** */
    (*matvec)(&c__0, a, ia, &wdummy, &r__[1], &ap[1], n);
    dennew = 1.;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b[i__] = r__[i__];
	pold[i__] = 0.f;
	apold[i__] = 0.f;
/* L26: */
    }

/*     *** UPDATE ITERS *** */
L30:
    ++iters;

/*     *** COMPUTE NEW X AND R *** */
    denold = dennew;
/* Computing 2nd power */
    d__1 = dnrm2_(n, &ap[1], &c__1);
    dennew = d__1 * d__1;
    alfold = alpha;
    alpha = ddot_(n, &r__[1], &c__1, &ap[1], &c__1) / dennew;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	x[i__] += alpha * b[i__];
	r__[i__] -= alpha * ap[i__];
/* L32: */
    }

/*     *** CHECK NEW R *** */
    rnorm = dnrm2_(n, &r__[1], &c__1);
    if (iounit > 0) {
	io___32.ciunit = iounit;
	s_wsfe(&io___32);
	do_fio(&c__1, (char *)&iters, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&rnorm, (ftnlen)sizeof(doublereal));
	d__1 = rnorm / r0norm;
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }

/*     *** TEST TO HALT *** */
    jstop = mdstop_(&istop, &iters, &itmax, &errtol, &stptst, ierror, &rdumm, 
	    &sdumm, &zdumm, n, &rnorm, &rnorm, &rnorm, &denom, &conda, &ido);
    if (jstop == 1) {
	goto L90;
    }

/*     *** CASE I: ALPHA SMALL *** */
    if (abs(alpha) <= epslon) {

/*        *** DETERMINE COEF *** */
	if (abs(alfold) <= epslon) {
	    coef = 1.;
	} else {
	    coef = -1. / alfold;
	}

/*        *** COMPUTE NEW P, AP *** */
	(*matvec)(&c__0, a, ia, &wdummy, &ap[1], &aap[1], n);
	sigma = coef * dennew / denold;
	gamma = ddot_(n, &aap[1], &c__1, &ap[1], &c__1) / dennew;
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    tempp = gamma * b[i__] + sigma * pold[i__];
	    pold[i__] = b[i__];
	    b[i__] = ap[i__] - tempp;
	    tempp = gamma * ap[i__] + sigma * apold[i__];
	    apold[i__] = ap[i__];
	    ap[i__] = aap[i__] - tempp;
/* L44: */
	}
    } else {

/*     *** CASE II: ALPHA LARGE *** */

/*        *** COMPUTE NEW P, AP *** */
	(*matvec)(&c__0, a, ia, &wdummy, &r__[1], &aap[1], n);
	beta = ddot_(n, &aap[1], &c__1, &ap[1], &c__1) / dennew;
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    pold[i__] = b[i__];
	    apold[i__] = ap[i__];
	    b[i__] = r__[i__] - beta * b[i__];
	    ap[i__] = aap[i__] - beta * ap[i__];
/* L55: */
	}
    }

/*     *** RESUME CR ITERATION *** */
    goto L30;

/*     *** FINISHED: PASS BACK ITERATION INFO *** */
L90:
    iparam[10] = iters;
    rparam[2] = stptst;
    rparam[31] = conda;
    rparam[34] = rnorm / r0norm;

    return 0;
} /* dcrind_ */

