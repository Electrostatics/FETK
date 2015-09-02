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
 * rcsid="$Id: mainSlu.c,v 1.3 2010/08/12 05:19:30 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     main.c
 *
 * Purpose:  Driver program for testing the SuperLU package.
 *
 * Notes:    The SuperLU code was developed at UC Berkeley, LBL, and Xerox.
 *           The test driver was modified from the example distributed with
 *           the SuperLU package.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include <mc/bam.h>

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
VEMBED(rcsid="$Id: mainSlu.c,v 1.3 2010/08/12 05:19:30 fetk Exp $")

int main(int argc, char *vargv[])
{
    double s, u, p, e, r, l, value, tmp, *a, b[5], x[5], true[5];
    int    i, j, k, m, n, nnz, *ia, *ja;
    Slu    *slu;
    int    skey; /* 0=row-wise YSMP structure, 1=col-wise YSMP structure */

    /* dimensions */
    m    = 5;  /* number of rows */
    n    = 5;  /* number of columns */
    nnz  = 12; /* number of nonzeros */

    /* malloc arrays (must do since SuperLU wants to free it later!) */
    ia = (int*)calloc( m+1, sizeof(int) );
    ja = (int*)calloc( nnz, sizeof(int) );
    a  = (double*)calloc( nnz, sizeof(double) );

    /* initialize the matrix (ia,ja,a) */
    s      = 19.0;
    u      = 21.0;
    p      = 16.0;
    e      = 5.0;
    r      = 18.0;
    l      = 12.0;
    a[0]   = s;
    a[1]   = l;
    a[2]   = l;
    a[3]   = u;
    a[4]   = l;
    a[5]   = l;
    a[6]   = u;
    a[7]   = p;
    a[8]   = u;
    a[9]   = e;
    a[10]  = u;
    a[11]  = r;
    ja[0]  = 0;
    ja[1]  = 1;
    ja[2]  = 4;
    ja[3]  = 1;
    ja[4]  = 2;
    ja[5]  = 4;
    ja[6]  = 0;
    ja[7]  = 2;
    ja[8]  = 0;
    ja[9]  = 3;
    ja[10] = 3;
    ja[11] = 4;
    ia[0]  = 0;
    ia[1]  = 3;
    ia[2]  = 6;
    ia[3]  = 8;
    ia[4]  = 10;
    ia[5]  = 12;

    /* choose solution */
    true[0] = 1.0;
    true[1] = 2.0;
    true[2] = 3.0;
    true[3] = 4.0;
    true[4] = 5.0;

    /* initialize rhs and solution to zero */
    for (i=0; i<n; i++)
        x[i] = 0.0;
    for (i=0; i<m; i++)
        b[i] = 0.0;

    /* now form rhs from chosen true solution via a matvec */

    /* TEST: ROW-WISE YSMP */
    /*
     * skey = 0;
     * for (i=0; i<m; i++) {
     *     for (k=ia[i]; k<ia[i+1]; k++) {
     *         j = ja[k];
     *         b[i] += ( a[k] * true[j] );
     *     }
     * }
     */

    /* TEST: COL-WISE YSMP */
    skey = 1;
    for (i=0; i<n; i++) {
        for (k=ia[i]; k<ia[i+1]; k++) {
            j = ja[k];
            b[j] += ( a[k] * true[i] );
        }
    }

    /* call the solver */
    slu = Slu_ctor(VNULL, skey, m, n, nnz, ia, ja, a);
    VASSERT( Slu_factor(slu) );
    VASSERT( Slu_solve(slu, 0, b, x) );
    Slu_dtor(&slu);

    /* check solution */
    value = 0.0;
    for (i=0; i<m; i++) {
        tmp = VABS( true[i] - x[i] );
        value += tmp*tmp;
        printf("t[%d]=%g   x[%d]=%g   e[%d]=%g\n",
            i, true[i], i, x[i], i, tmp);
    }
    fprintf(stderr, "l2-error=<%e>\n", sqrt(VABS(value)) );

    /* return */
    return 0;
}

