/* $Id: vb.c,v 1.2 2000/10/27 15:21:40 mholst Exp $ */

/*
 * Mesa 3-D graphics library
 * Version:  2.0
 * Copyright (C) 1995-1996  Brian Paul
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "types.h"
#include "vb.h"



/*
 * Initialize the vertex buffer.
 */
void gl_init_vb( struct vertex_buffer* VB )
{
   GLuint i;

   for (i=0;i<VB_SIZE;i++) {
      VB->Unclipped[i] = 1;
      VB->MaterialMask[i] = 0;
   }
   VB->MaterialChanges = GL_FALSE;
}


