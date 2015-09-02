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
 * rcsid="$Id: mypde.c,v 1.4 2010/08/12 05:17:35 fetk Exp $"
 * ***************************************************************************
 */

/* ///////////////////////////////////////////////////////////////////////////
// File:     mypde.c
//
// Purpose:  Class PDE: methods.
//
//     Problem type:          scalar nonlinear test problem
//     Spatial dimension:     2 or 3
//     Product dimension:     1
//     Differential operator: Linear or nonlinear potential equation
//                            with symmetric or nonsymmetric linear part
//     Boundary conditions:   zero or nonzero Dirichlet conditions
//                            nonzero or zero Neumann/Robin conditions
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */

#include "mypde.h"

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void**)&rcsid);
VEMBED(rcsid="$Id: mypde.c,v 1.4 2010/08/12 05:17:35 fetk Exp $")

const int P_DIR=0; /* 0=zero Dirichlet, 1=nonzero Dirichlet     */
const int P_NEU=0; /* 0=standard Neumann, 1=Robin term also     */
const int P_NSY=0; /* 0=symmetric, 1=non-symmetric              */
const int P_NON=0; /* 0=linear, 1=linear Helmholtz, 2=nonlinear */
const int P_NUN=1; /* 0=smooth solution, 1=highly non-uniform   */

/* ///////////////////////////////////////////////////////////////////////////
// Problem-specific
/////////////////////////////////////////////////////////////////////////// */

const double PP = -21.;
const double QQ = 0.05;
const double RR = 0.9;
const double C0 = 0.25;
const double C1 = 0.25;
const double C2 = 0.25;

VPRIVATE double FAC(int d, int m, double *x);
VPRIVATE double FACx0(int d, int m, double *x);
VPRIVATE double FACx1(int d, int m, double *x);
VPRIVATE double FACx2(int d, int m, double *x);
VPRIVATE double FACxx0(int d, int m, double *x);
VPRIVATE double FACxx1(int d, int m, double *x);
VPRIVATE double FACxx2(int d, int m, double *x);
VPRIVATE double UU(int d, int m, double *x);
VPRIVATE double UUx0(int d, int m, double *x);
VPRIVATE double UUx1(int d, int m, double *x);
VPRIVATE double UUx2(int d, int m, double *x);
VPRIVATE double UUxx0(int d, int m, double *x);
VPRIVATE double UUxx1(int d, int m, double *x);
VPRIVATE double UUxx2(int d, int m, double *x);
VPRIVATE double Ux0(int d, int m, double *x);
VPRIVATE double Ux1(int d, int m, double *x);
VPRIVATE double Ux2(int d, int m, double *x);
VPRIVATE double Uxx0(int d, int m, double *x);
VPRIVATE double Uxx1(int d, int m, double *x);
VPRIVATE double Uxx2(int d, int m, double *x);
VPRIVATE void my_D(int d, int m, double *x, double *f);
VPRIVATE double my_A(int d, int m, double *x);
VPRIVATE double my_B(int d, int m, double A, double *DN, double *x,
    double *u);
VPRIVATE double my_DB(int d, int m, double *x, double *u);
VPRIVATE double my_C(int d, int m, double *x);
VPRIVATE double my_GN(int d, int m, double A, double C, double *x);
VPRIVATE double my_US(int d, int m, double *x);

VPRIVATE double FAC(int d, int m, double *x) {
    double value;
    if (!P_NUN) value = 1.;
    else {
        double dist = 0.; 
        if (d==2) dist = VSQR(C0-x[0])+VSQR(C1-x[1]);
        else      dist = VSQR(C0-x[0])+VSQR(C1-x[1])+VSQR(C2-x[2]);
        value = QQ*VPOW(RR+dist,PP);
    }
    return value;
}
VPRIVATE double FACx0(int d, int m, double *x) {
    double value;
    if (!P_NUN) value = 0.;
    else {
        double dist = 0.; 
        if (d==2) dist = VSQR(C0-x[0])+VSQR(C1-x[1]);
        else      dist = VSQR(C0-x[0])+VSQR(C1-x[1])+VSQR(C2-x[2]);
        value = -2.*(C0-x[0])*PP*QQ*VPOW(RR+dist,PP-1);
    }
    return value;
}
VPRIVATE double FACx1(int d, int m, double *x) {
    double value;
    if (!P_NUN) value = 0.;
    else {
        double dist = 0.; 
        if (d==2) dist = VSQR(C0-x[0])+VSQR(C1-x[1]);
        else      dist = VSQR(C0-x[0])+VSQR(C1-x[1])+VSQR(C2-x[2]);
        value = -2.*(C1-x[1])*PP*QQ*VPOW(RR+dist,PP-1);
    }
    return value;
}
VPRIVATE double FACx2(int d, int m, double *x) {
    double value, dist = 0.; 
    if (!P_NUN) value = 0.;
    else {
        if (d==2) dist = VSQR(C0-x[0])+VSQR(C1-x[1]);
        else      dist = VSQR(C0-x[0])+VSQR(C1-x[1])+VSQR(C2-x[2]);
        value = -2.*(C2-x[2])*PP*QQ*VPOW(RR+dist,PP-1);
    }
    return value;
}
VPRIVATE double FACxx0(int d, int m, double *x) {
    double value, dist = 0.; 
    if (!P_NUN) value = 0.;
    else {
        if (d==2) dist = VSQR(C0-x[0])+VSQR(C1-x[1]);
        else      dist = VSQR(C0-x[0])+VSQR(C1-x[1])+VSQR(C2-x[2]);
        value = 2.*PP*QQ*VPOW(RR+dist,PP-1)
              + 4.*PP*QQ*(PP-1)*VSQR(C0-x[0])*VPOW(RR+dist,PP-2);
    }
    return value;
}
VPRIVATE double FACxx1(int d, int m, double *x) {
    double value;
    if (!P_NUN) value = 0.;
    else {
        double dist = 0.; 
        if (d==2) dist = VSQR(C0-x[0])+VSQR(C1-x[1]);
        else      dist = VSQR(C0-x[0])+VSQR(C1-x[1])+VSQR(C2-x[2]);
        value = 2.*PP*QQ*VPOW(RR+dist,PP-1)
              + 4.*PP*QQ*(PP-1)*VSQR(C1-x[1])*VPOW(RR+dist,PP-2);
    }
    return value;
}
VPRIVATE double FACxx2(int d, int m, double *x) {
    double value, dist = 0.; 
    if (!P_NUN) value = 0.;
    else {
        if (d==2) dist = VSQR(C0-x[0])+VSQR(C1-x[1]);
        else      dist = VSQR(C0-x[0])+VSQR(C1-x[1])+VSQR(C2-x[2]);
        value = 2.*PP*QQ*VPOW(RR+dist,PP-1)
              + 4.*PP*QQ*(PP-1)*VSQR(C2-x[2])*VPOW(RR+dist,PP-2);
    }
    return value;
}
VPRIVATE double UU(int d, int m, double *x) {
    double value;
    if (d==2) {
        if (P_DIR==0) value = VSIN(VPI*x[0])*VSIN(VPI*x[1]);
        else          value = VCOS(VPI*x[0])*VCOS(VPI*x[1]);
    } else { /* (d==3) */
        if (P_DIR==0) value = VSIN(VPI*x[0])*VSIN(VPI*x[1])*VSIN(VPI*x[2]);
        else          value = VCOS(VPI*x[0])*VCOS(VPI*x[1])*VCOS(VPI*x[2]);
    }
    return value;
}
VPRIVATE double UUx0(int d, int m, double *x) {
    double value;
    if (d==2) {
        if (P_DIR==0) value =  VPI*VCOS(VPI*x[0])*VSIN(VPI*x[1]);
        else          value = -VPI*VSIN(VPI*x[0])*VCOS(VPI*x[1]);
    } else { /* (d==3) */
        if (P_DIR==0) value =  VPI*VCOS(VPI*x[0])*VSIN(VPI*x[1])*VSIN(VPI*x[2]);
        else          value = -VPI*VSIN(VPI*x[0])*VCOS(VPI*x[1])*VCOS(VPI*x[2]);
    }
    return value;
}
VPRIVATE double UUx1(int d, int m, double *x) {
    double value;
    if (d==2) {
        if (P_DIR==0) value =  VPI*VSIN(VPI*x[0])*VCOS(VPI*x[1]);
        else          value = -VPI*VCOS(VPI*x[0])*VSIN(VPI*x[1]);
    } else { /* (d==3) */
        if (P_DIR==0) value =  VPI*VSIN(VPI*x[0])*VCOS(VPI*x[1])*VSIN(VPI*x[2]);
        else          value = -VPI*VCOS(VPI*x[0])*VSIN(VPI*x[1])*VCOS(VPI*x[2]);
    }
    return value;
}
VPRIVATE double UUx2(int d, int m, double *x) {
    double value;
    if (d==2) {
        value = 0.0;
    } else { /* (d==3) */
        if (P_DIR==0) value =  VPI*VSIN(VPI*x[0])*VSIN(VPI*x[1])*VCOS(VPI*x[2]);
        else          value = -VPI*VCOS(VPI*x[0])*VCOS(VPI*x[1])*VSIN(VPI*x[2]);
    }
    return value;
}
VPRIVATE double UUxx0(int d, int m, double *x) {return -VPI*VPI*UU(d,m,x);}
VPRIVATE double UUxx1(int d, int m, double *x) {return -VPI*VPI*UU(d,m,x);}
VPRIVATE double UUxx2(int d, int m, double *x) {return -VPI*VPI*UU(d,m,x);}
VPRIVATE double Ux0(int d, int m, double *x) {
    return FACx0(d,m,x) * UU(d,m,x) + FAC(d,m,x) * UUx0(d,m,x);
}
VPRIVATE double Ux1(int d, int m, double *x) {
    return FACx1(d,m,x) * UU(d,m,x) + FAC(d,m,x) * UUx1(d,m,x);
}
VPRIVATE double Ux2(int d, int m, double *x) {
    if (d==2) return 0.;
    else return FACx2(d,m,x) * UU(d,m,x) + FAC(d,m,x) * UUx2(d,m,x);
}
VPRIVATE double Uxx0(int d, int m, double *x) {
    return FACxx0(d,m,x) * UU(d,m,x)
         + 2. * FACx0(d,m,x) * UUx0(d,m,x)
         + FAC(d,m,x) * UUxx0(d,m,x);
}
VPRIVATE double Uxx1(int d, int m, double *x) {
    return FACxx1(d,m,x) * UU(d,m,x)
         + 2. * FACx1(d,m,x) * UUx1(d,m,x)
         + FAC(d,m,x) * UUxx1(d,m,x);
}
VPRIVATE double Uxx2(int d, int m, double *x) {
    if (d==2) return 0.;
    else return FACxx2(d,m,x) * UU(d,m,x)
              + 2. * FACx2(d,m,x) * UUx2(d,m,x)
              + FAC(d,m,x) * UUxx2(d,m,x);
}

VPRIVATE void my_D(int d, int m, double *x, double *f) {
    double magNsym = 1.0 * P_NSY;
    f[0] = magNsym;
    f[1] = magNsym;
    if (d==3) f[2] = magNsym;
    else      f[2] = 0.0;
}
VPRIVATE double my_A(int d, int m, double *x) { return 1.0; }
VPRIVATE double my_B(int d, int m, double A, double *DN, double *x,
    double *u) {
    double SRC;
    double helm  = 0.0;
    double helmt = 0.0;
    if (P_NON==0) { /* linear potential operator */
        helm  = 0.0;
        helmt = 0.0;
    } else if (P_NON==1) { /* linear helmholtz operator */
        helm  = 100.0 * u[0];
        helmt = 100.0 * my_US(d,m,x);
    } else if (P_NON==2) { /* nonlinear operator */
        helm  = VPOW(u[0],3.0);
        helmt = VPOW(my_US(d,m,x),3.0);
    }
    SRC = - A * ( Uxx0(d,m,x) + Uxx1(d,m,x) + Uxx2(d,m,x) )
          + DN[0]*Ux0(d,m,x) + DN[1]*Ux1(d,m,x) + DN[2]*Ux2(d,m,x)
          + helmt;
    return helm - SRC;
}
VPRIVATE double my_DB(int d, int m, double *x, double *u) {
    if (P_NON==0) /* linear potential operator */
        return 0.0;
    else if (P_NON==1) /* linear helmholtz operator */
        return 100.0;
    else if (P_NON==2) /* nonlinear operator */
        return 3.0*VPOW(u[0],2.0);
    return 0.0;
}
VPRIVATE double my_C(int d, int m, double *x) {
    if (P_NEU==0) return 0.0; /* neumann condition */
    else          return 1.0; /* robin condition */
}
VPRIVATE double my_GN(int d, int m, double A, double C, double *x) {
    double value, u, u_x0, u_x1, u_x2;
    value = 0.0;
    u = my_US(d, m, x);
    u_x0 = Ux0(d, m, x);
    u_x1 = Ux1(d, m, x);
    u_x2 = Ux2(d, m, x);
    if (d==2) {
        if      (VABS( x[0] - 0.0 ) < VSMALL) value = - A*u_x0+C*u;
        else if (VABS( x[0] - 1.0 ) < VSMALL) value =   A*u_x0+C*u;
        else if (VABS( x[1] - 0.0 ) < VSMALL) value = - A*u_x1+C*u;
        else if (VABS( x[1] - 1.0 ) < VSMALL) value =   A*u_x1+C*u;
        else {
            /* Vnm_print(2, "my_GN: there is some problem...\n"); */
            /* Vnm_print(2, "my_GN: x=(%e,%e,%e)\n", x[0], x[1], x[2]); */
            value = 0.;
        }
    } else { /* (d==3) */
        if      (VABS( x[0] - 0.0 ) < VSMALL) value = - A*u_x0+C*u;
        else if (VABS( x[0] - 1.0 ) < VSMALL) value =   A*u_x0+C*u;
        else if (VABS( x[1] - 0.0 ) < VSMALL) value = - A*u_x1+C*u;
        else if (VABS( x[1] - 1.0 ) < VSMALL) value =   A*u_x1+C*u;
        else if (VABS( x[2] - 0.0 ) < VSMALL) value = - A*u_x2+C*u;
        else if (VABS( x[2] - 1.0 ) < VSMALL) value =   A*u_x2+C*u;
        else {
            /* Vnm_print(2, "my_GN: there is some problem...\n"); */
            /* Vnm_print(2, "my_GN: x=(%e,%e,%e)\n", x[0], x[1], x[2]); */
            value = 0.;
        }
    }
    return value;
}
VPRIVATE double my_US(int d, int m, double *x) {
    return FAC(d,m,x) * UU(d,m,x);
}

/* ///////////////////////////////////////////////////////////////////////////
// Local data
/////////////////////////////////////////////////////////////////////////// */

VPRIVATE double xq[3], nvec[3], vx[4][3], U[MAXV], dU[MAXV][3];

VPRIVATE double A, B, DB, C, GN, DN[3];
VPRIVATE int sType, fType;

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  initAssemble
//
// Purpose:  Do once-per-assembly initialization.
//
// Input:    PDE = pointer to the PDE object
//           ip  = integer parameters for the assembly
//           rp  = real parameters for the assembly
//
// Output:   None
//
// Speed:    This function is called by MC just before a full assembly,
//           and does not have to be particularly fast.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void initAssemble(PDE *thee, int ip[], double rp[])
{
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  initElement
//
// Purpose:  Do once-per-element initialization.
//
// Input:    PDE         = pointer to the PDE object
//           elementType = type of this element (various material types)
//           chart       = chart in which vertex coordinates are provided
//           tvx[][3]    = coordinates of all the vertices of the element
//
// Output:   None
//
// Speed:    This function is called by MC just before assembling a single
//           element, and needs to be a fast as possible.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void initElement(PDE *thee, int elementType,
    int chart, double tvx[][3], void *data)
{
    int i, j;

    /* vertex locations of this simplex */
    for (i=0; i<thee->dim+1; i++)
        for (j=0; j<thee->dim; j++)
            vx[i][j] = tvx[i][j];

    /* save the element type */
    sType = elementType;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  initFace
//
// Purpose:  Do once-per-face initialization.
//
// Input:    PDE      = pointer to the PDE object
//           faceType = type of this face (interior or various boundary types)
//           chart    = chart in which normal vector coordinates are provided
//           tnvec[]  = coordinates of the outward normal vector to this face
//
// Output:   None
//
// Speed:    This function is called by MC just before assembling a single
//           element face, and needs to be a fast as possible.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void initFace(PDE *thee, int faceType,
    int chart, double tnvec[])
{
    int i;

    /* unit normal vector of this face */
    for (i=0; i<thee->dim; i++)
        nvec[i] = tnvec[i];

    /* save the face type */
    fType = faceType;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  initPoint
//
// Purpose:  Do once-per-point initialization.
//
// Input:    PDE       = pointer to the PDE object
//           pointType = type of this point (interior or boundary)
//           chart     = chart in which the point coordinates are provided
//           txq[]     = coordinates of the point
//           tU[]      = current solution at the point
//           tdU[]     = current solution gradient at the point
//
// Output:   None
//
// Speed:    This function is called by MC for every quadrature point
//           during an assmebly, and needs to be a fast as possible.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void initPoint(PDE *thee, int pointType,
    int chart, double txq[],
    double tU[], double tdU[][3])
{
    int i, j;

    /* the point, and the solution value and gradient at the point */
    for (i=0; i<thee->vec; i++) {
        U[i] = tU[i];
        for (j=0; j<thee->dim; j++) {
            if (i==0) xq[j] = txq[j];
            dU[i][j] = tdU[i][j];
        }
    }

    /* interior form case */
    if (pointType == 0) {

        A = my_A(thee->dim, thee->vec, xq);
        my_D(thee->dim, thee->vec, xq, DN);
        B = my_B(thee->dim, thee->vec, A, DN, xq, U);
        DB = my_DB(thee->dim, thee->vec, xq, U);

    /* boundary form case */
    } else { /* (pointType == 1) */

        A = my_A(thee->dim, thee->vec, xq);
        C = my_C(thee->dim, thee->vec, xq);
        GN = my_GN(thee->dim, thee->vec, A, C, xq);

    }
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Fu
//
// Purpose:  Evaluate the strong form of the differential operator F(u)
//           at the single point x.  This is your nonlinear strong form:
//              
//            [   b(u)^i - a(u)^{iq}_{~;q},   if t = 0
//     F(u) = [   c(u)^i + a(u)^{iq} n_q,     if t = 1
//            [   0      + a(u)^{iq} n_q,     if t = 2
//
// Input:    PDE   = pointer to the PDE object
//           key   = piece to evaluate (0=interior, 1=boundary, 2=int-bndry)
//
// Output:   F[]   = operator piece evaluated at the point given to initPoint
//
// Speed:    This function is called by MC only when using error
//           estimation based on strong residuals.  The speed of this
//           function will impact the speed of the error estimator.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Fu(PDE *thee, int key, double F[])
{
    int j;

    /* element residual case */
    if (key == 0) {
        F[0] = 0.;

    /* neumann face residual case */
    } else if (key == 1) {
        F[0] = C * U[0] - GN;
        for (j=0; j<thee->dim; j++)
            F[0] += dU[0][j] * nvec[j];

    /* interior face residual case */
    } else { /* (key == 2) */
        F[0] = 0.;
        for (j=0; j<thee->dim; j++)
            F[0] += dU[0][j] * nvec[j];
    }
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Ju
//
// Purpose:  Evaluate the integrand J_k(u) of the energy functional J(u)
//           at the single point x.  This is your nonlinear energy
//           functional for which your weak form PDE below in Fu_v() is the
//           Euler condition.  (There may not be such a J(u) in all cases.)
//
//            /\              /\
//     J(u) = \  J_0(u) dx +  \  J_1(u) ds
//           \/m             \/dm
//
// Input:    PDE   = pointer to the PDE object
//           key   = integrand to evaluate (0=J_0, 1=J_1)
//
// Output:   Value of the integrand is returned
//
// Speed:    This function is called by MC once times for a single
//           quadrature point during assembly, and needs to be fast.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC double Ju(PDE *thee, int key)
{
    double value = 0.;

    /* interior form case */
    if (key == 0) {
        value = 0.;

    /* boundary form case */
    } else if (key == 1) {
        value = 0.;

    } else { VASSERT(0); }

    return value;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Fu_v
//
// Purpose:  Evaluate the integrand F(u)(v) of the functional <F(u),v>
//           at the single point x.  This is your nonlinear weak form:
//
//                /\                 /\
//     <F(u),v> = \  F_0(u)(v) dx +  \  F_1(u)(v) ds
//               \/m                \/dm
//
//                /\
//              = \  g_{ij} ( a(u)^{iq} v^j_{~;q} + b(u)^i v^j ) dx
//               \/m
//
//                /\
//              + \  g_{ij} c(u)^i v^j ds
//               \/dm
//
//           or the data for the linearized adjoint (dual) problem:
//
//                          /\              /\
//     <F(u),v> = <psi,v> = \  F_2(v) dx +  \  F_3(v) ds
//                         \/m             \/dm
//
// Input:    PDE   = pointer to the PDE object
//           key   = integrand to evaluate (0=F_0, 1=F_1, 2=F_2, 3=F_3)
//           tV[]  = test function at the current point
//           tdV[] = test function gradient at the current point
//
// Output:   Value of the integrand is returned
//
// Speed:    This function is called by MC multiple times for a single
//           quadrature point during assembly, and needs to be a fast
//           as possible.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC double Fu_v(PDE *thee, int key,
    double V[], double dV[][3])
{
    int i;
    double value = 0.;

    /* interior form case */
    if (key == 0) {
        value = B * V[0];
        for (i=0; i<thee->dim; i++)
            value += ( A * dU[0][i] * dV[0][i] + DN[i] * dU[0][i] * V[0] );

    /* boundary form case */
    } else if (key == 1) {
        value = (C * U[0] - GN) * V[0];

    /* DUAL: interior form case */
    } else if (key == 2) {
        value = 0.0;

    /* DUAL: boundary form case */
    } else if (key == 3) {
        value = 0.0;

    } else { VASSERT(0); }

    return value;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  DFu_wv
//
// Purpose:  Evaluate the integrand DF(u)(w,v) of the functional <DF(u)w,v>
//           at the single point x.  This is your bilinear weak form:
//
//                  /\                    /\
//     <DF(u)w,v> = \  DF_0(u)(w,v) dx +  \  DF_1(u)(w,v) ds
//                 \/m                   \/dm
//
//                  /\
//                = \  d/dt F_0(u+tw)(v)|_{t=0} dx
//                 \/m
//
//                  /\
//                + \  d/dt F_1(u+tw)(v)|_{t=0} ds
//                 \/dm
//
//           or the bilinear weak form for the linearized dual problem:
//
//                                /\                    /\
//     <DF(u)w,v> = <A(u)^Tw,v> = \  DF_2(u)(w,v) dx +  \  DF_3(u)(w,v) ds
//                               \/m                   \/dm
//
// Input:    PDE   = pointer to the PDE object
//           key   = integrand to evaluate (0=DF_0, 1=DF_1, 2=DF_2, 3=DF_3)
//           tW[]  = trial function at the current point
//           tdW[] = trial function gradient at the current point
//           tV[]  = test function at the current point
//           tdV[] = test function gradient at the current point
//
// Output:   Value of the integrand is returned
//
// Speed:    This function is called by MC multiple times for a single
//           quadrature point during assembly, and needs to be a fast
//           as possible.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC double DFu_wv(PDE *thee, int key,
    double W[], double dW[][3],
    double V[], double dV[][3])
{
    int i;
    double value = 0.;

    /* interior form case */
    if (key == 0) {
        value = DB * W[0] * V[0];
        for (i=0; i<thee->dim; i++)
            value += ( A * dW[0][i] * dV[0][i] + DN[i] * dW[0][i] * V[0] );

    /* boundary form case */
    } else if (key == 1) {
        value = C * W[0] * V[0];

    /* DUAL: interior form case */
    } else if (key == 2) {
        value = 0.0;

    /* DUAL: boundary form case */
    } else if (key == 3) {
        value = 0.0;

    } else { VASSERT(0); }

    return value;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  p_wv
//
// Purpose:  Evaluate the integrand p(w,v) of the functional <p w,v> at
//           the single point x.  This is your bilinear mass form:
//
//               /\             /\
//     <p w,v> = \  p(w,v) dx = \  p(x) w(x) v(x) dx
//              \/m            \/m
//
// Input:    PDE   = pointer to the PDE object
//           key   = integrand to evaluate (0=p(w,v), 1=0)
//           tW[]  = trial function at the current point
//           tV[]  = test function at the current point
//
// Output:   Value of the integrand is returned
//
// Speed:    This function is called by MC one time for a single
//           quadrature point during assembly, and needs to be as fast
//           as possible.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC double p_wv(PDE *thee, int key, double W[], double V[])
{
    double value = 0.;

    /* interior form case */
    if (key == 0) {
        value = W[0] * V[0];

    /* boundary form case */
    } else if (key == 1) {
        value = 0.0;

    /* DUAL: interior form case */
    } else if (key == 2) {
        value = 0.0;

    /* DUAL: boundary form case */
    } else if (key == 3) {
        value = 0.0;

    } else { VASSERT(0); }

    return value;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  delta
//
// Purpose:  At the single given point x, evaluate a delta function
//           source term (if one is present): delta = g(x).
//
// Input:    PDE   = pointer to the PDE object
//           chart = chart in which the point coordinates are provided
//           txq[] = coordinates of the point
//
// Output:   F[]   = resulting function values
//
// Speed:    This function is called by MC once for each node in the mesh,
//           just after a full element-wise assembly, so it should be fast.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void delta(PDE *thee, int type,
    int chart, double txq[], void *data,
    double F[])
{
    F[0] = 0;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  u_D
//
// Purpose:  At the single given point x, evaluate the dirichlet boundary
//           function: u_D = g(x).
//
// Input:    PDE   = pointer to the PDE object
//           chart = chart in which the point coordinates are provided
//           txq[] = coordinates of the point
//
// Output:   F[]   = resulting function values
//
// Speed:    This function is called by MC just before a full assembly,
//           and does not have to be particularly fast.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void u_D(PDE *thee, int type,
    int chart, double txq[], double F[])
{
    F[0] = my_US(thee->dim, thee->vec, txq);
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  u_T
//
// Purpose:  At the single given point x, evaluate the true solution
//           function (if you have one for your problem): u_T = u(x).
//
// Input:    PDE   = pointer to the PDE object
//           chart = chart in which the point coordinates are provided
//           txq[] = coordinates of the point
//
// Output:   F[]   = resulting function values
//
// Speed:    This function is called by MC just before a full assembly,
//           and does not have to be particularly fast.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void u_T(PDE *thee, int type,
    int chart, double txq[], double F[], double dF[][3])
{
    F[0] = my_US(thee->dim, thee->vec, txq);
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  bisectEdge
//
// Purpose:  Define the way manifold edges are bisected.
//
// Input:    The input parameters have the following interpretations:
//
//               dim                  = intrinsic dimension of the manifold
//               dimII                = imbedding dimension of the manifold
//               edgeType             = edge type being refined
//               chart[0]             = manifold chart for 0th vertex of edge
//               chart[1]             = manifold chart for 1st vertex of edge
//               vx[0][0,...,dimII-1] = 1st vertex coordinates w.r.t. chart[0]
//               vx[1][0,...,dimII-1] = 2nd vertex coordinates w.r.t. chart[1]
//
// Output:   The output parameters have the following interpretations:
//
//               chart[2]             = manifold chart for NEW 3rd vertex
//               vx[2][0,...,dimII-1] = 3rd vertex coordinates w.r.t. chart[2]
//
// Speed:    This function is called by MC every time an edge must be
//           bisected for simplex refinement, and needs to be as fast as
//           possible.
//
// Notes:    The chart numbers are the charts you associated with your
//           vertices in your input manifold.  If the coordinates of the two
//           vertices of the edge had been given w.r.t. different charts, then
//           you need to call your "oneChart" routine to produce a single
//           chart to represent both vertices for the bisection, and then pass
//           back both the coordinates of the new bisection point and the
//           associated chart number.  The idea is that other than your
//           initial chart assignment you made in your input manifold
//           specification, the oneChart function that you provide along with
//           this bisectEdge function is the only place where coordinate
//           transformations occur, and they are entirely under your control.
//           
//           For a non-flat Riemannian 2- or 3-manifold, you should be
//           producing something as close as possible to the bisection of a
//           geodesic on your manifold, with the distance to the midpoint
//           measured using the Riemannian metric for your manifold.  If you
//           can do this, then the bisection of every generalized simplex on
//           the manifold by longest "geodesic" is guaranteed to remain
//           non-degenerate (in the metric measure).  This is a simple
//           extension of the planar result to a Riemannian manifold.  In the
//           case of a 3-manifold, it is open whether this produces
//           non-degenerate generalized simplices (because it is still an open
//           question for bisection of tetrahedra in R^3 by their longest
//           edge), but emperically it appears to be non-degenerate.
//
// Example:  In the simple case of a single orthogonal cartesian coordinate 
//           system in R^2 or R^3, the bisection should be simply the midpoint
//           of the edge as follows:
//
//               Input parameters (set by MC before the call):
//
//                   dim                  = d;
//                   dimII                = d;
//                   edgeType             = (determined from face types you
//                                           specified in input manfold)
//                   chart                = 0;
//                   vx[0][0,...,dimII-1] = (coordinates of vx[0] w.r.t. chart)
//                   vx[1][0,...,dimII-1] = (coordinates of vx[1] w.r.t. chart)
//
//               bisectEdge rule:
//
//                   for (i=0; i<dimII; i++)
//                       vx[2][i] = .5 * ( vx[0][i] + vx[1][i] );
//
//               Output parameters:
//
//                   vx[2][0,...,dimII] = (coordinates of vx[2] w.r.t. chart)
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void bisectEdge(int dim, int dimII,
    int edgeType, int chart[], double vx[][3])
{
    int i;
    for (i=0; i<dimII; i++)
        vx[2][i] = .5 * (vx[0][i] + vx[1][i]);
}
VPUBLIC void mapBoundary(int dim, int dimII,
    int vertexType, int chart, double vx[3])
{
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  markSimplex
//
// Purpose:  User-provided error estimator which allows the user to define
//           his own refinement strategies rather than using the builtin
//           a posteriori error estimators.
//
// Input:    The input parameters have the following interpretations:
//
//               dim                  = intrinsic dimension of the manifold
//               dimII                = imbedding dimension of the manifold
//               simplexType          = simplex type being refined
//               chart[0,...,d+1]     = manifold charts for all d+1 vertices
//               vx[0][0,...,dimII-1] = vx[0] coordinates w.r.t. chart
//                       ...
//               vx[d][0,...,dimII-1] = vx[d] coordinates w.r.t. chart
//
// Output:   The output parameters have the following interpretations:
//
//               return value         = 0 if the simplex is not to be refined
//                                    = 1 if the simplex is to be refined
//
// Speed:    This function is called by MC for every element during error
//           estimation, if the user-provided error estimator is requested.
//           Therefore, it should be pretty fast or the error estimation
//           phase will be slow.
//
// Notes:    The user can use this routine to define, for example,
//           a completely geometry-based error estimator.
//
// Example:  In the case that the user-provided error estimator is never
//           requested, then this routine can simply return any value.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC int markSimplex(int dim, int dimII,
    int simplexType, int faceType[4], int vertexType[4],
    int chart[], double vx[][3], void *data)
{
    int j, k, less, more;
    double radius, d[4];

    /* radius = radius of a refinement sphere for testing */
    radius = 0.1; /* must be > 0 */
    less = 0;
    more = 0;
    for (j=0; j<dim+1; j++) {
        d[j] = 0.0;
        for (k=0; k<3; k++)
            d[j] += VSQR( vx[j][k] );
        d[j] = VSQRT( d[j] );
        if (d[j] <= radius+VSMALL) less = 1;
        else more = 1;
    }

    /* return true if simplex touches or stradles surface of sphere */
    return ( less && more );
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  oneChart
//
// Purpose:  Select a single unified chart for a set of two or more vertices
//           whose coordinates may be given with respect to different charts.
//           Then transform all of the coordinates of the vertex set to be
//           with respect to the single selected "unified" chart.
//
// Input:    The input parameters have the following interpretations:
//
//               dim     = intrinsic dimension of the manifold
//               dimII   = imbedding dimension of the manifold
//               dimV    = number of vertices in the simplex
//                           dimV=1 ==> v is a single vertex
//                           dimV=2 ==> v is part of an edge
//                           dimV=3 ==> v is part of a triangle (or face)
//                           dimV=4 ==> v is part of a tetrahedron
//               objType = object type of the simplex
//                   dimV=1:
//                       type=?        ==> any interpretation
//                   dimV=2:
//                       type=0        ==> object is an interior edge
//                       type>0 & ODD  ==> object is a dirichlet edge
//                       type>0 & EVEN ==> object is a neumann edge
//                   dimV=3:
//                       dim=2
//                           type=anything ==> material type of triangle
//                       dim=3
//                           type=0        ==> object is an interior face
//                           type>0 & ODD  ==> object is a dirichlet face
//                           type>0 & EVEN ==> object is a neumann face
//                   dimV=4:
//                       type=anything ==> material type of tetrahedron
//               chart[] = current manifold chart numbers for input vertices
//               vx[][3] = original vertex coordinates w.r.t. charts in chart[]
//
// Output:   The output parameters have the following interpretations:
//
//               chart[] = selected (unified) output charts (all the same)
//               vx[][3] = new vertex coordinates w.r.t. new unified char
//
// Speed:    This function is called by MC whenever it encounters an element
//           with vertices having coordinates in different charts.  If you
//           many charts and thus many elements which stradle chart
//           boundaries, then you will want to make this as fast as possible.
//
// Notes:    In this routine, you define how to move from one chart to
//           another, which means you implicitly define how to change
//           coordinate systems.  The code allows the user to select the
//           appropriate chart for the vertices of an object in order to give
//           the user maximal control over how he uses coordinate systems to
//           represent a manifold.
//
//           The caller gives the user a set of vertex coordinates for two or
//           more vertices that are a part of some simplex (edge, triangle,
//           or tet).  The vertex coordinates may be given with respect to
//           different charts if the simplex happens to stradle two charts.
//
//           Our job is to select the most appropriate chart based on the
//           simplex class (edge, tri, or tet) and the simplex type (interior
//           or boundary for edges, or triangular boundary faces, or some
//           material type for triangles or tets), and then transform all
//           of the vertex coordinates to the single coordinate system
//           you have selected.  You then pass back the chart number that you
//           have selected, along with the new coordinates.
//
// Example:  In the simple case of a single chart covering the manifold,
//           this routine can simply return without modifying either
//           chart or vx.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void oneChart(int dim, int dimII, int objType,
    int chart[], double vx[][3], int dimV)
{
    VASSERT( (2 <= dim)   && (dim   <= 3) );
    VASSERT( (2 <= dimII) && (dimII <= 3) );
    VASSERT( (1 <= dimV)  && (dimV  <= 4) );
    VASSERT( (0 <= objType) );
}

/* ///////////////////////////////////////////////////////////////////////////
// Class PDE: Inlineable methods
/////////////////////////////////////////////////////////////////////////// */
#if !defined(VINLINE_PDE)
#endif /* if !defined(VINLINE_PDE) */

/* ///////////////////////////////////////////////////////////////////////////
// Class PDE: Non-inlineable methods
/////////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  PDE_ctor
//
// Purpose:  Construct the differential equation object.
//
// Speed:    This function is called by MC one time during setup,
//           and does not have to be particularly fast.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC PDE* myPDE_ctor(void)
{
    int i;
    PDE *thee = VNULL;

    /* create some space for the pde object */
    thee = Vmem_malloc( VNULL, 1, sizeof(PDE) );

    /* PDE-specific parameters and function pointers */
    thee->initAssemble = initAssemble;  /* once-per-assembly initialization */
    thee->initElement  = initElement;   /* once-per-element initialization  */
    thee->initFace     = initFace;      /* once-per-face initialization     */
    thee->initPoint    = initPoint;     /* once-per-point initialization    */
    thee->Fu           = Fu;            /* nonlinear strong form            */
    thee->Ju           = Ju;            /* nonlinear energy functional      */
    thee->Fu_v         = Fu_v;          /* nonlinear weak form              */
    thee->DFu_wv       = DFu_wv;        /* bilinear linearization weak form */
    thee->p_wv         = p_wv;          /* bilinear mass density form       */
    thee->delta        = delta;         /* delta function source term       */
    thee->u_D          = u_D;           /* dirichlet func and initial guess */
    thee->u_T          = u_T;           /* analytical soln for testing      */
    thee->vec          = 1;             /* unknowns per spatial point;      */
    thee->sym[0][0]    = 0;             /* symmetries of bilinear form      */
    thee->est[0]       = 1.0;           /* error estimator weights          */
    for (i=0; i<VMAX_BDTYPE; i++)       /* boundary type remappings         */
        thee->bmap[0][i] = i;

    /* Manifold-specific function pointers */
    thee->bisectEdge  = bisectEdge;  /* edge bisection rule                 */
    thee->mapBoundary = mapBoundary; /* boundary recovery rule              */
    thee->markSimplex = markSimplex; /* simplex marking rule                */
    thee->oneChart    = oneChart;    /* coordinate transformations          */

    /* Element-specific function pointers */
    thee->simplexBasisInit = simplexBasisInit; /* initialization of bases   */
    thee->simplexBasisForm = simplexBasisForm; /* form trial & test bases   */

    /* return the new pde object */
    return thee;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  PDE_dtor
//
// Purpose:  Destroy the differential equation object.
//
// Speed:    This function is called by MC one time during shutdown,
//           and does not have to be particularly fast.
//
// Author:   Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void myPDE_dtor(PDE **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        Vmem_free( VNULL, 1, sizeof(PDE), (void**)thee );

        (*thee) = VNULL;
    }
}

