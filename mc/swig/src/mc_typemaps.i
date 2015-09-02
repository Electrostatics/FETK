/* -*- C -*- */
// Copyright (C) 2010 Johan Hake
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2010-10-01
// Last changed: 2010-10-01
//

//=============================================================================
// General typemaps for MC
//=============================================================================

//-----------------------------------------------------------------------------
// The typecheck (unsigned int)
//-----------------------------------------------------------------------------
%typecheck(SWIG_TYPECHECK_INTEGER) unsigned int
{
  $1 = PyInt_Check($input) ? 1 : 0;
}

//-----------------------------------------------------------------------------
// The typemap (unsigned int)
//-----------------------------------------------------------------------------
%typemap(in) unsigned int
{
  if (PyInt_Check($input))
  {
    long tmp = static_cast<long>(PyInt_AsLong($input));
    if (tmp>=0)
      $1 = static_cast<unsigned int>(tmp);
    else
      SWIG_exception(SWIG_TypeError, "expected positive 'int' for argument $argnum");
  }
  else
    SWIG_exception(SWIG_TypeError, "expected positive 'int' for argument $argnum");
}

//%typemap(in, numinputs=0) SurfaceMesh*& (SurfaceMesh* tmp_mesh)
//{
//  $1 = &tmp_mesh;
//}
//
//%typemap(argout) SurfaceMesh*&
//{
//  $result = SWIG_NewPointerObj(SWIG_as_voidptr(*$1), $descriptor(SurfaceMesh*), 1 );
//}
//
//%typemap(in, numinputs=0) SurfaceMesh** (SurfaceMesh* tmp_mesh)
//{
//  $1 = &tmp_mesh;
//}
//
//%typemap(argout) SurfaceMesh**
//{
//  $result = SWIG_NewPointerObj(SWIG_as_voidptr(*$1), $descriptor(SurfaceMesh*), 1 );
//}
