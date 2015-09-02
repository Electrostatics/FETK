c* ///////////////////////////////////////////////////////////////////////////
c* @file    mblasd.f
c* @author  Michael Holst
c* @brief   Micro version of the BLAS needed for low-level PMG support.
c* @version $Id: mblasd.f,v 1.2 2010/08/12 05:45:33 fetk Exp $
c* @attention
c* @verbatim
c*
c* PMG -- Parallel algebraic MultiGrid
c* Copyright (C) 1994-- Michael Holst.
c*
c* Michael Holst <mholst@math.ucsd.edu>
c* University of California, San Diego
c* Department of Mathematics, 5739 AP&M
c* 9500 Gilman Drive, Dept. 0112
c* La Jolla, CA 92093-0112 USA                                                  
c* http://math.ucsd.edu/~mholst
c*
c* This file is part of PMG.
c*
c* PMG is free software; you can redistribute it and/or modify
c* it under the terms of the GNU General Public License as published by
c* the Free Software Foundation; either version 2 of the License, or
c* (at your option) any later version.
c*
c* PMG is distributed in the hope that it will be useful,
c* but WITHOUT ANY WARRANTY; without even the implied warranty of
c* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
c* GNU General Public License for more details.
c*
c* You should have received a copy of the GNU General Public License
c* along with PMG; if not, write to the Free Software
c* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
c*
c* Linking PMG statically or dynamically with other modules is making a
c* combined work based on PMG. Thus, the terms and conditions of the GNU
c* General Public License cover the whole combination.
c* 
c* SPECIAL GPL EXCEPTION
c* In addition, as a special exception, the copyright holders of PMG
c* give you permission to combine the PMG program with free software
c* programs and libraries that are released under the GNU LGPL or with
c* code included in releases of ISIM, PMV, PyMOL, SMOL, VMD, and Vision.
c* Such combined software may be linked with PMG and redistributed together 
c* in original or modified form as mere aggregation without requirement that 
c* the entire work be under the scope of the GNU General Public License.
c* This special exception permission is also extended to any software listed
c* in the SPECIAL GPL EXCEPTION clauses by the FEtk and APBS libraries.
c* 
c* Note that people who make modified versions of PMG are not obligated
c* to grant this special exception for their modified versions; it is
c* their choice whether to do so. The GNU General Public License gives
c* permission to release a modified version without this exception; this
c* exception also makes it possible to release a modified version which
c* carries forward this exception.
c*
c* @endverbatim
c* ///////////////////////////////////////////////////////////////////////////

      subroutine daxpy(n,alpha,x,istep,y,jstep)
c* *********************************************************************
c* purpose:
c*
c*    parallel/vector vector saxpy.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      double precision x(*),y(*),alpha
      integer          n,istep,jstep,i,ii,nproc,ipara,ivect
      parameter        (nproc=1)
c*
cmdir 0 0
c*
c*    *** find parallel loops (ipara), remainder (ivect) ***
      ipara = n / nproc
      ivect = mod(n,nproc)
c*
c*    *** do parallel loops ***
cmdir 2 1
      do 10 ii = 1, nproc
cmdir 2 2
         do 11 i = 1+(ipara*(ii-1)), ipara*ii
            y(i) = y(i) + alpha * x(i)
 11      continue
 10   continue
c*
c*    *** do vector loops ***
cmdir 1 1
      do 20 i = ipara*nproc+1, n
         y(i) = y(i) + alpha * x(i)
 20   continue
c*
c*    *** return and end ***
      return
      end
      subroutine dcopy(n,x,istep,y,jstep)
c* *********************************************************************
c* purpose:
c*
c*    parallel/vector vector copy.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      double precision x(*),y(*)
      integer          n,istep,jstep,i,ii,nproc,ipara,ivect
      parameter        (nproc=1)
c*
cmdir 0 0
c*
c*    *** find parallel loops (ipara), remainder (ivect) ***
      ipara = n / nproc
      ivect = mod(n,nproc)
c*
c*    *** do parallel loops ***
cmdir 2 1
      do 10 ii = 1, nproc
cmdir 2 2
         do 11 i = 1+(ipara*(ii-1)), ipara*ii
            y(i) = x(i) 
 11      continue
 10   continue
c*
c*    *** do vector loops ***
cmdir 1 1
      do 20 i = ipara*nproc+1, n
         y(i) = x(i) 
 20   continue
c*
c*    *** return and end ***
      return
      end
      function dasum(n,x,istep)
c* *********************************************************************
c* purpose:
c*
c*    parallel/vector sum of vector components.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      double precision x(*)
      double precision dasum,dnrm1
      integer          n,istep
c*
cmdir 0 0
c*
c*    *** call the max-norm function ***
      dasum = dnrm1(n,x,istep)
c*
c*    *** return and end ***
      return
      end
      function dnrm1(n,x,istep)
c* *********************************************************************
c* purpose:
c*
c*    parallel/vector vector norm.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      double precision x(*)
      double precision tmp,dnrm1
      integer          n,istep,i,ii,nproc,ipara,ivect
      parameter        (nproc=1)
c*
cmdir 0 0
c*
c*    *** initialize ***
      tmp = 0.0d0
c*
c*    *** find parallel loops (ipara), remainder (ivect) ***
      ipara = n / nproc
      ivect = mod(n,nproc)
c*
c*    *** do parallel loops ***
cmdir 2 1
      do 10 ii = 1, nproc
cmdir 2 2
         do 11 i = 1+(ipara*(ii-1)), ipara*ii
            tmp = tmp + dabs(x(i))
 11      continue
 10   continue
c*
c*    *** do vector loops ***
cmdir 1 1
      do 20 i = ipara*nproc+1, n
         tmp = tmp + dabs(x(i))
 20   continue
c*
c*    *** finish up ***
      dnrm1 = tmp
c*
c*    *** return and end ***
      return
      end
      function dnrm2(n,x,istep)
c* *********************************************************************
c* purpose:
c*
c*    parallel/vector vector norm.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      double precision x(*)
      double precision tmp,dnrm2
      integer          n,istep,i,ii,nproc,ipara,ivect
      parameter        (nproc=1)
c*
cmdir 0 0
c*
c*    *** initialize ***
      tmp = 0.0d0
c*
c*    *** find parallel loops (ipara), remainder (ivect) ***
      ipara = n / nproc
      ivect = mod(n,nproc)
c*
c*    *** do parallel loops ***
cmdir 2 1
      do 10 ii = 1, nproc
cmdir 2 2
         do 11 i = 1+(ipara*(ii-1)), ipara*ii
            tmp = tmp + x(i)*x(i)
 11      continue
 10   continue
c*
c*    *** do vector loops ***
cmdir 1 1
      do 20 i = ipara*nproc+1, n
         tmp = tmp + x(i)*x(i)
 20   continue
c*
c*    *** finish up ***
      dnrm2 = dsqrt(tmp)
c*
c*    *** return and end ***
      return
      end
      function dnrm8(n,x,istep)
c* *********************************************************************
c* purpose:
c*
c*    parallel/vector vector norm.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      double precision x(*)
      double precision tmp,dnrm8
      integer          n,istep,i,ii,nproc,ipara,ivect
      parameter        (nproc=1)
c*
cmdir 0 0
c*
c*    *** initialize ***
      tmp = 0.0d0
c*
c*    *** find parallel loops (ipara), remainder (ivect) ***
      ipara = n / nproc
      ivect = mod(n,nproc)
c*
c*    *** do parallel loops ***
cmdir 2 1
      do 10 ii = 1, nproc
cmdir 2 2
         do 11 i = 1+(ipara*(ii-1)), ipara*ii
            tmp = dmax1( tmp , dabs(x(i)) )
 11      continue
 10   continue
c*
c*    *** do vector loops ***
cmdir 1 1
      do 20 i = ipara*nproc+1, n
         tmp = dmax1( tmp , dabs(x(i)) )
 20   continue
c*
c*    *** finish up ***
      dnrm8 = tmp
c*
c*    *** return and end ***
      return
      end
      subroutine dscal(n,fac,x,istep)
c* *********************************************************************
c* purpose:
c*
c*    parallel/vector vector scale.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      double precision x(*),fac
      integer          n,istep,i,ii,nproc,ipara,ivect
      parameter        (nproc=1)
c*
cmdir 0 0
c*
c*    *** find parallel loops (ipara), remainder (ivect) ***
      ipara = n / nproc
      ivect = mod(n,nproc)
c*
c*    *** do parallel loops ***
cmdir 2 1
      do 10 ii = 1, nproc
cmdir 2 2
         do 11 i = 1+(ipara*(ii-1)), ipara*ii
            x(i) = fac*x(i)
 11      continue
 10   continue
c*
c*    *** do vector loops ***
cmdir 1 1
      do 20 i = ipara*nproc+1, n
         x(i) = fac*x(i)
 20   continue
c*
c*    *** return and end ***
      return
      end
      function ddot(n,x,istep,y,jstep)
c* *********************************************************************
c* purpose:
c*
c*    parallel/vector dot product.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      double precision x(*),y(*),ddot
      integer          n,istep,jstep,i,ii,nproc,ipara,ivect
      parameter        (nproc=1)
c*
cmdir 0 0
c*
c*    *** initialize ***
      ddot = 0.0d0
c*
c*    *** find parallel loops (ipara), remainder (ivect) ***
      ipara = n / nproc
      ivect = mod(n,nproc)
c*
c*    *** do parallel loops ***
cmdir 2 1
      do 10 ii = 1, nproc
cmdir 2 2
         do 11 i = 1+(ipara*(ii-1)), ipara*ii
            ddot = ddot + x(i)*y(i)
 11      continue
 10   continue
c*
c*    *** do vector loops ***
cmdir 1 1
      do 20 i = ipara*nproc+1, n
         ddot = ddot + x(i)*y(i)
 20   continue
c*
c*    *** return and end ***
      return
      end
      function idamax(n,sx,incx)
c* *********************************************************************
c* purpose:
c*
c*    parallel/vector icamax.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      integer          idamax,n,ns,incx,ii,i
      double precision smax,xmag
      double precision sx(*)
c*
cmdir 0 0
c*
      idamax = 0
      if(n.le.0) return
      idamax = 1
      if(n.le.1)return
      if(incx.eq.1)goto 20
c*
c*       code for increments not equal to 1.
c*
      smax = dabs(sx(1))
      ns = n*incx
      ii = 1
      do 10 i=1,ns,incx
          xmag = dabs(sx(i))
          if(xmag.le.smax) go to 40
          idamax = ii
          smax = xmag
 40       ii = ii + 1
 10   continue
      return
c*
c*    code for increments equal to 1.
c*
 20   smax = dabs(sx(1))
      do 30 i = 2,n
         xmag = dabs(sx(i))
         if(xmag.le.smax) go to 30
         idamax = i
         smax = xmag
 30   continue
      return
      end

