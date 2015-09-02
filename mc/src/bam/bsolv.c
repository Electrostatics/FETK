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
 * rcsid="$Id: bsolv.c,v 1.32 2010/08/12 05:18:25 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     bsolv.c
 *
 * Purpose:  Class Bvec: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "bvec_p.h"

VEMBED(rcsid="$Id: bsolv.c,v 1.32 2010/08/12 05:18:25 fetk Exp $")

/* private routines */
VPRIVATE void Bvec_mgCore(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P);

/*
 * ***************************************************************************
 * Class Bvec: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_BAM)

#endif /* if !defined(VINLINE_BAM) */
/*
 * ***************************************************************************
 * Class Bvec: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Bvec_lmethod
 *
 * Purpose:  Executes one of a number of linear solvers.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_lmethod(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    int meth)
{
    Bvec *w[11];
    Bvec *u = thee;

    if ((flag==0) || (flag==2)) {
        Vnm_tstart(40, "linear solve");
    }

    /* method choice (0=slu,1=mg,2=cg,3=bcg,4=pcg,5=pbcg) */
    switch (meth) {

        /* primary methods */
        case 0:  Bvec_slu( u, A, f, r, ut, key, flag);
                 break;

        case 1:  Bvec_mg( u, A, f, r, ut, key, flag, itmax, etol, prec,
                     cycle, P);
                 break;

        case 2:  Bvec_createVectors(thee, w, 6);
                 Bvec_cg( u, A, f, r, ut, key, flag, itmax, etol, prec,
                      cycle, P,
                      w[0],w[1],w[2],w[3],w[4],w[5] );
                 Bvec_destroyVectors(thee, w, 6);
                 break;

        case 3:  Bvec_createVectors(thee, w, 11);
                 Bvec_bcg( u, A, f, r, ut, key, flag, itmax, etol, prec,
                      cycle, P,
                      w[0],w[1],w[2],w[3],w[4],w[5],w[6],w[7],w[8],w[9],w[10]);
                 Bvec_destroyVectors(thee, w, 11);
                 break;

        /* bad choice */
        default:
                 Vnm_print(0,"Bvec_lmethod: Bad meth given!\n");
                 break;
    }

    if ((flag==0) || (flag==2)) {
        Vnm_tstop(40, "linear solve");
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_slu
 *
 * Purpose:  Sparse LU direct solver (requires only a nonsingular A).
 *
 * Input:    The "flag" variable determines which "mode" we run in:
 *
 *           key ==0   --> Solve: A  u = f
 *           key ==1   --> Solve: A' u = f
 *
 *           flag==0,2 --> Normal: normal i/o
 *           flag==1,3 --> Silent: no i/o
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_slu(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag)
{
    char rn[80];
    double rsnrm, ernrm2, ernrm8;
    double denom, erden2, erden8;

    if (flag==2) {
        strncpy(rn,"--->Bvec_slu:",80);
    } else {
        strncpy(rn,"Bvec_slu:",80);
    }

    if (!Bmat_sluDirect(A)) {
        Vnm_print(2,"%s ------------------------------------------\n", rn);
        Vnm_print(2,"%s WARNING: linear system size is too large  \n", rn);
        Vnm_print(2,"%s     for sparse direct solve; this may take\n", rn);
        Vnm_print(2,"%s     enormous memory and/or CPU resources..\n", rn);
        Vnm_print(2,"%s     ..but MC will do as you ask..sigh...  \n", rn);
        Vnm_print(2,"%s                                           \n", rn);
        Vnm_print(2,"%s     A better alternative is to use one of \n", rn);
        Vnm_print(2,"%s     the available iterative methods.  If  \n", rn);
        Vnm_print(2,"%s     you are already using a multilevel    \n", rn);
        Vnm_print(2,"%s     method and you are reading this       \n", rn);
        Vnm_print(2,"%s     message, then your coarse problem     \n", rn);
        Vnm_print(2,"%s     is too large, and you need to use one \n", rn);
        Vnm_print(2,"%s     of the algebraic coarsening methods   \n", rn);
        Vnm_print(2,"%s     reduce the size of the coarse problem.\n", rn);
        Vnm_print(2,"%s ------------------------------------------\n", rn);
    }

    /* factor (if necessary) */
    VJMPERR1( Bmat_sluFactor(A) );

    /* forward/backward solve the system */
    VJMPERR2( Bmat_sluSolve(A, key, Bvec_addr(f), Bvec_addr(thee)) );

    /* check the solution quality before returning */
    if ((flag==0) || (flag==2)) {

        /* check the residual */
        Bvec_matvec( r, A, thee, key, 0 );
        Bvec_axpy( r, f, (-1.0) );
        Bvec_scal( r, (-1.0) );
        rsnrm = Bvec_nrm2( r );
        denom = Bvec_nrm2( f );
        if (denom == 0.) denom = 1.;

        /* check the analytical (discretization) error */
        ernrm2 = Bvec_dif2( thee, ut );
        ernrm8 = Bvec_dif8( thee, ut );
        erden2 = Bvec_nrm2( ut );
        erden8 = Bvec_nrm8( ut );
        if (erden2 == 0.) erden2 = 1.;
        if (erden8 == 0.) erden8 = 1.;

        Vnm_print(0,"%s it=%4d",rn,0);
        Vnm_print(0,"  rr=%8.2e  r=%8.2e  re2=%8.2e  re8=%8.2e\n",
            rsnrm/denom, rsnrm, ernrm2/erden2, ernrm8/erden8);
    }

    /* return with no errors */
    return;

  VERROR1:
    Vnm_print(2,"%s Factorization failed.\n",rn);
    return;

  VERROR2:
    Vnm_print(2,"%s Solve failed.\n",rn);
    return;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_mg
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
 *           other=?  --> just passed along to Bvec_mgCore()
 *
 * Details:  We use P to build an algebraic multilevel hierarchy in
 *           A,u(thee),f,r,ut from the fine-level-only representations,
 *           and then make the first call to the recursively-callable
 *           core MG algorithm Bvec_mgCore().
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_mg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P)
{
    int iMadeMultilevel = 0;
    Bvec *u = thee;

    /* create multilevel structure if necessary */
    if( thee->coarse == VNULL ) {
        Bvec_mgInit(thee, A, f, r, P);
        iMadeMultilevel = 1;
    }

    /* call multilevel solver */
    Bvec_mgCore(u, A, f, r, ut, key, flag, itmax, etol, prec, cycle, P);

    /* destroy multilevel structure if we made it */
    if (iMadeMultilevel == 1) {
        Bvec_mgDestroy(thee, A, f, r);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_mgInit
 *
 * Purpose:  Initialize the algebraic multilevel hierarchy for Bvec_mg
 *
 * Input:
 *           P=?      --> prolongation operators (linked list)
 *           A=?      --> system matrix
 *           thee=?   --> solution slot
 *           f=?      --> source vector slot
 *           r=?      --> residual slot
 *
 * Details:  We use P to build an algebraic multilevel hierarchy in
 *           A,u(thee),f,r,ut from the fine-level-only representations.
 *           The vectors are created after the matrix to reduce the total
 *           memory usage since Bmat_galerkin uses temporary arrays.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bvec_mgInit(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bmat *P)
{
    int ii, jj, numB, numR[MAXV];
    MATmirror mirror[MAXV][MAXV];
    Bmat *WP, *WA, *RAP;
    Bvec *Wu, *Wf, *Wr;
    Bvec *u = thee;

    numB = Bmat_numB(A);

    /* create multilevel matrix structure */
    WP   = P;
    WA   = A;

    while ((WP != VNULL) && (WA->coarse == VNULL) && (!Bmat_sluDirect(WA))) {

#if 0
	/* remove zero boundary columns from WP */
	Bmat_squeezeBRC(WP, 1);
	/* remove zero boundary rows from WP->coarse */
	if( WP->coarse != VNULL ) {
	    Bmat_squeezeBRC(WP->coarse, 0);
	}
#endif

        /* create the coarse matrix */
        for (ii=0; ii<numB; ii++) {
            numR[ii] = Bmat_numC(WP,ii,ii);
            for (jj=0; jj<numB; jj++) {
                mirror[ii][jj] = Bmat_mirror(WA,ii,jj);
            }
        }
        RAP = Bmat_ctor( u->vmem, "A", numB, numR, numR, mirror );
        Bmat_galerkin( RAP, WP, WA, WP );
        WA->coarse = RAP;

        /* move to coarse level */
        WA  = WA->coarse;
        WP  = WP->coarse;
    }

    /* create multilevel vector structure */
    WP   = P;
    WA   = A;
    Wu   = u;
    Wf   = f;
    Wr   = r;

    while ((WP != VNULL) && (!Bmat_sluDirect(WA))) {

        /* create the coarse vectors */
        for (ii=0; ii<numB; ii++) {
            numR[ii] = Bmat_numC(WP,ii,ii);
        }
        if (Wu->coarse == VNULL ) {
            Wu->coarse  = Bvec_ctor( u->vmem, "u",  numB, numR );
        }
        if (Wf->coarse == VNULL ) {
            Wf->coarse  = Bvec_ctor( u->vmem, "f",  numB, numR );
        }
        if (Wr->coarse == VNULL ) {
            Wr->coarse  = Bvec_ctor( u->vmem, "r",  numB, numR );
        }

        /* move to coarse level */
        WP  = WP->coarse;
        WA  = WA->coarse;
        Wu  = Wu->coarse;
        Wf  = Wf->coarse;
        Wr  = Wr->coarse;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_mgDestroy
 *
 * Purpose:  Destroy algebraic multilevel hierarchy created by Bvec_mgInit
 *
 * Input:
 *           P=?      --> prolongation operators (linked list)
 *           A=?      --> system matrix
 *           thee=?   --> solution slot
 *           f=?      --> source vector slot
 *           r=?      --> residual slot
 *           ut=?     --> true solution slot
 *
 *           other=?  --> just passed along to Bvec_mgCore()
 *
 * Details:  Only the coarser level matrices and vectors are destructed.
 *
 * Author:   Michael Holst and Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Bvec_mgDestroy(Bvec *thee, Bmat *A, Bvec *f, Bvec *r)
{
    /* destroy multilevel structure if it exists */

    if (VNULL != A->coarse)    Bmat_dtor( &(A->coarse) );
    if (VNULL != thee->coarse) Bvec_dtor( &(thee->coarse) );
    if (VNULL != f->coarse)    Bvec_dtor( &(f->coarse) );
    if (VNULL != r->coarse)    Bvec_dtor( &(r->coarse) );
}

/*
 * ***************************************************************************
 * Routine:  Bvec_mgCore
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
VPRIVATE void Bvec_mgCore(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P)
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
        strncpy(rn,"--->Bvec_mgCore:",80);
        prtKey = 1;
    } else {
        strncpy(rn,"Bvec_mgCore:",80);
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
        prec_c  = 0; /* no preconditioner */
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
        Bvec_smooth( u, A, f, r,
            key_s, flag_s, meth_s, adj_s, itmax_s, etol_s, omega_s );

        /* calculate the residual */
        Bvec_matvec( r, A, u, key, 0 );
        Bvec_axpy( r, f, (-1.0) );

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
        Bvec_mgCore( u->coarse, A->coarse, f->coarse, r->coarse, VNULL,
            key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P->coarse );

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
        Bvec_smooth( u, A, f, r,
            key_s, flag_s, meth_s, adj_s, itmax_s, etol_s, omega_s );

        /* iterate */
        iters++;
        if (iters >= itmax) return;
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_cg
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
VPUBLIC void Bvec_cg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bvec *p, Bvec *ap, Bvec *bap, Bvec *po, Bvec *apo, Bvec *tp)
{
    int iters;
    double denom,rsnrm,ernrm2,ernrm8,erden2,erden8;
    double alpha,gamma,sigma,rp,pAp,poApo,BApAp,BApApo,normal;
    int key_m,flag_m,itmax_m,prec_m,cycle_m;
    double etol_m;
    Bvec *u = thee;
    Bvec *w;

    int prtKey = VPRTKEY;
    char rn[80], rmeth[80];

    if (prec == 0) {
        strncpy(rmeth,":",80);
    } else if (prec == 1) {
        strncpy(rmeth,"(ds):",80);
    } else if (prec == 2) {
        strncpy(rmeth,"(mg):",80);
    } else if (prec == 3) {
        strncpy(rmeth,"(sgs):",80);
    } else {
        strncpy(rmeth,":",80);
    }
    if (flag==2) {
        sprintf(rn,"--->Bvec_cg%s",rmeth);
        prtKey = 50;
    } else {
        sprintf(rn,"Bvec_cg%s",rmeth);
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

    if (prec == 2) {
        Bvec_mgInit(bap, A, ap, tp, P);
    }

    if (prec == 3) {
      Bvec_createVectors(u, &w, 1);
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
            if (prec == 2) {
                Bvec_mgDestroy(bap, A, ap, tp);
            }
            return;
        }
        if ( iters >= itmax ) {
            if ( (flag==0) || (flag==2) )
                Vnm_print(0,"%s itmax reached! (rr=%e)\n", rn, rsnrm/denom);
            if (prec == 2) {
                Bvec_mgDestroy(bap, A, ap, tp);
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
            } else if (prec == 2) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_copy( ap, r );  /* Copy reduces no. multilevel vecs */
                Bvec_mg(bap, A, ap, tp, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P);
                Bvec_copy( p, bap ); /* Copy reduces no. multilevel vecs */
            } else if (prec == 3) {
              Bvec_scal(p, 0.0);
              Bvec_smooth(p, A, r, w,
                          0, 1, 2, 0, /*itmax*/ 1, 0.0,
                          0.0);
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
            } else if (prec == 2) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_mg(bap, A, ap, tp, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P);
            } else if (prec == 3) {
              Bvec_scal(bap, 0.0);
              Bvec_smooth(bap, A, ap, w,
                          0, 1, 2, 0, /*itmax*/ 1, 0.0,
                          0.0);
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

    if (prec == 2) {
        Bvec_mgDestroy(bap, A, ap, tp);
    }

    if (prec == 3) {
      Bvec_destroyVectors(u, &w, 1);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_bcg
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
VPUBLIC void Bvec_bcg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
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
    } else if (prec == 2) {
        strncpy(rmeth,"(mg):",80);
    } else {
        strncpy(rmeth,":",80);
    }
    if (flag==2) {
        sprintf(rn,"--->Bvec_bcg%s",rmeth);
        prtKey = 50;
    } else {
        sprintf(rn,"Bvec_bcg%s",rmeth);
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

    if (prec == 2) {
        Bvec_mgInit(bap, A, ap, s, P);
        Bvec_mgInit(btatq, A, atq, s, P);
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
            if (prec == 2) {
                Bvec_mgDestroy(bap, A, ap, s);
                Bvec_mgDestroy(btatq, A, atq, s);
            }
            return;
        }
        if ( iters >= itmax ) {
            if ( (flag==0) || (flag==2) )
                Vnm_print(0,"%s itmax reached! (rr=%e)\n", rn, rsnrm/denom);
            if (prec == 2) {
                Bvec_mgDestroy(bap, A, ap, s);
                Bvec_mgDestroy(btatq, A, atq, s);
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
            } else if (prec == 2) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_copy( ap, r );  /* Copy reduces no. multilevel vecs */
                Bvec_mg(bap, A, ap, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P);
                Bvec_copy( p, bap ); /* Copy reduces no. multilevel vecs */
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
            } else if (prec == 2) {
                key_m   = !key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_copy( atq, s );   /* Copy reduces no. multilevel vecs */
                Bvec_mg(btatq, A, atq, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P);
                Bvec_copy( q, btatq ); /* Copy reduces no. multilevel vecs */
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
            } else if (prec == 2) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_mg(bap, A, ap, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P);
            } else {
                Bvec_copy( bap, ap );
            }

            /* DO: (form: B' A' q^i) */
            if (prec == 0) {
                Bvec_copy( btatq, atq );
            } else if (prec == 1) {
                Bvec_diagScale(btatq, A, atq);
            } else if (prec == 2) {
                key_m   = !key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_mg(btatq, A, atq, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P);
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
            if (prec == 2) {
                Bvec_mgDestroy(bap, A, ap, s);
                Bvec_mgDestroy(btatq, A, atq, s);
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

    if (prec == 2) {
        Bvec_mgDestroy(bap, A, ap, s);
        Bvec_mgDestroy(btatq, A, atq, s);
    }
}

/*
 * ***************************************************************************
 * Routine:  Bvec_eig
 *
 * Purpose:  Calculate the eigenvector corresponding to the second smallest
 *           eigenvalue of the given (symmetric adjacency) matrix.
 *
 * Notes:    We make the following assumptions about the matrix A, which
 *           are valid when A is the adjaceny matrix of a simplex mesh
 *           (e.g., the laplace operator for the dual mesh):
 *
 *               (1) A is symmetric positive semi-definite
 *               (2) A is singular with null space of dimension 1
 *               (3) A has a unique smallest eigenvalue "0" and a
 *                   corresponding unique (up to constant multiplier)
 *                   eigenvector (or null vector) representing the set of
 *                   constant vectors.
 *
 *           Note that since A is symmetric, it has a complete set of
 *           orthonormal eigenvectors.
 *
 *           The algorithm we employ here is a simple inverse iteration
 *           (or Rayleigh quotient iteration) which pulls out the
 *           second smallest eigenvalue (the smallest positive eigenvalue)
 *           and the corresponding eigenvector.  The algorithm simply
 *           does a sequence of inexact inverse iterations, while
 *           repeatedly orthogonalizing the computed eigenvector against
 *           the unique null vector of constants.   The inverse step
 *           damps out all eigendirections other than the smallest, and
 *           the orthgonalizing step removes the smallest eigen direction.
 *
 *           On convergence (change in eigenvector meets a tolerance) then
 *           we generate the corresponding eigenvalue with a final
 *           Rayleigh quotient.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_eig(Bvec *thee, Bmat *A,
    int litmax, double letol, double *lambda,
    int key, int flag, int itmax, double etol)
{
    Bvec *work[5], *f, *r, *ut, *w, *z;
    double rsnrmV, denomV, rsnrmE, denomE, eig, eigOld;
    int prtKey, done, iters, lkey, lflag, lprec, lcycle, lmeth;
    char rn[80];

    if (flag==2) {
        strncpy(rn,"--->Bvec_eig:",80);
        prtKey = 50;
    } else {
        strncpy(rn,"Bvec_eig:",80);
        prtKey = 1;
    }

    /* create the work vectors */
    Bvec_createVectors(thee, work, 5);
    f  = work[0];
    r  = work[1];
    ut = work[2];
    w  = work[3];
    z  = work[4];

    /* null vector */
    Bvec_init(w, 1.0);
    Bvec_scal(w, (1./Bvec_nrm2(w)) );

    /* initial guess -- orthogonalize w.r.t. null vector and normalize */
    if (Bvec_nrm2(thee) < 1.0e-9) {
        Bvec_init(thee, 1.0);
        Bvec_setB(thee, 0, 0, (double)(1-Bvec_numRT(thee)));
    } else {
        Bvec_axpy(thee, w, (-Bvec_dot(thee,w)) );
        VASSERT( Bvec_nrm2(thee) > 1.0e-9 );
    }
    Bvec_scal(thee, (1./Bvec_nrm2(thee)) );
    VASSERT( Bvec_dot(thee, w) < 1.0e-9 );

    /* DO: for i=0,1,2,.... */
    denomE = 0;
    denomV = 0;
    eig = 0.;
    done = 0;
    iters = 0;
    while ((!done) && (!Vnm_sigInt())) {

        /* rayleigh quotient */
        Bvec_matvec(f, A, thee, 0, 0);
        eigOld = eig;
        eig = Bvec_dot(f, thee);

        /* residual vector */
        Bvec_scal(f, (-1.) );
        Bvec_axpy(f, thee, eig);

        /* calculate norm of current residual, setup for i/o */
        rsnrmE = VABS(eig - eigOld);
        rsnrmV = Bvec_nrm2( f );
        if (iters == 0) {
            denomE = rsnrmE;
            denomV = rsnrmV;
            if (denomV == 0.) denomV = 1.;
            if (denomE == 0.) denomE = 1.;
        }

        /* if the main solver, do some i/o */
        if ( ((flag==0) || (flag==2))
           && (((iters%prtKey)==0)
           || ((rsnrmV/denomV<=etol) && (rsnrmE/denomE<=etol)) ) ) {
            Vnm_print(0,"%s it=%4d",rn,iters);
            Vnm_print(0,"  rrv=%8.2e  rre=%8.2e  eig=%8.2e\n",
                rsnrmV/denomV, rsnrmE/denomE, eig);
        }

        /* check stopping criteria */
        if ((rsnrmV/denomV <= etol) && (rsnrmE/denomE <= etol)) done = 1;
        if ( iters >= itmax ) {
            if ( (flag==0) || (flag==2) )
                Vnm_print(0,"%s itmax reached! (rrv=%e,rre=%e)\n",
                    rn, rsnrmV/denomV, rsnrmE/denomE);
            done = 1;
        }

        /* solve linear system for correction */
        lkey    = 0;  /* 0=(Au=f), 1=(A'u=f) */
        lflag   = 1; /* this way we get some i/o if we are the only level */
        lprec   = 0; /* no preconditioner */
        lcycle  = 2; /* symmetric multigrid */
        lmeth   = 3; /* bcg */
        Bvec_init(z, 0.);
        Bvec_lmethod(z, A, f, r, ut, lkey, lflag, litmax, letol, lprec, lcycle,
            VNULL, lmeth);

        /* do the correction */
        Bvec_axpy(thee, z, 1. );

        /* orthogonalize w.r.t. null vector and normalize */
        Bvec_axpy(thee, w, (-Bvec_dot(thee,w)) );
        Bvec_scal(thee, (1./Bvec_nrm2(thee)) );

        /* iterate */
        iters++;
    }

    /* final rayleigh quotient */
    Bvec_matvec(f, A, thee, 0, 0);
    eig = Bvec_dot(f, thee);

    /* destroy the work vectors */
    Bvec_destroyVectors(thee, work, 5);

    /* return with no errors */
    *lambda = eig;
    return;
}

/*
 * ***************************************************************************
 * Routine:  Bvec_cgnr
 *
 * Purpose:  CGNR method (ODIR algorithm, allows for A and B arbitrary).
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
 *           CG=ODIR( M=(BA)'BA, BA=(BA)'BA )
 *           --------------------------------
 *
 *           Given u^0
 *           r^0 = f - A u^0
 *           p^0 = A'B'B r^0 / ||A'B'B r^0||
 *           for i=0,1,2,....
 *               alpha_i = <B r^i, BA p^i> / <BA p^i, BA p^i>
 *               u^{i+1} = u^i + alpha_i p^i
 *               r^{i+1} = r^i - alpha_i A p^i
 *               gamma_i = <BA A'B'BA p^i,BA p^i>     / <BA p^i,    BA p^i>
 *               sigma_i = <BA A'B'BA p^i,BA p^{i-1}> / <BA p^{i-1},BA p^{i-1}>
 *               v       = A'B'BA p^i - gamma_i p^i - sigma_i p^{i-1}
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
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Bvec_cgnr(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bvec *s,
    Bvec *p, Bvec *ap, Bvec *bap, Bvec *po, Bvec *apo,
    Bvec *q, Bvec *atq, Bvec *btatq, Bvec *qo, Bvec *atqo)
{
    int iters;
    double denom,rsnrm,ernrm2,ernrm8,erden2,erden8;
    double alpha,gamma,sigma,normal;
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
    } else {
        strncpy(rmeth,":",80);
    }
    if (flag==2) {
        sprintf(rn,"--->Bvec_cgnr%s",rmeth);
        prtKey = 50;
    } else {
        sprintf(rn,"Bvec_cgnr%s",rmeth);
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

    if (prec == 2) {
        Bvec_mgInit(p, A, r, ap, P);
        Bvec_mgInit(bap, A, ap, s, P);
        Bvec_mgInit(btatq, A, atq, s, P);
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
            if (prec == 2) {
                Bvec_mgDestroy(p, A, r, ap);
                Bvec_mgDestroy(bap, A, ap, s);
                Bvec_mgDestroy(btatq, A, atq, s);
            }
            return;
        }
        if ( iters >= itmax ) {
            if ( (flag==0) || (flag==2) )
                Vnm_print(0,"%s itmax reached! (rr=%e)\n", rn, rsnrm/denom);
            if (prec == 2) {
                Bvec_mgDestroy(p, A, r, ap);
                Bvec_mgDestroy(bap, A, ap, s);
                Bvec_mgDestroy(btatq, A, atq, s);
            }
            return;
        }

        /* form new direction vector */
        if ( iters == 0 ) {

            /* DO: (form: B'B A' r^0) */
            Bvec_matvec( p, A, r, !key, 0 );
            Bvec_copy( r, p );
            if (prec == 0) {
                Bvec_copy( p, r );
            } else if (prec == 1) {
                Bvec_diagScale(p, A, r);
                Bvec_copy( r, p );
                Bvec_diagScale(p, A, r);
            } else if (prec == 2) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_mg(p, A, r, ap, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P);
                Bvec_copy( r, p );
                key_m   = !key;
                Bvec_mg(p, A, r, ap, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P);
            } else {
                Bvec_copy( p, r );
            }

            /* DO: p^0 = B'B A' r^0 / ||B'B A' r^0|| */
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
            } else if (prec == 2) {
                key_m   = key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_mg(bap, A, ap, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P);
            } else {
                Bvec_copy( bap, ap );
            }

            /* DO: (form: B' A' q^i) */
            if (prec == 0) {
                Bvec_copy( btatq, atq );
            } else if (prec == 1) {
                Bvec_diagScale(btatq, A, atq);
            } else if (prec == 2) {
                key_m   = !key;
                flag_m  = 1;
                itmax_m = 1;
                etol_m  = 0.;
                prec_m  = prec;  /* preconditioner */
                cycle_m = 2;     /* symmetric multigrid */
                Bvec_mg(btatq, A, atq, s, ut,
                    key_m, flag_m, itmax_m, etol_m, prec_m, cycle_m, P);
            } else {
                Bvec_copy( btatq, atq );
            }

            /* DO: gamma_i = <A B'B A'A p^i, A p^i> / <A p^i, A p^i> */
            /* DO: gamma_i = <B A p^i, A' q^i> / <A p^i, q^i> */
            BApAtq = Bvec_dot( bap, atq );
            gamma  = BApAtq / Apq;

            /* DO: sigma_i = <AB'BA'Ap^i, Ap^{i-1}> / <Ap^{i-1}, Ap^{i-1}> */
            /* DO: sigma_i = <B A p^i, A' q^{i-1}> / <A p^{i-1}, q^{i-1}> */
            if ( iters == 1 ) {
                sigma = 0.0;
            } else {
                BApAtqo = Bvec_dot( bap, atqo );
                sigma   = BApAtqo / Apoqo;
            }

            /* DO: v = B'B A'A p^i - gamma_i p^i - sigma_i p^{i-1} */
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

        /* DO: alpha_i = <r^i, A p^i> / <A p^i, A p^i> */
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
            if (prec == 2) {
                Bvec_mgDestroy(p, A, r, ap);
                Bvec_mgDestroy(bap, A, ap, s);
                Bvec_mgDestroy(btatq, A, atq, s);
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

    if (prec == 2) {
        Bvec_mgDestroy(p, A, r, ap);
        Bvec_mgDestroy(bap, A, ap, s);
        Bvec_mgDestroy(btatq, A, atq, s);
    }
}

