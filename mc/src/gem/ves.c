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
 * rcsid="$Id: ves.c,v 1.13 2010/08/12 05:18:59 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     ves.c
 *
 * Purpose:  Class V,E,S: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "ves_p.h"

VEMBED(rcsid="$Id: ves.c,v 1.13 2010/08/12 05:18:59 fetk Exp $")

/*
 * ***************************************************************************
 * Class V: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_GEM)

/*
 * ***************************************************************************
 * Routine:  VV_init
 *
 * Purpose:  Initialize a vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_init(VV *thee, int dim, int id)
{
    thee->d.ePtr    = VNULL;
    thee->d.sPtr    = VNULL;
    thee->d.eParent = VNULL;
    thee->d.x[0]    = 0.0;
    thee->d.x[1]    = 0.0;
    thee->d.x[2]    = 0.0;
    Vel_init((Vel*)thee, dim, id);
}

/*
 * ***************************************************************************
 * Routine:  VV_reinit
 *
 * Purpose:  Re-initialize a vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_reinit(VV *thee)
{
    /* keep the dimension and id information */
    thee->d.ePtr    = VNULL;
    thee->d.sPtr    = VNULL;
    thee->d.eParent = VNULL;
    thee->d.x[0]    = 0.0;
    thee->d.x[1]    = 0.0;
    thee->d.x[2]    = 0.0;
    Vel_reinit((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  VV_setReality
 *
 * Purpose:  Set the reality.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_setReality(VV *thee, int reel)
{
    Vel_setReality((Vel*)thee, reel);
}

/*
 * ***************************************************************************
 * Routine:  VV_setDim
 *
 * Purpose:  Set the dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_setDim(VV *thee, int dim)
{
    Vel_setDim((Vel*)thee, dim);
}

/*
 * ***************************************************************************
 * Routine:  VV_setClass
 *
 * Purpose:  Set the class.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_setClass(VV *thee, int clas)
{
    Vel_setClass((Vel*)thee, clas);
}

/*
 * ***************************************************************************
 * Routine:  VV_setType
 *
 * Purpose:  Set the type.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_setType(VV *thee, int type)
{
    Vel_setType((Vel*)thee, type);
}

/*
 * ***************************************************************************
 * Routine:  VV_setChart
 *
 * Purpose:  Set the chart.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_setChart(VV *thee, int chart)
{
    Vel_setChart((Vel*)thee, chart);
}

/*
 * ***************************************************************************
 * Routine:  VV_setId
 *
 * Purpose:  Set the ID.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_setId(VV *thee, int id)
{
    Vel_setId((Vel*)thee, id);
}

/*
 * ***************************************************************************
 * Routine:  VV_reality
 *
 * Purpose:  Return the reality.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int VV_reality(VV *thee)
{
    return Vel_reality((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  VV_dim
 *
 * Purpose:  Return the dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int VV_dim(VV *thee)
{
    return Vel_dim((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  VV_dimVV
 *
 * Purpose:  Return the number of vertices in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int VV_dimVV(VV *thee)
{
    return Vel_dimVV((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  VV_dimEE
 *
 * Purpose:  Return the number of edges in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int VV_dimEE(VV *thee)
{
    return Vel_dimEE((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  VV_dimFF
 *
 * Purpose:  Return the number of faces in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int VV_dimFF(VV *thee)
{
    return Vel_dimFF((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  VV_class
 *
 * Purpose:  Return the class.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int VV_class(VV *thee)
{
    return Vel_class((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  VV_type
 *
 * Purpose:  Return the type.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int VV_type(VV *thee)
{
    return Vel_type((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  VV_chart
 *
 * Purpose:  Return the chart.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int VV_chart(VV *thee)
{
    return Vel_chart((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  VV_id
 *
 * Purpose:  Return the ID.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int VV_id(VV *thee)
{
    return Vel_id((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  VV_setCoord
 *
 * Purpose:  Set the coordinate.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_setCoord(VV *thee, int i, double val)
{
    thee->d.x[i] = val;
}

/*
 * ***************************************************************************
 * Routine:  VV_coord
 *
 * Purpose:  Return the coordinate.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double VV_coord(VV *thee, int i)
{
    return thee->d.x[i];
}

/*
 * ***************************************************************************
 * Routine:  VV_addEdgeToRing
 *
 * Purpose:  Add an edge to an edge ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_addEdgeToRing(VV *thee, EE *eg)
{
    VASSERT( eg != VNULL );
    VASSERT( eg != VV_firstEE(thee) );
    VASSERT( !VV_edgeInRing(thee, eg) );
    EE_setLink( eg, thee, VV_firstEE(thee) );
    VV_setFirstEE( thee, eg );
}

/*
 * ***************************************************************************
 * Routine:  VV_addSimplexToRing
 *
 * Purpose:  Add a simplex to a simplex ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_addSimplexToRing(VV *thee, SS *sm)
{
    VASSERT( sm != VNULL );
    VASSERT( sm != VV_firstSS(thee) );
    VASSERT( !VV_simplexInRing(thee, sm) );
    SS_setLink( sm, thee, VV_firstSS(thee) );
    VV_setFirstSS( thee, sm );
}

/*
 * ***************************************************************************
 * Routine:  VV_setFirstEE
 *
 * Purpose:  Set the first edge in an edge ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_setFirstEE(VV *thee, EE *eg)
{
    thee->d.ePtr = eg;
}

/*
 * ***************************************************************************
 * Routine:  VV_setFirstSS
 *
 * Purpose:  Set the first simplex in a simplex ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_setFirstSS(VV *thee, SS *sm)
{
    thee->d.sPtr = sm;
}

/*
 * ***************************************************************************
 * Routine:  VV_setParent
 *
 * Purpose:  Set the parent edge pointer.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_setParent(VV *thee, EE *eg)
{
    thee->d.eParent = eg;
}

/*
 * ***************************************************************************
 * Routine:  VV_firstEE
 *
 * Purpose:  Return the first edge in an edge ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* VV_firstEE(VV *thee)
{
    return (EE*)(thee->d.ePtr);
}

/*
 * ***************************************************************************
 * Routine:  VV_firstSS
 *
 * Purpose:  Return the first simplex in a simplex ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* VV_firstSS(VV *thee)
{
    return (SS*)(thee->d.sPtr);
}

/*
 * ***************************************************************************
 * Routine:  VV_parent
 *
 * Purpose:  Return the parent edge pointer.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* VV_parent(VV *thee)
{
    return (EE*)(thee->d.eParent);
}

#endif /* if !defined(VINLINE_GEM) */
/*
 * ***************************************************************************
 * Class V: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  VV_ctor
 *
 * Purpose:  The vertex constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* VV_ctor(int dim, int myid)
{
    VV *thee = VNULL;

    VDEBUGIO("VV_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(VV) );

    thee->d.ePtr    = VNULL;
    thee->d.sPtr    = VNULL;
    thee->d.eParent = VNULL;
    thee->d.x[0] = 0.0;
    thee->d.x[1] = 0.0;
    thee->d.x[2] = 0.0;
    Vel_init((Vel*)thee, dim, myid);

    VDEBUGIO("..done.\n");

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  VV_dtor
 *
 * Purpose:  The vertex destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_dtor(VV **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        VDEBUGIO("VV_dtor: DESTROYING object..");
        Vmem_free( VNULL, 1, sizeof(VV), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  VV_removeEdgeFromRing
 *
 * Purpose:  Remove an edge from an edge ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_removeEdgeFromRing(VV *thee, EE *eg)
{
    EE *leg, *teg;

    /* edge must be non-VNULL, and vertex must point to some edges */
    VASSERT( eg != VNULL );
    VASSERT( VV_firstEE(thee) != VNULL );
    VASSERT( VV_edgeInRing(thee, eg) );

    /* start with the first guy in the list */
    leg = VV_firstEE(thee);

    /* check the first guy */
    if (eg == leg) {

        /* patch the list to effectively remove guy from the list */
        VV_setFirstEE(thee, EE_link(eg, thee));

        /* set guy's link to VNULL */
        EE_setLink(eg, thee, VNULL);

        /* we are done; return */
        return;

    /* not first guy; starting looping through the list */
    } else {

        /* move to the second guy in the list and start looping */
        teg = EE_link(leg, thee);
        while ( teg != VNULL) {

            /* okay, we found the guy to remove */
            if (teg == eg) {

                /* patch the list to effectively remove guy from the list */
                EE_setLink(leg, thee, EE_link(eg, thee));

                /* set guy's link to VNULL */
                EE_setLink(eg, thee, VNULL);

                /* we are done; return */
                return;

            /* not found; move to the next guy and continue */
            } else {
                leg = teg;
                teg = EE_link(leg, thee);
            }
        }
    }

    /* if we get to here, there is a problem... */
    Vnm_print(2,"VV_removeEdgeFromRing: EE not found!\n");
}

/*
 * ***************************************************************************
 * Routine:  VV_removeSimplexFromRing
 *
 * Purpose:  Remove a simplex from a simplex ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void VV_removeSimplexFromRing(VV *thee, SS *sm)
{
    SS *lsm, *tsm;

    /* simplex must be non-VNULL, and vertex must point to some simplices */
    VASSERT( sm != VNULL );
    VASSERT( VV_firstSS(thee) != VNULL );
    VASSERT( VV_simplexInRing(thee, sm) );

    /* start with the first guy in the list */
    lsm = VV_firstSS(thee);

    /* check the first guy */
    if (sm == lsm) {

        /* patch the list to effectively remove guy from the list */
        VV_setFirstSS(thee, SS_link(sm, thee));

        /* set guy's link to VNULL */
        SS_setLink(sm, thee, VNULL);

        /* we are done; return */
        return;

    /* not first guy; starting looping through the list */
    } else {

        /* move to the second guy in the list and start looping */
        tsm = SS_link(lsm, thee);
        while ( tsm != VNULL) {

            /* okay, we found the guy to remove */
            if (tsm == sm) {

                /* patch the list to effectively remove guy from the list */
                SS_setLink(lsm, thee, SS_link(sm, thee));

                /* set guy's link to VNULL */
                SS_setLink(sm, thee, VNULL);

                /* we are done; return */
                return;

            /* not found; move to the next guy and continue */
            } else {
                lsm = tsm;
                tsm = SS_link(lsm, thee);
            }
        }
    }

    /* if we get to here, there is a problem... */
    Vnm_print(2,"VV_removeSimplexFromRing: SS not found!\n");
}

/*
 * ***************************************************************************
 * Routine:  VV_edgeInRing
 *
 * Purpose:  Is an edge in the edge ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int VV_edgeInRing(VV *thee, EE *eg)
{
    EE *teg;
    VASSERT( eg != VNULL );
    for (teg=VV_firstEE(thee); teg!=VNULL; teg=EE_link(teg, thee))
        if (teg == eg) return VTRUE;
    return VFALSE;
}

/*
 * ***************************************************************************
 * Routine:  VV_simplexInRing
 *
 * Purpose:  Is a simplex in a simplex ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int VV_simplexInRing(VV *thee, SS *sm)
{
    SS *tsm;
    VASSERT( sm != VNULL );
    for (tsm=VV_firstSS(thee); tsm!=VNULL; tsm=SS_link(tsm, thee))
        if (tsm == sm) return VTRUE;
    return VFALSE;
}

/*
 * ***************************************************************************
 * Routine:  VV_commonEdge
 *
 * Purpose:  Return the common edge between two vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* VV_commonEdge(VV *thee, VV *v0)
{
    EE *eg;
    VASSERT( thee != VNULL );
    VASSERT( v0 != VNULL );
    VASSERT( v0 != thee );
    for (eg=VV_firstEE(thee); eg!=VNULL; eg=EE_link(eg, thee))
        if ((EE_vertex(eg,0) == v0) || (EE_vertex(eg,1) == v0)) return eg;
    return VNULL;
}

/*
 * ***************************************************************************
 * Routine:  VV_parentEdge
 *
 * Purpose:  Return parent edge having one of two vertices as midpoint.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* VV_parentEdge(VV *thee, VV *v0)
{
    EE *eg;
    VASSERT( thee != VNULL );
    VASSERT( v0 != VNULL );
    VASSERT( v0 != thee );
    for (eg=VV_firstEE(thee); eg!=VNULL; eg=EE_link(eg, thee))
        if (EE_midPoint(eg) == v0) return eg;
    for (eg=VV_firstEE(v0); eg!=VNULL; eg=EE_link(eg, v0))
        if (EE_midPoint(eg) == thee) return eg;
    return VNULL;
}

/*
 * ***************************************************************************
 * Routine:  VV_commonSimplex2
 *
 * Purpose:  Return a 2-simplex that is shared by 2 vertices,
 *           and which is different from the input simplex sm.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* VV_commonSimplex2(VV *thee, VV *v0, SS *sm)
{
    unsigned int i;
    SS *tsm;
    for (tsm=VV_firstSS(thee); tsm!=VNULL; tsm=SS_link(tsm, thee))
        if (tsm != sm)
            for (i=0; i<VV_dimVV(thee); i++)
                if (SS_vertex(tsm,i) == v0) return tsm;
    return VNULL;
}

/*
 * ***************************************************************************
 * Routine:  VV_commonSimplex3
 *
 * Purpose:  Return a 3-simplex that is shared by 3 vertices,
 *           and which is different from the input simplex sm.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* VV_commonSimplex3(VV *thee, VV *v0, VV *v1, SS *sm)
{
    unsigned int i,j;
    SS *tsm;
    for (tsm=VV_firstSS(thee); tsm!=VNULL; tsm=SS_link(tsm, thee))
        if (tsm != sm)
            for (i=1; i<VV_dimVV(thee); i++)
                for (j=0; j<i; j++)
                    if (((SS_vertex(tsm,i) == v0) && (SS_vertex(tsm,j) == v1))
                     || ((SS_vertex(tsm,j) == v0) && (SS_vertex(tsm,i) == v1)))
                        return tsm;
    return VNULL;
}

/*
 * ***************************************************************************
 * Routine:  VV_commonSimplex4
 *
 * Purpose:  Return a 3-simplex that is shared by 4 vertices,
 *           and which is different from the input simplex sm.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* VV_commonSimplex4(VV *thee, VV *v0, VV *v1, VV *v2, SS *sm)
{
    unsigned int i,j,k;
    SS *tsm;
    for (tsm=VV_firstSS(thee); tsm!=VNULL; tsm=SS_link(tsm, thee))
        if (tsm != sm)
            for (i=1; i<VV_dimVV(thee); i++)
                for (j=0; j<i; j++)
                    for (k=0; k<j; k++)
                        if ( (    (SS_vertex(tsm,i) == v0)
                               && (SS_vertex(tsm,j) == v1)
                               && (SS_vertex(tsm,k) == v2) )
                          || (    (SS_vertex(tsm,i) == v0)
                               && (SS_vertex(tsm,j) == v2)
                               && (SS_vertex(tsm,k) == v1) )
                          || (    (SS_vertex(tsm,i) == v1)
                               && (SS_vertex(tsm,j) == v0)
                               && (SS_vertex(tsm,k) == v2) )
                          || (    (SS_vertex(tsm,i) == v1)
                               && (SS_vertex(tsm,j) == v2)
                               && (SS_vertex(tsm,k) == v0) )
                          || (    (SS_vertex(tsm,i) == v2)
                               && (SS_vertex(tsm,j) == v0)
                               && (SS_vertex(tsm,k) == v1) )
                          || (    (SS_vertex(tsm,i) == v2)
                               && (SS_vertex(tsm,j) == v1)
                               && (SS_vertex(tsm,k) == v0) ) )
                            return tsm;
    return VNULL;
}

/*
 * ***************************************************************************
 * Routine:  VV_commonVertex3
 *
 * Purpose:  I can't actually remember what this guys does!!!
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* VV_commonVertex3(VV *thee, VV *v0, VV *v1)
{
    EE *eg, *eg0, *eg1;
    VASSERT( thee != VNULL );
    VASSERT( v0 != VNULL );
    VASSERT( v1 != VNULL );
    for (eg=VV_firstEE(thee); eg!=VNULL; eg=EE_link(eg, thee)) {
        for (eg0=VV_firstEE(v0); eg0!=VNULL; eg0=EE_link(eg0, v0)) {
            for (eg1=VV_firstEE(v1); eg1!=VNULL; eg1=EE_link(eg1, v1)) {
                if (  (EE_otherVertex(eg,thee)==EE_otherVertex(eg0,v0))
                   && (EE_otherVertex(eg,thee)==EE_otherVertex(eg1,v1)) )
                    return EE_otherVertex(eg,thee);
            }
        }
    }
    return VNULL;
}

/*
 * ***************************************************************************
 * Routine:  VV_commonVertex4
 *
 * Purpose:  I can't actually remember what this guys does!!!
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* VV_commonVertex4(VV *thee, VV *v0, VV *v1, VV *v2)
{
    EE *eg, *eg0, *eg1, *eg2;
    VASSERT( thee != VNULL );
    VASSERT( v0 != VNULL );
    VASSERT( v1 != VNULL );
    VASSERT( v2 != VNULL );
    for (eg=VV_firstEE(thee); eg!=VNULL; eg=EE_link(eg, thee)) {
        for (eg0=VV_firstEE(v0); eg0!=VNULL; eg0=EE_link(eg0, v0)) {
            for (eg1=VV_firstEE(v1); eg1!=VNULL; eg1=EE_link(eg1, v1)) {
                for (eg2=VV_firstEE(v2); eg2!=VNULL; eg2=EE_link(eg2, v2)) {
                    if (  (EE_otherVertex(eg,thee)==EE_otherVertex(eg0,v0))
                       && (EE_otherVertex(eg,thee)==EE_otherVertex(eg1,v1))
                       && (EE_otherVertex(eg,thee)==EE_otherVertex(eg2,v2)) )
                        return EE_otherVertex(eg,thee);
                }
            }
        }
    }
    return VNULL;
}

/*
 * ***************************************************************************
 * Class E: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_GEM)

/*
 * ***************************************************************************
 * Routine:  EE_init
 *
 * Purpose:  Initialize an edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_init(EE *thee, int dim, int id)
{
    thee->d.vPtr[0] = VNULL;
    thee->d.vPtr[1] = VNULL;
    thee->d.ePtr[0] = VNULL;
    thee->d.ePtr[1] = VNULL;
    thee->d.midPtr  = VNULL;
    thee->d.eParent = VNULL;
    Vel_init((Vel*)thee, dim, id);
}

/*
 * ***************************************************************************
 * Routine:  EE_reinit
 *
 * Purpose:  Re-initialize an edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_reinit(EE *thee)
{
    /* keep the dimension and id information */
    thee->d.vPtr[0] = VNULL;
    thee->d.vPtr[1] = VNULL;
    thee->d.ePtr[0] = VNULL;
    thee->d.ePtr[1] = VNULL;
    thee->d.midPtr  = VNULL;
    thee->d.eParent = VNULL;
    Vel_reinit((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_setReality
 *
 * Purpose:  Set the reality.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setReality(EE *thee, int reel)
{
    Vel_setReality((Vel*)thee, reel);
}

/*
 * ***************************************************************************
 * Routine:  EE_setDim
 *
 * Purpose:  Set the dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setDim(EE *thee, int dim)
{
    Vel_setDim((Vel*)thee, dim);
}

/*
 * ***************************************************************************
 * Routine:  EE_setClass
 *
 * Purpose:  Set the class.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setClass(EE *thee, int clas)
{
    Vel_setClass((Vel*)thee, clas);
}

/*
 * ***************************************************************************
 * Routine:  EE_setType
 *
 * Purpose:  Set the type.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setType(EE *thee, int type)
{
    Vel_setType((Vel*)thee, type);
}

/*
 * ***************************************************************************
 * Routine:  EE_setChart
 *
 * Purpose:  Set the chart.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setChart(EE *thee, int chart)
{
    Vel_setChart((Vel*)thee, chart);
}

/*
 * ***************************************************************************
 * Routine:  EE_setId
 *
 * Purpose:  Set the ID.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setId(EE *thee, int id)
{
    Vel_setId((Vel*)thee, id);
}

/*
 * ***************************************************************************
 * Routine:  EE_reality
 *
 * Purpose:  Return the reality.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int EE_reality(EE *thee)
{
    return Vel_reality((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_dim
 *
 * Purpose:  Return the dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int EE_dim(EE *thee)
{
    return Vel_dim((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_dimVV
 *
 * Purpose:  Return the number of vertices in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int EE_dimVV(EE *thee)
{
    return Vel_dimVV((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_dimEE
 *
 * Purpose:  Return the number of edges in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int EE_dimEE(EE *thee)
{
    return Vel_dimEE((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_dimFF
 *
 * Purpose:  Return the number of faces in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int EE_dimFF(EE *thee)
{
    return Vel_dimFF((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_class
 *
 * Purpose:  Return the class.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int EE_class(EE *thee)
{
    return Vel_class((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_type
 *
 * Purpose:  Return the type.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int EE_type(EE *thee)
{
    return Vel_type((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_chart
 *
 * Purpose:  Return the chart.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int EE_chart(EE *thee)
{
    return Vel_chart((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_id
 *
 * Purpose:  Return the ID.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int EE_id(EE *thee)
{
    return Vel_id((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_setVertex
 *
 * Purpose:  Set one of the two vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setVertex(EE *thee, int i, VV *vx)
{
    thee->d.vPtr[i] = vx;
}

/*
 * ***************************************************************************
 * Routine:  EE_setMidPoint
 *
 * Purpose:  Set the midpoint of the edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setMidPoint(EE *thee, VV *vx)
{
    thee->d.midPtr = vx;
}

/*
 * ***************************************************************************
 * Routine:  EE_setParent
 *
 * Purpose:  Set the parent edge pointer.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setParent(EE *thee, EE *eg)
{
    thee->d.eParent = eg;
}

/*
 * ***************************************************************************
 * Routine:  EE_setVertexOrder
 *
 * Purpose:  Set the vertex order.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setVertexOrder(EE *thee, VV *vxTmp)
{
    /* enforce an ordering if both vertices have been set */
    if (VV_id(thee->d.vPtr[0]) > VV_id(thee->d.vPtr[1])) {
        vxTmp = thee->d.vPtr[1];
        thee->d.vPtr[1] = thee->d.vPtr[0];
        thee->d.vPtr[0] = vxTmp;
    }
}

/*
 * ***************************************************************************
 * Routine:  EE_setLink
 *
 * Purpose:  Set the next edge pointer associated with one of the vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_setLink(EE *thee, VV *vx, EE *eg)
{
    if      (vx == (VV*)thee->d.vPtr[0]) thee->d.ePtr[0] = eg;
    else if (vx == (VV*)thee->d.vPtr[1]) thee->d.ePtr[1] = eg;
    else Vnm_print(2, "EE_setLink: Don't have that vertex!\n");
}

/*
 * ***************************************************************************
 * Routine:  EE_vertex
 *
 * Purpose:  Return one of the vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* EE_vertex(EE *thee, int i)
{
    return (VV*)(thee->d.vPtr[i]);
}

/*
 * ***************************************************************************
 * Routine:  EE_midPoint
 *
 * Purpose:  Return the midpoint of the edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* EE_midPoint(EE *thee)
{
    return (VV*)(thee->d.midPtr);
}

/*
 * ***************************************************************************
 * Routine:  EE_parent
 *
 * Purpose:  Return the parent edge pointer.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* EE_parent(EE *thee)
{
    return (EE*)(thee->d.eParent);
}

/*
 * ***************************************************************************
 * Routine:  EE_otherVertex
 *
 * Purpose:  Return the vertex not matching the input vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* EE_otherVertex(EE *thee, VV *vx)
{
    if      (vx == (VV*)(thee->d.vPtr[0])) return (VV*)(thee->d.vPtr[1]);
    else if (vx == (VV*)(thee->d.vPtr[1])) return (VV*)(thee->d.vPtr[0]);
    Vnm_print(2, "EE_otherVertex: Don't have that vertex!\n");
    return VNULL;
}

/*
 * ***************************************************************************
 * Routine:  EE_link
 *
 * Purpose:  Return the next edge in the ring around a given vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* EE_link(EE *thee, VV *vx)
{
    if      (vx == (VV*)(thee->d.vPtr[0])) return (EE*)(thee->d.ePtr[0]);
    else if (vx == (VV*)(thee->d.vPtr[1])) return (EE*)(thee->d.ePtr[1]);
    Vnm_print(2, "EE_link: Don't have that vertex!\n");
    return VNULL;
}

#endif /* if !defined(VINLINE_GEM) */
/*
 * ***************************************************************************
 * Class E: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  EE_ctor
 *
 * Purpose:  The edge constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* EE_ctor(int dim, int myid)
{
    EE *thee = VNULL;

    VDEBUGIO("EE_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(EE) );

    thee->d.vPtr[0] = VNULL;
    thee->d.vPtr[1] = VNULL;
    thee->d.ePtr[0] = VNULL;
    thee->d.ePtr[1] = VNULL;
    thee->d.midPtr  = VNULL;
    thee->d.eParent = VNULL;
    Vel_init((Vel*)thee, dim, myid);

    VDEBUGIO("..done.\n");

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  EE_dtor
 *
 * Purpose:  The edge destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_dtor(EE **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        VDEBUGIO("EE_dtor: DESTROYING object..");
        Vmem_free( VNULL, 1, sizeof(EE), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  EE_initRing
 *
 * Purpose:  Initialize the edge rings.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_initRing(EE *thee)
{
    thee->d.ePtr[0] = VNULL;
    thee->d.ePtr[1] = VNULL;
}

/*
 * ***************************************************************************
 * Routine:  EE_meltRing
 *
 * Purpose:  Destroy the edge rings.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_meltRing(EE *thee)
{
    VV_removeEdgeFromRing(EE_vertex(thee,0), thee);
    VV_removeEdgeFromRing(EE_vertex(thee,1), thee);
}

/*
 * ***************************************************************************
 * Routine:  EE_buildRing
 *
 * Purpose:  Build the edge rings.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void EE_buildRing(EE *thee)
{
    /* make sure ring empty, and that we have two unique vertices first! */
    if (  (EE_link(thee, EE_vertex(thee,0)) != VNULL)
       || (EE_link(thee, EE_vertex(thee,1)) != VNULL) ) {
        Vnm_print(2,"EE_buildRing: called on non-VNULL ring!\n");
        VASSERT(0);
    }
    if ( EE_vertex(thee,0) == EE_vertex(thee,1) ) {
        Vnm_print(2,"EE_buildRing: duplicate vertices in edge <%d>\n",
            EE_id(thee));
        Vnm_print(2,"EE_buildRing: this mesh is unusable!\n");
        VASSERT(0);
    }

    /* okay, build the rings */
    VV_addEdgeToRing(EE_vertex(thee,0), thee);
    VV_addEdgeToRing(EE_vertex(thee,1), thee);
}

/*
 * ***************************************************************************
 * Class S: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_GEM)

/*
 * ***************************************************************************
 * Routine:  SS_init
 *
 * Purpose:  Initialize a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_init(SS *thee, int dim, int id)
{
    thee->d.vPtr[0] = VNULL;
    thee->d.vPtr[1] = VNULL;
    thee->d.vPtr[2] = VNULL;
    thee->d.vPtr[3] = VNULL;
    thee->d.sPtr[0] = VNULL;
    thee->d.sPtr[1] = VNULL;
    thee->d.sPtr[2] = VNULL;
    thee->d.sPtr[3] = VNULL;
#   if defined(VG_ELEMENT)
        thee->d.fNum[0] = -1;
        thee->d.fNum[1] = -1;
        thee->d.fNum[2] = -1;
        thee->d.fNum[3] = -1;
        thee->d.eNum[0] = -1;
        thee->d.eNum[1] = -1;
        thee->d.eNum[2] = -1;
        thee->d.eNum[3] = -1;
        thee->d.eNum[4] = -1;
        thee->d.eNum[5] = -1;
#   endif
    thee->d.tags    = MASK_00000000000000000000000000000000;
    Vel_init((Vel*)thee, dim, id);
}

/*
 * ***************************************************************************
 * Routine:  SS_reinit
 *
 * Purpose:  Re-initialize a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_reinit(SS *thee)
{
    /* keep the dimension information */
    thee->d.vPtr[0] = VNULL;
    thee->d.vPtr[1] = VNULL;
    thee->d.vPtr[2] = VNULL;
    thee->d.vPtr[3] = VNULL;
    thee->d.sPtr[0] = VNULL;
    thee->d.sPtr[1] = VNULL;
    thee->d.sPtr[2] = VNULL;
    thee->d.sPtr[3] = VNULL;
#   if defined(VG_ELEMENT)
        thee->d.fNum[0] = -1;
        thee->d.fNum[1] = -1;
        thee->d.fNum[2] = -1;
        thee->d.fNum[3] = -1;
        thee->d.eNum[0] = -1;
        thee->d.eNum[1] = -1;
        thee->d.eNum[2] = -1;
        thee->d.eNum[3] = -1;
        thee->d.eNum[4] = -1;
        thee->d.eNum[5] = -1;
#   endif
    thee->d.tags    = MASK_00000000000000000000000000000000;
    Vel_reinit((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_setReality
 *
 * Purpose:  Set the reality.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setReality(SS *thee, int reel)
{
    Vel_setReality((Vel*)thee, reel);
}

/*
 * ***************************************************************************
 * Routine:  SS_setDim
 *
 * Purpose:  Set the dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setDim(SS *thee, int dim)
{
    Vel_setDim((Vel*)thee, dim);
}

/*
 * ***************************************************************************
 * Routine:  SS_setClass
 *
 * Purpose:  Set the class.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setClass(SS *thee, int clas)
{
    Vel_setClass((Vel*)thee, clas);
}

/*
 * ***************************************************************************
 * Routine:  SS_setType
 *
 * Purpose:  Set the type.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setType(SS *thee, int type)
{
    Vel_setType((Vel*)thee, type);
}

/*
 * ***************************************************************************
 * Routine:  SS_setChart
 *
 * Purpose:  Set the chart.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setChart(SS *thee, int chart)
{
    Vel_setChart((Vel*)thee, chart);
}

/*
 * ***************************************************************************
 * Routine:  SS_setId
 *
 * Purpose:  Set the ID.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setId(SS *thee, int id)
{
    Vel_setId((Vel*)thee, id);
}

/*
 * ***************************************************************************
 * Routine:  SS_reality
 *
 * Purpose:  Return the reality.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_reality(SS *thee)
{
    return Vel_reality((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_dim
 *
 * Purpose:  Return the dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_dim(SS *thee)
{
    return Vel_dim((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_dimVV
 *
 * Purpose:  Return the number of vertices in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_dimVV(SS *thee)
{
    return Vel_dimVV((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_dimEE
 *
 * Purpose:  Return the number of edges in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_dimEE(SS *thee)
{
    return Vel_dimEE((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_dimFF
 *
 * Purpose:  Return the number of faces in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_dimFF(SS *thee)
{
    return Vel_dimFF((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_class
 *
 * Purpose:  Return the class.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_class(SS *thee)
{
    return Vel_class((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_type
 *
 * Purpose:  Return the type.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_type(SS *thee)
{
    return Vel_type((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_chart
 *
 * Purpose:  Return the chart.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_chart(SS *thee)
{
    return Vel_chart((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_id
 *
 * Purpose:  Return the ID.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_id(SS *thee)
{
    return Vel_id((Vel*)thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_setFaceType
 *
 * Purpose:  Set the face type.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setFaceType(SS *thee, int f, int type)
{ 
    if (f==0) {
        thee->d.faces &= MASK_11111111111111111111111100000000;
        thee->d.faces |= type;
    } else if (f==1) {
        thee->d.faces &= MASK_11111111111111110000000011111111;
        thee->d.faces |= (type << 8);
    } else if (f==2) {
        thee->d.faces &= MASK_11111111000000001111111111111111;
        thee->d.faces |= (type << 16);
    } else if (f==3) {
        thee->d.faces &= MASK_00000000111111111111111111111111;
        thee->d.faces |= (type << 24);
    } else Vnm_print(2, "SS_setFaceType: Don't have that face!\n");
}

/*
 * ***************************************************************************
 * Routine:  SS_setRefinementEdge
 *
 * Purpose:  Set the refinement edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setRefinementEdge(SS *thee, int i)
{
    thee->d.tags &= MASK_11111111111111111111111111111000;
    thee->d.tags |= (i);
}

/*
 * ***************************************************************************
 * Routine:  SS_setMarkedEdge1
 *
 * Purpose:  Set the first marked edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setMarkedEdge1(SS *thee, int i)
{ 
    thee->d.tags &= MASK_11111111111111111111111111000111;
    thee->d.tags |= (i << 3);
}

/*
 * ***************************************************************************
 * Routine:  SS_setMarkedEdge2
 *
 * Purpose:  Set the second marked edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setMarkedEdge2(SS *thee, int i)
{ 
    thee->d.tags &= MASK_11111111111111111111111000111111;
    thee->d.tags |= (i << 6);
}

/*
 * ***************************************************************************
 * Routine:  SS_setMarkedEdge3
 *
 * Purpose:  Set the third marked edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setMarkedEdge3(SS *thee, int i)
{ 
    thee->d.tags &= MASK_11111111111111111111000111111111;
    thee->d.tags |= (i << 9);
}

/*
 * ***************************************************************************
 * Routine:  SS_setDegen
 *
 * Purpose:  Set degenerate marking flag.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setDegen(SS *thee, int i)
{
    thee->d.tags &= MASK_11111111111111111000111111111111;
    thee->d.tags |= (i << 12);
}

/*
 * ***************************************************************************
 * Routine:  SS_setRefinementCount
 *
 * Purpose:  Set the refinement count.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setRefinementCount(SS *thee, int i)
{ 
    VASSERT( (i>=0) && (i<=7) );
    thee->d.tags &= MASK_11111111111111000111111111111111;
    thee->d.tags |= (i << 15);
}

/*
 * ***************************************************************************
 * Routine:  SS_setRefineKey
 *
 * Purpose:  Set the refinement key.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setRefineKey(SS *thee, int which, int key)
{ 
    if (which == 0) {
        thee->d.tags &= MASK_11111111111110111111111111111111;
        thee->d.tags |= (key << 18);
    } else {
        thee->d.tags &= MASK_11111111111101111111111111111111;
        thee->d.tags |= (key << 19);
    }
}
#if defined(VG_ELEMENT)
    VPUBLIC void SS_setFaceNumber(SS *thee, int i, int fn)
    {
        thee->d.fNum[i] = fn;
    }
    VPUBLIC void SS_setEdgeNumber(SS *thee, int i, int en)
    {
        thee->d.eNum[i] = en;
    }
#endif

/*
 * ***************************************************************************
 * Routine:  SS_setVertex
 *
 * Purpose:  Set a given vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setVertex(SS *thee, int i, VV *vx)
{
    thee->d.vPtr[i] = vx;
}

/*
 * ***************************************************************************
 * Routine:  SS_setLink
 *
 * Purpose:  Set the next simplex pointer for a given simplex ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_setLink(SS *thee, VV *vx, SS *sm)
{
    if      (vx == (VV*)thee->d.vPtr[0]) { thee->d.sPtr[0] = sm; return; }
    else if (vx == (VV*)thee->d.vPtr[1]) { thee->d.sPtr[1] = sm; return; }
    else if (vx == (VV*)thee->d.vPtr[2]) { thee->d.sPtr[2] = sm; return; }
    else if (vx == (VV*)thee->d.vPtr[3]) { thee->d.sPtr[3] = sm; return; }
    Vnm_print(2, "SS_setLink: Don't have that vertex!\n");
}

/*
 * ***************************************************************************
 * Routine:  SS_faceType
 *
 * Purpose:  Set the type of a given face.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_faceType(SS *thee, int f)
{ 
    if (f==0)
        return  (thee->d.faces & MASK_00000000000000000000000011111111);
    else if (f==1)
        return ((thee->d.faces & MASK_00000000000000001111111100000000) >> 8);
    else if (f==2)
        return ((thee->d.faces & MASK_00000000111111110000000000000000) >> 16);
    else if (f==3)
        return ((thee->d.faces & MASK_11111111000000000000000000000000) >> 24);
    else
        Vnm_print(2, "SS_faceType: Don't have that face!\n");
    return 0;
}

/*
 * ***************************************************************************
 * Routine:  SS_refinementEdge
 *
 * Purpose:  Return the refinement edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_refinementEdge(SS *thee)
{
    return  (thee->d.tags & MASK_00000000000000000000000000000111);
}

/*
 * ***************************************************************************
 * Routine:  SS_markedEdge1
 *
 * Purpose:  Return the first marked edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_markedEdge1(SS *thee)
{
    return ((thee->d.tags & MASK_00000000000000000000000000111000) >> 3);
}

/*
 * ***************************************************************************
 * Routine:  SS_markedEdge2
 *
 * Purpose:  Return the second marked edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_markedEdge2(SS *thee)
{
    return ((thee->d.tags & MASK_00000000000000000000000111000000) >> 6);
}

/*
 * ***************************************************************************
 * Routine:  SS_markedEdge3
 *
 * Purpose:  Return the third marked edge.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_markedEdge3(SS *thee)
{
    return ((thee->d.tags & MASK_00000000000000000000111000000000) >> 9);
}

/*
 * ***************************************************************************
 * Routine:  SS_degen
 *
 * Purpose:  Return the degenerate edge marker.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_degen(SS *thee)
{
    return ((thee->d.tags & MASK_00000000000000000111000000000000) >> 12);
}

/*
 * ***************************************************************************
 * Routine:  SS_refinementCount
 *
 * Purpose:  Return the refinement count.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_refinementCount(SS *thee)
{ 
    return ((thee->d.tags & MASK_00000000000000111000000000000000) >> 15);
}

/*
 * ***************************************************************************
 * Routine:  SS_refineKey
 *
 * Purpose:  Return the refinement key.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int SS_refineKey(SS *thee, int which)
{ 
    if (which == 0)
        return ((thee->d.tags & MASK_00000000000001000000000000000000) >> 18);
    else
        return ((thee->d.tags & MASK_00000000000010000000000000000000) >> 19);
}

#if defined(VG_ELEMENT)
    VPUBLIC int SS_faceNumber(SS *thee, int i)
    {
        return (thee->d.fNum[i]);
    }
    VPUBLIC int SS_edgeNumber(SS *thee, int i)
    {
        return (thee->d.eNum[i]);
    }
#endif

/*
 * ***************************************************************************
 * Routine:  SS_vertex
 *
 * Purpose:  Return a given vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC VV* SS_vertex(SS *thee, int i)
{
    return (VV*)(thee->d.vPtr[i]);
}

/*
 * ***************************************************************************
 * Routine:  SS_link
 *
 * Purpose:  Return the next simplex in a given simplex ring.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* SS_link(SS *thee, VV *vx)
{
    if      (vx == (VV*)(thee->d.vPtr[0])) return (SS*)(thee->d.sPtr[0]);
    else if (vx == (VV*)(thee->d.vPtr[1])) return (SS*)(thee->d.sPtr[1]);
    else if (vx == (VV*)(thee->d.vPtr[2])) return (SS*)(thee->d.sPtr[2]);
    else if (vx == (VV*)(thee->d.vPtr[3])) return (SS*)(thee->d.sPtr[3]);
    Vnm_print(2, "SS_link: Don't have that vertex!\n");
    return VNULL;
}

/*
 * ***************************************************************************
 * Routine:  SS_faceVertexNumber
 *
 * Purpose:  Return local vertex number i for face f.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int SS_faceVertexNumber(SS *thee, int f, int i)
{
    return vmapF[f][i];
}

/*
 * ***************************************************************************
 * Routine:  SS_vptr2localVnum
 *
 * Purpose:  Return the local vertex number associated with a given vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int SS_vptr2localVnum(SS *thee, VV *vx)
{
    if      (vx == (VV*)thee->d.vPtr[0]) return 0;
    else if (vx == (VV*)thee->d.vPtr[1]) return 1;
    else if (vx == (VV*)thee->d.vPtr[2]) return 2;
    else if (SS_dim(thee) == 3) if (vx == (VV*)thee->d.vPtr[3]) return 3;
    Vnm_print(2, "SS_vptr2localVnum: Don't have that vertex!\n");
    return 0;
}

#endif /* if !defined(VINLINE_GEM) */
/*
 * ***************************************************************************
 * Class S: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  SS_ctor
 *
 * Purpose:  The simplex constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* SS_ctor(int dim, int myid)
{
    SS *thee = VNULL;

    VDEBUGIO("SS_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(SS) );

    thee->d.vPtr[0] = VNULL;
    thee->d.vPtr[1] = VNULL;
    thee->d.vPtr[2] = VNULL;
    thee->d.vPtr[3] = VNULL;
    thee->d.sPtr[0] = VNULL;
    thee->d.sPtr[1] = VNULL;
    thee->d.sPtr[2] = VNULL;
    thee->d.sPtr[3] = VNULL;
    thee->d.fPtr[0] = VNULL;
    thee->d.fPtr[1] = VNULL;
    thee->d.fPtr[2] = VNULL;
    thee->d.fPtr[3] = VNULL;
#   if defined(VG_ELEMENT)
        thee->d.fNum[0] = -1;
        thee->d.fNum[1] = -1;
        thee->d.fNum[2] = -1;
        thee->d.fNum[3] = -1;
        thee->d.eNum[0] = -1;
        thee->d.eNum[1] = -1;
        thee->d.eNum[2] = -1;
        thee->d.eNum[3] = -1;
        thee->d.eNum[4] = -1;
        thee->d.eNum[5] = -1;
#   endif
    thee->d.tags    = MASK_00000000000000000000000000000000;
    Vel_init((Vel*)thee, dim, myid);

    VDEBUGIO("..done.\n");

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  SS_dtor
 *
 * Purpose:  The simplex destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_dtor(SS **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        VDEBUGIO("SS_dtor: DESTROYING object..");
        Vmem_free( VNULL, 1, sizeof(SS), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  SS_initRing
 *
 * Purpose:  Initialize the simplex rings.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_initRing(SS *thee)
{
    unsigned int i;
    for (i=0; i<SS_dimVV(thee); i++)
        thee->d.sPtr[i] = VNULL;
}

/*
 * ***************************************************************************
 * Routine:  SS_meltRing
 *
 * Purpose:  Destroy the simplex rings.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_meltRing(SS *thee)
{
    unsigned int i;
    for (i=0; i<SS_dimVV(thee); i++)
        VV_removeSimplexFromRing(SS_vertex(thee,i),thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_buildRing
 *
 * Purpose:  Build the simplex rings.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_buildRing(SS *thee)
{
    unsigned int i,j;

    /* make sure ring empty, and we have d+1 unique vertices first! */
    for (i=0; i<SS_dimVV(thee); i++) {
        if ( SS_link(thee, SS_vertex(thee,i)) != VNULL ) {
            Vnm_print(2,"SS_buildRing: called on non-VNULL ring!\n");
            VASSERT(0);
        }
        for (j=0; j<i; j++) {
            if ( SS_vertex(thee,i) == SS_vertex(thee,j) ) {
                Vnm_print(2,"SS_buildRing: duplicate vertices in"
                    " simplex <%d>\n", SS_id(thee));
                Vnm_print(2,"SS_buildRing: this mesh is unusable!\n");
                VASSERT(0);
            }
        }
    }

    /* okay, build the rings */
    for (i=0; i<SS_dimVV(thee); i++)
        VV_addSimplexToRing(SS_vertex(thee,i),thee);
}

/*
 * ***************************************************************************
 * Routine:  SS_nabor
 *
 * Purpose:  Return the simplex sharing face i (opposite vertex i).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* SS_nabor(SS *thee, int i)
{
    if (SS_dim(thee)==2) {
        return VV_commonSimplex2( SS_vertex(thee,(i+1)%3),
            SS_vertex(thee,(i+2)%3), thee ); 
    } else { /* (SS_dim(thee)==3) */
        return VV_commonSimplex3( SS_vertex(thee,(i+1)%4),
            SS_vertex(thee,(i+2)%4), SS_vertex(thee,(i+3)%4), thee ); 
    }
}

/*
 * ***************************************************************************
 * Routine:  SS_edge
 *
 * Purpose:  Return the edge connecting vertices i and j.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC EE* SS_edge(SS *thee, int i, int j)
{
    return VV_commonEdge(SS_vertex(thee,i), SS_vertex(thee,j));
}

/*
 * ***************************************************************************
 * Routine:  SS_sharedFaceLocNum
 *
 * Purpose:  Return local face number of face shared between two simplices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int SS_sharedFaceLocNum(SS *thee, SS *sm)
{
    if      (sm == SS_nabor(thee,0)) return 0;
    else if (sm == SS_nabor(thee,1)) return 1;
    else if (sm == SS_nabor(thee,2)) return 2;
    else if (SS_dim(thee) == 3) if (sm == SS_nabor(thee,3)) return 3;
    Vnm_print(2, "SS_sharedFaceLocNum: Don't have that face!\n");
    return 0;
}

/*
 * ***************************************************************************
 * Routine:  SS_localEdgeType
 *
 * Purpose:  Return the proper edge type (interior/boundary) of an edge
 *           connecting the two given vertices.
 *
 * Notes:    ASSUME that the edge DOES NOT exist or does not have a correct
 *           and consistent type, and calculate its type from the face types.
 * 
 *           The type we calculate is based only on local info; in 3D it may
 *           NOT be the correct edge type for the edge as far as the global
 *           mesh is concerned.  However, the local information about all
 *           simplices using the edge can be combined to determine the
 *           correct global type.
 *
 *           We must not be tempted to look for an existing edge and then
 *           grab its type; the edge may have just been created (with
 *           interior type by default), and in fact WE are being called as
 *           part of an attempt to calculate its global type...
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int SS_localEdgeType(SS *thee, VV *v0, VV *v1)
{
    int i,j,fTypeA,fTypeB,eType,vertA_otherThan_ij,vertB_otherThan_ij;

    i = SS_vptr2localVnum(thee,v0);
    j = SS_vptr2localVnum(thee,v1);
    VASSERT( i != j );
    eType = 0;

    /*
     * In 2D, we have only one face using this edge, and in fact we can
     * determine both the local and global types of the edge by simply
     * looking at that one face.
     */
    if (SS_dim(thee) == 2) {

        vertA_otherThan_ij = vmapOV2[0][i][j];
        eType = SS_faceType( thee, vertA_otherThan_ij );

    /*
     * In 3D, we have two faces using this edge.  After we locate the 
     * faces, we determine the edge type from the faces types as follows:
     * (1) If both faces are interior, the edge is interior
     * (2) If at least one face is boundary, the edge is boundary
     */
    } else if (SS_dim(thee) == 3) {

        vertA_otherThan_ij = vmapOV2[0][i][j];
        vertB_otherThan_ij = vmapOV2[1][i][j];

        fTypeA = SS_faceType( thee, vertA_otherThan_ij );
        fTypeB = SS_faceType( thee, vertB_otherThan_ij );

        /* If at least one face is boundary, the edge is boundary */
        if ( VBOUNDARY(fTypeA) || VBOUNDARY(fTypeB) ) {
            if ( VBOUNDARY(fTypeA) && VBOUNDARY(fTypeB) ) {
                eType = VMAX2(fTypeA,fTypeB);
            } else if ( VBOUNDARY(fTypeA) ) {
                eType = fTypeA;
            } else if ( VBOUNDARY(fTypeB) ) {
                eType = fTypeB;
            } else {
                eType = 1;
                VASSERT(0);
            }
        /* If all faces are interior, the edge is interior */
        } else {
            eType = 0;
        }

    } else { VASSERT(0); }

    return eType;
}

/*
 * ***************************************************************************
 * Routine:  SS_reverse
 *
 * Purpose:  Reverse the orientation of a simplex by swapping vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void SS_reverse(SS *thee)
{
    VV *vx0, *vx1;
    int ft0, ft1;

    SS_meltRing(thee);
    vx0 = SS_vertex( thee, 0 );
    vx1 = SS_vertex( thee, 1 );
    ft0 = SS_faceType( thee, 0 );
    ft1 = SS_faceType( thee, 1 );
    SS_setVertex( thee, 0, vx1 );
    SS_setVertex( thee, 1, vx0 );
    SS_setFaceType( thee, 0, ft1 );
    SS_setFaceType( thee, 1, ft0 );
    SS_buildRing( thee );
}

/*
 * ***************************************************************************
 * Routine:  FF_ctor
 *
 * Purpose:  The FF constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC FF* FF_ctor(int grandParentFace, SS *sPtr, int color)
{
    /* DAN-MIKE: */
    FF *thee = VNULL;
    int dim = 0;

    VDEBUGIO("FF_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(FF) );
   
    thee->d.gID    = color;
    thee->d.sPtr   = sPtr;
    thee->d.rhist  = 0;
    thee->d.rlevel = 0;

    Vel_init((Vel*)thee, dim, grandParentFace);  /* init gip sub-structure */

    VDEBUGIO("..done.\n");

    return thee;
}

