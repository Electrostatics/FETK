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
 * rcsid="$Id: vel.c,v 1.10 2010/08/12 05:18:58 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     vel.c
 *
 * Purpose:  Class Vel: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "vel_p.h"

VEMBED(rcsid="$Id: vel.c,v 1.10 2010/08/12 05:18:58 fetk Exp $")

/*
 * ***************************************************************************
 * Class Vel: Global objects
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Mapping:  vmapE
 *
 * Purpose:  The edge permutation map "vmapE"; this mapping takes pairs of
 *           vertices into single edge numbers.
 *
 *     Mapping Function     Edge (vtx pair)  Edge (number)
 *     ------------------   --------------   -----------
 *     i+j+(i/3)+(j/3)-1:   (0,1) or (1,0)   0 \           \
 *                          (0,2) or (2,0)   1 |-- 2D Case |
 *                          (1,2) or (2,1)   2 /           |--- 3D Case
 *                          (0,3) or (3,0)   3             |
 *                          (1,3) or (3,1)   4             |
 *                          (2,3) or (3,2)   5             /
 *
 * Notes:    Works for BOTH 2D and 3D cases, in that the 2D case is just
 *           the first 3x3 block:
 *
 *                 vmapE_2D[3][3] = { { -1,  0,  1  },
 *                                    {  0, -1,  2  },
 *                                    {  1,  2, -1  } };
 *
 *           Example (2D):   edge_connecting_vertices_0_and_1 = vmapE[0][1];
 *
 *           Example (3D):   edge_connecting_vertices_2_and_3 = vmapE[2][3];
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
#if 0
VPUBLIC const int vmapE[4][4] = {
    { -1,  0,  1,  3  },
    {  0, -1,  2,  4  },
    {  1,  2, -1,  5  },
    {  3,  4,  5, -1  }
};
#else
VPUBLIC const int vmapE[4][4] = {
    { -1,  2,  1,  3  },
    {  2, -1,  0,  4  },
    {  1,  0, -1,  5  },
    {  3,  4,  5, -1  }
};
#endif

/*
 * ***************************************************************************
 * Mapping:  vmapEI
 *
 * Purpose:  The inverse edge permutation map "vmapEI"; this mapping takes a
 *           single edge number into the appropriate pair of vertices.
 *
 *     Mapping Function     Edge (vtx pair)  Edge (number)
 *     ------------------   --------------   -----------
 *     i+j+(i/3)+(j/3)-1:   (0,1) or (1,0)   0 \           \
 *                          (0,2) or (2,0)   1 |-- 2D Case |
 *                          (1,2) or (2,1)   2 /           |--- 3D Case
 *                          (0,3) or (3,0)   3             |
 *                          (1,3) or (3,1)   4             |
 *                          (2,3) or (3,2)   5             /
 *
 * Notes:    Works for BOTH 2D and 3D cases, in that the 2D case is just
 *           the first 3x2 block:
 *
 *                 vmapEI_2D[6][2] = { {  0,  1  },
 *                                     {  0,  2  },
 *                                     {  1,  2  } };
 *
 *           Example (2D):   edge0_vertex1 = vmapEI[0][1];
 *
 *           Example (3D):   edge5_vertex0 = vmapEI[5][0];
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
#if 0
VPUBLIC const int vmapEI[6][2] = {
    {  0,  1  },
    {  0,  2  },
    {  1,  2  },
    {  0,  3  },
    {  1,  3  },
    {  2,  3  }
};
#else
VPUBLIC const int vmapEI[6][2] = {
    {  1,  2  },
    {  0,  2  },
    {  0,  1  },
    {  0,  3  },
    {  1,  3  },
    {  2,  3  }
};
#endif

/*
 * ***************************************************************************
 * Mapping:  vmapV
 *
 * Purpose:  The vertex permutation map "vmapV"; this mapping allows us to
 *           map any of the three/six refinement scenarios onto the canonical
 *           one.  Each row represents the appropriate vertex number mappings
 *           for each of the three/six cases.
 *
 *           One uses this as follows:  If for example edge 2-0 (or 0-2) must
 *           be refined.  According to the above, vmapE[0][2]=vmapE[2][0]=1,
 *           so this is edge number 1.  We take this edge number 1 and look
 *           in row 1 of vmapV, which gives a permutation of vertices so that
 *           the 2-0 edge appears to as the first edge, i.e. the 0-1 edge in
 *           a canonical 0-1-2 or 0-1-2-3 vertex ordering.  Therefore, we can
 *           write a single bisection (etc) routine that only deals only with
 *           bisecting the 0-1 edge; the vmapE and vmapV remappings then
 *           takes us to the correct vertex numbers for an arbitrary edge.
 *
 * Notes:    Works for BOTH 2D and 3D cases, in that the 2D case is just
 *           the first 3x3 block:
 *
 *                 vmapV_2D[3][3] = { {  0,  1,  2  },
 *                                    {  2,  0,  1  },
 *                                    {  1,  2,  0  } };
 *
 *           Example (2D):   case2_vertex0 = vmapV[2][0];
 *                           case2_vertex1 = vmapV[2][1];
 *                           case2_vertex2 = vmapV[2][1];
 *
 *           Example (3D):   case0_vertex0 = vmapV[0][0];
 *                           case0_vertex1 = vmapV[0][1];
 *                           case0_vertex2 = vmapV[0][2];
 *                           case0_vertex3 = vmapV[0][3];
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
#if 0
VPUBLIC const int vmapV[6][4] = {
    {  0,  1,  2,  3  },
    {  2,  0,  1,  3  },
    {  1,  2,  0,  3  },
    {  0,  3,  1,  2  },
    {  3,  1,  0,  2  },
    {  2,  3,  0,  1  }
};
#else
VPUBLIC const int vmapV[6][4] = {
    {  1,  2,  0,  3  },
    {  2,  0,  1,  3  },
    {  0,  1,  2,  3  },
    {  0,  3,  1,  2  },
    {  3,  1,  0,  2  },
    {  2,  3,  0,  1  }
};
#endif

/*
 * ***************************************************************************
 * Mapping:  vmapF
 *
 * Purpose:  The face permutation map "vmapF"; the vertex numbers of the
 *           three/four simplex edges/faces in 2D or 3D.  Each row represents
 *           the appropriate vertex number mappings for each of the three/four
 *           cases.  The orderings of the edges/faces are taken to be opposite
 *           the vertices; i.e., edge/face k is opposite vertex k, and so on.
 *           The orderings of the vertices with each face are taken to produce
 *           a counter-clockwise line integral in the 2D case, and outward
 *           unit normals determined by a right-hand-rule in the 3D case.
 *
 * Notes:    Works for BOTH 2D and 3D cases, in that the 2D case is just
 *           the first 2x3 block:
 *
 *                 vmapF_2D[3][2] = { {  1,  2  },
 *                                    {  2,  0  },
 *                                    {  0,  1  } };
 *
 *           Example (2D):   face1_vertex0 = vmapF[1][0];
 *                           face1_vertex1 = vmapF[1][1];
 *
 *           Example (3D):   face3_vertex0 = vmapF[3][0];
 *                           face3_vertex1 = vmapF[3][1];
 *                           face3_vertex2 = vmapF[3][2];
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC const int vmapF[4][3] = {
    {  1,  2,  3  },
    {  2,  0,  3  },
    {  0,  1,  3  },  
    {  0,  2,  1  }
};

/*
 * ***************************************************************************
 * Mapping:  vmapFE
 *
 * Purpose:  Maps face number into numbers of edges which belong to the face.
 *           Ordering of faces is taken to be opposite to the vertices. I.e.
 *           face opposite to vertex 1 has number 1. In 2D, the first 3x1
 *           block represents simply numbers of edges (as it should be). In 3D, 
 *           ordering of edges on the face is taken to be counterclockwise if 
 *           looking on the face from inside the tetrahedron.
 *
 * Notes:    Works for BOTH 2D and 3D cases, in that the 2D case is just
 *           the first 3x1 block:
 *
 *                vmapFE_2D[3][1] = { {  0  },
 *                                    {  1  },
 *                                    {  2  } };
 *
 *           Example (2D):   face1_edge0 = vmapF[1][0];
 *                           face0_edge0 = vmapF[0][0];
 *
 *           Example (3D):   face3_edge0 = vmapF[3][0];
 *                           face3_edge1 = vmapF[3][1];
 *                           face3_edge2 = vmapF[3][2];
 *
 * Author:   Michael Holst, Oleg Korobkin
 * ***************************************************************************
 */
VPUBLIC const int vmapFE[4][3] = {
    {  0,  4,  5  },
    {  1,  5,  3  },
    {  2,  3,  4  },  
    {  0,  1,  2  }
};

/*
 * ***************************************************************************
 * Mapping:  vmapOV1
 *
 * Purpose:  The "other vertex" map vmapOV1; this gives the third/fourth
 *           distinct vertex number, given the other two/three distinct
 *           vertex numbers.
 *
 *     2D Mapping Function  Vertex pair      Third vertex
 *     ------------------   -----------      ------------
 *                          (0,1)            2
 *                          (0,2)            1
 *                          (1,2)            0
 *
 *     3D Mapping Function  Vertex trio      Fourth vertex
 *     ------------------   -----------      -------------
 *                          (0,1,3)          2
 *                          (0,2,3)          1
 *                          (1,2,3)          0
 *                          (0,1,2)          3
 *
 * Notes:    Works for BOTH 2D and 3D cases, in that the 2D case is just
 *           the first 3x3 block of the fourth matrix:
 *
 *                 vmapOV1_2D[3][3] = { { -1,  2,  1  },
 *                                      {  2, -1,  0  },
 *                                      {  1,  0, -1  } };
 * 
 *           Example (2D):   vertex_other_than_01  = vmapOV1[3][0][1];
 *
 *           Example (3D):   vertex_other_than_012 = vmapOV1[0][1][2];
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC const int vmapOV1[4][4][4] = {

    { { -1, -1, -1, -1  },
      { -1, -1,  3,  2  },
      { -1,  3, -1,  1  },
      { -1,  2,  1, -1  } },

    { { -1, -1,  3,  2  },
      { -1, -1, -1, -1  },
      {  3, -1, -1,  0  },
      {  2, -1,  0, -1  } },

    { { -1,  3, -1,  1  },
      {  3, -1, -1,  0  },
      { -1, -1, -1, -1  },
      {  1,  0, -1, -1  } },

    { { -1,  2,  1, -1  },
      {  2, -1,  0, -1  },
      {  1,  0, -1, -1  },
      { -1, -1, -1, -1  } }

};

/*
 * ***************************************************************************
 * Mapping:  vmapOV2
 *
 * Purpose:  The "other vertex" map vmapOV2; this gives the other vertex (2D)
 *           or the two other vertices (3D), given the other two distinct
 *           vertex numbers.
 *
 *     2D Mapping Function  Vertex pair      Third vertex
 *     ------------------   -----------      ------------
 *                          (0,1)            2
 *                          (0,2)            1
 *                          (1,2)            0
 *
 *     3D Mapping Function  Vertex pair      Other vertex pair
 *     ------------------   -----------      -----------------
 *                          (0,1)            (2,3)
 *                          (0,2)            (1,3)
 *                          (0,3)            (1,2)
 *                          (1,2)            (0,3)
 *                          (1,3)            (0,2)
 *                          (2,3)            (0,1)
 *
 * Notes:    Works for BOTH 2D and 3D cases, in that the 2D case is just
 *           the first 3x3 block of the first matrix:
 *
 *                 vmapOV2_2D[3][3] = { { -1,  2,  1  },
 *                                      {  2, -1,  0  },
 *                                      {  1,  0, -1  } };
 * 
 *           Example (2D):   vertex_other_than_12  = vmapOV2[0][1][2];
 *
 *           Example (3D):   vertexA_other_than_12 = vmapOV2[0][1][2];
 *                           vertexB_other_than_12 = vmapOV2[1][1][2];
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC const int vmapOV2[2][4][4] = {

    { { -1,  2,  1,  1  },
      {  2, -1,  0,  0  },
      {  1,  0, -1,  0  },
      {  1,  0,  0, -1  } },

    { { -1,  3,  3,  2  },
      {  3, -1,  3,  2  },
      {  3,  3, -1,  1  },
      {  2,  2,  1, -1  } }

};

/*
 * ***************************************************************************
 * Mapping:  vmapOV3
 *
 * Purpose:  The "other vertex" map vmapOV3; this gives the other two/three
 *           vertices given the other distinct vertex number.
 *
 *     2D Mapping Function  Vertex single    Other Vertex pair 
 *     ------------------   -------------    -----------------
 *                          0                (1,2)
 *                          1                (0,2)
 *                          2                (0,1)
 *
 *     3D Mapping Function  Vertex single    Other vertex trio
 *     ------------------   -------------    -----------------
 *                          0                (1,2,3)
 *                          1                (0,2,3)
 *                          2                (0,1,3)
 *                          3                (0,1,2)
 *
 * Notes:    Works for BOTH 2D and 3D cases, in that the 2D case is just
 *           the first 3x2 block:
 *
 *                 vmapOV3_2D[3][3] = { {  1,  2  },
 *                                      {  0,  2  },
 *                                      {  0,  1  } };
 * 
 *           Example (2D):   vertexA_other_than_2 = vmapOV3[2][0];
 *                           vertexB_other_than_2 = vmapOV3[2][1];
 *
 *           Example (3D):   vertexA_other_than_3 = vmapOV3[3][0];
 *                           vertexB_other_than_3 = vmapOV3[3][1];
 *                           vertexC_other_than_3 = vmapOV3[3][2];
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC const int vmapOV3[4][3] = {
    {  1,  2,  3  },
    {  0,  2,  3  },
    {  0,  1,  3  },
    {  0,  1,  2  }
};

/*
 * ***************************************************************************
 * Mapping:  vmapOE
 *
 * Purpose:  Maps single vertex to the "other edge" in 2D or 3 edges of the
 *           opposite face in 3D.
 *
 *     2D Mapping Function  Vertex single    Other edge 
 *     ------------------   -------------    -----------------
 *                          0                0
 *                          1                1
 *                          2                2
 *
 *     3D Mapping Function  Vertex single    Other edge trio
 *     ------------------   -------------    -----------------
 *                          0                (0,4,5)
 *                          1                (1,5,3)
 *                          2                (2,3,4)
 *                          3                (0,1,2)
 *
 * Notes:    Works for BOTH 2D and 3D cases, in that the 2D case is just
 *           the first 3x1 block:
 *
 *                 vmapOE_2D[3][1] = { {  0  },
 *                                     {  1  },
 *                                     {  2  } };
 * 
 *           Example (2D):   edge_other_than_2 = vmapOE[2][0];
 *
 *           Example (3D):   edgeA_other_than_3 = vmapOE[3][0];
 *                           edgeB_other_than_3 = vmapOE[3][1];
 *                           edgeC_other_than_3 = vmapOE[3][2];
 *
 * Author:   Michael Holst, Oleg Korobkin
 * ***************************************************************************
 */
VPUBLIC const int vmapOE[4][3] = {
    {  0,  4,  5  },
    {  1,  5,  3  },
    {  2,  3,  4  },
    {  0,  1,  2  }
};
/*
 * ***************************************************************************
 * Class Vel: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_GEM)

/*
 * ***************************************************************************
 * Routine:  Vel_init
 *
 * Purpose:  Initialize the element.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vel_init(Vel *thee, int tdim, int tid)
{
    thee->g.bits = MASK_00000000000000000000000000000000;
    thee->g.uid  = MASK_00000000000000000000000000000000;
    Vel_setDim(thee, tdim);
    Vel_setId(thee, tid);
}

/*
 * ***************************************************************************
 * Routine:  Vel_reinit
 *
 * Purpose:  Re-initialize the element.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vel_reinit(Vel *thee)
{
    /* keep the dimension and id information */
    thee->g.bits &= MASK_11111111111111111100000000111111;
    thee->g.uid  &= MASK_11111111111111111111111111111111;
}

/*
 * ***************************************************************************
 * Routine:  Vel_setReality
 *
 * Purpose:  Set the reality bits.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vel_setReality(Vel *thee, int reel)
{
    thee->g.bits &= MASK_11111111111111111111111111111100;
    thee->g.bits |= reel;
}

/*
 * ***************************************************************************
 * Routine:  Vel_setDim
 *
 * Purpose:  Set the dimension bits.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vel_setDim(Vel *thee, int dim)
{
    VASSERT( (dim==2) || (dim==3) );
    thee->g.bits &= MASK_11111111111111111111111111110011;
    thee->g.bits |= (dim << 2);
}

/*
 * ***************************************************************************
 * Routine:  Vel_setClass
 *
 * Purpose:  Set the class bits.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vel_setClass(Vel *thee, int clas)
{
    thee->g.bits &= MASK_11111111111111111111111111001111;
    thee->g.bits |= (clas << 4);
}

/*
 * ***************************************************************************
 * Routine:  Vel_setType
 *
 * Purpose:  Set the type bits.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vel_setType(Vel *thee, int type)
{
    thee->g.bits &= MASK_11111111111111111100000000111111;
    thee->g.bits |= (type << 6);
}

/*
 * ***************************************************************************
 * Routine:  Vel_setChart
 *
 * Purpose:  Set the chart bits.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vel_setChart(Vel *thee, int chart)
{
    thee->g.bits &= MASK_00000000000000000011111111111111;
    thee->g.bits |= ((chart) << 14);
}

/*
 * ***************************************************************************
 * Routine:  Vel_setId
 *
 * Purpose:  Set the ID bits.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vel_setId(Vel *thee, int vid)
{
    thee->g.uid = vid;
}

/*
 * ***************************************************************************
 * Routine:  Vel_reality
 *
 * Purpose:  Return the reality.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int Vel_reality(Vel *thee)
{
    return (thee->g.bits & MASK_00000000000000000000000000000011);
}

/*
 * ***************************************************************************
 * Routine:  Vel_dim
 *
 * Purpose:  Return the dimension.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int Vel_dim(Vel *thee)
{
    return ((thee->g.bits & MASK_00000000000000000000000000001100) >> 2);
}

/*
 * ***************************************************************************
 * Routine:  Vel_dimVV
 *
 * Purpose:  Return the number of vertices in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int Vel_dimVV(Vel *thee)
{
    return (Vel_dim(thee)+1);
}

/*
 * ***************************************************************************
 * Routine:  Vel_dimEE
 *
 * Purpose:  Return the number of edges in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int Vel_dimEE(Vel *thee)
{
    return (3*(Vel_dim(thee)-1));
}

/*
 * ***************************************************************************
 * Routine:  Vel_dimFF
 *
 * Purpose:  Return the number of faces in a simplex.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int Vel_dimFF(Vel *thee)
{
    return (Vel_dim(thee)+1);
}

/*
 * ***************************************************************************
 * Routine:  Vel_class
 *
 * Purpose:  Return the class.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int Vel_class(Vel *thee)
{
    return ((thee->g.bits & MASK_00000000000000000000000000110000) >> 4);
}

/*
 * ***************************************************************************
 * Routine:  Vel_type
 *
 * Purpose:  Return the type.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int Vel_type(Vel *thee)
{
    return ((thee->g.bits & MASK_00000000000000000011111111000000) >> 6);
}

/*
 * ***************************************************************************
 * Routine:  Vel_chart
 *
 * Purpose:  Return the chart.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int Vel_chart(Vel *thee)
{
    return ((thee->g.bits & MASK_11111111111111111100000000000000) >> 14);
}

/*
 * ***************************************************************************
 * Routine:  Vel_id
 *
 * Purpose:  Return the ID.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC unsigned int Vel_id(Vel *thee)
{
    return thee->g.uid;
}

#endif /* if !defined(VINLINE_GEM) */
/*
 * ***************************************************************************
 * Class V: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Vel_ctor
 *
 * Purpose:  The Vel constructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC Vel* Vel_ctor(int tdim, int tid)
{
    Vel *thee = VNULL;

    VDEBUGIO("Vel_ctor: CREATING object..");

    thee = Vmem_malloc( VNULL, 1, sizeof(Vel) );

    thee->g.bits = MASK_00000000000000000000000000000000;
    Vel_setDim(thee, tdim);
    Vel_setId(thee, tid);

    VDEBUGIO("..done.\n");

    return thee;
}

/*
 * ***************************************************************************
 * Routine:  Vel_dtor
 *
 * Purpose:  The Vel destructor.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Vel_dtor(Vel **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        VDEBUGIO("Vel_dtor: DESTROYING object..");
        Vmem_free( VNULL, 1, sizeof(Vel), (void**)thee );
        VDEBUGIO("..done.\n");

        (*thee) = VNULL;
    }
}

