/*
 * ***************************************************************************
 * PUNC = < Portable Understructure for Numerical Computing >
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
 * rcsid="$Id: mainc.c,v 1.3 2010/08/12 05:52:43 fetk Exp $"
 * ***************************************************************************
 */

/*
 * ***************************************************************************
 * File:     main.c
 *
 * Purpose:  Driver program for testing the BLAS.
 *
 * Author:   Michael Holst
 * ***************************************************************************
 */

#include <punc/punc.h>

#define VEMBED(rctag) VPRIVATE const char* rctag; \
    static void* use_rcsid=(0 ? &use_rcsid : (void*)&rcsid);
VEMBED(rcsid="$Id: mainc.c,v 1.3 2010/08/12 05:52:43 fetk Exp $")

int main(int argc, char **argv) {
    int n, incx, incy;
    double dx[3], dy[3];
    n = 3;
    incx = 1;
    incy = 1;
    fprintf(stderr,"mainc: just before call to BLAS::ddot\n");
    (void)ddot(&n, dx, &incx, dy, &incy);
    fprintf(stderr,"mainc: just after call to BLAS::ddot\n");
    return 0;
}

