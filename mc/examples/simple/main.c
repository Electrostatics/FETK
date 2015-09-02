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
 * rcsid="$Id: main.c,v 1.7 2010/08/12 05:17:36 fetk Exp $"
 * ***************************************************************************
 */

#include "mypde.h"

int main(int argc, char **argv)
{
    PDE  *myPde  = VNULL;
    Gem  *myGem  = VNULL;
    Aprx *myAprx = VNULL;
    AM   *myAm   = VNULL;
    Vio  *sock   = VNULL;
    double *defX[3] = { VNULL, VNULL, VNULL };
    double GVAL, LTOL;
    int dualKey, done, marked, mcsf_format, defKey, CKEY, DKEY, FKEY;
    int LKEY, LMAX, PREC, GUES, PJAC, PVEC;
    int AKEY, RCOL, EKEY, RKEY, BKEY, PROK;
    int adaptIter, adaptMax;
    double ETOL;
    char *rwFlag, *solFmt;
    char *ISKEY, *ISFMT, *IFNAM, *ISNAM, *IHVAL;
    char *OSKEY, *OSFMT, *OFNAM, *OSNAM, *OHVAL;

    /* initialize the socket stuff */
    Vio_start();

    /* construct the PDE object */
    myPde = myPDE_ctor();

    /* construct the MCsh object */
    /* mc = MCsh_ctor(myPde,argc,argv); */

    /* the geometry manager object */
    myGem = Gem_ctor( VNULL, myPde );

    /* the approximation object */
    myAprx = Aprx_ctor( VNULL, myGem, myPde );

    /* the algebra manager object */
    myAm = AM_ctor( VNULL, myAprx );

    /* read mesh */
    rwFlag = "r";         /* read(r) or write(w) */
    ISKEY  = "FILE";      /* VIO INPUT DEV type (sdio,file,buff,unix,inet) */
    ISFMT  = "ASC";       /* VIO INPUT DEV format (asc,xdr) */
    IFNAM  = "mcin.m";    /* VIO INPUT DEV file (filename for file I/O) */
    IHVAL  = "localhost"; /* VIO INPUT DEV host (INET hostname or IP addr) */
    VASSERT( VNULL != (sock=Vio_socketOpen(rwFlag,ISKEY,ISFMT,IHVAL,IFNAM)) );
    mcsf_format = 0; /* 0=simplex, 1=edge, 2=simplex-nabor */
    (void)AM_read(myAm, mcsf_format, sock);
    Vio_socketClose( &sock );

    /* plot mesh */
    rwFlag = "w";
    OSKEY  = "INET"; /* VIO OUTPUT DEV type (sdio,file,buff,unix,inet) */
    OSFMT  = "ASC";  /* VIO OUTPUT DEV format (asc,xdr) */
    OSNAM  = "0";    /* VIO OUTPUT DEV name ([ buff | unix | inet ] num) */
    OHVAL  = "localhost"; /* VIO OUTPUT DEV host (INET hostname or IP) */
    VASSERT(VNULL!=(sock=Vio_socketOpen(rwFlag,OSKEY,OSFMT,OHVAL,OSNAM)));
    defKey = 0;   /* 0=plot mesh, 1=plot defX as deformation of mesh */
    CKEY   = 1;   /* color (0=none,1=simplex chart#,2=by bd face type) */
    DKEY   = -1;  /* subd write (-1=entire mesh,0<=k chart# simps only) */
    GVAL   = 1.0; /* glue value (separation of simplices in graphics) */
    FKEY   = 0;   /* volume/face plot/write (0=volume,1=face) [3D only] */
    Gem_writeGEOM(myGem, sock, defKey, CKEY, DKEY, GVAL, FKEY, defX, "GV");
    Vio_socketClose( &sock );

    /* loop: disc-solve/plot-soln/estimate-refine/plot-mesh */
    adaptMax = 15;
    done = 0;
    adaptIter = 0;
    while (!done) {

        /* disc-solve */
        dualKey = 0;      /* 0=PDE, 1=adjoint of PDE */
        LKEY    = 2;      /* linear solver (0=slu,1=mg,2=cg,3=bcg) */
        LMAX    = 100;    /* linear solve itmax (standalone or inside Newton) */
        LTOL    = 1.0e-7; /* linear solve tolerance (2-norm of rel resid) */
        PREC    = 0;      /* preconditioner (0=identity,1=diag-scale,2=mg) */
        GUES    = 2;      /* initial guess (0=0,1=ud,2=I_h[u]) */
        PJAC    = -1;     /* print jacs (-1=no,-2=all,k>=0=>kth jac jac_k.m) */
        AM_lSolve(myAm, dualKey, LKEY, LMAX, LTOL, PREC, GUES, PJAC);

        /* plot soln (sg format) */
        rwFlag = "w";
        OSKEY  = "INET"; /* VIO OUTPUT DEV type (sdio,file,buff,unix,inet) */
        OSFMT  = "ASC";  /* VIO OUTPUT DEV format (asc,xdr) */
        OSNAM  = "1";    /* VIO OUTPUT DEV name ([ buff | unix | inet ] num) */
        OHVAL  = "localhost"; /* VIO OUTPUT DEV host (INET hostname or IP) */
        VASSERT(VNULL!=(sock=Vio_socketOpen(rwFlag,OSKEY,OSFMT,OHVAL,OSNAM)));
        defKey = 1;   /* 0=plot mesh, 1=plot defX as deformation of mesh */
        CKEY   = 1;   /* color (0=none,1=simplex chart#,2=by bndry face type) */
        DKEY   = -1;  /* subd write (-1=entire mesh,0<=k chart# simps only) */
        GVAL   = 1.0; /* glue value (separation of simplices in graphics) */
        FKEY   = 0;   /* volume/face plot/write (0=volume,1=face)  [3D only] */
        PVEC   = -1;  /* which vec (-1=u+ud,0=f,1=u,2=ud,3=ui,4=ut,5=r,...) */
        AM_writeGEOM(myAm, sock, defKey, CKEY, DKEY, GVAL, FKEY, PVEC, "GV");
        Vio_socketClose( &sock );

        /* plot soln (dx/etc format) */
        rwFlag = "w";
        OSKEY  = "FILE"; /* VIO OUTPUT DEV type (sdio,file,buff,unix,inet) */
        OSFMT  = "ASC";  /* VIO OUTPUT DEV format (asc,xdr) */
        OFNAM  = "mcout.dx";  /* VIO OUTPUT DEV file (filename for file I/O) */
        OHVAL  = "localhost"; /* VIO OUTPUT DEV host (INET hostname or IP) */
        VASSERT(VNULL!=(sock=Vio_socketOpen(rwFlag,OSKEY,OSFMT,OHVAL,OFNAM)));
        PVEC   = -1;   /* which vec (-1=u+ud,0=f,1=u,2=ud,3=ui,4=ut,5=r,...) */
        solFmt = "DX"; /* DX, UCD, TEC, GMV */
        AM_writeSOL(myAm, sock, PVEC, solFmt);
        Vio_socketClose( &sock );

        /* estimate-refine */
        AKEY =  2;     /* estimator (-1=clear,0=all,1=user,2=nresid,...) */
        RCOL = -1;     /* refine restrict (-1=none,k>=0=>restrict to subd k)*/
        EKEY =  1;     /* error barrier choice (0=ETOL, 1=ETOL/#simplices) */
        ETOL = 5.0e-2; /* error estimator tolerance (error per simplex) */
        marked = AM_markRefine(myAm, AKEY, RCOL, EKEY, ETOL);
        if (marked) {
            RKEY = 0; /* simplex refinement method (0=b-b, 1=q-b, 2=q-q) */
            BKEY = 0; /* bisect type (0=longest edge, 1=newest vertex,...) */
            PROK = 0; /* prolongation operator (0=[I,P], 1=[P]) */
            (void)AM_refine(myAm, RKEY, BKEY, PROK);
        } else {
            done = 1;
        }

        /* plot mesh */
        rwFlag = "w";
        OSKEY  = "INET"; /* VIO OUTPUT DEV type (sdio,file,buff,unix,inet) */
        OSFMT  = "ASC";  /* VIO OUTPUT DEV format (asc,xdr) */
        OSNAM  = "0";    /* VIO OUTPUT DEV name ([ buff | unix | inet ] num) */
        OHVAL  = "localhost"; /* VIO OUTPUT DEV host (INET hostname or IP) */
        VASSERT(VNULL!=(sock=Vio_socketOpen(rwFlag,OSKEY,OSFMT,OHVAL,OSNAM)));
        defKey = 0;   /* 0=plot mesh, 1=plot defX as deformation of mesh */
        CKEY   = 1;   /* color (0=none,1=simplex chart#,2=by bd face type) */
        DKEY   = -1;  /* subd write (-1=entire mesh,0<=k chart# simps only) */
        GVAL   = 1.0; /* glue value (separation of simplices in graphics) */
        FKEY   = 0;   /* volume/face plot/write (0=volume,1=face) [3D only] */
        Gem_writeGEOM(myGem, sock, defKey, CKEY, DKEY, GVAL, FKEY, defX, "GV");
        Vio_socketClose( &sock );

        /* are we done? */
        adaptIter++;
        if (adaptIter > adaptMax) {
            done = 1;
        }
    }

    /* destroy objects in reverse order */
    AM_dtor(    &myAm );
    Aprx_dtor(  &myAprx );
    Gem_dtor(   &myGem );
    myPDE_dtor( &myPde );

    /* kill the socket stuff */
    Vio_stop();

    /* normal return */
    return 0;
}

