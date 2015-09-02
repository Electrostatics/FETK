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
 * rcsid="$Id: myelm.c,v 1.3 2010/08/12 05:18:09 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     myelm.c
 *
 * Purpose:  Define the trial and test elements, as well as bump-function
 *           variations for a posteriori error estimation.
 *
 *     Element number:        1
 *     Spatial dimension:     2 or 3
 *     Quadrature order:      1, 2, or 3
 *     Trial space:           continuous piecewise linear or quadratic
 *     Test space:            continuous piecewise linear or quadratic
 *     Trial bump space:      continuous piecewise bumps of next order
 *     Test bump space:       continuous piecewise bumps of next order
 *
 * Notes:    The user must provide:
 *
 *               VEXTERNC int simplexBasisInit(int key, int dim, int comp,
 *                   int *ndof, int dof[]);
 *               VEXTERNC void simplexBasisForm(int key, int dim, int comp,
 *                   int pdkey, double xq[], double basis[]);
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "mc/mc.h"

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
VEMBED(rcsid="$Id: myelm.c,v 1.3 2010/08/12 05:18:09 fetk Exp $")

const int P_DEG=1; /* 1=linear, 2=quadratic */

/*
 * ***************************************************************************
 * Required prototypes
 * ***************************************************************************
 */

VEXTERNC int simplexBasisInit(int key, int dim, int comp,
    int *ndof, int dof[]);
VEXTERNC void simplexBasisForm(int key, int dim, int comp,
    int pdkey, double xq[], double basis[]);

/*
 * ***************************************************************************
 * Element-specific
 * ***************************************************************************
 */

VPRIVATE void init_2DP1(int dimIS[], int *ndof, int dof[],
    double c[][VMAXP],
    double cx[][VMAXP], double cy[][VMAXP], double cz[][VMAXP]);
VPRIVATE void init_3DP1(int dimIS[], int *ndof, int dof[],
    double c[][VMAXP],
    double cx[][VMAXP], double cy[][VMAXP], double cz[][VMAXP]);

VPRIVATE void setCoef(int numP,
    double c[][VMAXP],
    double cx[][VMAXP], double cy[][VMAXP], double cz[][VMAXP],
    int ic[][VMAXP],
    int icx[][VMAXP], int icy[][VMAXP], int icz[][VMAXP]);

VPRIVATE void polyEval(int numP,
    double p[], double c[][VMAXP], double xv[]);

/*
 * ***************************************************************************
 * 2D-P1 Basis:
 *
 *     p1(x,y) = c0 + c1*x + c2*y
 *
 *     Lagrange Point    Lagrange Basis Function Definition
 *     --------------    ----------------------------------
 *     (0, 0)            p[0](x,y) = 1 - x - y
 *     (1, 0)            p[1](x,y) = x
 *     (0, 1)            p[2](x,y) = y
 *
 * ***************************************************************************
 */
VPRIVATE int dim_2DP1 = 3;
VPRIVATE int lgr_2DP1[3][VMAXP] = {
/*c0  c1  c2  c3  ---------------------------------------------------------- */
/* 1   x   y   z  ---------------------------------------------------------- */
{  2, -2, -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DP1x[3][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DP1y[3][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DP1z[3][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};

/*
 * ***************************************************************************
 * 3D-P1 Basis:
 *
 *     p1(x,y,z) = c0 + c1*x + c2*y + c3*z
 *
 *     Lagrange Point    Lagrange Basis Function Definition
 *     --------------    ----------------------------------
 *     (0, 0, 0)         p[0](x,y,z) = 1 - x - y - z
 *     (1, 0, 0)         p[1](x,y,z) = x
 *     (0, 1, 0)         p[2](x,y,z) = y
 *     (0, 0, 1)         p[3](x,y,z) = z
 *
 * ***************************************************************************
 */
VPRIVATE int dim_3DP1 = 4;
VPRIVATE int lgr_3DP1[4][VMAXP] = {
/*c0  c1  c2  c3  ---------------------------------------------------------- */
/* 1   x   y   z  ---------------------------------------------------------- */
{  2, -2, -2, -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_3DP1x[4][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_3DP1y[4][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_3DP1z[4][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
};

/*
 * ***************************************************************************
 * Routine:  polyEval
 *
 * Purpose:  Evaluate a collection of at most cubic polynomials at a
 *           specified point in at most R^3.
 *
 * Input:    numP           == the number of polynomials to evaluate
 *           c[numP][VMAXP] == the coefficients of each polynomial
 *           xv[3]          == the point (x,y,z) to evaluate the polynomials.
 *
 * Output:   p[numP]        == the results of the evaluation
 *
 * Notes:    Note that "VMAXP" must be >= 19 for cubic polynomials.
 *           The polynomials are build from the coefficients c[][] as
 *           follows.  To build polynomial "k", fix k and set:
 *
 *               c0=c[k][0], c1=c[k][1], .... , cp=c[k][p]
 *
 *           Then evaluate as:
 *
 *             p3(x,y,z) = c0 + c1*x + c2*y + c3*z
 *                       + c4*x*x + c5*y*y + c6*z*z + c7*x*y + c8*x*z + c9*y*z
 *                       + c10*x*x*x + c11*y*y*y + c12*z*z*z
 *                       + c13*x*x*y + c14*x*x*z + c15*x*y*y
 *                       + c16*y*y*z + c17*x*z*z + c18*y*z*z
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void polyEval(int numP,
    double p[], double c[][VMAXP], double xv[])
{
    int i;
    double x, y, z;

    x = xv[0];
    y = xv[1];
    z = xv[2];
    for (i=0; i<numP; i++) {
        p[i] = c[i][0]
             + c[i][1]  * x
             + c[i][2]  * y
             + c[i][3]  * z
             + c[i][4]  * x*x
             + c[i][5]  * y*y
             + c[i][6]  * z*z
             + c[i][7]  * x*y
             + c[i][8]  * x*z
             + c[i][9]  * y*z
             + c[i][10] * x*x*x
             + c[i][11] * y*y*y
             + c[i][12] * z*z*z
             + c[i][13] * x*x*y
             + c[i][14] * x*x*z
             + c[i][15] * x*y*y
             + c[i][16] * y*y*z
             + c[i][17] * x*z*z
             + c[i][18] * y*z*z;
    }
}

/*
 * ***************************************************************************
 * Routine:  setCoef
 *
 * Purpose:  Setup coefficients of polynomals from integer table data.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void setCoef(int numP,
    double c[][VMAXP],
    double cx[][VMAXP], double cy[][VMAXP], double cz[][VMAXP],
    int ic[][VMAXP],
    int icx[][VMAXP], int icy[][VMAXP], int icz[][VMAXP])
{
    int i, j;
    for (i=0; i<numP; i++) {
        for (j=0; j<VMAXP; j++) {
            c[i][j]  = 0.5 * (double)ic[i][j];
            cx[i][j] = 0.5 * (double)icx[i][j];
            cy[i][j] = 0.5 * (double)icy[i][j];
            cz[i][j] = 0.5 * (double)icz[i][j];
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  simplexBasisInit
 *
 * Purpose:  Initialize the bases for the trial or the test space, for a
 *           particular component of the system, at all quadrature points
 *           on the master simplex element.
 *
 * Input:    key    = bases type to evaluate (0=trial,1=test,2=trialB,3=testB)
 *           dim    = spatial dimension (for ele that work in both 2D & 3D)
 *           comp   = which component of elliptic system to produce basis for
 *           pdkey  = basis partial differentian evaluation key:
 *
 *                       0 = evaluate basis(x,y,z)
 *                       1 = evaluate basis_x(x,y,z)
 *                       2 = evaluate basis_y(x,y,z)
 *                       3 = evaluate basis_z(x,y,z)
 *                       4 = evaluate basis_xx(x,y,z)
 *                       5 = evaluate basis_yy(x,y,z)
 *                       6 = evaluate basis_zz(x,y,z)
 *                       7 = etc...
 *
 * Output:   ndof              = total degrees of freedom
 *           nqpt              = number of quadrature points
 *           dof[4]            = degree of freedom information per v/e/f/s
 *           qpt[nqpt][3]      = coords of all quad points on master simplex
 *           basis[nqpt][ndof] = all basis funcs evaluated at all quad points
 *
 * Notes:    The basis ordering is important.  For a fixed quadrature
 *           point iq, you must follow the following ordering in p[iq][],
 *           based on how you specify the degrees of freedom in dof[]:
 *
 *               <v_0 vDF_0>,      <v_1 vDF_0>,      ..., <v_{nv} vDF_0>
 *               <v_0 vDF_1>,      <v_1 vDF_1>,      ..., <v_{nv} vDF_1>
 *                                    ...
 *               <v_0 vDF_{nvDF}>, <v_0 vDF_{nvDF}>, ..., <v_{nv} vDF_{nvDF}>
 *
 *               <e_0 eDF_0>,      <e_1 eDF_0>,      ..., <e_{ne} eDF_0>
 *               <e_0 eDF_1>,      <e_1 eDF_1>,      ..., <e_{ne} eDF_1>
 *                                    ...
 *               <e_0 eDF_{neDF}>, <e_1 eDF_{neDF}>, ..., <e_{ne} eDF_{neDF}>
 *
 *               <f_0 fDF_0>,      <f_1 fDF_0>,      ..., <f_{nf} fDF_0>
 *               <f_0 fDF_1>,      <f_1 fDF_1>,      ..., <f_{nf} fDF_1>
 *                                    ...
 *               <f_0 fDF_{nfDF}>, <f_1 fDF_{nfDF}>, ..., <f_{nf} fDF_{nfDF}>
 *
 *               <s_0 sDF_0>,      <s_1 sDF_0>,      ..., <s_{ns} sDF_0>
 *               <s_0 sDF_1>,      <s_1 sDF_1>,      ..., <s_{ns} sDF_1>
 *                                    ...
 *               <s_0 sDF_{nsDF}>, <s_1 sDF_{nsDF}>, ..., <s_{ns} sDF_{nsDF}>
 *
 *           For example, linear elements in R^3, with one degree of freedom
 *           at each vertex, would use the following ordering:
 *
 *               <v_0 vDF_0>, <v_1 vDF_0>, <v2 vDF_0>, <v_3 vDF_0>
 *
 *           Quadratic elements in R^2, with one degree of freedom at each
 *           vertex and edge, would use the following ordering:
 *
 *               <v_0 vDF_0>, <v_1 vDF_0>, <v_2 vDF_0>
 *               <e_0 eDF_0>, <e_1 eDF_0>, <e_2 eDF_0>
 *
 *           You can use different trial and test spaces for each component
 *           of the elliptic system, thereby allowing for the use of
 *           Petrov-Galerkin methods.  You MUST then tag the bilinear form
 *           symmetry entries as nonsymmetric in your PDE constructor to
 *           reflect that DF(u)(w,v) will be different from DF(u)(v,w), even
 *           if your form acts symmetrically when the same basis is used for
 *           w and v.
 *
 *           You can also use different trial spaces for each component of
 *           the elliptic system, and different test spaces for each component
 *           of the elliptic system.  This allows you to e.g. use a basis
 *           which is vertex-based for one component, and a basis which is
 *           edge-based for another.  This is useful in fluid mechanics,
 *           eletromagnetics, or simply to play around with different
 *           elements.
 *
 * Speed:    This function is called by MC to build new master elements
 *           whenever it reads in a new mesh.  Therefore, this function does
 *           not have to be all that fast, and e.g. could involve symbolic
 *           computation.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int numP;
VPRIVATE double c[VMAXP][VMAXP];
VPRIVATE double cx[VMAXP][VMAXP];
VPRIVATE double cy[VMAXP][VMAXP];
VPRIVATE double cz[VMAXP][VMAXP];
VPUBLIC int simplexBasisInit(int key, int dim, int comp,
    int *ndof, int dof[])
{
    int qorder, bump, dimIS[4];

    /* necessary quadrature order to return at the end */
    qorder = P_DEG;

    /* deal with bump function requests */
    if ((key == 0) || (key == 1)) {
        bump = 0;
    } else if ((key == 2) || (key == 3)) {
        bump = 1;
    } else { VASSERT(0); }

    /* for now use same element for all components, both trial and test */
    if (dim==2) {
        /* 2D simplex dimensions */
        dimIS[0] = 3;  /* number of vertices             */
        dimIS[1] = 3;  /* number of edges                */
        dimIS[2] = 0;  /* number of faces (3D only)      */
        dimIS[3] = 1;  /* number of simplices (always=1) */
        if (bump==0) {
            if (P_DEG==1) {
                init_2DP1(dimIS, ndof, dof, c, cx, cy, cz);
            } else if (P_DEG==2) {
                init_2DP1(dimIS, ndof, dof, c, cx, cy, cz);
            } else if (P_DEG==3) {
                init_2DP1(dimIS, ndof, dof, c, cx, cy, cz);
            } else Vnm_print(2, "..bad order..");
        } else if (bump==1) {
            if (P_DEG==1) {
                init_2DP1(dimIS, ndof, dof, c, cx, cy, cz);
            } else Vnm_print(2, "..bad order..");
        } else Vnm_print(2, "..bad bump..");
    } else if (dim==3) {
        /* 3D simplex dimensions */
        dimIS[0] = 4;  /* number of vertices             */
        dimIS[1] = 6;  /* number of edges                */
        dimIS[2] = 4;  /* number of faces (3D only)      */
        dimIS[3] = 1;  /* number of simplices (always=1) */
        if (bump==0) {
            if (P_DEG==1) {
                init_3DP1(dimIS, ndof, dof, c, cx, cy, cz);
            } else if (P_DEG==2) {
                init_3DP1(dimIS, ndof, dof, c, cx, cy, cz);
            } else if (P_DEG==3) {
                init_3DP1(dimIS, ndof, dof, c, cx, cy, cz);
            } else Vnm_print(2, "..bad order..");
        } else if (bump==1) {
            if (P_DEG==1) {
                init_3DP1(dimIS, ndof, dof, c, cx, cy, cz);
            } else Vnm_print(2, "..bad order..");
        } else Vnm_print(2, "..bad bump..");
    } else Vnm_print(2, "..bad dimension..");

    /* save number of DF */
    numP = *ndof;

    /* return the required quarature order */
    return qorder;
}

/*
 * ***************************************************************************
 * Routine:  simplexBasisForm
 *
 * Purpose:  Evaluate the bases for the trial or the test space, for a
 *           particular component of the system, at all quadrature points
 *           on the master simplex element.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void simplexBasisForm(int key, int dim, int comp,
    int pdkey, double xq[], double basis[])
{
    if (pdkey == 0) {
        polyEval(numP, basis, c, xq);
    } else if (pdkey == 1) {
        polyEval(numP, basis, cx, xq);
    } else if (pdkey == 2) {
        polyEval(numP, basis, cy, xq);
    } else if (pdkey == 3) {
        polyEval(numP, basis, cz, xq);
    } else { VASSERT(0); }
}

/*
 * ***************************************************************************
 * Routine:  init_2DP1
 *
 * Purpose:  2D linear master simplex information generator
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void init_2DP1(int dimIS[], int *ndof, int dof[],
    double c[][VMAXP],
    double cx[][VMAXP], double cy[][VMAXP], double cz[][VMAXP])
{
    int i;

    /* dof number and locations */
    dof[0] = 1;
    dof[1] = 0;
    dof[2] = 0;
    dof[3] = 0;
    *ndof  = 0;
    for (i=0; i<4; i++)
        *ndof += dimIS[i] * dof[i];
    VASSERT( *ndof == dim_2DP1 );
    VASSERT( *ndof <= VMAXP );

    /* coefficients of the polynomials */
    setCoef( *ndof, c, cx, cy, cz, lgr_2DP1, lgr_2DP1x, lgr_2DP1y, lgr_2DP1z );
}

/*
 * ***************************************************************************
 * Routine:  init_3DP1
 *
 * Purpose:  3D linear master simplex information generator
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void init_3DP1(int dimIS[], int *ndof, int dof[],
    double c[][VMAXP],
    double cx[][VMAXP], double cy[][VMAXP], double cz[][VMAXP])
{
    int i;

    /* dof number and locations */
    dof[0] = 1;
    dof[1] = 0;
    dof[2] = 0;
    dof[3] = 0;
    *ndof  = 0;
    for (i=0; i<4; i++)
        *ndof += dimIS[i] * dof[i];
    VASSERT( *ndof == dim_3DP1 );
    VASSERT( *ndof <= VMAXP );

    /* coefficients of the polynomials */
    setCoef( *ndof, c, cx, cy, cz, lgr_3DP1, lgr_3DP1x, lgr_3DP1y, lgr_3DP1z );
}

