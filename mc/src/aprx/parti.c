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
 * rcsid="$Id: parti.c,v 1.8 2010/08/12 05:18:19 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     parti.c
 *
 * Purpose:  Class Aprx: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "aprx_p.h"

VEMBED(rcsid="$Id: parti.c,v 1.8 2010/08/12 05:18:19 fetk Exp $")

/*
 * ***************************************************************************
 * Class Aprx: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_NAM)

#endif /* if !defined(VINLINE_NAM) */
/*
 * ***************************************************************************
 * Class Aprx: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Aprx_partSet
 *
 * Purpose:  Clear the partitioning (set all colors to pcolor).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_partSet(Aprx *thee, int pcolor)
{
    int i;

    Vnm_print(0,"Aprx_partSet: [pc=%d] resetting partitioning..", pcolor);

    /* clear the mesh coloring */
    for (i=0; i<Gem_numSS(thee->gm); i++) {
        SS_setChart(Gem_SS(thee->gm,i), pcolor);
    }
    Vnm_print(0,"..done.\n");
    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_partSmooth
 *
 * Purpose:  Smooth the partitioning.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_partSmooth(Aprx *thee)
{
    int i, j, dim, max, maxc, tcount, myc, mycount;
    int c[4], count[4];
    SS *sm, *sm0;

    Vnm_print(0,"Aprx_partSmooth: smoothing partitioning..");

    dim = Gem_dim(thee->gm);

    /* smooth the mesh coloring */
    tcount = 0;
    for (i=0; i<Gem_numSS(thee->gm); i++) {
        sm = Gem_SS(thee->gm, i);

        myc = SS_chart(sm);
        mycount = 0;

        for (j=0; j<4; j++) {
            count[j] = 0;
            c[j] = -1;
        }

        for (j=0; j<Gem_dimVV(thee->gm); j++) {
            sm0 = SS_nabor(sm,j);
            if (sm0 != VNULL) {
                if ((int)SS_chart(sm0) == myc) {
                    mycount++;
                } else {
                    count[j] = 1;
                    c[j] = SS_chart(sm0);
                }
            }
        }

        if ((c[0] >= 0) && (c[0] == c[1])) count[0]++;
        if ((c[0] >= 0) && (c[0] == c[2])) count[0]++;
        if ((c[0] >= 0) && (c[0] == c[3])) count[0]++;

        if ((c[1] >= 0) && (c[1] == c[0])) count[1]++;
        if ((c[1] >= 0) && (c[1] == c[2])) count[1]++;
        if ((c[1] >= 0) && (c[1] == c[3])) count[1]++;

        if ((c[2] >= 0) && (c[2] == c[0])) count[2]++;
        if ((c[2] >= 0) && (c[2] == c[1])) count[2]++;
        if ((c[2] >= 0) && (c[2] == c[3])) count[2]++;

        if (dim == 3) {
            if ((c[3] >= 0) && (c[3] == c[0])) count[3]++;
            if ((c[3] >= 0) && (c[3] == c[1])) count[3]++;
            if ((c[3] >= 0) && (c[3] == c[2])) count[3]++;
        }

        max  = mycount;
        maxc = -1;
        for (j=0; j<Gem_dimVV(thee->gm); j++) {
            if (count[j] > max) {
                max  = count[j];
                maxc = j;
            }
        }

        if (max > mycount) {
            SS_setChart(sm, c[maxc]);
            tcount++;
        }
    }
    Vnm_print(0,"..done. [%d simplices changed color]\n", tcount);
    return tcount;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_partInert
 *
 * Purpose:  Partition the domain using inertial bisection.
 *           Partition sets of points in R^d (d=2 or d=3) by viewing them
 *           as point masses of a rigid body, and by then employing the
 *           classical mechanics ideas of inertia and Euler axes.
 *
 * Notes:    We first locate the center of mass, then change the coordinate
 *           system so that the center of mass is located at the origin.
 *           We then form the (symmetric) dxd inertia tensor, and then find
 *           the set of (real) eigenvalues and (orthogonal) eigenvectors.
 *           The eigenvectors represent the principle inertial rotation axes,
 *           and the eigenvalues represent the inertial strength in those
 *           principle directions.  The smallest inerial component along an
 *           axis represents a direction along which the rigid body is most
 *           "line-like" (assuming all the points have the same mass).
 *
 *           For our purposes, it makes sense to using the axis (eigenvector)
 *           corresponding to the smallest inertia (eigenvalue) as the line to
 *           bisect with a line (d=2) or a plane (d=3).  We know the center of
 *           mass, and once we also have this particular eigenvector, we can
 *           effectively bisect the point set into the two regions separated
 *           by the line/plane simply by taking an inner-product of the
 *           eigenvector with each point (or rather the 2- or 3-vector
 *           representing the point).  A positive inner-product represents one
 *           side of the cutting line/plane, and a negative inner-product
 *           represents the other side (a zero inner-product is right on the
 *           cutting line/plane, so we arbitrarily assign it to one region or
 *           the other).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_partInert(Aprx *thee, int pcolor,
    int numC, double *evec, simHelper *simH)
{
    int i, j, k, lambdaI;
    double rad, sca, lambda, normal, caxis[3];
    Mat3 I, II, V, D;

    Vnm_print(0,"Aprx_partInert: WARNING: assuming single-chart manifold.\n");
    Vnm_print(0,"Aprx_partInert: [pc=%d] partitioning:\n", pcolor);

    /* form the inertia tensors */
    Mat3_eye(I);
    Mat3_init(II, 0.);
    for (i=0; i<numC; i++) {

        /* get vector length (squared!) */
        rad = 0.;
        for (j=0; j<3; j++) {
            rad += ( simH[i].bc[j] * simH[i].bc[j] );
        }

        /* add contribution to the inertia tensor */
        for (j=0; j<3; j++) {
            for (k=0; k<3; k++) {
                II[j][k] += ( simH[i].mass *
                    (I[j][k]*rad - simH[i].bc[j]*simH[i].bc[k]) );
            }
        }
    }

    /* find the d-principle axes, and isolate the single axis we need */
    /* (the principle axis we want is the one with SMALLEST moment) */
    sca = Mat3_nrm8(II);
    Mat3_scal(II, 1./sca);
    (void)Mat3_qri(V, D, II);
    lambda  = VLARGE;
    lambdaI = -1;
    for (i=0; i<3; i++) {
        if ( VABS(D[i][i]) < lambda ) {
            lambda  = VABS(D[i][i]);
            lambdaI = i;
        }
    }
    VASSERT( lambda > 0. );
    VASSERT( lambda != VLARGE );
    VASSERT( lambdaI >= 0 );
    for (i=0; i<3; i++) {
        caxis[i] = V[i][lambdaI];
    }
    normal = Vec3_nrm2(caxis);
    VASSERT( normal > 0. );
    Vec3_scal(caxis,1./normal);

    /* decompose points based on bisecting principle axis with a line or */
    /* plane; we do this using an inner-product test with normal vec "caxis" */
    normal = 0;
    for (i=0; i<numC; i++) {
        evec[i] = Vec3_dot( simH[i].bc, caxis );
        normal += (evec[i]*evec[i]);
    }
    normal = VSQRT( normal );

    /* normalize the final result */
    for (i=0; i<numC; i++) {
        evec[i] = evec[i] / normal;
    }

    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_partSpect
 *
 * Purpose:  Partition the domain using spectral bisection.
 *
 * Notes:    We solve the following generalized eigenvalue problem:
 *
 *                Ax = lambda Bx
 *
 *           for second smallest eigenpair.  We then return the eigenvector
 *           from the pair.  We make this happen by turning it into a
 *           regular eigenvalue problem:
 *
 *               B^{-1/2} A B^{-1/2} ( B^{1/2} x ) = lambda ( B^{1/2} x )
 *
 *           or rather
 *
 *               C y = lambda y,   where C=B^{-1/2}AB^{-1/2}, y=B^{1/2}x.
 *
 *           The matrix "B" is simply a diagonal matrix with a (positive)
 *           error estimate for the element on the diagonal.  Therefore, the
 *           matrix B^{-1/2} is a well-defined positive diagonal matrix.
 *
 *           We explicitly form the matrix C and then send it to the inverse
 *           Rayleigh-quotient iteration to recover the second smallest
 *           eigenpair.  On return, we scale the eigenvector y by B^{-1/2} to
 *           recover the actual eigenvector x = B^{-1/2} y.
 *
 *           To handle the possibility that an element has zero error, in
 *           which case the B matrix had a zero on the diagonal, we set the
 *           corresponding entry in B^{-1/2} to be 1.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_partSpect(Aprx *thee, int pcolor,
    int numC, double *evec, simHelper *simH,
    int *ford, int *rord, int general)
{
    int i, j, k, dim, itmax, litmax, key, flag;
    int numF, *IA, *JA;
    int numB, numR[MAXV];
    MATsym psym[MAXV][MAXV];
    MATmirror pmirror[MAXV][MAXV];
    MATformat pfrmt[MAXV][MAXV];
    int numO[MAXV][MAXV], *IJA[MAXV][MAXV];
    double lambda, normal, etol, letol, value;
    SS *sm, *sm0;
    VV *v[4];
    Bmat *A;
    Bvec *u, *B2, *B2inv;

    Vnm_print(0,"Aprx_partSpect: [pc=%d] partitioning:\n", pcolor);

    /* dimensions */
    dim  = Gem_dim(thee->gm);

    /* go through the elements and enumerate elements and faces */
    numF=0;
    for (i=0; i<numC; i++) {
        sm = Gem_SS(thee->gm,ford[i]);

        for (j=0;j<(int)SS_dimVV(sm);j++) {

            /* get the vertex pointers for this face */
            for (k=0; k<dim; k++) {
                v[k] = SS_vertex( sm, vmapF[j][k] );
            }

            /* do we already know our nabor */
            if (dim == 2) {

                /* find the unique face nabor (if not on boundary) */
                sm0 = VV_commonSimplex2(v[0],v[1],sm);
            } else { /* (dim == 3) */

                /* find the unique face nabor (if not on boundary) */
                sm0 = VV_commonSimplex3(v[0],v[1],v[2],sm);
            }

            /* okay we found a nabor */
            if (sm0 != VNULL) {
                if ((int)SS_chart(sm0) == pcolor) {
                    simH[i].diag++;
                    k = rord[ SS_id(sm0) ];
                    if (k > i) {
                        simH[i].faceId[j] = k;
                        numF++;
                    }
                }
            }
        }
    } /* el; loop over elements */

    /* sort the rows and build matrix integer structures */
    IJA[0][0] = Vmem_malloc( thee->vmem, numC+1+numF, sizeof(int) );
    IA        = IJA[0][0];
    JA        = IA + numC + 1;
    k = 0;
    IA[0] = 0;
    for (i=0; i<numC; i++) {
        Vnm_qsort(simH[i].faceId, 4);
        for (j=0; j<4; j++) {
            if (simH[i].faceId[j] > i) {
                JA[k] = simH[i].faceId[j];
                k++; 
            }
        }
        IA[i+1] = k;
    }
    VASSERT( k == numF );

    /* create the real matrix object (creating space for matrix entries) */
    numB          = 1;
    numR[0]       = numC;
    numO[0][0]    = numF;
    psym[0][0]    = IS_SYM;        /* symmetric */
    pmirror[0][0] = ISNOT_MIRROR;  /* really exists */
    pfrmt[0][0]   = DRC_FORMAT;    /* YSMP-bank */
    A = Bmat_ctor( thee->vmem, "A", numB, numR, numR, pmirror );
    Bmat_initStructure( A, pfrmt, psym, numO, IJA );

    /* create the eigenvector */
    u = Bvec_ctor( thee->vmem, "u", numB, numR );

    /* create the scaling matrix */
    B2    = Bvec_ctor( thee->vmem, "B2",    numB, numR );
    B2inv = Bvec_ctor( thee->vmem, "B2inv", numB, numR );
    for (i=0; i<numC; i++) {
        if ( general ) {
            if ( simH[i].error > 0. ) {
                Bvec_setB( B2,    0, i,    VSQRT(simH[i].error) );
                Bvec_setB( B2inv, 0, i, 1./VSQRT(simH[i].error) );
            } else if ( simH[i].error == 0. ) {
                Bvec_setB( B2,    0, i, 1. );
                Bvec_setB( B2inv, 0, i, 1. );
            } else { VASSERT(0); }
        } else {
            Bvec_setB( B2,    0, i, 1. );
            Bvec_setB( B2inv, 0, i, 1. );
        }
    }

    /* now build the scaled adjacency matrix entries */
    k = 0;
    for (i=0; i<numC; i++) {
        value = (double)simH[i].diag
              * Bvec_valB( B2inv, 0, i ) 
              * Bvec_valB( B2inv, 0, i );
        Bmat_set( A, 0, 0, i, i, value );
        for (j=0; j<4; j++) {
            if (simH[i].faceId[j] > i) {
                value = -1. 
                      * Bvec_valB( B2inv, 0, i )
                      * Bvec_valB( B2inv, 0, simH[i].faceId[j] );
                Bmat_set( A, 0, 0, i, simH[i].faceId[j], value );
                k++;
            }
        }
    }
    VASSERT( k == numO[0][0] );

    /* the initial approximation */
    for (i=0; i<numC; i++) {
        Bvec_setB( u, 0, i, evec[i] );
    }

    /* print out matrix for testing */
    /* Bmat_printSp(A, "lap.m"); */

    /* finally, get eigenvector #2 (this is the costly part...) */
    litmax = 500;
    letol  = 1.0e-3;
    lambda = 0.;
    key    = 0;
    flag   = 0;
    itmax  = 50;
    etol   = 1.0e-4;
    Bvec_eig(u, A, litmax, letol, &lambda, key, flag, itmax, etol);

    /* re-scale the final approximation */
    normal = 0;
    for (i=0; i<numC; i++) {
        evec[i] = Bvec_valB( B2inv, 0, i ) * Bvec_valB( u, 0, i );
        normal += (evec[i]*evec[i]);
    }
    normal = VSQRT( normal );

    /* normalize the final result */
    for (i=0; i<numC; i++) {
        evec[i] = evec[i] / normal;
    }

    /* destroy the adjacency matrix and eigenvector */
    Bmat_dtor( &A ); /* this frees our earlier IJA malloc! */
    Bvec_dtor( &B2 );
    Bvec_dtor( &B2inv );
    Bvec_dtor( &u );

    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_partOne
 *
 * Purpose:  Do a single bisection step.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_partOne(Aprx *thee, int pkey, int pwht, int pcolor, int poff)
{
    int i, j, k, ii, dim, rc, numC, numS, sCount1, sCount2, cutOff;
    int *pord, *ford, *rord;
    double tm, cm[3], *evec, eCount1, eCount2, ecutOff, ePart;
    simHelper *simH;
    SS *sm;

    Vnm_print(0,"Aprx_partOne: [pcolor=%d] partitioning:\n", pcolor);

    /* dimensions */
    dim  = Gem_dim(thee->gm);
    numS = Gem_numSS(thee->gm);

    /* how many guys of this color */
    numC = 0;
    for (i=0; i<numS; i++) {
        sm = Gem_SS(thee->gm,i);
        if ((int)SS_chart(sm) == pcolor) numC++;
    }

    /* grab some temporary storage */
    pord = Vmem_malloc( thee->vmem, numC, sizeof(int) );
    ford = Vmem_malloc( thee->vmem, numC, sizeof(int) );
    rord = Vmem_malloc( thee->vmem, numS, sizeof(int) );
    evec = Vmem_malloc( thee->vmem, numC, sizeof(double) );
    simH = Vmem_malloc( thee->vmem, numC, sizeof(simHelper) );

    /* build the simplex helper vector and forward/reverse ordering arrays */
    ePart = 0.;
    tm = 0.;
    for (i=0; i<3; i++) cm[i] = 0.;
    i = 0;
    for (ii=0; ii<Gem_numSS(thee->gm); ii++) {
        sm = Gem_SS(thee->gm,ii);
        if ((int)SS_chart(sm) == pcolor) {

            /* initialization */
            pord[i] = i;
            ford[i] = ii;
            rord[ii] = i;
            evec[i] = 0.;
            simH[i].color = SS_chart(sm);
            simH[i].diag  = 0;
            simH[i].mass  = 1.;
            simH[i].error = Bvec_valB( thee->wev, 0, ii );
            for (j=0; j<4; j++) {
                simH[i].faceId[j] = -1;
            }

            /* accumulate error into total for this partition */
            ePart += simH[i].error;

            /* baricenter of this simplex and center of mass of all */
            tm += simH[i].mass;
            for (j=0; j<3; j++) {
                simH[i].bc[j] = 0.;
                for (k=0; k<dim+1; k++) {
                    simH[i].bc[j] += VV_coord(SS_vertex(sm,k),j);
                }
                simH[i].bc[j] /= (dim+1.);
                cm[j] += (simH[i].mass * simH[i].bc[j]);
            }

            i++;
        } else {
            rord[ii] = -1;
        }
    }
    VASSERT( i == numC );
    for (i=0; i<3; i++) cm[i] /= tm;

    /* translate coordinate systems so center of mass is at origin */
    for (i=0; i<numC; i++) {
        for (j=0; j<3; j++) {
            simH[i].bc[j] -= cm[j];
        }
    }

    /* okay partition it */
    if (pkey == 0) {
        rc = Aprx_partInert(thee, pcolor, numC, evec, simH);
    } else if (pkey == 1) {
        rc = Aprx_partSpect(thee, pcolor, numC, evec, simH, ford, rord, 0);
    } else if (pkey == 2) {
        rc = Aprx_partSpect(thee, pcolor, numC, evec, simH, ford, rord, 1);
    } else if (pkey == 3) {
        rc = Aprx_partInert(thee, pcolor, numC, evec, simH);
        rc = Aprx_partSpect(thee, pcolor, numC, evec, simH, ford, rord, 0);
    } else {
        Vnm_print(2,"Aprx_partOne: illegal pkey value of <%d>\n", pkey);
        rc = -1;
    }

    /* sort the values small-to-big; allows us to have equi-size submeshes */
    Vnm_dqsortOrd(evec, pord, numC);

    /* color the mesh using the ordering given by the eigenvector */
    sCount1 = 0;
    sCount2 = 0;
    eCount1 = 0.;
    eCount2 = 0.;
    if (rc >= 0) {

        /* weighted partitioning; divides into two sets of equal error */
        if (pwht == 1) {
            ecutOff = ( ePart / 2. );
            for (i=0; i<numC; i++) {
                sm = Gem_SS(thee->gm,ford[pord[i]]);
                if (eCount1 < ecutOff) {
                    SS_setChart( sm, pcolor );
                    sCount1++;
                    eCount1 += Bvec_valB( thee->wev, 0, ford[pord[i]] );
                } else {
                    SS_setChart( sm, pcolor+poff );
                    sCount2++;
                    eCount2 += Bvec_valB( thee->wev, 0, ford[pord[i]] );
                }
            }

        /* unweighted partitioning; divides into two sets of equal number */
        } else {
            cutOff = numC / 2;
            for (i=0; i<numC; i++) {
                sm = Gem_SS(thee->gm,ford[pord[i]]);
                if (sCount1 < cutOff) {
                    SS_setChart( sm, pcolor );
                    sCount1++;
                    eCount1 += Bvec_valB( thee->wev, 0, ford[pord[i]] );
                } else {
                    SS_setChart( sm, pcolor+poff );
                    sCount2++;
                    eCount2 += Bvec_valB( thee->wev, 0, ford[pord[i]] );
                }
            }
        }
    }

    /* free the temporary storage */
    Vmem_free( thee->vmem, numC, sizeof(int), (void**)&pord );
    Vmem_free( thee->vmem, numC, sizeof(int), (void**)&ford );
    Vmem_free( thee->vmem, numS, sizeof(int), (void**)&rord );
    Vmem_free( thee->vmem, numC, sizeof(double), (void**)&evec );
    Vmem_free( thee->vmem, numC, sizeof(simHelper), (void**)&simH );

    Vnm_print(0,"Aprx_partOne: done.");
    Vnm_print(0,"  [c1=%d,c2=%d,e1=%8.2e,e2=%8.2e,eT=%8.2e]\n",
        sCount1, sCount2, eCount1, eCount2, (eCount1+eCount2));

    if (sCount1 == 0) {
      Vnm_print(2,"Aprx_partOne: ERROR: first partition has NO SIMPLICES!\n");
    }
    if (sCount2 == 0) {
      Vnm_print(2,"Aprx_partOne: ERROR: second partition has NO SIMPLICES!\n");
    }

    return rc;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_part
 *
 * Purpose:  Do recursive bisection.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_part(Aprx *thee, int pkey, int pwht, int ppow)
{
    int i, j, k;

    Aprx_partSet(thee, 0);
    k = 1;
    for (i=0; i<ppow; i++) {
        for (j=0; j<k; j++) {
            Aprx_partOne(thee, pkey, pwht, j, k);
            Vnm_sigIntClear();
            while (Aprx_partSmooth(thee)) {}
        }
        k *= 2;
    }
    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_internalBoundaries
 *
 * Purpose:  Make internal boundary datastructures
 *
 * Author:   Michael Holst and Daniel Reynolds
 * ***************************************************************************
 */
VPUBLIC int Aprx_internalBoundaries(Aprx *thee)
{
    /* DAN-MIKE: */
    int i, j, k, faceIDs, currID;
    SS *sm, *sm0;

    faceIDs = 0;
    for (i=0; i<Gem_numSS(thee->gm); i++) {
        sm = Gem_SS(thee->gm,i);
        for (j=0; j<Gem_dimVV(thee->gm); j++) {
            sm0 = SS_nabor(sm,j);
            if (SS_chart(sm0) != SS_chart(sm)) {
                 for (k=0; k<Gem_dimVV(thee->gm); k++) {
                     if (( sm0->d.fPtr[k] != VNULL ) &&
                         ( SS_nabor(sm0,k) == sm )) {
                             currID = ((FF*)(sm0->d.fPtr[k]))->g.uid;
                     } else {
                         currID = faceIDs;
                         faceIDs++;
                     }
                 }
                 /*
                  * allocate: sm->fptr->FF for face j of sm
                  *    FF_ctor needs: grandParentFace,sPtr,color
                  */
                  sm->d.fPtr[j] = FF_ctor( currID, sm, SS_chart(sm0) );
            }
        }
    }

    return 0;
}

