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
 * rcsid="$Id: main.c,v 1.11 2010/08/12 05:19:39 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     main.c
 *
 * Purpose:  Main driver for the Manifold Code (MC)
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include <mc/nam.h>

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
VEMBED(rcsid="$Id: main.c,v 1.11 2010/08/12 05:19:39 fetk Exp $")

int main(int argc, char **argv)
{
    Aprx *vaprx = VNULL;
    AM *vam = VNULL;

    /* some i/o */
    Vnm_print(0,"main: starting.\n");

    /* construct the objects */
    vaprx = Aprx_ctor(VNULL, VNULL, VNULL);
    vam = AM_ctor(VNULL, vaprx);

    /* destroy the objects */
    Aprx_dtor(&vaprx);
    AM_dtor(&vam);

    /* some more i/o */
    Vnm_print(0,"main: stopping.\n");

    /* normal return */
    return 0;
}

