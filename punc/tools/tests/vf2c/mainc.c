/* mainf.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <punc/vf2c.h>"

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* * *************************************************************************** */
/* * PUNC = < Portable Understructure for Numerical Computing > */
/* * Copyright (C) 1994-- Michael Holst */
/* * */
/* * This program is free software; you can redistribute it and/or modify it */
/* * under the terms of the GNU General Public License as published by the */
/* * Free Software Foundation; either version 2 of the License, or (at your */
/* * option) any later version. */
/* * */
/* * This program is distributed in the hope that it will be useful, */
/* * but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */
/* * See the GNU General Public License for more details. */
/* * */
/* * You should have received a copy of the GNU General Public License along */
/* * with this program; if not, write to the Free Software Foundation, Inc., */
/* * 675 Mass Ave, Cambridge, MA 02139, USA. */
/* * */
/* * rcsid="$Id: mainc.c,v 1.6 2010/08/12 05:53:15 fetk Exp $" */
/* * *************************************************************************** */
/* * *************************************************************************** */
/* * File:     mainf.f */
/* * */
/* * Purpose:  Driver program for testing the VF2C. */
/* * */
/* * Author:   Michael Holst */
/* * *************************************************************************** */
/* Main program */ int MAIN__(void)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, 0, 0 };


    s_wsle(&io___1);
    do_lio(&c__9, &c__1, "Hello, Word!", (ftnlen)12);
    e_wsle();
    s_stop("", (ftnlen)0);
    return 0;
} /* MAIN__ */

/* Main program alias */ int main () { MAIN__ (); return 0; }
