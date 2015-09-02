/*
 * ***************************************************************************
 * SG = < Socket Graphics >
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
 * rcsid="$Id: ogl.c,v 1.15 2010/08/12 04:56:22 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     ogl.c
 *
 * Purpose:  Class Ogl: methods.
 *
 * Notes:    Ogl is an OpenGL object manipulator for 2D plane polygon-based
 *           objects.  It is designed to look and act very much like Geomview.
 *           The manipulator itself is designed to feel like a combination
 *           of the manipulator in Geomview, and the Arcball rotator of
 *           Ken Shoemake.
 *
 *           Ogl is a simple, machine and window system-independent layer
 *           built on the OpenGL libraris (GL and GLU).  It is written to be
 *           independent of the particular windowing system.  The windowing
 *           system-specific code (for example, X, Win32, or other window
 *           system) is to be wrapped around this small set of graphics
 *           routines (which is itself wrapped around the OpenGL library...)
 *
 * On the ordering of the vertices in a polygon:
 *
 *           All closed polygons must be specified by a set of consecutive 
 *           vertices in counter-clockwise-ordering by vertices, as seen from
 *           the "up" side of the polygon.  This produces the correct
 *           surface-normals from the right-hand-rule for surfaces, which is
 *           required to get correct shading effects from OpenGL.  Since
 *           the polygons are allowed to be oriented in any manner in R^3,
 *           it is important that you provide these orderings correctly.
 *           (There is no way to determine the ordering for you; for example,
 *           there is no such consistent ordering for a mobius strip, which
 *           is an example of a non-orientable surface that can be displayed
 *           using Ogl.
 *
 * General notes and warnings to myself about programming with OpenGL:
 *
 *           (1) The "GL_MODELVIEW" matrix is the default matrix which stack 
 *               operations will pertain to.  When switching to the
 *               "GL_PROJECTION" matrix with "glMatrixMode" to define the view
 *               volume projector, you MUST switch back to the "GL_MODELVIEW"
 *               matrix with another "glMatrixMode" command.
 *
 *           (2) The node ordering/shading relationship is subtle; you may not
 *               see mistakes in the normal vectors if both front and back
 *               sides of polygons are set to be drawn with fill.  To try to
 *               catch mistakes, we always set the back-side of polygons to be
 *               drawn wire.  For a closed 3D object, no back-sides should be
 *               seen.  If some polygons appear to be drawn with wire rather
 *               than solid, this means a node ordering for some tetrahedra
 *               was given incorrectly.  (The fill type is set as
 *               "glPolygonMode(GL_BACK, GL_LINE)", with GL_LINE or GL_FILL
 *               specified).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "ogl_p.h"

VEMBED(rcsid="$Id: ogl.c,v 1.15 2010/08/12 04:56:22 fetk Exp $")

#define CUBESIZE     1.0
#define BALLSIZE     1.0
#define NUMARC       20
#define NUMPDB       10
#define RENORMAL     100
#define TOL          1.0e-5

/*
 * VPRIVATE float C_BLACK[4]     = { 0.0,   0.0,   0.0,   1.0 };
 * VPRIVATE float C_RED[4]       = { 1.0,   0.0,   0.0,   1.0 };
 * VPRIVATE float C_GREEN[4]     = { 0.0,   1.0,   0.0,   1.0 };
 * VPRIVATE float C_BLUE[4]      = { 0.0,   0.0,   1.0,   1.0 };
 * VPRIVATE float C_YELLOW[4]    = { 1.0,   1.0,   0.0,   1.0 };
 * VPRIVATE float C_CYAN[4]      = { 0.0,   1.0,   1.0,   1.0 };
 * VPRIVATE float C_MAGENTA[4]   = { 1.0,   0.0,   1.0,   1.0 };
 * VPRIVATE float C_WHITE[4]     = { 1.0,   1.0,   1.0,   1.0 };
 * VPRIVATE float C_DGREY[4]     = { 0.333, 0.333, 0.333, 1.0 };
 * VPRIVATE float C_LGREY[4]     = { 0.666, 0.666, 0.666, 1.0 };
 * VPRIVATE float C_CLEAR_GV[4]  = { 0.310, 0.320, 0.310, 1.0 };
 * VPRIVATE float C_INTERIOR[4]  = { 0.0,   1.0,   0.0,   1.0 };
 * VPRIVATE float C_CLEAR[4]     = { 1.0,   1.0,   1.0,   1.0 };
 */

#if 1
  VPRIVATE float C_CLEAR_GV[4]={(float)1.0, (float)1.0, (float)1.0, (float)1.0};
#else
  VPRIVATE float C_CLEAR_GV[4]={(float)0.31,(float)0.32,(float)0.31,(float)1.0};
#endif
VPRIVATE float C_BLACK[4]   ={(float)0.0, (float)0.0, (float)0.0, (float)1.0};
VPRIVATE float C_CYAN[4]    ={(float)0.0, (float)1.0, (float)1.0, (float)1.0};
VPRIVATE float C_BALL[4]    ={(float)0.8, (float)1.0, (float)1.0, (float)1.0};

VPRIVATE void makeBallList(Ogl *thee);
VPRIVATE void makeBBoxList(Ogl *thee);
VPRIVATE void dragBall(Ogl *thee);
VPRIVATE void initView(Ogl *thee);
VPRIVATE void setLights(Ogl *thee);
VPRIVATE void setEffects(Ogl *thee);
VPRIVATE void clearBBox(Ogl *thee);
VPRIVATE void makeBBox(Ogl *thee);
VPRIVATE void rotate(Ogl *thee);
VPRIVATE void scale(Ogl *thee);
VPRIVATE void translate(Ogl *thee);

VPRIVATE void vzero(float u[]);
VPRIVATE void vset(float u[], float x, float y, float z);
VPRIVATE void vsub(const float u[], const float v[], float w[]);
VPRIVATE void vcopy(const float u[], float v[]);
VPRIVATE void vcross(const float u[], const float v[], float w[]);
VPRIVATE float vlength(const float u[]);
VPRIVATE void vscale(float u[], float scale);
VPRIVATE void vnormal(float u[]);
VPRIVATE float vdot(const float u[], const float v[]);
VPRIVATE void vadd(const float u[], const float v[], float w[]);

VPRIVATE void buildQuat(float q[4], float r0[3], float r2[3]);
VPRIVATE void axisQuat(float a[3], float phi, float q[4]);
VPRIVATE void addQuat(float q0[4], float q1[4], float des[4]);
VPRIVATE void normalQuat(float q[4]);
VPRIVATE void buildRotation(float m[4][4], float q[4]);
VPRIVATE float projectSphere(float r, float x, float y);

#define sph8_numV 6
VPRIVATE float sph8_V[sph8_numV][3] = {
{  0.0000000000e+00,  0.0000000000e+00,  1.0000000000e+00 },
{  0.0000000000e+00,  0.0000000000e+00, -1.0000000000e+00 },
{  7.0710680000e-01,  7.0710680000e-01,  0.0000000000e+00 },
{ -7.0710680000e-01,  7.0710680000e-01,  0.0000000000e+00 },
{ -7.0710680000e-01, -7.0710680000e-01,  0.0000000000e+00 },
{  7.0710680000e-01, -7.0710680000e-01,  0.0000000000e+00 }
};
#if 0
#define sph8_numS 8
VPRIVATE int sph8_S[sph8_numS][3] = {
{ 0, 2, 3 },
{ 0, 3, 4 },
{ 0, 4, 5 },
{ 0, 5, 2 },
{ 1, 3, 2 },
{ 1, 4, 3 },
{ 1, 5, 4 },
{ 1, 2, 5 }
};
#endif

#if 0
#define sph20_numV 12
VPRIVATE float sph20_V[sph20_numV][3] = {
{ -5.257e-01,  0.000e+00,  8.507e-01 },
{  5.257e-01,  0.000e+00,  8.507e-01 },
{ -5.257e-01,  0.000e+00, -8.507e-01 },
{  5.257e-01,  0.000e+00, -8.507e-01 },
{  0.000e+00,  8.507e-01,  5.257e-01 },
{  0.000e+00,  8.507e-01, -5.257e-01 },
{  0.000e+00, -8.507e-01,  5.257e-01 },
{  0.000e+00, -8.507e-01, -5.257e-01 },
{  8.507e-01,  5.257e-01,  0.000e+00 },
{ -8.507e-01,  5.257e-01,  0.000e+00 },
{  8.507e-01, -5.257e-01,  0.000e+00 },
{ -8.507e-01, -5.257e-01,  0.000e+00 }
};
#define sph20_numS 20
VPRIVATE int sph20_S[sph20_numS][3] = {
{  0,  1,  4 },
{  0,  4,  9 },
{  9,  4,  5 },
{  4,  8,  5 },
{  4,  1,  8 },
{  8,  1, 10 },
{  8, 10,  3 },
{  5,  8,  3 },
{  5,  3,  2 },
{  2,  3,  7 },
{  7,  3, 10 },
{  7, 10,  6 },
{  7,  6, 11 },
{ 11,  6,  0 },
{  0,  6,  1 },
{  6, 10,  1 },
{  9, 11,  0 },
{  9,  2, 11 },
{  9,  5,  2 },
{  7, 11,  2 }
};
#endif

#define sph80_numV 42
VPRIVATE float sph80_V[sph80_numV][3] = {
{ -5.257e-01,  0.000e+00,  8.507e-01 },
{  5.257e-01,  0.000e+00,  8.507e-01 },
{ -5.257e-01,  0.000e+00, -8.507e-01 },
{  5.257e-01,  0.000e+00, -8.507e-01 },
{  0.000e+00,  8.507e-01,  5.257e-01 },
{  0.000e+00,  8.507e-01, -5.257e-01 },
{  0.000e+00, -8.507e-01,  5.257e-01 },
{  0.000e+00, -8.507e-01, -5.257e-01 },
{  8.507e-01,  5.257e-01,  0.000e+00 },
{ -8.507e-01,  5.257e-01,  0.000e+00 },
{  8.507e-01, -5.257e-01,  0.000e+00 },
{ -8.507e-01, -5.257e-01,  0.000e+00 },
{ -3.090e-01,  5.000e-01,  8.090e-01 },
{  3.090e-01,  5.000e-01,  8.090e-01 },
{  0.000e+00,  0.000e+00,  1.000e+00 },
{ -8.090e-01,  3.090e-01,  5.000e-01 },
{ -5.000e-01,  8.090e-01,  3.090e-01 },
{ -5.000e-01,  8.090e-01, -3.090e-01 },
{  0.000e+00,  1.000e+00,  0.000e+00 },
{  5.000e-01,  8.090e-01,  3.090e-01 },
{  5.000e-01,  8.090e-01, -3.090e-01 },
{  8.090e-01,  3.090e-01,  5.000e-01 },
{  1.000e+00,  0.000e+00,  0.000e+00 },
{  8.090e-01, -3.090e-01,  5.000e-01 },
{  8.090e-01,  3.090e-01, -5.000e-01 },
{  8.090e-01, -3.090e-01, -5.000e-01 },
{  3.090e-01,  5.000e-01, -8.090e-01 },
{ -3.090e-01,  5.000e-01, -8.090e-01 },
{  0.000e+00,  0.000e+00, -1.000e+00 },
{ -3.090e-01, -5.000e-01, -8.090e-01 },
{  3.090e-01, -5.000e-01, -8.090e-01 },
{  5.000e-01, -8.090e-01, -3.090e-01 },
{  5.000e-01, -8.090e-01,  3.090e-01 },
{  0.000e+00, -1.000e+00,  0.000e+00 },
{ -5.000e-01, -8.090e-01,  3.090e-01 },
{ -5.000e-01, -8.090e-01, -3.090e-01 },
{ -3.090e-01, -5.000e-01,  8.090e-01 },
{ -8.090e-01, -3.090e-01,  5.000e-01 },
{  3.090e-01, -5.000e-01,  8.090e-01 },
{ -1.000e+00,  0.000e+00,  0.000e+00 },
{ -8.090e-01,  3.090e-01, -5.000e-01 },
{ -8.090e-01, -3.090e-01, -5.000e-01 }
};
#if 0
#define sph80_numS 80
VPRIVATE int sph80_S[sph80_numS][3] = {
{  4, 12, 13 },
{  0, 12, 15 },
{  9, 16, 17 },
{  4, 19, 18 },
{  4, 13, 19 },
{  8, 21, 22 },
{  3, 24, 25 },
{  3, 26, 24 },
{  2, 27, 28 },
{  7, 29, 30 },
{  7, 30, 31 },
{ 10, 32, 31 },
{  6, 34, 33 },
{  6, 36, 34 },
{  0, 36, 14 },
{  1, 38, 23 },
{  0, 15, 37 },
{  9, 40, 39 },
{  5, 27, 17 },
{  2, 29, 41 },
{  0, 14, 12 },
{  1, 13, 14 },
{ 14, 13, 12 },
{  4, 16, 12 },
{  9, 15, 16 },
{ 16, 15, 12 },
{  4, 18, 16 },
{  5, 17, 18 },
{ 18, 17, 16 },
{  8, 20, 19 },
{  5, 18, 20 },
{ 20, 18, 19 },
{  1, 21, 13 },
{  8, 19, 21 },
{ 21, 19, 13 },
{  1, 23, 21 },
{ 10, 22, 23 },
{ 23, 22, 21 },
{  8, 22, 24 },
{ 10, 25, 22 },
{ 22, 25, 24 },
{  5, 20, 26 },
{  8, 24, 20 },
{ 20, 24, 26 },
{  5, 26, 27 },
{  3, 28, 26 },
{ 26, 28, 27 },
{  2, 28, 29 },
{  3, 30, 28 },
{ 28, 30, 29 },
{  3, 25, 30 },
{ 10, 31, 25 },
{ 25, 31, 30 },
{  6, 33, 32 },
{  7, 31, 33 },
{ 33, 31, 32 },
{ 11, 35, 34 },
{  7, 33, 35 },
{ 35, 33, 34 },
{  0, 37, 36 },
{ 11, 34, 37 },
{ 37, 34, 36 },
{  6, 38, 36 },
{  1, 14, 38 },
{ 38, 14, 36 },
{  6, 32, 38 },
{ 10, 23, 32 },
{ 32, 23, 38 },
{  9, 39, 15 },
{ 11, 37, 39 },
{ 39, 37, 15 },
{  2, 41, 40 },
{ 11, 39, 41 },
{ 41, 39, 40 },
{  2, 40, 27 },
{  9, 17, 40 },
{ 40, 17, 27 },
{  7, 35, 29 },
{ 11, 41, 35 },
{ 35, 41, 29 }
};
#endif

#define sph320_numV 162
VPRIVATE float sph320_V[sph320_numV][3] = {
{ -5.2573110000e-01,  0.0000000000e+00,  8.5065080000e-01 },
{  5.2573110000e-01,  0.0000000000e+00,  8.5065080000e-01 },
{ -5.2573110000e-01,  0.0000000000e+00, -8.5065080000e-01 },
{  5.2573110000e-01,  0.0000000000e+00, -8.5065080000e-01 },
{  0.0000000000e+00,  8.5065080000e-01,  5.2573110000e-01 },
{  0.0000000000e+00,  8.5065080000e-01, -5.2573110000e-01 },
{  0.0000000000e+00, -8.5065080000e-01,  5.2573110000e-01 },
{  0.0000000000e+00, -8.5065080000e-01, -5.2573110000e-01 },
{  8.5065080000e-01,  5.2573110000e-01,  0.0000000000e+00 },
{ -8.5065080000e-01,  5.2573110000e-01,  0.0000000000e+00 },
{  8.5065080000e-01, -5.2573110000e-01,  0.0000000000e+00 },
{ -8.5065080000e-01, -5.2573110000e-01,  0.0000000000e+00 },
{ -3.0901699170e-01,  5.0000000229e-01,  8.0901699398e-01 },
{  3.0901699170e-01,  5.0000000229e-01,  8.0901699398e-01 },
{  0.0000000000e+00,  0.0000000000e+00,  1.0000000000e+00 },
{ -8.0901699398e-01,  3.0901699170e-01,  5.0000000229e-01 },
{ -5.0000000229e-01,  8.0901699398e-01,  3.0901699170e-01 },
{ -5.0000000229e-01,  8.0901699398e-01, -3.0901699170e-01 },
{  0.0000000000e+00,  1.0000000000e+00,  0.0000000000e+00 },
{  5.0000000229e-01,  8.0901699398e-01,  3.0901699170e-01 },
{  5.0000000229e-01,  8.0901699398e-01, -3.0901699170e-01 },
{  8.0901699398e-01,  3.0901699170e-01,  5.0000000229e-01 },
{  1.0000000000e+00,  0.0000000000e+00,  0.0000000000e+00 },
{  8.0901699398e-01, -3.0901699170e-01,  5.0000000229e-01 },
{  8.0901699398e-01,  3.0901699170e-01, -5.0000000229e-01 },
{  8.0901699398e-01, -3.0901699170e-01, -5.0000000229e-01 },
{  3.0901699170e-01,  5.0000000229e-01, -8.0901699398e-01 },
{ -3.0901699170e-01,  5.0000000229e-01, -8.0901699398e-01 },
{  0.0000000000e+00,  0.0000000000e+00, -1.0000000000e+00 },
{ -3.0901699170e-01, -5.0000000229e-01, -8.0901699398e-01 },
{  3.0901699170e-01, -5.0000000229e-01, -8.0901699398e-01 },
{  5.0000000229e-01, -8.0901699398e-01, -3.0901699170e-01 },
{  5.0000000229e-01, -8.0901699398e-01,  3.0901699170e-01 },
{  0.0000000000e+00, -1.0000000000e+00,  0.0000000000e+00 },
{ -5.0000000229e-01, -8.0901699398e-01,  3.0901699170e-01 },
{ -5.0000000229e-01, -8.0901699398e-01, -3.0901699170e-01 },
{ -3.0901699170e-01, -5.0000000229e-01,  8.0901699398e-01 },
{ -8.0901699398e-01, -3.0901699170e-01,  5.0000000229e-01 },
{  3.0901699170e-01, -5.0000000229e-01,  8.0901699398e-01 },
{ -1.0000000000e+00,  0.0000000000e+00,  0.0000000000e+00 },
{ -8.0901699398e-01,  3.0901699170e-01, -5.0000000229e-01 },
{ -8.0901699398e-01, -3.0901699170e-01, -5.0000000229e-01 },
{  0.0000000000e+00,  5.2573111404e-01,  8.5065080716e-01 },
{ -1.6062203536e-01,  7.0204644650e-01,  6.9378047588e-01 },
{  1.6062203536e-01,  7.0204644650e-01,  6.9378047588e-01 },
{ -5.8778525089e-01,  4.2532540412e-01,  6.8819096147e-01 },
{ -4.3388855988e-01,  2.5989191600e-01,  8.6266848187e-01 },
{ -6.9378047588e-01,  1.6062203536e-01,  7.0204644650e-01 },
{ -5.2573111404e-01,  8.5065080716e-01,  0.0000000000e+00 },
{ -7.0204644650e-01,  6.9378047588e-01,  1.6062203536e-01 },
{ -7.0204644650e-01,  6.9378047588e-01, -1.6062203536e-01 },
{  2.6286555729e-01,  9.5105651619e-01,  1.6245984673e-01 },
{  2.5989191600e-01,  8.6266848187e-01,  4.3388855988e-01 },
{  0.0000000000e+00,  9.6193835912e-01,  2.7326652422e-01 },
{  4.2532540412e-01,  6.8819096147e-01,  5.8778525089e-01 },
{  9.5105651619e-01,  1.6245984673e-01,  2.6286555729e-01 },
{  8.6266848187e-01,  4.3388855988e-01,  2.5989191600e-01 },
{  9.6193835912e-01,  2.7326652422e-01,  0.0000000000e+00 },
{  8.5065080716e-01,  0.0000000000e+00, -5.2573111404e-01 },
{  6.9378047588e-01,  1.6062203536e-01, -7.0204644650e-01 },
{  6.9378047588e-01, -1.6062203536e-01, -7.0204644650e-01 },
{  5.8778525089e-01,  4.2532540412e-01, -6.8819096147e-01 },
{  4.3388855988e-01,  2.5989191600e-01, -8.6266848187e-01 },
{ -1.6245984673e-01,  2.6286555729e-01, -9.5105651619e-01 },
{ -4.3388855988e-01,  2.5989191600e-01, -8.6266848187e-01 },
{ -2.7326652422e-01,  0.0000000000e+00, -9.6193835912e-01 },
{  0.0000000000e+00, -5.2573111404e-01, -8.5065080716e-01 },
{ -1.6062203536e-01, -7.0204644650e-01, -6.9378047588e-01 },
{  1.6062203536e-01, -7.0204644650e-01, -6.9378047588e-01 },
{  4.2532540412e-01, -6.8819096147e-01, -5.8778525089e-01 },
{  2.5989191600e-01, -8.6266848187e-01, -4.3388855988e-01 },
{  5.2573111404e-01, -8.5065080716e-01,  0.0000000000e+00 },
{  7.0204644650e-01, -6.9378047588e-01,  1.6062203536e-01 },
{  7.0204644650e-01, -6.9378047588e-01, -1.6062203536e-01 },
{ -2.6286555729e-01, -9.5105651619e-01,  1.6245984673e-01 },
{ -2.5989191600e-01, -8.6266848187e-01,  4.3388855988e-01 },
{  0.0000000000e+00, -9.6193835912e-01,  2.7326652422e-01 },
{ -4.2532540412e-01, -6.8819096147e-01,  5.8778525089e-01 },
{ -1.6062203536e-01, -7.0204644650e-01,  6.9378047588e-01 },
{ -1.6245984673e-01, -2.6286555729e-01,  9.5105651619e-01 },
{ -4.3388855988e-01, -2.5989191600e-01,  8.6266848187e-01 },
{ -2.7326652422e-01,  0.0000000000e+00,  9.6193835912e-01 },
{  5.8778525089e-01, -4.2532540412e-01,  6.8819096147e-01 },
{  4.3388855988e-01, -2.5989191600e-01,  8.6266848187e-01 },
{  6.9378047588e-01, -1.6062203536e-01,  7.0204644650e-01 },
{ -8.5065080716e-01,  0.0000000000e+00,  5.2573111404e-01 },
{ -6.9378047588e-01, -1.6062203536e-01,  7.0204644650e-01 },
{ -9.5105651619e-01,  1.6245984673e-01, -2.6286555729e-01 },
{ -8.6266848187e-01,  4.3388855988e-01, -2.5989191600e-01 },
{ -9.6193835912e-01,  2.7326652422e-01,  0.0000000000e+00 },
{ -4.2532540412e-01,  6.8819096147e-01, -5.8778525089e-01 },
{ -1.6062203536e-01,  7.0204644650e-01, -6.9378047588e-01 },
{ -2.5989191600e-01,  8.6266848187e-01, -4.3388855988e-01 },
{ -5.8778525089e-01, -4.2532540412e-01, -6.8819096147e-01 },
{ -4.3388855988e-01, -2.5989191600e-01, -8.6266848187e-01 },
{ -6.9378047588e-01, -1.6062203536e-01, -7.0204644650e-01 },
{ -1.6245984673e-01,  2.6286555729e-01,  9.5105651619e-01 },
{  1.6245984673e-01,  2.6286555729e-01,  9.5105651619e-01 },
{  4.3388855988e-01,  2.5989191600e-01,  8.6266848187e-01 },
{  2.7326652422e-01,  0.0000000000e+00,  9.6193835912e-01 },
{ -4.2532540412e-01,  6.8819096147e-01,  5.8778525089e-01 },
{ -2.5989191600e-01,  8.6266848187e-01,  4.3388855988e-01 },
{ -6.8819096147e-01,  5.8778525089e-01,  4.2532540412e-01 },
{ -8.6266848187e-01,  4.3388855988e-01,  2.5989191600e-01 },
{ -2.6286555729e-01,  9.5105651619e-01,  1.6245984673e-01 },
{ -2.6286555729e-01,  9.5105651619e-01, -1.6245984673e-01 },
{  0.0000000000e+00,  9.6193835912e-01, -2.7326652422e-01 },
{  5.2573111404e-01,  8.5065080716e-01,  0.0000000000e+00 },
{  7.0204644650e-01,  6.9378047588e-01, -1.6062203536e-01 },
{  7.0204644650e-01,  6.9378047588e-01,  1.6062203536e-01 },
{  2.6286555729e-01,  9.5105651619e-01, -1.6245984673e-01 },
{  2.5989191600e-01,  8.6266848187e-01, -4.3388855988e-01 },
{  5.8778525089e-01,  4.2532540412e-01,  6.8819096147e-01 },
{  6.9378047588e-01,  1.6062203536e-01,  7.0204644650e-01 },
{  6.8819096147e-01,  5.8778525089e-01,  4.2532540412e-01 },
{  8.5065080716e-01,  0.0000000000e+00,  5.2573111404e-01 },
{  9.5105651619e-01, -1.6245984673e-01,  2.6286555729e-01 },
{  9.6193835912e-01, -2.7326652422e-01,  0.0000000000e+00 },
{  8.6266848187e-01, -4.3388855988e-01,  2.5989191600e-01 },
{  9.5105651619e-01,  1.6245984673e-01, -2.6286555729e-01 },
{  8.6266848187e-01,  4.3388855988e-01, -2.5989191600e-01 },
{  9.5105651619e-01, -1.6245984673e-01, -2.6286555729e-01 },
{  8.6266848187e-01, -4.3388855988e-01, -2.5989191600e-01 },
{  4.2532540412e-01,  6.8819096147e-01, -5.8778525089e-01 },
{  1.6062203536e-01,  7.0204644650e-01, -6.9378047588e-01 },
{  6.8819096147e-01,  5.8778525089e-01, -4.2532540412e-01 },
{  0.0000000000e+00,  5.2573111404e-01, -8.5065080716e-01 },
{  1.6245984673e-01,  2.6286555729e-01, -9.5105651619e-01 },
{  2.7326652422e-01,  0.0000000000e+00, -9.6193835912e-01 },
{ -1.6245984673e-01, -2.6286555729e-01, -9.5105651619e-01 },
{  1.6245984673e-01, -2.6286555729e-01, -9.5105651619e-01 },
{  4.3388855988e-01, -2.5989191600e-01, -8.6266848187e-01 },
{  5.8778525089e-01, -4.2532540412e-01, -6.8819096147e-01 },
{  6.8819096147e-01, -5.8778525089e-01, -4.2532540412e-01 },
{  2.6286555729e-01, -9.5105651619e-01,  1.6245984673e-01 },
{  2.5989191600e-01, -8.6266848187e-01,  4.3388855988e-01 },
{  2.6286555729e-01, -9.5105651619e-01, -1.6245984673e-01 },
{  0.0000000000e+00, -9.6193835912e-01, -2.7326652422e-01 },
{ -5.2573111404e-01, -8.5065080716e-01,  0.0000000000e+00 },
{ -7.0204644650e-01, -6.9378047588e-01, -1.6062203536e-01 },
{ -7.0204644650e-01, -6.9378047588e-01,  1.6062203536e-01 },
{ -2.6286555729e-01, -9.5105651619e-01, -1.6245984673e-01 },
{ -2.5989191600e-01, -8.6266848187e-01, -4.3388855988e-01 },
{ -5.8778525089e-01, -4.2532540412e-01,  6.8819096147e-01 },
{ -6.8819096147e-01, -5.8778525089e-01,  4.2532540412e-01 },
{ -8.6266848187e-01, -4.3388855988e-01,  2.5989191600e-01 },
{  0.0000000000e+00, -5.2573111404e-01,  8.5065080716e-01 },
{  1.6062203536e-01, -7.0204644650e-01,  6.9378047588e-01 },
{  1.6245984673e-01, -2.6286555729e-01,  9.5105651619e-01 },
{  4.2532540412e-01, -6.8819096147e-01,  5.8778525089e-01 },
{  6.8819096147e-01, -5.8778525089e-01,  4.2532540412e-01 },
{ -9.5105651619e-01,  1.6245984673e-01,  2.6286555729e-01 },
{ -9.5105651619e-01, -1.6245984673e-01,  2.6286555729e-01 },
{ -9.6193835912e-01, -2.7326652422e-01,  0.0000000000e+00 },
{ -8.5065080716e-01,  0.0000000000e+00, -5.2573111404e-01 },
{ -6.9378047588e-01,  1.6062203536e-01, -7.0204644650e-01 },
{ -9.5105651619e-01, -1.6245984673e-01, -2.6286555729e-01 },
{ -8.6266848187e-01, -4.3388855988e-01, -2.5989191600e-01 },
{ -5.8778525089e-01,  4.2532540412e-01, -6.8819096147e-01 },
{ -6.8819096147e-01,  5.8778525089e-01, -4.2532540412e-01 },
{ -4.2532540412e-01, -6.8819096147e-01, -5.8778525089e-01 },
{ -6.8819096147e-01, -5.8778525089e-01, -4.2532540412e-01 }
};
#if 0
#define sph320_numS 320
VPRIVATE int sph320_S[sph320_numS][3] = {
{ 12, 42, 43 },
{ 12, 45, 46 },
{ 16, 48, 49 },
{ 19, 51, 52 },
{ 13, 54, 44 },
{ 21, 55, 56 },
{ 24, 58, 59 },
{ 26, 61, 62 },
{ 27, 63, 64 },
{ 29, 66, 67 },
{ 30, 69, 68 },
{ 32, 71, 72 },
{ 34, 74, 75 },
{ 36, 77, 78 },
{ 36, 79, 80 },
{ 38, 82, 83 },
{ 15, 85, 47 },
{ 40, 87, 88 },
{ 27, 90, 91 },
{ 29, 93, 94 },
{ 14, 96, 81 },
{ 13, 97, 98 },
{ 12, 96, 42 },
{ 16, 100, 101 },
{ 15, 102, 103 },
{ 15, 45, 102 },
{ 18, 104, 53 },
{ 17, 105, 92 },
{ 16, 104, 48 },
{ 20, 107, 108 },
{ 18, 110, 106 },
{ 18, 51, 110 },
{ 21, 112, 113 },
{ 19, 114, 109 },
{ 19, 54, 114 },
{ 23, 115, 84 },
{ 22, 116, 117 },
{ 22, 55, 116 },
{ 22, 119, 57 },
{ 25, 121, 122 },
{ 24, 119, 58 },
{ 20, 123, 111 },
{ 24, 125, 120 },
{ 20, 125, 123 },
{ 26, 126, 124 },
{ 28, 127, 128 },
{ 26, 127, 126 },
{ 28, 129, 65 },
{ 30, 130, 131 },
{ 29, 129, 66 },
{ 25, 132, 60 },
{ 31, 133, 73 },
{ 30, 132, 69 },
{ 33, 134, 76 },
{ 31, 136, 70 },
{ 33, 136, 134 },
{ 35, 138, 139 },
{ 33, 141, 137 },
{ 33, 74, 141 },
{ 37, 143, 86 },
{ 34, 144, 140 },
{ 34, 77, 144 },
{ 38, 146, 147 },
{ 14, 148, 99 },
{ 14, 79, 148 },
{ 32, 149, 135 },
{ 23, 150, 118 },
{ 32, 150, 149 },
{ 39, 151, 89 },
{ 37, 152, 145 },
{ 15, 151, 85 },
{ 41, 154, 95 },
{ 39, 156, 153 },
{ 39, 87, 156 },
{ 40, 158, 155 },
{ 17, 159, 50 },
{ 17, 90, 159 },
{ 35, 160, 142 },
{ 41, 161, 157 },
{ 29, 160, 93 },
{ 13, 44, 42 },
{ 4, 43, 44 },
{ 44, 43, 42 },
{ 15, 47, 45 },
{ 0, 46, 47 },
{ 47, 46, 45 },
{ 17, 50, 48 },
{ 9, 49, 50 },
{ 50, 49, 48 },
{ 18, 53, 51 },
{ 4, 52, 53 },
{ 53, 52, 51 },
{ 19, 52, 54 },
{ 4, 44, 52 },
{ 52, 44, 54 },
{ 22, 57, 55 },
{ 8, 56, 57 },
{ 57, 56, 55 },
{ 25, 60, 58 },
{ 3, 59, 60 },
{ 60, 59, 58 },
{ 24, 59, 61 },
{ 3, 62, 59 },
{ 59, 62, 61 },
{ 28, 65, 63 },
{ 2, 64, 65 },
{ 65, 64, 63 },
{ 30, 68, 66 },
{ 7, 67, 68 },
{ 68, 67, 66 },
{ 31, 70, 69 },
{ 7, 68, 70 },
{ 70, 68, 69 },
{ 31, 73, 71 },
{ 10, 72, 73 },
{ 73, 72, 71 },
{ 33, 76, 74 },
{ 6, 75, 76 },
{ 76, 75, 74 },
{ 34, 75, 77 },
{ 6, 78, 75 },
{ 75, 78, 77 },
{ 14, 81, 79 },
{ 0, 80, 81 },
{ 81, 80, 79 },
{ 23, 84, 82 },
{ 1, 83, 84 },
{ 84, 83, 82 },
{ 37, 86, 85 },
{ 0, 47, 86 },
{ 86, 47, 85 },
{ 39, 89, 87 },
{ 9, 88, 89 },
{ 89, 88, 87 },
{ 17, 92, 90 },
{ 5, 91, 92 },
{ 92, 91, 90 },
{ 41, 95, 93 },
{ 2, 94, 95 },
{ 95, 94, 93 },
{ 12, 46, 96 },
{ 0, 81, 46 },
{ 46, 81, 96 },
{ 14, 99, 97 },
{ 1, 98, 99 },
{ 99, 98, 97 },
{ 14, 97, 96 },
{ 13, 42, 97 },
{ 97, 42, 96 },
{ 12, 43, 100 },
{ 4, 101, 43 },
{ 43, 101, 100 },
{ 16, 49, 102 },
{ 9, 103, 49 },
{ 49, 103, 102 },
{ 12, 100, 45 },
{ 16, 102, 100 },
{ 100, 102, 45 },
{ 16, 101, 104 },
{ 4, 53, 101 },
{ 101, 53, 104 },
{ 18, 106, 105 },
{ 5, 92, 106 },
{ 106, 92, 105 },
{ 18, 105, 104 },
{ 17, 48, 105 },
{ 105, 48, 104 },
{ 19, 109, 107 },
{ 8, 108, 109 },
{ 109, 108, 107 },
{ 20, 111, 110 },
{ 5, 106, 111 },
{ 111, 106, 110 },
{ 19, 107, 51 },
{ 20, 110, 107 },
{ 107, 110, 51 },
{ 13, 98, 112 },
{ 1, 113, 98 },
{ 98, 113, 112 },
{ 21, 56, 114 },
{ 8, 109, 56 },
{ 56, 109, 114 },
{ 13, 112, 54 },
{ 21, 114, 112 },
{ 112, 114, 54 },
{ 21, 113, 115 },
{ 1, 84, 113 },
{ 113, 84, 115 },
{ 23, 118, 116 },
{ 10, 117, 118 },
{ 118, 117, 116 },
{ 21, 115, 55 },
{ 23, 116, 115 },
{ 115, 116, 55 },
{ 24, 120, 119 },
{ 8, 57, 120 },
{ 120, 57, 119 },
{ 22, 117, 121 },
{ 10, 122, 117 },
{ 117, 122, 121 },
{ 22, 121, 119 },
{ 25, 58, 121 },
{ 121, 58, 119 },
{ 26, 124, 123 },
{ 5, 111, 124 },
{ 124, 111, 123 },
{ 20, 108, 125 },
{ 8, 120, 108 },
{ 108, 120, 125 },
{ 24, 61, 125 },
{ 26, 123, 61 },
{ 61, 123, 125 },
{ 27, 91, 126 },
{ 5, 124, 91 },
{ 91, 124, 126 },
{ 26, 62, 127 },
{ 3, 128, 62 },
{ 62, 128, 127 },
{ 28, 63, 127 },
{ 27, 126, 63 },
{ 63, 126, 127 },
{ 29, 94, 129 },
{ 2, 65, 94 },
{ 94, 65, 129 },
{ 28, 128, 130 },
{ 3, 131, 128 },
{ 128, 131, 130 },
{ 28, 130, 129 },
{ 30, 66, 130 },
{ 130, 66, 129 },
{ 30, 131, 132 },
{ 3, 60, 131 },
{ 131, 60, 132 },
{ 25, 122, 133 },
{ 10, 73, 122 },
{ 122, 73, 133 },
{ 25, 133, 132 },
{ 31, 69, 133 },
{ 133, 69, 132 },
{ 32, 135, 134 },
{ 6, 76, 135 },
{ 135, 76, 134 },
{ 33, 137, 136 },
{ 7, 70, 137 },
{ 137, 70, 136 },
{ 31, 71, 136 },
{ 32, 134, 71 },
{ 71, 134, 136 },
{ 34, 140, 138 },
{ 11, 139, 140 },
{ 140, 139, 138 },
{ 35, 142, 141 },
{ 7, 137, 142 },
{ 142, 137, 141 },
{ 34, 138, 74 },
{ 35, 141, 138 },
{ 138, 141, 74 },
{ 36, 80, 143 },
{ 0, 86, 80 },
{ 80, 86, 143 },
{ 37, 145, 144 },
{ 11, 140, 145 },
{ 145, 140, 144 },
{ 36, 143, 77 },
{ 37, 144, 143 },
{ 143, 144, 77 },
{ 36, 78, 146 },
{ 6, 147, 78 },
{ 78, 147, 146 },
{ 38, 83, 148 },
{ 1, 99, 83 },
{ 83, 99, 148 },
{ 36, 146, 79 },
{ 38, 148, 146 },
{ 146, 148, 79 },
{ 38, 147, 149 },
{ 6, 135, 147 },
{ 147, 135, 149 },
{ 32, 72, 150 },
{ 10, 118, 72 },
{ 72, 118, 150 },
{ 23, 82, 150 },
{ 38, 149, 82 },
{ 82, 149, 150 },
{ 15, 103, 151 },
{ 9, 89, 103 },
{ 103, 89, 151 },
{ 39, 153, 152 },
{ 11, 145, 153 },
{ 153, 145, 152 },
{ 39, 152, 151 },
{ 37, 85, 152 },
{ 152, 85, 151 },
{ 40, 155, 154 },
{ 2, 95, 155 },
{ 155, 95, 154 },
{ 41, 157, 156 },
{ 11, 153, 157 },
{ 157, 153, 156 },
{ 40, 154, 87 },
{ 41, 156, 154 },
{ 154, 156, 87 },
{ 27, 64, 158 },
{ 2, 155, 64 },
{ 64, 155, 158 },
{ 40, 88, 159 },
{ 9, 50, 88 },
{ 88, 50, 159 },
{ 27, 158, 90 },
{ 40, 159, 158 },
{ 158, 159, 90 },
{ 29, 67, 160 },
{ 7, 142, 67 },
{ 67, 142, 160 },
{ 35, 139, 161 },
{ 11, 157, 139 },
{ 139, 157, 161 },
{ 35, 161, 160 },
{ 41, 93, 161 },
{ 161, 93, 160 }
};
#endif

/*
 * ***************************************************************************
 * Class Ogl: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_OGL)
#endif /* if !defined(VINLINE_OGL) */

/*
 * ***************************************************************************
 * Class Ogl: Non-inlineable methods
 * ***************************************************************************
 */

VPUBLIC Ogl* Ogl_ctor(int frameMode, int orthoMode)
{
    int i;
    Ogl *thee = VNULL;

    thee = (Ogl*)calloc( 1, sizeof(Ogl) );
    VJMPERR1( thee != VNULL );

    /* one-time initialization of main view parameters */
    thee->frameMode  = frameMode; /* frame (0=centered, 1=offset) */
    thee->orthoMode  = orthoMode;  /* projection (0=perspect, 1=ortho) */

    /* initialization of main view parameters */
    thee->lightMode  = 1;         /* lighting (0=no, 1=yes) */
    thee->ballMode   = 0;         /* draw (0=none, 1=draw arcball) */
    thee->bboxMode   = 0;         /* draw (0=none, 1=draw bounding box) */
    thee->backMode   = 1;         /* polybackside dark paint (0=no, 1=yes) */
    thee->mouseMode  = 0;         /* mouse (0=rotate, 1=scale, 2=translate) */
    thee->mouseDown  = 0;         /* is mouse button pressed (0=no, 1=yes) */
    thee->scale      = 1.0;       /* current global scaling */
    thee->eyezInit   = 3.0;       /* current eye position up the z-axis */
    thee->viewWidth  = 0;         /* width of the plotbox */
    thee->viewHeight = 0;         /* height of the plotbox */

    /* display list initialization */
    for (i=0; i<10; i++) {
        thee->list[i] = 0;
        thee->listMode[i] = 0;
    }
    thee->ball = 0;
    thee->bbox = 0;
    thee->bboxUpdate = 0;

    /* additional view parameter initialization; can be reset the user */
    initView(thee);

    /* initialize lighting and effects */
    setEffects(thee);
    setLights(thee);

    /* default bbox */
    clearBBox(thee);

    /* normal return */
    return thee;

  VERROR1:
    /* something went wrong */
    fprintf(stderr,"Ogl_ctor: problem initalizing.\n"); 
    return VNULL;
}

VPUBLIC void Ogl_dtor(Ogl **thee)
{
    if ((*thee) != VNULL) {
        free( *thee );
        (*thee) = VNULL;
    }
}

/*
 * ***************************************************************************
 * Purpose:  Initialize the OpenGL context.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Ogl_initBegin(Ogl *thee)
{
    int i;
    clearBBox(thee);
    if ( glIsList(thee->ball) ) {
        glDeleteLists(thee->ball,1);
        thee->ball = 0;
    }
    if ( glIsList(thee->bbox) ) {
        glDeleteLists(thee->bbox,1);
        thee->bbox = 0;
    }
    for (i=0; i<10; i++) {
        if ( glIsList(thee->list[i]) ) {
            glDeleteLists(thee->list[i],1);
            thee->list[i] = 0;
            thee->listMode[i] = 0;
        }
    }
}
VPUBLIC void Ogl_initEnd(Ogl *thee)
{
    makeBBox(thee);
    makeBBoxList(thee);
    makeBallList(thee);
}

/*
 * ***************************************************************************
 * Purpose:  The main 3D==>2D Projection function.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Ogl_reshape(Ogl *thee, int w, int h)
{
    thee->viewWidth  = w;
    thee->viewHeight = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (thee->orthoMode) {
        if (thee->frameMode) {
            glOrtho( -1.0001, 2.0001, -1.0001, 1.0001, -1.0, 20.0 );
        } else {
            glOrtho( -1.0001, 1.0001, -1.0001, 1.0001, -1.0, 20.0 );
        }
    } else {
        gluPerspective(45.0, (double)w / (double)h, 0.01, 20.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    setLights(thee);
}

/*
 * ***************************************************************************
 * Purpose:  Main OpenGL display driver.
 *
 * Notes:    We use the Z-buffer here for hidden line and hidden surface
 *           removal.  We just have to make sure that we get a visual
 *           device with some Z-buffer bits, and that we don't mess up the
 *           transformations so that the Z-axis points somewhere other than
 *           positively straight at the eye.
 *
 * Frame codes:
 *
 *           If "frameMode==0", we draw only the frame 4 lists (4-9),
 *           centered in frame 1 show below, regardless of window shape.
 *
 *           If "frameMode==1", we draw frame 1,2,3,4 lists (0-9), in the
 *           appropriate frames.
 *
 *      ._____._____._____.     ._____._____._____.     ._____._____.......
 *      |                 |     |           |     |     |           |     .
 *      |                 |     |           |  2  |     |           |     .
 *      |        1        |     |     4     |_____|     |     ?     |......
 *      |                 |     |           |     |     |           |     .
 *      |                 |     |           |  3  |     |           |     .
 *      |_____._____._____|     |_____._____|_____|     |_____._____.......
 *
 * Display list codes:
 *
 *      List   Frame     Type
 *
 *         0       1     non-rotating, non-lighted
 *         1       1     non-rotating, non-lighted
 *         2       2     non-rotating, non-lighted
 *         3       3     non-rotating, non-lighted
 *
 *         4       4     non-rotating, non-lighted
 *         5       4         rotating, non-lighted
 *         6       4         rotating, non-lighted
 *         7       4         rotating,     lighted
 *         8       4         rotating,     lighted
 *         9       4     non-rotating,     lighted
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Ogl_display(Ogl *thee)
{
    int i, lightSave;
    float quat[4], m[4][4];

    /* clear the OpenGL buffer and push matrix transformations on the stack */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
     * HACK: This empty glBegin/glEnd is required to get the buggy
     *       nVidia OpenGL libraries to do two-sided lighting effects
     *       correctly.
     */       
#if 1
    glBegin(GL_LINES);
    glEnd();
#endif

    glPushMatrix();

        /* setup the view (handles possible translation) */
        if (thee->orthoMode) {
            gluLookAt( thee->eye[0],    thee->eye[1],    thee->eye[2],
                       thee->origin[0], thee->origin[1], thee->origin[2],
                       0.0, 1.0, 0.0 );
        } else {
            gluLookAt( thee->eye[0],    thee->eye[1],    thee->eye[2],
                       thee->origin[0], thee->origin[1], thee->origin[2],
                       0.0, 1.0, 0.0 );
            if (thee->frameMode) {
                glTranslatef( -0.5, 0.0, 0.0 );
            }
        }

        /* translation fix for left-shifted rotation origin in a wide window */

        /* call list=9 (lighted, but not rotated) */
        if (thee->listMode[9] == 1)
            if ( glIsList(thee->list[9]) )
                glCallList(thee->list[9]);

        glPushMatrix();

            /* global scaling and translation */
            glScalef( 1./thee->scale, 1./thee->scale, 1./thee->scale );
            glTranslatef( thee->trans[0], thee->trans[1], thee->trans[2] );

            /* call dragarc display list (lighted, but not rotated) */
            if (    (thee->ballMode  == 1)
                 && (thee->mouseMode == 0)
                 && (thee->mouseDown >  0) ) dragBall(thee);

            /* compute the rotation */
            addQuat(thee->quatDrag, thee->quat, quat);
            buildRotation(m, quat);
            glMultMatrixf(&m[0][0]);

            /* call trackball list (lighted, and rotated) */
            if (thee->ballMode == 1)
                if ( glIsList(thee->ball) )
                    glCallList(thee->ball);

            /* call list=8,7 (lighted, and rotated) */
            for (i=7; i<=8; i++) {
                if (thee->listMode[i] == 1)
                    if ( glIsList(thee->list[i]) )
                        glCallList(thee->list[i]);
            }

            /* turn the lights out */
            lightSave = thee->lightMode;
            thee->lightMode = 0;
            setLights(thee);

            /* call list=6,5 (not lighted, but rotated) */
            for (i=5; i<=6; i++) {
                if (thee->listMode[i] == 1)
                    if ( glIsList(thee->list[i]) )
                        glCallList(thee->list[i]);
            }

            /* call the bounding box list (not lighted, but rotated) */
            if (thee->bboxMode == 1)
                if ( glIsList(thee->bbox) )
                    glCallList(thee->bbox);

        glPopMatrix();

        /* call list=4 (not lighted, not rotated) */
        if (thee->listMode[4] == 1)
            if ( glIsList(thee->list[4]) )
                glCallList(thee->list[4]);

        /* call list=3,2,1,0 (not lighted, not rotated) */
        if (thee->frameMode) {
            for (i=0; i<=3; i++) {
                if (thee->listMode[i] == 1)
                    if ( glIsList(thee->list[i]) )
                        glCallList(thee->list[i]);
            }
        }

    glPopMatrix();

    /* turn the lights back on */
    thee->lightMode = lightSave;
    setLights(thee);

    /* flush the graphics pipeline */
    glFlush();

    /* int error;
     * while ((error=glGetError()) != GL_NO_ERROR)
     *     fprintf(stderr, "GL error: %s\n", gluErrorString(error));
     */
}

/*
 * ***************************************************************************
 * Purpose:  Some simple callback routines to manipulate the object.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Ogl_lightModeOnOff(Ogl *thee)
{
    thee->lightMode = (thee->lightMode + 1) % 2;
    return thee->lightMode;
}
VPUBLIC int Ogl_orthoModeOnOff(Ogl *thee)
{
    thee->orthoMode = (thee->orthoMode + 1) % 2;
    return thee->orthoMode;
}
VPUBLIC int Ogl_frameModeOnOff(Ogl *thee)
{
    thee->frameMode = (thee->frameMode + 1) % 2;
    return thee->frameMode;
}
VPUBLIC int Ogl_ballModeOnOff(Ogl *thee)
{
    thee->ballMode = (thee->ballMode + 1) % 2;
    return thee->ballMode;
}
VPUBLIC int Ogl_bboxModeOnOff(Ogl *thee)
{
    thee->bboxMode = (thee->bboxMode + 1) % 2;
    return thee->bboxMode;
}
VPUBLIC int Ogl_listModeOnOff(Ogl *thee, int list)
{
    thee->listMode[list] = (thee->listMode[list] + 1) % 2;
    return thee->listMode[list];
}
VPUBLIC int Ogl_isList(Ogl *thee, int list)
{
    return glIsList(thee->list[list]);
}
VPUBLIC int Ogl_isListOn(Ogl *thee, int list)
{
    return thee->listMode[list];
}

VPUBLIC void Ogl_resetPos(Ogl *thee)
{
    initView(thee);
}

/*
 * ***************************************************************************
 * Purpose:  Draw (immediate mode) a circular partial arc on the trackball.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void dragBall(Ogl *thee)
{
    int i;
    float alpha, pq[3];

    glLineWidth( (float)3.0 );
    glColor4fv( C_CYAN );
    glBegin(GL_LINE_STRIP);
        for (i=0; i<NUMARC; i++) {
            alpha = (float)i / (float)(NUMARC-1);
            pq[0] = (1.0-alpha)*thee->r0[0] + alpha*thee->r2[0];
            pq[1] = (1.0-alpha)*thee->r0[1] + alpha*thee->r2[1];
            pq[2] = (1.0-alpha)*thee->r0[2] + alpha*thee->r2[2];
            vnormal(pq);
            vscale(pq, BALLSIZE);
            glVertex3fv(pq);
        }
    glEnd();
    glLineWidth( (float)1.0 );
}

/*
 * ***************************************************************************
 * Purpose:  Make a trackball display list.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void makeBallList(Ogl *thee)
{
    static int init=0;
    static GLUquadricObj *quadObj;

    if (!init) {
        quadObj = gluNewQuadric();
        gluQuadricDrawStyle(quadObj, GLU_FILL);
        init = 1;
    }

    VJMPERR1( glIsList(thee->ball=glGenLists(1)) );
    glNewList(thee->ball,GL_COMPILE);

    glColor4fv( C_BALL );
    glPolygonMode( GL_BACK, GL_FILL );
    glPolygonMode( GL_FRONT, GL_POINT );
    gluSphere(quadObj, BALLSIZE, NUMARC, NUMARC);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glEndList();

    /* normal return */
    return;

  VERROR1:
    /* something went wrong */
    fprintf(stderr,"makeBallList: problem creating display list.\n"); 
    return;
}

/*
 * ***************************************************************************
 * Purpose:  Make a bounding box display list.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void makeBBoxList(Ogl *thee)
{
    VJMPERR1( glIsList(thee->bbox=glGenLists(1)) );
    glNewList(thee->bbox,GL_COMPILE);

    glColor4fv( C_BLACK );

    glBegin(GL_LINES);

        glVertex3fv(thee->bboxCoord[0]);
        glVertex3fv(thee->bboxCoord[1]);
        glVertex3fv(thee->bboxCoord[0]);
        glVertex3fv(thee->bboxCoord[2]);
        glVertex3fv(thee->bboxCoord[0]);
        glVertex3fv(thee->bboxCoord[4]);

        glVertex3fv(thee->bboxCoord[5]);
        glVertex3fv(thee->bboxCoord[1]);
        glVertex3fv(thee->bboxCoord[5]);
        glVertex3fv(thee->bboxCoord[4]);
        glVertex3fv(thee->bboxCoord[5]);
        glVertex3fv(thee->bboxCoord[7]);

        glVertex3fv(thee->bboxCoord[6]);
        glVertex3fv(thee->bboxCoord[4]);
        glVertex3fv(thee->bboxCoord[6]);
        glVertex3fv(thee->bboxCoord[7]);
        glVertex3fv(thee->bboxCoord[6]);
        glVertex3fv(thee->bboxCoord[2]);

        glVertex3fv(thee->bboxCoord[3]);
        glVertex3fv(thee->bboxCoord[1]);
        glVertex3fv(thee->bboxCoord[3]);
        glVertex3fv(thee->bboxCoord[2]);
        glVertex3fv(thee->bboxCoord[3]);
        glVertex3fv(thee->bboxCoord[7]);

    glEnd();

    glEndList();

    /* normal return */
    return;

  VERROR1:
    /* something went wrong */
    fprintf(stderr,"makeBBoxList: problem creating display list.\n"); 
    return;
}

/*
 * ***************************************************************************
 * Purpose:  Make a generic display list.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Ogl_beginList(Ogl *thee, int list, int show)
{
    VJMPERR1( (0 <= list) && (list <= 9) );
    VJMPERR1( glIsList(thee->list[list]=glGenLists(1)) );
    glNewList(thee->list[list],GL_COMPILE);

#if defined(HAVE_POLYGON_OFFSET)
    glEnable( GL_POLYGON_OFFSET_FILL );
    glPolygonOffset(1.0, 1.0);
#endif

    /* are we supposed to display the list by default? */
    if (show) {
        thee->listMode[list] = 1;
    } else {
        thee->listMode[list] = 0;
    }

    /* do we update the bounding box? */
    if ((4 <= list) && (list <= 9)) {
        thee->bboxUpdate = 1;
    } else {
        thee->bboxUpdate = 0;
    }

    /* normal return */
    return;

  VERROR1:
    /* something went wrong */
    fprintf(stderr,"Ogl_beginList: problem creating display list.\n"); 
    return;
}
VPUBLIC void Ogl_endList(Ogl *thee)
{
#if defined(HAVE_POLYGON_OFFSET)
    glDisable( GL_POLYGON_OFFSET_FILL );
#endif

    glEndList();
}
VPUBLIC void Ogl_addListObject(Ogl *thee,
    int type, int numPV, float vx[][3], float c[4], float r, char text[])
{
    int j, p;
    float d1[3], d2[3], d3[3], vv[sph320_numV][3];
    static int init=0;
    static GLUquadricObj *quadObj;
#if 0
    float b[4];
#endif

    if (!init) {
        quadObj = gluNewQuadric();
        gluQuadricDrawStyle(quadObj, GLU_FILL);
        init = 1;
    }

    /*
     * type==0  ==>  edges (a line strip)
     * type==1  ==>  filled polygon
     * type==3  ==>  text
     * type==4  ==>  2-sphere (coarse resolution)
     * type==5  ==>  2-sphere (medium resolution)
     * type==6  ==>  2-sphere (fine resolution)
     */

    /* deal with text immediately and return */
    if (type == 3) {
        VASSERT( numPV == 1 );
        glRasterPos3f( vx[0][0], vx[0][1], vx[0][2] );
        glColor4fv( c );
        glListBase(2000);
        glCallLists( strlen(text), GL_UNSIGNED_BYTE, text );
        return;
    }

    /* collect bbox info (ignore vertices outside unit cube) */
    if (thee->bboxUpdate) {
        for (j=0; j<numPV; j++) {
            for (p=0; p<3; p++) {
                /*
                 * if ((vx[j][p]>(CUBESIZE+TOL))||(vx[j][p]<-(CUBESIZE+TOL))){
                 *   fprintf(stderr,
                 *   "Ogl_addListObject: object outside cube; clipping.\n");
                 *   return;
                 * }
                 */
                if (vx[j][p] < thee->min[p]) thee->min[p] = vx[j][p];
                if (vx[j][p] > thee->max[p]) thee->max[p] = vx[j][p];
            }
        }
    }

    /* deal with point/line/polygon differences */
    if (numPV == 1) {

        glColor4fv( c );

        /* POINT: if zero radius, just register point and that's it */
        if ((type == 1) || (r == 0.0)) {
            glBegin(GL_POINTS);
                glVertex3fv(vx[0]);
            glEnd();

        /* NON-zero radius: type tells how nice to make a sphere at point */
        } else if (type == 4) {
            for (j=0; j<sph8_numV; j++) {
                vcopy(sph8_V[j],vv[j]);
                vnormal(vv[j]);
                vscale(vv[j],r);
            }
            glPushMatrix();
                glTranslatef( vx[0][0], vx[0][1], vx[0][2] );
#if 1
                gluSphere(quadObj, r, NUMPDB, NUMPDB);
#else
                glBegin(GL_TRIANGLES);
                    for (i=0; i<sph8_numS; i++) {
                        glNormal3fv(sph8_V[ sph8_S[i][0] ]);
                        glVertex3fv(vv[ sph8_S[i][0] ]);
                        glNormal3fv(sph8_V[ sph8_S[i][1] ]);
                        glVertex3fv(vv[ sph8_S[i][1] ]);
                        glNormal3fv(sph8_V[ sph8_S[i][2] ]);
                        glVertex3fv(vv[ sph8_S[i][2] ]);
                    }
                glEnd();
#endif
            glPopMatrix();
        } else if (type == 5) {
            for (j=0; j<sph80_numV; j++) {
                vcopy(sph80_V[j],vv[j]);
                vnormal(vv[j]);
                vscale(vv[j],r);
            }
            glPushMatrix();
                glTranslatef( vx[0][0], vx[0][1], vx[0][2] );
#if 1
                gluSphere(quadObj, r, NUMPDB, NUMPDB);
#else
                glBegin(GL_TRIANGLES);
                    for (i=0; i<sph80_numS; i++) {
                        glNormal3fv(sph80_V[ sph80_S[i][0] ]);
                        glVertex3fv(vv[ sph80_S[i][0] ]);
                        glNormal3fv(sph80_V[ sph80_S[i][1] ]);
                        glVertex3fv(vv[ sph80_S[i][1] ]);
                        glNormal3fv(sph80_V[ sph80_S[i][2] ]);
                        glVertex3fv(vv[ sph80_S[i][2] ]);
                    }
                glEnd();
#endif
            glPopMatrix();
        } else if (type == 6) {
            for (j=0; j<sph320_numV; j++) {
                vcopy(sph320_V[j],vv[j]);
                vnormal(vv[j]);
                vscale(vv[j],r);
            }
            glPushMatrix();
                glTranslatef( vx[0][0], vx[0][1], vx[0][2] );
#if 1
                gluSphere(quadObj, r, NUMPDB, NUMPDB);
#else
                glBegin(GL_TRIANGLES);
                    for (i=0; i<sph320_numS; i++) {
                        glNormal3fv(sph320_V[ sph320_S[i][0] ]);
                        glVertex3fv(vv[ sph320_S[i][0] ]);
                        glNormal3fv(sph320_V[ sph320_S[i][1] ]);
                        glVertex3fv(vv[ sph320_S[i][1] ]);
                        glNormal3fv(sph320_V[ sph320_S[i][2] ]);
                        glVertex3fv(vv[ sph320_S[i][2] ]);
                    }
                glEnd();
#endif
            glPopMatrix();
        }

    } else if (numPV >= 2) {

        if ((numPV == 2) || (type == 0)) {

            /* LINE: set the frontface and backface colors */
            glColor4fv( c );

            /* register the line */
            if (numPV == 2) {
                glBegin(GL_LINES);
                    glVertex3fv(vx[0]);
                    glVertex3fv(vx[1]);
                glEnd();
            } else if (type == 0) {
                glBegin(GL_LINE_STRIP);
                    for (j=0; j<numPV; j++)
                        glVertex3fv(vx[j]);
                glEnd();
            }

        } else if ((numPV >= 3) && (type == 1)) {

            /* POLYGON: set the frontface and backface colors */
            glColor4fv( c );
#if 0
            if (thee->backMode == 1) {
                for (j=0; j<4; j++) b[j] = 0.5 * c[j];
            }
#endif

            /* get a normal vector using first three vertices to define plane */
            for (j=0; j<3; j++) {
                d1[j] = vx[0][j] - vx[1][j];
                d2[j] = vx[0][j] - vx[2][j];
            }
            vcross(d1, d2, d3);
            vnormal(d3);
            glNormal3fv(d3);

            /* register the polygon */
            if (numPV == 3) {
                glBegin(GL_TRIANGLES);
                    glVertex3fv(vx[0]);
                    glVertex3fv(vx[1]);
                    glVertex3fv(vx[2]);
                glEnd();
            } else if (numPV == 4) {
                glBegin(GL_QUADS);
                    glVertex3fv(vx[0]);
                    glVertex3fv(vx[1]);
                    glVertex3fv(vx[2]);
                    glVertex3fv(vx[3]);
                glEnd();
            } else { /* (numPV >= 5) */
                glBegin(GL_POLYGON);
                    for (j=0; j<numPV; j++)
                        glVertex3fv(vx[j]);
                glEnd();
            }
        } else {
            fprintf(stderr,
                "Ogl_addListObject: object is defective; clipping.\n");
            return;
        }
    } else {
        fprintf(stderr,
            "Ogl_addListObject: object is defective; clipping.\n");
        return;
    }
}

/*
 * ***************************************************************************
 * Purpose:  Initialize the OpenGL context view parameters.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void initView(Ogl *thee)
{
    thee->origin[0] = 0.0;
    thee->origin[1] = 0.0;
    thee->origin[2] = 0.0;
    thee->eye[0]    = 0.0;
#if 1
    thee->eye[1]    = 0.0;
#else
    thee->eye[1]    = 0.4 * thee->eyezInit;
#endif
    thee->eye[2]    = thee->eyezInit;
    thee->trans[0]  = 0.0;
    thee->trans[1]  = 0.0;
    thee->trans[2]  = 0.0;
    thee->scale     = 1.0;
    vzero(thee->quat);
    thee->quat[3] = 1.0;
    vzero(thee->quatDrag);
    thee->quatDrag[3] = 1.0;
    vset(thee->r0, 0.0, 0.0, projectSphere(BALLSIZE, 0.0, 0.0));
    vset(thee->r1, 0.0, 0.0, projectSphere(BALLSIZE, 0.0, 0.0));
    vset(thee->r2, 0.0, 0.0, projectSphere(BALLSIZE, 0.0, 0.0));
    vzero(thee->s1);
    vzero(thee->s2);
    vzero(thee->t1);
    vzero(thee->t2);
}

/*
 * ***************************************************************************
 * Purpose:  Set the OpenGL lighting and other effects.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE float amb[4] = {(float)0.12, (float)0.12, (float)0.12, (float)0.0 };
VPRIVATE float dif[4] = {(float)0.5, (float)0.5, (float)0.5, (float)0.0 };
VPRIVATE float spe[4] = {(float)0.6, (float)0.6, (float)0.6, (float)0.0 };
VPRIVATE void setLights(Ogl *thee)
{
    VPRIVATE float pos0[4] ={(float) 0.0, (float) 0.0, (float) 1.0, (float)0.0};
    VPRIVATE float spt0[3] ={(float) 0.0, (float) 0.0, (float)-1.0};

    if (thee->lightMode) {
        glEnable( GL_LIGHTING );
        glEnable( GL_LIGHT0 );
        glLightfv( GL_LIGHT0, GL_AMBIENT, amb );
        glLightfv( GL_LIGHT0, GL_DIFFUSE, dif );
        glLightfv( GL_LIGHT0, GL_SPECULAR, spe );
        glLightfv( GL_LIGHT0, GL_POSITION, pos0 );
        glLightfv( GL_LIGHT0, GL_SPOT_DIRECTION, spt0 );
    } else glDisable( GL_LIGHTING );
}
VPRIVATE void setEffects(Ogl *thee)
{
    VPRIVATE float emi[4] = {(float)0.0, (float)0.0, (float)0.0, (float)0.0 };
    VPRIVATE float shi[1] = {(float)12.0 };

    glClearColor( C_CLEAR_GV[0], C_CLEAR_GV[1], C_CLEAR_GV[2], C_CLEAR_GV[3] );
    glLineWidth( (float)1.0 );
    glFrontFace( GL_CCW );
    glDepthFunc( GL_LEQUAL );
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_NORMALIZE );
    glEnable( GL_COLOR_MATERIAL );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb );
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, dif );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, spe );
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emi );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, shi );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
#if 0
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
#endif
}
VPRIVATE void clearBBox(Ogl *thee)
{
    thee->min[0] =  VLARGE;
    thee->max[0] = -VLARGE;
    thee->min[1] =  VLARGE;
    thee->max[1] = -VLARGE;
    thee->min[2] =  VLARGE;
    thee->max[2] = -VLARGE;

    thee->bboxCoord[0][0] = - CUBESIZE;
    thee->bboxCoord[0][1] = - CUBESIZE;
    thee->bboxCoord[0][2] = - CUBESIZE;

    thee->bboxCoord[1][0] =   CUBESIZE;
    thee->bboxCoord[1][1] = - CUBESIZE;
    thee->bboxCoord[1][2] = - CUBESIZE;

    thee->bboxCoord[2][0] = - CUBESIZE;
    thee->bboxCoord[2][1] =   CUBESIZE;
    thee->bboxCoord[2][2] = - CUBESIZE;

    thee->bboxCoord[3][0] =   CUBESIZE;
    thee->bboxCoord[3][1] =   CUBESIZE;
    thee->bboxCoord[3][2] = - CUBESIZE;

    thee->bboxCoord[4][0] = - CUBESIZE;
    thee->bboxCoord[4][1] = - CUBESIZE;
    thee->bboxCoord[4][2] =   CUBESIZE;

    thee->bboxCoord[5][0] =   CUBESIZE;
    thee->bboxCoord[5][1] = - CUBESIZE;
    thee->bboxCoord[5][2] =   CUBESIZE;

    thee->bboxCoord[6][0] = - CUBESIZE;
    thee->bboxCoord[6][1] =   CUBESIZE;
    thee->bboxCoord[6][2] =   CUBESIZE;

    thee->bboxCoord[7][0] =   CUBESIZE;
    thee->bboxCoord[7][1] =   CUBESIZE;
    thee->bboxCoord[7][2] =   CUBESIZE;
}
VPRIVATE void makeBBox(Ogl *thee)
{
    thee->bboxCoord[0][0] = thee->min[0];
    thee->bboxCoord[0][1] = thee->min[1];
    thee->bboxCoord[0][2] = thee->min[2];

    thee->bboxCoord[1][0] = thee->max[0];
    thee->bboxCoord[1][1] = thee->min[1];
    thee->bboxCoord[1][2] = thee->min[2];

    thee->bboxCoord[2][0] = thee->min[0];
    thee->bboxCoord[2][1] = thee->max[1];
    thee->bboxCoord[2][2] = thee->min[2];

    thee->bboxCoord[3][0] = thee->max[0];
    thee->bboxCoord[3][1] = thee->max[1];
    thee->bboxCoord[3][2] = thee->min[2];

    thee->bboxCoord[4][0] = thee->min[0];
    thee->bboxCoord[4][1] = thee->min[1];
    thee->bboxCoord[4][2] = thee->max[2];

    thee->bboxCoord[5][0] = thee->max[0];
    thee->bboxCoord[5][1] = thee->min[1];
    thee->bboxCoord[5][2] = thee->max[2];

    thee->bboxCoord[6][0] = thee->min[0];
    thee->bboxCoord[6][1] = thee->max[1];
    thee->bboxCoord[6][2] = thee->max[2];

    thee->bboxCoord[7][0] = thee->max[0];
    thee->bboxCoord[7][1] = thee->max[1];
    thee->bboxCoord[7][2] = thee->max[2];
}

/*
 * ***************************************************************************
 * Purpose:  Primary rotation/scaling/translation routines.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void rotate(Ogl *thee)
{
    if ( (thee->r0[0]==thee->r2[0]) && (thee->r0[1]==thee->r2[1]) ) {
        vzero(thee->quatDrag);
        thee->quatDrag[3] = 1.0;
    } else { buildQuat(thee->quatDrag, thee->r0, thee->r2); }
}
VPRIVATE void scale(Ogl *thee)
{
    float px, py, qx, qy, dx, dy, d, scale;
    if ( (thee->s1[0]==thee->s2[0]) && (thee->s1[1]==thee->s2[1]) ) {
    } else {
        px = thee->s1[0];
        py = thee->s1[1];
        qx = thee->s2[0];
        qy = thee->s2[1];
        dx = px-qx;
        dy = py-qy;
        d = VSQRT( dx*dx + dy*dy );
        if (VABS(dx) > VABS(dy)) {
            scale = 1.0 + VSIGN(d,dx);
        } else {
            scale = 1.0 + VSIGN(d,dy);
        }
        thee->scale *= scale;
    }
}
VPRIVATE void translate(Ogl *thee)
{
    float px, py, qx, qy, dx, dy;
    if ( (thee->t1[0]==thee->t2[0]) && (thee->t1[1]==thee->t2[1]) ) {
    } else {
        px = thee->t1[0];
        py = thee->t1[1];
        qx = thee->t2[0];
        qy = thee->t2[1];
        dx = px-qx;
        dy = py-qy;
        thee->trans[0] -= 1.0*dx;
        thee->trans[1] -= 1.0*dy;
    }
}
VPUBLIC void Ogl_setMouseMode(Ogl *thee, int value)
{
    int xval = 0;
    if ((0 <= value) && (value <= 2)) xval = value;
    thee->mouseMode = xval;
}
VPUBLIC void Ogl_mouseDown(Ogl *thee, int x, int y)
{
    float px, py;
    VASSERT( thee->mouseDown < 3 );
    thee->mouseDown++;
    if ( thee->mouseDown == 1 ) {
        vzero(thee->quatDrag);
        thee->quatDrag[3] = 1.0;
        px = (2.0*x - thee->viewWidth) / thee->viewWidth;
        py = (thee->viewHeight - 2.0*y) / thee->viewHeight;
        if (thee->mouseMode == 0) {
            vset(thee->r0, px, py, projectSphere(BALLSIZE, px, py));
            vset(thee->r1, px, py, projectSphere(BALLSIZE, px, py));
            vset(thee->r2, px, py, projectSphere(BALLSIZE, px, py));
        } else if (thee->mouseMode == 1) {
            vset(thee->s1, px, py, 0.0);
            vset(thee->s2, px, py, 0.0);
        } else if (thee->mouseMode == 2) {
            vset(thee->t1, px, py, 0.0);
            vset(thee->t2, px, py, 0.0);
        } else { VASSERT(0); }
    }
}
VPUBLIC void Ogl_mouseUp(Ogl *thee, int x, int y)
{
    VASSERT( thee->mouseDown > 0 );
    thee->mouseDown--;
    if ( thee->mouseDown == 0 ) {
        addQuat(thee->quatDrag, thee->quat, thee->quat);
        vzero(thee->quatDrag);
        thee->quatDrag[3] = 1.0;
    }
}
VPUBLIC void Ogl_mouseMotion(Ogl *thee, int x, int y)
{
    float px, py;
    VASSERT( thee->mouseDown > 0 );
    px = (2.0*x - thee->viewWidth) / thee->viewWidth;
    py = (thee->viewHeight - 2.0*y) / thee->viewHeight;
    if (thee->mouseMode == 0) {
        vcopy(thee->r2, thee->r1);
        vset(thee->r2, px, py, projectSphere(BALLSIZE, px, py));
        rotate( thee );
    } else if (thee->mouseMode == 1) {
        vcopy(thee->s2, thee->s1);
        vset(thee->s2, px, py, 0.0);
        scale( thee );
    } else if (thee->mouseMode == 2) {
        vcopy(thee->t2, thee->t1);
        vset(thee->t2, px, py, 0.0);
        translate( thee );
    } else { VASSERT(0); }
}
VPUBLIC int Ogl_spin(Ogl *thee)
{
    int i;
    float r0[3], r1[3], r2[3], bc[3], r02[3], r12[3];
    float alpha, d02, d12;

    vcopy(thee->r0, r0);
    vcopy(thee->r1, r1);
    vcopy(thee->r2, r2);

    vsub(r0,r2,r02);
    vsub(r1,r2,r12);
    d02 = vlength(r02);
    d12 = vlength(r12);
    alpha = d12 / d02;

    vadd(r0,r2,bc);
    vscale(bc,0.5);
    for (i=0; i<3; i++) {
        r0[i] = (1.0-alpha)*bc[i] + alpha*r0[i];
        r2[i] = (1.0-alpha)*bc[i] + alpha*r2[i];
    }

    if (d12 > TOL) {
        buildQuat(thee->quatDrag, r0, r2);
        addQuat(thee->quatDrag, thee->quat, thee->quat);
        vzero(thee->quatDrag);
        thee->quatDrag[3] = 1.0;
        return 1;
    } else {
        return 0;
    }
}

/*
 * ***************************************************************************
 * Purpose:  Vector utilities to support the quaternion-based rotator.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void vzero(float u[]) {
    u[0] = 0.0;
    u[1] = 0.0;
    u[2] = 0.0;
}
VPRIVATE void vset(float u[], float x, float y, float z)
{
    u[0] = x;
    u[1] = y;
    u[2] = z;
}
VPRIVATE void vsub(const float u[], const float v[], float w[])
{
    w[0] = u[0] - v[0];
    w[1] = u[1] - v[1];
    w[2] = u[2] - v[2];
}
VPRIVATE void vcopy(const float u[], float v[])
{
    v[0] = u[0];
    v[1] = u[1];
    v[2] = u[2];
}
VPRIVATE void vcross(const float u[], const float v[], float w[])
{
    float tmp[3];
    tmp[0] = (u[1] * v[2]) - (u[2] * v[1]);
    tmp[1] = (u[2] * v[0]) - (u[0] * v[2]);
    tmp[2] = (u[0] * v[1]) - (u[1] * v[0]);
    vcopy(tmp, w);
}
VPRIVATE float vlength(const float u[])
{
    return VSQRT( u[0]*u[0] + u[1]*u[1] + u[2]*u[2] );
}
VPRIVATE void vscale(float u[], float scale)
{
    u[0] *= scale;
    u[1] *= scale;
    u[2] *= scale;
}
VPRIVATE void vnormal(float u[])
{
    vscale(u, 1.0 / vlength(u));
}
VPRIVATE float vdot(const float u[], const float v[])
{
    return ( u[0]*v[0] + u[1]*v[1] + u[2]*v[2] );
}
VPRIVATE void vadd(const float u[], const float v[], float w[])
{
    w[0] = u[0] + v[0];
    w[1] = u[1] + v[1];
    w[2] = u[2] + v[2];
}

/*
 * ***************************************************************************
 * Purpose:  Quaternion utilities for the quaternion-based rotator.
 *
 * Notes:    The six routines:
 *
 *               buildQuat, axisQuat, addQuat, normalQuat,
 *               buildRotation, projectSphere
 *
 *           are my quaternion rotator hacks, based heavily on the trackball
 *           rotator example in Mark Kilgard's OpenGL programming book.
 *
 *           Unfortunately, Kilgard's example exhibits hysteresis.
 *           However, I used Ken Shoemake's trick from his famous arcball
 *           implementation in Graphics Gems to remove this effect.
 *           The trick is to avoid accumulating the quaternion rotations
 *           during mouse dragging, and to keep the current drag and the
 *           initial rotation as separate quaternions.
 *           You then accumulate the two quaternions only on mouse release.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void buildQuat(float q[4], float r0[3], float r2[3])
{
    float a[3], d[3], phi, t;
    vcross(r2, r0, a);
    vsub(r0, r2, d);
    t = vlength(d) / (2.0 * BALLSIZE);
    if (t >  1.0) t =  1.0;
    if (t < -1.0) t = -1.0;
    phi = 2.0 * VASIN(t);
    axisQuat(a, phi, q);
}
VPRIVATE void axisQuat(float a[3], float phi, float q[4])
{
    vnormal(a);
    vcopy(a, q);
    vscale(q, VSIN(phi / 2.0));
    q[3] = VCOS(phi / 2.0);
}
VPRIVATE void addQuat(float q0[4], float q1[4], float des[4])
{
    static int count = 0;
    float r0[4], r1[4], r2[4], r3[4];

    vcopy(q0, r0);
    vscale(r0, q1[3]);
    vcopy(q1, r1);
    vscale(r1, q0[3]);

    vcross(q1, q0, r2);
    vadd(r0, r1, r3);
    vadd(r2, r3, r3);
    r3[3] = q0[3] * q1[3] - vdot(q0, q1);

    des[0] = r3[0];
    des[1] = r3[1];
    des[2] = r3[2];
    des[3] = r3[3];

    count++;
    if (count > RENORMAL) {
        count = 0;
        normalQuat(des);
    }
}
VPRIVATE void normalQuat(float q[4])
{
    int i;
    float mag;
    mag = ( q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3] );
    for (i=0; i<4; i++) q[i] /= mag;
}
VPRIVATE void buildRotation(float m[4][4], float q[4])
{
    m[0][0] = 1.0 - 2.0*(q[1]*q[1] + q[2]*q[2]);
    m[0][1] = 2.0*(q[0]*q[1] - q[2]*q[3]);
    m[0][2] = 2.0*(q[2]*q[0] + q[1]*q[3]);
    m[0][3] = 0.0;

    m[1][0] = 2.0*(q[0]*q[1] + q[2]*q[3]);
    m[1][1] = 1.0 - 2.0*(q[2]*q[2] + q[0]*q[0]);
    m[1][2] = 2.0*(q[1]*q[2] - q[0]*q[3]);
    m[1][3] = 0.0;

    m[2][0] = 2.0*(q[2]*q[0] - q[1]*q[3]);
    m[2][1] = 2.0*(q[1]*q[2] + q[0]*q[3]);
    m[2][2] = 1.0 - 2.0*(q[1]*q[1] + q[0]*q[0]);
    m[2][3] = 0.0;

    m[3][0] = 0.0;
    m[3][1] = 0.0;
    m[3][2] = 0.0;
    m[3][3] = 1.0;
}
VPRIVATE float projectSphere(float r, float x, float y)
{
    static int init = 0;
    static float SQRTHALF, SQRTTWO;
    float d, t, z;

    if (!init) {
        SQRTTWO  = VSQRT( 2.0 );
        SQRTHALF = 1.0 / SQRTTWO;
        init = 1;
    }

    d = VSQRT( x*x + y*y );
    if (d < r*SQRTHALF) {
        z = VSQRT( r*r - d*d );
    } else {
        t = r / SQRTTWO;
        z = t*t / d;
    }
    return z;
}

