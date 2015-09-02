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
 * rcsid="$Id: re.c,v 1.18 2010/08/12 05:18:20 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     Re.c
 *
 * Purpose:  Class Re: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "re_p.h"

VEMBED(rcsid="$Id: re.c,v 1.18 2010/08/12 05:18:20 fetk Exp $")

VPRIVATE void init_2DP1(Re *thee);
VPRIVATE void init_2DP2(Re *thee);
VPRIVATE void init_3DP1(Re *thee);
VPRIVATE void init_3DP2(Re *thee);
VPRIVATE void init_3DFB(Re *thee);
VPRIVATE void setQP2D(Re *thee);
VPRIVATE void setQP3D(Re *thee);

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
VPRIVATE int dim_1DP1 = 2;
VPRIVATE int dim_1DP2 = 3;
VPRIVATE int dim_2DP1 = 3;
VPRIVATE int lgr_2DP1[3][VMAXP] = {
/*c0  c1  c2  c3  ---------------------------------------------------------- */
/* 1   x   y   z  ---------------------------------------------------------- */
{  2, -2, -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DP1x[3][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DP1y[3][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DP1z[3][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};

/*
 * ***************************************************************************
 * 2D-P2 Basis:
 *
 *     p1(x,y) = c0 + c1*x + c2*y + c4*x*x + c5*y*y + c7*x*y
 *
 *     Lagrange Point    Lagrange Basis Function Definition
 *     --------------    ----------------------------------
 *     (0, 0)            p[0](x,y) = q*(2*q - 1)
 *     (1, 0)            p[1](x,y) = x*(2*x - 1)
 *     (0, 1)            p[2](x,y) = y*(2*y - 1)
 *     (1/2, 1/2)        p[3](x,y) = 4*x*y
 *     (0, 1/2)          p[4](x,y) = 4*q*y
 *     (1/2, 0)          p[5](x,y) = 4*q*x
 *
 *     where q = 1 - x - y
 *
 * ***************************************************************************
 */
VPRIVATE int dim_2DP2 = 6;
VPRIVATE int lgr_2DP2[6][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  ------------------------------------------ */
/* 1   x   y   z  x*x y*y z*z x*y ------------------------------------------ */
{  2, -6, -6,  0,  4,  4,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0, -2,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0, -2,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  8,  0,  0, -8,  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  8,  0,  0, -8,  0,  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DP2x[6][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -6,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{ -2,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  8,-16, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DP2y[6][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -6,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{ -2,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  8, -8,-16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DP2z[6][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
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
{  2, -2, -2, -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_3DP1x[4][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_3DP1y[4][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_3DP1z[4][VMAXP] = {
/*c0  ---------------------------------------------------------------------- */
/* 1  ---------------------------------------------------------------------- */
{ -2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
};

/*
 * ***************************************************************************
 * 3D-P2 Basis:
 *
 *     p1(x,y) = c0 + c1*x + c2*y + c3*z + 
 *                  + c4*x*x + c5*y*y + c6*z*z +
 *                  + c7*x*y + c8*x*z + c9*y*z
 *
 *     Lagrange Point    Lagrange Basis Function Definition
 *     --------------    ----------------------------------
 *     (0, 0, 0)         p[0](x,y,z) = q*(2*q - 1)
 *     (1, 0, 0)         p[1](x,y,z) = x*(2*x - 1)
 *     (0, 1, 0)         p[2](x,y,z) = y*(2*y - 1)
 *     (0, 0, 1)         p[3](x,y,z) = z*(2*z - 1)
 *     (1/2, 1/2, 0)     p[4](x,y,z) = 4*x*y
 *     (0, 1/2, 0)       p[5](x,y,z) = 4*q*y
 *     (1/2, 0, 0)       p[6](x,y,z) = 4*q*x
 *     (0, 0, 1/2)       p[7](x,y,z) = 4*q*z 
 *     (1/2, 0, 1/2)     p[8](x,y,z) = 4*x*z
 *     (0, 1/2, 1/2)     p[9](x,y,z) = 4*y*z
 *
 *     where q = 1 - x - y - z
 *
 * ***************************************************************************
 */
VPRIVATE int dim_3DP2 = 10;
VPRIVATE int lgr_3DP2[10][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9  ---------------------------------- */
/* 1   x   y   z  x*x y*y z*z x*y x*z y*z ---------------------------------- */
{  2, -6, -6, -6,  4,  4,  4,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0, -2,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0, -2,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0, -2,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  8,  0,  0, -8,  0, -8,  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  8,  0,  0, -8,  0,  0, -8, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  8,  0,  0, -8,  0, -8, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } 
};
VPRIVATE int lgr_3DP2x[10][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9  ---------------------------------- */
/* 1   x   y   z  x*x y*y z*z x*y x*z y*z ---------------------------------- */
{ -6,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{ -2,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  8,-16, -8, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_3DP2y[10][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9  ---------------------------------- */
/* 1   x   y   z  x*x y*y z*z x*y x*z y*z ---------------------------------- */
{ -6,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{ -2,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  8, -8,-16, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_3DP2z[10][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9  ---------------------------------- */
/* 1   x   y   z  x*x y*y z*z x*y x*z y*z ---------------------------------- */
{ -6,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{ -2,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0, -8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  8, -8, -8,-16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};

/*
 * ***************************************************************************
 * 2D-FB Basis:
 *
 *     p3(x,y) = c0 + c1*x + c2*y + c4*x*x + c5*y*y + c7*x*y
 *                    + c10*x*x*x + c11*y*y*y 
 *                    + c13*x*x*y + c15*x*y*y
 *
 *     Lagrange Point    Lagrange Basis Function Definition
 *     --------------    ----------------------------------
 *     (1/3, 1/3)     p[3](x,y,z) = 9*q*x*y
 *
 *     where q = 1 - x - y
 *
 * ***************************************************************************
 */
VPRIVATE int dim_2DFB = 1;
VPRIVATE int lgr_2DFB[1][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9 c10 c11 c12 c13 c14 c15 c16 c17 c18 c19 */
/* 1   x   y   z  xx  yy  zz  xy  xz  yz xxx yyy zzz xxy xxz xyy yyz xzz yzz xyz */
{  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,-18,  0,-18,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DFBx[1][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9 c10 c11 c12 c13 c14 c15 c16 c17 c18 c19 */
/* 1   x   y   z  xx  yy  zz  xy  xz  yz xxx yyy zzz xxy xxz xyy yyz xzz yzz xyz */
{  0,  0, 18,  0,  0,-18,  0,-36,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_2DFBy[1][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9 c10 c11 c12 c13 c14 c15 c16 c17 c18 c19 */
/* 1   x   y   z  xx  yy  zz  xy  xz  yz xxx yyy zzz xxy xxz xyy yyz xzz yzz xyz */
{  0, 18,  0,  0,-18,  0,  0,-36,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};

/*
 * ***************************************************************************
 * 3D-FB Basis:
 *
 *     p3(x,y,z) = c0 + c1*x + c2*y + c3*z
 *                    + c4*x*x + c5*y*y + c6*z*z + c7*x*y + c8*x*z + c9*y*z
 *                    + c10*x*x*x + c11*y*y*y + c12*z*z*z
 *                    + c13*x*x*y + c14*x*x*z + c15*x*y*y
 *                    + c16*y*y*z + c17*x*z*z + c18*y*z*z
 *                    + c19*x*y*z
 *
 *     Lagrange Point    Lagrange Basis Function Definition
 *     --------------    ----------------------------------
 *     (1/3, 1/3, 1/3)   p[0](x,y,z) = 9*x*y*z
 *     (0, 1/3, 1/3)     p[1](x,y,z) = 9*q*y*z
 *     (1/3, 0, 1/3)     p[2](x,y,z) = 9*q*x*z
 *     (1/3, 1/3, 0)     p[3](x,y,z) = 9*q*x*y
 *
 *     where q = 1 - x - y - z
 *
 * ***************************************************************************
 */
VPRIVATE int dim_3DFB = 4;
VPRIVATE int lgr_3DFB[4][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9 c10 c11 c12 c13 c14 c15 c16 c17 c18 c19 */
/* 1   x   y   z  xx  yy  zz  xy  xz  yz xxx yyy zzz xxy xxz xyy yyz xzz yzz xyz */
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,  0,-18,  0,-18,-18 },
{  0,  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,-18,  0,  0,-18,  0,-18 },
{  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,-18,  0,-18,  0,  0,  0,-18 }
};
VPRIVATE int lgr_3DFBx[4][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9 c10 c11 c12 c13 c14 c15 c16 c17 c18 c19 */
/* 1   x   y   z  xx  yy  zz  xy  xz  yz xxx yyy zzz xxy xxz xyy yyz xzz yzz xyz */
{  0,  0,  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,  0,-18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0, 18,  0,  0,-18,  0,-36,-18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0, 18,  0,  0,-18,  0,-36,  0,-18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_3DFBy[4][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9 c10 c11 c12 c13 c14 c15 c16 c17 c18 c19 */
/* 1   x   y   z  xx  yy  zz  xy  xz  yz xxx yyy zzz xxy xxz xyy yyz xzz yzz xyz */
{  0,  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0, 18,  0,  0,-18,  0,-18,-36,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,  0,-18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0, 18,  0,  0,-18,  0,  0,-36,-18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};
VPRIVATE int lgr_3DFBz[4][VMAXP] = {
/*c0  c1  c2  c3  c4  c5  c6  c7  c8  c9 c10 c11 c12 c13 c14 c15 c16 c17 c18 c19 */
/* 1   x   y   z  xx  yy  zz  xy  xz  yz xxx yyy zzz xxy xxz xyy yyz xzz yzz xyz */
{  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0, 18,  0,  0,-18,  0,-18,  0,-36,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0, 18,  0,  0,-18,  0,  0,-18,-36,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
{  0,  0,  0,  0,  0,  0,  0,-18,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
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
 *                       + c19*x*y*z
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
             + c[i][18] * y*z*z
             + c[i][19] * x*y*z;
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

#if 0
VPRIVATE void setCoef(Re *thee,
    int c[][VMAXP],
    int cx[][VMAXP], int cy[][VMAXP], int cz[][VMAXP])
{
    int i, j;
    for (i=0; i<thee->numP; i++) {
        for (j=0; j<VMAXP; j++) {
            thee->c[i][j]  = 0.5 * (double)c[i][j];
            thee->cx[i][j] = 0.5 * (double)cx[i][j];
            thee->cy[i][j] = 0.5 * (double)cy[i][j];
            thee->cz[i][j] = 0.5 * (double)cz[i][j];
        }
    }
}
#endif

/*
 * ***************************************************************************
 * Class Re: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_APRX)
#endif /* if !defined(VINLINE_APRX) */

/*
 * ***************************************************************************
 * Class Re: Non-inlineable methods
 * ***************************************************************************
 */

VPUBLIC Re* Re_ctor(int key, int dim,
    int (*simplexBasisInit)(int key, int dim, int comp,
        int *ndof, int dof[]),
    void (*simplexBasisForm)(int key, int dim, int comp,
        int pdkey, double xq[], double basis[]), int qorder) 
{
    /* key == 0 -> non-bump functions */
    /* key != 0 -> bump functions */
    /* Right now, only dim == 3, qorder == 3 is implemented for bump functions. */
    int bump;

    Re *thee = VNULL;

    thee = Vmem_malloc( VNULL, 1, sizeof(Re) );

    thee->dim = dim;
    thee->simplexBasisInit = simplexBasisInit;
    thee->simplexBasisForm = simplexBasisForm;

    if (key == 0) {
        Vnm_print(0,"Re_ctor: constructing %dD master element..",
            thee->dim);
    } else if (key == 1) {
        Vnm_print(0,"Re_ctor: constructing %dD master bump element..",
            thee->dim);
    } else { VASSERT(0); }

    if (key == 0) bump = 0;
    else bump = 1;

    if (thee->dim==2) {
        /* simplex information */
        thee->dimIS[0] = 3;
        thee->dimIS[1] = 3;
        thee->dimIS[2] = 1;
        thee->dimIS[3] = 0;
        /* element information */
        if (bump==0) {
            if (qorder==1) {
                init_2DP1(thee); 
            } else if (qorder==2) {
                init_2DP2(thee);
            } else Vnm_print(2, "..bad qorder..");
        } else if (bump==1) {
            Vnm_print(2, "..bad bump..");
        } else Vnm_print(2, "..bad bump..");
    } else if (thee->dim==3) {
        /* simplex information */
        thee->dimIS[0] = 4;
        thee->dimIS[1] = 6;
        thee->dimIS[2] = 4;
        thee->dimIS[3] = 1;
        /* element information */
        if (bump==0) {
            if (qorder==1) {
                init_3DP1(thee); 
            } else if (qorder==2) {
                init_3DP2(thee);
            } else Vnm_print(2, "..bad qorder..");
        } else if (bump==1) {
            if (qorder==3) {
                init_3DFB(thee); 
            } else Vnm_print(2, "..bad bump..");
        } else Vnm_print(2, "..bad bump..");
    } else {
        Vnm_print(0, "..ignored (safely skipping).");
    }

    Vnm_print(0,"..done.\n");

    return thee;
}

VPUBLIC void Re_dtor(Re **thee)
{
    if ((*thee) != VNULL) {

        VDEBUGIO("Re_dtor: DESTROYING object..");
        Vmem_free( VNULL, 1, sizeof(Re), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

VPUBLIC int Re_dim(Re *thee)
{
    return thee->dim;
}
VPUBLIC int Re_dimV(Re *thee)
{
    return thee->dimIS[0];
}
VPUBLIC int Re_dimE(Re *thee)
{
    return thee->dimIS[1];
}
VPUBLIC int Re_dimF(Re *thee)
{
    return thee->dimIS[2];
}
VPUBLIC int Re_dimS(Re *thee)
{
    return thee->dimIS[3];
}

VPUBLIC int Re_numVDF(Re *thee)
{
    return thee->numDF[0];
}
VPUBLIC int Re_numEDF(Re *thee)
{
    return thee->numDF[1];
}
VPUBLIC int Re_numFDF(Re *thee)
{
    return thee->numDF[2];
}
VPUBLIC int Re_numSDF(Re *thee)
{
    return thee->numDF[3];
}

VPUBLIC int Re_qorder(Re *thee)
{
    return thee->qorder;
}
VPUBLIC int Re_numP(Re *thee, int f)
{
    if (f<0) return thee->numP;
    else     return thee->numPS;
}
VPUBLIC int Re_numQ(Re *thee, int f)
{
    if (f<0) return thee->q;
    else     return thee->qs;
}
VPUBLIC int Re_numQ_hi(Re *thee, int f)
{
    if (f<0) return thee->qhi;
    else     return thee->qshi;
}
VPUBLIC double Re_w(Re *thee, int m, int f)
{
    if (f<0) return thee->v[m].w;
    else     return thee->s[m][f].w;
}
VPUBLIC double Re_w_hi(Re *thee, int m, int f)
{
    if (f<0) return thee->vhi[m].w;
    else     return thee->shi[m][f].w;
}
VPUBLIC double Re_x(Re *thee, int m, int i, int f)
{
    if (f<0) return thee->v[m].x[i];
    else     return thee->s[m][f].x[i];
}
VPUBLIC double Re_x_hi(Re *thee, int m, int i, int f)
{
    if (f<0) return thee->vhi[m].x[i];
    else     return thee->shi[m][f].x[i];
}
VPUBLIC double Re_phi(Re *thee, int m, int i, int f)
{
    if (f<0) return thee->v[m].phi[i];
    else     return thee->s[m][f].phi[i];
}
VPUBLIC double Re_phi_hi(Re *thee, int m, int i, int f)
{
    if (f<0) return thee->vhi[m].phi[i];
    else     return thee->shi[m][f].phi[i];
}
VPUBLIC double Re_phix(Re *thee, int m, int i, int f)
{
    if (f<0) return thee->v[m].phix[i];
    else     return thee->s[m][f].phix[i];
}
VPUBLIC double Re_phix_hi(Re *thee, int m, int i, int f)
{
    if (f<0) return thee->vhi[m].phix[i];
    else     return thee->shi[m][f].phix[i];
}
VPUBLIC double Re_phiy(Re *thee, int m, int i, int f)
{
    if (f<0) return thee->v[m].phiy[i];
    else     return thee->s[m][f].phiy[i];
}
VPUBLIC double Re_phiy_hi(Re *thee, int m, int i, int f)
{
    if (f<0) return thee->vhi[m].phiy[i];
    else     return thee->shi[m][f].phiy[i];
}
VPUBLIC double Re_phiz(Re *thee, int m, int i, int f)
{
    if (f<0) return thee->v[m].phiz[i];
    else     return thee->s[m][f].phiz[i];
}
VPUBLIC double Re_phiz_hi(Re *thee, int m, int i, int f)
{
    if (f<0) return thee->vhi[m].phiz[i];
    else     return thee->shi[m][f].phiz[i];
}
VPUBLIC double Re_phix2(Re *thee, int m, int i, int j, int f)
{
    if (f<0) {
        if      (j==0) return thee->v[m].phix[i];
        else if (j==1) return thee->v[m].phiy[i];
        else if (j==2) return thee->v[m].phiz[i];
        else Vnm_print(2, "Re_phix2: bad argument.\n");
        return 0;
    } else {
        if      (j==0) return thee->s[m][f].phix[i];
        else if (j==1) return thee->s[m][f].phiy[i];
        else if (j==2) return thee->s[m][f].phiz[i];
        else Vnm_print(2, "Re_phix2: bad argument.\n");
        return 0;
    }
}

VPUBLIC double Re_phix2_hi(Re *thee, int m, int i, int j, int f)
{
    if (f<0) {
        if      (j==0) return thee->vhi[m].phix[i];
        else if (j==1) return thee->vhi[m].phiy[i];
        else if (j==2) return thee->vhi[m].phiz[i];
        else Vnm_print(2, "Re_phix2: bad argument.\n");
        return 0;
    } else {
        if      (j==0) return thee->shi[m][f].phix[i];
        else if (j==1) return thee->shi[m][f].phiy[i];
        else if (j==2) return thee->shi[m][f].phiz[i];
        else Vnm_print(2, "Re_phix2: bad argument.\n");
        return 0;
    }
}

VPUBLIC int Re_sqPmt(Re *thee, int pmt, int qp) 
{
    return (thee->spmt[pmt][qp]);    
}

VPUBLIC int Re_sqPmt_hi(Re *thee, int pmt, int qp) 
{
    return (thee->spmthi[pmt][qp]);    
}

VPRIVATE void evalQuadPoint(Re *thee, int iq, int is)
{
    if (is < 0) {
        polyEval(thee->numP, thee->v[iq].phi,  thee->c,  thee->v[iq].x);
        polyEval(thee->numP, thee->v[iq].phix, thee->cx, thee->v[iq].x);
        polyEval(thee->numP, thee->v[iq].phiy, thee->cy, thee->v[iq].x);
        polyEval(thee->numP, thee->v[iq].phiz, thee->cz, thee->v[iq].x);
    } else {
        polyEval(thee->numP, thee->s[iq][is].phi,  thee->c,  thee->s[iq][is].x);
        polyEval(thee->numP, thee->s[iq][is].phix, thee->cx, thee->s[iq][is].x);
        polyEval(thee->numP, thee->s[iq][is].phiy, thee->cy, thee->s[iq][is].x);
        polyEval(thee->numP, thee->s[iq][is].phiz, thee->cz, thee->s[iq][is].x);
    }
}

VPRIVATE void evalQuadPoint_hi(Re *thee, int iq, int is)
{
    if (is < 0) {
        polyEval(thee->numP, thee->vhi[iq].phi,  thee->c,  thee->vhi[iq].x);
        polyEval(thee->numP, thee->vhi[iq].phix, thee->cx, thee->vhi[iq].x);
        polyEval(thee->numP, thee->vhi[iq].phiy, thee->cy, thee->vhi[iq].x);
        polyEval(thee->numP, thee->vhi[iq].phiz, thee->cz, thee->vhi[iq].x);
    } else {
        polyEval(thee->numP,
            thee->shi[iq][is].phi,  thee->c,  thee->shi[iq][is].x);
        polyEval(thee->numP,
            thee->shi[iq][is].phix, thee->cx, thee->shi[iq][is].x);
        polyEval(thee->numP,
            thee->shi[iq][is].phiy, thee->cy, thee->shi[iq][is].x);
        polyEval(thee->numP,
            thee->shi[iq][is].phiz, thee->cz, thee->shi[iq][is].x);
    }
}

VPRIVATE void setQuadPoint(Re *thee, int iq, int is,
    double wq, double xq[])
{
    if (is < 0) {
        thee->v[iq].x[0] = xq[0];
        thee->v[iq].x[1] = xq[1];
        thee->v[iq].x[2] = xq[2];
        thee->v[iq].w    = wq;
        evalQuadPoint(thee,iq,is);
    } else {
        thee->s[iq][is].x[0] = xq[0];
        thee->s[iq][is].x[1] = xq[1];
        thee->s[iq][is].x[2] = xq[2];
        thee->s[iq][is].w    = wq;
        evalQuadPoint(thee,iq,is);
    }
}

VPRIVATE void setQuadPoint_hi(Re *thee, int iq, int is,
    double wq, double xq[])
{
    if (is < 0) {
        thee->vhi[iq].x[0] = xq[0];
        thee->vhi[iq].x[1] = xq[1];
        thee->vhi[iq].x[2] = xq[2];
        thee->vhi[iq].w    = wq;
        evalQuadPoint_hi(thee,iq,is);
    } else {
        thee->shi[iq][is].x[0] = xq[0];
        thee->shi[iq][is].x[1] = xq[1];
        thee->shi[iq][is].x[2] = xq[2];
        thee->shi[iq][is].w    = wq;
        evalQuadPoint_hi(thee,iq,is);
    }
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
VPRIVATE void init_2DP1(Re *thee)
{
    /* locations and number of degrees of freedom */
    thee->numDF[0] = 1;
    thee->numDF[1] = 0;
    thee->numDF[2] = 0;
    thee->numDF[3] = 0;
    thee->numP     = 3 * thee->numDF[0]  /* 3 vertices */
                   + 3 * thee->numDF[1]  /* 3 edges */
                   + 1 * thee->numDF[2]; /* 1 face */
    thee->numPS    = 2 * thee->numDF[0]  /* 2 vertices */
                   + 1 * thee->numDF[1]; /* 1 edge */
    VASSERT( thee->numPS == dim_1DP1 );
    VASSERT( thee->numP == dim_2DP1 );
    VASSERT( thee->numP <= VMAXP );

    /* qorder of polynomials in the element */
    thee->qorder = 1;

    /* define the polynomial coefficients */
    /* setCoef( thee, lgr_2DP1, lgr_2DP1x, lgr_2DP1y, lgr_2DP1z ); */
    setCoef(thee->numP,
        thee->c, thee->cx, thee->cy, thee->cz,
        lgr_2DP1, lgr_2DP1x, lgr_2DP1y, lgr_2DP1z );

    setQP2D(thee);

}

/*
 * ***************************************************************************
 * Routine:  init_2DP2
 *
 * Purpose:  2D quadratic master simplex information generator
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void init_2DP2(Re *thee)
{
    /* locations and number of degrees of freedom */
    thee->numDF[0] = 1;
    thee->numDF[1] = 1;
    thee->numDF[2] = 0;
    thee->numDF[3] = 0;
    thee->numP     = 3 * thee->numDF[0]  /* 3 vertices */
                   + 3 * thee->numDF[1]  /* 3 edges */
                   + 1 * thee->numDF[2]; /* 1 face */
    thee->numPS    = 2 * thee->numDF[0]  /* 2 vertices */
                   + 1 * thee->numDF[1]; /* 1 edge */
    VASSERT( thee->numPS == dim_1DP2 );
    VASSERT( thee->numP == dim_2DP2 );
    VASSERT( thee->numP <= VMAXP );

    /* qorder of polynomials in the element */
    thee->qorder = 2;

    /* define the polynomial coefficients */
    setCoef(thee->numP,
        thee->c, thee->cx, thee->cy, thee->cz,
        lgr_2DP2, lgr_2DP2x, lgr_2DP2y, lgr_2DP2z );

    setQP2D(thee);

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
VPRIVATE void init_3DP1(Re *thee)
{
    /* locations and number of degrees of freedom */
    thee->numDF[0] = 1;
    thee->numDF[1] = 0;
    thee->numDF[2] = 0;
    thee->numDF[3] = 0;
    thee->numP     = 4 * thee->numDF[0]  /* 4 vertices */
                   + 6 * thee->numDF[1]  /* 6 edges */
                   + 4 * thee->numDF[2]  /* 4 faces */
                   + 1 * thee->numDF[3]; /* 1 simplex */
    thee->numPS    = 3 * thee->numDF[0]  /* 3 vertices */
                   + 3 * thee->numDF[1]  /* 3 edges */
                   + 1 * thee->numDF[2]; /* 1 face */
    VASSERT( thee->numPS == dim_2DP1 );
    VASSERT( thee->numP == dim_3DP1 );
    VASSERT( thee->numP <= VMAXP );

    /* qorder of polynomials in the element */
    thee->qorder = 1;

    /* define the polynomial coefficients */
    /* setCoef( thee, lgr_3DP1, lgr_3DP1x, lgr_3DP1y, lgr_3DP1z ); */
    setCoef(thee->numP,
        thee->c, thee->cx, thee->cy, thee->cz,
        lgr_3DP1, lgr_3DP1x, lgr_3DP1y, lgr_3DP1z );

    setQP3D(thee);
}

/*
 * ***************************************************************************
 * Routine:  init_3DP2
 *
 * Purpose:  3D quadratic master simplex information generator
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void init_3DP2(Re *thee)
{
    /* locations and number of degrees of freedom */
    thee->numDF[0] = 1;
    thee->numDF[1] = 1;
    thee->numDF[2] = 0;
    thee->numDF[3] = 0;
    thee->numP     = 4 * thee->numDF[0]  /* 4 vertices */
                   + 6 * thee->numDF[1]  /* 6 edges */
                   + 4 * thee->numDF[2]  /* 4 faces */
                   + 1 * thee->numDF[3]; /* 1 simplex */
    thee->numPS    = 3 * thee->numDF[0]  /* 3 vertices */
                   + 3 * thee->numDF[1]  /* 3 edges */
                   + 1 * thee->numDF[2]; /* 1 face */
    VASSERT( thee->numPS == dim_2DP2 );
    VASSERT( thee->numP == dim_3DP2 );
    VASSERT( thee->numP <= VMAXP );

    /* qorder of polynomials in the element */
    thee->qorder = 2;

    /* define the polynomial coefficients */
    setCoef(thee->numP,
        thee->c, thee->cx, thee->cy, thee->cz,
        lgr_3DP2, lgr_3DP2x, lgr_3DP2y, lgr_3DP2z );

    setQP3D(thee);
}

/*
 * ***************************************************************************
 * Routine:  init_3DFB
 *
 * Purpose:  3D Cubic Face Bump information generator
 *
 * Author:   Ryan Szypowski
 * ***************************************************************************
 */
VPRIVATE void init_3DFB(Re *thee)
{
    /* locations and number of degrees of freedom */
    thee->numDF[0] = 0;
    thee->numDF[1] = 0;
    thee->numDF[2] = 1;
    thee->numDF[3] = 0;
    thee->numP     = 4 * thee->numDF[0]  /* 4 vertices */
                   + 6 * thee->numDF[1]  /* 6 edges */
                   + 4 * thee->numDF[2]  /* 4 faces */
                   + 1 * thee->numDF[3]; /* 1 simplex */
    thee->numPS    = 3 * thee->numDF[0]  /* 3 vertices */
                   + 3 * thee->numDF[1]  /* 3 edges */
                   + 1 * thee->numDF[2]; /* 1 face */
    VASSERT( thee->numPS == dim_2DFB );
    VASSERT( thee->numP == dim_3DFB );
    VASSERT( thee->numP <= VMAXP );

    /* qorder of polynomials in the element */
    thee->qorder = 3;

    /* define the polynomial coefficients */
    setCoef(thee->numP,
        thee->c, thee->cx, thee->cy, thee->cz,
        lgr_3DFB, lgr_3DFBx, lgr_3DFBy, lgr_3DFBz );

    setQP3D(thee);

}

/*
 * ***************************************************************************
 * Routine:  setQP2D
 *
 * Purpose:  Initializer for quadrature points in 2D
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void setQP2D(Re *thee)
{
    int iq, is;
    double wq, xq[3];
    double c0 = 1.0 / 3.0;
    double c1 = 1.0 / 2.0;
    double c2 = 1.0 / (2.0*VSQRT(3.0));
    double c3 = VSQRT(2.0) / 2.0;
    double c4;
    const double SQ2 = VSQRT(2.0);

    /* ************************* */
    /* VOLUME QUADRATURE POINT 1 */
    /* ************************* */

    /* number of volume quadrature points */
    thee->q  = 1;

    iq = 0; is = -1; wq = c1;
    xq[0] = c0; xq[1] = c0; xq[2] = 0.;
    setQuadPoint(thee, iq, is, wq, xq);

    /* *************************************** */
    /* SURFACE QUADRATURE POINT 1 -- ALL FACES */
    /* *************************************** */

    /* number of surface quadrature points */
    thee->qs = 2;

    iq = 0; is = 0; wq = c3;
    xq[0] = c1+c2; xq[1] = c1-c2; xq[2] = 0.;
    setQuadPoint(thee, iq, is, wq, xq);

    iq = 0; is = 1; wq = c1;
    xq[0] = 0.; xq[1] = c1+c2; xq[2] = 0.;
    setQuadPoint(thee, iq, is, wq, xq);

    iq = 0; is = 2; wq = c1;
    xq[0] = c1-c2; xq[1] = 0.; xq[2] = 0.;
    setQuadPoint(thee, iq, is, wq, xq);

    iq = 0; is = 3; wq = 0.;
    xq[0] = 0.; xq[1] = 0.; xq[2] = 0.;
    setQuadPoint(thee, iq, is, wq, xq);

    /* *************************************** */
    /* SURFACE QUADRATURE POINT 2 -- ALL FACES */
    /* *************************************** */

    iq = 1; is = 0; wq = c3;
    xq[0] = c1-c2; xq[1] = c1+c2; xq[2] = 0.;
    setQuadPoint(thee, iq, is, wq, xq);

    iq = 1; is = 1; wq = c1;
    xq[0] = 0.; xq[1] = c1-c2; xq[2] = 0.;
    setQuadPoint(thee, iq, is, wq, xq);

    iq = 1; is = 2; wq = c1;
    xq[0] = c1+c2; xq[1] = 0.; xq[2] = 0.;
    setQuadPoint(thee, iq, is, wq, xq);

    iq = 1; is = 3; wq = 0.;
    xq[0] = 0.; xq[1] = 0.; xq[2] = 0.;
    setQuadPoint(thee, iq, is, wq, xq);

    /* ****************************************** */
    /* VOLUME QUADRATURE POINTS -- HIGH ACCURACY  */
    /* ****************************************** */

    /* number of volume quadrature points */
#if 1
    /* Rules from: Higher-order Finite Element Methods 
     *    By: Solin, Segeth and Dolezel (pg 238)
     */

    thee->qhi  = 6;

    iq = 0; is = -1; wq = 0.5 * 0.109951743655322;
    xq[0] = 0.816847572980459; xq[1] = 0.091576213509771; xq[2] = 0.0;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 1; is = -1; wq = 0.5 * 0.109951743655322;
    xq[0] = 0.091576213509771; xq[1] = 0.816847572980459; xq[2] = 0.0;
    setQuadPoint_hi(thee, iq, is, wq, xq);
 
    iq = 2; is = -1; wq = 0.5 * 0.109951743655322;
    xq[0] = 0.091576213509771; xq[1] = 0.091576213509771; xq[2] = 0.0;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 3; is = -1; wq = 0.5 * 0.223381589678011;
    xq[0] = 0.108103018168070; xq[1] = 0.445948490915965; xq[2] = 0.0;
    setQuadPoint_hi(thee, iq, is, wq, xq);
    
    iq = 4; is = -1; wq = 0.5 * 0.223381589678011;
    xq[0] = 0.445948490915965; xq[1] = 0.445948490915965; xq[2] = 0.0;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 5; is = -1; wq = 0.5 * 0.223381589678011;
    xq[0] = 0.445948490915965; xq[1] = 0.108103018168070; xq[2] = 0.0;
    setQuadPoint_hi(thee, iq, is, wq, xq);
#endif

#if 0
    /* number of volume quadrature points */
    thee->qhi  = 4;

    iq = 0; is = -1; wq = -0.28125;
    xq[0] = 1./3.; xq[1] = 1./3.; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 1; is = -1; wq = 1./3.84;
    xq[0] = 1./5.; xq[1] = 1./5.; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 2; is = -1; wq = 1./3.84;
    xq[0] = 3./5.; xq[1] = 1./5.; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 3; is = -1; wq = 1./3.84;
    xq[0] = 1./5.; xq[1] = 3./5.; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);
#endif

    /* ******************************************************** */
    /* SURFACE QUADRATURE POINT 0 -- ALL FACES -- HIGH ACCURACY */
    /* ******************************************************** */

    /* number of surface quadrature points */
    thee->qshi = 3;
    c1 = .5;
    c2 = .38729833;
    c3 = 4./9.;
    c4 = 5./18.;
    
    /*iq = 0; is = 0; wq = c3*SQ2;ECC-MOD */
    iq = 1; is = 0; wq = c3*SQ2;
    xq[0] = c1; xq[1] = c1; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* iq = 0; is = 1; wq = c3; ECC-MOD */
    iq = 1; is = 1; wq = c3;
    xq[0] = 0.; xq[1] = c1; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* iq = 0; is = 2; wq = c3; ECC-MOD */
    iq = 1; is = 2; wq = c3;
    xq[0] = c1; xq[1] = 0.; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* iq = 0; is = 3; wq = 0.; ECC-MOD */
    iq = 1; is = 3; wq = 0.;
    xq[0] = 0.; xq[1] = 0.; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* ******************************************************** */
    /* SURFACE QUADRATURE POINT 1 -- ALL FACES -- HIGH ACCURACY */
    /* ******************************************************** */

    /* iq = 1; is = 0; wq = c4*SQ2; ECC-MOD */
    iq = 0; is = 0; wq = c4*SQ2;
    xq[0] = c1+c2; xq[1] = c1-c2; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* iq = 1; is = 1; wq = c4; ECC-MOD */
    iq = 0; is = 1; wq = c4;
    xq[0] = 0.; xq[1] = c1+c2; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* iq = 1; is = 2; wq = c4; ECC-MOD */
    iq = 0; is = 2; wq = c4;
    xq[0] = c1-c2; xq[1] = 0.; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* iq = 1; is = 3; wq = 0.; ECC-MOD */
    iq = 0; is = 3; wq = 0.;
    xq[0] = 0.; xq[1] = 0.; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* ******************************************************** */
    /* SURFACE QUADRATURE POINT 2 -- ALL FACES -- HIGH ACCURACY */
    /* ******************************************************** */

    iq = 2; is = 0; wq = c4*SQ2;
    xq[0] = c1-c2; xq[1] = c1+c2; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 2; is = 1; wq = c4;
    xq[0] = 0.; xq[1] = c1-c2; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 2; is = 2; wq = c4;
    xq[0] = c1+c2; xq[1] = 0.; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 2; is = 3; wq = 0.;
    xq[0] = 0.; xq[1] = 0.; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);
}

/*
 * ***************************************************************************
 * Routine:  setQP3D
 *
 * Purpose:  Initializer for quadrature points in 3D
 *
 * Author:   Michael Holst, Oleg Korobkin
 * ***************************************************************************
 */
VPRIVATE void setQP3D(Re *thee)
{
    int iq, is;
    double wq, xq[3];
    double c0 = 1.0 / 4.0;
    double c1 = 1.0 / 6.0;
    double c2 = 1.0 / 2.0;
    double c3 = 1.0 / 3.0;
    double c4 = VSQRT(3.0) / 2.0;
    const double SQ3 = VSQRT(3.0);
    double xi1,xi2,xi3;

    /* ************************* */
    /* VOLUME QUADRATURE POINT 1 */
    /* ************************* */

    /* number of volume quadrature points */
    thee->q  = 1;

    iq = 0; is = -1; wq = c1;
    xq[0] = c0; xq[1] = c0; xq[2] = c0;
    setQuadPoint(thee, iq, is, wq, xq);

    /* *************************************** */
    /* SURFACE QUADRATURE POINT 1 -- ALL FACES */
    /* *************************************** */

    /* number of surface quadrature points */
    thee->qs = 1;

    iq = 0; is = 0; wq = c4;
    xq[0] = c3; xq[1] = c3; xq[2] = c3;
    setQuadPoint(thee, iq, is, wq, xq);

    iq = 0; is = 1; wq = c2;
    xq[0] = 0.; xq[1] = c3; xq[2] = c3;
    setQuadPoint(thee, iq, is, wq, xq);

    iq = 0; is = 2; wq = c2;
    xq[0] = c3; xq[1] = 0.; xq[2] = c3;
    setQuadPoint(thee, iq, is, wq, xq);

    iq = 0; is = 3; wq = c2;
    xq[0] = c3; xq[1] = c3; xq[2] = 0.;
    setQuadPoint(thee, iq, is, wq, xq);

    /* permutations of surface quadrature points */
    thee->spmt[VPMT_012][0] = 0;
    thee->spmt[VPMT_021][0] = 0;
    thee->spmt[VPMT_102][0] = 0;
    thee->spmt[VPMT_120][0] = 0;
    thee->spmt[VPMT_201][0] = 0;
    thee->spmt[VPMT_210][0] = 0;

    /* ****************************************** */
    /* VOLUME QUADRATURE POINTS -- HIGH ACCURACY  */
    /* ****************************************** */

#if 1
    /* Rules from: Higher-order Finite Element Methods 
     *    By: Solin, Segeth and Dolezel (pg 247)
     */
    thee->qhi  = 14;

    /* first weight */
    iq = 0; is = -1; wq = 0.0979907241/8.; 
    xi1 = -0.8145294993; xi2 = -0.8145294993; xi3 = -0.8145294993;
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 1; is = -1; wq = 0.0979907241/8.; 
    xi1 =  0.4435884981; xi2 = -0.8145294993; xi3 = -0.8145294993;
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 2; is = -1; wq = 0.0979907241/8.; 
    xi1 = -0.8145294993; xi2 =  0.4435884981; xi3 = -0.8145294993;
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 3; is = -1; wq = 0.0979907241/8.; 
    xi1 = -0.8145294993; xi2 = -0.8145294993; xi3 =  0.4435884981; 
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* second weight */
    iq = 4; is = -1; wq = 0.1502505676/8.;
    xi1 = -0.3782281614; xi2 = -0.3782281614; xi3 = -0.3782281614; 
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 5; is = -1; wq = 0.1502505676/8.;
    xi1 = -0.8653155155; xi2 = -0.3782281614; xi3 = -0.3782281614; 
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 6; is = -1; wq = 0.1502505676/8.;
    xi1 = -0.3782281614; xi2 = -0.8653155155; xi3 = -0.3782281614; 
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 7; is = -1; wq = 0.1502505676/8.;
    xi1 = -0.3782281614; xi2 = -0.3782281614; xi3 = -0.8653155155;
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* third weight */
    iq = 8; is = -1; wq = 0.0567280277/8.;
    xi1 = -0.0910074082; xi2 = -0.0910074082; xi3 = -0.9089925917;
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 9; is = -1; wq = 0.0567280277/8.;
    xi1 = -0.0910074082; xi2 = -0.9089925917; xi3 = -0.0910074082;
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 10; is = -1; wq = 0.0567280277/8.;
    xi1 = -0.9089925917; xi2 = -0.0910074082; xi3 = -0.0910074082;
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 11; is = -1; wq = 0.0567280277/8.;
    xi1 = -0.0910074082; xi2 = -0.9089925917; xi3 = -0.9089925917;
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 12; is = -1; wq = 0.0567280277/8.;
    xi1 = -0.9089925917; xi2 = -0.0910074082; xi3 = -0.9089925917;
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 13; is = -1; wq = 0.0567280277/8.;
    xi1 = -0.9089925917; xi2 = -0.9089925917; xi3 = -0.0910074082; 
    xq[0] = (xi1+1.)/2.; xq[1] = (xi2+1.)/2.; xq[2] = (xi3+1.)/2.;
    setQuadPoint_hi(thee, iq, is, wq, xq);
#endif


#if 0
    /* number of volume quadrature points */
    thee->qhi  = 5;

    iq = 0; is = -1; wq = -1./7.5;
    xq[0] = 1./4.; xq[1] = 1./4.; xq[2] = 1./4.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 1; is = -1; wq = 0.075;
    xq[0] = 1./6.; xq[1] = 1./6.; xq[2] = 1./6.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 2; is = -1; wq = 0.075;
    xq[0] = 3./6.; xq[1] = 1./6.; xq[2] = 1./6.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 3; is = -1; wq = 0.075;
    xq[0] = 1./6.; xq[1] = 3./6.; xq[2] = 1./6.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 4; is = -1; wq = 0.075;
    xq[0] = 1./6.; xq[1] = 1./6.; xq[2] = 3./6.;
    setQuadPoint_hi(thee, iq, is, wq, xq);
#endif

    /* ******************************************************** */
    /* SURFACE QUADRATURE POINT 0 -- ALL FACES -- HIGH ACCURACY */
    /* ******************************************************** */

    /************************************************************************
     * When specifying high-order 3D surface quadrature rules, 
     * one should take into account the following:
     * 1. The order at which quadrature points are numbered, should
     *    be the same for all faces. This means, that for two faces
     *    ABC and DEF the order of numbering of quadrature points
     *    should be such that if ABC is affinely mapped onto DEF,
     *    so that vertex A maps to D, B->E and C->F, then all quad points
     *    (q1,q2,..,qN) in ABC map to quad points at DEF (d1,d2,..,dN) 
     *    in the same order: q1->d1, q2->d2,.., qN->dN.
     * 2. Arrays Re::qpmt and Re::qpmthi must be initialized to reflect the
     *    way set of quadrature points is transformed under permutation
     *    of vertices. This is best viewed with quadrature points in
     *    equilateral triangle: every permutation of vertices corresponds
     *    to a symmetry transformation of the triangle, which maps
     *    set of all quadrature points onto itself. In other words,
     *    permutation of vertices induces certain permutation of 
     *    quadrature points.
     *
     * Example of quadrature points numbering for standard 3D master element,
     * and 4-point quadrature rule:
     *  
     *          face 0        face 1      face 2       face 3
     *          {1,2,3}       {2,0,3}     {0,1,3}      {0,2,1}
     *                                                        
     *               3             3      3            0----1
     *              / \           /|      |\           |1 3/
     *             / 3 \         /3|      |3\          | 0/ 
     *            /  0  \       /0 |      | 0\         |2/ 
     *           / 1   2 \     /1 2|      |1 2\        |/   
     *          1---------2   2----0      0----1       2
     *
     * 3D-coordinates of these quadrature points:
     * --------+-------------------------------------------------
     * qp\face |  0:{1,2,3}  | 1:{2,0,3} | 2:{0,1,3} | 3:{0,1,3}
     * --------+-------------------------------------------------
     * qp #0   | 1/3,1/3,1/3 | 0,1/3,1/3 | 1/3,0,1/3 | 1/3,1/3,0
     * qp #1   | 3/5,1/5,1/5 | 0,3/5,1/5 | 1/5,0,1/5 | 1/5,1/5,0
     * qp #2   | 1/5,3/5,1/5 | 0,1/5,1/5 | 3/5,0,1/5 | 1/5,3/5,0
     * qp #5   | 1/5,1/5,3/5 | 0,1/5,3/5 | 1/5,0,3/5 | 3/5,1/5,0
     * --------+-------------------------------------------------
     *
     * Permutation of vertices and induced permutations of quad. points:
     *
     * 012 -> 0123
     * 021 -> 0132
     * 102 -> 0213
     * 120 -> 0231
     * 201 -> 0312
     * 210 -> 0321
     *
     ************************************************************************/
    /* number of surface quadrature points */
    thee->qshi  = 4;
    c2 = -0.28125;
    c3 = 1./3.;

    iq = 0; is = 0; wq = c2*SQ3;
    xq[0] = c3; xq[1] = c3; xq[2] = c3;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 0; is = 1; wq = c2;
    xq[0] = 0.; xq[1] = c3; xq[2] = c3;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 0; is = 2; wq = c2;
    xq[0] = c3; xq[1] = 0.; xq[2] = c3;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 0; is = 3; wq = c2;
    xq[0] = c3; xq[1] = c3; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* ******************************************************** */
    /* SURFACE QUADRATURE POINT 1 -- ALL FACES -- HIGH ACCURACY */
    /* ******************************************************** */
    c2 = 1./3.84;
    c3 = 1./5.; 
    c4 = 3./5.;

    iq = 1; is = 0; wq = c2*SQ3;
    xq[0] = c4; xq[1] = c3; xq[2] = c3;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 1; is = 1; wq = c2;
    xq[0] = 0.; xq[1] = c4; xq[2] = c3;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 1; is = 2; wq = c2;
    xq[0] = c3; xq[1] = 0.; xq[2] = c3;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 1; is = 3; wq = c2;
    xq[0] = c3; xq[1] = c3; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* ******************************************************** */
    /* SURFACE QUADRATURE POINT 2 -- ALL FACES -- HIGH ACCURACY */
    /* ******************************************************** */
    iq = 2; is = 0; wq = c2*SQ3;
    xq[0] = c3; xq[1] = c4; xq[2] = c3;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 2; is = 1; wq = c2;
    xq[0] = 0.; xq[1] = c3; xq[2] = c3;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 2; is = 2; wq = c2;
    xq[0] = c4; xq[1] = 0.; xq[2] = c3;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 2; is = 3; wq = c2;
    xq[0] = c3; xq[1] = c4; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* ******************************************************** */
    /* SURFACE QUADRATURE POINT 3 -- ALL FACES -- HIGH ACCURACY */
    /* ******************************************************** */
    iq = 3; is = 0; wq = c2*SQ3;
    xq[0] = c3; xq[1] = c3; xq[2] = c4;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 3; is = 1; wq = c2;
    xq[0] = 0.; xq[1] = c3; xq[2] = c4;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 3; is = 2; wq = c2;
    xq[0] = c3; xq[1] = 0.; xq[2] = c4;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    iq = 3; is = 3; wq = c2;
    xq[0] = c4; xq[1] = c3; xq[2] = 0.;
    setQuadPoint_hi(thee, iq, is, wq, xq);

    /* permutations of hi-accuracy surface quadrature points */
    thee->spmthi[VPMT_012][0] = 0;
    thee->spmthi[VPMT_012][1] = 1;
    thee->spmthi[VPMT_012][2] = 2;
    thee->spmthi[VPMT_012][3] = 3;

    thee->spmthi[VPMT_021][0] = 0;
    thee->spmthi[VPMT_021][1] = 1;
    thee->spmthi[VPMT_021][2] = 3;
    thee->spmthi[VPMT_021][3] = 2;

    thee->spmthi[VPMT_102][0] = 0;
    thee->spmthi[VPMT_102][1] = 2;
    thee->spmthi[VPMT_102][2] = 1;
    thee->spmthi[VPMT_102][3] = 3;

    thee->spmthi[VPMT_120][0] = 0;
    thee->spmthi[VPMT_120][1] = 2;
    thee->spmthi[VPMT_120][2] = 3;
    thee->spmthi[VPMT_120][3] = 1;

    thee->spmthi[VPMT_201][0] = 0;
    thee->spmthi[VPMT_201][1] = 3;
    thee->spmthi[VPMT_201][2] = 1;
    thee->spmthi[VPMT_201][3] = 2;

    thee->spmthi[VPMT_210][0] = 0;
    thee->spmthi[VPMT_210][1] = 3;
    thee->spmthi[VPMT_210][2] = 2;
    thee->spmthi[VPMT_210][3] = 1;

}

