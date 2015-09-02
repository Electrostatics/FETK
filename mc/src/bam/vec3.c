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
 * rcsid="$Id: vec3.c,v 1.3 2010/08/12 05:18:31 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     vec3.c
 *
 * Purpose:  Class Vec3,Mat3: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "vec3_p.h"

VEMBED(rcsid="$Id: vec3.c,v 1.3 2010/08/12 05:18:31 fetk Exp $")

/*
 * ***************************************************************************
 * Class Vec3,Mat3: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_MALOC)

#endif /* if !defined(VINLINE_MALOC) */
/*
 * ***************************************************************************
 * Class Vec3,Mat3: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Vec3_nrm1
 *
 * Purpose:  1-norm of a 3-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec3_nrm1(Vec3 u)
{
    return ( VABS(u[0]) + VABS(u[1]) + VABS(u[2]) );
}

/*
 * ***************************************************************************
 * Routine:  Vec3_nrm2
 *
 * Purpose:  2-norm of a 3-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec3_nrm2(Vec3 u)
{
    return VSQRT( u[0]*u[0] + u[1]*u[1] + u[2]*u[2] );
}

/*
 * ***************************************************************************
 * Routine:  Vec3_nrm8
 *
 * Purpose:  oo-norm of a 3-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec3_nrm8(Vec3 u)
{
    double tmp = 0.;
    tmp = VMAX2( tmp, VABS(u[0]) );
    tmp = VMAX2( tmp, VABS(u[1]) );
    tmp = VMAX2( tmp, VABS(u[2]) );
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Vec3_dif1
 *
 * Purpose:  1-norm of a 3-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec3_dif1(Vec3 u, Vec3 v)
{
    double tmp = 0.;
    tmp += VABS(u[0]-v[0]);
    tmp += VABS(u[1]-v[1]);
    tmp += VABS(u[2]-v[2]);
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Vec3_dif2
 *
 * Purpose:  2-norm of a 3-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec3_dif2(Vec3 u, Vec3 v)
{
    double tmp = 0.;
    tmp += ( (u[0]-v[0]) * (u[0]-v[0]) );
    tmp += ( (u[1]-v[1]) * (u[1]-v[1]) );
    tmp += ( (u[2]-v[2]) * (u[2]-v[2]) );
    return VSQRT(tmp);
}

/*
 * ***************************************************************************
 * Routine:  Vec3_dif8
 *
 * Purpose:  oo-norm of a 3-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec3_dif8(Vec3 u, Vec3 v)
{
    double tmp = 0.;
    tmp = VMAX2( tmp, VABS( u[0]-v[0] ) );
    tmp = VMAX2( tmp, VABS( u[1]-v[1] ) );
    tmp = VMAX2( tmp, VABS( u[2]-v[2] ) );
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Vec3_dot
 *
 * Purpose:  dot product of two 3-vectors.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Vec3_dot(Vec3 u, Vec3 v)
{
    return ( u[0]*v[0] + u[1]*v[1] + u[2]*v[2] );
}

/*
 * ***************************************************************************
 * Routine:  Vec3_init
 *
 * Purpose:  initialize a 3-vector to be a constant.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_init(Vec3 u, double val)
{
    u[0] = val;
    u[1] = val;
    u[2] = val;
}

/*
 * ***************************************************************************
 * Routine:  Vec3_scal
 *
 * Purpose:  3-vector scale.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_scal(Vec3 u, double val)
{
    u[0] *= val;
    u[1] *= val;
    u[2] *= val;
}

/*
 * ***************************************************************************
 * Routine:  Vec3_copy
 *
 * Purpose:  3-vector copy.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_copy(Vec3 u, Vec3 v)
{
    u[0] = v[0];
    u[1] = v[1];
    u[2] = v[2];
}

/*
 * ***************************************************************************
 * Routine:  Vec3_axpy
 *
 * Purpose:  scalar times 3-vector plus 3-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_axpy(Vec3 u, Vec3 v, double val)
{
    u[0] += (val * v[0]);
    u[1] += (val * v[1]);
    u[2] += (val * v[2]);
}

/*
 * ***************************************************************************
 * Routine:  Vec3_xcry
 *
 * Purpose:  cross-product of two 3-vectors.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_xcry(Vec3 u, Vec3 v, Vec3 w)
{
    u[0] = v[1]*w[2] - v[2]*w[1];
    u[1] = v[2]*w[0] - v[0]*w[2];
    u[2] = v[0]*w[1] - v[1]*w[0];
}

/*
 * ***************************************************************************
 * Routine:  Vec3_nrmlize
 *
 * Purpose:  normalize a 3-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_nrmlize(Vec3 u, double scale)
{
    double d;
    d = Vec3_nrm2(u);
    if (d == 0.) {
        VASSERT ( d != 0. );
        d = 1.;
        u[0] = d;
    }
    d = scale/d;
    u[0] *= d; u[1] *= d; u[2] *= d;
}

/*
 * ***************************************************************************
 * Routine:  Vec3_nrmlizeNE
 *
 * Purpose:  normalize a 3-vector (no error check).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_nrmlizeNE(Vec3 u, double scale)
{
    double d;
    d = Vec3_nrm2(u);
    if (d == 0.) {
        d = 1.;
        u[0] = d;
    }
    d = scale/d;
    u[0] *= d; u[1] *= d; u[2] *= d;
}

/*
 * ***************************************************************************
 * Routine:  Vec3_print
 *
 * Purpose:  print a 3-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_print(Vec3 u, const char *name)
{
    Vnm_print(0, "\n%s = [\n", name);
    Vnm_print(0, "    %15.8e\n", u[0]);
    Vnm_print(0, "    %15.8e\n", u[1]);
    Vnm_print(0, "    %15.8e\n", u[2]);
    Vnm_print(0, "];\n\n");
}

/*
 * ***************************************************************************
 * Routine:  Vec3_mult
 *
 * Purpose:  multiply a 3-matrix and a 3-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_mult(Vec3 u, Mat3 A, Vec3 v)
{
    int i,j;
    for (i=0; i<3; i++) {
        u[i] = 0.;
        for (j=0; j<3; j++)
            u[i] += (A[i][j] * v[j]);
    }
}

/*
 * ***************************************************************************
 * Routine:  Vec3_getCol
 *
 * Purpose:  get 3-vector column of a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_getCol(Vec3 u, Mat3 A, int col)
{
    u[0] = A[0][col];
    u[1] = A[1][col];
    u[2] = A[2][col];
}

/*
 * ***************************************************************************
 * Routine:  Vec3_getRow
 *
 * Purpose:  get 3-vector row of a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vec3_getRow(Vec3 u, Mat3 A, int row)
{
    u[0] = A[row][0];
    u[1] = A[row][1];
    u[2] = A[row][2];
}

/*
 * ***************************************************************************
 * Routine:  Mat3_nrm1
 *
 * Purpose:  1-norm of a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Mat3_nrm1(Mat3 A)
{
    int i, j;
    double tmp = 0.;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            tmp += VABS(A[i][j]);
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Mat3_nrm2
 *
 * Purpose:  2-norm of a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Mat3_nrm2(Mat3 A)
{
    int i, j;
    double tmp = 0.;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            tmp += ( A[i][j] * A[i][j] );
    return VSQRT(tmp);
}

/*
 * ***************************************************************************
 * Routine:  Mat3_nrm8
 *
 * Purpose:  oo-norm of a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Mat3_nrm8(Mat3 A)
{
    int i, j;
    double tmp = 0.;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            tmp = VMAX2( tmp, VABS(A[i][j]) );
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Mat3_dif1
 *
 * Purpose:  1-norm of difference of two 3-matrices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Mat3_dif1(Mat3 A, Mat3 B)
{
    int i, j;
    double tmp = 0.;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            tmp += VABS(A[i][j] - B[i][j]);
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Mat3_dif2
 *
 * Purpose:  2-norm of difference of two 3-matrices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Mat3_dif2(Mat3 A, Mat3 B)
{
    int i, j;
    double tmp = 0.;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            tmp += ( (A[i][j]-B[i][j]) * (A[i][j]-B[i][j]) );
    return VSQRT(tmp);
}

/*
 * ***************************************************************************
 * Routine:  Mat3_dif8
 *
 * Purpose:  oo-norm of difference of two 3-matrices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Mat3_dif8(Mat3 A, Mat3 B)
{
    int i, j;
    double tmp = 0.;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            tmp = VMAX2( tmp, VABS(A[i][j]-B[i][j]) );
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Mat3_nrm8Low
 *
 * Purpose:  oo-norm of lower-triangle of a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Mat3_nrm8Low(Mat3 A)
{
    int i, j;
    double tmp = 0.;
    for (i=0; i<3; i++) 
        for (j=0; j<3; j++) 
            if (i>j) tmp = VMAX2( tmp, VABS(A[i][j]) );
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Mat3_eye
 *
 * Purpose:  identity 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_eye(Mat3 A)
{
    int i;
    Mat3_init(A, 0.);
    for (i=0; i<3; i++)
        A[i][i] = 1.;
}

/*
 * ***************************************************************************
 * Routine:  Mat3_init
 *
 * Purpose:  initialize a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_init(Mat3 A, double val)
{
    int i,j;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            A[i][j] = val;
}

/*
 * ***************************************************************************
 * Routine:  Mat3_scal
 *
 * Purpose:  normalize a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_scal(Mat3 A, double val)
{
    int i,j;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            A[i][j] *= val;
}

/*
 * ***************************************************************************
 * Routine:  Mat3_copy
 *
 * Purpose:  copy a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_copy(Mat3 A, Mat3 B)
{
    int i, j;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            A[i][j] = B[i][j];
}

/*
 * ***************************************************************************
 * Routine:  Mat3_axpy
 *
 * Purpose:  Saxpy for 3-matrices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_axpy(Mat3 A, Mat3 B, double val)
{
    int i, j;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            A[i][j] += ( val * B[i][j] );
}

/*
 * ***************************************************************************
 * Routine:  Mat3_mult
 *
 * Purpose:  multiply 3-matrices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_mult(Mat3 C, Mat3 A, Mat3 B)
{
    int i, j, k;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++) {
            C[i][j] = 0.;
            for (k=0; k<3; k++)
                C[i][j] += ( A[i][k] * B[k][j] );
        }
}

/*
 * ***************************************************************************
 * Routine:  Mat3_putCol
 *
 * Purpose:  put a 3-vector column in a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_putCol(Mat3 A, Vec3 u, int col)
{
    A[0][col] = u[0];
    A[1][col] = u[1];
    A[2][col] = u[2];
}

/*
 * ***************************************************************************
 * Routine:  Mat3_putRow
 *
 * Purpose:  put a 3-vector row in a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_putRow(Mat3 A, Vec3 u, int row)
{
    A[row][0] = u[0];
    A[row][1] = u[1];
    A[row][2] = u[2];
}

/*
 * ***************************************************************************
 * Routine:  Mat3_print
 *
 * Purpose:  print a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_print(Mat3 A, const char *name)
{
    int i, j;

    Vnm_print(0,"\n%s = [\n", name);
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++)
            Vnm_print(0, "    %15.8e", A[i][j]);
        Vnm_print(0,"\n");
    }
    Vnm_print(0,"];\n\n");
}

/*
 * ***************************************************************************
 * Routine:  Mat3_qri
 *
 * Purpose:  QR iteration for 3-matrices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Mat3_qri(Mat3 V, Mat3 D, Mat3 A)
{
    Mat3 Q, R, T;
    Vec3 v0, v1, v2;
    double min, max, err, TOL = 1.0e-5;
    int i, minI, maxI, midI, iters;
    char rn[80];

    strncpy(rn,"--->Mat3_qri:",80);

    /* do a QR iteration until lower triangle of A has vanished */
    Mat3_copy(D, A);
    Mat3_eye(V);
    err = 1.;
    iters = 0;
    while ( (err > TOL) && (!Vnm_sigInt()) ) {
        Mat3_qr(Q,R,D);
        Mat3_mult(D,R,Q);
        Mat3_copy(T,V);
        Mat3_mult(V,T,Q);
        err = Mat3_nrm8Low(D);
        iters++;
    }
    Vnm_print(0,"%s it=%4d",rn,iters);
    Vnm_print(0,"  err=%8.2e\n", err);

    /* reorder D (and V) to give eigs in ascending order */
    min  =  VLARGE;
    max  = -VLARGE;
    minI = -1;
    maxI = -1;
    for (i=0; i<3; i++) {
        if (D[i][i] < min) {
            min  = D[i][i];
            minI = i;
        }
        if (D[i][i] > max) {
            max  = D[i][i];
            maxI = i;
        }
    }
    if (minI != maxI) {
        midI = -1;
        if      ((minI == 0) && (maxI == 1)) midI = 2;
        else if ((minI == 1) && (maxI == 0)) midI = 2;
        else if ((minI == 0) && (maxI == 2)) midI = 1;
        else if ((minI == 2) && (maxI == 0)) midI = 1;
        else if ((minI == 1) && (maxI == 2)) midI = 0;
        else if ((minI == 2) && (maxI == 1)) midI = 0;
        else Vnm_print(2,"Mat3_qri: Problem!\n");

        Mat3_eye(T);
        T[0][0] = D[minI][minI];
        T[1][1] = D[midI][midI];
        T[2][2] = D[maxI][maxI];
        Mat3_copy(D,T);
        Vec3_getCol(v0, V, minI);
        Vec3_getCol(v1, V, midI);
        Vec3_getCol(v2, V, maxI);
        Mat3_putCol(V, v0, 0);
        Mat3_putCol(V, v1, 1);
        Mat3_putCol(V, v2, 2);
    }

    return err;
}

/*
 * ***************************************************************************
 * Routine:  Mat3_gramSch
 *
 * Purpose:  QR factorization of 3-matrix (via modified Graham-Schmidt).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_gramSch(Mat3 Q, Mat3 R, Mat3 A)
{
    int i,j,k;
    double tmp, den;

    /* initialize Q and R */
    Mat3_copy(Q, A);
    Mat3_init(R, 0.);

    /* do one complete step of modified gram-schmidt */
    for (k=0; k<3; k++) {
        tmp = 0.;
        for (i=0; i<3; i++)
            tmp += ( Q[i][k] * Q[i][k] );
        VASSERT( tmp >= 0. );
        R[k][k] = VSQRT( tmp );
        if (R[k][k] == 0.) den = 1.;
        else den = R[k][k];
        for (i=0; i<3; i++)
            Q[i][k] /= den;
        for (j=k+1; j<3; j++) {
            tmp = 0.;
            for (i=0; i<3; i++)
                tmp += ( Q[i][k] * Q[i][j] );
            R[k][j] = tmp;
            for (i=0; i<3; i++)
                Q[i][j] -= ( Q[i][k] * R[k][j] );
        }
    }

    /* handle possible zero rows -- make an identity equation */
    for (i=0; i<3; i++) {
        tmp = 0.;
        for (j=0; j<3; j++)
            tmp += Q[i][j];
        if (tmp == 0.) Q[i][i] = 1.;
    }
}

/*
 * ***************************************************************************
 * Routine:  Mat3_ar
 *
 * Purpose:  a single QR iteration for a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_qr(Mat3 Q, Mat3 R, Mat3 A)
{
    Mat3 Q1, Q2, R1, R2, R3, T;

    /* do QR three times to deal with possible loss of orthogonality... */
    Mat3_gramSch(Q1, R1, A);
    Mat3_gramSch(Q2, R2, Q1);
    Mat3_gramSch(Q,  R3, Q2);

    /* build the cummulative R now */
    Mat3_mult(T, R2, R1);
    Mat3_mult(R, R3, T);
}

/*
 * ***************************************************************************
 * Routine:  Mat3_det
 *
 * Purpose:  determinant of a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC double Mat3_det(Mat3 A)
{
    double tmp;

    tmp = A[0][0]*A[1][1]*A[2][2]
        - A[0][0]*A[2][1]*A[1][2]
        - A[0][1]*A[1][0]*A[2][2]
        + A[0][1]*A[2][0]*A[1][2]
        + A[0][2]*A[1][0]*A[2][1]
        - A[0][2]*A[2][0]*A[1][1];

    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  Mat3_inverse
 *
 * Purpose:  inverse of a 3-matrix.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Mat3_inverse(Mat3 A, Mat3 Ainv)
{
    double detA, detAinv;

    detA = Mat3_det(A);
    VASSERT( detA != 0. );
    detAinv = (1. / detA);

    Ainv[0][0] = detAinv * (A[1][1]*A[2][2] - A[2][1]*A[1][2]);
    Ainv[0][1] = detAinv * (A[2][1]*A[0][2] - A[0][1]*A[2][2]);
    Ainv[0][2] = detAinv * (A[0][1]*A[1][2] - A[1][1]*A[0][2]);
    Ainv[1][0] = detAinv * (A[2][0]*A[1][2] - A[1][0]*A[2][2]);
    Ainv[1][1] = detAinv * (A[0][0]*A[2][2] - A[2][0]*A[0][2]);
    Ainv[1][2] = detAinv * (A[1][0]*A[0][2] - A[0][0]*A[1][2]);
    Ainv[2][0] = detAinv * (A[1][0]*A[2][1] - A[2][0]*A[1][1]);
    Ainv[2][1] = detAinv * (A[2][0]*A[0][1] - A[0][0]*A[2][1]);
    Ainv[2][2] = detAinv * (A[0][0]*A[1][1] - A[1][0]*A[0][1]);
}

