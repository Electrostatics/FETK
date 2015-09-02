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
 * rcsid="$Id: gemunref.c,v 1.7 2010/08/12 05:18:57 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     Gemunref.c
 *
 * Purpose:  Class Gem: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "gem_p.h"

VEMBED(rcsid="$Id: gemunref.c,v 1.7 2010/08/12 05:18:57 fetk Exp $")

/*
 * ***************************************************************************
 * Class Gem: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_GEM)

#endif /* if !defined(VINLINE_GEM) */
/*
 * ***************************************************************************
 * Class Gem: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Gem_unRefine
 *
 * Purpose:  Un-refine the mesh.
 *
 * Input:    If (key==0) Simply toss out the marked simplices; this leaves
 *                       "holes", and we mark all neighbor faces that were
 *                       revealed as boundary faces.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_unRefine(Gem *thee, int rkey, int pkey)
{
    int unrefined,currentQ;
    SS *sm;

    /* un-refinement main loop */
    Vnm_print(0,"Gem_unRefine: un-refining marked simps..\n");

    /* count number actually unrefined */
    unrefined = 0;

    /* first pass setup; keep track of which queue is which.. */
    currentQ = 0;

    /* go through all simplices (backwards!) and unrefine marked ones */
    for (sm=Gem_lastSS(thee); sm!=VNULL; sm=Gem_prevSS(thee)) {
        if (SS_refineKey(sm,0) != 0) {

            /* simply delete the marked simplex (possibly creating a hole) */
            if (rkey == 0) {
                Gem_delSimplex(thee, sm, currentQ);
            } else { VASSERT(0); }

            unrefined++;
        }
    }

    /* remove any hanging vertices */
    Gem_unHangVertices(thee);

    /* count v/e/f/s and check the mesh */
    Gem_countChk(thee);

    return unrefined;
}

/*
 * ***************************************************************************
 * Routine:  Gem_delSimplex
 *
 * Purpose:  Delete a simplex cleanly, maintaining a consecutive list
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_delSimplex(Gem *thee, SS *sm, int currentQ)
{
    int i, j, face;
    SS *lastS;

    /* mark all the neighbor faces as boundary faces */
    for (i=0; i<Gem_dimVV(thee); i++) {
        SS *nb = SS_nabor(sm,i);
        if (nb != VNULL) {
            face = SS_sharedFaceLocNum(nb,sm);
            if (VINTERIOR( SS_faceType(nb,face) )) {
                SS_setFaceType( nb, face, 1 );
                Gem_numBFpp(thee);
                for (j=0; j<Gem_dimVV(thee)-1; j++) {
                    int vv = SS_faceVertexNumber(nb, face, j);
                    if (VINTERIOR( VV_type( SS_vertex(nb,vv) )) ) {
                        VV_setType( SS_vertex(nb,vv), 1 );
                        Gem_numBVpp(thee);
                    }
                }
            }
        }
    }

    /* before destroying last simplex, fix boundary face counts */
    for (i=0; i<Gem_dimVV(thee); i++) {
        if (VBOUNDARY( SS_faceType(sm,i) )) Gem_numBFmm(thee);
    }

    /* pull sm out of its simplex rings */
    SS_meltRing(sm);
    SS_reinit(sm);

    /* if sm is not last in the list, exchange it with the last one */
    if ( sm != (lastS=Gem_lastSS(thee)) ) {
        SS_meltRing(lastS);
        SS_setType(sm, SS_type(lastS));
        SS_setChart(sm, SS_chart(lastS));
        for (j=0; j<Gem_dimVV(thee); j++) {
            SS_setVertex( sm, j, SS_vertex(lastS,j) );
            SS_setFaceType( sm, j, SS_faceType(lastS,j) );
        }
        SS_reinit(lastS);
        SS_buildRing(sm);
        SS_setRefineKey(sm,currentQ,0);
    }

    /* now delete the last guy */
    Gem_destroySS(thee);
}

/*
 * ***************************************************************************
 * Routine:  Gem_unHangVertices
 *
 * Purpose:  Toss out any hanging vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_unHangVertices(Gem *thee)
{
    /* go through all vertices (backwards!) and DELETE any hanging ones */
    int i, j, myid, numSimps;
    SS *qs,*simps[100];
    int verts[100];
    VV *vx, *lastV;

    for (vx=Gem_lastVV(thee); vx!=VNULL; vx=Gem_prevVV(thee)) {
        if (VV_firstSS(vx) == VNULL) {

            /* before destroying last vertex, fix boundary vertex counts */
            if ( VBOUNDARY( VV_type(vx) ) ) Gem_numBVmm(thee);

            /* copy last guy into our slot (unless we are last). */
            lastV=Gem_peekLastVV( thee );
            if ( vx != lastV ) {

                /* find all simplices which point to last guy */
                numSimps=0;
                for (qs=VV_firstSS(lastV);qs!=VNULL;qs=SS_link(qs,lastV)) {
                    simps[numSimps] = qs;

                    /* record vertex number of simplex pointing to last guy */
                    verts[numSimps] = -1; 
                    for (j=0; j<Gem_dimVV(thee); j++)
                        if (SS_vertex(qs,j) == lastV)
                            verts[numSimps] = j; 
                    VASSERT( verts[numSimps] >= 0 );
                    numSimps++;
                }
                VASSERT( numSimps <= 100 );

                /* copy last guy's data to me */
                myid=VV_id(vx);
                VV_reinit(vx);
                for (j=0; j<Gem_dimII(thee); j++)
                    VV_setCoord( vx, j, VV_coord(lastV,j) );
                VV_setId( vx, myid );

                /* melt and then rebuild the simplex rings */
                for (i=0; i<numSimps; i++) {
                    SS_meltRing(simps[i]);
                    SS_setVertex(simps[i],verts[i], vx);
                    SS_buildRing(simps[i]);
                }
            }

            /* now delete the last guy */
            VV_reinit(lastV);
            Gem_destroyVV( thee );
        }
    }
}

