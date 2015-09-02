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
 * rcsid="$Id: eval.c,v 1.8 2010/08/12 05:18:17 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     eval.c
 *
 * Purpose:  Class Aprx: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "aprx_p.h"

VEMBED(rcsid="$Id: eval.c,v 1.8 2010/08/12 05:18:17 fetk Exp $")

/*
 * ***************************************************************************
 * Class Aprx: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_APRX)

#endif /* if !defined(VINLINE_APRX) */
/*
 * ***************************************************************************
 * Class Aprx: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Aprx_evalFunc
 *
 * Purpose:  Evaluate a finite element solution at a set of arbitrary points.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_evalFunc(Aprx *thee,
    Bvec *u, int block, int numPts, double *pts,
    double *vals, int *marks)
{
    /* some variables */
    int i, k, smid, index, notFounds;
    double xgiven[3], phi[4], phix[4][3], um[4];
    SS *sm;

    Vnm_print(0,"Aprx_evalFunc: making slice..");

    /* initialize the interpolated values */
    for (k=0; k<numPts; k++) {
        marks[k] = 0;
        vals[k]  = 0.0;
    }

   /*
    * ************************************************************************
    * the BIG loop over all of the elements in the mesh..
    * ************************************************************************
    */
    for (smid=0; smid<Gem_numSS(thee->gm); smid++) {
        sm = Gem_SS(thee->gm,smid);

       /*
        * **********************
        * ONCE-PER-ELEMENT STUFF
        * **********************
        */

        if ( (smid>0) && (smid % VPRTKEY) == 0 ) Vnm_print(0,"[FEM:%d]",smid);

        /* go through all pts to see if in simplex; if so, do interpolation */
        for (index=0; index<numPts; index++) {

           /*
            * ********************
            * ONCE-PER-POINT STUFF
            * ********************
            */

            /* if haven't done the interpolation for this point yet, do it */
            if (marks[index] == 0) { 

                /* extract the current point */
                for (i=0; i<Gem_dimII(thee->gm); i++)
                    xgiven[i] = pts[3*index+i];

                /* If point in simplex then do interpolation */
                if ( Gem_pointInSimplexVal(thee->gm,sm,xgiven,phi,phix) ) {

                    /* marks as found */
                    marks[index] = 1;

                    /* get the multipliers */
                    for (i=0; i<Gem_dimVV(thee->gm); i++) {
                        um[i] = Bvec_valB( u, block, VV_id( SS_vertex(sm,i) ) );
#if 0
                        /* add in dirichlet function if necessary */
                        if (number < 0) {
                            um[i] += Bvec_valB(thee->W[W_ud], block,
                                VV_id(SS_vertex(sm,i)));
                        }
#endif
                    }

                    /* do the interpolation */
                    vals[index] = 0.;
                    for (i=0; i<Gem_dimVV(thee->gm); i++)
                        vals[index] += (um[i] * phi[i]);
                }

            } /* if haven't done interpolation for this point yet */
        } /* loop over all points */
    } /* loop over all simplices */

    /* count the number of points not found */
    notFounds = 0;
    for (k=0; k<numPts; k++)
        if (marks[k] == 0) notFounds++;
    Vnm_print(0,"..done. [numPts=%d,notFounds=%d]\n", numPts, notFounds);
}

/*
 * ***************************************************************************
 * Routine:  myint
 *
 * Purpose:  Grab the integer part of a double.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int myint(double x)
{
    double y;
    if (x >= 0) {
        return (int)x;
    } else {
        y = (double)(int)(-x) + 1.;
        return (int)(x+y) - (int)y;
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_fe2fd
 *
 * Purpose:  Interpolates data onto finite difference grid
 *
 * Notes:    Much is lifted from Aprx_evalFunc,
 *           with some ideas from Doug Arnold.
 *           Contributed by Karen Camarda.
 *
 * Example:  Below is a matlab example courtesy of Doug Arnold.
 *
 *    %-- BEGIN MATLAB CODE --------------------------------------------------
 *    
 *    function colormesh
 *    
 *    % This file demonstrates how to go from an unstructured grid to
 *    % a structured one.  Each point on the structured grid is colored
 *    % according to which triangle in the unstructured grid it belongs to.
 *    
 *    % Douglas N. Arnold, 3/4/98
 *    
 *    % set up a mesh
 *    npts=10;
 *    x=[ 1.13 1.66 0.50 0.46 0.26 0.20 0.70 1.93 1.01 0.65 ];
 *    y=[ 1.81 1.23 0.99 1.30 1.29 1.50 1.10 0.68 0.60 0.07 ];
 *    tri = delaunay(x,y);
 *    ntri=size(tri,1);
 *    
 *    % grid spacing
 *    h=.03;
 *    k=.04;
 *    
 *    clf
 *    [z,i]=sort(rand(64,1));
 *    colormap hsv;
 *    cmap = colormap;
 *    cmap=cmap(i,:,:);
 *    
 *    % loop over triangles
 *    for m = 1:ntri
 *      % get vertices of triangle i
 *      v1=[x(tri(m,1)),y(tri(m,1))];
 *      v2=[x(tri(m,2)),y(tri(m,2))];
 *      v3=[x(tri(m,3)),y(tri(m,3))];
 *      
 *      % plot the triangle
 *      ttt=[v1;v2;v3;v1];
 *      line(ttt(:,1),ttt(:,2),'color','green') 
 *    
 *      % find bounding box of triangle
 *      xmin = min([v1(1),v2(1),v3(1)]);
 *      xmax = max([v1(1),v2(1),v3(1)]);
 *      ymin = min([v1(2),v2(2),v3(2)]);
 *      ymax = max([v1(2),v2(2),v3(2)]);
 *    
 *      % loop through grid points in bounding box, plotting those in triangle
 *      for i = ceil(xmin/h):floor(xmax/h)
 *        for j = ceil(ymin/k):floor(ymax/k)
 *          if intriangle(v1,v2,v3,[i*h,j*k])
 *            % set color according to triangle number
 *        color = cmap(m,:);
 *            line(i*h,j*k,'marker','.','markersize',10,'color',color)
 *          end
 *        end
 *      end
 *    
 *    end
 *    
 *    function i = intriangle(v1,v2,v3,x)
 *    % INTRIANGLE -- check if a point belongs to a triangle
 *    %                
 *    % f = intriangle(v1,v2,v3,x)
 *    %
 *    % input:
 *    %   v1,v2,v3   2-vectors giving the vertices of the triangle
 *    %   x          2-vector giving the point
 *    %
 *    % output:
 *    %   i          1 if x belongs to the close triangle, 0 else
 *    
 *    % map point under affine mapping from given triangle to ref triangle
 *    xhat = (x-v1)/[v2-v1;v3-v1];
 *    % check if mapped point belongs to reference triangle
 *    i = xhat(1) >= 0 & xhat(2) >= 0 & 1-xhat(1)-xhat(2) >= 0;
 *    %-- END   MATLAB CODE --------------------------------------------------
 *
 * ***************************************************************************
 */
VPUBLIC void Aprx_fe2fd(Aprx *thee, Bvec *u, int block,
    int nx, int ny, int nz,
    double x0, double y0, double z0, double dx, double dy, double dz,
    int derivs, int outTypeKey)
{
    int smid, i, j, k, ijk, n, func, nfunc;
    int imin, imax, jmin, jmax, kmin, kmax;
    double xmin, xmax, ymin, ymax, zmin, zmax, initval=-2.;
    double x[3], phi[4], phix[4][3], um[4], *f;
    SS *sm;
    VV *vx;
    FILE *fptr;
    char filename[7];

    /* Some i/o */
    Vnm_print(0,"Aprx_fe2fd: WARNING: assuming single-chart manifold.\n");
    Vnm_print(0,"Aprx_fe2fd: Start function evaluation..");

    /* Initialize f to initval */
    f = Vmem_malloc( thee->vmem, nx*ny*nz, sizeof(double) );
    ijk = -1;
    for (i=0; i<nx; i++) {
        for (j=0; j<ny; j++) {
            for (k=0; k<nz; k++) {
                ijk++;
                f[ijk] = initval;
            }
        }
    }

    if (derivs) nfunc = 4;
    else        nfunc = 1;

    for (func=0; func<nfunc; func++) {
        /* Loop over simplices */
        for (smid=0; smid<Gem_numSS(thee->gm); smid++) {
            sm = Gem_SS(thee->gm,smid);

            /* Find the bounds of the box which contains the simplex */
            xmin = 10000.;
            xmax = -10000.;
            ymin = 10000.;
            ymax = -10000.;
            zmin = 10000.;
            zmax = -10000.;
            for (n=0; n<Gem_dimVV(thee->gm); n++) {
                vx = SS_vertex(sm,n);
                xmin = VMIN2(xmin, VV_coord(vx,0));
                xmax = VMAX2(xmax, VV_coord(vx,0));
                ymin = VMIN2(ymin, VV_coord(vx,1));
                ymax = VMAX2(ymax, VV_coord(vx,1));
                zmin = VMIN2(zmin, VV_coord(vx,2));
                zmax = VMAX2(zmax, VV_coord(vx,2));
            }

            /* Find which points on the structured mesh are within this box */
            imin = VMAX2(myint((xmin-x0-VSMALL)/dx)+1, 0);
            imax = VMIN2(myint((xmax-x0)/dx), nx-1);

            jmin = VMAX2(myint((ymin-y0-VSMALL)/dy)+1, 0);
            jmax = VMIN2(myint((ymax-y0)/dy), ny-1);

            kmin = VMAX2(myint((zmin-z0-VSMALL)/dz)+1, 0);
            kmax = VMIN2(myint((zmax-z0)/dz), nz-1);

            /* Go through points in box to see if in simplex; if so, interp */
            for (i=imin; i<=imax && i>=0 && i<=(nx-1); i++) {
                for (j=jmin; j<=jmax && j>=0 && j<=(ny-1); j++) {
                    for (k=kmin; k<=kmax && k>=0 && k<=(nz-1); k++) {
                        x[0] = x0 + (double)i*dx;
                        x[1] = y0 + (double)j*dy;
                        x[2] = z0 + (double)k*dz;

                        /* If point in simplex then do interpolation */
                        if ( Gem_pointInSimplexVal(thee->gm,sm,x,phi,phix) ) {

                            /* Get the multipliers */
                            for (n=0; n<Gem_dimVV(thee->gm); n++) {
                                um[n] = Bvec_valB(u, block,
                                     VV_id(SS_vertex(sm,n)));
#if 0
                                /* add in dirichlet function if necessary */
                                if (number < 0) {
                                    um[n] += Bvec_valB(thee->W[W_ud], block,
                                      VV_id(SS_vertex(sm,n)));
                                }
#endif
                            }

                            /* Do the interpolation */
                            ijk = i*ny*nz + j*nz + k;
                            f[ijk] = 0.;
                            if (func == 0) {
                                for (n=0; n<Gem_dimVV(thee->gm); n++)
                                    f[ijk] += um[n] * phi[n];
                            } else {
                                for (n=0; n<Gem_dimVV(thee->gm); n++)
                                    f[ijk] += um[n] * phix[n][func-1];
                            }

                        } /* if (found) */
                    } /* k loop */
                } /* j loop */
            } /* i loop */
        } /* Simplex loop */

        /* Output data */
        if (func == 0)
            sprintf(filename, "f%d.dat", block);
        else if (func == 1)
            sprintf(filename, "f%dx.dat", block);
        else if (func == 2)
            sprintf(filename, "f%dy.dat", block);
        else if (func == 3)
            sprintf(filename, "f%dz.dat", block);
        fptr = fopen(filename, "w");

        if (outTypeKey == 1) {  /* ASCII output */
            fprintf(fptr, "%d %d %d\n",nx,ny,nz);
            fprintf(fptr, "%f %f %f %f %f %f\n",dx,dy,dz,x0,y0,z0);
            ijk = -1;
            for (i=0; i<nx; i++) {
                for (j=0; j<ny; j++) {
                    for (k=0; k<nz; k++) {
                        ijk++;
                        fprintf(fptr, "%f\n", f[ijk]);
                    }
                }
            }
        } else {  /* Binary output */
            fwrite(&nx, sizeof(int), 1, fptr);
            fwrite(&ny, sizeof(int), 1, fptr);
            fwrite(&nz, sizeof(int), 1, fptr);
            fwrite(&dx, sizeof(double), 1, fptr);
            fwrite(&dy, sizeof(double), 1, fptr);
            fwrite(&dz, sizeof(double), 1, fptr);
            fwrite(&x0, sizeof(double), 1, fptr);
            fwrite(&y0, sizeof(double), 1, fptr);
            fwrite(&z0, sizeof(double), 1, fptr);
            fwrite(f, sizeof(double), nx*ny*nz, fptr);
        }

        fclose(fptr);

    } /* func loop */

    Vmem_free( thee->vmem, nx*ny*nz, sizeof(double), (void**)&f );

    Vnm_print(0,"..done.\n");
}

/*
 * ***************************************************************************
 * Routine:  Aprx_buildFunc
 *
 * Purpose:  Build finite element functions.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Aprx_buildFunc(Aprx *thee, Re *re,
    TT *t, int qp, int face, Bvec *u, Bvec *ud, Bvec *ut,
    double xq[], double U[], double dU[][3], double Ut[], double dUt[][3])
{
    int i, j, k;
    double phi[4], phix[4][3];
    double u_u[4][MAXV], u_ud[4][MAXV], u_t[4][MAXV];

    /* Get quad pt by mapping master el quad pt to this el */
    for (i=0; i<Gem_dimII(thee->gm); i++) {
        xq[i] = t->bb[i];
        for (j=0;j<Gem_dimII(thee->gm);j++)
            xq[i] += ( t->ff[i][j] * Re_x_hi(re,qp,j,face) );
    }

    /* Get basis functions; transform grads to arbitrary elm */
    for (i=0; i<Gem_dimVV(thee->gm); i++) {
        phi[i] = Re_phi_hi(re,qp,i,face);
        for (j=0; j<Gem_dim(thee->gm); j++) {
            phix[i][j] = 0.;
            for (k=0; k<Gem_dim(thee->gm); k++)
                phix[i][j] += ( t->gg[k][j] * Re_phix2_hi(re,qp,i,k,face) );
        }
    }

    /* Setup for initialize of [U+UD] and [dU+dUD] and [Ut] and [dUt] */
    for (j=0; j<Gem_dimVV(thee->gm); j++) {
        for (i=0; i<Aprx_numB(thee); i++) {
            u_u[j][i]  = Bvec_valB( u,  i, t->vid[j] );
            u_ud[j][i] = Bvec_valB( ud, i, t->vid[j] );
            u_t[j][i]  = Bvec_valB( ut, i, t->vid[j] );
        }
    }

    /* Initialize [U+UD] and [dU+dUD] and [Ut] and [dUt] */
    for (i=0; i<Aprx_numB(thee); i++) {
        U[i]  = 0.;
        Ut[i] = 0.;
        for (k=0; k<Gem_dim(thee->gm); k++) {
            dU[i][k]  = 0.;
            dUt[i][k] = 0.;
            for (j=0; j<Gem_dimVV(thee->gm); j++) {
                if (k==0) {
                    U[i]  += phi[j] * ( u_u[j][i] + u_ud[j][i] );
                    Ut[i] += phi[j] * u_t[j][i];
                }
                dU[i][k]  += phix[j][k] * ( u_u[j][i] + u_ud[j][i] );
                dUt[i][k] += phix[j][k] * u_t[j][i];
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Aprx_bndIntegralSimplex
 *
 * Purpose:  Evaluate a given boundary integral restricted to one simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Aprx_bndIntegralSimplex(Aprx *thee, Bvec *u, Bvec *ud, Bvec *ut,
    SS *sm, int block, double val[])
{
    /* some variables */
    int i, m, face, someComponentIsBoundary;
    double Dw, faceInt, xm[3], U[MAXV], dU[MAXV][3], Ut[MAXV], dUt[MAXV][3];
    TT t;
    Re *re;

    /* initialize integral for this element */
    val[0] = 0.;
        
    /* volume trans from master to this element (and back) */
    Gem_buildVolumeTrans(thee->gm,sm,&t);

    /* hard-code element for now... */
    re = thee->re[0];

    /* go through the faces */
    for (face=0; face<Gem_dimVV(thee->gm); face++) {

        /* boundary trans from master to this element (and back) */
        Gem_buildSurfaceTrans(thee->gm,face,&t);

        /* NOTE: This does integrals over Dirichlet boundaries also!!! */
        /* if outer boundary face, do integral */
        someComponentIsBoundary = 0;
        for (i=0; i<PDE_vec(thee->pde); i++) {
            if (VBOUNDARY( thee->pde->bmap[i][ SS_faceType(sm,face) ] )) {
                someComponentIsBoundary = 1;
            }
        }

        if ( someComponentIsBoundary ) {

            /* Cycle thru quad points (diff edge integs poss) */
            for (m=0; m<Re_numQ_hi(re,face); m++) {

                /* jacobian and quadrature weight */
                Dw = t.faceD[face] * Re_w_hi(re,m,face);

                /* evaluate solution/gradient/model at current quad point */
                Aprx_buildFunc(thee,re, &t, m, face, u,ud,ut, xm, U,dU, Ut,dUt);

                /* evaluate the normal derivative */
                faceInt = 0.;
                for (i=0; i<Gem_dimII(thee->gm); i++)
                    faceInt += ( dU[block][i] * t.nvec[face][i] );
#if 0
                Vnm_print(0,"faceInt=<%g>   Anal=<%g>\n",
                    faceInt,1.0/250000.0);
#endif

                /* add in contribution from this quadrature point */
                val[0] += ( Dw * faceInt );

            } /* m; loop over surface quadrature points */
        } /* if neumann surface */
    } /* r; loop over surfaces of the element */
}

/*
 * ***************************************************************************
 * Routine:  Aprx_bndIntegral
 *
 * Purpose:  Evaluate a given boundary integral.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_bndIntegral(Aprx *thee, Bvec *u, Bvec *ud, Bvec *ut)
{
    /* some variables */
    int smid, block=0;
    double val[MAXV], valTmp[MAXV];
    SS *sm;

    /* initialize result */
    val[0] = 0.;

    /* traverse the simplices and compute the boundary integral */
    Vnm_print(0,"Aprx_bndIntegral: computing boundary integral..");
    smid = 0;
    while ( (smid < Gem_numSS(thee->gm)) && (!Vnm_sigInt()) ) {
        sm = Gem_SS(thee->gm,smid);

        if ( (smid>0) && (smid % VPRTKEY) == 0 ) Vnm_print(0,"[MS:%d]",smid);
        
        /* get this element contribution */
        Aprx_bndIntegralSimplex(thee, u, ud, ut, sm, block, valTmp);
        val[0] += valTmp[0];

        /* next sm */
        smid++;

    } /* el; loop over elements */

    /* hard-coded scaling for specific problem */
    val[0] /= (4. * VPI);

    /* do some i/o */
    Vnm_print(0,"..done.  [val[0]=<%g>]\n",val[0]);
}

/*
 * ***************************************************************************
 * Routine:  Aprx_admMass
 *
 * Purpose:  Evaluate ADM mass from conformal factor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_admMass(Aprx *thee, Bvec *u, Bvec *ud, Bvec *ut, int block)
{
    /* some variables */
    int smid;
    double mass, massTmp;
    SS *sm;

    /* initialize result */
    mass = 0.;

    /* traverse the simplices and compute the boundary integral */
    Vnm_print(0,"Aprx_admMass: computing boundary integral..");
    smid = 0;
    while ( (smid < Gem_numSS(thee->gm)) && (!Vnm_sigInt()) ) {
        sm = Gem_SS(thee->gm,smid);

        if ( (smid>0) && (smid % VPRTKEY) == 0 ) Vnm_print(0,"[MS:%d]",smid);
        
        /* get this element contribution */
        Aprx_bndIntegralSimplex(thee, u, ud, ut, sm, block, &massTmp);
        mass += massTmp;

        /* next sm */
        smid++;

    } /* el; loop over elements */

    /* hard-coded scaling for specific problem */
    mass /= (2. * VPI);

    /* do some i/o */
    Vnm_print(0,"..done.  [ADM mass=<%g>]\n",mass);
}

/*
 * ***************************************************************************
 * Routine:  Aprx_evalL2
 *
 * Purpose:  Compute the L2 norm of the difference of two functions.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE double Aprx_evalL2(Aprx *thee, SS *sm, Bvec *u, Bvec *ud, Bvec *ut)
{
    /* some variables */
    int i, m, face;
    double Dw, theError, nval, tmp;
    double xm[3], U[MAXV], dU[MAXV][3], Ut[MAXV], dUt[MAXV][3];
    Re *re;
    TT t;

    /* initialize the error for this element */
    theError = 0.0;
        
    /* volume trans from master to this element (and back) */
    Gem_buildVolumeTrans(thee->gm,sm,&t);

    /* hard-code element for now... */
    re = thee->re[0];

    /* Cycle thru quad points */
    face = -1;
    for (m=0; m<Re_numQ_hi(re,face); m++) {

        /* jacobian and quadrature weight */
        Dw = t.D * Re_w_hi(re,m,face);

        /* evaluate solution/gradient/model at current quad point */
        Aprx_buildFunc(thee,re,&t,m,face,u,ud,ut,xm,U,dU,Ut,dUt);

        /* evaluate difference in element:  (u+ud) - ut */
        nval = 0.;
        for (i=0; i<Aprx_numB(thee); i++) {
            tmp = ( U[i] - Ut[i] );
            nval += tmp*tmp;
        }
        theError += ( Dw * nval );

    } /* m; loop over volume quadrature points */

    return theError;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_evalL8
 *
 * Purpose:  Compute the L8 norm of the difference of two functions.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE double Aprx_evalL8(Aprx *thee, SS *sm, Bvec *u, Bvec *ud, Bvec *ut)
{
    /* some variables */
    int i, m, face;
    double theError;
    double xm[3], U[MAXV], dU[MAXV][3], Ut[MAXV], dUt[MAXV][3];
    Re *re;
    TT t;

    /* initialize the error for this element */
    theError = 0.0;
        
    /* volume trans from master to this element (and back) */
    Gem_buildVolumeTrans(thee->gm,sm,&t);

    /* hard-code element for now... */
    re = thee->re[0];

    /* Cycle thru quad points */
    face = -1;
    for (m=0; m<Re_numQ_hi(re,face); m++) {

        /* evaluate solution/gradient/model at current quad point */
        Aprx_buildFunc(thee,re,&t,m,face,u,ud,ut,xm,U,dU,Ut,dUt);

        /* evaluate difference in element:  (u+ud) - ut */
        for (i=0; i<Aprx_numB(thee); i++) {
            theError = VMAX2( theError, VABS(U[i] - Ut[i]) );
        }

    } /* m; loop over volume quadrature points */

    return theError;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_evalH1
 *
 * Purpose:  Compute the H1 norm of the difference of two functions.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
/*RYAN*/
/*VPRIVATE double Aprx_evalH1(Aprx *thee, SS *sm, Bvec *u, Bvec *ud, Bvec *ut)*/
VPUBLIC double Aprx_evalH1(Aprx *thee, SS *sm, Bvec *u, Bvec *ud, Bvec *ut)
{
    /* some variables */
    int i, j, m, face;
    double Dw, theError, nval, tmp;
    double xm[3], U[MAXV], dU[MAXV][3], Ut[MAXV], dUt[MAXV][3];
    Re *re;
    TT t;

    /* initialize the error for this element */
    theError = 0.0;
        
    /* volume trans from master to this element (and back) */
    Gem_buildVolumeTrans(thee->gm,sm,&t);

    /* hard-code element for now... */
    re = thee->re[0];

    /* Cycle thru quad points */
    face = -1;
    for (m=0; m<Re_numQ_hi(re,face); m++) {

        /* jacobian and quadrature weight */
        Dw = t.D * Re_w_hi(re,m,face);

        /* evaluate solution/gradient/model at current quad point */
        Aprx_buildFunc(thee,re,&t,m,face,u,ud,ut,xm,U,dU,Ut,dUt);

	/* ACTUALLY evaluate exact solution */
	thee->pde->u_T(thee->pde, t.stype, t.gchart, xm, Ut, dUt);

        /* evaluate difference in element:  (u+ud) - ut */
        nval = 0.;
        for (i=0; i<Aprx_numB(thee); i++) {
            tmp = ( U[i] - Ut[i] );
            nval += tmp*tmp;
            for (j=0; j<Gem_dim(thee->gm); j++) {
                tmp = ( dU[i][j] - dUt[i][j] );
                nval += tmp*tmp;
            }
        }
        theError += ( Dw * nval );

    } /* m; loop over volume quadrature points */

    return theError;
}

/*
 * ***************************************************************************
 * Routine:  Aprx_evalError
 *
 * Purpose:  Evaluate error in solution in one of several norms.
 *
 * Notes:    We evaluate the error in the solution (in the case that
 *           an exact analytical solution is available) in one of several
 *           norms:
 *
 *           If (key == 0) ==> L^2 norm of the error.
 *           If (key == 1) ==> L^{\infty} norm of the error.
 *           If (key == 2) ==> H^1 norm of the error.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Aprx_evalError(Aprx *thee, int pcolor, int key,
    Bvec *u, Bvec *ud, Bvec *ut)
{
    /* some variables */
    int smid;
    double theError, minError, maxError, simError;
    SS *sm;

    /* input check and some i/o */
    if (key == 0) {
        Vnm_print(0,"Aprx_evalError: computing L2 norm of the error.\n");
    } else if (key == 1) {
        Vnm_print(0,"Aprx_evalError: computing L8 norm of the error.\n");
    } else if (key == 2) {
        Vnm_print(0,"Aprx_evalError: computing H1 norm of the error.\n");
    } else {
        Vnm_print(0,"Aprx_evalError: bad key given.\n");
        return 0.0;
    }

    minError =  VLARGE;
    maxError = -VLARGE;
    theError = 0.;

    /* traverse the simplices and compute the error */
    Vnm_print(0,"Aprx_evalError: estimating error..");
    smid = 0;
    while ( (smid < Gem_numSS(thee->gm)) && (!Vnm_sigInt()) ) {
        sm = Gem_SS(thee->gm,smid);

        if ( (smid>0) && (smid % VPRTKEY) == 0 ) Vnm_print(0,"[MS:%d]",smid);
        
        /* compute the error for this element if it is in the set */
        if ( ((int)SS_chart(sm)==pcolor) || (pcolor<0) ) {

            /* compute the appropriate error for the element */
            simError = 0.;
            if (key == 0) {
                simError = Aprx_evalL2(thee, sm, u,ud,ut);
            } else if (key == 1) {
                simError = Aprx_evalL8(thee, sm, u,ud,ut);
            } else if (key == 2) {
                simError = Aprx_evalH1(thee, sm, u,ud,ut);
            } else { VASSERT(0); }
            VASSERT( simError >= 0. );

            /* keep track of min/max errors over the mesh */
            minError = VMIN2( VABS(simError), minError );
            maxError = VMAX2( VABS(simError), maxError );

            /* accumlate into the total error */
            if (key == 0) {
                theError += simError;
            } else if (key == 1) {
                theError = VMAX2( theError, simError );
            } else if (key == 2) {
                theError += simError;
            } else { VASSERT(0); }

        }

        /* next sm */
        smid++;

    } /* el; loop over elements */

    /* final fixup of error */
    if (key == 0) {
        theError = VSQRT( theError );
    } else if (key == 1) {
        /* no-op */
    } else if (key == 2) {
        theError = VSQRT( theError );
    } else { VASSERT(0); }

    /* do some i/o */
    Vnm_print(0,"..done.  [theError=<%g>  maxError=<%g>  minError=<%g>]\n",
        theError,maxError,minError);

    /* return */
    return theError;
}

