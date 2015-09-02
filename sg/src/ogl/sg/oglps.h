/**
 *  @file       oglps.h
 *  @ingroup    Oglps
 *  @brief      High-quality OpenGL-to-Postscript rendering.
 *  @author     Michael Holst
 *  @note       None
 *  @version    $Id: oglps.h,v 1.13 2010/08/12 04:56:24 fetk Exp $
 * 
 *  @attention
 *  @verbatim
 *
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
 *  @endverbatim
 */

#ifndef _OGLPS_H_
#define _OGLPS_H_

#include <sg/sg_base.h>

/*
 * ***************************************************************************
 * Oglps: Parameters and datatypes
 * ***************************************************************************
 */

/** 
 * @ingroup Oglps
 * @brief   Setup the feedback buffer for the OpenGL library to render into.  
 * @author  Michael Holst
 * @note    We malloc the float, triangle, and edge buffer areas, 
 *          set glRenderMode to GL_FEEDBACK, and finish by opening the
 *          output postscript file.\n
 *          The input parameters are interpretted as:\n
 *          filename  ==> name of eventual output PostScript file   
 * @return  None
 */
VEXTERNC void Oglps_begin(void);

/** 
 * @ingroup Oglps
 * @brief   Feed triangles from the OpenGL library into our buffer
 *          and output to file.
 * @author  Michael Holst
 * @note    We flush the OpenGL rendering buffer, grab the triangles and 
 *          edges from feedback buffer, construct a proper ordering for the 
 *          painter's algorithm, and finally write the postscript output.
 * @return  None
 * @param   outLine   0=use filled triangles\n
 *                    1=use filled triangles and then outline them
 * @param   inColor   0=grayscale\n
 *                    1=color
 * @param   doCulling 0=don't cull (render everything)\n
 *                    1=cull (remove backface triangles before rendering)
 */
VEXTERNC void Oglps_end(int outLine, int inColor, int doCulling);

/** 
 * @ingroup Oglps
 * @brief   Quick and dirty postscript generator (low-resolution only). 
 * @author  Michael Holst
 * @note    This generator is a modified example from Mark Kilgard's book.
 * @return  None
 * @param   filename name of file containing PostScript output   
 * @param   inColor  0=grayscale, 1=color
 * @param   width    width of input image in pixels
 * @param   height   height of input image in pixels 
 */
VEXTERNC void Oglps_gen(char *filename, int inColor, int width, int height);

#endif /* _OGLPS_H_ */

