function [thetam] = fu(evalKey, parm, xm,ym,type, nvec, u,ux,uy);
%FU  Evaluate the nonlinear strong form of a PDE
%
% Usage: [thetam] = fu(evalKey, parm, xm,ym,type, u,ux,uy, nvec);
%
%     Evaluate the nonlinear form by providing the value of the quantity
%     at a particular point.
%
% Input:
%
%     evalKey     ==> particular piece of the strong form that is desired
%     xm          ==> x-coordindinates of the point
%     ym          ==> y-coordindinates of the point
%     type        ==> point type (interior/diri/neum)
%
%     u           ==> u, evaluated on master element
%     ux          ==> partial w.r.t. x of u
%     uy          ==> partial w.r.t. x of u
%
%     nvec(1:2)   ==> unit outward normal vector if an element face
%
% Output:
%
%     thetam      ==> the value of the strong form at the point
%                     not including the jacobian of transformation
%
% Author:   Michael Holst
% rcsid="$Id: fu.m,v 1.2 2008/03/12 06:23:07 fetk Exp $"

   lambda = parm(1);

   %%% element residual case:  b(u)^i - a(u)^{iq}_{~;q}
   if (evalKey == 0)

      %%% value
      thetam = 0.0;

   %%% neumann face residual case:  c(u)^i + a(u)^{iq} n_q
   elseif (evalKey == 1)

      %%% apply appropriate condition based on which boundary we are on
      thetam = 0.0;
      if (type == 2)
          thetam =  pi*cos(pi*xm)*sin(pi*ym);
      elseif (type == 4)
          thetam = -pi*cos(pi*xm)*sin(pi*ym);
      elseif (type == 1)
          thetam =  pi*sin(pi*xm)*cos(pi*ym);
      elseif (type == 3)
          thetam = -pi*sin(pi*xm)*cos(pi*ym); 
      else 
         thetam = 0;
      end             

      %%% value
      thetam = thetam + ux .* nvec(:,1) + uy .* nvec(:,2);

   %%% interior face residual case:  a(u)^{iq} n_q
   elseif (evalKey == 2)

      %%% initialization
      thetam = 0.0;

      %%% value
      thetam = thetam + ux * nvec(1) + uy * nvec(2);

   %%% error
   else
      assertw( 0, 'fu 1' );
   end

