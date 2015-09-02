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
 * rcsid="$Id: io.c,v 1.9 2010/08/12 05:18:18 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     io.c
 *
 * Purpose:  Class Aprx: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "aprx_p.h"

VEMBED(rcsid="$Id: io.c,v 1.9 2010/08/12 05:18:18 fetk Exp $")

/*
 * ***************************************************************************
 * Class Aprx: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_NAM)

#endif /* if !defined(VINLINE_NAM) */
/*
 * ***************************************************************************
 * Class Aprx: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Aprx_writeGEOM
 *
 * Purpose:  Write a finite element mesh or mesh function in some format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_writeGEOM(Aprx *thee, Vio *sock,
    int defKey, int colKey, int chartKey, double gluVal, int fkey,
    Bvec *u, char *format)
{
    int i;
    double *defX[MAXV];

    for (i=0; i<MAXV; i++) {
        defX[i] = VNULL;
    }
    for (i=0; i<Aprx_numB(thee); i++) {
        defX[i] = Bvec_addrB(u,i);
    }

    Gem_writeGEOM(thee->gm,sock,
        defKey,colKey,chartKey,gluVal,fkey,defX,format);
}

/*
 * ***************************************************************************
 * Routine:  Aprx_writeSOL
 *
 * Purpose:  Write a finite element mesh or mesh function in some format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Aprx_writeSOL(Aprx *thee, Vio *sock, Bvec *u, char *format)
{
    int i,fldKey;
    double *defX[MAXV];

    fldKey = Aprx_numB(thee);
    for (i=0; i<MAXV; i++) {
        defX[i] = VNULL;
    }
    for (i=0; i<fldKey; i++) {
        defX[i] = Bvec_addrB(u,i);
    }

    Gem_writeSOL(thee->gm,sock,fldKey,defX,format);
}

