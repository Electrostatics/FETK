/* ./src_f77/spcgnr.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__0 = 0;

/* Subroutine */ int spcgnr_(S_fp matvec, S_fp pcondl, real *a, integer *ia, 
	real *x, real *b, integer *n, real *q, integer *iq, integer *iparam, 
	real *rparam, integer *iwork, real *r__, real *h__, real *ap, real *
	d__, real *e, real *cndwk, integer *ierror)
{
    /* Format strings */
    static char fmt_6[] = "(\002 THE METHOD IS CG ON CT*AT*A*C (PCGNR)\002,/)"
	    ;
    static char fmt_8[] = "(4x,\002CNDPNS = \002,e12.5,/)";
    static char fmt_10[] = "(\002 RESID  = 2-NORM OF C*CT*AT*R\002,/,\002 RE"
	    "LRSD = RESID / INITIAL RESID\002,/,\002 COND(C*CT*AT*A) USED IN "
	    "STOPPING CRITERION\002,/)";
    static char fmt_25[] = "(\002 INITIAL RESID = \002,e12.5,/)";
    static char fmt_35[] = "(\002 ITERS = \002,i5,4x,\002RESID = \002,e12.5,"
	    "4x,\002RELRSD = \002,e12.5)";
    static char fmt_70[] = "(/,\002 NEW ESTIMATES FOR C*CT*AT*A:\002)";

    /* System generated locals */
    integer i__1;
    real r__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, nce, ido, isp1;
    static real beta;
    static integer kmax;
    extern doublereal snrm2_(integer *, real *, integer *);
    static real alpha, denom;
    static integer itmax;
    static real hnorm, sdumm;
    static integer iters;
    static real wdumm, zdumm;
    static integer istop, jstop;
    static real snorm;
    extern /* Subroutine */ int saxpy_(integer *, real *, real *, integer *, 
	    real *, integer *);
    extern doublereal r1mach_(integer *);
    static real s0norm;
    extern /* Subroutine */ int scgchk_(integer *, real *, integer *);
    static real ralpha;
    static integer icycle;
    static real eigmin, eigmax, oldhnm, cndpns, rndumm;
    static integer iounit;
    static real errtol;
    extern /* Subroutine */ int sonest_(integer *, real *, real *, real *, 
	    real *, integer *, integer *, real *, real *, real *);
    static real wdummy;
    extern integer msstop_(integer *, integer *, integer *, real *, real *, 
	    integer *, real *, real *, real *, integer *, real *, real *, 
	    real *, real *, real *, integer *);
    static real stptst;

    /* Fortran I/O blocks */
    static cilist io___9 = { 0, 0, 0, fmt_6, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_8, 0 };
    static cilist io___11 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___21 = { 0, 0, 0, fmt_25, 0 };
    static cilist io___30 = { 0, 0, 0, fmt_35, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_70, 0 };


/* ***BEGIN PROLOGUE  SPCGNR */
/* ***DATE WRITTEN   860115   (YYMMDD) */
/* ***REVISION DATE  900210   (YYMMDD) */
/* ***CATEGORY NO. D2A4 */
/* ***KEYWORDS  LINEAR SYSTEM,SPARSE,NONSYMMETRIC,NORMAL EQUATIONS, */
/*             PRECONDITION,ITERATIVE,CONJUGATE GRADIENTS */
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
/* ***PURPOSE  THIS ROUTINE SOLVES THE ARBITRARY LINEAR SYSTEM AX=P BY */
/*            THE METHOD OF CONJUGATE GRADIENTS ON THE PRECONDITIONED */
/*            NORMAL EQUATIONS.  SEE THE LONG DESCRIPTION FOR DETAILS. */
/* ***DESCRIPTION */

/* --- ON ENTRY --- */

/*    MATVEC   EXTERNAL SUBROUTINE MATVEC(JOB,A,IA,W,X,Y,N) */
/*             THE USER MUST PROVIDE A SUBROUTINE HAVING THE SPECIFED */
/*             PARAMETER LIST.  THE SUBROUTINE MUST RETURN THE PRODUCT */
/*             (OR A RELATED COMPUTATION; SEE BELOW) Y=A*X, WHERE A IS */
/*             THE COEFFICIENT MATRIX OF THE LINEAR SYSTEM.  THE MATRIX */
/*             A IS REPRESENTED BY THE WORK ARRAYS A AND IA, DESCRIBED */
/*             BELOW.  THE INTEGER PARAMETER JOB SPECIFIES THE PRODUCT */
/*             TO BE COMPUTED: */
/*                  JOB=0    Y=A*X */
/*                  JOB=1    Y=AT*X */
/*                  JOB=2    Y=W - A*X */
/*                  JOB=3    Y=W - AT*X. */
/*             IN THE ABOVE, AT DENOTES A-TRANSPOSE.  NOTE THAT */
/*             ONLY THE VALUES OF JOB=0,1 ARE REQUIRED FOR CGCODE. */
/*             ALL OF THE ROUTINES IN CGCODE REQUIRE JOB=0; THE */
/*             ROUTINES SCGNR, SCGNE, SPCGNR, AND SPCGNE ALSO REQUIRE */
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

/*    PCONDL   EXTERNAL SUBROUTINE PCONDL(JOB,Q,IQ,W,X,Y,N) */
/*             PCONDL IMPLEMENTS A USER SUPPLIED LEFT-PRECONDITIONER. */
/*             IF PRECONDITIONING IS SPECIFIED BY THE USER, THEN THE */
/*             USER MUST PROVIDE A SUBROUTINE HAVING THE SPECIFED */
/*             PARAMETER LIST.  THE SUBROUTINE MUST RETURN THE PRODUCT */
/*             (OR A RELATED COMPUTATION; SEE BELOW) Y=C*X, WHERE C */
/*             IS A PRECONDITIONING MATRIX.  THE MATRIX C IS */
/*             REPRESENTED BY THE WORK ARRAYS Q AND IQ, DESCRIBED */
/*             BELOW.  THE INTEGER PARAMETER JOB SPECIFIES THE PRODUCT */
/*             TO BE COMPUTED: */
/*                  JOB=0    Y=C*X */
/*                  JOB=1    Y=CT*X */
/*                  JOB=2    Y=W - C*X */
/*                  JOB=3    Y=W - CT*X. */
/*             IN THE ABOVE, CT DENOTES C-TRANSPOSE.  NOTE THAT */
/*             ONLY THE VALUES OF JOB=0,1 ARE REQUIRED FOR CGCODE. */
/*             THE ROUTINES SPCG, SPCGNR, SPCGNE, SPPCG, AND SPCGCA IN */
/*             CGCODE REQUIRE JOB=0; THE ROUTINES SPCGNR AND SPCGNE ALSO */
/*             REQUIRE THE VALUE OF JOB=1.  (THE VALUES OF JOB=2,3 ARE */
/*             NOT REQUIRED BY ANY OF THE ROUTINES IN CGCODE, BUT MAY BE */
/*             REQUIRED BY OTHER ITERATIVE PACKAGES CONFORMING TO THE */
/*             PROPOSED ITERATIVE STANDARD.)  THE PARAMETERS W,X,Y ARE */
/*             ALL VECTORS OF LENGTH N.  THE ONLY PARAMETER THAT MAY BE */
/*             CHANGED INSIDE THE ROUTINE IS Y.  PCONDL WILL USUALLY */
/*             SERVE AS AN INTERFACE TO THE USER'S OWN PRECONDITIONING */
/*             NOTE: PCONDL MUST BE DECLARED IN AN EXTERNAL STATEMENT */
/*             IN THE CALLING PROGRAM.  IF NO PRE-CONDITIONING IS BEING */
/*             DONE, PCONDL IS A DUMMY ARGUMENT. */

/*    A        REAL ARRAY ADDRESS. */
/*             THE BASE ADDRESS OF THE USER'S REAL WORK ARRAY, USUALLY */
/*             THE MATRIX A.  SINCE A IS ONLY ACCESSED BY CALLS TO SUBR */
/*             MATVEC, IT MAY BE A DUMMY ADDRESS. */

/*    IA       INTEGER ARRAY ADDRESS. */
/*             THE BASE ADDRESS OF THE USER'S INTEGER WORK ARRAY.  THIS */
/*             USUALLY CONTAINS ADDITIONAL INFORMATION ABOUT A NEEDED BY */
/*             MATVEC.  SINCE IA IS ONLY ACCESSED BY CALLS TO MATVEC, IT */
/*             MAY BE A DUMMY ADDRESS. */

/*    X        REAL(N). */
/*             THE INITIAL GUESS VECTOR, X0. */
/*             (ON EXIT, X IS OVERWRITTEN WITH THE APPROXIMATE SOLUTION */
/*             OF A*X=B.) */

/*    B        REAL(N). */
/*             THE RIGHT-HAND SIDE VECTOR OF THE LINEAR SYSTEM AX=B. */
/*             NOTE: B IS CHANGED BY THE SOLVER. */

/*    N        INTEGER. */
/*             THE ORDER OF THE MATRIX A IN THE LINEAR SYSTEM AX=B. */

/*    Q        REAL ARRAY ADDRESS. */
/*             THE BASE ADDRESS OF THE USER'S LEFT-PRECONDITIONING ARRAY, */
/*             Q.  SINCE Q IS ONLY ACCESSED BY CALLS TO PCONDL, IT MAY BE */
/*             A DUMMY ADDRESS.  IF NO LEFT-PRECONDITIONING IS BEING */
/*             DONE, THIS IS A DUMMY ARGUMENT. */

/*    IQ       INTEGER ARRAY ADDRESS. */
/*             THE BASE ADDRESS OF AN INTEGER WORK ARRAY ASSOCIATED WITH */
/*             Q.  THIS PROVIDES THE USER WITH A WAY OF PASSING INTEGER */
/*             INFORMATION ABOUT Q TO PCONDL.  SINCE IQ IS ONLY ACCESSED */
/*             BY CALLS TO PCONDL, IT MAY BE A DUMMY ADDRESS.  IF NO */
/*             LEFT-PRECONDITIONING IS BEING DONE, THIS IS A DUMMY */
/*             ARGUMENT. */

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
/*             DESCRIPTION BELOW FOR DETAILS. */

/*             IPARAM(9) = ITMAX */
/*             THE MAXIMUM NUMBER OF ITERATIVE STEPS TO BE TAKEN. */
/*             IF SOLVER IS UNABLE TO SATISFY THE STOPPING CRITERION */
/*             WITHIN ITMAX ITERATIONS, IT RETURNS TO THE CALLING */
/*             PROGRAM WITH IERROR=-1000. */

/*             IPARAM(31) = ICYCLE */
/*             THE FREQUENCY WITH WHICH A CONDITION NUMBER ESTIMATE IS */
/*             COMPUTED; SEE THE LONG DESCRIPTION BELOW. */

/*             IPARAM(32) = NCE */
/*             THE MAXIMUM NUMBER OF CONDITION NUMBER ESTIMATES TO BE */
/*             COMPUTED.  IF NCE = 0 NO ESTIMATES ARE COMPUTED.  SEE */
/*             THE LONG DESCRIPTION BELOW. */

/*             NOTE:  KMAX = ICYCLE*NCE IS THE ORDER OF THE LARGEST */
/*             ORTHOGONAL SECTION OF C*A USED TO COMPUTE A CONDITION */
/*             NUMBER ESTIMATE.  THIS ESTIMATE IS ONLY USED IN THE */
/*             STOPPING CRITERION.  AS SUCH, KMAX SHOULD BE MUCH LESS */
/*             THAN N.  OTHERWISE THE CODE WILL HAVE EXCESSIVE STORAGE */
/*             AND WORK REQUIREMENTS. */

/*    RPARAM   REAL(40). */
/*             AN ARRAY OF REAL INPUT PARAMETERS: */
/*                NOTE: RPARAM(1) AND RPARAM(2) ARE MANDATED BY THE */
/*                PROPOSED STANDARD; RPARAM(3) THROUGH RPARAM(30) ARE */
/*                RESERVED FOR EXPANSION OF THE PROPOSED STANDARD; */
/*                RPARAM(31) THROUGH RPARAM(34) ARE ADDITIONAL */
/*                PARAMETERS, SPECIFIC TO CGCODE. */

/*             RPARAM(1) = ERRTOL */
/*             USER PROVIDED ERROR TOLERANCE; SEE ISTOP ABOVE, AND THE */
/*             LONG DESCRIPTION BELOW. */

/*             RPARAM(31) = CONDES */
/*             AN INITIAL ESTIMATE FOR THE COND NUMBER OF THE ITERATION */
/*             MATRIX; SEE THE INDIVIDUAL SUBROUTINE'S PROLOGUE. AN */
/*             ACCEPTABLE INITIAL VALUE IS 1.0. */

/*    R        REAL(N). */
/*             WORK ARRAY OF LENGTH .GE. N. */

/*    H        REAL(N). */
/*             WORK ARRAY OF LENGTH .GE. N. */

/*    AP       REAL(N). */
/*             WORK ARRAY OF LENGTH .GE. N. */

/*    D,E      REAL(ICYCLE*NCE + 1), REAL(ICYCLE*NCE + 1). */
/*    CNDWK    REAL(2*ICYCLE*NCE). */
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
/*             ABOVE, AND THE LONG DESCRIPTION BELOW. */

/*             RPARAM(31) = CONDES */
/*             CONDITION NUMBER ESTIMATE; FINAL ESTIMATE USED IN THE */
/*             STOPPING CRITERION; SEE ISTOP ABOVE, AND THE LONG */
/*             DESCRIPTION BELOW. */

/*             RPARAM(34) = SCRLRS */
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

/* ***LONG DESCRIPTION */

/*    SPCGNR IMPLEMENTS SCGNR ON THE PRECONDITIONED NORMAL EQUATIONS, */
/*    CT*AT*A*C, USING THE OMIN ALGORITHM GIVEN BY: */

/*                   H0 = CT*AT*R0 */
/*                   P0 = C*H0 */
/*                   ALPHA = <H,H>/<A*P,A*P> */
/*                   XNEW = X + ALPHA*P */
/*                   RNEW = R - ALPHA*(A*P) */
/*                   HNEW = CT*AT*RNEW */
/*                   BETA = <HNEW,HNEW>/<H,H> */
/*                   PNEW = C*HNEW + BETA*P */

/*    THIS ALGORITHM IS GUARANTEED TO CONVERGE FOR ANY NONSINGULAR A. */
/*    MATHEMATICALLY, IF CT*AT*A*C HAS M DISTINCT EIGENVALUES, THEN */
/*    THE ALGORITHM WILL CONVERGE IN AT MOST M STEPS.  AT EACH STEP THE */
/*    ALGORITHM MINIMIZES THE 2-NORM OF THE RESIDUAL. */

/*    WHEN THE USER SELECTS THE STOPPING CRITERION OPTION ISTOP=0, THE */
/*    CODE STOPS WHEN COND(C*CT*AT*A)*(SNORM/S0NORM) .LE. ERRTOL, */
/*    ATTEMPTING TO GUARANTEE THAT (FINAL RELATIVE ERROR) .LE. ERRTOL. */
/*    A NEW ESTIMATE FOR COND(C*CT*AT*A) IS COMPUTED EVERY ICYCLE */
/*    STEPS, DONE BY COMPUTING THE MIN AND MAX EGVALS OF AN ORTHOGONAL */
/*    SECTION OF A.  THE LARGEST ORTHOG SECTION HAS ORDER ICYCLE*NCE, */
/*    WHERE NCE IS THE MAXIMUM NUMBER OF CONDITION ESTIMATES.  IF NCE=0, */
/*    NO CONDITION ESTIMATES ARE COMPUTED.  IN THIS CASE, THE CODE STOPS */
/*    WHEN SNORM/S0NORM .LE. ERRTOL.  (ALSO SEE THE PROLOGUE TO SCGDRV.) */

/*    THIS STOPPING CRITERION WAS IMPLEMENTED BY A.J. ROBERTSON, III */
/*    (DEPT. OF MATHEMATICS, UNIV. OF COLORADO AT DENVER).  QUESTIONS */
/*    MAY BE DIRECTED TO HIM OR TO ONE OF THE AUTHORS. */

/*    SPCGNR IS ONE ROUTINE IN A PACKAGE OF CG CODES; THE OTHERS ARE: */

/*    SCGDRV: AN INTERFACE TO ANY ROUTINE IN THE PACKAGE. */
/*    SCG:    METHOD OF CONJUGATE GRADIENTS, A SPD. */
/*    SCR:    METHOD OF CONJUGATE RESIDUALS, A SYMMETRIC. */
/*    SCRIND: METHOD OF CONJUGATE RESIDUALS, A SYMMETRIC INDEFINITE. */
/*    SPCG:   PRECONDITIONED CG, BOTH A AND C SPD. */
/*    SCGNR:  CG APPLIED TO AT*A, A ARBITRARY. */
/*    SCGNE:  CG APPLIED TO A*AT, A ARBITRARY. */
/*    SPCGNR: CG APPLIED TO CT*AT*A*C, A AND C ARBITRARY. */
/*    SPCGNE: CG APPLIED TO C*A*AT*CT, A AND C ARBITRARY. */
/*    SPPCG:  POLYNOMIAL PRECONDITIONED CG, BOTH A AND C SPD. */
/*    SPCGCA: CG APPLIED TO C(A)*C*A, BOTH A AND C SPD. */

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

/* ***ROUTINES CALLED  SONEST,R1MACH,SCGCHK,SAXPY,SNRM2 */
/* ***END PROLOGUE  SPCGNR */

/*     *** DECLARATIONS *** */
/* CCCCCIMPLICIT  DOUBLE PRECISION(A-H,O-Z) */

/* ***FIRST EXECUTABLE STATEMENT  SPCGNR */
    /* Parameter adjustments */
    --ap;
    --h__;
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
    cndpns = dmax(1.f,rparam[31]);

/*     *** CHECK THE INPUT PARAMETERS *** */
    if (iounit > 0) {
	io___9.ciunit = iounit;
	s_wsfe(&io___9);
	e_wsfe();
    }
    scgchk_(&iparam[1], &rparam[1], n);
    if (iounit > 0) {
	io___10.ciunit = iounit;
	s_wsfe(&io___10);
	do_fio(&c__1, (char *)&cndpns, (ftnlen)sizeof(real));
	e_wsfe();
    }
    if (iounit > 0) {
	io___11.ciunit = iounit;
	s_wsfe(&io___11);
	e_wsfe();
    }

/*     *** INITIALIZE D(1), EIGMIN, EIGMAX, ITERS *** */
    d__[1] = 0.f;
    eigmin = r1mach_(&c__2);
    eigmax = r1mach_(&c__1);
    iters = 0;

/*     *** COMPUTE STOPPING CRITERION DENOMINATOR *** */
    denom = 1.f;
    if (istop == 2) {
	denom = snrm2_(n, &b[1], &c__1);
    }
    if (istop == 0 || istop == 4) {
	(*matvec)(&c__1, a, ia, &wdumm, &b[1], &r__[1], n);
	(*pcondl)(&c__1, q, iq, &wdumm, &r__[1], &ap[1], n);
	(*pcondl)(&c__0, q, iq, &wdumm, &ap[1], &r__[1], n);
	denom = snrm2_(n, &r__[1], &c__1);
    }

/*     *** TELL MSSTOP WHETHER OR NOT I AM SUPPLYING THE STOPPING QUANTITY *** */
    if (istop == 1 || istop == 2) {
	ido = 0;
    } else {
	ido = 1;
    }

/*     *** COMPUTE THE INITIAL S = C*CT*AT*R *** */
    (*matvec)(&c__0, a, ia, &wdummy, &x[1], &r__[1], n);
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	r__[i__] = b[i__] - r__[i__];
/* L20: */
    }
    (*matvec)(&c__1, a, ia, &wdummy, &r__[1], &ap[1], n);
    (*pcondl)(&c__1, q, iq, &wdummy, &ap[1], &h__[1], n);
    (*pcondl)(&c__0, q, iq, &wdummy, &h__[1], &b[1], n);
    s0norm = snrm2_(n, &b[1], &c__1);
    if (iounit > 0) {
	io___21.ciunit = iounit;
	s_wsfe(&io___21);
	do_fio(&c__1, (char *)&s0norm, (ftnlen)sizeof(real));
	e_wsfe();
    }

/*     *** CHECK THE INITIAL RESIDUAL *** */
    jstop = msstop_(&istop, &iters, &itmax, &errtol, &stptst, ierror, &ap[1], 
	    &sdumm, &zdumm, n, &rndumm, &s0norm, &s0norm, &denom, &cndpns, &
	    ido);
    if (jstop == 1) {
	goto L90;
    }

/*     *** INITIALIZE HNORM *** */
    hnorm = snrm2_(n, &h__[1], &c__1);

/*     *** UPDATE ITERS AND COMPUTE A*P *** */
L30:
    ++iters;
    (*matvec)(&c__0, a, ia, &wdummy, &b[1], &ap[1], n);

/*     *** COMPUTE NEW X *** */
/* Computing 2nd power */
    r__1 = hnorm / snrm2_(n, &ap[1], &c__1);
    alpha = r__1 * r__1;
    saxpy_(n, &alpha, &b[1], &c__1, &x[1], &c__1);

/*     *** COMPUTE AND CHECK NEW S *** */
    r__1 = -alpha;
    saxpy_(n, &r__1, &ap[1], &c__1, &r__[1], &c__1);
    (*matvec)(&c__1, a, ia, &wdummy, &r__[1], &ap[1], n);
    (*pcondl)(&c__1, q, iq, &wdummy, &ap[1], &h__[1], n);
    (*pcondl)(&c__0, q, iq, &wdummy, &h__[1], &ap[1], n);
    snorm = snrm2_(n, &ap[1], &c__1);
    if (iounit > 0) {
	io___30.ciunit = iounit;
	s_wsfe(&io___30);
	do_fio(&c__1, (char *)&iters, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&snorm, (ftnlen)sizeof(real));
	r__1 = snorm / s0norm;
	do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	e_wsfe();
    }

/*     *** TEST TO HALT *** */
    jstop = msstop_(&istop, &iters, &itmax, &errtol, &stptst, ierror, &ap[1], 
	    &sdumm, &zdumm, n, &rndumm, &snorm, &snorm, &denom, &cndpns, &ido)
	    ;
    if (jstop == 1) {
	goto L90;
    }

/*     *** COMPUTE NEW P *** */
    oldhnm = hnorm;
    hnorm = snrm2_(n, &h__[1], &c__1);
/* Computing 2nd power */
    r__1 = hnorm / oldhnm;
    beta = r__1 * r__1;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b[i__] = ap[i__] + beta * b[i__];
/* L40: */
    }

/*     *** UPDATE CONDITION NUMBER *** */
    if (iters <= kmax && istop == 0) {
/*        *** UPDATE PARAMETERS *** */
	isp1 = iters + 1;
	ralpha = 1.f / alpha;
	d__[iters] += ralpha;
	d__[isp1] = beta * ralpha;
	e[isp1] = -sqrt(beta) * ralpha;
	if (iters % icycle == 0) {
	    if (iounit > 0) {
		io___35.ciunit = iounit;
		s_wsfe(&io___35);
		e_wsfe();
	    }
	    sonest_(&iounit, &d__[1], &e[1], &cndwk[1], &cndwk[kmax + 1], &
		    iwork[1], &iters, &eigmin, &eigmax, &cndpns);
	}
    }

/*     *** RESUME PCGNR ITERATION *** */
    goto L30;

/*     *** FINISHED: PASS BACK ITERATION INFO *** */
L90:
    iparam[10] = iters;
    rparam[2] = stptst;
    rparam[31] = cndpns;
    rparam[34] = snorm / s0norm;

    return 0;
} /* spcgnr_ */

