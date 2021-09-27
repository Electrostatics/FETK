
/*! @file slu_scomplex.h
 * \brief Header file for complex operations
 * <pre> 
 *  -- SuperLU routine (version 2.0) --
 * Univ. of California Berkeley, Xerox Palo Alto Research Center,
 * and Lawrence Berkeley National Lab.
 * November 15, 1997
 *
 * Contains definitions for various complex operations.
 * This header file is to be included in source files c*.c
 * </pre>
 */
#ifndef __SUPERLU_SCOMPLEX /* allow multiple inclusions */
#define __SUPERLU_SCOMPLEX


#ifndef SCOMPLEX_INCLUDE
#define SCOMPLEX_INCLUDE

typedef struct { float r, i; } realcomplex;


/* Macro definitions */

/*! \brief Complex Addition c = a + b */
#define c_add(c, a, b) { (c)->r = (a)->r + (b)->r; \
			 (c)->i = (a)->i + (b)->i; }

/*! \brief Complex Subtraction c = a - b */
#define c_sub(c, a, b) { (c)->r = (a)->r - (b)->r; \
			 (c)->i = (a)->i - (b)->i; }

/*! \brief Complex-Double Multiplication */
#define cs_mult(c, a, b) { (c)->r = (a)->r * (b); \
                           (c)->i = (a)->i * (b); }

/*! \brief Complex-Complex Multiplication */
#define cc_mult(c, a, b) { \
	float cr, ci; \
    	cr = (a)->r * (b)->r - (a)->i * (b)->i; \
    	ci = (a)->i * (b)->r + (a)->r * (b)->i; \
    	(c)->r = cr; \
    	(c)->i = ci; \
    }

#define cc_conj(a, b) { \
        (a)->r = (b)->r; \
        (a)->i = -((b)->i); \
    }

/*! \brief Complex equality testing */
#define c_eq(a, b)  ( (a)->r == (b)->r && (a)->i == (b)->i )


#ifdef __cplusplus
extern "C" {
#endif

/* Prototypes for functions in scomplex.c */
void c_div(realcomplex *, realcomplex *, realcomplex *);
double c_abs(realcomplex *);     /* exact */
double c_abs1(realcomplex *);    /* approximate */
void c_exp(realcomplex *, realcomplex *);
void r_cnjg(realcomplex *, realcomplex *);
double r_imag(realcomplex *);


#ifdef __cplusplus
  }
#endif

#endif

#endif  /* __SUPERLU_SCOMPLEX */
