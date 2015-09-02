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
 * rcsid="$Id: main.c,v 1.6 2010/08/12 04:56:32 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     main.c
 *
 * Purpose:  Driver program for testing OpenGL.
 *
 * Author:   Michael Holst (Hacked the program found in the glXIntro manpage)
 * ***************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#if defined(HAVE_X11)
    #include <GL/glx.h>
#elif defined(HAVE_WIN32)
#elif defined(HAVE_NEXT)
    #include <AppKit/AppKit.h>
    #include <GL/osmesa.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#if defined(HAVE_X11)
    extern Bool WaitForNotify(Display  *d,  XEvent  *e,  char *arg);
    static int gl_width=300;
    static int gl_height=300;
#elif defined(HAVE_WIN32)
#elif defined(HAVE_NEXT)
    static int gl_width=300;
    static int gl_height=300;
#endif

#if defined(HAVE_X11)
    static int attributeList[] = {
        GLX_RGBA,
        GLX_DOUBLEBUFFER,
        None
    };
    Bool WaitForNotify(Display  *d,  XEvent  *e,  char *arg) {
        return  (e->type  ==  MapNotify) && (e->xmap.window == (Window)arg);
    }
#elif defined(HAVE_WIN32)
#elif defined(HAVE_NEXT)
#endif

int main(int argc, char **argv) {
    GLclampf c[4];
    #if defined(HAVE_X11)
        Display *dpy;
        XVisualInfo *vi;
        Colormap cmap;
        XSetWindowAttributes swa;
        Window win;
        GLXContext ctx;
        XEvent event;
    #elif defined(HAVE_WIN32)
    #elif defined(HAVE_NEXT)
        OSMesaContext ctx;
        unsigned char *buffer;
        NSWindow *myWindow;
        NSView *myView;
        NSMenu *myMenu;
        NSBitmapImageRep *bitmap;
        char name[50];
        NSRect GR;
    #endif

    #if defined(HAVE_X11)
        /* get a connection */
        dpy = XOpenDisplay(0);

        /* get an appropriate visual */
        vi = glXChooseVisual(dpy, DefaultScreen(dpy), attributeList);

        /* create a color map */
        cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen), vi->visual,
            AllocNone);

        /* create a window */
        swa.colormap = cmap;
        swa.border_pixel = 0;
        swa.event_mask = StructureNotifyMask;
        win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0, 
            (unsigned int)gl_width, (unsigned int)gl_height,
            0, vi->depth, InputOutput, vi->visual,
            CWBorderPixel|CWColormap|CWEventMask, &swa);
        XMapWindow(dpy, win);
        XIfEvent(dpy, &event, WaitForNotify, (char*)win);

    #elif defined(HAVE_WIN32)
    #elif defined(HAVE_NEXT)
     
        [[NSAutoreleasePool alloc] init];
        NSApp=[NSApplication sharedApplication];

        /* Allocate the image buffer */
        buffer = malloc( gl_width * gl_height * 4 );
   
        bitmap = [[ NSBitmapImageRep alloc] initWithBitmapDataPlanes:&buffer
                                            pixelsWide:gl_width
                                            pixelsHigh:gl_height
                                            bitsPerSample:8 samplesPerPixel:4
                                            hasAlpha:YES isPlanar:NO
                                            colorSpaceName:NSDeviceRGBColorSpace
                                           bytesPerRow:0 bitsPerPixel:0];
        GR = NSMakeRect(100, 100, gl_width, gl_height);

        myWindow = [[ NSWindow alloc] initWithContentRect:GR
                                    styleMask:NSTitledWindowMask|
                                              NSMiniaturizableWindowMask
                                    backing:NSBackingStoreBuffered defer:NO];

        sprintf(name, "VGL: `%s'", argv[0]);

        myView = [[ NSView alloc] initWithFrame:GR];

        myMenu = [[ NSMenu alloc] initWithTitle:@"VGL"];
        [myMenu addItemWithTitle:@"Quit"
                action:@selector(terminate:)
                keyEquivalent:@"q"];
        [myMenu sizeToFit];

        [myWindow setTitle:[NSString stringWithCString:name]];
        [myWindow display];
        [myWindow setContentView:myView];
        [myWindow makeKeyAndOrderFront:nil];

        [NSApp setMainMenu:myMenu];

        [myView lockFocus];
    #endif

    #if defined(HAVE_X11)
        ctx = glXCreateContext(dpy, vi, 0, GL_TRUE);
        glXMakeCurrent(dpy, win, ctx);
    #elif defined(HAVE_WIN32)
    #elif defined(HAVE_NEXT)
        ctx = OSMesaCreateContext( GL_RGBA, NULL );
        OSMesaMakeCurrent( ctx, buffer, GL_UNSIGNED_BYTE, gl_width, gl_height );
    #endif

    c[0] = (GLclampf)1.0;
    c[1] = (GLclampf)1.0;
    c[2] = (GLclampf)0.0;
    c[3] = (GLclampf)1.0;
    glClearColor( c[0], c[1], c[2], c[3] );
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    #if defined(HAVE_X11)
        glXSwapBuffers(dpy,win);
        while(1);
    #elif defined(HAVE_WIN32)
    #elif defined(HAVE_NEXT)
        [bitmap draw];
        [bitmap release];
        [myWindow flushWindow];
        [myView unlockFocus];
        free( buffer );
        OSMesaDestroyContext( ctx );
        [NSApp run];
        [NSApp release];
    #endif

    return 0;
}

