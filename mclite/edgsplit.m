function [V] = edgsplit(V1,V2);
%EDGSPLIT  Split an edge by introducing a new vertex
%
% Usage: [V] = edgsplit(V1,V2);
%
%    Split an edge by introducing a new vertex (perhaps at midpoint).
%    Handle manifolds by approximating a geodesic bisection.
%
% Input:
%
%    The vertices on the endpoints of the edge to be split.
%
% Output:
%
%    The new vertex representing the common endpoint of the two child edges.
%
% Author:   Michael Holst
% rcsid="$Id: edgsplit.m,v 1.1.1.1 2007/04/27 08:28:04 hrg Exp $"

%%% normal bisection case in R^2 or R^3

    V = zeros(1,3);
    V = ( V1 + V2 ) / 2.0;

%%% now handle placing the new point on a taurus

%   r=9.900000e+00;     %radius of first circle
%   R=10.000000e+00;    %radius of second circle 

%   Vec1=zeros(1,3);
%   Vec1(1:2)=V(1:2);
%   Vec1=R*Vec1*(1/norm(Vec1));
%   Vec2=V-Vec1;
%   Vec2=r*Vec2*(1/norm(Vec2));
%   V=Vec1+Vec2;

