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
 * rcsid="$Id: pde.c,v 1.8 2010/08/12 05:19:16 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     pde.c
 *
 * Purpose:  Class PDE: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "pde_p.h"

VEMBED(rcsid="$Id: pde.c,v 1.8 2010/08/12 05:19:16 fetk Exp $")

/*
 * ***************************************************************************
 * Class PDE: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_PDE)

/*
 * ***************************************************************************
 * Routine:  PDE_setDim
 *
 * Purpose:  Set the extrinsic spatial dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void PDE_setDim(PDE *thee, int d)
{
    thee->dim = d;
}

/*
 * ***************************************************************************
 * Routine:  PDE_setDimII
 *
 * Purpose:  Set the intrinsic spatial dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void PDE_setDimII(PDE *thee, int d)
{
    thee->dimII = d;
}

/*
 * ***************************************************************************
 * Routine:  PDE_dim
 *
 * Purpose:  Return the extrinsic spatial dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int PDE_dim(PDE *thee)
{
    return thee->dim;
}

/*
 * ***************************************************************************
 * Routine:  PDE_dimII
 *
 * Purpose:  Return the intrinsic spatial dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int PDE_dimII(PDE *thee)
{
    return thee->dimII;
}

/*
 * ***************************************************************************
 * Routine:  PDE_vec
 *
 * Purpose:  Return the PDE product space dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int PDE_vec(PDE *thee)
{
    return thee->vec;
}

#endif /* if !defined(VINLINE_PDE) */
/*
 * ***************************************************************************
 * Class PDE: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  bisectEdge_default
 *
 * Purpose:  DEFAULT: Define the way manifold edges are bisected.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void bisectEdge_default(int dim, int dimII,
    int edgeType, int chart[], double vx[][3])
{
    int i;
    for (i=0; i<dimII; i++)
        vx[2][i] = .5 * (vx[0][i] + vx[1][i]);
}

/*
 * ***************************************************************************
 * Routine:  mapBoundary_default
 *
 * Purpose:  DEFAULT: Define the way the manifold boundary is treated.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void mapBoundary_default(int dim, int dimII,
    int vertexType, int chart, double vx[3])
{
}

/*
 * ***************************************************************************
 * Routine:  markSimplex_default
 *
 * Purpose:  DEFAULT: Simplex marking routine for refinement.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int markSimplex_default(int dim, int dimII,
    int simplexType, int faceType[4], int vertexType[4],
    int chart[], double vx[][3], void *data)
{
    int j, k, less, more;
    double radius, d[4];

    /* radius = radius of a refinement sphere for testing */
    radius = 0.1; /* must be > 0 */
    less = 0;
    more = 0;
    for (j=0; j<dim+1; j++) {
        d[j] = 0.0;
        for (k=0; k<3; k++)
            d[j] += VSQR( vx[j][k] );
        d[j] = VSQRT( d[j] );
        if (d[j] <= radius+VSMALL) less = 1;
        else more = 1;
    }

    /* return true if simplex touches or stradles surface of sphere */
    return ( less && more );
}

/*
 * ***************************************************************************
 * Routine:  oneChart_default
 *
 * Purpose:  DEFAULT: Select a single unified chart for a set of two or 
 *           more vertices whose coordinates may be given with respect to 
 *           different charts.  Then transform all of the coordinates of 
 *           the vertex set to be with respect to the single selected 
 *           "unified" chart.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void oneChart_default(int dim, int dimII, int objType,
    int chart[], double vx[][3], int dimV)
{
    VASSERT( (2 <= dim)   && (dim   <= 3) );
    VASSERT( (2 <= dimII) && (dimII <= 3) );
    VASSERT( (1 <= dimV)  && (dimV  <= 4) );
    VASSERT( (0 <= objType) );
}

/*
 * ***************************************************************************
 * Routine:  PDE_ctor_default
 *
 * Purpose:  Construct a fake differential equation object in case there
 *           is not one provided.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC PDE* PDE_ctor_default(void)
{
    int i;
    PDE *thee = VNULL;

    /* create some space for the pde object */
    thee = Vmem_malloc( VNULL, 1, sizeof(PDE) );

    /* PDE-specific parameters and function pointers */
    thee->initAssemble = VNULL;         /* once-per-assembly initialization */
    thee->initElement  = VNULL;         /* once-per-element initialization  */
    thee->initFace     = VNULL;         /* once-per-face initialization     */
    thee->initPoint    = VNULL;         /* once-per-point initialization    */
    thee->Fu           = VNULL;         /* nonlinear strong form            */
    thee->Ju           = VNULL;         /* nonlinear energy functional      */
    thee->Fu_v         = VNULL;         /* nonlinear weak form              */
    thee->DFu_wv       = VNULL;         /* bilinear linearization weak form */
    thee->p_wv         = VNULL;         /* bilinear mass density form       */
    thee->delta        = VNULL;         /* delta function source term       */
    thee->u_D          = VNULL;         /* dirichlet func and initial guess */
    thee->u_T          = VNULL;         /* analytical soln for testing      */
    thee->vec          = 1;             /* unknowns per spatial point;      */
    thee->sym[0][0]    = 0;             /* symmetries of bilinear form      */
    thee->est[0]       = 1.0;           /* error estimator weights          */
    for (i=0; i<VMAX_BDTYPE; i++)       /* boundary type remappings         */
        thee->bmap[0][i] = i;

    /* Manifold-specific function pointers */
    thee->bisectEdge  = bisectEdge_default;  /* edge bisection rule         */
    thee->mapBoundary = mapBoundary_default; /* boundary recovery rule      */
    thee->markSimplex = markSimplex_default; /* simplex marking rule        */
    thee->oneChart    = oneChart_default;    /* coordinate transformations  */

    /* Element-specific function pointers */
    thee->simplexBasisInit = VNULL;            /* initialization of bases   */
    thee->simplexBasisForm = VNULL;            /* form trial & test bases   */

    /* return the new pde object */
    return thee;
}

/*
 * ***************************************************************************
 * Routine:  PDE_dtor_default
 *
 * Purpose:  Destroy a fake differential equation object.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void PDE_dtor_default(PDE **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        Vmem_free( VNULL, 1, sizeof(PDE), (void**)thee );

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  PDE_sym
 *
 * Purpose:  Return the bilinear form minor symmetry (i,j).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int PDE_sym(PDE *thee, int i, int j)
{
    return thee->sym[i][j];
}

