function [thetam] = fu_v(evalKey, parm, L, xm,ym,type, u,ux,uy, pr,prx,pry);
%FU_V  Evaluate the nonlinear weak form of a PDE
%
% Usage: [thetam] = fu_v(evalKey, parm, L, xm,ym,type, u,ux,uy, pr,prx,pry);
%
%     Evaluate the nonlinear form by providing the value of the quantity
%     under the integral sign, at a particular quadrature point.
%
%     Because we do this for all of the elements at one time to make things
%     reasonably fast, we pass some arrays around.
%
% Input:
%
%     evalKey     ==> area or surface integral
%     L           ==> number of elements to do all at once
%     xm(1:L,1)   ==> x-coordindinates of quadrature points, one per element
%     ym(1:L,1)   ==> y-coordindinates of quadrature points, one per element
%     type(1:L,1) ==> point type (interior/diri/neum), one per element
%
%     u(1:L,1)    ==> u, evaluated on master element
%     ux(1:L,1)   ==> partial w.r.t. x of u, one per element
%     uy(1:L,1)   ==> partial w.r.t. x of u, one per element
%
%     pr          ==> phi(r), evaluated on master element
%     prx(1:L,1)  ==> partial w.r.t. x of phi(r), one per element
%     pry(1:L,1)  ==> partial w.r.t. x of phi(r), one per element
%
% Output:
%
%     thetam      ==> the integrand for the area or surface integral,
%                     not including the jacobian of transformation
%
% Author:   Michael Holst
% rcsid="$Id: fu_v.m,v 1.2 2008/03/12 06:23:07 fetk Exp $"

   lambda = parm(1);

   %%% area integral
   if (evalKey == 0)

      %%% coefficients
      atilde = ones(L,1);   % the first order coefficient function

      %%% source term chosen to give (one) analytical solution
      utilde(1:L,1) = sin(pi*xm) .* sin(pi*ym);
      ftilde(1:L,1) = (2*pi*pi) * atilde(1:L,1) .* utilde(1:L,1) ...
                    + lambda * exp(utilde(1:L,1));

      %%% nonlinear residual of the given FEM function "u"
      thetam(1:L,1) = ...
         atilde(1:L,1) .* (ux(1:L,1).*prx(1:L,1)+uy(1:L,1).*pry(1:L,1)) ...
       + (lambda * exp(u(1:L,1)) - ftilde(1:L,1)) * pr;

   %%% edge integral (for natural boundary condition)
   elseif (evalKey == 1)

      %%% apply appropriate condition based on which boundary we are on
      thetam = zeros(L,1);
      for k=1:L  
         if (type(k) == 2)
             thetam(k) =  pi*cos(pi*xm(k))*sin(pi*ym(k))*pr;
         elseif (type(k) == 4)
             thetam(k) = -pi*cos(pi*xm(k))*sin(pi*ym(k))*pr;
         elseif (type(k) == 1)
             thetam(k) =  pi*sin(pi*xm(k))*cos(pi*ym(k))*pr;
         elseif (type(k) == 3)
             thetam(k) = -pi*sin(pi*xm(k))*cos(pi*ym(k))*pr; 
         else 
             thetam(k) = 0;
         end
      end             

   %%% error
   else
      assertw( 0, 'fu_v 1' );
   end

