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
 * rcsid="$Id: svio.c,v 1.5 2010/08/12 05:18:42 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     svio.c
 *
 * Purpose:  Class Vlines: super vio functions.
 *
 * Author:   Stephen Bond and Michael Holst
 * ***************************************************************************
 */

#include "svio_p.h"

VEMBED(rcsid="$Id: svio.c,v 1.5 2010/08/12 05:18:42 fetk Exp $")

/*
 * ***************************************************************************
 * Class Vlines: Inlineable methods
 * ***************************************************************************
 */
#if !defined(VINLINE_VLINES)

#endif /* if !defined(VINLINE_VLINES) */
/*
 * ***************************************************************************
 * Class Vlines: Non-inlineable methods
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * Routine:  SVio_ctor
 *
 * Purpose:  Construct the Vio socket container object.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC SVio* SVio_ctor(void)
{
    SVio *thee = VNULL;

    thee = (SVio*)calloc( 1, sizeof(SVio) );
    VJMPERR1( thee != VNULL );

    strncpy( thee->iodev,  "", VMAX_BUFSIZE );
    strncpy( thee->iofmt,  "", VMAX_BUFSIZE );
    strncpy( thee->iohost, "", VMAX_BUFSIZE );
    strncpy( thee->iofile, "", VMAX_BUFSIZE );

    thee->colKeyGV   =  1;
    thee->chartKeyGV = -1;
    thee->fkeyGV     =  1;
    thee->gluValGV   =  1.0;

    thee->sock    = VNULL;
    thee->buf     = VNULL;
    thee->bufsize =  0;

    return thee;

  VERROR1:
    fprintf(stderr,"SVio_ctor: bailing out.\n");
    return VNULL;

}

/*
 * ***************************************************************************
 * Routine:  SVio_dtor
 *
 * Purpose:  Destroy the Vio socket container object.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void SVio_dtor(SVio **thee)
{

  if ((*thee) != VNULL) {
        if ((*thee)->buf != VNULL) {
            free( (*thee)->buf );
            (*thee)->buf = VNULL;
	    (*thee)->bufsize = 0;
        }

	if ((*thee)->sock != VNULL) {
	    Vio_dtor( &((*thee)->sock) );
	}

        free( (*thee) );
        (*thee) = VNULL;
  }

}

/*
 * ***************************************************************************
 * Routine:  Vsh_SVioSetup
 *
 * Purpose:  Setup for I/O commands using SVio.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC SVio *Vsh_SVioSetup(Vsh *thee, char *key)
{
    SVio *vsock;

    /* setup for a read */
    if (!strcmp("r",key)) {

        VJMPERR1( VNULL != (vsock = SVio_ctor()) );

        strncpy(vsock->iohost,Vsh_getenv(thee,"IHVAL"),VMAX_BUFSIZE);
        strncpy(vsock->rwkey,"r",1);

        if (!strcmp("sdio",Vsh_getenv(thee,"ISKEY"))) {
            strncpy(vsock->iodev,"SDIO",VMAX_BUFSIZE);
            strncpy(vsock->iofile,"console",VMAX_BUFSIZE);
        } else if (!strcmp("file",Vsh_getenv(thee,"ISKEY"))) {
            strncpy(vsock->iodev,"FILE",VMAX_BUFSIZE);
            strncpy(vsock->iofile,Vsh_getenv(thee,"IFNAM"),VMAX_BUFSIZE);
        } else if (!strcmp("buff",Vsh_getenv(thee,"ISKEY"))) {
            strncpy(vsock->iodev,"BUFF",VMAX_BUFSIZE);
            strncpy(vsock->iofile,Vsh_getenv(thee,"ISNAM"),VMAX_BUFSIZE);
        } else if (!strcmp("unix",Vsh_getenv(thee,"ISKEY"))) {
            strncpy(vsock->iodev,"UNIX",VMAX_BUFSIZE);
            strncpy(vsock->iofile,Vsh_getenv(thee,"ISNAM"),VMAX_BUFSIZE);
        } else if (!strcmp("inet",Vsh_getenv(thee,"ISKEY"))) {
            strncpy(vsock->iodev,"INET",VMAX_BUFSIZE);
            strncpy(vsock->iofile,Vsh_getenv(thee,"ISNAM"),VMAX_BUFSIZE);
        } else {
            Vnm_print(2,"Vsh_SVioSetup: Internal logic error.\n");
            VJMPERR2( 0 );
        }
        if (!strcmp("asc",Vsh_getenv(thee,"ISFMT"))) {
            strncpy(vsock->iofmt,"ASC", VMAX_BUFSIZE);
        } else if (!strcmp("xdr",Vsh_getenv(thee,"ISFMT"))) {
            strncpy(vsock->iofmt,"XDR", VMAX_BUFSIZE);
        } else {
            Vnm_print(2,"Vsh_SVioSetup: Internal logic error.\n");
            VJMPERR2( 0 );
        }

	/* set the read format type */
	vsock->printtype = -1;

    /* setup for a write */
    } else if (!strcmp("w",key)) {

        VJMPERR1( VNULL != (vsock = SVio_ctor()) );

        strncpy(vsock->iohost,Vsh_getenv(thee,"OHVAL"),VMAX_BUFSIZE);
        strncpy(vsock->rwkey,"w",1);

        if (!strcmp("sdio",Vsh_getenv(thee,"OSKEY"))) {
            strncpy(vsock->iodev,"SDIO",VMAX_BUFSIZE);
            strncpy(vsock->iofile,"console",VMAX_BUFSIZE);
        } else if (!strcmp("file",Vsh_getenv(thee,"OSKEY"))) {
            strncpy(vsock->iodev,"FILE",VMAX_BUFSIZE);
            strncpy(vsock->iofile,Vsh_getenv(thee,"OFNAM"),VMAX_BUFSIZE);
        } else if (!strcmp("buff",Vsh_getenv(thee,"OSKEY"))) {
            strncpy(vsock->iodev,"BUFF",VMAX_BUFSIZE);
            strncpy(vsock->iofile,Vsh_getenv(thee,"OSNAM"),VMAX_BUFSIZE);
        } else if (!strcmp("unix",Vsh_getenv(thee,"OSKEY"))) {
            strncpy(vsock->iodev,"UNIX",VMAX_BUFSIZE);
            strncpy(vsock->iofile,Vsh_getenv(thee,"OSNAM"),VMAX_BUFSIZE);
        } else if (!strcmp("inet",Vsh_getenv(thee,"OSKEY"))) {
            strncpy(vsock->iodev,"INET",VMAX_BUFSIZE);
            strncpy(vsock->iofile,Vsh_getenv(thee,"OSNAM"),VMAX_BUFSIZE);
        } else {
            Vnm_print(2,"Vsh_SVioSetup: Internal logic error.\n");
            VJMPERR2( 0 );
        }

        if (!strcmp("asc",Vsh_getenv(thee,"OSFMT"))) {
            strncpy(vsock->iofmt,"ASC", VMAX_BUFSIZE);
        } else if (!strcmp("xdr",Vsh_getenv(thee,"OSFMT"))) {
            strncpy(vsock->iofmt,"XDR", VMAX_BUFSIZE);
        } else {
            Vnm_print(2,"Vsh_SVioSetup: Internal logic error.\n");
            VJMPERR2( 0 );
        }

	/* set the print format type */
	vsock->printtype = Vsh_getenvInt(thee,"PTYPE");

        /* set the GV format options */
	vsock->colKeyGV   =  Vsh_getenvInt(thee,"CKEY");
	vsock->chartKeyGV =  Vsh_getenvInt(thee,"DKEY");
	vsock->gluValGV   =  Vsh_getenvReal(thee,"GVAL");
	vsock->fkeyGV     =  Vsh_getenvInt(thee,"FKEY");

    } else {
        Vnm_print(2,"Vsh_SVioSetup: Internal logic error.\n");
        VJMPERR2( 0 );
    }

    /* associate the buffer */
    SVio_bufTake(vsock, thee->buf, thee->bufsize);

    return vsock;

  VERROR1:
    Vnm_print(2,"Vsh_SVioSetup: null pointer, bailing out.\n");
    return VNULL;
  VERROR2:
    Vnm_print(2,"Vsh_SVioSetup: bailing out.\n");
    return VNULL;

}

/*
 * ***************************************************************************
 * Routine:  Vsh_SVioCleanup
 *
 * Purpose:  Cleanup after I/O commands using SVio.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Vsh_SVioCleanup(Vsh *thee, SVio **vsock)
{
    VJMPERR1( VNULL != thee );
    VJMPERR1( VNULL != *vsock );

    /* grab the buffer before destroying the socket */
    thee->bufsize = SVio_bufSize(*vsock);
    thee->buf     = SVio_bufGive(*vsock);

    /* return without error */
    SVio_dtor( vsock );
    return;

  VERROR1:
    Vnm_print(2,"Vsh_SVioCleanup: bailing out.\n");
    return;
}

/*
 * ***************************************************************************
 * Routine:  SVio_initStructure
 *
 * Purpose:  Initialize the Vio socket container object.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void SVio_initStructure(SVio *thee, const char *rwkey,
    const char *iodev, const char *iofmt, const char *iohost,
    const char *iofile, char *buf, int bufsize, int ptype)
{
    VJMPERR1( thee != VNULL );

    strncpy( thee->iodev,  iodev,  VMAX_BUFSIZE );
    strncpy( thee->iofmt,  iofmt,  VMAX_BUFSIZE );
    strncpy( thee->iohost, iohost, VMAX_BUFSIZE );
    strncpy( thee->iofile, iofile, VMAX_BUFSIZE );
    thee->printtype = ptype;

    thee->sock      = VNULL;
    thee->buf       = buf;
    thee->bufsize   = bufsize;

    return;

  VERROR1:
    fprintf(stderr,"SVio_initStructure: bailing out.\n");
    return;

}

/*
 * ***************************************************************************
 * Routine:  SVio_bufSize
 *
 * Purpose:  Return the length of the internal buffer.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC int SVio_bufSize(SVio *thee)
{
    /* return without error */
    return thee->bufsize;
}

/*
 * ***************************************************************************
 * Routine:  SVio_bufGive
 *
 * Purpose:  Return the pointer to the internal buffer.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC char* SVio_bufGive(SVio *thee)
{
    char *tmp;

    /* grab the pointer */
    tmp = thee->buf;

    /* reset things for the hand-off */
    thee->bufsize = 0;
    thee->buf     = VNULL;

    /* return without error */
    return tmp;
}

/*
 * ***************************************************************************
 * Routine:  SVio_bufTake
 *
 * Purpose:  Set the pointer to the internal buffer.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void SVio_bufTake(SVio *thee, char *buf, int bufsize)
{
    /* clear the internal buffer */
    if (thee->buf != VNULL) {
        free( thee->buf );
        thee->buf = VNULL;
    }

    /* now set the buffer */
    thee->buf     = buf;
    thee->bufsize = bufsize;

    /* return without error */
    return;

}


/*
 * ***************************************************************************
 * Routine:  Aprx_writeSVio
 *
 * Purpose:  Write a finite element mesh or mesh function to a socket.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPUBLIC void Aprx_writeSVio(Aprx *thee, int printlabel, Bvec *w0, SVio *vsock)
{

    char fnam[VMAX_BUFSIZE];
#if 0
    char c;
#endif
    int maxprintlabel = 1000;

    /* STEVE SHOULD FIX THIS LATER */
    if ( vsock->printtype == 0 && !strcmp( vsock->iodev, "FILE" ) ) {
        sprintf( fnam, "%s", vsock->iofile );
	printlabel = printlabel%maxprintlabel;
        Char_enumToken( fnam, "NUM", printlabel );
        Bvec_printSp( w0, fnam );
	return;
    }

    if ( !strcmp( vsock->iodev, "FILE" ) ) {
        sprintf( fnam, "%s", vsock->iofile );
	printlabel = printlabel%maxprintlabel;
        Char_enumToken( fnam, "NUM", printlabel );
	vsock->sock = Vio_socketOpen( "w", vsock->iodev, vsock->iofmt,
				      vsock->iohost, fnam );
    } else {
        vsock->sock = Vio_socketOpen( "w", vsock->iodev, vsock->iofmt,
				      vsock->iohost, vsock->iofile );
    }


    VJMPERR1( VNULL != vsock->sock);
    vsock->sock->VIObuffer    = vsock->buf;
    vsock->sock->VIObufferLen = vsock->bufsize;
    vsock->sock->VIObufferPtr = 0;

    /* format choice (0=Matlab,1=GV,2=GMV,3=DX,4=UCD) */
    switch ( vsock->printtype ) {

        case 0:  Vnm_print(2,"Alg_writeSVio: unsupported print type.\n");
	         break;
        case 1:  Aprx_writeGEOM( thee, vsock->sock, 1,
		     vsock->colKeyGV, vsock->chartKeyGV, vsock->gluValGV,
		     vsock->fkeyGV, w0, "GV" );
	         break;
        case 2:  Aprx_writeSOL( thee, vsock->sock, w0, "GMV" );
	         break;
        case 3:  Aprx_writeSOL( thee, vsock->sock, w0, "DX" );
                 break;
        case 4:  Aprx_writeSOL( thee, vsock->sock, w0, "UCD" );
                 break;
        case 5:  Aprx_writeSOL( thee, vsock->sock, w0, "TEC" );
                 break;
        default:
	         Vnm_print(2,"Alg_writeSVio: unsupported print type.\n");
		 break;
    }

    vsock->buf     = vsock->sock->VIObuffer;
    vsock->bufsize = vsock->sock->VIObufferLen;
    vsock->sock->VIObuffer = VNULL;
    vsock->sock->VIObufferLen = 0;

    Vio_socketClose( &(vsock->sock) );

#if 0
    if ( strcmp( vsock->iodev, "FILE" ) ) {
        Vnm_print(2,"AM_tStep: Press <return> to continue..");
        while ( ( c = getchar() ) != '\n' ) Vnm_print(2,"%s",c);
    }
#endif

    return;

 VERROR1:
    Vnm_print(2,"Alg_writeSVio: bailing out.\n");
    return;
}

/*
 * ***************************************************************************
 * Routine:  Char_enumToken
 *
 * Purpose:  Replace a substring by a zero-padded integer.
 *
 * Author:   Stephen Bond
 * ***************************************************************************
 */
VPRIVATE void Char_enumToken(char *thee, const char *token, int ilabel)
{
    char numnam[VMAX_BUFSIZE], numfmt[7], *tmpnam;
    int  tokenlen;

    tokenlen = strlen(token);
    sprintf( numfmt, "%%%dd", tokenlen);

    if ( (tmpnam = strstr(thee,token)) == VNULL ) {
      sprintf( thee, "%s%s", token, thee );
    }

    while ( NULL != (tmpnam = strstr(thee,token)) ) {
      sprintf( numnam, numfmt, ilabel);
      strncpy( tmpnam, numnam, strlen(numnam));
    }

    while ( NULL != (tmpnam = strstr(thee," ")) ) {
      strncpy( tmpnam, "0", 1 );
    }

}
