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
 * rcsid="$Id: mtool.c,v 1.11 2010/08/12 05:18:29 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     mtool.c
 *
 * Purpose:  Class MTOOL: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "mtool_p.h"

VEMBED(rcsid="$Id: mtool.c,v 1.11 2010/08/12 05:18:29 fetk Exp $")

/*
 * ***************************************************************************
 * Class MTOOL: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_BAM)

#endif /* if !defined(VINLINE_BAM) */
/*
 * ***************************************************************************
 * Class MTOOL: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  mPlaceit
 *
 * Purpose:  Set or add a value to a matrix row/column.
 *
 * Notes:    key==0 ==> Set the value
 *           key==1 ==> Add the value
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void mPlaceit(int *IA, int *JA, double *A,
    int key, int i, int j, double val)
{
    int jj;
    for (jj=IA[i]; jj<IA[i+1]; jj++) {
        if (JA[jj] == j) {
            if (key==0) A[jj]  = val;
            else        A[jj] += val;
            return;
        }
    }
    /* should never get to this point -- should have already found column! */
    VASSERT( 0 );
}

/*
 * ***************************************************************************
 * Routine:  mContrib
 *
 * Purpose:  Set or add a value to a linked matrix entry list.
 *
 * Notes:    key==0 ==> Set the value
 *           key==1 ==> Add the value
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void mContrib(Vset *mtpool,
    int key, int *count, int i, int j, double val)
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
            mnew = (LinkA*)Vset_create(mtpool);
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
            mnew = (LinkA*)Vset_create(mtpool);
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
 * Routine:  lContrib
 *
 * Purpose:  Add a link to a linked graph entry list.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void lContrib(Vset *mtpool, int *count, int i, int j)
{
    int done;
    Link *curr, *mnew;

    mnew=VNULL;
    curr=(Link*)Vset_access(mtpool,i);
    VASSERT( curr != VNULL );

    /* we have to look through the row(col) */
    done=0;
    while (!done) {

        /* if first guy in row(col) is "blank", fill him with the info */
        if (curr->idx == -1) {
            (*count)++;
            curr->idx  = j;
            curr->next = VNULL;
            done = 1;

        /* we found the position; do nothing */
        } else if (curr->idx == j) {
            done = 1;

        /* it is not in the list; insert new struct AFTER it */
        } else if (curr->idx > j) {
            (*count)++;
            mnew = (Link*)Vset_create(mtpool);
            mnew->idx  = curr->idx;
            mnew->next = curr->next;
            curr->idx  = j;
            curr->next = mnew;
            done = 1;

        /* not found; no one left */
        } else if (curr->next == VNULL) {
            (*count)++;
            mnew = (Link*)Vset_create(mtpool);
            mnew->idx  = j;
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
 * Routine:  mBuildGraphT
 *
 * Purpose:  Builds an index (and value) array in transposed format given
 *           the index and value array of a ROW or COL matrix.
 *
 *   Notes:  The construction of the value array is optional.
 *
 *           (flag == 0)  Build index array only, don't use matrix values.
 *           (flag == 1)  Build index array only, guard against zero values.
 *           (flag == 2)  Build index and val array, don't guard for zeros.
 *           (flag == 3)  Build index and val arrays, guard for zero values.
 *
 *           If the original A is ROW (COL) it must be of size nxm (mxn).
 *           Hence, IJA, A, and work are n+1+numO, numO, and m respectively.
 *
 *  Author:  Stephen Bond
 * ***************************************************************************
 */
VEXTERNC void mBuildGraphT(Vmem *vmem, int **IJAT, double **AT, int *ATnumO,
    int *IJA, double *A, int n, int m, int flag, int *work)
{
    int i, ii, j, jj, kk, count;
    int *IA, *JA, *IAT, *JAT;

    IA = IJA;
    JA = IJA + n + 1;

    /* initialize the work array with zeros */
    for (j=0;j<m;j++) work[j] = 0;

    /* count the number of nonzeros in each row (col) */
    count = 0;
    if ( (flag == 1) || (flag == 3) ) {
        for (i=0;i<n;i++) {
            for (jj=IA[i];jj<IA[i+1];jj++) {
                j = JA[jj];
                if (j>=0) {
                    if (A[jj] != 0) {
                        count++;
                        work[j]++;
                    }
                }
            }
        }
    } else { /* (flag == 0) || (flag == 2) */
        for (i=0;i<n;i++) {
            for (jj=IA[i];jj<IA[i+1];jj++) {
                j = JA[jj];
                if (j>=0) {
                    count++;
                    work[j]++;
                }
            }
        }
    }

    /* allocate space for the index array */
    (*IJAT) = Vmem_malloc( vmem, m+1+count, sizeof(int) );
    IAT = (*IJAT);
    JAT = (*IJAT) + m + 1;

    /* fill in the values of the transposed IA array */
    IAT[0] = 0;
    for (j=0;j<m;j++) {
        IAT[j+1] = IAT[j] + work[j];
        if( work[j] != 0 ) {
            ii = IAT[j];
            JAT[ii] = -1; /* this isn't necessary */
            work[j] = 0;
        }
    }

    /* allocate space for the trasposed A array (if the flag is set) */
    if ( (flag == 2) || (flag == 3) ) {
        (*AT) = Vmem_malloc( vmem, count, sizeof(double) );
    }

    /* fill in the values of the transposed JA (and A) array */
    if ( (flag == 0) || (flag == 2)) {
        for (i=0;i<n;i++) {
            for (jj=IA[i];jj<IA[i+1];jj++) {
                j = JA[jj];
                if (j>=0) {
                    kk = IAT[j] + work[j];
                    JAT[kk] = i;  /* not in order? not a problem? */
                    if (flag == 2) (*AT)[kk] = A[jj];
                    work[j]++;
                }
            }
        }
    } else { /* (flag == 1) || (flag == 3) */
        for (i=0;i<n;i++) {
            for (jj=IA[i];jj<IA[i+1];jj++) {
                if (A[jj] != 0 ) {
                    j = JA[jj];
                    if (j>=0) {
                        kk = IAT[j] + work[j];
                        JAT[kk] = i;  /* not in order? not a problem? */
                        if (flag == 3) (*AT)[kk] = A[jj];
                        work[j]++;
                    }
                }
            }
        }
    }

    (*ATnumO) = count;
}

/*
 * ***************************************************************************
 * Routine:  buildG
 *
 * Purpose:  Produce the sparse triple matrix product:   B = R*A*P,
 *           where A is a sparse NxN square matrix, R is a sparse
 *           MxN retangular matrix, and P is a sparse NxM rectangular 
 *           matrix, with M < N (possibly M << N).
 *
 *           The result is a smaller (but possibly much more dense)
 *           square MxM matrix B.
 *
 * Notes:    The input matrices R,A,P are assumed to have the following 
 *           storage formats:  R is stored column-wise (ROW-format), P is
 *           stored row-wise (ROW-format), and A is stored in one of three
 *           forms, namely, either row-wise (ROW), col-wise (COL), or by
 *           diagonal followed by upper-triangle row-wise and then by lower
 *           triangle columne-wise (DRC).  The resulting B is stored in the
 *           same format as the input matrix A.  I.e., the matrices have the
 *           following possible storage format combinations:
 *
 *           The matrices A and B in DRC format:
 *
 *                B  =       R       *    A    *  P
 *
 *               \--   | | | | | | |   \------   ---
 *               |\- = | | | | | | | * |\----- * ---
 *               ||\   | | | | | | |   ||\----   ---
 *                                     |||\---   ---
 *                                     ||||\--   ---
 *                                     |||||\-   ---
 *                                     ||||||\   ---
 *
 *           Or, the matrices A and B in ROW format:
 *
 *                B  =       R       *    A    *  P
 *
 *               ---   | | | | | | |   -------   ---
 *               --- = | | | | | | | * ------- * ---
 *               ---   | | | | | | |   -------   ---
 *                                     -------   ---
 *                                     -------   ---
 *                                     -------   ---
 *                                     -------   ---
 *
 *           Or, finally, the matrices A and B in COL format:
 *
 *                B  =       R       *    A    *  P
 *
 *               |||   | | | | | | |   |||||||   ---
 *               ||| = | | | | | | | * ||||||| * ---
 *               |||   | | | | | | |   |||||||   ---
 *                                     |||||||   ---
 *                                     |||||||   ---
 *                                     |||||||   ---
 *                                     |||||||   ---
 *
 *           We compute the product B = R*A*P by splitting up A into its
 *           three structures A=D+L+U, and then by splitting up the sum:
 *
 *               B = R*D*P + R*L*P + R*U*P
 *
 *           In the case of A in ROW form, only the last term is
 *           present.  In the case of COL form, only the middle
 *           term is present.  In the DRC case, all terms are present.
 *           Note that in the ROW and COL forms, U and L are not
 *           actually upper and lower triangular, but general rectangular
 *           matrices; this is all that we need here.  In the DRC form,
 *           they are strict triangles, but we never use this fact directly.
 *
 *           The first and last terms are easy to compute using the 
 *           datastructures used for R,D,U,P.  However, the middle term
 *           R*L*P is not straightforward to compute directly, since the
 *           lower-triangle L of A is stored column-wise rather than
 *           row-wise.  However, this product can be easily formed by 
 *           computing its transpose instead:
 *
 *               B = R*D*P + (P^T*L^T*R^T)^T + R*U*P
 *
 *           The product P^T*L^T*R^T is easy to compute using the column-wise
 *           structure of L, hence row-wise structure of L^T; the result is 
 *           then transposed and added into B.
 *
 *           The product is formed component-wise; no temporary matrices
 *           are stored, except for a linked-list structure to build the
 *           non-zero structure of B, which is not possible to predict
 *           without actually doing the product (at least symbolically).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void buildG(Vmem *vmem, MATformat frmt, MATsym sym,
    int m, int n, int *numO, int *numA,
    int **ijb, double **b,
    int **ib, int **jb, double **diagb, double **offUb, double **offLb,
    int *ir, int *jr, double *r,
    int *ia, int *ja, double *a,
    double *diag, double *offU, double *offL,
    int *ip, int *jp, double *p)
{
    int i,j,k,l,ii,jj,ll,offUcnt,offLcnt,countU,countL;
    int size_ijb, size_b;
    double Bij, Bji, *lnkD;
    Vset *lnkL, *lnkU;
    LinkA *mt;
    const double TOL = 1.0e-9;

    VASSERT( m < n );

    /* clear the dynamic arrays */
    lnkL = Vset_ctor( vmem, "lnkL", sizeof( LinkA ), VMAX_OBJECTS, 0 );
    lnkU = Vset_ctor( vmem, "lnkU", sizeof( LinkA ), VMAX_OBJECTS, 0 );
    Vset_reset( lnkL );
    Vset_reset( lnkU );

    /* create and clear the arrays */
    lnkD = Vmem_malloc( vmem, m, sizeof(double) );

    /* initialize diag and a zero LinkA for each row of resulting matrix */
    for (i=0; i<m; i++) {
        lnkD[i] = 0.;
        mt=(LinkA*)Vset_create(lnkU);
        mt->idx  = -1;
        mt->val  = 0.;
        mt->next = VNULL;
        mt=(LinkA*)Vset_create(lnkL);
        mt->idx  = -1;
        mt->val  = 0.;
        mt->next = VNULL;
    }

    /* compute the sparse triple matrix product B=R*A*P */
    offUcnt = 0;
    offLcnt = 0;
    for (k=0; k<n; k++) {

        /* contribution to B from diagonal of A */
        /* KEY PLAY: compute B += R * D * P */
        if (frmt == DRC_FORMAT) {
            for (ii=ir[k]; ii<ir[k+1]; ii++) {
                i=jr[ii];
                for (jj=ip[k]; jj<ip[k+1]; jj++) {
                    j=jp[jj];
                    VASSERT( (i<m) && (j<m) );
                    Bij = ( r[ii] * diag[k] * p[jj] );
                    if (VABS(Bij) > TOL) {
                        if (i==j) {
                            lnkD[i] += Bij;
                        } else if (i<j) {
                            mContrib(lnkU,1,&offUcnt,i,j,Bij);
                        } else if (sym == ISNOT_SYM) {
                            mContrib(lnkL,1,&offLcnt,j,i,Bij);
                        }
                    }
                }
            }
        }

        /* contribution to B from off-diagonal parts of A */
        for (ll=ia[k]; ll<ia[k+1]; ll++) {
            l=ja[ll];

            /* contribution to B from strict upper-triangle of A */
            /* KEY PLAY: compute B += R * U * P */
            if ((frmt == DRC_FORMAT) || (frmt == ROW_FORMAT)) {
                for (ii=ir[k]; ii<ir[k+1]; ii++) {
                    i=jr[ii];
                    for (jj=ip[l]; jj<ip[l+1]; jj++) {
                        j=jp[jj];
                        VASSERT( (i<m) && (j<m) );
                        if (frmt == DRC_FORMAT) {
                            Bij = ( r[ii] * offU[ll] * p[jj] );
                            if (VABS(Bij) > TOL) {
                                if (i==j) {
                                    lnkD[i] += Bij;
                                } else if (i<j) {
                                    mContrib(lnkU,1,&offUcnt,i,j,Bij);
                                } else if (sym == ISNOT_SYM) {
                                    mContrib(lnkL,1,&offLcnt,j,i,Bij);
                                }
                            }
                        } else if (frmt == ROW_FORMAT) {
                            VASSERT( sym == ISNOT_SYM );
                            Bij = ( r[ii] * a[ll] * p[jj] );
                            if (VABS(Bij) > TOL)
                                mContrib(lnkU,1,&offUcnt,i,j,Bij);
                        } else { VASSERT(0); }
                    }
                }
            }

            /* contribution to B from strict lower-triangle of A */
            /* KEY PLAY: compute B += (P^T * L^T * R^T)^T */
            if ((frmt == DRC_FORMAT) || (frmt == COL_FORMAT)) {
                for (jj=ir[l]; jj<ir[l+1]; jj++) {
                    j=jr[jj];
                    for (ii=ip[k]; ii<ip[k+1]; ii++) {
                        i=jp[ii];
                        VASSERT( (i<m) && (j<m) );
                        if (frmt == DRC_FORMAT) {
                            Bji = ( p[ii] * offL[ll] * r[jj] );
                            if (VABS(Bji) > TOL) {
                                if (i==j) {
                                    lnkD[i] += Bji;
                                } else if (i>j) {
                                    mContrib(lnkU,1,&offUcnt,j,i,Bji);
                                } else if (sym == ISNOT_SYM) {
                                    mContrib(lnkL,1,&offLcnt,i,j,Bji);
                                }
                            }
                        } else if (frmt == COL_FORMAT) {
                            VASSERT( sym == ISNOT_SYM );
                            Bji = ( p[ii] * a[ll] * r[jj] );
                            if (VABS(Bji) > TOL)
                                mContrib(lnkL,1,&offLcnt,i,j,Bji);
                        } else { VASSERT(0); }
                    }
                }
            }
        }
    }

    /* determine storage sizes for ijb and b */
    size_ijb = 0;
    size_b   = 0;
    if (frmt == DRC_FORMAT) {
        size_ijb = m+1+offUcnt;
        if (sym == IS_SYM) size_b = m+offUcnt;
        else     size_b = m+offUcnt+offLcnt;
    } else if (frmt == ROW_FORMAT) {
        VASSERT( sym == ISNOT_SYM );
        size_ijb = m+1+offUcnt;
        size_b   = offUcnt;
    } else if (frmt == COL_FORMAT) {
        VASSERT( sym == ISNOT_SYM );
        size_ijb = m+1+offLcnt;
        size_b   = offLcnt;
    } else { VASSERT(0); }

    /* create actually storage for ijb */
    *numO = size_ijb - (m+1);
    *numA = size_b;
    (*ijb) = Vmem_malloc( vmem, size_ijb, sizeof(int) );

    /* create actually storage for b -- watch out for possible zero matrix! */
    if (size_b > 0) (*b) = Vmem_malloc( vmem, size_b, sizeof(double) );
    else (*b) = VNULL;

    /* now setup some convenience pointers into ijb and b */
    (*ib) = (*ijb);
    (*jb) = (*ijb)+m+1;
    if (frmt == DRC_FORMAT) {
        (*diagb) = (*b);
        (*offUb) = (*b)+m;
        if (sym == IS_SYM) (*offLb) = (*offUb);
        else     (*offLb) = (*b)+m+offUcnt;
    } else if (frmt == ROW_FORMAT) {
        (*offUb) = (*b);
    } else if (frmt == COL_FORMAT) {
        (*offLb) = (*b);
    } else { VASSERT(0); }

    /* now create the matrix B from the temporary LinkA structures */
    countL = 0;
    countU = 0;
    (*ib)[0] = 0;
    for (i=0; i<m; i++) {

        /* diagonal entry */
        if (frmt == DRC_FORMAT) (*diagb)[i] = lnkD[i];

        /* consecutive left-to-right entries in i-th row of upper-triangle */
        if ((frmt == DRC_FORMAT) || (frmt == ROW_FORMAT)) {
            for (mt=(LinkA*)Vset_access(lnkU,i); mt!=VNULL; mt=mt->next) {
                if (mt->idx >= 0) {
                    (*jb)[countU]    = mt->idx;
                    (*offUb)[countU] = mt->val;
                    countU++;
                }
            }
        }

        /* consecutive top-to-bottom entries in i-th col of lower-triangle */
        if ((frmt == DRC_FORMAT) || (frmt == COL_FORMAT)) {
            for (mt=(LinkA*)Vset_access(lnkL,i); mt!=VNULL; mt=mt->next) {
                if (mt->idx >= 0) {
                    if ((frmt == DRC_FORMAT) && (sym == ISNOT_SYM)) {
                        VASSERT( (*jb)[countL] == mt->idx );
                        (*offLb)[countL] = mt->val;
                        countL++;
                    } else {
                        (*jb)[countL] = mt->idx;
                        (*offLb)[countL] = mt->val;
                        countL++;
                    }
                }
            }
        }

        if ((frmt == DRC_FORMAT) || (frmt == ROW_FORMAT)) {
            (*ib)[i+1] = countU;
        } else {
            (*ib)[i+1] = countL;
        }
    }

    /* clear the dynamics arrays */
    Vset_reset( lnkL );
    Vset_reset( lnkU );
    Vset_dtor( &lnkL );
    Vset_dtor( &lnkU );
    Vmem_free( vmem, m, sizeof(double), (void**)&lnkD );
}

