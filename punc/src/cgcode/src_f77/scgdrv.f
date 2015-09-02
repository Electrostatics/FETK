cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c $Id: scgdrv.f,v 1.1 2006/06/08 08:56:27 mholst Exp $
c $Log: scgdrv.f,v $
c Revision 1.1  2006/06/08 08:56:27  mholst
c *** empty log message ***
c
c Revision 1.19  90/05/19  19:07:50  holst
c (1) CRIND documentation fix: algorithm section.
c (2) General documentation fix throughout the entire package, to make more
c     consistent with the CgCode report.
c 
c Note: now ready for initial distribution.
c 
c Revision 1.18  90/05/12  18:08:39  holst
c A fix in CGDRV to make the code consistent with the CgCode Report.
c Basically, CRIND was moved from ICG=10 to ICG=3 to be more logically
c correct (CR is ICG=2), and to be consistent with the report.
c After a check on some of the documentation, (specifically the algorithm
c section of CRIND, and the stopping crierion code/doc for all routines)
c we will be ready for the initial release of the code.
c 
c Revision 1.17  90/03/18  16:47:35  holst
c Changed the one instance of "FLOAT" to "REAL" to make conversion to
c double precision more uniform and simple.
c 
c Revision 1.16  90/03/18  16:02:48  holst
c Simply added the following line to each subroutine to make conversion
c to double precision automatic during development:
c CCCCCCIMPLICIT  DOUBLE PRECISION(A-H,O-Z)
c 
c Have written a script file that uncomments this, and performs all of
c the other necessary conversions to create a double precision version
c of the cgcode package from the single precision version.
c 
c Revision 1.15  90/03/18  14:22:59  holst
c Just updated the comments to the last revision
c 
c Revision 1.14  90/03/18  14:03:34  holst
c Cleaned up internal constants and intrinsic function calls to prepare
c for development of a double precision version of the code.  Specifically
c I changed:
c 
c (1) changed constants from:  x.y    to:   x.yE0
c (2) calls to MAX were changed to calls to AMAX1
c (3) calls to MIN were changed to calls to AMIN1
c (4) calls to LOG were changed to calls to ALOG
c 
c To change to double precision now simple involves:
c 
c (1) change constants from:  x.yEz   to:   z.yDz
c (2) calls to AMAX1  will be changed to DMAX1
c (3) calls to AMIN1  will be changed to DMIN1
c (4) calls to ALOG   will be changed to DLOG
c (5) calls to R1MACH will be changed to D1MACH
c (6) calls to SNRM2  will be changed to DNRM2
c (7) calls to SCOPY  will be changed to DCOPY
c (8) calls to SDOT   will be changed to DDOT
c (9) calls to SAXPY  will be changed to DAXPY
c (10)calls to SSCAL  will be changed to DSCAL
c (11)calls to SQRT   will be changed to DSQRT
c (12)format statements changed from xxExx to xxDxx
c (13)the line added to each routine: IMPLICIT DOUBLE PRECISION(A-H,O-Z)
c 
c Revision 1.13  90/02/20  00:37:39  holst
c Add SCR into package, making for 10 cg methods.
c (Steve A. wants to provide both SCR and SCRIND; now done.)
c Documentation of package also updated to include SCR.
c 
c Revision 1.12  90/02/19  10:27:48  holst
c Document/redo a little on MSTOP; SPPCG still needs work.  Others are
c ok I think.  See comments on last revision about SCRIND.
c 
c Revision 1.11  90/02/18  17:27:50  holst
c (1) Cosmetic fixes; documentation, output, etc.
c (2) Redo MSTOP; more fully implement all stopping criterion for 9 routines.
c (3) All stopping criterion implemented (I think) except for SPPCG.
c     (Should we add CONEST to SCRIND?  Should we add a SPCRIND?)
c     (There are other/better ways to implement MSTOP; look at?)
c 
c Revision 1.10  90/02/14  21:34:12  holst
c Small fix to condition estimate code in SPPCG and SPCGCA
c (allow ADPCHB to function even if not using ISTOP=0)
c 
c Revision 1.9  90/02/14  21:21:22  holst
c (1) The whole package is now consistently documented.
c (2) All 10 of the CGCODE subroutines now match the proposed standard,
c     except that the 9 subordinate routines deviate in two ways:
c     (a) uneccessary args not passed (PCONDL not passed to SCG, etc.)
c     (b) rwork parsed in SCGDRV so that the 9 subroutines are passed
c         seperate vectors to make for cleaner coding.
c     Except for those two differences, the remainder of the arguments
c     to the 9 routines conform to the proposed standard.
c (3) SCGDRV conforms completely to the proposed standard.
c (4) Up to now, identical results are obtained on the regression tests
c     as were obtained in revision 1.1 (before any changes were made.)
c (5) What remains:   MSTOP and stopping criterion questions.
c     Give the code to Dr. Steve Ashby for comments.
c 
c Revision 1.8  90/02/14  00:11:42  holst
c (1) Change parameter lists to individual 9 cg routines to more closely
c     conform to the proposed standard
c (2) Change indexes into RPARAM and IPARAM inside all routines that 
c     access them to conform to SCGDRV requirements; eliminate having
c     to do translation.
c (3) Documentation is now out of date for the 9 cg routines as far
c     as parameter descriptions; fix tomorrow.
c (4) Good night.
c 
c Revision 1.7  90/02/13  17:41:12  holst
c Simple fix to output format; Problem created by me when changing output
c terms like IMAX to ITMAX (different lengths).
c 
c Revision 1.6  90/02/13  16:50:18  holst
c Bug fix in stopping criterion in routine SPCGNR.
c 
c Revision 1.5  90/02/13  13:04:33  holst
c (1) Stopping criterion has been isolated in each of the nine routines
c     now; all of the routines use MSTOP.
c (2) Some of the stopping criterion need to be looked at in detail
c     (specifically SCRIND, SPPCG, and SPCGCA).
c (3) Ready for Steve Ashby to take a look at.
c 
c Revision 1.4  90/02/12  23:31:11  holst
c In this revision, we have completed:
c (1) The stopping criterion has been modularized and replaced with
c     calls to MSTOP in 7 of the 9 cgcode routines;  SPPCG and SPCGCA
c     are buggy and a little difficult.  The next revision will deal
c     simply with implementing MSTOP for SPPCG and SPCGCA.
c 
c Revision 1.3  90/02/12  03:16:24  holst
c This revision accomplished the following:
c (1) SCGDRV now conforms to the iterative standard; mcgdrv has been
c     eliminated.  While the individual cgcode subroutines still do
c     not conform to the standard, the external routines of matvec,
c     pcondl, and pcondr do conform.
c (2) All documentation of SCGDRV is complete.  All documentation of
c     the individual cgcode routines remains complete (see 3)
c (3) MSTOP has been implemented, and is used in SCG.  It appears
c     to work.  The next revision will involve solely putting MSTOP
c     calls into all of the other 8 cgcode routines.  Once that has
c     been complete, we will check in the code to steve ashby for a
c     look see, and start on the writeup.
c 
c Revision 1.2  90/02/10  21:24:48  holst
c The main changes were:
c (1) Fit cgcode, with new scrind, together with sppcg and spcgca, as one
c     package.
c (2) Update all comments to make sppcg, spcgca, and other routines
c     consistent.
c (3) Move mcgdrv standard interface to scgdrv into the mcgcode.f file,
c     ready to eliminate on next revision.
c 
c Revision 1.1  90/02/04  12:01:04  holst
c Initial revision
c 
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      SUBROUTINE SCGDRV(MATVEC,PCONDL,PCONDR,A,IA,X,B,N,Q,IQ,P,IP, 
     2   IPARAM,RPARAM,IWORK,RWORK,IERROR)
C***BEGIN PROLOGUE  SCGDRV
C***DATE WRITTEN   860115   (YYMMDD)
C***REVISION DATE  900210   (YYMMDD)
C***CATEGORY NO. D2A4,D2B4
C***KEYWORDS  LINEAR SYSTEM,SPARSE,ITERATIVE,CONJUGATE GRADIENTS
C***AUTHOR  ASHBY,STEVEN F., (UIUC)
C             UNIV. OF ILLINOIS
C             DEPT. OF COMPUTER SCIENCE
C             URBANA, IL 61801
C***AUTHOR  HOLST,MICHAEL J., (UIUC)
C             UNIV. OF ILLINOIS
C             DEPT. OF COMPUTER SCIENCE
C             URBANA, IL 61801
C           MANTEUFFEL,THOMAS A., (LANL)
C             LOS ALAMOS NATIONAL LABORATORY
C             MAIL STOP B265
C             LOS ALAMOS, NM 87545
C***PURPOSE  THIS SUBROUTINE IS AN INTERFACE TO CGCODE, A PACKAGE OF 
C            PRECONDITIONED CONJUGATE GRADIENT CODES.  THESE CODES 
C            WILL SOLVE BOTH SYMMETRIC AND NONSYMMETRIC LINEAR SYSTEMS, 
C            WITH OR WITHOUT PRECONDITIONING.  PRECONDITIONING INCLUDES
C            USER SUPPLIED PRECONDITIONERS AND/OR OR AUTOMATIC ADAPTIVE 
C            POLYNOMIAL PRECONDITIONING.  SEE THE FLAGS ICG=IPARAM(13)
C            AND IPCOND=IPARAM(7) FOR DETAILS; ALSO SEE THE INDIVIDUAL 
C            SUBROUTINES' PROLOGUES.  THE ARGUMENT LIST OF THIS 
C            INTERFACE SUBROUTINE CONFORMS TO THE PROPOSED STANDARD FOR 
C            ITERATIVE LINEAR SOLVERS (SEE THE BIBLIOGRAPHY FOR MORE 
C            INFORMATION.) 
C***DESCRIPTION
C
C--- ON ENTRY ---
C
C    MATVEC   EXTERNAL SUBROUTINE MATVEC(JOB,A,IA,W,X,Y,N)
C             THE USER MUST PROVIDE A SUBROUTINE HAVING THE SPECIFED
C             PARAMETER LIST.  THE SUBROUTINE MUST RETURN THE PRODUCT
C             (OR A RELATED COMPUTATION; SEE BELOW) Y=A*X, WHERE A IS 
C             THE COEFFICIENT MATRIX OF THE LINEAR SYSTEM.  THE MATRIX 
C             A IS REPRESENTED BY THE WORK ARRAYS A AND IA, DESCRIBED
C             BELOW.  THE INTEGER PARAMETER JOB SPECIFIES THE PRODUCT 
C             TO BE COMPUTED:
C                  JOB=0    Y=A*X
C                  JOB=1    Y=AT*X
C                  JOB=2    Y=W - A*X
C                  JOB=3    Y=W - AT*X.  
C             IN THE ABOVE, AT DENOTES A-TRANSPOSE.  NOTE THAT
C             ONLY THE VALUES OF JOB=0,1 ARE REQUIRED FOR CGCODE.
C             ALL OF THE ROUTINES IN CGCODE REQUIRE JOB=0; THE
C             ROUTINES SCGNR, SCGNE, SPCGNR, AND SPCGNE ALSO REQUIRE
C             THE VALUE OF JOB=1.  (THE VALUES OF JOB=2,3 ARE NOT 
C             REQUIRED BY ANY OF THE ROUTINES IN CGCODE, BUT MAY BE 
C             REQUIRED BY OTHER ITERATIVE PACKAGES CONFORMING TO THE 
C             PROPOSED ITERATIVE STANDARD.)  THE PARAMETERS W,X,Y ARE 
C             ALL VECTORS OF LENGTH N.  THE ONLY PARAMETER THAT MAY BE 
C             CHANGED INSIDE THE ROUTINE IS Y.  MATVEC WILL USUALLY 
C             SERVE AS AN INTERFACE TO THE USER'S OWN MATRIX-VECTOR 
C             MULTIPLY SUBROUTINE.  
C             NOTE: MATVEC MUST BE DECLARED IN AN EXTERNAL STATEMENT 
C             IN THE CALLING PROGRAM.
C
C    PCONDL   EXTERNAL SUBROUTINE PCONDL(JOB,Q,IQ,W,X,Y,N)
C             PCONDL IMPLEMENTS A USER SUPPLIED LEFT-PRECONDITIONER.
C             IF PRECONDITIONING IS SPECIFIED BY THE USER, THEN THE 
C             USER MUST PROVIDE A SUBROUTINE HAVING THE SPECIFED
C             PARAMETER LIST.  THE SUBROUTINE MUST RETURN THE PRODUCT
C             (OR A RELATED COMPUTATION; SEE BELOW) Y=C*X, WHERE C
C             IS A PRECONDITIONING MATRIX.  THE MATRIX C IS 
C             REPRESENTED BY THE WORK ARRAYS Q AND IQ, DESCRIBED
C             BELOW.  THE INTEGER PARAMETER JOB SPECIFIES THE PRODUCT 
C             TO BE COMPUTED:
C                  JOB=0    Y=C*X
C                  JOB=1    Y=CT*X
C                  JOB=2    Y=W - C*X
C                  JOB=3    Y=W - CT*X.  
C             IN THE ABOVE, CT DENOTES C-TRANSPOSE.  NOTE THAT
C             ONLY THE VALUES OF JOB=0,1 ARE REQUIRED FOR CGCODE.
C             THE ROUTINES SPCG, SPCGNR, SPCGNE, SPPCG, AND SPCGCA IN 
C             CGCODE REQUIRE JOB=0; THE ROUTINES SPCGNR AND SPCGNE ALSO 
C             REQUIRE THE VALUE OF JOB=1.  (THE VALUES OF JOB=2,3 ARE 
C             NOT REQUIRED BY ANY OF THE ROUTINES IN CGCODE, BUT MAY BE 
C             REQUIRED BY OTHER ITERATIVE PACKAGES CONFORMING TO THE 
C             PROPOSED ITERATIVE STANDARD.)  THE PARAMETERS W,X,Y ARE 
C             ALL VECTORS OF LENGTH N.  THE ONLY PARAMETER THAT MAY BE 
C             CHANGED INSIDE THE ROUTINE IS Y.  PCONDL WILL USUALLY 
C             SERVE AS AN INTERFACE TO THE USER'S OWN PRECONDITIONING
C             NOTE: PCONDL MUST BE DECLARED IN AN EXTERNAL STATEMENT 
C             IN THE CALLING PROGRAM.  IF NO PRE-CONDITIONING IS BEING 
C             DONE, PCONDL IS A DUMMY ARGUMENT.  
C
C    PCONDR   DUMMY ARGUMENT (MANDATED BY PROPOSED STANDARD.)
C
C    A        REAL ARRAY ADDRESS.
C             THE BASE ADDRESS OF THE USER'S REAL WORK ARRAY, USUALLY
C             THE MATRIX A.  SINCE A IS ONLY ACCESSED BY CALLS TO SUBR
C             MATVEC, IT MAY BE A DUMMY ADDRESS.
C
C    IA       INTEGER ARRAY ADDRESS.
C             THE BASE ADDRESS OF THE USER'S INTEGER WORK ARRAY.  THIS
C             USUALLY CONTAINS ADDITIONAL INFORMATION ABOUT A NEEDED BY
C             MATVEC.  SINCE IA IS ONLY ACCESSED BY CALLS TO MATVEC, IT
C             MAY BE A DUMMY ADDRESS.
C
C    X        REAL(N).
C             THE INITIAL GUESS VECTOR, X0.
C             (ON EXIT, X IS OVERWRITTEN WITH THE APPROXIMATE SOLUTION
C             OF A*X=B.)
C
C    B        REAL(N).
C             THE RIGHT-HAND SIDE VECTOR OF THE LINEAR SYSTEM AX=B.
C             NOTE: B IS CHANGED BY THE SOLVER.
C
C    N        INTEGER.
C             THE ORDER OF THE MATRIX A IN THE LINEAR SYSTEM AX=B.
C
C    Q        REAL ARRAY ADDRESS.
C             THE BASE ADDRESS OF THE USER'S LEFT-PRECONDITIONING ARRAY, 
C             Q.  SINCE Q IS ONLY ACCESSED BY CALLS TO PCONDL, IT MAY BE 
C             A DUMMY ADDRESS.  IF NO LEFT-PRECONDITIONING IS BEING 
C             DONE, THIS IS A DUMMY ARGUMENT.
C
C    IQ       INTEGER ARRAY ADDRESS.
C             THE BASE ADDRESS OF AN INTEGER WORK ARRAY ASSOCIATED WITH
C             Q.  THIS PROVIDES THE USER WITH A WAY OF PASSING INTEGER
C             INFORMATION ABOUT Q TO PCONDL.  SINCE IQ IS ONLY ACCESSED
C             BY CALLS TO PCONDL, IT MAY BE A DUMMY ADDRESS.  IF NO 
C             LEFT-PRECONDITIONING IS BEING DONE, THIS IS A DUMMY 
C             ARGUMENT.
C
C    P        DUMMY ARGUMENT (MANDATED BY PROPOSED STANDARD.)
C
C    IP       DUMMY ARGUMENT (MANDATED BY PROPOSED STANDARD.)
C
C    IPARAM   INTEGER(40).
C             AN ARRAY OF INTEGER INPUT PARAMETERS:
C                NOTE: IPARAM(1) THROUGH IPARAM(10) ARE MANDATED BY THE 
C                PROPOSED STANDARD; IPARAM(11) THROUGH IPARAM(30) ARE
C                RESERVED FOR EXPANSION OF THE PROPOSED STANDARD; 
C                IPARAM(31) THROUGH IPARAM(34) ARE ADDITIONAL 
C                PARAMETERS, SPECIFIC TO CGCODE.
C
C             IPARAM(1) = NIPAR 
C             LENGTH OF THE IPARAM ARRAY.  
C
C             IPARAM(2) = NRPAR 
C             LENGTH OF THE RPARAM ARRAY.  
C
C             IPARAM(3) = NIWK 
C             LENGTH OF THE IWORK ARRAY.  
C
C             IPARAM(4) = NRWK 
C             LENGTH OF THE RWORK ARRAY.  
C
C             IPARAM(5) = IOUNIT
C             IF (IOUNIT > 0) THEN ITERATION INFORMATION (AS 
C             SPECIFIED BY IOLEVL; SEE BELOW) IS SENT TO UNIT=IOUNIT,
C             WHICH MUST BE OPENED IN THE CALLING PROGRAM.  
C             IF (IOUNIT <= 0) THEN THERE IS NO OUTPUT.
C
C             IPARAM(6) = IOLEVL 
C             SPECIFIES THE AMOUNT AND TYPE OF INFORMATION TO BE 
C             OUTPUT IF (IOUNIT > 0):  
C                IOLEVL = 0   OUTPUT ERROR MESSAGES ONLY
C                IOLEVL = 1   OUTPUT INPUT PARAMETERS AND LEVEL 0 INFO
C                IOLEVL = 2   OUTPUT STPTST (SEE BELOW) AND LEVEL 1 INFO
C                IOLEVL = 3   OUTPUT LEVEL 2 INFO AND MORE DETAILS
C
C             IPARAM(7) = IPCOND 
C             PRECONDITIONING FLAG, SPECIFIED AS:
C                IPCOND = 0   NO PRECONDITIONING
C                IPCOND = 1   LEFT PRECONDITIONING
C                IPCOND = 2   RIGHT PRECONDITIONING 
C                IPCOND = 3   BOTH LEFT AND RIGHT PRECONDITIONING 
C             NOTE:  RIGHT PRECONDITIONING IS A MANDATED OPTION OF THE 
C             PROPOSED STANDARD, BUT NOT IMPLEMENTED IN CGCODE.
C
C             IPARAM(8) = ISTOP
C             STOPPING CRITERION FLAG, INTERPRETED AS:
C                ISTOP = 0  ||E||/||E0||      <= ERRTOL  (DEFAULT)
C                ISTOP = 1  ||R||             <= ERRTOL 
C                ISTOP = 2  ||R||/||B||       <= ERRTOL
C                ISTOP = 3  ||C*R||           <= ERRTOL
C                ISTOP = 4  ||C*R||/||C*B||   <= ERRTOL
C             WHERE E=ERROR, R=RESIDUAL, B=RIGHT HAND SIDE OF A*X=B, 
C             AND C IS THE PRECONDITIONING MATRIX OR PRECONDITIONING 
C             POLYNOMIAL (OR BOTH.) 
C             NOTE: IF ISTOP=0 IS SELECTED BY THE USER, THEN ERRTOL 
C             IS THE AMOUNT BY WHICH THE INITIAL ERROR IS TO BE 
C             REDUCED.  BY ESTIMATING THE CONDITION NUMBER OF THE 
C             ITERATION MATRIX, THE CODE ATTEMPTS TO GUARANTEE THAT 
C             THE FINAL RELATIVE ERROR IS .LE. ERRTOL.  SEE THE LONG 
C             DESCRIPTION BELOW FOR DETAILS.
C
C             IPARAM(9) = ITMAX
C             THE MAXIMUM NUMBER OF ITERATIVE STEPS TO BE TAKEN.
C             IF SOLVER IS UNABLE TO SATISFY THE STOPPING CRITERION 
C             WITHIN ITMAX ITERATIONS, IT RETURNS TO THE CALLING
C             PROGRAM WITH IERROR=-1000.
C
C             IPARAM(31) = ICYCLE
C             THE FREQUENCY WITH WHICH A CONDITION NUMBER ESTIMATE IS
C             COMPUTED; SEE THE LONG DESCRIPTION BELOW.
C
C             IPARAM(32) = NCE
C             THE MAXIMUM NUMBER OF CONDITION NUMBER ESTIMATES TO BE
C             COMPUTED.  IF NCE = 0 NO ESTIMATES ARE COMPUTED.  SEE
C             THE LONG DESCRIPTION BELOW.
C
C             IPARAM(33) = ICG
C             A FLAG SPECIFYING THE METHOD TO BE USED.  BELOW C IS 
C             THE USER'S PRECONDITIONING MATRIX, CT ITS TRANSPOSE, 
C             AND AT IS THE TRANSPOSE OF A.
C                ICG=1 : CG    : CONJUGATE GRADIENTS ON A, A SPD (CGHS)
C                ICG=2 : CR    : CONJUGATE RESIDUALS ON A, A SPD
C                ICG=3 : CRIND : CR ON A, A SYMMETRIC 
C                ICG=4 : PCG   : PRECONITIONED CG ON A, A AND C SPD
C                ICG=5 : CGNR  : CGHS ON AT*A, A ARBITRARY
C                ICG=6 : CGNE  : CGHS ON A*AT, A ARBITRARY
C                ICG=7 : PCGNR : CGNR ON A*C, A AND C ARBITRARY
C                ICG=8 : PCGNE : CGNE ON C*A, A AND C ARBITRARY
C                ICG=8 : PPCG  : POLYNOMIAL PCG ON A, A AND C SPD 
C                ICG=10: PCGCA : CGHS ON C(A)*A, A AND C SPD 
C             IF (1 .LT. ICG) OR (ICG .GT. 10) THEN ICG=1 IS ASSUMED.
C
C             IPARAM(34) = NDEG
C             WHEN USING THE CONJUGATE GRADIENT ROUTINES SPPCG AND
C             SPCGCA, NDEG SPECIFIES THE DEGREE OF THE PRECONDITIONING 
C             POLYNOMIAL TO BE USED IN THE ADAPTIVE POLYNOMIAL 
C             PRECONDITIONING ROUTINES.
C
C             NOTE:  KMAX = ICYCLE*NCE IS THE ORDER OF THE LARGEST
C             ORTHOGONAL SECTION OF C*A USED TO COMPUTE A CONDITION
C             NUMBER ESTIMATE.  THIS ESTIMATE IS ONLY USED IN THE
C             STOPPING CRITERION.  AS SUCH, KMAX SHOULD BE MUCH LESS
C             THAN N.  OTHERWISE THE CODE WILL HAVE EXCESSIVE STORAGE
C             AND WORK REQUIREMENTS.
C
C    RPARAM   REAL(40).
C             AN ARRAY OF REAL INPUT PARAMETERS:
C                NOTE: RPARAM(1) AND RPARAM(2) ARE MANDATED BY THE 
C                PROPOSED STANDARD; RPARAM(3) THROUGH RPARAM(30) ARE
C                RESERVED FOR EXPANSION OF THE PROPOSED STANDARD;
C                RPARAM(31) THROUGH RPARAM(34) ARE ADDITIONAL 
C                PARAMETERS, SPECIFIC TO CGCODE.
C
C             RPARAM(1) = ERRTOL
C             USER PROVIDED ERROR TOLERANCE; SEE ISTOP ABOVE, AND THE
C             LONG DESCRIPTION BELOW.
C
C             RPARAM(31) = CONDES
C             AN INITIAL ESTIMATE FOR THE COND NUMBER OF THE ITERATION
C             MATRIX; SEE THE INDIVIDUAL SUBROUTINE'S PROLOGUE. AN 
C             ACCEPTABLE INITIAL VALUE IS 1.0.
C
C             RPARAM(32) = AA     
C             INITIAL ESTIMATE OF THE SMALLEST EIGENVALUE OF THE 
C             SYSTEM MATRIX.  WHEN USING THE CONJUGATE GRADIENT
C             ROUTINES SPPCG AND SPCGCA, AA IS USED IN THE ADAPTIVE 
C             POLYNOMIAL PRECONDITIONING ROUTINES FOR FORMING THE 
C             OPTIMAL PRECONDITIONING POLYNOMIAL.
C
C             RPARAM(33) = BB
C             INITIAL ESTIMATE OF THE LARGEST EIGENVALUE OF THE 
C             SYSTEM MATRIX.  WHEN USING THE CONJUGATE GRADIENT
C             ROUTINES SPPCG AND SPCGCA, BB IS USED IN THE ADAPTIVE 
C             POLYNOMIAL PRECONDITIONING ROUTINES FOR FORMING THE 
C             OPTIMAL PRECONDITIONING POLYNOMIAL.
C
C    RWORK    REAL(N1+N2).
C             WORK ARRAY, WHERE N1 AND N2 ARE INTEGERS SUCH THAT:
C                N1 .GE. 2*N               FOR SCG, SPCG, SCGNR, SCGNE.
C                N1 .GE. 3*N               FOR SCR, SPCGNR, SPCGNE.  
C                N1 .GE. 5*N               FOR SCRIND
C                N1 .GE. 6*N               FOR SPPCG, SPCGCA.  
C                N2 .GE. 2*ICYCLE*NCE+2    FOR SPPCG, SPCGCA
C                N2 .GE. 4*ICYCLE*NCE+2    FOR SCG, SCR, SPCG, SCGNR, 
C                                              SCGNE, SPCGNR, SPCGNE, 
C                                              SCRIND 
C             THE N2 SPACE IS FOR COMPUTING CONDITION NUMBER ESTIMATES;
C             THE N1 SPACE IS FOR TEMPORARY VECTORS.  TO SAVE STORAGE 
C             AND WORK, ICYCLE*NCE SHOULD BE MUCH LESS THAN N.  NOTE
C             THAT IF NCE = 0, N2 MAY BE SET TO ZERO.
C
C    IWORK    INTEGER(ICYCLE*NCE)
C             INTEGER WORK ARRAY FOR COMPUTING COND NUMBER ESTIMATES.
C             IF NCE = 0, THIS MAY BE A DUMMY ADDRESS.
C
C--- ON RETURN ---
C
C    IPARAM   THE FOLLOWING ITERATION INFO IS RETURNED VIA THIS ARRAY:
C
C             IPARAM(10) = ITERS
C             THE NUMBER OF ITERATIONS TAKEN.  IF IERROR=0, THEN X_ITERS
C             SATISFIES THE SPECIFIED STOPPING CRITERION.  IF 
C             IERROR=-1000, CGCODE WAS UNABLE TO CONVERGE WITHIN ITMAX 
C             ITERATIONS, AND X_ITERS IS CGCODE'S BEST APPROXIMATION TO 
C             THE SOLUTION OF A*X=B.
C
C    RPARAM   THE FOLLOWING ITERATION INFO IS RETURNED VIA THIS ARRAY:
C
C             RPARAM(2) = STPTST
C             FINAL QUANTITY USED IN THE STOPPING CRITERION; SEE ISTOP
C             ABOVE, AND THE LONG DESCRIPTION BELOW.
C
C             RPARAM(31) = CONDES
C             CONDITION NUMBER ESTIMATE; FINAL ESTIMATE USED IN THE 
C             STOPPING CRITERION; SEE ISTOP ABOVE, AND THE LONG 
C             DESCRIPTION BELOW.
C
C             RPARAM(34) = SCRLRS
C             THE SCALED RELATIVE RESIDUAL USING THE LAST COMPUTED 
C             RESIDUAL.
C
C    X        THE COMPUTED SOLUTION OF THE LINEAR SYSTEM AX=B.
C
C    IERROR   INTEGER.
C             ERROR FLAG (NEGATIVE ERRORS ARE FATAL):
C             (BELOW, A=SYSTEM MATRIX, Q=LEFT PRECONDITIONING MATRIX.)
C             IERROR =  0      NORMAL RETURN: ITERATION CONVERGED
C             IERROR =  -1000  METHOD FAILED TO CONVERGE IN ITMAX STEPS
C             IERROR = +-2000  ERROR IN USER INPUT
C             IERROR = +-3000  METHOD BREAKDOWN
C             IERROR =  -6000  A DOES NOT SATISTY ASSUMPTIONS OF METHOD
C             IERROR =  -7000  Q DOES NOT SATISTY ASSUMPTIONS OF METHOD
C
C***LONG DESCRIPTION
C
C    EACH CG ALGORITHM IN THE PACKAGE IS AN INSTANCE OF AN ORTHOGONAL
C    ERROR METHOD.  THE GENERAL FORM OF SUCH A METHOD IS:
C
C                   P0 = S0 = C*R0
C                   ALPHA = <B*E,P>/<B*P,P>
C                   XNEW = X + ALPHA*P
C                   RNEW = R - ALPHA*(A*P)
C                   SNEW = C*RNEW
C                   BETA = <B*SNEW,P>/<B*P,P>
C                   PNEW = SNEW - BETA*P
C
C    WHERE B IS A SYMMETRIC POSITIVE DEFINITE MATRIX AND C IS A 
C    PRECONDITIONING MATRIX.  THE FOLLOWING CHOICES OF B AND C GIVE THE 
C    ALGORITHMS IN THE PACKAGE.  THE QUANTITY MINIMIZED AT EACH STEP IS 
C    ALSO LISTED.
C
C       ROUTINE        B MATRIX      C MATRIX     QUANTITY MINIMIZED
C
C        SCG              A             I             <A*E E>       
C        SCR             A*A            I              <R, R>         
C        SCRIND          A*A            I              <R, R>         
C        SPCG             A             C             <A*E, E>       
C        SCGNR           AT*A           AT             <R, R>         
C        SCGNE            I             AT             <E, E>         
C        SPCGNR          AT*A         C*CT*AT          <R, R>
C        SPCGNE           I           AT*CT*C          <E, E>          
C        SPPCG            A           C(A)*C          <A*E, E>
C        SPCGCA         C(A)*A          C           <C(A)*A*E, E>
C
C    FOR SPECIFIC ALGORITHMS AND IMPLEMENTATION DETAILS SEE THE ROUTINE
C    OF INTEREST.  FOR MORE ON ORTHOGONAL ERROR METHODS SEE THE SECOND
C    REFERENCE BELOW.
C
C    WHEN THE USER SELECTS THE STOPPING CRITERION OPTION ISTOP=0, THEN
C    THE CODES ALL ATTEMPT TO GUARANTEE THAT
C
C            (FINAL ERROR) / (INITIAL ERROR)  .LE.  ERRTOL     (1)
C
C    THAT IS, THE CODES ATTEMPT TO REDUCE THE INITIAL ERROR BY ERRTOL.
C    (IF X0=0, THEN ERRTOL IS ALSO A BOUND FOR THE RELATIVE ERROR IN 
C    THE COMPUTED SOLUTION, X.) TO SEE HOW (1) IS SATISFIED, CONSIDER
C    THE SCALED SYSTEM C*AX = C*P.   IF E(K) IS THE ERROR AT THE KTH
C    STEP, THEN WE HAVE
C
C                 E(K)/E(0)  .LE.  COND(CA) * S(K)/S(0)      
C  
C    WHERE S(K) = C*R(K) IS THE KTH SCALED RESIDUAL.  THE S VECTORS ARE
C    AVAILABLE FROM THE ITERATION.  IF WE CAN ESTIMATE COND(CA), THEN
C    EQUATION (1) IS SATISFIED WHEN
C
C                 COND(CA) * S(K)/S(0)  .LE.  ERRTOL.
C
C    AN ESTIMATE FOR COND(CA) IS OBTAINED BY COMPUTING THE MIN AND MAX
C    EIGENVALUES OF AN ORTHOGONAL SECTION OF C*A.  THIS IS DONE EVERY
C    ICYCLE STEPS.  THE LARGEST ORTHOG SECTION HAS ORDER ICYCLE*NCE,
C    WHERE NCE IS THE MAXIMUM NUMBER OF CONDITION ESTIMATES.  TO SAVE
C    STORAGE AND WORK, ICYCLE*NCE SHOULD BE MUCH LESS THAN N. IF NCE=0,
C    NO CONDITION ESTIMATES ARE COMPUTED.  IN THIS CASE, THE CODE STOPS
C    WHEN S(K)/S(0) .LE. ERRTOL.  SEE THE INDIVIDUAL SUBROUTINES' LONG
C    DESCRIPTIONS FOR DETAILS.
C
C    THIS STOPPING CRITERION WAS IMPLEMENTED BY A.J. ROBERTSON, III
C    (DEPT. OF MATHEMATICS, UNIV. OF COLORADO AT DENVER).  QUESTIONS
C    MAY BE DIRECTED TO HIM OR TO ONE OF THE AUTHORS.
C
C***REFERENCES  HOWARD C. ELMAN, "ITERATIVE METHODS FOR LARGE, SPARSE,
C                 NONSYMMETRIC SYSTEMS OF LINEAR EQUATIONS", YALE UNIV.
C                 DCS RESEARCH REPORT NO. 229 (APRIL 1982).
C               VANCE FABER AND THOMAS MANTEUFFEL, "NECESSARY AND
C                 SUFFICIENT CONDITIONS FOR THE EXISTENCE OF A
C                 CONJUGATE GRADIENT METHODS", SIAM J. NUM ANAL 21(2),
C                 PP. 352-362, 1984.
C               S. ASHBY, T. MANTEUFFEL, AND P. SAYLOR, "A TAXONOMY FOR
C                 CONJUGATE GRADIENT METHODS", SIAM J. NUM ANAL 27(6),
C                 PP. 1542-1568, 1990.
C               S. ASHBY, M. HOLST, T. MANTEUFFEL, AND P. SAYLOR,
C                 THE ROLE OF THE INNER PRODUCT IN STOPPING CRITERIA
C                 FOR CONJUGATE GRADIENT ITERATIONS", BIT 41(1),
C                 PP. 26-53, 2001.
C               M. HOLST, "CGCODE: SOFTWARE FOR SOLVING LINEAR SYSTEMS
C                 WITH CONJUGATE GRADIENT METHODS", M.S. THESIS, UNIV. 
C                 OF ILLINOIS DCS RESEARCH REPORT (MAY 1990).
C               S. ASHBY, "POLYNOMIAL PRECONDITIONG FOR CONJUGATE 
C                 GRADIENT METHODS", PH.D. THESIS, UNIV. OF ILLINOIS
C                 DCS RESEARCH REPORT NO. R-87-1355 (DECEMBER 1987).
C               S. ASHBY, M. SEAGER, "A PROPOSED STANDARD FOR ITERATIVE
C                 LINEAR SOLVERS", LAWRENCE LIVERMORE NATIONAL 
C                 LABORATORY REPORT (TO APPEAR).
C
C***ROUTINES CALLED  SCG,SCRIND,SPCG,SCGNR,SCGNE,SPCGNR,SPCGNE,
C                    SPPCG,SPCGCA
C***END PROLOGUE  SCGDRV
C
C     *** DECLARATIONS ***
CCCCCCIMPLICIT  DOUBLE PRECISION(A-H,O-Z)
      EXTERNAL  MATVEC,PCONDL,PCONDR
      DIMENSION A(*),IA(*),X(*),B(*),Q(*),IQ(*),P(*),IP(*)
      DIMENSION IPARAM(*),RPARAM(*),IWORK(*),RWORK(*)
C
C***FIRST EXECUTABLE STATEMENT  SCGDRV
 1    CONTINUE
C
C     *** DECODE METHOD PARAMETER AND RWORK PARSING PARAMETERS ***
      IOUNIT = IPARAM(5)
      IOLEVL = IPARAM(6)
      ICG    = IPARAM(33) 
      ICYCLE = IPARAM(31) 
      NCE    = IPARAM(32) 
      KMAX   = ICYCLE*NCE
C
C     *** CALL THE APPROPRIATE CGCODE SUBROUTINE ***
      IF ((IOUNIT .GT. 0) .AND. (IOLEVL .GT. 0)) WRITE(IOUNIT,100) ICG
 100  FORMAT(' USING CGCODE:  ICG=',I10)
      GOTO (11,12,13,14,15,16,17,18,19,20) ICG
C
 11   CALL SCG(MATVEC,A,IA,X,B,N,IPARAM,RPARAM,IWORK,
     2   RWORK(1),RWORK(N+1),RWORK(2*N+1),RWORK(2*N+KMAX+2),
     3   RWORK(2*N+2*KMAX+3),IERROR)
      GOTO 99
C
 12   CALL SCR(MATVEC,A,IA,X,B,N,IPARAM,RPARAM,IWORK,
     2   RWORK(1),RWORK(N+1),RWORK(2*N+1),RWORK(3*N+1),
     3   RWORK(3*N+KMAX+2),RWORK(3*N+2*KMAX+3),IERROR)
      GOTO 99
C
 13   CALL SCRIND(MATVEC,A,IA,X,B,N,IPARAM,RPARAM,IWORK,
     2   RWORK(1),RWORK(N+1),RWORK(2*N+1),RWORK(3*N+1),RWORK(4*N+1),
     3   RWORK(5*N+1),RWORK(5*N+KMAX+2),RWORK(5*N+2*KMAX+3),IERROR)
      GOTO 99
C
 14   CALL SPCG(MATVEC,PCONDL,A,IA,X,B,N,Q,IQ,IPARAM,RPARAM,IWORK,
     2   RWORK(1),RWORK(N+1),RWORK(2*N+1),RWORK(2*N+KMAX+2),
     3   RWORK(2*N+2*KMAX+3),IERROR)
      GOTO 99
C
 15   CALL SCGNR(MATVEC,A,IA,X,B,N,IPARAM,RPARAM,IWORK,
     2   RWORK(1),RWORK(N+1),RWORK(2*N+1),RWORK(2*N+KMAX+2),
     3   RWORK(2*N+2*KMAX+3),IERROR)
      GOTO 99
C
 16   CALL SCGNE(MATVEC,A,IA,X,B,N,IPARAM,RPARAM,IWORK,
     2   RWORK(1),RWORK(N+1),RWORK(2*N+1),RWORK(2*N+KMAX+2),
     3   RWORK(2*N+2*KMAX+3),IERROR)
      GOTO 99
C
 17   CALL SPCGNR(MATVEC,PCONDL,A,IA,X,B,N,Q,IQ,IPARAM,RPARAM,IWORK,
     2   RWORK(1),RWORK(N+1),RWORK(2*N+1),RWORK(3*N+1),
     3   RWORK(3*N+KMAX+2),RWORK(3*N+2*KMAX+3),IERROR)
      GOTO 99
C
 18   CALL SPCGNE(MATVEC,PCONDL,A,IA,X,B,N,Q,IQ,IPARAM,RPARAM,IWORK,
     2   RWORK(1),RWORK(N+1),RWORK(2*N+1),RWORK(3*N+1),
     3   RWORK(3*N+KMAX+2),RWORK(3*N+2*KMAX+3),IERROR)
      GOTO 99
C
 19   CALL SPPCG(MATVEC,PCONDL,A,IA,X,B,N,Q,IQ,IPARAM,RPARAM,IWORK,
     2   RWORK(1),RWORK(N+1),RWORK(2*N+1),RWORK(3*N+1),RWORK(4*N+1),
     3   RWORK(5*N+1),RWORK(6*N+1),RWORK(6*N+KMAX+2),IERROR)
      GOTO 99
C
 20   CALL SPCGCA(MATVEC,PCONDL,A,IA,X,B,N,Q,IQ,IPARAM,RPARAM,IWORK,
     2   RWORK(1),RWORK(N+1),RWORK(2*N+1),RWORK(3*N+1),RWORK(4*N+1),
     3   RWORK(5*N+1),RWORK(6*N+1),RWORK(6*N+KMAX+2),IERROR)
C
C     *** RETURN ***
 99   CONTINUE
C
      RETURN
      END
