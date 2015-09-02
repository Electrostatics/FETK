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
 * rcsid="$Id: bmat.c,v 1.44 2010/08/12 05:18:24 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     bmat.c
 *
 * Purpose:  Class Bmat: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "bmat_p.h"

VEMBED(rcsid="$Id: bmat.c,v 1.44 2010/08/12 05:18:24 fetk Exp $")

/*
 * ***************************************************************************
 * Class Bmat: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_BAM)

#endif /* if !defined(VINLINE_BAM) */
/*
 * ***************************************************************************
 * Class Bmat: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Bmat_ctor
 *
 * Purpose:  The block sparse matrix constructor.
 *
 * Notes:    This constructor only does minimal initialization of a Bmat
 *           object after creating the object itself; it doesn't create
 *           any storage for either the integer structure arrays or the
 *           nonzero storage arrays.
 *
 *           This constructor only fixes the number of blocks and the
 *           numbers of rows and columns in each block; the nonzero
 *           structure is not set yet.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Bmat* Bmat_ctor(Vmem *vmem, const char *name,
    int pnumB, int pnumR[MAXV], int pnumC[MAXV],
    MATmirror pmirror[MAXV][MAXV])
{
    int p,q;
    char bname[15];
    Bmat *thee = VNULL;

    VDEBUGIO("Bmat_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Bmat) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Bmat" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    strncpy(thee->name, name, 10);
    thee->coarse = VNULL;
    thee->fine   = VNULL;
    thee->numB   = pnumB;
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            thee->mirror[p][q] = pmirror[p][q];
            thee->AD[p][q]     = VNULL;
        }
    }

    /* create upper-triangular blocks before the lower-triangular blocks */
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            if ( !thee->mirror[p][q] ) {
                sprintf(bname, "%s_%d%d", thee->name, p, q);
                thee->AD[p][q] = Mat_ctor(thee->vmem,bname,pnumR[p],pnumC[q]);
            } else { /* ( thee->mirror[p][q] ) */
                /* first make sure that the mirror of this guy exists! */
                VASSERT( !thee->mirror[q][p] );
                VASSERT( thee->AD[q][p] != VNULL );
                thee->AD[p][q] = thee->AD[q][p];
            }
        }
    }

    VDEBUGIO("..done.\n");

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_dtor
 *
 * Purpose:  The block sparse matrix destructor.
 *
 * Notes:    This destructor does the reverse of Bmat_ctor, and if 
 *           necessary first reverses Bmat_initStructure
 *           (or Bmat_copyStructure).  I.e., if necessary,
 *           it first frees the large integer and real arrays created by
 *           Bmat_initStructure or Bmat_copyStructure, and then frees the
 *           Bmat object itself at the last moment.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_dtor(Bmat **thee)
{
    int p, q;

    /* VASSERT( (*thee) != VNULL ); */
    if ((*thee) != VNULL) {

        /* first free any coarse guy */
        if ( (*thee)->coarse != VNULL ) {
            Bmat_dtor( &((*thee)->coarse) );
        }

        /* next free the large integer and real nonzero structure */
        Bmat_killStructure(*thee);

        /* kill the submatrices themselves */
        Mat_dtor( &((*thee)->AG) );
        for (p=0; p<(*thee)->numB; p++) {
            for (q=0; q<(*thee)->numB; q++) {
                if ( !(*thee)->mirror[p][q] ) {
                    Mat_dtor( &((*thee)->AD[p][q]) );
                }
            }
        }

        /* now kill the object itself */
        VDEBUGIO("Bmat_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Bmat), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_initStructure
 *
 * Purpose:  Initialize the nonzero structure given structure information.
 *
 * Notes:    This routine actually does the storage creation for both the
 *           integer structure information arrays and the nonzero value
 *           arrays.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_initStructure(Bmat *thee,
    MATformat pfrmt[MAXV][MAXV], MATsym psym[MAXV][MAXV],
    int pnumO[MAXV][MAXV], int *IJA[MAXV][MAXV])
{
    int p, q;

    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            if ( !thee->mirror[p][q] ) {
                Mat_initStructure(thee->AD[p][q],
                    pfrmt[p][q], psym[p][q], pnumO[p][q], IJA[p][q], VNULL);
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_copyStructure
 *
 * Purpose:  Copy the nonzero structure from an input model.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_copyStructure(Bmat *thee, Bmat *model)
{
    int p, q;

    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            VASSERT( thee->mirror[p][q] == model->mirror[p][q] );
            if ( !thee->mirror[p][q] ) {
                Mat_copyStructure(thee->AD[p][q], model->AD[p][q]);
            } else {
                VASSERT( !thee->mirror[q][p] );
                thee->AD[p][q] = thee->AD[q][p]; 
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_killStructure
 *
 * Purpose:  Kill the nonzero structure.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_killStructure(Bmat *thee)
{
    int p, q;

    Mat_killStructure(thee->AG);
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            if ( !thee->mirror[p][q] ) {
                Mat_killStructure(thee->AD[p][q]);
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numB
 *
 * Purpose:  Return the number of blocks.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numB(Bmat *thee)
{
    return thee->numB;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numR
 *
 * Purpose:  Return the number of rows.
 *
 * Notes:    For a mirror block, AD[p][q] is a pointer to the mirror,
 *           AD[q][p], and hence, the dimensions must be transposed.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numR(Bmat *thee, int p, int q)
{
    if( !(thee->mirror[p][q]) ) {
        return Mat_numR( thee->AD[p][q] );
    } else {
        return Mat_numC( thee->AD[q][p] );
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numC
 *
 * Purpose:  Return the number of columns.
 *
 * Notes:    For a mirror block, AD[p][q] is a pointer to the mirror,
 *           AD[q][p], and hence, the dimensions must be transposed.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numC(Bmat *thee, int p, int q)
{
    if( !(thee->mirror[p][q]) ) {
        return Mat_numC( thee->AD[p][q] );
    } else {
        return Mat_numR( thee->AD[q][p] );
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numA
 *
 * Purpose:  Return the number of nonzeros we actually store in a block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numA(Bmat *thee, int p, int q)
{
    return Mat_numA( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numO
 *
 * Purpose:  Return the number of nonzeros we actually store in a block
 *           which are actually in the strict upper-triangle of the
 *           block (DRC only).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numO(Bmat *thee, int p, int q)
{
    return Mat_numO( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numZ
 *
 * Purpose:  Return the number of nonzeros we WOULD actually store in a block
 *           if we ignored symmetry and stored everything.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numZ(Bmat *thee, int p, int q)
{
    return Mat_numZ( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numRT
 *
 * Purpose:  Return the total number of rows.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numRT(Bmat *thee)
{
    int p, numRT;

    numRT = 0;
    for (p=0; p<thee->numB; p++) {
        numRT += Bmat_numR(thee,p,p);
    }

    return numRT;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numCT
 *
 * Purpose:  Return the total number of columns.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numCT(Bmat *thee)
{
    int q, numCT;

    numCT = 0;
    for (q=0; q<thee->numB; q++) {
        numCT += Bmat_numC(thee,q,q);
    }

    return numCT;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numAT
 *
 * Purpose:  Return the total number of nonzeros we are actually storing.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numAT(Bmat *thee)
{
    int p, q, numAT;

    numAT = 0;
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            numAT += Bmat_numA(thee,p,q);
        }
    }

    return numAT;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numOT
 *
 * Purpose:  Return the total number of nonzeros we are actually storing
 *           which are located in the strict upper-triangle.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numOT(Bmat *thee)
{
    int p, q, numOT;

    numOT = 0;
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            numOT += Bmat_numO(thee,p,q);
        }
    }

    return numOT;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_numZT
 *
 * Purpose:  Return the total number of nonzeros we WOULD be storing if we
 *           ignored all symmetry in all blocks and stored everything.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_numZT(Bmat *thee)
{
    int p, q, numZT;

    numZT = 0;
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            numZT += Bmat_numZ(thee,p,q);
        }
    }

    return numZT;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_format
 *
 * Purpose:  Return the format of the block.
 *
 * Notes:    For a mirror block, AD[p][q] is a pointer to the mirror,
 *           AD[q][p], and hence, the format must be transposed.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC MATformat Bmat_format(Bmat *thee, int p, int q)
{
    if( thee->mirror[p][q] ) {  /* Is it a mirror block ? */
        switch ( Mat_format( thee->AD[q][p] ) ) {
          case ZERO_FORMAT:
            return ZERO_FORMAT;
            break;
          case ROW_FORMAT:
            return COL_FORMAT;
            break;
          case COL_FORMAT:
            return ROW_FORMAT;
            break;
          default:
            /* Mirrors of all other cases currently unsupported */
            VASSERT( 0 );
       }
    }

    return Mat_format( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_sym
 *
 * Purpose:  Return the symmetry of the block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC MATsym Bmat_sym(Bmat *thee, int p, int q)
{
    return Mat_sym( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_state
 *
 * Purpose:  Return the state of the block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC MATstate Bmat_state(Bmat *thee, int p, int q)
{
    return Mat_state( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_impl
 *
 * Purpose:  Return the implicitness of the block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC MATimpl Bmat_impl(Bmat *thee, int p, int q)
{
    return Mat_impl( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_mirror
 *
 * Purpose:  Return the mirror-ness of the block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC MATmirror Bmat_mirror(Bmat *thee, int p, int q)
{
    return thee->mirror[p][q];
}

/*
 * ***************************************************************************
 * Routine:  Bmat_sizeA
 *
 * Purpose:  Return the number of nonzeros in all blocks.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_sizeA(Bmat *thee)
{
    int p,q,size = 0;
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            size += Mat_sizeA( thee->AD[p][q] );
        }
    }
    return size;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_sizeIJA
 *
 * Purpose:  Return the numer of integer storage locations used.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_sizeIJA(Bmat *thee)
{
    int p,q,size = 0;

    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            size += Mat_sizeIJA( thee->AD[p][q] );
        }
    }

    return size;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_IJA
 *
 * Purpose:  Return the integer structure IJA.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int *Bmat_IJA(Bmat *thee, int p, int q)
{
    return Mat_IJA( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_IA
 *
 * Purpose:  Return the integer structure IA.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int *Bmat_IA(Bmat *thee, int p, int q)
{
    return Mat_IA( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_JA
 *
 * Purpose:  Return the integer structure JA.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int *Bmat_JA(Bmat *thee, int p, int q)
{
    return Mat_JA( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_A
 *
 * Purpose:  Return the real structure A.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double *Bmat_A(Bmat *thee, int p, int q)
{
    return Mat_A( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_diag
 *
 * Purpose:  Return the diagonal of A (DRC only).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double *Bmat_diag(Bmat *thee, int p, int q)
{
    return Mat_diag( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_offU
 *
 * Purpose:  Return the strict upper triangle of A (DRC only).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double *Bmat_offU(Bmat *thee, int p, int q)
{
    return Mat_offU( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_offL
 *
 * Purpose:  Return the strict lower triangle of A (DRC only).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double *Bmat_offL(Bmat *thee, int p, int q)
{
    return Mat_offL( thee->AD[p][q] );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_print
 *
 * Purpose:  Print the prolongation matrix blocks.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_print(Bmat *thee)
{
    int p,q;

    for (p=0; p<thee->numB; p++) {  
        for (q=0; q<thee->numB; q++) {  
            Mat_print(thee->AD[p][q]);
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_printSp
 *
 * Purpose:  Print the prolongation matrix in MATLAB sparse form.
 *
 * Notes:    flag==0 ==> write
 *           flag==1 ==> append
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_printSp(Bmat *thee, char *fname, int pflag)
{
    char rn[80];
    FILE *fp;
    int p, q, numRT, numCT;

    strncpy(rn,"Bmat_printSp:",80);

    numRT = Bmat_numRT( thee );
    numCT = Bmat_numCT( thee );

    if (pflag == 0) {
        fp=fopen(fname,"w");
    } else if (pflag == 1) {
        fp=fopen(fname,"a");
    } else {
        fp=VNULL;
    }

    if (fp==VNULL) {
        Vnm_print(2, "%s problem opening file <%s>\n", rn, fname);
        return;
    }

    /* print the matrix in matlab sparse format */
    fprintf(fp,"%% %s matrix <%s> [dim=(%dx%d)]\n",
        rn, thee->name, numRT, numCT);
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp, "fprintf('Defining the blocks of %s..');\n\n", thee->name);
    fclose(fp);

    for (p=0; p<thee->numB; p++) {  
        for (q=0; q<thee->numB; q++) { 
            if( !(thee->mirror[p][q]) ) { 
                Mat_printSp(thee->AD[p][q],fname,1);
            }
        }
    }

    fp=fopen(fname,"a");

    if (fp==VNULL) {
        Vnm_print(2, "%s problem opening file <%s>\n", rn, fname);
        return;
    }

    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%% Matlab code to generate the block matrix.\n");
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%s = [\n",thee->name);
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            if( !thee->mirror[p][q] ) {
                fprintf(fp,"  %s ",(thee->AD[p][q])->name);
            } else {
                fprintf(fp,"  %s'",(thee->AD[q][p])->name);
            }
        }
        fprintf(fp,"\n");
    }
    fprintf(fp, "];\n\n");
    fprintf(fp,"%% ----------------------------------------\n");

    /* close file and return */
    fclose(fp);
}

/*
 * ***************************************************************************
 * Routine:  Bmat_printNoD
 *
 * Purpose:  Print the matrix as a DENSE matrix in MATLAB format,
 *           but first zero out any rows/cols corresponding to
 *           Dirichlet boundary points.
 *
 * Notes:    This routine is useful for e.g. checking that Galerkin
 *           conditions hold for stiffness matrices.  Removing the
 *           dirichlet equations is crucial; otherwise the Galerkin
 *           condition cannot hold.  Note that the matrix (and the
 *           Galerkin coarse matrix) are then of course singular.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_printNoD(Bmat *thee)
{
    int p,q;

    for (p=0; p<thee->numB; p++) {  
        for (q=0; q<thee->numB; q++) {  
            Mat_printNoD(thee->AD[p][q]);
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_printSpNoD
 *
 * Purpose:  Print the matrix as a SPARSE matrix in MATLAB format,
 *           but first zero out any rows/cols corresponding to
 *           Dirichlet boundary points.
 *
 * Notes:    This routine is useful for e.g. checking that Galerkin
 *           conditions hold for stiffness matrices.  Removing the
 *           dirichlet equations is crucial; otherwise the Galerkin
 *           condition cannot hold.  Note that the matrix (and the
 *           Galerkin coarse matrix) are then of course singular.
 *
 *           flag==0 ==> write
 *           flag==1 ==> append
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_printSpNoD(Bmat *thee, char *fname, int pflag)
{
    char rn[80];
    FILE *fp;
    int p, q, numRT, numCT;

    strncpy(rn,"Bmat_printSpNoD:",80);

    numRT = Bmat_numRT( thee );
    numCT = Bmat_numCT( thee );

    if (pflag == 0) {
        fp=fopen(fname,"w");
    } else if (pflag == 1) {
        fp=fopen(fname,"a");
    } else {
        fp=VNULL;
    }

    if (fp==VNULL) {
        Vnm_print(2, "%s problem opening file <%s>\n", rn, fname);
        return;
    }

    /* print the matrix in matlab sparse format */
    fprintf(fp,"%% %s matrix <%s> [dim=(%dx%d)]\n",
        rn, thee->name, numRT, numCT);
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp, "fprintf('Defining the blocks of %s..');\n\n", thee->name);
    fclose(fp);

    for (p=0; p<thee->numB; p++) {  
        for (q=0; q<thee->numB; q++) {  
            Mat_printSpNoD(thee->AD[p][q],fname,1);
        }
    }

    fp=fopen(fname,"a");

    if (fp==VNULL) {
        Vnm_print(2, "%s problem opening file <%s>\n", rn, fname);
        return;
    }

    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%% Matlab code to generate the block matrix.\n");
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%s = [\n",thee->name);
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            fprintf(fp,"  %s",(thee->AD[p][q])->name);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp, "];\n\n");
    fprintf(fp,"%% ----------------------------------------\n");

    /* close file and return */
    fclose(fp);

}

/*
 * ***************************************************************************
 * Routine:  Bmat_zero
 *
 * Purpose:  Clear the floating point storage for the sparse matrix.
 *           Also clear any sparse factorization storage.
 *
 * Notes:    This is basically done in preparation for an accumulation as
 *           part of a matrix assembly, and before a new sparse factorization.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_zero(Bmat *thee)
{
    int p, q;

    /* zero out all of the floating point storage */
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {
            if ( !thee->mirror[p][q] ) {
                Mat_zero(thee->AD[p][q]);
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_diri
 *
 * Purpose:  Setup the dirichlet equations.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_diri(Bmat *thee)
{
    int p;

    /* stick identity on the boundary rows/cols of diagonal blocks */
    for (p=0; p<thee->numB; p++) {
        Mat_diagBRC(thee->AD[p][p]);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_set
 *
 * Purpose:  Set the (i,j)-th entry of the (p,q)-th block to <val>
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_set(Bmat *thee, int p, int q, int i, int j, double val)
{
    if ( !thee->mirror[p][q] ) {
        Mat_set(thee->AD[p][q],i,j,val);
    } else {
        /* we should NEVER get to here */
        VASSERT(0);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_addTo
 *
 * Purpose:  Contribute <val> to the (i,j)-th entry of the (p,q)-th block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_addTo(Bmat *thee, int p, int q, int i, int j, double val)
{
    if ( !thee->mirror[p][q] ) {
        Mat_addTo(thee->AD[p][q],i,j,val);
    } else {
        /* we should NEVER get to here */
        VASSERT(0);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_galerkin
 *
 * Purpose:  Enforce the Galerkin conditions algebraically.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_galerkin(Bmat *thee, Bmat *rmat, Bmat *amat, Bmat *pmat)
{
    int p, q, numR, numC;
    char bname[15];

#if 0
    Vnm_tstart(30, "triple matrix product");
    Vnm_print(0,"Bmat_galerkin: triple matrix product..");
#endif

    /* go through blocks and form B=r*A*p */
    for (p=0; p<thee->numB; p++) {
        for (q=0; q<thee->numB; q++) {

            /* form the product:  B=R*A*P */
            if ( !Bmat_mirror(thee,p,q) ) {

                /* hold onto row/col sizes */
                numR = Bmat_numR(thee,p,q);
                numC = Bmat_numR(thee,p,q);

                /* reinitialize the block */
                Mat_dtor(&thee->AD[p][q]);
                sprintf(bname, "%s_%d%d", thee->name, p, q);
                thee->AD[p][q] = Mat_ctor(thee->vmem, bname, numR, numC);

                /* don't forget the possible mirror!!! */
                if ( Bmat_mirror(thee,q,p) ) {
                    thee->AD[q][p] = thee->AD[p][q];
                }

                /* now form the triple matrix product */
                Mat_galerkin(thee->AD[p][q],
                    rmat->AD[p][p], amat->AD[p][q], pmat->AD[q][q]);
            }
        }
    }

    /*
     * Now, insert dirichlet identity equations due to singular P.
     *
     * (The new matrix is singular otherwise, since the prolongation matrix
     * has zero COLUMNS at coarse dirichlet points and zero ROWS at fine
     * dirichlet points, with the reverse situation for the restriction.)
     */
    Bmat_diri( thee );

    /* Set the coarse and fine pointers within the matrices. */
    thee->fine = amat;
    amat->coarse = thee;

#if 0
    Vnm_print(0,"..done.\n");
    Vnm_tstop(30, "triple matrix product");
#endif
}

/*
 * ***************************************************************************
 * Routine:  Bmat_sluDirect
 *
 * Purpose:  Make a decision about whether or not a sparse direct solver
 *           should be used in place of an iterative solver, based on the
 *           size of the system.
 *
 * Notes:    This is obviously heuristic in nature; in general the cutoff
 *           size where iterative methods start to win is smaller in 3D.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_sluDirect(Bmat *thee)
{
    int ival = 0;
    /* the decision about when sparse direct will be the best solver */
    if ( Bmat_numRT(thee) < SPARSE_CUTOFF ) ival = 1;
    return ival;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_sluCreate
 *
 * Purpose:  Create the global matrix from the blocks in the modified
 *           ROW or COL storage format.  This is useful for preparing a
 *           single global matrix for input to e.g. a sparse direct solver.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_sluCreate(Bmat *thee)
{
    int i, j, k, p, q, count, istart, jstart;
    Vset  *lnk;
    LinkA *mt;
    Mat *blk, *gmat;
    MATmirror mirror;
    MATformat format;
    double *diag, *offU, *offL;

    /* initialize the global matrix datastructure */
    gmat = Mat_ctor(thee->vmem, "AG", Bmat_numRT(thee), Bmat_numCT(thee));
    Mat_initStructure(gmat, SLU_FORMAT, ISNOT_SYM, Bmat_numZT(thee),
        VNULL, VNULL);

    /* initialize/clear the dynamic array */
    lnk = Vset_ctor( thee->vmem, "lnk", sizeof( LinkA ), VMAX_OBJECTS, 0 );
    Vset_reset( lnk );

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
        for (q=0; q<thee->numB; q++) {

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
                        /* still in "istart/jstart" block; */
                        /* but roles of "i" and "j" are reversed */
                        mContrib(lnk,0,&count,jstart+i,istart+j,offU[k]);
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

    /* now create the matrix from the temporary structure */
    count = 0;
    gmat->IA[0] = 0;
    for (i=0; i<Bmat_numRT(thee); i++) {
        for (mt=(LinkA*)Vset_access(lnk,i); mt!=VNULL; mt=mt->next) {
            if (mt->idx >= 0) {
                gmat->JA[count] = mt->idx;
                gmat->A[count]  = mt->val;
                count++;
            }
        }
        gmat->IA[i+1] = count;
    }
    thee->AG = gmat;

    /* clear/destroy the dynamic array */
    Vset_reset( lnk );
    Vset_dtor( &lnk );
}

/*
 * ***************************************************************************
 * Routine:  Bmat_sluFactor
 *
 * Purpose:  Create the sparse LU factors for global matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_sluFactor(Bmat *thee)
{
    if ( thee->AG == VNULL ) {
        Bmat_sluCreate(thee);
    }

    if ( Mat_state(thee->AG) == FACTORED_STATE ) {
        return 1;
    } else {
        return Mat_sluFactor(thee->AG);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_sluSolve
 *
 * Purpose:  Forward/backward solve using sparse LU factors of global matrix.
 *
 * Notes:    This requires that Bmat_sluFactor has been previously called.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bmat_sluSolve(Bmat *thee, int key, double *f, double *u)
{
    return Mat_sluSolve(thee->AG, key, f, u);
}

/*
 * ***************************************************************************
 * Routine:  Bmat_sluDestroy
 *
 * Purpose:  Destroy the sparse LU factors for the system matrix.
 *
 * Notes:    This frees our <ia,ja,a> storage, and also the internal
 *           storage that was malloc'd by the sparse direct library.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_sluDestroy(Bmat *thee)
{
    Mat_sluDestroy(thee->AG);
}

/*
 * ***************************************************************************
 * Routine:  Bmat_memChk
 *
 * Purpose:  Print the exact current malloc usage.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bmat_memChk(Bmat *thee)
{
    if (thee->iMadeVmem) Vmem_print(thee->vmem);
}

/*
 * ***************************************************************************
 * Routine:  Bmat_clone
 *
 * Purpose:  Construct a clone of a Bmat with the same structure.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC Bmat *Bmat_clone(Vmem *vmem, char *name, Bmat *X)
{

  int p, q, numR[MAXV], numC[MAXV];
  int numB;
  MATmirror pmir[MAXV][MAXV];

  numB = Bmat_numB(X);

  for (p=0; p<numB; p++) {
      numR[p] = Bmat_numR( X, p, p );
      numC[p] = Bmat_numC( X, p, p );
      for (q=0; q<numB; q++) {
          pmir[p][q] = Bmat_mirror( X, p, q );
      }
  }

  return Bmat_ctor(vmem, name, numB, numR, numC, pmir );

}

/*
 * ***************************************************************************
 * Routine:  Bmat_copy
 *
 * Purpose:  Copy a block matrix.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bmat_copy(Bmat *Y, Bmat *X)
{

  int p, q;
  int numB;

  numB = Bmat_numB(X);

  VASSERT( Bmat_numB(Y)  == numB );

  for (p=0; p<numB; p++) {
      for (q=0; q<numB; q++) {
          if ( !Y->mirror[p][q] ) {
              Mat_copy( Y->AD[p][q], X->AD[p][q] );
          } else {
              VASSERT( !Y->mirror[q][p] );
              VASSERT( Y->AD[q][p] != VNULL );
              VASSERT( Y->AD[p][q] == VNULL );
              Y->AD[p][q] = Y->AD[q][p];
          }
      }
  }

}

/*
 * ***************************************************************************
 * Routine:  Bmat_squeezeBRC
 *
 * Purpose:  Remove the boundary rows or columns from a block matrix.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bmat_squeezeBRC(Bmat *thee, int key)
{

  int p, q;
  int numB;

  numB = Bmat_numB(thee);

  /* this only makes sense for prolongation matrices */

  for (p=0; p<numB; p++) {
      for (q=p+1; q<numB; q++) {
	  VASSERT( Bmat_mirror(thee,p,q) == ISNOT_MIRROR );
	  VASSERT( Bmat_mirror(thee,q,p) == ISNOT_MIRROR );
	  VASSERT( Bmat_format(thee,p,q) == ZERO_FORMAT );
	  VASSERT( Bmat_format(thee,q,p) == ZERO_FORMAT );
      }
      Mat_squeezeBRC( thee->AD[p][p], key );
  }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_copy2
 *
 * Purpose:  Copy a block matrix.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bmat_copy2(Bmat *Y, Bmat *X)
{

  int p, q;
  int numB;

  numB = Bmat_numB(X);

  VASSERT( Bmat_numB(Y)  == numB );

  for (p=0; p<numB; p++) {
      for (q=0; q<numB; q++) {
          if ( !Y->mirror[p][q] ) {
              Mat_copy2( Y->AD[p][q], X->AD[p][q] );
          } else {
              VASSERT( !Y->mirror[q][p] );
              VASSERT( Y->AD[q][p] == Y->AD[q][p] );
          }
      }
  }

}

/*
 * ***************************************************************************
 * Routine:  Bmat_axpy
 *
 * Purpose:  Scalar times a Bmat plus a Bmat:  Y += val*X.
 *
 * Notes:    The function of this routine can be controlled using "key"
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bmat_axpy(Bmat *Y, Bmat *X, double val, int key)
{

  int p, q;
  int numB;

  numB = X->numB;

  /* General checks of the block sizes of Y and X */
  VASSERT( Bmat_numB(Y)  == numB );

  for (p=0; p<numB; p++) {
      for (q=0; q<numB; q++) {
          if ( !Y->mirror[p][q] ) {
              Mat_axpy( Y->AD[p][q], X->AD[p][q], val, key );
          }
      }
  }

}

