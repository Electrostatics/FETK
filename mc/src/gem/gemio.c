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
 * rcsid="$Id: gemio.c,v 1.24 2010/08/12 05:18:57 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     Gemio.c
 *
 * Purpose:  Class Gem: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "gem_p.h"

VEMBED(rcsid="$Id: gemio.c,v 1.24 2010/08/12 05:18:57 fetk Exp $")

/* comment and whitespace characters */
VPRIVATE char *MCwhiteChars = " =,;\t\n";
VPRIVATE char *MCcommChars  = "#%";

/* the MC copyright */
/* (NOTE: Only 509 char-length constant strings supported in ISO C) */
VPRIVATE char *MCcopyRightPCT1 = 
"%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\
%%% MC = < Manifold Code >\n\
%%% Copyright (C) 1994-- Michael Holst\n\
%%%\n";

VPRIVATE char *MCcopyRightPCT2 = 
"%%% This program is free software; you can redistribute it and/or modify it\n\
%%% under the terms of the GNU General Public License as published by the\n\
%%% Free Software Foundation; either version 2 of the License, or (at your\n\
%%% option) any later version.\n\
%%%\n";

VPRIVATE char *MCcopyRightPCT3 = 
"%%% This program is distributed in the hope that it will be useful,\n\
%%% but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
%%% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\
%%% See the GNU General Public License for more details.\n\
%%%\n";

VPRIVATE char *MCcopyRightPCT4 = 
"%%% You should have received a copy of the GNU General Public License along\n\
%%% with this program; if not, write to the Free Software Foundation, Inc.,\n\
%%% 675 Mass Ave, Cambridge, MA 02139, USA.\n\
%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";

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
 * Routine:  Gem_read
 *
 * Purpose:  Read in the user-specified initial vertex-simplex mesh.
 *           provided to us in MC-Simplex-Format (MCSF), and transform
 *           into our internal datastructures.
 *
 * Parms:    key          ==> input format type
 *                                key=0 ==> simplex format
 *                                key=1 ==> edge format
 *                                key=2 ==> simplex-nabor format
 *
 * Notes: The user provides the following information about a domain and an
 *        initial simplex-triangulation:
 *
 *        D = DIMENSION  = spatial dimension of problem (1, 2, or 3)
 *        N = NVERTICES  = total number of vertices in mesh
 *        L = NSIMPLICES = total number of simplices in the mesh
 *
 *        double vertex* = List of all vertex coordinates in the form:
 *
 *        vertex[ N * (3+D) ] = {
 *            { id1, chart1, v1_x1, ..., v1_xD },
 *            { id2, chart2, v2_x1, ..., v2_xD },
 *                          ...
 *            { idN, chartN, vN_x1, ..., vN_xD }
 *        }
 *
 *        Here, vj_xk is the kth component (float or double) of the vertex 
 *        with global vertex number j.  The "idj" flag is a 32-bit integer 
 *        "name" for vertex j, "chartj" is a 32-bit number representing the
 *        "chart" with which to interpret the coordinates vj_xk, in the sense
 *        of the charts of an atlas of manifold domain.
 *
 *        int simplex* = List of all simplices by vertex number in the form:
 *
 *        simplex[ L * (2 + 2*(D+1)) ] = {
 *            { id1, g1, m1, f1_1, ..., f1_{D+1}, s1_v1, ..., s1_v{D+1} },
 *            { id2, g2, m2, f2_1, ..., f2_{D+1}, s2_v1, ..., s2_v{D+1} },
 *                                  ...
 *            { idL, gL, mL, fL_1, ..., f2_{D+1}, sL_v1, ..., sL_v{D+1} }
 *        }
 *
 *        Here, sj_vk is a 32-bit integer giving the global vertex number
 *        making up the kth vertex of the simplex with global number j.  The
 *        "idj" flag is a 32-bit integer "name" for simplex j, "gj" is a
 *        32-bit group number associated with simplex j (for grouping subsets
 *        of simplices together for various reasons), "mj" is a 32-bit integer
 *        containing the information about the simplex j such as its material
 *        type, and "fj_k" is a 32-bit integer containing the information 
 *        about each face k of simplex j such as their boundary types (each 
 *        face opposite vertex k in simplex j).
 *
 *        Thus, in 2D, a simplex (triangle) is specified by 3 consecutive 
 *        vertex numbers, and in 3D a simplex (tetrahedra) is specified by 4 
 *        consecutive vertex numbers.  The physical coordinates of any vertex
 *        k in the simplex array are given in the vertex array in the
 *        appropriate row of the array.
 *
 *        NOTE: The ordering of the vertices in a simplex is *extremely* 
 *        important here; see the note below.
 *
 * Ordering of the vertices in a simplex:
 *
 *    1D: Well, this is pretty straight-forward; we will order the vertices
 *        from left-to-right in each simplex; this will produce the correct
 *        sign in integration by parts.
 *
 *    2D: All closed triangles must be specified by three consecutive vertices
 *        in simplex and must be counter-clockwise-ordered by their vertices,
 *        as seen from the "up" side of the 2D body/shell/surface.  This 
 *        produces the correct surface-normals from the right-hand-rule for 
 *        surface (line in 2D) integrals.
 *
 *    3D: All closed tetrahedra must be specified by four consecutive vertices
 *        in "simplex" in the following way:  The first three vertices must 
 *        represent any one of the four faces as a counter-clockwise-ordered 
 *        triangle, as seen from INSIDE the tetrahedra.  I.e., you can think
 *        about this first triangle as lying in the plane, and you are 
 *        standing on the plane looking down at it. The fourth vertex 
 *        specified following the first three in the simplex is then some 
 *        height above the plane containing the first counter-clockwise 
 *        ordered triangle.  This specification allows the remaining three
 *        (of the four) triangles making up any tetrahedra to be correctly 
 *        specified in a counter-clockwise, inward-facing manner, so that the
 *        correct surface-normals can be calculated consistently.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_read(Gem *thee, int key, Vio *sock)
{
    int i, j, theDim, theDimII, inum;
    int numVV, indexV, chartV;
    int numSS, indexS, groupS, materialS, faceTypeS[4], sv[4];
    int vnum, vtp, vtpI;
    int fnum[3], ftp[3], ftpB[3];
    double x[3];
    char tok[VMAX_BUFSIZE];
    VV *vx;
    SS *sm;

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (0<=key) && (key<=2) );

    if (key == 1) {
        return Gem_readEdge(thee,sock);
    } else if (key == 2) {
        Vnm_print(2,"Gem_read: Cannot handle simplex-nabor format\n");
        VJMPERR2( 0 );
    }

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    /* get the "mcsf_begin=1" tag */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"mcsf_begin") );
    VJMPERR2( 1==Vio_scanf(sock,"%d",&inum) );
    VJMPERR2( inum == 1 );

    /* read the intrinsic dimension */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"dim") );
    VJMPERR2( 1==Vio_scanf(sock,"%d",&theDim) );
    VJMPERR2( (theDim == 2) || (theDim == 3) );

    /* read the imbedding dimension */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"dimii") );
    VJMPERR2( 1==Vio_scanf(sock,"%d",&theDimII) );
    VJMPERR2( (theDimII == 2) || (theDimII == 3) );

    /* read and set the number of vertices information */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"vertices") );
    VJMPERR2( 1==Vio_scanf(sock,"%d",&numVV) );
    thee->numVV0 = numVV;

    /* read and set the number of simplices information */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"simplices") );
    VJMPERR2( 1==Vio_scanf(sock,"%d",&numSS) );

    /* reset ourself to handle the new manifold dimensions */
    Vnm_print(0,"Gem_read: theDim=%d, theDimII=%d, numVV=%d, numSS=%d\n",
        theDim, theDimII, numVV, numSS);
    Vnm_print(0,"Gem_read: Reseting manifold structures.\n");
    Gem_reset( thee, theDim, theDimII );

    /* read in the vertices */
    Vnm_print(0,"Gem_read: Reading ..vertices..");
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"vert") );
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"[") );
    for (i=0; i<numVV; i++) {

        /* grab the three integer info fields */
        VJMPERR2( 1==Vio_scanf(sock,"%d",&indexV) );
        VJMPERR2( 1==Vio_scanf(sock,"%d",&chartV) );

        /* grab the "dimii" coordinates */
        for (j=0; j<theDimII; j++)
            VJMPERR2( 1==Vio_scanf(sock,"%le",&x[j]) );

        /* trivially embed any 2D coordinates into 3D */
        if (theDimII == 2) x[2] = 0.;

        /* create the new vertex */
        vx = Gem_createAndInitVV(thee);
        VV_setReality(vx, 0);
        VV_setDim(vx, theDim);
        VV_setClass(vx, 0);
        VV_setType(vx, 0);
        VV_setId(vx, i);
        VV_setChart(vx, chartV);

        /* set the vertex coordinates */
        for (j=0; j<3; j++)
            VV_setCoord(vx, j, x[j]);
    }
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"]") );

    /* read in the simplices */
    Vnm_print(0,"..simplices..");
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"simp") );
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"[") );
    for (i=0; i<numSS; i++) {

        /* grab the three integer info fields */
        VJMPERR2( 1==Vio_scanf(sock,"%d",&indexS) );
        VJMPERR2( 1==Vio_scanf(sock,"%d",&groupS) );
        VJMPERR2( 1==Vio_scanf(sock,"%d",&materialS) );

        /* grab the "dim+1" face types */
        for (j=0; j<theDim+1; j++)
            VJMPERR2( 1==Vio_scanf(sock,"%d",&faceTypeS[j]) );

        /* grab the "dim+1" vertex numbers */
        for (j=0; j<theDim+1; j++)
            VJMPERR2( 1==Vio_scanf(sock,"%d",&sv[j]) );

        /* create the new simplex */
        sm = Gem_createAndInitSS(thee);
        SS_setReality(sm, 0);
        SS_setDim(sm, theDim);
        SS_setClass(sm, theDim);
        SS_setType(sm, materialS);
        SS_setId(sm, i); 
        SS_setChart(sm, groupS); 

        /* set the simplex face types and vertex labels */
        for (j=0; j<theDim+1; j++) {
            SS_setFaceType( sm, j, faceTypeS[j] );
            if (VBOUNDARY( faceTypeS[j] )) {
                (thee->numBF)++;
            }
            vx = Gem_VV(thee, sv[j] );
            SS_setVertex( sm, j, vx );
        }

        /* calculate (our contribution to) vertex types from our face types */
        for (j=0; j<theDim+1; j++) {

            /* get the vertex in question */
            vnum = j;
            vx = SS_vertex( sm, vnum );

            /* get face numbers of two/three faces which touch vertex vnum */
            fnum[0] = vmapOV3[vnum][0];
            fnum[1] = vmapOV3[vnum][1];
            fnum[2] = vmapOV3[vnum][2];  /* 2D: third face always interior */

            /* some shorthand notation... */
            vtp     = VV_type(vx);
            vtpI    = VINTERIOR( VV_type(vx) );
            ftp[0]  = SS_faceType(sm,fnum[0]);
            ftp[1]  = SS_faceType(sm,fnum[1]);
            ftp[2]  = SS_faceType(sm,fnum[2]);
            ftpB[0] = VBOUNDARY( SS_faceType(sm,fnum[0]) );
            ftpB[1] = VBOUNDARY( SS_faceType(sm,fnum[1]) );
            ftpB[2] = VBOUNDARY( SS_faceType(sm,fnum[2]) );

            /* if any of the faces are Boundary, then mark vertex Boundary */
            if ( ftpB[0] || ftpB[1] || ftpB[2] ) {

                /* deal with existing vertex type */
                if (vtpI) {
                    (thee->numBV)++;
                } else {
                    /* this is okay; may already be boundary */
                }

                /* okay, determine max boundary flag (including vtp) */
                if (ftpB[0]) vtp = VMAX2(vtp,ftp[0]);
                if (ftpB[1]) vtp = VMAX2(vtp,ftp[1]);
                if (ftpB[2]) vtp = VMAX2(vtp,ftp[2]);

                /* set the type */
                VV_setType(vx, vtp);

            /* otherwise, if all faces Interior, just leave vertex alone */
            }
        }

        /* build the ringed vertex datastructure */
        SS_buildRing(sm);
    }
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"]") );

    /* get the "mcsf_end" tag */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"mcsf_end") );
    VJMPERR2( 1==Vio_scanf(sock,"%d",&inum) );
    VJMPERR2( inum == 1 );

    /* finish the i/o */
    Vnm_print(0,"..done.\n");

    /* create initial edge markings in the simplices */
    Gem_markEdges(thee);

    /* count v/e/f/s and check the mesh */
    Gem_countChk(thee);

    /* return with no errors */
    return 1; 

  VERROR1:
    Vnm_print(2,"Gem_read: Problem with I/O socket.\n");
    Vnm_print(2,"Gem_read: Reseting manifold structures (bailing out).\n");
    Gem_reset( thee, 0, 0 );
    return 0; 

  VERROR2:
    Vnm_print(2,"Gem_read: Format problem with input\n");
    Vnm_print(2,"Gem_read: Reseting manifold structures (bailing out).\n");
    Gem_reset( thee, 0, 0 );
    return 0; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_write
 *
 * Purpose:  Write out a 2-simplex or 3-simplex mesh in "MCSF" format.
 *
 * Parms:    key          ==> output format type
 *                                key=0 ==> simplex format
 *                                key=1 ==> edge format
 *                                key=2 ==> simplex-nabor format
 *           fkey         ==> simplex write option
 *                                fkey=0 ==> write simplices
 *                                fkey=1 ==> write only simplex boundary faces
 *                                fkey=2 ==> write only simplices that have
 *                                           at least one boundary face
 *                                           (NOT IMPLIMENTED HERE)
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_write(Gem *thee, int key, Vio *sock, int fkey)
{
    int i, j, k, nid[4];
    VV *vx;
    SS *sm;

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( Gem_numVV(thee) > 0 );
    VJMPERR2( (0<=key) && (key<=2) );
    VJMPERR2( (0<=fkey) && (fkey<=2) );

    if (key == 1) {
        Gem_writeEdge(thee, sock);
    } else if ((fkey==1) && (Gem_dim(thee) == 3)) {
        Gem_writeFace3d(thee, sock);
    } else if (fkey==2) {
        Vnm_print(2,"Gem_write: fkey=<%d> not implemented (not useful).\n",
            fkey);
    } else { /* (fkey==0) */

        /* deal with socket or file setup */
        Vio_setWhiteChars(sock, MCwhiteChars);
        Vio_setCommChars(sock, MCcommChars);

        /* write out the header */
        Vio_printf(sock,"%s",MCcopyRightPCT1);
        Vio_printf(sock,"%s",MCcopyRightPCT2);
        Vio_printf(sock,"%s",MCcopyRightPCT3);
        Vio_printf(sock,"%s",MCcopyRightPCT4);
        Vio_printf(sock,"\n");
        Vio_printf(sock,"%s=%d;\n\n","mcsf_begin",1);

        Vio_printf(sock,"      %s=%d;    %% intrinsic manifold dimension\n",
            "dim",Gem_dim(thee));

        Vio_printf(sock,"    %s=%d;    %% imbedding manifold dimension\n",
            "dimii",Gem_dimII(thee));

        Vio_printf(sock," %s=%d;    %% number of vertices\n",
            "vertices",Gem_numVV(thee));

        Vio_printf(sock,"%s=%d;    %% number of simplices\n",
            "simplices",Gem_numSS(thee));

        /* write out the vertex data */
        Vio_printf(sock,"\n%s=%s\n","vert","[");
        Vio_printf(sock,"%%-------- ---- -----------------"
         " ----------------- -----------------\n");
        Vio_printf(sock,
         "%% Vert-ID Chrt X0-Coordinate     X1-Coordinate     X2-Coordinate\n");
        Vio_printf(sock,"%%-------- ---- -----------------"
         " ----------------- -----------------\n");
        for (i=0; i<Gem_numVV(thee); i++) {
            vx = Gem_VV(thee,i);
            Vio_printf(sock,"%-9d %-4d", VV_id(vx), VV_chart(vx) );
            for (j=0; j<Gem_dimII(thee); j++)
                Vio_printf(sock," %17.10le", VV_coord(vx,j) );
            Vio_printf(sock,"\n");
        }
        Vio_printf(sock,"%s;\n","]");

        /* write out the simplex data */
        Vio_printf(sock,"\n%s=%s\n","simp","[");
        Vio_printf(sock,"%%-------- ---- ---- -------------------"
         " ---------------------------------------\n");
        Vio_printf(sock,
         "%% Simp-ID Grp  Mat  Face-Types          Vertex-Numbers\n");
        Vio_printf(sock,"%%-------- ---- ---- -------------------"
         " ---------------------------------------\n");
        for (i=0; i<Gem_numSS(thee); i++) {
            sm = Gem_SS(thee,i);
            Vio_printf(sock,"%-9d %-4d %-4d ", i, SS_chart(sm), SS_type(sm));
            if (Gem_dimVV(thee) == 3) {
                Vio_printf(sock,"%-4d %-4d %-4d      %d %d %d", 
                   SS_faceType(sm,0),
                   SS_faceType(sm,1),
                   SS_faceType(sm,2),
                   VV_id( SS_vertex(sm,0) ),
                   VV_id( SS_vertex(sm,1) ),
                   VV_id( SS_vertex(sm,2) )
                );
                if (key == 0) {
                    Vio_printf(sock,"\n");
                } else if (key == 2) {
                    for (k=0; k<3; k++) {
                        if (SS_nabor(sm,k) != VNULL) {
                            nid[k] = SS_id( SS_nabor(sm,k) );
                        } else {
                            nid[k] = -1;
                        }
                    }
                    Vio_printf(sock,"          %d %d %d\n",
                        nid[0], nid[1], nid[2]);
                } else { VASSERT(0); }
            } else if (Gem_dimVV(thee) == 4) {
                Vio_printf(sock,"%-4d %-4d %-4d %-4d %d %d %d %d",
                   SS_faceType(sm,0),
                   SS_faceType(sm,1),
                   SS_faceType(sm,2),
                   SS_faceType(sm,3),
                   VV_id( SS_vertex(sm,0) ),
                   VV_id( SS_vertex(sm,1) ),
                   VV_id( SS_vertex(sm,2) ),
                   VV_id( SS_vertex(sm,3) )
                );
                if (key == 0) {
                    Vio_printf(sock,"\n");
                } else if (key == 2) {
                    for (k=0; k<4; k++) {
                        if (SS_nabor(sm,k) != VNULL) {
                            nid[k] = SS_id( SS_nabor(sm,k) );
                        } else {
                            nid[k] = -1;
                        }
                    }
                    Vio_printf(sock,"     %d %d %d %d\n",
                        nid[0], nid[1], nid[2], nid[3]);
                } else { VASSERT(0); }
            } else { VASSERT(0); }
        }
        Vio_printf(sock,"%s;\n","]");

        /* finish the file */
        Vio_printf(sock,"\n%s=%d;\n\n","mcsf_end",1);
    }

    /* return with no errors */
    return; 

  VERROR1:
    Vnm_print(2,"Gem_write: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_write: Detected a problem (bailing out).\n");
    return; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeFace3d
 *
 * Purpose:  Write out the faces of a 3-simplex mesh as a complete and legal
 *           2-simplex mesh in "MCSF" format (described above for Gem_read).
 *
 * Parms:    iodev        ==> output device type (file/buff/unix/inet)
 *           iofmt        ==> output device format (ascii/xdr)
 *           thost        ==> output hostname (for sockets)
 *           fname        ==> output file/buff/unix/inet name
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeFace3d(Gem *thee, Vio *sock)
{
    int i, j, ii, numVV, numSS, *vTmp;
    VV *vx;
    SS *sm;

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( Gem_numVV(thee) > 0 );
    VJMPERR2( Gem_dim(thee) == 3 );
    VJMPERR2( Gem_dimII(thee) == 3 );

    /* number of boundary vertices and faces */
    numVV = Gem_numBV(thee);
    numSS = Gem_numBF(thee);

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    /* write out the header */
    Vio_printf(sock,"%s",MCcopyRightPCT1);
    Vio_printf(sock,"%s",MCcopyRightPCT2);
    Vio_printf(sock,"%s",MCcopyRightPCT3);
    Vio_printf(sock,"%s",MCcopyRightPCT4);
    Vio_printf(sock,"\n");
    Vio_printf(sock,"%s=%d;\n\n","mcsf_begin",1);

    Vio_printf(sock,"      %s=%d;    %% intrinsic manifold dimension\n",
        "dim",2);

    Vio_printf(sock,"    %s=%d;    %% imbedding manifold dimension\n",
        "dimii",3);

    Vio_printf(sock," %s=%d;    %% number of vertices\n",
        "vertices",numVV);

    Vio_printf(sock,"%s=%d;    %% number of simplices\n",
        "simplices",numSS);

    /* write out the vertex data */
    Vio_printf(sock,"\n%s=%s\n","vert","[");
    Vio_printf(sock,"%%-------- ---- -----------------"
     " ----------------- -----------------\n");
    Vio_printf(sock,
     "%% Vert-ID Chrt X0-Coordinate     X1-Coordinate     X2-Coordinate\n");
    Vio_printf(sock,"%%-------- ---- -----------------"
     " ----------------- -----------------\n");
    vTmp = Vmem_malloc( thee->vmem, Gem_numVV(thee), sizeof(int) );
    ii = 0;
    for (i=0; i<Gem_numVV(thee); i++) {
        vx = Gem_VV(thee,i);
        if (VBOUNDARY( VV_type(vx) )) {
            vTmp[VV_id(vx)] = ii;
            Vio_printf(sock,"%-9d %-4d", ii, VV_chart(vx) );
            for (j=0; j<Gem_dimII(thee); j++)
                Vio_printf(sock," %17.10le", VV_coord(vx,j) );
            Vio_printf(sock,"\n");
            ii++;
        }
    }
    VASSERT( ii == numVV );
    Vio_printf(sock,"%s;\n","]");

    /* write out the simplex data */
    Vio_printf(sock,"\n%s=%s\n","simp","[");
    Vio_printf(sock,"%%-------- ---- ---- -------------------"
     " ---------------------------------------\n");
    Vio_printf(sock,
     "%% Simp-ID Grp  Mat  Face-Types          Vertex-Numbers\n");
    Vio_printf(sock,"%%-------- ---- ---- -------------------"
     " ---------------------------------------\n");
    ii = 0;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        for (j=0; j<4; j++) { 
            if (VBOUNDARY( SS_faceType(sm,j) )) {
                Vio_printf(sock,"%-9d %-4d %-4d ",
                    ii, SS_chart(sm), SS_type(sm));
                Vio_printf(sock,"%-4d %-4d %-4d      %d %d %d\n", 
                    0, 0, 0,
                    vTmp[ VV_id( SS_vertex(sm,vmapF[j][0]) ) ],
                    vTmp[ VV_id( SS_vertex(sm,vmapF[j][1]) ) ],
                    vTmp[ VV_id( SS_vertex(sm,vmapF[j][2]) ) ] );
                ii++;
            }
        }
    }
    VASSERT( ii == numSS );
    Vio_printf(sock,"%s;\n","]");

    /* finish the file */
    Vio_printf(sock,"\n%s=%d;\n\n","mcsf_end",1);

    /* release the temporary storage */
    Vmem_free( thee->vmem, Gem_numVV(thee), sizeof(int), (void**)&vTmp );

    /* return with no errors */
    Vnm_print(0,"Gem_writeFace3d: Finished writing output\n");
    return; 

  VERROR1:
    Vnm_print(2,"Gem_writeFace3d: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeFace3d: Detected a problem (bailing out).\n");
    return; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_readEdge
 *
 * Purpose:  Read in the user-specified initial vertex-edge mesh
 *           provided to us in MC-Edge-Format (MCEF), and transform
 *           into our internal datastructures.
 *
 * Notes: The user provides the following information about a domain and an
 *        initial edge-based triangulation:
 *
 *        D = DIMENSION  = spatial dimension of problem (1, 2, or 3)
 *        N = NVERTICES  = total number of vertices in mesh
 *        L = NEDGES     = total number of edges in the mesh
 *
 *        double vertex* = List of all vertex coordinates in the form:
 *
 *        vertex[ N * (3+D) ] = {
 *            { id1, proc1, info1, v1_x1, ..., v1_xD },
 *            { id2, proc2, info2, v2_x1, ..., v2_xD },
 *                            ...
 *            { idN, procN, infoN, vN_x1, ..., vN_xD }
 *        }
 *
 *        Here, vj_xk is the kth component (float or double) of the vertex 
 *        with global vertex number j.  The "idj" flag is a 32-bit integer 
 *        "name" for vertex j, "procj" is a 32-bit color or processor number 
 *        associated with vertex j, and "infoj" is a 32-bit integer containing
 *        information about vertex j.
 *
 *        int edge* = List of all edges by vertex number in the form:
 *
 *        edge[ L * (2 + 2*(D+1)) ] = {
 *            { id1, proc1, info1, e1_v1, e1_v2 },
 *            { id2, proc2, info2, e2_v1, e2_v2 },
 *                            ...
 *            { idL, procL, infoL, eL_v1, eL_v2 }
 *        }
 *
 *        Here, ej_vk is a 32-bit integer giving the global vertex number
 *        making up the kth vertex of the edge with global number j.  The
 *        "idj" flag is a 32-bit integer "name" for edge j, "procj" is a
 *        32-bit color or processor number associated with edge j,
 *        "infoj" is a 32-bit integer containing the information about the
 *        edge j.
 *
 * Notes: To recover a simplex (triangle) mesh from the vertices and edges,
 *        we must traverse them and rebuild the simplex structure, and do it
 *        all in linear time.
 *
 *        The three-step simplex recovery algorithm is as follows:
 *
 *        (1) Definite vertices and edges from the input data.
 *
 *        (2) Create all possible simplices as follows:
 *
 *            For (vx=firstVV; vx!=lastVV; vx=nextVV) {
 *            | Build all simplices which use vx as a vertex as follows:
 *            |   2D CASE: For each distinct pair of vertices connected
 *            |            by an edge with vx, if this pair are also
 *            |            connected by an edge, then the three make a
 *            |            triangle.  If the triangle has not already
 *            |            been created, then do so and add to the
 *            |            simplex rings for each of the three vertices.
 *            |   3D CASE: For each distinct trio of vertices connected
 *            |            by an edge with vx, if this trio forms a triangle,
 *            |            then the foursome make a tetrahedron.  If the
 *            |            tetrahedron has not already been created, then do
 *            |            so and add to the simplex rings for each of the
 *            |            four vertices.
 *            EndFor
 *
 *        (3) Remove a few "bad" simplices which were created incorrectly
 *            in Step (2) above as follows:
 *
 *            For (sm=firstSS; sm!=lastSS; sm=nextSS) {
 *            | Remove all "bad" simplices, defined to be those satisfying:
 *            |   2D CASE: All interior edges have multiple nabors, and
 *            |            all boundary edges have at least one nabor.
 *            |   3D CASE: All interior faces have multiple nabors, and
 *            |            all boundary faces have at least one nabor.
 *            EndFor
 *
 *       NOTE: The crucial Step (3) of the above algorithm only works
 *       correctly if we correctly identify the boundary faces of the
 *       simplices, which is only possible if the input edge-based mesh
 *       was given with boundary edge information.  (We can construct
 *       correct face types from the types of the one or three edges
 *       forming the face in 2D or 3D respectively.)
 *
 *       We attempt to recover simplex face types from the given
 *       edge types.  However, (at least) one degenerate cases is not 
 *       recoverable: an isolated Neumann face surounded by Dirichlet faces
 *       will appear simply as three Dirichlet edges in the edge-based mesh,
 *       and we turn this into a Dirichlet face.  Note that if a Neumann
 *       face consists of more than one simplex face, then it will be
 *       recovered correctly from the edge types.  
 *
 *       Note also that if a non-simplex mesh is provided as input in
 *       as an edge-based mesh, we will build the edges as specified,
 *       but our attempt to build simplices will only recover those
 *       simplices which actually exist in the edge mesh.  Any other
 *       non-simplex polyedra will appear as holes in the final
 *       simplex mesh.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC int Gem_readEdge(Gem *thee, Vio *sock)
{
    int i, j, theDim, theDimII, inum;
    int numVV, indexV, chartV;
    int numEE, indexE, groupE, typeE, se[2];
    double x[3];
    char tok[VMAX_BUFSIZE];
    VV *vx;
    EE *eg;

    /* some error checking */
    VJMPERR1( VNULL != sock );

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    /* get the "mcef_begin=1" tag */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"mcef_begin") );
    VJMPERR2( 1==Vio_scanf(sock,"%d",&inum) );
    VJMPERR2( inum == 1 );

    /* read the intrinsic dimension */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"dim") );
    VJMPERR2( 1==Vio_scanf(sock,"%d", &theDim) );
    VJMPERR2( (theDim == 2) || (theDim == 3) );

    /* read the imbedding dimension */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"dimii") );
    VJMPERR2( 1==Vio_scanf(sock,"%d", &theDimII) );
    VJMPERR2( (theDimII == 2) || (theDimII == 3) );

    /* read and set the number of vertices information */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"vertices") );
    VJMPERR2( 1==Vio_scanf(sock,"%d", &numVV) );
    thee->numVV0 = numVV;

    /* read and set the number of edges information */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"edges") );
    VJMPERR2( 1==Vio_scanf(sock,"%d", &numEE) );

    /* reset ourself to handle the new manifold dimensions */
    Vnm_print(0,"Gem_readEdge: theDim=%d, theDimII=%d, numVV=%d, numEE=%d\n",
        theDim, theDimII, numVV, numEE);
    Vnm_print(0,"Gem_readEdge: Reseting manifold structures.\n");
    Gem_reset( thee, theDim, theDimII );

    /* read in the vertices */
    Vnm_print(0,"Gem_readEdge: Reading ..vertices..");
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"vert") );
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"[") );
    for (i=0; i<numVV; i++) {

        /* grab the three integer info fields */
        VJMPERR2( 1==Vio_scanf(sock,"%d",&indexV) );
        VJMPERR2( 1==Vio_scanf(sock,"%d",&chartV) );

        /* grab the "dimii" coordinates */
        for (j=0; j<theDimII; j++)
            VJMPERR2( 1==Vio_scanf(sock,"%le",&x[j]) );

        /* trivially embed any 2D coordinates into 3D */
        if (theDimII == 2) x[2] = 0.;

        /* create the new vertex */
        vx = Gem_createAndInitVV(thee);
        VV_setReality(vx, 0);
        VV_setDim(vx, theDim);
        VV_setClass(vx, 0);
        VV_setType(vx, 0);
        VV_setId(vx, i);
        VV_setChart(vx, chartV);

        /* set the vertex coordinates */
        for (j=0; j<3; j++)
            VV_setCoord(vx, j, x[j]);
    }
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"]") );

    /* read in the edges */
    Vnm_print(0,"..edges..");
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"edge") );
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"[") );
    for (i=0; i<numEE; i++) {

        /* grab the three integer info fields */
        VJMPERR2( 1==Vio_scanf(sock,"%d",&indexE) );
        VJMPERR2( 1==Vio_scanf(sock,"%d",&groupE) );
        VJMPERR2( 1==Vio_scanf(sock,"%d",&typeE) );

        /* grab the "2" vertex numbers */
        for (j=0; j<2; j++)
            VJMPERR2( 1==Vio_scanf(sock,"%d",&se[j]) );

        /* create the new edge */
        eg = Gem_createAndInitEE(thee);
        EE_setReality(eg, 0);
        EE_setDim(eg, theDim);
        EE_setClass(eg, theDim);
        EE_setType(eg, typeE);
        EE_setId(eg, i); 
        EE_setChart(eg, groupE); 

        /* set the vertex labels */
        for (j=0; j<2; j++) {
            vx = Gem_VV(thee, se[j] );
            EE_setVertex( eg, j, vx );
        }

        /* build the ringed vertex datastructure */
        EE_buildRing(eg);
    }
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"]") );

    /* get the "mcef_end" tag */
    VJMPERR2( 1==Vio_scanf(sock,"%s",tok) );
    VJMPERR2( !strcmp(tok,"mcef_end") );
    VJMPERR2( 1==Vio_scanf(sock,"%d",&inum) );
    VJMPERR2( inum == 1 );

    /* finish the i/o */
    Vnm_print(0,"..done.\n");

    /* close the input file */
    Vnm_print(0,"Gem_readEdge: Finished reading input\n");

    /* build the simplices from the edges */
    Gem_buildSfromE(thee);

    /* destroy the edges */
    Gem_destroyEdges(thee);

    /* create initial edge markings in the simplices */
    Gem_markEdges(thee);

    /* count v/e/f/s and check the mesh */
    Gem_countChk(thee);

    /* return with no errors */
    return 1; 

  VERROR1:
    Vnm_print(2,"Gem_readEdge: Problem with I/O socket.\n");
    Vnm_print(2,"Gem_readEdge: Reseting manifold structures (bailing out).\n");
    Gem_reset( thee, 0, 0 );
    return 0; 

  VERROR2:
    Vnm_print(2,"Gem_readEdge: Format problem with input\n");
    Vnm_print(2,"Gem_readEdge: Reseting manifold structures (bailing out).\n");
    Gem_reset( thee, 0, 0 );
    return 0; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeEdge
 *
 * Purpose:  Write out the edges of a 2- or 3-simplex mesh 
 *           in "MCEF" (MC-Edge-Format).
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeEdge(Gem *thee, Vio *sock)
{
    int i, j;
    VV *vx;
    EE *eg;

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( Gem_numVV(thee) > 0 );

    /* create edges if we don't have them yet */
    Gem_createEdges(thee);

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    /* write out the header */
    Vio_printf(sock,"%s",MCcopyRightPCT1);
    Vio_printf(sock,"%s",MCcopyRightPCT2);
    Vio_printf(sock,"%s",MCcopyRightPCT3);
    Vio_printf(sock,"%s",MCcopyRightPCT4);
    Vio_printf(sock,"\n");
    Vio_printf(sock,"%s=%d;\n\n","mcef_begin",1);

    Vio_printf(sock,"      %s=%d;    %% intrinsic manifold dimension\n",
        "dim",Gem_dim(thee));

    Vio_printf(sock,"    %s=%d;    %% imbedding manifold dimension\n",
        "dimii",Gem_dimII(thee));

    Vio_printf(sock," %s=%d;    %% number of vertices\n",
        "vertices",Gem_numVV(thee));

    Vio_printf(sock,"    %s=%d;    %% number of edges\n",
        "edges",Gem_numEE(thee));

    /* write out the vertex data */
    Vio_printf(sock,"\n%s=%s\n","vert","[");
    Vio_printf(sock,"%%-------- ---- -----------------"
        " ----------------- -----------------\n");
    Vio_printf(sock,
     "%% Vert-ID Chrt X0-Coordinate     X1-Coordinate     X2-Coordinate\n");
    Vio_printf(sock,"%%-------- ---- -----------------"
        " ----------------- -----------------\n");
    for (i=0; i<Gem_numVV(thee); i++) {
        vx = Gem_VV(thee,i);
        Vio_printf(sock,"%-9d %-4d", VV_id(vx), VV_chart(vx) );
        for (j=0; j<Gem_dimII(thee); j++)
            Vio_printf(sock," %17.10le", VV_coord(vx,j) );
        Vio_printf(sock,"\n");
    }
    Vio_printf(sock,"%s;\n","]");

    /* write out the edge data */
    Vio_printf(sock,"\n%s=%s\n","edge","[");
    Vio_printf(sock,"%%-------- ---- ----"
        " ---------------------------------------\n");
    Vio_printf(sock,
        "%% Edge-ID Grp  Mat  Vertex-Numbers\n");
    Vio_printf(sock,"%%-------- ---- ----"
        " ---------------------------------------\n");
    for (i=0; i<Gem_numEE(thee); i++) {
        eg = Gem_EE(thee,i);
        Vio_printf(sock,"%-9d %-4d %-4d %d %d\n",
            i, EE_chart(eg), EE_type(eg),
            VV_id( EE_vertex(eg,0) ),
            VV_id( EE_vertex(eg,1) )
        );
    }
    Vio_printf(sock,"%s;\n","]");

    /* finish the file */
    Vio_printf(sock,"\n%s=%d;\n\n","mcef_end",1);

    /* destroy edges */
    Gem_destroyEdges(thee);

    /* return with no errors */
    Vnm_print(0,"Gem_writeEdge: Finished writing output\n");
    return; 

  VERROR1:
    Vnm_print(2,"Gem_writeEdge: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeEdge: Detected a problem (bailing out).\n");
    return; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_buildSfromE
 *
 * Purpose:  Build a vertex-simplex mesh from a vertex-edge mesh.
 *
 * Notes:    Below is an email I sent to R. Bank outlining the idea of the
 *           algorithm.  I wanted to do this completely topologically, using
 *           no geometry information, so that it would work for abstract
 *           simplex manifolds.
 *
 * ---------------------------------------------------------------------------
 * Randy,
 * 
 * I realized on the drive that your 2-manifold example is not actually
 * a problem after all.
 * 
 * Consider first the planar situation we were worrying about, e.g., take a tet
 * and push the fourth vertex down into the plane of the other three vertices,
 * and you have the three (good) triangles inside one (bad) triangle.
 * As we agreed, any situation like this in the plane is managable (e.g. we can
 * detect the "bad" triangle) as long as we known what the boundary edges are
 * for the entire mesh.
 * 
 * I conjecture that the "bad" simplices in this case and other 2D cases, as
 * well as the 3D case, are precisely those whose faces (edges in 2D) satisfy
 * both of the following conditions.  (If this is a theorem, then everything
 * in this note is rigorous.)
 *    (a) All interior faces are shared with >1 other simplex
 *    (b) All boundary faces are shared with >0 other simplex
 * 
 * Consider now your example, e.g. the four surface triangles of a tetrahedron
 * as a 2-manifold without boundary.  We would like to be able to recover all
 * four surface triangles from the six edges, and we don't want to toss out one
 * of the triangles as we did above.  The key difference is that above, the
 * problem triangle either has one or more boundary edges, OR it is imbedded in
 * the interior of a mesh, so its interior edges have neighoring triangles.
 * 
 * That doesn't happen for the tet surface example.  We would first build all
 * possible triangles from triples of edges.  According to the above
 * "bad simplex" rule, all four of the triangles are "good", since they all
 * have exactly one naboring triangle sharing each edge.  So we get the correct
 * triangulation of the surface of the tet.
 * 
 * I conjecture that the following algorithm will rebuild d-simplices
 * (d=2 or d=3) from edges, using only topological information, with no
 * geometry information (and no floating point arithmetic at all, for that
 * matter).  The edge-based input mesh has to satisfy three properties:
 * 
 *    1. The dimension "d" of the mesh is specified (either d=2 or d=3)
 *    2. The edge-based mesh was built from an underlying d-simplex mesh
 *    3. The boundary edges are marked as such
 * 
 * The two-step simplex reconstruction algorithm is then as follows:
 * 
 *    1. For each vertex "v" do:
 *          For all vertices connected to "v" by a single edge do:
 *             Build every possible d-simplex
 *          EndFor
 *       EndFor
 *    2. For each simplex "s" that was built in step 1 do:
 *          3.  If d=3, calculate all "face" types of "s" based on edge types
 *          4.  Remove simplex "s" from list of simplices if (a) AND (b) hold:
 *              (a) ALL inter faces (edges if d=2) shared by >1 other simplices
 *              (b) ALL bndry faces (edges if d=2) shared by >0 other simplices
 *       EndFor
 * 
 * If you can come up with a triangulation of any 2-manifold, with or without
 * boundary, with or without holes, etc, which can't be turned into an edge
 * mesh and then recovered correctly using the above algorithm, then I'll
 * give you a dollar...  -mike
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_buildSfromE(Gem *thee)
{
    int i, j, k, l, m, p, q, r, neg, theDim, goodFace, conformCount;
    int groupS, materialS, faceTypeS[4], sv[4];
    VV *vx, *v[4], *vtx[100];
    EE *eg;
    SS *sm, *sm0, *sm1, *sm2;

    theDim = Gem_dim(thee);

    /* build simplices from edges */
    for (i=0; i<Gem_numVV(thee); i++) {
        vx = Gem_VV(thee,i);

        /* make a list of all vertices which are edge nabors of vx */
        neg = 0;
        for (eg=VV_firstEE(vx); eg!=VNULL; eg=EE_link(eg,vx)) {
            VASSERT( neg < 100 );
            vtx[neg] = EE_otherVertex(eg,vx);
            neg++;
        }

        /* 2D: consider all duos of these nabors; do they make an edge? */
        if (theDim == 2) {
            for (p=0; p<neg; p++) {
                for (q=0; q<p; q++) {
                    if (VNULL!=VV_commonEdge(vtx[p],vtx[q])) {
                        if (VNULL==VV_commonSimplex3(vx,vtx[p],vtx[q],VNULL)) {

                            sv[0] = VV_id(vx);
                            sv[1] = VV_id(vtx[p]);
                            sv[2] = VV_id(vtx[q]);

                            /* group, material, and facetypes */
                            groupS = 0;
                            materialS = 0;
                            for (j=0; j<theDim+1; j++) faceTypeS[j]=0;

                            /* create the new simplex */
                            sm = Gem_createAndInitSS(thee);
                            SS_setReality(sm, 0);
                            SS_setDim(sm, theDim);
                            SS_setClass(sm, theDim);
                            SS_setType(sm, materialS);
                            SS_setId( sm, Gem_numSS(thee)-1 ); 
                            SS_setChart(sm, groupS); 

                            /* set simplex face types and vertex labels */
                            for (j=0; j<theDim+1; j++) {
                                SS_setFaceType( sm, j, faceTypeS[j] );
                                if (VBOUNDARY( faceTypeS[j] )) {
                                    (thee->numBF)++;
                                }
                                SS_setVertex(sm,j,Gem_VV(thee,sv[j]));
                            }

                            /* orientation check */
                            if (Gem_simplexVolume(thee,sm) < 0) {
                                SS_setVertex(sm,0,Gem_VV(thee,sv[1]));
                                SS_setVertex(sm,1,Gem_VV(thee,sv[0]));
                            }

                            /* build the ringed vertex datastructure */
                            SS_buildRing(sm);
                        }
                    }
                }
            }

        /* 3D: consider all trios of these nabors; do they make a triangle? */
        } else if (theDim == 3) {
            for (p=0; p<neg; p++) {
                for (q=0; q<p; q++) {
                    for (r=0; r<q; r++) {
                        if ( (VNULL != VV_commonEdge(vtx[p],vtx[q]))
                          && (VNULL != VV_commonEdge(vtx[p],vtx[r]))
                          && (VNULL != VV_commonEdge(vtx[q],vtx[r])) ) {
                            if (VNULL == VV_commonSimplex4(vx,
                              vtx[p],vtx[q],vtx[r],VNULL)) {

                                sv[0] = VV_id(vx);
                                sv[1] = VV_id(vtx[p]);
                                sv[2] = VV_id(vtx[q]);
                                sv[3] = VV_id(vtx[r]);

                                /* group, material, and facetypes */
                                groupS = 0;
                                materialS = 0;
                                for (j=0; j<theDim+1; j++) faceTypeS[j]=0;

                                /* create the new simplex */
                                sm = Gem_createAndInitSS(thee);
                                SS_setReality(sm, 0);
                                SS_setDim(sm, theDim);
                                SS_setClass(sm, theDim);
                                SS_setType(sm, materialS);
                                SS_setId( sm, Gem_numSS(thee)-1 ); 
                                SS_setChart(sm, groupS); 

                                /* set simplex face types/vertex labels */
                                for (j=0; j<theDim+1; j++) {
                                    SS_setFaceType( sm, j, faceTypeS[j] );
                                    if (VBOUNDARY( faceTypeS[j] )) {
                                        (thee->numBF)++;
                                    } 
                                    SS_setVertex(sm,j,Gem_VV(thee,sv[j]));
                                }

                                /* orientation check */
                                if (Gem_simplexVolume(thee,sm) < 0) {
                                    SS_setVertex(sm,0,Gem_VV(thee,sv[1]));
                                    SS_setVertex(sm,1,Gem_VV(thee,sv[0]));
                                }

                                /* build the ringed vertex datastructure */
                                SS_buildRing(sm);
                            }
                        }
                    }
                }
            }
        } else { VASSERT(0); }
    }

    /*
     * All that remains is to handle the one degenerate situation.
     * This occurs when a group of simplices is contained entirely inside
     * another simplex.  When this happens, the above simplex construction
     * algorithm will incorrectly add the enclosing simplex, which really
     * was not part of the original mesh.  This of course creates some
     * overlapping/nonconforming simplices.  It can be detected and corrected
     * however by noting that these simplices will be precisely those
     * for which ALL of their interior faces have more than one face nabor,
     * and all of their boundary faces also have an unexpected nabor.
     * The naboring simplices also have some faces with multiple nabors,
     * but only the bad simplices have ALL of the faces with bad nabor
     * structure.  Therefore, we just need to traverse the simplices once
     * and remove those which have multiple face nabors on all faces.
     *
     * NOTE: This requires that we have actually reconstructed the boundary
     * face information correctly from the input boundary edge information.
     * If the input edge mesh did not contain boundary edge information,
     * we have no way to remove these degenerate "extra" simplices.
     */
    i=0;
    while (i < Gem_numSS(thee)) {
        sm = Gem_SS(thee,i);

        /* get local vertices */
        for (j=0; j<Gem_dimVV(thee); j++)
            v[j] = SS_vertex(sm,j);

        /* check for a bad simplex (they don't have a single good face) */
        goodFace=0;
        for (j=0; j<Gem_dimVV(thee); j++) {
            k=(j+1) % Gem_dimVV(thee);
            l=(k+1) % Gem_dimVV(thee);
            m=(l+1) % Gem_dimVV(thee);
            conformCount = 0;
            for (sm0=VV_firstSS(v[k]); sm0!=VNULL;sm0=SS_link(sm0,v[k])) {
                for (sm1=VV_firstSS(v[l]);sm1!=VNULL;sm1=SS_link(sm1,v[l])){
                    if (Gem_dim(thee) == 2) {
                        if ((sm0!=sm) && (sm0==sm1)) conformCount++;
                    } else {
                        for (sm2=VV_firstSS(v[m]); sm2!=VNULL;
                          sm2=SS_link(sm2,v[m])) {
                            if ((sm0!=sm) && (sm0==sm1) && (sm0==sm2)) {
                                conformCount++;
                            }
                        }
                    }
                }
            }
            /* if this face has less that two nabors, it is "good" */
            if ( conformCount < 2 ) goodFace++;
        }

        /* bad simplices have either 0 good faces if they are interior, */
        /* or 1 good face (and that one good face is a boundary face).  */
        if ( (goodFace == 0) || (goodFace == 1) ) {
            Vnm_print(0,"Gem_buildSfromE: simplex <%d> is bad..", i);
            Vnm_print(0,"..removing (not an error)");

            /* get last simplex in list */
            sm0 = Gem_lastSS(thee);

            /* if sm is not last in the list, exchange it with the last one */
            SS_meltRing(sm);
            if ( sm != sm0 ) {
                SS_meltRing(sm0);

                SS_setType(sm, SS_type(sm0));
                SS_setChart(sm, SS_chart(sm0)); 

                /* set simplex face types/vertex labels */
                for (j=0; j<theDim+1; j++) {
                    SS_setVertex( sm, j, SS_vertex(sm0,j) );
                    SS_setFaceType( sm, j, SS_faceType(sm0,j) );
                }

                /* build the ringed vertex datastructure */
                SS_buildRing(sm);
            }

            /* now remove the last guy */
            Gem_destroySS(thee);

            Vnm_print(0,"..done.\n");
        }

        /* iterate */
        i++;
    }

    /* finally, make a boundary */
    Gem_makeBnd(thee, 1);

    /* return */
    return;
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeBrep
 *
 * Purpose:  Write out the boundary edges or boundary faces of a 
 *           2-simplex or 3-simplex mesh in a "BREP" format for input
 *           into Barry Joe's 2D/3D Geompak.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeBrep(Gem *thee, Vio *sock)
{
    if (Gem_dim(thee) == 2) {
        Gem_writeBrep2to3(thee, sock);
    } else if (Gem_dim(thee) == 3) {
        Gem_writeBrep3(thee, sock);
    } else { VASSERT(0); }
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeBrep2
 *
 * Purpose:  Write out boundary edges of a 2-simplex mesh 
 *           in a "BREP" format for input into Barry Joe's 2D Geompak.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeBrep2(Gem *thee, Vio *sock)
{
    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );
    VJMPERR2( Gem_dim(thee) == 2 );

    Vnm_print(2,"Gem_writeBrep2: this routine is broken.\n");

    /* return with no errors */
    return; 

  VERROR1:
    Vnm_print(2,"Gem_writeBrep2: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeBrep2: Detected a problem (bailing out).\n");
    return; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeBrep3
 *
 * Purpose:  Write out boundary faces of a 3-simplex mesh
 *           in a "BREP" format for input into Barry Joe's 3D Geompak.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeBrep3(Gem *thee, Vio *sock)
{
    int i, j, ii, numVV, numSS, *vTmp;
    VV *vx;
    SS *sm;

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );
    VJMPERR2( Gem_dim(thee) == 3 );

    /* number of boundary vertices and faces */
    numVV = Gem_numBV(thee);
    numSS = Gem_numBF(thee);

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    /* write out the header */
    Vio_printf(sock,"%s\n","BREP");
    Vio_printf(sock,
        "1.0e-10 30.0 20.0 40.0 0.05 30.0 0.25 0.5    5 5 0    0.8\n");
    Vio_printf(sock,"%d %d 0 1 0 0 0\n\n", numVV, numSS);

    /* write out the vertices */
    vTmp = Vmem_malloc( thee->vmem, Gem_numVV(thee), sizeof(int) );
    ii=0;
    for (i=0; i<Gem_numVV(thee); i++) {
        vx = Gem_VV(thee,i);
        if (VBOUNDARY( VV_type(vx) )) {
            vTmp[VV_id(vx)] = ii;
            Vio_printf(sock,"%13.6e %13.6e %13.6e\n",
                VV_coord(vx,0), VV_coord(vx,1), VV_coord(vx,2) );
            ii++;
        }
    }
    Vio_printf(sock,"\n");

    /* write out the face starts */
    ii=0;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        for (j=0; j<=Gem_dimVV(thee); j++) {
            if (VBOUNDARY( SS_faceType(sm,j) )) {
                Vio_printf(sock," %4d",3*ii+1);
                ii++;
            }
        }
    }
    Vio_printf(sock," %4d\n",3*ii+1);

    /* write out the face numbers */
    ii=0;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        for (j=0; j<=Gem_dimVV(thee); j++) {
            if (VBOUNDARY( SS_faceType(sm,j) )) {
                Vio_printf(sock," %4d",ii+1);
                ii++;
            }
        }
    }
    Vio_printf(sock,"\n\n");

    /* write out the faces */
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        for (j=0; j<=Gem_dimVV(thee); j++) {
            if (VBOUNDARY( SS_faceType(sm,j) )) {
                Vio_printf(sock,"%4d %4d %4d\n", 
                    vTmp[ VV_id( SS_vertex(sm,vmapF[j][1]) ) ] + 1,
                    vTmp[ VV_id( SS_vertex(sm,vmapF[j][0]) ) ] + 1,
                    vTmp[ VV_id( SS_vertex(sm,vmapF[j][2]) ) ] + 1 );
            }
        }
    }
    Vio_printf(sock,"\n");

    /* write out the face numbers */
    Vio_printf(sock," %4d %4d\n",1,numSS+1);
    ii=0;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        for (j=0; j<=Gem_dimVV(thee); j++) {
            if (VBOUNDARY( SS_faceType(sm,j) )) {
                Vio_printf(sock," %4d",ii+1);
                ii++;
            }
        }
    }
    Vio_printf(sock,"\n");

    /* release the temporary storage */
    Vmem_free( thee->vmem, Gem_numVV(thee), sizeof(int), (void**)&vTmp );

    /* return with no errors */
    Vnm_print(0,"Gem_writeBrep3: Finished writing output\n");
    return; 

  VERROR1:
    Vnm_print(2,"Gem_writeBrep3: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeBrep3: Detected a problem (bailing out).\n");
    return; 
}

/*
 * ***************************************************************************
 * Routine:  Gem_writeBrep2to3
 *
 * Purpose:  Write out triangles of a 2-manifold as a 3-simplex boundary mesh
 *           in a "BREP" format for input into Barry Joe's 3D Geompak.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_writeBrep2to3(Gem *thee, Vio *sock)
{
    int i, ii, numVV, numSS;
    VV *vx;
    SS *sm;

    /* some error checking */
    VJMPERR1( VNULL != sock );
    VJMPERR2( (Gem_numVV(thee) > 0) && (Gem_numSS(thee) > 0) );
    VJMPERR2( Gem_dim(thee) == 2 );

    /* number of boundary vertices and faces */
    numVV = Gem_numVV(thee);
    numSS = Gem_numSS(thee);

    /* deal with socket or file setup */
    Vio_setWhiteChars(sock, MCwhiteChars);
    Vio_setCommChars(sock, MCcommChars);

    /* write out the header */
    Vio_printf(sock,"%s\n","BREP");
    Vio_printf(sock,
        "1.0e-10 30.0 20.0 40.0 0.05 30.0 0.25 0.5    5 5 0    0.8\n");
    Vio_printf(sock,"%d %d 0 1 0 0 0\n\n", numVV, numSS);

    /* write out the vertices */
    for (i=0; i<Gem_numVV(thee); i++) {
        vx = Gem_VV(thee,i);
        Vio_printf(sock,"%13.6e %13.6e %13.6e\n",
            VV_coord(vx,0), VV_coord(vx,1), VV_coord(vx,2) );
    }
    Vio_printf(sock,"\n");

    /* write out the face starts */
    ii=0;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        Vio_printf(sock," %4d",3*ii+1);
        ii++;
    }
    Vio_printf(sock," %4d\n",3*ii+1);

    /* write out the face numbers */
    ii=0;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        Vio_printf(sock," %4d",ii+1);
        ii++;
    }
    Vio_printf(sock,"\n\n");

    /* write out the faces */
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        Vio_printf(sock,"%4d %4d %4d\n", 
            VV_id( SS_vertex(sm,0) ) + 1,
            VV_id( SS_vertex(sm,1) ) + 1,
            VV_id( SS_vertex(sm,2) ) + 1 );
    }
    Vio_printf(sock,"\n");

    /* write out the face numbers */
    Vio_printf(sock," %4d %4d\n",1,numSS+1);
    ii=0;
    for (i=0; i<Gem_numSS(thee); i++) {
        sm = Gem_SS(thee,i);
        Vio_printf(sock," %4d",ii+1);
        ii++;
    }
    Vio_printf(sock,"\n");

    /* return with no errors */
    Vnm_print(0,"Gem_writeBrep2to3: Finished writing output\n");
    return; 

  VERROR1:
    Vnm_print(2,"Gem_writeBrep2to3: Problem with I/O socket.\n");

  VERROR2:
    Vnm_print(2,"Gem_writeBrep2to3: Detected a problem (bailing out).\n");
    return; 
}

