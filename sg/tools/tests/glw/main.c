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
 * rcsid="$Id: main.c,v 1.5 2010/08/12 04:56:35 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     main.c
 *
 * Purpose:  Driver program for testing the OpenGL Drawing Widget.
 *
 * Author:   Michael Holst (Hacked a test program found in Mesa)
 * ***************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <X11/X.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/Form.h>
#include <GL/gl.h>
#include <GL/GLwDrawA.h>

static GLint Black, Red, Green, Blue;

extern void quit_function (Widget, XtPointer, XtPointer);

void quit_function (Widget w, XtPointer closure, XtPointer call_data) {
    exit (0);
}

static void draw_cube (void) {
    /* X faces */
    glIndexi (Red);
    glColor3d (1.0, 0.0, 0.0);
    glBegin (GL_POLYGON); {
        glVertex3d (1.0, 1.0, 1.0);
        glVertex3d (1.0, -1.0, 1.0);
        glVertex3d (1.0, -1.0, -1.0);
        glVertex3d (1.0, 1.0, -1.0);
    }
    glEnd ();

    glBegin (GL_POLYGON);
    {
        glVertex3d (-1.0, 1.0, 1.0);
        glVertex3d (-1.0, 1.0, -1.0);
        glVertex3d (-1.0, -1.0, -1.0);
        glVertex3d (-1.0, -1.0, 1.0);
    }
    glEnd ();

    /* Y faces */
    glIndexi (Green);
    glColor3d (0.0, 1.0, 0.0);
    glBegin (GL_POLYGON); {
        glVertex3d (1.0, 1.0, 1.0);
        glVertex3d (1.0, 1.0, -1.0);
        glVertex3d (-1.0, 1.0, -1.0);
        glVertex3d (-1.0, 1.0, 1.0);
    }
    glEnd ();

    glBegin (GL_POLYGON); {
        glVertex3d (1.0, -1.0, 1.0);
        glVertex3d (-1.0, -1.0, 1.0);
        glVertex3d (-1.0, -1.0, -1.0);
        glVertex3d (1.0, -1.0, -1.0);
    }
    glEnd ();

    /* Z faces */
    glIndexi (Blue);
    glColor3d (0.0, 0.0, 1.0);
    glBegin (GL_POLYGON); {
        glVertex3d (1.0, 1.0, 1.0);
        glVertex3d (-1.0, 1.0, 1.0);
        glVertex3d (-1.0, -1.0, 1.0);
        glVertex3d (1.0, -1.0, 1.0);
    }
    glEnd ();

    glBegin (GL_POLYGON); {
        glVertex3d (1.0, 1.0, -1.0);
        glVertex3d (1.0, -1.0, -1.0);
        glVertex3d (-1.0, -1.0, -1.0);
        glVertex3d (-1.0, 1.0, -1.0);
    }
    glEnd ();
}

GLfloat xrot, yrot, zrot;

static void init_display (Widget w) {
    xrot = yrot = zrot = 0.0;

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearIndex (Black);
    glClearDepth (10.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
    glTranslated (0.0, 0.0, -3.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    glCullFace (GL_BACK);
    glEnable (GL_CULL_FACE);

    glShadeModel (GL_FLAT);
}

static void display (Widget w)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix (); {
        glRotated (xrot, 1.0, 0.0, 0.0);
        glRotated (yrot, 0.0, 1.0, 0.0);
        glRotated (zrot, 0.0, 0.0, 1.0);
        draw_cube ();
    }
    glPopMatrix ();
    glFinish ();
    GLwDrawingAreaSwapBuffers ( w );
      
    xrot += 1.0;
    yrot += 0.7;
    zrot -= 0.3;
}

static GLint alloc_color (Widget w, Colormap cmap, int red, int green, int blue)
{ 
    XColor xcolor;
    xcolor.red = red;
    xcolor.green = green;
    xcolor.blue = blue;
    xcolor.flags = DoRed | DoGreen | DoBlue;
    if (!XAllocColor (XtDisplay (w), cmap, &xcolor)) {
        printf ("Couldn't allocate color!\n");
        exit (1);
    }
    return xcolor.pixel;
}

static void translate_pixels (Widget to, Widget from, ...) {
    va_list ap;
    char *name;
    Colormap from_cmap, to_cmap;
    XColor xcolor;

    XtVaGetValues (from, XtNcolormap, &from_cmap, NULL);
    XtVaGetValues (to, XtNcolormap, &to_cmap, NULL);

    va_start (ap, from);
    for (name = va_arg (ap, char *); name != NULL; name = va_arg (ap, char *)) {
        XtVaGetValues (from, name, &xcolor.pixel, NULL);
        XQueryColor (XtDisplay (from), from_cmap, &xcolor);
        if (!XAllocColor (XtDisplay (to), to_cmap, &xcolor))
            XtAppWarning (XtWidgetToApplicationContext (to),
                "Couldn't allocate color!\n");
        else
            XtVaSetValues (from, name, xcolor.pixel, NULL);
    }
    va_end (ap);
}

/* Just like the movies: do 24 frames per second. */
unsigned long delay = 1000/24;

static void first_frame (Widget);
static void next_frame (XtPointer, XtIntervalId *);

static void first_frame (Widget w) {
    XtAppAddTimeOut (XtWidgetToApplicationContext (w),
        delay, next_frame, (XtPointer) w);
}

static void next_frame (XtPointer client_data, XtIntervalId *id) {
    Widget w = (Widget) client_data;
    first_frame (w);
    display (w);
}

static String fallback_resources[] = {
    "*GLwDrawingArea.width: 300",
    "*GLwDrawingArea.height: 300",
    "*GLwDrawingArea.rgba: true",
    "*GLwDrawingArea.installColormap: true",
    "*GLwDrawingArea.doublebuffer: true",
    NULL
};

int main (int argc, char *argv[]) {
    Widget top, frame, plot, quit;
    XtAppContext app_context;
    GLXContext glx_context;
    XVisualInfo *vi;
    Boolean rgba, doublebuffer, cmap_installed;

    top = XtVaAppInitialize (&app_context, "Cube", NULL, 0,
        &argc, argv, fallback_resources, NULL);

    frame = XtVaCreateManagedWidget ("frame", formWidgetClass, top, NULL);
    plot = XtVaCreateManagedWidget ("plot", glwDrawingAreaWidgetClass, frame,
        NULL);
    quit = XtVaCreateManagedWidget ("quit", commandWidgetClass, frame,
        XtNfromHoriz, plot, XtNhorizDistance, 10, NULL);
    XtAddCallback (quit, XtNcallback, quit_function, NULL);

    XtRealizeWidget (top);

    XtVaGetValues (plot, GLwNrgba, &rgba, GLwNinstallColormap, &cmap_installed,
        GLwNdoublebuffer, &doublebuffer, GLwNvisualInfo, &vi, NULL);

    /* create a visual context */
    glx_context = glXCreateContext (XtDisplay(plot), vi, 0, GL_FALSE);
    GLwDrawingAreaMakeCurrent( plot, glx_context );

    if (rgba) {
        Black = Red = Green = Blue = 0;

        if (cmap_installed) {
            /* In RGBA mode, widgets will have their own color map.
               Adjust the colors of the other widgets so that--even if the rest
               of the screen has wrong colors--all application widgets have the
               right colors.  */
             
            translate_pixels (plot, quit, XtNbackground, XtNforeground,
                XtNborder, NULL);
            translate_pixels (plot, frame, XtNbackground, XtNborder, NULL);

            /* Finally warp the pointer into the widget, to make sure that
            the user sees the right colors at the beginning.  */

            XWarpPointer (XtDisplay (plot), None, XtWindow (plot),
            0, 0, 0, 0, 0, 0);
        }
    } else {
        /* Allocate a few colors for use in color index mode.  */
        Colormap cmap;
        cmap = DefaultColormap(XtDisplay(top), DefaultScreen(XtDisplay (top)));
        Black = alloc_color (top, cmap, 0x0000, 0x0000, 0x0000);
        Red   = alloc_color (top, cmap, 0xffff, 0x0000, 0x0000);
        Green = alloc_color (top, cmap, 0x0000, 0xffff, 0x0000);
        Blue  = alloc_color (top, cmap, 0x0000, 0x0000, 0xffff);
    }

    init_display (plot);
    first_frame (plot);

    XtAppMainLoop (app_context);
    return (0);
}
