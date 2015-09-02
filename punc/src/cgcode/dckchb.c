/* ./src_f77/dckchb.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__0 = 0;

/* Subroutine */ int dckchb_(integer *ipar, doublereal *rpar, doublereal *
	pegmin, doublereal *pegmax, doublereal *condca)
{
    /* Format strings */
    static char fmt_5[] = "(4x,\002NDEG   = \002,i5,/,4x,\002AA     = \002,d"
	    "12.5,/,4x,\002BB     = \002,d12.5)";
    static char fmt_10[] = "(/,\002 WARNING IN DCKCHB: NDEG .LT. 0; NO PRECO"
	    "NDG DONE\002,/)";
    static char fmt_11[] = "(/,\002 WARNING IN DCKCHB: NDEG IS ODD; NO ADAPT"
	    "IVE DONE\002,/)";
    static char fmt_15[] = "(/,\002 ERROR IN DCKCHB: (AA .LE. 0) OR (AA .GT."
	    " BB)\002)";
    static char fmt_20[] = "(/,\002 WARNING IN DCKCHB: INITIAL AA,BB CHANGE"
	    "D\002,/)";
    static char fmt_25[] = "(4x,\002CL     = \002,d12.5,/,4x,\002CU     ="
	    " \002,d12.5,/,4x,\002CONDCA = \002,d12.5,/)";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal aa, bb;
    static integer nchb, ndeg;
    extern doublereal d1mach_(integer *);
    extern /* Subroutine */ int ddpchb_(integer *, doublereal *, doublereal *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , integer *);
    static integer iadapt, iounit;
    static doublereal errtol;

    /* Fortran I/O blocks */
    static cilist io___6 = { 0, 0, 0, fmt_5, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___8 = { 0, 0, 0, fmt_11, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_15, 0 };
    static cilist io___12 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___13 = { 0, 0, 0, fmt_25, 0 };


/* ***BEGIN PROLOGUE  DCKCHB */
/* ***REFER TO  DPPCG,DPCGCA */
/* ***ROUTINES CALLED  DDPCHB,D1MACH */
/* ***REVISION DATE  870401   (YYMMDD) */
/* ***END PROLOGUE  DCKCHB */

/*     THIS SUBR OUTPUTS THE POLYNOMIAL INPUT PARAMETERS NDEG, AA, BB. */
/*     IT THEN CALLS DDPCHB (WITH IOUNIT=0) TO GET THE CORRESPONDING */
/*     MIN AND MAX EGVALS OF C(A)A.  FINALLY, THE INITIAL CONDCA IS */
/*     COMPUTED FOR USE IN THE STOPPING CRITERION. */

/*     *** DECLARATIONS *** */

/* ***FIRST EXECUTABLE STATEMENT  DCKCHB */
    /* Parameter adjustments */
    --rpar;
    --ipar;

    /* Function Body */
/* L1: */

/*     *** OUTPUT THE PARAMETERS *** */
    iounit = ipar[5];
    ndeg = ipar[34];
    nchb = ndeg + 1;
    aa = rpar[32];
    bb = rpar[33];
    if (iounit > 0) {
	io___6.ciunit = iounit;
	s_wsfe(&io___6);
	do_fio(&c__1, (char *)&ndeg, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&aa, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&bb, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }

/*     *** CHECK FOR IMPROPER NDEG *** */
    if (ndeg < 0) {
	io___7.ciunit = iounit;
	s_wsfe(&io___7);
	e_wsfe();
    }
    if (nchb % 2 == 0 && nchb >= 0) {
	io___8.ciunit = iounit;
	s_wsfe(&io___8);
	e_wsfe();
    }

/*     *** CHECK FOR INVALID AA, BB *** */
    if (aa <= 0. || aa > bb) {
	io___9.ciunit = iounit;
	s_wsfe(&io___9);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }

/*     *** DETERMINE PEGMIN, PEGMAX, CONDCA *** */
    if (ndeg < 0 || nchb % 2 == 0) {
	*pegmin = d1mach_(&c__2);
	*pegmax = d1mach_(&c__1);
    } else {
	*pegmin = 1.;
	*pegmax = 1.;
    }
    *condca = 1.;
    errtol = rpar[1];
    ddpchb_(&c__0, &aa, &bb, &nchb, pegmin, pegmax, condca, &errtol, &iadapt);
    if (iadapt > 0) {
	io___12.ciunit = iounit;
	s_wsfe(&io___12);
	e_wsfe();
    }

/*     *** OUTPUT INFO *** */
    if (iounit > 0) {
	io___13.ciunit = iounit;
	s_wsfe(&io___13);
	do_fio(&c__1, (char *)&(*pegmin), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*pegmax), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*condca), (ftnlen)sizeof(doublereal));
	e_wsfe();
    }

    return 0;
} /* dckchb_ */

