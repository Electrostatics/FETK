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
 * rcsid="$Id: hbtools.c,v 1.7 2010/08/12 05:19:22 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     hbtools.c
 *
 * Purpose:  Class Whb: converters and utilities.
 *
 * Author:   Burak Aksoylu, Stephen Bond, and Michael Holst
 * ***************************************************************************
 */

#include "hbtools_p.h"

VEMBED(rcsid="$Id: hbtools.c,v 1.7 2010/08/12 05:19:22 fetk Exp $")

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
 * Routine:  HBvec_matvec
 *
 * Purpose:  Special matrix-vector multiplication for HB.
 *
 *   Notes:  The input parameters are interpreted thusly:
 *
 *           key  =  0   standard product, u += G *u
 *                   1  transpose product, u += G'*u
 *
 *           Blocks which are entirely zero should be specified using
 *           NULL pointers.  The work vector should be of the same length
 *           as the number of rows in G21. This vector is only used if
 *           A12 != 0 or A22 != 0, otherwise it can be safely set to VNULL.
 *
 * Author:   Burak Aksoylu and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void HBvec_matvec(HBvec *thee, HBmat *Gmat, int key, Bvec *work)
{
    Bvec *u1 = thee->bv, *u2 = thee->bv2;

    if ( Gmat->type == GHB_TYPE ) { /* HB CASE */
        if (key == 0) {
            Bvec_matvec( u2, Gmat->A21, u1, 2, 0 );
        } else if (key == 1) {
            Bvec_matvec( u1, Gmat->A21, u2, 3, 0 );
        } else { VASSERT( 0 ); }
    } else if ( Gmat->type == GWM_TYPE ) { /* WMHB CASE */
        Bvec_copy(work, u2);
        if (key == 0) {
            Bvec_matvec( u2, Gmat->A21, u1, 2, 0 );
            Bvec_matvec( u1, Gmat->A12, work, 2, 0 );
            Bvec_matvec( u2, Gmat->A22, work, 2, 0 );
        } else if (key == 1) {
            Bvec_matvec( u2, Gmat->A12, u1, 3, 0 );
            Bvec_matvec( u1, Gmat->A21, work, 3, 0 );
            Bvec_matvec( u2, Gmat->A22, work, 3, 0 );
        } else { VASSERT( 0 ); }
    } else { VASSERT( 0 ); }

}

/*
 * ***************************************************************************
 * Routine:  HBmat_ctor
 *
 * Purpose:  The HBmat constructor.
 *
 * Author:   Stephen Bond 2002/01/07
 * ***************************************************************************
 */
VPUBLIC HBmat* HBmat_ctor(Vmem *vmem, const char *bname, int pnumB )
{
    char name[80];
    HBmat *thee = VNULL;

    VDEBUGIO("HBmat_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(HBmat) );
    if (vmem == VNULL) {
        sprintf(name, "%s", bname);
        thee->vmem = Vmem_ctor( name );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    thee->next = VNULL;

    /* product dimension; unknowns per spatial point */
    if ( ! ((1 <= pnumB) && (pnumB <= MAXV)) ) {
        Vnm_print(2,"HBmat_ctor: numB=<%d> invalid; setting numB=<1>", pnumB);
        pnumB = 1;
    }
    thee->numB = pnumB;

    VDEBUGIO("..done.\n");

    /* initialize algebraic structures */
    thee->type = ZERO_TYPE;
    thee->A12  = VNULL;
    thee->A21  = VNULL;
    thee->A22  = VNULL;

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  HBmat_dtor
 *
 * Purpose:  The HBmat destructor.
 *
 * Author:   Stephen Bond 2002/01/07
 * ***************************************************************************
 */
VPUBLIC void HBmat_dtor(HBmat **thee)
{
    if ((*thee) != VNULL) {

        /* destroy the algebraic structures */
        Bmat_dtor(&((*thee)->A12) );
        Bmat_dtor(&((*thee)->A21) );
        Bmat_dtor(&((*thee)->A22) );

        /* finally, destroy myself */
        VDEBUGIO("HBmat_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(HBmat), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;

    }
}

/*
 * ***************************************************************************
 * Routine:  HBvec_ctor
 *
 * Purpose:  The HBvec constructor.
 *
 * Author:   Stephen Bond 2002/01/07
 * ***************************************************************************
 */
VPUBLIC HBvec* HBvec_ctor(Vmem *vmem, const char *bname, int pnumB )
{
    char name[80];
    HBvec *thee = VNULL;

    VDEBUGIO("HBvec_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(HBvec) );
    if (vmem == VNULL) {
        sprintf(name, "%s", bname);
        thee->vmem = Vmem_ctor( name );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    thee->next = VNULL;

    /* product dimension; unknowns per spatial point */
    if ( ! ((1 <= pnumB) && (pnumB <= MAXV)) ) {
        Vnm_print(2,"HBvec_ctor: numB=<%d> invalid; setting numB=<1>", pnumB);
        pnumB = 1;
    }
    thee->numB = pnumB;

    VDEBUGIO("..done.\n");

    /* initialize algebraic structures */
    thee->state = 0;
    thee->bv    = VNULL;
    thee->bv2   = VNULL;

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  HBvec_dtor
 *
 * Purpose:  The HBvec destructor.
 *
 * Author:   Stephen Bond 2002/01/07
 * ***************************************************************************
 */
VPUBLIC void HBvec_dtor(HBvec **thee)
{
    if ((*thee) != VNULL) {

        /* destroy the algebraic structures */
        Bvec_dtor ( &((*thee)->bv) );
        Bvec_dtor ( &((*thee)->bv2) );

        /* finally, destroy myself */
        VDEBUGIO("HBvec_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(HBvec), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;

    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_ctorPoint
 *
 * Purpose:  Create a Bvec pointer to the tail of a Bvec.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC Bvec* Bvec_ctorPoint( Bvec *v, const char *name, int *ibase, int *numR)
{
    int p;
    char bname[15];
    Bvec *thee = VNULL;

    VDEBUGIO("Bvec_ctorPoint: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Bvec) );

    VDEBUGIO("..done.\n");

    strncpy(thee->name, name, 10);
    thee->numB = v->numB;

    /* THIS WORKS ONLY FOR SCALAR PROBLEMS! */
    /* NOTE: The idea we were using before was to create Bvec pointers  */
    /*       which were a collection of Vec pointers.  Each vec pointer */
    /*       looked like a regular vector, but was sharing it's double  */
    /*       array of data with another vector.  This way we were able  */
    /*       to have a pointer to the head and tail of a vector and use */
    /*       all the standard Matvec routines.  Unfortunately, this is  */
    /*       now broken since the Bvec's must have a contiguous memory  */
    /*       segment and the heads and tails are not contiguous objects.*/
    /*       For now we are just enforcing that numB == 1 and the old   */
    /*       method works.  The longer term solution appears to be to   */
    /*       copy the tail of the Bvec before calling the coarse solver.*/
    /*       The result can then be copied back.  This won't work for   */
    /*       head since that would kill the algorithmic complexity.     */
    /* BEGIN SCALAR ONLY SECTION */
    thee->u = &(v->u[ibase[0]]);
    thee->n = numR[0];
    thee->numR[0] = numR[0];
    VASSERT( thee->numB == 1 );
    /* END SCALAR ONLY SECTION   */

    /* create the pointers to the blocks */
    for (p=0; p<thee->numB; p++) {
        sprintf(bname, "%s_%d", thee->name, p);
        thee->VC[p] = Vec_ctorPoint( v->VC[p], bname, ibase[p], numR[p] );
    }

    return thee;

}

/*
 * ***************************************************************************
 * Routine:  Bvec_dtorPoint
 *
 * Purpose:  The block vec pointer destructor.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bvec_dtorPoint( Bvec **thee )
{
    int i;

    if ( (*thee) != VNULL ) {

        for (i=0; i<(*thee)->numB; i++) {
            Vec_dtorPoint( &((*thee)->VC[i]) );
        }

        VDEBUGIO("Bvec_dtorPoint: DESTROYING object..");
        Vmem_free( VNULL, 1, sizeof(Bvec), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Vec_ctorPoint
 *
 * Purpose:  Create a Vec pointer to the tail of a Vec.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC Vec *Vec_ctorPoint( Vec *v, const char *name, int ibase, int numR )
{
    Vec *thee = VNULL;

    VASSERT( (v->n - ibase) >= numR );

    VDEBUGIO("Vec_ctorPoint: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Vec) );

    VDEBUGIO("..done.\n");

    strncpy(thee->name, name, 10);
    thee->n = numR;

    /* set the array pointer */
    thee->u = &(v->u[ibase]);

    return thee;

}

/*
 * ***************************************************************************
 * Routine:  Vec_dtorPoint
 *
 * Purpose:  The vec pointer destructor.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Vec_dtorPoint( Vec **thee )
{
    if ( (*thee) != VNULL ) {

        VDEBUGIO("Vec_dtorPoint: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Vec), (void **)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bmat_ctorPoint
 *
 * Purpose:  Create a Bmat pointer to the tail of a Bmat.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC Bmat *Bmat_ctorPoint( Bmat *Ppro,
                              const char *name, int *ibase, int *numR )
{
    int p, numB = Bmat_numB(Ppro);
    char bname[15];
    Mat *Pb;
    Bmat *thee = VNULL;

    VDEBUGIO("Bmat_ctorPoint: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Bmat) );
    thee->vmem = Ppro->vmem;
    thee->iMadeVmem = 0;

    strncpy(thee->name, name, 10);
    thee->numB = numB;

    for (p=0; p<numB; p++) {
        Pb = Ppro->AD[p][p];
        sprintf(bname, "%s_%d%d", name, p, p );
        thee->AD[p][p] = Mat_ctorPoint( Pb, bname, ibase[p], numR[p] );
    }

    return thee;
}


/*
 * ***************************************************************************
 * Routine:  Mat_ctorPoint
 *
 * Purpose:  Create a Mat pointer to the tail of a Pro.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC Mat *Mat_ctorPoint( Mat *Pb, const char *name, int ibase, int numR )
{
    Mat *thee = VNULL;

    VASSERT( (Pb->numR - ibase) >= numR );

    VDEBUGIO("Mat_ctorPoint: CREATING object..");

    thee = Mat_ctor( Pb->vmem, name, numR, Pb->numC );

    /* set the array pointer */
    thee->IJA  = &(Pb->IJA[ibase]);
    thee->A    = Pb->A;
    thee->numO = Pb->IJA[ibase+numR] - Pb->IJA[ibase];
    thee->numZ = thee->numO;
    thee->numA = -1; /* HB CODE FOR "ARRAYS ARE JUST POINTERS" */
    thee->IA   = thee->IJA;
    thee->JA   = thee->IJA + numR + 1;
    thee->sym  = ISNOT_SYM;
    thee->format = ROW_FORMAT;
    thee->state = ASSEMBLED_STATE;

    VDEBUGIO("..done.\n");

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Bmat_dtorPoint
 *
 * Purpose:  The Bmat pointer destructor.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bmat_dtorPoint( Bmat **thee )
{
    int p, numB;

    if ( (*thee) != VNULL ) {

        VDEBUGIO("Bmat_dtorPoint: DESTROYING object..");

        numB = (*thee)->numB;

        for (p=0; p<numB; p++) {
            Mat_dtorPoint( &((*thee)->AD[p][p]) );
        }

        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Bmat), (void **)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat_dtorPoint
 *
 * Purpose:  The Mat pointer destructor.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Mat_dtorPoint( Mat **thee )
{
    if ( (*thee) != VNULL ) {

        VDEBUGIO("Mat_dtorPoint: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Mat), (void **)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  HBmat_printSp
 *
 * Purpose:  Print an HBmat in MATLAB sparse form.
 *
 * Author:   Stephen Bond 2002/08/11
 * ***************************************************************************
 */
VPUBLIC void HBmat_printSp(HBmat *thee, char *fname, int pflag)
{
    char rn[80];
    FILE *fp;

    strncpy(rn,"HBmat_printSp:",80);

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

    /* print the blocks in matlab sparse format */

    fprintf(fp,"%% Defining the A12 block\n");
    fprintf(fp,"%% ----------------------------------------\n");

    fclose(fp);

    if (thee->A12 != VNULL) {

        Bmat_printSp(thee->A12,fname,1);

    }

    fp=fopen(fname,"a");

    if (fp==VNULL) {
        Vnm_print(2, "%s problem opening file <%s>\n", rn, fname);
        return;
    }

    fprintf(fp,"%% Defining the A21 block\n");
    fprintf(fp,"%% ----------------------------------------\n");

    fclose(fp);

    if (thee->A21 != VNULL) {

        Bmat_printSp(thee->A21,fname,1);

    }

    fp=fopen(fname,"a");

    if (fp==VNULL) {
        Vnm_print(2, "%s problem opening file <%s>\n", rn, fname);
        return;
    }

    fprintf(fp,"%% Defining the A22 block\n");
    fprintf(fp,"%% ----------------------------------------\n");

    fclose(fp);

    if (thee->A22 != VNULL) {

        Bmat_printSp(thee->A22,fname,1);

    }

}

/*
 * ***************************************************************************
 * Routine:  Bmat_printDiriSp
 *
 * Purpose:  Print the Dirichlet info of a Bmat in MATLAB sparse form.
 *
 * Author:   Stephen Bond 2002/08/24
 * ***************************************************************************
 */
VPUBLIC void Bmat_printDiriSp(Bmat *thee, char *fname, int pflag)
{
    char rn[80];
    FILE *fp;
    int p;

    strncpy(rn,"Bmat_printDiriSp:",80);

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

    fprintf(fp,"%% %s matrix <%s> [dim=(%dx%d)]\n",
        rn, thee->name, Bmat_numRT(thee), Bmat_numCT(thee));
    fprintf(fp,"%% ----------------------------------------\n");
    fclose(fp);

    for (p=0; p<thee->numB; p++) {
        Mat_printDiriSp(thee->AD[p][p],fname,1);
    }


    fp=fopen(fname,"a");

    if (fp==VNULL) {
        Vnm_print(2, "%s problem opening file <%s>\n", rn, fname);
        return;
    }

    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%% Matlab code to generate the global array.\n");
    fprintf(fp,"%% ----------------------------------------\n");

    fprintf(fp,"%s_BR = [\n",thee->name);
    for (p=0; p<thee->numB; p++) {
        fprintf(fp,"  %s_BR\n",(thee->AD[p][p])->name);
    }

    fprintf(fp, "];\n\n");
    fprintf(fp,"%% ----------------------------------------\n");

    fprintf(fp,"%s_BC = [\n",thee->name);
    for (p=0; p<thee->numB; p++) {
        fprintf(fp,"  %s_BC\n",(thee->AD[p][p])->name);
    }

    fprintf(fp, "];\n\n");
    fprintf(fp,"%% ----------------------------------------\n");

    /* close file and return */
    fclose(fp);
}

/*
 * ***************************************************************************
 * Routine:  Mat_printDiriSp
 *
 * Purpose:  Print the Dirichlet info of a Mat in MATLAB sparse form.
 *
 * Author:   Stephen Bond 2002/08/24
 * ***************************************************************************
 */
VPUBLIC void Mat_printDiriSp(Mat *thee, char *fname, int pflag)
{
    char rn[80];
    FILE *fp;
    int i, numR, numC;

    numR = thee->numR;
    numC = thee->numC;

    strncpy(rn,"Mat_printDiriSp:",80);

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

    /* print the Dirichlet info in matlab sparse format */
    fprintf(fp,"%% %s matrix <%s> [dim=(%dx%d)]\n",
        rn, thee->name, thee->numR, thee->numC);

    if (thee->state != NULL_STATE) {

        fprintf(fp,"%% ----------------------------------------\n");
        fprintf(fp, "fprintf('Defining %s_RIJA..');", thee->name);
        fprintf(fp, "\n%s_RIJA = [\n", thee->name);

        for (i=0; i<(thee->numBR); i++) {
            fprintf(fp,"    %d\n", thee->BR[i] + 1 );
        }

        fprintf(fp, "];\n\n");

        fprintf(fp,"%% ----------------------------------------\n");
        fprintf(fp, "fprintf('Defining %s_CIJA..');", thee->name);
        fprintf(fp, "\n%s_CIJA = [\n", thee->name);

        for (i=0; i<(thee->numBC); i++) {
            fprintf(fp,"    %d\n", thee->BC[i] + 1 );
        }

        fprintf(fp, "];\n\n");

    }

    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%% Matlab code to generate sparse dir array.\n");
    fprintf(fp,"%% ----------------------------------------\n");

    if( (thee->state != NULL_STATE) && (thee->numBR > 0) ) {
        fprintf(fp,
          "%s_BR = sparse(%s_RIJA,ones(1,%d),ones(1,%d),%d,%d);\n",
          thee->name, thee->name, thee->numBR, thee->numBR, numR, 1);
    } else {
        fprintf(fp, "%s_BR = sparse(%d,%d);\n", thee->name, numR, 1);
    }

    fprintf(fp,"%% ----------------------------------------\n");

    if( (thee->state != NULL_STATE) && (thee->numBC > 0) ) {
        fprintf(fp,
          "%s_BC = sparse(%s_CIJA,ones(1,%d),ones(1,%d),%d,%d);\n",
          thee->name, thee->name, thee->numBC, thee->numBC, numC, 1);
    } else {
        fprintf(fp, "%s_BC = sparse(%d,%d);\n", thee->name, numC, 1);
    }

    /* close file and return */
    fclose(fp);
}

/*
 * ***************************************************************************
 * Routine:  Bmat_AD
 *
 * Purpose:  Return the Mat structure AD.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Mat *Bmat_AD(Bmat *thee, int p, int q)
{
    return thee->AD[p][q];
}

#if 0
/*
 * ***************************************************************************
 * Routine:  checkList
 *
 * Purpose:  Checks if an index is in a list.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPRIVATE int checkList( int *ilist, int numi, int idx )
{
    int i, thee;

    thee = 0;
    i = 0;

    while ( (thee == 0) && (i < numi) ) {
        if ( ilist[i] == idx ) {
            thee = 1;
        }
        i++;
    }

    return thee;
}
#endif
