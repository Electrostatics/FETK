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
 * rcsid="$Id: bvec.c,v 1.55 2010/08/12 05:18:26 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     bvec.c
 *
 * Purpose:  Class Bvec: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "bvec_p.h"

VEMBED(rcsid="$Id: bvec.c,v 1.55 2010/08/12 05:18:26 fetk Exp $")

/*
 * ***************************************************************************
 * Class Bvec: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_BAM)

/*
 * ***************************************************************************
 * Routine:  Bvec_numB
 *
 * Purpose:  Return the number of blocks.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bvec_numB(Bvec *thee)
{
    return thee->numB;
}

#endif /* if !defined(VINLINE_BAM) */
/*
 * ***************************************************************************
 * Class Bvec: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Bvec_ctor
 *
 * Purpose:  The block vector constructor (data array malloc'd by us).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Bvec* Bvec_ctor(Vmem *vmem,
    const char *name, int pnumB, int pnumR[MAXV])
{
    int i, toffset;
    char bname[15];
    Bvec *thee = VNULL;

    VDEBUGIO("Bvec_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Bvec) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Bvec" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    VDEBUGIO("..done.\n");

    strncpy(thee->name, name, 10);
    thee->coarse = VNULL;
    thee->fine   = VNULL;
    thee->numB   = pnumB;

    /* malloc the array */
    thee->n = 0;
    for (i=0; i<thee->numB; i++) {
        thee->numR[i] = pnumR[i];
        thee->n      += pnumR[i];
    }
    thee->iMallocU = 1;
    thee->u = Vmem_malloc( thee->vmem, thee->n, sizeof(double) );
    VASSERT( thee->u != VNULL );

    /* create the subblocks out of the array */
    toffset = 0;
    for (i=0; i<thee->numB; i++) {
        sprintf(bname, "%s_%d", name, i);
#if 0
        thee->VC[i] = (Vec*)Bvec_ctor4( thee->vmem,
            bname, thee->numR[i], &(thee->u[ toffset ]) );
#else
        thee->VC[i] = Vec_ctor2( thee->vmem,
            bname, thee->numR[i], &(thee->u[ toffset ]) );
#endif
        toffset += pnumR[i];
    }

    /* sanity check */
    VASSERT( Bvec_len(thee) == Bvec_numRT(thee) );

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_ctor2
 *
 * Purpose:  The block vector constructor (data array passed in).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Bvec* Bvec_ctor2(Vmem *vmem,
    const char *name, int pnumB, int pnumR[MAXV], double *data)
{
    int i, toffset;
    char bname[15];
    Bvec *thee = VNULL;

    VDEBUGIO("Bvec_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Bvec) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Bvec" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    VDEBUGIO("..done.\n");

    strncpy(thee->name, name, 10);
    thee->coarse = VNULL;
    thee->fine   = VNULL;
    thee->numB   = pnumB;

    /* malloc the array */
    thee->n = 0;
    for (i=0; i<thee->numB; i++) {
        thee->numR[i] = pnumR[i];
        thee->n      += pnumR[i];
    }
    thee->iMallocU = 0;
    thee->u = data;
    VASSERT( thee->u != VNULL );

    /* create the subblocks out of the array */
    toffset = 0;
    for (i=0; i<thee->numB; i++) {
        sprintf(bname, "%s_%d", name, i);
#if 0
        thee->VC[i] = (Vec*)Bvec_ctor4( thee->vmem,
            bname, thee->numR[i], &(thee->u[ toffset ]) );
#else
        thee->VC[i] = Vec_ctor2( thee->vmem,
            bname, thee->numR[i], &(thee->u[ toffset ]) );
#endif
        toffset += pnumR[i];
    }

    /* sanity check */
    VASSERT( Bvec_len(thee) == Bvec_numRT(thee) );

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_ctor3
 *
 * Purpose:  The vector constructor (data array malloc'd by us).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Bvec* Bvec_ctor3(Vmem *vmem, const char *name, int length)
{
    Bvec *thee = VNULL;

    VDEBUGIO("Bvec_ctor3: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Bvec) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Bvec" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    VDEBUGIO("..done.\n");

    strncpy(thee->name, name, 10);
    thee->coarse = VNULL;
    thee->fine   = VNULL;
    thee->numB   = 0; /* there are no sub-blocks! */

    /* malloc the array */
    thee->n = length;
    thee->iMallocU = 1;
    if (thee->n > 0) {
        thee->u = Vmem_malloc( thee->vmem, thee->n, sizeof(double) );
        VASSERT( thee->u != VNULL );
    }

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_ctor4
 *
 * Purpose:  The vector constructor (data array passed in).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Bvec* Bvec_ctor4(Vmem *vmem, const char *name, int length, double *data)
{
    Bvec *thee = VNULL;

    VDEBUGIO("Bvec_ctor4: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Bvec) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Bvec" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    VDEBUGIO("..done.\n");

    strncpy(thee->name, name, 10);
    thee->coarse = VNULL;
    thee->fine   = VNULL;
    thee->numB   = 0; /* there are no sub-blocks! */

    /* snag the array */
    thee->n = length;
    thee->iMallocU = 0;
    if (thee->n > 0) {
        thee->u = data;
        VASSERT( thee->u != VNULL );
    }

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_dtor
 *
 * Purpose:  The block vector destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_dtor(Bvec **thee)
{
    int i;

    /* VASSERT( (*thee) != VNULL ); */
    if ((*thee) != VNULL) {

        /* first free any coarse guy */
        if ( (*thee)->coarse != VNULL ) {
            Bvec_dtor( &((*thee)->coarse) );
        }

        /* now free block vector substructure */
        for (i=0; i<(*thee)->numB; i++) {
#if 0
            Bvec_dtor( (Bvec**)&((*thee)->VC[i]) );
#else
            Vec_dtor( &((*thee)->VC[i]) );
#endif
        }

        /* now free actual contiguous block vector storage */
        if ( (*thee)->iMallocU == 1 ) {
            Vmem_free( (*thee)->vmem, (*thee)->n, sizeof(double),
                (void**)&((*thee)->u) );
        }

        /* cleanup */
        VDEBUGIO("Bvec_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Bvec), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_createVectors
 *
 * Purpose:  Create a set of vectors with duplicate attributes.
 *
 * Notes:    We actually do this using contiguous memory, i.e., each
 *           vector follows contiguously from the preceeding one.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_createVectors(Bvec *thee, Bvec *vecs[], int num)
{
    int i, toffset;
    char name[15];
    double *data;

    /* malloc the space */
    data = Vmem_malloc( thee->vmem, (num * thee->n), sizeof(double) );
    VASSERT( thee->u != VNULL );

    /* set up the block vectors using this space */
    toffset = 0;
    for (i=0; i<num; i++) {
        sprintf(name, "w%d", i);
        vecs[i] = Bvec_ctor2(thee->vmem, name, thee->numB, thee->numR,
            &(data[ toffset ]) );
        toffset += thee->n;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_destroyVectors
 *
 * Purpose:  Destroy set of vectors previously created by Bvec_createVectors.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_destroyVectors(Bvec *thee, Bvec *vecs[], int num)
{
    int i;
    double *u;

    /* free the space (first vector has the space pointer) */
    u = (vecs[0])->u;
    Vmem_free( thee->vmem, (num * thee->n), sizeof(double), (void**)&u );

    /* kill the block vectors */
    for (i=0; i<num; i++) {
        Bvec_dtor( &(vecs[i]) );
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_createVecMat
 *
 * Purpose:  Create a matrix from columns of vectors.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_createVecMat(Bvec *thee, Bvec *vecs[], int num, Mat **mat)
{
    double *data;

    /* create the vectors and snag the data pointer */
    Bvec_createVectors(thee, vecs, num);
    data = vecs[0]->u;

    /* set up the mat structure using this space */
    *mat = Mat_ctor( thee->vmem, "VecMat", thee->n, num );
    Mat_initStructure( *mat, CFL_FORMAT, ISNOT_SYM, 0, VNULL, data );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_destroyVecMat
 *
 * Purpose:  Destroy matrix previously created by Bvec_createVecMat.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_destroyVecMat(Bvec *thee, Bvec *vecs[], int num, Mat **mat)
{
    /* destroy the vectors */
    Bvec_destroyVectors(thee, vecs, num);

    /* destroy the mat */
    Mat_dtor( mat );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_len
 *
 * Purpose:  Return the total number of rows.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bvec_len(Bvec *thee)
{
    return thee->n;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_addr
 *
 * Purpose:  Return a pointer to the total data array.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double* Bvec_addr(Bvec *thee)
{
    return thee->u;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_val
 *
 * Purpose:  Return value of component of vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Bvec_val(Bvec *thee, int i)
{
    return Vec_val( (Vec*)thee, i );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_set
 *
 * Purpose:  Set value of component of vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_set(Bvec *thee, int i, double val)
{
    Vec_set( (Vec*)thee, i, val );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_nrm1
 *
 * Purpose:  1-norm of a block vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Bvec_nrm1(Bvec *thee)
{
    return Vec_nrm1( (Vec*)thee );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_nrm2
 *
 * Purpose:  2-norm of a block vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Bvec_nrm2(Bvec *thee)
{
    return Vec_nrm2( (Vec*)thee );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_nrm8
 *
 * Purpose:  oo-norm of a block vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Bvec_nrm8(Bvec *thee)
{
    return Vec_nrm8( (Vec*)thee );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_dif1
 *
 * Purpose:  1-norm of the difference of two block vectors.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Bvec_dif1(Bvec *thee, Bvec *v)
{
    return Vec_dif1( (Vec*)thee, (Vec*)v );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_dif2
 *
 * Purpose:  2-norm of the difference of two block vectors.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Bvec_dif2(Bvec *thee, Bvec *v)
{
    return Vec_dif2( (Vec*)thee, (Vec*)v );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_dif8
 *
 * Purpose:  oo-norm of the difference of two block vectors.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Bvec_dif8(Bvec *thee, Bvec *v)
{
    return Vec_dif8( (Vec*)thee, (Vec*)v );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_dot
 *
 * Purpose:  Dot product of two block vectors.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Bvec_dot(Bvec *thee, Bvec *v)
{
    return Vec_dot( (Vec*)thee, (Vec*)v );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_init
 *
 * Purpose:  Initialize a block vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_init(Bvec *thee, double val)
{
    Vec_init( (Vec*)thee, val );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_scal
 *
 * Purpose:  Scale a block vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_scal(Bvec *thee, double val)
{
    Vec_scal( (Vec*)thee, val );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_copy
 *
 * Purpose:  Copy a block vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_copy(Bvec *thee, Bvec *v)
{
    Vec_copy( (Vec*)thee, (Vec*)v );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_axpy
 *
 * Purpose:  Saxpy for a block vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_axpy(Bvec *thee, Bvec *v, double val)
{
    Vec_axpy( (Vec*)thee, (Vec*)v, val );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_print
 *
 * Purpose:  Print the block vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_print(Bvec *thee)
{
    int i;
    char rn[80];
    const int MaxRows = 100;

    strncpy(rn,"Bvec_print:",80);

    Vnm_print(0, "%s printing <%s> [dim=(%dx1)]\n",
       rn, thee->name, Bvec_numRT(thee) );

    if (Bvec_numRT(thee) > MaxRows) {
        Vnm_print(0,"%svector too large to view....skipping.\n", rn);
        return;
    } else {
        for (i=0; i<thee->numB; i++) {
            Vec_print( thee->VC[i] );
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_printSp
 *
 * Purpose:  Print the block vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_printSp(Bvec *thee, char *fname)
{
    char rn[80];
    FILE *fp;
    int i;

    strncpy(rn,"Bvec_printSp:",80);

    Vnm_print(0, "%s printing <%s> [dim=(%dx1)] to file <%s>..",
        rn, thee->name, Bvec_numRT(thee), fname);

    fp=fopen(fname,"w");

    if (fp==VNULL) {
        Vnm_print(2, "%s problem opening file <%s>\n", rn, fname);
        return;
    }

    fprintf(fp,"%% %s vector <%s> [dim=(%dx1)]\n",
        rn, thee->name, Bvec_numRT(thee) );
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp, "fprintf('Defining the blocks of %s..\\n');\n\n", thee->name);
    fclose(fp);

    for (i=0; i<thee->numB; i++) {
        Vec_printSp( thee->VC[i], fname, 1 );
    }

    fp=fopen(fname,"a");

    if (fp==VNULL) {
        Vnm_print(2, "%s problem opening file <%s>\n", rn, fname);
        return;
    }

    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%% Matlab code to generate the block vector.\n");
    fprintf(fp,"%% ----------------------------------------\n");
    fprintf(fp,"%s = [\n",thee->name);
    for (i=0; i<thee->numB; i++) {
        fprintf(fp,"  %s\n",(thee->VC[i])->name);
    }
    fprintf(fp, "];\n\n");
    fprintf(fp,"%% ----------------------------------------\n");
    fclose(fp);

    Vnm_print(0,"..done.\n");
}

/*
 * ***************************************************************************
 * Routine:  Bvec_diagScale
 *
 * Purpose:  Apply inverse of diagonal to a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_diagScale(Bvec *thee, Bmat *amat, Bvec *f)
{
    int p;
    Vec *uu, *ff;
    Mat *AA;

    /* intialize the result */
    Bvec_init(thee, 0.0);

    /* invert the diagonal using each diagonal block */
    for (p=0; p<amat->numB; p++) {

        uu = thee->VC[p];
        ff = f->VC[p];
        AA = amat->AD[p][p];
        Vec_diagScale(uu, AA, ff);

    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_matvec
 *
 * Purpose:  Block matrix times vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_matvec(Bvec *thee, Bmat *amat, Bvec *v, int pkey, int part)
{
    int p, q, pp, qq, qpart, key;
    Vec *uu, *vv;
    Mat *AA;

    /* intialize the result */
    if ((pkey==0) || (pkey==1)) {
        Bvec_init(thee, 0.0);
    } else if ((pkey==2) || (pkey==3)) {
        /* no-op: we just accumulate (u+=A*v or u+=A'*v) */
    } else {
        VASSERT(0);
    }

    /* use all of each block matrix */
    qpart = 0;

    /* do the product */
    for (p=0; p<amat->numB; p++) {
        uu = thee->VC[p];

        for (q=0; q<amat->numB; q++) {
            vv = v->VC[q];

            if (pkey) {
               pp = q;
               qq = p;
            } else {
               pp = p;
               qq = q;
            }

            AA = amat->AD[pp][qq];

            if (amat->mirror[pp][qq]) {
                if ((pkey==0) || (pkey==2)) {
                    key = 3; /* accumulate: u=A'*v */
                } else if ((pkey==1) || (pkey==3)) {
                    key = 2; /* accumulate: u=A*v */
                } else {
                    VASSERT(0);
                }
            } else {
                if ((pkey==0) || (pkey==2)) {
                    key = 2; /* accumulate: u=A*v */
                } else if ((pkey==1) || (pkey==3)) {
                    key = 3; /* accumulate: u=A'*v */
                } else {
                    VASSERT(0);
                }
            }

            Vec_matvec(uu, AA, vv, key, qpart);
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_smooth
 *
 * Purpose:  Generic smoothing operator (for a general YSMP-based matrix).
 *
 * Notes:    The input parameters are interpreted thusly:
 *
 *               key    = smooth with A or A' (0=A, 1=A')
 *               ioflag = debug output level (0=normal, 1=none, 2=lots, ... )
 *               meth   = smoother choice (0=jac, 1=gs, ... )
 *               adj    = adjoint choice (0=normal, 1=adjoint)
 *               itmax  = number of iterations to do (the maximum allowed)
 *               etol   = error tolerance (currently ignored)
 *               omega  = SOR parameter (currently ignored)
 *
 *            meth==1, adj==0  : Forward Gauss-Seidel
 *               u = (D + L)^{-1}*(f - U*u)
 *            meth==1, adj==1  : Adjoint Gauss-Seidel
 *               u = (D + U)^{-1}*(f - L*u)
 *            meth==2 : Self-adjoint or Symmetric Gauss-Seidel
 *               Apply (meth==1, adj==0) then (meth==1, adj==1)
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bvec_smooth(Bvec *thee, Bmat *amat, Bvec *f, Bvec *w,
    int key, int ioflag, int meth, int adj, int itmax, double etol,
    double omega)
{
    int i, j, k, p, q, iters, numB, numR;
    int *IA, *JA;
    double *A, *uu, *ww, *ff, *diag, *offU, *offL;
    char rn[80];
    strncpy(rn,"Bvec_smooth:",80);

    VASSERT( etol   == 0. );
    VASSERT( ioflag == 1 );

    /* some local variable pointers for speed and readability */
    numB = Bmat_numB(amat);

    /* check some dimensions of vector/blocks */
    VASSERT(Bvec_numB(thee) == Bvec_numB(f));
    VASSERT(Bvec_numB(thee) == Bvec_numB(w));
    VASSERT(Bvec_numB(thee) == Bmat_numB(amat));
    for (p=0; p<numB; p++) {
        VASSERT(Bvec_numRB(f,p) == Bvec_numRB(w,p));
        VASSERT(Bvec_numRB(f,p) == Bvec_numRB(thee,p));
        for (q=0; q<numB; q++) {
            VASSERT(Bmat_numC(amat,p,q) == Bvec_numRB(thee,q));
            VASSERT(Bmat_numR(amat,p,q) == Bvec_numRB(f,p));
        }
    }

    /* Gauss-Seidel smoother */
    if ( (meth == 1) | (meth == 2) ) {

        iters = 0;
        while ((iters < itmax) && (!Vnm_sigInt())) {
            iters++;

            if ( (adj == 0) | (meth == 2) ) {

                /* pull off (strict) upper triangle times old guy */
                for (p=0; p<numB; p++) {
                    numR = Bvec_numRB(thee,p);
                    ww   = Bvec_addrB(w,p);
                    ff   = Bvec_addrB(f,p);
                    uu   = Bvec_addrB(thee,p);

                    /* diag blocks: pull off only strict upper triangle */
                    IA = Bmat_IA(amat,p,p);
                    JA = Bmat_JA(amat,p,p);
                    A  = Bmat_A(amat,p,p);
                    diag = Bmat_diag(amat,p,p);
                    if( key==0 ) {       /* smooth(u,A,f) */
                      offU = Bmat_offU(amat,p,p);
                      offL = Bmat_offL(amat,p,p);
                    } else { /* ( key==1 ) smooth(u,A',f) */
                      offU = Bmat_offL(amat,p,p);
                      offL = Bmat_offU(amat,p,p);
                    }

                    for (i=0; i<numR; i++) {
                        /* diag block initializes ww */
                        ww[i] = ff[i];
                        /* now handle this row */
                        for (k=IA[i]; k<IA[i+1]; k++) {
                            j = JA[k];
                            ww[i] -= ( offU[k] * uu[j] );
                        }
                    }

                    /* off-diag blocks: pull off entire matrix */
                    for (q=p+1; q<numB; q++) {
                        uu = Bvec_addrB(thee,q);
                        if( key==0 ) {       /* smooth(u,A,f) */
                          VASSERT( ROW_FORMAT == Bmat_format(amat,p,q) );
                          IA = Bmat_IA(amat,p,q);
                          JA = Bmat_JA(amat,p,q);
                          A  = Bmat_A(amat,p,q);
                        } else { /* ( key==1 ) smooth(u,A',f) */
                          VASSERT( COL_FORMAT == Bmat_format(amat,q,p) );
                          IA = Bmat_IA(amat,q,p);
                          JA = Bmat_JA(amat,q,p);
                          A  = Bmat_A(amat,q,p);
                        }

                        for (i=0; i<numR; i++) {
                            /* ww is initialized by diag block above */
                            /* now handle this row, and corres. column */
                            for (k=IA[i]; k<IA[i+1]; k++) {
                                j = JA[k];
                                ww[i] -= ( A[k] * uu[j] );
                            }
                        }
                    }
                }

                /* now solve lower triangular system with "w" as RHS */
                for (p=0; p<numB; p++) {
                    ww   = Bvec_addrB(w,p);

                    /* off-diag blocks: solve using prev diag result */
                    for (q=0; q<p; q++) {
                        numR = Bvec_numRB(thee,q);
                        uu = Bvec_addrB(thee,q);

                        if( key==0 ) {       /* smooth(u,A,f) */
                          VASSERT( COL_FORMAT == Bmat_format(amat,p,q) );
                          IA = Bmat_IA(amat,p,q);
                          JA = Bmat_JA(amat,p,q);
                          A  = Bmat_A(amat,p,q);
                        } else { /* ( key==1 ) smooth(u,A',f) */
                          VASSERT( ROW_FORMAT == Bmat_format(amat,q,p) );
                          IA = Bmat_IA(amat,q,p);
                          JA = Bmat_JA(amat,q,p);
                          A  = Bmat_A(amat,q,p);
                        }
                        for (i=0; i<numR; i++) {
                            for (k=IA[i]; k<IA[i+1]; k++) {
                                j = JA[k];
                                ww[j] -= ( A[k] * uu[i] );
                            }
                        }
                    }

                    /* diag blocks: solve by column */
                    numR = Bvec_numRB(thee,p);
                    uu = Bvec_addrB(thee,p);

                    IA = Bmat_IA(amat,p,p);
                    JA = Bmat_JA(amat,p,p);
                    A  = Bmat_A(amat,p,p);
                    diag = Bmat_diag(amat,p,p);
                    if( key==0 ) {       /* smooth(u,A,f) */
                      offU = Bmat_offU(amat,p,p);
                      offL = Bmat_offL(amat,p,p);
                    } else { /* ( key==1 ) smooth(u,A',f) */
                      offU = Bmat_offL(amat,p,p);
                      offL = Bmat_offU(amat,p,p);
                    }

                    for (i=0; i<numR; i++) {
                        /* solve for guy on diag in current row */
                        uu[i] = ww[i] / diag[i];
                        /* propagate result column-at-a-time */
                        for (k=IA[i]; k<IA[i+1]; k++) {
                            j = JA[k];
                            ww[j] -= ( offL[k] * uu[i] );
                        }
                    }

                }

            }

            if ( (adj == 1) | (meth == 2) ) {


                /* pull off (strict) lower triangle times old guy */
                for (p=0; p<numB; p++) {
                    numR = Bvec_numRB(thee,p);
                    ww   = Bvec_addrB(w,p);
                    ff   = Bvec_addrB(f,p);
                    uu = Bvec_addrB(thee,p);

                    /* diag blocks: pull off only strict lower triangle */
                    IA = Bmat_IA(amat,p,p);
                    JA = Bmat_JA(amat,p,p);
                    A  = Bmat_A(amat,p,p);
                    diag = Bmat_diag(amat,p,p);
                    if( key==0 ) {       /* smooth(u,A,f) */
                      offU = Bmat_offU(amat,p,p);
                      offL = Bmat_offL(amat,p,p);
                    } else { /* ( key==1 ) smooth(u,A',f) */
                      offU = Bmat_offL(amat,p,p);
                      offL = Bmat_offU(amat,p,p);
                    }

                    for (i=0; i<numR; i++) {
                        ww[i] = ff[i];
                    }
                    for (i=0; i<numR; i++) {
                        for (k=IA[i]; k<IA[i+1]; k++) {
                            j = JA[k];
                            ww[j] -= ( offL[k] * uu[i] );
                        }
                    }

                    /* off-diag blocks: pull off entire matrix */
                    for (q=0; q<p; q++) {
                        numR = Bvec_numRB(thee,q);
                        uu = Bvec_addrB(thee,q);

                        if( key==0 ) {       /* smooth(u,A,f) */
                          VASSERT( COL_FORMAT == Bmat_format(amat,p,q) );
                          IA = Bmat_IA(amat,p,q);
                          JA = Bmat_JA(amat,p,q);
                          A  = Bmat_A(amat,p,q);
                        } else { /* ( key==1 ) smooth(u,A',f) */
                          VASSERT( ROW_FORMAT == Bmat_format(amat,q,p) );
                          IA = Bmat_IA(amat,q,p);
                          JA = Bmat_JA(amat,q,p);
                          A  = Bmat_A(amat,q,p);
                        }
                        for (i=0; i<numR; i++) {
                            /* ww is initialized by diag block above */
                            /* now handle this row, and corres. column */
                            for (k=IA[i]; k<IA[i+1]; k++) {
                                j = JA[k];
                                ww[j] -= ( A[k] * uu[i] );
                            }
                        }
                    }
                }

                /* now solve upper triangular system with "w" as RHS */
                for (q=numB-1; q>=0; q--) {
                    numR = Bvec_numRB(thee,q);
                    ww   = Bvec_addrB(w,q);
                    uu   = Bvec_addrB(thee,q);

                    /* diag blocks: solve by row */
                    IA = Bmat_IA(amat,q,q);
                    JA = Bmat_JA(amat,q,q);
                    A  = Bmat_A(amat,q,q);
                    diag = Bmat_diag(amat,q,q);
                    if( key==0 ) {       /* smooth(u,A,f) */
                      offU = Bmat_offU(amat,q,q);
                      offL = Bmat_offL(amat,q,q);
                    } else { /* ( key==1 ) smooth(u,A',f) */
                      offU = Bmat_offL(amat,q,q);
                      offL = Bmat_offU(amat,q,q);
                    }

                    for (i=numR-1; i>=0; i--) {
                        /* solve row-at-a-time */
                        for (k=IA[i]; k<IA[i+1]; k++) {
                            j = JA[k];
                            ww[i] -= ( offU[k] * uu[j] );
                        }
                        uu[i] = ww[i] / diag[i];
                    }

                    /* off-diag blocks: pull-off using prev result */
                    for (p=0; p<q; p++) {
                        numR = Bvec_numRB(w,p);
                        ww = Bvec_addrB(w,p);

                        if( key==0 ) {       /* smooth(u,A,f) */
                          VASSERT( ROW_FORMAT == Bmat_format(amat,p,q) );
                          IA = Bmat_IA(amat,p,q);
                          JA = Bmat_JA(amat,p,q);
                          A  = Bmat_A(amat,p,q);
                        } else { /* ( key==1 ) smooth(u,A',f) */
                          VASSERT( COL_FORMAT == Bmat_format(amat,q,p) );
                          IA = Bmat_IA(amat,q,p);
                          JA = Bmat_JA(amat,q,p);
                          A  = Bmat_A(amat,q,p);
                        }
                        for (i=0; i<numR; i++) {
                            /* now handle this row, and corres. column */
                            for (k=IA[i]; k<IA[i+1]; k++) {
                                j = JA[k];
                                ww[i] -= ( A[k] * uu[j] );
                            }
                        }
                    }
                }
            }
        }
    } else {
        Vnm_print(2,"%s Invalid smoother specified..\n", rn);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_bnd
 *
 * Purpose:  Apply boundary condition.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_bnd(Bvec *thee, Bmat *bmat, int key)
{
    int i;

    VASSERT( Bvec_numB(thee) == Bmat_numB(bmat) );

    for (i=0; i<Bvec_numB(thee); i++) {
        Vec_bnd( thee->VC[i], bmat->AD[i][i], key );
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_memChk
 *
 * Purpose:  Print the exact current malloc usage.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_memChk(Bvec *thee)
{
    if (thee->iMadeVmem) Vmem_print(thee->vmem);
}

/*
 * ***************************************************************************
 * Routine:  Bvec_numRT
 *
 * Purpose:  Return the total number of rows.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bvec_numRT(Bvec *thee)
{
    int i, numRT;

    numRT = 0;
    for (i=0; i<thee->numB; i++) {
        numRT += Bvec_numRB(thee,i);
    }

    return numRT;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_numR
 *
 * Purpose:  Return the size of a block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Bvec_numRB(Bvec *thee, int i)
{
    return Vec_len(thee->VC[i]);
}

/*
 * ***************************************************************************
 * Routine:  Bvec_addrB
 *
 * Purpose:  Return a pointer to the data in a block.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double* Bvec_addrB(Bvec *thee, int i)
{
    return Vec_addr(thee->VC[i]);
}

/*
 * ***************************************************************************
 * Routine:  Bvec_val
 *
 * Purpose:  Return value of component of a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Bvec_valB(Bvec *thee, int i, int which)
{
    return (Vec_addr(thee->VC[i]))[which];
}

/*
 * ***************************************************************************
 * Routine:  Bvec_set
 *
 * Purpose:  Set value of component of a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_setB(Bvec *thee, int i, int which, double val)
{
    (Vec_addr(thee->VC[i]))[which] = val;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_addTo
 *
 * Purpose:  Add value to component of a vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_addToB(Bvec *thee, int i, int which, double val)
{
    (Vec_addr(thee->VC[i]))[which] += val;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_initB
 *
 * Purpose:  Initialize a particular block of a block vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_initB(Bvec *thee, int i, double val)
{
    Vec_init( thee->VC[i], val );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_absLog
 *
 * Purpose:  Log of abs value of entries of block vector, shifted by <val>
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_absLog(Bvec *thee, double val)
{
    int p;

    for (p=0; p<thee->numB; p++) {
        Vec_absLog( thee->VC[p], val );
    }
}

