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
 * rcsid="$Id: main.c,v 1.12 2010/08/12 05:19:33 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     main.c
 *
 * Purpose:  Test main driver for the Gem layer.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include <mc/gem.h>

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
VEMBED(rcsid="$Id: main.c,v 1.12 2010/08/12 05:19:33 fetk Exp $")

int main(int argc, char *argv[])
{
    double gluVal;
    int defKey, colKey, pidKey, sockNum, ycoord;
    int mcFileType;
    char sysCmd[80], theSocket[80], theSocketF[80];
    char *rwFlag;
    char *ISKEY, *ISFMT, *IXNAM, *IHVAL;
    char *OSKEY, *OSFMT, *OXNAM, *OHVAL;
    Gem *gm = VNULL;
    PDE *pde = VNULL;
    Vio *sock = VNULL;
    Vio *sock0 = VNULL;
    Vio *sock1 = VNULL;

    Vio_start();

   /*
    ****************************************************************
    * get the vertex and simplex info from the data file
    ****************************************************************
    */

    rwFlag = "r";         /* read(r) or write(w) */
    ISKEY  = "FILE";      /* VIO INPUT DEV type (sdio,file,buff,unix,inet) */
    ISFMT  = "ASC";       /* VIO INPUT DEV format (asc,xdr) */
    IXNAM  = "mcin.m";    /* VIO INPUT DEV file (filename for file I/O) */
    IHVAL  = "localhost"; /* VIO INPUT DEV host (INET hostname or IP addr) */
    VASSERT( VNULL != (sock=Vio_socketOpen(rwFlag,ISKEY,ISFMT,IHVAL,IXNAM)) );

    mcFileType = 0;
    gm = Gem_ctor( VNULL, pde );
    Gem_read(gm, mcFileType, sock);

    Vio_socketClose( &sock );

    defKey  = 0;
    colKey  = 1;
    pidKey  = -1;
    gluVal  = 0.9;

    sockNum = 0;
    ycoord  = 242 * sockNum;
    sprintf(theSocket,"%d", sockNum);
    sprintf(sysCmd,
        "mcsg -asc -wpos 210,210@0,%d -Mci %d &",
         ycoord, sockNum);
    system(sysCmd);

    sockNum = 1;
    ycoord  = 242 * sockNum;
    sprintf(theSocketF,"%d", sockNum);
    sprintf(sysCmd,
        "mcsg -asc -wpos 210,210@0,%d -Mci %d &",
         ycoord, sockNum);
    system(sysCmd);

    sprintf(sysCmd,"%s", "sleep 3");

    rwFlag = "w";
    OSKEY  = "INET"; /* VIO OUTPUT DEV type (sdio,file,buff,unix,inet) */
    OSFMT  = "ASC";  /* VIO OUTPUT DEV format (asc,xdr) */
    OHVAL  = "localhost"; /* VIO OUTPUT DEV host (INET hostname or IP) */
    OXNAM  = "0";    /* VIO OUTPUT DEV name ([ buff | unix | inet ] num) */
    VASSERT(VNULL!=(sock0=Vio_socketOpen(rwFlag,OSKEY,OSFMT,OHVAL,OXNAM)));
    OXNAM  = "1";    /* VIO OUTPUT DEV name ([ buff | unix | inet ] num) */
    VASSERT(VNULL!=(sock1=Vio_socketOpen(rwFlag,OSKEY,OSFMT,OHVAL,OXNAM)));

    sprintf(sysCmd,"%s", "sleep 3");

    system(sysCmd);
    Gem_writeGV(gm, sock0,
        defKey,colKey,pidKey,gluVal, 0, VNULL);
    Gem_writeGV(gm, sock1,
        defKey,colKey,pidKey,gluVal, 1, VNULL);
#if 0
    Gem_write(gm, mcFileType, sock, 0);
#endif

    Vio_socketClose( &sock0 );
    Vio_socketClose( &sock1 );

    Vio_stop();

    /* return */
    return 0;
}

