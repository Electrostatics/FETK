/*
 * ***************************************************************************
 * SG = < Socket Graphics >
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
 * rcsid="$Id: sg_base.c,v 1.9 2010/08/12 04:56:16 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     sg_base.c
 *
 * Purpose:  SG linkage assistance.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "sg_base_p.h"

VEMBED(rcsid="$Id: sg_base.c,v 1.9 2010/08/12 04:56:16 fetk Exp $")

/*
 * ***************************************************************************
 * Routine:  sg_link, sg_needs_XXX
 *
 * Purpose:  Autoconf linkage assistance for packages built on top of SG.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
void sg_link(void)
{
}

#if defined(HAVE_MOTIF)
    VPUBLIC void sg_needs_motif(void)
    {
    }
#endif

