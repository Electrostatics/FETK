/* -*- C -*- */
// Copyright (C) 2010 Johan Hake
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2010-10-01
// Last changed: 2010-10-01
//
// ===========================================================================
// SWIG directives for MC 
//
// The directives in this file are applied _after_ the header files has been 
// loaded.
// ===========================================================================

// Code that will both be verbitim inserted in the header section in the 
// generated wrapper code, but also parsed by SWIG to generate wrapper code
//%inline%{
//    
//static FLTVECT* _Vertex_getitem(SurfaceMesh* surfmesh, unsigned int i){
//  return surfmesh->vertex + i;
//}
//
//static INT3VECT* _Face_getitem(SurfaceMesh* surfmesh, unsigned int i){
//  return surfmesh->face + i;
//}
//%}
//
//// Extend both the C and Python interface of SurfaceMesh 
//%extend SurfaceMesh {
//  
//  // Create an empty mesh 
//  SurfaceMesh(unsigned int num_vertices, unsigned int num_faces)
//  {
//    return SurfaceMesh_ctor(num_vertices, num_faces);
//  }
//
//  // Create a spherical surface mesh
//  SurfaceMesh(unsigned int level)
//  {
//    return SurfaceMesh_sphere(level);
//  }
//
//  // Constructor for pdb or off files
//  SurfaceMesh(char* filename)
//  {
//    char* basename_end_pointer;
//
//    // Check if input is a .off file
//    basename_end_pointer = strstr(filename, ".off");
//    if (basename_end_pointer != NULL){
//      return SurfaceMesh_readOFF(filename);
//    }
//  
//    // Check if input is a .pdb file
//    basename_end_pointer = strstr(filename, ".pdb");
//    if (basename_end_pointer != NULL){
//      return SurfaceMesh_readPDB(filename);
//    }
//  
//    // If neither is correct file format
//    printf("Provide a file in either \'.off\' or \'.pdb\' format.\n");
//    exit(1); 
//    return 0;
//  }
//
//  // Constructor for LatticeData
//  SurfaceMesh(char* segmentation_filename, float isovalue, bool padd)
//  {
//    return SurfaceMesh_readLattice(segmentation_filename, isovalue, padd);
//  }  
//
//  // Constructor for LatticeData together with intensity values
//  SurfaceMesh(char* segmentation_filename, char* intensity_filename, 
//	      float isovalue, bool padd)
//  {
//    return SurfaceMesh_readLattice(segmentation_filename, 
//				   intensity_filename, isovalue, padd);
//  }  
//
//  // Constructor that merges two surface meshes
//  SurfaceMesh(SurfaceMesh* in0, SurfaceMesh* in1)
//  {
//    return SurfaceMesh_merge(in0, in1);
//  }
//
//  // Destructor
//  ~SurfaceMesh()
//  {
//    SurfaceMesh_dtor($self);
//  }
//  
//  // Python interface
//  %pythoncode %{
//
//    def vertex(self, i):
//        "Return the ith vertex"
//        if not isinstance(i, int):
//            raise TypeError, "expected an int for the index value"
//        if i >= self.nv:
//            raise IndexError, "index out of range"
//        return _Vertex_getitem(self, i)
//
//    def face(self, i):
//        "Return the ith vertex"
//        if not isinstance(i, int):
//            raise TypeError, "expected an int for the index value"
//        if i >= self.nf:
//            raise IndexError, "index out of range"
//        return _Face_getitem(self, i)
//
//    def refine(self):
//        "Refine a surface mesh uniformly"
//        SurfaceMesh_refine(self)
//
//    def smooth(self, max_min_angle = 15, min_max_angle = 150,
//               max_iter = 6, flip_edges = True):
//        "Smooth the mesh"
//        return SurfaceMesh_smooth(self, max_min_angle, min_max_angle, 
//				  max_iter, flip_edges)
//
//    def normalSmooth(self):
//        "Smooth the facet normals of the mesh"
//        SurfaceMesh_normalSmooth(self)
//
//    def correctNormals(self):
//        "Correct any normals that might be screwed"
//        SurfaceMesh_correctNormals(self)
//
//    def writeOFF(self, filename):
//        "Write the mesh to file"
//        SurfaceMesh_writeOFF(self, filename)
//  
//    def coarse_flat(self, rate=0.016):
//        "Coarse flat areas"
//        SurfaceMesh_coarse(self, rate, 1, 0, -1)
//        
//    def coarse_dense(self, rate=1.6):
//        "Coarse flat areas"
//        SurfaceMesh_coarse(self, rate, 0, 10, -1)
//
//    def getCenterRadius(self):
//        "Return an ATOM structor of the radius and center of a surface mesh"
//        return SurfaceMesh_getCenterRadius(self)
//    
//  %}
//
////    def getMinMaxAngles(self, max_min_angle=15, min_max_angle=150):
////        """Return angle statistics"""
////        return SurfaceMesh_getMinMaxAngles(max_min_angle, min_max_angle)
//
//
//
//}
