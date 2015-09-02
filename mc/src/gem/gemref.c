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
 * rcsid="$Id: gemref.c,v 1.30 2010/08/12 05:18:57 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     gemref.c
 *
 * Purpose:  Class Gem: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "gem_p.h"

VEMBED(rcsid="$Id: gemref.c,v 1.30 2010/08/12 05:18:57 fetk Exp $")

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
 * Routine:  Gem_markRefine
 *
 * Purpose:  Mark simplices to be refined.
 *
 * Input:    If (key == -1)  Clear all simplex refinement flags.
 *           If (key == 0)   Mark all simplices for refinement.
 *           If (key == 1)   Mark special simplices for a testcase refinement.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_markRefine(Gem *thee, int key, int color)
{
    int i,j,k,count,marked,currentQ,markMe,chart[4],fType[4],vType[4];
    double vx[4][3];
    SS *sm;

    /* count = num generations to produce from marked simplices (minimally) */
    count = 1; /* must be >= 1 */

    /* marked = num simplices marked for refinement */
    marked = 0;

    /* check the refinement Qs for emptyness */
    currentQ = 0;
    if (Gem_numSQ(thee,currentQ) > 0) {
        Vnm_print(0,"Gem_markRefine: non-empty refine Q%d....clearing..",
            currentQ);
        Gem_resetSQ(thee,currentQ);
        Vnm_print(0,"..done.\n");
    }
    if (Gem_numSQ(thee,!currentQ) > 0) {
        Vnm_print(0,"Gem_markRefine: non-empty refine Q%d....clearing..",
            !currentQ);
        Gem_resetSQ(thee,!currentQ);
        Vnm_print(0,"..done.\n");
    }
    VASSERT( Gem_numSQ(thee,currentQ)  == 0 );
    VASSERT( Gem_numSQ(thee,!currentQ) == 0 );

    /* clear everyone's refinement flags */
    Vnm_print(0,"Gem_markRefine: clearing all simplex refinement flags..");
    for (i=0; i<Gem_numSS(thee); i++) {
        if ( (i>0) && (i % VPRTKEY) == 0 ) Vnm_print(0,"[MS:%d]",i);
        sm = Gem_SS(thee,i);
        SS_setRefineKey(sm,currentQ,0);
        SS_setRefineKey(sm,!currentQ,0);
        SS_setRefinementCount(sm,0); /* refine X many times? */
    }
    Vnm_print(0,"..done.\n");

    /* mark all simplices (of appropriate color) to be refined */
    if (key == -1) {
        /* this is already done... */
    } else if (key == 0) {
        /* mark everyone for refinement */
        Vnm_print(0,"Gem_markRefine: marking all simplices..");
        for (i=0; i<Gem_numSS(thee); i++) {
            if ( (i>0) && (i % VPRTKEY) == 0 ) Vnm_print(0,"[MS:%d]",i);
            sm = Gem_SS(thee,i);
            if ( ((int)SS_chart(sm)==color)||(color<0) ) {
                Gem_appendSQ(thee,currentQ, sm); /* add to refinement Q */
                SS_setRefineKey(sm,currentQ,1);  /* note is now on refine Q */
                SS_setRefinementCount(sm,count); /* refine X many times? */
                marked++;
            }
        }
        Vnm_print(0,"..done.  [marked=<%d>]\n", marked);
    } else if (key == 1) {
        /* user-defined marking */
        Vnm_print(0,"Gem_markRefine: marking with user-defined choice..");

        i = 0;
        while ( (i < Gem_numSS(thee)) && (!Vnm_sigInt()) ) {
            sm = Gem_SS(thee,i);
            if ( (i>0) && (i % VPRTKEY) == 0 ) Vnm_print(0,"[MS:%d]",i);
            if ( ((int)SS_chart(sm)==color)||(color<0) ) {

                /* grab vertices of the simplex */
                for (j=0; j<Gem_dimVV(thee); j++) {
                    fType[j] = SS_faceType(sm,j);
                    vType[j] = VV_type( SS_vertex(sm,j) );
                    chart[j] = VV_chart( SS_vertex(sm,j) );
                    for (k=0; k<Gem_dimII(thee); k++) {
                        vx[j][k] = VV_coord( SS_vertex(sm,j), k );
                    }
                }
                   
                /* user-defined marking choice */
                markMe = thee->pde->markSimplex( Gem_dim(thee), Gem_dimII(thee),
                    SS_type(sm), fType, vType, chart, vx, sm );

                /* mark it if requested */
                if ( markMe ) {
                    Gem_appendSQ(thee,currentQ, sm); /* add to refinement Q */
                    SS_setRefineKey(sm,currentQ,1);  /* note now on refine Q */
                    SS_setRefinementCount(sm,count); /* refine X many times? */
                    marked++;
                }
            }
            /* next sm */
            i++;
        } /* i; loop over simplices */

        Vnm_print(0,"..done.  [marked=<%d>]\n", marked);
    } else Vnm_print(0,"Gem_markRefine: request invalid....bailing out.\n");

    /* return with no errors */
    return marked;
}

/*
 * ***************************************************************************
 * Routine:  Gem_refine
 *
 * Purpose:  Refine the manifold and also build a prolongation operator that
 *           can interpolate functions from the original manifold to the
 *           new manifold.
 *
 * Input:    If (rkey==0) Perform recursive simplex bisection until conformity
 *
 *           If (rkey==1) Perform first quadra-[octa-]-section, followed by
 *                        recursive simplex bisection until conformity
 *
 *                        IMPORTANT NOTE: In 2D, (rkey==1) WILL generate
 *                        a conforming mesh.  However, in 3D, this procedure
 *                        will in general produce nonconforming simplices.
 *                        To produce a conforming mesh in 3D would require an
 *                        implementation covering all possible face refinement
 *                        combinations (something like 169 cases).  This has
 *                        been done e.g. by Jurgen Bey in AGM, but we are
 *                        not that patient; use (rkey==0) above if you want
 *                        a conforming mesh...
 *
 *           If (rkey==2) As a test of the conformity procedure, perform
 *                        quadra-[octa-]-section until conformity, which
 *                        should produce a uniformly regularly refined mesh.
 *                        (In 2D, each triangle should be divided into four
 *                        children, and in 3D each tetrahedron should be
 *                        divided into eight children.)
 *
 * Notes:    Longest Edge, Newest Vertex, or Newest Pair, is used to bisect
 *           a single simplex in an asymptotically non-degenerate way in the
 *           "bisect[LE,NV,NP]" routines which are called from this routine.
 *           Marked simplices are subdivided into 2/4/8 child simplices.
 *           A closure algorithm is performed which continues subdivision
 *           until a conforming mesh is produced.  Boundary
 *           nodes/edges[faces] are correctly refined.
 *
 *           We purposely do the following trick in order to facilitate the
 *           construction of a prolongation operator after refinement,
 *           if it is so desired.  We begin the refinement with no edges;
 *           only the conforming mesh as described by the list of vertices
 *           and the list of simplices using the vertices.  When a simplex
 *           is to be subdivided, the refinement edge (or edges) is then
 *           identified, and then created on the fly.  The new vertex which
 *           is created by the refinement, namely the midpoint of the edge,
 *           is then stored with the newly created edge.  The edge is added
 *           to the ring of edges around each of its two vertices.  This
 *           allows our refinement algorithm to easily detect whether or
 *           not an edge has already been refined by a naboring simplex by
 *           simply traversing the edge lists of the two vertices on the
 *           refinement edge.  If the edge exists, then it must have already
 *           been refined, since it is only created in order to refine it.
 *           Moreover, the new vertex at the midpoint of the edge is then
 *           also directly available from the edge structure for use in
 *           building the children simplices, without having to search for it.
 *           (The edge datastructure can be viewed as simply a holding cell
 *           for the newly created vertices so that they can be found without
 *           any searching.) 
 *
 *           How does this help us to later build an appropriate prolongation
 *           operator between the original mesh and the final refined mesh?
 *           While we begin the refinement with no edges, we end with a
 *           list of edges that is precisely the set of edges that were
 *           refined.  Let us order the function values of a mesh function
 *           on the fine mesh (with function values at vertices) in the
 *           following order: vertices common to the coarse mesh in the same
 *           order as the coarse mesh, followed by vertices at the midpoints
 *           of the refined mesh, in the order of the edges in the edge list.
 *           The linear prolongation operator (for example) which would
 *           linearly interpolate a function from the original coarse mesh
 *           to the refined mesh is then a block 2x1 matrix.  The upper block
 *           is a square identity matrix with number of rows/columns equal
 *           to the number of vertices in the original mesh; it is completely
 *           clear how to build this upper block.  The lower block is a
 *           (generally) rectangular matrix, with number of rows equal to the
 *           number of edges that were refined.  Since we finish refinement
 *           with precisely the refined edges in the edge list, he can
 *           simply traverse the edge list to build the lower block of the
 *           prolongation matrix.  In particular, in the linear interpolation
 *           case, each row of the lower block will be zero, except for two
 *           columns, corresponding to the vertex numbers of the two coarse
 *           mesh vertices which lie on the ends of the edge that was refined.
 *           A value of 0.5 is then placed in those two columns.
 *
 *           In the case of linear prolongation, the lower block of the
 *           prolongation matrix has exactly one row for each edge that was
 *           refined, with zeros as every entry except for the two columns
 *           corresponding to the vertex numbers that were on each end of the
 *           edge that was bisected.
 *
 *           There is an opportunity for a problem with this approach; if an
 *           edge is multiply refined, then we must keep track of all of the
 *           resulting edges and their parent-child relationships, in order
 *           to build the correct interpolation.  The lower block of the
 *           prolongation matrix will now be slightly more complicated than
 *           described above.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_refine(Gem *thee, int rkey, int bkey, int pkey)
{
    int refined, currentQ, loop, qid;

    Vnm_tstart(60, "manifold refinement");

    /* input check and some i/o */
    if (rkey == 0) {
        Vnm_print(0,"Gem_refine: TODO: [Bsect]-->[Bsect to conformity]\n");
        if (bkey == 0) {
            Vnm_print(0,"Gem_refine: Bisection type: Longest Edge\n");
        } else if (bkey == 1) {
            Vnm_print(0,"Gem_refine: Bisection type: Newest Vertex\n");
        } else /* (bkey == 2) */ {
            Vnm_print(0,"Gem_refine: Bisection type: Newest Pair\n");
        }
    } else if (rkey == 1) {
        Vnm_print(0,"Gem_refine: TODO: [Qsect]-->[Bsect to conformity]\n");
        if (bkey == 0) {
            Vnm_print(0,"Gem_refine: Bisection type: Longest Edge\n");
        } else if (bkey == 1) {
            Vnm_print(0,"Gem_refine: Bisection type: Newest Vertex\n");
        } else /* (bkey == 2) */ {
            Vnm_print(0,"Gem_refine: Bisection type: Newest Pair\n");
        }
    } else if (rkey == 2) {
        Vnm_print(0,"Gem_refine: TODO: [Qsect]-->[Qsect to conformity]\n");
    } else {
        Vnm_print(0,"Gem_refine: Bad input!\n");
        rkey = 0;
    }

    /* ********************************************************************* */
    /* MUST HAVE EMPTY EDGE LIST: edge list must be empty before refinement  */
    /* ********************************************************************* */
    if (Gem_numEE(thee) > 0) {
        Vnm_print(0,"Gem_refine: non-empty edge list....clearing it.\n");
        Gem_destroyEdges(thee);
        VASSERT( Gem_numEE(thee) == 0 );
    }

    /* count number actually refined */
    refined = 0;

    /* first pass setup; keep track of which queue is which.. */
    currentQ = 0;

    /* refinement/conformity main loop */
    Vnm_tstart(61, "manifold refinement core");
    Vnm_print(0,"Gem_refine: refinement..");
    loop = 0;
    while ( Gem_numSQ(thee,currentQ) > 0 ) {
        Vnm_print(0, "[%d]",loop);

        /* traverse Q, refine each simplex (nonconf simps appended to !Q) */
        VASSERT( Gem_numSQ(thee,!currentQ) == 0 );
        for (qid=0; qid<Gem_numSQ(thee,currentQ); qid++) {
            SS *qs = Gem_SQ(thee,currentQ, qid);
            if (loop == 0) {
                if (rkey == 0) {
                    if (bkey == 0) {
                        Gem_bisectLE(thee, qs, currentQ);
                    } else if (bkey == 1) {
                        Gem_bisectNV(thee, qs, currentQ);
                    } else /* (bkey == 2) */ {
                        Gem_bisectNP(thee, qs, currentQ);
                    }
                } else {
                    Gem_octsect(thee, qs, currentQ);
                }
            } else {
                if (rkey == 2) {
                    Gem_octsect(thee, qs, currentQ);
                } else {
                    if (bkey == 0) {
                        Gem_bisectLE(thee, qs, currentQ);
                    } else if (bkey == 1) {
                        Gem_bisectNV(thee, qs, currentQ);
                    } else /* (bkey == 2) */ {
                        Gem_bisectNP(thee, qs, currentQ);
                    }
                }
            }
            refined++;
        }
        /* cleanup the queue */
        Gem_resetSQ(thee,currentQ);
        VASSERT( Gem_numSQ(thee,currentQ) == 0 );

        /* swap the Q roles */
        currentQ = !currentQ;

        /* increment the loop variable */
        loop++;
    }
    Vnm_print(0,"..conforming.  [refined=<%d>]\n", refined);
    Vnm_tstop(61, "manifold refinement core");

    /* return */
    Vnm_tstop(60, "manifold refinement");
    return refined;
}

/*
 * ***************************************************************************
 * Routine:  Gem_refineEdge
 *
 * Purpose:  We do three things in this routine:
 *           (1) Find the midpoint of existing edge, or create it
 *           (2) Tell simplices using edge that they are now nonconforming
 *           (3) Determine the "type" of the new point by using the type
 *               of the edge.  The edge type must itself be calculated 
 *               on the fly, because we allow the use of lazy edge creation.
 *
 * Notes:    Note that we MUST determine the type of the new point
 *           (interior or boundary) based effectively on EDGE types
 *           rather than vertex or face types.  It is easy to construct
 *           examples where typing based on vertex type can mark a new 
 *           interior point falsely as a boundary point.  Note that typing by
 *           the faces of a single simplex which uses the bisection edge
 *           can also be fooled in 3D (it is foolproof in 2D).
 *           For example, it may be the case in 3D that an edge of a tet 
 *           touches a boundary, but none of its faces are boundary faces.
 *           In this case, the new point would be marked (incorrectly)
 *           as an interior point.
 *
 *           The solution to this problem is to determine the type of the
 *           new point by using the type of the edge.  The only problem we
 *           then face is how to do this without actually having edges around.
 *           In other words, we must determine the correct edge type on the 
 *           fly.  This can be handled by looking at all faces of all simplices 
 *           which use the edge, and applying the following rules:
 *           (1) If all faces are interior, the edge is interior
 *           (3) If at least one face is boundary, the edge is boundary
 *
 *           Note that since we must look at all simplices on the ring
 *           around the edge anyway to handle the conformity situation,
 *           we don't have to do any additional work to determine the
 *           correct edge type.  Therefore, we will take this approach
 *           at determining the correct edge type on the fly, EVEN IF
 *           the edges are always around and their correct types are 
 *           recorded correctly once and for all when a mesh is built.
 *
 *           This way we can also do lazy edge creation; i.e., create an 
 *           edge only when it needs to be refined.  The lazy edge is then
 *           in principle simply a holder for the new point, allowing O(1)
 *           access to the new point by other simplices, through the edge
 *           rings around their vertices.
 *
 *           Note that lazy edge creation has a serious performance benefit
 *           to this routine in particular: if all edges are around, then to
 *           find a particular edge, we then always have to search both edge
 *           rings associated with each vertex for a common edge.  This means
 *           we look for the intersection of two sets of five elements on
 *           average in 2D, and two sets of fifteen elements on average in 3D.  
 *           With lazy edge creation, we search only through lists of edges
 *           that were created for refinement; these lists are usually a
 *           much smaller.
 *
 *           A final advantage of lazy edge creation is that having a list
 *           of only the refined edges allows us to efficiently build a
 *           prolongation operator between the original mesh and the refined
 *           mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_refineEdge(Gem *thee, int currentQ,
    SS *sm, VV *v[4], VV **vAB, int A, int B)
{
    int j,iDid,cntInterior,cntBoundary,smFound,chart[4];
    int eType, eTypeI, eTypeD;
    double vx[3][3];
    SS *smA, *smB;
    EE *eg;

    /* get existing refinement edge (or create on fly), look for midpoint */
    iDid = 0;
    eg = Gem_findOrCreateEdge( thee, v[A], v[B], &iDid );
    (*vAB) = EE_midPoint(eg);

#if 0
    if (EE_parent(eg) != VNULL) {
        fprintf(stderr,"Gem_refineEdge: Edge with parent found =<%d>\n",
            EE_id(eg) );
    }
#endif

   /*
    * ************************************************************************
    * If *we* created the temporary edge to hold an as-yet-uncreated-new 
    * midpoint vertex (to be done below) as recorded by the "iDid" flag, then 
    * cycle thru the simplices using the unrefined edge (by cycling 
    * through the simplex rings around the vertices on each end of the edge)
    * and tell them that they are now non-conforming...
    *
    * If the edge was already created and we just grabbed it, then it was
    * created by a previous call to this routine; that means that the midpoint
    * also exists because it is also created by the same previous call to
    * this routine (is done below).
    *
    * Note that simplex sm should not be found on the list of currently
    * unmarked simplices which we are considering marking as non-confirming,
    * because it is in the currentQ generating this edge bisection.
    * ************************************************************************
    */
    if ( iDid != 0 ) {
        VASSERT( (*vAB) == VNULL );
        eType  = 0;
        eTypeI = 0;
        eTypeD = 0;
        cntInterior = 0;
        cntBoundary = 0;
        smFound = 0;
        for (smA=VV_firstSS(v[A]); smA!=VNULL; smA=SS_link(smA,v[A])) {
            for (smB=VV_firstSS(v[B]); smB!=VNULL; smB=SS_link(smB,v[B])) {
                if (smA == smB) {
                    /* if simplex not already marked then mark it */
                    if (  (SS_refineKey(smA,currentQ) == 0)
                       && (SS_refineKey(smA,!currentQ) == 0) ) {
                        VASSERT( smA != sm );
                        Gem_appendSQ(thee, !currentQ, smA); /* add to ref !Q*/
                        SS_setRefineKey(smA,!currentQ,1); /* guy is now on !Q*/
                        SS_setRefinementCount(smA,1);     /* num times to ref*/
                    }
                    /* count the face types (smA==sm definitely occurs here) */
                    if (EE_parent(eg) == VNULL) {
                        eType = SS_localEdgeType(smA,v[A],v[B]);
                        if ( VBOUNDARY(eType) ) {
                            eTypeD = VMAX2(eTypeD,eType);
                            cntBoundary++;
                        } else if ( VINTERIOR(eType) ) {
                            eTypeI = VMAX2(eTypeI,eType);
                            cntInterior++;
                        } else { VASSERT(0); }
                    }
                    /* doublecheck that sm was found! */
                    if (smA == sm) smFound = 1;
                }
            }
        }
        VASSERT( smFound );
       /*
        * ********************************************************************
        * Determine the edge type according to our boundary/interior rules.
        *
        * NOTE:  The above approach for determining the edgeType from the
        *        combined facetypes of all of the simplices on the edge
        *        ring only works if all of the simplices on the edge
        *        ring "register" their facetypes.  If all simplices are
        *        reachable (exist and can be grabbed from the edge ring
        *        in the edge ring loops above) then this works.  However,
        *        if we have a MULTIPLY REFINED EDGE, and not all simplices
        *        have been created for a preliminary refinement, then we
        *        may not actually get to all of the simplices in the above
        *        loops!  The result is that some boundary edges are
        *        mis-classified as interior edges.
        *
        *        The solution is to "type" each edge when it is created,
        *        and then "type" any children edges by using the types
        *        of the parent edges.  We then check this type here before
        *        we locally calculate the edge type.  If the edge is
        *        already typed, then there WAS a parent edge the typed it,
        *        we can just go with it.  Otherwise, there is no parent
        *        edge to get the type from (or it really was an interior
        *        edge), and we calculate it here locally from face types.
        *
        *        If there was a multiply refined edge, then the parent will
        *        exist; if not, then there is no parent, but that also means
        *        that our local calculation will work and we don't need the
        *        parent to determine the edge type.
        * ********************************************************************
        */
        if (EE_parent(eg) == VNULL) {
            if ( VINTERIOR( EE_type(eg) ) ) {
                /* If at least one face is boundary, the edge is boundary */
                if ( cntBoundary > 0 ) {
                    eType = eTypeD;
                /* If all faces are interior, the edge is interior */
                } else if ( cntInterior > 0 ) {
                    eType = eTypeI;
                } else { VASSERT(0); }
                EE_setType(eg,eType);
            }
        }

        /* setup for the call to bisectEdge */
        chart[0] = VV_chart(v[A]);
        chart[1] = VV_chart(v[B]);
        chart[2] = 0;
        for (j=0; j<Gem_dimII(thee); j++) {
            vx[0][j] = VV_coord(v[A], j);
            vx[1][j] = VV_coord(v[B], j);
            vx[2][j] = 0.;
        }
        eType = EE_type(eg);

        /* call bisectEdge */
        thee->pde->bisectEdge(Gem_dim(thee),Gem_dimII(thee),eType,chart,vx);

        /* call mapBoundary (if we bisected a boundary edge) */
        if ( VBOUNDARY(eType) ) {
            thee->pde->mapBoundary( Gem_dim(thee), Gem_dimII(thee), eType,
                chart[2], vx[2] );
        }

        /* create the new vertex and initialize it correctly */
        (*vAB) = Gem_createAndInitVV( thee );
        VV_setChart((*vAB), chart[2]);
        VV_setType((*vAB), eType);
        for (j=0; j<Gem_dimII(thee); j++)
            VV_setCoord((*vAB), j, vx[2][j]);
        EE_setMidPoint( eg, (*vAB) );
        VV_setParentEE( (*vAB), eg );

        /* update the boundary vertex counts */
        if ( VBOUNDARY(eType) ) Gem_numBVpp(thee);
    }

    VASSERT( (*vAB) != VNULL );
}

/*
 * ***************************************************************************
 * Routine:  Gem_octsect
 *
 * Purpose:  Uniform regular (quadrasection) refinement of a single simplex.
 *
 * Notes:    Boundary nodes/edges[faces] are correctly refined.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_octsect(Gem *thee, SS *sm, int currentQ)
{
    int i, j, k, canon, refCount, interior, numKids, badKids;
    int reality, class, type, color, lEdge, newFaces, fType[4];
    double len, L01_23,L02_13,L03_12;
    VV *v[4], *v01, *v02, *v12, *v03, *v13, *v23;
    SS *fsm[8];

   /*
    * ************************************************************************
    * first we check for logical consistency...
    * ************************************************************************
    */
    VASSERT( SS_refineKey(sm,currentQ) );

   /*
    * ************************************************************************
    * setup a "canonical" bisection
    * ************************************************************************
    */
    canon = SS_refinementEdge(sm);
    refCount = SS_refinementCount(sm);
    VASSERT( refCount >= 1 );
    refCount--;

   /*
    * ************************************************************************
    * get vertices for the canonical bisection; other setup
    * ************************************************************************
    */

    /* initialize and get simplices' vertices and its face types */
    for (i=0; i<8; i++) {
        fsm[i] = VNULL;
    }
    for (i=0; i<4; i++) {
        v[i] = VNULL;
        if (Gem_dim(thee) == 2) {
            fType[i] = SS_faceType( sm, i );
        } else { /* (Gem_dim(thee) == 3) */
            fType[i] = SS_faceType( sm, vmapV[canon][i] );
        }
    }
    for (i=0; i<Gem_dimVV(thee); i++) {
        if (Gem_dim(thee) == 2) {
            v[i] = SS_vertex( sm, i );
        } else { /* (Gem_dim(thee) == 3) */
            v[i] = SS_vertex( sm, vmapV[canon][i] );
        }
    }

    /* get various attibutes of parent that children should inherit */
    reality = SS_reality(sm);  /* we must force inheritance here */
    class   = SS_class(sm);    /* we must force inheritance here */
    type    = SS_type(sm);     /* we must force inheritance here */
    color   = SS_chart(sm);    /* we must force inheritance here */

   /*
    * ************************************************************************
    * refine the simplex by refining edge v0-v1, producing point v01
    * ************************************************************************
    */

    v01 = VNULL;
    v02 = VNULL;
    v12 = VNULL;
    v03 = VNULL;
    v13 = VNULL;
    v23 = VNULL;
    Gem_refineEdge(thee, currentQ, sm, v, &v01, 0,1);
    Gem_refineEdge(thee, currentQ, sm, v, &v02, 0,2);
    Gem_refineEdge(thee, currentQ, sm, v, &v12, 1,2);
    if (Gem_dim(thee)==3) {
        Gem_refineEdge(thee, currentQ, sm, v, &v03, 0,3);
        Gem_refineEdge(thee, currentQ, sm, v, &v13, 1,3);
        Gem_refineEdge(thee, currentQ, sm, v, &v23, 2,3);
    }

   /*
    * ************************************************************************
    * remove simplex from simplex rings, re-init for reuse as first child
    * ************************************************************************
    */

    SS_meltRing(sm);
    SS_reinit(sm);

   /*
    * ************************************************************************
    * the new simplices
    * ************************************************************************
    */

    /* fsm[0]: first corner (2d/3d) simplex based on v0 (v0-v01-v02-[v03]) */
    fsm[0] = sm; /* first child re-uses the parent simplex */
    SS_setReality(fsm[0], reality);
    SS_setClass(fsm[0], class);
    SS_setType(fsm[0], type);
    SS_setChart(fsm[0], color);
    SS_setVertex(fsm[0], 0, v[0]);
    SS_setVertex(fsm[0], 1, v01);
    SS_setVertex(fsm[0], 2, v02);
    SS_setFaceType(fsm[0], 0, 0);
    SS_setFaceType(fsm[0], 1, fType[1]);
    SS_setFaceType(fsm[0], 2, fType[2]);
    if (Gem_dim(thee)==3) {
        SS_setVertex(fsm[0], 3, v03);
        SS_setFaceType(fsm[0], 3, fType[3]);
    }
    SS_buildRing(fsm[0]);
    /* DAN-MIKE: Deal with internal face refinemens */
    /* 
     * if (fPtr[i] != VNULL && fPtr will be split) then
     *     make child0 --> FF --> g.uid    = fPtr.g.uid
     *                        --> d.rlevel = fPtr.d.rlevel+1
     *                        --> d.rhist  = fPtr.d.rhist
     *     make child1 --> FF --> g.uid    = fPtr.g.uid
     *                        --> d.rlevel = fPtr.d.rlevel+1
     *                        --> d.rhist  = fPtr.d.rhist (incremented!)
     * else if (fPtr[i] != VNULL && fPtr will NOT be split) then
     *     make childX --> copy of original FF, where X is child 
     *                     with the preserved face
     * end
     *
     * increment step for rlevel: TBD
     *
     */

    /* fsm[1]: second corner (2d/3d) simplex based on v1 (v1-v12-v01-[v13]) */
    fsm[1] = Gem_createAndInitSS( thee );
    SS_setReality(fsm[1], reality);
    SS_setClass(fsm[1], class);
    SS_setType(fsm[1], type);
    SS_setChart(fsm[1], color);
    SS_setVertex(fsm[1], 0, v[1]);
    SS_setVertex(fsm[1], 1, v12);
    SS_setVertex(fsm[1], 2, v01);
    SS_setFaceType(fsm[1], 0, 0);
    SS_setFaceType(fsm[1], 1, fType[2]);
    SS_setFaceType(fsm[1], 2, fType[0]);
    if (Gem_dim(thee)==3) {
        SS_setVertex(fsm[1], 3, v13);
        SS_setFaceType(fsm[1], 3, fType[3]);
    }
    SS_buildRing(fsm[1]);

    /* fsm[2]: third corner (2d/3d) simplex based on v2 (v2-v02-v12-[v23]) */
    fsm[2] = Gem_createAndInitSS( thee );
    SS_setReality(fsm[2], reality);
    SS_setClass(fsm[2], class);
    SS_setType(fsm[2], type);
    SS_setChart(fsm[2], color);
    SS_setVertex(fsm[2], 0, v[2]);
    SS_setVertex(fsm[2], 1, v02);
    SS_setVertex(fsm[2], 2, v12);
    SS_setFaceType(fsm[2], 0, 0);
    SS_setFaceType(fsm[2], 1, fType[0]);
    SS_setFaceType(fsm[2], 2, fType[1]);
    if (Gem_dim(thee)==3) {
        SS_setVertex(fsm[2], 3, v23);
        SS_setFaceType(fsm[2], 3, fType[3]);
    }
    SS_buildRing(fsm[2]);

    if (Gem_dim(thee)==2) {
        /* fsm[3]: fourth simplex (2d only, interior) new verts (v12-v02-v01)*/
        fsm[3] = Gem_createAndInitSS( thee );
        SS_setReality(fsm[3], reality);
        SS_setClass(fsm[3], class);
        SS_setType(fsm[3], type);
        SS_setChart(fsm[3], color);
        SS_setVertex(fsm[3], 0, v12);
        SS_setVertex(fsm[3], 1, v02);
        SS_setVertex(fsm[3], 2, v01);
        SS_setFaceType(fsm[3], 0, 0);
        SS_setFaceType(fsm[3], 1, 0);
        SS_setFaceType(fsm[3], 2, 0);
        SS_buildRing(fsm[3]);
    } else {
        /* fsm[3]: 4th corner (3d only) simplex based on v3 (v3-v03-v23-v13) */
        fsm[3] = Gem_createAndInitSS( thee );
        SS_setReality(fsm[3], reality);
        SS_setClass(fsm[3], class);
        SS_setType(fsm[3], type);
        SS_setChart(fsm[3], color);
        SS_setVertex(fsm[3], 0, v[3]);
        SS_setVertex(fsm[3], 1, v03);
        SS_setVertex(fsm[3], 2, v23);
        SS_setVertex(fsm[3], 3, v13);
        SS_setFaceType(fsm[3], 0, 0);
        SS_setFaceType(fsm[3], 1, fType[0]);
        SS_setFaceType(fsm[3], 2, fType[2]);
        SS_setFaceType(fsm[3], 3, fType[1]);
        SS_buildRing(fsm[3]);

       /*
        * ********************************************************************
        * deal with the inner-diamond -- three possible configurations
        * ********************************************************************
        */

        /* get the three possible interior edge lengths */
        L01_23 = Gem_edgeLength( thee, v01, v23 );
        L02_13 = Gem_edgeLength( thee, v02, v13 );
        L03_12 = Gem_edgeLength( thee, v03, v12 );
        /* Vnm_print(0, "L01_23 = %g\n", L01_23); */
        /* Vnm_print(0, "L02_13 = %g\n", L02_13); */
        /* Vnm_print(0, "L03_12 = %g\n", L03_12); */

        /* identify the SHORTEST interior edge (Zhang approach) */
        interior = 0;
        if      ((L01_23 <= L02_13) && (L01_23 <= L03_12)) interior = 0;
        else if ((L02_13 <= L01_23) && (L02_13 <= L03_12)) interior = 1;
        else if ((L03_12 <= L01_23) && (L03_12 <= L02_13)) interior = 2;
        else Vnm_print(0, "Problem!\n");

        if (interior == 0) {  /* v01-v23 */

           /*
            * ****************************************************************
            * first tetrahedron of the inner-diamond
            * (vertex order of:  v01,v12,v23,v13)
            * ****************************************************************
            */
            fsm[4] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[4], reality);
            SS_setClass(fsm[4], class);
            SS_setType(fsm[4], type);
            SS_setChart(fsm[4], color);
            SS_setVertex(fsm[4], 0, v01);
            SS_setVertex(fsm[4], 1, v12);
            SS_setVertex(fsm[4], 2, v23);
            SS_setVertex(fsm[4], 3, v13);
            SS_setFaceType(fsm[4], 0, fType[0]);
            SS_setFaceType(fsm[4], 1, 0);
            SS_setFaceType(fsm[4], 2, 0);
            SS_setFaceType(fsm[4], 3, 0);
            SS_buildRing(fsm[4]);

           /*
            * ****************************************************************
            * second tetrahedron of the inner-diamond
            * (vertex order of:  v23,v02,v12,v01)
            * ****************************************************************
            */
            fsm[5] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[5], reality);
            SS_setClass(fsm[5], class);
            SS_setType(fsm[5], type);
            SS_setChart(fsm[5], color);
            SS_setVertex(fsm[5], 0, v23);
            SS_setVertex(fsm[5], 1, v02);
            SS_setVertex(fsm[5], 2, v12);
            SS_setVertex(fsm[5], 3, v01);
            SS_setFaceType(fsm[5], 0, fType[3]);
            SS_setFaceType(fsm[5], 1, 0);
            SS_setFaceType(fsm[5], 2, 0);
            SS_setFaceType(fsm[5], 3, 0);
            SS_buildRing(fsm[5]);

           /*
            * ****************************************************************
            * third tetrahedron of the inner-diamond
            * (vertex order of:  v01,v02,v03,v23)
            * ****************************************************************
            */
            fsm[6] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[6], reality);
            SS_setClass(fsm[6], class);
            SS_setType(fsm[6], type);
            SS_setChart(fsm[6], color);
            SS_setVertex(fsm[6], 0, v01);
            SS_setVertex(fsm[6], 1, v02);
            SS_setVertex(fsm[6], 2, v03);
            SS_setVertex(fsm[6], 3, v23);
            SS_setFaceType(fsm[6], 0, fType[1]);
            SS_setFaceType(fsm[6], 1, 0);
            SS_setFaceType(fsm[6], 2, 0);
            SS_setFaceType(fsm[6], 3, 0);
            SS_buildRing(fsm[6]);

           /*
            * ****************************************************************
            * fourth tetrahedron of the inner-diamond
            * (vertex order of:  v23,v03,v01,v13)
            * ****************************************************************
            */
            fsm[7] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[7], reality);
            SS_setClass(fsm[7], class);
            SS_setType(fsm[7], type);
            SS_setChart(fsm[7], color);
            SS_setVertex(fsm[7], 0, v23);
            SS_setVertex(fsm[7], 1, v03);
            SS_setVertex(fsm[7], 2, v01);
            SS_setVertex(fsm[7], 3, v13);
            SS_setFaceType(fsm[7], 0, fType[2]);
            SS_setFaceType(fsm[7], 1, 0);
            SS_setFaceType(fsm[7], 2, 0);
            SS_setFaceType(fsm[7], 3, 0);
            SS_buildRing(fsm[7]);

        } else if (interior == 1) {  /* v02-v13 */

           /*
            * ****************************************************************
            * first tetrahedron of the inner-diamond
            * (vertex order of:  v02,v13,v01,v12)
            * ****************************************************************
            */
            fsm[4] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[4], reality);
            SS_setClass(fsm[4], class);
            SS_setType(fsm[4], type);
            SS_setChart(fsm[4], color);
            SS_setVertex(fsm[4], 0, v02);
            SS_setVertex(fsm[4], 1, v13);
            SS_setVertex(fsm[4], 2, v01);
            SS_setVertex(fsm[4], 3, v12);
            SS_setFaceType(fsm[4], 0, 0);
            SS_setFaceType(fsm[4], 1, fType[3]);
            SS_setFaceType(fsm[4], 2, 0);
            SS_setFaceType(fsm[4], 3, 0);
            SS_buildRing(fsm[4]);

           /*
            * ****************************************************************
            * second tetrahedron of the inner-diamond
            * (vertex order of:  v13,v02,v23,v12)
            * ****************************************************************
            */
            fsm[5] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[5], reality);
            SS_setClass(fsm[5], class);
            SS_setType(fsm[5], type);
            SS_setChart(fsm[5], color);
            SS_setVertex(fsm[5], 0, v13);
            SS_setVertex(fsm[5], 1, v02);
            SS_setVertex(fsm[5], 2, v23);
            SS_setVertex(fsm[5], 3, v12);
            SS_setFaceType(fsm[5], 0, 0);
            SS_setFaceType(fsm[5], 1, fType[0]);
            SS_setFaceType(fsm[5], 2, 0);
            SS_setFaceType(fsm[5], 3, 0);
            SS_buildRing(fsm[5]);

           /*
            * ****************************************************************
            * third tetrahedron of the inner-diamond
            * (vertex order of:  v02,v13,v23,v03)
            * ****************************************************************
            */
            fsm[6] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[6], reality);
            SS_setClass(fsm[6], class);
            SS_setType(fsm[6], type);
            SS_setChart(fsm[6], color);
            SS_setVertex(fsm[6], 0, v02);
            SS_setVertex(fsm[6], 1, v13);
            SS_setVertex(fsm[6], 2, v23);
            SS_setVertex(fsm[6], 3, v03);
            SS_setFaceType(fsm[6], 0, 0);
            SS_setFaceType(fsm[6], 1, fType[1]);
            SS_setFaceType(fsm[6], 2, 0);
            SS_setFaceType(fsm[6], 3, 0);
            SS_buildRing(fsm[6]);

           /*
            * ****************************************************************
            * fourth tetrahedron of the inner-diamond
            * (vertex order of:  v13,v02,v01,v03)
            * ****************************************************************
            */
            fsm[7] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[7], reality);
            SS_setClass(fsm[7], class);
            SS_setType(fsm[7], type);
            SS_setChart(fsm[7], color);
            SS_setVertex(fsm[7], 0, v13);
            SS_setVertex(fsm[7], 1, v02);
            SS_setVertex(fsm[7], 2, v01);
            SS_setVertex(fsm[7], 3, v03);
            SS_setFaceType(fsm[7], 0, 0);
            SS_setFaceType(fsm[7], 1, fType[2]);
            SS_setFaceType(fsm[7], 2, 0);
            SS_setFaceType(fsm[7], 3, 0);
            SS_buildRing(fsm[7]);

        } else if (interior == 2) {  /* v03-v12 */

           /*
            * ****************************************************************
            * first tetrahedron of the inner-diamond
            * (vertex order of:  v03,v12,v23,v13)
            * ****************************************************************
            */
            fsm[4] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[4], reality);
            SS_setClass(fsm[4], class);
            SS_setType(fsm[4], type);
            SS_setChart(fsm[4], color);
            SS_setVertex(fsm[4], 0, v03);
            SS_setVertex(fsm[4], 1, v12);
            SS_setVertex(fsm[4], 2, v23);
            SS_setVertex(fsm[4], 3, v13);
            SS_setFaceType(fsm[4], 0, fType[0]);
            SS_setFaceType(fsm[4], 1, 0);
            SS_setFaceType(fsm[4], 2, 0);
            SS_setFaceType(fsm[4], 3, 0);
            SS_buildRing(fsm[4]);

           /*
            * ****************************************************************
            * second tetrahedron of the inner-diamond
            * (vertex order of:  v12,v03,v01,v13)
            * ****************************************************************
            */
            fsm[5] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[5], reality);
            SS_setClass(fsm[5], class);
            SS_setType(fsm[5], type);
            SS_setChart(fsm[5], color);
            SS_setVertex(fsm[5], 0, v12);
            SS_setVertex(fsm[5], 1, v03);
            SS_setVertex(fsm[5], 2, v01);
            SS_setVertex(fsm[5], 3, v13);
            SS_setFaceType(fsm[5], 0, fType[2]);
            SS_setFaceType(fsm[5], 1, 0);
            SS_setFaceType(fsm[5], 2, 0);
            SS_setFaceType(fsm[5], 3, 0);
            SS_buildRing(fsm[5]);

           /*
            * ****************************************************************
            * third tetrahedron of the inner-diamond
            * (vertex order of:  v03,v12,v01,v02)
            * ****************************************************************
            */
            fsm[6] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[6], reality);
            SS_setClass(fsm[6], class);
            SS_setType(fsm[6], type);
            SS_setChart(fsm[6], color);
            SS_setVertex(fsm[6], 0, v03);
            SS_setVertex(fsm[6], 1, v12);
            SS_setVertex(fsm[6], 2, v01);
            SS_setVertex(fsm[6], 3, v02);
            SS_setFaceType(fsm[6], 0, fType[3]);
            SS_setFaceType(fsm[6], 1, 0);
            SS_setFaceType(fsm[6], 2, 0);
            SS_setFaceType(fsm[6], 3, 0);
            SS_buildRing(fsm[6]);

           /*
            * ****************************************************************
            * fourth tetrahedron of the inner-diamond
            * (vertex order of:  v12,v03,v23,v02)
            * ****************************************************************
            */
            fsm[7] = Gem_createAndInitSS( thee );
            SS_setReality(fsm[7], reality);
            SS_setClass(fsm[7], class);
            SS_setType(fsm[7], type);
            SS_setChart(fsm[7], color);
            SS_setVertex(fsm[7], 0, v12);
            SS_setVertex(fsm[7], 1, v03);
            SS_setVertex(fsm[7], 2, v23);
            SS_setVertex(fsm[7], 3, v02);
            SS_setFaceType(fsm[7], 0, fType[1]);
            SS_setFaceType(fsm[7], 1, 0);
            SS_setFaceType(fsm[7], 2, 0);
            SS_setFaceType(fsm[7], 3, 0);
            SS_buildRing(fsm[7]);

        } else Vnm_print(0, "Gem_octsect: Problem.\n");
    }

   /*
    * ************************************************************************
    * construct the child refinement markings
    * ************************************************************************
    */

    numKids = 4 * (Gem_dim(thee)-1);
    for (i=0; i<numKids; i++) {
        lEdge = Gem_longestEdge(thee,fsm[i],-1,&len); /* get refinement edge */
        SS_setRefinementEdge(fsm[i],lEdge);        /* store refinement edge */
    }

   /*
    * ************************************************************************
    * boundary face types and counts
    * ************************************************************************
    */

    /* if an old face was boundary face, we be adding one or three more */
    newFaces = 1;
    if (Gem_dim(thee)==3) newFaces = 3;
    if ( VBOUNDARY(fType[0]) ) Gem_addToNumBF(thee, newFaces);
    if ( VBOUNDARY(fType[1]) ) Gem_addToNumBF(thee, newFaces);
    if ( VBOUNDARY(fType[2]) ) Gem_addToNumBF(thee, newFaces);
    if ( VBOUNDARY(fType[3]) ) Gem_addToNumBF(thee, newFaces);

   /*
    * ************************************************************************
    * See if my refCount>1 so children should be refined.
    * See if new children are non-conforming; if so, mark them for refinement.
    * Note that if we are only creating edges on the fly when we need to
    * refine an edge, then the children should NEVER have a non-VNULL edge.
    * Thus, a child would be non-conforming simply if an edge existed.
    * This is the procedure that the loop below currently implements.
    *
    * NOTE: If we want to allow for the edges to live at all times, a child 
    *       would only be non-conforming if one of its edges had a midpoint
    *       (a hanging node) meaning that the edge had been refined.
    *       The loop below DOES NOT currently handle this case; we are
    *       assuming lazy edge created -- edges are only created if they
    *       are being refined.
    * ************************************************************************
    */
    for (i=0; i<numKids; i++) {
        badKids = 0;
        for (k=1; k<Gem_dimVV(thee); k++)
            for (j=0; j<k; j++)
                if (SS_edge(fsm[i],j,k) != VNULL) badKids++;
        if ((badKids > 0) || (refCount > 0)) {
            Gem_appendSQ(thee, !currentQ, fsm[i]); /* add child to ref !Q */
            SS_setRefineKey(fsm[i],!currentQ,1);   /* note child is on !Q */
            SS_setRefinementCount( fsm[i], VMAX2(1,refCount) ); /* refs todo*/
        }
    }

    /* Hook for external structure updating */
    if (thee->xUpFlag) thee->xUp(fsm, numKids);
}

/*
 * ***************************************************************************
 * Routine:  Gem_bisectLE
 *
 * Purpose:  Bisection refinement of a single simplex by longest edge.
 *
 * Notes:    Boundary nodes/edges[faces] are correctly refined.
 *
 *           "Face Type rule": Boundary faces rule over Interior faces.
 *
 *           In other words, if an edge is shared between a boundary face and
 *           an interior face, and the edge gets refined, the new point will
 *           be a boundary point.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_bisectLE(Gem *thee, SS *sm, int currentQ)
{
    int i, j, k, canon, refCount, fType[4], numKids, badKids;
    int reality, class, type, color, lEdge;
    double len;
    VV *v[4], *v01 = VNULL;
    SS *fsm[2];

   /*
    * ************************************************************************
    * first we check for logical consistency...
    * ************************************************************************
    */
    VASSERT( SS_refineKey(sm,currentQ) );

   /*
    * ************************************************************************
    * setup a "canonical" bisection
    * ************************************************************************
    */

    /* HACK: need to re-compute longest edge due to possible point movement */
    /*       that can happen with mesh smoothing.  If we don't do this, then*/
    /*       a situation can arise in which two tets which share a face may */
    /*       try to bisect that face using different edges; this is *never* */
    /*       recoverable, and we WILL end up with a non-conforming mesh.    */
    /* canon = SS_refinementEdge(sm); */
    canon = Gem_longestEdge(thee,sm,-1,&len);
    refCount = SS_refinementCount(sm);
    VASSERT( refCount >= 1 );
    refCount--;

   /*
    * ************************************************************************
    * get vertices for the canonical bisection; other setup
    * ************************************************************************
    */

    /* initialize and get simplices' vertices and its face types */
    for (i=0; i<2; i++)
        fsm[i] = VNULL;
    for (i=0; i<4; i++) {
        v[i] = VNULL;
        fType[i] = SS_faceType( sm, vmapV[canon][i] );
    }
    for (i=0; i<Gem_dimVV(thee); i++)
        v[i] = SS_vertex( sm, vmapV[canon][i] );

    /* get various attibutes of parent that children should inherit */
    reality = SS_reality(sm);  /* we must force inheritance here */
    class   = SS_class(sm);    /* we must force inheritance here */
    type    = SS_type(sm);     /* we must force inheritance here */
    color   = SS_chart(sm);    /* we must force inheritance here */

   /*
    * ************************************************************************
    * refine the simplex by refining edge v0-v1, producing point v01
    * ************************************************************************
    */

    Gem_refineEdge(thee, currentQ, sm, v, &v01, 0,1);

   /*
    * ************************************************************************
    * remove simplex from simplex rings, re-init for reuse as first child
    * ************************************************************************
    */

    SS_meltRing(sm);
    SS_reinit(sm);

   /*
    * ************************************************************************
    * first simplex -- new v01 plays the role of the old v1
    * ************************************************************************
    */

    fsm[0] = sm; /* first child re-uses the parent simplex */
    SS_setReality(fsm[0], reality);
    SS_setClass(fsm[0], class);
    SS_setType(fsm[0], type);
    SS_setChart(fsm[0], color);
    SS_setVertex(fsm[0], 0, v[0]);
    SS_setVertex(fsm[0], 1, v01);
    SS_setVertex(fsm[0], 2, v[2]);
    SS_setFaceType(fsm[0], 0, 0);
    SS_setFaceType(fsm[0], 1, fType[1]);
    SS_setFaceType(fsm[0], 2, fType[2]);
    if (Gem_dim(thee)==3) {
        SS_setVertex(fsm[0], 3, v[3]);
        SS_setFaceType(fsm[0], 3, fType[3]);
    }
    SS_buildRing(fsm[0]);

   /*
    * ************************************************************************
    * second simplex -- new v01 plays the role of the old v0
    * ************************************************************************
    */

    fsm[1] = Gem_createAndInitSS(thee); /* 2nd child gets new simp */
    SS_setReality(fsm[1], reality);
    SS_setClass(fsm[1], class);
    SS_setType(fsm[1], type);
    SS_setChart(fsm[1], color);
    SS_setVertex(fsm[1], 0, v[1]);
    SS_setVertex(fsm[1], 1, v[2]);
    SS_setVertex(fsm[1], 2, v01);
    SS_setFaceType(fsm[1], 0, 0);
    SS_setFaceType(fsm[1], 1, fType[2]);
    SS_setFaceType(fsm[1], 2, fType[0]);
    if (Gem_dim(thee)==3) {
        SS_setVertex(fsm[1], 3, v[3]);
        SS_setFaceType(fsm[1], 3, fType[3]);
    }
    SS_buildRing(fsm[1]);

   /*
    * ************************************************************************
    * construct the child refinement markings
    * ************************************************************************
    */

    numKids = 2;
    for (i=0; i<numKids; i++) {
        lEdge = Gem_longestEdge(thee,fsm[i],-1,&len); /* get refinement edge */
        SS_setRefinementEdge(fsm[i],lEdge);        /* store refinement edge */
    }

   /*
    * ************************************************************************
    * boundary face types and counts
    * ************************************************************************
    */

    /* If old face[2], face[3] boundary, add a boundary face */
    if ( VBOUNDARY(fType[2]) ) Gem_numBFpp(thee);
    if ( VBOUNDARY(fType[3]) ) Gem_numBFpp(thee); /* No 2D effect */

   /*
    * ************************************************************************
    * See if my refCount>1 so children should be refined.
    * See if new children are non-conforming; if so, mark them for refinement.
    * Note that if we are only creating edges on the fly when we need to
    * refine an edge, then the children should NEVER have a non-VNULL edge.
    * Thus, a child would be non-conforming simply if an edge existed.
    * This is the procedure that the loop below currently implements.
    *
    * NOTE: If we want to allow for the edges to live at all times, a child 
    *       would only be non-conforming if one of its edges had a midpoint
    *       (a hanging node) meaning that the edge had been refined.
    *       The loop below DOES NOT currently handle this case; we are
    *       assuming lazy edge created -- edges are only created if they
    *       are being refined.
    * ************************************************************************
    */
    for (i=0; i<numKids; i++) {
        badKids = 0;
        for (k=1; k<Gem_dimVV(thee); k++)
            for (j=0; j<k; j++)
                if (SS_edge(fsm[i],j,k) != VNULL) badKids++;
        if ((badKids > 0) || (refCount > 0)) {
            Gem_appendSQ(thee, !currentQ, fsm[i]); /* add child to ref !Q */
            SS_setRefineKey(fsm[i],!currentQ,1);   /* note child is on !Q */
            SS_setRefinementCount( fsm[i], VMAX2(1,refCount) ); /* refs todo*/
        }
    }

    /* Hook for external structure updating */
    if (thee->xUpFlag) thee->xUp(fsm, numKids);
}

/*
 * ***************************************************************************
 * Routine:  Gem_bisectNV
 *
 * Purpose:  Bisection refinement of a single simplex by newest vertex.
 *
 * Notes:    Boundary nodes/edges[faces] are correctly refined.
 *
 *           "Face Type rule": Boundary faces rule over Interior faces.
 *
 *           In other words, if an edge is shared between a boundary face and
 *           an interior face, and the edge gets refined, the new point will
 *           be a boundary point.
 *
 *           We use "newest vertex" approach to selecting the refinement edge
 *           choice generated by the Arnold-Mukherjee marking procedure.
 *           Below is a mathematica program that demonstrates the marking
 *           algorithm, courtesy of Doug Arnold and Arup Mukerjee.
 *
 *    (* -- BEGIN MATHEMATICA CODE ----------------------------------------- *)
 *    (*
 *     * NOTE: The following mathematica program, courtesy of doug arnold
 *     * and arup mukherjee, illustrates their particular edge choice,
 *     * which is provably non-degenerate.  The small comment at the
 *     * beginning, just following my comment here, is from Arup.
 *     * We implement their marking procedure in MC with our MC geometry
 *     * datastructures (as an alternative to longest edge choice) by 
 *     * allocating a few bits to indicate both the marked edges on each face
 *     * and then the refinement edge choice.  -mike
 *     *)
 *    (*
 *     * Arup's Comment:  I am also including a mathematica script for the 
 *     * bisection.  Given a tet and its "type" it does the bisection upto a 
 *     * required bisection level and lists the total number of similarity 
 *     * classes produced in the process (it uses a Liu-Joe indicator given on
 *     * one of their papers ... the example at the end of Chap 3 in the 
 *     * thesis has the specific reference on this). The tetrahedron specified
 *     * in the example attains the upper bound of 36 similarity classes.
 *     *)
 *    
 *    (* SET the value of nlevels (number of bisection levels)
 *    and the TYPE of t[0] p-uf, p-f, np-aa, etc ...
 *     before input
 *    to mathematica *)
 *    
 *    nlevels=8
 *    
 *    SetAttributes[bisect,Listable]
 *    (* these are the "bisection" rules 
 *      p-uf -- planar with flag off 
 *        v0-v1 is refinement edge and v0-v2 and v1-v2 are marked edges
 *          the plane containing all marked edges is v0 v1 v2
 *      p-f -- planar with flag on 
 *        v0-v1 is refinement edge and v0-v2 and v1-v2 are marked edges
 *          the plane containing all marked edges is v0 v1 v2
 *      np-aa -- non planar case with adjacent markings
 *        v0-v1 is refinement edge and v0-v2 and v1-v3 are marked edges 
 *      np-oo -- opp-opp  
 *        v0-v1 is refinement edge and v2-v3 is the other marked edge
 *      np-ao -- adj-opp
 *        v0-v1 is the refinement edge and v0-v2 and v2-v3 are marked
 *    *)
 *    
 *    bisect[Tetra[v0_,v1_,v2_,v3_,p-uf]]:= {
 *        Tetra[v0,v2,v3,(v0+v1)/2,p-f], Tetra[v1,v2,v3,(v0+v1)/2,p-f]  }
 *    
 *    bisect[Tetra[v0_,v1_,v2_,v3_,p-f]]:= {
 *        Tetra[v0,v2,v3,(v0+v1)/2,np-aa], Tetra[v1,v2,v3,(v0+v1)/2,np-aa] }
 *    
 *    bisect[Tetra[v0_,v1_,v2_,v3_,np-aa]]:={
 *        Tetra[v0,v2,v3,(v0+v1)/2,p-uf], Tetra[v1,v3,v2,(v0+v1)/2,p-uf] }
 *    
 *    bisect[Tetra[v0_,v1_,v2_,v3_,np-oo]]:={
 *        Tetra[v2,v3,v0,(v0+v1)/2,p-uf], Tetra[v2,v3,v1,(v0+v1)/2,p-uf] }
 *    
 *    bisect[Tetra[v0_,v1_,v2_,v3_,np-ao]]:={
 *        Tetra[v0,v2,v3,(v0+v1)/2,p-uf], Tetra[v2,v3,v1,(v0+v1)/2,p-uf] }
 *    
 *    (* a "generic" tetrahedron *)
 *    v0={0,0,0};
 *    v1={23,0,0};
 *    v2={7,0,11};
 *    v3={17,5,13};
 *    
 *    Clear[t]
 *    (* set t[0] to be pf, pt, or np-** as the case may be *)
 *    t[0]={Tetra[v0,v1,v2,v3,p-uf]};
 *    t[n_]:=t[n]=bisect[t[n-1]]
 *    
 *    (* The Liu-Joe quality indicator *)
 *    dist2[v0_,v1_] := (v0-v1).(v0-v1)
 *    dist[v0_,v1_] := Sqrt[dist[v0,v1]]
 *    SetAttributes[qual,Listable]
 *    qual[Tetra[v0_,v1_,v2_,v3_,any_]] :=
 *    12 Abs[Det[{v1-v0,v2-v0,v3-v0}]/2]^(2/3)/
 *    (dist2[v0,v1]+dist2[v0,v2]+dist2[v0,v3]
 *    +dist2[v1,v2]+dist2[v1,v3]+dist2[v2,v3])
 *    
 *    (* discretized Liu-Joe quality indicator *)
 *    (* (scaled to [0,100000] and rounded to an integer *)
 *    SetAttributes[dqual,Listable]
 *    dqual[t_] := Round[100000 N[qual[t],10]]
 *    
 *    (* q[i] --- list of qualities for level i
 *       qq[i] -- list of all qualities upto level i
 *       newout[i] -- the "number" of different similarity classes at 
 *                    level i
 *       totout[i] -- the "number" of different similarity classes at
 *                    or below level i    *)
 *    Do[q[i]=dqual[t[i]],{i,0,nlevels}]
 *    Do[qq[i]= Union@@Table[q[j],{j,0,i}],{i,0,nlevels}]
 *    Do[newout[i]=Dimensions[Union[Flatten[q[i]]]],{i,0,nlevels}]
 *    Do[totout[i]=Dimensions[Union[Flatten[qq[i]]]],{i,0,nlevels}]
 *    Table[{i,newout[i],totout[i]},{i,0,nlevels}]//TableForm
 *    (* -- END   MATHEMATICA CODE ---------------------------------------- *)
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_bisectNV(Gem *thee, SS *sm, int currentQ)
{
    int i, j, k, canon, refCount, fType[4], numKids, badKids;
    int reality, class, type, color, lEdge, origVertCnt;
    double len;
    VV *v[4], *v01 = VNULL;
    SS *fsm[2];

   /*
    * ************************************************************************
    * first we check for logical consistency...
    * ************************************************************************
    */
    VASSERT( SS_refineKey(sm,currentQ) );

   /*
    * ************************************************************************
    * setup a "canonical" bisection
    * ************************************************************************
    */

    canon = SS_refinementEdge(sm);
    refCount = SS_refinementCount(sm);
    VASSERT( refCount >= 1 );
    refCount--;

   /*
    * ************************************************************************
    * get vertices for the canonical bisection; other setup
    * ************************************************************************
    */

    /* initialize and get simplices' vertices and its face types */
    for (i=0; i<2; i++)
        fsm[i] = VNULL;
    for (i=0; i<4; i++) {
        v[i] = VNULL;
        fType[i] = SS_faceType( sm, vmapV[canon][i] );
    }
    for (i=0; i<Gem_dimVV(thee); i++)
        v[i] = SS_vertex( sm, vmapV[canon][i] );

    /* get various attibutes of parent that children should inherit */
    reality = SS_reality(sm);  /* we must force inheritance here */
    class   = SS_class(sm);    /* we must force inheritance here */
    type    = SS_type(sm);     /* we must force inheritance here */
    color   = SS_chart(sm);    /* we must force inheritance here */

   /*
    * ************************************************************************
    * refine the simplex by refining edge v0-v1, producing point v01
    * ************************************************************************
    */

    Gem_refineEdge(thee, currentQ, sm, v, &v01, 0,1);

   /*
    * ************************************************************************
    * remove simplex from simplex rings, re-init for reuse as first child
    * ************************************************************************
    */

    SS_meltRing(sm);
    SS_reinit(sm);

   /*
    * ************************************************************************
    * first simplex -- new v01 plays the role of the old v1
    * ************************************************************************
    */

    fsm[0] = sm; /* first child re-uses the parent simplex */
    SS_setReality(fsm[0], reality);
    SS_setClass(fsm[0], class);
    SS_setType(fsm[0], type);
    SS_setChart(fsm[0], color);
    SS_setVertex(fsm[0], 0, v[0]);
    SS_setVertex(fsm[0], 1, v01);
    SS_setVertex(fsm[0], 2, v[2]);
    SS_setFaceType(fsm[0], 0, 0);
    SS_setFaceType(fsm[0], 1, fType[1]);
    SS_setFaceType(fsm[0], 2, fType[2]);
    if (Gem_dim(thee)==3) {
        SS_setVertex(fsm[0], 3, v[3]);
        SS_setFaceType(fsm[0], 3, fType[3]);
    }
    SS_buildRing(fsm[0]);

   /*
    * ************************************************************************
    * second simplex -- new v01 plays the role of the old v0
    * ************************************************************************
    */

    fsm[1] = Gem_createAndInitSS(thee); /* 2nd child gets new simp */
    SS_setReality(fsm[1], reality);
    SS_setClass(fsm[1], class);
    SS_setType(fsm[1], type);
    SS_setChart(fsm[1], color);
    SS_setVertex(fsm[1], 0, v[1]);
    SS_setVertex(fsm[1], 1, v[2]);
    SS_setVertex(fsm[1], 2, v01);
    SS_setFaceType(fsm[1], 0, 0);
    SS_setFaceType(fsm[1], 1, fType[2]);
    SS_setFaceType(fsm[1], 2, fType[0]);
    if (Gem_dim(thee)==3) {
        SS_setVertex(fsm[1], 3, v[3]);
        SS_setFaceType(fsm[1], 3, fType[3]);
    }
    SS_buildRing(fsm[1]);

   /*
    * ************************************************************************
    * construct the child refinement markings
    * ************************************************************************
    */

    numKids = 2;
    for (i=0; i<numKids; i++) {
        origVertCnt = 0;
        for (j=0; j<Gem_dimVV(thee); j++) {
            if ( VV_id( SS_vertex( fsm[i], j ) ) < thee->numVV0) {
                origVertCnt++;
            }
        }
        if (origVertCnt > 0) {
            lEdge = Gem_longestEdge(thee,fsm[i],-1,&len); /* get ref edge */
        } else {
            lEdge = Gem_newestVertex(thee,fsm[i],-1,&len); /* get ref edge */
        }
        SS_setRefinementEdge(fsm[i],lEdge);        /* store ref edge */
    }

   /*
    * ************************************************************************
    * boundary face types and counts
    * ************************************************************************
    */

    /* If old face[2], face[3] boundary, add a boundary face */
    if ( VBOUNDARY(fType[2]) ) Gem_numBFpp(thee);
    if ( VBOUNDARY(fType[3]) ) Gem_numBFpp(thee); /* No 2D effect */

   /*
    * ************************************************************************
    * See if my refCount>1 so children should be refined.
    * See if new children are non-conforming; if so, mark them for refinement.
    * Note that if we are only creating edges on the fly when we need to
    * refine an edge, then the children should NEVER have a non-VNULL edge.
    * Thus, a child would be non-conforming simply if an edge existed.
    * This is the procedure that the loop below currently implements.
    *
    * NOTE: If we want to allow for the edges to live at all times, a child 
    *       would only be non-conforming if one of its edges had a midpoint
    *       (a hanging node) meaning that the edge had been refined.
    *       The loop below DOES NOT currently handle this case; we are
    *       assuming lazy edge created -- edges are only created if they
    *       are being refined.
    * ************************************************************************
    */
    for (i=0; i<numKids; i++) {
        badKids = 0;
        for (k=1; k<Gem_dimVV(thee); k++)
            for (j=0; j<k; j++)
                if (SS_edge(fsm[i],j,k) != VNULL) badKids++;
        if ((badKids > 0) || (refCount > 0)) {
            Gem_appendSQ(thee, !currentQ, fsm[i]); /* add child to ref !Q */
            SS_setRefineKey(fsm[i],!currentQ,1);   /* note child is on !Q */
            SS_setRefinementCount( fsm[i], VMAX2(1,refCount) ); /* refs todo*/
        }
    }

    /* Hook for external structure updating */
    if (thee->xUpFlag) thee->xUp(fsm, numKids);
}

/*
 * ***************************************************************************
 * Routine:  Gem_bisectNP
 *
 * Purpose:  Bisection refinement by pairs.
 *
 * Notes:    Boundary nodes/edges[faces] are correctly refined.
 *
 *           "Face Type rule": Boundary faces rule over Interior faces.
 *
 *           In other words, if an edge is shared between a boundary face and
 *           an interior face, and the edge gets refined, the new point will
 *           be a boundary point.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_bisectNP(Gem *thee, SS *sm, int currentQ)
{
    int i, j, k, canon, refCount, fType[4], numKids, badKids;
    int reality, class, type, color, lEdge;
    double len;
    VV *v[4], *v01 = VNULL;
    SS *fsm[2];

   /*
    * ************************************************************************
    * first we check for logical consistency...
    * ************************************************************************
    */
    VASSERT( SS_refineKey(sm,currentQ) );

   /*
    * ************************************************************************
    * setup a "canonical" bisection
    * ************************************************************************
    */

    canon = SS_refinementEdge(sm);
    refCount = SS_refinementCount(sm);
    VASSERT( refCount >= 1 );
    refCount--;

   /*
    * ************************************************************************
    * get vertices for the canonical bisection; other setup
    * ************************************************************************
    */

    /* initialize and get simplices' vertices and its face types */
    for (i=0; i<2; i++)
        fsm[i] = VNULL;
    for (i=0; i<4; i++) {
        v[i] = VNULL;
        fType[i] = SS_faceType( sm, vmapV[canon][i] );
    }
    for (i=0; i<Gem_dimVV(thee); i++)
        v[i] = SS_vertex( sm, vmapV[canon][i] );

    /* get various attibutes of parent that children should inherit */
    reality = SS_reality(sm);  /* we must force inheritance here */
    class   = SS_class(sm);    /* we must force inheritance here */
    type    = SS_type(sm);     /* we must force inheritance here */
    color   = SS_chart(sm);    /* we must force inheritance here */

   /*
    * ************************************************************************
    * refine the simplex by refining edge v0-v1, producing point v01
    * ************************************************************************
    */

    Gem_refineEdge(thee, currentQ, sm, v, &v01, 0,1);

   /*
    * ************************************************************************
    * remove simplex from simplex rings, re-init for reuse as first child
    * ************************************************************************
    */

    SS_meltRing(sm);
    SS_reinit(sm);

   /*
    * ************************************************************************
    * first simplex -- new v01 plays the role of the old v1
    * ************************************************************************
    */

    fsm[0] = sm; /* first child re-uses the parent simplex */
    SS_setReality(fsm[0], reality);
    SS_setClass(fsm[0], class);
    SS_setType(fsm[0], type);
    SS_setChart(fsm[0], color);
    SS_setVertex(fsm[0], 0, v[0]);
    SS_setVertex(fsm[0], 1, v01);
    SS_setVertex(fsm[0], 2, v[2]);
    SS_setFaceType(fsm[0], 0, 0);
    SS_setFaceType(fsm[0], 1, fType[1]);
    SS_setFaceType(fsm[0], 2, fType[2]);
    if (Gem_dim(thee)==3) {
        SS_setVertex(fsm[0], 3, v[3]);
        SS_setFaceType(fsm[0], 3, fType[3]);
    }
    SS_buildRing(fsm[0]);

   /*
    * ************************************************************************
    * second simplex -- new v01 plays the role of the old v0
    * ************************************************************************
    */

    fsm[1] = Gem_createAndInitSS(thee); /* 2nd child gets new simp */
    SS_setReality(fsm[1], reality);
    SS_setClass(fsm[1], class);
    SS_setType(fsm[1], type);
    SS_setChart(fsm[1], color);
    SS_setVertex(fsm[1], 0, v[1]);
    SS_setVertex(fsm[1], 1, v[2]);
    SS_setVertex(fsm[1], 2, v01);
    SS_setFaceType(fsm[1], 0, 0);
    SS_setFaceType(fsm[1], 1, fType[2]);
    SS_setFaceType(fsm[1], 2, fType[0]);
    if (Gem_dim(thee)==3) {
        SS_setVertex(fsm[1], 3, v[3]);
        SS_setFaceType(fsm[1], 3, fType[3]);
    }
    SS_buildRing(fsm[1]);

   /*
    * ************************************************************************
    * construct the child refinement markings
    * ************************************************************************
    */

    numKids = 2;
    for (i=0; i<numKids; i++) {
        lEdge = Gem_newestVertex(thee,fsm[i],-1,&len); /* get refinement edge */
        SS_setRefinementEdge(fsm[i],lEdge);        /* store refinement edge */
    }

   /*
    * ************************************************************************
    * boundary face types and counts
    * ************************************************************************
    */

    /* If old face[2], face[3] boundary, add a boundary face */
    if ( VBOUNDARY(fType[2]) ) Gem_numBFpp(thee);
    if ( VBOUNDARY(fType[3]) ) Gem_numBFpp(thee); /* No 2D effect */

   /*
    * ************************************************************************
    * See if my refCount>1 so children should be refined.
    * See if new children are non-conforming; if so, mark them for refinement.
    * Note that if we are only creating edges on the fly when we need to
    * refine an edge, then the children should NEVER have a non-VNULL edge.
    * Thus, a child would be non-conforming simply if an edge existed.
    * This is the procedure that the loop below currently implements.
    *
    * NOTE: If we want to allow for the edges to live at all times, a child 
    *       would only be non-conforming if one of its edges had a midpoint
    *       (a hanging node) meaning that the edge had been refined.
    *       The loop below DOES NOT currently handle this case; we are
    *       assuming lazy edge created -- edges are only created if they
    *       are being refined.
    * ************************************************************************
    */
    for (i=0; i<numKids; i++) {
        badKids = 0;
        for (k=1; k<Gem_dimVV(thee); k++)
            for (j=0; j<k; j++)
                if (SS_edge(fsm[i],j,k) != VNULL) badKids++;
        if ((badKids > 0) || (refCount > 0)) {
            Gem_appendSQ(thee, !currentQ, fsm[i]); /* add child to ref !Q */
            SS_setRefineKey(fsm[i],!currentQ,1);   /* note child is on !Q */
            SS_setRefinementCount( fsm[i], VMAX2(1,refCount) ); /* refs todo*/
        }
    }

    /* Hook for external structure updating */
    if (thee->xUpFlag) thee->xUp(fsm, numKids);
}

