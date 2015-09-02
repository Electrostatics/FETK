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
 * rcsid="$Id: vglm_p.h,v 1.13 2010/08/12 04:56:26 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     vglm_p.h
 *
 * Purpose:  PRIVATE header.
 *
 * Author:   Michael Holst and Randy Bank
 * ***************************************************************************
 */

#ifndef _VGLM_P_H_
#define _VGLM_P_H_

#include "vgl_p.h"

/*
 * ***************************************************************************
 * Class Vgl: Definition
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Class Vgl: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_VGL)
#else /* if defined(VINLINE_VGL) */
#endif /* if !defined(VINLINE_VGL) */

/*
 * ***************************************************************************
 * Class Vgl: Non-inlineable methods (vglm.c)
 * ***************************************************************************
 */

VEXTERNC void Vgl_M_buildListMenu(Vgl *thee);
VEXTERNC void Vgl_M_buildPsgenMenu(Vgl *thee);
VEXTERNC void Vgl_M_buildResetMenu(Vgl *thee);
VEXTERNC void Vgl_M_buildSocketMenu(Vgl *thee);
VEXTERNC void Vgl_M_buildSettingsMenu(Vgl *thee);

VEXTERNC void Vgl_M_fileSelectHandle(Vgl *thee);
VEXTERNC XtCallbackProc Vgl_M_fileReadCallback(Widget w,
    VPTR cli, VPTR cal);

#endif /* _VGLM_P_H_ */

