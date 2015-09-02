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
 * rcsid="$Id: cholesky.c,v 1.4 2010/08/12 05:19:21 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     cholesky.c
 *
 * Purpose:  Class Whb: Cholesky Experiment
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */

#include "cholesky_p.h"

VEMBED(rcsid="$Id: cholesky.c,v 1.4 2010/08/12 05:19:21 fetk Exp $")

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
 * Routine:  Bmat_lnDet
 *
 * Purpose:  Calculate the log of the determinant of a SPD Bmat matrix.
 *
 * Notes:    Uses Cholesky factorization (slow for large matrices).
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC double Bmat_lnDet(Bmat *thee)
{
    double lndet;
    Bmat_choleskyFactor(thee, 1);

    VASSERT( Mat_state(thee->AG) == FACTORED_STATE );

    lndet = 2*Mat_lnDetDiag(thee->AG);

    Mat_dtor( &(thee->AG) );

    return lndet;
}

/*
 * ***************************************************************************
 * Routine:  mContribRecycle
 *
 * Purpose:  Set or add a value to a linked matrix entry list.
 *
 * Notes:    key==0 ==> Set the value
 *           key==1 ==> Add the value
 *
 *           rclnk==VNULL  ==> Allocate a new link if necessary
 *           rclnk!=VNULL  ==> If necessary use rclnk, returning rclnk->next
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPRIVATE void mContribRecycle(Vset *mtpool,
    LinkA **rclnk, int key, int *count, int i, int j, double val)
{
    int done;
    LinkA *curr, *mnew;

    mnew=VNULL;
    curr=(LinkA*)Vset_access(mtpool,i);
    VASSERT( curr != VNULL );

    /* we have to look through the row(col) */
    done=0;
    while (!done) {

        /* if first guy in row(col) is "blank", fill him with the info */
        if (curr->idx == -1) {
            (*count)++;
            curr->idx  = j;
            curr->val  = val;
            curr->next = VNULL;
            done = 1;

        /* we found the position; just add in the contribution */
        } else if (curr->idx == j) {
            if (key == 0)
                curr->val = val;
            else
                curr->val += val;
            done = 1;

        /* it is not in the list; insert new struct AFTER it */
        /* KEY PLAY: this always inserts into the head of list */
        } else if (curr->idx > j) {
            (*count)++;
            if ( (*rclnk) == VNULL) {
                mnew = (LinkA*)Vset_create(mtpool);
            } else {
                mnew = (*rclnk);
                (*rclnk) = mnew->next;
            }
            mnew->idx  = curr->idx;
            mnew->val  = curr->val;
            mnew->next = curr->next;
            curr->idx  = j;
            curr->val  = val;
            curr->next = mnew;
            done = 1;

        /* not found; no one left */
        } else if (curr->next == VNULL) {
            (*count)++;
            if ( (*rclnk) == VNULL) {
                mnew = (LinkA*)Vset_create(mtpool);
            } else {
                mnew = (*rclnk);
                (*rclnk) = mnew->next;
            }
            mnew->idx  = j;
            mnew->val  = val;
            mnew->next = VNULL;
            curr->next = mnew;
            done = 1;

        /* not found yet; still hope */
        } else {
            curr=curr->next;
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_choleskyCreate
 *
 * Purpose:  Create the global matrix from the blocks in CLN storage format.
 *           This is required for preparing a single global matrix for input
 *           to the Cholesky Factor routine.
 *
 *    Note:  It is assumed implicitly that the Bmat is symmetric, and hence
 *           we only copy and store the lower triangular part!
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Bmat_choleskyCreate(Bmat *thee)
{
    int i, j, k, p, q, count, istart, jstart;
    Vset  *lnk;
    LinkA *mt;
    Mat *blk, *gmat;
    MATmirror mirror;
    MATformat format;
    /* Bound on the size of L */
    int maxnZ = Bmat_numRT(thee)*1000;
    double *diag, *offU, *offL;

    /* initialize the global matrix datastructure */
    gmat = Mat_ctor(thee->vmem, "AG", Bmat_numRT(thee), Bmat_numCT(thee));
    Mat_initStructure(gmat, CLN_FORMAT, IS_SYM, 0, VNULL);

    /* initialize/clear the dynamic array */
    gmat->lnkL = Vset_ctor( thee->vmem, "lnk", sizeof( LinkA ), maxnZ, 0 );
    Vset_reset( gmat->lnkL );
    lnk = gmat->lnkL;

    /* create an empty entry to start each row of global matrix */
    for (i=0; i<Bmat_numRT(thee); i++) {
        mt=(LinkA*)Vset_create(lnk);
        mt->idx  = -1;
        mt->val  = 0.;
        mt->next = VNULL;
    }

    /* now get the COL structure of the matrix */
    count = 0;

    istart = 0;
    for (p=0; p<thee->numB; p++) {
        jstart = 0;
        for (q=0; q<=p; q++) {
            mirror = thee->mirror[p][q];
            blk    = thee->AD[p][q];
            format = Mat_format(blk);
            diag   = blk->diag;
            offU   = blk->offU;
            offL   = blk->offL;
            if (mirror) {
                if (format == ROW_FORMAT) {
                    format = COL_FORMAT;
                } else if (format == COL_FORMAT) {
                    format = ROW_FORMAT;
                } else {
                    VASSERT(0);
                }
            }

            for (j=0; j<Mat_numR(blk); j++) {
                if (format == DRC_FORMAT) {
                    i = j;
                    mContrib(lnk,0,&count,jstart+j,istart+i,diag[i]);
                    for (k=blk->IA[j]; k<blk->IA[j+1]; k++) {
                        i = blk->JA[k];
                        mContrib(lnk,0,&count,jstart+j,istart+i,offL[k]);
                    }
                } else if (format == ROW_FORMAT) {
                    for (k=blk->IA[j]; k<blk->IA[j+1]; k++) {
                        i = blk->JA[k];
                        mContrib(lnk,0,&count,jstart+i,istart+j,blk->A[k]);
                    }
                } else if (format == COL_FORMAT) {
                    for (k=blk->IA[j]; k<blk->IA[j+1]; k++) {
                        i = blk->JA[k];
                        mContrib(lnk,0,&count,jstart+j,istart+i,blk->A[k]);
                    }
                } else { VASSERT(0); }

            }
            /* increment index for the column block */
            jstart += Bmat_numC(thee,q,q);
        }
        /* increment index for the row block */
        istart += Bmat_numR(thee,p,p);
    }
    gmat->numO = count;

    thee->AG = gmat;
}

/*
 * ***************************************************************************
 * Routine:  Mat_choleskyFactor
 *
 * Purpose:  Create the sparse L L^T factors for the system matrix.
 *
 *    Note:  The matrix is overwriten with the result!
 *
 *  Method:  In OCTAVE pseudocode
 *
 *           for k = 1:n
 *             A(k,k) = sqrt(A(k,k));
 *             for i = (k+1):n;
 *               A(i,k) = A(i,k)/A(k,k);
 *             end
 *             for j = (k+1):n
 *               for i = j:n
 *                 A(i,j) = A(i,j) - A(i,k)*A(j,k);
 *               end
 *             end
 *           end
 *
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPRIVATE int Mat_choleskyFactor(Mat *thee, int flag)
{
    int count, k, n;
    int recyc_idx;
    double Akk;
    LinkA *mt, *mti, *mtj, *mt_recyc, *mt_tmp;

    Vset *lnk = thee->lnkL;

    VASSERT( Mat_format(thee) == CLN_FORMAT );
    VASSERT( Mat_sym(thee) == IS_SYM );
    VASSERT( Mat_numR(thee) == Mat_numC(thee) );

    /*  matrix has already been sparse factored */
    if ( Mat_state(thee) == FACTORED_STATE) {
        return 1;
    }

    /*  groovy, it hasn't been factored yet!  */
    n = Mat_numR(thee);
    count = Mat_numO(thee);

    switch( flag ) {
    case 0:  /* CASE 0:  Keep full factoring and No pivoting */
        for (k=0; k<n; k++) {
            mt = (LinkA*)Vset_access(lnk,k); /* A(k,k) */
            if ( mt->val > 0 && mt->idx >= 0 ) {
                mt->val = sqrt(mt->val);
                Akk = mt->val;
                for ( mti=mt->next; mti!=VNULL; mti=mti->next ) {
                    mti->val /= Akk; /* A(i,k)/A(k,k) */
                }

                for ( mtj=mt->next; mtj!=VNULL; mtj=mtj->next ) {
                    for ( mti=mtj; mti!=VNULL; mti=mti->next ) {
                        mContrib( lnk, 1, &count, mtj->idx, mti->idx,
                                  -1*mti->val*mtj->val );
                        /* A(i,j) -= A(i,k)*A(j,k) */
                    }
                }
            } else {
                return 0;
            }
        }
        break;
    case 1:  /* CASE 1:  Only get the diagonal correct */
        recyc_idx = 0;
        mt_recyc = VNULL;
        for (k=0; k<n; k++) {
            mt = (LinkA*)Vset_access(lnk,k); /* A(k,k) */
            if ( mt->val > 0 && mt->idx >= 0 ) {
                mt->val = sqrt(mt->val);
                Akk = mt->val;
                for ( mti=mt->next; mti!=VNULL; mti=mti->next ) {
                    mti->val /= Akk; /* A(i,k)/A(k,k) */
                }

                for ( mtj=mt->next; mtj!=VNULL; mtj=mtj->next ) {
                    for ( mti=mtj; mti!=VNULL; mti=mti->next ) {
                        while( (mt_recyc == VNULL) && (recyc_idx < k) ) {
                            mt_tmp = (LinkA*)Vset_access(lnk,recyc_idx);
                            mt_recyc = mt_tmp->next;
                            mt_tmp = VNULL;
                            recyc_idx++;
                        }
                        mContribRecycle( lnk, &(mt_recyc), 1, &count,
                            mtj->idx, mti->idx, -1*mti->val*mtj->val );
                        /* A(i,j) -= A(i,k)*A(j,k) */
                    }
                }
            } else {
                return 0;
            }
        }
        break;
    default:
        VASSERT( 0 );
    }

    thee->state = FACTORED_STATE;

    return 1;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_choleskyFactor
 *
 * Purpose:  Create the sparse L L^T factors for global matrix.
 *
 *    Note:  Will only work if A is symmetric positive definite!
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPRIVATE int Bmat_choleskyFactor(Bmat *thee, int flag)
{
    if ( thee->AG == VNULL ) {
        Bmat_choleskyCreate(thee);
    }

    if ( Mat_state(thee->AG) == FACTORED_STATE ) {
        return 1;
    } else {
        return Mat_choleskyFactor(thee->AG, flag);
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_lnDetDiag
 *
 * Purpose:  Calculate the log(det(A)), where A is diagonal or triangular.
 *
 * Notes:    Use another algorithm first to reduce to the triangular.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPRIVATE double Mat_lnDetDiag(Mat *thee)
{
    int k,n;
    LinkA *mt;
    Vset *lnk;
    double lndet;

    VASSERT( Mat_format(thee) == CLN_FORMAT );
    VASSERT( Mat_numR(thee) == Mat_numC(thee) );

    n = Mat_numR(thee);
    lnk = thee->lnkL;

    lndet = 0.0;
    for ( k=0; k<n; k++ ) {
        mt=(LinkA*)Vset_access(lnk,k);
        lndet += log(VABS(mt->val));
    }

    return lndet;
}
