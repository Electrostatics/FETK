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
 * rcsid="$Id: oglps.c,v 1.10 2010/08/12 04:56:23 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     oglps.c
 *
 * Purpose:  High-quality OpenGL-to-Postscript rendering.
 *
 * Notes:    The purpose of Oglps is to produce a very high-quality and
 *           realistic PostScript rendering of an OpenGL rendered scene, by
 *           using the feedback mechanism in OpenGL to fetch the set of
 *           polygons in the current scene, determine a logical painting order
 *           for the polygons in the scene using a constaint resolution-based
 *           ``feasible region'' approach, and then by drawing the scene in
 *           that order in PostScript, using the painter's algorithm.  (While
 *           we usually have a Z-buffer when using OpenGL, we must resort to
 *           the painter's algorithm for rendering in postscript.)
 *
 *           There are two main difficulties in implementing such a rendering:
 *
 *           (1) The scene may not be orderable, e.g., if polygons overlap
 *               loops occur.  This is actually quite common, especially for
 *               scenes with polygons that intersect or self-intersect, such
 *               as a scene containing a Klein bottle.
 *
 *           (2) Even if the scene is orderable, determining an ordering may
 *               be difficult or extremely costly.  In particular, the
 *               complexity of looking at all pair-wise interactions to
 *               determine constraints (which polygons must be drawn before
 *               other polygons) makes determining the rendering order quite
 *               expensive, and perhaps intractable for scenes with many
 *               polygons.  (The complexity of the pairwise compare goes as
 *               N^2 for a scene with N polygons.)
 *
 *           The first problem is solvable through subdivision; we ignore this
 *           problem here and assume we are dealing only with scenes
 *           renderable using the painter's algorithm.
 *
 *           The second problem is addressed in a primative (but fast) way in
 *           several publically available GL-to-PS and OpenGL-to-PS
 *           generators.  Unfortunately, these codes use a simple quicksort
 *           of the polygons by the z-coordinates of their centroids or
 *           baricenters, which works pretty well for very smooth triangular
 *           2-manifolds, but fails badly for any seriously complex 3D scene.
 *           (Examples are 3D tetrhedral meshes, or even 2-manifold meshes
 *           which are not smooth.)
 *
 *           In this code, we solve this second problem in the case of much
 *           more complex OpenGL scenes.  We build a list of linear inequality
 *           constraints, and then locate a point in the feasible region
 *           defined by the constraints, producing a (possibly non-unique)
 *           rendering order that produces a correct (realistic) scene.  We
 *           address the complexity problem by building a binary space
 *           partition tree in the Z (z-buffer) direction, and then adaptively
 *           bisect the polygons in each Z-slice to further reduce the number
 *           of polygons that must be pair-wise compared to produce the list
 *           of linear inequality constraints for that part of the scene.
 *
 *           Once the list of linear inequality constraints has been created
 *           for the entire scene by moving through the Z-slices and through
 *           the X/Y partitions within each slice, we then use a "constraint
 *           walking" algorithm to locate a feasible rendering point in the
 *           feasible rendering region, beginning with a single unconstrained
 *           polygon in the rear of the scene.
 * 
 *           This "constraint walking" algorithm finds a feasible point in the
 *           feasible region defined by a set of (binary) linear inequality
 *           constraints in the sense of linear or nonlinear programming.
 *           However, the simple binary nature of each constraint allows us to
 *           find a feasible point without resorting to the use of something
 *           like phase one of the simplex method.
 *
 * Approach: The core rendering routines are based on the following approach.
 *
 *           (1) We build a binary space partition tree, with cutting planes
 *               moved along the Z-axis from maximal Z (the first polygons to
 *               be drawn) to minimal Z (the last polygons to be drawn).  This
 *               binary space partition tree is used primarily to try to
 *               reduce the complexity of collecting constraint information
 *               about the polygons.  Note that polygons are cut exactly at
 *               the plane, resulting in fragments, so that the total number
 *               of polygons rendered actually increases with each partition
 *               that is used.
 *
 *           (2) Within each Z partition (beginning with the maximal Z
 *               partition and working from back to front), we collect
 *               constraint information.  We use adaptive orthogonal bisection
 *               (bisecting parallel to either the X axis or the Y axis,
 *               depending on which bisection results in the smallest total
 *               number of polygons appearing in the sum of both resulting
 *               polygon lists).
 *
 *               The constraint information collected is as follows.  If an
 *               polygon A is found to lie under B, then A must be drawn
 *               before B.  We can view this as A "blocking" B from being
 *               drawn, or constraining B to be ordered after A in a sequential
 *               rendering order.  We store this information by (1) placing B
 *               in a list maintained by A that keeps track of exactly which
 *               polygons A blocks from being drawn, and (2) incrementing a
 *               "blocked" counter in polygon B that counts how many polygons
 *               are blocking B from being drawn.
 *
 *               The test of whether a polygon A lies above or below B is
 *               performed by forming the exact overlap polygon (if there is
 *               overlap), and then comparing the z-coordinates of the
 *               polygons A and B at the centroid of the overlap polygon.
 *               Comparing A and B by the z-coordinates of their separate
 *               baricenters can easily fail to order them correctly.  However,
 *               using the z-coordinates at the centroid of their overlap
 *               polygon cannot fail, if the polygons are disjoint and
 *               non-intersecting.
 *
 *           (3) Once the entire scene has been processed (hopefully in our
 *               lifetime, thanks to the complexity reductions in steps (1)
 *               and (2) above), we have a set of (binary) linear inequality
 *               constraints, defining a feasible rendering region.  Every
 *               point in this feasible region represents a (possibly
 *               non-unique) rendering order that will produce a logically
 *               correct scene using the Painter's algorithm.  We are not
 *               interested here in some optimal rendering order, but rather
 *               some ordering that produces a correct scene, so all we need
 *               to do is find a feasible point.
 *
 *               At this point we must locate a single point in this feasible
 *               region.  The standard approach for doing this is to build
 *               a "larger" linear programming problem for which we do have
 *               a starting point in the feasible region (of the larger
 *               problem), the solution of which is a feasible point in the
 *               original feasible region.  Once we have this larger problem,
 *               we can use the simplex method to solve it to locate the
 *               point the feasible region that we were originally after.
 *
 *               However, this is overkill here; our constraints are very
 *               special (binary), and a feasible point can be located much
 *               more efficiently by using the following "constraint walking"
 *               algorithm that has been suggested by Randy Bank.  We begin by
 *               finding all polygons with no constraints (single traversal
 *               through the polygon list, looking for polygons with "blocked"
 *               counter set to zero).  We place these unconstrained polygons
 *               in a final rendering order list, and then begin with the
 *               single unconstrained polygon in the first rendering list
 *               position.
 *
 *               If the scene is renderable by the painter's algorithm, then
 *               this unconstrained list has atleast one polygon in it.
 *               We then "draw" it by "walking" the list that it maintains
 *               about polygons it was blocking.  We then decrement the
 *               "blocked" counter in each of these polygons on the list.
 *               If any of the "blocked" counters reduce to zero, that polygon
 *               is placed on the final rendering list in the first empty
 *               slot.   We now move to the second polygon in the unconstrained
 *               list, and "draw" it by walking its constraint list as for the
 *               first polygon.  We continue in this manner until all polygons
 *               have been placed in a rendering order in the final rendering
 *               list.
 *
 *           Note that if the scene is renderable (via painter's algorithm),
 *           then this algorithm cannot fail.  Since we begin with all
 *           unconstrained polygons on the final rendering list, and since I
 *           immediately place any polygons with "blocked" count reduced to
 *           zero in the final rendering list, we always have access to all
 *           unconstrained polygons in the final rendering list.  If we come
 *           to the end of the unconstrained polygons and we still have
 *           unrendered polygons, then we can conclude that the scene was not
 *           renderable by the painter's algorithm.
 *
 * Limits:   To avoid floating point round-off problems that quickly kill
 *           the painter's algorithm, only TRIANGLES are rendered.  All other
 *           OpenGL objects retrieved by the glFeedbackBuffer() call are
 *           ignored (including points, lines, polygons other than triangles,
 *           and all other OpenGL objects other than polygons).  To make it
 *           possible to render the edges of e.g. a triangular or tetrahedral
 *           finite element mesh, an option is provided that will paint
 *           polygon outlines after the polygon itself is painted.
 *
 * Usage:    This library is used as follows.  You begin by making a call to
 *           "Oglps_begin()" with no argument.  You follow this by rendering
 *           your scene as usual (e.g., "Reshape" and "Display"), and
 *           finally you call "Oglps_end(x,c,b)".  You use first argment x=0
 *           for filled polygon rendering, or use x=1 for filled AND outlined
 *           polygon rendering.  You use c=0 for black/white or c=1 for color
 *           as the second argument.  Use the third argument b=0 for rendering
 *           of all polygons, or b=1 for removal of back-facing polygons
 *           before rendering (in a tetrahedral mesh, all back-facing triangles
 *           are in the interior of tets, and they can be safely removed before
 *           rendering, which will reduce the complexity costs of rendering
 *           the scene.)
 *
 *           The calling sequence in your code will look something like this:
 *
 *                  Oglps_begin();
 *                  reshape(w,h);
 *                  display();
 *                  Oglps_end( x, c, b );
 *
 *           There is also a quick and dirty GLXpixmap-to-postscript generator
 *           that we more or less typed in from Kilgard's book; you call it
 *           as follows, where "x" and "c" are as above, and where w and h
 *           are the width and height (in pixels) of the pixmap:
 *
 *                  Oglps_gen( "glx.ps", x, c, w, h );
 *
 *           (You must render into a GLXpixmap yourself, before calling
 *           Oglps_gen.)
 *
 * Comments: (1) The binary space paritioning scheme in the Z direction
 *               for reducing polygon comparision complexity is a well-known
 *               computational geometry algorithm in computer graphics, and
 *               can be found in most computational geometry books. 
 *
 *           (2) This OpenGL-2-Postscript rendering code came about by
 *               running into failure with the baricenter/quicksort ordering
 *               scheme used in Seth Teller's "PSGL" when trying to render
 *               complex OpenGL 3D finite element scenes into postscript.
 *               Peter Schroeder at Caltech suggested we try Gary Wu's
 *               "PSOGL", but it turns out that it shares the same simple
 *               baricenter/quicksort-based ordering scheme, so it fails to
 *               order these types of meshes correctly for the painter's
 *               algorithm in the same way as PSGL.
 *
 *               We ended up writing an exact polygon intersection comparison
 *               code to exactly resolve front/behind compares for any
 *               polygon pair.  Unfortunately, this creates a different "z"
 *               value for the same polygon, depending on who it is compared
 *               to (the overlap polygon changes).  What this means is that
 *               normal sorting algorithms such as quicksort can no longer be
 *               used, since what we really have is a set of linear inequality
 *               constraints defining a feasible rendering region in the
 *               sense of linear or nonlinear programming.  The solution was
 *               to use a completely constraint-oriented ordering approach,
 *               with binary space partitioning in Z, and then in X and Y as
 *               well, to keep the constraint construction complexity low,
 *               and then to resolve the constraints using something equivalent
 *               to phase one of the Simplex Method (which finds a feasible
 *               point in the feasible region from which to launch phase two).
 *
 *           (3) While using phase one of the simplex method works here, in
 *               that it finds a feasible point in the feasible region defined
 *               by the set of constraints (i.e., a legal rendering order),
 *               Randy Bank had a nice insight that lets me avoid actually
 *               using the simplex method here.  He had used a "constraint
 *               walking" algorithm like the one above for rendering scenes
 *               using the painter's algorithm in PLTMG, although he used
 *               mesh topology information to actually build the constraint
 *               information.  While we have no topology to exploit here
 *               (all we get from OpenGL's feedback mechanism is a list of
 *               unrelated objects to render), we can actually use this
 *               constraint walking algorithm here, once we have built the
 *               constraints by other means.  It is equivalent to phase one of
 *               the simplex method for finding a single point in the feasible
 *               region defined by a set of linear inequality constraints.
 *               The equivalence is due to the fact that the constraints in
 *               this situation are very special, namely binary linear
 *               inequality constraints.
 *
 *           (4) We also added a completely separate quick and dirty postscript
 *               generator by condensing an example from Mark Kilgard's
 *               OpenGL/X programming book to a single routine.  This single
 *               routine (Oglps_gen) is completely independent from the
 *               other rendering routines (shares no data, etc).  It simply
 *               generates a postscript image from pixel data, so it achieves
 *               rendering quality on the order of a screen dump (pretty bad).
 *               But it is a quick was to get PS output without bringing up
 *               e.g. xv, if you don't want to wait for the painter's
 *               algorithm to correctly render your scene.
 *
 * Author:   Michael Holst and Randy Bank
 * ***************************************************************************
 */

#include "oglps_p.h"

VEMBED(rcsid="$Id: oglps.c,v 1.10 2010/08/12 04:56:23 fetk Exp $")

#define VMAXPV      6       /* Max num of vertices allowed in a planar poly */
#define VBOX        10000.0 /* Virtual truncation box around the object     */
#define VTINY       1.0e-6  /* The effective ZERO for all floating point    */

/* PS generation parameters */
#define base            62
#define base3           ( base*base*base )
#define scale           5000
#define clipdist        0
#define PointsPerInch   72.0
#define PBox            0.02
#define PSize           ( 8.0   * PointsPerInch )
#define PWidth          ( 8.5   * PointsPerInch )
#define PHeight         ( 8.5   * PointsPerInch )
#define PXmin           ( (PWidth  - PSize) / 2.0 )
#define PYmin           ( (PHeight - PSize) / 2.0 )
#define PXmax           ( PXmin + PSize )
#define PYmax           ( PYmin + PSize )
#define PXmapPS(x)      ( (((x) - Xmid)*XYscale + 0.5) * PSize + PXmin )
#define PYmapPS(y)      ( (((y) - Ymid)*XYscale + 0.5) * PSize + PYmin )
#define PXmap01(x)      (((x) - Xmid)*XYscale   + 0.5)
#define PYmap01(y)      (((y) - Ymid)*XYscale   + 0.5)

typedef struct Color {    /* RGBA-color object */
    int   i;
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct Vert {    /* Vertex object */
    double x;
    double y;
    double z;
} Vert;

typedef struct Bloc {   /* Constraint matrix row entry */
    struct Poly  *guy;
    struct Bloc  *next;
} Bloc;
 
typedef struct Poly {    /* Planar polygon datastructure                    */
    int    id;           /* My global id                                    */
    int    nv;           /* My vertex count                                 */
    Color  c;            /* My color                                        */
    int    bnum;         /* Number of guys blocking me from being drawn     */
    Bloc   *blist;       /* The list of guys that I block from being drawn  */
    double xmin;         /* Minimum x-value in me                           */
    double xmax;         /* Maximum x-value in me                           */
    double ymin;         /* Minimum y-value in me                           */
    double ymax;         /* Maximum y-value in me                           */
    double zmin;         /* Minimum z-value in me                           */
    double zmax;         /* Maximum z-value in me                           */
    double bc[3];        /* Coordinates of my baricenter                    */
    Vert   v[VMAXPV];    /* My vertices                                     */
} Poly;

VPRIVATE int floatBufferMax = 4*1024*1024; /* feedback buffer (fixed) */
VPRIVATE int floatBufferNum;
VPRIVATE float* floatBuffer;

VPRIVATE int triaBufferMax = 1024;  /* start tria buffer small (dynamic) */
VPRIVATE int triaBufferNum;
VPRIVATE Poly* triaBuffer;

VPRIVATE int edgeBufferMax = 1024;  /* start edge buffer small (dynamic) */
VPRIVATE int edgeBufferNum;
VPRIVATE Poly* edgeBuffer;

VPRIVATE int *xord;   /* x/y/z-max orderings */
VPRIVATE int *yord;
VPRIVATE int *zord;

VPRIVATE int colorBufMax = base3;    /* color index buffer (fixed) */
VPRIVATE int colorBufNum;
VPRIVATE int *colorBufI;
VPRIVATE float *colorBufR, *colorBufG, *colorBufB;
VPRIVATE int colorBufInit = 0;

VPRIVATE char psFileName[256];       /* PS filename, counter, and pointer */
VPRIVATE int psFileNumber = 0;
VPRIVATE FILE* psFilePtr;

VPRIVATE double Xmin;                 /* Smallest box containing the scene */
VPRIVATE double Xmax;
VPRIVATE double Ymin;
VPRIVATE double Ymax;
VPRIVATE double Zmin;
VPRIVATE double Zmax;

VPRIVATE double Xmid;                 /* Center of the containment Box */
VPRIVATE double Ymid;

VPRIVATE double XYscale;              /* For PS generation page layout */

VPRIVATE char digits[62] =          /* color encoding; makes small PS files */
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*
 * ***************************************************************************
 * Private routine prototypes
 * ***************************************************************************
 */

/* interact with OpenGL feedback buffer */
VPRIVATE void yankPolys();

/* generic utilities */
VPRIVATE int roundX(float x);
VPRIVATE void sintc(char list[], int *length, int ival);
VPRIVATE void rgb2cindx(int *colorIndex, float red, float green, float blue);
#if 0
VPRIVATE void cindx2rgb(float *red, float *green, float *blue, int colorIndex);
#endif
VPRIVATE void xcrossy(double u[], double v[], double w[]);
VPRIVATE double norm2(double u[], int n);
VPRIVATE void normalize(double u[], int n);

/* polygon methods (simple) */
VPRIVATE void Poly_findCentroid(Poly *a);
VPRIVATE void Poly_swapVert0and1(Poly *a);
VPRIVATE void Poly_getMinMaxCentroid(Poly *a);
VPRIVATE void Poly_getIntercepts(Poly *a, Poly *b, int *no, Vert vo[]);
VPRIVATE void Poly_copy(Poly *a, Poly *b);
VPRIVATE void Poly_AblocksB(Poly *a, Poly *b);
VPRIVATE void Poly_matlabOut(
    Poly *a, Poly *b, Poly *c, Poly *d,
    int no, Vert vo[], double obc[], char *fname);

/* polygon methods (complex; intersection, area, etc) */
VPRIVATE int Poly_pointInTriangle(Poly *a, double x, double y, double TOL);
VPRIVATE void Poly_overlapTriangles(Poly *a, Poly *b, Poly *c);
VPRIVATE double Poly_evalTriangleZ(Poly *a, double x, double y);
VPRIVATE int Poly_compareTriangles(const void* A, const void* B);
VPRIVATE int Poly_compareMaxX(const void* A, const void* B);
VPRIVATE int Poly_compareMaxY(const void* A, const void* B);
VPRIVATE int Poly_compareMaxZ(const void* A, const void* B);
VPRIVATE int IntPoly_compareMaxX(const void* A, const void* B);
VPRIVATE int IntPoly_compareMaxY(const void* A, const void* B);
VPRIVATE int IntPoly_compareMaxZ(const void* A, const void* B);
VPRIVATE double Poly_areaTriangle(Poly *a);

/* polygon array methods (ordering, cutting, etc) */
VPRIVATE void Polys_paintOrdering(Poly tri[], int ntri,
    int xo[], int yo[], int zo[]);
VPRIVATE void Polys_removeBackTriangles(Poly *tri[], int *ntri);
VPRIVATE void Polys_buildConstraints(
    Poly tri[], int ntri, int xo[], int yo[], int zo[], int nord);
VPRIVATE void Polys_boxConstraints(
    Poly tri[], int ntri, int guys[], int nguys);
VPRIVATE int Polys_testCut(Poly tri[], int ntri,
    int xo[], int yo[], int zo[], int nord,
    int *lsize, int *rsize);
VPRIVATE void Polys_makeCut(Poly tri[], int ntri,
    int xo[], int yo[], int zo[], int nord,
    int whichCut, int nleft, int nright,
    int xleft[], int xright[],
    int yleft[], int yright[],
    int zleft[], int zright[]);

/* Better PS generation (borrowed from PLTMG with help from R. Bank) */
VPRIVATE void psgenHeader(void);
VPRIVATE void psgenTrailer(void);
VPRIVATE void psgenPaint(int outline);
VPRIVATE void psgenPaintPoly(Poly *p, int mode);
VPRIVATE void psgenUtl(int ncolor,
    float red[], float green[], float blue[], int cidx[]);
VPRIVATE void psgenPath(float x[], float y[], int n, int icolor, int itype);

/*
 * ***************************************************************************
 * Public routines
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Oglps_begin
 *
 * Purpose:  Setup the feedback buffer for the OpenGL library to render into.
 *
 * Notes:    We malloc the float, triangle, and edge buffer areas,
 *           set glRenderMode to GL_FEEDBACK, and finish by opening the
 *           output postscript file.
 *
 *           The input parameters are interpretted as:
 *
 *               filename  ==> name of eventual output PostScript file
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Oglps_begin(void)
{
    GLboolean zbufferPresent;
    int rc, renderMode;

    /* make sure we are not already in GL_FEEDBACK mode */
    glGetIntegerv( GL_RENDER_MODE, &renderMode );
    VJMPERR1( renderMode == GL_RENDER );

    /* initialize the feedback float buffer */
    if ( floatBuffer != VNULL ) free( floatBuffer );
    floatBufferNum = 0;
    floatBuffer = VNULL;
    floatBuffer = (float*)calloc( floatBufferMax, sizeof(float) );
    VJMPERR1( floatBuffer != VNULL );

    /* initialize the triangle buffer */
    if ( triaBuffer != VNULL ) free( triaBuffer );
    triaBufferNum = 0;
    triaBuffer = VNULL;
    triaBuffer = (Poly*)calloc( triaBufferMax, sizeof(Poly) );
    VJMPERR1( triaBuffer != VNULL );
  
    /* initialize the edge buffer */
    if ( edgeBuffer != VNULL ) free( edgeBuffer );
    edgeBufferNum = 0;
    edgeBuffer = VNULL;
    edgeBuffer = (Poly*)calloc( edgeBufferMax, sizeof(Poly) );
    VJMPERR1( edgeBuffer != VNULL );
  
    /* make sure we have a z-buffer here to make everything possible */
    glGetBooleanv( GL_DEPTH_TEST, &zbufferPresent );
    VJMPERR1( zbufferPresent );

    /* register feedback buffer (must happen BEFORE changing to GL_FEEDBACK) */
    glFeedbackBuffer( floatBufferMax, GL_3D_COLOR, floatBuffer );

    /* switch to GL_FEEDBACK mode (must happen AFTER registering the buffer) */
    rc = glRenderMode( GL_FEEDBACK );
    VJMPERR1( rc == 0 );

    /* return without error */
    return;

    /* return with error */
  VERROR1:
    fprintf(stderr, "Oglps_begin: problem occurred (bailing out).\n");
}

/*
 * ***************************************************************************
 * Routine:  Oglps_end
 *
 * Purpose:  Feed triangles from the OpenGL library into our buffer
 *           and output to file.
 *
 * Notes:    We flush the OpenGL rendering buffer, grab the triangles and
 *           edges from feedback buffer, construct a proper ordering for the
 *           painter's algorithm, and finally write the postscript output.
 *
 *           The input parameters are interpretted as:
 *
 *               outLine   ==> 0=use filled triangles
 *                             1=use filled triangles and then outline them
 *
 *               inColor   ==> 0=grayscale
 *                             1=color
 *
 *               doCulling ==> 0=don't cull (render everything)
 *                             1=cull (remove backface triangles before
 *                               rendering)
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Oglps_end(int outLine, int inColor, int doCulling)
{
    int i, renderMode, rc;

    /* make sure we were in GL_FEEDBACK mode */
    glGetIntegerv( GL_RENDER_MODE, &renderMode );
    VJMPERR1( renderMode == GL_FEEDBACK );

    /* flush the OpenGL pipeline */
    glFinish();

    /* retrieve triangles and edges from feedback buffer; check for error */
    floatBufferNum = glRenderMode( GL_FEEDBACK );
    VJMPERR2(floatBufferNum >= 0);

    /* pull the triangles and edges out of the feedback float buffer */
    yankPolys();

    /* switch back to GL_RENDER mode */
    rc = glRenderMode( GL_RENDER );
    VJMPERR3( rc == 0 );

    /* cull back-facing faces if requested (e.g. these are inside in tets) */
    if (doCulling) Polys_removeBackTriangles( &triaBuffer, &triaBufferNum );

    /* produce an initial ordering based on zmin values for each triangle */
    if (triaBufferNum > 0) {
        qsort( triaBuffer, triaBufferNum, sizeof(Poly), Poly_compareMaxZ );
        xord = (int*)calloc( triaBufferNum, sizeof(int) );
        yord = (int*)calloc( triaBufferNum, sizeof(int) );
        zord = (int*)calloc( triaBufferNum, sizeof(int) );
        for (i=0; i<triaBufferNum; i++) {
            xord[i] = i;
            yord[i] = i;
            zord[i] = i;
        }
        qsort( xord, triaBufferNum, sizeof(int), IntPoly_compareMaxX );
        qsort( yord, triaBufferNum, sizeof(int), IntPoly_compareMaxY );
        qsort( zord, triaBufferNum, sizeof(int), IntPoly_compareMaxZ );
    }

    /* produce triangle ordering for drawing with the painter's algorithm */
    Polys_paintOrdering( triaBuffer, triaBufferNum, xord, yord, zord);

    /* output postscript header, all triangles, and a postscript trailer */
    psgenHeader();
    fprintf(stderr, "Oglps_end: opening <%s>\n", psFileName);
    psgenPaint(outLine);
    fprintf(stderr, "Oglps_end: closing <%s>\n", psFileName);
    psgenTrailer();

    /* memory usage statistics */
    fprintf(stderr, "Oglps_end: fbuffer usage: <%d/%d> floats\n",
        floatBufferNum, floatBufferMax);
    fprintf(stderr, "Oglps_end: tbuffer usage: <%d/%d> triangles\n",
        triaBufferNum, triaBufferMax);
    fprintf(stderr, "Oglps_end: ebuffer usage: <%d/%d> edges\n",
        edgeBufferNum, edgeBufferMax);

    /* free everything */
    if ( xord != VNULL ) free( xord ); xord = VNULL;
    if ( yord != VNULL ) free( yord ); yord = VNULL;
    if ( zord != VNULL ) free( zord ); zord = VNULL;

    /* free everything */
    if ( floatBuffer != VNULL ) free( floatBuffer );
    floatBufferNum = 0;
    floatBuffer = VNULL;
    if ( triaBuffer != VNULL ) free( triaBuffer );
    triaBufferNum = 0;
    triaBuffer = VNULL;
    if ( edgeBuffer != VNULL ) free( edgeBuffer );
    edgeBufferNum = 0;
    edgeBuffer = VNULL;

    /* return without error */
    return;

    /* return with error */
  VERROR1:
    fprintf(stderr, "Oglps_end: PROBLEM: Not currently in FEEDBACK mode.\n");
    fprintf(stderr, "Oglps_end: BAILING OUT.\n");
    return;

  VERROR2:
    fprintf(stderr, "Oglps_end: PROBLEM: Feedback buffer not available.\n");
    fprintf(stderr, "Oglps_end: BAILING OUT.\n");
    return;

  VERROR3:
    fprintf(stderr, "Oglps_end: PROBLEM: Reset back to RENDER mode failed.\n");
    fprintf(stderr, "Oglps_end: BAILING OUT.\n");
    return;
}

/*
 * ***************************************************************************
 * Routine:  Oglps_gen
 *
 * Purpose:  Quick and dirty postscript generator (low-resolution only).
 *
 * Notes:    This generator is a modified example from Mark Kilgard's book.
 *
 *           The input parameters are interpretted as:
 *
 *               filename  ==> name of file containing PostScript output
 *
 *               inColor   ==> 0=grayscale
 *                             1=color
 *
 *               width     ==> width of input image in pixels
 *
 *               height    ==> height of input image in pixels
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Oglps_gen(char *filename, int inColor, int width, int height)
{
    int swapbytes, lsbfirst, rowlength, skiprows, skippixels, alignment;
    int i, pos, components;
    int size;
    unsigned char *curpix;
    GLenum format;
    void *pixels;
    FILE *fp;

    fprintf(stderr, "Oglps_gen: started generating PS from a pixmap..");

    /* setup for pixel grab */
    if (inColor) {
        format = GL_RGB;
        size = width * height * 3;
    } else {
        format = GL_LUMINANCE;
        size = width * height * 1;
    }
    pixels = (void *)malloc(size);
    VJMPERR1(pixels != VNULL);

    /* store current GL_PACK settings */
    glGetIntegerv(GL_PACK_SWAP_BYTES, &swapbytes);
    glGetIntegerv(GL_PACK_LSB_FIRST, &lsbfirst);
    glGetIntegerv(GL_PACK_ROW_LENGTH, &rowlength);
    glGetIntegerv(GL_PACK_SKIP_ROWS, &skiprows);
    glGetIntegerv(GL_PACK_SKIP_PIXELS, &skippixels);
    glGetIntegerv(GL_PACK_ALIGNMENT, &alignment);
    glPixelStorei(GL_PACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_PACK_LSB_FIRST, GL_FALSE);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    /* actual pixel grab */
    glReadPixels(0, 0, width, height, format,
        GL_UNSIGNED_BYTE, (void *) pixels);

    /* restore to original GL_PACK modes */
    glPixelStorei(GL_PACK_SWAP_BYTES, swapbytes);
    glPixelStorei(GL_PACK_LSB_FIRST, lsbfirst);
    glPixelStorei(GL_PACK_ROW_LENGTH, rowlength);
    glPixelStorei(GL_PACK_SKIP_ROWS, skiprows);
    glPixelStorei(GL_PACK_SKIP_PIXELS, skippixels);
    glPixelStorei(GL_PACK_ALIGNMENT, alignment);

    /* okay generate a quick & dirty postscript file using the pixel data */
    if (inColor) components = 3;     /* Red, green, blue. */
    else         components = 1;     /* Luminance. */
    fp = fopen(filename, "w");
    VJMPERR1(fp != VNULL);
    fprintf(fp, "%%!PS-Adobe-2.0 EPSF-1.2\n");
    fprintf(fp, "%%%%Creator: OpenGL pixmap render output\n");
    fprintf(fp, "%%%%BoundingBox: 0 0 %d %d\n", width, height);
    fprintf(fp, "%%%%EndComments\n");
    fprintf(fp, "gsave\n");
    fprintf(fp, "/bwproc {\n");
    fprintf(fp, "    rgbproc\n");
    fprintf(fp, "    dup length 3 idiv string 0 3 0\n");
    fprintf(fp, "    5 -1 roll {\n");
    fprintf(fp, "    add 2 1 roll 1 sub dup 0 eq\n");
    fprintf(fp, "    { pop 3 idiv 3 -1 roll dup 4 -1 roll dup\n");
    fprintf(fp, "        3 1 roll 5 -1 roll put 1 add 3 0 }\n");
    fprintf(fp, "    { 2 1 roll } ifelse\n");
    fprintf(fp, "    } forall\n");
    fprintf(fp, "    pop pop pop\n");
    fprintf(fp, "} def\n");
    fprintf(fp, "systemdict /colorimage known not {\n");
    fprintf(fp, "    /colorimage {\n");
    fprintf(fp, "        pop\n");
    fprintf(fp, "        pop\n");
    fprintf(fp, "        /rgbproc exch def\n");
    fprintf(fp, "        { bwproc } image\n");
    fprintf(fp, "    } def\n");
    fprintf(fp, "} if\n");
    fprintf(fp, "/picstr %d string def\n", width * components);
    fprintf(fp, "%d %d scale\n", width, height);
    fprintf(fp, "%d %d %d\n", width, height, 8);
    fprintf(fp, "[%d 0 0 %d 0 0]\n", width, height);
    fprintf(fp, "{currentfile picstr readhexstring pop}\n");
    fprintf(fp, "false %d\n", components);
    fprintf(fp, "colorimage\n");
    curpix = (unsigned char *) pixels;
    pos = 0;
    for (i = width * height * components; i > 0; i--) {
        fprintf(fp, "%02hx", *curpix++);
        if (++pos >= 32) {
            fprintf(fp, "\n");
            pos = 0;
        }
    }
    if (pos) fprintf(fp, "\n");
    fprintf(fp, "grestore\n");
    fprintf(fp, "showpage\n");
    free(pixels);
    fclose(fp);
    fprintf(stderr, "..done.\n");

    /* return without error */
    return;

    /* return with error */
  VERROR1:
    fprintf(stderr, "Oglps_gen: problem occurred (bailing out).\n");
}

/*
 * ***************************************************************************
 * Private routines
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  yankPolys
 *
 * Purpose:  Yank out all triangles and edges from OpenGL feedback buffer.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void yankPolys(void)
{
    int i, j, bufPtr;
    float objectType;
    Color vc;
    Poly pp;

    Xmin =  VLARGE;
    Xmax = -VLARGE;
    Ymin =  VLARGE;
    Ymax = -VLARGE;

    bufPtr=0;
    while (bufPtr < floatBufferNum) {

        /* "doubling malloc" approach to growing triangle array dynamically */
        while ( triaBufferMax <= triaBufferNum ) {
            triaBufferMax *= 2;
            triaBuffer = (Poly*)realloc(triaBuffer,triaBufferMax*sizeof(Poly));
            VJMPERR1( triaBuffer != VNULL );
        }

        /* "doubling malloc" approach to growing edge array dynamically */
        while ( edgeBufferMax <= edgeBufferNum ) {
            edgeBufferMax *= 2;
            edgeBuffer = (Poly*)realloc(edgeBuffer,edgeBufferMax*sizeof(Poly));
            VJMPERR1( edgeBuffer != VNULL );
        }

        /* grab the object type as the first field */
        objectType = floatBuffer[bufPtr++];

        /* pull out all necessary floats to characterize the object */
        if ( objectType == GL_POINT_TOKEN ||
             objectType == GL_LINE_TOKEN ||
             objectType == GL_LINE_RESET_TOKEN ||
             objectType == GL_POLYGON_TOKEN ) {
            if ( objectType == GL_POINT_TOKEN ) {
                pp.nv = 1;
            } else if ( objectType == GL_LINE_TOKEN ||
                        objectType == GL_LINE_RESET_TOKEN ) {
                pp.nv = 2;
            } else if ( objectType == GL_POLYGON_TOKEN ) {
                pp.nv = (int)floatBuffer[bufPtr++];
            } else { VJMPERR1(0); }

            VJMPERR1( (1<=pp.nv) && (pp.nv<=VMAXPV) );

            /* grab all vertex locations and colors for this object */
            pp.c.r = 0.;
            pp.c.g = 0.;
            pp.c.b = 0.;
            pp.c.a = 0.;
            for (i=0; i<pp.nv; i++) {

                /* grab the vertex */
                pp.v[i].x = floatBuffer[bufPtr++];
                pp.v[i].y = floatBuffer[bufPtr++];
                pp.v[i].z = floatBuffer[bufPtr++];

                /* grab the vertex color */
                vc.r = floatBuffer[bufPtr++];
                vc.g = floatBuffer[bufPtr++];
                vc.b = floatBuffer[bufPtr++];
                vc.a = floatBuffer[bufPtr++];

                /* check color for correct rgb range */
                if (!( (0.0-VSMALL <= vc.r) && (vc.r <= 1.0+VSMALL) ) ) {
                    fprintf(stderr,"yankPolys: "
                        "MacOSX OpenGL BUG (& Workaround) Triggered: "
                        "vc.r=<%17.5le>\n",(double)vc.r);
                    vc.r = 1.0;
                }
                if (!( (0.0-VSMALL <= vc.g) && (vc.g <= 1.0+VSMALL) ) ) {
                    fprintf(stderr,"yankPolys: "
                        "MacOSX OpenGL BUG (& Workaround) Triggered: "
                        "vc.g=<%17.5le>\n",(double)vc.g);
                    vc.g = 1.0;
                }
                if (!( (0.0-VSMALL <= vc.b) && (vc.b <= 1.0+VSMALL) ) ) {
                    fprintf(stderr,"yankPolys: "
                        "MacOSX OpenGL BUG (& Workaround) Triggered: "
                        "vc.b=<%17.5le>\n",(double)vc.b);
                    vc.b = 1.0;
                }
                if (!( (0.0-VSMALL <= vc.a) && (vc.a <= 1.0+VSMALL) ) ) {
                    fprintf(stderr,"yankPolys: "
                        "MacOSX OpenGL BUG (& Workaround) Triggered: "
                        "vc.a=<%17.5le>\n",(double)vc.a);
                    vc.a = 1.0;
                }

                /* accumlate vertex color into the total color for object */
                pp.c.r += vc.r;
                pp.c.g += vc.g;
                pp.c.b += vc.b;
                pp.c.a += vc.a;
            }

            /* object color is "centroid" of vertex colors in color space */
            pp.c.r /= pp.nv;
            pp.c.g /= pp.nv;
            pp.c.b /= pp.nv;
            pp.c.a /= pp.nv;

            /* discard points */
            if ( pp.nv == 1 ) {

                /* do nothing */

            /* save edges */
            } else if ( pp.nv == 2 ) {

                /* get edge centroid, xmin/xmax, ymin/ymax, zmin/zmax */
                Poly_getMinMaxCentroid( &pp );

                /* check vertex locations for box containment */
                for (j=0; j<pp.nv; j++)
                    if ((VABS(pp.v[j].x) > VBOX) || (VABS(pp.v[j].y) > VBOX))
                        fprintf(stderr,"yankPolys: PROBLEM: "
                            "pp.x[%d]=<%g> pp.y[%d]=<%g>\n",
                            j, pp.v[j].x, j, pp.v[j].y);

                /* save data to new edge buffer location */
                edgeBuffer[edgeBufferNum] = pp;
                edgeBufferNum++;

            /* save triangles */
            } else if ( pp.nv == 3 ) {

                /* get triangle centroid, xmin/xmax, ymin/ymax, zmin/zmax */
                Poly_getMinMaxCentroid( &pp );

                /* check vertex locations for box containment */
                for (j=0; j<pp.nv; j++)
                    if ((VABS(pp.v[j].x) > VBOX) || (VABS(pp.v[j].y) > VBOX))
                        fprintf(stderr,"yankPolys: PROBLEM: "
                            "pp.x[%d]=<%g> pp.y[%d]=<%g>\n",
                            j, pp.v[j].x, j, pp.v[j].y);

                /* save data to new triangle buffer location */
                triaBuffer[triaBufferNum] = pp;
                triaBufferNum++;

            /* discard polygons which are higher order than triangles */
            } else {

                fprintf(stderr,"yankPolys: "
                    "Polygon discarded (more than three sides): "
                    "pp.nv=<%d>\n",pp.nv);

            }

        } else { VJMPERR1(0); }
    }

    /* return without error */
    return;

    /* return with error */
  VERROR1:
    fprintf(stderr, "yankPolys: problem occurred (bailing out).\n");
}

/*
 * ***************************************************************************
 * Routine:  roundX
 *
 * Purpose:  Round a float to nearlest int
 *           (yeah, this really is not in math.h...)
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
int roundX(float x)
{
    return (int)floor( x + 0.5 );
}

/*
 * ***************************************************************************
 * Routine:  sintc
 *
 * Purpose:  Convert integer to a character string.
 *
 * Author:   Randy Bank
 * ***************************************************************************
 */
void sintc(char list[], int *length, int ival)
{
    int i, j, n, temp[10];

    if (ival == 0) {
        *length = 1;
        list[0] = '0';
        list[1] = '\0';
    } else {
        *length = 0;
        n = abs(ival);
        while (n > 0) {
            j = n / 10;
            i = n - j * 10;
            (*length)++;
            temp[*length-1] = i+1;
            n=j;
        }
        if (ival < 0) {
            list[0] = '-';
            for (i=0; i<(*length); i++) {
                list[i+1] = digits[ temp[*length-i-1] - 1];
            }
            ++(*length);
        } else {
            for (i=0; i<(*length); i++) {
                list[i] = digits[ temp[*length-i-1] - 1];
            }
        }
        list[(*length)] = '\0';
    }
    return;
}

/*
 * ***************************************************************************
 * Routine:  rgb2cindx
 *
 * Purpose:  Convert rgb values on [0,1] to a color index on [0,base**3-1]
 *
 * Author:   Randy Bank
 * ***************************************************************************
 */
void rgb2cindx(int *colorIndex, float red, float green, float blue)
{
    int ired, igreen, iblue;

    ired   = roundX(red   * (base-1));
    igreen = roundX(green * (base-1));
    iblue  = roundX(blue  * (base-1));
    (*colorIndex) = (ired*base + igreen)*base +iblue;
}

/*
 * ***************************************************************************
 * Routine:  cindx2rgb
 *
 * Purpose:  Convert color index on [0,base**3-1] to rgb values on [0,1]
 *
 * Author:   Randy Bank
 * ***************************************************************************
 */
#if 0
void cindx2rgb(float *red, float *green, float *blue, int colorIndex)
{
    int ired, igreen, iblue, ii;

    ii     = colorIndex / base;
    iblue  = colorIndex - base*ii;
    ired   = ii / base;
    igreen = ii - base*ired;

    (*red)   = (float)ired   / (float)(base-1);
    (*green) = (float)igreen / (float)(base-1);
    (*blue)  = (float)iblue  / (float)(base-1);
}
#endif

/*
 * ***************************************************************************
 * Routine:  xcrossy
 *
 * Purpose:  Cross-product of two 3-vectors.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void xcrossy(double u[], double v[], double w[])
{
    u[0] = v[1]*w[2] - v[2]*w[1];
    u[1] = v[2]*w[0] - v[0]*w[2];
    u[2] = v[0]*w[1] - v[1]*w[0];
}

/*
 * ***************************************************************************
 * Routine:  norm2
 *
 * Purpose:  Take the 2-norm of an n-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE double norm2(double u[], int n)
{
    int i;
    double result = 0.0;
    for (i=0; i<n; i++) result += u[i]*u[i];
    return VSQRT( result );
}

/*
 * ***************************************************************************
 * Routine:  normalize
 *
 * Purpose:  Normalize an n-vector.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void normalize(double u[], int n)
{
    int i;
    double nscale = norm2(u,n);
    if (nscale <= 0.0) {
        nscale = 1.0;
        fprintf(stderr,"normalize: cannot normalize a zero vector.\n");
    }
    for (i=0; i<n; i++) u[i] /= nscale;
}

/*
 * ***************************************************************************
 * Routine:  Poly_areaTriangle
 *
 * Purpose:  Compute the (2-measure) area of a triangle.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE double Poly_areaTriangle(Poly *a)
{
    double value = 0.0;

    VASSERT( a->nv == 3 );

    value = (a->v[1].x-a->v[0].x)*(a->v[2].y-a->v[0].y)
          - (a->v[2].x-a->v[0].x)*(a->v[1].y-a->v[0].y);
    return value;
}

/*
 * ***************************************************************************
 * Routine:  Poly_pointInTriangle
 *
 * Purpose:  Determine whether or not a point is inside a given triangle.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int Poly_pointInTriangle(Poly *a, double x, double y, double TOL)
{
    Poly aa, t0, t1, t2;
    
    VASSERT( a->nv == 3 );

    /* we need to work with a counter-clockwise ordering here */
    Poly_copy( &aa, a );
    if (Poly_areaTriangle(&aa) < 0.0) Poly_swapVert0and1(&aa);

    t0.nv = 3;
    t0.v[0].x = x;         t0.v[0].y = y;
    t0.v[1].x = aa.v[0].x; t0.v[1].y = aa.v[0].y;
    t0.v[2].x = aa.v[1].x; t0.v[2].y = aa.v[1].y;

    t1.nv = 3;
    t1.v[0].x = x;         t1.v[0].y = y;
    t1.v[1].x = aa.v[1].x; t1.v[1].y = aa.v[1].y;
    t1.v[2].x = aa.v[2].x; t1.v[2].y = aa.v[2].y;

    t2.nv = 3;
    t2.v[0].x = x;         t2.v[0].y = y;
    t2.v[1].x = aa.v[2].x; t2.v[1].y = aa.v[2].y;
    t2.v[2].x = aa.v[0].x; t2.v[2].y = aa.v[0].y;

    if (  (Poly_areaTriangle(&t0) >= -TOL)
       && (Poly_areaTriangle(&t1) >= -TOL)
       && (Poly_areaTriangle(&t2) >= -TOL) ) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * ***************************************************************************
 * Routine:  Poly_overlapTriangles
 *
 * Purpose:  Compute the exact overlap polygon of two input triangles and
 *           also compute its baricenter.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Poly_overlapTriangles(Poly *a, Poly *b, Poly *c)
{
    int j, k, kk, nn, nn2, found;
    Vert vt[15];

    VASSERT( a->nv == 3 );
    VASSERT( b->nv == 3 );

    if (  (a->xmax < b->xmin)
       || (a->xmin > b->xmax)
       || (a->ymax < b->ymin)
       || (a->ymin > b->ymax) ) {
        c->nv = 0;
    } else {

        /* calc (up to) 9 intercepts of 3 lines of 1st guy and 3 lines of 2nd */
        Poly_getIntercepts(a, b, &nn, vt);
        if ( ! ((0 <= nn) && (nn <= 9)) )
            fprintf(stderr,"Poly_overlapTriangles: intercepts = <%d>\n", nn);
        VASSERT( (0 <= nn) && (nn <= 15) );

        /* add vertices of each triangle to the overlap polygon vertex list */
        kk = 0;
        for (k=0; k<a->nv; k++) {
            if (Poly_pointInTriangle(b,a->v[k].x,a->v[k].y,VTINY)) {
                vt[nn+kk].x = a->v[k].x;
                vt[nn+kk].y = a->v[k].y;
                kk++;
            }
        }
        for (k=0; k<b->nv; k++) {
            if (Poly_pointInTriangle(a,b->v[k].x,b->v[k].y,VTINY)) {
                vt[nn+kk].x = b->v[k].x;
                vt[nn+kk].y = b->v[k].y;
                kk++;
            }
        }
        nn += kk;
        if ( ! ((0 <= nn) && (nn <= 15)) )
            fprintf(stderr,"Poly_overlapTriangles: intercepts = <%d>\n", nn);
        VASSERT( (0 <= nn) && (nn <= 15) );

        /* remove any duplicate vertices */
        nn2 = 0;
        for (k=0; k<nn; k++) {
            found = 0;
            for (j=0; j<nn2; j++) {
                if (  (VABS(vt[k].x-c->v[j].x)<VTINY)
                   && (VABS(vt[k].y-c->v[j].y)<VTINY) )
                    found = 1;
            }
            if (!found) {
                c->v[nn2].x = vt[k].x;
                c->v[nn2].y = vt[k].y;
                c->v[nn2].z = 0.0;
                nn2++;
                VASSERT( nn2 <= VMAXPV );
            }
        }
        c->nv = nn2;
        VASSERT( (0 <= c->nv) && (c->nv <= VMAXPV) );

        /* compute centroid of common overlap polygon (1-6 sided possible) */
        Poly_getMinMaxCentroid(c);

        /* geom (exact arithmetic), can never get more than 6 vertices */
        if (c->nv > 6) {
            fprintf(stderr,"Poly_overlapTriangles: c->nv=<%d>\n",c->nv);
            Poly_matlabOut(a, b, VNULL, VNULL, c->nv, c->v, c->bc, "go.m");
        }
#if 0
        Poly_matlabOut(a, b, VNULL, VNULL, c->nv, c->v, c->bc, "go.m");
#endif
    }
}

/*
 * ***************************************************************************
 * Routine:  Poly_evalTriangleZ
 *
 * Purpose:  Evaluate the z-coordinate of an arbitrary (x,y) location
 *           in a triangle that has an arbitrary orientation in R^3.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE double Poly_evalTriangleZ(Poly *a, double x, double y)
{
    double aa, bb, cc, x0, y0, z0, x1, y1, z1, v0[3], v1[3], norm[3];

    VASSERT( a->nv == 3 );

    /* first verify that point is in the triangle */
    VASSERT( Poly_pointInTriangle(a,x,y,10.0*VTINY) );

    /* okay get the z-value */
    z1 = 0.0;
    v0[0] = a->v[1].x - a->v[0].x;
    v0[1] = a->v[1].y - a->v[0].y;
    v0[2] = a->v[1].z - a->v[0].z;
    v1[0] = a->v[2].x - a->v[0].x;
    v1[1] = a->v[2].y - a->v[0].y;
    v1[2] = a->v[2].z - a->v[0].z;
    xcrossy(norm,v0,v1);
    normalize(norm,3);
    aa = norm[0];
    bb = norm[1];
    cc = norm[2];
    x0 = a->v[0].x;
    y0 = a->v[0].y;
    z0 = a->v[0].z;
    x1 = x;
    y1 = y;
    if (VABS(cc) < VTINY) {
        z1 = z0;
    } else {
        z1 = z0 - (aa*(x1-x0) + bb*(y1-y0)) / cc;
    }
    return z1;
}

/*
 * ***************************************************************************
 * Routine:  Poly_compareTriangles
 *
 * Purpose:  Compare two triangles for z-buffer depth buy computing their
 *           exact overlap polygon and using the centroid of that overlap
 *           polygon for comparing their z-buffer depths.
 *
 * Notes:    For sets of non-intersecting triangles, this comparison function
 *           unambigously determines front-back relationships among triangles.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int Poly_compareTriangles(const void* A, const void* B)
{
    Poly *a = (Poly*)A;
    Poly *b = (Poly*)B;

    double aDepth, bDepth;
    Poly c;

    VASSERT( a->nv == 3 );
    VASSERT( b->nv == 3 );

    /* ***************************** */
    /* return  0:  draw either first */
    /* return -1:  draw A first      */
    /* return  1:  draw B first      */
    /* ***************************** */

    /* compute common overlap polygon */
    Poly_overlapTriangles(a, b, &c);
    VASSERT( (0 <= c.nv) && (c.nv <= VMAXPV) );

    /* no overlap: just return a zero to allow for arbitrary ordering */
    if (c.nv == 0) {

        /* evaluate z-value of triangles at separate baricenters */
        aDepth = a->bc[2];
        bDepth = b->bc[2];

    /* overlap: calc z-value for each triangle at baricenter of common poly */
    } else { /* (c.nv > 0) */

        /* evaluate z-value of triangles at baricenter of common overlap */
        aDepth = Poly_evalTriangleZ(a, c.bc[0], c.bc[1]);
        bDepth = Poly_evalTriangleZ(b, c.bc[0], c.bc[1]);
    }

    if ( VABS(aDepth-bDepth) < VTINY ) {
        /* DO NOT make constraint; either can be drawn first! */
        /* (we use a "nearly zero" test to deal with roundoff) */
        return  0;
    } else if ( aDepth > bDepth ) {
        return -1;
    } else if ( aDepth < bDepth ) {
        return  1;
    } else {
        /* we can only get here if some NANs are generated... */
        VASSERT(0);
    }

    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Poly_compareMaxX
 *
 * Purpose:  Compare two triangles for X-buffer depth based simply on their
 *           minimum X-buffer values throughout each entire triangle.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int Poly_compareMaxX(const void* A, const void* B)
{
    Poly *a = (Poly*)A;
    Poly *b = (Poly*)B;

    double aDepth, bDepth;

    VASSERT( a->nv == 3 );
    VASSERT( b->nv == 3 );

    /* ***************************** */
    /* return  0:  draw either first */
    /* return -1:  draw A first      */
    /* return  1:  draw B first      */
    /* ***************************** */

    /* evaluate maxx for each triangle */
    aDepth = a->xmax;
    bDepth = b->xmax;

    if ( VABS(aDepth-bDepth) < VTINY ) {
        /* DO NOT make constraint; either can be drawn first! */
        /* (we use a "nearly zero" test to deal with roundoff) */
        return  0;
    } else if ( aDepth > bDepth ) {
        return -1;
    } else if ( aDepth < bDepth ) {
        return  1;
    } else {
        /* we can only get here if some NANs are generated... */
        VASSERT(0);
    }

    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Poly_compareMaxY
 *
 * Purpose:  Compare two triangles for Y-buffer depth based simply on their
 *           minimum Y-buffer values throughout each entire triangle.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int Poly_compareMaxY(const void* A, const void* B)
{
    Poly *a = (Poly*)A;
    Poly *b = (Poly*)B;

    double aDepth, bDepth;

    VASSERT( a->nv == 3 );
    VASSERT( b->nv == 3 );

    /* ***************************** */
    /* return  0:  draw either first */
    /* return -1:  draw A first      */
    /* return  1:  draw B first      */
    /* ***************************** */

    /* evaluate maxy for each triangle */
    aDepth = a->ymax;
    bDepth = b->ymax;

    if ( VABS(aDepth-bDepth) < VTINY ) {
        /* DO NOT make constraint; either can be drawn first! */
        /* (we use a "nearly zero" test to deal with roundoff) */
        return  0;
    } else if ( aDepth > bDepth ) {
        return -1;
    } else if ( aDepth < bDepth ) {
        return  1;
    } else {
        /* we can only get here if some NANs are generated... */
        VASSERT(0);
    }

    return 0;
}

/*
 * ***************************************************************************
 * Routine:  Poly_compareMaxZ
 *
 * Purpose:  Compare two triangles for z-buffer depth based simply on their
 *           minimum Z-buffer values throughout each entire triangle.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int Poly_compareMaxZ(const void* A, const void* B)
{
    Poly *a = (Poly*)A;
    Poly *b = (Poly*)B;

    double aDepth, bDepth;

    VASSERT( a->nv == 3 );
    VASSERT( b->nv == 3 );

    /* ***************************** */
    /* return  0:  draw either first */
    /* return -1:  draw A first      */
    /* return  1:  draw B first      */
    /* ***************************** */

    /* evaluate maxz for each triangle */
    aDepth = a->zmax;
    bDepth = b->zmax;

    if ( VABS(aDepth-bDepth) < VTINY ) {
        /* DO NOT make constraint; either can be drawn first! */
        /* (we use a "nearly zero" test to deal with roundoff) */
        return  0;
    } else if ( aDepth > bDepth ) {
        return -1;
    } else if ( aDepth < bDepth ) {
        return  1;
    } else {
        /* we can only get here if some NANs are generated... */
        VASSERT(0);
    }

    return 0;
}

/*
 * ***************************************************************************
 * Routine:  IntPoly_compareMaxX
 *
 * Purpose:  Front-end to Poly_compareMaxX() for sorting integer arrays
 *           of triangle numbers based on minimum X-buffer values.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int IntPoly_compareMaxX(const void* A, const void* B)
{
    Poly *a, *b;
    int AA = *((int*)A);
    int BB = *((int*)B);
    a = triaBuffer+xord[AA];
    b = triaBuffer+xord[BB];
    return Poly_compareMaxX(a, b);
}

/*
 * ***************************************************************************
 * Routine:  IntPoly_compareMaxY
 *
 * Purpose:  Front-end to Poly_compareMaxY() for sorting integer arrays
 *           of triangle numbers based on minimum Y-buffer values.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int IntPoly_compareMaxY(const void* A, const void* B)
{
    Poly *a, *b;
    int AA = *((int*)A);
    int BB = *((int*)B);
    a = triaBuffer+yord[AA];
    b = triaBuffer+yord[BB];
    return Poly_compareMaxY(a, b);
}

/*
 * ***************************************************************************
 * Routine:  IntPoly_compareMaxZ
 *
 * Purpose:  Front-end to Poly_compareMaxZ() for sorting integer arrays
 *           of triangle numbers based on minimum Z-buffer values.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int IntPoly_compareMaxZ(const void* A, const void* B)
{
    Poly *a, *b;
    int AA = *((int*)A);
    int BB = *((int*)B);
    a = triaBuffer+zord[AA];
    b = triaBuffer+zord[BB];
    return Poly_compareMaxZ(a, b);
}

/*
 * ***************************************************************************
 * Routine:  Poly_getIntercepts
 *
 * Purpose:  Compute all overlap intercepts of the edges of two polygons.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Poly_getIntercepts(Poly *a, Poly *b, int *no, Vert vo[])
{
    int i, j;
    double det, idet, t, s, x, y, x2, y2;
    double v0[2], v1[2], v2[2], v3[2], f[2], m[2][2], mi[2][2];

    VASSERT( (0 <= a->nv) && (a->nv <= VMAXPV) );
    VASSERT( (0 <= b->nv) && (b->nv <= VMAXPV) );

    *no = 0;
    for (i=0; i<a->nv; i++) {
        v0[0] = a->v[i].x;
        v0[1] = a->v[i].y;
        v1[0] = a->v[(i+1)%3].x;
        v1[1] = a->v[(i+1)%3].y;

        for (j=0; j<b->nv; j++) {
            v2[0] = b->v[j].x;
            v2[1] = b->v[j].y;
            v3[0] = b->v[(j+1)%3].x;
            v3[1] = b->v[(j+1)%3].y;

            f[0] = v2[0] - v0[0];
            f[1] = v2[1] - v0[1];
            m[0][0] = v1[0] - v0[0];
            m[1][0] = v1[1] - v0[1];
            m[0][1] = v2[0] - v3[0];
            m[1][1] = v2[1] - v3[1];
            det = m[0][0]*m[1][1] - m[0][1]*m[1][0];

            /* if the two lines are not parallel */
            if (VABS(det) > VTINY) {
                idet = 1.0 / det;
                mi[0][0] =   idet * m[1][1];
                mi[1][1] =   idet * m[0][0];
                mi[0][1] = - idet * m[0][1];
                mi[1][0] = - idet * m[1][0];
                t  = mi[0][0]*f[0] + mi[0][1]*f[1];
                s  = mi[1][0]*f[0] + mi[1][1]*f[1];

                /* if common intersection is contained in edges themselves */
                if ( (0.0 <= t) && (t <= 1.0) && (0.0 <= s) && (s <= 1.0) ) {
                    x  = v0[0] + t * (v1[0] - v0[0]);
                    y  = v0[1] + t * (v1[1] - v0[1]);
                    x2 = v2[0] + s * (v3[0] - v2[0]);
                    y2 = v2[1] + s * (v3[1] - v2[1]);
                    if ( ! ((VABS(x-x2) < VTINY) && (VABS(y-y2) < VTINY)) )
                        fprintf(stderr,"Poly_getIntercepts: variation: "
                            "(x-x2,y-y2)=(%15.8e,%15.8e)\n",
                            VABS(x-x2),VABS(y-y2));

                    /* paranoia; should be in triangle since s,t in [0,1] */
#if 1
                    vo[*no].x = x;
                    vo[*no].y = y;
                    (*no)++;
#endif
#if 0
                    if ( Poly_pointInTriangle(a,x,y,VTINY)
                      && Poly_pointInTriangle(b,x,y,VTINY) ) {
                        vo[*no].x = x;
                        vo[*no].y = y;
                        (*no)++;
                    }
#endif
                }
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Poly_findCentroid
 *
 * Purpose:  Compute the centroid of a set of vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Poly_findCentroid(Poly *a)
{
    int k;

    VASSERT( (0 <= a->nv) && (a->nv <= VMAXPV) );

    for (k=0; k<3; k++) a->bc[k] = 0.0;
    for (k=0; k<a->nv; k++) {
        a->bc[0] += a->v[k].x;
        a->bc[1] += a->v[k].y;
        a->bc[2] += a->v[k].z;
    }
    for (k=0; k<3; k++) a->bc[k] /= a->nv;
}

/*
 * ***************************************************************************
 * Routine:  Poly_matlabOut
 *
 * Purpose:  Output some polygons in a MATLAB-compatible form.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Poly_matlabOut(
    Poly *a, Poly *b, Poly *c, Poly *d,
    int no, Vert vo[], double obc[],
    char *fname)
{
    int k;
    FILE *fp;

    fp = fopen(fname, "a");
    fprintf(fp,"clf\n");
    fprintf(fp,"axis('equal');\n");
    fprintf(fp,"hold on\n");
    if (a != VNULL) {
        fprintf(fp,"%% Poly A\n");
        fprintf(fp,"A=[\n");
        for (k=0; k<a->nv; k++)
            fprintf(fp,"%15.8e  %15.8e\n", a->v[k].x, a->v[k].y);
        fprintf(fp,"];\n");
        fprintf(fp,"xA = [ A(:,1) ; A(1,1) ];\n");
        fprintf(fp,"yA = [ A(:,2) ; A(1,2) ];\n");
        fprintf(fp,"plot(xA,yA,'g');\n");
        fprintf(fp,"plot(xA,yA,'og');\n");
    }
    if (b != VNULL) {
        fprintf(fp,"%% Poly B\n");
        fprintf(fp,"B=[\n");
        for (k=0; k<b->nv; k++)
            fprintf(fp,"%15.8e  %15.8e\n", b->v[k].x, b->v[k].y);
        fprintf(fp,"];\n");
        fprintf(fp,"xB = [ B(:,1) ; B(1,1) ];\n");
        fprintf(fp,"yB = [ B(:,2) ; B(1,2) ];\n");
        fprintf(fp,"plot(xB,yB,'--r');\n");
        fprintf(fp,"plot(xB,yB,'or');\n");
    }
    if (c != VNULL) {
        fprintf(fp,"%% Poly C\n");
        fprintf(fp,"C=[\n");
        for (k=0; k<c->nv; k++)
            fprintf(fp,"%15.8e  %15.8e\n", c->v[k].x, c->v[k].y);
        fprintf(fp,"];\n");
        fprintf(fp,"xC = [ C(:,1) ; C(1,1) ];\n");
        fprintf(fp,"yC = [ C(:,2) ; C(1,2) ];\n");
        fprintf(fp,"plot(xC,yC,'--b');\n");
        fprintf(fp,"plot(xC,yC,'ob');\n");
    }
    if (d != VNULL) {
        fprintf(fp,"%% Poly D\n");
        fprintf(fp,"D=[\n");
        for (k=0; k<d->nv; k++)
            fprintf(fp,"%15.8e  %15.8e\n", d->v[k].x, d->v[k].y);
        fprintf(fp,"];\n");
        fprintf(fp,"xD = [ D(:,1) ; D(1,1) ];\n");
        fprintf(fp,"yD = [ D(:,2) ; D(1,2) ];\n");
        fprintf(fp,"plot(xD,yD,'--y');\n");
        fprintf(fp,"plot(xD,yD,'oy');\n");
    }
    if (no > 0) {
        fprintf(fp,"%% Overlap Polygon\n");
        fprintf(fp,"Q=[\n");
        for (k=0; k<no; k++)
            fprintf(fp,"%15.8e  %15.8e\n", vo[k].x, vo[k].y);
        fprintf(fp,"];\n");
        fprintf(fp,"xQ = Q(:,1);\n");
        fprintf(fp,"yQ = Q(:,2);\n");
        fprintf(fp,"plot(xQ,yQ,'o');\n");
    }
    if (no > 0) {
        fprintf(fp,"%% Overlap Polygon Centroid\n");
        fprintf(fp,"P=[\n");
        fprintf(fp,"%15.8e  %15.8e\n", obc[0], obc[1]);
        fprintf(fp,"];\n");
        fprintf(fp,"xP = P(1);\n");
        fprintf(fp,"yP = P(2);\n");
        fprintf(fp,"plot(xP,yP,'xr');\n");
    }
    fprintf(fp,"fprintf('..');\n");
    fprintf(fp,"pause\n");
    fclose(fp);
}

/*
 * ***************************************************************************
 * Routine:  Poly_swapVert0and1
 *
 * Purpose:  Swap the first two vertices in a set of vertices.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Poly_swapVert0and1(Poly *a)
{
    double tmp;

    VASSERT( (0 <= a->nv) && (a->nv <= VMAXPV) );

    tmp = a->v[0].x; a->v[0].x = a->v[1].x; a->v[1].x = tmp;
    tmp = a->v[0].y; a->v[0].y = a->v[1].y; a->v[1].y = tmp;
    tmp = a->v[0].z; a->v[0].z = a->v[1].z; a->v[1].z = tmp;
}

/*
 * ***************************************************************************
 * Routine:  Poly_getMinMaxCentroid
 *
 * Purpose:  Calculate the min/max x/y/z coordinates of a polygon, and also
 *           compute the centroid (baricenter) of the polygon.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Poly_getMinMaxCentroid(Poly *a)
{
    int k;

    VASSERT( (0 <= a->nv) && (a->nv <= VMAXPV) );

    a->xmin =  VLARGE;
    a->xmax = -VLARGE;
    a->ymin =  VLARGE;
    a->ymax = -VLARGE;
    a->zmin =  VLARGE;
    a->zmax = -VLARGE;
    for (k=0; k<a->nv; k++) {
        if (a->v[k].x < a->xmin) a->xmin = a->v[k].x;
        if (a->v[k].x > a->xmax) a->xmax = a->v[k].x;
        if (a->v[k].y < a->ymin) a->ymin = a->v[k].y;
        if (a->v[k].y > a->ymax) a->ymax = a->v[k].y;
        if (a->v[k].z < a->zmin) a->zmin = a->v[k].z;
        if (a->v[k].z > a->zmax) a->zmax = a->v[k].z;
    }
    if (a->xmin < Xmin) Xmin = a->xmin;
    if (a->xmax > Xmax) Xmax = a->xmax;
    if (a->ymin < Ymin) Ymin = a->ymin;
    if (a->ymax > Ymax) Ymax = a->ymax;
    if (a->zmin < Zmin) Zmin = a->zmin;
    if (a->zmax > Zmax) Zmax = a->zmax;
    Xmid = ( Xmax + Xmin ) / 2.;
    Ymid = ( Ymax + Ymin ) / 2.;
    XYscale = 1. / VMAX2( Xmax-Xmin, Ymax-Ymin );

    Poly_findCentroid(a);
}

/*
 * ***************************************************************************
 * Routine:  Poly_copy
 *
 * Purpose:  Copy the contents of one polygon into another polygon.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Poly_copy(Poly *a, Poly *b)
{
    VASSERT( (0 <= b->nv) && (b->nv <= VMAXPV) );
    *a = *b;
}

/*
 * ***************************************************************************
 * Routine:  Poly_AblocksB
 *
 * Purpose:  Record the fact that polygon A blocks polygon B.
 *
 * Notes:    We place "B" on a list that "A" maintains of all guys that he is
 *           blocking from being drawn as long as he is not drawn.  We then
 *           also increment a counter in B that keeps track of how many
 *           guys are blocking it from being drawn.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Poly_AblocksB(Poly *a, Poly *b)
{
    Bloc *curr, *mnew;

    VASSERT( (0 <= a->nv) && (a->nv <= VMAXPV) );
    VASSERT( (0 <= b->nv) && (b->nv <= VMAXPV) );

    mnew=VNULL;
    curr=a->blist;

    if (curr == VNULL) {
        (b->bnum)++;
        curr = (Bloc*)calloc( 1, sizeof(Bloc) );
        curr->guy = b;
        curr->next = VNULL;
        a->blist = curr;
        return;
    } else {
        if ( curr->guy == b ) return;
        while (1) {
            if (curr->next == VNULL) {
                (b->bnum)++;
                mnew = (Bloc*)calloc( 1, sizeof(Bloc) );
                mnew->guy = b;
                mnew->next = VNULL;
                curr->next = mnew; 
                return;
            } else {
                if ( curr->guy == b ) return;
                curr = curr->next;
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Polys_removeBackTriangles
 *
 * Purpose:  Remove all backfacing triangles from the set of triangles.
 *
 * Notes:    This is useful for rendering tetrahedral meshes in which
 *           all backfacing triangles are guaranteed to be buried by
 *           front-facing triangles, and so can be safely culled.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Polys_removeBackTriangles(Poly *tri[], int *ntri)
{
    int i, ii;
    Poly *pp;

    /* input check */
    if (*ntri == 0) return;
    VASSERT( *ntri > 0 );

    /* remove back-facing triangles */
    pp = (Poly*)calloc( (*ntri), sizeof(Poly) );
    ii = 0;
    for (i=0; i<(*ntri); i++) {
        if (Poly_areaTriangle( (*tri)+i ) > 0.0) {
            Poly_copy( pp+ii, (*tri)+i );
            ii++;
        }
    }

    fprintf(stderr,
        "Polys_removeBackTriangles: removed <%d> of <%d> triangles,"
        " leaving <%d> triangles\n", ((*ntri)-ii), (*ntri), ii );

    free(*tri);
    (*ntri) = ii;
    (*tri)  = pp;
}

/*
 * ***************************************************************************
 * Routine:  Polys_buildConstraints
 *
 * Purpose:  MODE1: Build all front-back constraints between all pairs of
 *                  polygons in set of polygons using exact polygon overlaps.
 *
 *           MODE2: Build SOME front-back constraints between pairs of polygons
 *                  in a set of polygons using exact polygon overlaps.
 *                  We only build constraints for polygons which overlap in
 *                  their respective [zmin,zmax] windows.
 *
 * Notes:    To keep the complexity costs down, we bisect the polygons
 *           along an X- or Y- cutting plane and call ourselves recursively
 *           on the bisection children.  Once the polygon set is small
 *           enough, we pair-wise compare all polygons in the set using
 *           the centroid of their exact overlap polygon.  This compare
 *           cannot fail to build the constraints correctly if the polygons
 *           are non-intersecting.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Polys_buildConstraints(
    Poly tri[], int ntri, int xo[], int yo[], int zo[], int nord)
{
    int whichCut, lsize, rsize;
    int *xleft, *xright, *yleft, *yright, *zleft, *zright;

    whichCut = Polys_testCut(tri, ntri, xo, yo, zo, nord, &lsize, &rsize);
    if ( (lsize*lsize + rsize*rsize) < nord*nord ) {
        xleft  = (int*)calloc( lsize, sizeof(int) );
        xright = (int*)calloc( rsize, sizeof(int) );
        yleft  = (int*)calloc( lsize, sizeof(int) );
        yright = (int*)calloc( rsize, sizeof(int) );
        zleft  = (int*)calloc( lsize, sizeof(int) );
        zright = (int*)calloc( rsize, sizeof(int) );
        Polys_makeCut(tri, ntri, xo, yo, zo, nord, whichCut,
            lsize, rsize, xleft, xright, yleft, yright, zleft, zright);
        Polys_buildConstraints(tri, ntri, xleft, yleft, zleft, lsize);
        free(xleft);
        free(yleft);
        free(zleft);
        Polys_buildConstraints(tri, ntri, xright, yright, zright, rsize);
        free(xright);
        free(yright);
        free(zright);
    } else {
        Polys_boxConstraints(tri, ntri, zo, nord);
    }
}

/*
 * ***************************************************************************
 * Routine:  Polys_boxConstraints
 *
 * Purpose:  MODE1: Build all front-back constraints between all pairs of
 *                  polygons in set of polygons using exact polygon overlaps.
 *
 *           MODE2: Build SOME front-back constraints between pairs of polygons
 *                  in a set of polygons using exact polygon overlaps.
 *                  We only build constraints for polygons which overlap in
 *                  their respective [zmin,zmax] windows.
 *
 * Notes:    To keep the complexity costs down, we bisect the polygons
 *           along an X- or Y- cutting plane and call ourselves recursively
 *           on the bisection children.  Once the polygon set is small
 *           enough, we pair-wise compare all polygons in the set using
 *           the centroid of their exact overlap polygon.  This compare
 *           cannot fail to build the constraints correctly if the polygons
 *           are non-intersecting.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void Polys_boxConstraints(
    Poly tri[], int ntri, int guys[], int nguys)
{
    int i, j;
    Poly *a, *b, c;
    double aDepth, bDepth;

    fprintf(stderr,"Polys_boxConstraints: "
        "building constraints for <%d> polygons.\n", nguys);

    /* build the constraints as efficiently as possible */
    for (i=0; i<nguys; i++) {
        a = tri+guys[i];
        if ( ! ((i+1)%1000) )
            fprintf(stderr,"Polys_boxConstraints: "
                "building constraint <%d>\n", i);
        
        /* okay, do the pair-wise compares */
        for (j=i+1; j<nguys; j++) {
            b = tri+guys[j];
            Poly_overlapTriangles(a, b, &c);
            if (c.nv > 0) {
                /* evaluate z-value of triangles at the common point */
                aDepth = Poly_evalTriangleZ(a, c.bc[0], c.bc[1]);
                bDepth = Poly_evalTriangleZ(b, c.bc[0], c.bc[1]);
                if ( VABS(aDepth-bDepth) < VTINY ) {
                    /* DO NOT make constraint; either can be drawn first! */
                    /* (we use a "nearly zero" test to deal with roundoff) */
                } else if ( aDepth > bDepth ) {
                    Poly_AblocksB(a,b);
                } else if ( aDepth < bDepth ) {
                    Poly_AblocksB(b,a);
                } else {
                    /* we can only get here if some NANs are generated... */
                    VASSERT(0);
                }
            }
        }
    }
}

/*
 * ***************************************************************************
 * Routine:  Polys_paintOrdering
 *
 * Purpose:  Find a feasible point in the feasible rendering region.
 *
 * Notes:    We do this VERY quickly; see our paper...
 *
 * Authors:  Michael Holst and Randy Bank
 * ***************************************************************************
 */
VPRIVATE void Polys_paintOrdering(Poly tri[], int ntri,
    int xo[], int yo[], int zo[])
{
    int i, j, ppPtr, curPtr, done;
    Poly *pp, *qq;
    Bloc *curr, *last;

    fprintf(stderr,
        "Polys_paintOrdering: defining feasible region for <%d> polygons.\n",
            ntri);

    /* input check */
    if (ntri == 0) return;
    VASSERT( ntri > 0 );

    /* initialize the constraint count and list */
    /*    tri->bnum  == number of guys that must be ordered before polygon */
    /*    tri->blist == list of guys that triangle blocks from being drawn */
    for (i=0; i<ntri; i++) {
        tri[i].bnum  = 0;
        tri[i].blist = VNULL;
        tri[i].id    = i;
    }

    /* first build the constraint list */
    Polys_buildConstraints(tri, ntri, xo, yo, zo, ntri);

    /* start traversing final list and resolv constraints */
    pp = (Poly*)calloc( ntri, sizeof(Poly) );
    ppPtr  = 0;
    curPtr = 0;
    for (i=0; i<ntri; i++) {
        if ( ! (i%1000) )
          fprintf(stderr,"Polys_paintOrdering: resolving constraint <%d>\n",i);

        if ( i >= ppPtr ) {
            j=curPtr;
            done=0;
            while (!done) {
                if (tri[j].bnum == 0) {
                    tri[j].bnum = -1;
                    Poly_copy( pp+ppPtr, tri+j );
                    ppPtr++;
                    curPtr = j+1;
                    done=1;
                } else if (j==ntri-1) {
                    fprintf(stderr,"Polys_paintOrdering: "
                        "constraint resolution failed.\n");
                    fprintf(stderr,"Polys_paintOrdering: the "
                        "painter's algorithm WILL NOT work for this scene.\n");
                    fprintf(stderr,"Polys_paintOrdering: "
                        "reverting to quicksort.\n");
                    qsort( triaBuffer, triaBufferNum, sizeof(Poly),
                        Poly_compareTriangles );
                    return;
                } else {
                    j++;
                }
            }
        }
        VASSERT( ppPtr > i );

        curr = pp[i].blist;
        while (curr != VNULL) {
            qq = curr->guy;
            VASSERT( qq != VNULL );
            VASSERT( qq->bnum > 0 );
            (qq->bnum)--;
            if ( ((qq->bnum) == 0) && (qq->id < curPtr)) {
                qq->bnum = -1;
                Poly_copy( pp+ppPtr, qq );
                ppPtr++;
            }
            last = curr;
            curr = curr->next;
            free(last);
        }
    }

    /* copy the list back in the correct order */
    for (i=0; i<ntri; i++)
        Poly_copy( tri+i, pp+i );
    free(pp);

    fprintf(stderr,"Polys_paintOrdering: "
        "constraint resolution succeeded.\n");
    fprintf(stderr,"Polys_paintOrdering: "
        "the painter's algorithm WILL work for this scene.\n");
}

/*
 * ***************************************************************************
 * Routine:  psgenHeader
 *
 * Purpose:  Generate index of colors and a corresponding postscript header,
 *           using psgenUtl.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
void psgenHeader(void)
{
    int i, blackIndex;
    Color col;

    /* malloc the color space (only once!) */
    if ( !colorBufInit ) {
        colorBufInit = 1;
        colorBufI = (int*)calloc( colorBufMax, sizeof(int) );
        colorBufR = (float*)calloc( colorBufMax, sizeof(float) );
        colorBufG = (float*)calloc( colorBufMax, sizeof(float) );
        colorBufB = (float*)calloc( colorBufMax, sizeof(float) );
    }
    colorBufNum = colorBufMax;
    for (i=0; i<colorBufNum; i++) {
        colorBufI[i] = 0;
        colorBufR[i] = 0.;
        colorBufG[i] = 0.;
        colorBufB[i] = 0.;
    }

    /* ALWAYS pub black on the index list of colors */
    rgb2cindx( &blackIndex, 0., 0., 0. );
    colorBufI[ blackIndex ] = 1;
    colorBufR[ blackIndex ] = 0.;
    colorBufG[ blackIndex ] = 0.;
    colorBufB[ blackIndex ] = 0.;

    /* do the mapping to fill the color mapping arrays */
    for (i=0; i<triaBufferNum; i++) {
        if (triaBuffer[i].nv != 3) {
            fprintf(stderr, "psgenHeader: triaBuffer[%d].nv = <%d>\n",
                i, triaBuffer[i].nv);
        } else {
            col = triaBuffer[i].c;
            rgb2cindx( &(col.i), col.r, col.g, col.b );
            triaBuffer[i].c.i  = col.i;
            colorBufI[ col.i ] = 1;
            colorBufR[ col.i ] = col.r;
            colorBufG[ col.i ] = col.g;
            colorBufB[ col.i ] = col.b;
        }
    }

    psgenUtl(colorBufNum, colorBufR, colorBufG, colorBufB, colorBufI);
}

/*
 * ***************************************************************************
 * Routine:  psgenTrailer
 *
 * Purpose:  Finish the postscript file with a showpage using psgenUtl.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
void psgenTrailer(void)
{
    psgenUtl(-1, colorBufR, colorBufG, colorBufB, colorBufI);
}

/*
 * ***************************************************************************
 * Routine:  psgenPaint
 *
 * Purpose:  Write out each triangle in postscript.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE void psgenPaint(int outline)
{
    int i;
    for (i=0; i<triaBufferNum; i++) {
        VJMPERR1( triaBuffer[i].nv == 3 );
        psgenPaintPoly( triaBuffer+i, outline );
    }

    /* return without error */
    return;

    /* return with error */
  VERROR1:
    fprintf(stderr, "psgenPaint: problem occurred (bailing out).\n");
}

/*
 * ***************************************************************************
 * Routine:  psgenPaintPoly
 *
 * Purpose:  Write out a single triangle in postscript using psgenPath.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
void psgenPaintPoly(Poly *p, int mode)
{
    int i;
    float x[100], y[100];

    /* put the polygon vertices in the arrays */
    for (i=0; i<p->nv; i++) {
        x[i] = (float)PXmap01( p->v[i].x );
        y[i] = (float)PYmap01( p->v[i].y );
    }

    /* loop the first guy in again as the last guy to form a loop */
    i=p->nv;
    x[i] = (float)PXmap01( p->v[0].x );
    y[i] = (float)PYmap01( p->v[0].y );

    /*
     * mode = [ 0 | 1 ] ==> fill
     * mode = [ 1 | 2 ] ==> outline
     * mode = 1         ==> both fill and outline
     */
    if ((mode==0) || (mode==1)) psgenPath(x, y, p->nv,   p->c.i, 1);
    if ((mode==1) || (mode==2)) psgenPath(x, y, p->nv+1, 0,      0);
}

/*
 * ***************************************************************************
 * Routine:  psgenUtl
 *
 * Purpose:  Generate PS file header for ncolors given as RGB floats in [0,1]
 *
 * Author:   Converted from R. Bank's PLTMG by Michael Holst and Randy Bank
 * ***************************************************************************
 */
void psgenUtl(int ncolor,
    float red[], float green[], float blue[], int cidx[])
{
    int i, i0, i1, i2, ii, xmin, ymin, xmax, ymax, uniq;
    float si, width, sca;

    /* pop out a showpage and return */
    if (ncolor <= 0) {
        fprintf(psFilePtr, "showpage\n");
        fclose(psFilePtr);
        psFilePtr = VNULL;
        return;
    }

    /* the PS filename */
    ii = psFileNumber / 10;
    i0 = psFileNumber - ii * 10;
    i1 = ii - ii / 10 * 10;
    strcpy(psFileName, "fig00.ps");
    psFileName[3] = digits[i1];
    psFileName[4] = digits[i0];
    psFileNumber++;

    /* header and macros to reduce PS file size */
    sca = (float)VMAX2(Xmax-Xmin,Ymax-Ymin);
    psFilePtr = fopen(psFileName,"w");
    fprintf(psFilePtr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(psFilePtr, "%%%%Title: <%s>\n", psFileName);
    fprintf(psFilePtr, "%%%%Creator: Oglps"
        " (Rendering of an OpenGL Scene into PostScript)\n");
    fprintf(psFilePtr, "%%%%BoundingBox: %d %d %d %d\n",
        (int)PXmapPS(Xmin-PBox*sca),(int)PYmapPS(Ymin-PBox*sca),
        (int)PXmapPS(Xmax+PBox*sca),(int)PYmapPS(Ymax+PBox*sca));
    fprintf(psFilePtr, "[%d %d %d %d %d %d] concat\n",
        (int)(PSize), 0, 0, (int)(PSize), (int)(PXmin), (int)(PYmin));
    si = 1.f / scale;
    width = .01f / scale;
    fprintf(psFilePtr, "%8.6f %8.6f scale\n", si, si);
    fprintf(psFilePtr, "%10.8f setlinewidth\n", width);
    fprintf(psFilePtr, "2 setlinejoin\n");
    fprintf(psFilePtr, "/s {setrgbcolor newpath moveto} def\n");
    fprintf(psFilePtr, "/r {count 2 idiv {rlineto} repeat} def\n");
    fprintf(psFilePtr, "/f {s r closepath fill} def\n");
    fprintf(psFilePtr, "/g {s r stroke} def\n");

    /* clipping hack: clips scene to a smaller box; fixes an OpenGL bug */
    xmin = (int)(PXmap01(Xmin) * scale);
    xmax = (int)(PXmap01(Xmax) * scale);
    ymin = (int)(PYmap01(Ymin) * scale);
    ymax = (int)(PYmap01(Ymax) * scale);
    fprintf(psFilePtr, "newpath\n");
    fprintf(psFilePtr, "%d %d moveto ",  xmin+clipdist, ymin+clipdist);
    fprintf(psFilePtr, "%d %d lineto ",  xmax-clipdist, ymin+clipdist);
    fprintf(psFilePtr, "%d %d lineto ",  xmax-clipdist, ymax-clipdist);
    fprintf(psFilePtr, "%d %d lineto\n", xmin+clipdist, ymax-clipdist);
    fprintf(psFilePtr, "closepath clip\n");

    /* color definitions */
    uniq = 0;
    for (i=0; i<ncolor; i++) {
        if (cidx[i] == 1) {
            uniq++;
            i2 = i / (base*base);
            i1 = (i-i2*base*base) / base;
            i0 = i - i1*base - i2*base*base;
            fprintf(psFilePtr, "/b%c%c%c {%4.2f %4.2f %4.2f g} def\n",
                digits[i2],digits[i1],digits[i0],red[i],green[i],blue[i]);
            fprintf(psFilePtr, "/c%c%c%c {%4.2f %4.2f %4.2f f} def\n",
                digits[i2],digits[i1],digits[i0],red[i],green[i],blue[i]);
        }
    }
    fprintf(stderr, "psgenUtl: found <%d> unique colors.\n", uniq);
}

/*
 * ***************************************************************************
 * Routine:  psgenPath
 *
 * Purpose:  Render a single polygon into one line of the PS file.
 *
 * Author:   Converted from R. Bank's PLTMG by Michael Holst and Randy Bank
 * ***************************************************************************
 */
void psgenPath(float x[], float y[], int n, int icolor, int itype)
{
    int lenx, leny, i, k, i0, i1, i2, ix, iy, length, npts;
    char buf[100];

    /* print a path in compact int form; look for first nontrivial entry */
    length = 0;
    npts = 0;
    for (i=n-1; i>0; i--) {
        ix = roundX( (x[i]-x[i-1]) * scale );
        iy = roundX( (y[i]-y[i-1]) * scale );
        if ( (ix != 0) || (iy != 0) ) {
            sintc(buf+length, &lenx, ix);
            length += (lenx+1);
            buf[length-1] = ' ';
            sintc(buf+length, &leny, iy);
            length += (leny+1);
            npts = npts+1;
            buf[length-1] = ' ';

            /* purge the buffer when we exceed bufferlength */
            if (length > 60) {
                for (k=0; k<length; k++)
                    fprintf(psFilePtr,"%c",buf[k]);
                fprintf(psFilePtr,"\n");
                length = 0;
            }
        }
    }
    if (npts == 0) return;

    /* the last entry */
    ix = roundX( x[0] * scale );
    iy = roundX( y[0] * scale );
    sintc(buf+length, &lenx, ix);
    length += (lenx+1);
    buf[length-1] = ' ';
    sintc(buf+length, &leny, iy);
    length += (leny+1);
    buf[length-1] = ' ';

    /* set color, and line/fill */
    if (itype == 1) {
        buf[length] = 'c';
    } else {
        buf[length] = 'b';
    }
    i2 = icolor / (base*base);
    i1 = (icolor-i2*base*base) / base;
    i0 = icolor - i1*base - i2*base*base;
    buf[length+1] = digits[i2];
    buf[length+2] = digits[i1];
    buf[length+3] = digits[i0];
    length += 4;

    /* finally, purge the buffer */
    for (k=0; k<length; k++)
        fprintf(psFilePtr,"%c",buf[k]);
    fprintf(psFilePtr,"\n");
}

/*
 * ***************************************************************************
 * Routine:  Polys_testCut
 *
 * Purpose:  Find an orthogonal plane along which a bisection will split
 *           a set of polygons nearly in half.
 *
 * Author:   Michael Holst and Randy Bank
 * ***************************************************************************
 */
VPRIVATE int Polys_testCut(Poly tri[], int ntri,
    int xo[], int yo[], int zo[], int nord,
    int *lsize, int *rsize)
{
    int i, nhf, xlsize, xrsize, ylsize, yrsize, zlsize, zrsize;
    int xsize, ysize, zsize;
    double xcut, ycut, zcut;
    Poly *xp, *yp, *zp;

    nhf = (int)(nord/2);
    xcut = tri[ xo[nhf] ].xmax;
    ycut = tri[ yo[nhf] ].ymax;
    zcut = tri[ zo[nhf] ].zmax;

    xlsize = 0;
    ylsize = 0;
    zlsize = 0;
    xrsize = 0;
    yrsize = 0;
    zrsize = 0;
    for (i=0; i<nord; i++) {
        xp = tri+xo[i];
        yp = tri+yo[i];
        zp = tri+zo[i];

        if (xp->xmax < xcut) {
            xlsize++;
        } else if (xp->xmin > xcut) {
            xrsize++;
        } else {
            xlsize++;
            xrsize++;
        }
        if (yp->ymax < ycut) {
            ylsize++;
        } else if (yp->ymin > ycut) {
            yrsize++;
        } else {
            ylsize++;
            yrsize++;
        }
        if (zp->zmax < zcut) {
            zlsize++;
        } else if (zp->zmin > zcut) {
            zrsize++;
        } else {
            zlsize++;
            zrsize++;
        }
    }
    xsize = VMAX2( VABS(xlsize-nhf), VABS(xrsize-nhf) );
    ysize = VMAX2( VABS(ylsize-nhf), VABS(yrsize-nhf) );
    zsize = VMAX2( VABS(zlsize-nhf), VABS(zrsize-nhf) );

    if ( xsize < VMIN2(ysize,zsize) ) {
        *lsize = xlsize;
        *rsize = xrsize;
        return 0;
    } else if ( ysize < VMIN2(xsize,zsize) ) {
        *lsize = ylsize;
        *rsize = yrsize;
        return 1;
    } else {
        *lsize = zlsize;
        *rsize = zrsize;
        return 2;
    }
}

/*
 * ***************************************************************************
 * Routine:  Polys_makeCut
 *
 * Purpose:  Make the orthogonal plane cuts.
 *
 * Author:   Michael Holst and Randy Bank
 * ***************************************************************************
 */
VPRIVATE void Polys_makeCut(Poly tri[], int ntri,
    int xo[], int yo[], int zo[], int nord,
    int whichCut, int nleft, int nright,
    int xleft[], int xright[],
    int yleft[], int yright[],
    int zleft[], int zright[])
{
    int i, nhf, xlsize, xrsize, ylsize, yrsize, zlsize, zrsize;
    double cut, xpmax, xpmin, ypmax, ypmin, zpmax, zpmin;
    Poly *xp, *yp, *zp;

    nhf = (int)(nord/2);
    if (whichCut == 0) {
        cut = tri[ xo[nhf] ].xmax;
    } else if (whichCut == 1) {
        cut = tri[ yo[nhf] ].ymax;
    } else if (whichCut == 2) {
        cut = tri[ zo[nhf] ].zmax;
    } else {
        cut = 0.0;
        VASSERT(0);
    }

    xlsize = 0;
    ylsize = 0;
    zlsize = 0;
    xrsize = 0;
    yrsize = 0;
    zrsize = 0;
    for (i=0; i<nord; i++) {
        xp = tri+xo[i];
        yp = tri+yo[i];
        zp = tri+zo[i];
        if ( whichCut == 0 ) {
            xpmax = xp->xmax;
            xpmin = xp->xmin;
            ypmax = yp->xmax;
            ypmin = yp->xmin;
            zpmax = zp->xmax;
            zpmin = zp->xmin;
        } else if ( whichCut == 1 ) {
            xpmax = xp->ymax;
            xpmin = xp->ymin;
            ypmax = yp->ymax;
            ypmin = yp->ymin;
            zpmax = zp->ymax;
            zpmin = zp->ymin;
        } else {
            xpmax = xp->zmax;
            xpmin = xp->zmin;
            ypmax = yp->zmax;
            ypmin = yp->zmin;
            zpmax = zp->zmax;
            zpmin = zp->zmin;
        }

        if (xpmax < cut) {
            xleft[xlsize] = xo[i];
            xlsize++;
        } else if (xpmin > cut) {
            xright[xrsize] = xo[i];
            xrsize++;
        } else {
            xleft[xlsize] = xo[i];
            xright[xrsize] = xo[i];
            xlsize++;
            xrsize++;
        }

        if (ypmax < cut) {
            yleft[ylsize] = yo[i];
            ylsize++;
        } else if (ypmin > cut) {
            yright[yrsize] = yo[i];
            yrsize++;
        } else {
            yleft[ylsize] = yo[i];
            yright[yrsize] = yo[i];
            ylsize++;
            yrsize++;
        }
        if (zpmax < cut) {
            zleft[zlsize] = zo[i];
            zlsize++;
        } else if (zpmin > cut) {
            zright[zrsize] = zo[i];
            zrsize++;
        } else {
            zleft[zlsize] = zo[i];
            zright[zrsize] = zo[i];
            zlsize++;
            zrsize++;
        }
    }

    VASSERT( (xlsize == nleft) && (xrsize == nright) );
}

