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
 * rcsid="$Id: lsolv.c,v 1.51 2010/08/12 05:19:12 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     lsolv.c
 *
 * Purpose:  Class AM: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "am_p.h"

VEMBED(rcsid="$Id: lsolv.c,v 1.51 2010/08/12 05:19:12 fetk Exp $")

/*
 * ***************************************************************************
 * Class AM: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_NAM)

#endif /* if !defined(VINLINE_NAM) */
/*
 * ***************************************************************************
 * Class AM: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  AM_lSolve
 *
 * Purpose:  Linear solver.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_lSolve(AM *thee, int prob,
    int meth, int itmax, double etol, int prec, int gues, int pjac)
{
    /* assembly parameters */
    int key, flag, cycle, ip[10];
    int evalKey, energyKey, residKey, tangKey, massKey, bumpKey;
    double rp[10];
    Bvec *u_use;

    /* some i/o */
    Vnm_print(0,"AM_lSolve: starting..");

    /* make sure we have structure */
    AM_create(thee);

    /* setup for assembling either primal or dual problem */
    energyKey = 0;
    massKey   = 0;
    bumpKey = 0;
    if (prob == 0) {
        evalKey   = 0;    /* forward (primal) problem (linearized about 0) */
        residKey  = 1;
        tangKey   = 1;
        u_use     = thee->u;  /* solution (actual) ends up in "u" */
    } else if (prob == 1) {
        evalKey   = 2;    /* backward (dual) problem (linearized about 0) */
        residKey  = 1;
        tangKey   = 1;
        u_use     = thee->w0; /* solution (weights) ends up in "w0" */
    } else { VASSERT(0); }

    /* initial guess */
    if (gues == 0) {
        Vnm_print(0,"..using zero as initial approximation..\n");
        Bvec_init(u_use, 0.);
        AM_applyDiriZero( thee, u_use );
    } else if (gues == 1) {
        Vnm_print(0,"..using u_D as initial approximation..\n");
        AM_iniGuess( thee, u_use );
        AM_applyDiriZero( thee, u_use );
    } else {
        Vnm_print(0,"..using zero as initial approximation..\n");
        AM_iniGuess( thee, u_use );
        AM_applyDiriZero( thee, u_use );
    }

    /* clear the matrix, rhs, residual */
    Bmat_zero( thee->A );
    Bvec_init( thee->f,  0. );
    Bvec_init( thee->r,  0. );

    /* assemble the stiffness matrix and load vector */
    /* NOTE: we always linearize about W_u, regardless of u_use */
    rp[0] = 1.0; /* full load parameter for linear problems */
    AM_assem(thee,
        evalKey, energyKey, residKey, tangKey, massKey,
        bumpKey,
        thee->u, thee->ud, thee->f, ip, rp);
    if ((pjac == -2) || (pjac == 0)) AM_printAsp(thee, "jac.m");

    /* call the chosen linear solver */
    key   = 0; /* A u = f */
    flag  = 0; /* i/o flag */
    cycle = 2; /* symmetric multigrid */
    Bvec_lmethod( u_use, thee->A, thee->f, thee->r, thee->ut,
        key, flag, itmax, etol, prec, cycle, thee->P, meth );

    Vnm_print(0,"AM_lSolve: done.\n");

    /* return with no errors */
    return;
}

/*
 * ***************************************************************************
 * Routine:  AM_hlSolve
 *
 * Purpose:  Hierarchical linear solver.
 *
 * Author:   Burak Aksoylu, Stephen Bond, and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_hlSolve(AM *thee, int prob,
    int meth, int itmax, double etol, int prec, int gues, int pjac)
{
    /* assembly parameters */
    int key, flag, cycle, ip[10];
    int evalKey, energyKey, residKey, tangKey, massKey, bumpKey;
    double rp[10];
    Bvec *u_use;

    /* some i/o */
    Vnm_print(0,"AM_hlSolve: starting..\n");

    /* make sure we have structure */
    AM_create(thee);

    /* warn for suboptimal P */
    if (thee->P != VNULL) {
        if ( Bmat_impl(thee->P, 0, 0) != IS_IMPL ){
            Vnm_print(2,"AM_hlSolve:  Warning, storage not optimal.\n");
            Vnm_print(2,"AM_hlSolve:  Set pkey = 1 in Gem_refine !\n");
        }
    }

    /* setup for assembling either primal or dual problem */
    energyKey = 0;
    massKey   = 0;       /* Steve:  Change this later if we support WMHBMG */
    bumpKey = 0;
    if (prob == 0) {
        evalKey  = 0;    /* forward (primal) problem (linearized about 0) */
        residKey = 1;
        tangKey  = 1;
        u_use    = thee->u;    /* solution (actual) ends up in "u" */
    } else if (prob == 1) {
        evalKey   = 2;    /* backward (dual) problem (linearized about 0) */
        residKey  = 1;
        tangKey   = 1;
        u_use     = thee->w0;   /* solution (weights) ends up in "w0" */
    } else { VASSERT(0); }

    /* initial guess */
    if (gues == 0) {
        Vnm_print(0,"..using zero as initial approximation..\n");
        Bvec_init(u_use, 0.);
        AM_applyDiriZero( thee, u_use );
    } else if (gues == 1) {
        Vnm_print(0,"..using u_D as initial approximation..\n");
        AM_iniGuess( thee, u_use );
        AM_applyDiriZero( thee, u_use );
    } else {
        Vnm_print(0,"..using zero as initial approximation..\n");
        AM_iniGuess( thee, u_use );
        AM_applyDiriZero( thee, u_use );
    }

    /* clear the matrix, rhs, residual */
    Bmat_zero( thee->A );
    Bvec_init( thee->f,  0. );
    Bvec_init( thee->r,  0. );

    /* assemble the stiffness matrix and load vector */
    /* NOTE: we always linearize about W_u, regardless of W_u_use */
    rp[0] = 1.0; /* full load parameter for linear problems */
    AM_assem(thee,
        evalKey, energyKey, residKey, tangKey, massKey,
        bumpKey,
        thee->u, thee->ud, thee->f, ip, rp);
    if ((pjac == -2) || (pjac == 0)) AM_printAsp( thee, "jac.m" );

    /* call the chosen linear solver */
    key   = 0; /* A u = f */
    flag  = 0; /* i/o flag */
    cycle = 2; /* symmetric multigrid */
    Bvec_hlmethod( u_use, thee->A, thee->f, thee->r, thee->ut,
        key, flag, itmax, etol, prec, cycle, thee->P, thee->M, meth );

    Vnm_print(0,"AM_hlSolve: done.\n");

    /* return with no errors */
    return;
}

#if 0
/*
 * ***************************************************************************
 * Routine:  AM_hPbcg
 *
 * Purpose:  PBCG method (pure bi-orthogonal extension of PCG).
 *
 * Notes:    This is a pure Petrov-Galerkin formulation of the
 *           ODIR implementation of CG, and reduces to (exactly)
 *           the ODIR implementation of CG in the case of a
 *           symmetric (possibly indefinite) system matrix A and a
 *           symmetric (possibly indefinite) preconditioner B.
 *           (However, the operation count of BCG is rougly double
 *           that of CG.)
 *
 *           PG-ODIR(M,B,A) (for Au=f, preconditioner B, inner-product M)
 *           ------------------------------------------------------------
 *
 *           Given u^0
 *           r^0 = f - A  u^0
 *           s^0 = f - A' u^0
 *           p^0 = B r^0 / ||B r^0||
 *           q^0 = B's^0 / ||B's^0||
 *           for i=0,1,2,....
 *               alpha_i = <M e^i, q^i> / <M p^i, q^i>
 *               u^{i+1} = u^i + alpha_i p^i
 *               r^{i+1} = r^i - alpha_i A p^i
 *               gamma_i = <M B A p^i, q^i> / <M p^i, q^i>
 *               sigma_i = <M B A p^i, q^{i-1}> / <M p^{i-1}, q^{i-1}>
 *               delta_i = <M B A p^{i-1}, q^i> / <M p^{i-1}, q^{i-1}>
 *               v       = B A  p^i - gamma_i p^i - sigma_i p^{i-1}
 *               w       = B'A' q^i - gamma_i q^i - delta_i q^{i-1}
 *               p^{i+1} = v / ||v||
 *               q^{i+1} = w / ||w||
 *           end for
 *
 *           BCG=PG-ODIR(M=A,B=B,A=A)
 *           ------------------------
 *           Given u^0
 *           r^0 = f - A  u^0
 *           s^0 = f - A' u^0
 *           p^0 = B r^0 / ||B r^0||
 *           q^0 = B's^0 / ||B's^0||
 *           for i=0,1,2,....
 *               alpha_i = <r^i, q^i> / <A p^i, q^i>
 *               u^{i+1} = u^i + alpha_i p^i
 *               r^{i+1} = r^i - alpha_i A p^i
 *               gamma_i = <B A p^i, A' q^i> / <A p^i, q^i>
 *               sigma_i = <B A p^i, A' q^{i-1}> / <A p^{i-1}, q^{i-1}>
 *               delta_i = <B A p^{i-1}, A' q^i> / <A p^{i-1}, q^{i-1}>
 *               v       = B A  p^i - gamma_i p^i - sigma_i p^{i-1}
 *               w       = B'A' q^i - gamma_i q^i - delta_i q^{i-1}
 *               p^{i+1} = v / ||v||
 *               q^{i+1} = w / ||w||
 *           end for
 *
 * Input:    The "flag" variable determines which "mode" we run in:
 *
 *           flag==0 --> Normal: check itmax, error tolerance; normal i/o
 *           flag==1 --> Silent: check only itmax; no i/o
 *           flag==2 --> Subcycle: check itmax, error tolerance; subcycle i/o
 *           flag==3 --> Subcycle: check itmax, error tolerance; no i/o
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_hPbcg(AM *thee,
    int lev, int key, int flag, int itmax, double etol, int meth,
    int uu, int ff, int rr, int dd, int ut)
{
    int minLev, iters;
    double denom,rsnrm;
    double alpha,gamma,sigma,delta,normal;
    double rq,Apq,Apoqo,BApAtq,BApAtqo,BApoAtq;
    int p, pnumR[MAXV];
    Alg *ta = AM_alg(thee,lev);
    Bvec *Wu = ta->W[uu], *Wf = ta->W[ff], *Wr = ta->W[rr];
    Bvec *Wd = ta->W[dd];
    Bvec *Wp, *Wap, *Wapo, *Wpo, *Wbapo, *Wbap, *Ws;
    Bvec *Wq, *Watq, *Wqo, *Watqo, *Wbtatq, *Ww;
    HBmat *Ahb = VNULL, *Ghb = VNULL;
    HBvec *whb = VNULL, *dhb = VNULL;
    HBvec *aphb = VNULL, *atqhb = VNULL, *shb = VNULL;

    char rn[80];
    if (flag==2) {
        strncpy(rn,"--->AM_pbcg:",80);
    } else {
        strncpy(rn,"AM_pbcg:",80);
    }

    /* iteration parameters */
    iters   = 0;
    denom   = 0.0;
    rsnrm   = 0.0;
    alpha   = 0.0;
    gamma   = 0.0;
    sigma   = 0.0;
    normal  = 1.0;
    rq      = 0.0;
    Apq     = 0.0;
    Apoqo   = 0.0;
    BApAtq  = 0.0;
    BApAtqo = 0.0;
    BApoAtq = 0.0;

    /* determine the dimensions of the work vectors */
    for( p = 0; p < Bmat_numB( ta->A ); p++ ) {
        pnumR[p] = Bmat_numR( ta->A, p, p );
    }

    /* create a couple temporary work vectors */
    Ws   = Bvec_ctor( ta->vmem, "s", Bmat_numB(ta->A), pnumR );
    Bvec_init( Ws, 0.0 );

    /* DO: r^0 = f - A u^0 */
    Bvec_matvec( Wr, ta->A, Wu, key);
    Bvec_axpy( Wr, Wf, (-1.0) );
    Bvec_scal( Wr, (-1.0) );

    /* DO: s^0 = f - A' u^0 */
    Bvec_matvec( Ws, ta->A, Wu, !key);
    Bvec_axpy( Ws, Wf, (-1.0) );
    Bvec_scal( Ws, (-1.0) );

    /* calculate the lowest level accessed by the Vcycle */
    minLev = Alg_hbminLev( ta, thee->minLevel );

    /* stabilize the working blocks */
    Alg_hbPreproc( ta, &Ahb, &Ghb, &dhb, Wd, &shb, Ws, minLev, meth );

    /* create the remaining temporary vectors */
    Wp   = Bvec_ctor( ta->vmem, "p",   Bmat_numB(ta->A), pnumR );
    Bvec_init( Wp, 0.0 );
    Wq   = Bvec_ctor( ta->vmem, "q",   Bmat_numB(ta->A), pnumR );
    Bvec_init( Wq, 0.0 );
    Wap  = Bvec_ctor( ta->vmem, "ap",  Bmat_numB(ta->A), pnumR );
    Bvec_init( Wap, 0.0 );
    Wapo  = Bvec_ctor( ta->vmem, "apo",  Bmat_numB(ta->A), pnumR );
    Bvec_init( Wapo, 0.0 );
    Watq  = Bvec_ctor( ta->vmem, "atq",  Bmat_numB(ta->A), pnumR );
    Bvec_init( Watq, 0.0 );
    Wpo  = Bvec_ctor( ta->vmem, "po",  Bmat_numB(ta->A), pnumR );
    Bvec_init( Wpo, 0.0 );
    Wqo  = Bvec_ctor( ta->vmem, "qo",  Bmat_numB(ta->A), pnumR );
    Bvec_init( Wqo, 0.0 );
    Watqo  = Bvec_ctor( ta->vmem, "atqo",  Bmat_numB(ta->A), pnumR );
    Bvec_init( Watqo, 0.0 );
    Wbapo = Bvec_ctor( ta->vmem, "bapo", Bmat_numB(ta->A), pnumR );
    Bvec_init( Wbapo, 0.0 );
    Wbap  = Bvec_ctor( ta->vmem, "bap",  Bmat_numB(ta->A), pnumR );
    Bvec_init( Wbap, 0.0 );
    Wbtatq  = Bvec_ctor( ta->vmem, "btatq",  Bmat_numB(ta->A), pnumR );
    Bvec_init( Wbtatq, 0.0 );
    Ww   = Bvec_ctor( ta->vmem, "wrk", Bmat_numB(ta->A), pnumR );
    Bvec_init( Ww, 0.0 );

    /* create hierarchical pointers for a few of the work vectors */
    aphb = HBvec_ctor( ta->vmem, "aphb", lev, ta->A->numB );
    aphb->bv = Wap;
    HBvec_initStructure( aphb, ta, minLev );
    atqhb = HBvec_ctor( ta->vmem, "atqhb", lev, ta->A->numB );
    atqhb->bv = Watq;
    HBvec_initStructure( atqhb, ta, minLev );
    whb = HBvec_ctor( ta->vmem, "whb", lev, ta->A->numB );
    whb->bv = Ww;
    HBvec_initStructure( whb, ta, minLev );

    /* DO: for i=0,1,2,.... */
    iters = 0;
    while (!Vnm_sigInt()) {

        if ( flag!=1 ) {
            /* calculate norm of current residual, setup for i/o */
            rsnrm = Bvec_nrm2( Wr );
            if (iters == 0) {
                denom = rsnrm;
            }
            Vnm_print(0,"AM_hPbcg: it=%4d",iters);
            Vnm_print(0,"  rr=%12.6e  r=%8.2e\n", rsnrm/denom, rsnrm);
        }

        /* check stopping criteria */
        if ( (flag!=1) && (rsnrm/denom <= etol) ) {
            goto DONE;
        }

        /* form new direction vector */
        if ( iters == 0 ) {

            /* DO: (form: B r^0) */
            Bvec_copy( Wap, Wr );           /* copy rr -> ap */
            Bvec_init( Wd, 0.0 );           /* initial guess must be zero */
            HBvec_hbVcyc( dhb, Ahb, aphb, Ghb, minLev, whb, key, 2 );
            Bvec_axpy( Wp, Wd, 1.0 );       /* p = p + d */
#ifdef REDUCE_PBCG_TO_BCG
            Bvec_copy( Wp, Wr );
#endif
            /* DO: p^0 = B r^0 / ||B r^0|| */
            normal = Bvec_nrm2( Wp );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( Wp, normal );

            /* DO: (form: B' s^0) */
            Bvec_copy( Watq, Ws );          /* copy ss -> atq */
            Bvec_init( Wd, 0.0 );           /* initial guess must be zero */
            HBvec_hbVcyc( dhb, Ahb, atqhb, Ghb, minLev, whb, !key, 2 );
            Bvec_axpy( Wq, Wd, 1.0 );       /* q = q + d */
#ifdef REDUCE_PBCG_TO_BCG
            Bvec_copy( Wq, Ws );
#endif
            /* DO: q^0 = B' s^0 / ||B' s^0|| */
            normal = Bvec_nrm2( Wq );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( Wq, normal );

        } else {

            /* DO: (form: B A p^i) */
            Bvec_matvec( Ws, ta->A, Wbap, key );
            Bvec_axpy( Ws, Wap, (-1.0) ); /* s = A*bap - ap */
            Bvec_init( Wd, 0.0 );           /* initial guess must be zero */
            HBvec_hbVcyc( dhb, Ahb, shb, Ghb, minLev, whb, key, 2 );
            Bvec_axpy( Wbap, Wd, (-1.0) ); /* bap -= d */
#ifdef REDUCE_PBCG_TO_BCG
            Bvec_copy( Wbap, Wap );
#endif
            /* DO: (form: B'A' q^i) */
            Bvec_matvec( Ws, ta->A, Wbtatq, !key );
            Bvec_axpy( Ws, Watq, (-1.0) ); /* s = A*btatq - atq */
            Bvec_init( Wd, 0.0 );           /* initial guess must be zero */
            HBvec_hbVcyc( dhb, Ahb, shb, Ghb, minLev, whb, !key, 2 );
            Bvec_axpy( Wbtatq, Wd, (-1.0) ); /* btatq -= d */
#ifdef REDUCE_PBCG_TO_BCG
            Bvec_copy( Wbtatq, Watq );
#endif
            /* DO: gamma_i = <B A p^i, A' q^i> / <A p^i, q^i> */
            BApAtq = Bvec_dot( Wbap, Watq );
            gamma  = BApAtq / Apq;

            /* DO: sigma_i = <B A p^i, A' q^{i-1}> / <A p^{i-1}, q^{i-1}> */
            if ( iters == 1 ) {
                sigma = 0.0;
            } else {
                BApAtqo = Bvec_dot( Wbap, Watqo );
                sigma   = BApAtqo / Apoqo;
            }

            /* DO: delta_i = < A p^{i-1}, B' A' q^i> / <A p^{i-1}, q^{i-1}> */
            if ( iters == 1 ) {
                delta = 0.0;
            } else {
                BApoAtq = Bvec_dot( Wapo, Wbtatq );
                delta = BApoAtq / Apoqo;
            }

            /* DO: v = B A p^i - gamma_i p^i - sigma_i p^{i-1} */
            Bvec_copy( Wbapo, Wbap );
            Bvec_axpy( Wbap, Wp, (-gamma) );
            Bvec_axpy( Wbap, Wpo, (-sigma) );
            Bvec_copy( Wpo, Wp );
            Bvec_copy( Wp, Wbap );

            /* DO: p^{i+1} = v / ||v|| */
            normal = Bvec_nrm2( Wp );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( Wp, normal );

            /* DO: w = B'A' q^i - gamma_i q^i - delta_i q^{i-1} */
            Bvec_copy( Watqo, Watq );
            Bvec_axpy( Wbtatq, Wq, (-gamma) );
            Bvec_axpy( Wbtatq, Wqo, (-delta) );
            Bvec_copy( Wqo, Wq );
            Bvec_copy( Wq, Wbtatq );

            /* DO: q^{i+1} = w / ||w|| */
            normal = Bvec_nrm2( Wq );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( Wq, normal );
        }

        /* DO: alpha_i = <r^i, q^i> / <A p^i, q^i> */
        Bvec_copy( Wapo, Wap );
        Bvec_matvec( Wap, ta->A, Wp, key );
        Bvec_matvec( Watq, ta->A, Wq, !key );
        Apoqo = Apq;
        Apq   = Bvec_dot( Wap, Wq );
        if ( VABS(Apq) < VSMALL ) {
            Vnm_print(0,"%s (Ap,q)=%e (rr=%e)\n", rn, Apq, rsnrm/denom);
            Vnm_print(0,"%s Hitting the roundoff wall...returning.\n",rn);
            goto DONE;
        }
        rq    = Bvec_dot( Wr, Wq );
        alpha = rq / Apq;

        /* DO: u^{i+1} = u^i + alpha_i p^i */
        Bvec_axpy( Wu, Wp, alpha );

        /* DO: r^{i+1} = r^i - alpha_i A p^i */
        Bvec_axpy( Wr, Wap, (-alpha) );

        /* iterate */
        iters++;

        if (iters >= itmax ) {
            goto DONE;
        }
    }

DONE:
    /* deallocate extra blocks created in Alg_hbPreproc */
    Alg_hbPostproc( ta, &Ahb, &Ghb, &dhb, &shb, minLev );
    /* destruct hierarchical pointers for a few of the work vectors */
    HBvec_killStructure( aphb, minLev );
    HBvec_dtor( &aphb );
    HBvec_killStructure( atqhb, minLev );
    HBvec_dtor( &atqhb );
    HBvec_killStructure( whb, minLev );
    HBvec_dtor( &whb );
    /* destroy work vectors */
    Bvec_dtor( &Ws );
    Bvec_dtor( &Wp );
    Bvec_dtor( &Wq );
    Bvec_dtor( &Wap );
    Bvec_dtor( &Wapo );
    Bvec_dtor( &Watq );
    Bvec_dtor( &Wpo );
    Bvec_dtor( &Wqo );
    Bvec_dtor( &Watqo );
    Bvec_dtor( &Wbapo );
    Bvec_dtor( &Wbap );
    Bvec_dtor( &Wbtatq );
    Bvec_dtor( &Ww );
}

#endif

