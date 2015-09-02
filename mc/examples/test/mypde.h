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
 * rcsid="$Id: mypde.h,v 1.4 2010/08/12 05:17:58 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     mypde.h
 *
 * Purpose:  Class PDE: method prototypes.
 *
 * Notes:    The user must provide a correctly constructed PDE object to
 *           the VMC constructor.  Typically this means that the user will
 *           write constructors and destructors with prototypes:
 *
 *               VPUBLIC PDE* myPDE_ctor(void);
 *               VPUBLIC void myPDE_dtor(PDE **thee);
 *
 *           Since the user calls these functions, they can be give any
 *           name the user prefers; the above follows the MC coding style.
 *
 *           Note that since this header includes the core MC header
 *           "mc/mc.h", the user-defined code can simply include this
 *           single header.
 *
 *           In the constructor, the user must set some required informational
 *           fields in the PDE structure, and then must also set some function
 *           pointers to the problem-specific forms and functions.  All of
 *           these fields and prototypes are defined in the PDE structure
 *           header file <mc/pde.h>.  The required function prototypes are:
 *
 *               VPUBLIC void initAssemble(PDE *thee, int ip[], double rp[]);
 *               VPUBLIC void initElement(PDE *thee, int elementType,
 *                   int chart, double tvx[][3], void *data);
 *               VPUBLIC void initFace(PDE *thee, int faceType,
 *                   int chart, double tnvec[]);
 *               VPUBLIC void initPoint(PDE *thee, int pointType,
 *                   int chart, double txq[],
 *                   double U[], double dU[][3]);
 *
 *               VPUBLIC void Fu(PDE *thee, int key, double F[]);
 *               VPUBLIC double Ju(PDE *thee, int key);
 *               VPUBLIC double Fu_v(PDE *thee, int key,
 *                   double V[], double dV[][3]);
 *               VPUBLIC double DFu_wv(PDE *thee, int key,
 *                   double W[], double dW[][3],
 *                   double V[], double dV[][3]);
 *               VPUBLIC double p_wv(PDE *thee, int key,
 *                   double W[], double V[]);
 *
 *               VPUBLIC void delta(PDE *thee, int type,
 *                   int chart, double txq[], void *data,
 *                   double F[]);
 *               VPUBLIC void u_D(PDE *thee, int type,
 *                   int chart, double txq[], double F[]);
 *               VPUBLIC void u_T(PDE *thee, int type,
 *                   int chart, double txq[], double F[], double dF[][3]);
 *
 *               VPUBLIC void bisectEdge(int dim, int dimII,
 *                   int edgeType, int chart[], double vx[][3]);
 *               VPUBLIC void mapBoundary(int dim, int dimII,
 *                   int vertexType, int chart, double vx[3]);
 *               VPUBLIC void markSimplex(int dim, int dimII,
 *                   int simplexType, int faceType[4], int vertexType[4],
 *                   int chart[], double vx[][3], void *data);
 *               VPUBLIC void oneChart(int dim, int dimII,
 *                   int objType, int chart[], double vx[][3], int dimV);
 *
 *               VPUBLIC int simplexBasisInit(int key, int dim, int comp,
 *                   int *ndof, int dof[]);
 *               VPUBLIC void simplexBasisForm(int key, int dim, int comp,
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "mc/mc.h"

/*
 * ***************************************************************************
 * Required prototypes
 * ***************************************************************************
 */

VEXTERNC PDE* myPDE_ctor(void);
VEXTERNC void myPDE_dtor(PDE **thee);

VEXTERNC void initAssemble(PDE *thee, int ip[], double rp[]);
VEXTERNC void initElement(PDE *thee, int elementType,
    int chart, double tvx[][3], void *data);
VEXTERNC void initFace(PDE *thee, int faceType,
    int chart, double tnvec[]);
VEXTERNC void initPoint(PDE *thee, int pointType,
    int chart, double txq[],
    double tU[], double tdU[][3]);

VEXTERNC void Fu(PDE *thee, int key, double F[]);
VEXTERNC double Ju(PDE *thee, int key);
VEXTERNC double Fu_v(PDE *thee, int key,
    double V[], double dV[][3]);
VEXTERNC double DFu_wv(PDE *thee, int key,
    double W[], double dW[][3],
    double V[], double dV[][3]);
VEXTERNC double p_wv(PDE *thee, int key,
    double W[], double V[]);

VEXTERNC void delta(PDE *thee, int type,
    int chart, double txq[], void *data, 
    double F[]);
VEXTERNC void u_D(PDE *thee, int type,
    int chart, double txq[], double F[]);
VEXTERNC void u_T(PDE *thee, int type,
    int chart, double txq[], double F[], double dF[][3]);

VEXTERNC void bisectEdge(int dim, int dimII,
    int edgeType, int chart[], double vx[][3]);
VEXTERNC void mapBoundary(int dim, int dimII,
    int vertexType, int chart, double vx[3]);
VEXTERNC int markSimplex(int dim, int dimII,
    int simplexType, int faceType[4], int vertexType[4],
    int chart[], double vx[][3], void *data);
VEXTERNC void oneChart(int dim, int dimII,
    int objType, int chart[], double vx[][3], int dimV);

VEXTERNC int simplexBasisInit(int key, int dim, int comp,
    int *ndof, int dof[]);
VEXTERNC void simplexBasisForm(int key, int dim, int comp,
    int pdkey, double xq[], double basis[]);

