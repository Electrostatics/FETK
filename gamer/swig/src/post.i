/* -*- C -*- */
// Copyright (C) 2010 Johan Hake
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2010-08-06
// Last changed: 2010-10-06
//
// ===========================================================================
// SWIG directives for GAMer 
//
// The directives in this file are applied _after_ the header files has been 
// loaded.
// ===========================================================================

// Code that will both be verbitim inserted in the header section in the 
// generated wrapper code, but also parsed by SWIG to generate wrapper code
%inline%{
    
static FLTVECT* _Vertex_getitem(SurfaceMesh* surfmesh, unsigned int i){
  return surfmesh->vertex + i;
}

static INT3VECT* _Face_getitem(SurfaceMesh* surfmesh, unsigned int i){
  return surfmesh->face + i;
}

static void SurfaceMesh_set_vertex_marker(SurfaceMesh* surfmesh, unsigned int i, int value){
  surfmesh->vertex_markers[i] = value;
}

static int SurfaceMesh_get_vertex_marker(SurfaceMesh* surfmesh, unsigned int i){
  return surfmesh->vertex_markers[i];
}

static void SurfaceMesh_set_face_marker(SurfaceMesh* surfmesh, unsigned int i, int value){
  surfmesh->face_markers[i] = value;
}

static int SurfaceMesh_get_face_marker(SurfaceMesh* surfmesh, unsigned int i){
  return surfmesh->face_markers[i];
}

%}

// Extend both the C and Python interface of SurfaceMesh 
%extend SurfaceMesh {
  
  // Create an empty mesh 
  SurfaceMesh(unsigned int num_vertices, unsigned int num_faces)
  {
    return SurfaceMesh_ctor(num_vertices, num_faces);
  }

  // Create a spherical surface mesh
  SurfaceMesh(unsigned int level)
  {
    return SurfaceMesh_sphere(level);
  }

  // Constructor for pdb or off files
  SurfaceMesh(char* filename)
  {
    char* basename_end_pointer;

    // Check if input is a .off file
    basename_end_pointer = strstr(filename, ".off");
    if (basename_end_pointer != NULL){
      return SurfaceMesh_readOFF(filename);
    }
  
    // Check if input is a .pdb file
    basename_end_pointer = strstr(filename, ".pdb");
    if (basename_end_pointer != NULL){
      return SurfaceMesh_readPDB(filename);
    }
  
    // If neither is correct file format
    printf("Provide a file in either \'.off\' or \'.pdb\' format.\n");
    exit(1); 
    return 0;
  }

  // Constructor for LatticeData
  SurfaceMesh(char* segmentation_filename, float isovalue, bool padd)
  {
    return SurfaceMesh_readLattice(segmentation_filename, isovalue, padd);
  }  

  // Constructor for LatticeData together with intensity values
  SurfaceMesh(char* segmentation_filename, char* intensity_filename, 
	      float isovalue, bool padd)
  {
    return SurfaceMesh_readLattice(segmentation_filename, 
				   intensity_filename, isovalue, padd);
  }  

  // Constructor that merges two surface meshes
  SurfaceMesh(SurfaceMesh* in0, SurfaceMesh* in1)
  {
    return SurfaceMesh_merge(in0, in1);
  }

  // Destructor
  ~SurfaceMesh()
  {
    SurfaceMesh_dtor($self);
  }

  // Python interface
  %pythoncode %{

    def vertex(self, i):
        "Return the ith vertex"
        if not isinstance(i, int):
            raise TypeError, "expected an int for the index value"
        if i >= self.nv:
            raise IndexError, "index out of range"
        return _Vertex_getitem(self, i)

    def face(self, i):
        "Return the ith vertex"
        if not isinstance(i, int):
            raise TypeError, "expected an int for the index value"
        if i >= self.nf:
            raise IndexError, "index out of range"
        return _Face_getitem(self, i)

    def refine(self):
        "Refine a surface mesh uniformly"
        SurfaceMesh_refine(self)

    def smooth(self, max_min_angle = 15, min_max_angle = 150,
               max_iter = 6, flip_edges = True):
        "Smooth the mesh"
        return SurfaceMesh_smooth(self, max_min_angle, min_max_angle, 
				  max_iter, flip_edges)

    def normal_smooth(self):
        "Smooth the facet normals of the mesh"
        SurfaceMesh_normalSmooth(self)

    def correct_normals(self):
        "Correct any normals that might be screwed"
        SurfaceMesh_correctNormals(self)

    def write_off(self, filename):
        "Write the mesh to file"
        SurfaceMesh_writeOFF(self, filename)
  
    def coarse_flat(self, rate=0.016):
        "Coarse flat areas"
        SurfaceMesh_coarse(self, rate, 1, 0, -1)
        
    def coarse_dense(self, rate=1.6, numiter=1):
        "Coarse flat areas"
        if not isinstance(rate, (int, float)) or rate <= 0:
            raise TypeError, "expected a positive scalar for the 'rate' argument"
        if not isinstance(numiter, int) or numiter < 1:
            raise TypeError, "expected a positive scalar for the 'numiter' argument"
        for i in xrange(numiter):
            SurfaceMesh_coarse(self, rate, 0, 10, -1)

    def get_center_radius(self):
        "Return an ATOM structor of the radius and center of a surface mesh"
        return SurfaceMesh_getCenterRadius(self)

    def set_vertex_marker(self, i, value):
        "Sets the ith vertex marker"
        if not isinstance(i, int) or i < 0:
            raise TypeError, "expected a non negative integer for the first argument"
        
        if not isinstance(value, int) or value < 0:
            raise TypeError, "expected a non negative integer for the second argument"
        if i >= self.nvm:
            raise IndexError, "index out of range"
        SurfaceMesh_set_vertex_marker(self, i, value)
    
    def get_vertex_marker(self, i):
        "Return the ith vertex marker"
        if not isinstance(i, int) or i < 0:
            raise TypeError, "expected a non negative integer for the first argument"
        
        if i >= self.nvm:
            raise IndexError, "index out of range"
        return SurfaceMesh_get_vertex_marker(self, i, value)
    
    def set_face_marker(self, i, value):
        "Sets the ith face marker"
        if not isinstance(i, int) or i < 0:
            raise TypeError, "expected a non negative integer for the first argument"
        
        if not isinstance(value, int) or value < 0:
            raise TypeError, "expected a non negative integer for the second argument"
        if i >= self.nfm:
            raise IndexError, "index out of range"
        SurfaceMesh_set_face_marker(self, i, value)
    
    def get_face_marker(self, i):
        "Returns the ith face marker"
        if not isinstance(i, int) or i < 0:
            raise TypeError, "expected a non negative integer for the first argument"
        
        if i >= self.nfm:
            raise IndexError, "index out of range"
        return SurfaceMesh_get_face_marker(self, i, value)

    def reset_vertex_markers(self):
        "Resets the vertex markers"
        SurfaceMesh_resetVertexMarkers(self)
    
    def reset_face_markers(self):
        "Resets the face markers"
        SurfaceMesh_resetFaceMarkers(self)
    
  %}

//    def getMinMaxAngles(self, max_min_angle=15, min_max_angle=150):
//        """Return angle statistics"""
//        return SurfaceMesh_getMinMaxAngles(max_min_angle, min_max_angle)

}

// Extend both the C and Python interface of GemMesh
%extend GemMesh {
  
  GemMesh(SurfaceMesh* surfmesh, char* tetgen_quality_params="q1.333")
  {
    char tetgen_params[20];
    char default_params[] = "nnepAAY";
    sprintf(tetgen_params, "%s%s", default_params, tetgen_quality_params);
    return GemMesh_fromSurfaceMesh(surfmesh, tetgen_params);
  }
  
  ~GemMesh()
  {
    GemMesh_dtor($self);
  }

  void write_mcsf(char* filename)
  {
    GemMesh_writeMcsf(self, filename);
  }

  void write_off(char* filename)
  {
    GemMesh_writeOFF(self, filename);
  }

 }
