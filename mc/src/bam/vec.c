/*
 * ***************************************************************************
 * MC = < Manifold Code >
 * Copyright (C) 1994-- Michael Holst 
 *
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either  
 * version 2.1 of the License, or (at your option) any later version. 
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details. 
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library; if not, write to the Free Software  
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   
 * 
 * rcsid="$Id: vec.c,v 1.26 2010/08/12 05:18:30 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     vec.c
 *
 * Purpose:  Class Vec: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "vec_p.h"

VEMBED(rcsid="$Id: vec.c,v 1.26 2010/08/12 05:18:30 fetk Exp $")

/*
 * ***************************************************************************
 * Class Vec: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_BAM)

#endif /* if !defined(VINLINE_BAM) */
/*
 * ***************************************************************************
 * Class Vec: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Vec_ctor
 *
 * Purpose:  The vector constructor (data array malloc'd by us).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Vec* Vec_ctor(Vmem *vmem, const char *name, int length)
{
    Vec *thee = VNULL;

    VDEBUGIO("Vec_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Vec) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Vec" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    VDEBUGIO("..done.\n");

    strncpy(thee->name, name, 10);
    thee->n = length;

    /* malloc the array */
    thee->iMallocU = 1;
    if (thee->n > 0) {
        thee->u = Vmem_malloc( thee->vmem, thee->n, sizeof(double) );
        VASSERT( thee->u != VNULL );
    }

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Vec_ctor2
 *
 * Purpose:  The vector constructor (data array passed in).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Vec* Vec_ctor2(Vmem *vmem, const char *name, int length, double *data)
{
    Vec *thee = VNULL;

    VDEBUGIO("Vec_ctor2: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Vec) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Vec" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    VDEBUGIO("..done.\n");

    strncpy(thee->name, name, 10);
    thee->n = length;

    /* snag the array */
    thee->iMallocU = 0;
    if (thee->n > 0) {
        thee->u = data;
        VASSERT( thee->u != VNULL );
    }

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Vec_dtor
 *
 * Purpose:  The vector destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_dtor(Vec **thee)
{
    /* VASSERT( (*thee) != VNULL ); */
    if ((*thee) != VNULL) {

        if ( (*thee)->iMallocU == 1 ) {
            if ( (*thee)->n > 0 ) {
                Vmem_free( (*thee)->vmem, (*thee)->n, sizeof(double),
                    (void**)&((*thee)->u) );
            }
        }

        VDEBUGIO("Vec_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Vec), (void**)thee );
        VDEBUGIO("..done.\n"); 

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Vec_len
 *
 * Purpose:  Length of a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Vec_len(Vec *thee)
{
    return thee->n;
}

/*
 * ***************************************************************************
 * Routine:  Vec_addr
 *
 * Purpose:  Address of a vector data.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double *Vec_addr(Vec *thee)
{
    return thee->u;
}

/*
 * ***************************************************************************
 * Routine:  Vec_val
 *
 * Purpose:  Return value of component of vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec_val(Vec *thee, int i)
{
    return (thee->u)[i];
}

/*
 * ***************************************************************************
 * Routine:  Vec_set
 *
 * Purpose:  Set value of component of vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_set(Vec *thee, int i, double val)
{
    (thee->u)[i] = val;
}

/*
 * ***************************************************************************
 * Routine:  Vec_nrm1
 *
 * Purpose:  1-norm of a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec_nrm1(Vec *thee)
{
    int i, n;
    double *u, tmp = 0.0;

    n = thee->n;
    u = thee->u;

    for (i=0; i<n; i++) tmp += VABS(u[i]);
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Vec_nrm2
 *
 * Purpose:  2-norm of a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec_nrm2(Vec *thee)
{
    int i, n;
    double *u, tmp = 0.0;

    n = thee->n;
    u = thee->u;

    for (i=0; i<n; i++) tmp += (u[i] * u[i]);
    return VSQRT(tmp);
}

/*
 * ***************************************************************************
 * Routine:  Vec_nrm8
 *
 * Purpose:  oo-norm of a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec_nrm8(Vec *thee)
{
    int i, n;
    double *u, tmp = 0.0;

    n = thee->n;
    u = thee->u;

    for (i=0; i<n; i++) tmp = VMAX2( tmp, VABS(u[i]) );
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Vec_dif1
 *
 * Purpose:  1-norm of a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec_dif1(Vec *thee, Vec *s)
{
    int i, n, m;
    double *u, *v, tmp = 0.0;

    n = thee->n;
    m = s->n;
    VASSERT( n == m );
    u = thee->u;
    v = s->u;

    for (i=0; i<n; i++) tmp += VABS(u[i]-v[i]);
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Vec_dif2
 *
 * Purpose:  2-norm of a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec_dif2(Vec *thee, Vec *s)
{
    int i, n, m;
    double *u, *v, tmp = 0.0;

    n = thee->n;
    m = s->n;
    VASSERT( n == m );
    u = thee->u;
    v = s->u;

    for (i=0; i<n; i++) tmp += ( (u[i]-v[i]) * (u[i]-v[i]) );
    return VSQRT(tmp);
}

/*
 * ***************************************************************************
 * Routine:  Vec_dif8
 *
 * Purpose:  oo-norm of a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec_dif8(Vec *thee, Vec *s)
{
    int i, n, m;
    double *u, *v, tmp = 0.0;

    n = thee->n;
    m = s->n;
    VASSERT( n == m );
    u = thee->u;
    v = s->u;

    for (i=0; i<n; i++) tmp = VMAX2( tmp, VABS( u[i]-v[i] ) );
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Vec_dot
 *
 * Purpose:  dot product of two vectors.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec_dot(Vec *thee, Vec *s)
{
    int i, n, m;
    double *u, *v, tmp = 0.0;

    n = thee->n;
    m = s->n;
    VASSERT( n == m );
    u = thee->u;
    v = s->u;

    for (i=0; i<n; i++) tmp += (u[i] * v[i]);
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Vec_init
 *
 * Purpose:  initialize a vector to be a constant.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_init(Vec *thee, double val)
{
    int i, n;
    double *u;

    n = thee->n;
    u = thee->u;

    for (i=0; i<n; i++) u[i] = val;
}

/*
 * ***************************************************************************
 * Routine:  Vec_scal
 *
 * Purpose:  vector scale.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_scal(Vec *thee, double val)
{
    int i, n;
    double *u;

    n = thee->n;
    u = thee->u;

    for (i=0; i<n; i++) u[i] *= val;
}

/*
 * ***************************************************************************
 * Routine:  Vec_copy
 *
 * Purpose:  vector copy.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_copy(Vec *thee, Vec *s)
{
    int i, n, m;
    double *u, *v;

    n = thee->n;
    m = s->n;
    VASSERT( n == m );
    u = thee->u;
    v = s->u;

    for (i=0; i<n; i++) u[i] = v[i];
}

/*
 * ***************************************************************************
 * Routine:  Vec_axpy
 *
 * Purpose:  scalar times vector plus vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_axpy(Vec *thee, Vec *s, double val)
{
    int i, n, m;
    double *u, *v;

    n = thee->n;
    m = s->n;
    VASSERT( n == m );
    u = thee->u;
    v = s->u;

    for (i=0; i<n; i++) u[i] += (val * v[i]);
}

/*
 * ***************************************************************************
 * Routine:  Vec_print
 *
 * Purpose:  print a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_print(Vec *thee)
{
    int i;

    Vnm_print(0, "%s = [\n", thee->name);
    for (i=0; i<thee->n; i++) {
        Vnm_print(0, "    %15.8e\n", thee->u[i]);
    }
    Vnm_print(0, "];\n");
}

/*
 * ***************************************************************************
 * Routine:  Vec_printSp
 *
 * Purpose:  print a vector.
 *
 *   Notes:  pflag==0 ==> write
 *           pflag==1 ==> append
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_printSp(Vec *thee, char *fname, int pflag)
{
    int i;
    FILE *fp;

    if (pflag == 0) {
        fp=fopen(fname,"w");
    } else if (pflag == 1) {
        fp=fopen(fname,"a");
    } else {
        fp=VNULL;
    }

    if (fp==VNULL) {
        Vnm_print(2, "Vec_print: problem opening file <%s>\n", fname);
    } else {
        fprintf(fp, "%s = [\n", thee->name);
        for (i=0; i<thee->n; i++) {
            fprintf(fp, "    %15.8e\n", thee->u[i]);
        }
        fprintf(fp, "];\n");
        fclose(fp);
    }
}

/*
 * ***************************************************************************
 * Routine:  Vec_diagScale
 *
 * Purpose:  Apply inverse of diagonal to a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_diagScale(Vec *thee, Mat *amat, Vec *f)
{
    int i, numR;
    double *uu, *ff, *diag;

    /* some local variable pointers for speed and readability */
    numR = amat->numR;
    uu   = Vec_addr(thee);
    ff   = Vec_addr(f);
    diag = amat->diag;

    /* basic error checks */
    VASSERT( Vec_len(thee) == Mat_numR(amat) );
    VASSERT( amat->format == DRC_FORMAT );
    VASSERT( amat->state  == ASSEMBLED_STATE );

    /* invert the diagonal */
    for (i=0; i<numR; i++) {
        uu[i] = ff[i] / diag[i];
    }
}

/*
 * ***************************************************************************
 * Routine:  Vec_matvec
 *
 * Purpose:  Matrix times vector.
 *
 * Notes:    The input parameters are interpreted thusly:
 *
 *               part   = which part of matrix to use for the matvec
 *                        (0=A=D+L+U, 1=D, 2=D+L, 3=D+U, 4=L+U)
 *                        (NOTE: part!=0 only well-defined for DRC)
 *
 *               key    = which of A or A' to use for the matvec
 *                        (0=A, 1=A', 2=A(accumulate), 3=A'(accumulate))
 *                        (NOTE: 0=prolongate, 1=restrict, for PRO)
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_matvec(Vec *thee, Mat *amat, Vec *v, int key, int part)
{
    int i, j, k, numR, numC, uu_len, vv_len, ibase;
    int *IA, *JA;
    double *A, *uu, *vv;
    double *diag, *offU, *offL;

    /* some local variable pointers for speed and readability */
    numR   = Mat_numR(amat);
    numC   = Mat_numC(amat);
    uu     = Vec_addr(thee);
    vv     = Vec_addr(v);
    uu_len = Vec_len(thee);
    vv_len = Vec_len(v);

    /* do the product */
    if (amat->format == ZERO_FORMAT) {

        /* check dimensions:  non-square matrix allowed */
        /* uu_len and vv_len: allow to be LONGER than needed (supports HB) */
        if ((key == 0) || (key == 2)) {
            VASSERT( vv_len >= numC );
            VASSERT( uu_len >= numR );
        } else { /* ((key == 1) || (key == 3)) */
            VASSERT( vv_len >= numR );
            VASSERT( uu_len >= numC );
        }

        /* deal with accumulation issue */
        if ((key == 0) || (key == 1)) {
            for (i=0; i<numR; i++) {
                uu[i] = 0.;
            }
        } else { /* ((key == 2) || (key == 3)) */
            /* no-op (accumulate as y+=Ax or y+=A'x) */
        }

    } else if (amat->format == DRC_FORMAT) {

        /* basic error checks */
        VASSERT( amat->state == ASSEMBLED_STATE );

        /* check dimensions: only square matrix allowed */
        VASSERT( numR == numC );

        /* uu_len and vv_len: allow to be LONGER than needed (supports HB) */
        if ((key == 0) || (key == 2)) {
            VASSERT( vv_len >= numC );
            VASSERT( uu_len >= numR );
        } else { /* ((key == 1) || (key == 3)) */
            VASSERT( vv_len >= numR );
            VASSERT( uu_len >= numC );
        }

        /* setup aliases */
        IA   = amat->IA;
        JA   = amat->JA;
        A    = amat->A;
        diag = amat->diag;
        /* u = A * v */
        if ((key == 0) || (key == 2)) {
            offU = amat->offU;
            offL = amat->offL;
        /* u = A' * v */
        } else { /* ((key == 1) || (key == 3)) */
            offU = amat->offL;
            offL = amat->offU;
        }

        /* deal with accumulation issue */
        if ((key == 0) || (key == 1)) {
            for (i=0; i<numR; i++) {
                uu[i] = 0.;
            }
        } else { /* ((key == 2) || (key == 3)) */
            /* no-op (accumulate as y+=Ax or y+=A'x) */
        }

        /* do the product */
        if (part == 0) { /* useD && useL && useU */
            for (i=0; i<numR; i++) {
                uu[i] += ( diag[i] * vv[i]  );
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    uu[i] += ( offU[k] * vv[j] );
                    uu[j] += ( offL[k] * vv[i] );
                }
            }
        } else if (part == 1) { /* useD && (!useL) && (!useU) */
            for (i=0; i<numR; i++) {
                uu[i] += ( diag[i] * vv[i]  );
            }
        } else if (part == 2) { /* useD && useL && (!useU) */
            for (i=0; i<numR; i++) {
                uu[i] += ( diag[i] * vv[i]  );
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    uu[j] += ( offL[k] * vv[i] );
                }
            }
        } else if (part == 3) { /* useD && (!useL) && useU */
            for (i=0; i<numR; i++) {
                uu[i] += ( diag[i] * vv[i]  );
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    uu[i] += ( offU[k] * vv[j] );
                }
            }
        } else if (part == 4) { /* (!useD) && useL && useU */
            for (i=0; i<numR; i++) {
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    uu[i] += ( offU[k] * vv[j] );
                    uu[j] += ( offL[k] * vv[i] );
                }
            }
        } else { VASSERT(0); }

    } else if (amat->format == ROW_FORMAT) {

        /* basic error checks */
        VASSERT( part == 0 );
        VASSERT( amat->state == ASSEMBLED_STATE );

        /* handle implicit diagonal identity block that is not stored */
        if (Mat_impl(amat) == IS_IMPL) {
            ibase = numC;
        } else {
            ibase = 0;
        }

        /* check dimensions: non-square matrix allowed */
        /* uu_len and vv_len: allow to be LONGER than needed (supports HB) */
        if ((key == 0) || (key == 2)) {
            VASSERT( vv_len >= numC );
            VASSERT( uu_len >= (numR+ibase) );
        } else { /* ((key == 1) || (key == 3)) */
            VASSERT( vv_len >= (numR+ibase) );
            VASSERT( uu_len >= numC );
        }

        /* setup aliases */
        IA = amat->IA;
        JA = amat->JA;
        A  = amat->A;

        /* deal with accumulation issue */
        if ((key == 0) || (key == 1)) {
            for (i=0; i<numR; i++) {
                uu[i+ibase] = 0.;
            }
        } else { /* ((key == 2) || (key == 3)) */
            /* no-op (accumulate as y+=Ax or y+=A'x) */
        }

        /* do the product */
        /* NOTE:  (key=0 ==> prolongate) && (key=1 ==> restrict) */
        if ((key == 0) || (key == 2)) {

            /* apply the implicit identity block on the TOP of the matrix */
            for (i=0; i<ibase; i++) {
                uu[i] = vv[i];
            }

            /* apply the part of the matrix we are actually storing */
            for (i=0; i<numR; i++) {
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    uu[i+ibase] += (A[k] * vv[j]);
                }
            }

        } else { /* ((key == 1) || (key == 3)) */

            /* apply the implicit identity block on the LEFT of the matrix */
            /* NO-OP: we assume/enforce zero dirichlet right here!!! */

            /* apply the part of the matrix we are actually storing */
            for (i=0; i<numR; i++) {
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    uu[j] += (A[k] * vv[i]);
                }
            }
        }

    } else if (amat->format == COL_FORMAT) {

        /* basic error checks */
        VASSERT( part == 0 );
        VASSERT( amat->state == ASSEMBLED_STATE );

        /* check dimensions: non-square matrix allowed */
        /* uu_len and vv_len: allow to be LONGER than needed (supports HB) */
        if ((key == 0) || (key == 2)) {
            VASSERT( vv_len >= numC );
            VASSERT( uu_len >= numR );
        } else { /* ((key == 1) || (key == 3)) */
            VASSERT( vv_len >= numR );
            VASSERT( uu_len >= numC );
        }

        /* setup aliases */
        IA = amat->IA;
        JA = amat->JA;
        A  = amat->A;

        /* deal with accumulation issue */
        if ((key == 0) || (key == 1)) {
            for (i=0; i<numR; i++) {
                uu[i] = 0.;
            }
        } else { /* ((key == 2) || (key == 3)) */
            /* no-op (accumulate as y+=Ax or y+=A'x) */
        }

        /* do the product */
        if ((key == 0) || (key == 2)) {
            for (i=0; i<numC; i++) {
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    uu[j] += (A[k] * vv[i]);
                }
            }
        } else { /* ((key == 1) || (key == 3)) */
            for (i=0; i<numC; i++) {
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    uu[i] += (A[k] * vv[j]);
                }
            }
        }

    } else if (amat->format == SLU_FORMAT) {
        VASSERT( part == 0 );
        VASSERT(0);
    } else if (amat->format == RLN_FORMAT) {
        VASSERT( part == 0 );
        VASSERT(0);
    } else if (amat->format == CLN_FORMAT) {
        VASSERT( part == 0 );
        VASSERT(0);
    } else if (amat->format == RFL_FORMAT) {
        VASSERT( part == 0 );
        VASSERT(0);
    } else if (amat->format == CFL_FORMAT) {
        VASSERT( part == 0 );
        VASSERT(0);
    } else { VASSERT(0); }
}

/*
 * ***************************************************************************
 * Routine:  Vec_smooth
 *
 * Purpose:  Generic smoothing operator.
 *
 * Notes:    The input parameters are interpreted thusly:
 *
 *               key    = smooth with A or A' (0=A, 1=A')
 *               ioflag = debug output level (0=normal, 1=none, 2=lots, ... )
 *               meth   = smoother choice (0=jac, 1=gs, ... )
 *               itmax  = number of iterations to do (the maximum allowed)
 *               etol   = error tolerance (currently ignored)
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_smooth(Vec *thee, Mat *amat, Vec *f, Vec *w,
    int key, int ioflag, int meth, int adj, int itmax, double etol,
    double omega)
{
    if (meth == 0) {
        Vec_jac(thee, amat, f, w, key, ioflag, itmax, etol, omega);
    } else if (meth == 1) {
        Vec_gs(thee, amat, f, w, key, ioflag, adj, itmax, etol);
    } else { VASSERT(0); }
}

/*
 * ***************************************************************************
 * Routine:  Vec_jac
 *
 * Purpose:  Jacobi iteration. 
 *
 * Notes:    The input parameters are interpreted thusly:
 *
 *               key    = smooth with A or A' (0=A, 1=A')
 *               ioflag = debug output level (0=normal, 1=none, 2=lots, ... )
 *               itmax  = number of iterations to do (the maximum allowed)
 *               etol   = error tolerance (currently ignored)
 *               omega  = iteration parameter
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_jac(Vec *thee, Mat *amat, Vec *f, Vec *w,
    int key, int ioflag, int itmax, double etol, double omega)
{
    int i, j, k, iters, numR;
    int *IA, *JA;
    double *uu, *ww, *ff;
    double *diag, *offU, *offL;

    /* some local variable pointers for speed and readability */
    numR = amat->numR;
    uu   = Vec_addr(thee);
    ww   = Vec_addr(w);
    ff   = Vec_addr(f);
    IA   = amat->IA;
    JA   = amat->JA;
    diag = amat->diag;
    /* u = smooth(A,f,v) */
    if (key == 0) {
        offU = amat->offU;
        offL = amat->offL;
    /* u = smooth(A',f,v) */
    } else { /* (key == 1) */
        offU = amat->offL;
        offL = amat->offU;
    }

    /* basic error checks */
    VASSERT( etol   == 0. );
    VASSERT( ioflag == 1 );
    VASSERT( Vec_len(thee) == Vec_len(f) );
    VASSERT( Vec_len(thee) == Vec_len(w) );
    VASSERT( Vec_len(thee) == Mat_numR(amat) );

    /* we only do DRC */
    VASSERT( amat->format == DRC_FORMAT );
    VASSERT( amat->state  == ASSEMBLED_STATE );

    iters = 0;
    while ((iters < itmax) && (!Vnm_sigInt())) {
        iters++;

        /* ww = ff - U*uu */
        for (i=0; i<numR; i++) {
            ww[i] = ff[i];
            /* handle row-at-a-time */
            for (k=IA[i]; k<IA[i+1]; k++) {
                j = JA[k];
                ww[i] -= ( offU[k] * uu[j] );
            }
        }

        /* ww = ww - L*uu */
        for (i=0; i<numR; i++) {
            /* handle column-at-a-time */
            for (k=IA[i]; k<IA[i+1]; k++) {
                j = JA[k];
                ww[j] -= ( offL[k] * uu[i] );
            }
        }

        /* uu = D^{-1} * ww */
        for (i=0; i<numR; i++) {
            /* solve for guy on diag in current row */
            uu[i] = ww[i] / diag[i];
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Vec_gs
 *
 * Purpose:  Gauss-Seidel iteration.
 *
 * Notes:    The input parameters are interpreted thusly:
 *
 *               key    = smooth with A or A' (0=A, 1=A')
 *               ioflag = debug output level (0=normal, 1=none, 2=lots, ... )
 *               adj    = adjoint choice (0=normal, 1=adjoint)
 *               itmax  = number of iterations to do (the maximum allowed)
 *               etol   = error tolerance (currently ignored)
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_gs(Vec *thee, Mat *amat, Vec *f, Vec *w,
    int key, int ioflag, int adj, int itmax, double etol)
{
    int i, j, k, iters, numR;
    int *IA, *JA;
    double *uu, *ww, *ff;
    double *diag, *offU, *offL;

    /* some local variable pointers for speed and readability */
    numR = amat->numR;
    uu   = Vec_addr(thee);
    ww   = Vec_addr(w);
    ff   = Vec_addr(f);
    IA   = amat->IA;
    JA   = amat->JA;
    diag = amat->diag;
    /* u = smooth(A,f,v) */
    if (key == 0) {
        offU = amat->offU;
        offL = amat->offL;
    /* u = smooth(A',f,v) */
    } else { /* (key == 1) */
        offU = amat->offL;
        offL = amat->offU;
    }

    /* basic error checks */
    VASSERT( etol   == 0. );
    VASSERT( ioflag == 1 );
    VASSERT( Vec_len(thee) == Vec_len(f) );
    VASSERT( Vec_len(thee) == Vec_len(w) );
    VASSERT( Vec_len(thee) == Mat_numR(amat) );

    /* we only do DRC */
    VASSERT( amat->format == DRC_FORMAT );
    VASSERT( amat->state  == ASSEMBLED_STATE );

    iters = 0;
    while ((iters < itmax) && (!Vnm_sigInt())) {
        iters++;

        if (adj == 0) {

            /* ww = ff - U*uu */
            for (i=0; i<numR; i++) {
                /* initialize ww[i] */
                ww[i] = ff[i];
                /* now handle this row */
                    for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    ww[i] -= ( offU[k] * uu[j] );
                }
            }

            /* uu = (D-L)^{-1} * ww */
            for (i=0; i<numR; i++) {
                /* solve for guy on diag in current row */
                uu[i] = ww[i] / diag[i];
                /* propagate result column-at-a-time */
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    ww[j] -= ( offL[k] * uu[i] );
                }
            }

        } else { /* (adj == 1) */

            /* ww = ff - L*uu */
            for (i=0; i<numR; i++) {
                ww[i] = ff[i];
            }
            for (i=0; i<numR; i++) {
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    ww[j] -= ( offL[k] * uu[i] );
                }
            }

            /* uu = (D-U)^{-1} * ww */
            for (i=numR-1; i>=0; i--) {
                /* solve row-at-a-time */
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    ww[i] -= ( offU[k] * uu[j] );
                }
                uu[i] = ww[i] / diag[i];
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Vec_bnd
 *
 * Purpose:  Apply boundary condition.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_bnd(Vec *thee, Mat *mat, int key)
{
    int i, ibase;
    double *uu;

    uu = Vec_addr(thee);

    /* offset row indices in the case of implicit identity */
    ibase = (mat->impl == IS_IMPL) ? mat->numC : 0;

    if (key == 0) {
        VASSERT( thee->n == (Mat_numR(mat)+ibase) );
        for (i=0; i<mat->numBR; i++) {
            uu[ mat->BR[i] ] = 0.0;
        }
    } else {
        VASSERT( thee->n == Mat_numC(mat) );
        for (i=0; i<mat->numBC; i++) {
            uu[ mat->BC[i] ] = 0.0;
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Vec_absLog
 *
 * Purpose:  Log of abs value of entries of block vector, shifted by <val>
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec_absLog(Vec *thee, double val)
{
    int i;
    double *uu;

    uu = Vec_addr(thee);

    for (i=0; i<thee->n; i++) {
        uu[i] = VLOG( VABS( uu[i] ) + val );
    }

}
