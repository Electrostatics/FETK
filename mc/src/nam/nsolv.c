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
 * rcsid="$Id: nsolv.c,v 1.21 2010/08/12 05:19:13 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     nsolv.c
 *
 * Purpose:  Class AM: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "am_p.h"

VEMBED(rcsid="$Id: nsolv.c,v 1.21 2010/08/12 05:19:13 fetk Exp $")

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
 * Routine:  AM_nSolve
 *
 * Purpose:  Nonlinear solver.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_nSolve(AM *thee,
    int meth, int itmax, double etol,
    int lmeth, int litmax, double letol, int lprec, int gues, int pjac)
{
    Vnm_tstart(50, "nonlinear solve");

    Vnm_print(0,"AM_nSolve: starting..");

    /* make sure we have structure */
    AM_create(thee);

    /* initial guess */
    if (gues == 0) {
        Vnm_print(0,"..using zero as initial approximation..\n");
        Bvec_init(thee->u, 0.);
        AM_applyDiriZero( thee, thee->u );
    } else if (gues == 1) {
        Vnm_print(0,"..using u_D as initial approximation..\n");
        AM_iniGuess( thee, thee->u );
        AM_applyDiriZero( thee, thee->u );
    } else if (gues == 2) {
        Vnm_print(0,"..using u as initial approximation..\n");
        AM_applyDiriZero( thee, thee->u );
    } else {
        Vnm_print(0,"..using zero as initial approximation..\n");
        Bvec_init(thee->u, 0.);
        AM_applyDiriZero( thee, thee->u );
    }

    /* do [homotopy] or [newton] */
    if (meth==0) {
        AM_newton(thee, itmax, etol, lmeth, litmax, letol, lprec, pjac, 1.0);
    } else if (meth==1) {
        AM_homotopy(thee, itmax, etol, lmeth, litmax, letol, lprec, pjac);
    } else Vnm_print(0,"AM_nSolve: bad meth given.\n");

    Vnm_tstop(50, "nonlinear solve");

    /* return with no errors */
    return;
}

/*
 * ***************************************************************************
 * Routine:  AM_newton
 *
 * Purpose:  Damped-Inexact Newton iteration.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_newton(AM *thee,
    int itmax, double etol,
    int lmeth, int litmax, double letol, int lprec, int pjac, double loadParm)
{
    Bvec *w1;

    /* iteration parameters */
    int idamp   = 1;      /* 0=no damp-ing; 1=damp-ing  */
    int itmax_d = 10;     /* damp-ing iteration max     */
    double damp = 1.0;    /* damp-ing parameter         */
    double mu   = 0.25;   /* for sufficient decrease    */

    int key_s,flag_s,itmax_s,prec_s,cycle_s,meth_s;
    double etol_s;

    /* other parameters */
    int iters   = 0;
    int iters_d = 0;
    int done    = 0;
    double ernrm2 = 0.0;
    double ernrm8 = 0.0;
    double erden2 = 0.0;
    double erden8 = 0.0;
    double rsnrm     = 0.0;
    double rsnrm_old = 0.0;
    double rsnrm2     = 0.0;
    double rsnrm2_old = 0.0;

    /* assembly parameters */
    int ip[10];
    double rp[10];
    int evalKey, energyKey, residKey, tangKey, massKey, bumpKey;
    char jname[256];

    /* some i/o */
    Vnm_print(0,"AM_newton: starting..\n");

    /* make sure we have structure */
    AM_create(thee);

    /* create work vectors */ 
    Bvec_createVectors(thee->u, &w1, 1);

    /* initialize residual and work vector */
    Bvec_init( thee->r,  0. );
    Bvec_init( thee->w0, 0. );
    Bvec_init( w1, 0. );

    /* deal with i/o */
    erden2 = Bvec_nrm2( thee->ut );
    erden8 = Bvec_nrm8( thee->ut );
    if (erden2 == 0.0) erden2 = 1.0;
    if (erden8 == 0.0) erden8 = 1.0;

    /* do the newton iteration */
    Vnm_print(0,"AM_newton: starting newton iteration..\n");
    iters = -1;
    while (!Vnm_sigInt()) {
        iters++;

        /* assemble jacobian and nonlinear resid at current solution (u) */
        Bmat_zero( thee->A );
        Bvec_init(thee->f, 0.);
        rp[0] = loadParm; /* use the incoming load parameter */
        evalKey   = 1; /* get nonlinear residual and tangent matrix */
        energyKey = 0;
        residKey  = 1;
        tangKey   = 1;
        massKey   = 0;
	bumpKey = 0;
        AM_assem(thee,
            evalKey, energyKey, residKey, tangKey, massKey,
            bumpKey,
            thee->u, thee->ud, thee->f, ip, rp);
        if ((pjac == -2) || (pjac == iters)) {
            sprintf(jname,"jac_%d.m",iters);
            AM_printAsp(thee, jname);
        }
        rsnrm  = Bvec_nrm2( thee->f );
        rsnrm2 = rsnrm * rsnrm;

        /* check stopping criteria tests and do some i/o */
        ernrm2 = Bvec_dif2( thee->ut, thee->u );
        ernrm8 = Bvec_dif8( thee->ut, thee->u );
        Vnm_print(0,"AM_newton: it=%4d",iters);
        Vnm_print(0,"  r=%8.2e  re2=%8.2e  re8=%8.2e\n",
            rsnrm, ernrm2/erden2, ernrm8/erden8);
        if ( rsnrm <= etol ) return;
        if ( iters >= itmax ) {
            Vnm_print(0,"AM_newton: itmax reached! (r=%e)\n", rsnrm);
            return;
        }

        /* solve jacobian system for correction (w0) and update (u) */
        key_s   = 0;       /* A u = f */
        flag_s  = 2;       /* i/o flag */
        itmax_s = litmax;  /* iteration max for linear solver */
        etol_s  = letol;   /* error tolerance for linear solver */
        prec_s  = lprec;   /* preconditioner */
        cycle_s = 2;       /* symmetric multigrid */
        meth_s  = lmeth;   /* specified linear solver */
        Bvec_init( thee->w0, 0. );

        /* call the chosen linear solver */
        Bvec_lmethod( thee->w0, thee->A, thee->f, thee->r, thee->ut,
            key_s, flag_s, itmax_s, etol_s, prec_s, cycle_s, thee->P, meth_s );
        AM_applyDiriZero( thee, thee->w0 );

       /*
        * ********************************************************************
        * We can DAMP the Newton step in several ways.
        *
        * METHOD 1 (simple approach: sufficient descent)
        * --------
        *
        *    (1) Set t=1, mu = 0.25
        *    (2) IF (||F(u+tv)||_2 <= (1-t mu)||F(u)||_2) THEN GOTO (5)
        *    (3) Set t=t/2
        *    (4) GOTO (2)
        *    (5) Accept tv as the Newton step
        *
        *          
        * METHOD 2 (more intelligent)
        * --------
        *
        * We perform a quadratic fit to the nonlinearity, and minimize
        * this quadratic analytically.
        *
        * First let
        *          J(t)=(1/2)||F(u+tv)||_2^2
        * Then
        *          J(0)=(1/2)||F(u)||_2^2
        *          J(1)=(1/2)||F(u+v)||_2^2
        * Also
        *          J'(0)=(F(u),F'(u)v)_2
        *
        * All three of these are computable from quantities available in the
        * Newton iteration.  Now, consider the quadratic polynomial
        *
        *          p(x) = a x^2 + b x + c,
        * where
        *          J(0)  = p(0)  = c
        *          J'(0) = p'(1) = b
        *          J(1)  = p(1)  = a + c + b
        * thus
        *          a = J(1)-J(0)-J'(0)
        * and so
        *          p(x) = [J(1)-J(0)-J'(0)] x^2 + [J'(0)] x + [J(0)]
        *
        * This quadratic is minimized at p'(x)=0, or
        *
        *          p'(x) = 2 a x + b = 0,
        * or
        *          x = -b / 2a = -[J'(0)] / (2 [J(1)-J(0)-J'(0)])
        *
        * This is provides the Newton steplength
        *
        *          unew = uold + t v
        * where
        *          t = - (F(u),F'(u)v)_2 / 
        *              ( ||F(u+v)||_2^2  - ||F(u)||_2^2 - (F(u),F'(u)v)_2 )
        * ********************************************************************
        */

        /* apply the Newton correction */
        done = 0;
        damp = 1.0;
        Bvec_copy( w1, thee->u );
        Bvec_axpy( w1, thee->w0, damp );

        /* do a linesearch */
        if (idamp == 0) {

            Bvec_copy( thee->u, w1 );

        } else { /* (idamp == 1) */

            /* do the iterative linesearch */
            rsnrm_old  = rsnrm;
            rsnrm2_old = rsnrm_old * rsnrm_old;
            iters_d = 0;
            while ((!done) && (iters_d < itmax_d)) {

                /* skip on first iteration */
                if (iters_d > 0) {
                    Bvec_copy( w1, thee->u );
                    Bvec_axpy( w1, thee->w0, damp );
                }

                /* form nonlinear resid at proposed corrected solution */
                Bvec_init(thee->f, 0.);
                evalKey   = 1; /* get only nonlinear residual */
                energyKey = 0;
                residKey  = 1;
                tangKey   = 0;
                massKey   = 0;
		bumpKey = 0;
                AM_assem(thee,
                    evalKey, energyKey, residKey, tangKey, massKey,
                    bumpKey,
                    w1,thee->ud,thee->f,ip,rp);
                rsnrm  = Bvec_nrm2( thee->f );
                rsnrm2 = rsnrm * rsnrm;
                Vnm_print(0,"AM_newton: damp: iters_d=%4d  resid=%8.2e\n",
                    iters_d, rsnrm);

                /* check residual */
                if (rsnrm2 > ((1.0 - damp * mu) * rsnrm2_old)) {
                    damp /= 2.0;
                } else {
                    done = 1;
                }
                iters_d++;
            }

            /* w1 has reduced the energy; copy him over to u */
            Bvec_copy( thee->u, w1 );

            /* check stopping criteria tests and do some i/o */
            ernrm2 = Bvec_dif2( thee->ut, thee->u );
            ernrm8 = Bvec_dif8( thee->ut, thee->u );
            if ( rsnrm <= etol ) {
                Vnm_print(0,"AM_newton: it=%4d",iters+1);
                Vnm_print(0,"  r=%8.2e  re2=%8.2e  re8=%8.2e\n",
                    rsnrm, ernrm2/erden2, ernrm8/erden8);
                return;
            }
        }
    }

    /* destroy work vectors */
    Bvec_destroyVectors(thee->u, &w1, 1);
}

/*
 * ***************************************************************************
 * Routine:  AM_homotopy
 *
 * Purpose:  Homotopy and the related "incremental loading" iterations.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_homotopy(AM *thee,
    int itmax, double etol,
    int lmeth, int litmax, double letol, int lprec, int pjac)
{
    double step, Nsteps, cParm;

    /* assembly parameters */
    Nsteps = 10;
    step   = 1.0 / (Nsteps+1);

    /* do the homotopy iteration */
    cParm = 0.0 - step;
    while (!Vnm_sigInt()) {
        cParm = cParm + step;
        Vnm_print(0,"AM_homotopy: continuation parameter cparm=<%17.10le>\n",
             cParm);
        AM_newton(thee,itmax,etol,lmeth,litmax,letol,lprec,pjac,cParm);
        if ( VABS( cParm - 1.0 ) < VSMALL ) return; 
    }
}

