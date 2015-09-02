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
 * rcsid="$Id: estim.c,v 1.19 2010/08/12 05:18:17 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     estim.c
 *
 * Purpose:  Class Aprx: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "aprx_p.h"

VEMBED(rcsid="$Id: estim.c,v 1.19 2010/08/12 05:18:17 fetk Exp $")

VEXTERNC void Aprx_estRecovGrad(Aprx *thee, int color,
    Bvec *u, Bvec *ud, Bvec *r);
VEXTERNC double Aprx_estRecovGradSS(Aprx *thee, SS *sm,
    Bvec *u, Bvec *ud, Bvec *r);
VEXTERNC void Aprx_estFaceBump(Aprx *thee, int color,
    Bvec *u, Bvec *ud, Bvec *r);

/*
 * ***************************************************************************
 * Class Aprx: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_APRX)

#endif /* if !defined(VINLINE_APRX) */
/*
 * ***************************************************************************
 * Class Aprx: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Aprx_markRefine
 *
 * Purpose:  Mark simplices to be refined
 *
 * Input:    If (  (key == -1)  |
 *              || (key ==  0)  | ==> Let geometry manager deal with it.
 *              || (key ==  1)) |
 *           If (key == 2) ==> Nonlinear residual indicator.
 *           If (key == 3) ==> Dual-weighted residual indicator.
 *           If (key == 4) ==> Local problem indicator.
 *           If (key == 5) ==> Recovered gradient indicator.
 *           If (key == 6) ==> Face-bump error indicator.
 *
 * Author:   Michael Holst (updated by Ryan Szypowski)
 * ***************************************************************************
 */
VPUBLIC int Aprx_markRefine(Aprx *thee, int key, int color,
    int bkey, double elevel, Bvec *u, Bvec *ud, Bvec *f, Bvec *r)
{
    int marked = 0;

    /* input check and some i/o */
    if ( ! ((-1 <= key) && (key <= 6)) ) {
        Vnm_print(0,"Aprx_markRefine: bad refine key; simplices marked = %d\n",
            marked);
        return marked;
    }

    /* mark simplices to be refined */
    if ((-1 <= key) && (key <= 1)) {
        marked = Gem_markRefine(thee->gm, key, color);
    } else if ((2 <= key) && (key <= 6)) {
        marked = Aprx_estRefine(thee, key, color, bkey, elevel, u,ud,f,r);
    } else Vnm_print(0,"Aprx_markRefine: bad input!");

    return marked;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_buildFunc
 *
 * Purpose:  Build the elementary basis functions and other quantities that
 *           are needed for various error indicators.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_buildFunc(Aprx *thee, Re *re,
    TT *t, int qp, int face, Bvec *u, Bvec *ud,
    double xq[], double U[], double dU[][3])
{
    int i, j, k;
    double phi[4], phix[4][3];
    double u_u[4][MAXV], u_ud[4][MAXV];

    /* Get quad pt by mapping master el quad pt to this el */
    for (i=0; i<Gem_dimII(thee->gm); i++) {
        xq[i] = t->bb[i];
        for (j=0;j<Gem_dimII(thee->gm);j++)
            xq[i] += ( t->ff[i][j] * Re_x_hi(re,qp,j,face) );
    }

    /* Get basis functions; transform grads to arbitrary elm */
    for (i=0; i<Gem_dimVV(thee->gm); i++) {
        phi[i] = Re_phi_hi(re,qp,i,face);
        for (j=0; j<Gem_dim(thee->gm); j++) {
            phix[i][j] = 0.;
            for (k=0; k<Gem_dim(thee->gm); k++)
                phix[i][j] += ( t->gg[k][j] * Re_phix2_hi(re,qp,i,k,face) );
        }
    }

    /* Setup for initialize of [U+UD] and [dU+dUD] and [F] */
    for (j=0; j<Gem_dimVV(thee->gm); j++) {
        for (i=0; i<Aprx_numB(thee); i++) {
            u_u[j][i]  = Bvec_valB( u,  i, t->vid[j] );
            u_ud[j][i] = Bvec_valB( ud, i, t->vid[j] );
        }
    }

    /* Initialize [U+UD] and [dU+dUD] and [F] */
    for (i=0; i<Aprx_numB(thee); i++) {
        U[i] = 0.;
        for (k=0; k<Gem_dim(thee->gm); k++) {
            dU[i][k] = 0.;
            for (j=0; j<Gem_dimVV(thee->gm); j++) {
                if (k==0) {
                    U[i] += phi[j] * ( u_u[j][i] + u_ud[j][i] );
                }
                dU[i][k] += phix[j][k] * ( u_u[j][i] + u_ud[j][i] );
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_estNonlinResid
 *
 * Purpose:  A posteriori error estimation via the nonlinear residual.
 *
 * Notes:    This is a nonlinear residual estimator in the style of Verfurth.
 *           In particular, this is an implementation of the nonlinear
 *           residual estimator derived in:
 *
 *               "Adaptive multilevel finite element methods on manifolds
 *                and their implementation in MC", by M. Holst.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Aprx_estNonlinResid(Aprx *thee, SS *sm,
    Bvec *u, Bvec *ud, Bvec *f)
{
    /* some variables */
    int i, m, m_N, face, face_N;
    double Dw, errEst, errEstS, errEstF, nval, tmp;
    double xm[3], U[MAXV], dU[MAXV][3], F[MAXV];
    double xm_N[3], U_N[MAXV], dU_N[MAXV][3], F_N[MAXV];
    int vxn_pmt, vxn[3], vxn_N[3];
    Re *re;
    SS *sm_N;
    TT t, t_N;

    /* initialize the error estimate for this element */
    errEst = 0.0;
        
    /* volume trans from master to this element (and back) */
    Gem_buildVolumeTrans(thee->gm,sm,&t);

    /* once-per-element PDE initialization */
    thee->pde->initElement(thee->pde,t.stype,t.gchart,t.vx,&t);

    /* hard-code element for now... */
    re = thee->re[0];

    /* initialize contribution from this volume */
    errEstS = 0.;

    /* Cycle thru quad points */
    face = -1;
    for (m=0; m<Re_numQ_hi(re,face); m++) {

        /* jacobian and quadrature weight */
        Dw = t.D * Re_w_hi(re,m,face);

        /* evaluate solution/gradient at current quad point */
        Aprx_buildFunc(thee,re,&t,m,face,u,ud,xm,U,dU);

        /* get strong residual in element:  b(u)^i - a(u)^{iq}_{~;q}  */
        thee->pde->initPoint(thee->pde,0,t.gchart,xm,U,dU);
        thee->pde->Fu(thee->pde,0,F);
        nval = 0.;
        for (i=0; i<Aprx_numB(thee); i++) {
            tmp = F[i];
            nval += thee->pde->est[i] * tmp*tmp;
        }
        errEstS += ( Dw * nval );

    } /* m; loop over volume quadrature points */
    errEstS *= (t.D * t.D);

    /* add in contribution from this volume */
    errEst += errEstS;

    /* surface contributions to the estimate for this element */
    for (face=0; face<Gem_dimVV(thee->gm); face++) {
        t.focusFace = face;

        /* initialize contribution from this face */
        errEstF = 0.;

        /* boundary trans from master to this element (and back) */
        Gem_buildSurfaceTrans(thee->gm,face,&t);

        /* once-per-face PDE initialization */
        thee->pde->initFace(thee->pde,SS_faceType(sm,face),
            t.gchart,t.nvec[face]);

        /* fill array vxn[] with indices of vertices on a face */
        if(Gem_dim(thee->gm) == 3) {
            vxn[0] = t.vid[vmapF[face][0]];
            vxn[1] = t.vid[vmapF[face][1]];
            vxn[2] = t.vid[vmapF[face][2]];
        }

        /* if this is an interior face, do the jump estimation */
        if (VINTERIOR( SS_faceType(sm,face) )) {

            /* get face-nabor across face, his local face number, and trans */
            sm_N = SS_nabor(sm,face);
            face_N = SS_sharedFaceLocNum(sm_N,sm);
            Gem_buildVolumeTrans(thee->gm,sm_N,&t_N);

            /* fill array vxn_N[] with indices of vertices of face_N */
            if(Gem_dim(thee->gm) == 3) {
                vxn_N[0] = t_N.vid[vmapF[face_N][0]];
                vxn_N[1] = t_N.vid[vmapF[face_N][1]];
                vxn_N[2] = t_N.vid[vmapF[face_N][2]];
            }

            /* Cycle thru quad points (diff edge integs poss) */
            for (m=0; m<Re_numQ_hi(re,face); m++) {

                /* jacobian and quadrature weight */
                Dw = t.faceD[face] * Re_w_hi(re,m,face);

                /* take care of different "numbering" order of quad pts */
                if(Gem_dim(thee->gm) == 2) {
                    /* the face nabor's "numbering" of quad pts is reversed! */
                    m_N = (Re_numQ_hi(re,face)-1) - m;
                } else {
                    /* determine which permutaion maps vxn onto vxn_N */
                    if (vxn[0]==vxn_N[0]) {
                        if (vxn[1]==vxn_N[1]) {
                            VASSERT( vxn[2]==vxn_N[2]);
                            vxn_pmt = VPMT_012;
                        } else {
                            VASSERT( vxn[2]==vxn_N[1]);
                            VASSERT( vxn[1]==vxn_N[2]);
                            vxn_pmt = VPMT_021;
                        } 
                    } else if (vxn[0]==vxn_N[1]) {
                        if (vxn[1]==vxn_N[2]) {
                            VASSERT( vxn[2]==vxn_N[0]);
                            vxn_pmt = VPMT_120;
                        } else {
                            VASSERT( vxn[1]==vxn_N[0]);
                            VASSERT( vxn[2]==vxn_N[2]);
                            vxn_pmt = VPMT_102;
                        } 
                    } else {
                        VASSERT( vxn[0]==vxn_N[2]);
                        if (vxn[1]==vxn_N[0]) {
                            VASSERT( vxn[2]==vxn_N[1]);
                            vxn_pmt = VPMT_201;
                        } else {
                            VASSERT( vxn[1]==vxn_N[1]);
                            VASSERT( vxn[2]==vxn_N[0]);
                            vxn_pmt = VPMT_210;
                        } 
                    }  
                    /* find quad point m_N, which corresponds to m */
                    m_N = Re_sqPmt_hi(re, vxn_pmt, m);
                }

                /* evaluate solution/gradient at current quad point */
                Aprx_buildFunc(thee,re,&t,  m,  face,  u,ud,xm,  U,  dU  );
                Aprx_buildFunc(thee,re,&t_N,m_N,face_N,u,ud,xm_N,U_N,dU_N);

                /* TEST: see if we have the quad points lined up! */
                for (i=0; i<Gem_dimII(thee->gm); i++)
                    VASSERT( VABS(xm[i] - xm_N[i]) < VSMALL );

                /* get side1 of jump on interior face:  a(u1)^{iq} n_q  */
                thee->pde->initElement(thee->pde,
                    t.stype,t.gchart,t.vx,&t);
                thee->pde->initPoint(thee->pde,0,t.gchart,xm,U,dU);
                thee->pde->Fu(thee->pde,2,F);

                /* get side2 of jump on interior face:  a(u2)^{iq} n_q  */
                thee->pde->initElement(thee->pde,
                    t_N.stype,t_N.gchart,t_N.vx,&t_N);
                thee->pde->initPoint(thee->pde,0,t_N.gchart,xm_N,U_N,dU_N);
                thee->pde->Fu(thee->pde,2,F_N);

                /* jump term  [a(u1)^{iq} - a(u2)^{iq}] n_q  */
                nval = 0.;
                for (i=0; i<Aprx_numB(thee); i++)  {
                    tmp = F[i] - F_N[i];
                    nval += thee->pde->est[i] * tmp*tmp;
                }
                errEstF += ( Dw * nval );

            } /* m; loop over surface quadrature points */
            errEstF *= (0.5 * t.faceD[face]);

        /* if neumann boundary face, penalize using neumann residual */
        } else if (VNEUMANN( SS_faceType(sm,face) )) {

            /* Cycle thru quad points (diff edge integs poss) */
            for (m=0; m<Re_numQ_hi(re,face); m++) {

                /* jacobian and quadrature weight */
                Dw = t.faceD[face] * Re_w_hi(re,m,face);

                /* evaluate solution/gradient at current quad point */
                Aprx_buildFunc(thee,re,&t,m,face,u,ud,xm,U,dU);

                /* neumann condition residual:  c(u)^i + a(u)^{iq} n_q  */
                thee->pde->initPoint(thee->pde,1,t.gchart,xm,U,dU);
                thee->pde->Fu(thee->pde,1,F);
                nval = 0.;
                for (i=0; i<Aprx_numB(thee); i++) {
                    tmp = F[i];
                    nval += thee->pde->est[i] * tmp*tmp;
                }
                errEstF += ( Dw * nval );

            } /* m; loop over surface quadrature points */
            errEstF *= t.faceD[face];

        } /* if; this simplex surface was an interior or neumann surface */

        /* add in contribution from this face */
        errEst += errEstF;

    } /* r; loop over surfaces of the element */

    /* returning the SQUARE of final residual indicator over the element */
    return VABS(errEst);
}

/*
 * ***************************************************************************
 * Routine:  Aprx_estDualProblem
 *
 * Purpose:  A posteriori error estimation via linearized dual problem.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Aprx_estDualProblem(Aprx *thee, SS *sm,
    Bvec *u, Bvec *ud, Bvec *f)
{
    Vnm_print(0,"Aprx_estDualProblem: This estimator is broken badly.\n");
    Vnm_print(0,"Aprx_estDualProblem: Use the residual estimator instead.\n");
    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_estLocalProblem
 *
 * Purpose:  A posteriori error estimation via local problem solve.
 *
 * Notes:    We implement a standard bump-function estimator similar to that
 *           used in PLTMG.  This error estimator is also similar to the 
 *           "weak-residual" error estimator of Liu-Rheinboldt.  The error
 *           estimator has an advantage over normal residual-based error
 *           estimators in that it requires only the weak formulation of
 *           the problem, which fits in with the abstract forms interface
 *           which MC uses to define the problem in terms of abstract 
 *           nonlinear and bilinear forms.  Unfortunately, it involve the
 *           solution of a (small) elliptic system to produce the estimate
 *           in each element.
 *
 *           The estimator details are as follows.  In the case of linear
 *           elements in 2D or 3D, we build a local problem using the 
 *           quadratic bump functions which live on the edges of the 
 *           elements.  In the scalar case, this local problem is then
 *           3x3 for triangles, and 6x6 for tetrahedra.  Unfortunately,
 *           for an N-component elliptic system, the local problem has
 *           size 6Nx6N in 3D.  This can be quite expensive, so we do some
 *           tricks to avoid actually inverting this matrix every time we
 *           need to estimate the error in an element.
 *
 *           A further twist is that the local problem has Neumann boundary
 *           conditions, which unfortunately produces a singular matrix.
 *           We therefore solve the singular system using QR, and following
 *           Randy Bank's advice we ignore the degenerate eigen-direction
 *           (that component of the error is forcibly set to zero).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Aprx_estLocalProblem(Aprx *thee, SS *sm,
    Bvec *u, Bvec *ud, Bvec *f)
{
    Vnm_print(0,"Aprx_estLocalProblem: This estimator is broken badly.\n");
    Vnm_print(0,"Aprx_estLocalProblem: Use the residual estimator instead.\n");
    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_estGlobalWise
 *
 * Purpose:  Compute one of several element-wise error indicators.
 *
 * Notes:    Compute one of several error indicators, for all elements:
 *
 *               If (key == 5) ==> Recovered-gradient indicator.
 *               If (key == 6) ==> Face-bump error indicator.
 *
 * Author:   Michael Holst (updated by Ryan Szypowski)
 * ***************************************************************************
 */
VPUBLIC int Aprx_estGlobalWise(Aprx *thee, int key, int color,
    Bvec *u, Bvec *ud, Bvec *f, Bvec *r)
{
    /* input check and some i/o */
    switch (key) {
      case 5:
        Vnm_print(0,"Aprx_estRefine: using Aprx_estRecovGrad().\n");
        Aprx_estRecovGrad(thee, color, u, ud, r);
        break;
      case 6:
        Vnm_print(0,"Aprx_estRefine: using Aprx_estFaceBump().\n");
        Aprx_estFaceBump(thee, color, u, ud, r);
        break;
      default:
        VJMPERR1( 0 );
        break;
    }

    /* return with no errors */
    return 1; 

  VERROR1:
    Vnm_print(0,"Aprx_estGlobalWise: bad key given.\n");
    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_estElementWise
 *
 * Purpose:  Compute one of several element-wise error indicators.
 *
 * Notes:    Compute one of several error indicators, for all elements:
 *
 *               If (key == 2) ==> Nonlinear residual indicator.
 *               If (key == 3) ==> Dual-weighted residual indicator.
 *               If (key == 4) ==> Local problem indicator.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_estElementWise(Aprx *thee, int key, int color,
    Bvec *u, Bvec *ud, Bvec *f, Bvec *r)
{
    /* some variables */
    double errEst = 0.0;
    int    smid;
    SS     *sm;

    int doEffic = 1;
    double errExact = 0., effic = 0., efficTot = 0., minEffic = VLARGE, maxEffic = 0.;
    

    /* input check and some i/o */
    switch (key) {
      case 2:
        Vnm_print(0,"Aprx_estRefine: using Aprx_estNonlinResid().\n");
        break;
      case 3:
        Vnm_print(0,"Aprx_estRefine: using Aprx_estDualProblem().\n");
        break;
      case 4:
        Vnm_print(0,"Aprx_estRefine: using Aprx_estLocalProblem().\n");
        break;
      default:
        Vnm_print(0,"Aprx_estRefine: bad key given.\n");
        VJMPERR1( 0 );
        break;
    }

    /* traverse the simplices and estimate the error */
    smid = 0;
    while ( (smid < Gem_numSS(thee->gm)) && (!Vnm_sigInt()) ) {
        sm = Gem_SS(thee->gm,smid);

        if ((smid>0) && (smid % VPRTKEY) == 0) Vnm_print(0,"[MS:%d]",smid);
    
        /* produce an error estimate for this element if it is in the set */
        if ( ((int)SS_chart(sm)==color) || (color<0) ) {

            /* do the appropriate estimate for the element */
            if (key == 2) {
                errEst = Aprx_estNonlinResid(thee, sm, u,ud,f);
            } else if (key == 3) {
                errEst = Aprx_estDualProblem(thee, sm, u,ud,f);
            } else if (key == 4) {
                errEst = Aprx_estLocalProblem(thee, sm, u,ud,f);
            } else { VASSERT(0); }
            VASSERT( errEst >= 0. );

            /* store the estimate */
            Bvec_setB( thee->wev, 0, smid, errEst );

        /* otherwise store a zero for the estimate */
        } else {
            Bvec_setB( thee->wev, 0, smid, 0. );
        }

        if(doEffic) {
            /* compute the exact error on this element to keep track of efficiency */
	    errExact = Aprx_evalH1(thee, sm, u, ud, u);
	    effic = errEst / errExact;
	    efficTot += effic;
	    minEffic = VMIN2(minEffic, effic);
	    maxEffic = VMAX2(maxEffic, effic);
        }

        /* next sm */
        smid++;

    } /* el; loop over elements */

    if(doEffic) {
	Vnm_print(0, "\nMax elem effectivity = %f, Min elem effectivity = %f, Avg elem effectivity = %f\n", maxEffic, minEffic, efficTot/Gem_numSS(thee->gm));
    }

    /* return with no errors */
    return 1; 

  VERROR1:
    Vnm_print(0,"Aprx_estElementWise: bad key given.\n");
    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_estRefine
 *
 * Purpose:  A posteriori error estimation via several different approaches.
 *
 * Notes:    Apply one of several a posteriori error estimators:
 *
 *               If (key == 2) ==> Nonlinear residual indicator.
 *               If (key == 3) ==> Dual-weighted residual indicator.
 *               If (key == 4) ==> Local problem indicator.
 *               If (key == 5) ==> Recovered gradient indicator.
 *               If (key == 6) ==> Face-bump error indicator
 *
 *           The error tolerance can be used in several ways:
 *
 *               If (bkey == 0) ==> mark if:  [error/S] > TOL
 *               If (bkey == 1) ==> mark if:  [error/S] > (TOL^2/numS)^{1/2}
 *
 *               If (bkey == 2) ==> mark fixed number/fraction (dep. on ETOL): 
 *                   if elevel < 1, mark fraction of simplices
 *                   if elevel >=1, mark that many simplices (rounded to
 *                   the smaller integer)
 *
 * Author:   Michael Holst (updated by Ryan Szypowski)
 * ***************************************************************************
 */
VPUBLIC int Aprx_estRefine(Aprx *thee, int key, int color,
    int bkey, double elevel, Bvec *u, Bvec *ud, Bvec *f, Bvec *r)
{
    /* some variables */
    int i, smid, marked, count, currentQ;
    double minError = VLARGE;
    double maxError = 0.0;
    double errEst = 0.0;
    double mlevel,barrier;
    int ilevel = 0;
    SS     *sm;

    /* timer */
    Vnm_tstart(30, "error estimation");

    /* gerror = global error accumulation */
    thee->gerror = 0.;

    /* marked = num simplices marked for refinement (failed error test) */
    marked = 0;

    /* count = num generations to produce from marked simplices (minimally) */
    count = 1; /* must be >= 1 */

    /* set the barrier type */
    mlevel = (elevel*elevel) / Gem_numSS(thee->gm); 
    switch (bkey) {
      case 0:
        barrier = (elevel*elevel); 
        Vnm_print(0,"Aprx_estRefine: forcing [error/S] < [TOL] = %g\n",
            barrier);
        break;
      case 1:
        barrier = mlevel;
        Vnm_print(0,
            "Aprx_estRefine: forcing [error/S] < [(TOL^2/numS)^{1/2}] = %g\n",
            VSQRT(barrier));
        break;
      case 2:
        barrier = 0.0;
        if (elevel < 0.0) {
            VASSERT( 0 );
        } else if (elevel < 1.0) {
            ilevel = (int)(elevel * Gem_numSS(thee->gm));
            Vnm_print(0, "Aprx_estRefine: marking fixed fraction,");
            Vnm_print(0, "[AUTB*numS] = %d simplices\n", ilevel);
        } else if (elevel < Gem_numSS(thee->gm)) {
            ilevel = (int)elevel;
            Vnm_print(0, "Aprx_estRefine: marking fixed number of simplices,");
            Vnm_print(0, "[AUTB] = %d\n", ilevel);
        } else {
            Vnm_print(0, "Aprx_estRefine: number of simplices to be refined");
            Vnm_print(0, " [AUTB]=%d exceeds total number of simplices %d\n",
                (int)elevel, Gem_numSS(thee->gm));
            return marked;
        }
        break;
      case 3:
	barrier = elevel;
	Vnm_print(0, "Aprx_estRefine: refining based on Dorfler marking to mark %d%% of the error\n", (int) (barrier*100));
	break;
      default:
        Vnm_print(0,"Aprx_estRefine: bad bkey given; simplices marked = %d\n",
            marked);
        return marked;
        break;
    }

    /* firstly, estimate the error in some way */
    Vnm_print(0,"Aprx_estRefine: estimating error..");
    if ((2 <= key) && (key <= 4)) {
        VASSERT( Aprx_estElementWise(thee, key, color, u, ud, f, r) );
    } else if ((key >= 5) && (key <= 6)) {
        VASSERT( Aprx_estGlobalWise(thee, key, color, u, ud, f, r) );
    } else {
        VASSERT( 0 );
    }

    /* check the refinement Q for emptyness */
    currentQ = 0;
    if (Gem_numSQ(thee->gm,currentQ) > 0) {
        Vnm_print(0,"Aprx_estRefine: non-empty refinement Q%d....clearing..",
            currentQ);
        Gem_resetSQ(thee->gm,currentQ);
        Vnm_print(0,"..done.\n");
    }
    if (Gem_numSQ(thee->gm,!currentQ) > 0) {
        Vnm_print(0,"Aprx_estRefine: non-empty refinement Q%d....clearing..",
            !currentQ);
        Gem_resetSQ(thee->gm,!currentQ);
        Vnm_print(0,"..done.\n");
    }
    VASSERT( Gem_numSQ(thee->gm,currentQ)  == 0 );
    VASSERT( Gem_numSQ(thee->gm,!currentQ) == 0 );

    /* clear everyone's refinement flags */
    Vnm_print(0,"Aprx_estRefine: clearing all simplex refinement flags..");
    for (i=0; i<Gem_numSS(thee->gm); i++) {
        if ( (i>0) && (i % VPRTKEY) == 0 ) Vnm_print(0,"[MS:%d]",i);
        sm = Gem_SS(thee->gm,i);
        SS_setRefineKey(sm,currentQ,0);
        SS_setRefineKey(sm,!currentQ,0);
        SS_setRefinementCount(sm,0); /* refine X many times? */
    }
    Vnm_print(0,"..done.\n");

    /* if fixed number/fraction of simplices have to be refined */
    if (bkey == 2) {
        marked = Aprx_markRefineFixed (thee, ilevel, color);
        return marked;
    }

    if (bkey == 3) {
        marked = Aprx_markRefineDorfler (thee, barrier, color);
        return marked;
    }

    /* traverse simplices and look at error indicator for decision */
    smid = 0;
    while ( (smid < Gem_numSS(thee->gm)) && (!Vnm_sigInt()) ) {
        sm = Gem_SS(thee->gm,smid);

        if ((smid>0) && (smid % VPRTKEY) == 0) Vnm_print(0,"[MS:%d]",smid);
    
        /* look at error indicator for this element if it is in the set */
        if ( ((int)SS_chart(sm)==color) || (color<0) ) {

            /* do the appropriate estimate for the element */
            errEst = Bvec_valB( thee->wev, 0, smid );
            VASSERT( errEst >= 0. );

            /* if error estimate above tol, mark element for refinement */
            if ( errEst > barrier ) {
                marked++;
                Gem_appendSQ(thee->gm,currentQ, sm); /* add to refine Q  */
                SS_setRefineKey(sm,currentQ,1);      /* note on refine Q */
                SS_setRefinementCount(sm,count);     /* refine X times?  */
            }

            /* keep track of min/max errors over the mesh */
            minError = VMIN2( VSQRT(VABS(errEst)), minError );
            maxError = VMAX2( VSQRT(VABS(errEst)), maxError );

            /* accumlate into global error (errEst is SQUAREd already) */
            thee->gerror += errEst;
        }

        /* next sm */
        smid++;

    } /* el; loop over elements */

    /* final global error */
    thee->gerror = VSQRT(thee->gerror);

    /* do some i/o */
    Vnm_print(0,"..done.  [marked=<%d/%d>]\n",marked,Gem_numSS(thee->gm));
    Vnm_print(0,"Aprx_estRefine: TOL=<%g>  Global_Error=<%g>\n",
        elevel,thee->gerror);
    Vnm_print(0,"Aprx_estRefine: (TOL^2/numS)^{1/2}=<%g>  Max_Ele_Error=<%g>\n",
        VSQRT(mlevel),maxError);
    Vnm_tstop(30, "error estimation");

    /* check for making the error tolerance */
    if ((bkey == 1) && (thee->gerror <= elevel)) {
        Vnm_print(0,
          "Aprx_estRefine: *********************************************\n");
        Vnm_print(0,
          "Aprx_estRefine: Global Error criterion met; setting marked=0.\n");
        Vnm_print(0,
          "Aprx_estRefine: *********************************************\n");
        marked = 0;
    }

    /* return */
    return marked;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_estRecovGrad
 *
 * Purpose:  A posteriori error estimation via recovered gradient.
 *
 * Notes:    We implement a recovered gradient-type error indicator.
 *           The details are as follows:
 *
 *           (1) Given a piecewise-linear approximation u_h to the solution.
 *
 *           (2) Build a piecewise-linear "recovered gradient" approximation
 *               to each component of the piecwise-constant gradient grad u_h
 *               as follows:
 *
 *               For k=1,...,numVV, do:
 *
 *                  (a) Identify the 1-ring of n vertices around vertex v_k
 *
 *                  (b) Build the piecwise-linear approximation of the
 *                      piecewise-constant gradient within the support
 *                      region of this 1-ring, one component at a time,
 *                      by solving a small least squares problem of
 *                      the form:
 *
 *                          B^T B a = B f,
 *
 *                      where a=[a_0,a_1,...,a_d]^T are the coefficients
 *                      of the linear polynomial:
 *
 *                          p(x)=a_0 + a_1 x_1 + ... + a_d x_d.
 *
 *                      and where the matrix B and rhs f are as follows:
 *
 *                          B = [ 1, x_1^1, ..., x_d^1 ]
 *                              [ 1, x_1^2, ..., x_d^2 ]
 *                                          ...,
 *                              [ 1, x_1^n, ..., x_d^n ]  (n x [d+1] matrix)
 *
 *                          a = [ a_0, a_1, ..., a_d ]    ([d+1] x 1 vector)
 *
 *                          f = [ f_1, f_1, ..., f_n ]    (n x 1 vector)
 *
 *                      The n points used to form both B and f are the
 *                      n vertex locations in the 1-ring of vertices around
 *                      the current center vertex v_k.  I.e., B is as
 *                      specified above, whereas f is as follows:
 *
 *                          f = [ f(x^1), ..., f(x^n) ]
 *
 *                      where f = (u_h)_{x_i}, for fixed x_i.
 *                      By taking i=1,...,d, and solving each resulting
 *                      least squares system, we obtain piecewise-linear
 *                      scalar functions for each component of our
 *                      picewise-linear recovered gradient.
 *
 *           (3) Finally then, we compute the error in each simplex as
 *               simply the norm (squared) of the difference of the
 *               original gradient and the recovered gradient.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_estRecovGrad(Aprx *thee, int color,
    Bvec *u, Bvec *ud, Bvec *r)
{
    int    i, j, k, dim, numV, vxid, m, n, iComp, smid, iters, done;
    double v[50][3], b[50][4], bTb[4][4], f[50], bTf[4], a[4];
    double errEst, resid, rhs, tmp;
    VV     *vx;
    SS     *sm;

    /* hard-wired for scalar problems for now */
    VASSERT( PDE_vec(thee->pde) == 1 );

    /* get space for piecewise linear approx of gradient at the vertices */
    dim  = Gem_dim(thee->gm);
    numV = Gem_numVV(thee->gm);

    /* dimension of coefficient array (#cols in least-squares system) */
    n    = dim+1;
    VASSERT( n <= 4 );

    /* traverse the vertices to build the p-l recovered gradient */
    vxid = 0;
    while ( (vxid < Gem_numVV(thee->gm)) && (!Vnm_sigInt()) ) {
        vx = Gem_VV(thee->gm,vxid);
        if ((vxid>0) && (vxid % VPRTKEY) == 0) Vnm_print(0,"[MS:%d]",vxid);

        /* get coordinates of bari-centers of simplex ring (include center) */
        m = 0;
        for (i=0; i<Gem_dimII(thee->gm); i++) {
            v[m][i] = VV_coord(vx,i);
        }
        m++;
        for (sm=VV_firstSS(vx); sm!=VNULL; sm=SS_link(sm,vx)) {
            for (i=0; i<Gem_dimII(thee->gm); i++) {
                v[m][i] = 0.0;
                for (j=0; j<Gem_dimVV(thee->gm); j++) {
                    v[m][i] += VV_coord( SS_vertex(sm,j), i);
                }
                v[m][i] /= Gem_dimVV(thee->gm);
            }
            m++;
            VASSERT( m <= 50 );
        }

        /* double-check m (#rows in least-squares system) */
        VASSERT( m <= 50 );

        /* build the least-squares matrix b once and for all */
        for (i=0; i<m; i++) {
            b[i][0] = 1.0;
            for (j=1; j<n; j++) {
                b[i][j] = v[i][j-1];
            }
        }

        /* go ahead and build bTb */
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                bTb[i][j] = 0.0;
                for (k=0; k<m; k++) {
                    bTb[i][j] += b[k][i] * b[k][j];
                }
#if 0
                Vnm_print(2,"bTb[%d][%d]=<%g>\n", i, j, bTb[i][j]);
#endif
            }
        }

        /* for each comonent of the gradient build the p-l approximation */
        for (iComp=0; iComp<dim; iComp++) {

            /* only the rhs changes for each component; build it */
            for (i=0; i<m; i++) {
                f[i] = 1.0/(double)(i+1);
            }

            /* build bTf */
            for (i=0; i<n; i++) {
                bTf[i] = 0.0;
                for (j=0; j<m; j++) {
                    bTf[i] += b[j][i] * f[j];
                }
            }

            /* solve system for a:  bTb a = bTf */
            rhs = 0.0;
            for (i=0; i<n; i++) {
                a[i] = 0.0;
                rhs += bTf[i]*bTf[i];
            }
            VASSERT( rhs > 0 );
            rhs = VSQRT( rhs );
            iters = 0;
            done = 0;
            while ((iters < 1000) && (!done)) {
                for (i=0; i<n; i++) {
                    tmp = bTf[i];
                    for (j=0; j<n; j++) {
                        if (j != i) {
                            tmp -= (bTb[i][j] * a[j]);
                        }
                    }
                    a[i] = tmp / bTb[i][i];
                }
                resid = 0.0;
                for (i=0; i<n; i++) {
                    tmp = bTf[i];
                    for (j=0; j<n; j++) {
                        tmp -= (bTb[i][j] * a[j]);
                    }
                    resid += tmp*tmp;
                }
                resid = VSQRT( resid ) / rhs;
#if 0
                Vnm_print(2,"Aprx_estRecovGrad: resid=<%g>\n", resid);
#endif
                if (resid < 1.0e-5) {
                    done = 1;
                }
                iters++;
            }
            VASSERT( iters < 1000 );
#if 1
                Vnm_print(2,"Aprx_estRecovGrad: iters=<%d> resid=<%g>\n",
                    iters, resid);
#endif

            /* finally, evaluate p-l recovered gradient at central vertex */
            tmp = a[0];
            for (i=0; i<dim; i++) {
                tmp += a[i+1] * v[0][i];
            }
            Bvec_setB( r, 0, vxid, tmp );
        }

        /* next vx */
        vxid++;

    } /* loop over vertices */

    /* traverse the simplices and estimate the error */
    smid = 0;
    while ( (smid < Gem_numSS(thee->gm)) && (!Vnm_sigInt()) ) {
        sm = Gem_SS(thee->gm,smid);

        if ((smid>0) && (smid % VPRTKEY) == 0) Vnm_print(0,"[MS:%d]",smid);
    
        /* produce an error estimate for this element if it is in the set */
        if ( ((int)SS_chart(sm)==color) || (color<0) ) {

            /* do the appropriate estimate for the element */
            errEst = Aprx_estRecovGradSS(thee, sm, u, ud, r);
            VASSERT( errEst >= 0. );

            /* store the estimate */
            Bvec_setB( thee->wev, 0, smid, errEst );

        /* otherwise store a zero for the estimate */
        } else {
            Bvec_setB( thee->wev, 0, smid, 0. );
        }

        /* next sm */
        smid++;

    } /* el; loop over elements */
}

/*
 * ***************************************************************************
 * Routine:  Aprx_estRecovGradSS
 *
 * Purpose:  A posteriori error estimation via the nonlinear residual.
 *
 * Notes:    This is a nonlinear residual estimator in the style of Verfurth.
 *           In particular, this is an implementation of the nonlinear
 *           residual estimator derived in:
 *
 *               "Adaptive multilevel finite element methods on manifolds
 *                and their implementation in MC", by M. Holst.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Aprx_estRecovGradSS(Aprx *thee, SS *sm,
    Bvec *u, Bvec *ud, Bvec *r)
{
    /* some variables */
    int i, j, m, face;
    double Dw, errEst, nval, tmp;
    double xm[3], U[MAXV], dU[MAXV][3], R[MAXV], dR[MAXV][3];
    Re *re;
    TT t;

    /* initialize the error estimate for this element */
    errEst = 0.0;
        
    /* volume trans from master to this element (and back) */
     Gem_buildVolumeTrans(thee->gm,sm,&t);

    /* hard-code element for now... */
    re = thee->re[0];

    /* Cycle thru quad points */
    face = -1;
    for (m=0; m<Re_numQ_hi(re,face); m++) {

        /* jacobian and quadrature weight */
        Dw = t.D * Re_w_hi(re,m,face);

        /* evaluate solution/gradient at current quad point */
        Aprx_buildFunc(thee,re,&t,m,face,u,ud,xm,U,dU);

        /* evaluate solution/gradient at current quad point */
        Aprx_buildFunc(thee,re,&t,m,face,r,ud,xm,R,dR);

        /* indicator based on recovered gradient */
        VASSERT( Aprx_numB(thee) == 1 );
        nval = 0.;
        for (i=0; i<Aprx_numB(thee); i++) {
            for (j=0; j<Gem_dim(thee->gm); j++) {
#if 0
                tmp = (dU[i][j] - dR[i][j]);
#else
                tmp = (dU[i][j] - R[j]);
#endif
                nval += tmp*tmp;
            }
        }
        errEst += ( Dw * nval );

    } /* m; loop over volume quadrature points */
    errEst *= (t.D * t.D);

    /* returning the SQUARE of final residual indicator over the element */
    return VABS(errEst);
}

/*
 * ***************************************************************************
 * Routine:  Aprx_markRefineFixed
 *
 * Purpose:  This function is called by Aprx_markRefine if fixed number / 
 *           fraction of simplices <ilevel> has to be refined. Returns 
 *           number of marked elements.
 *
 * Author:   Oleg Korobkin, Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_markRefineFixed (Aprx *thee, int num2ref, int color) 
{
    int numSS, *iSS;
    int i, j, l, r, lt, rt, t, right;
    int marked, currentQ, count;
    double el, er, errEst;
    double minError = VLARGE;
    double maxError = 0.0;
    Gem *gm;
    SS *sm1, *sm2;

    gm = thee->gm;

    numSS = Gem_numSS(thee->gm);
    iSS = Vmem_malloc (thee->vmem, numSS, sizeof(int));

    /* check ilevel */
    VASSERT (num2ref > 0);
    VASSERT (num2ref < numSS);
    
    /* fill in initial simplex ordering (0,1,2 .. numSS-1) */
    for (i=0; i<numSS; i++) iSS[i] = i;

    /* set up initial indices for left, right and target position */
    lt = 0; 
    rt = numSS-1;
    t = num2ref - 1;
   
    Vnm_print (0, "Aprx_markRefineFixed: taking care of color marking...");
    if(color>=0) {
        /* sort indices of color elements to the beginning of iSS array */
        i = 0;
        sm1 = Gem_SS(gm,lt);
        sm2 = Gem_SS(gm,rt);
        while (lt<rt) {
            if((i>0) && (i % VPRTKEY) == 0) Vnm_print(0,"[MS:%d]",i);

            /* if left element has right color, shift left bracket */
            if ((int)SS_chart(sm1)==color) {
                sm1 = Gem_SS(gm, (++lt));

                /* keep track of min/max errors over the mesh */
                errEst = Bvec_valB( thee->wev, 0, lt );
                VASSERT( errEst >= 0. );
                minError = VMIN2( errEst, minError );
                maxError = VMAX2( errEst, maxError );
                thee->gerror += errEst;
            }

            /* if right element has wrong color, shift right bracket */
            if ((int)SS_chart(sm2)!=color) {
                sm2 = Gem_SS(gm, (--rt));
            }

            /* if left is not marked and right is marked, exchange their
               indices in iSS array, and shift both brackets */
            if (((int)SS_chart(sm1)!=color) && ((int)SS_chart(sm2)==color)) {
                /* keep track of min/max errors over the mesh */
                errEst = Bvec_valB( thee->wev, 0, rt );
                VASSERT( errEst >= 0. );
                minError = VMIN2( errEst, minError );
                maxError = VMAX2( errEst, maxError );
                thee->gerror += errEst;

                iSS[lt] = rt; 
                iSS[rt] = lt;
                ++lt; rt--;
                sm1 = Gem_SS(gm,lt);
                sm2 = Gem_SS(gm,rt);
            }
            i++;        
        }
        /* at this point, all relevant simplices have indices in [0,rt] */
        lt = 0;
        VASSERT( rt>=t );

    } else { 
        /* just find errorMax and errorMin */
        for(i=0; (i<numSS) && (!Vnm_sigInt()); i++) {
            if((i>0) && (i % VPRTKEY) == 0) Vnm_print(0,"[MS:%d]",i);
            errEst = Bvec_valB( thee->wev, 0, i );
            VASSERT( errEst >= 0. );
            minError = VMIN2( errEst, minError );
            maxError = VMAX2( errEst, maxError );
            thee->gerror += errEst;
        }
    }

    /* final errors */
    minError = VSQRT( minError );
    maxError = VSQRT( maxError );
    thee->gerror = VSQRT(thee->gerror);
    
    /* main loop of sorting routine */
    Vnm_print (0, "Aprx_markRefineFixed: quicksort..");
    i = 0; r = -1;
    while ((r != t) && (!Vnm_sigInt())) {
        r = rt; 
        l = lt;
        right = 0;
        el = Bvec_valB( thee->wev, 0, iSS[l]);
        er = Bvec_valB( thee->wev, 0, iSS[r]);
        while ((l<r) && (!Vnm_sigInt())) {
            if(right) {
                if(el<er) {
                    j = iSS[l]; iSS[l] = iSS[r]; iSS[r] = j;
                    r--;
                    right = 0;
                    el = er;
                    er = Bvec_valB( thee->wev, 0, iSS[r]);
                } else {
                    l++;
                    el = Bvec_valB( thee->wev, 0, iSS[l]);
                }
            } else {
                if(el<er) {
                    j = iSS[l]; iSS[l] = iSS[r]; iSS[r] = j;
                    l++;
                    right = 1;
                    er = el;
                    el = Bvec_valB( thee->wev, 0, iSS[l]);
                } else {
                    r--;
                    er = Bvec_valB( thee->wev, 0, iSS[r]);
                }
            } /* if(right) */
        } /* while (l<r) */
        if(l>t) rt = r-1;
        else    lt = l+1;

        if((i>0) && (i % VPRTKEY) == 0) Vnm_print(0,"[MS:%d]",i);
        i++;
    }
    Vnm_print(0,"..marking [%d] simplices..", num2ref);

    /* mark iSS[0], iSS[1], ..., iSS[t] for refinement */
    marked = 0;
    currentQ = 0;
    count = 1;
    for(i=0; (i<=t) && (!Vnm_sigInt()); i++) {
        if((i>0) && (i % VPRTKEY) == 0) Vnm_print(0,"[MS:%d]",i);
        sm1 = Gem_SS(gm, iSS[i]);
        marked++;
        Gem_appendSQ(thee->gm,currentQ, sm1); /* add to refine Q  */
        SS_setRefineKey(sm1,currentQ,1);      /* note on refine Q */
        SS_setRefinementCount(sm1,count);     /* refine X times?  */
    }

    /* do some i/o */
    Vnm_print(0,"..done.  [marked=<%d/%d>]\n",marked,numSS);
    Vnm_print(0,"Aprx_estRefine: Global_Error=<%g>\n",thee->gerror);
    Vnm_print(0,"Aprx_estRefine: Min_Ele_Error=<%g>\n",minError);
    Vnm_print(0,"Aprx_estRefine: Max_Ele_Error=<%g>\n",maxError);
    Vnm_tstop(30, "error estimation");

    /* free memory and return */
    Vmem_free (thee->vmem, numSS, sizeof(int), (void**)&iSS);
    return marked;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_markRefineDorfler
 *
 * Purpose:  This function is called by Aprx_markRefine if using Dorfler
 *           marking.  Returns number of marked elements.
 *
 * Author:   Ryan Szypowski, Oleg Korobkin, Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Aprx_markRefineDorfler (Aprx *thee, double percentToRefine,
				    int color) 
{
    int numSS;
    int *iSS;
    int *jSS;
    int i, temp, smid;
    int marked;
    int count, currentQ;
    double errEst;
    double minError = VLARGE;
    double maxError = 0.;
    double gerror = 0., gerror2 = 0.;
    double markedError;
    double heapmax, heapalpha;
    int heapstart, heapend, heapcurrstart, heapcurrend;
    SS *sm;

    numSS = Gem_numSS(thee->gm);
    iSS = Vmem_malloc (thee->vmem, numSS, sizeof(int));
    jSS = Vmem_malloc (thee->vmem, numSS, sizeof(int));

    /* check that the input makes sense */
    VASSERT(percentToRefine > 0.);
    VASSERT(percentToRefine <= 1.);
    
    /* find errorMax, errorMin, and gerror */
    for(i = 0; i < numSS; i++) {
	errEst = Bvec_valB(thee->wev, 0, i);
	VASSERT(errEst >= 0.);
	minError = VMIN2(errEst, minError);
	maxError = VMAX2(errEst, maxError);
	gerror += VSQRT(errEst);
	gerror2 += errEst;
    }

    /* final errors */
    minError = VSQRT(minError);
    maxError = VSQRT(maxError);
    thee->gerror = VSQRT(gerror2);

    /* fill in initial simplex ordering (0, 1, 2, ..., numSS - 1) */
    for(i = 0; i < numSS; i++) iSS[i] = i;

    /* heapify the simplices */
    Vnm_print (0, "Aprx_markRefineDorfler: starting heapification\n");

    heapstart = 0;
    heapend = numSS;

    /* find the max of the array */
    heapmax = 0.0;
    for (i = heapstart; i < heapend; i++) {
      if (Bvec_valB(thee->wev, 0, iSS[i]) > heapmax) {
        heapmax = Bvec_valB(thee->wev, 0, iSS[i]);
      }
    }

    for (heapalpha = 0.99; heapalpha > 0.001; heapalpha = 0.99*heapalpha) {
      /* put everything larger than (1.0 - heapalpha)*heapmax to the start of the array and the rest to the end */
      heapcurrstart = heapstart;
      heapcurrend = heapend;
      for (i = heapstart; i < heapend; i++) {
        if (Bvec_valB(thee->wev, 0, iSS[i]) > (1.0 - heapalpha)*heapmax) {
          jSS[heapcurrstart] = iSS[i];
          heapcurrstart++;
        }
        else {
          heapcurrend--;
          jSS[heapcurrend] = iSS[i];
        }
      }

      /* copy this from jSS back to iSS */
      for (i = heapstart; i < heapend; i++) {
        iSS[i] = jSS[i];
      }

      heapstart = 0;
      heapend = heapcurrstart;
    }

    /* // Below is the old n^2 sorting code
    i = 0;
    while (i < numSS) {
	if((i == 0) || (Bvec_valB(thee->wev, 0, iSS[i])
			<= Bvec_valB(thee->wev, 0, iSS[i - 1]))) {
	    i = i + 1;
	}
	else {
	    temp = iSS[i];
	    iSS[i] = iSS[i - 1];
	    iSS[i - 1] = temp;
	    i = i - 1;
	}
    }
    for(i = 0; i < numSS-1; i++) VASSERT(Bvec_valB(thee->wev, 0, iSS[i]) >= Bvec_valB(thee->wev, 0, iSS[i + 1]));
    */

    /* mark proper simplices for refinement */
    Vnm_print(0,"Aprx_markRefineDorfler: marking simplices...\n");
    marked = 0;
    markedError = 0.;
    currentQ = 0;
    count = 1;

    /* always refine at least one simplex */
    for(i = 0; (markedError < percentToRefine*gerror2) || (marked == 0); i++) {
	VASSERT(i < numSS);

	smid = iSS[i];
        sm = Gem_SS(thee->gm, smid);

        /* look at error indicator for this element if it is in the set */
        if ( ((int)SS_chart(sm) == color) || (color<0) ) {

            /* do the appropriate estimate for the element */
            errEst = Bvec_valB(thee->wev, 0, smid);

	    marked++;
	    markedError += errEst;

	    Gem_appendSQ(thee->gm, currentQ, sm); /* add to refine Q  */
	    SS_setRefineKey(sm, currentQ, 1);      /* note on refine Q */
	    SS_setRefinementCount(sm, count);     /* refine X times?  */
	}
    }

    /* do some i/o */
    Vnm_print(0, "...done.  [marked=<%d/%d> = %d%%]\n", marked, numSS,
	      (int) ((marked*100.)/numSS));
    Vnm_print(0, "Aprx_estRefine: Global_Error=<%g>\n", thee->gerror);
    Vnm_print(0, "Aprx_estRefine: Min_Ele_Error=<%g>\n", minError);
    Vnm_print(0, "Aprx_estRefine: Max_Ele_Error=<%g>\n", maxError);
    Vnm_tstop(30, "error estimation");

    /* free memory and return */
    Vmem_free (thee->vmem, numSS, sizeof(int), (void**)&iSS);
    Vmem_free (thee->vmem, numSS, sizeof(int), (void**)&jSS);

    return marked;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_estFaceBump
 *
 * Purpose:  A posteriori error estimation via face-bump error approximation.
 *
 * Notes:    We implement the error indicator in the paper:
 *
 *               "An efficient, reliable and robust error estimator
 *                for elliptic problems in \mathbb{R}^3", by M. Holst,
 *                J. Ovall, and R. Szypowski.
 *
 * Author:   Ryan Szypowski
 * ***************************************************************************
 */
VPUBLIC void Aprx_estFaceBump(Aprx *thee, int color,
    Bvec *u, Bvec *ud, Bvec *r_in)
{
    /* some variables */
    Re *re, *reB;
    int ip[10];
    double rp[10];

    int numB;
    int numR[MAXV], numO[MAXV][MAXV], *IJA[MAXV][MAXV];
    MATsym sym[MAXV][MAXV];
    MATmirror mirror[MAXV][MAXV];
    MATformat frmt[MAXV][MAXV];

    Bmat *A;
    Bvec *f, *e, *r, *ed;

    int smid;
    SS *sm, *sm1, *sm2;
    int eid, numS, numTS;
    EE *ee;
    VV *v1, *v2;
    TT t;
    double errEst;
    Emat em;

    double errExact, effic, efficTot = 0.;
    double minEffic = VLARGE;
    double maxEffic = 0;
    int doEffic = 0;
    int doPrint = 0;
    int doStats = 0;

    Vnm_print(0,"Aprx_estFaceBump: This only works for SCALAR LINEAR problems in 3D.\n");

    /* make sure we have a problem for which this should work */
    VASSERT ( PDE_vec(thee->pde) == 1 );
    /* there's no way to enforce that the problem is linear,
       so we just continue as if it is and scratch our head wondering what this
       does for nonlinear problems */

    /* the plan:
       1) assemble the RHS which represents F(v) - B(u, v)
          and assemble the the matrix represented by B(e, v)
       2) solve the system
       3) store the errors */

/* 1) assemble the RHS which represents F(v) - B(u, v)
      and assemble the the matrix represented by B(e, v) */

    /* build the matrix and vector structures */
    numB = Aprx_numB(thee);
    VASSERT(numB == 1);
    Aprx_interactBlock(thee, thee->reB, thee->reB,
		       sym, mirror, frmt, numR, numO, IJA);
    A = Bmat_ctor(thee->vmem, "A_b", numB, numR, numR, mirror);
    Bmat_initStructure(A, frmt, sym, numO, IJA);
    f = Bvec_ctor(thee->vmem, "f_b",  numB, numR);
    e = Bvec_ctor(thee->vmem, "e_b",  numB, numR);
    r = Bvec_ctor(thee->vmem, "r_b",  numB, numR);
    ed = Bvec_ctor(thee->vmem, "ed_b",  numB, numR);
    Bvec_init(ed, 0.);

    /* assemble the matrix */
    rp[0] = 1.0;
    Aprx_assem(thee,
	       /*eval*/ 1, /*energy*/ 0, /*resid*/ 1, /*tang*/ 1, /*mass*/ 0,
	       /*bump*/ 1,
	       ip, rp,
	       A, NULL, f, u, ud);

/* 2) solve the system */

    /* prec=0 for no preconditioner, prec=1 for diagonal scaling, prec = 3 for SGS */
    /* io=0 for output, io=1 for silence */
    Bvec_lmethod(e, A, f, r, /*NULL*/ ed, /*Au=f*/ 0, /*io*/ 0, /*itmax*/ 1000,
		 /*etol*/ 1.0e-8, /*prec*/ 3, /*cycle*/ 0, NULL, /*meth*/ 2 );

/* 3) store the errors */

    /* traverse the simplices and compute the norm of the error */
    thee->pde->initAssemble(thee->pde, ip, rp);
    smid = 0;
    while ( (smid < Gem_numSS(thee->gm)) && (!Vnm_sigInt()) ) {
        sm = Gem_SS(thee->gm, smid);

        if ((smid>0) && (smid % VPRTKEY) == 0) Vnm_print(0,"[MS:%d]",smid);
    
        /* produce an error estimate for this element if it is in the set */
        if ( ((int)SS_chart(sm)==color) || (color<0) ) {

            /* do the appropriate estimate for the element */
	    Gem_buildVolumeTrans(thee->gm, sm, &t);
	    Aprx_initEmat(thee, /*bump*/ 2, &t, &em);
	    thee->pde->initElement(thee->pde, t.stype, t.gchart, t.vx, &t);
	    Aprx_quadEmat(thee,
			  /*eval*/ 1, /*energy*/ 1, /*resid*/ 0, /*tang*/ 0, /*mass*/ 0,
			  /*bump*/ 2,
			  /*face*/ -1, &t, &em,
			  e, ed);
	    errEst = em.J;
            VASSERT(errEst >= 0.);

            /* store the estimate */
            Bvec_setB(thee->wev, 0, smid, errEst);

        /* otherwise store a zero for the estimate */
        } else {
            Bvec_setB(thee->wev, 0, smid, 0.);
        }

	if(doEffic) {
	    /* compute the exact error on this element to keep track of efficiency */
	    errExact = Aprx_evalH1(thee, sm, u, ud, ed);
	    effic = errEst / errExact;
	    efficTot += effic;
	    minEffic = VMIN2(minEffic, effic);
	    maxEffic = VMAX2(maxEffic, effic);
	}

        /* next sm */
        smid++;

    } /* el; loop over elements */

    if(doStats) {
      Gem_createEdges(thee->gm);
      Vnm_print(0, "\nNumber of: tets: %d, faces: %d, edges: %d, vertices: %d\n", Gem_numVirtSS(thee->gm), Gem_numVirtFF(thee->gm), Gem_numVirtEE(thee->gm), Gem_numVirtVV(thee->gm));
      numTS = 0;
      for(eid = 0; eid < Gem_numVirtEE(thee->gm); eid++) {
        ee = Gem_EE(thee->gm, eid);
        v1 = EE_vertex(ee, 0);
        v2 = EE_vertex(ee, 1);
        numS = 0;
        for (sm1 = VV_firstSS(v1); sm1 != VNULL; sm1 = SS_link(sm1, v1)) {
          for (sm2 = VV_firstSS(v2); sm2 != VNULL; sm2 = SS_link(sm2, v2)) {
            if (sm1 == sm2) {
              numS++;
            }
          }
        }
        numTS += 3*numS + 1; // Boundary edges should add 2 more
      }
      Vnm_print(0, "(Lower bound on) number of non-zeros in edge bump matrix: %d (vs. %d)\n", numTS, Gem_numVirtFF(thee->gm)*7 - Gem_numBF(thee->gm)*3);
    }

    if(doEffic) {
	Vnm_print(0, "\nMax elem effectivity = %f, Min elem effectivity = %f, Avg elem effectivity = %f\n", maxEffic, minEffic, efficTot/Gem_numSS(thee->gm));
    }

    if(doPrint) {
	Bmat_printSp(A, "A_file.m", 0);
    }

    /* clean up memory stuff */

    Bmat_dtor(&A);
    Bvec_dtor(&f);
    Bvec_dtor(&e);
    Bvec_dtor(&r);
    Bvec_dtor(&ed);
}
