/**
 * @defgroup Ogl Ogl class
 * @brief    A virtual (window system-independent) OpenGL object
 */

/**
 *  @file       ogl.h
 *  @ingroup    Ogl
 *  @brief      Class Ogl: a virtual (window system-independent) OpenGL object.
 *  @author     Michael Holst
 *  @note       None
 *  @version    $Id: ogl.h,v 1.17 2010/08/12 04:56:24 fetk Exp $
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

#ifndef _OGL_H_
#define _OGL_H_

#include <sg/sg_base.h>

/*
 * ***************************************************************************
 * Class Ogl: Parameters and datatypes
 * ***************************************************************************
 */

/**
 * @ingroup Ogl
 * @brief   Class Ogl: Definition
 * @author  Michael Holst
 */
struct sOgl {

  /** @brief frame (0=centered, 1=offset) */
    int    frameMode;
  /** @brief projection (0=perspect, 1=ortho) */
    int    orthoMode;
  /** @brief draw (0=none, 1=draw arcball) */
    int    ballMode;
  /** @brief draw (0=none, 1=draw bounding box) */
    int    bboxMode;
  /** @brief mouse (0=rotate, 1=scale, 2=translate) */
    int    mouseMode;
  /** @brief lighting (0=no, 1=yes) */
    int    lightMode;
  /** @brief polybackside dark paint (0=no, 1=yes) */
    int    backMode;

  /** @brief width of the plotbox */
    int    viewWidth;
  /** @brief height of the plotbox */
    int    viewHeight;
  /** @brief current eye position up the z-axis */
    float  eyezInit;
  /** @brief current global scaling */
    float  scale;
  /** @brief vector of the view (handles possible translation) */
    float  eye[3]; 
  /** @brief origin of the view (handles possible translation) */
    float  origin[3];
  /** @brief translation matrix */
    float  trans[3];
  /** @brief minimal coordinates of the bbox */
    float  min[3];
  /** @brief maximal coordinates of the bbox */
    float  max[3];
  /** @brief bbox coordinates */
    float  bboxCoord[8][3];

  /** @brief is mouse button pressed (0=no, 1=yes) */
    int    mouseDown;
  /** @brief rotation coordinates */
    float  r0[3];
  /** @brief rotation coordinates  */
    float  r1[3];
  /** @brief rotation coordinates  */
    float  r2[3];
  /** @brief  scale array */
    float  s1[3];
  /** @brief scale array */
    float  s2[3];
  /** @brief translation aray */
    float  t1[3];
  /** @brief translation aray  */
    float  t2[3];
  /** @brief quaternion array */
    float  quat[4];
  /** @brief quatDrag array */
    float  quatDrag[4];

  /** @brief display list settings */
    int    list[10];
  /** @brief  listMode array*/
    int    listMode[10];
  /** @brief quaternion trackball */
    int    ball;
  /** @brief bounding box */
    int    bbox;
  /** @brief index for updating bbox or not */ 
    int bboxUpdate;

};

/**
 * @ingroup Ogl
 * @brief   Declaration of the Ogl class as the Ogl structure
 * @author  Michael Holst
 */
typedef struct sOgl Ogl;

/*
 * ***************************************************************************
 * Class Ogl: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_OGL)
#else /* if defined(VINLINE_OGL) */
#endif /* if !defined(VINLINE_OGL) */

/**
 * @ingroup Ogl
 * @brief   Construct an Ogl object.
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  Pointer to a newly allocated (empty) Ogl object
 * @param   frameMode frame (0=centered, 1=offset)
 * @param   orthoMode projection (0=perspect, 1=ortho)
 */
VEXTERNC Ogl* Ogl_ctor(int frameMode, int orthoMode);

/**
 * @ingroup Ogl
 * @brief   Ogl object destructor.
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC void Ogl_dtor(Ogl **thee);

/**
 * @ingroup Ogl
 * @brief   Initialize the OpenGL context.
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC void Ogl_initBegin(Ogl *thee);

/**
 * @ingroup Ogl
 * @brief   Initialize the OpenGL context.
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC void Ogl_initEnd(Ogl *thee);

/**
 * @ingroup Ogl
 * @brief   Make a generic display list.
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 * @param   list index for list options.
 * @param   show index for displaying the list or not.
 */
VEXTERNC void Ogl_beginList(Ogl *thee, int list, int show);

/**
 * @ingroup Ogl
 * @brief   Make a generic display list.
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC void Ogl_endList(Ogl *thee);

/**
 * @ingroup Ogl
 * @brief   Make a generic display list.
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee  Pointer to the Ogl object.
 * @param   type  index for type options
 *          type==0  ==>  edges (a line strip)
 *          type==1  ==>  filled polygon
 *          type==3  ==>  text
 *          type==4  ==>  2-sphere (coarse resolution)
 *          type==5  ==>  2-sphere (medium resolution)
 *          type==6  ==>  2-sphere (fine resolution)
 * @param   numPV number of different point/line/polygon
 * @param   vx    vertex coordinates
 * @param   c     parameter array
 * @param   r     coeficient to scale vertex coordinates.
 * @param   text  text char array
 */
VEXTERNC void Ogl_addListObject(Ogl *thee,
    int type, int numPV, float vx[][3], float c[4], float r, char text[]);

/**
 * @ingroup Ogl
 * @brief   The main 3D==>2D Projection function.  
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 * @param   w    width of the plotbox
 * @param   h    height of the plotbox
 */
VEXTERNC void Ogl_reshape(Ogl *thee, int w, int h);

/**
 * @ingroup Ogl
 * @brief   Main OpenGL display driver.
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @verbatim
 * Notes:    We use the Z-buffer here for hidden line and hidden surface
 *           removal.  We just have to make sure that we get a visual
 *           device with some Z-buffer bits, and that we don't mess up the
 *           transformations so that the Z-axis points somewhere other than
 *           positively straight at the eye.
 *
 * Frame codes:
 *
 *           If "frameMode==0", we draw only the frame 4 lists (4-9),
 *           centered in frame 1 show below, regardless of window shape.
 *
 *           If "frameMode==1", we draw frame 1,2,3,4 lists (0-9), in the
 *           appropriate frames.
 *
 *      ._____._____._____.     ._____._____._____.     ._____._____.......
 *      |                 |     |           |     |     |           |     .
 *      |                 |     |           |  2  |     |           |     .
 *      |        1        |     |     4     |_____|     |     ?     |......
 *      |                 |     |           |     |     |           |     .
 *      |                 |     |           |  3  |     |           |     .
 *      |_____._____._____|     |_____._____|_____|     |_____._____.......
 *
 * Display list codes:
 *
 *      List   Frame     Type
 *
 *         0       1     non-rotating, non-lighted
 *         1       1     non-rotating, non-lighted
 *         2       2     non-rotating, non-lighted
 *         3       3     non-rotating, non-lighted
 *
 *         4       4     non-rotating, non-lighted
 *         5       4         rotating, non-lighted
 *         6       4         rotating, non-lighted
 *         7       4         rotating,     lighted
 *         8       4         rotating,     lighted
 *         9       4     non-rotating,     lighted
 * @endverbatim
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC void Ogl_display(Ogl *thee);

/**
 * @ingroup Ogl
 * @brief   Some simple callback routines to manipulate the object. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC int Ogl_lightModeOnOff(Ogl *thee);

/**
 * @ingroup Ogl
 * @brief   Some simple callback routines to manipulate the object. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC int Ogl_orthoModeOnOff(Ogl *thee);

/**
 * @ingroup Ogl
 * @brief   Some simple callback routines to manipulate the object. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC int Ogl_frameModeOnOff(Ogl *thee);

/**
 * @ingroup Ogl
 * @brief   Some simple callback routines to manipulate the object. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC int Ogl_ballModeOnOff(Ogl *thee);

/**
 * @ingroup Ogl
 * @brief   Some simple callback routines to manipulate the object. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC int Ogl_bboxModeOnOff(Ogl *thee);

/**
 * @ingroup Ogl
 * @brief   Some simple callback routines to manipulate the object. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 * @param   list index for list options.
 */
VEXTERNC int Ogl_listModeOnOff(Ogl *thee, int list);

/**
 * @ingroup Ogl
 * @brief   Some simple callback routines to manipulate the object. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 * @param   list index for list options.
 */
VEXTERNC int Ogl_isList(Ogl *thee, int list);

/**
 * @ingroup Ogl
 * @brief   Some simple callback routines to manipulate the object. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 * @param   list index for list options.
 */
VEXTERNC int Ogl_isListOn(Ogl *thee, int list);

/**
 * @ingroup Ogl
 * @brief   Primary rotation/scaling/translation routines. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee  Pointer to the Ogl object.
 * @param   value value of mouse (0=rotate, 1=scale, 2=translate)
 */
VEXTERNC void Ogl_setMouseMode(Ogl *thee, int value);

/**
 * @ingroup Ogl
 * @brief   Primary rotation/scaling/translation routines. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 * @param   x    width parameter
 * @param   y    height parameter
 */
VEXTERNC void Ogl_mouseDown(Ogl *thee, int x, int y);

/**
 * @ingroup Ogl
 * @brief   Primary rotation/scaling/translation routines. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 * @param   x    width parameter
 * @param   y    height parameter
 */
VEXTERNC void Ogl_mouseUp(Ogl *thee, int x, int y);

/**
 * @ingroup Ogl
 * @brief   Primary rotation/scaling/translation routines. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 * @param   x    width parameter
 * @param   y    height parameter
 */
VEXTERNC void Ogl_mouseMotion(Ogl *thee, int x, int y);

/**
 * @ingroup Ogl
 * @brief   Primary rotation/scaling/translation routines. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC int Ogl_spin(Ogl *thee);

/**
 * @ingroup Ogl
 * @brief   Some simple callback routines to manipulate the object. 
 * @author  Michael Holst
 * @note    Class Ogl: Non-inlineable methods (ogl.c) 
 * @return  None
 * @param   thee Pointer to the Ogl object.
 */
VEXTERNC void Ogl_resetPos(Ogl *thee);

#endif /* _OGL_H_ */

