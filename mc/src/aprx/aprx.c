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
 * rcsid="$Id: aprx.c,v 1.29 2010/08/12 05:18:15 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     aprx.c
 *
 * Purpose:  Class Aprx: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "aprx_p.h"

VEMBED(rcsid="$Id: aprx.c,v 1.29 2010/08/12 05:18:15 fetk Exp $")

/*
 * ***************************************************************************
 * Class Aprx: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_APRX)
#endif /* if !defined(VINLINE_GEM) */

/*
 * ***************************************************************************
 * Class Aprx: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Aprx_ctor
 *
 * Purpose:  Construct a linear Approximation object
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Aprx* Aprx_ctor(Vmem *vmem, Gem *tgm, PDE *tpde)
{
   /* Create a linear approximation */
   return Aprx_ctor2(vmem,tgm,tpde,1);
}

/*
 * ***************************************************************************
 * Routine:  Aprx_ctor2
 *
 * Purpose:  Approximation object constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Aprx* Aprx_ctor2(Vmem *vmem, Gem *tgm, PDE *tpde,int order)
{
    int i;
    Aprx* thee = VNULL;

    thee = Vmem_malloc( VNULL, 1, sizeof(Aprx) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Aprx" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    VDEBUGIO("Aprx_ctor: CREATING object..");
    VDEBUGIO("..done.\n");

    thee->gm   = tgm;
    thee->pde  = tpde;

    thee->numB = PDE_vec(thee->pde);
    thee->lnkG = Vset_ctor( thee->vmem, "G", sizeof( Link ), VMAX_OBJECTS, 0 );

    thee->B    = VNULL;
    for (i=0; i<MAXV; i++) {
        thee->re[i]  = VNULL;
        thee->reB[i] = VNULL;
    }

    thee->wev  = VNULL;
    thee->P    = VNULL;

    thee->order = order;

    Aprx_reset(thee);

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_dtor
 *
 * Purpose:  Approximation object destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_dtor(Aprx **thee)
{
    int i;

    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        if ((*thee)->lnkG != VNULL) {
            Vset_dtor( &((*thee)->lnkG) );
        }

        if ((*thee)->P != VNULL) {
            Bmat_dtor( &((*thee)->P) );
        }

        if ((*thee)->B != VNULL) {
            Bnode_dtor( &((*thee)->B) );
        }
        for (i=0; i<(*thee)->numB; i++) {
            if ((*thee)->numBV[i] > 0) {
                Vmem_free( ((*thee)->vmem), (*thee)->numBV[i], sizeof(int),
                    (void**)&((*thee)->ibv[i]) );
                Vmem_free( ((*thee)->vmem), (*thee)->numBV[i], sizeof(double),
                    (void**)&((*thee)->bv[i]) );
            }
        }

        for (i=0; i<MAXV; i++) {
            if ((*thee)->re[i] != VNULL) {
                Re_dtor( &((*thee)->re[i]) );
            }
            if ((*thee)->reB[i] != VNULL) {
                Re_dtor( &((*thee)->reB[i]) );
            }
        }

        if ((*thee)->wev != VNULL) {
            Bvec_dtor( &((*thee)->wev) );
        }

        VDEBUGIO("Aprx_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Aprx), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_numB
 *
 * Purpose:  Return the number of blocks.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_numB(Aprx *thee)
{
    return thee->numB;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_P
 *
 * Purpose:  Return a pointer to the current prolongation matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Bmat *Aprx_P(Aprx *thee)
{
    return thee->P;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_read
 *
 * Purpose:  Read in the user-specified initial mesh given in the
 *           "MCSF" or "MCEF" format, and transform into our internal
 *           datastructures.
 *
 *           Do a little more than a "Gem_read", in that we also
 *           initialize the extrinsic and intrinsic spatial dimensions
 *           corresponding to the input mesh, and we also then build the
 *           reference elements.
 *
 * Notes:    See the documentation to Gem_read for a description of the
 *           mesh input data file format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_read(Aprx *thee, int key, Vio *sock)
{
    /* read in the mesh; return error if problems */
    if ( !Gem_read(thee->gm,key,sock) ) {
        return 0;
    }

    /* create node information for the mesh */
    Aprx_reset(thee);
    Aprx_buildNodes(thee);

    /* error-free return */
    return 1;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_reset
 *
 * Purpose:  Reset all of the datastructures.
 *
 * Author:   Michael Holst (updated by Ryan Szypowski)
 * ***************************************************************************
 */
VPUBLIC void Aprx_reset(Aprx *thee)
{
    int i;

    /* now reset some other things */
    if ( thee->P    != VNULL ) Bmat_dtor( &(thee->P) );
    if ( thee->B    != VNULL ) Bnode_dtor( &(thee->B) );
    thee->P = VNULL;
    thee->B = VNULL;

    Vset_reset( thee->lnkG );

    if (thee->I_V2E != VNULL) {
        Vmem_free(thee->vmem,2*(thee->numE),sizeof(int),(void**)&(thee->I_V2E));
    }
    if (thee->I_V2F != VNULL) {
        Vmem_free(thee->vmem,3*(thee->numF),sizeof(int),(void**)&(thee->I_V2F));
    }
    if (thee->I_V2S != VNULL) {
        Vmem_free(thee->vmem,4*(thee->numS),sizeof(int),(void**)&(thee->I_V2S));
    }
    if (thee->I_E2F != VNULL) {
        Vmem_free(thee->vmem,3*(thee->numF),sizeof(int),(void**)&(thee->I_E2F));
    }
    if (thee->I_E2S != VNULL) {
        Vmem_free(thee->vmem,6*(thee->numS),sizeof(int),(void**)&(thee->I_E2S));
    }
    if (thee->I_F2S != VNULL) {
        Vmem_free(thee->vmem,4*(thee->numS),sizeof(int),(void**)&(thee->I_F2S));
    }
    thee->numV = 0;
    thee->numE = 0;
    thee->numF = 0;
    thee->numS = 0;

    /* build new master elements for this mesh */
    for (i=0; i<thee->numB; i++) {
        if (thee->re[i] != VNULL) {
            Re_dtor( &(thee->re[i]) );
        }
        thee->re[i] = Re_ctor(0, PDE_dim(thee->pde),
            thee->pde->simplexBasisInit, thee->pde->simplexBasisForm,thee->order);
        if (thee->reB[i] != VNULL) {
            Re_dtor( &(thee->reB[i]) );
        }
	if (PDE_dim(thee->pde) == 3) {
	    /* Use cubic face bumps for 3d. */
            thee->reB[i] = Re_ctor(1, PDE_dim(thee->pde),
                thee->pde->simplexBasisInit, thee->pde->simplexBasisForm,3);
	}
	else {
            thee->reB[i] = Re_ctor(0, PDE_dim(thee->pde),
                thee->pde->simplexBasisInit, thee->pde->simplexBasisForm,thee->order);
	}
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_initNodes
 *
 * Purpose:  Make node information.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_initNodes(Aprx *thee)
{
    int i, j, jmx, jj, jj0, k, k1, k2, l, count, numR[MAXV];
    double fctr;
    aNode *nd;
    VV *vx, *vx1;
    SS *sm;
    Re *re;
    Gem *gm;

    /* some i/o */
    Vnm_print(0,"Aprx_initNodes: initializing node structures..");

    /* local pointers */
    gm = thee->gm;

    /* create the geometry map datastructures (empty) */
    thee->numV = Gem_numVirtVV(gm);
    thee->numE = Gem_numVirtEE(gm);
    thee->numF = Gem_numVirtFF(gm);
    thee->numS = Gem_numVirtSS(gm);
    thee->I_V2E = Vmem_malloc( thee->vmem, 2*(thee->numE), sizeof(int) );
    if (Gem_dim(gm) == 2) {
        thee->I_V2S = Vmem_malloc( thee->vmem, 3*(thee->numS), sizeof(int) );
        thee->I_E2S = Vmem_malloc( thee->vmem, 3*(thee->numS), sizeof(int) );
        thee->I_V2F = VNULL;
        thee->I_E2F = VNULL;
        thee->I_F2S = VNULL;
    } else if (Gem_dim(gm) == 3) {
        thee->I_V2S = Vmem_malloc( thee->vmem, 4*(thee->numS), sizeof(int) );
        thee->I_E2S = Vmem_malloc( thee->vmem, 6*(thee->numS), sizeof(int) );
        thee->I_V2F = Vmem_malloc( thee->vmem, 3*(thee->numF), sizeof(int) );
        thee->I_E2F = Vmem_malloc( thee->vmem, 3*(thee->numF), sizeof(int) );
        thee->I_F2S = Vmem_malloc( thee->vmem, 4*(thee->numS), sizeof(int) );
    } else { VASSERT(0); }

    /* create the Bnode object (destroy any existing one) */
    if (thee->B != VNULL) {
        Bnode_dtor( &(thee->B) );
    }
    for (i=0; i<thee->numB; i++) {
        re = thee->re[i];
        numR[i] = Re_numVDF(re)*Gem_numVV(gm)
                + Re_numEDF(re)*Gem_numVirtEE(gm)
                + Re_numFDF(re)*Gem_numVirtVV(gm)
                + Re_numSDF(re)*Gem_numSS(gm);
    }
    thee->B = Bnode_ctor(thee->vmem, thee->numB, numR);

    /* Now initialize the Bnode */
    count = 0;
    for (i=0; i<thee->numB; i++) {
        re = thee->re[i];
        nd = Bnode_data(thee->B,i);
        jmx = Re_numVDF(re)*Gem_numVV(gm);
        for (j=0; j<jmx; j++) {
            vx = Gem_VV(gm,j);
            nd[j].myid   = count;
            nd[j].myvert = j; /* VV_id(vx); */
            nd[j].type   = 0;
            nd[j].chart  = VV_chart(vx);
            nd[j].numx   = Gem_dimII(gm);
            nd[j].x[0]   = VV_coord(vx,0);
            nd[j].x[1]   = VV_coord(vx,1);
            nd[j].x[2]   = VV_coord(vx,2);
            nd[j].val    = 0.0;
            count++;
        }

#ifdef VG_ELEMENT
        /* Initialize edge degrees of freedom */
        if (Re_numEDF(re)>0) {
            jj0 = Re_numVDF(re)*Gem_numVirtVV(gm);
            for (j=0; j<Gem_numSS(gm); j++) {
                sm = Gem_SS(gm, j);
                /* run through the edges */
                for (k=0; k<Gem_dimEE(gm);k++) {
                    /* run through df on the edge */
                    for (l=0; l<Re_numEDF(re); l++) {
                        jj = l + Re_numEDF(re)*SS_edgeNumber(sm,k) + jj0;
                        if (nd[jj].numx != Gem_dimII(gm)) {
                            k1 = vmapEI[k][0];
                            k2 = vmapEI[k][1];
                            vx  = SS_vertex (sm, k1);
                            vx1 = SS_vertex (sm, k2);
                            nd[jj].myid = count;
                            nd[jj].myvert = jj;
                            nd[jj].type = 0;
                            nd[jj].chart  = 0;
                            nd[jj].numx   = Gem_dimII(gm);
                            fctr = (double)(l+1)/(double)(Re_numEDF(re)+1);
                            nd[jj].x[0]   = fctr * (VV_coord(vx,0)+VV_coord(vx1,0));
                            nd[jj].x[1]   = fctr * (VV_coord(vx,1)+VV_coord(vx1,1));
                            nd[jj].x[2]   = fctr * (VV_coord(vx,2)+VV_coord(vx1,2));
                            nd[jj].val    = 0.0;
                            count++;
                        }
                    } /* l */
                } /* k */
            } /* j */
        } /* if */
#endif

    }

    /* build new elements vectors for this mesh */
    if (thee->wev != VNULL) {
        Bvec_dtor( &(thee->wev) );
    }
    numR[0] = Gem_numSS(thee->gm);
    thee->wev = Bvec_ctor( thee->vmem, "wev", 1, numR );

    /* some i/o */
    Vnm_print(0,"..done.\n");
}

/*
 * ***************************************************************************
 * Routine:  Aprx_buildNodes
 *
 * Purpose:  Determine the node types via a single fast traversal of
 *           the elements by looking at the element faces.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_buildNodes(Aprx *thee)
{
    /* some variables */
    int i, j, k, l, ef, es, ii, kk, kk0, numEF;
    int vType, eType, fType, numBVD, vxid, count, chart;
    double UUd[MAXV], xm[3];
    SS *sm;
    VV *vx;
    Re *re;
    Gem *gm;

    /* initialization */
    Aprx_initNodes(thee);
    gm = thee->gm;

    /* some i/o */
    Vnm_print(0,"Aprx_buildNodes: determing node types from face types..");

    /* dirichlet node count in each block */
    for (ii=0; ii<thee->numB; ii++) {
        numBVD = 0;
        re = thee->re[ii];

        /* fly through the elements */
        for (i=0; i<Gem_numSS(gm); i++) {
            sm = Gem_SS(gm,i);

            /* fly through the faces of the element */
            for (j=0; j<Gem_dimVV(gm); j++) {

                /* here the user-defined boundary type remapping is used! */
                fType = thee->pde->bmap[ii][ SS_faceType(sm,j) ];

                /* if boundary face, apply type to vertices of the face */
                if (VBOUNDARY( fType )) {

#ifdef VG_ELEMENT
                    /* type edge degrees of freedom */
                    if (Re_numEDF(re)>0) {

                        /* compute number of edges for a simplex 1 dimension lower */
                        numEF = (Re_dimV(re)-1)*(Re_dimV(re)-2)/2;
                        kk0 = Re_numVDF(re) * Gem_numVirtVV(gm);

                        /* run through the edges of the face */
                        for (ef=0; ef<numEF; ef++) {

                            /* get edge number wrt simplex */
                            es = vmapFE[j][ef];

                            /* run through df on the edge */
                            for (l=0; l<Re_numEDF(re); l++) {
                                k = l + Re_numEDF(re)*SS_edgeNumber(sm,es) + kk0;
                                eType = Bnode_data(thee->B,ii)[k].type;

                                /* if face is dirichlet, type is "hard" */
                                if (VDIRICHLET( fType )) {

                                    /* is this a new dirichlet addition */
                                    if ( ! VDIRICHLET( eType ) ) {
                                        numBVD++;
                                    }

                                    /* type this edge */
                                    Bnode_data(thee->B,ii)[k].type = fType;

                                /* if face is neumann, type is "soft" */
                                } else if (VNEUMANN( fType )) {

                                    /* type this edge */
                                    if ( ! VDIRICHLET( eType ) ) {
                                        Bnode_data(thee->B,ii)[k].type = fType;
                                    }

                                } else { VASSERT(0); }
                            }  /* l */
                        } /* ef */
                    } /* if */
#endif

                    /* go through vertices of this face */
                    k=j;
                    for (kk=0; kk<Gem_dim(gm); kk++) {

                        /* get the vertex */
                        k=(k+1) % Gem_dimVV(gm);
                        vx = SS_vertex(sm,k);
                        vxid = VV_id(vx);
                        vType = Bnode_data(thee->B,ii)[vxid].type;

                        /* if face is dirichlet, type is "hard" */
                        if (VDIRICHLET( fType )) {

                            /* is this a new dirichlet addition */
                            if ( ! VDIRICHLET( vType ) ) {
                                numBVD++;
                            }

                            /* type this vertex */
                            Bnode_data(thee->B,ii)[vxid].type = fType;

                        /* if face is neumann, type is "soft" */
                        } else if (VNEUMANN( fType )) {

                            /* type this vertex */
                            if ( ! VDIRICHLET( vType ) ) {
                                Bnode_data(thee->B,ii)[vxid].type = fType;
                            }

                        } else { VASSERT(0); }
                    }
                }
            }
        }

        /* record node count, create space for dirichlet vertex list info */
        if (thee->ibv[ii] != VNULL) {
            Vmem_free(thee->vmem,
                thee->numBV[ii],sizeof(int),(void**)&(thee->ibv[ii]));
        }
        if (thee->bv[ii] != VNULL) {
            Vmem_free(thee->vmem,
                thee->numBV[ii],sizeof(double),(void**)&(thee->bv[ii]));
        }
        thee->numBV[ii] = numBVD;
        if (thee->numBV[ii] > 0) {
            thee->ibv[ii] = Vmem_malloc(thee->vmem,
                                thee->numBV[ii],sizeof(int));
            thee->bv[ii]  = Vmem_malloc(thee->vmem,
                                thee->numBV[ii],sizeof(double));
        } else {
            thee->ibv[ii] = VNULL;
            thee->bv[ii]  = VNULL;
        }
    }

    /* initalize dirichlet boundary vertex list */
    for (k=0; k<thee->numB; k++) {
        count = 0;
        for (i=0; i<Bnode_numR(thee->B,k); i++) {
            for (j=0; j<Bnode_data(thee->B,k)[i].numx; j++) {
                xm[j] = Bnode_data(thee->B,k)[i].x[j];
            }
            chart = Bnode_data(thee->B,k)[i].chart;
            vType = Bnode_data(thee->B,k)[i].type;
            thee->pde->u_D(thee->pde, vType, chart, xm, UUd);
            if (VDIRICHLET( Bnode_data(thee->B,k)[i].type )) {
                Bnode_data(thee->B,k)[i].val = UUd[k];
                thee->ibv[k][count] = i;
                thee->bv[k][count]  = UUd[k];
                count++;
            }
        }
        Vnm_print(0,"count = %d, thee->numBV[0] = %d\n", count, thee->numBV[k]);
        VASSERT( count == thee->numBV[k] );
    }

    /* some i/o */
    Vnm_print(0,"..done.\n");
}

/*
 * ***************************************************************************
 * Routine:  Aprx_evalTrace
 *
 * Purpose:  Evaluate the trace information.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_evalTrace(Aprx *thee, Bvec *Wud, Bvec *Wui, Bvec *Wut)
{
    /* some variables */
    int i, j, k, vType, count, chart;
    double UUd[MAXV], UUt[MAXV], dUUt[MAXV][3], xm[3];

    /* some i/o */
    Vnm_print(0,"Aprx_evalTrace: evaluating <Ud,Ui,Ut>..");

    /* initalize pde solution and dirichlet boundary vertex list */
    for (k=0; k<thee->numB; k++) {
        count = 0;
        for (i=0; i<Bnode_numR(thee->B,k); i++) {
            for (j=0; j<Bnode_data(thee->B,k)[i].numx; j++) {
                xm[j] = Bnode_data(thee->B,k)[i].x[j];
            }
            chart = Bnode_data(thee->B,k)[i].chart;
            vType = Bnode_data(thee->B,k)[i].type;
            thee->pde->u_D(thee->pde, vType, chart, xm, UUd);
            thee->pde->u_T(thee->pde, vType, chart, xm, UUt, dUUt);
            if (VDIRICHLET( Bnode_data(thee->B,k)[i].type )) {
                Bvec_setB( Wud, k, i, UUd[k] );
                Bvec_setB( Wui, k, i, 0. );
                Bvec_setB( Wut, k, i, 0. );
                count++;
            } else {
                Bvec_setB( Wud, k, i, 0. );
                Bvec_setB( Wui, k, i, UUd[k] );
                Bvec_setB( Wut, k, i, UUt[k] );
            }
        }
        VASSERT( count == thee->numBV[k] );
    }

    /* some i/o */
    Vnm_print(0,"..done.\n");
}

/*
 * ***************************************************************************
 * Routine:  Aprx_refine
 *
 * Purpose:  Refine the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_refine(Aprx *thee, int rkey, int bkey, int pkey)
{
    int numRc, numR, refined;

    /* number of vertices before refinement */
    numRc = Gem_numVV(thee->gm);

    /* call refinement */
    refined = Gem_refine(thee->gm, rkey, bkey, pkey);

    /* number of vertices after refinement */
    numR = Gem_numVV(thee->gm);

    /* use lazy edge creation to build a linear prolongation operator */
    Aprx_buildProlong(thee, numRc, numR, pkey);

    /* destroy lazy edges that we used to build prolongation operator */
    Gem_destroyEdges(thee->gm);

    /* count v/e/f/s and check the mesh */
    Gem_countChk(thee->gm);

    /* return */
    return refined;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_unRefine
 *
 * Purpose:  Unrefine the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_unRefine(Aprx *thee, int rkey, int pkey)
{
    int refined;

    /* call unrefinement */
    refined = Gem_unRefine(thee->gm, rkey, pkey);

    /* return */
    return refined;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_buildProlong
 *
 * Purpose:  Create storage for and build prolongation operator; the operator
 *           prolongates a vector FROM a coarser level TO this level.
 *
 * Notes:    This routine assumes the prolongation operator, P = [ I ],
 *           where I is the identity and R is the tail of P.     [ R ]
 *           For "single-refined" edges, the rows of R are
 *           zero, except for 1/2 in the columns corresponding to the
 *           parent vertices.  For a multiply refined edge, we just
 *           take a half-half linear combination of the parent rows.
 *           We first build R as an RLN, then copy it into P in ROW format.
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_buildProlong(Aprx *thee, int numRc, int numR, int pkey)
{
    int k, i, j0, j1, count, queuecount, multRefCount;
    int pnumR, pnumC, pnumP, ibase, *IJP;
    EE *eg;
    VV *v01, *v0, *v1;
    Mat *Pmat, *Rmat;
    LinkA *mt, *mt0, *mt1;

    Vnm_print(0,"Aprx_buildProlong: creating prolongation operator..");

    /* Determine dimensions of new prolongation operator */
    pnumR = numR;
    pnumC = numRc;
    ibase = (pkey) ? pnumC : 0;

    /* Construct a matrix for the tail of the new prolongation operator */
    Rmat = Mat_ctor( VNULL, "P", (pnumR-pnumC), pnumC );

    /* Initialize Rmat with the RLN format */
    Mat_initStructureLN( Rmat, RLN_FORMAT, ISNOT_SYM );

    /* STEP 1: Loop over split edges, filling in the entries of Rmat */
    count = 0;
    queuecount = 0;
    multRefCount = 0;
    for (k=0; k<Gem_numEE(thee->gm); k++) {
        eg = Gem_EE(thee->gm,k);

        /* Get the new vertex */
        v01 = EE_midPoint(eg);
        VASSERT( v01 != VNULL );
        i = VV_id(v01) - pnumC;
        VASSERT( i >= 0 );

        /* Get the parent vertices */
        v0 = EE_vertex(eg,0);
        j0 = VV_id(v0);
        v1 = EE_vertex(eg,1);
        j1 = VV_id(v1);

        /* Get the head of the current row */
        mt = (LinkA*)Vset_access(Rmat->lnkU,i);

        /* Have we already completed this row? */
        if( mt->idx < 0 ) {

            /* Case 1: Vertex v0 is old and Vertex v1 is old */
            if( (j0 < pnumC) && (j1 < pnumC) ) {
                mContrib( Rmat->lnkU, 1, &count, i, j0, 0.5 );
                mContrib( Rmat->lnkU, 1, &count, i, j1, 0.5 );
            }

            /* Case 2: Vertex v0 is new and Vertex v1 is old */
            if( (j0 >= pnumC) && (j1 < pnumC) ) {
                mt0 = (LinkA*)Vset_access(Rmat->lnkU,j0-pnumC);
                if( mt0->idx < 0  ) {
                    /* Parent row unresolved */
                    queuecount++;
                } else {
                    /* Parent row resolved */
                    multRefCount++;
                    mContrib( Rmat->lnkU, 1, &count, i, j1, 0.5 );
                    for (mt=mt0; mt!=VNULL; mt=mt->next) {
                        mContrib( Rmat->lnkU, 1, &count,
                                  i, mt->idx, 0.5*(mt->val) );
                    }
                }
            }

            /* Case 3: Vertex v0 is old and Vertex v1 is new */
            if( (j0 < pnumC) && (j1 >= pnumC) ) {
                mt1 = (LinkA*)Vset_access(Rmat->lnkU,j1-pnumC);
                if( mt1->idx < 0  ) {
                    /* Parent row unresolved */
                    queuecount++;
                } else {
                    /* Parent row resolved */
                    multRefCount++;
                    mContrib( Rmat->lnkU, 1, &count, i, j0, 0.5 );
                    for (mt=mt1; mt!=VNULL; mt=mt->next) {
                        mContrib( Rmat->lnkU, 1, &count,
                                  i, mt->idx, 0.5*(mt->val) );
                    }
                }
            }

            /* Case 4: Vertex v0 is new and Vertex v1 is new */
            if( (j0 >= pnumC) && (j1 >= pnumC) ) {
                mt0 = (LinkA*)Vset_access(Rmat->lnkU,j0-pnumC);
                mt1 = (LinkA*)Vset_access(Rmat->lnkU,j1-pnumC);
                if( mt0->idx < 0  || mt1->idx < 0 ) {
                    /* Parent row(s) unresolved */
                    queuecount += 2;
                } else {
                    /* Parent row(s) resolved */
                    multRefCount++;
                    for (mt=mt0; mt!=VNULL; mt=mt->next) {
                        mContrib( Rmat->lnkU, 1, &count,
                                  i, mt->idx, 0.5*(mt->val) );
                    }
                    multRefCount++;
                    for (mt=mt1; mt!=VNULL; mt=mt->next) {
                        mContrib( Rmat->lnkU, 1, &count,
                                  i, mt->idx, 0.5*(mt->val) );
                    }
                }
            }
        }
    }
    if (multRefCount > 0) {
        Vnm_print(0,"[RESOLVED MULTIPLY REFINED EDGES = <%d>]",multRefCount);
    }
    if (queuecount > 0) {
        /* ERROR: This should never happen if edges are processed in order! */
        Vnm_print(0,"[UNRESOLVED MULTIPLY REFINED EDGES = <%d>!]",queuecount);
        /* We could add a loop until queue is empty, but is not necessary? */
        VASSERT(0);
    }

    /* STEP 2: Construct Pmat from Rmat */
    Pmat = Mat_ctor( VNULL, "P", (pnumR-ibase), pnumC );

    /* create actual space for new prolongation operator */
    pnumP = (pnumC - ibase) + count;

    IJP = Vmem_malloc( Pmat->vmem, (pnumR-ibase)+1+pnumP, sizeof(int) );
    Mat_initStructure( Pmat, ROW_FORMAT, ISNOT_SYM, pnumP, IJP, VNULL );
    Mat_setState( Pmat, ASSEMBLED_STATE );
    if (pkey == 1) {
        Mat_setImpl( Pmat, IS_IMPL );
    }

    /* STEP 2A: Create the identity for the shared coarse and fine points */
    count = 0;
    Pmat->IA[count] = 0;
    for (i=0; i<(pnumC-ibase); i++) {
        Pmat->A[count] = 1.;
        Pmat->JA[count] = i;
        count++;
        Pmat->IA[i+1] = count;
    }

    /* STEP 2B: Copy Rmat (RLN) into P (ROW) */
    for (i=0; i<Rmat->numR; i++) {
        for (mt=(LinkA*)Vset_access(Rmat->lnkU,i); mt!=VNULL; mt=mt->next) {
            if( mt->idx >= 0 ) {
                Pmat->A[count]  = mt->val;
                Pmat->JA[count] = mt->idx;
                count++;
            }
        }
        Pmat->IA[(pnumC-ibase)+i+1] = count;
    }

    /* Clean-up: Destroy temporary Rmat */
    Mat_dtor( &Rmat );

    Vnm_print(0,"..done.\n");

    /* STEP 3: Convert to block version (also updates Bnode) */
    Aprx_buildProlongBmat(thee, Pmat);
    Mat_dtor( &Pmat );
}

/*
 * ***************************************************************************
 * Routine:  Aprx_buildProlongBmat
 *
 * Purpose:  Create block version of prolongation operator; also
 *           updates the Bnode object.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_buildProlongBmat(Aprx *thee, Mat *p)
{
    Bmat *bp;
    int i, j, numR[MAXV], numC[MAXV];
    MATmirror mirror[MAXV][MAXV];
    int numBR[MAXV], *BR[MAXV];
    int numBC[MAXV], *BC[MAXV];

    /* prolongation matrix structure check */
    VASSERT(p != VNULL);
    VASSERT( Mat_format(p) == ROW_FORMAT );

    /* setup mirror information */
    for (i=0; i<thee->numB; i++) {
        numR[i] = Mat_numR(p);
        numC[i] = Mat_numC(p);
        for (j=0; j<thee->numB; j++) {
            mirror[i][j] = ISNOT_MIRROR;
        }
    }

    /* copy old boundary node arrays while we still have them */
    for (i=0; i<thee->numB; i++) {
        numBC[i] = thee->numBV[i];
        if (numBC[i] > 0) {
            BC[i] = Vmem_malloc(thee->vmem,numBC[i],sizeof(int));
        }
        for (j=0; j<numBC[i]; j++) {
            BC[i][j] = thee->ibv[i][j];
        }
    }

    /* now build new nodes */
    Aprx_buildNodes(thee);

    /* now copy new boundary node arrays */
    for (i=0; i<thee->numB; i++) {
        numBR[i] = thee->numBV[i];
        if (numBR[i] > 0) {
            BR[i] = Vmem_malloc(thee->vmem,numBR[i],sizeof(int));
        }
        for (j=0; j<numBR[i]; j++) {
            BR[i][j] = thee->ibv[i][j];
        }
    }

    /* build new prolongation; keep pointer to old "coarse" prolongation */
    bp = Bmat_ctor( thee->vmem, "P", thee->numB, numR, numC, mirror );
    for (i=0; i<thee->numB; i++) {

        /* copy the nonzero structure */
        Mat_copyStructure( bp->AD[i][i], p );

        /* copy the nonzeros themselves and mark as assembled */
        for (j=0; j<p->numA; j++) {
            bp->AD[i][i]->A[j] = p->A[j];
        }
        Mat_setState( bp->AD[i][i], ASSEMBLED_STATE );

        /* apply any dirichlet node conditions */
        Mat_buildBRC(bp->AD[i][i], numBR[i], numBC[i], BR[i], BC[i]);
        Mat_zeroBRC(bp->AD[i][i]);
    }

    /* release local boundary node arrays */
    for (i=0; i<thee->numB; i++) {
        if (numBR[i] > 0) {
            Vmem_free(thee->vmem,numBR[i],sizeof(int),(void**)&BR[i]);
        }
        if (numBC[i] > 0) {
            Vmem_free(thee->vmem,numBC[i],sizeof(int),(void**)&BC[i]);
        }
    }

    /* setup the prolongation chain */
    bp->coarse = thee->P;
    thee->P = bp;
}

/*
 * ***************************************************************************
 * Routine:  bContrib
 *
 * Purpose:  Set or add an entry to a linked matrix entry list.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void bContrib(Vset *mtpool, int *count, int *countyr, int i, int j)
{
    int done;
    Link *curr, *mnew;

    mnew=VNULL;
    curr=(Link*)Vset_access(mtpool,i);
    VASSERT( curr != VNULL );

    /* we have to look through the row(col) */
    done=0;
    while (!done) {

        /* if first guy in row(col) is "blank", fill him with the info */
        if (curr->idx == -1) {
            (*countyr)++;
            if (i<j) (*count)++;
            curr->idx  = j;
            curr->next = VNULL;
            done = 1;

        /* we found the position; already here so nothing to do */
        } else if (curr->idx == j) {
            done = 1;

        /* not in list; insert new struct AFTER him, then swap me and him */
        } else if (curr->idx > j) {
            (*countyr)++;
            if (i<j) (*count)++;
            mnew = (Link*)Vset_create(mtpool);
            mnew->idx  = curr->idx;
            mnew->next = curr->next;
            curr->idx  = j;
            curr->next = mnew;
            done = 1;

        /* not found; no one left so create a new guy and put me there */
        } else if (curr->next == VNULL) {
            (*countyr)++;
            if (i<j) (*count)++;
            mnew = (Link*)Vset_create(mtpool);
            mnew->idx  = j;
            mnew->next = VNULL;
            curr->next = mnew;
            done = 1;

        /* not found yet; still hope */
        } else {
            curr=curr->next;
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_nodeCount
 *
 * Purpose:  Count up the total number of basis functions (nodes).
 *           This is basically an a priori count of the number of rows in
 *           the stiffness matrix.
 *
 * Notes:    This routine can handle COMPLETELY GENERAL ELEMENTS; see the
 *           comments in Aprx_interact().
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_nodeCount(Aprx *thee, Re *re)
{
    int nodeCount;

    /* make sure we have Vertex/Edge/Face/Simplex counts if needed */
    if (Re_numVDF(re) > 0) VASSERT( Gem_numVirtVV(thee->gm) > 0 );
    if (Re_numEDF(re) > 0) VASSERT( Gem_numVirtEE(thee->gm) > 0 );
    if (Re_numFDF(re) > 0) VASSERT( Gem_numVirtFF(thee->gm) > 0 );
    if (Re_numSDF(re) > 0) VASSERT( Gem_numVirtSS(thee->gm) > 0 );

    /* calculate the node count */
    nodeCount = Gem_numVirtVV(thee->gm) * Re_numVDF(re)
              + Gem_numVirtEE(thee->gm) * Re_numEDF(re)
              + Gem_numVirtFF(thee->gm) * Re_numFDF(re)
              + Gem_numVirtSS(thee->gm) * Re_numSDF(re);

    /* return */
    return nodeCount;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_interact
 *
 * Purpose:  Count the number of basis (linear/quadratic/etc) functions which
 *           interact with a given basis function.  This is basically an
 *           a priori count of the number of nonzeros per row in the
 *           stiffness matrix, and the number of nozeros per row above the
 *           diagonal (and thus the number of nonzeros per column below the
 *           diagonal if we have symmetric nonzero structure).  By doing this
 *           count, we can one-time malloc storage for matrices before
 *           assembly, and avoid extra copies as well as avoid the use
 *           of linked list structures for representing matrices with
 *           a priori unknown nonzero structure.
 *
 * Notes:    This routine can handle COMPLETELY GENERAL ELEMENTS; all it needs
 *           to do is simply compute all interactions of all nodes in the
 *           element.  The nodes may be any combination of vertex-based,
 *           edge-based, face-based (3D only), or simplex-based (interior)
 *           degrees of freedom.
 *
 *           This calculation is made possible because all of the node numbers
 *           for all of the vertex/edge/face/simplex-nodes in each simplex are
 *           available in O(1) time for each element, using the geometry
 *           manager routine Gem_simplexInfo().
 *
 * Author:   Michael Holst (updated by Ryan Szypowski)
 * ***************************************************************************
 */
VPUBLIC void Aprx_interact(Aprx *thee, Re *re, Re *reT,
    int *numR, int *numO, int *numOYR, int **IJA, int **IJAYR)
{
    int smid, i, j, p, q, ii, jj, count, countyr, size;
    int *IA,*JA,*IAYR,*JAYR;
    TT tt;
    Link *mt;
    SS *sm;
    Gem *gm;

    /* go through all nodes and setup the node interaction structure */
    Vnm_tstart(40, "node interactions");
    Vnm_print(0,"Aprx_interact: counting node interactions..\n");

    /* some local pointers */
    gm = thee->gm;

    /* clear the dynamic array */
    Vset_reset( thee->lnkG );

    /* calculate some node information */
    *numR = Aprx_nodeCount(thee, re);

    /* create an empty entry to start each row of global matrix */
    for (i=0; i<*numR; i++) {
        mt=(Link*)Vset_create(thee->lnkG);
        mt->idx  = -1;
        mt->next = VNULL;
    }

    /* go through simplices and count the off-diagonal interactions */
    count   = 0;
    countyr = 0;

    /* offsets for edge/face/simplex DF global indices */
    re->offIS[0] = 0;
    re->offIS[1] = Re_numVDF(re) * Gem_numVirtVV(gm);
    re->offIS[2] = Re_numEDF(re) * Gem_numVirtEE(gm) + re->offIS[1];
    re->offIS[3] = Re_numFDF(re) * Gem_numVirtFF(gm) + re->offIS[2];
#if 0
    re->offIS[4] = Re_numSDF(re) * Gem_numVirtSS(gm) + re->offIS[3];
#endif

    reT->offIS[0] = 0;
    reT->offIS[1] = Re_numVDF(reT) * Gem_numVirtVV(gm);
    reT->offIS[2] = Re_numEDF(reT) * Gem_numVirtEE(gm) + reT->offIS[1];
    reT->offIS[3] = Re_numFDF(reT) * Gem_numVirtFF(gm) + reT->offIS[2];
#if 0
    reT->offIS[4] = Re_numSDF(reT) * Gem_numVirtSS(gm) + reT->offIS[3];
#endif

    for (smid=0; smid<Gem_numSS(gm); smid++) {
        sm = Gem_SS(gm,smid);
        Gem_simplexInfo(gm, sm, &tt);

        /* calculate interactions: vertex-* */
        for (p=0; p<Re_numVDF(re); p++) {
            for (i=0; i<tt.dimV; i++) {
                ii = Aprx_nodeIndex (thee, re, tt.vid[i], 0, p);

                /* calculate interactions: vertex-vertex */
                for (q=0; q<Re_numVDF(reT); q++) {
                    for (j=0; j<tt.dimV; j++) {
                        jj = Aprx_nodeIndex (thee, reT, tt.vid[j], 0, q);
                        bContrib(thee->lnkG,&count,&countyr,ii,jj);
                    }
                }

                /* calculate interactions: vertex-edge */
                for (q=0; q<Re_numEDF(reT); q++) {
                    for (j=0; j<tt.dimE; j++) {
                        jj = Aprx_nodeIndex (thee, reT, tt.eid[j], 1, q);
                        bContrib(thee->lnkG,&count,&countyr,ii,jj);
                    }
                }

                /* calculate interactions: vertex-face */
                for (q=0; q<Re_numFDF(reT); q++) {
                    for (j=0; j<tt.dimF; j++) {
                        jj = Aprx_nodeIndex (thee, reT, tt.fid[j], 2, q);
                        bContrib(thee->lnkG,&count,&countyr,ii,jj);
                    }
                }

                /* calculate interactions: vertex-simplex */
                for (q=0; q<Re_numSDF(reT); q++) {
                    jj = Aprx_nodeIndex (thee, reT, tt.sid, 3, q);
                    bContrib(thee->lnkG,&count,&countyr,ii,jj);
                }
            }
        }

        /* calculate interactions: edge-* */
        for (p=0; p<Re_numEDF(re); p++) {
            for (i=0; i<tt.dimE; i++) {
                ii = Aprx_nodeIndex (thee, re, tt.eid[i], 1, p);

                /* calculate interactions: edge-vertex */
                for (q=0; q<Re_numVDF(reT); q++) {
                    for (j=0; j<tt.dimV; j++) {
                        jj = Aprx_nodeIndex (thee, reT, tt.vid[j], 0, q);
                        bContrib(thee->lnkG,&count,&countyr,ii,jj);
                    }
                }

                /* calculate interactions: edge-edge */
                for (q=0; q<Re_numEDF(reT); q++) {
                    for (j=0; j<tt.dimE; j++) {
                        jj = Aprx_nodeIndex (thee, reT, tt.eid[j], 1, q);
                        bContrib(thee->lnkG,&count,&countyr,ii,jj);
                    }
                }

                /* calculate interactions: edge-face */
                for (q=0; q<Re_numFDF(reT); q++) {
                    for (j=0; j<tt.dimF; j++) {
                        jj = Aprx_nodeIndex (thee, reT, tt.fid[j], 2, q);
                        bContrib(thee->lnkG,&count,&countyr,ii,jj);
                    }
                }

                /* calculate interactions: edge-simplex */
                for (q=0; q<Re_numSDF(reT); q++) {
                    jj = Aprx_nodeIndex (thee, reT, tt.sid, 3, q);
                    bContrib(thee->lnkG,&count,&countyr,ii,jj);
                }
            }
        }

        /* calculate interactions: face-* */
        for (p=0; p<Re_numFDF(re); p++) {
            for (i=0; i<tt.dimF; i++) {
                ii = Aprx_nodeIndex (thee, re, tt.fid[i], 2, p);

                /* calculate interactions: face-vertex */
                for (q=0; q<Re_numVDF(reT); q++) {
                    for (j=0; j<tt.dimV; j++) {
                        jj = Aprx_nodeIndex (thee, reT, tt.vid[j], 0, q);
                        bContrib(thee->lnkG,&count,&countyr,ii,jj);
                    }
                }

                /* calculate interactions: face-edge */
                for (q=0; q<Re_numEDF(reT); q++) {
                    for (j=0; j<tt.dimE; j++) {
                        jj = Aprx_nodeIndex (thee, reT, tt.eid[j], 1, q);
                        bContrib(thee->lnkG,&count,&countyr,ii,jj);
                    }
                }

                /* calculate interactions: face-face */
                for (q=0; q<Re_numFDF(reT); q++) {
                    for (j=0; j<tt.dimF; j++) {
                        jj = Aprx_nodeIndex (thee, reT, tt.fid[j], 2, q);
                        bContrib(thee->lnkG,&count,&countyr,ii,jj);
                    }
                }

                /* calculate interactions: face-simplex */
                for (q=0; q<Re_numSDF(reT); q++) {
                    jj = Aprx_nodeIndex (thee, reT, tt.sid, 3, q);
                    bContrib(thee->lnkG,&count,&countyr,ii,jj);
                }
            }
        }

        /* calculate interactions: simplex-* */
        for (p=0; p<Re_numSDF(re); p++) {
            ii = Aprx_nodeIndex (thee, re, tt.sid, 3, p);

            /* calculate interactions: simplex-vertex */
            for (q=0; q<Re_numVDF(reT); q++) {
                for (j=0; j<tt.dimV; j++) {
                    jj = Aprx_nodeIndex (thee, reT, tt.vid[j], 0, q);
                    bContrib(thee->lnkG,&count,&countyr,ii,jj);
                }
            }

            /* calculate interactions: simplex-edge */
            for (q=0; q<Re_numEDF(reT); q++) {
                for (j=0; j<tt.dimE; j++) {
                    jj = Aprx_nodeIndex (thee, reT, tt.eid[j], 1, q);
                    bContrib(thee->lnkG,&count,&countyr,ii,jj);
                }
            }

            /* calculate interactions: simplex-face */
            for (q=0; q<Re_numFDF(reT); q++) {
                for (j=0; j<tt.dimF; j++) {
                    jj = Aprx_nodeIndex (thee, reT, tt.fid[j], 2, q);
                    bContrib(thee->lnkG,&count,&countyr,ii,jj);
                }
            }

            /* calculate interactions: simplex-simplex */
            for (q=0; q<Re_numSDF(reT); q++) {
                jj = Aprx_nodeIndex (thee, reT, tt.sid, 3, q);
                bContrib(thee->lnkG,&count,&countyr,ii,jj);
            }
        }
    }
    *numO   = count;
    *numOYR = countyr;
    Vnm_print(0,"Aprx_interact: numN=<%d>, numO=<%d> numOYR=<%d>\n",
        *numR, *numO, *numOYR);
    VASSERT( *numOYR == (*numR+2*(*numO)) );

    /* create the row-start and column-index arrays for YSMP-bank */
    size = *numR + 1 + *numO;
    *IJA = Vmem_malloc( thee->vmem, size, sizeof(int) );
    IA = *IJA;
    JA = *IJA + *numR + 1;

    /* create the row-start and column-index arrays for YSMP-row(col) */
    size = *numR + 1 + *numOYR;
    *IJAYR = Vmem_malloc( thee->vmem, size, sizeof(int) );
    IAYR = *IJAYR;
    JAYR = *IJAYR + *numR + 1;

    /* now create the matrix from the temporary structure */
    count   = 0;
    countyr = 0;
    IA[0]   = 0;
    IAYR[0] = 0;
    for (i=0; i<*numR; i++) {
        for (mt=(Link*)Vset_access(thee->lnkG,i); mt!=VNULL; mt=mt->next) {
            if (mt->idx >= 0) {
                JAYR[countyr] = mt->idx;
                countyr++;
                if (mt->idx > i) {
                    JA[count] = mt->idx;
                    count++;
                }
            }
        }
        IA[i+1]   = count;
        IAYR[i+1] = countyr;
    }
    VASSERT( count   == *numO   );
    VASSERT( countyr == *numOYR );

    /* clear the dynamic array */
    Vset_reset( thee->lnkG );

    /* finish up */
    Vnm_print(0,"Aprx_interact: Done.\n");
    Vnm_tstop(40, "node interactions");
}

/*
 * ***************************************************************************
 * Routine:  Aprx_interactBlock
 *
 * Purpose:  Determine all basis function interations.
 *
 * Author:   Michael Holst (modified by Ryan Szypowski)
 * ***************************************************************************
 */
VPUBLIC void Aprx_interactBlock(Aprx *thee, Re *re[MAXV], Re *reT[MAXV],
    MATsym sym[MAXV][MAXV], MATmirror mirror[MAXV][MAXV], MATformat frmt[MAXV][MAXV],
    int numR[MAXV], int numO[MAXV][MAXV], int *IJA[MAXV][MAXV])
{
    int i, j, k;
    int nr, no, noyr, *ija, *ijayr, *itmp;

    for (i=0; i<thee->numB; i++) {
        for (j=0; j<thee->numB; j++) {

            /* store the symmetry key for this block */
            switch (thee->pde->sym[i][j]) {
              case 0:
                sym[i][j]    = ISNOT_SYM;
                mirror[i][j] = ISNOT_MIRROR;
                break;
              case 1:
                sym[i][j]    = IS_SYM;
                mirror[i][j] = ISNOT_MIRROR;
                break;
              case 2:
                sym[i][j]    = ISNOT_SYM; /* ignored when <mirror=IS_MIRROR> */
                mirror[i][j] = IS_MIRROR;
                break;
              default:
                VASSERT(0);
                break;
            }

            /* upper-triangular blocks built first */
            if (j >= i) {

                /* compute the interactions */
		Aprx_interact( thee, re[i], reT[j],
			       &nr, &no, &noyr, &ija, &ijayr );
                numR[i] = nr;

                /* handle diag/off-diag differences */
                if (j==i) {

                    /* diagonal blocks: bank-YSMP */
                    frmt[i][j] = DRC_FORMAT;
                    numO[i][j] = no;
                    IJA[i][j]  = ija;
                    Vmem_free( thee->vmem, nr+1+noyr, sizeof(int),
                        (void**)&ijayr );

                } else if (j>i) {

                    /* upper-triangle blocks: row-YSMP */
                    frmt[i][j] = ROW_FORMAT;
                    numO[i][j] = noyr;
                    IJA[i][j]  = ijayr;
                    Vmem_free( thee->vmem, nr+1+no, sizeof(int),
                        (void**)&ija );

                }

            } else { /* (j<i) */

                if ( !mirror[i][j] ) {

                    /* build lower-triangle block from upper triangle block */
                    nr    = numR[j];
                    noyr  = numO[j][i];
                    ijayr = Vmem_malloc( thee->vmem, nr+1+noyr, sizeof(int) );
                    itmp  = IJA[j][i];
                    for (k=0; k<(nr+1+noyr); k++) {
                        ijayr[k] = itmp[k];
                    }

                    /* lower-triangle blocks: col-YSMP */
                    frmt[i][j] = COL_FORMAT;
                    numO[i][j] = noyr;
                    IJA[i][j]  = ijayr;

                }
            }
        }
    }

}

/*
 * ***************************************************************************
 * Routine:  Aprx_nodeIndex
 *
 * Purpose:  Compute global index of node of dimension dim in the matrix
 *
 * Author:   Michael Holst, Oleg Korobkin (updated by Ryan Szypowski)
 * ***************************************************************************
 */
VPUBLIC int Aprx_nodeIndex (Aprx *thee, Re *re, int i, int dim, int q)
{
    int ir;

    ir = re->offIS[dim] + i;
    switch (dim) {
    case 0: ir += q * Gem_numVirtVV(thee->gm); break;
    case 1: ir += q * Gem_numVirtEE(thee->gm); break;
    case 2: ir += q * Gem_numVirtFF(thee->gm); break;
    case 3: ir += q * Gem_numVirtSS(thee->gm); break;
    default: VASSERT(0);
    }
    return (ir);
}

/*
 * ***************************************************************************
 * Routine:  Aprx_nodeIndexTT
 *
 * Purpose:  Given an index of node DF within the simplex and
 *           its TT structure, compute global index for that node
 *
 * Author:   Michael Holst, Oleg Korobkin (updated by Ryan Szypowski)
 * ***************************************************************************
 */
VPUBLIC int Aprx_nodeIndexTT (Aprx *thee, Re *re, TT *t, int idf)
{
    int d, thr, ni, nq;

    thr = 0;
    /* d is dimension of node DF (0=v,1=e,2=f,3=s) */
    for (d=0; d<re->dim; d++) {
        thr = re->dimIS[d] * re->numDF[d];
        if (idf < thr) break;
        idf -= thr;
    }
    ni = idf / re->numDF[d];  /* number of i-simplex */
    nq = idf % re->numDF[d];  /* df within this i-simplex */

    /* get i-simplex global number */
    switch (d) {
    case 0: ni = t->vid[ni]; break;
    case 1: ni = t->eid[ni]; break;
    case 2: ni = t->fid[ni]; break;
    case 3: ni = t->sid; break;
    default: VASSERT(0);
    }

    return (Aprx_nodeIndex (thee, re, ni, d, nq));
}

/*
 * ***************************************************************************
 * Routine:  Aprx_deform
 *
 * Purpose:  Deform the mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_deform(Aprx *thee, Bvec *def)
{
    int rc,i,numB;
    double *defX[MAXV];

    /* first make sure "u" makes sense as a mesh displacement */
    numB = Aprx_numB(thee);
    VWARN( numB == Gem_dimII(thee->gm) );

    /* set up the data fields for use by the deformation routine */
    for (i=0; i<MAXV; i++) {
        defX[i] = VNULL;
    }
    for (i=0; i<numB; i++) {
        defX[i] = Bvec_addrB(def,i);
    }

    /* call deform */
    rc = Gem_deform(thee->gm,numB,defX);

    /* return */
    return rc;
}

