/* -*- C -*- */
// Copyright (C) 2010 Johan Hake
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2010-10-01
// Last changed: 2010-10-15
//
// ===========================================================================
// Main SWIG directive file for MC 
// ===========================================================================

%module (package="mc") cmc

// Code included verbatim into the header section of the generated wrapper code
%{
#include <mc/mc.h>
#define PY_ARRAY_UNIQUE_SYMBOL PyDOLFIN
#include <numpy/arrayobject.h>
%}


// Code included verbatim into the generated wrapper where the Python module
//  gets initialized
%init%{
import_array();
%}

// Include general SWIG directives
%include <exception.i>

// Generate docstrings
%feature("autodoc", "0");

// Include mc typemaps
%include "mc_typemaps.i"

// Apply SWIG directives before reading the header files
%include "pre.i"

// Include the interface of MC
%include "mc/mc_base.h"
%include "maloc.i"
%include "am_stripped.i"
%include "vio_stripped.i"
%include "gem_stripped.i"
%include "aprx_stripped.i"
%include "pde_stripped.i"

// Apply SWIG directives after reading the header files
%include "post.i"

