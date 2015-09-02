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
 * rcsid="$Id: matcopy.c,v 1.9 2010/08/12 05:18:28 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     matcopy.c
 *
 * Purpose:  Class Mat: matrix copy routines.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */

#include "mat_p.h"

VEMBED(rcsid="$Id: matcopy.c,v 1.9 2010/08/12 05:18:28 fetk Exp $")

/*
 * ***************************************************************************
 * Class Mat: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_BAM)

#endif /* if !defined(VINLINE_BAM) */
/*
 * ***************************************************************************
 * Class Mat: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Mat_copy
 *
 * Purpose:  Copy a matrix.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copy(Mat *thee, Mat *smat)
{
  int i, count, sizeIJA, *IJA;
  LinkA *mt;

  VASSERT( thee->numR == smat->numR );
  VASSERT( thee->numC == smat->numC );

  VASSERT( thee->state == NULL_STATE );
  VASSERT( smat->state >= ASSEMBLED_STATE );

  switch (smat->format) {

    case DRC_FORMAT:
      VASSERT( thee->numR == thee->numC );

      sizeIJA = smat->numO+smat->numR+1;
      IJA = Vmem_malloc( thee->vmem, sizeIJA, sizeof(int) );
      Mat_initStructure( thee, DRC_FORMAT, smat->sym, smat->numO, IJA, VNULL );

      /* Perform vector copy on the raw data */
      for (i=0; i<sizeIJA; i++)
          thee->IJA[i] = smat->IJA[i];

      for (i=0; i<smat->numA; i++)
          thee->A[i] = smat->A[i];

      break;

    case ROW_FORMAT:
      VASSERT( smat->sym == ISNOT_SYM );

      sizeIJA = smat->numO+smat->numR+1;
      IJA = Vmem_malloc( thee->vmem, sizeIJA, sizeof(int) );
      Mat_initStructure( thee, ROW_FORMAT, smat->sym, smat->numO, IJA, VNULL );

      /* Perform vector copy on the raw data */
      for (i=0; i<sizeIJA; i++)
          thee->IJA[i] = smat->IJA[i];

      for (i=0; i<smat->numA; i++)
          thee->A[i] = smat->A[i];
      break;

    case COL_FORMAT:
      VASSERT( smat->sym == ISNOT_SYM );

      sizeIJA = smat->numO+smat->numC+1;
      IJA = Vmem_malloc( thee->vmem, sizeIJA, sizeof(int) );
      Mat_initStructure( thee, COL_FORMAT, smat->sym, smat->numO, IJA, VNULL );

      /* Perform vector copy on the raw data */
      for (i=0; i<sizeIJA; i++)
          thee->IJA[i] = smat->IJA[i];

      for (i=0; i<smat->numA; i++)
          thee->A[i] = smat->A[i];
      break;

    case RLN_FORMAT:
      VASSERT( smat->sym == ISNOT_SYM );
      Mat_initStructureLN( thee, RLN_FORMAT, smat->sym );

      count = 0;
      for (i=0; i<smat->numR; i++) {
          for (mt=(LinkA*)Vset_access(smat->lnkU, i);
               mt!=VNULL; mt=mt->next) {
              if ( mt->idx >= 0 ) {
                  mContrib( thee->lnkU, 0, &count, i, mt->idx, mt->val );
              }
          }
      }
      thee->numO = count;

      break;

    case CLN_FORMAT:
      VASSERT( smat->sym == ISNOT_SYM );
      Mat_initStructureLN( thee, CLN_FORMAT, smat->sym );

      count = 0;
      for (i=0; i<smat->numC; i++) {
          for (mt=(LinkA*)Vset_access(smat->lnkL, i);
               mt!=VNULL; mt=mt->next) {
              if ( mt->idx >= 0 ) {
                  mContrib( thee->lnkL, 0, &count, i, mt->idx, mt->val );
              }
          }
      }
      thee->numO = count;

      break;

    default:
      /* All other cases are currently unsupported */
      VASSERT( 0 );
  }

  thee->state = ASSEMBLED_STATE;

}

/*
 * ***************************************************************************
 * Routine:  Mat_format2format
 *
 * Purpose:  Copies a matrix as a new matrix with specified format.
 *
 * Notes:    This routine requires that the first matrix is passed with
 *           NULL_STATE and ZERO_FORMAT, i.e. just after ctor.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_format2format(Mat *thee, Mat *smat, MATformat frmt )
{
    Mat * tmat;

    VASSERT( thee->numR == smat->numR );
    VASSERT( thee->numC == smat->numC );
    VASSERT( thee->format == ZERO_FORMAT );
    VASSERT( thee->state == NULL_STATE );

    switch (smat->format) {
      case DRC_FORMAT:

        switch (frmt) {
          case DRC_FORMAT: /* DRC2DRC */
            Mat_copy( thee, smat );
            break;
          case ROW_FORMAT: /* DRC2ROW */
            tmat = Mat_ctor( thee->vmem, "temp", thee->numR, thee->numC );
            Mat_copyDRC2RLN( tmat, smat );
            Mat_copyRLN2ROW( thee, tmat );
            Mat_dtor( &(tmat) );
            break;
          case COL_FORMAT: /* DRC2COL */
            tmat = Mat_ctor( thee->vmem, "temp", thee->numR, thee->numC );
            Mat_copyDRC2CLN( tmat, smat );
            Mat_copyCLN2COL( thee, tmat );
            Mat_dtor( &(tmat) );
            break;
          case RLN_FORMAT: /* DRC2RLN */
            Mat_copyDRC2RLN( thee, smat );
            break;
          case CLN_FORMAT: /* DRC2CLN */
            Mat_copyDRC2CLN( thee, smat );
            break;
          case XLN_FORMAT: /* DRC2XLN */
            Mat_copyDRC2XLN( thee, smat );
            break;
          default:
            VASSERT(0);
        }

        break;
      case ROW_FORMAT:

        switch (frmt) {
          case DRC_FORMAT: /* ROW2DRC */
            tmat = Mat_ctor( thee->vmem, "temp", thee->numR, thee->numC );
            Mat_copyROW2XLN( tmat, smat );
            Mat_copyXLN2DRC( thee, tmat );
            Mat_dtor( &(tmat) );
            break;
          case ROW_FORMAT: /* ROW2ROW */
            Mat_copy( thee, smat );
            break;
          case COL_FORMAT: /* ROW2COL */
            Mat_copyROW2COL( thee, smat );
            break;
          case RLN_FORMAT: /* ROW2RLN */
            Mat_copyROW2RLN( thee, smat );
            break;
          case CLN_FORMAT: /* ROW2CLN */
            Mat_copyROW2CLN( thee, smat );
            break;
          case XLN_FORMAT: /* ROW2XLN */
            Mat_copyROW2XLN( thee, smat );
            break;
          default:
            VASSERT(0);
        }

        break;
      case COL_FORMAT:

        switch (frmt) {
          case DRC_FORMAT: /* COL2DRC */
            tmat = Mat_ctor( thee->vmem, "temp", thee->numR, thee->numC );
            Mat_copyCOL2XLN( tmat, smat );
            Mat_copyXLN2DRC( thee, tmat );
            Mat_dtor( &(tmat) );
            break;
          case ROW_FORMAT: /* COL2ROW */
            Mat_copyCOL2ROW( thee, smat );
            break;
          case COL_FORMAT: /* COL2COL */
            Mat_copy( thee, smat );
            break;
          case RLN_FORMAT: /* COL2RLN */
            Mat_copyCOL2RLN( thee, smat );
            break;
          case CLN_FORMAT: /* COL2CLN */
            Mat_copyCOL2CLN( thee, smat );
            break;
          case XLN_FORMAT: /* COL2XLN */
            Mat_copyCOL2XLN( thee, smat );
            break;
          default:
            VASSERT(0);
        }

        break;
      case RLN_FORMAT:

        switch (frmt) {
          case DRC_FORMAT: /* RLN2DRC */
            tmat = Mat_ctor( thee->vmem, "temp", thee->numR, thee->numC );
            Mat_copyRLN2XLN( tmat, smat );
            Mat_copyXLN2DRC( thee, tmat );
            Mat_dtor( &(tmat) );
            break;
          case ROW_FORMAT: /* RLN2ROW */
            Mat_copyRLN2ROW( thee, smat );
            break;
          case COL_FORMAT: /* RLN2COL */
            tmat = Mat_ctor( thee->vmem, "temp", thee->numR, thee->numC );
            Mat_copyRLN2CLN( tmat, smat );
            Mat_copyCLN2COL( thee, tmat );
            Mat_dtor( &(tmat) );
            break;
          case RLN_FORMAT: /* RLN2RLN */
            Mat_copy( thee, smat );
            break;
          case CLN_FORMAT: /* RLN2CLN */
            Mat_copyRLN2CLN( thee, smat );
            break;
          case XLN_FORMAT: /* RLN2XLN */
            Mat_copyRLN2XLN( thee, smat );
            break;
          default:
            VASSERT(0);
        }

        break;
      case CLN_FORMAT:

        switch (frmt) {
          case DRC_FORMAT: /* CLN2DRC */
            tmat = Mat_ctor( thee->vmem, "temp", thee->numR, thee->numC );
            Mat_copyCLN2XLN( tmat, smat );
            Mat_copyXLN2DRC( thee, tmat );
            Mat_dtor( &(tmat) );
            break;
          case ROW_FORMAT: /* CLN2ROW */
            tmat = Mat_ctor( thee->vmem, "temp", thee->numR, thee->numC );
            Mat_copyCLN2RLN( tmat, smat );
            Mat_copyRLN2ROW( thee, tmat );
            Mat_dtor( &(tmat) );
            break;
          case COL_FORMAT: /* CLN2COL */
            Mat_copyCLN2COL( thee, smat );
            break;
          case RLN_FORMAT: /* CLN2RLN */
            Mat_copyCLN2RLN( thee, smat );
            break;
          case CLN_FORMAT: /* CLN2CLN */
            Mat_copy( thee, smat );
            break;
          case XLN_FORMAT: /* CLN2XLN */
            Mat_copyCLN2XLN( thee, smat );
            break;
          default:
            VASSERT(0);
        }

        break;
      case XLN_FORMAT:

        switch (frmt) {
          case DRC_FORMAT: /* XLN2DRC */
            Mat_copyXLN2DRC( thee, smat );
            break;
          case ROW_FORMAT: /* XLN2ROW */
            Mat_copyXLN2ROW( thee, smat );
            break;
          case COL_FORMAT: /* XLN2COL */
            Mat_copyXLN2COL( thee, smat );
            break;
          case RLN_FORMAT: /* XLN2RLN */
            Mat_copyXLN2RLN( thee, smat );
            break;
          case CLN_FORMAT: /* XLN2CLN */
            Mat_copyXLN2CLN( thee, smat );
            break;
          case XLN_FORMAT: /* XLN2XLN */
            Mat_copy( thee, smat );
            break;
          default:
            VASSERT(0);
        }

        break;
      default:
        VASSERT(0);
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyROW2COL
 *
 * Purpose:  Copy a matrix from ROW to COL.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyROW2COL(Mat *thee, Mat *smat)
{
    int *work;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == ROW_FORMAT);

    /* Build the transposed IJA and A arrays */
    work = Vmem_malloc( thee->vmem, thee->numC, sizeof(int) );
    mBuildGraphT( thee->vmem, &(thee->IJA), &(thee->A), &(thee->numO),
        smat->IJA, smat->A, smat->numR, smat->numC, 2, work );
    Vmem_free( thee->vmem, thee->numC, sizeof(int), (void**) &(work) );

    /* Set all the internal pointers and parameters */
    thee->format = COL_FORMAT;
    thee->sym    = ISNOT_SYM;

    thee->IA   = thee->IJA;
    thee->JA   = thee->IJA + thee->numC + 1;
    thee->numZ = thee->numO;
    thee->numA = thee->numO;

    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyCOL2ROW
 *
 * Purpose:  Copy a matrix from COL to ROW.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyCOL2ROW(Mat *thee, Mat *smat)
{
    int *work;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == COL_FORMAT);

    /* Build the transposed IJA and A arrays */
    work = Vmem_malloc( thee->vmem, thee->numR, sizeof(int) );
    mBuildGraphT( thee->vmem, &(thee->IJA), &(thee->A), &(thee->numO),
        smat->IJA, smat->A, smat->numC, smat->numR, 2, work );
    Vmem_free( thee->vmem, thee->numR, sizeof(int), (void**) &(work) );

    /* Set all the internal pointers and parameters */
    thee->format = COL_FORMAT;
    thee->sym    = ISNOT_SYM;

    thee->IA   = thee->IJA;
    thee->JA   = thee->IJA + thee->numR + 1;
    thee->numZ = thee->numO;
    thee->numA = thee->numO;

    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyDRC2RLN
 *
 * Purpose:  Copy a matrix from DRC to RLN.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_copyDRC2RLN(Mat *thee, Mat *smat)
{
    int i, j, k, count;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == DRC_FORMAT);

    /* initialize the RLN structure */
    Mat_initStructureLN( thee, RLN_FORMAT, ISNOT_SYM );

    /* now get the RLN structure of the matrix */
    count=0;
    for (i=0; i<smat->numR; i++) {
        j = i;
        mContrib( thee->lnkU, 0, &count, i, j, smat->diag[i] );
        for(k=smat->IA[i]; k<smat->IA[i+1]; k++) {
            j = smat->JA[k];
            mContrib( thee->lnkU, 0, &count, i, j, smat->offU[k]);
            /* roles of "i" and "j" reversed for upper triangle */
            mContrib( thee->lnkU, 0, &count, j, i, smat->offL[k]);
        }
    }

    /* we are done */
    VASSERT( count == smat->numZ );

    thee->numO = count;
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyROW2RLN
 *
 * Purpose:  Copy a matrix from ROW to RLN.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_copyROW2RLN(Mat *thee, Mat *smat)
{
    int i, j, k, count;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == ROW_FORMAT);

    /* initialize the RLN structure */
    Mat_initStructureLN( thee, RLN_FORMAT, ISNOT_SYM );

    /* now get the RLN structure of the matrix */
    count=0;
    for (i=0; i<smat->numR; i++) {
        j = i;
        for(k=smat->IA[i]; k<smat->IA[i+1]; k++) {
            j = smat->JA[k];
            mContrib(thee->lnkU, 0, &count, i, j, smat->A[k]);
        }
    }

    /* we are done */
    VASSERT( count == smat->numZ );

    thee->numO = count;
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyCOL2RLN
 *
 * Purpose:  Copy a matrix from COL to RLN.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_copyCOL2RLN(Mat *thee, Mat *smat)
{
    int i, j, k, count;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == COL_FORMAT);

    /* initialize the RLN structure */
    Mat_initStructureLN( thee, RLN_FORMAT, ISNOT_SYM );

    /* now get the RLN structure of the matrix */
    count=0;
    for (j=0; j<smat->numC; j++) {
        for(k=smat->IA[j]; k<smat->IA[j+1]; k++) {
            i = smat->JA[k];
            mContrib(thee->lnkU, 0, &count, i, j, smat->A[k]);
        }
    }

    /* we are done */
    VASSERT( count == smat->numZ );

    thee->numO = count;
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyRLN2ROW
 *
 * Purpose:  Copy a matrix from RLN to ROW.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_copyRLN2ROW(Mat *thee, Mat *smat)
{
    int i, count, *IJA;
    LinkA *mt;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == RLN_FORMAT);

    /* initialize the ROW structure */
    IJA = Vmem_malloc( thee->vmem, smat->numR + 1 + smat->numO, sizeof(int) );
    Mat_initStructure( thee, ROW_FORMAT, ISNOT_SYM, smat->numO, IJA, VNULL );

    /* now get the ROW structure of the matrix */
    count = 0;
    thee->IA[0] = 0;
    for (i=0; i<smat->numR; i++) {
        for (mt=(LinkA*)Vset_access(smat->lnkU,i); mt!=VNULL; mt=mt->next) {
            if (mt->idx >= 0) {
                thee->JA[count] = mt->idx;
                thee->A[count]  = mt->val;
                count++;
            }
        }
        thee->IA[i+1] = count;
    }

    /* we are done */
    VASSERT( count == smat->numO );
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyDRC2CLN
 *
 * Purpose:  Copy a matrix from DRC to CLN.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_copyDRC2CLN(Mat *thee, Mat *smat)
{
    int i, j, k, count;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == DRC_FORMAT);

    /* initialize the CLN structure */
    Mat_initStructureLN( thee, CLN_FORMAT, ISNOT_SYM );

    /* now get the CLN structure of the matrix */
    count = 0;
    for (i=0; i<smat->numR; i++) {
        j = i;
        mContrib( thee->lnkL, 0, &count, j, i, smat->diag[i] );
        for (k=smat->IA[i]; k<smat->IA[i+1]; k++) {
            j = smat->JA[k];
            mContrib( thee->lnkL, 0, &count, j, i, smat->offU[k] );
            /* roles of "i" and "j" reversed for lower triangle */
            mContrib( thee->lnkL, 0, &count, i, j, smat->offL[k]);
        }
    }

    /* we are done */
    VASSERT( count == smat->numZ );

    thee->numO = count;
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyROW2CLN
 *
 * Purpose:  Copy a matrix from ROW to CLN.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_copyROW2CLN(Mat *thee, Mat *smat)
{
    int i, j, k, count;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == ROW_FORMAT);

    /* initialize the CLN structure */
    Mat_initStructureLN( thee, CLN_FORMAT, ISNOT_SYM );

    /* now get the CLN structure of the matrix */
    count = 0;
    for (i=0; i<smat->numR; i++) {
        for (k=thee->IA[i]; k<thee->IA[i+1]; k++) {
            j = thee->JA[k];
            mContrib(thee->lnkL, 0, &count, j, i, smat->A[k]);
        }
    }

    /* we are done */
    VASSERT( count == smat->numZ );

    thee->numO = count;
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyCOL2CLN
 *
 * Purpose:  Copy a matrix from COL to CLN.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_copyCOL2CLN(Mat *thee, Mat *smat)
{
    int i, j, k, count;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == COL_FORMAT);

    /* initialize the CLN structure */
    Mat_initStructureLN( thee, CLN_FORMAT, ISNOT_SYM );

    /* now get the CLN structure of the matrix */
    count = 0;
    for (j=0; j<smat->numC; j++) {
        for (k=smat->IA[j]; k<smat->IA[j+1]; k++) {
            i = thee->JA[k];
            mContrib(thee->lnkL, 0, &count, j, i, thee->A[k]);
        }
    }

    /* we are done */
    VASSERT( count == smat->numZ );

    thee->numO = count;
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyCLN2COL
 *
 * Purpose:  Copy a matrix from CLN to COL.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_copyCLN2COL(Mat *thee, Mat *smat)
{
    int j, count, *IJA;
    LinkA *mt;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == CLN_FORMAT);

    /* initialize the COL structure */
    IJA = Vmem_malloc( thee->vmem, smat->numC + 1 + smat->numO, sizeof(int) );
    Mat_initStructure( thee, COL_FORMAT, ISNOT_SYM, smat->numO, IJA, VNULL );

    /* now get the COL structure of the matrix */
    count = 0;
    thee->IA[0] = 0;
    for (j=0; j<smat->numC; j++) {
        for (mt=(LinkA*)Vset_access(smat->lnkL,j);
          mt!=VNULL; mt=mt->next) {
            if (mt->idx >= 0) {
                thee->JA[count] = mt->idx;
                thee->A[count]  = mt->val;
                count++;
            }
        }
        thee->IA[j+1] = count;
    }

    /* we are done */
    VASSERT( count == smat->numZ );
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyCLN2RLN
 *
 * Purpose:  Copy a matrix from CLN to RLN.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyCLN2RLN(Mat *thee, Mat *smat)
{
    int i, j, count;
    LinkA *mt;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == CLN_FORMAT);

    /* initialize the RLN structure */
    Mat_initStructureLN( thee, RLN_FORMAT, ISNOT_SYM );

    /* now get the RLN structure of the matrix */
    count = 0;
    for (j=0; j<smat->numC; j++) {
        for (mt=(LinkA*)Vset_access(smat->lnkL,j);
          mt!=VNULL; mt=mt->next) {
            if (mt->idx >= 0) {
                i = mt->idx;
                mContrib(thee->lnkU, 0, &count, i, j, mt->val);
            }
        }
    }

    /* we are done */
    thee->numO = count;
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyRLN2CLN
 *
 * Purpose:  Copy a matrix from RLN to CLN.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyRLN2CLN(Mat *thee, Mat *smat)
{
    int i, j, count;
    LinkA *mt;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == RLN_FORMAT);

    /* initialize the CLN structure */
    Mat_initStructureLN( thee, CLN_FORMAT, ISNOT_SYM );

    /* now get the CLN structure of the matrix */
    count = 0;
    for (i=0; i<smat->numR; i++) {
        for (mt=(LinkA*)Vset_access(smat->lnkU,i);
             mt!=VNULL; mt=mt->next) {
            if (mt->idx >= 0) {
                j = mt->idx;
                mContrib(thee->lnkL, 0, &count, j, i, mt->val);
            }
        }
    }

    /* we are done */
    thee->numO = count;
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyDRC2XLN
 *
 * Purpose:  Copy a matrix from DRC to XLN.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyDRC2XLN(Mat *thee, Mat *smat)
{
    int i, j, k;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == DRC_FORMAT);

    switch (smat->sym) {
      case IS_SYM:
        /* initialize the XLN structure */
        Mat_initStructureLN( thee, XLN_FORMAT, IS_SYM );

        /* now get the XLN structure of the matrix */
        for (i=0; i<smat->numR; i++) {
            j = i;
            Mat_contribSYMXLN( thee, 0, i, j, smat->diag[i] );
            for(k=smat->IA[i]; k<smat->IA[i+1]; k++) {
                if ( smat->offU[k] != 0 ) {
                    j = smat->JA[k];
                    Mat_contribSYMXLN( thee, 0, i, j, smat->offU[k] );
                }
            }
        }
        break;
      case ISNOT_SYM:
        /* initialize the XLN structure */
        Mat_initStructureLN( thee, XLN_FORMAT, STRUC_SYM );

        /* now get the XLN structure of the matrix */
        for (i=0; i<smat->numR; i++) {
            j = i;
            Mat_contribSSYMXLN( thee, 0, i, j, smat->diag[i] );
            for(k=smat->IA[i]; k<smat->IA[i+1]; k++) {
                j = smat->JA[k];
                if ( (smat->offU[k] != 0) || (smat->offL[k] != 0) ) {
                    Mat_contribSSYMXLN( thee, 0, i, j, smat->offU[k] );
                    Mat_contribSSYMXLN( thee, 0, j, i, smat->offL[k] );
                }
            }
        }
        break;
    default:
        VASSERT(0);
    }

    /* we are done */
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyROW2XLN
 *
 * Purpose:  Copy a matrix from ROW to XLN.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyROW2XLN(Mat *thee, Mat *smat)
{
    int i, j, k;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == ROW_FORMAT);

    /* initialize the XLN structure */
    Mat_initStructureLN( thee, XLN_FORMAT, ISNOT_SYM );

    /* now get the XLN structure of the matrix */
    for (i=0; i<smat->numR; i++) {
        for (k=smat->IA[i]; k<smat->IA[i+1]; k++) {
            j = smat->JA[k];
            Mat_contribNSYMXLN( thee, 0, i, j, smat->A[k] );
        }
    }

    /* we are done */
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyCOL2XLN
 *
 * Purpose:  Copy a matrix from COL to XLN.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyCOL2XLN(Mat *thee, Mat *smat)
{
    int i, j, k;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == COL_FORMAT);

    /* initialize the XLN structure */
    Mat_initStructureLN( thee, XLN_FORMAT, ISNOT_SYM );

    /* now get the XLN structure of the matrix */
    for (j=0; j<smat->numC; j++) {
        for (k=smat->IA[j]; k<smat->IA[j+1]; k++) {
            i = smat->JA[k];
            Mat_contribNSYMXLN( thee, 0, j, i, smat->A[k] );
        }
    }

    /* we are done */
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyRLN2XLN
 *
 * Purpose:  Copy a matrix from RLN to XLN.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyRLN2XLN(Mat *thee, Mat *smat)
{

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == RLN_FORMAT);

    VASSERT( 0 );
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyCLN2XLN
 *
 * Purpose:  Copy a matrix from CLN to XLN.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyCLN2XLN(Mat *thee, Mat *smat)
{

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == CLN_FORMAT);

    VASSERT( 0 );
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyXLN2DRC
 *
 * Purpose:  Copy a matrix from XLN to DRC.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyXLN2DRC(Mat *thee, Mat *smat)
{
    int i, idxmax, count, *IJA;
    LinkRC *mt;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == XLN_FORMAT);

    VASSERT(smat->sym != ISNOT_SYM);

    /* calculate the number of nonzeros before initialization */
    count = 0;
    for (i=0; i<(smat->numR); i++) {
        mt = (LinkRC*) &(((LinkRCS*) (smat->xln))[i]);
        idxmax = smat->numC;
        /* mt->next is the first off diagonal */
        for (mt=mt->next; (mt!=VNULL) && (mt->idx<idxmax); mt=mt->next) {
            count++;
        }
    }

    switch (smat->sym) {
    case IS_SYM:
        /* initialize the DRC structure */
        IJA = Vmem_malloc( thee->vmem, count + 1 + smat->numR, sizeof(int) );
        Mat_initStructure( thee, DRC_FORMAT, IS_SYM, count, IJA, VNULL );

        /* now get the DRC structure of the matrix */
        count = 0;
        for (i=0; i<(smat->numR); i++) {
            mt = (LinkRC*) &(((LinkRCS*) (smat->xln))[i]);
            thee->diag[i] = ((LinkRCS*) mt)->val;
            idxmax = smat->numC;
            /* mt->next is the first off diagonal */
            for (mt=mt->next; (mt!=VNULL) && (mt->idx<idxmax); mt=mt->next) {
                thee->offU[count] = ((LinkRCS*) mt)->val;
                thee->JA[count] = mt->idx;
                count++;
            }
            thee->IA[i+1] = count;
        }
        break;
    case STRUC_SYM:
        /* initialize the DRC structure */
        IJA = Vmem_malloc( thee->vmem, count + 1 + smat->numR, sizeof(int) );
        Mat_initStructure( thee, DRC_FORMAT, ISNOT_SYM, count, IJA, VNULL );

        /* now get the DRC structure of the matrix */
        count = 0;
        for (i=0; i<(smat->numR); i++) {
            mt = (LinkRC*) &(((LinkRCS*) (smat->xln))[i]);
            thee->diag[i] = ((LinkRCS*) mt)->val;
            idxmax = smat->numC;
            /* mt->next is the first off diagonal */
            for (mt=mt->next; (mt!=VNULL) && (mt->idx<idxmax); mt=mt->next) {
                thee->offU[count] = ((LinkRCN*) mt)->val;
                thee->offL[count] = ((LinkRCN*) mt)->valT;
                thee->JA[count] = mt->idx;
                count++;
            }
            thee->IA[i+1] = count;
        }
        break;
    default:
        VASSERT( 0 );
    }

    /* we are done */
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyXLN2ROW
 *
 * Purpose:  Copy a matrix from XLN to ROW.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyXLN2ROW(Mat *thee, Mat *smat)
{
    int i, idxmax, count, *IJA;
    LinkRC *mt;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == XLN_FORMAT);

    VASSERT(smat->sym == ISNOT_SYM);

    /* calculate the number of nonzeros before initialization */
    count = 0;
    for (i=0; i<(smat->numR); i++) {
        mt = ((LinkRC**) (smat->xln))[i];
        idxmax = smat->numC;
        for (/* no-op */; (mt!=VNULL) && (mt->idx<idxmax); mt=mt->next) {
            count++;
        }
    }

    /* initialize the ROW structure */
    IJA = Vmem_malloc( thee->vmem, count + 1 + smat->numR, sizeof(int) );
    Mat_initStructure( thee, ROW_FORMAT, IS_SYM, count, IJA, VNULL );

    /* now get the ROW structure of the matrix */
    count = 0;
    for (i=0; i<(smat->numR); i++) {
        mt = ((LinkRC**) (smat->xln))[i];
        idxmax = smat->numC;
        for (/* no-op */; (mt!=VNULL) && (mt->idx<idxmax); mt=mt->next) {
            thee->A[count] = ((LinkRCS*) mt)->val;
            thee->JA[count] = mt->idx;
            count++;
        }
        thee->IA[i+1] = count;
    }

    /* we are done */
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyXLN2COL
 *
 * Purpose:  Copy a matrix from XLN to COL.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyXLN2COL(Mat *thee, Mat *smat)
{
    int i, j, idxmax, count, *IJA;
    LinkRC *mt;

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == XLN_FORMAT);

    VASSERT(smat->sym == ISNOT_SYM);

    /* calculate the number of nonzeros before initialization */
    count = 0;
    for (i=0; i<(smat->numR); i++) {
        mt = ((LinkRC**) (smat->xln))[i];
        idxmax = smat->numC;
        for (/* no-op */; (mt!=VNULL) && (mt->idx<idxmax); mt=mt->next) {
            count++;
        }
    }

    /* initialize the COL structure */
    IJA = Vmem_malloc( thee->vmem, count + 1 + smat->numC, sizeof(int) );
    Mat_initStructure( thee, COL_FORMAT, IS_SYM, count, IJA, VNULL );

    /* now get the COL structure of the matrix */
    count = 0;
    for (j=0; j<(smat->numC); j++) {
        mt = ((LinkRC**) (smat->xlnt))[j];
        idxmax = smat->numC;
        for (/* no-op */; (mt!=VNULL) && (mt->idx<idxmax); mt=mt->next) {
            thee->A[count] = ((LinkRCS*) mt)->val;
            thee->JA[count] = mt->idxT;
            count++;
        }
        thee->IA[j+1] = count;
    }

    /* we are done */
    thee->state = ASSEMBLED_STATE;
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyXLN2RLN
 *
 * Purpose:  Copy a matrix from XLN to RLN.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyXLN2RLN(Mat *thee, Mat *smat)
{

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == XLN_FORMAT);

    VASSERT( 0 );
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyXLN2CLN
 *
 * Purpose:  Copy a matrix from XLN to CLN.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copyXLN2CLN(Mat *thee, Mat *smat)
{

    VASSERT(thee->numR == smat->numR);
    VASSERT(thee->numC == smat->numC);

    VASSERT(thee->state == NULL_STATE);
    VASSERT(thee->format == ZERO_FORMAT);
    VASSERT(smat->format == XLN_FORMAT);

    VASSERT( 0 );
}

/*
 * ***************************************************************************
 * Routine:  Mat_squeezeBRC
 *
 * Purpose:  Remove the boundary rows or columns from a matrix.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_squeezeBRC(Mat *thee, int key)
{
    int i, j, k, *IA, *JA, numR, numC, numO, count, ibase;
    int ic, jc, kc, kbrc, cnumR, cnumC, cibase;
    double *A;

    VASSERT(thee->format == ROW_FORMAT);

    /* do nothing if it is already compressed */
    if ( (key == 0 && thee->numBR == 0) || (key == 1 && thee->numBC == 0) ) {
	return;
    }

    /* hand off pointers to the uncompressed arrays */
    IA = thee->IA;
    JA = thee->JA;
    A = thee->A;
    numC = thee->numC;
    numR = thee->numR;
    numO = thee->numO;

    /* offset row indices in the case of implicit identity */
    ibase = (thee->impl == IS_IMPL) ? numC : 0;

    /* determine the dimensions of the compressed matrix */
    count = 0;
    if (key == 0) {
	cnumC = numC;

	cibase = 0;
	kbrc = 0;
	for (i=0; i<ibase; i++) {
	    if ( kbrc < thee->numBR && thee->BR[kbrc] == i ) {
		kbrc++;
	    } else {
		cibase++;
	    }
	}
	for (i=0; i<numR; i++) {
	    if ( kbrc < thee->numBR && thee->BR[kbrc] == i ) {
		kbrc++;
	    } else {
		count += IA[i+1] - IA[i];
		cnumR++;
	    }
	}

	cnumR = numR - (thee->numBR - cibase);
    } else if (key == 1) {
	cnumR = numR;
	cibase = ibase;

	for (i=0; i<numR; i++) {
	    kbrc = 0;
	    for(k=IA[i]; k<IA[i+1]; k++) {
		j = JA[k];
		while ( kbrc < thee->numBC && thee->BC[kbrc] < j ) {
		    kbrc++;
		}
		if ( kbrc < thee->numBC && thee->BC[kbrc] == j ) {
		    kbrc++;
		} else {
		    count++;
		}
	    }
	}

	cnumC = numC - (thee->numBC);
    } else {
	VASSERT(0);
    }

    /* now resize the matrix */
    thee->numR = cnumR;
    thee->numC = cnumC;

    /* create the compressed IJA and A arrays */
    thee->IJA = Vmem_malloc(thee->vmem, cnumR + 1 + count, sizeof(int) );
    thee->IA = thee->IJA;
    thee->JA = thee->IJA + cnumR + 1;

    thee->A = Vmem_malloc(thee->vmem, count, sizeof(double) );
    thee->offU = thee->A;

    thee->numO = count;
    thee->numA = count;
    thee->numZ = count;

    /* now copy the old arrays into the new arrays */
    if (key == 0) {
	kbrc=0;
	for (i=0; i<ibase; i++) {
	    if ( kbrc < thee->numBR && thee->BR[kbrc] == i ) {
		kbrc++;
	    }
	}
	ic = 0;
	thee->IA[0] = 0;
	kc = 0;
	for (i=0; i<numR; i++) {
	    if ( kbrc < thee->numBR && thee->BR[kbrc] == i ) {
		kbrc++;
	    } else {
		for(k=IA[i]; k<IA[i+1]; k++) {
		    thee->A[kc] = A[k];
		    thee->JA[kc] = JA[k];
		    kc++;
		}
		thee->IA[ic+1] = kc;
		ic++;
	    }
	}
	VASSERT(kc == count);
    } else if (key == 1) {
	thee->IA[0] = 0;
	kc = 0;
	for (i=0; i<numR; i++) {
	    kbrc = 0;
	    for(k=IA[i]; k<IA[i+1]; k++) {
		j = JA[k];
		while ( kbrc < thee->numBC && thee->BC[kbrc] < j ) {
		    kbrc++;
		}
		if ( kbrc < thee->numBC && thee->BC[kbrc] == j ) {
		    kbrc++;
		} else {
		    thee->A[kc] = A[k];
		    thee->JA[kc] = JA[k] - kbrc;
		    kc++;
		}
	    }
	    thee->IA[i+1] = kc;
	}
	VASSERT(kc == count);
    }

    /* now kill the original matrix structure */
    Vmem_free( thee->vmem, numR + 1 + numO, sizeof(int),
	       (void **)&(IA) );
    Vmem_free( thee->vmem, numO, sizeof(double),
	       (void **)&(A) );

    /* kill the boundary row or column arrays */
    if (key == 0) {
	if ( thee->numBR > 0 ) {
	    Vmem_free( thee->vmem, thee->numBR, sizeof(int),
		       (void **)&(thee->BR) );
	    thee->numBR = 0;
	}
    } else if (key == 1) {
	if ( thee->numBC > 0 ) {
	    Vmem_free( thee->vmem, thee->numBC, sizeof(int),
		       (void **)&(thee->BC) );
	    thee->numBC = 0;
	}
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_copy2
 *
 * Purpose:  Raw copy of the nonzeros of X into Y.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_copy2(Mat *Y, Mat *X)
{
  int i, size, numR, numC, numO;
  MATformat frmt;
  MATsym sym;

  VASSERT( Mat_state(Y) >= ZERO_STATE );
  VASSERT( Mat_state(X) >= ASSEMBLED_STATE );

  frmt = Mat_format(X);
  numC = Mat_numC(X);
  numR = Mat_numR(X);
  sym  = Mat_sym(X);
  numO = Mat_numO(X);

  VASSERT( Mat_numR(Y) == numR );
  VASSERT( Mat_numC(Y) == numC );
  VASSERT( Mat_format(Y) == frmt );
  VASSERT( Mat_sym(Y) == sym );
  VASSERT( Mat_numO(Y) == numO );
  
  switch (frmt) {

      case DRC_FORMAT:
          VASSERT( numR == numC );            /* is square block? */
          if ( sym == ISNOT_SYM ) {
              size = numR + 2*numO;                /* nonsymmetry */
          } else if ( sym == IS_SYM ) {
              size = numR + numO;                     /* symmetry */
          } else {
              VASSERT( 0 );    /* enforce nonsymmetry OR symmetry */
          }
          break;
      case ROW_FORMAT:
          if ( sym == ISNOT_SYM ) {
              size = numO;                         /* nonsymmetry */
          } else {
              VASSERT( 0 );                /* enforce nonsymmetry */
          }
          break;
      case COL_FORMAT:
          if ( sym == ISNOT_SYM ) {
              size = numO;                         /* nonsymmetry */
          } else {
              VASSERT( 0 );                /* enforce nonsymmetry */
          }
          break;
      default:
          /* All other cases are currently unsupported */
          VASSERT( 0 );
      }

  /* Perform vector axpy on the raw data */
  for (i=0; i<size; i++)
      Y->A[i] = X->A[i];

}

/*
 * ***************************************************************************
 * Routine:  Mat_axpy
 *
 * Purpose:  scalar times a Mat plus a Mat:  Y += val*X.
 *
 * Notes:    The function of this routine can be controlled using "key"
 *
 *           (key==0) X and Y have the EXACT SAME nonzero structure (nZ).
 *                    Very fast with no checking or temporary matrices
 *
 *           (key==1) The nZ of Y is a SUBSET of the nZ of X.
 *                    Still fast but requires a few extra checks.
 *
 *           (key==2) X and Y have arbitrary nZ structure.
 *                    Slowest requiring creation of a temporary link list.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_axpy(Mat *Y, Mat *X, double val, int key)
{
  int i, size, numR, numC, numO;
  MATformat frmt;
  MATsym sym;

  VASSERT( Mat_state(Y) >= ZERO_STATE );
  VASSERT( Mat_state(X) >= ASSEMBLED_STATE );

  frmt = Mat_format(X);
  numC = Mat_numC(X);
  numR = Mat_numR(X);
  sym  = Mat_sym(X);
  numO = Mat_numO(X);

  if ( key == 0 ) { /* Y and X have the SAME NONZERO STRUCTURE */

      VASSERT( Mat_numR(Y) == numR );
      VASSERT( Mat_numC(Y) == numC );
      VASSERT( Mat_format(Y) == frmt );
      VASSERT( Mat_sym(Y) == sym );
      VASSERT( Mat_numO(Y) == numO );
  
      switch (frmt) {

      case DRC_FORMAT:
          VASSERT( numR == numC );            /* is square block? */
          if ( sym == ISNOT_SYM ) {
              size = numR + 2*numO;                /* nonsymmetry */
          } else if ( sym == IS_SYM ) {
              size = numR + numO;                     /* symmetry */
          } else {
              VASSERT( 0 );    /* enforce nonsymmetry OR symmetry */
          }
          break;
      case ROW_FORMAT:
          if ( sym == ISNOT_SYM ) {
              size = numO;                         /* nonsymmetry */
          } else {
              VASSERT( 0 );                /* enforce nonsymmetry */
          }
          break;
      case COL_FORMAT:
          if ( sym == ISNOT_SYM ) {
              size = numO;                         /* nonsymmetry */
          } else {
              VASSERT( 0 );                /* enforce nonsymmetry */
          }
          break;
      default:
          /* All other cases are currently unsupported */
          VASSERT( 0 );
      }

      /* Perform vector axpy on the raw data */
      for (i=0; i<size; i++)
          Y->A[i] += val*X->A[i];

  } else if ( key == 1 ) {

      /* All other keys are currently unsupported */
      VASSERT( 0 );

  } else if ( key == 2 ) {

      /* All other keys are currently unsupported */
      VASSERT( 0 );

  } else {
      /* All other keys are currently unsupported */
      VASSERT( 0 );

  }

}

