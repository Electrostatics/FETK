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
 * rcsid="$Id: dyn.c,v 1.7 2010/08/12 05:18:42 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     dyn.c
 *
 * Purpose:  Class Dyn: dynamics library.
 *
 * Author:   Stephen Bond, Michael Holst, Kaihsu Tai, Nathan Baker, Yuhua Song
 * ***************************************************************************
 */
#include "dyn_p.h"

VEMBED(rcsid="$Id: dyn.c,v 1.7 2010/08/12 05:18:42 fetk Exp $")

/* symbolic encoding of method names */
VPRIVATE char *Meth_name[4] = {
   "AM_fEuler",    /* 0 */
   "AM_bEuler",    /* 1 */
   "AM_tSICN ",    /* 2 */
   "AM_tRK4  "     /* 3 */
};

#if 1   /* For non-symmetric problems */
#define len_w 13
#else   /* For symmetric problems */
#define len_w 8
#endif

#undef _LOG_OF_U

/*
 * ***************************************************************************
 * Class Dyn: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_DYN)	

#endif /* if !defined(VINLINE_DYN) */
/*
 * ***************************************************************************
   Class Dyn: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  AM_tSolve
 *
 * Purpose:  Solution of Time-Dependent problems by Method of Lines.
 *
 * Author:   Stephen Bond and Kaihsu Tai
 * ***************************************************************************
 */
VPUBLIC void AM_tSolve(AM *thee, int meth, double dt, double t0, int numstep,
    int pfreq, int efreq, int ekeytotal, DYNtype pdetype,
    double ltol, int lmax, SVio *vsock)
{
    int imadeDyn=0, ip[20];
    int evalKey=0, energyKey=0, residKey=1, tangKey=1, massKey=1, bumpKey=0;
    double rp[20];

    /* some i/o */
    Vnm_print(0,"AM_tSolve: starting..");

    /* Initialize PDE Structure */
    if( ! PDE_checkDyn( thee->aprx->pde ) ) {
        PDE_initDyn( thee->aprx->pde );
        imadeDyn = 1;
    }

    /* setup the initial condition by copying ui into u */
    AM_iniGuess( thee, thee->u );

    /* clear the matrices and rhs */
    Bmat_zero( thee->A );
    Bmat_zero( thee->M );
    Bvec_init( thee->f, 0. );
    Bvec_init( thee->w0, 0. );

    /* assemble the stiffness matrix and load vector */
    rp[0] = 1.0;
    AM_assem( thee,
        evalKey, energyKey, residKey, tangKey, massKey, 
        bumpKey,
        thee->u, thee->ud, thee->f, ip, rp );

    /* call the chosen solver */
    AM_tStepper( thee, meth, pdetype, 
        dt, t0, numstep, pfreq, efreq, ekeytotal, ltol, lmax, vsock );

    /* kill our private PDE structure */
    if( imadeDyn ) {
        PDE_killDyn( thee->aprx->pde);
    }

    Vnm_print(0,"AM_tSolve: done.\n");

    /* return with no errors */
    return;
}

/*
 * ***************************************************************************
 * Routine:  AM_tStepper
 *
 * Purpose:  Several Generalized Theta Methods for LINEAR PDEs including
 *           Trapezoidal, Forward, and Backward Euler
 *
 * Input:    The "pfreq" variable determines which "mode" we run in:
 *
 *           pfreq==0 --> never output the solution
 *           pfreq==n --> output the solution every 'n' steps
 *
 *           efreq==0 --> never output the energy
 *           efreq==n --> output the energy every 'n' steps
 *
 * Notes:    Theta methods are simple one-step methods applied to the
 *           linear vector field (-1) M^{-1} A(u) u.  The core
 *           timestepping map is the exp approximation:
 *
 *           u_{n+1}  = Exp[-dt*M^{-1}*A] u_n
 *                   ~= [M + theta*dt*A]^{-1} [M - (1-theta)*dt*A] u_n
 *
 *           For the linear scalar problem, one can show that the stability
 *           region is described by 
 *             |1 - a*dt| <= 1   for Forward Euler,  theta = 0
 *             |1 + a*dt| >= 1   for Backward Euler, theta = 1
 *             |2 + a*dt| <= |2 - a*dt| for Trapez., theta = 0.5
 *
 * Author:   Stephen Bond and Kaihsu Tai
 * ***************************************************************************
 */
VPRIVATE void AM_tStepper(AM *thee, int meth, DYNtype pdetype,
    double dt, double t0, int numstep, int pfreq, int efreq,
    int ekeytotal, double ltol, int lmax, SVio *vsock)
{
    int ip[20], iters, piters, ekey;
#if 0
    int evalKey=1, energyKey=0, residKey=1, massKey=0;
#endif
    double rp[20], time = t0, theta = 1.0, energy;
    Bvec *u, *ud, *f, *w0, *w[len_w];
    Bmat *cmat = VNULL, *A = VNULL, *M = VNULL;

    Vnm_tstart(40, "time solve");

    /* local pointers */
    u = thee->u; f = thee->f; w0 = thee->w0; ud = thee->ud;
    A = thee->A; M = thee->M;

    /* create work vectors */
    Bvec_createVectors( u, w, len_w );

    switch(meth) {
    case 0: /* Forward Euler */
        cmat = M;
        theta = 0.0;
        break;
    case 1: /* Backward Euler */
        cmat = Bmat_clone( thee->vmem, "C", A );
        Bmat_copy( cmat, M );
        Bmat_axpy( cmat, A, dt, 0 );
        theta = 1.0;
        break;
    case 2: /* Trapezoidal Rule */
        cmat = Bmat_clone( thee->vmem, "C", A );
        Bmat_copy( cmat, M );
        Bmat_axpy( cmat, A, 0.5*dt, 0 );
        theta = 0.5;
        break;
    default:
        Vnm_print(2,"Bad Method!\n");
        return;
    }

    /* Set the initial time */
    PDE_setTime( thee->aprx->pde, time );

    Vnm_print(0,"%s: taking %d steps with dt = %12.8e.\n",
        Meth_name[meth], numstep, dt);

    /* DO: for i=0,1,2,... */
    iters = 0;  piters = 0;
    while (!Vnm_sigInt()){    /* Start Main Loop */

        if ( (pfreq > 0) && !(iters%pfreq) ) {  /* Print contour */
            Bvec_copy( w0, u );
            Bvec_axpy( w0, ud, 1.0 );
#ifdef _LOG_OF_U
            Bvec_abslog( w0, VSMALL );
#endif
            Aprx_writeSVio( thee->aprx, piters, w0, vsock );
            piters++;
        }

        if ( (efreq > 0) && !(iters%efreq) ) {  /* Print Energy */
            Vnm_print(0, "\n time = %6.2f", iters*dt);
            for (ekey = 0; ekey < ekeytotal; ekey++) {
                PDE_setEnergyKey(thee->aprx->pde, ekey);
                energy = Aprx_assem( thee->aprx,
                  /*eval*/ 1, /*ener*/ 1, /*resd*/ 0, /*tang*/ 0, /*mass*/ 0,
                  /*bump*/ 0,
                    ip, rp, A, M, f, u, ud);
                Vnm_print(0,", Ju (%2d) = %8.4e", ekey, energy);
            }
            Vnm_print(0,"\n");

            /* NAB/YHS:  Allow for external user-defined processing command */
            PDE_userStepHook(thee->aprx->pde, thee, ekey);
        }

        /* check stopping criteria */
        if ( iters >= numstep ) {
            goto DONE;
        }

        switch( pdetype ) {
        case SIMP_TYPE:
            break;
        case TDEP_TYPE:
            Bvec_init(f, 0.0);
            PDE_setTime( thee->aprx->pde, time + theta*dt );
            energy = Aprx_assem( thee->aprx,
                /*eval*/ 0, /*ener*/ 0, /*resd*/ 1, /*tang*/ 0, /*mass*/ 0,
                /*bump*/ 0,
                ip, rp, A, M, f, u, ud);
            break;
        case NLIN_TYPE:
            Bvec_init(f, 0.0);
            energy = Aprx_assem( thee->aprx,
                /*eval*/ 1, /*ener*/ 0, /*resd*/ 1, /*tang*/ 1, /*mass*/ 0,
                /*bump*/ 0,
                ip, rp, A, M, f, u, ud);
            break;
        default:
            Vnm_print(2,"%s warning: Bad PDE type!\n",Meth_name[meth]);
            break;
        }

        /* DO: W1 = (M - (1-theta)*dt*A)*U_{n} + dt*f */
        Bvec_matvec(w[0], M, u, 0, 0);
        if (theta != 1.0) {
            Bvec_matvec(w[1], A, u, 0, 0);
            Bvec_axpy(w[0],w[1],(theta-1.0)*dt);
        }

        Bvec_axpy(w[0],f,dt);

#if 1   /* For non-symmetric problems */
        Bvec_bcg( u, cmat, w[0], w[1], u, 0, 3,  lmax, ltol,
                 1, 0, VNULL,
              w[2], w[3], w[4], w[5], w[6], w[7],
              w[8], w[9], w[10], w[11], w[12] );
        /*  ( thee,   A,   f,   r, ut, key, flag, itmax, etol,
                  prec, cycl, P, w0, ... , w10 ) */
#else  /* For symmetric problems */
        Bvec_cg( u, cmat, w[0], w[1], u, 0, 3,  lmax, ltol,
                 1, 0, VNULL,
              w[2], w[3], w[4], w[5], w[6], w[7] );
        /*  ( thee,   A,   f,   r, ut, key, flag, itmax, etol,
                  prec, cycl, P, w0, ... , w5 ) */
#endif

        /* iterate */
        iters++;
        time += dt;
        PDE_setTime( thee->aprx->pde, time );

   }						/* End Main Loop */

DONE:
    Vnm_tstop(40, "time solve");

    /* destroy iteration matrix and work vectors */
    if (meth != 0) {
        Bmat_dtor(&cmat);
    }
    Bvec_destroyVectors( u, w, len_w );

    return;

}

/*
 * ***************************************************************************
 * Routine:  PDE_initDyn
 *
 * Purpose:  Construct the Dyn PDE datastructure inside the PDE structure.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void PDE_initDyn(PDE *thee)
{
    /* error checking */
    VASSERT( thee != VNULL );
    VASSERT( thee->user == VNULL);

    if( thee->user == VNULL ) {
        thee->user = Vmem_malloc( VNULL, 1, sizeof(DynPDE) );

        PDE_setTime(thee, 0.0);

        /* NAB/YHS:  set userStepHook function pointer to NULL */
        PDE_nullUserStepHook(thee);
    }


}
/*
 * ***************************************************************************
 * Routine:  PDE_killDyn
 *
 * Purpose:  Destruct the Dyn PDE datastructure inside the PDE structure.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void PDE_killDyn(PDE *thee)
{
    if( thee->user != VNULL ) {
        Vmem_free( VNULL, 1, sizeof(DynPDE), (void **)(&(thee->user)) );
    }
}
/*
 * ***************************************************************************
 * Routine:  PDE_checkDyn
 *
 * Purpose:  Checks to see if the Dyn PDE structure has been created.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC int PDE_checkDyn(PDE *thee) {
    double value = 1;

    VASSERT( thee != VNULL ); /* error checking */
    if( thee->user == VNULL ) value = 0;

    return value;
}

/*
 * ***************************************************************************
 * Routine:  PDE_setTime
 *
 * Purpose:  Set the time variable in the Dyn PDE structure
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void PDE_setTime(PDE *thee, double mytime)
{
    ((DynPDE *)(thee->user))->time = mytime;
}

/*
 * ***************************************************************************
 * Routine:  PDE_nullUserStepHook
 *
 * Purpose:  Set the UserStepHook function pointer to VNULL
 *
 * Author:   Nathan Baker
 * ***************************************************************************
 */
VPUBLIC void PDE_nullUserStepHook(PDE *thee) { 

    DynPDE *dynPDE;

    dynPDE = (DynPDE *)(thee->user);
    dynPDE->userStepHook = VNULL;
    dynPDE->haveUserStepHook = 0;
}

/*
 * ***************************************************************************
 * Routine:  PDE_setUserStepHook
 *
 * Purpose:  Set the userStepHook function pointer in the Dyn PDE structure
 *
 * Author:   Nathan Baker
 * ***************************************************************************
 */
VPUBLIC void PDE_setUserStepHook(PDE *thee, 
        void (*userStepHook)(PDE *thee, AM *am, int ekey)) {

    DynPDE *dynPDE;

    dynPDE = (DynPDE *)(thee->user);
    dynPDE->userStepHook = userStepHook;
    dynPDE->haveUserStepHook = 1;
}

/*
 * ***************************************************************************
 * Routine:  PDE_userStepHook
 *
 * Purpose:  Call the userStepHook function
 *
 * Author:   Nathan Baker
 * ***************************************************************************
 */
VPUBLIC void PDE_userStepHook(PDE *thee, AM *am, int ekey) {

    DynPDE *dynPDE;

    dynPDE = (DynPDE *)(thee->user);
    if (dynPDE->haveUserStepHook) {
        dynPDE->userStepHook(thee, am, ekey);
    }
}


/*
 * ***************************************************************************
 * Routine:  PDE_getTime
 *
 * Purpose:  Get the time variable from the Dyn PDE structure
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC double PDE_getTime(PDE *thee )
{
    if( thee->user != VNULL ) {
        return ((DynPDE *)(thee->user))->time;
    } else {
        return 0.0;
    }
}

/*
 * ***************************************************************************
 * Routine:  PDE_setEnergyKey
 *
 * Purpose:  Set the energy key variable in the Dyn PDE structure
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void PDE_setEnergyKey(PDE *thee, int ekey)
{
    ((DynPDE *)(thee->user))->ekey = ekey;
}

/*
 * ***************************************************************************
 * Routine:  PDE_getEnergyKey
 *
 * Purpose:  Get the energy key variable from the Dyn PDE structure
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC int PDE_getEnergyKey(PDE *thee)
{
    if( thee->user != VNULL ) {
        return ((DynPDE *)(thee->user))->ekey;
    } else {
        return 0;
    }
}

