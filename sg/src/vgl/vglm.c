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
 * rcsid="$Id: vglm.c,v 1.32 2010/08/12 04:56:26 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     vglm.c
 *
 * Purpose:  Class Vgl: methods.
 *
 * Comments: Some Motif-based widget constructions which provide
 *           button control for the SG display tool.
 *
 * Notes:    The Motif button generation code in Vgl_M_makeWidgets
 *           came from Randy's Motif version of <xgraph.c> with some
 *           minor changes.
 *
 * Author:   Michael Holst and Randy Bank
 * ***************************************************************************
 */

#include "vglm_p.h"

VEMBED(rcsid="$Id: vglm.c,v 1.32 2010/08/12 04:56:26 fetk Exp $")

/*
 * ***************************************************************************
 * Private routine prototypes
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Class Vglm: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_VGL)
#endif /* if !defined(VINLINE_VGL) */

/*
 * ***************************************************************************
 * Class Vglm: Non-inlineable methods
 * ***************************************************************************
 */

VPUBLIC void Vgl_M_buildSocketMenu(Vgl *thee)
{
    Vglcore *vcore = thee->vcore;
    int i, j, num_items;
    char item_name[80];
    Widget widget;
    XmString name_TITLE;
    XmString name_CLOSED;
    XmString name_UNIX0, name_UNIX1, name_UNIX2, name_UNIX3;
    XmString name_INET0, name_INET1, name_INET2, name_INET3;

    if (vcore->socketMenu != VNULL) {
        XtDestroyWidget(vcore->socketMenu);
        vcore->socketMenu = VNULL;
    }

    name_TITLE = XmStringCreateLocalized("Input Socket Selection");
    name_CLOSED=XmStringCreateLocalized("Closed");
    name_UNIX0 = XmStringCreateLocalized("UNIX Domain socket 0");
    name_UNIX1 = XmStringCreateLocalized("UNIX Domain socket 1");
    name_UNIX2 = XmStringCreateLocalized("UNIX Domain socket 2");
    name_UNIX3 = XmStringCreateLocalized("UNIX Domain socket 3");
    name_INET0 = XmStringCreateLocalized("INET TCP/IP socket 0");
    name_INET1 = XmStringCreateLocalized("INET TCP/IP socket 1");
    name_INET2 = XmStringCreateLocalized("INET TCP/IP socket 2");
    name_INET3 = XmStringCreateLocalized("INET TCP/IP socket 3");
    vcore->socketMenu = XmVaCreateSimplePopupMenu (
        vcore->button[VGL_SOCKET],
        "socketMenu", (XtCallbackProc)Vgl_socketCallBack,
        XmVaTITLE, name_TITLE,
        XmVaDOUBLE_SEPARATOR,
        XmVaTOGGLEBUTTON, name_CLOSED, VNULL, VNULL, VNULL,
        XmVaSEPARATOR,
        XmVaTOGGLEBUTTON, name_UNIX0, VNULL, VNULL, VNULL,
        XmVaTOGGLEBUTTON, name_UNIX1, VNULL, VNULL, VNULL,
        XmVaTOGGLEBUTTON, name_UNIX2, VNULL, VNULL, VNULL,
        XmVaTOGGLEBUTTON, name_UNIX3, VNULL, VNULL, VNULL,
        XmVaSEPARATOR,
        XmVaTOGGLEBUTTON, name_INET0, VNULL, VNULL, VNULL,
        XmVaTOGGLEBUTTON, name_INET1, VNULL, VNULL, VNULL,
        XmVaTOGGLEBUTTON, name_INET2, VNULL, VNULL, VNULL,
        XmVaTOGGLEBUTTON, name_INET3, VNULL, VNULL, VNULL,
        XmNradioBehavior,  True,
        XmNradioAlwaysOne, True,
        XmNtraversalOn, False,
        VNULL);
    XmStringFree(name_TITLE);
    XmStringFree(name_CLOSED);
    XmStringFree(name_UNIX0);
    XmStringFree(name_UNIX1);
    XmStringFree(name_UNIX2);
    XmStringFree(name_UNIX3);
    XmStringFree(name_INET0);
    XmStringFree(name_INET1);
    XmStringFree(name_INET2);
    XmStringFree(name_INET3);
    XtVaSetValues(vcore->socketMenu, XmNwhichButton, 1, VNULL);
    XmChangeColor(vcore->socketMenu, vcore->buttonBackgrnd);
    num_items = 7;
    for (i=0; i<num_items; i++) {
        sprintf(item_name,"button_%d",i);
        widget = VNULL;
        if ( (widget=XtNameToWidget(vcore->socketMenu,item_name)) ) {
            XmChangeColor(widget, vcore->buttonBackgrnd);
            if ( !strncmp(thee->socktype,"UNIX",80) ) {
                VASSERT( thee->socket >= 0 );
                j=thee->socket+1;
            } else if ( !strncmp(thee->socktype,"INET",80) ) {
                VASSERT( thee->socket >= 0 );
                j=thee->socket+5;
            } else { 
                VASSERT( thee->socket < 0 );
                j=0;
            }
            if (i==j) {
                XtVaSetValues(widget, XmNset, True, VNULL);
            } else {
                XtVaSetValues(widget, XmNset, False, VNULL);
            }
        }
    }
}

VPUBLIC void Vgl_M_buildPsgenMenu(Vgl *thee)
{
    Vglcore *vcore = thee->vcore;
    int i, num_items;
    char item_name[80];
    Widget widget;
    XmString name_TITLE, name_PS, name_PS2, name_XPM, name_BH;

    if (vcore->psgenMenu != VNULL) {
        XtDestroyWidget(vcore->psgenMenu);
        vcore->psgenMenu = VNULL;
    }

    name_TITLE = XmStringCreateLocalized("Output File Generation");
    name_PS  = XmStringCreateLocalized("(p)  postscript (no edges)");
    name_PS2 = XmStringCreateLocalized("(P)  postscript (edges)");
    name_XPM = XmStringCreateLocalized("(x)  xpm");
    name_BH  = XmStringCreateLocalized("(h)  bh");
    vcore->psgenMenu = XmVaCreateSimplePopupMenu(
        vcore->button[VGL_GL2FILE],
        "psgenMenu", (XtCallbackProc)Vgl_fileWriteCallback,
        XmVaTITLE, name_TITLE,
        XmVaDOUBLE_SEPARATOR,
        XmVaPUSHBUTTON, name_PS,  VNULL, VNULL, VNULL,
        XmVaPUSHBUTTON, name_PS2, VNULL, VNULL, VNULL,
        XmVaPUSHBUTTON, name_XPM, VNULL, VNULL, VNULL,
        XmVaPUSHBUTTON, name_BH,  VNULL, VNULL, VNULL,
        XmNradioBehavior,  True,
        XmNradioAlwaysOne, True,
        XmNtraversalOn, False,
        VNULL);
    XmStringFree(name_TITLE);
    XmStringFree(name_PS);
    XmStringFree(name_PS2);
    XmStringFree(name_XPM);
    XmStringFree(name_BH);
    XtVaSetValues(vcore->psgenMenu, XmNwhichButton, 1, VNULL);
    XmChangeColor(vcore->psgenMenu, vcore->buttonBackgrnd);
    num_items = 4;
    for (i=0; i<num_items; i++) {
        sprintf(item_name,"button_%d",i);
        widget = VNULL;
        if ( (widget=XtNameToWidget(vcore->psgenMenu,item_name)) ) {
            XmChangeColor(widget, vcore->buttonBackgrnd);
            XtVaSetValues(widget, XmNset, False, VNULL);
        }
    }
}

VPUBLIC void Vgl_M_buildResetMenu(Vgl *thee)
{
    Vglcore *vcore = thee->vcore;
    int i, num_items;
    char item_name[80];
    Widget widget;
    XmString name_TITLE, name_POS, name_MEM;

    if (vcore->resetMenu != VNULL) {
        XtDestroyWidget(vcore->resetMenu);
        vcore->resetMenu = VNULL;
    }

    name_TITLE = XmStringCreateLocalized("Reset Orientation and Memory");
    name_POS = XmStringCreateLocalized("(w)  reset position");
    name_MEM = XmStringCreateLocalized("(W)  release memory");
    vcore->resetMenu = XmVaCreateSimplePopupMenu(
        vcore->button[VGL_RESET],
        "resetMenu", (XtCallbackProc)Vgl_resetCallback,
        XmVaTITLE, name_TITLE,
        XmVaDOUBLE_SEPARATOR,
        XmVaPUSHBUTTON, name_POS, VNULL, VNULL, VNULL,
        XmVaPUSHBUTTON, name_MEM, VNULL, VNULL, VNULL,
        XmNradioBehavior,  True,
        XmNradioAlwaysOne, True,
        XmNtraversalOn, False,
        VNULL);
    XmStringFree(name_TITLE);
    XmStringFree(name_POS);
    XmStringFree(name_MEM);
    XtVaSetValues(vcore->resetMenu, XmNwhichButton, 1, VNULL);
    XmChangeColor(vcore->resetMenu, vcore->buttonBackgrnd);
    num_items = 2;
    for (i=0; i<num_items; i++) {
        sprintf(item_name,"button_%d",i);
        widget = VNULL;
        if ( (widget=XtNameToWidget(vcore->resetMenu,item_name)) ) {
            XmChangeColor(widget, vcore->buttonBackgrnd);
            XtVaSetValues(widget, XmNset, False, VNULL);
        }
    }
}

VPUBLIC void Vgl_M_buildSettingsMenu(Vgl *thee)
{
    Vglcore *vcore = thee->vcore;
    int i, num_items;
    char item_name[80];
    Widget widget;
    XmString name_TITLE, name_LIGHT, name_FRAME;
    XmString name_BALL, name_BOX, name_ORTHO, name_XDR;

    if (vcore->settingsMenu != VNULL) {
        XtDestroyWidget(vcore->settingsMenu);
        vcore->settingsMenu = VNULL;
    }

    name_TITLE = XmStringCreateLocalized("Parameter Settings");
    name_LIGHT = XmStringCreateLocalized("(l)  lighting effects");
    name_ORTHO = XmStringCreateLocalized("(o)  orthographic projection");
    name_FRAME = XmStringCreateLocalized("(m)  mode");
    name_BALL  = XmStringCreateLocalized("(v)  quaternion trackball");
    name_BOX   = XmStringCreateLocalized("(b)  bounding box");
    name_XDR   = XmStringCreateLocalized("(a)  XDR input rather than ASCII");
    vcore->settingsMenu = XmVaCreateSimplePopupMenu (
        vcore->button[VGL_SETTINGS],
        "settingsMenu", (XtCallbackProc)Vgl_settingsCallback,
        XmVaTITLE, name_TITLE,
        XmVaDOUBLE_SEPARATOR,
        XmVaTOGGLEBUTTON, name_LIGHT, VNULL, VNULL, VNULL,
        XmVaTOGGLEBUTTON, name_ORTHO, VNULL, VNULL, VNULL,
        XmVaTOGGLEBUTTON, name_FRAME, VNULL, VNULL, VNULL,
        XmVaSEPARATOR,
        XmVaTOGGLEBUTTON, name_BALL,  VNULL, VNULL, VNULL,
        XmVaTOGGLEBUTTON, name_BOX,   VNULL, VNULL, VNULL,
        XmVaSEPARATOR,
        XmVaTOGGLEBUTTON, name_XDR,   VNULL, VNULL, VNULL,
        XmNradioBehavior,  False,
        XmNradioAlwaysOne, False,
        XmNtraversalOn, False,
        VNULL);
    XmStringFree(name_TITLE);
    XmStringFree(name_LIGHT);
    XmStringFree(name_ORTHO);
    XmStringFree(name_FRAME);
    XmStringFree(name_BALL);
    XmStringFree(name_BOX);
    XmStringFree(name_XDR);
    XtVaSetValues(vcore->settingsMenu, XmNwhichButton, 1, VNULL);
    XmChangeColor(vcore->settingsMenu, vcore->buttonBackgrnd);
    num_items = 7;
    for (i=0; i<num_items; i++) {
        sprintf(item_name,"button_%d",i);
        widget = VNULL;
        if ( (widget=XtNameToWidget(vcore->settingsMenu,item_name)) ) {
            XmChangeColor(widget, vcore->buttonBackgrnd);
            XtVaSetValues(widget, XmNset, thee->settings[i], VNULL);
        }
    }
}

VPUBLIC void Vgl_M_buildListMenu(Vgl *thee)
{
    Vglcore *vcore = thee->vcore;
    XmString name_TITLE, name_LIST[10];
    char item_name[80];
    int j, num_items;
    Widget widget;

    if (vcore->listMenu != VNULL) {
        XtDestroyWidget(vcore->listMenu);
        vcore->listMenu = VNULL;
    }

    if (!thee->winUp) {

        VASSERT( vcore->listMenu == VNULL );
        VASSERT( thee->ogl == VNULL );

        /* build basically an empty menu */
        name_TITLE = XmStringCreateLocalized("Visible Display Lists");
        vcore->listMenu = XmVaCreateSimplePopupMenu (
            vcore->button[VGL_LISTS],
            "listMenu", (XtCallbackProc)Vgl_listCallback,
            XmVaTITLE, name_TITLE,
            XmVaDOUBLE_SEPARATOR,
            XmNradioBehavior,  False,
            XmNradioAlwaysOne, False,
            XmNtraversalOn, False,
            VNULL);
        XtVaSetValues(vcore->listMenu, XmNwhichButton, 1, VNULL);
        XmChangeColor(vcore->listMenu, vcore->buttonBackgrnd);
        XmStringFree(name_TITLE);

    } else {

        name_TITLE
            = XmStringCreateLocalized("Visible Display Lists");
        name_LIST[0]
            = XmStringCreateLocalized("0 (fr1) non-rotated, non-lighted");
        name_LIST[1]
            = XmStringCreateLocalized("1 (fr1) non-rotated, non-lighted");
        name_LIST[2]
            = XmStringCreateLocalized("2 (fr2) non-rotated, non-lighted");
        name_LIST[3]
            = XmStringCreateLocalized("3 (fr3) non-rotated, non-lighted");
        name_LIST[4]
            = XmStringCreateLocalized("4 (fr4) non-rotated, non-lighted");
        name_LIST[5]
            = XmStringCreateLocalized("5 (fr4)     rotated, non-lighted (e)");
        name_LIST[6]
            = XmStringCreateLocalized("6 (fr4)     rotated, non-lighted");
        name_LIST[7]
            = XmStringCreateLocalized("7 (fr4)     rotated,     lighted (f)");
        name_LIST[8]
            = XmStringCreateLocalized("8 (fr4)     rotated,     lighted");
        name_LIST[9]
            = XmStringCreateLocalized("9 (fr4) non-rotated,     lighted");
        vcore->listMenu = XmVaCreateSimplePopupMenu(
            vcore->button[VGL_LISTS],
            "listMenu", (XtCallbackProc)Vgl_listCallback,
            XmVaTITLE, name_TITLE,
            XmVaDOUBLE_SEPARATOR,
            XmVaTOGGLEBUTTON, name_LIST[0], VNULL, VNULL, VNULL,
            XmVaTOGGLEBUTTON, name_LIST[1], VNULL, VNULL, VNULL,
            XmVaTOGGLEBUTTON, name_LIST[2], VNULL, VNULL, VNULL,
            XmVaTOGGLEBUTTON, name_LIST[3], VNULL, VNULL, VNULL,
            XmVaSEPARATOR,
            XmVaTOGGLEBUTTON, name_LIST[4], VNULL, VNULL, VNULL,
            XmVaTOGGLEBUTTON, name_LIST[5], VNULL, VNULL, VNULL,
            XmVaTOGGLEBUTTON, name_LIST[6], VNULL, VNULL, VNULL,
            XmVaTOGGLEBUTTON, name_LIST[7], VNULL, VNULL, VNULL,
            XmVaTOGGLEBUTTON, name_LIST[8], VNULL, VNULL, VNULL,
            XmVaTOGGLEBUTTON, name_LIST[9], VNULL, VNULL, VNULL,
            XmNradioBehavior,  False,
            XmNradioAlwaysOne, False,
            XmNtraversalOn, False,
            VNULL);
        XmStringFree(name_TITLE);
        for (j=0; j<10; j++) {
            XmStringFree(name_LIST[j]);
        }
        XtVaSetValues(vcore->listMenu, XmNwhichButton, 1, VNULL);
        XmChangeColor(vcore->listMenu, vcore->buttonBackgrnd);
        num_items = 10;
        for (j=0; j<num_items; j++) {
            sprintf(item_name,"button_%d",j);
            widget = VNULL;
            if ( (widget=XtNameToWidget(vcore->listMenu,item_name)) ) {
                XmChangeColor(widget, vcore->buttonBackgrnd);
                if ( thee->ogl != VNULL ) {
                    thee->list[j] = Ogl_isListOn(thee->ogl,j);
                    XtVaSetValues(widget, XmNset, thee->list[j], VNULL);
                    if ( !Ogl_isList(thee->ogl,j) ) {
                        /* XtUnmanageChild(widget); */
                        XtDestroyWidget(widget);
                    }
                }
            }
        }
    }
}

VPUBLIC void Vgl_M_fileSelectHandle(Vgl *thee)
{
    Vglcore *vcore = thee->vcore;
    Widget         tempw, tempv, temps, temph;

    if (!vcore->fileSelect) {
        vcore->fileSelect = XmCreateFileSelectionDialog(
            vcore->topLev, "file_select", VNULL, 0);
        XtVaSetValues(vcore->fileSelect, 
/*
                      XmNtraversalOn, False, 
*/
                      XmNwidth,       XWidthOfScreen(vcore->scr)*9/20,    
                      XmNheight,      XHeightOfScreen(vcore->scr)/2,
                      XmNresizePolicy,          XmRESIZE_NONE,
                      VNULL);
        XmChangeColor(vcore->fileSelect, vcore->backgrnd);


/*   remove help button */
  
        tempw = XtNameToWidget(vcore->fileSelect,"Help");
        XtUnmanageChild(tempw);
  
/*   the rest of the buttons */

        tempw = XtNameToWidget(vcore->fileSelect,"OK");
        XtVaSetValues(tempw, XmNfillOnArm, FALSE, NULL);
        tempw = XtNameToWidget(vcore->fileSelect,"Apply");
        XtVaSetValues(tempw, XmNfillOnArm, FALSE, NULL);
        tempw = XtNameToWidget(vcore->fileSelect,"Cancel");
        XtVaSetValues(tempw, XmNfillOnArm, FALSE, NULL);
            

/*  directory list widgets */
  
        tempw = XtNameToWidget(vcore->fileSelect,"DirListSW.DirList");
        tempv = XtNameToWidget(vcore->fileSelect,"DirListSW");
  
        XtVaGetValues(tempv, XmNverticalScrollBar ,&temps ,NULL );
        XtVaGetValues(tempv, XmNhorizontalScrollBar ,&temph ,NULL );

        XmChangeColor (tempw,  vcore->buttonBackgrnd);
        XmChangeColor (tempv,  vcore->backgrnd);
        XmChangeColor (temps,  vcore->backgrnd);
        XmChangeColor (temph,  vcore->backgrnd);
  
        XtVaSetValues(tempv, 
            XmNscrollBarPlacement,     XmBOTTOM_RIGHT, 
            NULL);
        XtVaSetValues(temps, 
            XmNtroughColor,           vcore->buttonBackgrnd, 
            NULL);
        XtVaSetValues(temph, 
            XmNtroughColor,           vcore->buttonBackgrnd, 
            NULL);
  
/*  file list widgets      */
  
        tempw = XtNameToWidget(vcore->fileSelect,"ItemsListSW.ItemsList");
        tempv = XtNameToWidget(vcore->fileSelect,"ItemsListSW");
        XtVaGetValues(tempv, XmNverticalScrollBar ,&temps ,NULL );
        XtVaGetValues(tempv, XmNhorizontalScrollBar ,&temph ,NULL );

        XmChangeColor (tempw,  vcore->buttonBackgrnd);
        XmChangeColor (tempv,  vcore->backgrnd);
        XmChangeColor (temps,  vcore->backgrnd);
        XmChangeColor (temph,  vcore->backgrnd);
  
        XtVaSetValues(tempv, 
            XmNscrollBarPlacement,     XmBOTTOM_RIGHT, 
            NULL);
        XtVaSetValues(temps, 
            XmNtroughColor,           vcore->buttonBackgrnd, 
            NULL);
        XtVaSetValues(temph, 
            XmNtroughColor,           vcore->buttonBackgrnd, 
            NULL);
  
/*   filter text widgets   */
  
        tempw = XtNameToWidget(vcore->fileSelect,"FilterText");
        XmChangeColor (tempw, vcore->buttonBackgrnd);

  
/*  selection text widgets   */

        tempw = XtNameToWidget(vcore->fileSelect,"Text");
        XmChangeColor (tempw, vcore->buttonBackgrnd);

/*  callbacks  */

        XtAddCallback(vcore->fileSelect, XmNokCallback,
           (XtCallbackProc)Vgl_M_fileReadCallback, (XtPointer) thee);
        XtAddCallback(vcore->fileSelect, XmNcancelCallback,
           (XtCallbackProc)XtUnmanageChild, (XtPointer) thee);
    } 
    XtManageChild(vcore->fileSelect);
    XtPopup(XtParent(vcore->fileSelect), XtGrabNone);
}


VPUBLIC XtCallbackProc Vgl_M_fileReadCallback(Widget w,
    XtPointer cli, XtPointer cal)
{
    char title[80], *fname;
    Vio *sock, *sockHolder;
    Vgl *thee = (Vgl*)cli;
    Vglcore *vcore = thee->vcore;

    fname = (char*)XmTextGetString(
        XmFileSelectionBoxGetChild(vcore->fileSelect, XmDIALOG_TEXT));
    XtUnmanageChild(w);

    /* open up a temporary FILE socket */
    if (VNULL==(sock=Vio_ctor("FILE",thee->dataform,"localhost",fname,"r"))) {
        fprintf(stderr,
            "Vgl_M_fileReadCallback: Problem opening file: %s\n", fname);
    } else {
        /* rebuild display lists but now using the file */
        sockHolder = thee->sock;
        thee->sock = sock;
        if ( thee->buildDisplayLists(thee) ) {
            Vgl_M_buildListMenu(thee);
        }
        thee->sock = sockHolder;

        /* destroy the file socket we created */
        Vio_dtor(&sock);

        /* update the window title */
        strncpy(thee->filename,fname,80);
        sprintf(thee->id,"%s File=%s",thee->dataform,thee->filename);
        sprintf(title,"Socket Graphics <%s>",thee->id);
        XtVaSetValues(vcore->topLev,XtNtitle,title,VNULL);
    }

    /* free the malloc fname area */
    XtFree(fname);

    return 0;
}

