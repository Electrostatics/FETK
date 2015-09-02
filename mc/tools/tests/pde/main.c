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
 * rcsid="$Id: main.c,v 1.8 2010/08/12 05:19:41 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     main.c
 *
 * Purpose:  Test program for PDE class.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "mc/pde.h"

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
VEMBED(rcsid="$Id: main.c,v 1.8 2010/08/12 05:19:41 fetk Exp $")

VPUBLIC PDE* myPDE_ctor(void)
{
    int i;
    PDE *thee = VNULL;

    /* create some space for the pde object */
    thee = Vmem_malloc( VNULL, 1, sizeof(PDE) );

    /* return the new pde object */
    return thee;
}

VPUBLIC void myPDE_dtor(PDE **thee)
{
    VASSERT( (*thee) != VNULL );
    if ((*thee) != VNULL) {

        Vmem_free( VNULL, 1, sizeof(PDE), (void**)thee );

        (*thee) = VNULL;
    }
}

int main(int argc, char **argv)
{
    PDE *myPde = VNULL;

    /* some i/o */
    Vnm_print(0,"main: starting.\n");

    /* construct the PDE object */
    myPde = myPDE_ctor();

    /* destroy the PDE object */
    myPDE_dtor(&myPde);

    /* some more i/o */
    Vnm_print(0,"main: stopping.\n");

    /* normal return */
    return 0;
}

