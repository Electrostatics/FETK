%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File:          mc2.m
%
% Dimension:     2
% Domain:        A square divided into 18 triangles.
% Boundary:      All dirichlet nodes
%
% rcsid="$Id: mcin.m,v 1.7 2010/08/12 05:17:11 fetk Exp $"
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% MC = < Manifold Code >
%%% Copyright (C) 1994-- Michael Holst 
%%%
%%% This library is free software; you can redistribute it and/or 
%%% modify it under the terms of the GNU Lesser General Public 
%%% License as published by the Free Software Foundation; either  
%%% version 2.1 of the License, or (at your option) any later version. 
%%%
%%% This library is distributed in the hope that it will be useful, 
%%% but WITHOUT ANY WARRANTY; without even the implied warranty of             
%%% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
%%% Lesser General Public License for more details. 
%%%
%%% You should have received a copy of the GNU Lesser General Public 
%%% License along with this library; if not, write to the Free Software  
%%% Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   
%%%
%%% rcsid="$Id: mcin.m,v 1.7 2010/08/12 05:17:11 fetk Exp $"
%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mcsf_begin=1;

      dim=2;         % intrinsic manifold dimension
    dimii=3;         % imbedding manifold dimension
 vertices=16;        % number of vertices
simplices=18;        % number of simplices

vert=[
%-------- ---- ----------------- ----------------- -----------------
% Vert-ID Chrt X-Coordinate      Y-Coordinate      Z-Coordinate
%-------- ---- ----------------- ----------------- -----------------
0         0     0.0000000000e+00  0.0000000000e+00  0.0000000000e+00
1         0     3.3333330000e-01  0.0000000000e+00  0.0000000000e+00
2         0     6.6666670000e-01  0.0000000000e+00  0.0000000000e+00
3         0     1.0000000000e+00  0.0000000000e+00  0.0000000000e+00
4         0     0.0000000000e+00  3.3333330000e-01  0.0000000000e+00
5         0     3.3333330000e-01  3.3333330000e-01  0.0000000000e+00
6         0     6.6666670000e-01  3.3333330000e-01  0.0000000000e+00
7         0     1.0000000000e+00  3.3333330000e-01  0.0000000000e+00
8         0     0.0000000000e+00  6.6666670000e-01  0.0000000000e+00
9         0     3.3333330000e-01  6.6666670000e-01  0.0000000000e+00
10        0     6.6666670000e-01  6.6666670000e-01  0.0000000000e+00
11        0     1.0000000000e+00  6.6666670000e-01  0.0000000000e+00
12        0     0.0000000000e+00  1.0000000000e+00  0.0000000000e+00
13        0     3.3333330000e-01  1.0000000000e+00  0.0000000000e+00
14        0     6.6666670000e-01  1.0000000000e+00  0.0000000000e+00
15        0     1.0000000000e+00  1.0000000000e+00  0.0000000000e+00
];

simp=[
%-------- ---- ---- ------------------- ---------------------------------------
% Simp-ID Grp  Mat  Face-Types          Vertex-Numbers
%-------- ---- ---- ------------------- ---------------------------------------
0         0    0    0    1    1         0 1 4
1         0    0    0    0    0         1 5 4
2         0    0    0    0    1         1 2 5
3         0    0    0    0    0         2 6 5
4         0    0    0    0    1         2 3 6
5         0    0    0    0    1         3 7 6
6         0    0    0    1    0         4 5 8
7         0    0    0    0    0         5 9 8
8         0    0    0    0    0         5 6 9
9         0    0    0    0    0         6 10 9
10        0    0    0    0    0         6 7 10
11        0    0    0    0    1         7 11 10
12        0    0    0    1    0         8 9 12
13        0    0    1    0    0         9 13 12
14        0    0    0    0    0         9 10 13
15        0    0    1    0    0         10 14 13
16        0    0    0    0    0         10 11 14
17        0    0    1    0    1         11 15 14
];

mcsf_end=1;

