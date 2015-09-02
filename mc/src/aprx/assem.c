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
 * rcsid="$Id: assem.c,v 1.21 2010/08/12 05:18:16 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     assem.c
 *
 * Purpose:  Class Aprx: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "aprx_p.h"

VEMBED(rcsid="$Id: assem.c,v 1.21 2010/08/12 05:18:16 fetk Exp $")

/*
 * ***************************************************************************
 * Class Alg: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_APRX)

#endif /* if !defined(VINLINE_APRX) */
/*
 * ***************************************************************************
 * Class Alg: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Aprx_buildXq
 *
 * Purpose:  Translate reference element coordinate to the current triangle.
 *
 * Author:   Michael Holst and Ryan Szypowski
 * ***************************************************************************
 */
VPUBLIC void Aprx_buildXq(Aprx *thee, Re *re,
    int qp, int face, TT *t,
    double xq[])
{
    int i, j;

    Gem *gm;
    gm = thee->gm; /* shortcut to gem structure */

    /* Get quad pt by mapping master el quad pt to this el */
    for (i=0; i<Gem_dimII(gm); i++) {
        xq[i] = t->bb[i];
        for (j=0;j<Gem_dimII(gm);j++)
            xq[i] += ( t->ff[i][j] * Re_x_hi(re,qp,j,face) );
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_buildPhi
 *
 * Purpose:  Build the scalar basis functions and their gradients
 *           on this element.
 *
 * Author:   Michael Holst and Ryan Szypowski
 * ***************************************************************************
 */
VPUBLIC void Aprx_buildPhi(Aprx *thee, Re *re,
    int qp, int face, TT *t,
    double phi[], double phix[][3])
{
    int i, j, k;

    Gem *gm;
    gm = thee->gm; /* shortcut to gem structure */

    /* Get basis functions; transform grads to arbitrary elm */
    for (i=0; i<Re_numP(re,-1); i++) {
        phi[i] = Re_phi_hi(re,qp,i,face);
        t->phi[i] = phi[i];
        for (j=0; j<Gem_dim(gm); j++) {
            phix[i][j] = 0.;
            for (k=0; k<Gem_dim(gm); k++)
                phix[i][j] += ( t->gg[k][j] * Re_phix2_hi(re,qp,i,k,face) );
            t->phix[i][j] = phix[i][j];
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_buildU
 *
 * Purpose:  Build an interpolant of the solution and its gradient.
 *
 * Notes:    evalKey==0 ==> use U=[0+ud] as evaluation point
 *           evalKey>=1 ==> use U=[u+ud] as evaluation point
 *
 * Author:   Michael Holst and Ryan Szypowski
 * ***************************************************************************
 */
VPUBLIC void Aprx_buildU(Aprx *thee, Re *re,
    int evalKey, int qp, int face, TT *t,
    double U[], double dU[][3],
    Bvec *Wu, Bvec *Wud)
{
    int i, j, k, gi;
    double u_u[VMAXP][MAXV], u_ud[VMAXP][MAXV];
    double phi[VMAXP], phix[VMAXP][3];

    Gem *gm;
    gm = thee->gm; /* shortcut to gem structure */

    /* Get basis functions and gradients */
    Aprx_buildPhi(thee, re, qp, face, t, phi, phix);

    /* Handle linearization differences between zero and non-zero functions */
    if (evalKey == 0) {
        for (j=0; j<Re_numP(re,-1); j++) {
            gi = Aprx_nodeIndexTT (thee, re, t, j);
            for (i=0; i<PDE_vec(thee->pde); i++) {
                u_u[j][i] = 0.;
                u_ud[j][i] = Bvec_valB( Wud, i, gi );
            }
        }
    } else {
        for (j=0; j<Re_numP(re,-1); j++) {
            gi = Aprx_nodeIndexTT (thee, re, t, j);
            for (i=0; i<PDE_vec(thee->pde); i++) {
                u_u[j][i] = Bvec_valB( Wu, i, gi );
                u_ud[j][i] = Bvec_valB( Wud, i, gi );
            }
        }
    }

    /* Initialize function [U+UD] and its gradient [dU+dUD] */
    for (i=0; i<PDE_vec(thee->pde); i++) {
        U[i] = 0.;
        for (k=0; k<Gem_dim(gm); k++) {
            dU[i][k] = 0.;
            for (j=0; j<Re_numP(re,-1); j++) {
                if (k==0) U[i] += phi[j] * ( u_u[j][i] + u_ud[j][i] );
                dU[i][k] += phix[j][k] * ( u_u[j][i] + u_ud[j][i] );
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_initSpace
 *
 * Purpose:  Initialize vector test function "i" and its gradient,
 *           generated by scalar test function "r" for this element.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_initSpace(Aprx *thee, int i, int r,
    double phi[], double phix[][3], double V[], double dV[][3])
{
    int j, k;
    for (j=0; j<PDE_vec(thee->pde); j++) {
        V[j] = ( (j==i) ? phi[r] : 0. );
        for (k=0; k<Gem_dim(thee->gm); k++)
            dV[j][k] = ( (j==i) ? phix[r][k] : 0. );
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_initEmat
 *
 * Purpose:  Initialize an element matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_initEmat(Aprx *thee, int bumpKey, TT *t, Emat *em)
{
    int r, s, iv, iw, gr;
    Re *re;
    Gem *gm;

    if(bumpKey) re = thee->reB[0];
    else re = thee->re[0];
    gm = thee->gm;

    em->J = 0.;
    for (iv=0; iv<PDE_vec(thee->pde); iv++) {
        for (r=0; r<Re_numP(re,-1); r++) {
            gr = Aprx_nodeIndexTT (thee, re, t, r);
            em->NI[iv][r] = gr;
#if 0
fprintf(stderr,"*** gr=<%d> ***\n", gr);
#else
            if (bumpKey) em->TP[iv][r] = SS_faceType(t->s, r);
            else em->TP[iv][r] = Bnode_data(thee->B,iv)[gr].type;
#endif
            em->F[iv][r]  = 0.;
            for (iw=0; iw<PDE_vec(thee->pde); iw++) {
                for (s=0; s<Re_numP(re,-1); s++) {
                    em->A[iv][iw][r][s] = 0.;
                    em->M[iv][iw][r][s] = 0.;
                }
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_quadEmat
 *
 * Purpose:  Build an element matrix and an element load vector for a
 *           single given element, using quadrature.
 *
 * Notes:    We handle both the volume and surface cases here, using
 *           "face" and "t" as follows:
 *
 *           face <  0 ==> do volume quadrature; we take the node numbers
 *                         as just the identity mapping.
 *
 *           face >= 0 ==> do face quadrature for face "face", where the node
 *                         numbers for face are taken from t->loc[face][].
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_quadEmat(Aprx *thee,
    int evalKey, int energyKey, int residKey, int tangKey, int massKey,
    int bumpKey,
    int face, TT *t, Emat *em,
    Bvec *Wu, Bvec *Wud)
{
    /* some variables */
    int i, qp, r, s, r2, s2, gr, gs, iv, iw, rrange, sym, key, iw_formed;
    int loc[VMAXP];
    double Dw, xq[3], phi[VMAXP], phix[VMAXP][3], gamma, theta, energy, jacD;
    double U[MAXV], dU[MAXV][3];
    double W[MAXV], dW[MAXV][3];
    double V[MAXV], dV[MAXV][3];
    Re *re, *reU;
    Gem *gm;

    /* hard-coded element for now... */
    if(bumpKey) {
	re = thee->reB[0];
	if(bumpKey == 2) reU = thee->reB[0];
	else reU = thee->re[0];
    }
    else {
	re = thee->re[0];
	reU = thee->re[0];
    }
    gm = thee->gm;

    /* deal with differences between a volume and a surface quadrature */
    if (face<0) {
        if ((evalKey == 0) || (evalKey == 1)) {
            key = 0;  /* build primal problem: volume form */
        } else { /* if ((evalKey == 2) || (evalKey == 3)) */
            key = 2;  /* build dual problem: volume form */
        }
        jacD = t->D;
    } else {
        if ((evalKey == 0) || (evalKey == 1)) {
            key = 1;  /* build primal problem: surface form */
        } else { /* if ((evalKey == 2) || (evalKey == 3)) */
            key = 3;  /* build dual problem: surface form */
        }
        jacD = t->faceD[face];
    }
    rrange = Re_numP(re,-1);
    for (i=0;i<rrange;i++) loc[i] = i;

    /* Go thru quad pts m=1:Qx, computing contrib. to ele matrix. */
    for (qp=0; qp<Re_numQ_hi(re,face); qp++) {

        /* jacobian and quadrature weight */
        Dw = jacD * Re_w_hi(re,qp,face);

        /* build basis functions and translate quadrature point to global domain */
        Aprx_buildPhi(thee,re,qp,face,t,phi,phix);
        Aprx_buildU(thee,reU,evalKey,qp,face,t,U,dU,Wu,Wud);
        Aprx_buildXq(thee,re,qp,face,t,xq);

        /* once-per-point PDE initialization */
        thee->pde->initPoint(thee->pde,key,t->gchart,xq,U,dU);

        /* assemble energy if required */
        if (energyKey > 0) {

            /* eval (interior or boundary) energy functional */
            energy = thee->pde->Ju(thee->pde,key);

            /* add in contribution to vector */
            em->J += Dw*energy;
        }

        /* outer basis loop; only need if building a residual/load vector */
        if ((residKey > 0) || (tangKey > 0) || (massKey > 0)) {

            /* begin dealing with inner-products of the form (r,s) */
            for (r2=0; r2<rrange; r2++) {
                r = loc[r2];
                gr = Aprx_nodeIndexTT (thee, re, t, r);

                /* which V-basis function */
                for (iv=0; iv<PDE_vec(thee->pde); iv++) {
                    t->focusIV = iv;

                    /* initialize function/gradient */
                    Aprx_initSpace(thee,iv,r,phi,phix,V,dV);

                    /* assemble residual if required */
                    if (residKey > 0) {

                        /* eval (interior or boundary) nonlinear form */
                        gamma = thee->pde->Fu_v(thee->pde,key,V,dV);

                        /* add in contribution to vector */
                        em->F[iv][r] -= Dw*gamma;
                    }

                    /* inner basis loop; only need if building a matrix */
                    if ((tangKey > 0) || (massKey > 0)) {

                        /* build only upper-triangle if possible */
                        for (s2=0; s2<rrange; s2++) {
                            s = loc[s2];
                            gs = Aprx_nodeIndexTT (thee, re, t, s);

                            /* which W-basis function */
                            for (iw=0; iw<PDE_vec(thee->pde); iw++) {
                                t->focusIW = iw;
                                iw_formed = 0;
                                sym = thee->pde->sym[iv][iw];

                                /* assemble tangent matrix if required */
                                if (tangKey > 0) {

                                    /* handle symmetries in tangent form */
                                    if ((sym==0)||((sym==1) && (gr<=gs))) {

                                        /* initialize function/gradient */
                                        Aprx_initSpace(thee,iw,s,phi,phix,W,dW);
                                        iw_formed = 1;

                                        /* eval (interior or bndry) form */
                                        theta = thee->pde->DFu_wv(thee->pde,
                                            key,W,dW,V,dV);

                                        /* add in contribution to matrix */
                                        em->A[iv][iw][r][s] += Dw*theta;

                                    } /* symmetries in the tengent form */
                                } /* assemble tangent matrix */

                                /* assemble mass matrix if required */
                                if (massKey > 0) {

                                    /* handle symmetries in the mass form */
                                    if ((sym==0)||((sym==1) && (gr<=gs))) {

                                        /* initialize function/gradient */
                                        if (!iw_formed) {
                                            Aprx_initSpace(thee,
                                                iw,s,phi,phix,W,dW);
                                            iw_formed = 1;
                                        }

                                        /* eval (interior or bndry) form */
                                        theta = thee->pde->p_wv(thee->pde,
                                            key,W,V);

                                        /* add in contribution to matrix */
                                        em->M[iv][iw][r][s] += Dw*theta;
    
                                    } /* symmetries in the mass form */
                                } /* assemble mass matrix */

                            } /* which W-basis function */
                        } /* s; loop over element matrix columns */
                    } /* if tangent or mass matrix needed */
                } /* which V-basis function */
            } /* r; loop over element matrix rows (and, faces of simplex) */
        } /* if residual/load vector needed */
    } /* m; loop over quadrature points */
}

/*
 * ***************************************************************************
 * Routine:  Aprx_fanEmat
 *
 * Purpose:  Fan out an element matrix to the global matrix,
 *           and fan out an element vector to the global vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_fanEmat(Aprx *thee,
    int evalKey, int energyKey, int residKey, int tangKey, int massKey,
    int bumpKey,
    Emat *em,
    Bmat *A, Bmat *M, Bvec *F)
{
    int iv, iw, sym, r, s;
#if 0
    int j;
#endif
    Re *re = thee->re[0];

    if(bumpKey) re = thee->reB[0];

    if ((residKey > 0) || (tangKey > 0) || (massKey > 0)) {
        for (r=0; r<Re_numP(re,-1); r++) { /* for (r=0; r<Gem_dimVV(thee->gm); r++) */
            for (iv=0; iv<PDE_vec(thee->pde); iv++) {

                if (residKey > 0) {
                    if (VDIRICHLET( em->TP[iv][r] )) {
                        /* vr is a dirichlet point */
                        Bvec_setB(F, iv, em->NI[iv][r], 0.);
                    } else {
                        /* vr is not a dirichlet point */
                        Bvec_addToB(F, iv, em->NI[iv][r], em->F[iv][r]);
                    }
                }

                if ((tangKey > 0) || (massKey > 0)) {
                    for (s=0; s<Re_numP(re,-1); s++) { /* for (s=0; s<Gem_dimVV(thee->gm); s++)  */
                        for (iw=0; iw<PDE_vec(thee->pde); iw++) {
                            sym = thee->pde->sym[iv][iw];

                            /* assemble tangent matrix */
                            if (tangKey > 0) {
                                /* handle symmetries in tangent form */
                                if ( (sym==0) || ((sym==1)
                                    &&(em->NI[iv][r]<=em->NI[iw][s])) ) {

                                    /* one or both vr|vs are dirichlet */
                                    if  ( VDIRICHLET( em->TP[iv][r] )
					  || VDIRICHLET( em->TP[iw][s] ) ) {

                                        /* vr is dirichlet */
                                        if (VDIRICHLET( em->TP[iv][r] ) ) {
#if 1
                                            Bmat_set( A,iv,iv, em->NI[iv][r], em->NI[iv][r], 1. );
#else
                                            for (j=0; j<PDE_vec(thee->pde); j++)
                                                Bmat_set( A,j,j,
                                                    em->NI[iv][r],
                                                    em->NI[iv][r], 1. );
#endif
                                        }
                                        /* vs is dirichlet */
                                        if (VDIRICHLET( em->TP[iw][s] ) ) {
#if 1
                                            Bmat_set( A,iw,iw, em->NI[iw][s], em->NI[iw][s], 1. ); 
#else
                                            for (j=0; j<PDE_vec(thee->pde); j++)
                                                Bmat_set( A,j,j,
                                                    em->NI[iw][s],
                                                    em->NI[iw][s], 1. );
#endif
                                        }

                                    /* neither vr|vs are dirichlet */
                                    } else {
#if 1
                                        Bmat_addTo( A, iv, iw, em->NI[iv][r], em->NI[iw][s], em->A[iv][iw][r][s] );
#else
                                        Bmat_addTo( A, iv, iw,
                                            em->NI[iv][r], em->NI[iw][s],
                                            em->A[iv][iw][r][s] );
#endif
                                    }
                                } /* symmetries in the tangent form */
                            } /* assemble tangent matrix */
                           
                            /* assemble mass matrix */
                            if (massKey > 0) {
                                /* handle symmetries in mass form */
                                if ( (sym==0) || ((sym==1)
                                    &&(em->NI[iv][r]<=em->NI[iw][s])) ) {

                                    /* one or both vr|vs are dirichlet */
                                    if  ( VDIRICHLET( em->TP[iv][r] )
					  || VDIRICHLET( em->TP[iw][s] ) ) {

                                        /* vr is dirichlet */
                                        if (VDIRICHLET( em->TP[iv][r] )) {
#if 1
                                            Bmat_set( M,iv,iv, em->NI[iv][r], em->NI[iv][r], 1. );
#else
                                            for (j=0; j<PDE_vec(thee->pde); j++)
                                                Bmat_set( M,j,j,
                                                    em->NI[iv][r],
                                                    em->NI[iv][r], 1. );
#endif
                                        }
                                        /* vs is dirichlet */
                                        if (VDIRICHLET( em->TP[iw][s] )) {
#if 1
                                            Bmat_set( M,iw,iw, em->NI[iw][s], em->NI[iw][s], 1. );
#else
                                            for (j=0; j<PDE_vec(thee->pde); j++)
                                                Bmat_set( M,j,j,
                                                    em->NI[iw][s],
                                                    em->NI[iw][s], 1. );
#endif
                                        }

                                    /* neither vr|vs are dirichlet */
                                    } else {
#if 1
                                        Bmat_addTo( M, iv, iw, em->NI[iv][r], em->NI[iw][s], em->M[iv][iw][r][s] );
#else
                                        Bmat_addTo( M, iv, iw,
                                            em->NI[iv][r], em->NI[iw][s],
                                            em->M[iv][iw][r][s] );
#endif
                                    }
                                } /* symmetries in the mass form */
                            } /* assemble mass matrix */

                        } /* which W-basis function */
                    } /* s; loop over element matrix columns */
                } /* if tangent or mass matrix needed */
            } /* which V-basis function */
        } /* r; loop over element matrix rows (and, faces of simplex) */
    } /* if residual/load vector needed */
}

/*
 * ***************************************************************************
 * Routine:  Aprx_assemEmat
 *
 * Purpose:  Assemble one element matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_assemEmat(Aprx *thee, SS *sm,
    int evalKey, int energyKey, int residKey, int tangKey, int massKey,
    int bumpKey,
    Emat *em,
    Bvec *Wu, Bvec *Wud)
{
    int face, someComponentIsNeumann, i, j;
    TT t;

    /* volume trans from master to this element (and back) */
    Gem_buildVolumeTrans(thee->gm,sm,&t);

    /* initialize the element matrix (zero it out) */
    Aprx_initEmat(thee,bumpKey,&t,em);

    /* once-per-element PDE initialization */
    thee->pde->initElement(thee->pde,t.stype,t.gchart,t.vx,&t);

    /* volume quadrature */
    face = -1;
    Aprx_quadEmat(thee,
        evalKey,energyKey,residKey,tangKey,massKey,
        bumpKey,
        face,&t,em,Wu,Wud);

    if(bumpKey) return;

    /* now handle any neumann boundary faces this element may have */
    for (face=0; face<Gem_dimVV(thee->gm); face++) {
        t.focusFace = face;

        someComponentIsNeumann = 0; 
        for (i=0; i<PDE_vec(thee->pde); i++) {
            if (VNEUMANN( thee->pde->bmap[i][ SS_faceType(sm,face) ] )) {
                someComponentIsNeumann = 1;
            }
        }
     
        if ( someComponentIsNeumann ) {

            /* boundary trans from master to this element (and back) */
            Gem_buildSurfaceTrans(thee->gm,face,&t);

            /* once-per-face PDE initialization */
            thee->pde->initFace(thee->pde,SS_faceType(sm,face),
                t.gchart,t.nvec[face]);

            /* surface quadrature */
            Aprx_quadEmat(thee,
                evalKey,energyKey,residKey,tangKey,massKey,
                bumpKey,
                face,&t,em,Wu,Wud);
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_assem
 *
 * Purpose:  Assemble the tangent matrix and nonlinear residual 
 *           vector (which reduces to the normal stiffness matrix and load 
 *           vector in the case of a linear problem) for a general nonlinear
 *           system of m components in spatial dimension d.
 *
 * NOTES:    The assembly modes for this routine are:
 *
 *               evalKey   == 0 ==> Primal problem: evaluation at z=[0+ud].
 *                         == 1 ==> Primal problem: evaluation at z=[u+ud].
 *                         == 2 ==> Dual problem: evaluation at z=[0+ud].
 *                         == 3 ==> Dual problem: evaluation at z=[u+ud].
 *                         == ? ==> Same as 0.
 *
 *               energyKey == 0 ==> DON'T assemble an energy.
 *                         == 1 ==> Assemble the energy J(z).
 *                         == 2 ==> Assemble the energy 0.
 *                         == ? ==> Same as 0.
 *
 *               residKey  == 0 ==> DON'T assemble a residual.
 *                         == 1 ==> Assemble the residual F(z)(v).
 *                         == 2 ==> Assemble the residual 0.
 *                         == ? ==> Same as 0.
 *
 *               tangKey   == 0 ==> DON'T assemble a tangent matrix.
 *                         == 1 ==> Assemble the tangent matrix DF(z)(w,v).
 *                         == 2 ==> Assemble the tangent matrix 0.
 *                         == ? ==> Same as 0.
 *
 *               massKey   == 0 ==> DON'T assemble a mass matrix.
 *                         == 1 ==> Assemble the mass matrix p(w,v).
 *                         == 2 ==> Assemble the mass matrix 0.
 *                         == ? ==> Same as 0.
 *
 * NOTES:    The nonlinear residual should always be ZERO at dirichlet nodes!
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Aprx_assem(Aprx *thee,
    int evalKey, int energyKey, int residKey, int tangKey, int massKey,
    int bumpKey,
    int ip[], double rp[],
    Bmat *A, Bmat *M, Bvec *F, Bvec *Wu, Bvec *Wud)
{
    /* some variables */
    int i, j, k, smid, vxid, vType, chart, cnt;
    double energy, xm[3], Delt[MAXV];
    SS *sm;
    VV *vx;
    Emat em;

    /* do some i/o if this is a single assembly (e.g. linear problem) */
    if ((evalKey==0) || (evalKey==2)) {
        Vnm_tstart(30, "element assembly");
        Vnm_print(0,"Aprx_assem: assembling..");
    }

    /* once-per-assembly PDE initialization */
    thee->pde->initAssemble(thee->pde,ip,rp);

    /* initialize the energy */
    energy = 0.;

    /* the BIG loop over all of the elements in the mesh.. */
    smid = 0;
    while ( (smid < Gem_numSS(thee->gm)) && (!Vnm_sigInt()) ) {
        sm = Gem_SS(thee->gm,smid);

        if ( (smid>0) && (smid % VPRTKEY) == 0 ) Vnm_print(0,"[AS:%d]",smid);
        
        /* assemble the element matrix and the element vector */
        Aprx_assemEmat(thee, sm,
            evalKey, energyKey, residKey, tangKey, massKey,
            bumpKey,
            &em, Wu, Wud);

        /* fan-out element matrix and element vector to global system */
        Aprx_fanEmat(thee,
            evalKey, energyKey, residKey, tangKey, massKey,
            bumpKey,
            &em, A, M, F);

        /* accumulate the energy */
        energy += em.J;

        /* next sm */
        smid++;

    } /* loop over elements */

    if(bumpKey) { /* bail out if we're solving the bump system */
	/* do some i/o if this is a single assembly (linear problem) */
	if ((evalKey==0) || (evalKey==2)) {
	    Vnm_print(0,"..done.\n");
	    Vnm_tstop(30, "assembly");
	}

	/* return the assembled energy */
	return energy;
    }

    /* the BIG loop over all of the nodes in the mesh.. */
    cnt = 0;
    for (k=0; k<Bnode_numB(thee->B); k++) {
        for (i=0; i<Bnode_numR(thee->B,k); i++) {
            if ( (cnt>0) && (cnt % VPRTKEY) == 0 ) Vnm_print(0,"[AV:%d]",cnt);
            cnt++;

/* MIKE: FIX THIS! */
            vType = Bnode_data(thee->B,k)[i].type;
#if 1
            chart = Bnode_data(thee->B,k)[i].chart;
#else
            chart = VV_chart( Gem_VV(thee->gm,i) );
#endif
            vxid  = Bnode_data(thee->B,k)[i].myvert;

            /* only deal with it if node is actually non-diri vertex of mesh */
            if ( (!VDIRICHLET( vType )) && (vxid >= 0) && (vxid<Gem_numVV(thee->gm))) {
                vx = Gem_VV(thee->gm,vxid);
                for (j=0; j<Bnode_data(thee->B,k)[i].numx; j++)
                    xm[j] = Bnode_data(thee->B,k)[i].x[j];
                for (j=0; j<PDE_vec(thee->pde); j++)
                    Delt[j] = 0.0;

                /* deal with any delta-func contributions to the source term */
                /* (assuming our basis functions are a Lagrange basis!) */
                thee->pde->delta(thee->pde, vType, chart, xm, vx, Delt);

                /* count ONLY the k-th component */
                Bvec_addToB( F, k, vxid, Delt[k] );
            }
        }
    }

    /* build Bnode information into A and M */
    Aprx_buildBRC(thee, A, M);

    /* do some i/o if this is a single assembly (linear problem) */
    if ((evalKey==0) || (evalKey==2)) {
        Vnm_print(0,"..done.\n");
        Vnm_tstop(30, "assembly");
    }

    /* return the assembled energy */
    return energy;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_buildBRC
 *
 * Purpose:  Build boundary Bnode information into two Bmats.
 *
 * Notes:    Either/both Bmat objects can be VNULL without error;
 *           the result for that VNULL Bmat is a No-Op.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_buildBRC(Aprx *thee, Bmat *A, Bmat *M)
{
    /* some variables */
    int i, j;
    int numBR[MAXV], numBC[MAXV], *BR[MAXV], *BC[MAXV];

    /* sanity check: Bnode B better exist, since B/ibv created together */
    VASSERT( thee->B != VNULL );

    /* make boundary node arrays */
    for (i=0; i<thee->numB; i++) {
        numBR[i] = thee->numBV[i]; 
        numBC[i] = thee->numBV[i]; 
        if (numBR[i] > 0) {
            BR[i] = Vmem_malloc(thee->vmem,numBR[i],sizeof(int));
        }
        if (numBC[i] > 0) {
            BC[i] = Vmem_malloc(thee->vmem,numBC[i],sizeof(int));
        }
        for (j=0; j<numBR[i]; j++) { 
            BR[i][j] = thee->ibv[i][j];
        }
        for (j=0; j<numBC[i]; j++) { 
            BC[i][j] = thee->ibv[i][j];
        }
    }

    /* copy boundary node arrays into A */
    for (i=0; i<thee->numB; i++) {
        for (j=0; j<thee->numB; j++) {
            if (A != VNULL) {
                Mat_buildBRC(A->AD[i][j], numBR[i], numBC[j], BR[i], BC[j]);
            }
            if (M != VNULL) {
                Mat_buildBRC(M->AD[i][j], numBR[i], numBC[j], BR[i], BC[j]);
            }
        }
    }

    /* free boundary node arrays */
    for (i=0; i<thee->numB; i++) {
        if (numBR[i] > 0) {
            Vmem_free(thee->vmem,numBR[i],sizeof(int),(void**)&BR[i]);
        }
        if (numBC[i] > 0) {
            Vmem_free(thee->vmem,numBC[i],sizeof(int),(void**)&BC[i]);
        }
    }
}

