/* ./util_f77/iset.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>


/* ----------------------------------------------------------------------- */

/*     Only work with increment equal to 1 right now. */

/* Subroutine */ int iset_(integer *n, integer *value, integer *array, 
	integer *inc)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;



    /* Parameter adjustments */
    --array;

    /* Function Body */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	array[i__] = *value;
/* L10: */
    }

    return 0;
} /* iset_ */

