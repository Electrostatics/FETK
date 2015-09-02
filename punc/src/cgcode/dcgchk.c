/* ./src_f77/dcgchk.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;
static integer c__4 = 4;

/* Subroutine */ int dcgchk_(integer *ipar, doublereal *rpar, integer *n)
{
    /* Format strings */
    static char fmt_5[] = "(\002 THE ITERATION PARAMETERS ARE \002,/,4x,\002"
	    "N      = \002,i5,/,4x,\002ITMAX  = \002,i5,/,4x,\002ICYCLE = "
	    "\002,i5,/,4x,\002NCE    = \002,i5,/,4x,\002ERRTOL = \002,d12.5)";
    static char fmt_11[] = "(\002 ERROR IN DCGCHK: N .LE. 0\002,/)";
    static char fmt_12[] = "(/,\002 WARNING IN DCGCHK: ITMAX .LE. 0\002,/)";
    static char fmt_13[] = "(/,\002 WARNING IN DCGCHK: ICYCLE < 0 .OR. ICYCL"
	    "E > ITMAX\002,/)";
    static char fmt_14[] = "(/,\002 WARNING IN DCGCHK: NCE .LT. 0; SET TO "
	    "0\002,/)";
    static char fmt_15[] = "(/,\002 WARNING IN DCGCHK: ERRTOL .LE. MACHINE E"
	    "PSILON\002,/)";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    extern doublereal d1mach_(integer *);
    static integer iounit;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 0, fmt_5, 0 };
    static cilist io___3 = { 0, 0, 0, fmt_11, 0 };
    static cilist io___4 = { 0, 0, 0, fmt_12, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_13, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_14, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_15, 0 };


/* ***BEGIN PROLOGUE  DCGCHK */
/* ***REFER TO  DCG,DCR,DPCG,DCGNR,DCGNE,DPCGNR,DPCGNE,DPPCG,DPCGCA */
/* ***ROUTINES CALLED  D1MACH */
/* ***REVISION DATE  860901   (YYMMDD) */
/* ***END PROLOGUE  DCGCHK */

/*     THIS ROUTINE OUTPUTS THE INPUT PARAMETERS, AND THEN CHECKS THEIR */
/*     VALIDITY.  IF AN INVALID PARAMETER IS FOUND, AN ERROR MESSAGE IS */
/*     PRINTED AND THE CODE STOPPED.  IF AN UNUSUAL PARAMETER ASSIGNMENT */
/*     IS FOUND, A WARNING MESSAGE IS PRINTED, BUT THE CODE CONTINUES. */

/*     *** DECLARATIONS *** */

/* ***FIRST EXECUTABLE STATEMENT  DCGCHK */
    /* Parameter adjustments */
    --rpar;
    --ipar;

    /* Function Body */
/* L1: */

/*     *** OUTPUT THE PARAMETERS *** */
    iounit = ipar[5];
    if (iounit <= 0) {
	goto L10;
    }
    io___2.ciunit = iounit;
    s_wsfe(&io___2);
    do_fio(&c__1, (char *)&(*n), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ipar[9], (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ipar[31], (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ipar[32], (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&rpar[1], (ftnlen)sizeof(doublereal));
    e_wsfe();

/*     *** CHECK THE PARAMETERS *** */
L10:
    if (*n <= 0) {
	io___3.ciunit = iounit;
	s_wsfe(&io___3);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }

    if (ipar[9] <= 0) {
	io___4.ciunit = iounit;
	s_wsfe(&io___4);
	e_wsfe();
    }

    if (ipar[31] < 0 || ipar[31] > ipar[9]) {
	io___5.ciunit = iounit;
	s_wsfe(&io___5);
	e_wsfe();
    }

    if (ipar[32] < 0) {
	io___6.ciunit = iounit;
	s_wsfe(&io___6);
	e_wsfe();
	ipar[32] = 0;
    }

    if (rpar[1] <= d1mach_(&c__4)) {
	io___7.ciunit = iounit;
	s_wsfe(&io___7);
	e_wsfe();
    }

    return 0;
} /* dcgchk_ */

