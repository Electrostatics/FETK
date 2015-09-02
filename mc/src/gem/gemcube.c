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
 * rcsid="$Id: gemcube.c,v 1.7 2010/08/12 05:18:54 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     Gemcube.c
 *
 * Purpose:  Class Gem: methods.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include "gem_p.h"

VEMBED(rcsid="$Id: gemcube.c,v 1.7 2010/08/12 05:18:54 fetk Exp $")

/* local variables */
VPRIVATE char *GEM_square =
"mcsf_begin=1;\n\
\n\
      dim=2;\n\
    dimii=3;\n\
 vertices=4;\n\
simplices=2;\n\
\n\
vert=[\n\
0 0 0.0 0.0 0.0\n\
1 0 1.0 0.0 0.0\n\
2 0 0.0 1.0 0.0\n\
3 0 1.0 1.0 0.0\n\
];\n\
\n\
simp=[\n\
0 0 0 0 1 1 0 1 2\n\
1 0 0 1 0 1 1 3 2\n\
];\n\
\n\
mcsf_end=1;\n\
";

VPRIVATE char *GEM_cube =
"mcsf_begin=1;\n\
\n\
      dim=3;\n\
    dimii=3;\n\
 vertices=8;\n\
simplices=6;\n\
\n\
vert=[\n\
0 0 0.0 0.0 0.0\n\
1 0 1.0 0.0 0.0\n\
2 0 0.0 1.0 0.0\n\
3 0 1.0 1.0 0.0\n\
4 0 0.0 0.0 1.0\n\
5 0 1.0 0.0 1.0\n\
6 0 0.0 1.0 1.0\n\
7 0 1.0 1.0 1.0\n\
];\n\
\n\
simp=[\n\
0 0 0 0 1 0 1 0 5 1 2\n\
1 0 0 0 1 1 0 0 5 2 4\n\
2 0 0 0 1 0 1 1 5 3 2\n\
3 0 0 0 1 0 1 3 5 7 2\n\
4 0 0 1 1 0 0 2 5 7 6\n\
5 0 0 1 1 0 0 2 5 6 4\n\
];\n\
\n\
mcsf_end=1;\n\
\n\
";

VPRIVATE char *GEM_octahedron =
"mcsf_begin=1;\n\
\n\
      dim=3;\n\
    dimii=3;\n\
 vertices=7;\n\
simplices=8;\n\
\n\
vert=[\n\
0 0  0.0  0.0  0.0\n\
1 0  0.0  0.0  1.0\n\
2 0  0.0  0.0 -1.0\n\
3 0  1.0  0.0  0.0\n\
4 0  0.0  1.0  0.0\n\
5 0 -1.0  0.0  0.0\n\
6 0  0.0 -1.0  0.0\n\
];\n\
\n\
simp=[\n\
0 0 0 1 0 0 0 0 3 4 1\n\
1 0 0 1 0 0 0 0 6 3 1\n\
2 0 0 1 0 0 0 0 4 5 1\n\
3 0 0 1 0 0 0 0 5 6 1\n\
4 0 0 1 0 0 0 0 4 3 2\n\
5 0 0 1 0 0 0 0 3 6 2\n\
6 0 0 1 0 0 0 0 5 4 2\n\
7 0 0 1 0 0 0 0 6 5 2\n\
];\n\
\n\
mcsf_end=1;\n\
";

VPRIVATE char *GEM_icosahedron1 =
"mcsf_begin=1;\n\
\n\
      dim=3;\n\
    dimii=3;\n\
 vertices=12;\n\
simplices=18;\n\
\n\
vert=[\n\
0  0 -0.6180339887498948 -1.0 0.0\n\
1  0 -0.6180339887498948  1.0 0.0\n\
2  0  0.6180339887498948 -1.0 0.0\n\
3  0  0.6180339887498948  1.0 0.0\n\
4  0 -1.0  0.0 -0.6180339887498948\n\
5  0 -1.0  0.0  0.6180339887498948\n\
6  0  1.0  0.0 -0.6180339887498948\n\
7  0  1.0  0.0  0.6180339887498948\n\
8  0  0.0 -0.6180339887498948 -1.0\n\
9  0  0.0 -0.6180339887498948  1.0\n\
10 0  0.0  0.6180339887498948 -1.0\n\
11 0  0.0  0.6180339887498948  1.0\n\
];\n\
\n\
";
VPRIVATE char *GEM_icosahedron2 = 
"simp=[\n\
0 0 0  0 1 1 0  5 0 1 4\n\
1 0 0  0 0 0 0  6 3 2 4\n\
2 0 0  0 1 0 0  10 4 3 6\n\
3 0 0  0 0 0 0  5 1 2 3\n\
4 0 0  0 0 0 0  7 2 3 5\n\
5 0 0  0 0 0 0  5 1 0 2\n\
6 0 0  0 0 1 0  11 3 5 7\n\
7 0 0  0 1 1 0  7 3 2 6\n\
8 0 0  0 0 0 0  4 0 1 2\n\
9 0 0  0 0 0 0  4 2 1 3\n\
10 0 0  0 0 1 1  10 1 3 4\n\
11 0 0  0 1 1 0  11 7 5 9\n\
12 0 0  0 0 1 1  9 0 2 5\n\
13 0 0  0 1 0 0  9 5 2 7\n\
14 0 0  0 0 1 0  8 2 4 6\n\
15 0 0  0 1 1 0  10 4 6 8\n\
16 0 0  0 1 0 1  8 2 0 4\n\
17 0 0  0 1 0 1  11 3 1 5\n\
];\n\
\n\
mcsf_end=1;\n\
";

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
 * Routine:  Gem_makeSquare
 *
 * Purpose:  Generate a unit square domain.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
void Gem_makeSquare(Gem *thee)
{
    int  skey    = 0;           /* simplex format */
    char *key    = "r";         /* read */
    char *iodev  = "BUFF";      /* buffer */
    char *iofmt  = "ASC";       /* ascii */
    char *iohost = "localhost"; /* localhost (dummy) */
    char *iofile = "0";         /* socket 0 (dummy) */
    Vio *sock;
    char buf[VMAX_BUFSIZE];
    int bufsize = 0;

    bufsize = strlen(GEM_square);
    VASSERT( bufsize <= VMAX_BUFSIZE );
    strncpy(buf, GEM_square, VMAX_BUFSIZE);

    VASSERT( VNULL != (sock=Vio_socketOpen(key,iodev,iofmt,iohost,iofile)) );
    Vio_bufTake(sock, buf, bufsize);

    Gem_read(thee, skey, sock);
}

/*
 * ***************************************************************************
 * Routine:  Gem_makeCube
 *
 * Purpose:  Generate a unit cube domain.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_makeCube(Gem *thee)
{
    int  skey    = 0;           /* simplex format */
    char *key    = "r";         /* read */
    char *iodev  = "BUFF";      /* buffer */
    char *iofmt  = "ASC";       /* ascii */
    char *iohost = "localhost"; /* localhost (dummy) */
    char *iofile = "0";         /* socket 0 (dummy) */
    Vio *sock;
    char buf[VMAX_BUFSIZE];
    int bufsize = 0;

    bufsize = strlen(GEM_cube);
    VASSERT( bufsize <= VMAX_BUFSIZE );
    strncpy(buf, GEM_cube, VMAX_BUFSIZE);

    VASSERT( VNULL != (sock=Vio_socketOpen(key,iodev,iofmt,iohost,iofile)) );
    Vio_bufTake(sock, buf, bufsize);

    Gem_read(thee, skey, sock);
}

/*
 * ***************************************************************************
 * Routine:  Gem_makeOctahedron
 *
 * Purpose:  Generate a unit octahedron domain.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_makeOctahedron(Gem *thee)
{
    int  skey    = 0;           /* simplex format */
    char *key    = "r";         /* read */
    char *iodev  = "BUFF";      /* buffer */
    char *iofmt  = "ASC";       /* ascii */
    char *iohost = "localhost"; /* localhost (dummy) */
    char *iofile = "0";         /* socket 0 (dummy) */
    Vio *sock;
    char buf[VMAX_BUFSIZE];
    int bufsize = 0;

    bufsize = strlen(GEM_octahedron);
    VASSERT( bufsize <= VMAX_BUFSIZE );
    strncpy(buf, GEM_octahedron, VMAX_BUFSIZE);

    VASSERT( VNULL != (sock=Vio_socketOpen(key,iodev,iofmt,iohost,iofile)) );
    Vio_bufTake(sock, buf, bufsize);

    Gem_read(thee, skey, sock);
}

/*
 * ***************************************************************************
 * Routine:  Gem_makeIcosahedron
 *
 * Purpose:  Generate a unit icosahedron domain.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */
VPUBLIC void Gem_makeIcosahedron(Gem *thee)
{
    int  skey    = 0;           /* simplex format */
    char *key    = "r";         /* read */
    char *iodev  = "BUFF";      /* buffer */
    char *iofmt  = "ASC";       /* ascii */
    char *iohost = "localhost"; /* localhost (dummy) */
    char *iofile = "0";         /* socket 0 (dummy) */
    Vio *sock;
    char buf[VMAX_BUFSIZE];
    int bufsize1 = 0;
    int bufsize2 = 0;

    bufsize1 = strlen(GEM_icosahedron1);
    bufsize2 = strlen(GEM_icosahedron2);
    VASSERT( (bufsize1+bufsize2) <= VMAX_BUFSIZE);
    strncpy(&buf[0], GEM_icosahedron1, bufsize1);
    strncpy(&buf[bufsize1], GEM_icosahedron2, bufsize2);

    VASSERT( VNULL != (sock=Vio_socketOpen(key,iodev,iofmt,iohost,iofile)) );
    Vio_bufTake(sock, buf, VMAX_BUFSIZE);

    Gem_read(thee, skey, sock);
}

