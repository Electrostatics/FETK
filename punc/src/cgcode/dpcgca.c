/* ./src_f77/dpcgca.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;

/* Subroutine */ int dpcgca_(S_fp matvec, S_fp pcondl, doublereal *a, integer 
	*ia, doublereal *x, doublereal *b, integer *n, doublereal *q, integer 
	*iq, integer *iparam, doublereal *rparam, integer *iwork, doublereal *
	p, doublereal *h__, doublereal *cap, doublereal *w1, doublereal *w2, 
	doublereal *w3, doublereal *d__, doublereal *e, integer *ierror)
{
    /* Format strings */
    static char fmt_5[] = "(\002 THE METHOD IS POLYNOMIAL PCGCA\002,/)";
    static char fmt_10[] = "(\002 RESID  = 2-NORM OF C(A)R\002,/,\002 RELRSD"
	    " = RESID / INITIAL RESID\002,/)";
    static char fmt_11[] = "(\002 RESID  = 2-NORM OF C(C*A)C*R\002,/,\002 RE"
	    "LRSD = RESID / INITIAL RESID\002,/)";
    static char fmt_25[] = "(\002 INITIAL RESID = \002,d12.5,/)";
    static char fmt_40[] = "(\002 ITERS = \002,i5,4x,\002RESID = \002,d12.5,"
	    "4x,\002RELRSD = \002,d12.5)";
    static char fmt_45[] = "(/,\002 NEW ESTIMATES FOR C(A)*A:\002)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    double sqrt(doublereal);
    integer do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static integer i__;
    static doublereal aa, bb;
    static integer nce, ido, ksp1, nchb;
    static doublereal beta;
    static integer ndeg;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static integer kmax;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    static doublereal alpha, erred, denom;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    static doublereal ereps;
    static integer itmax;
    static doublereal hnorm, rdumm, sdumm;
    static integer iters, kstep;
    static doublereal zdumm;
    static integer istop, jstop;
    static doublereal h0norm;
    extern /* Subroutine */ int dckchb_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *), dcgchk_(integer *, doublereal *, 
	    integer *), ddpchb_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     integer *);
    static doublereal condca;
    extern /* Subroutine */ int dcbfix_(S_fp, S_fp, doublereal *, integer *, 
	    doublereal *, integer *, integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *);
    static integer iadapt;
    static doublereal ralpha;
    static integer icycle, ipcond;
    static doublereal pegmin, pegmax, oldhnm;
    extern /* Subroutine */ int donest_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *);
    extern integer mdstop_(integer *, integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, integer *);
    static integer iounit;
    static doublereal errtol, wdummy, stptst;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 0, fmt_5, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___8 = { 0, 0, 0, fmt_11, 0 };
    static cilist io___28 = { 0, 0, 0, fmt_25, 0 };
    static cilist io___36 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___40 = { 0, 0, 0, fmt_45, 0 };


/* ***BEGIN PROLOGUE  DPCGCA */
/* ***DATE WRITTEN   860715   (YYMMDD) */
/* ***REVISION DATE  900210   (YYMMDD) */
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
/*            DYNAMICALLY FOUND.  MANTEUFFEL AND SAYLOR'S PCGCA IS */
/*            USED; A MUST BE SPD. */

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

/*    PCONDL   EXTERNAL SUBROUTINE PCONDL(JOB,Q,IQ,W,X,Y,N) */
/*             PCONDL IMPLEMENTS A USER SUPPLIED LEFT-PRECONDITIONER. */
/*             IF PRECONDITIONING IS SPECIFIED BY THE USER, THEN THE */
/*             USER MUST PROVIDE A SUBROUTINE HAVING THE SPECIFED */
/*             PARAMETER LIST.  THE SUBROUTINE MUST RETURN THE PRODUCT */
/*             (OR A RELATED COMPUTATION; SEE BELOW) Y=C*X, WHERE C */
/*             IS A PRECONDITIONING MATRIX.  THE MATRIX C IS */
/*             REPRESENTED BY THE WORK ARRAYS Q AND IQ, DEDCRIBED */
/*             BELOW.  THE INTEGER PARAMETER JOB SPECIFIES THE PRODUCT */
/*             TO BE COMPUTED: */
/*                  JOB=0    Y=C*X */
/*                  JOB=1    Y=CT*X */
/*                  JOB=2    Y=W - C*X */
/*                  JOB=3    Y=W - CT*X. */
/*             IN THE ABOVE, CT DENOTES C-TRANSPOSE.  NOTE THAT */
/*             ONLY THE VALUES OF JOB=0,1 ARE REQUIRED FOR CGCODE. */
/*             THE ROUTINES DPCG, DPCGNR, DPCGNE, DPPCG, AND DPCGCA IN */
/*             CGCODE REQUIRE JOB=0; THE ROUTINES DPCGNR AND DPCGNE ALSO */
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

/*    Q        DBLE ARRAY ADDRESS. */
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

/*             IPARAM(34) = NDEG */
/*             WHEN USING THE CONJUGATE GRADIENT ROUTINES DPPCG AND */
/*             DPCGCA, NDEG SPECIFIES THE DEGREE OF THE PRECONDITIONING */
/*             POLYNOMIAL TO BE USED IN THE ADAPTIVE POLYNOMIAL */
/*             PRECONDITIONING ROUTINES. */

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

/*             RPARAM(32) = AA */
/*             INITIAL ESTIMATE OF THE SMALLEST EIGENVALUE OF THE */
/*             SYSTEM MATRIX.  WHEN USING THE CONJUGATE GRADIENT */
/*             ROUTINES DPPCG AND DPCGCA, AA IS USED IN THE ADAPTIVE */
/*             POLYNOMIAL PRECONDITIONING ROUTINES FOR FORMING THE */
/*             OPTIMAL PRECONDITIONING POLYNOMIAL. */

/*             RPARAM(33) = BB */
/*             INITIAL ESTIMATE OF THE LARGEST EIGENVALUE OF THE */
/*             SYSTEM MATRIX.  WHEN USING THE CONJUGATE GRADIENT */
/*             ROUTINES DPPCG AND DPCGCA, BB IS USED IN THE ADAPTIVE */
/*             POLYNOMIAL PRECONDITIONING ROUTINES FOR FORMING THE */
/*             OPTIMAL PRECONDITIONING POLYNOMIAL. */

/*    P,H,CAP  DBLE(N), DBLE(N), DBLE(N). */
/*             WORK ARRAYS FOR THE CG ITERATION. */

/*    W1,W2    DBLE(N), DBLE(N). */
/*             WORK ARRAYS FOR EXECUTING THE POLYNOMIAL PRECONDITIONING. */

/*    W3       DBLE(N). */
/*             WORK ARRAY FOR EXECUTING THE INNER PRECONDITIONING.  THIS */
/*             IS A DUMMY ARGUMENT IF IPCOND=0. */

/*    D,E      DBLE(ICYCLE*NCE + 1), DBLE(ICYCLE*NCE + 1). */
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

/*    (IF IPCOND=1 THE FOLLOWING REMARKS PERTAIN TO C*A RATHER THAN A.) */

/*    DPCGCA IMPLEMENTS THE PRECONDITIONED CONJUGATE GRADIENT METHOD */
/*    OF MANTEUFFEL AND SAYLOR, WITH A DYNAMICALLY COMPUTED OPTIMAL */
/*    POLYNOMIAL PRECONDITIONER, USING THE OMIN ALGORITHM GIVEN BY: */

/*                   H0 = C(A)*R0 */
/*                   P0 = H0 */
/*                   CAP = C(A)*A*P */
/*                   ALPHA = <H,H>/<CAP,P> */
/*                   XNEW = X + ALPHA*P */
/*                   HNEW = H - ALPHA*CAP */
/*                   BETA = <HNEW,HNEW>/<H,H> */
/*                   PNEW = HNEW + BETA*P */

/*    THIS IS SIMPLY CG ON C(A)A.  IT IS GUARANTEED TO CONVERGE IF C(A)A */
/*    IS SYMMETRIC POSITIVE DEFINITE.  IF A IS SPD, AND NDEG IS EVEN, */
/*    C(A)A IS SPD.  MATHEMATICALLY, IF C(A)A HAS M DISTINCT EGVALS, THE */
/*    ALGORITHM CONVERGES IN AT MOST M STEPS. AT EACH STEP THE ALGORITHM */
/*    MINIMIZES THE C(A)A-NORM OF THE ERROR.  THAT IS, IT APPROXIMATELY */
/*    MINIMIZES THE 2-NORM OF THE ERROR. */

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

/*    DPCGCA IS ONE ROUTINE IN A PACKAGE OF CG CODES; THE OTHERS ARE: */

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

/* ***ROUTINES CALLED  DDPCHB,DCBFIX,DONEST,D1MACH,DAXPY,DCGCHK,DCKCHB, */
/*                    DDOT,DNRM2 */
/* ***END PROLOGUE  DPCGCA */

/*     *** DECLARATIONS *** */

/* ***FIRST EXECUTABLE STATEMENT  DPCGCA */
    /* Parameter adjustments */
    --w2;
    --w1;
    --cap;
    --h__;
    --p;
    --b;
    --x;
    --iparam;
    --rparam;
    --iwork;
    --w3;
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
    dcgchk_(&iparam[1], &rparam[1], n);
    dckchb_(&iparam[1], &rparam[1], &pegmin, &pegmax, &condca);
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

/*     *** INITIALIZE ITERS, E(1), ERRED *** */
    e[1] = 0.;
    erred = 1.;
    iters = 0;

/*     *** INITIALIZE ITERATION PARAMETERS *** */
L15:
    kstep = 0;
    d__[1] = 0.;
    errtol *= erred;

/*     *** COMPUTE STOPPING CRITERION DENOMINATOR *** */
    denom = 1.;
    if (istop == 2) {
	denom = dnrm2_(n, &b[1], &c__1);
    }
    if (istop == 0 || istop == 4) {
	if (ipcond == 0) {
	    dcbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &
		    bb, &nchb, &b[1], &h__[1], &w1[1], &w2[1], &w3[1], n);
	    denom = sqrt(ddot_(n, &h__[1], &c__1, &h__[1], &c__1));
	} else {
	    (*pcondl)(&c__0, q, iq, &wdummy, &b[1], &p[1], n);
	    dcbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &
		    bb, &nchb, &p[1], &h__[1], &w1[1], &w2[1], &w3[1], n);
	    denom = sqrt(ddot_(n, &h__[1], &c__1, &h__[1], &c__1));
	}
    }

/*     *** TELL MDSTOP WHETHER OR NOT I AM SUPPLYING THE STOPPING QUANTITY *** */
    if (istop == 1 || istop == 2) {
	ido = 0;
    } else {
	ido = 1;
    }

/*     *** COMPUTE INITIAL H *** */
    (*matvec)(&c__0, a, ia, &wdummy, &x[1], &cap[1], n);
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	cap[i__] = b[i__] - cap[i__];
/* L20: */
    }
    if (ipcond == 0) {
	dcbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &bb, &
		nchb, &cap[1], &h__[1], &w1[1], &w2[1], &w3[1], n);
    } else {
	(*pcondl)(&c__0, q, iq, &wdummy, &cap[1], &p[1], n);
	dcbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &bb, &
		nchb, &p[1], &h__[1], &w1[1], &w2[1], &w3[1], n);
    }
    dcopy_(n, &h__[1], &c__1, &p[1], &c__1);
    h0norm = dnrm2_(n, &h__[1], &c__1);
    hnorm = h0norm;
    if (iounit > 0) {
	io___28.ciunit = iounit;
	s_wsfe(&io___28);
	do_fio(&c__1, (char *)&h0norm, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }

/*     *** CHECK THE INITIAL RESIDUAL *** */
    jstop = mdstop_(&istop, &iters, &itmax, &errtol, &stptst, ierror, &rdumm, 
	    &sdumm, &zdumm, n, &h0norm, &h0norm, &h0norm, &denom, &condca, &
	    ido);
    if (jstop == 1) {
	goto L90;
    }

/*     *** COMPUTE INITIAL CAP *** */
    dcbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &bb, &
	    nchb, &p[1], &w1[1], &cap[1], &w2[1], &w3[1], n);
    if (ipcond == 0) {
	(*matvec)(&c__0, a, ia, &wdummy, &w1[1], &cap[1], n);
    } else {
	(*matvec)(&c__0, a, ia, &wdummy, &w1[1], &w2[1], n);
	(*pcondl)(&c__0, q, iq, &wdummy, &w2[1], &cap[1], n);
    }

/*     *** UPDATE ITERS AND KSTEP *** */
L35:
    ++iters;
    ++kstep;

/*     *** COMPUTE NEW X AND H *** */
/* Computing 2nd power */
    d__1 = hnorm;
    alpha = d__1 * d__1 / ddot_(n, &cap[1], &c__1, &p[1], &c__1);
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	x[i__] += alpha * p[i__];
	h__[i__] -= alpha * cap[i__];
/* L37: */
    }

/*     *** CHECK NEW H *** */
    oldhnm = hnorm;
    hnorm = dnrm2_(n, &h__[1], &c__1);
    if (iounit > 0) {
	io___36.ciunit = iounit;
	s_wsfe(&io___36);
	do_fio(&c__1, (char *)&iters, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hnorm, (ftnlen)sizeof(doublereal));
	d__1 = hnorm / h0norm;
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }

/*     *** TEST TO HALT *** */
    jstop = mdstop_(&istop, &iters, &itmax, &errtol, &stptst, ierror, &rdumm, 
	    &sdumm, &zdumm, n, &hnorm, &hnorm, &hnorm, &denom, &condca, &ido);
    if (jstop == 1) {
	goto L90;
    }

/*     *** CONDITION ESTIMATE *** */
/* Computing 2nd power */
    d__1 = hnorm / oldhnm;
    beta = d__1 * d__1;
    if (iters <= kmax) {
/*        *** SAVE PARAMETERS *** */
	ksp1 = kstep + 1;
	ralpha = 1. / alpha;
	d__[kstep] += ralpha;
	d__[ksp1] = beta * ralpha;
	e[ksp1] = -sqrt(beta) * ralpha;
	if (iters % icycle == 0) {
	    erred = h0norm / (hnorm * condca);
	    if (iounit > 0) {
		io___40.ciunit = iounit;
		s_wsfe(&io___40);
		e_wsfe();
	    }
	    donest_(&iounit, &d__[1], &e[1], &w1[1], &w2[1], &iwork[1], &
		    kstep, &pegmin, &pegmax, &condca);
	    ereps = errtol * erred;
	    ddpchb_(&iounit, &aa, &bb, &nchb, &pegmin, &pegmax, &condca, &
		    ereps, &iadapt);
	    if (iadapt == 2) {
		goto L15;
	    }
	}
    }

/*     *** COMPUTE NEW P, C(A)A*P *** */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	p[i__] = h__[i__] + beta * p[i__];
/* L50: */
    }
    dcbfix_((S_fp)matvec, (S_fp)pcondl, a, ia, q, iq, &ipcond, &aa, &bb, &
	    nchb, &p[1], &w1[1], &cap[1], &w2[1], &w3[1], n);
    if (ipcond == 0) {
	(*matvec)(&c__0, a, ia, &wdummy, &w1[1], &cap[1], n);
    } else {
	(*matvec)(&c__0, a, ia, &wdummy, &w1[1], &w2[1], n);
	(*pcondl)(&c__0, q, iq, &wdummy, &w2[1], &cap[1], n);
    }

/*     *** RESUME CG ITERATION *** */
    goto L35;

/*     *** RETURN UPDATED PARAMETERS *** */
L90:
    iparam[10] = iters;
    rparam[2] = stptst;
    rparam[31] = condca;
    rparam[34] = hnorm / h0norm;
    rparam[32] = aa;
    rparam[33] = bb;

    return 0;
} /* dpcgca_ */

