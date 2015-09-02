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
 * rcsid="$Id: vgl.c,v 1.52 2010/08/12 04:56:25 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     vgl.c
 *
 * Purpose:  Class Vgl: methods.
 *
 * Comments: A simple interface to the Ogl class, suitable for plotting
 *           simplical 2-dimensional triangular manifolds imbedded in R^3.
 *           The core Ogl routines are windowing system-independent; this 
 *           module forms an interface to the core routines to connect them
 *           to the particular window system.  The core routines are currently
 *           written in OpenGL, but could easily be replaced by any other 
 *           high-level graphics language that is connectable to the window 
 *           system.
 *
 *           The X-based interface uses only the native Xlib, Xtoolkit, and
 *           the GLw widget set (not even the Athena widgets).
 *
 *           The Win32-based interface uses only low-level Win32 API calls;
 *           no special libraries are used.
 *
 *           Hooks are available for supporting a number of other
 *           window systems (OpenStep, OS/2, etc).
 *
 * Author:   Michael Holst and Randy Bank
 * ***************************************************************************
 */

#include "vgl_p.h"

#if defined(HAVE_MOTIF)
#   include "vglm_p.h"
#endif

VEMBED(rcsid="$Id: vgl.c,v 1.52 2010/08/12 04:56:25 fetk Exp $")

VPUBLIC Vgl *theeVgl;

/*
 * ***************************************************************************
 * Private routine prototypes
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Class Vgl: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_VGL)
#endif /* if !defined(VINLINE_VGL) */

/*
 * ***************************************************************************
 * Class Vgl: Non-inlineable methods
 * ***************************************************************************
 */

VPUBLIC int Vgl_capability(void)
{
#if defined(HAVE_MOTIF)
    return 1;
#else
    return 0;
#endif
}

VPUBLIC Vgl* Vgl_ctor(int mode,
    char *socktype, char *dataform, char *hostname, char *filename,
    int xsize, int ysize, int xpos, int ypos,
    int (*buildDisplayLists)(Vgl *thee))
{
    int i;
    Vgl *thee = VNULL;
    Vglcore *vcore = VNULL;

#if defined(HAVE_X11)
    char   t_argv[80];
    int    t_argc;
    String t_argv_string;
    char   *dpyName;
    String fallback_resources[] = {
        "*GLwDrawingArea.installColormap: true",
        "*GLwDrawingArea.rgba: true",
        "*GLwDrawingArea.doublebuffer: true",
        "*GLwDrawingArea.depthSize: 1",
        /* "*GLwDrawingArea.stencilSize: 1", */
        "*GLwDrawingArea.alphaSize: 0",
        VNULL
    };
#elif defined(HAVE_WIN32)
#elif defined(HAVE_NEXT)                  
#endif

    /* malloc the base structure areas */
    thee = Vmem_malloc( VNULL, 1, sizeof(Vgl) );
    thee->vcore = Vmem_malloc( VNULL, 1, sizeof(Vglcore) );
    vcore = (Vglcore*)thee->vcore;
    thee->mode = mode;
    VASSERT( (0==thee->mode) || (1==thee->mode) );
    theeVgl = thee;

    /* create anchor block (applic context) and initialize (ONCE per exec) */
#if defined(HAVE_X11)
    XtToolkitInitialize();
    thee->appCon = VNULL;
    thee->appCon = XtCreateApplicationContext();
    VASSERT( thee->appCon != VNULL );
    XtAppSetFallbackResources(thee->appCon, fallback_resources);
    t_argc = 0;
    strncpy(t_argv,"Vgl",80);
    t_argv_string = (String)t_argv;
    dpyName = getenv("DISPLAY");
    vcore->dpy = XtOpenDisplay (thee->appCon, dpyName, t_argv_string,
        t_argv_string, VNULL, 0, &t_argc, &t_argv_string);
    VASSERT( vcore->dpy != VNULL );
#elif defined(HAVE_WIN32)
    /* create the "anchor block" for this application */
    thee->appCon = GetModuleHandle(VNULL);
#elif defined(HAVE_NEXT)
#endif

    /* initialize the core variables */
    thee->douBuf    = VTRUE;  /* NT only works WITH double Buffering */
    thee->winInit   = VFALSE;
    thee->winUp     = VFALSE;
    thee->theScale  = 50;
    vcore->topLev   = VNULL;
    vcore->plot     = VNULL;
    vcore->glxCon   = VNULL;

    /* internal polygon XDR buffer */
    thee->pbuf = VNULL;

    /* display list routine and socket state strings */
    thee->buildDisplayLists = buildDisplayLists;
    strncpy(thee->socktype,socktype,80);
    strncpy(thee->dataform,dataform,80);
    strncpy(thee->hostname,hostname,80);
    strncpy(thee->filename,filename,80);
    thee->socket = -1;

    /* it is useful for I/O to have the username */
    VASSERT( Vnm_getuser(thee->username, sizeof(thee->username)) );

    /* primary state variables */
    thee->settings[VGL_LIGHT] = 1;
    thee->settings[VGL_BALL]  = 0;
    thee->settings[VGL_BBOX]  = 0;
    if (0 == thee->mode) {
        thee->settings[VGL_ORTHO] = 0;
        thee->settings[VGL_FRAME] = 0;
    } else {
        thee->settings[VGL_ORTHO] = 1;
        thee->settings[VGL_FRAME] = 1;
    }
    if ( !strncmp(thee->dataform,"ASC",80) ) {
        thee->settings[VGL_XDR] = 0;
    } else if ( !strncmp(thee->dataform,"XDR",80) ) {
        thee->settings[VGL_XDR] = 1;
    } else { VJMPERR1(0); }

    /* display list settings */
    for (i=0; i<10; i++) {
        thee->list[i] = 1;
    }

    /* application title */
    if ( !strncmp(thee->socktype,"NONE",80) ) {
        sprintf(thee->id,"%s CLOSED",thee->dataform);
    } else if ( !strncmp(thee->socktype,"FILE",80) ) {
        sprintf(thee->id,"%s File=%s",thee->dataform,thee->filename);
    } else if ( !strncmp(thee->socktype,"UNIX",80) ) {
        sprintf(thee->id,"%s UNIX socket=/tmp/%s-%s",
            thee->dataform,thee->filename,thee->username);
        thee->socket = atoi(thee->filename);
    } else if ( !strncmp(thee->socktype,"INET",80) ) {
        sprintf(thee->id,"%s INET socket=%s+%d",
            thee->dataform,thee->filename,VPORTNUMBER);
        thee->socket = atoi(thee->filename);
    } else { VJMPERR1(0); }

    /* try to open the (initial) input [file/buff/unix/inet] device */
    if ( !strncmp(thee->socktype,"NONE",80) ) {
        thee->sock = VNULL;
    } else {
        thee->sock = Vio_ctor(thee->socktype,thee->dataform,
                         thee->hostname,thee->filename,"r");
        VJMPERR1( VNULL != thee->sock );
    }

    /* realize widget hierarchy */
    Vgl_open(thee, xsize, ysize, xpos, ypos);

    /* setup the OpenGL device and start the event loop */
    Vgl_makeCurrent(thee);
    thee->ogl = Ogl_ctor(thee->settings[VGL_FRAME],thee->settings[VGL_ORTHO]);

    /* finally enter the event loop */
    Vgl_eventLoop(thee);

    /* normal return */
    return thee;

  VERROR1:
    /* error return */
    fprintf(stderr,"Vgl_ctor: Problem opening file: %s\n", thee->filename);
    return VNULL;
}

VPUBLIC void Vgl_dtor(Vgl **thee)
{
    Vglcore *vcore = (Vglcore*)(*thee)->vcore;

    if ((*thee) != VNULL) {

        Ogl_dtor( (Ogl**)&((*thee)->ogl) );

#if defined(HAVE_X11)
#   if 0
        glXDestroyContext( vcore->dpy, vcore->glxCon );
        XtDestroyWidget( vcore->topLev );
        XtDestroyApplicationContext( thee->appCon );
#   endif
    if ( (*thee)->mode == 1 ) {
#if defined(HAVE_MOTIF)
        XmFontListEntryFree( &(vcore->theFontEntry) );
#endif
    }
        
#elif defined(HAVE_WIN32)
        VASSERT( DestroyWindow( vcore->topLev) );
        ExitProcess(0);
#elif defined(HAVE_NEXT)
        [vcore->plot release];
        [vcore->topLev flushWindow];
        [vcore->theViu unlockFocus];
        Vmem_free( VNULL, 1, (*thee)->plotWidth * (*thee)->plotHeight*4,
            (void**)(vcore->buf) );
        OSMesaDestroyContext( vcore->glxCon );
        [NSApp run];
        [NSApp release];
#endif

        Vio_dtor( (Vio**)&((*thee)->sock) );
        Vio_dtor( (Vio**)&((*thee)->pbuf) );

        Vmem_free( VNULL, 1, sizeof(Vglcore), (void**)&((*thee)->vcore) );
        Vmem_free( VNULL, 1, sizeof(Vgl), (void**)thee );
    }
}

VPUBLIC void Vgl_unmakeWidgets(Vgl *thee)
{
#if defined(HAVE_X11)
    Vglcore *vcore = thee->vcore;
    int i;

    if (1 == thee->mode) {
#if defined(HAVE_MOTIF)
        XmFontListFree(vcore->theFont);
#endif
    }

    /* destroy ONLY mainForm (all children are recursively destroyed) */
    if (vcore->mainForm != VNULL) {
        XtDestroyWidget(vcore->mainForm);
    }
    vcore->mainForm     = VNULL;
    vcore->plot         = VNULL;
    vcore->psgenMenu    = VNULL;
    vcore->resetMenu    = VNULL;
    vcore->socketMenu   = VNULL;
    vcore->settingsMenu = VNULL;
    vcore->listMenu     = VNULL;
    vcore->fileSelect   = VNULL;
    for (i=0; i<NUM_BUTTONS; i++) {
        vcore->button[i] = VNULL;
    }
#endif
}

VPUBLIC void Vgl_makeWidgets(Vgl *thee)
{
#if defined(HAVE_X11)
    Vglcore *vcore = thee->vcore;
    EventMask eventList0, eventList1, eventList2;

#if defined(HAVE_MOTIF)
    int i, counter;
    const String buttonLabel[NUM_BUTTONS] = {
        "socket",
        "settings",
        "lists",
        "gl->file",
        "file->gl",
        "reset",
        "quit"
    };
#endif

    /* main event lists */
    eventList0 = StructureNotifyMask;
    eventList1 = ExposureMask | KeyPressMask
               | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask;
    eventList2 = ButtonPressMask;
    
#if defined(HAVE_MOTIF)
    if (0 == thee->mode) {
#endif
        /* Create the FORM for everything. */
        vcore->mainForm = XtVaCreateManagedWidget("mainForm",
            formWidgetClass, vcore->topLev, 
            XtNwidth, thee->mainFormWidth,
            XtNheight, thee->mainFormHeight,
            XtNborderWidth, thee->defaultBorder,
            XtNdefaultDistance, thee->defaultSep,
            XtNforeground, WhitePixelOfScreen(vcore->scr),
            XtNbackground, vcore->backgrnd,
            VNULL);
        XtAddEventHandler(vcore->mainForm, eventList0, (int) 0,
            (XtEventHandler) Vgl_handler, (VPTR) thee);

        /* Create the plot BOX for graphics. */
        vcore->plot = XtVaCreateManagedWidget("plot", 
            glwDrawingAreaWidgetClass, vcore->mainForm,
            XtNwidth, thee->plotWidth,
            XtNheight, thee->plotHeight,
            XtNborderWidth, thee->defaultBorder,
            XtNdefaultDistance, thee->defaultSep,
            XtNforeground, BlackPixelOfScreen(vcore->scr),
            XtNbackground, WhitePixelOfScreen(vcore->scr),
            XtNborderColor, vcore->backgrnd,
            VNULL);
        XtAddEventHandler(vcore->plot, eventList1, (int) 0,
            (XtEventHandler) Vgl_handler, (VPTR) thee);

#if defined(HAVE_MOTIF)
    } else {
        /* Create the FORM for everything. */
        vcore->mainForm = XtVaCreateManagedWidget("mainForm", 
            xmFormWidgetClass, vcore->topLev,
            XmNwidth, thee->mainFormWidth,
            XmNheight, thee->mainFormHeight,
            XmNborderWidth, thee->defaultBorder,
            XmNforeground, WhitePixelOfScreen(vcore->scr),
            XmNbackground, vcore->backgrnd,
            XmNtraversalOn, False,
            VNULL);
        XtAddEventHandler(vcore->mainForm, eventList0, (int) 0,
            (XtEventHandler) Vgl_handler, (VPTR) thee);

        /* Create the plot BOX for graphics. */
        vcore->plot = XtVaCreateManagedWidget("plot", 
            glwDrawingAreaWidgetClass, vcore->mainForm,
            XmNwidth, thee->plotWidth,
            XmNheight, thee->plotHeight,
            XmNforeground, BlackPixelOfScreen(vcore->scr),
            XmNbackground, WhitePixelOfScreen(vcore->scr),
            XmNborderColor, vcore->backgrnd,
            XmNtopAttachment, XmATTACH_FORM,
            XmNtopOffset, thee->defaultSep,
            XmNleftAttachment, XmATTACH_FORM,
            XmNleftOffset, thee->defaultSep,
            XmNrightAttachment, XmATTACH_FORM,
            XmNrightOffset, thee->defaultSep,
            XmNtraversalOn, False,
            VNULL);
        XtAddEventHandler(vcore->plot, eventList1, (int) 0,
            (XtEventHandler) Vgl_handler, (VPTR) thee);

        /* buttons */
        counter = 0;
        for (i=0; i<NUM_BUTTONS; i++) {

            vcore->button[i] = XtVaCreateManagedWidget(
                buttonLabel[i], (i < 6)
                    ? xmDrawnButtonWidgetClass : xmPushButtonWidgetClass,
                vcore->mainForm,
                XmNwidth,thee->ButtonWidth,
                XmNheight,thee->ButtonHeight,
                XmNfontList, vcore->theFont,
                XmNtopAttachment, XmATTACH_WIDGET,
                XmNtopWidget, vcore->plot,
                XmNtopOffset, thee->ButtonVertSep,
                XmNleftAttachment,
                    (counter==0) ? XmATTACH_FORM: XmATTACH_WIDGET,
                XmNleftWidget,
                    (counter==0) ? vcore->mainForm : vcore->button[i-1],
                XmNleftOffset, thee->ButtonHorizSep,
                XmNtraversalOn, False,
                XmNhighlightOnEnter, True,
                XmNshadowType,XmSHADOW_OUT,
                XmNlabelString,VNULL,
                VNULL);
            XmChangeColor(vcore->button[i], vcore->buttonBackgrnd);

            if (i == VGL_LISTS)    Vgl_buildListMenu(thee);
            if (i == VGL_SOCKET)   Vgl_buildSocketMenu(thee);
            if (i == VGL_GL2FILE)  Vgl_buildPsgenMenu(thee);
            if (i == VGL_RESET)    Vgl_buildResetMenu(thee);
            if (i == VGL_SETTINGS) Vgl_buildSettingsMenu(thee);

            XtManageChild(vcore->button[i]);
            XtAddEventHandler(vcore->button[i], eventList2, (int) 0,
                (XtEventHandler) Vgl_handler, (VPTR) thee);
            counter++;
        }

    }
#endif
#endif
}

VPUBLIC void Vgl_object(Vgl *thee,
    int itype, int np, float x[], float y[], float z[],
    int icolor, float color[], float r, char text[])
{
    int j;
    float c[4], vx[100][3];

    /* make sure have enough local storage to handle number of vertices */
    VASSERT( np <= 100 );

    /* grab and pack vertices */
    for (j=0; j<np; j++) {
        vx[j][0] = x[j];
        vx[j][1] = y[j];
        vx[j][2] = z[j];
    }

    /* map color integer to RGB values */
    if (icolor < 0) {
        c[0] = color[0];
        c[1] = color[1];
        c[2] = color[2];
        c[3] = color[3];
    } else {
        c[0] = thee->red[   icolor ];
        c[1] = thee->green[ icolor ];
        c[2] = thee->blue[  icolor ];
        c[3] = 0.0;
    }

    /* add the object to the display list */
    Ogl_addListObject( thee->ogl, itype, np, vx, c, r, text);
}

VPUBLIC void Vgl_putl(Vgl *thee,
    int ncolor, float red[], float green[], float blue[])
{
    int i;

    if (ncolor >= 0) {
        VASSERT( ncolor <= 256 );
        thee->ncolor = ncolor;
        for (i=0; i<thee->ncolor; i++) {
            thee->red[i]   = red[i];
            thee->green[i] = green[i];
            thee->blue[i]  = blue[i];
        }
        Ogl_initBegin(thee->ogl);
    } else {
        Ogl_initEnd(thee->ogl);
        Vgl_redraw(thee);
    }
}

VPUBLIC void Vgl_list(Vgl *thee, int dlist, int show)
{
    if (dlist >= 0) {
        Ogl_beginList(thee->ogl, dlist, show);
    } else {
        Ogl_endList(thee->ogl);
    }
}

VPUBLIC void Vgl_line(Vgl *thee,
    float x[], float y[], float z[], int np, int icolor, float color[])
{
    int itype = 0;
    Vgl_object(thee,itype,np,x,y,z,icolor,color,0.,VNULL);
}

VPUBLIC void Vgl_fill(Vgl *thee,
    float x[], float y[], float z[], int np, int icolor, float color[])
{
    int itype = 1;
    Vgl_object(thee,itype,np,x,y,z,icolor,color,0.,VNULL);
}

VPUBLIC void Vgl_text(Vgl *thee,
    float x[], float y[], float z[], char line[], int icolor, float color[])
{
    int itype = 3;
    int np = 1;
    Vgl_object(thee,itype,np,x,y,z,icolor,color,0.,line);
}

VPUBLIC void Vgl_pont(Vgl *thee,
    float x[], float y[], float z[], int np, int icolor, float color[],
    int ptype, float radius)
{
    int itype;
    VASSERT( (0<=ptype) && (ptype<=2) );
    if (ptype == 0) {
        itype = 4;
    } else if (ptype == 1) {
        itype = 5;
    } else if (ptype == 2) {
        itype = 6;
    } else { VASSERT(0); }
    Vgl_object(thee,itype,np,x,y,z,icolor,color,radius,VNULL);
}

VPUBLIC void Vgl_quit(Vgl *thee)
{
    thee->winUp  = VFALSE;
}

VPUBLIC void Vgl_swapBuffers(Vgl *thee)
{
    Vglcore *vcore = (Vglcore*)thee->vcore;

    if (thee->douBuf) {
#if defined(HAVE_X11)
        GLwDrawingAreaSwapBuffers(vcore->plot);
#elif defined(HAVE_WIN32)
        SwapBuffers(vcore->plot);
#elif defined(HAVE_NEXT)         
        [vcore->plot draw];
#endif
    } else {
#if defined(HAVE_X11)
#elif defined(HAVE_WIN32)
#elif defined(HAVE_NEXT)
        [vcore->plot draw];
#endif
    }
}

VPUBLIC void Vgl_makeCurrent(Vgl *thee)
{
    Vglcore *vcore = (Vglcore*)thee->vcore;

#if defined(HAVE_X11)
    GLwDrawingAreaMakeCurrent(vcore->plot, vcore->glxCon);
#elif defined(HAVE_WIN32)
    VASSERT( wglMakeCurrent(vcore->plot, vcore->glxCon) );
#elif defined(HAVE_NEXT)                                     
    OSMesaMakeCurrent( vcore->glxCon, vcore->buf, GL_UNSIGNED_BYTE,
        thee->plotWidth, thee->plotHeight );
#endif
}

VPUBLIC void Vgl_eventLoop(Vgl *thee)
{
    unsigned long rc;

#if defined(HAVE_X11)
    XEvent event;
#elif defined(HAVE_WIN32)
    MSG Message;
    Vglcore *vcore = (Vglcore*)thee->vcore;
#elif defined(HAVE_NEXT)                                     
#endif

#if defined(HAVE_X11)
    rc = XtAppAddTimeOut(thee->appCon,
        1000, Vgl_getPolys, (VPTR)thee);
#elif defined(HAVE_WIN32)
    rc = SetTimer(vcore->topLev, 1, 1000, VNULL);
#elif defined(HAVE_NEXT)                                     
#endif
    VASSERT(rc != 0);

    while (thee->winUp) {
#if defined(HAVE_X11)
        while (thee->winUp && XtAppPending(thee->appCon)) {
            XtAppNextEvent(thee->appCon,&event);
            XtDispatchEvent(&event);
        }
#elif defined(HAVE_WIN32)
        while (thee->winUp &&
          PeekMessage(&Message, VNULL, 0, 0, PM_NOREMOVE)==TRUE) {
            if (GetMessage(&Message, VNULL, 0, 0) ) {
                TranslateMessage(&Message);
                DispatchMessage(&Message);
            }
        }
#elif defined(HAVE_NEXT)
        [NSApp run];
#endif
    }
}

VPUBLIC void Vgl_spin(void *wId, unsigned long *tId)
{
    Vgl *thee = (Vgl*)wId;
#if defined(HAVE_X11)
#elif defined(HAVE_WIN32)
    Vglcore *vcore = (Vglcore*)thee->vcore;
#elif defined(HAVE_NEXT)
#endif

    /* only spin if rotation was large enough */
    if ( Ogl_spin( thee->ogl ) ) {

        /* redraw the rotated picture and swap buffers */
        Ogl_display( thee->ogl );
        Vgl_swapBuffers( thee );

        /* re-register us as a timeout */
#if defined(HAVE_X11)
        thee->spinId = XtAppAddTimeOut(thee->appCon,
            1, Vgl_spin, (VPTR)thee);
#elif defined(HAVE_WIN32)
        thee->spinId = SetTimer(vcore->topLev, 2, 1, VNULL);
#elif defined(HAVE_NEXT)
#endif
    } else {
        /* de-register us as a timeout */
        if (thee->spinId != 0) {
#if defined(HAVE_X11)
            XtRemoveTimeOut(thee->spinId);
#elif defined(HAVE_WIN32)
            KillTimer(vcore->topLev, thee->spinId);
#elif defined(HAVE_NEXT)
#endif
            thee->spinId = 0;
        }
        thee->spinning = 0;
    }
}

VPUBLIC void Vgl_getPolys(void *wId, unsigned long *tId)
{
    Vgl *thee = (Vgl*)wId;
#if defined(HAVE_X11)
#elif defined(HAVE_WIN32)
    Vglcore *vcore = (Vglcore*)thee->vcore;
#elif defined(HAVE_NEXT)
#endif

    unsigned long rc;

    /* get polygons and rebuild/render display lists if polys are waiting */
    if ( thee->buildDisplayLists(thee) ) {
        if (1 == thee->mode) {
            Vgl_buildListMenu(thee);
        }
    }

    /* always re-register us as a timeout */
#if defined(HAVE_X11)
    rc = XtAppAddTimeOut(thee->appCon,
        10, Vgl_getPolys, (VPTR)thee);
#elif defined(HAVE_WIN32)
    rc = SetTimer(vcore->topLev, 1, 10, VNULL);
#elif defined(HAVE_NEXT)
#endif
    VASSERT(rc != 0);
}

VPUBLIC void Vgl_redraw(Vgl *thee)
{
    Ogl_reshape(thee->ogl,thee->plotWidth,thee->plotHeight);
    Ogl_display(thee->ogl);
    Vgl_swapBuffers(thee);
}

VPUBLIC VCBPROC Vgl_listCallback(VWIDGET w,
    VPTR cli, VPTR cal)
{
    int which = (int)cli;

    theeVgl->list[which] = Ogl_listModeOnOff(theeVgl->ogl,which);
    Vgl_redraw(theeVgl);
    return 0;
}

VPUBLIC VCBPROC Vgl_settingsCallback(VWIDGET w,
    VPTR cli, VPTR cal)
{
    Vglcore *vcore = theeVgl->vcore;
    int which = (int)cli;
    char title[80];

    if (which == VGL_LIGHT) {
        theeVgl->settings[VGL_LIGHT] = Ogl_lightModeOnOff(theeVgl->ogl);
    } else if (which == VGL_ORTHO) {
        theeVgl->settings[VGL_ORTHO] = Ogl_orthoModeOnOff(theeVgl->ogl);
    } else if (which == VGL_FRAME) {
#if defined(HAVE_X11)
        theeVgl->settings[VGL_FRAME] = Ogl_frameModeOnOff(theeVgl->ogl);
        theeVgl->mode = theeVgl->settings[VGL_FRAME];
        Vgl_unmakeWidgets(theeVgl);
        Vgl_makeGeom(theeVgl,0);
        XtResizeWidget(vcore->topLev, theeVgl->mainFormWidth,
            theeVgl->mainFormHeight, theeVgl->defaultBorder);
        Vgl_makeWidgets(theeVgl);
        Vgl_makeCurrent(theeVgl);
#endif
    } else if (which == VGL_BALL) {
        theeVgl->settings[VGL_BALL]  = Ogl_ballModeOnOff(theeVgl->ogl);
    } else if (which == VGL_BBOX) {
        theeVgl->settings[VGL_BBOX]  = Ogl_bboxModeOnOff(theeVgl->ogl);
    } else if (which == VGL_XDR) {

        /* toggle the dataform */
        if ( !strncmp(theeVgl->dataform,"ASC",80) ) {
            theeVgl->settings[VGL_XDR] = 1;
            sprintf(theeVgl->dataform,"XDR");
        } else if ( !strncmp(theeVgl->dataform,"XDR",80) ) {
            theeVgl->settings[VGL_XDR] = 0;
            sprintf(theeVgl->dataform,"ASC");
        } else { VASSERT( 0 ); }

        /* make a new window title */
        if ( !strncmp(theeVgl->socktype,"NONE",80) ) {
            sprintf(theeVgl->id,"%s CLOSED",theeVgl->dataform);
            VASSERT( theeVgl->socket < 0 );
        } else if ( !strncmp(theeVgl->socktype,"FILE",80) ) {
            sprintf(theeVgl->id,"%s File=%s",
                theeVgl->dataform,theeVgl->filename);
            VASSERT( theeVgl->socket < 0 );
        } else if ( !strncmp(theeVgl->socktype,"UNIX",80) ) {
            sprintf(theeVgl->id,"%s UNIX socket=/tmp/%s-%s",
                theeVgl->dataform,theeVgl->filename,theeVgl->username);
        } else if ( !strncmp(theeVgl->socktype,"INET",80) ) {
            sprintf(theeVgl->id,"%s INET socket=%s+%d",
                theeVgl->dataform,theeVgl->filename,VPORTNUMBER);
        } else { VASSERT( 0 ); }

        /* close and re-open the socket */
        if (theeVgl->socket >= 0) {
            Vio_dtor( &(theeVgl->sock) );
            if (VNULL==(theeVgl->sock=Vio_ctor(theeVgl->socktype,
              theeVgl->dataform,theeVgl->hostname,theeVgl->filename,"r"))) {
                fprintf(stderr,
                    "Vgl_fileReadCallback: Problem opening socket: %s\n",
                    theeVgl->filename);
            }
        }

        /* update the window title information */
        sprintf(title,"Socket Graphics <%s>",theeVgl->id);
#if defined(HAVE_X11)
        XtVaSetValues(vcore->topLev,XtNtitle,title,VNULL);
#endif

    } else { VASSERT( 0 ); }

    Vgl_redraw(theeVgl);

    return 0;
}

VPUBLIC VCBPROC Vgl_resetCallback(VWIDGET w,
    VPTR cli, VPTR cal)
{
    int which = (int)cli;

    if (which == 0) {
        fprintf(stderr,
            "Vgl_resetCallback: resetting object orientation and position.\n");
        Ogl_resetPos( theeVgl->ogl );
        Vgl_redraw(theeVgl);
    } else if (which == 1) {
        fprintf(stderr,
            "Vgl_resetCallback: releasing object and associated memory.\n");
        Ogl_resetPos( theeVgl->ogl );
        Ogl_initBegin(theeVgl->ogl);
        Ogl_initEnd(theeVgl->ogl);
        Vgl_buildListMenu(theeVgl);
        Vgl_redraw(theeVgl);
    } else { VASSERT( 0 ); }

    return 0;
}

VPUBLIC VCBPROC Vgl_fileWriteCallback(VWIDGET w,
    VPTR cli, VPTR cal)
{
    int which = (int)cli;

   /*
    * Oglps options:
    *
    *    outLine   ==> 0=use filled triangles
    *                  1=use filled triangles and then outline them
    * 
    *    inColor   ==> 0=grayscale
    *                  1=color
    * 
    *    doCulling ==> 0=don't cull (render everything)
    *                  1=cull (remove backface triangles before
    *                    rendering)
    */
    int outline, inColor, doCulling;

    if (which == 0) {
        fprintf(stderr,
            "Vgl_fileWriteCallback: PS generation started (no edges).\n");
        Oglps_begin();
        Ogl_reshape(theeVgl->ogl,theeVgl->plotWidth,theeVgl->plotHeight);
        Ogl_display(theeVgl->ogl);
        outline   = 0;
        inColor   = 1;
        doCulling = 0;
        Oglps_end(outline,inColor,doCulling);
        fprintf(stderr,
            "Vgl_fileWriteCallback: PS generation ended (no edges).\n");
    } else if (which == 1) {
        fprintf(stderr,
            "Vgl_fileWriteCallback: PS generation started (edges).\n");
        Oglps_begin();
        Ogl_reshape(theeVgl->ogl,theeVgl->plotWidth,theeVgl->plotHeight);
        Ogl_display(theeVgl->ogl);
        outline   = 1;
        inColor   = 1;
        doCulling = 0;
        Oglps_end(outline,inColor,doCulling);
        fprintf(stderr,
            "Vgl_fileWriteCallback: PS generation ended (edges).\n");
    } else if (which == 2) {
        fprintf(stderr,
            "Vgl_fileWriteCallback: XPM generation not yet implemented.\n");
    } else if (which == 3) {
        fprintf(stderr,
            "Vgl_fileWriteCallback: BH generation not yet implemented.\n");
    } else { VASSERT( 0 ); }

    return 0;
}

VPUBLIC VCBPROC Vgl_socketCallBack(VWIDGET w,
    VPTR cli, VPTR cal)
{
    Vglcore *vcore = theeVgl->vcore;
    int which = (int)cli;
    char title[80];

    /* closed socket */
    if (which == 0) {
        sprintf(theeVgl->socktype,"NONE");
        theeVgl->socket = -1;
        sprintf(theeVgl->filename,"%d",theeVgl->socket);
        sprintf(theeVgl->id,"%s CLOSED", theeVgl->dataform);

    /* UNIX Domain socket */
    } else if ((1<=which) && (which<=4)) {
        sprintf(theeVgl->socktype,"UNIX");
        theeVgl->socket = which-1;
        sprintf(theeVgl->filename,"%d",theeVgl->socket);
        sprintf(theeVgl->id,"%s UNIX socket=/tmp/%s-%s",
            theeVgl->dataform,theeVgl->filename,theeVgl->username);

    /* INET TCP/IP socket */
    } else if ((5<=which) && (which<=8)) {
        sprintf(theeVgl->socktype,"INET");
        theeVgl->socket = which-5;
        sprintf(theeVgl->filename,"%d",theeVgl->socket);
        sprintf(theeVgl->id,"%s INET socket=%s+%d",
            theeVgl->dataform,theeVgl->filename,VPORTNUMBER);

    } else { VASSERT( 0 ); }

    /* actually open the socket */
    Vio_dtor( &(theeVgl->sock) );
    if (theeVgl->socket >= 0) {
        if (VNULL==(theeVgl->sock=Vio_ctor(theeVgl->socktype,
          theeVgl->dataform,theeVgl->hostname,theeVgl->filename,"r"))) {
            fprintf(stderr,
                "Vgl_fileReadCallback: Problem opening socket: %s\n",
                theeVgl->filename);
        }
    }

    /* update the window title information */
    sprintf(title,"Socket Graphics <%s>",theeVgl->id);
#if defined(HAVE_X11)
    XtVaSetValues(vcore->topLev,XtNtitle,title,VNULL);
#endif

    return 0;
}

#if defined(HAVE_X11)
VPUBLIC VCBPROC Vgl_fileReadCallback(VWIDGET w,
    VPTR cli, VPTR cal)
{
    if (1 == theeVgl->mode) {
#if defined(HAVE_MOTIF)
        return Vgl_M_fileReadCallback(w, cli, cal);
#else
        return 0;
#endif
    } else {
        return 0;
    }
}

/* ************************************************* */
/* Vgl_makeColors was yanked from Randy's <xgraph.c> */
/* ************************************************* */
VPUBLIC void Vgl_makeColors(Vgl *thee)
{
    Vglcore *vcore = thee->vcore;
    XColor color;
    int    Status1, Status2;
#if defined(HAVE_MOTIF)
    Pixel  topShadow, bottomShadow, selectit;
#endif

#if 1
    String bgclr="grey80";
    String btnbg="gray53";
#endif
#if 0
    String bgclr="dodgerblue4";
    String btnbg="dodgerblue4";
#endif

    vcore->foregrnd = WhitePixelOfScreen(vcore->scr);
    vcore->backgrnd = BlackPixelOfScreen(vcore->scr);

    vcore->buttonBackgrnd = BlackPixelOfScreen(vcore->scr);
    Status1 = XParseColor(vcore->dpy, 
        DefaultColormapOfScreen(vcore->scr), bgclr, &color);
    if (Status1 != 0) {
        Status2 = XAllocColor(vcore->dpy, 
            DefaultColormapOfScreen(vcore->scr),&color); 
        if (Status2 != 0) {
            vcore->backgrnd = color.pixel;
        }
    }

    Status1 = XParseColor(vcore->dpy, 
        DefaultColormapOfScreen(vcore->scr), btnbg, &color);
    if (Status1 != 0) {
        Status2 = XAllocColor(vcore->dpy, 
            DefaultColormapOfScreen(vcore->scr),&color); 
        if (Status2 != 0) {
            vcore->buttonBackgrnd = color.pixel;
        }
    }
#if defined(HAVE_MOTIF)
    XmGetColors (vcore->scr, 
        DefaultColormapOfScreen(vcore->scr),
        vcore->backgrnd, &vcore->foregrnd, 
        &topShadow, &bottomShadow, &selectit);
    XmGetColors (vcore->scr, 
        DefaultColormapOfScreen(vcore->scr),
        vcore->buttonBackgrnd, &vcore->buttonForegrnd, 
        &topShadow, &bottomShadow, &selectit);
#endif
}

/* *********************************************** */
/* Vgl_makeGeom was yanked from Randy's <xgraph.c> */
/* *********************************************** */
VPUBLIC void Vgl_makeGeom(Vgl *thee, int key)
{
    Vglcore *vcore = thee->vcore;
    char      newfont[100];
    char      *fontname;
    Dimension winX, winY;

    if (0 == thee->mode) {

        if (key == 0) {
            winX = XWidthOfScreen(vcore->scr);
            winY = XHeightOfScreen(vcore->scr);
            thee->minWidth  = winX / 10;
            thee->minHeight = winY / 10;
            thee->maxWidth  = winX - 50;
            thee->maxHeight = winY - 50;
            /* assume [mainFormWidth,mainFormHeight] come in as set */
        } else {
            XtVaGetValues(vcore->topLev,
                XtNwidth, &winX, XtNheight, &winY, VNULL);
            thee->defaultBorder = 1;
            thee->defaultSep    = 1;
            thee->mainFormWidth  = winX - 4 * thee->defaultBorder;
            thee->mainFormHeight = winY - 4 * thee->defaultBorder;
        }
        if (thee->mainFormWidth  < thee->minWidth) {
            thee->mainFormWidth  = thee->minWidth;
        }
        if (thee->mainFormHeight < thee->minHeight) {
            thee->mainFormHeight = thee->minHeight;
        }
        if (thee->mainFormWidth  > thee->maxWidth) {
            thee->mainFormWidth  = thee->maxWidth;
        }
        if (thee->mainFormHeight > thee->maxHeight) {
            thee->mainFormHeight = thee->maxHeight;
        }

    } else {
        if (key == 0) {
            winX = XWidthOfScreen(vcore->scr);
            winY = XHeightOfScreen(vcore->scr);
            if (15*winX < 21*winY) {
                thee->minWidth  = winX * 1/ 10;
                thee->minHeight = (winX * 15) / 21;
            } else {
                thee->minHeight = winY * 1 / 10;
                thee->minWidth  = (winY * 21) / 15;
            }
            winX = thee->mainFormWidth;
            winY = thee->mainFormHeight;
        } else {
            XtVaGetValues(vcore->topLev,
                XtNwidth, &winX, XtNheight, &winY, VNULL);
        }
        if (winX < thee->minWidth)  winX = thee->minWidth;
        if (winY < thee->minHeight) winY = thee->minHeight;
        if (15*winX  < 21*winY) {
            winY = (winX * 15) / 21;
        } else {
            winX = (winY * 21) / 15;
        }
        thee->mainFormWidth  = winX;
        thee->mainFormHeight = winY;
    }

    /* plot, border, and separator sizes */
    thee->defaultBorder = 1;
    thee->defaultSep = thee->mainFormWidth / 200;     
    if (thee->defaultSep <= 0) {
        thee->defaultSep = 1;      
        thee->defaultBorder = 1;
    }
    thee->plotWidth  = thee->mainFormWidth
                     - 2 * thee->defaultBorder
                     - 2 * thee->defaultSep;
    if (0 == thee->mode) {
        thee->plotHeight = thee->mainFormHeight
                         - 2 * thee->defaultBorder
                         - 2 * thee->defaultSep;
    } else {
        thee->plotHeight = (2 * thee->plotWidth) / 3;
    }
    
    /* button and button separator sizes */
    thee->ButtonWidth   = thee->mainFormWidth / (NUM_BUTTONS + 1);
    thee->ButtonHeight  = thee->ButtonWidth / 3;
    thee->ButtonVertSep = ( thee->mainFormHeight - thee->plotHeight 
                         - 4 * thee->defaultBorder
                         - 1 * thee->ButtonHeight
                         - 1 * thee->defaultSep ) / 2;
    if (thee->ButtonVertSep <= 0 ) {
        thee->ButtonVertSep = 1;
    }
    thee->ButtonHorizSep  = (thee->mainFormWidth
                          - NUM_BUTTONS * thee->ButtonWidth)
                          / (NUM_BUTTONS + 1);
    if (thee->ButtonHorizSep <= 0 ) {
        thee->ButtonHorizSep = 1;
    }

    /* try scalable font */
    vcore->fontHeight = (thee->ButtonHeight * 50) / 100;
    if (vcore->fontHeight > thee->ButtonHeight - 4) 
    vcore->fontHeight = thee->ButtonHeight - 4;
    if (vcore->fontHeight < 5) vcore->fontHeight = 5;     
    fontname = "-*-courier-medium-r-*-*-00-*-*-*-*-*-*-*";  
    strcpy(newfont,fontname);
    newfont[24] = 48 + vcore->fontHeight / 10;
    newfont[25] = 48 + vcore->fontHeight - (vcore->fontHeight / 10) * 10;
#if defined(HAVE_MOTIF)
    vcore->theFontEntry = XmFontListEntryLoad(vcore->dpy, newfont,
        XmFONT_IS_FONT, "myTag");
    vcore->theFont = XmFontListAppendEntry(VNULL, vcore->theFontEntry);
#endif

}
#endif /* if defined(HAVE_X11) */

VPUBLIC void Vgl_open(Vgl *thee, int xsize, int ysize, int xpos, int ypos)
{
    Vglcore *vcore = (Vglcore*)thee->vcore;

#if defined(HAVE_X11)
    char        title[80];

    /* setup the application context if needed */
    if (!thee->winInit) {
        thee->winInit = VTRUE;
    }

    /* if not done already, create the widget structure and realize */
    if (!thee->winUp) {

        /* initial geometry */
        thee->mainFormWidth  = xsize;
        thee->mainFormHeight = ysize;
        thee->left           = xpos;
        thee->top            = ypos;

        /* Create the top level widget */
        sprintf(title,"Socket Graphics <%s>",thee->id);
        vcore->topLev = XtVaAppCreateShell(
            title, title, topLevelShellWidgetClass, 
            vcore->dpy, XtNx, thee->left, XtNy, thee->top, VNULL);

        /* store the screen away */
        vcore->scr = XtScreen(vcore->topLev);
        VASSERT( vcore->scr != VNULL );

        /* make the colors */
        Vgl_makeColors(thee);

        /* figure out the geometry */
        Vgl_makeGeom(thee, 0);

        /* make the widgets */
        Vgl_makeWidgets(thee);

        /* realize the Widget */
        XtRealizeWidget(vcore->topLev);

 /*  hack to fix screen blanking problem using kde window manager (7/1/03) */

        Vgl_unmakeWidgets(thee);
        Vgl_makeGeom(thee, 1);
        Vgl_makeWidgets(thee);

 /*  hack to fix screen blanking problem using kde window manager (7/1/03) */

        /* get X info and construct a Graphics ctx */
        XtVaGetValues(vcore->plot,
            GLwNrgba, &(vcore->rgbaVis),
            GLwNinstallColormap, &(vcore->cmapIns),
            GLwNvisualInfo, &(vcore->xVisInf),
            GLwNdoublebuffer, &(thee->douBuf),
            VNULL);

        /* check some things */
        VASSERT( vcore->rgbaVis );
        VASSERT( vcore->cmapIns );
        VASSERT( thee->douBuf );

        /* setup the graphics context */
        vcore->glxCon = glXCreateContext(vcore->dpy,vcore->xVisInf,0,VFALSE);
        VASSERT( vcore->glxCon != VNULL );

        /* check out the visual */
#if 0 /* defined(VDEBUG) */
        /* int xTmp; */
        glXGetConfig(vcore->dpy,vcore->xVisInf,GLX_DOUBLEBUFFER,&xTmp);
        fprintf(stderr,"Vgl_open: vi DOUBLEBUFFER flag = %d\n", xTmp);
        glXGetConfig(vcore->dpy,vcore->xVisInf,GLX_RGBA,&xTmp);
        fprintf(stderr,"Vgl_open: vi RGBA flag = %d\n", xTmp);
        xTmp = glXIsDirect(vcore->dpy, vcore->glxCon);
        fprintf(stderr,"Vgl_open: vi DIRECT flag = %d\n", xTmp);
        glXGetConfig(vcore->dpy,vcore->xVisInf,GLX_DEPTH_SIZE,&xTmp);
        fprintf(stderr,"Vgl_open: vi DEPTH size = %d\n", xTmp);
        glXGetConfig(vcore->dpy,vcore->xVisInf,GLX_STENCIL_SIZE,&xTmp);
        fprintf(stderr,"Vgl_open: vi STENCIL size = %d\n", xTmp);
        glXGetConfig(vcore->dpy,vcore->xVisInf,GLX_ALPHA_SIZE,&xTmp);
        fprintf(stderr,"Vgl_open: vi ALPHA size = %d\n", xTmp);
        glXGetConfig(vcore->dpy,vcore->xVisInf,GLX_ACCUM_RED_SIZE,&xTmp);
        fprintf(stderr,"Vgl_open: vi ACCUM_RED_SIZE = %d\n", xTmp);
        glXGetConfig(vcore->dpy,vcore->xVisInf,GLX_ACCUM_GREEN_SIZE,&xTmp);
        fprintf(stderr,"Vgl_open: vi ACCUM_GREEN_SIZE = %d\n", xTmp);
        glXGetConfig(vcore->dpy,vcore->xVisInf,GLX_ACCUM_BLUE_SIZE,&xTmp);
        fprintf(stderr,"Vgl_open: vi ACCUM_BLUE_SIZE = %d\n", xTmp);
#endif

        /* warp the pointer into the new window to get right colors */
        /*
         * XWarpPointer (XtDisplay(vcore->plot), None,
         *     XtWindow(vcore->plot), 0, 0, 0, 0, 0, 0);
         */

        /* okay, we are up! */
        thee->winUp = VTRUE;
    }

#elif defined(HAVE_WIN32)
    int xborder, yborder, ytitle, ygunk;
    WNDCLASS mglWndClass;
    RECT  WinRect;
    int iPixelFormat;
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR), /* size of this pfd       */
        1,                             /* version number         */
        PFD_DRAW_TO_WINDOW |           /* support window         */
        PFD_SUPPORT_OPENGL |           /* support OpenGL         */
        PFD_DOUBLEBUFFER,              /* double buffered        */
        PFD_TYPE_RGBA,                 /* RGBA type              */
        24,                            /* 24-bit color depth     */
        0, 0, 0, 0, 0, 0,              /* color bits ignored     */
        0,                             /* no alpha buffer        */
        0,                             /* shift bit ignored      */
        0,                             /* no accumulation buffer */
        0, 0, 0, 0,                    /* accum bits ignored     */
        32,                            /* 32-bit z-buffer    */
        0,                             /* no stencil buffer      */
        0,                             /* no auxiliary buffer    */
        PFD_MAIN_PLANE,                /* main layer             */
        0,                             /* reserved               */
        0, 0, 0                        /* layer masks ignored    */
    };

    void  *iaddr;
    char theeAddr[32];
    char title[80];

    /* turn "thee" address into a string */
    iaddr = (void*)thee;
    sprintf(theeAddr,"%p",iaddr);

    /* setup the application context if needed */
    if (!thee->winInit) {
        thee->winInit = VTRUE;

        /* register window classes and their handlers once per execution */
        mglWndClass.style         = CS_HREDRAW | CS_VREDRAW;
        mglWndClass.lpfnWndProc   = (WNDPROC)Vgl_handler;
        mglWndClass.cbClsExtra    = 0;
        mglWndClass.cbWndExtra    = 0;
        mglWndClass.hInstance     = thee->appCon;
        mglWndClass.hIcon         = LoadIcon(VNULL, IDI_APPLICATION);
        mglWndClass.hCursor       = LoadCursor(VNULL, IDC_ARROW);
        mglWndClass.hbrBackground = GetStockObject(BLACK_BRUSH);
        mglWndClass.lpszMenuName  = VNULL;
        mglWndClass.lpszClassName = (LPCSTR)theeAddr;
        VASSERT( RegisterClass(&mglWndClass) );
    }

    /* if not done already, create the window structure and realize */
    if (!thee->winUp) {
        thee->winUp = VTRUE;

        /* initial geometry */
        thee->plotWidth  = xsize;
        thee->plotHeight = ysize;
        xborder          = GetSystemMetrics(SM_CXFRAME);
        yborder          = GetSystemMetrics(SM_CYFRAME);
        ytitle           = GetSystemMetrics(SM_CYCAPTION);
        ygunk            = GetSystemMetrics(SM_CYBORDER);
        thee->left       = xpos + xborder;
        thee->top        = ypos + yborder + ytitle - ygunk;

        /* Make win large enough to hold client area */
        WinRect.left   = thee->left;
        WinRect.right  = thee->left + thee->plotWidth;
        WinRect.top    = thee->top;
        WinRect.bottom = thee->top  + thee->plotHeight;
        VASSERT( AdjustWindowRect(&WinRect, WS_OVERLAPPEDWINDOW, FALSE) );

        /* Must use WS_CLIPCHILDREN and WS_CLIPSIBLINGS styles. */
        sprintf(title,"Socket Graphics <%s>",thee->id);
        vcore->topLev = CreateWindow( (LPCSTR)theeAddr, title,
            WS_VISIBLE | WS_OVERLAPPEDWINDOW |
            WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
            WinRect.left, WinRect.top,
            WinRect.right - WinRect.left, WinRect.bottom - WinRect.top,
            VNULL, VNULL, thee->appCon, VNULL );
        VASSERT( vcore->topLev != VNULL );

        /* Get the hdc */
        vcore->plot = GetDC(vcore->topLev);
        VASSERT( vcore->plot != VNULL );

        /* pixel stuff for WinNT.. */
        /* get the device context's best-available-match pixel format */
        iPixelFormat = ChoosePixelFormat(vcore->plot, &pfd);

        /* make that the device context's current pixel format */
        VASSERT( SetPixelFormat(vcore->plot, iPixelFormat, &pfd) );

        /* create the graphics context */
        vcore->glxCon = wglCreateContext(vcore->plot);
        VASSERT( vcore->glxCon != VNULL );

        /* force the showing of the windows in the foreground */
        ShowWindow(vcore->topLev, SW_NORMAL);
        VASSERT( SetActiveWindow(vcore->topLev) );
    }
#elif defined(HAVE_NEXT)
    NSRect      GR;
    NSMenu      *myMenu;

    const char *title = "Vgl OpenGL Graphics";

    /* setup the application context if needed */
    if (!thee->winInit) {
        thee->winInit = VTRUE;
    }
     
    /* if not done already, create the widget structure and realize */
    if (!thee->winUp) {
        thee->winUp = VTRUE;

        /* initial geometry */
        thee->plotWidth  = xsize;
        thee->plotHeight = ysize;
        thee->left       = xpos;
        thee->top        = ypos;

        [[NSAutoreleasePool alloc] init];
        NSApp=[NSApplication sharedApplication];

        /* Allocate the image buffer */
        vcore->buf  = Vmem_malloc( VNULL, 1, thee->plotWidth * thee->plotHeight * 4 );

        vcore->plot = [[ NSBitmapImageRep alloc]
                               initWithBitmapDataPlanes:&(vcore->buf)
                               pixelsWide:thee->plotWidth
                               pixelsHigh:thee->plotHeight
                               bitsPerSample:8 samplesPerPixel:4
                               hasAlpha:YES isPlanar:NO
                               colorSpaceName:NSDeviceRGBColorSpace
                               bytesPerRow:0 bitsPerPixel:0];
        GR = NSMakeRect(100, 100, thee->plotWidth, thee->plotHeight);


        vcore->topLev = [[ NSWindow alloc] initWithContentRect:GR
                                    styleMask:NSTitledWindowMask|
                                              NSMiniaturizableWindowMask
                                    backing:NSBackingStoreBuffered defer:NO];

        vcore->theViu = [[ NSView alloc] initWithFrame:GR];

        myMenu = [[ NSMenu alloc] initWithTitle:@"VGL"];
        [myMenu addItemWithTitle:@"Quit"
                action:@selector(terminate:)
                keyEquivalent:@"q"];
        [myMenu sizeToFit];

        [vcore->topLev setTitle:[NSString stringWithCString:title]];
        [vcore->topLev display];
        [vcore->topLev setContentView:vcore->theViu];
        [vcore->topLev makeKeyAndOrderFront:nil];

        [NSApp setMainMenu:myMenu];

        [vcore->theViu lockFocus];

        vcore->glxCon = OSMesaCreateContext( GL_RGBA, NULL );
    }
#endif
}

#if defined(HAVE_X11)
    VPUBLIC void Vgl_handler(Widget w,
        VPTR msg, XEvent* wParam, VPTR lParam)
#elif defined(HAVE_WIN32)
    VPUBLIC WINAPI Vgl_handler(HWND w,
        UINT msg, DWORD wParam, LONG lParam)
#elif defined(HAVE_NEXT)
    VPUBLIC void Vgl_handler(NSWindow *w,
        int msg, int wParam, int lParam)
#endif
{
    int            ihandle = 0;
    static int     mouseDown = 0;
    static int     mouseMode = 0;
    static int     resizeSwitch = 0;
    Vgl            *thee;
    Vglcore        *vcore;

#if defined(HAVE_X11)
    XComposeStatus       compose;
    KeySym               keysym;
    char                 thisKey,buffer[1];
    int                  x,y,bufsize = 1;
    double               cpu = 0.0;
    unsigned long        after;
    static unsigned long before;
#elif defined(HAVE_WIN32)
    PAINTSTRUCT          paint;
    MSG                  qmsg;
    HDC                  hdc;
    int                  x,y;
    long                 keysym,thisKey;
    unsigned long        wTimerID;
    void                 *iaddr;
    char                 theeAddr[32];
    double               cpu = 0.0;
    unsigned long        after;
    static unsigned long before;
#elif defined(HAVE_NEXT)      
    static char lastKey = ' ';
    static char thisKey = ' ';
    int dummy;                
    int keysym;
#endif

    /* decode the given object address */
#if defined(HAVE_X11)
    thee = (Vgl*)msg;
#elif defined(HAVE_WIN32)
    VASSERT( GetClassName(w,theeAddr,32) );
    sscanf(theeAddr,"%p",&iaddr);
    thee = (Vgl*)iaddr;
#elif defined(HAVE_NEXT)          
#endif

    vcore = (Vglcore*)thee->vcore;

#if defined(HAVE_X11)
    /* with X, this handler is called only if needed */
    if ( 0 == thee->mode ) {
        VASSERT( (w == vcore->plot) || (w == vcore->mainForm) );
    }
    ihandle = 1;
#elif defined(HAVE_WIN32)
    /* with Win32, this handler is called other times also... */
    if (w == vcore->topLev) ihandle = 1;
#elif defined(HAVE_NEXT)          
#endif

    /* handle the single event */
    if (ihandle) {

#if defined(HAVE_X11)
        switch (wParam->type) {
#elif defined(HAVE_WIN32)
        switch (msg) {
#elif defined(HAVE_NEXT)
        switch (dummy) {
#endif

            /* Window resize */
#if defined(HAVE_X11)
            case ConfigureNotify:
                if (resizeSwitch == 0) {
                    resizeSwitch = 1;
                    thee->plotWidth  = wParam->xconfigure.width;
                    thee->plotHeight = wParam->xconfigure.height;
                    Vgl_unmakeWidgets(thee);
                    Vgl_makeGeom(thee,1);
                    XtResizeWidget(vcore->topLev, thee->mainFormWidth,
                        thee->mainFormHeight, thee->defaultBorder);
                    Vgl_makeWidgets(thee);
                    Vgl_makeCurrent(thee);
                    Vgl_redraw(thee);
                } else {
                    /* HACK to avoid cascading <ConfigureNotify> forever */
                    resizeSwitch = 0;
                }
                break;
#elif defined(HAVE_WIN32)
            case WM_SIZE:
                thee->plotWidth  = LOWORD(lParam);
                thee->plotHeight = HIWORD(lParam);
                Ogl_reshape( thee->ogl, thee->plotWidth, thee->plotHeight );
                if (!PeekMessage(&qmsg,w,WM_PAINT,WM_PAINT,PM_NOREMOVE))
                    VASSERT( InvalidateRect( w, VNULL, FALSE ) );
                return 0;
#elif defined(HAVE_NEXT)
#endif

            /* Window expose */
#if defined(HAVE_X11)
            case Expose:
                Ogl_display( thee->ogl );
                Vgl_swapBuffers( thee );
                break;
#elif defined(HAVE_WIN32)
            case WM_PAINT:
                hdc = BeginPaint(vcore->topLev, &paint);
                Ogl_display( thee->ogl );
                Vgl_swapBuffers( thee );
                EndPaint(vcore->topLev, &paint);
                return 0;
#elif defined(HAVE_NEXT)
#endif

            /* Keyboard key press in window */
#if defined(HAVE_X11)
            case KeyPress:
                XLookupString(&(wParam->xkey),buffer,bufsize,&keysym,&compose);
#elif defined(HAVE_WIN32)
            case WM_CHAR:
                keysym = wParam;
#elif defined(HAVE_NEXT)
            case 0:
#endif
                thisKey = keysym;

                if (thisKey == VKEY_Q) {
                    Vgl_quit(thee);
#if defined(HAVE_X11)
                        return;
#elif defined(HAVE_WIN32)
                        return 0;
#elif defined(HAVE_NEXT)
#endif

                } else if (thisKey == VKEY_QUE) {
                    Vgl_prtStat( thee );
                } else if (thisKey == VKEY_w) {
                    Vgl_resetCallback(VNULL, (VPTR) 0, VNULL);
                } else if (thisKey == VKEY_W) {
                    Vgl_resetCallback(VNULL, (VPTR) 1, VNULL);
                } else if (thisKey == VKEY_0) {
                    Vgl_listCallback(VNULL, (VPTR) 0, VNULL);
                    Vgl_buildListMenu(thee);
                } else if (thisKey == VKEY_1) {
                    Vgl_listCallback(VNULL, (VPTR) 1, VNULL);
                    Vgl_buildListMenu(thee);
                } else if (thisKey == VKEY_2) {
                    Vgl_listCallback(VNULL, (VPTR) 2, VNULL);
                    Vgl_buildListMenu(thee);
                } else if (thisKey == VKEY_3) {
                    Vgl_listCallback(VNULL, (VPTR) 3, VNULL);
                    Vgl_buildListMenu(thee);
                } else if (thisKey == VKEY_4) {
                    Vgl_listCallback(VNULL, (VPTR) 4, VNULL);
                    Vgl_buildListMenu(thee);
                } else if (thisKey == VKEY_5) {
                    Vgl_listCallback(VNULL, (VPTR) 5, VNULL);
                    Vgl_buildListMenu(thee);
                } else if (thisKey == VKEY_6) {
                    Vgl_listCallback(VNULL, (VPTR) 6, VNULL);
                    Vgl_buildListMenu(thee);
                } else if (thisKey == VKEY_7) {
                    Vgl_listCallback(VNULL, (VPTR) 7, VNULL);
                    Vgl_buildListMenu(thee);
                } else if (thisKey == VKEY_8) {
                    Vgl_listCallback(VNULL, (VPTR) 8, VNULL);
                    Vgl_buildListMenu(thee);
                } else if (thisKey == VKEY_9) {
                    Vgl_listCallback(VNULL, (VPTR) 9, VNULL);
                    Vgl_buildListMenu(thee);

                } else if (thisKey == VKEY_f) {
                    Vgl_listCallback(VNULL, (VPTR) 7, VNULL);
                    Vgl_buildListMenu(thee);
                } else if (thisKey == VKEY_e) {
                    Vgl_listCallback(VNULL, (VPTR) 5, VNULL);
                    Vgl_buildListMenu(thee);

                } else if (thisKey == VKEY_l) {
                    Vgl_settingsCallback(VNULL, (VPTR) VGL_LIGHT, VNULL);
                    Vgl_buildSettingsMenu(thee);
                } else if (thisKey == VKEY_o) {
                    Vgl_settingsCallback(VNULL, (VPTR) VGL_ORTHO, VNULL);
                    Vgl_buildSettingsMenu(thee);
                } else if (thisKey == VKEY_v) {
                    Vgl_settingsCallback(VNULL, (VPTR) VGL_BALL, VNULL);
                    Vgl_buildSettingsMenu(thee);
                } else if (thisKey == VKEY_b) {
                    Vgl_settingsCallback(VNULL, (VPTR) VGL_BBOX, VNULL);
                    Vgl_buildSettingsMenu(thee);
                } else if (thisKey == VKEY_a) {
                    Vgl_settingsCallback(VNULL, (VPTR) VGL_XDR, VNULL);
                    Vgl_buildSettingsMenu(thee);

                } else if (thisKey == VKEY_p) {
                    Vgl_fileWriteCallback(VNULL, (VPTR) 0, VNULL);
                } else if (thisKey == VKEY_P) {
                    Vgl_fileWriteCallback(VNULL, (VPTR) 1, VNULL);
                } else if (thisKey == VKEY_x) {
                    Vgl_fileWriteCallback(VNULL, (VPTR) 2, VNULL);
                } else if (thisKey == VKEY_h) {
                    Vgl_fileWriteCallback(VNULL, (VPTR) 3, VNULL);

                } else if (thisKey == VKEY_m) {
                    Vgl_settingsCallback(VNULL, (VPTR) VGL_FRAME, VNULL);
                    Vgl_buildSettingsMenu(thee);
                }
                Vgl_redraw(thee);

#if defined(HAVE_X11)
                break;
#elif defined(HAVE_WIN32)
                if (!PeekMessage(&qmsg,w,WM_PAINT,WM_PAINT,PM_NOREMOVE))
                    VASSERT( InvalidateRect( w, VNULL, FALSE ) );
                return 0;
#elif defined(HAVE_NEXT)
#endif

            /* Mouse button press */
#if defined(HAVE_X11)
            case ButtonPress:
                /* Mouse button press in graphics window */
                if (w==vcore->plot) {
                    if (!mouseDown) {
                        if (wParam->xbutton.button == 1) {
                            mouseMode = 0;
                            Ogl_setMouseMode(thee->ogl,mouseMode);
                        } else if (wParam->xbutton.button == 2) {
                            mouseMode = 2;
                            Ogl_setMouseMode(thee->ogl,mouseMode);
                        } else if (wParam->xbutton.button == 3) {
                            mouseMode = 1;
                            Ogl_setMouseMode(thee->ogl,mouseMode);
                        }
                        mouseDown = 1;
                        x = wParam->xbutton.x;
                        y = wParam->xbutton.y;
                        Ogl_mouseDown( thee->ogl, x, y );
                        Ogl_display( thee->ogl );
                        Vgl_swapBuffers( thee );
                        before = clock();
                    }
                /* Mouse button on one of the button widgets */
                } else {
#if defined(HAVE_MOTIF)
                    if ( 1 == thee->mode ) { 
                        if (w==vcore->button[VGL_SOCKET]) {
                            XmMenuPosition(vcore->socketMenu,
                                (XButtonPressedEvent*)(wParam));
                            XtManageChild(vcore->socketMenu);
                        } else if (w==vcore->button[VGL_SETTINGS]) {
                            XmMenuPosition(vcore->settingsMenu,
                                (XButtonPressedEvent*)(wParam));
                            XtManageChild(vcore->settingsMenu);
                        } else if (w==vcore->button[VGL_LISTS]) {
                            XmMenuPosition(vcore->listMenu,
                                (XButtonPressedEvent*)(wParam));
                            XtManageChild(vcore->listMenu);
                        } else if (w==vcore->button[VGL_GL2FILE]) {
                            XmMenuPosition(vcore->psgenMenu,
                                (XButtonPressedEvent*)(wParam));
                            XtManageChild(vcore->psgenMenu);
                        } else if (w==vcore->button[VGL_FILE2GL]) {
                            Vgl_fileSelectHandle(thee);
                        } else if (w==vcore->button[VGL_RESET]) {
                            XmMenuPosition(vcore->resetMenu,
                                (XButtonPressedEvent*)(wParam));
                            XtManageChild(vcore->resetMenu);
                        } else if (w==vcore->button[VGL_QUIT]) {
                            Vgl_quit(thee);
                            return;
                        }
                        Vgl_redraw(thee);
                    }
#endif
                }
                break;
#elif defined(HAVE_WIN32)
            case WM_LBUTTONDOWN:
                if (!mouseDown) {
                    mouseMode = 0;
                    Ogl_setMouseMode(thee->ogl,mouseMode);
                    mouseDown = 1;
                    x = LOWORD(lParam);
                    y = HIWORD(lParam);
                    Ogl_mouseDown( thee->ogl, x, y );
                    VASSERT( SetFocus(vcore->topLev) );
                    VASSERT( SetActiveWindow(vcore->topLev) );
                    SetCapture(vcore->topLev);
                    before = clock();
                }
                return 0;
            case WM_MBUTTONDOWN:
                if (!mouseDown) {
                    mouseMode = 2;
                    Ogl_setMouseMode(thee->ogl,mouseMode);
                    mouseDown = 1;
                    x = LOWORD(lParam);
                    y = HIWORD(lParam);
                    Ogl_mouseDown( thee->ogl, x, y );
                    VASSERT( SetFocus(vcore->topLev) );
                    VASSERT( SetActiveWindow(vcore->topLev) );
                    SetCapture(vcore->topLev);
                    before = clock();
                }
                return 0;
            case WM_RBUTTONDOWN:
                if (!mouseDown) {
                    mouseMode = 1;
                    Ogl_setMouseMode(thee->ogl,mouseMode);
                    mouseDown = 1;
                    x = LOWORD(lParam);
                    y = HIWORD(lParam);
                    Ogl_mouseDown( thee->ogl, x, y );
                    VASSERT( SetFocus(vcore->topLev) );
                    VASSERT( SetActiveWindow(vcore->topLev) );
                    SetCapture(vcore->topLev);
                    before = clock();
                }
                return 0;
#elif defined(HAVE_NEXT)
#endif

            /* Mouse button release (after press) */
#if defined(HAVE_X11)
            case ButtonRelease:
                if (mouseDown) {
                    mouseDown = 0;
                    x = wParam->xbutton.x;
                    y = wParam->xbutton.y;
                    Ogl_mouseUp( thee->ogl, x, y );
                    Ogl_display( thee->ogl );
                    Vgl_swapBuffers( thee );
                    after = clock();
                    /* cpu = (double)(after - before) / (double)(CLK_TCK); */
                    cpu = (double)(after - before) / (double)(CLOCKS_PER_SEC);
                    if (   (thee->spinning == 0)
                        && (mouseMode == 0)
                        && (cpu < 4.0e-1) ) {
                       thee->spinId = XtAppAddTimeOut(thee->appCon,
                           1, Vgl_spin, (VPTR)thee);
                       thee->spinning = 1;
                    }
                }
                break;
#elif defined(HAVE_WIN32)
            case WM_LBUTTONUP:
                if (mouseDown) {
                    mouseDown = 0;
                    x = LOWORD(lParam);
                    y = HIWORD(lParam);
                    Ogl_mouseUp( thee->ogl, x, y );
                    VASSERT( ReleaseCapture() );
                    after = clock();
                    cpu = (double)(after - before) / (double)(CLOCKS_PER_SEC);
                    if (   (thee->spinning == 0)
                        && (mouseMode == 0)
                        && (cpu < 4.0e-1) ) {
                       thee->spinId = SetTimer(vcore->topLev, 2, 1, VNULL);
                       thee->spinning = 1;
                    }
                    if (!PeekMessage(&qmsg,w,WM_PAINT,WM_PAINT,PM_NOREMOVE))
                        VASSERT( InvalidateRect( w, VNULL, FALSE ) );
                }
                return 0;
#elif defined(HAVE_NEXT)
#endif

            /* Mouse movement while button pressed */
#if defined(HAVE_X11)
            case MotionNotify:
                if (mouseDown) {
                    x = wParam->xbutton.x;
                    y = wParam->xbutton.y;
                    Ogl_mouseMotion( thee->ogl, x, y );
                    Ogl_display( thee->ogl );
                    Vgl_swapBuffers( thee );
                    before = clock();
                }
                break;
#elif defined(HAVE_WIN32)
            case WM_MOUSEMOVE:
                if (mouseDown) {
                    x = LOWORD(lParam); /* horizontal position of cursor */
                    y = HIWORD(lParam); /* vertical position of cursor */
                    Ogl_mouseMotion( thee->ogl, x, y );
                    if (!PeekMessage(&qmsg,w,WM_PAINT,WM_PAINT,PM_NOREMOVE))
                        VASSERT( InvalidateRect( w, VNULL, FALSE ) );
                    before = clock();
                }
                return 0;
#elif defined(HAVE_NEXT)
#endif

            /* Win32-specific extra events */
#if defined(HAVE_WIN32)
                case WM_TIMER:
                    wTimerID = wParam;
                    if (wTimerID == 1) {
                        Vgl_getPolys(thee, &wTimerID);
                    } else if (wTimerID == 2) {
                        Vgl_spin(thee, &wTimerID);
                    } else {
                        VASSERT(0);
                    }
                    return 0;
                case WM_USER:
                    return 0;
                case WM_MOVE:
                    thee->left = LOWORD(lParam);
                    thee->top = HIWORD(lParam);
                    return 0;
                case WM_KEYDOWN:
                    return 0;
                case WM_CLOSE:
                    Vgl_quit(thee);
                    return 0;
                case WM_DESTROY:
                    return 0;
#elif defined(HAVE_NEXT)
#endif

            default:
                break;
        }
    }

#if defined(HAVE_X11)
#elif defined(HAVE_WIN32)
    return DefWindowProc(w, msg, wParam, lParam);
#elif defined(HAVE_NEXT)
#endif
}

VPUBLIC void Vgl_buildSocketMenu(Vgl *thee)
{
    if (1 == thee->mode) {
#if defined(HAVE_MOTIF)
        Vgl_M_buildSocketMenu(thee);
#else
        /* no-op */
#endif
    } else {
        /* no-op */
    }
}

VPUBLIC void Vgl_buildPsgenMenu(Vgl *thee)
{
    if (1 == thee->mode) {
#if defined(HAVE_MOTIF)
        Vgl_M_buildPsgenMenu(thee);
#else
        /* no-op */
#endif
    } else {
        /* no-op */
    }
}

VPUBLIC void Vgl_buildResetMenu(Vgl *thee)
{
    if (1 == thee->mode) {
#if defined(HAVE_MOTIF)
        Vgl_M_buildResetMenu(thee);
#else
        /* no-op */
#endif
    } else {
        /* no-op */
    }
}

VPUBLIC void Vgl_buildSettingsMenu(Vgl *thee)
{
    if (1 == thee->mode) {
#if defined(HAVE_MOTIF)
        Vgl_M_buildSettingsMenu(thee);
#else
        /* no-op */
#endif
    } else {
        /* no-op */
    }
}

VPUBLIC void Vgl_buildListMenu(Vgl *thee)
{
    if (1 == thee->mode) {
#if defined(HAVE_MOTIF)
        Vgl_M_buildListMenu(thee);
#else
        /* no-op */
#endif
    } else {
        /* no-op */
    }
}

VPUBLIC void Vgl_fileSelectHandle(Vgl *thee)
{
    if (1 == thee->mode) {
#if defined(HAVE_MOTIF)
        Vgl_M_fileSelectHandle(thee);
#else
        /* no-op */
#endif
    } else {
        /* no-op */
    }
}

VPUBLIC void Vgl_prtStat(Vgl *thee)
{
    int i;
    fprintf(stderr, "\n");
    fprintf(stderr, "------------------------[ status of Vgl display ]");
    fprintf(stderr, "-------------------------\n");
    fprintf(stderr, "| Key   Mode         Value  Description"
        "                                  |\n");
    fprintf(stderr, "| l     lighting     %5d  lights on or off"
        " (0=no lights,1=lights)      |\n", thee->settings[VGL_LIGHT]);
    fprintf(stderr, "| o     ortho        %5d  projection"
        " (0=perspective,1=orthographic)    |\n", thee->settings[VGL_ORTHO]);
    fprintf(stderr, "| m     mode         %5d  operating mode"
        " (0=no frames,1=frames)        |\n", thee->settings[VGL_FRAME]);
    fprintf(stderr, "| v     visible ball %5d  visible arcball"
        " (0=none,1=draw arcball)      |\n", thee->settings[VGL_BALL]);
    fprintf(stderr, "| b     visible box  %5d  visible bounding box"
        " (0=none,1=draw box)     |\n", thee->settings[VGL_BBOX]);
    fprintf(stderr, "| a     ASCII I/O    %5d  ASCII or XDR I/O"
        " (0=ASCII,1=XDR)             |\n", thee->settings[VGL_XDR]);
    for (i=0; i<10; i++) {
        if ( Ogl_isList(thee->ogl, i) ) {
            if (i==5) {
                fprintf(stderr, "| %1d (e) listMode[%1d]  %5d  list mode"
                   " (0=none,1=draw display list %d)     |\n",
                    i, i, Ogl_isListOn(thee->ogl,i), i);
            } else if (i==7) {
                fprintf(stderr, "| %1d (f) listMode[%1d]  %5d  list mode"
                   " (0=none,1=draw display list %d)     |\n",
                    i, i, Ogl_isListOn(thee->ogl,i), i);
            } else {
                fprintf(stderr, "| %1d     listMode[%1d]  %5d  list mode"
                   " (0=none,1=draw display list %d)     |\n",
                    i, i, Ogl_isListOn(thee->ogl,i), i);
            }
        }
    }
    fprintf(stderr, "-------------------------------------------------");
    fprintf(stderr, "-------------------------\n");
    fprintf(stderr, "| ?     printStat        -  "
         "print this display of context status         |\n");
    fprintf(stderr, "| w     reset            -  "
         "reset object to original position            |\n");
    fprintf(stderr, "| W     reset            -  "
         "free object and all associated malloc areas  |\n");
    fprintf(stderr, "| Q     quit             -  "
         "quit                                         |\n");
    fprintf(stderr, "-------------------------------------------------");
    fprintf(stderr, "-------------------------\n");
}

