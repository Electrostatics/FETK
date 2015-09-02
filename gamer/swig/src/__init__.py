""" Python interface of GAMer
"""

__author__ = "Johan Hake (hake.dev@gmail.com)"
__copyright__ = "Copyright (C) 2010 Johan Hake"
__date__ = "2010-08-06 -- 2010-10-06"
__license__  = "GNU LGPL Version 3.1"

# Import the wrapped SWIG wrapped version of gamer
import cgamer

# Expose the C interface of gamer
SurfaceMesh = cgamer.SurfaceMesh
GemMesh = cgamer.GemMesh
