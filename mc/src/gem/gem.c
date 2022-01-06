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
 * rcsid="$Id: gem.c,v 1.22 2010/08/12 05:18:46 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     Gem.c
 *
 * Purpose:  Class Gem: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "gem_p.h"

VEMBED(rcsid="$Id: gem.c,v 1.22 2010/08/12 05:18:46 fetk Exp $")

/* Hook for external structure updating */
VPRIVATE void defaultxUpFunc(SS **sms, int numS) { VASSERT(0); }

/*
 * ***************************************************************************
 * Class Gem: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_GEM)

/*
 * ***************************************************************************
 * Routine:  Gem_dim
 *
 * Purpose:  Return the extrinsic spatial dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_dim(Gem *thee)
{
    return thee->dim;
}

/*
 * ***************************************************************************
 * Routine:  Gem_dimII
 *
 * Purpose:  Return the intrinsic spatial dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_dimII(Gem *thee)
{
    return thee->dimII;
}

/*
 * ***************************************************************************
 * Routine:  Gem_dimVV
 *
 * Purpose:  Return the number of vertices in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_dimVV(Gem *thee)
{
    return thee->dimVV;
}

/*
 * ***************************************************************************
 * Routine:  Gem_dimEE
 *
 * Purpose:  Return the number of edges in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_dimEE(Gem *thee)
{
    return thee->dimEE;
}

/*
 * ***************************************************************************
 * Routine:  Gem_numVirtVV
 *
 * Purpose:  Return the logical number of vertices in the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_numVirtVV(Gem *thee)
{
    return thee->numVV;
}

/*
 * ***************************************************************************
 * Routine:  Gem_numVirtEE
 *
 * Purpose:  Return the logical number of edges in the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_numVirtEE(Gem *thee)
{
    return thee->numEE;
}

/*
 * ***************************************************************************
 * Routine:  Gem_numVirtFF
 *
 * Purpose:  Return the logical number of faces in the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_numVirtFF(Gem *thee)
{
    return thee->numFF;
}

/*
 * ***************************************************************************
 * Routine:  Gem_numVirtSS
 *
 * Purpose:  Return the logical number of simplices in the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_numVirtSS(Gem *thee)
{
    return thee->numSS;
}

/*
 * ***************************************************************************
 * Routine:  Gem_setNumVirtVV
 *
 * Purpose:  Set the logical number of vertices in the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_setNumVirtVV(Gem *thee, int i)
{
    thee->numVV = i;
}

/*
 * ***************************************************************************
 * Routine:  Gem_setNumVirtEE
 *
 * Purpose:  Set the logical number of edges in the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_setNumVirtEE(Gem *thee, int i)
{
    thee->numEE = i;
}

/*
 * ***************************************************************************
 * Routine:  Gem_setNumVirtFF
 *
 * Purpose:  Geometry manager constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_setNumVirtFF(Gem *thee, int i)
{
    thee->numFF = i;
}

/*
 * ***************************************************************************
 * Routine:  Gem_setNumVirtSS
 *
 * Purpose:  Set the logical number of simplices in the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_setNumVirtSS(Gem *thee, int i)
{
    thee->numSS = i;
}

/*
 * ***************************************************************************
 * Routine:  Gem_numVV
 *
 * Purpose:  Return the number of vertices in the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_numVV(Gem *thee)
{
    return Vset_num(thee->vertices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_VV
 *
 * Purpose:  Return a given vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* Gem_VV(Gem *thee, int i)
{
    return (VV*)Vset_access(thee->vertices,i);
}

/*
 * ***************************************************************************
 * Routine:  Gem_createVV
 *
 * Purpose:  Create a new vertex (becoming the new last vertex).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* Gem_createVV(Gem *thee)
{
    return (VV*)Vset_create(thee->vertices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_firstVV
 *
 * Purpose:  Return the first vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* Gem_firstVV(Gem *thee)
{
    return (VV*)Vset_first(thee->vertices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_lastVV
 *
 * Purpose:  Return the last vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* Gem_lastVV(Gem *thee)
{
    return (VV*)Vset_last(thee->vertices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_nextVV
 *
 * Purpose:  Return the next vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* Gem_nextVV(Gem *thee)
{
    return (VV*)Vset_next(thee->vertices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_prevVV
 *
 * Purpose:  Return the previous vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* Gem_prevVV(Gem *thee)
{
    return (VV*)Vset_prev(thee->vertices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_peekFirstVV
 *
 * Purpose:  Peek at the first vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* Gem_peekFirstVV(Gem *thee)
{
    return (VV*)Vset_peekFirst(thee->vertices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_peekLastVV
 *
 * Purpose:  Peek at the last vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* Gem_peekLastVV(Gem *thee)
{
    return (VV*)Vset_peekLast(thee->vertices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_destroyVV
 *
 * Purpose:  Destroy the last vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_destroyVV(Gem *thee)
{
    Vset_destroy(thee->vertices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_resetVV
 *
 * Purpose:  Destroy all of the vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_resetVV(Gem *thee)
{
    Vset_reset(thee->vertices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_numEE
 *
 * Purpose:  Return the number of edges.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_numEE(Gem *thee)
{
    return Vset_num(thee->edges);
}

/*
 * ***************************************************************************
 * Routine:  Gem_EE
 *
 * Purpose:  Return a given edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* Gem_EE(Gem *thee, int i)
{
    return (EE*)Vset_access(thee->edges,i);
}

/*
 * ***************************************************************************
 * Routine:  Gem_createEE
 *
 * Purpose:  Create a new edge (becoming the new last edge).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* Gem_createEE(Gem *thee)
{
    return (EE*)Vset_create(thee->edges);
}

/*
 * ***************************************************************************
 * Routine:  Gem_firstEE
 *
 * Purpose:  Return the first edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* Gem_firstEE(Gem *thee)
{
    return (EE*)Vset_first(thee->edges);
}

/*
 * ***************************************************************************
 * Routine:  Gem_lastEE
 *
 * Purpose:  Return the last edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* Gem_lastEE(Gem *thee)
{
    return (EE*)Vset_last(thee->edges);
}

/*
 * ***************************************************************************
 * Routine:  Gem_nextEE
 *
 * Purpose:  Return the next edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* Gem_nextEE(Gem *thee)
{
    return (EE*)Vset_next(thee->edges);
}

/*
 * ***************************************************************************
 * Routine:  Gem_prevEE
 *
 * Purpose:  Return the previous edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* Gem_prevEE(Gem *thee)
{
    return (EE*)Vset_prev(thee->edges);
}

/*
 * ***************************************************************************
 * Routine:  Gem_peekFirstEE
 *
 * Purpose:  Peek at the first edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* Gem_peekFirstEE(Gem *thee)
{
    return (EE*)Vset_peekFirst(thee->edges);
}

/*
 * ***************************************************************************
 * Routine:  Gem_peekLastEE
 *
 * Purpose:  Peek at the last edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* Gem_peekLastEE(Gem *thee)
{
    return (EE*)Vset_peekLast(thee->edges);
}

/*
 * ***************************************************************************
 * Routine:  Gem_destroyEE
 *
 * Purpose:  Destroy the last edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_destroyEE(Gem *thee)
{
    Vset_destroy(thee->edges);
}

/*
 * ***************************************************************************
 * Routine:  Gem_resetEE
 *
 * Purpose:  Destroy all of the edges.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_resetEE(Gem *thee)
{
    Vset_reset(thee->edges);
}

/*
 * ***************************************************************************
 * Routine:  Gem_numSS
 *
 * Purpose:  Return the number of simplices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_numSS(Gem *thee)
{
    return Vset_num(thee->simplices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_SS
 *
 * Purpose:  Return a given simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* Gem_SS(Gem *thee, int i)
{
    return (SS*)Vset_access(thee->simplices,i);
}

/*
 * ***************************************************************************
 * Routine:  Gem_createSS
 *
 * Purpose:  Create a new simplex (becoming the new last simplex).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* Gem_createSS(Gem *thee)
{
    return (SS*)Vset_create(thee->simplices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_firstSS
 *
 * Purpose:  Return the first simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* Gem_firstSS(Gem *thee)
{
    return (SS*)Vset_first(thee->simplices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_lastSS
 *
 * Purpose:  Return the last simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* Gem_lastSS(Gem *thee)
{
    return (SS*)Vset_last(thee->simplices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_nextSS
 *
 * Purpose:  Return the next simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* Gem_nextSS(Gem *thee)
{
    return (SS*)Vset_next(thee->simplices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_prevSS
 *
 * Purpose:  Return the previous simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* Gem_prevSS(Gem *thee)
{
    return (SS*)Vset_prev(thee->simplices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_peekFirstSS
 *
 * Purpose:  Peek at the first simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* Gem_peekFirstSS(Gem *thee)
{
    return (SS*)Vset_peekFirst(thee->simplices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_peekLastSS
 *
 * Purpose:  Peek at the last simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* Gem_peekLastSS(Gem *thee)
{
    return (SS*)Vset_peekLast(thee->simplices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_destroySS
 *
 * Purpose:  Destroy the last simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_destroySS(Gem *thee)
{
    Vset_destroy(thee->simplices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_resetSS
 *
 * Purpose:  Destroy all of the simplices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_resetSS(Gem *thee)
{
    Vset_reset(thee->simplices);
}

/*
 * ***************************************************************************
 * Routine:  Gem_numSQ
 *
 * Purpose:  Return the number of simplices in a given queue.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_numSQ(Gem *thee, int currentQ)
{
    return Vset_num(thee->sQueM[currentQ]);
}

/*
 * ***************************************************************************
 * Routine:  Gem_resetSQ
 *
 * Purpose:  Release all of the simplices in a given queue.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_resetSQ(Gem *thee, int currentQ)
{
    Vset_reset(thee->sQueM[currentQ]);
}

/*
 * ***************************************************************************
 * Routine:  Gem_numBF
 *
 * Purpose:  Return the number of boundary faces.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_numBF(Gem *thee)
{
    return thee->numBF;
}

/*
 * ***************************************************************************
 * Routine:  Gem_numBV
 *
 * Purpose:  Return the number of boundary vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_numBV(Gem *thee)
{
    return thee->numBV;
}

/*
 * ***************************************************************************
 * Routine:  Gem_setNumBF
 *
 * Purpose:  Set the number of boundary faces.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_setNumBF(Gem *thee, int val)
{
    thee->numBF = val;
}

/*
 * ***************************************************************************
 * Routine:  Gem_setNumBV
 *
 * Purpose:  Set the number of boundary vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_setNumBV(Gem *thee, int val)
{
    thee->numBV = val;
}

/*
 * ***************************************************************************
 * Routine:  Gem_addToNumBF
 *
 * Purpose:  Increment the number of boundary faces by a given integer.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_addToNumBF(Gem *thee, int val)
{
    thee->numBF += val;
}

/*
 * ***************************************************************************
 * Routine:  Gem_addToNumBV
 *
 * Purpose:  Increment the number of boundary vertices by a given integer.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_addToNumBV(Gem *thee, int val)
{
    thee->numBV += val;
}

/*
 * ***************************************************************************
 * Routine:  Gem_numBFpp
 *
 * Purpose:  Increment the number of boundary faces by 1.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_numBFpp(Gem *thee)
{
    thee->numBF++;
}

/*
 * ***************************************************************************
 * Routine:  Gem_numBVpp
 *
 * Purpose:  Increment the number of boundary vertices by 1.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_numBVpp(Gem *thee)
{
    thee->numBV++;
}

/*
 * ***************************************************************************
 * Routine:  Gem_numBFmm
 *
 * Purpose:  Decrement the number of boundary faces by 1.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_numBFmm(Gem *thee)
{
    thee->numBF--;
}

/*
 * ***************************************************************************
 * Routine:  Gem_numBVmm
 *
 * Purpose:  Decrement the number of boundary vertices by 1.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_numBVmm(Gem *thee)
{
    thee->numBV--;
}

#endif /* if !defined(VINLINE_GEM) */
/*
 * ***************************************************************************
 * Class Gem: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Gem_ctor
 *
 * Purpose:  Geometry manager constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Gem* Gem_ctor(Vmem *vmem, PDE *tpde)
{
    int i;
    Gem* thee = VNULL;

    thee = Vmem_malloc( VNULL, 1, sizeof(Gem) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Gem" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }
   
    VDEBUGIO("Gem_ctor: CREATING object..");
    VDEBUGIO("..done.\n");

    thee->xUp     = defaultxUpFunc;
    thee->xUpFlag = 0;

    if (tpde != VNULL) {
        thee->iMadePDE = 0;
        thee->pde      = tpde;
    } else {
        thee->iMadePDE = 1;
        thee->pde      = PDE_ctor_default();
    }

    thee->vertices  = VNULL;
    thee->edges     = VNULL;
    thee->simplices = VNULL;
    for (i=0; i<VMAXSQ; i++) {
        thee->sQueM[i] = VNULL;
    }

    Gem_reset(thee, 0, 0);

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Gem_dtor
 *
 * Purpose:  Geometry manager destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_dtor(Gem **thee)
{
    int i;

    //VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        if ((*thee)->iMadePDE) {
            PDE_dtor_default( &((*thee)->pde) );
        }

        Vset_dtor( &((*thee)->vertices) );
        Vset_dtor( &((*thee)->edges) );
        Vset_dtor( &((*thee)->simplices) );
        for (i=0; i<VMAXSQ; i++) {
            Vset_dtor( &((*thee)->sQueM[i]) );
        }

        VDEBUGIO("Gem_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Gem), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_reset
 *
 * Purpose:  Reset all of the geometry datastructures.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_reset(Gem *thee, int dim, int dimII)
{
    int i;
    char name[80];
    SS* SQ = VNULL;

    if ((dim > 0) && (dimII > 0)) {
        if ( ! ((2 <= dim) && (dim <= 3)) ) {
            Vnm_print(2,"Gem_reset: dim=<%d> bad; setting dim=<3>",dim);
            dim = 3;
        }
        if ( ! ((2 <= dimII) && (dimII <= 3)) ) {
            Vnm_print(2,"Gem_reset: dimII=<%d> bad; setting dimII=<3>",dimII);
            dimII = 3;
        }
        thee->dim   = dim;
        thee->dimII = dimII;
        thee->dimVV = dim+1;
        thee->dimEE = 3*(dim-1);

        /* set the possibly new dimensions for the PDE routines to get at */
        if (thee->pde != VNULL) {
            PDE_setDim(thee->pde,   dim);
            PDE_setDimII(thee->pde, dimII);
        }

    } else {
        thee->dim   = 0;
        thee->dimII = 0;
        thee->dimVV = 0;
        thee->dimEE = 0;

        /* set the possibly new dimensions for the PDE routines to get at */
        if (thee->pde != VNULL) {
            PDE_setDim(thee->pde,   0);
            PDE_setDimII(thee->pde, 0);
        }
    }

    thee->numVV0 = 0;
    thee->numVV  = 0;
    thee->numEE  = 0;
    thee->numFF  = 0;
    thee->numSS  = 0;
    thee->numBV  = 0;
    thee->numBF  = 0;

    if ( thee->vertices  != VNULL ) Vset_dtor( &(thee->vertices) );
    if ( thee->edges     != VNULL ) Vset_dtor( &(thee->edges) );
    if ( thee->simplices != VNULL ) Vset_dtor( &(thee->simplices) );
    for (i=0; i<VMAXSQ; i++) {
        if ( thee->sQueM[i] != VNULL ) {
            Vset_dtor( &(thee->sQueM[i]) );
        }
    }

    thee->vertices  = Vset_ctor( VNULL, "VV",  sizeof(VV), VMAX_OBJECTS, 0 );
    thee->edges     = Vset_ctor( VNULL, "EE",  sizeof(EE), VMAX_OBJECTS, 0 );
    thee->simplices = Vset_ctor( VNULL, "SS",  sizeof(SS), VMAX_OBJECTS, 0 );
    for (i=0; i<VMAXSQ; i++) {
        sprintf(name,"SQ%d",i);
        thee->sQueM[i]  = Vset_ctor( VNULL, name, sizeof(SQ),VMAX_OBJECTS, 0 );
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_createAndInitVV
 *
 * Purpose:  Create and initialize a new vertex; return a point to it.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* Gem_createAndInitVV(Gem *thee)
{
    VV *vx = Gem_createVV(thee);
    VV_init(vx, Gem_dim(thee), Gem_numVV(thee)-1 );
    return vx;
}

/*
 * ***************************************************************************
 * Routine:  Gem_createAndInitEE
 *
 * Purpose:  Create and initialize a new edge; return a point to it.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* Gem_createAndInitEE(Gem *thee)
{
    EE *eg = Gem_createEE(thee);
    EE_init(eg, Gem_dim(thee), Gem_numEE(thee)-1 );
    return eg;
}

/*
 * ***************************************************************************
 * Routine:  Gem_createAndInitSS
 *
 * Purpose:  Create and initialize a new simplex; return a point to it.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* Gem_createAndInitSS(Gem *thee)
{
    SS *sm = Gem_createSS(thee);
    SS_init(sm, Gem_dim(thee), Gem_numSS(thee)-1 );
    return sm;
}

/*
 * ***************************************************************************
 * Routine:  Gem_SQ
 *
 * Purpose:  Return the simplex at a particular location in the simplex Q.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS *Gem_SQ(Gem *thee, int currentQ, int i)
{
    SS **val = (SS**)Vset_access(thee->sQueM[currentQ],i);
    if (val != VNULL) return *val;
    return VNULL;
}

/*
 * ***************************************************************************
 * Routine:  Gem_appendSQ
 *
 * Purpose:  Append a simplex to the end of a simplex Q.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_appendSQ(Gem *thee, int currentQ, SS *qsm)
{
    SS **val = (SS**)Vset_create(thee->sQueM[currentQ]);
    *val = qsm;
}

/*
 * ***************************************************************************
 * Routine:  Gem_createSimplexRings
 *
 * Purpose:  Create all of the simplex rings.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_createSimplexRings(Gem *thee)
{
    int i;
    SS *sm;

    Vnm_tstart(70, "simplex ring create");
    Vnm_print(0,"Gem_createSimplexRings: creating simplex rings..");

    /* go through all simplices and create simplex rings */
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        SS_buildRing( sm );
    }

    Vnm_print(0,"..done.\n");
    Vnm_tstop(70, "simplex ring create");
}

/*
 * ***************************************************************************
 * Routine:  Gem_destroySimplexRings
 *
 * Purpose:  Destroy all of the simplex rings.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_destroySimplexRings(Gem *thee)
{
    int i;
    VV *vx;
    SS *sm;

    Vnm_print(0,"Gem_destroySimplexRings: destroying simplex rings..");

    /* go through all vertices and reset firstSS pointer */
    for (i=0; i<Gem_numVV(thee); i++) {
        vx = Gem_VV(thee,i);
        VV_setFirstSS( vx, VNULL );
    }

    /* go through all simplices and reinitialize simplex rings */
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        SS_initRing( sm );
    }

    Vnm_print(0,"..done.\n");
}

/*
 * ***************************************************************************
 * Routine:  Gem_findOrCreateEdge
 *
 * Purpose:  Look for a common edges between two vertices.
 *           If it doesn't yet exist, we create it, and then note that
 *           we did so.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE *Gem_findOrCreateEdge(Gem *thee, VV *v0, VV *v1, int *iDid)
{
    VV *vxTmp   = VNULL;
    EE *eg      = VNULL;
    EE *parent0 = VNULL;
    EE *parent1 = VNULL;
    *iDid = 0;

    eg = VV_commonEdge(v0,v1);
    if (eg == VNULL) {
        *iDid = 1;
        eg=Gem_createAndInitEE(thee);
        EE_setVertex(eg, 0, v0);
        EE_setVertex(eg, 1, v1);
        EE_setVertexOrder(eg,vxTmp);
        EE_setParent(eg,VNULL);
        EE_setType(eg,0);
        EE_buildRing(eg);
        parent0 = VV_parentEE(v0);
        parent1 = VV_parentEE(v1);
        if ( parent0 != VNULL ) {
            EE_setParent(eg, parent0);
        } else if ( parent1 != VNULL ) {
            EE_setParent(eg, parent1);
        }
        if ( EE_parent(eg) != VNULL ) {
            EE_setType(eg, EE_type(EE_parent(eg)));
        }
    }

    return eg;
}

/*
 * ***************************************************************************
 * Routine:  Gem_createEdges
 *
 * Purpose:  Create all of the edges.
 *
 * Notes:    Based on a simplex traversal.
 *
 *           We also set the edge numbers in the simplices while we we
 *           are doing the edge creation.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_createEdges(Gem *thee)
{
    int i,j,k,l,iDid,edgeCnt;
#   if defined(VG_ELEMENT)
        int edgeNum;
        EE *eg;
#   endif
    SS *sm;
    VV *v0, *v1;

    Vnm_tstart(70, "edge create");
    Vnm_print(0,"Gem_createEdges: creating edges (simplex traversal)..");

    /* go through simplices and create edges if they don't already exist */
    if (Gem_numEE(thee) == 0) {
        for (i=0; i<Gem_numSS(thee); i++) {
            sm = Gem_SS(thee,i);
            for (j=0; j<Gem_dimEE(thee); j++) {
                k  = vmapEI[j][0];
                l  = vmapEI[j][1];
                v0 = SS_vertex(sm,k);
                v1 = SS_vertex(sm,l);
#               if defined(VG_ELEMENT)
                    eg = Gem_findOrCreateEdge(thee, v0, v1, &iDid);
                    edgeNum = EE_id( eg );
                    SS_setEdgeNumber(sm,j,edgeNum);
#               else
                    (void*)Gem_findOrCreateEdge(thee, v0, v1, &iDid);
#               endif
            }
        }
    }
    edgeCnt = Gem_numEE(thee);

    Vnm_print(0,"..done.  [edges=<%d>]\n",edgeCnt);
    Vnm_tstop(70, "edge create");

    /* set the edge counter and return */
    Gem_setNumVirtEE(thee, edgeCnt);
}

/*
 * ***************************************************************************
 * Routine:  Gem_destroyEdges
 *
 * Purpose:  Destroy all of the edges.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_destroyEdges(Gem *thee)
{
    int i;
    VV *vx;

    Vnm_print(0,"Gem_destroyEdges: destroying edges..");

    /* destroy edges if they exist */
    if (Gem_numEE(thee) > 0) {
        /* go through all vertices and reset firstEE pointer */

        for (i=0; i<Gem_numVV(thee); i++) {
            vx = Gem_VV(thee,i);
            VV_setFirstEE( vx, VNULL );
            VV_setParentEE( vx, VNULL );
        }

        /* reset the edges (release the ram) */
        Gem_resetEE(thee);
        VASSERT( Gem_numEE(thee) == 0 );
    }

    Vnm_print(0,"..done.  [edges=<%d>]\n",Gem_numEE(thee));
}

/*
 * ***************************************************************************
 * Routine:  Gem_countChk
 *
 * Purpose:  Count all vertices, edges, faces, simplices, and do it
 *           is cheaply as possible.  Also do a form check.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_countChk(Gem *thee)
{
    /* count vertices */
    Gem_setNumVirtVV( thee, Gem_numVV(thee) );

    /* count edges */
    if ( Gem_numEE(thee) > 0 ) {
        /* edges DO exist; just use the current edge count */
        Gem_setNumVirtEE( thee, Gem_numEE(thee) );
    } else {
        /* edges DO NOT exist; create/destroy to get edge nums (fastest way) */
        Gem_createEdges( thee );
        Gem_destroyEdges( thee );
    }

    /* count faces -- COSTLY!  Only do if you have face DOF in the element */
    Gem_countFaces( thee );

    /* count simplices */
    Gem_setNumVirtSS( thee, Gem_numSS(thee) );

    /* check ringed vertex: 0=[v+s],1=[.+sRing],2=[.+eRing],3=[.+conform] */
    /* Gem_formChk(thee,2); */
}

/*
 * ***************************************************************************
 * Routine:  Gem_countFaces
 *
 * Purpose:  Count all of the faces without actually creating them.
 *
 * Notes:    Keep track of the global face numbers in each element.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_countFaces(Gem *thee)
{
    int i, j, faceCnt, face;
#   if defined(VG_ELEMENT)
        int face2;
#   endif
    SS *sm, *sm2;

    Vnm_tstart(70, "face count");
    Vnm_print(0,"Gem_countFaces: counting faces..");

    /* count the faces (including boundary faces) */
    if (Gem_dim(thee) == 2) {
        faceCnt = 0;
    } else {
        faceCnt = 0;
        for (i=0; i<Gem_numSS(thee); i++) {
            sm = Gem_SS(thee,i);

            /* now count all i-j (sm-sm2) faces where i<j */
            for (face=0; face<Gem_dimVV(thee); face++) {
                sm2 = SS_nabor(sm,face);
                if (sm2 == VNULL) {
#                   if defined(VG_ELEMENT)
                        SS_setFaceNumber(sm,face,faceCnt);
#                   endif
                    faceCnt++;
                } else {
                    j = SS_id(sm2);
                    if (i < j) {
#                       if defined(VG_ELEMENT)
                            face2 = SS_sharedFaceLocNum(sm2,sm);
                            SS_setFaceNumber(sm,face,faceCnt);
                            SS_setFaceNumber(sm2,face2,faceCnt);
#                       endif
                        faceCnt++;
                    }
                }
            }
        }
    }

    Vnm_print(0,"..done.  [faces=<%d>]\n",faceCnt);
    Vnm_tstop(70, "face count");

    /* set the face counter and return */
    Gem_setNumVirtFF(thee, faceCnt);
}

/*
 * ***************************************************************************
 * Routine:  Gem_clearEdges
 *
 * Purpose:  Clear all of the edge numbers in each simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_clearEdges(Gem *thee)
{
#   if defined(VG_ELEMENT)
        int i,j;
        SS *sm;
#   endif

    Vnm_tstart(70, "edge clear");
    Vnm_print(0,"Gem_clearEdges: clearing edge numbers..");

    /* go through simplices and clear edge numbers */
#if defined(VG_ELEMENT)
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        for (j=0; j<Gem_dimEE(thee); j++) {
            SS_setEdgeNumber(sm,j,-1);
        }
    }
#endif

    Vnm_print(0,"..done.\n");
    Vnm_tstop(70, "edge clear");

    /* set the edge counter and return */
    Gem_setNumVirtEE(thee, 0);
}

/*
 * ***************************************************************************
 * Routine:  Gem_countEdges
 *
 * Purpose:  Count up all of the edges without actually creating them, and
 *           keep track of the global edge numbers in each element.
 *
 * Notes:    Based on a simplex traversal.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_countEdges(Gem *thee)
{
    int edgeCnt;
#   if defined(VG_ELEMENT)
        int i,j,k,l,iv,iv2,edgeNum;
        SS *sm, *sm0, *sm2;
        VV *vx, *vx2;
#   endif

    Vnm_tstart(70, "edge count");
    Vnm_print(0,"Gem_countEdges: counting edges (simplex traversal)..");

    /* go through simplices and count edges */
    edgeCnt = 0;
#if defined(VG_ELEMENT)
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        for (j=0; j<Gem_dimEE(thee); j++) {
            k = vmapEI[j][0];
            l = vmapEI[j][1];
            edgeNum = vmapE[k][l];
            if (SS_edgeNumber(sm,edgeNum) < 0) {
                vx  = SS_vertex(sm,k);
                vx2 = SS_vertex(sm,l);
                /* tell all simplices using edge what its number is */
                for (sm2=VV_firstSS(vx2);sm2!=VNULL;sm2=SS_link(sm2,vx2)){
                    for (sm0=VV_firstSS(vx);sm0!=VNULL;sm0=SS_link(sm0,vx)){
                        if (sm0 == sm2) {
                            iv  = SS_vptr2localVnum(sm0, vx);
                            iv2 = SS_vptr2localVnum(sm0, vx2);
                            edgeNum = vmapE[iv][iv2];
                            SS_setEdgeNumber(sm0,edgeNum,edgeCnt);
                        }
                    }
                }
                edgeCnt++;
            }
        }
    }
#endif

    Vnm_print(0,"..done.  [edges=<%d>]\n",edgeCnt);
    Vnm_tstop(70, "edge count");

    /* set the edge counter and return */
    Gem_setNumVirtEE(thee, edgeCnt);
}

/*
 * ***************************************************************************
 * Routine:  Gem_formFix
 *
 * Purpose:  Make some specified hacked fix to a given mesh.
 *
 * Notes:    key==0 --> ?
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_formFix(Gem *thee, int key)
{
    int i, j, k, l, m, nabors, btype;
    double radk, radl, radm, myTol;
    VV *v[4];
    SS *sm, *sm0, *sm1, *sm2;

    /* input check and some i/o */
    btype = key;
    VASSERT( (0 <= btype) && (btype <= 2) );

    /* go through all simplices and zero all boundary faces */
    Vnm_print(0,"Gem_makeBnd: zeroing boundary faces/vertices..");
    Gem_setNumBF(thee, 0);
    Gem_setNumBV(thee, 0);
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        if ( (i>0) && (i % VPRTKEY) == 0 ) Vnm_print(0,"[BS:%d]",i);

        /* get local vertices */
        for (j=0; j<Gem_dimVV(thee); j++)
            v[j] = SS_vertex(sm,j);

        /* reset all vertices and faces to interior type */
        for (j=0; j<Gem_dimVV(thee); j++) {
            /* the other three local vertex/face numbers besides "j" */
            k=(j+1) % Gem_dimVV(thee);
            l=(k+1) % Gem_dimVV(thee);
            m=(l+1) % Gem_dimVV(thee);
            SS_setFaceType(sm, j, 0);
            VV_setType(v[k], 0);
            VV_setType(v[l], 0);
            if (Gem_dim(thee) == 3) VV_setType(v[m], 0);
        }
    }
    Vnm_print(0,"..done.\n");

    /* are we done */
    /* if (btype == 0) return; */

    /* okay now make a boundary */
    Vnm_print(0,"Gem_makeBnd: rebuilding boundary faces/vertices..");
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        if ( (i>0) && (i % VPRTKEY) == 0 ) Vnm_print(0,"[BS:%d]",i);

        /* get local vertices */
        for (j=0; j<Gem_dimVV(thee); j++)
            v[j] = SS_vertex(sm,j);

        /* rebuild everything */
        for (j=0; j<Gem_dimVV(thee); j++) {

            /* the other three local vertex/face numbers besides "j" */
            k=(j+1) % Gem_dimVV(thee);
            l=(k+1) % Gem_dimVV(thee);
            m=(l+1) % Gem_dimVV(thee);

            /* look for a face nabor sharing face "j" (opposite vertex "j") */
            nabors = 0;
            for (sm0=VV_firstSS(v[k]); sm0!=VNULL;sm0=SS_link(sm0,v[k])) {
                for (sm1=VV_firstSS(v[l]); sm1!=VNULL; sm1=SS_link(sm1,v[l])) {
                    if (Gem_dim(thee) == 2) {
                        if ((sm0!=sm) && (sm0==sm1)) nabors++;
                    } else {
                        for (sm2=VV_firstSS(v[m]); sm2!=VNULL; 
                          sm2=SS_link(sm2,v[m])) {
                            if ((sm0!=sm) && (sm0==sm1) && (sm0==sm2)) {
                                nabors++;
                            }
                        }
                    }
                }
            }

            /* if no one there, then face "j" is actually a boundary face */
            if (nabors == 0) {

                myTol = 1.0e-2;

                if ( ( VABS(VV_coord(v[k],2) - 0.0) < myTol) 
                  && ( VABS(VV_coord(v[l],2) - 0.0) < myTol)
                  && ( VABS(VV_coord(v[m],2) - 0.0) < myTol) ) {
                    btype = 1;
                } else if ( ( VABS(VV_coord(v[k],2) - 68.03512) < myTol)
                         && ( VABS(VV_coord(v[l],2) - 68.03512) < myTol) 
                         && ( VABS(VV_coord(v[m],2) - 68.03512) < myTol) ) {
                    btype = 3;
                } else {
                    radk = VSQRT( VSQR( VV_coord(v[k],0) )
                                + VSQR( VV_coord(v[k],1) ) );
                    radl = VSQRT( VSQR( VV_coord(v[l],0) )
                                + VSQR( VV_coord(v[l],1) ) );
                    radm = VSQRT( VSQR( VV_coord(v[m],0) )
                                + VSQR( VV_coord(v[m],1) ) );
                    if ( ( VABS(radk - 1.5) < myTol)
                      && ( VABS(radl - 1.5) < myTol)
                      && ( VABS(radm - 1.5) < myTol) ) {
                        btype = 2;
                    } else if ( ( VABS(radk - 2.0) < myTol)
                            &&  ( VABS(radl - 2.0) < myTol)
                            &&  ( VABS(radm - 2.0) < myTol) ){
                        btype = 4;
                    } else {
                        btype = 0;
                    }
                }

                SS_setFaceType(sm, j, btype);

                Gem_numBFpp(thee);
                if (VINTERIOR( VV_type(v[k])) ) {
                    VV_setType(v[k], btype);
                    Gem_numBVpp(thee);
                }
                if (VINTERIOR( VV_type(v[l])) ) {
                    VV_setType(v[l], btype);
                    Gem_numBVpp(thee);
                }
                if (Gem_dim(thee) == 3) {
                    if (VINTERIOR( VV_type(v[m])) ) {
                        VV_setType(v[m], btype);
                        Gem_numBVpp(thee);
                    }
                }
            }
        }
    }
    Vnm_print(0,"..done.\n");
}

/*
 * ***************************************************************************
 * Routine:  Gem_externalUpdateFlag, Gem_setExternalUpdateFlag,
 *           Gem_setExternalUpdateFunction
 *
 * Purpose:  Hook for external structure updating.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_externalUpdateFlag(Gem *thee)
{
    return thee->xUpFlag;
}
VPUBLIC void Gem_setExternalUpdateFlag(Gem *thee, int fl)
{
    thee->xUpFlag = fl;
}
VPUBLIC void Gem_setExternalUpdateFunction(Gem *thee,
    void (*xUp)(SS **sms, int numS))
{
    thee->xUpFlag = 1;
    thee->xUp     = xUp;
}

