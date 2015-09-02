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
 * rcsid="$Id: subopt.c,v 1.15 2010/08/12 05:19:23 fetk Exp $"
 * ***************************************************************************
 */

#define  ONE_RING_METHOD0
#undef  ONE_RING_METHOD1
#undef  ONE_RING_METHOD2
#undef  SEGMENTED_BCHAR

/*
 * ***************************************************************************
 * File:     subopt.c
 *
 * Purpose:  Class Bvec: Suboptimal multigrid implementations for testing.
 *
 * Author:   Stephen Bond, Burak Aksoylu, and Michael Holst
 * ***************************************************************************
 */

#include "subopt_p.h"
VPRIVATE void Bmat_printBRC(Bmat *thee);

VEMBED(rcsid="$Id: subopt.c,v 1.15 2010/08/12 05:19:23 fetk Exp $")

/*
 * ***************************************************************************
 * Class Bvec: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_WHB)

#endif /* if !defined(VINLINE_WHB) */
/*
 * ***************************************************************************
 * Class Bvec: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Bvec_submethod
 *
 * Purpose:  Executes one of a number of linear solvers.
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_submethod(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    int meth)
{
    Bvec *w[11];
    Bvec *u = thee;
    Bchar *fc;

    if ((flag==0) || (flag==2)) {
        Vnm_tstart(40, "linear solve");
    }

    /* methods (0=slu,1=sfmg,2=pcgsfmg,3=pbcgsfmg) */
    switch (meth) {
        /* primary methods */
        case 0:  Bvec_slu( u, A, f, r, ut, key, flag);
                 break;

        case 1:  fc = Bchar_ctor(thee->vmem,"fc",thee->numB,thee->numR);
                 Bvec_sfmg( u, A, f, r, ut, key, flag, itmax, etol, prec,
                     cycle, P, fc);
                 Bchar_dtor(&fc);
                 break;

        case 2:  Bvec_createVectors(thee, w, 6);
                 fc = Bchar_ctor(thee->vmem,"fc",thee->numB,thee->numR);
                 Bvec_sfpcg( u, A, f, r, ut, key, flag, itmax, etol, prec,
                      cycle, P, fc,
                      w[0],w[1],w[2],w[3],w[4],w[5] );
                 Bchar_dtor(&fc);
                 Bvec_destroyVectors(thee, w, 6);
                 break;

        case 3:  Bvec_createVectors(thee, w, 11);
                 fc = Bchar_ctor(thee->vmem,"fc",thee->numB,thee->numR);
                 Bvec_sfpbcg( u, A, f, r, ut, key, flag, itmax, etol, prec,
                      cycle, P, fc,
                      w[0],w[1],w[2],w[3],w[4],w[5],w[6],w[7],w[8],w[9],w[10]);
                 Bchar_dtor(&fc);
                 Bvec_destroyVectors(thee, w, 11);
                 break;

        /* bad choice */
        default:
                 Vnm_print(0,"Bvec_submethod: Bad meth given!\n");
                 break;
    }

    if ((flag==0) || (flag==2)) {
        Vnm_tstop(40, "linear solve");
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_sfmg
 *
 * Purpose:  MG algorithm front end (NOT recursively callable).
 *
 * Input:
 *           P=?      --> prolongation operators (linked list)
 *           A=?      --> system matrix
 *           thee=?   --> solution slot
 *           f=?      --> source vector slot
 *           r=?      --> residual slot
 *           ut=?     --> true solution slot
 *
 *           other=?  --> just passed along to Bvec_sfmgCore()
 *
 * Details:  We use P to build an algebraic multilevel hierarchy in
 *           A,u(thee),f,r,ut from the fine-level-only representations,
 *           and then make the first call to the recursively-callable
 *           core MG algorithm Bvec_sfmgCore().
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPRIVATE void Bvec_sfmg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bchar *fc)
{
    int iMadeMultilevel = 0;
    Bvec *u = thee;

    /* create multilevel structure if necessary */
    if( thee->coarse == VNULL ) {
        Bvec_mgInit(thee, A, f, r, P);
        Bchar_sfmgInit(fc, prec, A, P);
        iMadeMultilevel = 1;
    }

    /* call multilevel solver */
    Bvec_sfmgCore(u, A, f, r, ut, key, flag, itmax, etol, prec, cycle, P, fc);

    /* destroy multilevel structure if we made it */
    if (iMadeMultilevel == 1) {
        Bvec_mgDestroy(thee, A, f, r);
        Bchar_sfmgDestroy(fc);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bchar_sfmgInit
 *
 * Purpose:  Initialize the multilevel FC array
 *
 * Input:
 *           P=?      --> prolongation operators (linked list)
 *           thee=?   --> FC array
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPRIVATE void Bchar_sfmgInit(Bchar *thee, int prec, Bmat *A, Bmat *P)
{
    int ii, numB, numR[MAXV];
    Bmat *WP, *WA;
    Bchar *Wfc;

    numB = Bmat_numB(A);

    /* create multilevel structure */
    WP   = P;
    WA   = A;
    Wfc  = thee;
    while ((WP != VNULL) && (!Bmat_sluDirect(WA))) {

        /* label f and c points */
#ifdef ONE_RING_METHOD2
        Bchar_assem2( Wfc, prec - 2, WA, WP );
#else /* ONE_RING_METHOD0 OR ONE_RING_METHOD1 */
        Bchar_assem( Wfc, prec - 2, WP );
#endif
        /* create the coarse array */
        for (ii=0; ii<numB; ii++) {
            numR[ii] = Bmat_numC(WP,ii,ii);
        }

        if (Wfc->coarse == VNULL) {
            Wfc->coarse = Bchar_ctor( thee->vmem, "fc", numB, numR );
        }

#if 0
	Bmat_printBRC(WP);
#endif

        /* move to coarse level */
        WP  = WP->coarse;
        WA  = WA->coarse;
        Wfc = Wfc->coarse;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_sfmgDestroy
 *
 * Purpose:  Destroy the multilevel FC array
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPRIVATE void Bchar_sfmgDestroy(Bchar *thee)
{
    /* destroy multilevel structure */
    if (VNULL != thee->coarse) Bchar_dtor( &(thee->coarse) );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_sfmgCore
 *
 * Purpose:  MG algorithm core (recursively callable).
 *
 * Input:
 *           P=?      --> prolongation operators (linked list)
 *           A=?      --> system matrices (linked list)
 *           thee=?   --> solution slots (linked list)
 *           f=?      --> source vector slots (linked list)
 *           r=?      --> residual slots (linked list)
 *           ut=?     --> true solution slots (linked list)
 *
 *           key=0    --> solve Au=f
 *           key=1    --> solve A'u=f
 *
 *           flag=0   --> Normal: check itmax, error tolerance; normal i/o
 *           flag=1   --> Normal: check itmax; no error tolerance; no i/o
 *           flag=2   --> Subcycle: check itmax, error tolerance; subcycle i/o
 *           flag=3   --> Subcycle: check itmax, error tolerance; no i/o
 *
 *           itmax=?  --> iteration maximum
 *           etol=?   --> error tolerance
 *           prec=?   --> not used (ignored)
 *
 *           cycle=0  --> nonsymmetric multigrid
 *           cycle=1  --> adjoint of nonsymmetric multigrid
 *           cycle=2  --> symmetric multigrid
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPRIVATE void Bvec_sfmgCore(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bchar *fc)
{
    int iters;
    double denom,rsnrm,ernrm2,ernrm8,erden2,erden8;
    int key_s,flag_s,itmax_s,meth_s,adj_s;
    int key_m,flag_m,itmax_m,prec_m,cycle_m;
    int key_c,flag_c,itmax_c,prec_c,cycle_c,meth_c;
    double etol_c,etol_s,etol_m;
    double omega_s;
    Bvec *u = thee;

    int prtKey = VPRTKEY;
    char rn[80];
    if (flag==2) {
        strncpy(rn,"--->Bvec_sfmgCore:",80);
        prtKey = 1;
    } else {
        strncpy(rn,"Bvec_sfmgCore:",80);
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

    /* solve coarse problem using best available single-level method */
    if (Bmat_sluDirect(A) || (A->coarse == VNULL)) {
        key_c   = key;  /* 0=(Au=f), 1=(A'u=f) */
        flag_c  = flag; /* this way we get some i/o if we are the only level */
        itmax_c = 500;
        etol_c  = 1.0e-10;
        cycle_c = 2; /* symmetric multigrid */
        Bvec_init( u, 0. );
#if 1
        prec_c = 1; /* diagonal scaling */
        meth_c = 3; /* bcg */
#else
        prec_c = 0; /* no preconditioner */
        meth_c = 0; /* slu */
#endif
        Bvec_lmethod(u, A, f, r, ut, key_c, flag_c, itmax_c, etol_c, prec_c,
            cycle_c, VNULL, meth_c);
        return;
    }

    /* initialize basic iteration quantities and iterate */
    iters = 0;
    while (!Vnm_sigInt()) {

        /* apply pre-smoothing iteration */
        key_s   = key;
        flag_s  = 1;
        meth_s  = 1;
        itmax_s = 2;
        etol_s  = 0.0;
        omega_s = 0.5;
        if ((cycle == 0) || (cycle == 2)) {
            adj_s = 0;
        } else { /* (cycle == 1) */
            adj_s = 1;
        }
        Bvec_fsmooth( u, A, f, r, key_s, flag_s, meth_s, adj_s, itmax_s, fc );

        /* calculate the residual */
        Bvec_matvec( r, A, u, key, 0 );
        Bvec_axpy( r, f, (-1.0) );

        /* calculate norm of initial residual, setup for i/o */
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
        if ( (flag!=1) && (rsnrm/denom <= etol) ) return;

        /* restrict the residual */
        Bvec_scal( r, (-1.) );
        Bvec_matvec( f->coarse, P, r, /*key*/ 1, 0 );
        Bvec_bnd( f->coarse, P, /*key*/ 1 );

        /* call multigrid recursively to solve coarse problem */
        key_m     = key;
        flag_m    = 1;
        itmax_m   = 1;
        etol_m    = 0.0;
        prec_m    = prec;
        cycle_m   = cycle;
        Bvec_init( u->coarse, 0. );
        Bvec_sfmgCore( u->coarse, A->coarse, f->coarse, r->coarse, VNULL,
            key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P->coarse,
            fc->coarse );

        /* prolongate correction to fine grid and perform the correction */
        Bvec_matvec( r, P, u->coarse, /*key*/ 0, 0 );
        Bvec_bnd( r, P, /*key*/ 0 );
        Bvec_axpy( u, r, (1.0) );

        /* apply the post-smoothing iteration */
        key_s   = key;
        flag_s  = 1;
        meth_s  = 1;
        itmax_s = 2;
        etol_s  = 0.0;
        omega_s = 0.5;
        if ((cycle == 0) || (cycle == 1)) {
            adj_s = 0;
        } else { /* (cycle == 2) */
            adj_s = 1;
        }
        Bvec_fsmooth( u, A, f, r, key_s, flag_s, meth_s, adj_s, itmax_s, fc );

        /* iterate */
        iters++;
        if (iters >= itmax) return;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_sfpcg
 *
 * Purpose:  CG method (ODIR algorithm, requires SPD operators A, B, and M).
 *
 *           ODIR(M,B,A) (for Au=f, preconditioner B, inner-product M)
 *           ---------------------------------------------------------
 *
 *           Given u^0
 *           r^0 = f - A u^0
 *           p^0 = B r^0 / ||B r^0||
 *           for i=0,1,2,....
 *               alpha_i = <M e^i, p^i> / <M p^i, p^i>
 *               u^{i+1} = u^i + alpha_i p^i
 *               r^{i+1} = r^i - alpha_i A p^i
 *               gamma_i = <M B A p^i, p^i> / <M p^i, p^i>
 *               sigma_i = <M B A p^i, p^{i-1}> / <M p^{i-1}, p^{i-1}>
 *               v       = B A p^i - gamma_i p^i - sigma_i p^{i-1}
 *               p^{i+1} = v / ||v||
 *           end for
 *
 *           CG=ODIR(M=A,B=B,A=A)
 *           --------------------
 *
 *           Given u^0
 *           r^0 = f - A u^0
 *           p^0 = B r^0 / ||B r^0||
 *           for i=0,1,2,....
 *               alpha_i = <r^i, p^i> / <A p^i, p^i>
 *               u^{i+1} = u^i + alpha_i p^i
 *               r^{i+1} = r^i - alpha_i A p^i
 *               gamma_i = <B A p^i, A p^i> / <A p^i, p^i>
 *               sigma_i = <B A p^i, A p^{i-1}> / <A p^{i-1}, p^{i-1}>
 *               v       = B A p^i - gamma_i p^i - sigma_i p^{i-1}
 *               p^{i+1} = v / ||v||
 *           end for
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
VPRIVATE void Bvec_sfpcg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bchar *fc, Bvec *p, Bvec *ap, Bvec *bap, Bvec *po, Bvec *apo, Bvec *tp)
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
    } else if (prec == 2) {
        strncpy(rmeth,"(mg):",80);
    } else if (prec == 3) {
        strncpy(rmeth,"(hb):",80);
    } else if (prec == 4) {
        strncpy(rmeth,"(bpx):",80);
    } else {
        strncpy(rmeth,":",80);
    }
    if (flag==2) {
        sprintf(rn,"--->Bvec_sfpcg%s",rmeth);
        prtKey = 50;
    } else {
        sprintf(rn,"Bvec_sfpcg%s",rmeth);
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

    /* calculate norm of initial residual, setup for i/o */
    rsnrm = Bvec_nrm2( r );
    denom = rsnrm;
    if ( rsnrm == 0.0 ) {
        Vnm_print(0,"%sinitial residual=%8.2e\n", rn, rsnrm);
        Vnm_print(0,"%sinitial residual is zero...returning.\n", rn);
        return;
    }

    if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
        Bvec_mgInit(bap, A, ap, tp, P);
        Bchar_sfmgInit(fc, prec, A, P);
    }

    /* DO: for i=0,1,2,.... */
    iters = 0;
    while (!Vnm_sigInt()) {

        /* calculate norm of current residual */
        if ( iters > 0 ) {
            rsnrm = Bvec_nrm2( r );
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
        if ( rsnrm/denom <= etol ) {
            if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
                Bvec_mgDestroy(bap, A, ap, tp);
                Bchar_sfmgDestroy(fc);
            }
            return;
        }
        if ( iters >= itmax ) {
            if ( (flag==0) || (flag==2) )
                Vnm_print(0,"%s itmax reached! (rr=%e)\n", rn, rsnrm/denom);
            if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
                Bvec_mgDestroy(bap, A, ap, tp);
                Bchar_sfmgDestroy(fc);
            }
            return;
        }

        /* form new direction vector */
        if ( iters == 0 ) {

            /* DO: (form: B r^0) */
            if (prec == 0) {
                Bvec_copy( p, r );
            } else if (prec == 1) {
                Bvec_diagScale(p, A, r);
            } else if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_copy( ap, r );
                Bvec_sfmg(bap, A, ap, tp, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P, fc);
                Bvec_copy( p, bap );
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
            } else if ((prec == 2) || (prec == 3) || (prec == 4)) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_sfmg(bap, A, ap, tp, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P, fc);
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

    if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
        Bvec_mgDestroy(bap, A, ap, tp);
        Bchar_sfmgDestroy(fc);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_sfpbcg
 *
 * Purpose:  BCG method (pure bi-orthogonal extension of CG).
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
 *               delta_i = <A p^{i-1}, B'A' q^i> / <A p^{i-1}, q^{i-1}>
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
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPRIVATE void Bvec_sfpbcg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bchar *fc, Bvec *s,
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
    } else if (prec == 2) {
        strncpy(rmeth,"(mg):",80);
    } else if (prec == 3) {
        strncpy(rmeth,"(hb):",80);
    } else if (prec == 4) {
        strncpy(rmeth,"(bpx):",80);
    } else {
        strncpy(rmeth,":",80);
    }
    if (flag==2) {
        sprintf(rn,"--->Bvec_sfpbcg%s",rmeth);
        prtKey = 50;
    } else {
        sprintf(rn,"Bvec_sfpbcg%s",rmeth);
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

    /* calculate norm of initial residual, setup for i/o */
    rsnrm = Bvec_nrm2( r );
    denom = rsnrm;
    if ( rsnrm == 0.0 ) {
        Vnm_print(0,"%sinitial residual=%8.2e\n", rn, rsnrm);
        Vnm_print(0,"%sinitial residual is zero...returning.\n", rn);
        return;
    }

    if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
        Bvec_mgInit(bap, A, ap, s, P);
        Bvec_mgInit(btatq, A, atq, s, P);
        Bchar_sfmgInit(fc, prec, A, P);
    }

    /* DO: for i=0,1,2,.... */
    iters = 0;
    while (!Vnm_sigInt()) {

        /* calculate norm of current residual */
        if ( iters > 0 ) {
            rsnrm = Bvec_nrm2( r );
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
        if ( rsnrm/denom <= etol ) {
            if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
                Bvec_mgDestroy(bap, A, ap, s);
                Bvec_mgDestroy(btatq, A, atq, s);
                Bchar_sfmgDestroy(fc);
            }
            return;
        }
        if ( iters >= itmax ) {
            if ( (flag==0) || (flag==2) )
                Vnm_print(0,"%s itmax reached! (rr=%e)\n", rn, rsnrm/denom);
            if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
                Bvec_mgDestroy(bap, A, ap, s);
                Bvec_mgDestroy(btatq, A, atq, s);
                Bchar_sfmgDestroy(fc);
            }
            return;
        }

        /* form new direction vector */
        if ( iters == 0 ) {

            /* DO: (form: B r^0) */
            if (prec == 0) {
                Bvec_copy( p, r );
            } else if (prec == 1) {
                Bvec_diagScale(p, A, r);
            } else if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_copy( ap, r );
                Bvec_sfmg(bap, A, ap, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P, fc);
                Bvec_copy( p, bap );
            } else {
                Bvec_copy( p, r );
            }

            /* DO: p^0 = B r^0 / ||B r^0|| */
            normal = Bvec_nrm2( p );
            if (normal < VSMALL) normal = 1.;
            else normal = 1. / normal;
            Bvec_scal( p, normal );

            /* DO: s^0 = f - A' u^0 */
            Bvec_matvec( s, A, u, !key, 0 );
            Bvec_axpy( s, f, (-1.0) );
            Bvec_scal( s, (-1.0) );

            /* DO: (form: B' s^0) */
            if (prec == 0) {
                Bvec_copy( q, s );
            } else if (prec == 1) {
                Bvec_diagScale(q, A, s);
            } else if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
                key_m   = !key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_copy( atq, s );
                Bvec_sfmg(btatq, A, atq, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P, fc);
                Bvec_copy( q, btatq );
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
            } else if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_sfmg(bap, A, ap, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P, fc);
            } else {
                Bvec_copy( bap, ap );
            }

            /* DO: (form: B' A' q^i) */
            if (prec == 0) {
                Bvec_copy( btatq, atq );
            } else if (prec == 1) {
                Bvec_diagScale(btatq, A, atq);
            } else if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
                key_m   = !key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_sfmg(btatq, A, atq, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P, fc);
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
            if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
                Bvec_mgDestroy(bap, A, ap, s);
                Bvec_mgDestroy(btatq, A, atq, s);
                Bchar_sfmgDestroy(fc);
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

    if ( (prec == 2) || (prec == 3) || (prec == 4) ) {
        Bvec_mgDestroy(bap, A, ap, s);
        Bvec_mgDestroy(btatq, A, atq, s);
        Bchar_sfmgDestroy(fc);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_fsmooth
 *
 * Purpose:  F-point smoothing operator
 *
 * Notes:    Consider the following partitioned linear system
 *
 *             [ Acc Acf ] [ xc ] = [ bc ]
 *             [ Afc Aff ] [ xf ]   [ bf ]
 *
 *           where xc is a vector of "coarse" or c-points and
 *           xf is a vector of "fine" or f-points.  This partitioning
 *           induces an analogous partitioning of the matrix A and the
 *           vector b as illustrated above. Given such a partitioning,
 *           an f-point smoother applies a Gauss-Seidel (or Jacobi)
 *           smoother to the f-points, leaving the c-points unchanged.
 *
 *           The forward Gauss-Seidel f-point smoother can be written as
 *               xc = xc
 *               xf = ( Dff + Lff )^(-1) ( bf - Afc xc - Uff xf )
 *
 *           The adjoint Gauss-Seidel f-point smoother can be written as
 *               xc = xc
 *               xf = ( Dff + Uff )^(-1) ( bf - Afc xc - Lff xf )
 *
 *           where, Aff = Uff + Lff + Dff is the standard gs splitting.
 *
 *           This method is invoked in the same manner as Bvec_smooth
 *           with one additional input.  This additional input is a char
 *           array of point types, with coarse and fine points indicated
 *           by 'c' and 'f' respectively.
 *
 *           For example, suppose we have 3 blocks with fpoints (1,5)
 *           in the first block, (0,3) in the second block, and (2,3,4)
 *           in the third block.  In this case fc should be
 *
 *           fc = {{'c', 'f', 'c', 'c', 'c', 'f'},
 *                    {'f', 'c', 'c', 'f', 'c', 'c'},
 *                    {'c', 'c', 'f', 'f', 'f', 'c'}}
 *
 *           This algorithm is not fast and its only practical purpose is
 *           for understanding and debugging HB and BPX style preconditioners.
 *           The HBMG algorithm is output-equivalent to standard
 *           multigrid with f-point smoothing where the f-points are the
 *           degrees of freedom introduced on the current level.  For
 *           multiplicative BPX, the list of f-points is expanded to include
 *           the one-ring of the f-points used by HB.
 *
 *           The optimal versions of multiplicative HB and BPX require
 *           the use of a change of basis so the f-point smoother does
 *           not need to touch the c-points explicitly.  However, the
 *           optimal version is mathematically "output-equivalent" to
 *           the suboptimal version described above.
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_fsmooth(Bvec *thee, Bmat *amat, Bvec *f, Bvec *w,
    int key, int ioflag, int meth, int adj, int itmax, Bchar *fc)
{
    int i, j, k, p, q, iters, numB, numR;
    int *IA, *JA;
    double *A, *uu, *ww, *ff, *diag, *offU, *offL;
    char rn[80], *pt, *qt;
    strncpy(rn,"Bvec_fsmooth:",80);

    VASSERT( ioflag == 1 );

    /* some local variable pointers for speed and readability */
    numB = Bmat_numB(amat);

    /* check some dimensions of vector/blocks */
    VASSERT(Bvec_numB(thee) == Bvec_numB(f));
    VASSERT(Bvec_numB(thee) == Bvec_numB(w));
    VASSERT(Bvec_numB(thee) == Bmat_numB(amat));
    for (p=0; p<numB; p++) {
        VASSERT(Bvec_numRB(f,p) == Bvec_numRB(w,p));
        VASSERT(Bvec_numRB(f,p) == Bvec_numRB(thee,p));
        for (q=0; q<numB; q++) {
            VASSERT(Bmat_numC(amat,p,q) == Bvec_numRB(thee,q));
            VASSERT(Bmat_numR(amat,p,q) == Bvec_numRB(f,p));
        }
    }

    /* Gauss-Seidel smoother */
    if ( (meth == 1) | (meth == 2) ) {

        iters = 0;
        while ((iters < itmax) && (!Vnm_sigInt())) {
            iters++;

            if ( (adj == 0) | (meth == 2) ) {

                /* Step 1: w = bf - Afc xc - Uff xf */
                for (p=0; p<numB; p++) {
                    numR = Bvec_numRB(thee,p);
                    ww   = Bvec_addrB(w,p);
                    ff   = Bvec_addrB(f,p);
                    uu   = Bvec_addrB(thee,p);
                    pt   = fc->u[p];

                    /* diag blocks: pull off only strict upper triangle */
                    IA = Bmat_IA(amat,p,p);
                    JA = Bmat_JA(amat,p,p);
                    A  = Bmat_A(amat,p,p);
                    if (key == 0) {     /* smooth(u,A,f) */
                        offU = Bmat_offU(amat,p,p);
                        offL = Bmat_offL(amat,p,p);
                    } else { /* ( key==1 ) smooth(u,A',f) */
                        offU = Bmat_offL(amat,p,p);
                        offL = Bmat_offU(amat,p,p);
                    }
                    for (i=0; i<numR; i++) {
                        if ('f' == pt[i]) {
                            /* w = bf */
                            ww[i] = ff[i];
                            /* w = w - Uff xf - Ufc xc for blocks on diag */
                            for (k=IA[i]; k<IA[i+1]; k++) {
                                j = JA[k];
                                ww[i] -= ( offU[k] * uu[j] );
                            }
                        }
                    }
                    for (i=0; i<numR; i++) {
                        if ('c' == pt[i]) {
                            /* w = w - Lfc xc for blocks on diag */
                            for (k=IA[i]; k<IA[i+1]; k++) {
                                j = JA[k];
                                if ('f' == pt[j]) {
                                    ww[j] -= ( offL[k] * uu[i] );
                                }
                            }
                        }
                    }

                    /* off-diag blocks: pull off entire matrix */
                    for (q=p+1; q<numB; q++) {
                        uu = Bvec_addrB(thee,q);
                        qt = fc->u[q];
                        if (key==0) {       /* smooth(u,A,f) */
                            VASSERT( ROW_FORMAT == Bmat_format(amat,p,q) );
                            IA = Bmat_IA(amat,p,q);
                            JA = Bmat_JA(amat,p,q);
                            A  = Bmat_A(amat,p,q);
                        } else { /* ( key==1 ) smooth(u,A',f) */
                            VASSERT( COL_FORMAT == Bmat_format(amat,q,p) );
                            IA = Bmat_IA(amat,q,p);
                            JA = Bmat_JA(amat,q,p);
                            A  = Bmat_A(amat,q,p);
                        }
                        for (i=0; i<numR; i++) {
                            if ('f' == pt[i]) {
                                /* w = w - Aff xf - Afc xc blocks above diag */
                                for (k=IA[i]; k<IA[i+1]; k++) {
                                    j = JA[k];
                                    ww[i] -= ( A[k] * uu[j] );
                                }
                            }
                        }
                    }
                    for (q=0; q<p; q++) {
                        numR = Bvec_numRB(thee,q);
                        uu = Bvec_addrB(thee,q);
                        qt = fc->u[q];

                        if (key==0) {       /* smooth(u,A,f) */
                            VASSERT( COL_FORMAT == Bmat_format(amat,p,q) );
                            IA = Bmat_IA(amat,p,q);
                            JA = Bmat_JA(amat,p,q);
                            A  = Bmat_A(amat,p,q);
                        } else { /* ( key==1 ) smooth(u,A',f) */
                            VASSERT( ROW_FORMAT == Bmat_format(amat,q,p) );
                            IA = Bmat_IA(amat,q,p);
                            JA = Bmat_JA(amat,q,p);
                            A  = Bmat_A(amat,q,p);
                        }
                        for (i=0; i<numR; i++) {
                            if ('c' == qt[i]) {
                                /* w = w - Afc xc blocks below diag */
                                for (k=IA[i]; k<IA[i+1]; k++) {
                                    j = JA[k];
                                    if ('f' == pt[j]) {
                                        ww[j] -= ( A[k] * uu[i] );
                                    }
                                }
                            }
                        }
                    }
                }

                /* Step 2: Solve (Dff + Lff) xf = w */
                for (p=0; p<numB; p++) {
                    ww = Bvec_addrB(w,p);
                    pt = fc->u[p];

                    /* off-diag blocks: solve using prev diag result */
                    for (q=0; q<p; q++) {
                        numR = Bvec_numRB(thee,q);
                        uu = Bvec_addrB(thee,q);
                        qt = fc->u[q];

                        if (key==0) {       /* smooth(u,A,f) */
                            VASSERT( COL_FORMAT ==  Bmat_format(amat,p,q) );
                            IA = Bmat_IA(amat,p,q);
                            JA = Bmat_JA(amat,p,q);
                            A  = Bmat_A(amat,p,q);
                        } else { /* ( key==1 ) smooth(u,A',f) */
                            VASSERT( ROW_FORMAT == Bmat_format(amat,q,p) );
                            IA = Bmat_IA(amat,q,p);
                            JA = Bmat_JA(amat,q,p);
                            A  = Bmat_A(amat,q,p);
                        }
                        for (i=0; i<numR; i++) {
                            if ('f' == qt[i]) {
                                /* w = w - Aff xf for blocks below diag */
                                for (k=IA[i]; k<IA[i+1]; k++) {
                                    j = JA[k];
                                    if ('f' == pt[j]) {
                                        ww[j] -= ( A[k] * uu[i] );
                                    }
                                }
                            }
                        }
                    }

                    /* diag blocks: solve by column */
                    numR = Bvec_numRB(thee,p);
                    uu   = Bvec_addrB(thee,p);
                    pt   = fc->u[p];

                    IA = Bmat_IA(amat,p,p);
                    JA = Bmat_JA(amat,p,p);
                    A  = Bmat_A(amat,p,p);
                    diag = Bmat_diag(amat,p,p);
                    if (key == 0) {     /* smooth(u,A,f) */
                        offU = Bmat_offU(amat,p,p);
                        offL = Bmat_offL(amat,p,p);
                    } else { /* ( key==1 ) smooth(u,A',f) */
                        offU = Bmat_offL(amat,p,p);
                        offL = Bmat_offU(amat,p,p);
                    }
                    for (i=0; i<numR; i++) {
                        if ('f' == pt[i]) {
                            /* xf = Dff^{-1} w */
                            uu[i] = ww[i] / diag[i];
                            /* w =  w - Lff xf */
                            for (k=IA[i]; k<IA[i+1]; k++) {
                                j = JA[k];
                                if ('f' == pt[j]) {
                                    ww[j] -= ( offL[k] * uu[i] );
                                }
                            }
                        }
                    }
                }
            }

            if ( (adj == 1) | (meth == 2) ) {

                /* Step 1: w = bf - Afc xc - Lff xf */
                for (p=0; p<numB; p++) {
                    numR = Bvec_numRB(thee,p);
                    ww   = Bvec_addrB(w,p);
                    ff   = Bvec_addrB(f,p);
                    uu   = Bvec_addrB(thee,p);
                    pt   = fc->u[p];
                    for (i=0; i<numR; i++) {
                        if ('f' == pt[i]) {
                            /* w = bf */
                            ww[i] = ff[i];
                        }
                    }

                    /* diag blocks: pull off only strict lower triangle */
                    IA = Bmat_IA(amat,p,p);
                    JA = Bmat_JA(amat,p,p);
                    A  = Bmat_A(amat,p,p);
                    if (key==0) {       /* smooth(u,A,f) */
                        offU = Bmat_offU(amat,p,p);
                        offL = Bmat_offL(amat,p,p);
                    } else { /* ( key==1 ) smooth(u,A',f) */
                        offU = Bmat_offL(amat,p,p);
                        offL = Bmat_offU(amat,p,p);
                    }
                    /* w = w - Lfc xc - Lff xf for blocks on diag */
                    for (i=0; i<numR; i++) {
                        for (k=IA[i]; k<IA[i+1]; k++) {
                            j = JA[k];
                            if ('f' == pt[j]) {
                                ww[j] -= ( offL[k] * uu[i] );
                            }
                        }
                    }
                    /* w = w - Ufc xc for blocks on diag */
                    for (i=0; i<numR; i++) {
                        if ('f' == pt[i]) {
                            for (k=IA[i]; k<IA[i+1]; k++) {
                                j = JA[k];
                                if ('c' == pt[j]) {
                                    ww[i] -= ( offU[k] * uu[j] );
                                }
                            }
                        }
                    }

                    /* off-diag blocks: pull off entire matrix */
                    for (q=0; q<p; q++) {
                        numR = Bvec_numRB(thee,q);
                        uu = Bvec_addrB(thee,q);
                        qt = fc->u[q];

                        if (key==0) {       /* smooth(u,A,f) */
                            VASSERT( COL_FORMAT ==  Bmat_format(amat,p,q) );
                            IA = Bmat_IA(amat,p,q);
                            JA = Bmat_JA(amat,p,q);
                            A  = Bmat_A(amat,p,q);
                        } else { /* ( key==1 ) smooth(u,A',f) */
                            VASSERT( ROW_FORMAT ==  Bmat_format(amat,q,p) );
                            IA = Bmat_IA(amat,q,p);
                            JA = Bmat_JA(amat,q,p);
                            A  = Bmat_A(amat,q,p);
                        }
                        /* w = w - Afc xc - Aff xf blocks below diag */
                        for (i=0; i<numR; i++) {
                            for (k=IA[i]; k<IA[i+1]; k++) {
                                j = JA[k];
                                if ('f' == pt[j]) {
                                    ww[j] -= ( A[k] * uu[i] );
                                }
                            }
                        }
                    }

                    numR = Bvec_numRB(f,p);
                    for (q=(p+1); q<numB; q++) {
                        uu = Bvec_addrB(thee,q);
                        qt = fc->u[q];

                        if (key==0) {       /* smooth(u,A,f) */
                            VASSERT( ROW_FORMAT == Bmat_format(amat,p,q) );
                            IA = Bmat_IA(amat,p,q);
                            JA = Bmat_JA(amat,p,q);
                            A  = Bmat_A(amat,p,q);
                        } else { /* ( key==1 ) smooth(u,A',f) */
                            VASSERT( COL_FORMAT ==  Bmat_format(amat,q,p) );
                            IA = Bmat_IA(amat,q,p);
                            JA = Bmat_JA(amat,q,p);
                            A  = Bmat_A(amat,q,p);
                        }
                        /* w = w - Afc xc for blocks above diag */
                        for (i=0; i<numR; i++) {
                            if ('f' == pt[i]) {
                                for (k=IA[i]; k<IA[i+1]; k++) {
                                    j = JA[k];
                                    if ('c' == qt[j]) {
                                        ww[i] -= ( A[k] * uu[j] );
                                    }
                                }
                            }
                        }
                    }
                }

                /* Step 2: Solve (Dff + Uff) xf = w */
                for (q=numB-1; q>=0; q--) {
                    numR = Bvec_numRB(thee,q);
                    ww   = Bvec_addrB(w,q);
                    ff   = Bvec_addrB(f,q);
                    qt   = fc->u[q];

                    /* diag blocks: solve by row */
                    IA = Bmat_IA(amat,q,q);
                    JA = Bmat_JA(amat,q,q);
                    A  = Bmat_A(amat,q,q);
                    uu = Bvec_addrB(thee,q);
                    diag = Bmat_diag(amat,q,q);
                    if (key==0) {       /* smooth(u,A,f) */
                        offU = Bmat_offU(amat,q,q);
                        offL = Bmat_offL(amat,q,q);
                    } else { /* ( key==1 ) smooth(u,A',f) */
                        offU = Bmat_offL(amat,q,q);
                        offL = Bmat_offU(amat,q,q);
                    }
                    for (i=numR-1; i>=0; i--) {
                        if ('f' == qt[i]) {
                            /* w = w - Uff xf */
                            for (k=IA[i]; k<IA[i+1]; k++) {
                                j = JA[k];
                                if ('f' == qt[j]) {
                                    ww[i] -= ( offU[k] * uu[j] );
                                }
                            }
                            /* xf = Dff^{-1} w */
                            uu[i] = ww[i] / diag[i];
                        }
                    }

                    /* off-diag blocks: pull-off using prev result */
                    for (p=0; p<q; p++) {
                        numR = Bvec_numRB(w,p);
                        ww = Bvec_addrB(w,p);
                        pt = fc->u[p];

                        if (key==0) {       /* smooth(u,A,f) */
                            VASSERT( ROW_FORMAT == Bmat_format(amat,p,q) );
                            IA = Bmat_IA(amat,p,q);
                            JA = Bmat_JA(amat,p,q);
                            A  = Bmat_A(amat,p,q);
                        } else { /* ( key==1 ) smooth(u,A',f) */
                            VASSERT( COL_FORMAT == Bmat_format(amat,q,p) );
                            IA = Bmat_IA(amat,q,p);
                            JA = Bmat_JA(amat,q,p);
                            A  = Bmat_A(amat,q,p);
                        }
                        for (i=0; i<numR; i++) {
                            if ('f' == pt[i]) {
                                /* w = w - Aff xf */
                                for (k=IA[i]; k<IA[i+1]; k++) {
                                    j = JA[k];
                                    if ('f' == qt[j]) {
                                        ww[i] -= ( A[k] * uu[j] );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        Vnm_print(2,"%s Invalid smoother specified..\n", rn);
    }
}


/*
 * ***************************************************************************
 * Routine:  Bchar_ctor
 *
 * Purpose:  The block character constructor
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */

VPUBLIC Bchar* Bchar_ctor(Vmem *vmem,
    const char *name, int pnumB, int pnumR[MAXV])
{
    int i, toffset;
    Bchar *thee = VNULL;

    VDEBUGIO("Bchar_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Bchar) );
    if (vmem == VNULL) {
        thee->vmem = Vmem_ctor( "Bchar" );
        thee->iMadeVmem = 1;
    } else {
        thee->vmem = vmem;
        thee->iMadeVmem = 0;
    }

    VDEBUGIO("..done.\n");

    strncpy(thee->name, name, 10);
    thee->coarse = VNULL;
    thee->numB = pnumB;

    /* malloc the array */
    thee->n = 0;
    for (i=0; i<thee->numB; i++) {
        thee->numR[i] = pnumR[i];
        thee->n      += pnumR[i];
    }

#ifndef SEGMENTED_BCHAR
    thee->uflat = Vmem_malloc( thee->vmem, thee->n, sizeof(char) );
    VASSERT( thee->uflat != VNULL );

    /* create pointers to blocks */
    toffset = 0;
    for (i=0; i<thee->numB; i++) {
        thee->u[i] = &((thee->uflat)[toffset]);
        toffset += pnumR[i];
    }
#else
    thee->uflat = VNULL;
    for (i=0; i<thee->numB; i++) {
	thee->u[i] = Vmem_malloc( thee->vmem, thee->numR[i], sizeof(char) );
    }
#endif

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Bchar_dtor
 *
 * Purpose:  The block character destructor.
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bchar_dtor(Bchar **thee)
{
#ifdef SEGMENTED_BCHAR
    int i;
#endif
    if ((*thee) != VNULL ) {

        /* first free any coarse guy */
        if ( (*thee)->coarse != VNULL ) {
            Bchar_dtor( &((*thee)->coarse) );
        }

#ifndef SEGMENTED_BCHAR
        /* now free actual contiguous character array storage */
        Vmem_free((*thee)->vmem, (*thee)->n, sizeof(char),
            (void**)&((*thee)->uflat));
#else
	for (i=0; i<((*thee)->numB); i++) {
	    Vmem_free((*thee)->vmem, (*thee)->numR[i], sizeof(char),
		      (void**)&((*thee)->u[i]));
	}
#endif

        /* cleanup */
        VDEBUGIO("Bchar_dtor: DESTROYING object..");
        if ((*thee)->iMadeVmem) Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(Bchar), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bchar_assem
 *
 * Purpose:  Build a block list of F and C points
 *
 * Notes:    key==0 :  MG    -- All points are F-points
 *           key==1 :  HBMG  -- All new nodes are F-points
 *           key==2 :  BPXMG -- All new nodes plus 1-ring are F-points
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bchar_assem(Bchar *thee, int key, Bmat *Ppro)
{
    int i, j, k, p, *IA, *JA, numR, offset, ibase[MAXV];
    double *A;
    char *uu;

    VASSERT( Bmat_numB(Ppro) == (thee->numB) );

    for (p=0; p<(thee->numB); p++) {
        uu = (thee->u)[p];

        /* Check for implicit representation of identity block */
        if ( Bmat_impl( Ppro, p, p ) == IS_IMPL ) {
            ibase[p] = 0;
            VASSERT( Bmat_numR(Ppro, p, p) + Bmat_numC(Ppro, p, p)
                     == (thee->numR)[p] );
        } else {
            ibase[p] = Bmat_numC(Ppro, p, p);
            VASSERT( Bmat_numR(Ppro, p, p) == (thee->numR)[p] );
        }

        /* Initialize all points as C-points */
        for (i=0; i<(thee->numR)[p]; i++) {
            uu[i] = 'c';
        }
    }

    switch(key) {
      case 0: /* FULL MG */
        for (p=0; p<(thee->numB); p++) {
            uu = (thee->u)[p];
            for (i=0; i<(thee->numR)[p]; i++) {
                uu[i] = 'f';
            }
        }
      break;
      case 1: /* HBMG */
        for (p=0; p<(thee->numB); p++) {
            uu = (thee->u)[p];
            numR = Bmat_numR(Ppro, p, p);
            for (i=ibase[p]; i<numR; i++) {
                IA = Bmat_IA(Ppro,p,p);
                JA = Bmat_JA(Ppro,p,p);
                A  = Bmat_A(Ppro,p,p);
                offset = Bmat_numC(Ppro,p,p) - ibase[p];
#ifndef ONE_RING_METHOD0
		uu[i + offset] = 'f';
#endif
#ifdef  ONE_RING_METHOD0
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    if( A[k] != 0. ) {
                      uu[i + offset] = 'f';
                    }
                }
#endif
            }
        }
      break;
      case 2: /* BPXMG */
        for (p=0; p<(thee->numB); p++) {
            uu = (thee->u)[p];
            numR = Bmat_numR(Ppro, p, p);
            for (i=ibase[p]; i<numR; i++) {
                IA = Bmat_IA(Ppro,p,p);
                JA = Bmat_JA(Ppro,p,p);
                A  = Bmat_A(Ppro,p,p);
                offset = Bmat_numC(Ppro,p,p) - ibase[p];
#ifndef ONE_RING_METHOD0
		uu[i + offset] = 'f';
#endif
                for (k=IA[i]; k<IA[i+1]; k++) {
                    j = JA[k];
                    if( A[k] != 0. ) {
#ifdef ONE_RING_METHOD0
                      uu[i + offset] = 'f';
#endif
                      uu[j] = 'f';
                    }
                }
            }
        }
      break;
      default:
        VASSERT(0);
    }

#if 0 /* DEBUG OUTPUT */
    Vnm_print(0,"Bchar_assem: ");
    for (p=0; p<thee->numB; p++) {
	uu = (thee->u)[p];
	numR = (thee->numR)[p];
	/* Label all nodes as F-points */
	for (i=0; i<numR; i++) {
	    Vnm_print(0,"%c",uu[i]);
	}
	Vnm_print(0,"|");
    }
    Vnm_print(0,"\n");
#endif
}

/*
 * ***************************************************************************
 * Routine:  Bchar_assem2
 *
 * Purpose:  Build a block list of F and C points
 *
 * Notes:    key==0 :  MG    -- All points are F-points
 *           key==1 :  HBMG  -- All "new nodes" are F-points
 *           key==2 :  BPXMG -- All "new nodes" plus 1-ring are F-points
 *
 *           If the node index, i, statisfies (offset[p] <= i < numR[p]),
 *           then it is considered to be a "new node" in the pth block.
 *
 *           The BPXMG case is computed by performing the logical 
 *           equivalent of a matrix-vector product of a boolean matrix
 *           with a boolean vector.  The boolean matrix is just the graph
 *           of the stiffness matrix with '1' in the nonzero locations, and 
 *           the boolean vector is a vector with '1' in the locations of
 *           the HBMG F-points (i.e. the new nodes): 
 *
 *           Ubpx = ( ( ( (A != 0) + (A' != 0) ) * Uhb ) != 0 )
 *
 *           Note that we use both A and A' in the event A is nonsymmetric.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bchar_assem2(Bchar *thee, int key, Bmat *amat, Bmat *Ppro)
{
    int i, j, k, p, q, numB, numR, numC, *IA, *JA, offset[MAXV];
    Mat *AA;
    double *offU, *offL, *diag;
    char *uu, *vv;

    numB = thee->numB;

    /* check some dimensions of vector/blocks */
    VASSERT( Bmat_numB(amat) == thee->numB );
    for (p=0; p<numB; p++) {
	for( q=0; q<numB; q++) {
	    VASSERT( Bmat_numR(amat,p,q) == (thee->numR)[p] );
	    VASSERT( Bmat_numC(amat,p,q) == (thee->numR)[q] );
	}
        /* Check for implicit representation of identity block */
        if ( Bmat_impl( Ppro, p, p ) == IS_IMPL ) {
            VASSERT( Bmat_numR(Ppro, p, p) + Bmat_numC(Ppro, p, p)
                     == (thee->numR)[p] );
        } else {
            VASSERT( Bmat_numR(Ppro, p, p) == (thee->numR)[p] );
        }
    }

    /* Initialize all points as C-points */
    for (p=0; p<numB; p++) {
        uu = (thee->u)[p];
	numR = (thee->numR)[p];
	offset[p] = Bmat_numC(Ppro, p, p);
        for (i=0; i<numR; i++) {
            uu[i] = 'c';
        }
    }

    switch(key) {
      case 0: /* FULL MG */
        for (p=0; p<numB; p++) {
            uu = (thee->u)[p];
            numR = (thee->numR)[p];
	    /* Label all nodes as F-points */
            for (i=0; i<numR; i++) {
                uu[i] = 'f';
            }
        }
      break;
      case 1: /* HBMG */
        for (p=0; p<numB; p++) {
            uu = (thee->u)[p];
            numR = (thee->numR)[p];
	    /* Label all new nodes as F-points */
            for (i=offset[p]; i<numR; i++) {
		uu[i] = 'f';
            }
        }
      break;
      case 2: /* BPXMG */
        for (p=0; p<numB; p++) {
	    for (q=0; q<numB; q++) {
		uu = (thee->u)[p];
		vv = (thee->u)[q];
		AA = (amat->AD)[p][q];
		numR = Mat_numR(AA);
		numC = Mat_numC(AA);
		if( AA->format == DRC_FORMAT ) {
		    VASSERT( AA->state == ASSEMBLED_STATE );
		    VASSERT( numR == numC );
		    IA = AA->IA;
		    JA = AA->JA;
		    diag = AA->diag;
		    offU = AA->offU;
		    offL = AA->offL;
                    for(i=offset[p]; i<numR; i++) {
			uu[i] = 'f';
		    }
                    for(i=0; i<numR; i++) {
			for(k=IA[i]; k<IA[i+1]; k++) {
			    j = JA[k];
			    if( offU[k] != 0. && j >= offset[q] ) {
				uu[i] = 'f';
			    }
			    if( offL[k] != 0. && j >= offset[p] ) {
				vv[i] = 'f';
			    }
			}
		    }
		} else if( AA->format == ROW_FORMAT ) {
		    VASSERT( AA->state == ASSEMBLED_STATE );
		    IA = AA->IA;
		    JA = AA->JA;
		    offU = AA->A;
                    for(i=0; i<numR; i++) {
			for(k=IA[i]; k<IA[i+1]; k++) {
			    j = JA[k];
			    if( offU[k] != 0. && j >= offset[q] ) {
				uu[i] = 'f';
			    }
			    if( offU[k] != 0. && i >= offset[p] ) {
				vv[j] = 'f';
			    }
			}
		    }
                } else if( AA->format == COL_FORMAT ) {
		    VASSERT( AA->state == ASSEMBLED_STATE );
		    IA = AA->IA;
		    JA = AA->JA;
		    offL = AA->A;
                    for(j=0; j<numC; j++) {
			for(k=IA[j]; k<IA[j+1]; k++) {
			    i = JA[k];
			    if( offL[k] != 0. && j >= offset[q] ) {
				uu[i] = 'f';
			    }
			    if( offL[k] != 0. && i >= offset[p] ) {
				vv[j] = 'f';
			    }
			}
		    }
		} else  { VASSERT(0); }
	    }
	}
      break;
      default:
        VASSERT(0);
    }

#if 0 /* DEBUG OUTPUT */
    Vnm_print(0,"Bchar_assem2: ");
    for (p=0; p<numB; p++) {
	uu = (thee->u)[p];
	numR = (thee->numR)[p];
	/* Label all nodes as F-points */
	for (i=0; i<numR; i++) {
	    Vnm_print(0,"%c",uu[i]);
	}
	Vnm_print(0,"|");
    }
    Vnm_print(0,"\n");
#endif
}

/*
 * ***************************************************************************
 * Routine:  Bmat_printBRC
 *
 * Purpose:  Print the boundary row and column indices
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPRIVATE void Bmat_printBRC(Bmat *thee)
{
    Mat *amat;
    int p, i, j, k;

    Vnm_print(0,"Bmat_printBRC: ");
    Vnm_print(0,"BR = {");
    for (p=0; p<thee->numB; p++) {
	if( p == 0 ) {
	    Vnm_print(0,"[");
	} else {
	    Vnm_print(0,", [");
	}
	amat = thee->AD[p][p];
	for (i=0; i<amat->numBR; i++) {
	    Vnm_print(0," %d",amat->BR[i]);
	}
	Vnm_print(0,"]");
    }
    Vnm_print(0,"}; ");
    Vnm_print(0,"BC = {");
    for (p=0; p<thee->numB; p++) {
	if( p == 0 ) {
	    Vnm_print(0,"[");
	} else {
	    Vnm_print(0,", [");
	}
	amat = thee->AD[p][p];
	for (i=0; i<amat->numBC; i++) {
	    Vnm_print(0," %d",amat->BC[i]);
	}
	Vnm_print(0,"]");
    }
    Vnm_print(0,"};\n");
}
