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
 * rcsid="$Id: vgl_p.h,v 1.21 2010/08/12 04:56:25 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     vgl_p.h
 *
 * Purpose:  PRIVATE header.
 *
 * Author:   Michael Holst and Randy Bank
 * ***************************************************************************
 */

#ifndef _VGL_P_H_
#define _VGL_P_H_

#include <sg/vgl.h>
#include "sgcf.h"

#include <sg/ogl.h>
#include <sg/oglps.h>

/* X11/GLX or Win32/GLW or <OS-type/GL-interface> headers */
#if defined(HAVE_X11)
#   include <X11/keysym.h>
#   include <X11/IntrinsicP.h>
#   include <X11/StringDefs.h>
#   include <X11/Shell.h>
#   include <X11/Xaw/Form.h>
#   include <X11/Xaw/Box.h>
#   include <X11/Xaw/Command.h>
#   include <GL/glx.h>
#   include <GL/GLwDrawA.h>
#   if defined(HAVE_MOTIF)
#       include <Xm/Xm.h>
#       include <Xm/Form.h>
#       include <Xm/PushB.h>
#       include <Xm/DrawnB.h>
#       include <Xm/FileSB.h>
#       include <Xm/Text.h>
#       include <Xm/RowColumn.h>
#   endif
#elif defined(HAVE_WIN32)
#   include <windows.h>
#elif defined(HAVE_NEXT)
#   include <AppKit/AppKit.h>
#   include <AppKit/event.h>
#   include <GL/osmesa.h>
#endif

/*
 * ***************************************************************************
 * Class Vgl: Parameters and datatypes
 * ***************************************************************************
 */

#if defined(HAVE_X11)
#    define VPTR     XtPointer
#    define VCBPROC  XtCallbackProc
#    define VWIDGET  Widget
#    define VKEY_ESC XK_Escape
#    define VKEY_QUE XK_question

#    define VKEY_0 XK_0
#    define VKEY_1 XK_1
#    define VKEY_2 XK_2
#    define VKEY_3 XK_3
#    define VKEY_4 XK_4
#    define VKEY_5 XK_5
#    define VKEY_6 XK_6
#    define VKEY_7 XK_7
#    define VKEY_8 XK_8
#    define VKEY_9 XK_9

#    define VKEY_a XK_a
#    define VKEY_b XK_b
#    define VKEY_c XK_c
#    define VKEY_d XK_d
#    define VKEY_e XK_e
#    define VKEY_f XK_f
#    define VKEY_g XK_g
#    define VKEY_h XK_h
#    define VKEY_i XK_i
#    define VKEY_j XK_j
#    define VKEY_k XK_k
#    define VKEY_l XK_l
#    define VKEY_m XK_m
#    define VKEY_n XK_n
#    define VKEY_o XK_o
#    define VKEY_p XK_p
#    define VKEY_q XK_q
#    define VKEY_r XK_r
#    define VKEY_s XK_s
#    define VKEY_t XK_t
#    define VKEY_u XK_u
#    define VKEY_v XK_v
#    define VKEY_w XK_w
#    define VKEY_x XK_x
#    define VKEY_y XK_y
#    define VKEY_z XK_z

#    define VKEY_A XK_A
#    define VKEY_B XK_B
#    define VKEY_C XK_C
#    define VKEY_D XK_D
#    define VKEY_E XK_E
#    define VKEY_F XK_F
#    define VKEY_G XK_G
#    define VKEY_H XK_H
#    define VKEY_I XK_I
#    define VKEY_J XK_J
#    define VKEY_K XK_K
#    define VKEY_L XK_L
#    define VKEY_M XK_M
#    define VKEY_N XK_N
#    define VKEY_O XK_O
#    define VKEY_P XK_P
#    define VKEY_Q XK_Q
#    define VKEY_R XK_R
#    define VKEY_S XK_S
#    define VKEY_T XK_T
#    define VKEY_U XK_U
#    define VKEY_V XK_V
#    define VKEY_W XK_W
#    define VKEY_X XK_X
#    define VKEY_Y XK_Y
#    define VKEY_Z XK_Z

#elif defined(HAVE_WIN32) || defined(HAVE_NEXT)
#    define VPTR     void*
#    define VCBPROC  int
#    define VWIDGET  int*
#    define VKEY_ESC 0x1B
#    define VKEY_QUE 0x3f

#    define VKEY_0 '0'
#    define VKEY_1 '1'
#    define VKEY_2 '2'
#    define VKEY_3 '3'
#    define VKEY_4 '4'
#    define VKEY_5 '5'
#    define VKEY_6 '6'
#    define VKEY_7 '7'
#    define VKEY_8 '8'
#    define VKEY_9 '9'

#    define VKEY_a 'a'
#    define VKEY_b 'b'
#    define VKEY_c 'c'
#    define VKEY_d 'd'
#    define VKEY_e 'e'
#    define VKEY_f 'f'
#    define VKEY_g 'g'
#    define VKEY_h 'h'
#    define VKEY_i 'i'
#    define VKEY_j 'j'
#    define VKEY_k 'k'
#    define VKEY_l 'l'
#    define VKEY_m 'm'
#    define VKEY_n 'n'
#    define VKEY_o 'o'
#    define VKEY_p 'p'
#    define VKEY_q 'q'
#    define VKEY_r 'r'
#    define VKEY_s 's'
#    define VKEY_t 't'
#    define VKEY_u 'u'
#    define VKEY_v 'v'
#    define VKEY_w 'w'
#    define VKEY_x 'x'
#    define VKEY_y 'y'
#    define VKEY_z 'z'

#    define VKEY_A 'A'
#    define VKEY_B 'B'
#    define VKEY_C 'C'
#    define VKEY_D 'D'
#    define VKEY_E 'E'
#    define VKEY_F 'F'
#    define VKEY_G 'G'
#    define VKEY_H 'H'
#    define VKEY_I 'I'
#    define VKEY_J 'J'
#    define VKEY_K 'K'
#    define VKEY_L 'L'
#    define VKEY_M 'M'
#    define VKEY_N 'N'
#    define VKEY_O 'O'
#    define VKEY_P 'P'
#    define VKEY_Q 'Q'
#    define VKEY_R 'R'
#    define VKEY_S 'S'
#    define VKEY_T 'T'
#    define VKEY_U 'U'
#    define VKEY_V 'V'
#    define VKEY_W 'W'
#    define VKEY_X 'X'
#    define VKEY_Y 'Y'
#    define VKEY_Z 'Z'
#endif

#define NUM_BUTTONS 7

typedef enum VGLbuttons {
    VGL_SOCKET   = 0,   /* socket menu */
    VGL_SETTINGS = 1,   /* settings menu */
    VGL_LISTS    = 2,   /* display list menu */
    VGL_GL2FILE  = 3,   /* PS/XPM/BH file generation */
    VGL_FILE2GL  = 4,   /* BH/OFF/IV/PQR file load */
    VGL_RESET    = 5,   /* reset rotator position */
    VGL_QUIT     = 6    /* quit */
} VGLbuttons;

typedef enum VGLsettings {
    VGL_LIGHT = 0,      /* lighting effects        */
    VGL_ORTHO = 1,      /* orthographic projection */
    VGL_FRAME = 2,      /* three frames            */
    VGL_BALL  = 3,      /* quaternion trackball    */
    VGL_BBOX  = 4,      /* bounding box            */
    VGL_XDR   = 5       /* XDR input file format   */
} VGLsettings;

VEXTERNC Vgl *theeVgl;

/*
 * ***************************************************************************
 * Class Vgl: Definition
 * ***************************************************************************
 */

typedef struct Vglcore {
#if defined(HAVE_X11)
    Widget           topLev;
    Widget           mainForm;
    Widget           plot;
    Widget           psgenMenu;
    Widget           resetMenu;
    Widget           socketMenu;
    Widget           settingsMenu;
    Widget           listMenu;
    Widget           fileSelect;
    Widget           button[NUM_BUTTONS];
    GLXContext       glxCon;
    XVisualInfo      *xVisInf;
    Display          *dpy;
    Screen           *scr;
    Pixel            foregrnd;
    Pixel            backgrnd;
    Pixel            buttonForegrnd;
    Pixel            buttonBackgrnd;
    int              rgbaVis;
    int              cmapIns;
    int              fontHeight;
# if defined(HAVE_MOTIF)
    XmFontList       theFont;
    XmFontListEntry  theFontEntry;
# endif
#elif defined(HAVE_WIN32)
    HWND             topLev;
    HDC              plot;
    HGLRC            glxCon;
#elif defined(HAVE_NEXT)
    NSWindow         *topLev;
    NSBitmapImageRep *plot;
    OSMesaContext    glxCon;
    NSView           *theViu;
    unsigned char    *buf; 
#endif

} Vglcore;

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
 * Class Vgl: Non-inlineable methods (vgl.c)
 * ***************************************************************************
 */

VEXTERNC void Vgl_open(Vgl *thee, int xsize, int ysize, int xpos, int ypos);
VEXTERNC void Vgl_quit(Vgl *thee);
VEXTERNC void Vgl_swapBuffers(Vgl *thee);
VEXTERNC void Vgl_makeCurrent(Vgl *thee);
VEXTERNC void Vgl_eventLoop(Vgl *thee);
VEXTERNC void Vgl_spin(void *wId, unsigned long *tId);
VEXTERNC void Vgl_getPolys(void *wId, unsigned long *tId);
VEXTERNC void Vgl_makeColors(Vgl *thee);
VEXTERNC void Vgl_makeGeom(Vgl *thee, int key);
VEXTERNC void Vgl_unmakeWidgets(Vgl *thee);
VEXTERNC void Vgl_makeWidgets(Vgl *thee);
VEXTERNC void Vgl_buildListMenu(Vgl *thee);
VEXTERNC void Vgl_buildPsgenMenu(Vgl *thee);
VEXTERNC void Vgl_buildResetMenu(Vgl *thee);
VEXTERNC void Vgl_buildSocketMenu(Vgl *thee);
VEXTERNC void Vgl_buildSettingsMenu(Vgl *thee);
VEXTERNC void Vgl_fileSelectHandle(Vgl *thee);
VEXTERNC void Vgl_prtStat(Vgl *thee);
VEXTERNC void Vgl_redraw(Vgl *thee);

VEXTERNC VCBPROC Vgl_listCallback(VWIDGET w,
    VPTR cli, VPTR cal);
VEXTERNC VCBPROC Vgl_settingsCallback(VWIDGET w,
    VPTR cli, VPTR cal);
VEXTERNC VCBPROC Vgl_fileWriteCallback(VWIDGET w,
    VPTR cli, VPTR cal);
VEXTERNC VCBPROC Vgl_resetCallback(VWIDGET w,
    VPTR cli, VPTR cal);
VEXTERNC VCBPROC Vgl_socketCallBack(VWIDGET w,
    VPTR cli, VPTR cal);
VEXTERNC VCBPROC Vgl_fileReadCallback(VWIDGET w,
    VPTR cli, VPTR cal);

#if defined(HAVE_X11)
    VEXTERNC void Vgl_handler(Widget w,
        VPTR msg, XEvent *wParam, VPTR lParam);
#elif defined(HAVE_WIN32)
    VEXTERNC WINAPI Vgl_handler(HWND w,
        UINT msg, DWORD wParam, LONG lParam);
#elif defined(HAVE_NEXT)
#endif

#endif /* _VGL_P_H_ */

