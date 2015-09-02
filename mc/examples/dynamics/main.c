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
//  rcsid="$Id: main.c,v 1.3 2010/08/12 05:16:34 fetk Exp $"
// //////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////////
// File:     main.c
//
// Purpose:  Main driver for the Manifold Code (MC)
//
// Author:   Kaihsu Tai, Stephen Bond, Michael Holst
/////////////////////////////////////////////////////////////////////////// */

#include "mypde.h"
#include "mc/dyn.h"

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void**)&rcsid);
VEMBED(rcsid="$Id: main.c,v 1.3 2010/08/12 05:16:34 fetk Exp $")

VPRIVATE AM  *am;
VPRIVATE PDE *pde;
VPRIVATE Gem *gm;

/* Some help to organize the application-specific shell commands */
typedef enum APPcommand {
    app_none,
    app_help,
    app_stat,

    app_qread,
    app_quit,
    app_qinit,
    app_qstep,
    app_qwritedx,
    app_qinfo,
    app_qhelp,

    /* Add your new command here */

    app_hello,
    app_bye
} APPcommand;

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  APPgetCmd
//
// Purpose: The application-specific shell parser
//
// Author:   Kaihsu Tai, Michael Holst
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

    } else if (!strcmp(argv[0],"qread")) {
        theCmd = app_qread;
    } else if (!strcmp(argv[0],"quit")) {
        theCmd = app_quit;
    } else if (!strcmp(argv[0],"qinit")) {
        theCmd = app_qinit;
    } else if (!strcmp(argv[0],"qstep")) {
        theCmd = app_qstep;
    } else if (!strcmp(argv[0],"qwritedx")) {
      theCmd = app_qwritedx;
    } else if (!strcmp(argv[0],"qinfo")) {
        theCmd = app_qinfo;
    } else if (!strcmp(argv[0],"qhelp")) {
        theCmd = app_qhelp;

    /* Add your new command here */

    } else if (!strcmp(argv[0],"hello")) {
        theCmd = app_hello;
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
// Author:   Kaihsu Tai, Stephen Bond, Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPRIVATE int APVsh(void *pthee, int argc, char *argv[])
{
    MCsh *thee = (MCsh*)pthee;

    int rc;
    APPcommand theCmd;
    static int init=0;
    Vio *sock;

    /* timestepping parameters */
    double t0 = 0.0;
    SVio *vsock;

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
            Vnm_print(1,"    bye       --> Print 'Bye, World!' and exit.\n");

            Vnm_print(1,"\n    Commands for dynamics:\n");
            Vnm_print(1,"    qread     --> Read mesh from 'mcin.m'.\n");
            Vnm_print(1,"    quit      --> Leave.\n");
            Vnm_print(1,"    qinit     --> Initialise dynamics.\n");
            Vnm_print(1,"    qstep     --> Time-step ahead.\n");
            Vnm_print(1,"    qhelp,qinfo-> More extensive help ");
            Vnm_print(1,"(env. var., etc.).\n");

            /* Add your new command here */

            Vnm_print(1,"\n");
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

      case app_qread:
        Vnm_print(1, "%s(APVsh): reading the mesh from '%s'.\n",
		  Vsh_getenv(thee->vsh,"SHELL"),
		  Vsh_getenv(thee->vsh,"IFNAM"));
        sock = Vsh_ioSetup(thee->vsh,"r");
        (void)AM_read(thee->am,
            Vsh_getenvInt(thee->vsh,"TKEY"),
            sock);
        Vsh_ioCleanup(thee->vsh,&sock);
        Vsh_putenvInt(thee->vsh,"MARKED",0);
        Vnm_print(1, "%s(APVsh): mesh '%s' read.\n",
		  Vsh_getenv(thee->vsh,"SHELL"),
		  Vsh_getenv(thee->vsh,"IFNAM"));
        break;

      case app_quit:
        Vnm_print(1,"%s(APVsh): leaving.\n",
            Vsh_getenv(thee->vsh,"SHELL"));
        rc = 2;
        break;

      case app_qinit:
        Vnm_print(1,"%s(APVsh): initialising dynamics.\n",
            Vsh_getenv(thee->vsh,"SHELL"));
	AM_create(am);
        break;

      case app_qstep:
        Vnm_print(1,"%s(APVsh): Taking %d steps with a stepsize of %12.8e.\n",
            Vsh_getenv(thee->vsh,"SHELL"),
            Vsh_getenvInt(thee->vsh,"NSTEP"),
	    Vsh_getenvReal(thee->vsh,"TSTEP"));
	vsock = Vsh_SVioSetup(thee->vsh, "w");
	AM_tSolve(am,
		  Vsh_getenvInt(thee->vsh,"TMETH"),
		  Vsh_getenvReal(thee->vsh,"TSTEP"),
		  t0,
		  Vsh_getenvInt(thee->vsh,"NSTEP"),
		  Vsh_getenvInt(thee->vsh,"PFREQ"),
		  Vsh_getenvInt(thee->vsh,"EFREQ"),
                  Vsh_getenvInt(thee->vsh,"EKEYT"),
                  Vsh_getenvInt(thee->vsh,"PDETY"),
		  Vsh_getenvReal(thee->vsh,"LTOL"),
		  Vsh_getenvInt(thee->vsh,"LMAX"),
		  vsock);
	Vsh_SVioCleanup(thee->vsh, &vsock);
        break;  /* case app_qstep */

      case app_qinfo:
      case app_qhelp:
        Vnm_print(1,"%s(APVsh): build %s %s\n",
            Vsh_getenv(thee->vsh,"SHELL"), __DATE__, __TIME__);
        Vnm_print(1,
            "rcsid='$Id: main.c,v 1.3 2010/08/12 05:16:34 fetk Exp $'\n");
        Vnm_print(1, "Dynamics module for MC, ");
        Vnm_print(1, "Copyright © 2001 Kaihsu Tai, Stephen Bond.\n");
        Vnm_print(1, "MC, Copyright © 1994-- Michael Holst ");
        Vnm_print(1, "and co-authors.\n");
        Vnm_print(1, "  Environmental variables:\n");
        Vnm_print(1, "TSTEP defines the time-step.\n");
        Vnm_print(1, "TMETH defines the method for timestepping.\n");
        Vnm_print(1, "NSTEP defines the number of steps.\n");
        Vnm_print(1, "PFREQ defines output frequency.\n");
        Vnm_print(1, "PTYPE defines output type.\n");
        break;

      /* Add your new command here */

      case app_hello:
        Vnm_print(1,"%s(APVsh): Hello, World!\n",
            Vsh_getenv(thee->vsh,"SHELL"));
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
// Author:   Kaihsu Tai, Nathan Baker, and Michael Holst
/////////////////////////////////////////////////////////////////////////// */
int main(int argc, char **argv)
{
    MCsh *vmc = VNULL;
    pde     = myPDE_ctor();

    /* ********************************************************************* */
    /* NOTE: avoiding Vnm_print before MCsh_ctor() allows output file tagging*/
    /* ********************************************************************* */

    /* construct the MCsh object */
    vmc = MCsh_ctor(pde,argc,argv);

    /* construct the PDE object */
    am = vmc -> am;
    gm = vmc -> gm;

    /* start the MCsh command shell */
    MCsh_shell(vmc,APVsh);

    /* destroy the MCsh object */
    MCsh_dtor(&vmc);

    /* destroy the PDE object */
    myPDE_dtor(&pde);

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
