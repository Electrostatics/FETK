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
 * rcsid="$Id: am.c,v 1.58 2010/08/12 05:19:12 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     am.c
 *
 * Purpose:  Class AM: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "am_p.h"

VEMBED(rcsid="$Id: am.c,v 1.58 2010/08/12 05:19:12 fetk Exp $")

/*
 * ***************************************************************************
 * Class AM: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_NAM)

#endif /* if !defined(VINLINE_NAM) */
/*
 * ***************************************************************************
 * Class AM: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  AM_ctor
 *
 * Purpose:  The AM constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC AM* AM_ctor(Vmem *vmem, Aprx *aprx)
{ 
    AM *thee = VNULL;

    VDEBUGIO("AM_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(AM) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "AM" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    /* hand-off of aprx pointer */
    VASSERT( VNULL != (thee->aprx = aprx) );

    /* no algebraic structures exist yet */
    thee->algExist = 0;

    /* basic structure data */
    thee->P  = VNULL;
    thee->A  = VNULL;
    thee->M  = VNULL;
    thee->f  = VNULL;
    thee->u  = VNULL;
    thee->ud = VNULL;
    thee->ui = VNULL;
    thee->ut = VNULL;
    thee->r  = VNULL;
    thee->w0 = VNULL;

    VDEBUGIO("..done.\n");

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  AM_dtor
 *
 * Purpose:  The AM destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_dtor(AM **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        /* destroy the block matrix storage arrays */
        if ( (*thee)->algExist ) {
            AM_destroy(*thee);
        }

        VDEBUGIO("AM_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(AM), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  AM_create
 *
 * Purpose:  Create the following internal Alg structures:
 * 
 *               A     ==> The tangent matrix (linearization operator)
 *               M     ==> The mass matrix
 *               W[]   ==> The node vectors
 *  
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_create(AM *thee)
{
    int numB;
    int numR[MAXV], numO[MAXV][MAXV], *IJA[MAXV][MAXV];
    MATsym sym[MAXV][MAXV];
    MATmirror mirror[MAXV][MAXV];
    MATformat frmt[MAXV][MAXV];

    if ( !thee->algExist ) {

        /* initialization key */
        thee->algExist = 1;

        /* node interaction; gives structure of matrix */
        Aprx_interactBlock( thee->aprx, thee->aprx->re, thee->aprx->re, 
			    sym, mirror, frmt, numR, numO, IJA );

        /* build sparse (square) block matrices (only integer structures) */
        numB = Aprx_numB(thee->aprx);
        thee->A = Bmat_ctor( thee->vmem, "A", numB, numR, numR, mirror );
        Bmat_initStructure( thee->A, frmt, sym, numO, IJA );

        /* now handle mass matrix (purposely use same mirror struct as A) */
        thee->M = Bmat_ctor( thee->vmem, "M", numB, numR, numR, mirror );
        Bmat_copyStructure( thee->M, thee->A );

        /* insert the boundary node information into A and M */
        Aprx_buildBRC( thee->aprx, thee->A, thee->M );

        /* NODE work vector construction */
        thee->f  = Bvec_ctor( thee->vmem, "f",  numB, numR );
        thee->u  = Bvec_ctor( thee->vmem, "u",  numB, numR );
        thee->ud = Bvec_ctor( thee->vmem, "ud", numB, numR );
        thee->ui = Bvec_ctor( thee->vmem, "ui", numB, numR );
        thee->ut = Bvec_ctor( thee->vmem, "ut", numB, numR );
        thee->r  = Bvec_ctor( thee->vmem, "r",  numB, numR );
        thee->w0 = Bvec_ctor( thee->vmem, "w0", numB, numR );

        /* get a pointer to prolongation and Bnode objects in geometry object */
        thee->P = Aprx_P( thee->aprx );

        /* evaluate the trace function u_d (and also u_i and u_t) */
        Aprx_evalTrace( thee->aprx, thee->ud, thee->ui, thee->ut );
    }
}

/*
 * ***************************************************************************
 * Routine:  AM_destroy
 *
 * Purpose:  Destroy the following internal Alg structures:
 *
 *               A     ==> The tangent matrix (linearization operator)
 *               M     ==> The mass matrix
 *               W[]   ==> The node vectors
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_destroy(AM *thee)
{
    if (thee->algExist) {

        /* reset the initialization key */
        thee->algExist = 0;

        /* kill the objects */
        Bmat_dtor( &(thee->A) );
        Bmat_dtor( &(thee->M) );
        Bvec_dtor( &(thee->f) );
        Bvec_dtor( &(thee->u) );
        Bvec_dtor( &(thee->ud) );
        Bvec_dtor( &(thee->ui) );
        Bvec_dtor( &(thee->ut) );
        Bvec_dtor( &(thee->r) );
        Bvec_dtor( &(thee->w0) );

    }
}

/*
 * ***************************************************************************
 * Routine:  AM_markRefine
 *
 * Purpose:  Mark a given mesh for refinement.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int AM_markRefine(AM *thee, int key, int color,
    int bkey, double elevel)
{
    int rc;

    /* make sure we have structure */
    AM_create(thee);

    /* mark the mesh */
    rc = Aprx_markRefine( thee->aprx, key, color, bkey, elevel,
             thee->u, thee->ud, thee->f, thee->r );

    /* return */
    return rc;
}

/*
 * ***************************************************************************
 * Routine:  AM_refine
 *
 * Purpose:  Refine the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int AM_refine(AM *thee, int rkey, int bkey, int pkey)
{
    int rc;

    /* destroy everything */
    AM_destroy(thee);

    /* refinement */
    rc = Aprx_refine(thee->aprx, rkey, bkey, pkey);

    /* recreate everything */
    AM_create(thee);

    /* return */
    return rc;
}

/*
 * ***************************************************************************
 * Routine:  AM_unRefine
 *
 * Purpose:  Un-refine the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int AM_unRefine(AM *thee, int rkey, int pkey)
{
    int rc;

    /* destroy everything */
    AM_destroy(thee);

    /* unrefinement */
    rc = Aprx_unRefine(thee->aprx, rkey, pkey);

    /* recreate everything */
    AM_create(thee);

    /* return */
    return rc;
}

/*
 * ***************************************************************************
 * Routine:  AM_deform
 *
 * Purpose:  Deform the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int AM_deform(AM *thee)
{
    int rc;

    /* deformation */
    rc = Aprx_deform(thee->aprx, thee->u);

    /* return */
    return rc;
}

/*
 * ***************************************************************************
 * Routine:  AM_read
 *
 * Purpose:  Read in the user-specified initial mesh given in the
 *           "MCSF" or "MCEF" format, and transform into our internal 
 *           datastructures.
 *
 *           Do a little more than a "Aprx_read", in that we also
 *           initialize the extrinsic and intrinsic spatial dimensions
 *           corresponding to the input mesh, and we also then build the
 *           reference elements.
 *
 * Notes:    See the documentation to Aprx_read for a description of the
 *           mesh input data file format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int AM_read(AM *thee, int key, Vio *sock)
{
    int rc;

    /* destroy everything */
    AM_destroy(thee);

    /* read in the mesh; return error if problems */
    rc = Aprx_read(thee->aprx,key,sock);

    /* recreate everything */
    AM_create(thee);

    /* return */
    return rc;
}

/*
 * ***************************************************************************
 * Routine:  AM_assem
 *
 * Purpose:  Assemble the linearized problem at a given level.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double AM_assem(AM *thee,
    int evalKey, int energyKey, int residKey, int tangKey, int massKey,
    int bumpKey,
    Bvec *u, Bvec *ud, Bvec *f, int ip[], double rp[])
{
    double energy = 0.0;

    /* make sure we have structure */
    AM_create(thee);

    /* assemble the linearized problem */
    energy = Aprx_assem( thee->aprx,
        evalKey, energyKey, residKey, tangKey, massKey,
        bumpKey,
        ip, rp, thee->A, thee->M, f, u, ud );

    /* return */
    return energy;
}

/*
 * ***************************************************************************
 * Routine:  AM_evalJ
 *
 * Purpose:  Assemble the energy functional at the current solution.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double AM_evalJ(AM *thee)
{
    int ip[10], evalKey, energyKey, residKey, tangKey, massKey, bumpKey;
    double rp[10], energy;

    /* make sure we have structure */
    AM_create(thee);

    /* compute the energy */
    evalKey   = 1;
    energyKey = 1;
    residKey  = 0;
    tangKey   = 0;
    massKey   = 0;
    bumpKey = 0;
    energy    = AM_assem(thee,
        evalKey, energyKey, residKey, tangKey, massKey,
        bumpKey,
        thee->u, thee->ud, thee->f, ip, rp);

    /* return */
    return energy;
}

/*
 * ***************************************************************************
 * Routine:  AM_evalFunc
 *
 * Purpose:  Evaluate a finite element function.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_evalFunc(AM *thee,
    int number, int block, int numPts, double *pts,
    double *vals, int *marks)
{
    /* make sure we have structure */
    AM_create(thee);

    /* function evaluation */
    Aprx_evalFunc( thee->aprx, thee->u, block, numPts, pts, vals, marks );
}

/*
 * ***************************************************************************
 * Routine:  AM_bndIntegral
 *
 * Purpose:  Perform a boundary integral.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_bndIntegral(AM *thee)
{
    /* make sure we have structure */
    AM_create(thee);

    /* boundary integral evaluation */
    Aprx_bndIntegral( thee->aprx, thee->u, thee->ud, thee->ut );
}

/*
 * ***************************************************************************
 * Routine:  AM_evalError
 *
 * Purpose:  Evaluate error in the current solution.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double AM_evalError(AM *thee, int pcolor, int key)
{
    int rc;

    /* make sure we have structure */
    AM_create(thee);

    /* error evaluation */
    rc = Aprx_evalError( thee->aprx,
             pcolor, key, thee->u, thee->ud, thee->ut );

    /* return */
    return rc;
}

/*
 * ***************************************************************************
 * Routine:  AM_applyDiriZero
 *
 * Purpose:  Apply zero dirichlet condition at a given level.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_applyDiriZero(AM *thee, Bvec *v)
{
    /* make sure we have structure */
    AM_create(thee);

    /* apply boundary condition */
    Bvec_bnd( v, thee->A, 0 );
}

/*
 * ***************************************************************************
 * Routine:  AM_iniGuess
 *
 * Purpose:  Setup an initial guess at a given level.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_iniGuess(AM *thee, Bvec *v)
{
    int i,j;

    /* make sure we have structure */
    AM_create(thee);

    /* apply initial condition */
    for (i=0; i<Bvec_numB(v); i++)
        for (j=0; j<Bvec_numRB(v,i); j++)
            Bvec_setB( v,i,j,Bvec_valB(thee->ui,i,j) );
}

/*
 * ***************************************************************************
 * Routine:  AM_part
 *
 * Purpose:  Partition the mesh using the matching Alg level.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int AM_part(AM *thee, int pkey, int pwht, int ppow)
{
    /* make sure we have structure */
    AM_create(thee);

    /* partition the mesh */
    return Aprx_part( thee->aprx, pkey, pwht, ppow );
}

/*
 * ***************************************************************************
 * Routine:  AM_partSet
 *
 * Purpose:  Set the partition color.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int AM_partSet(AM *thee, int pcolor)
{
    /* make sure we have structure */
    AM_create(thee);

    /* set partition */
    return Aprx_partSet( thee->aprx, pcolor );
}

/*
 * ***************************************************************************
 * Routine:  AM_partSmooth
 *
 * Purpose:  Do a partition smoothing.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int AM_partSmooth(AM *thee)
{
    /* make sure we have structure */
    AM_create(thee);

    /* smooth partition */
    return Aprx_partSmooth( thee->aprx );
}

/*
 * ***************************************************************************
 * Routine:  AM_printJ
 *
 * Purpose:  Print the energy.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_printJ(AM *thee)
{
    double energy;

    /* make sure we have structure */
    AM_create(thee);

    /* print energy */
    energy = AM_evalJ(thee);
    Vnm_print(2,"AM_printJ: Energy=<%g>\n", energy);
}

/*
 * ***************************************************************************
 * Routine:  AM_printA
 *
 * Purpose:  Print the system matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_printA(AM *thee)
{
    /* make sure we have structure */
    AM_create(thee);

    /* print A */
    Bmat_print( thee->A );
}

/*
 * ***************************************************************************
 * Routine:  AM_printAnoD
 *
 * Purpose:  Print the system matrix with Dirichlet rows/cols zeroed.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_printAnoD(AM *thee)
{
    /* make sure we have structure */
    AM_create(thee);

    /* print A */
    Bmat_printNoD( thee->A );
}

/*
 * ***************************************************************************
 * Routine:  AM_printAsp
 *
 * Purpose:  Print the system matrix in MATLAB sparse format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_printAsp(AM *thee, char *fname)
{
    /* make sure we have structure */
    AM_create(thee);

    /* print A */
    Bmat_printSp( thee->A, fname, 0 );
}

/*
 * ***************************************************************************
 * Routine:  AM_printAspNoD
 *
 * Purpose:  Print the system matrix in MATLAB sparse format with
 *           Dirichlet rows/cols zeroed.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_printAspNoD(AM *thee, char *fname)
{
    /* make sure we have structure */
    AM_create(thee);

    /* print A */
    Bmat_printSpNoD( thee->A, fname, 0 );
}

/*
 * ***************************************************************************
 * Routine:  AM_printP
 *
 * Purpose:  Print the prolongation matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_printP(AM *thee)
{
    /* make sure we have structure */
    AM_create(thee);

    /* print P */
    Bmat_print( thee->P );
}

/*
 * ***************************************************************************
 * Routine:  AM_printPsp
 *
 * Purpose:  Print the prolongation matrix in MATLAB sparse format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_printPsp(AM *thee, char *fname)
{
    /* make sure we have structure */
    AM_create(thee);

    /* print P */
    Bmat_printSp( thee->P, fname, 0 );
}

/*
 * ***************************************************************************
 * Routine:  AM_printV
 *
 * Purpose:  Print a specified vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_printV(AM *thee, int number)
{
    int maxw, W_f, W_u, W_ud, W_ui, W_ut, W_r, W_w0;
    Bvec *W[7];
    char *W_name[7];

    /* make sure we have structure */
    AM_create(thee);

    maxw  = 7;
    W_f   = 0,      /* rhs/residual                                         */
    W_u   = 1,      /* solution/error                                       */
    W_ud  = 2,      /* dirichlet function                                   */
    W_ui  = 3,      /* interior dirichlet function (initial guess)          */
    W_ut  = 4,      /* analytical solution (for testing)                    */
    W_r   = 5,      /* residual/temp vector                                 */
    W_w0  = 6,      /* work vector                                          */

    W[W_f]  = thee->f;
    W[W_u]  = thee->u;
    W[W_ud] = thee->ud;
    W[W_ui] = thee->ui;
    W[W_ut] = thee->ut;
    W[W_r]  = thee->r;
    W[W_w0] = thee->w0;

    W_name[W_f]  = "f";
    W_name[W_u]  = "u";
    W_name[W_ud] = "ud";
    W_name[W_ui] = "ui";
    W_name[W_ut] = "ut";
    W_name[W_r]  = "r";
    W_name[W_w0] = "w0";

    if (number == -W_ud) number = W_ud;
    if ((-maxw < number) && (number < 0)) {
        Vnm_print(0,"AM_printV: forming <w0=%s+ud> to print <w0>\n",
            W_name[-number]);
        Bvec_copy( W[W_w0], W[-number] );
        Bvec_axpy( W[W_w0], W[W_ud], 1. );
        Bvec_print( W[W_w0] );
    } else if ((0 <= number) && (number < maxw)) {
        Vnm_print(0,"AM_printV: printing <%s>\n", W_name[number]);
        Bvec_print( W[number] );
    }
}

/*
 * ***************************************************************************
 * Routine:  AM_printVsp
 *
 * Purpose:  Print a vector in MATLAB sparse format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_printVsp(AM *thee, int number, char *fname)
{
    int maxw, W_f, W_u, W_ud, W_ui, W_ut, W_r, W_w0;
    Bvec *W[7];
    char *W_name[7];

    /* make sure we have structure */
    AM_create(thee);

    maxw  = 7;
    W_f   = 0,      /* rhs/residual                                         */
    W_u   = 1,      /* solution/error                                       */
    W_ud  = 2,      /* dirichlet function                                   */
    W_ui  = 3,      /* interior dirichlet function (initial guess)          */
    W_ut  = 4,      /* analytical solution (for testing)                    */
    W_r   = 5,      /* residual/temp vector                                 */
    W_w0  = 6,      /* work vector                                          */

    W[W_f]  = thee->f;
    W[W_u]  = thee->u;
    W[W_ud] = thee->ud;
    W[W_ui] = thee->ui;
    W[W_ut] = thee->ut;
    W[W_r]  = thee->r;
    W[W_w0] = thee->w0;

    W_name[W_f]  = "f";
    W_name[W_u]  = "u";
    W_name[W_ud] = "ud";
    W_name[W_ui] = "ui";
    W_name[W_ut] = "ut";
    W_name[W_r]  = "r";
    W_name[W_w0] = "w0";

    if (number == -W_ud) number = W_ud;
    if ((-maxw < number) && (number < 0)) {
        Vnm_print(0,"AM_printVsp: forming <w0=%s+ud> to print <w0>\n",
            W_name[-number]);
        Bvec_copy( W[W_w0], W[-number] );
        Bvec_axpy( W[W_w0], W[W_ud], 1. );
        Bvec_printSp( W[W_w0], fname );
    } else if ((0 <= number) && (number < maxw)) {
        Vnm_print(0,"AM_printVsp: printing <%s>\n", W_name[number]);
        Bvec_printSp( W[number], fname );
    }
}

/*
 * ***************************************************************************
 * Routine:  AM_writeGEOM
 *
 * Purpose:  Write out a mesh in some format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_writeGEOM(AM *thee, Vio *sock,
    int defKey, int colKey, int chartKey, double gluVal, int fkey,
    int number, char *format)
{
    int maxw, W_f, W_u, W_ud, W_ui, W_ut, W_r, W_w0;
    Bvec *W[7];
    char *W_name[7];

    /* make sure we have structure */
    AM_create(thee);

    maxw  = 7;
    W_f   = 0,      /* rhs/residual                                         */
    W_u   = 1,      /* solution/error                                       */
    W_ud  = 2,      /* dirichlet function                                   */
    W_ui  = 3,      /* interior dirichlet function (initial guess)          */
    W_ut  = 4,      /* analytical solution (for testing)                    */
    W_r   = 5,      /* residual/temp vector                                 */
    W_w0  = 6,      /* work vector                                          */

    W[W_f]  = thee->f;
    W[W_u]  = thee->u;
    W[W_ud] = thee->ud;
    W[W_ui] = thee->ui;
    W[W_ut] = thee->ut;
    W[W_r]  = thee->r;
    W[W_w0] = thee->w0;

    W_name[W_f]  = "f";
    W_name[W_u]  = "u";
    W_name[W_ud] = "ud";
    W_name[W_ui] = "ui";
    W_name[W_ut] = "ut";
    W_name[W_r]  = "r";
    W_name[W_w0] = "w0";

    if (number == -W_ud) number = W_ud;
    if ((-maxw < number) && (number < 0)) {
        Vnm_print(0,"AM_writeGEOM: forming <w0=%s+ud> to print <w0>\n",
            W_name[-number]);
        Bvec_copy( W[W_w0], W[-number] );
        Bvec_axpy( W[W_w0], W[W_ud], 1. );
        Aprx_writeGEOM( thee->aprx,
            sock, defKey, colKey, chartKey, gluVal, fkey, W[W_w0], format );
    } else if ((0 <= number) && (number < maxw)) {
        Vnm_print(0,"AM_writeGEOM: printing <%s>\n", W_name[number]);
        Aprx_writeGEOM( thee->aprx,
            sock, defKey, colKey, chartKey, gluVal, fkey, W[number], format );
    }
}

/*
 * ***************************************************************************
 * Routine:  AM_writeSOL
 *
 * Purpose:  Write out a solution in some format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_writeSOL(AM *thee, Vio *sock, int number, char *format)
{
    int maxw, W_f, W_u, W_ud, W_ui, W_ut, W_r, W_w0;
    Bvec *W[7];
    char *W_name[7];

    /* make sure we have structure */
    AM_create(thee);

    maxw  = 7;
    W_f   = 0,      /* rhs/residual                                         */
    W_u   = 1,      /* solution/error                                       */
    W_ud  = 2,      /* dirichlet function                                   */
    W_ui  = 3,      /* interior dirichlet function (initial guess)          */
    W_ut  = 4,      /* analytical solution (for testing)                    */
    W_r   = 5,      /* residual/temp vector                                 */
    W_w0  = 6,      /* work vector                                          */

    W[W_f]  = thee->f;
    W[W_u]  = thee->u;
    W[W_ud] = thee->ud;
    W[W_ui] = thee->ui;
    W[W_ut] = thee->ut;
    W[W_r]  = thee->r;
    W[W_w0] = thee->w0;

    W_name[W_f]  = "f";
    W_name[W_u]  = "u";
    W_name[W_ud] = "ud";
    W_name[W_ui] = "ui";
    W_name[W_ut] = "ut";
    W_name[W_r]  = "r";
    W_name[W_w0] = "w0";

    if (number == -W_ud) number = W_ud;
    if ((-maxw < number) && (number < 0)) {
        Vnm_print(0,"AM_writeSOL: forming <w0=%s+ud> to print <w0>\n",
            W_name[-number]);
        Bvec_copy( W[W_w0], W[-number] );
        Bvec_axpy( W[W_w0], W[W_ud], 1. );
        Aprx_writeSOL( thee->aprx, sock, W[W_w0], format );
    } else if ((0 <= number) && (number < maxw)) {
        Vnm_print(0,"AM_writeSOL: printing <%s>\n", W_name[number]);
        Aprx_writeSOL( thee->aprx, sock, W[number], format );
    }
}

/*
 * ***************************************************************************
 * Routine:  AM_memChk
 *
 * Purpose:  Print the exact current malloc usage.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_memChk(AM *thee)
{
    if (thee->iMadeVmem)     Vmem_print(thee->vmem);
    if (thee->P    != VNULL) Bmat_memChk(thee->P);
    if (thee->A    != VNULL) Bmat_memChk(thee->A);
    if (thee->M    != VNULL) Bmat_memChk(thee->M);
    if (thee->f    != VNULL) Bvec_memChk(thee->f);
    if (thee->u    != VNULL) Bvec_memChk(thee->u);
    if (thee->ud   != VNULL) Bvec_memChk(thee->ud);
    if (thee->ui   != VNULL) Bvec_memChk(thee->ui);
    if (thee->ut   != VNULL) Bvec_memChk(thee->ut);
    if (thee->r    != VNULL) Bvec_memChk(thee->r);
    if (thee->w0   != VNULL) Bvec_memChk(thee->w0);
}

