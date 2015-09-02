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
 * rcsid="$Id: bvechb.c,v 1.8 2010/08/12 05:19:20 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     bvechb.c
 *
 * Purpose:  Class Whb: Bvec interface to HB methods.
 *
 * Author:   Burak Aksoylu, Stephen Bond, and Michael Holst
 * ***************************************************************************
 */

#include "bvechb_p.h"

VEMBED(rcsid="$Id: bvechb.c,v 1.8 2010/08/12 05:19:20 fetk Exp $")

#undef REDUCE_PBCG_TO_BCG

/*
 * ***************************************************************************
 * Class Whb: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_WHB)

#endif /* if !defined(VINLINE_WHB) */
/*
 * ***************************************************************************
 * Class Whb: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Bvec_hlmethod
 *
 * Purpose:  Executes one of a number of hierarchical linear solvers.
 *
 * Author:   Stephen Bond 2007/09/24
 * ***************************************************************************
 */
VPUBLIC void Bvec_hlmethod(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bmat *M, int meth)
{
    Bvec *w[11];
    Bvec *u = thee;

    if ((flag==0) || (flag==2)) {
        Vnm_tstart(40, "linear solve");
    }

    /* method choice (0=slu,1=mg,2=cg,3=bcg) */
    switch (meth) {

        /* primary methods */
        case 0:  Bvec_slu( u, A, f, r, ut, key, flag);
                 break;
        case 1:  Bvec_hb( u, A, f, r, ut, key, flag, itmax, etol, prec, P, M);
                 break;
        case 2:  Bvec_createVectors( thee, w, 6);
                 Bvec_hcg( u, A, f, r, ut, key, flag, itmax, etol, prec, P, M,
                     w[0], w[1], w[2], w[3] ,w[4], w[5]);
                 Bvec_destroyVectors(thee, w, 6);
                 break;
        case 3:  Bvec_createVectors( thee, w, 11);
                 Bvec_hbcg(u, A, f, r, ut, key, flag, itmax, etol, prec, P, M,
                     w[0],w[1],w[2],w[3],w[4],w[5],w[6],w[7],w[8],w[9],w[10]);
                 Bvec_destroyVectors(thee, w, 11);
                 break;
        default:
                 /* bad choice */
                 Vnm_print(0,"Bvec_hlmethod: Bad meth given!\n");
                 break;
    }

    if ((flag==0) || (flag==2)) {
        Vnm_tstop(40, "linear solve");
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_hb
 *
 * Purpose:  HBMG algorithm due to Bank, Dupont, and Yserentant
 *
 * Notes:    The MODES in which this routine operates are:
 *
 *           key=0    --> solve Au=f
 *           key=1    --> solve A'u=f
 *
 *           flag==0  --> Normal: check itmax, error tolerance; normal i/o
 *           flag==1  --> Normal: check itmax; no error tolerance; no i/o
 *
 *           csolv==0 --> nonsymmetric HB
 *           csolv==1 --> adjoint of nonsymmetric HB
 *           csolv==2 --> symmetric HB
 *
 *           prec==3  --> Standard HB
 *           prec==5  --> Wavelet Modified HB
 *
 * Author:   Burak Aksoylu and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bvec_hb(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, Bmat *Ppro, Bmat *M)
{
    int iters, csolv = 0, numB, meth;
    double rsnrm, denom;
    Bvec *u = thee, *ww[2];
    HBmat *Ahb = VNULL, *Ghb = VNULL;
    HBvec *w1hb = VNULL, *rhb = VNULL, *dhb = VNULL;

    if( 3 == prec ) {
        meth = 0;
    } else if ( 5 == prec ) {
        meth = 1;
    } else {
        VASSERT(0);
    }

    /* fix this later */
    Bvec_createVectors( thee, ww, 2);

    /* create multilevel matrix structure */
    numB = Bmat_numB( A );
    HBmat_initMulti( &Ahb, &Ghb, A, M, Ppro, meth );

    /* create multilevel work vectors */
    dhb = HBvec_ctor( thee->vmem, "dhb", numB );
    dhb->bv = ww[0];
    HBvec_initStructure( dhb, Ahb );

    w1hb = HBvec_ctor( thee->vmem, "w1hb", numB );
    w1hb->bv = ww[1];
    HBvec_initStructure( w1hb, Ahb );

    rhb = HBvec_ctor( thee->vmem, "rhb", numB );
    rhb->bv = r;
    HBvec_initStructure( rhb, Ahb );

    /* initialize basic iteration quantities and iterate */
    iters = 0; rsnrm = 1.0; denom = 1.0;
    while (!Vnm_sigInt()) {

        /* calculate the residual: (-r) = A u - f */
        Bvec_matvec( r, A, u, key, 0 );
        Bvec_axpy( r, f, -1.0 );

        if (flag!=1) {
            /* calculate norm of current residual, setup for i/o */
            rsnrm = Bvec_nrm2( r );

            if (iters == 0) {
                denom = rsnrm;
            }
            Vnm_print(0,"Bvec_hb: it=%4d",iters);
            Vnm_print(0,"  rr=%12.6e  r=%8.2e\n", rsnrm/denom, rsnrm);
        }

        /* check stopping criteria */
        if ( (flag!=1) && (rsnrm/denom <= etol) ) {
            goto DONE;
        }

        /* call hbVcycle to approximate solution of A*(-d) = (-r) */
        Bvec_init(ww[0], 0. ); /* initial guess must be zero */
        HBvec_hbVcyc( dhb, Ahb, rhb, Ghb, w1hb, key, csolv );
        Bvec_axpy( u, ww[0], (-1.0) );  /* u = u + (-d) */

        /* iterate */
        iters++;

        if (iters >= itmax) {
            goto DONE;
        }

    } /* end of while */

 DONE:
    Bvec_destroyVectors(thee, ww, 2);

    /* destroy multilevel vectors */
    HBvec_killStructure( w1hb );
    HBvec_dtor( &w1hb );

    HBvec_killStructure( dhb );
    HBvec_dtor( &dhb );

    HBvec_killStructure( rhb );
    HBvec_dtor( &rhb );

    /* destroy multilevel matrix structure */
    HBmat_killMulti( &Ahb, &Ghb );
    return;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_hcg
 *
 * Purpose:  CG method with Bvec_hb as an optional preconditioner.
 *
 * Notes:    This is an exact copy of Bvec_cg with Bvec_mg -> Bvec_hb
 *
 * Input:    The "flag" variable determines which "mode" we run in:
 *
 *           flag==0 --> Normal: check itmax, error tolerance; normal i/o
 *           flag==1 --> Silent: check only itmax; no i/o
 *           flag==2 --> Subcycle: check itmax, error tolerance; subcycle i/o
 *           flag==3 --> Subcycle: check itmax, error tolerance; no i/o
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bvec_hcg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, Bmat *P, Bmat *M,
    Bvec *p, Bvec *ap, Bvec *bap, Bvec *po, Bvec *apo, Bvec *tp)
{
    int iters;
    double denom,rsnrm,ernrm2,ernrm8,erden2,erden8;
    double alpha,gamma,sigma,rp,pAp,poApo,BApAp,BApApo,normal;
    int key_m,flag_m,itmax_m,prec_m,cycle_m;
    double etol_m;
    Bvec *u = thee;

    int prtKey = VPRTKEY;
    char rn[80], rmeth[80];

    if (prec == 0) {
        strncpy(rmeth,":",80);
    } else if (prec == 1) {
        strncpy(rmeth,"(ds):",80);
    } else if (prec == 3) {
        strncpy(rmeth,"(hb):",80);
    } else if (prec == 5) {
        strncpy(rmeth,"(wmhb):",80);
    } else {
        strncpy(rmeth,":",80);
    }
    if (flag==2) {
        sprintf(rn,"--->Bvec_hcg%s",rmeth);
        prtKey = 50;
    } else {
        sprintf(rn,"Bvec_hcg%s",rmeth);
        prtKey = 1;
    }

    /* iteration parameters */
    iters   = 0;
    denom   = 0.0;
    rsnrm   = 0.0;
    ernrm2  = 0.0;
    ernrm8  = 0.0;
    erden2  = 0.0;
    erden8  = 0.0;
    alpha   = 0.0;
    gamma   = 0.0;
    sigma   = 0.0;
    rp      = 0.0;
    pAp     = 0.0;
    poApo   = 0.0;
    BApAp   = 0.0;
    BApApo  = 0.0;
    normal  = 1.0;

    /* DO: r^0 = f - A u^0 */
    Bvec_matvec( r, A, u, key, 0 );
    Bvec_axpy( r, f, (-1.0) );
    Bvec_scal( r, (-1.0) );

    /* DO: for i=0,1,2,.... */
    iters = 0;
    while (!Vnm_sigInt()) {

        /* calculate norm of current residual, setup for i/o */
        rsnrm = Bvec_nrm2( r );
        if (iters == 0) {
            denom = rsnrm;
            if ( rsnrm == 0.0 ) {
                Vnm_print(0,"%sinitial residual=%8.2e\n", rn, rsnrm);
                Vnm_print(0,"%sinitial residual is zero...returning.\n", rn);
                return;
            }
        }

        /* if the main solver, do some i/o */
        if ( ((flag==0) || (flag==2))
           && (((iters%prtKey)==0) || (rsnrm/denom<=etol)) ) {
            ernrm2 = Bvec_dif2( u, ut );
            ernrm8 = Bvec_dif8( u, ut );
            if (iters == 0) {
                Vnm_print(0,"%sinitial residual=%8.2e\n", rn, rsnrm);
                erden2 = Bvec_nrm2( ut );
                erden8 = Bvec_nrm8( ut );
                if (erden2 == 0.0) erden2 = 1.0;
                if (erden8 == 0.0) erden8 = 1.0;
            }
            Vnm_print(0,"%s it=%4d",rn,iters);
            Vnm_print(0,"  rr=%8.2e  r=%8.2e  re2=%8.2e  re8=%8.2e\n",
                rsnrm/denom, rsnrm, ernrm2/erden2, ernrm8/erden8);
        }

        /* check stopping criteria */
        if ( rsnrm/denom <= etol ) return;
        if ( iters >= itmax ) {
            if ( (flag==0) || (flag==2) )
                Vnm_print(0,"%s itmax reached! (rr=%e)\n", rn, rsnrm/denom);
            return;
        }

        /* form new direction vector */
        if ( iters == 0 ) {

            /* DO: (form: B r^0) */
            if (prec == 0) {
                Bvec_copy( p, r );
            } else if (prec == 1) {
                Bvec_diagScale(p, A, r);
            } else if (prec == 3 || prec == 5) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_hb(p, A, r, tp, ut,
                     key_m, flag_m, itmax_m, etol_m, prec_m, P, M);
            } else {
                Bvec_copy( p, r );
            }

            /* DO: p^0 = B r^0 / ||B r^0|| */
            normal = Bvec_nrm2( p );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( p, normal );

        } else {
            /* DO: (form: B A p^i) */
            if (prec == 0) {
                Bvec_copy( bap, ap );
            } else if (prec == 1) {
                Bvec_diagScale(bap, A, ap);
            } else if (prec == 3 || prec == 5) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_hb(bap, A, ap, tp, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, P, M);
            } else {
                Bvec_copy( bap, ap );
            }

            /* DO: gamma_i = <B A p^i, A p^i> / <A p^i, p^i> */
            BApAp = Bvec_dot( bap, ap );
            gamma = BApAp / pAp;

            /* DO: sigma_i = <B A p^i, A p^{i-1}> / <A p^{i-1}, p^{i-1}> */
            if ( iters == 1 ) {
                sigma = 0.0;
            } else {
                BApApo = Bvec_dot( bap, apo );
                sigma = BApApo / poApo;
            }

            /* DO: v = B A p^i - gamma_i p^i - sigma_i p^{i-1} */
            Bvec_copy( apo, ap );
            Bvec_axpy( bap, p, (-gamma) );
            Bvec_axpy( bap, po, (-sigma) );
            Bvec_copy( po, p );
            Bvec_copy( p, bap );

            /* DO: p^{i+1} = v / ||v|| */
            normal = Bvec_nrm2( p );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( p, normal );
        }

        /* DO: alpha_i = <r^i, p^i> / <A p^i, p^i> */
        Bvec_matvec( ap, A, p, key, 0 );
        poApo = pAp;
        pAp   = Bvec_dot( p, ap );
        rp    = Bvec_dot( r, p );
        alpha = rp / pAp;

        /* DO: u^{i+1} = u^i + alpha_i p^i */
        Bvec_axpy( u, p, alpha );

        /* DO: r^{i+1} = r^i - alpha_i A p^i */
        Bvec_axpy( r, ap, (-alpha) );

        /* iterate */
        iters++;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_hbcg with Bvec_hb as an optional preconditioner.
 *
 * Purpose:  BCG method
 *
 * Notes:    This is an exact copy of Bvec_bcg with Bvec_mg -> Bvec_hb
 *
 * Input:    The "flag" variable determines which "mode" we run in:
 *
 *           flag==0 --> Normal: check itmax, error tolerance; normal i/o
 *           flag==1 --> Silent: check only itmax; no i/o
 *           flag==2 --> Subcycle: check itmax, error tolerance; subcycle i/o
 *           flag==3 --> Subcycle: check itmax, error tolerance; no i/o
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bvec_hbcg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, Bmat *P, Bmat *M,
    Bvec *s,
    Bvec *p, Bvec *ap, Bvec *bap, Bvec *po, Bvec *apo,
    Bvec *q, Bvec *atq, Bvec *btatq, Bvec *qo, Bvec *atqo)
{
    int iters;
    double denom,rsnrm,ernrm2,ernrm8,erden2,erden8;
    double alpha,gamma,sigma,delta,normal;
    double rq,Apq,Apoqo,BApAtq,BApAtqo,ApoBtAtq;
    int key_m,flag_m,itmax_m,prec_m,cycle_m;
    double etol_m;
    Bvec *u = thee;

    int prtKey = VPRTKEY;
    char rn[80], rmeth[80];

    if (prec == 0) {
        strncpy(rmeth,":",80);
    } else if (prec == 1) {
        strncpy(rmeth,"(ds):",80);
    } else if (prec == 3) {
        strncpy(rmeth,"(hb):",80);
    } else if (prec == 5) {
        strncpy(rmeth,"(wmhb):",80);
    } else {
        strncpy(rmeth,":",80);
    }
    if (flag==2) {
        sprintf(rn,"--->Bvec_hbcg%s",rmeth);
        prtKey = 50;
    } else {
        sprintf(rn,"Bvec_hbcg%s",rmeth);
        prtKey = 1;
    }

    /* iteration parameters */
    iters    = 0;
    denom    = 0.0;
    rsnrm    = 0.0;
    ernrm2   = 0.0;
    ernrm8   = 0.0;
    erden2   = 0.0;
    erden8   = 0.0;
    alpha    = 0.0;
    gamma    = 0.0;
    sigma    = 0.0;
    normal   = 1.0;
    rq       = 0.0;
    Apq      = 0.0;
    Apoqo    = 0.0;
    BApAtq   = 0.0;
    BApAtqo  = 0.0;
    ApoBtAtq = 0.0;

    /* DO: r^0 = f - A u^0 */
    Bvec_matvec( r, A, u, key, 0 );
    Bvec_axpy( r, f, (-1.0) );
    Bvec_scal( r, (-1.0) );

    /* DO: s^0 = f - A' u^0 */
    Bvec_matvec( s, A, u, !key, 0 );
    Bvec_axpy( s, f, (-1.0) );
    Bvec_scal( s, (-1.0) );

    /* DO: for i=0,1,2,.... */
    iters = 0;
    while (!Vnm_sigInt()) {

        /* calculate norm of current residual, setup for i/o */
        rsnrm = Bvec_nrm2( r );
        if (iters == 0) {
            denom = rsnrm;
            if ( rsnrm == 0.0 ) {
                Vnm_print(0,"%sinitial residual=%8.2e\n", rn, rsnrm);
                Vnm_print(0,"%sinitial residual is zero...returning.\n", rn);
                return;
            }
        }

        /* if the main solver, do some i/o */
        if ( ((flag==0) || (flag==2))
           && (((iters%prtKey)==0) || (rsnrm/denom<=etol)) ) {
            ernrm2 = Bvec_dif2( u, ut );
            ernrm8 = Bvec_dif8( u, ut );
            if (iters == 0) {
                Vnm_print(0,"%sinitial residual=%8.2e\n", rn, rsnrm);
                erden2 = Bvec_nrm2( ut );
                erden8 = Bvec_nrm8( ut );
                if (erden2 == 0.0) erden2 = 1.0;
                if (erden8 == 0.0) erden8 = 1.0;
            }
            Vnm_print(0,"%s it=%4d",rn,iters);
            Vnm_print(0,"  rr=%8.2e  r=%8.2e  re2=%8.2e  re8=%8.2e\n",
                rsnrm/denom, rsnrm, ernrm2/erden2, ernrm8/erden8);
        }

        /* check stopping criteria */
        if ( rsnrm/denom <= etol ) return;
        if ( iters >= itmax ) {
            if ( (flag==0) || (flag==2) )
                Vnm_print(0,"%s itmax reached! (rr=%e)\n", rn, rsnrm/denom);
            return;
        }

        /* form new direction vector */
        if ( iters == 0 ) {

            /* DO: (form: B r^0) */
            if (prec == 0) {
                Bvec_copy( p, r );
            } else if (prec == 1) {
                Bvec_diagScale(p, A, r);
            } else if (prec == 3 || prec == 5) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_hb(p, A, r, ap, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, P, M);
            } else {
                Bvec_copy( p, r );
            }

            /* DO: p^0 = B r^0 / ||B r^0|| */
            normal = Bvec_nrm2( p );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( p, normal );

            /* DO: (form: B' s^0) */
            if (prec == 0) {
                Bvec_copy( q, s );
            } else if (prec == 1) {
                Bvec_diagScale(q, A, s);
            } else if (prec == 3 || prec == 5) {
                key_m   = !key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_hb(q, A, s, atq, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, P, M);
            } else {
                Bvec_copy( q, s );
            }

            /* DO: q^0 = B' s^0 / ||B' s^0|| */
            normal = Bvec_nrm2( q );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( q, normal );

        } else {

            /* DO: (form: B A p^i) */
            if (prec == 0) {
                Bvec_copy( bap, ap );
            } else if (prec == 1) {
                Bvec_diagScale(bap, A, ap);
            } else if (prec == 3 || prec == 5) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_hb(bap, A, ap, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, P, M);
            } else {
                Bvec_copy( bap, ap );
            }

            /* DO: (form: B' A' q^i) */
            if (prec == 0) {
                Bvec_copy( btatq, atq );
            } else if (prec == 1) {
                Bvec_diagScale(btatq, A, atq);
            } else if (prec == 3 || prec == 5) {
                key_m   = !key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_hb(btatq, A, atq, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, P, M);
            } else {
                Bvec_copy( btatq, atq );
            }

            /* DO: gamma_i = <B A p^i, A' q^i> / <A p^i, q^i> */
            BApAtq = Bvec_dot( bap, atq );
            gamma  = BApAtq / Apq;

            /* DO: sigma_i = <B A p^i, A' q^{i-1}> / <A p^{i-1}, q^{i-1}> */
            if ( iters == 1 ) {
                sigma = 0.0;
            } else {
                BApAtqo = Bvec_dot( bap, atqo );
                sigma   = BApAtqo / Apoqo;
            }

            /* DO: delta_i = <A p^{i-1}, B'A' q^i> / <A p^{i-1}, q^{i-1}> */
            if ( iters == 1 ) {
                delta = 0.0;
            } else {
                ApoBtAtq = Bvec_dot( apo, btatq );
                delta = ApoBtAtq / Apoqo;
            }

            /* DO: v = B A p^i - gamma_i p^i - sigma_i p^{i-1} */
            Bvec_copy( apo, ap );
            Bvec_axpy( bap, p, (-gamma) );
            Bvec_axpy( bap, po, (-sigma) );
            Bvec_copy( po, p );
            Bvec_copy( p, bap );

            /* DO: p^{i+1} = v / ||v|| */
            normal = Bvec_nrm2( p );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( p, normal );

            /* DO: w = B'A' q^i - gamma_i q^i - delta_i q^{i-1} */
            Bvec_copy( atqo, atq );
            Bvec_axpy( btatq, q, (-gamma) );
            Bvec_axpy( btatq, qo, (-delta) );
            Bvec_copy( qo, q );
            Bvec_copy( q, btatq );

            /* DO: q^{i+1} = w / ||w|| */
            normal = Bvec_nrm2( q );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( q, normal );
        }

        /* DO: alpha_i = <r^i, q^i> / <A p^i, q^i> */
        Bvec_matvec( ap, A, p, key, 0 );
        Bvec_matvec( atq, A, q, !key, 0 );
        Apoqo = Apq;
        Apq   = Bvec_dot( ap, q );
        if ( VABS(Apq) < VSMALL ) {
            if ( (flag==0) || (flag==2) ) {
                Vnm_print(0,"%s (Ap,q)=%e (rr=%e)\n", rn, Apq, rsnrm/denom);
                Vnm_print(0,"%s Hitting the roundoff wall...returning.\n",rn);
            }
            return;
        }
        rq    = Bvec_dot( r, q );
        alpha = rq / Apq;

        /* DO: u^{i+1} = u^i + alpha_i p^i */
        Bvec_axpy( u, p, alpha );

        /* DO: r^{i+1} = r^i - alpha_i A p^i */
        Bvec_axpy( r, ap, (-alpha) );

        /* iterate */
        iters++;
    }
}

/*
 * ***************************************************************************
 * Routine:  HBmat_initMulti
 *
 * Purpose:  Assembles the hierarchical matrix structures for the HB Vcycle.
 *
 *   Notes:  This routine takes a null pointer to two HBmat pointers and
 *           returns a linked (hierarchical) chain of fully assembled
 *           HBmat's.
 *
 *           Basic Inputs:
 *
 *           Bmat *A             the finest level stiffness matrix
 *           Bmat *P0, *P1, ...  the prologation matrices for each level
 *
 *           Basic Outputs (inside the HBmat chain):
 *
 *           Bmat *A21, *A22, *A12   stabilized Mat blocks on each level
 *           Bmat *A11               stabilized A11 block on coarse level
 *           Bvec *d1, *d2           defect section pointers
 *           Bvec *r1, *r2           residual section pointers
 *
 * Example:  Suppose we have a two-level system, resulting from a
 *           mesh refinement.  Let P be the prologation (restriction)
 *           matrix which prolongates (restricts) a trial solution
 *           from level 0 to 1 (1 to 0).  The stiffness matrix, A,
 *           can be naturally decomposed into four blocks, if the nodes
 *           added during refinement (fine nodes) are logically
 *           "appended" to the end of the solution vector:
 *
 *           A = [ A11 A12 ] ; P = [ I ] ; d = [ d1 ] ; r = [ r1 ]
 *               [ A21 A22 ]       [ R ]       [ d2 ]       [ r2 ]
 *
 *           Hierarchical Basis Multigrid (HB), doesn't use the standard
 *           nodal basis, using instead the "hierarchical basis".  The
 *           HB-basis stiffness matrix is related to the nodal basis
 *           stiffness matrix through a "change-of-basis" transform:
 *
 *           A_hb = S'*A*S ; d = S*d_hb ; r_hb = S'*r ; S = [ I 0 ]
 *                                                          [ R I ]
 *           Written out in blocks, A_hb has the form:
 *
 *           A_hb = [ A11 + A12*R + R'*A21 + R'*A22*R ; A12 + R'*A22 ]
 *                  [ A21 + A22*R                     ; A22          ]
 *
 *           The resulting HBmat and HBvec chains will have two levels,
 *           0 and 1, with a pointer to the chains returned as output.
 *           Level 0 contains the only non-null pointer to A11.
 *
 * Author:   Burak Aksoylu and Stephen Bond
 * ***************************************************************************
 */

VPUBLIC void HBmat_initMulti( HBmat **Ahb, HBmat **Ghb,
    Bmat *A, Bmat *M, Bmat *Ppro, int meth )
{
    int ii, jj, numB;
    int numR[MAXV], numC[MAXV];
    MATsym psym[MAXV][MAXV];
    MATmirror pmir[MAXV][MAXV];
    Bmat *Mlink = VNULL;
    Bmat *Alink = VNULL;

    numB = Bmat_numB(A);
    for (ii=0; ii<numB; ii++ ) {
        numR[ii] = Bmat_numR(A,ii,ii);
        numC[ii] = Bmat_numC(A,ii,ii);
    }

    /* construct the hierarchical HBmat chain for G = S - I */
    if ( (meth == 0) && (Ppro != VNULL) && (!Bmat_sluDirect(A)) ) {
        (*Ghb) = HBmat_ctor( A->vmem, "Ghb", numB );
        HBmat_initG( (*Ghb), Ppro, Mlink, meth );
    } else if ( (meth == 1) && (Ppro != VNULL) && (!Bmat_sluDirect(A)) ) {
        for (ii=0; ii<numB; ii++ ) {
            for (jj=0; jj<numB; jj++ ) {
                psym[ii][jj] = Bmat_sym(M,ii,jj);
                if ( (psym[ii][jj] == ISNOT_SYM)
                     && (Bmat_format(M,ii,jj) == DRC_FORMAT) ) {
                    psym[ii][jj] = STRUC_SYM; /* MESSY BUT IT WORKS */
                }
                pmir[ii][jj] = Bmat_mirror(M,ii,jj);
            }
        }
#if 0
        Bmat_printSp(M,"Mnodal.m",0);
#endif
        Mlink = Bmat_ctor( M->vmem, "M", numB, numR, numC, pmir);
        BXLN_copyBmat( Mlink, M );
        (*Ghb) = HBmat_ctor( A->vmem, "Ghb", numB );
        HBmat_initG( (*Ghb), Ppro, Mlink, meth );
        Bmat_dtor( &Mlink );
    }

    /* construct the hierarchical HBmat chain for A */
    (*Ahb) = HBmat_ctor( A->vmem, "Ahb", numB );

    if ( (Ppro == VNULL) || (Bmat_sluDirect(A)) ) {
        (*Ahb)->A22 = A;
        (*Ahb)->type = AMIN_TYPE;
    } else {
        /* create an BXLN copy of the finest level stiffness matrix */
        for (ii=0; ii<numB; ii++ ) {
            for (jj=0; jj<numB; jj++ ) {
                psym[ii][jj] = Bmat_sym(A,ii,jj);
                if ( (psym[ii][jj] == ISNOT_SYM)
                     && (Bmat_format(A,ii,jj) == DRC_FORMAT) ) {
                    psym[ii][jj] = STRUC_SYM; /* MESSY BUT IT WORKS */
                }
                pmir[ii][jj] = Bmat_mirror(A,ii,jj);
            }
        }
        Alink = Bmat_ctor( A->vmem, "A", numB, numR, numC, pmir );
        BXLN_copyBmat( Alink, A );
        HBmat_initA( (*Ahb), (*Ghb), Alink );
        Bmat_dtor( &Alink );
    }
}
/*
 * ***************************************************************************
 * Routine:  HBmat_killMulti
 *
 * Purpose:  Destruct the hierarchical structures
 *
 * Author:   Burak Aksoylu and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void HBmat_killMulti(HBmat **Ahb, HBmat **Ghb)
{
    /* destruct the hierarchical HBmat chain for S */
    HBmat_killStructure( (*Ghb) );
    HBmat_dtor( Ghb );

    /* destruct the hierarchical HBmat chain for A */
    if ( (*Ahb)->type == AMIN_TYPE ) {
        (*Ahb)->A22 = VNULL;
    }
    HBmat_killStructure( (*Ahb) );
    HBmat_dtor( Ahb );
}
