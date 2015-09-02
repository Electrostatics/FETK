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
 * rcsid="$Id: whb.c,v 1.7 2010/08/12 05:19:25 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     whb.c
 *
 * Purpose:  Class Whb: methods.
 *
 * Author:   Burak Aksoylu, Stephen Bond, and Michael Holst
 * ***************************************************************************
 */
#include "whb_p.h"

VEMBED(rcsid="$Id: whb.c,v 1.7 2010/08/12 05:19:25 fetk Exp $")

/*
 * ***************************************************************************
 * Class Whb: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_WHB)

#endif /* if !defined(VINLINE_WHB) */
/*
 * ***************************************************************************
 * Class Whb: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  HBvec_hbVcyc
 *
 * Purpose:  Hierarchical Basis MG Vcycle (Bank, Dupont, and Yserentant).
 *
 * Warning:  This version is uses RESIDUAL/ERROR form!  The initial guess is
 *           always zero, and the righthand side is always the residual from
 *           the previous iteration.
 *
 *   Notes:  By using a residual/error form for the Vcycle, the code inside
 *           the Vcycle is much cleaner.  In addition, it's much simpler to
 *           decide when the residual tolerance has been met.  If a full
 *           approximation scheme is used, or if the residual is calculated
 *           "on the fly", the magnitude of the residual is not known until
 *           the very bottom of the Vcycle.  This makes Vcycle code a bit
 *           more complicated.
 *
 * HB crash course:
 *
 * A typical multigrid algorithm can be implemented in two different ways:
 * either as a full approximation scheme (FAS) or as a coarse grid correction
 * scheme (CGCS). CGCS seems to be more popular than FAS. Here, Alg_hbVcycle
 * is implemented as CGCS.  As far as we can tell, they both require the same
 * number of operations.
 *
 * Here is the MATLAB equivalent of HBvec_hbVcyc.
 *
 * function [u]=vhbmg(rhs,level) ;
 *
 * %%% global variables: prolongation and stiffness matrices
 * global P_12 P_23 P_34 P_45 P_56 P_67 P_78 P_89;
 * global A_1 A_2 A_3 A_4 A_5 A_6 A_7 A_8 A_9;
 *
 *   %%% get the stiffness matrix on this level
 *   A = eval(['A_' num2str(level) ]);
 *
 *  if (level == 1)
 *   u = A \ rhs;
 *  else
 *    %%%%%%% recover the dimensions
 *    P = eval(['P_' num2str(level-1) num2str(level)]);
 *    [N,M] = size(P);
 *    n = N-M;
 *    P2 = [zeros(M,n);eye(n,n)];
 *    myzeros = zeros(n,1);
 *
 *    %%% get the level-2 block of the stiffness matrix
 *    A_22 = A(N-n+1:N, N-n+1:N);
 *    %%% grab the fine part of rhs
 *    rhs_2 = P2'*rhs;
 *    %%% pre-smoothing by block symmetric Gauss-Seidel
 *    u_2 = smooth_block(A_22,myzeros,rhs_2);
 *    %%% transform basis
 *    w = P2*u_2;
 *    %%% restriction of the residual for the coarse grid
 *    res = P'*(rhs - A*w);
 *
 *        u = vhbmg(res,level-1);
 *
 *    %%% Prolongate the error
 *    %%% Be careful u is the error not the solution because of CGCR
 *    u = P*u;
 *    %%% update fine-grid pseudo residual. Pseudo residual because of
 *    %%% CGCS style. In fact, pseudoRes_2 = residual_2 + A_22*u_2.
 *    pseudoRes_2 = P2'*(rhs - A*u);
 *    %%% post-smoothing by block symmetric Gauss-Seidel
 *    %%% Rather than u_2 = smooth_block(A_22,myzeros,residual_2), we use
 *    u_2 = smooth_block(A_22,u_2,pseudoRes_2);
 *
 *    %%% embed the updated error to the solution by inclusion
 *    error = P2*u_2;
 *    u = u + error;
 *  end;
 *
 * Author:   Burak Aksoylu and Stephen Bond 2002/01/09
 * ***************************************************************************
 */
VPUBLIC void HBvec_hbVcyc(HBvec *dd, HBmat *Ahb, HBvec *rr,
    HBmat *Ghb, HBvec *ww, int key, int csolv)
{
    int meth_s = 2/*sGS*/, flag_s = 1, flag_c = 1, itmax_s = 1, itmax_c = 500;
    int adj_s, meth_c, prec_c;
    double omega_s = 0.5, etol_s = 0.0, etol_c = 1.0e-10;

#if 0
    Bvec_print( rr->bv );  /* this is a permanent check print */
#endif

    /* solve coarse problem using best available single-level method */
    if (Ahb->type == AMIN_TYPE) {
#if 1
        prec_c = 1; /* diagonal scaling */
        meth_c = 3; /* bcg */
#else
        prec_c = 0; /* no preconditioner */
        meth_c = 0; /* slu */
#endif
        Bvec_lmethod( dd->bv, Ahb->A22, rr->bv, ww->bv, dd->bv /*ut*/,
            key, flag_c, itmax_c, etol_c, prec_c, 0, VNULL, meth_c);
        return;
    }

    /* STEP 1: Convert the NODAL residual to an HB basis residual     */
    /*     DO: r = S'*r,  as r = r + G'*r                             */
    HBvec_matvec( rr, Ghb, 1, ww->bv2 );

    /* STEP 2: Smooth A22 d2 = r2                                     */
    /*     DO: HBSmooth( d2, A22, r2, 0 )      (0=standard,1=adjoint) */
    adj_s = ( (csolv == 0) || (csolv == 2) ) ? 0 : 1;
    Bvec_smooth( dd->bv2, Ahb->A22, rr->bv2, ww->bv2,
        key, flag_s, meth_s, adj_s, itmax_s, etol_s, omega_s);

    /* STEP 3: Correct the HB basis residual using smoother result    */
    /*     DO: r1 = r1 + A12*(-d2)                                    */
    Bvec_scal( dd->bv2, -1.0 );
    if (key == 0) {
        Bvec_matvec( rr->bv, Ahb->A12, dd->bv2, 2, 0 );
    } else {
        Bvec_matvec( rr->bv, Ahb->A21, dd->bv2, 3, 0 );
    }
    Bvec_scal( dd->bv2, -1.0 );

    /* STEP 4: Solve the coarse level problem using HB                */
    /*     DO: HBSolve( d1, A11, r1 )                                 */
    HBvec_hbVcyc( dd->next, Ahb->next, rr->next,
                  Ghb->next, ww->next, key, csolv );

    /* STEP 5: Correct the HB basis residual with coarse solve result */
    /*     DO: (-r2) = (-r2) + A21*d1                                 */
    Bvec_scal( rr->bv2, -1.0 );
    if (key == 0) {
        Bvec_matvec( rr->bv2, Ahb->A21, dd->bv, 2, 0 );
    } else {
        Bvec_matvec( rr->bv2, Ahb->A12, dd->bv, 3, 0 );
    }
    Bvec_scal( rr->bv2, -1.0 );

    /* STEP 6: Smooth A22 d2 = r2                                     */
    /*     DO: HBSmooth( d2, A22, r2, 1 )      (0=standard,1=adjoint) */
    adj_s = ( (csolv == 0) || (csolv == 1) ) ? 0 : 1;
    Bvec_smooth( dd->bv2, Ahb->A22, rr->bv2, ww->bv2,
        key, flag_s, meth_s, adj_s, itmax_s, etol_s, 0.5);

    /* STEP 7: Convert the HB basis correction to the NODAL basis     */
    /*     DO: d = S*d,  as d = d + G*d                               */
    HBvec_matvec( dd, Ghb, 0, ww->bv2 );

#if 0
    Bvec_print( dd->bv );  /* this is a permanent check print */
#endif
}

/*
 * ***************************************************************************
 * Routine:  HBvec_initStructure
 *
 * Purpose:  Creates a chain of HBvec pointers to a Bvec.
 *
 *   Notes:  This routine takes a null pointer to an HBvec array, and
 *           returns a linked (hierarchical) chain of fully assembled
 *           HBvec's.  Each of the links contains two Bvec pointers,
 *           which correspond to logical subsections of a global Bvec.
 *           The fully assemble HBvec array consist of only pointers,
 *           sharing the data space used by the specified Bvec.
 *
 *           Basic Inputs:
 *
 *           Bmat *P0, *P1, ...  the prologation matrices for each level
 *           Bvec *u             a block vector on the finest level
 *                               (passed using the HBvec bv pointer)
 *
 *           Basic Outputs (inside the HBvec chain):
 *
 *           Bvec *bv, *bv2     pointers to logical subsections of u.
 *
 * Author:   Burak Aksoylu and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void HBvec_initStructure(HBvec *thee, HBmat *Ahb)
{
    int ii, numB = Bmat_numB( Ahb->A22 );
    int pnumR1[MAXV], pnumR2[MAXV], pnumR[MAXV], pzero[MAXV];
    Bvec *u = thee->bv;  /* global Bvec is always passed in bv */

    if ( Ahb->type == AMIN_TYPE ) {
        for (ii=0; ii<numB; ii++) {
            pzero[ii] = 0;
            pnumR[ii] = Bmat_numR( Ahb->A22, ii, ii ); /* FIX ME (MESSY) */
        }
        thee->bv = Bvec_ctorPoint( u, "Bvec_ptr", pzero, pnumR );
        return;
    }

    /* determine the size of the subblocks */
    for (ii=0; ii<numB; ii++) {
        pzero[ii] = 0; /* FIX ME (MESSY) */
        pnumR1[ii] = Bmat_numR( Ahb->A12, ii, ii );
        pnumR2[ii] = Bmat_numR( Ahb->A22, ii, ii );
        pnumR[ii]  = pnumR1[ii] + pnumR2[ii];
    }

    /* set the block vector pointers to the block vector tails */
    thee->bv  = Bvec_ctorPoint( u, "Bvec_ptr",  pzero, pnumR );
    thee->bv2 = Bvec_ctorPoint( u, "Bvec_ptr2", pnumR1, pnumR2 );

    /* construct the HBvec pointer for the next level */
    thee->next = HBvec_ctor( thee->vmem, "HBvec", numB );

    /* shift the global Bvec down the chain */
    thee->next->bv = u;

    /* descend to the next coarser level */
    HBvec_initStructure( thee->next, Ahb->next );

    return;
}

/*
 * ***************************************************************************
 * Routine:  HBvec_killStructure
 *
 * Purpose:  Kills a chain of HBvec pointers.
 *
 * Author:   Burak Aksoylu and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void HBvec_killStructure(HBvec *thee)
{

    if ( thee->next == VNULL ) {
        Bvec_dtorPoint( &(thee->bv) );
        return;
    }

    /* descend to the next coarser level */
    HBvec_killStructure( thee->next);

    Bvec_dtorPoint( &(thee->bv) );
    Bvec_dtorPoint( &(thee->bv2) );
    HBvec_dtor( &(thee->next) );
    return;
}

/*
 * ***************************************************************************
 * Routine:  HBmat_initA
 *
 * Purpose:  Assembles the hierarchical matrix for the HB Vcycle.
 *
 *   Notes:  This routine takes a pointer to an HBmat array, and
 *           returns a linked (hierarchical) chain of fully assembled
 *           HBmat's.  Each of the links contains several block matrices,
 *           which correspond to the stabilized subsections of the global
 *           block (stiffness) matrix.  All together, these stabilized
 *           blocks form the entire stiffness matrix, with respect to the
 *           recursively defined "hierarchical basis".
 *
 *           Basic Inputs:
 *
 *           HBmat *G    change of basis matrices for each level
 *           BXLN *A   nodal stiffness matrix in doubly linked format
 *           int minLev  coarsest level in the hierarchy
 *
 *           Basic Outputs (inside the HBmat chain):
 *
 *           Bmat *A21, *A22, *A12   stabilized Mat blocks on each level
 *
 * Author:   Burak Aksoylu and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void HBmat_initA(HBmat *Ahb, HBmat *Ghb, Bmat *Alink)
{
    int ii, jj, numB = Alink->numB;
    int pnumR1[MAXV], pnumR2[MAXV], pnumC1[MAXV], pnumC2[MAXV];
    MATmirror pmir[MAXV][MAXV];
#if 0
    Bmat *Ppro = Ghb->A21;
#endif

    if ( Ghb->next == VNULL ) {
        for (ii=0; ii<numB; ii++) {
            pnumR2[ii] = Bmat_numR( Alink, ii, ii );
            pnumC2[ii] = Bmat_numC( Alink, ii, ii );
            for (jj=0; jj<numB; jj++) {
                pmir[ii][jj] = Bmat_mirror( Alink, ii, jj );
            }
        }
        Ahb->A22 = Bmat_ctor( Ahb->vmem, "A11", numB, pnumR2, pnumC2, pmir );
        Bmat_copyBXLN( Ahb->A22, Alink );
        Ahb->type = AMIN_TYPE;
        return;
    }

    /* determine block sizes */
    for (ii=0; ii<numB; ii++) {
        pnumC1[ii] = Bmat_numC(Ghb->A21, ii, ii);
        pnumC2[ii] = Bmat_numR(Ghb->A21, ii, ii);
        pnumR1[ii] = pnumC1[ii];
        pnumR2[ii] = pnumC2[ii];
        for (jj=0; jj<numB; jj++) {
            pmir[ii][jj] = Bmat_mirror( Alink, ii, jj );
        }
    }

    /* construct the matrix subblocks for this level */
    Ahb->A12 = Bmat_ctor( Ahb->vmem, "A12", numB, pnumR1, pnumC2, pmir );
    Ahb->A21 = Bmat_ctor( Ahb->vmem, "A21", numB, pnumR2, pnumC1, pmir );
    Ahb->A22 = Bmat_ctor( Ahb->vmem, "A22", numB, pnumR2, pnumC2, pmir );

    /* stabilize the matrix */
    BXLN_hbTriple( Alink, Ghb );

    BXLN_copyBlocks( Alink, Ahb->A12, Ahb->A21, Ahb->A22 );

    BXLN_shrinkLogical( Alink, Ahb->A12, Ahb->A21 );

    /* set the type for the HBmat on this level */
    Ahb->type = ANOR_TYPE;

    /* construct HBmat pointer for the next level */
    Ahb->next = HBmat_ctor( Ahb->vmem, "HBmat", 1);

    /* descend to the next coarser level */
    HBmat_initA( Ahb->next, Ghb->next, Alink);

    return;
}

/*
 * ***************************************************************************
 * Routine:  HBmat_initG
 *
 * Purpose:  Assembles the change of basis matrices for the HB Vcycle.
 *
 *   Notes:  This routine takes a pointer to an HBmat array, and
 *           returns a linked (hierarchical) chain of fully assembled
 *           HBmat's.  Each of the links contains several block matrices,
 *           which correspond to the logical subsections of the change
 *           of basis matrix:
 *
 *           [ S11 S12 ] = [  I  0  ] + [ G11 G12 ]
 *           [ S21 S22 ]   [  0  I  ]   [ G21 G22 ]
 *
 *           To keep optimal storage complexity, only G is stored, and
 *           any blocks which are entirely zero have VNULL pointers.
 *
 *           Basic Inputs:
 *
 *           BXLN *M   nodal mass matrix in doubly linked format
 *           Bmat *R     tails of the prolongation matrices (inside Algs)
 *           int minLev  coarsest level in the hierarchy
 *
 *           Basic Outputs (inside the HBmat chain):
 *
 *           Bmat *G21, *G22, *G12   logical blocks of G = S - I.
 *
 *           The mass matrix can be safely passed as VNULL in the HB
 *           case, since it is only touched in the WMHB case.
 *
 * Author:   Burak Aksoylu and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void HBmat_initG(HBmat *thee, Bmat *Ppro, Bmat *Mlink, int meth)
{
    int ii, jj, numB;
    int ibase[MAXV], pnumR1[MAXV], pnumR2[MAXV], pnumC1[MAXV], pnumC2[MAXV];
    int pnumR[MAXV], pnumC[MAXV];
    MATmirror pmir[MAXV][MAXV];
    Bmat *Atest;

    if ( Ppro == VNULL ) {
        return;
    }

    numB = Bmat_numB( Ppro );

    /* determine block sizes */
    for (ii=0; ii<numB; ii++) {
        ibase[ii] = ( Bmat_impl( Ppro, ii, ii ) == IS_IMPL ) ?
            0 : Bmat_numC( Ppro, ii, ii ) ;
        pnumC1[ii] = Bmat_numC(Ppro, ii, ii );
        pnumC2[ii] = Bmat_numR(Ppro, ii, ii ) - ibase[ii];
        pnumR1[ii] = pnumC1[ii];
        pnumR2[ii] = pnumC2[ii];
        for (jj=0; jj<numB; jj++) {
            pmir[ii][jj] = ISNOT_MIRROR;
        }
        pnumR[ii] = pnumR1[ii] + pnumR2[ii];
        pnumC[ii] = pnumC1[ii] + pnumC2[ii];
    }

    /* REALLY BIG HACK, STEVE FIX THIS NOW! */
    Atest = Bmat_ctor( thee->vmem, "Atest", numB, pnumR, pnumC, pmir );
    if ( Bmat_sluDirect( Atest ) ) {
        Bmat_dtor( &Atest );
        return;
    }
    Bmat_dtor( &Atest );

    /* construct the matrix subblocks for this level */
    thee->A12 = Bmat_ctor( thee->vmem, "G12", numB, pnumR1, pnumC2, pmir );
    thee->A22 = Bmat_ctor( thee->vmem, "G22", numB, pnumR2, pnumC2, pmir );
    thee->A21 = Bmat_ctorPoint( Ppro, "G21", ibase, pnumR2 );
    thee->type = GHB_TYPE; /* G matrix for HB */

    if (meth == 1) {
        BXLN_hbTriple( Mlink, thee ); /* Change M from NODAL to HB basis */
#if 0
        Bmat_printSp(Mlink, "Mhb.m",0);
#endif
        HBmat_GHB2WMHB( thee, Mlink ); /* Init G12/G22 using M_hb  */
        thee->type = GWM_TYPE; /* G matrix for WMHB */
    }

    /* construct HBmat pointer for the next level */
    thee->next = HBmat_ctor( thee->vmem, "HBmatG", numB );

    /* descend to the next coarser level */
    HBmat_initG( thee->next, Ppro->coarse, Mlink, meth);

    return;
}

/*
 * ***************************************************************************
 * Routine:  HBmat_killStructure
 *
 * Purpose:  Kills a chain of HBmat pointers.
 *
 * Author:   Burak Aksoylu and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void HBmat_killStructure(HBmat *thee)
{
    int p, q, numB;
    Mat *Ablock;

    if ( thee == VNULL ) return;

    if ( thee->next == VNULL ) {
        return;
    }

    /* descend to the next coarser level */
    HBmat_killStructure( thee->next );

    /* unset any Mat's which are just "pointers" */
    if ( thee->A12 != VNULL ) {
        numB = Bmat_numB( thee->A12 );
        for (p=0; p<numB; p++) {
            for (q=0; q<numB; q++) {
                Ablock = Bmat_AD( thee->A12, p, q);
                if (Ablock != VNULL) {
                    if ( Mat_numA( Ablock ) < 0 ) {
                        Ablock->IJA = VNULL;
                        Ablock->A  = VNULL;
                        Ablock->numA = 0;
                        Ablock->state = NULL_STATE;
                    }
                }
            }
        }
    }
    /* unset any Mat's which are just "pointers" */
    if ( thee->A21 != VNULL ) {
        numB = Bmat_numB( thee->A21 );
        for (p=0; p<numB; p++) {
            for (q=0; q<numB; q++) {
                Ablock = Bmat_AD( thee->A21, p, q);
                if (Ablock != VNULL) {
                    if ( Mat_numA( Ablock ) < 0 ) {
                        Ablock->IJA = VNULL;
                        Ablock->A  = VNULL;
                        Ablock->numA = 0;
                        Ablock->state = NULL_STATE;
                    }
                }
            }
        }
    }

    HBmat_dtor( &(thee->next) );
    return;
}

