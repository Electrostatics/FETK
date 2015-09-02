/*
 * ***************************************************************************
 * MC = < Manifold Code >
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
 * rcsid="$Id: gemdisp.c,v 1.10 2010/08/12 05:18:55 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     Gemdisp.c
 *
 * Purpose:  Class Gem: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "gem_p.h"

VEMBED(rcsid="$Id: gemdisp.c,v 1.10 2010/08/12 05:18:55 fetk Exp $")

/* local variables */
VPRIVATE const int MAX_COLORS = 9;
VPRIVATE double C_COLORS[9][3] = {
    { 0.0,   1.0,   0.0   },  /* g  */
    { 1.0,   0.0,   0.0   },  /* r  */
    { 0.0,   0.0,   1.0   },  /* b  */
    { 1.0,   1.0,   0.0   },  /* y  */
    { 0.0,   1.0,   1.0   },  /* c  */
    { 1.0,   0.0,   1.0   },  /* m  */
    { 1.0,   1.0,   1.0   },  /* w  */
    { 0.333, 0.333, 0.333 },  /* dg */
    { 0.666, 0.666, 0.666 }   /* lg */
};

/* comment and whitespace characters */
VPRIVATE char *MCwhiteChars = " =,;\t\n";
VPRIVATE char *MCcommChars  = "#%";

/*
 * ***************************************************************************
 * Class Gem: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_GEM)

#endif /* if !defined(VINLINE_GEM) */
/*
 * ***************************************************************************
 * Class Gem: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  Gem_writeGEOM
 *
 * Purpose:  Write a finite element mesh or mesh function in some format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeGEOM(Gem *thee, Vio *sock,
    int defKey, int colKey, int chartKey, double gluVal, int fkey,
    double *defX[MAXV], char *format)
{
    if (!strcmp(format,"GV")) {
        Gem_writeGV(thee,sock,defKey,colKey,chartKey,gluVal,fkey,defX);
    } else if (!strcmp(format,"MATH")) {
        Gem_writeMATH(thee,sock,defKey,colKey,chartKey,gluVal,fkey,defX);
    } else { VASSERT(0); }
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeSOL
 *
 * Purpose:  Write a finite element mesh or mesh function in some format.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeSOL(Gem *thee, Vio *sock,
    int fldKey, double *defX[MAXV], char *format)
{
    if (!strcmp(format,"GMV")) {
        Gem_writeGMV(thee, sock, fldKey, defX);
    } else if (!strcmp(format,"UCD")) {
        Gem_writeUCD(thee, sock, fldKey, defX);
    } else if (!strcmp(format,"DX")) {
        Gem_writeDX(thee, sock, fldKey, defX);
    } else if (!strcmp(format,"TEC")) {
        Gem_writeTEC(thee, sock, fldKey, defX);
    } else { VASSERT(0); }
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeVolHeaderOFF
 *
 * Purpose:  Produce an OFF file header for a volume mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeVolHeaderOFF(Gem *thee, Vio *sock)
{
    Vio_printf(sock,"(geometry MC_geometry { : MC_mesh })\n");
#if 0
    Vio_printf(sock,"(backcolor c0 1 1 1)\n");
#endif
    Vio_printf(sock,"(bbox-draw g1 no)\n");
    Vio_printf(sock,"(read geometry {\n");
    Vio_printf(sock,"    appearance { +edge }\n");
    Vio_printf(sock,"    define MC_mesh\n\n");
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeBndHeaderOFF
 *
 * Purpose:  Produce an OFF file header for a boundary mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeBndHeaderOFF(Gem *thee, Vio *sock)
{
    Vio_printf(sock,"(geometry MC_geometry { : MC_mesh })\n");
    Vio_printf(sock,"(read geometry {\n");
    Vio_printf(sock,"    appearance { +edge linewidth 2 }\n");
    Vio_printf(sock,"    define MC_mesh\n\n");
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeTrailerOFF
 *
 * Purpose:  Produce an OFF file trailer.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeTrailerOFF(Gem *thee, Vio *sock)
{
    Vio_printf(sock,"})\n\n");
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeGV
 *
 * Purpose:  Write out a mesh in "Geomview OFF" format to a file or socket.
 *
 * Notes:    defKey == 0  ==> draw mesh as it is
 *           defKey == 1  ==> use "def??" as new vertex coords (deformation)
 *           defKey == 2  ==> add "def??" to old vertex coords (displacement)
 *
 *           colKey == 0  ==> color simplices all same default color
 *           colKey == 1  ==> color simplices based on their chart
 *           colKey == 2  ==> color boundary simplices based on type
 *
 *           chartKey <  0  ==> draw all simplices
 *           chartKey >= 0  ==> draw only simplices with chart chartKey
 *
 *           gluVal == 1. ==> draw all simplices glued together
 *      0. < gluVal <  1. ==> draw simplices with some separation
 *
 *           defX[][MAXV] ==> vertex deformation or displacement values
 *
 *           fkey   == 0  ==> draw simplices
 *           fkey   == 1  ==> draw only simplex boundary faces
 *           fkey   == 2  ==> draw only simplices with a boundary face
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeGV(Gem *thee, Vio *sock,
    int defKey, int colKey, int chartKey, double gluVal, int fkey,
    double *defX[MAXV])
{
    int i, j, ii, jj, numVV, numSS, face, fType, gType, theDim;
    int numVVchart, numSSchart;
    double *theColor, bc[3], x[4][3], y[3];
    VV *vx;
    SS *sm;
 
    /*
     * double C_BLACK[4]     = { 0.0,   0.0,   0.0,   0.0 };
     * double C_RED[4]       = { 1.0,   0.0,   0.0,   0.0 };
     * double C_GREEN[4]     = { 0.0,   1.0,   0.0,   0.0 };
     * double C_BLUE[4]      = { 0.0,   0.0,   1.0,   0.0 };
     * double C_YELLOW[4]    = { 1.0,   1.0,   0.0,   0.0 };
     * double C_CYAN[4]      = { 0.0,   1.0,   1.0,   0.0 };
     * double C_MAGENTA[4]   = { 1.0,   0.0,   1.0,   0.0 };
     * double C_WHITE[4]     = { 1.0,   1.0,   1.0,   0.0 };
     * double C_DGREY[4]     = { 0.333, 0.333, 0.333, 0.0 };
     * double C_LGREY[4]     = { 0.666, 0.666, 0.666, 0.0 };
     *
     * double C_CLEAR[4]     = { 0.310, 0.320, 0.310, 0.0 };
     * double C_INTERIOR[4]  = { 0.0,   1.0,   0.0,   0.0 };
     */

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );
    VJMPERR2( (0. <= gluVal) && (gluVal <= 1.) );

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    theDim = Gem_dim(thee);
    if (fkey==1) {
        if (theDim == 2) {
            Gem_writeFace2dGV(thee, sock,
                defKey, colKey, chartKey, gluVal, defX);
        } else { /* (theDim == 3) */
            Gem_writeFace3dGV(thee, sock,
                defKey, colKey, chartKey, gluVal, defX);
        }
    } else {

        /* count how many simplices we will actually deal with */
        numSSchart = 0;
        for (i=0; i<Gem_numSS(thee); i++) {
            sm = Gem_SS(thee,i);

            gType = 0;
            if (theDim==2) {
                gType = SS_faceType(sm,0) + SS_faceType(sm,1)
                      + SS_faceType(sm,2);
            } else if (theDim==3) {
                gType = SS_faceType(sm,0) + SS_faceType(sm,1)
                      + SS_faceType(sm,2) + SS_faceType(sm,3);
            } else { VASSERT( 0 ); };

            if ((chartKey < 0) || ((int)SS_chart(sm) == chartKey)) {
                if ( (fkey==0) || ((fkey==2)&&(gType>0)) ) {
                    numSSchart++;
                }
            }
        }
        numVVchart = Gem_numVV(thee);

        /* determine the correct number of vertices and simplices */
        if (gluVal == 1.) {
            if (theDim==2) {
                numSS = numSSchart;
                numVV = numVVchart;
            } else {
                numSS = 4 * numSSchart;
                numVV = 1 * numVVchart;
            }
        } else {
            if (theDim==2) {
                numSS = 1 * numSSchart;
                numVV = 3 * Gem_numSS(thee);
            } else {
                numSS = 4 * numSSchart;
                numVV = 4 * Gem_numSS(thee);
            }
        }

        /* write the volume header */
        Gem_writeVolHeaderOFF(thee, sock);

        /* write out the "OFF" header */
        Vio_printf(sock,"%s\n","OFF");
        Vio_printf(sock,"%d %d %d\n", numVV, numSS, 0);

        /* normal (glued) case */
        if (gluVal == 1.) {

            /* write out the vertex data */
            ii = 0;
            for (vx=Gem_firstVV(thee);vx!=VNULL;vx=Gem_nextVV(thee)) {
                switch (defKey) {
                  case 0:
                    for (i=0;i<3;i++) 
                        y[i]=VV_coord(vx,i);
                    break;
                  case 1:
                    if (theDim==2) {
                        y[0]=VV_coord(vx,0);
                        y[1]=VV_coord(vx,1);
                        if (defX[0] != VNULL) y[2]=defX[0][ii];
                        else                  y[2]=0.;
                    } else { /* (theDim==3) */
                        for (i=0;i<3;i++) {
                            if (defX[i] != VNULL)
                                y[i]=defX[i][ii];
                            else
                                y[i]=0.;
                        }
                    }
                    break;
                  case 2:
                    if (theDim==2) {
                        for (i=0;i<2;i++) {
                            if (defX[i] != VNULL)
                                y[i]=VV_coord(vx,i)+defX[i][ii];
                            else
                                y[i]=VV_coord(vx,i);
                        }
                        y[2]=0.;
                    } else { /* (theDim==3) */
                        for (i=0;i<3;i++) {
                            if (defX[i] != VNULL)
                                y[i]=VV_coord(vx,i)+defX[i][ii];
                            else
                                y[i]=VV_coord(vx,i);
                        }
                    }
                    break;
                }
                Vio_printf(sock,"%10.3e %10.3e %10.3e\n", y[0], y[1], y[2]);
                ii++;
            }
            VASSERT( ii == numVV );

            /* write out the simplex data */
            ii = 0;
            for (sm=Gem_firstSS(thee);sm!=VNULL;sm=Gem_nextSS(thee)) {

                gType = 0;
                if (theDim==2) {
                    gType = SS_faceType(sm,0) + SS_faceType(sm,1)
                          + SS_faceType(sm,2);
                } else if (theDim==3) {
                    gType = SS_faceType(sm,0) + SS_faceType(sm,1)
                          + SS_faceType(sm,2) + SS_faceType(sm,3);
                } else { VASSERT( 0 ); };

                if ( (fkey==0) || ((fkey==2)&&(gType>0)) ) {

                    if ((chartKey < 0) || ((int)SS_chart(sm) == chartKey)) {
                        if (theDim==2) {
                            fType = 0;
                            if (colKey==1) fType = SS_chart(sm);
                            theColor = C_COLORS[ fType % MAX_COLORS ];
                            Vio_printf(sock,
                                "%d %d %d %d %4.2f %4.2f %4.2f\n",
                                3,
                                VV_id( SS_vertex(sm,0) ),
                                VV_id( SS_vertex(sm,1) ),
                                VV_id( SS_vertex(sm,2) ),
                                theColor[0], theColor[1], theColor[2]
                            );
                            ii++;
                        } else {
                            for (face=0; face<4; face++) { 
                                fType = 0;
                                if (colKey==1) fType = SS_chart(sm);
                                if (colKey==2) fType = SS_faceType(sm,face);
                                theColor = C_COLORS[ fType % MAX_COLORS ];
#if 0
                                if (SS_faceType(sm,face) != 0) {
                                    theColor = C_COLORS[ 8 ];
                                } else {
                                    theColor = C_COLORS[ 1 ];
                                }
#endif
                                Vio_printf(sock,
                                    "%d %d %d %d %4.2f %4.2f %4.2f\n",
                                    3,
                                    VV_id( SS_vertex(sm,vmapF[face][0]) ),
                                    VV_id( SS_vertex(sm,vmapF[face][1]) ),
                                    VV_id( SS_vertex(sm,vmapF[face][2]) ),
                                    theColor[0], theColor[1], theColor[2]
                                );
                                ii++;
                            }
                        }
                    }
                }
            }
#if 0
            VASSERT( ii == numSS );
#endif

        /* abnormal (un-glued) case */
        } else {

            /* write out the vertex data */
            ii = 0;
            for (sm=Gem_firstSS(thee);sm!=VNULL;sm=Gem_nextSS(thee)) {

                /* compute baricenter of this simplex */
                /* i=which vertex, j=which component */
                for (j=0; j<3; j++) {
                    bc[j] = 0.0;
                    for (i=0; i<theDim+1; i++) {
                        vx = SS_vertex(sm,i);
                        switch (defKey) {
                          case 0:
                            x[i][j]=VV_coord(vx,j);
                            break;
                          case 1:
                            if (theDim==2) {
                                if (j==2) {
                                    if (defX[0] != VNULL) 
                                        x[i][2]=defX[0][VV_id(vx)];
                                    else
                                        x[i][2]=0.;
                                } else x[i][j]=VV_coord(vx,j);
                            } else { /* (theDim==3) */
                                if (defX[j] != VNULL)
                                    x[i][j]=defX[j][VV_id(vx)];
                                else
                                    x[i][j]=0.;
                            }
                            break;
                          case 2:
                            if (theDim==2) {
                                if (j==2) x[i][2]=0.;
                                else {
                                    if (defX[j] != VNULL) 
                                        x[i][j] = VV_coord(vx,j)
                                                + defX[j][VV_id(vx)];
                                    else
                                        x[i][j] = VV_coord(vx,j);
                                }
                            } else { /* (theDim==3) */
                                if (defX[j] != VNULL)
                                    x[i][j] = VV_coord(vx,j)
                                            + defX[j][VV_id(vx)];
                                else
                                    x[i][j] = VV_coord(vx,j);
                            }
                            break;
                        }
                        bc[j] += x[i][j];
                    }
                    bc[j] /= (theDim+1.);
                }

                /* shrink the vertices and print them */
                for (i=0; i<theDim+1; i++) {
                    Vio_printf(sock,"%10.3e %10.3e %10.3e\n",
                        gluVal*x[i][0]+(1.-gluVal)*bc[0],
                        gluVal*x[i][1]+(1.-gluVal)*bc[1],
                        gluVal*x[i][2]+(1.-gluVal)*bc[2]
                    );
                    ii++;
                }
            }
#if 0
            VASSERT( ii == numVV );
#endif

            /* write out the simplex data */
            ii = 0;
            jj = 0;
            for (sm=Gem_firstSS(thee);sm!=VNULL;sm=Gem_nextSS(thee)) {

                gType = 0;
                if (theDim==2) {
                    gType = SS_faceType(sm,0) + SS_faceType(sm,1)
                          + SS_faceType(sm,2);
                } else if (theDim==3) {
                    gType = SS_faceType(sm,0) + SS_faceType(sm,1)
                          + SS_faceType(sm,2) + SS_faceType(sm,3);
                } else { VASSERT( 0 ); };

                if (theDim==2) {
                    if ((chartKey < 0) || ((int)SS_chart(sm) == chartKey)) {
                      if ( (fkey==0) || ((fkey==2)&&(gType>0)) ) {
                        fType = 0;
                        if (colKey==1) fType = SS_chart(sm);
                        theColor = C_COLORS[ fType % MAX_COLORS ];
                        Vio_printf(sock,
                            "%d %d %d %d %4.2f %4.2f %4.2f\n",
                            3,
                            jj*3+0,
                            jj*3+1,
                            jj*3+2,
                            theColor[0], theColor[1], theColor[2]
                        );
                        ii++;
                      }
                    }
                    jj++;
                } else {
                    if ((chartKey < 0) || ((int)SS_chart(sm) == chartKey)) {
                      if ( (fkey==0) || ((fkey==2)&&(gType>0)) ) {
                        for (face=0; face<4; face++) { 
                            fType = 0;
                            if (colKey==1) fType = SS_chart(sm);
                            if (colKey==2) fType = SS_faceType(sm,face);
                            theColor = C_COLORS[ fType % MAX_COLORS ];
#if 0
                            if (SS_faceType(sm,face) != 0) {
                                theColor = C_COLORS[ 8 ];
                            } else {
                                theColor = C_COLORS[ 1 ];
                            }
#endif
                            Vio_printf(sock,
                                "%d %d %d %d %4.2f %4.2f %4.2f\n",
                                3,
                                jj*4+vmapF[face][0],
                                jj*4+vmapF[face][1],
                                jj*4+vmapF[face][2],
                                theColor[0], theColor[1], theColor[2]
                            );
                            ii++;
                        }
                      }
                    }
                    jj++;
                }
            }
#if 0
            VASSERT( ii == numSS );
#endif
        }

        /* write the last line and flush any buffers */
        Vio_printf(sock,"\n");

        /* write the trailer */
        Gem_writeTrailerOFF(thee, sock);

        /* in the 2D case, go ahead and draw a skeleton boundary also */
        /* 
         * if (theDim == 2) {
         *     Gem_writeFace2dGV(thee, sock,
         *         defKey, colKey, chartKey, gluVal, defX);
         * }
         */
    }

    /* return with no errors */
    Vnm_print(0,"Gem_writeGV: Finished writing output\n");
    return; 

  VERROR1:
    Vnm_print(2,"Gem_writeGV: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeGV: Detected a problem (bailing out).\n");
    return; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeFace2dGV
 *
 * Purpose:  Write out the faces of a 2-simplex mesh as a complete and legal
 *           1-simplex mesh in "Geomview SKEL" format.
 *
 * Notes:    defKey == 0  ==> draw mesh as it is
 *           defKey == 1  ==> use "def??" as new vertex coords (deformation)
 *           defKey == 2  ==> add "def??" to old vertex coords (displacement)
 *
 *           colKey == 0  ==> color simplices all same default color
 *           colKey == 1  ==> color simplices based on their chart
 *           colKey == 2  ==> color boundary simplices based on type
 *
 *           chartKey <  0  ==> draw all simplices
 *           chartKey >= 0  ==> draw only simplices with chart chartKey
 *
 *           gluVal == 1. ==> draw all simplices glued together
 *      0. < gluVal <  1. ==> draw simplices with some separation
 *
 *           defX[][MAXV] ==> vertex deformation or displacement values
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeFace2dGV(Gem *thee, Vio *sock,
    int defKey, int colKey, int chartKey, double gluVal,
    double *defX[MAXV])
{
    int i, j, ii, jj, numVV, numSS, vType, fType, face, *vTmp;
    int numVVchart, numSSchart;
    double *theColor, bc[3], x[3][3], y[3];
    VV *vx;
    SS *sm;
 
    /*
     * double C_BLACK[4]     = { 0.0,   0.0,   0.0,   0.0 };
     * double C_RED[4]       = { 1.0,   0.0,   0.0,   0.0 };
     * double C_GREEN[4]     = { 0.0,   1.0,   0.0,   0.0 };
     * double C_BLUE[4]      = { 0.0,   0.0,   1.0,   0.0 };
     * double C_YELLOW[4]    = { 1.0,   1.0,   0.0,   0.0 };
     * double C_CYAN[4]      = { 0.0,   1.0,   1.0,   0.0 };
     * double C_MAGENTA[4]   = { 1.0,   0.0,   1.0,   0.0 };
     * double C_WHITE[4]     = { 1.0,   1.0,   1.0,   0.0 };
     * double C_DGREY[4]     = { 0.333, 0.333, 0.333, 0.0 };
     * double C_LGREY[4]     = { 0.666, 0.666, 0.666, 0.0 };
     *
     * double C_CLEAR[4]     = { 0.310, 0.320, 0.310, 0.0 };
     * double C_INTERIOR[4]  = { 0.0,   1.0,   0.0,   0.0 };
     */

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );
    VJMPERR2( (0. <= gluVal) && (gluVal <= 1.) );
    VJMPERR2( Gem_dim(thee) == 2 );

    /* count how many simplices we will actually deal with */
    numSSchart = 0;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        if ((chartKey < 0) || ((int)SS_chart(sm) == chartKey))
            for (ii=0; ii<3; ii++)
                if (VBOUNDARY( SS_faceType(sm,ii) )) numSSchart++;
    }
    numVVchart = Gem_numBV(thee);

    /* determine the correct number of vertices and simplices */
    if (gluVal == 1.) {
        numSS = numSSchart;
        numVV = numVVchart;
    } else {
        numSS = numSSchart;
        numVV = 2 * Gem_numBF(thee);
    }

    /* write the boundary header */
    Gem_writeBndHeaderOFF(thee, sock);

    /* write out the "SKEL" header */
    Vio_printf(sock,"%s\n","SKEL");
    Vio_printf(sock,"%d %d\n", numVV, numSS);

    /* normal (glued) case */
    if (gluVal == 1.) {

        vTmp = Vmem_malloc( thee->vmem, Gem_numVV(thee), sizeof(int) );

        /* write out the vertex data */
        ii = 0;
        for (vx=Gem_firstVV(thee);vx!=VNULL;vx=Gem_nextVV(thee)) {
            vType = VV_type(vx);
            if (vType >= 1) {
                switch (defKey) {
                  case 0:
                    for (i=0;i<3;i++)
                        y[i]=VV_coord(vx,i);
                    break;
                  case 1:
                    for (i=0;i<3;i++) {
                        if (defX[i] != VNULL)
                            y[i]=defX[i][VV_id(vx)];
                        else
                            y[i]=0.;
                    }
                    break;
                  case 2:
                    for (i=0;i<3;i++) {
                        if (defX[i] != VNULL)
                            y[i]=VV_coord(vx,i)+defX[i][VV_id(vx)];
                        else
                            y[i]=VV_coord(vx,i);
                    }
                    break;
                }
                vTmp[VV_id(vx)] = ii;
                Vio_printf(sock,"%10.3e %10.3e %10.3e\n", y[0], y[1], y[2]);
                ii++;
            }
        }
        VASSERT( ii == numVV );

        /* write out the simplex data */
        ii = 0;
        for (sm=Gem_firstSS(thee);sm!=VNULL;sm=Gem_nextSS(thee)) {
            if ((chartKey < 0) || ((int)SS_chart(sm) == chartKey)) {
                for (face=0; face<3; face++) { 
                    if (VBOUNDARY( SS_faceType(sm,face) )) {
                        fType = 0;
                        if (colKey==1) fType = SS_chart(sm);
                        if (colKey==2) fType = SS_faceType(sm,face);
                        theColor = C_COLORS[ fType % MAX_COLORS ];
                        Vio_printf(sock,
                            "%d %d %d %4.2f %4.2f %4.2f\n",
                            2,
                            vTmp[ VV_id( SS_vertex(sm,vmapF[face][0]) ) ],
                            vTmp[ VV_id( SS_vertex(sm,vmapF[face][1]) ) ],
                            theColor[0], theColor[1], theColor[2]
                        );
                        ii++;
                    }
                }
            }
        }
        VASSERT( ii == numSS );

        /* release the common temporary storage */
        Vmem_free( thee->vmem, Gem_numVV(thee), sizeof(int), (void**)&vTmp );

    /* abnormal (un-glued) case */
    } else {

        /* write out the vertex data */
        ii = 0;
        for (sm=Gem_firstSS(thee);sm!=VNULL;sm=Gem_nextSS(thee)) {
            for (face=0; face<3; face++) { 
                if (VBOUNDARY( SS_faceType(sm,face) )) {

                    /* compute baricenter of this face */
                    /* i=which vertex, j=which component */
                    for (j=0; j<3; j++) {
                        bc[j] = 0.0;
                        for (i=0; i<2; i++) {
                            vx = SS_vertex(sm,vmapF[face][i]);
                            switch (defKey) {
                              case 0: 
                                x[i][j]=VV_coord(vx,j);
                                break;
                              case 1: 
                                if (defX[j] != VNULL)
                                    x[i][j]=defX[j][VV_id(vx)];
                                else
                                    x[i][j]=0.;
                                break;
                              case 2:
                                if (defX[j] != VNULL)
                                    x[i][j]=VV_coord(vx,j)+defX[j][VV_id(vx)];
                                else
                                    x[i][j]=VV_coord(vx,j);
                                break;
                            }
                            bc[j] += x[i][j];
                        }
                        bc[j] /= 3.;
                    }

                    /* shrink the vertices and print them */
                    for (i=0; i<2; i++) {
                        Vio_printf(sock,"%10.3e %10.3e %10.3e\n",
                            gluVal*x[i][0]+(1.-gluVal)*bc[0],
                            gluVal*x[i][1]+(1.-gluVal)*bc[1],
                            gluVal*x[i][2]+(1.-gluVal)*bc[2]
                        );
                        ii++;
                    }
                }
            }
        }
        VASSERT( ii == numVV );

        /* write out the simplex data */
        ii = 0;
        jj = 0;
        for (sm=Gem_firstSS(thee);sm!=VNULL;sm=Gem_nextSS(thee)) {
            for (face=0; face<3; face++) { 
                if (VBOUNDARY( SS_faceType(sm,face) )) {
                    if ((chartKey < 0) || ((int)SS_chart(sm) == chartKey)) {
                        fType = 0;
                        if (colKey==1) fType = SS_chart(sm);
                        if (colKey==2) fType = SS_faceType(sm,face);
                        theColor = C_COLORS[ fType % MAX_COLORS ];
                        Vio_printf(sock,
                            "%d %d %d %4.2f %4.2f %4.2f\n",
                            2,
                            jj*2+0, jj*2+1,
                            theColor[0], theColor[1], theColor[2]
                        );
                        ii++;
                    }
                    jj++;
                }
            }
        }
        VASSERT( ii == numSS );
    }

    /* write the last line and flush any buffers */
    Vio_printf(sock,"\n");

    /* write the trailer */
    Gem_writeTrailerOFF(thee, sock);

    /* return with no errors */
    return; 

  VERROR1:
    Vnm_print(2,"Gem_writeFace2dGV: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeFace2dGV: Detected a problem (bailing out).\n");
    return; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeFace3dGV
 *
 * Purpose:  Write out the faces of a 3-simplex mesh as a complete and legal
 *           2-simplex mesh in "Geomview OFF" format.
 *
 * Notes:    defKey == 0  ==> draw mesh as it is
 *           defKey == 1  ==> use "def??" as new vertex coords (deformation)
 *           defKey == 2  ==> add "def??" to old vertex coords (displacement)
 *
 *           colKey == 0  ==> color simplices all same default color
 *           colKey == 1  ==> color simplices based on their chart
 *           colKey == 2  ==> color boundary simplices based on type
 *
 *           chartKey <  0  ==> draw all simplices
 *           chartKey >= 0  ==> draw only simplices with chart chartKey
 *
 *           gluVal == 1. ==> draw all simplices glued together
 *      0. < gluVal <  1. ==> draw simplices with some separation
 *
 *           defX[][MAXV] ==> vertex deformation or displacement values
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeFace3dGV(Gem *thee, Vio *sock,
    int defKey, int colKey, int chartKey, double gluVal,
    double *defX[MAXV])
{
    int i, j, ii, jj, numVV, numSS, vType, fType, face, *vTmp;
    int numVVchart, numSSchart;
    double *theColor, bc[3], x[3][3], y[3];
    VV *vx;
    SS *sm;
 
    /*
     * double C_BLACK[4]     = { 0.0,   0.0,   0.0,   0.0 };
     * double C_RED[4]       = { 1.0,   0.0,   0.0,   0.0 };
     * double C_GREEN[4]     = { 0.0,   1.0,   0.0,   0.0 };
     * double C_BLUE[4]      = { 0.0,   0.0,   1.0,   0.0 };
     * double C_YELLOW[4]    = { 1.0,   1.0,   0.0,   0.0 };
     * double C_CYAN[4]      = { 0.0,   1.0,   1.0,   0.0 };
     * double C_MAGENTA[4]   = { 1.0,   0.0,   1.0,   0.0 };
     * double C_WHITE[4]     = { 1.0,   1.0,   1.0,   0.0 };
     * double C_DGREY[4]     = { 0.333, 0.333, 0.333, 0.0 };
     * double C_LGREY[4]     = { 0.666, 0.666, 0.666, 0.0 };
     *
     * double C_CLEAR[4]     = { 0.310, 0.320, 0.310, 0.0 };
     * double C_INTERIOR[4]  = { 0.0,   1.0,   0.0,   0.0 };
     */

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );
    VJMPERR2( (0. <= gluVal) && (gluVal <= 1.) );
    VJMPERR2( Gem_dim(thee) == 3 );

    /* count how many simplices we will actually deal with */
    numSSchart = 0;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        if ((chartKey < 0) || ((int)SS_chart(sm) == chartKey))
            for (ii=0; ii<4; ii++)
                if (VBOUNDARY( SS_faceType(sm,ii) )) numSSchart++;
    }
    numVVchart = Gem_numBV(thee);

    /* determine the correct number of vertices and simplices */
    if (gluVal == 1.) {
        numSS = numSSchart;
        numVV = numVVchart;
    } else {
        numSS = numSSchart;
        numVV = 3 * Gem_numBF(thee);
    }

    /* write the volume header */
    Gem_writeVolHeaderOFF(thee, sock);

    /* write out the "OFF" header */
    Vio_printf(sock,"%s\n","OFF");
    Vio_printf(sock,"%d %d %d\n", numVV, numSS, 0);

    /* normal (glued) case */
    if (gluVal == 1.) {

        vTmp = Vmem_malloc( thee->vmem, Gem_numVV(thee), sizeof(int) );

        /* write out the vertex data */
        ii = 0;
        for (vx=Gem_firstVV(thee);vx!=VNULL;vx=Gem_nextVV(thee)) {
            vType = VV_type(vx);
            if (vType >= 1) {
                switch (defKey) {
                  case 0:
                    for (i=0;i<3;i++)
                        y[i]=VV_coord(vx,i);
                    break;
                  case 1:
                    for (i=0;i<3;i++) {
                        if (defX[i] != VNULL)
                            y[i]=defX[i][VV_id(vx)];
                        else
                            y[i]=0.;
                    }
                    break;
                  case 2:
                    for (i=0;i<3;i++) {
                        if (defX[i] != VNULL)
                            y[i]=VV_coord(vx,i)+defX[i][VV_id(vx)];
                        else
                            y[i]=VV_coord(vx,i);
                    }
                    break;
                }
                vTmp[VV_id(vx)] = ii;
                Vio_printf(sock,"%10.3e %10.3e %10.3e\n", y[0], y[1], y[2]);
                ii++;
            }
        }
        VASSERT( ii == numVV );

        /* write out the simplex data */
        ii = 0;
        for (sm=Gem_firstSS(thee);sm!=VNULL;sm=Gem_nextSS(thee)) {
            if ((chartKey < 0) || ((int)SS_chart(sm) == chartKey)) {
                for (face=0; face<4; face++) { 
                    if (VBOUNDARY( SS_faceType(sm,face) )) {
                        fType = 0;
                        if (colKey==1) fType = SS_chart(sm);
                        if (colKey==2) fType = SS_faceType(sm,face);
                        theColor = C_COLORS[ fType % MAX_COLORS ];
                        Vio_printf(sock,
                            "%d %d %d %d %4.2f %4.2f %4.2f\n",
                            3,
                            vTmp[ VV_id( SS_vertex(sm,vmapF[face][0]) ) ],
                            vTmp[ VV_id( SS_vertex(sm,vmapF[face][1]) ) ],
                            vTmp[ VV_id( SS_vertex(sm,vmapF[face][2]) ) ],
                            theColor[0], theColor[1], theColor[2]
                        );
                        ii++;
                    }
                }
            }
        }
        VASSERT( ii == numSS );

        /* release the common temporary storage */
        Vmem_free( thee->vmem, Gem_numVV(thee), sizeof(int), (void**)&vTmp );

    /* abnormal (un-glued) case */
    } else {

        /* write out the vertex data */
        ii = 0;
        for (sm=Gem_firstSS(thee);sm!=VNULL;sm=Gem_nextSS(thee)) {
            for (face=0; face<4; face++) { 
                if (VBOUNDARY( SS_faceType(sm,face) )) {

                    /* compute baricenter of this face */
                    /* i=which vertex, j=which component */
                    for (j=0; j<3; j++) {
                        bc[j] = 0.0;
                        for (i=0; i<3; i++) {
                            vx = SS_vertex(sm,vmapF[face][i]);
                            switch (defKey) {
                              case 0: 
                                x[i][j]=VV_coord(vx,j);
                                break;
                              case 1: 
                                if (defX[j] != VNULL)
                                    x[i][j]=defX[j][VV_id(vx)];
                                else
                                    x[i][j]=0.;
                                break;
                              case 2:
                                if (defX[j] != VNULL)
                                    x[i][j]=VV_coord(vx,j)+defX[j][VV_id(vx)];
                                else
                                    x[i][j]=VV_coord(vx,j);
                                break;
                            }
                            bc[j] += x[i][j];
                        }
                        bc[j] /= 3.;
                    }

                    /* shrink the vertices and print them */
                    for (i=0; i<3; i++) {
                        Vio_printf(sock,"%10.3e %10.3e %10.3e\n",
                            gluVal*x[i][0]+(1.-gluVal)*bc[0],
                            gluVal*x[i][1]+(1.-gluVal)*bc[1],
                            gluVal*x[i][2]+(1.-gluVal)*bc[2]
                        );
                        ii++;
                    }
                }
            }
        }
        VASSERT( ii == numVV );

        /* write out the simplex data */
        ii = 0;
        jj = 0;
        for (sm=Gem_firstSS(thee);sm!=VNULL;sm=Gem_nextSS(thee)) {
            for (face=0; face<4; face++) { 
                if (VBOUNDARY( SS_faceType(sm,face) )) {
                    if ((chartKey < 0) || ((int)SS_chart(sm) == chartKey)) {
                        fType = 0;
                        if (colKey==1) fType = SS_chart(sm);
                        if (colKey==2) fType = SS_faceType(sm,face);
                        theColor = C_COLORS[ fType % MAX_COLORS ];
                        Vio_printf(sock,
                            "%d %d %d %d %4.2f %4.2f %4.2f\n",
                            3,
                            jj*3+0, jj*3+1, jj*3+2,
                            theColor[0], theColor[1], theColor[2]
                        );
                        ii++;
                    }
                    jj++;
                }
            }
        }
        VASSERT( ii == numSS );
    }

    /* write the last line and flush any buffers */
    Vio_printf(sock,"\n");

    /* write the trailer */
    Gem_writeTrailerOFF(thee, sock);

    /* return with no errors */
    return; 

  VERROR1:
    Vnm_print(2,"Gem_writeFace3dGV: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeFace3dGV: Detected a problem (bailing out).\n");
    return; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeHeaderMATH
 *
 * Purpose:  Produce an MATH file header for a volume mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeHeaderMATH(Gem *thee, Vio *sock)
{
    Vio_printf(sock,"Graphics3D[{\n");
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeTrailerMATH
 *
 * Purpose:  Produce an MATH file trailer.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeTrailerMATH(Gem *thee, Vio *sock)
{
    Vio_printf(sock,"\n");
    Vio_printf(sock,"},\n");
    Vio_printf(sock,"{\n");
    Vio_printf(sock,"  Boxed->False,\n");
    Vio_printf(sock,"  Background->GrayLevel[1],\n");
    Vio_printf(sock,"  ViewPoint->{-0.0, 0.0, 3.0},\n");
    Vio_printf(sock,"  ViewVertical->{0.0, 3.0, 0.0}\n");
    Vio_printf(sock,"}\n");
    Vio_printf(sock,"]\n");
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeMATH
 *
 * Purpose:  Write out a mesh in "Mathematica" format to a file or socket.
 *
 * Notes:    defKey == 0  ==> draw mesh as it is
 *           defKey == 1  ==> use "def??" as new vertex coords (deformation)
 *           defKey == 2  ==> add "def??" to old vertex coords (displacement)
 *
 *           colKey == 0  ==> color simplices all same default color
 *           colKey == 1  ==> color simplices based on their chart
 *           colKey == 2  ==> color boundary simplices based on type
 *
 *           chartKey <  0  ==> draw all simplices
 *           chartKey >= 0  ==> draw only simplices with chart chartKey
 *
 *           gluVal == 1. ==> draw all simplices glued together
 *      0. < gluVal <  1. ==> draw simplices with some separation
 *
 *           defX[][MAXV] ==> vertex deformation or displacement values
 *
 *           fkey   == 0  ==> draw simplices
 *           fkey   == 1  ==> draw only simplex boundary faces
 *           fkey   == 2  ==> draw only simplices with a boundary face
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeMATH(Gem *thee, Vio *sock,
    int defKey, int colKey, int chartKey, double gluVal, int fkey,
    double *defX[MAXV])
{
    int i, j, k, theDim, theDimII, iface;
    double bc[3], x[4][3];
    VV *vx;
    SS *sm;
 
    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );
    VJMPERR2( (0. <= gluVal) && (gluVal <= 1.) );

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    theDim   = Gem_dim(thee);
    theDimII = Gem_dimII(thee);

    VASSERT( (theDim   == 2) || (theDim == 3) );
    VASSERT( (theDimII == 3) );

    if ((fkey==1) && (theDim == 3)) {
#if 0
        Gem_writeFace3dMATH(thee, sock,
            defKey, colKey, chartKey, gluVal, defX);
#endif
    } else {

        /* write the MATH header */
        Gem_writeHeaderMATH(thee, sock);

        /* write out the simplex data */
        for (i=0; i<Gem_numSS(thee); i++) {
            sm = Gem_SS(thee,i);

            if (theDim == 2) {

                /* compute baricenter of this face */
                /* k=which vertex, j=which component */
                for (j=0; j<3; j++) {
                    bc[j] = 0.0;
                    for (k=0; k<3; k++) {
                        vx = SS_vertex(sm,k);
                        x[k][j]=VV_coord(vx,j);
                        bc[j] += x[k][j];
                    }
                    bc[j] /= 3.;
                }

                /* print the polygons */
                Vio_printf(sock,"Polygon[{\n");
                for (j=0; j<3; j++) {
                    Vio_printf(sock,"    { %17.10le, %17.10le, %17.10le }",
                        gluVal*x[j][0]+(1.-gluVal)*bc[0],
                        gluVal*x[j][1]+(1.-gluVal)*bc[1],
                        gluVal*x[j][2]+(1.-gluVal)*bc[2]
                    );
                    if (j < 2) {
                        Vio_printf(sock,",\n");
                    }
                }
                Vio_printf(sock,"\n}]");
                if (i < (Gem_numSS(thee)-1)) {
                    Vio_printf(sock,",\n");
                }

            } else { /* (theDim == 3) */

                /* compute baricenter of this face */
                /* k=which vertex, j=which component */
                for (j=0; j<3; j++) {
                    bc[j] = 0.0;
                    for (k=0; k<4; k++) {
                        vx = SS_vertex(sm,k);
                        x[k][j]=VV_coord(vx,j);
                        bc[j] += x[k][j];
                    }
                    bc[j] /= 4.;
                }

                /* print the polygons */
                for (iface=0; iface<4; iface++) {
                    Vio_printf(sock,"Polygon[{\n");
                    for (j=0; j<3; j++) {
                        Vio_printf(sock,
                            "    { %17.10le, %17.10le, %17.10le }",
                            gluVal*x[vmapF[iface][j]][0]+(1.-gluVal)*bc[0],
                            gluVal*x[vmapF[iface][j]][1]+(1.-gluVal)*bc[1],
                            gluVal*x[vmapF[iface][j]][2]+(1.-gluVal)*bc[2]
                        );
                        if (j < 2) {
                            Vio_printf(sock,",\n");
                        }
                    }
                    Vio_printf(sock,"\n}]");
                    if ( (iface<3) || (i < (Gem_numSS(thee)-1)) ) {
                        Vio_printf(sock,",\n");
                    }
                }
            }
        }

    }

    /* write the trailer */
    Gem_writeTrailerMATH(thee, sock);

    /* return with no errors */
    Vnm_print(0,"Gem_writeMATH: Finished writing output\n");
    return; 

  VERROR1:
    Vnm_print(2,"Gem_writeMATH: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeMATH: Detected a problem (bailing out).\n");
    return; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeGMV
 *
 * Purpose:  Write out a scalar or vector function over a simplex mesh 
 *           in "GMV" (General Mesh Viewer) format.
 *
 * Notes:    fldKey == 0  ==> draw mesh as it is
 *           fldKey == 1  ==> write field[] as a scalar field over the mesh
 *           fldKey == 2  ==> write field[] as a 2-vector field over the mesh
 *           fldKey == 3  ==> write field[] as a 3-vector field over the mesh
 *           fldKey == 4  ==> etc
 *
 *           defX[][MAXV] ==> possible scalar or vector field
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeGMV(Gem *thee, Vio *sock,
    int fldKey, double *defX[MAXV])
{
    int i, j, k, vec, dim, dimII, dimVV, numVV, numSS;
    double value;
    VV *vx;
    SS *sm;

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );

    /* number of boundary vertices and faces */
    vec   = fldKey;
    dim   = Gem_dim(thee);
    dimII = Gem_dimII(thee);
    dimVV = Gem_dimVV(thee);
    numVV = Gem_numVV(thee);
    numSS = Gem_numSS(thee);

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    /* write out the header */
    Vio_printf(sock,"%s\n\n","gmvinput ascii");

    /* write out the vertices */
    Vio_printf(sock,"nodes %d\n", numVV);
    for (j=0; j<dimII; j++) {
        for (i=0; i<numVV; i++) {
            vx = Gem_VV(thee,i);
            Vio_printf(sock, " %13.6e", VV_coord(vx,j) );
        }
        Vio_printf(sock,"\n");
    }

    /* write out the simplices */
    Vio_printf(sock,"\n%s %d\n", "cells", numSS);
    for (i=0; i<numSS; i++) {
        sm = Gem_SS(thee,i);
        if (dim == 2) {
            Vio_printf(sock,"%s","tri 3   ");
        } else {
            Vio_printf(sock,"%s","tet 4   ");
        }
        for (j=0; j<dimVV; j++) {
            Vio_printf(sock," %d",VV_id(SS_vertex(sm,j))+1 );
        }
        Vio_printf(sock,"\n");
    }

    /* node and cell fields */
    Vio_printf(sock,"\n%s\n\n","variable");

    /* write out the node-field */
    for (j=0; j<vec; j++) {
        Vio_printf(sock,"node_%d 1\n",j);
        for (i=0; i<numVV; i++)
            Vio_printf(sock, " %13.6e", defX[j][i]);
        Vio_printf(sock,"\n");
    }
    Vio_printf(sock,"\n");

    /* write out the cell-field */
    for (j=0; j<vec; j++) {
        Vio_printf(sock, "cell_%d 0\n", j);
        for (i=0; i<numSS; i++) {
            sm = Gem_SS(thee,i);
            value = 0.;
            for (k=0; k<dimVV; k++)
                value += defX[j][ VV_id( SS_vertex(sm,k) ) ];
            value /= dimVV;
            Vio_printf(sock, " %13.6e", value);
        }
        Vio_printf(sock,"\n");
    }
    Vio_printf(sock,"\n%s\n\n","endvars");

    /* write out the trailer */
    Vio_printf(sock,"%s\n\n","endgmv");

    /* return with no errors */
    Vnm_print(0,"Gem_writeGMV: Finished writing output\n");
    return; 

  VERROR1:
    Vnm_print(2,"Gem_writeGMV: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeGMV: Detected a problem (bailing out).\n");
    return; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeUCD
 *
 * Purpose:  Write out a scalar or vector function over a simplex mesh
 *           in "UCD" (Unstructured Cell Data) format for AVS 5.0
 *
 * Notes:    fldKey == 0  ==> draw mesh as it is
 *           fldKey == 1  ==> write field[] as a scalar field over the mesh
 *           fldKey == 2  ==> write field[] as a 2-vector field over the mesh
 *           fldKey == 3  ==> write field[] as a 3-vector field over the mesh
 *           fldKey == 4  ==> etc
 *
 *           defX[][MAXV] ==> possible scalar or vector field
 *
 * Format:   Our particular use of the UCD format is as follows
 *
 *           PART 1.1: [# NODES] [# CELLS] [DIM NODEDAT] [DIM CELLDAT] [0]
 *           PART 1.2: [NODE ID] [X COORD] [Y COORD] [Z COORD]
 *                     (REPEATED FOR EACH NODE)
 *           PART 1.3: [CELL ID] [MATERIAL] [CELL TYPE] [LIST OF NODE IDS]
 *                     (REPEATED FOR EACH CELL)
 *           PART 2.1: [NUM NODE FIELD COMPONENTS] [LIST OF COMPONENT SIZES]
 *           PART 2.2: [COMPONENT LABEL], [COMPONENT UNITS]
 *                     (REPEATED FOR EACH NODE DATA COMPONENT)
 *           PART 2.3: [NODE ID] [DATA VALUES]
 *                     (REPEATED FOR EACH NODE)
 *
 *           PART 3.1: [NUM CELL FIELD COMPONENTS] [LIST OF COMPONENT SIZES]
 *           PART 3.2: [COMPONENT LABEL], [COMPONENT UNITS]
 *                     (REPEATED FOR EACH CELL DATA COMPONENT)
 *           PART 3.3: [CELL ID] [DATA VALUES]
 *                     (REPEATED FOR EACH CELL)
 *
 *
 * Author:   Amit Majumdar and Stephen Bond
 *           (created using Mike Holst's Gem_writeGMV as template)
 * ***************************************************************************
 */
VPUBLIC void Gem_writeUCD(Gem *thee, Vio *sock,
    int fldKey, double *defX[MAXV])
{
    int i, j, k, vec, dim, dimII, dimVV, numVV, numSS;
    double value;
    VV *vx;
    SS *sm;

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );

    /* number of boundary vertices and faces */
    vec   = fldKey;
    dim   = Gem_dim(thee);
    dimII = Gem_dimII(thee);
    dimVV = Gem_dimVV(thee);
    numVV = Gem_numVV(thee);
    numSS = Gem_numSS(thee);

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    /* write out the header */
    Vio_printf(sock, "%d %d %d %d %d\n", numVV, numSS, vec, vec, 0);
    /* # vert, # simp, dim node-data, dim cell-data, dim model-data */

    /* write out the vertices */
    for (i=0; i<numVV; i++) {
        Vio_printf(sock,"%d", i+1);
        for (j=0; j<dimII; j++) {
            vx = Gem_VV(thee,i);
            Vio_printf(sock, " %13.6e", VV_coord(vx,j) );
        }
        Vio_printf(sock,"\n");
    }

    /* write out the simplices */
    for (i=0; i<numSS; i++) {
        sm = Gem_SS(thee,i);
        if (dim == 2) {
            Vio_printf(sock,"%d %d %s", i+1, SS_type(sm), "tri");
        } else {
            Vio_printf(sock,"%d %d %s", i+1, SS_type(sm), "tet");
        }
        for (j=0; j<dimVV; j++) {
            Vio_printf(sock," %d",VV_id(SS_vertex(sm,j))+1 );
        }
        Vio_printf(sock,"\n");
    }

    if ( fldKey ) {
        /* write out the node-field */
        Vio_printf(sock,"%d %d\n", 1, vec);
        for (j=0; j<vec; j++) {
            Vio_printf(sock,"%s, %s\n","nodedata","dimensionless");
        }
        for (i=0; i<numVV; i++) {
            Vio_printf(sock,"%d",i+1);
            for (j=0; j<vec; j++) {
	        Vio_printf(sock, " %13.6e", defX[j][i]);
	    }
            Vio_printf(sock,"\n");
        }

        /* write out the cell-field */
        Vio_printf(sock,"%d %d\n", 1, vec);
        for (j=0; j<vec; j++) {
            Vio_printf(sock,"%s, %s\n","celldata","dimensionless");
        }
        for (i=0; i<numSS; i++) {
            Vio_printf(sock,"%d",i+1);
	    sm = Gem_SS(thee,i);
            for (j=0; j<vec; j++) {
                value = 0.0;
		for (k=0; k<dimVV; k++)
                    value += defX[j][ VV_id( SS_vertex(sm,k) ) ];
		value /= dimVV;
	        Vio_printf(sock, " %13.6e", value);
	    }
            Vio_printf(sock,"\n");
        }
    }

    /* return with no errors */
    Vnm_print(0,"Gem_writeUCD: Finished writing output\n");
    return;

  VERROR1:
    Vnm_print(2,"Gem_writeUCD: Problem with I/O socket.\n");
  VERROR2:
    Vnm_print(2,"Gem_writeUCD: Detected a problem (bailing out).\n");
    return;
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeDX
 *
 * Purpose:  Write out a scalar or vector function over a simplex mesh
 *           in "DX" (www.opendx.org) format.
 *
 * Notes:    fldKey == 0  ==> draw mesh as it is
 *           fldKey == 1  ==> write field[] as a scalar field over the mesh
 *           fldKey == 2  ==> write field[] as a 2-vector field over the mesh
 *           fldKey == 3  ==> write field[] as a 3-vector field over the mesh
 *           fldKey == 4  ==> etc
 *
 *           defX[][MAXV] ==> possible scalar or vector field
 *
 * Author:   Nathan Baker, Stephen Bond, and Michael Holst
 *           (created using Gem_writeGMV as template)
 * ***************************************************************************
 */
VPUBLIC void Gem_writeDX(Gem *thee, Vio *sock,
    int fldKey, double *defX[MAXV])
{
    int i, j, vec, dimII, dimVV, numVV, numSS;
    double val;
    VV *vx;
    SS *sm;

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );

    /* number of boundary vertices and faces */
    vec   = fldKey;
    dimII = Gem_dimII(thee);
    dimVV = Gem_dimVV(thee);
    numVV = Gem_numVV(thee);
    numSS = Gem_numSS(thee);

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    /* write out the vertices */
    Vio_printf(sock,"\n%s\n","## Vertices");
    Vio_printf(sock,"%s %d %s %s %s %d %s %d %s %d\n",
	       "object", 1, "class array", "type float", "rank", 1,
	       "shape", dimII, "items", numVV);
    Vio_printf(sock,"data follows\n");

    for (i=0; i<numVV; i++) {
      for (j=0; j<dimII; j++) {
            vx = Gem_VV(thee,i);
            val = (VABS(VV_coord(vx,j)) >= VSMALL) ? VV_coord(vx,j) : 0.0;
            Vio_printf(sock, "%13.6e ", val );
      }
      Vio_printf(sock,"\n");
    }

    /* write out the simplices */
    Vio_printf(sock,"\n%s\n","## Simplices");
    Vio_printf(sock,"%s %d %s %s %s %d %s %d %s %d\n",
	       "object", 2, "class array", "type int", "rank", 1,
	       "shape", dimVV, "items", numSS);
    Vio_printf(sock,"data follows\n");
    for (i=0; i<numSS; i++) {
        sm = Gem_SS(thee,i);
        for (j=0; j<dimVV; j++) {
            Vio_printf(sock," %d",VV_id(SS_vertex(sm,j)));
        }
        Vio_printf(sock,"\n");
    }
    if (dimVV == 3) {
      Vio_printf(sock,"attribute \"element type\" string \"triangles\"\n");
      Vio_printf(sock,"attribute \"ref\" string \"positions\"\n");
    } else if (dimVV == 4) {
      Vio_printf(sock,"attribute \"element type\" string \"tetrahedra\"\n");
      Vio_printf(sock,"attribute \"ref\" string \"positions\"\n");
    }

    /* write out the node-field */
    if ( fldKey ) {
        Vio_printf(sock,"\n%s\n","## Node field");
        if ( vec == 1 ) {
            Vio_printf(sock,"%s %d %s %s %s %d %s %d\n",
	        "object", 3, "class array", "type float", "rank", 0,
	        "items", numVV);
            Vio_printf(sock,"data follows\n");
        } else {
            Vio_printf(sock,"%s %d %s %s %s %d %s %d %s %d\n",
	        "object", 3, "class array", "type float", "rank", 1,
	        "shape", vec, "items", numVV);
            Vio_printf(sock,"data follows\n");
        }
        for (i=0; i<numVV; i++) {
          for (j=0; j<vec; j++) {
            val = (VABS(defX[j][i]) >= VSMALL) ? defX[j][i] : 0.0;
	    Vio_printf(sock, " %13.6e", val );
          }
          Vio_printf(sock,"\n");
        }
        Vio_printf(sock,"attribute \"dep\" string \"positions\"\n\n");
    }

    /* define the data object */
    Vio_printf(sock,"object \"irregular positions irregular connections\" ");
    Vio_printf(sock,"class field\n");
    Vio_printf(sock,"component \"positions\" value %d\n",1);
    Vio_printf(sock,"component \"connections\" value %d\n",2);
    if ( fldKey ) {
        Vio_printf(sock,"component \"data\" value %d\n",3);
    }

    /* write out the trailer */
    Vio_printf(sock,"end\n");

    /* return with no errors */
    Vnm_print(0,"Gem_writeDX: Finished writing output\n");
    return;

  VERROR1:
    Vnm_print(2,"Gem_writeDX: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeDX: Detected a problem (bailing out).\n");
    return;
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeTEC
 *
 * Purpose:  Write out a scalar or vector function over a simplex mesh
 *           in "TEC" (www.opendx.org) format.
 *
 * Notes:    fldKey == 0  ==> draw mesh as it is
 *           fldKey == 1  ==> write field[] as a scalar field over the mesh
 *           fldKey == 2  ==> write field[] as a 2-vector field over the mesh
 *           fldKey == 3  ==> write field[] as a 3-vector field over the mesh
 *           fldKey == 4  ==> etc
 *
 *           defX[][MAXV] ==> possible scalar or vector field
 *
 * Author:   Stephen Bond, Jason Suen, and Michael Holst
 *           (created using Gem_writeGMV as template)
 * ***************************************************************************
 */
VPUBLIC void Gem_writeTEC(Gem *thee, Vio *sock,
    int fldKey, double *defX[MAXV])
{
    char str1[10], str2[10];
    int i, j, vec, dim, dimII, dimVV, numVV, numSS;
    VV *vx;
    SS *sm;

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );

    /* number of boundary vertices and faces */
    vec   = fldKey;
    dim   = Gem_dim(thee);
    dimII = Gem_dimII(thee);
    dimVV = Gem_dimVV(thee);
    numVV = Gem_numVV(thee);
    numSS = Gem_numSS(thee);

    /* create some temporary strings here */
    if( dimVV == 3 ) {
        sprintf(str1,"TRIANGLES");
        sprintf(str2,"TRIANGLE");
    } else if ( dimVV == 4 ) {
        sprintf(str1,"TETRAHEDRA");
        sprintf(str2,"TETRAHEDRON");
    } else {
        VJMPERR3( 0 );
    }

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    /* write some header information */
    Vio_printf(sock,"\nTITLE = \"%s\"\n","FETk Problem");
    Vio_printf(sock,"VARIABLES =");
    for(j=0; j<dim; j++) {
        Vio_printf(sock," \"x%d\"",j+1);
    }
    for(j=0; j<vec; j++) {
        Vio_printf(sock," \"u%d\"",j+1);
    }
    Vio_printf(sock,"\n");

    Vio_printf(sock,"ZONE T=\"%s\", N=%d, E=%d, ",str1, numVV, numSS);
    Vio_printf(sock,"F=FEPOINT, ET=\"%s\"\n",str2);

    /* write out the vertices and solution*/
    for (i=0; i<numVV; i++) {
      for (j=0; j<dim; j++) {
            vx = Gem_VV(thee,i);
            Vio_printf(sock, "%13.6e ", VV_coord(vx,j) );
      }
      for (j=0; j<vec; j++) {
          Vio_printf(sock, "%13.6e ", defX[j][i]);
      }
      Vio_printf(sock,"\n");
    }

    /* write out the simplices */
    for (i=0; i<numSS; i++) {
        sm = Gem_SS(thee,i);
        for (j=0; j<dimVV; j++) {
            Vio_printf(sock," %d",VV_id(SS_vertex(sm,j))+1);
        }
        Vio_printf(sock,"\n");
    }

    /* return with no errors */
    Vnm_print(0,"Gem_writeTEC: Finished writing output\n");
    return;

  VERROR1:
    Vnm_print(2,"Gem_writeTEC: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeTEC: Detected a problem (bailing out).\n");

  VERROR3:
    Vnm_print(2,"Gem_writeTEC: Dimension not supported\n");
    return;
}
