/* ./src_f77/mlinpckd.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>

/* Table of constant values */

static integer c__1 = 1;

/* * /////////////////////////////////////////////////////////////////////////// */
/* * @file    mlinpckd.f */
/* * @author  Michael Holst */
/* * @brief   XXX */
/* * @version $Id: mlinpckd.c,v 1.3 2010/08/12 05:45:23 fetk Exp $ */
/* * @attention */
/* * @verbatim */
/* * */
/* * PMG -- Parallel algebraic MultiGrid */
/* * Copyright (C) 1994-- Michael Holst. */
/* * */
/* * Michael Holst <mholst@math.ucsd.edu> */
/* * University of California, San Diego */
/* * Department of Mathematics, 5739 AP&M */
/* * 9500 Gilman Drive, Dept. 0112 */
/* * La Jolla, CA 92093-0112 USA */
/* * http://math.ucsd.edu/~mholst */
/* * */
/* * This file is part of PMG. */
/* * */
/* * PMG is free software; you can redistribute it and/or modify */
/* * it under the terms of the GNU General Public License as published by */
/* * the Free Software Foundation; either version 2 of the License, or */
/* * (at your option) any later version. */
/* * */
/* * PMG is distributed in the hope that it will be useful, */
/* * but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* * GNU General Public License for more details. */
/* * */
/* * You should have received a copy of the GNU General Public License */
/* * along with PMG; if not, write to the Free Software */
/* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA */
/* * */
/* * Linking PMG statically or dynamically with other modules is making a */
/* * combined work based on PMG. Thus, the terms and conditions of the GNU */
/* * General Public License cover the whole combination. */
/* * */
/* * SPECIAL GPL EXCEPTION */
/* * In addition, as a special exception, the copyright holders of PMG */
/* * give you permission to combine the PMG program with free software */
/* * programs and libraries that are released under the GNU LGPL or with */
/* * code included in releases of ISIM, PMV, PyMOL, SMOL, VMD, and Vision. */
/* * Such combined software may be linked with PMG and redistributed together */
/* * in original or modified form as mere aggregation without requirement that */
/* * the entire work be under the scope of the GNU General Public License. */
/* * This special exception permission is also extended to any software listed */
/* * in the SPECIAL GPL EXCEPTION clauses by the FEtk and APBS libraries. */
/* * */
/* * Note that people who make modified versions of PMG are not obligated */
/* * to grant this special exception for their modified versions; it is */
/* * their choice whether to do so. The GNU General Public License gives */
/* * permission to release a modified version without this exception; this */
/* * exception also makes it possible to release a modified version which */
/* * carries forward this exception. */
/* * */
/* * @endverbatim */
/* * /////////////////////////////////////////////////////////////////////////// */
/* *********************************************************************** */
/* A few routines from LINPACK for dealing with banded matrices. */

/* DPBCO -- FACTOR BANDED SPD MATRIX AND COMPUTE CONDITION NUMBER */
/* DPBFA -- FACTOR BANDED SPD MATRIX */
/* DPBSL -- BACKSOLVE A FACTORED BANDED SPD MATRIX */

/* DOUBLE PRECISION VERSION */
/* *********************************************************************** */
/* Subroutine */ int dpbco_(doublereal *abd, integer *lda, integer *n, 
	integer *m, doublereal *rcond, doublereal *z__, integer *info)
{
    /* System generated locals */
    integer abd_dim1, abd_offset, i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Builtin functions */
    double d_sign(doublereal *, doublereal *);

    /* Local variables */
    static integer i__, j, k, l;
    static doublereal s, t;
    static integer j2, kb, la, lb;
    static doublereal ek;
    static integer lm;
    static doublereal sm, wk;
    static integer mu, kp1;
    static doublereal wkm;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    extern /* Subroutine */ int dpbfa_(doublereal *, integer *, integer *, 
	    integer *, integer *), dscal_(integer *, doublereal *, doublereal 
	    *, integer *);
    extern doublereal dasum_(integer *, doublereal *, integer *);
    static doublereal anorm;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static doublereal ynorm;


/*     DPBCO FACTORS A DOUBLE PRECISION SYMMETRIC POSITIVE DEFINITE */
/*     MATRIX STORED IN BAND FORM AND ESTIMATES THE CONDITION OF THE */
/*     MATRIX. */

/*     IF  RCOND  IS NOT NEEDED, DPBFA IS SLIGHTLY FASTER. */
/*     TO SOLVE  A*X = B , FOLLOW DPBCO BY DPBSL. */
/*     TO COMPUTE  INVERSE(A)*C , FOLLOW DPBCO BY DPBSL. */
/*     TO COMPUTE  DETERMINANT(A) , FOLLOW DPBCO BY DPBDI. */

/*     ON ENTRY */

/*        ABD     DOUBLE PRECISION(LDA, N) */
/*                THE MATRIX TO BE FACTORED.  THE COLUMNS OF THE UPPER */
/*                TRIANGLE ARE STORED IN THE COLUMNS OF ABD AND THE */
/*                DIAGONALS OF THE UPPER TRIANGLE ARE STORED IN THE */
/*                ROWS OF ABD .  SEE THE COMMENTS BELOW FOR DETAILS. */

/*        LDA     INTEGER */
/*                THE LEADING DIMENSION OF THE ARRAY  ABD . */
/*                LDA MUST BE .GE. M + 1 . */

/*        N       INTEGER */
/*                THE ORDER OF THE MATRIX  A . */

/*        M       INTEGER */
/*                THE NUMBER OF DIAGONALS ABOVE THE MAIN DIAGONAL. */
/*                0 .LE. M .LT. N . */

/*     ON RETURN */

/*        ABD     AN UPPER TRIANGULAR MATRIX  R , STORED IN BAND */
/*                FORM, SO THAT  A = TRANS(R)*R . */
/*                IF  INFO .NE. 0 , THE FACTORIZATION IS NOT COMPLETE. */

/*        RCOND   DOUBLE PRECISION */
/*                AN ESTIMATE OF THE RECIPROCAL CONDITION OF  A . */
/*                FOR THE SYSTEM  A*X = B , RELATIVE PERTURBATIONS */
/*                IN  A  AND  B  OF SIZE  EPSILON  MAY CAUSE */
/*                RELATIVE PERTURBATIONS IN  X  OF SIZE  EPSILON/RCOND . */
/*                IF  RCOND  IS SO SMALL THAT THE LOGICAL EXPRESSION */
/*                           1.0 + RCOND .EQ. 1.0 */
/*                IS TRUE, THEN  A  MAY BE SINGULAR TO WORKING */
/*                PRECISION.  IN PARTICULAR,  RCOND  IS ZERO  IF */
/*                EXACT SINGULARITY IS DETECTED OR THE ESTIMATE */
/*                UNDERFLOWS.  IF INFO .NE. 0 , RCOND IS UNCHANGED. */

/*        Z       DOUBLE PRECISION(N) */
/*                A WORK VECTOR WHOSE CONTENTS ARE USUALLY UNIMPORTANT. */
/*                IF  A  IS SINGULAR TO WORKING PRECISION, THEN  Z  IS */
/*                AN APPROXIMATE NULL VECTOR IN THE SENSE THAT */
/*                NORM(A*Z) = RCOND*NORM(A)*NORM(Z) . */
/*                IF  INFO .NE. 0 , Z  IS UNCHANGED. */

/*        INFO    INTEGER */
/*                = 0  FOR NORMAL RETURN. */
/*                = K  SIGNALS AN ERROR CONDITION.  THE LEADING MINOR */
/*                     OF ORDER  K  IS NOT POSITIVE DEFINITE. */

/*     BAND STORAGE */

/*           IF  A  IS A SYMMETRIC POSITIVE DEFINITE BAND MATRIX, */
/*           THE FOLLOWING PROGRAM SEGMENT WILL SET UP THE INPUT. */

/*                   M = (BAND WIDTH ABOVE DIAGONAL) */
/*                   DO 20 J = 1, N */
/*                      I1 = MAX0(1, J-M) */
/*                      DO 10 I = I1, J */
/*                         K = I-J+M+1 */
/*                         ABD(K,J) = A(I,J) */
/*                10    CONTINUE */
/*                20 CONTINUE */

/*           THIS USES  M + 1  ROWS OF  A , EXCEPT FOR THE  M BY M */
/*           UPPER LEFT TRIANGLE, WHICH IS IGNORED. */

/*     EXAMPLE..  IF THE ORIGINAL MATRIX IS */

/*           11 12 13  0  0  0 */
/*           12 22 23 24  0  0 */
/*           13 23 33 34 35  0 */
/*            0 24 34 44 45 46 */
/*            0  0 35 45 55 56 */
/*            0  0  0 46 56 66 */

/*     THEN  N = 6 , M = 2  AND  ABD  SHOULD CONTAIN */

/*            *  * 13 24 35 46 */
/*            * 12 23 34 45 56 */
/*           11 22 33 44 55 66 */

/*     LINPACK.  THIS VERSION DATED 08/14/78 . */
/*     CLEVE MOLER, UNIVERSITY OF NEW MEXICO, ARGONNE NATIONAL LAB. */

/*     SUBROUTINES AND FUNCTIONS */

/*     LINPACK DPBFA */
/*     BLAS DAXPY,DDOT,DSCAL,DASUM */
/*     FORTRAN DABS,DMAX1,MAX0,MIN0,DREAL,DSIGN */

/*     INTERNAL VARIABLES */



/*     FIND NORM OF A */

    /* Parameter adjustments */
    abd_dim1 = *lda;
    abd_offset = 1 + abd_dim1;
    abd -= abd_offset;
    --z__;

    /* Function Body */
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
/* Computing MIN */
	i__2 = j, i__3 = *m + 1;
	l = min(i__2,i__3);
/* Computing MAX */
	i__2 = *m + 2 - j;
	mu = max(i__2,1);
	z__[j] = dasum_(&l, &abd[mu + j * abd_dim1], &c__1);
	k = j - l;
	if (*m < mu) {
	    goto L20;
	}
	i__2 = *m;
	for (i__ = mu; i__ <= i__2; ++i__) {
	    ++k;
	    z__[k] += (d__1 = abd[i__ + j * abd_dim1], abs(d__1));
/* L10: */
	}
L20:
/* L30: */
	;
    }
    anorm = 0.;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
	d__1 = anorm, d__2 = z__[j];
	anorm = max(d__1,d__2);
/* L40: */
    }

/*     FACTOR */

    dpbfa_(&abd[abd_offset], lda, n, m, info);
    if (*info != 0) {
	goto L180;
    }

/*        RCOND = 1/(NORM(A)*(ESTIMATE OF NORM(INVERSE(A)))) . */
/*        ESTIMATE = NORM(Z)/NORM(Y) WHERE  A*Z = Y  AND  A*Y = E . */
/*        THE COMPONENTS OF  E  ARE CHOSEN TO CAUSE MAXIMUM LOCAL */
/*        GROWTH IN THE ELEMENTS OF W  WHERE  TRANS(R)*W = E . */
/*        THE VECTORS ARE FREQUENTLY RESCALED TO AVOID OVERFLOW. */

/*        SOLVE TRANS(R)*W = E */

    ek = 1.;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	z__[j] = 0.;
/* L50: */
    }
    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
	if (z__[k] != 0.) {
	    d__1 = -z__[k];
	    ek = d_sign(&ek, &d__1);
	}
	if ((d__1 = ek - z__[k], abs(d__1)) <= abd[*m + 1 + k * abd_dim1]) {
	    goto L60;
	}
	s = abd[*m + 1 + k * abd_dim1] / (d__1 = ek - z__[k], abs(d__1));
	dscal_(n, &s, &z__[1], &c__1);
	ek = s * ek;
L60:
	wk = ek - z__[k];
	wkm = -ek - z__[k];
	s = abs(wk);
	sm = abs(wkm);
	wk /= abd[*m + 1 + k * abd_dim1];
	wkm /= abd[*m + 1 + k * abd_dim1];
	kp1 = k + 1;
/* Computing MIN */
	i__2 = k + *m;
	j2 = min(i__2,*n);
	i__ = *m + 1;
	if (kp1 > j2) {
	    goto L100;
	}
	i__2 = j2;
	for (j = kp1; j <= i__2; ++j) {
	    --i__;
	    sm += (d__1 = z__[j] + wkm * abd[i__ + j * abd_dim1], abs(d__1));
	    z__[j] += wk * abd[i__ + j * abd_dim1];
	    s += (d__1 = z__[j], abs(d__1));
/* L70: */
	}
	if (s >= sm) {
	    goto L90;
	}
	t = wkm - wk;
	wk = wkm;
	i__ = *m + 1;
	i__2 = j2;
	for (j = kp1; j <= i__2; ++j) {
	    --i__;
	    z__[j] += t * abd[i__ + j * abd_dim1];
/* L80: */
	}
L90:
L100:
	z__[k] = wk;
/* L110: */
    }
    s = 1. / dasum_(n, &z__[1], &c__1);
    dscal_(n, &s, &z__[1], &c__1);

/*        SOLVE  R*Y = W */

    i__1 = *n;
    for (kb = 1; kb <= i__1; ++kb) {
	k = *n + 1 - kb;
	if ((d__1 = z__[k], abs(d__1)) <= abd[*m + 1 + k * abd_dim1]) {
	    goto L120;
	}
	s = abd[*m + 1 + k * abd_dim1] / (d__1 = z__[k], abs(d__1));
	dscal_(n, &s, &z__[1], &c__1);
L120:
	z__[k] /= abd[*m + 1 + k * abd_dim1];
/* Computing MIN */
	i__2 = k - 1;
	lm = min(i__2,*m);
	la = *m + 1 - lm;
	lb = k - lm;
	t = -z__[k];
	daxpy_(&lm, &t, &abd[la + k * abd_dim1], &c__1, &z__[lb], &c__1);
/* L130: */
    }
    s = 1. / dasum_(n, &z__[1], &c__1);
    dscal_(n, &s, &z__[1], &c__1);

    ynorm = 1.;

/*        SOLVE TRANS(R)*V = Y */

    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
/* Computing MIN */
	i__2 = k - 1;
	lm = min(i__2,*m);
	la = *m + 1 - lm;
	lb = k - lm;
	z__[k] -= ddot_(&lm, &abd[la + k * abd_dim1], &c__1, &z__[lb], &c__1);
	if ((d__1 = z__[k], abs(d__1)) <= abd[*m + 1 + k * abd_dim1]) {
	    goto L140;
	}
	s = abd[*m + 1 + k * abd_dim1] / (d__1 = z__[k], abs(d__1));
	dscal_(n, &s, &z__[1], &c__1);
	ynorm = s * ynorm;
L140:
	z__[k] /= abd[*m + 1 + k * abd_dim1];
/* L150: */
    }
    s = 1. / dasum_(n, &z__[1], &c__1);
    dscal_(n, &s, &z__[1], &c__1);
    ynorm = s * ynorm;

/*        SOLVE  R*Z = W */

    i__1 = *n;
    for (kb = 1; kb <= i__1; ++kb) {
	k = *n + 1 - kb;
	if ((d__1 = z__[k], abs(d__1)) <= abd[*m + 1 + k * abd_dim1]) {
	    goto L160;
	}
	s = abd[*m + 1 + k * abd_dim1] / (d__1 = z__[k], abs(d__1));
	dscal_(n, &s, &z__[1], &c__1);
	ynorm = s * ynorm;
L160:
	z__[k] /= abd[*m + 1 + k * abd_dim1];
/* Computing MIN */
	i__2 = k - 1;
	lm = min(i__2,*m);
	la = *m + 1 - lm;
	lb = k - lm;
	t = -z__[k];
	daxpy_(&lm, &t, &abd[la + k * abd_dim1], &c__1, &z__[lb], &c__1);
/* L170: */
    }
/*        MAKE ZNORM = 1.0 */
    s = 1. / dasum_(n, &z__[1], &c__1);
    dscal_(n, &s, &z__[1], &c__1);
    ynorm = s * ynorm;

    if (anorm != 0.) {
	*rcond = ynorm / anorm;
    }
    if (anorm == 0.) {
	*rcond = 0.;
    }
L180:
    return 0;
} /* dpbco_ */

/* Subroutine */ int dpbfa_(doublereal *abd, integer *lda, integer *n, 
	integer *m, integer *info)
{
    /* System generated locals */
    integer abd_dim1, abd_offset, i__1, i__2, i__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer j, k;
    static doublereal s, t;
    static integer ik, jk, mu;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);


/*     DPBFA FACTORS A DOUBLE PRECISION SYMMETRIC POSITIVE DEFINITE */
/*     MATRIX STORED IN BAND FORM. */

/*     DPBFA IS USUALLY CALLED BY DPBCO, BUT IT CAN BE CALLED */
/*     DIRECTLY WITH A SAVING IN TIME IF  RCOND  IS NOT NEEDED. */

/*     ON ENTRY */

/*        ABD     DOUBLE PRECISION(LDA, N) */
/*                THE MATRIX TO BE FACTORED.  THE COLUMNS OF THE UPPER */
/*                TRIANGLE ARE STORED IN THE COLUMNS OF ABD AND THE */
/*                DIAGONALS OF THE UPPER TRIANGLE ARE STORED IN THE */
/*                ROWS OF ABD .  SEE THE COMMENTS BELOW FOR DETAILS. */

/*        LDA     INTEGER */
/*                THE LEADING DIMENSION OF THE ARRAY  ABD . */
/*                LDA MUST BE .GE. M + 1 . */

/*        N       INTEGER */
/*                THE ORDER OF THE MATRIX  A . */

/*        M       INTEGER */
/*                THE NUMBER OF DIAGONALS ABOVE THE MAIN DIAGONAL. */
/*                0 .LE. M .LT. N . */

/*     ON RETURN */

/*        ABD     AN UPPER TRIANGULAR MATRIX  R , STORED IN BAND */
/*                FORM, SO THAT  A = TRANS(R)*R . */

/*        INFO    INTEGER */
/*                = 0  FOR NORMAL RETURN. */
/*                = K  IF THE LEADING MINOR OF ORDER  K  IS NOT */
/*                     POSITIVE DEFINITE. */

/*     BAND STORAGE */

/*           IF  A  IS A SYMMETRIC POSITIVE DEFINITE BAND MATRIX, */
/*           THE FOLLOWING PROGRAM SEGMENT WILL SET UP THE INPUT. */

/*                   M = (BAND WIDTH ABOVE DIAGONAL) */
/*                   DO 20 J = 1, N */
/*                      I1 = MAX0(1, J-M) */
/*                      DO 10 I = I1, J */
/*                         K = I-J+M+1 */
/*                         ABD(K,J) = A(I,J) */
/*                10    CONTINUE */
/*                20 CONTINUE */

/*     LINPACK.  THIS VERSION DATED 08/14/78 . */
/*     CLEVE MOLER, UNIVERSITY OF NEW MEXICO, ARGONNE NATIONAL LAB. */

/*     SUBROUTINES AND FUNCTIONS */

/*     BLAS DDOT */
/*     FORTRAN MAX0,DSQRT */

/*     INTERNAL VARIABLES */

/*     BEGIN BLOCK WITH ...EXITS TO 40 */


    /* Parameter adjustments */
    abd_dim1 = *lda;
    abd_offset = 1 + abd_dim1;
    abd -= abd_offset;

    /* Function Body */
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	*info = j;
	s = 0.;
	ik = *m + 1;
/* Computing MAX */
	i__2 = j - *m;
	jk = max(i__2,1);
/* Computing MAX */
	i__2 = *m + 2 - j;
	mu = max(i__2,1);
	if (*m < mu) {
	    goto L20;
	}
	i__2 = *m;
	for (k = mu; k <= i__2; ++k) {
	    i__3 = k - mu;
	    t = abd[k + j * abd_dim1] - ddot_(&i__3, &abd[ik + jk * abd_dim1],
		     &c__1, &abd[mu + j * abd_dim1], &c__1);
	    t /= abd[*m + 1 + jk * abd_dim1];
	    abd[k + j * abd_dim1] = t;
	    s += t * t;
	    --ik;
	    ++jk;
/* L10: */
	}
L20:
	s = abd[*m + 1 + j * abd_dim1] - s;
/*     ......EXIT */
	if (s <= 0.) {
	    goto L40;
	}
	abd[*m + 1 + j * abd_dim1] = sqrt(s);
/* L30: */
    }
    *info = 0;
L40:
    return 0;
} /* dpbfa_ */

/* Subroutine */ int dpbsl_(doublereal *abd, integer *lda, integer *n, 
	integer *m, doublereal *b)
{
    /* System generated locals */
    integer abd_dim1, abd_offset, i__1, i__2;

    /* Local variables */
    static integer k;
    static doublereal t;
    static integer kb, la, lb, lm;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);


/*     DPBSL SOLVES THE DOUBLE PRECISION SYMMETRIC POSITIVE DEFINITE */
/*     BAND SYSTEM  A*X = B */
/*     USING THE FACTORS COMPUTED BY DPBCO OR DPBFA. */

/*     ON ENTRY */

/*        ABD     DOUBLE PRECISION(LDA, N) */
/*                THE OUTPUT FROM DPBCO OR DPBFA. */

/*        LDA     INTEGER */
/*                THE LEADING DIMENSION OF THE ARRAY  ABD . */

/*        N       INTEGER */
/*                THE ORDER OF THE MATRIX  A . */

/*        M       INTEGER */
/*                THE NUMBER OF DIAGONALS ABOVE THE MAIN DIAGONAL. */

/*        B       DOUBLE PRECISION(N) */
/*                THE RIGHT HAND SIDE VECTOR. */

/*     ON RETURN */

/*        B       THE SOLUTION VECTOR  X . */

/*     ERROR CONDITION */

/*        A DIVISION BY ZERO WILL OCCUR IF THE INPUT FACTOR CONTAINS */
/*        A ZERO ON THE DIAGONAL.  TECHNICALLY THIS INDICATES */
/*        SINGULARITY BUT IT IS USUALLY CAUSED BY IMPROPER SUBROUTINE */
/*        ARGUMENTS.  IT WILL NOT OCCUR IF THE SUBROUTINES ARE CALLED */
/*        CORRECTLY AND  INFO .EQ. 0 . */

/*     TO COMPUTE  INVERSE(A) * C  WHERE  C  IS A MATRIX */
/*     WITH  P  COLUMNS */
/*           CALL DPBCO(ABD,LDA,N,RCOND,Z,INFO) */
/*           IF (RCOND IS TOO SMALL .OR. INFO .NE. 0) GO TO ... */
/*           DO 10 J = 1, P */
/*              CALL DPBSL(ABD,LDA,N,C(1,J)) */
/*        10 CONTINUE */

/*     LINPACK.  THIS VERSION DATED 08/14/78 . */
/*     CLEVE MOLER, UNIVERSITY OF NEW MEXICO, ARGONNE NATIONAL LAB. */

/*     SUBROUTINES AND FUNCTIONS */

/*     BLAS DAXPY,DDOT */
/*     FORTRAN MIN0 */

/*     INTERNAL VARIABLES */


/*     SOLVE TRANS(R)*Y = B */

    /* Parameter adjustments */
    abd_dim1 = *lda;
    abd_offset = 1 + abd_dim1;
    abd -= abd_offset;
    --b;

    /* Function Body */
    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
/* Computing MIN */
	i__2 = k - 1;
	lm = min(i__2,*m);
	la = *m + 1 - lm;
	lb = k - lm;
	t = ddot_(&lm, &abd[la + k * abd_dim1], &c__1, &b[lb], &c__1);
	b[k] = (b[k] - t) / abd[*m + 1 + k * abd_dim1];
/* L10: */
    }

/*     SOLVE R*X = Y */

    i__1 = *n;
    for (kb = 1; kb <= i__1; ++kb) {
	k = *n + 1 - kb;
/* Computing MIN */
	i__2 = k - 1;
	lm = min(i__2,*m);
	la = *m + 1 - lm;
	lb = k - lm;
	b[k] /= abd[*m + 1 + k * abd_dim1];
	t = -b[k];
	daxpy_(&lm, &t, &abd[la + k * abd_dim1], &c__1, &b[lb], &c__1);
/* L20: */
    }
    return 0;
} /* dpbsl_ */

