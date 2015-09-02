/* ./src_f77/sppcg.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__0 = 0;
static integer c__1 = 1;

/* Subroutine */ int sppcg_(S_fp matvec, S_fp pcondl, real *a, integer *ia, 
	real *x, real *b, integer *n, real *q, integer *iq, integer *iparam, 
	real *rparam, integer *iwork, real *r__, real *h__, real *w1, real *
	w2, real *w3, real *w4, real *d__, real *e, integer *ierror)
{
    /* Format strings */
    static char fmt_5[] = "(\002 THE METHOD IS POLYNOMIAL PPCG\002,/)";
    static char fmt_10[] = "(\002 RESID  = SQRT(<C(A)R,R>)\002,/,\002 RELRSD"
	    " = RESID / INITIAL RESID\002,/)";
    static char fmt_11[] = "(\002 RESID  = SQRT(<C(C*A)C*R,R>)\002,/,\002 RE"
	    "LRSD = RESID / INITIAL RESID\002,/)";
    static char fmt_25[] = "(\002 INITIAL RESID   = \002,e12.5,/)";
    static char fmt_35[] = "(\002 ITERS = \002,i5,4x,\002RESID = \002,e12.5,"
	    "4x,\002RELRSD = \002,e12.5)";
    static char fmt_40[] = "(/,\002 NEW ESTIMATES FOR C(A)*A:\002)";

    /* System generated locals */
    integer i__1;
    real r__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    double sqrt(doublereal);
    integer do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static integer i__;
    static real aa, bb;
    static integer nce, ido, ksp1, nchb;
    static real beta;
    static integer ndeg, kmax;
    extern doublereal sdot_(integer *, real *, integer *, real *, integer *), 
	    snrm2_(integer *, real *, integer *);
    static real alpha, erred, denom, ereps;
    static integer itmax;
    static real sdumm;
    static integer iters, kstep;
    static real zdumm;
    static integer istop;
    static real snorm;
    static integer jstop;
    extern /* Subroutine */ int saxpy_(integer *, real *, real *, integer *, 
	    real *, integer *);
    static real s0norm, condca;
    extern /* Subroutine */ int sckchb_(integer *, real *, real *, real *, 
	    real *), scgchk_(integer *, real *, integer *), sdpchb_(integer *,
	     real *, real *, integer *, real *, real *, real *, real *, 
	    integer *);
    static integer iadapt;
    static real ralpha;
    static integer icycle, ipcond;
    extern /* Subroutine */ int scbfix_(S_fp, S_fp, real *, integer *, real *,
	     integer *, integer *, real *, real *, integer *, real *, real *, 
	    real *, real *, real *, integer *);
    static real pegmin, pegmax, oldsnm, rndumm;
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
    static cilist io___2 = { 0, 0, 0, fmt_5, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___8 = { 0, 0, 0, fmt_11, 0 };
    static cilist io___28 = { 0, 0, 0, fmt_25, 0 };
    static cilist io___36 = { 0, 0, 0, fmt_35, 0 };
    static cilist io___40 = { 0, 0, 0, fmt_40, 0 };


/* ***BEGIN PROLOGUE  SPPCG */
/* ***DATE WRITTEN   860715   (YYMMDD) */
/* ***REVISION DATE  900208   (YYMMDD) */
/* ***CATEGORY NO. D2B4 */
/* ***KEYWORDS  LINEAR SYSTEM,SPARSE,SYMMETRIC,POSITIVE DEFINITE, */
/*             ITERATIVE,PRECONDITION,CONJUGATE GRADIENTS,POLYNOMIAL, */
/*             CHEBYSHEV,ADAPTIVE */
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
/* ***PURPOSE  THIS SUBR SOLVES THE POLYNOMIAL PRECONDITIONED LINEAR */
/*            SYSTEM C(A)*AX = C(A)*B.   THE OPTIMAL (CHEBYSHEV) */
/*            PRECONDTIONING POLYNOMIAL C(A) (OF EVEN DEGREE) IS */
/*            DYNAMICALLY FOUND.  THE METHOD OF PRECONDITIONED CG IS */
/*            USED, WITH C(A) AS THE PRECONDITIONER; A MUST BE SPD. */

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

/*             IPARAM(7) = IPCOND */
/*             PRECONDITIONING FLAG, SPECIFIED AS: */
/*                IPCOND = 0   NO PRECONDITIONING */
/*                IPCOND = 1   LEFT PRECONDITIONING */
/*                IPCOND = 2   RIGHT PRECONDITIONING */
/*                IPCOND = 3   BOTH LEFT AND RIGHT PRECONDITIONING */
/*             NOTE:  RIGHT PRECONDITIONING IS A MANDATED OPTION OF THE */
/*             PROPOSED STANDARD, BUT NOT IMPLEMENTED IN CGCODE. */

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

/*             IPARAM(34) = NDEG */
/*             WHEN USING THE CONJUGATE GRADIENT ROUTINES SPPCG AND */
/*             SPCGCA, NDEG SPECIFIES THE DEGREE OF THE PRECONDITIONING */
/*             POLYNOMIAL TO BE USED IN THE ADAPTIVE POLYNOMIAL */
/*             PRECONDITIONING ROUTINES. */

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

/*             RPARAM(32) = AA */
/*             INITIAL ESTIMATE OF THE SMALLEST EIGENVALUE OF THE */
/*             SYSTEM MATRIX.  WHEN USING THE CONJUGATE GRADIENT */
/*             ROUTINES SPPCG AND SPCGCA, AA IS USED IN THE ADAPTIVE */
/*             POLYNOMIAL PRECONDITIONING ROUTINES FOR FORMING THE */
/*             OPTIMAL PRECONDITIONING POLYNOMIAL. */

/*             RPARAM(33) = BB */
/*             INITIAL ESTIMATE OF THE LARGEST EIGENVALUE OF THE */
/*             SYSTEM MATRIX.  WHEN USING THE CONJUGATE GRADIENT */
/*             ROUTINES SPPCG AND SPCGCA, BB IS USED IN THE ADAPTIVE */
/*             POLYNOMIAL PRECONDITIONING ROUTINES FOR FORMING THE */
/*             OPTIMAL PRECONDITIONING POLYNOMIAL. */

/*    R,H      REAL(N), REAL(N). */
/*             WORK ARRAYS FOR THE CG ITERATION. */

/*    W1,W2    REAL(N), REAL(N). */
/*             WORK ARRAYS FOR EXECUTING THE POLYNOMIAL PRECONDITIONING. */

/*    W3,W4    REAL(N), REAL(N). */
/*             WORK ARRAYS FOR EXECUTING THE INNER PRECONDITIONING.  THESE */
/*             ARE DUMMY ARGUMENTS IF IPCOND=0. */

/*    D,E      REAL(ICYCLE*NCE + 1), REAL(ICYCLE*NCE + 1). */
/*    IWORK    INTEGER(ICYCLE*NCE). */
/*             WORK ARRAYS FOR COMPUTING CONDITION NUMBER ESTIMATES. */
/*             IF NCE=0 THESE MAY BE DUMMY ADDRESSES. */

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

/*    (IF IPCOND=1 THE FOLLOWING REMARKS PERTAIN TO C*A RATHER THAN A.) */

/*    SPPCG IMPLEMENTS THE PRECONDITIONED CONJUGATE GRADIENT METHOD, */
/*    WITH A DYNAMICALLY COMPUTED OPTIMAL POLYNOMIAL PRECONDITIONER, */
/*    USING THE OMIN ALGORITHM GIVEN BY: */

/*                   R0 = B - A*X0 */
/*                   H0 = C(A)*R0 */
/*                   P0 = H0 */
/*                   AP = A*P */
/*                   ALPHA = <R,H>/<AP,P> */
/*                   XNEW = X + ALPHA*P */
/*                   RNEW = R - ALPHA*AP */
/*                   HNEW = C(A)*R */
/*                   BETA = <RNEW,HNEW>/<R,H> */
/*                   PNEW = HNEW + BETA*P */

/*    THIS ALGORITHM IS GUARANTEED TO CONVERGE IF BOTH A AND C(A) ARE */
/*    SYMMETRIC POSITIVE DEFINITE.   MATHEMATICALLY, IF C(A)*A HAS M */
/*    DISTINCT EGVALS, THE ALGORITHM WILL CONVERGE IN AT MOST M STEPS. */
/*    AT EACH STEP THE ALGORITHM MINIMIZES THE A-NORM OF THE ERROR. THAT */
/*    IS, IT MINIMIZES <A*E,E>. */

/*    THE CODE DYNAMICALLY SEEKS THE OPTIMAL PRECONDITIONING POLY, C(A). */
/*    THIS IS DONE AS FOLLOWS.  EVERY ICYCLE STEPS ESTIMATES FOR THE MIN */
/*    (CL) AND MAX (CU) EGVALS OF C(A)A ARE COMPUTED FROM AN ORTHOGONAL */
/*    SECTION OF C(A)A; SEE THE REFERENCES BELOW.  (THE LARGEST POSSIBLE */
/*    ORDER IS ICYCLE*NCE, WHERE NCE IS THE MAXIMUM NUMBER OF ADAPTIVE */
/*    CALLS.)  ONCE CL AND CU ARE COMPUTED, NEW ESTIMATES FOR AA AND BB */
/*    ARE DETERMINED.  IF THE NEW CONVERGENCE FACTOR IS SMALLER THAN THE */
/*    CURRENT CF, THE ITERATION IS RESTARTED, USING THE NEW AA AND BB. */
/*    OTHERWISE THE ITERATION CONTINUES. */

/*    WHEN THE USER SELECTS THE STOPPING CRITERION OPTION ISTOP=0, THEN */
/*    THE CODE STOPS WHEN COND(C(A)A)*(HNORM/H0NORM) .LE. ERRTOL, THEREBY */
/*    ATTEMPTING TO GUARANTEE THAT (FINAL RELATIVE ERROR) .LE. ERRTOL. */
/*    A NEW COND(C(A)A) ESTIMATE IS COMPUTED FROM CL AND CU.  IF NCE=0, */
/*    NO CONDITION ESTIMATES ARE COMPUTED.  IN THIS CASE, THE CODE STOPS */
/*    WHEN COND0*(HNORM/H0NORM) .LE. ERRTOL, WHERE COND0 IS THE CONDITION */
/*    NUMBER ESTIMATE FOR C(A)A OBTAINED FROM THE INITIAL AA AND BB. */

/*    THIS STOPPING CRITERION WAS IMPLEMENTED BY A.J. ROBERTSON, III */
/*    (DEPT. OF MATHEMATICS, UNIV. OF COLORADO AT DENVER).  QUESTIONS */
/*    MAY BE DIRECTED TO HIM OR TO ONE OF THE AUTHORS. */

/*    SPPCG IS ONE ROUTINE IN A PACKAGE OF CG CODES; THE OTHERS ARE: */

/*    SCGDRV : AN INTERFACE TO ANY ROUTINE IN THE PACKAGE */
/*    SCG    : CONJUGATE GRADIENTS ON A, A SPD (CGHS) */
/*    SCR    : CONJUGATE RESIDUALS ON A, A SPD (CR) */
/*    SCRIND : CR ON A, A SYMMETRIC (CRIND) */
/*    SPCG   : PRECONITIONED CG ON A, A AND C SPD (PCG) */
/*    SCGNR  : CGHS ON AT*A, A ARBITRARY (CGNR) */
/*    SCGNE  : CGHS ON A*AT, A ARBITRARY (CGNE) */
/*    SPCGNR : CGNR ON A*C, A AND C ARBITRARY (PCGNR) */
/*    SPCGNE : CGNE ON C*A, A AND C ARBITRARY (PCGNE) */
/*    SPPCG  : POLYNOMIAL PCG ON A, A AND C SPD (PPCG) */
/*    SPCGCA : CGHS ON C(A)*A, A AND C SPD (PCGCA) */

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

/* ***ROUTINES CALLED  SDPCHB,SCBFIX,SONEST,R1MACH,SAXPY,SCGCHK,SCKCHB, */
/*                    SDOT,SNRM2 */
/* ***END PROLOGUE  SPPCG */

/*     *** DECLARATIONS *** */
/* CCCCCIMPLICIT  DOUBLE PRECISION(A-H,O-Z) */

/* ***FIRST EXECUTABLE STATEMENT  SPPCG */
    /* Parameter adjustments */
    --w2;
    --w1;
    --h__;
    --r__;
    --b;
    --x;
    --iparam;
    --rparam;
    --iwork;
    --w3;
    --w4;
    --d__;
    --e;

    /* Function Body */
/* L1: */

/*     *** CHECK THE INPUT PARAMETERS *** */
    iounit = iparam[5];
    if (iounit > 0) {
	io___2.ciunit = iounit;
	s_wsfe(&io___2);
	e_wsfe();
    }
    scgchk_(&iparam[1], &rparam[1], n);
    sckchb_(&iparam[1], &rparam[1], &pegmin, &pegmax, &condca);
    if (iounit > 0) {
	if (ipcond == 0) {
	    io___7.ciunit = iounit;
	    s_wsfe(&io___7);
	    e_wsfe();
	}
	if (ipcond == 1) {
	    io___8.ciunit = iounit;
	    s_wsfe(&io___8);
	    e_wsfe();
	}
    }

/*     *** INITIALIZE INPUT PARAMETERS *** */
    ipcond = iparam[7];
    istop = iparam[8];
    itmax = iparam[9];
    icycle = iparam[31];
    nce = iparam[32];
    kmax = icycle * nce;
    ndeg = iparam[34];
    nchb = ndeg + 1;
    errtol = rparam[1];
    aa = rparam[32];
    bb = rparam[33];

/*     *** INITIALIZE ITERS, E(1), ERRED, R *** */
    e[1] = 0.f;
    erred = 1.f;
    (*matvec)(&c__0, a, ia, &wdummy, &x[1], &r__[1], n);
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	r__[i__] = b[i__] - r__[i__];
/* L15: */
    }
    iters = 0;

/*     *** INITIALIZE ITERATION PARAMETERS *** */
L20:
    kstep = 0;
    d__[1] = 0.f;
    errtol *= erred;

/*     *** COMPUTE STOPPING CRITERION DENOMINATOR *** */
    denom = 1.f;
    if (istop == 2) {
	denom = snrm2_(n, &b[1], &c__1);
    }
    if (istop == 0 || istop == 4) {
	if (ipcond == 0) {
	    scbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &
		    bb, &nchb, &b[1], &h__[1], &w1[1], &w2[1], &w3[1], n);
	    denom = sqrt(sdot_(n, &b[1], &c__1, &h__[1], &c__1));
	} else {
	    (*pcondl)(&c__0, q, iq, &wdummy, &b[1], &w4[1], n);
	    scbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &
		    bb, &nchb, &w4[1], &h__[1], &w1[1], &w2[1], &w3[1], n);
	    denom = sqrt(sdot_(n, &b[1], &c__1, &h__[1], &c__1));
	}
    }

/*     *** TELL MSSTOP WHETHER OR NOT I AM SUPPLYING THE STOPPING QUANTITY *** */
    if (istop == 1 || istop == 2) {
	ido = 0;
    } else {
	ido = 1;
    }

/*     *** COMPUTE INITIAL H *** */
    if (ipcond == 0) {
	scbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &bb, &
		nchb, &r__[1], &b[1], &w1[1], &w2[1], &w3[1], n);
    } else {
	(*pcondl)(&c__0, q, iq, &wdummy, &r__[1], &w4[1], n);
	scbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &bb, &
		nchb, &w4[1], &b[1], &w1[1], &w2[1], &w3[1], n);
    }
    s0norm = sqrt(sdot_(n, &r__[1], &c__1, &b[1], &c__1));
    snorm = s0norm;
    if (iounit > 0) {
	io___28.ciunit = iounit;
	s_wsfe(&io___28);
	do_fio(&c__1, (char *)&s0norm, (ftnlen)sizeof(real));
	e_wsfe();
    }

/*     *** CHECK THE INITIAL RESIDUAL *** */
    jstop = msstop_(&istop, &iters, &itmax, &errtol, &stptst, ierror, &r__[1],
	     &sdumm, &zdumm, n, &rndumm, &s0norm, &s0norm, &denom, &condca, &
	    ido);
    if (jstop == 1) {
	goto L90;
    }

/*     *** UPDATE ITERS, KSTEP AND COMPUTE A*P *** */
L30:
    ++iters;
    ++kstep;
    (*matvec)(&c__0, a, ia, &wdummy, &b[1], &h__[1], n);

/*     *** COMPUTE NEW X *** */
/* Computing 2nd power */
    r__1 = snorm;
    alpha = r__1 * r__1 / sdot_(n, &h__[1], &c__1, &b[1], &c__1);
    saxpy_(n, &alpha, &b[1], &c__1, &x[1], &c__1);

/*     *** COMPUTE NEW R AND H *** */
    r__1 = -alpha;
    saxpy_(n, &r__1, &h__[1], &c__1, &r__[1], &c__1);
    if (ipcond == 0) {
	scbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &bb, &
		nchb, &r__[1], &h__[1], &w1[1], &w2[1], &w3[1], n);
    } else {
	(*pcondl)(&c__0, q, iq, &wdummy, &r__[1], &w4[1], n);
	scbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &bb, &
		nchb, &w4[1], &h__[1], &w1[1], &w2[1], &w3[1], n);
    }
    oldsnm = snorm;
    snorm = sqrt(sdot_(n, &r__[1], &c__1, &h__[1], &c__1));
    if (iounit > 0) {
	io___36.ciunit = iounit;
	s_wsfe(&io___36);
	do_fio(&c__1, (char *)&iters, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&snorm, (ftnlen)sizeof(real));
	r__1 = snorm / s0norm;
	do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	e_wsfe();
    }

/*     *** TEST TO HALT *** */
    jstop = msstop_(&istop, &iters, &itmax, &errtol, &stptst, ierror, &r__[1],
	     &sdumm, &zdumm, n, &rndumm, &snorm, &snorm, &denom, &condca, &
	    ido);
    if (jstop == 1) {
	goto L90;
    }

/*     *** CONDITION ESTIMATE *** */
/* Computing 2nd power */
    r__1 = snorm / oldsnm;
    beta = r__1 * r__1;
    if (iters <= kmax) {
/*        *** SAVE PARAMETERS *** */
	ksp1 = kstep + 1;
	ralpha = 1.f / alpha;
	d__[kstep] += ralpha;
	d__[ksp1] = beta * ralpha;
	e[ksp1] = -sqrt(beta) * ralpha;
	if (iters % icycle == 0) {
	    erred = s0norm / (snorm * condca);
	    if (iounit > 0) {
		io___40.ciunit = iounit;
		s_wsfe(&io___40);
		e_wsfe();
	    }
	    sonest_(&iounit, &d__[1], &e[1], &w1[1], &w2[1], &iwork[1], &
		    kstep, &pegmin, &pegmax, &condca);
	    ereps = errtol * erred;
	    sdpchb_(&iounit, &aa, &bb, &nchb, &pegmin, &pegmax, &condca, &
		    ereps, &iadapt);
	    if (iadapt == 2) {
		goto L20;
	    }
	}
    }

/*     *** COMPUTE NEW P *** */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b[i__] = h__[i__] + beta * b[i__];
/* L45: */
    }

/*     *** RESUME CG ITERATION *** */
    goto L30;

/*     *** RETURN UPDATED PARAMETERS *** */
L90:
    iparam[10] = iters;
    rparam[2] = stptst;
    rparam[31] = condca;
    rparam[34] = snorm / s0norm;
    rparam[32] = aa;
    rparam[33] = bb;

    return 0;
} /* sppcg_ */

