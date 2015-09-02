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
 * rcsid="$Id: gemg.c,v 1.17 2010/08/12 05:18:56 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     Gemg.c
 *
 * Purpose:  Class Gem: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "gem_p.h"

VEMBED(rcsid="$Id: gemg.c,v 1.17 2010/08/12 05:18:56 fetk Exp $")

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
 * Routine:  Gem_simplexInfo
 *
 * Purpose:  Build the basic master-to-element transformation information.
 *
 * Notes:
 *
 *      gchart              ==> unified common chart for vertex coordinates
 *      chart[4]            ==> individual charts for vertex coordinates
 *
 *      D                   ==> jacobian determinant of the transformation
 *      Dcook               ==> jacobian determinant of cooked trans
 *      faceD[4]            ==> face jacobian determinants
 *
 *      ff[3][3], bb[3]     ==> affine trans from master to arbitrary el
 *      gg[3][3], cc[3]     ==> affine trans from arbitrary el to master
 *
 *      loc[4][3]           ==> local ordering of vertices for each face
 *      vx[4][3]            ==> vertex coordinate labels
 *      nvec[4][3]          ==> normal vectors to the faces
 *      evec[6][3]          ==> edge vectors
 *      elen[6]             ==> edge vector lengths
 *
 *      dimV                ==> number of vertices in the d-simplex
 *      dimE                ==> number of edges in the d-simplex
 *      dimF                ==> number of faces in the d-simplex
 *      dimS                ==> number of simplices in the d-simplex (=1)
 *
 *      sid                 ==> global simplex ID
 *      vid[4]              ==> global vertex IDs
 *      fid[4]              ==> global face IDs
 *      eid[6]              ==> global edge IDs
 *
 *      stype               ==> global simplex type
 *      vtype[4]            ==> global vertex types
 *      ftype[4]            ==> global face types
 *      etype[6]            ==> LOCAL edge types
 *  
 *      *s                  ==> pointer to the simplex
 *      *v[4]               ==> pointers to vertices of the simplex
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_simplexInfo(Gem *thee, SS *sm, TT *t)
{
    unsigned int i, j;
    double area, masterArea, vx[4][3], v0[3], v1[3], v2[3];

    /* this simplex */
    t->s = sm;

    /* basic simplex info */
    t->dimV  = SS_dimVV(t->s);
    t->dimE  = SS_dimEE(t->s);
    t->dimF  = SS_dimVV(t->s);
    t->dimS  = 1;
    t->D     = 1.;
    t->sid   = SS_id(t->s);
    t->stype = SS_type(t->s);

    /* vertex and face info */
    for (j=0; j<3; j++) {
        t->bc[j] = 0.;
    }
    for (i=0; i<SS_dimVV(t->s); i++) {

        t->v[i] = SS_vertex(t->s,i);

        t->chart[i] = VV_chart(t->v[i]);
        t->faceD[i] = 1.;

        t->vid[i]   = VV_id(t->v[i]);
        t->vtype[i] = VV_type(t->v[i]);

#       if defined(VG_ELEMENT)
            t->fid[i]   = SS_faceNumber(t->s,i);
#       endif

        t->ftype[i] = SS_faceType(t->s,i);

        for (j=0; j<3; j++) {
            vx[i][j] = VV_coord(t->v[i],j);
            t->bc[j] += vx[i][j];
            t->nvec[i][j] = 0.;
        }
        for (j=0; j<SS_dim(t->s); j++)
            t->loc[i][j] = vmapF[i][j];
    }
    for (j=0; j<3; j++) {
        t->bc[j] /= SS_dimVV(t->s);
    }

    /* edge info */
    for (i=0; i<SS_dimEE(t->s); i++) {
#       if defined(VG_ELEMENT)
            t->eid[i]   = SS_edgeNumber(t->s,i);
#       endif
        t->etype[i] = 0;
        /* t->etype[i] = SS_edgeType(t->s,i); */
        /*
         * *** If we have the edge list rather than explicit storage of edge
         * *** info in the simplex, then get the edge info as follows:
         * j = vmapEI[i][0];
         * k = vmapEI[i][1];
         * eg = SS_edge(t->s,j,k);
         * t->eid[i]   = EE_id( eg );
         * t->etype[i] = EE_type( eg );
         */
    }

    /* call oneChart to get the vertex coordinates w.r.t. a single chart */
    /* (IF the user is using multiple coordinate systems...) */
    thee->pde->oneChart(Gem_dim(thee), Gem_dimII(thee), t->stype,
        t->chart, vx, SS_dimVV(t->s));

    /* chart choice for all vertices of this simplex */
    t->gchart = t->chart[0];

    /* set vertex coordinates for simplex now w.r.t. a single chart */
    for (i=0; i<SS_dimVV(t->s); i++)
        for (j=0; j<3; j++)
            t->vx[i][j] = vx[i][j];

    /* 2-simplex: get triangle area plus (virtual) 4th vertex along the way */
    if (SS_dim(t->s) == 2) {

        /* produce a unit normal */
        for (i=0; i<3; i++) {
            v0[i] = t->vx[1][i] - t->vx[0][i];
            v1[i] = t->vx[2][i] - t->vx[0][i];
        }
        Vec3_xcry(v2, v0, v1);
        area = Vec3_nrm2(v2);
        Vec3_scal(v2, 1./area);

        /* triangle area is 1/2 parallelogram area given by cross-product */
        area *= 0.5;

        /* transformation jacobian is an area ratio: area(this)/area(master) */
        masterArea = 0.5;
        t->D = area / masterArea;
        /* VASSERT( t->D != 0. ); */
        /* VASSERT( t->D > 0. ); */

        /* cookup a "good" (virtual) fourth vertex from baricenter up normal */
        /* first get the baricenter */
        for (j=0; j<3; j++) {
            t->vx[3][j] = 0.;
            for (i=0; i<3; i++)
                t->vx[3][j] += t->vx[i][j];
            t->vx[3][j] /= 3.;
        }
        /* now move up the normal */
        for (j=0; j<3; j++)
            t->vx[3][j] += v2[j];
    }

    /* we have 4 vertex coords of a (some) tetrahedron (all in one chart) */
    /* SO, now get all 6 edge vectors and 6 edge lengths (squared) */
    for (i=0; i<6; i++) {
        t->elen[i] = 0.0;
        for (j=0; j<3; j++) {
            t->evec[i][j] = t->vx[vmapEI[i][1]][j] - t->vx[vmapEI[i][0]][j];
            t->elen[i] += ( t->evec[i][j]*t->evec[i][j] );
        }
    }

    /* initialize transformations to/from master simplex and this simplex */
    for (i=0; i<3; i++) {
        t->bb[i] = t->vx[0][i];
        t->cc[i] = 0.0;
        for (j=0; j<3; j++) t->gg[i][j] = 0.;
    }
    t->ff[0][0] = t->evec[ vmapE[1][0] ][0];
    t->ff[1][0] = t->evec[ vmapE[1][0] ][1];
    t->ff[2][0] = t->evec[ vmapE[1][0] ][2];
    t->ff[0][1] = t->evec[ vmapE[2][0] ][0];
    t->ff[1][1] = t->evec[ vmapE[2][0] ][1];
    t->ff[2][1] = t->evec[ vmapE[2][0] ][2];
    t->ff[0][2] = t->evec[ vmapE[3][0] ][0];
    t->ff[1][2] = t->evec[ vmapE[3][0] ][1];
    t->ff[2][2] = t->evec[ vmapE[3][0] ][2];

    /* jacobian of the transformation */
    t->Dcook = (t->ff[0][0]*t->ff[1][1]*t->ff[2][2]) 
             + (t->ff[0][1]*t->ff[1][2]*t->ff[2][0])
             + (t->ff[0][2]*t->ff[1][0]*t->ff[2][1]) 
             - (t->ff[2][0]*t->ff[1][1]*t->ff[0][2])
             - (t->ff[1][2]*t->ff[2][1]*t->ff[0][0]) 
             - (t->ff[2][2]*t->ff[1][0]*t->ff[0][1]);

    /* 3-simplex: tetrahedron volume is jacobian of the transformation */
    if (SS_dim(t->s) == 3) t->D = t->Dcook;

    /* 2D PLANER HACK ONLY: make sign reflect orientation of triangle */
#if 1
    if (SS_dim(t->s) == 2)
        if ( (t->ff[0][0]*t->ff[1][1] - t->ff[1][0]*t->ff[0][1]) < 0. )
            t->D = - t->D;
#endif
}

/*
 * ***************************************************************************
 * Routine:  Gem_buildVolumeTrans
 *
 * Purpose:  Build the complete master-to-element transformation.
 *
 * Notes:    We just call Gem_simplexInfo to build the basic information,
 *           and then we compute the transformation and some additional
 *           things like the inverse transformations and various determinants.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_buildVolumeTrans(Gem *thee, SS *sm, TT *t)
{
    unsigned int i, j;
    double Di;

    /* get jacobian with vertex coordinates w.r.t. a single chart */
    Gem_simplexInfo(thee, sm, t);
    /* VASSERT( t->Dcook > 0. ); */
    Di = 1. / t->Dcook;

    /* linear part of inverse transformation from this simplex to master */
    t->gg[0][0] = Di * (t->ff[1][1]*t->ff[2][2] - t->ff[2][1]*t->ff[1][2]);
    t->gg[0][1] = Di * (t->ff[2][1]*t->ff[0][2] - t->ff[0][1]*t->ff[2][2]);
    t->gg[0][2] = Di * (t->ff[0][1]*t->ff[1][2] - t->ff[1][1]*t->ff[0][2]);
    t->gg[1][0] = Di * (t->ff[2][0]*t->ff[1][2] - t->ff[1][0]*t->ff[2][2]);
    t->gg[1][1] = Di * (t->ff[0][0]*t->ff[2][2] - t->ff[2][0]*t->ff[0][2]);
    t->gg[1][2] = Di * (t->ff[1][0]*t->ff[0][2] - t->ff[0][0]*t->ff[1][2]);
    t->gg[2][0] = Di * (t->ff[1][0]*t->ff[2][1] - t->ff[2][0]*t->ff[1][1]);
    t->gg[2][1] = Di * (t->ff[2][0]*t->ff[0][1] - t->ff[0][0]*t->ff[2][1]);
    t->gg[2][2] = Di * (t->ff[0][0]*t->ff[1][1] - t->ff[1][0]*t->ff[0][1]);

    /* affine part of inverse transformation from this simplex to master */
    for (i=0; i<3; i++) {
        t->cc[i] = 0.0;
        for (j=0; j<3; j++)
            t->cc[i] -= t->gg[i][j] * t->bb[j];
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_buildSurfaceTrans
 *
 * Purpose:  Build the complete masterFace-to-elementFace transformation.
 *
 * Notes:    We ASSUME that Gem_simplexInfo has already been called to build
 *           the basic information in the TT structure we are given.
 *           We then compute some additional things here for a SINGLE face
 *           specified by "iface", such as the inverse transformations and 
 *           various determinants.
 *
 *           We do not actually have to assume that Gem_buildVolumeTrans
 *           has been previously called, only that Gem_simplexInfo has
 *           been called.  However, it seems that all situations that
 *           occur result in Gem_buildVolumeTrans being called for an
 *           element before Gem_buildSurfTrans is called on any face.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_buildSurfaceTrans(Gem *thee, int iface, TT *t)
{
    double length, masterLength, area, masterArea, v0[3], v1[3], v2[3];

    /* consistency check */
    VASSERT( (iface>=0) && (iface<(int)SS_dimVV(t->s)) );

    /* Recover el num and local node nums in simplex forming edge; */
    /* recall that iface is the local node num OPPOSITE the edge */
    if (SS_dim(t->s) == 2) {

        /* the unit normal vector */
        v0[0] = t->vx[ t->loc[iface][0] ][0];
        v0[1] = t->vx[ t->loc[iface][0] ][1];
        v0[2] = t->vx[ t->loc[iface][0] ][2];

        v1[0] = t->vx[ t->loc[iface][1] ][0];
        v1[1] = t->vx[ t->loc[iface][1] ][1];
        v1[2] = t->vx[ t->loc[iface][1] ][2];

       /*
        * ********************************************************************
        * Approximate normal for a 3-vector in the plane of the face
        * NOTE: requires that "loc[iface][2]" be defined; CURRENTLY NOT!
        * v2[0] = t->vx[ t->loc[iface][2] ][0];
        * v2[1] = t->vx[ t->loc[iface][2] ][1];
        * v2[2] = t->vx[ t->loc[iface][2] ][2];
        * Vec3_copy(normal, v0);
        * Vec3_axpy(normal, v1, (1.0));
        * Vec3_scal(normal, 0.5);
        * Vec3_axpy(normal, v2, -1.);
        * ********************************************************************
        */
        /* Exact normal for a 2-vector in the 2-d plane */
        Vec3_copy(v2, v0);
        Vec3_axpy(v2, v1, -1.);
        length = Vec3_nrm2(v2);
        t->nvec[iface][0] = -v2[1];
        t->nvec[iface][1] =  v2[0];
        t->nvec[iface][2] =  0.0;
        area = Vec3_nrm2(t->nvec[iface]);
        /* VASSERT( area != 0.0 ); */
        Vec3_scal(t->nvec[iface], 1./area);

        /* master edge length depends on the edge */
        if (iface == 0) {
            masterLength = VSQRT(2.0);
        } else {
            masterLength = 1.0;
        }

        /* transformation jacobian is a length ratio: len(this)/len(master) */
        t->faceD[iface] = length / masterLength;

    } else { /* (SS_dim(t->s) == 3) */

        /* the unit normal vector */
        v0[0] = t->vx[ t->loc[iface][1] ][0] - t->vx[ t->loc[iface][0] ][0];
        v0[1] = t->vx[ t->loc[iface][1] ][1] - t->vx[ t->loc[iface][0] ][1];
        v0[2] = t->vx[ t->loc[iface][1] ][2] - t->vx[ t->loc[iface][0] ][2];
        v1[0] = t->vx[ t->loc[iface][2] ][0] - t->vx[ t->loc[iface][0] ][0];
        v1[1] = t->vx[ t->loc[iface][2] ][1] - t->vx[ t->loc[iface][0] ][1];
        v1[2] = t->vx[ t->loc[iface][2] ][2] - t->vx[ t->loc[iface][0] ][2];
        Vec3_xcry(v2, v0, v1);
        area = Vec3_nrm2(v2);
        Vec3_copy(t->nvec[iface], v2);
        /* VASSERT( area != 0.0 ); */
        Vec3_scal(t->nvec[iface], 1./area);

        /* tri-face area is 1/2 parallelogram area given by cross-product */
        area *= 0.5;

        /* master tri-face area depends on the face */
        if (iface == 0) {
            masterArea = 0.5 * VSQRT(3.0);
        } else {
            masterArea = 0.5;
        }

        /* transformation jacobian is a volume ratio: vol(this)/vol(master) */
        t->faceD[iface] = area / masterArea;
    }
    /* VASSERT ( (t->faceD[iface]) > 0. ); */
}

/*
 * ***************************************************************************
 * Routine:  Gem_edgeLength
 *
 * Purpose:  Calculate the edge lengths of a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Gem_edgeLength(Gem *thee, VV *v0, VV *v1)
{
    int j, edgeType, chart[4];
    double value, vx[4][3];

    /* setup the chart and vertex info */
    chart[0] = VV_chart(v0);
    chart[1] = VV_chart(v1);
    for (j=0; j<Gem_dimII(thee); j++) {
        vx[0][j] = VV_coord(v0,j);
        vx[1][j] = VV_coord(v1,j);
    }

    /* have no idea what the edge type really is */
    edgeType = 0;

    /* call oneChart to get vertex coordinates w.r.t. a single chart */
    thee->pde->oneChart(Gem_dim(thee),Gem_dimII(thee), edgeType,chart,vx,2);

    /* okay, now return the edge length */
    value = 0.;
    for (j=0; j<Gem_dimII(thee); j++)
        value += VSQR( vx[0][j] - vx[1][j] );
    return VSQRT( value );
}

/*
 * ***************************************************************************
 * Routine:  Gem_newestVertex
 *
 * Purpose:  Determine the edge of a simplex opposite the newest vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_newestVertex(Gem *thee, SS *sm, int face, double *len)
{ 
    unsigned int p;
    int v0,v1,v2,localNV;
    long v0_id,v1_id,v2_id,nv;

    /* determine the newest vertex in this simplex */
    nv = -1;
    localNV = -1;
    for (p=0; p<SS_dimVV(sm); p++) {
        v0_id = VV_id( SS_vertex(sm, p) );
        if (v0_id > nv) {
            nv = v0_id;
            localNV = p;
        }
    }
    VASSERT( (localNV >= 0) );

    /* assign one of the opposite edges (there is only one in 2D) */
    v0 = vmapOV3[localNV][0];
    v1 = vmapOV3[localNV][1];
    if (Gem_dim(thee) == 3) {

        /* get the third vertex of opposite face */
        v2 = vmapOV3[localNV][2];

        /* get the global vertex numbers */
        v0_id = VV_id ( SS_vertex(sm, v0) );
        v1_id = VV_id ( SS_vertex(sm, v1) );
        v2_id = VV_id ( SS_vertex(sm, v2) );

        /* if v0 is oldest of (v0,v1), check if v2 is older than v1 */
        if (v0_id < v1_id) {
            if (v2_id < v1_id) {
                v1 = v2;
            }

        /* if v1 is oldest of (v0,v1), check if v2 is older than v0 */
        } else {
            if (v2_id < v0_id) {
                v0 = v2;
            }
        }
    }

    /* return the result */
    return vmapE[v0][v1];
}

/*
 * ***************************************************************************
 * Routine:  Gem_longestEdge
 *
 * Purpose:  Determine the longest edge of a simplex or a simplex face.
 *
 * Note:     It is critical to have a consistent tie-breaking rule in order
 *           to guarantee that recursive refinement procedures:
 *           (1) produce conforming meshes (two simplices will refine the
 *               same edge of a shared face)
 *           (2) terminate in finite steps (due to (1)).
 *
 *           If the following statement is true then A is longer than B:
 *               ( (len(A).ge.len(B)) AND NOT(len(B).eq.len(A)) )
 *
 *           Here len(A) is the length of A, .eq. is a "fuzzy" equals,
 *           and .ge. is a "fuzzy" greater than or equal to.  To define the
 *           fuzzy comparisons we start by defining "greater than or equal to"
 *           ( x.ge.y ) as the logical statement ( x*(1+TOL) >= y ).
 *           Using x.ge.y we then define (x.eq.y) as (x.ge.y AND y.ge.x).
 *
 *           In the case of a tie, the longest is defined as the edge with
 *           the smallest global edge number (as determined by the global 
 *           vertex numbers).
 *
 *           Note that by expanding the .eq. definition and simplifying we
 *           can rewrite the test "A is longer than B" as follows:
 *               ( (len(A).ge.len(B)) AND NOT(len(B).ge.len(A)) )
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC int Gem_longestEdge(Gem *thee, SS *sm, int face, double *len)
{ 
    unsigned int p,q,pp,qq,ii,jj,q_lim;
    int localENumI,localENumJ,vxp_id,vxq_id;
    long kk, vertexMax, globalENum;
    double tmpLen,edgeLen,TOL;
    VV *vxp, *vxq;

    VASSERT( (face==-1) || ((Gem_dim(thee)==3) && (face >=0) && (face <= 3)) );

    localENumI = -1;
    localENumJ = -1;
    vertexMax = 100000000;   /* conservative max of vertex numbers */
    globalENum = -1;         /* the current longest edge global number */
    edgeLen = -VVLARGE;      /* the current longest edge length */
    TOL = VVSMALL;           /* tolerance for our floating point tests */

    if (face == -1) {
        q_lim = SS_dimVV(sm);
    } else {
        q_lim = SS_dimVV(sm) - 1;
    }
    for (q=1; q<q_lim; q++) {
        for (p=0; p<q; p++) {

            if (face == -1) {
                pp = p;
                qq = q;
            } else {
                pp = vmapF[face][p];
                qq = vmapF[face][q];
            }
            vxp = SS_vertex(sm, pp);
            vxq = SS_vertex(sm, qq);
            vxp_id = VV_id( vxp );
            vxq_id = VV_id( vxq );
        
            tmpLen = Gem_edgeLength(thee, vxp, vxq);
            VASSERT( tmpLen > 0. );

	    /* if ( len(this_edge).ge.len(curr_max_edge) ) */
            if ( tmpLen*(1.+TOL) >= edgeLen ) {

                ii = VMAX2( vxp_id, vxq_id );
                jj = VMIN2( vxp_id, vxq_id );
                kk = (vertexMax * ii) + jj;

		/* if ( NOT(len(curr_max_edge).ge.len(this_edge))  */
		/*      OR  num(this_edge) < num(curr_max_edge) )  */
                if ( ( !(edgeLen*(1.+TOL) >= tmpLen) ) 
                         || (kk < globalENum) ) {

                    localENumI = pp;
                    localENumJ = qq;
                    globalENum = kk;
                    edgeLen = tmpLen;

                }
            }
        }
    }

    *len = edgeLen;
    VASSERT( (localENumI>=0) && (localENumJ>=0) );
    return vmapE[localENumI][localENumJ];
}

/*
 * ***************************************************************************
 * Routine:  Gem_shortestEdge
 *
 * Purpose:  Determine the shortest edge of a simplex or a simplex face.
 *
 * Note:     It is critical to have a consistent tie-breaking rule in order
 *           to guarantee that recursive refinement procedures:
 *           (1) produce conforming meshes (two simplices will refine the
 *               same edge of a shared face)
 *           (2) terminate in finite steps (due to (1)).
 *
 *           If the following statement is true then A is shorter than B:
 *               ( (len(B).ge.len(A)) AND NOT(len(A).eq.len(B)) )
 *
 *           Here len(A) is the length of A, .eq. is a "fuzzy" equals,
 *           and .ge. is a "fuzzy" greater than or equal to.  To define the
 *           fuzzy comparisons we start by defining "greater than or equal to"
 *           ( x.ge.y ) as the logical statement ( x*(1+TOL) >= y ).
 *           Using x.ge.y we can define (x.eq.y) as (x.ge.y AND y.ge.x).
 *
 *           In the case of a tie, the shortest is defined as the edge with
 *           the largest global edge number (as determined by the global 
 *           vertex numbers).
 *
 *           Note that by expanding the .eq. definition and simplifying we
 *           can rewrite the test "A is shorter than B" as follows:
 *               ( (len(B).ge.len(A)) AND NOT(len(A).ge.len(B)) )
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC int Gem_shortestEdge(Gem *thee, SS *sm, int face, double *len)
{ 
    unsigned int p,q,pp,qq,ii,jj,q_lim;
    int localENumI,localENumJ,vxp_id,vxq_id;
    long kk, vertexMax, globalENum;
    double tmpLen,edgeLen,TOL;
    VV *vxp, *vxq;

    localENumI = -1;
    localENumJ = -1;
    vertexMax = 100000000;   /* conservative max of vertex numbers */
    globalENum = -1;         /* the current longest edge global number */
    edgeLen = VVLARGE;       /* the current longest edge length */
    TOL = VVSMALL;           /* tolerance for our floating point tests */

    if (face == -1) {
        q_lim = SS_dimVV(sm);
    } else {
        q_lim = SS_dimVV(sm) - 1;
    }
    for (q=1; q<q_lim; q++) {
        for (p=0; p<q; p++) {

            if (face == -1) {
                pp = p;
                qq = q;
            } else {
                pp = vmapF[face][p];
                qq = vmapF[face][q];
            }
            vxp = SS_vertex(sm, pp);
            vxq = SS_vertex(sm, qq);
            vxp_id = VV_id( vxp );
            vxq_id = VV_id( vxq );
            
            tmpLen = Gem_edgeLength(thee, vxp, vxq);
            VASSERT( tmpLen > 0. );

	    /* if ( len(curr_min_edge).ge.len(this_edge) ) */
            if ( edgeLen*(1.+TOL) >= tmpLen ) {

                ii = VMAX2( vxp_id, vxq_id );
                jj = VMIN2( vxp_id, vxq_id );
                kk = (vertexMax * ii) + jj;

		/* if ( NOT(len(this_edge).ge.len(curr_min_edge))  */
		/*      OR num(this_edge) > num(curr_min_edge)  )  */
                if ( ( !( tmpLen*(1.+TOL) >= edgeLen ) )
                        || (kk > globalENum) ) {
                    localENumI = pp;
                    localENumJ = qq;
                    globalENum = kk;
                    edgeLen = tmpLen;
                }
            }
        }
    }
    *len = edgeLen;
    VASSERT( (localENumI>=0) && (localENumJ>=0) );
    return vmapE[localENumI][localENumJ];
}

/*
 * ***************************************************************************
 * Routine:  Gem_edgeRatio
 *
 * Purpose:  Calculate ratio of longest-to-shortest edge of a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Gem_edgeRatio(Gem *thee, SS *sm)
{
    double lLong, lShort;
    Gem_longestEdge(thee, sm, -1, &lLong);
    Gem_shortestEdge(thee, sm, -1, &lShort);
    return lLong / lShort;
}

/*
 * ***************************************************************************
 * Routine:  Gem_simplexVolume
 *
 * Purpose:  Calculate the determinant of the transformation from the
 *           master element to this element.
 *
 * Notes:    We just call Gem_simplexInfo to build the basic information,
 *           and then we build the transformation and compute the determinant
 *           here.
 *
 *           For a manifold, we need to know the orientation of the manifold
 *           in order to decide what is counter-clock-wise, and what is
 *           clockwise, in terms of vertex orderings.  One will lead to a
 *           positive volume, and the other to a negative volume, when we
 *           compute volume using the determinant of the jacobian of the
 *           affine transformation to the master element.  We assume here
 *           that the uniform chart computed by Gem_simplexInfo is such that
 *           the orientation in the chart reflects the correct orientation
 *           of the manifold (locally).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Gem_simplexVolume(Gem *thee, SS *sm)
{
    TT t;
    Gem_simplexInfo(thee, sm, &t);
    return t.D;
}

/*
 * ***************************************************************************
 * Routine:  Gem_shapeChk
 *
 * Purpose:  Traverse the simplices and check their shapes.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_shapeChk(Gem *thee)
{
    int i;
    double f,g;
    double tmp0,tmp1,tmp2,tmp3,tmp4;
    double min0,min1,min2,min3,min4;
    double max0,max1,max2,max3,max4;
    SS *sm;

    /* go through all simplices and setup the initial edge markings */
    min0 = VVLARGE;
    max0 = VVSMALL;
    min1 = VVLARGE;
    max1 = VVSMALL;
    min2 = VVLARGE;
    max2 = VVSMALL;
    min3 = VVLARGE;
    max3 = VVSMALL;
    min4 = VVLARGE;
    max4 = VVSMALL;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        tmp0 = Gem_shapeMeasure( thee, sm, &f, &g );
        tmp1 = Gem_edgeRatio( thee, sm );
        tmp2 = Gem_simplexVolume( thee, sm );
        Gem_shortestEdge(thee, sm, -1, &tmp3);
        Gem_longestEdge(thee, sm, -1, &tmp4);
        if (tmp0 < min0) min0 = tmp0; 
        if (tmp0 > max0) max0 = tmp0; 
        if (tmp1 < min1) min1 = tmp1; 
        if (tmp1 > max1) max1 = tmp1; 
        if (tmp2 < min2) min2 = tmp2; 
        if (tmp2 > max2) max2 = tmp2; 
        if (tmp3 < min3) min3 = tmp3; 
        if (tmp3 > max3) max3 = tmp3; 
        if (tmp4 < min4) min4 = tmp4; 
        if (tmp4 > max4) max4 = tmp4; 
    }
    Vnm_print(0,"Gem_shapeChk: Shape statistics for <%d> simplices:\n",
        Gem_numSS(thee));
    Vnm_print(0,"Gem_shapeChk:    Joe-Liu:    [best,worst]  = [%8.2e,%8.2e]\n",
        max0,min0);
    Vnm_print(0,"Gem_shapeChk:    Edge-Ratio: [best,worst]  = [%8.2e,%8.2e]\n",
        min1,max1);
    Vnm_print(0,"Gem_shapeChk:    Volume:     [small,large] = [%8.2e,%8.2e]\n",
        min2,max2);
    Vnm_print(0,"Gem_shapeChk:    Short Edge: [small,large] = [%8.2e,%8.2e]\n",
        min3,max3);
    Vnm_print(0,"Gem_shapeChk:    Long Edge:  [small,large] = [%8.2e,%8.2e]\n",
        min4,max4);
}

/*
 * ***************************************************************************
 * Routine:  Gem_markEdges
 *
 * Purpose:  Produce the initial edge markings in all of the simplices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_markEdges(Gem *thee)
{
    int i, refEg, ref_0, ref_1, ref_2, ref_3;
    double len, len_0, len_1, len_2, len_3;
    SS *sm;
    VV *v0, *v1, *v2, *v3;

    /* go through all simplices and setup the initial edge markings */
    Vnm_print(0,"Gem_markEdges: marking edges..");

    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);

        if (Gem_dim(thee) == 2) {

            refEg = Gem_longestEdge(thee,sm,-1,&len);
            SS_setRefinementEdge(sm,refEg);

        } else if (Gem_dim(thee) == 3) {

            /* (3D ONLY -- for Arnold/Mukherjee refinment) */
            /* determine longest edge of each face; these are marked edges */

            /* FACE 0 (face opposite vertex 0) */
            v1 = SS_vertex(sm, vmapF[0][0]);
            v2 = SS_vertex(sm, vmapF[0][1]);
            v3 = SS_vertex(sm, vmapF[0][2]);
            ref_0 = Gem_longestEdge(thee,sm,0,&len_0);

            /* FACE 1 (face opposite vertex 1) */
            v2 = SS_vertex(sm, vmapF[1][0]);
            v0 = SS_vertex(sm, vmapF[1][1]);
            v3 = SS_vertex(sm, vmapF[1][2]);
            ref_1 = Gem_longestEdge(thee,sm,1,&len_1);

            /* FACE 2 (face opposite vertex 2) */
            v0 = SS_vertex(sm, vmapF[2][0]);
            v1 = SS_vertex(sm, vmapF[2][1]);
            v3 = SS_vertex(sm, vmapF[2][2]);
            ref_2 = Gem_longestEdge(thee,sm,2,&len_2);

            /* FACE 3 (face opposite vertex 3) */
            v0 = SS_vertex(sm, vmapF[3][0]);
            v2 = SS_vertex(sm, vmapF[3][1]);
            v1 = SS_vertex(sm, vmapF[3][2]);
            ref_3 = Gem_longestEdge(thee,sm,3,&len_3);

            /* now mark edges appropriately */
            refEg = Gem_longestEdge(thee,sm,-1,&len);
            if (refEg == ref_0) {
                SS_setRefinementEdge(sm,ref_0);
                SS_setMarkedEdge1(sm,ref_1);
                SS_setMarkedEdge2(sm,ref_2);
                SS_setMarkedEdge3(sm,ref_3);
            } else if (refEg == ref_1) {
                SS_setRefinementEdge(sm,ref_1);
                SS_setMarkedEdge1(sm,ref_0);
                SS_setMarkedEdge2(sm,ref_2);
                SS_setMarkedEdge3(sm,ref_3);
            } else if (refEg == ref_2) {
                SS_setRefinementEdge(sm,ref_2);
                SS_setMarkedEdge1(sm,ref_0);
                SS_setMarkedEdge2(sm,ref_1);
                SS_setMarkedEdge3(sm,ref_3);
            } else if (refEg == ref_3) {
                SS_setRefinementEdge(sm,ref_3);
                SS_setMarkedEdge1(sm,ref_0);
                SS_setMarkedEdge2(sm,ref_1);
                SS_setMarkedEdge3(sm,ref_2);
            } else {
                VASSERT( 0 );
            }
#if 0
            Vnm_print(2,"Gem_markEdges: RefEg = <%d> <%le>\n",refEg,len);
            Vnm_print(2,"Gem_markEdges: ref_0 = <%d> <%le>\n",ref_0,len_0);
            Vnm_print(2,"Gem_markEdges: ref_1 = <%d> <%le>\n",ref_1,len_1);
            Vnm_print(2,"Gem_markEdges: ref_2 = <%d> <%le>\n",ref_2,len_2);
            Vnm_print(2,"Gem_markEdges: ref_3 = <%d> <%le>\n",ref_3,len_3);
#endif
        }
    }

    Vnm_print(0,"..done.\n");
}

/*
 * ***************************************************************************
 * Routine:  Gem_reorderSV
 *
 * Purpose:  Go through simplices and enforce a vertex ordering that
 *           will produce a positive determinant.
 *
 * Notes:    This relies on an embedding of R2 into R3 (or R3 into R4)
 *           and breaks e.g. if this is a non-orientable 2-manifold, etc.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_reorderSV(Gem *thee)
{
    SS *sm;
    int i;

    /* go through all simplices and reorder vertices if necessary */
    Vnm_print(0,"Gem_simpVertReorder: reordering vertices in each simplex..");

    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        if (Gem_simplexVolume(thee,sm) < 0.) {
            SS_reverse(sm);
        }
        VASSERT( Gem_simplexVolume(thee,sm) > 0.);
    }
    Vnm_print(0,"..done.\n");
}

/*
 * ***************************************************************************
 * Routine:  Gem_smoothMeshLaplace
 *
 * Purpose:  Smooth the mesh using simple Laplace smoothing.
 *
 * Notes:    We don't need the simplex rings here, but we need the edge rings.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_smoothMeshLaplace(Gem *thee)
{
    double v[50][3], w[50], x[3];
    int i, numNabors;
    VV *vx, *vx2;
    EE *eg;

    Gem_createEdges(thee);

    /* go through all vertices (can go forwards now!) and relax hole nodes */
    for (vx=Gem_firstVV(thee); vx!=VNULL; vx=Gem_nextVV(thee)) {

        /* get coordinates of this vertex */
#if 0
        for (i=0; i<Gem_dimII(thee); i++)
            c[i] = VV_coord(vx,i);
#endif

        /* initialize */
        numNabors=0;
        for (i=0; i<50; i++) w[i] = 0.0;

        /* get coordinates of all vertices which share edges */
        for (eg=VV_firstEE(vx); eg!=VNULL; eg=EE_link(eg,vx)) {
            vx2 = EE_otherVertex(eg,vx);
            w[numNabors] = 1.0;
            for (i=0; i<Gem_dimII(thee); i++)
                v[numNabors][i] = VV_coord(vx2,i);
            numNabors++;
            VASSERT( numNabors <= 50 );
        }

        /* if interior node, do a simple smoothing */
        if ( VINTERIOR( VV_type(vx) ) ) {

            /* do a simple averaging of the vertex positions */
#if 0
            Vec3_copy(x, c);
            for (i=0; i<numNabors; i++)
                Vec3_axpy(x, &(v[i][0]), w[i]);
            Vec3_scal(x, (1.0/(numNabors+1)));
#endif
            Vec3_init(x, 0.0);
            for (i=0; i<numNabors; i++)
                Vec3_axpy(x, &(v[i][0]), w[i]);
            Vec3_scal( x, (1.0/numNabors) );

            /* set the new vertex positions */
            for (i=0; i<Gem_dimII(thee); i++)
                VV_setCoord(vx, i, x[i]);

        } else {

        } /* end if this is a vertex we need to smooth */
    } /* end loop over vertices */

    Gem_destroyEdges(thee);
}

/*
 * ***************************************************************************
 * Routine:  Gem_smoothMesh
 *
 * Purpose:  Smooth the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
#define VRINGMAX 1000
VPUBLIC void Gem_smoothMesh(Gem *thee)
{
    int i, j, k, numSring, maxSring, maxVring, maxVBring, numVring, numVBring;
    int found;
    double c[3], p[3], bc[3], mass, totalMass;
    VV *vx, *vxt, *vring[VRINGMAX];
    /* VV *vbring[VRINGMAX]; */
    SS *sm, *sring[VRINGMAX];

    /* go through all vertices and adjust them to improve the mesh */
    maxSring  = 0;
    maxVring  = 0;
    maxVBring = 0;
    for (vx=Gem_firstVV(thee); vx!=VNULL; vx=Gem_nextVV(thee)) {

        /* get coordinates of this vertex */
        for (i=0; i<Gem_dimII(thee); i++)
            c[i] = VV_coord(vx,i);

        /* get the ring of simplices around this vertex */
        numSring=0;
        sring[numSring] = VV_firstSS(vx);
        while (sring[numSring] != VNULL) {
            numSring++;
            sring[numSring] = SS_link(sring[numSring-1],vx);
        }
        VASSERT( numSring > 0 );
        VASSERT( numSring <= VRINGMAX );
        if (numSring > maxSring) maxSring = numSring;

        /* get the ring of vertices around this vertex */
        numVring=0;
        numVBring=0;
        vring[numVring] = VNULL;
        /* vbring[numVBring] = VNULL; */
        for (i=0; i<numSring; i++) {
            sm = sring[i];
            for (j=0; j<Gem_dimVV(thee); j++) {
                vxt = SS_vertex(sm,j);
                found = 0;
                for (k=0; k<numVring; k++)
                    if ((vxt == vring[k]) || (vxt == vx))
                        found = 1;
                if (!found) {
                    vring[numVring] = vxt;
                    numVring++;
                    if ( VBOUNDARY( VV_type(vxt) ) 
                       && ( VV_type(vxt) == VV_type(vx) ) ) {
                        /* vbring[numVBring] = vxt; */
                        numVBring++;
                    }
                }
            }
        }
        VASSERT( numVring > 0 );
        VASSERT( numVring <= VRINGMAX );
        VASSERT( numVBring <= VRINGMAX );
        if (numVring  > maxVring)  maxVring  = numVring;
        if (numVBring > maxVBring) maxVBring = numVBring;

        /* if interior node, do a simple smoothing */
        if ( VINTERIOR( VV_type(vx) ) ) {

            /* find centroid of entire vertex cloud */
            for (j=0; j<Gem_dimII(thee); j++) {
                bc[j] = 0.;
                totalMass = 0.;
                for (i=0; i<numVring; i++) {
                    if ( VBOUNDARY( VV_type(vring[i]) ) 
                       && (VV_type(vring[i]) > 1) ) {
                        mass = 0.66;
                    } else {
                        mass = 1.0;
                    }
                    bc[j] += mass * VV_coord(vring[i],j);
                    totalMass += mass;
                }
                /* bc[j] /= totalMass; */
                p[j] = ( totalMass * c[j] + bc[j] ) / ( 2.0 * totalMass );
                VV_setCoord( vx, j, p[j] );
            }

        } /* end if this is a vertex we need to smooth */

    } /* end loop over vertices */

    Vnm_print(0, "Gem_smoothMesh: maxSring  = <%d>\n", maxSring);
    Vnm_print(0, "Gem_smoothMesh: maxVring  = <%d>\n", maxVring);
    Vnm_print(0, "Gem_smoothMesh: maxVBring = <%d>\n", maxVBring);
}

/*
 * ***************************************************************************
 * Routine:  Gem_smoothMeshBnd
 *
 * Purpose:  Smooth the boundary mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_smoothMeshBnd(Gem *thee)
{
    int i, j, k, numSring, maxSring, maxVring, maxVBring, numVring, numVBring;
    int found;
    double c[3], p[3], bc[3], mass, totalMass;
    VV *vx, *vxt, *vring[VRINGMAX];
    /* VV *vbring[VRINGMAX]; */
    SS *sm, *sring[VRINGMAX];

    /* go through all vertices and adjust them to improve the mesh */
    maxSring  = 0;
    maxVring  = 0;
    maxVBring = 0;
    for (vx=Gem_firstVV(thee); vx!=VNULL; vx=Gem_nextVV(thee)) {

        /* get coordinates of this vertex */
        for (i=0; i<Gem_dimII(thee); i++)
            c[i] = VV_coord(vx,i);

        /* get the ring of simplices around this vertex */
        numSring=0;
        sring[numSring] = VV_firstSS(vx);
        while (sring[numSring] != VNULL) {
            numSring++;
            sring[numSring] = SS_link(sring[numSring-1],vx);
        }
        VASSERT( numSring > 0 );
        VASSERT( numSring <= VRINGMAX );
        if (numSring > maxSring) maxSring = numSring;

        /* get the ring of vertices around this vertex */
        numVring=0;
        numVBring=0;
        vring[numVring] = VNULL;
        /* vbring[numVBring] = VNULL; */
        for (i=0; i<numSring; i++) {
            sm = sring[i];
            for (j=0; j<Gem_dimVV(thee); j++) {
                vxt = SS_vertex(sm,j);
                found = 0;
                for (k=0; k<numVring; k++)
                    if ((vxt == vring[k]) || (vxt == vx))
                        found = 1;
                if (!found) {
                    vring[numVring] = vxt;
                    numVring++;
                    if ( VBOUNDARY( VV_type(vxt) ) 
                       && ( VV_type(vxt) == VV_type(vx) ) ) {
                        /* vbring[numVBring] = vxt; */
                        numVBring++;
                    }
                }
            }
        }
        VASSERT( numVring > 0 );
        VASSERT( numVring <= VRINGMAX );
        VASSERT( numVBring <= VRINGMAX );
        if (numVring  > maxVring)  maxVring  = numVring;
        if (numVBring > maxVBring) maxVBring = numVBring;

        /* if boundary node, do a simple smoothing */
        if ( VBOUNDARY( VV_type(vx) ) ) {

            /* find centroid of entire vertex cloud */
            for (j=0; j<Gem_dimII(thee); j++) {
                bc[j] = 0.;
                totalMass = 0.;
                for (i=0; i<numVring; i++) {
                    if ( VBOUNDARY( VV_type(vring[i]) ) ) {
                        mass = 1.0;
                    } else {
                        mass = 0.66;
                    }
                    bc[j] += mass * VV_coord(vring[i],j);
                    totalMass += mass;
                }
                /* bc[j] /= totalMass; */
                p[j] = ( totalMass * c[j] + bc[j] ) / ( 2.0 * totalMass );
            }
            thee->pde->mapBoundary( Gem_dim(thee), Gem_dimII(thee),
                VV_type(vx), VV_chart(vx), p );
            for (j=0; j<Gem_dimII(thee); j++)
                VV_setCoord( vx, j, p[j] );

        } /* end if this is a vertex we need to smooth */

    } /* end loop over vertices */

    Vnm_print(0, "Gem_smoothMeshBnd: maxSring  = <%d>\n", maxSring);
    Vnm_print(0, "Gem_smoothMeshBnd: maxVring  = <%d>\n", maxVring);
    Vnm_print(0, "Gem_smoothMeshBnd: maxVBring = <%d>\n", maxVBring);
}

/*
 * ***************************************************************************
 * Routine:  Gem_shapeMeasure
 *
 * Purpose:  Calculate the shape quality measure for this simplex.
 *
 * Notes:    Let |s| denote the volume (which may be negative) of a given
 *           d-simplex "s", let v_i (i=0,...,d) denote the vertices of s,
 *           and let e_{ij} denote the d-vectors representing the 3 or 6 edges
 *           of s that connect v_i to v_j.  We compute the following shape
 *           quality measure for the simplex s:
 *
 *                           f(s,d)   2^{2(1-1/d)} * 3^{(d-1)/2} * |s|^{2/d}
 *               meas(s,d) = ------ = --------------------------------------
 *                           g(s,d)       \sum_{0<=i<j<=d} |e_{ij}|^2
 *
 * 2D Notes: The shape function meas(s,2) is (nearly) the same one used by
 *           Randy Bank and Kent Smith in their joint paper on mesh smoothing:
 *
 *                           f(s,2)         2 * 3^{1/2} * |s|
 *               meas(s,2) = ------ = ---------------------------
 *                           g(s,2)   \sum_{0<=i<j<=2} |e_{ij}|^2
 *
 *           It has the property that its maximal value of 1 is obtained
 *           for an equilateral triangle, and it is scaling invariant, i.e.,
 *           we don't have to worry about the size of the triangle.
 *           Their original function was normalized (their numerator was
 *           2*f(s,2) above) to yield a value of 1 for a equalateral triangle
 *           (with volume 1); this is modified to yield a maximal value
 *           of 1 for the unit triangle (with volume 1/2) to work better with
 *           the unit triangle code.  To effect this slightly different
 *           normalization, the numerator of the quality function was changed
 *           to 2(3)^{1/2}|s|.
 *
 * 3D Notes: The shape function meas(s,3) is (nearly) the same one used by
 *           Joe and Liu in their paper on quality measures for tetrahedra:
 *
 *                           f(s,3)     2^{4/3} * 3 * |s|^{2/3}
 *               meas(s,3) = ------ = ---------------------------
 *                           g(s,3)   \sum_{0<=i<j<=3} |e_{ij}|^2
 *
 *           It is also scaling invariant, so we don't have to worry about
 *           the size of the tetrahedron.  Their original function was 
 *           normalized (their numerator was 12(3|s|)^{2/3}) to yield a
 *           maximal value of 1 for a regular tetrahedron (with volume 1);
 *           this was modified to yield a maximal value of 1 for the unit
 *           tetrahedron (with volume 1/6) to work better with the unit
 *           tetrahedron code.  To effect this slightly different
 *           normalization, the numerator of the quality function was changed
 *           to f(s,3) = 12(3|s|/6)^{2/3} = 2^{4/3}*3*|s|^{2/3}, as above.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Gem_shapeMeasure(Gem *thee, SS *sm, double *f, double *g)
{
    int i;
    double d, vol, siggn, value;
    TT t;

    /* get simplex volume and its sign */
    Gem_simplexInfo(thee, sm, &t);
    siggn = VSIGN( 1., t.D );
    vol   = VABS( t.D );

    /* compute volume scaling */
    d = (double)Gem_dim(thee);
    (*f) = siggn * VPOW( 2., 2.*(1.-1./d) )
                 * VPOW( 3., (d-1.)*.5 )
                 * VPOW( vol, 2./d );

    /* accumlate (squared) edge lengths */
    (*g) = 0.;
    for (i=0; i<Gem_dimEE(thee); i++)
        (*g) += t.elen[i];

    if ((*g) > 0.) {
        value = ((*f) / (*g));
    } else {
        value = 0.;
    }

    return value;
}

/*
 * ***************************************************************************
 * Routine:  Gem_shapeMeasureGrad
 *
 * Purpose:  Calculate gradient of the shape quality measure for this simplex,
 *           where the last vertex (vertex d) is treated as the set of
 *           independent variables.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_shapeMeasureGrad(Gem *thee, SS *sm, int vmap[], double dm[])
{
    int i, d;
    double f, g, vol, siggn, fac, df[3], dg[3], x[4], y[4], z[4];
    TT t;

    d = Gem_dim(thee);
    (void)Gem_shapeMeasure(thee, sm, &f, &g);

    if (d==2) {
        for (i=0; i<d+1; i++) {
            x[i] = VV_coord( SS_vertex( sm, vmap[i] ), 0 );
            y[i] = VV_coord( SS_vertex( sm, vmap[i] ), 1 );
        }
        fac   = 2. * VSQRT(3.);
        df[0] = fac * ( y[0] - y[1] );
        df[1] = fac * ( x[1] - x[0] );
        df[2] = 0.;
        dg[0] = 2. * (x[2] - x[0]) + 2. * (x[2] - x[1]);
        dg[1] = 2. * (y[2] - y[0]) + 2. * (y[2] - y[1]);
        dg[2] = 0.;
    } else if (d==3) {
        for (i=0; i<d+1; i++) {
            x[i] = VV_coord( SS_vertex( sm, vmap[i] ), 0 );
            y[i] = VV_coord( SS_vertex( sm, vmap[i] ), 1 );
            z[i] = VV_coord( SS_vertex( sm, vmap[i] ), 2 );
        }
        Gem_simplexInfo(thee, sm, &t);
        siggn = VSIGN( 1., t.D );
        vol   = VABS( t.D );
        fac   = siggn * 2. * VPOW(2.,4./3.) * VPOW(vol,-5./3.);
        df[0] = fac * ( (y[1]-y[0])*(z[2]-z[0]) - (y[2]-y[0])*(z[1]-z[0]) );
        df[1] = fac * ( (x[2]-x[0])*(z[1]-z[0]) - (x[1]-x[0])*(z[2]-z[0]) );
        df[2] = fac * ( (x[1]-x[0])*(y[2]-y[0]) - (x[2]-x[0])*(y[1]-y[0]) );
        dg[0] = 2. * (x[3] - x[0]) + 2. * (x[3] - x[1]) + 2. * (x[3] - x[2]);
        dg[1] = 2. * (y[3] - y[0]) + 2. * (y[3] - y[1]) + 2. * (y[3] - y[2]);
        dg[2] = 2. * (z[3] - z[0]) + 2. * (z[3] - z[1]) + 2. * (z[3] - z[2]);
    } else { VASSERT(0); }

    fac = 1. / (g*g);
    for (i=0; i<3; i++)
        dm[i] = fac * ( g*df[i] - f*dg[i] );
}

/*
 * ***************************************************************************
 * Routine:  Gem_smoothMeshOpt
 *
 * Purpose:  Smooth the mesh using a volume optimization approach.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_smoothMeshOpt(Gem *thee)
{
    int i, j, k, done, imap, numSring, minIdx, maxSring, maxVring;
    int iters, itmax, numVring, numVBring, maxVBring, found, map[4];
    double step, f, g, minShape, longEdgeLen;
    double dm[3], a[3], b[3], c[3], shape[VRINGMAX];
    VV *vx, *vxt, *vring[VRINGMAX];
    /* VV *vbring[VRINGMAX]; */
    SS *sm, *sring[VRINGMAX];

    /* go through all vertices and adjust them to improve the mesh */
    maxSring  = 0;
    maxVring  = 0;
    maxVBring = 0;
    for (vx=Gem_firstVV(thee); vx!=VNULL; vx=Gem_nextVV(thee)) {

        /* get coordinates of this vertex */
        for (i=0; i<Gem_dimII(thee); i++)
            c[i] = VV_coord(vx,i);

        /* get the ring of simplices around this vertex */
        numSring=0;
        sring[numSring] = VV_firstSS(vx);
        while (sring[numSring] != VNULL) {
            numSring++;
            sring[numSring] = SS_link(sring[numSring-1],vx);
        }
        VASSERT( numSring > 0 );
        VASSERT( numSring <= VRINGMAX );
        if (numSring > maxSring) maxSring = numSring;

        /* get the ring of vertices around this vertex */
        numVring=0;
        numVBring=0;
        vring[numVring] = VNULL;
        /* vbring[numVBring] = VNULL; */
        for (i=0; i<numSring; i++) {
            sm = sring[i];
            for (j=0; j<Gem_dimVV(thee); j++) {
                vxt = SS_vertex(sm,j);
                found = 0;
                for (k=0; k<numVring; k++)
                    if ((vxt == vring[k]) || (vxt == vx))
                        found = 1;
                if (!found) {
                    vring[numVring] = vxt;
                    numVring++;
                    if ( VBOUNDARY( VV_type(vxt) ) 
                       && ( VV_type(vxt) == VV_type(vx) ) ) {
                        /* vbring[numVBring] = vxt; */
                        numVBring++;
                    }
                }
            }
        }
        VASSERT( numVring > 0 );
        VASSERT( numVring <= VRINGMAX );
        VASSERT( numVBring <= VRINGMAX );
        if (numVring  > maxVring)  maxVring  = numVring;
        if (numVBring > maxVBring) maxVBring = numVBring;

        /* calculate shape measures; collect vertices */
        minShape = 1.1;
        minIdx = -1;
        for (i=0; i<numSring; i++) {
            shape[i] = Gem_shapeMeasure(thee, sring[i], &f, &g);
            if (shape[i] < minShape) {
                minShape = shape[i];
                minIdx = i;
            }
        }
        VASSERT( minShape <= 1.0 );
        VASSERT( minIdx   >= 0.0 );

        /* collect info about the worst simplex */
        imap = -1;
        sm = sring[minIdx];
        for (i=0; i<Gem_dimVV(thee); i++) {
            vxt = SS_vertex(sm,i);
            if (vxt == vx) imap = i;
        }
        VASSERT( imap >= 0 );

        /* make last vertex the movable one for simplicity */
        for (i=0; i<Gem_dimVV(thee); i++)
            map[i] = (imap+i+1) % Gem_dimVV(thee);

        /* if interior node, do a simple smoothing */
        if ( VINTERIOR( VV_type(vx) ) ) {

            /* get the current measure and gradient */
            Gem_shapeMeasureGrad(thee, sm, map, dm);

            /* set the initial end-points of the bisection interval */
            (void)Gem_longestEdge(thee, sm, -1, &longEdgeLen);
            step = longEdgeLen;
            for (j=0; j<Gem_dimII(thee); j++) {
                a[j] = c[j];
                b[j] = a[j] + step * dm[j];
                VV_setCoord( vx, j, b[j] );
            }

            /* bisect along gradient to find optimal shape for simplex */
            /* (find point the improves worst shape in the entire ring) */
            itmax = 8;
            iters = 0;
            done = 0;
            while (!done) {
                VJMPERR1( !Vnm_sigInt() );
                iters++;
                done = 1;
                for (j=0; j<numSring; j++) {
                    shape[j] = Gem_shapeMeasure(thee, sring[j], &f, &g);
                    if (shape[j] <= minShape) done = 0;
                }
                if (iters > itmax) {
                    done = 1;
                    for (j=0; j<Gem_dimII(thee); j++)
                        VV_setCoord( vx, j, c[j] );
                } else {
                    step *= 0.5;
                    for (j=0; j<Gem_dimII(thee); j++) {
                        b[j] = a[j] + step * dm[j];
                        VV_setCoord( vx, j, b[j] );
                    }
                }
            }

        } else {

        } /* end if this is a vertex we need to smooth */

    } /* end loop over vertices */

  VERROR1:
    Vnm_print(0, "Gem_smoothMeshOpt: maxSring  = <%d>\n", maxSring);
    Vnm_print(0, "Gem_smoothMeshOpt: maxVring  = <%d>\n", maxVring);
    Vnm_print(0, "Gem_smoothMeshOpt: maxVBring = <%d>\n", maxVBring);
}

/*
 * ***************************************************************************
 * Routine:  Gem_buildCharts
 *
 * Purpose:  Unify the charts of vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_buildCharts(Gem *thee)
{
    int j, chartV;
    VV *vx;
    double v[4][3];

    for (vx=Gem_firstVV(thee); vx!=VNULL; vx=Gem_nextVV(thee)) {
        chartV = VV_chart(vx);
        for (j=0; j<Gem_dimII(thee); j++)
            v[0][j] = VV_coord(vx,j);
        thee->pde->oneChart(Gem_dim(thee), Gem_dimII(thee), 1, &chartV, v, 1);
        VV_setChart(vx, chartV);
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_clearCharts
 *
 * Purpose:  Unify the charts of vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_clearCharts(Gem *thee)
{
    VV *vx;

    for (vx=Gem_firstVV(thee); vx!=VNULL; vx=Gem_nextVV(thee)) {
        VV_setChart(vx, 0);
    }
}

