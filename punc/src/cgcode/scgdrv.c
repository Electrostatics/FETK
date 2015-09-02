/* ./src_f77/scgdrv.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* $Id: scgdrv.c,v 1.3 2006/06/12 22:52:01 mholst Exp $ */
/* $Log: scgdrv.c,v $
/* Revision 1.3  2006/06/12 22:52:01  mholst
/* *** empty log message ***
/* */
/* Revision 1.1  2006/06/08 08:56:27  mholst */
/* *** empty log message *** */

/* Revision 1.19  90/05/19  19:07:50  holst */
/* (1) CRIND documentation fix: algorithm section. */
/* (2) General documentation fix throughout the entire package, to make more */
/*     consistent with the CgCode report. */

/* Note: now ready for initial distribution. */

/* Revision 1.18  90/05/12  18:08:39  holst */
/* A fix in CGDRV to make the code consistent with the CgCode Report. */
/* Basically, CRIND was moved from ICG=10 to ICG=3 to be more logically */
/* correct (CR is ICG=2), and to be consistent with the report. */
/* After a check on some of the documentation, (specifically the algorithm */
/* section of CRIND, and the stopping crierion code/doc for all routines) */
/* we will be ready for the initial release of the code. */

/* Revision 1.17  90/03/18  16:47:35  holst */
/* Changed the one instance of "FLOAT" to "REAL" to make conversion to */
/* double precision more uniform and simple. */

/* Revision 1.16  90/03/18  16:02:48  holst */
/* Simply added the following line to each subroutine to make conversion */
/* to double precision automatic during development: */
/* CCCCCCIMPLICIT  DOUBLE PRECISION(A-H,O-Z) */

/* Have written a script file that uncomments this, and performs all of */
/* the other necessary conversions to create a double precision version */
/* of the cgcode package from the single precision version. */

/* Revision 1.15  90/03/18  14:22:59  holst */
/* Just updated the comments to the last revision */

/* Revision 1.14  90/03/18  14:03:34  holst */
/* Cleaned up internal constants and intrinsic function calls to prepare */
/* for development of a double precision version of the code.  Specifically */
/* I changed: */

/* (1) changed constants from:  x.y    to:   x.yE0 */
/* (2) calls to MAX were changed to calls to AMAX1 */
/* (3) calls to MIN were changed to calls to AMIN1 */
/* (4) calls to LOG were changed to calls to ALOG */

/* To change to double precision now simple involves: */

/* (1) change constants from:  x.yEz   to:   z.yDz */
/* (2) calls to AMAX1  will be changed to DMAX1 */
/* (3) calls to AMIN1  will be changed to DMIN1 */
/* (4) calls to ALOG   will be changed to DLOG */
/* (5) calls to R1MACH will be changed to D1MACH */
/* (6) calls to SNRM2  will be changed to DNRM2 */
/* (7) calls to SCOPY  will be changed to DCOPY */
/* (8) calls to SDOT   will be changed to DDOT */
/* (9) calls to SAXPY  will be changed to DAXPY */
/* (10)calls to SSCAL  will be changed to DSCAL */
/* (11)calls to SQRT   will be changed to DSQRT */
/* (12)format statements changed from xxExx to xxDxx */
/* (13)the line added to each routine: IMPLICIT DOUBLE PRECISION(A-H,O-Z) */

/* Revision 1.13  90/02/20  00:37:39  holst */
/* Add SCR into package, making for 10 cg methods. */
/* (Steve A. wants to provide both SCR and SCRIND; now done.) */
/* Documentation of package also updated to include SCR. */

/* Revision 1.12  90/02/19  10:27:48  holst */
/* Document/redo a little on MSTOP; SPPCG still needs work.  Others are */
/* ok I think.  See comments on last revision about SCRIND. */

/* Revision 1.11  90/02/18  17:27:50  holst */
/* (1) Cosmetic fixes; documentation, output, etc. */
/* (2) Redo MSTOP; more fully implement all stopping criterion for 9 routines. */
/* (3) All stopping criterion implemented (I think) except for SPPCG. */
/*     (Should we add CONEST to SCRIND?  Should we add a SPCRIND?) */
/*     (There are other/better ways to implement MSTOP; look at?) */

/* Revision 1.10  90/02/14  21:34:12  holst */
/* Small fix to condition estimate code in SPPCG and SPCGCA */
/* (allow ADPCHB to function even if not using ISTOP=0) */

/* Revision 1.9  90/02/14  21:21:22  holst */
/* (1) The whole package is now consistently documented. */
/* (2) All 10 of the CGCODE subroutines now match the proposed standard, */
/*     except that the 9 subordinate routines deviate in two ways: */
/*     (a) uneccessary args not passed (PCONDL not passed to SCG, etc.) */
/*     (b) rwork parsed in SCGDRV so that the 9 subroutines are passed */
/*         seperate vectors to make for cleaner coding. */
/*     Except for those two differences, the remainder of the arguments */
/*     to the 9 routines conform to the proposed standard. */
/* (3) SCGDRV conforms completely to the proposed standard. */
/* (4) Up to now, identical results are obtained on the regression tests */
/*     as were obtained in revision 1.1 (before any changes were made.) */
/* (5) What remains:   MSTOP and stopping criterion questions. */
/*     Give the code to Dr. Steve Ashby for comments. */

/* Revision 1.8  90/02/14  00:11:42  holst */
/* (1) Change parameter lists to individual 9 cg routines to more closely */
/*     conform to the proposed standard */
/* (2) Change indexes into RPARAM and IPARAM inside all routines that */
/*     access them to conform to SCGDRV requirements; eliminate having */
/*     to do translation. */
/* (3) Documentation is now out of date for the 9 cg routines as far */
/*     as parameter descriptions; fix tomorrow. */
/* (4) Good night. */

/* Revision 1.7  90/02/13  17:41:12  holst */
/* Simple fix to output format; Problem created by me when changing output */
/* terms like IMAX to ITMAX (different lengths). */

/* Revision 1.6  90/02/13  16:50:18  holst */
/* Bug fix in stopping criterion in routine SPCGNR. */

/* Revision 1.5  90/02/13  13:04:33  holst */
/* (1) Stopping criterion has been isolated in each of the nine routines */
/*     now; all of the routines use MSTOP. */
/* (2) Some of the stopping criterion need to be looked at in detail */
/*     (specifically SCRIND, SPPCG, and SPCGCA). */
/* (3) Ready for Steve Ashby to take a look at. */

/* Revision 1.4  90/02/12  23:31:11  holst */
/* In this revision, we have completed: */
/* (1) The stopping criterion has been modularized and replaced with */
/*     calls to MSTOP in 7 of the 9 cgcode routines;  SPPCG and SPCGCA */
/*     are buggy and a little difficult.  The next revision will deal */
/*     simply with implementing MSTOP for SPPCG and SPCGCA. */

/* Revision 1.3  90/02/12  03:16:24  holst */
/* This revision accomplished the following: */
/* (1) SCGDRV now conforms to the iterative standard; mcgdrv has been */
/*     eliminated.  While the individual cgcode subroutines still do */
/*     not conform to the standard, the external routines of matvec, */
/*     pcondl, and pcondr do conform. */
/* (2) All documentation of SCGDRV is complete.  All documentation of */
/*     the individual cgcode routines remains complete (see 3) */
/* (3) MSTOP has been implemented, and is used in SCG.  It appears */
/*     to work.  The next revision will involve solely putting MSTOP */
/*     calls into all of the other 8 cgcode routines.  Once that has */
/*     been complete, we will check in the code to steve ashby for a */
/*     look see, and start on the writeup. */

/* Revision 1.2  90/02/10  21:24:48  holst */
/* The main changes were: */
/* (1) Fit cgcode, with new scrind, together with sppcg and spcgca, as one */
/*     package. */
/* (2) Update all comments to make sppcg, spcgca, and other routines */
/*     consistent. */
/* (3) Move mcgdrv standard interface to scgdrv into the mcgcode.f file, */
/*     ready to eliminate on next revision. */

/* Revision 1.1  90/02/04  12:01:04  holst */
/* Initial revision */

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* Subroutine */ int scgdrv_(U_fp matvec, U_fp pcondl, U_fp pcondr, real *a, 
	integer *ia, real *x, real *b, integer *n, real *q, integer *iq, real 
	*p, integer *ip, integer *iparam, real *rparam, integer *iwork, real *
	rwork, integer *ierror)
{
    /* Format strings */
    static char fmt_100[] = "(\002 USING CGCODE:  ICG=\002,i10)";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer icg, nce;
    extern /* Subroutine */ int scg_(U_fp, real *, integer *, real *, real *, 
	    integer *, integer *, real *, integer *, real *, real *, real *, 
	    real *, real *, integer *), scr_(U_fp, real *, integer *, real *, 
	    real *, integer *, integer *, real *, integer *, real *, real *, 
	    real *, real *, real *, real *, integer *), spcg_(U_fp, U_fp, 
	    real *, integer *, real *, real *, integer *, real *, integer *, 
	    integer *, real *, integer *, real *, real *, real *, real *, 
	    real *, integer *);
    static integer kmax;
    extern /* Subroutine */ int scgne_(U_fp, real *, integer *, real *, real *
	    , integer *, integer *, real *, integer *, real *, real *, real *,
	     real *, real *, integer *), scgnr_(U_fp, real *, integer *, real 
	    *, real *, integer *, integer *, real *, integer *, real *, real *
	    , real *, real *, real *, integer *), sppcg_(U_fp, U_fp, real *, 
	    integer *, real *, real *, integer *, real *, integer *, integer *
	    , real *, integer *, real *, real *, real *, real *, real *, real 
	    *, real *, real *, integer *), spcgca_(U_fp, U_fp, real *, 
	    integer *, real *, real *, integer *, real *, integer *, integer *
	    , real *, integer *, real *, real *, real *, real *, real *, real 
	    *, real *, real *, integer *);
    static integer icycle;
    extern /* Subroutine */ int spcgne_(U_fp, U_fp, real *, integer *, real *,
	     real *, integer *, real *, integer *, integer *, real *, integer 
	    *, real *, real *, real *, real *, real *, real *, integer *), 
	    scrind_(U_fp, real *, integer *, real *, real *, integer *, 
	    integer *, real *, integer *, real *, real *, real *, real *, 
	    real *, real *, real *, real *, integer *);
    static integer iolevl;
    extern /* Subroutine */ int spcgnr_(U_fp, U_fp, real *, integer *, real *,
	     real *, integer *, real *, integer *, integer *, real *, integer 
	    *, real *, real *, real *, real *, real *, real *, integer *);
    static integer iounit;

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 0, 0, fmt_100, 0 };


/* ***BEGIN PROLOGUE  SCGDRV */
/* ***DATE WRITTEN   860115   (YYMMDD) */
/* ***REVISION DATE  900210   (YYMMDD) */
/* ***CATEGORY NO. D2A4,D2B4 */
/* ***KEYWORDS  LINEAR SYSTEM,SPARSE,ITERATIVE,CONJUGATE GRADIENTS */
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
/* ***PURPOSE  THIS SUBROUTINE IS AN INTERFACE TO CGCODE, A PACKAGE OF */
/*            PRECONDITIONED CONJUGATE GRADIENT CODES.  THESE CODES */
/*            WILL SOLVE BOTH SYMMETRIC AND NONSYMMETRIC LINEAR SYSTEMS, */
/*            WITH OR WITHOUT PRECONDITIONING.  PRECONDITIONING INCLUDES */
/*            USER SUPPLIED PRECONDITIONERS AND/OR OR AUTOMATIC ADAPTIVE */
/*            POLYNOMIAL PRECONDITIONING.  SEE THE FLAGS ICG=IPARAM(13) */
/*            AND IPCOND=IPARAM(7) FOR DETAILS; ALSO SEE THE INDIVIDUAL */
/*            SUBROUTINES' PROLOGUES.  THE ARGUMENT LIST OF THIS */
/*            INTERFACE SUBROUTINE CONFORMS TO THE PROPOSED STANDARD FOR */
/*            ITERATIVE LINEAR SOLVERS (SEE THE BIBLIOGRAPHY FOR MORE */
/*            INFORMATION.) */
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

/*    PCONDR   DUMMY ARGUMENT (MANDATED BY PROPOSED STANDARD.) */

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

/*    P        DUMMY ARGUMENT (MANDATED BY PROPOSED STANDARD.) */

/*    IP       DUMMY ARGUMENT (MANDATED BY PROPOSED STANDARD.) */

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

/*             IPARAM(33) = ICG */
/*             A FLAG SPECIFYING THE METHOD TO BE USED.  BELOW C IS */
/*             THE USER'S PRECONDITIONING MATRIX, CT ITS TRANSPOSE, */
/*             AND AT IS THE TRANSPOSE OF A. */
/*                ICG=1 : CG    : CONJUGATE GRADIENTS ON A, A SPD (CGHS) */
/*                ICG=2 : CR    : CONJUGATE RESIDUALS ON A, A SPD */
/*                ICG=3 : CRIND : CR ON A, A SYMMETRIC */
/*                ICG=4 : PCG   : PRECONITIONED CG ON A, A AND C SPD */
/*                ICG=5 : CGNR  : CGHS ON AT*A, A ARBITRARY */
/*                ICG=6 : CGNE  : CGHS ON A*AT, A ARBITRARY */
/*                ICG=7 : PCGNR : CGNR ON A*C, A AND C ARBITRARY */
/*                ICG=8 : PCGNE : CGNE ON C*A, A AND C ARBITRARY */
/*                ICG=8 : PPCG  : POLYNOMIAL PCG ON A, A AND C SPD */
/*                ICG=10: PCGCA : CGHS ON C(A)*A, A AND C SPD */
/*             IF (1 .LT. ICG) OR (ICG .GT. 10) THEN ICG=1 IS ASSUMED. */

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

/*    RWORK    REAL(N1+N2). */
/*             WORK ARRAY, WHERE N1 AND N2 ARE INTEGERS SUCH THAT: */
/*                N1 .GE. 2*N               FOR SCG, SPCG, SCGNR, SCGNE. */
/*                N1 .GE. 3*N               FOR SCR, SPCGNR, SPCGNE. */
/*                N1 .GE. 5*N               FOR SCRIND */
/*                N1 .GE. 6*N               FOR SPPCG, SPCGCA. */
/*                N2 .GE. 2*ICYCLE*NCE+2    FOR SPPCG, SPCGCA */
/*                N2 .GE. 4*ICYCLE*NCE+2    FOR SCG, SCR, SPCG, SCGNR, */
/*                                              SCGNE, SPCGNR, SPCGNE, */
/*                                              SCRIND */
/*             THE N2 SPACE IS FOR COMPUTING CONDITION NUMBER ESTIMATES; */
/*             THE N1 SPACE IS FOR TEMPORARY VECTORS.  TO SAVE STORAGE */
/*             AND WORK, ICYCLE*NCE SHOULD BE MUCH LESS THAN N.  NOTE */
/*             THAT IF NCE = 0, N2 MAY BE SET TO ZERO. */

/*    IWORK    INTEGER(ICYCLE*NCE) */
/*             INTEGER WORK ARRAY FOR COMPUTING COND NUMBER ESTIMATES. */
/*             IF NCE = 0, THIS MAY BE A DUMMY ADDRESS. */

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

/*    EACH CG ALGORITHM IN THE PACKAGE IS AN INSTANCE OF AN ORTHOGONAL */
/*    ERROR METHOD.  THE GENERAL FORM OF SUCH A METHOD IS: */

/*                   P0 = S0 = C*R0 */
/*                   ALPHA = <B*E,P>/<B*P,P> */
/*                   XNEW = X + ALPHA*P */
/*                   RNEW = R - ALPHA*(A*P) */
/*                   SNEW = C*RNEW */
/*                   BETA = <B*SNEW,P>/<B*P,P> */
/*                   PNEW = SNEW - BETA*P */

/*    WHERE B IS A SYMMETRIC POSITIVE DEFINITE MATRIX AND C IS A */
/*    PRECONDITIONING MATRIX.  THE FOLLOWING CHOICES OF B AND C GIVE THE */
/*    ALGORITHMS IN THE PACKAGE.  THE QUANTITY MINIMIZED AT EACH STEP IS */
/*    ALSO LISTED. */

/*       ROUTINE        B MATRIX      C MATRIX     QUANTITY MINIMIZED */

/*        SCG              A             I             <A*E E> */
/*        SCR             A*A            I              <R, R> */
/*        SCRIND          A*A            I              <R, R> */
/*        SPCG             A             C             <A*E, E> */
/*        SCGNR           AT*A           AT             <R, R> */
/*        SCGNE            I             AT             <E, E> */
/*        SPCGNR          AT*A         C*CT*AT          <R, R> */
/*        SPCGNE           I           AT*CT*C          <E, E> */
/*        SPPCG            A           C(A)*C          <A*E, E> */
/*        SPCGCA         C(A)*A          C           <C(A)*A*E, E> */

/*    FOR SPECIFIC ALGORITHMS AND IMPLEMENTATION DETAILS SEE THE ROUTINE */
/*    OF INTEREST.  FOR MORE ON ORTHOGONAL ERROR METHODS SEE THE SECOND */
/*    REFERENCE BELOW. */

/*    WHEN THE USER SELECTS THE STOPPING CRITERION OPTION ISTOP=0, THEN */
/*    THE CODES ALL ATTEMPT TO GUARANTEE THAT */

/*            (FINAL ERROR) / (INITIAL ERROR)  .LE.  ERRTOL     (1) */

/*    THAT IS, THE CODES ATTEMPT TO REDUCE THE INITIAL ERROR BY ERRTOL. */
/*    (IF X0=0, THEN ERRTOL IS ALSO A BOUND FOR THE RELATIVE ERROR IN */
/*    THE COMPUTED SOLUTION, X.) TO SEE HOW (1) IS SATISFIED, CONSIDER */
/*    THE SCALED SYSTEM C*AX = C*P.   IF E(K) IS THE ERROR AT THE KTH */
/*    STEP, THEN WE HAVE */

/*                 E(K)/E(0)  .LE.  COND(CA) * S(K)/S(0) */

/*    WHERE S(K) = C*R(K) IS THE KTH SCALED RESIDUAL.  THE S VECTORS ARE */
/*    AVAILABLE FROM THE ITERATION.  IF WE CAN ESTIMATE COND(CA), THEN */
/*    EQUATION (1) IS SATISFIED WHEN */

/*                 COND(CA) * S(K)/S(0)  .LE.  ERRTOL. */

/*    AN ESTIMATE FOR COND(CA) IS OBTAINED BY COMPUTING THE MIN AND MAX */
/*    EIGENVALUES OF AN ORTHOGONAL SECTION OF C*A.  THIS IS DONE EVERY */
/*    ICYCLE STEPS.  THE LARGEST ORTHOG SECTION HAS ORDER ICYCLE*NCE, */
/*    WHERE NCE IS THE MAXIMUM NUMBER OF CONDITION ESTIMATES.  TO SAVE */
/*    STORAGE AND WORK, ICYCLE*NCE SHOULD BE MUCH LESS THAN N. IF NCE=0, */
/*    NO CONDITION ESTIMATES ARE COMPUTED.  IN THIS CASE, THE CODE STOPS */
/*    WHEN S(K)/S(0) .LE. ERRTOL.  SEE THE INDIVIDUAL SUBROUTINES' LONG */
/*    DESCRIPTIONS FOR DETAILS. */

/*    THIS STOPPING CRITERION WAS IMPLEMENTED BY A.J. ROBERTSON, III */
/*    (DEPT. OF MATHEMATICS, UNIV. OF COLORADO AT DENVER).  QUESTIONS */
/*    MAY BE DIRECTED TO HIM OR TO ONE OF THE AUTHORS. */

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

/* ***ROUTINES CALLED  SCG,SCRIND,SPCG,SCGNR,SCGNE,SPCGNR,SPCGNE, */
/*                    SPPCG,SPCGCA */
/* ***END PROLOGUE  SCGDRV */

/*     *** DECLARATIONS *** */
/* CCCCCIMPLICIT  DOUBLE PRECISION(A-H,O-Z) */

/* ***FIRST EXECUTABLE STATEMENT  SCGDRV */
    /* Parameter adjustments */
    --rwork;
    --iwork;
    --rparam;
    --iparam;
    --ip;
    --p;
    --iq;
    --q;
    --b;
    --x;
    --ia;
    --a;

    /* Function Body */
/* L1: */

/*     *** DECODE METHOD PARAMETER AND RWORK PARSING PARAMETERS *** */
    iounit = iparam[5];
    iolevl = iparam[6];
    icg = iparam[33];
    icycle = iparam[31];
    nce = iparam[32];
    kmax = icycle * nce;

/*     *** CALL THE APPROPRIATE CGCODE SUBROUTINE *** */
    if (iounit > 0 && iolevl > 0) {
	io___7.ciunit = iounit;
	s_wsfe(&io___7);
	do_fio(&c__1, (char *)&icg, (ftnlen)sizeof(integer));
	e_wsfe();
    }
    switch (icg) {
	case 1:  goto L11;
	case 2:  goto L12;
	case 3:  goto L13;
	case 4:  goto L14;
	case 5:  goto L15;
	case 6:  goto L16;
	case 7:  goto L17;
	case 8:  goto L18;
	case 9:  goto L19;
	case 10:  goto L20;
    }

L11:
    scg_((U_fp)matvec, &a[1], &ia[1], &x[1], &b[1], n, &iparam[1], &rparam[1],
	     &iwork[1], &rwork[1], &rwork[*n + 1], &rwork[(*n << 1) + 1], &
	    rwork[(*n << 1) + kmax + 2], &rwork[(*n << 1) + (kmax << 1) + 3], 
	    ierror);
    goto L99;

L12:
    scr_((U_fp)matvec, &a[1], &ia[1], &x[1], &b[1], n, &iparam[1], &rparam[1],
	     &iwork[1], &rwork[1], &rwork[*n + 1], &rwork[(*n << 1) + 1], &
	    rwork[*n * 3 + 1], &rwork[*n * 3 + kmax + 2], &rwork[*n * 3 + (
	    kmax << 1) + 3], ierror);
    goto L99;

L13:
    scrind_((U_fp)matvec, &a[1], &ia[1], &x[1], &b[1], n, &iparam[1], &rparam[
	    1], &iwork[1], &rwork[1], &rwork[*n + 1], &rwork[(*n << 1) + 1], &
	    rwork[*n * 3 + 1], &rwork[(*n << 2) + 1], &rwork[*n * 5 + 1], &
	    rwork[*n * 5 + kmax + 2], &rwork[*n * 5 + (kmax << 1) + 3], 
	    ierror);
    goto L99;

L14:
    spcg_((U_fp)matvec, (U_fp)pcondl, &a[1], &ia[1], &x[1], &b[1], n, &q[1], &
	    iq[1], &iparam[1], &rparam[1], &iwork[1], &rwork[1], &rwork[*n + 
	    1], &rwork[(*n << 1) + 1], &rwork[(*n << 1) + kmax + 2], &rwork[(*
	    n << 1) + (kmax << 1) + 3], ierror);
    goto L99;

L15:
    scgnr_((U_fp)matvec, &a[1], &ia[1], &x[1], &b[1], n, &iparam[1], &rparam[
	    1], &iwork[1], &rwork[1], &rwork[*n + 1], &rwork[(*n << 1) + 1], &
	    rwork[(*n << 1) + kmax + 2], &rwork[(*n << 1) + (kmax << 1) + 3], 
	    ierror);
    goto L99;

L16:
    scgne_((U_fp)matvec, &a[1], &ia[1], &x[1], &b[1], n, &iparam[1], &rparam[
	    1], &iwork[1], &rwork[1], &rwork[*n + 1], &rwork[(*n << 1) + 1], &
	    rwork[(*n << 1) + kmax + 2], &rwork[(*n << 1) + (kmax << 1) + 3], 
	    ierror);
    goto L99;

L17:
    spcgnr_((U_fp)matvec, (U_fp)pcondl, &a[1], &ia[1], &x[1], &b[1], n, &q[1],
	     &iq[1], &iparam[1], &rparam[1], &iwork[1], &rwork[1], &rwork[*n 
	    + 1], &rwork[(*n << 1) + 1], &rwork[*n * 3 + 1], &rwork[*n * 3 + 
	    kmax + 2], &rwork[*n * 3 + (kmax << 1) + 3], ierror);
    goto L99;

L18:
    spcgne_((U_fp)matvec, (U_fp)pcondl, &a[1], &ia[1], &x[1], &b[1], n, &q[1],
	     &iq[1], &iparam[1], &rparam[1], &iwork[1], &rwork[1], &rwork[*n 
	    + 1], &rwork[(*n << 1) + 1], &rwork[*n * 3 + 1], &rwork[*n * 3 + 
	    kmax + 2], &rwork[*n * 3 + (kmax << 1) + 3], ierror);
    goto L99;

L19:
    sppcg_((U_fp)matvec, (U_fp)pcondl, &a[1], &ia[1], &x[1], &b[1], n, &q[1], 
	    &iq[1], &iparam[1], &rparam[1], &iwork[1], &rwork[1], &rwork[*n + 
	    1], &rwork[(*n << 1) + 1], &rwork[*n * 3 + 1], &rwork[(*n << 2) + 
	    1], &rwork[*n * 5 + 1], &rwork[*n * 6 + 1], &rwork[*n * 6 + kmax 
	    + 2], ierror);
    goto L99;

L20:
    spcgca_((U_fp)matvec, (U_fp)pcondl, &a[1], &ia[1], &x[1], &b[1], n, &q[1],
	     &iq[1], &iparam[1], &rparam[1], &iwork[1], &rwork[1], &rwork[*n 
	    + 1], &rwork[(*n << 1) + 1], &rwork[*n * 3 + 1], &rwork[(*n << 2) 
	    + 1], &rwork[*n * 5 + 1], &rwork[*n * 6 + 1], &rwork[*n * 6 + 
	    kmax + 2], ierror);

/*     *** RETURN *** */
L99:

    return 0;
} /* scgdrv_ */

