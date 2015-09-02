c* ***************************************************************************
c* PUNC = < Portable Understructure for Numerical Computing >
c* Copyright (C) 1994-- Michael Holst
c*
c* This library is free software; you can redistribute it and/or
c* modify it under the terms of the GNU Lesser General Public
c* License as published by the Free Software Foundation; either
c* version 2.1 of the License, or (at your option) any later version.
c*
c* This library is distributed in the hope that it will be useful,
c* but WITHOUT ANY WARRANTY; without even the implied warranty of
c* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
c* Lesser General Public License for more details.
c*
c* You should have received a copy of the GNU Lesser General Public
c* License along with this library; if not, write to the Free Software
c* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
c*
c* rcsid="$Id: mainf.f,v 1.3 2010/08/12 05:52:40 fetk Exp $"
c* ***************************************************************************

c* ***************************************************************************
c* File:     mainf.f
c*
c* Purpose:  Driver program for testing the VF2C.
c*
c* Author:   Michael Holst
c* ***************************************************************************

      program main
      integer n, incx, incy
      double precision dx(3), dy(3)
      double precision function ddot
      n = 3
      incx = 1
      incy = 1
      print*,"mainf: just before call to BLAS::ddot"
      call ddot(n, dx, incx, dy, incy)
      print*,"mainf: just after call to BLAS::ddot"
      stop
      end

