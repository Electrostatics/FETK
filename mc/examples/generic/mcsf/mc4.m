%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File:          mc4.m
%
% Dimension:     2
% Domain:        Semi-adapted tesselation of an L-shaped domain.
% Boundary:      All bndry nodes are dirichlet-type.
%
% rcsid="$Id: mc4.m,v 1.4 2010/08/12 05:17:22 fetk Exp $"
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
%%% rcsid="$Id: mc4.m,v 1.4 2010/08/12 05:17:22 fetk Exp $"
%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mcsf_begin=1;

      dim=2;         % intrinsic manifold dimension
    dimii=3;         % imbedding manifold dimension
 vertices=22;        % number of vertices
simplices=30;        % number of simplices

vert=[
%-------- ---- ----------------- ----------------- -----------------
% Vert-ID Chrt X-Coordinate      Y-Coordinate      Z-Coordinate
%-------- ---- ----------------- ----------------- -----------------
0         0     0.0000000000e+00  1.0000000000e+00  0.0000000000e+00
1         0    -1.0000000000e+00  1.0000000000e+00  0.0000000000e+00
2         0    -1.0000000000e+00  0.0000000000e+00  0.0000000000e+00
3         0    -1.0000000000e+00 -1.0000000000e+00  0.0000000000e+00
4         0     0.0000000000e+00 -1.0000000000e+00  0.0000000000e+00
5         0     1.0000000000e+00 -1.0000000000e+00  0.0000000000e+00
6         0     1.0000000000e+00  0.0000000000e+00  0.0000000000e+00
7         0     5.0000000000e-01  0.0000000000e+00  0.0000000000e+00
8         0     5.0000000000e-01 -5.0000000000e-01  0.0000000000e+00
9         0     0.0000000000e+00 -5.0000000000e-01  0.0000000000e+00
10        0    -5.0000000000e-01 -5.0000000000e-01  0.0000000000e+00
11        0    -5.0000000000e-01  0.0000000000e+00  0.0000000000e+00
12        0    -5.0000000000e-01  5.0000000000e-01  0.0000000000e+00
13        0     0.0000000000e+00  5.0000000000e-01  0.0000000000e+00
14        0     0.0000000000e+00  2.5000000000e-01  0.0000000000e+00
15        0    -2.5000000000e-01  2.5000000000e-01  0.0000000000e+00
16        0    -2.5000000000e-01  0.0000000000e+00  0.0000000000e+00
17        0    -2.5000000000e-01 -2.5000000000e-01  0.0000000000e+00
18        0     0.0000000000e+00 -2.5000000000e-01  0.0000000000e+00
19        0     2.5000000000e-01 -2.5000000000e-01  0.0000000000e+00
20        0     2.5000000000e-01  0.0000000000e+00  0.0000000000e+00
21        0     0.0000000000e+00  0.0000000000e+00  0.0000000000e+00
];

simp=[
%-------- ---- ---- ------------------- ---------------------------------------
% Simp-ID Grp  Mat  Face-Types          Vertex-Numbers
%-------- ---- ---- ------------------- ---------------------------------------
0         0    0    0    0    1         0 1 12
1         0    0    0    0    1         1 2 12
2         0    0    0    0    1         2 3 10
3         0    0    0    0    1         3 4 10
4         0    0    0    0    1         4 5 8
5         0    0    0    0    1         5 6 8
6         0    0    0    0    1         6 7 8
7         0    0    0    0    0         4 8 9
8         0    0    0    0    0         4 9 10
9         0    0    0    0    0         2 10 11
10        0    0    0    0    0         2 11 12
11        0    0    0    1    0         0 12 13
12        0    0    0    0    0         12 15 13
13        0    0    0    0    0         11 15 12
14        0    0    0    0    0         10 17 11
15        0    0    0    0    0         9 17 10
16        0    0    0    0    0         8 19 9
17        0    0    0    0    0         7 19 8
18        0    0    0    0    1         7 20 19
19        0    0    0    0    0         9 19 18
20        0    0    0    0    0         9 18 17
21        0    0    0    0    0         11 17 16
22        0    0    0    0    0         11 16 15
23        0    0    0    1    0         13 15 14
24        0    0    0    0    0         14 15 16
25        0    0    0    0    0         16 17 18
26        0    0    0    0    0         18 19 20
27        0    0    1    0    0         18 20 21
28        0    0    0    0    0         16 18 21
29        0    0    0    1    0         14 16 21
];

mcsf_end=1;

