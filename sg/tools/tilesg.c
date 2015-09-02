/*
 * ***************************************************************************
 * SG = < Socket Graphics >
 * Copyright (C) 1994-- Michael Holst
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 * rcsid="$Id: tilesg.c,v 1.4 2010/08/09 19:02:07 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     tilesg.c
 *
 * Purpose:  Auto-tiler for the Socket Graphics tool SG.
 *
 * Author:   Michael Holst and Randy Bank
 * ***************************************************************************
 */

#if 0
#   include <sg/vgl.h>
#   define VEMBED(rctag) VPRIVATE const char* rctag; \
       static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
    VEMBED(rcsid="$Id: tilesg.c,v 1.4 2010/08/09 19:02:07 fetk Exp $")
#else
#   include <stdio.h>
#   include <stdlib.h>
#endif

#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
    int i,j,k,ysize,xsize,header,winY,winX,bysize,bxsize,ret;
    int border,menubar,xmin,ymin,nrow,ncol,nwin;
    char cmdbuf[100],PR[80];

    Display *myDisplay;
    Screen  *myScreen;

    myDisplay= XOpenDisplay("");              
    myScreen = DefaultScreenOfDisplay(myDisplay);
    winX = XWidthOfScreen(myScreen);
    winY = XHeightOfScreen(myScreen);
    ret = XCloseDisplay(myDisplay);

    sprintf(PR,"%s","tilesg");

    /* platform parameters (these are for MacOSX): */
    menubar=20;
    /* generic parameters: */
    header=20;
    border=2;

    /* handles args; determine which Vio object to create (file/unix/inet) */
    if (argc == 4) {
        nrow = atoi(argv[1]);
        ncol = atoi(argv[2]);
        nwin = atoi(argv[3]);
    } else {
        fprintf(stderr,"\n");
        fprintf(stderr, "Usage: %s rows cols nwin\n",PR);
        fprintf(stderr,"\n");
        fprintf(stderr,"   Parameter interpretation:\n\n");
        fprintf(stderr,"    rows = number of rows\n");
        fprintf(stderr,"    cols = number of columns\n");
        fprintf(stderr,"    nwin = number of windows\n");
        fprintf(stderr,"\n");
        return 0;
    }

    /* ratio=5/7 */
    ysize = (winY-menubar)/nrow - header - 2*border;
    xsize = winX/ncol - 2*border;
    if (5*xsize > 7*ysize) {
        xsize = (ysize*7)/5;
    } else {
        ysize = (xsize*5)/7;
    }
    fprintf(stderr,"xsize=<%d> ysize=<%d>\n",xsize,ysize);
    bysize = ysize + header + 2*border;
    bxsize = xsize + 2*border;
    for (i=0; i<ncol; i++) {
        for (j=0; j<nrow; j++) {
            k = j + i*nrow;
            if (k < nwin) {
                xmin = winX - (i+1)*bxsize;
                ymin = winY - (j+1)*bysize;
                fprintf(stderr,"k=<%d> xmin=<%d> ymin=<%d>\n",k,xmin,ymin);
                sprintf(cmdbuf, "sg -Mci %d -wpos %d,%d@%d,%d &",
                    k,xsize,ysize,xmin,ymin);
                system(cmdbuf);
            }
        }
    }

    return 0;
}

