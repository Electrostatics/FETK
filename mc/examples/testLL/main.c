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
 * rcsid="$Id: main.c,v 1.6 2010/08/12 05:18:00 fetk Exp $"
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
    int dualKey, done, marked, mcsf_format, defKey, CKEY, DKEY, FKEY;
    int LKEY, LMAX, PREC, GUES, PJAC, PVEC;
    int AKEY, RCOL, EKEY, RKEY, BKEY, PROK;
    int adaptIter, adaptMax, pkey;
    int key, flag, cycle, ip[10];
    int evalKey, energyKey, residKey, tangKey, massKey, bumpKey;
    double rp[10], GVAL, LTOL, ETOL;
    double *defX[3] = { VNULL, VNULL, VNULL };
    double alpha, beta, gam, xi, eps;
    char *rwFlag, *solFmt;
    char *ISKEY, *ISFMT, *IFNAM, *ISNAM, *IHVAL;
    char *OSKEY, *OSFMT, *OFNAM, *OSNAM, *OHVAL;
    Bvec *w[4], *u, *u2, *Au, *Mu, *Mu2;
    Bmat *A, *M;
    Mat *AA, *BB, *CC;
    double *aa, *bb, *cc, *dd;
    int i, j, k, m, n;

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
    adaptMax = 10;
    done = 0;
    adaptIter = 0;
    while (!done) {

        /* discretize */
        AM_create(myAm); /* initialize internal vector space structures */
        evalKey   = 0; /* forward (primal) problem (linearized about 0) */
        energyKey = 0; /* 0=don't assemble J --> J(u), 1=do it */
        residKey  = 1; /* 0=don't assemble F --> F(u)(v), 1=do it */
        tangKey   = 1; /* 0=don't assemble A --> DF(u)(w,v), 1=do it */
        massKey   = 1; /* 0=don't assemble mass matrix M, 1=do it */
        bumpKey   = 0; /* 0=no bumps*/
        Bvec_init(myAm->u, 0.2); /* initial guess of solution is zero */
     Bvec_print( myAm->u );
        AM_applyDiriZero( myAm, myAm->u ); /* enforce dirichlet cond */
     Bvec_print( myAm->u );
        Bmat_zero( myAm->A ); /* deal with dirichlet cond in matrix */
        Bvec_init( myAm->f,  0. ); /* initialize source term */
        Bvec_init( myAm->r,  0. ); /* initialize source term */
        AM_assem(myAm, evalKey, energyKey, residKey, tangKey, massKey, bumpKey,
            myAm->u, myAm->ud, myAm->f, ip, rp);

        /* solve */
        key   = 0;      /* A u = f rather than A^Tu = f */
        flag  = 0;      /* i/o flag; 0=none */
        LKEY  = 0;      /* linear solver (0=slu,1=mg,2=cg,3=bcg) */
        LMAX  = 100;    /* linear solve itmax (standalone or inside Newton) */
        LTOL  = 1.0e-7; /* linear solve tolerance (2-norm of rel resid) */
        PREC  = 2;      /* preconditioner (0=identity,1=diag-scale,2=mg) */
        cycle = 2;      /* symmetric multigrid */
#if 0
        Bvec_lmethod( myAm->u, myAm->A, myAm->f, myAm->r, myAm->ut,
            key, flag, LMAX, LTOL, PREC, cycle, myAm->P, LKEY );
#else
        Bvec_slu( myAm->u, myAm->A, myAm->f, myAm->r, myAm->ut, key, flag);
#endif
        A   = myAm->A;
        M   = myAm->M;
        u   = myAm->u;

        /* create some work vectors; also builds a shared dense matrix */
        Bvec_createVecMat(u, w, 4, &AA);

/* ************************************************************************ */

     /* Building other dense matrices (FORTRAN-compatible storage format) */
     n = u->n;
     m = 4;
     BB = Mat_ctor( VNULL, "BB", n, m );
     CC = Mat_ctor( VNULL, "CC", m, m );
     Mat_initStructure( BB, CFL_FORMAT, ISNOT_SYM, 0, VNULL, VNULL );
     Mat_initStructure( CC, CFL_FORMAT, ISNOT_SYM, 0, VNULL, VNULL );

     /* print the matrices */
     Mat_print( AA );
     Mat_print( BB );
     Mat_print( CC );

     /* Yanking out the core array for using e.g. w/ BLAS */
     aa = AA->A;
     bb = BB->A;
     cc = CC->A;

     /* Illustrating FORTRAN col-wise storage layout (copy Bvec into col) */
     dd = u->u;
     j = 2;
     for (i=0; i<k; i++) {
         bb[ j*m + i ] = dd[ i ];
     }

     /* Illustrating a call to BLAS DGEMM using these cores */
     alpha = 1.0;
     beta  = 1.0;
     dgemm_ ( "t","n", &m,&m,&n, &alpha, aa,&n, bb,&n, &beta, cc,&m, 1,1 );

/* ************************************************************************ */

        u2  = w[0];
        Au  = w[1];
        Mu  = w[2];
        Mu2 = w[3];
        gam = 0.1;
        pkey  = 0;   /* 0=>u=A*v, 1=>u=A'*v, 2=>u+=A*v, 3=>u+=A'*v */
        Bvec_matvec( Au, A, u, pkey, 0 );
        Bvec_axpy( u2, Au, gam );
        Bvec_matvec( Mu, M, u, pkey, 0 );
        Bvec_matvec( Mu2, M, u2, pkey, 0 );
        alpha = Bvec_dot( u2, Mu2 );
        beta  = Bvec_dot( u2, Mu );
        xi    = Bvec_dot( u, Mu );
        eps   = Bvec_dot( u, Au );
        fprintf(stderr,
           "alpha=<%13.6le> beta=<%13.6le> xi=<%13.6le> eps=<%13.6le>\n",
           alpha, beta, xi, eps);
        Bvec_destroyVecMat(u, w, 4, &AA);

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

