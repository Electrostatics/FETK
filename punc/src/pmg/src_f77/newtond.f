c* ///////////////////////////////////////////////////////////////////////////
c* @file    newtond.f
c* @author  Michael Holst
c* @brief   The main Newton iteration.
c* @version $Id: newtond.f,v 1.2 2010/08/12 05:45:36 fetk Exp $
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

      subroutine fnewton(nx,ny,nz,x,iz,w0,w1,w2,w3,
     2   istop,itmax,iters,ierror,nlev,ilev,nlev_real,mgsolv,
     3   iok,iinfo,epsiln,errtol,omega,nu1,nu2,mgsmoo,
     4   cprime,rhs,xtmp,
     5   ipc,rpc,pc,ac,cc,fc,tru)
c* *********************************************************************
c* purpose:
c*
c*    nested iteration for an inexact-newton-multilevel method.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
c*
c*    *** other declarations ***
      integer          ipc(*),iz(50,*),iok,ilev,iinfo,nlev,itmax
      integer          iters,ierror,level,itmxd,nlevd,iterd,iokd,istop
      integer          nx,ny,nz,nxf,nyf,nzf,nxc,nyc,nzc,nlev_real,istpd
      integer          nu1,nu2,mgsmoo,mgsolv
      double precision epsiln,errd,errtol,omega
      double precision x(*),w0(*),w1(*),w2(*),w3(*)
      double precision rpc(*),pc(*),ac(*),cc(*),fc(*),tru(*)
      double precision cprime(*),rhs(*),xtmp(*)
c*
c*    *** recover gridsizes ***
      nxf = nx
      nyf = ny
      nzf = nz
      call mkcors(nlev-1,nxf,nyf,nzf,nxc,nyc,nzc)
c*
c*    *** move up grids: interpolate solution to finer, do newton ***
      if (iinfo.ne.0) then
         write(6,100)'% FNEWTON: starting:',nxf,nyf,nzf,nxc,nyc,nzc
 100     format(a,2(2x,' [',i3,',',i3,',',i3,'] '))
      endif
      do 10 level = nlev_real, ilev+1, -1
c*
c*       *** call mv cycle ***
         errd  = errtol
         itmxd = 1000
         nlevd = nlev_real - level + 1
         iterd = 0
         iokd  = iok
         istpd = istop
         call newton(nxc,nyc,nzc,x,iz,w0,w1,w2,w3,
     2      istpd,itmxd,iterd,ierror,nlevd,level,nlev_real,mgsolv,
     3      iokd,iinfo,epsiln,errd,omega,nu1,nu2,mgsmoo,
     4      cprime,rhs,xtmp,
     5      ipc,rpc,pc,ac,cc,fc,tru)
c*
c*       *** find new grid size ***
         call mkfine(1,nxc,nyc,nzc,nxf,nyf,nzf)
c*
c*       *** interpolate to next finer grid (use correct bc's) ***
         call interp(nxc,nyc,nzc,nxf,nyf,nzf,
     2      x(iz(1,level)),x(iz(1,level-1)),pc(iz(11,level-1)))
CZZZ     call ninterp(nxc,nyc,nzc,nxf,nyf,nzf,
CZZZ 2      x(iz(1,level)),x(iz(1,level-1)),pc(iz(11,level-1)),
CZZZ 3      ipc(iz(5,level-1)),rpc(iz(6,level-1)),
CZZZ 4      ac(iz(7,level-1)),cc(iz(1,level-1)),fc(iz(1,level-1)))
c*
c*       *** new grid size ***
         nxc = nxf
         nyc = nyf
         nzc = nzf
 10   continue
c*
c*    *** call mv cycle ***
      level = ilev 
      call newton(nx,ny,nz,x,iz,w0,w1,w2,w3,
     2   istop,itmax,iters,ierror,nlev,level,nlev_real,mgsolv,
     3   iok,iinfo,epsiln,errtol,omega,nu1,nu2,mgsmoo,
     4   cprime,rhs,xtmp,
     5   ipc,rpc,pc,ac,cc,fc,tru)
c*
c*    *** return and end ***
      return
      end
      subroutine newton(nx,ny,nz,x,iz,w0,w1,w2,w3,
     2   istop,itmax,iters,ierror,nlev,ilev,nlev_real,mgsolv,
     3   iok,iinfo,epsiln,errtol,omega,nu1,nu2,mgsmoo,
     4   cprime,rhs,xtmp,
     5   ipc,rpc,pc,ac,cc,fc,tru)
c* *********************************************************************
c* purpose:
c*
c*    inexact-newton-multilevel method.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
c*
c*    *** other declarations ***
      integer          ipc(*),iz(50,*),iok,ilev,iinfo,nlev,level,lev
      integer          itmax,iters,ierror,istop,nu1,nu2,mgsmoo
      integer          itmax_s,iters_s,ierror_s,iok_s,iinfo_s,istop_s
      integer          nx,ny,nz,nlev_real,mgsolv
      double precision errtol,epsiln,omega,errtol_s,ord,bigc
      double precision rsden,rsnrm,orsnrm,xnrm1,xnrm2,xdot
      double precision x(*),w0(*),w1(*),w2(*),w3(*)
      double precision rpc(*),pc(*),ac(*),cc(*),fc(*),tru(*)
      double precision cprime(*),rhs(*),xtmp(*)
c*
c*    *** local variables ***
      double precision xnorm_old,xnorm_new,damp,xnorm_med,xnorm_den
      double precision rho_max,rho_min,rho_max_mod,rho_min_mod,errtol_p
      integer          iter_d,itmax_d,mode,idamp,ipkey
      integer          itmax_p,iters_p,iok_p,iinfo_p
c*
c*    *** recover level information ***
      level = 1
      lev   = (ilev-1)+level
c*
c*    *** do some i/o if requested ***
      if (iinfo.ne.0) then
         write(6,100)'% NEWTON: starting: ',nx,ny,nz
 100     format(a,(2x,' [',i3,',',i3,',',i3,'] '))
      endif
c*
c*    *** initial wall clock ***
      if (iok.ne.0) then
         call prtini(istop)
         call prtstp(iok,-1,0.0d0,0.0d0,0.0d0)
      endif
c*
c*    **************************************************************
c*    *** note: if (iok.ne.0) then:  use a stopping test.        ***
c*    ***       else:  use just the itmax to stop iteration.     ***
c*    **************************************************************
c*    *** istop=0 most efficient (whatever it is)                ***
c*    *** istop=1 relative residual                              ***
c*    *** istop=2 rms difference of successive iterates          ***
c*    *** istop=3 relative true error (provided for testing)     ***
c*    **************************************************************
c*
c*    *** compute denominator for stopping criterion ***
      if (istop .eq. 0) then
         rsden = 1.0d0
      elseif (istop .eq. 1) then
c*       *** compute initial residual with zero initial guess ***
c*       *** this is analogous to the linear case where one can ***
c*       *** simply take norm of rhs for a zero initial guess ***
         call azeros(nx,ny,nz,w1)
         call nmresid(nx,ny,nz,
     2      ipc(iz(5,lev)),rpc(iz(6,lev)),
     3      ac(iz(7,lev)),cc(iz(1,lev)),fc(iz(1,lev)),
     4      w1,w2,w3)
         rsden = xnrm1(nx,ny,nz,w2)
      elseif (istop .eq. 2) then
         rsden = dsqrt(dble(nx*ny*nz))
      elseif (istop .eq. 3) then
         rsden = xnrm2(nx,ny,nz,tru(iz(1,lev)))
      elseif (istop .eq. 4) then
         rsden = xnrm2(nx,ny,nz,tru(iz(1,lev)))
      elseif (istop .eq. 5) then
         call nmatvec(nx,ny,nz,
     2      ipc(iz(5,lev)),rpc(iz(6,lev)),
     3      ac(iz(7,lev)),cc(iz(1,lev)),
     4      tru(iz(1,lev)),w1,w2)
         rsden = dsqrt(xdot(nx,ny,nz,tru(iz(1,lev)),w1))
      else
         print*,'% NEWTON: bad istop value... '
      endif
      if (rsden.eq.0.0d0) then
         rsden = 1.0d0
         print*,'% NEWTON: rhs is zero...'
      endif
      rsnrm = rsden
      orsnrm = rsnrm
      if (iok.ne.0) call prtstp (iok,0,rsnrm,rsden,orsnrm)
c*
c* *********************************************************************
c* *** begin newton iteration
c* *********************************************************************
c*
c*    *** now compute residual with the initial guess ***
      call nmresid(nx,ny,nz,
     2   ipc(iz(5,lev)),rpc(iz(6,lev)),
     3   ac(iz(7,lev)),cc(iz(1,lev)),fc(iz(1,lev)),
     4   x(iz(1,lev)),w0,w2)
      xnorm_old = xnrm1(nx,ny,nz,w0)
      if (iok.ne.0) then
         xnorm_den = rsden
      else
         xnorm_den = xnorm_old
      endif
c*
c* *********************************************************************
c* *** begin the loop 
c* *********************************************************************
c*
c*    *** setup for the looping ***
      print*,'% NEWTON: damping enabled...'
      idamp  = 1
      iters  = 0 
 30   continue
         iters  = iters  + 1
c*
c*       *** save iterate if stop test will use it on next iter ***
         if (istop .eq. 2) call xcopy(nx,ny,nz,x(iz(1,lev)),
     2      tru(iz(1,lev)))
c*
c*       *** compute the current jacobian system and rhs ***
         ipkey = ipc(10)
         call getjac (nx,ny,nz,nlev_real,iz,ilev,ipkey,
     2      x,w0,cprime,rhs,cc,pc)
c*
c* ***** *** determine number of correct digits in current residual ***
c* ***** if (lev .eq. 1) then
c* *****    itmax_s = -idnint(dlog10(xnorm_old/xnorm_den))
c* *****    itmax_s = max0(itmax_s,1)
c* ***** else
c* *****    itmax_s = 10
c* ***** endif
c* ***** itmax_s = 1000
c* ***** print*,'% NEWTON: using itmax_s: ',itmax_s
c*
c*       *** algorithm 5.3 in the thesis, test version (1') ***
c*       *** global-superlinear convergence ***
         bigc = 1.0d0
         ord  = 2.0d0
         errtol_s  = dmin1((0.9*xnorm_old),(bigc*xnorm_old**ord))
         print*,'% NEWTON: using errtol_s: ',errtol_s
c*
c*       *** do a linear multigrid solve of the newton equations ***
         call azeros(nx,ny,nz,xtmp(iz(1,lev)))
         itmax_s   = 1000
         istop_s   = 0
         iters_s   = 0
         ierror_s  = 0
         iok_s     = 0
         iinfo_s   = 0
         if ((iinfo .ge. 2) .and. (ilev .eq. 1)) iok_s = 2
         call mvcs(nx,ny,nz,xtmp,iz,w0,w1,w2,w3,
     2      istop_s,itmax_s,iters_s,ierror_s,
     3      nlev,ilev,nlev_real,mgsolv,
     4      iok_s,iinfo_s,epsiln,errtol_s,omega,nu1,nu2,mgsmoo,
     5      ipc,rpc,pc,ac,cprime,rhs,tru)
c*
c*       **************************************************************
c*       *** note: rhs and cprime are now available as temp vectors ***
c*       **************************************************************
c*
c*       *** if damping is still enabled -- doit ***
         if (idamp .eq. 1) then
c*
c*          *** try the correction ***
            call xcopy(nx,ny,nz,x(iz(1,lev)),w1)
            damp = 1.0d0
            call xaxpy(nx,ny,nz,damp,xtmp(iz(1,lev)),w1)
            call nmresid(nx,ny,nz,
     2         ipc(iz(5,lev)),rpc(iz(6,lev)),
     3         ac(iz(7,lev)),cc(iz(1,lev)),fc(iz(1,lev)),
     4         w1,w0,rhs(iz(1,lev)))
            xnorm_new = xnrm1(nx,ny,nz,w0)
c*
c*          *** damping is still enabled -- doit ***
            damp    = 1.0d0
            iter_d  = 0
            itmax_d = 10
            mode    = 0
            write(6,110)
     2         'NEWTON: attempting damping: iter_d, relres = ',
     3         iter_d,(xnorm_new/xnorm_den)
 110           format('% ',a,i5,1pe10.2)
 11         continue
               if (iter_d .ge. itmax_d) goto 12
               if (mode .eq. 0) then
                  if (xnorm_new .lt. xnorm_old) mode = 1
               else
                  if (xnorm_new .gt. xnorm_med) goto 12
               endif
c*
c*             *** keep old soln and residual around, and its norm ***
               call xcopy(nx,ny,nz,w1,w2)
               call xcopy(nx,ny,nz,w0,w3)
               xnorm_med = xnorm_new
c*
c*             *** new damped correction, residual, and its norm ***
               call xcopy(nx,ny,nz,x(iz(1,lev)),w1)
               damp = damp / 2.0d0
               call xaxpy(nx,ny,nz,damp,xtmp(iz(1,lev)),w1)
               call nmresid(nx,ny,nz,
     2            ipc(iz(5,lev)),rpc(iz(6,lev)),
     3            ac(iz(7,lev)),cc(iz(1,lev)),fc(iz(1,lev)),
     4            w1,w0,rhs(iz(1,lev)))
               xnorm_new = xnrm1(nx,ny,nz,w0)
c*
c*             *** next iter... ***
               iter_d = iter_d + 1
               write(6,110)
     2            'NEWTON: attempting damping: iter_d, relres = ',
     3            iter_d,(xnorm_new/xnorm_den)
            goto 11 
c*
c*          *** accept the previous newton step ***
 12         continue
            call xcopy(nx,ny,nz,w2,x(iz(1,lev)))
            call xcopy(nx,ny,nz,w3,w0)
            xnorm_new = xnorm_med
            xnorm_old = xnorm_new
            write(6,110)
     2         'NEWTON: damping accepted:   iter_d, relres = ',
     3         iter_d-1,(xnorm_new/xnorm_den)
c*
c*          *** determine whether or not to disable damping ***
            if ((iter_d-1) .eq. 0) then
               print*,'% NEWTON: damping disabled...'
               idamp = 0
            endif
         else
c*
c*          *** damping is disabled -- accept the newton step ***
            damp = 1.0d0
            call xaxpy(nx,ny,nz,damp,xtmp(iz(1,lev)),x(iz(1,lev)))
            call nmresid(nx,ny,nz,
     2         ipc(iz(5,lev)),rpc(iz(6,lev)),
     3         ac(iz(7,lev)),cc(iz(1,lev)),fc(iz(1,lev)),
     4         x(iz(1,lev)),w0,rhs(iz(1,lev)))
            xnorm_new = xnrm1(nx,ny,nz,w0)
            xnorm_old = xnorm_new
         endif
c*
c*       *** compute/check the current stopping test ***
         if (iok.ne.0) then
            orsnrm = rsnrm
            if (istop .eq. 0) then
               rsnrm = xnorm_new
            elseif (istop .eq. 1) then
               rsnrm = xnorm_new
            elseif (istop .eq. 2) then
               call xcopy(nx,ny,nz,tru(iz(1,lev)),w1)
               call xaxpy(nx,ny,nz,(-1.0d0),x(iz(1,lev)),w1)
               rsnrm = xnrm1(nx,ny,nz,w1)
            elseif (istop .eq. 3) then
               call xcopy(nx,ny,nz,tru(iz(1,lev)),w1)
               call xaxpy(nx,ny,nz,(-1.0d0),x(iz(1,lev)),w1)
               rsnrm = xnrm2(nx,ny,nz,w1)
            elseif (istop .eq. 4) then
               call xcopy(nx,ny,nz,tru(iz(1,lev)),w1)
               call xaxpy(nx,ny,nz,(-1.0d0),x(iz(1,lev)),w1)
               rsnrm = xnrm2(nx,ny,nz,w1)
            elseif (istop .eq. 5) then
               call xcopy(nx,ny,nz,tru(iz(1,lev)),w1)
               call xaxpy(nx,ny,nz,(-1.0d0),x(iz(1,lev)),w1)
               call nmatvec(nx,ny,nz,
     2            ipc(iz(5,lev)),rpc(iz(6,lev)),
     3            ac(iz(7,lev)),cc(iz(1,lev)),
     4            w1,w2,w3)
               rsnrm = dsqrt(xdot(nx,ny,nz,w1,w2))
            else
               print*,'% NEWTON: bad istop value... '
            endif
            call prtstp (iok,iters,rsnrm,rsden,orsnrm)
            if ((rsnrm/rsden) .le. errtol) goto 99
         endif
c*
c*       *** check iteration count ***
         if (iters .ge. itmax) goto 99
c*
c*    *** main loop ***
      goto 30
c*
c*    *** a few things ***
 99   continue
c*
c*    *** condition estimate of final jacobian ***
      if (iinfo .gt. 2) then
         print*,'%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
     2         ,'%%%%%%%%%%'
         write(6,200)'% NEWTON: JACOBIAN ANALYSIS==>',nx,ny,nz
 200     format(a,' [',i3,',',i3,',',i3,'] ')
c*
c*       *** largest eigenvalue of the jacobian matrix ***
         print*,'% NEWTON: power calculating rho(JAC)...'
         itmax_p   = 1000
         errtol_p  = 1.0e-4
         iters_p   = 0
         iinfo_p   = iinfo
         call power(nx,ny,nz,iz,ilev,
     2      ipc,rpc,ac,cprime,
     3      w0,w1,w2,w3,
     4      rho_max,rho_max_mod,errtol_p,itmax_p,iters_p,iinfo_p)
         print*,'% NEWTON: power iters   = ',iters_p
         print*,'% NEWTON: power eigmax  = ',rho_max
         print*,'% NEWTON: power (MODEL) = ',rho_max_mod
c*
c*       *** smallest eigenvalue of the system matrix A ***
         print*,'% NEWTON: ipower calculating lambda_min(JAC)...'
         itmax_p   = 1000
         errtol_p  = 1.0e-4
         iters_p   = 0
         iinfo_p   = iinfo
         call azeros(nx,ny,nz,xtmp)
         call ipower(nx,ny,nz,xtmp,iz,
     2      w0,w1,w2,w3,rhs,
     3      rho_min,rho_min_mod,errtol_p,itmax_p,iters_p,
     4      nlev,ilev,nlev_real,mgsolv,
     5      iok_p,iinfo_p,epsiln,errtol,omega,nu1,nu2,mgsmoo,
     6      ipc,rpc,pc,ac,cprime,tru)
         print*,'% NEWTON: ipower iters   = ',iters_p
         print*,'% NEWTON: ipower eigmin  = ',rho_min
         print*,'% NEWTON: ipower (MODEL) = ',rho_min_mod
c*
c*       *** condition number estimate ***
         print*,'% NEWTON: condition number  = ',rho_max/rho_min
         print*,'% NEWTON: condition (MODEL) = ',
     2      rho_max_mod/rho_min_mod
         print*,'%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%'
     2         ,'%%%%%%%%%%'
      endif
c*
c*    *** return and end ***
      return
      end
      subroutine getjac (nx,ny,nz,nlev_real,iz,lev,ipkey,
     2   x,r,cprime,rhs,cc,pc)
c* *********************************************************************
c* purpose:
c*
c*    form the jacobian system.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      integer          iz(50,*),nx,ny,nz,nlev_real,lev,level
      integer          nxx,nyy,nzz,nxold,nyold,nzold,ipkey
      double precision x(*),r(*),cprime(*),rhs(*),cc(*),pc(*)
c*
c*    *** setup ***
      nxx    = nx
      nyy    = ny
      nzz    = nz
c*
c*    *** form the rhs of the newton system -- just current residual ***
      call xcopy(nx,ny,nz,r,rhs(iz(1,lev)))
c*
c*    *** get nonlinear part of the jacobian operator ***
      call dc_vec(cc(iz(1,lev)),x(iz(1,lev)),cprime(iz(1,lev)),
     2   nx,ny,nz,ipkey)
c*
c*    *** build the (nlev-1) level operators ***
      do 10 level = lev+1, nlev_real
         nxold = nxx
         nyold = nyy
         nzold = nzz
         call mkcors(1,nxold,nyold,nzold,nxx,nyy,nzz)
c*
c*       *** make the coarse grid rhs functions ***
         call restrc(nxold,nyold,nzold,nxx,nyy,nzz,
     2      rhs(iz(1,level-1)),rhs(iz(1,level)),pc(iz(11,level-1)))
c*
c*       *** make the coarse grid helmholtz terms ***
         call restrc(nxold,nyold,nzold,nxx,nyy,nzz,
     2      cprime(iz(1,level-1)),cprime(iz(1,level)),
     3      pc(iz(11,level-1)))
 10   continue
c*
c*    *** end it ***
      return
      end
