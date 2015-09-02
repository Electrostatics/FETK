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
 * rcsid="$Id: mcsh.c,v 1.45 2010/08/12 05:19:09 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     mcsh.c
 *
 * Purpose:  Class MCsh: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "mcsh_p.h"

VEMBED(rcsid="$Id: mcsh.c,v 1.45 2010/08/12 05:19:09 fetk Exp $")

/* builtin MCsh commands */
typedef enum MCsh_command {
    mccom_none,
    mccom_mark,
    mccom_lsolve,
    mccom_dsolve,
    mccom_nsolve,
    mccom_estimate,
    mccom_refine,
    mccom_deform,
    mccom_part,
    mccom_partsmooth,
    mccom_partset,
    mccom_evall2,
    mccom_evall8,
    mccom_evalh1,
    mccom_makebnd,
    mccom_makebndd,
    mccom_makebndn,
    mccom_makebndx,
    mccom_gen,
    mccom_reordersv,
    mccom_smooth,
    mccom_smoothb,
    mccom_smootho,
    mccom_tangent,
    mccom_formfix,
    mccom_evalj,
    mccom_eval,
    mccom_evalbint,
    mccom_buildcharts,
    mccom_clearcharts,
    mccom_read,
    mccom_write,
    mccom_writebrep,
    mccom_writeoff,
    mccom_writeoffdef,
    mccom_writeoffdis,
    mccom_writemath,
    mccom_writemathdef,
    mccom_writemathdis,
    mccom_writegmv,
    mccom_writeucd,
    mccom_writedx,
    mccom_writetec,
    mccom_printj,
    mccom_printa,
    mccom_printasp,
    mccom_printanod,
    mccom_printaspnod,
    mccom_printc,
    mccom_printcsp,
    mccom_printcnod,
    mccom_printcspnod,
    mccom_printp,
    mccom_printpsp,
    mccom_printv,
    mccom_printvsp,
    mccom_typechk,
    mccom_memchk,
    mccom_shapechk,
    mccom_formchk,
    mccom_formchkf,
    mccom_contentchk,
    mccom_speedchk,
    mccom_free,
    mccom_help
} MCsh_command;

/*
 * ***************************************************************************
 * Class MCsh: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_MCSH)

#endif /* if !defined(VINLINE_MCSH) */
/*
 * ***************************************************************************
 * Class MCsh: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  MCsh_ctor
 *
 * Purpose:  The MCsh constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC MCsh* MCsh_ctor(PDE *tpde, int argc, char **argv)
{
    MCsh *thee = VNULL;

    VDEBUGIO("MCsh_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(MCsh) );
    thee->vmem = Vmem_ctor( "MCsh" );

    VDEBUGIO("..done.\n");

    /* the environment and shell object */
    thee->PR[0] = '\0';
    thee->USER_shell = VNULL;
    thee->vsh = Vsh_ctor(VNULL, argc, argv);

    /* the differential equation object */
    thee->pde = tpde;

    /* the geometry manager object */
    thee->gm = Gem_ctor( VNULL, thee->pde );

    /* the approximation object */
    thee->aprx = Aprx_ctor( VNULL, thee->gm, thee->pde );

    /* the algebra manager object */
    thee->am = AM_ctor( VNULL, thee->aprx );

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  MCsh_dtor
 *
 * Purpose:  The MCsh destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void MCsh_dtor(MCsh **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        AM_dtor(   &((*thee)->am) );
        Aprx_dtor( &((*thee)->aprx) );
        Gem_dtor(  &((*thee)->gm) );
        Vsh_dtor(  &((*thee)->vsh) );

        VDEBUGIO("MCsh_dtor: DESTROYING object..");
        Vmem_dtor( &((*thee)->vmem) );
        Vmem_free( VNULL, 1, sizeof(MCsh), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Routine:  MCsh_publishVars
 *
 * Purpose:  Publish a set of environment variables with Vsh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void MCsh_publishVars(MCsh *thee)
{
    int i, numVars = 25;
    typedef struct mcVars {
        char envi[80];
        char valu[80];
        char info[80];
    } mcVars;
    mcVars envVars[] = {

        /* --------   -----       ----------- */
        /* VARIABLE   VALUE       EXPLANATION */
        /* --------   -----       ----------- */

        /* ===[ MESH=10]=== */
        { "ETOL",     "1.0e-2",
            "error estimator tolerance (error per simplex)" },
        { "EKEY",     "1",
            "error barrier (0=ETOL, 1=ETOL/#SS),2=refine fixed #/fraction SS" },
        { "AKEY",     "1",
            "estimator (-1=clear,0=all,1=user,2=nresid,3=dual,4=loc,5=rgrad)" },
        { "RKEY",     "0",
            "simplex refinement method (0=b-b, 1=q-b, 2=q-q)" },
        { "BKEY",     "0",
            "bisection type (0=longest edge, 1=newest vertex, 2=newest pair)" },
        { "RCOL",     "-1",
            "refine restriction (-1=none,k>=0=>restrict to subd k)" },
        { "PKEY",     "0",
            "partition method (0=inert,1=spect,2=gspect,3=i-then-s)" },
        { "PWHT",     "0",
            "partitioning weighting (0=none, 1=by error)" },
        { "PPOW",     "1",
            "partitioning steps (0=none,1=one,etc) [part=2^ppow]" },
        { "PROK",     "0",
            "prolongation operator (0=[I,P], 1=[P])" },

        /* ===[ SOLV=10 ]=== */
        { "LKEY",     "0",
            "linear solver (0=slu,1=mg,2=cg,3=bcg)" },
        { "NKEY",     "0",
            "nonlinear solver (0=newton,1=incremental,2=pseudo-arclength)" },
        { "PREC",     "0",
            "preconditioner (0=identity,1=diag-scale,2=mg)" },
        { "LTOL",     "1.0e-7",
            "linear solve tolerance (2-norm of rel resid)" },
        { "NTOL",     "1.0e-7",
            "nonlinear solve tolerance (2-norm of nonlinear resid)" },
        { "LMAX",     "100",
            "linear solve itmax (standalone or inside Newton)" },
        { "NMAX",     "100",
            "nonlinear solve itmax (e.g. Newton iteration max)" },
        { "GUES",     "2",
            "initial guess (0=0,1=ud,2=I_h[u])" },
        { "PJAC",     "-1",
            "print jacs (-1=no,-2=all,k>=0=>kth jac as jac_k.m)" },
        { "PVEC",     "-1",
            "which vec (...,-1=u+ud,0=f,1=u,2=ud,3=ui,4=ut,5=r,...)" },

        /* ===[ GRAPHICS=5 ]=== */
        { "TKEY",     "0",
            "mesh i/o format (0=simplex,1=edge,2=simplex-nabor)" },
        { "FKEY",     "0",
            "volume/face plot/write (0=volume,1=face,2=boundary simplices)" },
        { "CKEY",     "1",
            "color (0=none,1=simplex chart#,2=by bndry face type)" },
        { "DKEY",     "-1",
            "subd write (-1=entire mesh,0<=k chart# simps only)" },
        { "GVAL",     "1.0e-0",
            "glue value (separation of simplices in graphics)" },
    };

    for (i=0; i<numVars; i++) {
        Vsh_putenv(     thee->vsh, envVars[i].envi, envVars[i].valu );
        Vsh_putenvInfo( thee->vsh, envVars[i].envi, envVars[i].info );
    }
}

/*
 * ***************************************************************************
 * Routine:  MCsh_getCmd
 *
 * Purpose:  Get (decode) the command.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE MCsh_command MCsh_getCmd(MCsh *thee, int argc, char **argv)
{
    MCsh_command theCmd = mccom_none;
    if (!strcmp(argv[0],"")) {
        theCmd = mccom_none;
    } else if (!strcmp(argv[0],"help")) { 
        theCmd = mccom_help;
    } else if (!strcmp(argv[0],"mark")) {
        theCmd = mccom_mark;
    } else if (!strcmp(argv[0],"lsolve")) {
        theCmd = mccom_lsolve;
    } else if (!strcmp(argv[0],"dsolve")) {
        theCmd = mccom_dsolve;
    } else if (!strcmp(argv[0],"nsolve")) {
        theCmd = mccom_nsolve;
    } else if (!strcmp(argv[0],"estimate")) {
        theCmd = mccom_estimate;
    } else if (!strcmp(argv[0],"refine")) {
        theCmd = mccom_refine;
    } else if (!strcmp(argv[0],"deform")) {
        theCmd = mccom_deform;
    } else if (!strcmp(argv[0],"part")) {
        theCmd = mccom_part;
    } else if (!strcmp(argv[0],"partsmooth")) {
        theCmd = mccom_partsmooth;
    } else if (!strcmp(argv[0],"partset")) {
        theCmd = mccom_partset;
    } else if (!strcmp(argv[0],"evall2")) {
        theCmd = mccom_evall2;
    } else if (!strcmp(argv[0],"evall8")) {
        theCmd = mccom_evall8;
    } else if (!strcmp(argv[0],"evalh1")) {
        theCmd = mccom_evalh1;
    } else if (!strcmp(argv[0],"makebnd")) {
        theCmd = mccom_makebnd;
    } else if (!strcmp(argv[0],"makebndd")) {
        theCmd = mccom_makebndd;
    } else if (!strcmp(argv[0],"makebndn")) {
        theCmd = mccom_makebndn;
    } else if (!strcmp(argv[0],"makebndx")) {
        theCmd = mccom_makebndx;
    } else if (!strcmp(argv[0],"gen")) {
        theCmd = mccom_gen;
    } else if (!strcmp(argv[0],"reordersv")) {
        theCmd = mccom_reordersv;
    } else if (!strcmp(argv[0],"smooth")) {
        theCmd = mccom_smooth;
    } else if (!strcmp(argv[0],"smoothb")) {
        theCmd = mccom_smoothb;
    } else if (!strcmp(argv[0],"smootho")) {
        theCmd = mccom_smootho;
    } else if (!strcmp(argv[0],"tangent")) {
        theCmd = mccom_tangent;
    } else if (!strcmp(argv[0],"formfix")) {
        theCmd = mccom_formfix;
    } else if (!strcmp(argv[0],"evalj")) {
        theCmd = mccom_evalj;
    } else if (!strcmp(argv[0],"eval")) {
        theCmd = mccom_eval;
    } else if (!strcmp(argv[0],"evalbint")) {
        theCmd = mccom_evalbint;
    } else if (!strcmp(argv[0],"buildcharts")) {
        theCmd = mccom_buildcharts;
    } else if (!strcmp(argv[0],"clearcharts")) {
        theCmd = mccom_clearcharts;
    } else if (!strcmp(argv[0],"read")) {
        theCmd = mccom_read;
    } else if (!strcmp(argv[0],"write")) {
        theCmd = mccom_write;
    } else if (!strcmp(argv[0],"writebrep")) {
        theCmd = mccom_writebrep;
    } else if (!strcmp(argv[0],"writeoff")) {
        theCmd = mccom_writeoff;
    } else if (!strcmp(argv[0],"writeoffdef")) {
        theCmd = mccom_writeoffdef;
    } else if (!strcmp(argv[0],"writeoffdis")) {
        theCmd = mccom_writeoffdis;
    } else if (!strcmp(argv[0],"writemath")) {
        theCmd = mccom_writemath;
    } else if (!strcmp(argv[0],"writemathdef")) {
        theCmd = mccom_writemathdef;
    } else if (!strcmp(argv[0],"writemathdis")) {
        theCmd = mccom_writemathdis;
    } else if (!strcmp(argv[0],"writegmv")) {
        theCmd = mccom_writegmv;
    } else if (!strcmp(argv[0],"writeucd")) {
        theCmd = mccom_writeucd;
    } else if (!strcmp(argv[0],"writedx")) {
        theCmd = mccom_writedx;
    } else if (!strcmp(argv[0],"writetec")) {
        theCmd = mccom_writetec;
    } else if (!strcmp(argv[0],"printj")) {
        theCmd = mccom_printj;
    } else if (!strcmp(argv[0],"printa")) {
        theCmd = mccom_printa;
    } else if (!strcmp(argv[0],"printasp")) {
        theCmd = mccom_printasp;
    } else if (!strcmp(argv[0],"printanod")) {
        theCmd = mccom_printanod;
    } else if (!strcmp(argv[0],"printaspnod")) {
        theCmd = mccom_printaspnod;
    } else if (!strcmp(argv[0],"printc")) {
        theCmd = mccom_printc;
    } else if (!strcmp(argv[0],"printcsp")) {
        theCmd = mccom_printcsp;
    } else if (!strcmp(argv[0],"printcnod")) {
        theCmd = mccom_printcnod;
    } else if (!strcmp(argv[0],"printcspnod")) {
        theCmd = mccom_printcspnod;
    } else if (!strcmp(argv[0],"printp")) {
        theCmd = mccom_printp;
    } else if (!strcmp(argv[0],"printpsp")) {
        theCmd = mccom_printpsp;
    } else if (!strcmp(argv[0],"printv")) {
        theCmd = mccom_printv;
    } else if (!strcmp(argv[0],"printvsp")) {
        theCmd = mccom_printvsp;
    } else if (!strcmp(argv[0],"typechk")) {
        theCmd = mccom_typechk;
    } else if (!strcmp(argv[0],"memchk")) {
        theCmd = mccom_memchk;
    } else if (!strcmp(argv[0],"shapechk")) {
        theCmd = mccom_shapechk;
    } else if (!strcmp(argv[0],"formchk")) {
        theCmd = mccom_formchk;
    } else if (!strcmp(argv[0],"formchkf")) {
        theCmd = mccom_formchkf;
    } else if (!strcmp(argv[0],"contentchk")) {
        theCmd = mccom_contentchk;
    } else if (!strcmp(argv[0],"speedchk")) {
        theCmd = mccom_speedchk;
    } else if (!strcmp(argv[0],"free")) {
        theCmd = mccom_free;
    } else {
        theCmd = mccom_none;
    }
    return theCmd;
}

/*
 * ***************************************************************************
 * Routine:  MCsh_builtIn
 *
 * Purpose:  Deal with a builtin command.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int MCsh_builtIn(void *pthee, int argc, char **argv)
{
    MCsh *thee = (MCsh*)pthee;

    int i,rc,defKey,ncolor,marked;
    int block, numPts, marks[6];
    double *defX[3] = { VNULL, VNULL, VNULL };
    double pts[6*3], vals[6];
    MCsh_command theCmd;
    Vio *sock;

    static int  init=0;
    static char num[VMAX_BUFSIZE], mesh[VMAX_BUFSIZE], solv[VMAX_BUFSIZE];
    const char *stmp;

    /* one-time intialization */
    if (!init) {
        init=1;

        /* no simplices have been marked */
        Vsh_putenvInt(thee->vsh,"MARKED",0);

        /* make the num message (%s slots = 1) */
        stmp = "%s: General numerical commands: \n"
               "    speedchk --> run a speed check\n"
               "    free     --> free any extra mallocs\n";
        sprintf(num,stmp,thee->PR);

        /* make the mesh message (%s slots = 1) */
        /* (NOTE: Only 509 char-length constant strings supported in ISO C) */
        stmp = "%s: Mesh manipulation commands: \n"
               "    mark        --> mark a mesh\n"
               "    estimate    --> a posteriori error estim\n"
               "    refine      --> refine the mesh\n"
               "    deform      --> deform the mesh using existing solution\n"
               "    makebnd     --> clear all bndry faces in mesh\n";
        sprintf(mesh,stmp,thee->PR);
        stmp = "    makebndd    --> rebuild dirichlet bndry faces in mesh\n"
               "    makebndn    --> rebuild neumann bndry faces in mesh\n"
               "    makebndx    --> rebuild special bndry faces in mesh\n"
               "    gen         --> generate delaunay mesh\n"
               "    reordersv   --> reorder the vertices in every simplex\n";
        strcat(mesh,stmp);
        stmp = "    smooth      --> interior mesh smoothing\n"
               "    smoothb     --> boundary mesh smoothing\n"
               "    smootho     --> optimization mesh smoothing\n"
               "    tangent     --> build tangent plane at each vertex\n"
               "    formfix     --> make a specific fix to a mesh\n";
        strcat(mesh,stmp);
        stmp = "    buildcharts --> build the manifold charts\n"
               "    clearcharts --> clear the manifold charts\n"
               "    typechk     --> run a datatype size check\n"
               "    memchk      --> run a memory check\n"
               "    shapechk    --> run element shape check\n"
               "    formchk     --> run ringed-vertex datastructure check\n";
        strcat(mesh,stmp);
        stmp = "    formchkf    --> run formcheck and also conformity check\n"
               "    contentchk  --> run geometry content check\n"
               "    part        --> mesh partition (recursive bisection)\n"
               "    partsmooth  --> smooth the partition\n"
               "    partset     --> reset the partition\n";
        strcat(mesh,stmp);
        stmp = "    read        --> read mesh in MC-Simplex-Format (MCSF)\n"
               "    write       --> write mesh in MC-Simplex-Format (MCSF)\n"
               "    writebrep   --> write bdry mesh in GeomPak BREP-Format\n"
               "    writeoff    --> write mesh in Geomview OFF-Format\n"
               "    writemath   --> write mesh in Mathematica MATH-Format\n";
        strcat(mesh,stmp);

        /* make the solv message (%s slots = 1) */
        stmp = "%s: Solver related commands: \n"
               "    lsolve      --> solve linear problem\n"
               "    dsolve      --> solve linear dual problem\n"
               "    nsolve      --> solve nonlinear problem\n"
               "    evalj       --> energy functional of global FE solution\n"
               "    eval        --> evaluate FE function at a point\n";
        sprintf(solv,stmp,thee->PR);
        stmp = "    evalbint    --> evaluate FE function boundary integral\n"
               "    evall2      --> L2-norm of error in subdomain <rcol>\n"
               "    evall8      --> L8-norm of error in subdomain <rcol>\n"
               "    evalh1      --> H1-norm of error in subdomain <rcol>\n"
               "    printa      --> print fine jac matrix\n";
        strcat(solv,stmp);
        stmp = "    printasp    --> print fine jac matrix (sparse .m)\n"
               "    printc      --> print coarse jac matrix\n"
               "    printcsp    --> print coarse jac matrix (sparse .m)\n"
               "    printp      --> print prolongation matrix\n"
               "    printpsp    --> print prolongation matrix (sparse .m)\n";
        strcat(solv,stmp);
        stmp = "    printv      --> print a vector\n"
               "    printvsp    --> print a vector (sparse .m)\n"
               "    printanod   --> printa with dirichlet equations zeroed\n"
               "    printaspnod --> printasp with dirichlet equations zeroed\n"
               "    printcnod   --> printc with dirichlet equations zeroed\n";
        strcat(solv,stmp);
        stmp = "    printcspnod --> printcsp with dirichlet equations zeroed\n"
               "    writeoffdef --> write deformation in OFF-Format\n"
               "    writeoffdis --> write displacement in OFF-Format\n"
               "    writemathdef--> write deformation in MATH-Format\n"
               "    writemathdis--> write displacement in MATH-Format\n"
               "    writegmv    --> write solution in GMV-Format\n"
               "    writeucd    --> write solution in UCD-Format\n"
               "    writedx     --> write solution in DX-Format\n"
               "    writetec    --> write solution in TECPLOT-Format\n";
        strcat(solv,stmp);
    }

    /* the user-defined shell gets first shot at the command */
    if (thee->USER_shell != VNULL) {
        rc = (*(thee->USER_shell))(thee,argc,argv);
        if (rc != 0) return rc;
    }

    /* default return code (success) */
    rc = 1;

    /* get the command */
    theCmd = MCsh_getCmd(thee, argc, argv);

    /* decode and execute the command */
    switch (theCmd) {

      case mccom_mark:
        marked = Gem_markRefine(thee->gm,
            Vsh_getenvInt(thee->vsh,"AKEY"),
            Vsh_getenvInt(thee->vsh,"RCOL"));
        Vsh_putenvInt(thee->vsh,"MARKED",marked);
        break;

      case mccom_lsolve:
        AM_lSolve(thee->am,
            0,
            Vsh_getenvInt(thee->vsh,"LKEY"),
            Vsh_getenvInt(thee->vsh,"LMAX"),
            Vsh_getenvReal(thee->vsh,"LTOL"),
            Vsh_getenvInt(thee->vsh,"PREC"),
            Vsh_getenvInt(thee->vsh,"GUES"),
            Vsh_getenvInt(thee->vsh,"PJAC"));
        break;

      case mccom_dsolve:
        AM_lSolve(thee->am,
            1,
            Vsh_getenvInt(thee->vsh,"LKEY"),
            Vsh_getenvInt(thee->vsh,"LMAX"),
            Vsh_getenvReal(thee->vsh,"LTOL"),
            Vsh_getenvInt(thee->vsh,"PREC"),
            Vsh_getenvInt(thee->vsh,"GUES"),
            Vsh_getenvInt(thee->vsh,"PJAC"));
        break;

      case mccom_nsolve:
        AM_nSolve(thee->am,
            Vsh_getenvInt(thee->vsh,"NKEY"),
            Vsh_getenvInt(thee->vsh,"NMAX"),
            Vsh_getenvReal(thee->vsh,"NTOL"),
            Vsh_getenvInt(thee->vsh,"LKEY"),
            Vsh_getenvInt(thee->vsh,"LMAX"),
            Vsh_getenvReal(thee->vsh,"LTOL"),
            Vsh_getenvInt(thee->vsh,"PREC"),
            Vsh_getenvInt(thee->vsh,"GUES"),
            Vsh_getenvInt(thee->vsh,"PJAC"));
        break;

      case mccom_estimate:
        marked = AM_markRefine(thee->am,
            Vsh_getenvInt(thee->vsh,"AKEY"),
            Vsh_getenvInt(thee->vsh,"RCOL"),
            Vsh_getenvInt(thee->vsh,"EKEY"),
            Vsh_getenvReal(thee->vsh,"ETOL"));
        Vsh_putenvInt(thee->vsh,"MARKED",marked);
        break;

      case mccom_refine:
        marked = Vsh_getenvInt(thee->vsh,"MARKED");
        if (marked) {
            (void)AM_refine(thee->am,
                Vsh_getenvInt(thee->vsh,"RKEY"),
                Vsh_getenvInt(thee->vsh,"BKEY"),
                Vsh_getenvInt(thee->vsh,"PROK"));
            Vsh_putenvInt(thee->vsh,"MARKED",0);
        }
        break;

      case mccom_deform:
        (void)AM_deform(thee->am);
        break;

      case mccom_part:
        (void)AM_part(thee->am,
            Vsh_getenvInt(thee->vsh,"PKEY"),
            Vsh_getenvInt(thee->vsh,"PWHT"),
            Vsh_getenvInt(thee->vsh,"PPOW"));
        break;

      case mccom_partsmooth:
        ncolor = AM_partSmooth(thee->am);
        break;

      case mccom_partset:
        ncolor = 0;
        ncolor = AM_partSet(thee->am,ncolor);
        break;

      case mccom_evall2:
        (void)AM_evalError(thee->am,
            Vsh_getenvInt(thee->vsh,"RCOL"),
            0);
        break;

      case mccom_evall8:
        (void)AM_evalError(thee->am,
            Vsh_getenvInt(thee->vsh,"RCOL"),
            1);
        break;

      case mccom_evalh1:
        (void)AM_evalError(thee->am,
            Vsh_getenvInt(thee->vsh,"RCOL"),
            2);
        break;

      case mccom_makebnd:
        Gem_makeBnd(thee->gm,0);
        break;

      case mccom_makebndd:
        Gem_makeBnd(thee->gm,1);
        break;

      case mccom_makebndn:
        Gem_makeBnd(thee->gm,2);
        break;

      case mccom_makebndx:
        Gem_makeBndExt(thee->gm,0);
        break;

      case mccom_gen:
        Gem_delaunay(thee->gm);
        break;

      case mccom_reordersv:
        Gem_reorderSV(thee->gm);
        break;

      case mccom_smooth:
        Gem_smoothMesh(thee->gm);
        break;

      case mccom_smoothb:
        Gem_smoothMeshBnd(thee->gm);
        break;

      case mccom_smootho:
        Gem_smoothMeshOpt(thee->gm);
        break;

      case mccom_formfix:
        Gem_formFix(thee->gm,0);
        break;

      case mccom_evalj:
        (void)AM_evalJ(thee->am);
        break;

      case mccom_eval:
#if 0
        pts[0]  =  1.; pts[1]  =  0.; pts[2]  =  0.; 
        pts[3]  =  0.; pts[4]  =  1.; pts[5]  =  0.; 
        pts[6]  =  0.; pts[7]  =  0.; pts[8]  =  1.; 
        pts[9]  = -1.; pts[10] =  0.; pts[11] =  0.; 
        pts[12] =  0.; pts[13] = -1.; pts[14] =  0.; 
        pts[15] =  0.; pts[16] =  0.; pts[17] = -1.; 
#else
        pts[0]  =  0.0; pts[1]  =  0.0; pts[2]  =  2.1; 
        pts[3]  =  0.0; pts[4]  =  2.1; pts[5]  =  0.0; 
        pts[6]  =  2.1; pts[7]  =  0.0; pts[8]  =  0.0; 
        pts[9]  =  0.0; pts[10] =  0.0; pts[11] = -2.1; 
        pts[12] =  0.0; pts[13] = -2.1; pts[14] =  0.0; 
        pts[15] = -2.1; pts[16] =  0.0; pts[17] =  0.0; 
#endif
        block  = 0;
        numPts = 6;
        AM_evalFunc(thee->am,
            Vsh_getenvInt(thee->vsh,"PVEC"),
            block, numPts, pts, vals, marks);
        for (i=0; i<numPts; i++) {
            Vnm_print(0,"MCsh_builtIn: W_{%d}(%g,%g,%g)=<%g>\n",
                Vsh_getenvInt(thee->vsh,"PVEC"),
                pts[i*3+0],pts[i*3+1],pts[i*3+2],vals[i]);
        }
        break;

      case mccom_evalbint:
        AM_bndIntegral(thee->am);
        break;

      case mccom_buildcharts:
        Gem_buildCharts(thee->gm);
        break;

      case mccom_clearcharts:
        Gem_clearCharts(thee->gm);
        break;

      case mccom_read:
        sock = Vsh_ioSetup(thee->vsh,"r");
        (void)AM_read(thee->am,
            Vsh_getenvInt(thee->vsh,"TKEY"),
            sock);
        Vsh_ioCleanup(thee->vsh,&sock);
        Vsh_putenvInt(thee->vsh,"MARKED",0);
        break;

      case mccom_write:
        sock = Vsh_ioSetup(thee->vsh,"w");
        Gem_write(thee->gm,
            Vsh_getenvInt(thee->vsh,"TKEY"),
            sock,
            Vsh_getenvInt(thee->vsh,"FKEY"));
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writebrep:
        sock = Vsh_ioSetup(thee->vsh,"w");
        Gem_writeBrep(thee->gm,sock);
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writeoff:
        defKey = 0;
        sock = Vsh_ioSetup(thee->vsh,"w");
        Gem_writeGEOM(thee->gm,
            sock,
            defKey,
            Vsh_getenvInt(thee->vsh,"CKEY"),
            Vsh_getenvInt(thee->vsh,"DKEY"),
            Vsh_getenvReal(thee->vsh,"GVAL"),
            Vsh_getenvInt(thee->vsh,"FKEY"),
            defX,
            "GV");
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writeoffdef:
        defKey = 1;
        sock = Vsh_ioSetup(thee->vsh,"w");
        AM_writeGEOM(thee->am,
            sock,
            defKey,
            Vsh_getenvInt(thee->vsh,"CKEY"),
            Vsh_getenvInt(thee->vsh,"DKEY"),
            Vsh_getenvReal(thee->vsh,"GVAL"),
            Vsh_getenvInt(thee->vsh,"FKEY"),
            Vsh_getenvInt(thee->vsh,"PVEC"),
            "GV");
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writeoffdis:
        defKey = 2;
        sock = Vsh_ioSetup(thee->vsh,"w");
        AM_writeGEOM(thee->am, 
            sock,
            defKey,
            Vsh_getenvInt(thee->vsh,"CKEY"),
            Vsh_getenvInt(thee->vsh,"DKEY"),
            Vsh_getenvReal(thee->vsh,"GVAL"),
            Vsh_getenvInt(thee->vsh,"FKEY"),
            Vsh_getenvInt(thee->vsh,"PVEC"),
            "GV");
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writemath:
        defKey = 0;
        sock = Vsh_ioSetup(thee->vsh,"w");
        Gem_writeGEOM(thee->gm,
            sock,
            defKey,
            Vsh_getenvInt(thee->vsh,"CKEY"),
            Vsh_getenvInt(thee->vsh,"DKEY"),
            Vsh_getenvReal(thee->vsh,"GVAL"),
            Vsh_getenvInt(thee->vsh,"FKEY"),
            defX,
            "MATH");
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writemathdef:
        defKey = 1;
        sock = Vsh_ioSetup(thee->vsh,"w");
        AM_writeGEOM(thee->am,
            sock,
            defKey,
            Vsh_getenvInt(thee->vsh,"CKEY"),
            Vsh_getenvInt(thee->vsh,"DKEY"),
            Vsh_getenvReal(thee->vsh,"GVAL"),
            Vsh_getenvInt(thee->vsh,"FKEY"),
            Vsh_getenvInt(thee->vsh,"PVEC"),
            "MATH");
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writemathdis:
        defKey = 2;
        sock = Vsh_ioSetup(thee->vsh,"w");
        AM_writeGEOM(thee->am, 
            sock,
            defKey,
            Vsh_getenvInt(thee->vsh,"CKEY"),
            Vsh_getenvInt(thee->vsh,"DKEY"),
            Vsh_getenvReal(thee->vsh,"GVAL"),
            Vsh_getenvInt(thee->vsh,"FKEY"),
            Vsh_getenvInt(thee->vsh,"PVEC"),
            "MATH");
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writegmv:
        sock = Vsh_ioSetup(thee->vsh,"w");
        AM_writeSOL(thee->am,
            sock,
            Vsh_getenvInt(thee->vsh,"PVEC"),
            "GMV");
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writeucd:
        sock = Vsh_ioSetup(thee->vsh,"w");
        AM_writeSOL(thee->am,
            sock,
            Vsh_getenvInt(thee->vsh,"PVEC"),
            "UCD");
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writedx:
        sock = Vsh_ioSetup(thee->vsh,"w");
        AM_writeSOL(thee->am,
            sock,
            Vsh_getenvInt(thee->vsh,"PVEC"),
            "DX");
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_writetec:
        sock = Vsh_ioSetup(thee->vsh,"w");
        AM_writeSOL(thee->am,
            sock,
            Vsh_getenvInt(thee->vsh,"PVEC"),
            "TEC");
        Vsh_ioCleanup(thee->vsh,&sock);
        break;

      case mccom_printj:
        AM_printJ(thee->am);
        break;

      case mccom_printa:
        AM_printA(thee->am);
        break;

      case mccom_printasp:
        AM_printAsp(thee->am, "jac.m");
        break;

      case mccom_printanod:
        AM_printAnoD(thee->am);
        break;

      case mccom_printaspnod:
        AM_printAspNoD(thee->am, "jac.m");
        break;

      case mccom_printc:
        AM_printA(thee->am);
        break;

      case mccom_printcsp:
        AM_printAsp(thee->am, "jacc.m");
        break;

      case mccom_printcnod:
        AM_printAnoD(thee->am);
        break;

      case mccom_printcspnod:
        AM_printAspNoD(thee->am, "jacc.m");
        break;

      case mccom_printp:
        AM_printP(thee->am);
        break;

      case mccom_printpsp:
        AM_printPsp(thee->am, "pro.m");
        break;

      case mccom_printv:
        AM_printV(thee->am,
            Vsh_getenvInt(thee->vsh,"PVEC"));
        break;

      case mccom_printvsp:
        AM_printVsp(thee->am,
            Vsh_getenvInt(thee->vsh,"PVEC"),
            "sol.m");
        break;

      case mccom_typechk:
        Vnm_typeChk();
        break;

      case mccom_memchk:
        MCsh_memChk(thee);
        break;

      case mccom_formchk:
        /* check ringed vertex: 0=[v+s],1=[.+sRing],2=[.+eRing],3=[.+conform] */
        Gem_formChk(thee->gm,2);
        break;

      case mccom_formchkf:
        /* check ringed vertex: 0=[v+s],1=[.+sRing],2=[.+eRing],3=[.+conform] */
        Gem_formChk(thee->gm,3);
        break;

      case mccom_shapechk:
        Gem_shapeChk(thee->gm);
        break;

      case mccom_contentchk:
        Gem_contentChk(thee->gm);
        break;

      case mccom_speedchk:
        Gem_speedChk(thee->gm);
        break;

      case mccom_free:
        Gem_ramClear(thee->gm,2);
        Gem_ramClear(thee->gm,1);
        Gem_ramClear(thee->gm,0);
        break;

      case mccom_help:
        if (argc==1) {
            Vnm_print(1,"MCsh: MCsh-layer Help Menu:\n");
            Vnm_print(1,
                "    help num  --> Help on %s general numerical commands\n",
                thee->PR);
            Vnm_print(1,
                "    help mesh --> Help on %s mesh manipulation commands\n",
                thee->PR);
            Vnm_print(1,
                "    help solv --> Help on %s solver control commands\n",
                thee->PR);
            rc = 0;  /* pretend we didn't see it so subshell can help too */
        } else {
            if (!strcmp(argv[1],"num")) { 
                Vnm_print(1, "%s", num);
            } else if (!strcmp(argv[1],"mesh")) { 
                Vnm_print(1, "%s", mesh);
            } else if (!strcmp(argv[1],"solv")) { 
                Vnm_print(1, "%s", solv);
            } else {
                rc = 0;  /* pretend we didn't it so subshell can help too */
            }
        }
        break;                                                              

      default:
        rc = 0;
        break;
    }
    return rc;
}

/*
 * ***************************************************************************
 * Routine:  MCsh_shell
 *
 * Purpose:  The actual shell.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int MCsh_shell(MCsh *thee, 
    int (*USER_shell)(void *thee, int argc, char **argv))
{
    thee->USER_shell = USER_shell;
    strcpy(thee->PR,"MCsh");
    MCsh_publishVars(thee);
    return Vsh_shell(thee->vsh, thee->PR, (void*)thee, &MCsh_builtIn);
}

/*
 * ***************************************************************************
 * Routine:  MCsh_pshell
 *
 * Purpose:  The actual shell (version with parallel extensions).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int MCsh_pshell(MCsh *thee, 
    int (*USER_shell)(void *thee, int argc, char **argv))
{
    thee->USER_shell = USER_shell;
    strcpy(thee->PR,"MCsh");
    MCsh_publishVars(thee);
    return Vsh_pshell(thee->vsh, thee->PR, (void*)thee, &MCsh_builtIn);
}

/*
 * ***************************************************************************
 * Routine:  MCsh_memChk
 *
 * Purpose:  Print the exact current malloc usage.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void MCsh_memChk(MCsh *thee)
{
    Vnm_print(0,"mc_vertex  = %d;\n", Gem_numVV(thee->gm));
    Vnm_print(0,"mc_simplex = %d;\n", Gem_numSS(thee->gm));
    Vnm_print(0,"mc_memory  = [\n");
    Vnm_print(0,"%% --------------------------------------"
                "--------------------------------------\n");
    Vnm_print(0,"%%  Footprint        Areas       Malloc         Free"
                "    Highwater   Class\n"),
    Vnm_print(0,"%% --------------------------------------"
                "--------------------------------------\n");
    if (thee->gm != VNULL) Gem_memChk(thee->gm);
    if (thee->am != VNULL) AM_memChk(thee->am);
    Vmem_print(VNULL);
    Vnm_print(0,"%% --------------------------------------"
                "--------------------------------------\n");
    Vmem_printTotal();
    Vnm_print(0,"%% --------------------------------------"
                "--------------------------------------\n");
    Vnm_print(0,"];\n");
    if (thee->gm != VNULL) Gem_memChkMore(thee->gm);
}

