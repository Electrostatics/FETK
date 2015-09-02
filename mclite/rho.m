function [rhoxy] = rho(x,y);
%RHO  Mass function for computing the mass matrix.
%
% Usage: [rhoxy] = rho(x,y);
%
% Author:   Michael Holst
% rcsid="$Id: rho.m,v 1.2 2008/03/12 06:23:07 fetk Exp $"

   [L,one] = size(x);
   rhoxy = ones(L,1);

