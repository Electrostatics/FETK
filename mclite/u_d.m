function [gxy] = u_d(x,y,type);
%U_D  Dirichlet boundary condition function
%
% Usage: [gxy] = u_d(x,y,type);
%
% Input:
%
%     xm(1:L,1)   ==> x-coordindinates of evaluation points
%     ym(1:L,1)   ==> y-coordindinates of evaluation points
%     type(1:L,1) ==> point type (interior/diri/neum)
%
% Output:
%
%     gxy         ==> value of the dirichlet function at evaluation points
%
% Author:   Michael Holst
% rcsid="$Id: u_d.m,v 1.2 2008/03/12 06:23:07 fetk Exp $"

   [M,one] = size(x);

   gxy = zeros(M,1);
   gxy = u_t(x,y,type);

