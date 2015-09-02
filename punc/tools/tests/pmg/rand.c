/* ///////////////////////////////////////////////////////////////////////////
// @file    rand.c
// @author  Michael Holst
// @brief   Random number generation.
// @version $Id: rand.c,v 1.2 2010/08/12 05:53:10 fetk Exp $
// @attention
// @verbatim
//
// PMG -- Parallel algebraic MultiGrid
// Copyright (C) 1994-- Michael Holst.
//
// Michael Holst <mholst@math.ucsd.edu>
// University of California, San Diego
// Department of Mathematics, 5739 AP&M
// 9500 Gilman Drive, Dept. 0112
// La Jolla, CA 92093-0112 USA                                                  
// http://math.ucsd.edu/~mholst
//
// This file is part of PMG.
//
// PMG is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// PMG is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PMG; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
//
// Linking PMG statically or dynamically with other modules is making a
// combined work based on PMG. Thus, the terms and conditions of the GNU
// General Public License cover the whole combination.
// 
// SPECIAL GPL EXCEPTION
// In addition, as a special exception, the copyright holders of PMG
// give you permission to combine the PMG program with free software
// programs and libraries that are released under the GNU LGPL or with
// code included in releases of ISIM, PMV, PyMOL, SMOL, VMD, and Vision.
// Such combined software may be linked with PMG and redistributed together 
// in original or modified form as mere aggregation without requirement that 
// the entire work be under the scope of the GNU General Public License.
// This special exception permission is also extended to any software listed
// in the SPECIAL GPL EXCEPTION clauses by the FEtk and APBS libraries.
// 
// Note that people who make modified versions of PMG are not obligated
// to grant this special exception for their modified versions; it is
// their choice whether to do so. The GNU General Public License gives
// permission to release a modified version without this exception; this
// exception also makes it possible to release a modified version which
// carries forward this exception.
//
// @endverbatim
// //////////////////////////////////////////////////////////////////////// */

/* ******************************************************************* */
/* purpose:                                                            */
/*                                                                     */
/*    Interface to a random number generator.                          */
/*                                                                     */
/* Machine:                                                            */
/*                                                                     */
/*    most UNIX machines                                               */
/*                                                                     */
/* author:  michael holst                                              */
/* ******************************************************************* */
#include <stdio.h>
#include <math.h>

#if 0
float rand_(key)
    int key;
{
    /* return (rand(key)); */
    return 0.0;
}
#endif

