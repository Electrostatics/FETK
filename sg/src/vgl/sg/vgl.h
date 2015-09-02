/** 
 * @defgroup Vgl Vgl class
 * @brief    Window-system (X11/Win32/etc) wrapper for Class Ogl.
 */

/**
 *  @file       vgl.h
 *  @ingroup    Vgl
 *  @brief      Class Vgl: Window-system (X11/Win32/etc) wrapper for Class Ogl. 
 *  @author     Michael Holst
 *  @note       None
 *  @version    $Id: vgl.h,v 1.33 2010/08/12 04:56:27 fetk Exp $
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

#ifndef _VGL_H_
#define _VGL_H_

#include <sg/sg_base.h>

#include <sg/ogl.h>
#include <sg/oglps.h>

/*
 * ***************************************************************************
 * Class Vgl: Parameters and datatypes
 * ***************************************************************************
 */

/**
 *  @ingroup Vgl
 *  @brief   Class Vgl: Definition
 *  @author  Michael Ho.st
 */
struct sVgl {

    int    mode;             /**< @brief what capabilities do i have */

    void   *appCon;          /**< @brief application context */

    Vio    *pbuf;            /**< @brief the polygon buffer */

    Vio    *sock;            /**< @brief the socket object */
    int    socket;           /**< @brief currently selected socket number */

    char   socktype[80];     /**< @brief socket type */
    char   dataform[80];     /**< @brief xdr vs. ascii */
    char   hostname[80];     /**< @brief hostname for inet sockets */
    char   filename[80];     /**< @brief filename for file i/o */
    char   username[80];     /**< @brief username for i/o */

    int    settings[7];      /**< @brief lightening and other effects */
    int    list[10];         /**< @brief display list states */

    char   id[VMAX_BUFSIZE]; /**< @brief my id */

    int    douBuf;           /**< @brief double or single buffer */

    int    winInit;          /**< @brief have we been initialized */
    int    winUp;            /**< @brief is the main window currently up */

    int    minWidth;         /**< @brief minimum width of form window */
    int    minHeight;        /**< @brief minimum height of form window */
    int    maxWidth;         /**< @brief maximum width of form window */
    int    maxHeight;        /**< @brief maximum height of form window */

    int    mainFormWidth;    /**< @brief width of form window */
    int    mainFormHeight;   /**< @brief height of form window */

    int    plotWidth;        /**< @brief width of OpenGL window */
    int    plotHeight;       /**< @brief height of OpenGL window */

    int    ButtonWidth;      /**< @brief button width */
    int    ButtonHeight;     /**< @brief button height */
    int    ButtonVertSep;    /**< @brief button vertical separator */
    int    ButtonHorizSep;   /**< @brief button horizontal separator */

    int    defaultSep;       /**< @brief default separator */
    int    defaultBorder;    /**< @brief default border */

    int    top;              /**< @brief top of OpenGL window */
    int    left;             /**< @brief left of OpenGL window */
    int    theScale;         /**< @brief the scale */

    int    ncolor;           /**< @brief number of colors */
    float  red[256];         /**< @brief reds */
    float  green[256];       /**< @brief greens */
    float  blue[256];        /**< @brief blues */

    int            spinning; /**< @brief am i spinning now */
    unsigned long  spinId;   /**< @brief my spinning callback id */

    /** @brief Pointer to the Vgl class */
    int (*buildDisplayLists)(struct sVgl *thee);

    Ogl    *ogl;             /**< the OpenGL device */

    void   *vcore;           /**< window-system dependent sub-objects */

};

/**
 * @ingroup Vgl
 * @brief   Declaraction of the Vgl class as the Vgl structure
 * @author  Michael Holst
 */
typedef struct sVgl Vgl;

/*
 * ***************************************************************************
 * Class Vgl: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_VGL)
#else /* if defined(VINLINE_VGL) */
#endif /* if !defined(VINLINE_VGL) */


/** 
 * @ingroup Vgl
 * @brief   the Vgl class
 * @author  Michael Holst
 * @note    Class Vgl: Non-inlineable methods (vgl.c) 
 * @return  Success enumeration
 */
VEXTERNC int Vgl_capability(void);

/** 
 * @ingroup Vgl
 * @brief   the Vgl class
 * @author  Michael Holst
 * @note    Class Vgl: Non-inlineable methods (vgl.c) 
 * @return  Pointer to a new allocated Vgl class
 * @param   mode              mode option
 * @param   socktype          pointer to socket type 
 * @param   dataform          pointer to different data formats
 * @param   hostname          pointer to the hostname
 * @param   filename          pointer to the file name
 * @param   xsize             main Form Width
 * @param   ysize             main Form Height
 * @param   xpos              
 * @param   ypos              MIKE-FIX
 * @param   buildDisplayLists MIKE-FIX
 */
VEXTERNC Vgl* Vgl_ctor(int mode,
    char *socktype, char *dataform, char *hostname, char *filename,
    int xsize, int ysize, int xpos, int ypos,
    int (*buildDisplayLists)(Vgl *thee));

/** 
 * @ingroup Vgl
 * @brief   MIKE-FIX
 * @author  Michael Holst
 * @note    Class Vgl: Non-inlineable methods (vgl.c) 
 * @return  None
 * @param   thee MIKE-FIX
 */
VEXTERNC void Vgl_dtor(Vgl **thee);

/** 
 * @ingroup Vgl
 * @brief   MIKE-FIX
 * @author  Michael Holst
 * @note    Class Vgl: Non-inlineable methods (vgl.c) 
 * @return  None
 * @param   thee   MIKE-FIX
 * @param   ncolor MIKE-FIX
 * @param   red    MIKE-FIX
 * @param   green  MIKE-FIX
 * @param   blue   MIKE-FIX
 */
VEXTERNC void Vgl_putl(Vgl *thee,
    int ncolor, float red[], float green[], float blue[]);

/** 
 * @ingroup Vgl
 * @brief   MIKE-FIX
 * @author  Michael Holst
 * @note    Class Vgl: Non-inlineable methods (vgl.c) 
 * @return  None
 * @param   thee  MIKE-FIX
 * @param   dlist MIKE-FIX
 * @param   show  MIKE-FIX
 */
VEXTERNC void Vgl_list(Vgl *thee, int dlist, int show);

/** 
 * @ingroup Vgl
 * @brief   MIKE-FIX
 * @author  Michael Holst
 * @note    Class Vgl: Non-inlineable methods (vgl.c) 
 * @return  None
 * @param   thee   MIKE-FIX
 * @param   x      MIKE-FIX
 * @param   y      MIKE-FIX
 * @param   z      MIKE-FIX
 * @param   np     MIKE-FIX
 * @param   icolor MIKE-FIX
 * @param   color  MIKE-FIX
 */
VEXTERNC void Vgl_line(Vgl *thee,
    float x[], float y[], float z[], int np, int icolor, float color[]);

/** 
 * @ingroup Vgl
 * @brief   MIKE-FIX
 * @author  Michael Holst
 * @note    Class Vgl: Non-inlineable methods (vgl.c) 
 * @return  None
 * @param   thee   MIKE-FIX
 * @param   x      MIKE-FIX
 * @param   y      MIKE-FIX
 * @param   z      MIKE-FIX
 * @param   np     MIKE-FIX
 * @param   icolor MIKE-FIX
 * @param   color  MIKE-FIX
 */
VEXTERNC void Vgl_fill(Vgl *thee,
    float x[], float y[], float z[], int np, int icolor, float color[]);

/** 
 * @ingroup Vgl
 * @brief   MIKE-FIX
 * @author  Michael Holst
 * @note    Class Vgl: Non-inlineable methods (vgl.c) 
 * @return  None
 * @param   thee   MIKE-FIX
 * @param   x      MIKE-FIX
 * @param   y      MIKE-FIX
 * @param   z      MIKE-FIX
 * @param   line   MIKE-FIX
 * @param   icolor MIKE-FIX
 * @param   color  MIKE-FIX
 */
VEXTERNC void Vgl_text(Vgl *thee,
    float x[], float y[], float z[], char line[], int icolor, float color[]);

/** 
 * @ingroup Vgl
 * @brief   MIKE-FIX
 * @author  Michael Holst
 * @note    Class Vgl: Non-inlineable methods (vgl.c) 
 * @return  None
 * @param   thee   MIKE-FIX
 * @param   x      MIKE-FIX
 * @param   y      MIKE-FIX
 * @param   z      MIKE-FIX
 * @param   np     MIKE-FIX
 * @param   icolor MIKE-FIX
 * @param   color  MIKE-FIX
 * @param   itype  MIKE-FIX
 * @param   radius MIKE-FIX
 */
VEXTERNC void Vgl_pont(Vgl *thee,
    float x[], float y[], float z[], int np, int icolor, float color[],
    int itype, float radius);

#endif /* _VGL_H_ */

