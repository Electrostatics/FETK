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
 * rcsid="$Id: gemgen.c,v 1.18 2010/08/12 05:18:56 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     Gemgen.c
 *
 * Purpose:  Class Gem: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "gem_p.h"

VEMBED(rcsid="$Id: gemgen.c,v 1.18 2010/08/12 05:18:56 fetk Exp $")

VPRIVATE int predInit = 0;

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
 * Routine:  Gem_pointInSimplex
 *
 * Purpose:  Determine whether or a not a point is in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_pointInSimplex(Gem *thee, SS *sm, double x[])
{
    int i, j;
    double a[3], b[3], c[3], d[3], bc[3], len, z;

    /* first do a quick check */
    for (j=0; j<3; j++) {
        bc[j] = 0.;
    }
    for (i=0; i<SS_dimVV(sm); i++) {
        for (j=0; j<3; j++) {
            bc[j] += VV_coord(SS_vertex(sm,i),j);
        }
    }
    for (j=0; j<3; j++) {
        bc[j] /= SS_dimVV(sm);
    }
    (void)Gem_longestEdge(thee, sm, -1, &len);
    z = len + VSMALL;
    if ( (VABS(x[0]-bc[0])>z)||(VABS(x[1]-bc[1])>z)||(VABS(x[2]-bc[2])>z) ) {
        return 0;
    }

    /* OK, that didn't work; now do a more careful check */
    Gem_predinit(thee);
 
    if (Gem_dim(thee)==2) {
        for (j=0; j<2; j++) {
            a[j] = VV_coord(SS_vertex(sm,0),j);
            b[j] = VV_coord(SS_vertex(sm,1),j);
            c[j] = VV_coord(SS_vertex(sm,2),j);
        }
        if (  (Vpred_orient2d(a,b,x) >= -VSMALL)
           && (Vpred_orient2d(b,c,x) >= -VSMALL)
           && (Vpred_orient2d(c,a,x) >= -VSMALL) ) {
            return  1;
        } else {
            return  0;
        }
    } else if (Gem_dim(thee)==3) {
        for (j=0; j<3; j++) {
            a[j] = VV_coord(SS_vertex(sm,1),j);
            b[j] = VV_coord(SS_vertex(sm,0),j);
            c[j] = VV_coord(SS_vertex(sm,2),j);
            d[j] = VV_coord(SS_vertex(sm,3),j);
        }
        if (  (Vpred_orient3d(a,b,c,x) >= -VSMALL)
           && (Vpred_orient3d(a,c,d,x) >= -VSMALL)
           && (Vpred_orient3d(a,d,b,x) >= -VSMALL)
           && (Vpred_orient3d(b,d,c,x) >= -VSMALL) ) {
            return  1;
        } else {
            return  0;
        }
    } else {
        VASSERT(0);
        return 0;
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_pointInSimplexVal
 *
 * Purpose:  Evaluate basis functions at a point in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_pointInSimplexVal(Gem *thee, SS *sm, double x[],
    double phi[], double phix[][3])
{
    int i, j, found;
    double xm[3];
    TT t;

    /* Affine transformation from master element to this element */
    Gem_buildVolumeTrans(thee,sm,&t);

    /* Map current point to master element */
    for (i=0; i<Gem_dimII(thee); i++) {
        xm[i] = t.cc[i];
        for (j=0; j<Gem_dimII(thee); j++)
            xm[i] += t.gg[i][j]*x[j];
    }

    /* Evaluate master element basis functions at the point */
    phi[0] = 1. - xm[0] - xm[1] - xm[2];
    phi[1] = xm[0];
    phi[2] = xm[1];
    phi[3] = xm[2];

    /* Evaluate master element basis functions gradients at the point */
    phix[0][0] = -1.;
    phix[0][1] = -1.;
    phix[0][2] = -1.;
    phix[1][0] =  1.;
    phix[1][1] =  0.;
    phix[1][2] =  0.;
    phix[2][0] =  0.;
    phix[2][1] =  1.;
    phix[2][2] =  0.;
    phix[3][0] =  0.;
    phix[3][1] =  0.;
    phix[3][2] =  1.;

    /* Check if point lies in master element */
    found = 1;
    for (j=0; j<Gem_dimVV(thee); j++) {
        if ( phi[j] <= -VVSMALL ) found = 0;
    }

    /* return */
    return found;
}

/*
 * ***************************************************************************
 * Routine:  Gem_findSimplex
 *
 * Purpose:  Find a simplex containing a given vertex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC SS* Gem_findSimplex(Gem *thee, VV *vx)
{
    int i, j;
    double x[3];
    SS *sm;

    /* grab coordinates of the point */
    for (j=0; j<Gem_dimII(thee); j++)
        x[j] = VV_coord( vx, j );

    /* find the simplex in which this vertex lies */
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        if ( Gem_pointInSimplex(thee, sm, x) )
            return sm;
    }
    return VNULL;
}

/*
 * ***************************************************************************
 * Routine:  Gem_predinit
 *
 * Purpose:  Initialize the geometric predicates.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_predinit(Gem *thee)
{
    if ( !predInit ) {
        predInit = 1;
        Vpred_exactinit();
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_orient
 *
 * Purpose:  Determine the orientation of the vertices in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_orient(Gem *thee, SS *sm)
{
    int j;
    double a[3], b[3], c[3], d[3];

    Gem_predinit(thee);
 
    if (Gem_dim(thee)==2) {
        for (j=0; j<2; j++) {
            a[j] = VV_coord(SS_vertex(sm,0),j);
            b[j] = VV_coord(SS_vertex(sm,1),j);
            c[j] = VV_coord(SS_vertex(sm,2),j);
        }
        if ( Vpred_orient2d(a,b,c) >= VVSMALL ) {
            return  1;
        } else if ( Vpred_orient2d(a,b,c) <= -VVSMALL ) {
            return -1;
        } else {
            return  0;
        }
    } else if (Gem_dim(thee)==3) {
        for (j=0; j<3; j++) {
            a[j] = VV_coord(SS_vertex(sm,1),j);
            b[j] = VV_coord(SS_vertex(sm,0),j);
            c[j] = VV_coord(SS_vertex(sm,2),j);
            d[j] = VV_coord(SS_vertex(sm,3),j);
        }
        if ( Vpred_orient3d(a,b,c,d) >= VVSMALL ) {
            return  1;
        } else if ( Vpred_orient3d(a,b,c,d) <= -VVSMALL ) {
            return -1;
        } else {
            return  0;
        }
    } else {
        VASSERT(0);
        return 0;
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_orientVal
 *
 * Purpose:  Determine the orientation value of the vertices in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Gem_orientVal(Gem *thee, SS *sm)
{
    int j;
    double a[3], b[3], c[3], d[3];

    Gem_predinit(thee);
 
    if (Gem_dim(thee)==2) {
        for (j=0; j<2; j++) {
            a[j] = VV_coord(SS_vertex(sm,0),j);
            b[j] = VV_coord(SS_vertex(sm,1),j);
            c[j] = VV_coord(SS_vertex(sm,2),j);
        }
        return Vpred_orient2d(a,b,c);
    } else if (Gem_dim(thee)==3) {
        for (j=0; j<3; j++) {
            a[j] = VV_coord(SS_vertex(sm,1),j);
            b[j] = VV_coord(SS_vertex(sm,0),j);
            c[j] = VV_coord(SS_vertex(sm,2),j);
            d[j] = VV_coord(SS_vertex(sm,3),j);
        }
        return Vpred_orient3d(a,b,c,d);
    } else {
        VASSERT(0);
        return 0;
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_inSphere
 *
 * Purpose:  Determine if a vertex lies in a sphere of other vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_inSphere(Gem *thee, SS *sm, int sm_facet, VV *vx, VV *vxnb)
{
    int j;
    double a[3], b[3], c[3], d[3], e[3];

    Gem_predinit(thee);
 
    if (Gem_dim(thee)==2) {
        for (j=0; j<2; j++) {
            a[j] = VV_coord(vx,j);
            b[j] = VV_coord(SS_vertex(sm,SS_faceVertexNumber(sm,sm_facet,0)),j);
            c[j] = VV_coord(SS_vertex(sm,SS_faceVertexNumber(sm,sm_facet,1)),j);
            d[j] = VV_coord(vxnb,j);
        }
        if ( Vpred_incircle(a, b, c, d) >= VSMALL ) {
            return  1;
        } else if ( Vpred_incircle(a, b, c, d) <= -VSMALL ) {
            return -1;
        } else {
            return  0;
        }
    } else if (Gem_dim(thee)==3) {
        for (j=0; j<3; j++) {
            a[j] = VV_coord(vx,j);
            b[j] = VV_coord(SS_vertex(sm,SS_faceVertexNumber(sm,sm_facet,1)),j);
            c[j] = VV_coord(SS_vertex(sm,SS_faceVertexNumber(sm,sm_facet,0)),j);
            d[j] = VV_coord(SS_vertex(sm,SS_faceVertexNumber(sm,sm_facet,2)),j);
            e[j] = VV_coord(vxnb,j);
        }
        if ( Vpred_insphere(a, b, c, d, e) >= VSMALL ) {
            return  1;
        } else if ( Vpred_insphere(a, b, c, d, e) <= -VSMALL ) {
            return -1;
        } else {
            return  0;
        }
    } else {
        VASSERT(0);
        return 0;
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_delaunay
 *
 * Purpose:  Incremental flip Delaunay generator.
 *
 * Notes:    We use an incremental flip Delaunay mesh generator.
 *           In 2D, this is based on the standard edge-flipping.
 *           In 3D, this is based on 2-to-3 flips (shared face-to-edge flip),
 *           and 3-to-2 flips (a restricted edge-to-face flip).
 *
 *           The 2D version of the algorithm here is similar to several
 *           edge-flip-based Delaunay algorithms in the literature.
 *
 *           The 3D version of the algorithm here is similar to Barry Joe's
 *           and Ernst Mucke's.  However, the ringed-vertex datastructure used
 *           here leads to a more concise implementation, as compared to
 *           implementations using e.g. Mucke's edge-facet datastructure.
 *          
 *           Both this algorithm and similar incremental flip algorithms in
 *           the 3D case are based on several recent theoretical results
 *           due to Barry Joe, which guarantee the following:
 *
 *               (1) The flipping algorithm to re-establish Delaunay-ness
 *                   always terminates in a finite number of steps.
 *
 *               (2) The algorithm works regardless of the flipping order.
 *
 *               (3) Only the exterior faces of the star region of the new
 *                   vertex (what Mucke calls "link facets", because these
 *                   "facets" link two triangles or tets together), and in the
 *                   3D case the three edges which make up those faces, need
 *                   be tested and then possibly flipped.
 *
 *           The algorithm is as follows:
 *
 *               (1) Given N inputs points, a single enclosing simplex is
 *                   formed by adding d+1 additional points, and then forming
 *                   that single simplex.
 *
 *               (2) The N points are then added to the mesh one at a time
 *                   by locating the simplex containing each point, adding
 *                   the point, and splitting the containing simplex into
 *                   d+1 children (note that unless the points are in
 *                   "general" position, this may give rise to degenerate
 *                   simplices).
 *
 *               (3) The link-facets of the newly added vertex are checked
 *                   for Delaunayness.  The link-facets are the faces 
 *                   opposite the new vertex in each simplex that uses
 *                   the new vertex.  (This is the boundary of the support
 *                   region for a finite element basis function, for example.)
 *                   If a non-Delaunay face is located, we attempt to flip
 *                   one of the three edges of the face using a 3-to-2
 *                   (edge-to-face) flip.  We only flip such as edge if the
 *                   simplex ring about the edge has length three.  If no
 *                   such edge flips are possible, we do a 2-to-3 flip
 *                   (face-to-edge) if this is possible (it is only possible
 *                   if the two tets sharing the face form a convex region).
 *                   If no flipping is possible, we temporarily ignore this
 *                   non-Delaunay face and move on to the next face.
 *
 *               (4) Step (3) above terminates in a finite number of steps
 *                   thanks to the theoretical results of Barry Joe.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
#define VXNUM 20
VPUBLIC void Gem_delaunay(Gem *thee)
{
    int i, j, theDim, vxid, reality, class, type, color;
    double max, *defX[3] = { VNULL, VNULL, VNULL };
    VV *vx, *v[4], *vb[4];
    SS *sm, *lastS, *fsm[4];
    Vio *sock;

    /* dimension */
    theDim = Gem_dim(thee);
    Vnm_print(2,"Gem_delaunay: dimension=<%d>\n", theDim);

    /* reset the boundary vertex/face counters */
    thee->numBV = 0;
    thee->numBF = 0;

    /* reset boundary information and first simplex ptrs, also get bbox */
    max = -VLARGE;
    for (vxid=0; vxid<Gem_numVV(thee); vxid++) {
        vx = Gem_VV(thee,vxid);
        /* VV_setType(vx, 0); */
        VV_setFirstSS(vx, VNULL);
        for (j=0; j<Gem_dimII(thee); j++)
            if (VABS(VV_coord(vx,j)) > max) max = VABS(VV_coord(vx,j));
    }
  
    /* make bbox-vertices and then the bbox-simplex from the bounding box */
    for (i=0; i<Gem_dimVV(thee); i++) {

        /* create the new vertex */
        vx = Gem_createAndInitVV(thee);
        vb[i] = vx;
        VV_setType(vx, 1);

        /* set the vertex coordinates */
        if (Gem_dim(thee) == 2) {
            if (i==0) {
                VV_setCoord(vx, 0, -10.0*max);
                VV_setCoord(vx, 1, -10.0*max);
                VV_setCoord(vx, 2,   0.0*max);
            } else if (i==1) {
                VV_setCoord(vx, 0,  10.0*max);
                VV_setCoord(vx, 1, -10.0*max);
                VV_setCoord(vx, 2,   0.0*max);
            } else if (i==2) {
                VV_setCoord(vx, 0,   0.0*max);
                VV_setCoord(vx, 1,  10.0*max);
                VV_setCoord(vx, 2,   0.0*max);
            } else { VASSERT(0); }
        } else if (Gem_dim(thee) == 3) {
            if (i==0) {
                VV_setCoord(vx, 0,  20.0*max);
                VV_setCoord(vx, 1,   0.0*max);
                VV_setCoord(vx, 2,   0.0*max);
            } else if (i==1) {
                VV_setCoord(vx, 0,   0.0*max);
                VV_setCoord(vx, 1,  20.0*max);
                VV_setCoord(vx, 2,   0.0*max);
            } else if (i==2) {
                VV_setCoord(vx, 0,   0.0*max);
                VV_setCoord(vx, 1,   0.0*max);
                VV_setCoord(vx, 2,  20.0*max);
            } else if (i==3) {
                VV_setCoord(vx, 0, -20.0*max);
                VV_setCoord(vx, 1, -20.0*max);
                VV_setCoord(vx, 2, -20.0*max);
            } else { VASSERT(0); }
        } else { VASSERT(0); }
    }

    /* delete any existing simplices */
    if ( thee->simplices != VNULL ) Vset_dtor( &(thee->simplices) );
    thee->simplices = Vset_ctor( VNULL, "SS",  sizeof( SS ), VMAX_OBJECTS, 0 );

    /* make the bbox simplex */
    sm = Gem_createAndInitSS(thee);
    SS_setDim(sm, theDim);
    SS_setClass(sm, theDim);
    /* set the simplex face types and vertex labels */
    for (j=0; j<Gem_dimVV(thee); j++) {
        SS_setFaceType( sm, j, 0 );
        SS_setVertex( sm, j, vb[j] );
    }
    /* build the ringed vertex datastructure */
    SS_buildRing(sm);

    /* make sure we have the right orientation on initial guy */
    if ( Gem_orient(thee,sm) < 0 ) SS_reverse(sm);
    VASSERT( Gem_orient(thee,sm) > 0 );

    /* make a picture */
    sock = Vio_socketOpen("w","INET", "ASC", "localhost", "1");
    Gem_writeGV(thee,sock,0,0,0,1.0,0,defX);
    Vio_socketClose(&sock);
#if 0
    Vnm_print(2,"HIT RETURN TO CONTINUE...");
    c=getchar();
#endif

    /* insert verts (except last dimVV guys in bbox) one at a time into mesh */
    for (vxid=0; vxid<Gem_numVV(thee)-Gem_dimVV(thee); vxid++) {
        vx = Gem_VV(thee,vxid);
        if (vxid < VXNUM) {
            Vnm_print(2,"Gem_delaunay: inserting V<%d>\n", VV_id(vx) );
        }

        /* find encasing simplex, remove it, replace with d+1 children */
        if ( (sm=Gem_findSimplex(thee,vx)) != VNULL ) {

            /* initialize and get simplices' vertices and its face types */
            for (i=0; i<4; i++)
                fsm[i] = VNULL;
            for (i=0; i<4; i++) {
                v[i] = VNULL;
            }
            for (i=0; i<Gem_dimVV(thee); i++)
                v[i] = SS_vertex( sm, i );

            /* get various attibutes of parent that children should inherit */
            reality = SS_reality(sm);  /* we must force inheritance here */
            class   = SS_class(sm);    /* we must force inheritance here */
            type    = SS_type(sm);     /* we must force inheritance here */
            color   = SS_chart(sm);    /* we must force inheritance here */

            /* remove sm from simplex rings, reinit for reuse as first child */
            SS_meltRing(sm);
            SS_reinit(sm);

            /* first simplex -- new vx plays the role of the old v0 */
            fsm[0] = sm; /* first child re-uses the parent simplex */
            SS_setReality(fsm[0], reality);
            SS_setClass(fsm[0], class);
            SS_setType(fsm[0], type);
            SS_setChart(fsm[0], color);
            SS_setVertex(fsm[0], 0, vx);
            SS_setVertex(fsm[0], 1, v[0]);
            SS_setVertex(fsm[0], 2, v[1]);
            SS_setFaceType(fsm[0], 0, 0);
            SS_setFaceType(fsm[0], 1, 0);
            SS_setFaceType(fsm[0], 2, 0);
            if (Gem_dim(thee)==3) {
                SS_setVertex(fsm[0], 3, v[3]);
                SS_setFaceType(fsm[0], 3, 0);
            } else {
                SS_setVertex(fsm[0], 3, VNULL);
                SS_setFaceType(fsm[0], 3, 0);
            }
            SS_buildRing(fsm[0]);

            /* second simplex -- new vx plays the role of the old v1 */
            fsm[1] = Gem_createAndInitSS(thee);
            SS_setReality(fsm[1], reality);
            SS_setClass(fsm[1], class);
            SS_setType(fsm[1], type);
            SS_setChart(fsm[1], color);
            SS_setVertex(fsm[1], 0, vx);
            SS_setVertex(fsm[1], 1, v[1]);
            SS_setVertex(fsm[1], 2, v[2]);
            SS_setFaceType(fsm[1], 0, 0);
            SS_setFaceType(fsm[1], 1, 0);
            SS_setFaceType(fsm[1], 2, 0);
            if (Gem_dim(thee)==3) {
                SS_setVertex(fsm[1], 3, v[3]);
                SS_setFaceType(fsm[1], 3, 0);
            } else {
                SS_setVertex(fsm[1], 3, VNULL);
                SS_setFaceType(fsm[1], 3, 0);
            }
            SS_buildRing(fsm[1]);

            /* third simplex -- new vx plays the role of the old v2 */
            fsm[2] = Gem_createAndInitSS(thee);
            SS_setReality(fsm[2], reality);
            SS_setClass(fsm[2], class);
            SS_setType(fsm[2], type);
            SS_setChart(fsm[2], color);
            SS_setVertex(fsm[2], 0, vx);
            SS_setVertex(fsm[2], 1, v[2]);
            SS_setVertex(fsm[2], 2, v[0]);
            SS_setFaceType(fsm[2], 0, 0);
            SS_setFaceType(fsm[2], 1, 0);
            SS_setFaceType(fsm[2], 2, 0);
            if (Gem_dim(thee)==3) {
                SS_setVertex(fsm[2], 3, v[3]);
                SS_setFaceType(fsm[2], 3, 0);
            } else {
                SS_setVertex(fsm[2], 3, VNULL);
                SS_setFaceType(fsm[2], 3, 0);
            }
            SS_buildRing(fsm[2]);

            /* fourth simplex -- new vx plays the role of the old v3 */
            if (Gem_dim(thee)==3) {
                fsm[3] = Gem_createAndInitSS(thee);
                SS_setReality(fsm[3], reality);
                SS_setClass(fsm[3], class);
                SS_setType(fsm[3], type);
                SS_setChart(fsm[3], color);
                SS_setVertex(fsm[3], 0, v[0]);
                SS_setVertex(fsm[3], 1, v[1]);
                SS_setVertex(fsm[3], 2, v[2]);
                SS_setVertex(fsm[3], 3, vx);
                SS_setFaceType(fsm[3], 0, 0);
                SS_setFaceType(fsm[3], 1, 0);
                SS_setFaceType(fsm[3], 2, 0);
                SS_setFaceType(fsm[3], 3, 0);
                SS_buildRing(fsm[3]);
            }

        } else { VASSERT(0); }

        /* make a picture */
        if (vxid < VXNUM) {
#if 0
            sock = Vio_socketOpen("w","INET", "ASC", "localhost", "1");
            Gem_writeGV(thee,sock,0,0,0,1.0,0,defX);
            Vio_socketClose(&sock);
            Vnm_print(2,"HIT RETURN TO CONTINUE...");
            c=getchar();
#endif
        }

        /* flip link facets of this point until we are delaunay */
        Gem_flip(thee, vx);

        /* make a picture */
        /* if ( (vxid < VXNUM) && ((vxid % 10) == 0) ){ */
        if (vxid < VXNUM) {
            sock = Vio_socketOpen("w","INET", "ASC", "localhost", "1");
            Gem_writeGV(thee,sock,0,0,0,1.0,0,defX);
            Vio_socketClose(&sock);
#if 0
            Vnm_print(2,"HIT RETURN TO CONTINUE...");
            c=getchar();
#endif
        }
    }

    /* delete the entire rings of simplices which use the bbox vertices */
    for (i=0; i<Gem_dimVV(thee); i++) {

        /* delete the current ring */
        while ( (sm=VV_firstSS(vb[i])) != VNULL ) {

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
            }

            /* now remove the last guy */
            Gem_destroySS(thee);
        }
    }

    /* delete the bbox vertices */
    for (i=0; i<Gem_dimVV(thee); i++)
        Gem_destroyVV(thee);

    /* one pass through simplices to destroy non-convex simplices */
#if 0
    smid = 0;
    while (smid < Gem_numSS(thee)) {
        sm = Gem_SS(thee,smid);
        found = 0;
        for (j=0; j<Gem_dimVV(thee); j++)
            if (VV_type(SS_vertex(sm,j)) == 0)
                found = 1;
        if (!found) {
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
            } else {
                smid++;
            }

            /* now remove the last guy */
            Gem_destroySS(thee);
        } else {
            smid++;
        }
    }
#endif

    /* make a boundary */
    Gem_makeBnd(thee,1);

    /* make a picture */
    Vnm_print(2,"DRAWING FINAL MESH\n");
    sock = Vio_socketOpen("w","INET", "ASC", "localhost", "1");
    Gem_writeGV(thee,sock,0,0,0,1.0,0,defX);
    Vio_socketClose(&sock);
}

/*
 * ***************************************************************************
 * Routine:  Gem_flip
 *
 * Purpose:  Edge or face flip for the incremental flip algorithm.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_flip(Gem *thee, VV *vx)
{
    int i, j, k, currentQ, qid, sm0_facet, sm1_facet, sm2_facet, smnb_facet;
    int reality, class, type, color;
    int scnt, found, jmax, imin, imax, swapped, smid;
    SS *sm0, *sm1, *sm2, *sm3, *smnb, *ss[100], *ss2[100], *lastS, *sm;
    SS sx0, sx1, sx2;
    VV *vx0, *vx1, *vx2, *vxnb, *vv[100];

    /* check the simplex Qs for emptyness */
    currentQ = 0;
    if (Gem_numSQ(thee,currentQ) > 0) {
        Vnm_print(2,"Gem_flip: non-empty flip Q%d....clearing..",currentQ);
        Gem_resetSQ(thee,currentQ);
        Vnm_print(2,"..done.\n");
    }
    VASSERT( Gem_numSQ(thee,currentQ) == 0 );
    if (Gem_numSQ(thee,!currentQ) > 0) {
        Vnm_print(2,"Gem_flip: non-empty flip Q%d....clearing..",!currentQ);
        Gem_resetSQ(thee,!currentQ);
        Vnm_print(2,"..done.\n");
    }
    VASSERT( Gem_numSQ(thee,!currentQ) == 0 );

    /* place all non-Delaunay link facets into the initial Q */
    for (sm0=VV_firstSS(vx); sm0!=VNULL; sm0=SS_link(sm0,vx)) {
        sm0_facet  = SS_vptr2localVnum(sm0,vx);
        sm1        = SS_nabor(sm0,sm0_facet);
        if (sm1 != VNULL) {
            sm1_facet = SS_sharedFaceLocNum(sm1,sm0);
            vxnb      = SS_vertex(sm1,sm1_facet);
            if ( Gem_inSphere(thee,sm0,sm0_facet,vx,vxnb) > 0 )
                Gem_appendSQ(thee, currentQ, sm0);
        }
    }

    /* traverse current Q and flip non-Delaunay link-facets until Q is empty */
    while ( Gem_numSQ(thee,currentQ) > 0 ) {

        /* traverse Q, flipping non-Delaunay link-facets */
        for (qid=0; qid<Gem_numSQ(thee,currentQ); qid++) {

            /* retrieve the Q link-facet pair */
            sm0 = Gem_SQ(thee,currentQ, qid);
            sm0_facet = SS_vptr2localVnum(sm0,vx);
            /* VASSERT( Gem_orient(thee,sm0) >= 0 ); */

            /* if non-null nabor */
            sm1 = SS_nabor(sm0,sm0_facet);
            if (sm1 != VNULL) {
                sm1_facet = SS_sharedFaceLocNum(sm1,sm0);
                vxnb      = SS_vertex(sm1,sm1_facet);

                /* if still non-delaunay */
                if ( Gem_inSphere(thee,sm0,sm0_facet,vx,vxnb) > 0 ) {

                  /* 2D: just flip the edge (if region is convex) */
                  if (Gem_dim(thee) == 2) {

                    /* 2-2 swap */
                    for (i=0; i<3; i++) {
                        SS_setVertex(&sx0, i, SS_vertex(sm0,i));
                        SS_setVertex(&sx1, i, SS_vertex(sm1,i));
                    }
                    SS_setVertex(&sx0, vmapF[sm0_facet][0], vxnb);
                    SS_setVertex(&sx1, vmapF[sm1_facet][0], vx);

                    /* if this region was non-convex, swap back and re-Q sm0 */
                    if (  (Gem_orient(thee,&sx0) < 0)
                       || (Gem_orient(thee,&sx1) < 0) ) {

                        smnb = SS_nabor(sm0,sm0_facet);
                        if ( smnb != VNULL ) {
                            smnb_facet = SS_sharedFaceLocNum(smnb,sm0);
                            vxnb       = SS_vertex(smnb,smnb_facet);
                            /* if facet non-delaunay, place sm0 on second Q */
                            if ( Gem_inSphere(thee,sm0,sm0_facet,vx,vxnb) > 0 )
                                Gem_appendSQ(thee, !currentQ, sm0);
                        }

                    /* region convex; check two new faces for delaunayness */
                    } else {
                        SS_meltRing(sm0);
                        SS_meltRing(sm1);
                        SS_setVertex(sm0, vmapF[sm0_facet][0], vxnb);
                        SS_setVertex(sm1, vmapF[sm1_facet][0], vx);
                        SS_buildRing(sm0);
                        SS_buildRing(sm1);
                        VASSERT( Gem_orient(thee,sm0) >= 0 );
                        VASSERT( Gem_orient(thee,sm1) >= 0 );

                        /* check for delaunayness of sm0 */
                        sm0_facet = SS_vptr2localVnum(sm0,vx);
                        smnb      = SS_nabor(sm0,sm0_facet);
                        if ( smnb != VNULL ) {
                            smnb_facet = SS_sharedFaceLocNum(smnb,sm0);
                            vxnb       = SS_vertex(smnb,smnb_facet);
                            /* if facet non-delaunay, place sm0 on second Q */
                            if ( Gem_inSphere(thee,sm0,sm0_facet,vx,vxnb) > 0 )
                                Gem_appendSQ(thee, !currentQ, sm0);
                        }

                        /* check for delaunayness of sm1 */
                        sm1_facet = SS_vptr2localVnum(sm1,vx);
                        smnb      = SS_nabor(sm1,sm1_facet);
                        if ( smnb != VNULL ) {
                            smnb_facet = SS_sharedFaceLocNum(smnb,sm1);
                            vxnb       = SS_vertex(smnb,smnb_facet);
                            /* if facet non-delaunay, place sm1 on second Q */
                            if ( Gem_inSphere(thee,sm1,sm1_facet,vx,vxnb) > 0 )
                                Gem_appendSQ(thee, !currentQ, sm1);
                        }
                    }

                  /* 3D: try 3-ring edge flip first, then faces (if convex) */
                  } else if (Gem_dim(thee) == 3) {

                    vx0 = SS_vertex(sm0, vmapF[sm0_facet][0]);
                    vx1 = SS_vertex(sm0, vmapF[sm0_facet][1]);
                    vx2 = SS_vertex(sm0, vmapF[sm0_facet][2]);

                    /* 3-2 (edge-to-face) swap */
                    swapped = 0;
                    scnt = 0;

                    /* edge (0-1) attempt */
                    if (scnt != 3) {
                        scnt = 0;
                        vv[0] = vx0;
                        vv[1] = vx1;
                        for (sm2=VV_firstSS(vv[0]); sm2!=VNULL;
                          sm2=SS_link(sm2,vv[0])) {
                            for (sm3=VV_firstSS(vv[1]); sm3!=VNULL;
                              sm3=SS_link(sm3,vv[1])) {
                                if (sm2 == sm3) {
                                    ss[scnt] = sm2;
                                    scnt++;
                                }
                            }
                        }
                        VASSERT( scnt <= 100 );
                    }

                    /* edge (1-2) attempt */
                    if (scnt != 3) {
                        scnt = 0;
                        vv[0] = vx1;
                        vv[1] = vx2;
                        for (sm2=VV_firstSS(vv[0]); sm2!=VNULL;
                          sm2=SS_link(sm2,vv[0])) {
                            for (sm3=VV_firstSS(vv[1]); sm3!=VNULL;
                              sm3=SS_link(sm3,vv[1])) {
                                if (sm2 == sm3) {
                                    ss[scnt] = sm2;
                                    scnt++;
                                }
                            }
                        }
                        VASSERT( scnt <= 100 );
                    }

                    /* edge (2-0) attempt */
                    if (scnt != 3) {
                        scnt = 0;
                        vv[0] = vx2;
                        vv[1] = vx0;
                        for (sm2=VV_firstSS(vv[0]); sm2!=VNULL;
                          sm2=SS_link(sm2,vv[0])) {
                            for (sm3=VV_firstSS(vv[1]); sm3!=VNULL;
                              sm3=SS_link(sm3,vv[1])) {
                                if (sm2 == sm3) {
                                    ss[scnt] = sm2;
                                    scnt++;
                                }
                            }
                        }
                        VASSERT( scnt <= 100 );
                    }

                    /* can we do one of the 3-2 (edge-to-face) swaps */
                    if (scnt == 3) {

                        Vnm_print(2,"STARTING: 3-2 (edge-to-face) flip\n");

                        /* grab/count the unique vertices in this situation */
                        vv[2] = vx;
                        vv[3] = vxnb;
                        jmax = 4;
                        for (i=0; i<3; i++) {
                            sm2 = ss[i];
                            for (k=0; k<4; k++) {
                                found = 0;
                                for (j=0; j<jmax; j++)
                                    if (SS_vertex(sm2, k) == vv[j]) found = 1;
                                if (!found) {
                                    vv[jmax] = SS_vertex(sm2, k);
                                    jmax++;
                                }
                            }
                        }

                        /* if jmax==5, then 3-simplex ring closed; can flip */
                        if (jmax == 5) {
    
                            /* order simps touching vx first in simplex list */
                            imin = 0;
                            imax = 2;
                            for (i=0; i<3; i++) {
                                found = 0;
                                for (j=0; j<4; j++)
                                    if (SS_vertex(ss[i],j) == vx) found = 1;
                                if (found) {
                                    ss2[imin] = ss[i];
                                    imin++;
                                } else {
                                    ss2[imax] = ss[i];
                                    imax--;
                                }
                            }
                            VASSERT( (1 <= imin) && (imin <= 2) );
                            VASSERT( imin == (imax+1) );
                            sm0 = ss2[0];
                            sm1 = ss2[1];
                            sm2 = ss2[2];

                            /* sm2 not touch vx; pull out of simplex rings */
                            SS_meltRing(sm2);
                            SS_reinit(sm2);

                            Vnm_print(2,"FINISHING: 3-2 (edge-to-face) flip\n");
                            SS_meltRing(sm0);
                            SS_meltRing(sm1);
                            SS_setVertex(sm0, 0, vv[0]);
                            SS_setVertex(sm0, 1, vv[2]);
                            SS_setVertex(sm0, 2, vv[3]);
                            SS_setVertex(sm0, 3, vv[4]);
                            SS_setVertex(sm1, 0, vv[1]);
                            SS_setVertex(sm1, 1, vv[2]);
                            SS_setVertex(sm1, 2, vv[3]);
                            SS_setVertex(sm1, 3, vv[4]);
                            SS_buildRing(sm0);
                            SS_buildRing(sm1);
                            if ( Gem_orient(thee,sm0) < 0 ) SS_reverse(sm0);
                            if ( Gem_orient(thee,sm1) < 0 ) SS_reverse(sm1);
                            VASSERT( Gem_orient(thee,sm0) > 0 );
                            VASSERT( Gem_orient(thee,sm1) > 0 );

                            swapped = 1;
                        } else {
                            Vnm_print(2,"BACKING-OUT: 3-to-2 flip\n");
                        }
                    }

                    /* 2-3 (face-to-edge) swap */
                    if (!swapped) {

                        Vnm_print(2,"STARTING: 2-3 (face-to-edge) flip\n");
                
                        /* attempt the face-to-edge swap */
                        SS_setVertex(&sx0, 0, vx);
                        SS_setVertex(&sx0, 1, vx0);
                        SS_setVertex(&sx0, 2, vx1);
                        SS_setVertex(&sx0, 3, vxnb);
                        SS_setVertex(&sx1, 0, vx);
                        SS_setVertex(&sx1, 1, vx1);
                        SS_setVertex(&sx1, 2, vx2);
                        SS_setVertex(&sx1, 3, vxnb);
                        SS_setVertex(&sx2, 0, vx);
                        SS_setVertex(&sx2, 1, vx2);
                        SS_setVertex(&sx2, 2, vx0);
                        SS_setVertex(&sx2, 3, vxnb);
                        if ( Gem_orient(thee,&sx0) < 0 ) {
                            Vnm_print(2,"-- sx0 BAD: <%g> --\n",
                                Gem_orientVal(thee,&sx0));
                        }
                        if ( Gem_orient(thee,&sx1) < 0 ) {
                            Vnm_print(2,"-- sx1 BAD: <%g> --\n",
                                Gem_orientVal(thee,&sx1));
                        }
                        if ( Gem_orient(thee,&sx2) < 0 ) {
                            Vnm_print(2,"-- sx2 BAD: <%g> --\n",
                                Gem_orientVal(thee,&sx2));
                        }

                        /* if region was non-convex, swap back and re-Q sm0 */
                        if (  (Gem_orient(thee,&sx0) < 0)
                           || (Gem_orient(thee,&sx1) < 0)
                           || (Gem_orient(thee,&sx2) < 0) ) {
                            Vnm_print(2,"BACKING-OUT: 2-to-3 flip\n");
                            smnb = SS_nabor(sm0,sm0_facet);
                            if ( smnb != VNULL ) {
                                smnb_facet = SS_sharedFaceLocNum(smnb,sm0);
                                vxnb       = SS_vertex(smnb,smnb_facet);
                                /* if facet non-delaunay, place sm0 on Q2 */
                                if (Gem_inSphere(thee,sm0,sm0_facet,vx,vxnb)>0)
                                    Gem_appendSQ(thee, !currentQ, sm0);
                            }

                        /* region convex; check 3 new faces for delaunayness */
                        } else {
                            Vnm_print(2,"FINISHING: 2-3 (face-to-edge) flip\n");

                            /* get various attibutes of parent */
                            reality = SS_reality(sm0);
                            class   = SS_class(sm0);
                            type    = SS_type(sm0);
                            color   = SS_chart(sm0);

                            /* grab a third simplex */
                            sm2 = Gem_createAndInitSS(thee);
                            SS_setReality(sm2, reality);
                            SS_setClass(sm2, class);
                            SS_setType(sm2, type);
                            SS_setChart(sm2, color);
                            SS_setFaceType(sm2, 0, 0);
                            SS_setFaceType(sm2, 1, 0);
                            SS_setFaceType(sm2, 2, 0);
                            SS_setFaceType(sm2, 3, 0);

                            /* set things up */
                            SS_meltRing(sm0);
                            SS_meltRing(sm1);
Vnm_print(2,"vx=<%d>  v0=<%d>  v1=<%d>  v2=<%d>  vxnb=<%d>\n",
    VV_id(vx), VV_id(vx0), VV_id(vx1), VV_id(vx2), VV_id(vxnb));
                            SS_setVertex(sm0, 0, vx);
                            SS_setVertex(sm0, 1, vx0);
                            SS_setVertex(sm0, 2, vx1);
                            SS_setVertex(sm0, 3, vxnb);
                            SS_setVertex(sm1, 0, vx);
                            SS_setVertex(sm1, 1, vx1);
                            SS_setVertex(sm1, 2, vx2);
                            SS_setVertex(sm1, 3, vxnb);
                            SS_setVertex(sm2, 0, vx);
                            SS_setVertex(sm2, 1, vx2);
                            SS_setVertex(sm2, 2, vx0);
                            SS_setVertex(sm2, 3, vxnb);
                            SS_buildRing(sm0);
                            SS_buildRing(sm1);
                            SS_buildRing(sm2);
                            VASSERT( Gem_orient(thee,sm0) >= 0 );
                            VASSERT( Gem_orient(thee,sm1) >= 0 );
                            VASSERT( Gem_orient(thee,sm2) >= 0 );

                            /* check for delaunayness of sm0 */
                            sm0_facet = SS_vptr2localVnum(sm0,vx);
                            smnb      = SS_nabor(sm0,sm0_facet);
                            if ( smnb != VNULL ) {
                                smnb_facet = SS_sharedFaceLocNum(smnb,sm0);
                                vxnb       = SS_vertex(smnb,smnb_facet);
                                /* if facet non-delaunay, place sm0 on Q2 */
                                if (Gem_inSphere(thee,sm0,sm0_facet,vx,vxnb)>0)
                                    Gem_appendSQ(thee, !currentQ, sm0);
                            }
    
                            /* check for delaunayness of sm1 */
                            sm1_facet = SS_vptr2localVnum(sm1,vx);
                            smnb      = SS_nabor(sm1,sm1_facet);
                            if ( smnb != VNULL ) {
                                smnb_facet = SS_sharedFaceLocNum(smnb,sm1);
                                vxnb       = SS_vertex(smnb,smnb_facet);
                                /* if facet non-delaunay, place sm1 on Q2 */
                                if (Gem_inSphere(thee,sm1,sm1_facet,vx,vxnb)>0)
                                    Gem_appendSQ(thee, !currentQ, sm1);
                            }
    
                            /* check for delaunayness of sm2 */
                            sm2_facet = SS_vptr2localVnum(sm2,vx);
                            smnb      = SS_nabor(sm2,sm2_facet);
                            if ( smnb != VNULL ) {
                                smnb_facet = SS_sharedFaceLocNum(smnb,sm2);
                                vxnb       = SS_vertex(smnb,smnb_facet);
                                /* if facet non-delaunay, place sm2 on Q2 */
                                if (Gem_inSphere(thee,sm2,sm2_facet,vx,vxnb)>0)
                                    Gem_appendSQ(thee, !currentQ, sm2);
                            }
                        }
                    }
    
                  } else { VASSERT(0); } /* if (Gem_dim(thee) == 2) { */
                } /* if ( Gem_inSphere(thee,sm0,sm0_facet,vx,vxnb) > 0 ) { */
            } /* if (sm1 != VNULL) { */
        } /* for (qid=0; qid<Gem_numSQ(thee,currentQ); qid++) { */

        /* reset the current Q and then swap the Qs */
        Gem_resetSQ(thee,currentQ);
        currentQ = !currentQ;

    } /* while ( Gem_numSQ(thee,currentQ) > 0 ) { */

    /* all Qs should be empty at this point */
    for (i=0; i<VMAXSQ; i++)
        VASSERT( Gem_numSQ(thee,i) == 0 );

    /* clean up deleted simplices */
    smid = 0;
    while (smid < Gem_numSS(thee)) {
        sm = Gem_SS(thee,smid);
        if (SS_vertex(sm,0) == VNULL) {

            /* if sm is not last in the list, exchange it with the last one */
            lastS=Gem_lastSS(thee);
            if ( (sm != lastS) && (SS_vertex(lastS,0) != VNULL) ) {
                SS_meltRing(lastS);
                SS_setType(sm, SS_type(lastS));
                SS_setChart(sm, SS_chart(lastS));
                for (j=0; j<Gem_dimVV(thee); j++) {
                    SS_setVertex( sm, j, SS_vertex(lastS,j) );
                    SS_setFaceType( sm, j, SS_faceType(lastS,j) );
                }
                SS_buildRing(sm);
                SS_reinit(lastS);
            } else if (SS_vertex(lastS,0) == VNULL) {
                /* don't increment */
            } else {
                smid++;
            }

            /* now remove the last guy */
            Gem_destroySS(thee);
        } else {
            smid++;
        }
    }

    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        VASSERT( SS_vertex(sm,0) != VNULL );
    }
}

/*
 * ***************************************************************************
 * Routine:  Gem_deform
 *
 * Purpose:  Edge or face flip for the incremental flip algorithm.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_deform(Gem *thee, int dimX, double *defX[MAXV])
{
    int i, j;
    double val;
    VV *vx;

    /* sanity check */
    VWARN( dimX == Gem_dimII(thee) );

    /* deform (actually displace) the vertices */
    for (i=0; i<Gem_numVV(thee); i++) {
        vx = Gem_VV(thee,i);
        for (j=0; j<dimX; j++) {
            val = VV_coord(vx,j) + defX[j][i];
            VV_setCoord(vx, j, val);
        }
    }

    return 0;
}

