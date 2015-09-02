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
 * rcsid="$Id: main.c,v 1.32 2010/08/09 19:02:07 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     main.c
 *
 * Purpose:  Driver for [ X11/GLX | Win32/glW | etc ]-based display tool SG.
 *
 * Notes:    SG is a visualization tool somewhat similar to Geomview
 *           (a tool developed by University of Minnesota's Geometry Center).
 *           SG code can display Geomview "OFF" files, as well as SGI's
 *           OpenInventor IV files, and several other graphics file formats,
 *           including a new format called BH (Bank/Holst) graphics format.
 *
 *           SG uses files, UNIX domain sockets, and INET sockets
 *           to accept ASCII or XDR (RPC's eXternal Data Format) input from
 *           a polygon-generating code such as a finite element code.
 *
 *           You start SG with appropriate parameters to tell it to read
 *           geometry and control data from a particular UNIX or INET socket,
 *           rather than from a normal data file or from the standard input.
 *           We use a parameter syntax which is similar to Geomview; for
 *           example, if you start up SG as follows:
 *
 *               ./mcsg -Mcs 1
 *
 *           then SG will "listen" for input on the UNIX domain socket
 *           /geomview/1-username, the location of which again is to be
 *           compatible with applications that are designed to function
 *           with Geomview.
 *
 *           SG can work with internet (INET) sockets in addition to UNIX
 *           domain sockets, which Geomview can't do.  In particular, SG
 *           can be run on an SGI Octane, and you can run your polygon
 *           generating finite element code on an Origin or an Alpha/Linux
 *           box.  You then just send the geometry over network sockets to
 *           the waiting SG.  It has the appearance of working just like a 
 *           local UNIX domain socket implementation.  Note that this is *not*
 *           the same as displaying an X window from an alpha box remotely on 
 *           an SGI; this is extremely fast.  For example, to start up SG
 *           to listen for XDR data on INET socket 1+14916 (all socket numbers
 *           in SG are relative to the safe socket offset number 14916),
 *           you would type the following:
 *
 *               ./mcsg -xdr -Mci 1
 *
 *           Any machine on the internet that writes to socket 1+14916 on
 *           the machine which is running this invocation of SG will
 *           reach SG waiting for input in XDR format.
 *
 *           SG has one additional advantage (although some would call it 
 *           a disadvantage), in that it also runs under Windows NT.  The 
 *           NT version also supports the network socket use via WINSOCK;
 *           you can crunch on your Alpha/Linux box, and display realtime
 *           through internet sockets on your NT/OpenGL box using your
 *           Diamond FireGL board, for example.
 *
 *           If the SG binary is named anything other than "mcsg", then
 *           it attempts to configure itself using a somewhat more
 *           sophisticated window frame containing buttons for setting
 *           the various controlling parameters as an alternative to
 *           providing them at the command line.  This allows for an SG
 *           instance to be e.g. reconfigured at run-time to take input
 *           from a different socket or socket type, or to toggle between
 *           ASCII and XDR input.  You can also toggle between the two
 *           modes (buttons or no buttons) by pressing the "m" key.
 *           The various keys which affect the behavior of sg and mcsg
 *           are listed in a small menu printed to standard out if you
 *           pres the "?" key at run-time.
 *         
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include <sg/vgl.h>

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
VEMBED(rcsid="$Id: main.c,v 1.32 2010/08/09 19:02:07 fetk Exp $")

typedef struct Vertx {
    float x[3];        /* (x,y,z) coordinate of a vertex */
    float c[4];        /* (r,g,b,a) coloring for this vertex */
    float r;           /* radius of sphere at this vertex (0.0=point) */
} Vertx;

#define VMAXPGV 15     /* maximum number of vertices in a planer polygon */
typedef struct Polyg {
    int   numPV;       /* num vertices in poly ( 3 <= numV <= VMAXPGV ) */
    int   v[VMAXPGV];  /* vertex numbers of this polygon */
    float c[4];        /* (r,g,b,a) coloring for this polygon */
} Polyg;

/* max allowed garbage tokens before recognizing something useful */
VPRIVATE int tokMaxHEAD=40;
VPRIVATE int tokMaxBODY=1000;

/* the Inventor comment char set and white space char set */
VPUBLIC char *INVwhiteChars = " ,\t\n";
VPUBLIC char *INVcommChars = "#";
    
/* the OFF comment char set and white space char set */
VPUBLIC char *OFFwhiteChars = " \t\n";
VPUBLIC char *OFFcommChars = "#";
    
/* the PDB comment char set and white space char set */
VPUBLIC char *PDBwhiteChars = " \t\n";
VPUBLIC char *PDBcommChars = "#";
    
/* the BH comment char set and white space char set */
VPUBLIC char *BHwhiteChars = " \t\n";
VPUBLIC char *BHcommChars = "#";
    
/* global variables */
VPRIVATE char PR[80];
VPRIVATE float frame_xscale = 1.0;
VPRIVATE float frame_yscale = 1.0;
VPRIVATE float frame_zscale = 1.0;
VPRIVATE float frame_xshift = 0.0;
VPRIVATE float frame_yshift = 0.0;
VPRIVATE float frame_zshift = 0.0;

VPRIVATE char *theBuffer   = VNULL;
VPRIVATE int theBufferSize = 0;

/*
 * ***************************************************************************
 * Frame codes:
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
 *
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Purpose:  Frame transformation selection
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void frame(int listNumber)
{
    if (listNumber == 2) {
        frame_xscale = 0.5;
        frame_yscale = 0.5;
        frame_zscale = 0.0;
        frame_xshift = 1.0;
        frame_yshift = 0.5;
        frame_zshift = 0.8;
    } else if (listNumber == 3) {
        frame_xscale = 0.5;
        frame_yscale = 0.5;
        frame_zscale = 0.0;
        frame_xshift = 1.0;
        frame_yshift = 0.0;
        frame_zshift = 0.8;
    } else {
        frame_xscale = 1.0;
        frame_yscale = 1.0;
        frame_zscale = 1.0;
        frame_xshift = 0.0;
        frame_yshift = 0.0;
        frame_zshift = 0.0;
    }
}

/*
 * ***************************************************************************
 * Purpose:  Apply the frame transformation
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void frameTransform(int numPV, float *x, float *y, float *z)
{
    int i;

    for (i=0; i<numPV; i++) {
        x[i] = frame_xscale * x[i] + frame_xshift;
        y[i] = frame_yscale * y[i] + frame_yshift;
        z[i] = frame_zscale * z[i] + frame_zshift;
    }
    for (i=0; i<numPV; i++) {
        x[i] = 2.0 * x[i] - 1.0;
        y[i] = 2.0 * y[i] - 1.0;
        z[i] = 2.0 * z[i] - 1.0;
    }
}

/*
 * ***************************************************************************
 * Purpose:  Apply the inverse frame transformation
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void frameTransformInverse(int numPV, float *x, float *y, float *z)
{
    int i;

    for (i=0; i<numPV; i++) {
        x[i] = (x[i] - frame_xshift) / frame_xscale;
        y[i] = (y[i] - frame_yshift) / frame_yscale;
        z[i] = (z[i] - frame_zshift) / frame_zscale;
    }
    for (i=0; i<numPV; i++) {
        x[i] = (x[i] + 1.0) / 2.0;
        y[i] = (y[i] + 1.0) / 2.0;
        z[i] = (z[i] + 1.0) / 2.0;
    }
}

/*
 * ***************************************************************************
 * Purpose:  Transform poly data to BH data
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int poly2bh(Vgl *thee,
    int numV, int numP, Vertx *vert, Polyg *poly)
{
    int i, j, p, numPV;
    float c[4], r, Min, Max, Len, SC, min[3], max[3];
    float x[VMAXPGV+1], y[VMAXPGV+1], z[VMAXPGV+1];

    /* sanity check */
    VJMPERR1( numV >  0 );
    VJMPERR1( numP >= 0 );

    /* create internal XDR buffer */
    VASSERT( VNULL != (thee->pbuf=Vio_ctor("BUFF","XDR","localhost","0","w")));
    Vio_setWhiteChars(thee->pbuf, BHwhiteChars);
    Vio_setCommChars(thee->pbuf, BHcommChars);
    VJMPERR2( 0 < Vio_printf(thee->pbuf,"%s\n","bhsingle") );

    /* collect bounding box info */
    min[0] =  VLARGE;
    max[0] = -VLARGE;
    min[1] =  VLARGE;
    max[1] = -VLARGE;
    min[2] =  VLARGE;
    max[2] = -VLARGE;
    for (j=0; j<numV; j++) {
        for (p=0; p<3; p++) {
            if (vert[j].x[p] < min[p]) min[p] = vert[j].x[p];
            if (vert[j].x[p] > max[p]) max[p] = vert[j].x[p];
        }
    }

    /* the common cube dmensions */ 
    Min = VLARGE; Max = -VLARGE;
    if (min[0] < Min) Min = min[0];
    if (max[0] > Max) Max = max[0];
    if (min[1] < Min) Min = min[1];
    if (max[1] > Max) Max = max[1];
    if (min[2] < Min) Min = min[2];
    if (max[2] > Max) Max = max[2];
    Len = VABS(Max - Min);
    if (Len == 0) SC = 1.0; 
    else SC = 1.0 / Len;

    /* apply affine transformation to take all verts to master cube */
    for (i=0; i<numV; i++) {    
        vert[i].x[0] = SC * (2.0*vert[i].x[0] - min[0] - max[0]);
        vert[i].x[1] = SC * (2.0*vert[i].x[1] - min[1] - max[1]);
        vert[i].x[2] = SC * (2.0*vert[i].x[2] - min[2] - max[2]);
    }

    /* initialize things */
    VJMPERR2( 0 < Vio_printf(thee->pbuf,"%s %d\n","putl",0) );

    /* vertices/polygons */
    if (numP > 0) {

        /* polygons (display lists 7,8: rotated, lighted) */
        VJMPERR2( 0 < Vio_printf(thee->pbuf,"%s %d\n","list",7) );
        frame(7);
        for (i=0; i<numP; i++) {
            numPV = poly[i].numPV;
            for (j=0; j<numPV; j++) {
                x[j] = vert[ poly[i].v[j] ].x[0];
                y[j] = vert[ poly[i].v[j] ].x[1];
                z[j] = vert[ poly[i].v[j] ].x[2];
            }
            for (j=0; j<4; j++) c[j] = poly[i].c[j];
            frameTransformInverse(numPV,x,y,z);
            VJMPERR2( 0 < Vio_printf(thee->pbuf,
                "%s %e %e %e %d\n", "fill",c[0],c[1],c[2],numPV) );
            for (j=0; j<numPV; j++) {
                VJMPERR2( 0 < Vio_printf(thee->pbuf," %e",x[j]) );
            }
            VJMPERR2( 0 <= Vio_printf(thee->pbuf,"\n") );
            for (j=0; j<numPV; j++) {
                VJMPERR2( 0 < Vio_printf(thee->pbuf," %e",y[j]) );
            }
            VJMPERR2( 0 <= Vio_printf(thee->pbuf,"\n") );
            for (j=0; j<numPV; j++) {
                VJMPERR2( 0 < Vio_printf(thee->pbuf," %e",z[j]) );
            }
            VJMPERR2( 0 <= Vio_printf(thee->pbuf,"\n") );
        }
        VJMPERR2( 0 < Vio_printf(thee->pbuf,"%s %d\n","list",-7) );

        /* edges (display lists 5,6: rotated, non-lighted */
        VJMPERR2( 0 < Vio_printf(thee->pbuf,"%s %d\n","list",5) );
        frame(5);
        for (i=0; i<4; i++) c[i] = 0.0;
        for (i=0; i<numP; i++) {
            numPV = poly[i].numPV;
            for (j=0; j<numPV; j++) {
                x[j] = vert[ poly[i].v[j] ].x[0];
                y[j] = vert[ poly[i].v[j] ].x[1];
                z[j] = vert[ poly[i].v[j] ].x[2];
            }
            x[numPV] = vert[ poly[i].v[0] ].x[0];
            y[numPV] = vert[ poly[i].v[0] ].x[1];
            z[numPV] = vert[ poly[i].v[0] ].x[2];
            frameTransformInverse(numPV+1,x,y,z);
            VJMPERR2( 0 < Vio_printf(thee->pbuf,
                "%s %e %e %e %d\n", "line",c[0],c[1],c[2],numPV+1) );
            for (j=0; j<numPV+1; j++) {
                VJMPERR2( 0 < Vio_printf(thee->pbuf," %e",x[j]) );
            }
            VJMPERR2( 0 <= Vio_printf(thee->pbuf,"\n") );
            for (j=0; j<numPV+1; j++) {
                VJMPERR2( 0 < Vio_printf(thee->pbuf," %e",y[j]) );
            }
            VJMPERR2( 0 <= Vio_printf(thee->pbuf,"\n") );
            for (j=0; j<numPV+1; j++) {
                VJMPERR2( 0 < Vio_printf(thee->pbuf," %e",z[j]) );
            }
            VJMPERR2( 0 <= Vio_printf(thee->pbuf,"\n") );
        }
        VJMPERR2( 0 < Vio_printf(thee->pbuf,"%s %d\n","list",-5) );

    /* vertices only (for placing spheres at points) */
    } else {

        /* everything here is a point */
        numPV = 1;

        /* spheres (display lists 7,8: rotated, lighted) */
        VJMPERR2( 0 < Vio_printf(thee->pbuf,"%s %d\n","list",8) );
        frame(7);
        for (i=0; i<numV; i++) {
            r = vert[i].r;
            x[0] = vert[i].x[0];
            y[0] = vert[i].x[1];
            z[0] = vert[i].x[2];
            frameTransformInverse(1,x,y,z);
            for (j=0; j<4; j++) c[j] = vert[i].c[j];
            VJMPERR2( 0 < Vio_printf(thee->pbuf,
              "%s %e %e %e %e %e %e %e\n",
              "pont",c[0],c[1],c[2],SC*r,x[0],y[0],z[0]) );
        }
        VJMPERR2( 0 < Vio_printf(thee->pbuf,"%s %d\n","list",-8) );
    }

    /* finish up */
    VJMPERR2( 0 < Vio_printf(thee->pbuf,"%s %d\n","putl",-1) );

    /* return with no errors (with polygons) */
    theBufferSize = Vio_bufSize(thee->pbuf);
    theBuffer = Vio_bufGive(thee->pbuf);
    Vio_dtor( &(thee->pbuf) );
    return 1;

  VERROR1:
    fprintf(stderr,"poly2bh: problem with input data\n");
    theBufferSize = 0;
    theBuffer = VNULL;
    Vio_dtor( &(thee->pbuf) );
    return 0;

  VERROR2:
    fprintf(stderr,"poly2bh: problem with output data\n");
    theBufferSize = 0;
    theBuffer = VNULL;
    Vio_dtor( &(thee->pbuf) );
    return 0;
}

/*
 * ***************************************************************************
 * Purpose:  Render BH data to a GL device
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int bh2gl(Vgl *thee)
{
    int j, ncolor, myColor, done, numPV, ikey, numF, numL, numP;
    int listNumber, listNumberTmp;
    char tok[VMAX_BUFSIZE];
    float c[4], x[VMAX_BUFSIZE], y[VMAX_BUFSIZE], z[VMAX_BUFSIZE];
    float red[VMAX_BUFSIZE], green[VMAX_BUFSIZE], blue[VMAX_BUFSIZE];
    float fval, radius;

    /* some i/o */
    numF = 0;
    numL = 0;
    numP = 0;
    fprintf(stderr,"%s: Rendering BH data as GL..", PR);

    /* create internal XDR buffer */
    VASSERT( VNULL != (thee->pbuf=Vio_ctor("BUFF","XDR","localhost","0","r")));
    Vio_setWhiteChars(thee->pbuf, BHwhiteChars);
    Vio_setCommChars(thee->pbuf, BHcommChars);
    Vio_bufTake(thee->pbuf, theBuffer, theBufferSize);

    /* initialization */
    listNumber = -1;

    /* this better be a "bhsingle" file */
    VJMPERR1( 1==Vio_scanf(thee->pbuf,"%s",tok) );
    VJMPERR1( strstr(tok,"bhsingle") != VNULL );

    /* the first command should be putl */
    VJMPERR1( 1==Vio_scanf(thee->pbuf,"%s",tok) );
    VJMPERR1( strstr(tok,"putl") != VNULL );

    /* number of colors (and possible RGB arrays) */
    VJMPERR1( 1==Vio_scanf(thee->pbuf,"%d",&ncolor) );
    VJMPERR1( ncolor >= 0 );
    if (ncolor == 0) {
        /* non-color indexed mode */
    } else if (ncolor > 0) {
        for (j=0; j<ncolor; j++) {
            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
            red[j] = fval;
        }
        for (j=0; j<ncolor; j++) {
            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
            green[j] = fval;
        }
        for (j=0; j<ncolor; j++) {
            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
            blue[j] = fval;
        }
    } else { VJMPERR1(0); }

    /* initialize things; make us current OpenGL device */
    Vgl_putl( thee, ncolor, red, green, blue );

    /* process commands until "putl" is encountered again */
    done = 0;
    while (!done) {

        /* get and process the next command token */
        VJMPERR1( 1==Vio_scanf(thee->pbuf,"%s",tok) );

        /* CASE: display list begin/end */
        if ( strstr(tok,"list") != VNULL ) {

            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%d",&listNumberTmp) );
            if ( listNumberTmp >= 0 ) {
                VJMPERR1( listNumber < 0 );
                listNumber = listNumberTmp;
                VJMPERR1( (0<=listNumber) && (listNumber<=9) );
                frame(listNumber);
                Vgl_list(thee,listNumber,1);
            } else {
                VJMPERR1( (0<=listNumber) && (listNumber<=9) );
                VJMPERR1( listNumberTmp == -listNumber );
                listNumber = -1;
                frame(listNumber);
                Vgl_list(thee,listNumber,1);
            }

        /* CASE: line */
        } else if ( strstr(tok,"line") != VNULL ) {

            numL++;

            VJMPERR1( (0<=listNumber) && (listNumber<=9) );
            if (ncolor == 0) {
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                c[0] = fval;
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                c[1] = fval;
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                c[2] = fval;
            } else { /* (ncolor > 0) */
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%d",&myColor) );
                c[0] = red[   myColor - 1 ];
                c[1] = green[ myColor - 1 ];
                c[2] = blue[  myColor - 1 ];
            }
            c[3] = 0.0;
            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%d",&numPV) );
            for (j=0; j<numPV; j++) {
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                x[j] = fval;
            }
            for (j=0; j<numPV; j++) {
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                y[j] = fval;
            }
            for (j=0; j<numPV; j++) {
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                z[j] = fval;
            }
            frameTransform(numPV,x,y,z);
            Vgl_line(thee,x,y,z,numPV,-1,c);

        /* CASE: fill */
        } else if ( strstr(tok,"fill") != VNULL ) {

            numF++;

            VJMPERR1( (0<=listNumber) && (listNumber<=9) );
            if (ncolor == 0) {
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                c[0] = fval;
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                c[1] = fval;
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                c[2] = fval;
            } else { /* (ncolor > 0) */
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%d",&myColor) );
                c[0] = red[   myColor - 1 ];
                c[1] = green[ myColor - 1 ];
                c[2] = blue[  myColor - 1 ];
            }
            c[3] = 0.0;
            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%d",&numPV) );
            for (j=0; j<numPV; j++) {
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                x[j] = fval;
            }
            for (j=0; j<numPV; j++) {
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                y[j] = fval;
            }
            for (j=0; j<numPV; j++) {
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                z[j] = fval;
            }
            frameTransform(numPV,x,y,z);
            Vgl_fill(thee,x,y,z,numPV,-1,c);

        /* CASE: pont */
        } else if ( strstr(tok,"pont") != VNULL ) {

            numP++;

            VJMPERR1( (0<=listNumber) && (listNumber<=9) );
            if (ncolor == 0) {
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                c[0] = fval;
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                c[1] = fval;
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
                c[2] = fval;
            } else { /* (ncolor > 0) */
                VJMPERR1( 1==Vio_scanf(thee->pbuf,"%d",&myColor) );
                c[0] = red[   myColor - 1 ];
                c[1] = green[ myColor - 1 ];
                c[2] = blue[  myColor - 1 ];
            }
            c[3] = 0.0;
            numPV = 1;
            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
            radius = fval;
            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
            x[0] = fval;
            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
            y[0] = fval;
            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%e",&fval) );
            z[0] = fval;
            frameTransform(numPV,x,y,z);
            Vgl_pont(thee,x,y,z,numPV,-1,c,2,radius);

        /* CASE: putl */
        } else if ( strstr(tok,"putl") != VNULL ) {

            VJMPERR1( listNumber < 0 );
            VJMPERR1( 1==Vio_scanf(thee->pbuf,"%d",&ikey) );
            VJMPERR1( ikey == -1 );
            done = 1;
            Vgl_putl( thee, -1, VNULL, VNULL, VNULL );

        } else { VJMPERR1(0); }
    }

    /* return with no errors */
    fprintf(stderr,"..%d fills, %d lines, %d points.\n", numF, numL, numP);
    return 1;

  VERROR1:
    fprintf(stderr,"bh2gl: problem reading BH data.\n");
    return 0;
}

/*
 * ***************************************************************************
 * Purpose:  Read a BH-file (Bank/Holst compressed graphics format)
 *
 * Notes:    Each "BH" file begins with either "bhsingle" or "bhdouble".
 *           The "bhsingle" and "bhdouble" are necessary for XDR encoding.
 *           If "bhdouble" is used then the XDR encoding uses "double"
 *           in place of "float" for all floating point numbers above.
 *
 *           Other than the "bhsingle" or "bhdouble" keywords, there are
 *           only 5 primatives in the BH language:
 *
 *            PUTL:
 *               putl <ncolors> ==> begin/end a plot
 *                                    ncolors <  0   : end a plot
 *                                    ncolors >= 0   : begin a plot
 *                                      ncolors = 0  : begin a plot (direct)
 *                                      ncolors > 0  : begin a plot (indexed)
 *
 *            LIST:
 *               list <nlist>   ==> begin/end a display list
 *                                    list > 0       : begin list <nlist>
 *                                    list < 0       : end list <nlist>
 *
 *            FILL:
 *               fill <R> <G> <B> <nvert> ==> draw a filled colored polygon
 *                                    <R>      : "red"   float between 0 and 1
 *                                    <G>      : "green" float between 0 and 1
 *                                    <B>      : "blue"  float between 0 and 1
 *                                    <nvert>  : number of vertices in polygon
 *                  (or)
 *               fill <cindex> <nvert> ==> draw a filled polygon
 *                                    <cindex> : index into color array
 *                                    <nvert>  : number of vertices in polygon
 *                  (followed by:)
 *               x_vert_0 y_vert_0 z_vert_0
 *                     ...
 *               x_vert_{<nvert>-1} y_vert_{<nvert>-1} z_vert_{<nvert>-1}
 *
 *            LINE:
 *               line <R> <G> <B> <nvert> ==> draw a colored line
 *                                    <R>      : "red"   float between 0 and 1
 *                                    <G>      : "green" float between 0 and 1
 *                                    <B>      : "blue"  float between 0 and 1
 *                                    <nvert>  : number of vertices in polygon
 *                  (or)
 *               line <cindex> <nvert> ==> draw a colored line
 *                                    <cindex> : index into color array
 *                                    <nvert>  : number of vertices in polygon
 *                  (followed by:)
 *               x_vert_0 y_vert_0 z_vert_0
 *                     ...
 *               x_vert_{<nvert>-1} y_vert_{<nvert>-1} z_vert_{<nvert>-1}
 *
 *            PONT:
 *               pont <R> <G> <B> <radius> <x> <y> <z> ==> draw a sphere
 *                                    <R>      : "red"   float between 0 and 1
 *                                    <G>      : "green" float between 0 and 1
 *                                    <B>      : "blue"  float between 0 and 1
 *                                    <radius> : radius of the sphere
 *                                    <x>      : x-coordinate of sphere center
 *                                    <y>      : y-coordinate of sphere center
 *                                    <z>      : z-coordinate of sphere center
 *                  (or)
 *               pont <cindex> <radius> <x> <y> <z> ==> draw a sphere
 *                                    <cindex> : index into color array
 *                                    <radius> : radius of the sphere
 *                                    <x>      : x-coordinate of sphere center
 *                                    <y>      : y-coordinate of sphere center
 *                                    <z>      : z-coordinate of sphere center
 *
 *   DIRECT method: color given as RGB with each object (fill or line)
 *
 *     ###################################################################
 *     bhsingle            # filetype key (bhsingle or bhdouble)
 *     putl 0              # begin plot (RGB colors given with each object)
 *     list 7              # start display list 7 (of 9 posible)
 *     fill 1.0 0.0 0.0 3  # fill polygon with 3 vertices, RGB=(1.0,0.0,0.0)
 *     0.0 0.0 0.0         # vertex 0 (x-y-z coords)
 *     1.0 0.0 0.0         # vertex 1 (x-y-z coords)
 *     0.0 1.0 0.0         # vertex 2 (x-y-z coords)
 *     list -7             # end display list 7
 *     list 5              # start display list 5 (of 9 posible)
 *     line 1.0 1.0 1.0 4  # line connecting 4 vertices, RGB=(1.0,1.0,1.0)
 *     0.0 0.0 0.0         # vertex 0 (x-y-z coords)
 *     1.0 0.0 0.0         # vertex 1 (x-y-z coords)
 *     0.0 1.0 0.0         # vertex 2 (x-y-z coords)
 *     0.0 0.0 1.0         # vertex 3 (x-y-z coords)
 *     list -5             # end display list 5
 *     putl -1             # end plot
 *     ###################################################################
 *
 *   INDEXED method: color given as RGB index with each object (fill or line)
 *
 *     ###################################################################
 *     bhsingle            # filetype key (bhsingle or bhdouble)
 *     putl 2              # begin plot (num colors, followed by RGB array)
 *     1.0 1.0 1.0         # color 0 (black)
 *     1.0 0.0 0.0         # color 1 (red)
 *     list 7              # start display list 7 (of 9 posible)
 *     fill 1 3            # fill polygon with 3 vertices, RGB=color 1
 *     0.0 0.0 0.0         # vertex 0 (x-y-z coords)
 *     1.0 0.0 0.0         # vertex 1 (x-y-z coords)
 *     0.0 1.0 0.0         # vertex 2 (x-y-z coords)
 *     list -7             # end display list 7
 *     list 5              # start display list 5 (of 9 posible)
 *     line 0 4            # line connecting 4 vertices, RGB=color 0
 *     0.0 0.0 0.0         # vertex 0 (x-y-z coords)
 *     1.0 0.0 0.0         # vertex 1 (x-y-z coords)
 *     0.0 1.0 0.0         # vertex 2 (x-y-z coords)
 *     0.0 0.0 1.0         # vertex 3 (x-y-z coords)
 *     list -5             # end display list 5
 *     putl -1             # end plot
 *     ###################################################################
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int getBH(Vgl *thee, int *numF, int *numL, int dubl)
{
    int j, ncolor, myColor, done, numPV, ikey;
    int listNumber, listNumberTmp;
    char tok[VMAX_BUFSIZE];
    float c[4], x[VMAX_BUFSIZE], y[VMAX_BUFSIZE], z[VMAX_BUFSIZE];
    float red[VMAX_BUFSIZE], green[VMAX_BUFSIZE], blue[VMAX_BUFSIZE];
    float fval;
    double dval;

    /* we can do ASC or XDR */
    VJMPERR2( (thee->sock->frmt == VIO_ASC) || (thee->sock->frmt == VIO_XDR) );

    /* set the comment/whitespace character sets */
    Vio_setWhiteChars(thee->sock, BHwhiteChars);
    Vio_setCommChars(thee->sock, BHcommChars);

    /* the counts */
    *numF = 0;
    *numL = 0;

    /* initialization */
    listNumber = -1;

    /* create internal XDR buffer */
    VASSERT( VNULL != (thee->pbuf=Vio_ctor("BUFF","XDR","localhost","0","w")));
    Vio_setWhiteChars(thee->pbuf, BHwhiteChars);
    Vio_setCommChars(thee->pbuf, BHcommChars);
    VJMPERR3( 0 < Vio_printf(thee->pbuf,"%s\n","bhsingle") );

    /* the first command should be putl */
    VJMPERR1( 1==Vio_scanf(thee->sock,"%s",tok) );
    VJMPERR3( 0 < Vio_printf(thee->pbuf,"%s",tok) );
    VJMPERR1( strstr(tok,"putl") != VNULL );

    /* number of colors (and possible RGB arrays) */
    VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&ncolor) );
    VJMPERR3( 0 < Vio_printf(thee->pbuf," %d\n",ncolor) );
    VJMPERR1( ncolor >= 0 );
    if (ncolor == 0) {
        /* non-color indexed mode */
    } else if (ncolor > 0) {
        for (j=0; j<ncolor; j++) {
            if (dubl) {
                VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                red[j] = (float)dval;
            } else {
                VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                red[j] = fval;
            }
            VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",red[j]) );
        }
        VJMPERR3( 0 <= Vio_printf(thee->pbuf,"\n") );
        for (j=0; j<ncolor; j++) {
            if (dubl) {
                VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                green[j] = (float)dval;
            } else {
                VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                green[j] = fval;
            }
            VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",green[j]) );
        }
        VJMPERR3( 0 <= Vio_printf(thee->pbuf,"\n") );
        for (j=0; j<ncolor; j++) {
            if (dubl) {
                VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                blue[j] = (float)dval;
            } else {
                VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                blue[j] = fval;
            }
            VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",blue[j]) );
        }
        VJMPERR3( 0 <= Vio_printf(thee->pbuf,"\n") );
    } else { VJMPERR1(0); }

    /* process commands until "putl" is encountered again */
    done = 0;
    while (!done) {

        /* get and process the next command token */
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",tok) );
        VJMPERR3( 0 < Vio_printf(thee->pbuf,"%s",tok) );

        /* CASE: display list begin/end */
        if ( strstr(tok,"list") != VNULL ) {

            VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&listNumberTmp) );
            VJMPERR3( 0 < Vio_printf(thee->pbuf," %d\n",listNumberTmp) );
            if ( listNumberTmp >= 0 ) {
                VJMPERR1( listNumber < 0 );
                listNumber = listNumberTmp;
                VJMPERR1( (0<=listNumber) && (listNumber<=9) );
            } else {
                VJMPERR1( (0<=listNumber) && (listNumber<=9) );
                VJMPERR1( listNumberTmp == -listNumber );
                listNumber = -1;
            }

        /* CASE: line */
        } else if ( strstr(tok,"line") != VNULL ) {

            VJMPERR1( (0<=listNumber) && (listNumber<=9) );
            (*numL)++;
            if (ncolor == 0) {
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    c[0] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    c[0] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",c[0]) );
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    c[1] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    c[1] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",c[1]) );
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    c[2] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    c[2] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",c[2]) );
            } else { /* (ncolor > 0) */
                VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&myColor) );
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %d",myColor) );
                c[0] = red[   myColor - 1 ];
                c[1] = green[ myColor - 1 ];
                c[2] = blue[  myColor - 1 ];
            }
            c[3] = 0.0;
            VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&numPV) );
            VJMPERR3( 0 < Vio_printf(thee->pbuf," %d\n",numPV) );
            for (j=0; j<numPV; j++) {
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    x[j] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    x[j] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",x[j]) );
            }
            for (j=0; j<numPV; j++) {
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    y[j] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    y[j] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",y[j]) );
            }
            for (j=0; j<numPV; j++) {
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    z[j] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    z[j] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",z[j]) );
            }
            VJMPERR3( 0 <= Vio_printf(thee->pbuf,"\n") );

        /* CASE: fill */
        } else if ( strstr(tok,"fill") != VNULL ) {

            VJMPERR1( (0<=listNumber) && (listNumber<=9) );
            (*numF)++;
            if (ncolor == 0) {
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    c[0] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    c[0] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",c[0]) );
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    c[1] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    c[1] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",c[1]) );
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    c[2] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    c[2] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",c[2]) );
            } else { /* (ncolor > 0) */
                VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&myColor) );
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %d",myColor) );
                c[0] = red[   myColor - 1 ];
                c[1] = green[ myColor - 1 ];
                c[2] = blue[  myColor - 1 ];
            }
            c[3] = 0.0;
            VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&numPV) );
            VJMPERR3( 0 < Vio_printf(thee->pbuf," %d\n",numPV) );
            for (j=0; j<numPV; j++) {
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    x[j] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    x[j] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",x[j]) );
            }
            for (j=0; j<numPV; j++) {
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    y[j] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    y[j] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",y[j]) );
            }
            for (j=0; j<numPV; j++) {
                if (dubl) {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%le",&dval) );
                    z[j] = (float)dval;
                } else {
                    VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                    z[j] = fval;
                }
                VJMPERR3( 0 < Vio_printf(thee->pbuf," %e",z[j]) );
            }
            VJMPERR3( 0 <= Vio_printf(thee->pbuf,"\n") );

        /* CASE: putl */
        } else if ( strstr(tok,"putl") != VNULL ) {

            VJMPERR1( listNumber < 0 );
            VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&ikey) );
            VJMPERR3( 0 < Vio_printf(thee->pbuf," %d\n",ikey) );
            VJMPERR1( ikey == -1 );
            done = 1;

        } else { VJMPERR1(0); }
    }

    /* return with no errors */
    theBufferSize = Vio_bufSize(thee->pbuf);
    theBuffer = Vio_bufGive(thee->pbuf);
    Vio_dtor( &(thee->pbuf) );
    return 1;

  VERROR1:
    fprintf(stderr,"getBH: problem reading BH data.\n");
    theBufferSize = 0;
    theBuffer = VNULL;
    Vio_dtor( &(thee->pbuf) );
    return 0;

  VERROR2:
    fprintf(stderr,"getBH: BH data must be in ASC or XDR.\n");
    theBufferSize = 0;
    theBuffer = VNULL;
    Vio_dtor( &(thee->pbuf) );
    return 0;

  VERROR3:
    fprintf(stderr,"getBH: Problem writing to internal XDR buffer.\n");
    theBufferSize = 0;
    theBuffer = VNULL;
    Vio_dtor( &(thee->pbuf) );
    return 0;
}

/*
 * ***************************************************************************
 * Purpose:  Read an OFF-file (Geomview format)
 *
 * Notes:    Typical "OFF" input file:
 *
 *     ###################################################################
 *     OFF                             # filetype key
 *     1231 1078 4166                  # number of V,S,E (E is ignored)
 *     28.75 8.50 -28.25               # first vertex (x-y-z coords)
 *          ...
 *     -21.90 47.90 17.50              # last vertex (x-y-z coords)
 *     3   6 8 0        0.80 0.10 0.10 # first polygon (#verts, verts, RGBA)
 *          ...
 *     3   121 128 130  0.80 0.10 0.10 # last polygon (#verts, verts, RGBA)
 *     ###################################################################
 *
 *     Note that there might be a 4th real number on each line in an OFF file;
 *     this is interpretted as an ALPHA (GAMMA) value for that polygon.
 *     We currently do not allow the extra ALPHA values in our OFF read
 *     routine; files with ALPHA values on any line will generate an error.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int getOFF(Vgl *thee,
    int *numV, int *numP, Vertx **vert, Polyg **poly)
{
    int i, j, dummy;
    float fval;

    /* we can do ASC or XDR */
    VJMPERR2( (thee->sock->frmt == VIO_ASC) || (thee->sock->frmt == VIO_XDR) );

    /* set the comment/whitespace character sets */
    Vio_setWhiteChars(thee->sock, OFFwhiteChars);
    Vio_setCommChars(thee->sock, OFFcommChars);

    /* next line has vertex/simplex/edge information */
    VJMPERR1( 1==Vio_scanf(thee->sock,"%d",numV) );
    VJMPERR1( 1==Vio_scanf(thee->sock,"%d",numP) );
    VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&dummy) );

    /* get new space -- we DO know A PRIORI how big arrays need to be */
    if (*numV > 0) (*vert) = (Vertx*)calloc( *numV, sizeof(Vertx) );
    if (*numP > 0) (*poly) = (Polyg*)calloc( *numP, sizeof(Polyg) );

    /* read in the vertices */
    for (i=0; i<*numV; i++) {
        for (j=0; j<3; j++) {
            VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
            (*vert)[i].x[j] = fval;
        }
#if 0
        fprintf(stderr,"v[%d]=< %e , %e , %e >\n",
            i,(*vert)[i].x[0],(*vert)[i].x[1],(*vert)[i].x[2]);
#endif
    }

    /* read in the polygons */
    for (i=0; i<*numP; i++) {

        /* number of vertices in this polygon */
        VJMPERR1( 1==Vio_scanf(thee->sock,"%d", &((*poly)[i].numPV) ) );
        VJMPERR1( (3 <= (*poly)[i].numPV) && ((*poly)[i].numPV <= 15) );

        /* the vertex numbers for this polygon */
        for (j=0; j<(*poly)[i].numPV; j++)
            VJMPERR1( 1==Vio_scanf(thee->sock,"%d", (*poly)[i].v+j) );

        /* get (r,g,b) colors for this polygon */
        for (j=0; j<3; j++) {
            VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
            (*poly)[i].c[j] = fval;
        }

        /* set alpha to zero; assume not in the file as part of color! */
        (*poly)[i].c[3] = 0.0;

#if 0
        fprintf(stderr,"s[%d]=< %d , %d , %d >   < %e, %e, %e >\n",
            i,(*poly)[i].v[0],(*poly)[i].v[1],(*poly)[i].v[2],
              (*poly)[i].c[0],(*poly)[i].c[1],(*poly)[i].c[2]);
#endif
    }
    VJMPERR1( i == *numP );

    /* return with no errors */
    return 1;

  VERROR1:
    fprintf(stderr,"getOFF: problem reading OFF data.\n");
    return 0;

  VERROR2:
    fprintf(stderr,"getOFF: OFF data must be in ASC or XDR.\n");
    return 0;
}

/*
 * ***************************************************************************
 * Purpose:  Read an PDB-file (Protein database format)
 *
 * Notes:    Typical "pdb" input file and the standard coloring of atoms:
 *
 *     ###################################################################
 *     PDB                   # filetype key
 *     9 1651                # number of RGBA colors and number of atoms
 *     #   RRR GGG BBB AAA   # RGBA order
 *     C   0.2 0.2 0.2 1.0   # carbon      -- grey/black
 *     O   1.0 0.0 0.0 1.0   # oxygen      -- red
 *     N   0.0 0.0 1.0 1.0   # nitrogen    -- blue
 *     H   1.0 1.0 1.0 1.0   # hydrogen    -- white/not shown
 *     P   0.0 1.0 0.0 1.0   # phosphorous -- green/varies
 *     S   1.0 1.0 0.0 1.0   # sulfur      -- yellow
 *     L   0.0 0.0 0.0 1.0   # lithium     -- anything/nothing?
 *     F   1.0 0.0 1.0 1.0   # fluorine    -- pink/purple/anything
 *     I   0.0 1.0 1.0 1.0   # iodine      -- anything
 *     #
 *     ATOM      1  OXT       G      1  13.976  23.322   9.208 -0.760 1.600
 *     ...                                ...
 *     ATOM   1651  OXT       G     91  14.213  22.233   8.283 -0.760 1.600
 *     ###################################################################
 * 
 * The "ATOM" lines specify one atom per line in a PQR file is as follows:
 *
 *     What   # Type ResName   ResNum X-coord Y-coord Z-coord Chrg   Radius
 *     ---- --- ---- -------   ------ ------- ------- ------- ------ ------
 *     ATOM  28 Oxyz Cxyz       2      12.590  25.761   1.393 -0.89   1.600
 *
 * The "ATOM" lines specify one atom per line in a PDB file is as follows:
 *
 *     What   # Type ResName ? ResNum X-coord Y-coord Z-coord  ???    ???  
 *     ---- --- ---- ------- - ------ ------- ------- ------- ------ ------
 *     ATOM 124 H    THR     A 12      -2.924  33.977  32.167  0.00  15.00  etc
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int getPDB(Vgl *thee,
    int *numV, int *numP, Vertx **vert, Polyg **poly)
{
    int i, j, idum, numC, found;
    float fval, radius, acolor[100][80];
    char cdum[80], atype[80], aname[100][80];

    /* we only do ASC */
    VJMPERR2( thee->sock->frmt == VIO_ASC );

    /* set the comment/whitespace character sets */
    Vio_setWhiteChars(thee->sock, PDBwhiteChars);
    Vio_setCommChars(thee->sock, PDBcommChars);

    /* next line has color and vertex information */
    VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&numC) );
    VJMPERR1( 1==Vio_scanf(thee->sock,"%d",numV) );
    *numP = 0;
    VJMPERR1( numC <= 100 );

    /* get new space -- we DO know A PRIORI how big arrays need to be */
    if (*numV > 0) (*vert) = (Vertx*)calloc( *numV, sizeof(Vertx) );

    /* read in the colors */
    for (i=0; i<numC; i++) {
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",aname[i]) );
        for (j=0; j<4; j++) {
            VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
            acolor[i][j] = fval;
        }
    }

    /* read in the atoms */
    for (i=0; i<*numV; i++) {

        /* grab the atom name token */
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",cdum) );

        /* grab the atom number token */
        VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&idum) );

        /* grab the atom type token */
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",atype) );

        /* grab the residue name token */
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",cdum) );

        /* grab the residue number token */
        VJMPERR1( 1==Vio_scanf(thee->sock,"%d",&idum) );

        for (j=0; j<3; j++) {
            VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
            (*vert)[i].x[j] = fval;
        }

        /* grab the charge token */
        VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );

        /* grab the radius token */
        VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
        radius = 1.2 * fval;
        if (radius == 0.0) radius = 1.0;
        (*vert)[i].r = radius;

        /* setup some colors based on atom type */
        (*vert)[i].c[0] = 1.0;
        (*vert)[i].c[1] = 1.0;
        (*vert)[i].c[2] = 1.0;
        (*vert)[i].c[3] = 1.0;
        found = 0;
        for (j=0; j<numC; j++) {
            if (atype[0] == aname[j][0]) {
                (*vert)[i].c[0] = acolor[j][0];
                (*vert)[i].c[1] = acolor[j][1];
                (*vert)[i].c[2] = acolor[j][2];
                (*vert)[i].c[3] = acolor[j][3];
                found = 1;
            }
        }
        if (!found) fprintf(stderr,"getPDB: unknown atom <%s>\n", atype);
    }

    /* return with no errors */
    return 1;

  VERROR1:
    fprintf(stderr,"getPDB: problem reading PDB data.\n");
    return 0;

  VERROR2:
    fprintf(stderr,"getPDB: PDB data must be in ASC.\n");
    return 0;
}

/*
 * ***************************************************************************
 * Purpose:  Read an IV-file (Inventor format)
 *
 * Notes:    Typical "IV" input file:
 *
 *           #################################################################
 *           #Inventor V2.1 ascii
 *           Separator {
 *               Blah-Blah-Blah
 *               Coordinate3 {
 *                   point [ 10.8343 5.71745 196.846,
 *                           ...
 *                           16.2891 -183.083 83.8652 ]
 *               }
 *               IndexedFaceSet {
 *                   coordIndex [ 2, 0, 3, -1, 1, 0, 4, -1,
 *                                ...
 *                                46, 16, 39, -1 ]
 *               }
 *           }
 *           #################################################################
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int getIV(Vgl *thee,
    int *numV, int *numP, Vertx **vert, Polyg **poly)
{
    int i, j, k, done, ival;
    float fval;
    char tok[VMAX_BUFSIZE];

    Vertx *vertOld = VNULL;
    Polyg *polyOld = VNULL;
    int numVmaxOld = 0;
    int numPmaxOld = 0;
    int numVmax    = 0;
    int numPmax    = 0;

    /* we only do ASC */
    VJMPERR2( thee->sock->frmt == VIO_ASC );

    /* set the comment/whitespace character sets */
    Vio_setWhiteChars(thee->sock, INVwhiteChars);
    Vio_setCommChars(thee->sock, INVcommChars);

    /* get new space -- we DO NOT know A PRIORI how big arrays need to be */
    numVmax = 0;
    numPmax = 0;

    /* need to skip down to the "Coordinate3" label to start vertex list */
    done = 0;
    i = 0;
    while ((!done) && (i < tokMaxBODY)) {
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",tok) );
        if ( strstr(tok,"Coordinate3") != VNULL ) done = 1;
        i++;
    }
    VJMPERR1( i < tokMaxBODY );

    /* need to skip down to the "[" label to start vertex list */
    done = 0;
    i = 0;
    while ((!done) && (i < tokMaxBODY)) {
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",tok) );
        if ( strstr(tok,"[") != VNULL ) done = 1;
        i++;
    }
    VJMPERR1( i < tokMaxBODY );

    /* read in the vertices */
    done = 0;
    i = 0;
    while (!done) {
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",tok) );
        if ( strstr(tok,"]") != VNULL ) done = 1;
        else {
            if (i == numVmax) {
                numVmaxOld = numVmax;
                vertOld = (*vert);
                numVmax = 2*(numVmaxOld+1);
                (*vert) = (Vertx*)calloc( numVmax, sizeof(Vertx) );
                if (vertOld != VNULL) {
                    for (j=0; j<numVmaxOld; j++)
                        for (k=0; k<3; k++)
                            (*vert)[j].x[k] = vertOld[j].x[k];
                    free( vertOld );
                    vertOld = VNULL;
                }
            }
            sscanf(tok,"%e",&fval);
            (*vert)[i].x[0] = fval;
            for (j=1; j<3; j++) {
                VJMPERR1( 1==Vio_scanf(thee->sock,"%e",&fval) );
                (*vert)[i].x[j] = fval;
            }
            i++;
        }
    }
    *numV = i;

    /* need to skip down to the "IndexedFaceSet" label to start polygon list */
    done = 0;
    i = 0;
    while ((!done) && (i < tokMaxBODY)) {
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",tok) );
        if ( strstr(tok,"IndexedFaceSet") != VNULL ) done = 1;
        i++;
    }
    VJMPERR1( i < tokMaxBODY );

    /* need to skip down to the "[" label to start polygon list */
    done = 0;
    i = 0;
    while ((!done) && (i < tokMaxBODY)) {
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",tok) );
        if ( strstr(tok,"[") != VNULL ) done = 1;
        i++;
    }
    VJMPERR1( i < tokMaxBODY );

    /* read in the vertices */
    done = 0;
    i = 0;
    while (!done) {
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",tok) );
        if ( strstr(tok,"]") != VNULL ) done = 1;
        else {
            if (i == numPmax) {
                numPmaxOld = numPmax;
                polyOld = (*poly);
                numPmax = 2*(numPmaxOld+1);
                (*poly) = (Polyg*)calloc( numPmax, sizeof(Polyg) );
                if (polyOld != VNULL) {
                    for (j=0; j<numPmaxOld; j++) {
                        (*poly)[j].numPV = polyOld[j].numPV;
                        for (k=0; k<(*poly)[j].numPV; k++)
                            (*poly)[j].v[k] = polyOld[j].v[k];
                        for (k=0; k<4; k++)
                            (*poly)[j].c[k] = polyOld[j].c[k];
                    }
                    free( polyOld );
                    polyOld = VNULL;
                }
            }
            sscanf(tok,"%d", &ival);
            if (ival == -1) {
                VJMPERR1( (3<=(*poly)[i].numPV) && ((*poly)[i].numPV<=15) );
                for (j=0; j<4; j++) (*poly)[i].c[j] = (float)0.6;
                i++;
            } else {
                (*poly)[i].v[ (*poly)[i].numPV ] = ival;

                /* ASSUME WAS INITIALIZED TO ZERO BY CALLOC!!! */
                (*poly)[i].numPV++;
            }
        }
    }
    *numP = i;

    /* remalloc vertices so we have just enough space */
    if (*numV > 0) {
        vertOld = (*vert);
        (*vert) = (Vertx*)calloc( *numV, sizeof(Vertx) );
        VJMPERR1( (*vert) != VNULL );
        for (j=0; j<*numV; j++)
            for (k=0; k<3; k++)
                (*vert)[j].x[k] = vertOld[j].x[k];
        free( vertOld );
        vertOld = VNULL;
    }

    /* remalloc polygons so we have just enough space */
    if (*numP > 0) {
        polyOld = (*poly);
        (*poly) = (Polyg*)calloc( *numP, sizeof(Polyg) );
        VJMPERR1( (*poly) != VNULL );
        for (j=0; j<*numP; j++) {
            (*poly)[j].numPV = polyOld[j].numPV;
            for (k=0; k<(*poly)[j].numPV; k++)
                (*poly)[j].v[k] = polyOld[j].v[k];
            for (k=0; k<4; k++)
                (*poly)[j].c[k] = polyOld[j].c[k];
        }
        free( polyOld );
        polyOld = VNULL;
    }

    /* return with no errors */
    return 1;

  VERROR1:
    fprintf(stderr,"getIV: problem reading IV data.\n");
    return 0;

  VERROR2:
    fprintf(stderr,"getIV: IV data must be in ASC.\n");
    return 0;
}

/*
 * ***************************************************************************
 * Purpose:  Read the polygons
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPRIVATE int getPolygs(Vgl *thee)
{
    int dtype, tokCount, done;
    char tok[VMAX_BUFSIZE];
    int numV    = 0;
    int numP    = 0;
    int numF    = 0;
    int numL    = 0;
    Vertx *vert = VNULL;
    Polyg *poly = VNULL;

    /* common minimal settings for white space and comment character sets */
    Vio_setWhiteChars(thee->sock," \t\n");
    Vio_setCommChars(thee->sock,"");

    /* determine the input file format */
    tokCount = 0;
    done = 0;
    dtype = 0;
    while ((!dtype) && (tokCount < tokMaxHEAD) && (!done) ) {
        VJMPERR1( 1==Vio_scanf(thee->sock,"%s",tok) );
        if (tok != VNULL) {
            if      ( strstr(tok,"#Inventor")     != VNULL ) dtype = 1;
            else if ( strstr(tok,"OFF")           != VNULL ) dtype = 2;
            else if ( strstr(tok,"PDB")           != VNULL ) dtype = 3;
            else if ( strstr(tok,"bhsingle")      != VNULL ) dtype = 4;
            else if ( strstr(tok,"bhdouble")      != VNULL ) dtype = 5;
            else if ( strstr(tok,"mcsf_begin")    != VNULL ) dtype = 6;
            else if ( strstr(tok,"mcef_begin")    != VNULL ) dtype = 7;
            tokCount++;
        } else done = 1;
    }

    /* take action based on classification */
    if (dtype == 1) {
        fprintf(stderr,"%s: Hit with an IV file..", PR);
        VJMPERR1( getIV(thee, &numV, &numP, &vert, &poly) );
        fprintf(stderr,"..%d vertices and %d polygons.\n", numV, numP);
        VJMPERR1( poly2bh(thee, numV, numP, vert, poly) );
    } else if (dtype == 2) {
        fprintf(stderr,"%s: Hit with an OFF file..", PR);
        VJMPERR1( getOFF(thee, &numV, &numP, &vert, &poly) );
        fprintf(stderr,"..%d vertices and %d polygons.\n", numV, numP);
        VJMPERR1( poly2bh(thee, numV, numP, vert, poly) );
    } else if (dtype == 3) {
        fprintf(stderr,"%s: Hit with a PDB file..", PR);
        VJMPERR1( getPDB(thee, &numV, &numP, &vert, &poly) );
        fprintf(stderr,"..%d vertices (atoms).\n", numV);
        VJMPERR1( poly2bh(thee, numV, numP, vert, poly) );
    } else if (dtype == 4) {
        fprintf(stderr,"%s: Hit with a BHsingle file..", PR);
        VJMPERR1( getBH(thee, &numF, &numL, 0) );
        fprintf(stderr,"..%d files and %d lines.\n", numF, numL);
    } else if (dtype == 5) {
        fprintf(stderr,"%s: Hit with a BHdouble file..", PR);
        VJMPERR1( getBH(thee, &numF, &numL, 1) );
        fprintf(stderr,"..%d files and %d lines.\n", numF, numL);
    } else {
        if (dtype == 6) {
            fprintf(stderr,"%s: Unable to display MCSF files directly.\n", PR);
        } else if (dtype == 7) {
            fprintf(stderr,"%s: Unable to display MCEF files directly.\n", PR);
        } else {
            fprintf(stderr,"%s: Problem understanding the file header.\n", PR);
        }
    }
    /* release data space */
    if ( vert != VNULL ) {
        free( vert );
        vert = VNULL;
    }
    if ( poly != VNULL ) {
        free( poly );
        poly = VNULL;
    }
    return 1;

  VERROR1:
    fprintf(stderr,"getPolygs: problem reading data.\n");
    /* release data space */
    if ( vert != VNULL ) {
        free( vert );
        vert = VNULL;
    }
    if ( poly != VNULL ) {
        free( poly );
        poly = VNULL;
    }
    return 0;
}

/*
 * ***************************************************************************
 * Purpose:  Build the display lists
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
int buildDisplayLists(Vgl *thee)
{
    int rc;

    /* check the socket first */
    if (thee->sock == VNULL) return 0;

    /* call (non-blocking) accept */
    if (0 <= Vio_accept(thee->sock,1)) {

        /* get the new polygons */
        rc=getPolygs(thee);

        /* free input subsocket to setup for another accept */
        Vio_acceptFree(thee->sock);

        /* return with no errors (without polygons) */
        if (rc == 0) {
            fprintf(stderr,"buildDisplayLists: hmmm...didn't get polygons!\n");
            return 0;

        /* return with no errors (with polygons) after rendering */
        } else {
            VJMPERR1( bh2gl(thee) );
            return 1;
        }

    } else {
        /* return with no errors (without polygons) */
        return 0;
    }

  VERROR1:
    fprintf(stderr,"buildDisplayLists: problem with data\n");
    return 0;
}

/*
 * ***************************************************************************
 * Routine:  main
 *
 * Purpose:  Read data from file/unix-or-inet-socket
 *           and display using VGL library.
 *
 * Notes:    This code currently supports the following data formats:
 *
 *           (1) OFF --> Geomview-style data files
 *           (2) IV  --> Inventor-style data files
 *           (3) PDB --> Protein Databank-style data files
 *           (4) BH  --> Bank/Holst-style compressed data files
 *
 * Example:  The following brings up SG listening to AF_UNIX socket 1:
 *
 *               ./mcsg -nopanels -wpos 215,208@0,764 -Mcs 1
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
int main(int argc, char *argv[])
{
    int mode, argi, xsize, ysize, xpos, ypos;
    char geomInfo[80], *buf[80];
    char dataform[80], socktype[80], hostname[80], filename[80];

    Vgl *vgl = VNULL;

    /* default window size and position */
    xsize = 500;
    ysize = 500;
    xpos  = 0;
    ypos  = 0;

    /* defaults */
    strncpy(filename,"-1",80);
    strncpy(dataform,"XDR",80);
    strncpy(socktype,"FILE",80);
    strncpy(hostname,"localhost",80);
    strncpy(PR,argv[0],80);

    /* determine startup mode based on name of invoked binary */
#if 0
    mode = 0;
#else
    if ( (!strcmp(PR,"mcsg")) || (!strcmp(PR,"./mcsg")) ) {
        mode = 0;
    } else {
        if (Vgl_capability() > 0) {
            mode = 1;
            /* change default socktype to "NONE" */
            strncpy(socktype,"NONE",80);
        } else {
            mode = 0;
        }
    }
#endif

    /* handles args; determine which Vio object to create (file/unix/inet) */
    if (argc > 1) {
        argi = 1;
        while (argi < argc) {
            if ((!strcmp(argv[argi],"-h")) || (!strcmp(argv[argi],"--help"))) {
                VJMPERR1(0);
            } else if (!strcmp(argv[argi],"-nopanels")) {
                argi++;
            } else if (!strcmp(argv[argi],"-asc")) {
                argi++;
                strncpy(dataform,"ASC",80);
            } else if (!strcmp(argv[argi],"-xdr")) {
                argi++;
                strncpy(dataform,"XDR",80);
            } else if (!strcmp(argv[argi],"-wpos")) {
                argi++;
                if (argi < argc) {
                    strncpy(geomInfo,argv[argi],80);
                    (void)Vnm_gentokens(geomInfo, buf, 80, ",@", "");
                    if (buf[0] != VNULL) xsize = atoi(buf[0]);
                    if (buf[1] != VNULL) ysize = atoi(buf[1]);
                    if (buf[2] != VNULL) xpos  = atoi(buf[2]);
                    if (buf[3] != VNULL) ypos  = atoi(buf[3]);
                    argi++;
                }
            } else if (!strcmp(argv[argi],"-Mci")) {
                argi++;
                if (argi < argc) sprintf(filename,"%s", argv[argi]);
                else             sprintf(filename,"%s", "-1");
                strncpy(socktype,"INET",80);
                argi++;
            } else if (!strcmp(argv[argi],"-Mcs")) {
                argi++;
                if (argi < argc) sprintf(filename,"%s", argv[argi]);
                else             sprintf(filename,"%s", "-1");
                strncpy(socktype,"UNIX",80);
                argi++;
            } else if (!strcmp(argv[argi],"-Mcf")) {
                argi++;
                if (argi < argc) sprintf(filename,"%s", argv[argi]);
                else             sprintf(filename,"%s", "input");
                strncpy(socktype,"FILE",80);
                argi++;
            } else {
                sprintf(filename,"%s", argv[argi]);
                strncpy(socktype,"FILE",80);
                argi++;
            }
        }
    } else if (mode == 0) {
        VJMPERR1(0);
    }

    /* startup vio */
    Vio_start();

    /* startup and shutdown the trackball rotator */
    vgl = Vgl_ctor(mode,socktype,dataform,hostname,filename,
        xsize,ysize,xpos,ypos,buildDisplayLists);
    Vgl_dtor(&vgl);

    /* stop vio */
    Vio_stop();

    /* return without error */
    return 0;

    /* return with error */
  VERROR1:
    fprintf(stderr,"\n");
    fprintf(stderr,
      "Usage: %s [ -nopanels ] [ -wpos xsize,ysize@[xmin,ymin] ]\n",PR);
    fprintf(stderr,
      "            [ -asc | -xdr ] [ -Mcs | -Mci ]\n");
    fprintf(stderr,
      "            filename | domainSocketName | inetSocketNumber\n");
    fprintf(stderr,"\n");
    fprintf(stderr,"   Parameter interpretation:\n\n");
    fprintf(stderr,"    -nopanels= for geomview compatibility (ignored)\n");
    fprintf(stderr,"    -wpos    = initial window size and location\n");
    fprintf(stderr,"    -asc     = input stream is ASC data\n");
    fprintf(stderr,"    -xdr     = input stream is XDR data (default)\n");
    fprintf(stderr,"    -Mcf     = input device is FILE (default)\n");
    fprintf(stderr,"    -Mcs     = input device is UNIX domain socket\n");
    fprintf(stderr,"    -Mci     = input device is INET network socket\n");
    fprintf(stderr,"    filename = input device filename or portnumber:\n");
    fprintf(stderr,"       If -Mcf : filename=FILE name\n");
    fprintf(stderr,"       If -Mcs : filename=UNIX domain socket name\n");
    fprintf(stderr,"       If -Mci : filename=INET socket port number\n");
    fprintf(stderr,"\n");
    return 0;
}

