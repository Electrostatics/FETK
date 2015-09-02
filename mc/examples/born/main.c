/* ///////////////////////////////////////////////////////////////////////////
//  MC = < Manifold Code >
//  Copyright (C) 1994-- Michael Holst 
//
//  This library is free software; you can redistribute it and/or 
//  modify it under the terms of the GNU Lesser General Public 
//  License as published by the Free Software Foundation; either  
//  version 2.1 of the License, or (at your option) any later version. 
//
//  This library is distributed in the hope that it will be useful, 
//  but WITHOUT ANY WARRANTY; without even the implied warranty of             
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//  Lesser General Public License for more details. 
//
//  You should have received a copy of the GNU Lesser General Public 
//  License along with this library; if not, write to the Free Software  
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   
//
//  rcsid="$Id: main.c,v 1.4 2010/08/12 05:16:32 fetk Exp $"
// //////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////////
// File:     main.c
//
// Purpose:  Main driver for the Manifold Code (MC)
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */

#include "mypde.h"
#include "mc/whb.h"

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void**)&rcsid);
VEMBED(rcsid="$Id: main.c,v 1.4 2010/08/12 05:16:32 fetk Exp $")

/*
 * ***************************************************************************
 * Routine:  AM_subSolve
 *
 * Purpose:  Suboptimal Linear solver.
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */
VPUBLIC void AM_subSolve(AM *thee, int prob,
    int meth, int itmax, double etol, int prec, int gues, int pjac)
{
    /* assembly parameters */
    int key, flag, cycle, ip[10];
    int evalKey, energyKey, residKey, tangKey, massKey, bumpKey;
    double rp[10];
    Bvec *u_use;

    /* some i/o */
    Vnm_print(0,"AM_subSolve: starting..");

    /* make sure we have structure */
    AM_create(thee);

    /* setup for assembling either primal or dual problem */
    energyKey = 0;
    massKey   = 0;
    bumpKey   = 0;
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
        evalKey, energyKey, residKey, tangKey, massKey, bumpKey,
        thee->u, thee->ud, thee->f, ip, rp);
    if ((pjac == -2) || (pjac == 0)) AM_printAsp(thee, "jac.m");

    /* call the chosen linear solver */
    key   = 0; /* A u = f */
    flag  = 0; /* i/o flag */
    cycle = 2; /* symmetric multigrid */
    Bvec_submethod( u_use, thee->A, thee->f, thee->r, thee->ut,
        key, flag, itmax, etol, prec, cycle, thee->P, meth );

    Vnm_print(0,"AM_subSolve: done.\n");

    /* return with no errors */
    return;
}

/* Some help to organize the application-specific shell commands */
typedef enum APPcommand {
    app_none,
    app_help,
    app_stat,
    app_hello,
    app_hlsolve,
    app_subsolve,
    app_printA,
    app_printP,
    app_bye
} APPcommand;

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  APPgetCmd
//
// Purpose: The application-specific shell parser
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPRIVATE APPcommand APPgetCmd(MCsh *thee, int argc, char *argv[])
{
    APPcommand theCmd = app_none;
    if (!strcmp(argv[0],"")) {
        theCmd = app_none;
    } else if (!strcmp(argv[0],"help")) {
        theCmd = app_help;
    } else if (!strcmp(argv[0],"stat")) {
        theCmd = app_stat;
    } else if (!strcmp(argv[0],"hello")) {
        theCmd = app_hello;
    } else if (!strcmp(argv[0],"hlsolve")) {
        theCmd = app_hlsolve;
    } else if (!strcmp(argv[0],"subsolve")) {
        theCmd = app_subsolve;
    } else if (!strcmp(argv[0],"printA")) {
        theCmd = app_printA;
    } else if (!strcmp(argv[0],"printP")) {
        theCmd = app_printP;
    } else if (!strcmp(argv[0],"bye")) {
        theCmd = app_bye;
    } else {
        theCmd = app_none;
    }
    return theCmd;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  APVsh
//
// Purpose: The application-specific shell for enriching the Vsh_shell
//          or for overriding the builtin Vsh_shell commands.
//
// Return codes (required):
//
//     rc=0   --> APVsh does not know about this command
//     rc=1   --> APVsh handled this command sucessfully
//     rc=2   --> APVsh handled this command sucessfully and wants to exit!
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPRIVATE int APVsh(void *pthee, int argc, char *argv[])
{
    MCsh *thee = (MCsh*)pthee;

    int rc;
    APPcommand theCmd;
    static int init=0;

    /* one-time intialization */
    if (!init) {
       init=1;
    }

    /* default return code (success) */
    rc = 1;

    /* get the command */
    theCmd = APPgetCmd(thee, argc, argv);

    /* decode and execute the command */
    switch (theCmd) {

      case app_help:
        if (argc==1) {
            Vnm_print(1,"%s: Application-layer Help Menu:\n",
                Vsh_getenv(thee->vsh,"SHELL"));
            Vnm_print(1,"    help      --> Print this menu.\n");
            Vnm_print(1,"    stat      --> Print some environ variables.\n");
            Vnm_print(1,"    hello     --> Print 'Hello, World!'.\n");
            Vnm_print(1,"    hlsolve   --> Call hierarchical basis solver.\n");
            Vnm_print(1,"    subsolve  --> Call suboptimal solver.\n");
            Vnm_print(1,"    printA    --> Print A to 'loadA.m'.\n");
            Vnm_print(1,"    printP    --> Print P to 'loadP.m'.\n");
            Vnm_print(1,"    bye       --> Print 'Bye, World!' and exit.\n");
            rc = 0;  /* pretend we didn't see it so subshell can help too */
        } else {
            rc = 0;  /* pretend we didn't see it so subshell can help too */
        }
        break;

      case app_stat:
        Vnm_print(1,"%s(APVsh): IFNAM=<%s>  LMAX=<%d>  LTOL=<%e>\n",
            Vsh_getenv(thee->vsh,"SHELL"),
            Vsh_getenv(thee->vsh,"IFNAM"),
            Vsh_getenvInt(thee->vsh,"LMAX"),
            Vsh_getenvReal(thee->vsh,"LTOL"));
        break;

      case app_hello:
        Vnm_print(1,"%s(APVsh): Hello, World!\n",
            Vsh_getenv(thee->vsh,"SHELL"));
        break;

      case app_hlsolve:
        AM_create(thee->am);
        AM_hlSolve(thee->am,
            0,
            Vsh_getenvInt(thee->vsh,"LKEY"),
            Vsh_getenvInt(thee->vsh,"LMAX"),
            Vsh_getenvReal(thee->vsh,"LTOL"),
            Vsh_getenvInt(thee->vsh,"PREC"),
            Vsh_getenvInt(thee->vsh,"GUES"),
            Vsh_getenvInt(thee->vsh,"PJAC"));
        break;
      case app_subsolve:
        AM_create(thee->am);
        AM_subSolve(thee->am,
            0,
            Vsh_getenvInt(thee->vsh,"LKEY"),
            Vsh_getenvInt(thee->vsh,"LMAX"),
            Vsh_getenvReal(thee->vsh,"LTOL"),
            Vsh_getenvInt(thee->vsh,"PREC"),
            Vsh_getenvInt(thee->vsh,"GUES"),
            Vsh_getenvInt(thee->vsh,"PJAC"));
        break;
      case app_printA:
        AM_printAsp(thee->am, "loadA.m");
        break;
      case app_printP:
        AM_printPsp(thee->am, "loadP.m");
        break;
      case app_bye:
        Vnm_print(1,"%s(APVsh): Bye, World!\n",
            Vsh_getenv(thee->vsh,"SHELL"));
        rc = 2;
        break;

      default:
        rc = 0;
        break;
    }
    return rc;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  main
//
// Purpose: The main driver for initiating the Vsh_shell.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
int main(int argc, char **argv)
{
    PDE *myPde = VNULL;
    MCsh *mc = VNULL;

    /* ********************************************************************* */
    /* NOTE: avoiding Vnm_print before MCsh_ctor() allows output file tagging */
    /* ********************************************************************* */

    /* construct the PDE object */
    myPde = myPDE_ctor();

    /* construct the MCsh object */
    mc = MCsh_ctor(myPde,argc,argv);

    /* start the MCsh command shell */
    MCsh_shell(mc,APVsh);

    /* destroy the MCsh object */
    MCsh_dtor(&mc);

    /* destroy the PDE object */
    myPDE_dtor(&myPde);

    /* some final i/o */
    Vnm_print(1,"\n");
    Vnm_print(1,"mc_leaks = [\n");
    Vnm_print(1,"%% --------------------------------------"
                "--------------------------------------\n");
    Vnm_print(1,"%%  Footprint        Areas       Malloc         Free"
                "    Highwater   Class\n"),
    Vnm_print(1,"%% --------------------------------------"
                "--------------------------------------\n");
    Vmem_print(VNULL);
    Vmem_printTotal();
    Vnm_print(1,"%% --------------------------------------"
                "--------------------------------------\n");
    Vnm_print(1,"];\n");

    /* normal return */
    return 0;
}

