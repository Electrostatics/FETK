function [txy] = u_t(x,y,type);
%U_T  Analytical solution (for testing purposes, if available)
%
% Usage: [txy] = u_t(x,y,type);
%
% Input:
%
%     xm(1:L,1)   ==> x-coordindinates of evaluation points
%     ym(1:L,1)   ==> y-coordindinates of evaluation points
%     type(1:L,1) ==> point type (interior/diri/neum)
%
% Output:
%
%     txy         ==> value of the analytical solution at evaluation points
%
% Author:   Michael Holst
% rcsid="$Id: u_t.m,v 1.2 2008/03/12 06:23:07 fetk Exp $"

   [M,one] = size(x);

   txy = zeros(M,1);
   txy = sin(pi*x) .* sin(pi*y);

