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
 * rcsid="$Id: gemchk.c,v 1.17 2010/08/12 05:18:53 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     Gemchk.c
 *
 * Purpose:  Class Gem: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "gem_p.h"

VEMBED(rcsid="$Id: gemchk.c,v 1.17 2010/08/12 05:18:53 fetk Exp $")

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
 * Routine:  Gem_memChk
 *
 * Purpose:  Print the exact current malloc usage.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_memChk(Gem *thee)
{
    int i;

    if (thee->iMadeVmem) Vmem_print(thee->vmem);
    if (thee->vertices  != VNULL) Vset_memChk(thee->vertices);
    if (thee->edges     != VNULL) Vset_memChk(thee->edges);
    if (thee->simplices != VNULL) Vset_memChk(thee->simplices);
    for (i=0; i<VMAXSQ; i++) {
        if (thee->sQueM[i] != VNULL) Vset_memChk(thee->sQueM[i]);
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_memChkVV
 *
 * Purpose:  Print the exact current malloc usage: vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_memChkVV(Gem *thee, int *num,
    int *size, int *vecUse, int *vecMal, int *vecOhd)
{
    Vset_check(thee->vertices, num, size, vecUse, vecMal, vecOhd);
}

/*
 * ***************************************************************************
 * Routine:  Gem_memChkEE
 *
 * Purpose:  Print the exact current malloc usage: edges.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_memChkEE(Gem *thee, int *num,
    int *size, int *vecUse, int *vecMal, int *vecOhd)
{
    Vset_check(thee->edges, num, size, vecUse, vecMal, vecOhd);
}

/*
 * ***************************************************************************
 * Routine:  Gem_memChkSS
 *
 * Purpose:  Print the exact current malloc usage: simplices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_memChkSS(Gem *thee, int *num,
    int *size, int *vecUse, int *vecMal, int *vecOhd)
{
    Vset_check(thee->simplices, num, size, vecUse, vecMal, vecOhd);
}

/*
 * ***************************************************************************
 * Routine:  Gem_memChkSQ
 *
 * Purpose:  Print the exact current malloc usage: simplex queues.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_memChkSQ(Gem *thee, int currentQ,
    int *tnum, int *tsize, int *tVecUse, int *tVecMal, int *tVecOhd)
{
    Vset_check(thee->sQueM[currentQ], tnum, tsize, tVecUse, tVecMal, tVecOhd);
}

/*
 * ***************************************************************************
 * Routine:  Gem_memChkMore
 *
 * Purpose:  Estimate the current RAM usage.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_memChkMore(Gem *thee)
{
    int i, geom_ramUse, geom_ramMal, geom_ramOhd;

    int v_num,  v_size,  v_ramUse,  v_ramMal,  v_ramOhd;
    int e_num,  e_size,  e_ramUse,  e_ramMal,  e_ramOhd;
    int s_num,  s_size,  s_ramUse,  s_ramMal,  s_ramOhd;
    int sq_num, sq_size, sq_ramUse, sq_ramMal, sq_ramOhd;

    Vnm_print(0, "Gem_memChkMore: Geometry memory usage\n");

    /* get sizes of vertices, edges, simplices */
    Gem_memChkVV(thee,
        &v_num,  &v_size,  &v_ramUse,  &v_ramMal,  &v_ramOhd);
    Gem_memChkEE(thee,
        &e_num,  &e_size,  &e_ramUse,  &e_ramMal,  &e_ramOhd);
    Gem_memChkSS(thee,
        &s_num,  &s_size,  &s_ramUse,  &s_ramMal,  &s_ramOhd);
    Vnm_print(0, "%9d VV ;%3d bytes/VV =%9d bytes[%9d:t=%9d:b+%6d:o]\n",
        v_num, v_size, v_ramUse, (v_ramMal+v_ramOhd), v_ramMal, v_ramOhd);
    Vnm_print(0, "%9d EE ;%3d bytes/EE =%9d bytes[%9d:t=%9d:b+%6d:o]\n",
        e_num, e_size, e_ramUse, (e_ramMal+e_ramOhd), e_ramMal, e_ramOhd);
    Vnm_print(0, "%9d SS ;%3d bytes/SS =%9d bytes[%9d:t=%9d:b+%6d:o]\n",
        s_num, s_size, s_ramUse, (s_ramMal+s_ramOhd), s_ramMal, s_ramOhd);

    /* get simplex Q sizes and also total all of the sizes */
    geom_ramUse = v_ramUse + s_ramUse + e_ramUse;
    geom_ramMal = v_ramMal + s_ramMal + e_ramMal;
    geom_ramOhd = v_ramOhd + s_ramOhd + e_ramOhd;
    for (i=0; i<VMAXSQ; i++) {
        Gem_memChkSQ(thee,
            i,&sq_num,&sq_size,&sq_ramUse,&sq_ramMal,&sq_ramOhd);
        Vnm_print(0, "%9d Q%d ;%3d bytes/Q0 =%9d bytes[%9d:t=%9d:b+%6d:o]\n",
            sq_num, i, sq_size, sq_ramUse, (sq_ramMal+sq_ramOhd),
            sq_ramMal, sq_ramOhd);
        geom_ramUse += sq_ramUse;
        geom_ramMal += sq_ramMal;
        geom_ramOhd += sq_ramOhd;
    }
    Vnm_print(0, "                    TOTALS =%9d bytes[%9d:t=%9d:b+%6d:o]\n",
        geom_ramUse, (geom_ramMal+geom_ramOhd), geom_ramMal, geom_ramOhd);
}

/*
 * ***************************************************************************
 * Routine:  Gem_speedChk
 *
 * Purpose:  Calculate the cost to traverse the various structures.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_speedChk(Gem *thee)
{
    const int N = 100000;
    const int loop = 1000;
    int i, j, itotal;
    double rtotal;
    double *d0;
    int *i0;
    VV *v0, *vx;

    Vnm_print(0,"Gem_speedChk: Creating normal double vec...\n");
    Vnm_tstart(90, "double vec creation");
    d0 = Vmem_malloc( thee->vmem, N, sizeof(double) );
    Vnm_tstop(90, "double vec creation");

    Vnm_print(0,"Gem_speedChk: Creating normal int vec...\n");
    Vnm_tstart(90, "int vec creation");
    i0 = Vmem_malloc( thee->vmem, N, sizeof(int) );
    Vnm_tstop(90, "int vec creation");

    Vnm_print(0,"Gem_speedChk: Creating normal VV vec...\n");
    Vnm_tstart(90, "VV vec creation");
    v0 = Vmem_malloc( thee->vmem, N, sizeof(VV) );
    Vnm_tstop(90, "VV vec creation");

    Vnm_print(0,"Gem_speedChk: Creating Vset VV vec...\n");
    Vnm_tstart(90, "VV Vset creation");
    for (i=0; i<N; i++)
        vx = Gem_createAndInitVV(thee);
    Vnm_tstop(90, "VV Vset creation");

    Vnm_print(0,"Gem_speedChk: Looping over double vec...\n");
    Vnm_print(0,"Gem_speedChk: N, loop = %d, %d\n", N, loop);
    Vnm_tstart(90, "double vec loop");
    rtotal = 0.0;
    for (j=0; j<loop; j++)
        for (i=0; i<N; i++)
            rtotal += ( j * d0[i] * (j+d0[i]) );
    Vnm_tstop(90, "double vec loop");

    Vnm_print(0,"Gem_speedChk: Looping over int vec...\n");
    Vnm_print(0,"Gem_speedChk: N, loop = %d, %d\n", N, loop);
    Vnm_tstart(90, "int vec loop");
    itotal = 0;
    for (j=0; j<loop; j++)
        for (i=0; i<N; i++)
            itotal += ( j * i0[i] * (j+i0[i]) );
    Vnm_tstop(90, "int vec loop");

    Vnm_print(0,"Gem_speedChk: Looping over VV vec...\n");
    Vnm_print(0,"Gem_speedChk: N, loop = %d, %d\n", N, loop);
    Vnm_tstart(90, "VV vec loop");
    itotal = 0;
    for (j=0; j<loop; j++)
        for (i=0; i<N; i++)
            itotal += ( j * VV_id(&v0[i]) * (j+VV_id(&v0[i])) );
    Vnm_tstop(90, "VV vec loop");

    Vnm_print(0,"Gem_speedChk: Looping (index) over Vset VV vec...\n");
    Vnm_print(0,"Gem_speedChk: N, loop = %d, %d\n", N, loop);
    Vnm_tstart(90, "VV Vset loop");
    itotal = 0;
    for (j=0; j<loop; j++)
        for (i=0; i<N; i++)
            itotal += ( j * VV_id(Gem_VV(thee,i)) 
                     * (j + VV_id(Gem_VV(thee,i)) ) );
    Vnm_tstop(90, "VV Vset loop");

    Vnm_print(0,"Gem_speedChk: Looping (iterator) over Vset VV vec...\n");
    Vnm_print(0,"Gem_speedChk: N, loop = %d, %d\n", N, loop);
    Vnm_tstart(90, "VV Vset loop");
    itotal = 0;
    for (j=0; j<loop; j++)
        for (vx=Gem_firstVV(thee);vx!=VNULL;vx=Gem_nextVV(thee))
            itotal += ( j * VV_id(vx) * (j + VV_id(vx)) );
    Vnm_tstop(90, "VV Vset loop");

    Vnm_print(0,"Gem_speedChk: Freeing normal double vec...\n");
    Vnm_tstart(90, "Free double vec");
    Vmem_free( thee->vmem, N, sizeof(double), (void**)&d0 );
    Vnm_tstop(90, "Free double vec");

    Vnm_print(0,"Gem_speedChk: Freeing normal int vec...\n");
    Vnm_tstart(90, "Free int vec");
    Vmem_free( thee->vmem, N, sizeof(int), (void**)&i0 );
    Vnm_tstop(90, "Free int vec");

    Vnm_print(0,"Gem_speedChk: Freeing normal VV vec...\n");
    Vnm_tstart(90, "Free VV vec");
    Vmem_free( thee->vmem, N, sizeof(VV), (void**)&v0 );
    Vnm_tstop(90, "Free VV vec");

    Vnm_print(0,"Gem_speedChk: Freeing Vset VV vec...\n");
    Vnm_tstart(90, "Free VV Vset");
    for (i=0; i<N; i++)
        Gem_destroyVV(thee);
    Vnm_tstop(90, "Free VV Vset");
}

/*
 * ***************************************************************************
 * Routine:  Gem_formChk
 *
 * Purpose:  Check the self-consistency of the geometry datastructures.
 *
 * Notes:    key==0 --> check: min (just vertices and simplices)
 *           key==1 --> check: min + simplex ring
 *           key==2 --> check: min + simplex ring + edge ring
 *           key==3 --> check: min + simplex ring + edge ring + conform
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_formChk(Gem *thee, int key)
{
    int i, j, k;
    int l, m, bndVert, bndFace;
    int edgeOrderProb, conformCount, fType[4];
    double svol;
    VV *vx, *v[4];
    SS *sm, *sm0, *sm1, *sm2;
    EE *eg;

    /* input check and some i/o */
    VASSERT( (key >= 0) && (key <= 3) );

    /* go through all vertices and check for consistency */
    Vnm_tstart(80, "form check");
    Vnm_print(0,"Gem_formChk: Topology check on: "
        "<%d> SS, <%d> EE, <%d> VV:\n",
        Gem_numSS(thee), Gem_numEE(thee), Gem_numVV(thee));
    Vnm_print(0,"Gem_formChk: ..VV..\n");
    bndVert = 0;
    for (i=0; i<Gem_numVV(thee); i++) {
        vx = Gem_VV(thee,i);
        if ( (i>0) && (i % VPRTKEY) == 0 ) Vnm_print(0,"[CV:%d]",i);
        VJMPERR1( !Vnm_sigInt() );

        /* check basic data */
        if ((int)VV_id(vx)!=i)
            Vnm_print(2,"Gem_formChk: VV_id BAD vtx <%d>\n", i);
        if (key == 0) {
            if (VV_firstSS(vx) != VNULL)
                Vnm_print(2,"Gem_formChk: firstS BAD vtx <%d>\n",i);
            if (VV_firstEE(vx) != VNULL)
                Vnm_print(2,"Gem_formChk: firstE BAD vtx <%d>\n",i);
        } else if (key == 1) {
            if (VV_firstSS(vx) == VNULL)
                Vnm_print(2,"Gem_formChk: firstS BAD vtx <%d>\n",i);
            if (VV_firstEE(vx) != VNULL)
                Vnm_print(2,"Gem_formChk: firstE BAD vtx <%d>\n",i);
        } else if ((key == 2) || (key == 3)) {
            if (VV_firstSS(vx) == VNULL)
                Vnm_print(2,"Gem_formChk: firstS BAD vtx <%d>\n",i);
            if ((VV_firstEE(vx) == VNULL) && (Gem_numEE(thee) > 0))
                Vnm_print(2,"Gem_formChk: firstE BAD vtx <%d>\n",i);
        } else { VASSERT(0); }

        /* boundary data */
        if ( VBOUNDARY( VV_type(vx) ) ) bndVert++;
    }
    if (bndVert != Gem_numBV(thee))
        Vnm_print(2,"Gem_formChk: bndVert BAD\n");

    /* go through all edges and check for consistency */
    if (key >= 2) {
        Vnm_print(0,"Gem_formChk: ..EE..\n");
        edgeOrderProb = 0;
        for (i=0; i<Gem_numEE(thee); i++) {
            eg = Gem_EE(thee,i);
            if ( (i>0) && (i % VPRTKEY) == 0 ) Vnm_print(0,"[CE:%d]",i);
            VJMPERR1( !Vnm_sigInt() );

            /* check basic data */
            /* (edge re-orderings ok; may not be error) */
            if ((int)EE_id(eg) != i) edgeOrderProb = 1;
            if ( EE_vertex(eg,0) == VNULL )
                Vnm_print(2,"Gem_formChk: vertex0 BAD edge <%d>\n",i);
            if ( EE_vertex(eg,1) == VNULL )
                Vnm_print(2,"Gem_formChk: vertex1 BAD edge <%d>\n",i);

            /* check edge ring consistencies */
            if ( ! VV_edgeInRing(EE_vertex(eg,0), eg) )
                Vnm_print(2,"Gem_formChk: edgeInRing0 BAD edge <%d>\n",i);
            if ( ! VV_edgeInRing(EE_vertex(eg,1), eg) )
                Vnm_print(2,"Gem_formChk: edgeInRing1 BAD edge <%d>\n",i);

            /* check midpoint data; should be VNULL */
            if ( EE_midPoint(eg) != VNULL )
                Vnm_print(2,"Gem_formChk: midPoint BAD edge <%d>\n",i);
        }
        if (edgeOrderProb)
            Vnm_print(0,"Gem_formChk: WARNING noncons edge order..)\n");
    }

    /* go through all simplices and check for consistency */
    Vnm_print(0,"Gem_formChk: ..SS..\n");
    bndFace = 0;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        if ( (i>0) && (i % VPRTKEY) == 0 ) Vnm_print(0,"[CS:%d]",i);
        VJMPERR1( !Vnm_sigInt() );

        if ( (int)SS_id(sm) != i )
            Vnm_print(2,"Gem_formChk: SS_id BAD sim <%d>\n",i);

        /* check for well-ordering of vertices through positive volume */
        svol = Gem_simplexVolume(thee,sm);
        if (svol <= VSMALL)
            Vnm_print(2,"Gem_formChk: Degenerate sim <%d> has volume <%g>\n",
                i, svol);

        /* another check for well-ordering of vertices via positive volume */
        if ( !Gem_orient(thee,sm) )
            Vnm_print(2,"Gem_formChk: sim <%d> is badly ordered\n", i);

        /* no simplices should be marked for refinement/unrefinement */
        if ( SS_refineKey(sm,0) != 0 )
            Vnm_print(2,"Gem_formChk: SS_refineKey BAD sim <%d>\n",i);
        if ( SS_refineKey(sm,1) != 0 )
            Vnm_print(2,"Gem_formChk: SS_refineKey BAD sim <%d>\n",i);

        /* get simplex face info */
        for (j=0; j<4; j++) fType[j] = SS_faceType(sm,j);

        /* check vertex data and simplex ring structure */
        for (j=0; j<Gem_dimVV(thee); j++) {
            v[j] = SS_vertex(sm,j);
            if ( v[j] == VNULL )
                Vnm_print(2,"Gem_formChk: v[%d] BAD sim <%d>\n",j,i);
            if (key >= 1) {
                if ( ! VV_simplexInRing( v[j], sm ) )
                    Vnm_print(2,"Gem_formChk: sInR BAD sim <%d>\n",i);
            }
        }

        /* check simplex ring, boundary faces count, vertex type */
        for (j=0; j<Gem_dimVV(thee); j++) {

            /* boundary vertex check */
            if ( VBOUNDARY(fType[j]) ) {
                bndFace++;
                for (k=1; k<Gem_dimVV(thee); k++) {
                    l=(j+k) % Gem_dimVV(thee);
                    if ( VINTERIOR( VV_type(SS_vertex(sm,l)) ) )
                        Vnm_print(2,"Gem_formChk: Dv[%d] BAD sim <%d>\n",
                            l,i);
                }
            }

            /* face check with all nabors; verify we are conforming */
            if (key >= 3) {
                k=(j+1) % Gem_dimVV(thee);
                l=(k+1) % Gem_dimVV(thee);
                m=(l+1) % Gem_dimVV(thee);
                conformCount = 0;
                for (sm0=VV_firstSS(v[k]); sm0!=VNULL;sm0=SS_link(sm0,v[k])) {
                    for (sm1=VV_firstSS(v[l]);sm1!=VNULL;sm1=SS_link(sm1,v[l])){
                        if (Gem_dim(thee) == 2) {
                            if ((sm0!=sm) && (sm0==sm1)) conformCount++;
                        } else {
                            for (sm2=VV_firstSS(v[m]); sm2!=VNULL; 
                              sm2=SS_link(sm2,v[m])) {
                                if ((sm0!=sm) && (sm0==sm1) && (sm0==sm2)) {
                                    conformCount++;
                                }
                            }
                        }
                    }
                }
                if ( VBOUNDARY(fType[j]) ) {
                    if ( conformCount != 0 ) {
                        Vnm_print(2,"Gem_formChk: conform BAD sim <%d>",i);
                        Vnm_print(2,"..face <%d> should NOT have a nabor\n",j);
                    }
                } else {
                    if ( conformCount < 1 ) {
                        Vnm_print(2,"Gem_formChk: conform BAD sim <%d>",i);
                        Vnm_print(2,"..face <%d> should have a nabor\n",j);
                    }
                    if ( conformCount > 1 ) {
                        Vnm_print(2,"Gem_formChk: conform BAD sim <%d>",i);
                        Vnm_print(2,"..face <%d> has more than one nabor\n",j);
                    }
                }
            }

        }
    }
    if ( bndFace != Gem_numBF(thee) )
        Vnm_print(2,"Gem_formChk: numBF count BAD\n");
    Vnm_print(0,"Gem_formChk: ..done.\n");

    /* return with no errors */
    Vnm_tstop(80, "form check");
    return;

  VERROR1:
    Vnm_print(0,"Gem_formChk: ..done.  [Early termination was forced]\n");
    Vnm_tstop(80, "form check");
    return;
}

/*
 * ***************************************************************************
 * Routine:  Gem_contentChk
 *
 * Purpose:  Print out contents of all geometry structures.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_contentChk(Gem *thee)
{
    int i, j, k, ii;
    SS *sm;
    EE *eg;
    VV *vx;

    Vnm_print(0,"Gem_contentChk: printing data.\n");
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        Vnm_print(0,"SIMPLEX [%d]\n", SS_id(sm));
        Vnm_print(0,"  g.bits =<%d>\n",sm->g.bits);
        Vnm_print(0,"  g.uid  =<%d>\n",sm->g.uid);
        Vnm_print(0,"  d.tags =<%d>\n",sm->d.tags);
        Vnm_print(0,"  d.faces=<%d>\n",sm->d.faces);

        Vnm_print(0,"  d.vPtr =");
        for (ii=0; ii<4; ii++) {
            j = -1;
            if (sm->d.vPtr[ii] != VNULL) j = VV_id(sm->d.vPtr[ii]);
            Vnm_print(0," <%d>",j);
        }
        Vnm_print(0,"\n");

        Vnm_print(0,"  d.sPtr =");
        for (ii=0; ii<4; ii++) {
            j = -1;
            if (sm->d.sPtr[ii] != VNULL) j = SS_id(sm->d.sPtr[ii]);
            Vnm_print(0," <%d>",j);
        }
        Vnm_print(0,"\n");

#       if defined(VG_ELEMENT)
            Vnm_print(0,"  d.fNum =");
            for (ii=0; ii<4; ii++) {
                j = sm->d.fNum[ii];
                Vnm_print(0," <%d>",j);
            }
            Vnm_print(0,"\n");

            Vnm_print(0,"  d.eNum =");
            for (ii=0; ii<6; ii++) {
                j = sm->d.eNum[ii];
                Vnm_print(0," <%d>",j);
            }
            Vnm_print(0,"\n");
#       endif

    }
    for (i=0; i<Gem_numEE(thee); i++) {
        eg = Gem_EE(thee,i);
        Vnm_print(0,"EDGE [%d]\n", EE_id(eg));
        Vnm_print(0,"  g.bits=<%d>\n",eg->g.bits);
        Vnm_print(0,"  g.uid =<%d>\n",eg->g.uid);
        k = 0;
        if (eg->d.midPtr != VNULL) k = VV_id(eg->d.midPtr);
        Vnm_print(0,"  d.midPtr=<%d>\n", k);

        Vnm_print(0,"  d.vPtr =");
        for (ii=0; ii<2; ii++) {
            j = 0;
            if (eg->d.vPtr[ii] != 0) j = VV_id(eg->d.vPtr[ii]);
            Vnm_print(0," <%d>",j);
        }
        Vnm_print(0,"\n");

        Vnm_print(0,"  d.ePtr =");
        for (ii=0; ii<2; ii++) {
            j = 0;
            if (eg->d.ePtr[ii] != 0) j = EE_id(eg->d.ePtr[ii]);
            Vnm_print(0," <%d>",j);
        }
        Vnm_print(0,"\n");
    }
    for (i=0; i<Gem_numVV(thee); i++) {
        vx = Gem_VV(thee,i);
        Vnm_print(0,"VERTEX [%d]\n", VV_id(vx));
        Vnm_print(0,"  g.bits=<%d>\n",vx->g.bits);
        Vnm_print(0,"  g.uid =<%d>\n",vx->g.uid);
        j = 0;
        k = 0;
        if (vx->d.ePtr != VNULL) j = EE_id(vx->d.ePtr);
        if (vx->d.sPtr != VNULL) k = SS_id(vx->d.sPtr);
        Vnm_print(0,"  d.ePtr=<%d>\n", j);
        Vnm_print(0,"  d.sPtr=<%d>\n", k);
        Vnm_print(0,"  d.x   =");
        for (ii=0; ii<3; ii++)
            Vnm_print(0," <%e>", vx->d.x[ii]);
        Vnm_print(0,"\n");
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_ramClear
 *
 * Purpose:  Clear some structures.
 *
 * Notes:    key==0 --> clear down to: min (vertices and simplices)
 *           key==1 --> clear down to: min + simplex ring
 *           key==2 --> clear down to: min + simplex ring + edges + edge ring
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_ramClear(Gem *thee, int key)
{
    /* input check and some i/o */
    VASSERT( (-1 <= key) && (key <= 2) );

    /* clear the geometry structures */
    if (key == 2) {
        Vnm_print(0, "Gem_ramClear: clearing queues..");
        Gem_resetSQ(thee,0);
        Gem_resetSQ(thee,1);
        Vnm_print(0, "..done.\n");
    } else if (key == 1) {
        Vnm_print(0, "Gem_ramClear: clearing edges..");
        Gem_resetEE(thee);
        Vnm_print(0, "..done.\n");
    } else if (key == 0) {
    } else if (key == -1) {
        Vnm_print(0, "Gem_ramClear: clearing vertices..");
        Gem_resetVV(thee);
        Vnm_print(0, "..done.\n");
        Vnm_print(0, "Gem_ramClear: clearing simplices..");
        Gem_resetSS(thee);
        Vnm_print(0, "..done.\n");
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_makeBnd
 *
 * Purpose:  Force naborless faces to become boundary faces.
 *
 * Notes:    btype==0 --> create interior boundary faces
 *           btype==1 --> create boundary faces of type "1"
 *           btype==2 --> create boundary faces of type "2"
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_makeBnd(Gem *thee, int btype)
{
    int i, j, k, l, m, nabors;
    VV *v[4];
    SS *sm, *sm0, *sm1, *sm2;

    /* input check and some i/o */
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
    if (btype == 0) return;

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
 * Routine:  Gem_makeBndExt
 *
 * Purpose:  Mark selected boundary faces in a special way.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_makeBndExt(Gem *thee, int key)
{
    int i, j, k, l, m, p, q, nabors, btype, done, btypeGeneric;
    VV *v[4];
    SS *sm, *sm0, *sm1, *sm2;
    double x[4][3], xchk;

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

                /* grab coordinates of the vertices of this face */
                for (q=0; q<Gem_dim(thee); q++) {
                    x[0][q] = VV_coord(v[k],q);
                }
                for (q=0; q<Gem_dim(thee); q++) {
                    x[1][q] = VV_coord(v[l],q);
                }
                if (Gem_dim(thee) == 3) {
                    for (q=0; q<Gem_dim(thee); q++) {
                        x[2][q] = VV_coord(v[m],q);
                    }
                }

                /* default is interior; should not occur! */
                btypeGeneric = 18;
                done = 0;
                btype = btypeGeneric;

                /* ---------- check for base marking ---------- */
                xchk = 0.0;
                for (p=0; p<Gem_dim(thee); p++) {
                    xchk += VABS( x[p][1] - (-1.0) );
                }
                if (xchk < VSMALL) {
                    done = 1;
                    btype = 1;
                }

                /* ---------- check for base marking again ---------- */
                xchk = 0.0;
                for (p=0; p<Gem_dim(thee); p++) {
                    xchk += VABS( x[p][1] - ( 0.0) );
                }
                if (xchk < VSMALL) {
                    done = 1;
                    btype = 18;
                }

                /* ---------- check for first section ---------- */
                if (!done) {
                    done = 1;
                    btype = 2;
                    for (p=0; p<Gem_dim(thee); p++) {
                        if (! (  ( 1.9    <= x[p][0])
                              && ( 6.1    >= x[p][0])
                              && (-VSMALL <= x[p][1])
                              && (-1.1    <= x[p][2])
                              && ( 1.1    >= x[p][2]) )) {
                            done = 0;
                            btype = btypeGeneric;
                        }
                    }

                    if (done) {
                        xchk = 0.0;
                        for (p=0; p<Gem_dim(thee); p++) {
                            xchk += VABS( x[p][1] - 10.0 );
                        }
                        if (xchk < VSMALL) {
                            btype = 10;
                        }
                    }
                }

                /* ---------- check for second section ---------- */
                if (!done) {
                    done = 1;
                    btype = 4;
                    for (p=0; p<Gem_dim(thee); p++) {
                        if (! (  ( 7.9    <= x[p][0])
                              && (12.1    >= x[p][0])
                              && (-VSMALL <= x[p][1])
                              && (-1.1    <= x[p][2])
                              && ( 1.1    >= x[p][2]) )) {
                            done = 0;
                            btype = btypeGeneric;
                        }
                    }

                    if (done) {
                        xchk = 0.0;
                        for (p=0; p<Gem_dim(thee); p++) {
                            xchk += VABS( x[p][1] - 10.0 );
                        }
                        if (xchk < VSMALL) {
                            btype = 12;
                        }
                    }
                }



                /* ---------- check for third section ---------- */
                if (!done) {
                    done = 1;
                    btype = 6;
                    for (p=0; p<Gem_dim(thee); p++) {
                        if (! (  (13.9    <= x[p][0])
                              && (18.1    >= x[p][0])
                              && (-VSMALL <= x[p][1])
                              && (-1.1    <= x[p][2])
                              && ( 1.1    >= x[p][2]) )) {
                            done = 0;
                            btype = btypeGeneric;
                        }
                    }

                    if (done) {
                        xchk = 0.0;
                        for (p=0; p<Gem_dim(thee); p++) {
                            xchk += VABS( x[p][1] - 10.0 );
                        }
                        if (xchk < VSMALL) {
                            btype = 14;
                        }
                    }
                }


                /* ---------- check for fourth section ---------- */
                if (!done) {
                    done = 1;
                    btype = 8;
                    for (p=0; p<Gem_dim(thee); p++) {
                        if (! (  (19.9    <= x[p][0])
                              && (24.1    >= x[p][0])
                              && (-VSMALL <= x[p][1])
                              && (-1.1    <= x[p][2])
                              && ( 1.1    >= x[p][2]) )) {
                            done = 0;
                            btype = btypeGeneric;
                        }
                    }

                    if (done) {
                        xchk = 0.0;
                        for (p=0; p<Gem_dim(thee); p++) {
                            xchk += VABS( x[p][1] - 10.0 );
                        }
                        if (xchk < VSMALL) {
                            btype = 16;
                        }
                    }
                }

                /* should have been marked with SOME boundary type */
                VASSERT( 0 != btype );

                /* set the facetype */
                SS_setFaceType(sm, j, btype);
                Gem_numBFpp(thee);

                /* set the vertex types (dirichlet overrides robin) */
                if (!VDIRICHLET( VV_type(v[k])) ) {
                    if (VINTERIOR( VV_type(v[k])) ) {
                        Gem_numBVpp(thee);
                    }
                    VV_setType(v[k], btype);
                }
                if (!VDIRICHLET( VV_type(v[l])) ) {
                    if (VINTERIOR( VV_type(v[l])) ) {
                        Gem_numBVpp(thee);
                    }
                    VV_setType(v[l], btype);
                }
                if (Gem_dim(thee) == 3) {
                    if (!VDIRICHLET( VV_type(v[m])) ) {
                        if (VINTERIOR( VV_type(v[m])) ) {
                            Gem_numBVpp(thee);
                        }
                        VV_setType(v[m], btype);
                    }
                }
            }
        }
    }
    Vnm_print(0,"..done.\n");
}

