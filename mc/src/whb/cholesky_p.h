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
 * rcsid="$Id: cholesky_p.h,v 1.5 2010/08/12 05:19:21 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     cholesky_p.h
 *
 * Purpose:  PRIVATE header.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#ifndef _WHB_P_H_
#define _WHB_P_H_

#include <mc/whb.h>
#include "mccf.h"

/*
 * ***************************************************************************
 * Class Whb: Non-Inlineable methods (cholesky.c)
 * ***************************************************************************
 */

VPRIVATE void mContribRecycle(Vset *mtpool,
    LinkA **rclnk, int key, int *count, int i, int j, double val);
VPRIVATE void Bmat_choleskyCreate(Bmat *thee);
VPRIVATE int Mat_choleskyFactor(Mat *thee, int flag);
VPRIVATE int Bmat_choleskyFactor(Bmat *thee, int flag);
VPRIVATE double Mat_lnDetDiag(Mat *thee);

#endif /* _WHB_P_H_ */
