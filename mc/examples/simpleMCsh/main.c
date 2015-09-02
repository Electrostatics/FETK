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
 * rcsid="$Id: main.c,v 1.7 2010/08/12 05:17:40 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     main.c
 *
 * Purpose:  Main driver for the Manifold Code (MC)
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "mypde.h"

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
VEMBED(rcsid="$Id: main.c,v 1.7 2010/08/12 05:17:40 fetk Exp $")

/* Some help to organize the application-specific shell commands */
typedef enum APPcommand {
    app_none,
    app_help,
    app_stat,
    app_hello,
    app_bye,
    app_chkmesh
} APPcommand;

/*
 * ***************************************************************************
 * Routine:  APPgetCmd
 *
 * Purpose: The application-specific shell parser
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
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
    } else if (!strcmp(argv[0],"bye")) {
        theCmd = app_bye;
    } else if (!strcmp(argv[0],"chkmesh")) {
        theCmd = app_chkmesh;
    } else {
        theCmd = app_none;
    }
    return theCmd;
}

/*
 * ***************************************************************************
 * Routine:  APVsh
 *
 * Purpose: The application-specific shell for enriching the Vsh_shell
 *          or for overriding the builtin Vsh_shell commands.
 *
 * Return codes (required):
 *
 *     rc=0   --> APVsh does not know about this command
 *     rc=1   --> APVsh handled this command sucessfully
 *     rc=2   --> APVsh handled this command sucessfully and wants to exit!
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int APVsh(void *pthee, int argc, char *argv[])
{
    MCsh *thee = (MCsh*)pthee;

    int rc;
    APPcommand theCmd;
    static int init=0;

    Vio *sock;
    Gem *gm;
    SS *sm;
    int i, irefineSize, done, *irefine, itmp, iold, marked, currentQ, count;
    char *rwFlag;
    char *ISKEY, *ISFMT, *IHVAL, *IFNAM;

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
            Vnm_print(1,"    chkmesh   --> Do a mesh check.\n");
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

      case app_bye:
        Vnm_print(1,"%s(APVsh): Bye, World!\n",
            Vsh_getenv(thee->vsh,"SHELL"));
        rc = 2;
        break;

      case app_chkmesh:
        rwFlag = "r";         /* read(r) or write(w) */
        ISKEY  = "FILE";      /* INPUT DEV type (sdio,file,buff,unix,inet) */
        ISFMT  = "ASC";       /* INPUT DEV format (asc,xdr) */
        IFNAM  = "Marked.dat";/* INPUT DEV file (filename for file I/O) */
        IHVAL  = "localhost"; /* INPUT DEV host (INET hostname or IP addr) */
        VASSERT(VNULL!=(sock=Vio_socketOpen(rwFlag,ISKEY,ISFMT,IHVAL,IFNAM)));
        irefineSize=0;
        done=0;
        irefine = Vmem_malloc( VNULL, 100000, sizeof(int) );
        iold = -1;
        while (!done) {
            if ( !Vio_scanf(sock,"%d",&itmp) ) {
                done = 1;
            } else {
                VASSERT( itmp > iold );
                VASSERT( itmp >= 0 );
                VASSERT( itmp < 59062 );
                iold = itmp;
                irefine[irefineSize] = itmp;
  /* fprintf(stderr,"x[%d]=<%d>\n",irefineSize,irefine[irefineSize]); */
                irefineSize++;
            }
        }
        Vio_socketClose(&sock);
        gm = thee->gm;

        count = 1;
        marked = 0;
        currentQ = 0;
        if (Gem_numSQ(gm,currentQ) > 0) {
            Vnm_print(0,"app_chkmesh: non-empty refine Q%d....clearing..",
                currentQ);
            Gem_resetSQ(gm,currentQ);
            Vnm_print(0,"..done.\n");
        }
        if (Gem_numSQ(gm,!currentQ) > 0) {
            Vnm_print(0,"app_chkmesh: non-empty refine Q%d....clearing..",
                !currentQ);
            Gem_resetSQ(gm,!currentQ);
            Vnm_print(0,"..done.\n");
        }
        VASSERT( Gem_numSQ(gm,currentQ)  == 0 );
        VASSERT( Gem_numSQ(gm,!currentQ) == 0 );

        Vnm_print(0,"app_chkmesh: clearing all simplex refinement flags..");
        for (i=0; i<Gem_numSS(gm); i++) {
            if ( (i>0) && (i % VPRTKEY) == 0 ) Vnm_print(0,"[MS:%d]",i);
            sm = Gem_SS(gm,i);
            SS_setRefineKey(sm,currentQ,0);
            SS_setRefineKey(sm,!currentQ,0);
            SS_setRefinementCount(sm,0); /* refine X many times? */
        }
        Vnm_print(0,"..done.\n");

        Vnm_print(0,"app_chkmesh: marking marked simplices..");
        for (i=0; i<irefineSize; i++) {
            sm = Gem_SS(gm,irefine[i]);
            Gem_appendSQ(gm,currentQ, sm); /* add to refinement Q */
            SS_setRefineKey(sm,currentQ,1);  /* note is now on refine Q */
            SS_setRefinementCount(sm,count); /* refine X many times? */
            marked++;
        }
        Vnm_print(0,"..done.  [marked=<%d>]\n", marked);
        Vsh_putenvInt(thee->vsh,"MARKED",marked);
        break;

      default:
        rc = 0;
        break;
    }
    return rc;
}

/*
 * ***************************************************************************
 * Routine:  main
 *
 * Purpose: The main driver for initiating the Vsh_shell.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
int main(int argc, char **argv)
{
    PDE *myPde = VNULL;
    MCsh *mc = VNULL;

    /* ********************************************************************* */
    /* NOTE: avoiding Vnm_print before MCsh_ctor() allows output file tagging */
    /* ********************************************************************* */

    /* first executable statement should realy be <MPI_Init> */
    VASSERT( Vmp_init(&argc,&argv) );

    /* construct the PDE object */
    myPde = myPDE_ctor();

    /* construct the MCsh object */
    mc = MCsh_ctor(myPde,argc,argv);

    /* start the MCsh command shell */
    MCsh_pshell(mc,APVsh);

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

    /* last executable statement should really be <MPI_Finalize> */
    VASSERT( Vmp_finalize() );

    /* normal return */
    return 0;
}

