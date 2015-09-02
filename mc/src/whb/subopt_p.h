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
 * rcsid="$Id: subopt_p.h,v 1.9 2010/08/12 05:19:24 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     subopt_p.h
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
 * Class Whb: Non-Inlineable methods (subopt.c)
 * ***************************************************************************
 */
VPRIVATE void Bvec_sfmg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bchar *fc);

VPRIVATE void Bvec_sfpcg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bchar *fc, Bvec *p, Bvec *ap, Bvec *bap, Bvec *po, Bvec *apo, Bvec *tp);

VPRIVATE void Bvec_sfpbcg(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bchar *fc, Bvec *s, Bvec *p, Bvec *ap, Bvec *bap, Bvec *po, Bvec *apo,
    Bvec *q, Bvec *atq, Bvec *btatq, Bvec *qo, Bvec *atqo);

VPRIVATE void Bchar_sfmgInit(Bchar *thee, int prec, Bmat *A, Bmat *P);

VPRIVATE void Bchar_sfmgDestroy(Bchar *thee);

VPRIVATE void Bvec_sfmgCore(Bvec *thee, Bmat *A, Bvec *f, Bvec *r, Bvec *ut,
    int key, int flag, int itmax, double etol, int prec, int cycle, Bmat *P,
    Bchar *fc);


#endif /* _WHB_P_H_ */
