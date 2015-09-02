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
 * rcsid="$Id: rcmat.c,v 1.4 2010/08/12 05:19:22 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     rcmat.c
 *
 * Purpose:  Class Whb: special linked list data structures.
 *
 * Author:   Burak Aksoylu, Stephen Bond, and Michael Holst
 * ***************************************************************************
 */

#include "rcmat_p.h"

VEMBED(rcsid="$Id: rcmat.c,v 1.4 2010/08/12 05:19:22 fetk Exp $")

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
 * Routine:  XLN_hbTriple
 *
 * Purpose:  Produce the HB sparse triple matrix product:
 *
 *           A_hb = (I + GL') A (I + GR)
 *
 *                  = [  I     GL21'    ] [ A11 A12 ] [  I      GR12   ]
 *                    [ GL12' (I+GL22') ] [ A21 A22 ] [ GR21  (I+GR22) ]
 *
 *           where GL/GR are the left/right change of basis matrices.
 *
 *   Notes:  The G21, G22, and G12 blocks must be ROW, DRC, and COL
 *           formats respectively.  Any NULL blocks are treated as
 *           zero matrices.  If the XLN is of symmetric type, only the
 *           upper triangular portion is used/modified.
 *
 *           The matrix A is overwritten with the A11 result.
 *
 *  Method:  CASE 1: Heirarchical Basis (HB)
 *
 *           [A11 A12] += [ A12 GL21 + GL21'(A21 + A22 GR21); GL21'A22 ]
 *           [A21 A22]    [                        A22 GR21 ;  0       ]
 *
 *           CASE 2: Wavelet Modified Heirarchical Basis (WMHB)
 *
 *   [A11 A12] += [ GL21'(A21+A22*GR21) + A12*GR21 ; 0 ]
 *   [A21 A22]    [ GL22'(A21+A22*GR21) + A22*GR21 ; 0 ]
 *
 *              + [ 0                   ; GL21'(A22+A22*GR22+A21*GR12) ]
 *                [ GL21'(A11+A12*GR21) ; GL22'(A22+A22*GR22+A21*GR12) ]
 *
 *              + [ 0 ; A11*GR12 + A12*GR22                                ]
 *                [ 0 ; A21*GR12 + A22*GR22 + GL12'(A12+A12*GR22+A11*GR12) ]
 *
 * Author:   Stephen Bond and Burak Aksoylu 2002/01/26
 * ***************************************************************************
 */
VPUBLIC void XLN_hbTriple(Mat *thee,
    Mat *GL21, Mat *GL12, Mat *GL22, Mat *GR21, Mat *GR12, Mat *GR22 )
{
    int flagWMHB = 0;
    MATsym psym = Mat_sym( thee );

    if ( (Mat_format(GL12)==ZERO_FORMAT)||(Mat_format(GR12)==ZERO_FORMAT)||
         (Mat_format(GL22)==ZERO_FORMAT)||(Mat_format(GR22)==ZERO_FORMAT) ) {
        flagWMHB = 0;
    } else {
        flagWMHB = 1;
    }

    switch (psym) {
    case ISNOT_SYM:
        if ( flagWMHB == 0 ) {
            XLN_hbTripleNSYM( thee, GL21, GR21 );
        } else {
            XLN_wmTripleNSYM( thee, GL21, GL12, GL22, GR21, GR12, GR22 );
        }
        break;
    case STRUC_SYM:
        if ( flagWMHB == 0 ) {
            XLN_hbTripleSTRUC( thee, GL21, GR21 );
        } else {
            XLN_wmTripleSTRUC( thee, GL21, GL12, GL22, GR21, GR12, GR22 );
        }
        break;
    case IS_SYM:
        if ( flagWMHB == 0 ) {
            VASSERT( GL21 == GR21 );
            XLN_hbTripleSYM( thee, GL21 );
        } else {
            VASSERT( (GL21 == GR21) && (GL12 == GR12) && (GL22 == GR22) );
            XLN_wmTripleSYM( thee, GL21, GL12, GL22 );
        }
        break;
    default:
        VASSERT(0);
    }
}

/*
 * ***************************************************************************
 * Routine:  XLN_hbTripleNSYM
 *
 * Purpose:  Produce the HB sparse triple matrix product:
 *
 *           A_hb = (I + GL') A (I + GR)
 *
 *                  = [  I     GL21'    ] [ A11 A12 ] [  I      0      ]
 *                    [  0     I        ] [ A21 A22 ] [ GR21    I      ]
 *
 *           where GL/GR are the left/right change of basis matrices.
 *
 *   Notes:  The G21 blocks must be ROW format.
 *
 *           The matrix A is overwritten with the result.
 *
 *  Method:  Heirarchical Basis (HB)
 *
 *           [A11 A12] += [ A12 GL21 + GL21'(A21 + A22 GR21); GL21'A22 ]
 *           [A21 A22]    [                        A22 GR21 ;  0       ]
 *
 * Warning:  Completely Untested!
 *
 * Author:   Stephen Bond and Burak Aksoylu 2002/01/26
 * ***************************************************************************
 */
VPRIVATE void XLN_hbTripleNSYM(Mat *thee, Mat *GL21, Mat *GR21 )
{
    int numR1, numR2, numR, numC1, numC2, numC;
    int ii, jj, k, kk, ll, imax, jmax;
    int *IG, *JG;
    double val_ij, *GU;
    MATsym psym = Mat_sym( thee );
    LinkRC *mt;

    VASSERT( psym == ISNOT_SYM );

    /* DO: A = (I + GL') * A * (I + GR ) */
    numR1 = Mat_numC(GL21);
    numR2 = Mat_numR(GL21);
    numR = numR1 + numR2;
    numC1 = Mat_numC(GR21);
    numC2 = Mat_numR(GR21);
    numC = numC1 + numC2;

    GU = GR21->A;
    IG = GR21->IA;
    JG = GR21->JA;
    /* STEP 1:  [ A11 A12 ] += [ A11 A12 ] [  0    0 ] */
    /*          [ A21 A22 ]    [ A21 A22 ] [ GR21  0 ] */
    for (k=0;k<numC2;k++) {
        kk = k + numC1;
        imax = numR;
        for (mt=Mat_accessXLN(thee, kk, 1);
             (mt!=VNULL) && (mt->idxT<imax); mt=mt->nextT) {
            if (((LinkRCS*)mt)->val != 0) {
                ii = mt->idxT;
                for (ll=IG[k]; ll<IG[k+1]; ll++) {
                    if (GU[ll] != 0) {
                        jj = JG[ll];
                        val_ij = ((LinkRCS*)mt)->val*GU[ll];
                        Mat_contribXLN( thee, 1, ii, jj, val_ij );
                    }
                }
            }
        }
    }
    GU = GL21->A;
    IG = GL21->IA;
    JG = GL21->JA;
    /* STEP 2:  [ A11 A12 ] += [ 0  GL21'] [ A11 A12 ] */
    /*          [ A21 A22 ]    [ 0    0  ] [ A21 A22 ] */
    for (k=0;k<numR2;k++) {
        kk = k + numR1;
        jmax = numC;
        for (mt=Mat_accessXLN(thee, kk, 0);
             (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
            if (((LinkRCS*)mt)->val != 0) {
                jj = mt->idx;
                for (ll=IG[k]; ll<IG[k+1]; ll++) {
                    if (GU[ll] != 0) {
                        ii = JG[ll];
                        val_ij = GU[ll]*((LinkRCS*)mt)->val;
                        Mat_contribXLN( thee, 1, ii, jj, val_ij );
                    }
                }
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  XLN_wmTripleNSYM
 *
 * Purpose:  Produce the WMHB sparse triple matrix product:
 *
 *           A_hb = (I + GL') A (I + GR)
 *
 *                  = [  I     GL21'    ] [ A11 A12 ] [  I      GR12   ]
 *                    [ GL12' (I+GL22') ] [ A21 A22 ] [ GR21  (I+GR22) ]
 *
 *           where GL/GR are the left/right change of basis matrices.
 *
 *   Notes:  The G21, G22, and G12 blocks must be ROW, DRC, and COL
 *           formats respectively.
 *
 *           The matrix A is overwritten with the A11 result.
 *
 *  Method:  Wavelet Modified Heirarchical Basis (WMHB)
 *
 *   [A11 A12] += [ GL21'(A21+A22*GR21) + A12*GR21 ; 0 ]
 *   [A21 A22]    [ GL22'(A21+A22*GR21) + A22*GR21 ; 0 ]
 *
 *              + [ 0                   ; GL21'(A22+A22*GR22+A21*GR12) ]
 *                [ GL21'(A11+A12*GR21) ; GL22'(A22+A22*GR22+A21*GR12) ]
 *
 *              + [ 0 ; A11*GR12 + A12*GR22                                ]
 *                [ 0 ; A21*GR12 + A22*GR22 + GL12'(A12+A12*GR22+A11*GR12) ]
 *
 * Warning:  Completely Untested!
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPRIVATE void XLN_wmTripleNSYM(Mat *thee,
    Mat *GL21, Mat *GL12, Mat *GL22, Mat *GR21, Mat *GR12, Mat *GR22 )
{
    int numR1, numR2, numR, numC1, numC2, numC;
    int i, ii, j, jj, k, kk, ll, rr;
    int count, *IJA, *IG, *JG, *IA2, *JA2;
    double val_ij, *GoffU, *Gdiag, *GoffL, *AA2;
    Mat *A2;
    MATsym psym = Mat_sym( thee );
    LinkRC *mt;

    VASSERT( psym == ISNOT_SYM );

    /* DO: A = (I + GL') * A * (I + GR ) */
    numR1 = Mat_numC(GL21);
    numR2 = Mat_numR(GL21);
    numR = numR1 + numR2;
    numC1 = Mat_numC(GR21);
    numC2 = Mat_numR(GR21);
    numC = numC1 + numC2;

    /* STEP 0:  Copy [ A12 ; A22 ] ==> A2 */
    count = 0;
    for (kk=numC1;kk<numC;kk++) {
        for (mt=Mat_accessXLN(thee, kk, 1);
             (mt!=VNULL) && (mt->idxT<numR); mt=mt->nextT) {
            if (((LinkRCS*)mt)->val != 0) {
                count++;
            }
        }
    }
    A2 = Mat_ctor( thee->vmem, "A2", numR, numC2 );
    IJA = Vmem_malloc( thee->vmem, count+numC2+1, sizeof(int) );
    Mat_initStructure( A2, COL_FORMAT, ISNOT_SYM, count, IJA, VNULL );
    IA2 = A2->IA;
    JA2 = A2->JA;
    AA2 = A2->A;

    count = 0;
    IA2[0] = 0;
    for (kk=numC1;kk<numC;kk++) {
        for (mt=Mat_accessXLN(thee, kk, 1);
             (mt!=VNULL) && (mt->idxT<numR); mt=mt->nextT) {
            if (((LinkRCS*)mt)->val != 0) {
                JA2[count] = mt->idxT;
                AA2[count] = ((LinkRCS*)mt)->val;
                count++;
            }
        }
        IA2[kk-numC1+1] = count;
    }

    /* STEP 1:  [ A11 A12 ] += [ A11 A12 ] [  0    GR12 ] */
    /*          [ A21 A22 ]    [ A21 A22 ] [  0    0    ] */
    GoffL = GR12->A;
    IG = GR12->IA;
    JG = GR12->JA;
    for (j=0;j<numC2;j++) {
        jj = j + numC1;
        for (ll=IG[j]; ll<IG[j+1]; ll++) {
            if (GoffL[ll] != 0) {
                kk = JG[ll];
                for (mt=Mat_accessXLN(thee, kk, 1);
                     (mt!=VNULL) && (mt->idxT<numR); mt=mt->nextT) {
                    if (((LinkRCS*)mt)->val != 0) {
                        ii = mt->idxT;
                        val_ij = ((LinkRCS*)mt)->val*GoffL[ll];
                        Mat_contribXLN( thee, 1, ii, jj, val_ij );
                    }
                }
            }
        }
    }

    /* STEP 2:  [ A11 A12 ] += [ A11 A12 ] [  0    0   ] */
    /*          [ A21 A22 ]    [ A21 A22 ] [ GR21  0   ] */
    /*   Note:  Uses the COPY of [A12; A22] stored in A2 */
    GoffU = GR21->A;
    IG = GR21->IA;
    JG = GR21->JA;
    for (k=0;k<numC2;k++) {
        kk = k + numC1;
        for (ll=IG[k]; ll<IG[k+1]; ll++) {
            if (GoffU[ll] != 0) {
                jj = JG[ll];
                for (rr=IA2[k]; rr<IA2[k+1]; rr++) {
                    ii = JA2[rr];
                    val_ij = AA2[rr]*GoffU[ll];
                    Mat_contribXLN( thee, 1, ii, jj, val_ij );
                }
            }
        }
    }

    /* STEP 3:  [ A11 A12 ] += [ A11 A12 ] [  0    0   ] */
    /*          [ A21 A22 ]    [ A21 A22 ] [  0  GR22  ] */
    /*   Note:  Uses the COPY of [A12; A22] stored in A2 */
    GoffL = GR22->offL;
    GoffU = GR22->offU;
    Gdiag = GR22->diag;
    IG = GR22->IA;
    JG = GR22->JA;
    for (k=0;k<numC2;k++) {
        kk = k + numC1;
        jj = kk;
        for (rr=IA2[k]; rr<IA2[k+1]; rr++) {
            ii = JA2[rr];
            val_ij = AA2[rr]*Gdiag[k];
            Mat_contribXLN( thee, 1, ii, jj, val_ij );
        }
        for (ll=IG[k]; ll<IG[k+1]; ll++) {
            if (GoffU[ll] != 0) {
                jj = JG[ll];
                for (rr=IA2[k]; rr<IA2[k+1]; rr++) {
                    ii = JA2[rr];
                    val_ij = AA2[rr]*GoffU[ll];
                    Mat_contribXLN( thee, 1, ii, jj, val_ij );
                }
            }
            if (GoffL[ll] != 0) { /* CHECK THIS LATER */
                i = JG[ll];
                ii = i + numC1;
                for (rr=IA2[i]; rr<IA2[i+1]; rr++) {
                    jj = JA2[rr];
                    val_ij = AA2[rr]*GoffL[ll];
                    Mat_contribXLN( thee, 1, jj, ii, val_ij );
                }
            }
        }
    }

    Mat_dtor( &A2 );

    /* STEP 4:  Copy [ A21 ; A22 ] ==> A2 */
    count = 0;
    for (kk=numR1;kk<numR;kk++) {
        for (mt=Mat_accessXLN(thee, kk, 0);
             (mt!=VNULL) && (mt->idx<numC); mt=mt->next) {
            if (((LinkRCS*)mt)->val != 0) {
                count++;
            }
        }
    }
    A2 = Mat_ctor( thee->vmem, "A2", numR2, numC );
    IJA = Vmem_malloc( thee->vmem, count+numR2+1, sizeof(int) );
    Mat_initStructure( A2, ROW_FORMAT, ISNOT_SYM, count, IJA, VNULL );
    IA2 = A2->IA;
    JA2 = A2->JA;
    AA2 = A2->A;

    count = 0;
    IA2[0] = 0;
    for (kk=numR1;kk<numR;kk++) {
        for (mt=Mat_accessXLN(thee, kk, 0);
             (mt!=VNULL) && (mt->idx<numR); mt=mt->next) {
            if (((LinkRCS*)mt)->val != 0) {
                JA2[count] = mt->idx;
                AA2[count] = ((LinkRCS*)mt)->val;
                count++;
            }
        }
        IA2[kk-numR1+1] = count;
    }

    /* STEP 5:  [ A11 A12 ] += [  0      0  ] [ A11 A12 ] */
    /*          [ A21 A22 ]    [ GL12'   0  ] [ A21 A22 ] */
    GoffL = GL12->A;
    IG = GL12->IA;
    JG = GL12->JA;
    for (i=0;i<numR2;i++) {
        ii = i + numR1;
        for (ll=IG[i]; ll<IG[i+1]; ll++) {
            if (GoffL[ll] != 0) {
                kk = JG[ll];
                for (mt=Mat_accessXLN(thee, kk, 0);
                     (mt!=VNULL) && (mt->idx<numC); mt=mt->next) {
                    if (((LinkRCS*)mt)->val != 0) {
                        jj = mt->idxT;
                        val_ij = ((LinkRCS*)mt)->val*GoffL[ll];
                        Mat_contribXLN( thee, 1, ii, jj, val_ij );
                    }
                }
            }
        }
    }

    /* STEP 6:  [ A11 A12 ] += [  0   GL21' ] [ A11 A12 ] */
    /*          [ A21 A22 ]    [  0    0    ] [ A21 A22 ] */
    /*   Note:  Uses the COPY of [ A21; A22] stored in A2 */
    GoffU = GL21->A;
    IG = GL21->IA;
    JG = GL21->JA;
    for (k=0;k<numR2;k++) {
        kk = k + numR1;
        for (ll=IG[k]; ll<IG[k+1]; ll++) {
            if (GoffU[ll] != 0) {
                ii = JG[ll];
                for (rr=IA2[k]; rr<IA2[k+1]; rr++) {
                    jj = JA2[rr];
                    val_ij = AA2[rr]*GoffU[ll];
                    Mat_contribXLN( thee, 1, ii, jj, val_ij );
                }
            }
        }
    }

    /* STEP 7:  [ A11 A12 ] += [  0    0   ] [ A11 A12 ] */
    /*          [ A21 A22 ]    [  0  GL22' ] [ A21 A22 ] */
    /*   Note:  Uses the COPY of [A21; A22] stored in A2 */
    GoffL = GL22->offL;
    GoffU = GL22->offU;
    Gdiag = GL22->diag;
    IG = GL22->IA;
    JG = GL22->JA;
    for (k=0;k<numR2;k++) {
        kk = k + numR1;
        ii = kk;
        for (rr=IA2[k]; rr<IA2[k+1]; rr++) {
            jj = JA2[rr];
            val_ij = AA2[rr]*Gdiag[k];
            Mat_contribXLN( thee, 1, ii, jj, val_ij );
        }
        for (ll=IG[k]; ll<IG[k+1]; ll++) {
            if (GoffU[ll] != 0) {
                ii = JG[ll];
                for (rr=IA2[k]; rr<IA2[k+1]; rr++) {
                    jj = JA2[rr];
                    val_ij = AA2[rr]*GoffU[ll];
                    Mat_contribXLN( thee, 1, ii, jj, val_ij );
                }
            }
            if (GoffL[ll] != 0) {
                j = JG[ll];
                jj = j + numC1;
                for (rr=IA2[j]; rr<IA2[j+1]; rr++) {
                    ii = JA2[rr];
                    val_ij = AA2[rr]*GoffL[ll];
                    Mat_contribXLN( thee, 1, kk, ii, val_ij );
                }
            }
        }
    }

    Mat_dtor( &A2 );
}

/*
 * ***************************************************************************
 * Routine:  XLN_hbTripleSYM
 *
 * Purpose:  Produce the HB sparse triple matrix product:
 *
 *           A_hb = (I + GL') A (I + GR)
 *
 *                  = [  I     GL21'    ] [ A11 A12 ] [  I      0      ]
 *                    [  0     I        ] [ A21 A22 ] [ GR21    I      ]
 *
 *           where GL/GR are the left/right change of basis matrices.
 *
 *   Notes:  The G21 block must be ROW format.  Since the XLN is of
 *           symmetric type, only the upper triangular portion is
 *           used/modified.
 *
 *           The matrix A is overwritten with the result.
 *
 *  Method:  Heirarchical Basis (HB)
 *
 *           [A11 A12] += [ A12 GL21 + GL21'(A21 + A22 GL21); GL21'A22 ]
 *           [A21 A22]    [                        A22 GL21 ;  0       ]
 *
 * Author:   Stephen Bond and Burak Aksoylu 2002/01/26
 * ***************************************************************************
 */
VPRIVATE void XLN_hbTripleSYM(Mat *thee, Mat *GL21)
{
    int numR1, numR2, numC1, numC2, numC;
    int ii, j, jj, k, kk, tt, rr, jmax;
    int *IG, *JG;
    double val_ij, val_ik, *GU;
    MATsym psym = Mat_sym( thee );
    LinkRC *mt;

    VASSERT( psym == IS_SYM );

    /* DO: A = (I + GL') * A * (I + GL ) */
    numR1 = Mat_numC(GL21);
    numR2 = Mat_numR(GL21);
    numC1 = Mat_numC(GL21);
    numC2 = Mat_numR(GL21);
    numC = numC1 + numC2;

    GU = GL21->A;
    IG = GL21->IA;
    JG = GL21->JA;
    /* STEP 1:  [ A11 A12 ] += [ A11 A12 ] [  0    0 ]  */
    /*          [ A21 A22 ]    [ A21 A22 ] [ GL21  0 ]  */
    /*                                                  */
    /*     (a) A11_{i<=j}  +=  [A12 GL21]_{i<=j}        */
    for (k=0;k<numC2;k++) {
        kk = k + numC1;
        for (mt=Mat_accessXLN( thee, kk, 1 );
             (mt!=VNULL) && (mt->idxT>=numR1); mt=mt->nextT) {
            /* no-op */
        }
        for ( /* no-op */;
             (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
            if (((LinkRCS*)mt)->val != 0) { /* [A12]_ik */
                ii = mt->idxT;
                for (rr=IG[k]; rr<IG[k+1]; rr++) {
                    if (GU[rr] != 0) { /* GL21_kj */
                        jj = JG[rr];
                        if ( ii <= jj ) {
                            val_ij = ((LinkRCS*)mt)->val*GU[rr];
                            Mat_contribXLN( thee, 1, ii, jj, val_ij );
                        }
                    }
                }
            }
        }
    }
    /*     (b) A12 += GL21'(D22 + U22) + (U22 GL21)'    */
    for (k=0;k<numR2;k++) {
        kk = k + numR1;
        jmax = numC;
        for (mt=Mat_accessXLN(thee, kk, 0);
             (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
            if (((LinkRCS*)mt)->val != 0) { /* [D22+U22]_kj */
                jj = mt->idx;
                for (rr=IG[k]; rr<IG[k+1]; rr++) {
                    if (GU[rr] != 0) { /* GL21_ki */
                        ii = JG[rr];
                        val_ij = GU[rr]*((LinkRCS*)mt)->val;
                        Mat_contribXLN( thee, 1, ii, jj, val_ij );
                    }
                }
                if (kk != jj ) { /* [U22]_kj */
                    j = jj - numC1;
                    for (tt=IG[j]; tt<IG[j+1]; tt++) {
                        if (GU[tt] != 0) { /* GL_21_ji */
                            ii = JG[tt];
                            val_ik = GU[tt]*((LinkRCS*)mt)->val;
                            Mat_contribXLN( thee, 1, ii, kk, val_ik );
                        }
                    }
                }
            }
        }
    }
    /* STEP 2:  [ A11 A12 ] += [ 0  GL21'] [ A11 A12 ]  */
    /*          [ A21 A22 ]    [ 0   0   ] [ A21 A22 ]  */
    /*                                                  */
    /*     (a) A11_{i<=j}  +=  [(A12*GL21)']_{i<=j}     */
    for (k=0;k<numC2;k++) {
        kk = k + numC1;
        for (mt=Mat_accessXLN( thee, kk, 1 );
             (mt!=VNULL) && (mt->idxT>=numR1); mt=mt->nextT) {
            /* no-op */
        }
        for (/* no-op */;
             (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
            if (((LinkRCS*)mt)->val != 0) { /* A12_ik */
                ii = mt->idxT;
                for (rr=IG[k]; rr<IG[k+1]; rr++) {
                    if (GU[rr] != 0) { /* GL21_kj */
                        jj = JG[rr];
                        if ( jj<=ii ) {
                            val_ij = ((LinkRCS*)mt)->val*GU[rr];
                            Mat_contribXLN( thee, 1, jj, ii, val_ij );
                        }
                    }
                }
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  XLN_wmTripleSYM
 *
 * Purpose:  Produce the WMHB sparse triple matrix product:
 *
 *           A_hb = (I + GL') A (I + GR)
 *
 *                  = [  I     GL21'    ] [ A11 A12 ] [  I      GR12   ]
 *                    [ GL12' (I+GL22') ] [ A21 A22 ] [ GR21  (I+GR22) ]
 *
 *           where GL/GR are the left/right change of basis matrices.
 *
 *   Notes:  The G21, G22, and G12 blocks must be ROW, DRC, and COL
 *           formats respectively.  Since the XLN is of symmetric type,
 *           only the upper triangular portion is used/modified.
 *
 *           The matrix A is overwritten with the A11 result.
 *
 *  Method:  Wavelet Modified Heirarchical Basis (WMHB)
 *
 *   [A11 A12] += [ GL21'(A21+A22*GR21) + A12*GR21 ; 0 ]
 *   [A21 A22]    [ GL22'(A21+A22*GR21) + A22*GR21 ; 0 ]
 *
 *              + [ 0                   ; GL21'(A22+A22*GR22+A21*GR12) ]
 *                [ GL21'(A11+A12*GR21) ; GL22'(A22+A22*GR22+A21*GR12) ]
 *
 *              + [ 0 ; A11*GR12 + A12*GR22                                ]
 *                [ 0 ; A21*GR12 + A22*GR22 + GL12'(A12+A12*GR22+A11*GR12) ]
 *
 * Author:   Stephen Bond and Burak Aksoylu 2002/01/26
 * ***************************************************************************
 */
VPRIVATE void XLN_wmTripleSYM(Mat *thee, Mat *GL21, Mat *GL12, Mat *GL22 )
{
    VASSERT( 0 );
}

/*
 * ***************************************************************************
 * Routine:  XLN_hbTripleSTRUC
 *
 * Purpose:  Produce the HB sparse triple matrix product:
 *
 *           A_hb = (I + GL') A (I + GR)
 *
 *                  = [  I     GL21'    ] [ A11 A12 ] [  I      0      ]
 *                    [  0     I        ] [ A21 A22 ] [ GR21    I      ]
 *
 *           where GL/GR are the left/right change of basis matrices.
 *
 *   Notes:  The G21 block must be ROW format.
 *
 *           The matrix A is overwritten with the result.
 *
 *  Method:  Heirarchical Basis (HB)
 *
 *           [A11 A12] += [ A12 GR21 + GL21'(A21 + A22 GR21); GL21'A22 ]
 *           [A21 A22]    [                        A22 GR21 ;  0       ]
 *
 * Author:   Stephen Bond and Burak Aksoylu 2002/01/26
 * ***************************************************************************
 */
VPRIVATE void XLN_hbTripleSTRUC(Mat *thee, Mat *GL21, Mat *GR21)
{
    int numR1, numR2, numC1, numC2, numC;
    int i, ii, j, jj, k, kk, rr, tt, jmax;
    int *IG, *JG;
    double val_ij, val_ik, val_jk, *GU;
    MATsym psym = Mat_sym( thee );
    LinkRC *mt;

    VASSERT( psym == STRUC_SYM );

    /* DO: A = (I + GL') * A * (I + GR ) */
    numR1 = Mat_numC(GL21);
    numR2 = Mat_numR(GL21);
    numC1 = Mat_numC(GR21);
    numC2 = Mat_numR(GR21);
    numC = numC1 + numC2;

    GU = GR21->A;
    IG = GR21->IA;
    JG = GR21->JA;
    /* STEP 1:  [ A11 A12 ] += [ A11 A12 ] [  0    0 ]  */
    /*          [ A21 A22 ]    [ A21 A22 ] [ GR21  0 ]  */
    /*                                                  */
    /*     (a) [ A11 ] +=  [ A12 ] [ GR21 ]             */
    for (k=0;k<numC2;k++) {
        kk = k + numC1;
        for (mt=Mat_accessXLN( thee, kk, 1 );
             (mt!=VNULL) && (mt->idxT>=numR1); mt=mt->nextT) {
            /* no-op */
        }
        for (/* no-op */;
             (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
            if (((LinkRCN*)mt)->val != 0) { /* [A12]_ik */
                ii = mt->idxT;
                for (rr=IG[k]; rr<IG[k+1]; rr++) {
                    if (GU[rr] != 0) { /* GR21_kj */
                        jj = JG[rr];
                        val_ij = ((LinkRCN*)mt)->val*GU[rr];
                        Mat_contribXLN( thee, 1, ii, jj, val_ij );
                    }
                }
            }
        }
    }
    /*     (b) [ A21 ] += [ D22 + U22 + L22 ] [ GR21 ]  */
    for (i=0;i<numR2;i++) {
        ii = i + numR1;
        jmax = numC;
        for (mt=Mat_accessXLN(thee, ii, 0);
             (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
            jj = mt->idx;
            if (((LinkRCN*)mt)->val != 0) { /* [D22+U22]_ij */
                j = jj - numC1;
                for (rr=IG[j]; rr<IG[j+1]; rr++) {
                    if (GU[rr] != 0) { /* GR21_jk */
                        kk = JG[rr];
                        val_ik = ((LinkRCN*)mt)->val*GU[rr];
                        Mat_contribXLN( thee, 1, ii, kk, val_ik );
                    }
                }
            }
            if ( (ii < jj) && (((LinkRCN*)mt)->valT != 0) ) { /* [L22]_ji */
                for (tt=IG[i]; tt<IG[i+1]; tt++) {
                    if (GU[tt] != 0) { /* GR21_ik */
                        kk = JG[tt];
                        val_jk = ((LinkRCN*)mt)->valT*GU[tt];
                        Mat_contribXLN( thee, 1, jj, kk, val_jk );
                    }
                }
            }
        }
    }
    GU = GL21->A;
    IG = GL21->IA;
    JG = GL21->JA;
    /* STEP 2:  [ A11 A12 ] += [ 0  GL21'] [ A11 A12 ]  */
    /*          [ A21 A22 ]    [ 0   0   ] [ A21 A22 ]  */
    /*                                                  */
    /*     (a) [ A11 ]  +=  [ GL21' ] [ A21 ]           */
    for (k=0;k<numC2;k++) {
        kk = k + numC1;
        for (mt=Mat_accessXLN( thee, kk, 1 );
             (mt!=VNULL) && (mt->idxT>=numR1); mt=mt->nextT) {
            /* no-op */
        }
        for (/* no-op */;
             (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
            if (((LinkRCN*)mt)->valT != 0) { /* [A21]_ki */
                ii = mt->idxT;
                for (rr=IG[k]; rr<IG[k+1]; rr++) {
                    if (GU[rr] != 0) { /* GL21_kj */
                        jj = JG[rr];
                        val_ij = GU[rr]*((LinkRCN*)mt)->valT;
                        Mat_contribXLN( thee, 1, jj, ii, val_ij );
                    }
                }
            }
        }
    }
    /*     (b) [ A12 ] += [ GR21' ] [ D22 + U22 + L22 ] */
    for (i=0;i<numR2;i++) {
        ii = i + numR1;
        jmax = numC;
        for (mt=Mat_accessXLN(thee, ii, 0);
             (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
            jj = mt->idx;
            if (((LinkRCN*)mt)->val != 0) { /* [D22+U22]_ij */
                for (rr=IG[i]; rr<IG[i+1]; rr++) {
                    if (GU[rr] != 0) { /* GL21_ik */
                        kk = JG[rr];
                        val_jk = GU[rr]*((LinkRCN*)mt)->val;
                        Mat_contribXLN( thee, 1, kk, jj, val_jk );
                    }
                }
            }
            if ( (ii < jj) && (((LinkRCN*)mt)->valT != 0) ) { /* [L22]_ji */
                j = jj - numC1;
                for (tt=IG[j]; tt<IG[j+1]; tt++) {
                    if (GU[tt] != 0) { /* GR21_jk */
                        kk = JG[tt];
                        val_ik = GU[tt]*((LinkRCN*)mt)->valT;
                        Mat_contribXLN( thee, 1, kk, ii, val_ik );
                    }
                }
            }
        }
    }

}

/*
 * ***************************************************************************
 * Routine:  XLN_wmTripleSTRUC
 *
 * Purpose:  Produce the WMHB sparse triple matrix product:
 *
 *           A_hb = (I + GL') A (I + GR)
 *
 *                  = [  I     GL21'    ] [ A11 A12 ] [  I      GR12   ]
 *                    [ GL12' (I+GL22') ] [ A21 A22 ] [ GR21  (I+GR22) ]
 *
 *           where GL/GR are the left/right change of basis matrices.
 *
 *   Notes:  The G21, G22, and G12 blocks must be ROW, DRC, and COL
 *           formats respectively.
 *
 *           The matrix A is overwritten with the A11 result.
 *
 *  Method:  Wavelet Modified Heirarchical Basis (WMHB)
 *
 *   [A11 A12] += [ GL21'(A21+A22*GR21) + A12*GR21 ; 0 ]
 *   [A21 A22]    [ GL22'(A21+A22*GR21) + A22*GR21 ; 0 ]
 *
 *              + [ 0                   ; GL21'(A22+A22*GR22+A21*GR12) ]
 *                [ GL21'(A11+A12*GR21) ; GL22'(A22+A22*GR22+A21*GR12) ]
 *
 *              + [ 0 ; A11*GR12 + A12*GR22                                ]
 *                [ 0 ; A21*GR12 + A22*GR22 + GL12'(A12+A12*GR22+A11*GR12) ]
 *
 * Author:   Stephen Bond and Burak Aksoylu 2002/01/26
 * ***************************************************************************
 */
VPRIVATE void XLN_wmTripleSTRUC(Mat *thee,
    Mat *GL21, Mat *GL12, Mat *GL22, Mat *GR21, Mat *GR12, Mat *GR22 )
{
    int i, ii, j, jj, kk, ll;
    int numR1, numR2, numR, numC1, numC2, numC;
    double val_ij, val_kj, val_ik;
    int *IG, *JG;
    double *GoffL, *GoffU;
    Mat *A12, *A21, *A22;
    LinkRC *mt;

#if 0
    Mat_printSp(GL12,"G12.m",0);
    Mat_printSp(GL21,"G21.m",0);
    Mat_printSp(GL22,"G22.m",0);
    Mat_printSp(thee,"Anodal.m",0);
#endif

    /* DO: A = (I + GL') * A * (I + GR ) */
    numR1 = Mat_numC(GL21);
    numR2 = Mat_numR(GL21);
    numR = numR1 + numR2;

    numC1 = Mat_numC(GR21);
    numC2 = Mat_numR(GR21);
    numC = numC1 + numC2;

    /* STEP 0:  Copy [ A12 ; A22 ] */
    A12 = Mat_ctor( thee->vmem, "A12", numR1, numC2 );
    XLN_copySubblock( A12, thee, 12 );

    A22 = Mat_ctor( thee->vmem, "A22", numR2, numC2 );
    XLN_copySubblock( A22, thee, 22 );

    /* STEP 1:  [ A11 A12 ] += [ A11 A12 ] [  0   GR12 ] */
    /*          [ A21 A22 ]    [ A21 A22 ] [  0    0   ] */
    GoffL = GR12->A;
    GoffU = VNULL;
    IG = GR12->IA;
    JG = GR12->JA;
    for (jj=numC1;jj<numC;jj++) {
        j = jj - numC1;
        for (ll=IG[j]; ll<IG[j+1]; ll++) {
            if (GoffL[ll] != 0) { /* GR12_kj */
                kk = JG[ll];
                mt = Mat_accessXLN(thee, kk, 1); /* D11_kk */
                val_kj = ((LinkRCS*)mt)->val*GoffL[ll];
                Mat_contribXLN( thee, 1, kk, jj, val_kj );
                for (mt=mt->nextT;
                     (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
                    if (((LinkRCN*)mt)->val != 0) { /* U11_ik */
                        ii = mt->idxT;
                        val_ij = ((LinkRCN*)mt)->val*GoffL[ll];
                        Mat_contribXLN( thee, 1, ii, jj, val_ij );
                    }
                }
                mt = Mat_accessXLN(thee, kk, 0);
                for (mt=mt->next;
                     (mt!=VNULL) && (mt->idx<numC); mt=mt->next) {
                    if (((LinkRCN*)mt)->valT != 0) { /* L11_ik or A21_ik */
                        ii = mt->idx;
                        val_ij = ((LinkRCN*)mt)->valT*GoffL[ll];
                        Mat_contribXLN( thee, 1, ii, jj, val_ij );
                    }
                }
            }
        }
    }

    /* STEP 2:  [ A11 A12 ] += [ A11 A12 ] [  0     0  ] */
    /*          [ A21 A22 ]    [ A21 A22 ] [ GR21   0  ] */
    XLN_matmatContrib( thee, A12, 0, 0, GR21, 0, 0 );
    XLN_matmatContrib( thee, A22, numR1, 0, GR21, 0, 0 );

    /* STEP 3:  [ A11 A12 ] += [ A11 A12 ] [  0     0  ] */
    /*          [ A21 A22 ]    [ A21 A22 ] [  0   GR22 ] */

    XLN_matmatContrib( thee, A12, 0, 0, GR22, numC1, 0 );
    XLN_matmatContrib( thee, A22, numR1, 0, GR22, numC1, 0 );

    Mat_dtor( &A12 );
    Mat_dtor( &A22 );

    /* STEP 4:  Copy [ A21 ; A22 ] */
    A21 = Mat_ctor( thee->vmem, "A21", numR2, numC1 );
    XLN_copySubblock( A21, thee, 21 );

    A22 = Mat_ctor( thee->vmem, "A22", numR2, numC2 );
    XLN_copySubblock( A22, thee, 22 );

    /* STEP 5:  [ A11 A12 ] += [  0     0  ] [ A11 A12 ] */
    /*          [ A21 A22 ]    [ GL12'  0  ] [ A21 A22 ] */
    GoffU = GL12->A;
    GoffL = VNULL;
    IG = GL12->IA;
    JG = GL12->JA;
    for (ii=numR1;ii<numR;ii++) {
        i = ii - numR1;
        for (ll=IG[i]; ll<IG[i+1]; ll++) {
            if (GoffU[ll] != 0) { /* [GL12']_ik */
                kk = JG[ll];
                mt = Mat_accessXLN(thee, kk, 1); /* D11_kk */
                val_ik = ((LinkRCS*)mt)->val*GoffU[ll];
                Mat_contribXLN( thee, 1, ii, kk, val_ik );
                for (mt=mt->nextT;
                     (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
                    if (((LinkRCN*)mt)->valT != 0) { /* L11_kj */
                        jj = mt->idxT;
                        val_ij = GoffU[ll]*((LinkRCN*)mt)->valT;
                        Mat_contribXLN( thee, 1, ii, jj, val_ij );
                    }
                }
                mt = Mat_accessXLN(thee, kk, 0);
                for (mt=mt->next;
                     (mt!=VNULL) && (mt->idx<numC); mt=mt->next) {
                    if (((LinkRCN*)mt)->val != 0) { /* U11_kj or A12_kj */
                        jj = mt->idx;
                        val_ij = GoffU[ll]*((LinkRCN*)mt)->val;
                        Mat_contribXLN( thee, 1, ii, jj, val_ij );
                    }
                }
            }
        }
    }

    /* STEP 6:  [ A11 A12 ] += [  0  GL21' ] [ A11 A12 ] */
    /*          [ A21 A22 ]    [  0    0   ] [ A21 A22 ] */
    XLN_matmatContrib( thee, GL21, 0, 1, A21, 0, 0 );
    XLN_matmatContrib( thee, GL21, 0, 1, A22, numC1, 0);

    /* STEP 7:  [ A11 A12 ] += [  0    0   ] [ A11 A12 ] */
    /*          [ A21 A22 ]    [  0  GL22' ] [ A21 A22 ] */
    XLN_matmatContrib( thee, GL22, numR1, 1, A21,  0, 0 );
    XLN_matmatContrib( thee, GL22, numR1, 1, A22, numC1, 0 );

    Mat_dtor( &A21 );
    Mat_dtor( &A22 );

#if 0
    Mat_printSp(thee,"Awmhb.m",0);
#endif
}

/*
 * ***************************************************************************
 * Routine:  XLN_copyBlocks
 *
 * Purpose:  Copies the A12, A21, and A22 blocks of a XLN, storing them
 *           in Mats of type COL, ROW, and DRC respectively.
 *
 *   Notes:  The logical position of each block is determined from the
 *           sizes of the other blocks.
 *
 *                    [   A11    |   A12   ]
 *                    [ sepxsep  | sepxn   ]
 *           A_hb  =  [----------|---------]  where numR = sep + n
 *                    [   A21    |   A22   ]
 *                    [   nxsep  |   nxn   ]
 *
 *           A12, A21, A22 must be passed w/ NULL_STATE (i.e. after ctor).
 *
 * Author:   Burak Aksoylu and Stephen Bond 2002/01/26
 * ***************************************************************************
 */
VPUBLIC void XLN_copyBlocks(Mat *Ablock, Mat *A12, Mat *A21, Mat *A22)
{
    XLN_copySubblock( A12, Ablock, 12 );

    if ( Mat_sym( Ablock ) != IS_SYM ) {

        XLN_copySubblock( A21, Ablock, 21 );

    } else {
        A21->numA = -1; /* HB CODE FOR "ARRAY IS JUST A POINTER" */
        A21->sym = ISNOT_SYM;
        A21->IJA = A12->IJA;
        A21->IA  = A12->IA;
        A21->JA  = A12->JA;
        A21->A   = A12->A;
        A21->state = ASSEMBLED_STATE;
        A21->format = ROW_FORMAT;
    }

    XLN_copySubblock( A22, Ablock, 22 );

}

/*
 * ***************************************************************************
 * Routine:  XLN_matmatContrib
 *
 * Purpose:  Multiplies two Mat's contributing the result to an XLN.
 *
 *   Notes:  The offset of the contrib is controlled by ibase, jbase.
 *           If flag1 (flag2) is nonzero, the first (second) matrix
 *           is applied using its transpose.
 *
 *           This routine is used by the WMHB method while forming
 *           the triple matrix product.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void XLN_matmatContrib(Mat *thee, Mat *Ablock1, int ibase, int flag1,
                               Mat *Ablock2, int jbase, int flag2 )
{
    int *IA1, *IA2, *JA1, *JA2, numR1, numC1, numR2, numC2;
    double *offL1 = VNULL, *offU1 = VNULL, *diag1 = VNULL;
    double *offL2 = VNULL, *offU2 = VNULL, *diag2 = VNULL;
    int i, ii, j, jj, kk, rr, tt;
    double val;
    MATformat frmt1 = Mat_format(Ablock1), frmt2 = Mat_format(Ablock2);

    if (flag1 == 0) {
        numR1 = Mat_numR(Ablock1);
        numC1 = Mat_numC(Ablock1);
    } else {
        numC1 = Mat_numR(Ablock1);
        numR1 = Mat_numC(Ablock1);
    }

    IA1 = Mat_IA(Ablock1);
    JA1 = Mat_JA(Ablock1);

    switch(frmt1) {
    case COL_FORMAT:
        if (flag1 == 0) {
            offL1 = Mat_A(Ablock1);
        } else {
            offU1 = Mat_A(Ablock1);
        }
        break;
    case ROW_FORMAT:
        if (flag1 == 0) {
            offU1 = Mat_A(Ablock1);
        } else {
            offL1 = Mat_A(Ablock1);
        }
        break;
    case DRC_FORMAT:
        if (flag1 == 0) {
            offU1 = Mat_offU(Ablock1);
            offL1 = Mat_offL(Ablock1);
        } else {
            offL1 = Mat_offU(Ablock1);
            offU1 = Mat_offL(Ablock1);
        }
        diag1 = Mat_diag(Ablock1);
        break;
    default:
        VASSERT(0);
    }

    if (flag2 == 0) {
        numR2 = Mat_numR(Ablock2);
        numC2 = Mat_numC(Ablock2);
    } else {
        numC2 = Mat_numR(Ablock2);
        numR2 = Mat_numC(Ablock2);
    }

    IA2 = Mat_IA(Ablock2);
    JA2 = Mat_JA(Ablock2);

    switch(frmt2) {
    case COL_FORMAT:
        if (flag2 == 0) {
            offL2 = Mat_A(Ablock2);
        } else {
            offU2 = Mat_A(Ablock2);
        }
        break;
    case ROW_FORMAT:
        if (flag2 == 0) {
            offU2 = Mat_A(Ablock2);
        } else {
            offL2 = Mat_A(Ablock2);
        }
        break;
    case DRC_FORMAT:
        if (flag2 == 0) {
            offU2 = Mat_offU(Ablock2);
            offL2 = Mat_offL(Ablock2);
        } else {
            offL2 = Mat_offU(Ablock2);
            offU2 = Mat_offL(Ablock2);
        }
        diag2 = Mat_diag(Ablock2);
        break;
    default:
        VASSERT(0);
    }

    /* STEP 1: D1 * U2 */
    if (diag1 != VNULL && offU2 != VNULL) {
        for(ii=0; ii<numR2; ii++) {
            i = ii + ibase;
            for(tt=IA2[ii]; tt<IA2[ii+1]; tt++) {
                j = JA2[tt] + jbase;
                Mat_contribXLN( thee, 1, i, j, diag1[ii]*offU2[tt] );
            }
        }
    }

    /* STEP 2: D1 * L2 */
    if (diag1 != VNULL && offL2 != VNULL) {
        for(jj=0; jj<numC2; jj++) {
            j = jj + jbase;
            for(tt=IA2[jj]; tt<IA2[jj+1]; tt++) {
                ii = JA2[tt];
                i = ii + ibase;
                Mat_contribXLN( thee, 1, i, j, diag1[ii]*offL2[tt] );
            }
        }
    }

    /* STEP 3: D1 * D2 */
    if (diag1 != VNULL && diag2 != VNULL) {
        for(ii=0; ii<numR2; ii++) {
            i = ii + ibase;
            j = ii + jbase;
            Mat_contribXLN( thee, 1, i, j, diag1[ii]*diag2[ii] );
        }
    }

    /* STEP 4: U1 * U2 */
    if (offU1 != VNULL && offU2 != VNULL) {
        for(ii=0; ii<numR1; ii++) {
            i = ii + ibase;
            for(rr=IA1[ii]; rr<IA1[ii+1]; rr++) {
                kk = JA1[rr];
                for(tt=IA2[kk]; tt<IA2[kk+1]; tt++) {
                    j = JA2[tt] + jbase;
                    Mat_contribXLN( thee, 1, i, j, offU1[rr]*offU2[tt] );
                }
            }
        }
    }

    /* STEP 5: U1 * L2 */
    if (offU1 != VNULL && offL2 != VNULL) {
        for(ii=0; ii<numR1; ii++) {
            i = ii + ibase;
            for(jj=0; jj<numC2; jj++) {
                j = jj + jbase;
                rr = IA1[ii];
                tt = IA2[jj];
                val = 0.0;
                while( (rr<IA1[ii+1]) && (tt<IA2[jj+1]) ) {
                    if( JA1[rr] == JA2[tt] ) {
                        val += offU1[rr]*offL2[tt];
                        rr++;
                        tt++;
                    } else if( JA1[rr] < JA2[tt] ) {
                        rr++;
                    } else {
                        tt++;
                    }
                }
                if ( val != 0.0 ) {
                    Mat_contribXLN( thee, 1, i, j, val );
                }
            }
        }
    }

    /* STEP 6: U1 * D2 */
    if (offU1 != VNULL && diag2 != VNULL) {
        for(ii=0; ii<numR1; ii++) {
            i = ii + ibase;
            for(rr=IA1[ii]; rr<IA1[ii+1]; rr++) {
                jj = JA1[rr];
                j =  jj + jbase;
                Mat_contribXLN( thee, 1, i, j, offU1[rr]*diag2[jj] );
            }
        }
    }

    /* STEP 7: L1 * U2 */
    if (offL1 != VNULL && offU2 != VNULL) {
        for(kk=0; kk<numC1; kk++) {
            for(rr=IA1[kk]; rr<IA1[kk+1]; rr++) {
                i = JA1[rr] + ibase;
                for(tt=IA2[kk]; tt<IA2[kk+1]; tt++) {
                    j = JA2[tt] + jbase;
                    Mat_contribXLN( thee, 1, i, j, offL1[rr]*offU2[tt] );
                }
            }
        }
    }

    /* STEP 8: L1 * L2 */
    if (offL1 != VNULL && offL2 != VNULL) {
        for(jj=0; jj<numR2; jj++) {
            j = jj + jbase;
            for(tt=IA2[jj]; tt<IA2[jj+1]; tt++) {
                kk = JA2[tt];
                for(rr=IA1[kk]; rr<IA1[kk+1]; rr++) {
                    i = JA1[rr] + ibase;
                    Mat_contribXLN( thee, 1, i, j, offL1[rr]*offL2[tt] );
                }
            }
        }
    }

    /* STEP 9: L1 * D2 */
    if (offL1 != VNULL && diag2 != VNULL) {
        for(jj=0; jj<numC1; jj++) {
            j = jj + jbase;
            for(rr=IA1[jj]; rr<IA1[jj+1]; rr++) {
                i =  JA1[rr] + ibase;
                Mat_contribXLN( thee, 1, i, j, offL1[rr]*diag2[jj] );
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  XLN_copySubblock
 *
 * Purpose:  Copies the A12, A21, or A22 subblock of a XLN, storing it
 *           in a Mat of type COL, ROW, or DRC respectively.
 *
 *   Notes:  The logical position of each block is determined from the
 *           sizes of the other blocks.
 *
 *                    [   A11    |   A12   ]
 *                    [ sepxsep  | sepxn   ]
 *           A_hb  =  [----------|---------]  where numR = sep + n
 *                    [   A21    |   A22   ]
 *                    [   nxsep  |   nxn   ]
 *
 *           The subblock must be passed w/ NULL_STATE (i.e. after ctor).
 *
 * Author:   Burak Aksoylu and Stephen Bond 2002/01/26
 * ***************************************************************************
 */
VPUBLIC void XLN_copySubblock(Mat *thee, Mat *Amat, int flag)
{
    int i, j, ii, jj;
    int count;
    int numR, numC, numRb, numCb, imin, jmin, imax, jmax;
    int *IJA = VNULL;
    MATsym pqsym = Mat_sym( Amat );
    LinkRC *mt;

    numR = Mat_numR(Amat);
    numC = Mat_numC(Amat);
    numRb = Mat_numR(thee);
    numCb = Mat_numC(thee);

    switch(flag) {
    case 12:
        imin = 0;
        imax = numRb;
        jmin = numC - numCb;
        jmax = numC;
        break;
    case 21:
        if ( pqsym == ISNOT_SYM ) {
            imin = numR - numRb;
            imax = numR;
            jmin = 0;
            jmax = numCb;
        } else {
            imin = 0;
            imax = numCb;
            jmin = numR - numRb;
            jmax = numR;
        }
        break;
    case 22:
        imin = numR - numRb;
        imax = numR;
        jmin = numC - numCb;
        jmax = numC;
        break;
    default:
        VASSERT(0);
    }

    /* STEP 0: determine the nonzero structure */
    count = 0;
    switch (pqsym) {
      case IS_SYM:
      case STRUC_SYM:
        VASSERT( numC == numR );
        switch(flag) {
          case 12:
          case 21:
            for (jj=jmin; jj<jmax; jj++) {
                for (mt=(Mat_accessXLN( Amat, jj, 1 ))->nextT;
                     (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
                    if ( mt->idxT < imax ) {
                        count++;
                    }
                }
            }
            break; /* case 12/21 */
          case 22:
            VASSERT( imin == jmin );
            for (ii=imin; ii<imax; ii++) {
                for (mt=(Mat_accessXLN( Amat, ii, 0 ))->next;
                     (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
                    count++;
                }
            }
            break; /* case 22 */
        }
        break; /* case IS_SYM/STRUC_SYM */
      case ISNOT_SYM:
        switch(flag) {
          case 12:
            for (jj=jmin; jj<jmax; jj++) {
                for (mt=Mat_accessXLN( Amat, jj, 1 );
                     (mt!=VNULL) && (mt->idxT<imax); mt=mt->nextT) {
                    count++;
                }
            }
            break; /* case 12 */
          case 21:
            for (ii=imin; ii<imax; ii++) {
                for (mt=Mat_accessXLN( Amat, ii, 0 );
                     (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
                    count++;
                }
            }
            break; /* case 21 */
          case 22:
            for (ii=imin; ii<imax; ii++) {
                for (mt=Mat_accessXLN( Amat, ii, 0 );
                     (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
                    if ( mt->idx >= jmin ) {
                        count++;
                    }
                }
            }
            break; /* case 22 */
        }
        break;
      default:
        VASSERT(0);
    }

    /* STEP 1: initialize the nonzero structure */
    switch(flag) {
      case 12:
        IJA = Vmem_malloc( thee->vmem, count+numCb+1, sizeof(int) );
        Mat_initStructure( thee, COL_FORMAT, ISNOT_SYM, count, IJA, VNULL );
        break;
      case 21:
        IJA = Vmem_malloc( thee->vmem, count+numRb+1, sizeof(int) );
        Mat_initStructure( thee, ROW_FORMAT, ISNOT_SYM, count, IJA, VNULL );
        break;
      case 22:
        switch (pqsym) {
          case IS_SYM:
            IJA = Vmem_malloc( thee->vmem, count+numRb+1, sizeof(int) );
            Mat_initStructure( thee, DRC_FORMAT, IS_SYM, count, IJA, VNULL );
            break;
          case STRUC_SYM:
            IJA = Vmem_malloc( thee->vmem, count+numRb+1, sizeof(int) );
            Mat_initStructure( thee, DRC_FORMAT, ISNOT_SYM, count, IJA, VNULL );
            break;
          case ISNOT_SYM:
            if (numCb > numRb) {
                IJA = Vmem_malloc( thee->vmem, count+numRb+1, sizeof(int) );
                Mat_initStructure( thee, ROW_FORMAT, pqsym, count, IJA, VNULL );
            } else {
                IJA = Vmem_malloc( thee->vmem, count+numCb+1, sizeof(int) );
                Mat_initStructure( thee, COL_FORMAT, pqsym, count, IJA, VNULL );
            }
            break;
          default:
            VASSERT(0);
        }
        break;
      default:
        VASSERT(0);
    }
    thee->state = ASSEMBLED_STATE;

    /* STEP 2: copy the block */
    switch (pqsym) {
      case IS_SYM:
        VASSERT( numC == numR );
        switch(flag) {
          case 12:
          case 21:
            thee->IA[jmax-jmin] = count; /* MUST BE ASSEMBLED BACKWARDS! */
            for (jj=(jmax-1); jj>=jmin; jj--) {
                for (mt=(Mat_accessXLN( Amat, jj, 1 ))->nextT;
                     (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
                    if ( mt->idxT < imax ) {
                        count--;
                        thee->JA[count] = mt->idxT;
                        thee->A[count] = ((LinkRCS*)mt)->val;
                    }
                }
                thee->IA[jj-jmin] = count;
            }
            break; /* case 12/21 */
          case 22:
            VASSERT( imin == jmin );
            thee->IA[0] = 0;
            count = 0;
            for (ii=imin; ii<imax; ii++) {
                i = ii - imin;
                mt = Mat_accessXLN( Amat, ii, 0 );
                thee->diag[i] = ((LinkRCS*)mt)->val;
                for (mt=mt->next;
                     (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
                    thee->JA[count] = mt->idx - jmin;
                    thee->offU[count] = ((LinkRCS*)mt)->val;
                    count++;
                }
                thee->IA[i+1] = count;
            }
            break; /* case 22 */
        }
        break;
      case STRUC_SYM:
        VASSERT( numC == numR );
        switch(flag) {
          case 12:
            thee->IA[jmax-jmin] = count; /* MUST BE ASSEMBLED BACKWARDS! */
            for (jj=(jmax-1); jj>=jmin; jj--) {
                for (mt=(Mat_accessXLN( Amat, jj, 1 ))->nextT;
                     (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
                    if ( mt->idxT < imax ) {
                        count--;
                        thee->JA[count] = mt->idxT;
                        thee->A[count] = ((LinkRCS*)mt)->val;
                    }
                }
                thee->IA[jj-jmin] = count;
            }
            break; /* case 12 */
          case 21:
            thee->IA[jmax-jmin] = count; /* MUST BE ASSEMBLED BACKWARDS! */
            for (jj=(jmax-1); jj>=jmin; jj--) {
                for (mt=(Mat_accessXLN( Amat, jj, 1 ))->nextT;
                     (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
                    if ( mt->idxT < imax ) {
                        count--;
                        thee->JA[count] = mt->idxT;
                        thee->A[count] = ((LinkRCN*)mt)->valT;
                    }
                }
                thee->IA[jj-jmin] = count;
            }
            break; /* case 21 */
          case 22:
            VASSERT( imin == jmin );
            thee->IA[0] = 0;
            count = 0;
            for (ii=imin; ii<imax; ii++) {
                i = ii - imin;
                mt = Mat_accessXLN( Amat, ii, 0 );
                thee->diag[i] = ((LinkRCS*)mt)->val;
                for (mt=mt->next;
                     (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
                    thee->JA[count] = mt->idx - jmin;
                    thee->offU[count] = ((LinkRCN*)mt)->val;
                    thee->offL[count] = ((LinkRCN*)mt)->valT;
                    count++;
                }
                thee->IA[i+1] = count;
            }
            break; /* case 22 */
        }
        break;
      case ISNOT_SYM:
        count = 0;
        thee->IA[0] = 0;
        switch(flag) {
          case 12:
            for (jj=jmin; jj<jmax; jj++) {
                j = jj - jmin;
                for (mt=Mat_accessXLN( Amat, jj, 1 );
                     (mt!=VNULL) && (mt->idxT<imax); mt=mt->nextT) {
                    thee->JA[count] = mt->idx;
                    thee->A[count] = ((LinkRCS*)mt)->val;
                    count++;
                }
                thee->IA[j+1] = count;
            }
            break; /* case 12 */
          case 21:
            for (ii=imin; ii<imax; ii++) {
                i = ii - imin;
                for (mt=Mat_accessXLN( Amat, ii, 0 );
                     (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
                    thee->JA[count] = mt->idxT;
                    thee->A[count] = ((LinkRCS*)mt)->val;
                    count++;
                }
                thee->IA[i+1] = count;
            }
            break; /* case 21 */
          case 22:
            if (numCb > numRb) {
                for (ii=imin; ii<imax; ii++) {
                    i = ii - imin;
                    for (mt=Mat_accessXLN( Amat, ii, 0 );
                         (mt!=VNULL) && (mt->idx<jmax); mt=mt->next) {
                        if ( mt->idx >= jmin ) {
                            thee->JA[count] = mt->idxT - imin;
                            thee->A[count] = ((LinkRCS*)mt)->val;
                            count++;
                        }
                    }
                    thee->IA[i+1] = count;
                }
            } else {
                for (jj=jmin; jj<jmax; jj++) {
                    j = jj - jmin;
                    for (mt=Mat_accessXLN( Amat, jj, 1 );
                         (mt!=VNULL) && (mt->idxT<imax); mt=mt->next) {
                        if ( mt->idxT >= imin ) {
                            thee->JA[count] = mt->idx - jmin;
                            thee->A[count] = ((LinkRCS*)mt)->val;
                            count++;
                        }
                    }
                    thee->IA[j+1] = count;
                }
            }
            break; /* case 22 */
        }
        break;
      default:
        VASSERT(0);
    }
}

/*
 * ***************************************************************************
 * Routine:  XLN_shrinkLogical
 *
 * Purpose:  Sets the sizes of the logical blocks inside a XLN using
 *           the number of rows and cols in two different Mats.
 *
 *   Notes:  This method is used exclusively by HB methods to "replace"
 *           the matrix A with its A11 subblock.  The size of the A11
 *           sublock can be uniquely determined using the sizes of the A12
 *           and A21 sublocks:
 *
 *                 [   A11    |   A12   ]
 *                 [ sepxsep  | sepxn   ]
 *           A  =  [----------|---------]  where numR = sep + n
 *                 [   A21    |         ]
 *                 [   nxsep  |         ]
 *
 *           In the future, this routine may actually shrink the matrix,
 *           but for now it only sets the internal numR and numC values
 *           to reflect the size of the logical A11 block.
 *
 * Author:   Burak Aksoylu and Stephen Bond 2002/01/26
 * ***************************************************************************
 */
VPUBLIC void XLN_shrinkLogical(Mat *thee, Mat *A12, Mat *A21 )
{

    thee->numR = Mat_numR(A12);
    thee->numC = Mat_numC(A21);

}

/*
 * ***************************************************************************
 * Routine:  Mat_initGWMHB
 *
 * Purpose:  Constructs G12/G22 for WMHB using Mhb and G21.
 *
 *   Notes:  This routine is the second step in the construction of the
 *           change of basis matrix for WMHB.  It constructs the G12 and
 *           G22 blocks using the mass matrix in the HB basis:
 *
 *           [ G11 ] = [ 0 ]  ;   [ G12 ] =  [ I ] inv(-Mhb_11) Mhb_12
 *           [ G21 ]   [ R ]      [ G22 ]    [ R ]
 *
 *           where Mhb is the previously formed mass matrix in the HB basis:
 *
 *           Mhb = [ Mhb_11 Mhb_12 ] = [ I R'] [ M_11 M_12 ] [ I 0 ]
 *                 [ Mhb_21 Mhb_22 ]   [ 0 I ] [ M_21 M_22 ] [ R I ]
 *
 *           Here inv( . ) represents any approximation to the inverse.
 *           To keep optimal complexity this should be chosen very carefully.
 *           Some possible choices include special matrix polynomials,
 *           mass lumping, or simply the inverse of the diagonal.
 *
 *           The G12 and G22 blocks should be passed in with zero state,
 *           with only their shape determined (i.e. just after ctor).  The
 *           G21 block must already exist, and contain the tail of the
 *           prolongation matrix, R.
 *
 * Author:   Stephen Bond 2002/02/03
 * ***************************************************************************
 */
VPUBLIC void Mat_initGWMHB(Mat *G12, Mat *G22, Mat *G21, Mat *Mblock)
{
    int i, ii, j, jj, valb;
    int k1, kk1, k2, kk2, numC1, numC2, numC, numR1, numR2;
    int count, *IJA, *IG, *JG, *IR, *JR, *JG22, *IG22;
    double *GA, *RA, *G22U = VNULL, *G22L = VNULL, *G22D = VNULL;
    double val_ij, val_ji;
    LinkRC *mt, *mtD;

    numR1 = Mat_numR(G12);
    numR2 = Mat_numR(G21);
    numC1 = Mat_numC(G21);
    numC2 = Mat_numC(G12);
    numC  = numC1 + numC2;

    /* Step 1:  Compute the nonzero structure of G12    */
    count = 0;
    for (jj=numC1; jj<numC; jj++) {
        for (mt=Mat_accessXLN( Mblock, jj, 1 );
             (mt!=VNULL) && (mt->idxT>=numR1); mt=mt->nextT) {
            /* no-op */
        }
        for (/* no-op */; (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
            count++;
        }
    }

    /* Step 2:  Initialize the nonzero structure of G12 */
    IJA = Vmem_malloc( G12->vmem, count+numC2+1, sizeof(int) );
    Mat_initStructure( G12, COL_FORMAT, ISNOT_SYM, count, IJA, VNULL );
    G12->state = ASSEMBLED_STATE;
    IG = Mat_IA(G12);
    JG = Mat_JA(G12);
    GA = Mat_A(G12);

    /* Step 3:  Compute G12 = inv(-Mhb_11) Mhb_12       */
    /*          MUST BE ASSEMBLED BACKWARDS!            */
    IG[numC2] = count;
    for (j=(numC2-1); j>=0; j--) {
        jj = j + numC1;
        for (mt=Mat_accessXLN( Mblock, jj, 1 );
             (mt!=VNULL) && (mt->idxT>=numR1); mt=mt->nextT) {
            /* no-op */
        }
        for (/* no-op */; (mt!=VNULL) && (mt->idxT>=0); mt=mt->nextT) {
            count--;
            ii = mt->idxT;
            mtD = Mat_accessXLN( Mblock, ii, 0 );
            JG[count] = ii;
            GA[count] = -1.0*((LinkRCS*)mt)->val/((LinkRCS*)mtD)->val;
                    /* -[Mhb12]_ij/[Mhb11]_ii */
        }
        IG[j] = count;
    }

    /* Step 4: Compute the nonzero structure of G22       */
    /*         Uses a double indexed symmetric count loop */
    IR = Mat_IA(G21);
    JR = Mat_JA(G21);
    RA = Mat_A(G21);
    VASSERT( numR2 == numC2 );
    /* Loop over all index pairs (i,j) with j>i */
    count = 0;
    for (i=0; i<numR2; i++) {
        for (j=(i+1); j<numC2; j++) {
            valb = 0;
            kk1 = IR[i];
            kk2 = IG[j];
            /* First check to see if the (i,j) entry is nonzero */
            while ( (!valb) && (kk1<IR[i+1]) && (kk2<IG[j+1]) ) {
                k1 = JR[kk1];
                k2 = JG[kk2];
                if (k1 == k2) {
                    /* terminate the loop if nonzero */
                    valb = ( (RA[kk1] != 0) && (GA[kk2] != 0) );
                    kk1++;
                    kk2++;
                } else if (k1 < k2) {
                    kk1++;
                } else {
                    kk2++;
                }
            }
            kk1 = IR[j];
            kk2 = IG[i];
            /* Second check to see if the (j,i) entry is nonzero */
            while ( (!valb) && (kk1<IR[j+1]) && (kk2<IG[i+1]) ) {
                k1 = JR[kk1];
                k2 = JG[kk2];
                if (k1 == k2) {
                    /* terminate the loop if nonzero */
                    valb = ( (GA[kk2] != 0) && (RA[kk1] != 0) );
                    kk1++;
                    kk2++;
                } else if (k1 < k2) {
                    kk1++;
                } else {
                    kk2++;
                }
            }
            if (valb != 0) count++;
        }
    }

    /* Step 5:  Initialize the nonzero structure of G22 */
    IJA = Vmem_malloc( G22->vmem, count+numR2+1, sizeof(int) );
    Mat_initStructure( G22, DRC_FORMAT, ISNOT_SYM, count, IJA, VNULL );
    G22->state = ASSEMBLED_STATE;

    IG22 = Mat_IA( G22 );
    JG22 = Mat_JA( G22 );
    G22D = Mat_diag( G22 );
    G22U = Mat_offU( G22 );
    G22L = Mat_offL( G22 );

    /* Step 6:  Compute G22 = G21 * G12                 */
    for (i=0; i<numR2; i++) { /* Compute D22 */
        val_ij = 0.0;
        kk1 = IR[i];
        kk2 = IG[i];
        while ( (kk1<IR[i+1]) && (kk2<IG[i+1]) ) {
            k1 = JR[kk1];
            k2 = JG[kk2];
            if (k1 == k2) {
                val_ij += RA[kk1] * GA[kk2];
                kk1++;
                kk2++;
            } else if (k1 < k2) {
                kk1++;
            } else {
                kk2++;
            }
        }
        G22D[i] = val_ij;
    }
    count = 0;
    IG22[0] = 0;
    for (i=0; i<numR2; i++) { /* Compute U22 and L22 */
        for (j=(i+1); j<numC2; j++) {
            valb = 0;
            val_ij = 0.0;
            kk1 = IR[i];
            kk2 = IG[j];
            while ( (kk1<IR[i+1]) && (kk2<IG[j+1]) ) { /* U22_ij */
                k1 = JR[kk1];
                k2 = JG[kk2];
                if (k1 == k2) {
                    if ( (RA[kk1] != 0) && (GA[kk2] != 0) ) {
                        valb = 1;
                        val_ij += RA[kk1] * GA[kk2];
                    }
                    kk1++;
                    kk2++;
                } else if (k1 < k2) {
                    kk1++;
                } else {
                    kk2++;
                }
            }
            val_ji = 0.0;
            kk1 = IR[j];
            kk2 = IG[i];
            while ( (kk1<IR[j+1]) && (kk2<IG[i+1]) ) { /* L22_ji */
                k1 = JR[kk1];
                k2 = JG[kk2];
                if (k1 == k2) {
                    if ( (GA[kk2] != 0) && (RA[kk1] != 0) ) {
                        valb = 1;
                        val_ji += GA[kk2] * RA[kk1];
                    }
                    kk1++;
                    kk2++;
                } else if (k1 < k2) {
                    kk1++;
                } else {
                    kk2++;
                }
            }
            if (valb != 0) {
                G22U[count] = val_ij;
                G22L[count] = val_ji;
                JG22[count] = j;
                count++;
            }
        }
        IG22[i+1] = count;
    }
}
