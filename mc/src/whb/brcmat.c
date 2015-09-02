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
 * rcsid="$Id: brcmat.c,v 1.5 2010/08/12 05:19:19 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     brcmat.c
 *
 * Purpose:  Class Whb: special linked list data structures.
 *
 * Author:   Burak Aksoylu, Stephen Bond, and Michael Holst
 * ***************************************************************************
 */

#include "brcmat_p.h"

VEMBED(rcsid="$Id: brcmat.c,v 1.5 2010/08/12 05:19:19 fetk Exp $")

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
 * Routine:  BXLN_copyBmat
 *
 * Purpose:  Create an BXLN copy of a Bmat.
 *
 *    Note:  Only the upper triangular part of any symmetric part is copied.
 *
 * Author:   Stephen Bond 2002/01/28
 * ***************************************************************************
 */
VPUBLIC void BXLN_copyBmat(Bmat *thee, Bmat *Amat)
{
    int p, q, numB;

    numB = thee->numB;

    for(p=0; p<numB; p++) {
        for(q=0; q<numB; q++) {
            if( !thee->mirror[p][q] ) {
                switch( Mat_format( Amat->AD[p][q] ) ) {
                  case DRC_FORMAT:
                    Mat_copyDRC2XLN( thee->AD[p][q], Amat->AD[p][q] );
                    break;
                  case ROW_FORMAT:
                    Mat_copyROW2XLN( thee->AD[p][q], Amat->AD[p][q] );
                    break;
                  case COL_FORMAT:
                    Mat_copyCOL2XLN( thee->AD[p][q], Amat->AD[p][q] );
                    break;
                  default:
                    VASSERT( 0 );
                }
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_copyBXLN
 *
 * Purpose:  Produces a Bmat copy of a BXLN.
 *
 * Author:   Stephen Bond 2002/01/26
 * ***************************************************************************
 */
VPUBLIC void Bmat_copyBXLN(Bmat *thee, Bmat *Alink)
{
    int p, q, numB;

    VASSERT( thee->numB == Alink->numB );

    numB = thee->numB;

    for (p=0; p<numB; p++) {
        for (q=0; q<numB; q++) {
            if( !thee->mirror[p][q] ) {
                switch( Mat_sym( Alink->AD[p][q] ) ) {
                  case IS_SYM:
                  case STRUC_SYM:
                    Mat_copyXLN2DRC( thee->AD[p][q], Alink->AD[p][q] );
                    break;
                  case ISNOT_SYM:
                    if ( p <= q ) {
                        Mat_copyXLN2ROW( thee->AD[p][q], Alink->AD[p][q] );
                    } else {
                        Mat_copyXLN2COL( thee->AD[p][q], Alink->AD[p][q] );
                    }
                    break;
                  default:
                    VASSERT(0);
               }
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  BXLN_hbTriple
 *
 * Purpose:  Produce the HB sparse triple matrix product:
 *
 *           A(p,q)_hb = (I + G(p)') A(p,q) (I + G(q))
 *
 *                  = [  I     Gp21'    ] [ Apq11 Apq12 ] [  I      Gq12   ]
 *                    [ Gp12' (I+Gp22') ] [ Apq21 Apq22 ] [ Gq21  (I+Gq22) ]
 *
 *           for every (p,q) block of A_hb.
 *
 *   Notes:  The G21, G22, and G12 blocks must be ROW, DRC, and COL
 *           formats respectively.  Any NULL blocks are treated as
 *           zero matrices.  If the subblock of the BXLN is of symmetric
 *           type, only the upper triangular portion is used/modified.
 *
 *           The matrix A is overwritten with the A11 result.
 *
 *  Method:  CASE 1: Heirarchical Basis (HB)
 *
 *           [A11 A12] += [ A12 Gq21 + Gp21'(A21 + A22 Gq21); Gp21'A22 ]
 *           [A21 A22]    [                        A22 Gq21 ;  0       ]
 *
 *           CASE 2: Wavelet Modified Heirarchical Basis (WMHB)
 *
 *   [A11 A12] += [ Gp21'(A21+A22*Gq21) + A12*Gq21 ; 0 ]
 *   [A21 A22]    [ Gp22'(A21+A22*Gq21) + A22*Gq21 ; 0 ]
 *
 *              + [ 0                   ; Gp21'(A22+A22*Gq22+A21*Gq12) ]
 *                [ Gp21'(A11+A12*Gq21) ; Gp22'(A22+A22*Gq22+A21*Gq12) ]
 *
 *              + [ 0 ; A11*Gq12 + A12*Gq22                                ]
 *                [ 0 ; A21*Gq12 + A22*Gq22 + Gp12'(A12+A12*Gq22+A11*Gq12) ]
 *
 * Author:   Stephen Bond and Burak Aksoylu 2002/01/26
 * ***************************************************************************
 */
VPUBLIC void BXLN_hbTriple(Bmat *thee, HBmat *G)
{
    int p, q, numB;
    Mat *Gp21, *Gq22, *Gp12;
    Mat *Gq21, *Gp22, *Gq12;

    numB = thee->numB;

    for (p=0; p<numB; p++) {
        Gp21 = G->A21->AD[p][p];
        Gp12 = G->A12->AD[p][p];
        Gp22 = G->A22->AD[p][p];

        for (q=0; q<numB; q++) {
            Gq21 = G->A21->AD[q][q];
            Gq12 = G->A12->AD[q][q];
            Gq22 = G->A22->AD[q][q];

            if( !thee->mirror[p][q] ) {
                XLN_hbTriple( thee->AD[p][q],
                    Gp21, Gp12, Gp22, Gq21, Gq12, Gq22 );
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  BXLN_copyBlocks
 *
 * Purpose:  Copies the A12, A21, and A22 blocks of a XLN, storing them
 *           in Mats of type COL, ROW, and DRC respectively.
 *
 *   Notes:  The logical position of eacg block is determined from the
 *           sizes of the other blocks.
 *
 *                    [   A11    |   A12   ]
 *                    [ sepxsep  | sepxn   ]
 *           A_hb  =  [----------|---------]  where numR = sep + n
 *                    [   A21    |   A22   ]
 *                    [   nxsep  |   nxn   ]
 *
 *           A12, A21, A22 must be passed w/ NULL_STATE blocks.
 *
 * Author:   Burak Aksoylu and Stephen Bond 2002/01/26
 * ***************************************************************************
 */
VPUBLIC void BXLN_copyBlocks(Bmat *Alink, Bmat *A12, Bmat *A21, Bmat *A22)
{
    int p, q, numB;

    numB = Alink->numB;

    for (p=0; p<numB; p++) {
        for(q=0; q<numB; q++) {
            if( !Alink->mirror[p][q] ) {
                XLN_copyBlocks( Alink->AD[p][q],
                    A12->AD[p][q], A21->AD[p][q], A22->AD[p][q]);
            }
        }
    }

}

/*
 * ***************************************************************************
 * Routine:  BXLN_shrinkLogical
 *
 * Purpose:  Sets the sizes of the logical blocks inside a BXLN using
 *           the number of rows and cols in two different Bmats.
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
 *           but for now it only sets the internal numR and numC arrays
 *           to reflect the size of the logical A11 block.
 *
 * Author:   Burak Aksoylu and Stephen Bond 2002/01/26
 * ***************************************************************************
 */
VPUBLIC void BXLN_shrinkLogical(Bmat *thee, Bmat *A12, Bmat *A21 )
{
    int p, q, numB;

    numB = thee->numB;

    for (p=0; p<numB; p++) {
        for (q=0; q<numB; q++) {
            if( !thee->mirror[p][q] ) {
                XLN_shrinkLogical( thee->AD[p][q],
                    A12->AD[p][q], A21->AD[p][q] );
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  HBmat_GHB2WMHB
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
 *           The G12 and G22 blocks should be passed in with NULL_STATE
 *           subblocks, with only their shape determined (i.e. just after
 *           ctor).  The G21 block must already exist, and contain the tail
 *           of the prolongation matrix, i.e. P = [I ; R].
 *
 * Author:   Stephen Bond 2002/02/03
 * ***************************************************************************
 */
VPUBLIC void HBmat_GHB2WMHB(HBmat *thee, Bmat *Mhb)
{
    int p, numB = Mhb->numB;
    Bmat *G12 = thee->A12, *G22 = thee->A22, *G21 = thee->A21;

    for (p=0; p<numB; p++) {
        Mat_initGWMHB( G12->AD[p][p], G22->AD[p][p],
            G21->AD[p][p], Mhb->AD[p][p] );
    }
}
