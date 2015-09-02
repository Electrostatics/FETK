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
 * rcsid="$Id: mat.c,v 1.45 2010/08/12 05:18:27 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     mat.c
 *
 * Purpose:  Class Mat: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "mat_p.h"

VEMBED(rcsid="$Id: mat.c,v 1.45 2010/08/12 05:18:27 fetk Exp $")

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
 * Routine:  Mat_ctor
 *
 * Purpose:  The sparse matrix constructor.
 *
 * Notes:    This constructor only fixes the number of rows and columns
 *           in the matrix; the nonzero structure is not set.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Mat* Mat_ctor(Vmem *vmem, const char *name, int pnumR, int pnumC)
{
    Mat *thee = VNULL;

    VDEBUGIO("Mat_ctor: CREATING object..");

    /* initialize the memory manager and instantiate myself */
    thee = Vmem_malloc( VNULL, 1, sizeof(Mat) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Mat" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    thee->format = ZERO_FORMAT;
    thee->state  = NULL_STATE;
    thee->sym    = ISNOT_SYM;
    thee->impl   = ISNOT_IMPL;

    thee->iMallocIJA = 0;
    thee->iMallocA   = 0;

    /* initialize the parameters */
    strncpy(thee->name, name, 10);
    thee->numR  = pnumR;
    thee->numC  = pnumC;
    thee->numA  = 0;
    thee->numO  = 0;
    thee->numZ  = 0;
    thee->numBR = 0;
    thee->numBC = 0;

    /* initialize complex object pointers */
    thee->slu  = VNULL;
    thee->lnkL = VNULL;
    thee->lnkU = VNULL;
    thee->xln  = VNULL;
    thee->xlnt = VNULL;

    /* initialize primary malloc area pointers */
    thee->IJA  = VNULL;
    thee->A    = VNULL;
    thee->BR   = VNULL;
    thee->BC   = VNULL;

    /* initialize alias pointers */
    thee->IA   = VNULL;
    thee->JA   = VNULL;
    thee->diag = VNULL;
    thee->offU = VNULL;
    thee->offL = VNULL;

    VDEBUGIO("..done.\n");

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Mat_dtor
 *
 * Purpose:  The sparse matrix destructor.
 *
 * Notes:    This destructor does the reverse of Mat_ctor, and if
 *           necessary first reverses Mat_initStructure
 *           (or Mat_copyStructure).  I.e., if necessary,
 *           it first frees the large integer and real arrays created
 *           by Mat_initStructure or Mat_copyStructure, and then frees
 *           the Mat object itself at the last moment.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_dtor(Mat **thee)
{
    /* VASSERT( (*thee) != VNULL ); */
    if ((*thee) != VNULL) {

        /* first free the large integer and real nonzero structure */
        Mat_killStructure(*thee);

        /* now kill the object itself */
        VDEBUGIO("Mat_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Mat), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_initStructure
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
VPUBLIC void Mat_initStructure(Mat *thee,
    MATformat frmt, MATsym sym, int numO, int *IJA, double *A)
{
    /* keep track of malloc actions */
    thee->iMallocIJA = 0;
    thee->iMallocA   = 0;

    /* build framework from input */
    thee->format = frmt;
    thee->sym    = sym;
    thee->numO   = numO;

    /* initialize the state */
    thee->state  = ZERO_STATE;

    /* Format-dependent consistency checks and setup */
    switch (thee->format) {

      /* DRC consistency checks and setup */
      case DRC_FORMAT:

        /* DRC valid for symmetry OR nonsymmetry */
        VASSERT( (thee->sym==ISNOT_SYM) || (thee->sym==IS_SYM) );


        /* DRC only valid for square matrices */
        VASSERT( thee->numR==thee->numC );

        /* the setup */
        thee->IJA = IJA; /* integer structure via hand-off (don't malloc) */
        thee->IA  = thee->IJA;
        thee->JA  = thee->IJA + thee->numR + 1;
        if (thee->sym == ISNOT_SYM) {
            thee->numZ = thee->numR + 2*thee->numO;
            thee->numA = thee->numR + 2*thee->numO;
            if (thee->numA > 0) {
                VASSERT( A == VNULL );
                thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
                thee->iMallocA = 1;
            }
            thee->diag = thee->A;
            thee->offU = thee->A + thee->numR;
            thee->offL = thee->A + thee->numR + thee->numO;

        } else { /* (thee->sym == IS_SYM) */
            thee->numZ = thee->numR + 2*thee->numO;
            thee->numA = thee->numR + thee->numO;
            if (thee->numA > 0) {
                VASSERT( A == VNULL );
                thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
                thee->iMallocA = 1;
            }
            thee->diag = thee->A;
            thee->offU = thee->A + thee->numR;
            thee->offL = thee->offU;
        }
        break;

      /* ROW consistency checks and setup */
      case ROW_FORMAT:

        /* ROW only valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        /* the setup */
        thee->IJA  = IJA; /* integer structure via hand-off (don't malloc) */
        thee->IA   = thee->IJA;
        thee->JA   = thee->IJA + thee->numR + 1;
        thee->numZ = thee->numO;
        thee->numA = thee->numO;
        if ( thee->numA > 0 ) {
            VASSERT( A == VNULL );
            thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
            thee->iMallocA = 1;
        }
        thee->offU = thee->A;
        thee->offL = VNULL;
        thee->diag = VNULL;
        break;

      /* COL consistency checks */
      case COL_FORMAT:

        /* COL only valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        /* the setup */
        thee->IJA  = IJA; /* integer structure via hand-off (don't malloc) */
        thee->IA   = thee->IJA;
        thee->JA   = thee->IJA + thee->numC + 1;
        thee->numZ = thee->numO;
        thee->numA = thee->numO;
        if ( thee->numA > 0 ) {
            VASSERT( A == VNULL );
            thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
            thee->iMallocA = 1;
        }
        thee->offL = thee->A;
        thee->offU = VNULL;
        thee->diag = VNULL;
        break;

      /* SLU consistency checks */
      case SLU_FORMAT:

        /* SLU valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        /* the setup (we MUST malloc the integer structure) */
        thee->IJA  = Vmem_malloc( thee->vmem, thee->numR+1+numO, sizeof(int) );
        thee->iMallocIJA = 1;
        thee->IA   = thee->IJA;
        thee->JA   = thee->IJA + thee->numC + 1;
        thee->numZ = thee->numO;
        thee->numA = thee->numO;
        if ( thee->numA > 0 ) {
            VASSERT( A == VNULL );
            thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
            thee->iMallocA = 1;
        }
        thee->offL = VNULL;
        thee->offU = VNULL;
        thee->diag = VNULL;
        break;

      /* RLN consistency checks and setup */
      case RLN_FORMAT:

        Mat_initStructureLN( thee, frmt, sym );
        break;

      /* CLN consistency checks and setup */
      case CLN_FORMAT:

        Mat_initStructureLN( thee, frmt, sym );
        break;

      /* XLN consistency checks and setup */
      case XLN_FORMAT:

        Mat_initStructureLN( thee, frmt, sym );
        break;

      /* RFL consistency checks and setup */
      case RFL_FORMAT:

        /* RFL only valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        /* the setup (input numO and IJA are ignored) */
        thee->numO = thee->numR * thee->numC;
        thee->numA = thee->numO;
        thee->numZ = thee->numO;
        if ( thee->numA > 0 ) {
            if (A != VNULL) {
                thee->A = A;
            } else {
                VASSERT( A == VNULL );
                thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
                thee->iMallocA = 1;
            }
        }
        break;

      /* CFL consistency checks and setup */
      case CFL_FORMAT:

        /* CFL only valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        /* the setup (input numO and IJA are ignored) */
        thee->numO = thee->numR * thee->numC;
        thee->numA = thee->numO;
        thee->numZ = thee->numO;
        if ( thee->numA > 0 ) {
            if (A != VNULL) {
                thee->A = A;
            } else {
                VASSERT( A == VNULL );
                thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
                thee->iMallocA = 1;
            }
        }
        break;

      default:
        VASSERT(0);
        break;
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_copyStructure
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
VPUBLIC void Mat_copyStructure(Mat *thee, Mat *model)
{
    int i, size;

    VASSERT( thee->numR == model->numR );
    VASSERT( thee->numC == model->numC );

    /* initialize the state */
    thee->state = ZERO_STATE;

    /* build framework (numR and numC have already been set in ctor) */
    thee->format = model->format;  /* same format */
    thee->sym    = model->sym;     /* keep symmetry */
    thee->impl   = model->impl;    /* keep implicitness */
    thee->numO   = model->numO;    /* numA and numZ are set below */

    /* keep track of malloc actions */
    thee->iMallocIJA = 0;
    thee->iMallocA   = 0;

    /* nonzero integer structure is via copy (we malloc) */
    size      = thee->numR + 1 + thee->numO;
    thee->IJA = Vmem_malloc(thee->vmem,size,sizeof(int));
    thee->iMallocIJA = 1;
    for (i=0; i<size; i++) {
        thee->IJA[i] = model->IJA[i];
    }

    /* boundary structure is via copy (we malloc) */
    thee->numBR = model->numBR;
    if (thee->numBR > 0) {
        thee->BR = Vmem_malloc(thee->vmem,thee->numBR,sizeof(int));
        for (i=0; i<thee->numBR; i++) {
            thee->BR[i] = model->BR[i];
        }
    }
    thee->numBC = model->numBC;
    if (thee->numBC > 0) {
        thee->BC = Vmem_malloc(thee->vmem,thee->numBC,sizeof(int));
        for (i=0; i<thee->numBC; i++) {
            thee->BC[i] = model->BC[i];
        }
    }

    /* Format-dependent consistency checks and setup */
    switch (thee->format) {

      /* DRC consistency checks and setup */
      case DRC_FORMAT:

        /* DRC valid for symmetry OR nonsymmetry */
        VASSERT( (thee->sym==ISNOT_SYM) || (thee->sym==IS_SYM) );

        /* DRC only valid for square matrices */
        VASSERT( thee->numR==thee->numC );

        /* the setup */
        thee->IA = thee->IJA;
        thee->JA = thee->IJA + thee->numR + 1;
        if (thee->sym == ISNOT_SYM) {
            thee->numZ = thee->numR + 2*thee->numO;
            thee->numA = thee->numR + 2*thee->numO;
            if (thee->numA > 0) {
                thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
                thee->iMallocA = 1;
            }
            thee->diag = thee->A;
            thee->offU = thee->A + thee->numR;
            thee->offL = thee->A + thee->numR + thee->numO;

        } else { /* (thee->sym == IS_SYM) */
            thee->numZ = thee->numR + 2*thee->numO;
            thee->numA = thee->numR + thee->numO;
            if (thee->numA > 0) {
                thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
                thee->iMallocA = 1;
            }
            thee->diag = thee->A;
            thee->offU = thee->A + thee->numR;
            thee->offL = thee->offU;
        }
        break;

      /* ROW consistency checks and setup */
      case ROW_FORMAT:

        /* ROW only valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        /* the setup */
        thee->IA = thee->IJA;
        thee->JA = thee->IJA + thee->numR + 1;
        thee->numZ = thee->numO;
        thee->numA = thee->numO;
        if ( thee->numA > 0 ) {
            thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
            thee->iMallocA = 1;
        }
        break;

      /* COL consistency checks */
      case COL_FORMAT:

        /* COL only valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        /* the setup */
        thee->IA = thee->IJA;
        thee->JA = thee->IJA + thee->numC + 1;
        thee->numZ = thee->numO;
        thee->numA = thee->numO;
        if ( thee->numA > 0 ) {
            thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
            thee->iMallocA = 1;
        }
        break;

      /* RFL consistency checks and setup */
      case RFL_FORMAT:

        /* RFL only valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        /* the setup (input numO is already copied over) */
        thee->numA = thee->numO;
        thee->numZ = thee->numO;
        if ( thee->numA > 0 ) {
            thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
            thee->iMallocA = 1;
        }
        break;

      /* CFL consistency checks and setup */
      case CFL_FORMAT:

        /* CFL only valid for nonsymmetry */
        VASSERT( thee->sym==ISNOT_SYM );

        /* the setup (input numO is already copied over) */
        thee->numA = thee->numO;
        thee->numZ = thee->numO;
        if ( thee->numA > 0 ) {
            thee->A = Vmem_malloc(thee->vmem,thee->numA,sizeof(double));
            thee->iMallocA = 1;
        }
        break;

      default:
        VASSERT(0);
        break;
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_killStructure
 *
 * Purpose:  Kill the nonzero structure and structure information.
 *
 * Notes:    This routine does the reverse of Mat_initStructure
 *           (or Mat_copyStructure).  It leaves only the information
 *           about the number of blocks, number of rows, and number of
 *           columns per block.  I.e., what is left is only what was
 *           present after the initial call to Mat_ctor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_killStructure(Mat *thee)
{
    int size;

    /* VASSERT( (*thee) != VNULL ); */
    if (thee != VNULL) {
        if (thee->state != NULL_STATE) {

            /* Format-dependent destruction */
            switch (thee->format) {

              case DRC_FORMAT:

                /* DRC only valid for symmetry OR nonsymmetry */
                VASSERT( (thee->sym==ISNOT_SYM)||(thee->sym==IS_SYM) );
                /* DRC only valid for square matrices */
                VASSERT( thee->numR==thee->numC );

                /* release of nonzero structure */
                size = thee->numR + 1 + thee->numO;
                /* VASSERT( thee->iMallocIJA == 1 ); */
                Vmem_free( thee->vmem, size, sizeof(int),
                    (void**)&(thee->IJA) );

                /* release of boundary row/column arrays */
                if ( thee->BR != VNULL ) {
                    Vmem_free( thee->vmem, thee->numBR, sizeof(int),
                        (void**)&(thee->BR) );
                }
                if ( thee->BC != VNULL ) {
                    Vmem_free( thee->vmem, thee->numBC, sizeof(int),
                        (void**)&(thee->BC) );
                }
                thee->numBR = 0;
                thee->numBC = 0;

                /* release of nonzeros */
                if ( thee->numA > 0 ) {
                    /* If VWARN is triggered, it will either be memory leak */
                    /* or bus error */
                    VWARN( thee->iMallocA == 1 );
                    Vmem_free( thee->vmem, thee->numA, sizeof(double),
                        (void**)&(thee->A) );
                    thee->numA = 0;
                    thee->numO = 0;
                    thee->numZ = 0;
                }

                break;

              case ROW_FORMAT:

                /* ROW only valid for nonsymmetry */
                VASSERT( (thee->sym==ISNOT_SYM) );

                /* release of nonzero structure */
                size = thee->numR + 1 + thee->numO;
                /* VASSERT( thee->iMallocIJA == 1 ); */
                Vmem_free( thee->vmem, size, sizeof(int),
                    (void**)&(thee->IJA) );

                /* release of boundary row/column arrays */
                if ( thee->BR != VNULL ) {
                    Vmem_free( thee->vmem, thee->numBR, sizeof(int),
                        (void**)&(thee->BR) );
                }
                if ( thee->BC != VNULL ) {
                    Vmem_free( thee->vmem, thee->numBC, sizeof(int),
                        (void**)&(thee->BC) );
                }
                thee->numBR = 0;
                thee->numBC = 0;

                /* release of nonzeros */
                if ( thee->numA > 0 ) {
                    VASSERT( thee->iMallocA == 1 );
                    Vmem_free( thee->vmem, thee->numA, sizeof(double),
                        (void**)&(thee->A) );
                    thee->numA = 0;
                    thee->numO = 0;
                    thee->numZ = 0;
                }

                break;

              case COL_FORMAT:

                /* COL only valid for nonsymmetry */
                VASSERT( (thee->sym==ISNOT_SYM) );

                /* release of nonzero structure */
                size = thee->numC + 1 + thee->numO;
                /* VASSERT( thee->iMallocIJA == 1 ); */
                Vmem_free( thee->vmem, size, sizeof(int),
                    (void**)&(thee->IJA) );

                /* release of boundary row/column arrays */
                if ( thee->BR != VNULL ) {
                    Vmem_free( thee->vmem, thee->numBR, sizeof(int),
                        (void**)&(thee->BR) );
                }
                if ( thee->BC != VNULL ) {
                    Vmem_free( thee->vmem, thee->numBC, sizeof(int),
                        (void**)&(thee->BC) );
                }
                thee->numBR = 0;
                thee->numBC = 0;

                /* release of nonzeros */
                if ( thee->numA > 0 ) {
                    VASSERT( thee->iMallocA == 1 );
                    Vmem_free( thee->vmem, thee->numA, sizeof(double),
                        (void**)&(thee->A) );
                    thee->numA = 0;
                    thee->numO = 0;
                    thee->numZ = 0;
                }

                break;

              case SLU_FORMAT:

                /* SLU only valid for nonsymmetry */
                VASSERT( (thee->sym==ISNOT_SYM) );

                /* release of nonzero structure */
                size = thee->numC + 1 + thee->numO;
                /* VASSERT( thee->iMallocIJA == 1 ); */
                Vmem_free( thee->vmem, size, sizeof(int),
                    (void**)&(thee->IJA) );

                /* release of boundary row/column arrays */
                if ( thee->BR != VNULL ) {
                    Vmem_free( thee->vmem, thee->numBR, sizeof(int),
                        (void**)&(thee->BR) );
                }
                if ( thee->BC != VNULL ) {
                    Vmem_free( thee->vmem, thee->numBC, sizeof(int),
                        (void**)&(thee->BC) );
                }
                thee->numBR = 0;
                thee->numBC = 0;

                /* release of nonzeros */
                if ( thee->numA > 0 ) {
                    VASSERT( thee->iMallocA == 1 );
                    Vmem_free( thee->vmem, thee->numA, sizeof(double),
                        (void**)&(thee->A) );
                    thee->numA = 0;
                    thee->numO = 0;
                    thee->numZ = 0;
                }

                /* finally destroy the internal objects */
                Mat_sluDestroy(thee);

                break;

              case RLN_FORMAT:
                Mat_killStructureLN( thee );
                break;

              case CLN_FORMAT:
                Mat_killStructureLN( thee );
                break;

              case XLN_FORMAT:
                Mat_killStructureLN( thee );
                break;

              case RFL_FORMAT:

                /* RFL only valid for nonsymmetry */
                VASSERT( (thee->sym==ISNOT_SYM) );

                /* release of nonzeros */
                if ( thee->numA > 0 ) {
                    if ( thee->iMallocA == 1 ) {
                        Vmem_free( thee->vmem, thee->numA, sizeof(double),
                            (void**)&(thee->A) );
                    }
                    thee->numA = 0;
                    thee->numO = 0;
                    thee->numZ = 0;
                }
                break;

              case CFL_FORMAT:

                /* CFL only valid for nonsymmetry */
                VASSERT( (thee->sym==ISNOT_SYM) );

                /* release of nonzeros */
                if ( thee->numA > 0 ) {
                    if ( thee->iMallocA == 1 ) {
                        Vmem_free( thee->vmem, thee->numA, sizeof(double),
                            (void**)&(thee->A) );
                    }
                    thee->numA = 0;
                    thee->numO = 0;
                    thee->numZ = 0;
                }
                break;

              default:
                VASSERT(0);
                break;
            }

            /* initialize the state */
            thee->state = NULL_STATE;

            /* keep track of malloc actions */
            thee->iMallocIJA = 0;
            thee->iMallocA   = 0;
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_numR
 *
 * Purpose:  Return number of row in the matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Mat_numR(Mat *thee)
{
    return thee->numR;
}

/*
 * ***************************************************************************
 * Routine:  Mat_numC
 *
 * Purpose:  Return number of columns in the matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Mat_numC(Mat *thee)
{
    return thee->numC;
}

/*
 * ***************************************************************************
 * Routine:  Mat_numA
 *
 * Purpose:  Return number of nonzeros we are actually storing.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Mat_numA(Mat *thee)
{
    return thee->numA;
}

/*
 * ***************************************************************************
 * Routine:  Mat_numO
 *
 * Purpose:  Return number of nonzeros we are actually storing
 *           which are located in upper (or lower) triangle.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Mat_numO(Mat *thee)
{
    return thee->numO;
}

/*
 * ***************************************************************************
 * Routine:  Mat_numZ
 *
 * Purpose:  Return number of nonzeros we WOULD be storing if we were
 *           ignoring symmetry and storing all nonzeros.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Mat_numZ(Mat *thee)
{
    return thee->numZ;
}

/*
 * ***************************************************************************
 * Routine:  Mat_format
 *
 * Purpose:  Return the format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC MATformat Mat_format(Mat *thee)
{
    return thee->format;
}

/*
 * ***************************************************************************
 * Routine:  Mat_sym
 *
 * Purpose:  Return the symmetry.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC MATsym Mat_sym(Mat *thee)
{
    return thee->sym;
}

/*
 * ***************************************************************************
 * Routine:  Mat_state
 *
 * Purpose:  Return the state.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC MATstate Mat_state(Mat *thee)
{
    return thee->state;
}

/*
 * ***************************************************************************
 * Routine:  Mat_impl
 *
 * Purpose:  Return the impl.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC MATimpl Mat_impl(Mat *thee)
{
    return thee->impl;
}

/*
 * ***************************************************************************
 * Routine:  Mat_setFormat
 *
 * Purpose:  Set the format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_setFormat(Mat *thee, MATformat format)
{
    thee->format = format;
}

/*
 * ***************************************************************************
 * Routine:  Mat_setSym
 *
 * Purpose:  Set the symmetry.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_setSym(Mat *thee, MATsym sym)
{
    thee->sym = sym;
}

/*
 * ***************************************************************************
 * Routine:  Mat_setState
 *
 * Purpose:  Set the state.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_setState(Mat *thee, MATstate state)
{
    thee->state = state;
}

/*
 * ***************************************************************************
 * Routine:  Mat_setImpl
 *
 * Purpose:  Set the impl.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_setImpl(Mat *thee, MATimpl impl)
{
    thee->impl = impl;
}

/*
 * ***************************************************************************
 * Routine:  Mat_sizeIJA
 *
 * Purpose:  Return total number of INTEGER STORAGE LOCATIONS in the matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Mat_sizeIJA(Mat *thee)
{
    return (thee->numR + 1 + thee->numO);
}

/*
 * ***************************************************************************
 * Routine:  Mat_sizeA
 *
 * Purpose:  Return total number of REAL STORAGE LOCATIONS in the matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Mat_sizeA(Mat *thee)
{
    return Mat_numA(thee);
}

/*
 * ***************************************************************************
 * Routine:  Mat_IJA
 *
 * Purpose:  Return the integer structure IJA.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int *Mat_IJA(Mat *thee)
{
    return thee->IJA;
}

/*
 * ***************************************************************************
 * Routine:  Mat_IA
 *
 * Purpose:  Return the integer structure IA.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int *Mat_IA(Mat *thee)
{
    return thee->IA;
}

/*
 * ***************************************************************************
 * Routine:  Mat_JA
 *
 * Purpose:  Return the integer structure JA.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int *Mat_JA(Mat *thee)
{
    return thee->JA;
}

/*
 * ***************************************************************************
 * Routine:  Mat_A
 *
 * Purpose:  Return the real structure A.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double *Mat_A(Mat *thee)
{
    return thee->A;
}

/*
 * ***************************************************************************
 * Routine:  Mat_diag
 *
 * Purpose:  Return the diagonal structure A.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double *Mat_diag(Mat *thee)
{
    return thee->diag;
}

/*
 * ***************************************************************************
 * Routine:  Mat_offU
 *
 * Purpose:  Return the upper-triangle structure A.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double *Mat_offU(Mat *thee)
{
    return thee->offU;
}

/*
 * ***************************************************************************
 * Routine:  Mat_offL
 *
 * Purpose:  Return the lower-triangle structure A.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double *Mat_offL(Mat *thee)
{
    return thee->offL;
}

/*
 * ***************************************************************************
 * Routine:  Mat_print
 *
 * Purpose:  Print the matrix as a DENSE matrix in MATLAB format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_print(Mat *thee)
{
    int i, j, k;
    int numR, numC;
    char rn[80];
    const int MaxRows = 100;
    const int MaxCols = 30;
    double matrix[100][30];

    if ( ( thee->format == RLN_FORMAT ) ||
         ( thee->format == CLN_FORMAT ) ||
         ( thee->format == XLN_FORMAT ) ) {
        Mat_printLN( thee );
        return;
    }

    numR = thee->numR;
    numC = thee->numC;

    strncpy(rn,"Mat_print:",80);

    /* some i/o */
    Vnm_print(0, "%s printing <%s>" " [dim=(%dx%d),sym=%d,numA=%d,numO=%d]\n",
        rn, thee->name, thee->numR, thee->numC, thee->sym,
        thee->numA, thee->numO);

    /* size check */
    if ((numR > MaxRows) || (numC > MaxCols)) {
        Vnm_print(0, "%smatrix too large to view....skipping.\n", rn);
        return;
    }

    /* make a dense matrix first */
    for (i=0; i<numR; i++) {
        for (j=0; j<numC; j++) {
            matrix[i][j] = 0.0;
        }
    }

    if (thee->state != NULL_STATE) {

        switch (thee->format) {

          case DRC_FORMAT:

            for (i=0; i<numR; i++) {
                matrix[i][i] = thee->diag[i];
                for (k=thee->IA[i]; k<thee->IA[i+1]; k++) {
                    j = thee->JA[k];
                    matrix[i][j] = thee->offU[k];
                    matrix[j][i] = thee->offL[k];
                }
            }
            break;

          case ROW_FORMAT:

            for (i=0; i<numR; i++) {
                for (k=thee->IA[i]; k<thee->IA[i+1]; k++) {
                    j = thee->JA[k];
                    matrix[i][j] = thee->A[k];
                }
            }
            break;

          case COL_FORMAT:

            for (j=0; j<numC; j++) {
                for (k=thee->IA[j]; k<thee->IA[j+1]; k++) {
                    i = thee->JA[k];
                    matrix[i][j] = thee->A[k];
                }
            }
            break;

          case RFL_FORMAT:

            for (i=0; i<numR; i++) {
                for (j=0; j<numC; j++) {
                    matrix[i][j] = thee->A[ (i*numC) + j ];
                }
            }
            break;

          case CFL_FORMAT:

            for (i=0; i<numR; i++) {
                for (j=0; j<numC; j++) {
                    matrix[i][j] = thee->A[ (j*numR) + i ];
                }
            }
            break;

          default:
            Vnm_print(0,
              "%smatrix not in correct format to print....skipping.\n", rn);
            break;
            }
    }

    /* print the matrix */
    Vnm_print(0, "%s = [\n", thee->name);
    for (i=0; i<numR; i++) {
        for (j=0; j<numC; j++) {
            if (VABS(matrix[i][j]) < 0.0001) {
                Vnm_print(0, "  0.0  ");
            } else {
                Vnm_print(0, "%7.3f", matrix[i][j]);
            }
        }
        Vnm_print(0, "\n");
    }
    Vnm_print(0, "];\n");
}

/*
 * ***************************************************************************
 * Routine:  Mat_printSp
 *
 * Purpose:  Print the matrix as a SPARSE matrix in MATLAB format.
 *
 *   Notes:  flag==0 ==> write
 *           flag==1 ==> append
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_printSp(Mat *thee, char *fname, int pflag)
{
    int i, j, k;
    int numR, numC;
    char rn[80];
    FILE *fp;

    if ( ( thee->format == RLN_FORMAT ) ||
         ( thee->format == CLN_FORMAT ) ||
         ( thee->format == XLN_FORMAT ) ) {
        Mat_printLNSp( thee, fname, pflag );
        return;
    }

    numR = thee->numR;
    numC = thee->numC;

    strncpy(rn,"Mat_printSp:",80);

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

    Vnm_print(0, "%s printing <%s>" " [dim=(%dx%d),sym=%d,numA=%d,numO=%d]"
                 " to file <%s>\n",
        rn, thee->name, thee->numR, thee->numC, thee->sym,
        thee->numA, thee->numO, fname);

    /* print the matrix in matlab sparse format */
    fprintf(fp,"%% %s matrix <%s> [dim=(%dx%d)]\n",
        rn, thee->name, numR, numC);

    if (thee->state != NULL_STATE) {

        fprintf(fp,"%% ----------------------------------------\n");
        fprintf(fp, "fprintf('Defining %s_IJA..');", thee->name);
        fprintf(fp, "\n%s_IJA = [\n", thee->name);

        switch (thee->format) {

          case DRC_FORMAT:
            for (i=0; i<numR; i++) {
                fprintf(fp, "    %d    %d    %15.8e\n",
                    i+1, i+1, thee->diag[i]);
                for (k=thee->IA[i]; k<thee->IA[i+1]; k++) {
                    j = thee->JA[k];
                    fprintf(fp, "    %d    %d    %15.8e\n",
                        i+1, j+1, thee->offU[k]);
                    fprintf(fp, "    %d    %d    %15.8e\n",
                        j+1, i+1, thee->offL[k]);
                }
            }
            break;

          case ROW_FORMAT:
            for (i=0; i<numR; i++) {
                for (k=thee->IA[i]; k<thee->IA[i+1]; k++) {
                    j = thee->JA[k];
                    fprintf(fp, "    %d    %d    %15.8e\n",
                        i+1, j+1, thee->A[k]);
                }
            }
            break;

          case COL_FORMAT:
            for (j=0; j<numC; j++) {
                for (k=thee->IA[j]; k<thee->IA[j+1]; k++) {
                    i = thee->JA[k];
                    fprintf(fp, "    %d    %d    %15.8e\n",
                        i+1, j+1, thee->A[k]);
                }
            }
            break;

          default:
            Vnm_print(0,
              "%smatrix not in correct format to print....skipping.\n", rn);
            break;
        }

        fprintf(fp, "];\n\n");
        fprintf(fp, "fprintf('..done.\\n');\n");
    }

    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%% Matlab code to generate sparse matrix.\n");
    fprintf(fp,"%% ----------------------------------------\n");
    if( thee->state != NULL_STATE ) {
        fprintf(fp,
          "%s = sparse(%s_IJA(:,1),%s_IJA(:,2),%s_IJA(:,3),%d,%d);\n",
          thee->name, thee->name, thee->name, thee->name, numR, numC);
    } else {
        fprintf(fp, "%s = sparse(%d,%d);\n", thee->name, numR, numC);
    }
    fprintf(fp,"%% ----------------------------------------\n");

    Vnm_print(0,"..done.\n");

    /* close file and return */
    fclose(fp);
}

/*
 * ***************************************************************************
 * Routine:  Mat_printNoD
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
VPUBLIC void Mat_printNoD(Mat *thee)
{
    int i, j, k;
    char rn[80];
    const int MaxRows = 100;
    const int MaxCols = 30;
    double matrix[30][30];

    strncpy(rn,"Mat_printNoD:",80);

    /* some i/o */
    Vnm_print(0, "%s printing <%s>" " [dim=(%dx%d),sym=%d,numA=%d,numO=%d]\n",
        rn, thee->name, thee->numR, thee->numC, thee->sym,
        thee->numA, thee->numO);

    /* size check */
    if ((thee->numR > MaxRows) || (thee->numC > MaxCols)) {
        Vnm_print(0,
            "%smatrix too large to view....skipping.\n", rn);
        return;
    }

    /* make a dense matrix first */
    for (i=0; i<thee->numR; i++)
        for (j=0; j<thee->numC; j++)
            matrix[i][j] = 0.0;

    switch (thee->format) {

      case DRC_FORMAT:
        for (i=0; i<thee->numR; i++) {
            matrix[i][i] = thee->diag[i];
            for (k=thee->IA[i]; k<thee->IA[i+1]; k++) {
                j = thee->JA[k];
                matrix[i][j] = thee->offU[k];
                matrix[j][i] = thee->offL[k];
            }
        }
        break;

      case ROW_FORMAT:
        for (i=0; i<thee->numR; i++) {
            for (k=thee->IA[i]; k<thee->IA[i+1]; k++) {
                j = thee->JA[k];
                matrix[i][j] = thee->A[k];
            }
        }
        break;

      case COL_FORMAT:
        for (j=0; j<thee->numC; j++) {
            for (k=thee->IA[j]; k<thee->IA[j+1]; k++) {
                i = thee->JA[k];
                matrix[i][j] = thee->A[k];
            }
        }
        break;

      default:
        Vnm_print(0,
          "%smatrix not in correct format to print....skipping.\n", rn);
        break;
    }

    /* pull out the dirichlet rows and columns */
    for (k=0; k<thee->numBR; k++) {
        for (j=0; j<thee->numC; j++) {
            matrix[ thee->BR[k] ][ j ] = 0.0;
        }
    }
    for (k=0; k<thee->numBC; k++) {
        for (i=0; i<thee->numR; i++) {
            matrix[ i ][ thee->BC[k] ] = 0.0;
        }
    }

    /* print the matrix */
    Vnm_print(0, "%s = [\n", thee->name);
    for (i=0; i<thee->numR; i++) {
        for (j=0; j<thee->numC; j++) {
            if (VABS(matrix[i][j]) < 0.0001) {
                Vnm_print(0, "  0.0  ");
            } else {
                Vnm_print(0, "%7.3f", matrix[i][j]);
            }
        }
        Vnm_print(0, "\n");
    }
    Vnm_print(0, "];\n");
}

/*
 * ***************************************************************************
 * Routine:  Mat_printSpNoD
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
VPUBLIC void Mat_printSpNoD(Mat *thee, char *fname, int pflag)
{
    int i, j, k, ii, i_do;
    char rn[80];
    FILE *fp;

    strncpy(rn,"Mat_printSpNoD:",80);

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

    Vnm_print(0, "%s printing <%s>" " [dim=(%dx%d),sym=%d,numA=%d,numO=%d]"
                 " to file <%s>\n",
        rn, thee->name, thee->numR, thee->numC, thee->sym,
        thee->numA, thee->numO, fname);

    /* print the matrix in matlab sparse format */
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%% %s matrix <%s> [dim=(%dx%d), sym=%d]\n",
        rn,thee->name,thee->numR,thee->numC,thee->sym);
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp, "fprintf('Defining %s..');", thee->name);
    fprintf(fp, "\n%s_IJA = [\n", thee->name);

    switch (thee->format) {

      case DRC_FORMAT:
        for (i=0; i<thee->numR; i++) {
            i_do = 1;
            for (ii=0; ii<thee->numBR; ii++)
                if (thee->BR[ii] == i) i_do = 0;
            if (i_do)
                fprintf(fp, "    %d    %d    %15.8e\n",
                    i+1, i+1, thee->diag[i]);
        }

        for (i=0; i<thee->numR; i++) {
            for (k=thee->IA[i]; k<thee->IA[i+1]; k++) {
                j = thee->JA[k];
                i_do = 1;
                for (ii=0; ii<thee->numBR; ii++)
                    if ((thee->BR[ii] == i) || (thee->BR[ii] == j)) {
                        i_do = 0;
                    }
                if (i_do)
                    fprintf(fp, "    %d    %d    %15.8e\n",
                        i+1, j+1, thee->offU[k]);
            }
        }

        for (j=0; j<thee->numR; j++) {
            for (k=thee->IA[j]; k<thee->IA[j+1]; k++) {
                i = thee->JA[k];
                i_do = 1;
                for (ii=0; ii<thee->numBR; ii++)
                    if ((thee->BR[ii] == i) || (thee->BR[ii] == j)) {
                        i_do = 0;
                    }
                if (i_do)
                    fprintf(fp, "    %d    %d    %15.8e\n",
                        i+1, j+1, thee->offL[k]);
            }
        }
        break;

      case ROW_FORMAT:
        for (i=0; i<thee->numR; i++) {
            for (k=thee->IA[i]; k<thee->IA[i+1]; k++) {
                j = thee->JA[k];
                i_do = 1;
                for (ii=0; ii<thee->numBR; ii++)
                    if ((thee->BR[ii] == i) || (thee->BR[ii] == j)) {
                        i_do = 0;
                    }
                if (i_do)
                    fprintf(fp, "    %d    %d    %15.8e\n",
                        i+1, j+1, thee->A[k]);
            }
        }
        break;

      case COL_FORMAT:
        for (j=0; j<thee->numC; j++) {
            for (k=thee->IA[j]; k<thee->IA[j+1]; k++) {
                i = thee->JA[k];
                i_do = 1;
                for (ii=0; ii<thee->numBR; ii++)
                    if ((thee->BR[ii] == i) || (thee->BR[ii] == j)) {
                        i_do = 0;
                    }
                if (i_do)
                    fprintf(fp, "    %d    %d    %15.8e\n",
                        i+1, j+1, thee->A[k]);
            }
        }
        break;

      default:
        Vnm_print(0,
          "%smatrix not in correct format to print....skipping.\n", rn);
        break;
    }

    fprintf(fp, "];\n");
    fprintf(fp, "fprintf('..done.\\n');\n");
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%% Matlab code to generate sparse matrix.\n");
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,
      "%s = sparse(%s_IJA(:,1),%s_IJA(:,2),%s_IJA(:,3),%d,%d);\n",
      thee->name, thee->name, thee->name, thee->name,
      thee->numR, thee->numC);
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp, "\n\n");

    Vnm_print(0,"..done.\n");

    /* close file and return */
    fclose(fp);
}

/*
 * ***************************************************************************
 * Routine:  Mat_zero
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
VPUBLIC void Mat_zero(Mat *thee)
{
    int i;

    /* zero out all of the floating point storage */
    if (thee->state != NULL_STATE) {

        switch (thee->format) {

          case DRC_FORMAT:
            for (i=0; i<thee->numA; i++) {
                thee->A[i] = 0.;
            }
            break;

          case ROW_FORMAT:
            for (i=0; i<thee->numA; i++) {
                thee->A[i] = 0.;
            }
            break;

          case COL_FORMAT:
            if (thee->sym != 2) {
                for (i=0; i<thee->numA; i++) {
                    thee->A[i] = 0.;
                }
            }
            break;

          case SLU_FORMAT:
            for (i=0; i<thee->numA; i++) {
                thee->A[i] = 0.;
            }
            Mat_sluDestroy(thee);
            break;

          case RLN_FORMAT:
            if (thee->lnkU != VNULL) {
                Vset_reset( thee->lnkU );
            }
            break;

          case CLN_FORMAT:
            if (thee->lnkL != VNULL) {
                Vset_reset( thee->lnkL );
            }
            break;

          case XLN_FORMAT:
            break;

          case RFL_FORMAT:
            for (i=0; i<thee->numA; i++) {
                thee->A[i] = 0.;
            }
            break;

          case CFL_FORMAT:
            for (i=0; i<thee->numA; i++) {
                thee->A[i] = 0.;
            }
            break;

          default:
            VASSERT(0);
            break;
        }

        thee->state = ZERO_STATE;
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_set
 *
 * Purpose:  Set a value in a matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_set(Mat *thee, int i, int j, double val)
{
    VASSERT( thee->state != NULL_STATE );

    switch (thee->format) {

      case DRC_FORMAT:
        thee->state = ASSEMBLED_STATE;
        if (i==j)     thee->diag[i] = val;
        else if (i<j) mPlaceit(thee->IA, thee->JA, thee->offU, 0, i, j, val);
        else          mPlaceit(thee->IA, thee->JA, thee->offL, 0, j, i, val);
        break;

      case ROW_FORMAT:
        thee->state = ASSEMBLED_STATE;
        mPlaceit(thee->IA, thee->JA, thee->A, 0, i, j, val);
        break;

      case COL_FORMAT:
        thee->state = ASSEMBLED_STATE;
        mPlaceit(thee->IA, thee->JA, thee->A, 0, j, i, val);
        break;

      case RFL_FORMAT:
        thee->state = ASSEMBLED_STATE;
        thee->A[ i*(thee->numC) + j ] = val;
        break;

      case CFL_FORMAT:
        thee->state = ASSEMBLED_STATE;
        thee->A[ j*(thee->numR) + i ] = val;
        break;

      default:
        VASSERT(0);
        break;
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_addTo
 *
 * Purpose:  Add to a value in a matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_addTo(Mat *thee, int i, int j, double val)
{
    VASSERT( thee->state != NULL_STATE );

    switch (thee->format) {

      case DRC_FORMAT:
        thee->state = ASSEMBLED_STATE;
        if (i==j)     thee->diag[i] += val;
        else if (i<j) mPlaceit(thee->IA, thee->JA, thee->offU, 1, i, j, val);
        else          mPlaceit(thee->IA, thee->JA, thee->offL, 1, j, i, val);
        break;

      case ROW_FORMAT:
        thee->state = ASSEMBLED_STATE;
        mPlaceit(thee->IA, thee->JA, thee->A, 1, i, j, val);
        break;

      case COL_FORMAT:
        thee->state = ASSEMBLED_STATE;
        mPlaceit(thee->IA, thee->JA, thee->A, 1, j, i, val);
        break;

      case RFL_FORMAT:
        thee->state = ASSEMBLED_STATE;
        thee->A[ i*(thee->numC) + j ] += val;
        break;

      case CFL_FORMAT:
        thee->state = ASSEMBLED_STATE;
        thee->A[ j*(thee->numR) + i ] += val;
        break;

      default:
        VASSERT(0);
        break;
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_buildBRC
 *
 * Purpose:  Set the boundary row and column information.
 *
 * Notes:    key=0 ==> set pointers
 *           key=1 ==> do a copy
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_buildBRC(Mat *thee, int numBR, int numBC, int *BR, int *BC)
{
    int i;

    if ( thee->numBR > 0 ) {
        VASSERT( thee->BR != VNULL );
        Vmem_free( thee->vmem, thee->numBR, sizeof(int),
            (void**)&(thee->BR) );
    }
    if ( thee->numBC > 0 ) {
        VASSERT( thee->BC != VNULL );
        Vmem_free( thee->vmem, thee->numBC, sizeof(int),
            (void**)&(thee->BC) );
    }
    thee->BR = VNULL;
    thee->BC = VNULL;

    thee->numBR = numBR;
    thee->numBC = numBC;

    if (thee->numBR > 0) {
        thee->BR = Vmem_malloc(thee->vmem,thee->numBR,sizeof(int));
        for (i=0; i<thee->numBR; i++) {
            thee->BR[i] = BR[i];
        }
    }
    if (thee->numBC > 0) {
        thee->BC = Vmem_malloc(thee->vmem,thee->numBC,sizeof(int));
        for (i=0; i<thee->numBC; i++) {
            thee->BC[i] = BC[i];
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_zeroBRC
 *
 * Purpose:  Apply the boundary row and column information.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_zeroBRC(Mat *thee)
{
    int i, j, k, ibase, *BR, *BC;

    /* this only makes sense for prolongation matrix at this point */
    VASSERT( thee->format == ROW_FORMAT );

    /* offset row indices in the case of implicit identity */
    ibase = (thee->impl == IS_IMPL) ? thee->numC : 0;

    /* create temporary boundary row/col info */
    BR = Vmem_malloc( thee->vmem, thee->numR + ibase, sizeof(int) );
    BC = Vmem_malloc( thee->vmem, thee->numC, sizeof(int) );

    for (i=0; i<thee->numR; i++) {
        BR[ i ] = 0;
    }
    for (i=0; i<thee->numBR; i++) {
        BR[ thee->BR[i] ] = 1;
    }
    for (i=0; i<thee->numC; i++) {
        BC[ i ] = 0;
    }
    for (i=0; i<thee->numBC; i++) {
        BC[ thee->BC[i] ] = 1;
    }

    /* bring in the PDE: zero the dirichlet rows */
    for (i=0; i<thee->numR; i++) {
        for (k=thee->IA[i]; k<thee->IA[i+1]; k++) {
            j = thee->JA[k];
            if ( VDIRICHLET( BR[i+ibase] ) ) {
                thee->A[ k ] = 0.0;
            } else if ( VDIRICHLET( BC[j] ) ) {
                thee->A[ k ] = 0.0;
            }
        }
    }

    /* destroy temporary boundary row/col info */
    Vmem_free( thee->vmem, thee->numR + ibase, sizeof(int), (void**)&BR );
    Vmem_free( thee->vmem, thee->numC, sizeof(int), (void**)&BC );
}

/*
 * ***************************************************************************
 * Routine:  Mat_diagBRC
 *
 * Purpose:  Place identity entries on diagonal of boundary row/col.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_diagBRC(Mat *thee)
{
    int i;

    /* this only makes sense for DRC matrices */
    VASSERT( thee->format == DRC_FORMAT );
    VASSERT( thee->numR   == thee->numC );
    VASSERT( thee->numBR  == thee->numBC );

    /* put identity on the boundary rows */
    for (i=0; i<thee->numBR; i++) {
        thee->diag[ thee->BR[i] ] = 1.0;
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_galerkin
 *
 * Purpose:  Enforce the Galerkin conditions algebraically.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_galerkin(Mat *thee, Mat *rmat, Mat *amat, Mat *pmat)
{
    int numBR, numBC, *BR, *BC;

    /*  are we ready to roll? */
    VASSERT( thee->state == NULL_STATE );

    /* do dimensions of R,A,P agree for a product? */
    VASSERT( amat->numR == Mat_numR(rmat) );
    VASSERT( amat->numC == Mat_numR(pmat) );

    /* some additional consistency checks */
    VASSERT( thee->numR == Mat_numC(rmat) );
    VASSERT( thee->numC == Mat_numC(pmat) );

    /* form the triple matrix product */
    buildG(thee->vmem, amat->format, amat->sym, thee->numR, amat->numR,

        &(thee->numO),
        &(thee->numA),
        &(thee->IJA),
        &(thee->A),
        &(thee->IA),
        &(thee->JA),
        &(thee->diag),
        &(thee->offU),
        &(thee->offL),

        Mat_IA(rmat), Mat_JA(rmat), Mat_A(rmat),

        Mat_IA(amat), Mat_JA(amat),
        Mat_A(amat), Mat_diag(amat),
        Mat_offU(amat), Mat_offL(amat),

        Mat_IA(pmat), Mat_JA(pmat), Mat_A(pmat)
    );

    /* we have structure now */
    thee->state  = ASSEMBLED_STATE;
    thee->format = amat->format;
    thee->sym    = amat->sym;
    thee->impl   = amat->impl;

    /* buildG allocated the space */
    thee->iMallocIJA = 1;
    if (thee->numA > 0 ) {
        thee->iMallocA = 1;
    }

    /* the numZ parameter */
    if (thee->format == DRC_FORMAT) {
        if (thee->sym == IS_SYM) {
            thee->numZ = thee->numA + thee->numO;
        } else { /* (thee->sym == ISNOT_SYM) */
            thee->numZ = thee->numA;
        }
    } else { /* (thee->format != DRC_FORMAT) */
        thee->numZ = thee->numA;
    }

    /* the BRC structure */
    numBR = rmat->numBC;
    numBC = pmat->numBC;
    BR = rmat->BC;
    BC = pmat->BC;
    Mat_buildBRC(thee, numBR, numBC, BR, BC);
}

/*
 * ***************************************************************************
 * Routine:  Mat_sluDirect
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
VPUBLIC int Mat_sluDirect(Mat *thee)
{
    int ival = 0;
    /* VASSERT( thee->format == SLU_FORMAT ); */
    /* the decision about when sparse direct will be the best solver */
    if ( thee->numR < SPARSE_CUTOFF ) ival = 1;
    return ival;
}

/*
 * ***************************************************************************
 * Routine:  Mat_sluCreate
 *
 * Purpose:  Setup for a sparse LU factorization of matrix.
 *
 * Notes:    Creates internal <ia,ja,a> storage which is later freed
 *           by Mat_sluDestroy.  Also initializes the sparse direct
 *           library.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_sluCreate(Mat *thee)
{
    VASSERT( thee->format == SLU_FORMAT );
}

/*
 * ***************************************************************************
 * Routine:  Mat_sluFactor
 *
 * Purpose:  Create the sparse LU factors for the system matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Mat_sluFactor(Mat *thee)
{
    int rc = 0;    /* 1=factors okay, 0=factors not okay */

    VASSERT( thee->format == SLU_FORMAT );
    VASSERT( thee->numO == thee->numA );
    VASSERT( thee->numO == thee->numZ );

    /*  matrix has already been sparse factored */
    if (thee->state == FACTORED_STATE) {

        rc = 1;

    /* if it hasn't been factored, then free existing factors and rebuild */
    } else if (thee->state == ZERO_STATE) {

        VDEBUGIO("Mat_sluFactor: ");

        /* first any free space currently taken for global COL matrix */
        VDEBUGIO("clearing..");
        Mat_sluDestroy(thee);

        /* initialize the slu object */
        VDEBUGIO("..Slu_ctor..");
        VASSERT( thee->slu == VNULL );
        thee->slu = Slu_ctor( thee->vmem, 1, thee->numR, thee->numR,
            thee->numA, thee->IA, thee->JA, thee->A);

        /* attempt to factor the matrix */
        VDEBUGIO("..factoring..");
        rc = Slu_factor(thee->slu);
        VDEBUGIO("..done.\n");

        /*  matrix has been successfully sparse factored */
        if (rc == 1) thee->state = FACTORED_STATE;

    /*  matrix is not ready to factor */
    } else if (thee->state == NULL_STATE) {
        VASSERT( 0 );
        rc = 0;

    /*  there is a very serious problem */
    } else {
        VASSERT( 0 );
        rc = 0;
    }

    return rc;
}

/*
 * ***************************************************************************
 * Routine:  Mat_sluSolve
 *
 * Purpose:  Performs a forward/backward solve using the sparse LU factors.
 *
 * Notes:    This requires that Mat_sluFactor has been previously called.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Mat_sluSolve(Mat *thee, int key, double *f, double *u)
{
    int rc;

    VASSERT( thee->format == SLU_FORMAT );

    rc = Slu_solve(thee->slu, key, f, u);
    return rc;
}

/*
 * ***************************************************************************
 * Routine:  Mat_sluDestroy
 *
 * Purpose:  Destroy the sparse LU factors for the system matrix.
 *
 * Notes:    This frees our <ia,ja,a> storage, and also the internal
 *           storage that was malloc'd by the sparse direct library.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_sluDestroy(Mat *thee)
{
    VASSERT( thee->format == SLU_FORMAT );

    if (thee->slu != VNULL) {
        if (thee->state != NULL_STATE ) {

            /* this frees <ia,ja,a> as well as everything else */
            Slu_dtor(&(thee->slu));

            /* new state */
            thee->state = NULL_STATE;
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_memChk
 *
 * Purpose:  Print the exact current malloc usage
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat_memChk(Mat *thee)
{
    if (thee->iMadeVmem) Vmem_print(thee->vmem);
}

