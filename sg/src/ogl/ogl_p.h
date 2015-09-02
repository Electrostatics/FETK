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
 * rcsid="$Id: ogl_p.h,v 1.5 2010/08/12 04:56:23 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     ogl_p.h
 *
 * Purpose:  PRIVATE header.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#ifndef _OGL_P_H_
#define _OGL_P_H_

#include <sg/ogl.h>
#include "sgcf.h"

#if defined(HAVE_WIN32)    /* "windows.h" needed -- bad design by Microsoft */
#    include <windows.h>
#endif
#include <GL/gl.h>         /* Core OpenGL library    */
#include <GL/glu.h>        /* OpenGL Utility library */

#endif /* _OGL_P_H_ */

